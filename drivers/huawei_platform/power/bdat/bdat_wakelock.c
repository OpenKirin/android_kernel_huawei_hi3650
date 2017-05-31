/*
 * BDAT wakelock sources.
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

#include <linux/atomic.h>
#include <linux/list.h>
#include <linux/jiffies.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#include <huawei_platform/power/bdat/bdat_common.h>

#define BDAT_MAX_WACKELOCK_SIZE			256
#define BDAT_MAX_NAME_LEN				256
#define BDAT_WAKELOCK_NAME_SIZE			64

/**
 * struct bdat_wl - Representation of wakelock
 *
 * wl_name: wakelock name
 * prevent_time:Total time(ms) this source has been preventing sleep
 * power_time: Total time(ms) this source has been consumed
 * active_count: Number of times the wakeup sorce was activated
 * uid: wakelock's uid
 * pid: wakelock's pid
 * pid_name: wakelock's pid name
 */
struct wakelock_stat {
	uid_t uid;
	pid_t pid;
	int active_count;
	int prevent_time;
	int power_time;
	char wl_name[BDAT_WAKELOCK_NAME_SIZE];
	char pid_name[TASK_COMM_LEN];
};

/**
 * bdat_wakelock - Representation of wakelock source
 *
 * start_time: jiffies when acquire the wakelock
 * active: Status of the wakeup source(true--acquire, false--release)
 */
struct bdat_wakelock {
	struct wakelock_stat stat;
	struct hlist_node list;
	unsigned long start_time;
	bool active;
};

/**
 * struct bdat_wakelock_store -store the wakelock sources
 *
 * array: store all bdat_wakelock.
 * num: the used number
 * active_size:Total times which state is active(acquire)
 */
struct bdat_wakelock_store {
	struct bdat_wakelock array[BDAT_MAX_WACKELOCK_SIZE];
	int num;
	int active_size;
};

struct bdat_wakelock_store wakelock_store;
static spinlock_t wakelock_lock;
static atomic_t wakelock_enable;
HLIST_HEAD(bdat_wakelock_head);

/*
 * Function name: bdat_wakelock_lookup_add
 * Description: lookup or create the wakelock name in list
 * Input: const char* name, wakeup source name
 * Output: none
 * Return: struct bdat_wakelock
 */
static struct bdat_wakelock *bdat_wakelock_lookup_add(const char *name)
{
	size_t len;
	struct hlist_node *p = NULL, *n = NULL;
	struct bdat_wakelock *wl = NULL;

	len = strlen(name);
	if (len > BDAT_WAKELOCK_NAME_SIZE - 1)
		len = BDAT_WAKELOCK_NAME_SIZE - 1;

	hlist_for_each_safe(p, n, &bdat_wakelock_head) {
		wl = hlist_entry(p, struct bdat_wakelock, list);
		if (0 == strncmp(name, wl->stat.wl_name, len))
			if (!wl->stat.wl_name[len])
				return wl;
	}

	if (wakelock_store.num >= BDAT_MAX_WACKELOCK_SIZE) {
		/* when the vector is full, report this message to daemon */
		BDAT_LOGE("wakelock num exceed %d, abort waklock name:%s!",
			BDAT_MAX_WACKELOCK_SIZE, name);
		return NULL;
	}
	wl = &wakelock_store.array[wakelock_store.num];
	wakelock_store.num++;
	strncpy(wl->stat.wl_name, name, len);
	wl->stat.wl_name[len] = '\0';

	hlist_add_head(&wl->list, &bdat_wakelock_head);

	return wl;
}

/*
 * Function name: bdat_calc_active_wakelock
 * Description: calculate wakeup source power
 * Input: unsigned long now, now time
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
static void bdat_calc_active_wakelock(unsigned long now)
{
	struct hlist_node *p = NULL, *n = NULL;
	struct bdat_wakelock *wl = NULL;
	int delta = 0;
	long time;
	unsigned long weight;

	if (wakelock_store.active_size > 0)
		weight = wakelock_store.active_size;
	else
		weight = 1;

	hlist_for_each_safe(p, n, &bdat_wakelock_head) {
		wl = hlist_entry(p, struct bdat_wakelock, list);
		if (wl->active) {
			time = (long)now - (long)wl->start_time;
			delta = (int)jiffies_to_msecs(time);
			wl->stat.prevent_time += delta;
			wl->stat.power_time += (delta / weight);
			wl->start_time = now;
		}
	}
}

/*
 * Function name: bdat_collect_wakelock_stop
 * Description: stop collect the wakelock power when set disable
 * Input: none
 * Output: none
 * Return: none
 */
static int bdat_collect_wakelock_stop(void)
{
	struct hlist_node *p = NULL, *n = NULL;
	struct bdat_wakelock *wl = NULL;

	bdat_calc_active_wakelock(jiffies);
	hlist_for_each_safe(p, n, &bdat_wakelock_head) {
		wl = hlist_entry(p, struct bdat_wakelock, list);
		wl->active = false;
	}
	wakelock_store.active_size = 0;

	return 0;
}

/*
 * Function name: bdat_collect_wakelock_start
 * Description: start collect the wakeup source when set enable
 * Input: none
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
static int bdat_collect_wakelock_start(void)
{
	char active_sources[BDAT_MAX_NAME_LEN];
	char *sptr, *name, *str;
	struct bdat_wakelock *wl = NULL;

	/* get the active wakelock name, and save to active_sources */
	pm_get_active_wakeup_sources(active_sources, BDAT_MAX_NAME_LEN);
	sptr = active_sources;
	str = strsep(&sptr, ":");
	if (str == NULL || sptr == NULL)
		return -1;
	if (0 != strncmp(str, "Pending Wakeup Sources",
		sizeof("Pending Wakeup Sources")))
		return 0;
	sptr++;
	while ((name = strsep(&sptr, " ")) && *name != '\0') {
		wl = bdat_wakelock_lookup_add(name);
		if (NULL == wl)
			continue;

		wl->active = true;
		wl->stat.active_count++;
		wl->start_time = jiffies;
		strncpy(wl->stat.pid_name, "null", sizeof("null"));
		wakelock_store.active_size++;
	}

	return 0;
}

/*
 * Function name: bdat_update_wakelock
 * Description: entry func, acquire or release a wakelock
 * Input: const char* name, wakelock name
 *        bool active, wakelock active state
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_update_wakelock(const char *name, bool active)
{
	struct bdat_wakelock *wl;
	unsigned long flags, now;

	if (!atomic_read(&wakelock_enable))
		return -1;

	if (name == NULL) {
		BDAT_LOGE("invalid wakeup source name\n");
		return -1;
	}

	spin_lock_irqsave(&wakelock_lock, flags);
	wl = bdat_wakelock_lookup_add(name);
	if (wl == NULL || wl->active == active) {
		spin_unlock_irqrestore(&wakelock_lock, flags);
		return -1;
	}

	now = jiffies;
	bdat_calc_active_wakelock(now);
	wl->active = active;
	if (0 == wl->stat.pid) {
		strncpy(wl->stat.pid_name, current->comm, TASK_COMM_LEN);
		if (current->real_cred != NULL)
			wl->stat.uid = current->real_cred->uid.val;
		else
			wl->stat.uid = 0;
		wl->stat.pid = current->pid;
	}

	/*
	 * true, acquire a wakelock
	 * false, release a wakelock
	 */
	if (active) {
		wl->start_time = now;
		wl->stat.active_count++;
		wakelock_store.active_size++;
	} else {
		wakelock_store.active_size--;
	}
	spin_unlock_irqrestore(&wakelock_lock, flags);

	return 0;
}

/*
 * Function name: bdat_set_wakelock_enable
 * Description: set bdat wakeup source enable
 * Input: bool enable, wakeup source enable state
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_set_wakelock_enable(bool enable)
{
	unsigned long flags;
	int ret;

	if (atomic_read(&wakelock_enable) == enable)
		return 0;

	BDAT_LOGD("wakelock enable: %d", enable);

	atomic_set(&wakelock_enable, enable);
	spin_lock_irqsave(&wakelock_lock, flags);
	if (enable)
		ret = bdat_collect_wakelock_start();
	else
		ret = bdat_collect_wakelock_stop();
	spin_unlock_irqrestore(&wakelock_lock, flags);

	return ret;
}

/*
 * Function name: bdat_get_wakelock
 * Description: get wakelock stats, and send to daemon
 * Input: unsigned long arg, user point
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_get_wakelock(unsigned long arg)
{
	struct hlist_node *p = NULL, *n = NULL;
	struct bdat_wakelock *wl = NULL;
	unsigned long flags;
	void __user *argp = (void __user *)arg;
	int rc = 0;
	size_t size, wl_size;
	struct dev_transmit_t *stat = NULL;
	char *pStat;

	wl_size = sizeof(struct wakelock_stat);

	spin_lock_irqsave(&wakelock_lock, flags);
	if (wakelock_store.num <= 0) {
		spin_unlock_irqrestore(&wakelock_lock, flags);
		return 0;
	}
	size = sizeof(struct dev_transmit_t)
			+ wakelock_store.num * wl_size;
	stat = kzalloc(size, GFP_KERNEL);
	if (stat == NULL) {
		BDAT_LOGE("Failed to kmalloc for wakelock stat buffer\n");
		rc = -ENOMEM;
		spin_unlock_irqrestore(&wakelock_lock, flags);
		return rc;
	}
	pStat = stat->data;

	bdat_calc_active_wakelock(jiffies);
	hlist_for_each_safe(p, n, &bdat_wakelock_head) {
		wl = hlist_entry(p, struct bdat_wakelock, list);
		/* save wakelock data */
		if (wl->stat.prevent_time > 0) {
			memcpy(pStat, &(wl->stat), wl_size);
			pStat += wl_size;
			stat->length++;
		}

		hlist_del(&wl->list);
		memset(wl, 0, wl_size);
	}

	if (stat->length > 0) {
		size = stat->length * wl_size
			+ sizeof(struct dev_transmit_t);
		BDAT_LOGD("wakelock stat length: %d", stat->length);
		rc = copy_to_user(argp, stat, size);
	}
	kfree(stat);

	memset(&wakelock_store, 0, sizeof(wakelock_store));

	if (atomic_read(&wakelock_enable))
		bdat_collect_wakelock_start();

	spin_unlock_irqrestore(&wakelock_lock, flags);

	return rc;
}

/*
 * Function name: bdat_wakelock_init
 * Description: bdat wakelock init
 * Input: none
 * Output: none
 * Return: 0, success
 *         -1, failed
 */
int bdat_wakelock_init(void)
{
	atomic_set(&wakelock_enable, 0);
	memset(&wakelock_store, 0, sizeof(wakelock_store));
	spin_lock_init(&wakelock_lock);

	return 0;
}

/*
 * Function name: bdat_wakelock_exit
 * Description: bdat wakelock exit
 * Input: none
 * Output: none
 * Return: none
 */
void bdat_wakelock_exit(void)
{
}
