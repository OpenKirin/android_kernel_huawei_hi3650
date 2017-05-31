/*
 * sescan.h
 *
 * the sescan.h for selinux status checking
 *
 * Yongzheng Wu <Wu.Yongzheng@huawei.com>
 * likun <quentin.lee@huawei.com>
 * likan <likan82@huawei.com>
 *
 * Copyright (c) 2001-2021, Huawei Tech. Co., Ltd. All rights reserved.
 */

#ifndef _SESCAN_H_
#define _SESCAN_H_

#include <asm-generic/sections.h>
#include <linux/crypto.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/scatterlist.h>
#include <linux/security.h>
#include <linux/string.h>
#include "./include/hw_rscan_utils.h"

extern int selinux_enforcing;

int get_selinux_enforcing(void);
int sescan_hookhash(uint8_t *hash);

#endif
