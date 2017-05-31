

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "MnCallApi.h"
#include  "product_config.h"
#include "MnErrorCode.h"
#include "AtParse.h"
#include "ATCmdProc.h"

#include "TafAppCall.h"


/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_API_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_CALL_SendAppRequest
 ��������  : ��APP���첽�����͵�CCA����������
 �������  : enReq    - ���������
              clientId - Client ID
              opId     - ���β����ı�ʶ
              callId   - ���е�ID
              punParam - ������Я���Ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��07��
    ��    ��   : f00179208
    �޸�����   : AT Project, �޸�AT�����WUEPS_PID_VCΪWUEPS_PID_AT
  3.��    ��   : 2012��9��27��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  4.��    ��   : 2012��12��22��
    ��    ��   : l00227485
    �޸�����   : DSDA phaseII

*****************************************************************************/
VOS_UINT32  MN_CALL_SendAppRequest(
    MN_CALL_APP_REQ_ENUM_UINT32         enReq,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_APP_REQ_PARM_UNION   *punParam
)
{
    MN_CALL_APP_REQ_MSG_STRU *pstMsg =
        (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("MN_CALL_SendAppRequest: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(MN_CALL_APP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* ��дԭ���ײ� */
    pstMsg->enReq = enReq;
    pstMsg->clientId = clientId;
    pstMsg->opId = opId;
    pstMsg->callId = callId;

    if (TAF_NULL_PTR != punParam)
    {
        PS_MEM_CPY(&pstMsg->unParm, punParam, sizeof(pstMsg->unParm));
    }

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG1("MN_CALL_SendAppRequest: Send Message Fail. reqtype:", (VOS_INT32)enReq);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_Orig
 ��������  : ����һ������
 �������  : clientId   - Client ID
             opId       - ���β����ı�ʶ
             pstOrigParam - ���в�����Ҫ�Ĳ���
 �������  : pCallId    - ���κ��е�ID, ����Ψһ�ı�ʶ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��06��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ, ����CALLId�ŵ�C��
  3.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
VOS_UINT32  MN_CALL_Orig(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                       *pCallId,
    const MN_CALL_ORIG_PARAM_STRU      *pstOrigParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_ID_T                        callId;

    /* �ڸô����ڷ���CallId��ֱ�ӽ�callId��ֵΪ0
       CallId�ķ���ŵ�MN CALLģ�鴦�������ĺ����� */
    callId = 0;

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ORIG_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstOrigParam);

    *pCallId = callId;

    return ulResult;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_End
 ��������  : �Ҷ�һ������
 �������  : clientId   - Client ID
             opId       - ���β����ı�ʶ
             callId     - ��Ҫ�Ҷϵĺ��е�ID
             pstEndParam  - �Ҷϲ�����Ҫ�Ĳ���, �ò�����ѡ, NULL��ʾʹ��Ĭ�ϲ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��ĿCS��������ϱ����ϱ����ඨ��Ĵ�����

*****************************************************************************/
VOS_UINT32  MN_CALL_End(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParam
)
{
    MN_CALL_END_PARAM_STRU              stEndParam;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stEndParam, 0x00, sizeof(MN_CALL_END_PARAM_STRU));

    if ( TAF_NULL_PTR == pstEndParam)
    {
        /* ���ع���һ��MN_CALL_END_REQ_PARAM_STRU�ṹ, ��дԭ��ֵΪ255 */
        stEndParam.enEndCause = MN_CALL_INTERWORKING_UNSPECIFIED;
        pstEndParam = &stEndParam;
    }

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_END_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstEndParam);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_QryCdur
 ��������  : ��ѯͨ��ʱ��
 �������  : MN_CLIENT_ID_T                      clientId  Client ID
             MN_OPERATION_ID_T                   opId      ���β����ı�ʶ
             MN_CALL_ID_T                        callId    ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  MN_CALL_QryCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_CDUR_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_Answer
 ��������  : ����һ������
 �������  : clientId   - Client ID
             opId       - ���β����ı�ʶ
             callId     - ��Ҫ�����ĺ��е�ID
             pstAnsParam  - ����������Ҫ�Ĳ���, �ò�����ѡ, NULL��ʾʹ��Ĭ�ϲ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_Answer(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
)
{
    MN_CALL_ANS_PARAM_STRU              stAnsParam;
    VOS_UINT32                          ulResult;

    if ( TAF_NULL_PTR == pstAnsParam)
    {
        /* ���ع���һ��MN_CALL_ANS_REQ_PARAM_STRU�ṹ */
        pstAnsParam = &stAnsParam;
    }

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ANSWER_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstAnsParam);
    return ulResult;

}


/*****************************************************************************
 �� �� ��  : TAF_CALL_SendDtmf
 ��������  : APP��TAF����DTMF
 �������  : enMsgType      - DTMF������Ϣ����
             clientId       - Client ID
             opId           - ���β����ı�ʶ
             pstDtmfParam   - ����DTMF������Ҫ�Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_UINT32  TAF_CALL_SendDtmf(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CALL_DTMF_PARAM_STRU     *pstDtmfParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_APP_REQ_PARM_UNION          stAppPara;

    /* ��ʼ���ֲ����� */
    PS_MEM_SET(&stAppPara, 0, sizeof(stAppPara));
    PS_MEM_CPY(&stAppPara.stDtmf, pstDtmfParam, sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(enMsgType, clientId, opId,
                                      pstDtmfParam->CallId,
                                      &stAppPara);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_Sups
 ��������  : ����һ�κ�����ز���ҵ��
 �������  : clientId   - Client ID
             opId       - ���β����ı�ʶ
             pstCallSupsParam   - ���ͺ�����ز���ҵ����Ҫ�Ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  3.��    ��   : 2013��09��30��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ����������CallId���һ��
*****************************************************************************/
VOS_UINT32  MN_CALL_Sups(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulResult;

    /* �����첽Ӧ������ */
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-30, begin */
    /* ��������CallId���һ�� */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_SUPS_CMD_REQ, clientId,
                                      opId, pstCallSupsParam->callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstCallSupsParam);
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-30, end */

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetInfoList
 ��������  : ��ȡ��ǰ����״̬��ΪIDLE�ĺ�����Ϣ
 �������  : pNumOfCalls - �����������ܴ洢�ĺ�����Ϣ����
 �������  : pNumOfCalls - ʵ�������(״̬��ΪIDLE��)������Ϣ����
              pstCallInfos  - ����ĺ�����Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : �޸Ľӿڻ�ȡ��ǰ������Ϣ
  3.��    ��   : 2011��10��15��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ�������첽��Ϣ��C�˻�ȡCALL Info
  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
VOS_UINT32  MN_CALL_GetCallInfos(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_INFO_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_SetAlsLineNo
 ��������  : �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��
 �������  : enAlsLine : ѡ�����·��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��22��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��24��
    ��    ��   : c00173809
    �޸�����   : AT�ں���Ŀ��ͨ���˼�ͨ�ŷ�ʽ����ֱ�ӵ���MN_CALL_UpdateAlsLineInfo������

  3.��    ��   : 2011��10��24��
    ��    ��   : o00132663
    �޸�����   : AT�ں���Ŀ�� CC API����MN_CALL_UpdateAlsLineInfo��Ϊ��Ϣ��
                 ��
  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
VOS_UINT32 MN_CALL_SetAlsLineNo(
    TAF_UINT8                           ucIndex,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_SET_ALS_PARAM_STRU          stSetAls;

    stSetAls.enAlsLine = enAlsLine;

    /*1.ͨ��TAF_MSG_ALS_LINE_NO_SET��Ϣ�������ṹMN_CALL_ALS_PARAM_STRU
        ֪ͨTAF��ALS�������á�*/
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_SET_ALS_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   0,
                                   (MN_CALL_APP_REQ_PARM_UNION*)&stSetAls);

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CheckUus1ParmValid
 ��������  : �������UUS1��������Ƿ�Ϸ�
 �������  : enSetType      :�����ȥ����UUS1
             pstUus1Info    :UUS1�����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32     :�������ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_CheckUus1ParmValid(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    if ( VOS_NULL_PTR == pstUus1Info )
    {
        return MN_ERR_INVALIDPARM;
    }

    /*  У������ĺϷ���,�Ƿ�ֱ�ӷ��� */
    if ( ( enSetType >= MN_CALL_SET_UUS1_BUTT )
      || ( pstUus1Info->enMsgType > MN_CALL_UUS1_MSG_RELEASE_COMPLETE ))
    {
        return MN_ERR_INVALIDPARM;
    }


    /* ����UUIE�ļ�������һ���Ƿ���UUIE,�����ĳ��Ⱥ�PD�����м��,
       ��Ӧ�ñ�֤,������ڼ���UUS1ʱ��Ҫ���,ȥ������ĸ���  */
    if ( ( MN_CALL_SET_UUS1_ACT == enSetType)
      && ( MN_CALL_UUS_IEI != pstUus1Info->aucUuie[MN_CALL_IEI_POS]))
    {
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendFlashReq
 ��������  : APP��TAF����Flash����
 �������  : clientId       - Client ID
             opId           - ���β����ı�ʶ
             pstFlashPara   - ����Flash������Ҫ�Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��8��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendFlashReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_FLASH_PARA_STRU           *pstFlashPara
)
{
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendBurstDtmf
 ��������  : APP��TAF����Flash����
 �������  : clientId              - Client ID
             opId                  - ���β����ı�ʶ
             pstSndBurstDTMFPara   - ����Send Burst Dtmf������Ҫ�Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendBurstDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstSndBurstDTMFPara
)
{
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendCustomDialReq
 ��������  : APP��TAF����Flash����
 �������  : clientId       - Client ID
             opId           - ���β����ı�ʶ
             pstFlashPara   - ����Flash������Ҫ�Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : w00242748
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCustomDialReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CUSTOM_DIAL_PARA_STRU     *pstCustomDialPara
)
{
    return VOS_FALSE;
}



VOS_UINT32  TAF_XCALL_SendContinuousDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CONT_DTMF_PARA_STRU       *pstSndContDTMFPara
)
{
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendCclpr
 ��������  : APP��TAF����Clpr����
 �������  : clientId              - Client ID
             opId                  - ���β����ı�ʶ
             ucCallId               - ����id
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��20��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCclpr(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT8                           ucCallId
)
{
    return VOS_ERR;
}




