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

#ifndef __BFM_PUBLIC_INTERFACE_H__
#define __BFM_PUBLIC_INTERFACE_H__

#include "hwbfr/boot_fail_recovery.h"

#ifdef __cplusplus
extern "C"{
#endif

enum PLATFORM_CODE{
    COMMON_PLATFORM = 0,
    HISI_PLATFORM,
    QUALCOMM_PLATFORM,
};
enum STAGE_CODE{
    PBL_STAGE = 0,
    BL1_STAGE,        /* BL1 -- bootloader stage 1, it's xloader for hisi, sbl1 for qualcomm*/
    BL2_STAGE,        /* BL2 -- bootloader stage 2, it's fastboot for hisi, lk for qualcomm*/
    KERNEL_STAGE,
    NATIVE_STAGE,
    ANDROID_FRAMEWORK_STAGE,
};

#define isBL1Errno(x) ((x & (0xFF <<24)) ==  (BL1_STAGE <<24))
#define isBL2Errno(x) ((x & (0xFF <<24)) ==  (BL2_STAGE <<24))
#define isKernelErrno(x) ((x & (0xFF <<24)) ==  (KERNEL_STAGE <<24))
#define isNativeErrno(x) ((x & (0xFF <<24)) ==  (NATIVE_STAGE <<24))
#define isAndroidFrameworkErrno(x) ((x & (0xFF <<24)) ==  (ANDROID_FRAMEWORK_STAGE <<24))

#define BOOT_COMMAND_BOOT_STAGE 0x00000001
#define BOOT_COMMAND_TRIGGER_ERROR 0x00000002
#define BOOT_COMMAND_SET_TIMER 0x00000003
#define BOOT_COMMAND_SET_TIMEROUT 0x00000004

#define BOOT_COMMAND_VALUE_SET_TIMER_ENABLE 0x00000001
#define BOOT_COMMAND_VALUE_SET_TIMER_DISABLE 0x00000000
#define BOOT_COMMAND_LEN 11
#define BOOT_TIMER_INTERVAL (10000)
#define BOOT_TOO_LONG_TIME (1000*60*30)
#define BOOT_TOO_LONG_TIME_EXACT (1000*60*30)
#define BFM_STAGE_CODE 0x00000001
#define BFM_ERROR_CODE 0x00000002
#define BFM_TIMER_EN_CODE 0x00000003
#define BFM_TIMER_SET_CODE 0x00000004



/*
* coding of boot fail error during entire boot process
*/
enum BFM_ERRNO_CODE {
    BL1_ERRNO_START = (BL1_STAGE <<24)|(COMMON_PLATFORM<<16),  /* BL1 -- bootloader stage 1, it's xloader for hisi, sbl1 for qualcomm*/
    BL1_DDR_INIT_FAIL,
    BL1_EMMC_INIT_FAIL,
    BL1_BL2_LOAD_FAIL,
    BL1_BL2_VERIFY_FAIL,
    BL1_WDT,

    BL1_PL1_START = (BL1_STAGE <<24)|(HISI_PLATFORM<<16), /* PL1 -- Platform 1 -- it's only for hisi */
    BL1_VRL_LOAD_FAIL,
    BL1_VRL_VERIFY_FAIL,

    BL1_PL2_START = (BL1_STAGE <<24)|(QUALCOMM_PLATFORM<<16), /* PL2 -- Platform 2 -- it's only for qualcomm */
    BL1_ERROR_GROUP_BOOT,
    BL1_ERROR_GROUP_BUSES,
    BL1_ERROR_GROUP_BAM,
    BL1_ERROR_GROUP_BUSYWAIT,
    BL1_ERROR_GROUP_CLK,
    BL1_ERROR_GROUP_CRYPTO,
    BL1_ERROR_GROUP_DAL,
    BL1_ERROR_GROUP_DEVPROG,
    BL1_ERROR_GROUP_DEVPROG_DDR,
    BL1_ERROR_GROUP_EFS,
    BL1_ERROR_GROUP_EFS_LITE,
    /*BL1_ERROR_GROUP_FLASH; --- move to common errno*/
    BL1_ERROR_GROUP_HOTPLUG,
    BL1_ERROR_GROUP_HSUSB,
    BL1_ERROR_GROUP_ICB,
    BL1_ERROR_GROUP_LIMITS,
    BL1_ERROR_GROUP_MHI,
    BL1_ERROR_GROUP_PCIE,
    BL1_ERROR_GROUP_PLATFOM,
    BL1_ERROR_GROUP_PMIC,
    BL1_ERROR_GROUP_POWER,
    BL1_ERROR_GROUP_PRNG,
    BL1_ERROR_GROUP_QUSB,
    BL1_ERROR_GROUP_SECIMG,
    BL1_ERROR_GROUP_SECBOOT,
    BL1_ERROR_GROUP_SECCFG,
    BL1_ERROR_GROUP_SMEM,
    BL1_ERROR_GROUP_SPMI,
    BL1_ERROR_GROUP_SUBSYS,
    BL1_ERROR_GROUP_TLMM,
    BL1_ERROR_GROUP_TSENS,
    BL1_ERROR_GROUP_HWENGINES,
    BL1_ERROR_GROUP_IMAGE_VERSION,
    BL1_ERROR_GROUP_SECURITY,
    BL1_ERROR_GROUP_STORAGE,
    BL1_ERROR_GROUP_SYSTEMDRIVERS,
    /*1_ERROR_GROUP_DDR, --- move to common errno*/
    BL1_ERROR_GROUP_EXCEPTIONS,
    BL1_ERROR_GROUP_MPROC,

    BL2_ERRNO_START = (BL2_STAGE <<24)|(COMMON_PLATFORM<<16),  /* BL2 -- bootloader stage 2, it's fastboot for hisi, lk for qualcomm*/
    BL2_EMMC_INIT_FAIL,
    BL2_PANIC,
    BL2_WDT,

    BL2_PL1_START = (BL2_STAGE <<24)|(HISI_PLATFORM<<16), /* PL1 -- Platform 1 -- it's only for hisi */
    BL2_PL1_OCV_ERROR,
    BL2_PL1_BAT_TEMP_ERROR,
    BL2_PL1_MISC_ERROR,
    BL2_PL1_DTIMG_ERROR,
    BL2_PL1_LOAD_OTHER_IMGS_ERRNO,
    BL2_PL1_KERNEL_IMG_ERROR,

    BL2_PL2_START = (BL2_STAGE <<24)|(QUALCOMM_PLATFORM<<16), /* PL2 -- Platform 2 -- it's only for qualcomm */
    BL2_MMC_INIT_FAILED,
    BL2_QSEECOM_START_ERROR,
    BL2_RPMB_INIT_FAILED,
    BL2_LOAD_SECAPP_FAILED,
    BL2_ABOOT_DLKEY_DETECTED,
    BL2_ABOOT_NORMAL_BOOT_FAIL,

    KERNEL_ERRNO_START = (KERNEL_STAGE <<24)|(COMMON_PLATFORM<<16),  /* kernel stage's bootFail errors */
    KERNEL_AP_PANIC,
    KERNEL_EMMC_INIT_FAIL,
    KERNEL_AP_WDT,
    KERNEL_PRESS10S,
    KERNEL_BOOT_TIMEOUT,
    KERNEL_AP_COMBINATIONKEY,

    KERNEL_PL1_START = (KERNEL_STAGE <<24)|(HISI_PLATFORM<<16),
    KERNEL_AP_S_ABNORMAL,
    KERNEL_AP_S_TSENSOR0,
    KERNEL_AP_S_TSENSOR1,
    KERNEL_LPM3_S_GLOBALWDT,
    KERNEL_G3D_S_G3DTSENSOR,
    KERNEL_LPM3_S_LPMCURST,
    KERNEL_CP_S_CPTSENSOR,
    KERNEL_IOM3_S_IOMCURST,
    KERNEL_ASP_S_ASPWD,
    KERNEL_CP_S_CPWD,
    KERNEL_IVP_S_IVPWD,
    KERNEL_ISP_S_ISPWD,
    KERNEL_AP_S_DDR_UCE_WD,
    KERNEL_AP_S_DDR_FATAL_INTER,
    KERNEL_AP_S_DDR_SEC,
    KERNEL_AP_S_MAILBOX,
    KERNEL_CP_S_MODEMDMSS,
    KERNEL_CP_S_MODEMNOC,
    KERNEL_CP_S_MODEMAP,
    KERNEL_CP_S_EXCEPTION,
    KERNEL_CP_S_RESETFAIL,
    KERNEL_CP_S_NORMALRESET,
    KERNEL_CP_S_ABNORMAL,
    KERNEL_LPM3_S_EXCEPTION,
    KERNEL_HIFI_S_EXCEPTION,
    KERNEL_HIFI_S_RESETFAIL,
    KERNEL_ISP_S_EXCEPTION,
    KERNEL_IVP_S_EXCEPTION,
    KERNEL_IOM3_S_EXCEPTION,
    KERNEL_TEE_S_EXCEPTION,
    KERNEL_MMC_S_EXCEPTION,
    KERNEL_CODECHIFI_S_EXCEPTION,
    KERNEL_CP_S_RILD_EXCEPTION,
    KERNEL_CP_S_3RD_EXCEPTION,
    KERNEL_IOM3_S_USER_EXCEPTION,

    KERNEL_PL2_START = (KERNEL_STAGE <<24)|(QUALCOMM_PLATFORM<<16),
    KERNEL_MODEM_PANIC,
    KERNEL_VENUS_PANIC,
    KERNEL_WCNSS_PANIC,
    KERNEL_SENSOR_PANIC,

    NATIVE_ERRNO_START = (NATIVE_STAGE <<24)|(COMMON_PLATFORM<<16),  /* natvie stage's bootFail errors */
    SYSTEM_MOUNT_FAIL,
    SECURITY_FAIL,
    CRITICAL_SERVICE_FAIL_TO_START,
    DATA_MOUNT_FAILED_AND_ERASED,
    DATA_MOUNT_RO, /* added by qidechun */
    DATA_NOSPC, /* added by qidechun, NOSPC means data partition is full */
    VENDOR_MOUNT_FAIL,

    ANDROID_FRAMEWORK_ERRNO_START = (ANDROID_FRAMEWORK_STAGE <<24)|(COMMON_PLATFORM<<16),  /* android frameworkl stage's bootFail errors */
    SYSTEM_SERVICE_LOAD_FAIL,
    PREBOOT_BROADCAST_FAIL,
    VM_OAT_FILE_DAMAGED,
    PACKAGE_MANAGER_SETTING_FILE_DAMAGED,

    BFM_ERRNO_MAX_COUNT,
};

#define isBootSuccess(x) (x == STAGE_BOOT_SUCCESS)
#define isBL1Stage(x) ((x & (0xFF <<24) ==  (BL1_STAGE <<24)) && ! isBootSuccess(x))
#define isBL2Stage(x) ((x & (0xFF <<24)) ==  (BL2_STAGE <<24))
#define isKernelStage(x) ((x & (0xFF <<24)) ==  (KERNEL_STAGE <<24))
#define isNativeStage(x) ((x & (0xFF <<24)) ==  (NATIVE_STAGE <<24))
#define isAndroidFrameworkStage(x) ((x & (0xFF <<24)) ==  (ANDROID_FRAMEWORK_STAGE <<24))

/*
* coding of boot stage during entire boot process
*/
enum BFM_BOOT_STAGE_CODE {
    BL1_STAGE_START = ((BL1_STAGE <<24)|(COMMON_PLATFORM<<16)) + 0x1, /* BL1 -- bootloader stage 1, it's xloader for hisi, sbl1 for qualcomm*/
    BL1_STAGE_DDR_INIT_START,
    BL1_STAGE_EMMC_INIT_START,
    BL1_STAGE_BL2_LOAD_START,
    BL1_STAGE_END,

    BL1_PL1_STAGE_START = (BL1_STAGE <<24)|(HISI_PLATFORM<<16),
    BL1_PL1_STAGE_DDR_INIT_FAIL,
    BL1_PL1_STAGE_DDR_INIT_OK,
    BL1_PL1_STAGE_EMMC_INIT_FAIL,
    BL1_PL1_STAGE_EMMC_INIT_OK,

    BL1_PL1_STAGE_RD_VRL_FAIL,
    BL1_PL1_STAGE_CHECK_VRL_ERROR,
    BL1_PL1_STAGE_IMG_TOO_LARGE,
    BL1_PL1_STAGE_READ_FASTBOOT_FAIL,
    BL1_PL1_STAGE_LOAD_HIBENCH_FAIL,
    BL1_PL1_STAGE_SEC_VERIFY_FAIL,
    BL1_PL1_STAGE_GET_FASTBOOTSIZE_FAIL,
    BL1_PL1_STAGE_FASTBOOTSIZE_ERROR,
    BL1_PL1_STAGE_VRL_CHECK_ERROR,
    BL1_PL1_SECURE_VERIFY_ERROR,

    BL1_PL2_STAGE_START = (BL1_STAGE <<24)|(QUALCOMM_PLATFORM<<16),
    BL1_PL2_STAGE_AUTH_QSEE,
    BL1_PL2_STAGE_AUTH_DEVCFG,
    BL1_PL2_STAGE_AUTH_DBG_POLICY,
    BL1_PL2_STAGE_AUTH_RPM_FW,
    BL1_PL2_STAGE_AUTH_APP_SBL,

    BL2_STAGE_START = ((BL2_STAGE <<24)|(COMMON_PLATFORM<<16)), /* BL2 -- bootloader stage 2, it's fastboot for hisi, lk for qualcomm*/
    BL2_STAGE_EMMC_INIT_START,
    BL2_STAGE_EMMC_INIT_FAIL,
    BL2_STAGE_EMMC_INIT_OK,
    BL2_STAGE_END,

    BL2_PL1_STAGE_START = (BL2_STAGE <<24)|(HISI_PLATFORM<<16),
    BL2_PL1_STAGE_DDR_INIT_START,
    BL2_PL1_STAGE_DISPLAY_INIT_START,
    BL2_PL1_STAGE_PRE_BOOT_INIT_START,
    BL2_PL1_STAGE_LD_OTHER_IMGS_START,
    BL2_PL1_STAGE_LD_KERNEL_IMG_START,
    BL2_PL1_STAGE_BOOT_KERNEL_START,

    BL2_PL2_STAGE_START = (BL2_STAGE <<24)|(QUALCOMM_PLATFORM<<16),
    BL2_PL2_STAGE_PLATFORM_INIT,
    BL2_PL2_STAGE_TARGET_INIT,
    BL2_PL2_STAGE_APPS_START,
    BL2_PL2_STAGE_APPS_ABOOT_START,
    BL2_PL2_STAGE_APPS_ABOOT_CHECK_BOOT,
    BL2_PL2_STAGE_APPS_ABOOT_CHECK_DDRSCREEN,
    BL2_PL2_STAGE_APPS_ABOOT_FASTBOOT,

    KERNEL_STAGE_START = (KERNEL_STAGE <<24)|(COMMON_PLATFORM<<16), /* kernel stage */
    KERNEL_EARLY_INITCALL,
    KERNEL_PURE_INITCALL,
    KERNEL_CORE_INITCALL_SYNC,
    KERNEL_POSTCORE_INITCALL,
    KERNEL_POSTCORE_INITCALL_SYNC,
    KERNEL_ARCH_INITCALL,
    KERNEL_ARCH_INITCALLC,
    KERNEL_SUBSYS_INITCALL,
    KERNEL_SUBSYS_INITCALL_SYNC,
    KERNEL_FS_INITCALL,
    KERNEL_FS_INITCALL_SYNC,
    KERNEL_ROOTFS_INITCALL,
    KERNEL_DEVICE_INITCALL,
    KERNEL_DEVICE_INITCALL_SYNC,
    KERNEL_LATE_INITCALL,
    KERNEL_LATE_INITCALL_SYNC,
    KERNEL_CONSOLE_INITCALL,
    KERNEL_SECURITY_INITCALL,
    KERNEL_BOOTANIM_COMPLETE,

    NATIVE_STAGE_START = (NATIVE_STAGE <<24)|(COMMON_PLATFORM<<16), /* native stage */
    STAGE_INIT_START,
    STAGE_ON_EARLY_INIT,
    STAGE_ON_INIT,
    STAGE_ON_EARLY_FS,
    STAGE_ON_FS,
    STAGE_ON_POST_FS,
    STAGE_ON_POST_FS_DATA,
    STAGE_ON_EARLY_BOOT,
    STAGE_ON_BOOT,

    ANDROID_FRAMEWORK_STAGE_START = (ANDROID_FRAMEWORK_STAGE <<24)|(COMMON_PLATFORM<<16), /* android framework start stage */
    STAGE_ZYGOTE_START,
    STAGE_VM_START,
    STAGE_PHASE_WAIT_FOR_DEFAULT_DISPLAY,
    STAGE_PHASE_LOCK_SETTINGS_READY,
    STAGE_PHASE_SYSTEM_SERVICES_READY,
    STAGE_PHASE_ACTIVITY_MANAGER_READY,
    STAGE_PHASE_THIRD_PARTY_APPS_CAN_START,

    STAGE_BOOT_SUCCESS = 0x7FFFFFFF,
};
#define MAX_LOGPATH 1024

/************************************************************
Function:      boot_fail_err
Description:   to save the log and do proper recovery actions,
                    while meet with error during system booting process.
Input:          bootErrNo:   boot fail errorNo.
                   sugRcvMtd:  suggested recovery method.
                   logFilePath:  path of logFile, if an additional log file existed
                                      and need to be saved.
Output:         NA
Return:        0 -- SUCCESS/OK
                   1 -- FAIL/ERROR
*************************************************************/
int boot_fail_err(enum BFM_ERRNO_CODE bootErrNo, enum SUGGESTED_RECOVERY_METHOD sugRcvMtd/* = NO_SUGGESTION*/, char * logFilePath/* = 0*/);

/************************************************************
Function:      get_boot_stage
Description:   get current boot stage during boot process
Input:          pBootStageValue:   address of returned boot stage value
Output:         boot stage value to be saved into pBootStageValue if valid
Return:        0 -- SUCCESS/OK
                   1 -- FAIL/ERROR
*************************************************************/
int get_boot_stage(enum BFM_BOOT_STAGE_CODE *pBootStageValue);

/************************************************************
Function:      set_boot_stage
Description:   set boot stage as input value
Input:          bootStageValue:   boot stage value to be set
Output:        N/A
Return:        0 -- SUCCESS/OK
                   1 -- FAIL/ERROR
*************************************************************/
int set_boot_stage(enum BFM_BOOT_STAGE_CODE bootStageValue);

int boot_timer_init(void);
void boot_timer_get(u32 *bt_value_ptr);
void boot_timer_set(u32 bt_value);
void boot_timer_get_enable(bool *enable);
void boot_timer_set_enable(bool enable);
void boot_timer_stop(void);
void bfmr_set_boot_fail_errno(unsigned int boot_fail_errno);
unsigned int bfmr_get_boot_fail_errno(void);
void bfmr_set_user_space_log_path(char *log_path);
char *bfmr_get_user_space_log_path(void);

#ifdef __cplusplus
}
#endif

#endif //__BFM_PUBLIC_INTERFACE_H__
