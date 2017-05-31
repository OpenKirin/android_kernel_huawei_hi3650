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
    EER_BOOT_FAIL_SOLUTION = 0, //��Ϊ��������ⷽ������eRecovery
    EER_PRESS_VOLUMEUP_KEY, //��Ϊ�û�����ʱ���������ϼ�����eRecovery��ǰ�����ֻ��ڿ���ǰ�Ѿ����ڳ��״̬�������ӵ��˿����ĵ���
    EER_VERIFY_BOOT, //��Ϊ�û���bootloader�׶ε�verifyboot��ʾ���泤�������ϼ�3�����eRecovery
    EER_MAX_COUNT, //����eRecovery��ԭ������
} enter_erecovery_reason_e;

typedef enum boot_fail_stage
{
    BFS_BOOTLOADER = 0, //���������Ϸ�����bootloader�׶�
    BFS_KERNEL, //���������Ϸ�����kernelr�׶�
    BFS_APP, //���������Ϸ�����Ӧ�ó��������׶�
} boot_fail_stage_e;

typedef struct enter_erecovery_reason_param
{
    char command[32]; //����eRecovery������"boot-erecovery"
    enter_erecovery_reason_e enter_erecovery_reason; //����eRecovery�Ĵ���ԭ��
    int enter_erecovery_reason_number; //eRecovery���Ѹ��ֶ��ϴ���BI�������������ϵ�BI�ϱ�����
    boot_fail_stage_e boot_fail_stage_for_erecovery; //�������׶���
    unsigned int boot_fail_no; //������������⵽ԭ��
    unsigned int recovery_method; //�������Ļָ���������Ҫ���Ӧ�ò�������
    char reserved[972]; //�����ֶ�
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

