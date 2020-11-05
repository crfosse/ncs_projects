/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <stdio.h>

#ifdef CONFIG_MCUMGR_CMD_OS_MGMT
#include "os_mgmt/os_mgmt.h"
#endif
#ifdef CONFIG_MCUMGR_CMD_IMG_MGMT
#include "img_mgmt/img_mgmt.h"
#endif

void main(void)
{
	#ifdef CONFIG_MCUMGR_CMD_OS_MGMT
		os_mgmt_register_group();
	#endif
	#ifdef CONFIG_MCUMGR_CMD_IMG_MGMT
		img_mgmt_register_group();
	#endif

	printk("Hello World -test! %s\n", CONFIG_BOARD);
}
