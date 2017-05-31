/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __NASNVINTERFACE_H__
#define __NASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV��� */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV��δ���� */

/* GPRS GEA �㷨֧�ֺ궨�� */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* ֧��GPRS GEA1�㷨 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* ֧��GEA1ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* ֧��GEA2ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* ֧��GEA3ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* ֧��GEA4ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* ֧��GEA5ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* ֧��GEA6ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* ֧��GEA7ʱ����������ֵ */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* ֧��GPRS GEA2�㷨 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* ֧��GPRS GEA3�㷨 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* ֧��GPRS GEA4�㷨 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* ֧��GPRS GEA5�㷨 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* ֧��GPRS GEA6�㷨 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* ֧��GPRS GEA7�㷨 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV�е�Чplmn���� */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn��Mcc��󳤶� */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn��Mnc��󳤶� */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* �û����õ�EHplmn�ĸ��� */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* ��ֹ���뼼����PLMN ID�������� */
#define NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM              (8)                /* ��չ��NV���EHplmn���������*/
#define NAS_MMC_NVIM_MAX_USER_CFG_FORB_PLMN_GROUP_NUM         (8)                /* �û����õ�forb plmn��������� */

#define NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN               (8)               /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* �û����õ�OPLMN����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_NUM                   (256)             /* �û����õ�OPLMN�������� */
#define NAS_MMC_NVIM_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* �û����õĴ����뼼��OPLMN������Ԫ���ȣ���6F61�ļ��Ļ������ȵ�ԪΪ5 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN              (500)             /* �û�����OPLMN������ֽ���,����ǰֻ֧��500*/
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN       (1280)            /* ��չ����û�����OPLMN������ֽ���*/


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
/* ����:��128��256; ����Ԥ��������Ϣ,��6��7*/
#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN             (7*256)            /* ��չ����û�����DPLMN������ֽ��� */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN             (7*256)            /* ��չ����û�����NPLMN������ֽ��� */
/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN       (6*128)            /* ��չ����û�����DPLMN������ֽ���*/
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN       (6*128)            /* ��չ����û�����NPLMN������ֽ���*/
#define NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM                   (3*8)
#define NAS_MCC_NVIM_VERSION_LEN                         (9)                /* �汾�ţ��̶�Ϊxx.xx.xxx */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM                   (256)            /* ��չ����û�����DPLMN���� */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM                   (256)            /* ��չ����û�����NPLMN���� */

#define NAS_NVIM_MAX_OPER_SHORT_NAME_LEN                36
#define NAS_NVIM_MAX_OPER_LONG_NAME_LEN                 40

#define NAS_NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */
#define NAS_MML_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */
#define NAS_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */

#define NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM          (6)                 /* ģʽ�Զ��л������Ŀ����ù�������� */
#define NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM       (6)                 /* ģʽ�Զ��л������Ŀ�����USIM/IMSI������Ÿ��� */

#define NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM              (8)                 /* ��ֹ���뼼����PLMN ID�������� */

#define NAS_MML_MAX_EXTENDED_FORB_PLMN_NUM                  (32)

#define NAS_SIM_FORMAT_PLMN_LEN                     (3)                     /* Sim����ʽ��Plmn���� */

#define NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG�Ѳ����ǹ�����Ĺ����������� */
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /* ����ԭ��ֵ����б� */

#define NV_ITEM_NET_CAPABILITY_MAX_SIZE                     (10)

#define NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE            (2)                 /* ��ǰ֧�ֵ�Э��汾 */

#define NAS_MMC_NVIM_MAX_IMSI_LEN                           (9)                     /* ����IMSI�ĳ��� */

#define NVIM_MAX_EPLMN_NUM                                  (16)
#define NVIM_MAX_MCC_SIZE                                   (3)
#define NVIM_MAX_MNC_SIZE                                   (3)

#define NVIM_MAX_FDD_FREQ_BANDS_NUM                         (12)

/*+CGMI - ��ȡ����������*/

#define NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM         (16)
#define NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM          (8)    /* Ԥ����չ */
#define NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM     (2)

#define NAS_NVIM_FORBIDDEN_RAT_NUM_0                 (0)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_1                 (1)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_2                 (2)


#define NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM              (8)

#define NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM     (12)

/* ��NVIDö�ٵ�ת����(PS_NV_ID_ENUM, SYS_NV_ID_ENUM, RF_NV_ID_ENUM) */
typedef VOS_UINT16  NV_ID_ENUM_U16;
#define NV_ITEM_IMEI_SIZE                      16
#define NV_ITEM_MMA_OPERATORNAME_SIZE          84

#define NV_ITEM_OPER_NAME_LONG          (40)
#define NV_ITEM_OPER_NAME_SHORT         (36)
#define NV_ITEM_PLMN_ID_LEN             (8)

#define NV_ITEM_AT_PARA_SIZE                   100
#define NV_ITEM_HPLMN_FIRST_SEARCH_SIZE        1  /* ��һ��HPLMN������ʱ���� */
#define NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */

#define CNAS_NVIM_MAX_1X_MRU_SYS_NUM                            (12)

#define NAS_MMC_NVIM_MAX_CAUSE_NUM      (10)     /* NV����ԭ��ֵ������ */

#define CNAS_NVIM_PRL_SIZE                                      (4096) /* PRL NV size: 4K byte */

#define CNAS_NVIM_CBT_PRL_SIZE                                  (48) /* PRL NV size: 45 bytes */

#define CNAS_NVIM_MAX_1X_BANDCLASS_NUM                          (32)

#define CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM                       (20)
#define CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_MAX_1X_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM                           (12)
#define CNAS_NVIM_HRPD_SUBNET_LEN                                (16)

#define CNAS_NVIM_MAX_STORAGE_BLOB_LEN                      ( 255 )

#define NAS_NVIM_BYTES_IN_SUBNET                            (16)
#define NAS_NVIM_MAX_RAT_NUM                                (7)                 /* Ԥ����1X��HRPD */

#define NAS_MSCC_NVIM_MLPL_SIZE                                      (1024) /* PRL NV size: 1K byte */
#define NAS_MSCC_NVIM_MSPL_SIZE                                      (1024) /* PRL NV size: 1K byte */

#define NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM      ( 8 )                       /*  ����ȫ��ͨ���ص�ͨ�����ó�����Ŀ */

#define CNAS_NVIM_ICCID_OCTET_LEN                            (10)
#define CNAS_NVIM_MEID_OCTET_NUM                             (7)
#define CNAS_NVIM_UATI_OCTET_LENGTH                          (16)

#define CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM                     (20)

#define CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM                (10)

#define CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM              (10)
#define CNAS_NVIM_MAX_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_NUM           (20)

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/* �����ȼ�PLMN refresh ����������Ĭ���ӳ�ʱ��: ��λ �� */
#define NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN    (5)
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

#define NAS_NVIM_MAX_PLMN_CSG_ID_NUM             (35)
#define NAS_NVIM_MAX_CSG_REJ_CAUSE_NUM           (10)

#define NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM      (16)    /* SIM���б� (LTE OOS������2G����3G) */

#define NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM        (16)        /*֧�ֵĽ�ֹLA�б��С*/
#define CNAS_NVIM_MAX_AUTHDATA_USERNAME_LEN                      (253)   /* HRPD ppp AN��Ȩ�û�����û�����
                                                                            �ο�C.S0023-D section 3.4.53�Լ�
                                                                            C.S0016-D,section 3.5.8.13,
                                                                            �ó��������Ϊ255-2(NAI������
                                                                            ����Ȩ�㷨�����ֽ�ռ�õ��ֽ�) */

#define CNAS_NVIM_1X_MAX_MRU_SYS_NUM                   (12)

#define CNAS_NVIM_1X_AVOID_MAX_PHASE_NUM               (8)
#define CNAS_NVIM_1X_AVOID_REASON_MAX                  (20)

#define CNAS_NVIM_MAX_HRPD_OOC_SCHEDULE_PHASE_NUM                    (8)

#define CNAS_NVIM_HRPD_AVOID_MAX_PHASE_NUM               (8)
#define CNAS_NVIM_HRPD_AVOID_REASON_MAX                  (16)

#define CNAS_NVIM_HOME_MCC_MAX_NUM                      (5)

#define NAS_NVIM_MAX_BSR_PHASE_NUM                      (2)

#define NAS_MMC_NVIM_MAX_EXTENDED_FORB_PLMN_NUM         (32)

#define NAS_MAX_TMSI_LEN                                (4)                     /* ����TMSI�ĳ��� */
#define NAS_SIM_MAX_LAI_LEN                             (6)                     /* SIM���б����LAI��󳤶� */
#define NAS_MMC_NVIM_MAX_CUSTOM_SUPPLEMENT_OPLMN_NUM    (16)

#define CNAS_NVIM_MAX_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_NUM           (20)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
ö����    : NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
�ṹ˵��  : ����ע�ᱻ�ܣ�MMC�Ķ���

1.��    ��   : 2012��6��11��
  ��    ��   : w00166186
  �޸�����   : AT&T&DCM��Ŀ��������

2.��    ��   : 2014��8��19��
  ��    ��   : w00167002
  �޸�����   : DTS2014081905808:������PSע��ܾ�14ʱ������ǰ��HOME PLMN�ϣ������
               ����ѭ��ƹ�ң��޸�Ϊ����ACTION����:�����������ϴ���ѡ������HOME������
               ����Ч�����������̽��д���

*****************************************************************************/
enum NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 0,            /* �������� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 1,            /* ����פ�� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 2,            /* ������ѡ���� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 3,            /* ����פ�� */

    NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 4,            /* ������������ע�ᷢ����������HOME�����ϲ���Ч */

    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;

/*****************************************************************************
ö����    : NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
�ṹ˵��  : ע��ʧ���Զ���ԭ��ֵ

1.��    ��   : 2012��6��11��
  ��    ��   : w00166186
  �޸�����   : AT&T&DCM��Ŀ��������

*****************************************************************************/
enum NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN = 14,
    NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT               = 301,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT16 NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16;

/*****************************************************************************
ö����    : NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8
�ṹ˵��  : ע����

1.��    ��   : 2012��6��11��
  ��    ��   : w00166186
  �޸�����   : AT&T&DCM��Ŀ��������

*****************************************************************************/
enum NAS_MMC_NVIM_REG_DOMAIN_ENUM
{
    NAS_MMC_NVIM_REG_DOMAIN_CS = 1,
    NAS_MMC_NVIM_REG_DOMAIN_PS = 2,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8;

/* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, begin */
/*****************************************************************************
 ö����    : NAS_MMC_UCS2_ENUM
 ö��˵��  : UCS2 ����
 �޸���ʷ  :
 1.��    ��    : 2013��03��11��
   ��    ��    : w00176964
   �޸�����    : �½�
*****************************************************************************/

enum NAS_MMC_UCS2_ENUM
{
    NAS_MMC_UCS2_HAS_PREFER                                = 0,
    NAS_MMC_UCS2_NO_PREFER                                 = 1,

    NAS_MMC_UCS2_BUTT
};

typedef VOS_UINT16 NAS_MMC_UCS2_ENUM_UINT16;
/* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, end */

/*****************************************************************************
 ö����    : NV_MS_MODE_ENUM_UINT8
 �ṹ˵��  :  NV�м�¼���ֻ�ģʽ
  1.��    ��   : 2011��8��18��
    ��    ��   : z00161729
    �޸�����   : ����
  2.��    ��   : 2012��4��23��
    ��    ��   : w00166186
    �޸�����   : DTS2012033104746,�ػ�״̬���÷�����ΪANY����Ч
*****************************************************************************/
enum NV_MS_MODE_ENUM
{
    NV_MS_MODE_CS_ONLY,                                                 /* ��֧��CS�� */
    NV_MS_MODE_PS_ONLY,                                                 /* ��֧��PS�� */
    NV_MS_MODE_CS_PS,                                                   /* CS��PS��֧�� */

    NV_MS_MODE_ANY,                                                     /* ANY,�൱�ڽ�֧��CS�� */

    NV_MS_MODE_BUTT
};
typedef VOS_UINT8 NV_MS_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_NV_LTE_CS_SERVICE_CFG_ENUM_UINT8
 ö��˵��  : Lģ֧�ֵ�cs��ҵ������������
 1.��    ��   : 2016��02��16��
   ��    ��   : w00167002
   �޸�����   : �½�
*****************************************************************************/
enum NAS_NV_LTE_CS_SERVICE_CFG_ENUM
{
    NAS_NV_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS = 1,           /* ֧��cs fallback��sms over sgs*/
    NAS_NV_LTE_SUPPORT_SMS_OVER_SGS_ONLY,                   /* ֧��sms over sgs only*/
    NAS_NV_LTE_SUPPORT_1XCSFB,                              /* ֧��1XCSFB */
    NAS_NV_LTE_SUPPORT_BUTT
};
typedef VOS_UINT8 NAS_NV_LTE_CS_SERVICE_CFG_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
 �ṹ˵��  : �޸ľܾ�ԭ��ֵ�����շ������������
  1.��    ��   : 2013��11��19��
    ��    ��   : l00208543
    �޸�����   : ����
*****************************************************************************/
enum NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_INACTIVE     = 0,        /* ���ܲ���Ч */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_PS,                   /* �޸�CS+PS�ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_ONLY,                 /* ���޸�CS��ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_PS_ONLY,                 /* ���޸�PS��ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8
 �ṹ˵��  : Ƶ���ظ���������ö��
 1.��    ��   : 2015��01��08��
   ��    ��   : h00313353
   �޸�����   : ����
*****************************************************************************/
enum NAS_NVIM_CHAN_REPEAT_SCAN
{
    NAS_NVIM_CHAN_SCAN_NORMAL,
    NAS_NVIM_CHAN_REPEAT_SCAN_REACQ_0_1_2_3_4S,
    NAS_NVIM_CHAN_REPEAT_SCAN_PING_5,
    NAS_NVIM_CHAN_REPEAT_SCAN_2_7,

    NAS_NVIM_CHAN_REPEAT_SCAN_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8
 �ṹ˵��  : EPDSZID֧������
 1.��    ��   : 2015��01��10��
   ��    ��   : g00261581
   �޸�����   : ����
*****************************************************************************/
enum NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID,

    NAS_NVIM_EPDSZID_SUPPORT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8;


enum NAS_NVIM_LC_RAT_COMBINED_ENUM
{
    NAS_NVIM_LC_RAT_COMBINED_GUL,
    NAS_NVIM_LC_RAT_COMBINED_CL,

    NAS_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8;

/*****************************************************************************
 ö����    : CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_ENUM_UINT8
 �ṹ˵��  : negϵͳ�� perfϵͳ�ȽϿ���
 1.��    ��   : 2015��6��9��
   ��    ��   : c00299063
   �޸�����   : ����
*****************************************************************************/
enum CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH,                /* Band Channel ģ��ƥ�� */
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_ACCURATE_MATCH,                 /* Band Channel ��ȷƥ��*/
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM
 ö��˵��  : CLϵͳ����dsds�Ĳ��Գ����Ķ���
 1.��    ��   : 2016��02��02��
   ��    ��   : w00176964
   �޸�����   : DTS2016013006596�½�
 2.��    ��   : 2016��06��15��
   ��    ��   : w00176964
   �޸�����   : DTS2016060709509�޸�
*****************************************************************************/
enum NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM
{
    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_SWITCH_ON                 = 0,        /* ���� */

    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_SWITCH_ON_AND_SYSCFG_SET  = 0x1,      /* ������syscfg���ó��� */

    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ANY                       = 0xFE,     /* CLϵͳ��������ⳡ�� */

    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU
 �ṹ˵��  : NV SrchHplmnFlg_ManualMode�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usManualSearchHplmnFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
 �ṹ˵��  : NV SrchHplmnFlg_ManualMode�Ľṹ�ṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usAutoSearchHplmnFlg; /*Range:[0,3]*/
}NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU
 �ṹ˵��  : NV en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG �Ľṹ�ṹ

  1.��    ��   : 2015��9��30��
    ��    ��   : c00318887
    �޸�����   : �½�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;       /* ucActiveFlag �Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
 �ṹ˵��  : NV SrchHplmnFlg_AutoMode�Ľṹ�ṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEHPlmnSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStkSteeringOfRoamingSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_SCAN_CTRL_STRU
 �ṹ˵��  : ��¼en_NV_Item_Scan_Ctrl_Para (9080)NV�����ݣ���ʶ�������ƹ����Ƿ�ʹ��
  1.��    ��   : 2012��06��11��
    ��    ��   : l60609
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Scan_Ctrl_Para NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserved1;                            /* ���� */
    VOS_UINT8                           ucReserved2;                            /* ���� */
    VOS_UINT8                           ucReserved3;                            /* ���� */
}NVIM_SCAN_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_ID_STRU
 �ṹ˵��  : PLMN�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_NVIM_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_ID_STRU
 �ṹ˵��  : en_NV_Item_Network_Name_From_MM_Info�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_NVIM_MAX_OPER_SHORT_NAME_LEN];/* ��ǰפ��������Ӫ�̵Ķ����� */
    VOS_UINT8                           aucOperatorNameLong[NAS_NVIM_MAX_OPER_LONG_NAME_LEN];  /* ��ǰפ��������Ӫ�̵ĳ����� */
}NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU
 �ṹ˵��  : en_NV_Item_OPERLOCK_PLMN_INFO NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBlackPlmnLockNum;                     /* ֧�ֺ������ĸ���,����Ϊ0ʱ��ʾ��֧�ֺ����� */
    NAS_NVIM_PLMN_ID_STRU               astBlackPlmnId[NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_AIS_ROAMING_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_AIS_ROAMING_Config NV������
 1.��    ��   : 2012��5��17��
   ��    ��   : z40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* �������Ƿ�� */
    VOS_UINT8                           ucHighPrioRatType;                              /* ����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
    NAS_NVIM_PLMN_ID_STRU               stHighPrioPlmnId;                       /* ����֧�ֵĸ����ȼ���PLMN ID ,��ʹפ����HPLMN��,��PLMNID�����ȼ�Ҳ�ϸ�*/
    NAS_NVIM_PLMN_ID_STRU               stSimHPlmnId;                           /* SIM����HPLMN ID */
}NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_USER_AUTO_RESEL_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_User_Auto_Resel_Switch NV������,UserResecl�����Ƿ�ʹ��
 1.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton����֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAutoReselActiveFlg;                   /* �Ƿ�����LTE�������α��:VOS_TRUE ��ʾ����LTE�������� VOS_FALSE ��ʾ��ֹLTE�������� */
    VOS_UINT8                           ucReserve;
}NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU
 �ṹ˵��  :  en_NV_Item_PRIO_HPLMNACT_CFG NV��ṹ
 1.��    ��   : 2012��6��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012060400029:��Ӷ�HPLMNAct���Ƚ��뼼���Ķ��ƣ�ĿǰUSim����HPLMNACT�ܶ಻֧��L
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;        /* NV��Ч��־, 1: ��Ч��0����Ч */
	VOS_UINT8                            ucReserved;      /* ���ֽڶ��� */
    VOS_UINT16                           usPrioHplmnAct;      /*���Ƶ����Ƚ��뼼��*/
}NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_NVIM_AVAIL_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_SEARCH_TIMER_INFO NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer��ʱ����һ�ε�ʱ�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer��ʱ����һ�εĴ��� */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer��ʱ����˯��ʱ�� */
    VOS_UINT32                          ulDeepSearchTimeCount;
}NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_T3212_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_SEARCH_TIMER_INFO NV��ṹ
  1.��    ��   : 2015��3��14��
    ��    ��   : w00167002
    �޸�����   : �½�

    BIT0����: LAUU����ʱ��ʧ������T3212����
    ulT3212StartSceanCtrlBitMask1 BIT0:             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL
    BIT1����: LAU����ʱ��REL����T3212����
    ulT3212StartSceanCtrlBitMask1 BIT1:             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNvActiveFlg;                          /* ���Ƶ�ǰNV�Ƿ�ʹ�� */
    VOS_UINT32                          ulT3212StartSceneCtrlBitMask;           /* BIT0~BIT31,���ڿ�����·ʧ�ܺ�����T3212ʱ���Ƿ�ʹ�õ�ǰNV���õ�ʱ�� */
    VOS_UINT32                          ulT3212Phase1TimeLen;                   /* t3212��ʱ����1�׶ε�ʱ��,��λΪs */
    VOS_UINT32                          ulT3212Phase1Count;                     /* t3212��ʱ����1�׶εĴ��� */
    VOS_UINT32                          ulT3212Phase2TimeLen;                   /* t3212��ʱ����2�׶ε�ʱ��,��λΪs  */
    VOS_UINT32                          ulT3212Phase2Count;                     /* t3212��ʱ����2�׶εĴ��� */
}NAS_MMC_NVIM_T3212_TIMER_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU
 �ṹ˵��  : en_NV_Item_OPERLOCK_PLMN_INFO_WHITE NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWhitePlmnLockNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    NAS_NVIM_PLMN_ID_STRU               astWhitePlmnId[NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_SUPPORT_CPHS_FLAG NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : en_NV_Item_PREVENT_TEST_IMSI_REG�ṹ
  1.��    ��   : 2012��2��22��
    ��    ��   : w00199382
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_PREVENT_TEST_IMSI_REG_STRU;
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : en_NV_Item_PREVENT_TEST_IMSI_REG�ṹ
  1.��    ��   : 2012��2��22��
    ��    ��   : w00199382
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnSearchPowerOn;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU;


/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_NVIM_ITEM_MAX_IMSI_LEN];        /* �ϴα����IMSI������ */
}NAS_NVIM_TIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulAutoStart;
}NAS_MMA_NVIM_AUTO_START_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU
 �ṹ˵��  : en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT NV��ṹ
  1.��    ��   : 2011��8��5��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSingleDomainFailPlmnSrchFlag;         /* DT�������󣬵���ע�ᱻ�ܺ���Ҫ�������� */
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPsLocInfo[NAS_NVIM_PS_LOCI_SIM_FILE_LEN];
}NAS_NVIM_PS_LOCI_SIM_FILES_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CS_LOCI_SIM_FILES_STRU
 �ṹ˵��  : en_NV_Item_Cs_Loci  NV�ṹ
  1.��    ��   : 2016��4��10��
    ��    ��   : j00174725
    �޸�����   : DTS2016040901340
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucTmsi[NAS_MAX_TMSI_LEN];
    VOS_UINT8                           aucLastLai[NAS_SIM_MAX_LAI_LEN];
    VOS_UINT8                           ucLauStaus;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_CS_LOCI_SIM_FILES_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_NVIM_GPRS_GEA_ALG_CTRL_STRU
 �ṹ˵��  : en_NV_Item_GEA_SUPPORT_CTRL NV��ṹ
 1.��    ��   : 2011��7��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucStatus;                                /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                          ucGeaSupportCtrl;                        /* �ն�����:GPRS GEA�㷨֧�ֿ��� */
}NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_LTE_CS_SERVICE_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_Lte_Cs_Service_Config NV�����ݣ�LTE֧�ֵ�csҵ������
  1.��    ��   : 2011��10��28��
    ��    ��   : z00161729
    �޸�����   : �½�
  2.��    ��   : 2013��09��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ���޸Ľṹ������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;    /* en_NV_Item_Lte_Cs_Service_Config NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucLteCsServiceCfg;  /* LTE֧�ֵ� cs��ҵ������*/
}NAS_NVIM_LTE_CS_SERVICE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU
 �ṹ˵��  : NVIM���е�����CSFB HO���̵�ϵͳ��Ϣʱ����NV��δ�����򲻵�ϵͳ��Ϣֱ��ע��
 1.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucWaitSysinfoTimeLen;
}NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU
 �ṹ˵��  : en_NV_Item_Lte_Internation_Roam_Config NV��ṹ
 1.��    ��   : 2012��3��14��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2012��4��25��
   ��    ��   : w00176964
   �޸�����   : DTS2012042403564:�޸�NV��ȡ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           aucRoamEnabledMccList[20];/* �������εĹ������б� */
}NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ROAM_RPLMN_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_Roam_Search_Rplmn_Config NV��ṹ
 1.��    ��   : 2014��2��24��
   ��    ��   : t00173447
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamRplmnflg;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                         aucRoamEnabledMccList[5];/* �������εĹ������б� */
}NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU;

/* Modified by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU
 �ṹ˵��  : en_NV_Item_Close_SMS_Capability_Config NV��ṹ
 1.��    ��   : 2013��3��11��
   ��    ��   : w00176964
   �޸�����   : close sms capability NV�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU;
/* Modified by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_STRU
 �ṹ˵��  : en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2013��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2013121206933:�Ǹ����ȼ����øߵ����������簴syscfg���ý��뼼�����ȼ�����9055 nv�����
  3.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWcdmaPriorityGsmFlg;                  /* H3G��������W����������G*/

    VOS_UINT8                           ucSortAvailalePlmnListRatPrioFlg;    /* �Ƿ�syscfg���ý��뼼�����ȼ�����ߵ����������б��ʶ��1:��; 0:���Ǹ��������簴���������������粻����*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPsOnlyCsServiceSupportFlg;            /* ����������ΪPS ONLYʱ���Ƿ�֧��CS����źͺ���ҵ��(�������г���)*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_CCBS_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /* CCBS(��æ�������)ҵ��*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}NAS_NVIM_CCBS_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU
 �ṹ˵��  : en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT NV��ṹ
 1.��    ��   : 2012��6��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&t&DCM�½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          aulCustommMccList[10];                   /* �������εĹ������б� */
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU;


/*****************************************************************************
 �ṹ��    : NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_ACTING_PLMN_SUPPORT_FLAG NV��ṹ
  1.��    ��   : 2011��06��11��
    ��    ��   : W00166186
    �޸�����   : AT&T&DCM�½��ṹ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU
 �ṹ˵��  : en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG NV��ṹ
  1.��    ��   : 2011��06��11��
    ��    ��   : W00166186
    �޸�����   : AT&T&DCM�½��ṹ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
 �ṹ˵��  : ����ע�ᱻ�ܶ��ƶ����ṹ
 1.��    ��   : 2012��6��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&t&DCM�½�
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enRegCause;
    NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8                      enDomain;
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enAction;
}NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
 �ṹ˵��  : ����ע�ᱻ�ܶ���en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST�ṹ
 1.��    ��   : 2012��6��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&t&DCM�½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               auReserv[2];
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU         astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_SIM_FORMAT_PLMN_ID
 �ṹ˵��  : Sim PLMN ID�Ĵ洢�ṹ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_SIM_FORMAT_PLMN_ID;

/*****************************************************************************
 �ṹ��    : NAS_UTRANCTRL_NVIM_CURRENT_UTRAN_MODE_STRU
 �ṹ˵��  : ��¼en_NV_Item_Utran_Mode NV������
 1.��    ��   : 2012��7��13��
   ��    ��   : w00167002
   �޸�����   : V7R1C50_GUTL_PhaseI:�¼�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranMode;                            /* ��ǰ֧�ֵ�UTRANģʽ */
    VOS_UINT8                           ucReserve;
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU
 �ṹ˵��  : ��¼en_NV_Item_Utran_Mode_Auto_Switch NV������
 1.��    ��   : 2012��8��7��
   ��    ��   : w00167002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0��UTRANģʽΪFDD 1��UTRANģʽΪTDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* ֧��TD����Ĺ��ҺŸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ����IMS PLMN����UTRANģʽ�Ƿ�AUTO SWITCHʱ����ǰIMSI��PLMN�ڴ��б��еĶ�֧���Զ��л�������̶�ΪWģ */
    VOS_UINT8                           aucReserve[1];

    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU;




/*****************************************************************************
 �ṹ��    : NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU
 �ṹ˵��  : en_NV_Item_UTRAN_TDD_SMC_FLAG NV��ṹ
 1.��    ��   : 2013��7��25��
   ��    ��   : w00167002
   �޸�����   : ������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                TD�²�����SMC���̡�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����CS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����PS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU
 �ṹ˵��  : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU�ṹ�����Ʒ�HPLMN/RPLMN
             ��������ֹ���Ƿ���PLMN���� en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG
 1.��    ��   : 2013��10��15��
   ��    ��   : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   aucReserve[3];
}NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU
 �ṹ˵��  : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU NVIM���е��û����õ�OPLMN
 1.��    ��   : 2013��10��15��
   ��    ��   : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU
 �ṹ˵��  : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU NVIM���е��û����õ�OPLMN
 1.��    ��   : 2013��11��26��
   �޸�����   : ��NV֧�ֵ����OPLMN������չ��256��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT16                          usOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           aucReserve[3];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg NVIM
            en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg
            en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg
            �е�DPLMN NPLMN������Ϣ
 1.��    ��   : 2015��5��28��
   ��    ��   : c00318887
   �޸�����   : �����Ż�����DPlmn���ݺ����Ƚ���HPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                                                    /* NVʹ�ܱ�־ */
    VOS_UINT8                           ucExtendedForbPlmnNum;                                          /* ��չ��Forb Plmn���� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    NAS_NVIM_PLMN_ID_STRU               astForbPlmnIdList[NAS_MMC_NVIM_MAX_EXTENDED_FORB_PLMN_NUM];     /* ��չ��Forb Plmn�б� */
}NAS_MMC_NVIM_EXTENDED_FORBIDDEN_PLMN_LIST_CFG_STRU;

/* Added by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg NVIM
            en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg
            en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg
            �е�DPLMN NPLMN������Ϣ
 1.��    ��   : 2015��5��28��
   ��    ��   : c00318887
   �޸�����   : �����Ż�����DPlmn���ݺ����Ƚ���HPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* �������õ�Dplmn�ĸ��� */
    VOS_UINT16                         usNplmnListNum;                                       /* �������õ�Nplmn�ĸ��� */

    /* DPLMN����,ÿ7���ֽڴ���һ��dplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)��
       ��6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)
       ��7ֱ��ΪԤ�ñ�ʾ��Ϣ: 1(Ԥ��Dplmn), 0(��ѧϰ����DPLMN) */
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN];

    /* NPLMN����,ÿ7���ֽڴ���һ��nplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)��
       ��6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)
       ��7ֱ��ΪԤ�ñ�ʾ��Ϣ: 1(Ԥ��nplmn), 0(��ѧϰ����nplmn) */
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN];/* NPLMN����*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_CMCC_Cfg_Dplmn_Nplmn NVIM
            en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn
            en_NV_Item_CT_Cfg_Dplmn_Nplmn
            �е�DPLMN NPLMN������Ϣ
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����Ż�������������DPLMN NPLMN
 2.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* �������õ�Dplmn�ĸ��� */
    VOS_UINT16                         usNplmnListNum;                                       /* �������õ�Nplmn�ĸ��� */

    /* DPLMN����,ÿ6���ֽڴ���һ��dplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)����6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)*/
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN];

    /* NPLMN����,ÿ6���ֽڴ���һ��nplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)����6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)*/
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN];/* NPLMN����*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_OLD_STRU;
/* Added by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Cfg_Dplmn_Nplmn_Flag NVIM
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����Ż�������������DPLMN NPLMNʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usCfgDplmnNplmnFlag;
    VOS_UINT8                          ucCMCCHplmnNum;
    VOS_UINT8                          aucCMCCHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucUNICOMHplmnNum;
    VOS_UINT8                          aucUNICOMHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucCTHplmnNum;
    VOS_UINT8                          aucCTHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          aucReserve[3];
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU
 �ṹ˵��  : en_NV_Item_Cfg_Dplmn_Nplmn_Flag NVIM
 1.��    ��   : 2015��10��20��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEHplmnNum;
    VOS_UINT8                           aucEHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                           aucVersionId[NAS_MCC_NVIM_VERSION_LEN];
    VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MML_USER_CFG_EHPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Ehplmn NVIM���е��û����õ�Ehplmn List
 1.��    ��   : 2012��8��9��
   ��    ��   : w00167002
   �޸�����   : V7R1C50_GUTL_PhaseII:CMCC����EHPLMN����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucEhplmnListNum;                        /* �û����õ�EHplmn�ĸ��� */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astEhPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Ehplmn NVIM���е��û����õ������Ehplmn List��
 1.��    ��   : 2014��12��19��
   ��    ��   : wx270776
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulNvimEhplmnNum;
    NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU    astNvimEhplmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_FORB_PLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Forb_Plmn_Info NVIM���е��û����õ�ÿһ��FPLMN��Ϣ
  1.��    ��   : 2016��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ÿһ���ﶨ�Ƶ�IMSI�б���� */
    VOS_UINT8                           ucForbPlmnListNum;                      /* ÿһ�����û����õ�Forb Plmn�ĸ��� */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astForbPlmnList[NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM];
}NAS_MMC_NVIM_FORB_PLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_FORB_PLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Forb_Plmn_Info NVIM���е��û����õ�Forb PLMN��
  1.��    ��   : 2016��3��31��
    ��    ��   : s00217060
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGroupNum;
    NAS_MMC_NVIM_FORB_PLMN_INFO_STRU    astForbPlmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_FORB_PLMN_GROUP_NUM];
}NAS_MMC_NVIM_USER_CFG_FORB_PLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CAUSE18_ENABLE_LTE_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_Cause18_Enable_Lte_Support_Flg NV�ṹ
  1.��    ��   : 2016��4��8��
    ��    ��   : h00275845
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucCause18EnableLteSupportFlg; /*�Ƿ�֧��Cause18 Enable Lte*/
    VOS_UINT8                          aucReserved0;
    VOS_UINT8                          aucReserved1;
    VOS_UINT8                          aucReserved2;
}NAS_MMC_NVIM_CAUSE18_ENABLE_LTE_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PLMN_WITH_RAT_STRU
 �ṹ˵��  : NAS MML PLMN�ͽ��뼼���ṹ
 1.��    ��   : 2012��8��9��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_NVIM_PLMN_WITH_RAT_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_DISABLED_RAT_PLMN_INFO NV��ṹ
  1.��    ��   : 2012��8��15��
    ��    ��   : w00176964
    �޸�����   : �½�
  2.��    ��   : 2015��4��18��
    ��    ��   : w00167002
    �޸�����   : DTS2015032709270:NV������ֹ����ĸ���Ϊ8����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDisabledRatPlmnNum;                   /* ֧�ֽ�ֹ���뼼����PLMN����,����Ϊ0��ʾ��֧�ָ����� */

    NAS_MMC_NVIM_PLMN_WITH_RAT_STRU     astDisabledRatPlmnId[NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM];/* ��ֹ���뼼����PLMN��RAT��Ϣ */

}NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU;

/*****************************************************************************
 ö����    : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
 �ṹ˵��  :
 1.��    ��: 2013��11��01��
   ��    ��: l00208543
   �޸�����: ����
*****************************************************************************/
enum NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /* ����δ���� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /* �������������� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /* �������������� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
 �ṹ˵��  :
 1.��    ��: 2013��11��01��
   ��    ��: l00208543
   �޸�����: ����
*****************************************************************************/
enum NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRAN����WCDMA/TDS-CDMA */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8;


enum NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM
{
    NAS_MSCC_NVIM_SYS_PRI_CLASS_HOME             = 0,    /* home or ehome plmn */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_PREF             = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ANY              = 2,    /* Acceptable PLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU
 �ṹ˵��  : en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config NV��ṹ
  1.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : �½�

    ucSwitchFlag        �������ͣ�0�����
                                  1: astImsiPlmnList �����ڵĿ����ý�ֹRAT���ܣ�
                                  2���Բ���astImsiPlmnList �����еĿ����ý�ֹRAT����
    ucImsiPlmnListNum   SIM����Ŀ�����֧��16��
    ucForbidRatListNum  ��ֹRAT����Ŀ�����ֵ֧�� 8����Ŀǰ��֧��NV�����ý�ֹLTE���߽�ֹLTE+UTRAN��
                                                       NV������������ֹ������ʽ�������Ϊ�ǷǷ�������
    astImsiPlmnList     SIM���б����֧��16��
    aucForbidRatList    ��ֹ��RAT�����ֵ֧�� 2����Ŀǰ��֧��NV�����ý�ֹLTE���߽�ֹLTE+UTRAN��
                                                   NV������������ֹ������ʽ�������Ϊ�ǷǷ�������
                        0: GSM
                        1: UTRAN
                        2: E-UTRAN
                        ����ֵΪ��Чֵ
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8  enSwitchFlag;                                         /*�����Ƿ���Ч�����ܵ�����  */
    VOS_UINT8                                               ucImsiListNum;                                        /*������Ч��SIM����Ŀ(������/������)  */
    VOS_UINT8                                               ucForbidRatNum;                                       /*��ֹRAT����Ŀ  */
    VOS_UINT8                                               aucReserve[1];
    NAS_SIM_FORMAT_PLMN_ID                                  astImsiList[NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM];        /* SIM���б� (������/������) */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            aenForbidRatList[NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM];    /*��ֹ�Ľ��뼼��  */
}NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU
 �ṹ˵��  : NVIM���е�����csfb ��������gu��lai�ı䣬mm�Ƚ���lau�����Ƚ��к���
 1.��    ��   : 2012��8��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT8                           aucRserved[1];
}NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
 �ṹ˵��  : en_NV_Item_PLMN_EXACTLY_COMPARE_FLG NV��ṹ
  1.��    ��   : 2012��08��16��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������,�½��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;
    VOS_UINT8                           aucRsv[3];                         /* ����*/
}NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Hplmn_Register_Ctrl_Flg NV��ṹ
 1.��    ��   : 2012��11��29��
   ��    ��   : w00176964
   �޸�����   : HPLMNע�ᱻ�ܺ��Ƿ�����ע����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMNע����Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU;
/*****************************************************************************
�ṹ��    : NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU
�ṹ˵��  : �ź����������ϱ����������Ϣ
1.��    ��  : 2012��11��21��
  ��    ��  : z00161729
  �޸�����  : ֧��^cerssi�����ṹ
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSignThreshold;    /* �źű仯����,��RSSI�仯������ֵ��
                                                                                  �������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    VOS_UINT8                                               ucMinRptTimerInterval;     /* ����ϱ���ʱ��   */
    VOS_UINT8                                               ucRserved1;
    VOS_UINT8                                               ucRserved2;
} NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU
 �ṹ˵��  : en_NV_Item_H3g_Ctrl_Flg NV��ṹ
 1.��    ��   : 2013��4��10��
   ��    ��   : w00176964
   �޸�����   : H3G���Ƴ������Ʊ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucH3gCtrlFlg;                           /* H3G���Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU
 �ṹ˵��  : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUcs2Customization;
    VOS_UINT8                           ucRserved1;
    VOS_UINT8                           ucRserved2;
}NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU;

/*****************************************************************************
 �ṹ��    : SMS_TIMER_LENGTH_STRU
 �ṹ˵��  : ����Э�鶨ʱ��ʱ���ṹ

1. ��    ��   : 2012��12��28��
   ��    ��   : l00167671
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_NVIM_TIMER_LENGTH_STRU;


/*****************************************************************************
 �ṹ��    : NVIM_PRIVATE_CMD_STATUS_RPT_STRU
 �ṹ˵��  : �Ƿ������ϱ���Ϣ
 1.��    ��   : 2013��5��10��
   ��    ��   : s00217060
   �޸�����   : �����ϱ�AT�������������C����Ŀ�����ϱ�NV�ṹ�嶨��
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucStatusRptGeneralControl;        /* ˽�������Ƿ�����״̬�ϱ� 0:���ϱ���1:�ϱ� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NVIM_PRIVATE_CMD_STATUS_RPT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SPECIAL_ROAM_STRU
 �ṹ˵��  : en_NV_Item_Special_Roam_Flag NV��ṹ
  1.��    ��   : 2011��7��20��
    ��    ��   : z00161729
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ����  */
    VOS_UINT8                           ucSpecialRoamFlg;                         /* Vplmn��Hplmn��ͬ������ʱ,�Ƿ�����ص�Hplmn,1:����0:������ */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SPECIAL_ROAM_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU
 �ṹ˵��  : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnhancedHplmnSrchFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_TIMER_LEN_STRU
 �ṹ˵��  : NAS_CC_NVIM_TIMER_LEN_STRU�ṹen_NV_Item_CC_TimerLen
  1.��    ��   : 2013��8��30��
    ��    ��   : l00208543
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucT305Len;
    VOS_UINT8   ucT308Len;
    VOS_UINT8   aucReserve[2];
}NAS_CC_NVIM_TIMER_LEN_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_T303_LEN_CFG_STRU
 �ṹ˵��  : NAS_CC_NVIM_T303_LEN_CFG_STRU�ṹen_NV_Item_CC_T303_Len_Cfg
  1.��    ��   : 2015��3��20��
    ��    ��   : wx270776
    �޸�����   : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT303ActiveFlag;                       /* �Ƿ���T303��ʱ����0:�رգ�1:������*/
    VOS_UINT8                           ucT303Len;                              /* T303��ʱ��ʱ�� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_CC_NVIM_T303_LEN_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU
 �ṹ˵��  : �ṹ
  1.��    ��   : 2015��8��21��
    ��    ��   : s00217060
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucCmSrvExistTrigPlmnSearch;                                                     /* ҵ�����ʱ�Ƿ񴥷����� */
    VOS_UINT8   ucCmSrvTrigPlmnSearchCauseNum;                                                  /* ����ҵ�����ʱ���������ı���ԭ��ֵ���� */
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucCmSrvTrigPlmnSearchCause[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];   /* ����ҵ�����ʱ���������ı���ԭ��ֵ */
    VOS_UINT8   aucReserve[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];                    /* Ԥ����ע�ᱻ�ܴ�������ʹ�� */
}NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU
 �ṹ˵��  : �ṹ
  1.��    ��   : 2015��8��21��
    ��    ��   : s00217060
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucLauRejCauseNum;
    VOS_UINT8   ucLauRejTimes;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucLauRejCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
}NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU
 �ṹ˵��  : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU�ṹen_NV_Item_ChangeRejectCause_Flg
  1.��    ��   : 2013��10��09��
    ��    ��   : l00208543
    �޸�����   : �½�
  2.��    ��   : 2013��11��19��
    ��    ��   : l00208543
    �޸�����   : �޸ģ�������λ��Ϊö�٣����ӵ������
*****************************************************************************/
typedef struct
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8           enChangeRegRejCauCfg;
    VOS_UINT8   ucPreferredRegRejCau_HPLMN_EHPLMN;             /* HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   ucPreferredRegRejCau_NOT_HPLMN_EHPLMN;         /* ��HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   aucReserve[1];
}NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU
 �ṹ˵��  : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU�ṹen_NV_Item_ROAMING_REJECT_NORETRY_CFG
  1.��    ��   : 2014��4��29��
    ��    ��   : l00208543
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucNoRetryRejectCauseNum;
    VOS_UINT8   aucNoRetryRejectCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
    VOS_UINT8   aucReserve[3];
}NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU
 �ṹ˵��  : en_NV_Item_Remove_Auth_Rej_CFG NV��ṹ


 1.��    ��   : 2014��2��18��
   ��    ��   : l00215384
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
   VOS_UINT8                           ucIgnoreAuthRejFlg;
   VOS_UINT8                           ucMaxAuthRejNo;
   VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_GWMAC_ADDR_STRU
 �ṹ˵��  : NV_GWMAC_ADDR(39026)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved1;
    VOS_UINT8 aucE5GwMacAddr[18];
}NAS_NV_GWMAC_ADDR_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU
 �ṹ˵��  : E5_RoamingWhiteList_Support_Flg(39330)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucE5_RoamingWhiteList_Support_Flg[2];
}NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU
 �ṹ˵��  : NDIS_DIALUP_ADDRESS(39330)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNDIS_DIALUP_ADDRESS;
}NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NV_BREATH_LED_STR_STRU
 �ṹ˵��  : NV_BREATH_LED_STR(9051)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucBreOnTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreOffTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreRiseTime; /*Range:[0,5]*/
    VOS_UINT8 ucBreFallTime; /*Range:[0,5]*/
}NAS_NVIM_NV_BREATH_LED_STR_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NV_WIFI_Key_STRU
 �ṹ˵��  : NV_WIFI_Key(50012)�ṹ(����)
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
VOS_UINT8  aucwlAuthMode[16];
VOS_UINT8  aucBasicEncryptionModes[5];
VOS_UINT8  aucWPAEncryptionModes[5];
VOS_UINT8  aucwlKeys1[27];
VOS_UINT8  aucwlKeys2[27];
VOS_UINT8  aucwlKeys3[27];
VOS_UINT8  aucwlKeys4[27];
VOS_UINT32 ulwlKeyIndex;
VOS_UINT8  aucwlWpaPsk[65];
VOS_UINT8  ucwlWpsEnbl;
VOS_UINT8  ucwlWpsCfg;
VOS_UINT8  ucReserved;
}NAS_NVIM_NV_WIFI_KEY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NV_PRI_VERSION_STRU
 �ṹ˵��  : NV_PRI_VERSION(50023)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
VOS_UINT8 aucPRIVersion[32];
VOS_UINT8 aucReserve[32];
}NAS_NVIM_NV_PRI_VERSION_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_SYSTEM_APP_CONFIG_STRU
�ṹ˵��  : en_NV_Item_System_APP_Config(121)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSysAppConfigType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SYSTEM_APP_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU
�ṹ˵��  : en_NV_Item_NetworkCapability(8197)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNetworkCapability[NV_ITEM_NET_CAPABILITY_MAX_SIZE];
}NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_AUTOATTACH_STRU
�ṹ˵��  : en_NV_Item_Autoattach(8202)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAutoattachFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_AUTOATTACH_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_SELPLMN_MODE_STRU
�ṹ˵��  : en_NV_Item_SelPlmn_Mode(8214)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSelPlmnMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SELPLMN_MODE_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_ACCESS_MODE_STRU
�ṹ˵��  : en_NV_Item_MMA_AccessMode(8232)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAccessMode[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_ACCESS_MODE_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_MS_CLASS_STRU
�ṹ˵��  : en_NV_Item_MMA_MsClass(8233)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsClass;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_MS_CLASS_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_RF_Auto_Test_Flag_STRU
�ṹ˵��  : en_NV_Item_RF_Auto_Test_Flag(8262)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRfAutoTestFlg;
}NAS_MMA_NVIM_RF_AUTO_TEST_FLAG_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_HPLMN_FIRST_TIMER_STRU
�ṹ˵��  : en_NV_Item_HPlmnFirstTimer(8276)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnTimerLen;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}NAS_NVIM_HPLMN_FIRST_TIMER_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU
�ṹ˵��  : en_NV_Item_NAS_Supported_3GPP_Release(8288)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSupported3GppRelease[NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE];
}NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_LAST_IMSI_STRU
�ṹ˵��  : en_NV_Item_Last_Imsi(8325)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucValid;
    VOS_UINT8   aucImsi[NAS_MMC_NVIM_MAX_IMSI_LEN];
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_LAST_IMSI_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_ROAMING_BROKER_STRU
�ṹ˵��  : en_NV_Item_Roaming_Broker(8328)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucRoamingBroker[2];
}NAS_MMA_NVIM_ROAMING_BROKER_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU
�ṹ˵��  : en_NV_Item_Use_Single_Rplmn_When_Area_Lost(8343)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usUseSingleRplmnFlag;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU;

/* en_NV_Item_EquivalentPlmn 8215 */
/*****************************************************************************
�ṹ��    : NVIM_PLMN_VALUE_STRU
�ṹ˵��  : en_NV_Item_EquivalentPlmn(8215)�ṹ����#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_VALUE_STRU;

/*****************************************************************************
�ṹ��    : NVIM_EQUIVALENT_PLMN_LIST_STRU
�ṹ˵��  : en_NV_Item_EquivalentPlmn(8215)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8             ucCount;
    NVIM_PLMN_VALUE_STRU  struPlmnList[NVIM_MAX_EPLMN_NUM];
    VOS_UINT8             aucReserve[3];   /*NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն�*/
}NVIM_EQUIVALENT_PLMN_LIST_STRU;

/*en_NV_Item_Support_Freqbands 8229*/
/*
NVIM_UE_SUPPORT_FREQ_BAND_STRU�ṹ˵��:
usWcdmaBand��usGsmBand��Bitλ��ʾ�û����õ�Ƶ�Σ�bit1����Ƶ��I,bit2����Ƶ��II,
��������,����λΪ1,��ʾ֧�ָ�Ƶ��.�±��Ǳ���λ��Ƶ�ζ�Ӧ��ϵ:
-------------------------------------------------------------------------------
        bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
-------------------------------------------------------------------------------
WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
        spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
-------------------------------------------------------------------------------
GSMƵ�� 1900(VIII) 1800(VII) E900(VI) R900(V) P900(IV) 850(III)  480(II)  450(I)  oct3
        spare      spare     spare    spare   spare    spare     spare    700(IX) oct4
-------------------------------------------------------------------------------
aucUeSupportWcdmaBand��aucUeSupportGsmBand�������ʾUE֧�ֵ�Ƶ��,���Դ洢˳���
�Ⱥ��ʾƵ������˳��,��0xff��ʾ��Ч.

����:
oct1-oct4�ֱ��ǣ�0x03,0x00,0x7B,0x00
   ������û�����Ƶ��Ϊ��W��WCDMA-I-2100, WCDMA-II-1900
                         G��850(III),P900(IV),R900(V),E900(VI),1800(VII)
oct5-oct16�ֱ���:2,5,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��WƵ��I,II,V,����˳����:II,V,I.
oct17-oct28�ֱ���:4,5,8,7,6,3,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��GƵ��III,IV,V,VI,VII,VIII,����˳����:IV,V,VIII,VII,VI,III.
*/
/*****************************************************************************
�ṹ��    : NAS_NVIM_UE_SUPPORT_FREQ_BAND_STRU
�ṹ˵��  : en_NV_Item_Support_Freqbands(8229)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2014��8��1��
  ��    ��   : b00269685
  �޸�����   : NV���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT32                  ulGsmBand;
    VOS_UINT8                   aucReserved1[12];
    VOS_UINT8                   aucReserved2[12];
    VOS_UINT8                   aucReserved[24];        /* Ϊ��֤nv����һ�±��� */
}NVIM_UE_SUPPORT_FREQ_BAND_STRU;

/*en_NV_Item_Roam_Capa 8266*/
/*****************************************************************************
 �ṹ��    : NAS_NVIM_ROAM_CFG_INFO_STRU
 �ṹ˵��  : en_NV_Item_Roam_Capa(8266) NV��ṹ#
  1.��    ��   : 2011��8��18��
    ��    ��   : z00161729
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*��¼���������Ƿ񼤻�,VOS_FALSE:������,VOS_TRUE:����*/
    VOS_UINT8                               ucRoamCapability;                   /*��¼�û����õ���������*/
    VOS_UINT8                               ucReserve1;
    VOS_UINT8                               ucReserve2;
}NAS_NVIM_ROAM_CFG_INFO_STRU;

/*en_NV_Item_CustomizeService 8271*/
/*****************************************************************************
�ṹ��    : NAS_NVIM_CUSTOMIZE_SERVICE_STRU
�ṹ˵��  : en_NV_Item_CustomizeService(8271)�ṹ#
            ���ڱ�����Ӫ�̶���Ҫ��ҵ������
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;           /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                          ulCustomizeService; /*�ն�˵������1��byte��Ϊ��û�пն��������4byte����3byte����*/
}NAS_NVIM_CUSTOMIZE_SERVICE_STRU;

/*en_NV_Item_RPlmnWithRat 8275*/
/*****************************************************************************
 �ṹ��    : NAS_MM_NVIM_RPLMN_WITH_RAT_STRU
 �ṹ˵��  : en_NV_Item_RPlmnWithRat(8275) NV��ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stGRplmn;                               /* G RPLMN��Ϣ */
    NAS_NVIM_PLMN_ID_STRU               stWRplmn;                               /* W RPLMN��Ϣ*/
    VOS_UINT8                           ucLastRplmnRat;                         /* �ϴιػ�ʱפ������Ľ��뼼��0:GSM;1:WCDMA;0xFF:��Чֵ */
    VOS_UINT8                           ucLastRplmnRatEnableFlg;                /* 0:NV δ����; 1:NV���� */
    VOS_UINT8                           aucReserved[2];                          /* ���� */
}NAS_NVIM_RPLMN_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU
 �ṹ˵��  : en_NV_Item_SearchHplmnTtimerValue NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;                              /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                            ucReserve;                             /* ����δ�� */
    VOS_UINT16                           usSrchHplmnTimerValue;                 /* VPLMN�·��״���HPLMNʱ��,��λ:���� */

}NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG NV��ṹ
 1.��    ��   : 2015��4��28��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTriggerBGSearchFlag;  /* 0: mmc�յ������ȼ�PLMN����ʱ������BG SEARCH; 1:mmc�յ������ȼ�PLMN����ʱ����BG SEARCH */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usSearchDelayLen;             /* BG SEARCH Delay ʱ��, ��λ: ��  */
}NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */


/*en_NV_Item_EFust_Service_Cfg 8285*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU
 �ṹ˵��  : en_NV_Item_EFust_Service_Cfg(8285) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV���Ƿ񼤻�0��δ���1������ */
    VOS_UINT8                           ucForbidReg2GNetWork;                   /* 0��EFust GSM�����־������ȥʹ�ܡ��������������EFust 27��38������GSM���롣
                                                                                   �������ö�������UE����SIM���е�EFust 27��38λ��ȷ���Ƿ�����GSM���룬
                                                                                   ���EFUST�ļ���ֹ����λ��ͬʱ����Ϊ0�������ֹGSM����ע�ᣬ����GSM���Խ��롣
                                                                                   ע�⣺SIM���в�����EFust 27��38λ����˸ù��ܽ����USIM����Ч��1��EFust GSM�����־������ʹ�� */
    VOS_UINT8                           ucForbidSndMsg;                         /* 0��EFust���ŷ��ͱ�־������ȥʹ�ܡ��������������EFust 10��12������SMS���͡�
                                                                                   1��EFust���ŷ��ͱ�־������ʹ�ܡ�NV���ö�������UE����SIM����EFUST��10��12λ��
                                                                                   ȷ���Ƿ��ֹ���ŷ���,�����ֹ����λ��ͬʱ����Ϊ0�������ֹ����SMS�����򣬶��ſ��Է��͡�*/
    VOS_UINT8                           ucReserved[13];
}NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU;

/*en_NV_Item_UE_MSCR_VERSION 8289*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_MSCR_VERSION_STRU
 �ṹ˵��  : en_NV_Item_UE_MSCR_VERSION(8289) NV��ṹ
 1.��    ��   : 2011��7��14��
   ��    ��   : z00161729
   �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeMscrVersion;                        /* �ն��ϱ���SGSN�汾 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MSCR_VERSION_STRU;

/*en_NV_Item_UE_SGSNR_VERSION 8290*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SGSNR_VERSION_STRU
 �ṹ˵��  : en_NV_Item_UE_SGSNR_VERSION(8290) NV��ṹ
 1.��    ��   : 2011��7��14��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeSgsnrVersion;                       /* �ն��ϱ���SGSN�汾 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SGSNR_VERSION_STRU;

/*en_NV_Item_SteeringofRoaming_SUPPORT_CTRL 8292*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU
 �ṹ˵��  : en_NV_Item_SteeringofRoaming_SUPPORT_CTRL(8292) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucCsRejSearchSupportFlg;                /* vodafone��������������,CS��ʧ���Ĵκ��·���������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
}NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU;

/*en_NV_Item_Max_Forb_Roam_La 8320*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU
 �ṹ˵��  : en_NV_Item_Max_Forb_Roam_La(8320) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxForbRoamLaFlg;                     /* NV�����õ�����ֹLA�����Ƿ���Ч: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucMaxForbRoamLaNum;                     /* NV�����õ�����ֹLA���� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU;

/*en_NV_Item_Default_Max_Hplmn_Srch_Peri 8321*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU
 �ṹ˵��  : en_NV_Item_Default_Hplmn_Srch_Peri(8321) NV��ṹ
  1.��    ��   : 2011��7��20��
    ��    ��   : z00161729
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDefaultMaxHplmnPeriFlg;               /* Ĭ������HPLMN���������Ƿ���Ч��־,VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucDefaultMaxHplmnTim;                   /* �û����Զ���Ĭ�ϵ�����HPLMN�������� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU;

/*en_NV_Item_USSD_Apha_To_Ascii 8327*/
/*����USSDת���ַ���*/
/*****************************************************************************
 �ṹ��    : NAS_SSA_NVIM_ALPHA_to_ASCII_STRU
 �ṹ˵��  : en_NV_Item_USSD_Apha_To_Ascii(8327) NV��ṹ
  1.��    ��   : 2011��7��20��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                       ucAlphaTransMode;    /* �ַ���ת��*/
}NAS_SSA_NVIM_ALPHA_to_ASCII_STRU;

/*en_NV_Item_Register_Fail_Cnt 8338*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REG_FAIL_CNT_STRU
 �ṹ˵��  : en_NV_Item_Register_Fail_Cnt(8338) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvActiveFlag;                         /* ��ǰNV���Ƿ񼤻� */
    VOS_UINT8                           ucRegFailCnt;                           /* NV�����õ�ע��ʧ�ܵĴ�����Ĭ��ֵΪ2����ע��ʧ�����κ��������� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_REG_FAIL_CNT_STRU;

/*en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt 8345*/
/* VDF����: CREG/CGREG����<CI>���Ƿ���4�ֽ��ϱ���NV����ƽṹ�� */
/*****************************************************************************
�ṹ��    : NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU
�ṹ˵��  : en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt(8345)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                        /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucCiBytesRpt;                    /* <CI>���ϱ��ֽ�����־��0��2�ֽ��ϱ�, 1��4�ֽ��ϱ� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item__Dell_Reject_Config NV�����ݣ����ű���11,12,13,15,other cause,����ʧ��,����û��Ӧ��ԭ����NV
 1.��    ��   : 2012��3��6��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* ���ű����Ƿ�ʹ�� VOS-TRUE:���ű���֧�� VOS_FALSE:���ű��ܲ�֧�� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU;

/* en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME 8344 */
typedef struct
{
    VOS_UINT32                          ulDhcpLeaseHour;    /*Range:[0x1,0x2250]*/
}NDIS_NV_DHCP_LEASE_HOUR_STRU;

typedef struct
{
    VOS_UINT32                          ulIpv6Mtu;          /*Range:[1280,65535]*/
}NDIS_NV_IPV6_MTU_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU
�ṹ˵��  : en_NV_Item_CCallState_Rpt_Status nvid 9116(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
 �ṹ˵��  : PLMN�Ƚ��Ƿ���о�ȷ�Ƚϵķ�ʽ�ı��
 �޸���ʷ  :
 1.��    ��    : 2012��08��7��
   ��    ��    : l00128652
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucPlmnExactlyCompareFlag;               /* PLMN�Ƚ��Ƿ���о�ȷ�Ƚϵķ�ʽ�ı�� */
   VOS_UINT8                            aucRsv[3];                              /* ����λ */
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
�ṹ��    : PLATFORM_RAT_TYPE_ENUM
�ṹ˵��  : ���뼼��

  1.��    ��   : 2012��12��25��
    ��    ��   : z00220246
    �޸�����   : ����
*******************************************************************************/
enum PLATFORM_RAT_TYPE_ENUM
{
    PLATFORM_RAT_GSM,                                                       /*GSM���뼼�� */
    PLATFORM_RAT_WCDMA,                                                     /* WCDMA���뼼�� */
    PLATFORM_RAT_LTE,                                                       /* LTE���뼼�� */
    PLATFORM_RAT_TDS,                                                       /* TDS���뼼�� */
    PLATFORM_RAT_1X,                                                        /* CDMA-1X���뼼�� */
    PLATFORM_RAT_HRPD,                                                      /* CDMA-EV_DO���뼼�� */

    PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 PLATFORM_RAT_TYPE_ENUM_UINT16;

#define PLATFORM_MAX_RAT_NUM            (7)                                    /* ���뼼�����ֵ */

/*****************************************************************************
�ṹ��    : PLATAFORM_RAT_CAPABILITY_STRU
�ṹ˵��  : ƽ̨֧�ֵĽ��뼼��

  1.��    ��   : 2012��12��25��
    ��    ��   : z00220246
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                              /* ���뼼������Ŀ*/
    PLATFORM_RAT_TYPE_ENUM_UINT16        aenRatList[PLATFORM_MAX_RAT_NUM];  /* ���뼼�� */
}PLATAFORM_RAT_CAPABILITY_STRU;

/*en_NV_Item_Rplmn 8216*/
/*****************************************************************************
 �ṹ��    : NAS_NVIM_RPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_Rplmn(8216) NV��ṹ(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRplmnInfo[56];
}NAS_NVIM_RPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : SVLTE_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_SVLTE_FLAG NV��ṹ
 1.��    ��   : 2013��6��20��
   ��    ��   : z00161729
   �޸�����   : SVLTE�����Ƿ�֧��:0-��֧�֣�1-֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvlteSupportFlag;                     /* SVLTE�����Ƿ�֧��:0-��֧�֣�1-֧�� */
    VOS_UINT8                           aucReserved[3];                         /* ���� */
}SVLTE_SUPPORT_FLAG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU
 �ṹ˵��  : en_NV_Item_Enable_Lte_Timer_Len NV��ṹ
 1.��    ��   : 2013��6��3��
   ��    ��   : z00161729
   �޸�����   : enable lte��ʱ��ʱ��
 2.��    ��   : 2015��4��24��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv��δ���1:nv��� */
    VOS_UINT8                           ucCsPsMode1EnableLteTimerLen;           /* 1)cs ps mode1 L����ע��eps only�ɹ�cs����#16/#17/#22������������disable lteʱ����enable lte��ʱ��ʱ��
                                                                                   2)cs ps mode1 L����ע��cs eps��ʧ��ԭ��ֵother cause ������������disable lte����enable lte��ʱ��ʱ��,��λ:���ӣ� nv���ʱ���Ϊ0Ĭ��54���� */
    VOS_UINT8                           ucCsfbEmgCallEnableLteTimerLen;         /* L�½��������޷�����csfb��gu��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���ӣ� nv���ʱ���Ϊ0Ĭ��5���� */

    /* ����ԭ��ֵΪ#16��#17��#18������ע��ɹ���Additional Update Result IE��Ϣ��
    ָʾSMS Only��CSFB Not Preferred��Ҫdisable lteʱ�����Э��汾���ڵ���R11��
    ���ñ��ܾ���PLMN��RAT��¼�ڽ�ֹ���뼼�������б��еĳͷ�ʱ�䣬���Ϊ0xFF��ʾ���óͷ�
    ��λ:���� */
    VOS_UINT8                           ucLteVoiceNotAvailPlmnForbiddenPeriod;
}NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU;


/* Added by c00318887 for ��ֲT3402 , 2015-6-17, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU
 �ṹ˵��  : en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG NV��ṹ
             ucT3402Flag ��������Disable LTE ���ٴΰ�LTE �ָ�����Ķ�ʱ��ʱ��:
             ���ucT3402Flag ��0����Disable LTE ���ٴΰ�LTE �ָ�����Ķ�ʱ��ʱ����NV_Item_Enable_Lte_Timer_Len  0x2404��9220������ֵ����
             ��� ucT3402Flag ����Ϊ 1�������³�����ʹ��LMM_MMC_T3402_LEN_NOTIFY��Ϣ�еĳ���
            1) EPS ONLY�ɹ�,CS����18,CS����16,17,22,other cause,EPS���Դ����ﵽ5��
            2) ����EPSע�ᱻ�� #19, �����ﵽ���ֵ
            3) ����EPSע�ᱻ�� #301, �����ﵽ���ֵ
            4) ����EPSע�ᱻ�� #other cause, �����ﵽ���ֵ
            5) ����EPSע�ᱻ�� #401, �����ﵽ���ֵ
 1.��    ��   : 2015��4��28��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT3402Flag;                           /* 0: ��ʹ��LMM_MMC_T3402_LEN_NOTIFY��Ϣ�еĳ���; 1:ʹ��LMM_MMC_T3402_LEN_NOTIFY��Ϣ�еĳ��� */
    VOS_UINT8                           ucHighPrioRatTimerNotEnableLteFlag;    /* 1:�����ȼ�RAT HPLMN TIMER ��ʱ������ENABLE lte��0: �����ȼ�RAT HPLMN TIMER ��ʱ����ENABLE lte */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU;

/* Added by c00318887 for ��ֲT3402 , 2015-6-17, end */


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REJ_MAX_TIMES_DISABLE_LTE_CFG_STRU
 �ṹ˵��  : lte attach and tau ���ܴ�������ʱ���Ƿ���R12Э��disable lte

  1.��    ��   : 2016��8��24��
    ��    ��   : c00318887
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRejMaxTimesDisableLte;          /* 0: ���ܴ�������ʱ������r12�汾disable lte; 1: ���ܴ�������ʱ����r12�汾disable lte */
    VOS_UINT8                           ucReserved1;                            
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_REJ_MAX_TIMES_DISABLE_LTE_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_NVIM_SRVCC_SN_MODULO_CFG_STRU
 �ṹ˵��  : SRVCC��G�º��Ƿ���Э�飬����SNͳһ����R99ģ4����

  1.��    ��   : 2016��9��1��
    ��    ��   : n00269697
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /* ����24007 11.2.3.2.3.1.1
       after successful completion of SRVCC handover (see 3GPP TS 23.216 [27]),
       the mobile station shall perform modulo 4 arithmetic operations on V(SD).
       The mobile station shall keep using modulo 4 until the release of the RR
       connection established at SRVCC handover.

       During SRVCC handover the MSCR bit is not provided to the mobile station,
       and therefore the mobile station assumes to access to a Release 99 or
       later core network.
    */
    VOS_UINT8                           ucSrvccSnModuloCfg;                     /* 0: ����SN����SRVCCǰg_stMmNsd.ucNsdMod����; 1: ����Э�飬����SNͳһ����R99ģ4���� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_SRVCC_SN_MODULO_CFG_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_ISR_CFG_STRU
�ṹ˵��  : ISR���������Ϣ
1.��    ��  : 2013��05��23��
  ��    ��  : z00234330
  �޸�����  : ISRͨ��NVIM�ж��Ƿ�֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsrSupport;       /* ISR ???? */
    VOS_UINT8                                               ucReserve1;
} NAS_NVIM_ISR_CFG_STRU;


/*****************************************************************************
 �ṹ��    : CSFB_MT_FOLLOW_ON_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_CSFB_MT_RAU_FOLLOW_ON_FLAG NV��ṹ
 1.��    ��   : 2013��7��25��
   ��    ��   : w00242748
   �޸�����   : Csfb mt�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ
 2.��    ��   : 2014��6��10��
   ��    ��   : w00242748
   �޸�����   : Csfb mo�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg;           /* Csfb mt�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg;           /* Csfb mo�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU
 �ṹ˵��  : en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG NV��ṹ
  ����˵��: ����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ���ǰ֧�ֵĲ���Ϊ��
  1)  ͨ����һModem��PLMN��Ϣ,����FDD�����Ƿ������Ĳ��ԡ�����GUTL+G�İ汾���������Ѿ�פ���ڹ���G����ʱ������������������FDD�����������ƶ�����ֻ��Ҫ֧��TDDģʽ����
  2)  ͨ��Modem1��GSM�ϱ���L��TDS������Ϣ, Modem0��֧��GSM������£�T/L�������ܹ����ݴ��ݵ�����Ƶ�����������TDS/LTE��
 1.��    ��   : 2013��11��18��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usSolutionMask;/*����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ�Bitλ���Ƹ����������ԣ�bitn=0����n�����Թرգ�bitn=1����n�����Կ�����
                                                         Ŀǰֻ��bit0��bit1 ��Ч��
                                                         BIT0������˫Modem��ͨ����һModem��PLMN��Ϣ����FDD�����Ƿ������Ĳ����Ƿ�������
                                                         BIT1��ͨ��Modem1��GSM�ϱ���L��TDS������Ϣ, Modem0��֧��GSM������£�T/L�������ܹ����ݴ��ݵ�����Ƶ�����������TDS/LTE��
                                                               ���Modem1���ݹ�����������Ϣ�����ڵ�����£�Ҳ��ͨ����ʷƵ��֧��NCELL������������������Ƶ����ucSolution2NcellSearchTimer������
                                                         BIT2~BIT15:Ԥ��*/
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer;       /*����Ƶ������������Ե�һ�׶�ʱ��������λ�룩��*/

   VOS_UINT8                            ucSolution2NcellQuickSearchTimer2;      /* ����Ƶ������������ԵĶ��׶�ʱ��������λ�룩��*/
   VOS_UINT8                            aucAdditonCfg[4];
}NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;


/*****************************************************************************
�ṹ��    : NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU
�ṹ˵��  : en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT(9140)�ṹ
1.��    ��   : 2014��01��13��
  ��    ��   : l65478
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucRelFlg;
    VOS_UINT8   ucReserve;
}NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_WG_RF_MAIN_BAND_STRU
�ṹ˵��  : en_NV_Item_WG_RF_MAIN_BAND�ṹ
  1.��    ��   : 2014��02��10��
    ��    ��   : f62575
    �޸�����   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND�����޸�Ϊ���ڴ��л�ȡ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWband;                                /* ֧�ֵ�WCDMA����ͨ· */
    VOS_UINT32                          ulWbandExt;                             /* ֧�ֵ�WCDMA����ͨ·��չ�ֶ� */
    VOS_UINT32                          ulGband;                                /* ֧�ֵ�GSM����ͨ· */
}NAS_NVIM_WG_RF_MAIN_BAND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT
 �ṹ˵��  : en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT NV��ṹ
 1.��    ��   : 2013��12��16��
   ��    ��   : f00261443
   �޸�����   : ISR����״̬�£���L��ϵͳ��GU�����LAI��RAIδ�����仯���Ƿ���Ҫ
                ����LAU����RAU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;           /* ISR�������ϵͳ��L�任��GU��LAIδ�ı䣬�Ƿ���Ҫǿ��LAU */
    VOS_UINT8                           ucImsVoiceMMEnable;         /* IMS�ƶ��Թ��� NV */
    VOS_UINT8                           aucReserved[2];             /* ���� */
}NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT;

/*****************************************************************************
�ṹ��    : NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU
�ṹ˵��  : en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG�ṹ
  1.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;             /* l disabled��rau�Ƿ���Ҫ��l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ��vos_true:��Ҫ��ȡ��vos_false:�����ȡ*/
    VOS_UINT8                           ucReserved[3];
}NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU;


/*****************************************************************************
�ṹ��    : NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU
�ṹ˵��  : en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG�ṹ
  1.��    ��   : 2014��02��13��
    ��    ��   : f62575
    �޸�����   : DTS2014012902032:
                 NV��en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* �Ƿ񼤻�� */
    VOS_UINT8                           ucCsOnlyDataServiceSupportFlg;          /* PSע�ᱻ��ֹ����£��Ƿ���������ҵ�񴥷�ע��ı�־ */
}NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_INFO NV��ṹ
 1.��    ��   : 2014��2��19��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2014��10��25��
   ��    ��   : b00269685
   �޸�����   : ��NV�ѷ�������������ֻ��Ϊ�˱���ͨ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /* �ö�ʱ���Ƿ�ʹ�� */                       /* TD��ʼ�����ѵĴ��� */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG NV��ṹ
 1.��    ��   : 2014��10��25��
   ��    ��   : b00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                            /* �ö�ʱ���Ƿ�ʹ�� */
    VOS_UINT8                           ucTdThreshold;                          /* TD��ʼ�����ѵĴ��� */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_Ultra_Flash_Csfb_Support_Flg NV��ṹ
 1.��    ��   : 2014��5��30��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUltraFlashCsfbSupportFLg;                 /* �Ƿ�֧��ultra flash csfb */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_3GPP2_Uplmn_Not_Pref_STRU
 �ṹ˵��  : en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg NV��ṹ
 1.��    ��   : 2014��6��13��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc3GPP2UplmnNotPrefFlg;                    /* �Ƿ���3GPP2 pref plmn */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg NV��ṹ
 1.��    ��   : 2014��7��14��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHighPrioRatPlmnSrchFlg;                  /* �Ƿ��������ȼ����뼼������ */
    VOS_UINT8                           aucReserved1[3];
}NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU
 �ṹ˵��  : en_NV_Item_DSDS_END_SESSION_DELAY NV��ṹ
 1.��    ��   : 2014��7��17��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;              /* Lau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;              /* Rau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulReserve1;
    VOS_UINT32                           ulReserve2;
} NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SYSTEM_STRU
 �ṹ˵��  : 1x system�ṹ
 1.��    ��   : 2014��8��18��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usChannel;
}CNAS_NVIM_1X_SYSTEM_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_NVIM_1X_MRU_LIST_STRU
 �ṹ˵��  : en_NV_Item_1X_MRU_LIST NV��ṹ
 1.��    ��   : 2014��8��18��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_SYSTEM_STRU            astSystem[CNAS_NVIM_MAX_1X_MRU_SYS_NUM];
}CNAS_NVIM_1X_MRU_LIST_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_TEST_CONFIG_STRU
 �ṹ˵��  : en_NV_Item_1X_TEST_CONFIG NV��ṹ
 1.��    ��   : 2015��5��11��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReadNvPrlDirectly;
    VOS_UINT8                           ucReadDefaultPrl;        /* ��ȡDefault Prl */
    VOS_UINT8                           ucIsMod1xAvailTimerLen;
    VOS_UINT8                           ucNvPrlCombinedFlag;     /* NV PRL������־ */
    VOS_UINT8                           aucReserve[12];

}CNAS_NVIM_TEST_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_CALLBACK_CFG_STRU
 �ṹ˵��  : en_Nv_Item_CNAS_XSD_CALLBACK_CFG NV��ṹ
 1.��    ��   : 2015��7��2��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} CNAS_NVIM_1X_CALLBACK_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_ADD_AVOID_FREQ_CFG_STRU
 �ṹ˵��  : en_NV_Item_1X_ADD_AVOID_CHAN_CFG NV��ṹ
 1.��    ��   : 2015��6��5��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsNegSysAdd;
    VOS_UINT8                           aucReserve[15];
}CNAS_NVIM_1X_ADD_AVOID_LIST_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU
 �ṹ˵��  : en_NV_Item_1X_NEG_PREF_SYS_CMP_CTRL NV��ṹ
 1.��    ��   : 2015��6��5��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8           enNegPrefSysCmpType;
    VOS_UINT8                                               aucReserve[15];
}CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_CALL_NVIM_CFG_STRU
 �ṹ˵��  : en_NV_Item_1X_CALL_NVIM_CFG_CTRL NV��ṹ
 1.��    ��   : 2015��6��15��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsL3ErrReOrigCount;
    VOS_UINT8                                               ucPrivacyMode;      /* privacy mode flag: 0 - disable 1 - enable */

    VOS_UINT8                                               aucReserve[14];
}CNAS_NVIM_1X_CALL_NVIM_CFG_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ն�֧�ֵ�Ƶ����������  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* �ն�֧�ֵ�Ƶ���������룬ÿbit��ʾ�Ƿ�֧�ֶ�Ӧ��Ƶ������������0x00000001��ʾֻ֧��Ƶ��0 */
}CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ն�֧�ֵ�Ƶ����������  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* �ն�֧�ֵ�Ƶ���������룬ÿbit��ʾ�Ƿ�֧�ֶ�Ӧ��Ƶ������������0x00000001��ʾֻ֧��Ƶ��0 */
}CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_AVOID_PHASE_STRU
 �ṹ˵��  : avoid������Ϣ
  1.��    ��   : 2016��03��02��
    ��    ��   : x00306642
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausAvoidTimerLen[CNAS_NVIM_HRPD_AVOID_MAX_PHASE_NUM];
}CNAS_NVIM_HRPD_AVOID_PHASE_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_AVOID_SCHEDULE_INFO_STRU
 �ṹ˵��  : avoid������Ϣ
  1.��    ��   : 2016��03��02��
    ��    ��   : x00306642
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_HRPD_AVOID_PHASE_STRU     astAvoidPhaseNum[CNAS_NVIM_HRPD_AVOID_REASON_MAX];
}CNAS_NVIM_HRPD_AVOID_SCHEDULE_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_MMC_NVIM_ADAPTION_CAUSE_STRU
ʹ��˵��    :�û���������ԭ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnCause;     /* ����ԭ��ֵ */
    VOS_UINT8                           ucHplmnCause;  /* �û�����ƥ��HPLMN��ԭ��ֵ */
    VOS_UINT8                           ucVplmnCause;  /* �û�����ƥ��VPLMN��ԭ��ֵ */
    VOS_UINT8                           aucReserved[1];
}NAS_MMC_NVIM_ADAPTION_CAUSE_STRU;

/*****************************************************************************
�ṹ����    :NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU
ʹ��˵��    :en_NV_Item_ChangeNWCause_CFG NV��ṹ
*****************************************************************************/
typedef struct
{
    /* CS��ע������(LU)�ܾ�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucCsRegCauseNum;
    VOS_UINT8                           aucReserved1[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* PS��ע������(ATTACH/RAU)�ܾ�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucPsRegCauseNum;
    VOS_UINT8                           aucReserved2[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* ����GPRS Detach ���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucDetachCauseNum;
    VOS_UINT8                           aucReserved3[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astDetachAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* GMM service request���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucPsSerRejCauseNum;
    VOS_UINT8                           aucReserved4[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* MM ABORT���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucMmAbortCauseNum;
    VOS_UINT8                           aucReserved5[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astMmAbortAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* CM Service���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucCmSerRejCauseNum;
    VOS_UINT8                           aucReserved6[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCmSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    VOS_UINT8                           ucHplmnPsRejCauseChangTo17MaxNum; /* HPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucHplmnCsRejCauseChangTo17MaxNum; /* HPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucVplmnPsRejCauseChangTo17MaxNum; /* VPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucVplmnCsRejCauseChangTo17MaxNum; /* VPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
}NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU
 �ṹ˵��  : en_NV_Item_REL_PS_SIGNAL_CON_CFG NV��ṹ
 1.��    ��   : 2014��11��04��
 ��    ��   : h00285180
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRelPsSignalConFlg;/* �Ƿ�������������������� */

    VOS_UINT8                           ucPdpExistNotStartT3340Flag; /* rau��attach���󲻴�follow on������ظ�attach accept��rau acceptҲ����follow on������pdp�����ĳ����Ƿ���Ҫ����T3340,0:��Ҫ����T3340; 1:����Ҫ���� */
    VOS_UINT8                           aucReserved[2];

    VOS_UINT32                          ulT3340Len;         /* ���õ�GMM T3340��ʱ��,��λ:�� */
}NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU
 �ṹ˵��  : en_NV_Item_WCDMA_VOICE_PREFER_CFG�ṹ
  1.��    ��   : 2014��12��26��
    ��    ��   : s00273135
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucEnableFlag;/*ʹ�ܿ��� */
    VOS_UINT8   aucReserve[3];
    VOS_UINT32  ulMcc;    /*���ڲ���ʹ��ָ��MCC*/
    VOS_UINT32  ulMnc;    /*���ڲ���ʹ��ָ��MNC*/
}NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU;
/*****************************************************************************
 �ṹ��    : NAS_NV_TRI_MODE_ENABLE_STRU
 �ṹ˵��  : en_NV_Item_TRI_MODE_ENABLE NV��ṹ
 1.��    ��   : 2015��01��04��
 ��    ��   : z00306637
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEnable;                          /* ȫ��ͨ���Կ��� */
    VOS_UINT16                              usReserved;
}NAS_NV_TRI_MODE_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU
 �ṹ˵��  : en_NV_Item_TRI_MODE_FEM_PROFILE_ID NV��ṹ
 1.��    ��   : 2015��01��04��
 ��    ��   : z00306637
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulProfileId;                        /* ����ʹ�ó���������ǰ�����������µ磨ABB��TCXO��RF���Լ�RFͨ���Ŀ��ơ�
                                                                                   ��AT�����·����á�Ĭ��ֵΪ0��ȡֵ��Χ0-7�� */
    VOS_UINT32                              ulReserved[3];                     /* ������������չʹ�� */
}NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU;



/*****************************************************************************
�ṹ��    : NAS_NV_MODE_BASIC_PARA_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2014��12��30��
    ��    ��   : z00306637
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usABBSwitch;                       /* ����ABB PLL���صĿ��ơ�0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1���� */
    VOS_UINT16                              usRFSwitch;                        /* ����RFIC��Դ���صĿ��ơ�0:RFICʹ��MIPI0���ƹ��緽ʽ 1��RFICʹ��MIPI1���ƹ��緽ʽ 2��ͬʱ����·��Դ��*/
    VOS_UINT16                              usTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              usReserved;                        /* ������������չʹ�� */
}NAS_NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_TRI_MODE_CHAN_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ��ͨͨ���������ò���  (���ܸı�)
*****************************************************************************/
typedef struct
{
    NAS_NV_MODE_BASIC_PARA_STRU            stModeBasicPara[2];                  /* �±�[0]:��ʾGSMģʽ�µ�ǰ�����������µ���ơ�
                                                                                   �±�[1]:��ʾWCDMAģʽ�µ�ǰ�����������µ���ơ�
                                                                                    ע������ʱ����ʹ��WCDMAģʽ�����á�*/
    VOS_UINT32                              ulRfSwitch;                         /* ���ڿ��ƹ��ּ��Ŀ��� */
    VOS_UINT32                              ulGsmRficSel;                       /* ����ģʽ�µ�ǰʹ�õ�ͨ����0��RF0,1��RF1�� */
    VOS_UINT32                              ulGpioCtrl;                         /* gpio */
    VOS_UINT32                              aulReserved[14];                    /* ������������չʹ�� */
}NAS_NV_TRI_MODE_CHAN_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 8�ֳ�����ͨ������
*****************************************************************************/
typedef struct
{
    NAS_NV_TRI_MODE_CHAN_PARA_STRU          stPara[NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* ���֧��8������������ */
}NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU;





/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU
 �ṹ˵��  : en_NV_Item_CSMO_SUPPORTED_Cfg_Info NV��ṹ
 1.��    ��   : 2015��3��03��
   ��    ��   : w00167002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU
 �ṹ˵��  : en_NV_Item_Roam_Display_Cfg NV��ṹ
 1.��    ��   : 2015��3��20��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_MT_CSFB_PAGING_PROCEDURE_LEN_STRU
 �ṹ˵��  : en_NV_Item_Mt_Csfb_Paging_Procedure_Len NV��ṹ
 1.��    ��   : 2015��5��4��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMtCsfbPagingProcedureLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU
 �ṹ˵��  : en_NV_Item_Roam_Plmn_Selection_Sort_Cfg NV��ṹ
 1.��    ��   : 2015��6��02��
   ��    ��   : W00167002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    VOS_UINT8                           ucSrchUOplmnPriorToDplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU
 �ṹ˵��  : ���׶ζ�ʱ��
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �½�

    NV ����˵��:
    ucHistoryNum        �ڼ��ε���ʷ�� ���� PrefBand/FullBand��
    ucPrefBandNum       �ڼ��ε�PrefBand�� ���� FullBand��
    ucFullBandNum       �ڼ���FullBand����, �˽׶ν���, ������һ�׶�

    ������
        ��һ�׶β�����
        Timerlen = 2sec
        ucHistoryNum            = 2
        ucPrefBandNum           = 2
        ucFullBandNum           = 1
         -> TotalLen            = 2*2*2 = 8
        �ڶ��׶β�����
        Timerlen = 4sec
        ucHistoryNum            = 1
        ucPrefBandNum           = 2
        ucFullBandNum           = Null (1 or 100 û��, ����һ���׶ε�full band)
         -> TotalLen            = 1*2*4 = 8

        ͼʾ��
        OOC:_H_P_H_F|__P__F__P__F__P__F__P__F ...

        ����ĳ�С춵��:
        OOC:_H_H_P_H_H_P_H_H_F|__H__P__H__P__H__F
        TotalLen = (2+1)*(2+1)*2sec = 18sec (FullBand)

        ��һ�׶�
        CASE#1:
        ucHistoryNum            = 2
        ucPrefBandNum           = 2
        ucFullBandNum           = 0
        OOC:_H_H_P_H_H_P|
        TotalLen = (2+1)*2sec = 6 (PrefBand)

        CASE#2:
        ucHistoryNum            = 2
        ucPrefBandNum           = 0
        ucFullBandNum           = 0
        OOC:_H_H|
        TotalLen = Timerlen     = 2sec (PrefBand)

        CASE#3:
        ucFullBandNum           = 0
        ucPrefBandNum           = 0
        ucHistoryNum            = 0
        ����Ԥ��ֵucFullBandNum = 1
        OOC:_F|

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimerLen;                        /* ���׶�������ʱ��,��λ:s */
    VOS_UINT16                          usSleepTimerLen;                        /* ���������˯��ʱ��,��λ:s */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucHistoryNum;                           /* �ڼ��ε���ʷ�� ���� PrefBand/FullBand�� */
    VOS_UINT8                           ucPrefBandNum;                          /* �ڼ��ε�PrefBand�� ���� FullBand�� */
    VOS_UINT8                           ucFullBandNum;                          /* �ڼ���FullBand����, �˽׶ν���, ������һ�׶� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
}NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU
 �ṹ˵��  : en_NV_Item_Oos_Plmn_Search_Strategy_Cfg NV��ṹ
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseOnePatternCfg;    /* ��һ�׶ε���������������˯��ʱ�� */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseTwoPatternCfg;    /* �ڶ��׶ε���������������˯��ʱ�� */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseThreePatternCfg;  /* �����������׶ε���������������˯��ʱ�� */
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_PATTERN_CFG_STRU           stPhaseFourPatternCfg;   /* ���������Ľ׶ε���������������˯��ʱ�� */
}NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU
 �ṹ˵��  : en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg NV��ṹ
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHistoryActiveFlg;                     /* NV���Ƿ񼤻� */
    VOS_UINT8                           ucPrefBandActiveFlg;                    /* NV���Ƿ񼤻� */
    VOS_UINT8                           ucSearchTypeAfterHistoryInAreaLostScene;/* area lost����history����֮����������� 0:���� 1:pref band�� 2:spec�� */
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulReserved4;
    VOS_UINT32                          ulReserved5;
}NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU;


/* Added by s00217060 for ������������, 2016-2-15, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OOS_BG_NETWORK_SEARCH_CUSTOM_STRU
 �ṹ˵��  : en_NV_Item_OOS_BG_NETWORK_SEARCH_CUSTOM NV��ṹ
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDelayNetworkSearchTimerLenAfterEmc;   /* ������֮������ʱ������λ:s��ʱ��Ϊ0��ʾҪ���� */
    VOS_UINT8                           ucBgHistorySupportFlg;                  /* BG��ʽhistory���Ƿ�֧�� */
    VOS_UINT8                           ucPrefBandListSupportFlg;               /* �б�ʽpref band���Ƿ�֧�� */
    VOS_UINT8                           ucFullBandListSupportFlg;               /* �б�ʽfull band���Ƿ�֧�� */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
}NAS_MMC_NVIM_OOS_BG_NETWORK_SEARCH_CUSTOM_STRU;
/* Added by s00217060 for ������������, 2016-2-15, end */

/*****************************************************************************
 �ṹ��    : NAS_NVIM_EXTEND_T3240_LEN_CFG_STRU
 �ṹ˵��  : en_NV_Item_EXTEND_T3240_LEN_CFG NV��ṹ
  1.��    ��   : 2016��4��13��
    ��    ��   : z00359541
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucExtendT3240LenFlg;                    /* �Ƿ���T3240ʱ���Ķ��� 0:δ���� 1:���� */
    VOS_UINT8                           ucReserve;                              /* ����λ */
    VOS_UINT16                          usCustomizedT3240Len;                   /* ���Ƶ�T3240��ʱ��ʱ������λΪ���룬���֧��65535���� */
}NAS_NVIM_EXTEND_T3240_LEN_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_GET_GEO_PRIO_RAT_LIST_STRU
 �ṹ˵��  : ��ȡ����λ����Ϣ�Ľ��뼼�����ȼ��б���Ϣ
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* ��ȡ����λ����Ϣ�Ľ��뼼������ */
    VOS_UINT8                           aucRatOrder[NAS_NVIM_MAX_RAT_NUM];      /* ��ȡ����λ����Ϣ�Ľ��뼼�����ȼ� */
}NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_GET_GEO_CFG_INFO_STRU
 �ṹ˵��  : en_NV_Item_Get_Geo_Cfg_Info NVIM
 1.��    ��   : 2015��05��22��
   ��    ��   : f00179208
   �޸�����   : ������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;               /* NV���Ƿ񼤻� */
    VOS_UINT8                                               ucGetGeoTimerlen;           /* ��ȡ�����붨ʱ��ʱ������λ���� */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT32                                              ulGeoEffectiveTimeLen;      /* ���������Ч��ʱ������λ�Ƿ��� */
    NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU                     stGetGeoPrioRatList;        /* ��ȡ����λ����Ϣ�Ľ��뼼�����ȼ��б���Ϣ */
}NAS_NVIM_GET_GEO_CFG_INFO_STRU;

/* added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU
 �ṹ˵��  : en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg NV��ṹ
  1.��    ��   : 2015��10��9��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU;
/* added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, end */

/*****************************************************************************
 �ṹ��    : NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU
 �ṹ˵��  : en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG NV��ṹ
  1.��    ��   : 2015��10��9��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDeleteRplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU
 �ṹ˵��  : en_NV_Item_Nw_Search_Chr_Record_Cfg NVIM
 1.��    ��   : 2015��08��13��
   ��    ��   : f00179208
   �޸�����   : ����CHR��¼����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;       /* NV���Ƿ񼤻� */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT32                                              ulRecordNum;        /* ��¼�Ĵ��� */
}NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_EVDO_PRL_LIST_STRU
 �ṹ˵��  : en_NV_Item_1X_EVDO_PRL_LIST NV��ṹ
 1.��    ��   : 2014��11��03��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrlData[CNAS_NVIM_PRL_SIZE];
}CNAS_NVIM_1X_EVDO_PRL_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CBT_PRL_LIST_STRU
 �ṹ˵��  : en_NV_Item_CBT_PRL_LIST NV��ṹ
 1.��    ��   : 2014��11��03��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrlData[CNAS_NVIM_CBT_PRL_SIZE];
}CNAS_NVIM_CBT_PRL_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_HOME_SID_NID_STRU
 �ṹ˵��  : HOME_SID_NID�����Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usReserved;
}CNAS_NVIM_1X_HOME_SID_NID_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU
 �ṹ˵��  : HOME_SID_NID����б���Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_HOME_SID_NID_STRU      astHomeSidNid[CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM];
}CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_STRU
 �ṹ˵��  : ɨ��������������Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}CNAS_NVIM_OOC_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 �ṹ˵��  : ɨ�������������б���Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           uc1xOocDoTchPhase1TimerLen;              /* Do TCH��ǰ4�γ��� Ooc Timer ���ʱ�� */
    VOS_UINT8                           uc1xOocDoTchPhase2TimerLen;              /* Do TCH��4�����ϳ��� Ooc Timer ���ʱ�� */
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 �ṹ˵��  : ɨ�������������б���Ϣ
 1.��    ��   : 2015��01��08��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucInsertOrigChanFlg;        /* ��ͬ������ǰ�Ƿ������ǰפ��Ƶ�� */
    NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8                    enChanRepeatScanStrategy;   /*Ƶ���ظ��������� */
    VOS_UINT8                                               aucReserved[2];
}CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU
 �ṹ˵��  : EPDSZID Feature Cfg
 1.��    ��   : 2015��01��08��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8                ucEpdszidType;  /* EPDSZID֧������ */
    VOS_UINT8                                               ucHatLen;       /* HATʱ������λs */
    VOS_UINT8                                               ucHtLen;        /* HTʱ������λs */
    VOS_UINT8                                               aucReserved[5];
}CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_SYSTEM_STRU
 �ṹ˵��  : NV����HRDP�����������BAND��Channel��Ϣ�ṹ
 1.��    ��   : 2014��12��11��
   ��    ��   : h00300778
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucSubnet[CNAS_NVIM_HRPD_SUBNET_LEN];
    VOS_UINT16                         usBandClass;
    VOS_UINT16                         usChannel;
}CNAS_NVIM_HRPD_SYSTEM_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_MRU_LIST_STRU
 �ṹ˵��  : en_NV_Item_HRPD_MRU_LIST NV��ṹ
 1.��    ��   : 2014��12��11��
   ��    ��   : h00300778
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucRsv[3];
    CNAS_NVIM_HRPD_SYSTEM_STRU          astSystem[CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM];
}CNAS_NVIM_HRPD_MRU_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_LAST_SCI_STRU
 �ṹ˵��  : en_NV_Item_1X_LAST_SCI NV��ṹ
 1.��    ��   : 2015��2��4��
   ��    ��   : g00256031
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSicValue;
}CNAS_NVIM_1X_LAST_SCI_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU
 �ṹ˵��  : en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len NV��ṹ
 1.��    ��   : 2015��1��29��
   ��    ��   : y00245242
   �޸�����   : �ȴ�IMS VOICE CAP�Ķ�ʱ��ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv��δ���1:nv��� */
    VOS_UINT8                           ucWaitImsVoiceAvailTimerLen;            /* �ȴ�IMS VOICE�Ŀ���ָʾ�Ķ�ʱ��ʱ��,��λΪ�뼶,��Ҫת��Ϊ���� */
    VOS_UINT8                           ucWaitImsWithWifiVoiceAvailTimerLen;    /* ֧��IMS WIFIʱ,�ȴ�IMS VOICE�Ŀ���ָʾ�Ķ�ʱ��ʱ��,��λΪ�뼶,��Ҫת��Ϊ���� */
    VOS_UINT8                           ucReserved;
}NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU;

typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT8                           ucLocType;
    VOS_UINT8                           ucLocLen;
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNID;
    VOS_UINT8                           ucPacketZoneID;
    VOS_UINT8                           ucReserve;
}CNAS_NVIM_HRPD_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT16                          usStrgBLOBType;
    VOS_UINT8                           ucStrgBLOBLen;
    VOS_UINT8                           aucStorageBLOB[CNAS_NVIM_MAX_STORAGE_BLOB_LEN];
    VOS_UINT8                           aucReserve[2];
}CNAS_NVIM_HRPD_STORAGE_BLOB_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU
 �ṹ˵��  : en_NV_Item_LTE_REJ_CAUSE_14_CFG NV��ṹ
 1.��    ��   : 2015��1��5��
   ��    ��   : h00285180
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRejCause14Flg;               /* �Ƿ���LTE #14ԭ��ܾ��Ż���0: δ������1:���� */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLteRejCause14EnableLteTimerLen; /* LTE #14ԭ��ܾ�ʱ��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���� */
}NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU;

/*****************************************************************************
 ö����    : NAS_SMS_PS_CONCATENATE_ENUM
 �ṹ˵��  : PS�������������ö�ٶ���
  1.��    ��   : 2015��05��18��
    ��    ��   : j00174725
    �޸�����   : ����
*****************************************************************************/
enum NAS_SMS_PS_CONCATENATE_ENUM
{
    NAS_SMS_PS_CONCATENATE_DISABLE      = 0,
    NAS_SMS_PS_CONCATENATE_ENABLE,

    NAS_SMS_PS_CONCATENATE_BUTT
};
typedef VOS_UINT8 NAS_SMS_PS_CONCATENATE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����  : NAS_NV_SMS_PS_CTRL_STRU
 �ṹ˵��  : PS����ſ���

  1.��    ��   : 2015��05��18��
    ��    ��   : j00174725
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8   enSmsConcatenateFlag;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} NAS_NV_SMS_PS_CTRL_STRU;

/*****************************************************************************
 �ṹ����  : NAS_NV_SMS_FILTER_CFG_STRU
 �ṹ˵��  : ���Ź���������Ϣ

  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsFilterEnableFlg;
    VOS_UINT8                           aucReserved[3];
} NAS_NV_SMS_FILTER_CFG_STRU;


/*****************************************************************************
 Name    : NAS_NVIM_AVAILABLE_TIMER_CFG_STRU
 Description  : Structure defintion for available timer config used in MSCC
 History     :
  1.Date     : 2015-04-14
    Author   : a00295761
    Modify   : create
  2.Date     : 2016-01-14
    Author   : W00176964
    Modify   : DTS2016011505496:���Ӷ�ԭʼϵͳ����MSPL�����BSR����,��ʱ��ʱ����NV����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReserved1;

    VOS_UINT8                           ucReserved2;

    VOS_UINT16                          usReserved1;/* ԭʼϵͳ����MSPL����ʱ,bsr��ʱ��ʱ�� */

    VOS_UINT32                          ulFirstSearchAvailTimerLen; /* Contains the Available timer length to be used , when the
                                                                    number of successive triggers is less than ulFirstSearchAvailTimerCount */

    VOS_UINT32                          ulFirstSearchAvailTimerCount; /* For the number successive triggers of avaiable timer less
                                                                      than or equal to ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                      length value of ulFirstSearchAvailTimerLen */

    VOS_UINT32                          ulDeepSearchAvailTimerLen;  /* For the number successive triggers of avaiable timer greater
                                                                    than ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                    length value of ulDeepSearchAvailTimerLen */

    VOS_UINT32                          ulScanTimerLen; /* Contains the scan timer length */
    VOS_UINT32                          ulReserved1; /* Contains the BSR Timer length */
    VOS_UINT32                          ulSleepTimerLen; /* Contains the sleep timer length */
}NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU;



typedef struct
{
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;

    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  en1xPrioClass;
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enAIPrioClass;
    VOS_UINT8                                               aucRsv[2];  /* remain four bytes in future */
}NAS_NVIM_1X_LOC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_3GPP_LOC_INFO_STRU
 �ṹ˵��  : 3gpp loc info

 1.��    ��   : 2015��5��26��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.Date       : 2015-05-29
   Author     : w00176964
   Modify     : DTS2015052903319:add pri class
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                                              ulMnc;                                  /* MNC,2 or 3 bytes */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enPrioClass;
    VOS_UINT8                                               aucRsv[3];  /* remain four bytes in future */
}NAS_NVIM_3GPP_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucIsLocInfoUsedInSwitchOn;
    NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8 enSysAcqMode;
    VOS_UINT8                           ucIs1xLocInfoValid;
    VOS_UINT8                           ucIsLteLocInfoValid;
    NAS_NVIM_1X_LOC_INFO_STRU           st1xLocInfo;
    NAS_NVIM_3GPP_LOC_INFO_STRU         st3gppLocInfo;
}NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU;


typedef struct
{

    VOS_UINT8                                               ucReAcqLteOnHrpdSyncIndFlag; /* The NVIM Flag controls if
                                                                                                       MSCC must search  for LTE Service
                                                                                                       when HSD sends Sync Ind, if LTE
                                                                                                       is preferred */

    VOS_UINT8                                               ucIs1xLocInfoPrefThanLte;  /* The NVIM Flag controls if CDMA 1x
                                                                                                     Loc info is more preferred than LTe
                                                                                                     Loc Info */
    VOS_UINT8                                               aucReserved[2];
    NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU                    stMmssSysAcqTimerCfg;  /* Contains the Timer Configuration
                                                                                                for MMSS System Acquire */
}NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucMlplMsplActiveFlag;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usMlplBufSize;
    VOS_UINT16                          usMsplBufSize;
    VOS_UINT8                           aucMlplBuf[NAS_MSCC_NVIM_MLPL_SIZE];
    VOS_UINT8                           aucMsplBuf[NAS_MSCC_NVIM_MSPL_SIZE];
}NAS_MSCC_NVIM_MLPL_MSPL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_MOB_TERM_STRU
 �ṹ˵��  : en_NV_Item_1X_MOB_TERM NV��ṹ
 1.��    ��   : 2015��6��2��
   ��    ��   : g00256031
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermHome;
    VOS_UINT8                           ucRsv;
}CNAS_NVIM_1X_MOB_TERM_STRU;


typedef struct
{
    VOS_UINT8                           ucActiveFlag;           /* NV item is active not not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usActTimerLen;          /* Session activate timer length, unit is second */
    VOS_UINT8                           ucMaxActCountConnFail;  /* Max session activate count of reason conntion fail */
    VOS_UINT8                           ucMaxActCountOtherFail; /* Max session activate count of reason other fail */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU;

/*****************************************************************************
 Name    : CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg
 History     :
  1.Date     : 2015-09-23
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-12-17
    Author   : m00312079
    Modify   : DTS2015121410637:����NV�������AMP setup��open̬ʱ��UATI req���ͳɹ����������UATI assign��ʱ��
  3.Date     : 2015-12-31
    Author   : m00312079
    Modify   : DTS2015123108077:����NV�������open̬ʱ��UATI req���ͳɹ��������UATI assign��ʱ������Դ���
  4.Date     : 2016-01-16
    Author   : m00312079
    Modify   : DTS2015122603997:����NV������Ƿ������ӽ�����ֹͣkeep alive���̣�NVĬ�Ͽ���
  5.Date     : 2016-04-05
    Author   : m00312079
    Modify   : DTS2016032810749:���UEƽ̨����֧��ehrpd������NV������Ƿ��ڿ��ػ���ָ�ehrpd������NVĬ�Ϲر�(���ػ��󲻻ָ�ehrpd����)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartUatiReqAfterSectorIdChgFlg;   /* Ϊ��ͨ��RF���Ժ�CCF2.2.2.8����������NV����
                                                                                          NV��(Ĭ��):���ձ��ֻҪsector ID�����仯������UATI��������
                                                                                          NV�ر�:      �ϸ���Э��C.S0024 7.3.7.1.6.1������ֻ����HO����
                                                                                                       Conn Close��sector ID�����仯������UATI�������� */

    VOS_UINT8                           ucWaitUatiAssignTimerLenInAmpSetup; /* ��λ:��(s),Ĭ��5s.��ĳЩ�������豸�̵������ϣ�Ϊ�˽���UE�Ľ���ʱ����
                                                                                        ����UE��UATI assign��ʱ������ʱ�����Ϊ5s���Ϊ120s(Э�鶨ʱ��ʱ��) */
    VOS_UINT8                           ucWaitUatiAssignTimerLenInAmpOpen; /* ��λ:��(s),Ĭ��120s(Э�鶨ʱ��ʱ��)����ʱ�����5s���120s��*/

    VOS_UINT8                           ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;/* ����NV�������open̬ʱ��UATI req���ͳɹ���
                                                                                                             ������UATI assign��ʱ������Դ���,Ĭ�ϲ����ԣ��������4�� */
    VOS_UINT8                           ucClearKATimerInConnOpenFlg;                          /* ����NV����ƣ��Ƿ������ӽ����ɹ������keep alive����
                                                                                                             NV��(Ĭ��): ���ӽ����ɹ���ֹͣkeep alive��ʱ��������keep alive��صļ���
                                                                                                                           ���ӶϿ��󣬿���keep alive��ʱ������������keep alive���̡�
                                                                                                             NV�ر�:       ���ӽ����ɹ��󣬲����keep alive���̣�����Э�鴦�� */
    VOS_UINT8                           ucRecoverEhrpdAvailFlg;                              /* ����NV����ƣ����UEƽ̨����֧��ehrpd,�Ƿ��ڿ��ػ���ָ�ehrpd����
                                                                                                             NV��:        ���ػ���ָ�ehrpd����������ػ�ǰ��hrpd�ĻỰ���򿪻�����Ҫ����Э��
                                                                                                             NV�ر�(Ĭ��):  ���ػ��󲻻ָ�ehrpd����������ػ�ǰ��hrpd�ĻỰ���򿪻���ִ��recover�Ự���� */

    VOS_UINT8                           aucRsv[26];
}CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucIsKeepAliveInfoValid;    /* If TRUE, then the Keep alive paramters are valid */
    VOS_UINT8                           ucRsv1;                    /* for padding */
    VOS_UINT16                          usTsmpClose;               /* stores the TsmpClose value of the last session. Unit is minutes */
    VOS_UINT32                          ulTsmpCloseRemainTime;     /* Stores the time remaining for Tsmpclose minutes to
                                                                               expire. Unit is seconds */
    VOS_UINT32                          aulLastPowerOffSysTime[2]; /* Stores the CDMA system time at last Power Off.
                                                                              Unit is Milliseconds. */
}CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEhrpdSupportFlg;       /* EHRPD is support or not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}NAS_NVIM_EHRPD_SUPPORT_FLG_STRU;


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG NV��ṹ
  1.��    ��   : 2015��8��26��
    ��    ��   : c00318887
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* NV���Ƿ񼤻� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulTotalTimeLen;                         /* ��һ�׶�������ʱ��,��λ:s */
}NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU;

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU
 �ṹ˵��  : en_NV_Item_CS_REG_FAIL_CAUSE_FORB_LA_TIME_CFG NV��ṹ
  1.��    ��   : 2015��9��23��
    ��    ��   : z00359541
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegFailCauseNum;                      /* ֧�ֵ�ע��ʧ��ԭ��ֵ����,����Ϊ0��ʾ��֧�ָ����� */
    VOS_UINT16                          usForbLaTimeLen;                        /* ��ֹLAʱ��,��λ:s */
    VOS_UINT16                          usPunishTimeLen;                        /* ��ƹ�һ�������Ҫ�ͷ���ʱ�� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT16                          ausRegFailCauseList[NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM];
}NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU;

/*****************************************************************************
 �ṹ����  : NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU
 �ṹ˵��  : CSG�����������������Ϣ

  1.��    ��   : 2015��9��21��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCsgAutonomousSrchFirstSrchTimeLen;                   /* CSG����������ʱ����һ�ε�ʱ�� */
    VOS_UINT8                           ucCsgAutonomousSrchFirstSrchTimeCount;                 /* CSG����������ʱ����һ�εĴ��� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usCsgAutonomousSrchSecondSrchTimeLen;                  /* CSG����������ʱ���ڶ��ε�ʱ�� */
    VOS_UINT8                           ucCsgAutonomousSrchSecondSrchTimeCount;                /* CSG����������ʱ���ڶ��εĴ��� */
    VOS_UINT8                           ucReserved2;
} NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_WITH_CSG_ID_STRU
 �ṹ˵��  : PLMN��CSG ID�Ľṹ

 1.��    ��   : 2015��9��21��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    NVIM_PLMN_VALUE_STRU                stPlmnId;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT32                          ulCsgId;
}NAS_NVIM_PLMN_WITH_CSG_ID_STRU;


/*****************************************************************************
 �ṹ��    : NAS_NVIM_ALLOWED_CSG_LIST_STRU
 �ṹ˵��  : Allowed CSG List���ļ�����ʱnv�м�¼allowed CSG List��Ϣ

 1.��    ��   : 2015��9��21��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnWithCsgIdNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    NAS_NVIM_PLMN_WITH_CSG_ID_STRU      astPlmnWithCsgIdList[NAS_NVIM_MAX_PLMN_CSG_ID_NUM];
}NAS_NVIM_ALLOWED_CSG_LIST_STRU;
/*****************************************************************************
 �ṹ��    : NAS_NVIM_UE_BASED_OPERATOR_CSG_LIST_STRU
 �ṹ˵��  : Operater CSG List���ļ�����ʱnv�м�¼operater CSG List��Ϣ

 1.��    ��   : 2016��3��23��
   ��    ��   : y00358807
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnWithCsgIdNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    NAS_NVIM_PLMN_WITH_CSG_ID_STRU      astPlmnWithCsgIdList[NAS_NVIM_MAX_PLMN_CSG_ID_NUM];
}NAS_NVIM_UE_BASED_OPERATOR_CSG_LIST_STRU;
/*****************************************************************************
�ṹ��    : NAS_NVIM_CSG_DUPLICATE_RPLMN_AND_EPLMN_LIST_STRU
�ṹ˵��  : ��¼CSG�ֶ�����ǰ��RPLMN��EPLMN��Ϣ
1.��    ��   : 2015��9��21��
  ��    ��   : z00161729
  �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           ucRat;                                  /* ��¼duplicate rplmn�Ľ��뼼��*/
    VOS_UINT8                           aucReserve[2];                          /*NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն�*/
    NVIM_PLMN_VALUE_STRU                astRplmnAndEplmnList[NVIM_MAX_EPLMN_NUM];
}NAS_NVIM_CSG_DUPLICATED_RPLMN_AND_EPLMN_LIST_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU
�ṹ˵��  : csg��ֹ�����������
1.��    ��   : 2015��9��21��
  ��    ��   : z00161729
  �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    /* CSG��ֹ����ͷ�ʱ��,��λ�� */
    VOS_UINT16                          usCsgPlmnForbiddenPeriod;

    /* ����CSG���类����Щԭ��ֵʱ��Ҫ������������ֹcsg�����б� */
    VOS_UINT8                           ucCauseNum;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausCause[NAS_NVIM_MAX_CSG_REJ_CAUSE_NUM];
}NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU;
/*****************************************************************************
 �ṹ����  : NAS_NVIM_CSG_CTRL_CFG_STRU
 �ṹ˵��  : CSG�����������nv

  1.��    ��   : 2015��9��21��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucBitOp1:1;
    VOS_UINT8                                               ucBitOp2:1;
    VOS_UINT8                                               ucBitOp3:1;
    VOS_UINT8                                               ucBitOp4:1;
    VOS_UINT8                                               ucBitOp5:1;
    VOS_UINT8                                               ucBitOp6:1;
    VOS_UINT8                                               ucBitOp7:1;
    VOS_UINT8                                               ucBitOp8:1;
    VOS_UINT8                                               ucReserved0;
    VOS_UINT8                                               ucIsSupportCsgFlag;             /* VOS_TRUE:UE֧��CSG����; VOS_FALSE:UE��֧��CSG���� */
    VOS_UINT8                                               ucCsgListOnlyReportOperatorCsgListFlag; /* VOS_TRUE:csg�б��������ֻ�ϱ���operator csg list������; VOS_FALSE:CSG�б������������CSG ID���ϱ� */
    NAS_NVIM_CSG_FORBIDDEN_PLMN_CFG_STRU                    stCsgForbiddenPlmnCfg;       /* CSG��ֹ����������� */
    NAS_NVIM_ALLOWED_CSG_LIST_STRU                          stAllowedCsgList;               /* ��¼Allowed CSG List��Ϣ */
    VOS_UINT32                                              ulCsgPeriodicSearchPeriod;      /* CSG����������ʱ��,��λ���� */
    NAS_NVIM_CSG_DUPLICATED_RPLMN_AND_EPLMN_LIST_STRU       stDuplicatedRplmnAndEplmnList;  /* �ػ�ʱ���֮ǰ���й�CSGָ���������ҹػ�ʱפ��CSG���磬���¼CSGָ������ǰ��RPLMN��EPLMN*/
    NAS_NVIM_CSG_AUTONOMOUS_SEARCH_CFG_STRU                 stCsgAutonomousSrchCfg;         /* CSG��������������� */
	NAS_NVIM_UE_BASED_OPERATOR_CSG_LIST_STRU                stUeBasedOperatorCsgList;       /* ��¼Based CSG List��Ϣ */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
    VOS_UINT32                                              ulReserved1;
} NAS_NVIM_CSG_CTRL_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU
 �ṹ˵��  : �����յ�PSע��ɹ���Ϣ�Ƿ�����ֹ��Ϣ

 1.��    ��   : 2015��12��11��
   ��    ��   : z00359541
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKeepCsForbInfoFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CLEAR_CKSN_STRU
 �ṹ˵��  : ������Լ�Ȩʧ�ܽ��û����Ӧ���ͷ���·ʱ�Ƿ����CKSN������
 1.��    ��   : 2015��1��5��
   ��    ��   : z00359541
   �޸�����   : �½�
  2.��    ��   : 2016��1��19��
    ��    ��   : c00318887
    �޸�����   : ����nv
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNwIgnoreAuthFailFlg;                  /* ������Լ�Ȩʧ�ܽ��û����Ӧ���ͷ���·ʱ�Ƿ����CKSN������ */
    VOS_UINT8                           ucUsimGsmAuthCfg;                       /* USIM����GSM����2G cs/ps ��Ȩ����3G���Ƿ���Ҫ���CS/ps CKSNֵ */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_NVIM_CLEAR_CKSN_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_ATT_ENS_CTRL_STRU
 �ṹ˵��  : ��¼en_NV_Item_ATT_Ctrl_Para(9081) NV������

 �޸ļ�¼  :
 1.��    ��   : 2016��02��15��
   ��    ��   : w00167002
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetSelMenuFlg;                        /* ����ѡ��˵����ƣ�VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucRatBalancingFlg;                      /* ���뼼��ƽ����ƣ�VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_NVIM_ATT_ENS_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : NAS_NVIM_NONREGULAR_SERVICE_CUSTOM_STRU
 �ṹ˵��  : ��¼en_NV_Item_Nonregular_Servic_Custom NV������

 �޸ļ�¼  :
 1.��    ��   : 2016��6��9��
   ��    ��   : n00269697
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTiNonregularCustom;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
}NAS_NVIM_NONREGULAR_SERVICE_CUSTOM_STRU;


enum CNAS_NVIM_HRPD_SESSION_STATUS_ENUM
{
    CNAS_NVIM_HRPD_SESSION_STATUS_CLOSE,
    CNAS_NVIM_HRPD_SESSION_STATUS_OPEN,
    CNAS_NVIM_HRPD_SESSION_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8;


enum CNAS_NVIM_HRPD_SESSION_TYPE_ENUM
{
    CNAS_NVIM_HRPD_SESSION_TYPE_HRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_EHRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8;


enum CNAS_NVIM_HARDWARE_ID_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_TYPE_MEID                    = 0x0000FFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_ESN                     = 0x00010000,
    CNAS_NVIM_HARDWARE_ID_TYPE_NULL                    = 0x00FFFFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32;


enum CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_NVIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_RAND,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_UIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32;

/*****************************************************************************
 Structure Name    : CNAS_NVIM_HRPD_UATI_INFO_STRU
 Description       : hrpd uati info structure
 History     :
  1.Date     : 2015-06-03
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-06-18
    Author   : m00312079
    Modify   : DTS2015091604029:nv�б�����Чuati assigngment��sequence number
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           aucCurUATI[CNAS_NVIM_UATI_OCTET_LENGTH];
    VOS_UINT8                           ucUATIColorCode;
    VOS_UINT8                           ucUATISubnetMask;
    VOS_UINT8                           ucUATIAssignMsgSeq;
    VOS_UINT8                           ucRsv2;
}CNAS_NVIM_HRPD_UATI_INFO_STRU;


typedef struct
{
    CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32                  enHwidType;
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32              enHwidSrcType;
    VOS_UINT32                                              ulEsn;                                /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_NVIM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               ucRsv1;
}CNAS_NVIM_HARDWARE_ID_INFO_STRU;


typedef struct
{
    VOS_INT32                           lLongitude;
    VOS_INT32                           lLatitude;
}CNAS_NVIM_LOC_INFO_STRU;


typedef struct
{
    CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8                enSessionStatus;
    CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                               aucIccid[CNAS_NVIM_ICCID_OCTET_LEN];
    CNAS_NVIM_HRPD_UATI_INFO_STRU                           stUatiInfo;
    CNAS_NVIM_LOC_INFO_STRU                                 stLocInfo;
    CNAS_NVIM_HARDWARE_ID_INFO_STRU                         stHwid;
}CNAS_NVIM_HRPD_SESSION_INFO_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSuppOnlyDo0;                          /* �Ƿ�ֻ֧��DO0�汾 */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithMfpa;                      /* �Ƿ�֧��DOA�汾��Ӧ������ֻ֧��MFPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithEmfpa;                     /* �Ƿ�֧��DOA�汾��Ӧ������֧��MFPA��EMPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaEhrpd;                         /* �Ƿ�֧��eHRPD */
}CNAS_NVIM_HRPD_UE_REV_INFO_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU
 Description  : Structure definition for en_Nv_Item_HRPD_Session_Info_Ex
 History     :
  1.Date     : 2015-09-18
    Author   : m00312079
    Modify   : create
  2.Date     : 2015-12-21
    Author   : m00312079
    Modify   : DTS2015120208895,��session��UE�İ汾��Ϣ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSessionSeed;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU     stUERevInfo;
    VOS_UINT8                           ucLteRegSuccFlg;
    VOS_UINT8                           aucReserve[11];
}CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU;


typedef struct
{
    VOS_UINT8                           ucAccessAuthAvailFlag;
    VOS_UINT8                           ucAccessAuthUserNameLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           aucAccessAuthUserName[CNAS_NVIM_MAX_AUTHDATA_USERNAME_LEN];
}CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU;

typedef struct
{
    VOS_UINT8                 ucUseImsiFlg;                                     /* VDF��������״̬�·��������Я��IMSI���� */
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_EMC_UNDER_NET_PIN_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU
 �ṹ˵��  : ����Attach����RAU������ʧ�ܴﵽ������֮���Ƿ�ֻ����һ��LAU
 1.��    ��   : 2015��08��13��
   ��    ��   : l00289540
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucPsRegFailMaxTimesTrigLauOnceFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU
 �ṹ˵��  : HPLMNע�ᱻ#13�ܾ�֮���Ƿ���Ҫ��������HPLMN WITH RAT
 1.��    ��   : 2015��08��13��
   ��    ��   : l00289540
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucKeepSrchHplmnEvenRejByCause13Flg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU
 �ṹ˵��  : VPLMN LTEע�ᱻ#14�ܾ�֮���Ƿ�������2/3G PS�����ע��
 1.��    ��   : 2015��08��13��
   ��    ��   : l00289540
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucEpsRejByCause14InVplmnAllowPsRegFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU;

/*****************************************************************************
 ö����    : NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
 �ṹ˵��  : ����RPLMNʱ�Ƿ���ҪЯ��EPLMN
 1.��    ��: 2015��8��13��
   ��    ��: l00289540
   �޸�����: ����
*****************************************************************************/
enum NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_OFF                     = 0,           /* �رմ��Ż� */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ROAM             = 1,           /* �Ż��򿪣����ǽ�������ʱ��Ч */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ALL              = 2,           /* �Ż��򿪣�����������ζ���Ч */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU
 �ṹ˵��  : ����RPLMN�Ƿ���ҪЯ��EPLMN��NV����
 1.��    ��   : 2015��08��13��
   ��    ��   : l00289540
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8         enSwitchFlag;
    VOS_UINT8                                               ucCarryEplmnSceneSwitchOn;
    VOS_UINT8                                               ucCarryEplmnSceneAreaLost;
    VOS_UINT8                                               ucCarryEplmnSceneAvailableTimerExpired;
    VOS_UINT8                                               ucCarryEplmnSceneSysCfgSet;
    VOS_UINT8                                               ucCarryEplmnSceneDisableLte;
    VOS_UINT8                                               ucCarryEplmnSceneEnableLte;
    VOS_UINT8                                               ucCarryEplmnSceneCSFBServiceRej;
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
}NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_HOME_SID_NID_PRI_CFG
                HOME SID/NID�б�����ȼ��Ƿ�����ߵģ�������ΪVOS_TRUE����ʾhome SID/NID
                ��ϵͳ���ȼ���ߣ����ܸ�ϵͳ�Ƿ���PRL���У����ΪVOS_FALSE��home SID/NID��ˢ��
                PRL���е�NEG��roaming���
 History     :
  1.Date     : 2015-07-02
    Author   : w00242748
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeSidNidDependOnPrlFlg;
    VOS_UINT8                           aucReserved[3];
}CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_SYS_INFO_STRU
 �ṹ˵��  : �����SID��MCC��Ϣ�����ư������е�MCC����ʼSID�Լ�����SID

 1.��    ��   : 2015��7��2��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}CNAS_NVIM_SYS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_OPER_LOCK_WHITE_SID_STRU
 �ṹ˵��  : en_NV_Item_OPER_LOCK_WHITE_SID_INFO NV��ṹ
  1.��    ��   : 2015��7��2��
    ��    ��   : w00242748
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* �������Ƿ�ʹ�� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    CNAS_NVIM_SYS_INFO_STRU             astSysInfo[CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_FREQENCY_CHANNEL_STRU
 �ṹ˵��  : Ƶ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT8                           aucReserved[2];
}CNAS_NVIM_FREQENCY_CHANNEL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU
 �ṹ˵��  : �й����Ŷ���Ƶ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_NVIM_FREQENCY_CHANNEL_STRU     astFreqList[CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM];
}CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU
 �ṹ˵��  : CDAM standard channels��Ϣ
  1.��    ��   : 2015��7��14��
    ��    ��   : y00245242
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryA;
    VOS_UINT16                          usPrimaryB;
    VOS_UINT16                          usSecondaryA;
    VOS_UINT16                          usSecondaryB;
}CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU;


typedef struct
{
    VOS_UINT32                                              ulEnableFlag;
}CNAS_NVIM_NO_CARD_MODE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_EMC_REDIAL_SYS_ACQ_CFG_STRU
 �ṹ˵��  : en_NV_Item_EMC_REDIAL_SYS_ACQ_CFG NV��ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : c00299063
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucRedialTimes[CNAS_NVIM_1X_MAX_MRU_SYS_NUM];  /* ��������ʧ��ʱ��ǰפ����Ƶ����mru list���ز���������������������*/
}CNAS_NVIM_1X_EMC_REDIAL_SYS_ACQ_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_AVOID_PHASE_NUM
 �ṹ˵��  : avoid������Ϣ
  1.��    ��   : 2015��11��23��
    ��    ��   : c00299063
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAvoidTimerLen[CNAS_NVIM_1X_AVOID_MAX_PHASE_NUM];
}CNAS_NVIM_1X_AVOID_PHASE_NUM;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU
 �ṹ˵��  : avoid������Ϣ
  1.��    ��   : 2015��11��23��
    ��    ��   : c00299063
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_AVOID_PHASE_NUM        astAvoidPhaseNum[CNAS_NVIM_1X_AVOID_REASON_MAX];
}CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU
 �ṹ˵��  : en_CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU NV��ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : c00299063
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPowerOffCampOnCtrlFlg;
    VOS_UINT8                                               aucReserved[3];
}CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_PRL_ROAM_IND_STRATEGY_CFG_STRU
 �ṹ˵��  : en_NV_Item_1X_PRL_ROAM_IND_STRATEGY_CFG NV��ṹ
  1.��    ��   : 2016��03��05��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsConsiderRoamIndInPRLFlg;        /* �Ƿ���PRL������ϵͳ�ж��п���ROAM IND���Եı�־ */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
} CNAS_NVIM_1X_PRL_ROAM_IND_STRATEGY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SYS_ACQ_NO_RF_PROTECT_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_1X_SYS_ACQ_NO_RF_PROTECT_TIMER_CFG NV��ṹ
  1.��    ��   : 2016��2��25��
    ��    ��   : Y00322978
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ul1xSysAcqNoRfProtectTimerLen;
    VOS_UINT32                                              ul1xRedirNoRfProtectTimerLen;
    VOS_UINT32                                              ulHrpdSysAcqNoRfProtectTimerLen;
    VOS_UINT8                                               aucReserved[4];
}CNAS_NVIM_1X_DO_SYS_ACQ_NO_RF_PROTECT_TIMER_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_LTE_OR_DO_CONN_1X_SYS_ACQ_SYNC_DELAY_INFO_STRU
 �ṹ˵��  : en_NV_Item_1X_SYS_ACQ_DELAY_TIMER_CFG_WHEN_LTE_DO_CONN NV��ṹ
  1.��    ��   : 2016��3��28��
    ��    ��   : Y00322978
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ul1xSysAcqDelayTimerLen;
    VOS_UINT8                                               uc1xSysAcqSyncDelayEnable;
    VOS_UINT8                                               aucReserved[3];
}CNAS_NVIM_LTE_OR_DO_CONN_1X_SYS_ACQ_SYNC_DELAY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRUs
 �ṹ˵��  : en_NV_Item_LTE_OOS_2G_PREF_PLMN_SEL_CFG NV��ṹ
  1.��    ��   : 2015��07��03��
    ��    ��   : h00285180
    �޸�����   : �½�

    ucImsiPlmnListNum   SIM����Ŀ�����֧��16��
    astImsiPlmnList     SIM���б����֧��16��;
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucImsiListNum;                                                  /*������Ч��SIM����Ŀ(LTE OOS������2G����3G)  */
    VOS_UINT8                          ucReserved1;
    VOS_UINT8                          ucReserved2;
    VOS_UINT8                          ucReserved3;
    NAS_SIM_FORMAT_PLMN_ID             astImsiList[NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM];/* SIM���б� (LTE OOS������2G����3G) */
}NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU
 �ṹ˵��  : Ƶ�κ�Ƶ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT16                          usBandClass;
} CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CDMA_1X_PREF_CHANNELS_STRU
 �ṹ˵��  : �й�����1X��ѡƵ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU astFreqList[CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_STRU
 �ṹ˵��  : �й�����1X��ѡƵ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU astFreqList[CNAS_NVIM_MAX_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_1X_CUSTOMIZE_PREF_CHANNELS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_DYNLOAD_CTRL_STRU
 �ṹ˵��  : ��̬���ؿ�����Ϣ
  1.��    ��   : 2015��8��12��
    ��    ��   : w00242748
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableDynloadTW;
    VOS_UINT8                           ucReseverd1;
    VOS_UINT8                           ucReseverd2;
    VOS_UINT8                           ucReseverd3;
}NAS_NVIM_DYNLOAD_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU
 �ṹ˵��  : ��̬���ش���������Ϣ
  1.��    ��   : 2015��11��12��
    ��    ��   : w00242748
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTWMaxAttemptCount;
    VOS_UINT8                           ucReseverd1;
    VOS_UINT8                           ucReseverd2;
    VOS_UINT8                           ucReseverd3;
}NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU
 �ṹ˵��  : en_NV_Item_1X_PAGING_RSP_SO_CFG NV��ṹ
 1.��    ��   : 2015��11��02��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNoDataSrvRspSo33;                     /* û������ҵ��ʱ��Paging rsp�Ļظ���0 - Paging Rsp��SO��0�� 1 - Paging Rsp��SO��33 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}CNAS_NVIM_1X_PAGING_RSP_SO_CFG_STRU;



/*****************************************************************************
 �ṹ��    : NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU
 �ṹ˵��  : en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO NV��ṹ
 1.��    ��   : 2015��10��10��
   ��    ��   : j00174725
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsStartT310AccordWith3GPP;            /* ��proceeding����progress�У�Я��progress indicatorֵΪ#1��#2��#64ʱ��
                                                                                   �Ƿ�����T310, 0 - ����Э����;  1 -  ����Э���� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU
 �ṹ˵��  : en_NV_Item_CDATA_DISCING_PARA_CFG NV��ṹ
 1.��    ��   : 2015��11��11��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPppDeactTimerLen;                     /* ��λ(S), PPPȥ��������ʱ�� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU;
/*****************************************************************************
 �ṹ��    : NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU
 �ṹ˵��  : en_NV_Item_PPP_AUTH_INFO_FROM_CARD_FLAG NV��ṹ
 1.��    ��   : 2015��11��11��
   ��    ��   : Y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsPppAuthGetFromCard;
}NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU
 �ṹ˵��  : en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG NV��ṹ
 1.��    ��   : 2015��12��26��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:Auto attach����ʹ�ܣ�VOS_FALSE:Auto attach���ܹر� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU
 �ṹ˵��  : ECC��������������Ϣ��
             ע: ECCҵ��״̬����ECCҵ������֧�ֵ�����£�����Ч��

 �޸���ʷ      :
  1.��    ��   : 2015-11-11
    ��    ��   : l00359089
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC��������: TRUE -- ֧��ECC����FALSE -- ��֧��ECC���� */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC����״̬: TRUE -- ECC����򿪣�FALSE -- ECC����ر� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} CNAS_NVIM_1X_CALL_ENCVOICE_ECC_SRV_CAP_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
 �ṹ˵��  : 1X�з���ʱCL�������׶����ýṹ��
 �޸���ʷ      :
  1.��    ��   : 2015-12-10
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimeLen;         /* �ý׶���������ʱ��,��λΪ�� */
    VOS_UINT16                          usSleepTimeLen;         /* �ý׶�available��ʱ��������ʱ��,��λΪ�� */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucLteHistorySrchNum;       /* �ý׶�LTE��ʷƵ�������ܴ��� */
    VOS_UINT8                           ucLteFullBandSrchNum;      /* �ý׶�LTEȫƵ�������ܴ��� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU
 �ṹ˵��  : 1X�з���ʱCL�������׶����ýṹ��
 �޸���ʷ      :
  1.��    ��   : 2015-12-21
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc1xBsrLteActiveFlg;                /* �����л��л���1X��BSR LTE�ļ�����--CCF����Ҫ�� */
    VOS_UINT8                           uc1xBsrLteTimerLen;                 /* �����л��л���1X��BSR LTE�Ķ�ʱ��ʱ��-��λ�� */
    VOS_UINT8                           ucSrlte1xBsrLteEnableFlg;           /* SRLTE��1x����ҵ��̬BSR LTEʹ�ܱ�־ */
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
    VOS_UINT8                           ucReserve8;
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU
 �ṹ˵��  : 1X�з���ʱCL�������Կ���NV
 �޸���ʷ      :
  1.��    ��   : 2015-12-10
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
typedef struct
{
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_CTRL_STRU         stCtrlInfo;
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseOnePatternCfg;   /* �׽׶�������Ϣ */
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseTwoPatternCfg;   /* ���׶�������Ϣ */
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseThreePatternCfg; /* ���׶�������Ϣ:Ŀǰδʹ��,Ԥ�� */
} NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 �ṹ˵��  : ɨ�������������б���Ϣ
 1.��    ��   : 2016��01��12��
   ��    ��   : z00316370
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           ucResv[2];
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_HRPD_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CL_SYSTEM_ACQUIRE_DSDS_STRATEGY_CFG_STRU
 �ṹ˵��  : ��ģ��ϵͳ����DSDS���Կ���
 �޸���ʷ      :
  1.��    ��   : 2016-2-2
    ��    ��   : w00176964
    �޸�����   : DTS2016013006596����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucReAcqLteWithNoRfEnable;           /* lte no rfʱ���²���lte�Ƿ�ʹ�� */
    NAS_NVIM_CL_SYS_ACQ_DSDS_STRATEGY_SCENE_ENUM_UINT8      enReAcqLteWithNoRfScene;            /* lte no rfʱ���²���lte���������� */
    VOS_UINT8                                               ucReAcqLteWithNoRfDelayTime;        /* lte no rfʱ���²���lte���ӳ�ʱ��-��λ�� */
    VOS_UINT8                                               ucRsv1;
    VOS_UINT16                                              usRsv1;
    VOS_UINT16                                              usRsv2;
    VOS_UINT8                                               ucRsv2;
    VOS_UINT8                                               ucRsv3;
    VOS_UINT8                                               ucRsv4;
    VOS_UINT8                                               ucRsv5;
    VOS_UINT8                                               ucRsv6;
    VOS_UINT8                                               ucRsv7;
    VOS_UINT8                                               ucRsv8;
    VOS_UINT8                                               ucRsv9;
}NAS_NVIM_CL_SYSTEM_ACQUIRE_DSDS_STRATEGY_CFG_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CTRL_STRU
 �ṹ˵��  : 1X OOSϵͳ��������ܿؽṹ
 1.��    ��   : 2015��12��22��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPhaseNum;                 /* �ܽ׶θ��� */
    NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8                    enChanRepeatScanStrategy;   /* Ƶ���ظ��������� */
    VOS_UINT16                                              usMru0SearchTimerLen;       /* ����MRU0ʱavailable��ʱ����ʱ��,ÿ���׶ε�ʱ��,��λΪ�� */
    VOS_UINT8                                               uc1xOocDoTchPhase1TimerLen; /* Do TCH��ǰ4�γ��� Ooc Timer ���ʱ��,��λ�� */
    VOS_UINT8                                               uc1xOocDoTchPhase2TimerLen; /* Do TCH��4�����ϳ��� Ooc Timer ���ʱ��,��λ�� */
    VOS_UINT16                                              usRsv1;
    VOS_UINT8                                               ucRsv1;
    VOS_UINT8                                               ucRsv2;
    VOS_UINT8                                               ucRsv3;
    VOS_UINT8                                               ucRsv4;
}CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_PATTERN_STRU
 �ṹ˵��  : 1X OOSϵͳ������Խ׶���Ϣ
 1.��    ��   : 2015��12��22��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTotalTimeLen;         /* 1xһ���׶�������ʱ��,��λΪ�� */
    VOS_UINT16                          usSleepTimeLen;         /* 1x����һ�ּ��ʱ��,��λΪ�� */
    VOS_UINT8                           ucSrchNum;              /* 1xһ���׶��������� */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
}CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_PATTERN_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CFG_STRU
 �ṹ˵��  : 1X��OOS������ϵͳ�����������NV
 1.��    ��   : 2015��12��22��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CTRL_STRU             stCtrlInfo;
    CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_PATTERN_STRU          astSysAcqPhaseInfo[CNAS_NVIM_MAX_1X_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_1X_OOS_SYS_ACQ_STRATEGY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_CDMA_ERR_LOG_ACTIVE_REPORT_CONTRL_STRU
 �ṹ˵��  :  NV��ṹ
 1.��    ��   : 2016��2��24��
   ��    ��   : j00354216
   �޸�����   : CDMA Iteration 20�½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc1xOosReportEnable;
    VOS_UINT8                           uc1xMtServiceExceptionReportEnable;
    VOS_UINT8                           ucHrpdUatiFailReportEnable;
    VOS_UINT8                           ucHrpdSessionFailReportEnable;
    VOS_UINT8                           ucHrpdSessionExceptionDeactReportEnable;
    VOS_UINT8                           uctHrpdOrLteOosReportEnable;
    VOS_UINT8                           uctXregResltReportEnable;
    VOS_UINT8                           ucXsmsReportEnable;
    VOS_UINT8                           aucReserved[16];
}NAS_NVIM_CDMA_ERR_LOG_ACTIVE_REPORT_CONTRL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HOME_MCC_INFO_STRU
 �ṹ˵��  : �������MCC��ֵ

 �޸���ʷ      :
  1.��    ��   : 2016-2-26
    ��    ��   : g00256031
    �޸�����   : Create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMccNum;                               /* �������MCC�ĸ��� */
    VOS_UINT32                          aulMcc[CNAS_NVIM_HOME_MCC_MAX_NUM];     /* �������MCC��ֵ */
} CNAS_NVIM_HOME_MCC_INFO_STRU;
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_MRU0_SWITCH_ON_OOC_STRATEGY_CFG_STRU
 �ṹ˵��  : MRU0�ڿ�����OOC�����µĲ����������NV
 1.��    ��   : 2015��12��22��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usMru0Times;
}CNAS_NVIM_MRU0_SWITCH_ON_OOC_STRATEGY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_SYS_ACQ_BSR_TIMER_INFO_STRU
 �ṹ˵��  : SYS ACQ BSR��ʱ����Ϣ�ӿ�
 1.��    ��   : 2016��3��8��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxHistorySrchTimes;
    VOS_UINT8                           ucMaxPrefBandSrchTimes;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT16                          usBsrTimerLenWithNoMatchedMsplRec;  /* MSPL����û��ƥ��ļ�¼��BSRʱ�� */
    VOS_UINT16                          usBsrTimerLen;                      /* MSPL������ƥ��ļ�¼��BSRʱ�� */
}NAS_NVIM_SYS_ACQ_BSR_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_SYS_ACQ_BSR_CTRL_STRU
 �ṹ˵��  : SYS ACQ BSR��ʱ�����ƽṹ
 1.��    ��   : 2016��3��8��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucBsrTimerActivateFlag;
    VOS_UINT8                                               ucBsrPhaseNum;
    VOS_UINT8                                               ucHrpdConnBsrActiveFlg; /* HRPD�´�������ʱBSR�Ƿ�򿪱�ǡ�VOS_TRUE:��;VOS_FALSE:�ر� */
    VOS_UINT8                                               ucEhrpdConnBsrActiveFlg;/* EHRPD�´�������ʱBSR�Ƿ�򿪱�ǡ�VOS_TRUE:��;VOS_FALSE:�ر� */
    NAS_NVIM_SYS_ACQ_BSR_TIMER_INFO_STRU                    astBsrTimerInfo[NAS_NVIM_MAX_BSR_PHASE_NUM];
}NAS_NVIM_SYS_ACQ_BSR_CTRL_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CUSTOM_SUPPLEMENT_OPLMN_INFO_STRU
 �ṹ˵��  : ���ƵĲ���OPLMN��Ϣ�ṹ��--en_NV_Item_Custom_Supplement_Oplmn_Info
 1.��    ��   : 2016��4��13��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;              /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucOPlmnListNum;                 /* �û����õ�Oplmn�ĸ��� */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astOPlmnList[NAS_MMC_NVIM_MAX_CUSTOM_SUPPLEMENT_OPLMN_NUM];
}NAS_MMC_NVIM_CUSTOM_SUPPLEMENT_OPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : AI_MODEM_NAS_PLMN_SRCH_CFG_STRU
 �ṹ˵��  : AI_MODEM_NAS_PLMN_SRCH_CFG_STRU�ṹ
  1.��    ��   : 2016��04��13��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOosSrchSleepCnt;
    VOS_UINT8                           ucHighPrioSrchSleepCnt;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
}AI_MODEM_NAS_PLMN_SRCH_CFG_STRU;

/*****************************************************************************
 �ṹ��    : AI_MODEM_LTE_MEASURE_CFG_STRU
 �ṹ˵��  : AI_MODEM_LTE_MEASURE_CFG_STRU�ṹ
  1.��    ��   : 2016��04��13��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_INT16                           sThresholdRsrq;                         /* ����С����RSRQ���ޣ�AI MODE�����Ż�ʱ����С��RSRQ����ڸ����ޡ�ȡֵ��Χ��[-15, -1],��λ1dB */
    VOS_INT16                           sThresholdRsrp;                         /* ����С����RSRP���ޣ�AI MODE�����Ż�ʱ����С��RSRP����ڸ����ޡ�ȡֵ��Χ��[-115 , -1],��λ1dB */
    VOS_UINT16                          usStillTimeThres;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_LTE_MEASURE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : AI_MODEM_GSM_MEASURE_CFG_STRU
 �ṹ˵��  : AI_MODEM_GSM_MEASURE_CFG_STRU�ṹ
  1.��    ��   : 2016��04��13��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_INT16                           sThresholdRssi;                         /* GSM��RSSI�ķ�Χ[-115��0] */
    VOS_INT16                           usReserve1;
    VOS_UINT16                          usStillTimeThres;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_GSM_MEASURE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : AI_MODEM_WCDMA_MEASURE_CFG_STRU
 �ṹ˵��  : AI_MODEM_WCDMA_MEASURE_CFG_STRU�ṹ
  1.��    ��   : 2016��04��13��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_INT16                           sThresholdRscp;                         /* WCDMA��RSCP�ķ�Χ[-120��0] */
    VOS_INT16                           sThresholdEcn0;                         /* WCDMA��ECN0��Χ[-24,0] */
    VOS_UINT16                          usStillTimeThres;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_WCDMA_MEASURE_CFG_STRU;


/*****************************************************************************
 �ṹ��    : AI_MODEM_TIME_CFG_STRU
 �ṹ˵��  : AI_MODEM_TIME_CFG_STRU�ṹ
  1.��    ��   : 2016��04��13��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucTimeStart;
    VOS_UINT8                           ucTimeEnd;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AI_MODEM_TIME_CFG_STRU;


/*****************************************************************************
 �ṹ��    : AI_MODEM_CFG_NVIM_STRU
 �ṹ˵��  : en_NV_Item_AI_MODEM_CFG_INFO�ṹ
  1.��    ��   : 2016��04��13��
    ��    ��   : w00167002
    �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucActFlg;                               /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                           ucApplyArea;                            /*��������,Ĭ��0��ʾ�������� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;

    AI_MODEM_TIME_CFG_STRU              stTimeCfg;
    AI_MODEM_NAS_PLMN_SRCH_CFG_STRU     stNasSrchCfg;
    AI_MODEM_LTE_MEASURE_CFG_STRU       stLteMeasureCfg;
    AI_MODEM_GSM_MEASURE_CFG_STRU       stGasMeasureCfg;
    AI_MODEM_WCDMA_MEASURE_CFG_STRU     stWcdmaMeasureCfg;


    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucReserve4;

    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
    VOS_UINT8                           ucReserve8;

    VOS_UINT8                           ucReserve9;
    VOS_UINT8                           ucReserve10;
    VOS_UINT8                           ucReserve11;
    VOS_UINT8                           ucReserve12;

    VOS_UINT8                           ucReserve13;
    VOS_UINT8                           ucReserve14;
}AI_MODEM_CFG_NVIM_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_STRU
 �ṹ˵��  : �й�����HRPD����Ƶ��ṹ
  1.��    ��   : 2016��04��21��
    ��    ��   : z00316370
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_FREQENCY_CHANNEL_STRU         astFreqList[CNAS_NVIM_MAX_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_HRPD_CUSTOMIZE_PREF_CHANNELS_STRU;

/*****************************************************************************
 �ṹ��    :  NAS_NVIM_SMS_FAIL_LINK_CTRL_CFG_STRU
 �ṹ˵��  :  ���Ƶ��������е�һ������ʧ��ʱ���Ƿ�رն��ŵ���������
  1.��    ��   : 2016��07��27��
    ��    ��   : j00174725
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved1;
    VOS_UINT8                               ucReserved2;
    VOS_UINT8                               ucReserved3;
} NAS_NVIM_SMS_FAIL_LINK_CTRL_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_SMS_RP_ERROR_CUSTOM_CFG_STRU
 �ṹ˵��  : DCM��������,��re_errorΪ21��TPFCΪ197ʱ����Ϊ���ŷ��ͳɹ���
  1.��    ��   : 2016��08��30��
    ��    ��   : j00174725
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRpErr21Tpfcs197;                  /* DCM��Rp error 21 ,TPFCS 197�Ķ��� */                        
    VOS_UINT8                               ucReserved1;
    VOS_UINT8                               ucReserved2;
    VOS_UINT8                               ucReserved3;
} NAS_NVIM_SMS_RP_ERROR_CUSTOM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_EMC_CATE_SUPPORT_ECALL_CFG_STRU
 �ṹ˵��  : en_NV_Item_Emc_Cate_Support_ECALL_CFG NV��ṹ
 1. ��    ��   : 2017��02��18��
    ��    ��   : j00174725
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmcCateSupportEcallFlag; 
    VOS_UINT8                           ucBit8Is1OtherBitOKFlag;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EMC_CATE_SUPPORT_ECALL_CFG_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
