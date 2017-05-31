/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: enter_erecovery_reason.h

    @brief: header file of module-"enter erecovery reason".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

#ifndef ENTER_ERECOVERY_REASON_H
#define ENTER_ERECOVERY_REASON_H


/*----includes-----------------------------------------------------------------------*/


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

#define ENTER_ERECOVERY_BY_PRESS_KEY (2001)
#define ENTER_ERECOVERY_BY_ADB_CMD (2002)
#define ENTER_ERECOVERY_BECAUSE_UNLOCK (2004)
#define ENTER_ERECOVERY_BECAUSE_SYSTEM_DAMAGED (2005)
#define ENTER_ERECOVERY_BECAUSE_HUAWEI_VERIFY_FAILED (2006)
#define ENTER_ERECOVERY_BECAUSE_HUAWEI_GOOGLE_VERIFY_FAILED (2007)
#define ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL (2008)
#define ENTER_ERECOVERY_REASON_BECAUSE_KERNEL_BOOT_FAIL (2009)
#define ENTER_ERECOVERY_BECAUSE_SYSTEM_MOUNT_FAILED (2010)
#define ENTER_ERECOVERY_BECAUSE_DATA_MOUNT_FAILED (2011)
#define ENTER_ERECOVERY_BECAUSE_DATA_MOUNT_RO (2012)
#define ENTER_ERECOVERY_BECAUSE_KEY_PROCESS_START_FAILED (2013)
#define ENTER_ERECOVERY_BECAUSE_RECOVERY_PROCESS_CRASH (2014)
#define ENTER_ERECOVERY_BECAUSE_AP_CRASH_REPEATEDLY (2015)
#define ENTER_ERECOVERY_BECAUSE_NON_AP_CRASH_REPEATEDLY (2016)
#define ENTER_ERECOVERY_BECAUSE_APP_BOOT_FAIL (2017)
#define ENTER_ERECOVERY_BECAUSE_SECURITY_FAIL (2018)
#define ENTER_ERECOVERY_BECAUSE_VENDOR_MOUNT_FAILED (2019)
#define ENTER_ERECOVERY_BECAUSE_CUST_MOUNT_FAILED (2020)
#define ENTER_ERECOVERY_BECAUSE_PRODUCT_MOUNT_FAILED (2021)
#define ENTER_ERECOVERY_BECAUSE_VERSION_MOUNT_FAILED (2022)
#define ENTER_ERECOVERY_UNKNOWN (2099)
#define ENTER_ERECOVEYR_COMMAND "boot-erecovery"


/*----export prototypes---------------------------------------------------------------*/

typedef enum enter_erecovery_reason
{
    EER_BOOT_FAIL_SOLUTION = 0, //因为不开机检测方案进入eRecovery
    EER_PRESS_VOLUMEUP_KEY, //因为用户开机时长按音量上键进入eRecovery，前提是手机在开机前已经置于充电状态或者连接到了开机的电脑
    EER_VERIFY_BOOT, //因为用户在bootloader阶段的verifyboot提示界面长按音量上键3秒进入eRecovery
    EER_MAX_COUNT, //进入eRecovery的原因总数
} enter_erecovery_reason_e;

typedef enum boot_fail_stage
{
    BFS_BOOTLOADER = 0, //不开机故障发生在bootloader阶段
    BFS_KERNEL, //不开机故障发生在kernelr阶段
    BFS_APP, //不开机故障发生在应用程序启动阶段
} boot_fail_stage_e;

typedef struct enter_erecovery_reason_param
{
    char command[32]; //进入eRecovery的命令"boot-erecovery"
    enter_erecovery_reason_e enter_erecovery_reason; //进入eRecovery的大类原因
    int enter_erecovery_reason_number; //eRecovery将把该字段上传到BI服务器，兼容老的BI上报方案
    boot_fail_stage_e boot_fail_stage_for_erecovery; //不开机阶段码
    unsigned int boot_fail_no; //不开机方案检测到原因
    unsigned int recovery_method; //不开机的恢复方法（主要针对应用不开机）
    char reserved[972]; //保留字段
} enter_erecovery_reason_param_t;

typedef struct boot_fail_no_range
{
    unsigned int start;
    unsigned int end;
} boot_fail_no_range_t;

typedef struct enter_erecovery_reason_pair
{
    boot_fail_no_range_t range;
    unsigned int enter_erecovery_reason; // this will be used by erecovery to communicate with BI server
} boot_fail_enter_erecovery_reason_map_t;


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

int save_enter_erecovery_reason(enter_erecovery_reason_param_t *reason_param);
int read_enter_erecovery_reason(enter_erecovery_reason_param_t *reason_param);

#ifdef __cplusplus
}
#endif
#endif /* ENTER_ERECOVERY_REASON_H */

