/*
 * hw_rscan_module.c
 *
 * the hw_rscan_module.c for root scanner kernel space init and deinit
 *
 * likun <quentin.lee@huawei.com>
 * likan <likan82@huawei.com>
 *
 * Copyright (c) 2001-2021, Huawei Tech. Co., Ltd. All rights reserved.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/types.h>
#include "./include/hw_rscan_utils.h"
#include "./include/hw_rscan_data_uploader.h"
#include "./include/hw_rscan_scanner.h"
#include "./include/hw_rscan_proc.h"

static int __init rscan_module_init(void);
static void __exit rscan_module_exit(void);
static const char *TAG = "hw_rscan_module";

static int __init rscan_module_init(void)
{
	int result = 0;

#ifndef RS_DEBUG
	if (RO_NORMAL != get_ro_secure()) {
		RSLogTrace(TAG, "in engneering mode, root scan stopped");
		return RSCAN_ERR_SECURE_MODE;
	}
#endif

	do {
		/* init uploader */
		result = rscan_uploader_init();
		if (result != 0)
			break;

		/* init dynamic scanner */
		result = rscan_dynamic_init();
		if (result != 0) {
			RSLogError(TAG, "dynamic scanner init failed: %d",
						result);
			break;
		}

		/* init proc file */
		result = rscan_proc_init();
		if (result != 0) {
			RSLogError(TAG, "rscan_proc_init init failed.");
			break;
		}
	} while (0);

	if (0 != result)
		rscan_module_exit();

	RSLogTrace(TAG, "+++root scan module init success");
	return result;
}

static void __exit rscan_module_exit(void)
{
	rscan_proc_deinit();
	rscan_uploader_deinit();
}

late_initcall(rscan_module_init);   /* lint -save -e528 */
module_exit(rscan_module_exit);   /* lint -save -e528 */

MODULE_AUTHOR("likun <quentin.lee@huawei.com>");
MODULE_DESCRIPTION("Huawei root scanner");
