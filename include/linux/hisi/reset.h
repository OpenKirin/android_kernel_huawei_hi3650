
#ifndef __MACH_RESET_H__
#define __MACH_RESET_H__

#include <linux/notifier.h>
#include <linux/semaphore.h>
#include "hifidrvinterface.h"
#include <linux/pstore_ram.h>

/*****************************************************************************
 �궨��
*****************************************************************************/
#define RESET_CPU_CCORE_STATUS_OFF            0x00000001
#define RESET_CPU_MCU_STATUS_OFF              0x00000002
#define RESET_CPU_HIFI_STATUS_OFF             0x00000004
/*CCORE OR hifi ������λ�ܿغ�*/
#define BSP_C_HIFI_RESET_ALONE_FEATURE
#undef RESET_PRINK_TO_FILE

/*�ú����ڿ��Ʋ��Դ���*/
#define BSP_C_HIFI_RESET_ALONE_TESET_VALID
#define BSP_RESET_MAILBOX_MSG_PROTECT           0x5a5a5a5a

/*CCORE OR hifi ������λ,CCORE������Ҫ��ȫУ��*/
#undef BSP_C_HIFI_RESET_ALONE_SEC_FEATURE

#define BSP_RESET_OK                    0
#define BSP_RESET_ERROR                 (-1)

#define DRV_RESET_MODULE_NAME_LEN       9/*exclude '\0'*/
/*reference to copy from bootloader, fastboot, starts*/
#define EFI_NAMELEN     36

/*һ����Ϣ����󳤶�*/
#define     BSP_RESET_LOG_INFO_ITEM_LEN     100
/*����log��Ϣ���ļ�*/
#define     BSP_RESET_LOG_FILE      "log/record/reset_sub.txt"

/*����ص��������ȼ�*/
#define     BSP_DRV_CBFUN_PRIOLEVEL         5

/*��Ϣ�ṹ�궨��*/
#define RESET_MCU_MSG_CORE_OFFSET               (16)
#define RESET_MCU_MSG_ID(core,phase)            ((core << RESET_MCU_MSG_CORE_OFFSET) | phase)
#define RESET_MCU_MSG_CORE(msg_id)              ((msg_id & 0xFFFF0000) >> RESET_MCU_MSG_CORE_OFFSET)
#define RESET_MCU_MSG_PHASE(msg_id)             (msg_id & 0x0000FFFF)

/*used for stop hifi watchdog1*/
#define DRV_WATCHDOG_LOCK_NUM           (0x0)           /* SP805 WATCHDOG������ */
#define DRV_WATCHDOG_UNLOCK_NUM         (0x1ACCE551)    /* SP805 WATCHDOG������ */
#define DRV_WATCHDOG_CONTROL_DISABLE    (0x0)           /* SP805 WATCHDOG������:�����жϲ�ֹͣ���´δ�ʱ���Զ����¼��� */
#define DRV_WATCHDOG_INTCLR_NUM         (0x4455)        /* SP805 WATCHDOG�ж�����֣�ʵ����д������ֵ������� */
/*������λģ���ʼ�������ʼ���ӳ�ʱ��*/
#define RESET_MOUDLE_DELAY_TIME          (2)


#define MNTN_PRINTBUF_LEN_MAX		128
#undef MNTN_SAVE_LOG_BY_FILESYS


#define MNTN_PRINT		printk

#ifndef FALSE
#define FALSE               (0)
#endif

#ifndef TRUE
#define TRUE                (1)
#endif

#ifndef __MDRV_ACORE_SYSBOOT_H__
typedef enum{
    MDRV_RESET_CB_BEFORE,   /* callback before doing the reset */
    MDRV_RESET_CB_AFTER,    /* callback after reset done */
    MDRV_RESET_RESETTING,   /* callback during doing the reset */
    MDRV_RESET_CB_INVALID,
}DRV_RESET_CB_MOMENT_E;

typedef int (*pdrv_reset_cbfun)(DRV_RESET_CB_MOMENT_E enparam, int userdata);
#endif
/*****************************************************************************
���ݽṹ����
*****************************************************************************/
/*Record information of callback functions*/
typedef struct
{
    char		name[DRV_RESET_MODULE_NAME_LEN + 1];
    int				priolevel;
    pdrv_reset_cbfun	cbfun;
    int         userdata;
} sreset_mgr_callbackfunc;

/*Link list unit of managing all callback functions*/
typedef struct _sreset_mgr_LLI
{
    sreset_mgr_callbackfunc cbfuninfo;
    struct _sreset_mgr_LLI	*pnext;
} sreset_mgr_LLI;


typedef struct _sreset_mailbox_msg_ccore
{
    int     iproctec;
    int     idata;
    int     ireserved;
} sreset_mailbox_msg_mcu;

typedef struct _sreset_debug_info
{
    unsigned int    ulCcpuTaskPhase;
} sreset_debug_info;
/*****************************************************************************
ö������
*****************************************************************************/
/*��λ�����漰��ģ��*/
typedef enum
{
    BSP_RESET_MODULE_CCORE,
    BSP_RESET_MODULE_HIFI,
    BSP_RESET_MODULE_MCU,
    BSP_RESET_MODULE_ACORE,
    BSP_RESET_MODULE_INVALID
} ereset_module;

/*��λ�����漰��ģ��*/
typedef enum
{
    BSP_RESET_CORE_CCORE = 0x0,
    BSP_RESET_CORE_HIFI = 0x1,
    BSP_RESET_CORE_INVALID
} ereset_core_with_mcu;
typedef enum
{
    BSP_RESET_PHASE_RESET_BEFORE = 0x0,
    BSP_RESET_PHASE_RESET_AFTER = 0x1,
    BSP_RESET_PHASE_RESET_FINISH = 0x2,
    BSP_RESET_PHASE_INVALID
} ereset_phase_with_mcu;
typedef enum
{
    BSP_RESET_MCU_MSG_CCORE_RESET_BEFORE = RESET_MCU_MSG_ID(BSP_RESET_CORE_CCORE, BSP_RESET_PHASE_RESET_BEFORE),
    BSP_RESET_MCU_MSG_CCORE_RESET_AFTER = RESET_MCU_MSG_ID(BSP_RESET_CORE_CCORE, BSP_RESET_PHASE_RESET_AFTER),
    BSP_RESET_MCU_MSG_CCORE_RESET_FINISH = RESET_MCU_MSG_ID(BSP_RESET_CORE_CCORE, BSP_RESET_PHASE_RESET_FINISH),
    BSP_RESET_MCU_MSG_HIFI_RESET_BEFORE = RESET_MCU_MSG_ID(BSP_RESET_CORE_HIFI, BSP_RESET_PHASE_RESET_BEFORE),
    BSP_RESET_MCU_MSG_HIFI_RESET_AFTER = RESET_MCU_MSG_ID(BSP_RESET_CORE_HIFI, BSP_RESET_PHASE_RESET_AFTER),
    BSP_RESET_MCU_MSG_INVALID = RESET_MCU_MSG_ID(BSP_RESET_CORE_INVALID, BSP_RESET_PHASE_INVALID)
} ereset_msg_with_mcu;

typedef enum
{
    RESET_TYPE_FAILGET_MSG_FROM_MCU,        /*����c�˸�λ��û���յ�MCU��Ϣ*/
    RESET_TYPE_FAILGET_MSG_FROM_HIFI,       /*����c�˸�λ��û���յ�hifi��Ϣ*/
    RESET_TYPE_MSG_FROM_MCU_WRONG,          /*����c�˸�λ��mcu�ظ�����Ϣ����ȷ*/
    RESET_TYPE_MSG_FROM_HIFI_WRONG,         /*����c�˸�λ��hifi�ظ�����Ϣ����ȷ*/
    RESET_TYPE_CRESET_NOTIFY_BEFORE,        /*����c�˸�λ����λǰ֪ͨ����*/
    RESET_TYPE_CRESET_NOTIFY_AFTER,         /*����c�˸�λ����λ��֪ͨ����*/
    RESET_TYPE_CRESET_NOTIFY_FINISH,        /*����c�˸�λ����λ���֪ͨ����*/
    RESET_TYPE_CRESET_RUNCB_STEP1_FAIL,     /*����c�˸�λ������ǰ���лص���������*/
    RESET_TYPE_CRESET_RUNCB_STEP2_FAIL,     /*����c�˸�λ�����غ����лص���������*/
    RESET_TYPE_CRESET_DORESET,              /*����c�˸�λ����λ����*/
    RESET_TYPE_CRESET_LOAD_BBE16_FAIL,      /*����c�˸�λ������bbe16����*/
    RESET_TYPE_CRESET_LOAD_CCPU_FAIL,       /*����c�˸�λ������ccpu����*/
    RESET_TYPE_CRESET_CRUN_NO_OK,           /*c�˵�����λ���������ɹ�*/

    RESET_TYPE_HIFIRESET_RUNCB_STEP1_FAIL,  /*����HIFI�˸�λ������ǰ���лص���������*/
    RESET_TYPE_HIFIRESET_RUNCB_STEP2_FAIL,  /*����HIFI�˸�λ�����غ����лص���������*/
    RESET_TYPE_HIFIRESET_LOAD_BIN_FAIL,     /*����HIFI�˸�λ�����س���*/

    /*add new above,please!!*/
    RESET_TYPE_FOR_TEST,        /*���ڲ���*/
    RESET_TYPE_MAX,
} ereset_type;

/*��λ����*/
typedef enum
{
    BSP_RESET_NONE,
    BSP_RESET_TYPE_MDM_PANIC,
    BSP_RESET_TYPE_MCU_PANIC
} ereset_irq_type;

/*��ռ�ö�ٶ���*/
typedef enum access_domain_type
{
    ACCESS_DOMAIN_NONE,
    ACCESS_DOMAIN_MODEM_SC, /*modem ��������*/
    ACCESS_DOMAIN_PERI_SC,  /*�����������*/
    ACCESS_DOMAIN_MEDIA_SC,  /*ý����ƼĴ� ����*/
    ACCESS_DOMAIN_MEDIA_NOC,  /*media noc���ƼĴ�����*/
    ACCESS_DOMAIN_BBE16_DTCM,  /*bbe16 dtcm��*/    
    
    /*Please add above*/
    ACCESS_DOMAIN_MAX
} eACCESS_DOMAIN_TYPE;

/*****************************************************************************
��������
*****************************************************************************/
extern int hifireset_runcbfun (DRV_RESET_CB_MOMENT_E eparam);
extern int hifireset_tonotify(DRV_RESET_CB_MOMENT_E eparam, ereset_module emodule);
extern void hifi_freeze_give_semaphone(void);
extern int hifireset_loadhifibin(void);
extern void mailbox_recfun_hifi(void  *UserHandle,void *MailHandle,unsigned int MailLen);
extern sreset_mgr_LLI * reset_link_insert(sreset_mgr_LLI *plink, sreset_mgr_LLI *punit);
extern int reset_no_ok_savelog(char *pname, int iresult, DRV_RESET_CB_MOMENT_E eparam, ereset_module emodule);
extern int reset_for_savelog(char *pstr);
extern void reset_hifi_up_semaphone(void);
extern void finish_reset_sub(void);

/*register the notifier to the notify events below*/
int mcu_panic_regsister_notifier(struct notifier_block *n);
int hifi_freeze_regsister_notifier(struct notifier_block *n);
int android_freeze_regsister_notifier(struct notifier_block *n);
int mcu_freeze_regsister_notifier(struct notifier_block *n);
int android_reboot_regsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_regsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mcu_puzzle_regsister_notifier(struct notifier_block *n);

/*unregister the notifier from the notify events below*/
int mcu_panic_unregsister_notifier(struct notifier_block *n);
int hifi_freeze_unregsister_notifier(struct notifier_block *n);
int android_freeze_unregsister_notifier(struct notifier_block *n);
int mcu_freeze_unregsister_notifier(struct notifier_block *n);
int android_reboot_unregsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_unregsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
void reset_clean_wdt_int(ereset_module emodule);
int mcu_puzzle_unregsister_notifier(struct notifier_block *n);
void save_mcu_log_info(void);
void test_fiq(void);
int drv_read_bin(const char *partion_name, unsigned int offset, unsigned length, char *buffer);
int is_mcu_exception(void);
void set_acore_state(unsigned int core, int state);
void clear_acore_state(unsigned int core);
/*END*/

extern int get_domain_access_status(eACCESS_DOMAIN_TYPE etype);

#endif

