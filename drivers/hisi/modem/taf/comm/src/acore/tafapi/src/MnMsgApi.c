

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "ATCmdProc.h"



/*****************************************************************************
  2 ��������
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define THIS_FILE_ID                PS_FILE_ID_MNMSG_API_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/*API���͵���Ϣ���ͺͳ�����һ����ά�����Ӧ����*/
typedef struct
{
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType;
    VOS_UINT16                          usLen;
}MSG_MSGTYPE_LEN_STRU;

/*****************************************************************************
  4 ��������
*****************************************************************************/
LOCAL MSG_MSGTYPE_LEN_STRU             f_astMsgTypeLen[] = {
    {MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT ,sizeof(MN_MSG_SEND_PARM_STRU)},
    {MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM ,sizeof(MN_MSG_SEND_FROMMEM_PARM_STRU)},
    {MN_MSG_MSGTYPE_SEND_RPRPT ,sizeof(MN_MSG_SEND_ACK_PARM_STRU)},
    {MN_MSG_MSGTYPE_WRITE ,sizeof(MN_MSG_WRITE_PARM_STRU)},
    {MN_MSG_MSGTYPE_READ ,sizeof(MN_MSG_READ_PARM_STRU)},
    {MN_MSG_MSGTYPE_LIST ,sizeof(MN_MSG_LIST_PARM_STRU)},
    {MN_MSG_MSGTYPE_DELETE ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_TEST, sizeof(MN_MSG_LIST_PARM_STRU)},
    {MN_MSG_MSGTYPE_WRITE_SRV_PARA ,sizeof(MN_MSG_WRITE_SRV_PARAM_STRU)},
    {MN_MSG_MSGTYPE_READ_SRV_PARA ,sizeof(MN_MSG_READ_COMM_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_SRV_PARA ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_MODIFY_STATUS ,sizeof(MN_MSG_MODIFY_STATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_RCVPATH ,sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_RCVPATH ,sizeof(MN_MSG_GET_RCVMSG_PATH_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_STORAGESTATUS ,sizeof(MN_MSG_GET_STORAGE_STATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_READ_STARPT ,sizeof(MN_MSG_READ_COMM_PARAM_STRU)},
    {MN_MSG_MSGTYPE_DELETE_STARPT ,sizeof(MN_MSG_DELETE_PARAM_STRU)},
    {MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG ,sizeof(MN_MSG_STARPT_MOMSG_PARM_STRU)},
    {MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT ,sizeof(MN_MSG_STARPT_MOMSG_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_MEMSTATUS ,sizeof(MN_MSG_SET_MEMSTATUS_PARM_STRU)},
    {MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL, sizeof(MN_MSG_SET_LINK_CTRL_STRU)},
    {MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL, 0},
    {MN_MSG_MSGTYPE_STUB, sizeof(MN_MSG_STUB_MSG_STRU)},
    {MN_MSG_MSGTYPE_GET_ALLCBMIDS ,0},
    {MN_MSG_MSGTYPE_ADD_CBMIDS ,    sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU)},
    {MN_MSG_MSGTYPE_DELETE_CBMIDS , sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU)},
    {MN_MSG_MSGTYPE_EMPTY_CBMIDS,0}
};

LOCAL MN_MSG_TS_DATA_INFO_STRU         f_stMsgDataInfo;

/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MSG_SendAppReq
 ��������  : ������Ϣ����д��Ϣͷ��������Ϣ�Ĺ�������
 �������  : enMsgType       - ������Ϣ������
             clientId        - ����������Client��ID
             opId            - Operation ID, ��ʶ���β���
             pSendParm       - ��Ҫ���͵Ĳ�������
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573,TQE����
  4.��    ��   : 2012��12��24��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II

*****************************************************************************/
VOS_UINT32 MSG_SendAppReq(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const VOS_VOID                      *pSendParm
)
{
    MN_APP_REQ_MSG_STRU                *pstAppReq;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSendLen;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMaxLoop;

    /* ��Ϣ������Ч���ж� */
    if ((enMsgType >= MN_MSG_MSGTYPE_MAX)
     || (enMsgType <= MN_APP_MSG_CLASS_MSG))
    {
        AT_WARN_LOG("MSG_SendAppReq:Invalid enMsgType. ");
        return MN_ERR_INVALIDPARM;
    }

    /* ��ȡ��Ϣ��Ϣ�ֶγ��� */
    ulMaxLoop    = sizeof(f_astMsgTypeLen)/sizeof(MSG_MSGTYPE_LEN_STRU);
    for (ulLoop = 0; ulLoop < ulMaxLoop; ulLoop++)
    {
        if (enMsgType == f_astMsgTypeLen[ulLoop].enMsgType)
        {
            break;
        }
    }

    if (ulLoop == ulMaxLoop)
    {
        return MN_ERR_CLASS_SMS_INTERNAL;
    }

    ulLen = f_astMsgTypeLen[ulLoop].usLen;

    ulSendLen = (ulLen + sizeof(MN_APP_REQ_MSG_STRU)) - (sizeof(VOS_UINT8)*4);

    /* ��д��������Ϣ */
    pstAppReq = (MN_APP_REQ_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,ulSendLen);

    if (VOS_NULL_PTR == pstAppReq)
    {
        AT_WARN_LOG("MSG_SendAppReq:Alloc Msg Failed");
        return MN_ERR_NOMEM;
    }

    pstAppReq->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstAppReq->ulSenderPid = WUEPS_PID_AT;
    pstAppReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAppReq->ulReceiverPid = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);
    pstAppReq->usMsgName = enMsgType;
    pstAppReq->aucReserve1[0] = 0;
    pstAppReq->aucReserve1[1] = 0;
    pstAppReq->clientId = clientId;
    pstAppReq->opId = opId;
    pstAppReq->aucReserve2[0] = 0;

    if ((ulLen > 0) && (VOS_NULL_PTR != pSendParm))
    {
        PS_MEM_CPY(pstAppReq->aucContent,(VOS_UINT8*)pSendParm,ulLen);
    }
    ulRet = PS_SEND_MSG(WUEPS_PID_AT, pstAppReq);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("MSG_SendAppReq: PS_SEND_MSG fails");
        return MN_ERR_SEND_MSG_ERROR;
    }

    return MN_ERR_NO_ERROR;
}

/* Added by f62575 for AT Project��2011-10-03,  Begin*/
/*****************************************************************************
 �� �� ��  : MN_MSG_ReqStub
 ��������  : ����C��ִ�ж���׮����
 �������  : MN_CLIENT_ID_T                 clientId ����������Client��ID
             MN_OPERATION_ID_T              opId     Operation ID, ��ʶ���β���
             const MN_MSG_STUB_MSG_STRU     *pstStubParam ׮��������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_ReqStub(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STUB_MSG_STRU         *pstStubParam
)
{
    VOS_UINT32                          ulRet;

    /*�ж���������ĺϷ���*/
    if (VOS_NULL_PTR == pstStubParam)
    {
        AT_WARN_LOG("MN_MSG_ReqStub: pstSetParam is Null ");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_STUB,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStubParam);

    return ulRet;
}
/* Added by f62575 for AT Project��2011-10-03,  End*/

/*****************************************************************************
 �� �� ��  : MN_MSG_SetLinkCtrl
 ��������  : Ӧ�������м���·���ƽӿ�
 �������  : clientId          - ����������Client��ID
             opId              - Operation ID, ��ʶ���β���
             pstSetParam    �� - Ӧ�����õ��м���·���ƵĲ�������
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��21��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_SetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SET_LINK_CTRL_STRU     *pstSetParam
)
{
    VOS_UINT32                          ulRet;

    /*�ж���������ĺϷ���*/
    if (VOS_NULL_PTR == pstSetParam)
    {
        AT_WARN_LOG("MN_MSG_SetLinkCtrl:pstSetParam is Null ");
        return MN_ERR_NULLPTR;
    }

    if (pstSetParam->enRelayLinkCtrl >= MN_MSG_LINK_CTRL_BUTT)
    {
        AT_WARN_LOG("MN_MSG_SetLinkCtrl:Invalid value");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSetParam);

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetLinkCtrl
 ��������  : Ӧ�û�ȡ�м���·���ƽӿ�
 �������  : clientId          - ����������Client��ID
             opId              - Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��21��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_GetLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_Send
 ��������  : Ӧ��ֱ�ӷ��Ͷ��źͶ�������ӿ�
 �������  : clientId          - ����������Client��ID
             opId              - Operation ID, ��ʶ���β���
             pstSendDirectParm - Ӧ�÷��Ͷ��ŵĲ�������
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��03��01��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                 ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
*****************************************************************************/
VOS_UINT32   MN_MSG_Send(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_PARM_STRU         *pstSendParm
)
{
    VOS_UINT32                          ulRet;

    /*�ж���������ĺϷ���*/
    if (VOS_NULL_PTR == pstSendParm)
    {
        AT_WARN_LOG("MN_MSG_Send:pstSendDirectParm is Null ");
        return MN_ERR_NULLPTR;
    }

    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED < pstSendParm->enDomain)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid enDomain");
        return MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
    }

    if (MN_MSG_MEM_STORE_NV < pstSendParm->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    /*�������SCADDR,24011Э��涨,BCD�������ٳ�����2,��󳤶���11*/
    if (pstSendParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        if ((pstSendParm->stMsgInfo.stScAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
         || (pstSendParm->stMsgInfo.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            AT_WARN_LOG("MN_MSG_Send:Invalid SC Address");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    /*�ж�����TPDU��ʽ�ĺϷ���,�������Ƿ�ɹ�*/
    if ((MN_MSG_TPDU_COMMAND != pstSendParm->stMsgInfo.stTsRawData.enTpduType)
     && (MN_MSG_TPDU_SUBMIT != pstSendParm->stMsgInfo.stTsRawData.enTpduType))
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    PS_MEM_SET(&f_stMsgDataInfo,0X00,sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstSendParm->stMsgInfo.stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_Send:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    if (MN_MSG_TPDU_SUBMIT == pstSendParm->stMsgInfo.stTsRawData.enTpduType)
    {
        if (MN_MSG_TPDU_SUBMIT != f_stMsgDataInfo.enTpduType)
        {
            AT_WARN_LOG("MN_MSG_Send:Conflict TPDU type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }

        if (0 == f_stMsgDataInfo.u.stSubmit.stDestAddr.ulLen)
        {
            AT_WARN_LOG("MN_MSG_Send:No DA");
            return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
        }
    }
    else
    {
        if (MN_MSG_TPDU_COMMAND != f_stMsgDataInfo.enTpduType)
        {
            AT_WARN_LOG("MN_MSG_Send:Conflict TPDU type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSendParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SendFromMem
 ��������  : ���ڴ�USIM��NVIM�з��Ͷ��Žӿ�
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             enDomain           - ���ŷ�����
             pstSendFromMemParm - ���ڴ��з��Ͷ��ŵĲ�������
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_SendFromMem(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_FROMMEM_PARM_STRU *pstSendFromMemParm
)
{
    VOS_UINT32                          ulRet;

    /*�ж���������ĺϷ���*/
    if (VOS_NULL_PTR == pstSendFromMemParm)
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:pstSendFromMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED < pstSendFromMemParm->enDomain)
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid enDomain");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstSendFromMemParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstSendFromMemParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((pstSendFromMemParm->stDestAddr.ucBcdLen > 0)
     && ((pstSendFromMemParm->stDestAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
      || (pstSendFromMemParm->stDestAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)))
    {
        AT_WARN_LOG("MN_MSG_SendFromMem:Invalid Dest Address");
        return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSendFromMemParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SendAck
 ��������  : �յ����ź�,Ӧ�ÿɵ��øýӿڷ����յ����ŵı���,RP-ACK��RP-ERROR
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstAckParm         - ���Ͷ��ű��������Ϣ
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_SendAck(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_ACK_PARM_STRU     *pstAckParm
)
{
    VOS_UINT32                          ulRet;

    /*�ж���������ĺϷ���*/
    if (VOS_NULL_PTR == pstAckParm)
    {
        AT_WARN_LOG("MN_MSG_SendAck:pstAckParm is Null");
        return MN_ERR_NULLPTR;
    }
    /*������Deliver Ack ��Deliver Err*/
    if ((MN_MSG_TPDU_DELIVER_RPT_ACK != pstAckParm->stTsRawData.enTpduType)
     && (MN_MSG_TPDU_DELIVER_RPT_ERR != pstAckParm->stTsRawData.enTpduType))
    {
        AT_WARN_LOG("MN_MSG_SendAck:Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }
    /*�ж�����TPDU��ʽ�ĺϷ���,�������Ƿ�ɹ�*/
    PS_MEM_SET(&f_stMsgDataInfo,0X00,sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstAckParm->stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_SendAck:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SEND_RPRPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstAckParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_Write
 ��������  : ��USIM��NVIM��дһ������
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstWriteParm   - д���Ų���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_Write(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_PARM_STRU        *pstWriteParm
)
{
    VOS_UINT32                          ulRet;

    /*�ж���������ĺϷ���*/
    if (VOS_NULL_PTR == pstWriteParm)
    {
        AT_WARN_LOG("MN_MSG_Write:pstWriteParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_WRITE_MODE_INSERT != pstWriteParm->enWriteMode)
     && (MN_MSG_WRITE_MODE_REPLACE != pstWriteParm->enWriteMode))
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enWriteMode");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstWriteParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstWriteParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (pstWriteParm->enStatus >= MN_MSG_STATUS_NONE)
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    /*�����SC ADDR,�ж�SC ADDR�Ƿ����*/
    if (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        if ((pstWriteParm->stMsgInfo.stScAddr.ucBcdLen < MN_MSG_MIN_BCD_NUM_LEN)
         || (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN))
        {
            AT_WARN_LOG("MN_MSG_Send:Invalid SC Address");
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    /*�ж�����TPDU��ʽ�ĺϷ���,�������Ƿ�ɹ�*/
    PS_MEM_SET(&f_stMsgDataInfo,0X00,sizeof(f_stMsgDataInfo));
    ulRet = MN_MSG_Decode(&pstWriteParm->stMsgInfo.stTsRawData,&f_stMsgDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_WARN_LOG("MN_MSG_Write:Invalid Tpdu");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_WRITE,
                           clientId,
                           opId,
                           (VOS_VOID *)pstWriteParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_Read
 ��������  : ��USIM��NVIM�ж�һ������
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstReadParm    - ��ȡ����
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_Read(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_PARM_STRU         *pstReadParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParm)
    {
        AT_WARN_LOG("MN_MSG_Read:pstReadParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstReadParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Read:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParm);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_List
 ��������  : ��USIM��NVIM���б�ĳ��״̬����
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstListParm    - �б����
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_List(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstListParm)
    {
        AT_WARN_LOG("MN_MSG_List:pstListParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstListParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstListParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_List:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_STATUS_NONE < pstListParm->enStatus)
    {
        AT_WARN_LOG("MN_MSG_List:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_LIST,
                           clientId,
                           opId,
                           (VOS_VOID *)pstListParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_Delete
 ��������  : ��USIM��NVIM���б�ɾ������
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstDeleteParm  - ɾ������,�������ʹ洢λ�õȵ�
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_Delete(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU      *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_Delete:pstDelete is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_DELETE_ALL < pstDeleteParam->enDeleteType)
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_Delete_Test
 ��������  : ��USIM��NVIM���б�ɾ����������Ĳ��Բ���
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             enMemStore     - ɾ�����Ų�����������Ĵ洢��������
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_Delete_Test(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstListPara
)
{
    VOS_UINT32                          ulRet;

    if ((MN_MSG_MEM_STORE_SIM != pstListPara->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstListPara->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (pstListPara->enStatus >= MN_MSG_STATUS_MAX)
    {
        AT_WARN_LOG("MN_MSG_Delete:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_TEST,
                           clientId,
                           opId,
                           (VOS_VOID *)pstListPara);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReadStaRpt
 ��������  : ��USIM��NVIM�ж�һ������״̬����
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstReadParm         - ��ȡ����,�������ʹ洢λ�õȵ�
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ�������
  3.��    ��   : 2014��5��30��
    ��    ��   : j00174725
    �޸�����   : TQE
*****************************************************************************/
VOS_UINT32   MN_MSG_ReadStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU   *pstReadParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParam)
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:pstReadParam is Null");
        return MN_ERR_NULLPTR;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ((MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:Invalid enMemStore1");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_ReadStaRpt:Invalid enMemStore2");
        return MN_ERR_INVALIDPARM;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_DeleteStaRpt
 ��������  : ��USIM��NVIM���б�ɾ������״̬����
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstDelete      - ɾ������,������,�洢λ��
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
 2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:APIɾ�������
*****************************************************************************/
VOS_UINT32   MN_MSG_DeleteStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:pstDeleteParam is Null");
        return MN_ERR_NULLPTR;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
     && (MN_MSG_DELETE_ALL != pstDeleteParam->enDeleteType))
    {
        AT_WARN_LOG("MN_MSG_DeleteStaRpt:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_STARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_WriteSrvParam
 ��������  : ���ö�����ز���,��������ģ���Ч�ڵȵ�
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstSrvParam     - ��Ҫ���õĲ���,��������ĵȵ�
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_WriteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_SRV_PARAM_STRU   *pstSrvParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstSrvParam)
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:pstSetSrvParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_WRITE_MODE_INSERT != pstSrvParam->enWriteMode)
     && (MN_MSG_WRITE_MODE_REPLACE != pstSrvParam->enWriteMode))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid enWriteMode");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstSrvParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstSrvParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV == pstSrvParam->enMemStore)
     && (0 != pstSrvParam->ulIndex))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Only one record supported in NV.");
        return MN_ERR_INVALIDPARM;
    }

    /*������õ�ֵû��һ����Ч,�򷵻�*/
    if (MN_MSG_SRV_PARM_TOTALABSENT == (pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_TOTALABSENT))
    {
        AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid Parm,No Valid Data");
        return MN_ERR_INVALIDPARM;
    }

    /*�ж�SC Addr��Dest Addr����Ч��*/
    if (MN_MSG_SRV_PARM_PRESENT ==
        ((pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR) >> 1))
    {
       if (pstSrvParam->stSrvParm.stScAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)
       {
           AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid SC Address");
           return MN_ERR_CLASS_SMS_INVALID_SCADDR;
       }
    }

    if (MN_MSG_SRV_PARM_PRESENT ==
        (pstSrvParam->stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
    {
        if (pstSrvParam->stSrvParm.stDestAddr.ucBcdLen > MN_MSG_MAX_BCD_NUM_LEN)
        {
            AT_WARN_LOG("MN_MSG_WriteSrvParam:Invalid Dest Address");
            return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_WRITE_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSrvParam);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReadSrvParam
 ��������  : ��ȡ������ز���,��������ģ���Ч�ڵȵ�
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstReadParm    - ��ȡ����,�������ʹ洢λ�õȵ�
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_ReadSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU  *pstReadParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstReadParam)
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam:pstReadParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstReadParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstReadParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV == pstReadParam->enMemStore)
     && (0 != pstReadParam->ulIndex))
    {
        AT_WARN_LOG("MN_MSG_ReadSrvParam: Only one record supported in NV.");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_READ_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstReadParam);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_DeleteSrvParam
 ��������  : ɾ��������ز���,��������ģ���Ч�ڵȵ�
 �������  : clientId        - ����������Client��ID
             opId            - Operation ID, ��ʶ���β���
             pstDeleteParm   - ɾ������,������,�洢λ�õȵ�
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_DeleteSrvParam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU     *pstDeleteParam
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstDeleteParam)
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:pstDeleteParam is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstDeleteParam->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstDeleteParam->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
     && (MN_MSG_DELETE_ALL != pstDeleteParam->enDeleteType))
    {
        AT_WARN_LOG("MN_MSG_DeleteSrvParam:Invalid enDeleteType");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_NV == pstDeleteParam->enMemStore)
    {
        if ((MN_MSG_DELETE_SINGLE != pstDeleteParam->enDeleteType)
         && (0 != pstDeleteParam->ulIndex))
        {
            AT_WARN_LOG("MN_MSG_WriteSrvParam:Only one record supported in NV.");
            return MN_ERR_INVALIDPARM;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_SRV_PARA,
                           clientId,
                           opId,
                           (VOS_VOID *)pstDeleteParam);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ModifyStatus
 ��������  : �޸Ķ���״̬��ͨ���ýӿڿ��Խ����յ��Ķ����޸�Ϊ�Ѷ���δ��״̬��
                                     ����SUMBIT��COMMAND����Ϣ�޸�Ϊ�ѷ��ͻ�δ����״̬
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstModifyParm       - �޸Ķ���״̬��ز���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_ModifyStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_MODIFY_STATUS_PARM_STRU *pstModifyParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstModifyParm)
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:pstModifyParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstModifyParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstModifyParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_STATUS_MO_SENT < pstModifyParm->enStatus)
    {
        AT_WARN_LOG("MN_MSG_ModifyStatus:Invalid enStatus");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_MODIFY_STATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstModifyParm);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_SetRcvMsgPath
 ��������  : ���ý��ն���·��,�����洢λ�úͶ��ű����Ӧ��
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstRcvPathParm      - ����·����ز���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_SetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstSetRcvPathParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstSetRcvPathParm)
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:pstSetRcvPathParm is Null");
        return MN_ERR_NULLPTR;
    }

    if  ((MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK < pstSetRcvPathParm->enRcvSmAct)
      || (MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK < pstSetRcvPathParm->enRcvStaRptAct))
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid enRcvSmAct");
        return MN_ERR_INVALIDPARM;
    }

    if ((MN_MSG_MEM_STORE_NV < pstSetRcvPathParm->enSmMemStore)
     || (MN_MSG_MEM_STORE_NV < pstSetRcvPathParm->enStaRptMemStore))
    {
        AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid enSmMemStore");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_RCVMSG_ACT_STORE == pstSetRcvPathParm->enRcvSmAct)
    {
        if ((MN_MSG_MEM_STORE_NV  != pstSetRcvPathParm->enSmMemStore)
         && (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enSmMemStore))
        {
            AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid Parm");
            return MN_ERR_INVALIDPARM;
        }
    }

    if (MN_MSG_RCVMSG_ACT_STORE == pstSetRcvPathParm->enRcvStaRptAct)
    {
        if ((MN_MSG_MEM_STORE_NV  != pstSetRcvPathParm->enStaRptMemStore)
         && (MN_MSG_MEM_STORE_SIM != pstSetRcvPathParm->enStaRptMemStore))
        {
            AT_WARN_LOG("MN_MSG_SetRcvMsgPath:Invalid Parm");
            return MN_ERR_INVALIDPARM;
        }
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_RCVPATH,
                           clientId,
                           opId,
                           (VOS_VOID *)pstSetRcvPathParm);

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetRcvMsgPath
 ��������  : ��ȡ���ն���·��,�����洢λ�úͶ��ű���Ӧ��
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstGetRcvPathParm   - ��ȡ·����ز���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_GetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_GET_RCVMSG_PATH_PARM_STRU *pstGetRcvPathParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstGetRcvPathParm)
    {
        AT_WARN_LOG("MN_MSG_GetRcvMsgPath:pstGetRcvPathParm is Null");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_RCVPATH,
                           clientId,
                           opId,
                           (VOS_VOID *)pstGetRcvPathParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetStorageStatus
 ��������  : ��ȡ���ŵ�ǰ�Ĵ洢״��
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstMemParm          - ���Ŵ洢λ����ز���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_MSG_GetStorageStatus(
    MN_CLIENT_ID_T                            clientId,
    MN_OPERATION_ID_T                         opId,
    const MN_MSG_GET_STORAGE_STATUS_PARM_STRU *pstStorageParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstStorageParm)
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:pstMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstStorageParm->enMem1Store)
     && (MN_MSG_MEM_STORE_NV != pstStorageParm->enMem1Store)
     && (MN_MSG_MEM_STORE_NONE != pstStorageParm->enMem1Store))
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:Invalid enMemStore:mem1");
        return MN_ERR_INVALIDPARM;
    }

    if (pstStorageParm->enMem1Store == pstStorageParm->enMem2Store)
    {
        AT_WARN_LOG("MN_MSG_GetStorageStatus:Invalid enMemStore:mem1 == mem2");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_STORAGESTATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStorageParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetStatusRptIndex
 ��������  : ����MO���������õ���״̬��������
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstMoMsgParm   - MO���ŵĲ���,���к�λ��
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   MN_MSG_GetStaRptIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstMoMsgParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstMoMsgParm)
    {
        AT_WARN_LOG("MN_MSG_GetStaRptFromMoMsg:pstMoMsgParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_STORE_SIM != pstMoMsgParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstMoMsgParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_GetStaRptFromMoMsg:Invalid enMemStore");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG,
                           clientId,
                           opId,
                           (VOS_VOID *)pstMoMsgParm);

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoMsgIndex
 ��������  : ���ݶ���״̬���������õ�MO���ŵ�����
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             pstStaRptParm  - ����״̬����Ĳ���,������λ��

 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
*****************************************************************************/
VOS_UINT32   MN_MSG_GetMoMsgIndex(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstStaRptParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstStaRptParm)
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:pstMemParm is Null");
        return MN_ERR_NULLPTR;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ((MN_MSG_MEM_STORE_SIM != pstStaRptParm->enMemStore)
     && (MN_MSG_MEM_STORE_NV != pstStaRptParm->enMemStore))
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:Invalid enMemStore1");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_MEM_STORE_SIM != pstStaRptParm->enMemStore)
    {
        AT_WARN_LOG("MN_MSG_GetMoMsgFromStaRpt:Invalid enMemStore2");
        return MN_ERR_INVALIDPARM;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT,
                           clientId,
                           opId,
                           (VOS_VOID *)pstStaRptParm);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SetMemStatus
 ��������  : APP���õ�ǰ�Ľ�������,������
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pMemStatusParm      - APP��ǰ��������
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_SetMemStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SET_MEMSTATUS_PARM_STRU *pMemStatusParm
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pMemStatusParm)
    {
        AT_WARN_LOG("MN_MSG_SetMemStatus:pMemStatusParm is Null");
        return MN_ERR_NULLPTR;
    }

    if ((MN_MSG_MEM_FULL_SET != pMemStatusParm->enMemFlag)
     && (MN_MSG_MEM_FULL_UNSET != pMemStatusParm->enMemFlag))
    {
        AT_WARN_LOG("MN_MSG_SetMemStatus:Invalid enMemFlag");
        return MN_ERR_INVALIDPARM;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_SET_MEMSTATUS,
                           clientId,
                           opId,
                           (VOS_VOID *)pMemStatusParm);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_GetAllCbMids
 ��������  : �ṩ��Ӧ�ò��ѯCBS�б��ܵ�����
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��10��
    ��    ��   : zhoujun \z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_GetAllCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_GET_ALLCBMIDS,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_AddCbMids
 ��������  : �ṩ��Ӧ�ò�򿪻�ر�CBS���ܵ�����
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCbMids          - �����ӵĹ㲥����ϢID����
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��8��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32 MN_MSG_AddCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstCbmirList)
    {
        AT_WARN_LOG("MN_MSG_DeleteCbMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_ADD_CBMIDS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstCbmirList);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_DeleteCbMids
 ��������  : �ṩ��Ӧ�ò�򿪻�ر�CBS���ܵ�����
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCbMids          - ��ɾ���Ĺ㲥����ϢID����
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR���ɹ�
             ������ʧ�ܼ���ʧ�ܵ�ԭ��
 ���ú���  :
 ��������  :

 1.��    ��   : 2010��5��8��
   ��    ��   : zhoujun /z40661
   �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32 MN_MSG_DelCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CBA_CBMI_RANGE_LIST_STRU *pstCbmirList
)
{
    VOS_UINT32                          ulRet;

    if (VOS_NULL_PTR == pstCbmirList)
    {
        AT_WARN_LOG("MN_MSG_DeleteCbMsg: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_DELETE_CBMIDS,
                           clientId,
                           opId,
                           (VOS_VOID *)pstCbmirList);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_EmptyCbMids
 ��������  : ɾ������CBS ID
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��8��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_EmptyCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;

    ulRet = MSG_SendAppReq(MN_MSG_MSGTYPE_EMPTY_CBMIDS,
                           clientId,
                           opId,
                           VOS_NULL_PTR);

    return ulRet;
}


