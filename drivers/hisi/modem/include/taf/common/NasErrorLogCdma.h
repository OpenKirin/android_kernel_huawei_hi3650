

#ifndef __NAS_ERRORLOGCDMA_H__
#define __NAS_ERRORLOGCDMA_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "NasErrorLogComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_ERR_LOG_HRPD_SECTORID_LENGTH                (16)

#define NAS_ERR_LOG_CL_OOS_MAX_SEARCH_RECORD_NUM        (20)   /* CL��ģ���������У���¼��������Ϣ������� */
#define NAS_ERR_LOG_MAX_CDMA_PS_CALL_EXCEP_REDIAL_NUM   (10)   /* CDMA PS���й����м�¼���ز���Ϣ������� */
#define NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM         (10)   /* CDMA PS�쳣���������У���¼���쳣��Ϣ�������  */

#define NAS_ERR_LOG_1X_CS_CALL_MAX_REDIAL_NUM           (10)

#define NAS_ERR_LOG_1X_OOS_MAX_SEARCH_RECORD             (20)
#define NAS_ERR_LOG_HRPD_OOS_MAX_SEARCH_RECORD           (20)

#define NAS_ERR_LOG_HRPD_UATI_ASSIGN_MAX_CNT      (5)   /* uati���������У�uati�ط������������� CNAS_HSM_UAIT_REQ_FAILED_MAX_CNT ����һ�� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 ö����    : NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_ENUM
 ö��˵��  : Session�쳣ȥ����ԭ��
  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_ENUM
{
    NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_BY_AN                  = 0,
    NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_BY_KEEPALIVE_TIMEOUT   = 1,
    NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_BY_SESSION_NEG_FAIL    = 2,
    NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_BUTT
};
typedef  VOS_UINT32  NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM
 �ṹ˵��  :  CL��ģ������ÿ���������
 1.��    ��   : 2016��2��24��
   ��    ��   : l00324781
   �޸�����   : ����
*****************************************************************************/
enum NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM
{
    /* HRPDפ����� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_SUCC       = 0x0000,     /* HRPD�����ɹ� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_FAIL       = 0x0001,     /* HRPD����ʧ�� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_ABORTED    = 0x0002,     /* HRPD��������� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_NO_RF      = 0x0003,     /* HRPD����Դ */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_REG_NO_RF  = 0x0004,     /* �����ɹ���ע����ΪNo_Rf */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_TIMEOUT    = 0x0005,     /* �ȴ�HSD���������ʱ */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_MSCC_ABORT = 0x0006,     /* HRPD������MSCC����� */

    /*  LTEפ�����  */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_NORMAL_SRV  = 0x1000,     /* LTE�����ɹ� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_LIMITED_SRV = 0x1001,     /* LTE����ʧ�� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_NO_SRV      = 0x1002,     /* LTE����ʧ�� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_INTERUPT    = 0x1003,     /* LTE��������� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_NO_RF       = 0x1004,     /* LTE����Դ */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_L2C         = 0x1005,     /* LTE��ѡ��HRPD*/
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_TIMEOUT     = 0x1006,     /* MSCC�ȴ�MCC���������ʱ*/
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_MSCC_ABORT  = 0x1007,     /* LTE������MSCC����� */
    NAS_ERR_LOG_CL_SEARCH_RSLT_BUTT            = 0xffff
};
typedef VOS_UINT32  NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_APS_RAT_TYPE_ENUM
 �ṹ˵��  :  PS���������ӵĽ��뼼��
 1.��    ��   : 2016��2��24��
   ��    ��   : l00324781
   �޸�����   : ����
*****************************************************************************/
enum NAS_ERR_LOG_APS_RAT_TYPE_ENUM
{
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_NULL,          /* ��ǰδ���κ�������פ�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_GSM,           /* GSM���뼼�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_LTE,           /* LTE���뼼�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_1X,            /* CDMA-1X���뼼�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_HRPD,          /* CDMA-HRPD���뼼�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_EHRPD,         /* CDMA-EHRPD���뼼�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_OOS_CAUSE_ENUM
 �ṹ˵��  : 1x����ԭ��ֵ

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
enum NAS_ERR_LOG_1X_OOS_CAUSE_ENUM
{
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_RESCAN,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_PROTO_MISMATCH,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_SYS_LOST,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_LOCK,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_UNLOCK,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_ACCESS_DENIED,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_ACCT_BLOCKED,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_NDSS_OFF,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_ERR,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_REDIRECTION,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_REGIST_REJ,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_RELEASE,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_RESELECTION,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_NEW_SYSTEM,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_MAX_ACCESS_FAILURE,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_ABNORMAL,
    NAS_ERR_LOG_1X_OOS_CAUSE_SD_ACQUISITION_FAIL,
    NAS_ERR_LOG_1X_OOS_CAUSE_NO_RF,
    NAS_ERR_LOG_1X_OOS_CAUSE_INVAID_REDIRECTION,
    NAS_ERR_LOG_1X_OOS_CAUSE_REDIRE_FAILURE,
    NAS_ERR_LOG_1X_OOS_CAUSE_PREFERRED_RESELECTION,
    NAS_ERR_LOG_1X_OOS_CAUSE_NOT_PREFERRED_RESELECTION,
    NAS_ERR_LOG_1X_OOS_CAUSE_HANDOFF_NEGATIVE_SYS,
    NAS_ERR_LOG_1X_OOS_CAUSE_CALL_RELEASE_ACQ_FAIL,
    NAS_ERR_LOG_1X_OOS_CAUSE_ENC_CALL_RELEASE_ACQ_FAIL,
    NAS_ERR_LOG_1X_OOS_CAUSE_SWITCH_ON_SEARCH_FAIL,
    NAS_ERR_LOG_1X_OOS_CAUSE_POWER_ON,                   /* CLģʽ�£������ɹ���һ��ʱ�䴦������״̬�������ϱ�һ��1x oss��Я����ԭ��ֵ */
    NAS_ERR_LOG_1X_OOS_CAUSE_OTHER,
    NAS_ERR_LOG_1X_OOS_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_1X_OOS_CAUSE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_OOS_CAUSE_ENUM
 �ṹ˵��  : Hrpd����ԭ��ֵ

  1.��    ��   : 2016��02��24��
    ��    ��   : d0212987
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
enum NAS_ERR_LOG_HRPD_OOS_CAUSE_ENUM
{
    NAS_ERR_LOG_CAS_NETWORK_LOST_NORMAL_ACS                     = 0x0000,
    NAS_ERR_LOG_CAS_NETWORK_LOST_NORMAL_OTHER                   = 0x0001,
    NAS_ERR_LOG_CAS_NETWORK_LOST_REDIRECT                       = 0x0002,
    NAS_ERR_LOG_CAS_NETWORK_LOST_ABNORMAL                       = 0x0003,
    NAS_ERR_LOG_CAS_NETWORK_LOST_NO_RF                          = 0x0004,
    NAS_ERR_LOG_CAS_NETWORK_LOST_REASON_ENUM_BUTT               = 0x0005,

    NAS_ERR_LOG_HSM_SESSION_NEG_RSLT_FAIL                       = 0x0006,
    NAS_ERR_LOG_HSM_SESSION_NEG_RSLT_TIMEOUT                    = 0x0007,
    NAS_ERR_LOG_HSM_SESSION_NEG_RSLT_SESSION_CLOSE              = 0x0008,
    NAS_ERR_LOG_HSM_SESSION_NEG_RSLT_ENUM_BUTT                  = 0x0009,

    NAS_ERR_LOG_MSCC_PIF_ACQUIRED_RESULT_FAIL                   = 0x000A,
    NAS_ERR_LOG_MSCC_PIF_ACQUIRED_RESULT_ABORTED                = 0x000B,
    NAS_ERR_LOG_MSCC_PIF_ACQUIRED_RESULT_NO_RF                  = 0x000C,
    NAS_ERR_LOG_MSCC_PIF_ACQUIRED_RESULT_ENUM_BUTT              = 0x000D,

    NAS_ERR_LOG_MSCC_SESSION_NEG_RESULT_FAIL                    = 0x000E,
    NAS_ERR_LOG_MSCC_SESSION_NEG_RESULT_TIMEOUT                 = 0x000F,              /* session negotiation result timeout ref 143 5.8.1 */
    NAS_ERR_LOG_MSCC_SESSION_NEG_RESULT_ENUM_BUTT               = 0x0010,

    NAS_ERR_LOG_MSCC_PIF_POWER_SAVE_FAILURE                     = 0x0011,

    NAS_ERR_LOG_MSCC_PIF_ENUM_BUTT                              = 0x0012,

    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_FAIL                         = 0x0013,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_PERSIST_FAIL                 = 0x0014,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_MAX_PROBE                    = 0x0015,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_AUTH_BILLING_FAIL            = 0x0016,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_BS_BUSY_OR_GENERAL           = 0x0017,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID          = 0x0018,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT          = 0x0019,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_NO_RF                        = 0x001A,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_SRCHING_NETWORK              = 0x001B,
    NAS_ERR_LOG_HSM_CONN_OPEN_RSLT_ENUM_BUTT                    = 0x001C,

    NAS_ERR_LOG_HSD_1X_NO_ASSN_FREQ,

    NAS_ERR_LOG_HSD_1X_NO_ASSN_WITH_HRPD,

    NAS_ERR_LOG_HSD_RCV_CAS_OHM_IND_IDLE,

    NAS_ERR_LOG_HSD_BG_SRCH_HRPD_SYS_NOT_AVAILABLE,

    NAS_ERR_LOG_HRPD_OOS_END_BUTT

};
typedef VOS_UINT32 NAS_ERR_LOG_HRPD_OOS_CAUSE_ENUM_UINT32;
/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_OOS_SEARCH_ENUM
 �ṹ˵��  : 1x�������

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
enum  NAS_ERR_LOG_1X_OOS_SEARCH_ENUM
{
    NAS_ERR_LOG_1X_SEARCH_RSLT_SUCCESS,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_SRV_ACQ,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_CALL_REDIAL,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_MO_CALL_END,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_POWER_SAVE,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_POWER_OFF,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_END_EMC_CALLBACK,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_CALLBACK_SRCH_TIMEOUT,
    NAS_ERR_LOG_1X_SEARCH_RSLT_ABORTED_BY_CALLBACK_MODE_TIMEOUT,
    NAS_ERR_LOG_1X_SEARCH_RSLT_FAILURE,
    NAS_ERR_LOG_1X_SEARCH_RSLT_NO_RF,
    NAS_ERR_LOG_1X_SEARCH_RSLT_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_1X_SEARCH_RSLT_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_OOS_SEARCH_ENUM
 �ṹ˵��  : HRPD�������

  1.��    ��   : 2016��02��24��
    ��    ��   : d00212987
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
enum  NAS_ERR_LOG_HRPD_OOS_SEARCH_ENUM
{
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_SUCCESS,
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_FAILURE,
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_ABORTED,
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_NO_RF,
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_REDIRECTION,

    NAS_ERR_LOG_HRPD_SEARCH_RSLT_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_HRPD_SEARCH_RSLT_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ENUM
 �ṹ˵��  : �����쳣ԭ��ö��

  1.��    ��   : 2016��03��03��
    ��    ��   : c00299063
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
enum  NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ENUM
{
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_SUCCESS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_LOCK,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_NO_SERVICE,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_INTERCEPT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_REORDER,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_NORMAL_RELEASE,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_SO_REJ,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_MAX_ACCESS_PROBES,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ACCESS_IN_PROGRESS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ACC_FAIL,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_NOT_ACCEPT_BY_BS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ACCT_BLOCK,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_SIGNAL_FADE,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_CHANNEL_ASSIGN_TIMEROUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_RELEASE_TIMEOUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_RETRY_FAIL,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_NO_RF,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MT_VOICE,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MO_VOICE,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MO_CSMS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MT_CSMS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MO_AGPS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MT_AGPS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MO_CDATA,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_EXIST_MT_CDATA,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_DATA_SWITCHED,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_INCOMING_RSP_FAIL,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_INCOMING_RSP_TIME_OUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_WAIT_AS_EST_CNF_TIME_OUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_WAIT_AS_CALL_INIT_IND_TIME_OUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_WAIT_FOR_ORDER_TIME_OUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_WAIT_WAIT_FOR_ANSWER_TIME_OUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_WAIT_WAIT_CONN_L2_ACK_TIME_OUT,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ACCESS_DENYIED,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_NDSS,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_SIGNAL_FADE_IN_TCH,
    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ABORT,

    NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_MT_SERVICE_TYPE_ENUM
 �ṹ˵��  :  1x��������

  1.��    ��   : 2016��03��03��
    ��    ��   : c00299063
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
enum NAS_ERR_LOG_1X_MT_SERVICE_TYPE_ENUM
{
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE,
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_VOICE_CALL,   /* �������� */
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_DATA_CALL,    /* ���ݺ��� */
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_SMS,          /* ����Ϣ */
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_AGPS_CALL,    /* AGPS */

    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_1X_SERVICE_TYPE_ENUM_UINT32;



/*****************************************************************************
 ö����    : NAS_ERR_LOG_XREG_FAIL_REASON_ENUM
 ö��˵��  : Xreg Errlog��ǰע�����ԭ������ö��
*****************************************************************************/
enum NAS_ERR_LOG_XREG_FAIL_REASON_ENUM
{
    NAS_ERR_LOG_XREG_EST_RSLT_SUCCESS                            = 0x00, /**< SUCCESS */
    NAS_ERR_LOG_XREG_EST_RSLT_NO_SERVICE                         = 0x01, /**< No Service,Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_MAX_ACCESS_PROBES                  = 0x02, /**< Max Access Probes, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_REORDER                            = 0x03, /**< Reorder Order, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_INTERCEPT                          = 0x04, /**< Intercept Order, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_ACCESS_DENYIED                     = 0x05, /**< Access Denied, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_LOCK                               = 0x06, /**< Lock until power cycle order, Call not Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_ACCT_BLOCK                         = 0x07, /**< Acct Block, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_NDSS                               = 0x08, /**< Access Control based on Call Type, redial */
    NAS_ERR_LOG_XREG_EST_RSLT_REDIRECTION                        = 0x09, /**< Redirection, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_NOT_ACCEPT_BY_BS                   = 0x0A, /**< BS Reject, used in Register process */
    NAS_ERR_LOG_XREG_EST_RSLT_ACCESS_IN_PROGRESS                 = 0x0B, /**< Access In Progress, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_ACCESS_FAIL                        = 0x0C, /**< Access fail, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_ABORT                              = 0x0D, /**< State can not Process Call, Call Redial */
    NAS_ERR_LOG_XREG_EST_RSLT_RETRY_FAIL                         = 0x0E,
    NAS_ERR_LOG_XREG_EST_RSLT_NO_RF                              = 0x0F,
    NAS_ERR_LOG_XREG_EST_RSLT_SIGNAL_FADE_IN_ACH                 = 0x10, /**< Signal fade in access (T40m) */
    NAS_ERR_LOG_XREG_EST_RSLT_SIGNAL_FADE_IN_TCH                 = 0x11,

    NAS_ERR_LOG_XREG_EST_RSLT_BUTT                               = 0x12,

    NAS_ERR_LOG_XREG_WAIT_EST_RSLT_TIMEOUT                       = 0x13,
    NAS_ERR_LOG_XREG_WAIT_XREG_ABORT_IND                         = 0x14,
    NAS_ERR_LOG_XREG_WAIT_XREG_ABORT_IND_TIMEOUT                 = 0x15,
    NAS_ERR_LOG_XREG_POWER_OFF_WAIT_EST_CNF_TIMEOUT              = 0x17,
    NAS_ERR_LOG_XREG_ACCESS_IND_FAIL                             = 0x18,

    NAS_ERR_LOG_XREG_XREG_BUTT
};
typedef VOS_UINT8 NAS_ERR_LOG_XREG_FAIL_REASON_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_XREG_FAIL_REASON_ENUM
 ö��˵��  : Xreg Errlog��ǰע������ö��
*****************************************************************************/
enum NAS_ERR_LOG_XREG_REGISTRATION_TYPE_ENUM
{
    NAS_ERR_LOG_XREG_TIMER_BASED_REGISTRATION                    = 0x00,
    NAS_ERR_LOG_XREG_POWER_UP_REGISTRATION                       = 0x01,
    NAS_ERR_LOG_XREG_ZONE_BASED_REGISTRATION                     = 0x02,
    NAS_ERR_LOG_XREG_POWER_DOWN_REGISTRATION                     = 0x03,
    NAS_ERR_LOG_XREG_PARAMETER_CHANGED_REGISTRATION              = 0x04,
    NAS_ERR_LOG_XREG_ORDERED_REGISTRATION                        = 0x05,
    NAS_ERR_LOG_XREG_DISTANCE_BASED_REGISTRATION                 = 0x06,
    NAS_ERR_LOG_XREG_USER_ZONE_BASED_REGISTRATION                = 0x07,
    NAS_ERR_LOG_XREG_ENCRYPTION_RE_SYNC_REQUIRED_REGISTRATION    = 0x08,

    NAS_ERR_LOG_XREG_REGISTRATION_TYPE_BUTT                      = 0x09,

    NAS_ERR_LOG_XREG_ACCESS_ORIG                                 = 0x0A,
    NAS_ERR_LOG_XREG_ACCESS_PAGING_RSP                           = 0x0B,
    NAS_ERR_LOG_XREG_ACCESS_REG                                  = 0x0C,
    NAS_ERR_LOG_XREG_ACCESS_OTHER_MSG                            = 0x0D,

    NAS_ERR_LOG_XREG_ACCESS_BUTT                                 = 0x0E,

};
typedef VOS_UINT8 NAS_ERR_LOG_XREG_REGISTRATION_TYPE_ENUM_UINT8;

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_ERR_LOG_XSMS_ALM_TYPE_ENUM
 ö��˵��  : Xsms Errlog��������ö��
*****************************************************************************/
enum NAS_ERR_LOG_XSMS_ALM_TYPE_ENUM
{
    NAS_ERR_LOG_XSMS_ALM_TYPE_SND_FAIL,
    NAS_ERR_LOG_XSMS_ALM_TYPE_RCV_FAIL,  /* ���մ��󣬱���Ϊ�յ�������ͬ�Ķ��� */

    NAS_ERR_LOG_XSMS_ALM_TYPE_BUTT
};

/*****************************************************************************
 ö����    : NAS_XSMS_SND_FAIL_REASON_ENUM
 ö��˵��  : Xsms Errlog���Ͷ��Ŵ���ԭ������ö��
*****************************************************************************/
enum NAS_ERR_LOG_XSMS_FAIL_REASON_ENUM
{
    NAS_ERR_LOG_XSMS_FAIL_REASON_ENCODE_ERR,
    NAS_ERR_LOG_XSMS_FAIL_REASON_LONG_TIME_NO_SERVICE,
    NAS_ERR_LOG_XSMS_FAIL_REASON_XCC_CNF_FAIL,
    NAS_ERR_LOG_XSMS_FAIL_REASON_XCC_CNF_TIME_OUT,
    NAS_ERR_LOG_XSMS_FAIL_REASON_SO_IND_TIME_OUT,
    NAS_ERR_LOG_XSMS_FAIL_REASON_MO_TIME_OUT,
    NAS_ERR_LOG_XSMS_FAIL_REASON_MO_WAIT_LINK_ABORT,
    NAS_ERR_LOG_XSMS_FAIL_REASON_WRONG_SO_IND,
    NAS_ERR_LOG_XSMS_FAIL_REASON_WRONG_CAS_DATA_CNF,
    NAS_ERR_LOG_XSMS_FAIL_REASON_CAS_DATA_CNF_TIME_OUT,
    NAS_ERR_LOG_XSMS_FAIL_REASON_WRONG_TL_ACK,
    NAS_ERR_LOG_XSMS_FAIL_REASON_TL_ACK_TIME_OUT,

    NAS_ERR_LOG_XSMS_FAIL_REASON_BUTT
};

typedef VOS_UINT8 NAS_ERR_LOG_XSMS_FAIL_REASON_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_XSMS_RCV_FAIL_REASON_ENUM
 ö��˵��  : Xsms Errlog���ն��Ŵ���ԭ������ö��
*****************************************************************************/
enum NAS_XSMS_RCV_FAIL_REASON_ENUM
{
    NAS_XSMS_RCV_FAIL_REASON_DECODE_ERR,
    NAS_XSMS_RCV_FAIL_REASON_LONG_TIME_NO_SERVICE,
    NAS_XSMS_RCV_FAIL_REASON_XCC_CNF_FAIL,
    NAS_XSMS_RCV_FAIL_REASON_WRONG_CAS_DATA_CNF,
    NAS_XSMS_RCV_FAIL_REASON_CAS_DATA_CNF_TIME_OUT,

    NAS_XSMS_RCV_FAIL_REASON_BUTT
};

typedef VOS_UINT8 NAS_XSMS_RCV_FAIL_REASON_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_XSMS_NO_TL_ACK_REASON_ENUM
 ö��˵��  : Xsms Errlog NO TL ACK����ԭ������ö��
*****************************************************************************/
enum NAS_XSMS_NO_TL_ACK_REASON_ENUM
{
    NAS_XSMS_NO_TL_ACK_REASON_CAS_LINK_ABORT,
    NAS_XSMS_NO_TL_ACK_REASON_CAS_HAND_OFF,
    NAS_XSMS_NO_TL_ACK_REASON_SMS_RCV,

    NAS_XSMS_NO_TL_ACK_REASON_BUTT
};

typedef VOS_UINT8 NAS_XSMS_NO_TL_ACK_REASON_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_ENUM
 ö��˵��  : Xsms Errlog NO TL ACK����ԭ������ö��
*****************************************************************************/
enum NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_ENUM
{
    NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_CAS_LINK_ABORT,
    NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_CAS_HAND_OFF,
    NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_SMS_RCV,

    NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_BUTT
};

typedef VOS_UINT8 NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_ERR_LOG_HRPD_UATI_ASSIGN_RSLT_ENUM
 ö��˵��  : uati���������У�ÿ��uati�ط�����
*****************************************************************************/
enum NAS_ERR_LOG_HRPD_UATI_ASSIGN_RSLT_ENUM
{
    NAS_ERR_LOG_HRPD_UATI_FAIL_HRM_HSM_DATA_CNF_RSLT_SUCC,
    NAS_ERR_LOG_HRPD_UATI_FAIL_HRM_HSM_DATA_CNF_RSLT_FAIL,
    NAS_ERR_LOG_HRPD_UATI_FAIL_HRM_HSM_DATA_CNF_RSLT_NO_RF,
    NAS_ERR_LOG_HRPD_UATI_FAIL_WAIT_HRM_SNP_DATA_CNF_TIMER_EXPIRE,
    NAS_ERR_LOG_HRPD_UATI_FAIL_WAIT_UATI_ASSIGN_TIMER_EXPIRE,

    NAS_ERR_LOG_HRPD_UATI_FAIL_REASON_BUTT
};

typedef VOS_UINT32 NAS_ERR_LOG_HRPD_UATI_ASSIGN_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM
 ö��˵��  : CLģʽ�£�LTE��HRPD�����������ָ��ϱ�CHR����
 *****************************************************************************/
enum NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM
{
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_HRPD_OOS,
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_HRPD_OOS_RECOVERY,
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_LTE_OOS,
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_LTE_OOS_RECOVERY,
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_POWER_ON,

    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_BUTT
};
typedef VOS_UINT8 NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_PDN_INFO_DIFFER_ENUM
 ö��˵��  : ������ͨ�����û�����ʧ�ܵ�����
*****************************************************************************/
enum NAS_ERR_LOG_PDN_INFO_DIFFER_ENUM
{
    NAS_ERR_LOG_PDN_INFO_NORMAL,
    NAS_ERR_LOG_PDN_INFO_APS_LESS_THAN_ESM,
    NAS_ERR_LOG_PDN_INFO_ESM_LESS_THAN_APS,
    NAS_ERR_LOG_PDN_INFO_APS_LESS_THAN_EHSM,
    NAS_ERR_LOG_PDN_INFO_EHSM_LESS_THAN_APS,
    NAS_ERR_LOG_PDN_INFO_DIFFER_BUTT
};

typedef VOS_UINT32 NAS_ERR_LOG_PDN_INFO_DIFFER_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_COMMON_INFO_STRU
 �ṹ˵��  : 1x������Ϣ�ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBaseId;
    VOS_UINT8                           aucReserve[2];
    VOS_INT32                           lLatitude;
    VOS_INT32                           lLongitude;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usFreq;
}NAS_ERR_LOG_1X_COMMON_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_COMMON_INFO_STRU
 �ṹ˵��  : Hrpd������Ϣ�ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT8                           ucColorCode;
    VOS_UINT8                           ucSubnetMask;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucSectorId[NAS_ERR_LOG_HRPD_SECTORID_LENGTH];
    VOS_UINT32                          ulSector24;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usFreq;
}NAS_ERR_LOG_HRPD_COMMON_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CL_LTE_COMMON_INFO_STRU
 �ṹ˵��  : CLģʽ�£�LTE������Ϣ�ṹ��

  1.��    ��   : 2016��04��15��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    MNTN_PLMN_ID_STRU                   stPlmn;          /* LTE��ǰ������PLMN */
    VOS_UINT16                          usLac;
    VOS_UINT16                          usRac;
    VOS_UINT32                          ulLteArfcn;      /* LTEפ��Ƶ����Ϣ */
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucRssiValue;     /* LTE�ź�ǿ�� */
    VOS_UINT8                           aucReserved[3];  /* ������ */
}NAS_ERR_LOG_CL_LTE_COMMON_INFO_STRU;
/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_OOS_REPORT_STRU
 �ṹ˵��  : 1x���������ϱ��ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_ERR_LOG_1X_OOS_CAUSE_ENUM_UINT32                    enOosCause;
}NAS_ERR_LOG_1X_OOS_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_OOS_RECOVERY_STRU
 �ṹ˵��  : 1x�����ָ������ϱ��ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT8                                               ucAlreadyReportOosToApFlag; /*���ֶ����ϱ��Ƿ��û�����֪������֪ΪTRUE�����ӳ��ϱ���ʱ����ʱ��δ�ѵ���*/
    VOS_UINT8                                               aucReserve[3];
}NAS_ERR_LOG_1X_OOS_RECOVERY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_OOS_SEARCH_RECORD_STRU
 �ṹ˵��  : 1x����������¼�ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    NAS_ERR_LOG_1X_SEARCH_RSLT_ENUM_UINT32                  enSearchRslt;
} NAS_ERR_LOG_1X_OOS_SEARCH_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_OOS_SEARCH_STRU
 �ṹ˵��  : 1x������¼�ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulSearchRecordCnt;
    NAS_ERR_LOG_1X_OOS_SEARCH_RECORD_STRU                   astSearchRecord[NAS_ERR_LOG_1X_OOS_MAX_SEARCH_RECORD];
}NAS_ERR_LOG_1X_OOS_SEARCH_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_UATI_ASSIGN_FAIL_RECORD_STRU
 �ṹ˵��  : UATI��������У�uati�ط�����Ϣ

  1.��    ��   : 2016��04��07��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulUatiAssignStartTimer;            /* ÿ��Uati�ط���Ŀ�ʼʱ�� */
    VOS_UINT32                                              ulUatiReqRcvSnpDataCnfTimer;       /* �յ�Uati Req��SnpDataCnf�ҽ��ΪSuccess��ʱ�� */
    VOS_UINT32                                              ulUatiAssignEndTimer;              /* ÿ��Uati�ط���Ľ���ʱ�� */
    NAS_ERR_LOG_HRPD_UATI_ASSIGN_RSLT_ENUM_UINT32           enUatiAssignRslt;                  /* ÿ��Uati�ط����ʧ��ԭ�� */
} NAS_ERR_LOG_HRPD_UATI_ASSIGN_FAIL_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_UATI_FAIL_STRU
 �ṹ˵��  : UATI����ʧ����Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulUatiStartTimer;            /* ����UATI����Ŀ�ʼʱ�� */
    VOS_UINT32                                              ulUatiEndTimer;              /* UATI�˳�״̬��������chr�¼���ʱ�� */
    VOS_UINT8                                               ucUATITriggerCause;          /* ����UATI��ԭ�� */
    VOS_UINT8                                               ucUATIFailCause;             /* UATIʧ�ܵ�ԭ�� */
    VOS_UINT8                                               ucRecordCnt;
    VOS_UINT8                                               ucReserved;
    VOS_UINT32                                              ulMainState;                 /* Hsm��״̬ */
    VOS_UINT32                                              ulSubState;                  /* Hsm��״̬ */
    NAS_ERR_LOG_HRPD_UATI_ASSIGN_FAIL_RECORD_STRU           astUatiAssignFailRecord[NAS_ERR_LOG_HRPD_UATI_ASSIGN_MAX_CNT];  /* Utai��������У��ط�����Ϣ */
}NAS_ERR_LOG_HRPD_UATI_FAIL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_SESSION_FAIL_STRU
 �ṹ˵��  : Session����ʧ����Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT8                           ucSessionActReason;     /* ����Session�����ԭ�� */
    VOS_UINT8                           ucSessionActType;       /* Session��������ͣ�����recovery��init��restore prio */
    VOS_UINT8                           ucSupportEhrpdFlg;      /* �Ƿ�֧��eHRPD */
    VOS_UINT8                           ucSessionFailCause;     /* Sessionʧ�ܵ�ԭ�� */
    VOS_UINT32                          ulStartTimer;
    VOS_UINT32                          ulEndTimer;
}NAS_ERR_LOG_HRPD_SESSION_FAIL_STRU;


/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_SESSION_EXCEP_DEACT_STRU
 �ṹ˵��  : Session�쳣ȥ������Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulTimer;
    NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_ENUM_UINT32       enSessionDeactCause;     /* ����������������Session close��keep alive��ʱ��������ʧ�� */
    VOS_UINT32                                              ulMainState;                 /* Hsm��״̬ */
    VOS_UINT32                                              ulSubState;                  /* Hsm��״̬ */
    VOS_UINT8                                               ucByAnSessionCloseReason;    /* ���������ر�Session��ԭ��ֻ��enSessionDeactCause����NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_BY_ANʱ��Ч */
    VOS_UINT8                                               ucByAnSessionCloseScene;     /* ���������ر�Session�ĳ��� */
    VOS_UINT8                                               aucReserve[2];
} NAS_ERR_LOG_HRPD_SESSION_EXCEP_DEACT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_OR_LTE_OOS_REPORT_STRU
 �ṹ˵��  : CLģʽ��HRPD��LTE���������ϱ��ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : d00212987
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM_UINT8     enPsReportChrState;
    VOS_UINT8                                               aucReserve[3];
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32                       enLteOosCause;
    NAS_ERR_LOG_HRPD_OOS_CAUSE_ENUM_UINT32                  enHrpdOosCause;
}NAS_ERR_LOG_HRPD_OR_LTE_OOS_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_OOS_RECOVERY_STRU
 �ṹ˵��  : Hrpd�����ָ������ϱ��ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : d00212987
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM_UINT8     enHrpdOrLteReportChrState;
    VOS_UINT8                                               ucAlreadyReportOosToApFlag; /*���ֶ����ϱ��Ƿ��û�����֪������֪ΪTRUE�����ӳ��ϱ���ʱ����ʱ��δ�ѵ���*/
    VOS_UINT8                                               aucReserve[2];
}NAS_ERR_LOG_HRPD_OR_LTE_OOS_RECOVERY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_OOS_SEARCH_RECORD_STRU
 �ṹ˵��  : Hrpd����������¼�ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : d00212987
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_ENUM_UINT32                enSearchRslt;
} NAS_ERR_LOG_HRPD_OOS_SEARCH_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_HRPD_OOS_SEARCH_STRU
 �ṹ˵��  : Hrpd������¼�ṹ��

  1.��    ��   : 2016��02��24��
    ��    ��   : d00212987
    �޸�����   : CDMA Iteration 20����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulSearchRecordCnt;
    NAS_ERR_LOG_HRPD_OOS_SEARCH_RECORD_STRU                 astSearchRecord[NAS_ERR_LOG_HRPD_OOS_MAX_SEARCH_RECORD];
}NAS_ERR_LOG_HRPD_OOS_SEARCH_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CL_OOS_SEARCH_RECORD_STRU
 �ṹ˵��  : CL��ģ�������̣�ÿ��������Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    VOS_UINT32                                              ulSearchRat;
    VOS_UINT32                                              ulSearchType;
    NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM_UINT32                  enSearchRslt;
} NAS_ERR_LOG_CL_OOS_SEARCH_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CL_OOS_SEARCH_STRU
 �ṹ˵��  : CL��ģ������Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulIsHrpdAndLteBothSupport; /* ��ǰϵͳ�Ƿ�ͬʱ֧��HRPD��LTE, TRUE��֧�֣�FALSE����֧�� */
    VOS_UINT32                                              ulSearchRecordCnt;
    NAS_ERR_LOG_CL_OOS_SEARCH_RECORD_STRU                   astSearchRecord[NAS_ERR_LOG_CL_OOS_MAX_SEARCH_RECORD_NUM];
} NAS_ERR_LOG_CL_OOS_SEARCH_STRU;


typedef struct
{
    VOS_UINT32                          ulTime;
    VOS_UINT32                          enFsmId;                                /* Stores the ID of the current FSM */
    VOS_UINT32                          ulState;                                /* Stores the current state of the FSM */
    VOS_UINT32                          ulParentEventType;                      /* Stores the Event type of the parent FSM */
    VOS_UINT32                          enEhrpdState;                           /* Stores the State of the Ehrpd */

    VOS_UINT8                           enErrorCode;                            /* Recodes the option for Lte Pdn info */
    VOS_UINT8                           enEhrpdWorkMode;
    VOS_UINT8                           ucLteAttachFlag;                        /* Stores the attach flag for Lte Pdn info */
    VOS_UINT8                           ucLteOption;                            /* Stores the option for Lte Pdn info */
    VOS_UINT32                          ulBitCid;
    VOS_UINT32                          ulEpsbId;

}NAS_ERR_LOG_EHSM_ERROR_INFO_STRU;


typedef struct
{
    NAS_ERR_LOG_PDN_INFO_DIFFER_ENUM_UINT32                 enCause;            /* �Ƿ����PDN��Ϣ��һ�� */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32                enRatType;          /* ��ǰ�Ľ��뼼��ģʽ */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32                enPsSerMode;        /* ��ǰ��PS�����ģʽ */
    VOS_UINT32                                              ulAttachAllowFlg;   /* ��ǰ��ps���attach allow flag */
}NAS_ERR_LOG_PS_PDN_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU
 �ṹ˵��  : PS���й����У��ز���Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32                enRatMode;       /* �����ز������ϵͳģʽ������1x,HRPD,eHRPD */
    VOS_UINT32                                              ulRedialRslt;    /* ��������enPsCauseȡֵ����,TAF_PS_CAUSE_ENUM_UINT32 */
} NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CDMA_PS_CALL_EXCEPTION_STRU
 �ṹ˵��  : PS����ʧ���쳣��Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulPsCause;     /* ���һ��ʧ��ԭ��,TAF_PS_CAUSE_ENUM_UINT32 */
    NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU                stApsFsmInfo;  /* ״̬����Ϣ */
    VOS_UINT32                                              ulRedialCnt;
    NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU               astRedialInfo[NAS_ERR_LOG_MAX_CDMA_PS_CALL_EXCEP_REDIAL_NUM];
    VOS_UINT32                                              ulEhsmErrCnt;               /* EHSM�б����ERROR��¼���� */
    NAS_ERR_LOG_EHSM_ERROR_INFO_STRU                        astEhsmErrInfo[NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM];    /* EHSM�쳣��Ϣ */
    NAS_ERR_LOG_PS_PDN_ERROR_INFO_STRU                      stPndInfoDiffer;
}NAS_ERR_LOG_CDMA_PS_CALL_EXCEPTION_STRU;


/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CDMA_PS_DISC_RECORD_STRU
 �ṹ˵��  : PS�쳣���������е�һ���쳣��Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulPsCause;     /* ���һ��ʧ��ԭ�� */
    NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU                stApsFsmInfo;  /* ״̬����Ϣ */
    VOS_UINT32                                              ulRedialCnt;
    NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU               astRedialInfo[NAS_ERR_LOG_MAX_CDMA_PS_CALL_EXCEP_REDIAL_NUM];
}NAS_ERR_LOG_CDMA_PS_DISC_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_CDMA_PS_DISC_INFO_STRU
 �ṹ˵��  : PS�쳣�������ؽ���Ϣ

  1.��    ��   : 2016��02��24��
    ��    ��   : l00324781
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulCdmaPsDiscRecdCnt;         /* PS�����󣬷��������ؽ�ʧ�ܴ��� */
    NAS_ERR_LOG_CDMA_PS_DISC_RECORD_STRU                    astErrLogCdmaPsDiscRecd[NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM];    /* PS�����쳣��Ϣ */
    VOS_UINT32                                              ulEhsmErrCnt;               /* EHSM�б����ERROR��¼���� */
    NAS_ERR_LOG_EHSM_ERROR_INFO_STRU                        astEhsmErrInfo[NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM];    /* EHSM�쳣��Ϣ */
    NAS_ERR_LOG_PS_PDN_ERROR_INFO_STRU                      stPndInfoDiffer;
}NAS_ERR_LOG_CDMA_PS_DISC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_CS_CALL_REDIAL_INFO_STRU
 �ṹ˵��  : ����ʧ�ܵ��ز��쳣��Ϣ
 1.��    ��   : 2016��02��24��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIndex;         /* �ṹ����������*/
    VOS_UINT32                          ulStartTimer;    /* ���ν�����ʼʱ��*/
    VOS_UINT32                          ulEndTimer;      /* ���ν�������ʱ��*/
    VOS_UINT32                          ulRedialRslt;    /* ʧ��ԭ��ֵ */
} NAS_ERR_LOG_1X_CS_CALL_REDIAL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_CS_CALL_EXCEPTION_STRU
 �ṹ˵��  : ���С��Ựʧ�ܵ��쳣��Ϣ
 1.��    ��   : 2016��02��24��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulCcCause;           /* �������һ��ʧ��ԭ��ֵ */
    VOS_UINT32                                              ulRedialCnt;         /* �ز�����*/
    NAS_ERR_LOG_1X_CS_CALL_REDIAL_INFO_STRU                 astRedialInfo[NAS_ERR_LOG_1X_CS_CALL_MAX_REDIAL_NUM];
}NAS_ERR_LOG_1X_CS_CALL_EXCEPTION_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_STRU
 �ṹ˵��  : ����ʧ�ܵ��쳣��Ϣ
 1.��    ��   : 2016��02��24��
   ��    ��   : c00299063
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU               stHeader;
    VOS_UINT32                           ulCcCause;      /* �����е�ԭ��ֵ����չ */
    VOS_UINT32                           ulPagingTimer;  /* ���յ�Paging��Ϣ��ʱ�� */
    VOS_UINT32                           ulPagingType;   /* ����ҵ�����ͣ��������������ź�����*/
    VOS_UINT32                           ulXccState;     /* ����쳣������XCCģ��ı���״̬���У�����XCC��ǰ����״̬*/
}NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_STRU;


/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_XREG_CTX_STRU
 �ṹ˵��  : xreg����ȫ�ֱ����е�ʧ����Ϣ
 1.��    ��   : 2016��01��25��
   ��    ��   : d00212987
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_XREG_REGISTRATION_TYPE_ENUM_UINT8           enRegType;              /* ��ǰע������ */
    NAS_ERR_LOG_XREG_FAIL_REASON_ENUM_UINT8                 enRegFailReason;        /* ע��ʧ��ԭ��ֵ */
    VOS_UINT8                                               ucRsv[2];
}NAS_ERR_LOG_XREG_CTX_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_REG_RESULT_EVENT_STRU
 �ṹ˵��  : xreg����ȫ�ֱ����е�ʧ����Ϣ
 1.��    ��   : 2016��01��25��
   ��    ��   : d00212987
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;
    NAS_ERR_LOG_XREG_CTX_STRU                           stXregErrLogCtx;
}NAS_ERR_LOG_XREG_RESULT_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_XSMS_SND_CTX_STRU
 �ṹ˵��  : MO���ŷ��͹����е�״̬�ṹ��
 1.��    ��   : 2016��01��25��
   ��    ��   : c00299064
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      enFailState;            /* ���������ʱ���״̬��״̬ ֵ�ο�:TAF_XSMS_MO_FSM_ID_ENUM_UINT32 */
    VOS_UINT32                                      enLastXccCnfRslt;       /* ���һ�ε�XCC RESULT ֵ�ο�:TAF_XCC_CAUSE_ENUM_UINT32*/
    VOS_UINT8                                       enLastCasCnfRslt;       /* ���һ�ε�CAS RESULT ֵ�ο�:CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8  */
    VOS_UINT8                                       enLastTlAckCauseCode;   /* �յ�TL_ACK �����CAUSE CODE��û�д���дBUTTֵ��ֵ�ο�:TAF_XSMS_TL_CAUSE_CODE_ENUM8*/
    NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_ENUM_UINT8    enNoTlAckReason;        /* û���յ�TL_ACK�� ����ԭ�� */
    NAS_ERR_LOG_XSMS_FAIL_REASON_ENUM_UINT8         enSndFailReason;        /* ����ʧ��ԭ�� */
    VOS_UINT32                                      ulReSendTime;

}NAS_ERR_LOG_XSMS_SND_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_SND_FAIL_INFO_STRU
 �ṹ˵��  : MO���Ŵ���ȫ�ֱ����е�ʧ����Ϣ
 1.��    ��   : 2016��01��25��
   ��    ��   : c00299064
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_ERR_LOG_XSMS_SND_CTX_STRU           stXsmsSndCtx;
}NAS_ERR_LOG_XSMS_SND_FAIL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_XSMS_RCV_CTX_STRU
 �ṹ˵��  : MT���Ŵ���ȫ�ֱ����е�ʧ����Ϣ
 1.��    ��   : 2016��01��25��
   ��    ��   : d00212987
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_XSMS_FAIL_REASON_ENUM_UINT8         enFailReason;         /* MTʧ��ԭ��ֵ */
    VOS_UINT8                                       ucReRcvTime;          /* MTʧ�ܴ��� */
    VOS_UINT8                                       enLastCasCnfRslt;     /* ֵ�ο�:CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8  */
    VOS_UINT8                                       ucRcv;
}NAS_ERR_LOG_XSMS_RCV_CTX_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_XSMS_RCV_FAIL_INFO_STRU
 �ṹ˵��  : MT���Ŵ���ȫ�ֱ����е�ʧ����Ϣ
 1.��    ��   : 2016��01��25��
   ��    ��   : d00212987
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_ERR_LOG_XSMS_RCV_CTX_STRU           stXsmsRcvCtx;
}NAS_ERR_LOG_XSMS_RCV_FAIL_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasErrorLoCdmag.h */


