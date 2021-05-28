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
    if (IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT))
    {
        /* Do nothing, modem is already turned on and connected */
    }
    else
    {
        int err;

        //LOG_INF("Enabling PSM\n");
        /* Enable PSM mode */
        //lte_lc_psm_req(true);

        LOG_INF("Establishing LTE link\n");
        err = lte_lc_init_and_connect();
        __ASSERT(err == 0, "LTE link could not be established. Rebooting\n");
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

    cJSON_AddStringToObject(message, "type", "test message");

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

/**@brief Thread initialisation */
void main(void)
{
    int err;

    LOG_INF("Google Cloud env sensor app started");

    LOG_INF("Initializing modem\n");
    modem_configure();

    LOG_INF("Initializing modem info\n");
    modem_info_init();

    date_time_update_async(date_time_handler);
    k_sem_take(&date_time_ok, K_FOREVER);

    /* Initialise Google Cloud thread */
    gc_tid = k_thread_create(&gc_thread, gc_stack_area, K_THREAD_STACK_SIZEOF(gc_stack_area),
                             (k_thread_entry_t)gcloud_thread, NULL, NULL, NULL,
                             7, 0, K_NO_WAIT);


    err = gcloud_provision();
    if (err)
    {
        LOG_ERR("Provisioning failed, error: %d\n", err);
        /* Reboot */
        sys_reboot(0); //TODO: Handle error
    }

    /* Connect to Google Cloud */
    LOG_INF("Connecting to Google Cloud\n");
    err = gcloud_connect(received_config_handler);
    if (err)
    {
        LOG_ERR("Failed to connect to Google Cloud, error: %d\n", err);
        /* Reboot */
        sys_reboot(0); //TODO: Handle error
    }
    else
    {
        LOG_INF("Connected to Google Cloud\n");
    }
    
    int pub_success;
    uint32_t cnt = 0;

    while (true)
    {
        //Get timestamp
	    int64_t curr_time;
	    date_time_now(&curr_time);

        struct app_message message;
        create_message(&message, "x", sizeof("x"), &curr_time);

        pub_success = gcloud_publish(message.data, message.len, MQTT_QOS_1_AT_LEAST_ONCE);
        if (pub_success != 0)
        {
            LOG_INF("JSON data Publish failed\n");
        }
        
        cnt++;
        k_sleep(K_SECONDS(10));
    }
}