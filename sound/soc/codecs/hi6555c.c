/*
 * hi6555 codec driver.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/clk.h>
#include <linux/timer.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/tlv.h>
#include <asm/io.h>
#include <linux/spinlock.h>
#include <linux/switch.h>
#include <linux/wakelock.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/of_gpio.h>
#include <linux/mfd/hisi_pmic.h>
#include <linux/hisi/hisi_adc.h>

/*add for codec irq*/
#include <linux/gpio.h>
/*  Reason: For hook  */
#include <sound/jack.h>
/*KEY_MEDIA defined in linux/input.h*/
#include <linux/input/matrix_keypad.h>
#include <linux/irq.h>
#include <sound/hi6555c_common.h>
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <linux/hisi/drv_pmic_if.h>
#include "hs_auto_calib.h"
#include "hi6555c.h"
#include "hi6555c_debug.h"
#include <linux/hisi/hilog.h>
#include <soc_crgperiph_interface.h>
#include <linux/pm_runtime.h>

/* HI6555C CODEC */
static struct snd_soc_codec *g_codec;

/* HI6555C REGISTER BASE ADDR */
static void __iomem *reg_base_addr[HI6555C_REG_CNT];

static struct hi6555c_reg_page reg_page_array[] = {
	{PAGE_SoCCODEC, HI6555C_SoCCODEC_START, HI6555C_SoCCODEC_END, "PAGE_SoCCODEC"},
	{PAGE_PMUCODEC, HI6555C_PMUCODEC_START, HI6555C_PMUCODEC_END, "PAGE_PMUCODEC"},
	{PAGE_PMUHKADC, HI6555C_PMUHKADC_START, HI6555C_PMUHKADC_END, "PAGE_PMUHKADC"},
	{PAGE_PeriSCTRL, HI6555C_PCTRL_START, HI6555C_PCTRL_END, "PAGE_PeriSCTRL"},
	{PAGE_PMUCTRL, HI6555C_PMUCTRL_START, HI6555C_PMUCTRL_END, "PAGE_PMUCTRL"},
	{PAGE_VIRCODEC, HI6555C_VIRCODEC_START, HI6555C_VIRCODEC_END, "PAGE_VIRCODEC"},
	{PAGE_ASPCFG, HI6555C_ASPCFG_START, HI6555C_ASPCFG_END, "PAGE_ASPCFG"},
	{PAGE_AO_IOC, HI6555C_AOIOC_START, HI6555C_AOIOC_END, "PAGE_AO_IOC"},
	{PAGE_IOC, HI6555C_IOC_START, HI6555C_IOC_END, "PAGE_IOC"},
	{PAGE_PERICRG, HI6555C_PERICRG_START, HI6555C_PERICRG_END, "PAGE_PERICRG"},
};

static void hs_plug_out_detect_func(struct snd_soc_codec *codec);
static void hi6555c_enable_ibias(struct snd_soc_codec *codec, bool enable);
static void hi6555c_hs_micbias_work_enable(struct snd_soc_codec *codec, bool enable);
static void hi6555c_ibias_hsmicbias_enable(struct snd_soc_codec *codec, bool enable);
static void hi6555c_hs_micbias_enable(struct snd_soc_codec *codec, bool enable);
static void hi6555c_ibias_work_enable(struct snd_soc_codec *codec, bool enable);
static inline int hi6555c_irq_stat(unsigned int irq_stat_bit);
static inline void hi6555c_irqs_mask_set(unsigned int irqs);
static inline void hi6555c_irqs_clr(unsigned int irqs);
static inline void hi6555c_irqs_mask_clr(unsigned int irqs);

static int classd_voltage = CLASSD_4500mV_VOL;

#define HAC_ENABLE                   1
#define HAC_DISABLE                  0
#define GPIO_PULL_UP                 1
#define GPIO_PULL_DOWN               0

static int hac_en_gpio = 0;

static int hac_switch = 0;

/*****************************************************************************
 *
 * CODEC REGISTER OPERATION AREA BEGIN
 *
 *****************************************************************************/
static inline unsigned int hi6555c_misc_reg_read(struct hi6555c_priv *priv, unsigned int reg)
{
	unsigned int ret = 0;

	switch (reg) {
	case HI6555C_CLASSD_POWER_IF:
		ret = priv->tool_data.scharge_boost_cnt;
		break;
	case HI6555C_CODEC_SOCCLK_IF:
		ret = priv->tool_data.codec_soc_clk_cnt;
		break;
	case HI6555C_ECO_DISABLE_IF:
		ret = priv->tool_data.normal_always;
		break;
	default:
		loge("reg=%d\n", reg);
		break;
	}

	logi("%d\n", ret);
	return ret;
}

static void hi6555c_misc_reg_write(struct work_struct *work)
{
	int ret = 0;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, tool_work);
	unsigned int value = 0;
	unsigned int reg = 0;

	BUG_ON(!priv);

	value = priv->tool_data.value;
	reg = priv->tool_data.reg;

	logi("%d : %d\n", reg, value);
	switch (reg) {
	case HI6555C_CLASSD_POWER_IF:
		if (HI6555C_ENABLE == value) {
			ret = regulator_enable(priv->regulator_schg_boost3);
			if (0 != ret) {
				loge("regulator_schg_boost3 enable failed, ret=%d\n", ret);
			} else {
				priv->tool_data.scharge_boost_cnt = regulator_is_enabled(priv->regulator_schg_boost3);
			}
		} else {
			ret = regulator_disable(priv->regulator_schg_boost3);
			if (0 != ret) {
				loge("regulator_schg_boost3 disable fail, ret=%d\n", ret);
			}

			priv->tool_data.scharge_boost_cnt = regulator_is_enabled(priv->regulator_schg_boost3);
		}
		break;
	case HI6555C_CODEC_SOCCLK_IF:
		if (HI6555C_ENABLE == value) {
			ret = clk_prepare_enable(priv->codec_soc);
			if (0 != ret) {
				loge("codec 49.15M clken fail, ret=%d\n", ret);
			}

			priv->tool_data.codec_soc_clk_cnt++;
		} else {
			clk_disable_unprepare(priv->codec_soc);
			priv->tool_data.codec_soc_clk_cnt--;
		}
		break;
	case HI6555C_ECO_DISABLE_IF:
		break;
	default:
		loge("reg=%d value=%d\n", reg, value);
		break;
	}
}

static bool hi6555c_reg_value_valid(unsigned int reg_type, unsigned int reg_value)
{
	bool is_valid = true;
	unsigned int reg_page_array_size = ARRAY_SIZE(reg_page_array);
	int i = 0;

	for (i = 0; i < reg_page_array_size; i++) {
		if (reg_type != reg_page_array[i].page_tag) {
			continue;
		}

		if ((reg_value < reg_page_array[i].page_reg_begin) ||
		    (reg_value > reg_page_array[i].page_reg_end)) {
			is_valid = false;
			loge("%s: offset 0x%x is invalid\n", reg_page_array[i].page_name, reg_value);
		}
		break;
	}

	return is_valid;
}

static unsigned int __hi6555c_reg_read(struct hi6555c_priv *priv, unsigned int reg)
{
	volatile unsigned int ret = 0;
	unsigned int reg_type = 0;
	unsigned int reg_value = 0;
	unsigned long flags = 0;

	reg_type  = reg & PAGE_TYPE_MASK;
	reg_value = reg & PAGE_VALUE_MASK;

	if (!hi6555c_reg_value_valid(reg_type, reg_value)) {
		return INVALID_REG_VALUE;
	}

	spin_lock_irqsave(&priv->lock, flags);

	switch (reg_type) {
	case PAGE_SoCCODEC:
		ret = readl(reg_base_addr[HI6555C_SOCCODEC] + reg_value);
		logd("PAGE_SoCCODEC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_PMUCODEC:
		ret = hisi_pmic_reg_read(reg_value);
		logd("PAGE_PMUCODEC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_PMUHKADC:
		#if 0 /* fixme: may be used afterward */
			ret = readl(reg_base_addr[HI6555C_PMUHKADC] + (reg_value << 2));
		#endif
		logd("PAGE_PMUHKADC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_PeriSCTRL:
		ret = readl(reg_base_addr[HI6555C_PCTRL] + reg_value);
		logd("PAGE_PeriSCTRL: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_PMUCTRL:
		ret = hisi_pmic_reg_read(reg_value);
		logd("PAGE_PMUCTRL: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_VIRCODEC:
		ret = priv->v_codec_reg[reg_value];
		logd("PAGE_VIRCODEC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_MISCCODEC:
		ret = hi6555c_misc_reg_read(priv, reg_value);
		logd("PAGE_MISCCODEC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_ASPCFG:
		ret = readl(reg_base_addr[HI6555C_ASPCFG] + reg_value);
		logd("PAGE_ASPCFG: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_AO_IOC:
		ret = readl(reg_base_addr[HI6555C_AOIOC] + reg_value);
		logd("PAGE_AO_IOC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_IOC:
		ret = readl(reg_base_addr[HI6555C_IOC] + reg_value);
		logd("PAGE_IOC: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	case PAGE_PERICRG:
		ret = readl(reg_base_addr[HI6555C_PERICRG] + reg_value);
		logd("PAGE_PERICRG: offset = 0x%x, value = 0x%x\n", reg_value, ret);
		break;
	default:
		loge("reg=0x%x\n", reg);
		ret = INVALID_REG_VALUE;
		break;
	}

#ifdef CONFIG_HISI_DEBUG_FS
	/* record reg */
#if 0
	hi6555c_debug_reg_rd_cache(reg, ret);
#endif
#endif
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}

static void __hi6555c_reg_write(struct hi6555c_priv *priv, unsigned int reg, unsigned int value)
{
	unsigned int reg_type = 0;
	unsigned int reg_value = 0;
	unsigned long flags = 0;

	reg_type  = reg & PAGE_TYPE_MASK;
	reg_value = reg & PAGE_VALUE_MASK;

	if (!hi6555c_reg_value_valid(reg_type, reg_value)) {
		return;
	}

	spin_lock_irqsave(&priv->lock, flags);

#ifdef CONFIG_HISI_DEBUG_FS
	/*record reg*/
	hi6555c_debug_reg_wr_cache(reg, value);
#endif

	switch (reg_type) {
	case PAGE_SoCCODEC:
		logd("PAGE_SoCCODEC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		writel(value, reg_base_addr[HI6555C_SOCCODEC] + reg_value);
		break;
	case PAGE_PMUCODEC:
		logd("PAGE_PMUCODEC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		hisi_pmic_reg_write(reg_value, value);
		break;
	case PAGE_PMUHKADC:
		logd("PAGE_PMUHKADC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		#if 0 /* fixme: may be used afterward */
			writel(value, reg_base_addr[HI6555C_PMUHKADC] + (reg_value << 2));
		#endif
		break;
	case PAGE_PeriSCTRL:
		logd("PAGE_PeriSCTRL: offset = 0x%x, value = 0x%x\n", reg_value, value);
		writel(value, reg_base_addr[HI6555C_PCTRL] + reg_value);
		break;
	case PAGE_PMUCTRL:
		logd("PAGE_PMUCTRL: offset = 0x%x, value = 0x%x\n", reg_value, value);
		hisi_pmic_reg_write(reg_value, value);
		break;
	case PAGE_VIRCODEC:
		logd("PAGE_VIRCODEC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		priv->v_codec_reg[reg_value] = value;
		break;
	case PAGE_MISCCODEC:
		logd("PAGE_MISCCODEC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		priv->tool_data.reg   = reg_value;
		priv->tool_data.value = value;
		schedule_work(&priv->tool_work);
		break;
	case PAGE_ASPCFG:
		logd("PAGE_ASPCFG: offset = 0x%x, value = 0x%x\n", reg_value, value);
		writel(value, reg_base_addr[HI6555C_ASPCFG] + reg_value);
		break;
	case PAGE_AO_IOC:
		logd("PAGE_AO_IOC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		writel(value, reg_base_addr[HI6555C_AOIOC] + reg_value);
		break;
	case PAGE_IOC:
		logd("PAGE_IOC: offset = 0x%x, value = 0x%x\n", reg_value, value);
		writel(value, reg_base_addr[HI6555C_IOC] + reg_value);
		break;
	case PAGE_PERICRG:
		writel(value, reg_base_addr[HI6555C_PERICRG] + reg_value);
		logd("PAGE_PERICRG: offset = 0x%x, value = 0x%x\n", reg_value, value);
		break;
	default:
		loge("reg=0x%x, value=0x%x\n", reg, value);
		break;
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}

static inline unsigned int hi6555c_reg_read(struct snd_soc_codec *codec, unsigned int reg)
{
	volatile unsigned int ret = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	ret = __hi6555c_reg_read(priv, reg);
	if (INVALID_REG_VALUE == ret) {
		loge("reg 0x%x read value 0x%x is invalid\n", reg, ret);
	}

	return ret;
}

static inline int hi6555c_reg_write(struct snd_soc_codec *codec, unsigned int reg, unsigned int value)
{
	int ret = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	__hi6555c_reg_write(priv, reg, value);

	return ret;
}

/*
 * value:set by bits
 */
static void hi6555c_set_reg_bits(unsigned int reg, unsigned int value)
{
	unsigned int val = 0;

	if (!g_codec) {
		loge("g_codec is NULL\n");
		return;
	}

	val = hi6555c_reg_read(g_codec, reg) | (value);
	hi6555c_reg_write(g_codec, reg, val);
}

/*
 * value:clear by bits
 */
static void hi6555c_clr_reg_bits(unsigned int reg, unsigned int value)
{
	unsigned int val = 0;

	if (!g_codec) {
		loge("g_codec is NULL\n");
		return;
	}

	val = hi6555c_reg_read(g_codec, reg) & ~(value);
	hi6555c_reg_write(g_codec, reg, val);
}

/* provide for externel modules or tools only
 *  reg : high 16bit(type) + low 16bit(reg)
 */
unsigned int codec_reg_read(unsigned int reg)
{
	struct hi6555c_priv *priv = NULL;

	if (!g_codec) {
		loge("g_codec is null\n");
		return INVALID_REG_VALUE;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);

	if (!priv) {
		loge("priv is null\n");
		return INVALID_REG_VALUE;
	}

	/* working then delay entering eco mode */
#if 0 /*may be used afterward */
	mod_timer(&priv->timer, jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);
#endif

	return __hi6555c_reg_read(priv, reg);
}

/* provide for externel modules or tools only */
void codec_reg_write(unsigned int reg, unsigned int value)
{
	struct hi6555c_priv *priv = NULL;

	if (!g_codec) {
		loge("g_codec is null\n");
		return;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);

	if (!priv) {
		loge("priv is null\n");
		return;
	}

	__hi6555c_reg_write(priv, reg, value);

	/* working then delay entering eco mode */
#if 0 /*may be used afterward */
	mod_timer(&priv->timer, jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);
#endif
}
/*****************************************************************************
 *
 * CODEC REGISTER OPERATION AREA END
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * HAC AREA BEGIN
 *
 *****************************************************************************/
static int hac_gpio_switch(int hac_cmd)
{
	if (!hac_en_gpio) {
		loge("Failed to get the hac gpio");
		return 0;
	}

	if (HAC_ENABLE == hac_cmd) {
		logi("Enable hac enable gpio %u\n", hac_en_gpio);
		gpio_direction_output(hac_en_gpio, GPIO_PULL_UP);
	} else {
		logi("Disable hac enable gpio %u\n", hac_en_gpio);
		gpio_direction_output(hac_en_gpio, GPIO_PULL_DOWN);
	}

	return hac_cmd;
}

static const char * const hac_switch_text[] = {"OFF", "ON"};

static const struct soc_enum hac_switch_enum[] = {
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(hac_switch_text), hac_switch_text),
};

static int hac_switch_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	if (NULL == kcontrol || NULL == ucontrol) {
		loge("input pointer is null\n");
		return 0;
	}

	ucontrol->value.integer.value[0] = hac_switch;

	return 0;
}

static int hac_switch_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	int ret = 0;

	if (NULL == kcontrol || NULL == ucontrol) {
		loge("input pointer is null\n");
		return ret;
	}

	hac_switch = ucontrol->value.integer.value[0];
	ret = hac_gpio_switch(hac_switch);

	return ret;
}
/*****************************************************************************
 *
 * HAC AREA END
 *
 *****************************************************************************/
/*****************************************************************************
 *
 * CLASSD VOLTAGE CONFIG AREA BEGIN
 *
 *****************************************************************************/
static int classd_voltage_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	if (NULL == kcontrol || NULL == ucontrol) {
		loge("input pointer is null\n");
		return 0;
	}

	ucontrol->value.integer.value[0] = classd_voltage;

	return 0;
}

static int classd_voltage_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	int ret = 0;

	if (NULL == kcontrol || NULL == ucontrol) {
		loge("input pointer is null\n");
		return ret;
	}

	/* The default voltage is 4.5,set by pmu.
	 * And here set range 4.5~5.2 */
	if ((0 != ucontrol->value.integer.value[0]%100)
		||(ucontrol->value.integer.value[0]<CLASSD_4500mV_VOL)
		||(ucontrol->value.integer.value[0]>CLASSD_5200mV_VOL)){
		loge("classd voltage config in xml is not support\n");
		return ret;
	}

	classd_voltage = ucontrol->value.integer.value[0];
	ret = scharger_flash_bst_vo_config(classd_voltage);

	return ret;
}

/*****************************************************************************
 *
 * CLASSD VOLTAGE CONFIG AREA END
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * CONTROL WIDGET AREA BEGIN
 *
 *****************************************************************************/

/*****************************************************************************
  Sound Controls
 *****************************************************************************/
/* LINEPGAL GAIN(LINEPGAL_GAIN<3:0>)��
 * range:-14dB~16dB��
 * step:2dB��
 * 0000:-14dB��
 * 0001:-12dB��
 * 0010:-10dB��
 * ����
 * 0111:0dB��
 * ����
 * 1110:14dB��
 * 1111:16dB�� */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_linepgal_gain_tlv, -1400, 200, 0);

/* LINEPGAR GAIN(LINEPGAR_GAIN<3:0>)��
 * range:-14dB~16dB��
 * step:2dB��
 * 0000:-14dB��
 * 0001:-12dB��
 * 0010:-10dB��
 * ����
 * 0111:0dB��
 * ����
 * 1110:14dB��
 * 1111:16dB�� */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_linepgar_gain_tlv, -1400, 200, 0);

/* AUXPGA GAIN(AUXPGA_GAIN<2:0>)��
 * range:0dB~14dB��
 * step:2dB��
 * 000: 0dB��
 * 001: 2dB��
 * 010: 4dB��
 * 011: 6dB��
 * 100: 8dB��
 * 101: 10dB��
 * 110: 12dB��
 * 111: 14dB�� */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_auxpga_gain_tlv, 0, 200, 0);

/* MAINPGA GAIN(MAINPGA_GAIN<2:0>)��
 * range:0dB~14dB��
 * step:2dB��
 * 000: 0dB��
 * 001: 2dB��
 * 010: 4dB��
 * 011: 6dB��
 * 100: 8dB��
 * 101: 10dB��
 * 110: 12dB��
 * 111: 14dB�� */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_mainpga_gain_tlv, 0, 200, 0);

/* HeadphoneL GAIN(HSL_GAIN<3:0>)��
 * range:-20dB~-0dB��
 * step:1.5dB��
 * 0000:-20dB��
 * 0001:-18dB��
 * 0010:-16.5dB��
 * 0011: -15dB;
 * 0100:-13.5dB;
 * 0101:-12dB;
 * 0110:-10.5dB;
 * 0111:-9.5dB;
 * 1000:-8.5dB;
 * 1001:-7.5dB;
 * 1010:-6.5dB;
 * 1011:-5.5dB;
 * 1100:-4.5dB;
 * 1101:-3dB;
 * 1110:-1.5dB;
 * 1111:0dB; */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_hsl_gain_tlv, -2000, 150, 0);

/* HeadphoneR GAIN(HSR_GAIN<3:0>)��
 * range:-20dB~-0dB��
 * step:1.5dB��
 * 0000:-20dB��
 * 0001:-18dB��
 * 0010:-16.5dB��
 * 0011: -15dB;
 * 0100:-13.5dB;
 * 0101:-12dB;
 * 0110:-10.5dB;
 * 0111:-9.5dB;
 * 1000:-8.5dB;
 * 1001:-7.5dB;
 * 1010:-6.5dB;
 * 1011:-5.5dB;
 * 1100:-4.5dB;
 * 1101:-3dB;
 * 1110:-1.5dB;
 * 1111:0dB; */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_hsr_gain_tlv, -2000, 150, 0);

/* EAR GAIN(EAR_GAIN<5:0>)��
 * range:-20dB~-6dB��
 * step:2dB��
 * 0000:-20dB��
 * 0001:-18dB��
 * 0010:-16dB��
 * 0011: -14dB;
 * 0100:-12dB;
 * 0101:-10dB;
 * 0110:-8dB;
 * 0111:-6dB;
 * 1000:-4dB;
 * 1001:-2dB;
 * 1010:-0dB;
 * 1011:2dB;
 * 1100:4dB;
 * 1101:6dB;
 * orther: mute */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_ear_gain_tlv, -2000, 200, 0);

static const struct snd_kcontrol_new hi6555c_snd_controls[] = {
	SOC_SINGLE("HISSC_DACL_HBF1I_EN",
			HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACL_HBF1I_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACL_HBF2I_EN",
			HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACL_HBF2I_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_HBF1I_EN",
			HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACR_HBF1I_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_HBF2I_EN",
			HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACR_HBF2I_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_FS_VOICE_DLINK",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_VOICE_DLINK_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_FS_STEREO_DLINK_L",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_STEREO_DLINK_L_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_FS_STEREO_DLINK_R",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_STEREO_DLINK_R_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_FS_DACLR",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_DACLR_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_FS_ADCLR",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_ADCLR_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_FS_S1",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_S1_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_FS_S2",
			HI6555C_FS_CFG_ADDR, HI6555C_FS_S2_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_S1_FUNC_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_FUNC_MODE_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_S1_CODEC_DATA_FORMAT",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_CODEC_DATA_FORMAT_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_RX_CLK_SEL",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_RX_CLK_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_TX_CLK_SEL",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_TX_CLK_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_DIRECT_LOOP",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_DIRECT_LOOP_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S1_CODEC_IO_WORDLENGTH",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_CODEC_IO_WORDLENGTH_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S1_CHNNL_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_CHNNL_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_LRCLK_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_LRCLK_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_MST_SLV",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_MST_SLV_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_FRAME_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S1_FRAME_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_FUNC_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_FUNC_MODE_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_S2_CODEC_DATA_FORMAT",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_CODEC_DATA_FORMAT_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_RX_CLK_SEL",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_RX_CLK_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_TX_CLK_SEL",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_TX_CLK_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_DIRECT_LOOP",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_DIRECT_LOOP_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S2_CODEC_IO_WORDLENGTH",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_CODEC_IO_WORDLENGTH_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S2_CHNNL_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_CHNNL_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_LRCLK_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_LRCLK_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_MST_SLV",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_MST_SLV_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_FRAME_MODE",
			HI6555C_I2S_CFG_ADDR, HI6555C_S2_FRAME_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACL_MIXER_GAIN",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_GAIN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_MIXER_GAIN",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_GAIN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_SRC_MODE",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_MODE_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_S2_OL_SRC_MODE",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_SRC_MODE_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S2_OL_MIXER_GAIN",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_MIXER_GAIN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_MIXER_GAIN",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_MIXER_GAIN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_ADCL_PGA_INTEGER_CONFIG",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_ADCL_PGA_FRAC_CONFIG",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_ADCL_PGA_MUTE",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_ADCL_PGA_THR_CONFIG",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_ADCR_PGA_INTEGER_CONFIG",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_ADCR_PGA_FRAC_CONFIG",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_ADCR_PGA_MUTE",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_ADCR_PGA_THR_CONFIG",
			HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S1_IL_PGA_INTEGER_CONFIG",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_S1_IL_PGA_FRAC_CONFIG",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_IL_PGA_MUTE",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_IL_PGA_THR_CONFIG",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S1_IR_PGA_INTEGER_CONFIG",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_S1_IR_PGA_FRAC_CONFIG",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_IR_PGA_MUTE",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S1_IR_PGA_THR_CONFIG",
			HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S2_IL_PGA_INTEGER_CONFIG",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_S2_IL_PGA_FRAC_CONFIG",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IL_PGA_MUTE",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IL_PGA_THR_CONFIG",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S2_IR_PGA_INTEGER_CONFIG",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_S2_IR_PGA_FRAC_CONFIG",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IR_PGA_MUTE",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IR_PGA_THR_CONFIG",
			HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_INTEGER_CONFIG",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_FRAC_CONFIG",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_MUTE",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_THR_CONFIG",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_INTEGER_CONFIG",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_FRAC_CONFIG",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_MUTE",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_THR_CONFIG",
			HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_PGA_INTEGER_CONFIG",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_PGA_FRAC_CONFIG",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_PGA_MUTE",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_PGA_THR_CONFIG",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SIDETONE_PGA_INTEGER_CONFIG",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_SIDETONE_PGA_FRAC_CONFIG",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SIDETONE_PGA_MUTE",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SIDETONE_PGA_THR_CONFIG",
			HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_FIFO_AFULL_TH",
			HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_DLINK_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_FIFO_AEMPTY_TH",
			HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_DLINK_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_L_FIFO_AFULL_TH",
			HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_L_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_L_FIFO_AEMPTY_TH",
			HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_L_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_R_FIFO_AFULL_TH",
			HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_R_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_DLINK_R_FIFO_AEMPTY_TH",
			HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_R_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_UPLINK_L_FIFO_AFULL_TH",
			HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_L_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_UPLINK_L_FIFO_AEMPTY_TH",
			HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_L_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_UPLINK_R_FIFO_AFULL_TH",
			HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_R_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_STEREO_UPLINK_R_FIFO_AEMPTY_TH",
			HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_R_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_VOICE_UPLINK_L_FIFO_AFULL_TH",
			HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_VOICE_UPLINK_L_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_VOICE_UPLINK_L_FIFO_AEMPTY_TH",
			HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_VOICE_UPLINK_L_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC___B0___LEFT___",
			HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C___B0___LEFT____BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_VOICE_UPLINK_R_FIFO_AEMPTY_TH",
			HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_VOICE_UPLINK_R_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

	SOC_SINGLE("HISSC_DACL_AGC_GWIN_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_GWIN_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_LEVELLOW_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_LEVELLOW_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_GSTEPD_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_GSTEPD_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_TIMEMUTE_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_TIMEMUTE_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_NGW_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGW_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_YTARGET_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_YTARGET_CONFIG_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_DACL_AGC_T_AMIN_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_T_AMIN_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_GSUPPRESS",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_GSUPPRESS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACL_AGC_KFSLOW",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_KFSLOW_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_KFRAPID",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_KFRAPID_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_NGL_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGL_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_NGH_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGH_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_TIMER",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_TIMER_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_DACL_AGC_NGI_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGI_CONFIG_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_DACL_AGC_TIMENNG_CONFIG",
			HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_TIMENNG_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_TIMEDECAY_CONFIG",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_TIMEDECAY_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_TIMEGHOLD_CONFIG",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_TIMEGHOLD_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_GMUTE_CONFIG",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_GMUTE_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACL_AGC_MUTE_BYPASS",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_MUTE_BYPASS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACL_AGC_BYPASS",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_BYPASS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACL_AGC_USR_GDB_INTEGER",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_USR_GDB_INTEGER_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_DACL_AGC_USR_GDB_FRAC",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_USR_GDB_FRAC_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACL_AGC_SW_CLR",
			HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_SW_CLR_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_AGC_GWIN_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_GWIN_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_LEVELLOW_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_LEVELLOW_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_GSTEPD_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_GSTEPD_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_TIMEMUTE_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_TIMEMUTE_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_NGW_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGW_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_YTARGET_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_YTARGET_CONFIG_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_DACR_AGC_T_AMIN_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_T_AMIN_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_GSUPPRESS",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_GSUPPRESS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_AGC_KFSLOW",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_KFSLOW_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_KFRAPID",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_KFRAPID_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_NGL_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGL_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_NGH_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGH_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_TIMER",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_TIMER_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_DACR_AGC_NGI_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGI_CONFIG_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_DACR_AGC_TIMENNG_CONFIG",
			HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_TIMENNG_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_TIMEDECAY_CONFIG",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_TIMEDECAY_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_TIMEGHOLD_CONFIG",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_TIMEGHOLD_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_GMUTE_CONFIG",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_GMUTE_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_DACR_AGC_MUTE_BYPASS",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_MUTE_BYPASS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_AGC_BYPASS",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_BYPASS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_AGC_USR_GDB_INTEGER",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_USR_GDB_INTEGER_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_DACR_AGC_USR_GDB_FRAC",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_USR_GDB_FRAC_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DACR_AGC_SW_CLR",
			HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_SW_CLR_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SIF_EDGE_SEL",
			HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_SIF_EDGE_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SW_DMIC_MODE",
			HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_SW_DMIC_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_DMIC_REVERSE",
			HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_DMIC_REVERSE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_FS_DMIC",
			HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_FS_DMIC_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL",
			HI6555C_MISC_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_FUNC_MODE",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_FUNC_MODE_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_S3_CODEC_DATA_FORMAT",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_CODEC_DATA_FORMAT_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_RX_CLK_SEL",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_RX_CLK_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_TX_CLK_SEL",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_TX_CLK_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_DIRECT_LOOP",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_DIRECT_LOOP_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S3_CODEC_IO_WORDLENGTH",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_CODEC_IO_WORDLENGTH_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_S3_CHNNL_MODE",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_CHNNL_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_LRCLK_MODE",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_LRCLK_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_MST_SLV",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_MST_SLV_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S3_FRAME_MODE",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_FRAME_MODE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_FS_S3",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_FS_S3_BIT_START, 0x7, 0),

	SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_INTEGER_CONFIG",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

	SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_FRAC_CONFIG",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_MUTE",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_THR_CONFIG",
			HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_THR_CONFIG_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_EXTERNAL_12288K_SEL",
			HI6555C_CLK_SEL_ADDR, HI6555C_EXTERNAL_12288K_SEL_BIT_START, 0x2, 0),

	SOC_SINGLE("HISSC_SMT_DACL_CLK_EDGE_SEL",
			HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_DACL_CLK_EDGE_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_DACR_CLK_EDGE_SEL",
			HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_DACR_CLK_EDGE_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCL_CLK_EDGE_SEL",
			HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_ADCL_CLK_EDGE_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_CLK_EDGE_SEL",
			HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_ADCR_CLK_EDGE_SEL_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_DAC_LOOPBACK",
			HI6555C_SMT_LOOPBACK_CFG_ADDR, HI6555C_SMT_DAC_LOOPBACK_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADC_LOOPBACK",
			HI6555C_SMT_LOOPBACK_CFG_ADDR, HI6555C_SMT_ADC_LOOPBACK_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_LINEPGAL_MUTE",
			HI6555C_SMT_CODEC_ANA_RW05_ADDR, HI6555C_SMT_LINEPGAL_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_LINEPGAL_GAIN",
			HI6555C_SMT_CODEC_ANA_RW05_ADDR, HI6555C_SMT_LINEPGAL_GAIN_BIT_START, 0xF, 0,
			hi6555c_smt_linepgal_gain_tlv),

	SOC_SINGLE("HISSC_SMT_LINEPGAL_SEL",
			HI6555C_SMT_CODEC_ANA_RW05_ADDR, HI6555C_SMT_LINEPGAL_SEL_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_LINEPGAR_MUTE",
			HI6555C_SMT_CODEC_ANA_RW06_ADDR, HI6555C_SMT_LINEPGAR_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_LINEPGAR_GAIN",
			HI6555C_SMT_CODEC_ANA_RW06_ADDR, HI6555C_SMT_LINEPGAR_GAIN_BIT_START, 0xF, 0,
			hi6555c_smt_linepgar_gain_tlv),

	SOC_SINGLE("HISSC_SMT_LINEPGAR_SEL",
			HI6555C_SMT_CODEC_ANA_RW06_ADDR, HI6555C_SMT_LINEPGAR_SEL_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_AUXPGA_SEL",
			HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_SEL_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_AUXPGA_MUTE",
			HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_AUXPGA_GAIN",
			HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_GAIN_BIT_START, 0x7, 0,
			hi6555c_smt_auxpga_gain_tlv),

	SOC_SINGLE("HISSC_SMT_AUXPGA_BOOST",
			HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_BOOST_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_MAINPGA_MUTE",
			HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_MAINPGA_GAIN",
			HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_GAIN_BIT_START, 0x7, 0,
			hi6555c_smt_mainpga_gain_tlv),

	SOC_SINGLE("HISSC_SMT_MAINPGA_BOOST",
			HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_BOOST_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCL_DWA_BPS",
			HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_DWA_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCL_FLSTN",
			HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_FLSTN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_ADCL_DAC_BIAS",
			HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_DAC_BIAS_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_ADCL_CLK_DELAY_0",
			HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_CLK_DELAY_0_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCL_CLK_DELAY_1",
			HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_CLK_DELAY_1_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_DWA_BPS",
			HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_DWA_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_FLSTN",
			HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_FLSTN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_DAC_BIAS",
			HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_DAC_BIAS_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_CLK_DELAY_0",
			HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_CLK_DELAY_0_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_CLK_DELAY_1",
			HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_CLK_DELAY_1_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADCR_CLK_DELAY_2",
			HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_CLK_DELAY_2_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_HSL_MIN_GAIN",
			HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HSL_MIN_GAIN_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_HSL_GAIN",
			HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HSL_GAIN_BIT_START, 0xF, 0,
			hi6555c_smt_hsl_gain_tlv),

	SOC_SINGLE("HISSC_SMT_HSL_MUTE",
			HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HSL_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_HS_LIT_LP_L",
			HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HS_LIT_LP_L_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_HSR_MIN_GAIN",
			HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HSR_MIN_GAIN_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_HSR_GAIN",
			HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HSR_GAIN_BIT_START, 0xF, 0,
			hi6555c_smt_hsr_gain_tlv),

	SOC_SINGLE("HISSC_SMT_HSR_MUTE",
			HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HSR_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_HS_LIT_LP_R",
			HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HS_LIT_LP_R_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_EAR_CM_CTRL",
			HI6555C_SMT_CODEC_ANA_RW19_ADDR, HI6555C_SMT_EAR_CM_CTRL_BIT_START, 0x1, 0),

	SOC_SINGLE_TLV("HISSC_SMT_EAR_GAIN",
			HI6555C_SMT_CODEC_ANA_RW19_ADDR, HI6555C_SMT_EAR_GAIN_BIT_START, 0xF, 0,
			hi6555c_smt_ear_gain_tlv),

	SOC_SINGLE("HISSC_SMT_EAR_MUTE",
			HI6555C_SMT_CODEC_ANA_RW19_ADDR, HI6555C_SMT_EAR_MUTE_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_DAC_CHOP_CLK_SEL",
			HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_DAC_CHOP_CLK_SEL_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_ADC_CHOP_CLK_SEL",
			HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_ADC_CHOP_CLK_SEL_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_SMT_DAC_CLK_SYS_EDGE_0",
			HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_DAC_CLK_SYS_EDGE_0_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_DAC_CLK_SYS_EDGE_1",
			HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_DAC_CLK_SYS_EDGE_1_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADC_CLK_SYS_EDGE_0",
			HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_ADC_CLK_SYS_EDGE_0_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADC_CLK_SYS_EDGE_1",
			HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_ADC_CLK_SYS_EDGE_1_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_CTCM_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_CTCM_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_MICPGA_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_MICPGA_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_LINEIN_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_LINEIN_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_ADC_SDM_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_ADC_SDM_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_RX_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_RX_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_HS_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_HS_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_EAR_CLD_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_EAR_CLD_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_DAC_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_DAC_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_TX_CHOP_BPS",
			HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_TX_CHOP_BPS_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IL_SRC_UP_EN",
			HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IL_SRC_UP_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IL_SRC_DOWN_EN",
			HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IL_SRC_DOWN_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IR_SRC_UP_EN",
			HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IR_SRC_UP_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_IR_SRC_DOWN_EN",
			HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IR_SRC_DOWN_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_S2_OL_SRC_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_S2_OL_SRC_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_VOICE_DLINK_SRC_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_EN_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_CR_MIXF_LINEINR",
			HI6555C_SMT_CODEC_ANA_RW14_ADDR, HI6555C_SMT_CR_MIXF_BIT_START, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_CR_MIXF_LINEINL",
			HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_CR_MIXF_BIT_START+1), 0x1, 0),

	SOC_SINGLE("HISSC_SMT_CR_MIXF_DACR",
			HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_CR_MIXF_BIT_START+2), 0x1, 0),

	SOC_SINGLE("HISSC_SMT_CR_MIXF_DACL",
			HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_CR_MIXF_BIT_START + 3), 0x1, 0),

	SOC_SINGLE("HISSC_PMU_CODEC_CLASSD_GAIN",
			HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, HI6555C_PMU_CODEC_CLASSD_GAIN_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_PMU_CODEC_CLASSD_I_OCP",
			HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, HI6555C_PMU_CODEC_CLASSD_I_OCP_BIT_START, 0x3, 0),

	SOC_SINGLE("HISSC_PMU_CODEC_CLASSD_MUTE",
			HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, HI6555C_PMU_CODEC_CLASSD_MUTE_BIT, 0x1, 0),

	SOC_SINGLE("HISSC_SMT_EAR_VREF_EN",
			HI6555C_SMT_CODEC_ANA_RW39_ADDR, HI6555C_SMT_EAR_VREF_EN_BIT_START, 0x1, 0),

	SOC_ENUM_EXT("HAC",
			hac_switch_enum[0], hac_switch_get, hac_switch_put),

	SOC_SINGLE_EXT("CLASSD_VOLTAGE_CONFIG", HI6555C_DDR_CODEC_VIR2_ADDR, 0, 0xffff, 0,
			classd_voltage_get, classd_voltage_put),
};

/*****************************************************************************
  Widgets Related
 *****************************************************************************/
int hi6555c_dacl_mixer_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START + 3)));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START + 3)));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

int hi6555c_dacr_mixer_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START + 2)));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START + 2)));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

int hi6555c_dacl_agc_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_DACL_AGC_CFG_2_ADDR, (0x01 << HI6555C_DACL_AGC_BYPASS_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF1I_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF2I_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_COMPI_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_SDM_EN_BIT_START));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF1I_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF2I_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_COMPI_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_SDM_EN_BIT_START));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

int hi6555c_dacr_agc_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_DACR_AGC_CFG_2_ADDR, (0x01 << HI6555C_DACR_AGC_BYPASS_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF1I_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF2I_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_COMPI_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_SDM_EN_BIT_START));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF1I_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF2I_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_COMPI_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_SDM_EN_BIT_START));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

int hi6555c_adcl_pga_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_CIC_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_COMPD_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HPF_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBFVD_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBF2D_EN_BIT_START));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_CIC_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_COMPD_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HPF_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBFVD_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBF2D_EN_BIT_START));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

int hi6555c_adcr_pga_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_CIC_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_COMPD_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HPF_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBFVD_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBF2D_EN_BIT_START));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_CIC_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_COMPD_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HPF_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBFVD_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBF2D_EN_BIT_START));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_smt_hslr_pd_outdrv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW17_ADDR, 0x58);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW18_ADDR, 0x58);
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
				(0x01 << HI6555C_SMT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_HSL_PD_BIT_START));
		msleep(100);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
				(0x01 << HI6555C_SMT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_HSL_PD_BIT_START));
		msleep(100);
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_smt_hslr_pd_mixer_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
				(0x01 << HI6555C_SMT_MIXOUT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_MIXOUT_HSL_PD_BIT_START));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
				(0x01 << HI6555C_SMT_MIXOUT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_MIXOUT_HSL_PD_BIT_START));
		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_pmu_classd_pd_outdrv_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int ret = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

	BUG_ON(!priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (!priv->use_battery_supply) {
			logi("use scharger supply\n");
			/* flash boost enable */
			ret = regulator_enable(priv->regulator_schg_boost3);
			if (ret != 0) {
				loge("regulator_schg_boost3 en fail, ret=%d\n", ret);
			}
		} else {
			logi("use battery supply\n");
		}

		/* classd pu */
		hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, (0x01 << HI6555C_PMU_CODEC_EN_CLASSD_INT_BIT));
		msleep(1);
		hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_DRV_EN_BIT));
		msleep(1);

		/* unmute 0x13B bit1 0 */
		hi6555c_clr_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_MUTE_BIT));
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* mute 0x13B bit1 1 */
		hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_MUTE_BIT));
		msleep(1);

		/* classd pd */
		hi6555c_clr_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_DRV_EN_BIT));
		hi6555c_clr_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR, (0x01 << HI6555C_PMU_CODEC_EN_CLASSD_INT_BIT));

		if (!priv->use_battery_supply) {
			/* flash boost close */
			ret = regulator_disable(priv->regulator_schg_boost3);
			if (ret != 0) {
				loge("regulator_schg_boost3 dis fail, ret=%d\n", ret);
			}
		}

		break;
	default:
		loge("event=%d\n", event);
		break;
	}

	return 0;
}

/* SOC_IBIAS EVENT */
static int hi6555c_soc_ibias_supply_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		break;
	case SND_SOC_DAPM_POST_PMD:
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

/* SMT_IBIAS EVENT */
static int hi6555c_smt_ibias_supply_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_ibias_work_enable(g_codec, true);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_ibias_work_enable(g_codec, false);
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

/* MICB1 EVENT */
static int hi6555c_smt_micb1_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* MICBIAS PU */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, (0x01 << HI6555C_SMT_MICB1_PD_BIT_START));
		msleep(1);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, (0x01 << HI6555C_SMT_MICB1_PD_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

/* MICB1 EVENT */
static int hi6555c_smt_hsmicb_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	unsigned int irq_mask = 0;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* to avoid irq while MBHD_COMP power up��mask the irq then clean it */
		irq_mask = hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR);
		hi6555c_irqs_mask_set(irq_mask | IRQ_MSK_COMP);
		hi6555c_hs_micbias_work_enable(g_codec, true);
		msleep(25);

		/* to avoid irq while MBHD_COMP power up��mask the irq then clean it */
		hi6555c_irqs_clr(IRQ_MSK_COMP);
		hi6555c_irqs_mask_clr(IRQ_MSK_BTN_NOR);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_hs_micbias_work_enable(g_codec, false);
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

int hi6555c_fm_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* cp clk 96k */
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, 0x60);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* cp clk 1.576M */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, 0x40);
		break;
	default :
		dev_warn(codec->dev, "%s : power mode event err : %d\n", __FUNCTION__, event);
		break;
	}

	return 0;
}

static void hi6555c_reuse(struct snd_soc_codec *codec)
{
	/* asp codec reset leave */
	hi6555c_set_reg_bits((PAGE_ASPCFG + ASP_CFG_SOFT_RST_REG_OFFSET), ASP_CODEC_SOFT_RST_VALUE);

	/* asp codec clk & apb clk enable */
	hi6555c_set_reg_bits((PAGE_ASPCFG + ASP_CFG_CLK_EN_REG_OFFSET), ASP_CODEC_CLK_EN_VALUE);

	/* 3rd fifo mux sel i2s1 */
	hi6555c_reg_write(codec, (PAGE_SoCCODEC + 0x8c), 0x10);

	/* set 24bit for codec to compitable with HIFI */
	hi6555c_set_reg_bits(HI6555C_SW_RST_N_ADDR,  HI6555C_CODEC_24BIT_SETTING);

	/* code_sel i2s&dma switch to fifo */
	hi6555c_reg_write(codec, (PAGE_ASPCFG + 0x1E0), 0x3);

	/* AO_IOC Pin multiplexing for s2p */
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x2c), 0x1);
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x30), 0x1);
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x34), 0x1);
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x38), 0x1);

	/* I2S 2 Pin multiplexing*/
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x3c), 0x1);
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x40), 0x1);
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x44), 0x1);
	hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x48), 0x1);

	/* I2S 1 Pin multiplexing */
	hi6555c_reg_write(codec, (PAGE_IOC + 0x20), 0x3);
	hi6555c_reg_write(codec, (PAGE_IOC + 0x24), 0x3);
	hi6555c_reg_write(codec, (PAGE_IOC + 0x28), 0x3);
	hi6555c_reg_write(codec, (PAGE_IOC + 0x2c), 0x3);
}

static int hi6555c_pll_supply_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int ret = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

	BUG_ON(!priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		ret = regulator_enable(priv->codec_peri);
		BUG_ON(ret != 0);

		ret = clk_prepare_enable(priv->codec_soc);
		if (0 != ret) {
			loge("codec 49.15M clken fail, ret=%d\n", ret);
		}

		priv->have_dapm = true;
		break;
	case SND_SOC_DAPM_POST_PMD:
		ret = regulator_disable(priv->codec_peri);
		BUG_ON(ret != 0);

		clk_disable_unprepare(priv->codec_soc);
		priv->have_dapm = false;
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_backuppll_supply_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int ret = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

	BUG_ON(!priv);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		ret = clk_prepare_enable(priv->codec_soc);
		if (0 != ret) {
			loge("codec 49.15M clken fail, ret=%d\n", ret);
		}
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW41_ADDR, 0x07);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW42_ADDR, 0x07);
		clk_disable_unprepare(priv->codec_soc);
		break;
	case SND_SOC_DAPM_POST_PMD:
		ret = clk_prepare_enable(priv->codec_soc);
		if (0 != ret) {
			loge("codec 49.15M clken fail, ret=%d\n", ret);
		}
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW42_ADDR, 0x00);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW41_ADDR, 0x27);
		clk_disable_unprepare(priv->codec_soc);
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_smt_lineinl_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (0 != (hi6555c_reg_read(g_codec, HI6555C_SMT_CODEC_ANA_RW05_ADDR) & 0x1)) {
			hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAL_PD_BIT_START));
		} else {
			hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW05_ADDR, (1 << HI6555C_SMT_LINEPGAL_MUTE_BIT_START));
			hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAL_PD_BIT_START));
			hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW05_ADDR, (1 << HI6555C_SMT_LINEPGAL_MUTE_BIT_START));
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAL_PD_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_smt_lineinr_pga_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (0 != (hi6555c_reg_read(g_codec, HI6555C_SMT_CODEC_ANA_RW06_ADDR) & 0x1)) {
			hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAR_PD_BIT_START));
		} else {
			hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW06_ADDR, (1 << HI6555C_SMT_LINEPGAR_MUTE_BIT_START));
			hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAR_PD_BIT_START));
			hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW06_ADDR, (1 << HI6555C_SMT_LINEPGAR_MUTE_BIT_START));
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAR_PD_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_hs_preprocess_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR,
				((1<<HI6555C_SMT_RST_N_R_BIT_START)|(1<<HI6555C_SMT_RST_N_L_BIT_START))|(1<<HI6555C_SMT_PDD_EN_BIT_START));
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW17_ADDR, 0x21);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW18_ADDR, 0x21);
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, (1<<HI6555C_SMT_HS_SYS_CLK_PD_BIT_START));
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW16_ADDR, (1<<HI6555C_SMT_HP_SOFT_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, (1<<HI6555C_SMT_HS_SYS_CLK_PD_BIT_START));
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR, (1<<HI6555C_SMT_CLK_SEL_BIT_START));
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW20_ADDR, 0xFA);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW28_ADDR, 0x00);
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, (1<<HI6555C_SMT_CP_CLK_PD_BIT_START));
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW37_ADDR, (1<<HI6555C_SMT_CP_PU_BIT_START));
		msleep(2);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR,
				((1<<HI6555C_SMT_RST_N_R_BIT_START)|(1<<HI6555C_SMT_RST_N_L_BIT_START))|(1<<HI6555C_SMT_PDD_EN_BIT_START));
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW17_ADDR, 0x20);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW18_ADDR, 0x20);
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, (1<<HI6555C_SMT_HS_SYS_CLK_PD_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW16_ADDR, (1<<HI6555C_SMT_HP_SOFT_EN_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR, (1<<HI6555C_SMT_CLK_SEL_BIT_START));
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW20_ADDR, 0x40);
		hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW28_ADDR, 0x00);
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW37_ADDR, (1<<HI6555C_SMT_CP_PU_BIT_START));
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR, (1<<HI6555C_SMT_CP_CLK_PD_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_dac_path_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
				(0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START + 2))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START + 3)));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
				(0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START + 2))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START + 3)));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_linein_path_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		msleep(50);
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
				(0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START + 0))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START + 1)));
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
				(0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START + 0))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START + 1)));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

/* fifo EVENT */
static int hi6555c_stereo_dlink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* STEREO DLINK AFIFO CLEAR CFG */
		hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
				(1 << HI6555C_STEREO_DLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_DLINK_R_FIFO_CLR_BIT_START));
		udelay(1);

		hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
				(1 << HI6555C_STEREO_DLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_DLINK_R_FIFO_CLR_BIT_START));

		/* fifo init, clear over depth */
		for (i = 0; i < 16; i++) {
			hi6555c_clr_reg_bits(HI6555C_STEREO_DLINK_CHANNEL_ADDR, 0xFFFFFFFF);
		}
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_voice_dlink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR, (1 << HI6555C_VOICE_DLINK_FIFO_CLR_BIT_START));
		udelay(1);
		hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR, (1 << HI6555C_VOICE_DLINK_FIFO_CLR_BIT_START));

		for (i = 0; i < 32; i++) {
			hi6555c_clr_reg_bits(HI6555C_VOICE_DLINK_CHANNEL_ADDR, 0xFFFFFFFF);
		}

		/*
		 *bugfix:wait 4ms to clear fifo
		 *fifo size 32, samplerate 8k, time 4ms
		 *time * samplerate = fifo size
		 */
		msleep(4);

		hi6555c_clr_reg_bits(HI6555C_MUX_TOP_MODULE_CFG_ADDR, (1 << HI6555C_VOICE_DLINK_MIXER_IN1_MUTE_BIT_START));
		break;
	case SND_SOC_DAPM_PRE_PMD:
		hi6555c_set_reg_bits(HI6555C_MUX_TOP_MODULE_CFG_ADDR, (1 << HI6555C_VOICE_DLINK_MIXER_IN1_MUTE_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_voice_uplink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
				(1 << HI6555C_VOICE_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_VOICE_UPLINK_R_FIFO_CLR_BIT_START));
		udelay(1);
		hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
				(1 << HI6555C_VOICE_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_VOICE_UPLINK_R_FIFO_CLR_BIT_START));

		for (i = 0; i < 16; i++) {
			hi6555c_clr_reg_bits(HI6555C_VOICE_UPLINK_CHANNEL_ADDR, 0xFFFFFFFF);
		}
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_thirdmd_dlink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR, (1 << HI6555C_THIRDMD_DLINK_FIFO_CLR_BIT_START));
		udelay(1);
		hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR, (1 << HI6555C_THIRDMD_DLINK_FIFO_CLR_BIT_START));

		for (i = 0; i < 16; i++) {
			hi6555c_clr_reg_bits(HI6555C_THIRDMD_DLINK_CHANNEL_ADDR, 0xFFFFFFFF);
		}
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_thirdmd_uplink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR, (1 << HI6555C_THIRDMD_UPLINK_FIFO_CLR_BIT_START));
		udelay(1);
		hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR, (1 << HI6555C_THIRDMD_UPLINK_FIFO_CLR_BIT_START));

		for  (i = 0; i < 16; i++) {
			hi6555c_clr_reg_bits(HI6555C_THIRDMD_UPLINK_CHANNEL_ADDR, 0xFFFFFFFF);
		}
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_stereo_uplink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
				(1 << HI6555C_STEREO_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_UPLINK_R_FIFO_CLR_BIT_START));
		udelay(1);
		hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
				(1 << HI6555C_STEREO_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_UPLINK_R_FIFO_CLR_BIT_START));

		for (i = 0; i < 16; i++) {
			hi6555c_clr_reg_bits(HI6555C_STEREO_UPLINK_CHANNEL_ADDR, 0xFFFFFFFF);
		}
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_dacl_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR, (1 << HI6555C_SMT_DACL_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR, (1 << HI6555C_SMT_DACL_PU_BIT_START));
		usleep_range(200, 250);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR, (1 << HI6555C_SMT_DACL_PU_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR, (1 << HI6555C_SMT_DACL_EN_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static int hi6555c_dacr_power_mode_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		hi6555c_set_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR, (1 << HI6555C_SMT_DACR_EN_BIT_START));
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR, (1 << HI6555C_SMT_DACR_PU_BIT_START));
		usleep_range(200, 250);
		break;
	case SND_SOC_DAPM_POST_PMD:
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR, (1 << HI6555C_SMT_DACR_PU_BIT_START));
		hi6555c_clr_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR, (1 << HI6555C_SMT_DACR_EN_BIT_START));
		break;
	default:
		loge("power mode event err : %d\n", event);
		break;
	}

	return 0;
}

static const struct snd_kcontrol_new hi6555c_stereo_uplink_l_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("STEREO_UP_L_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_STEREO_UPLINK_L_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_stereo_uplink_r_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("STEREO_UP_R_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_STEREO_UPLINK_R_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_voice_uplink_l_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("VOICE_UPLINK_L_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_VOICE_UPLINK_L_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_voice_uplink_r_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("VOICE_UPLINK_R_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_VOICE_UPLINK_R_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_thirdmd_dlink_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("THIRDMD_DLINK_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_THIRDMD_DLINK_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_thirdmd_uplink_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("THIRDMD_UPLINK_EN",
			HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_THIRDMD_UPLINK_EN_BIT_START, 1, 0/* not INVERT */),
};

static const char *hi6555c_rm_codec_dac2adc_mux_texts[] = {
	"CIC_ADC",
	"CIC_DACL",
	"CIC_DACR",
	"RESERVED",
	"CIC_DMIC_PORT0",
	"RESERVED",
};

static const struct soc_enum hi6555c_rm_codec_dac2adc_mux_enum =
SOC_ENUM_SINGLE(HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_RM_CODEC_DAC2ADC_BIT_START,
		ARRAY_SIZE(hi6555c_rm_codec_dac2adc_mux_texts), hi6555c_rm_codec_dac2adc_mux_texts);

static const struct snd_kcontrol_new hi6555c_rm_codec_dac2adc_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_rm_codec_dac2adc_mux_enum);

static const char *hi6555c_lm_codec_dac2adc_mux_texts[] = {
	"CIC_ADC",
	"CIC_DACL",
	"CIC_DACR",
	"RESERVED",
	"CIC_DMIC_PORT0",
	"RESERVED",
};

static const struct soc_enum hi6555c_lm_codec_dac2adc_mux_enum =
SOC_ENUM_SINGLE(HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_LM_CODEC_DAC2ADC_BIT_START,
		ARRAY_SIZE(hi6555c_lm_codec_dac2adc_mux_texts), hi6555c_lm_codec_dac2adc_mux_texts);

static const struct snd_kcontrol_new hi6555c_lm_codec_dac2adc_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_lm_codec_dac2adc_mux_enum);

static const struct snd_kcontrol_new hi6555c_dacl_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("DACL_MIXER_IN1_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN1_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("DACL_MIXER_IN2_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("DACL_MIXER_IN3_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN3_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("DACL_MIXER_IN4_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN4_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_dacr_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("DACR_MIXER_IN1_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN1_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("DACR_MIXER_IN2_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("DACR_MIXER_IN3_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN3_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("DACR_MIXER_IN4_MUTE",
			HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN4_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s2_ol_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("S2_OL_MIXER_IN1_MUTE",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_MIXER_IN1_MUTE_BIT_START, 1, 1/* INVERT */),
	SOC_DAPM_SINGLE("S2_OL_MIXER_IN2_MUTE",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_voice_dlink_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("VOICE_DL_MIXER_IN1_MUTE",
			HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT7, 1, 0/* INVERT */),
	SOC_DAPM_SINGLE("VOICE_DL_MIXER_IN2_MUTE",
			HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s1_if_rx_ena_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("FM_L",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT0, 1, 0/*NO INVERT */),
	SOC_DAPM_SINGLE("FM_R",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT1, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s1_if_tx_ena_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("ADC_LR",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT2, 1, 0/*NO INVERT */),
	SOC_DAPM_SINGLE("DAC_LR",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT3, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s2_if_rx_ena_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("VOICE_UL",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT4, 1, 0/*NO INVERT */),
	SOC_DAPM_SINGLE("VOICE_UR",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT5, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s2_if_tx_ena_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("DACL",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT6, 1, 0/*NO INVERT */),
	SOC_DAPM_SINGLE("VOICE_DLINK",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT7, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s3_if_rx_ena_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("VOICE_UP",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT8, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s3_if_tx_ena_mixer_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("VOICE_DL",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT9, 1, 0/*NO INVERT */),
	SOC_DAPM_SINGLE("VOICE_DR",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT10, 1, 0/*NO INVERT */),
};

static const char *hi6555c_stereo_uplink_l_fifo_din_sel_mux_texts[] = {
	"S1",
	"ADCL",
};

static const struct soc_enum hi6555c_stereo_uplink_l_fifo_din_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_STEREO_UPLINK_L_FIFO_DIN_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_stereo_uplink_l_fifo_din_sel_mux_texts), hi6555c_stereo_uplink_l_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_uplink_l_fifo_din_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_stereo_uplink_l_fifo_din_sel_mux_enum);

static const char *hi6555c_stereo_uplink_r_fifo_din_sel_mux_texts[] = {
	"S1",
	"ADCR",
};

static const struct soc_enum hi6555c_stereo_uplink_r_fifo_din_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_STEREO_UPLINK_R_FIFO_DIN_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_stereo_uplink_r_fifo_din_sel_mux_texts), hi6555c_stereo_uplink_r_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_uplink_r_fifo_din_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_stereo_uplink_r_fifo_din_sel_mux_enum);

static const char *hi6555c_voice_uplink_l_fifo_din_sel_mux_texts[] = {
	"S2",
	"ADCL",
};

static const struct soc_enum hi6555c_voice_uplink_l_fifo_din_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_UPLINK_L_FIFO_DIN_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_voice_uplink_l_fifo_din_sel_mux_texts), hi6555c_voice_uplink_l_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_uplink_l_fifo_din_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_voice_uplink_l_fifo_din_sel_mux_enum);

static const char *hi6555c_voice_uplink_r_fifo_din_sel_mux_texts[] = {
	"S2",
	"ADCR",
};

static const struct soc_enum hi6555c_voice_uplink_r_fifo_din_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_UPLINK_R_FIFO_DIN_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_voice_uplink_r_fifo_din_sel_mux_texts), hi6555c_voice_uplink_r_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_uplink_r_fifo_din_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_voice_uplink_r_fifo_din_sel_mux_enum);

static const char *hi6555c_stereo_uplink_r_test_sel_mux_texts[] = {
	"A_U_R",
	"AUDIO_DR",
};

static const struct soc_enum hi6555c_stereo_uplink_r_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_UPLINK_TEST_SEL_ADDR, HI6555C_STEREO_UPLINK_R_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_stereo_uplink_r_test_sel_mux_texts), hi6555c_stereo_uplink_r_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_uplink_r_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_stereo_uplink_r_test_sel_mux_enum);

static const char *hi6555c_stereo_uplink_l_test_sel_mux_texts[] = {
	"A_U_L",
	"AUDIO_DL",
};

static const struct soc_enum hi6555c_stereo_uplink_l_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_UPLINK_TEST_SEL_ADDR, HI6555C_STEREO_UPLINK_L_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_stereo_uplink_l_test_sel_mux_texts), hi6555c_stereo_uplink_l_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_uplink_l_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_stereo_uplink_l_test_sel_mux_enum);

static const char *hi6555c_voice_uplink_l_test_sel_mux_texts[] = {
	"V_U_L",
	"VOICE_",
};

static const struct soc_enum hi6555c_voice_uplink_l_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_UPLINK_TEST_SEL_ADDR, HI6555C_VOICE_UPLINK_L_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_voice_uplink_l_test_sel_mux_texts), hi6555c_voice_uplink_l_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_uplink_l_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_voice_uplink_l_test_sel_mux_enum);

static const char *hi6555c_thirdmd_uplink_l_test_sel_mux_texts[] = {
	"U_3RD",
	"MODEM_D_3RD",
};

static const struct soc_enum hi6555c_thirdmd_uplink_l_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_UPLINK_TEST_SEL_ADDR, HI6555C_THIRDMD_UPLINK_L_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_thirdmd_uplink_l_test_sel_mux_texts), hi6555c_thirdmd_uplink_l_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_thirdmd_uplink_l_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_thirdmd_uplink_l_test_sel_mux_enum);

static const char *hi6555c_smart_pa_fb_sel_mux_texts[] = {
	"S3_L",
	"S1_L_P",
};

static const struct soc_enum hi6555c_smart_pa_fb_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_UPLINK_TEST_SEL_ADDR, HI6555C_SMART_PA_FB_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_smart_pa_fb_sel_mux_texts), hi6555c_smart_pa_fb_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_smart_pa_fb_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_smart_pa_fb_sel_mux_enum);

static const struct snd_kcontrol_new hi6555c_sif_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("SIF_DACL_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT11, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_DACR_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT12, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_ADCL_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT13, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_ADCR_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT14, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_sif_en_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("SIF_HSLR_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT15, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_CLASSD_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT16, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_RCV_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT17, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_MIC1_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT18, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_MIC2_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT19, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_LINEINL_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT20, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("SIF_LINEINR_EN",
			HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT21, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_hs_linein_sel_vir_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("LINEIN", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT22, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_hs_dac_sel_vir_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("DAC", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT23, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_dac_p2s_loopback_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("DAC_P2S_LOOPBACK", HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_DAC_P2S_LOOPBACK_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_sif_s2p_loopback_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("SIF_S2P_LOOPBACK", HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_SIF_S2P_LOOPBACK_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_dmic_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("DMIC_EN", HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_DMIC_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_ana_loopback_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("ANA_LOOPBACK", HI6555C_SMT_CODEC_ANA_RW04_ADDR, (HI6555C_SMT_VREFSEL_BIT_START + 2), 1, 0/* not INVERT */),
};

static const char *hi6555c_s2_dout_left_sel_mux_texts[] = {
	"SRC3",
	"VOICE_DLINK_PGA",
};

static const struct soc_enum hi6555c_s2_dout_left_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S2_DOUT_LEFT_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_s2_dout_left_sel_mux_texts), hi6555c_s2_dout_left_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s2_dout_left_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_s2_dout_left_sel_mux_enum);

static const char *hi6555c_s1_dout_test_sel_mux_texts[] = {
	"DACL_MIXER_DACR_MIXER",
	"ADCL_ADCR",
};

static const struct soc_enum hi6555c_s1_dout_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S1_DOUT_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_s1_dout_test_sel_mux_texts), hi6555c_s1_dout_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s1_dout_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_s1_dout_test_sel_mux_enum);

static const char *hi6555c_s2_dout_test_sel_mux_texts[] = {
	"VOICE_DLINK_PGA_S2",
	"DACL_MIXER",
};

static const struct soc_enum hi6555c_s2_dout_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S2_DOUT_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_s2_dout_test_sel_mux_texts), hi6555c_s2_dout_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s2_dout_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_s2_dout_test_sel_mux_enum);

static const char *hi6555c_stereo_dlink_test_sel_mux_texts[] = {
	"APB",
	"S1_STEREO_DLINK_L_S1_STEREO_DLINK_R",
};

static const struct soc_enum hi6555c_stereo_dlink_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_STEREO_DLINK_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_stereo_dlink_test_sel_mux_texts), hi6555c_stereo_dlink_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_dlink_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("ST_DL Mux", hi6555c_stereo_dlink_test_sel_mux_enum);

static const char *hi6555c_voice_dlink_din_sel_mux_texts[] = {
	"APB",
	"S3",
};

static const struct soc_enum hi6555c_voice_dlink_din_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_VOICE_DLINK_DIN_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_voice_dlink_din_sel_mux_texts), hi6555c_voice_dlink_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_dlink_din_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_voice_dlink_din_sel_mux_enum);

static const char *hi6555c_voice_dlink_test_sel_mux_texts[] = {
	"FRONTSEL",
	"S2",
};

static const struct soc_enum hi6555c_voice_dlink_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_VOICE_DLINK_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_voice_dlink_test_sel_mux_texts), hi6555c_voice_dlink_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_dlink_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_voice_dlink_test_sel_mux_enum);

#if 0
/*not used for dallas*/
static const char *hi6555c_s3_din_test_sel_mux_texts[] = {
	"LEFT",
	"RIGHT",
};

static const struct soc_enum hi6555c_s3_din_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S3_DIN_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_s3_din_test_sel_mux_texts), hi6555c_s3_din_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s3_din_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_s3_din_test_sel_mux_enum);
#endif

static const char *hi6555c_s3_dout_left_sel_mux_texts[] = {
	"THIRDMD_DLINK_PGA",
	"ADCL_PGA",
};

static const struct soc_enum hi6555c_s3_dout_left_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S3_DOUT_LEFT_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_s3_dout_left_sel_mux_texts), hi6555c_s3_dout_left_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s3_dout_left_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_s3_dout_left_sel_mux_enum);

static const char *hi6555c_s3_dout_right_sel_mux_texts[] = {
	"THIRDMD_DLINK_PGA",
	"ADCR_PGA",
	"OTHER",
};

static const struct soc_enum hi6555c_s3_dout_right_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S3_DOUT_RIGHT_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_s3_dout_right_sel_mux_texts), hi6555c_s3_dout_right_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s3_dout_right_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_s3_dout_right_sel_mux_enum);

static const char *hi6555c_thirdmd_dlink_din_sel_mux_texts[] = {
	"APB_THIRDMD",
	"S2",
};

static const struct soc_enum hi6555c_thirdmd_dlink_din_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_THIRDMD_DLINK_DIN_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_thirdmd_dlink_din_sel_mux_texts), hi6555c_thirdmd_dlink_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_thirdmd_dlink_din_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_thirdmd_dlink_din_sel_mux_enum);

#if 0
/*not used for dallas*/
static const char *hi6555c_thirdmd_dlink_test_sel_mux_texts[] = {
	"APB_THIRDMD_S2",
	"S3",
};

static const struct soc_enum hi6555c_thirdmd_dlink_test_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_THIRDMD_DLINK_TEST_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_thirdmd_dlink_test_sel_mux_texts), hi6555c_thirdmd_dlink_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_thirdmd_dlink_test_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_thirdmd_dlink_test_sel_mux_enum);
#endif
static const struct snd_kcontrol_new hi6555c_smt_dacl_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("DACL_EN", HI6555C_SMT_CLK_EN_CFG_ADDR, HI6555C_SMT_DACL_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_dacr_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("DACR_EN", HI6555C_SMT_CLK_EN_CFG_ADDR, HI6555C_SMT_DACR_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_sif_en_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("SIF_EN", HI6555C_SMT_CLK_EN_CFG_ADDR, HI6555C_SMT_SIF_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_classd_virtual_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("CLASSD_EN", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT24, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_rcv_virtual_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("RCV_EN", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT25, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_dacr_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("SMT_DACR_EN", HI6555C_SMT_CODEC_ANA_RW13_ADDR, DDR_CODEC_BIT6, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_dacl_switch_dapm_controls[] = {
	SOC_DAPM_SINGLE("SMT_DACL_EN", HI6555C_SMT_CODEC_ANA_RW13_ADDR, DDR_CODEC_BIT3, 1, 0/* not INVERT */),
};

static const char *hi6555c_smt_mainpga_sel_mux_texts[] = {
	"MUTE",
	"MIC",
	"HP_MIC",
	/* "MUTE",  11:MUTE */
};

static const struct soc_enum hi6555c_smt_mainpga_sel_mux_enum =
SOC_ENUM_SINGLE(HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_SEL_BIT_START,
		ARRAY_SIZE(hi6555c_smt_mainpga_sel_mux_texts), hi6555c_smt_mainpga_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_smt_mainpga_sel_mux_dapm_controls =
SOC_DAPM_ENUM("Mux", hi6555c_smt_mainpga_sel_mux_enum);

static const struct snd_kcontrol_new hi6555c_smt_adcr_pd_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("AUXPGA",
			HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START + 0), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("MAINPGA",
			HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START + 1), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("LINEINR",
			HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START + 2), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("LINEINL",
			HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START + 3), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACR",
			HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START + 4), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACL",
			HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START + 5), 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_adcl_pd_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("AUXPGA",
			HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START + 0), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("MAINPGA",
			HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START + 1), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("LINEINR",
			HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START + 2), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("LINEINL",
			HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START + 3), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACR",
			HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START + 4), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACL",
			HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START + 5), 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_mixout_hslr_pd_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("LINEINLR", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT26, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACLR", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT27, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_mixout_ear_pu_mixer_dapm_controls[] = {
	SOC_DAPM_SINGLE("LINEINR", HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_MIXOUT_EAR_BIT_START + 0), 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("LINEINL", HI6555C_SMT_CODEC_ANA_RW14_ADDR, HI6555C_SMT_MIXOUT_EAR_BIT_START + 1, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACR", HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT3, 1, 0/* not INVERT */),
	SOC_DAPM_SINGLE("DACL", HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT4, 1, 0/* not INVERT */),
};

/* fm */
static const struct snd_kcontrol_new hi6555c_dapm_fm_controls[] = {
	SOC_DAPM_SINGLE("SWITCH", HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT8, 1, 0),
};

/*****************************************************************************
  Widgets
 *****************************************************************************/
static const struct snd_soc_dapm_widget hi6555c_dapm_widgets[] = {
		/* INPUT */
		SND_SOC_DAPM_INPUT("VOICE_DL INPUT"),
		SND_SOC_DAPM_INPUT("AUDIO_DLINK INPUT"),
		SND_SOC_DAPM_INPUT("THIRDMD_DOWN INPUT"),
		SND_SOC_DAPM_INPUT("DIGI_ADC_UL INPUT"),
		SND_SOC_DAPM_INPUT("DIGI_ADC_UR INPUT"),
		SND_SOC_DAPM_INPUT("DMIC INPUT"),
		SND_SOC_DAPM_INPUT("I2S1_2_3 INPUT"),
		SND_SOC_DAPM_INPUT("SIF_EN INPUT"),
		SND_SOC_DAPM_INPUT("SMT_ANA_DAC_SDATA INPUT"),
		SND_SOC_DAPM_INPUT("SMT_MAINMIC INPUT"),
		SND_SOC_DAPM_INPUT("SMT_HPMIC INPUT"),
		SND_SOC_DAPM_INPUT("SMT_AUXMIC INPUT"),
		SND_SOC_DAPM_INPUT("SMT_LINEIN_L INPUT"),
		SND_SOC_DAPM_INPUT("SMT_LINEIN_R INPUT"),

		/* OUTPUT*/
		SND_SOC_DAPM_OUTPUT("SIF_EN OUTPUT"),
		SND_SOC_DAPM_OUTPUT("VOICE_UL OUTPUT"),
		SND_SOC_DAPM_OUTPUT("VOICE_UR OUTPUT"),
		SND_SOC_DAPM_OUTPUT("AUDIO_UL OUTPUT"),
		SND_SOC_DAPM_OUTPUT("AUDIO_UR OUTPUT"),
		SND_SOC_DAPM_OUTPUT("THIRDMD_UP OUTPUT"),
		SND_SOC_DAPM_OUTPUT("SMT_HP_LR OUTPUT"),
		SND_SOC_DAPM_OUTPUT("SMT_HPMIC OUTPUT"),
		SND_SOC_DAPM_OUTPUT("SMT_SPEAKER OUTPUT"),
		SND_SOC_DAPM_OUTPUT("SMT_RECV OUTPUT"),
		SND_SOC_DAPM_OUTPUT("SMT_ANA_ADC_SDATA OUTPUT"),
		SND_SOC_DAPM_OUTPUT("PMU_CLASSD OUTPUT"),
		SND_SOC_DAPM_OUTPUT("I2S1_2_3 OUTPUT"),

		/* PGA */
		SND_SOC_DAPM_PGA_E("STEREO_DLINK_L_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_STEREO_DLINK_L_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_stereo_dlink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_PGA_E("STEREO_DLINK_R_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_STEREO_DLINK_R_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_stereo_dlink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_PGA_E("VOICE_DLINK_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_VOICE_DLINK_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_voice_dlink_fifo_power_mode_event,
				(SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD)),

		SND_SOC_DAPM_PGA("S1_IL_PGA_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S1_IL_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("S1_IR_PGA_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S1_IR_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("S2_IL_PGA_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S2_IL_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("S2_IR_PGA_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S2_IR_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SIF_ADCL_EN PGA",
				HI6555C_DMIC_SIF_CFG_ADDR,
				HI6555C_SIF_ADCL_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SIF_ADCR_EN PGA",
				HI6555C_DMIC_SIF_CFG_ADDR,
				HI6555C_SIF_ADCR_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SIF_DACL_EN PGA",
				HI6555C_DMIC_SIF_CFG_ADDR,
				HI6555C_SIF_DACL_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SIF_DACR_EN PGA",
				HI6555C_DMIC_SIF_CFG_ADDR,
				HI6555C_SIF_DACR_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SMT_SIF_ADCL_EN PGA",
				HI6555C_SMT_CLK_EN_CFG_ADDR,
				HI6555C_SMT_ADCL_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SMT_SIF_ADCR_EN PGA",
				HI6555C_SMT_CLK_EN_CFG_ADDR,
				HI6555C_SMT_ADCR_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_DAC_E("SMT_SIF_DACL_EN DAC",
				"Playback",
				HI6555C_DDR_CODEC_VIR1_ADDR,
				DDR_CODEC_BIT5,
				0/* not INVERT */,
				hi6555c_dacl_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_DAC_E("SMT_SIF_DACR_EN DAC",
				"Playback",
				HI6555C_DDR_CODEC_VIR1_ADDR,
				DDR_CODEC_BIT6,
				0/* not INVERT */,
				hi6555c_dacr_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA("S1_IF_CLK_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S1_IF_CLK_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("S2_IF_CLK_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S2_IF_CLK_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("S3_IF_CLK_EN PGA",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S3_IF_CLK_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("ADCL_PGA_EN PGA",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_ADCL_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SIDETONE_PGA_EN PGA",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_SIDETONE_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA_S("SMT_LINEPGAR_PD PGA",
				0,
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_smt_lineinr_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_S("SMT_LINEPGAL_PD PGA",
				0,
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_smt_lineinl_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA("SMT_AUXPGA_PD PGA",
				HI6555C_SMT_CODEC_ANA_RW01_ADDR,
				HI6555C_SMT_AUXPGA_PD_BIT_START,
				1/* INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA("SMT_MAINPGA_PD PGA",
				HI6555C_SMT_CODEC_ANA_RW01_ADDR,
				HI6555C_SMT_MAINPGA_PD_BIT_START,
				1/* INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_PGA_E("SMT_DACL_MIXER PGA",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_dacl_mixer_en_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_E("SMT_DACR_MIXER PGA",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_dacr_mixer_en_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_DAC_E("SMT_HS_PREPROCESS DAC",
				"Playback",
				HI6555C_DDR_CODEC_VIR0_ADDR,
				DDR_CODEC_BIT28,
				0/* not INVERT */,
				hi6555c_hs_preprocess_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_DAC_E("SMT_MIXEROUT_DAC_PATH DAC",
				"Playback",
				HI6555C_DDR_CODEC_VIR0_ADDR,
				DDR_CODEC_BIT29,
				0/* not INVERT */,
				hi6555c_dac_path_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_S("SMT_MIXEROUT_LINEIN_PATH DAC",
				1,
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_linein_path_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_E("DACL_AGC_EN PGA",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_DACL_AGC_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_dacl_agc_en_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_E("DACR_AGC_EN PGA",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_DACR_AGC_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_dacr_agc_en_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_E("ADCR_PGA_EN PGA",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_ADCR_PGA_EN_BIT_START,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_adcr_pga_en_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_PGA_E("ADCL_FILTER_EN PGA",
				HI6555C_DDR_CODEC_VIR1_ADDR,
				DDR_CODEC_BIT0,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_adcl_pga_en_pga_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_MIXER("S2_OL_MIXER_EN MIXER",
				HI6555C_IF_CLK_EN_CFG_ADDR,
				HI6555C_S2_OL_MIXER_EN_BIT_START,
				0/* not INVERT */,
				hi6555c_s2_ol_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s2_ol_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("VOICE_DL_EN MIXER",
				HI6555C_MUX_TOP_MODULE_CFG_ADDR,
				7,
				0/* not INVERT */,
				hi6555c_voice_dlink_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_voice_dlink_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("S1_IF_TX_ENA MIXER",
				HI6555C_I2S_CFG_ADDR,
				HI6555C_S1_IF_TX_ENA_BIT_START,
				0/* not INVERT */,
				hi6555c_s1_if_tx_ena_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s1_if_tx_ena_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("S1_IF_RX_ENA MIXER",
				HI6555C_I2S_CFG_ADDR,
				HI6555C_S1_IF_RX_ENA_BIT_START,
				0/* not INVERT */,
				hi6555c_s1_if_rx_ena_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s1_if_rx_ena_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("S2_IF_TX_ENA MIXER",
				HI6555C_I2S_CFG_ADDR,
				HI6555C_S2_IF_TX_ENA_BIT_START,
				0/* not INVERT */,
				hi6555c_s2_if_tx_ena_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s2_if_tx_ena_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("S2_IF_RX_ENA MIXER",
				HI6555C_I2S_CFG_ADDR,
				HI6555C_S2_IF_RX_ENA_BIT_START,
				0/* not INVERT */,
				hi6555c_s2_if_rx_ena_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s2_if_rx_ena_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("S3_IF_TX_ENA MIXER",
				HI6555C_THIRDMD_PCM_PGA_CFG_ADDR,
				HI6555C_S3_IF_TX_ENA_BIT_START,
				0/* not INVERT */,
				hi6555c_s3_if_tx_ena_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s3_if_tx_ena_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("S3_IF_RX_ENA MIXER",
				HI6555C_THIRDMD_PCM_PGA_CFG_ADDR,
				HI6555C_S3_IF_RX_ENA_BIT_START,
				0/* not INVERT */,
				hi6555c_s3_if_rx_ena_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_s3_if_rx_ena_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("DACL_MIXER_EN MIXER",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_DACL_MIXER_EN_BIT_START,
				0/* not INVERT */,
				hi6555c_dacl_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_dacl_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("DACR_MIXER_EN MIXER",
				HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
				HI6555C_DACR_MIXER_EN_BIT_START,
				0/* not INVERT */,
				hi6555c_dacr_mixer_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_dacr_mixer_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("SIF_EN MIXER",
				HI6555C_DMIC_SIF_CFG_ADDR,
				HI6555C_SIF_EN_BIT_START,
				0/* not INVERT */,
				hi6555c_sif_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_sif_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("SMT_MIXOUT_EAR_PU MIXER",
				HI6555C_SMT_CODEC_ANA_RW39_ADDR,
				HI6555C_SMT_MIXOUT_EAR_PU_BIT_START,
				0/* not INVERT */,
				hi6555c_smt_mixout_ear_pu_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_smt_mixout_ear_pu_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("SMT_SIF_EN MIXER",
				HI6555C_SMT_CLK_EN_CFG_ADDR,
				HI6555C_SMT_SIF_EN_BIT_START,
				0/* not INVERT */,
				hi6555c_smt_sif_en_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_smt_sif_en_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("SMT_ADCR_PD MIXER",
				HI6555C_SMT_CODEC_ANA_RW01_ADDR,
				HI6555C_SMT_ADCR_PD_BIT_START,
				1/* INVERT */,
				hi6555c_smt_adcr_pd_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_smt_adcr_pd_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER("SMT_ADCL_PD MIXER",
				HI6555C_SMT_CODEC_ANA_RW01_ADDR,
				HI6555C_SMT_ADCL_PD_BIT_START,
				1/* INVERT */,
				hi6555c_smt_adcl_pd_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_smt_adcl_pd_mixer_dapm_controls)),

		SND_SOC_DAPM_MIXER_E("SMT_MIXOUT_HSLR_PD MIXER",
				HI6555C_DDR_CODEC_VIR1_ADDR,
				DDR_CODEC_BIT1,
				0/* INVERT */,
				hi6555c_smt_mixout_hslr_pd_mixer_dapm_controls,
				ARRAY_SIZE(hi6555c_smt_mixout_hslr_pd_mixer_dapm_controls),
				hi6555c_smt_hslr_pd_mixer_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_MUX("RM_CODEC_DAC2ADC MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_rm_codec_dac2adc_mux_dapm_controls),

		SND_SOC_DAPM_MUX("LM_CODEC_DAC2ADC MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_lm_codec_dac2adc_mux_dapm_controls),

		SND_SOC_DAPM_MUX("STEREO_UPLINK_L_FIFO_DIN_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_stereo_uplink_l_fifo_din_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("STEREO_UPLINK_R_FIFO_DIN_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_stereo_uplink_r_fifo_din_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("VOICE_UPLINK_L_FIFO_DIN_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_voice_uplink_l_fifo_din_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("VOICE_UPLINK_R_FIFO_DIN_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_voice_uplink_r_fifo_din_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("S2_DOUT_LEFT_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_s2_dout_left_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("S1_DOUT_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_s1_dout_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("S2_DOUT_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_s2_dout_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("STEREO_DLINK_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_stereo_dlink_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("VOICE_DLINK_DIN_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_voice_dlink_din_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("VOICE_DLINK_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_voice_dlink_test_sel_mux_dapm_controls),

#if 0
		/*not used for dallas*/
		SND_SOC_DAPM_MUX("S3_DIN_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_s3_din_test_sel_mux_dapm_controls),
#endif

		SND_SOC_DAPM_MUX("S3_DOUT_LEFT_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_s3_dout_left_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("S3_DOUT_RIGHT_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_s3_dout_right_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("THIRDMD_DLINK_DIN_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_thirdmd_dlink_din_sel_mux_dapm_controls),
#if 0
		/*not used for dallas*/
		SND_SOC_DAPM_MUX("THIRDMD_DLINK_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_thirdmd_dlink_test_sel_mux_dapm_controls),
#endif

		SND_SOC_DAPM_MUX("SMT_MAINPGA_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_smt_mainpga_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("STEREO_UPLINK_R_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_stereo_uplink_r_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("STEREO_UPLINK_L_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_stereo_uplink_l_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("VOICE_UPLINK_L_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_voice_uplink_l_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("THIRDMD_UPLINK_L_TEST_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_thirdmd_uplink_l_test_sel_mux_dapm_controls),

		SND_SOC_DAPM_MUX("SMART_PA_FB_SEL MUX",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				&hi6555c_smart_pa_fb_sel_mux_dapm_controls),


		SND_SOC_DAPM_SWITCH("HS_LINEIN_SEL_VIR SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_hs_linein_sel_vir_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("HS_DAC_SEL_VIR SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_hs_dac_sel_vir_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("DAC_P2S_LOOPBACK SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_dac_p2s_loopback_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("SIF_S2P_LOOPBACK SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_sif_s2p_loopback_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("DMIC_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_dmic_en_switch_dapm_controls),

		/* ADD FOR ANA LOOPBACK */
		SND_SOC_DAPM_SWITCH("ANA_LOOPBACK SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_ana_loopback_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("SMT_SIF_EN_V2 SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_smt_sif_en_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH_E("THIRDMD_DLINK_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_thirdmd_dlink_en_switch_dapm_controls,
				hi6555c_thirdmd_dlink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_SWITCH_E("THIRDMD_UPLINK_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_thirdmd_uplink_en_switch_dapm_controls,
				hi6555c_thirdmd_uplink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_SWITCH("CLASSD VIR_SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_classd_virtual_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("RCV VIR_SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_rcv_virtual_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("SMT DACL_SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_smt_dacl_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH("SMT DACR_SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_smt_dacr_switch_dapm_controls),

		SND_SOC_DAPM_SWITCH_E("STEREO_UPLINK_L_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_stereo_uplink_l_en_switch_dapm_controls,
				hi6555c_stereo_uplink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_SWITCH_E("STEREO_UPLINK_R_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_stereo_uplink_r_en_switch_dapm_controls,
				hi6555c_stereo_uplink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_SWITCH_E("VOICE_UPLINK_L_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_voice_uplink_l_en_switch_dapm_controls,
				hi6555c_voice_uplink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		SND_SOC_DAPM_SWITCH_E("VOICE_UPLINK_R_EN SWITCH",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				hi6555c_voice_uplink_r_en_switch_dapm_controls,
				hi6555c_voice_uplink_fifo_power_mode_event,
				SND_SOC_DAPM_POST_PMU),

		/* virtual switch for fm */
		SND_SOC_DAPM_SWITCH_E("FM SWITCH",
				SND_SOC_NOPM, 0, 0,
				hi6555c_dapm_fm_controls,
				hi6555c_fm_mode_event, (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_MICBIAS("SMT_HSMICB_PD MICBIAS",
				SND_SOC_NOPM/*HI6555C_SMT_CODEC_ANA_RW02_ADDR*/,
				HI6555C_SMT_HSMICB_PD_BIT_START,
				1/* INVERT */),

		SND_SOC_DAPM_MICBIAS("SMT_MICB1_PD MICBIAS",
				HI6555C_SMT_CODEC_ANA_RW02_ADDR,
				HI6555C_SMT_MICB1_PD_BIT_START,
				1/* INVERT */),

		SND_SOC_DAPM_OUT_DRV("SMT_EAR_PU PGA",
				HI6555C_SMT_CODEC_ANA_RW39_ADDR,
				HI6555C_SMT_EAR_PU_BIT_START,
				0/* not INVERT */,
				NULL,
				0),

		SND_SOC_DAPM_OUT_DRV_E("SMT_HSLR_PD PGA",
				HI6555C_DDR_CODEC_VIR1_ADDR,
				DDR_CODEC_BIT2,
				0/*not INVERT */,
				NULL,
				0,
				hi6555c_smt_hslr_pd_outdrv_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_OUT_DRV_E("PMU_CLASSD_PU PGA",
				SND_SOC_NOPM,
				0,
				0/* not INVERT */,
				NULL,
				0,
				hi6555c_pmu_classd_pd_outdrv_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		/* SUPPLY */
		SND_SOC_DAPM_SUPPLY("PLL",
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_pll_supply_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_SUPPLY("Backup_PLL",
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_backuppll_supply_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_SUPPLY("SOC_IBIAS",
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_soc_ibias_supply_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		SND_SOC_DAPM_SUPPLY("SMT_IBIAS",
				SND_SOC_NOPM,
				0,
				0,
				hi6555c_smt_ibias_supply_power_mode_event,
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

		/* MIC */
		SND_SOC_DAPM_MIC("SMT_MICB1", hi6555c_smt_micb1_power_mode_event),
		SND_SOC_DAPM_MIC("SMT_HSMICB", hi6555c_smt_hsmicb_power_mode_event),
};


/*****************************************************************************
  Route Map
 *****************************************************************************/
static const struct snd_soc_dapm_route hi6555c_route_map[] = {
	/* audio play route soc */
	{"STEREO_DLINK_TEST_SEL MUX",               "APB",                  "AUDIO_DLINK INPUT"},
	{"STEREO_DLINK_L_EN PGA",                       NULL,                   "STEREO_DLINK_TEST_SEL MUX"},
	{"STEREO_DLINK_R_EN PGA",                      NULL,                   "STEREO_DLINK_TEST_SEL MUX"},
	{"DACL_MIXER_EN MIXER",            "DACL_MIXER_IN2_MUTE",  "STEREO_DLINK_L_EN PGA"},
	{"DACR_MIXER_EN MIXER",           "DACR_MIXER_IN2_MUTE",  "STEREO_DLINK_R_EN PGA"},
	{"DACL_AGC_EN PGA",                                NULL,                   "DACL_MIXER_EN MIXER"},
	{"DACR_AGC_EN PGA",                               NULL,                   "DACR_MIXER_EN MIXER"},
	{"SIF_DACL_EN PGA",                                 NULL,                    "DACL_AGC_EN PGA"},
	{"SIF_DACR_EN PGA",                                NULL,                    "DACR_AGC_EN PGA"},
	{"SMT_SIF_DACL_EN DAC",                        NULL,                    "SMT_ANA_DAC_SDATA INPUT"},
	{"SMT_SIF_DACR_EN DAC",                       NULL,                    "SMT_ANA_DAC_SDATA INPUT"},
	{"HS_DAC_SEL_VIR SWITCH",                   "DAC",                   "SMT_SIF_DACL_EN DAC"},
	{"HS_DAC_SEL_VIR SWITCH",                   "DAC",                   "SMT_SIF_DACR_EN DAC"},
	{"HS_LINEIN_SEL_VIR SWITCH",                "LINEIN",               "SMT_LINEPGAR_PD PGA"},
	{"HS_LINEIN_SEL_VIR SWITCH",                "LINEIN",               "SMT_LINEPGAL_PD PGA"},
	{"SMT_HS_PREPROCESS DAC",                   NULL,                   "HS_DAC_SEL_VIR SWITCH"},
	{"SMT_HS_PREPROCESS DAC",                   NULL,                   "HS_LINEIN_SEL_VIR SWITCH"},
	{"SMT_MIXEROUT_DAC_PATH DAC",           NULL,                    "SMT_HS_PREPROCESS DAC"},
	{"SMT_MIXEROUT_LINEIN_PATH DAC",        NULL,                    "SMT_HS_PREPROCESS DAC"},

	/* audio play hs route smartstar */
	{"SMT_MIXOUT_HSLR_PD MIXER",              "DACLR",               "SMT_MIXEROUT_DAC_PATH DAC"},
	{"SMT_MIXOUT_HSLR_PD MIXER",              "LINEINLR",            "SMT_MIXEROUT_LINEIN_PATH DAC"},
	{"SMT_HSLR_PD PGA",                               NULL,                    "SMT_MIXOUT_HSLR_PD MIXER"},
	{"SMT_HP_LR OUTPUT",                              NULL,                    "SMT_HSLR_PD PGA"},

	/* audio play rcv route smartstar */
	{"SMT_MIXOUT_EAR_PU MIXER",                 "DACL",                "SMT_DACL_MIXER PGA"},
	{"SMT_MIXOUT_EAR_PU MIXER",                 "DACR",               "SMT_DACR_MIXER PGA"},
	{"SMT_MIXOUT_EAR_PU MIXER",                 "LINEINR",            "SMT_LINEPGAR_PD PGA"},
	{"SMT_MIXOUT_EAR_PU MIXER",                 "LINEINL",             "SMT_LINEPGAL_PD PGA"},
	{"RCV VIR_SWITCH",                                 "RCV_EN",             "SMT_MIXOUT_EAR_PU MIXER"},
	{"SMT_EAR_PU PGA",                                  NULL,                    "RCV VIR_SWITCH"},
	{"SMT_RECV OUTPUT",                                NULL,                   "SMT_EAR_PU PGA"},
	{"SMT_DACL_MIXER PGA",                           NULL,                   "SMT_SIF_DACL_EN DAC"},
	{"SMT_DACR_MIXER PGA",                          NULL,                    "SMT_SIF_DACR_EN DAC"},

	/* audio play classd route pmu */
	{"CLASSD VIR_SWITCH",                       "CLASSD_EN",           "SMT_MIXOUT_EAR_PU MIXER"},
	{"PMU_CLASSD_PU PGA",                           NULL,                    "CLASSD VIR_SWITCH"},
	{"PMU_CLASSD OUTPUT",                           NULL,                    "PMU_CLASSD_PU PGA"},

	/* audio capture route smartstar */
	{"SMT_MAINPGA_SEL MUX",                       "MIC",                   "SMT_MAINMIC INPUT"},
	{"SMT_MAINPGA_SEL MUX",                     "HP_MIC",                "SMT_HPMIC INPUT"},
	{"SMT_MAINPGA_PD PGA",                         NULL,                    "SMT_MAINPGA_SEL MUX"},
	{"SMT_AUXPGA_PD PGA",                          NULL,                    "SMT_AUXMIC INPUT"},
	{"SMT_LINEPGAL_PD PGA",                        NULL,                    "SMT_LINEIN_L INPUT"},
	{"SMT_LINEPGAR_PD PGA",                        NULL,                    "SMT_LINEIN_R INPUT"},
	{"SMT_ADCL_PD MIXER",                         "MAINPGA",             "SMT_MAINPGA_PD PGA"},
	{"SMT_ADCL_PD MIXER",                         "AUXPGA",              "SMT_AUXPGA_PD PGA"},
	{"SMT_ADCL_PD MIXER",                         "LINEINL",               "SMT_LINEPGAL_PD PGA"},
	{"SMT_ADCL_PD MIXER",                         "LINEINR",               "SMT_LINEPGAR_PD PGA"},
	{"SMT_ADCR_PD MIXER",                         "MAINPGA",            "SMT_MAINPGA_PD PGA"},
	{"SMT_ADCR_PD MIXER",                         "AUXPGA",              "SMT_AUXPGA_PD PGA"},
	{"SMT_ADCR_PD MIXER",                         "LINEINL",               "SMT_LINEPGAL_PD PGA"},
	{"SMT_ADCR_PD MIXER",                       "LINEINR",                "SMT_LINEPGAR_PD PGA"},
	{"SMT_SIF_ADCL_EN PGA",                         NULL,                   "SMT_ADCL_PD MIXER"},
	{"SMT_SIF_ADCR_EN PGA",                        NULL,                   "SMT_ADCR_PD MIXER"},
	{"SMT_ANA_ADC_SDATA OUTPUT",             NULL,                    "SMT_SIF_ADCL_EN PGA"},
	{"SMT_ANA_ADC_SDATA OUTPUT",              NULL,                   "SMT_SIF_ADCR_EN PGA"},

	/* audio capture route SoC */
	{"SIF_ADCL_EN PGA",                                NULL,                   "DIGI_ADC_UL INPUT"},
	{"SIF_ADCR_EN PGA",                                NULL,                   "DIGI_ADC_UR INPUT"},
	{"LM_CODEC_DAC2ADC MUX",               "CIC_ADC",              "SIF_ADCL_EN PGA"},
	{"RM_CODEC_DAC2ADC MUX",               "CIC_ADC",             "SIF_ADCR_EN PGA"},
	{"ADCL_FILTER_EN PGA",                            NULL,                  "LM_CODEC_DAC2ADC MUX"},
	{"ADCL_PGA_EN PGA",                                NULL,                  "ADCL_FILTER_EN PGA"},
	{"SIDETONE_PGA_EN PGA",                         NULL,                  "ADCL_FILTER_EN PGA"},
	{"ADCR_PGA_EN PGA",                               NULL,                  "RM_CODEC_DAC2ADC MUX"},
	{"STEREO_UPLINK_L_FIFO_DIN_SEL MUX",  "ADCL",                "ADCL_PGA_EN PGA"},
	{"STEREO_UPLINK_R_FIFO_DIN_SEL MUX",  "ADCR",               "ADCR_PGA_EN PGA"},
	{"STEREO_UPLINK_L_TEST_SEL MUX",      "A_U_L",   "STEREO_UPLINK_L_FIFO_DIN_SEL MUX"},
	{"STEREO_UPLINK_R_TEST_SEL MUX",      "A_U_R",   "STEREO_UPLINK_R_FIFO_DIN_SEL MUX"},
	{"STEREO_UPLINK_L_EN SWITCH",      "STEREO_UP_L_EN",     "STEREO_UPLINK_L_TEST_SEL MUX"},
	{"STEREO_UPLINK_R_EN SWITCH",     "STEREO_UP_R_EN",     "STEREO_UPLINK_R_TEST_SEL MUX"},
	{"AUDIO_UL OUTPUT",                                 NULL,                 "STEREO_UPLINK_L_EN SWITCH"},
	{"AUDIO_UR OUTPUT",                                 NULL,                "STEREO_UPLINK_R_EN SWITCH"},

	/* voice uplink route SoC */
	{"VOICE_UPLINK_L_FIFO_DIN_SEL MUX",      "ADCL",             "ADCL_PGA_EN PGA"},
	{"VOICE_UPLINK_R_FIFO_DIN_SEL MUX",      "ADCR",            "ADCR_PGA_EN PGA"},
	{"VOICE_UPLINK_L_TEST_SEL MUX",        "V_U_L",         "VOICE_UPLINK_L_FIFO_DIN_SEL MUX"},
	{"VOICE_UPLINK_L_EN SWITCH",      "VOICE_UPLINK_L_EN",  "VOICE_UPLINK_L_TEST_SEL MUX"},
	{"VOICE_UPLINK_R_EN SWITCH",     "VOICE_UPLINK_R_EN",  "VOICE_UPLINK_R_FIFO_DIN_SEL MUX"},
	{"VOICE_UL OUTPUT",                                 NULL,                 "VOICE_UPLINK_L_EN SWITCH"},
	{"VOICE_UR OUTPUT",                                 NULL,                "VOICE_UPLINK_R_EN SWITCH"},

	/* voice uplink route BT SoC */
	{"S2_IL_PGA_EN PGA",                                NULL,                "I2S1_2_3 INPUT"},
	{"S2_IR_PGA_EN PGA",                                NULL,                "I2S1_2_3 INPUT"},
	{"VOICE_UPLINK_L_FIFO_DIN_SEL MUX",      "S2",                "S2_IL_PGA_EN PGA"},
	{"VOICE_UPLINK_R_FIFO_DIN_SEL MUX",      "S2",               "S2_IR_PGA_EN PGA"},

	/* voice downlink route SoC */
	{"VOICE_DLINK_DIN_SEL MUX",                   "APB",               "VOICE_DL INPUT"},
	{"VOICE_DLINK_DIN_SEL MUX",                   "S3",                 "I2S1_2_3 INPUT"},
	{"VOICE_DLINK_TEST_SEL MUX",                  "FRONTSEL",           "VOICE_DLINK_DIN_SEL MUX"},
	{"VOICE_DLINK_EN PGA",                            NULL,                "VOICE_DLINK_TEST_SEL MUX"},
	{"VOICE_DL_EN MIXER",      "VOICE_DL_MIXER_IN1_MUTE",  "VOICE_DLINK_EN PGA"},
	{"VOICE_DL_EN MIXER",     "VOICE_DL_MIXER_IN2_MUTE",   "SIDETONE_PGA_EN PGA"},
	{"DACL_MIXER_EN MIXER",     "DACL_MIXER_IN1_MUTE",      "VOICE_DL_EN MIXER"},
	{"DACR_MIXER_EN MIXER",       "DACR_MIXER_IN1_MUTE",   "VOICE_DL_EN MIXER"},
	{"DACL_MIXER_EN MIXER",      "DACL_MIXER_IN4_MUTE",     "SIDETONE_PGA_EN PGA"},
	{"DACR_MIXER_EN MIXER",        "DACR_MIXER_IN4_MUTE",  "SIDETONE_PGA_EN PGA"},

	{"S1_DOUT_TEST_SEL MUX",                    "DACL_MIXER_DACR_MIXER",  "DACL_MIXER_EN MIXER"},
	{"S1_DOUT_TEST_SEL MUX",                    "DACL_MIXER_DACR_MIXER",  "DACR_MIXER_EN MIXER"},
	{"S1_DOUT_TEST_SEL MUX",                    "ADCL_ADCR",           "ADCL_PGA_EN PGA"},
	{"S1_DOUT_TEST_SEL MUX",                    "ADCL_ADCR",           "ADCR_PGA_EN PGA"},
	{"I2S1_2_3 OUTPUT",                         NULL,                  "S1_DOUT_TEST_SEL MUX"},
	/* voice downlink route SoC(bt) */
	{"S2_OL_MIXER_EN MIXER",      "S2_OL_MIXER_IN1_MUTE",    "DACL_MIXER_EN MIXER"},
	{"S2_OL_MIXER_EN MIXER",      "S2_OL_MIXER_IN2_MUTE",    "DACR_MIXER_EN MIXER"},
	{"S2_DOUT_LEFT_SEL MUX",      "SRC3",                                "S2_OL_MIXER_EN MIXER"},
	{"S2_DOUT_LEFT_SEL MUX",      "VOICE_DLINK_PGA",            "VOICE_DLINK_EN PGA"},
	{"S2_DOUT_TEST_SEL MUX",     "VOICE_DLINK_PGA_S2",       "S2_DOUT_LEFT_SEL MUX"},
	{"S2_DOUT_TEST_SEL MUX",     "DACL_MIXER",                      "DACL_MIXER_EN MIXER"},
	{"I2S1_2_3 OUTPUT",                NULL,                                    "S2_DOUT_TEST_SEL MUX"},
	{"S1_IF_TX_ENA MIXER",                      "ADC_LR",              "I2S1_2_3 INPUT"},
	{"S1_IF_TX_ENA MIXER",                      "DAC_LR",              "I2S1_2_3 INPUT"},
	{"S1_IF_RX_ENA MIXER",                      "FM_L",                "I2S1_2_3 INPUT"},
	{"S1_IF_RX_ENA MIXER",                      "FM_R",                "I2S1_2_3 INPUT"},
	{"S1_IF_CLK_EN PGA",             NULL,                  "S1_IF_TX_ENA MIXER"},
	{"S1_IF_CLK_EN PGA",             NULL,                  "S1_IF_RX_ENA MIXER"},
	{"I2S1_2_3 OUTPUT",               NULL,                  "S1_IF_CLK_EN PGA"},
	{"S2_IF_TX_ENA MIXER",                      "DACL",                "I2S1_2_3 INPUT"},
	{"S2_IF_TX_ENA MIXER",                      "VOICE_DLINK",         "I2S1_2_3 INPUT"},
	{"S2_IF_RX_ENA MIXER",                      "VOICE_UL",            "I2S1_2_3 INPUT"},
	{"S2_IF_RX_ENA MIXER",                      "VOICE_UR",            "I2S1_2_3 INPUT"},
	{"S2_IF_CLK_EN PGA",             NULL,                  "S2_IF_TX_ENA MIXER"},
	{"S2_IF_CLK_EN PGA",             NULL,                  "S2_IF_RX_ENA MIXER"},
	{"I2S1_2_3 OUTPUT",               NULL,                  "S2_IF_CLK_EN PGA"},
	{"S3_IF_TX_ENA MIXER",                      "VOICE_DL",            "I2S1_2_3 INPUT"},
	{"S3_IF_TX_ENA MIXER",                      "VOICE_DR",            "I2S1_2_3 INPUT"},
	{"S3_IF_RX_ENA MIXER",                      "VOICE_UP",            "I2S1_2_3 INPUT"},
	{"S3_IF_CLK_EN PGA",             NULL,                  "S3_IF_TX_ENA MIXER"},
	{"S3_IF_CLK_EN PGA",             NULL,                  "S3_IF_RX_ENA MIXER"},
	{"I2S1_2_3 OUTPUT",               NULL,                  "S3_IF_CLK_EN PGA"},

	/* fm digital */
	{"S1_IL_PGA_EN PGA",            NULL,          "I2S1_2_3 INPUT"},
	{"S1_IR_PGA_EN PGA",            NULL,         "I2S1_2_3 INPUT"},
	{"DACL_MIXER_EN MIXER",      "DACL_MIXER_IN3_MUTE", "S1_IL_PGA_EN PGA"},
	{"DACR_MIXER_EN MIXER",     "DACR_MIXER_IN3_MUTE", "S1_IR_PGA_EN PGA"},

	{"I2S1_2_3 OUTPUT",          NULL,       "FM SWITCH"},
	{"FM SWITCH",   "SWITCH",   "I2S1_2_3 INPUT"},
	/* 3rd modem uplink */
	{"SMART_PA_FB_SEL MUX",    "S3_L",         "I2S1_2_3 INPUT"},
	{"THIRDMD_UP OUTPUT",                     NULL,       "THIRDMD_UPLINK_EN SWITCH"},

	/*3rd modem loop */
	{"THIRDMD_UPLINK_L_TEST_SEL MUX",        "MODEM_D_3RD", "THIRDMD_DLINK_EN SWITCH"},

	/* 3rd modem downlink */
	{"THIRDMD_DLINK_DIN_SEL MUX",   "APB_THIRDMD",             "THIRDMD_DOWN INPUT"},
	{"THIRDMD_DLINK_EN SWITCH",      "THIRDMD_DLINK_EN",    "THIRDMD_DLINK_DIN_SEL MUX"},
	{"S3_DOUT_RIGHT_SEL MUX",          "THIRDMD_DLINK_PGA",  "THIRDMD_DLINK_EN SWITCH"},
	{"S3_DOUT_RIGHT_SEL MUX",          "ADCR_PGA",                  "ADCR_PGA_EN PGA"},
	{"S3_DOUT_RIGHT_SEL MUX",          "OTHER",                        "I2S1_2_3 INPUT"},
	{"I2S1_2_3 OUTPUT",                        NULL,                            "S3_DOUT_RIGHT_SEL MUX"},
	{"S3_DOUT_LEFT_SEL MUX",             "THIRDMD_DLINK_PGA", "THIRDMD_DLINK_EN SWITCH"},
	{"S3_DOUT_LEFT_SEL MUX",             "ADCL_PGA",                  "ADCL_PGA_EN PGA"},
	{"I2S1_2_3 OUTPUT",                        NULL,                            "S3_DOUT_LEFT_SEL MUX"},

	/* DMIC */
	{"DMIC_EN SWITCH",                       "DMIC_EN",                    "DMIC INPUT"},
	{"RM_CODEC_DAC2ADC MUX",         "CIC_DMIC_PORT0",       "DMIC_EN SWITCH"},
	{"LM_CODEC_DAC2ADC MUX",          "CIC_DMIC_PORT0",      "DMIC_EN SWITCH"},

	/* sif interface */
	{"SIF_EN MIXER",                            "SIF_DACL_EN",         "SIF_DACL_EN PGA"},
	{"SIF_EN MIXER",                            "SIF_DACR_EN",         "SIF_DACR_EN PGA"},
	{"SIF_EN MIXER",                            "SIF_ADCL_EN",          "SIF_EN INPUT"},
	{"SIF_EN MIXER",                            "SIF_ADCR_EN",          "SIF_EN INPUT"},
	{"SIF_EN OUTPUT",                           NULL,                        "SIF_EN MIXER"},
	{"SMT_SIF_EN MIXER",                     "SIF_HSLR_EN",          "SIF_EN INPUT"},
	{"SMT_SIF_EN MIXER",                     "SIF_CLASSD_EN",     "SIF_EN INPUT"},
	{"SMT_SIF_EN MIXER",                     "SIF_RCV_EN",           "SIF_EN INPUT"},
	{"SMT_SIF_EN MIXER",                     "SIF_MIC1_EN",          "SIF_EN INPUT"},
	{"SMT_SIF_EN MIXER",                     "SIF_MIC2_EN",          "SIF_EN INPUT"},
	{"SMT_SIF_EN MIXER",                     "SIF_LINEINL_EN",      "SIF_EN INPUT"},
	{"SMT_SIF_EN MIXER",                     "SIF_LINEINR_EN",      "SIF_EN INPUT"},
	{"SIF_EN OUTPUT",                           NULL,                         "SMT_SIF_EN MIXER"},

	/* PLL & IBIAS */
	{"S1_IF_CLK_EN PGA",                        NULL,                  "SMT_IBIAS"},
	{"S2_IF_CLK_EN PGA",                        NULL,                  "SMT_IBIAS"},
	{"S3_IF_CLK_EN PGA",                        NULL,                  "SMT_IBIAS"},
	{"SMT_MIXOUT_HSLR_PD MIXER",        NULL,                  "SMT_IBIAS"},
	{"SMT_MIXOUT_EAR_PU MIXER",          NULL,                  "SMT_IBIAS"},
	{"SMT_ADCL_PD MIXER",                     NULL,                  "SMT_IBIAS"},
	{"SMT_ADCR_PD MIXER",                     NULL,                  "SMT_IBIAS"},
	{"SMT_MAINMIC INPUT",                      NULL,                  "SMT_MICB1"},
	{"SMT_AUXMIC INPUT",                        NULL,                  "SMT_MICB1"},
	{"SMT_HPMIC INPUT",                          NULL,                  "SMT_HSMICB"},
	{"SMT_ADCR_PD MIXER",                     NULL,                  "PLL"},
	{"SMT_ADCL_PD MIXER",                      NULL,                  "PLL"},
	{"SMT_SIF_DACR_EN DAC",                  NULL,                  "PLL"},
	{"SMT_SIF_DACL_EN DAC",                   NULL,                  "PLL"},
	{"S1_IF_CLK_EN PGA",                          NULL,                  "PLL"},
	{"S2_IF_CLK_EN PGA",                          NULL,                  "PLL"},
	{"S3_IF_CLK_EN PGA",                          NULL,                  "PLL"},
	{"DACL_MIXER_EN MIXER",                    NULL,                  "PLL"},
	{"DACR_MIXER_EN MIXER",                   NULL,                  "PLL"},
	{"ADCL_PGA_EN PGA",                          NULL,                  "PLL"},
	{"ADCR_PGA_EN PGA",                         NULL,                   "PLL"},
	{"SMT_LINEPGAL_PD PGA",                    NULL,                  "Backup_PLL"},
	{"SMT_LINEPGAR_PD PGA",                   NULL,                  "Backup_PLL"},

	/*smpa feedback*/
	{"SMART_PA_FB_SEL MUX",                  "S1_L_P",             "S1_IL_PGA_EN PGA"},
	{"THIRDMD_UPLINK_L_TEST_SEL MUX",        "U_3RD"      ,        "SMART_PA_FB_SEL MUX"},
	{"THIRDMD_UPLINK_EN SWITCH",             "THIRDMD_UPLINK_EN",  "THIRDMD_UPLINK_L_TEST_SEL MUX"},

	/* ANA LOOPBACK*/
	{"ANA_LOOPBACK SWITCH",        "ANA_LOOPBACK" ,       "SMT_ADCL_PD MIXER"},
	{"ANA_LOOPBACK SWITCH",        "ANA_LOOPBACK" ,       "SMT_ADCR_PD MIXER"},
	{"SMT_SIF_DACL_EN DAC",                   NULL ,                 "ANA_LOOPBACK SWITCH"},
	{"SMT_SIF_DACR_EN DAC",                  NULL ,                 "ANA_LOOPBACK SWITCH"},

	/* SMT switch */
	{"SMT DACL_SWITCH",        "SMT_DACL_EN",        "AUDIO_DLINK INPUT"},
	{"SMT_HP_LR OUTPUT",        NULL,                "SMT DACL_SWITCH"},
	{"SMT DACR_SWITCH",        "SMT_DACR_EN",        "AUDIO_DLINK INPUT"},
	{"SMT_HP_LR OUTPUT",        NULL,                "SMT DACL_SWITCH"},
};

/*****************************************************************************
 * CONTROL WIDGET AREA END
 *****************************************************************************/
/*
 *provide to Flash Driver
 *mute :
 */
void audio_codec_mute_pga(enum hi6555c_mute mute)
{
	if (!g_codec) {
		loge("g_codec is NULL\n");
		return;
	}

	if (MUTE_PGA == mute) {
		hi6555c_set_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_L_PGA_MUTE_BIT_START);
		hi6555c_set_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_R_PGA_MUTE_BIT_START);
		hi6555c_set_reg_bits(HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_VOICE_DLINK_PGA_MUTE_BIT_START);
		logi("mute\n");
	} else {
		hi6555c_clr_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_L_PGA_MUTE_BIT_START);
		hi6555c_clr_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_R_PGA_MUTE_BIT_START);
		hi6555c_clr_reg_bits(HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_VOICE_DLINK_PGA_MUTE_BIT_START);
		logi("unmute\n");
	}

	return;
}
EXPORT_SYMBOL_GPL(audio_codec_mute_pga);


/*****************************************************************************
 *
 * HEADSET AREA BEGIN
 *
 *****************************************************************************/
/*
 *Codec power
 */
static void hi6555c_power_codec(struct snd_soc_codec *codec, int on)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	if (on) {
		/* AVREF */
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW04_ADDR,
				((0x01 << HI6555C_SMT_VREFSEL_BIT_START) | (0x01 << HI6555C_SMT_VREFSEL_BIT_END))/*quick*/);
		msleep(5);
		/* IBIAS */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x01 << HI6555C_SMT_IBIAS_PD_BIT_START);

		/* AVREF */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW04_ADDR,  (0x01 << HI6555C_SMT_VREFSEL_BIT_END)/*normal*/);
	} else {
		/* IBIAS */
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x01 << HI6555C_SMT_IBIAS_PD_BIT_START);
	}
}

static inline void hi6555c_irqs_clr(unsigned int irqs)
{
	logd("IRQ=0x%x, irqs=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR), irqs);
	hi6555c_reg_write(g_codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR, irqs);
}

static inline void hi6555c_irqs_mask_set(unsigned int irqs)
{
	logd("IRQMb=0x%x, irqs=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR), irqs);
	hi6555c_set_reg_bits(HI6555C_SMT_ANA_IRQM_REG0_ADDR, irqs);
	logd("IRQMl=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR));
}

static inline void hi6555c_irqs_mask_clr(unsigned int irqs)
{
	logd("IRQMb=0x%x, irqs=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR), irqs);
	hi6555c_clr_reg_bits(HI6555C_SMT_ANA_IRQM_REG0_ADDR, irqs);
	logd("IRQMl=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR));
}

static void hi6555c_hs_micbias_pd(struct snd_soc_codec *codec, bool enable)
{
	unsigned int irq_mask = 0;

	/* to avoid irq while MBHD_COMP power up��mask the irq then clean it */
	irq_mask = hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR);
	hi6555c_irqs_mask_set(irq_mask | IRQ_MSK_COMP);

	if (enable) {
		/*open ibias*/
		hi6555c_ibias_hsmicbias_enable(codec, true);

		/* mbhc eco disable */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_MBHD_ECO_EN_BIT_START);

		/* hs micbias */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
		msleep(10);

		/* open normal compare */
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_COMP_PD_BIT_START);
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_BUFF_PD_BIT_START);
		usleep_range(100, 150);
	} else {
		/* close normal comp */
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_BUFF_PD_BIT_START);
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_COMP_PD_BIT_START);

		/* hs micbias */
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_HSMICB_DSCHG_BIT_START);
		msleep(5);
		hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_HSMICB_DSCHG_BIT_START);
		hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_MBHD_ECO_EN_BIT_START);
		msleep(20);

		/*close ibias*/
		hi6555c_ibias_hsmicbias_enable(codec, false);
		hi6555c_irqs_clr(IRQ_MSK_COMP);
		hi6555c_irqs_mask_clr(IRQ_MSK_BTN_ECO);
	}
}

static void hi6555c_hs_micbias_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	/* hs_micbias power up,then power down 3 seconds later */
	cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
	flush_workqueue(priv->hs_micbias_hkadc_dwq);

	if (enable) {
		if (((hi6555c_reg_read(codec, HI6555C_SMT_CODEC_ANA_RW02_ADDR))&(0x1 << HI6555C_SMT_HSMICB_PD_BIT_START))) /* read hs_micbias pd status */
			hi6555c_hs_micbias_pd(codec, true);
	} else {
		if ((0 == priv->hs_micbias_work) && !priv->hs_micbias_hkadc) {
			wake_lock_timeout(&priv->wake_lock, msecs_to_jiffies(3500));
			mod_delayed_work(priv->hs_micbias_hkadc_dwq,
					&priv->hs_micbias_hkadc_dw,
					msecs_to_jiffies(3000));
		}
	}
}

static void hi6555c_hs_micbias_work_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	mutex_lock(&priv->hs_micbias_mutex);
	if (enable) {
		if (0 == priv->hs_micbias_work)
			hi6555c_hs_micbias_enable(codec, true);

		++priv->hs_micbias_work;
	} else {
		--priv->hs_micbias_work;

		if (0 == priv->hs_micbias_work)
			hi6555c_hs_micbias_enable(codec, false);
	}
	mutex_unlock(&priv->hs_micbias_mutex);
}

static void hi6555c_hs_micbias_hkadc_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	mutex_lock(&priv->hs_micbias_mutex);
	if (enable) {
		if (!priv->hs_micbias_hkadc) {
			hi6555c_hs_micbias_enable(codec, true);
			priv->hs_micbias_hkadc = true;
		}
	} else {
		if (priv->hs_micbias_hkadc) {
			priv->hs_micbias_hkadc = false;
			hi6555c_hs_micbias_enable(codec, false);
		}
	}
	mutex_unlock(&priv->hs_micbias_mutex);
}

static void hi6555c_hs_micbias_hkadc_work_func(struct work_struct *work)
{
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_micbias_hkadc_dw.work);

	BUG_ON(!priv);
	BUG_ON(!priv->codec);

	hi6555c_hs_micbias_pd(priv->codec, false);
}

static void hi6555c_enable_ibias(struct snd_soc_codec *codec, bool enable)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	logd("Begin, en=%d\n", enable);
	BUG_ON(!priv);

	if (!priv->ibias_hkadc && 0 == priv->ibias_work) {
		if (enable) {
			logi("codec pu\n");
			hi6555c_power_codec(codec, HI6555C_ON);
		} else {
			logi("codec pd\n");
			hi6555c_power_codec(codec, HI6555C_OFF);
		}
	}
	logd("End\n");
}

static void hi6555c_ibias_work_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	mutex_lock(&priv->ibias_mutex);
	if (enable) {
		if (0 == priv->ibias_work)
			hi6555c_enable_ibias(codec, true);

		++priv->ibias_work;
	} else {
		--priv->ibias_work;

		if (0 == priv->ibias_work)
			hi6555c_enable_ibias(codec, false);
	}
	mutex_unlock(&priv->ibias_mutex);
}

static void hi6555c_ibias_hsmicbias_enable(struct snd_soc_codec *codec, bool enable)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	mutex_lock(&priv->ibias_mutex);
	if (enable) {
		if (!priv->ibias_hkadc) {
			hi6555c_enable_ibias(codec, true);
			priv->ibias_hkadc = true;
		}
	} else {
		if (priv->ibias_hkadc) {
			priv->ibias_hkadc = false;
			hi6555c_enable_ibias(codec, false);
		}
	}
	mutex_unlock(&priv->ibias_mutex);
}

/*
 *get irq stat
 *input: irq bit
 *output: 0 plugout,button up
 *           1 plugin,button down
 */
static inline int hi6555c_irq_stat(unsigned int irq_stat_bit)
{
	unsigned int irq_stat = 0;
	int ret = 0;

	irq_stat = hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR);
	irq_stat &= irq_stat_bit;

	switch (irq_stat_bit) {
	case IRQ_STAT_KEY_EVENT:
	case IRQ_STAT_ECO_KEY_EVENT:
		/* convert */
		ret = !irq_stat;
		break;
	case IRQ_STAT_PLUG_IN:
	default:
		/* no need to convert */
		ret = !!irq_stat;
		break;
	}
	logd("bit=0x%x, ret=%d\n", irq_stat_bit, ret);

	return ret;
}

static inline int hi6555c_hkadc_read(struct snd_soc_codec *codec)
{
	int hkadc_value = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	priv->adc_voltage = hisi_adc_get_value(HI6555C_HKADC_CHN);

	/* HKADC voltage, real value should devided 0.6 */
	hkadc_value = ((priv->adc_voltage)*(10))/(6);
	logi("adc_voltage = %d\n", priv->adc_voltage);

	return hkadc_value;
}

static irqreturn_t hi6555c_irq_handler(int irq, void *data)
{
	struct  snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = NULL;
	unsigned int irqs = 0;
	unsigned int irq_mask = 0, irq_masked = 0;

	logi(">>> Begin<<<\n");
	if (!data) {
		loge("data is null\n");
		return IRQ_NONE;
	}

	codec = data;
	priv = snd_soc_codec_get_drvdata(codec);
	BUG_ON(!priv);

	irqs = hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR);
	if (0 == irqs) {
		logi("irq pass\n");
		return IRQ_NONE;
	}

	irq_mask = hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR);
	irq_mask &= (~IRQ_PLUG_IN);
	irq_masked = irqs & (~irq_mask);

	wake_lock_timeout(&priv->wake_lock, msecs_to_jiffies(2000));
	/* distribute and handle irq individually, one deal one time */
	if (irq_masked & IRQ_PLUG_OUT) {
		queue_delayed_work(priv->hs_po_dwq,
				&priv->hs_po_dw,
				msecs_to_jiffies(0));
	} else if (irq_masked & IRQ_PLUG_IN) {
		queue_delayed_work(priv->hs_pi_dwq,
				&priv->hs_pi_dw,
				msecs_to_jiffies(HS_TIME_PI_DETECT));
	} else if (irq_masked & IRQ_COMP_L_BTN_DOWN) {
		queue_delayed_work(priv->hs_comp_l_btn_down_dwq,
				&priv->hs_comp_l_btn_down_dw,
				msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG));
	} else if (irq_masked & IRQ_COMP_L_BTN_UP) {
		queue_delayed_work(priv->hs_comp_l_btn_up_dwq,
				&priv->hs_comp_l_btn_up_dw,
				msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG_2));
	} else if (irq_masked & IRQ_ECO_BTN_DOWN) {
		queue_delayed_work(priv->hs_eco_btn_down_dwq,
				&priv->hs_eco_btn_down_dw,
				msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG));
	} else if (irq_masked & IRQ_ECO_BTN_UP) {
		queue_delayed_work(priv->hs_eco_btn_up_dwq,
				&priv->hs_eco_btn_up_dw,
				msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG_2));
	} else if (irq_masked & IRQ_COMP_H_BTN_DOWN) {
		queue_delayed_work(priv->hs_comp_h_btn_down_dwq,
				&priv->hs_comp_h_btn_down_dw,
				msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG));
	} else if (irq_masked & IRQ_COMP_H_BTN_UP) {
		queue_delayed_work(priv->hs_comp_h_btn_up_dwq,
				&priv->hs_comp_h_btn_up_dw,
				msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG_2));
	} else {
		logi("irq(0x%x) masked(0x%x) pass\n", irqs, irq_masked);
	}

	/* clear irq */
	hi6555c_irqs_clr(irqs);
	logi("<<< End, irq=0x%x(0x%x), IRQr=0x%x, IRQMr=0x%x, STATr=0x%x\n",
			irq_masked, irqs,
			hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
			hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
			hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));

	return IRQ_HANDLED;
}

void hs_jack_report(struct snd_soc_codec *codec)
{
	int jack_report = 0;
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	switch (priv->hs_status) {
	case HI6555C_JACK_BIT_NONE:
		jack_report = 0;
		logi("plug out\n");
		break;
	case HI6555C_JACK_BIT_HEADSET:
		jack_report = SND_JACK_HEADSET;
		logi("4-pole headset plug in\n");
		break;
	case HI6555C_JACK_BIT_HEADSET_NO_MIC:
		jack_report = SND_JACK_HEADPHONE;
		logi("invert headset plug in\n");
		break;
	case HI6555C_JACK_BIT_HEADPHONE:
		jack_report = SND_JACK_HEADPHONE;
		logi("3-pole headphone plug in\n");
		break;
	default:
		loge("error hs_status(%d)\n", priv->hs_status);
		return;
	}

	/* report jack status */
	snd_soc_jack_report(&priv->hs_jack.jack, jack_report, SND_JACK_HEADSET);
#ifdef CONFIG_SWITCH
	switch_set_state(&priv->hs_jack.sdev, priv->hs_status);
#endif
}

static void hs_plug_in_detect_func(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
	int hkadc_value = 0;

	BUG_ON(!priv);

	/* check state - plugin */
	if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
		logi("STAT: not plug in, IRQ=0x%x, IRQM=0x%x, STAT=0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
		hs_plug_out_detect_func(codec);
		return;
	}

	mutex_lock(&priv->plug_mutex);
	/* mask plug out */
	hi6555c_irqs_mask_set(IRQ_PLUG_OUT | IRQ_MSK_COMP);
	mutex_lock(&priv->hkadc_mutex);
	hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x1 << HI6555C_SMT_MBHD_VREF_PD_BIT_START);
	hi6555c_hs_micbias_hkadc_enable(codec, true);
	msleep(150);
	hkadc_value = hi6555c_hkadc_read(codec);

	/* value greater than 2565 can not trigger eco btn,
	 * so,the hs_micbias can't be closed until second detect finish.
	 */
	if (hkadc_value < 2565)
		hi6555c_hs_micbias_hkadc_enable(codec, false);
	mutex_unlock(&priv->hkadc_mutex);

	mutex_lock(&priv->io_mutex);
	if (hkadc_value <= priv->headset_voltage.hs_3_pole_max_voltage) {
		priv->hs_status = HI6555C_JACK_BIT_HEADPHONE;
		logi("headphone is 3 pole, saradc=%d\n", hkadc_value);
	} else if ((hkadc_value >= priv->headset_voltage.hs_4_pole_min_voltage)
			&& (hkadc_value <= priv->headset_voltage.hs_4_pole_max_voltage)) {
		priv->hs_status = HI6555C_JACK_BIT_HEADSET;
		logi("headphone is 4 pole, saradc=%d\n", hkadc_value);
#ifndef AUDIO_FACTORY_MODE
	} else if (hkadc_value >= HS_MAX_VOLTAGE) {
		priv->hs_status = HI6555C_JACK_BIT_LINEOUT;
		logi("headphone is lineout, saradc=%d\n", hkadc_value);
#endif
	} else {
		priv->hs_status = HI6555C_JACK_BIT_HEADSET_NO_MIC;
		logi("headphone is set reserve 4 pole temparily second check, saradc=%d\n", hkadc_value);
	}

	hi6555c_irqs_clr(IRQ_PLUG_OUT);
	hi6555c_irqs_mask_clr(IRQ_PLUG_OUT);
	mutex_unlock(&priv->io_mutex);

	if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
		logi("plug out happens\n");
		mutex_unlock(&priv->plug_mutex);
		hs_plug_out_detect_func(codec);
		return;
	}

	if ((HI6555C_JACK_BIT_LINEOUT != priv->hs_status) && (HI6555C_JACK_BIT_NONE != priv->hs_status) && (priv->hs_status != priv->old_hs_status)) {
		priv->old_hs_status = priv->hs_status;
		/*report headset info */
		hs_jack_report(codec);
	} else {
		loge("hs status=%d(old=%d) not changed\n", priv->hs_status, priv->old_hs_status);
	}

	/* to avoid irq while MBHD_COMP power up��mask the irq then clean it */
	hi6555c_irqs_clr(IRQ_MSK_COMP);
	hi6555c_irqs_mask_clr(IRQ_MSK_BTN_NOR);
	mutex_unlock(&priv->plug_mutex);

	return;
}

static void hs_plug_out_detect_func(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	mutex_lock(&priv->plug_mutex);
	/*
	 * Avoid hs_micbias_hkadc_dw waiting for entering eco,
	 * so cancel the delay work then power off hs_micbias.
	 */
	cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
	flush_workqueue(priv->hs_micbias_hkadc_dwq);
	priv->hs_micbias_hkadc = false;
	hi6555c_hs_micbias_pd(priv->codec, false);
	/* mbhc vref pd */
	hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x1 << HI6555C_SMT_MBHD_VREF_PD_BIT_START);
	/* mask all btn irq */
	hi6555c_irqs_mask_set(IRQ_MSK_COMP);
	mutex_lock(&priv->io_mutex);
	priv->hs_jack.report = 0;

	if (0 != priv->pressed_btn_type) {
		priv->hs_jack.jack.jack->type = priv->pressed_btn_type;
		/*report key event*/
		logi("report type=0x%x, status=0x%x\n", priv->hs_jack.report, priv->hs_status);
		snd_soc_jack_report(&priv->hs_jack.jack, priv->hs_jack.report, JACK_RPT_MSK_BTN);
	}

	priv->pressed_btn_type = 0;
	priv->hs_status = HI6555C_JACK_BIT_NONE;
	priv->old_hs_status = HI6555C_JACK_BIT_INVALID;
	mutex_unlock(&priv->io_mutex);

	/*report headset info */
	hs_jack_report(codec);
	headset_auto_calib_reset_interzone();
	hi6555c_irqs_clr(IRQ_MSK_COMP);
	hi6555c_irqs_mask_clr(IRQ_PLUG_IN);
	mutex_unlock(&priv->plug_mutex);

	return;
}

static int hs_btn_down_detect_func(struct snd_soc_codec *codec)
{
	int ret = 0;
	int pr_btn_type = 0;
	int hkadc_value = 0;

	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
	BUG_ON(!priv);

	if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
		logi("plug out happened\n");
		return 0;
	}

	if (HI6555C_JACK_BIT_HEADSET != priv->hs_status) {
		/* enter the second detect,it's triggered by btn irq  */
		loge("type 2-rec, saradc value=%d(btn_type=0x%x)\n", hkadc_value, priv->pressed_btn_type);
		hs_plug_in_detect_func(codec);
		return ret;
	}

	/* hs_micbias power up,then power down 3 seconds later */
	cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
	flush_workqueue(priv->hs_micbias_hkadc_dwq);

	mutex_lock(&priv->hkadc_mutex);
	hi6555c_hs_micbias_hkadc_enable(codec, true);
	hkadc_value = hi6555c_hkadc_read(codec);
	hi6555c_hs_micbias_hkadc_enable(codec, false);
	mutex_unlock(&priv->hkadc_mutex);
	msleep(30);
	/* to avoid irq while MBHD_COMP power up��mask the irq then clean it */
	hi6555c_irqs_clr(IRQ_MSK_COMP);
	hi6555c_irqs_mask_clr(IRQ_MSK_BTN_NOR);
	logi("mask clean\n");

	/*judge key type*/
	if ((hkadc_value >= priv->btn_voltage.key_play_min_value) && (hkadc_value <= priv->btn_voltage.key_play_max_value)) {
		pr_btn_type = SND_JACK_BTN_0;
		logi("key1 play down, saradc value is %d\n", hkadc_value);
	} else if ((hkadc_value >= priv->btn_voltage.key_forward_min_value) && (hkadc_value <= priv->btn_voltage.key_forward_max_value)) {
		pr_btn_type = SND_JACK_BTN_1;
		logi("key 2 forward down, saradc value is %d\n", hkadc_value);
	} else if ((hkadc_value >= priv->btn_voltage.key_back_min_value) && (hkadc_value <= priv->btn_voltage.key_back_max_value)) {
		pr_btn_type = SND_JACK_BTN_2;
		logi("key3 back key down , saradc value is %d\n", hkadc_value);
	} else {
		logi("hkadc value is not in range , hkadc value is %d\n", hkadc_value);
		return ret;
	}
	startup_FSM(REC_JUDGE, hkadc_value, &pr_btn_type);
	mutex_lock(&priv->io_mutex);
	priv->pressed_btn_type = pr_btn_type;
	priv->hs_jack.report = pr_btn_type;
	priv->hs_jack.jack.jack->type = pr_btn_type;
	mutex_unlock(&priv->io_mutex);

	if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
		logi("plug out happened\n");
	} else {
		/*report key event*/
		logi("report type=0x%x, status=0x%x\n", priv->hs_jack.report, priv->hs_status);
		snd_soc_jack_report(&priv->hs_jack.jack, priv->hs_jack.report, JACK_RPT_MSK_BTN);
	}

	return ret;
}

static int hs_btn_up_detect_func(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	BUG_ON(!priv);

	mutex_lock(&priv->io_mutex);
	if (0 == priv->pressed_btn_type) {
		mutex_unlock(&priv->io_mutex);

		/* second detect */
		if ((HI6555C_JACK_BIT_HEADSET_NO_MIC == priv->hs_status) || (HI6555C_JACK_BIT_HEADPHONE == priv->hs_status)
		|| (HI6555C_JACK_BIT_LINEOUT == priv->hs_status)) {
			logi("type 2-recognize\n");
			hs_plug_in_detect_func(codec);
		} else {
			logi("ignore the key up irq\n");
		}

		return 0;
	}

	priv->hs_jack.jack.jack->type = priv->pressed_btn_type;
	priv->hs_jack.report = 0;

	/*report key event*/
	logi("report type=0x%x, status=0x%x\n", priv->hs_jack.report, priv->hs_status);
	snd_soc_jack_report(&priv->hs_jack.jack, priv->hs_jack.report, JACK_RPT_MSK_BTN);
	priv->pressed_btn_type = 0;
	mutex_unlock(&priv->io_mutex);

	return 0;
}

static void hi6555c_hs_pi_work_func(struct work_struct *work)
{
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_pi_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	hs_plug_in_detect_func(codec);
	return;
}

static void hi6555c_hs_po_work_func(struct work_struct *work)
{
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_po_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	hs_plug_out_detect_func(codec);
	return;
}

static void hi6555c_hs_comp_l_btn_down_work_func(struct work_struct *work)
{
	int ret = 0;
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_l_btn_down_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	ret = hs_btn_down_detect_func(codec);
	if (ret < 0) {
		loge("compare l btn_down, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	}
}

static void hi6555c_hs_comp_l_btn_up_work_func(struct work_struct *work)
{
	int ret = 0;
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_l_btn_up_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	ret = hs_btn_up_detect_func(codec);

	if (ret < 0) {
		loge("compare l btn_up, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	}
}

static void hi6555c_hs_comp_h_btn_down_work_func(struct work_struct *work)
{
	int ret = 0;
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_h_btn_down_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	ret = hs_btn_down_detect_func(codec);

	if (ret < 0) {
		loge("compare h btn_down, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	}
}

static void hi6555c_hs_comp_h_btn_up_work_func(struct work_struct *work)
{
	int ret = 0;
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_h_btn_up_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	ret = hs_btn_up_detect_func(codec);

	if (ret < 0) {
		loge("compare h btn_up, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	}
}

static void hi6555c_hs_eco_btn_down_work_func(struct work_struct *work)
{
	int ret = 0;
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_eco_btn_down_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	ret = hs_btn_down_detect_func(codec);

	if (ret < 0) {
		loge("eco btn_down, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	}
}

static void hi6555c_hs_eco_btn_up_work_func(struct work_struct *work)
{
	int ret = 0;
	struct snd_soc_codec *codec = NULL;
	struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_eco_btn_up_dw.work);

	BUG_ON(!priv);

	codec = priv->codec;

	ret = hs_btn_up_detect_func(codec);

	if (ret < 0) {
		loge("eco btn_up, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
				hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	}
}

/*****************************************************************************
 *
 * HEADSET AREA END
 *
 *****************************************************************************/
/* INIT REGISTER VALUE FROM ARRAY */
static void hi6555c_init_reg_value(struct snd_soc_codec *codec)
{
	logi("hi6555c_init_reg_value Beg\n");

	/* Pop Reset */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW21_ADDR, 0x13);

	/* classD PGA CFG */
	hisi_pmic_reg_write(SOC_SMART_CLASSD_CTRL1_ADDR(0), 0x2A);

	/* classD normal mute mode, and set mute ---  0x13B [2:1] = 11 */
	hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL0_ADDR,
			((0x1 << HI6555C_PMU_CODEC_CLASSD_MUTE_SEL_BIT) | (0x1 << HI6555C_PMU_CODEC_CLASSD_MUTE_BIT)));

	/* eliminate btn dithering */
	hi6555c_reg_write(codec, HI6555C_SMT_DEB_CNT_HS_MIC_CFG_ADDR, 0x14);

	/* MBHC compare config 125mV 800mV 95% */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x9E);

	/* MICBIAS HSMICBIAS voltage 2.7V */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW22_ADDR, 0x36);

	/* clear HP MIXER,RCV MIXER channel select */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW13_ADDR, 0x00);
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW14_ADDR, 0x03);

	/* config HP PGA gain to -26dB */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW17_ADDR, 0x21);
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW18_ADDR, 0x21);

	/* Charge Pump freq 1.536MHz */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW25_ADDR, 0xAC);

	/* hp_bias always pu */
	hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW37_ADDR, (0x1 << HI6555C_SMT_HP_BIAS_PU_BIT_START));

	/* hp_l_r pop Resistor */
	hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW36_ADDR, (0x1 << HI6555C_SMT_ANALOG_LOOP_BIT_START));
	hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW40_ADDR, (0x1 << HI6555C_SMT_CODEC_ANA_REG40_BIT_START));

	/* NORMAL mode */
	hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW16_ADDR, 0x80);
}

static int hi6555c_startup(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	return 0;
}

static int hi6555c_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	/*TODO*/
	return 0;
}

static void hi6555c_shutdown(struct platform_device *dev)
{
	struct hi6555c_priv *priv = NULL;

	logi("Begin\n");

	if (!g_codec) {
		loge("g_codec is NULL\n");
		return;
	}

	priv = snd_soc_codec_get_drvdata(g_codec);

	if (!priv) {
		loge("priv is NULL\n");
		return;
	}

	if (HI6555C_JACK_BIT_NONE != priv->hs_status) {
		logi("hi6555c_codec_shutdown with headset\n");
		HiLOGE("audio", "Hi6555c", "hi6555c_codec_shutdown with headset\n");
		hi6555c_smt_hslr_pd_outdrv_power_mode_event((struct snd_soc_dapm_widget *)NULL,
				(struct snd_kcontrol *)NULL, SND_SOC_DAPM_POST_PMD);
	}

	hi6555c_pmu_classd_pd_outdrv_power_mode_event((struct snd_soc_dapm_widget *)NULL,
				(struct snd_kcontrol *)NULL, SND_SOC_DAPM_POST_PMD);

	/* codec pd */
	hi6555c_power_codec(g_codec, HI6555C_OFF);

	logi("End\n");
}

/* convenint for rollback */
#define CODEC_PM

static int hi6555c_suspend(struct device *dev)
{
	int ret = 0;

	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);
	BUG_ON(priv == NULL);

	/* i want to see this log anytime */
	logi("suspend\n");

#ifdef CODEC_PM
	if (!priv->have_dapm) {
		ret = regulator_disable(priv->asp_cfg_regu);
		priv->asp_use_count--;
		logi("codec power off count:%d\n", priv->asp_use_count);
		priv->asp_pd = true;
	}
#endif


	return 0;
}

static int hi6555c_resume(struct device *dev)
{
	int ret = 0;

	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);
	BUG_ON(priv == NULL);

	logi("resume\n");

#ifdef CODEC_PM
	if (priv->asp_pd) {
		ret = regulator_enable(priv->asp_cfg_regu);
		BUG_ON(ret != 0);
		priv->asp_use_count++;
		priv->asp_pd = false;
	}
#endif

	/* codec init cfg */
	hi6555c_reuse(g_codec);

	return 0;
}

struct snd_soc_dai_ops hi6555c_dai_ops = {
	.startup    = hi6555c_startup,
	.hw_params  = hi6555c_hw_params,
};

struct snd_soc_dai_driver hi6555c_dai[] = {
	{
		.name = "hi6555c-dai",
		.playback = {
			.stream_name = "Playback",
			.channels_min = HI6555C_PB_MIN_CHANNELS,
			.channels_max = HI6555C_PB_MAX_CHANNELS,
			.rates = HI6555C_RATES,
			.formats = HI6555C_FORMATS
		},
		.capture = {
			.stream_name = "Capture",
			.channels_min = HI6555C_CP_MIN_CHANNELS,
			.channels_max = HI6555C_CP_MAX_CHANNELS,
			.rates = HI6555C_RATES,
			.formats = HI6555C_FORMATS
		},
		.ops = &hi6555c_dai_ops,
	},
};

static void set_headset_keys_config(struct hi6555c_priv *priv)
{
	/* config the headset */
	priv->headset_voltage.hs_3_pole_max_voltage = 8;
	priv->headset_voltage.hs_4_pole_min_voltage = 900;
	priv->headset_voltage.hs_4_pole_max_voltage = 2565;
	logi("headset_voltage {3pole=%d, 4pole=(%d-%d)}\n",
			priv->headset_voltage.hs_3_pole_max_voltage,
			priv->headset_voltage.hs_4_pole_min_voltage,
			priv->headset_voltage.hs_4_pole_max_voltage);

	/* config the keys */
	priv->btn_voltage.key_up_min_value = 1350;
	priv->btn_voltage.key_up_max_value = 2565;
	priv->btn_voltage.key_play_min_value = 0;
	priv->btn_voltage.key_play_max_value = 100;
	priv->btn_voltage.key_back_min_value = 350;
	priv->btn_voltage.key_back_max_value = 700;
	priv->btn_voltage.key_forward_min_value = 130;
	priv->btn_voltage.key_forward_max_value = 320;

	logi("btn_voltage {keyup=(%d-%d), keyplay=(%d-%d), keyback=(%d-%d), keyfw=(%d-%d)}\n",
			priv->btn_voltage.key_up_min_value,
			priv->btn_voltage.key_up_max_value,
			priv->btn_voltage.key_play_min_value,
			priv->btn_voltage.key_play_max_value,
			priv->btn_voltage.key_back_min_value,
			priv->btn_voltage.key_back_max_value,
			priv->btn_voltage.key_forward_min_value,
			priv->btn_voltage.key_forward_max_value);

	return;
}

static void hi6555c_tool_init(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = NULL;
	logi("Begin\n");

	priv = snd_soc_codec_get_drvdata(codec);
	BUG_ON(!priv);

	INIT_WORK(&priv->tool_work, hi6555c_misc_reg_write);
	priv->tool_data.normal_always = HI6555C_DISABLE;
	priv->tool_data.codec_soc_clk_cnt = 0;
	priv->tool_data.scharge_boost_cnt = 0;
	logi("End\n");

	return;
}

/*
 *SoC init
 */
static int hi6555c_soc_init(struct snd_soc_codec *codec)
{
	int ret = 0;
	struct hi6555c_priv *priv = NULL;
	struct device_node *np  = codec->dev->of_node;
	struct device *dev  = codec->dev;

	priv = snd_soc_codec_get_drvdata(codec);
	BUG_ON(!priv);

	priv->asp_use_count = 0;

	/* asp power on */
	priv->asp_cfg_regu = devm_regulator_get(codec->dev, "asp");
	if (IS_ERR(priv->asp_cfg_regu)) {
		loge("get asp regulators err:%pK\n", priv->asp_cfg_regu);
		ret = PTR_ERR(priv->asp_cfg_regu);
		goto end;
	}

	ret = regulator_enable(priv->asp_cfg_regu);
	priv->asp_use_count++;
	if (0 != ret) {
		loge("couldn't enable asp_cfg_regu regulators %d\n", ret);
		goto end;
	}

	/* modem abb is codec work clk so peri zone must power on */
	priv->codec_peri = devm_regulator_get(codec->dev, "modem-abb");
	if (IS_ERR(priv->codec_peri)) {
		loge("couldn't get modem abb regulators ret:%ld\n", PTR_ERR(priv->codec_peri));
		return -EFAULT;
	}

	pm_runtime_set_autosuspend_delay(dev, 500);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_enable(dev);

	/* codec_modem0 clk always on */
	priv->codec_modem0 = devm_clk_get(dev, "clk_modem2codec0");
	if (IS_ERR(priv->codec_modem0)) {
		loge("Get Codec clk clk_modem2codec0 failed:%pK\n", priv->codec_modem0);
		ret = PTR_ERR(priv->codec_modem0);
		goto regulator_enabled;
	}

	ret = clk_prepare_enable(priv->codec_modem0);
	if (0 != ret) {
		loge("codec_modem0 clken fail, ret=%d\n", ret);
		goto regulator_enabled;
	}


	/* codec work clk */
	priv->codec_soc = devm_clk_get(dev, "clk_aspcodec");
	if (IS_ERR(priv->codec_soc)) {
		loge("Get Codec clk clk_bbppll_sel_src failed:%pK\n", priv->codec_soc);
		ret = PTR_ERR(priv->codec_soc);
		goto modem0_clk_enabled;
	}

	/* classD regulator */
	priv->regulator_schg_boost3 = devm_regulator_get(dev, "schg_boost3");
	if (IS_ERR(priv->regulator_schg_boost3)) {
		loge("regulator_schg_boost3 get failed:%pK\n", priv->regulator_schg_boost3);
		ret = PTR_ERR(priv->regulator_schg_boost3);
		goto modem0_clk_enabled;
	}

	/*set the classD power supply state*/
	priv->use_battery_supply = of_property_read_bool(np, "use-battery-power-supply-for-ClassD");

	/* codec init cfg */
	hi6555c_reuse(codec);

	goto end;

modem0_clk_enabled:
	clk_disable_unprepare(priv->codec_modem0);

regulator_enabled:
	regulator_disable(priv->asp_cfg_regu);

end:
	return ret;
}

static void hi6555c_soc_uninit(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = NULL;

	priv = snd_soc_codec_get_drvdata(codec);
	if (!priv) {
		loge("priv is NULL\n");
		return;
	}

	clk_disable_unprepare(priv->codec_modem0);

	regulator_disable(priv->asp_cfg_regu);

	return;
}
/*
   SmartStarCodec init
 */
static int hi6555c_headset_init(struct snd_soc_codec *codec)
{
	int ret = 0;
	struct hi6555c_priv *priv = NULL;
	struct device_node *np  = codec->dev->of_node;

	/* smartstar codec reset */
	hisi_pmic_reg_write(SOC_SMART_PMU_SOFT_RST_ADDR(0), 0x22 << SOC_SMART_PMU_SOFT_RST_soft_rst_n_START);
	msleep(10);
	hisi_pmic_reg_write(SOC_SMART_PMU_SOFT_RST_ADDR(0), 0x2F << SOC_SMART_PMU_SOFT_RST_soft_rst_n_START);

	priv = snd_soc_codec_get_drvdata(codec);
	BUG_ON(!priv);

	hi6555c_tool_init(codec);

	hi6555c_init_reg_value(codec);

	/* init */
	set_headset_keys_config(priv);
	priv->hs_status = HI6555C_JACK_BIT_NONE;
	priv->old_hs_status = HI6555C_JACK_BIT_INVALID;
	priv->hs_jack.report = 0;
	priv->pressed_btn_type = 0;

	/*VREF PD ��MICBIAS PD  */
	hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
	hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x1 << HI6555C_SMT_MBHD_VREF_PD_BIT_START);

	hi6555c_irqs_mask_set(IRQ_MSK_HS_ALL);

	/* avoid irq triggered while codec power up */
	hi6555c_irqs_clr(IRQ_MSK_HS_ALL);

	/* Headset jack */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0)
	ret = snd_soc_card_jack_new(codec->component.card, "Headset Jack", SND_JACK_HEADSET, (&priv->hs_jack.jack), NULL, 0);
#else
	ret = snd_soc_jack_new(codec, "Headset Jack", SND_JACK_HEADSET, (&priv->hs_jack.jack));
#endif
	if (ret) {
		loge("jack new, ret = %d\n", ret);
		return ret;
	}

	/* set a key mapping on a jack */
	ret = snd_jack_set_key(priv->hs_jack.jack.jack, SND_JACK_BTN_0, KEY_MEDIA);
	if (ret) {
		loge("jack set key(0x%x), ret = %d\n", SND_JACK_BTN_0, ret);
		return ret;
	}

	ret = snd_jack_set_key(priv->hs_jack.jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	if (ret) {
		loge("jack set key(0x%x), ret = %d\n", SND_JACK_BTN_1, ret);
		return ret;
	}

	ret = snd_jack_set_key(priv->hs_jack.jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	if (ret) {
		loge("jack set key(0x%x), ret = %d\n", SND_JACK_BTN_2, ret);
		return ret;
	}

#ifdef CONFIG_SWITCH
	priv->hs_jack.sdev.name = "h2w";
	ret = switch_dev_register(&(priv->hs_jack.sdev));
	if (ret) {
		loge("Registering switch device error, ret=%d\n", ret);
		return ret;
	}
	priv->hs_jack.is_dev_registered = true;
#endif

	/* IRQ config */
	priv->hs_pi_dwq = create_singlethread_workqueue("hs_pi_dwq");
	if (NULL == priv->hs_pi_dwq) {
		loge("hs_pi_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_pi_dw, hi6555c_hs_pi_work_func);

	priv->hs_po_dwq = create_singlethread_workqueue("hs_po_dwq");
	if (NULL == priv->hs_po_dwq) {
		loge("hs_po_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_po_dw, hi6555c_hs_po_work_func);

	priv->hs_comp_l_btn_down_dwq = create_singlethread_workqueue("hs_comp_l_btn_down_dwq");
	if (NULL == priv->hs_comp_l_btn_down_dwq) {
		loge("hs_btn_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_comp_l_btn_down_dw, hi6555c_hs_comp_l_btn_down_work_func);

	priv->hs_comp_l_btn_up_dwq = create_singlethread_workqueue("hs_comp_l_btn_up_dwq");
	if (NULL == priv->hs_comp_l_btn_up_dwq) {
		loge("hs_btn_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_comp_l_btn_up_dw, hi6555c_hs_comp_l_btn_up_work_func);

	priv->hs_comp_h_btn_down_dwq = create_singlethread_workqueue("hs_comp_h_btn_down_dwq");
	if (NULL == priv->hs_comp_h_btn_down_dwq) {
		loge("hs_btn_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_comp_h_btn_down_dw, hi6555c_hs_comp_h_btn_down_work_func);

	priv->hs_comp_h_btn_up_dwq = create_singlethread_workqueue("hs_comp_h_btn_up_dwq");
	if (NULL == priv->hs_comp_h_btn_up_dwq) {
		loge("hs_btn_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_comp_h_btn_up_dw, hi6555c_hs_comp_h_btn_up_work_func);

	priv->hs_eco_btn_down_dwq = create_singlethread_workqueue("hs_eco_btn_down_dwq");
	if (NULL == priv->hs_eco_btn_down_dwq) {
		loge("hs_btn_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_eco_btn_down_dw, hi6555c_hs_eco_btn_down_work_func);

	priv->hs_eco_btn_up_dwq = create_singlethread_workqueue("hs_eco_btn_up_dwq");
	if (NULL == priv->hs_eco_btn_up_dwq) {
		loge("hs_btn_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_eco_btn_up_dw, hi6555c_hs_eco_btn_up_work_func);

	priv->hs_micbias_hkadc_dwq = create_singlethread_workqueue("hs_micbias_hkadc_dwq");
	if (NULL == priv->hs_micbias_hkadc_dwq) {
		loge("hs_micbias_hkadc_dwq workqueue create failed\n");
		return -EFAULT;
	}
	INIT_DELAYED_WORK(&priv->hs_micbias_hkadc_dw, hi6555c_hs_micbias_hkadc_work_func);

	/* config intr for codec */
	priv->gpio_intr_pin = of_get_named_gpio(np, "gpios", 0);
	if (priv->gpio_intr_pin < 0) {
		loge("get gpio flags error(0x%x)\n", priv->gpio_intr_pin);
		return -EFAULT;
	}

	priv->gpio_irq = gpio_to_irq(priv->gpio_intr_pin);
	logi("gpio_to_irq, gp_irq = %d(%d)\n", priv->gpio_irq, priv->gpio_intr_pin);

	/* irq shared with pmu */
	ret = request_irq(priv->gpio_irq, hi6555c_irq_handler, IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND, "codec_irq", codec);
	if (ret) {
		loge("request_irq failed, ret = %d\n", ret);
		gpio_free(priv->gpio_intr_pin);
		free_irq(priv->gpio_irq, priv);
		return -EFAULT;
	}

	/* judge headset present or not */
	logi("irq soure stat %#04x", hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
	if (hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
		hs_plug_in_detect_func(codec);
	} else {
		hi6555c_irqs_mask_clr(IRQ_PLUG_IN);
	}
	headset_auto_calib_init(np);
	return ret;
}

static void hi6555c_headset_uninit(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = NULL;
	priv = snd_soc_codec_get_drvdata(codec);
	if (!priv) {
		loge("priv is NULL\n");
		return;
	}

#ifdef CONFIG_SWITCH
	if (priv->hs_jack.is_dev_registered) {
		switch_dev_unregister(&(priv->hs_jack.sdev));
		priv->hs_jack.is_dev_registered = false;
	}
#endif

	if (NULL != priv->hs_pi_dwq) {
		cancel_delayed_work(&priv->hs_pi_dw);
		flush_workqueue(priv->hs_pi_dwq);
		destroy_workqueue(priv->hs_pi_dwq);
		priv->hs_pi_dwq = NULL;
	}

	if (NULL != priv->hs_po_dwq) {
		cancel_delayed_work(&priv->hs_po_dw);
		flush_workqueue(priv->hs_po_dwq);
		destroy_workqueue(priv->hs_po_dwq);
		priv->hs_po_dwq = NULL;
	}

	if (NULL != priv->hs_comp_l_btn_down_dwq) {
		cancel_delayed_work(&priv->hs_comp_l_btn_down_dw);
		flush_workqueue(priv->hs_comp_l_btn_down_dwq);
		destroy_workqueue(priv->hs_comp_l_btn_down_dwq);
		priv->hs_comp_l_btn_down_dwq = NULL;
	}

	if (NULL != priv->hs_comp_l_btn_up_dwq) {
		cancel_delayed_work(&priv->hs_comp_l_btn_up_dw);
		flush_workqueue(priv->hs_comp_l_btn_up_dwq);
		destroy_workqueue(priv->hs_comp_l_btn_up_dwq);
		priv->hs_comp_l_btn_up_dwq = NULL;
	}

	if (NULL != priv->hs_comp_h_btn_down_dwq) {
		cancel_delayed_work(&priv->hs_comp_h_btn_down_dw);
		flush_workqueue(priv->hs_comp_h_btn_down_dwq);
		destroy_workqueue(priv->hs_comp_h_btn_down_dwq);
		priv->hs_comp_h_btn_down_dwq = NULL;
	}

	if (NULL != priv->hs_comp_h_btn_up_dwq) {
		cancel_delayed_work(&priv->hs_comp_h_btn_up_dw);
		flush_workqueue(priv->hs_comp_h_btn_up_dwq);
		destroy_workqueue(priv->hs_comp_h_btn_up_dwq);
		priv->hs_comp_h_btn_up_dwq = NULL;
	}

	if (NULL != priv->hs_eco_btn_down_dwq) {
		cancel_delayed_work(&priv->hs_eco_btn_down_dw);
		flush_workqueue(priv->hs_eco_btn_down_dwq);
		destroy_workqueue(priv->hs_eco_btn_down_dwq);
		priv->hs_eco_btn_down_dwq = NULL;
	}

	if (NULL != priv->hs_eco_btn_up_dwq) {
		cancel_delayed_work(&priv->hs_eco_btn_up_dw);
		flush_workqueue(priv->hs_eco_btn_up_dwq);
		destroy_workqueue(priv->hs_eco_btn_up_dwq);
		priv->hs_eco_btn_up_dwq = NULL;
	}

	if (NULL != priv->hs_micbias_hkadc_dwq) {
		cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
		flush_workqueue(priv->hs_micbias_hkadc_dwq);
		destroy_workqueue(priv->hs_micbias_hkadc_dwq);
		priv->hs_micbias_hkadc_dwq = NULL;
	}

	if (priv->gpio_irq) {
		free_irq(priv->gpio_irq, priv);
		priv->gpio_irq = 0;
	}

	if (priv->gpio_intr_pin >= 0) {
		gpio_free(priv->gpio_intr_pin);
		priv->gpio_intr_pin = 0;
	}

	return;
}

static int hi6555c_set_priv(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = NULL;
	struct device *dev = codec->dev;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		loge("priv devm_kzalloc failed\n");
		return -ENOMEM;
	}

	snd_soc_codec_set_drvdata(codec, priv);

	g_codec = codec;
	priv->codec = codec;

	/* virtual codec register init */
	priv->v_codec_reg[0] = 0;
	priv->v_codec_reg[1] = 0;

	spin_lock_init(&priv->lock);
	mutex_init(&priv->io_mutex);
	mutex_init(&priv->ibias_mutex);
	mutex_init(&priv->hs_micbias_mutex);
	mutex_init(&priv->hkadc_mutex);
	mutex_init(&priv->plug_mutex);
	wake_lock_init(&priv->wake_lock, WAKE_LOCK_SUSPEND, "hi6555c");

	if (0 > hi6555c_debug_init(codec)) {
		hi6555c_debug_uninit(codec);
	}

	return 0;
}

static void hi6555c_unset_priv(struct snd_soc_codec *codec)
{
	struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

	hi6555c_debug_uninit(codec);

	if (priv) {
		wake_lock_destroy(&priv->wake_lock);
		snd_soc_codec_set_drvdata(codec, NULL);
	}

	g_codec = NULL;

	return;
}

static void hi6555c_free_resource(struct snd_soc_codec *codec)
{
	hi6555c_headset_uninit(codec);
	hi6555c_soc_uninit(codec);
	hi6555c_unset_priv(codec);
	return;
}

static int hi6555c_codec_probe(struct snd_soc_codec *codec)
{
	int ret = 0;
	struct snd_soc_dapm_context *dapm = &codec->dapm;
	struct device_node *np  = codec->dev->of_node;
	int val = 0;

	logi("Begin\n");

	ret = hi6555c_set_priv(codec);
	if (0 != ret) {
		loge("hi6555c_set_priv err, ret=%d\n", ret);
		goto end;
	}

	ret = hi6555c_soc_init(codec);
	if (0 != ret) {
		loge("hi6555c_soc_init err, ret=%d\n", ret);
		goto priv_err;
	}

	ret = hi6555c_headset_init(codec);
	if (0 != ret) {
		loge("hi6555c_headset_init err, ret=%d\n", ret);
		goto headset_err;
	}

	ret = snd_soc_dapm_sync(dapm);
	if (0 != ret) {
		loge("dapm sync error, errornum = %d\n", ret);
		goto headset_err;
	}

	if (!of_property_read_u32(np, "hisilicon,hac_gpio", &val)) {
		hac_en_gpio = val;
		logi("hac gpio num is %d.\n",hac_en_gpio);
	} else {
		hac_en_gpio = 0;
		logi("hac is not support.\n");
		goto end;
	}

	if (gpio_request(hac_en_gpio, "hac_en_gpio")) {
		loge("hac_en_gpio request failed!\n");
		goto end;
	}

	if (gpio_direction_output(hac_en_gpio, 0)) {
		loge("hac_en_gpio set output failed!\n");
	}

	goto end;

headset_err:
	hi6555c_headset_uninit(codec);

	hi6555c_soc_uninit(codec);

priv_err:
	hi6555c_unset_priv(codec);

end:
	logi("End\n");

	return ret;
}

static int hi6555c_codec_remove(struct snd_soc_codec *codec)
{
	/*TODO*/
	hi6555c_free_resource(codec);

	if (hac_en_gpio) {
		gpio_free(hac_en_gpio);
	}

	return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_hi6555c = {
	.probe    = hi6555c_codec_probe,
	.remove  = hi6555c_codec_remove,
	.read      = hi6555c_reg_read,
	.write     = hi6555c_reg_write,
	.controls = hi6555c_snd_controls,
	.num_controls = ARRAY_SIZE(hi6555c_snd_controls),
	.dapm_widgets = hi6555c_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(hi6555c_dapm_widgets),
	.dapm_routes = hi6555c_route_map,
	.num_dapm_routes = ARRAY_SIZE(hi6555c_route_map),
};

static int hi6555c_base_addr_map(struct platform_device *pdev)
{
	struct resource *res = NULL;
	unsigned int i;

	for (i = 0; i < HI6555C_REG_CNT; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (!res) {
			loge("platform_get_resource %d err\n", i);
			return -ENOENT;
		}

		reg_base_addr[i] = (char * __force)(ioremap(res->start, resource_size(res)));
		if (!reg_base_addr[i]) {
			loge("cannot map register memory\n");
			return -ENOMEM;
		}
	}

	return 0;
}

static void hi6555c_base_addr_unmap(void)
{
	unsigned int i;

	for (i = 0; i < HI6555C_REG_CNT; i++) {
		if (reg_base_addr[i]) {
			iounmap(reg_base_addr[i]);
			reg_base_addr[i] = NULL;
		}
	}
}

static int hi6555c_probe(struct platform_device *pdev)
{
	int ret = 0;

	logi("Begin\n");
	ret = hi6555c_base_addr_map(pdev);
	if (0 != ret) {
		hi6555c_base_addr_unmap();
		return ret;
	}
	logi("End\n");

	return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_hi6555c, hi6555c_dai, ARRAY_SIZE(hi6555c_dai));
}

static int hi6555c_remove(struct platform_device *pdev)
{
	logd("Begin\n");
	snd_soc_unregister_codec(&pdev->dev);
	hi6555c_base_addr_unmap();

	return 0;
}

static const struct of_device_id hi6555c_codec_match[] = {
	{ .compatible = "hi6555c-codec", },
	{},
};


int hi6555c_runtime_suspend(struct device *dev)
{
	int ret = 0;
	struct hi6555c_priv *priv = dev_get_drvdata(dev);
	BUG_ON(priv == NULL);

	/* pm runtime we want to use in future */
	loge("begin\n");
	//ret = regulator_disable(priv->asp_cfg_regu);
	if (ret) {
		loge("couldn't disable asp_regu regulators %d\n", ret);
		return -EFAULT;
	}

	return ret;
}

int hi6555c_runtime_resume(struct device *dev)
{
	int ret = 0;
	struct hi6555c_priv *priv = dev_get_drvdata(dev);
	BUG_ON(priv == NULL);

	logi("begin\n");
	//ret = regulator_enable(priv->asp_cfg_regu);
	if (ret) {
		loge("couldn't enable asp_regu regulators %d\n", ret);
		return -EFAULT;
	}

	return ret;
}


const struct dev_pm_ops hi6555_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(hi6555c_suspend, hi6555c_resume)
	SET_RUNTIME_PM_OPS(hi6555c_runtime_suspend, hi6555c_runtime_resume, NULL)
};

static struct platform_driver hi6555c_driver = {
	.driver = {
		.name  = "hi6555c-codec",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hi6555c_codec_match),
		.pm = &hi6555_pm_ops,
	},
	.probe  = hi6555c_probe,
	.remove = hi6555c_remove,
	.shutdown = hi6555c_shutdown,
};

static int __init hi6555c_codec_init(void)
{
	logi("Begin\n");
	return platform_driver_register(&hi6555c_driver);
}
module_init(hi6555c_codec_init);

static void __exit hi6555c_codec_exit(void)
{
	logi("Begin\n");
	platform_driver_unregister(&hi6555c_driver);
}
module_exit(hi6555c_codec_exit);

MODULE_DESCRIPTION("ASoC hi6555c driver");
MODULE_LICENSE("GPL");
