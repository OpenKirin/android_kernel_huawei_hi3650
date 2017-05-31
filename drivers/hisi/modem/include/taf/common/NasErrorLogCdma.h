

#ifndef __NAS_ERRORLOGCDMA_H__
#define __NAS_ERRORLOGCDMA_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "NasErrorLogComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_ERR_LOG_HRPD_SECTORID_LENGTH                (16)

#define NAS_ERR_LOG_CL_OOS_MAX_SEARCH_RECORD_NUM        (20)   /* CL多模搜网过程中，记录的搜网信息最大轮数 */
#define NAS_ERR_LOG_MAX_CDMA_PS_CALL_EXCEP_REDIAL_NUM   (10)   /* CDMA PS呼叫过程中记录的重拨信息最大条数 */
#define NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM         (10)   /* CDMA PS异常断链过程中，记录的异常信息最大条数  */

#define NAS_ERR_LOG_1X_CS_CALL_MAX_REDIAL_NUM           (10)

#define NAS_ERR_LOG_1X_OOS_MAX_SEARCH_RECORD             (20)
#define NAS_ERR_LOG_HRPD_OOS_MAX_SEARCH_RECORD           (20)

#define NAS_ERR_LOG_HRPD_UATI_ASSIGN_MAX_CNT      (5)   /* uati分配流程中，uati重分配最多次数，和 CNAS_HSM_UAIT_REQ_FAILED_MAX_CNT 保持一致 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
 枚举名    : NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_ENUM
 枚举说明  : Session异常去激活原因
  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 新建
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
 枚举名    : NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM
 结构说明  :  CL多模搜网，每轮搜网结果
 1.日    期   : 2016年2月24日
   作    者   : l00324781
   修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM
{
    /* HRPD驻留结果 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_SUCC       = 0x0000,     /* HRPD搜网成功 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_FAIL       = 0x0001,     /* HRPD搜网失败 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_ABORTED    = 0x0002,     /* HRPD搜网被打断 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_NO_RF      = 0x0003,     /* HRPD无资源 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_REG_NO_RF  = 0x0004,     /* 搜网成功，注册结果为No_Rf */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_TIMEOUT    = 0x0005,     /* 等待HSD搜网结果超时 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_HRPD_MSCC_ABORT = 0x0006,     /* HRPD搜网在MSCC被打断 */

    /*  LTE驻留结果  */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_NORMAL_SRV  = 0x1000,     /* LTE搜网成功 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_LIMITED_SRV = 0x1001,     /* LTE搜网失败 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_NO_SRV      = 0x1002,     /* LTE搜网失败 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_INTERUPT    = 0x1003,     /* LTE搜网被打断 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_NO_RF       = 0x1004,     /* LTE无资源 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_L2C         = 0x1005,     /* LTE重选到HRPD*/
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_TIMEOUT     = 0x1006,     /* MSCC等待MCC搜网结果超时*/
    NAS_ERR_LOG_CL_SEARCH_RSLT_LTE_MSCC_ABORT  = 0x1007,     /* LTE搜网在MSCC被打断 */
    NAS_ERR_LOG_CL_SEARCH_RSLT_BUTT            = 0xffff
};
typedef VOS_UINT32  NAS_ERR_LOG_CL_SEARCH_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_APS_RAT_TYPE_ENUM
 结构说明  :  PS呼叫中链接的接入技术
 1.日    期   : 2016年2月24日
   作    者   : l00324781
   修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_APS_RAT_TYPE_ENUM
{
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_NULL,          /* 当前未在任何网络上驻留 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_GSM,           /* GSM接入技术 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_WCDMA,         /* WCDMA接入技术 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_LTE,           /* LTE接入技术 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_1X,            /* CDMA-1X接入技术 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_HRPD,          /* CDMA-HRPD接入技术 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_EHRPD,         /* CDMA-EHRPD接入技术 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_BUTT           /* 无效的接入技术 */
};
typedef VOS_UINT32 NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_OOS_CAUSE_ENUM
 结构说明  : 1x丢网原因值

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
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
    NAS_ERR_LOG_1X_OOS_CAUSE_POWER_ON,                   /* CL模式下，开机成功，一段时间处于无网状态，立即上报一次1x oss，携带该原因值 */
    NAS_ERR_LOG_1X_OOS_CAUSE_OTHER,
    NAS_ERR_LOG_1X_OOS_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_1X_OOS_CAUSE_ENUM_UINT32;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_OOS_CAUSE_ENUM
 结构说明  : Hrpd丢网原因值

  1.日    期   : 2016年02月24日
    作    者   : d0212987
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_1X_OOS_SEARCH_ENUM
 结构说明  : 1x搜网结果

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_HRPD_OOS_SEARCH_ENUM
 结构说明  : HRPD搜网结果

  1.日    期   : 2016年02月24日
    作    者   : d00212987
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_CAUSE_ENUM
 结构说明  : 被叫异常原因枚举

  1.日    期   : 2016年03月03日
    作    者   : c00299063
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_1X_MT_SERVICE_TYPE_ENUM
 结构说明  :  1x服务类型

  1.日    期   : 2016年03月03日
    作    者   : c00299063
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
enum NAS_ERR_LOG_1X_MT_SERVICE_TYPE_ENUM
{
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE,
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_VOICE_CALL,   /* 语音呼叫 */
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_DATA_CALL,    /* 数据呼叫 */
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_SMS,          /* 短消息 */
    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_AGPS_CALL,    /* AGPS */

    NAS_ERR_LOG_1X_MT_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_1X_SERVICE_TYPE_ENUM_UINT32;



/*****************************************************************************
 枚举名    : NAS_ERR_LOG_XREG_FAIL_REASON_ENUM
 枚举说明  : Xreg Errlog当前注册错误原因类型枚举
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
 枚举名    : NAS_ERR_LOG_XREG_FAIL_REASON_ENUM
 枚举说明  : Xreg Errlog当前注册类型枚举
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
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_ERR_LOG_XSMS_ALM_TYPE_ENUM
 枚举说明  : Xsms Errlog错误类型枚举
*****************************************************************************/
enum NAS_ERR_LOG_XSMS_ALM_TYPE_ENUM
{
    NAS_ERR_LOG_XSMS_ALM_TYPE_SND_FAIL,
    NAS_ERR_LOG_XSMS_ALM_TYPE_RCV_FAIL,  /* 接收错误，表现为收到两条相同的短信 */

    NAS_ERR_LOG_XSMS_ALM_TYPE_BUTT
};

/*****************************************************************************
 枚举名    : NAS_XSMS_SND_FAIL_REASON_ENUM
 枚举说明  : Xsms Errlog发送短信错误原因类型枚举
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
 枚举名    : NAS_XSMS_RCV_FAIL_REASON_ENUM
 枚举说明  : Xsms Errlog接收短信错误原因类型枚举
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
 枚举名    : NAS_XSMS_NO_TL_ACK_REASON_ENUM
 枚举说明  : Xsms Errlog NO TL ACK错误原因类型枚举
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
 枚举名    : NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_ENUM
 枚举说明  : Xsms Errlog NO TL ACK错误原因类型枚举
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
 枚举名    : NAS_ERR_LOG_HRPD_UATI_ASSIGN_RSLT_ENUM
 枚举说明  : uati分配流程中，每次uati重分配结果
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
 枚举名    : NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM
 枚举说明  : CL模式下，LTE或HRPD丢网、丢网恢复上报CHR类型
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
 枚举名    : NAS_ERR_LOG_PDN_INFO_DIFFER_ENUM
 枚举说明  : 数传不通或者用户激活失败的类型
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
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_COMMON_INFO_STRU
 结构说明  : 1x公共信息结构体

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_HRPD_COMMON_INFO_STRU
 结构说明  : Hrpd公共信息结构体

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_CL_LTE_COMMON_INFO_STRU
 结构说明  : CL模式下，LTE公共信息结构体

  1.日    期   : 2016年04月15日
    作    者   : l00324781
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    MNTN_PLMN_ID_STRU                   stPlmn;          /* LTE当前主流的PLMN */
    VOS_UINT16                          usLac;
    VOS_UINT16                          usRac;
    VOS_UINT32                          ulLteArfcn;      /* LTE驻留频点信息 */
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucRssiValue;     /* LTE信号强度 */
    VOS_UINT8                           aucReserved[3];  /* 保留域 */
}NAS_ERR_LOG_CL_LTE_COMMON_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_OOS_REPORT_STRU
 结构说明  : 1x丢网主动上报结构体

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_ERR_LOG_1X_OOS_CAUSE_ENUM_UINT32                    enOosCause;
}NAS_ERR_LOG_1X_OOS_REPORT_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_OOS_RECOVERY_STRU
 结构说明  : 1x丢网恢复主动上报结构体

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT8                                               ucAlreadyReportOosToApFlag; /*区分丢网上报是否被用户所感知，被感知为TRUE；即延迟上报定时器超时后还未搜到网*/
    VOS_UINT8                                               aucReserve[3];
}NAS_ERR_LOG_1X_OOS_RECOVERY_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_OOS_SEARCH_RECORD_STRU
 结构说明  : 1x单条搜网记录结构体

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    NAS_ERR_LOG_1X_SEARCH_RSLT_ENUM_UINT32                  enSearchRslt;
} NAS_ERR_LOG_1X_OOS_SEARCH_RECORD_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_OOS_SEARCH_STRU
 结构说明  : 1x搜网记录结构体

  1.日    期   : 2016年02月24日
    作    者   : j00354216
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulSearchRecordCnt;
    NAS_ERR_LOG_1X_OOS_SEARCH_RECORD_STRU                   astSearchRecord[NAS_ERR_LOG_1X_OOS_MAX_SEARCH_RECORD];
}NAS_ERR_LOG_1X_OOS_SEARCH_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_UATI_ASSIGN_FAIL_RECORD_STRU
 结构说明  : UATI分配过程中，uati重分配信息

  1.日    期   : 2016年04月07日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulUatiAssignStartTimer;            /* 每次Uati重分配的开始时间 */
    VOS_UINT32                                              ulUatiReqRcvSnpDataCnfTimer;       /* 收到Uati Req的SnpDataCnf且结果为Success的时间 */
    VOS_UINT32                                              ulUatiAssignEndTimer;              /* 每次Uati重分配的结束时间 */
    NAS_ERR_LOG_HRPD_UATI_ASSIGN_RSLT_ENUM_UINT32           enUatiAssignRslt;                  /* 每次Uati重分配的失败原因 */
} NAS_ERR_LOG_HRPD_UATI_ASSIGN_FAIL_RECORD_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_UATI_FAIL_STRU
 结构说明  : UATI分配失败信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulUatiStartTimer;            /* 发起UATI分配的开始时间 */
    VOS_UINT32                                              ulUatiEndTimer;              /* UATI退出状态机，生成chr事件的时间 */
    VOS_UINT8                                               ucUATITriggerCause;          /* 发起UATI的原因 */
    VOS_UINT8                                               ucUATIFailCause;             /* UATI失败的原因 */
    VOS_UINT8                                               ucRecordCnt;
    VOS_UINT8                                               ucReserved;
    VOS_UINT32                                              ulMainState;                 /* Hsm主状态 */
    VOS_UINT32                                              ulSubState;                  /* Hsm子状态 */
    NAS_ERR_LOG_HRPD_UATI_ASSIGN_FAIL_RECORD_STRU           astUatiAssignFailRecord[NAS_ERR_LOG_HRPD_UATI_ASSIGN_MAX_CNT];  /* Utai分配过程中，重分配信息 */
}NAS_ERR_LOG_HRPD_UATI_FAIL_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_SESSION_FAIL_STRU
 结构说明  : Session激活失败信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT8                           ucSessionActReason;     /* 发起Session激活的原因 */
    VOS_UINT8                           ucSessionActType;       /* Session激活的类型，包含recovery，init，restore prio */
    VOS_UINT8                           ucSupportEhrpdFlg;      /* 是否支持eHRPD */
    VOS_UINT8                           ucSessionFailCause;     /* Session失败的原因 */
    VOS_UINT32                          ulStartTimer;
    VOS_UINT32                          ulEndTimer;
}NAS_ERR_LOG_HRPD_SESSION_FAIL_STRU;


/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_SESSION_EXCEP_DEACT_STRU
 结构说明  : Session异常去激活信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulTimer;
    NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_ENUM_UINT32       enSessionDeactCause;     /* 区分网络主动发送Session close或keep alive超时或重配置失败 */
    VOS_UINT32                                              ulMainState;                 /* Hsm主状态 */
    VOS_UINT32                                              ulSubState;                  /* Hsm子状态 */
    VOS_UINT8                                               ucByAnSessionCloseReason;    /* 网侧主动关闭Session的原因，只在enSessionDeactCause等于NAS_ERR_LOG_SESSION_EXCEP_DEACT_CAUSE_BY_AN时有效 */
    VOS_UINT8                                               ucByAnSessionCloseScene;     /* 网侧主动关闭Session的场景 */
    VOS_UINT8                                               aucReserve[2];
} NAS_ERR_LOG_HRPD_SESSION_EXCEP_DEACT_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_OR_LTE_OOS_REPORT_STRU
 结构说明  : CL模式下HRPD或LTE丢网主动上报结构体

  1.日    期   : 2016年02月24日
    作    者   : d00212987
    修改内容   : CDMA Iteration 20创建
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
 结构名    : NAS_ERR_LOG_HRPD_OOS_RECOVERY_STRU
 结构说明  : Hrpd丢网恢复主动上报结构体

  1.日    期   : 2016年02月24日
    作    者   : d00212987
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_ERR_LOG_HRPD_OR_LTE_REPORT_CHR_STATE_ENUM_UINT8     enHrpdOrLteReportChrState;
    VOS_UINT8                                               ucAlreadyReportOosToApFlag; /*区分丢网上报是否被用户所感知，被感知为TRUE；即延迟上报定时器超时后还未搜到网*/
    VOS_UINT8                                               aucReserve[2];
}NAS_ERR_LOG_HRPD_OR_LTE_OOS_RECOVERY_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_OOS_SEARCH_RECORD_STRU
 结构说明  : Hrpd单条搜网记录结构体

  1.日    期   : 2016年02月24日
    作    者   : d00212987
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    NAS_ERR_LOG_HRPD_SEARCH_RSLT_ENUM_UINT32                enSearchRslt;
} NAS_ERR_LOG_HRPD_OOS_SEARCH_RECORD_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_HRPD_OOS_SEARCH_STRU
 结构说明  : Hrpd搜网记录结构体

  1.日    期   : 2016年02月24日
    作    者   : d00212987
    修改内容   : CDMA Iteration 20创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulSearchRecordCnt;
    NAS_ERR_LOG_HRPD_OOS_SEARCH_RECORD_STRU                 astSearchRecord[NAS_ERR_LOG_HRPD_OOS_MAX_SEARCH_RECORD];
}NAS_ERR_LOG_HRPD_OOS_SEARCH_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_CL_OOS_SEARCH_RECORD_STRU
 结构说明  : CL多模搜网过程，每轮搜网信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
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
 结构名    : NAS_ERR_LOG_CL_OOS_SEARCH_STRU
 结构说明  : CL多模搜网信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulIsHrpdAndLteBothSupport; /* 当前系统是否同时支持HRPD和LTE, TRUE：支持，FALSE：不支持 */
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
    NAS_ERR_LOG_PDN_INFO_DIFFER_ENUM_UINT32                 enCause;            /* 是否存在PDN信息不一致 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32                enRatType;          /* 当前的接入技术模式 */
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32                enPsSerMode;        /* 当前的PS域服务模式 */
    VOS_UINT32                                              ulAttachAllowFlg;   /* 当前的ps域的attach allow flag */
}NAS_ERR_LOG_PS_PDN_ERROR_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU
 结构说明  : PS呼叫过程中，重拨信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulStartTimer;
    VOS_UINT32                                              ulEndTimer;
    NAS_ERR_LOG_PS_CALL_RAT_TYPE_ENUM_UINT32                enRatMode;       /* 本次重拨发起的系统模式，区分1x,HRPD,eHRPD */
    VOS_UINT32                                              ulRedialRslt;    /* 复用下面enPsCause取值类型,TAF_PS_CAUSE_ENUM_UINT32 */
} NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_CDMA_PS_CALL_EXCEPTION_STRU
 结构说明  : PS呼叫失败异常信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulPsCause;     /* 最后一次失败原因,TAF_PS_CAUSE_ENUM_UINT32 */
    NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU                stApsFsmInfo;  /* 状态机信息 */
    VOS_UINT32                                              ulRedialCnt;
    NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU               astRedialInfo[NAS_ERR_LOG_MAX_CDMA_PS_CALL_EXCEP_REDIAL_NUM];
    VOS_UINT32                                              ulEhsmErrCnt;               /* EHSM中保存的ERROR记录个数 */
    NAS_ERR_LOG_EHSM_ERROR_INFO_STRU                        astEhsmErrInfo[NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM];    /* EHSM异常信息 */
    NAS_ERR_LOG_PS_PDN_ERROR_INFO_STRU                      stPndInfoDiffer;
}NAS_ERR_LOG_CDMA_PS_CALL_EXCEPTION_STRU;


/*****************************************************************************
 结构名    : NAS_ERR_LOG_CDMA_PS_DISC_RECORD_STRU
 结构说明  : PS异常断链过程中的一条异常信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulPsCause;     /* 最后一次失败原因 */
    NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU                stApsFsmInfo;  /* 状态机信息 */
    VOS_UINT32                                              ulRedialCnt;
    NAS_ERR_LOG_CDMA_PS_CALL_REDIAL_INFO_STRU               astRedialInfo[NAS_ERR_LOG_MAX_CDMA_PS_CALL_EXCEP_REDIAL_NUM];
}NAS_ERR_LOG_CDMA_PS_DISC_RECORD_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_CDMA_PS_DISC_INFO_STRU
 结构说明  : PS异常断链和重建信息

  1.日    期   : 2016年02月24日
    作    者   : l00324781
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulCdmaPsDiscRecdCnt;         /* PS断链后，发起链接重建失败次数 */
    NAS_ERR_LOG_CDMA_PS_DISC_RECORD_STRU                    astErrLogCdmaPsDiscRecd[NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM];    /* PS断链异常信息 */
    VOS_UINT32                                              ulEhsmErrCnt;               /* EHSM中保存的ERROR记录个数 */
    NAS_ERR_LOG_EHSM_ERROR_INFO_STRU                        astEhsmErrInfo[NAS_ERR_LOG_MAX_CDMA_PS_DISC_RECORD_NUM];    /* EHSM异常信息 */
    NAS_ERR_LOG_PS_PDN_ERROR_INFO_STRU                      stPndInfoDiffer;
}NAS_ERR_LOG_CDMA_PS_DISC_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_CS_CALL_REDIAL_INFO_STRU
 结构说明  : 主叫失败的重拨异常信息
 1.日    期   : 2016年02月24日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIndex;         /* 结构体数组索引*/
    VOS_UINT32                          ulStartTimer;    /* 本次建链开始时间*/
    VOS_UINT32                          ulEndTimer;      /* 本次建链结束时间*/
    VOS_UINT32                          ulRedialRslt;    /* 失败原因值 */
} NAS_ERR_LOG_1X_CS_CALL_REDIAL_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_CS_CALL_EXCEPTION_STRU
 结构说明  : 主叫、会话失败的异常信息
 1.日    期   : 2016年02月24日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    VOS_UINT32                                              ulCcCause;           /* 呼叫最后一次失败原因值 */
    VOS_UINT32                                              ulRedialCnt;         /* 重拨次数*/
    NAS_ERR_LOG_1X_CS_CALL_REDIAL_INFO_STRU                 astRedialInfo[NAS_ERR_LOG_1X_CS_CALL_MAX_REDIAL_NUM];
}NAS_ERR_LOG_1X_CS_CALL_EXCEPTION_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_STRU
 结构说明  : 被叫失败的异常信息
 1.日    期   : 2016年02月24日
   作    者   : c00299063
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU               stHeader;
    VOS_UINT32                           ulCcCause;      /* 在主叫的原因值上扩展 */
    VOS_UINT32                           ulPagingTimer;  /* 接收到Paging消息的时间 */
    VOS_UINT32                           ulPagingType;   /* 被叫业务类型，区分语音，短信和数据*/
    VOS_UINT32                           ulXccState;     /* 如果异常出现在XCC模块的被叫状态机中，返回XCC当前的子状态*/
}NAS_ERR_LOG_1X_MT_SERVICE_EXCEPTION_STRU;


/*****************************************************************************
 结构名    : NAS_ERR_LOG_XREG_CTX_STRU
 结构说明  : xreg存在全局变量中的失败信息
 1.日    期   : 2016年01月25日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_XREG_REGISTRATION_TYPE_ENUM_UINT8           enRegType;              /* 当前注册类型 */
    NAS_ERR_LOG_XREG_FAIL_REASON_ENUM_UINT8                 enRegFailReason;        /* 注册失败原因值 */
    VOS_UINT8                                               ucRsv[2];
}NAS_ERR_LOG_XREG_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_REG_RESULT_EVENT_STRU
 结构说明  : xreg存在全局变量中的失败信息
 1.日    期   : 2016年01月25日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;
    NAS_ERR_LOG_XREG_CTX_STRU                           stXregErrLogCtx;
}NAS_ERR_LOG_XREG_RESULT_EVENT_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_XSMS_SND_CTX_STRU
 结构说明  : MO短信发送过程中的状态结构体
 1.日    期   : 2016年01月25日
   作    者   : c00299064
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      enFailState;            /* 发生错误的时候的状态机状态 值参考:TAF_XSMS_MO_FSM_ID_ENUM_UINT32 */
    VOS_UINT32                                      enLastXccCnfRslt;       /* 最后一次的XCC RESULT 值参考:TAF_XCC_CAUSE_ENUM_UINT32*/
    VOS_UINT8                                       enLastCasCnfRslt;       /* 最后一次的CAS RESULT 值参考:CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8  */
    VOS_UINT8                                       enLastTlAckCauseCode;   /* 收到TL_ACK 里面的CAUSE CODE，没有错误写BUTT值，值参考:TAF_XSMS_TL_CAUSE_CODE_ENUM8*/
    NAS_ERR_LOG_XSMS_NO_TL_ACK_REASON_ENUM_UINT8    enNoTlAckReason;        /* 没有收到TL_ACK的 可能原因 */
    NAS_ERR_LOG_XSMS_FAIL_REASON_ENUM_UINT8         enSndFailReason;        /* 发送失败原因 */
    VOS_UINT32                                      ulReSendTime;

}NAS_ERR_LOG_XSMS_SND_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_XSMS_SND_FAIL_INFO_STRU
 结构说明  : MO短信存在全局变量中的失败信息
 1.日    期   : 2016年01月25日
   作    者   : c00299064
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_ERR_LOG_XSMS_SND_CTX_STRU           stXsmsSndCtx;
}NAS_ERR_LOG_XSMS_SND_FAIL_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_XSMS_RCV_CTX_STRU
 结构说明  : MT短信存在全局变量中的失败信息
 1.日    期   : 2016年01月25日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_XSMS_FAIL_REASON_ENUM_UINT8         enFailReason;         /* MT失败原因值 */
    VOS_UINT8                                       ucReRcvTime;          /* MT失败次数 */
    VOS_UINT8                                       enLastCasCnfRslt;     /* 值参考:CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8  */
    VOS_UINT8                                       ucRcv;
}NAS_ERR_LOG_XSMS_RCV_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_ERR_LOG_XSMS_RCV_FAIL_INFO_STRU
 结构说明  : MT短信存在全局变量中的失败信息
 1.日    期   : 2016年01月25日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_ERR_LOG_XSMS_RCV_CTX_STRU           stXsmsRcvCtx;
}NAS_ERR_LOG_XSMS_RCV_FAIL_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
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


