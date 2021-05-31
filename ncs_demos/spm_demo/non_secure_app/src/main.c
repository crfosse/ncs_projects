/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

int spm_read_ficr(void *destination);

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);

	int32_t HW_ID;

	spm_read_ficr(&HW_ID);
	printk("HW_ID : %d \n", HW_ID);
		
}
