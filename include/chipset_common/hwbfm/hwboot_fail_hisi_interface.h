/*
 * BFM for handling the boot fail exceptions during the entire process of system boot.
 *
 * Copyright (c) 2016 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 @brief: this is the public interface for definiation of type struct and common interface of BFM.
 */

#ifndef __BFM_HISI_PUBLIC_INTERFACE_H__
#define __BFM_HISI_PUBLIC_INTERFACE_H__
#include "hwboot_fail_public_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/*----locall defination for BFI parition implementation--------------------------------------*/
#define PART_BFI "bootfail_info"
#define PART_BFI_TEMP PART_HISITEST0
#define BFI_MAGIC_NUMBER 0x42464958 //BFIX
#define ONE_BLOCK_SIZE 4*1024
#define BFI_HEAD_SIZE ONE_BLOCK_SIZE
#define BFI_RECOVERY_LOG_TOTAL_NUMBER 20

struct bfi_head_info {
	u32 magic;
	u32 total_number;
	u32 cur_number;
	u32 every_number_size;
};

struct bfi_every_number_Info{
	u64 rtcValue;
       u32 bfmErrNo;
       u32 bfmStageCode;
       u32 isSystemRooted;
       u32 isUserPerceptiable;
	u32 rcvMethod;
	u32 rcvResult;
};

/*----local defination for BFMtoMntn boot_stage no map implementation--------------------------------------*/
struct bfmToMntnStageNo
{
    enum BFM_BOOT_STAGE_CODE bfmStageCode;
    u32 mntnStageNo;
};

/*----local defination for BFMtoMntn mod ID map implementation--------------------------------------*/
struct bfmToMntnModID
{
	enum BFM_ERRNO_CODE bfmErrNo;
	u32 mntnModID;
};

/*----local defination for BFMtoMntn reboot reason map implementation--------------------------------------*/
struct bfmToMntnRebootReason
{
	enum BFM_ERRNO_CODE bfmErrNo;
	u32 mntnRebootReason;
};

typedef enum {
	MODID_BFM_START            = HISI_BB_MOD_BFM_START,
	MODID_BFM_BOOT_TIMEOUT,
	MODID_BFM_NATIVE_START,
	MODID_BFM_NATIVE_SECURITY_FAIL,
	MODID_BFM_NATIVE_CRITICAL_SERVICE_FAIL_TO_START,
	MODID_BFM_NATIVE_END,
	MODID_BFM_NATIVE_DATA_START,
	MODID_BFM_NATIVE_SYS_MOUNT_FAIL,
	MODID_BFM_NATIVE_DATA_MOUNT_FAILED_AND_ERASED,
	MODID_BFM_NATIVE_DATA_MOUNT_RO, /* added by qidechun */
	MODID_BFM_NATIVE_DATA_NOSPC, /* added by qidechun, NOSPC means data partition is full */
	MODID_BFM_NATIVE_VENDOR_MOUNT_FAIL,
	MODID_BFM_NATIVE_DATA_END,
	MODID_BFM_FRAMEWORK_LEVEL_START,
	MODID_BFM_FRAMEWORK_SYS_SERVICE_LOAD_FAIL,
	MODID_BFM_FRAMEWORK_PREBOOT_BROADCAST_FAIL,
	MODID_BFM_FRAMEWORK_VM_OAT_FILE_DAMAGED,
	MODID_BFM_FRAMEWORK_LEVEL_END,
	MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED,
	MODID_BFM_END              = HISI_BB_MOD_BFM_END
} modid_hwbfm;

//unsigned int get_bfm_to_mntn_map_stagecode_size();
u32 bfm_to_mntn_stagecode(enum BFM_BOOT_STAGE_CODE stageCode);
enum BFM_BOOT_STAGE_CODE mntn_to_bfm_stagecode(u32 stageNo);
//unsigned int get_bfm_to_mntn_modid_map_size();
u32 bfm_to_mntn_modid(enum BFM_ERRNO_CODE bootErrNo);
enum BFM_ERRNO_CODE mntn_modid_to_bfm_errno(u32 modID);


u32 bfm_to_mntn_reboot_reason(enum BFM_ERRNO_CODE bootErrNo);

enum BFM_ERRNO_CODE mntn_reboot_reason_to_bfm_errno(u32 mntnRBReason);

#ifdef __cplusplus
}
#endif

#endif //__BFM_HISI_PUBLIC_INTERFACE_H__
