/*
 * Copyright (c) 2020 Safecility.com
 * Author: tad@safecility.com
 */

#include <zephyr.h>
#include <device.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <power/reboot.h>

#include <nrf_modem.h>
#include <modem/lte_lc.h>
#include <modem/modem_info.h>

#include <nrf_socket.h>
#include <net/socket.h>
#include <net/mqtt.h>

#include <date_time.h>
#include <gcloud.h>
#include <cJSON.h>

//#define WITH_BLE

#ifdef WITH_BLE

#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/hci.h>
#include <bluetooth/gatt_dm.h>
#include <bluetooth/scan.h>

#endif

static K_SEM_DEFINE(connected_to_cloud, 0, 1);
static K_SEM_DEFINE(ble_ready, 0, 1);


/* Size of buffer determines update rate */
#define MAX_MESSAGE_SIZE 256

struct app_message {
	char data[MAX_MESSAGE_SIZE];
	size_t len;
};

/* Register main module log */
LOG_MODULE_REGISTER(google_mqtt, CONFIG_GCLOUD_LOG_LEVEL);

/* Stack definition for application */
static K_THREAD_STACK_DEFINE(gc_stack_area, 4096);

/* Threads */
static struct k_thread gc_thread;

k_tid_t gc_tid;

struct m_info_t
{
    char cid[30];
    char tac[30];
    char rssi[30];
    char apn[60];
    char fwv[60];
    uint16_t vltg;
    uint16_t temp;
};

/* Semaphores */
static K_SEM_DEFINE(date_time_ok, 0, 1);

/* Global Variables */

/* Forward declarations of functions */
static void store_modem_configuration(void);
static void scan_stop(void);

/* Handlers */
void button_handler(uint32_t button_state, uint32_t has_changed)
{
    LOG_INF("Button event: %x  %x\n", button_state, has_changed);
    if ((has_changed & 0x01) && (button_state & 0x01))
    {
        store_modem_configuration();
    }
}

/**@brief Handler for when receiving data from Google Cloud */
void received_config_handler(const struct mqtt_publish_message *message)
{

    cJSON *data_json = cJSON_Parse(message->payload.data);
    cJSON_Delete(data_json);
}

/**@brief Configures modem to provide LTE link. Blocks until link is
 * successfully established
 */
static void modem_configure(void)
{
	/* Turn off LTE power saving features for a more responsive demo. Also,
	 * request power saving features before network registration. Some
	 * networks rejects timer updates after the device has registered to the
	 * LTE network.
	 */
	LOG_INF("Disabling PSM and eDRX");
	lte_lc_psm_req(false);
	lte_lc_edrx_req(false);

    if (IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT))
    {
        /* Do nothing, modem is already turned on and connected */
    }
    else
    {
        int err;

        LOG_INF("Establishing LTE link\n");
        err = lte_lc_init_and_connect();
        if (err) {
			LOG_INF("Failed to establish LTE connection: %d", err);
		}
    }
}

/**@brief Soft boots modem to store current values to NVM */
void store_modem_configuration(void)
{
    int err;

    LOG_INF("Storing modem configuration\n");
    err = lte_lc_power_off();
    if (err)
    {
        LOG_INF("Fail turning off modem: %d\n", err);
    }
    LOG_INF("Modem offline, turning back on\n");

    err = lte_lc_normal();
    if (err)
    {
        LOG_INF("Fail turning on modem: %d\n", err);
    }
    LOG_INF("Done\n");
}

/**@brief Return modem information */
void get_modem_info(struct m_info_t *info)
{
    LOG_INF("Getting modem info\n");
    modem_info_string_get(MODEM_INFO_CELLID, info->cid, sizeof(info->cid));
    modem_info_string_get(MODEM_INFO_AREA_CODE, info->tac, sizeof(info->tac));
    modem_info_string_get(MODEM_INFO_RSRP, info->rssi, sizeof(info->rssi));
    modem_info_string_get(MODEM_INFO_APN, info->apn, sizeof(info->apn));
    modem_info_string_get(MODEM_INFO_FW_VERSION, info->fwv, sizeof(info->fwv));
    modem_info_short_get(MODEM_INFO_BATTERY, &info->vltg);
    modem_info_short_get(MODEM_INFO_TEMP, &info->temp);
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

void create_message(struct app_message* destination, uint8_t *data, size_t len, int64_t *timestamp) {

	cJSON *message;

	message = cJSON_CreateObject();

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

#ifdef WITH_BLE

#define BT_ADDR  "06:09:16"

#define ADV_BUF_SIZE 128

bool bt_parse_cb(struct bt_data *data, void *user_data) {

	LOG_INF("Parsed adv -- Type: %d", data->type);

	return true;
}

void scan_filter_match(struct bt_scan_device_info *device_info,
		       struct bt_scan_filter_match *filter_match,
		       bool connectable)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(device_info->recv_info->addr, addr, sizeof(addr));

	int ret = !strncmp(BT_ADDR, addr, 9);

	if(!ret) {
		LOG_INF("Device found: %s", log_strdup(addr));

		bt_data_parse(device_info->adv_data, bt_parse_cb, (void *)addr);

		/** Demonstration of data transmission **/
		//Should check for connection before publishing

		int pub_success;
			
		//Get timestamp
		int64_t curr_time;
		date_time_now(&curr_time);

		struct app_message message;
		create_message(&message, addr, sizeof(addr), &curr_time);

		pub_success = gcloud_publish(message.data, message.len, MQTT_QOS_1_AT_LEAST_ONCE);
		if (pub_success != 0)
		{
			LOG_INF("JSON data Publish failed\n");
			scan_stop();
		}
		/** Demonstration end **/

	} else {
		LOG_INF("Not a relevant address: %d", ret);
	}
}

void scan_connecting_error(struct bt_scan_device_info *device_info)
{
	LOG_ERR("Connection to peer failed!");
}

bool bt_parse_cb_nomatch(struct bt_data *data, void *user_data) {

	//LOG_INF("Device found: %s", log_strdup(user_data));

	char buffer[ADV_BUF_SIZE];

	switch(data->type) 
	{
		case BT_DATA_NAME_COMPLETE:

			memcpy(buffer, data->data, data->data_len);
			if(!strncmp("47:05:9B",buffer,data->data_len)) {
				char addr_str_le[BT_ADDR_LE_STR_LEN];
				bt_addr_le_to_str(user_data, addr_str_le, BT_ADDR_LE_STR_LEN);
				LOG_INF("Got LE address: %s ", log_strdup(addr_str_le));
			}

			break;

		default:
			//nothing here
			break;
	}

	return true;
}

void scan_filter_no_match(struct bt_scan_device_info *device_info,bool connectable) {

	
	bt_data_parse(device_info->adv_data, bt_parse_cb_nomatch, (void *)device_info->recv_info->addr);

}

BT_SCAN_CB_INIT(scan_cb, scan_filter_match, scan_filter_no_match, scan_connecting_error, NULL);

static void scan_stop(void)
{
	int err;

	LOG_INF("Stopping scan");

	err = bt_le_scan_stop();
	if (err) {
		LOG_ERR("bt_le_scan_stop: %d", err);
	} else {
		LOG_INF("STANDBY");
	}
}

static void scan_start(void)
{
	int err;

	struct bt_le_scan_param scan_param = {
		.type = BT_LE_SCAN_TYPE_ACTIVE,
		.options = BT_LE_SCAN_OPT_NONE,
		.interval = 0x0010,
		.window = 0x0010,
	};

	struct bt_scan_init_param scan_init = {
		.connect_if_match = 0,
		.scan_param = &scan_param,
		.conn_param = NULL,
	};

	bt_scan_init(&scan_init);
	bt_scan_cb_register(&scan_cb);

	static const uint16_t manufacturer_id = 0x028d;
    struct bt_scan_manufacturer_data id_filter;
    id_filter.data = (uint8_t*) &manufacturer_id;
    id_filter.data_len = 2;

	err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_MANUFACTURER_DATA, &id_filter);
	if (err) {
		LOG_ERR("MANUFACTURER scanning filters cannot be set");
		return;
	}

	err = bt_scan_filter_enable(BT_SCAN_MANUFACTURER_DATA_FILTER, false);
	if (err) {
		LOG_ERR("Filters cannot be turned on");
	}

	err = bt_scan_start(BT_SCAN_TYPE_SCAN_ACTIVE);
	if (err) {
		LOG_ERR("Scanning failed to start, err %d", err);
	}


	LOG_INF("Scanning...");
}

static void bt_ready(int err)
{
	if (err) {
		LOG_ERR("%s: %d", __func__, err);
		return;
	}

	k_sem_give(&ble_ready);

	//Wait for cloud connection
    k_sem_take(&connected_to_cloud, K_FOREVER);
	scan_start();
}

#endif

/**@brief Thread initialisation */
void main(void)
{
    int err;

    LOG_INF("Google Cloud BLE app started");

    #ifdef WITH_BLE
		err = bt_enable(bt_ready);
		if (err) {
			LOG_ERR("bt_enable: %d", err);
		}

	k_sem_take(&ble_ready, K_FOREVER);
	#endif

    LOG_INF("Initializing modem");
    modem_configure();

    LOG_INF("Initializing modem info");
    modem_info_init();

    date_time_update_async(date_time_handler);
    k_sem_take(&date_time_ok, K_FOREVER);

    /* Initialise Google Cloud thread */
    gc_tid = k_thread_create(&gc_thread, gc_stack_area, K_THREAD_STACK_SIZEOF(gc_stack_area),
                             (k_thread_entry_t)gcloud_thread, NULL, NULL, NULL,
                             7, 0, K_NO_WAIT);



    /* Connect to Google Cloud */
    LOG_INF("Connecting to Google Cloud");
    //err = gcloud_connect(received_config_handler);
    err = gcloud_connect(NULL);
    if (err)
    {
        LOG_ERR("Failed to connect to Google Cloud, error: %d", err);
        /* Reboot */
        sys_reboot(0); //TODO: Handle error
    }
    else
    {
        LOG_INF("Connected to Google Cloud");
	    k_sem_give(&connected_to_cloud);
    }
}