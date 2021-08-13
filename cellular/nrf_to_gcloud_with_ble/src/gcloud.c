#include<logging/log.h>

#include <zephyr.h>
#include <kernel.h>
#include <string.h>
#include <errno.h>

#include <date_time.h>

#include <net/mqtt.h>
#include <net/socket.h>
#include <net/tls_credentials.h>

#include <modem/modem_key_mgmt.h>
#include <modem/modem_jwt.h>
#include <nrf_modem.h>

#include "gcloud.h"

#include "globalsign.inc"

#define CONFIGURATION_SUBSCRIPTION

#define GCLOUD_ID "projects/" CONFIG_GCLOUD_PROJECT_NAME "/locations/" CONFIG_GCLOUD_REGION "/registries/" CONFIG_GCLOUD_REGISTRY_NAME "/devices/" CONFIG_GCLOUD_DEVICE_NAME

#define GCLOUD_HOSTNAME "mqtt.googleapis.com" 
#define BROKER_ADDR GCLOUD_HOSTNAME
#define BROKER_PORT 8883

#define GCLOUD_SEC_TAG 16842752
#define SUBSCRIBE_ID 42

#define MQTT_LIVE_PERIOD K_SECONDS(55)
#define GCLOUD_DISCONNECT_INTERVAL K_HOURS(12)
//#define GCLOUD_DISCONNECT_INTERVAL K_MINUTES(1) //For testing purposes


#define GCLOUD_CONFIG_TOPIC "/devices/" CONFIG_GCLOUD_DEVICE_NAME "/config"
#define GCLOUD_STATE_TOPIC "/devices/" CONFIG_GCLOUD_DEVICE_NAME "/state"
#define GCLOUD_TOPIC "/devices/" CONFIG_GCLOUD_DEVICE_NAME "/events"

#define JWT_BUFFER_SIZE 850

#define GCLOUD_THREAD_STACK_SIZE 2048

#define GCLOUD_THREAD_PRIORITY 7

#define DEFAULT_MSGQ_TIMEOUT K_SECONDS(100)

LOG_MODULE_REGISTER(gcloud);

/* Buffers for MQTT client. */
static uint8_t rx_buffer[CONFIG_MQTT_MESSAGE_BUFFER_SIZE];
static uint8_t tx_buffer[CONFIG_MQTT_MESSAGE_BUFFER_SIZE];
static uint8_t payload_buffer[CONFIG_MQTT_PAYLOAD_BUFFER_SIZE];

/* MQTT thrad definitions */
static K_THREAD_STACK_DEFINE(mqtt_stack_area, 4096);
static struct k_thread mqtt_thread;
static k_tid_t mqtt_tid;

/* File descriptor */
static struct pollfd fds;

static K_SEM_DEFINE(gc_connected_sem, 0, 1);

extern void gcloud_thread(void *, void *, void *);

enum gcloud_event_type {
    CONNECT,
    PUBLISH_STATE,
    PUBLISH,
    RECONNECT_TIMEOUT,
    DISCONNECT,
    SUBSCRIBE
};

struct empty {};

union gcloud_event_param {
    struct empty connect;
    struct mqtt_publish_message publish_state; // This could be a whole mqtt message, thus allowing custom topics
    struct mqtt_publish_message publish;
    struct empty reconnect_timeout;
    struct empty disconnect;
    struct empty subscribe; // Here we could add the list of topics to be subscribed to
};

struct gcloud_event {
    enum gcloud_event_type type;
    union gcloud_event_param param;
};

static struct mqtt_client client;
static struct sockaddr_storage mqtt_broker;
static struct mqtt_sec_config tls_config;

char jwt_buffer[JWT_BUFFER_SIZE];
static struct mqtt_utf8 jwt_token = {
    .utf8 = jwt_buffer
};
static struct mqtt_utf8 username = {
    .utf8 = "unused",
    .size = sizeof("unused")
};

static struct mqtt_topic gcloud_topics_list[] = {
    {
        .topic = {
            .utf8 = GCLOUD_CONFIG_TOPIC,
            .size = sizeof(GCLOUD_CONFIG_TOPIC) - 1
        },
        .qos = MQTT_QOS_1_AT_LEAST_ONCE
    }
};



static received_config_handler_t received_config_handler = NULL;

#define N_MESSAGES 3
K_MSGQ_DEFINE(gcloud_msgq, sizeof(struct gcloud_event), N_MESSAGES, 4);

static void mqtt_event_handler(struct mqtt_client *const cli, const struct mqtt_evt *evt);

void reconnect_timer_handler(struct k_timer *timer_id);
K_TIMER_DEFINE(reconnect_timer, reconnect_timer_handler, NULL);

int k_msgq_get_atomic(struct k_msgq *q, void *data, k_timeout_t timeout);
int k_msgq_put_atomic(struct k_msgq *q, void *data, k_timeout_t timeout);

static bool connected = false;
static bool connecting = false;

/**@brief Function to print strings without null-termination
 */
static void data_print(uint8_t *prefix, uint8_t *data, size_t len)
{
	char buf[len + 1];

	memcpy(buf, data, len);
	buf[len] = 0;
	LOG_INF("%s%s", log_strdup(prefix), log_strdup(buf));
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

    err = getaddrinfo(GCLOUD_HOSTNAME, NULL, &hints, &result);
    if (err) {
        LOG_ERR("ERROR: getaddrinfo failed [%d] %s", err, strerror(err));
        return;
    }

    addr = result;
    err = -ENOENT;

    /* Look for address of the broker. */
    while (addr != NULL) {
        /* IPv4 Address. */
        if (addr->ai_addrlen == sizeof(struct sockaddr_in)) {
            struct sockaddr_in *broker4 =
                ((struct sockaddr_in *)&mqtt_broker);

            broker4->sin_addr.s_addr =
                ((struct sockaddr_in *)addr->ai_addr)
                ->sin_addr.s_addr;
            broker4->sin_family = AF_INET;
            broker4->sin_port = htons(BROKER_PORT);
            
            LOG_DBG("IPv4 Address found 0x%08x",
                broker4->sin_addr.s_addr);
            break;
        } else {
            LOG_ERR("ai_addrlen = %u should be %u or %u",
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

static int make_jwt(char *buffer, size_t buffer_size) {

    int err;
    
    struct jwt_data jwt;
    jwt.sec_tag = GCLOUD_SEC_TAG;
    jwt.key = JWT_KEY_TYPE_CLIENT_PRIV;
    jwt.alg = JWT_ALG_TYPE_ES256;
    jwt.exp_delta_s = 12 * 60 * 60; //24 hours
    jwt.jwt_buf = buffer;
    jwt.jwt_sz = buffer_size;
    jwt.subject = NULL;
    jwt.audience = CONFIG_GCLOUD_PROJECT_NAME;

    err = modem_jwt_generate(&jwt);

    return err;
}

static int gcloud_subscribe() {
    const struct mqtt_subscription_list subscriptions = {
        .list = (struct mqtt_topic *)&gcloud_topics_list,
        .list_count = ARRAY_SIZE(gcloud_topics_list),
        .message_id = SUBSCRIBE_ID
    };

    return mqtt_subscribe(&client, &subscriptions);
}

static int client_init(void) {

    mqtt_client_init(&client);

    int err = make_jwt(jwt_buffer, JWT_BUFFER_SIZE);
    if (err != 0) {
        LOG_ERR("Unable to make jwt: [%d] %s", err, strerror(-err));
        return err;
    }

    LOG_DBG("JWT:\n%s\n", log_strdup(jwt_buffer));
    LOG_DBG("JWT length: %d\n", strlen(jwt_buffer));
    jwt_token.size = strlen(jwt_buffer);

    client.broker = &mqtt_broker;

    /* MQTT client configuration */
    client.evt_cb = mqtt_event_handler;
    client.client_id.utf8 = (uint8_t *)GCLOUD_ID;
    client.client_id.size = strlen(GCLOUD_ID);

	client.password = &jwt_token;
	client.user_name = &username;

    client.protocol_version = MQTT_VERSION_3_1_1;

	/* MQTT buffers configuration */
	client.rx_buf = rx_buffer;
	// client.rx_buf_size = sizeof(rx_buffer);
    client.rx_buf_size = 512;

	client.tx_buf = tx_buffer;
	// client.tx_buf_size = sizeof(tx_buffer);
    client.tx_buf_size = 1024;

    /* MQTT transport configuration */
	client.transport.type = MQTT_TRANSPORT_SECURE;

    /* Session */
    client.clean_session = 1;
    client.keepalive = 120;

    return 0;
}

int gcloud_connect(received_config_handler_t received_config_cb) {
    int err = 0;
    received_config_handler = received_config_cb;

    // send connect command
    struct gcloud_event msg = {
        .type = CONNECT
    };

    LOG_DBG("Sending connect command");
    err = k_msgq_put_atomic(&gcloud_msgq, &msg, DEFAULT_MSGQ_TIMEOUT);
    if(err) {
        LOG_ERR("Could not add connect command to queue: %d", err);
    }

    LOG_DBG("Waiting for connection");

    k_sem_take(&gc_connected_sem, DEFAULT_MSGQ_TIMEOUT);

    return err;
}

int gcloud_disconnect() {
    int err = 0;

    // send disconnect command
    struct gcloud_event msg = {
        .type = DISCONNECT
    };
    err = k_msgq_put_atomic(&gcloud_msgq, &msg, DEFAULT_MSGQ_TIMEOUT);

    return err;
}

// CANDO: Merge publish functions, and only have one publish command
// (the public API can still have two separate functions)
int gcloud_publish(uint8_t *data, uint32_t size, enum mqtt_qos qos)
{
    int err;
    if (!connected) {
        LOG_WRN("Cannot publish data while not connected to Google Cloud");
        return -ENOTCONN;
    }

    struct gcloud_event cmd = {
        .type = PUBLISH,
        .param.publish = {
            .topic = {
                .topic = {
                    .utf8 = GCLOUD_TOPIC,
                    .size = strlen(GCLOUD_TOPIC)
                },
                .qos = qos
            },
            .payload = {
                .data = data,
                .len = size
            }
        }
    };

    err = k_msgq_put_atomic(&gcloud_msgq, &cmd, DEFAULT_MSGQ_TIMEOUT);

    return err;
}

int gcloud_publish_state(uint8_t *data, uint32_t size, enum mqtt_qos qos)
{
    int err;
    if (!connected) {
        LOG_WRN("Cannot publish state while not connected to Google Cloud");
        return -ENOTCONN;
    }
    struct gcloud_event state_cmd = {
        .type = PUBLISH_STATE,
        .param.publish_state = {
            .topic = {
                .topic = {
                    .utf8 = GCLOUD_STATE_TOPIC,
                    .size = strlen(GCLOUD_STATE_TOPIC)
                },
                .qos = qos
            },
            .payload = {
                .data = data,
                .len = size
            }
        }
    };
    err = k_msgq_put_atomic(&gcloud_msgq, &state_cmd, DEFAULT_MSGQ_TIMEOUT);
    return err;
}

int k_msgq_get_atomic(struct k_msgq *q, void *data, k_timeout_t timeout){
    unsigned int key = irq_lock();
    int temp = k_msgq_get(q, data, timeout);
    irq_unlock(key);
    return temp;
}

int k_msgq_put_atomic(struct k_msgq *q, void *data, k_timeout_t timeout){
    unsigned int key = irq_lock();
    int temp = k_msgq_put(q,data, timeout);
    irq_unlock(key);
    return temp;
}

void reconnect_timer_handler(struct k_timer *timer_id) {
    struct gcloud_event cmd = {
        .type = RECONNECT_TIMEOUT,
        .param = {}
    };
    int err = k_msgq_put(&gcloud_msgq, &cmd, K_NO_WAIT);

    if (err) {
        LOG_ERR("k_msgq_put (reconnect_timeout) failed: [%d] %s", err, strerror(err));
        // TODO: Find a way to report this error to the application.
    }
}

static void config_tls(void) {
    /* Security configuration */
    static sec_tag_t sec_tag_list[] = {GCLOUD_SEC_TAG};
    tls_config = (client.transport).tls.config;

	tls_config.peer_verify = 0;
    tls_config.hostname = NULL;

	tls_config.cipher_list = NULL;

	tls_config.cipher_count = 0;
	tls_config.sec_tag_count = ARRAY_SIZE(sec_tag_list);
	tls_config.sec_tag_list = sec_tag_list;
	tls_config.hostname = GCLOUD_HOSTNAME;
}

static void mqtt_event_handler(struct mqtt_client *const cli,
                const struct mqtt_evt *evt)
{
    int err = 0;
    LOG_INF("MQTT event: %d", evt->type);

    switch (evt->type) {
        /* Response to connack request */
        case MQTT_EVT_CONNACK:
            LOG_DBG("Got CONNACK");
            if (evt->result != 0) {
                LOG_ERR("MQTT connect failed: [%d] %s", evt->result, strerror(evt->result));
                break;
            }

            k_sem_give(&gc_connected_sem);

            connected = true;
            connecting = false;
            k_timer_start(&reconnect_timer, GCLOUD_DISCONNECT_INTERVAL, GCLOUD_DISCONNECT_INTERVAL);

            #ifdef CONFIGURATION_SUBSCRIPTION
            struct gcloud_event cmd = {
                .type = SUBSCRIBE,
                .param.subscribe = {}
            };

            err = k_msgq_put_atomic(&gcloud_msgq, &cmd, DEFAULT_MSGQ_TIMEOUT);

            if (err) {
                LOG_ERR("k_msgq_put_atomic (subscribe) failed: [%d] %s", err, strerror(err));
                // TODO: Find a way to report this error to the application.
            }
            #endif

            break;

        /* Message has been published to a topic we subscribe to */
        case MQTT_EVT_PUBLISH:
            LOG_DBG("MQTT PUBLISH event");
            const struct mqtt_publish_param *p = &evt->param.publish;

            if (evt->result != 0) {
                LOG_ERR("Publish event error: [%d] %s", evt->result, strerror(-evt->result));
            }

            if (p->message.topic.qos == MQTT_QOS_1_AT_LEAST_ONCE) {
                const struct mqtt_puback_param ack = {
                    .message_id = p->message_id
                };

                /* Send ack */
                mqtt_publish_qos1_ack(&client, &ack);
                LOG_INF("Send acknowledgement for message with ID: %d", p->message_id);
            }

            if(p->message.payload.len <= 2) {
                LOG_WRN("Received empty payload");
                break;
            }

            mqtt_readall_publish_payload(&client, payload_buffer, p->message.payload.len);

            LOG_DBG("Length of payload: %d", p->message.payload.len);
            LOG_DBG("Topic: %s", log_strdup(p->message.topic.topic.utf8));
            LOG_DBG("QoS: %d", p->message.topic.qos);
            data_print("Received: ", payload_buffer,
				p->message.payload.len);
            
            if (received_config_handler != NULL) {
                received_config_handler(&p->message);
            }
            
            break;

        /* Dissconnect event. MQTT Client Reference is no longer valid. */
        case MQTT_EVT_DISCONNECT:
            LOG_DBG("MQTT client disconnected: [%d] %s", evt->result, strerror(-evt->result));
            k_timer_stop(&reconnect_timer);
            // If we are connected, something has gone wrong, and we would like to reconnect
            // CANDO: Notify the application that we are attempting a reconnect
            
            // Purge message queue to make sure that there are no old messages waiting
            k_msgq_purge(&gcloud_msgq);

            if (connected || connecting) {
                LOG_DBG("Reconnection");
                k_thread_abort(mqtt_tid);
                err = gcloud_connect(received_config_handler);
                if (err) {
                    LOG_ERR("k_msgq_put_atomic (reconnect) [%d] %s", err, strerror(err));
                    // TODO: Find a way to report this error to the application.
                }
            }
            break;

        /* Acknowledgement for QoS 1 messages */
        case MQTT_EVT_PUBACK:
            if (evt->result != 0) {
                LOG_ERR("MQTT PUBACK error: %d", evt->result);
                break;
            }

            LOG_DBG("PUBACK packet id: %d\n", evt->param.puback.message_id);

            break;

        /* Reception confirmation for messages with QoS 2 */
        case MQTT_EVT_PUBREC:
            if (evt->result != 0) {
                LOG_ERR("MQTT PUBREC error: %d", evt->result);
                break;
            }

            LOG_DBG("PUBREC packet id: %u", evt->param.pubrec.message_id);

            const struct mqtt_pubrel_param rel_param = {
                .message_id = evt->param.pubrec.message_id
            };

            err = mqtt_publish_qos2_release(&client, &rel_param);
            if (err != 0) {
                LOG_ERR("Failed to send MQTT PUBREL: [%d] %s", err, strerror(err));
            }

            break;

        /* Release of messages with QoS 2 */
        case MQTT_EVT_PUBREL:
            LOG_DBG("MQTT PUBREL event");
            if (evt->result != 0) {
                LOG_ERR("PUBREL error: %d", evt->result);
                break;
            }
            break;

        /* Confirmation to publish */
        case MQTT_EVT_PUBCOMP:
            if (evt->result != 0) {
                LOG_ERR("MQTT PUBCOMP error: %d", evt->result);
                break;
            }

            LOG_DBG("PUBCOMP packet id: %u", evt->param.pubcomp.message_id);

            break;

        /* Ack of a subscription request */
        case MQTT_EVT_SUBACK:
            LOG_DBG("Got SUBACK");
            if (evt->result != 0) {
                LOG_ERR("MQTT SUBACK error: %d", evt->result);
                break;
            }

            break;

        /* Ack of an unsubscribe request */
        case MQTT_EVT_UNSUBACK:
            LOG_DBG("MQTT UNSUBACK event");
            if (evt->result != 0) {
                LOG_ERR("MQTT UNSUBACK error: %d", evt->result);
                break;
            }

            break;
        
        default:
            LOG_ERR("Unknown mqtt event type");
            break;
    }
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

void mqtt_thread_func(void *unused1, void *unused2, void *unused3) {
    int err;

    while(1) {
            err = poll(&fds, 1, mqtt_keepalive_time_left(&client));
            if (err < 0) {
                LOG_ERR("poll: %d", errno);
                break;
            }

            err = mqtt_live(&client);
            if ((err != 0) && (err != -EAGAIN)) {
                LOG_ERR("ERROR: mqtt_live: %d", err);
                break;
            }

            if ((fds.revents & POLLIN) == POLLIN) {
                err = mqtt_input(&client);
                if (err != 0) {
                    LOG_ERR("mqtt_input: %d", err);
                    break;
                }
            }

            if ((fds.revents & POLLERR) == POLLERR) {
                LOG_ERR("POLLERR");
                break;
            }

            if ((fds.revents & POLLNVAL) == POLLNVAL) {
                LOG_ERR("POLLNVAL");
                break;
            }
        }
}

extern void gcloud_thread(void *unused1, void *unused2, void *unused3) 
{
    int err;
    bool sent_flag = false;

    struct gcloud_event event;
    struct mqtt_publish_param msg;

    k_timer_init(&reconnect_timer, reconnect_timer_handler, NULL);

    config_tls();

    LOG_INF("Google Cloud Thread Running\n");
    while (true) {
        
        k_msgq_get_atomic(&gcloud_msgq, &event, K_FOREVER);

        switch (event.type) {
            case CONNECT:
                LOG_INF("Got CONNECT command");
                LOG_DBG("Initiating broker");
                broker_init();

                //LOG_DBG("Making JWT");
                //make_jwt(jwt_buffer, JWT_BUFFER_SIZE);

                LOG_DBG("Initiating client");
                client_init();

                LOG_DBG("Connecting mqtt");
                connecting = true;
                err = mqtt_connect(&client);
                if (err) {
                    LOG_ERR("mqtt_connect failed: [%d] %s", err, strerror(-err));
                    // TODO: Find a way to report this error to the application.
                }
                err = fds_init(&client);
	            if (err != 0) {
	            	LOG_ERR("fds_init: [%d] %s", err, strerror(-err));
	            }

                /* Initialise MQTT thread */
                mqtt_tid = k_thread_create(&mqtt_thread, mqtt_stack_area, K_THREAD_STACK_SIZEOF(mqtt_stack_area),
                             (k_thread_entry_t)mqtt_thread_func, NULL, NULL, NULL,
                             7, 0, K_NO_WAIT);

                break;
            case PUBLISH_STATE:
            if (connected) {
                LOG_DBG("Got PUBLISH_STATE command");
                msg.message = event.param.publish_state;
                msg.message_id = k_uptime_get_32();
                msg.dup_flag = 0;
                msg.retain_flag = 0;
                err = mqtt_publish(&client, &msg);
                
                if (err) {
                    LOG_ERR("mqtt_publish (state) failed: [%d] %s", err, strerror(-err));
                    // TODO: Find a way to report this error to the application.
                }
            };
            break;
            // CANDO: Merge these publish cases?
            case PUBLISH:
            if (connected) {
                LOG_DBG("Got PUBLISH command");
                msg.message = event.param.publish;
                msg.message_id = k_uptime_get_32();
                msg.dup_flag = 0;
                msg.retain_flag = 0;
                err = mqtt_publish(&client, &msg);
                if (err) {
                    LOG_ERR("mqtt_publish failed: [%d] %s", err, strerror(-err));
                    // TODO: Find a way to report this error to the application.
                }
                sent_flag = true;
            };
            break;
            case RECONNECT_TIMEOUT:
                LOG_DBG("Got RECONNECT_TIMEOUT command");
            case DISCONNECT:
                LOG_DBG("Got DISCONNECT command");
            if (connected) {
                k_timer_stop(&reconnect_timer);
       
                /* purge message queue */
                //k_msgq_purge(&gcloud_msgq);
                connected = false;
                if (event.type == DISCONNECT) {
                    LOG_DBG("Not setting connecting flag");
                    connecting = false;
                } else {
                    LOG_DBG("Setting connecting flag");
                    connecting = true;
                }

                LOG_DBG("Disconnecting mqtt");
                err = mqtt_disconnect(&client);
                if (err) {
                    LOG_ERR("mqtt_disconnect (reconnect) failed: [%d] %s", err, strerror(-err));
                    // TODO: Find a way to report this error to the application.
                }
            };
            break;
            case SUBSCRIBE:
            if (connected) {
                LOG_DBG("Got SUBSCRIBE command");
                err = gcloud_subscribe();
                if (err) {
                    LOG_ERR("gcloud_subscribe failed: [%d] %s", err, strerror(-err));
                    // TODO: Find a way to report this error to the application.
                }
            };
            break;
            default:
                LOG_ERR("Unknown event type received");
                // TODO: Find a way to report this error to the application.
        }
        /* If a message has been sent */
        if (sent_flag == true) {
           sent_flag = false;
        }
    }
}