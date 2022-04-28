/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <net/socket.h>
#include <nrf_modem_at.h>
#include <modem/lte_lc.h>
#include <logging/log.h>
#include <date_time.h>

LOG_MODULE_REGISTER(timestamp_demo, CONFIG_TIMESTAMP_DEMO_LOG_LEVEL);

/**@brief Recoverable modem library error. */
void nrf_modem_recoverable_error_handler(uint32_t err)
{
	LOG_ERR("Modem library recoverable error: %u", (unsigned int)err);
}

/**@brief Configures modem to provide LTE link. Blocks until link is
 * successfully established.
 */
static int modem_configure(void)
{
#if defined(CONFIG_LTE_LINK_CONTROL)
	/* Turn off LTE power saving features for a more responsive demo. Also,
	 * request power saving features before network registration. Some
	 * networks rejects timer updates after the device has registered to the
	 * LTE network.
	 */
	LOG_INF("Disabling PSM and eDRX");
	lte_lc_psm_req(false);
	lte_lc_edrx_req(false);

	if (IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT)) {
		/* Do nothing, modem is already turned on
		 * and connected.
		 */
	} else {
#if defined(CONFIG_LWM2M_CARRIER)
		/* Wait for the LWM2M_CARRIER to configure the modem and
		 * start the connection.
		 */
		LOG_INF("Waitng for carrier registration...");
		k_sem_take(&carrier_registered, K_FOREVER);
		LOG_INF("Registered!");
#else /* defined(CONFIG_LWM2M_CARRIER) */
		int err;

		LOG_INF("LTE Link Connecting...");
		err = lte_lc_init_and_connect();
		if (err) {
			LOG_INF("Failed to establish LTE connection: %d", err);
			return err;
		}
		LOG_INF("LTE Link Connected!");
#endif /* defined(CONFIG_LWM2M_CARRIER) */
	}
#endif /* defined(CONFIG_LTE_LINK_CONTROL) */

	return 0;
}

void main(void)
{
	int err;

	/* Connecting to network */
	do {
		err = modem_configure();
		if (err) {
			LOG_INF("Retrying in %d seconds",
				100);
			k_sleep(K_SECONDS(100));
		}
	} while (err);


	while(1) {

		//Get timestamp
		int64_t curr_time;
		date_time_now(&curr_time);

		int64_t curr_time_s = curr_time/1000;   			//Convert to seconds
		struct tm * readable_time = gmtime(&(curr_time_s)); //Get human readable time with time.h
		printk("Curr min: %d\n", readable_time->tm_min);
		printk("Curr sec: %d\n", readable_time->tm_sec);


		k_sleep(K_SECONDS(10));
	}
}
