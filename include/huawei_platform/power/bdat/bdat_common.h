/*
 * Copyright (c) Huawei Technologies Co., Ltd. 1998-2016. All rights reserved.
 *
 * File name: bdat_common.h
 * Description: bdat common header file
 * Author: Pengyu  ID: 00188486
 * Version: 1.0
 * Date: 2016/04/27
 *
 */

#ifndef BDAT_COMMON_H
#define BDAT_COMMON_H

#define BDAT_LOG_TAG	"BDAT"

#define BDAT_DEBUG		1
#define BDAT_INFO		1

#define BDAT_LOGD(fmt, ...) \
	do { \
		if (BDAT_DEBUG) \
			pr_debug("["BDAT_LOG_TAG"] %s: "fmt"\n", \
					__func__, ##__VA_ARGS__); \
	} while (0)

#define BDAT_LOGI(fmt, ...) \
	do { \
		if (BDAT_INFO) \
			pr_info("["BDAT_LOG_TAG"] %s: "fmt"\n", \
					__func__, ##__VA_ARGS__); \
	} while (0)

#define BDAT_LOGE(fmt, ...) \
	pr_err("["BDAT_LOG_TAG"] %s: "fmt"\n", __func__, ##__VA_ARGS__)

#define NAME_SIZE		64

struct pid_cputime {
	uid_t uid;
	pid_t pid;
	unsigned long long utime;
	unsigned long long stime;
	char name[NAME_SIZE];
};

struct dev_transmit_t {
	int length;
	char data[0];
};

int bdat_wakelock_init(void);
void bdat_wakelock_exit(void);
int bdat_set_wakelock_enable(bool enable);
int bdat_get_wakelock(unsigned long arg);

int bdat_pid_cputime_init(void);
void bdat_pid_cputime_exit(void);
int bdat_update_pid_cputime(void);
int bdat_get_pid_cputime(int length, char *buf);

int bdat_gpu_init(void);
void bdat_gpu_exit(void);
int bdat_set_gpu_enable(bool enable);
int bdat_get_gpu_info(unsigned long arg);

void pm_get_active_wakeup_sources(char *active_sources, size_t max);

#endif
