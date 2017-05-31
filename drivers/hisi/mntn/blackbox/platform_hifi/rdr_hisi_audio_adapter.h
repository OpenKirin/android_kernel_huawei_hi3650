/*
 * audio rdr adpter.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __RDR_HISI_AUDIO_ADAPTER_H__
#define __RDR_HISI_AUDIO_ADAPTER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/hisi/rdr_pub.h>

#define RDR_FNAME_LEN					128
/* rdr modid for hifi from 0x84000000(HISI_BB_MOD_HIFI_START) to 0x84ffffff(HISI_BB_MOD_HIFI_END) */
#define RDR_AUDIO_MODID_START          HISI_BB_MOD_HIFI_START

#define RDR_AUDIO_SOC_MODID_START      RDR_AUDIO_MODID_START
#define RDR_AUDIO_SOC_WD_TIMEOUT_MODID 0x84000001
#define RDR_AUDIO_SOC_MODID_END        0x8400000f

#define RDR_AUDIO_CODEC_MODID_START      0x84000010
#define RDR_AUDIO_CODEC_WD_TIMEOUT_MODID 0x84000011
#define RDR_AUDIO_CODEC_MODID_END        0x8400001F

#define RDR_AUDIO_REBOOT_MODID_START 0x84000020
#define RDR_AUDIO_NOC_MODID          0x84000021
#define RDR_AUDIO_REBOOT_MODID_END   0x8400002F

#define RDR_AUDIO_MODID_END          HISI_BB_MOD_HIFI_END

#define RDR_MODEM_CP_MOD_ID             0x82000001
#define RDR_MODEM_CP_RESET_3RD_MOD_ID   0x82000008

int rdr_audio_write_file(char *name, char *data, u32 size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

