

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicCtx.h"
#include "RnicProcMsg.h"
#include "AtRnicInterface.h"
#include "v_typdef.h"
#include "RnicTimerMgmt.h"
#include "mdrv.h"
#include "RnicEntity.h"
#include "AdsDeviceInterface.h"
#include "RnicLog.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "RnicDebug.h"

#include "AcpuReset.h"

#include "ImsaRnicInterface.h"

#include "RnicCdsInterface.h"

#include "SdioInterface.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_PROCMSG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* RNICģ�鶨ʱ����ʱ��Ϣ��������Ӧ�� */
const RNIC_RCV_TI_EXPRIED_PROC_STRU g_astRnicTiExpriedProcTab[]=
{
    /* ��ϢID */                            /* ��ʱ����ʱ������ */
    {TI_RNIC_DSFLOW_STATS_0,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_1,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_2,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_3,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_4,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_5,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DSFLOW_STATS_6,                RNIC_RcvTiDsflowStatsExpired},
    {TI_RNIC_DEMAND_DIAL_DISCONNECT,        RNIC_RcvTiDemandDialDisconnectExpired},
    {TI_RNIC_DEMAND_DIAL_PROTECT,           RNIC_RcvTiDemandDialProtectExpired}
 };

/* Deleted by wx270776 for OM�ں�, 2015-08-21, Begin */
/* Deleted by wx270776 for OM�ں�, 2012-08-21, End */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : RNIC_MNTN_TraceDialConnEvt
 ��������  : ��ά�ɲ⹳��: ������������¼�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012061800997: �޸İ��貦�ſ�ά�ɲ⹳����ʽ
  3.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID RNIC_MNTN_TraceDialConnEvt(VOS_VOID)
{
    RNIC_MNTN_DIAL_CONN_EVT_STRU       *pstDialEvt = VOS_NULL_PTR;

    /* ������Ϣ */
    pstDialEvt = (RNIC_MNTN_DIAL_CONN_EVT_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        ACPU_PID_RNIC,
                        sizeof(RNIC_MNTN_DIAL_CONN_EVT_STRU));
    if (VOS_NULL_PTR == pstDialEvt)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialEvent: Memory alloc failed.");
        return;
    }

    /* ��д��Ϣ */
    pstDialEvt->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDialEvt->ulReceiverPid   = ACPU_PID_RNIC;
    pstDialEvt->enMsgId         = ID_RNIC_MNTN_EVT_DIAL_CONNECT;

    /* ������ά�ɲ���Ϣ */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDialEvt))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialConnEvt():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_MNTN_TraceDialDisconnEvt
 ��������  : ��ά�ɲ⹳��: ������ŶϿ��¼�
 �������  : ulPktNum      - ���ŶϿ�ʱ�յ������ݰ�����
             ulUsrExistFlg - �û�����״̬(USB����WIFI)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012061800997: �޸İ��貦�ſ�ά�ɲ⹳����ʽ
  3.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID RNIC_MNTN_TraceDialDisconnEvt(
    VOS_UINT32                          ulPktNum,
    VOS_UINT32                          ulUsrExistFlg
)
{
    RNIC_MNTN_DIAL_DISCONN_EVT_STRU    *pstDialEvt = VOS_NULL_PTR;

    /* ������Ϣ */
    pstDialEvt = (RNIC_MNTN_DIAL_DISCONN_EVT_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        ACPU_PID_RNIC,
                        sizeof(RNIC_MNTN_DIAL_DISCONN_EVT_STRU));
    if (VOS_NULL_PTR == pstDialEvt)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialEvent: Memory alloc failed.");
        return;
    }

    /* ��д��Ϣͷ */
    pstDialEvt->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDialEvt->ulReceiverPid   = ACPU_PID_RNIC;
    pstDialEvt->enMsgId         = ID_RNIC_MNTN_EVT_DIAL_DISCONNECT;

    /* ��д��Ϣ���� */
    pstDialEvt->ulPktNum        = ulPktNum;
    pstDialEvt->ulUsrExistFlg   = ulUsrExistFlg;

    /* ������ά�ɲ���Ϣ */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDialEvt))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_MNTN_TraceDialDisconnEvt():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_SendDialEvent
 ��������  : RNICͨ��netlink֪ͨAPP���Ż�Ͽ�
 �������  : ulDeviceId :�豸��
             ulEventId  :�¼�ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��13��
   ��    ��   : S62952
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_SendDialEvent(
    VOS_UINT32                          ulDeviceId,
    VOS_UINT32                          ulEventId
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSize;
    DEVICE_EVENT                        stEvent;

    ulSize                              = sizeof(DEVICE_EVENT);
    stEvent.device_id                   = (DEVICE_ID)ulDeviceId;
    stEvent.event_code                  = (VOS_INT)ulEventId;
    stEvent.len                         = 0;

    /* �ϱ����貦���¼�*/
    ulRet = (VOS_UINT32)device_event_report(&stEvent, (VOS_INT)ulSize);

    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "RNIC_SendDialEvent: can't add event");
        return VOS_ERR;
    }

    RNIC_INFO_LOG2(ACPU_PID_RNIC, "RNIC_SendDialEvent Done ulEventId  ulDeviceId",ulEventId,ulDeviceId);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : RNIC_GetDsflowTimerIdByNetId
 ��������  : ͨ������ID�õ�����ͳ�ƶ�ʱ��ID
 �������  : ucRmNetId :����ID
 �������  : ��
 �� �� ֵ  : RNIC_TIMER_ID_ENUM_UINT16 ��ʱ��ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��28��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
RNIC_TIMER_ID_ENUM_UINT16 RNIC_GetDsflowTimerIdByNetId(VOS_UINT8 ucRmNetId)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;

    switch (ucRmNetId)
    {
        case RNIC_RMNET_ID_0 :
            enTimerId = TI_RNIC_DSFLOW_STATS_0;
            break;

        case RNIC_RMNET_ID_1 :
            enTimerId = TI_RNIC_DSFLOW_STATS_1;
            break;

        case RNIC_RMNET_ID_2 :
            enTimerId = TI_RNIC_DSFLOW_STATS_2;
            break;

        case RNIC_RMNET_ID_3 :
            enTimerId = TI_RNIC_DSFLOW_STATS_3;
            break;

        case RNIC_RMNET_ID_4 :
            enTimerId = TI_RNIC_DSFLOW_STATS_4;
            break;
        case RNIC_RMNET_ID_5 :
            enTimerId = TI_RNIC_DSFLOW_STATS_5;
            break;

        case RNIC_RMNET_ID_6 :
            enTimerId = TI_RNIC_DSFLOW_STATS_6;
            break;

        default :
            enTimerId = TI_RNIC_TIMER_BUTT;
            break;
    }

    return enTimerId;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetNetIdByTimerId
 ��������  : ���ݶ�ʱ��ID��ȡ����ID
 �������  : ucRmNetId :����ID
 �������  : ��
 �� �� ֵ  : VOS_UINT8 ����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��28��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT8 RNIC_GetNetIdByTimerId(VOS_UINT32 ulMsgId)
{
    VOS_UINT8                           ucRmNedId;

    switch (ulMsgId)
    {
        case TI_RNIC_DSFLOW_STATS_0 :
            ucRmNedId = RNIC_RMNET_ID_0;
            break;

        case TI_RNIC_DSFLOW_STATS_1 :
            ucRmNedId = RNIC_RMNET_ID_1;
            break;

        case TI_RNIC_DSFLOW_STATS_2 :
            ucRmNedId = RNIC_RMNET_ID_2;
            break;

        case TI_RNIC_DSFLOW_STATS_3 :
            ucRmNedId = RNIC_RMNET_ID_3;
            break;

        case TI_RNIC_DSFLOW_STATS_4 :
            ucRmNedId = RNIC_RMNET_ID_4;
            break;
        case TI_RNIC_DSFLOW_STATS_5 :
            ucRmNedId = RNIC_RMNET_ID_5;
            break;

        case TI_RNIC_DSFLOW_STATS_6 :
            ucRmNedId = RNIC_RMNET_ID_6;
            break;

        case TI_RNIC_DEMAND_DIAL_DISCONNECT :
        case TI_RNIC_DEMAND_DIAL_PROTECT :
            ucRmNedId = RNIC_RMNET_ID_0;
            break;

        default :
            ucRmNedId = RNIC_RMNET_ID_BUTT;
            break;
    }

    return ucRmNedId;
}

/*****************************************************************************
 �� �� ��  : RNIC_BuildRabIdByModemId
 ��������  : ����ModemId����Rabid
 �������  : enModemId : Modem ID
             ucRabId   : RabId
 �������  : pucRabId  : ���ɵ�RabId
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��06��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��28��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 RNIC_BuildRabIdByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucRabId
)
{
    if (MODEM_ID_0 == enModemId)
    {
        /* Modem0��RABID�ĸ���λ��00��ʾ */
        *pucRabId = ucRabId;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        /* Modem1��RABID�ĸ���λ��01��ʾ */
        *pucRabId = ucRabId | RNIC_RABID_TAKE_MODEM_1_MASK;
    }
    else if (MODEM_ID_2 == enModemId)
    {
        /* Modem2��RABID�ĸ���λ��10��ʾ */
        *pucRabId = ucRabId | RNIC_RABID_TAKE_MODEM_2_MASK;
    }
    else
    {
        /* �Ȳ���Modem0Ҳ����Modem1�ģ�����ʧ�� */
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_SaveNetIdByRabId
 ��������  : ����rabid�洢����ID
 �������  : enModemId : Modem ID
             ucRmNetId : ����ID
             ucRabId   : RabId
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��10��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_SaveNetIdByRabId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_RABID_INFO_STAU               *pstRabIdInfo;

    if ((ucRabId < RNIC_RAB_ID_MIN)
     || (ucRabId > RNIC_RAB_ID_MAX))
    {
        return VOS_ERR;
    }

    /* ��ȡָ��Modem��RABID��Ϣ */
    pstRabIdInfo = RNIC_GET_SPEC_MODEM_RABID_INFO(enModemId);

    pstRabIdInfo->aucRmNetId[ucRabId - RNIC_RAB_ID_OFFSET] = ucRmNetId;

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : RNIC_RcvIpv4PdpActInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_IPV4_PDP_ACT_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��1��31��
   ��    ��   : w00199382
   �޸�����   : ���ű�����ʱ����ʱɾ��
 3.��    ��   : 2012��6��6��
   ��    ��   : A00165503
   �޸�����   : DTS2012060502819: �����ʽ�������貦��, ����Ƶ���ϱ��¼�
 4.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��

 5.��    ��   : 2014��11��7��
   ��    ��   : y00218312
   �޸�����   : ����CDMAģʽ�µĴ���
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtIpv4PdpActInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id������id�����Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4PdpActInd, RabId:%d", pstRcvInd->ucRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstRcvInd->ucRabId;
    pstPdpAddr->stIpv4PdpInfo.ulIpv4Addr  = pstRcvInd->ulIpv4Addr;



    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ֹͣ���貦�ű�����ʱ�� */
    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);
    }


    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);


    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvIpv6PdpActInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_IPV6_PDP_ACT_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
 3.��    ��   : 2015��1��22��
   ��    ��   : Y00213812
   �޸�����   : ����CDMAģʽ��PPP��ACUPʱ�Ĵ���
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtIpv6PdpActInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id������id�����Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv6PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv6PdpActInd, RabId:%d", pstRcvInd->ucRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstRcvInd->ucRabId;
    VOS_MemCpy(pstPdpAddr->stIpv6PdpInfo.aucIpv6Addr,
               pstRcvInd->aucIpv6Addr,
               RNICITF_MAX_IPV6_ADDR_LEN);


    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */


    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);



    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : RNIC_RcvIpvv46PdpActInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_IPV4V6_PDP_ACT_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��6��
   ��    ��   : A00165503
   �޸�����   : DTS2012060502819: �����ʽ�������貦��, ����Ƶ���ϱ��¼�
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
 4.��    ��   : 2015��1��22��
   ��    ��   : Y00213812
   �޸�����   : ����CDMAģʽ��PPP��ACUPʱ�Ĵ���

*****************************************************************************/
VOS_UINT32 RNIC_RcvAtIpv4v6PdpActInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU    *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_IPV4V6_PDP_ACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id������id�����Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4v6PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtIpv4v6PdpActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType          = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4v6PdpInfo.ucRabId     = pstRcvInd->ucRabId;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = pstRcvInd->ucRabId;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = pstRcvInd->ucRabId;



    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ֹͣ���貦�ű�����ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);


    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);


    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : RNIC_RcvPdpDeactInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_PDP_DEACT_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��16��
   ��    ��   : z60575
   �޸�����   : DTS2012061502207: �ϱ�����Ͽ�ʱ��ʱ����ͶƱ��˯�ߣ�����Ӧ��
                ������Ϣǰ�ֽ�����˯
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtPdpDeactInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;

    pstRcvInd                           = (AT_RNIC_PDP_DEACT_IND_STRU *)pstMsg;
    ucRmNetId                           = pstRcvInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* �����IPV4 PDPȥ���� */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* ���IPV4 PDP��������Ϣ */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);

        /* ������0�ϲ��а��貦�ŵĹ��� */
        if (RNIC_RMNET_ID_0 == ucRmNetId)
        {
            /* ֹͣ���貦�ŶϿ���ʱ�� */
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

            /* ��ղ��ŶϿ���ʱ����ʱͳ�� */
            RNIC_ClearTiDialDownExpCount();
        }
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* ���IPV6 PDP��������Ϣ */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstRcvInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ���IPV4V6 PDP��������Ϣ */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP��δ�����ʱ�� */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ֹͣ����ͳ�ƶ�ʱ�� */
        RNIC_StopTimer(enTimerId);

        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucRmNetId);

        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */
    }

    /* �ڶϿ����ųɹ�ʱ���ͶƱ˯�ߣ��Ա��ܽ�����˯ */
    DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_RNIC);

    /* ���RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvAtDialModeReq
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_DIAL_MODE_REQ�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��21��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtDialModeReq(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_DIAL_MODE_REQ_STRU         *pstRcvInd;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_AT_DIAL_MODE_CNF_STRU         *pstSndMsg;

    /* �ڴ���� */
    pstSndMsg = (RNIC_AT_DIAL_MODE_CNF_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_AT_DIAL_MODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSndMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDialModeReq: Malloc failed!");
        return VOS_ERR;
    }

    pstRcvInd                           = (AT_RNIC_DIAL_MODE_REQ_STRU *)pstMsg;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();
    pstSndMsg->clientId                 = pstRcvInd->clientId;
    pstSndMsg->ulDialMode               = pstDialMode->enDialMode;
    pstSndMsg->ulIdleTime               = pstDialMode->ulIdleTime;
    pstSndMsg->ulEventReportFlag        = pstDialMode->enEventReportFlag;

    /* ͨ��ID_RNIC_AT_DIAL_MODE_CNF��Ϣ���͸�ATģ�� */
    /* �����Ϣ */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = ACPU_PID_RNIC;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->enMsgId                  = ID_RNIC_AT_DIAL_MODE_CNF;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstSndMsg))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDialModeReq: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvDsflowInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_DSFLOW_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtDsflowInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstRcvInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_AT_DSFLOW_RSP_STRU            *pstDsflowRsp;

    /* �ڴ���� */
    pstDsflowRsp = (RNIC_AT_DSFLOW_RSP_STRU *)PS_ALLOC_MSG(ACPU_PID_RNIC,
                        sizeof(RNIC_AT_DSFLOW_RSP_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstDsflowRsp)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDsflowInd: Malloc failed!");
        return VOS_ERR;
    }

    pstRcvInd                               = (AT_RNIC_DSFLOW_IND_STRU *)pstMsg;
    pstDsflowRsp->clientId                  = pstRcvInd->clientId;

    pstPdpAddr                              = RNIC_GetPdpCtxAddr(pstRcvInd->enRnicRmNetId);

    /* ��ƷҪ��δ���Ϻţ�����Ϊ0 */
    pstDsflowRsp->stRnicDataRate.ulDLDataRate = 0;
    pstDsflowRsp->stRnicDataRate.ulULDataRate = 0;

    /* PDP�����ʱ�򣬻�ȡ��ǰ������������ */
    if ((RNIC_PDP_REG_STATUS_ACTIVE == pstPdpAddr->stIpv4PdpInfo.enRegStatus)
     || (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpAddr->stIpv6PdpInfo.enRegStatus)
     || (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        pstDsflowRsp->stRnicDataRate.ulDLDataRate = RNIC_GetCurrentDlRate(pstRcvInd->enRnicRmNetId);
        pstDsflowRsp->stRnicDataRate.ulULDataRate = RNIC_GetCurrentUlRate(pstRcvInd->enRnicRmNetId);
    }

    /* ͨ��ID_RNIC_AT_DSFLOW_RSP��Ϣ���͸�ATģ�� */
    /* �����Ϣ */
    pstDsflowRsp->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstDsflowRsp->ulSenderPid                 = ACPU_PID_RNIC;
    pstDsflowRsp->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstDsflowRsp->ulReceiverPid               = WUEPS_PID_AT;
    pstDsflowRsp->enMsgId                     = ID_RNIC_AT_DSFLOW_RSP;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ACPU_PID_RNIC, pstDsflowRsp))
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvAtDsflowInd: Send msg failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvAtPdnInfoCfgInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_PDN_INFO_CFG_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtPdnInfoCfgInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_PDN_INFO_CFG_IND_STRU      *pstRnicPdnCfgInd;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;

    PS_MEM_SET(&stFilterIpAddr, 0, sizeof(ADS_FILTER_IP_ADDR_INFO_STRU));
    pstRnicPdnCfgInd = (AT_RNIC_PDN_INFO_CFG_IND_STRU *)pstMsg;
    ucRmNetId        = pstRnicPdnCfgInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id���Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRnicPdnCfgInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtPdnInfoCfgInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRnicPdnCfgInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtPdnInfoCfgInd, RabId:%d", pstRnicPdnCfgInd->ucRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    if (VOS_TRUE == pstRnicPdnCfgInd->bitOpIpv4PdnInfo)
    {
        /* ����PDP��������Ϣ */
        pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstRnicPdnCfgInd->ucRabId;
        pstPdpAddr->stIpv4PdpInfo.ulIpv4Addr  = pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr;

        /* ���¹���IP��ַ��Ϣ */
        stFilterIpAddr.bitOpIpv4Addr          = VOS_TRUE;
        PS_MEM_CPY(stFilterIpAddr.aucIpv4Addr,
                   (VOS_UINT8 *)&pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr,
                   ADS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstRnicPdnCfgInd->bitOpIpv6PdnInfo)
    {
        /* ����PDP��������Ϣ */
        pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstRnicPdnCfgInd->ucRabId;
        PS_MEM_CPY(pstPdpAddr->stIpv6PdpInfo.aucIpv6Addr,
                   pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   RNICITF_MAX_IPV6_ADDR_LEN);

        /* ���¹���IP��ַ��Ϣ */
        stFilterIpAddr.bitOpIpv6Addr          = VOS_TRUE;
        PS_MEM_CPY(stFilterIpAddr.aucIpv6Addr,
                   pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   ADS_IPV6_ADDR_LEN);
    }

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ע�����й��˻ص�������ADS����ע��ĺ��������������� */
    ADS_DL_RegFilterDataCallback(ucRabid, &stFilterIpAddr, (RCV_DL_DATA_FUNC)RNIC_RcvAdsDlData);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvAtPdnInfoRelInd
 ��������  : RNIC�յ�AT��ϢID_AT_RNIC_PDN_INFO_REL_REQ�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtPdnInfoRelInd(
    MsgBlock                           *pstMsg
)
{
    AT_RNIC_PDN_INFO_REL_IND_STRU      *pstRnicPdnRelInd;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;

    pstRnicPdnRelInd = (AT_RNIC_PDN_INFO_REL_IND_STRU *)pstMsg;

    ucRmNetId                           = pstRnicPdnRelInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ����PDP��������Ϣ */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstRnicPdnRelInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* ���IPV4 PDP��������Ϣ */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstRnicPdnRelInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* ���IPV6 PDP��������Ϣ */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstRnicPdnRelInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ���IPV4V6 PDP��������Ϣ */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP��δ�����ʱ�� */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ֹͣ����ͳ�ƶ�ʱ�� */
        RNIC_StopTimer(enTimerId);

        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
        pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;
        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucRmNetId);
    }

    /* ���RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRnicPdnRelInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return VOS_ERR;
    }

    /* ȥע�����й��˻ص����� */
    ADS_DL_DeregFilterDataCallback(pstRnicPdnRelInd->ucRabId);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvTiAppDsflowExpired
 ��������  : ����ͳ�ƶ�ʱ����ʱ��������RNIC�����е�ǰ������
 �������  : pstMsg:��ʱ����Ϣ�׵�ַ
             enRmNetId:����ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��02��
   ��    ��   : f00179208
   �޸�����   : ���ⵥ;DTS2012032406513,���������У���ѯ����Ϊ0
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32  RNIC_RcvTiDsflowStatsExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulTaBytes;
    VOS_UINT32                          ulRate;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;

    /* ��ȡ�����ĵ�ַ */
    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(ucRmNetId);

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId   = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* Added by f00179208 for DTS2012032406513��2012-03-24 Begin */
    RNIC_StopTimer(enTimerId);
    /* Added by f00179208 for DTS2012032406513��2012-03-24 End */

    /* ��ȡ2����������� */
    ulTaBytes   = pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow;

    /* ��ƷҪ��ÿ2���Ӽ���һ��,��λΪ:byte/s */
    ulRate = ulTaBytes>>1;
    RNIC_SetCurrentDlRate(ulRate, ucRmNetId);

    /* ��ȡ2����������� */
    ulTaBytes   = pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow;

    /* ��ƷҪ��ÿ2���Ӽ���һ��,��λΪ:byte/s */
    ulRate      = ulTaBytes>>1;
    RNIC_SetCurrentUlRate(ulRate, ucRmNetId);

    /* ÿ������ͳ�����ڽ�������Ҫ������ͳ��Byte����� */
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow = 0;

    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvTiAppDemandDialDownExpired
 ��������  : ���ŶϿ���ʱ����ʱ����֪ͨӦ�öϿ�����
 �������  : pstMsg:��ʱ����Ϣ�׵�ַ
             enRmNetId - ����ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��02��
   ��    ��   : w00199382
   �޸�����   : DTS201203025734
 3.��    ��   : 2012��6��6��
   ��    ��   : A00165503
   �޸�����   : DTS2012060502819: �����ʽ�������貦��, ����Ƶ���ϱ��¼�
 4.��    ��   : 2012��6��15��
   ��    ��   : z60575
   �޸�����   : DTS2012061502207: �ϱ�����Ͽ�ʱ��ʱ����ͶƱ��˯�ߣ�����Ӧ��
                ������Ϣǰ�ֽ�����˯
 5.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_RcvTiDemandDialDisconnectExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_UINT32                          ulPktsNum;
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulUserExistFlg;
    VOS_UINT32                          ulExpiredCount;

    /* ��ȡ�����ĵ�ַ */
    pstNetCntxt     = RNIC_GET_SPEC_NET_CTX(ucRmNetId);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode     = RNIC_GetDialModeAddr();

    /* ���û����õ�ʱ������ʱ��ʱ���ȷ� */
    ulExpiredCount  = (pstDialMode->ulIdleTime * TI_RNIC_UNIT) / TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN;

    /* Added by w00199382 for DTS201203025734��2012-03-02,  Begin */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    /* Added by w00199382 for DTS201203025734��2012-03-02,  End */

    /* �����ǰ���ֶ�����,��ֱ�ӷ���,����Ҫ֪ͨ */
    if (RNIC_DIAL_MODE_DEMAND_CONNECT != pstDialMode->enDialMode)
    {
        RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_RcvTiDemandDialDisconnectExpired: Dialmode is manual!");
        return VOS_OK;
    }

    /* ��ȡ�ڶ�ʱ��������������ͳ�Ƶ����ݰ����Լ���ǰ�û�����״̬ */
    ulPktsNum = pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum;
    ulUserExistFlg  = DRV_AT_GET_USER_EXIST_FLAG();

    /* ���貦�ŶϿ��߼�����:
         ���û������������ݰ�:
             ����������
         �������:
             ������++
       ���³����޷�ʶ��:
          ��ǰ����USB�����û������ݷ��ͣ��������������·�������Ҳ����Ϊ
          �����û������������ݰ��������¼�����
    */
    if ((0 != ulPktsNum)
     && (VOS_TRUE == ulUserExistFlg))
    {
        RNIC_ClearTiDialDownExpCount();
    }
    else
    {
        RNIC_IncTiDialDownExpCount();
    }

    /* �ж�ͳ�Ƽ������Ƿ���ڵ����û����öϿ�����ʱ���붨ʱ��ʱ���ȷ� */
    ulCount = RNIC_GetTiDialDownExpCount();

    if ((ulCount >= ulExpiredCount)
       &&(RNIC_ALLOW_EVENT_REPORT == pstDialMode->enEventReportFlag))
    {
        /*֪ͨӦ�öϿ����� */
        if (VOS_OK == RNIC_SendDialEvent(DEVICE_ID_WAN, RNIC_DAIL_EVENT_DOWN))
        {
            /* �ϱ��Ͽ������¼���ͶƱ������˯�ߣ��ڶϿ����ųɹ�ʱ��� */
            DRV_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_RNIC);
            RNIC_DBG_SEND_APP_DIALDOWN_SUCC_NUM(1, ucRmNetId);

            RNIC_WARNING_LOG(ACPU_PID_RNIC, "RNIC_ProcUlIpv4DataInPdpDeactive:Send Act PDP Msg to APP");
        }
        else
        {
            RNIC_DBG_SEND_APP_DIALDOWN_FAIL_NUM(1, ucRmNetId);
        }

        RNIC_MNTN_TraceDialDisconnEvt(ulPktsNum, ulUserExistFlg);
    }

    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvTiDemandDialProtectExpired
 ��������  : ���ű�����ʱ����ʱ����, ��ʽֹͣ��ʱ��, ��ʱ��״̬��Ϊֹͣ
 �������  : pstMsg  - ��ʱ����Ϣ
             enRmNetId - ����ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_RcvTiDemandDialProtectExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
)
{
    /* ֹͣ���貦�ű�����ʱ�� */
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetTiExpiredFuncByMsgId
 ��������  : ��ȡ��Ϣ������
 �������  : ulMsgId            - ��ϢID
 �������  : ��
 �� �� ֵ  : pTiExpriedProcFunc - ��ʱ����ʱ��������ַ
             VOS_NULL_PTR       - ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��28��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
RNIC_RCV_TI_EXPRIED_PROC_FUNC RNIC_GetTiExpiredFuncByMsgId(VOS_UINT32 ulMsgId)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulTableSize;

    /* ��g_astRnicTiExpriedProcTab�л�ȡ�������� */
    ulTableSize = sizeof(g_astRnicTiExpriedProcTab)/sizeof(RNIC_RCV_TI_EXPRIED_PROC_STRU);

    /* g_astRnicTiExpriedProcTab���������Ϣ����ķַ� */
    for (i = 0; i < ulTableSize; i++)
    {
        if (g_astRnicTiExpriedProcTab[i].ulMsgId== ulMsgId)
        {
            return g_astRnicTiExpriedProcTab[i].pTiExpriedProcFunc;
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvCcpuResetStartInd
 ��������  : RNIC�յ�RNIC��ϢID_CCPU_RESET_RNIC_START_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2013��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : ���L-C��������Ŀ����ӵ�ȫ�ֱ����ĳ�ʼ��
*****************************************************************************/
VOS_UINT32 RNIC_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    RNIC_CTX_STRU                      *pstRnicCtx;

    pstRnicCtx                          = RNIC_GetRnicCtxAddr();

    printk("\n RNIC_RcvCcpuResetStartInd enter, %u \n", VOS_GetSlice());

    /* ֹͣ���������Ķ�ʱ�� */
    RNIC_StopAllTimer();

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucIndex);

        /* ��ʼ��RNIC PDP������ */
        RNIC_InitPdpCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stPdpCtx), ucIndex);

        /* ��ʼ������״̬ */
        pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_STOP;

        /* ��ʼ��ģ��ID */
        /* ��ʼ����ʱ����Ѿ�ȷ��������������Ӧ�ĸ�MODEM */
        pstRnicCtx->astSpecCtx[ucIndex].enModemId        = RNIC_GET_MODEM_ID_BY_NET_ID(ucIndex);

        /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, begin */
        pstRnicCtx->astSpecCtx[ucIndex].enModemType      = RNIC_MODEM_TYPE_INSIDE;
        /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, end */
    }

    /* ��ʼ��RABID��Ϣ */
    for (ucIndex = 0 ; ucIndex < RNIC_MODEM_ID_MAX_NUM ; ucIndex++)
    {
        RNIC_InitRabidInfo(&pstRnicCtx->astRabIdInfo[ucIndex]);
    }

    /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, begin */
    /* ��ʼ��PDNID��Ϣ */
    RNIC_InitPdnIdInfo(&(pstRnicCtx->stPdnIdInfo));
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, end */

    /* ��ʼ��RNIC��ʱ�������� */
    RNIC_InitAllTimers(pstRnicCtx->astTimerCtx);

    /* ��ʼ������ģʽ��Ϣ */
    RNIC_ResetDialMode(&(pstRnicCtx->stDialMode));

    /* ��ʼ�����ŶϿ���ʱ����ʱ��������ͳ�� */
    RNIC_ClearTiDialDownExpCount();

    /* ��ʼ��TIMER4���ѱ�־ */
    RNIC_SetTimer4WakeFlg(VOS_FALSE);

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(RNIC_GetResetSem());

    /* Added by m00217266 for L-C��������Ŀ, 2014-2-17, begin */
    /* �˴��Ƿ�Ҫ���sdio����ע�ắ�� */
    /* Added by m00217266 for L-C��������Ŀ, 2014-2-17, end */
    printk("\n RNIC_RcvCcpuResetStartInd leave, %u \n", VOS_GetSlice());
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcImsaPdnActInd_Wifi
 ��������  : IMSע������wifiʱ��ID_IMSA_RNIC_PDN_ACT_IND�Ĵ���
 �������  : IMSA_RNIC_PDN_ACT_IND_STRU         *pstRcvInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��31��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

  2.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_VOID RNIC_ProcImsaPdnActInd_Wifi(
    IMSA_RNIC_PDN_ACT_IND_STRU         *pstRcvInd
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulIPV4PndInfo;

    ulIPV4PndInfo                       = 0;

    /* ָ��һ��ר�ŵ���������VT��Ƶ���ݴ��� */
    ucRmNetId                           = RNIC_RMNET_ID_IMS1;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    pstSpecNetCardCtx->enModemType      = RNIC_MODEM_TYPE_INSIDE;
    pstSpecNetCardCtx->enRatType        = pstRcvInd->stPdnInfo.enRatType;

    /* IPV4���� */
    if (VOS_TRUE == pstRcvInd->stPdnInfo.bitOpIpv4PdnInfo)
    {
        pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    }

    /* IPV6���� */
    if (VOS_TRUE == pstRcvInd->stPdnInfo.bitOpIpv6PdnInfo)
    {
        pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    }

    /* IPV4V6���� */
    ulIPV4PndInfo   = (VOS_UINT32)(pstRcvInd->stPdnInfo.bitOpIpv4PdnInfo & pstRcvInd->stPdnInfo.bitOpIpv6PdnInfo);

    if (VOS_TRUE == ulIPV4PndInfo)
    {
        pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcImsaPdnActInd_Lte
 ��������  : IMSע������lteʱ��ID_IMSA_RNIC_PDN_ACT_IND�Ĵ���
 �������  : IMSA_RNIC_PDN_ACT_IND_STRU         *pstRcvInd
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��31��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_ProcImsaPdnActInd_Lte(
    IMSA_RNIC_PDN_ACT_IND_STRU         *pstRcvInd
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulIPV4PndInfo;

    ulIPV4PndInfo                       = 0;

    /* ָ��һ��ר�ŵ���������VT��Ƶ���ݴ��� */
    ucRmNetId                           = RNIC_RMNET_ID_VT;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id������id�����Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstRcvInd->stPdnInfo.ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcImsaPdnActInd_Lte, modemId:%d", pstSpecNetCardCtx->enModemId);
        return VOS_ERR;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstRcvInd->stPdnInfo.ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcImsaPdnActInd_Lte, RabId:%d", pstRcvInd->stPdnInfo.ucRabId);
        return VOS_ERR;
    }

    pstSpecNetCardCtx->enModemType      = RNIC_MODEM_TYPE_INSIDE;
    pstSpecNetCardCtx->enRatType        = pstRcvInd->stPdnInfo.enRatType;

    /* ����PDP��������Ϣ */

    /* IPV4���� */
    if (VOS_TRUE == pstRcvInd->stPdnInfo.bitOpIpv4PdnInfo)
    {
        pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstRcvInd->stPdnInfo.ucRabId;
    }

    /* IPV6���� */
    if (VOS_TRUE == pstRcvInd->stPdnInfo.bitOpIpv6PdnInfo)
    {
        pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstRcvInd->stPdnInfo.ucRabId;
    }

    ulIPV4PndInfo   = (VOS_UINT32)(pstRcvInd->stPdnInfo.bitOpIpv4PdnInfo & pstRcvInd->stPdnInfo.bitOpIpv6PdnInfo);

    if (VOS_TRUE == ulIPV4PndInfo)
    {
        pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
        pstPdpAddr->stIpv4v6PdpInfo.ucRabId     = pstRcvInd->stPdnInfo.ucRabId;
    }

    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvImsaPdnActInd
 ��������  : RNIC�յ�IMSA��ϢID_IMSA_RNIC_PDN_ACT_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_RcvImsaPdnActInd(
    MsgBlock                           *pstMsg
)
{
    IMSA_RNIC_PDN_ACT_IND_STRU         *pstRcvInd;
    VOS_UINT32                          ulResult;

    pstRcvInd                           = (IMSA_RNIC_PDN_ACT_IND_STRU *)pstMsg;

    if (IMSA_RNIC_IMS_RAT_TYPE_WIFI == pstRcvInd->stPdnInfo.enRatType)
    {
        RNIC_ProcImsaPdnActInd_Wifi(pstRcvInd);
        return VOS_OK;
    }

    ulResult = RNIC_ProcImsaPdnActInd_Lte(pstRcvInd);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcImsaPdnDeactInd_Wifi
 ��������  : IMSע������wifiʱ��ID_IMSA_RNIC_PDN_DEACT_IND�Ĵ���
 �������  : IMSA_RNIC_PDN_DEACT_IND_STRU       *pstRcvInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��31��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

  2.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_VOID RNIC_ProcImsaPdnDeactInd_Wifi(
    IMSA_RNIC_PDN_DEACT_IND_STRU       *pstRcvInd
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRmNetId;

    /* ָ��һ��ר�ŵ���������VT��Ƶ���ݴ��� */
    ucRmNetId                           = RNIC_RMNET_ID_IMS1;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* �����IPV4 PDPȥ���� */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
    {
        /* ���IPV4 PDP��������Ϣ */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
    {
        /* ���IPV6 PDP��������Ϣ */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus)
    {
        /* ���IPV4V6 PDP��������Ϣ */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* ����������PDP��ȥ�����ʱ����ո���������������Ϣ */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucRmNetId);
        pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;
        pstSpecNetCardCtx->enRatType    = IMSA_RNIC_IMS_RAT_TYPE_BUTT;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcImsaPdnDeactInd_Lte
 ��������  : IMSע������lteʱ��ID_IMSA_RNIC_PDN_DEACT_IND�Ĵ���
 �������  : IMSA_RNIC_PDN_DEACT_IND_STRU       *pstRcvInd
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��31��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

  2.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_UINT32 RNIC_ProcImsaPdnDeactInd_Lte(
    IMSA_RNIC_PDN_DEACT_IND_STRU       *pstRcvInd
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucRmNetId;

    /* ָ��һ��ר�ŵ���������VT��Ƶ���ݴ��� */
    ucRmNetId                           = RNIC_RMNET_ID_VT;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* �����IPV4 PDPȥ���� */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
    {
        /* ���IPV4 PDP��������Ϣ */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
    {
        /* ���IPV6 PDP��������Ϣ */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus)
    {
        /* ���IPV4V6 PDP��������Ϣ */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* ����������PDP��ȥ�����ʱ����ո���������������Ϣ */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucRmNetId);
        pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;
        pstSpecNetCardCtx->enRatType    = IMSA_RNIC_IMS_RAT_TYPE_BUTT;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvImsaPdnDeactInd
 ��������  : RNIC�յ�IMSA��ϢID_IMSA_RNIC_PDN_DEACT_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

  2.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_UINT32 RNIC_RcvImsaPdnDeactInd(
    MsgBlock                           *pstMsg
)
{
    IMSA_RNIC_PDN_DEACT_IND_STRU       *pstRcvInd;
    VOS_UINT32                          ulResult;

    pstRcvInd                           = (IMSA_RNIC_PDN_DEACT_IND_STRU *)pstMsg;

    if (IMSA_RNIC_IMS_RAT_TYPE_WIFI == pstRcvInd->enRatType)
    {
        RNIC_ProcImsaPdnDeactInd_Wifi(pstRcvInd);
        return VOS_OK;
    }

    ulResult = RNIC_ProcImsaPdnDeactInd_Lte(pstRcvInd);

    return ulResult;
}


/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_ProcInsideModemIpv4ActInd
 ��������  : ��modem ipv4����
 �������  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcInsideModemIpv4ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU         *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id������id�����Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstPdpStatusInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv4ActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstPdpStatusInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv4ActInd, RabId:%d", pstPdpStatusInd->ucRabId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId     = pstPdpStatusInd->ucRabId;

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ֹͣ���貦�ű�����ʱ�� */
    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);
    }

    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcInsideModemIpv6ActInd
 ��������  : ��modem ipv6����
 �������  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcInsideModemIpv6ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRabid;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;


    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucRabid                             = RNIC_RAB_ID_INVALID;

    /* ����modem id������id�����Rabid */
    if (VOS_OK != RNIC_BuildRabIdByModemId(pstSpecNetCardCtx->enModemId,
                                           pstPdpStatusInd->ucRabId,
                                           &ucRabid))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv6ActInd, modemId:%d", pstSpecNetCardCtx->enModemId);
        return;
    }

    /* �洢RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstPdpStatusInd->ucRabId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcInsideModemIpv6ActInd, RabId:%d", pstPdpStatusInd->ucRabId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_INSIDE;

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId     = pstPdpStatusInd->ucRabId;

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    ADS_DL_RegDlDataCallback(ucRabid, RNIC_RcvAdsDlData, ucRmNetId);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcRnicPdpActInd
 ��������  : ����PDP������Ϣ
 �������  : RNIC_PDP_STATUS_IND_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��7��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcRnicPdpActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    /* Ĭ��ipv4��ipv6����ɹ��������·� */
    if (RNIC_MODEM_TYPE_INSIDE == pstPdpStatusInd->enModemType)
    {
        if (RNIC_IP_TYPE_IPV4 == pstPdpStatusInd->enIpType)
        {
            /* balong modem ipv4���� */
            RNIC_ProcInsideModemIpv4ActInd(pstPdpStatusInd);
        }

        if (RNIC_IP_TYPE_IPV6 == pstPdpStatusInd->enIpType)
        {
            /* balong modem ipv6���� */
            RNIC_ProcInsideModemIpv6ActInd(pstPdpStatusInd);
        }
    }

    if (RNIC_MODEM_TYPE_OUTSIDE == pstPdpStatusInd->enModemType)
    {
        if (RNIC_IP_TYPE_IPV4 == pstPdpStatusInd->enIpType)
        {
            /* ����modem ipv4����*/
            RNIC_ProcOutsideModemIpv4ActInd(pstPdpStatusInd);
        }

        if (RNIC_IP_TYPE_IPV6 == pstPdpStatusInd->enIpType)
        {
            /* ����modem ipv6����*/
            RNIC_ProcOutsideModemIpv6ActInd(pstPdpStatusInd);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_SaveNetIdByPdnId
 ��������  : ����pdn id��������id
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��7��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_SaveNetIdByPdnId(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_PDNID_INFO_STAU               *pstPdnIdInfo;

    if ((ucPdnId < RNIC_PDN_ID_MIN)
     || (ucPdnId > RNIC_PDN_ID_MAX))
    {
        return VOS_ERR;
    }

    /* ��ȡָ��Modem��RABID��Ϣ */
    pstPdnIdInfo = RNIC_GET_SPEC_MODEM_PDNID_INFO();

    pstPdnIdInfo->aucRmNetId[ucPdnId - RNIC_PDN_ID_OFFSET] = ucRmNetId;

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : RNIC_ProcOutsideModemIpv4ActInd
 ��������  : ��modem ipv4����
 �������  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcOutsideModemIpv4ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRmNetId;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucPdnId                             = pstPdpStatusInd->ucPdnId;

    /* �洢PDNID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcOutsideModemIpv4ActInd, PdnId:%d", ucPdnId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_OUTSIDE;

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId     = ucPdnId;

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)RNIC_RcvSdioDlData);

    return;
}


/*****************************************************************************
 �� �� ��  : RNIC_ProcOutsideModemIpv6ActInd
 ��������  : ��modem ipv6����
 �������  : RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcOutsideModemIpv6ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr          = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                          = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    ucPdnId                             = pstPdpStatusInd->ucPdnId;

    /* �洢PDNID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId,
                                        ucRmNetId))
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcOutsideModemIpv6ActInd, PdnId:%d", ucPdnId);
        return;
    }

    pstSpecNetCardCtx->enModemType        = RNIC_MODEM_TYPE_OUTSIDE;

    /* ����PDP��������Ϣ */
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId     = ucPdnId;

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* ��������ͳ�ƶ�ʱ�� */
    RNIC_StartTimer(enTimerId, TI_RNIC_DSFLOW_STATS_LEN);

    /* ע�����з��ͺ�����ADS����ע��ĺ��������������� */
    SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)RNIC_RcvSdioDlData);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearIpv4PdpCtxInSwitch
 ��������  : �����������л����������������ipv4 pdp������
 �������  : VOS_UINT8  ucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ClearIpv4PdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usModemId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtx           = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucPdnId           = RNIC_PDN_ID_INVALID;
    ucRabId           = RNIC_RAB_ID_INVALID;
    pstPdpCtx         = RNIC_GET_SPEC_NET_PDP_CTX(ucRmNetId);
    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    usModemId         = pstSpecNetCardCtx->enModemId;

    /* ����PDP�������ͣ����PDN ID �� RAB ID��Ӧ������id��Ϣ */
    /* ��������modem��Ҫ�ÿ��������ݷ���ָ�� */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtx->stIpv4PdpInfo.enRegStatus)
    {
        if (RNIC_PDN_ID_INVALID != pstPdpCtx->stIpv4PdpInfo.ucPdnId)
        {
            ucPdnId = pstPdpCtx->stIpv4PdpInfo.ucPdnId;

            if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4PdpCtxInSwitch, Pdnid:%d", ucPdnId);
            }

            SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);
        }

        if (RNIC_RAB_ID_INVALID != pstPdpCtx->stIpv4PdpInfo.ucRabId)
        {
            ucRabId = pstPdpCtx->stIpv4PdpInfo.ucRabId;

            if (VOS_OK != RNIC_SaveNetIdByRabId(usModemId, ucRabId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4PdpCtxInSwitch, ucRabId:%d", ucRabId);
            }
        }
    }

    /* ���ip������ */
    RNIC_InitIpv4PdpCtx(&(pstPdpCtx->stIpv4PdpInfo));
    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearIpv6PdpCtxInSwitch
 ��������  : �����������л����������������ipv6 pdp������
 �������  : VOS_UINT8  ucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ClearIpv6PdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usModemId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtx           = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucPdnId           = RNIC_PDN_ID_INVALID;
    ucRabId           = RNIC_RAB_ID_INVALID;
    pstPdpCtx         = RNIC_GET_SPEC_NET_PDP_CTX(ucRmNetId);
    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    usModemId         = pstSpecNetCardCtx->enModemId;

    /* ����PDP�������ͣ����PDN ID �� RAB ID��Ӧ������id��Ϣ */
    /* ��������modem��Ҫ�ÿ��������ݷ���ָ�� */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtx->stIpv6PdpInfo.enRegStatus)
    {
        if (RNIC_PDN_ID_INVALID != pstPdpCtx->stIpv6PdpInfo.ucPdnId)
        {
            ucPdnId = pstPdpCtx->stIpv6PdpInfo.ucPdnId;

            if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv6PdpCtxInSwitch, Pdnid:%d", ucPdnId);
            }

            SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);
        }

        if (RNIC_RAB_ID_INVALID != pstPdpCtx->stIpv6PdpInfo.ucRabId)
        {
            ucRabId = pstPdpCtx->stIpv6PdpInfo.ucRabId;

            if (VOS_OK != RNIC_SaveNetIdByRabId(usModemId, ucRabId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv6PdpCtxInSwitch, ucRabId:%d", ucRabId);
            }
        }
    }

    /* ���ip������ */
    RNIC_InitIpv6PdpCtx(&(pstPdpCtx->stIpv6PdpInfo));
    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearIpv4v6PdpCtxInSwitch
 ��������  : �����������л����������������ipv4v6 pdp������
 �������  : VOS_UINT8 ucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ClearIpv4v6PdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usModemId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtx           = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucPdnId           = RNIC_PDN_ID_INVALID;
    ucRabId           = RNIC_RAB_ID_INVALID;
    pstPdpCtx         = RNIC_GET_SPEC_NET_PDP_CTX(ucRmNetId);
    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);
    usModemId         = pstSpecNetCardCtx->enModemId;

    /* ����PDP�������ͣ����PDN ID �� RAB ID��Ӧ������id��Ϣ */
    /* ��������modem��Ҫ�ÿ��������ݷ���ָ�� */
    if (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtx->stIpv4v6PdpInfo.enRegStatus)
    {
        if (RNIC_PDN_ID_INVALID != pstPdpCtx->stIpv4v6PdpInfo.ucPdnId)
        {
            ucPdnId = pstPdpCtx->stIpv4v6PdpInfo.ucPdnId;

            if (VOS_OK != RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4v6PdpCtxInSwitch, Pdnid:%d", ucPdnId);
            }

            SDIO_DL_RegDataCallback(ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);
        }

        if (RNIC_RAB_ID_INVALID != pstPdpCtx->stIpv4v6PdpInfo.ucRabId)
        {
            ucRabId = pstPdpCtx->stIpv4v6PdpInfo.ucRabId;

            if (VOS_OK != RNIC_SaveNetIdByRabId(usModemId, ucRabId, RNIC_RMNET_ID_BUTT))
            {
                RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ClearIpv4v6PdpCtxInSwitch, ucRabId:%d", ucRabId);
            }
        }
    }

    /* ���ip������ */
    RNIC_InitIpv4v6PdpCtx(&(pstPdpCtx->stIpv4v6PdpInfo), ucRmNetId);
    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearSwitchPdpCtx
 ��������  : �����������л����������pdp������
 �������  : ucRmNetId
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��10��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ClearPdpCtxInSwitch(
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    pstSpecNetCardCtx = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* ����PDP�������ͣ��ֱ����PDN ID �� RAB ID��Ӧ������id��Ϣ */
    /* ��������modem��Ҫ�ÿ��������ݷ���ָ�� */
    /* ���ipv4 pdp������ */
    RNIC_ClearIpv4PdpCtxInSwitch(ucRmNetId);

    /* ���ipv6 pdp������ */
    RNIC_ClearIpv6PdpCtxInSwitch(ucRmNetId);

    /* ���ipv4v6 pdp������ */
    RNIC_ClearIpv4v6PdpCtxInSwitch(ucRmNetId);

    /* ����modem type */
    pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcRnicPdpHandoverInd
 ��������  : ����PDP handover��Ϣ
 �������  : RNIC_PDP_STATUS_IND_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��6��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcRnicPdpHandoverInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    VOS_UINT8                           ucRmNetId;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* handover�������̷�Ϊ������
       1���״�handover���req��Ϣ����֮ǰpdp�����ĺ�������Ϣ
       2�����汾��req��PDP�����ģ������̴�����PDP��������һ��*/

    /* step1:�״�handover���pdp�����ĺ�������Ϣ */
    if (pstPdpStatusInd->enModemType != pstSpecNetCardCtx->enModemType)
    {
        RNIC_ClearPdpCtxInSwitch(ucRmNetId);
    }

    /* step2:����PDP������ */
    RNIC_ProcRnicPdpActInd(pstPdpStatusInd);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcOutsideModemDeactInd
 ��������  : �����ⲿmodem PDPȥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��8��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcOutsideModemDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU         *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr       = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* �����IPV4 PDPȥ���� */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucPdnId == pstPdpStatusInd->ucPdnId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* ���IPV4 PDP��������Ϣ */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucPdnId == pstPdpStatusInd->ucPdnId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* ���IPV6 PDP��������Ϣ */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucPdnId == pstPdpStatusInd->ucPdnId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ���IPV4V6 PDP��������Ϣ */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP��δ�����ʱ�� */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ֹͣ����ͳ�ƶ�ʱ�� */
        RNIC_StopTimer(enTimerId);

        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucRmNetId);

        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
    }

    /* ���ע���SDIO�Ļص����� */
    SDIO_DL_RegDataCallback(pstPdpStatusInd->ucPdnId, (RCV_C_DL_DATA_FUNC)VOS_NULL_PTR);

    /* ���PDNID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByPdnId(pstPdpStatusInd->ucPdnId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : RNIC_ProcInsideModemDeactInd
 ��������  : �����ڲ�modem PDPȥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��8��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcInsideModemDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU         *pstPdpStatusInd
)
{
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;
    VOS_UINT8                           ucRmNetId;
    RNIC_PDP_CTX_STRU                  *pstPdpCtxAddr       = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx   = VOS_NULL_PTR;

    ucRmNetId                           = pstPdpStatusInd->ucRmNetId;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpCtxAddr                       = RNIC_GetPdpCtxAddr(ucRmNetId);
    pstSpecNetCardCtx                   = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* ��������ID��ȡ����ͳ�ƵĶ�ʱ��ID */
    enTimerId = RNIC_GetDsflowTimerIdByNetId(ucRmNetId);

    /* �����IPV4 PDPȥ���� */
    if ((pstPdpCtxAddr->stIpv4PdpInfo.ucRabId == pstPdpStatusInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus))
    {
        /* ���IPV4 PDP��������Ϣ */
        RNIC_InitIpv4PdpCtx(&pstPdpCtxAddr->stIpv4PdpInfo);

        /* ������0�ϲ��а��貦�ŵĹ��� */
        if (RNIC_RMNET_ID_0 == ucRmNetId)
        {
            /* ֹͣ���貦�ŶϿ���ʱ�� */
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

            /* ��ղ��ŶϿ���ʱ����ʱͳ�� */
            RNIC_ClearTiDialDownExpCount();
        }
    }

    if ((pstPdpCtxAddr->stIpv6PdpInfo.ucRabId == pstPdpStatusInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus))
    {
        /* ���IPV6 PDP��������Ϣ */
        RNIC_InitIpv6PdpCtx(&pstPdpCtxAddr->stIpv6PdpInfo);
    }

    if ((pstPdpCtxAddr->stIpv4v6PdpInfo.ucRabId == pstPdpStatusInd->ucRabId)
     && (RNIC_PDP_REG_STATUS_ACTIVE == pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ���IPV4V6 PDP��������Ϣ */
        RNIC_InitIpv4v6PdpCtx(&pstPdpCtxAddr->stIpv4v6PdpInfo, ucRmNetId);
    }

    /* PDP��δ�����ʱ�� */
    if ((RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv6PdpInfo.enRegStatus)
     && (RNIC_PDP_REG_STATUS_ACTIVE != pstPdpCtxAddr->stIpv4v6PdpInfo.enRegStatus))
    {
        /* ֹͣ����ͳ�ƶ�ʱ�� */
        RNIC_StopTimer(enTimerId);

        /* �������ͳ����Ϣ */
        RNIC_ClearNetDsFlowStats(ucRmNetId);

        pstSpecNetCardCtx->enModemType = RNIC_MODEM_TYPE_INSIDE;
    }

    /* �ڶϿ����ųɹ�ʱ���ͶƱ˯�ߣ��Ա��ܽ�����˯ */
    DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_RNIC);

    /* ���RABID��Ӧ������ID */
    if (VOS_OK != RNIC_SaveNetIdByRabId(pstSpecNetCardCtx->enModemId,
                                        pstPdpStatusInd->ucRabId,
                                        RNIC_RMNET_ID_BUTT))
    {
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcRnicPdpDeactInd
 ��������  : ����PDPȥ������Ϣ
 �������  : RNIC_PDP_STATUS_IND_STRU           *pstPdpStatusInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��6��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcRnicPdpDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
)
{
    /* ��ն�Ӧ������PDP������ */
    if (RNIC_MODEM_TYPE_INSIDE == pstPdpStatusInd->enModemType)
    {
        /* ����ڲ�modem PDPȥ������������� */
        RNIC_ProcInsideModemDeactInd(pstPdpStatusInd);
    }
    if (RNIC_MODEM_TYPE_OUTSIDE == pstPdpStatusInd->enModemType)
    {
        /* ����ⲿmodem PDPȥ������������� */
        RNIC_ProcOutsideModemDeactInd(pstPdpStatusInd);
    }
    return;
}


/*****************************************************************************
 �� �� ��  : RNIC_RcvRnicRmnetConfigReq
 ��������  : ����ID_RNIC_RMNET_CONFIG_REQ��Ϣ
 �������  : MsgBlock                           *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��6��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��3��
    ��    ��   : m00217266
    �޸�����   : DTS2014052902453
*****************************************************************************/
VOS_UINT32 RNIC_RcvRnicRmnetConfigReq(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucRmNetId;
    RNIC_RMNET_CONFIG_REQ_STRU         *pstRmnetConfigReq = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx = VOS_NULL_PTR;

    pstRmnetConfigReq       = (RNIC_RMNET_CONFIG_REQ_STRU *)pstMsg;
    ucRmNetId               = pstRmnetConfigReq->ucRmNetId;
    pstSpecNetCardCtx       = RNIC_GetSpecNetCardCtxAddr(ucRmNetId);

    /* pdp����ɹ���rnic����up */
    if (RNIC_RMNET_STATUS_UP == pstRmnetConfigReq->enRmnetStatus)
    {
        /* RNIC_MODEM_TYPE_BUTT�޸�ΪRNIC_MODEM_TYPE_INSIDE����ҪΪ������v3r3���貦�Ź��� */
        if ((pstSpecNetCardCtx->enModemType == pstRmnetConfigReq->enModemType)
         || (RNIC_MODEM_TYPE_INSIDE == pstSpecNetCardCtx->enModemType))
        {
            RNIC_ProcRnicPdpActInd(pstRmnetConfigReq);
        }
    }
    /* ����modem ps��handover��rnic����switch */
    else if (RNIC_RMNET_STATUS_SWITCH == pstRmnetConfigReq->enRmnetStatus)
    {
        RNIC_ProcRnicPdpHandoverInd(pstRmnetConfigReq);
    }
    /* pdpȥ����ɹ���rnic����down */
    else
    {
        if (pstSpecNetCardCtx->enModemType == pstRmnetConfigReq->enModemType)
        {
            RNIC_ProcRnicPdpDeactInd(pstRmnetConfigReq);
        }
    }

    return VOS_OK;
}
/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */


/*****************************************************************************
 �� �� ��  : Rnic_RcvAtMsg
 ��������  : RNIC�յ�AT��Ϣ�ķַ�
 �������  : pMsg:AT�ķ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��1��31��
   ��    ��   : w00199382
   �޸�����   : ID_AT_RNIC_DIAL_MODE_IND ID_AT_RNIC_DIAL_MODE_REQɾ��
  3.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: ����MTU������Ϣ
  4.��    ��   : 2013��6��4��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 RNIC_RcvAtMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_AT_RNIC_IPV4_PDP_ACT_IND:
            RNIC_RcvAtIpv4PdpActInd(pstMsg);
            break;

        case ID_AT_RNIC_IPV6_PDP_ACT_IND:
            RNIC_RcvAtIpv6PdpActInd(pstMsg);
            break;

        case ID_AT_RNIC_IPV4V6_PDP_ACT_IND:
            RNIC_RcvAtIpv4v6PdpActInd(pstMsg);
            break;

        case ID_AT_RNIC_PDP_DEACT_IND:
            RNIC_RcvAtPdpDeactInd(pstMsg);
            break;

        case ID_AT_RNIC_DSFLOW_IND:
            RNIC_RcvAtDsflowInd(pstMsg);
            break;

        case ID_AT_RNIC_DIAL_MODE_REQ:
            RNIC_RcvAtDialModeReq(pstMsg);
            break;

        case ID_AT_RNIC_PDN_INFO_CFG_IND:
            RNIC_RcvAtPdnInfoCfgInd(pstMsg);
            break;

        case ID_AT_RNIC_PDN_INFO_REL_IND:
            RNIC_RcvAtPdnInfoRelInd(pstMsg);
            break;

        default:
            RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvAtMsg:MsgId", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcTimerMsg
 ��������  : RNIC�յ���ʱ����Ϣ��ʱ�ķַ�
 �������  : pMsg:��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2011��12��06��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��31��
    ��    ��   : w00199382
    �޸�����   : ���ű�����ʱ����ʱɾ��
  3.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_RcvTimerMsg(MsgBlock *pstMsg)
{
    REL_TIMER_MSG                      *pstRcvMsg;
    VOS_UINT8                           ucRmNetId;
    RNIC_RCV_TI_EXPRIED_PROC_FUNC       pTiExpriedProcFunc;
    VOS_UINT32                          ulRst;

    pTiExpriedProcFunc = VOS_NULL_PTR;
    pstRcvMsg = (REL_TIMER_MSG *)pstMsg;

    /* ���ݶ�ʱ��ID��ȡ����ID */
    ucRmNetId = RNIC_GetNetIdByTimerId(pstRcvMsg->ulName);

    /* ���Ҷ�ʱ����ʱ���������Ϣ������� */
    pTiExpriedProcFunc = RNIC_GetTiExpiredFuncByMsgId(pstRcvMsg->ulName);
    if (VOS_NULL_PTR != pTiExpriedProcFunc)
    {
        ulRst = pTiExpriedProcFunc(pstMsg, ucRmNetId);
        if (VOS_ERR == ulRst)
        {
            RNIC_INFO_LOG(ACPU_PID_RNIC, "RNIC_RcvTimerMsg:proc func error! \r\n");
            return VOS_ERR;
        }
    }
    else
    {
        RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_RcvTimerMsg:pstRcvMsg->ulName\r\n", pstRcvMsg->ulName);
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : RNIC_ProcImsData
 ��������  :
 �������  : MsgBlock *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��26��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ProcImsData(MsgBlock *pMsg)
{
    RNIC_IMS_DATA_PROC_IND_STRU        *pstDataProcInd = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;

    pstDataProcInd = (RNIC_IMS_DATA_PROC_IND_STRU *)pMsg;

    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(pstDataProcInd->enRmNetId);

    for (;;)
    {
        pstImmZc = IMM_ZcDequeueHead(&pstNetCntxt->stPdpCtx.stImsQue);
        if (VOS_NULL_PTR == pstImmZc)
        {
            break;
        }

        RNIC_ProcVoWifiULData(pstImmZc, pstNetCntxt);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvRnicMsg
 ��������  : RNIC�յ�RNIC��Ϣ�ķַ�
 �������  : pstMsg:RNIC��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2013��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_RcvRnicMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_RNIC_CCPU_RESET_START_IND:
            RNIC_RcvCcpuResetStartInd(pstMsg);
            break;

        case ID_RNIC_CCPU_RESET_END_IND:

            /* do nothing */
            RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_RcvRnicMsg: rcv ID_CCPU_RNIC_RESET_END_IND");
            break;

        case ID_RNIC_IMS_DATA_PROC_IND:
            RNIC_ProcImsData(pstMsg);
            break;

        /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
        case ID_RNIC_RMNET_CONFIG_REQ:
            RNIC_RcvRnicRmnetConfigReq(pstMsg);
            break;

        /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

        default:
            RNIC_NORMAL_LOG1(ACPU_PID_RNIC, "RNIC_RcvRnicMsg: rcv error msg id %d\r\n", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvImsaMsg
 ��������  : RNIC�յ�IMSA��Ϣ�ķַ�
 �������  : pstMsg:IMSA��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_RcvImsaMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_IMSA_RNIC_PDN_ACT_IND:
            RNIC_RcvImsaPdnActInd(pstMsg);
            break;

        case ID_IMSA_RNIC_PDN_DEACT_IND:
            RNIC_RcvImsaPdnDeactInd(pstMsg);
            break;

        default:
            RNIC_NORMAL_LOG1(ACPU_PID_RNIC, "RNIC_RcvImsaMsg: rcv error msg id %d\r\n", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvCdsImsDataInd
 ��������  : �յ�CDS��ID_CDS_RNIC_IMS_DATA_IND��Ϣ����
 �������  : MsgBlock                           *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

  2.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_VOID RNIC_RcvCdsImsDataInd(
    MsgBlock                           *pstMsg
)
{
    CDS_RNIC_IMS_DATA_IND_STRU         *pstImsDataInd = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt   = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc      = VOS_NULL_PTR;
    VOS_UINT8                           ucIpType;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;

    pstImsDataInd = (CDS_RNIC_IMS_DATA_IND_STRU *)pstMsg;

    pstNetCntxt = RNIC_GetSpecNetCardCtxAddr(RNIC_RMNET_ID_IMS1);

    /* ����A���ڴ� */
    pstImmZc = IMM_ZcStaticAlloc(pstImsDataInd->usDataLen + IMM_MAC_HEADER_RES_LEN);
    if (VOS_NULL_PTR == pstImmZc)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvCdsImsDataInd, IMM_ZcStaticAlloc fail!");
        return ;
    }

    IMM_ZcReserve(pstImmZc, IMM_MAC_HEADER_RES_LEN);

    /* ����IP���ݰ� */
    PS_MEM_CPY(pstImmZc->data, pstImsDataInd->aucData, pstImsDataInd->usDataLen);

    IMM_ZcPut(pstImmZc, pstImsDataInd->usDataLen);

    /* ��ȡIP version */
    ucIpType = ((RNIC_IPFIXHDR_STRU *)(pstImsDataInd->aucData))->ucIpVer;

    if (RNIC_IPV4_VERSION == ucIpType)
    {
        enPktType = ADS_PKT_TYPE_IPV4;
    }
    else if (RNIC_IPV6_VERSION == ucIpType)
    {
        enPktType = ADS_PKT_TYPE_IPV6;
    }
    else    /* ���ݰ����������֧�����Ͳ�һ�� */
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_RECV_DL_ERR_PKT_NUM(1, RNIC_RMNET_ID_IMS1);
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_RcvCdsImsDataInd, Ip Type Error!");

        return;
    }

    RNIC_NetRxData(pstNetCntxt, pstImmZc, enPktType);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvCdsMsg
 ��������  : RNIC�յ�CDS��Ϣ�ķַ�
 �������  : MsgBlock *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_RcvCdsMsg(MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case ID_CDS_RNIC_IMS_DATA_IND:
            RNIC_RcvCdsImsDataInd(pstMsg);
            break;

        default:
            RNIC_NORMAL_LOG1(ACPU_PID_RNIC, "RNIC_RcvCdsMsg: rcv error msg id %d\r\n", pstMsgHeader->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_PidMsgProc
 ��������  : RNIC���ݽ���task��Ϣ������
 �������  : pMsg:��������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_ProcMsg (MsgBlock *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ProcMsg: Msg is invalid!");
        return VOS_ERR;
    }

    /* ��Ϣ�ķַ����� */
    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_AT:

            /* ����AT��Ϣ */
            RNIC_RcvAtMsg(pstMsg);
            break;

        case VOS_PID_TIMER:

            /* ���ն�ʱ����ʱ��Ϣ */
            RNIC_RcvTimerMsg(pstMsg);
            break;

        case ACPU_PID_RNIC:

            /* ����RNIC����Ϣ*/
            RNIC_RcvRnicMsg(pstMsg);
            break;

        case PS_PID_IMSA:

            /* ����IMSA����Ϣ*/
            RNIC_RcvImsaMsg(pstMsg);
            break;

        case UEPS_PID_CDS:

            /* ����CDS����Ϣ*/
            RNIC_RcvCdsMsg(pstMsg);
            break;

        default:
            RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_ProcMsg:SendPid", pstMsg->ulSenderPid);
            break;
    }

    return VOS_OK;
}


