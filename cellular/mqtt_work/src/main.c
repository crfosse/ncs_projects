/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <stdio.h>
#include <drivers/uart.h>
#include <string.h>
#include <random/rand32.h>
#include <net/mqtt.h>
#include <net/socket.h>
#include <modem/lte_lc.h>
#include <date_time.h>
#include <stdio.h>
#include <cJSON.h>
#include <modem/modem_info.h>

#include <dk_buttons_and_leds.h>

#define LOG_MODULE_NAME mqtt_demo
LOG_MODULE_REGISTER(LOG_MODULE_NAME, CONFIG_MQTT_DEMO_LOG_LEVEL);

/* Buffers for MQTT client. */
static uint8_t rx_buffer[CONFIG_MQTT_MESSAGE_BUFFER_SIZE];
static uint8_t tx_buffer[CONFIG_MQTT_MESSAGE_BUFFER_SIZE];
static uint8_t payload_buf[CONFIG_MQTT_PAYLOAD_BUFFER_SIZE];

/* The mqtt client struct */
static struct mqtt_client client;

/* MQTT Broker details. */
static struct sockaddr_storage broker;

/* File descriptor */
static struct pollfd fds;

static uint32_t current_rsrp;
K_MUTEX_DEFINE(rsrp_mutex);

/**** APPLICATION ADDITIONS - Start ****/

/* Test settings */
#define SAMPLE_INTERVAL      1  //Seconds - in this application the sample interval only describes how long main sleeps between wakeups when not connected
#define TRANSMISSION_INTERVAL 5 //Minutes - how often the timer fires to transmit samples
#define MQTT_TIMEOUT K_SECONDS(20)
#define FIDO_TRACE

/* Work queue and items */
#define APP_STACK_SIZE 4096
#define WORK_PRIORITY 5

K_THREAD_STACK_DEFINE(app_stack_area, APP_STACK_SIZE);

struct k_work_q app_work_q;
struct k_work alarm_work;
struct k_work periodic_work;

/* semaphores for real time control*/
static K_SEM_DEFINE(mqtt_connect_ok, 0, 1);
static K_SEM_DEFINE(mqtt_puback_ok, 0, 1);
static K_SEM_DEFINE(date_time_ok, 0, 1);

/* Types of messages transmitted by the application */
enum app_msg_type {
	SENSOR_ALARM,
	SENSOR_SAMPLE
};

struct app_message {
	char data[CONFIG_MQTT_MESSAGE_BUFFER_SIZE];
	size_t len;
};

/* forward declarations */
int app_connect(void);
void app_disconnect(void);
void create_message(struct app_message * destination, enum app_msg_type type, uint8_t* data, size_t len, int64_t * timestamp);

/* Connection status (should be mutex protected?) */
bool app_connected = false;

// TEST_DATA_SIZE
#define TEST_DATA_SIZE 100

//random characters in an array for upload testing
uint8_t * testData = "yK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQyK3vQHgUQ";

/**** APPLICATION ADDITIONS - End ****/

#if defined(CONFIG_BSD_LIBRARY)

/**@brief Recoverable BSD library error. */
void bsd_recoverable_error_handler(uint32_t err)
{
	LOG_ERR("bsdlib recoverable error: %u", (unsigned int)err);
}

#endif /* defined(CONFIG_BSD_LIBRARY) */

#include <soc.h>
#include <nrfx.h>

/**@brief Function to print strings without null-termination
 */
static void data_print(uint8_t *prefix, uint8_t *data, size_t len)
{
	char buf[len + 1];

	memcpy(buf, data, len);
	buf[len] = 0;
	LOG_INF("%s%s", log_strdup(prefix), log_strdup(buf));
}

/**@brief Function to publish data on the configured topic
 */
static int data_publish(struct mqtt_client *c, enum mqtt_qos qos,
	uint8_t *data, size_t len)
{
	
	struct mqtt_publish_param param;

	param.message.topic.qos = qos;
	param.message.topic.topic.utf8 = CONFIG_MQTT_PUB_TOPIC;
	param.message.topic.topic.size = strlen(CONFIG_MQTT_PUB_TOPIC);
	param.message.payload.data = data;
	param.message.payload.len = len;
	param.message_id = k_cycle_get_32();
	param.dup_flag = 0;
	param.retain_flag = 0;

	//("Publishing: %s", data, len);
	LOG_INF("Publishing: %s", log_strdup(data));
	LOG_DBG("to topic: %s len: %u",
		log_strdup(CONFIG_MQTT_PUB_TOPIC),
		(unsigned int)strlen(CONFIG_MQTT_PUB_TOPIC));

	return mqtt_publish(c, &param);
}

/**@brief Function to subscribe to the configured topic
 */
/*
static int subscribe(void)
{
	struct mqtt_topic subscribe_topic = {
		.topic = {
			.utf8 = CONFIG_MQTT_SUB_TOPIC,
			.size = strlen(CONFIG_MQTT_SUB_TOPIC)
		},
		.qos = MQTT_QOS_1_AT_LEAST_ONCE
	};

	const struct mqtt_subscription_list subscription_list = {
		.list = &subscribe_topic,
		.list_count = 1,
		.message_id = 1234
	};

	printk("Subscribing to: %s len %u\n", CONFIG_MQTT_SUB_TOPIC,
		(unsigned int)strlen(CONFIG_MQTT_SUB_TOPIC));

	return mqtt_subscribe(&client, &subscription_list);
}
*/

/**@brief Function to read the published payload.
 */
static int publish_get_payload(struct mqtt_client *c, size_t length)
{
	uint8_t *buf = payload_buf;
	uint8_t *end = buf + length;

	if (length > sizeof(payload_buf)) {
		return -EMSGSIZE;
	}

	while (buf < end) {
		int ret = mqtt_read_publish_payload(c, buf, end - buf);

		if (ret < 0) {
			int err;

			if (ret != -EAGAIN) {
				return ret;
			}

			LOG_ERR("mqtt_read_publish_payload: EAGAIN");

			err = poll(&fds, 1,
				   CONFIG_MQTT_KEEPALIVE * MSEC_PER_SEC);
			if (err > 0 && (fds.revents & POLLIN) == POLLIN) {
				continue;
			} else {
				return -EIO;
			}
		}

		if (ret == 0) {
			return -EIO;
		}

		buf += ret;
	}

	return 0;
}

/**@brief MQTT client event handler
 */
void mqtt_evt_handler(struct mqtt_client *const c,
		      const struct mqtt_evt *evt)
{
	int err;

	switch (evt->type) {
	case MQTT_EVT_CONNACK:
		if (evt->result != 0) {
			LOG_ERR("MQTT connect failed %d", evt->result);
			break;
		}

		k_sem_give(&mqtt_connect_ok);
		LOG_INF("[%s:%d] MQTT client connected!", log_strdup(__func__), __LINE__);
		//subscribe();
		break;

	case MQTT_EVT_DISCONNECT:
		LOG_INF("[%s:%d] MQTT client disconnected %d", log_strdup(__func__),
		       __LINE__, evt->result);

		break;

	case MQTT_EVT_PUBLISH: {
		const struct mqtt_publish_param *p = &evt->param.publish;

		LOG_INF("[%s:%d] MQTT PUBLISH result=%d len=%d", log_strdup(__func__),
		       __LINE__, evt->result, p->message.payload.len);
		err = publish_get_payload(c, p->message.payload.len);
		if (err >= 0) {
			data_print("Received: ", payload_buf,
				p->message.payload.len);
		} else {
			LOG_ERR("mqtt_read_publish_payload: Failed! %d", err);
			LOG_INF("Disconnecting MQTT client...");

			err = mqtt_disconnect(c);
			if (err) {
				LOG_ERR("Could not app_disconnect: %d", err);
			}
		}
	} break;

	case MQTT_EVT_PUBACK:
		if (evt->result != 0) {
			LOG_ERR("MQTT PUBACK error %d", evt->result);
			break;
		}

		k_sem_give(&mqtt_puback_ok);

		LOG_INF("[%s:%d] PUBACK packet id: %u", log_strdup(__func__), __LINE__,
				evt->param.puback.message_id);
		break;

	case MQTT_EVT_SUBACK:
		if (evt->result != 0) {
			LOG_ERR("MQTT SUBACK error %d", evt->result);
			break;
		}

		LOG_INF("[%s:%d] SUBACK packet id: %u", log_strdup(__func__), __LINE__,
				evt->param.suback.message_id);
		break;

	default:
		LOG_INF("[%s:%d] default: %d", log_strdup(__func__), __LINE__,
				evt->type);
		break;
	}
}

/**@brief Resolves the configured hostname and
 * initializes the MQTT broker structure
 */
static void broker_init(void)
{
	int err;
	struct addrinfo *result;
	struct addrinfo *addr;
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM
	};

	err = getaddrinfo(CONFIG_MQTT_BROKER_HOSTNAME, NULL, &hints, &result);
	if (err) {
		LOG_ERR("ERROR: getaddrinfo failed %d", err);

		return;
	}

	addr = result;
	err = -ENOENT;

	/* Look for address of the broker. */
	while (addr != NULL) {
		/* IPv4 Address. */
		if (addr->ai_addrlen == sizeof(struct sockaddr_in)) {
			struct sockaddr_in *broker4 =
				((struct sockaddr_in *)&broker);
			char ipv4_addr[NET_IPV4_ADDR_LEN];

			broker4->sin_addr.s_addr =
				((struct sockaddr_in *)addr->ai_addr)
				->sin_addr.s_addr;
			broker4->sin_family = AF_INET;
			broker4->sin_port = htons(CONFIG_MQTT_BROKER_PORT);

			inet_ntop(AF_INET, &broker4->sin_addr.s_addr,
				  ipv4_addr, sizeof(ipv4_addr));
			LOG_INF("IPv4 Address found %s", log_strdup(ipv4_addr));

			break;
		} else {
			LOG_WRN("ai_addrlen = %u should be %u or %u",
				(unsigned int)addr->ai_addrlen,
				(unsigned int)sizeof(struct sockaddr_in),
				(unsigned int)sizeof(struct sockaddr_in6));
		}

		addr = addr->ai_next;
		break;
	}

	/* Free the address. */
	freeaddrinfo(result);
}

/**@brief Initialize the MQTT client structure
 * DEV: Modified - Moved broker_init out.
 */
static void client_init(struct mqtt_client *client)
{
	mqtt_client_init(client);

	broker_init();

	/* MQTT client configuration */
	client->broker = &broker;
	client->evt_cb = mqtt_evt_handler;
	client->client_id.utf8 = (uint8_t *)CONFIG_MQTT_CLIENT_ID;
	client->client_id.size = strlen(CONFIG_MQTT_CLIENT_ID);
	client->password = NULL;
	client->user_name = NULL;
	client->protocol_version = MQTT_VERSION_3_1_1;

	/* MQTT buffers configuration */
	client->rx_buf = rx_buffer;
	client->rx_buf_size = sizeof(rx_buffer);
	client->tx_buf = tx_buffer;
	client->tx_buf_size = sizeof(tx_buffer);

	/* MQTT transport configuration */
#if defined(CONFIG_MQTT_LIB_TLS)
	client->transport.type = MQTT_TRANSPORT_SECURE;
#else
	client->transport.type = MQTT_TRANSPORT_NON_SECURE;
#endif
}

/**@brief Initialize the file descriptor structure used by poll.
 */
static int fds_init(struct mqtt_client *c)
{
	if (c->transport.type == MQTT_TRANSPORT_NON_SECURE) {
		fds.fd = c->transport.tcp.sock;
	} else {
#if defined(CONFIG_MQTT_LIB_TLS)
		fds.fd = c->transport.tls.sock;
#else
		return -ENOTSUP;
#endif
	}

	fds.events = POLLIN;

	return 0;
}

/**@brief Configures modem to provide LTE link. Blocks until link is
 * successfully established.
 */
static int modem_configure(void)
{
#if defined(CONFIG_LTE_LINK_CONTROL)
	if (IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT)) {
		/* Do nothing, modem is already turned on
		 * and connected.
		 */
	} else {
		int err;

		LOG_INF("LTE Link Connecting ...");
		err = lte_lc_init_and_connect();
		if(err) {
			LOG_ERR("LTE link could not be established.");
			return -1;
		}
		LOG_INF("LTE Link Connected!");

		return 0;
	}
#endif /* defined(CONFIG_LTE_LINK_CONTROL) */
}

/**** Application code - Start ****/

/**@brief Callback for button events from the DK buttons and LEDs library. 
*  Can be used to simulate alarm events.
*/

static void button_handler(uint32_t button_states, uint32_t has_changed)
{
	if (has_changed & button_states & DK_BTN1_MSK) {
		LOG_DBG("DEV_DBG: button 1 pressed");
		k_work_submit_to_queue(&app_work_q, &alarm_work);
	}
	else if (has_changed & button_states & DK_BTN2_MSK) {
	
	}

	return;
}

/**@brief Initializes buttons and LEDs, using the DK buttons and LEDs
 * library.
 */
static void buttons_leds_init(void)
{
	int err;

	LOG_DBG("Initalizing buttons and leds.");

	err = dk_buttons_init(button_handler);
	if (err) {
		LOG_ERR("Could not initialize buttons, err code: %d", err);
	}

	err = dk_leds_init();
	if (err) {
		LOG_ERR("Could not initialize leds, err code: %d", err);
	}

	err = dk_set_leds_state(DK_ALL_LEDS_MSK, DK_NO_LEDS_MSK);
	if (err) {
		LOG_ERR("Could not set leds state, err code: %d", err);
	}
}

/* @brief triggers every minute. Publish work if one period has passed */ 
void app_timer_handler(struct k_timer *dummy)
{
	static uint32_t minutes;

	minutes++;
	/* This shall match the PSM interval*/
	if (minutes % TRANSMISSION_INTERVAL == 0) {
		printk("Timer: fired sample interval\n");
		k_work_submit_to_queue(&app_work_q, &periodic_work);
	}
	printk("Elapsed time: %d\n", minutes);
}

K_TIMER_DEFINE(app_timer, app_timer_handler, NULL);

/* @brief initializes timer that triggers every minute */
void timer_init(void)
{
	k_timer_start(&app_timer, K_MINUTES(1), K_MINUTES(1));
}

void publish_samples(struct k_work *item) {
	int err;
	err = app_connect();
	if(err) {
		LOG_ERR("PUBLISH_SAMPLES: connect failed with error %d", err);
		//TODO: Handle error here
		app_disconnect();
		return;
	}
	LOG_DBG("Publish Samples");
	
	//Lighting LED2 to indicate that transmission is initiated
	dk_set_led(DK_LED2, 0);
	
	//Get timestamp
	int64_t curr_time;
	date_time_now(&curr_time);

	//Format JSON message
	struct app_message message;
	create_message(&message, SENSOR_SAMPLE, testData, sizeof(testData), &curr_time);

	//Publish message
	data_publish(&client, MQTT_QOS_1_AT_LEAST_ONCE, message.data, message.len);

	//Wait for publish acknowledgement
	k_sem_take(&mqtt_puback_ok, K_FOREVER);
	
	//Transmission phase over.
	dk_set_led(DK_LED2, 1);

	app_disconnect();
}

void publish_alarm(struct k_work *item) {	
	int err;

	err = app_connect();
	if(err) {
		LOG_ERR("PUBLISH_ALARM: connect failed with error %d", err);
		//retry_publish = true;
		//TODO: Handle error here.
		app_disconnect();
		return;
	}
	LOG_DBG("Publish alarm");

	//Lighting LED2 to indicate that transmission is initiated
	dk_set_led(DK_LED2, 0);
	
	//Sample simulator
	uint8_t * curr_sample = "x";

	//Get timestamp
	int64_t curr_time;
	date_time_now(&curr_time);

	//Create JSON formatted message
	struct app_message message;
	create_message(&message, SENSOR_ALARM, curr_sample, 1, &curr_time);

	//LOG_INF("%s", log_strdup(message));

	//Publish message
	data_publish(&client, MQTT_QOS_1_AT_LEAST_ONCE, message.data, message.len);

	//Wait for publish acknowledgement
	err = k_sem_take(&mqtt_puback_ok, MQTT_TIMEOUT);
	if(err) {
		LOG_ERR("MQTT publish acknowledgement timed out\n");
	}

	//Transmission phase over.
	dk_set_led(DK_LED2, 1);
	app_disconnect();
}

int app_connect(void) {
	LOG_INF("Connecting");
	int err;

	while(lte_lc_connect() != 0) {
		LOG_WRN("Failed to establish LTE connection.");
		LOG_WRN("Will retry in %d seconds.",
				CONFIG_APP_CONNECT_RETRY_DELAY);
		//TODO: limit number of retries
		k_sleep(K_SECONDS(CONFIG_APP_CONNECT_RETRY_DELAY));
	}

	LOG_INF("LTE: Link connected");

	err = mqtt_connect(&client);
	if (err != 0) {
		LOG_ERR("mqtt_connect %d", err);
		return err;
	}

	err = fds_init(&client);
	if (err != 0) {
		LOG_ERR("fds_init %d", err);
		return err;
	}

	app_connected = true;

	/* Wait for connection to finish */
	err = k_sem_take(&mqtt_connect_ok, MQTT_TIMEOUT);
	if(err) {
		LOG_ERR("MQTT connection timed out\n");
		app_connected = false;
		return -ENOTCONN;
	}

	//Lock to write out RSRP
	k_mutex_lock(&rsrp_mutex, K_FOREVER);
	LOG_INF("RSRP: %d", current_rsrp);
	k_mutex_unlock(&rsrp_mutex);

	return 0;
}

void app_disconnect(void) {
	LOG_INF("Disconnecting");
	int err;

	if(!app_connected) {
		//Never connected in the first place. Means that we need an abort.
		LOG_INF("Aborting mqtt connection");
		mqtt_abort(&client);
	} else {
		app_connected = 0;
		err = mqtt_disconnect(&client);
		if (err != 0) {
			LOG_ERR("mqtt_disconnect %d", err);
			return;
		}
	}
	LOG_INF("MQTT: disconnected");

	k_sleep(K_SECONDS(1));
	err = lte_lc_offline();
	if(err) {
		LOG_ERR("LTE: Offline mode failed\n");
	}
	LOG_INF("LTE: offline");
}

void init_work(void) {
	k_work_q_start(&app_work_q, app_stack_area, K_THREAD_STACK_SIZEOF(app_stack_area), WORK_PRIORITY);

	k_work_init(&alarm_work, publish_alarm);
	k_work_init(&periodic_work, publish_samples);
}

void date_time_handler(const struct date_time_evt *evt) {

	switch (evt->type)
	{
	case DATE_TIME_OBTAINED_MODEM:
		LOG_DBG("DATE_TIME: got time from modem.\n");
		k_sem_give(&date_time_ok);
		break;
	case DATE_TIME_OBTAINED_NTP:
		LOG_DBG("DATE_TIME: got time from NTP.\n");
		k_sem_give(&date_time_ok);
		break;
	case DATE_TIME_OBTAINED_EXT:
		LOG_DBG("DATE_TIME: got time from external.\n");
		k_sem_give(&date_time_ok);
		break;
	case DATE_TIME_NOT_OBTAINED:
		LOG_DBG("DATE_TIME: failed to get time.\n");
		k_sem_give(&date_time_ok);
		break;
	default:
		break;
	}
}

void create_message(struct app_message* destination, enum app_msg_type type, uint8_t *data, size_t len, int64_t *timestamp) {

	cJSON *message;

	message = cJSON_CreateObject();
	
	if(type == SENSOR_ALARM) {
		cJSON_AddStringToObject(message, "type", "alarm");
	} else {
		cJSON_AddStringToObject(message, "type", "periodic sample");
	}

	char time_str[16];
	snprintf(time_str, 16, "%lld", *timestamp);

	char data_str[len];
	snprintf(data_str, len, "%s", data);

	cJSON_AddStringToObject(message, "timestamp", time_str);
	cJSON_AddStringToObject(message, "data", data);

	destination->len = strlen(cJSON_Print(message));

	strcpy(destination->data, cJSON_Print(message));

	cJSON_Delete(message);
}

void rsrp_cb(char rsrp_val) {
	
	k_mutex_lock(&rsrp_mutex, K_FOREVER);
    current_rsrp = rsrp_val;
    LOG_DBG("RSRP callback: %d", rsrp_val);
	k_mutex_unlock(&rsrp_mutex);

}

/**** Application code - End ****/

void main(void)
{
	int err;

    LOG_INF("MQTT sensor application example started");

	while(modem_configure() != 0) {
		LOG_WRN("Failed to establish LTE connection.");
		LOG_WRN("Will retry in %d seconds.",
				CONFIG_APP_CONNECT_RETRY_DELAY);
		k_sleep(K_SECONDS(CONFIG_APP_CONNECT_RETRY_DELAY));
	}
	

	
	date_time_update_async(date_time_handler);
	k_sem_take(&date_time_ok,K_FOREVER);

	client_init(&client);

	buttons_leds_init(); /* Button for "alarm simulation" and leds for control */
	timer_init(); /* Periodic sample timer */
	init_work();  /* Work queue and items for sampling and alarm */
	
	modem_info_init();
  	modem_info_rsrp_register(rsrp_cb);

	err = lte_lc_offline();
	if(err) {
		LOG_ERR("LTE: Offline mode failed");
	}


	//Lighting LED1 to indicate that the application entering main loop.
	dk_set_led(DK_LED1, 0);

	while (1) {
		if(app_connected) {
			err = poll(&fds, 1, mqtt_keepalive_time_left(&client));
			if (err < 0) {
				printk("ERROR: poll %d\n", errno);
				break;
			}
			/* Check if the app is still connected, as it can be disconnnected
			 * during poll. */
			if(app_connected) { 
				err = mqtt_live(&client);
				if ((err != 0) && (err != -EAGAIN)) {
					LOG_ERR("ERROR: mqtt_live %d", err);
					break;
				}

				if ((fds.revents & POLLIN) == POLLIN) {
					err = mqtt_input(&client);
					if (err != 0) {
						LOG_ERR("ERROR: mqtt_input %d", err);
						continue;
					}
				}

				if ((fds.revents & POLLERR) == POLLERR) {
					LOG_ERR("POLLERR");
					break;
				}

				if ((fds.revents & POLLNVAL) == POLLNVAL) {
					LOG_ERR("POLLNVAL");
					continue;
				}
			}
		} else
		{
			k_sleep(K_SECONDS(SAMPLE_INTERVAL));
		}
	}

	LOG_INF("Disconnecting MQTT client...");

	err = mqtt_disconnect(&client);
	if (err) {
		LOG_ERR("Could not disconnect MQTT client. Error: %d", err);
	}
}
