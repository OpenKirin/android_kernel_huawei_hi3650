#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/input.h>
#include <huawei_platform/log/hw_log.h>

#include "audio_dmd.h"
#include <dsm/dsm_pub.h>

#define HWLOG_TAG audio_dmd
HWLOG_REGIST();

static struct dsm_dev dsm_audio_dmd = {
	.name = "dsm_audio",
	.fops = NULL,
	.buff_size = 1024,
};
struct dsm_client * audio_dmd_client = NULL;

static const struct of_device_id audio_dmd_table[] = {
	{
		.compatible = "huawei,audio_dmd",
	},
	{},
};

MODULE_DEVICE_TABLE(of, audio_dmd_table);

static int audio_dmd_probe(struct platform_device* pdev)
{
	int ret = 0;

	hwlog_debug("%s, audio_dmd_probe", __FUNCTION__);

	if(!audio_dmd_client){
		audio_dmd_client = dsm_register_client(&dsm_audio_dmd);
	}

	return ret;
}

static int audio_dmd_remove(struct platform_device* pdev)
{
	return 0;
}

static struct platform_driver audio_dmd_driver = {
	.driver =
	{
		.name  = "audio_dmd",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(audio_dmd_table),
	},
	.probe  = audio_dmd_probe,
	.remove = audio_dmd_remove,
};

struct platform_device audio_dmd_device = {
	.name = "audio_dmd",
};

int __init audio_dmd_init(void)
{
	int ret = 0;
	hwlog_info("audio_dmd init \n");

	ret = platform_driver_register(&audio_dmd_driver);
	if (0 != ret) {
		hwlog_err("audio_dmd driver register fail , ERROR is %d\n", ret);
		goto exit;
	}

	ret = platform_device_register(&audio_dmd_device);
	if (0 != ret) {
		hwlog_err("audio_dmd device register fail , ERROR is %d\n", ret);
		goto exit;
	}

exit:
	return ret;
}

void __exit audio_dmd_exit(void)
{
	platform_driver_unregister(&audio_dmd_driver);
}

module_init(audio_dmd_init);
module_exit(audio_dmd_exit);

MODULE_DESCRIPTION("audio dmd driver");
MODULE_LICENSE("GPL");
