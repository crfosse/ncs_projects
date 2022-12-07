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

#define TEST_BUF_SIZE 128

void main(void)
{
    printk("The I2C scanner started\n");
    const struct device *i2c_dev;
    int error;

    i2c_dev = device_get_binding("I2C_1");
    if (!i2c_dev) {
        printk("Binding failed.");
        return;
    }

    /* Demonstration of runtime configuration */
    i2c_configure(i2c_dev, I2C_SPEED_SET(I2C_SPEED_STANDARD));
    printk("Value of NRF_TWIM2->PSEL.SCL : %d \n",NRF_TWIM1->PSEL.SCL);
    printk("Value of NRF_TWIM2->PSEL.SDA : %d \n",NRF_TWIM1->PSEL.SDA);
    printk("Value of NRF_TWIM2->FREQUENCY: %d \n",NRF_TWIM1->FREQUENCY);
    printk("26738688 -> 100k\n");

    for (uint8_t i = 4; i <= 0x7F; i++) {
        struct i2c_msg msgs[1];
        uint8_t dst = 1;

        msgs[0].buf = &dst;
        msgs[0].len = 1U;
        msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

        error = i2c_transfer(i2c_dev, &msgs[0], 1, i);
        if (error == 0) {
            printk("0x%2x FOUND\n", i);
        }
        else {
            //printk("error %d \n", error);
        }

    }
}
