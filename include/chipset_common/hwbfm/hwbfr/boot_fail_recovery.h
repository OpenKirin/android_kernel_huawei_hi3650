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
    FRM_DO_NOTHING = 0, //�޲���
    FRM_REBOOT, //������λ
    FRM_GOTO_B_SYSTEM, //����Bϵͳ
    FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF, //��Ϊ��ͨ������ԭ�����eRecoveryɾ���ļ�
    FRM_GOTO_ERECOVERY_DEL_FILES_FOR_NOSPC, //��Ϊdata������������eRecoveryɾ���ļ�
    FRM_GOTO_ERECOVERY_FACTORY_RESET, //ִ�лָ���������
    FRM_GOTO_ERECOVERY_FORMAT_DATA_PART, //ֱ�Ӹ�ʽ������Ϊ����data������panic
    FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY, //����eRecovery�����������ָ�
    FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_DEL_FILES, //����eRecovery�����������ָ���ɾ���ļ�
    FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET, //����eRecovery�����������ָ����ָ���������
    FRM_NOTIFY_USER_RECOVERY_FAILURE, //��fastboot �׶���ʾ�û��ָ�ʧ��
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
    * ������ϼ����ϵͳ��֪���Թ�����δ���
    * �ָ���ϵͳ����Ԥ��Ļָ����Ժ͹��ϼ�¼
    * ѡ����ʵĻָ�����
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
    int boot_fail_no; //������ԭ����

    /*
    * errno��־�Ĺ���ӵ�й̶��Ļָ����ԣ�
    * �������ֹ��ϳ���ʱֱ�ӵ��üȶ��Ļָ����ԣ�
    * �����ؿ�����ǰ�Ļָ���¼��
    * 0-û�мȶ��ָ���1-�ɼȶ��ָ�������
    */
    int has_fixed_policy;
    fixed_recovery_method_param_t param[4]; //���errnoԤ��Ļָ�����
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

