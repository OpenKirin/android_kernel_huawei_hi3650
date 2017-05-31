

#ifndef __ADSTEST_H__
#define __ADSTEST_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "product_config.h"
#include "PsCommonDef.h"
#include "AdsIntraMsg.h"
#include "AdsCtx.h"
#include "msp_diag_comm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD   (5000000)
#define ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD   (500000)

#define ADS_LOG_BUFF_LEN 	                (256)

#if defined(_lint)
#define ADS_DBG_PRINT(lvl, fmt, ...)\
            PS_PRINTF(fmt, ##__VA_ARGS__)
#else
#define ADS_DBG_PRINT(lvl, fmt, ...)\
            ADS_LogPrintf(lvl, "[slice:%u][%s] "fmt, VOS_GetSlice(), __FUNCTION__, ##__VA_ARGS__)
#endif

#define ADS_TRACE_LOW(...)\
            ADS_DBG_PRINT(ADS_LOG_LEVEL_INFO, __VA_ARGS__)

#define ADS_TRACE_MED(...)\
            ADS_DBG_PRINT(ADS_LOG_LEVEL_NOTICE, __VA_ARGS__)

#define ADS_TRACE_HIGH(...)\
            ADS_DBG_PRINT(ADS_LOG_LEVEL_ERROR, __VA_ARGS__)


/* ����IPF�ж��¼�ͳ�� */
#define ADS_DBG_UL_QUE_NON_EMPTY_TRIG_EVENT(n)      (g_stAdsStats.stUlComStatsInfo.ulULQueNonEmptyTrigEvent += (n))
#define ADS_DBG_UL_QUE_HIT_THRES_TRIG_EVENT(n)      (g_stAdsStats.stUlComStatsInfo.ulULQueHitThresTrigEvent += (n))
#define ADS_DBG_UL_TMR_HIT_THRES_TRIG_EVENT(n)      (g_stAdsStats.stUlComStatsInfo.ulULTmrHitThresTrigEvent += (n))
#define ADS_DBG_UL_10MS_TMR_TRIG_EVENT(n)           (g_stAdsStats.stUlComStatsInfo.ulUL10MsTmrTrigEvent += (n))
#define ADS_DBG_UL_SPE_INT_TRIG_EVENT(n)            (g_stAdsStats.stUlComStatsInfo.ulULSpeIntTrigEvent += (n))
#define ADS_DBG_UL_PROC_EVENT_NUM(n)                (g_stAdsStats.stUlComStatsInfo.ulULProcEventNum += (n))

/* ��������ͳ�� */
#define ADS_DBG_UL_RMNET_RX_PKT_NUM(n)              (g_stAdsStats.stUlComStatsInfo.ulULRmnetRxPktNum += (n))
#define ADS_DBG_UL_RMNET_MODEMID_ERR_NUM(n)         (g_stAdsStats.stUlComStatsInfo.ulULRmnetModemIdErrNum += (n))
#define ADS_DBG_UL_RMNET_RABID_NUM(n)               (g_stAdsStats.stUlComStatsInfo.ulULRmnetRabIdErrNum += (n))
#define ADS_DBG_UL_RMNET_ENQUE_SUCC_NUM(n)          (g_stAdsStats.stUlComStatsInfo.ulULRmnetEnQueSuccNum += (n))
#define ADS_DBG_UL_RMNET_ENQUE_FAIL_NUM(n)          (g_stAdsStats.stUlComStatsInfo.ulULRmnetEnQueFailNum += (n))
#define ADS_DBG_UL_PKT_ENQUE_SUCC_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulULPktEnQueSuccNum += (n))
#define ADS_DBG_UL_PKT_ENQUE_FAIL_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulULPktEnQueFailNum += (n))

/* ����BDͳ�� */
#define ADS_DBG_UL_BDQ_CFG_IPF_HAVE_NO_BD_NUM(n)    (g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfHaveNoBd += (n))
#define ADS_DBG_UL_BDQ_CFG_BD_SUCC_NUM(n)           (g_stAdsStats.stUlComStatsInfo.ulULBdqCfgBdSuccNum += (n))
#define ADS_DBG_UL_BDQ_CFG_BD_FAIL_NUM(n)           (g_stAdsStats.stUlComStatsInfo.ulULBdqCfgBdFailNum += (n))
#define ADS_DBG_UL_BDQ_CFG_IPF_SUCC_NUM(n)          (g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfSuccNum += (n))
#define ADS_DBG_UL_BDQ_CFG_IPF_FAIL_NUM(n)          (g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfFailNum += (n))
#define ADS_DBG_UL_BDQ_SAVE_SRC_MEM_NUM(n)          (g_stAdsStats.stUlComStatsInfo.ulULBdqSaveSrcMemNum += (n))
#define ADS_DBG_UL_BDQ_FREE_SRC_MEM_NUM(n)          (g_stAdsStats.stUlComStatsInfo.ulULBdqFreeSrcMemNum += (n))
#define ADS_DBG_UL_BDQ_FREE_SRC_MEM_ERR(n)          (g_stAdsStats.stUlComStatsInfo.ulULBdqFreeSrcMemErr += (n))

/* �������ͳ�� */
#define ADS_DBG_UL_WM_LEVEL_1_HIT_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulULWmLevel1HitNum += (n))
#define ADS_DBG_UL_WM_LEVEL_2_HIT_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulULWmLevel2HitNum += (n))
#define ADS_DBG_UL_WM_LEVEL_3_HIT_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulULWmLevel3HitNum += (n))
#define ADS_DBG_UL_WM_LEVEL_4_HIT_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulULWmLevel4HitNum += (n))

/* ���и�λͳ�� */
#define ADS_DBG_UL_RESET_CREATE_SEM_FAIL_NUM(n)     (g_stAdsStats.stResetStatsInfo.ulULResetCreateSemFailNum += (n))
#define ADS_DBG_UL_RESET_LOCK_FAIL_NUM(n)           (g_stAdsStats.stResetStatsInfo.ulULResetLockFailNum += (n))
#define ADS_DBG_UL_RESET_SUCC_NUM(n)                (g_stAdsStats.stResetStatsInfo.ulULResetSuccNum += (n))

/* ����IPF�ж��¼�ͳ�� */
#define ADS_DBG_DL_RCV_IPF_RD_INT_NUM(n)            (g_stAdsStats.stDlComStatsInfo.ulDLRcvIpfRdIntNum += (n))
#define ADS_DBG_DL_CCORE_RESET_TRIG_EVENT(n)        (g_stAdsStats.stDlComStatsInfo.ulDLCCoreResetTrigEvent += (n))
#define ADS_DBG_DL_PROC_IPF_RD_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDLProcIpfRdEventNum += (n))
#define ADS_DBG_DL_RCV_IPF_ADQ_EMPTY_INT_NUM(n)     (g_stAdsStats.stDlComStatsInfo.ulDLRcvIpfAdqEmptyIntNum += (n))
#define ADS_DBG_DL_RECYCLE_MEM_TRIG_EVENT(n)        (g_stAdsStats.stDlComStatsInfo.ulDLRecycleMemTrigEvent += (n))
#define ADS_DBG_DL_PROC_IPF_AD_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDLProcIpfAdEventNum += (n))

/* ����RDͳ�� */
#define ADS_DBG_DL_RDQ_RX_RD_NUM(n)                 (g_stAdsStats.stDlComStatsInfo.ulDLRdqRxRdNum += (n))
#define ADS_DBG_DL_RDQ_GET_RD0_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDLRdqGetRd0Num += (n))
#define ADS_DBG_DL_RDQ_TRANS_MEM_FAIL_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDLRdqTransMemFailNum += (n))
#define ADS_DBG_DL_RDQ_RX_NORM_PKT_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDLRdqRxNormPktNum += (n))
#define ADS_DBG_DL_RDQ_RX_ND_PKT_NUM(n)             (g_stAdsStats.stDlComStatsInfo.ulDLRdqRxNdPktNum += (n))
#define ADS_DBG_DL_RDQ_RX_DHCP_PKT_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDLRdqRxDhcpPktNum += (n))
#define ADS_DBG_DL_RDQ_RX_ERR_PKT_NUM(n)            (g_stAdsStats.stDlComStatsInfo.ulDLRdqRxErrPktNum += (n))
#define ADS_DBG_DL_RDQ_FILTER_ERR_PKT_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDLRdqFilterErrNum += (n))

/* ��������ͳ��*/
#define ADS_DBG_DL_RMNET_TX_PKT_NUM(n)              (g_stAdsStats.stDlComStatsInfo.ulDLRmnetTxPktNum += (n))
#define ADS_DBG_DL_RMNET_MODEMID_ERR_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDLRmnetModemIdErrNum += (n))
#define ADS_DBG_DL_RMNET_RABID_ERR_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDLRmnetRabIdErrNum += (n))
#define ADS_DBG_DL_RMNET_NO_FUNC_FREE_PKT_NUM(n)    (g_stAdsStats.stDlComStatsInfo.ulDLRmnetNoFuncFreePktNum += (n))

/* ����ADͳ��  */
#define ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_SUCC_NUM(n)    (g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocSysMemSuccNum += (n))
#define ADS_DBG_DL_ADQ_ALLOC_SYS_MEM_FAIL_NUM(n)    (g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocSysMemFailNum += (n))
#define ADS_DBG_DL_ADQ_ALLOC_MEM_SUCC_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocMemSuccNum += (n))
#define ADS_DBG_DL_ADQ_ALLOC_MEM_FAIL_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocMemFailNum += (n))
#define ADS_DBG_DL_ADQ_FREE_MEM_NUM(n)              (g_stAdsStats.stDlComStatsInfo.ulDLAdqFreeMemNum  += (n))
#define ADS_DBG_DL_ADQ_RECYCLE_MEM_SUCC_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDLAdqRecycleMemSuccNum += (n))
#define ADS_DBG_DL_ADQ_RECYCLE_MEM_FAIL_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDLAdqRecycleMemFailNum += (n))
#define ADS_DBG_DL_ADQ_GET_FREE_AD_SUCC_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDLAdqGetFreeAdSuccNum += (n))
#define ADS_DBG_DL_ADQ_GET_FREE_AD_FAIL_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDLAdqGetFreeAdFailNum += (n))
#define ADS_DBG_DL_ADQ_CFG_AD_NUM(n)                (g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAdNum += (n))
#define ADS_DBG_DL_ADQ_CFG_AD0_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAd0Num += (n))
#define ADS_DBG_DL_ADQ_CFG_AD1_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAd1Num += (n))
#define ADS_DBG_DL_ADQ_CFG_IPF_SUCC_NUM(n)          (g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgIpfSuccNum += (n))
#define ADS_DBG_DL_ADQ_CFG_IPF_FAIL_NUM(n)          (g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgIpfFailNum += (n))
#define ADS_DBG_DL_ADQ_START_EMPTY_TMR_NUM(n)       (g_stAdsStats.stDlComStatsInfo.ulDLAdqStartEmptyTmrNum += (n))
#define ADS_DBG_DL_ADQ_EMPTY_TMR_TIMEOUT_NUM(n)     (g_stAdsStats.stDlComStatsInfo.ulDLAdqEmptyTmrTimeoutNum += (n))
#define ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(n)     (g_stAdsStats.stDlComStatsInfo.ulDLAdqRcvAd0EmptyIntNum += (n))
#define ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(n)     (g_stAdsStats.stDlComStatsInfo.ulDLAdqRcvAd1EmptyIntNum += (n))

/* ��������ͳ�� */
#define ADS_DBG_DL_FC_ACTIVATE_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDLFcActivateNum += (n))
#define ADS_DBG_DL_FC_TMR_TIMEOUT_NUM(n)            (g_stAdsStats.stDlComStatsInfo.ulDLFcTmrTimeoutNum += (n))

/* ���и�λͳ�� */
#define ADS_DBG_DL_RESET_CREATE_SEM_FAIL_NUM(n)     (g_stAdsStats.stResetStatsInfo.ulDLResetCreateSemFailNum += (n))
#define ADS_DBG_DL_RESET_LOCK_FAIL_NUM(n)           (g_stAdsStats.stResetStatsInfo.ulDLResetLockFailNum += (n))
#define ADS_DBG_DL_RESET_SUCC_NUM(n)                (g_stAdsStats.stResetStatsInfo.ulDLResetSuccNum += (n))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : ADS_FLOW_DEBUG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ADS�����ϱ�Debug����
*****************************************************************************/
enum ADS_FLOW_DEBUG_ENUM
{
    ADS_FLOW_DEBUG_OFF                  = 0,
    ADS_FLOW_DEBUG_DL_ON                = 1,
    ADS_FLOW_DEBUG_UL_ON                = 2,
    ADS_FLOW_DEBUG_ALL_ON               = 3,
    ADS_FLOW_DEBUG_BUTT
};

/*****************************************************************************
 ö������  : ADS_LOG_LEVEL_ENUM
 ö��˵��  : ADS��ӡLOG�ȼ�
*****************************************************************************/
enum ADS_LOG_LEVEL_ENUM
{
    ADS_LOG_LEVEL_DEBUG                 = 0,                /* 0x0: debug-level                      */
    ADS_LOG_LEVEL_INFO,                                     /* 0x1: informational                    */
    ADS_LOG_LEVEL_NOTICE,                                   /* 0x2: normal but significant condition */
    ADS_LOG_LEVEL_WARNING,                                  /* 0x3: warning conditions               */
    ADS_LOG_LEVEL_ERROR,                                    /* 0x4: error conditions                 */
    ADS_LOG_LEVEL_FATAL,                                    /* 0x5: fatal error condition            */

    ADS_LOG_LEVEL_BUTT
};
typedef VOS_UINT32 ADS_LOG_LEVEL_ENUM_UINT32;


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
�ṹ��    : ADS_UL_COM_STATS_INFO_STRU
�ṹ˵��  : ADS���й���������ͳ��������

  1.��    ��   : 2013��09��18��
    ��    ��   : f00179208
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    /* ����IPF�¼�ͳ�� */
    VOS_UINT32                          ulULQueNonEmptyTrigEvent;
    VOS_UINT32                          ulULQueFullTrigEvent;
    VOS_UINT32                          ulULQueHitThresTrigEvent;
    VOS_UINT32                          ulULTmrHitThresTrigEvent;
    VOS_UINT32                          ulUL10MsTmrTrigEvent;
    VOS_UINT32                          ulULSpeIntTrigEvent;
    VOS_UINT32                          ulULProcEventNum;

    /* ��������ͳ�� */
    VOS_UINT32                          ulULRmnetRxPktNum;
    VOS_UINT32                          ulULRmnetModemIdErrNum;
    VOS_UINT32                          ulULRmnetRabIdErrNum;
    VOS_UINT32                          ulULRmnetEnQueSuccNum;
    VOS_UINT32                          ulULRmnetEnQueFailNum;
    VOS_UINT32                          ulULPktEnQueSuccNum;
    VOS_UINT32                          ulULPktEnQueFailNum;

    /* ����BDͳ�� */
    VOS_UINT32                          ulULBdqCfgIpfHaveNoBd;
    VOS_UINT32                          ulULBdqCfgBdSuccNum;
    VOS_UINT32                          ulULBdqCfgBdFailNum;
    VOS_UINT32                          ulULBdqCfgIpfSuccNum;
    VOS_UINT32                          ulULBdqCfgIpfFailNum;
    VOS_UINT32                          ulULBdqSaveSrcMemNum;
    VOS_UINT32                          ulULBdqFreeSrcMemNum;
    VOS_UINT32                          ulULBdqFreeSrcMemErr;

    /* �������ͳ�� */
    VOS_UINT32                          ulULWmLevel1HitNum;
    VOS_UINT32                          ulULWmLevel2HitNum;
    VOS_UINT32                          ulULWmLevel3HitNum;
    VOS_UINT32                          ulULWmLevel4HitNum;

    /* ��������ͳ�� */
    VOS_UINT32                          ulULFlowDebugFlag;
    VOS_UINT32                          ulULFlowRptThreshold;
    VOS_UINT32                          ulULFlowInfo;
    VOS_UINT32                          ulULStartSlice;
    VOS_UINT32                          ulULEndSlice;

}ADS_UL_COM_STATS_INFO_STRU;

/*****************************************************************************
�ṹ��    : ADS_DL_COM_STATS_INFO_STRU
�ṹ˵��  : ADS���й���������ͳ��������

  1.��    ��   : 2013��09��18��
    ��    ��   : f00179208
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    /* ����IPF�¼�ͳ�� */
    VOS_UINT32                          ulDLRcvIpfRdIntNum;
    VOS_UINT32                          ulDLCCoreResetTrigEvent;
    VOS_UINT32                          ulDLProcIpfRdEventNum;
    VOS_UINT32                          ulDLRcvIpfAdqEmptyIntNum;
    VOS_UINT32                          ulDLRecycleMemTrigEvent;
    VOS_UINT32                          ulDLProcIpfAdEventNum;

    /* ����RDͳ�� */
    VOS_UINT32                          ulDLRdqRxRdNum;
    VOS_UINT32                          ulDLRdqGetRd0Num;
    VOS_UINT32                          ulDLRdqTransMemFailNum;
    VOS_UINT32                          ulDLRdqRxNormPktNum;
    VOS_UINT32                          ulDLRdqRxNdPktNum;
    VOS_UINT32                          ulDLRdqRxDhcpPktNum;
    VOS_UINT32                          ulDLRdqRxErrPktNum;
    VOS_UINT32                          ulDLRdqFilterErrNum;

    /* ��������ͳ�� */
    VOS_UINT32                          ulDLRmnetTxPktNum;
    VOS_UINT32                          ulDLRmnetModemIdErrNum;
    VOS_UINT32                          ulDLRmnetRabIdErrNum;
    VOS_UINT32                          ulDLRmnetNoFuncFreePktNum;

    /* ����ADͳ�� */
    VOS_UINT32                          ulDLAdqAllocSysMemSuccNum;
    VOS_UINT32                          ulDLAdqAllocSysMemFailNum;
    VOS_UINT32                          ulDLAdqAllocMemSuccNum;
    VOS_UINT32                          ulDLAdqAllocMemFailNum;
    VOS_UINT32                          ulDLAdqFreeMemNum;
    VOS_UINT32                          ulDLAdqRecycleMemSuccNum;
    VOS_UINT32                          ulDLAdqRecycleMemFailNum;
    VOS_UINT32                          ulDLAdqGetFreeAdSuccNum;
    VOS_UINT32                          ulDLAdqGetFreeAdFailNum;
    VOS_UINT32                          ulDLAdqCfgAdNum;
    VOS_UINT32                          ulDLAdqCfgAd0Num;
    VOS_UINT32                          ulDLAdqCfgAd1Num;
    VOS_UINT32                          ulDLAdqCfgIpfSuccNum;
    VOS_UINT32                          ulDLAdqCfgIpfFailNum;
    VOS_UINT32                          ulDLAdqStartEmptyTmrNum;
    VOS_UINT32                          ulDLAdqEmptyTmrTimeoutNum;
    VOS_UINT32                          ulDLAdqRcvAd0EmptyIntNum;
    VOS_UINT32                          ulDLAdqRcvAd1EmptyIntNum;

    /* ��������ͳ�� */
    VOS_UINT32                          ulDLFcActivateNum;
    VOS_UINT32                          ulDLFcTmrTimeoutNum;

    /* ��������ͳ�� */
    VOS_UINT32                          ulDLFlowDebugFlag;
    VOS_UINT32                          ulDLFlowRptThreshold;
    VOS_UINT32                          ulDLFlowInfo;
    VOS_UINT32                          ulDLStartSlice;
    VOS_UINT32                          ulDLEndSlice;

}ADS_DL_COM_STATS_INFO_STRU;

/*****************************************************************************
�ṹ��    : ADS_RESET_STATS_INFO_STRU
�ṹ˵��  : ADS��λ����ͳ��������

  1.��    ��   : 2013��09��18��
    ��    ��   : f00179208
    �޸�����   : ��������
*****************************************************************************/
typedef struct
{
    /* ���и�λͳ�� */
    VOS_UINT32                          ulULResetCreateSemFailNum;
    VOS_UINT32                          ulULResetLockFailNum;
    VOS_UINT32                          ulULResetSuccNum;

    /* ���и�λͳ�� */
    VOS_UINT32                          ulDLResetCreateSemFailNum;
    VOS_UINT32                          ulDLResetLockFailNum;
    VOS_UINT32                          ulDLResetSuccNum;
} ADS_RESET_STATS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_STATS_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ADSͳ����

  1.��    ��   : 2012��1��20��
    ��    ��   : S62952
    �޸�����   : �����ļ�

*****************************************************************************/
typedef struct
{
    ADS_UL_COM_STATS_INFO_STRU          stUlComStatsInfo;
    ADS_DL_COM_STATS_INFO_STRU          stDlComStatsInfo;
    ADS_RESET_STATS_INFO_STRU           stResetStatsInfo;

} ADS_STATS_INFO_STRU;


/*****************************************************************************
  8 ȫ�ֱ�������
*****************************************************************************/

extern ADS_STATS_INFO_STRU              g_stAdsStats;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID ADS_ResetDebugInfo(VOS_VOID);
VOS_VOID ADS_DLFlowAdd(VOS_UINT32 ulSduLen);
VOS_VOID ADS_ULFlowAdd(VOS_UINT32 ulSduLen);
VOS_VOID ADS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag);
VOS_VOID ADS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold);
VOS_VOID ADS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold);
VOS_VOID ADS_LogPrintf(ADS_LOG_LEVEL_ENUM_UINT32 enLevel, VOS_CHAR *pcFmt, ...);



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

#endif /* end of AdsDebug.h */
