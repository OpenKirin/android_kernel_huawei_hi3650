/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/clk-provider.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
#include <linux/clk-private.h>
#endif
#include <linux/clkdev.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <soc_crgperiph_interface.h>
#include "hisi-clk-mailbox.h"
#include "clk-kirin.h"
#ifdef CONFIG_HISI_PERIDVFS
#include "peri_dvfs/peri_volt_poll.h"
#endif

#define MAX_FREQ_NUM    	2
/*lint -e750 -esym(750,*) */
#define MAX_TRY_NUM    		20
#define VDEC_RECALC_ADDR(base)		SOC_CRGPERIPH_CLKDIV9_ADDR(base)
/*lint -e750 +esym(750,*) */
#define VDEC_MUX_MASK		0x60
#define VDEC_DIV_MASK		0x1F

struct peri_dvfs_clk {
	struct clk_hw			hw;
	void __iomem			*reg;	/* ctrl register */
	u32				id;
	unsigned long			freq_table[MAX_FREQ_NUM];
	u32				volt[MAX_FREQ_NUM];
	const char 			*link;
	unsigned long			rate;
	unsigned long			sensitive_freq;
	void __iomem			*crgctrl;
};

#ifdef CONFIG_HISI_PERIDVFS
struct peri_dvfs_switch_up {
	struct work_struct		updata;
	struct clk			*clk;
	struct clk			*linkage;
	struct peri_volt_poll		*pvp;
	unsigned int			target_volt;
	unsigned long			target_freq;
};
struct peri_dvfs_switch_up sw_up;
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
extern int __clk_prepare(struct clk *clk);
extern void __clk_unprepare(struct clk *clk);
#else
extern int clk_core_prepare(struct clk_core *clk_core);
extern void clk_core_unprepare(struct clk_core *clk_core);
#endif
extern int clk_set_rate_nolock(struct clk *clk, unsigned long rate);
extern int clk_get_rate_nolock(struct clk *clk);
extern int __clk_enable(struct clk *clk);
extern void __clk_disable(struct clk *clk);
extern int IS_FPGA(void);

#ifdef CONFIG_HISI_PERIDVFS
/* func: async dvfs func
*/
static void updata_freq_volt_up_fn(struct work_struct *work)
{
	struct peri_dvfs_switch_up *sw = &sw_up;
	int ret = 0;
	u32 volt = 0;
	u32 loop = MAX_TRY_NUM;

	/*set volt is async*/
	ret = peri_set_volt(sw->pvp, sw->target_volt);
	if (ret < 0)
		pr_err("[%s]set volt failed ret=%d tar=%d!\n", __func__, ret, sw->target_volt);
	do {
		volt = peri_get_volt(sw->pvp);
		if (volt != sw->target_volt) {
			loop--;
			usleep_range(1000, 3000);
		}
	} while (volt != sw->target_volt && loop > 0);

	if (volt != sw->target_volt) {
		pr_err("[%s]schedule up volt failed, ret = %d!\n", __func__, volt);
#if 0
		if (!IS_FPGA())
			BUG_ON(1);
#endif
	} else {
		ret = clk_set_rate_nolock(sw->linkage, sw->target_freq);
		if (ret < 0)
			pr_err("[%s]set linkage failed, ret = %d!\n", __func__, ret);
	}
}
#endif

static long peri_dvfs_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	return rate;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
static long peri_dvfs_clk_determine_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long *best_parent_rate,
					struct clk **best_parent_clk)
{
	return rate;
}
#else
static long peri_dvfs_clk_determine_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long min_rate, unsigned long max_rate,
					unsigned long *best_parent_rate, struct clk_hw **best_parent_hw)
{
	return rate;
}
#endif

/* func: get cur freq
*/
static unsigned long peri_dvfs_clk_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct peri_dvfs_clk *dfclk = container_of(hw, struct peri_dvfs_clk, hw);
	struct clk *ppll;
	struct clk *clk_friend;
	char *source[4] = {"clk_ppll0", "clk_ppll1", "clk_ppll2", "clk_ppll3"};
	u32 rate = 0;
	u32 ppll_rate;
	u32 value = 0;
	u32 vdec_mux_value = 0;
	u32 vdec_div_value = 0;
	int ret;

	value = readl(VDEC_RECALC_ADDR(dfclk->crgctrl));
	vdec_div_value = (value & VDEC_DIV_MASK) + 1;
	vdec_mux_value = (value & VDEC_MUX_MASK) >> 5;

	if (1 == vdec_mux_value) {
		pr_err("%s: vdec chose the wrong ppll: ppll1\n", __func__);
			return -ENODEV;
	}

	ppll = __clk_lookup(source[vdec_mux_value]);
	if (IS_ERR_OR_NULL(ppll)) {
		pr_err("[%s] %s get failed!\n", __func__, source[vdec_mux_value]);
		return -ENODEV;
	}
	ppll_rate = __clk_get_rate(ppll);
	rate = ppll_rate/vdec_div_value;
	dfclk->rate = rate;

	clk_friend = __clk_lookup(dfclk->link);
	if (IS_ERR_OR_NULL(clk_friend)) {
		pr_err("[%s] %s get failed!\n", __func__, dfclk->link);
		return -ENODEV;
	}
	ret = clk_set_rate_nolock(clk_friend, rate);
	if (ret < 0)
		pr_err("[%s]set friend failed, ret = %d!\n", __func__, ret);

	return rate;
}

/*func: check input freq
*/
static bool dev_freq_check(struct peri_dvfs_clk *dfclk, unsigned long rate)
{
	if (rate >= dfclk->freq_table[0]*1000 && rate <= dfclk->freq_table[1]*1000)
			return true;
	return false;
}

/*func: dvfs set rate main func
*/
static int peri_dvfs_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct peri_dvfs_clk *dfclk = container_of(hw, struct peri_dvfs_clk, hw);
#ifdef CONFIG_HISI_PERIDVFS
	struct peri_volt_poll *pvp;
#endif
	struct clk *friend_clk;
	int ret = 0;

	if (false == dev_freq_check(dfclk, rate)) {
		pr_err("[%s] freq_table not contain rate, ret =%d!\n",
						 __func__, ret);
		return -EINVAL;
	}

	friend_clk = __clk_lookup(dfclk->link);
	if (IS_ERR_OR_NULL(friend_clk)) {
		pr_err("[%s] %s get failed!\n", __func__, dfclk->link);
		return -ENODEV;
	}
#ifndef CONFIG_HISI_PERIDVFS
	ret = clk_set_rate_nolock(friend_clk, rate);
	if (ret < 0) {
		pr_err("[%s] fail to set rate, ret = %d, %d!\n",
						__func__, ret, __LINE__);
	}
#else
	if (__clk_is_enabled(friend_clk) == false) {
		ret = clk_set_rate_nolock(friend_clk, rate);
		if (ret < 0)
			pr_err("[%s] fail to set rate, ret = %d, %d!\n",
						__func__, ret, __LINE__);
		goto now;
	}
	pvp = peri_volt_poll_get(dfclk->id, NULL);
	if (!pvp) {
		pr_err("[%s]pvp get failed!\n", __func__);
		return -EINVAL;
	}
	if (rate > dfclk->sensitive_freq * 1000) {
		/*rasing rate and volt*/
		sw_up.target_freq = rate;
		sw_up.target_volt = PERI_VOLT_2;
		sw_up.pvp = pvp;
		sw_up.linkage = friend_clk;
		schedule_work(&sw_up.updata);
	} else {
		/*dropping rate and volt*/
		ret = clk_set_rate_nolock(friend_clk, rate);
		if (ret < 0) {
			pr_err("[%s] fail to updata rate, ret = %d!\n", __func__, ret);
			return ret;
		}
		/*set volt is async*/
		ret = peri_set_volt(pvp, PERI_VOLT_0);
		if (ret < 0) {
			pr_err("[%s]pvp set volt failed ret =%d!\n", __func__, ret);
			ret = clk_set_rate_nolock(friend_clk, dfclk->rate);
			if (ret < 0)
				pr_err("[%s] fail to reback, ret = %d!\n", __func__, ret);
			return ret;
		}
	}
now:
#endif
	dfclk->rate = rate;
	return ret;
}

#ifdef CONFIG_HISI_PERIDVFS
static int peri_volt_change(u32 id, u32 volt)
{
	struct peri_volt_poll *pvp = NULL;
	int ret = 0;

	pvp = peri_volt_poll_get(id, NULL);
	if (!pvp) {
		pr_err("[%s]pvp get failed!\n", __func__);
		return -EINVAL;
	}
	ret = peri_set_volt(pvp, volt);
	if (ret < 0) {
		pr_err("[%s]set volt failed ret=%d!\n", __func__, ret);
		return ret;
	}
	return ret;
}
#endif

static int peri_dvfs_clk_prepare(struct clk_hw *hw)
{
	struct peri_dvfs_clk *dfclk = container_of(hw, struct peri_dvfs_clk, hw);
	struct clk *friend_clk;
	int ret = 0;
	u32 cur_rate = 0;

	friend_clk = __clk_lookup(dfclk->link);
	if (IS_ERR_OR_NULL(friend_clk)) {
		pr_err("[%s] %s get failed!\n", __func__, dfclk->link);
		return -ENODEV;
	}
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	ret = __clk_prepare(friend_clk);
#else
	ret = clk_core_prepare(friend_clk->core);
#endif
	if (ret) {
		pr_err("[%s], friend clock prepare faild!", __func__);
		return ret;
	}
#ifdef CONFIG_HISI_PERIDVFS
	cur_rate = clk_get_rate(hw->clk);
	if (!cur_rate) {
		pr_err("[%s]soft rate mustn't be 0,please check!\n", __func__);
	}
	/*when first open clock if clock is closed and if freq <= sensitive_freq,
		then poll reducing volt
	*/
	if (cur_rate <= dfclk->sensitive_freq * 1000) {
		ret = peri_volt_change(dfclk->id, PERI_VOLT_0);
	} else {
		ret = peri_volt_change(dfclk->id, PERI_VOLT_2);
	}
#endif
	return ret;
}

/*func: dvfs clk enable func
*/
static int peri_dvfs_clk_enable(struct clk_hw *hw)
{
	struct peri_dvfs_clk *dfclk = container_of(hw, struct peri_dvfs_clk, hw);
	struct clk *friend_clk;
	int ret = 0;

	friend_clk = __clk_lookup(dfclk->link);
	if (IS_ERR_OR_NULL(friend_clk)) {
		pr_err("[%s] %s get failed!\n", __func__, dfclk->link);
		return -ENODEV;
	}
	ret = __clk_enable(friend_clk);
	if (ret) {
		pr_err("[%s], friend clock enable faild!", __func__);
		return ret;
	}
	return ret;
}

/*func: dvfs clk disable func
*/
static void peri_dvfs_clk_disable(struct clk_hw *hw)
{
	struct peri_dvfs_clk *dfclk = container_of(hw, struct peri_dvfs_clk, hw);
	struct clk *friend_clk;

	friend_clk = __clk_lookup(dfclk->link);
	if (IS_ERR_OR_NULL(friend_clk))
		pr_err("[%s] %s get failed!\n", __func__, dfclk->link);
	__clk_disable(friend_clk);
}

static void peri_dvfs_clk_unprepare(struct clk_hw *hw)
{
	struct peri_dvfs_clk *dfclk = container_of(hw, struct peri_dvfs_clk, hw);
	struct clk *friend_clk;

	friend_clk = __clk_lookup(dfclk->link);
	if (IS_ERR_OR_NULL(friend_clk)) {
		pr_err("[%s] %s get failed!\n", __func__, dfclk->link);
        return;
    }
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	__clk_unprepare(friend_clk);
#else
	clk_core_unprepare(friend_clk->core);
#endif

#ifdef CONFIG_HISI_PERIDVFS
	peri_volt_change(dfclk->id, PERI_VOLT_0);
#endif
	return;
}

static struct clk_ops peri_dvfs_clk_ops = {
	.recalc_rate	= peri_dvfs_clk_recalc_rate,
	.set_rate	= peri_dvfs_clk_set_rate,
	.determine_rate = peri_dvfs_clk_determine_rate,
	.round_rate	= peri_dvfs_clk_round_rate,
	.prepare	= peri_dvfs_clk_prepare,
	.unprepare	= peri_dvfs_clk_unprepare,
	.enable		= peri_dvfs_clk_enable,
	.disable	= peri_dvfs_clk_disable,
};

/*
 *.setup is for vdec or edc
 */
static void __init hisi_peri_dvfs_clk_setup(struct device_node *np)
{
	struct clk *clk;
	const char *clk_name, *clk_friend;
	struct clk_init_data *init;
	struct peri_dvfs_clk *devfreq_clk;
	int sensitive_freq, i, device_id = 0;
	u32 freq[2] = {0};

	if (of_property_read_string(np, "clock-output-names", &clk_name)) {
		pr_err("[%s] node %s doesn't have clock-output-names property!\n",
			__func__, np->name);
		goto err_prop;
	}
	if (of_property_read_u32(np, "hisilicon,clk-devfreq-id", &device_id)) {
		pr_err("[%s] node %s doesn't have clk-devfreq-id property!\n",
			__func__, np->name);
		goto err_prop;
	}
	if (of_property_read_string(np, "clock-friend-names", &clk_friend))
		clk_friend = NULL;
	if (of_property_read_u32(np, "hisilicon,sensitive-freq", &sensitive_freq)) {
		pr_err("[%s] node %s doesn't have sensitive-freqproperty!\n",
			__func__, np->name);
		goto err_prop;
	}
	devfreq_clk = kzalloc(sizeof(struct peri_dvfs_clk), GFP_KERNEL);
	if (!devfreq_clk) {
		pr_err("[%s] fail to alloc devfreq_clk!\n", __func__);
		goto err_prop;
	}
	init = kzalloc(sizeof(struct clk_init_data), GFP_KERNEL);
	if (!init) {
		pr_err("[%s] fail to alloc init!\n", __func__);
		goto err_init;
	}
	init->name = kstrdup(clk_name, GFP_KERNEL);
	init->ops = &peri_dvfs_clk_ops;
	init->parent_names = NULL;
	init->num_parents = 0;
	init->flags = CLK_IS_ROOT | CLK_GET_RATE_NOCACHE;

	for (i = 0; i < MAX_FREQ_NUM; i++) {
		devfreq_clk->freq_table[i] = 0;
		devfreq_clk->volt[i] = 0;
	}
	if (of_property_read_u32_array(np, "hisilicon,freq-opp-range", &freq[0], MAX_FREQ_NUM)) {
		pr_err("[%s] node %s doesn't freq-opp property!\n", __func__, np->name);
		goto err_clk;
	}
	for (i = 0; i < MAX_FREQ_NUM; i++)
		devfreq_clk->freq_table[i] = freq[i];
	devfreq_clk->hw.init = init;
	devfreq_clk->id = device_id;
	devfreq_clk->link = clk_friend;
	devfreq_clk->reg = NULL;
	devfreq_clk->rate = 0;
	devfreq_clk->sensitive_freq = sensitive_freq;
	devfreq_clk->crgctrl = hs_clk_base(HS_CRGCTRL);

	clk = clk_register(NULL, &devfreq_clk->hw);
	if (IS_ERR(clk)) {
		pr_err("[%s] fail to register devfreq_clk %s!\n",
				__func__, clk_name);
		goto err_clk;
	}
#ifdef CONFIG_HISI_PERIDVFS
	sw_up.clk = clk;
	INIT_WORK(&sw_up.updata, updata_freq_volt_up_fn);
#endif
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	clk_register_clkdev(clk, clk_name, NULL);
	return;

err_clk:
	kfree(init);
	init = NULL;
err_init:
	kfree(devfreq_clk);
	devfreq_clk = NULL;
err_prop:
	return;
}

CLK_OF_DECLARE(hisi_peri_dvfs, "hisilicon,clkdev-dvfs", hisi_peri_dvfs_clk_setup);
