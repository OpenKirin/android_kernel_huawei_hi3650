

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicTimerMgmt.h"
#include "RnicCtx.h"
#include "v_timer.h"
#include "RnicLog.h"
#include "mdrv.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_TIMERMGMT_C
/*lint -e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : RNIC_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��RNIC��ʼ����Resetʱ������
 �������  : pstRnicTimerCtx:��ʱ���������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  RNIC_InitAllTimers(
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 �� �� ��  : RNIC_StartTimer
 ��������  : ����ָ����RNIC��ʱ��
 �������  : enTimerId:��Ҫ�����Ķ�ʱ��ID
             ulLen    :��ʱ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��22��
    ��    ��   : A00165503
    �޸�����   : DTS2012052202998: ϵͳ������״̬��, ���貦���������ʱ�䵽
                 ���, �����޷��Զ��Ͽ�, ��ʱ����Ҫʹ��32Kʱ��Դ

  3.��    ��   : 2012��6��6��
    ��    ��   : z60575
    �޸�����   : DTS2012060508406������Ͽ�ʱ����׼�����޸�

  4.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt     = VOS_NULL_PTR;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;
    VOS_UINT32                          ulRet;

    /* Ŀǰ���貦�ŵĹ���ֻ������0���� */
    pstNetCntxt      = RNIC_GET_SPEC_NET_CTX(RNIC_RMNET_ID_0);
    pstRnicTimerCtx  = RNIC_GetTimerAddr();
    enTimerPrecision = VOS_TIMER_PRECISION_5;

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* ���������� */
    if (0 == ulLen)
    {
        RNIC_ERROR_LOG1(ACPU_PID_ADS_UL, "ADS_StartTimer:ulLen is",ulLen);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    /* �����δ���û���Դ��־�������ǰ���Ͽ���ʱ���������øñ�־����������32Kʱ��Ϊ����Դ */
    if ((VOS_FALSE == RNIC_GetTimer4WakeFlg())
      && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_SetTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_TRUE);
    }

     /* ����������ϱ���ʱ���������26Mʱ���ϣ��Խ��͹��� */
    if (RNIC_IS_DSFLOW_TIMER_ID(enTimerId))
    {
        enTimerPrecision = VOS_TIMER_NO_PRECISION;
    }


    /* VOS_StartRelTimer ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer),
                              ACPU_PID_RNIC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              enTimerPrecision);
    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");
        return;
    }

    if (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId)
    {
        /* ���貦��ͳ������ */
        pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum = 0;
    }

    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_RUNING;


    /* ��ʱ��״̬�������� */

}


/*****************************************************************************
 �� �� ��  : RNIC_StopTimer
 ��������  : ָֹͣ����RNIC��ʱ��
 �������  : enTimerId:��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��6��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ�ʱ����׼�����޸�
*****************************************************************************/
VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* û����������Ҫֹͣ */
    if (RNIC_TIMER_STATUS_RUNING  != pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstRnicTimerCtx[enTimerId].hTimer)
    {
        VOS_StopRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer));
    }

    pstRnicTimerCtx[enTimerId].hTimer        = VOS_NULL_PTR;
    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_STOP;

    /* ��ʱ��״̬�������� */
    /* ����Ѿ������˻���Դ��־�������ǰ���Ͽ���ʱ����������ñ�־����������32Kʱ��Ϊ�ǻ���Դ */
    if ((VOS_TRUE == RNIC_GetTimer4WakeFlg())
     && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
}


/*****************************************************************************
 �� �� ��  : RNIC_StopAllTimer
 ��������  : ֹͣRNIC�����ж�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��6��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ�ʱ����׼�����޸�
*****************************************************************************/
VOS_VOID  RNIC_StopAllTimer( VOS_VOID )
{

    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if (RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus)
        {
            /* ֹͣVOS��ʱ�� */
            VOS_StopRelTimer(&(pstRnicTimerCtx[i].hTimer));

            pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
        }
    }

    /* ����Ѿ������˻���Դ��־��������ñ�־����������32Kʱ��Ϊ�ǻ���Դ */
    if (VOS_TRUE == RNIC_GetTimer4WakeFlg())
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
}


/*****************************************************************************
 �� �� ��  : RNIC_GetTimerStatus
 ��������  : ��ѯָ����RNIC��ʱ����״̬
 �������  : enTimerId:��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : RNIC_TIMER_STATUS_ENUM_UINT8:��ʱ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          ulLeftLen;

    pstRnicTimerCtx = RNIC_GetTimerAddr();
    ulLeftLen       = 0;

    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return RNIC_TIMER_STATUS_STOP;
    }

    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        if (VOS_OK != (VOS_GetRelTmRemainTime(&(pstRnicTimerCtx[enTimerId].hTimer), &ulLeftLen)))
        {
            RNIC_StopTimer(enTimerId);
            return RNIC_TIMER_STATUS_STOP;
        }
        else
        {
            return RNIC_TIMER_STATUS_RUNING;
        }
    }

    return RNIC_TIMER_STATUS_STOP;

}



