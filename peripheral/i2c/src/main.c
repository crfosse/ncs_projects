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

/**@brief Recoverable BSD library error. */
void bsd_recoverable_error_handler(uint32_t err)
{
	printk("bsdlib recoverable error: %u\n", err);
}

#define MAX_CHUNKS 2
#define CHUNK_SIZE 10



/*"WBUNPGprMSh0o1ZOTpGzC788DMB0OoQytSTDmKo7zeybWdx1DGh3SX"
			   "IpfkYHSkX3hQuEUdWC8jWBq6qRAzv4NB79aECZwwUsReylQcJOzZ4NW1rY3xbyya"
			   "ep9DOEWnRsWkjILrSh4crLHlfvmqVLxRjA1dDvHx72JVD4rvhhLbcQ6Gi94lvVF7"
			   "0KmnO4Lh7IRGUm37TVXzQXtRnb228WPngoCC5Ge4GZNmBRFhXWtgeuU9Vt2JJbID"
			   "jvdEpZVL88RszUn7Ah4pnTC7rkHRft6apfuZCUqo0udcvNbEaUFncwjsU8zkw8j7"
			   "mfiD7QxF2A9Kv7XTztxef2Ryj1MbWe0vDAPXUz3yb4AqfgcxPb3TCocDCgAd2F2S"
			   "xlAZ69913oxzD0M24Sl0YIztsCnTuUrzrgIOrdXWvjOcEcuEJltiIZMygVx8gxwc"
			   "pwY4YNybojiLfuRET4w91tbTgn33IvFcY8J7tu5Y8LZjk5ZfkekJg5zhZs6Bo2Jm"
			   "N0mC7eCqYvSBGm4No2TPbLjYD2fB5ERubVuo2rGeZjbnWEx8jcP9jgq049pEjjS9"
			   "MRXvJnDtpo8hIZcZpz1HKyXbOXbz60baSbpW5RHOhwg1TBh8wrBTOOORMMCBhl4O"
			   "QApYjcf2w4ZlbyfWUjQY6gkGR21599Wb1IjraQL911QeFjiRFGtcDEpxo5GMWL1O"
			   "ZKM4Gnkp4LP0A0yK9FlHeopsaCOBxOI0dTaq2gWDD8rRRCbYykck0J5IZfQnrBbv"
               "AH1MSzQuBq5BLjPC6KhWj519pymLg11fSvhgWlOnhfuSNlmqq9pysYmZIPUNKGOP"
			   "9gfpEKm8tCuvpUWZvoFsrmxfYQNe9vUznG0PZMhHDSc5C6wDBpFqDBhHEHRdg0KR"
			   "Df8CU5RsaaviBtI8yFb0plaRQjzTYg2xZcppX4NANeqB0udVdEdfhIxX6iVXcEb5"
			   "lGY0a35dDRjCgL7ePgZn7oQbLuusUurDbprEu2m"; */



void main(void)
{
	printk("The I2C test started\n");
    struct device *i2c_dev;
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
        
    for (uint8_t i = 4; i <= 0xFF; i++) {
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

    struct i2c_msg messages[MAX_CHUNKS]; //An array for the messages
    int chunk_number = 0;

    uint8_t * chunk = "yK3vQHgUQ1";

    /*
    //Handling normal chunks
    while(chunk_number < MAX_CHUNKS-1) {
        messages[chunk_number].buf =   (uint8_t *)chunk;
        messages[chunk_number].len =   CHUNK_SIZE;
        messages[chunk_number].flags = I2C_MSG_WRITE; //Adding only the write flag

        chunk_number++;
    }
    */
   /*
    //Final chunk
    messages[chunk_number].buf = chunk;
    messages[chunk_number].len = CHUNK_SIZE;
    messages[chunk_number].flags = I2C_MSG_WRITE | I2C_MSG_STOP; //Adding the stop conditiond
    
    printk("Size: %d\n", sizeof(messages));

    int err;
    int i2c_addr = 0x50;
    // Transfer the array of messages.
    //err = i2c_transfer(dev, messages, 1, I2C_TEST_ADDR);
    err = i2c_transfer(i2c_dev, &messages[0], 1, i2c_addr);
    if(err) {
        printk("Transfer failed: %d\n", err);
    }
    */
}
