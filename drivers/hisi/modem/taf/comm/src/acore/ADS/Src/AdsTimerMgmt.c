
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsTimerMgmt.h"
#include "AdsCtx.h"
#include "AdsDownLink.h"
#include "AdsUpLink.h"
#include "AdsDebug.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_TIMERMGMT_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

ADS_TIMER_OPERATE_STRU                  g_astAdsTmrOperateTbl[] =
{
    { ACPU_PID_ADS_UL,  TI_ADS_UL_SEND,         VOS_TIMER_PRECISION_5,  {0},    ADS_UL_RcvTiSendExpired     },
    { ACPU_PID_ADS_UL,  TI_ADS_DSFLOW_STATS,    VOS_TIMER_NO_PRECISION, {0},    VOS_NULL_PTR                },
    { ACPU_PID_ADS_DL,  TI_ADS_DL_ADQ_EMPTY,    VOS_TIMER_PRECISION_0,  {0},    ADS_DL_RcvTiAdqEmptyExpired },
    { ACPU_PID_ADS_UL,  TI_ADS_UL_DATA_STAT,    VOS_TIMER_NO_PRECISION, {0},    VOS_NULL_PTR                }

};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : ADS_MNTN_TraceTimerOperation
 ��������  : ������Ϣ��OMģ�飬ADS��ʱ������״̬
 �������  : ulPid         - PID
             enTimerId     - ��ʱ��ID
             ulTimerLen    - ��ʱ��ʱ��
             enTimerStatus - ��ʱ��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��22��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  ADS_MNTN_TraceTimerOperation(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulTimerLen,
    ADS_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
)
{
    ADS_TIMER_INFO_STRU                 stMsg = {0};

    stMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid       = ulPid;
    stMsg.ulReceiverPid     = VOS_PID_TIMER;
    stMsg.ulLength          = sizeof(ADS_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stMsg.enTimerId         = enTimerId;
    stMsg.ulTimerLen        = ulTimerLen;
    stMsg.enTimerAction     = enTimerAction;
    stMsg.enTimerStopCause  = enStopCause;
    stMsg.aucReserved[0]    = 0;
    stMsg.aucReserved[1]    = 0;

    DIAG_TraceReport(&stMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_StartTimer
 ��������  : ADS������ʱ��
 �������  : VOS_UINT32                          ulPid
             ADS_TIMER_ID_ENUM_UINT32            enTimerId
             VOS_UINT32                          ulLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��14��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013092200927: ��ʱ��ʹ���Ż�

  3.��    ��   : 2016��01��25��
    ��    ��   : w00316404
    �޸�����   : DTS2016010709647: ��ʱ��ʹ�þ���жϲ��Ż�

  4.��    ��   : 2016��2��22��
    ��    ��   : A00165503
    �޸�����   : DTS2016022200697: ȥ��������ղ���, ��ֹ��ʱ����Դά���쳣

*****************************************************************************/
VOS_VOID  ADS_StartTimer(
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulLen
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx      = VOS_NULL_PTR;
    ADS_TIMER_OPERATE_STRU             *pstTmrOperate = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_UL,
            "ADS_StartTimer: timer id is invalid. <enTimerId>", enTimerId);
        return;
    }


    /* ��ȡ��ʱ�������� */
    pstTmrOperate = &(g_astAdsTmrOperateTbl[enTimerId]);
    pstTiCtx      = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    /* ��ʱ�����ȼ�� */
    if (0 == ulLen)
    {
        ADS_ERROR_LOG(pstTmrOperate->ulPid,
            "ADS_StartTimer: timer len is 0,");
        return;
    }

    /* ��ʱ�������� */
    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        return;
    }

    /* ������ʱ�� */
    if (VOS_NULL_PTR == pstTmrOperate->pfnTimerStartCallBack)
    {
        ulRet = VOS_StartRelTimer(&(pstTiCtx->hTimer),
                                  pstTmrOperate->ulPid,
                                  ulLen,
                                  enTimerId,
                                  0,
                                  VOS_RELTIMER_NOLOOP,
                                  pstTmrOperate->enPrecision);
    }
    else
    {
        ulRet = VOS_StartCallBackRelTimer(&(pstTiCtx->hTimer),
                                          pstTmrOperate->ulPid,
                                          ulLen,
                                          enTimerId,
                                          0,
                                          VOS_RELTIMER_NOLOOP,
                                          pstTmrOperate->pfnTimerStartCallBack,
                                          pstTmrOperate->enPrecision);
    }

    if (VOS_OK != ulRet)
    {
        ADS_ERROR_LOG1(pstTmrOperate->ulPid,
            "ADS_StartTimer: timer start failed! <ret>", ulRet);
        return;
    }

    /*����ADS_TIMER_INFO_STRU*/
    ADS_MNTN_TraceTimerOperation(pstTmrOperate->ulPid, enTimerId, ulLen, ADS_TIMER_OPERATION_START, ADS_TIMER_STOP_CAUSE_ENUM_BUTT);

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_StopTimer
 ��������  : ADSֹͣ��ʱ��
 �������  : VOS_UINT32                          ulPid
             ADS_TIMER_ID_ENUM_UINT32            enTimerId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2016��2��22��
    ��    ��   : A00165503
    �޸�����   : DTS2016022200697: ȥ��������ղ���, ��ֹ��ʱ����Դά���쳣

*****************************************************************************/
VOS_VOID ADS_StopTimer(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    ADS_TIMER_STOP_CAUSE_ENUM_UINT8     enStopCause
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx = VOS_NULL_PTR;

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_UL,
            "ADS_StopTimer: timer id is invalid. <enTimerId>", enTimerId);
        return;
    }

    /* ��ȡ��ʱ�������� */
    pstTiCtx = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    /* ֹͣ��ʱ�� */
    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstTiCtx->hTimer));
    }

    /*����ADS_TIMER_INFO_STRU*/
    ADS_MNTN_TraceTimerOperation(ulPid, enTimerId, 0, ADS_TIMER_OPERATION_STOP, enStopCause);

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_GetTimerStatus
 ��������  : ��ȡADS��ʱ����״̬
 �������  : VOS_UINT32                          ulPid
             ADS_TIMER_ID_ENUM_UINT32            enTimerId
 �������  : ��
 �� �� ֵ  : ADS_TIMER_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013092200927: ��ʱ��ʹ���Ż�

  3.��    ��   : 2016��2��22��
    ��    ��   : A00165503
    �޸�����   : DTS2016022200697: ȥ��������ղ���, ��ֹ��ʱ����Դά���쳣

*****************************************************************************/
ADS_TIMER_STATUS_ENUM_UINT8 ADS_GetTimerStatus(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId
)
{
    ADS_TIMER_CTX_STRU                 *pstTiCtx = VOS_NULL_PTR;

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= ADS_MAX_TIMER_NUM)
    {
        return ASD_TIMER_STATUS_BUTT;
    }

    /* ��ȡ��ʱ�������� */
    pstTiCtx = &(g_stAdsCtx.astAdsTiCtx[enTimerId]);

    /* ��鶨ʱ����� */
    if (VOS_NULL_PTR != pstTiCtx->hTimer)
    {
        return ADS_TIMER_STATUS_RUNNING;
    }

    return ADS_TIMER_STATUS_STOP;
}


