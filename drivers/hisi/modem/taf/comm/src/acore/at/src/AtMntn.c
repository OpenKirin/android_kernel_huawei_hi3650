


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtMntn.h"
#include "AtInputProc.h"
#include "AtCtx.h"
#include "AtDataProc.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_MNTN_C
/*lint -e767 +e960*/

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
AT_DEBUG_INFO_STRU                      g_stAtDebugInfo = {VOS_FALSE};

AT_MNTN_STATS_STRU                      g_stAtStatsInfo;

AT_MNTN_MSG_RECORD_INFO_STRU            g_stAtMsgRecordInfo;

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ����ʵ��
*****************************************************************************/
/*****************************************************************************
�� �� ��  : AT_InitMntnCtx
��������  : ATģ���ά�ɲ���Ϣ��ʼ��
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��09��13��
   ��    ��   : g00261581
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_InitMntnCtx(VOS_VOID)
{
    PS_MEM_SET(&g_stAtMsgRecordInfo, 0, sizeof(g_stAtMsgRecordInfo));
}

/*****************************************************************************
�� �� ��  : AT_SetPcuiCtrlConcurrentFlag
��������  : ����PCUI��PCUI2��CTRL�ڵĲ�����־λ
�������  : VOS_UINT8    ucFlag
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��4��18��
   ��    ��   : z00220246
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetPcuiCtrlConcurrentFlag(VOS_UINT8 ucFlag)
{
    g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg = ucFlag;
}

/*****************************************************************************
�� �� ��  : AT_GetPcuiCtrlConcurrentFlag
��������  : ��ȡPCUI��CTRL�ڵĲ�����־λ
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT8
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��4��18��
   ��    ��   : z00220246
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_GetPcuiCtrlConcurrentFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg;
}

/*****************************************************************************
 �� �� ��  : AT_SetPcuiPsCallFlag
 ��������  : ����PCUI��ģ��nidsdup���ŵı�־λ
 �������  : VOS_UINT8         ucFlag
             VOS_UINT8         ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetPcuiPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucPcuiPsCallFlg     = ucFlag;
    g_stAtDebugInfo.ucPcuiUserId        = AT_CLIENT_TAB_APP_INDEX;
}

/*****************************************************************************
 �� �� ��  : AT_GetPcuiPsCallFlag
 ��������  : ��ȡPCUI��ģ��nidsdup���ŵı�־λ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_GetPcuiPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiPsCallFlg;
}

/*****************************************************************************
 �� �� ��  : AT_GetPcuiUsertId
 ��������  : ��ȡPCUI��ģ���ĸ��˿�NDISDUP����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_GetPcuiUsertId(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiUserId;
}

/*****************************************************************************
 �� �� ��  : AT_SetCtrlPsCallFlag
 ��������  : ����Ctrl��ģ��nidsdup���ŵı�־λ
 �������  : VOS_UINT8            ucFlag
             VOS_UINT8            ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��8��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetCtrlPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucCtrlPsCallFlg     = ucFlag;
    g_stAtDebugInfo.ucCtrlUserId        = AT_CLIENT_TAB_APP5_INDEX;
}

/*****************************************************************************
 �� �� ��  : AT_GetCtrlPsCallFlag
 ��������  : ��ȡCTRL��ģ��nidsdup���ŵı�־λ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��8��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_GetCtrlPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlPsCallFlg;
}

/*****************************************************************************
 �� �� ��  : AT_GetCtrlUserId
 ��������  : ��ȡCTRL��ģ���ĸ��˿�NDISDUP����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��8��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_GetCtrlUserId(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlUserId;
}

/*****************************************************************************
 �� �� ��  : AT_SetPcui2PsCallFlag
 ��������  : ����PCUI2��ģ��^NDISDUP���ŵı�־λ
 �������  : VOS_UINT8        ucFlag
             VOS_UINT8        ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_SetPcui2PsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
)
{
    g_stAtDebugInfo.ucPcui2PsCallFlg    = ucFlag;
    g_stAtDebugInfo.ucPcui2UserId       = AT_CLIENT_TAB_APP20_INDEX;

}

/*****************************************************************************
 �� �� ��  : AT_GetPcui2PsCallFlag
 ��������  : ��ȡPCUI2��ģ��^NDISDUP���ŵı�־λ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_GetPcui2PsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcui2PsCallFlg;
}

/*****************************************************************************
 �� �� ��  : AT_GetPcui2UserId
 ��������  : ��ȡPCUI2��ģ���ĸ��˿�NDISDUP����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_GetPcui2UserId(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcui2UserId;
}


/*****************************************************************************
 �� �� ��  : AT_SetUnCheckApPortFlg
 ��������  : ���� �����ApPort��־
 �������  : VOS_UINT8                            ucFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��1��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetUnCheckApPortFlg(
    VOS_UINT8                           ucFlag
)
{
    if ((0 == ucFlag) || (1 == ucFlag))
    {
        g_stAtDebugInfo.ucUnCheckApPortFlg = ucFlag;
    }
}

/*****************************************************************************
 �� �� ��  : AT_GetUnCheckApPortFlg
 ��������  : ��ȡ �����ApPort��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : g_stAtDebugInfo.ucUnCheckApPortFlg
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��1��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 AT_GetUnCheckApPortFlg(VOS_VOID)
{
    return g_stAtDebugInfo.ucUnCheckApPortFlg;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceEvent
 ��������  : �����ά�ɲ�
 �������  : pMsg - ��ά�ɲ���Ϣ(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceEvent(VOS_VOID *pMsg)
{

    DIAG_TraceReport(pMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceInputMsc
 ��������  : �ܽ��ź������ά�ɲ�
 �������  : ucIndex   - �˿�����
             pstDceMsc - �ܽ��ź���Ϣ(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceInputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_INPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnMsc.ulPortId = ucIndex;
    PS_MEM_CPY(&(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceOutputMsc
 ��������  : �ܽ��ź������ά�ɲ�
 �������  : ucIndex   - �˿�����
             pstDceMsc - �ܽ��ź���Ϣ(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceOutputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_OUTPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnMsc.ulPortId = ucIndex;
    PS_MEM_CPY(&(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceStartFlowCtrl
 ��������  : �������ؿ�ά�ɲ�
 �������  : ucIndex    - �˿�����
             enFcDevive - �����豸
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStartFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_START_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceStopFlowCtrl
 ��������  : ֹͣ���ؿ�ά�ɲ�
 �������  : ucIndex    - �˿�����
             enFcDevive - �����豸
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStopFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_STOP_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceRegFcPoint
 ��������  : ע�����ص��ά�ɲ�
 �������  : ucIndex   - �˿�����
             enFcPoint - ���ص�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRegFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_REG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceDeregFcPoint
 ��������  : ȥע�����ص��ά�ɲ�
 �������  : ucIndex   - �˿�����
             enFcPoint - ���ص�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceDeregFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_DEREG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceCmdResult
 ��������  : AT����ظ���ά�ɲ�
 �������  : ucIndex   - �˿�����
             pucData   - ��������
             usDataLen - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdResult(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /* ������Ϣ�ڴ� */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdResult:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��д��Ϣͷ */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /* ��д��Ϣ���� */
    pstMsg->ucType  = 0x1;
    pstMsg->ucIndex = ucIndex;
    pstMsg->usLen   = usDataLen;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));
    PS_MEM_CPY((TAF_VOID*)pstMsg->aucValue, pucData, usDataLen);

    /* ��д��Ϣ���� */
    AT_MNTN_TraceEvent(pstMsg);

    /* �ͷ���Ϣ�ڴ� */
    PS_MEM_FREE(WUEPS_PID_AT, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceCmdBuffer
 ��������  : ���������ά�ɲ�
 �������  : ucIndex   - �˿�����
             pucData   - ��������
             usDataLen - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��24��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdBuffer(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /* ������Ϣ�ڴ� */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��д��Ϣͷ */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /* ��д��Ϣ���� */
    pstMsg->ucType          = 0x2;
    pstMsg->ucIndex         = ucIndex;
    pstMsg->usLen           = usDataLen;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));
    PS_MEM_CPY((TAF_VOID*)pstMsg->aucValue, pucData, usDataLen);

    /* ��д��Ϣ���� */
    AT_MNTN_TraceEvent(pstMsg);

    /* �ͷ���Ϣ�ڴ� */
    PS_FREE_MSG(WUEPS_PID_AT, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceContextData
 ��������  : ��AT�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2010��02��12��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��7��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ�ţ�DTS2010071402189��֧��ATģ���CLIENT ID�Ļط�
  3.��    ��   : 2013��03��07��
    ��    ��   : f00179208
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_MNTN_TraceContextData(VOS_VOID)
{
    NAS_AT_SDT_AT_PART_ST                  *pstSndMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx   = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx       = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pstSndMsgCB = (NAS_AT_SDT_AT_PART_ST *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_PART_ST));

    if (VOS_NULL_PTR == pstSndMsgCB)
    {
        AT_ERR_LOG("AT_MNTN_TraceContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST) + 4;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_MSG;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;


    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx                           = AT_GetModemSmsCtxAddrFromModemId(enModemId);
        pstOutsideCtx                       = &pstSndMsgCB->astOutsideCtx[enModemId];

        pstOutsideCtx->gucAtCscsType        = gucAtCscsType;
        pstOutsideCtx->gucAtCsdhType        = pstSmsCtx->ucCsdhType;
        pstOutsideCtx->g_OpId               = g_OpId;
        pstOutsideCtx->g_enAtCsmsMsgVersion = pstSmsCtx->enCsmsMsgVersion;
        pstOutsideCtx->g_enAtCmgfMsgFormat  = pstSmsCtx->enCmgfMsgFormat;

        PS_MEM_CPY(&pstOutsideCtx->gstAtCnmiType,
                   &(pstSmsCtx->stCnmiType),
                   sizeof(pstSmsCtx->stCnmiType));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCgsmsSendDomain,
                   &(pstSmsCtx->stCgsmsSendDomain),
                   sizeof(pstSmsCtx->stCgsmsSendDomain));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCscaCsmpInfo,
                   &(pstSmsCtx->stCscaCsmpInfo),
                   sizeof(pstSmsCtx->stCscaCsmpInfo));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCpmsInfo,
                   &(pstSmsCtx->stCpmsInfo),
                   sizeof(pstSmsCtx->stCpmsInfo));

    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceClientData
 ��������  : ����ATģ��Ŀͻ��˿�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��17��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceClientData(VOS_VOID)
{
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU         *pstSndMsgCB;
    TAF_UINT8                               ucLoop;

    pstSndMsgCB = (NAS_AT_SDT_AT_CLIENT_TABLE_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceClientData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU) - 20;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_CLIENT_TAB;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG_CLIENT_TAB;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->gastAtClientTab[ucLoop].usClientId   = gastAtClientTab[ucLoop].usClientId;
        pstSndMsgCB->gastAtClientTab[ucLoop].opId         = gastAtClientTab[ucLoop].opId;
        pstSndMsgCB->gastAtClientTab[ucLoop].ucUsed       = gastAtClientTab[ucLoop].ucUsed;
        pstSndMsgCB->gastAtClientTab[ucLoop].UserType     = gastAtClientTab[ucLoop].UserType;
        pstSndMsgCB->gastAtClientTab[ucLoop].Mode         = gastAtClientTab[ucLoop].Mode;
        pstSndMsgCB->gastAtClientTab[ucLoop].IndMode      = gastAtClientTab[ucLoop].IndMode;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceRPTPORT
 ��������  : ����ATģ��Ŀͻ��˿�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��1��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRPTPORT(VOS_VOID)
{
    AT_MNTN_RPTPORT_STRU                   *pstSndMsgCB;
    VOS_UINT8                               ucLoop;

    pstSndMsgCB = (AT_MNTN_RPTPORT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(AT_MNTN_RPTPORT_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceRPTPORT:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(AT_MNTN_RPTPORT_STRU) - 20;
    pstSndMsgCB->enMsgId            = ID_AT_MNTN_RPT_PORT;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->astAtRptPort[ucLoop].enAtClientTabIndex = (AT_CLIENT_TAB_INDEX_UINT8)ucLoop;
        pstSndMsgCB->astAtRptPort[ucLoop].enModemId          = g_astAtClientCtx[ucLoop].stClientConfiguration.enModemId;
        pstSndMsgCB->astAtRptPort[ucLoop].ucReportFlg        = g_astAtClientCtx[ucLoop].stClientConfiguration.ucReportFlg;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_InitHsUartStats
 ��������  : ��ʼ��UART��ά�ɲ���Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_InitHsUartStats(VOS_VOID)
{
    PS_MEM_SET(&g_stAtStatsInfo.stHsUartStats, 0x00, sizeof(AT_MNTN_HSUART_STATS_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : AT_MODEM_Help
 ��������  : ��ʼ��UART��ά�ɲ���Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_InitModemStats(VOS_VOID)
{
    PS_MEM_SET(&g_stAtStatsInfo.stModemStats, 0x00, sizeof(AT_MNTN_MODEM_STATS_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : AT_RecordAtMsgInfo
 ��������  : ��¼����At_MsgProc��������Ϣ����
 �������  : VOS_UINT32                          ulSendPid,
             VOS_UINT32                          ulMsgName,
             VOS_UINT32                          ulSliceStart,
             VOS_UINT32                          ulSliceEnd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��04��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_RecordAtMsgInfo(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulSliceStart,
    VOS_UINT32                          ulSliceEnd
)
{
    VOS_UINT32                          ulIndex;

    if (g_stAtMsgRecordInfo.ulCurrentIndex >= AT_MNTN_MSG_RECORD_MAX_NUM)
    {
        g_stAtMsgRecordInfo.ulCurrentIndex = 0;
    }

    ulIndex = g_stAtMsgRecordInfo.ulCurrentIndex;

    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSendPid    = ulSendPid;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulMsgName    = ulMsgName;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSliceStart = ulSliceStart;
    g_stAtMsgRecordInfo.astAtMntnMsgRecord[ulIndex].ulSliceEnd   = ulSliceEnd;

    g_stAtMsgRecordInfo.ulCurrentIndex++;

    return;
}


/*****************************************************************************
 �� �� ��  : AT_ShowModemDataStats
 ��������  : MODEM������ͳ�ƿ�ά�ɲ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowModemDataStats(VOS_VOID)
{
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("MODEM UL DATA STATS                 \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("UL Read CB NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlDataReadCBNum);
    (VOS_VOID)vos_printf("UL RD SUCC NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum);
    (VOS_VOID)vos_printf("UL RD Fail NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum);
    (VOS_VOID)vos_printf("UL Invalid RD NUM:          %d\r\n", g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum);
    (VOS_VOID)vos_printf("UL Retrun BUFF FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffFailNum);
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("MODEM DL DATA STATS                 \r\n");
    (VOS_VOID)vos_printf("====================================\r\n");
    (VOS_VOID)vos_printf("DL Write Async SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum);
    (VOS_VOID)vos_printf("DL Write Async FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum);
    (VOS_VOID)vos_printf("DL Free BUFF NUM:           %d\r\n", g_stAtStatsInfo.stModemStats.ulDlFreeBuffNum);


    return;
}

/*****************************************************************************
 �� �� ��  : AT_ShowPsEntityInfo
 ��������  : PS��ʵ����Ϣ
 �������  : ucCallId - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowPsEntityInfo(VOS_UINT8 ucCallId)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6PrimDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6SecDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        (VOS_VOID)vos_printf("################MODEM ID is %d################\n", enModemId);
        pstCallEntity = &(AT_GetModemPsCtxAddrFromModemId(enModemId)->astCallEntity[ucCallId]);

        (VOS_VOID)vos_printf("********************PS����ʵ����Ϣ***********************\n");
        (VOS_VOID)vos_printf("Active Flag                             %d\n", pstCallEntity->ulUsedFlg);
        (VOS_VOID)vos_printf("Current Call Type                       %d\n", pstCallEntity->enCurrPdpType);
        (VOS_VOID)vos_printf("********************�û�������Ϣ*************************\n");
        (VOS_VOID)vos_printf("User Actual Index                       %d\n", pstCallEntity->stUserInfo.enPortIndex);
        (VOS_VOID)vos_printf("User Expect Index                       %d\n", pstCallEntity->stUserInfo.enUserIndex);
        (VOS_VOID)vos_printf("User Type                               %d\n", pstCallEntity->stUserInfo.ucUsrType);
        (VOS_VOID)vos_printf("User CID                                %d\n", pstCallEntity->stUserInfo.ucUsrCid);
        (VOS_VOID)vos_printf("********************IPv4������Ϣ*************************\n");
        (VOS_VOID)vos_printf("IPv4 Bearer CID                         %d\n", pstCallEntity->ucIpv4Cid);
        (VOS_VOID)vos_printf("IPv4 Bearer State                       %d\n", pstCallEntity->enIpv4State);
        (VOS_VOID)vos_printf("IPv4 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv4DhcpInfo.ucRabId);
        (VOS_VOID)vos_printf("IPv4 Bearer Address                     0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr);
        (VOS_VOID)vos_printf("IPv4 Bearer Primary DNS                 0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS);
        (VOS_VOID)vos_printf("IPv4 Bearer Secondary DNS               0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS);
        (VOS_VOID)vos_printf("IPv4 Bearer Gate Way                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay);
        (VOS_VOID)vos_printf("IPv4 Bearer NET Mask                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask);
        (VOS_VOID)vos_printf("***********************************************************\n");

        PS_MEM_SET(aucIpv6AddrStr, 0x00, sizeof(aucIpv6AddrStr));
        PS_MEM_SET(aucIpv6PrimDnsStr, 0x00, sizeof(aucIpv6PrimDnsStr));
        PS_MEM_SET(aucIpv6SecDnsStr, 0x00, sizeof(aucIpv6SecDnsStr));

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6PrimDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6SecDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        (VOS_VOID)vos_printf("********************IPv6������Ϣ*************************\n");
        (VOS_VOID)vos_printf("IPv6 Bearer CID                         %d\n", pstCallEntity->ucIpv6Cid);
        (VOS_VOID)vos_printf("IPv6 Bearer State                       %d\n", pstCallEntity->enIpv6State);
        (VOS_VOID)vos_printf("***********************************************************\n");
        (VOS_VOID)vos_printf("IPv6 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv6DhcpInfo.ucRabId);
        (VOS_VOID)vos_printf("IPv6 Bearer Global Address              %s\n", aucIpv6AddrStr);
        (VOS_VOID)vos_printf("IPv6 Bearer Primary DNS                 %s\n", aucIpv6PrimDnsStr);
        (VOS_VOID)vos_printf("IPv6 Bearer Secondary DNS               %s\n", aucIpv6SecDnsStr);
        (VOS_VOID)vos_printf("***********************************************************\n");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ShowPsFcIdState
 ��������  : ��ʾAT���ص�ע����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2013��04��15��
      ��    ��   : f00179208
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowPsFcIdState(VOS_UINT32 ulFcid)
{
    if (ulFcid >= FC_ID_BUTT)
    {
        (VOS_VOID)vos_printf("AT_ShowFcStatsInfo: Fcid overtop, ulFcid = %d\n", ulFcid);
        return;
    }

    (VOS_VOID)vos_printf("ָ��FCID��Ӧ�Ľ���Ƿ���Ч                  %d\n", g_stFcIdMaptoFcPri[ulFcid].ulUsed);
    (VOS_VOID)vos_printf("ָ��FCID��Ӧ�Ľ������ȼ�                  %d\n", g_stFcIdMaptoFcPri[ulFcid].enFcPri);
    (VOS_VOID)vos_printf("ָ��FCID��Ӧ�Ľ���RABID����               %d\n", g_stFcIdMaptoFcPri[ulFcid].ulRabIdMask);
    (VOS_VOID)vos_printf("ָ��FCID��Ӧ�Ľ���ModemId                 %d\n", g_stFcIdMaptoFcPri[ulFcid].enModemId);
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ShowResetStats
 ��������  : ��ʾAT�ź�����ʼ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2013��04��15��
      ��    ��   : f00179208
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowResetStatsInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("ģ���ʼ����ʶ                              %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg);
    (VOS_VOID)vos_printf("��ǰ�Ķ������ź���                          %p\n", AT_GetResetSem());
    (VOS_VOID)vos_printf("�����Ķ������ź���                          %p\n", g_stAtStatsInfo.stCCpuResetStatsInfo.hBinarySemId);
    (VOS_VOID)vos_printf("�����������ź���ʧ�ܴ���                    %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum);
    (VOS_VOID)vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLockBinarySemFailNum);
    (VOS_VOID)vos_printf("���һ�����������ź���ʧ��ԭ��              %x\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLastBinarySemErrRslt);
    (VOS_VOID)vos_printf("C�˸�λǰ�Ĵ���                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetBeforeNum);
    (VOS_VOID)vos_printf("C�˸�λ��Ĵ���                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetAfterNum);
    (VOS_VOID)vos_printf("HIFI��λ�ɹ��Ĵ���                          %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulHifiResetNum);
    (VOS_VOID)vos_printf("AT��λ״̬                                  %d\n", AT_GetResetFlag());
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ShowAllClientState
 ��������  : �˿�״̬��ѯ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��15��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowAllClientState(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    (VOS_VOID)vos_printf("\r\n The All Client State: \r\n");

    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        (VOS_VOID)vos_printf("Client[%d] State: %s    Mode: %s\r\n", i,
            acStateStr[g_stParseContext[i].ucClientStatus], acModeStr[gastAtClientTab[i].Mode]);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_SetClientState
 ��������  : ���ö˿�״̬
 �������  : ucIndex -- clientID
             ulState -- �˿�״̬(Pend/Ready)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��15��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetClientState(VOS_UINT8 ucIndex, VOS_UINT8 ucState)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucState > AT_FW_CLIENT_STATUS_PEND))
    {
        return;
    }

    g_stParseContext[ucIndex].ucClientStatus = ucState;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_SetClientMode
 ��������  : ���ö˿�ģʽ
 �������  : ucIndex -- clientID
             ucMode -- �˿�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��15��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetClientMode(VOS_UINT8 ucIndex, VOS_UINT8 ucMode)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucMode > AT_ONLINE_CMD_MODE))
    {
        return;
    }

    gastAtClientTab[ucIndex].Mode = ucMode;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ShowUsedClient
 ��������  : ��ӡ��ǰʹ�ö˿�״̬
 �������  : ucIndex -- clientID
             ucMode -- �˿�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��15��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowUsedClient(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortCfg;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    pstPortCfg = AT_GetPortBuffCfgInfo();

    (VOS_VOID)vos_printf("\r\n The All Used Client State: \r\n");
    for (i = 0; i < pstPortCfg->ucNum; i++)
    {
        ulIndex = pstPortCfg->ulUsedClientID[i];
        (VOS_VOID)vos_printf("Client[%d] State: %s    Mode: %s\r\n", ulIndex,
            acStateStr[g_stParseContext[ulIndex].ucClientStatus], acModeStr[gastAtClientTab[ulIndex].Mode]);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : AT_ShowClientCtxInfo
 ��������  : ��ӡClient���õ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ShowClientCtxInfo(VOS_VOID)
{
    VOS_UINT8                           i;
    AT_CLIENT_CFG_MAP_TAB_STRU         *pstCfgMapTbl;
    AT_CLIENT_CONFIGURATION_STRU       *pstClientCfg;

    (VOS_VOID)vos_printf("\r\n The All Used Client Config: \r\n");
    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++)
    {
        pstCfgMapTbl = AT_GetClientCfgMapTbl(i);
        pstClientCfg = AT_GetClientConfig(pstCfgMapTbl->enClientId);
        (VOS_VOID)vos_printf("Client[%s] modem:%d, reportFlag:%d\r\n",
                   pstCfgMapTbl->aucPortName,
                   pstClientCfg->enModemId,
                   pstClientCfg->ucReportFlg);
    }
}

/*****************************************************************************
 �� �� ��  : AT_Help
 ��������  : AT��ά�ɲ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("PS�����Ϣ                                              \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowPsEntityInfo         ��ʾ����ʵ����Ϣ            \n");
    (VOS_VOID)vos_printf("AT_ShowPsFcIdState(ulFcid)  ��ʾ���ص�״̬��Ϣ          \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("UART�����Ϣ                                            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowHsUartConfigInfo     ��ʾHSUART��������Ϣ        \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartNvStats        ��ʾHSUART��NV��дͳ����Ϣ  \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartIoctlStats     ��ʾHSUART��IOCTLͳ����Ϣ   \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartDataStats      ��ʾHSUART������ͳ����Ϣ    \n");
    (VOS_VOID)vos_printf("AT_ShowHsUartFcState        ��ʾHSUART������״̬��Ϣ    \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("MODEM�����Ϣ                                           \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowModemDataStats       ��ʾMODEM������ͳ����Ϣ     \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("���������Ϣ                                            \n");
    (VOS_VOID)vos_printf("********************************************************\n");
    (VOS_VOID)vos_printf("AT_ShowResetStatsInfo       ��ʾAT��λ״̬��Ϣ          \n");
    (VOS_VOID)vos_printf("AT_ShowAllClientState       �鿴�˿�״̬��Ϣ            \n");
    (VOS_VOID)vos_printf("AT_ShowClientCtxInfo        �鿴Client���õ���������Ϣ  \n");

    return;
}




