/*
 * hi6555 codec debug driver.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/switch.h>
#include <linux/wakelock.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/debugfs.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include "hi6555c.h"
#include "hi6555c_debug.h"

static struct snd_soc_codec *g_codec;
void *g_dump_addr;
unsigned int g_dump_size;
static unsigned int g_vs_reg = INVALID_REG;

/*
 * record reg write op
 * loop range (0-1023)
 * catch atomic ensured by read/write function
 */
void hi6555c_debug_reg_wr_cache(unsigned int reg, unsigned int val)
{
	u64 sec;
	struct hi6555c_priv *priv;
	unsigned int idx_wr;

	if (!g_codec) {
		loge("g_codec is null\n");
		return;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);
	if (!priv) {
		loge("priv is null\n");
		return;
	}

	idx_wr = priv->rr_cache_idx;

	idx_wr %= REG_CACHE_NUM_MAX;
	/* highest 16bit is r/w flag */
	priv->rr_cache[idx_wr].reg = reg | REG_CACHE_FLAG_WRITE;
	priv->rr_cache[idx_wr].val = val;

	sec = hisi_getcurtime();
	do_div(sec, 1000000000);
	priv->rr_cache[idx_wr].time = (unsigned long int)sec;
	idx_wr++;
	priv->rr_cache_idx = idx_wr % REG_CACHE_NUM_MAX;
}

/*
 * record reg read op
 * loop range (0-1023)
 * catch atomic ensured by read/write function
 */
void hi6555c_debug_reg_rd_cache(unsigned int reg, unsigned int val)
{
	u64 sec;
	struct hi6555c_priv *priv;
	unsigned int idx_wr;

	if (!g_codec) {
		loge("g_codec is null\n");
		return;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);
	if (!priv) {
		loge("priv is null\n");
		return;
	}

	idx_wr = priv->rr_cache_idx;

	idx_wr %= REG_CACHE_NUM_MAX;
	/* highest 16bit is r/w flag */
	priv->rr_cache[idx_wr].reg = reg | REG_CACHE_FLAG_READ;
	priv->rr_cache[idx_wr].val = val;

	sec = hisi_getcurtime();
	do_div(sec, 1000000000);
	priv->rr_cache[idx_wr].time = (unsigned long int)sec;
	idx_wr++;
	priv->rr_cache_idx = idx_wr % REG_CACHE_NUM_MAX;
}


static void hi6555c_debug_dapm_widget_dp(char *buf)
{
	struct list_head *l;
	struct snd_soc_dapm_widget *w;
	int i = -1;

	memset(buf, 0, HI6555C_DBG_SIZE_WIDGET); /*lint !e747 */

	if (!g_codec) {
		snprintf(buf, HI6555C_DBG_SIZE_WIDGET, "g_codec is null\n"); /*lint !e747 */
		return;
	}

	snprintf(buf, HI6555C_DBG_SIZE_WIDGET, "BEGIN widget\n"); /*lint !e747 */
	l = &(g_codec->dapm.card->widgets);
	list_for_each_entry(w, l, list) { /*lint !e64 !e826 */
		i++;
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_WIDGET - strlen(buf), "<%02d> pwr= %d \"%s\"\n", i, w->power, w->name);
	}
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_WIDGET - strlen(buf), "END\n");
}

static void hi6555c_debug_dapm_path_dp(char *buf)
{
	struct list_head *l;
	struct snd_soc_dapm_path *p;
	struct snd_soc_dapm_widget *source;
	struct snd_soc_dapm_widget *sink;
	int i = -1;

	memset(buf, 0, HI6555C_DBG_SIZE_PATH); /*lint !e747 */

	if (!g_codec) {
		snprintf(buf, HI6555C_DBG_SIZE_PATH, "g_codec is null\n"); /*lint !e747 */
		return;
	}

	snprintf(buf, HI6555C_DBG_SIZE_PATH, "BEGIN path\n"); /*lint !e747 */
	l = &(g_codec->dapm.card->paths);
	list_for_each_entry(p, l, list) { /*lint !e64 !e826 */
		i++;
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "<%d>cn_stat: %d\n", i, p->connect);
		if (p->source == NULL || p->sink == NULL) {
			snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "<%d>end\n", i);
			continue;
		}

		source = p->source;
		sink   = p->sink;

		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "src w \"%s\"\n", source->name);
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "sink w \"%s\"\n", sink->name);
	}
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "END\n");
}

static void hi6555c_debug_reg_history_dp(char *buf)
{
	struct hi6555c_priv *priv;
	unsigned int idx_wr_now, idx_wr_latter;
	unsigned int idx, idx_start = 0, idx_stop = 0;
	unsigned long time, time_next;
	unsigned int reg = 0, val = 0;
	unsigned long flags = 0;
	u64 sec;

	memset(buf, 0, HI6555C_DBG_SIZE_CACHE); /*lint !e747 */

	if (!g_codec) {
		snprintf(buf, HI6555C_DBG_SIZE_CACHE, "g_codec is null\n"); /*lint !e747 */
		return;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);
	if (!priv) {
		snprintf(buf, HI6555C_DBG_SIZE_CACHE, "priv is null\n"); /*lint !e747 */
		return;
	}

	spin_lock_irqsave(&priv->lock, flags); /*lint !e550 */
	idx_wr_now = priv->rr_cache_idx;
	time_next = priv->rr_cache[(idx_wr_now + 1) % REG_CACHE_NUM_MAX].time; /*lint !e679 */
	spin_unlock_irqrestore(&priv->lock, flags);

	if (idx_wr_now >= REG_CACHE_NUM_MAX) {
		snprintf(buf, HI6555C_DBG_SIZE_CACHE, "rr_idx(%d) err\n", idx_wr_now); /*lint !e747 */
		return;
	}

	if (0 == idx_wr_now) {
		snprintf(buf, HI6555C_DBG_SIZE_CACHE, "no register cached now\n"); /*lint !e747 */
		return;
	}

	/* parameters: idx_wr_now */
	sec = hisi_getcurtime();
	do_div(sec, 1000000000);
	snprintf(buf, HI6555C_DBG_SIZE_CACHE, "time=%lu s, idx now=%d, BEGIN\n", (unsigned long int)sec, idx_wr_now); /*lint !e747 */

	/* judge the position of idx in order to loop*/
	if (0 == time_next) {
		idx_start = 0;
		idx_stop = idx_wr_now;
	} else {
		/* loop */
		idx_start = idx_wr_now + 1;
		idx_stop = idx_wr_now + REG_CACHE_NUM_MAX;
	}

	for (idx = idx_start; idx < idx_stop; idx++) {
		spin_lock_irqsave(&priv->lock, flags); /*lint !e550 */

		reg = priv->rr_cache[idx % REG_CACHE_NUM_MAX].reg;
		val = priv->rr_cache[idx % REG_CACHE_NUM_MAX].val;
		time = priv->rr_cache[idx % REG_CACHE_NUM_MAX].time;

		if (REG_CACHE_FLAG_READ == (reg & REG_CACHE_FLAG_MASK)) {
			/* read */
			snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "%lu.r %04X:%02X\n", time, reg & ~REG_CACHE_FLAG_MASK, val);
		} else if (REG_CACHE_FLAG_WRITE == (reg & REG_CACHE_FLAG_MASK)) {
			/* write */
			snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "%lu.w %04X %02X\n", time, reg & ~REG_CACHE_FLAG_MASK, val);
		} else {
			/* error branch */
			snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "%lu.e %x %x\n", time, reg & ~REG_CACHE_FLAG_MASK, val);
		}
		spin_unlock_irqrestore(&priv->lock, flags);
	}

	/* dump */
	spin_lock_irqsave(&priv->lock, flags); /*lint !e550 */
	idx_wr_latter = priv->rr_cache_idx;
	spin_unlock_irqrestore(&priv->lock, flags);
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "idx=%d -- %d, END\n", idx_wr_now, idx_wr_latter);
}

static void hi6555c_debug_page_dp(char *buf)
{
	unsigned int regi;

	memset(buf, 0, HI6555C_DBG_SIZE_PAGE); /*lint !e747 */

	/* SOC CODEC */
	snprintf(buf, HI6555C_DBG_SIZE_PAGE, "SOC CODEC\n"); /*lint !e747 */
	for  (regi = HI6555C_CODEC_CFG_START; regi <= HI6555C_CODEC_CFG_END; regi += 4) {
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#010x\n", regi, codec_reg_read(regi));
	}

	for (regi = HI6555C_CODEC_FIFO_START; regi <= HI6555C_CODEC_FIFO_END; regi += 4) {
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#010x\n", regi, codec_reg_read(regi));
	}

	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");

	/* PMU CODEC */
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "PMU CODEC\n");
	for (regi = HI6555C_PMU_CODEC_START; regi <= HI6555C_PMU_CODEC_END; regi++) {
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, codec_reg_read(regi));
	}
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");

	/* PMU HKADC */
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "PMU HKADC\n");
	for (regi = HI6555C_PMU_HKADC_START; regi <= HI6555C_PMU_HKADC_END; regi++) {
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, codec_reg_read(regi));
	}
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");

	/* PMU CTRL */
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "PMU CTRL\n");
	for (regi = HI6555C_PMU_CTRL_LDO_START; regi <= HI6555C_PMU_CTRL_LDO_END; regi++) {
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, codec_reg_read(regi));
	}

	for (regi = HI6555C_PMU_CTRL_CLASSD_START; regi <= HI6555C_PMU_CTRL_CLASSD_END; regi++) {
		snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, codec_reg_read(regi));
	}

	for (regi = HI6555C_PMU_CTRL_LDOV_START; regi <= HI6555C_PMU_CTRL_LDOV_END; regi++) {
		if ((HI6555C_PMU_CTRL_LDOV2 == regi) ||
		    (HI6555C_PMU_CTRL_LDOV5 == regi) ||
		    (HI6555C_PMU_CTRL_LDOV8 == regi) ||
		    (HI6555C_PMU_CTRL_LDOV23 == regi) ||
		    (HI6555C_PMU_CTRL_LDOV34 == regi)) {
			snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, codec_reg_read(regi));
		}
	}

	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "<cat end>\n");
	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");
}

static void hi6555c_debug_state_dp(char *buf)
{
	struct hi6555c_priv *priv;

	memset(buf, 0, HI6555C_DBG_SIZE_PAGE); /*lint !e747 */

	if (!g_codec) {
		snprintf(buf, HI6555C_DBG_SIZE_PAGE, "g_codec is null\n"); /*lint !e747 */
		return;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);
	if (!priv) {
		snprintf(buf, HI6555C_DBG_SIZE_PAGE, "priv is null\n"); /*lint !e747 */
		return;
	}

	snprintf(buf, HI6555C_DBG_SIZE_PAGE, "hs_status=%d(old=%d), jack.report=0x%x\n" /*lint !e747 */
			, priv->hs_status, priv->old_hs_status, priv->hs_jack.report);

	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "IRQ=0x%x, IRQM=0x%x, STAT=0x%x\n"
			, codec_reg_read(HI6555C_SMT_ANA_IRQ_REG0_ADDR),
			codec_reg_read(HI6555C_SMT_ANA_IRQM_REG0_ADDR),
			codec_reg_read(HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));

	snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "<end>\n");
}

/*
 *1 default: page outpue
 *2 single reg read: echo "r reg" > rr£¬cat rr
 *3 single reg write: echo "w reg val"
 */
/*lint -e715 */
static ssize_t hi6555c_debug_rr_read(struct file *file, char __user *user_buf,
		size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_read;
	unsigned int vs_reg_r = g_vs_reg;

	kn_buf = kzalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL); /*lint !e747 */
	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", sizeof("kn_buf alloc fail\n"));
	}

	if (INVALID_REG != vs_reg_r) {
		/* Register */
		if (PAGE_SoCCODEC == (vs_reg_r & PAGE_TYPE_MASK)) {
			snprintf(kn_buf, HI6555C_DBG_SIZE_PAGE, "%#04x:%#010x\n", vs_reg_r, codec_reg_read(vs_reg_r)); /*lint !e747 */
			snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_PAGE - strlen(kn_buf), "<cat end>\n");
		} else {
			snprintf(kn_buf, HI6555C_DBG_SIZE_PAGE, "%#04x:%#04x\n", vs_reg_r, codec_reg_read(vs_reg_r)); /*lint !e747 */
			snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_PAGE - strlen(kn_buf), "<cat end>\n");
		}
	} else {
		/* PAGE */
		hi6555c_debug_page_dp(kn_buf);
	}

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));
	kfree(kn_buf);

	return byte_read;
}

/*
 *1 default: page outpue
 *2 single reg read: echo "r reg" > rr£¬cat rr
 *3 single reg write: echo "w reg val"
 */
static ssize_t hi6555c_debug_rr_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_writen;
	int num = 0;
	unsigned int vs_reg = 0;
	unsigned int vs_val = 0;

	kn_buf = kzalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL); /*lint !e747 */
	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf, HI6555C_DBG_SIZE_PAGE, ppos, user_buf, count); /*lint !e747 */
	if (byte_writen != count) { /*lint !e737 */
		loge("simple_write_to_buffer err:%zd\n", byte_writen);
		goto end;
	}

	switch (kn_buf[0]) {
	case 'w':
		/* write single reg */
		num = sscanf(kn_buf, "w 0x%x 0x%x", &vs_reg, &vs_val);
		if (2 == num) {
			codec_reg_write(vs_reg, vs_val);
			g_vs_reg = vs_reg;
		} else {
			g_vs_reg = INVALID_REG;
			byte_writen = -EINVAL;
		}
		logi("write single reg,g_vs_reg value:0x%x",g_vs_reg);
		break;
	case 'r':
		/* read single reg */
		num = sscanf(kn_buf, "r 0x%x", &g_vs_reg);
		if (1 != num) {
			g_vs_reg = INVALID_REG;
			byte_writen = -EINVAL;
		}
		logi("read single reg,g_vs_reg value:0x%x",g_vs_reg);
		break;
	case 'p':
		/* read PAGE */
		g_vs_reg = INVALID_REG;
		break;
	default:
		/* abnormal */
		g_vs_reg = INVALID_REG;
		byte_writen = -EINVAL;
		break;
	}

end:
	kfree(kn_buf);

	return byte_writen;
}

/*
 * history reg read
 */
static ssize_t hi6555c_debug_rh_read(struct file *file, char __user *user_buf,
		size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_read;

	kn_buf = vmalloc(HI6555C_DBG_SIZE_CACHE); /*lint !e747 */

	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos, "vmalloc fail\n", sizeof("vmalloc fail\n"));
	}

	hi6555c_debug_reg_history_dp(kn_buf);

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	vfree(kn_buf);


	return byte_read;
}

/*
 *widget state interface
 */
static ssize_t hi6555c_debug_dwidget_read(struct file *file, char __user *user_buf,
		size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_read;

	kn_buf = vmalloc(HI6555C_DBG_SIZE_WIDGET); /*lint !e747 */

	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", sizeof("kn_buf alloc fail\n"));
	}

	hi6555c_debug_dapm_widget_dp(kn_buf);

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	vfree(kn_buf);


	return byte_read;
}

/*
 *path state interface
 */
static ssize_t hi6555c_debug_dpath_read(struct file *file, char __user *user_buf,
		size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_read;

	kn_buf = vmalloc(HI6555C_DBG_SIZE_PATH); /*lint !e747 */
	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", sizeof("kn_buf alloc fail\n"));
	}

	hi6555c_debug_dapm_path_dp(kn_buf);

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	vfree(kn_buf);


	return byte_read;
}

/*
 *codec state interface
 */
static ssize_t hi6555c_debug_state_read(struct file *file, char __user *user_buf,
		size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_read;

	kn_buf = kzalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL); /*lint !e747 */

	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", sizeof("kn_buf alloc fail\n"));
	}

	hi6555c_debug_state_dp(kn_buf);

	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	kfree(kn_buf);


	return byte_read;
}
/*lint -e785 */
static const struct file_operations hi6555c_debug_rr_fops = {
	.read  = hi6555c_debug_rr_read,
#ifdef CONFIG_HISI_DEBUG_FS
	.write = hi6555c_debug_rr_write,
#endif
};

static const struct file_operations hi6555c_debug_rh_fops = {
	.read  = hi6555c_debug_rh_read,
};

static const struct file_operations hi6555c_debug_dwidget_fops = {
	.read  = hi6555c_debug_dwidget_read,
};

static const struct file_operations hi6555c_debug_dpath_fops = {
	.read  = hi6555c_debug_dpath_read,
};

static const struct file_operations hi6555c_debug_state_fops = {
	.read  = hi6555c_debug_state_read,
};
/*lint +e785 */
#ifdef CONFIG_DEBUG_POP
static struct hi6555c_debug_ps_cache ps_cache[100];
static unsigned int ps_index;

/* write reg by seq */
static void hi6555c_debug_pop_debug(void)
{
	unsigned int idx_ps;

	for (idx_ps = 0; idx_ps < ps_index; idx_ps++) {
		switch (ps_cache[idx_ps].op) {
		case HI6555C_POP_DELAY_MS:
			logi("m %d\n", ps_cache[idx_ps].val);
			msleep(ps_cache[idx_ps].val);
			break;
		case HI6555C_POP_DELAY_US:
			logi("u %d\n", ps_cache[idx_ps].val);
			udelay(ps_cache[idx_ps].val); /*lint !e747 */
			break;
		case HI6555C_POP_REG_WRITE:
			logi("w 0x%x 0x%x\n", ps_cache[idx_ps].reg, ps_cache[idx_ps].val);
			codec_reg_write(ps_cache[idx_ps].reg, ps_cache[idx_ps].val);
			break;
		default:
			loge("op not found\n");
			break;
		}
	}
}

/*
 *1 default: Output PAGE
 *2 clean history reg: echo "c" > ps
 *3 reg write:   echo "w reg val" > ps
 *4 delay ms:   echo "m val" > ps
 *5 delay us:   echo "u val" > ps
 */
static ssize_t hi6555c_debug_ps_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_writen;
	int num = 0;
	unsigned int vs_reg = 0;
	unsigned int vs_val = 0;

	kn_buf = kzalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL); /*lint !e747 */
	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf, HI6555C_DBG_SIZE_PAGE, ppos, user_buf, count); /*lint !e747 */
	if (byte_writen != count) { /*lint !e737 */
		loge("simple_write_to_buffer err:%zd\n", byte_writen);
		goto end;
	}

	if (ps_index == 100) {
		loge("ps is full, echo 'c' > ps to clean\n");
		goto end;
	}

	switch (kn_buf[0]) {
	case 'w':
		/* reg write */
		num = sscanf(kn_buf, "w 0x%x 0x%x", &vs_reg, &vs_val);
		if (2 == num) {
			logd("cmd is stored, echo 'e' > ps to pop cmd\n");
			ps_cache[ps_index].op  = HI6555C_POP_REG_WRITE;
			ps_cache[ps_index].reg = vs_reg;
			ps_cache[ps_index].val = vs_val;
			ps_index++;
		}
		break;
	case 'm':
		/* delay ms */
		num = sscanf(kn_buf, "m %d", &vs_val); /*lint !e706 */
		if (1 == num) {
			logd("cmd is stored, echo 'e' > ps to pop cmd\n");
			ps_cache[ps_index].op = HI6555C_POP_DELAY_MS;
			ps_cache[ps_index].val = vs_val;
			ps_index++;
		}
		break;
	case 'u':
		/* delay us */
		num = sscanf(kn_buf, "u %d", &vs_val); /*lint !e706 */
		if (1 == num) {
			if (vs_val > (MAX_UDELAY_MS * 1000)) {
				loge("Not allowed! %d is over max udelay time (%dus)\n", vs_val, MAX_UDELAY_MS * 1000);
			} else {
				logd("cmd is stored, echo 'e' > ps to pop cmd\n");
				ps_cache[ps_index].op = HI6555C_POP_DELAY_US;
				ps_cache[ps_index].val = vs_val;
				ps_index++;
			}
		}
		break;
	case 'c':
		/* history clean */
		logd("clean ps\n");
		ps_index = 0;
		break;
	case 'e':
		/* exec pop */
		logd("pop cmd\n");
		hi6555c_debug_pop_debug();
		break;
	default:
		loge("cmd error\n");
		break;
	}

end:
	kfree(kn_buf);


	return byte_writen;
}

/*
 * ps current value interface
 */
static ssize_t hi6555c_debug_ps_read(struct file *file, char __user *user_buf,
		size_t count, loff_t *ppos)
{
	char *kn_buf;
	ssize_t byte_read;
	unsigned int idx_ps;

	kn_buf = vmalloc(HI6555C_DBG_SIZE_CACHE); /*lint !e747 */
	if (NULL == kn_buf) {
		loge("kn_buf is null\n");
		return simple_read_from_buffer(user_buf, count, ppos, "vmalloc fail\n", sizeof("vmalloc fail\n"));
	}

	memset(kn_buf, 0, HI6555C_DBG_SIZE_CACHE); /*lint !e747 */

	snprintf(kn_buf, HI6555C_DBG_SIZE_CACHE, "PS DUMP BEGIN\n"); /*lint !e747 */
	for (idx_ps = 0; idx_ps < ps_index; idx_ps++) {
		switch (ps_cache[idx_ps].op) {
		case HI6555C_POP_DELAY_MS:
			snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "m %d\n", ps_cache[idx_ps].val);
			break;
		case HI6555C_POP_DELAY_US:
			snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "u %d\n", ps_cache[idx_ps].val);
			break;
		case HI6555C_POP_REG_WRITE:
			snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "w 0x%x 0x%x\n", ps_cache[idx_ps].reg, ps_cache[idx_ps].val);
			break;
		default:
			loge("op not found\n");
			break;
		}
	}
	snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "PS DUMP END\n");
	byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

	vfree(kn_buf);


	return byte_read;
}
/*lint +e715 */
static const struct file_operations hi6555c_debug_ps_fops = {
	.read  = hi6555c_debug_ps_read,
	.write = hi6555c_debug_ps_write,
}; /*lint !e785 */
#endif

int hi6555c_debug_init(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv;

	if (!codec) {
		loge("codec is null\n");
		return -EINVAL;
	}

	priv = snd_soc_codec_get_drvdata(codec);
	if (!priv) {
		loge("priv is null\n");
		return -EINVAL;
	}

	g_codec = codec;
	g_dump_addr = (void *)priv->rr_cache;
	g_dump_size = sizeof(struct hi6555c_debug_rr_cache) * REG_CACHE_NUM_MAX;

	priv->df_dir = debugfs_create_dir("hi6555c", NULL);
	if (!priv->df_dir) {
		loge("create hi6555c debugfs dir\n");
		return -ENOMEM;
	}

	/* register */
	if (!debugfs_create_file("rr", 0644, priv->df_dir, NULL, &hi6555c_debug_rr_fops)) {
		loge("create hi6555c debugfs rr\n");
		return -ENOMEM;
	}

	/* register history */
	if (!debugfs_create_file("rh", 0644, priv->df_dir, NULL, &hi6555c_debug_rh_fops)) {
		loge("create hi6555c debugfs cache\n");
		return -ENOMEM;
	}

	/* dump widget */
	if (!debugfs_create_file("dwidget", 0640, priv->df_dir, NULL, &hi6555c_debug_dwidget_fops)) {
		loge("create hi6555c debugfs dwidget\n");
		return -ENOMEM;
	}

	/* dump path */
	if (!debugfs_create_file("dpath", 0640, priv->df_dir, NULL, &hi6555c_debug_dpath_fops)) {
		loge("create hi6555c debugfs dpath\n");
		return -ENOMEM;
	}

	/* codec state */
	if (!debugfs_create_file("stat", 0640, priv->df_dir, NULL, &hi6555c_debug_state_fops)) {
		loge("create hi6555c debugfs stat\n");
		return -ENOMEM;
	}

#ifdef CONFIG_DEBUG_POP
	if (!debugfs_create_file("ps", 0640, priv->df_dir, NULL, &hi6555c_debug_ps_fops)) {
		loge("create hi6555c debugfs ps\n");
		return -ENOMEM;
	}
#endif

	return 0;
}

void hi6555c_debug_uninit(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv;

	if (!codec) {
		loge("codec is null\n");
		return;
	}

	priv = snd_soc_codec_get_drvdata(codec);
	if (!priv) {
		loge("priv is null\n");
		return;
	}

	if (priv->df_dir) {
		debugfs_remove_recursive(priv->df_dir);
		priv->df_dir = NULL;
	}
}
