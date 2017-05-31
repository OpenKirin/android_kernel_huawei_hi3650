/*
 *
 * (C) COPYRIGHT ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */





#include <linux/ioport.h>
#include <mali_kbase.h>
#include <mali_kbase_defs.h>
#include <mali_kbase_config.h>
#ifdef CONFIG_DEVFREQ_THERMAL
#include <linux/devfreq_cooling.h>
#endif

#include <linux/opp.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#ifdef CONFIG_REPORT_VSYNC
#include <linux/export.h>
#endif
#include <linux/delay.h>

/* Versatile Express (VE) configuration defaults shared between config_attributes[]
 * and config_attributes_hw_issue_8408[]. Settings are not shared for
 * JS_HARD_STOP_TICKS_SS and JS_RESET_TICKS_SS.
 */
#define KBASE_VE_JS_SCHEDULING_TICK_NS_DEBUG    15000000u      /* 15ms, an agressive tick for testing purposes. This will reduce performance significantly */
#define KBASE_VE_JS_SOFT_STOP_TICKS_DEBUG       1	/* between 15ms and 30ms before soft-stop a job */
#define KBASE_VE_JS_SOFT_STOP_TICKS_CL_DEBUG    1	/* between 15ms and 30ms before soft-stop a CL job */
#define KBASE_VE_JS_HARD_STOP_TICKS_SS_DEBUG    333	/* 5s before hard-stop */
#define KBASE_VE_JS_HARD_STOP_TICKS_SS_8401_DEBUG 2000	/* 30s before hard-stop, for a certain GLES2 test at 128x128 (bound by combined vertex+tiler job) - for issue 8401 */
#define KBASE_VE_JS_HARD_STOP_TICKS_CL_DEBUG    166	/* 2.5s before hard-stop */
#define KBASE_VE_JS_HARD_STOP_TICKS_NSS_DEBUG   100000	/* 1500s (25mins) before NSS hard-stop */
#define KBASE_VE_JS_RESET_TICKS_SS_DEBUG        500	/* 45s before resetting GPU, for a certain GLES2 test at 128x128 (bound by combined vertex+tiler job) */
#define KBASE_VE_JS_RESET_TICKS_SS_8401_DEBUG   3000	/* 7.5s before resetting GPU - for issue 8401 */
#define KBASE_VE_JS_RESET_TICKS_CL_DEBUG        500	/* 45s before resetting GPU */
#define KBASE_VE_JS_RESET_TICKS_NSS_DEBUG       100166	/* 1502s before resetting GPU */

#define KBASE_VE_JS_SCHEDULING_TICK_NS          1250000000u	/* 1.25s */
#define KBASE_VE_JS_SOFT_STOP_TICKS             2	/* 2.5s before soft-stop a job */
#define KBASE_VE_JS_SOFT_STOP_TICKS_CL          1	/* 1.25s before soft-stop a CL job */
#define KBASE_VE_JS_HARD_STOP_TICKS_SS          4	/* 5s before hard-stop */
#define KBASE_VE_JS_HARD_STOP_TICKS_SS_8401     24	/* 30s before hard-stop, for a certain GLES2 test at 128x128 (bound by combined vertex+tiler job) - for issue 8401 */
#define KBASE_VE_JS_HARD_STOP_TICKS_CL          2	/* 2.5s before hard-stop */
#define KBASE_VE_JS_HARD_STOP_TICKS_NSS         1200	/* 1500s before NSS hard-stop */
#define KBASE_VE_JS_RESET_TICKS_SS              6	/* 7.5s before resetting GPU */
#define KBASE_VE_JS_RESET_TICKS_SS_8401         36	/* 45s before resetting GPU, for a certain GLES2 test at 128x128 (bound by combined vertex+tiler job) - for issue 8401 */
#define KBASE_VE_JS_RESET_TICKS_CL              3	/* 7.5s before resetting GPU */
#define KBASE_VE_JS_RESET_TICKS_NSS             1201	/* 1502s before resetting GPU */

#define KBASE_VE_JS_RESET_TIMEOUT_MS            3000	/* 3s before cancelling stuck jobs */
#define KBASE_VE_JS_CTX_TIMESLICE_NS            1000000	/* 1ms - an agressive timeslice for testing purposes (causes lots of scheduling out for >4 ctxs) */
#define KBASE_VE_POWER_MANAGEMENT_CALLBACKS     ((uintptr_t)&pm_callbacks)
#define KBASE_PLATFORM_CALLBACKS                ((uintptr_t)&platform_funcs)
#ifdef CONFIG_PM_DEVFREQ
#define KBASE_POWER_MODEL_CALLBACKS		((uintptr_t)&hisi_model_ops)
#endif

#define HARD_RESET_AT_POWER_OFF 0

#ifndef CONFIG_OF
static kbase_io_resources io_resources = {
	.job_irq_number = 68,
	.mmu_irq_number = 69,
	.gpu_irq_number = 70,
	.io_memory_region = {
	.start = 0xFC010000,
	.end = 0xFC010000 + (4096 * 4) - 1
	}
};
#endif /* CONFIG_OF */

#define KBASE_HI3635_PLATFORM_GPU_REGULATOR_NAME      "gpu"
#define DEFAULT_POLLING_MS	20
#define STOP_POLLING		0

static u32 RUNTIME_PM_DELAY_TIME = 100;

#ifdef CONFIG_REPORT_VSYNC
static struct kbase_device *kbase_dev = NULL;
#endif

#if 0 /* use following code to power on/off gpu, bypass lpm3 control */
static inline void kbase_platform_power_on_stub(struct kbase_device *kbdev)
{
        void __iomem *crg = ioremap(0xfff35000, 0xfff);
        void __iomem *pmu = ioremap(0xfff36000, 0xfff);

        writel(0x00000003, pmu+0x938);
        msleep(5);
        writel(0x00000020, crg+0x148);
        writel(0x007c001c, crg+0x88);
        writel(0x00000001, crg+0x234);
        writel(0x00000001, crg+0x238);
        msleep(1);
        writel(0x00030003, crg+0xf0);
        writel(0x00000038, crg+0x30);
        msleep(1);
        writel(0x2968a819, kbdev->reg+0x50);
        writel(0xc4b00960, kbdev->reg+0x58);
        msleep(1);
}

static inline void kbase_platform_power_off_stub(struct kbase_device *kbdev)
{
        void __iomem *crg = ioremap(0xfff35000, 0xfff);
        void __iomem *pmu = ioremap(0xfff36000, 0xfff);

        writel(0x00000000, crg+0x234);
        writel(0x00000000, crg+0x238);
        msleep(1);
        writel(0x007c001c, crg+0x084);
        writel(0x00000038, crg+0x034);
        writel(0x00030000, crg+0x0f0);
        writel(0x00000020, crg+0x144);
        writel(0x00000000, pmu+0x938);
        msleep(1);
}
#endif

static inline void kbase_platform_on(struct kbase_device *kbdev)
{
	if (kbdev->regulator) {
		if (unlikely(regulator_enable(kbdev->regulator)))
		{
			printk("MALI-MIDGARD:  Failed to enable regulator\n");
		}
#ifdef CONFIG_ARCH_HI3650
		else
		{
			kbase_os_reg_write(kbdev,GPU_CONTROL_REG(PWR_KEY),KBASE_PWR_KEY_VALUE);
			kbase_os_reg_write(kbdev,GPU_CONTROL_REG(PWR_OVERRIDE1),KBASE_PWR_OVERRIDE_VALUE);
		}
#endif
	}
}

static inline void kbase_platform_off(struct kbase_device *kbdev)
{
	if (kbdev->regulator)
		regulator_disable(kbdev->regulator);

}

#ifdef CONFIG_PM_DEVFREQ
static int mali_kbase_devfreq_target(struct device *dev, unsigned long *_freq,
			      u32 flags)
{
	struct kbase_device *kbdev = (struct kbase_device *)dev->platform_data;
	unsigned long old_freq = kbdev->devfreq->previous_freq;
	struct opp *opp = NULL;
	unsigned long freq;

	rcu_read_lock();
	opp = devfreq_recommended_opp(dev, _freq, flags);
	if (IS_ERR(opp)) {
		pr_err("[mali-midgard]  Failed to get Operating Performance Point\n");
		rcu_read_unlock();
		return PTR_ERR(opp);
	}
	freq = opp_get_freq(opp);
	rcu_read_unlock();

#ifdef CONFIG_HISI_IPA_THERMAL
	freq = ipa_freq_limit(IPA_GPU,freq);
#endif
	if (old_freq == freq)
		return 0;

	if (clk_set_rate((kbdev->clk), freq)) {
		pr_err("[mali-midgard]  Failed to set gpu freqency, [%lu->%lu]\n", old_freq, freq);
		return -ENODEV;
	}

	*_freq = freq;

	return 0;
}

static int mali_kbase_get_dev_status(struct device *dev,
				      struct devfreq_dev_status *stat)
{
	struct kbase_device *kbdev = (struct kbase_device *)dev->platform_data;

	if (kbdev->pm.metrics.kbdev != kbdev) {
		pr_err("[mali-midgard] pm metrics not initialized\n", __func__);
		return 0;
	}

	(void)kbase_pm_get_dvfs_action(kbdev);
	stat->busy_time = kbdev->pm.metrics.utilisation;
	stat->total_time = 100;
	stat->private_data = (void *)(long)kbdev->pm.metrics.vsync_hit;
	stat->current_frequency = clk_get_rate(kbdev->clk);

#ifdef CONFIG_DEVFREQ_THERMAL
	memcpy(&kbdev->devfreq_cooling->last_status, stat, sizeof(*stat));
#endif

	return 0;
}

static struct devfreq_dev_profile mali_kbase_devfreq_profile = {
	/* it would be abnormal to enable devfreq monitor during initialization. */
	.polling_ms	= DEFAULT_POLLING_MS, //STOP_POLLING,
	.target		= mali_kbase_devfreq_target,
	.get_dev_status	= mali_kbase_get_dev_status,
};
#endif

#ifdef CONFIG_REPORT_VSYNC
void mali_kbase_pm_report_vsync(int buffer_updated)
{
	if (kbase_dev)
		kbase_pm_report_vsync(kbase_dev, buffer_updated);
}
EXPORT_SYMBOL(mali_kbase_pm_report_vsync);
#endif

#ifdef CONFIG_MALI_MIDGARD_DVFS
int kbase_platform_dvfs_event(struct kbase_device *kbdev, u32 utilisation, u32 util_gl_share, u32 util_cl_share[2])
{
	return 1;
}

int kbase_platform_dvfs_enable(struct kbase_device *kbdev, bool enable, int freq)
{
	unsigned long flags;

	KBASE_DEBUG_ASSERT(kbdev != NULL);

	if (enable != kbdev->pm.metrics.timer_active) {
		if (enable) {
			spin_lock_irqsave(&kbdev->pm.metrics.lock, flags);
			kbdev->pm.metrics.timer_active = MALI_TRUE;
			spin_unlock_irqrestore(&kbdev->pm.metrics.lock, flags);
			hrtimer_start(&kbdev->pm.metrics.timer,
					HR_TIMER_DELAY_MSEC(kbdev->pm.platform_dvfs_frequency),
					HRTIMER_MODE_REL);
		} else {
			spin_lock_irqsave(&kbdev->pm.metrics.lock, flags);
			kbdev->pm.metrics.timer_active = MALI_FALSE;
			spin_unlock_irqrestore(&kbdev->pm.metrics.lock, flags);
			hrtimer_cancel(&kbdev->pm.metrics.timer);
		}
	}

	return 1;
}
#endif

#ifdef CONFIG_DEVFREQ_THERMAL
static unsigned long hisi_model_static_power(unsigned long voltage)
{
	struct thermal_zone_device *tz = NULL;
	unsigned long temperature;
	const unsigned long voltage_cubed = (voltage * voltage * voltage) >> 10;
	unsigned long temp,temp_squared,temp_cubed;
	unsigned long temp_scaling_factor =0;

        struct device_node * dev_node = NULL;
        u32 prop;
        int ret = -EINVAL,i;
        const char*  temperature_scale_capacitance[5];
        int capacitance[5]={0};
        dev_node = of_find_compatible_node(NULL,NULL,"arm,ipa-thermal");
        if (dev_node) {
            for (i = 0; i < 5; i++) {
              ret =  of_property_read_string_index(dev_node,"hisilicon,gpu_temp_scale_capacitance",i,&temperature_scale_capacitance[i]);
              if (ret) {
		pr_err("%s temperature_scale_capacitance [%d] read err\n",__func__,i);
		continue;
		}

                (void)kstrtoint(temperature_scale_capacitance[i],10, &capacitance[i]);
            }
        }

	temperature = get_soc_temp();
	temp = temperature / 1000;
	temp_squared = temp * temp;
	temp_cubed = temp_squared * temp;
	temp_scaling_factor = capacitance[3]*temp_cubed +
	              capacitance[2]*temp_squared +
	              capacitance[1]*temp +
	              capacitance[0];

        return (((capacitance[4] * voltage_cubed) >> 20) * temp_scaling_factor) / 1000000;
}

static unsigned long hisi_model_dynamic_power(unsigned long freq,
		unsigned long voltage)
{
	/* The inputs: freq (f) is in Hz, and voltage (v) in mV.
	 * The coefficient (c) is in mW/(MHz mV mV).
	 *
	 * This function calculates the dynamic power after this formula:
	 * Pdyn (mW) = c (mW/(MHz*mV*mV)) * v (mV) * v (mV) * f (MHz)
	 */
	const unsigned long v2 = (voltage * voltage) / 1000; /* m*(V*V) */
	const unsigned long f_mhz = freq / 1000000; /* MHz */
	unsigned long coefficient = 3600; /* mW/(MHz*mV*mV) */
    struct device_node * dev_node = NULL;
    u32 prop;
    dev_node = of_find_compatible_node(NULL,NULL,"arm,ipa-thermal");
    if(dev_node)
    {
        int ret = of_property_read_u32(dev_node,"hisilicon,gpu_dyn_capacitance",&prop);
        if(ret == 0)
        {
            coefficient = prop;
        }
    }

	return (coefficient * v2 * f_mhz) / 1000000; /* mW */
}

static struct devfreq_cooling_ops hisi_model_ops = {
        .get_static_power = hisi_model_static_power,
        .get_dynamic_power = hisi_model_dynamic_power,
};

#endif

static mali_bool kbase_platform_init(struct kbase_device *kbdev)
{
      int err;
	struct device *dev = kbdev->dev;
	dev->platform_data = kbdev;

#ifdef CONFIG_REPORT_VSYNC
	kbase_dev = kbdev;
#endif

	kbdev->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(kbdev->clk)) {
		printk("[mali-midgard]  Failed to get clk\n");
		return MALI_FALSE;
	}

	kbdev->regulator = devm_regulator_get(dev, KBASE_HI3635_PLATFORM_GPU_REGULATOR_NAME);
	if (IS_ERR(kbdev->regulator)) {
		printk("[mali-midgard]  Failed to get regulator\n");
		return MALI_FALSE;
	}

#ifdef CONFIG_PM_DEVFREQ
	if (dev_pm_opp_of_add_table(dev) ||
		opp_init_devfreq_table(dev,
			&mali_kbase_devfreq_profile.freq_table)) {
		printk("[mali-midgard]  Failed to init devfreq_table\n");
		kbdev->devfreq = NULL;
	} else {
		mali_kbase_devfreq_profile.initial_freq	= clk_get_rate(kbdev->clk);
		rcu_read_lock();
		mali_kbase_devfreq_profile.max_state = opp_get_opp_count(dev);
		rcu_read_unlock();
		kbdev->devfreq = devfreq_add_device(dev,
						&mali_kbase_devfreq_profile,
						"mali_ondemand",
						NULL);
	}

	if (NULL == kbdev->devfreq) {
		printk("[mali-midgard]  NULL pointer [kbdev->devFreq]\n");
		goto JUMP_DEVFREQ_THERMAL;
	}

#ifdef CONFIG_DEVFREQ_THERMAL
	{
		struct devfreq_cooling_ops *callbacks;

		callbacks = (void *)kbasep_get_config_value(kbdev,
				kbdev->config_attributes,
				KBASE_CONFIG_ATTR_POWER_MODEL_CALLBACKS);

		kbdev->devfreq_cooling = of_devfreq_cooling_register_power(
				kbdev->dev->of_node,
				kbdev->devfreq,
				callbacks);
		if (IS_ERR_OR_NULL(kbdev->devfreq_cooling)) {
			err = PTR_ERR(kbdev->devfreq_cooling);
			dev_err(kbdev->dev,
				"[MALI-MIDGARD]: Failed to register cooling device (%d)\n",
				err);
			HiLOGE("DISPLAY", "GPU", "[MALI-MIDGARD]: Failed to register cooling device (%d)",err);
			goto JUMP_DEVFREQ_THERMAL;
		}
	}
#endif

	/* make devfreq function */
	//mali_kbase_devfreq_profile.polling_ms = DEFAULT_POLLING_MS;
#endif/*CONFIG_PM_DEVFREQ*/
JUMP_DEVFREQ_THERMAL:
	return MALI_TRUE;
}

static void kbase_platform_term(struct kbase_device *kbdev)
{
#ifdef CONFIG_PM_DEVFREQ
	devfreq_remove_device(kbdev->devfreq);
#endif
}

kbase_platform_funcs_conf platform_funcs = {
	.platform_init_func = &kbase_platform_init,
	.platform_term_func = &kbase_platform_term,
};

static int pm_callback_power_on(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	int result;
	int ret_val;
	struct device *dev = kbdev->dev;

#if (HARD_RESET_AT_POWER_OFF != 1)
	if (!pm_runtime_status_suspended(dev))
		ret_val = 0;
	else
#endif
		ret_val = 1;

	if (unlikely(dev->power.disable_depth > 0)) {
		kbase_platform_on(kbdev);
	} else {
		result = pm_runtime_resume(dev);
		if (result < 0 && result == -EAGAIN)
			kbase_platform_on(kbdev);
		else if (result < 0)
			printk("[mali-midgard]  pm_runtime_resume failed (%d)\n", result);
	}

	return ret_val;
#else
	kbase_platform_on(kbdev);

	return 1;
#endif
}

static void pm_callback_power_off(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	struct device *dev = kbdev->dev;
	int ret = 0, retry = 0;

#if HARD_RESET_AT_POWER_OFF
	/* Cause a GPU hard reset to test whether we have actually idled the GPU
	 * and that we properly reconfigure the GPU on power up.
	 * Usually this would be dangerous, but if the GPU is working correctly it should
	 * be completely safe as the GPU should not be active at this point.
	 * However this is disabled normally because it will most likely interfere with
	 * bus logging etc.
	 */
	KBASE_TRACE_ADD(kbdev, CORE_GPU_HARD_RESET, NULL, NULL, 0u, 0);
	kbase_os_reg_write(kbdev, GPU_CONTROL_REG(GPU_COMMAND), GPU_COMMAND_HARD_RESET);
#endif

	if (unlikely(dev->power.disable_depth > 0)) {
		kbase_platform_off(kbdev);
	} else {
		do {
			ret = pm_schedule_suspend(dev, RUNTIME_PM_DELAY_TIME);
			if (ret != -EAGAIN) {
				if (unlikely(ret < 0)) {
					pr_err("[mali-midgard]  pm_schedule_suspend failed (%d)\n\n", ret);
					WARN_ON(1);
				}

				/* correct status */
				break;
			}

			/* -EAGAIN, repeated attempts for 1s totally */
			msleep(50);
		} while (++retry < 20);
	}
#else
	kbase_platform_off(kbdev);
#endif
}

static mali_error pm_callback_runtime_init(struct kbase_device *kbdev)
{
	pm_suspend_ignore_children(kbdev->dev, true);
	pm_runtime_enable(kbdev->dev);
	return MALI_ERROR_NONE;
}

static void pm_callback_runtime_term(struct kbase_device *kbdev)
{
	pm_runtime_disable(kbdev->dev);
}

static void pm_callback_runtime_off(struct kbase_device *kbdev)
{
#ifdef CONFIG_PM_DEVFREQ
	devfreq_suspend_device(kbdev->devfreq);
#elif defined(CONFIG_MALI_MIDGARD_DVFS)
	kbase_platform_dvfs_enable(kbdev, false, 0);
#endif

	kbase_platform_off(kbdev);
}

static int pm_callback_runtime_on(struct kbase_device *kbdev)
{
	kbase_platform_on(kbdev);

#ifdef CONFIG_PM_DEVFREQ
	devfreq_resume_device(kbdev->devfreq);
#elif defined(CONFIG_MALI_MIDGARD_DVFS)
	if (kbase_platform_dvfs_enable(kbdev, true, 0) != MALI_TRUE)
		return -EPERM;
#endif

	return 0;
}

static inline void pm_callback_suspend(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	if (!pm_runtime_status_suspended(kbdev->dev))
		pm_callback_runtime_off(kbdev);
#else
	pm_callback_power_off(kbdev);
#endif
}

static inline void pm_callback_resume(struct kbase_device *kbdev)
{
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	if (!pm_runtime_status_suspended(kbdev->dev))
		pm_callback_runtime_on(kbdev);
	else
		pm_callback_power_on(kbdev);
#else
	pm_callback_power_on(kbdev);
#endif
}

static struct kbase_pm_callback_conf pm_callbacks = {
	.power_on_callback = pm_callback_power_on,
	.power_off_callback = pm_callback_power_off,
	.power_suspend_callback = pm_callback_suspend,
	.power_resume_callback = pm_callback_resume,
#ifdef CONFIG_MALI_MIDGARD_RT_PM
	.power_runtime_init_callback = pm_callback_runtime_init,
	.power_runtime_term_callback = pm_callback_runtime_term,
	.power_runtime_off_callback = pm_callback_runtime_off,
	.power_runtime_on_callback = pm_callback_runtime_on
#else
	.power_runtime_init_callback = NULL,
	.power_runtime_term_callback = NULL,
	.power_runtime_off_callback = NULL,
	.power_runtime_on_callback = NULL
#endif
};

/* Please keep table config_attributes in sync with config_attributes_hw_issue_8408 */
static struct kbase_attribute config_attributes[] = {
#ifdef CONFIG_MALI_DEBUG
/* Use more aggressive scheduling timeouts in debug builds for testing purposes */
	{
	 KBASE_CONFIG_ATTR_JS_SCHEDULING_TICK_NS,
	 KBASE_VE_JS_SCHEDULING_TICK_NS_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_SOFT_STOP_TICKS,
	 KBASE_VE_JS_SOFT_STOP_TICKS_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_SOFT_STOP_TICKS_CL,
	 KBASE_VE_JS_SOFT_STOP_TICKS_CL_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_HARD_STOP_TICKS_SS,
	 KBASE_VE_JS_HARD_STOP_TICKS_SS_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_HARD_STOP_TICKS_CL,
	 KBASE_VE_JS_HARD_STOP_TICKS_CL_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_HARD_STOP_TICKS_NSS,
	 KBASE_VE_JS_HARD_STOP_TICKS_NSS_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_RESET_TICKS_SS,
	 KBASE_VE_JS_RESET_TICKS_SS_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_RESET_TICKS_CL,
	 KBASE_VE_JS_RESET_TICKS_CL_DEBUG},

	{
	 KBASE_CONFIG_ATTR_JS_RESET_TICKS_NSS,
	 KBASE_VE_JS_RESET_TICKS_NSS_DEBUG},
#else				/* CONFIG_MALI_DEBUG */
/* In release builds same as the defaults but scaled for 5MHz FPGA */
	{
	 KBASE_CONFIG_ATTR_JS_SCHEDULING_TICK_NS,
	 KBASE_VE_JS_SCHEDULING_TICK_NS},

	{
	 KBASE_CONFIG_ATTR_JS_SOFT_STOP_TICKS,
	 KBASE_VE_JS_SOFT_STOP_TICKS},

	{
	 KBASE_CONFIG_ATTR_JS_SOFT_STOP_TICKS_CL,
	 KBASE_VE_JS_SOFT_STOP_TICKS_CL},

	{
	 KBASE_CONFIG_ATTR_JS_HARD_STOP_TICKS_SS,
	 KBASE_VE_JS_HARD_STOP_TICKS_SS},

	{
	 KBASE_CONFIG_ATTR_JS_HARD_STOP_TICKS_CL,
	 KBASE_VE_JS_HARD_STOP_TICKS_CL},

	{
	 KBASE_CONFIG_ATTR_JS_HARD_STOP_TICKS_NSS,
	 KBASE_VE_JS_HARD_STOP_TICKS_NSS},

	{
	 KBASE_CONFIG_ATTR_JS_RESET_TICKS_SS,
	 KBASE_VE_JS_RESET_TICKS_SS},

	{
	 KBASE_CONFIG_ATTR_JS_RESET_TICKS_CL,
	 KBASE_VE_JS_RESET_TICKS_CL},

	{
	 KBASE_CONFIG_ATTR_JS_RESET_TICKS_NSS,
	 KBASE_VE_JS_RESET_TICKS_NSS},
#endif				/* CONFIG_MALI_DEBUG */
	{
	 KBASE_CONFIG_ATTR_JS_RESET_TIMEOUT_MS,
	 KBASE_VE_JS_RESET_TIMEOUT_MS},

	{
	 KBASE_CONFIG_ATTR_JS_CTX_TIMESLICE_NS,
	 KBASE_VE_JS_CTX_TIMESLICE_NS},
	{
	 KBASE_CONFIG_ATTR_POWER_MANAGEMENT_CALLBACKS,
	 KBASE_VE_POWER_MANAGEMENT_CALLBACKS},
	{
	 KBASE_CONFIG_ATTR_PLATFORM_FUNCS,
	 KBASE_PLATFORM_CALLBACKS},
#ifdef CONFIG_DEVFREQ_THERMAL
	{
	KBASE_CONFIG_ATTR_POWER_MODEL_CALLBACKS,
	KBASE_POWER_MODEL_CALLBACKS},
#endif
	{
	 KBASE_CONFIG_ATTR_END,
	 0}
};

static struct kbase_platform_config hi3650_platform_config = {
	.attributes = config_attributes,
#ifndef CONFIG_OF
	.io_resources = &io_resources
#endif
};

struct kbase_platform_config *kbase_get_platform_config(void)
{
	return &hi3650_platform_config;
}

int kbase_platform_early_init(void)
{
	/* Nothing needed at this stage */
	return 0;
}

#ifdef CONFIG_DEBUG_FS

#define MALI_PM_RUNTIME_DELAY_TIME_DEBUGFS_FILE_NAME "mali_pm_runtime_delay_time"

int __init mali_pm_runtime_delay_time_debugfs_init(void)
{
    struct dentry *mali_debugfs_dir = NULL;

    printk("mali_pm_runtime_delay_time_debugfs_init\n");

    debugfs_create_u32(MALI_PM_RUNTIME_DELAY_TIME_DEBUGFS_FILE_NAME, 0664, mali_debugfs_dir,  &RUNTIME_PM_DELAY_TIME);
    return 0;
}
module_init(mali_pm_runtime_delay_time_debugfs_init);
#endif
