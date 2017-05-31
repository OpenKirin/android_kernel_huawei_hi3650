/*
 * BFM for handling the boot fail exceptions during the entire process of system boot.
 *
 * Copyright (c) 2016 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 @brief: this is the public interface for definiation of type struct and common interface of BFM.
 */

#ifndef __BFM_PRINT_H__
#define __BFM_PRINT_H__
#include <linux/types.h>

#define BFM_PRINT_PN(args...)    printk(KERN_ERR args);
#define BFM_PRINT_ERR(args...)   printk(KERN_ERR args);
#define BFM_PRINT_DBG(args...)   printk(KERN_DEBUG args);
#define BFM_PRINT_START(args...) \
	printk(KERN_INFO ">>>>>enter bfm %s: %.4d.\n", __func__, __LINE__);
#define BFM_PRINT_END(args...)   \
	printk(KERN_INFO "<<<<<exit  bfm %s: %.4d.\n", __func__, __LINE__);

#endif