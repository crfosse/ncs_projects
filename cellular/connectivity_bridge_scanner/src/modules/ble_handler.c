/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr.h>
#include <zephyr/types.h>
#include <sys/ring_buffer.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/hci.h>
#include <bluetooth/gatt_dm.h>
#include <bluetooth/scan.h>

#define MODULE ble_handler
#include "module_state_event.h"
#include "peer_conn_event.h"
#include "ble_ctrl_event.h"
#include "ble_data_event.h"
#include "uart_data_event.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(MODULE, CONFIG_BRIDGE_BLE_LOG_LEVEL);

#define BT_ADDR  "06:09:16"

#define BLE_RX_BLOCK_SIZE (CONFIG_BT_L2CAP_TX_MTU - 3)
#define BLE_RX_BUF_COUNT 4
#define BLE_SLAB_ALIGNMENT 4

#define ADV_BUF_SIZE 128

K_MEM_SLAB_DEFINE(ble_rx_slab, BLE_RX_BLOCK_SIZE, BLE_RX_BUF_COUNT, BLE_SLAB_ALIGNMENT);

static atomic_t ready;
static atomic_t active;

bool bt_parse_cb(struct bt_data *data, void *user_data) {

	int err;
	void *buffer;


	LOG_INF("Parsed adv -- Type: %d", data->type);
	switch (data->type) {

		BT_DATA_NAME_COMPLETE:

			memcpy(buffer, data->data, data->data_len);
			LOG_INF("Got data from device: %s ", log_strdup(buffer));

			break;

		BT_DATA_MANUFACTURER_DATA:


				err = k_mem_slab_alloc(&adv_data_slab, &buf, K_NO_WAIT);
				if (err) {
					LOG_WRN("BLE RX overflow");
					break;
				}

				struct ble_data_event *event = new_ble_data_event();
				memcpy(event->buf,data->data);
				event->len = data->data_len;
				EVENT_SUBMIT(event);

			return false;

			break;

		default:
			break;
	}

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
		module_set_state(MODULE_STATE_STANDBY);
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

	//err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_UUID, BT_UUID_THINGY);
	//if (err) {
	//	LOG_ERR("UUID scanning filters cannot be set");
	//	return;
	//}
	
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

	atomic_set(&ready, true);

#if CONFIG_BRIDGE_BLE_ALWAYS_ON
	atomic_set(&active, true);
#endif

	if (atomic_get(&active)) {
		scan_start();
	}
}

static bool event_handler(const struct event_header *eh)
{
	if (is_uart_data_event(eh)) {
		
		#ifdef OG_CODE
		const struct uart_data_event *event =
			cast_uart_data_event(eh);

		/* Only one BLE Service instance, mapped to UART_0 */
		if (event->dev_idx != 0) {
			return false;
		}

		if (current_conn == NULL) {
			return false;
		}

		uint32_t written = ring_buf_put(
			&ble_tx_ring_buf,
			event->buf,
			event->len);
		if (written != event->len) {
			LOG_WRN("UART_%d -> BLE overflow", event->dev_idx);
		}

		uint32_t buf_utilization =
			(ring_buf_capacity_get(&ble_tx_ring_buf) -
			ring_buf_space_get(&ble_tx_ring_buf));

		/* Simple check to start transmission. */
		/* If bt_send_work is already running, this has no effect */
		if (buf_utilization == written) {
			k_work_submit(&bt_send_work);
		}

		#endif

		return false;
	}

	if (is_ble_data_event(eh)) {
		
		LOG_INF("BLE_DATA_EVENT");
		const struct ble_data_event *event =
			cast_ble_data_event(eh);
		/* All subscribers have gotten a chance to copy data at this point */
		k_mem_slab_free(&ble_rx_slab, (void **) &event->buf);
		return false;
	}

	if (is_ble_ctrl_event(eh)) {
		const struct ble_ctrl_event *event =
			cast_ble_ctrl_event(eh);

		switch (event->cmd) {
		case BLE_CTRL_ENABLE:
			LOG_INF("BLE_CTRL_ENABLE");
			if (!atomic_set(&active, true)) {
				scan_start();
			}
			break;
		case BLE_CTRL_DISABLE:
			LOG_INF("BLE_CTRL_DISABLE");
			if (atomic_set(&active, false)) {
				scan_stop();
			}
			break;
		case BLE_CTRL_NAME_UPDATE:
			LOG_INF("BLE_CTRL_NAME_UPDATE");
			break;
		default:
			/* Unhandled control message */
			__ASSERT_NO_MSG(false);
			break;
		}

		return false;
	}

	if (is_module_state_event(eh)) {
		const struct module_state_event *event =
			cast_module_state_event(eh);

		if (check_state(event, MODULE_ID(main), MODULE_STATE_READY)) {
			int err;

			atomic_set(&active, false);

			err = bt_enable(bt_ready);
			if (err) {
				LOG_ERR("bt_enable: %d", err);
				return false;
			}
			
			LOG_INF("BT enabled");
		}

		return false;
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

EVENT_LISTENER(MODULE, event_handler);
EVENT_SUBSCRIBE(MODULE, module_state_event);
EVENT_SUBSCRIBE(MODULE, ble_ctrl_event);
EVENT_SUBSCRIBE(MODULE, uart_data_event);
EVENT_SUBSCRIBE_FINAL(MODULE, ble_data_event);