#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/hisi/usb/hisi_usb.h>
#include <linux/mfd/hisi_pmic.h>
#include <pmic_interface.h>
#include <huawei_platform/log/log_jank.h>
#include <huawei_platform/power/direct_charger.h>
#ifdef CONFIG_TCPC_CLASS
#include <huawei_platform/usb/hw_pd_dev.h>
int support_pd;
#endif

struct delayed_work g_disconnect_work;
extern struct completion pd_get_typec_state_completion;

static int huawei_usb_vbus_value(void)
{
	unsigned long base = 0;
	int pmic_status1 = hisi_pmic_reg_read(PMIC_STATUS1_ADDR(base));
	return !!(pmic_status1 & (1 << 7));
}

static irqreturn_t charger_connect_interrupt(int irq, void *p)
{
	pr_info("%s: start\n", __func__);
#ifdef CONFIG_TCPC_CLASS
	if (support_pd && pd_dpm_get_pd_finish_flag() 
		|| pd_dpm_get_pd_source_vbus()) {
		pr_info("in pd mode, do not report charger connect_event\n");
		return IRQ_HANDLED;
	}
#endif
	LOG_JANK_D(JLID_USBCHARGING_START, "JL_USBCHARGING_START");
	hisi_usb_otg_event(CHARGER_CONNECT_EVENT);
	pr_info("%s: end\n", __func__);
	return IRQ_HANDLED;
}

static irqreturn_t charger_disconnect_interrupt(int irq, void *p)
{
	pr_info("%s: start\n", __func__);
	schedule_delayed_work(&g_disconnect_work, msecs_to_jiffies(0));
	pr_info("%s: end\n", __func__);
	return IRQ_HANDLED;
}

static void vbus_disconnect_work(struct work_struct *w)
{
	pr_info("%s: start\n", __func__);

#ifdef CONFIG_TCPC_CLASS
	unsigned long timeout = 0;
        int typec_state = PD_DPM_USB_TYPEC_DETACHED;

	if((direct_charge_get_cutoff_normal_flag() == 0) && strstr(saved_command_line, "androidboot.mode=charger"))
	{
		timeout = wait_for_completion_timeout(&pd_get_typec_state_completion, msecs_to_jiffies(2000));

		if(!timeout)
		{
			pr_info("%s: wait_for_completion_timeout\n", __func__);
		}

		pd_dpm_get_typec_state(&typec_state);

		reinit_completion(&pd_get_typec_state_completion);

		if(typec_state != PD_DPM_USB_TYPEC_DETACHED)
		{
			pr_info("in Power off charging, do not report charger disconnect_event\n");
			return;
		}
	}

	if (support_pd && pd_dpm_get_pd_finish_flag()
		&& !pd_dpm_get_pd_source_vbus) {
		pr_info("in pd mode, do not report charger disconnect_event\n");
		return;
	}
#endif

	LOG_JANK_D(JLID_USBCHARGING_END, "JL_USBCHARGING_END");
        hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);

	pr_info("%s: end\n", __func__);
}

int hw_vbus_connect_irq, hw_vbus_disconnect_irq;

static int hisi_usb_vbus_probe(struct platform_device *pdev)
{
	int ret = 0;
#ifdef CONFIG_TCPC_CLASS
	struct device_node *np = NULL;
	struct device* dev;
#endif
	printk("[%s]+\n", __func__);

#ifdef CONFIG_TCPC_CLASS
	dev = &pdev->dev;
	np = dev->of_node;
	ret = of_property_read_u32(np, "support_pd", &support_pd);
	if (ret) {
		pr_err("get support_pd failed\n");
		return -EINVAL;
	}
	pr_info("support_pd = %d\n", support_pd);
#endif
	hw_vbus_connect_irq = platform_get_irq_byname(pdev, "connect");
	if (0 == hw_vbus_connect_irq) {
		dev_err(&pdev->dev, "failed to get connect irq\n");
		return -ENOENT;
	}
	hw_vbus_disconnect_irq = platform_get_irq_byname(pdev, "disconnect");
	if (0 == hw_vbus_disconnect_irq) {
		dev_err(&pdev->dev, "failed to get disconnect irq\n");
		return -ENOENT;
	}

	pr_info("hw_vbus_connect_irq: %d, hw_vbus_disconnect_irq: %d\n",
			hw_vbus_connect_irq, hw_vbus_disconnect_irq);

	ret = request_irq(hw_vbus_connect_irq, charger_connect_interrupt,
					  IRQF_NO_SUSPEND, "hiusb_in_interrupt", pdev);
	if (ret) {
		pr_err("request charger connect irq failed, irq: %d!\n", hw_vbus_connect_irq);
		return ret;
	}

	ret = request_irq(hw_vbus_disconnect_irq, charger_disconnect_interrupt,
					  IRQF_NO_SUSPEND, "hiusb_in_interrupt", pdev);
	if (ret) {
		free_irq(hw_vbus_disconnect_irq, pdev);
		pr_err("request charger connect irq failed, irq: %d!\n", hw_vbus_disconnect_irq);
	}

	/* avoid lose intrrupt */
	if (huawei_usb_vbus_value()) {
		pr_info("%s: vbus high, issue a charger connect event\n", __func__);
		hisi_usb_otg_event(CHARGER_CONNECT_EVENT);
	} else {
		pr_info("%s: vbus low, issue a charger disconnect event\n", __func__);
		hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
	}

	INIT_DELAYED_WORK(&g_disconnect_work, vbus_disconnect_work);

	printk("[%s]-\n", __func__);

	return ret;
}

static int hisi_usb_vbus_remove(struct platform_device *pdev)
{
	free_irq(hw_vbus_connect_irq, pdev);
	free_irq(hw_vbus_disconnect_irq, pdev);
	return 0;
}

static struct of_device_id hisi_usb_vbus_of_match[] = {
	{ .compatible = "huawei,usbvbus", },
	{ },
};

static struct platform_driver hisi_usb_vbus_drv = {
	.probe		= hisi_usb_vbus_probe,
	.remove		= hisi_usb_vbus_remove,
	.driver		= {
		.owner		= THIS_MODULE,
		.name		= "hw_usb_vbus",
		.of_match_table	= hisi_usb_vbus_of_match,
	},
};

static int __init huawei_usb_vbus_init(void)
{
    return platform_driver_register(&hisi_usb_vbus_drv);
}

static void __exit huawei_usb_vbus_exit(void)
{
    platform_driver_unregister(&hisi_usb_vbus_drv);
}

device_initcall_sync(huawei_usb_vbus_init);
module_exit(huawei_usb_vbus_exit);

MODULE_AUTHOR("huawei");
MODULE_DESCRIPTION("This module detect USB VBUS connection/disconnection");
MODULE_LICENSE("GPL v2");
