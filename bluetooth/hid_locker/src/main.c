/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <string.h>
#include <random/rand32.h>
#include <stdio.h>

#include <usb/usb_device.h>
#include <usb/class/usb_hid.h>
#include <usb/class/usb_cdc.h>

#include <dk_buttons_and_leds.h>

#include "ble.h"
#include "event_thingy_btn.h"

#define LOG_LEVEL LOG_LEVEL_DBG
LOG_MODULE_REGISTER(main);

#define FLAGS_OR_ZERO(node)						\
	COND_CODE_1(DT_PHA_HAS_CELL(node, gpios, flags),		\
		    (DT_GPIO_FLAGS(node, gpios)),			\
		    (0))

#define SW0_NODE DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define PORT0		DT_GPIO_LABEL(SW0_NODE, gpios)
#define PIN0		DT_GPIO_PIN(SW0_NODE, gpios)
#define PIN0_FLAGS	FLAGS_OR_ZERO(SW0_NODE)
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define PORT0		""
#define PIN0		0
#define PIN0_FLAGS	0
#endif

K_FIFO_DEFINE(evt_fifo);

enum evt_t {
	GPIO_BUTTON_0	= 0x00,
	BLE_BTN			= 0x01,
	HID_KBD_CLEAR	= 0x0B,
};

struct app_evt_t {
	sys_snode_t node;
	struct k_mem_block block;
	enum evt_t event_type;
};

#define FIFO_ELEM_MIN_SZ        sizeof(struct app_evt_t)
#define FIFO_ELEM_MAX_SZ        sizeof(struct app_evt_t)
#define FIFO_ELEM_COUNT         255
#define FIFO_ELEM_ALIGN         sizeof(unsigned int)

K_MEM_POOL_DEFINE(event_elem_pool, FIFO_ELEM_MIN_SZ, FIFO_ELEM_MAX_SZ,
		  FIFO_ELEM_COUNT, FIFO_ELEM_ALIGN);

static inline void app_evt_free(struct app_evt_t *ev)
{
	k_mem_pool_free(&ev->block);
}

static inline void app_evt_put(struct app_evt_t *ev)
{
	k_fifo_put(&evt_fifo, ev);
}

static inline struct app_evt_t *app_evt_get(void)
{
	return k_fifo_get(&evt_fifo, K_NO_WAIT);
}

static inline void app_evt_flush(void)
{
	struct app_evt_t *ev;

	do {
		ev = app_evt_get();
		if (ev) {
			app_evt_free(ev);
		}
	} while (ev != NULL);
}

static inline struct app_evt_t *app_evt_alloc(void)
{
	int ret;
	struct app_evt_t *ev;
	struct k_mem_block block;

	ret = k_mem_pool_alloc(&event_elem_pool, &block,
			       sizeof(struct app_evt_t),
			       K_NO_WAIT);
	if (ret < 0) {
		LOG_ERR("APP event allocation failed!");
		app_evt_flush();

		ret = k_mem_pool_alloc(&event_elem_pool, &block,
				       sizeof(struct app_evt_t),
				       K_NO_WAIT);
		if (ret < 0) {
			LOG_ERR("APP event memory corrupted.");
			__ASSERT_NO_MSG(0);
			return NULL;
		}
		return NULL;
	}

	ev = (struct app_evt_t *)block.data;
	ev->block = block;

	return ev;
}

/* HID */
static const u8_t hid_kbd_report_desc[] = HID_KEYBOARD_REPORT_DESC();

static K_SEM_DEFINE(evt_sem, 0, 1);	/* starts off "not available" */
static K_SEM_DEFINE(usb_sem, 1, 1);	/* starts off "available" */
static struct gpio_callback callback[4];

static void in_ready_cb(void)
{
	k_sem_give(&usb_sem);
}

static const struct hid_ops ops = {
	.int_in_ready = in_ready_cb,
};

static void clear_kbd_report(void)
{
	struct app_evt_t *new_evt = app_evt_alloc();

	new_evt->event_type = HID_KBD_CLEAR;
	app_evt_put(new_evt);
	k_sem_give(&evt_sem);
}

/* Devices */
static void btn0(struct device *gpio, struct gpio_callback *cb, u32_t pins)
{
	struct app_evt_t *ev = app_evt_alloc();

	ev->event_type = GPIO_BUTTON_0,
	app_evt_put(ev);
	k_sem_give(&evt_sem);
}

int callbacks_configure(struct device *gpio, u32_t pin, int flags,
			void (*handler)(struct device*, struct gpio_callback*,
			u32_t), struct gpio_callback *callback)
{
	if (!gpio) {
		LOG_ERR("Could not find PORT");
		return -ENXIO;
	}

	gpio_pin_configure(gpio, pin,
			   GPIO_INPUT | GPIO_INT_DEBOUNCE | flags);

	gpio_init_callback(callback, handler, BIT(pin));
	gpio_add_callback(gpio, callback);
	gpio_pin_interrupt_configure(gpio, pin, GPIO_INT_EDGE_TO_ACTIVE);

	return 0;
}

static void status_cb(enum usb_dc_status_code status, const u8_t *param)
{
	LOG_INF("Status %d", status);
}

static bool ble_event_handler(const struct event_header *eh)
{
        if (is_event_thingy_btn(eh)) {

                /* Accessing event data. */
                struct event_thingy_btn *event = cast_event_thingy_btn(eh);

                int8_t v1 = event->btn_val;

                /* Actions when received given event type. */
                printk("Btn val: %x\n", v1);
				if(v1 > 0) {
					struct app_evt_t *ev = app_evt_alloc();

					printk("Post event to FIFO\n");

					ev->event_type = BLE_BTN,
					app_evt_put(ev);
					k_sem_give(&evt_sem);
				}

                return false;
        }

        return false;
}

EVENT_LISTENER(ble, ble_event_handler);
EVENT_SUBSCRIBE(ble, event_thingy_btn);

void main(void)
{
	int ret;

	event_manager_init();
    ble_init();

	struct device *hid0_dev;
	struct app_evt_t *ev;

	/* Configure devices */

	hid0_dev = device_get_binding("HID_0");
	if (hid0_dev == NULL) {
		LOG_ERR("Cannot get USB HID 0 Device");
		return;
	}

	if (callbacks_configure(device_get_binding(PORT0), PIN0, PIN0_FLAGS,
				&btn0, &callback[0])) {
		LOG_ERR("Failed configuring button 0 callback.");
		return;
	}

	/* Initialize HID */
	usb_hid_register_device(hid0_dev, hid_kbd_report_desc,
				sizeof(hid_kbd_report_desc), &ops);

	usb_hid_init(hid0_dev);

	ret = usb_enable(status_cb);
	if (ret != 0) {
		LOG_ERR("Failed to enable USB");
		return;
	}

	/* Wait 1 sec for the host to do all settings */
	k_busy_wait(USEC_PER_SEC);

	while (true) {
		k_sem_take(&evt_sem, K_FOREVER);

		while ((ev = app_evt_get()) != NULL) {
			switch (ev->event_type) {
			case GPIO_BUTTON_0:
			{
				printk("GPIO btn lock.\n");
				/* LOCK */
				u8_t lock_rep[] = {HID_KBD_MODIFIER_RIGHT_UI, 0x00, 0x00, 0x00,
					      0x00, 0x00, 0x00, HID_KEY_L};

				k_sem_take(&usb_sem, K_FOREVER);
				hid_int_ep_write(hid0_dev, lock_rep,
						 sizeof(lock_rep), NULL);
				clear_kbd_report();
				break;
			}
			case BLE_BTN:
			{
				printk("BLE btn lock.\n");
				/* LOCK */
				u8_t lock_rep[] = {HID_KBD_MODIFIER_RIGHT_UI, 0x00, 0x00, 0x00,
					      0x00, 0x00, 0x00, HID_KEY_L};

				k_sem_take(&usb_sem, K_FOREVER);
				hid_int_ep_write(hid0_dev, lock_rep,
						 sizeof(lock_rep), NULL);
				clear_kbd_report();
				break;
			}
			case HID_KBD_CLEAR:
			{
				/* Clear kbd report */
				u8_t rep[] = {0x00, 0x00, 0x00, 0x00,
					      0x00, 0x00, 0x00, 0x00};

				k_sem_take(&usb_sem, K_FOREVER);
				hid_int_ep_write(hid0_dev, rep,
						 sizeof(rep), NULL);
				break;
			}
			default:
			{
				LOG_ERR("Unknown event to execute");
				break;
			}
			break;
			}
			app_evt_free(ev);
		}
	}
}
