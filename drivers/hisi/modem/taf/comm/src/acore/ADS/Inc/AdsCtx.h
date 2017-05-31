

#ifndef __ADSCTX_H__
#define __ADSCTX_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "AdsInterface.h"
#include "AdsDeviceInterface.h"
#include "CdsAdsInterface.h"
#include "AdsNdInterface.h"
#include "AdsTimerMgmt.h"
#include "AdsLog.h"
#include "mdrv.h"
#include "NVIM_Interface.h"
#include "AdsFcInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/wakelock.h>
#if (defined(CONFIG_BALONG_SPE))
#include <linux/spe/spe_interface.h>
#include "mdrv_spe_wport.h"
#endif /* CONFIG_BALONG_SPE */
#else
#include "Linuxstub.h"
#endif /* VOS_OS_VER == VOS_LINUX */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ADSʵ��������Modem��������һ�� */
#define ADS_INSTANCE_MAX_NUM            (MODEM_ID_BUTT)

/* ADSʵ������ֵ */
#define ADS_INSTANCE_INDEX_0            (0)
#define ADS_INSTANCE_INDEX_1            (1)
#define ADS_INSTANCE_INDEX_2            (2)

/*���»�����е����ֵ */
#define ADS_RAB_NUM_MAX                 (11)

/* ��ǰ������Ķ�����5��15, �����һ��5��ƫ���� */
#define ADS_RAB_ID_OFFSET               (5)

/* Rab Id����Сֵ */
#define ADS_RAB_ID_MIN                  (5)

/* Rab Id�����ֵ */
#define ADS_RAB_ID_MAX                  (15)

/* Rab Id����Чֵ */
#define ADS_RAB_ID_INVALID              (0xFF)

/* Ϊ�˱���Ƶ������IPF�жϣ���Ҫ�����ܰ����ƣ��ܰ��������� */
#define ADS_UL_SEND_DATA_NUM_THREDHOLD          (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum)

#define ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(n)   (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = (n))

#define ADS_UL_RX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen)
#define ADS_DL_TX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen)

/* �����AD��Ҫƫ��14��ΪIPF RD��Ŀ�ĵ�ַ��14ΪMACͷ�ĳ��� */
#define ADS_DL_AD_DATA_PTR_OFFSET       (14)

/* Ĭ�ϵ����ȼ���Ȩ�� */
#define ADS_UL_DEFAULT_PRI_WEIGHTED_NUM (0x01)

#define ADS_GET_CURR_KERNEL_TIME()      (jiffies)
#define ADS_TIME_AFTER_EQ(a, b)         time_after_eq((a), (b))

/* ADS ADQ�ĸ��� */
#define ADS_DL_ADQ_MAX_NUM              (2)

/*����ADQ�ձ�����ʱ������ֵ����������AD�������ڸ�ֵʱ������������ʱ��*/
#define ADS_IPF_DLAD_START_TMR_THRESHOLD (IPF_DLAD0_DESC_SIZE - 6)

/* ADSʹ�õ�SPE�˿ں� */
#define ADS_IPF_SPE_PORT_0              (SPE_PORT_MAX + 128)
#define ADS_IPF_SPE_PORT_1              (SPE_PORT_MAX + 129)

/* AD�ڴ���д�С */
#define ADS_IPF_AD0_MEM_BLK_NUM         (IPF_DLAD0_DESC_SIZE * 2)
#define ADS_IPF_AD1_MEM_BLK_NUM         (IPF_DLAD1_DESC_SIZE * 3)
#define ADS_IPF_AD_MEM_RESV_BLK_NUM     (64)

/* AD���ݰ��ĳ��� */
#define ADS_IPF_AD0_MEM_BLK_SIZE        (448)
#define ADS_IPF_AD1_MEM_BLK_SIZE        (1536 + 14)

/* ADS_UL_SendPacket��ADS_DL_RegDlDataCallback��rabidΪ��չ��rabid��
   ��2bit��ΪMODEM ID����6bit��ΪRAB ID��������չ��RABID��ȡMODEM ID */
#define ADS_GET_MODEMID_FROM_EXRABID(i) ((i >> 6) & 0x03)

#define ADS_GET_RABID_FROM_EXRABID(i)   (i & 0x3F)

#define ADS_BUILD_EXRABID(i,j)          (((i << 6) & 0xC0) | (j & 0x3F))

/*******************************�����¼� Begin*******************************/

/* ADS���������¼� */
#define ADS_UL_EVENT_BASE               (0x00000000)
#define ADS_UL_EVENT_DATA_PROC          (ADS_UL_EVENT_BASE | 0x0001)

/* ADS���������¼� */
#define ADS_DL_EVENT_BASE               (0x00000000)
#define ADS_DL_EVENT_IPF_RD_INT         (ADS_DL_EVENT_BASE | 0x0001)
#define ADS_DL_EVENT_IPF_ADQ_EMPTY_INT  (ADS_DL_EVENT_BASE | 0x0002)

/*******************************�����¼� End*******************************/

/*******************************����ͳ�� Begin*******************************/
/* ��ȡ����ͳ�������� */
#define ADS_GET_DSFLOW_STATS_CTX_PTR()              (&(g_stAdsCtx.stDsFlowStatsCtx))

/* ���õ�ǰ�������� */
#define ADS_SET_CURRENT_UL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULCurDataRate = (n))

/* ���õ�ǰ�������� */
#define ADS_SET_CURRENT_DL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLCurDataRate = (n))

/* ͳ�������������յ����ĸ��� */
#define ADS_RECV_UL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes += (n))

/* ͳ�������������յ����ĸ��� */
#define ADS_RECV_DL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes += (n))

/* ��ȡ�����������յ����ĸ��� */
#define ADS_GET_UL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes)

/* ��ȡ�����������յ����ĸ��� */
#define ADS_GET_DL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes)

/* �������������յ����ĸ������� */
#define ADS_CLEAR_UL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes = 0)

/* �������������յ����ĸ������� */
#define ADS_CLEAR_DL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes = 0)

/*******************************����ͳ�� End*******************************/


/*******************************���� Begin*******************************/
/* ��ȡADS����ʵ���ַ */
#define ADS_UL_GET_CTX_PTR(i)                       (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx))

/* ��ȡ���ж���ָ�� */
#define ADS_UL_GET_QUEUE_LINK_PTR(i, j)             (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)

/* ��ȡ���ж����� */
#define ADS_UL_GET_QUEUE_LINK_SPINLOCK(i, j)        (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].stSpinLock))

/* ��ȡADS����BD���ò�����ַ */
#define ADS_UL_GET_BD_CFG_PARA_PTR(index)           (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdCfgParam[index]))

/* ��ȡADS����BD�����ַ */
#define ADS_UL_GET_BD_BUFF_PTR(index)               (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdBuff[index]))

/* ��ȡADS���з��ͱ�����ʱ��ʱ�� */
#define ADS_UL_GET_PROTECT_TIMER_LEN()              (g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen)

/* ��ȡ�����Ƿ����ڷ��͵ı�־λ */
#define ADS_UL_GET_SENDING_FLAG()                   (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg)

/* ���������Ƿ����ڷ��͵ı�־λ */
#define ADS_UL_SET_SENDING_FLAG(flg)                (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = flg)

/* ��ȡ�洢���е����� */
#define ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.aucPrioIndex[j])

/* ��ȡ���ж��е������ȼ�*/
#define ADS_UL_GET_QUEUE_QCI(i, j)                  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].enPrio)

/* ��ȡ���ж�����Ϣ */
#define ADS_UL_GET_QUEUE_LINK_INFO(i, j)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].pstAdsUlLink)

/* ��ȡIX OR HRPD������IPF�������־ */
#define ADS_UL_GET_1X_OR_HRPD_UL_IPF_FLAG(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].uc1XorHrpdUlIpfFlag)

/* ��ȡ���ж���һ����Ȩ����Χ�ڼ�¼�ķ��͸��� */
#define ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum)

/* �������ж���һ����Ȩ����Χ�ڼ�¼�ķ��͸��� */
#define ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(i, j, n)  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum += n)

/* ������ж���һ����Ȩ����Χ�ڼ�¼�ķ��͸��� */
#define ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum = 0)

/* ��ȡ���ж������ȼ��ļ�Ȩ�� */
#define ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[ADS_UL_GET_QUEUE_QCI(i, j)])

/* ��ȡ���ж������ݰ�������*/
#define ADS_UL_GET_QUEUE_PKT_TYPE(InstanceIndex, RabId) \
            (g_stAdsCtx.astAdsSpecCtx[InstanceIndex].stAdsUlCtx.astAdsUlQueue[RabId].enPktType)


/* ��ȡADS���з��ͱ�����ʱ��ʱ�� */
#define ADS_UL_GET_STAT_TIMER_LEN()     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatTmrLen)

#define ADS_UL_ADD_STAT_PKT_NUM(n)      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum += (n))

#define ADS_UL_GET_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum)

#define ADS_UL_CLR_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum = 0)

/* ��ȡ�����ް����Ʊ�� */
#define ADS_UL_GET_THRESHOLD_ACTIVE_FLAG() \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulActiveFlag)

/* ��ȡ�����ް���jiffies��ʱ����� */
#define ADS_UL_GET_JIFFIES_TMR_CNT()     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt)

/* ���������ް���jiffies��ʱ����� */
#define ADS_UL_SET_JIFFIES_TMR_CNT(n)     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt += (n))

/* ��ȡ�����ް���jiffies�ĳ�ʱ���� */
#define ADS_UL_GET_JIFFIES_EXP_TMR_LEN() (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrExpCnt)

/* ��ȡ�������ݰ�ˮ�ߵȼ� */
#define ADS_UL_GET_WATER_LEVEL_ONE()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel1)

#define ADS_UL_GET_WATER_LEVEL_TWO()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel2)

#define ADS_UL_GET_WATER_LEVEL_THREE()  \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel3)

#define ADS_UL_GET_WATER_LEVEL_FOUR()   \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel4)

/* ��ȡ�����ް����� */
#define ADS_UL_DATA_THRESHOLD_ONE       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1)

#define ADS_UL_DATA_THRESHOLD_TWO       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold2)

#define ADS_UL_DATA_THRESHOLD_THREE     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold3)

#define ADS_UL_DATA_THRESHOLD_FOUR      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold4)


/*******************************���� End*******************************/

/* ����IPF�ڴ��ͷŶ����׵�ַ */
#define ADS_UL_IPF_SRCMEM_FREE_QUE()            (&(g_stAdsCtx.stAdsIpfCtx.stUlSrcMemFreeQue))

/* IPF����Դ�ڴ��ͷ�QUEUE�������޳�Ϊ����IPF BD��������2�� */
#define ADS_UL_IPF_SRCMEM_FREE_QUE_SIZE         (2 * IPF_ULBD_DESC_SIZE)

/* ͨ������ADS���ж��г��ȣ�����A��ϵͳ�ڴ棬�����޳���ʼ��ֵ */
#define ADS_UL_MAX_QUEUE_LENGTH                 (500)

/* ��ȡ���ж����޳� */
#define ADS_UL_GET_MAX_QUEUE_LENGTH(i)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ulUlMaxQueueLength)

/* ��ȡADS����IPF AD BUFFER��ַ */
#define ADS_DL_GET_IPF_AD_DESC_PTR(i, j)        (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdDesc[i][j]))

/*******************************���� Begin*******************************/

/* ��ȡADS����ʵ���ַ */
#define ADS_DL_GET_CTX_PTR(i)                   (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx))

/* ��ȡADS����IPF RD BUFFER��ַ */
#define ADS_DL_GET_IPF_RD_DESC_PTR(index)       (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlRdDesc[index]))

/* ��ȡADS����RAB INFO��ַ */
#define ADS_DL_GET_RAB_INFO_PTR(i, rabid)       (&(ADS_DL_GET_CTX_PTR(i)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET]))

/* ��ȡADS����RAB��Ӧ�����ݰ����� */
#define ADS_DL_GET_PKT_TYPE(instance, rabid)    (ADS_DL_GET_CTX_PTR(instance)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET].enPktType)

/* ��ȡADS�������ݻص�����ָ�� */
#define ADS_DL_GET_DATA_CALLBACK_FUNC(i,j)      (ADS_DL_GET_RAB_INFO_PTR(i,j)->pRcvDlDataFunc)
#define ADS_DL_GET_DATA_EXPARAM(i,j)            (ADS_DL_GET_RAB_INFO_PTR(i,j)->ulExParam)

/* get/set the last data buff ptr */
#define ADS_DL_GET_LST_DATA_PTR(mid,rabid)          (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt)
#define ADS_DL_SET_LST_DATA_PTR(mid,rabid, psPara)  (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt = (psPara))

#define ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId) \
            (ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId)->pRcvDlFilterDataFunc)

/* ��ȡADS�������ز�����Ϣ��ַ */
#define ADS_DL_GET_FC_ASSEM_INFO_PTR(i)         (&(ADS_DL_GET_CTX_PTR(i)->stFcAssemInfo))

/* ��ȡADS��������������������ص�����ָ�� */
#define ADS_DL_GET_FC_ASSEM_TUNE_FUNC(i)        (ADS_DL_GET_FC_ASSEM_INFO_PTR(i)->pFcAssemTuneFunc)

/*******************************���� End*******************************/

/*******************************IPF Begin*******************************/
/* ��ȡIPF��ص������� */
#define ADS_GET_IPF_CTX_PTR()           (&(g_stAdsCtx.stAdsIpfCtx))

#define ADS_GET_IPF_DEV()               (&(g_stAdsCtx.stAdsIpfCtx.stDev))
#define ADS_IMM_MEM_CB(pstImmZc)        ((ADS_IMM_MEM_CB_STRU *)((pstImmZc)->cb))

#if (defined(CONFIG_BALONG_SPE))
#define ADS_GET_IPF_SPE_WPORT()         (g_stAdsCtx.stAdsIpfCtx.lSpeWPort)
#define ADS_GET_IPF_MEM_POOL_CFG_PTR()  (&(g_stAdsCtx.stAdsIpfCtx.stMemPoolCfg))
#define ADS_GET_IPF_MEM_POOL_PTR(id)    (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id]))
#define ADS_GET_IPF_MEM_QUE(id)         (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id].stQue))
#define ADS_SPE_MEM_CB(pstImmZc)        ((ADS_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))
#endif

/*lint -emacro({717}, ADS_IPF_SPE_MEM_MAP)*/
#define ADS_IPF_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapByDmaRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/*lint -emacro({717}, ADS_IPF_SPE_MEM_UNMAP)*/
#define ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)


/*******************************IPF End*******************************/

/* ���MODEMID��Ч�� */
#define ADS_IS_MODEMID_VALID(usModemId)\
            ((usModemId) < ADS_INSTANCE_MAX_NUM)

/* ���RABIID��Ч�� */
#define ADS_IS_RABID_VALID(ucRabId)\
            (((ucRabId) >= ADS_RAB_ID_MIN) && ((ucRabId) <= ADS_RAB_ID_MAX))

#define ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ucSendingFlg) \
    ((0 != ulAllUlQueueDataNum) && (ulAllUlQueueDataNum >= ADS_UL_SEND_DATA_NUM_THREDHOLD) && (VOS_FALSE == ucSendingFlg))

#if !defined(ADS_ARRAY_SIZE)
#define ADS_ARRAY_SIZE(a)               (sizeof((a)) / sizeof((a[0])))
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö������  : ADS_IPF_MEM_POOL_ID_ENUM
 ö��˵��  : IPF �ڴ����
*****************************************************************************/
enum ADS_IPF_MEM_POOL_ID_ENUM
{
    ADS_IPF_MEM_POOL_ID_AD0             = 0,
    ADS_IPF_MEM_POOL_ID_AD1,

    ADS_IPF_MEM_POOL_ID_BUTT
};
typedef VOS_UINT32 ADS_IPF_MEM_POOL_ID_ENUM_UINT32;


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
 �ṹ����  : ADS_SPE_MEM_CB_STRU
 �ṹ˵��  : IPF CB�ṹ
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} ADS_SPE_MEM_CB_STRU;

/*****************************************************************************
 �ṹ����  : ADS_IMM_MEM_CB_STRU
 �ṹ˵��  : IMM CB�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulPriv[2];
    dma_addr_t                          ulDmaAddr;

} ADS_IMM_MEM_CB_STRU;

/*****************************************************************************
 �ṹ����  : ADS_IPF_BD_BUFF_STRU
 �ṹ˵��  : IPF BD Buffer�ṹ
*****************************************************************************/
typedef struct
{
    IMM_ZC_STRU                        *pstPkt;

} ADS_IPF_BD_BUFF_STRU;

/*****************************************************************************
�ṹ��    : ADS_UL_QUEUE_STRU
�ṹ˵��  : ADS���ж��й���

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS���ж��й���
  2.��    ��   : 2012��02��20��
    ��    ��   : f00179208
    �޸�����   : �޸����ȼ���Ķ���
  3.��    ��   : 2012��9��12��
    ��    ��   : l60609
    �޸�����   : AP������Ŀ������������
  4.��    ��   : 2012��11��27��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II:˫ʵ��
  5.��    ��   : 2013��05��22��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP RPOJECT:����PDP TYPE
*****************************************************************************/
typedef struct
{
    IMM_ZC_HEAD_STRU                   *pstAdsUlLink;                           /* Rab Id��Ӧ�Ķ��� */
    VOS_UINT8                           ucIsQueueValid;                         /* �����Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;                                 /* �������ȼ� */
    VOS_UINT16                          usRecordNum;                            /* ��¼��һ����Ȩ����Χ�ڷ������ݵĸ��� */
    VOS_SPINLOCK                        stSpinLock;                             /* ������ */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* ���ݰ����� */
    VOS_UINT8                           uc1XorHrpdUlIpfFlag;                    /* 1X OR HRPDģʽ�µ�IPF������ */
    VOS_UINT8                           aucRsv[6];

}ADS_UL_QUEUE_STRU;

/*****************************************************************************
�ṹ��    : ADS_DL_RAB_INFO_STRU
�ṹ˵��  : ADS����RAB��Ϣ����

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS����RABID��Ϣ����
  2.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : Share-PDP��Ŀ�������й��˽��պ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabId;                                /* Rab Id */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* ���ݰ����� */
    VOS_UINT8                           aucRsv[2];                              /* ���� */
    VOS_UINT32                          ulExParam;                              /* RMNET���ݽ�����չ���� */
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc;                         /* ��Ӧ�����н��պ��� */
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc;                   /* ��Ӧ�����й��˽��պ��� */
    IMM_ZC_STRU                        *pstLstPkt;

}ADS_DL_RAB_INFO_STRU;

/*****************************************************************************
 �ṹ��   : ADS_DL_FC_ASSEM_STRU
 �ṹ˵�� : ���ض�̬�������

 �޸���ʷ      :
  1.��    ��   : 2012��11��19��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulEnableMask;
    VOS_UINT32              ulFcActiveFlg;
    unsigned long           ulTmrCnt;
    VOS_UINT32              ulRdCnt;
    VOS_UINT32              ulRateUpLev;
    VOS_UINT32              ulRateDownLev;
    VOS_UINT32              ulExpireTmrLen;
    ADS_DRV_ASSEM_FUNC      pFcAssemTuneFunc;

} ADS_DL_FC_ASSEM_STRU;

/*****************************************************************************
�ṹ��    : ADS_DL_CTX_STRU
�ṹ˵��  : ADS����������

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS����������

  2.��    ��   : 2012��4��12��
    ��    ��   : A00165503
    �޸�����   : DTS2012020708222: ADS�����Ż�

  3.��    ��   : 2012��11��19��
    ��    ��   : A00165503
    �޸�����   : DTS2012112206761: ����̬�����������

  4.��    ��   : 2012��11��23��
    ��    ��   : L60609
    �޸�����   : DSDA Phase II

*****************************************************************************/
typedef struct
{
    ADS_DL_RAB_INFO_STRU                astAdsDlRabInfo[ADS_RAB_NUM_MAX];       /*����Rab��Ϣ */
    ADS_DL_FC_ASSEM_STRU                stFcAssemInfo;

} ADS_DL_CTX_STRU;

/*****************************************************************************
�ṹ��    : ADS_UL_CTX_STRU
�ṹ˵��  : ADS����������

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS����������

  2.��    ��   : 2012��02��20��
    ��    ��   : f00179208
    �޸�����   : V7R1C50��Ŀ���������ж������ȼ���Ȩ��

  3.��    ��   : 2012��4��12��
    ��    ��   : A00165503
    �޸�����   : DTS2012020708222: ADS�����Ż�

  4.��    ��   : 2012��8��31��
    ��    ��   : l60609
    �޸�����   : AP������Ŀ�����������ڴ��ͷŶ���

  5.��    ��   : 2012��11��23��
    ��    ��   : L60609
    �޸�����   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    ADS_UL_QUEUE_STRU                   astAdsUlQueue[ADS_RAB_ID_MAX + 1];      /* ���ж��й���ֻ��5-15 */
    ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU  stQueuePriNv;                           /* ��NV�ж�ȡ�����ж������ȼ���Ӧ�ļ�Ȩ�� */
    VOS_UINT8                           aucPrioIndex[ADS_RAB_NUM_MAX];          /* �洢���ź����ȼ������ж��е����� */
    VOS_UINT8                           ucAdsUlCurIndex;                        /* ��¼��ǰ���ȵĶ��� */
    VOS_UINT8                           aucRsv[4];
    VOS_UINT32                          ulUlMaxQueueLength;                     /* ���ж����޳� */
    VOS_UINT8                           aucReserved1[4];

}ADS_UL_CTX_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_DATA_STATS_STRU
 �ṹ˵��  : ADS��������ͳ��
   1.��    ��   : 2012��1��10��
     ��    ��   : L60609
     �޸�����   : �½�
*****************************************************************************/
typedef struct ADS_UL_DATA_STATS
{
    VOS_UINT32                          ulULCurDataRate;                        /* ��ǰ�������ʣ�����PDP�����2������ʣ�ȥ�������� */
    VOS_UINT32                          ulULPeriodSndBytes;                     /* һ������ͳ�������ڷ��͵�byte�� */
}ADS_UL_DATA_STATS_STRU;

/*****************************************************************************
 �ṹ��    : ADS_DL_DATA_STATS_STRU
 �ṹ˵��  : ADS��������ͳ��
   1.��    ��   : 2012��1��10��
     ��    ��   : L60609
     �޸�����   : �½�
*****************************************************************************/
typedef struct ADS_DL_DATA_STATS
{
    VOS_UINT32                          ulDLCurDataRate;                        /* ��ǰ�������ʣ�����PDP�����2������ʣ�ȥ�������� */
    VOS_UINT32                          ulDLPeriodRcvBytes;                     /* һ������ͳ���������յ���byte�� */
}ADS_DL_DATA_STATS_STRU;

/*****************************************************************************
 �ṹ��    : ADS_STATS_INFO_CTX_STRU
 �ṹ˵��  : ADS״̬ͳ��
   1.��    ��   : 2012��1��10��
     ��    ��   : L60609
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    ADS_UL_DATA_STATS_STRU              stULDataStats;                          /* ADS��������ͳ�� */
    ADS_DL_DATA_STATS_STRU              stDLDataStats;                          /* ADS��������ͳ�� */
}ADS_STATS_INFO_CTX_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_THRESHOLD_STAT_STRU
 �ṹ˵��  : ADS�����ް�״̬ͳ��
   1.��    ��   : 2014��06��03��
     ��    ��   : f00179208
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatTmrLen;                           /* ͳ�ƶ�ʱ������ */
    VOS_UINT32                          ulStatPktNum;                           /* �ڵ�λʱ��������ͳ�ư��ĸ��� */
}ADS_UL_THRESHOLD_STAT_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UL_DYNAMIC_ASSEM_INFO_STRU
 �ṹ˵��  : ADS���������Ϣ
   1.��    ��   : 2014��11��08��
     ��    ��   : f00179208
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* ʹ�ܱ�ʶ: 0��ʾȥʹ��,1��ʾʹ�� */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /* ������ʱ����ʱʱ�� */
    unsigned long                       ulProtectTmrCnt;                        /* ������ʱ���ļ��� */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;                       /* ��̬ˮ��ֵ */
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;                       /* ��̬�ް�����ֵ */
    ADS_UL_THRESHOLD_STAT_STRU          stThresholdStatInfo;                    /* �ް�״̬ͳ�� */
}ADS_UL_DYNAMIC_ASSEM_INFO_STRU;

/*****************************************************************************
 �ṹ����  : ADS_IPF_MEM_CFG_STRU
 �ṹ˵��  : �ڴ�������Ϣ

  1.��    ��   : 2015��10��06��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usBlkSize;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];

} ADS_IPF_MEM_CFG_STRU;

/*****************************************************************************
 �ṹ����  : ADS_IPF_MEM_POOL_CFG_STRU
 �ṹ˵��  : �ڴ�����ýṹ

  1.��    ��   : 2015��10��06��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnable;
    ADS_IPF_MEM_CFG_STRU                astMemCfg[ADS_IPF_MEM_POOL_ID_BUTT];

} ADS_IPF_MEM_POOL_CFG_STRU;

/*****************************************************************************
 �ṹ����  : ADS_IPF_MEM_POOL_CFG_STRU
 �ṹ˵��  : �ڴ����ýṹ

  1.��    ��   : 2015��10��06��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBlkSize;
    VOS_UINT16                          usBlkNum;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];
    IMM_ZC_HEAD_STRU                    stQue;

} ADS_IPF_MEM_POOL_STRU;

/*****************************************************************************
 �ṹ��    : ADS_IPF_CTX_STRU
 �ṹ˵��  : ADS��IPF��ص�������
   1.��    ��   : 2012��11��23��
     ��    ��   : L60609
     �޸�����   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    IPF_CONFIG_ULPARAM_S                astIpfUlBdCfgParam[IPF_ULBD_DESC_SIZE]; /* ����BD DESC */
    IPF_RD_DESC_S                       astIpfDlRdDesc[IPF_DLRD_DESC_SIZE];     /* ����RD DESC */
    /* AD */
    IPF_AD_DESC_S                       astIpfDlAdDesc[ADS_DL_ADQ_MAX_NUM][IPF_DLAD0_DESC_SIZE];   /* ����AD DESC */
    ADS_IPF_BD_BUFF_STRU                astIpfUlBdBuff[IPF_ULBD_DESC_SIZE];     /* ����BD */
    IMM_ZC_HEAD_STRU                    stUlSrcMemFreeQue;                      /* IPF�����ڴ��ͷ�BUFF */
    ADS_UL_DYNAMIC_ASSEM_INFO_STRU      stUlAssemParmInfo;                      /* ���ж�̬�����Ϣ */
    VOS_UINT32                          ulThredHoldNum;                         /* �����ް�����ֵ */
    VOS_UINT32                          ulProtectTmrLen;
    VOS_UINT8                           ucSendingFlg;                           /* ���ڷ��ͱ�־ */
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulWakeLockEnable;                       /* wake lock ʹ�ܱ�ʶ */

    struct wake_lock                    stUlBdWakeLock;                         /* wake lock BD */
    struct wake_lock                    stDlRdWakeLock;                         /* wake lock RD */

    struct wake_lock                    stRxWakeLock;                           /* wake lock RX */
    struct wake_lock                    stTxWakeLock;                           /* wake lock TX */

    VOS_UINT32                          ulUlBdWakeLockCnt;                      /* wake lock BD ���� */
    VOS_UINT32                          ulDlRdWakeLockCnt;                      /* wake lock BD ���� */

    VOS_UINT32                          ulRxWakeLockTimeout;                    /* wake lock RX ��ʱʱ�� */
    VOS_UINT32                          ulTxWakeLockTimeout;                    /* wake lock TX ��ʱʱ�� */

    VOS_UINT32                          ulTxWakeLockTmrLen;                     /* wake lock TX ��ʱ���� */
    VOS_UINT32                          ulRxWakeLockTmrLen;                     /* wake lock RX ��ʱ���� */

    struct device                       stDev;
#if (defined(CONFIG_BALONG_SPE))
    VOS_INT32                           lSpeWPort;
    ADS_IPF_MEM_POOL_CFG_STRU           stMemPoolCfg;
    ADS_IPF_MEM_POOL_STRU               astMemPool[ADS_IPF_MEM_POOL_ID_BUTT];
#endif

}ADS_IPF_CTX_STRU;

/*****************************************************************************
�ṹ��    : ADS_SPEC_CTX_STRU
�ṹ˵��  : ADSÿ��ʵ��ר�е�������

  1.��    ��   : 2012��11��23��
    ��    ��   : ³��/l60609
    �޸�����   : DSDA Phase II: ����ADSÿ��ʵ��ר�е�������
*****************************************************************************/
typedef struct
{
    ADS_UL_CTX_STRU                     stAdsUlCtx;                             /* ���������� */
    ADS_DL_CTX_STRU                     stAdsDlCtx;                             /* ���������� */

}ADS_SPEC_CTX_STRU;

/*****************************************************************************
�ṹ��    : ADS_CTX_STRU
�ṹ˵��  : ADS������

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS������

  2.��    ��   : 2012��11��23��
    ��    ��   : L60609
    �޸�����   : DSDA Phase II
*****************************************************************************/
typedef struct
{
    ADS_SPEC_CTX_STRU                   astAdsSpecCtx[ADS_INSTANCE_MAX_NUM];    /* ÿ��ʵ��ר�е������� */
    ADS_STATS_INFO_CTX_STRU             stDsFlowStatsCtx;                       /* ����ͳ�� */
    ADS_IPF_CTX_STRU                    stAdsIpfCtx;                            /* ��IPF��ص������� */
    ADS_TIMER_CTX_STRU                  astAdsTiCtx[ADS_MAX_TIMER_NUM];         /* ��ʱ�������� */
    VOS_UINT8                           ucAdsCurInstanceIndex;                  /* ��ǰʵ����index */
    VOS_UINT8                           ucUlResetFlag;
    VOS_UINT8                           aucRsv[6];
    VOS_SEM                             hULResetSem;                            /* �������ź���������UL��λ����  */
    VOS_SEM                             hDLResetSem;                            /* �������ź���������DL��λ����  */
}ADS_CTX_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

extern VOS_UINT32                       g_ulAdsULTaskId;
extern VOS_UINT32                       g_ulAdsDLTaskId;
extern VOS_UINT32                       g_ulAdsULTaskReadyFlag;
extern VOS_UINT32                       g_ulAdsDLTaskReadyFlag;
extern ADS_CTX_STRU                     g_stAdsCtx;


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_UINT32 ADS_UL_IsAllRabNotSndPermitFlg(VOS_VOID);
VOS_UINT32 ADS_UL_GetSpecInstanceSndPermitFlg(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_DL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_DL_SndEvent(VOS_UINT32 ulEvent);
ADS_DL_CTX_STRU* ADS_GetDlCtx(VOS_UINT8 ucInstanceIndex);
ADS_TIMER_CTX_STRU* ADS_GetTiCtx(VOS_VOID);
ADS_UL_CTX_STRU* ADS_GetUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_InitCtx(VOS_VOID);
VOS_VOID ADS_InitDlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_InitIpfCtx(VOS_VOID);
VOS_VOID ADS_InitSpecCtx(VOS_VOID);
VOS_VOID ADS_InitStatsInfoCtx(VOS_VOID);
VOS_VOID ADS_InitTiCtx(VOS_VOID);
VOS_VOID ADS_InitUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_CheckAllQueueEmpty(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_UL_ClearQueue(
    VOS_UINT8                           ucRabId,
    IMM_ZC_HEAD_STRU                   *pstQueue
);
VOS_UINT32 ADS_UL_CreateQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_DestroyQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetAllQueueDataNum(VOS_VOID);
VOS_UINT32 ADS_UL_GetInsertIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetInstanceAllQueueDataNum(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_InsertQueue(
    VOS_UINT8                           ucInstance,
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_IsQueueExistent(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_OrderQueueIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucIndex
);
VOS_VOID ADS_UL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_SetProtectTmrLen(VOS_UINT32 ulTimerLen);
VOS_VOID ADS_UL_SetQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucIsQueueValid,
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_SndEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_UpdateQueueInPdpDeactived(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_UpdateQueueInPdpModified(
           VOS_UINT8                           ucInstanceIndex,
           ADS_QCI_TYPE_ENUM_UINT8             enPrio,
           VOS_UINT8                           ucRabId
);
ADS_CTX_STRU* ADS_GetAllCtx(VOS_VOID);

VOS_UINT32 ADS_UL_EnableRxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_UL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_UL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_UL_WakeUnLock(VOS_VOID);
VOS_UINT32 ADS_DL_EnableTxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_DL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_DL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_DL_WakeUnLock(VOS_VOID);

VOS_VOID ADS_DL_InitFcAssemParamInfo(VOS_VOID);
VOS_SEM ADS_GetULResetSem(VOS_VOID);
VOS_SEM ADS_GetDLResetSem(VOS_VOID);
VOS_VOID ADS_DL_ResetFcAssemParamInfo(VOS_VOID);
VOS_VOID ADS_ResetSpecUlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_ResetUlCtx(VOS_VOID);
VOS_VOID ADS_ResetSpecDlCtx(VOS_UINT8 ucInstance);
VOS_VOID ADS_ResetDlCtx(VOS_VOID);
VOS_VOID ADS_ResetIpfCtx(VOS_VOID);

VOS_UINT32 ADS_UL_IsAnyQueueExist(VOS_VOID);

VOS_UINT8 ADS_GetUlResetFlag(VOS_VOID);
VOS_VOID  ADS_SetUlResetFlag(VOS_UINT8 ucFlag);

VOS_UINT32 ADS_IPF_IsSpeMem(IMM_ZC_STRU *pstImmZc);
IMM_ZC_STRU* ADS_IPF_AllocMem(VOS_UINT32 ulPoolId, VOS_UINT32 ulLen, VOS_UINT32 ulReserveLen);
dma_addr_t ADS_IPF_GetMemDma(IMM_ZC_STRU *pstImmZc);
VOS_VOID ADS_IPF_SetMemDma(IMM_ZC_STRU *pstImmZc, dma_addr_t ulDmaAddr);
VOS_VOID ADS_IPF_MemMapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemMapByDmaRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemUnmapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);

#if (defined(CONFIG_BALONG_SPE))
VOS_VOID ADS_IPF_InitMemPoolCfg(VOS_VOID);
VOS_VOID ADS_IPF_CreateMemPool(VOS_VOID);
#endif


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

#endif


