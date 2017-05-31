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

/* ��Ҫ�����eRecovery��ִ��״̬ */
typedef enum recovery_method_running_status_code
{
    RMRSC_EXEC_COMPLETED = 0, //�������ָ�����ִ�гɹ�
    RMRSC_ERECOVERY_BOOT_FAILED = 1,//�ָ�ϵͳ����ʧ��
    RMRSC_ERECOVERY_BOOT_SUCCESS,//�ָ�ϵͳ�����ɹ�
    RMRSC_ERECOVERY_START_DEL_FILES,//��ʼɾ���ļ�
    RMRSC_ERECOVERY_DEL_FILES_SUCCESS,//ɾ���ļ��ɹ��������ļ��У�
    RMRSC_ERECOVERY_DEL_FILES_FAILED,//ɾ���ļ�ʧ�ܣ������ļ��У�
    RMRSC_ERECOVERY_START_WIFI,//��ʼ����WIFI����
    RMRSC_ERECOVERY_START_WIFI_SUCCESS,//����WIFI�ɹ�
    RMRSC_ERECOVERY_START_WIFI_FAILED, //����WIFIʧ��
    RMRSC_ERECOVERY_SATRT_QUERY_PACKAGES,//��ʼ��ѯ������
    RMRSC_ERECOVERY_QUERY_PACKAGES_SUCCESS,//��ѯ�������ɹ�
    RMRSC_ERECOVERY_QUERY_PACKAGES_FAILED,//��ѯ������ʧ��
    RMRSC_ERECOVERY_START_DOWNLOAD_PACKAGES,//��ʼ����������
    RMRSC_ERECOVERY_DOWNLOAD_PACKAGES_SUCCESS,//�����������ɹ�
    RMRSC_ERECOVERY_DOWNLOAD_PACKAGES_FAILED,//����������ʧ��
    RMRSC_ERECOVERY_START_DOWNLOAD_UPDATE_AUTH_FILES,//��ʼ���ؼ�Ȩ�ļ�
    RMRSC_ERECOVERY_DOWNLOAD_UPDATE_AUTH_FILES_SUCCESS,//���ؼ�Ȩ�ļ��ɹ�
    RMRSC_ERECOVERY_DOWNLOAD_UPDATE_AUTH_FILES_FAILED,//���ؼ�Ȩ�ļ�ʧ��
    RMRSC_ERECOVERY_START_INSTALL_PACKAGES, //��ʼ��װ�ļ�
    RMRSC_ERECOVERY_INSTALL_PACKAGES_SUCCESS, //��װ�������ɹ�
    RMRSC_ERECOVERY_INSTALL_PACKAGES_FAILED, //��װ������ʧ��
} recovery_method_running_status_code_e;

typedef enum recovery_method_run_result
{
    RMRR_SUCCESS = 0, //�ָ�����ִ�гɹ�
    RMRR_FAILED, //�ָ�����ִ�гɹ�
} recovery_method_run_result_e;

typedef enum boot_fail_recovery_result
{
    BOOT_FAIL_RECOVERY_SUCCESS = ((unsigned int)0xA5A5A5A5), //���������ϻָ��ɹ�
    BOOT_FAIL_RECOVERY_FAILURE = ((unsigned int)0x5A5A5A5A), //���������ϻָ�ʧ��
} boot_fail_recovery_result_e;

/* �ָ���¼��ͷ����Ϣ */
typedef struct failure_recovery_record_header
{
    unsigned int crc32;
    unsigned int magic_number; //ħ��
    int boot_fail_count; //�������ܴ���
    int last_record_idx; //���һ����¼�ı�ţ���Ŵ�0��ʼ
    int next_record_idx; //��һ����¼�ı�ţ���Ŵ�0��ʼ
    int record_count; //�÷����ܹ������ļ�¼����
    char reserved[104]; //�����ֶ�
} failure_recovery_record_header_t;

/* ÿ���ָ���¼�ĸ�ʽ */
typedef struct failure_recovery_record
{
    unsigned long long boot_fail_detected_time; //���ϱ���⵽��ʱ�䣨�룩
    unsigned int boot_fail_stage;  //���������Ϸ����Ľ׶�
    unsigned int boot_fail_no; //����������ԭ��
    unsigned int recovery_method; //�ָ���ϵͳѡ���Ĺ��ϻָ�����
    recovery_method_running_status_code_e running_status_code; //���ϻָ�����ִ�д�����
    recovery_method_run_result_e method_run_result; //���ϻָ�����ִ�н��
    boot_fail_recovery_result_e recovery_result; //���ϻָ����
    char reserved[96]; //�����ֶ�
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

