/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/i2c.h>
#include <device.h>
#include <nrfx_twim.h>

void main(void)
{
	printk("The I2C scanner started\n");
    const struct device *i2c_dev;
	int error;

    i2c_dev = device_get_binding("I2C_2");
    if (!i2c_dev) {
        printk("Binding failed.");
        return;
    }
    i2c_configure(i2c_dev, I2C_SPEED_SET(I2C_SPEED_STANDARD));

    printk("Value of NRF_TWIM2_NS->PSEL.SCL : %d \n",NRF_TWIM2_NS->PSEL.SCL);
	printk("Value of NRF_TWIM2_NS->PSEL.SDA : %d \n",NRF_TWIM2_NS->PSEL.SDA);
	printk("Value of NRF_TWIM2_NS->FREQUENCY: %d \n",NRF_TWIM2_NS->FREQUENCY);
	printk("26738688 -> 100k\n");

	//printk("Maximum I2C chunck length: %d\n", TWIM0_LENGTH_VALIDATE(8210,500));

	uint8_t testbuf[8210];
	memset(testbuf, 0, 8210);
	error = i2c_write(i2c_dev,testbuf,8210, 0x7F);
	printk("Error: %d",error);

    // for (uint8_t i = 4; i <= 0x7F; i++) {
	// 	struct i2c_msg msgs[1];
	// 	uint8_t dst = 1;

	// 	msgs[0].buf = &dst;
	// 	msgs[0].len = 1U;
	// 	msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;
		
	// 	error = i2c_transfer(i2c_dev, &msgs[0], 1, i);
	// 	if (error == 0) {
	// 		printk("0x%2x FOUND\n", i);
	// 	}
	// 	else {
	// 		//printk("error %d \n", error);
	// 	}
		
	// }
}
