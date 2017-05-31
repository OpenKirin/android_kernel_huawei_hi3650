/*
 * BDAT gpu.
 *
 * Copyright (C) 2016 Huawei Device Co.,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#include <huawei_platform/power/bdat/bdat_common.h>

#define BDAT_GPU_FREQ_MAX_SIZE		(20)
#define US_PER_MSEC					(1000)

/*
 * freq, gpu freq(HZ)
 * run_time, run time
 * idle_time, idle time
 */
struct gpu_info {
	unsigned long freq;
	unsigned long run_time;
	unsigned long idle_time;
};

struct gpu_store {
	struct gpu_info array[BDAT_GPU_FREQ_MAX_SIZE];
	int num;
};

struct gpu_store store;
static spinlock_t gpu_lock;
static bool enable_update_gpu_info;

/*
 * Function name: bdat_gpu_lookup_add
 * Description: lookup or create the gpu information
 * Input: unsigned long freq, gpu freq
 * Output: none
 * Return: struct gpu_info
 */
static struct gpu_info *bdat_gpu_lookup_add(unsigned long freq)
{
	int i = 0, num = store.num;

	if (0 == freq)
		return NULL;

	for (i = 0; i < num; i++) {
		if (freq == store.array[i].freq)
			return &store.array[i];
	}
	if (num < BDAT_GPU_FREQ_MAX_SIZE - 1) {
		store.array[num].freq = freq;
		store.num++;
		return &store.array[num];
	}
	return NULL;
}

/*
 * Function name: bdat_update_gpu_info
 * Description: entry func when gpu is running
 * Input: unsigned long freq, gpu freq(HZ)
 *        unsigned long busy_time, device was working among the total_time
 *        unsigned long total_time, total time devfreq_dev_status instance
 *        unsigned long cycle_ms, gpu polling time
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_update_gpu_info(unsigned long freq, unsigned long busy_time,
	unsigned long total_time, unsigned long cycle_ms)
{
	struct gpu_info *info = NULL;
	unsigned long temp = 0;

	if (!enable_update_gpu_info || 0 == freq)
		return -1;

	spin_lock_bh(&gpu_lock);
	info = bdat_gpu_lookup_add(freq);
	if (NULL == info) {
		spin_unlock_bh(&gpu_lock);
		BDAT_LOGE("gpu num exceed %d, abort freq:%ld!",
			BDAT_GPU_FREQ_MAX_SIZE, freq);
		return -1;
	}

	info->freq = freq;
	temp = cycle_ms * US_PER_MSEC * busy_time / total_time;
	info->run_time += temp;
	info->idle_time += (cycle_ms * US_PER_MSEC - temp);

	spin_unlock_bh(&gpu_lock);

	return 0;
}

/*
 * Function name: bdat_set_gpu_enable
 * Description: set gpu enable
 * Input: bool enable, true--enable false--disable
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_set_gpu_enable(bool enable)
{
	enable_update_gpu_info = enable;
	BDAT_LOGD("gpu enable: %d", enable);
	return 0;
}

/*
 * Function name: bdat_get_gpu_info
 * Description: get gpu information
 * Input: unsigned long arg, user point
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_get_gpu_info(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	struct dev_transmit_t *stat = NULL;
	int rc = 0, i = 0;
	uint8_t *pdata;
	size_t size;

	spin_lock_bh(&gpu_lock);
	if (store.num <= 0) {
		spin_unlock_bh(&gpu_lock);
		return 0;
	}
	size = store.num * sizeof(struct gpu_info)
		+ sizeof(struct dev_transmit_t);

	stat = kzalloc(size, GFP_KERNEL);
	if (stat == NULL) {
		rc = -ENOMEM;
		spin_unlock_bh(&gpu_lock);
		return rc;
	}

	pdata = stat->data;
	for (i = 0; i < store.num; i++) {
		memcpy(pdata, &store.array[i], sizeof(struct gpu_info));
		pdata += sizeof(struct gpu_info);
	}
	stat->length = store.num;
	BDAT_LOGD("gpu stat length: %d", stat->length);

	rc = copy_to_user(argp, stat, size);
	memset(&store, 0, sizeof(struct gpu_store));
	spin_unlock_bh(&gpu_lock);

	kfree(stat);

	return rc;
}

/*
 * Function name: bdat_gpu_init
 * Description: bdat bdat_gpu_init init
 * Input: none
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_gpu_init(void)
{
	memset(&store, 0, sizeof(struct gpu_store));
	spin_lock_init(&gpu_lock);
	enable_update_gpu_info = false;

	return 0;
}

/*
 * Function name: bdat_gpu_exit
 * Description: bdat bdat_gpu_exit exit
 * Input: none
 * Output: none
 * Return: none
 */
void bdat_gpu_exit(void)
{
}
