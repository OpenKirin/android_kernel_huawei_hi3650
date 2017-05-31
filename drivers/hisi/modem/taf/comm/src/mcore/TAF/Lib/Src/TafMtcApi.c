


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"

#include "TafMtcApi.h"





/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTC_API_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
    extern VOS_UINT32 AT_GetDestPid(
        MN_CLIENT_ID_T                      usClientId,
        VOS_UINT32                          ulRcvPid
    );

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MTC_SndMsg
 ��������  : ����MTC��Ϣ
 �������  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MTC_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    TAF_PS_MSG_STRU                    *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult = VOS_OK;

    /* ������Ϣ */
    pstMsg = (TAF_PS_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                UEPS_PID_MTC,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->stHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    /* ��д��Ϣ���� */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* ������Ϣ */
    ulResult = PS_SEND_MSG(UEPS_PID_MTC, pstMsg);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MTC_SetCdmaServiceConnStateInfo
 ��������  : �����ⲿCDMA Modem������״̬(PS&CS)
 �������  : ulModuleId                 - ģ��ID(����Pid)
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstCdmsStatus              - ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MTC_SetCdmaServiceConnStateInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmaState
)
{
    TAF_MTC_CDMA_STATE_IND_STRU         stSetCdmaConnSt;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetCdmaConnSt, 0x00, sizeof(TAF_MTC_CDMA_STATE_IND_STRU));

    /* ����ID_MSG_MTC_CDMA_CONN_STATUS��Ϣ */
    TAF_API_CTRL_HEADER(&stSetCdmaConnSt.stCtrl, pstCtrl->ulModuleId,
                        pstCtrl->usClientId, pstCtrl->ucOpId);

    PS_MEM_CPY(&stSetCdmaConnSt.stCdmaState, pstCdmaState, sizeof(TAF_MTC_CDMA_STATE_INFO_STRU));

    /* ������Ϣ */
    ulResult = MTC_SndMsg(UEPS_PID_MTC,
                         ID_MSG_MTC_CDMA_CONN_STATE_IND,
                         &stSetCdmaConnSt,
                         sizeof(TAF_MTC_CDMA_STATE_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemServiceConnState
 ��������  : ����modem״̬��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             pstModemConnSt  ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 MTC_SetModemServiceConnState(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemConnSt
)
{
    TAF_MTC_MODEM_CONN_STATUS_IND_STRU  stModemConnSt;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stModemConnSt, 0x00, sizeof(TAF_MTC_MODEM_CONN_STATUS_IND_STRU));

    /* ����ID_MSG_MTC_CDMA_CONN_STATUS��Ϣ */
    TAF_API_CTRL_HEADER(&(stModemConnSt.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    PS_MEM_CPY(&stModemConnSt.stModemConnStateInfo, pstModemConnSt, sizeof(TAF_MTC_SRV_CONN_STATE_INFO_STRU));

    /* ������Ϣ */
    ulResult = MTC_SndMsg(UEPS_PID_MTC,
                         ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND,
                         &stModemConnSt,
                         sizeof(TAF_MTC_MODEM_CONN_STATUS_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemUsimmState
 ��������  : ���ÿ�״̬��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             pstModemConnSt  ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������

  2.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 MTC_SetModemUsimmState(
    TAF_CTRL_STRU                           *pstCtrl,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimState,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enCsimState
)
{
    TAF_MTC_USIMM_STATUS_IND_STRU       stUsimmState;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stUsimmState, 0x00, sizeof(TAF_MTC_USIMM_STATUS_IND_STRU));

    /* ����ID_MSG_MTC_CDMA_CONN_STATUS��Ϣ */
    TAF_API_CTRL_HEADER(&(stUsimmState.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stUsimmState.enUsimState = enUsimState;
    stUsimmState.enCsimState = enCsimState;

    /* ������Ϣ */
    ulResult = MTC_SndMsg(UEPS_PID_MTC,
                          ID_MSG_MTC_USIMM_STATE_IND,
                          &stUsimmState,
                          sizeof(TAF_MTC_USIMM_STATUS_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MTC_SetBeginSessionInfo
 ��������  : �����ṩAPI���ⲿģ������������֪ͨMTC ID_MSG_MTC_BEGIN_SESSION_IND��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             enSessionType   ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_SetBeginSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_BEGIN_SESSION_IND_STRU          stSessionInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stSessionInfo, 0x00, sizeof(MTC_BEGIN_SESSION_IND_STRU));

    /* ����ID_MSG_MTC_BEGIN_SESSION_IND��Ϣ */
    TAF_API_CTRL_HEADER(&(stSessionInfo.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stSessionInfo.enSessionType = enSessionType;

    /* ������Ϣ */
    MTC_SndMsg(UEPS_PID_MTC,
               ID_MSG_MTC_BEGIN_SESSION_IND,
               &stSessionInfo,
               sizeof(MTC_BEGIN_SESSION_IND_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SetEndSessionInfo
 ��������  : �����ṩAPI���ⲿģ������������֪ͨMTC ID_MSG_MTC_END_SESSION_IND��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             enSessionType   ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_SetEndSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_END_SESSION_IND_STRU            stEndSessionInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stEndSessionInfo, 0x00, sizeof(MTC_END_SESSION_IND_STRU));

    /* ����ID_MSG_MTC_END_SESSION_IND��Ϣ */
    TAF_API_CTRL_HEADER(&(stEndSessionInfo.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stEndSessionInfo.enSessionType  = enSessionType;
    stEndSessionInfo.enCsRelAll     = VOS_FALSE;
    stEndSessionInfo.enPsRelAll     = VOS_FALSE;

    /* ������Ϣ */
    MTC_SndMsg(UEPS_PID_MTC,
               ID_MSG_MTC_END_SESSION_IND,
               &stEndSessionInfo,
               sizeof(MTC_BEGIN_SESSION_IND_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SetPowerSaveInfo
 ��������  : �����ṩAPI���ⲿģ������������֪ͨMTC Power save��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             enSessionType   ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��30��
    ��    ��   : j00174725
    �޸�����   : DTS2016033008957
*****************************************************************************/
VOS_VOID MTC_SetPowerSaveInfo(
    VOS_UINT32                          ulSndPid,
    TAF_MTC_POWER_SAVE_ENUM_UINT8       enPowerSaveStatus
)
{
    MTC_POWER_SAVE_IND_STRU             stPowerSaveInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stPowerSaveInfo, 0x00, sizeof(MTC_POWER_SAVE_IND_STRU));

    /* ����ID_MSG_MTC_POWER_SAVE_IND��Ϣ */
    stPowerSaveInfo.stCtrl.ulModuleId = ulSndPid;
    stPowerSaveInfo.enPowerSaveStatus = enPowerSaveStatus;

    /* ������Ϣ */
    MTC_SndMsg(UEPS_PID_MTC,
               ID_MSG_MTC_POWER_SAVE_IND,
               &stPowerSaveInfo,
               sizeof(MTC_POWER_SAVE_IND_STRU));

    return;
}



