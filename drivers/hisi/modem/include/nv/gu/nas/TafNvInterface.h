/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TafNvInterface.h
  Description     : TafNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __TAFNVINTERFACE_H__
#define __TAFNVINTERFACE_H__

#include "vos.h"
#include "product_config.h"

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

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define AT_NVIM_SETZ_LEN                (16)
#define AT_NOTSUPPORT_STR_LEN           (16)

/* ���ȼ���������� */
#define ADS_UL_QUEUE_SCHEDULER_PRI_MAX  (9)

/*WIFI ��� NV����*/
#define AT_WIFI_BASIC_NV_LEN            (116)
#define AT_WIFI_SEC_NV_LEN              (205)

/*WIFI SSID KEY��󳤶�*/
#define AT_WIFI_SSID_LEN_MAX            (33)
#define AT_WIFI_KEY_LEN_MAX             (27)

/* ��Ȩģʽ�ַ������� */
#define AT_WIFI_WLAUTHMODE_LEN          (16)

/* ����ģʽ�ַ������� */
#define AT_WIFI_ENCRYPTIONMODES_LEN     (5)

/* WPA�������ַ������� */
#define AT_WIFI_WLWPAPSK_LEN            (65)

/* ���֧��4��SSID */
#define AT_WIFI_MAX_SSID_NUM            (4)

#define AT_WIFI_KEY_NUM                 (AT_WIFI_MAX_SSID_NUM)

#define TAF_CBA_NVIM_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM            (5)                 /* ��Чʱ���������������ָ��MCC���� */
#define TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM            (2)

/* 9130��չIPv6���˴�����չԭ��ֵ������ */
#define TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM      (20)

#define AT_AP_NVIM_XML_RPT_SRV_URL_LEN              (127)
#define AT_AP_XML_RPT_SRV_URL_LEN                   (127)
#define AT_AP_XML_RPT_SRV_URL_STR_LEN               (AT_AP_XML_RPT_SRV_URL_LEN + 1)
#define AT_AP_XML_RPT_INFO_TYPE_LEN                 (127)

/*WEB UI ������󳤶�*/
#define AT_WEBUI_PWD_MAX                            (16)
#define AT_WEBUI_PWD_MAX_SET                        (0)
#define AT_WEBUI_PWD_VERIFY                         (1)

#define AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN            (127)
#define AT_AP_NVIM_XML_RPT_INFO_TYPE_STR_LEN        (AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN + 1)
/* PRODUCT NAME*/
#define AT_PRODUCT_NAME_MAX_NUM                     (29)
#define AT_PRODUCT_NAME_LENGHT                      (AT_PRODUCT_NAME_MAX_NUM + 1)

#define TAF_NVIM_DFS_MAX_PROFILE_NUM                (8)

#define TAF_NVIM_DIFF_DFS_NUM                       (8)

#define TAF_NVIM_MAX_APN_LEN                        (99)
#define TAF_NVIM_MAX_APN_STR_LEN                    (TAF_NVIM_MAX_APN_LEN + 1)

#define AT_MAX_ABORT_CMD_STR_LEN                    (16)
#define AT_MAX_ABORT_RSP_STR_LEN                    (16)

#define AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM       (8)

#define AT_NVIM_RIGHT_PWD_LEN                       (16)

#define TAF_PH_NVIM_MAX_GUL_RAT_NUM                 (3)                 /*AT^syscfgex��acqorder����Ľ��뼼������ */

#define TAF_NVIM_ITEM_IMEI_SIZE                     (16)

#define AT_DISSD_PWD_LEN                            (16)

#define AT_OPWORD_PWD_LEN                           (16)

#define AT_FACINFO_INFO1_LENGTH                     (128)
#define AT_FACINFO_INFO2_LENGTH                     (128)
#define AT_FACINFO_STRING_LENGTH        \
((AT_FACINFO_INFO1_LENGTH + 1) + (AT_FACINFO_INFO2_LENGTH + 1))

#define AT_FACINFO_INFO1_STR_LENGTH                 (AT_FACINFO_INFO1_LENGTH + 1)
#define AT_FACINFO_INFO2_STR_LENGTH                 (AT_FACINFO_INFO2_LENGTH + 1)

#define AT_MDATE_STRING_LENGTH                      (20)

#define MMA_FORB_BAND_NV_MAX_SIZE                   (10)     /* FobBand��NV���� */

#define MMA_OPERTOR_NAME_MAX_SIZE                   (256)

#define TAF_PH_WCDMA_CLASSMAEK1_LEN                         (2)
#define TAF_PH_WCDMA_CLASSMAEK2_LEN                         (4)
#define TAF_PH_WCDMA_CLASSMAEK3_LEN                         (16)

#define TAF_MAX_MFR_ID_LEN                                  (31)
#define TAF_MAX_MFR_ID_STR_LEN                              (TAF_MAX_MFR_ID_LEN + 1)

#define NAS_MMA_NVIM_OPERATOR_NAME_LEN                      (360)

#define TAF_NVIM_ME_PERSONALISATION_PWD_LEN_MAX             (8)

#define TAF_NVIM_MAX_IMSI_LEN                               (15)
#define TAF_NVIM_MAX_IMSI_STR_LEN                           (TAF_NVIM_MAX_IMSI_LEN + 1)

#define TAF_NVIM_MSG_ACTIVE_MESSAGE_MAX_URL_LEN             (160)

/*^AUTHDATA�������û������������󳤶�*/
#define TAF_NVIM_MAX_NDIS_USERNAME_LEN_OF_AUTHDATA          (128)                            /* USERNAME Ϊ127 */
#define TAF_NVIM_MAX_NDIS_PASSWORD_LEN_OF_AUTHDATA          (128)                            /* PASSWORD Ϊ127 */

/*^AUTHDATA������<PLMN>��������󳤶�*/
#define TAF_NVIM_MAX_NDIS_PLMN_LEN                          (7)

#define TAF_NVIM_PDP_PARA_LEN                               (1952)

#define TAF_PH_PRODUCT_NAME_LEN                             (15)
#define TAF_PH_PRODUCT_NAME_STR_LEN                         (TAF_PH_PRODUCT_NAME_LEN + 1)

/* ����ҵ������ṹ��NV���д洢��λ�� */
#define MN_MSG_SRV_PARAM_LEN                                (8)                 /* ����ҵ������ṹ��NV���д洢�ĳ��� */
#define MN_MSG_SRV_RCV_SM_ACT_OFFSET                        (0)                 /* ���Ž����ϱ���ʽ��NV���д洢��ƫ�� */
#define MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET                  (1)                 /* ���Ž��մ洢������NV���д洢��ƫ�� */
#define MN_MSG_SRV_RCV_STARPT_ACT_OFFSET                    (2)                 /* ����״̬��������ϱ���ʽc */
#define MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET              (3)                 /* ����״̬������մ洢������NV���д洢��ƫ�� */
#define MN_MSG_SRV_CBM_MEM_STORE_OFFSET                     (4)                 /* �㲥���Ž��մ洢������NV���д洢��ƫ�� */
#define MN_MSG_SRV_APP_MEM_STATUS_OFFSET                    (5)                 /* APP���Ž��մ洢���ʿ��ñ�־��NV���д洢��ƫ�ƣ���Ӧ�ֽ�ȡֵ����0:�洢���洢���ʲ����� 1:�洢���д洢���ʿ��� */
#define MN_MSG_SRV_SM_MEM_ENABLE_OFFSET                     (6)                 /* ���Ž��մ洢������NV���д洢��־��NV���д洢��ƫ�ƣ���Ӧ�ֽ�ȡֵ����0:��ʹ�� 1:ʹ�� */
#define MN_MSG_SRV_MO_DOMAIN_PROTOCOL_OFFSET                (7)                 /* ���ŷ�����Э��Ҫ��ʵ�ֵ�ƫ�ƣ���Ӧ�ֽ�ȡֵ����0:��ʹ�� 1:ʹ�� */

#define MN_MSG_MAX_EF_LEN                                   (255)
#define MN_MSG_EFSMSS_PARA_LEN                              (256)
#define MN_MSG_EFSMSP_PARA_LEN                              (256)

#define TAF_PH_SIMLOCK_PLMN_STR_LEN                         (8)                 /* Plmn �Ŷγ��� */
#define TAF_MAX_SIM_LOCK_RANGE_NUM                          (20)

/* WINS������NV��Ľṹ�� */
#define WINS_CONFIG_DISABLE                                 (0)                 /* WINS��ʹ�� */
#define WINS_CONFIG_ENABLE                                  (1)                 /* WINSʹ�� */

#define TAF_CBA_NVIM_MAX_CBMID_RANGE_NUM                    (100)               /* �û������������ϢID��Χ�������ڽ���ģʽ�»�Ҫ�ܵ�CBMIR�ļ���С���� */
#define TAF_CBA_NVIM_MAX_LABEL_NUM                          (16)                /* �û����������������Ϣ�ĳ��ȣ���λBYTE */

#define TAF_SVN_DATA_LENGTH                                 (2)                 /* SVN��Ч���ݳ��� */

/*  ��ǰ֧�ֵ�UMTS��codec���ͽ�����3��,��Э���л�����չ����˴˴�Ԥ����չ���ֶ� */
#define MN_CALL_MAX_UMTS_CODEC_TYPE_NUM                     (7)

#define MN_CALL_NVIM_BC_MAX_SPH_VER_NUM                     (6)
#define MN_CALL_NVIM_MAX_CUSTOM_ECC_NUM                     (20)                /* �û����ƵĽ���������������� */

#define MN_CALL_NVIM_MAX_BCD_NUM_LEN                        (20)

#define TAF_AT_NVIM_CLIENT_CONFIG_LEN                       (64)

#define TAF_NVIM_CBA_MAX_LABEL_NUM                          (16)

#define MTA_BODY_SAR_WBAND_MAX_NUM                          (5)
#define MTA_BODY_SAR_GBAND_MAX_NUM                          (4)

#define MTC_RF_LCD_MIPICLK_MAX_NUM                          (8)                 /* MIPICLK������ */
#define MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM                     (8)                 /* ÿ��MIPICLKӰ������Ƶ�ʸ��� */

#define TAF_NV_BLACK_LIST_MAX_NUM                           (51)


#define TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM              (4)
#define TAF_NVIM_STORED_OPER_NAME_NUM                        (3)

#define TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM     (128)       /* IMS --> CS ��Ҫ�ز���ԭ��ֵ������Ϊ128 */
#define TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM    (64)        /* IMSA --> CS ��Ҫ�ز���ԭ��ֵ������Ϊ128 */


#define TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM            (32)
#define TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM               (32)
#define TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM              (32)
#define TAF_NVIM_SMS_NO_RETRY_RP_CAUSE_MAX_NUM        (32)

#define TAF_NVIM_CALL_RETRY_DISC_CAUSE_MAX_NUM               (64)

#define TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN          (48)

#define TAF_NVIM_CTCC_OOS_TIMER_MAX_PHASE              (10)

#define TAF_SIM_FORMAT_PLMN_LEN                        (3)                      /* Sim����ʽ��Plmn���� */
#define TAF_NVIM_OTA_SECURITY_MSG_IMSI_PLMN_MAX_NUM    (6)

#define TAF_NVIM_MAX_1X_NW_NORMAL_REL_REDIAL_PHASE_NUM (4)

#define TAF_NVIM_ICC_ID_MAX                             (11)
#define TAF_NVIM_RPM_RSV_PARA_NUM                       (26)


typedef VOS_UINT8  MN_CALL_STATE_ENUM_UINT8;

typedef VOS_UINT32  MMA_QUICK_START_STA_UINT32;
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/* ME Storage Function On or Off*/
enum MN_MSG_ME_STORAGE_STATUS_ENUM
{
    MN_MSG_ME_STORAGE_DISABLE           = 0x00,
    MN_MSG_ME_STORAGE_ENABLE            = 0x01,
    MN_MSG_ME_STORAGE_BUTT
};
typedef VOS_UINT8 MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8;

enum AT_UART_LINK_TYPE_ENUM
{
    AT_UART_LINK_TYPE_OM        = 1,          /* OMģʽ */
    AT_UART_LINK_TYPE_AT        = 2,          /* ATģʽ */
    AT_UART_LINK_TYPE_BUTT
};
typedef VOS_UINT16 AT_UART_LINK_TYPE_ENUM_UINT16;

enum MMA_CUSTOM_CARDLOCK_OPERATOR_ENUM
{
    MMA_CUSTOM_CARDLOCK_NO_AVAILABLE   = 0,                                     /* 0��Ĭ�ϲ��򿪣�ʹ�ÿ�����д���SIMLOCK */
    MMA_CUSTOM_CARDLOCK_EGYPT_VDF,                                              /* 1���򿪰���VDF���Ƶ�37��SIMLOCK */
    MMA_CUSTOM_CARDLOCK_NORWAY_NETCOM,                                          /* 2����Ų��Netcomm��SIMLOCK */
    MMA_CUSTOM_CARDLOCK_MEXICO_TELCEL,                                          /* 3����ī����TELCEL�����������Ŷ�334020 */
    MMA_CUSTOM_CARDLOCK_DOMINICA_TELCEL,                                        /* 4���򿪶������TELCEL�����������Ŷ�37002��33870��42502 */
    MMA_CUSTOM_CARDLOCK_BUTT
};


/*****************************************************************************
 ö����    : MTA_WCDMA_BAND_ENUM
 �ṹ˵��  : WCDMAƵ�ζ���
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : ����ö��
*****************************************************************************/
enum MTA_WCDMA_BAND_ENUM
{
    MTA_WCDMA_I_2100                    = 0x0001,
    MTA_WCDMA_II_1900,
    MTA_WCDMA_III_1800,
    MTA_WCDMA_IV_1700,
    MTA_WCDMA_V_850,
    MTA_WCDMA_VI_800,
    MTA_WCDMA_VII_2600,
    MTA_WCDMA_VIII_900,
    MTA_WCDMA_IX_J1700,
    /* Ƶ���ݲ�֧��
    MTA_WCDMA_X,
    */
    MTA_WCDMA_XI_1500                   = 0x000B,
    /* ����Ƶ���ݲ�֧��
    MTA_WCDMA_XII,
    MTA_WCDMA_XIII,
    MTA_WCDMA_XIV,
    MTA_WCDMA_XV,
    MTA_WCDMA_XVI,
    MTA_WCDMA_XVII,
    MTA_WCDMA_XVIII,
    */
    MTA_WCDMA_XIX_850                   = 0x0013,

    MTA_WCDMA_BAND_BUTT
};
typedef VOS_UINT16 MTA_WCDMA_BAND_ENUM_UINT16;

/* Added by s00246516 for L-C��������Ŀ, 2014-01-23, Begin */
/*****************************************************************************
 ö����    : TAF_NVIM_LC_WORK_CFG_ENUM
 �ṹ˵��  : L-C��������������
 1.��    ��   : 2014��01��23��
   ��    ��   : s00246516
   �޸�����   : ����ö��
*****************************************************************************/
enum TAF_NVIM_LC_WORK_CFG_ENUM
{
    TAF_NVIM_LC_INDEPENT_WORK = 0,
    TAF_NVIM_LC_INTER_WORK    = 1,
    TAF_NVIM_LC_WORK_CFG_BUTT
};
typedef VOS_UINT8 TAF_NVIM_LC_WORK_CFG_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_NVIM_LC_RAT_COMBINED_ENUM
 �ṹ˵��  : L-C��������������
 1.��    ��   : 2014��01��23��
   ��    ��   : s00246516
   �޸�����   : ����ö��
*****************************************************************************/
enum TAF_NVIM_LC_RAT_COMBINED_ENUM
{
    TAF_NVIM_LC_RAT_COMBINED_GUL  = 0x55,
    TAF_NVIM_LC_RAT_COMBINED_CL   = 0xAA,
    TAF_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8;
/* Added by s00246516 for L-C��������Ŀ, 2014-01-23, End */

/*****************************************************************************
 ö����    : MTC_PS_TRANSFER_ENUM
 �ṹ˵��  : PSǨ�� ������ѡ����ö��
 1.��    ��   : 2014��01��17��
   ��    ��   : l00198894
   �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
enum MTC_PS_TRANSFER_ENUM
{
    MTC_PS_TRANSFER_NONE                = 0x00,                                 /* ��PS��Ǩ�Ʋ��� */
    MTC_PS_TRANSFER_LOST_AREA           = 0x01,                                 /* ������ѡ���� */
    MTC_PS_TRANSFER_OFF_AREA            = 0x02,                                 /* ������ѡ���� */

    MTC_PS_TRANSFER_SOLUTION_BUTT
};
typedef VOS_UINT8 MTC_PS_TRANSFER_ENUM_UINT8;


enum TAF_NV_CLIENT_CFG_ENUM
{
    TAF_NV_CLIENT_CFG_PCUI              = 0,
    TAF_NV_CLIENT_CFG_CTRL              = 1,
    TAF_NV_CLIENT_CFG_MODEM             = 2,
    TAF_NV_CLIENT_CFG_NDIS              = 3,
    TAF_NV_CLIENT_CFG_UART              = 4,
    TAF_NV_CLIENT_CFG_SOCK              = 5,
    TAF_NV_CLIENT_CFG_APPSOCK           = 6,
    TAF_NV_CLIENT_CFG_HSIC1             = 7,
    TAF_NV_CLIENT_CFG_HSIC2             = 8,
    TAF_NV_CLIENT_CFG_HSIC3             = 9,
    TAF_NV_CLIENT_CFG_HSIC4             = 10,
    TAF_NV_CLIENT_CFG_MUX1              = 11,
    TAF_NV_CLIENT_CFG_MUX2              = 12,
    TAF_NV_CLIENT_CFG_MUX3              = 13,
    TAF_NV_CLIENT_CFG_MUX4              = 14,
    TAF_NV_CLIENT_CFG_MUX5              = 15,
    TAF_NV_CLIENT_CFG_MUX6              = 16,
    TAF_NV_CLIENT_CFG_MUX7              = 17,
    TAF_NV_CLIENT_CFG_MUX8              = 18,
    TAF_NV_CLIENT_CFG_APP               = 19,
    TAF_NV_CLIENT_CFG_APP1              = 20,
    TAF_NV_CLIENT_CFG_APP2              = 21,
    TAF_NV_CLIENT_CFG_APP3              = 22,
    TAF_NV_CLIENT_CFG_APP4              = 23,
    TAF_NV_CLIENT_CFG_APP5              = 24,
    TAF_NV_CLIENT_CFG_APP6              = 25,
    TAF_NV_CLIENT_CFG_APP7              = 26,
    TAF_NV_CLIENT_CFG_APP8              = 27,
    TAF_NV_CLIENT_CFG_APP9              = 28,
    TAF_NV_CLIENT_CFG_APP10             = 29,
    TAF_NV_CLIENT_CFG_APP11             = 30,
    TAF_NV_CLIENT_CFG_APP12             = 31,
    TAF_NV_CLIENT_CFG_APP13             = 32,
    TAF_NV_CLIENT_CFG_APP14             = 33,
    TAF_NV_CLIENT_CFG_APP15             = 34,
    TAF_NV_CLIENT_CFG_APP16             = 35,
    TAF_NV_CLIENT_CFG_APP17             = 36,
    TAF_NV_CLIENT_CFG_APP18             = 37,
    TAF_NV_CLIENT_CFG_APP19             = 38,
    TAF_NV_CLIENT_CFG_APP20             = 39,
    TAF_NV_CLIENT_CFG_APP21             = 40,
    TAF_NV_CLIENT_CFG_APP22             = 41,
    TAF_NV_CLIENT_CFG_APP23             = 42,
    TAF_NV_CLIENT_CFG_APP24             = 43,
    TAF_NV_CLIENT_CFG_APP25             = 44,
    TAF_NV_CLIENT_CFG_APP26             = 45,
    TAF_NV_CLIENT_CFG_HSIC_MODEM        = 46,
    TAF_NV_CLIENT_CFG_HSUART            = 47,
    TAF_NV_CLIENT_CFG_PCUI2             = 48,

    TAF_NV_CLIENT_CFG_MAX               = TAF_AT_NVIM_CLIENT_CONFIG_LEN
};
typedef VOS_UINT16 TAF_NV_CLIENT_CFG_ENUM_UINT16;
/*****************************************************************************
 ö����    : TAF_FLASH_DIRECTORY_TYPE_ENUM
 �ṹ˵��  : FLASH�ļ��洢·������
 1.��    ��   : 2014��03��04��
   ��    ��   : f62575
   �޸�����   : DTS2013091009786 ֧��ͨ����Ʒ��̬�Ͱ汾����FLASH�ļ���Ŀ¼
*****************************************************************************/
enum TAF_FLASH_DIRECTORY_TYPE_ENUM
{

    /* V3R3�汾��E5��STICK */
    TAF_FLASH_DIRECTORY_TYPE_V3R3E5_V3R3STICK               = 0x00,

    /* V7R2�汾��V3R3�汾��M2M��Ʒ��̬ */
    TAF_FLASH_DIRECTORY_TYPE_V7R2_V3R3M2M                   = 0x01,

    /* V9R1�ֻ� */
    TAF_FLASH_DIRECTORY_TYPE_V9R1PHONE                      = 0x02,

    /* FLASH�ļ��洢��һ·������ǰ��������K3V3V8R1�汾 */
    TAF_FLASH_DIRECTORY_TYPE_K3V3V8R1                       = 0x03,

    TAF_FLASH_DIRECTORY_TYPE_BUTT
};
typedef VOS_UINT8 TAF_FLASH_DIRECTORY_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : TAF_NVIM_RAT_MODE_ENUM
 �ṹ˵��  : ��Ƶ�����еĽ���ģʽö��
 1.��    ��   : 2014��06��03��
   ��    ��   : g00261581
   �޸�����   : V711 Cell Lock��Ŀ
*****************************************************************************/
enum TAF_NVIM_RAT_MODE_ENUM
{
    TAF_NVIM_RAT_MODE_GSM               = 0x01,
    TAF_NVIM_RAT_MODE_WCDMA,
    TAF_NVIM_RAT_MODE_LTE,
    TAF_NVIM_RAT_MODE_CDMA1X,
    TAF_NVIM_RAT_MODE_TDSCDMA,
    TAF_NVIM_RAT_MODE_WIMAX,
    TAF_NVIM_RAT_MODE_EVDO,

    TAF_NVIM_RAT_MODE_BUTT
};
typedef VOS_UINT8 TAF_NVIM_RAT_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_NVIM_GSM_BAND_ENUM
 �ṹ˵��  : GSMƵ�ζ���
 1.��    ��   : 2014��06��04��
   ��    ��   : g00261581
   �޸�����   : ����ö��
*****************************************************************************/
enum TAF_NVIM_GSM_BAND_ENUM
{
    TAF_NVIM_GSM_BAND_850               = 0,
    TAF_NVIM_GSM_BAND_900,
    TAF_NVIM_GSM_BAND_1800,
    TAF_NVIM_GSM_BAND_1900,

    TAF_NVIM_GSM_BAND_BUTT
};
typedef VOS_UINT16 TAF_NVIM_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
 ö����    : TAF_NV_ACTIVE_MODEM_MODE_ENUM
 �ṹ˵��  : DSDS��Ʒ��Modemģʽö��
 1.��    ��   : 2014��09��21��
   ��    ��   : l00198894
   �޸�����   : ����DSDS��/˫������
*****************************************************************************/
enum TAF_NV_ACTIVE_MODEM_MODE_ENUM
{
    TAF_NV_ACTIVE_SINGLE_MODEM              = 0x00,
    TAF_NV_ACTIVE_MULTI_MODEM               = 0x01,

    TAF_NV_ACTIVE_MODEM_MODE_BUTT
};
typedef VOS_UINT8 TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CNAS_XSMS_DATA_REQ_SEND_CHAN_ENUM
 ö��˵��  : ���ŷ��͵��ŵ�ָʾ
*****************************************************************************/
enum TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM
{
    TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN   = 0x0,
    TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN    = 0x1,
    TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH           = 0x2,
    TAF_XSMS_DATA_REQ_SEND_CHAN_BUTT
};

typedef VOS_UINT8 TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM
 *
 * Description :
 *******************************************************************************/
enum TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM
{
    TAF_MMA_CFREQ_LOCK_MODE_OFF         = 0x00,     /* ��ֹ��Ƶ���� */
    TAF_MMA_CFREQ_LOCK_MODE_ON          = 0x01,     /* ������Ƶ���� */
    TAF_MMA_CFREQ_LOCK_MODE_BUTT        = 0x02
};
typedef VOS_UINT8 TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_VC_TTYMODE_ENUM
 �ṹ˵��  : TTYģʽ״̬ö��
  1.��    ��   : 2015��02��07��
    ��    ��   : w00316404
    �޸�����   : �½�
*****************************************************************************/
enum TAF_VC_TTYMODE_ENUM
{
    TAF_VC_TTY_OFF                      = 0,
    TAF_VC_TTY_FULL                     = 1,
    TAF_VC_TTY_VCO                      = 2,
    TAF_VC_TTY_HCO                      = 3,
    TAF_VC_TTYMODE_BUTT
};
typedef VOS_UINT8 TAF_VC_TTYMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_CALL_CCWA_CTRL_MODE_ENUM
 ö��˵��  : ���еȴ�����ģʽö��
 1.��    ��   : 2015��8��24��
   ��    ��   : n00269697
   �޸�����   : �½�
*****************************************************************************/
enum TAF_CALL_CCWA_CTRL_MODE_ENUM
{
    TAF_CALL_CCWA_CTRL_BY_NW          = 0,
    TAF_CALL_CCWA_CTRL_BY_UE            = 1,

    TAF_CALL_CCWA_CTRL_MODE_BUTT
};
typedef VOS_UINT8   TAF_CALL_CCWA_CTRL_MODE_ENUM_U8;

/*****************************************************************************
 ö����    : TAF_CALL_CCWAI_MODE_ENUM
 ö��˵��  : ���еȴ�����ģʽ

 1.��    ��   : 2016��02��16��
   ��    ��   : n00269697
   �޸�����   : DTS2016021506132��ccwai������call����call��ims�ṩ�ӿ�����ѯ
*****************************************************************************/
enum TAF_CALL_CCWAI_MODE_ENUM
{
    TAF_CALL_CCWAI_MODE_DISABLE               = 0,
    TAF_CALL_CCWAI_MODE_ENABLE                = 1,

    TAF_CALL_CCWAI_MODE_BUTT
};
typedef  VOS_UINT8  TAF_CALL_CCWAI_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM
 �ṹ˵��  : TL_ACK��Ҫ����Ҫ�ж�ö��
  1.��    ��   : 2016��01��19��
    ��    ��   : c00299064
    �޸�����   : �½�
*****************************************************************************/
enum TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM
{
    TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NEEDED                    = 0,
    TAF_XSMS_TL_ACK_NEED_LEVEL_NOT_NEEDED_WHEN_RCV_SMS          = 1,  /* �����Ͷ��Ź����У��յ����ŵ�ʱ�򣬿��Բ��ж�TL_ACK */
    TAF_XSMS_TL_ACK_NEED_LEVEL_ALWAYS_NOT_NEEDED                = 2,  /* �����Ͷ��Ź����У�����Ҫ�ж�TL_ACK */

    TAF_XSMS_TL_ACK_NEED_LEVEL_BUTT
};
typedef VOS_UINT8 TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM_UINT8
 �ṹ˵��  : ȫģ������CS����������: 3GPP2���Ȼ���3GPP����
  1.��    ��   : 2016��07��19��
    ��    ��   : y00245242
    �޸�����   : �½�
*****************************************************************************/
enum TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM
{
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_3GPP_PRFER                = 0,
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_3GPP2_PRFER               = 1,
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_3GPP_ONLY                 = 2,
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_3GPP2_ONLY                = 3,

    TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_BUTT                = 4
};
typedef VOS_UINT8 TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : TAF_AT_TZ_STRU
 �ṹ˵��  : en_NV_Item_ATSETZ_RET_VALUE NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_CHAR    acTz[AT_NVIM_SETZ_LEN];
}TAF_AT_TZ_STRU;

/*****************************************************************************
 �ṹ��    : AT_NOT_SUPPORT_CMD_ERROR_TEXT_STRU
 �ṹ˵��  : en_NV_Item_NOT_SUPPORT_RET_VALUE NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_CHAR    acErrorText[AT_NOTSUPPORT_STR_LEN];
}TAF_AT_NOT_SUPPORT_CMD_ERROR_TEXT_STRU;

/*****************************************************************************
�ṹ��    : ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU
�ṹ˵��  : ADS���ж������ȼ���NV�ṹ

  1.��    ��   : 2012��02��24��
    ��    ��   : f00179208
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    /* ��NV���״̬ 0:δʹ�ܣ���ʾ���������ȼ����ȼ����ȴ��� 1:ʹ�ܣ��������ȼ��㷨 */
    VOS_UINT32                              ulStatus;

    /* ���ж������ȼ��ļ�Ȩ�� */
    VOS_UINT16                              ausPriWeightedNum[ADS_UL_QUEUE_SCHEDULER_PRI_MAX];
    VOS_UINT8                               aucRsv[2];
}ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU;

/*****************************************************************************
 �ṹ��    : TAF_TAF_AT_MULTI_WIFI_SSID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : en_NV_Item_MULTI_WIFI_STATUS_SSID NV���Ӧ�Ľṹ��
             ���ڱ���wifi SSID����NV�ṹ���£����ڳ���SSID����Ĳ��ֲ�����
             �κβ�����Ϊ�˱�������PADDING���ڶ���ʱֱ�Ӷ���ΪUINT8���͵�����
             aucwlSsid[AT_WIFI_MAX_SSID_NUM][AT_WIFI_SSID_LEN_MAX];
             ulwlChannel;
             ulwlHide;
             aucwlCountry[NV_WLCOUNTRY_CODE_LEN];
             aucwlMode[NV_WLMODE_LEN];
             ulwlRate;
             ulwlTxPwrPcnt;
             ulwlMaxAssoc;
             ucwlEnbl;
             ulwlFrgThrshld;
             ulwlRtsThrshld;
             ulwlDtmIntvl;
             ulwlBcnIntvl;
             ulwlWme;
             ulwlPamode;
             ulwlIsolate;
             ulwlProtectionmode;
             ulwloffenable;
             ucwlofftime;
             aucwlExtends[12];
             ucReserve;

  1.��    ��   : 2012��9��15��
    ��    ��   : z60575
    �޸�����   : �����ṹ
*****************************************************************************/

typedef struct
{

    VOS_UINT8    aucWifiSsid[AT_WIFI_MAX_SSID_NUM][AT_WIFI_SSID_LEN_MAX];
    VOS_UINT8    aucReserved[84];
}TAF_AT_MULTI_WIFI_SSID_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_MULTI_WIFI_SEC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : en_NV_Item_MULTI_WIFI_KEY NV���Ӧ�Ľṹ��
             ���ڱ���wifi ��ȫ��Ϣ
             nv_wifisec_type�ṹ�ĸ���������NV��50012�����ݽṹnv_wifisec_type����һ��
             aucwlAuthMode              ��Ȩģʽ
             aucBasicEncryptionModes    ��������ģʽ
             aucWPAEncryptionModes      WPA����ģʽ
             aucWifiWepKey1...aucWifiWepKey4               WIFI KEY
             ucWifiWepKeyIndex          ʹ�õ�WIFI KEY index,���磬1����ʹ��wlKeys1
             aucWpaPsk                  WPA������
             ucWpsEnable                wps�Ƿ�ʹ�ܿ���
             ucWpsCfg                   �Ƿ�����register���ı�enrollee�Ĳ���,  0:������(Ĭ��);  1:����

  1.��    ��   : 2012��9��15��
    ��    ��   : z60575
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucWifiAuthmode[AT_WIFI_WLAUTHMODE_LEN];
    VOS_UINT8    aucWifiBasicencryptionmodes[AT_WIFI_ENCRYPTIONMODES_LEN];
    VOS_UINT8    aucWifiWpaencryptionmodes[AT_WIFI_ENCRYPTIONMODES_LEN];
    VOS_UINT8    aucWifiWepKey1[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey2[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey3[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    aucWifiWepKey4[AT_WIFI_MAX_SSID_NUM][AT_WIFI_KEY_LEN_MAX];
    VOS_UINT8    ucWifiWepKeyIndex[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8    aucWifiWpapsk[AT_WIFI_MAX_SSID_NUM][AT_WIFI_WLWPAPSK_LEN];
    VOS_UINT8    ucWifiWpsenbl;
    VOS_UINT8    ucWifiWpscfg;
}TAF_AT_MULTI_WIFI_SEC_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_AP_RPT_SRV_URL_STRU
 �ṹ˵��  : TAF_AT_NVIM_AP_RPT_SRV_URL_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucApRptSrvUrl[AT_AP_XML_RPT_SRV_URL_STR_LEN];
}TAF_AT_NVIM_AP_RPT_SRV_URL_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU
 �ṹ˵��  : en_NV_Item_WEB_ADMIN_PASSWORD�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucWebPwd[AT_WEBUI_PWD_MAX];
}TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU
 �ṹ˵��  : TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucApXmlInfoType[AT_AP_NVIM_XML_RPT_INFO_TYPE_STR_LEN];
}TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU;

/*****************************************************************************
 �ṹ��    : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU
 �ṹ˵��  : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    VOS_UINT32                          ulNvStatus;
    VOS_UINT8                           aucProductId[AT_PRODUCT_NAME_LENGHT];   /* product id */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_PRODUCT_ID_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/* ����TIM���Ŵ�����NV��ṹ�� */
/*****************************************************************************
 �ṹ��    : NAS_NV_PPP_DIAL_ERR_CODE_STRU
 �ṹ˵��  : en_NV_Item_PPP_DIAL_ERR_CODE(50061)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : m00217266
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucErrCodeRpt;                           /*�������ϱ���־1: 0�����ϱ�,  1���ϱ�*/
}NAS_NV_PPP_DIAL_ERR_CODE_STRU;

/*****************************************************************************
 �ṹ��    : AT_NVIM_ABORT_CMD_PARA_STRU
 �ṹ˵��  : ��������AT���������������ͷ��ؽ���Ľṹ, NV��ʹ��
             �������û�����"AT"��ʾ����������, ����"ABORT"��ʾ������. �����ִ�Сд

  1.��    ��   : 2012��09��21��
    ��    ��   : L00171473
    �޸�����   : for V7R1C50_At_Abort,  ����
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAbortEnableFlg;                           /* AT��Ͽ��ر�־ */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN]; /* ���AT������ */
    VOS_UINT8                           aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN]; /* �������ķ��ؽ�� */
}AT_NVIM_ABORT_CMD_PARA_STRU;

/*****************************************************************************
�ṹ��    : AT_BODYSARGSM_SET_PARA_STRU
�ṹ˵��  : Body SAR������������ṹ��
1.��    ��  : 2013��03��12��
  ��    ��  : l00198894
  �޸�����  : Body SAR��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucParaNum;                                      /* ��������������� */
    VOS_UINT8                   ucRsv[3];                                       /* ����λ */
    VOS_INT16                   asPower[AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM];      /* GƵ�ι�������ֵ */
    VOS_UINT32                  aulBand[AT_NVIM_BODYSARGSM_MAX_PARA_GROUP_NUM];      /* GƵ��λ�� */
}AT_BODYSARGSM_SET_PARA_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU
 �ṹ˵��  : en_NV_Item_AT_RIGHT_PASSWORD NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enRightOpenFlg;
    VOS_INT8                            acPassword[AT_NVIM_RIGHT_PWD_LEN];
}TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_GWMAC_ADDR_STRU
 �ṹ˵��  : RABM_TOTAL_RX_BYTES(39126)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulDSTotalSendFluxLow;
    VOS_UINT32 ulDSTotalSendFluxHigh;
    VOS_UINT32 ulDSTotalReceiveFluxLow;
    VOS_UINT32 ulDSTotalReceiveFluxHigh;
    TAF_AT_NVIM_RIGHT_OPEN_FLAG_STRU stRightPwd;
}NAS_NV_RABM_TOTAL_RX_BYTES_STRU;

/*****************************************************************************
�ṹ��    : IMEI_STRU
�ṹ˵��  : en_NV_Item_IMEI(0)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucImei[TAF_NVIM_ITEM_IMEI_SIZE];
}IMEI_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_DISSD_PWD_STRU
�ṹ˵��  : en_NV_Item_AT_DISSD_PWD(43)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_INT8                           acATE5DissdPwd[AT_DISSD_PWD_LEN];
}TAF_AT_NVIM_DISSD_PWD_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_DISLOG_PWD_NEW_STRU
�ṹ˵��  : en_NV_Item_AT_DISLOG_PWD_NEW(48)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_INT8                           acATOpwordPwd[AT_OPWORD_PWD_LEN];
}TAF_AT_NVIM_DISLOG_PWD_NEW_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_EQ_VER_STRU
 �ṹ˵��  : TAF_AT_EQ_VER_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEqver;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_EQ_VER_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_CS_VER_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCsver;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_NVIM_CS_VER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucEnableFlag;
    VOS_UINT8   ucReserve;
}NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU;

/*****************************************************************************
 �ṹ����   : AT_IPV6_CAPABILITY_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IPV6����NV����ƽṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;           /* NV��Ч��־, 1: ��Ч��0����Ч */
    VOS_UINT8                           ucIpv6Capablity;    /* IPV6���� */
    VOS_UINT8                           aucReversed[2];     /* ���ֽڶ��� */

} AT_NV_IPV6_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{

    VOS_UINT8   ucGsmConnectRate;
    VOS_UINT8   ucGprsConnectRate;
    VOS_UINT8   ucEdgeConnectRate;
    VOS_UINT8   ucWcdmaConnectRate;
    VOS_UINT8   ucDpaConnectRate;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}AT_NVIM_DIAL_CONNECT_DISPLAY_RATE_STRU;

/*****************************************************************************
 �ṹ��    : AT_TRAFFIC_CLASS_CUSTOMIZE_STRU
 �ṹ˵��  : ���ڶ���PDP����������QoS�� Traffic Class��ֵ�Ľṹ��
*****************************************************************************/

typedef struct
{
    VOS_UINT8                          ucStatus;                         /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                          ucTrafficClass;                   /* Traffic Class��ֵ */
    VOS_UINT8                          ucReserve1;
    VOS_UINT8                          ucReserve2;
}AT_TRAFFIC_CLASS_CUSTOMIZE_STRU;

/*****************************************************************************
�ṹ��    : AT_SS_CUSTOMIZE_PARA_STRU
�ṹ˵��  : SS���Ʋ���������
            NV����־ucStatus��0: �����1: ����
            SS��׼����Ʋ���
            BIT 0 ����+CCWA��ѯ�����Ƿ��������ҵ��״̬��0������� ��1: ���
            BIT 1 ����+CLCK��ѯ�����Ƿ��������ҵ��״̬��0������� ��1: ���
1.��    ��  : 2013��01��24��
  ��    ��  : f62575
  �޸�����  : SS�������������ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־,  */
    VOS_UINT8                           ucSsCmdCustomize;
    VOS_UINT8                           aucReserved1[2];
} AT_SS_CUSTOMIZE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_CIMI_PORT_CFG_STRU
 �ṹ˵��  : TAF_AT_NVIM_CIMI_PORT_CFG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulCimiPortCfg;
}TAF_AT_NVIM_CIMI_PORT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_MUX_REPORT_CFG_STRU
 �ṹ˵��  : TAF_AT_NVIM_MUX_REPORT_CFG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulMuxReportCfg;
}TAF_AT_NVIM_MUX_REPORT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MN_NVIM_TOTAL_MSG_STRU
 �ṹ˵��  : NAS_MN_NVIM_TOTAL_MSG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulTotalMsg;
}NAS_MN_NVIM_TOTAL_MSG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_AP_XML_RPT_FLG_STRU
 �ṹ˵��  : TAF_AT_NVIM_AP_XML_RPT_FLG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucApXmlRptFlg;
    VOS_UINT8   ucReserve[3];
}TAF_AT_NVIM_AP_XML_RPT_FLG_STRU;


/*****************************************************************************
 �ṹ��    : AT_CLIENT_BASIC_INFO_STRU
 �ṹ˵��  : ATͨ���Ļ���������Ϣ

  1.��    ��   : 2012��12��20��
    ��    ��   : L60609
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usModemId;                              /* �ö˿������ĸ�modem */
    VOS_UINT8                           ucReportFlg;                            /* �ö˿��Ƿ����������ϱ���VOS_TRUEΪ����VOS_FALSEΪ������Ĭ������ */
    VOS_UINT8                           aucRsv[1];
}AT_NVIM_CLIENT_CONFIGURATION_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMA_NVIM_FORBAND_STRU
 �ṹ˵��  : NAS_MMA_NVIM_FORBAND_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucForband[MMA_FORB_BAND_NV_MAX_SIZE];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_FORBAND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMA_NVIM_OPERATOR_NAME_STRU
 �ṹ˵��  : NAS_MMA_NVIM_OPERATOR_NAME_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucRcvData[MMA_OPERTOR_NAME_MAX_SIZE];
}NAS_MMA_NVIM_OPERATOR_NAME_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU
�ṹ˵��  : en_NV_Item_FollowOn_OpenSpeed_Flag(6656)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MMA_QUICK_START_STA_UINT32          ulQuickStartSta;
}NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_CLASSMARK1_STRU
�ṹ˵��  : en_NV_Item_Classmark1(8194)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucClassmark1[TAF_PH_WCDMA_CLASSMAEK1_LEN];
}NAS_MMA_NVIM_CLASSMARK1_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_CLASSMARK2_STRU
�ṹ˵��  : en_NV_Item_Classmark2(8195)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucClassmark2[TAF_PH_WCDMA_CLASSMAEK2_LEN];
}NAS_MMA_NVIM_CLASSMARK2_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_CLASSMARK3_STRU
�ṹ˵��  : en_NV_Item_Classmark3(8196)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucClassmark3[TAF_PH_WCDMA_CLASSMAEK3_LEN];
}NAS_MMA_NVIM_CLASSMARK3_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_SMS_SERVICE_PARA_STRU
�ṹ˵��  : en_NV_Item_SMS_SERVICE_Para(8237)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSmsServicePara[MN_MSG_SRV_PARAM_LEN];
}TAF_NVIM_SMS_SERVICE_PARA_STRU;

/*****************************************************************************
�ṹ��    : TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU
�ṹ˵��  : en_NV_Item_SMS_EFSMSS_Para(8238)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSmsEfsmssPara[MN_MSG_EFSMSS_PARA_LEN];
}TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU;

/*****************************************************************************
�ṹ��    : TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU
�ṹ˵��  : en_NV_Item_SMS_EFSMSP_Para(8239)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSmsEfsmspPara[MN_MSG_EFSMSP_PARA_LEN];
}TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_SIM_PERSONAL_PWD_STRU
�ṹ˵��  : en_NV_Item_Sim_Personalisation_Pwd(8253)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8  aucPwd[TAF_NVIM_ME_PERSONALISATION_PWD_LEN_MAX];
}TAF_MMA_SIM_PERSONAL_PWD_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_SIM_PERSONAL_IMST_STRU
�ṹ˵��  : en_NV_Item_Sim_Personalisation_Imsi_Str(8254)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8  aucImsiStr[TAF_NVIM_MAX_IMSI_STR_LEN];
}NAS_MMA_SIM_PERSONAL_IMST_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_DISPLAY_SPN_FLAG_STRU
�ṹ˵��  : en_NV_Item_Display_Spn_Flag(8296)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucDisplaySpnFlag[2];
}NAS_MMA_NVIM_DISPLAY_SPN_FLAG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_RXDIV_CONFIG_STRU
�ṹ˵��  : en_NV_Item_RXDIV_CONFIG(8319)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucVaild;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}TAF_AT_NVIM_RXDIV_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_SMS_ACTIVE_MESSAGE_STRU
�ṹ˵��  : en_NV_Item_SMS_ActiveMessage_Para(8322)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    VOS_INT8    cStatus;
    VOS_UINT8   ucEncodeType;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT32  ulLength;
    VOS_UINT8   ucData[TAF_NVIM_MSG_ACTIVE_MESSAGE_MAX_URL_LEN];
}TAF_AT_NVIM_SMS_ACTIVE_MESSAGE_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*8301-8312���ýṹ��*/
/*****************************************************************************
�ṹ��    : TAF_NVIM_NDIS_AUTHDATA_STRU
�ṹ˵��  : en_NV_Item_NDIS_Authdata_0(8301-8312)�ṹ��Ƕ�׽ṹ��#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAuthType;
    VOS_UINT8                           aucPlmn[TAF_NVIM_MAX_NDIS_PLMN_LEN];
    VOS_UINT8                           aucPassword[TAF_NVIM_MAX_NDIS_PASSWORD_LEN_OF_AUTHDATA];
    VOS_UINT8                           aucUsername[TAF_NVIM_MAX_NDIS_USERNAME_LEN_OF_AUTHDATA];
}TAF_NVIM_NDIS_AUTHDATA_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_NDIS_AUTHDATA_TABLE_STRU
�ṹ˵��  : en_NV_Item_NDIS_Authdata_0(8301-8312)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                             /*0��δʹ�ã�1��ʹ��*/
    VOS_UINT8                           aucRsv[3];
    TAF_NVIM_NDIS_AUTHDATA_STRU         stAuthData;                                         /*��Ȩ����*/
}TAF_NVIM_NDIS_AUTHDATA_TABLE_STRU;

/*8451-8462���ýṹ�� en_NV_Item_Taf_PdpPara_0*/
/*****************************************************************************
�ṹ��    : TAF_NVIM_PDP_PARA_STRU
�ṹ˵��  : en_NV_Item_Taf_PdpPara_0(8451-8462)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8          aucPdpPara[TAF_NVIM_PDP_PARA_LEN];
}TAF_NVIM_PDP_PARA_STRU;

/* en_NV_Item_ProductName 8205 */
/*****************************************************************************
�ṹ��    : TAF_PH_PRODUCT_NAME_STRU
�ṹ˵��  : en_NV_Item_ProductName(8205)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8          aucProductName[TAF_PH_PRODUCT_NAME_STR_LEN];
}TAF_PH_PRODUCT_NAME_STRU;

/*en_NV_Item_Imei_Svn 8337*/
/*****************************************************************************
�ṹ��    : TAF_SVN_DATA_STRU
�ṹ˵��  : en_NV_Item_Imei_Svn(8337)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;
    VOS_UINT8                           aucSvn[TAF_SVN_DATA_LENGTH];
    VOS_UINT8                           aucReserve[1];
}TAF_SVN_DATA_STRU;

/*en_NV_Item_SMS_MO_RETRY_PERIOD 8293*/
/*****************************************************************************
�ṹ��    : MN_MSG_NVIM_RETRY_PERIOD_STRU
�ṹ˵��  : en_NV_Item_SMS_MO_RETRY_PERIOD(8293)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;                                           /* NVIM�и����Ƿ񼤻� */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulRetryPeriod;                                      /*�����ط�������*/
}MN_MSG_NVIM_RETRY_PERIOD_STRU;

/*en_NV_Item_SMS_MO_RETRY_INTERVAL 8294*/
/*****************************************************************************
�ṹ��    : MN_MSG_NVIM_RETRY_INTERVAL_STRU
�ṹ˵��  : en_NV_Item_SMS_MO_RETRY_INTERVAL(8294)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;                               /* NVIM�и����Ƿ񼤻� */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulRetryInterval;                        /*�����ط���ʱ����*/
}MN_MSG_NVIM_RETRY_INTERVAL_STRU;

/*****************************************************************************
�ṹ��    : TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU
�ṹ˵��  : en_NV_Item_SMS_RETRY_CN_SRV_REJ_CAUSE_CFG��Ӧ�Ľṹ��
  1.��    ��   : 2015��8��29��
    ��    ��   : s00217060
    �޸�����   : �½�
*****************************************************************************/typedef struct
{
    VOS_UINT8                           ucSmsRetryCmSrvRejCauseNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucSmsRetryCmSrvRejCause[TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM];
}TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU;

/*****************************************************************************
�ṹ��    : TAF_MSG_NVIM_NO_RETRY_RP_CAUSE_CFG_STRU
�ṹ˵��  : en_NV_Item_SMS_RETRY_RP_CAUSE_CFG��Ӧ�Ľṹ��
  1.��    ��   : 2016��5��14��
    ��    ��   : n00269697
    �޸�����   : ��Ϊԭ������RP CAUSE������Ҫ�ط��ģ�ֻ��38��ԭ��ֵ�����󲻳䷢�����Զ��岻�ط�ԭ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsNoRetryRpCauseNum;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT8                           aucReserved3;
    VOS_UINT8                           aucSmsNoRetryRpCause[TAF_NVIM_SMS_NO_RETRY_RP_CAUSE_MAX_NUM];
}TAF_MSG_NVIM_NO_RETRY_RP_CAUSE_CFG_STRU;

/*en_NV_Item_SMS_SEND_DOMAIN 8295*/
/* NVIM���ж��ŷ�����Ľṹ */
/*****************************************************************************
�ṹ��    : AT_NVIM_SEND_DOMAIN_STRU
�ṹ˵��  : en_NV_Item_SMS_SEND_DOMAIN(8295)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucSendDomain;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}AT_NVIM_SEND_DOMAIN_STRU;

/*en_NV_Item_WINS_Config 8297*/
/*****************************************************************************
�ṹ��    : WINS_CONFIG_STRU
�ṹ˵��  : en_NV_Item_WINS_Config(8297)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;        /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucWins;          /* WINSʹ�ܱ��: 0��Disable,  1��Enable */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}WINS_CONFIG_STRU;

/*en_NV_Item_CustomizeSimLockPlmnInfo 8267*/
/*****************************************************************************
�ṹ��    : TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU
�ṹ˵��  : en_NV_Item_CustomizeSimLockPlmnInfo(8267)�ṹǶ�׽ṹ#
            ���ڼ�¼SIM LOCKҪ���PLMN��Ϣ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMncNum;
    VOS_UINT8                           aucRangeBegin[TAF_PH_SIMLOCK_PLMN_STR_LEN];
    VOS_UINT8                           aucRangeEnd[TAF_PH_SIMLOCK_PLMN_STR_LEN];
}TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU;

/*****************************************************************************
�ṹ��    : TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU
�ṹ˵��  : en_NV_Item_CustomizeSimLockPlmnInfo(8267)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;/*�Ƿ񼤻0�����1���� */
    TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU astSimLockPlmnRange[TAF_MAX_SIM_LOCK_RANGE_NUM];
}TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU;

/* en_NV_Item_CardlockStatus 8268 */
/*****************************************************************************
�ṹ��    : TAF_NVIM_CUSTOM_CARDLOCK_STATUS_STRU
�ṹ˵��  : en_NV_Item_CardlockStatus(8268)�ṹ#
            ���ڱ���SIM LOCK��״̬�Լ�ʣ���������
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                          ulCardlockStatus;    /**/
    VOS_UINT32                          ulRemainUnlockTimes; /*����ʣ�����*/
}TAF_NVIM_CUSTOM_CARDLOCK_STATUS_STRU;

/*en_NV_Item_CustomizeSimLockMaxTimes 8269*/
/*****************************************************************************
�ṹ��    : TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU
�ṹ˵��  : en_NV_Item_CustomizeSimLockMaxTimes(8269)�ṹ#
            ���ڱ���SIM LOCKҪ�������������,Ĭ��Ϊδ���Ĭ������������Ϊ10��
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                          ulLockMaxTimes;
}TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU;

/*en_NV_Item_CCA_TelePara 8230*/
/*****************************************************************************
�ṹ��    : TAF_CCA_TELE_PARA_STRU
�ṹ˵��  : en_NV_Item_CCA_TelePara(8230)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
/*Ϊ����V1R1NV��ƥ��ǰ15���ֽڱ���*/
typedef struct
{
    VOS_UINT8               aucRsv[15];              /*NV��Ľṹ�У�4�ֽڶ��뷽ʽ���пն�Ҫ�ֶ�����*/
    VOS_UINT8               ucS0TimerLen;
} TAF_CCA_TELE_PARA_STRU;

/*en_NV_Item_PS_TelePara 8231*/
/*****************************************************************************
�ṹ��    : TAF_APS_NVIM_PS_ANS_MODE_STRU
�ṹ˵��  : en_NV_Item_PS_TelePara(8231)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8         AnsMode;
    VOS_UINT8         AnsType;
    VOS_UINT16        ClientId;
}TAF_APS_NVIM_PS_ANS_MODE_STRU;

/*en_NV_Item_User_Set_Freqbands 8265*/
/*��ȡbandֵ����MS��RACIEZ�л��*/
/*
  80��CM_BAND_PREF_GSM_DCS_1800��              GSM DCS systems
  100��CM_BAND_PREF_GSM_EGSM_900��             Extended GSM 900
  200��CM_BAND_PREF_GSM_PGSM_900��             Primary GSM 900
  100000��CM_BAND_PREF_GSM_RGSM_900��          GSM Railway GSM 900
  200000��CM_BAND_PREF_GSM_PCS_1900��          GSM PCS
  400000��CM_BAND_PREF_WCDMA_I_IMT_2000��      WCDMA IMT 2000
  3FFFFFFF��CM_BAND_PREF_ANY��                 �κ�Ƶ��
  40000000��CM_BAND_PREF_NO_CHANGE��           Ƶ�����仯
*/
/*****************************************************************************
�ṹ��    : TAF_MMA_NVIM_USER_SET_PREF_BAND64
�ṹ˵��  : en_NV_Item_User_Set_Freqbands(8265)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulBandLow; /*��32λ*/
    VOS_UINT32 ulBandHigh;/*��32λ*/
} TAF_MMA_NVIM_USER_SET_PREF_BAND64;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU
�ṹ˵��  : en_NV_Item_REPORT_REG_ACT_FLG(8340)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReportRegActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_REPORT_REG_ACT_FLG_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU
�ṹ˵��  : en_NV_Item_Me_Personalisation_Active_Flag(8255)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMePersonalActFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU;

/*****************************************************************************
�ṹ��    : TAF_CBA_CBS_SERVICE_PARM_STRU
�ṹ˵��  : en_NV_Item_CBS_Service_Para(8240)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCbStatus;         /* CBSҵ���Ƿ����ñ�־*/

    VOS_UINT8                           ucDupDetectCfg;     /* �ظ��������� */

    VOS_UINT8                           ucRptAppFullPageFlg; /* VOS_TRUE: �ϱ���ҳ��88���ֽ�; VOS_FALSE: �ϱ�ʵ����Ч�ֽ� */

    VOS_UINT8                           ucRsv;              /* NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն� */
}TAF_CBA_NVIM_CBS_SERVICE_PARM_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_COMMDEGBUG_CFG_STRU
�ṹ˵��  : en_NV_Item_COMMDEGBUG_CFG(27)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCommDebugFlag;
}TAF_AT_NVIM_COMMDEGBUG_CFG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU
�ṹ˵��  : en_NV_Item_DEFAULT_LINK_OF_UART(53)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    AT_UART_LINK_TYPE_ENUM_UINT16       enUartLinkType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_AUTOATTACH_STRU
�ṹ˵��  : en_NV_Item_FMRID(8203)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucMfrId[TAF_MAX_MFR_ID_STR_LEN];
}TAF_PH_FMR_ID_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_OPERATOR_NAME_STRU
�ṹ˵��  : en_NV_Item_MMA_OperatorName(8206)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucOperatorName[NAS_MMA_NVIM_OPERATOR_NAME_LEN];
}NAS_MMA_OPERATOR_NAME_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_FACTORY_INFO_STRU
�ṹ˵��  : en_NV_Item_AT_FACTORY_INFO(115)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucFactInfo1[AT_FACINFO_INFO1_STR_LENGTH];
    VOS_UINT8                           aucFactInfo2[AT_FACINFO_INFO2_STR_LENGTH];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NVIM_FACTORY_INFO_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_MANUFACTURE_DATE_STRU
�ṹ˵��  : en_NV_Item_AT_MANUFACTURE_DATE(116)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMDate[AT_MDATE_STRING_LENGTH];
}TAF_AT_NVIM_MANUFACTURE_DATE_STRU;

/*****************************************************************************
 �ṹ��    : APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_PCVOICE_Support_Flg�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPcVoiceSupportFlag; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU;



/*****************************************************************************
 �ṹ��    : MN_MSG_ME_STORAGE_PARM_STRU
 �ṹ˵��  : en_NV_Item_Sms_Me_Storage_Info NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMeStorageStatus;                      /* ME�洢���Ź����Ƿ����ñ�־*/
    VOS_UINT8                           aucReserve[1];                          /* NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն� */
    VOS_UINT16                          usMeStorageNum;                         /* ME�洢�������� */
}MN_MSG_ME_STORAGE_PARM_STRU;
/*****************************************************************************
 �ṹ��    : TAF_APS_DSFLOW_NV_STRU
 �ṹ˵��  : ������ʷ������Ϣ��NV�ṹ����
1.��    ��   : 2011��12��14��
  ��    ��   : ŷ���� 00132663
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulDSLastLinkTime;                       /*DS���һ������ʱ��*/
    VOS_UINT32      ulDSTotalSendFluxLow;                   /*DS�ۼƷ����������ĸ��ֽ�*/
    VOS_UINT32      ulDSTotalSendFluxHigh;                  /*DS�ۼƷ����������ĸ��ֽ�*/
    VOS_UINT32      ulDSTotalLinkTime;                      /*DS�ۼ�����ʱ��*/
    VOS_UINT32      ulDSTotalReceiveFluxLow;                /*DS�ۼƽ����������ĸ��ֽ�*/
    VOS_UINT32      ulDSTotalReceiveFluxHigh;               /*DS�ۼƽ����������ĸ��ֽ�*/

} TAF_APS_DSFLOW_NV_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : en_NV_Item_PREVENT_TEST_IMSI_REG�ṹ
  1.��    ��   : 2012��2��22��
    ��    ��   : w00199382
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_DISCARD_DELIVER_MSG_STRU;
/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : en_NV_Item_PREVENT_TEST_IMSI_REG�ṹ
  1.��    ��   : 2012��2��22��
    ��    ��   : w00199382
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_REPLACE_DELIVER_MSG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_APS_DSFLOW_STATS_CTRL_NV_STRU
 �ṹ˵��  : ����ͳ�ƿ���NV��ṹ����
1.��    ��   : 2011��12��21��
  ��    ��   : ŷ���� 00132663
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucDsFlowStatsRptCtrl;                   /* ��ʶ�Ƿ���������ϱ� */
    VOS_UINT8       ucDsFlowStatsSave2NvCtrl;               /* ��ʶ�Ƿ���Ҫ������ʷ������Ϣ��NV�� */
    VOS_UINT8       ucDsFlowSavePeriod;                     /* ����дNV������ */
    VOS_UINT8       aucReserve[1];                          /* ����λ*/
} TAF_APS_DSFLOW_STATS_CTRL_NV_STRU;

/*****************************************************************************
 �ṹ��    : TAF_PH_RAT_STRU
 �ṹ˵��  : AT^syscfgex�����õ�acqorder�еĳ��Ⱥ���ֵ
 1.��    �� : 2011��06��9��
   ��    �� : l00130025
   �޸����� : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* syscfgex�����õ�acqoder�е�ָʾ���� */
    VOS_UINT8                           aenRatOrder[TAF_PH_NVIM_MAX_GUL_RAT_NUM];    /* at^syscfgex�����õ�acqoder��˳�� */
}TAF_PH_NVIM_RAT_ORDER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_NVIM_MO_SMS_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : TAF_APS_NVIM_PDP_ACT_LIMIT_STRU
 �ṹ˵��  : AT&T���� PDP��������NV��
 1.��    ��   : 2012��6��14��
   ��    ��   : m00217266
   �޸�����   : �½�
 2.��    ��   : 2015��3��2��
   ��    ��   : w00316404
   �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_PDP_Actving_Limit NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserved1;                            /* ���� */
    VOS_UINT8                           ucReserved2;                            /* ���� */
    VOS_UINT8                           ucReserved3;                            /* ���� */
}TAF_APS_NVIM_PDP_ACT_LIMIT_STRU;
/*****************************************************************************
 �ṹ��    : MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU
 �ṹ˵��  : ��Ӫ�̶��ƽ���������NV�ṹ
 1.��    ��   : 2012��06��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&DCM��Ŀ�����ṹ

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategory;                             /* �������������� */
    VOS_UINT8                           ucValidSimPresent;                      /* �������������п�ʱ��Ч�����޿�ʱ��Ч��1�п�ʱ��Ч��0�޿�ʱ��Ч */
    VOS_UINT8                           ucAbnormalServiceFlg;                   /* �����������п�ʱ�Ƿ���ڷ���������ʱ��Ч��0:�κη���ʱ����Ч��1:������������ʱ��Ч */
    VOS_UINT8                           ucEccNumLen;
    VOS_UINT8                           aucEccNum[MN_CALL_NVIM_MAX_BCD_NUM_LEN];
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU;


/*****************************************************************************
 �ṹ��    : MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU
 �ṹ˵��  : en_NV_Item_CUSTOM_ECC_NUM_LIST�ṹ
 1.��    ��   : 2012��06��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&DCM��Ŀ�����ṹ

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccNumCount;
    VOS_UINT8                           aucReserve[3];
    MN_CALL_NVIM_CUSTOM_ECC_NUM_STRU    astCustomEccNumList[MN_CALL_NVIM_MAX_CUSTOM_ECC_NUM];
} MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU
 �ṹ˵��  : NV en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG �Ľṹ

  1.��    ��   : 2015��9��30��
    ��    ��   : c00318887
    �޸�����   : �½�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBufferCcProtectTimerLen;              /* 0: ��ѡ��ʱ�����л��棻����0: ����CC����ı�����ʱ��ʱ������λ �� */
    VOS_UINT8                           ucBufferSmsProtectTimerLen;             /* 0: ��ѡ��ʱ�����л��棻����0: ����SMS����ı�����ʱ��ʱ������λ �� */
    VOS_UINT8                           ucBufferSsProtectTimerLen;              /* 0: ��ѡ��ʱ�����л��棻����0: ����SS����ı�����ʱ��ʱ������λ �� */
    VOS_UINT8                           ucReserve1;
}TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU;



/*****************************************************************************
 �ṹ��    : MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSimCallCtrlSupportFlg;                /* SIM��Call Controlҵ��*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU;
/*****************************************************************************
 �ṹ��    : MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_CALL_DEFLECTION_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallDeflectionSupportFlg;             /* ֧�ֺ���ƫתҵ��*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_CALL_NVIM_CALL_DEFLECTION_SUPPORT_FLG_STRU;
/*****************************************************************************
 �ṹ��    : MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_ALS_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAlsSupportFlg;                        /* ֧����·�л�ҵ��*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_CALL_NVIM_ALS_SUPPORT_FLG_STRU;
/*****************************************************************************
 �ṹ��    : MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2014��9��9��
    ��    ��   : z00161729
    �޸�����   : DTS2014091200106:�й�����4G����0x6f42��������ĺ�����ڣ���indicationָʾbitΪ1����ʾû�У��ֻ����ε������޷���ȡ���������ģ������˶���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGetCsmpParaFromUsimSupportFlg;        /*��(U)SIM���ж�ȡCSMP����*/

    VOS_UINT8                           ucGetScAddrIgnoreScIndication; /* 0x6f42�ļ���sc indicationָʾ�����ڶ������ĺ���ʱ������������ĺ���Ϸ��Ƿ��ȡ��
                                                                       VOS_FALSE:sc indicationָʾ�������ĺ��벻�����򲻶�ȡ�������ĺ��룻
                                                                       VOS_TRUE: sc indicationָʾ�������ĺ��벻���ڶ�ȡ�������ĺ��� */
}MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU;
/*****************************************************************************
 �ṹ��    : MN_MSG_SMS_PP_DOWNLOAD_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsPpDownlodSupportFlg;               /*�����Ƿ�֧�ֶ��ŵ�PP-DOWNLOAD����*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_MSG_SMS_PP_DOWNLOAD_SUPPORT_FLG_STRU;
/*****************************************************************************
 �ṹ��    : MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_SMS_NVIM_SMSREXIST_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsNvSmsRexitSupportFlg;              /*����������ΪPS ONLYʱ���Ƿ�֧��CS����źͺ���ҵ��(�������г���) */
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsStatusInEfsmsSupportFlg;           /* ����NVIM���Ƿ��ܱ������״̬����*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU;



/*****************************************************************************
 �ṹ��    : MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU
 �ṹ˵��  : NVIM�б���GSM����codec�����Ľṹ
 1.��    ��   : 2012��2��09��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucCodecTypeNum;
    VOS_UINT8                           aucCodecType[MN_CALL_NVIM_BC_MAX_SPH_VER_NUM];
    VOS_UINT8                           ucReserve;
}MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU;


/*****************************************************************************
 �ṹ��    : TAF_FDN_CONFIG_STRU
 �ṹ˵��  : FDNҵ�����Բ����ṹ
             enMeStatus         ME�Ƿ�����FDNҵ����
1.��    ��   : 2012��02��23��
  ��    ��   : f62575
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32       ulMeStatus;
}TAF_FDN_NVIM_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU
�ṹ˵��  : �ն˲�֧��CALL���ظ�RELEASE COMPLETE��Ϣԭ��ֵ����ҵ�����Բ����ṹ
            ucVoiceCallNotSupportedCause   �ն˲�֧��VOICE CALL��RELEASE COMPLETE��Ϣԭ��ֵ
            ucVideoCallNotSupportedCause   �ն˲�֧��VIDEO CALL��RELEASE COMPLETE��Ϣԭ��ֵ
1.��    ��   : 2013��12��09��
    ��    ��   : f62575
    �޸�����   : DTS2013120411878���ն˲�֧��VOICE/VIDEO CALL���ظ�RELEASE COMPLETE
��Ϣԭ����
*****************************************************S************************/
typedef struct
{
    VOS_UINT8                           ucVoiceCallNotSupportedCause;
    VOS_UINT8                           ucVideoCallNotSupportedCause;
    VOS_UINT8                           aucReserved1[2];
}TAF_CALL_NVIM_CALL_NOT_SUPPORTED_CAUSE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU
 �ṹ˵��  : ��¼en_NV_Item_REPORT_PLMN_SUPPORT_FLAG NV�����ݣ�
             ��ʶ�Ƿ�ʹ���ϱ�PLMN

 �޸ļ�¼  :
 1.��    ��   : 2012��06��11��
   ��    ��   : W00166186
   �޸�����   : ����
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Network_Selection_Menu_Ctrl_Para NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserved;                             /* ���� */
}TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU;

	/*****************************************************************************
 �ṹ��    : TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU
 �ṹ˵��  : en_NV_Item_NotDisplayLocalNetworkName NV�е��û�������Ϣ�ṹ��
 1.��    ��   : 2012��11��1��
   ��    ��   : w00167002
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNotDisplayLocalNetworkNameFlg;
    VOS_UINT8                           ucReserved;
}TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU;

/*****************************************************************************
 �ṹ��    : MN_MSG_MT_CUSTOMIZE_INFO_STRU
 �ṹ˵��  : ���Ž��ն���NV��en_NV_Item_SMS_MT_CUSTOMIZE_INFO���ݽṹ
             ucActFlag      �����־
             enMtCustomize  ���Ž��ն�������
  1.��    ��   : 2012��11��10��
    ��    ��   : f62575
    �޸�����   : DCM&DEVICE

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlag;
    VOS_UINT8                           enMtCustomize;
    VOS_UINT8                           aucReserved1[2];
}MN_MSG_MT_CUSTOMIZE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_SIM_FORMAT_PLMN_ID
 �ṹ˵��  : Sim PLMN ID�Ĵ洢�ṹ

 1.��    ��   : 2016��4��6��
   ��    ��   : c00318887
   �޸�����   : DAM & SmartCard

*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[TAF_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}TAF_SIM_FORMAT_PLMN_ID;

/*****************************************************************************
 �ṹ��    : TAF_MN_OTA_MSG_PLMN_LIST_STRU
 �ṹ˵��  : DAM & SmartCard��Ŀ����NV�����ݽṹ

  1.��    ��   : 2016��4��6��
    ��    ��   : c00318887
    �޸�����   : DAM & SmartCard
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    TAF_SIM_FORMAT_PLMN_ID              astSimPlmnId[TAF_NVIM_OTA_SECURITY_MSG_IMSI_PLMN_MAX_NUM];
} TAF_MN_OTA_SECURITY_SMS_IMSI_PLMN_LIST;

/*****************************************************************************
 �ṹ��    : TAF_MN_NVIM_OTA_SECURITY_SMS_CFG_STRU
 �ṹ˵��  : DAM & SmartCard��Ŀ����NV��en_NV_Item_MN_OTA_MSG_SECURITY_REQUIREMENT_CFG���ݽṹ
             ucOtaMsgSequrityRequirementActFlg      OTA���Ű�ȫ���󼤻��־
  1.��    ��   : 2016��03��29��
    ��    ��   : wx270776
    �޸�����   : DAM & SmartCard

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucOtaSmsActiveFlg;
    VOS_UINT8                                               ucReserve1;
    VOS_UINT8                                               ucReserve2;
    VOS_UINT8                                               ucReserve3;
    TAF_MN_OTA_SECURITY_SMS_IMSI_PLMN_LIST                  stImsiPlmnList;  /* IMSI��MCC-MNC���б�  */
}TAF_MN_NVIM_OTA_SECURITY_SMS_CFG_STRU;


/*****************************************************************************
 �ṹ��    : MN_CALL_UMTS_CODEC_TYPE_STRU
 �ṹ˵��  : MN_CALL_UMTS_CODEC_TYPE_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8  ucCnt;
    VOS_UINT8  aucUmtsCodec[MN_CALL_MAX_UMTS_CODEC_TYPE_NUM];
} MN_CALL_UMTS_CODEC_TYPE_STRU;
/*****************************************************************************
 �ṹ��    : MMA_CUSTOM_CARDLOCK_PERM_STRU
 �ṹ˵��  : MMA_CUSTOM_CARDLOCK_PERM_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;/*�Ƿ񼤻0�����1���� */
    VOS_UINT8                           ucCardLockPerm;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}MMA_CUSTOM_CARDLOCK_PERM_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU
 �ṹ˵��  : ETWS��MSG ID��Χ�Ľṹ
 1.��    ��   : 2012��3��08��
   ��    ��   : l00171473
   �޸�����   : �½� for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /*Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /*Cell broadcast message id value range to    */
}TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU;
/*****************************************************************************
 �ṹ��    : TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU
 �ṹ˵��  : NVIM��ETWS���������Ľṹ
 1.��    ��   : 2012��3��08��
   ��    ��   : l00171473
   �޸�����   : �½� for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEnhDupDetcFlg;    /* DoCoMo��ǿ���ظ���ⶨ�����ԣ���ETWS����֪ͨ����ǿ���ظ���������Ƿ񼤻�, VOS_TRUE:����,VOS_FALSE:δ����.
                                                                                        1. ����֪ͨ,������ͨCBS��Ϣ, �ظ����ʱ��Ҫ�ж�PLMN
                                                                                        2. ����֪ͨ,������ͨCBS��Ϣ, �ظ�����ʱ������ݵ�ǰPLMN��MCC��������
                                                                                        3. ETWS��Ϣ����ͨCBS��Ϣ����ͬ�Ĺ������ظ����˺�ʱЧ��� */
    VOS_UINT8                                               ucRsv;

    VOS_UINT16                                              usNormalTimeLen;   /* ��λ:����, ��������δ����ʱʹ�ô���Чʱ�� */

    VOS_UINT16                                              usSpecMccTimeLen;  /* ��λ:����, ��ǿ���ظ���ⶨ�����Լ���ʱ��/��֪ͨ/CBS��MCC��ָ��Mcc����ʹ�ô���Чʱ�� */
    VOS_UINT16                                              usOtherMccTimeLen; /* ��λ:����, ��ǿ���ظ���ⶨ�����Լ���ʱ��/��֪ͨ/CBS��MCC����ָ��Mcc����ʹ�ô���Чʱ�� */
    VOS_UINT32                                              aulSpecMcc[TAF_CBA_NVIM_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM];  /* ��ǿ���ظ���ⶨ��������ص�MCC */
}TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_ECC_NUM_REPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReportEccNumFlg;                      /* 1:֧����APP�ϱ�����������, 0:��֧����APP�ϱ�����������*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}MN_CALL_NVIM_REPORT_ECC_NUM_SUPPORT_FLG_STRU;


/*****************************************************************************
 �ṹ��    : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU
 �ṹ˵��  : MMA_CUSTOM_CARDLOCK_OPERATOR_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;/*�Ƿ񼤻0�����1���� */
    MN_CALL_STATE_ENUM_UINT8            enCardLockOperator;
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
}MMA_CUSTOM_CARDLOCK_OPERATOR_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_NV_ITEM_VIDEO_CALL_STRU
 �ṹ˵��  : MN_CALL_NV_ITEM_VIDEO_CALL_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucVpCfgState;                           /* ��ǰNV����ֵ */
}MN_CALL_NV_ITEM_VIDEO_CALL_STRU;

/*****************************************************************************
 �ṹ��    : MN_MSG_NVIM_CLASS0_TAILOR_STRU
 �ṹ˵��  : MN_MSG_NVIM_CLASS0_TAILOR_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;                               /* NVIM�и����Ƿ񼤻� */
    VOS_UINT8                           enClass0Tailor;
}MN_MSG_NVIM_CLASS0_TAILOR_STRU;
/* �ն˿���������: 2G���������ֹSpare_bit3�Ȳ��� */
typedef struct
{
    VOS_UINT8                           ucStatus;       /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucDisable2GBit3;
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
}APS_2G_DISABLE_BIT3_CUSTOMIZE_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU
 �ṹ˵��  : MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMultiSimCallConf;                             /*oΪ��������ʱ�ϱ���1��������ʱ���ϱ�*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
}MN_CALL_NV_ITEM_MULTISIM_CALLCON_STRU;


/*****************************************************************************
 �ṹ��    : TAF_USSD_NVIM_TRANS_MODE_STRU
 �ṹ˵��  : TAF_USSD_NVIM_TRANS_MODE_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;        /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucUssdTransMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_USSD_NVIM_TRANS_MODE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU
 �ṹ˵��  : ��¼�����ؽ�������Ϣ
 1. ��    ��   : 2015��8��29��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialCmSrvRejCauseNum;                                   /* �ز�ԭ��ֵ���� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucCallRedialCmSrvRejCause[TAF_NVIM_CALL_REDIAL_CAUSE_MAX_NUM]; /* �ز�ԭ��ֵ */
}TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CALL_REDIAL_DISC_CFG_STRU
 �ṹ˵��  : ��¼����DISCONNECTԭ��ֵ�ĺ����ؽ�������Ϣ
 1. ��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialForDiscSupportFlg;                            /* ����disconnect ԭ��ֵ�����Ի��ƵĿ���VOS_TRUE:�򿪣�VOS_FALSE:�ر�*/
    VOS_UINT8                           ucCallRedialDiscCauseNum;                                   /* �ز�ԭ��ֵ���� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           aucCallRedialDiscCause[TAF_NVIM_CALL_RETRY_DISC_CAUSE_MAX_NUM]; /* �ز�ԭ��ֵ */
}TAF_CALL_REDIAL_DISC_CFG_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_REDIAL_CFG_STRU
 �ṹ˵��  : ��¼�����ؽ�������Ϣ
 1.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��04��28��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialSupportFlg;     /* ֧�ֺ����ؽ����ܱ�־��VOS_TRUE:֧�֣�VOS_FALSE:��֧��*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulCallRedialPeriod;         /* �����ؽ����Դ�ʱ�������ؽ����ʱ������λ���� */
    VOS_UINT32                          ulCallRedialInterval;       /* �����ؽ����Դ�ʱ�������ز������λ���� */
}MN_CALL_REDIAL_CFG_STRU;

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
/*****************************************************************************
 �ṹ��    : TAF_CALL_NVIM_ECALL_CFG_STRU
 �ṹ˵��  : eCall������Ϣ, ����eCall�ز���ʱ����T9��ʱ��ʱ��
 1.��    ��   : 2014��04��15��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEcallT9Len;                /* T9ʱ����ʱ��ʱ������λΪСʱ��1~12Сʱ */
    VOS_UINT8                           ucEcallRedialSupportFlg;   /* ֧��eCall�ؽ����ܱ�־��VOS_TRUE:֧�֣�VOS_FALSE:��֧��*/
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT16                          usEcallRedialPeriod;         /* eCall�ؽ����Դ�ʱ��eCall�ؽ����ʱ������λ���� */
    VOS_UINT16                          usEcallRedialInterval;       /* eCall�ؽ����Դ�ʱ��eCall�ز������λ���� */
}TAF_CALL_NVIM_ECALL_CFG_STRU;
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-15, end */


/*****************************************************************************
 �ṹ��    : APP_VC_NV_CLVL_VOLUME_STRU
 �ṹ˵��  : en_NV_Item_Clvl_Volume�Ľṹ

  1.��    ��   : 2012��05��08��
    ��    ��   : l60609
    �޸�����   : ����en_NV_Item_Clvl_Volume�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sHandSetVolValue;
    VOS_INT16                           sHandsFreeVolValue;
    VOS_INT16                           sCarFreeVolValue;
    VOS_INT16                           sEarphoneVolValue;
    VOS_INT16                           sBlueToothVolValue;
    VOS_INT16                           sPcVoiceVolValue;
    VOS_INT16                           sHeadPhoneVolValue;
    VOS_INT16                           sSuperFreeVolValue;
    VOS_INT16                           sSmartTalkVolValue;
    VOS_INT16                           sPreVolume;
    VOS_UINT16                          usCurrDevMode;
    VOS_UINT16                          usPreDevMode;
    VOS_UINT16                          usSetVoiceFlg;                          /*����DEV��Vol�Ĺ�����flag��ȷ����modemֻ��һ�������ù�����*/
    VOS_INT16                           sRsv[3];
} APP_VC_NV_CLVL_VOLUME_STRU;

/* �ն˿���������: ����Ĭ��APN���� */
typedef struct
{
    VOS_UINT8   ucStatus;       /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8   aucApn[TAF_NVIM_MAX_APN_STR_LEN];       /* APN�Ӹ�����ĵ�һ���ֽڿ�ʼд�룬������'\0'��Ϊ��β */
    VOS_UINT8   aucRsv[3];
}APS_APN_CUSTOMIZE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CBA_NVIM_ETWS_CFG_STRU
 �ṹ˵��  : NVIM��ETWS���������Ľṹ
 1.��    ��   : 2012��3��08��
   ��    ��   : l00171473
   �޸�����   : �½� for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEtwsEnableFlg;    /* ETWS���Կ���, VOS_TRUE:����, VOS_FALSE:δ���� */
    VOS_UINT8                                               ucRsv;
    VOS_UINT16                                              usTempEnableCbsTimeLen; /* ��λ:����, CBS����δ����ʱ,�յ���֪ͨ����ʱʹ��CBS�Խ��մ�֪ͨ��ʱ�� */

    TAF_CBA_NVIM_ETWS_DUP_DETC_CFG_STRU                     stDupDetcCfg;       /* TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM Duplication Detection Time ������ */
    TAF_CBA_NVIM_ETWS_MSGID_RANGE_STRU                      astSpecEtwsMsgIdList[TAF_CBA_NV_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM];   /* �û����Ƶ�ETWS��ϢID��Χ */
}TAF_CBA_NVIM_ETWS_CFG_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_ALS_LINE_INFO_STRU
 �ṹ˵��  : en_NV_Item_ALS_LINE_Config(8450) NVIM�ṹ
 1.��    ��   : 2012��3��08��
   ��    ��   : l00171473
   �޸�����   : �½� for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enAlsLine;
    VOS_UINT8                           aucMmaImsi[9];
}MN_CALL_ALS_LINE_INFO_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NVIM_AT_CLIENT_CONFIG_STRU
�ṹ˵��  : en_NV_Item_AT_CLIENT_CONFIG 9202
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucAtClientConfig[TAF_AT_NVIM_CLIENT_CONFIG_LEN];
}TAF_AT_NVIM_AT_CLIENT_CONFIG_STRU;

/*******************************************************************************
 �ṹ��    : TAF_TEMP_PROTECT_CONFIG_STRU
 �ṹ˵��  : �¶ȱ���ʹ��NV��ṹ��(9212)
 1.��    ��   : 2013��04��17��
   ��    ��   : z00214637
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucECallNotifySupport;                   /* �����������¶ȱ�������NV�� */
    VOS_UINT8                           ucSpyStatusIndSupport;                  /* �±�״̬�ϱ�ʹ��NV�� */
    VOS_UINT8                           aucReserved[2];                          /* ������ */
}TAF_TEMP_PROTECT_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_ATT_ENS_CTRL_STRU
 �ṹ˵��  : ��¼en_NV_Item_ATT_Ctrl_Para(9081) NV������

 �޸ļ�¼  :
 1.��    ��   : 2012��06��12��
   ��    ��   : l60609
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNetSelMenuFlg;                        /* ����ѡ��˵����ƣ�VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucRatBalancingFlg;                      /* ���뼼��ƽ����ƣ�VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NVIM_ATT_ENS_CTRL_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_USER_SET_LTEBANDS_STRU
�ṹ˵��  : en_NV_Item_USER_SET_LTEBANDS 9017
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulUserSetLtebands[2];
}TAF_NVIM_USER_SET_LTEBANDS_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_RABM_TOTAL_RX_BYTES_STRU
�ṹ˵��  : en_NV_Item_RABM_TOTAL_RX_BYTES 8491(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDSTotalSendFluxLow;
    VOS_UINT32                          ulDSTotalSendFluxHigh;
    VOS_UINT32                          ulDSTotalReceiveFluxLow;
    VOS_UINT32                          ulDSTotalReceiveFluxHig;
}TAF_NVIM_RABM_TOTAL_RX_BYTES_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_E5_ROAM_WHITE_LIST_SUPPORT_FLG_STRU
�ṹ˵��  : en_NV_Item_E5_RoamingWhiteList_Support_Flg 8504(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRoamWhiteListFlag[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_NVIM_E5_ROAM_WHITE_LIST_SUPPORT_FLG_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_NDIS_DIALUP_ADDRESS_STRU
�ṹ˵��  : en_NV_Item_NDIS_DIALUP_ADDRESS 9010(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulNdisDialUpAdd;
}TAF_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*nv 9130, Ϊipv6��Ŀ����nvԤ��*/
/*****************************************************************************
 �ṹ��  : TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU
 �ṹ˵��: ��������IPv4v6˫ջ���Ż������̵���չԭ��ֵ(SM Cause)�ṹ��

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT8                           aucSmCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];

} TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU;

/*****************************************************************************
�ṹ��    : TAF_NDIS_NV_IPV6_ROUTER_MTU_STRU
�ṹ˵��  : en_NV_Item_IPV6_ROUTER_MTU 8513(��nv�����ڱ���,�ýṹ����û��ʹ��)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpv6RouterMtu;
}TAF_NDIS_NV_IPV6_ROUTER_MTU_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_DISLOG_PWD_STRU
�ṹ˵��  : en_NV_Item_AT_DISLOG_PWD 32(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_INT32                           lValue;
    VOS_INT8                            acPassword[16];
}TAF_AT_NV_DISLOG_PWD_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_E5_RIGHT_FLAG_STRU
�ṹ˵��  : en_NV_Item_AT_E5_RIGHT_FLAG 34(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulE5RightFlag;
}TAF_AT_NV_E5_RIGHT_FLAG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_DISSD_FLAG_STRU
�ṹ˵��  : en_NV_Item_AT_DISSD_FLAG 42(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDissdFlag;
}TAF_AT_NV_DISSD_FLAG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_OM_PORT_NUM_STRU
�ṹ˵��  : en_NV_Item_OM_Port_Num 2049(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulOmPortNum;
}TAF_AT_NV_OM_PORT_NUM_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_RA_CAPABILITY_STRU
�ṹ˵��  : en_NV_Item_RaCapability 8198(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucData[53];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_RA_CAPABILITY_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_UMTS_AUTH_STRU
�ṹ˵��  : en_NV_Item_UMTS_Auth 8199(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUmtsAuth[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_UMTS_AUTH_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_GMM_INFO_STRU
�ṹ˵��  : en_NV_Item_GmmInfo 8200(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGmmInfo[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_GMM_INFO_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_MM_INFO_STRU
�ṹ˵��  : en_NV_Item_MMInfo 8201(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMmInfo[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_MM_INFO_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_SMS_TEXT_STRU
�ṹ˵��  : en_NV_Item_SMS_TEXT_Para 8236(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSmsText[16];
}TAF_AT_NV_SMS_TEXT_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_CUSTOM_GPRS_RECENT_ACT_TIMER_STRU
�ṹ˵��  : en_NV_Item_CustomizeGprsRecentActivityTimer 8270(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;
    VOS_UINT32                          ulGprsRecentActTime;
}TAF_AT_NV_CUSTOM_GPRS_RECENT_ACT_TIMER_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_PS_DELAY_FLAG_STRU
�ṹ˵��  : en_NV_Item_Ps_Delay_Flag 8272(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPsDelayFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_PS_DELAY_FLAG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_EHPLMN_SUPPORT_FLAG_STRU
�ṹ˵��  : en_NV_Item_EHPlmn_Support_Flag 8300(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucEhplmnSupportFlag[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_EHPLMN_SUPPORT_FLAG_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_BG_FS_FBS_RATIO_STRU
�ṹ˵��  : en_NV_Item_BG_FS_FBS_Ratio 8315(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucBgFsFbsRatio[4];
}TAF_AT_NV_BG_FS_FBS_RATIO_STRU;

/*****************************************************************************
�ṹ��    : TAF_AT_NV_EPLMN_USE_RAT_FLAG_STRU
�ṹ˵��  : en_NV_Item_Eplmn_Use_Rat_Flag 8342(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2015��3��2��
  ��    ��   : w00316404
  �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEplmnUseRatFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}TAF_AT_NV_EPLMN_USE_RAT_FLAG_STRU;
/*****************************************************************************
 �ṹ��    : TAF_CBA_CBMI_RANGE_STRU
 �ṹ˵��  : С���㲥��Ϣ�ķ�Χ��Ϣ
 1.��    ��   : 2012��03��17��
   ��    ��   : z40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLabel[TAF_NVIM_CBA_MAX_LABEL_NUM]; /* С���㲥��Ϣid��Χ��ǩ */
    VOS_UINT16                                              usMsgIdFrom;                    /* С���㲥��ϢID�Ŀ�ʼ���  */
    VOS_UINT16                                              usMsgIdTo;                      /* С���㲥��ϢID�Ľ������ */
    VOS_UINT32                                              ulRcvMode;                      /* ÿ��CBMI RANGE �Ľ���ģʽ, Ŀǰ��֧�� ACCEPT��ģʽ */
}TAF_CBA_NVIM_CBMI_RANGE_STRU;
/*****************************************************************************
 �ṹ��    : TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU
 �ṹ˵��  : С���㲥��ϢID�ķ�Χ�б���Ϣ
 1.��    ��   : 2012��03��28��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCbmirNum;                             /* С���㲥��Ϣ��ID���� */
    TAF_CBA_NVIM_CBMI_RANGE_STRU        astCbmiRangeInfo[TAF_CBA_NVIM_MAX_CBMID_RANGE_NUM]; /* С���㲥��Ϣ�ķ�Χ��Ϣ */
}TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU;


/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlatform;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_PLATFORM_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU
 �ṹ˵��  : TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_AT_NVIM_MUX_SUPPORT_FLG_STRU;

/*����USSDת���ַ���*/
typedef struct
{
    VOS_UINT8                           ucStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                           ucAlphaTransMode;    /* �ַ���ת��*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}SSA_NV_ITEM_ALPHA_to_ASCII_STRU;

/*****************************************************************************
�ṹ��    : TAF_CBA_CBS_SERVICE_PARM_STRU
�ṹ˵��  : NV��CBS�Ƿ����õĽṹ
1.��    ��   : 2012��3��23��
  ��    ��   : t00212959
  �޸�����   : �½� for V7R1C50 CSFB&PPAC&ETWS&ISR
2.��    ��   : 2012��12��04��
  ��    ��   : l00171473
  �޸�����   : for DTS2012120600056, NV������ظ����˿���
3.��    ��   : 2012��12��10��
  ��    ��   : l00171473
  �޸�����   : for DTS2012120609682,�ն�Ҫ��CBSͳһ�ϱ�88���ֽ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCbStatus;         /* CBSҵ���Ƿ����ñ�־*/

    VOS_UINT8                           ucDupDetectCfg;     /* �ظ��������� */


    VOS_UINT8                           ucRptAppFullPageFlg; /* VOS_TRUE: �ϱ���ҳ��88���ֽ�; VOS_FALSE: �ϱ�ʵ����Ч�ֽ� */

    VOS_UINT8                           ucRsv;              /* NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն� */
}TAF_CBA_CBS_SERVICE_PARM_STRU;

/*******************************************************************************
 �ṹ��    : MTA_BODY_SAR_W_PARA_STRU
 �ṹ˵��  : Body SAR W �����ṹ��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_WCDMA_BAND_ENUM_UINT16          enBand;                     /* WCDMAƵ�� */
    VOS_INT16                           sPower;                     /* ��������ֵ */
}MTA_BODY_SAR_W_PARA_STRU;

/*******************************************************************************
 �ṹ��    : MTA_BODY_SAR_G_PARA_STRU
 �ṹ˵��  : Body SAR G �����ṹ��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sGPRSPower;                 /* GPRS��������ֵ */
    VOS_INT16                           sEDGEPower;                 /* EDGE��������ֵ */
}MTA_BODY_SAR_G_PARA_STRU;

/*******************************************************************************
 �ṹ��    : MTA_BODY_SAR_PARA_STRU
 �ṹ˵��  : Body SAR�������޲����ṹ��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGBandMask;                                /* GSM Band��Maskλ */
    VOS_UINT16                          usWBandNum;                                 /* WCDMA��Band���� */
    VOS_UINT16                          ausReserved1[1];                            /* ����λ */
    MTA_BODY_SAR_G_PARA_STRU            astGBandPara[MTA_BODY_SAR_GBAND_MAX_NUM];   /* GSM��������ֵ */
    MTA_BODY_SAR_W_PARA_STRU            astWBandPara[MTA_BODY_SAR_WBAND_MAX_NUM];   /* WCDMA��������ֵ */
}MTA_BODY_SAR_PARA_STRU;

typedef struct
{
    VOS_UINT32  ulNvStatus;
    VOS_UINT8   aucFirstPortStyle[17];   /* �豸�л�ǰ�˿���̬ */
    VOS_UINT8   aucRewindPortStyle[17];  /* �豸�л���˿���̬ */
    VOS_UINT8   aucReserved[22];         /* ���� */
}AT_DYNAMIC_PID_TYPE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_SHARE_PDP_INFO_STRU
 �ṹ˵��  : Share-PDP���Կ���NV
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;       /* �Ƿ�ʹ��Share PDP����, 0 - ��ֹ;  1 - ʹ�� */
    VOS_UINT8                           ucReserved;         /* ���� */
    VOS_UINT16                          usAgingTimeLen;     /* �ϻ�ʱ�䣬��λΪ�� */

} TAF_NVIM_SHARE_PDP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU
 �ṹ˵��  : AT+CFUN=0������ػ���ȥ����(U)SIM�����ܵ�NV�ṹ��
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;  /* AT+CFUN=0��ػ���ȥ����(U)SIM������ʹ�ܱ�ʶ, 0 - ��ֹ, 1 - ʹ��*/
    VOS_UINT8                           aucReserved[3];
} TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU;

/* ���Ƶ�MSCC module */

/*******************************************************************************
 �ṹ��    : TAF_NV_SCI_CFG_STRU
 �ṹ˵��  :
  1.��    ��   : 2013��7��4��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��6��16��
    ��    ��   : l00198894
    �޸�����   : TSTS
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitCardNum      : 3;
    VOS_UINT32                          bitReserved0    : 5;
    VOS_UINT32                          bitCard0        : 3;
    VOS_UINT32                          bitCard1        : 3;
    VOS_UINT32                          bitCard2        : 3;
    VOS_UINT32                          bitReserved1    : 15;
} TAF_NV_SCI_CFG_STRU;

/*******************************************************************************
 �ṹ��    : TAF_NVIM_SMS_CLOSE_PATH_CFG_STRU
 �ṹ˵��  :
  1.��    ��   : 2013��7��17��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimValid;
    VOS_UINT8                           ucSmsClosePathFlg;
} TAF_NVIM_SMS_CLOSE_PATH_CFG_STRU;


/* Added by j00174725 for V9R1 ���ſ���, 2013/08/12, begin */
/*******************************************************************************
 �ṹ��    : MTC_NV_RF_INTRUSION_CFG_STRU
 �ṹ˵��  : MTCģ����ſ������NV��
  1.��    ��   : 2013��08��13��
    ��    ��   : ���±�/j00174725
    �޸�����   : ������
*******************************************************************************/
typedef struct
{
    /* λ���� :0�����1:����
    bit0�����ƶ�˫����B39/B3���ų�ͻ����
    bit1��Notch Bypass���Կ���
    bit2: NarrowBand Dcs ����(V9 not support)
    bit3: B39/B3 ���ų�ͻ����2(G��Ƶ����ģʽ)
    bit4: RES ʹ�ܿ��أ�1��ʾ֧��RSE���ԣ�0��ʾ��֧��RSE����
    */
    VOS_UINT8                          ucSolutionMask;
    VOS_UINT8                          aucAdditonCfg[3];
} MTC_NV_RF_INTRUSION_CFG_STRU;
/* Added by j00174725 for V9R1 ���ſ���, 2013/08/12, end */

/**************************************************************
 �ṹ��    : TAF_NVIM_VSIM_CFG_STRU
 �ṹ˵��  : ME�����⿨���Ʋ���
             ucVsimCtrlFlg   NAS���⿨���̿��Ʊ�־:
             1: �������VSIM״̬��MODEM��ֹ�������ܣ�
                  OTA������ŵĽ��չ��ܣ�
                  ���緢���CS��ҵ���ܣ�
             0: ȥ����
             aucReserved1 ����1BYTE��֤NV��Ҫ��16BIT����
  1.��    ��   : 2013��8��29��
    ��    ��   : f62575
    �޸�����   : VSIM FEATURE
  2.��    ��   : 2015��3��2��
    ��    ��   : w00316404
    �޸�����   : ���ֽڶ��룬����reserveλ
**************************************************************/
typedef struct
{
    VOS_UINT8                           ucVsimCtrlFlg;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT8                           aucReserved3;
} TAF_NVIM_VSIM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_SSA_NVIM_RETRY_CFG_STRU
 �ṹ˵��  : ��¼ss�ط�������Ϣ
 1.��    ��   : 2013��9��10��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsSsRetrySupportFlg;                  /* �Ƿ�֧��ss�ط����ܣ�VOS_TRUE:֧�֣�VOS_FALSE:��֧��*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulSsRetryPeriod;                        /* ss�ط����Դ�ʱ��ss�ط����ʱ������λ��,Ĭ��30s */
    VOS_UINT32                          ulSsRetryInterval;                      /* ss�ط����Դ�ʱ��ss�ط������λ�룬Ĭ��5s */
}TAF_SSA_NVIM_RETRY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_SSA_NVIM_RETRY_CFG_STRU
 �ṹ˵��  : ��¼ss�ط�������Ϣ
 1.��    ��   : 2015��8��24��
   ��    ��   : n00355355
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSsRetryCmSrvRejCauseNum;                                      /* ss�ط�ԭ��ֵ����*/
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucSsRetryCmSrvRejCause[TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM];       /* ss�ط�ԭ�� */
}TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU;


/*****************************************************************************
 �ṹ��    : TAF_NV_UART_RI_CFG_STRU
 �ṹ˵��  : UART RI�źŲ��νṹ

  1.��    ��   : 2013��09��18��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSmsRiOnInterval;      /* ����RI�ߵ�ƽ����ʱ��(ms) */
    VOS_UINT32                          ulSmsRiOffInterval;     /* ����RI�͵�ƽ����ʱ��(ms) */

    VOS_UINT32                          ulVoiceRiOnInterval;    /* ����RI�ߵ�ƽ����ʱ��(ms) */
    VOS_UINT32                          ulVoiceRiOffInterval;   /* ����RI�͵�ƽ����ʱ��(ms) */
    VOS_UINT8                           ucVoiceRiCycleTimes;    /* ����RI�������ڴ���     */
    VOS_UINT8                           aucReserved[3];

} TAF_NV_UART_RI_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_UART_FRAME_STRU
 �ṹ˵��  : UART ֡�ṹ

  1.��    ��   : 2013��09��18��
    ��    ��   : j00174725
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFormat;               /* UART ����λֹͣλλ�� */
    VOS_UINT8                           ucParity;               /* UARTУ�鷽ʽ */
    VOS_UINT8                           aucReserved[2];

} TAF_NV_UART_FRAME_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_UART_CFG_STRU
 �ṹ˵��  : UART �������

  1.��    ��   : 2013��09��18��
    ��    ��   : j00174725
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBaudRate;             /* UART������ */
    TAF_NV_UART_FRAME_STRU              stFrame;                /* UART֡��ʽ */
    TAF_NV_UART_RI_STRU                 stRiConfig;             /* UART Ring������ */

} TAF_NV_UART_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_DFS_RATE_BAND_STRU
 �ṹ˵��  : ���ٵ�λ��DDRƵ�ʵĶ�Ӧ��ϵ

  1.��    ��   : 2013��12��13��
    ��    ��   : f00179208
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDlRate;
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDdrBand;
} TAF_NV_DFS_RATE_BAND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU
 �ṹ˵��  : APS����DDR��Ƶ�ĵ�λֵ

  1.��    ��   : 2013��12��13��
    ��    ��   : f00179208
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProfileNum;
    TAF_NV_DFS_RATE_BAND_STRU           astProfile[TAF_NVIM_DFS_MAX_PROFILE_NUM];
} TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU;
/*****************************************************************************
 �ṹ��    : TAF_NV_DIFF_RAT_DFS_DSFLOW_RATE_CONFIG_STRU
 �ṹ˵��  : ��ͬ���뼼��ģʽ��APS����DDR��Ƶ�ĵ�λֵ

  1.��    ��   : 2014��05��26��
    ��    ��   : m00217266
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU          astDfsConfig[TAF_NVIM_DIFF_DFS_NUM];
} TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_VOICE_TEST_FLAG_STRU
 �ṹ˵��  :

  1.��    ��   : 2013��12��23��
    ��    ��   : m00217266
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFlagValue;
    VOS_UINT32                          ulReserved;
} TAF_NV_VOICE_TEST_FLAG_STRU;

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
/*******************************************************************************
 �ṹ��    : TAF_NVIM_SMS_DOMAIN_STRU
 �ṹ˵��  :
  1.��    ��   : 2013��11��05��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*******************************************************************************/
typedef struct
{
    VOS_UINT8                          ucSmsDomain;
    VOS_UINT8                          aucReserved[3];
} TAF_NVIM_SMS_DOMAIN_STRU;

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

/*****************************************************************************
 �ṹ��    : TAF_NV_PORT_BUFF_CFG_STRU
 �ṹ˵��  : �������

  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           aucReserved[3];
} TAF_NV_PORT_BUFF_CFG_STRU;


/* Added by s00246516 for L-C��������Ŀ, 2014-01-23, Begin */
/*****************************************************************************
 �ṹ��    : TAF_NV_LC_CTRL_PARA_STRU
 Э����  : ��
 �ṹ˵��  : ���ڼ�¼L+C��SIM�������Ƿ���ʹ��״̬

 �޸���ʷ      :
  1.��    ��   : 2014��01��23��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ����NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     ucLCEnableFlg;
    TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8           enRatCombined;
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8               enLCWorkCfg;
    VOS_UINT8                                     aucReserved[1];
}TAF_NV_LC_CTRL_PARA_STRU;
/* Added by s00246516 for L-C��������Ŀ, 2014-01-23, End */

/*****************************************************************************
 �ṹ��    : TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 ucImsRedialCauseNum;                                                  /* IMS call�ز�ԭ��ֵ���� */
    VOS_UINT8                 ucImsaRedialCauseNum;                                                 /* IMSA call�ز�ԭ��ֵ���� */
    VOS_UINT8                 aucReserve[2];
    VOS_UINT16                ausImsRedialCause[TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM];
    VOS_UINT16                ausImsaRedialCause[TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM];
}TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* call�ز�flag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS �ز�flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  �ز�flag */
    VOS_UINT8                                               aucReserve[1];
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU        stCallRedialCauseCfg;
}TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU
 �ṹ˵��  :
 1.��    ��   : 2013��12��24��
   ��    ��   : y00245242
   �޸�����   : ����IMS��CS֮��Ļ����ز�����
 2.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                              ucCallRedial;
    VOS_UINT8                                              ucSmsRedial;
    VOS_UINT8                                              ucSsRedial;
    VOS_UINT8                                              aucReserve[1];
}TAF_NV_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_SWITCH_DOMAIN_REDIAL_CONFIG_STRU
 �ṹ˵��  :
 1.��    ��   : 2013��12��24��
   ��    ��   : y00245242
   �޸�����   : ����IMS��CS֮��Ļ����ز�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedial;
    VOS_UINT8                           ucSmsRedial;
    VOS_UINT8                           ucSsRedial;
    VOS_UINT8                           aucReserve[1];
}TAF_NV_SWITCH_DOMAIN_REDIAL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_IMS_ROAMING_SUPPORT_STRU
 �ṹ˵��  :
 1.��    ��   : 2013��12��24��
   ��    ��   : y00245242
   �޸�����   : ����IMS���ο��Ʊ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsRoamingFlg;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_IMS_ROAMING_SUPPORT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_IMS_USSD_SUPPORT_STRU
 �ṹ˵��  :
 3.��    ��   : 2014��04��01��
   ��    ��   : y00245242
   �޸�����   : ΪDTS2014040203732�޸ģ�����NV����USSDҵ����ѡ��USSDҵ��NV�򿪣�
                ����������ѡ�񣬷���ѡ��CS��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUssdOnImsSupportFlag;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_IMS_USSD_SUPPORT_STRU;

/*******************************************************************************
 �ṹ��    : MTC_NV_PS_TRANSFER_CFG_STRU
 �ṹ˵��  : MTCģ��PS��Ǩ�����NV��
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*******************************************************************************/
typedef struct
{
    MTC_PS_TRANSFER_ENUM_UINT8         enSolutionCfg;
    VOS_UINT8                          aucAdditonCfg[3];
} MTC_NV_PS_TRANSFER_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 �ṹ˵��  : Ϊ��ȡFLASH �ļ��洢·��������Ʒ��̬NV��
 1.��    ��   : 2014��03��04��
   ��    ��   : f62575
   �޸�����   : DTS2013091009786 ֧��ͨ����Ʒ��̬�Ͱ汾����FLASH�ļ���Ŀ¼
*****************************************************************************/
typedef struct
{
    TAF_FLASH_DIRECTORY_TYPE_ENUM_UINT16                     enFlashDirectoryType;
    VOS_UINT8                                                aucReserved1[2];
}TAF_NV_FLASH_DIRECTORY_TYPE_STRU;

/*******************************************************************************
 �ṹ��    : MTC_RF_LCD_TIMER_INTERVAL_STRU
 �ṹ˵��  : ��¼MIPICLK�ϱ���ʱ����
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerInterval;                        /* ʱ����ֵ,��λ�� */
}MTC_RF_LCD_TIMER_INTERVAL_STRU;

/*******************************************************************************
 �ṹ��    : MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU
 �ṹ˵��  : ��¼MIPICLK����Ӱ��Ƶ�ʵĽṹ��
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMipiClk;                              /* MipiClkֵ */
    VOS_UINT32                          aulFreq[MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM];/* ulMipiClkֵӰ���Ƶ�ʱ� */
}MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU;

/*******************************************************************************
 �ṹ��    : MTC_NVIM_RF_LCD_CFG_STRU
 �ṹ˵��  : MTCģ��RF&LCD���Ź���������NV��
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnableBitMap;                         /* ʹ�ܿ��أ�ÿ��bit����ͬ���㷨����0����ʹ�� */
    VOS_UINT16                          usFreqWidth;                            /* ���� ��λ100KHZ */
    MTC_NVIM_RF_LCD_MIPICLK_FREQ_STRU   astRfMipiClkFreqList[MTC_RF_LCD_MIPICLK_MAX_NUM]; /* ��λ100KHZ */
} MTC_NVIM_RF_LCD_CFG_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_WATER_MARK_LEVEL_NV_STRU
 �ṹ˵��  : ADS ULˮ�߽��ṹ
   1.��    ��   : 2014��06��03��
     ��    ��   : f00179208
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaterLevel1;                          /* ˮ�߽��1 */
    VOS_UINT32                          ulWaterLevel2;                          /* ˮ�߽��2 */
    VOS_UINT32                          ulWaterLevel3;                          /* ˮ�߽��3 */
    VOS_UINT32                          ulWaterLevel4;                          /* ˮ�߽��4,Ԥ�� */
} ADS_UL_WATER_MARK_LEVEL_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_WATER_MARK_LEVEL_NV_STRU
 �ṹ˵��  : ADS UL�ް����޽ṹ
   1.��    ��   : 2014��06��03��
     ��    ��   : f00179208
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulThreshold1;                           /* �ް�����1 */
    VOS_UINT32                          ulThreshold2;                           /* �ް�����2 */
    VOS_UINT32                          ulThreshold3;                           /* �ް�����3 */
    VOS_UINT32                          ulThreshold4;                           /* �ް�����4 */
} ADS_UL_THRESHOLD_LEVEL_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_WATER_MARK_LEVEL_NV_STRU
 �ṹ˵��  : ADS UL��̬�ް��ṹ
   1.��    ��   : 2014��06��03��
     ��    ��   : f00179208
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* ʹ�ܱ�ʶ: 0��ʾȥʹ��,1��ʾʹ�� */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /* ������ʱ����ʱ����ʱ�� */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;
    VOS_UINT32                          aulReserved[6];
} ADS_NV_DYNAMIC_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_Ata_Report_Ok_Async_Cfg NV������
 �޸ļ�¼  :
 1.��    ��   : 2014��06��23��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    /* VOS_TRUE:���ata�첽�ϱ�ok������connect���ϱ�ok����������connect ack��
       VOS_FALSE:δ����,ataͬ���ϱ�������connect����յ�����connect ack�����ϱ�ok */
    VOS_UINT8                           ucAtaReportOkAsyncFlag;
    VOS_UINT8                           aucReserved1[3];
}TAF_CALL_NVIM_ATA_REPORT_OK_ASYNC_CFG_STRU;



/*****************************************************************************
�ṹ��    : NV_NAS_JAM_DETECT_CFG_STRU
�ṹ˵��  : en_NV_Item_JAM_DETECT_CFG�ṹ

1.��    ��   : 2014��4��25��
  ��    ��   : y00142674
  �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;                                 /* JAM���õ�ģʽ��0:�ر�, 1:�� */
    VOS_UINT8                           ucMethod;                               /* JAM���ʹ�õķ�����1:����1��2:����2,Ŀǰֻ֧��2 */
    VOS_UINT8                           ucFreqNum;                              /* �����Ҫ�ﵽ��Ƶ�������ȡֵ��Χ:[0,255] */
    VOS_UINT8                           ucThreshold;                            /* �����Ҫ�ﵽ��Ƶ�����ֵ��ȡֵ��Χ:[0,70] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* ǿ�ź�Ƶ������������޺󣬼��ͬ������Ķ�ʱ��ʱ��(s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* ��⵽���ź󣬵ȴ�����������ʱ��(s) */
    VOS_UINT8                           ucFastReportFlag;                       /* �����������Ƿ���Ҫ�����ϱ� */
    VOS_UINT8                           aucRsv[1];
}NV_NAS_JAM_DETECT_CFG_STRU;
/*****************************************************************************
�ṹ��    : NV_NAS_WCDMA_JAM_DETECT_CFG_STRU
�ṹ˵��  : en_NV_Item_WCDMA_JAM_DETECT_CFG�ṹ

1.��    ��   : 2015��2��17��
  ��    ��   : y00142674
  �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;                                 /* JAM���õ�ģʽ��0:�ر�, 1:�� */
    VOS_UINT8                           ucMethod;                               /* JAM���ʹ�õķ�����1:����1��2:����2,Ŀǰֻ֧��2 */
    VOS_UINT8                           ucJamBandWidth;                         /* �������źŴ���Ĭ��30M */
    VOS_UINT8                           ucFastReportFlag;                       /* �����������Ƿ���Ҫ�����ϱ� */
    VOS_UINT8                           ucRssiSrhThreshold;                     /* ����RSSIʱ�����Ҫ�ﵽ��Ƶ�����ֵ��ȡֵ��Χ:[0,70]��ʵ���õ�ʱ���70ʹ�� */
    VOS_UINT8                           ucRssiSrhFreqPercent;                   /* ����RSSIʱ�����Ҫ�ﵽ��Ƶ�����ռƵ������(BAND�͸����ź�ȡ����)�İٷֱȣ�ȡֵ��Χ:[0,100] */
    VOS_UINT16                          usPschSrhThreshold;                     /* ����PSCHʱ�����ҪС�ڵ��ڵ�Ƶ�����ֵ��ȡֵ��Χ:[0,65535] */
    VOS_UINT8                           ucPschSrhFreqPercent;                   /* ����PSCHʱ�����Ҫ�ﵽ��Ƶ�����ռƵ������(BAND�͸����ź�ȡ����)�İٷֱȣ�ȡֵ��Χ:[0,100] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* ǿ�ź�Ƶ������������޺󣬼��ͬ������Ķ�ʱ��ʱ��(s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* ��⵽���ź󣬵ȴ�����������ʱ��(s) */
    VOS_UINT8                           aucRsv[1];
}NV_NAS_WCDMA_JAM_DETECT_CFG_STRU;
/*******************************************************************************
 �ṹ��    : TAF_NV_VCOM_DEBUG_CFG_STRU
 �ṹ˵��  : VCOM DEBUG�������NV��
  1.��    ��   : 2014��06��03��
    ��    ��   : n00269697
    �޸�����   : VCOM DEBUG����
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDebugLevel;                           /* VCOM DEBUG����:ERR,NORMAL,INFO,DEBUG */
    VOS_UINT32                          ulAppVcomPortIdMask;                    /* VCOM�˿�ID���� */
    VOS_UINT32                          ulReserved[4];                          /* Ԥ�� */
} TAF_NV_PORT_DEBUG_CFG_STRU;

/*******************************************************************************
 �ṹ��    : TAF_NVIM_FREQ_LOCK_CFG_STRU
 �ṹ˵��  : ��Ƶ�������NV��
  1.��    ��   : 2014��06��03��
    ��    ��   : g00261581
    �޸�����   : V711 Cell Lock��Ŀ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:��Ƶ���ܴ򿪣�0:���ܹر� */
    TAF_NVIM_RAT_MODE_ENUM_UINT8        enRatMode;
    VOS_UINT16                          usLockedFreq;
    TAF_NVIM_GSM_BAND_ENUM_UINT16       enBand;
    VOS_UINT8                           aucReserved[2];
} TAF_NVIM_FREQ_LOCK_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU
 �ṹ˵��  : ָʾDSDS��Ʒ����ʱ�Ķ�Modemģʽ
 1.��    ��   : 2014��09��21��
   ��    ��   : l00198894
   �޸�����   : ����DSDS��/˫������
*****************************************************************************/
typedef struct
{
    TAF_NV_ACTIVE_MODEM_MODE_ENUM_UINT8 enActiveModem;
    VOS_UINT8                           aucReserve[3];
}TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU;

/*******************************************************************************
 �ṹ��    : TAF_NVIM_ECID_TL2GSM_CFG_STRU
 �ṹ˵��  : AT+ECID����TDSCDMA��LTEģʽ����GSM��չС����Ϣ����
  1.��    ��   : 2014��11��11��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:���ܴ򿪣�0:���ܹر� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usMcc;                                  /* �����룬��ʽʾ��: 0x0460(�й���½) */
} TAF_NVIM_ECID_TL2GSM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU
 �ṹ˵��  : en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG NV��ṹ
 1.��    ��   : 2015��2��9��
 ��    ��   : z00161729
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOperNameServicePrioNum;

    /* 1����֧��PNN��cosp��^eonsucs2��ѯʱ���PNN�ļ�����ƥ�����Ӫ������;
       2����֧��CPHS,cops��^eonsucs2��ѯʱ���CPHS�ļ�����ƥ�����Ӫ������;
       3����֧��MM INFO,cops��^eonsucs2��ѯʱ��mm/gmm/emm information�в���ƥ�����Ӫ������;
       4����֧��SPN,cops��^eonsucs2��ѯʱ���SPN�ļ�����ƥ�����Ӫ������*/
    VOS_UINT8                           aucOperNameSerivcePrio[TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM];
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           ucPlmnCompareSupportWildCardFlag; /* plmn�Ƚ�ʱ�Ƿ�֧��ͨ��� */
    VOS_UINT8                           ucWildCard;                       /* ͨ���,ȡֵa-f,�ɴ���0-9�������� */
    VOS_UINT8                           ucReserved4;
    VOS_UINT8                           ucReserved5;                      /* �����ڲ���������^usimstub��^refreshstub�����Ƿ����*/
}TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU
 �ṹ˵��  : en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG NV��ṹ
 1.��    ��   : 2015��2��9��
 ��    ��   : z00161729
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRefreshAllFileRestartFlag;  /* 0: mma�յ�pih��refreshָʾ�����ļ����ʱ������modem; 1:mma�յ�pih��refreshָʾ�����ļ����ʱ�޽����绰ҵ��ʱ����modem*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU;


/*****************************************************************************
 �ṹ��    : TAF_NVIM_REFRESH_USIM_DELAY_RESTART_CFG_STRU
 �ṹ˵��  : TAF_NVIM_REFRESH_USIM_DELAY_RESTART_CFG_STRU NV��ṹ

  1.��    ��   : 2016��3��31��
    ��    ��   : c00318887
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNormalCallDelayRestartFlg;            /* �յ�refresh������������绰ʱ: 0: ��������modem; 1:�ӳ�����modem */
    VOS_UINT8                           ucSmsDelayRestartFlg;                   /* �յ�refresh�������smsʱ: 0: ��������modem; 1:�ӳ�����modem */
    VOS_UINT8                           ucSsDelayRestartFlg;                    /* �յ�refresh�������ssʱ: 0: ��������modem; 1:�ӳ�����modem */
    VOS_UINT8                           ucNoServiceDelayRestartFlg;             /* �յ�refresh���û��ҵ��ʱ: 0: ��������modem; 1:�ӳ�����modem */
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           ucReserved4;
    VOS_UINT8                           ucReserved5;
}TAF_NVIM_REFRESH_USIM_DELAY_RESTART_CFG_STRU;


/*****************************************************************************
 �ṹ����  : TAF_NV_PDN_TEARDOWN_POLICY_STRU
 �ṹ˵��  : PDN�Ͽ�����

  1.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAllowDefPdnTeardownFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;

} TAF_NV_PDN_TEARDOWN_POLICY_STRU;

typedef struct
{
    TAF_XSMS_DATA_REQ_SEND_CHAN_ENUM_UINT8                  enXsmsChannelOption;    /* �����ŵ���ר���ŵ� */
    VOS_UINT8                                               ucResendMax;            /* ���������������5�� */
    VOS_UINT8                                               ucResendInterval;       /* ���·������ݵ������ĵȴ�ʱ�䣬1�� */
    VOS_UINT8                                               ucReconnectInterval;    /* ���½������ӵĵȴ�ʱ�䣬5�� */
}TAF_NVIM_1X_XSMS_CFG_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_CFREQ_LOCK_CFG_STRU
�ṹ˵��  : 1X/EVDO��Ƶ����

  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    TAF_MMA_CFREQ_LOCK_MODE_TYPE_ENUM_UINT8                 enFreqLockMode;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usCdmaBandClass;
    VOS_UINT16                                              usCdmaFreq;
    VOS_UINT16                                              usCdmaPn;
    VOS_UINT16                                              usEvdoBandClass;
    VOS_UINT16                                              usEvdoFreq;
    VOS_UINT16                                              usEvdoPn;
}TAF_NVIM_CFREQ_LOCK_CFG_STRU;

/*****************************************************************************
 �ṹ����  : TAF_NV_TTY_CFG_STRU
 �ṹ˵��  : TTY MODE

  1.��    ��   : 2015��02��07��
    ��    ��   : w00316404
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTTYMode;/*TTYģʽֵ��0-3��default:0*/
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;

} TAF_NV_TTY_CFG_STRU;

/*******************************************************************************
 �ṹ��    : TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU
 �ṹ˵��  : gutlƵ���л�CHR�ϱ����á�NV��
  1.��    ��   : 2015��03��10��
    ��    ��   : n00269697
    �޸�����   : CHR optimize
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatisticTime;                        /* ͳ��ʱ�䣬��λΪ�� */
    VOS_UINT32                          ulSwitchNum;                            /* gutlƵ���л��Ĵ��� */
} TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU;

/*******************************************************************************
 �ṹ��    : TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU
 �ṹ˵��  : ���еȴ�����ģʽNV��
  1.��    ��   : 2015��08��24��
    ��    ��   : n00269697
    �޸�����   : ims_call_wait
*******************************************************************************/
typedef struct
{
    /* ��NV �������ú��еȴ��Ŀ���ģʽ��ulCcwaCtrlModeΪ0������еȴ���3gpp������ƣ�
       ulCcwaCtrlModeΪ1������еȴ���UE���ƣ�����VOLTE�����硣
      ����VoLTE�������ϣ�AP����CCWA֧��ʱ��IMS��û�к����罻����VoLTE�ĵ绰��CCWA��UE���ƣ���
       ֧��VOLTE���նˣ�����VOLTE������û�д򿪣������·�CCWAI�����ú��еȴ���
    */
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU;

/*******************************************************************************
 �ṹ��    : TAF_EMC_CS_TO_IMS_REDIAL_CFG_STRU
 �ṹ˵��  : CS������ʧ�ܵ�IMS�ز���NV
  1.��    ��   : 2016��03��30��
    ��    ��   : n00269697
    �޸�����   : VOLTE_EMC
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmcCs2ImsRedialSupportFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} TAF_EMC_CS_TO_IMS_REDIAL_CFG_STRU;


/*****************************************************************************
 �ṹ��    : TAF_NVIM_CCPU_RESET_RECORD_STRU
 �ṹ˵��  : en_NV_Item_Ccpu_Reset_Record NV��ṹ
 1.��    ��   : 2015��5��25��
   ��    ��   : n00269697
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0 �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcpuResetFlag;                        /* 0:����C�˵�����λ�������ϵ� ;
                                                                                   1:��C�˵�����λ*/
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_CCPU_RESET_RECORD_STRU;


/*****************************************************************************
�ṹ��    : TAF_NVIM_1X_DATA_SO_CFG
�ṹ˵��  : ��NV�ж�ȡ����ҵ��SO��ʼֵ

  1.��    ��   : 2015��8��12��
    ��    ��   : c00299063
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_DATA_SO_CFG;



/*****************************************************************************
�ṹ��    : TAF_NVIM_DATA_GENERIC_CONFIG_STRU
�ṹ˵��  : ��NV�ж�ȡ����ҵ������޷����ʱ��

  1.��    ��   : 2015��4��22��
    ��    ��   : c00299063
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPktCdataInactivityTmrLen;     /* CDMA���ݷ����������ݴ���ʱ��, ��λ�� */
    VOS_UINT8                           ucSwitchOnWaitCLTmerLen;        /* �����ȴ�CL������ʱ��ʱ������λ�� */
    VOS_UINT8                           uc1xBackOffToDoTmrLen;          /* 1X����ҵ������̬��ʱ������������inactive timer��ʱ����ʱ����
                                                                           1X backof to DO.��λ�룬0 ��ʾ�����Թر� */
    VOS_UINT8                           ucLessPktCdataInactivityTmrLen; /* CDMA���ݷ�������С�����ݴ���ʱ��, ��λ��, Ĭ��ֵ1s */
}TAF_NVIM_CDATA_GENERIC_CONFIG_STRU;


/*****************************************************************************
 �ṹ����  : TAF_NV_RNIC_NETIF_RX_TYPE_STRU
 �ṹ˵��  : ʹ��netif_rx�ں˺���������

  1.��    ��   : 2015��07��31��
    ��    ��   : w00316404
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRnicNetifRxType;    /* 0:netif_rx��1:netif_rx_ni��default:0 */
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_RNIC_NETIF_RX_TYPE_STRU;

/*****************************************************************************
 �ṹ����  : TAF_NV_ADS_WAKE_LOCK_CFG_STRU
 �ṹ˵��  : ADS WALE LOCK���ýṹ

  1.��    ��   : 2015��09��23��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;           /* ʹ�ܱ�ʶ */
    VOS_UINT32                          ulTxWakeTimeout;    /* ���з��ͻ��ѳ�ʱ���� */
    VOS_UINT32                          ulRxWakeTimeout;    /* ���н��ջ��ѳ�ʱ���� */
    VOS_UINT32                          ulReserved;

} TAF_NV_ADS_WAKE_LOCK_CFG_STRU;

/*****************************************************************************
 �ṹ����  : TAF_NV_ADS_MEM_CFG_STRU
 �ṹ˵��  : �ڴ�������Ϣ

  1.��    ��   : 2015��10��06��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usReserved0;
    VOS_UINT16                          usReserved1;
    VOS_UINT16                          usReserved2;

} TAF_NV_ADS_MEM_CFG_STRU;

/*****************************************************************************
 �ṹ����  : TAF_NV_ADS_MEM_POOL_CFG_STRU
 �ṹ˵��  : �ڴ�����ýṹ

  1.��    ��   : 2015��10��06��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;
    TAF_NV_ADS_MEM_CFG_STRU             astMemCfg[2];

} TAF_NV_ADS_MEM_POOL_CFG_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU
 �ṹ˵��  : en_Nv_Item_EMC_REDIAL_PERIOD NV��ṹ
 1.��    ��   : 2015��6��15��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulEmcCallRedialPeriod;  /* �������ز���ʱ��ʱ�� */
} TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU;

/*****************************************************************************
�ṹ��    : TAF_NVIM_1X_VOICE_SO_CFG
�ṹ˵��  : ��NV�ж�ȡ����ҵ�� so��ʼֵ

  1.��    ��   : 2015��8��19��
    ��    ��   : c00299063
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSo;
    VOS_UINT8                           aucReserved[2];
}TAF_NVIM_1X_VOICE_SO_CFG;



/*****************************************************************************
 �ṹ����  : TAF_NV_NVWR_SEC_CTRL_STRU
 �ṹ˵��  : NVWR���ȫ����

  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSecType;
    VOS_UINT8                           ucBlackListNum;
    VOS_UINT16                          ausBlackList[TAF_NV_BLACK_LIST_MAX_NUM];
} TAF_NV_NVWR_SEC_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_CCPU_RESET_RECORD_STRU
 �ṹ˵��  : en_NV_Item_Ipv6_Address_Test_Mode_Cfg NV��ṹ
 1.��    ��   : 2015��7��29��
   ��    ��   : n00269697
   �޸�����   : DTS2015072804293 �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulIpv6AddrTestModeCfg;                 /* 0x55aa55aa�ǲ���ģʽ������ֵΪ����ģʽ */
}TAF_NVIM_IPV6_ADDR_TEST_MODE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU
 �ṹ˵��  : en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG NV��ṹ
 1. ��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                               /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulRptSrvStaDelayTimerValue;             /*��ʱ�ϱ���ʱ��ʱ��,��λ:�� */
}TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU
 �ṹ˵��  : TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU�ṹ
  1.��    ��   : 2016��01��06��
    ��    ��   : h00313353
    �޸�����   : ��ȡ�ӳ��ϱ�CL����״̬ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucCLDelayTimerLen;                                              /* DO+LTE�ӳ��ϱ��޷���ʱ��ʱ��: 0:���ӳ��ϱ�����������ʱ���ӳٺ��ϱ� */
    VOS_UINT8   ucDoDelayTimerLen;                                              /* DO�ӳ��ϱ��޷���ʱ��ʱ��: 0:���ӳ��ϱ�����������ʱ���ӳٺ��ϱ� */
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}TAF_MMA_NVIM_DELAY_RPT_CLNOSERVICE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU
 �ṹ˵��  : en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL NV��ṹ
 1.��    ��   : 2015��8��18��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* ��ʱ��ʱ������λ:ms  */
}TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;

/*****************************************************************************
 �ṹ����  : TAF_NV_PRINT_MODEM_LOG_TYPE_STRU
 �ṹ˵��  : �����Ƿ����modem log������

  1.��    ��   : 2015��10��17��
    ��    ��   : w00316404
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrintModemLogType;                    /* 0:���modem log��1:�����modem log��default:0 */
    VOS_UINT8                           ucReserved0;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NV_PRINT_MODEM_LOG_TYPE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU
 �ṹ˵��  : CL�ӳ��ϱ� NV��ṹ
 1.��    ��   : 2015��8��18��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCLDelayRptEnable;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulCLRptSrvStaDelayTimerLen;
    VOS_UINT8                           aucReserved2[12];
}TAF_MMA_NVIM_CL_DELAY_REPORT_SERVICE_STATUS_STRU;


/*****************************************************************************
 �ṹ��    : TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU
 �ṹ˵��  : en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG NV��ṹ
 1.��    ��   : 2015��10��28��
   ��    ��   : z00359541
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMergeFlg;                             /* �������������Ƿ�ϲ�ע��״̬�ϱ� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU
 �ṹ˵��  : ECC��������������Ϣ��
             ע: ECCҵ��״̬����ECCҵ������֧�ֵ�����£�����Ч��

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC��������: TRUE -- ֧��ECC����FALSE -- ��֧��ECC���� */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC����״̬: TRUE -- ECC����򿪣�FALSE -- ECC����ر� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
} TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU
 �ṹ˵��  : ECC��Կ��Ϣ��������ԿK0�Լ���Ӧ�İ汾��

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT8                           aucPubKey[TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
} TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU
 �ṹ˵��  : ��ȫ��Ϣ����ϵͳʱ����Ϣ

 �޸ļ�¼  :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU
 �ṹ˵��  : ��������ϵͳʱ����Ϣ

 �޸ļ�¼  :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU
 �ṹ˵��  : ��ʱ�ܻ�������ʱ������

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDelayEncVoiceReqTimerLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usRemoteCtrlAnswerTimerLen;
} TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_1X_CALLBACK_CFG_STRU
 �ṹ˵��  : en_Nv_Item_CNAS_XSD_CALLBACK_CFG NV��ṹ
 1.��    ��   : 2016��1��9��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} TAF_NVIM_1X_CALLBACK_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_NDIS_FILTER_ENABLE_FLAG_CFG_STRU
 �ṹ˵��  : en_NV_Item_NDIS_FILTER_FLAG_CFG NV��ṹ
 1.��    ��   : 2015��12��26��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlag;                           /* VOS_TRUE:����Filter���˹���VOS_FALSE:�����ù��˹��� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_NDIS_FILTER_ENABLE_FLAG_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU
 �ṹ˵��  : TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU NV��ṹ
 1.��    ��   : 2016��04��25��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRedialInterTimerLen;   /* 1���ز��׶��У�ÿ���ز������ʱ��ʱ�� */
    VOS_UINT8                           ucRedialNum;             /* 1���ز��׶��У����Գ��Ե��ز����� */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
} TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_CFG_STRU
 �ṹ˵��  :  NV��ṹ
 1.��    ��   : 2016��04��25��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucPhaseNum;    /* �ܽ׶θ���: Ĭ��4���׶Σ�4s��10s��15s��20s */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_STRU          astRedialInfo[TAF_NVIM_MAX_1X_NW_NORMAL_REL_REDIAL_PHASE_NUM];
} TAF_NVIM_1X_NW_NORMAL_REL_REDIAL_STRATEGY_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU
 �ṹ˵��  :  NV��ṹ
 1.��    ��   : 2016��01��19��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsCfgEnable;  /* VOS_TRUE: ʹ�� VOS_FALSE:��ʹ�� */
    TAF_XSMS_TL_ACK_NEED_LEVEL_ENUM_UINT8                   enTlAckNeedLevel;
    VOS_UINT8                                               ucMaxFlacQryTime; /* ������Դ��� Ĭ��ֵ : 2*/
    VOS_UINT8                                               ucFlacQryInterVal;/* ���Լ�� ��λ:�ٺ��� Ĭ���� 6 ��600ms */
}TAF_XSMS_MO_TL_ACK_TIME_OUT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_KMC_DEF_ADDRESS_STRU
 �ṹ˵��  :  NV��ṹ
 1.��    ��   : 2015��10��14��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNumOfDigits;
    VOS_UINT8                           aucDigits[38]; /* DTMF���� */
}TAF_XSMS_KMC_DEF_ADDRESS_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU
 �ṹ˵��  :  �й�����OOS��ʱ��ʱ������
 1.��    ��   : 2016��2��15��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_CTCC_OOS_CONFIG_STRU
 �ṹ˵��  :  NV��ṹ
 1.��    ��   : 2016��2��15��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU    astClOosTimerCfg[TAF_NVIM_CTCC_OOS_TIMER_MAX_PHASE];
    TAF_NVIM_CTCC_OOS_TIMER_CFG_STRU    astGulOosTimerCfg[TAF_NVIM_CTCC_OOS_TIMER_MAX_PHASE];
}TAF_NVIM_CTCC_OOS_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_GET_DNS_THTOUGH_DHCP_CFG_STRU
 �ṹ˵��  :  �����Ƿ���Ҫͨ��DHCP��ȡDNS
 1.��    ��   : 2016��2��29��
   ��    ��   : y00213812
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNeedGetDnsByDhcp;                     /* 1��Ҫ��0����Ҫ��Ĭ��Ϊ0 */

    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;

}TAF_NVIM_GET_DNS_THTOUGH_DHCP_CFG_STRU;


/*****************************************************************************
 �ṹ��    : TAF_NVIM_XCPOSRRPT_CFG_STRU
 �ṹ˵��  : NV��ṹ
 1.��    ��   : 2016��03��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucXcposrRptNvCfg;                       /* �Ƿ��ϱ����GPS����ĸ�����λ��Ϣ */
    VOS_UINT8                           ucCposrDefault;
    VOS_UINT8                           ucXcposrDefault;
    VOS_UINT8                           ucXcposrRptDefault;
}TAF_NVIM_XCPOSRRPT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_ICC_ID_STRU
 �ṹ˵��  :    ICC ID�ṹ
 1.��    ��   : 2016��04��08��
   ��    ��   : w00316404
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucIccId[TAF_NVIM_ICC_ID_MAX];
}TAF_NVIM_ICC_ID_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_RPM_CFG_STRU
 �ṹ˵��  : RPM���Կ��ƽṹ
 1.��    ��   : 2016��04��08��
   ��    ��   : w00316404
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRpmCap;
    VOS_UINT8                           ucRpmEnableFlag;
    VOS_UINT8                           ucRpmVersion;
    VOS_UINT8                           ucReserved0;
    TAF_NVIM_ICC_ID_STRU                stUiccInfo;
    VOS_UINT8                           ucRpmParaN1;
    VOS_UINT8                           ucRpmParaT1;
    VOS_UINT8                           ucRpmParaF1;
    VOS_UINT8                           ucRpmParaF2;
    VOS_UINT8                           ucRpmParaF3;
    VOS_UINT8                           ucRpmParaF4;
    VOS_UINT8                           aucReserved1[TAF_NVIM_RPM_RSV_PARA_NUM];
}TAF_NVIM_RPM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_USER_REBOOT_SUPPORT_STRU
 �ṹ˵��  : �Ƿ�֧���û�����������λ
 1.��    ��   : 2016��05��30��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUserRebootConfig;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}TAF_NVIM_USER_REBOOT_SUPPORT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_NVIM_SPM_VOICE_DOMAIN_SEL_CFG_STRU
 �ṹ˵��  : ������ѡ����
  1.��    ��   : 2016��07��12��
    ��    ��   : m00217266
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulEmcRetryPeriod;           /* ���������Զ�ʱ��ʱ�� */
    TAF_SPM_NVIM_MULTIMODE_EMC_CS_PRFER_TYPE_ENUM_UINT8     enMultiModeEmcCsPreferType; /* ȫģ����������������ѡΪcs preferʱ��3gpp��3gpp2 cs�����ȼ� */
    VOS_UINT8                                               ucCycleRetryFlag;           /* ѭ�����Ա�־ */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucEnableFlg;                /* SPMģ��������ѡ��UE����������������Ƿ�ʹ�� */
    VOS_UINT8                                               ucSpmVoiceDomain;           /* SPMģ�����ͨ����ѡ��0:cs only 1:ps only 2:cs prefer 3:ps prefer */
    VOS_UINT8                                               ucSpmEmsDomain;             /* SPMģ���������ѡ��0:cs forced 1:cs prefer 2:ps prefer */
    VOS_UINT8                                               ucReserved3;
}TAF_NVIM_SPM_VOICE_DOMAIN_SEL_CFG_STRU;

/*****************************************************************************
 �ṹ����  : TAF_NVIM_DEACT_EMC_PDN_POLICY_STRU
 �ṹ˵��  : ��������PDN�ص�GU�����ӶϿ�����

  1.��    ��   : 2017��02��03��
    ��    ��   : W00316404
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAllowDeactEmcPdnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} TAF_NVIM_DEACT_EMC_PDN_POLICY_STRU;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
