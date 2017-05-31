/*
 *  slimbus is a kernel driver which is used to manager SLIMbus devices
 *  Copyright (C) 2014  Hisilicon

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/of.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <linux/hisi/hilog.h>

static struct snd_soc_dai_link hi3660_hi6402_dai_link[] = {
	{
		/* dai link name*/
		.name       = "hi3660_hi6402_pb_normal",
		/* stream name same as name */
		.stream_name    = "hi3660_hi6402_pb_normal",
		/* codec device name ,see in hi6402.c */
		.codec_name = "hi6402-codec",
		/* cpu dai name(device name), see in slimbus_dai.c */
		.cpu_dai_name   = "slimbus-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name = "hi6402-audio-dai",
		/* platform device name */
		.platform_name  = "hi6210-hifi",
	},
	{
		/* dai link name*/
		.name       = "hi3660_voice",
		/* stream name same as name */
		.stream_name    = "hi3660_voice",
		/* codec device name ,see in hi6402.c */
		.codec_name = "hi6402-codec",
		/* cpu dai name(device name), see in slimbus_dai.c */
		.cpu_dai_name   = "slimbus-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name = "hi6402-voice-dai",
		/* platform device name */
		.platform_name  = "snd-soc-dummy",
	},
	{
		/* dai link name*/
		.name       = "hi3660_fm1",
		/* stream name same as name */
		.stream_name    = "hi3660_fm1",
		/* codec device name ,see in hi6402.c */
		.codec_name = "hi6402-codec",
		/* cpu dai name(device name), see in slimbus_dai.c */
		.cpu_dai_name   = "slimbus-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name = "hi6402-fm-dai",
		/* platform device name */
		.platform_name  = "snd-soc-dummy",
	},
	{
		/* dai link name*/
		.name       = "hi3660_fm2",
		/* stream name same as name */
		.stream_name    = "hi3660_fm2",
		/* codec(hi6402) device name ,see in hi6402.c */
		.codec_name = "hi6402-codec",
		/* cpu dai name(device name), see in slimbus_dai.c */
		.cpu_dai_name   = "slimbus-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name = "hi6402-fm-dai",
		/* platform device name */
		.platform_name  = "snd-soc-dummy",
	},
	{
		/* dai link name*/
		.name       = "hi3660_hi6402_pb_dsp",
		/* stream name same as name */
		.stream_name    = "hi3660_hi6402_pb_dsp",
		/* codec(hi6402) device name ,see in hi6402.c */
		.codec_name = "hi6402-codec",
		/* cpu dai name(device name), see in slimbus_dai.c */
		.cpu_dai_name   = "slimbus-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name = "hi6402-audio-dai",
		/* platform device name */
		.platform_name  = "snd-soc-dummy",
	},
};

/* Audio machine driver */
static struct snd_soc_card hi3660_hi6402_card = {
	/* sound card name, can see all sound cards in /proc/asound/cards */
	.name = "hi3660_HI64xx_CARD",
	.owner = THIS_MODULE,
	.dai_link = hi3660_hi6402_dai_link,
	.num_links = ARRAY_SIZE(hi3660_hi6402_dai_link),
};

static int hi3660_hi6402_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &hi3660_hi6402_card;

	pr_info("Audio : hi3660_hi6402_probe \n");
	card->dev = &pdev->dev;

	ret = snd_soc_register_card(card);
	if (ret) {
		pr_err("%s : register failed %d\n", __FUNCTION__, ret);
		HiLOGE("audio", "Hi3660_hi6402", "%s : register failed %d\n", __FUNCTION__, ret);
	}

	return ret;
}

static int hi3660_hi6402_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	if (NULL != card)
		snd_soc_unregister_card(card);

	return 0;
}

static const struct of_device_id hi3660_hi6402_of_match[] = {
	{.compatible = "hisilicon,hi3xxx-hi6402", },
	{ },
};
MODULE_DEVICE_TABLE(of, hi3660_hi6402_of_match);

static struct platform_driver hi3660_hi6402_driver = {
	.driver	= {
		.name = "hi3660_hi6402",
		.owner = THIS_MODULE,
		.of_match_table = hi3660_hi6402_of_match,
	},
	.probe	= hi3660_hi6402_probe,
	.remove	= hi3660_hi6402_remove,
};
//module_platform_driver(hi3660_hi6402_driver);

static int __init hi3660_init(void)
{
	pr_info("Audio : hi3xxx-hi6402 init \n");
	return platform_driver_register(&hi3660_hi6402_driver);
}

late_initcall(hi3660_init);

static void __exit hi3660_exit(void)
{
	//remove_proc_entry("status", audio_pcm_dir);

	platform_driver_unregister(&hi3660_hi6402_driver);
}
module_exit(hi3660_exit);

/* Module information */
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("ALSA SoC for Hisilicon hi3660 with hi6402 codec");
MODULE_LICENSE("GPL");
MODULE_ALIAS("machine driver:hi3660-hi6402");
