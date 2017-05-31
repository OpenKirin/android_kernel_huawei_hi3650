/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: recovery_record.h

    @brief: header file of module-"recovery record".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

#ifndef RECOVERY_RECORD_H
#define RECOVERY_RECORD_H


/*----includes-----------------------------------------------------------------------*/

#include "enter_erecovery_reason.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

#define RECOVERY_RECORD_PART_NAME "rrecord"
#define RECOVERY_RECORD_PART_NAME_TEMP "reserved2"
#define RECOVERY_RECORD_FIRST_DEV_PATH "/dev/block/bootdevice/by-name/" RECOVERY_RECORD_PART_NAME
#define RECOVERY_RECORD_SECOND_DEV_PATH "/dev/block/bootdevice/by-name/" RECOVERY_RECORD_PART_NAME_TEMP
#define RECORD_PARTS_MAX_COUNT (2)

/* 0x72656364-'r' 'e' 'c' 'd' */
#define RECOVERY_RECORD_MAGIC_NUMBER ((unsigned int)0x72656364)

#define CRC32_TABLE_ELEMENT_COUNT (256)
#define CRC32_MULTINOMIAL_VALUE (0xedb88320)
#define ENTER_ERECOVERY_REASON_SIZE (sizeof(enter_erecovery_reason_param_t))
#define EACH_RECORD_PART_SIZE ((unsigned int)0x100000)
#define ENTER_ERECOVERY_REASON_OFFSET ((unsigned int)0x0)
#define RRECORD_FIRST_PART_OFFSET (ENTER_ERECOVERY_REASON_SIZE)
#define RRECORD_SECOND_PART_OFFSET (RRECORD_FIRST_PART_OFFSET + EACH_RECORD_PART_SIZE)
#define RRECORD_THIRD_PART_OFFSET (RRECORD_SECOND_PART_OFFSET + EACH_RECORD_PART_SIZE)


/*----export prototypes---------------------------------------------------------------*/

/* 主要是针对eRecovery的执行状态 */
typedef enum recovery_method_running_status_code
{
    RMRSC_EXEC_COMPLETED = 0, //不开机恢复方法执行成功
    RMRSC_ERECOVERY_BOOT_FAILED = 1,//恢复系统启动失败
    RMRSC_ERECOVERY_BOOT_SUCCESS,//恢复系统启动成功
    RMRSC_ERECOVERY_START_DEL_FILES,//开始删除文件
    RMRSC_ERECOVERY_DEL_FILES_SUCCESS,//删除文件成功（包括文件夹）
    RMRSC_ERECOVERY_DEL_FILES_FAILED,//删除文件失败（包括文件夹）
    RMRSC_ERECOVERY_START_WIFI,//开始启动WIFI链接
    RMRSC_ERECOVERY_START_WIFI_SUCCESS,//启动WIFI成功
    RMRSC_ERECOVERY_START_WIFI_FAILED, //启动WIFI失败
    RMRSC_ERECOVERY_SATRT_QUERY_PACKAGES,//开始查询升级包
    RMRSC_ERECOVERY_QUERY_PACKAGES_SUCCESS,//查询升级包成功
    RMRSC_ERECOVERY_QUERY_PACKAGES_FAILED,//查询升级包失败
    RMRSC_ERECOVERY_START_DOWNLOAD_PACKAGES,//开始下载升级包
    RMRSC_ERECOVERY_DOWNLOAD_PACKAGES_SUCCESS,//下载升级包成功
    RMRSC_ERECOVERY_DOWNLOAD_PACKAGES_FAILED,//下载升级包失败
    RMRSC_ERECOVERY_START_DOWNLOAD_UPDATE_AUTH_FILES,//开始下载鉴权文件
    RMRSC_ERECOVERY_DOWNLOAD_UPDATE_AUTH_FILES_SUCCESS,//下载鉴权文件成功
    RMRSC_ERECOVERY_DOWNLOAD_UPDATE_AUTH_FILES_FAILED,//下载鉴权文件失败
    RMRSC_ERECOVERY_START_INSTALL_PACKAGES, //开始安装文件
    RMRSC_ERECOVERY_INSTALL_PACKAGES_SUCCESS, //安装升级包成功
    RMRSC_ERECOVERY_INSTALL_PACKAGES_FAILED, //安装升级包失败
} recovery_method_running_status_code_e;

typedef enum recovery_method_run_result
{
    RMRR_SUCCESS = 0, //恢复策略执行成功
    RMRR_FAILED, //恢复策略执行成功
} recovery_method_run_result_e;

typedef enum boot_fail_recovery_result
{
    BOOT_FAIL_RECOVERY_SUCCESS = ((unsigned int)0xA5A5A5A5), //不开机故障恢复成功
    BOOT_FAIL_RECOVERY_FAILURE = ((unsigned int)0x5A5A5A5A), //不开机故障恢复失败
} boot_fail_recovery_result_e;

/* 恢复记录的头部信息 */
typedef struct failure_recovery_record_header
{
    unsigned int crc32;
    unsigned int magic_number; //魔数
    int boot_fail_count; //不开机总次数
    int last_record_idx; //最后一条记录的编号，编号从0开始
    int next_record_idx; //下一条记录的编号，编号从0开始
    int record_count; //该分区能够保留的记录总数
    char reserved[104]; //保留字段
} failure_recovery_record_header_t;

/* 每条恢复记录的格式 */
typedef struct failure_recovery_record
{
    unsigned long long boot_fail_detected_time; //故障被检测到的时间（秒）
    unsigned int boot_fail_stage;  //不开机故障发生的阶段
    unsigned int boot_fail_no; //不开机故障原因
    unsigned int recovery_method; //恢复子系统选定的故障恢复方法
    recovery_method_running_status_code_e running_status_code; //故障恢复策略执行错误码
    recovery_method_run_result_e method_run_result; //故障恢复方法执行结果
    boot_fail_recovery_result_e recovery_result; //故障恢复结果
    char reserved[96]; //保留字段
} failure_recovery_record_t;


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

int create_recovery_record(failure_recovery_record_t *precord);

/* this function need not be realized in bootloader, it should be realized in kernel and erecovery */
int renew_recovery_record(failure_recovery_record_t *precord);

/* in bootloader, this function should be called firstly */
int read_recovery_record(failure_recovery_record_t *precord,
    int record_count_to_read,
    int *record_count_actually_read);

#ifdef __cplusplus
}
#endif
#endif /* RECOVERY_RECORD_H */

