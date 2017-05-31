/*
 * hi64xx_hifi_om.c -- om module for hi64xx
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/sched/rt.h>
#include <linux/wakelock.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/dma-mapping.h>
#include <linux/clk.h>
#include <linux/rtc.h>
#include <linux/time.h>
#include <linux/stat.h>
#include <linux/hisi/hi64xx/hi6403_dsp_regs.h>
#include <hi64xx_hifi_interface.h>

#include "hi64xx_hifi_om.h"
#include "hi64xx_hifi_debug.h"
#include "slimbus.h"
#include "hifi_lpp.h"
#include "hi64xx_hifi_misc.h"
#include "hi64xx_hifi_anc_beta.h"

/*lint -e655 -e838 -e730*/

#define UNUSED_PARAMETER(x) (void)(x)

#define HI64XX_OM_DRIVER_VERSION "1.0"
#define DRV_NAME "hi64xx_hifi_om_drv"

#define VERIFY_FRAME_HEAD_MAGIC_NUM (0x5a5a5a5a)
#define VERIFY_FRAME_BODY_MAGIC_NUM (0xa5a5a5a5)

#define LEFT_DMA_ADDR (CODEC_DSP_OM_DMA_BUFFER_ADDR)
#define LEFT_DMA_SIZE (CODEC_DSP_OM_DMA_BUFFER_SIZE / 2)
#define LEFT_DMA_CFG_ADDR (CODEC_DSP_OM_DMA_CONFIG_ADDR)
#define LEFT_DMA_CFG_SIZE (CODEC_DSP_OM_DMA_CONFIG_SIZE / 2)

#define RIGHT_DMA_ADDR (LEFT_DMA_ADDR + LEFT_DMA_SIZE)
#define RIGHT_DMA_SIZE (LEFT_DMA_SIZE)
#define RIGHT_DMA_CFG_ADDR (LEFT_DMA_CFG_ADDR + LEFT_DMA_CFG_SIZE)
#define RIGHT_DMA_CFG_SIZE (LEFT_DMA_CFG_SIZE)

#define HOOK_AP_DMA_INTERVAL (20) /* ms */
#define HOOK_DSP_DMA_INTERVAL (5) /* ms */
#define HOOK_AP_DSP_DMA_TIMES ((HOOK_AP_DMA_INTERVAL) / (HOOK_DSP_DMA_INTERVAL))
#define HOOK_PATH_BETA_CLUB "/data/log/codec_dsp/beta_club/"
#define HOOK_PATH_VISUAL_TOOL "/data/log/codec_dsp/visual_tool/"
#define HOOK_PATH_DEFAULT "/data/log/codec_dsp/default/"
#define HOOK_RECORD_FILE "hi64xx_dsp_hook.data"
#define HOOK_RECORD_MAX_LENGTH (200)
#define HOOK_FILE_NAME_MAX_LENGTH (100)
#define HOOK_VISUAL_TOOL_MAX_FILE_SIZE (192 * 1024)
#define HOOK_MAX_FILE_SIZE (0x40000000) /* 1G */
#define HOOK_MAX_DIR_SIZE (0x100000000) /* 4G */
#define HOOK_DEFAULT_SUBDIR_CNT (20)
#define HOOK_MAX_SUBDIR_CNT (5000)
#define PRINT_MAX_CNT (3)

#define ROOT_UID     0
#define SYSTEM_GID   1000

enum {
	VERIFY_DEFAULT,
	VERIFY_START,
	VERIFY_ADJUSTING,
	VERIFY_ADJUSTED,
	VERIFY_END,
};

enum {
	PCM_SWAP_BUFF_A 	= 0,
	PCM_SWAP_BUFF_B,
	PCM_SWAP_BUFF_CNT,
};

enum {
	HOOK_LEFT = 0,
	HOOK_RIGHT,
	HOOK_CNT,
};

typedef enum {
	HOOK_VALID = 0,
	HOOK_POS_UNSUPPORT,
	HOOK_CONFIG_ERR,
	HOOK_BANDWIDTH_LIMIT,
	HOOK_DUPLICATE_POS,
	HOOK_IF_BUSY,
	HOOK_MULTI_SCENE,
	HOOK_STATUS_BUTT,
}hook_status;

struct hook_pos_name {
	hook_pos pos;
	char *name;
};

struct linux_dirent {
	unsigned long d_ino;
	unsigned long d_off;
	unsigned short d_reclen;
	char d_name[1];
};

struct data_cfg {
	unsigned int sample_rate;
	unsigned short resolution;
	unsigned short channels;
};

struct pos_info {
	hook_pos pos;
	struct data_cfg config;
	unsigned int size;
	hook_status hook_status;
};

struct pos_infos {
	struct list_head node;
	struct pos_info info;
};

struct data_flow {
	struct list_head node;
	void *addr;
};

struct hook_dma_cfg {
	unsigned int port; 	    /* slimbus port address */
	unsigned int config;    /* dma config number */
	unsigned short channel;	/* dma channel number */
};

struct hook_runtime {
	void __iomem *lli_cfg[PCM_SWAP_BUFF_CNT];   /* must be aligned to 32byte */
	void *lli_cfg_phy[PCM_SWAP_BUFF_CNT];       /* lli cfg, physical addr */
	void __iomem *buffer[PCM_SWAP_BUFF_CNT];    /* dma buffer */
	void *buffer_phy[PCM_SWAP_BUFF_CNT];        /* dma buffer, physical addr */
	unsigned int size;                          /* dma buffer size */
	unsigned short channel;                     /* dma channel number */
	struct semaphore hook_proc_sema;
	struct semaphore hook_stop_sema;
	struct wake_lock wake_lock;
	struct task_struct *kthread;
	unsigned int kthread_should_stop;
	unsigned int verify_state;
	struct pos_infos info_list;
	struct data_flow data_list;
	unsigned int hook_id;
	unsigned int cookie;
	unsigned int hook_file_size;
	unsigned int hook_file_cnt;
	bool parsed;
};

struct hi64xx_om_priv {
	struct device *dev;
	struct clk *asp_subsys_clk;
	struct hook_runtime runtime[HOOK_CNT];
	char hook_path[HOOK_PATH_MAX_LENGTH];
	unsigned short bandwidth;
	unsigned short sponsor;
	unsigned int dir_count;
	bool standby;
	bool started;
	bool is_eng;
	bool should_deactive_slimbus;
	unsigned short open_file_failed_cnt;
};

static struct data_cfg slim_data_cfg[HOOK_CNT] = {
	{.sample_rate = 192000, .resolution = 4, .channels = 1},  /* left */
	{.sample_rate = 192000, .resolution = 4, .channels = 1},  /* right */
};

static struct hook_dma_cfg slim_dma_cfg[HOOK_CNT] = {
	{.port = 0xe8051180, .config = 0x43322067, .channel = 7},  /* left */
	{.port = 0xe80511c0, .config = 0x43322077, .channel = 8},  /* right */
};

static struct hook_pos_name pos_name[] = {
	{HOOK_POS_IF0,              "IF0"},
	{HOOK_POS_IF1,              "IF1"},
	{HOOK_POS_IF2,              "IF2"},
	{HOOK_POS_IF3,              "IF3"},
	{HOOK_POS_IF4,              "IF4"},
	{HOOK_POS_IF5,              "IF5"},
	{HOOK_POS_IF6,              "IF6"},
	{HOOK_POS_IF7,              "IF7"},
	{HOOK_POS_IF8,              "IF8"},
	{HOOK_POS_ANC_CORE,         "ANC_CORE"},
	{HOOK_POS_LOG,              "LOG"},
	{HOOK_POS_ANC_PCM_RX_VOICE, "ANC_PCM_RX_VOICE"},
	{HOOK_POS_ANC_PCM_REF,      "ANC_PCM_REF"},
	{HOOK_POS_ANC_PCM_ERR,      "ANC_PCM_ERR"},
	{HOOK_POS_ANC_PCM_ANTI,     "ANC_PCM_ANTI"},
	{HOOK_POS_ANC_BETA_CSINFO,  "ANC_BETA_CSINFO"},
	{HOOK_POS_ANC_PCM_TX_VOICE, "ANC_PCM_TX_VOICE"},
	{HOOK_POS_ANC_ALG_INDICATE, "ANC_ALG_INDICATE"},
	{HOOK_POS_ANC_COEF,         "ANC_COEF"},
	{HOOK_POS_PA_EFFECTIN,      "PA_EFFECTIN"},
	{HOOK_POS_PA_EFFECTOUT,     "PA_EFFECTOUT"},
	{HOOK_POS_WAKEUP_MICIN,     "WAKEUP_MICIN"},
	{HOOK_POS_WAKEUP_EFFECTOUT, "WAKEUP_EFFECTOUT"},
	{HOOK_POS_PA1_I,            "PA1_I"},
	{HOOK_POS_PA1_V,            "PA1_V"},
	{HOOK_POS_PA2_I,            "PA2_I"},
	{HOOK_POS_PA2_V,            "PA2_V"},
};

static struct hi64xx_om_priv *om_priv = NULL;

static unsigned int _get_data_size(struct data_cfg *config)
{
	uint32_t data_size = 0;

	data_size = config->sample_rate * config->resolution *
				config->channels * HOOK_AP_DMA_INTERVAL / 1000;

	return data_size;
}

static unsigned int _get_verify_pos(void *data, unsigned int size)
{
	unsigned int i = 0;

	unsigned int *buffer = (unsigned int*)data;

	for (i = 0; i < size / sizeof(unsigned int); i++)
		if (VERIFY_FRAME_HEAD_MAGIC_NUM == buffer[i])
			break;

	return i * sizeof(unsigned int);
}

static unsigned int _get_idle_buffer_id(struct hook_runtime *runtime)
{
	unsigned int used_dma_addr = 0;
	unsigned int src_addr_a = 0;

	src_addr_a = (unsigned int)((unsigned long)runtime->buffer_phy[PCM_SWAP_BUFF_A]);

	used_dma_addr = asp_dma_get_des(runtime->channel);

	if (used_dma_addr == src_addr_a)
		return PCM_SWAP_BUFF_B;
	else
		return PCM_SWAP_BUFF_A;
}

static const char* _get_pos_name(hook_pos pos)
{
	unsigned int i;
	unsigned int array_size = 0;

	array_size = sizeof(pos_name) / sizeof(pos_name[0]);

	for (i = 0; i < array_size; i++) {
		if (pos_name[i].pos == pos)
			return pos_name[i].name;
	}

	return "UNKNOW";
}

static int _add_data_to_list(struct hook_runtime *runtime)
{
	int ret = 0;
	void *buffer = NULL;
	unsigned int id = 0;
	struct data_flow *data = NULL;

	buffer = kzalloc(runtime->size, GFP_KERNEL);
	if (!buffer) {
		HI64XX_DSP_ERROR("malloc failed.\n");
		return -ENOMEM;
	}

	data = kzalloc(sizeof(struct data_flow), GFP_KERNEL);
	if (!data) {
		HI64XX_DSP_ERROR("malloc failed.\n");
		ret = -ENOMEM;
		goto err_exit;
	}

	id = _get_idle_buffer_id(runtime);
	memcpy(buffer, runtime->buffer[id], runtime->size);

	if (runtime->cookie != _get_idle_buffer_id(runtime))
		HI64XX_DSP_WARNING("dma buffer is changed.\n");

	data->addr = buffer;

	list_add_tail(&data->node, &runtime->data_list.node);

	return 0;

err_exit:
	kfree(buffer);

	return ret;
}

static int _alloc_hook_buffer_fama(unsigned int hook_id)
{
	struct hook_runtime *runtime = NULL;
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	runtime = &priv->runtime[hook_id];

	if (HOOK_LEFT == hook_id) {
		runtime->buffer_phy[PCM_SWAP_BUFF_A] = (void *)LEFT_DMA_ADDR;
		runtime->buffer_phy[PCM_SWAP_BUFF_B] = (void *)(unsigned long)(LEFT_DMA_ADDR + runtime->size);
		runtime->lli_cfg_phy[PCM_SWAP_BUFF_A] = (void *)LEFT_DMA_CFG_ADDR;
		runtime->lli_cfg_phy[PCM_SWAP_BUFF_B] =
			(void *)(LEFT_DMA_CFG_ADDR + sizeof(struct dma_lli_cfg));

		runtime->buffer[PCM_SWAP_BUFF_A] =
			ioremap_wc(LEFT_DMA_ADDR, LEFT_DMA_SIZE);
		runtime->buffer[PCM_SWAP_BUFF_B] =
			(void __iomem*)((char *)runtime->buffer[PCM_SWAP_BUFF_A] + runtime->size);
		runtime->lli_cfg[PCM_SWAP_BUFF_A] =
			ioremap_wc(LEFT_DMA_CFG_ADDR, LEFT_DMA_CFG_SIZE);
		runtime->lli_cfg[PCM_SWAP_BUFF_B] =
			(void __iomem*)((char *)runtime->lli_cfg[PCM_SWAP_BUFF_A] + sizeof(struct dma_lli_cfg));
	} else {
		runtime->buffer_phy[PCM_SWAP_BUFF_A] = (void *)RIGHT_DMA_ADDR;
		runtime->buffer_phy[PCM_SWAP_BUFF_B] = (void *)(unsigned long)(RIGHT_DMA_ADDR + runtime->size);
		runtime->lli_cfg_phy[PCM_SWAP_BUFF_A] = (void *)RIGHT_DMA_CFG_ADDR;
		runtime->lli_cfg_phy[PCM_SWAP_BUFF_B] =
			(void *)(RIGHT_DMA_CFG_ADDR + sizeof(struct dma_lli_cfg));

		runtime->buffer[PCM_SWAP_BUFF_A] =
			ioremap_wc(RIGHT_DMA_ADDR, RIGHT_DMA_SIZE);
		runtime->buffer[PCM_SWAP_BUFF_B] =
			(void __iomem*)((char *)runtime->buffer[PCM_SWAP_BUFF_A] + runtime->size);
		runtime->lli_cfg[PCM_SWAP_BUFF_A] =
			ioremap_wc(RIGHT_DMA_CFG_ADDR, RIGHT_DMA_CFG_SIZE);
		runtime->lli_cfg[PCM_SWAP_BUFF_B] =
			(void __iomem*)((char *)runtime->lli_cfg[PCM_SWAP_BUFF_A] + sizeof(struct dma_lli_cfg));
	}

	/* must use ioremap_wc to remap */
	memset((void*)runtime->buffer[PCM_SWAP_BUFF_A], 0, LEFT_DMA_SIZE);
	memset((void*)runtime->lli_cfg[PCM_SWAP_BUFF_A], 0, LEFT_DMA_CFG_SIZE);

	return 0;
}


static int _hook_runtime_config(unsigned int hook_id)
{
	struct hi64xx_om_priv *priv = om_priv;
	struct dma_lli_cfg *lli_cfg_a = NULL;
	struct dma_lli_cfg *lli_cfg_b = NULL;
	struct hook_runtime *runtime = NULL;
	struct data_cfg *data_cfg = NULL;
	struct hook_dma_cfg *dma_cfg = NULL;

	BUG_ON(NULL == priv);

	runtime = &priv->runtime[hook_id];
	data_cfg = &slim_data_cfg[hook_id];
	dma_cfg = &slim_dma_cfg[hook_id];

	runtime->size = _get_data_size(data_cfg);

	_alloc_hook_buffer_fama(hook_id);

	runtime->channel = dma_cfg->channel;
	runtime->verify_state = VERIFY_DEFAULT;
	runtime->parsed = false;

	lli_cfg_a = (struct dma_lli_cfg*)runtime->lli_cfg[PCM_SWAP_BUFF_A];
	lli_cfg_b = (struct dma_lli_cfg*)runtime->lli_cfg[PCM_SWAP_BUFF_B];

	lli_cfg_a->a_count = runtime->size;
	lli_cfg_a->src_addr = dma_cfg->port;
	lli_cfg_a->des_addr = (unsigned int)((unsigned long)runtime->buffer_phy[PCM_SWAP_BUFF_A]);
	lli_cfg_a->config = dma_cfg->config;
	lli_cfg_a->lli = ASP_DMA_LLI_LINK(runtime->lli_cfg_phy[PCM_SWAP_BUFF_B]);

	lli_cfg_b->a_count = runtime->size;
	lli_cfg_b->src_addr = dma_cfg->port;
	lli_cfg_b->des_addr = (unsigned int)((unsigned long)runtime->buffer_phy[PCM_SWAP_BUFF_B]);
	lli_cfg_b->config = dma_cfg->config;
	lli_cfg_b->lli = ASP_DMA_LLI_LINK(runtime->lli_cfg_phy[PCM_SWAP_BUFF_A]);

	return 0;
}

static int _om_chown(char *path, uid_t user, gid_t group)
{
	int ret = 0;

	if (NULL == path)
		return -1;

	ret = (int)sys_chown((const char __user *)path, user, group);
	if (ret) {
		HI64XX_DSP_ERROR("chown %s uid [%d] gid [%d] failed error [%d]!\n",
				path, user, group, ret);
	}

	return ret;
}

static int _rm_dir(char *path)
{
	char *pdst = path;
	int ret = 0;

	while (*pdst)
		pdst++;

	pdst--;

	if (*pdst == '/')
		*pdst = '\0';

	ret = sys_rmdir(path);
	if (ret != 0)
		HI64XX_DSP_ERROR("del %s failed. ret:%d\n", path, ret);

	*pdst = '/';

	return ret;
}

static int _rm_hook_dir(char *path)
{
	int fd = -1, ret = 0;
	char buf[1024];
	int bufsize = 0;
	struct linux_dirent *dirent = NULL;
	char d_type;
	char fullname[HOOK_PATH_MAX_LENGTH] = {0};
	unsigned int bpos = 0;

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return -1;
	}

	fd = sys_open(path, O_RDONLY, 0770);
	if (fd < 0) {
		HI64XX_DSP_ERROR("open %s failed.\n", path);
		return fd;
	}

	for (;;) {
		bufsize = sys_getdents(fd, (struct linux_dirent *)buf, sizeof(buf));
		if (0 >= bufsize)
			break;

		dirent = (struct linux_dirent *)(buf + bpos);
		for (bpos = 0; bpos < bufsize; bpos += dirent->d_reclen) {
			dirent = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + dirent->d_reclen - 1);

			snprintf(fullname, sizeof(fullname) - 1, "%s/%s", path, dirent->d_name);/* [false alarm] */

			if (d_type == DT_DIR) {
				if (!strncmp(dirent->d_name, ".", sizeof("."))
					|| !strncmp(dirent->d_name, "..", sizeof(".."))
					|| !strncmp(dirent->d_name, "...", sizeof("...")))
					continue;

				(void)_rm_hook_dir(fullname);
			} else if (d_type == DT_REG) {
				sys_unlink(fullname);
			} else {
				HI64XX_DSP_WARNING("err dir type:%d.\n", d_type);
			}
		}
	}

	_rm_dir(path);

	if (fd >= 0)
		sys_close(fd);

	return ret;
}

static int _get_dir_count(char *path)
{
	int fd = -1;
	char buf[1024];
	int bufsize = 0;
	struct linux_dirent *dirent = NULL;
	struct kstat stat;
	unsigned int count = 0, bpos = 0;

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return -1;
	}

	fd = sys_open(path, O_RDONLY, 0770);
	if (fd < 0) {
		HI64XX_DSP_ERROR("open %s failed.\n", path);
		return fd;
	}

	memset(&stat, 0, sizeof(struct kstat));
	if (0 != vfs_stat(path, &stat))
		HI64XX_DSP_WARNING("stat failed:%s.\n", path);

	memset(&buf, 0, sizeof(buf));
	bufsize = sys_getdents(fd, (struct linux_dirent *)buf, sizeof(buf));
	if (0 >= bufsize) {
		HI64XX_DSP_ERROR("sys_getdents end.\n");
		goto out;
	}

	dirent = (struct linux_dirent *)(buf + bpos);
	for (bpos = 0; bpos < bufsize; bpos += dirent->d_reclen) {
		dirent = (struct linux_dirent *)(buf + bpos);
		count++;
	}

out:
	if (fd >= 0)
		sys_close(fd);

	return count;
}

static long long _get_dir_size(char *path)
{
	int fd = -1;
	char buf[1024];
	int bufsize = 0;
	struct linux_dirent *dirent = NULL;
	char d_type;
	char fullname[HOOK_PATH_MAX_LENGTH] = {0};
	struct kstat stat;
	unsigned int bpos = 0;
	unsigned long long size = 0;

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return -1;
	}

	fd = sys_open(path, O_RDONLY, 0770);
	if (fd < 0) {
		HI64XX_DSP_ERROR("open %s failed.\n", path);
		return fd;
	}

	memset(&stat, 0, sizeof(struct kstat));
	if (0 != vfs_stat(path, &stat))
		HI64XX_DSP_WARNING("stat failed:%s.\n", path);

	size += stat.size;

	memset(&buf, 0, sizeof(buf));

	for (;;) {
		bufsize = sys_getdents(fd, (struct linux_dirent *)buf, sizeof(buf));
		if (0 >= bufsize)
			break;

		dirent = (struct linux_dirent *)(buf + bpos);
		for (bpos = 0; bpos < bufsize; bpos += dirent->d_reclen) {
			dirent = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + dirent->d_reclen - 1);

			memset(&stat, 0, sizeof(struct kstat));
			snprintf(fullname, sizeof(fullname) - 1, "%s/%s", path, dirent->d_name);/* [false alarm] */

			if (0 != vfs_stat(fullname, &stat))
				HI64XX_DSP_WARNING("stat failed:%s.\n", fullname);

			if (d_type == DT_DIR) {
				if (!strncmp(dirent->d_name, ".", sizeof("."))
					|| !strncmp(dirent->d_name, "..", sizeof(".."))
					|| !strncmp(dirent->d_name, "...", sizeof("...")))
					continue;

				size += _get_dir_size(fullname);
			} else if (d_type == DT_REG) {
				size += stat.size;
			} else {
				HI64XX_DSP_WARNING("err dir type:%d.\n", d_type);
			}
		}
	}

	if (fd >= 0)
		sys_close(fd);

	return size;
}

static void _get_dir_name(char *dir_name, size_t size)
{
	struct rtc_time tm;
	struct timeval tv;
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);
	BUG_ON(NULL == dir_name);

	memset(&tm, 0, sizeof(tm));
	memset(&tv, 0, sizeof(tv));

	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);

	snprintf(dir_name, size, "%s%04d%02d%02d%02d%02d%02d/",/* [false alarm] */
		priv->hook_path,
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);

	return;
}

static int _create_dir(char *path)
{
	int fd;

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return -1;
	}

	fd = sys_access(path, 0);
	if (fd) {
		fd = sys_mkdir(path, 0770);
		if (fd < 0) {
			HI64XX_DSP_ERROR("create dir %s failed!\n", path);
			return fd;
		}
		HI64XX_DSP_INFO("create dir %s successed.\n", path);
	}

	if (_om_chown(path, ROOT_UID, SYSTEM_GID)) {
		HI64XX_DSP_ERROR("chown %s failed!\n", path);
	}

	return 0;
}

static int _create_full_dir(char *path)
{
	char cur_path[HOOK_PATH_MAX_LENGTH];
	int index = 0;

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return -1;
	}

	memset(cur_path, 0, (unsigned long)HOOK_PATH_MAX_LENGTH);

	if (*path != '/')
		return -1;

	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/')
			_create_dir(cur_path);

		cur_path[index++] = *path++;
	}

	return 0;
}

static int _create_hook_dir(void)
{
	struct hi64xx_om_priv *priv = om_priv;
	long long dir_size = 0;
	int dir_count = 0;
	char dir[HOOK_PATH_MAX_LENGTH] = {0};
	mm_segment_t old_fs;
	int ret = 0;

	BUG_ON(NULL == priv);

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	if (_create_full_dir(priv->hook_path)) {
		ret = -EFAULT;
		goto out;
	}

	if (priv->sponsor != OM_SPONSOR_DEFAULT) {
		if (0 > _rm_hook_dir(priv->hook_path)) {
			ret = -EFAULT;
			goto out;
		}

		if (_create_full_dir(priv->hook_path)) {
			ret = -EFAULT;
			goto out;
		}

		goto out;
	}

	dir_size = _get_dir_size(priv->hook_path);
	if (0 > dir_size) {
		ret = dir_size;
		goto out;
	}

	HI64XX_DSP_INFO("dir size:%lld\n", dir_size);

	dir_count = _get_dir_count(priv->hook_path);
	if (0 > dir_count) {
		ret = dir_count;
		goto out;
	}

	HI64XX_DSP_INFO("dir count:%d, max dir count:%d\n",
			dir_count, priv->dir_count);

	if (dir_size > HOOK_MAX_DIR_SIZE
		|| (unsigned int)dir_count > priv->dir_count) {
		HI64XX_DSP_INFO("rm dirs, dir size:%lld, dir count:%d, max dir count:%d.\n",
			dir_size, dir_count, priv->dir_count);

		if (0 > _rm_hook_dir(priv->hook_path)) {
			ret = -EFAULT;
			goto out;
		}

		if (_create_full_dir(priv->hook_path)) {
			ret = -EFAULT;
			goto out;
		}
	}

	/* generate dir name by system time */
	_get_dir_name(dir, HOOK_PATH_MAX_LENGTH - 1);
	if (_create_full_dir(dir)) {
		ret = -EFAULT;
		goto out;
	}

	strncpy(priv->hook_path, dir, sizeof(priv->hook_path) - 1);

out:
	set_fs(old_fs);

	return ret;
}

int hi64xx_hifi_create_hook_dir(const char *path)
{
	mm_segment_t old_fs;
	char tmp_path[HOOK_PATH_MAX_LENGTH] = {0};
	int ret = 0;

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return -EINVAL;
	}

	strncpy(tmp_path, path,  sizeof(tmp_path) -1);

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	if (_create_full_dir(tmp_path)) {
		ret = -EFAULT;
		goto out;
	}

	if (0 > _rm_hook_dir(tmp_path)) {
		ret = -EFAULT;
		goto out;
	}

	if (_create_full_dir(tmp_path)) {
		ret = -EFAULT;
		goto out;
	}

out:
	set_fs(old_fs);

	return ret;
}

static void _set_hook_path(void)
{
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	switch (priv->sponsor) {
	case OM_SPONSOR_BETA:
		strncpy(priv->hook_path, HOOK_PATH_BETA_CLUB, sizeof(priv->hook_path));
		break;
	case OM_SPONSOR_TOOL:
		strncpy(priv->hook_path, HOOK_PATH_VISUAL_TOOL, sizeof(priv->hook_path));
		break;
	default:
		strncpy(priv->hook_path, HOOK_PATH_DEFAULT, sizeof(priv->hook_path));
		break;
	}
}

static void _dump_runtime(struct hook_runtime *runtime)
{
	struct dma_lli_cfg *lli_cfg_a = NULL;
	struct dma_lli_cfg *lli_cfg_b = NULL;

	if (!runtime)
		return;

	HI64XX_DSP_INFO("lli cfg:%pK, buffer:%pK\n",
				runtime->lli_cfg[PCM_SWAP_BUFF_A], runtime->buffer[PCM_SWAP_BUFF_A]);

	HI64XX_DSP_INFO("lli cfg phy:%pK, buffer phy:%pK\n",
				runtime->lli_cfg_phy[PCM_SWAP_BUFF_A], runtime->buffer_phy[PCM_SWAP_BUFF_A]);

	lli_cfg_a = (struct dma_lli_cfg*)runtime->lli_cfg[PCM_SWAP_BUFF_A];
	lli_cfg_b = (struct dma_lli_cfg*)runtime->lli_cfg[PCM_SWAP_BUFF_B];
	if (!lli_cfg_a || !lli_cfg_b)
		return;

	HI64XX_DSP_INFO("A::a count:0x%x, src addr:0x%x, dest addr:0x%x, config:0x%x, lli:0x%x\n",
				lli_cfg_a->a_count, lli_cfg_a->src_addr, lli_cfg_a->des_addr,
				lli_cfg_a->config, lli_cfg_a->lli);

	HI64XX_DSP_INFO("B::a count:0x%x, src addr:0x%x, dest addr:0x%x, config:0x%x, lli:0x%x\n",
				lli_cfg_b->a_count, lli_cfg_b->src_addr, lli_cfg_b->des_addr,
				lli_cfg_b->config, lli_cfg_b->lli);

	HI64XX_DSP_INFO("dma size:%d, dma channel:%d\n",
				runtime->size, runtime->channel);

	HI64XX_DSP_INFO("parsed:%d, verify state:%d\n",
				runtime->parsed, runtime->verify_state);
}


void hi64xx_hifi_dump_to_file(char *buf, unsigned int size, char *path)
{
	struct file *fp = NULL;
	int file_flag = O_RDWR;
	struct kstat file_stat;
	mm_segment_t fs = 0;
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	if (!path) {
		HI64XX_DSP_ERROR("path is null.\n");
		return;
	}

	if (!buf) {
		HI64XX_DSP_ERROR("buf is null.\n");
		return;
	}

	if (0 == size) {
		HI64XX_DSP_ERROR("size is 0.\n");
		return;
	}

	fs = get_fs();
	set_fs(KERNEL_DS); /*lint !e501*/

	if (0 == vfs_stat(path, &file_stat) &&
	    file_stat.size > HOOK_MAX_FILE_SIZE) {
		/* delete file */
		sys_unlink(path);
		HI64XX_DSP_INFO("delete too large file.\n");
	}

	if (0 > vfs_stat(path , &file_stat)) {
		if (priv->open_file_failed_cnt < PRINT_MAX_CNT)
			HI64XX_DSP_INFO("create file:%s.\n", path);
		file_flag |= O_CREAT;
	}

	fp = filp_open(path, file_flag, 0660);
	if (IS_ERR(fp)) {
		if (priv->open_file_failed_cnt < PRINT_MAX_CNT) {
			HI64XX_DSP_ERROR("open file fail: %s.\n", path);
			priv->open_file_failed_cnt++;
		}
		fp = NULL;
		goto END;
	}

	vfs_llseek(fp, 0L, SEEK_END);

	if(vfs_write(fp, buf, size, &fp->f_pos) < 0) {
		HI64XX_DSP_ERROR("write file fail.\n");
	}

	if (_om_chown(path, ROOT_UID, SYSTEM_GID)) {
		HI64XX_DSP_ERROR("chown %s failed!\n", path);
	}

END:
	if (fp)
		filp_close(fp, 0);

	set_fs(fs);
}

static void _dump_dsp_data_for_tool(hook_pos pos,
				void *data, unsigned int size, unsigned int hook_id)
{
	char path[HOOK_PATH_MAX_LENGTH + HOOK_FILE_NAME_MAX_LENGTH] = {0};
	char new_path[HOOK_PATH_MAX_LENGTH + HOOK_FILE_NAME_MAX_LENGTH] = {0};
	struct hi64xx_om_priv *priv = om_priv;
	struct hook_runtime *runtime = NULL;

	BUG_ON(NULL == priv);

	if (HOOK_POS_LOG == pos) {
		//todo:print dsp log
		return;
	}

	if (HOOK_LEFT == hook_id) {
		runtime = &priv->runtime[HOOK_LEFT];
		snprintf(path, sizeof(path) - 1, "%s%s_L_WRITING.data",/* [false alarm] */
				priv->hook_path, _get_pos_name(pos));
		snprintf(new_path, sizeof(new_path) - 1, "%s%s_L_%d.data",/* [false alarm] */
				priv->hook_path, _get_pos_name(pos), runtime->hook_file_cnt);
	}
	else {
		runtime = &priv->runtime[HOOK_RIGHT];
		snprintf(path, sizeof(path) - 1, "%s%s_R_WRITING.data",/* [false alarm] */
				priv->hook_path, _get_pos_name(pos));
		snprintf(new_path, sizeof(new_path) - 1, "%s%s_R_%d.data",/* [false alarm] */
				priv->hook_path, _get_pos_name(pos), runtime->hook_file_cnt);
	}

	hi64xx_hifi_dump_to_file(data, size, path);

	runtime->hook_file_size += size;

	if (runtime->hook_file_size >= HOOK_VISUAL_TOOL_MAX_FILE_SIZE) {
		(void)sys_rename(path, new_path);
		runtime->hook_file_cnt++;
		runtime->hook_file_size = 0;
	}
}

static void _dump_dsp_data(hook_pos pos,
				void *data, unsigned int size, unsigned int hook_id)
{
	char path[HOOK_PATH_MAX_LENGTH + HOOK_FILE_NAME_MAX_LENGTH] = {0};
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	if (HOOK_POS_LOG == pos) {
		//todo:print dsp log
		return;
	}

	if (OM_SPONSOR_BETA == priv->sponsor) {
		anc_beta_generate_path(pos, priv->hook_path, path, sizeof(path));
	} else {
		if (HOOK_LEFT == hook_id)
			snprintf(path, sizeof(path), "%s%s_L.data", priv->hook_path, _get_pos_name(pos));/* [false alarm] */
		else
			snprintf(path, sizeof(path), "%s%s_R.data", priv->hook_path, _get_pos_name(pos));/* [false alarm] */
	}
	hi64xx_hifi_dump_to_file(data, size, path);
}

static void _parse_dsp_data(void *data, struct hook_runtime *runtime)
{
	struct hi64xx_om_priv *priv = om_priv;
	unsigned int *buffer = (unsigned int*)data;
	unsigned int *dsp_buffer = NULL;
	struct pos_infos *pos_infos = NULL;
	unsigned int data_size = 0;
	unsigned int i = 0;

	BUG_ON(NULL == priv);

	if (VERIFY_FRAME_HEAD_MAGIC_NUM == *buffer) {
		HI64XX_DSP_WARNING("throw away verify data.\n");
		return;
	}

	/*
	 * data arrange:
	 * |dsp buffer1|dsp buffer2|dsp buffer3|dsp buffer4|
	 */
	for (i = 0; i < HOOK_AP_DSP_DMA_TIMES; i++) {
		dsp_buffer = buffer;

		list_for_each_entry(pos_infos, &runtime->info_list.node, node) {
			data_size = pos_infos->info.size;

			if (((char *)dsp_buffer + data_size) > ((char *)data + runtime->size)) {
				HI64XX_DSP_ERROR("om buffer will overflow, forbid dump data.\n");
				return;
			}

			if (OM_SPONSOR_TOOL == priv->sponsor)
				_dump_dsp_data_for_tool(pos_infos->info.pos, dsp_buffer,
						data_size, runtime->hook_id);
			else
				_dump_dsp_data(pos_infos->info.pos, dsp_buffer,
						data_size, runtime->hook_id);

			dsp_buffer += data_size / sizeof(unsigned int);
		}

		buffer += (runtime->size / HOOK_AP_DSP_DMA_TIMES) / sizeof(unsigned int);
	}
}

static int _parse_pos_info(void *data, struct hook_runtime *runtime)
{
	struct hi64xx_om_priv *priv = om_priv;
	struct pos_info *pos_info = NULL;
	struct pos_infos *pos_infos = NULL;
	unsigned int parsed_size = 0;
	unsigned int *buffer = (unsigned int*)data;
	char log[HOOK_RECORD_MAX_LENGTH] = {0};
	char path[HOOK_PATH_MAX_LENGTH + HOOK_FILE_NAME_MAX_LENGTH] = {0};

	BUG_ON(NULL == priv);

	/*
	 * pos info arrange:
	 * |5a5a5a5a|a5a5a5a5|......|a5a5a5a5|
	 * |  head  |  body  | info |  body  |
	 */
	if (VERIFY_FRAME_BODY_MAGIC_NUM != buffer[1]) {
		HI64XX_DSP_ERROR("err pos info:%d.\n", buffer[1]);
		return -EINVAL;
	}

	pos_info =(struct pos_info*) (&buffer[2]);

	while ((VERIFY_FRAME_BODY_MAGIC_NUM != *(unsigned int*)pos_info)
		&& parsed_size <= runtime->size) {
		if (HOOK_VALID != pos_info->hook_status
			|| (pos_info->size > (runtime->size / HOOK_AP_DSP_DMA_TIMES))) {
			HI64XX_DSP_ERROR("invalid hook pos:0x%x, size:%d, reason:%d.\n",
					pos_info->pos, pos_info->size, pos_info->hook_status);
			snprintf(log, sizeof(log) - 1, "invalid hook pos:0x%x, size:%d, reason:%d.\n",/* [false alarm] */
					pos_info->pos, pos_info->size, pos_info->hook_status);
			snprintf(path, sizeof(path) - 1, "%s%s", priv->hook_path, HOOK_RECORD_FILE);/* [false alarm] */
			hi64xx_hifi_dump_to_file(log, strlen(log), path);
			pos_info++;
			parsed_size += sizeof(struct pos_info);
			break;
		}

		pos_infos = kzalloc(sizeof(struct pos_infos), GFP_KERNEL);
		if (!pos_infos) {
			HI64XX_DSP_ERROR("malloc failed.\n");
			break;
		}

		memcpy(&pos_infos->info, pos_info, sizeof(struct pos_info));

		HI64XX_DSP_INFO("pos:0x%x, size:%d, state:%d, rate:%d, resolution:%d, channels:%d.\n",
					pos_infos->info.pos, pos_infos->info.size, pos_infos->info.hook_status,
					pos_infos->info.config.sample_rate, pos_infos->info.config.resolution,
					pos_infos->info.config.channels);

		list_add_tail(&pos_infos->node, &runtime->info_list.node);

		pos_info++;

		parsed_size += sizeof(struct pos_info);
	}

	return 0;
}

static void _data_verify(struct data_flow *data,
			struct hook_runtime *runtime)
{
	unsigned int pos = 0;
	unsigned int id = 0;

	if (VERIFY_END == runtime->verify_state)
		return;

	if (VERIFY_DEFAULT == runtime->verify_state) {
		pos = _get_verify_pos(data->addr, runtime->size);
		if (pos == runtime->size) {
			return;
		}

		id = _get_idle_buffer_id(runtime);
		if (pos)
			((struct dma_lli_cfg*)(runtime->lli_cfg[id]))->a_count = pos;

		HI64XX_DSP_INFO("verify pos:%d.\n", pos);

		runtime->verify_state = VERIFY_START;
		HI64XX_DSP_INFO("verify start.\n");

	} else if (VERIFY_START == runtime->verify_state) {
		((struct dma_lli_cfg*)(runtime->lli_cfg[PCM_SWAP_BUFF_A]))->a_count = runtime->size;
		((struct dma_lli_cfg*)(runtime->lli_cfg[PCM_SWAP_BUFF_B]))->a_count = runtime->size;
		runtime->verify_state = VERIFY_ADJUSTING;
		HI64XX_DSP_INFO("verify adjusting.\n");

	} else if (VERIFY_ADJUSTING == runtime->verify_state) {
		runtime->verify_state = VERIFY_ADJUSTED;
		HI64XX_DSP_INFO("verify adjusted.\n");

	} else {
		runtime->verify_state = VERIFY_END;
		HI64XX_DSP_INFO("verify end.\n");
	}
}

static void _data_parse(struct hook_runtime *runtime)
{
	struct data_flow *data = NULL;

	if (list_empty(&runtime->data_list.node)) {
		HI64XX_DSP_ERROR("data list is empty!\n");
		return;
	}
	data = list_entry(runtime->data_list.node.next, struct data_flow, node);

	_data_verify(data, runtime);

	if (VERIFY_END != runtime->verify_state)
		goto free_list_node;

	if (!runtime->parsed) {
		if (!_parse_pos_info(data->addr, runtime))
			runtime->parsed = true;
	} else {
		_parse_dsp_data(data->addr, runtime);
	}

free_list_node:
	list_del(&data->node);
	kfree(data->addr);
	kfree(data);
}

static void _hook_should_stop(void)
{
	slimbus_framer_type_t framer;
	unsigned int s2_ctrl = 0;
	bool s2_clk_en = false;

	framer = slimbus_debug_get_framer();

	s2_ctrl = hi64xx_hifi_read_reg(HI64xx_DSP_S2_CTRL_L);
	if (s2_ctrl & (0x1 << HI64xx_DSP_S2_CLK_EN_BIT)) {
		HI64XX_DSP_INFO("S2 is enable, om hook can't start.\n");
		s2_clk_en = true;
	}

	if ((framer != SLIMBUS_FRAMER_CODEC) || s2_clk_en)
		hi64xx_stop_hook();

	return;
}

static int _left_data_parse_thread(void *p)
{
	int ret;
	struct hi64xx_om_priv *priv = om_priv;
	struct hook_runtime *runtime = NULL;

	BUG_ON(NULL == priv);

	runtime = &priv->runtime[HOOK_LEFT];

	while (!runtime->kthread_should_stop) {

		ret = down_interruptible(&runtime->hook_proc_sema);
		if (ret == -ETIME) {
			HI64XX_DSP_ERROR("proc sema down_int err -ETIME .\n");
		}

		ret = down_interruptible(&runtime->hook_stop_sema);
		if (ret == -ETIME) {
			HI64XX_DSP_ERROR("stop sema down_int err -ETIME .\n");
		}

		if (!priv->started || priv->standby) {
			up(&runtime->hook_stop_sema);
			HI64XX_DSP_ERROR("parse data when hook stopped!\n");
			continue;
		}

		wake_lock(&runtime->wake_lock);

		_add_data_to_list(runtime);

		_data_parse(runtime);

		if (runtime->cookie != _get_idle_buffer_id(runtime))
			HI64XX_DSP_WARNING("dma buffer is changed.\n");

		wake_unlock(&runtime->wake_lock);

		up(&runtime->hook_stop_sema);

		_hook_should_stop();
	}

	return 0;
}

static int _right_data_parse_thread(void *p)
{
	int ret;
	struct hi64xx_om_priv *priv = om_priv;
	struct hook_runtime *runtime = NULL;

	BUG_ON(NULL == priv);

	runtime = &priv->runtime[HOOK_RIGHT];

	while (!runtime->kthread_should_stop) {

		ret = down_interruptible(&runtime->hook_proc_sema);
		if (ret == -ETIME) {
			HI64XX_DSP_ERROR("proc sema down_int err -ETIME .\n");
		}

		ret = down_interruptible(&runtime->hook_stop_sema);
		if (ret == -ETIME) {
			HI64XX_DSP_ERROR("stop sema down_int err -ETIME .\n");
		}

		if (!priv->started || priv->standby) {
			up(&runtime->hook_stop_sema);
			HI64XX_DSP_ERROR("parse data when hook stopped!\n");
			continue;
		}

		wake_lock(&runtime->wake_lock);

		_add_data_to_list(runtime);

		_data_parse(runtime);

		if (runtime->cookie != _get_idle_buffer_id(runtime))
			HI64XX_DSP_WARNING("dma buffer is changed.\n");

		wake_unlock(&runtime->wake_lock);

		up(&runtime->hook_stop_sema);
	}

	return 0;
}

static int _left_dma_irq_handler(
			unsigned short int_type,
			unsigned int para)
{
	struct hi64xx_om_priv *priv = om_priv;
	struct hook_runtime *runtime = NULL;

	BUG_ON(NULL == priv);

	if ((ASP_DMA_INT_TYPE_TC1 != int_type)
		&& (ASP_DMA_INT_TYPE_TC2 != int_type)) {
		HI64XX_DSP_ERROR("int type err:%d\n", int_type);
		return -EINVAL;
	}

	runtime = &priv->runtime[HOOK_LEFT];
	runtime->cookie = _get_idle_buffer_id(runtime);
	up(&runtime->hook_proc_sema);

	return 0;
}

static int _right_dma_irq_handler(
			unsigned short int_type,
			unsigned int para)
{
	struct hi64xx_om_priv *priv = om_priv;
	struct hook_runtime *runtime = NULL;

	BUG_ON(NULL == priv);

	if ((ASP_DMA_INT_TYPE_TC1 != int_type)
		&& (ASP_DMA_INT_TYPE_TC2 != int_type)) {
		HI64XX_DSP_ERROR("int type err:%d\n", int_type);
		return -EINVAL;
	}

	runtime = &priv->runtime[HOOK_RIGHT];
	runtime->cookie = _get_idle_buffer_id(runtime);
	up(&runtime->hook_proc_sema);

	return 0;
}

static int _om_hook_start(unsigned int hook_id)
{
	struct hook_runtime *runtime = NULL;
	struct hi64xx_om_priv *priv = om_priv;
	callback_t callback = NULL;

	BUG_ON(NULL == priv);

	runtime = &priv->runtime[hook_id];

	runtime->hook_file_cnt  = 0;
	runtime->hook_file_size = 0;

	_hook_runtime_config(hook_id);

	_dump_runtime(runtime);

	if (HOOK_LEFT == hook_id)
		callback = _left_dma_irq_handler;
	else
		callback = _right_dma_irq_handler;

	asp_dma_config(runtime->channel,
				runtime->lli_cfg[PCM_SWAP_BUFF_A],
				callback, 0);
	asp_dma_start(runtime->channel,
				runtime->lli_cfg[PCM_SWAP_BUFF_A]);

	priv->started = true;
	priv->standby = false;

	return 0;
}

static void _om_hook_stop(unsigned int hook_id)
{
	int ret;
	struct hook_runtime *runtime = NULL;
	struct pos_infos *pos_infos = NULL;
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	runtime = &priv->runtime[hook_id];

	runtime->hook_file_cnt  = 0;
	runtime->hook_file_size = 0;

	asp_dma_stop(runtime->channel);

	ret = down_interruptible(&runtime->hook_stop_sema);
	if (ret == -ETIME) {
		HI64XX_DSP_ERROR("down_interruptible error -ETIME .\n");
	}

	iounmap(runtime->buffer[PCM_SWAP_BUFF_A]);
	iounmap(runtime->lli_cfg[PCM_SWAP_BUFF_A]);

	while (!list_empty(&runtime->info_list.node)) {
		pos_infos = list_entry(runtime->info_list.node.next,
						struct pos_infos, node);
		list_del(&pos_infos->node);
		kfree(pos_infos);
	}

	priv->started = false;
	priv->standby = true;

	up(&runtime->hook_stop_sema);
}

int _om_slimbus_callback(unsigned int type, void *params)
{
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);
	UNUSED_PARAMETER(params);

	if (SLIMBUS_TRACK_DEBUG == type) {
		priv->should_deactive_slimbus = false;

	}

	return 0;

}

int hi64xx_hifi_om_set_bw(unsigned short bandwidth)
{
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	if (bandwidth >= OM_BANDWIDTH_BUTT) {
		HI64XX_DSP_ERROR("err om bw:%d.\n", bandwidth);
		return -EINVAL;
	}

	if (priv->started || !priv->standby) {
		HI64XX_DSP_ERROR("om is running, forbid set bw:%d.\n", bandwidth);
		return -EBUSY;
	}

	priv->bandwidth = bandwidth;

	HI64XX_DSP_INFO("set om bw:%d.\n", bandwidth);

	return 0;
}

int hi64xx_hifi_om_set_sponsor(unsigned short sponsor)
{
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	if (sponsor >= OM_SPONSOR_BUTT) {
		HI64XX_DSP_ERROR("err om sponsor:%d.\n", sponsor);
		return -EINVAL;
	}

	if (priv->started || !priv->standby) {
		HI64XX_DSP_ERROR("om is running, forbid set sponsor:%d.\n", sponsor);
		return -EBUSY;
	}

	priv->sponsor = sponsor;

	HI64XX_DSP_INFO("set om sponsor:%d.\n", sponsor);

	return 0;
}

int hi64xx_hifi_om_set_hook_path(char *path, unsigned int size)
{
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	if (!path || size > (HOOK_PATH_MAX_LENGTH - 2)) {
		HI64XX_DSP_ERROR("err para.\n");
		return -EINVAL;
	}

	if (priv->started || !priv->standby) {
		HI64XX_DSP_ERROR("om is running, forbid set path.\n");
		return -EBUSY;
	}

	HI64XX_DSP_INFO("path:%s\n", priv->hook_path);

	return 0;
}

int hi64xx_hifi_om_set_dir_count(unsigned int count)
{
	struct hi64xx_om_priv *priv = om_priv;

	BUG_ON(NULL == priv);

	if (priv->started || !priv->standby) {
		HI64XX_DSP_ERROR("om is running, forbid set dir count:%d.\n", count);
		return -EBUSY;
	}

	if (count > HOOK_MAX_SUBDIR_CNT)
		priv->dir_count = HOOK_MAX_SUBDIR_CNT;
	else
		priv->dir_count = count;

	HI64XX_DSP_INFO("set om dir count:%d.\n", priv->dir_count);

	return 0;
}

int hi64xx_hifi_om_hook_start(void)
{
	int ret = 0;
	slimbus_framer_type_t framer;
	struct hi64xx_om_priv *priv = om_priv;
	slimbus_track_param_t slimbus_params;
	struct data_cfg *data_cfg = &slim_data_cfg[HOOK_LEFT];

	BUG_ON(NULL == priv);

	if (priv->started || !priv->standby)
		return -EBUSY;

	/* slimbus clk must at codec to avoid frequency offset */
	framer = slimbus_debug_get_framer();
	if (framer != SLIMBUS_FRAMER_CODEC) {
		HI64XX_DSP_ERROR( "slimbus framer is not codec, can not start om.\n");
		return -EBUSY;
	}

	_set_hook_path();

	ret = _create_hook_dir();
	if (ret) {
		HI64XX_DSP_ERROR( "create hook dir failed, ret:%d.\n", ret);
		return -EBUSY;
	}

	ret = clk_prepare_enable(priv->asp_subsys_clk);
	if (IS_ERR_VALUE(ret)) {
		HI64XX_DSP_ERROR( "clk prepare enable failed.\n");
		return -EBUSY;
	}

	memset(&slimbus_params, 0, sizeof(slimbus_params));
	slimbus_params.rate = data_cfg->sample_rate;
	if (OM_BANDWIDTH_12288 == priv->bandwidth) {
		slimbus_params.channels = 2;
	} else {
		slimbus_params.channels = 1;
	}
	slimbus_params.callback = _om_slimbus_callback;

	priv->should_deactive_slimbus = true;

	ret = slimbus_track_activate(SLIMBUS_DEVICE_HI6403, SLIMBUS_TRACK_DEBUG, &slimbus_params);
	if (ret) {
		HI64XX_DSP_ERROR("slimbus activate failded, ret: %d.\n", ret);
		return ret;
	}

	priv->open_file_failed_cnt = 0;

	_om_hook_start(HOOK_LEFT);

	HI64XX_DSP_INFO("left hook started\n");

	if (OM_BANDWIDTH_12288 == priv->bandwidth) {
		_om_hook_start(HOOK_RIGHT);

		HI64XX_DSP_INFO("right hook started\n");
	}

	return 0;
}

void hi64xx_hifi_om_hook_stop(void)
{
	struct hi64xx_om_priv *priv = om_priv;
	int ret = 0;

	BUG_ON(NULL == priv);

	if (!priv->started || priv->standby)
		return;

	_om_hook_stop(HOOK_LEFT);

	HI64XX_DSP_INFO("left hook stoped\n");

	if (OM_BANDWIDTH_12288 == priv->bandwidth) {
		_om_hook_stop(HOOK_RIGHT);

		HI64XX_DSP_INFO("right hook stoped\n");
	}

	if (priv->should_deactive_slimbus)
		ret = slimbus_track_deactivate(SLIMBUS_DEVICE_HI6403, SLIMBUS_TRACK_DEBUG, NULL);

	if (ret)
		HI64XX_DSP_WARNING("deactivate debug return ret %d\n", ret);

	clk_disable_unprepare(priv->asp_subsys_clk);

	priv->sponsor = OM_SPONSOR_DEFAULT;
}

int hi64xx_hifi_om_init(struct hi64xx_irq *irqmgr)
{
	int ret = 0;
	int i = 0;
	struct sched_param param;
	struct hi64xx_om_priv *priv = NULL;

	HI64XX_DSP_INFO("init begin.\n");

	priv = kzalloc(sizeof(struct hi64xx_om_priv), GFP_KERNEL);
	if (!priv) {
		HI64XX_DSP_ERROR("malloc failed.\n");
		return -ENOMEM;
	}

	priv->dev = irqmgr->dev;
	strncpy(priv->hook_path, HOOK_PATH_DEFAULT, sizeof(priv->hook_path));
	priv->sponsor = OM_SPONSOR_DEFAULT;
	priv->bandwidth = OM_BANDWIDTH_6144;
	priv->dir_count = HOOK_DEFAULT_SUBDIR_CNT;

	priv->is_eng = false;

	priv->asp_subsys_clk = devm_clk_get(priv->dev, "clk_asp_subsys");
	if ( IS_ERR(priv->asp_subsys_clk)) {
		HI64XX_DSP_ERROR( "asp subsys clk fail.\n");
		goto err_exit;
	}

	for (i = 0; i < HOOK_CNT; i++) {
		priv->runtime[i].hook_id = i;

		INIT_LIST_HEAD(&priv->runtime[i].info_list.node);
		INIT_LIST_HEAD(&priv->runtime[i].data_list.node);

		wake_lock_init(&priv->runtime[i].wake_lock,
					WAKE_LOCK_SUSPEND, "hi64xx_hifi_om");

		sema_init(&priv->runtime[i].hook_proc_sema, 0);

		sema_init(&priv->runtime[i].hook_stop_sema, 1);

		if (HOOK_RIGHT == i)
			priv->runtime[i].kthread = kthread_create(
						_right_data_parse_thread, 0, "right_data_parse_thread");
		else
			priv->runtime[i].kthread = kthread_create(
						_left_data_parse_thread, 0, "left_data_parse_thread");

		if (IS_ERR(priv->runtime[i].kthread)) {
			HI64XX_DSP_ERROR("create data parse thread fail:%d.\n", i);
			ret = -ENOMEM;
			goto err_exit;
		}

		priv->runtime[i].kthread_should_stop = 0;

		/* set high prio */
		memset(&param, 0, sizeof(struct sched_param));
		param.sched_priority = MAX_RT_PRIO - 20;
		ret = sched_setscheduler(priv->runtime[i].kthread, SCHED_RR, &param);
		if (ret)
			HI64XX_DSP_ERROR("set thread schedule priorty failed:%d.\n", i);
	}

	priv->started = false;
	priv->standby = true;
	priv->should_deactive_slimbus = true;

	om_priv = priv;

	wake_up_process(priv->runtime[HOOK_LEFT].kthread);
	wake_up_process(priv->runtime[HOOK_RIGHT].kthread);

	HI64XX_DSP_INFO("init end.\n");

	return 0;

err_exit:
	kfree(priv);

	om_priv = NULL;

	HI64XX_DSP_ERROR("init failed.\n");

	return ret;
}

void hi64xx_hifi_om_deinit(void)
{
	int i = 0;
	struct hi64xx_om_priv *priv = om_priv;

	if (!priv)
		return;

	for (i = 0; i < HOOK_CNT; i++) {
		if (priv->runtime[i].kthread) {
			priv->runtime[i].kthread_should_stop = 1;
			up(&priv->runtime[i].hook_proc_sema);
			kthread_stop(priv->runtime[i].kthread);
		}

		wake_lock_destroy(&priv->runtime[i].wake_lock);
	}

	kfree(priv);

	om_priv = NULL;
}

MODULE_AUTHOR("LiuJinHong <liujinhong@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon (R) HI64XX OM Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_VERSION(HI64XX_OM_DRIVER_VERSION);
