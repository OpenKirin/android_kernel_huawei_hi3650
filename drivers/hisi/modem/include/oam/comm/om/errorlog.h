

#ifndef __ERRORLOG_H__
#define __ERRORLOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "v_typdef.h"
#include "OmCodecInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#pragma pack(4)

/*****************************************************************************
   �궨��
******************************************************************************/
#define MNTN_ERRLOG_DIR                     "/mnvm3:0/Errlog"
#define MNTN_ERRLOG0_PATH                   "/mnvm3:0/Errlog/Errorlog0.bin"  /*log�ļ�0��ַ*/
#define MNTN_ERRLOG1_PATH                   "/mnvm3:0/Errlog/Errorlog1.bin"  /*log�ļ�1��ַ*/
#define MNTN_ERRLOG_UNITARY_DIR             "/modem_log/Errlog"
#define MNTN_ERRLOG0_UNITARY_PATH           "/modem_log/Errlog/Errorlog0.bin"  /*log�ļ�0��ַ*/
#define MNTN_ERRLOG1_UNITARY_PATH           "/modem_log/Errlog/Errorlog1.bin"  /*log�ļ�1��ַ*/


#define MNTN_ERRLOG_IMEI_SIZE               (16)
#define MNTN_ERRLOG_HARDVERSION_SIZE        (32)
#define MNTN_ERRLOG_SOFTVERSION_SIZE        (32)
#define IMSI_RECORD_LEN						(9)

#define MNTN_ERRLOG_MAXSIZE                 (0x10000)

/* PC��ʱ��ʱ����������2 */
#define NAS_MNTN_PC_ACTIVE_EXPIRE_TIMES     (2)

/* PDP����ʧ��ԭ��ֵ��Ĭ��ֵ */
#define NAS_MNTN_SM_REJ_CAUSE_INVALID       (0xff)
#define MNTN_RAC_INVALID_ID                 (0xffff)
#define NAS_MNTN_IMSI_LENGTH_IN_USIM        (9)
#define NAS_MNTN_CS_ATTEMPT_MAX             (4)
#define NAS_MNTN_PS_ATTEMPT_MAX             (5)
#define NAS_MNTN_MAX_ASCII_ADDRESS_NUM      (20)
#define NAS_MNTN_MAX_HIGH_PLMN_NUM          (16)                                    /* ��������PLMN�������� RRC_MAX_HIGH_PLMN_NUM*/
#define NAS_MNTN_LOW_PLMN_NUM               (16)                                    /* ��������PLMN�������� RRC_MAX_LOW_PLMN_NUM*/
/* ERROR LOG�������¼��������������ʱ��ʱ��Ϊ5���5������ʱ��¼ */
/* ���������ʱ��ʱ��Ϊ5�룬��ʱ��ʱ��INDEXΪ0 */
#define NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_LENGTH_ZERO      (0)

/* ���������ʱ����5��������������ʱ����������Ϊ5 */
#define NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_COUNTER_TIMES    (5)

/* ERROR LOG�¼�ҵ�񲻿����¼��ӵ����ϵ絽�µ��ڼ��¼�¼��������� */
#define NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX     (10)

/* ERROR LOG�¼�����ʧ���¼��ӵ����ϵ絽�µ��ڼ��¼�¼��������� */
#define NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX        (30)

/* ERROR LOG�¼�PDP����ʧ���¼��ӵ����ϵ絽�µ��ڼ��¼�¼��������� */
#define NAS_MNTN_ERRORLOG_ACTIVATE_FAIL_EVENT_MAX           (15)

/* ERROR LOG�¼����ŷ���ʧ���¼��ӵ����ϵ絽�µ��ڼ��¼�¼��������� */
#define NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX                (5)

/*30�����ڼ�¼�����źŷ�����������*/
#define GAS_MNTN_WEAK_SIGNAL_LIST_MAX_NUM                       (30)

/* ERROR LOG�¼�ME�ļ�����ʧ���¼��ӵ����ϵ絽�µ��ڼ��¼�¼��������� */
#define NAS_MNTN_ERRORLOG_ME_FILE_ERROR_MAX                 (1)
/*******************************************************************************
   ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : MNTN_WRITEFLASH_EVENT_ENUM
 �ṹ˵��  : ԭ���ulMsgName
*****************************************************************************/
enum MNTN_WRITEFLASH_EVENT_ENUM
{
    /* ��Ϣ���� */                              /*��ϢID*/              /* ��ע */
    MNTN_VERSION_INFO_EVENT                     = 0x00000000,           /* _H2ASN_MsgChoice MNTN_VERSION_INFO_EVENT_STRU */
    MNTN_NAS_ERRORLOG_ACTIVATE_FAIL_EVENT       = 0x00000001,           /* _H2ASN_MsgChoice NAS_MNTN_ACTIVE_FAIL_EVENT_STRU */
    MNTN_NAS_ERRORLOG_PLMN_UNAVAILABLE_EVENT    = 0x00000002,           /* _H2ASN_MsgChoice NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SERVICE_UNAVAILABLE_EVENT = 0x00000003,           /* _H2ASN_MsgChoice NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SMS_MO_FAILURE            = 0x00000004,           /* _H2ASN_MsgChoice NAS_MNTN_SMS_MO_FAIL_EVENT_STRU */
    MNTN_NAS_ERRORLOG_CS_CHANNEL_OPEN_FAILURE   = 0x00000005,           /* _H2ASN_MsgChoice NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU */
    MNTN_NAS_ERRORLOG_CS_MED_TIMEOUT            = 0x00000006,           /* _H2ASN_MsgChoice NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU */
    MNTN_NAS_ERRORLOG_SMS_ME_ERROR              = 0x00000007,           /* _H2ASN_MsgChoice NAS_MNTN_SMS_ME_ERROR_EVENT_STRU */

    MNTN_GAS_INIT_WEAK_SIGNAL_EVENT             = 0x00000201,           /* _H2ASN_MsgChoice GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU */

    MNTN_GAS_PERIOD_WEAK_SIGNAL_LIST_EVENT      = 0x00000202,            /* _H2ASN_MsgChoice GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU */

    MNTN_WAS_NO_SIGNAL_EVENT                    = 0x00000301,           /* _H2ASN_MsgChoice WAS_MNTN_NO_SIGNAL_EVENT_STRU*/
    MNTN_WAS_WEAK_SIGNAL_SAMPLE_EVENT           = 0x00000302,           /* _H2ASN_MsgChoice WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU*/
    MNTN_OAM_NO_SIM_CARD_EVENT                  = 0x00000401,           /* _H2ASN_MsgChoice OAM_MNTN_NO_SIM_CARD_EVENT_STRU */
    MNTN_OAM_SIM_CARD_LOST_EVENT                = 0x00000402,           /* _H2ASN_MsgChoice OAM_MNTN_SIM_CARD_LOST_EVENT_STRU */
    MNTN_OAM_PCV_QUNUE_FULL_EVENT               = 0x00000403,           /* _H2ASN_MsgChoice OAM_MNTN_PCV_ERRLOG_EVENT_STRU */
    MNTN_OAM_PCV_DATA_EXCEPTION_EVENT           = 0x00000404,           /* _H2ASN_MsgChoice OAM_MNTN_PCV_ERRLOG_EVENT_STRU */
    MNTN_OAM_MNTN_NV_ERRLOG_EVENT               = 0x00000405,           /* _H2ASN_MsgChoice OAM_MNTN_NV_ERRLOG_EVENT_STRU */
    MNTN_OAM_MNTN_WD_COUNT_ERRLOG_EVENT         = 0x00000406,           /* _H2ASN_MsgChoice OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU */
    MNTN_OAM_PORT_NUM_ERRLOG_EVENT              = 0x00000407,           /* _H2ASN_MsgChoice OAM_MNTN_PORT_ERRLOG_EVENT_STRU */
    MNTN_USB_ENUMERATE_STATUS_EVENT             = 0x00000501,           /* _H2ASN_MsgChoice USB_MNTN_ENUMERATE_STATUS_EVENT_STRU */
    MNTN_USB_INSTALL_SUCCESS_EVENT              = 0x00000502,           /* _H2ASN_MsgChoice USB_MNTN_INSTALL_SUCCESS_EVENT_STRU */
    MNTN_USB_RESET_ABNORMAL_EVENT               = 0x00000503,           /* _H2ASN_MsgChoice USB_MNTN_RESET_ABNORMAL_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_DMA_MIC_RESET     = 0x00000601,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_DMA_SPK_RESET     = 0x00000602,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_W_DEC_INT_LOST    = 0x00000603,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_WBBP_DATA_NONE    = 0x00000604,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_WBBP_DATA_BAD     = 0x00000605,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_W_DECIPHER_LOST   = 0x00000606,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_GSM_BFI_FRAME     = 0x00000607,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_CODEC_SID_FRAME   = 0x00000608,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_PCV_INTERPOLATE   = 0x00000609,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_MED_VS_ERRLOG_EVENTS_PCV_RINGBUF_FULL  = 0x0000060A,           /* _H2ASN_MsgChoice MED_MNTN_CS_ERR_EVENT_STRU */
    MNTN_DRV_HIGH_STACK_RECORD                  = 0x00000701,           /* _H2ASN_MsgChoice HIGH_STACK_TASK_STR */
    MNTN_DRV_SD_ERRLOG_RECORD                   = 0x00000702,           /* _H2ASN_MsgChoice SD_TRANSFER_ERROR_ST */
    MNTN_DRV_WIFI_ERRLOG_RECORD                 = 0x00000703,           /* _H2ASN_MsgChoice WIFI_TARGET_ASSERT_ERROR_ST */
    MNTN_DRV_PMU_WRNLOG_RECORD                  = 0x00000704,           /* _H2ASN_MsgChoice MNTN_DRV_PMU_ERROR_ST */
    MNTN_DRV_PMU_ERRLOG_RECORD                  = 0x00000705,           /* _H2ASN_MsgChoice MNTN_DRV_PMU_ERROR_ST */
    MNTN_DRV_SYSTEM_RESET_RECORD                = 0x00000706,           /* _H2ASN_MsgChoice DRV_MNTN_SYSTEM_RESET_STRU */

    MNTN_SPY_QOS_LIMIT_EVENT                    = 0x00000801,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_SPY_SOFTOFF_EVENT                      = 0x00000802,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_SPY_PWOER_DOWN_EVENT                   = 0x00000803,           /* _H2ASN_MsgChoice OAM_MNTN_SPY_ERROR_EVENT_STRU */
    MNTN_OAM_SOCP_ERROR_EVENT                   = 0x00000A01,
    MNTN_OAM_ICC_ERROR_EVENT                    = 0x00000B01,
    MNTN_ERRLOG_BUTT                            = 0xFFFFFFFF
};
typedef VOS_INT32 MNTN_WRITEFLASH_EVENT_ENUM_UINT32;

typedef struct
{
    MNTN_HEAD_INFO_STRU    stRecordHead;
    VOS_UINT32             ulStatusReg;
}MNTN_DRV_PMU_ERROR_ST;

/*****************************************************************************
 ö����    : MNTN_ME_OPERATION_ENUM
 �ṹ˵��  : ����ME�洢���������ͣ���������д���ֲ���
*****************************************************************************/
enum MNTN_ME_OPERATION_ENUM
{
    MNTN_ME_OPERATION_READ,
    MNTN_ME_OPERATION_WRITE,
    MNTN_ME_OPERATION_BUTT
};
typedef VOS_INT32 MNTN_ME_OPERATION_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM
 �ṹ˵��  : PDP����ʧ�����ͣ�����PS����񲻿��ã�
             �ȴ�������Ӧ��ʱ,������ܾ��ͱ�BACKOFF�㷨�ܾ�
*****************************************************************************/
enum NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM
{
    NAS_MNTN_ACTIVE_FAIL_TYPE_PS_SERVICE_UNAVAILABLE = 0,
    NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_TIMEOUT,
    NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_REJECT,
    NAS_MNTN_ACTIVE_FAIL_TYPE_BACKOFF_ALG_NOT_ALLOWED,
    NAS_MNTN_ACTIVE_FAIL_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MNTN_SYS_SUBMODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : פ������Ľ��뼼��ö��
*****************************************************************************/
enum NAS_MNTN_SYS_SUBMODE_ENUM
{
    NAS_MNTN_SYS_SUBMODE_NULL                  = 0,                /* �޷��� */
    NAS_MNTN_SYS_SUBMODE_GSM                   = 1,                /* GSMģʽ */
    NAS_MNTN_SYS_SUBMODE_GPRS                  = 2,                /* GPRSģʽ */
    NAS_MNTN_SYS_SUBMODE_EDGE                  = 3,                /* EDGEģʽ */
    NAS_MNTN_SYS_SUBMODE_WCDMA                 = 4,                /* WCDMAģʽ */
    NAS_MNTN_SYS_SUBMODE_HSDPA                 = 5,                /* HSDPAģʽ */
    NAS_MNTN_SYS_SUBMODE_HSUPA                 = 6,                /* HSUPAģʽ */
    NAS_MNTN_SYS_SUBMODE_HSDPA_HSUPA           = 7,                /* HSDPA+HSUPAģʽ */
    NAS_MNTN_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  NAS_MNTN_SYS_SUBMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MNTN_SEND_DOMAIN_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���������״̬
*****************************************************************************/
enum NAS_MNTN_SEND_DOMAIN_STATUS_ENUM
{
    NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE,
    NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE
};
typedef VOS_UINT32 NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : OSA_MNTN_WD_COUNT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :��Դʹ��״̬
*****************************************************************************/
enum OSA_MNTN_WD_COUNT_ENUM
{
    OSA_MNTN_WD_COUNT_TIMER         = 0,
    OSA_MNTN_WD_COUNT_RTC_TIMER,
    OSA_MNTN_WD_COUNT_MESSAGE,
    OSA_MNTN_WD_COUNT_PS_MEMORY,
    OSA_MNTN_WD_COUNT_APP_MEMORY,
    OSA_MNTN_WD_COUNT_BUTT
};
typedef VOS_UINT32 OSA_MNTN_WD_COUNT_ENUM_UINT32;
/*****************************************************************************
   STRUCT����
*****************************************************************************/

/*******************************************************************************
 �ṹ��    : MNTN_VERSION_INFO_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �汾��Ϣ�ṹ
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stRecordHead;
    IMEI_STRU                           stIMEI;
    VOS_CHAR                            acHardVersion[MNTN_ERRLOG_HARDVERSION_SIZE];
    VOS_CHAR                            acSoftVersion[MNTN_ERRLOG_SOFTVERSION_SIZE];
}MNTN_VERSION_INFO_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : USB_MNTN_INSTALL_SUCCESS_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��װ��Ϣ�Ľṹ
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU              stRecordHead;
    VOS_UINT32                       ulRewindCommand;
    VOS_UINT32                       ulU2diag;
}USB_MNTN_INSTALL_SUCCESS_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : USB_MNTN_ENUMERATE_STATUS_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ö����Ϣ�Ľṹ
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU             stRecordHead;
    VOS_UINT32                      ulU2diag;
    VOS_UINT8                       ucFlag;      /*differentiate rewind and timeout*/
    VOS_UINT8                       ucUsbSpeed;
    VOS_UINT8                       ucUsbStatus;
    VOS_UINT8                       ucReserved;
}USB_MNTN_ENUMERATE_STATUS_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : USB_MNTN_RESET_ABNORMAL_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : usb�����쳣��λ��Ϣ�Ľṹ
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU             stRecordHead;
    VOS_UINT32                      ulU2diag;
    VOS_UINT8                       ucUsbStatus;
    VOS_UINT8                       ucUsbSpeed;
    VOS_UINT8                       ucSCSITimeoutFlag;
    VOS_UINT8                       ucSCSICommand;
    VOS_UINT8                       ucLastIntrIndex;
    VOS_UINT8                       aucReserve[3];
    VOS_UINT32                      ulLedStatus;
}USB_MNTN_RESET_ABNORMAL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : DRV_MNTN_SYSTEM_RESET_STR
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��¼ϵͳ��λ�ṹ�Ľṹ
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                    stRecordHead;
    VOS_UINT32                             ulRebootReason ;
    VOS_UINT32                             ulModeId;
    VOS_UINT32                             ulArg1;
    VOS_UINT32                             ulArg2;
    VOS_UINT8                              Imsi[IMSI_RECORD_LEN];
    VOS_UINT8                              ImsiStatus;
    VOS_UINT8                              reserv[2];
}DRV_MNTN_SYSTEM_RESET_STRU;

/*****************************************************************************
�ṹ��     : NAS_MNTN_SMS_ME_ERROR_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :ME�ļ��������󣬰�����������
             �¼�ͷ�����ļ�����������
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    MNTN_ME_OPERATION_ENUM_UINT32       enOperation;
    VOS_UINT32                          ulErrorNo;
} NAS_MNTN_SMS_ME_ERROR_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_PDP_ACTIVE_FAIL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʧ��ԭ�򣬰�����������:
             ����ʧ������ ֧�ֲ��ű�����ܾ�����������ȴ�������Ӧ��ʱ��PS���޷���
             ����ܾ�ԭ��ֵ
             GMM��PS���Ƿ�ע���־
*******************************************************************************/
typedef struct
{
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                   enFailType;
    VOS_UINT8                                               ucSmCause;
    /* ��ʱ������3380��ʱ���������л�ȡ���������¼ */
    VOS_UINT8                                               ucRegisterFlg;
    VOS_UINT8                                               aucReserved1[2];
}NAS_MNTN_PDP_ACTIVE_FAIL_STRU;

/*******************************************************************************
 �ṹ��    : MNTN_PLMN_ID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PLMN�Ľṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                        ulMcc;
    VOS_UINT32                        ulMnc;
}MNTN_PLMN_ID_STRU;/* MMC_PLMN_ID_STRU�ṹ��ͬ���ṹ */

/*******************************************************************************
 �ṹ��    : MNTN_RAI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : λ������·������Ϣ
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmn;
    VOS_UINT16                          usLac;
    VOS_UINT16                          usRac;
}MNTN_RAI_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_USIM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS��ص�(U)SIM����Ϣ��������������:
             ������״̬��������(����SIM����USIM���Ϳ��ٿ���)������PIN�뿪��״̬
             (U)SIM����IMSI
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCardStatus;                           /* ��״̬: �޿����п� */
    VOS_UINT8                           ucCardType;                             /* ������: SIM����USIM�������ٿ��� */
    VOS_UINT8                           ucPinStatus;                            /* ��PIN��״̬: READY��*/
    VOS_UINT8                           aucImsi[NAS_MNTN_IMSI_LENGTH_IN_USIM];  /* IMSI���� */
    MNTN_PLMN_ID_STRU                   stRplmn;
}NAS_MNTN_USIM_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_POSITION_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : λ����Ϣ��������������
             λ�ú�·������Ϣ��С��ID��CS��������ޱ�־��PS��������ޱ�־��
             ϵͳ��ģʽ�����뼼��������ģʽ
*******************************************************************************/
typedef struct
{
    MNTN_RAI_INFO_STRU                      stRai;                                  /* LAC: g_MmcGlobalCtrl.CurLai.ulLac */
    VOS_UINT32                              ulCellId;                               /* CELL ID: gstMmcCellInfo.aulCellId[0]*/
    NAS_MNTN_SYS_SUBMODE_ENUM_UINT8         enSysSubMode;                           /* ��ǰС����ϵͳ��ģʽ��ϵͳ��Ϣ�ṹRRMM_SYS_INFO_IND_STRU������ */
    VOS_UINT8                               ucRat;
    VOS_UINT8                               ucNetworkMode;                          /* NETWORK MODE: g_MmcGlobalCtrl.ucNwMode */
    VOS_UINT8                               aucReserved[1];
}NAS_MNTN_POSITION_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_CS_UNAVAILABLE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CS��ע��ʧ��ԭ���б�������������
             ע��ʧ�ܴ�����ע��ʧ��ԭ��ֵ�б��Ҫ��������¼�¼���־��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulCause[NAS_MNTN_CS_ATTEMPT_MAX];                                             /* ����ʧ��ԭ��                             */
    VOS_BOOL                            bRecordRequired;
}NAS_MNTN_CS_UNAVAILABLE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_PS_UNAVAILABLE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS��ע��ʧ��ԭ���б�������������
             ע��ʧ�ܴ�����ע��ʧ��ԭ��ֵ�б��Ҫ��������¼�¼���־��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimes;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulCause[NAS_MNTN_PS_ATTEMPT_MAX];                                             /* ����ʧ��ԭ��                             */
    VOS_BOOL                            bRecordRequired;
}NAS_MNTN_PS_UNAVAILABLE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_SERVICE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ע��ʧ��ԭ���б�������������
             CS���PS��ע��״̬
*******************************************************************************/
typedef struct
{
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU   stCsUnavailable;
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU   stPsUnavailable;
}NAS_MNTN_SERVICE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_MO_SERVICE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���Ź�����ص�UST�ļ���Ϣ��������������
             (U)SIM���е�SMSS,SMS,SMSR,SMSP�ļ��Ĵ���״̬
             �Ƿ�֧��MO-SMS Control by USIM
*******************************************************************************/
typedef struct
{
    VOS_BOOL                            bEfSmssFlag;                            /*�Ƿ�֧��EFSMSS�ļ�*/
    VOS_BOOL                            bEfSmsFlag;                             /*SMS Storage �������*/
    VOS_BOOL                            bEfSmsrFlag;                            /*SMSR Storage �������*/
    VOS_BOOL                            bEfSmspFlag;                            /*SMSP �������*/
    VOS_BOOL                            bMoSmsCtrlFlag;                         /*�Ƿ�֧��MO-SMS Control by USIM*/
}NAS_MNTN_MO_SERVICE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_USIM_STATUS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���Ź��ܳ�ʼ����Ϣ��������������
             ����ģ���¼��(U)SIM������״̬������TAF��ĳ�ʼ��״̬
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsimStatus;                           /*SIM��״̬*/
    VOS_UINT8                           ucPowerState;                           /*��ʶ�Ƿ����ϵ������*/
    VOS_UINT8                           aucReserved[2];
} NAS_MNTN_USIM_STATUS_INFO_STRU;/*MN_MSG_USIM_STATUS_INFO_STRU*/

/*******************************************************************************
 �ṹ��    : NAS_MNTN_ASCII_ADDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���Ź��ܵ�ַ��Ϣ���ݽṹ��������������
             �������ͣ����żƻ������볤�ȣ�ASCII�����ĺ���
*******************************************************************************/
/*Content of Sms BCD Address*/
typedef struct
{
    VOS_UINT8                           ucNumType;                              /*type of number*/
    VOS_UINT8                           ucNumPlan;                              /*Numbering plan identification*/
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulLen;                                  /*Length of AsicNum*/
    VOS_UINT8                           aucAsciiNum[NAS_MNTN_MAX_ASCII_ADDRESS_NUM + 1];   /*array  of ASCII Num*/
    VOS_UINT8                           aucReserve2[3];
} NAS_MNTN_ASCII_ADDR_STRU;/*MN_MSG_ASCII_ADDR_STRU*/

/*******************************************************************************
 �ṹ��    : NAS_MNTN_SMS_MO_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ŷ��͹�����Ϣ���ݽṹ��������������
             ���Ź�����ص�UST�ļ���Ϣ�����Ź��ܳ�ʼ����Ϣ���������ĺ��룬
             ���ŷ���Ŀ�ĺ��룬RP-ERROR��Ϣ�е�RP-Cause
1.��    ��   : 2013��6��26��
  ��    ��   : f62575
  �޸�����   : V9R1 STK���� ucRpCause-> ulMoFailCause
*******************************************************************************/
typedef struct
{
    NAS_MNTN_MO_SERVICE_INFO_STRU       stUstInfo;
    NAS_MNTN_USIM_STATUS_INFO_STRU      stMsgStatus;
    NAS_MNTN_ASCII_ADDR_STRU            stScAddr;                               /*destination addr of sms*/
    NAS_MNTN_ASCII_ADDR_STRU            stDestAddr;                             /*destination addr of sms*/
    VOS_UINT32                          ulMoFailCause;
}NAS_MNTN_SMS_MO_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_LOW_PLMN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������PLMN��Ϣ���ݽṹ��������������
             PLMN��Ϣ��RSCP����ֵ
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmnId;                               /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP����ֵ */
}NAS_MNTN_LOW_PLMN_INFO_STRU;/*RRC_LOW_PLMN_INFO_STRU*/

/*******************************************************************************
 �ṹ��    : NAS_MNTN_PLMN_AVAILABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PLMN��Ϣ���ݽṹ��������������
             ������PLMN�ĸ�����������PLMN�ĸ�����������PLMN��Ϣ�б�������PLMN��Ϣ�б�
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* ������PLMN�ĸ��� */
    MNTN_PLMN_ID_STRU                   astHighPlmnList[NAS_MNTN_MAX_HIGH_PLMN_NUM];   /* ������PLMN�б�   */
    VOS_UINT32                          ulLowPlmnNum;                           /* ������PLMN�ĸ��� */
    NAS_MNTN_LOW_PLMN_INFO_STRU         astLowPlmnList[NAS_MNTN_LOW_PLMN_NUM];     /* ������PLMN�б�   */
}NAS_MNTN_PLMN_AVAILABLE_STRU;/*RRC_PLMN_ID_LIST_STRU*/

/*******************************************************************************
 �ṹ��    : NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE�����򲻿����¼���������������
             �¼�ͷ����NAS��ص�SIM����Ϣ��λ����Ϣ������������Ϣ
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    VOS_UINT32                          ulBand;
    /* �䳤�ȵĿ���PLMN�б���ϸ��Ϣֱ����ASN�ж��壬 */
    VOS_UINT8                           aucPlmnAttempt[4];
}NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE�����򲻿����¼���������������
             �¼�ͷ����NAS��ص�SIM����Ϣ��λ����Ϣ��UEע��״̬
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_SERVICE_INFO_STRU          stServiceInfo;
}NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_SMS_MO_FAIL_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ŷ���ʧ���¼���������������
             �¼�ͷ����NAS��ص�(U)SIM����Ϣ��λ����Ϣ�����ŷ��͹��������Ϣ
             CS�����״̬��PS�����״̬��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_SMS_MO_INFO_STRU           stMoFail;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enCsStatus;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enPsStatus;
}NAS_MNTN_SMS_MO_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_ACTIVE_FAIL_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʧ���¼���������������
             �¼�ͷ����NAS��ص�SIM����Ϣ��λ����Ϣ��PDP����ʧ��ԭ��PS��ע��״̬
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;
    NAS_MNTN_PDP_ACTIVE_FAIL_STRU       stPsActiveFail;
}NAS_MNTN_ACTIVE_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_MSG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ERROR LOG��Ϣ������MO����ʧ�ܼ�����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMoFailureCounter;
    VOS_UINT8                           ucMeFileErrorCounter;
    VOS_UINT8                           aucReserved1[2];
}NAS_MNTN_MSG_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_SM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SM���ERROR LOG��Ϣ������PDP����ʧ�ܼ�����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdpActiveFailureCounter;
    VOS_UINT8                           aucReserved1[3];
}NAS_MNTN_SM_INFO_STRU;

typedef struct
{
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU   stCsUnavailableInfo;
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU   stPsUnavailableInfo;
    NAS_MNTN_PLMN_AVAILABLE_STRU        stPlmnAvailableList;
    VOS_UINT8                           ucServiceUnavailableCounter;
    VOS_UINT8                           ucPlmnUnavailableCounter;
    VOS_UINT8                           aucReserved1[2];
}NAS_MNTN_MM_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CS������ͨ����ʧ���¼�ERROR LOG��Ϣ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* NAS���ĵ�SIM����Ϣ�� */
    VOS_UINT16                          usPort;                                 /* ����ͨ���˿� */
    VOS_UINT8                           aucReserved1[2];                        /* ���ֽڶ�������ֶ� */
    VOS_UINT32                          ulOmOperResult;                         /* OM�򿪵�����ͨ���˿�ִ�н���� */
}NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VC��MED���ֳ�ʱ�¼�ERROR LOG��Ϣ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* NAS���ĵ�SIM����Ϣ�� */
    VOS_UINT32                          ulTimerId;                              /* ��ʱ����ʱ�¼� */
} NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU;

#define MNTN_WAS_WEAK_SIGNAL_SAMPLE_NUMBER    (30)  /*Error LOG�ϱ��ļ��ʱ�䣬30���ӱ�һ��*/

/*****************************************************************************
 ��Ϣ����  : WAS_MNTN_FREQ_INFO_STRU
 ��������  : Ƶ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlUarfcn;   /* ����Ƶ�� Integer(0 .. 16383),��Чֵ0xFFFF */
    VOS_UINT16                          usDlUarfcn;   /* ����Ƶ��,��Чֵ0xFFFF                     */
} WAS_MNTN_FREQ_INFO_STRU;

/*****************************************************************************
 ��Ϣ����  : WAS_MNTN_NO_SIGNAL_EVENT_STRU
 ��������  : ��¼�����������źŵ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    MNTN_RAI_INFO_STRU                   stRai;
    WAS_MNTN_FREQ_INFO_STRU              stFreqInfo;
    VOS_UINT16                           usPSC;       /* ���� Integer(0..511) */
    VOS_INT16                            sRscp;
    VOS_INT16                            sECN0;
    VOS_UINT8                            aucReserve1[2];     /* ���� */
}WAS_MNTN_NO_SIGNAL_EVENT_STRU;

/*****************************************************************************
 ��Ϣ����  : WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU
 ��������  : WAS�������ź�ʱ��Ҫ�ϱ���С����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    MNTN_RAI_INFO_STRU                   stRai;       /*λ������·������Ϣ */
    WAS_MNTN_FREQ_INFO_STRU              stFreqInfo;  /* ������Ƶ����Ϣ */
    VOS_UINT16                           usPSC;       /* ���� Integer(0..511) */
    VOS_INT16                            sRscp;
    VOS_INT16                            sECN0;
    VOS_UINT16                           usErrlogIndex;/*���źŷ�����30���ӵĵڼ�����  */
}WAS_MNTN_WEAK_SIGNAL_CELL_INFO_STRU;

/*****************************************************************************
 ��Ϣ����  : WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU
 ��������  : WAS���źŲ����ϱ���Ϣ�ṹ,30���ӱ�һ�Σ�
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    VOS_UINT16                           usWeakSignalNum;    /* 30���������źŷ������� */
    VOS_UINT8                            aucReserve2[2];     /* ���� */
    WAS_MNTN_WEAK_SIGNAL_CELL_INFO_STRU  astWeakSignalCellInfo[MNTN_WAS_WEAK_SIGNAL_SAMPLE_NUMBER];/*�������ź�ʱ��Ҫ�ϱ���С����Ϣ*/
}WAS_MNTN_WEAK_SIGNAL_SAMPLE_EVENT_STRU;
/*****************************************************************************
 ��Ϣ����  : GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU
 ��������  : GAS���������ź��¼��ṹ
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    MNTN_RAI_INFO_STRU                  stRai;
    VOS_UINT16                          usArfcn;
    VOS_INT16                           sRxlev;
}GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU;

/*****************************************************************************
 ��Ϣ����  : GAS_MNTN_WEAK_SIGNAL_INFO_STRU
 ��������  : GAS���ź������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWeakSignalIndex;      /*���źŷ�����30���ӵĵڼ�����*/
    VOS_UINT8                           aucReserve1[3];
    MNTN_RAI_INFO_STRU                  stRai;                  /*���źŷ���С�������Ϣ:PLMN��LAC����RAC��*/
    VOS_UINT16                          usArfcn;                /*Ƶ���*/
    VOS_INT16                           sRxlev;                 /*�ź�ǿ�ȣ���dBmΪ��λ*/
}GAS_MNTN_WEAK_SIGNAL_INFO_STRU;

/*****************************************************************************
 ��Ϣ����  : GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU
 ��������  : Gģ���ź��¼��ϱ��ṹ
*****************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                  stHeader;
    VOS_UINT8                            ucWeakSignalNum;                                       /*���źŷ����Ĵ���*/
    VOS_UINT8                            aucReserve1[3];
    GAS_MNTN_WEAK_SIGNAL_INFO_STRU       astWeakSignalInfo[GAS_MNTN_WEAK_SIGNAL_LIST_MAX_NUM];  /*30����ÿ���ӷ��������źż������Ϣ*/
} GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_NO_SIM_CARD_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ̽�⵽��SIM���¼���������������
             �¼�ͷ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_NO_SIM_CARD_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_SIM_CARD_LOST_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ̽�⵽SIM�������¼���������������
             �¼�ͷ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_SIM_CARD_LOST_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_PCV_ERRLOG_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PC voice �쳣
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_PCV_ERRLOG_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_NV_ERRLOG_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NV�ָ� �쳣
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_NV_ERRLOG_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_PORT_ERRLOG_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM�˿�����
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT16                          usLineNum;
    VOS_UINT16                          usPortNum;
}OAM_MNTN_PORT_ERRLOG_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : MED_MNTN_CS_ERR_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MED ERR LOG EVENT
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    CODEC_OM_ERRLOG_EVENT_RPT_STRU      stMedErrLog;
}MED_MNTN_CS_ERR_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : HIGH_STACK_TASK_STR
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DRV HIGH STACK EVENT
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU     stRecordHead;
    VOS_INT8                taskName[16] ;
    VOS_INT32               taskId;
    VOS_INT32               highStackSize;
    VOS_INT32               taskStackSize;
}HIGH_STACK_TASK_STR;

/*******************************************************************************
 �ṹ��    : SD_TRANSFER_ERROR_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��¼SD�������쳣�ṹ��
*******************************************************************************/
typedef struct
{
   VOS_UINT32 Ebe_int;
   VOS_UINT32 Ccd_int;
   VOS_UINT32 Sbe_int;
   VOS_UINT32 Hle_int;
   VOS_UINT32 Frun_int;
   VOS_UINT32 Hto_int;
   VOS_UINT32 Drto_int;
   VOS_UINT32 Rto_int;
   VOS_UINT32 Dcrc_int;
   VOS_UINT32 Rcrc_int;
   VOS_UINT32 Rxdr_int;
   VOS_UINT32 Txdr_int;
   VOS_UINT32 Dto_int;
   VOS_UINT32 Cd_int;
   VOS_UINT32 Re_int;
}SD_ERROR_REG_BIT_ST;

typedef struct
{
    MNTN_HEAD_INFO_STRU                  stRecordHead;
    SD_ERROR_REG_BIT_ST                  stSdErrLogGetFromInt;
}SD_TRANSFER_ERROR_ST;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Դʹ�����
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    OSA_MNTN_WD_COUNT_ENUM_UINT32       enReason;
}OAM_MNTN_WD_COUNT_ERRLOG_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_SOCP_ERROR_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ̽�⵽SOCPͨ�������¼���������������
             �¼�ͷ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT32                          ulChannelID;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          ulData;
}OAM_MNTN_SOCP_ERROR_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_ICC_ERROR_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ̽�⵽ICCͨ�������¼���������������
             �¼�ͷ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
    VOS_UINT32                          ulChannelID;
    VOS_UINT32                          ulEvent;
    VOS_UINT32                          ulData;
}OAM_MNTN_ICC_ERROR_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : OAM_MNTN_SPY_ERROR_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ̽�⵽���±����¼���������������
             �¼�ͷ��
*******************************************************************************/
typedef struct
{
    MNTN_HEAD_INFO_STRU                 stHeader;
}OAM_MNTN_SPY_ERROR_EVENT_STRU;


/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    MNTN_WRITEFLASH_EVENT_ENUM_UINT32   enMsgID;    /*_H2ASN_MsgChoice_Export MNTN_WRITEFLASH_EVENT_ENUM_UINT32*/
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��MNTN_WRITEFLASH_EVENT_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MNTN_WRITEFLASH_EVENT_ENUM_UINT32
    ****************************************************************************/
}ERR_LOG_MSG_DATA;
/*_H2ASN_Length UINT32*/

/* ��������ݽṹ�벻Ҫ��������, ��ASN����dll��� */
typedef struct
{
    VOS_UINT32                          ulInfoLen; /* _H2ASN_Skip */
    ERR_LOG_MSG_DATA                    stMsgData;
}ErrorLog_MSG;

/*****************************************************************************
  �ⲿ�ӿڶ���
*****************************************************************************/
extern VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen);
#define MNTN_RecordErrorLog(ulErrNo,pBuf,ulLen) \
    DIAG_ErrorLog(__FILE__,THIS_FILE_ID,__LINE__,ulErrNo,pBuf,ulLen)

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif/* end of ErrorLog.h */

