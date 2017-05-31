/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: boot_fail_recovery.h

    @brief: header file of module-"boot fail recovery".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

#ifndef BOOT_FAIL_RECOVERY_H
#define BOOT_FAIL_RECOVERY_H


/*----includes-----------------------------------------------------------------------*/


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/

typedef enum failure_recovery_method
{
    FRM_DO_NOTHING = 0, //无操作
    FRM_REBOOT, //整机复位
    FRM_GOTO_B_SYSTEM, //启动B系统
    FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF, //因为普通不开机原因进入eRecovery删除文件
    FRM_GOTO_ERECOVERY_DEL_FILES_FOR_NOSPC, //因为data分区满而进入eRecovery删除文件
    FRM_GOTO_ERECOVERY_FACTORY_RESET, //执行恢复出厂设置
    FRM_GOTO_ERECOVERY_FORMAT_DATA_PART, //直接格式化，因为挂载data分区会panic
    FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY, //进入eRecovery下载升级包恢复
    FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_DEL_FILES, //进入eRecovery下载升级包恢复并删除文件
    FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET, //进入eRecovery下载升级包恢复并恢复出厂设置
    FRM_NOTIFY_USER_RECOVERY_FAILURE, //在fastboot 阶段提示用户恢复失败
    FRM_GOTO_ERECOVERY_LOWLEVEL_FORMAT_DATA,
    FRM_MAX_COUNT
} failure_recovery_method_e;

/*
* suggested recovery method to recovery system while meet with BFI error.
* NO_SUGGESTION - let recovery system determin the recovery method.
* DO_NOTHING - suggest recovery system to do nothing.
* moved here from hwboot_fail_public_interface.h by qidechun 2016-05-05
*/
typedef enum SUGGESTED_RECOVERY_METHOD
{
    /*
    * 如果故障检测子系统不知道对故障如何处理，
    * 恢复子系统按照预设的恢复策略和故障记录
    * 选择合适的恢复方法
    */
    NO_SUGGESTION = 0x0,
    DO_NOTHING = 0x1,
} suggested_recovery_method_e;

typedef struct fixed_recovery_method_param
{
    int enable_this_method; /* 0 - disable; 1 - enable */
    failure_recovery_method_e recovery_method;
} fixed_recovery_method_param_t;

typedef struct failure_recovery_policy
{
    int boot_fail_no; //不开机原因码

    /*
    * errno标志的故障拥有固定的恢复策略，
    * 即当此种故障出现时直接调用既定的恢复策略，
    * 而不必考虑以前的恢复记录。
    * 0-没有既定恢复，1-由既定恢复方法。
    */
    int has_fixed_policy;
    fixed_recovery_method_param_t param[4]; //针对errno预设的恢复方法
} failure_recovery_policy_e;


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

failure_recovery_method_e try_to_recovery(
    unsigned long long boot_fail_detected_time,
    unsigned int boot_fail_no,
    unsigned int boot_fail_stage,
    suggested_recovery_method_e suggested_recovery_method,
    char *args);

/* 0 - failed; 1 - success, this will be called by monitor for APP in kernel */
void boot_status_notify(int is_success);

#ifdef __cplusplus
}
#endif
#endif /* BOOT_FAIL_RECOVERY_H */

