/*
 * Copyright (c) Huawei Technologies Co., Ltd. 1998-2016. All rights reserved.
 *
 * File name: bdat.h
 * Description: BDAT beacon information API definition
 * Author: Pengyu  ID: 00188486
 * Version: 1.0
 * Date: 2016/02/04
 *
 */

#ifndef BDAT_H
#define BDAT_H

int bdat_update_wakelock(const char *name, bool active);
int bdat_update_gpu_info(unsigned long freq, unsigned long busy_time,
	unsigned long total_time, unsigned long cycle_ms);
void bdat_update_wakeup_info(const char *name, int gpio);
#endif
