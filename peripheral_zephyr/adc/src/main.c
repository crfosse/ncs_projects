/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <net/socket.h>
#include <stdio.h>
#include <string.h>
#include <drivers/adc.h>
#include <zephyr.h>

const struct device *adc_dev;

#include <hal/nrf_saadc.h>
#define ADC_DEVICE_NAME DT_ADC_0_NAME
#define ADC_RESOLUTION 10
#define ADC_GAIN ADC_GAIN_1_6
#define ADC_REFERENCE ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10)
#define ADC_1ST_CHANNEL_ID 0
#define ADC_1ST_CHANNEL_INPUT NRF_SAADC_INPUT_AIN0
#define ADC_2ND_CHANNEL_ID 2
#define ADC_2ND_CHANNEL_INPUT NRF_SAADC_INPUT_AIN2

static const struct adc_channel_cfg m_1st_channel_cfg = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_1ST_CHANNEL_ID,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive = ADC_1ST_CHANNEL_INPUT,
#endif
};

#define BUFFER_SIZE 8
static int16_t m_sample_buffer[BUFFER_SIZE];

const struct adc_sequence_options sequence_opts = {
	.interval_us = 0,
	.callback = NULL,
	.user_data = NULL,
	.extra_samplings = 7,
};

static int adc_sample(void)
{
	int ret;

	const struct adc_sequence sequence = {
		.options = &sequence_opts,
		.channels = BIT(ADC_1ST_CHANNEL_ID),
		.buffer = m_sample_buffer,
		.buffer_size = sizeof(m_sample_buffer),
		.resolution = ADC_RESOLUTION,
	};

	if (!adc_dev) {
		return -1;
	}

	ret = adc_read(adc_dev, &sequence);
	printk("ADC read err: %d\n", ret);

	/* Print the AIN0 values */
	printk("ADC raw value: ");
	for (int i = 0; i < BUFFER_SIZE; i++) {
		printk("%d ", m_sample_buffer[i]);
	}
	
	printf("\n Measured voltage: ");
	for (int i = 0; i < BUFFER_SIZE; i++) {
		float adc_voltage = 0;
		adc_voltage = (float)(((float)m_sample_buffer[i] / 1023.0f) *
				      3600.0f);
		printk("%f ",adc_voltage);
	}
	printk("\n");


	return ret;
}

int main(void)
{
	int err;

	printk("nRF53 SAADC sampling AIN0 (P0.13)\n");

	adc_dev = device_get_binding("ADC_0");
	if (!adc_dev) {
		printk("device_get_binding ADC_0 failed\n");
	}
	err = adc_channel_setup(adc_dev, &m_1st_channel_cfg);
	if (err) {
		printk("Error in adc setup: %d\n", err);
	}

	/* Trigger offset calibration
	 * As this generates a _DONE and _RESULT event
	 * the first result will be incorrect.
	 */
	NRF_SAADC_S->TASKS_CALIBRATEOFFSET = 1;
	while (1) {
		err = adc_sample();
		if (err) {
			printk("Error in adc sampling: %d\n", err);
		}
		k_sleep(K_MSEC(500));
	}
}
