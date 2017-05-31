

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtCmdImsProc.h"
#include "ATCmdProc.h"

#include "AtDataProc.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_IMS_PROC_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*AT��IMSAģ�����Ϣ������ָ��*/
const AT_IMSA_MSG_PRO_FUNC_STRU g_astAtImsaMsgTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
    {ID_IMSA_AT_CIREG_SET_CNF,              AT_RcvImsaCiregSetCnf},
    {ID_IMSA_AT_CIREG_QRY_CNF,              AT_RcvImsaCiregQryCnf},
    {ID_IMSA_AT_CIREP_SET_CNF,              AT_RcvImsaCirepSetCnf},
    {ID_IMSA_AT_CIREP_QRY_CNF,              AT_RcvImsaCirepQryCnf},
    {ID_IMSA_AT_VOLTEIMPU_QRY_CNF,          AT_RcvImsaImpuSetCnf},
    {ID_IMSA_AT_CIREGU_IND,                 AT_RcvImsaCireguInd},
    {ID_IMSA_AT_CIREPH_IND,                 AT_RcvImsaCirephInd},
    {ID_IMSA_AT_CIREPI_IND,                 AT_RcvImsaCirepiInd},

    {ID_IMSA_AT_VT_PDP_ACTIVATE_IND,        AT_RcvImsaVtPdpActInd},
    {ID_IMSA_AT_VT_PDP_DEACTIVATE_IND,      AT_RcvImsaVtPdpDeactInd},
    {ID_IMSA_AT_MT_STATES_IND,              AT_RcvImsaMtStateInd},
    {ID_IMSA_AT_IMS_CTRL_MSG,               AT_RcvImsaImsCtrlMsg},
    {ID_IMSA_AT_IMS_REG_DOMAIN_QRY_CNF,     AT_RcvImsaImsRegDomainQryCnf},
    {ID_IMSA_AT_CALL_ENCRYPT_SET_CNF,       AT_RcvImsaCallEncryptSetCnf},
    {ID_IMSA_AT_ROAMING_IMS_QRY_CNF,        AT_RcvImsaRoamImsServiceQryCnf},

    {ID_IMSA_AT_IMS_RAT_HANDOVER_IND,       AT_RcvImsaRatHandoverInd},
    {ID_IMSA_AT_IMS_SRV_STATUS_UPDATE_IND,  AT_RcvSrvStatusUpdateInd},
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : AT_ProcImsaMsg
 ��������  : ��������IMSAģ�����Ϣ
 �������  : AT_IMSA_MSG_STRU *pMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID AT_ProcImsaMsg(AT_IMSA_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*��g_astAtProcMsgFromImsaTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtImsaMsgTab)/sizeof(AT_IMSA_MSG_PRO_FUNC_STRU);

    /*����Ϣ���л�ȡMSG ID*/
    ulMsgId  = pstMsg->ulMsgId;

    /*g_astAtProcMsgFromImsaTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtImsaMsgTab[i].ulMsgId == ulMsgId)
        {
            ulRst = g_astAtImsaMsgTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("AT_ProcImsaMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("AT_ProcImsaMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCiregSetCnf
 ��������  : +CIREG��������ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCiregSetCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREG_SET_CNF_STRU         *pstCiregCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstCiregCnf = (IMSA_AT_CIREG_SET_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCiregCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCiregSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCiregSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CIREG_SET */
    if ( AT_CMD_CIREG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCiregSetCnf: WARNING:Not AT_CMD_CIREG_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( VOS_OK == pstCiregCnf->ulResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCiregQryCnf
 ��������  : +CIREG��ѯ����ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCiregQryCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREG_QRY_CNF_STRU         *pstCiregCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    usLength    = 0;
    pstCiregCnf = (IMSA_AT_CIREG_QRY_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCiregCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCiregQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCiregQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CIREG_QRY */
    if ( AT_CMD_CIREG_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCiregQryCnf: WARNING:Not AT_CMD_CIREG_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( VOS_OK == pstCiregCnf->ulResult )
    {

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: %d,",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstCiregCnf->enCireg);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                           "%d",
                                           pstCiregCnf->ulRegInfo);

        /* ���IMSδע�ᣬ<ext_info>���������壬�Ҳ���������3GPP 27007 v11 8.71 */
        if ((VOS_FALSE != pstCiregCnf->ulRegInfo) && (VOS_FALSE != pstCiregCnf->bitOpExtInfo))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr+usLength,
                                               ",%d",
                                               pstCiregCnf->ulExtInfo);
        }

        ulResult                = AT_OK;
    }
    else
    {
        ulResult                = AT_ERROR;
    }

    gstAtSendData.usBufLen  = usLength;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCirepSetCnf
 ��������  : +CIREP��������ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirepSetCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREP_SET_CNF_STRU         *pstCirepCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstCirepCnf = (IMSA_AT_CIREP_SET_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirepCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirepSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCirepSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CIREP_SET */
    if ( AT_CMD_CIREP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCirepSetCnf: WARNING:Not AT_CMD_CIREP_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( VOS_OK == pstCirepCnf->ulResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCirepQryCnf
 ��������  : +CIREP��ѯ����ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirepQryCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREP_QRY_CNF_STRU         *pstCirepCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstCirepCnf = (IMSA_AT_CIREP_QRY_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirepCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirepQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCirepQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CIREP_QRY */
    if ( AT_CMD_CIREP_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaCirepQryCnf: WARNING:Not AT_CMD_CIREP_QRY!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( VOS_OK == pstCirepCnf->ulResult )
    {

        gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d,%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstCirepCnf->enReport,
                                                       pstCirepCnf->enImsvops);

        ulResult                = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen  = 0;
        ulResult                = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_RcvImsaImpuSetCnf
 ��������  : +CIREP��ѯ����ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��17��
    ��    ��   : c64416
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaImpuSetCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_VOLTEIMPU_QRY_CNF_STRU      *pstImpuCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_CHAR                            acString[AT_IMSA_IMPU_MAX_LENGTH+1];

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstImpuCnf  = (IMSA_AT_VOLTEIMPU_QRY_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstImpuCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_IMPU_SET */
    if ( AT_CMD_IMPU_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:Not AT_CMD_IMPU_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    VOS_MemSet(acString, 0, sizeof(acString));
    if(pstImpuCnf->ulImpuLen > AT_IMSA_IMPU_MAX_LENGTH)
    {
        VOS_MemCpy(acString, pstImpuCnf->aucImpu, AT_IMSA_IMPU_MAX_LENGTH);
    }
    else
    {
        VOS_MemCpy(acString, pstImpuCnf->aucImpu, pstImpuCnf->ulImpuLen);
    }

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( VOS_OK == pstImpuCnf->ulResult )
    {

        gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %s",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       acString);

        ulResult                = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen  = 0;
        ulResult                = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCirephInd
 ��������  : +CIREPH�����ϱ��������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirephInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREPH_IND_STRU            *pstCirephInd;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ���� */
    ucIndex      = 0;
    pstCirephInd = (IMSA_AT_CIREPH_IND_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirephInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirephInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: %d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CIREPH].pucText,
                                                    pstCirephInd->enHandover,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCirepiInd
 ��������  : +CIREPI�����ϱ��������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCirepiInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREPI_IND_STRU            *pstCirepiInd;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ���� */
    ucIndex      = 0;
    pstCirepiInd = (IMSA_AT_CIREPI_IND_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCirepiInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCirepiInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: %d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_CIREPI].pucText,
                                                    pstCirepiInd->enImsvops,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaCireguInd
 ��������  : +CIREGU�����ϱ��������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCireguInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CIREGU_IND_STRU            *pstCireguInd;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ��ʼ����Ϣ���� */
    ucIndex      = 0;
    usLength     = 0;
    pstCireguInd = (IMSA_AT_CIREGU_IND_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCireguInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaCireguInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s%s: %d",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_CIREGU].pucText,
                                       pstCireguInd->ulRegInfo);

    /* ���IMSδע�ᣬ<ext_info>���������� */
    if ((VOS_FALSE != pstCireguInd->ulRegInfo) && (VOS_FALSE != pstCireguInd->bitOpExtInfo))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstCireguInd->ulExtInfo);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : AT_RcvImsaVtIpv4PdpActInd
 ��������  : VT IPV4���ؼ���ָʾ������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID AT_RcvImsaVtIpv4PdpActInd(
    VOS_UINT8                           ucIndex,
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd
)
{
    VOS_UINT32                          ulIPAddr;                               /* IP ��ַ���������*/
    VOS_UINT32                          ulSubNetMask;                           /* ���������ַ������IP��ַ����*/
    VOS_UINT32                          ulGateWay;                              /* ���ص�ַ��Ҳ�Ǳ�DHCP Server�ĵ�ַ*/
    VOS_UINT32                          ulPrimDNS;                              /* �� DNS��ַ���������*/
    VOS_UINT32                          ulSecDNS;                               /* �� DNS��ַ���������*/

    ulIPAddr     = AT_GetLanAddr32(pstPdpActInd->stPdpAddr.aucIpv4Addr);
    ulSubNetMask = AT_DHCPGetIPMask(ulIPAddr);
    ulGateWay    = AT_DHCPGetGateWay(ulIPAddr, ulSubNetMask);
    ulPrimDNS    = 0;
    ulSecDNS     = 0;

    if (IMSA_AT_IMS_RAT_TYPE_LTE != pstPdpActInd->enRatType)
    {
        AT_WARN_LOG("AT_RcvImsaVtIpv4PdpActInd: WARNING: enRatType is not LTE");
        return;
    }

    if (pstPdpActInd->stIpv4Dns.bitOpPrimDnsAddr)
    {
        ulPrimDNS = AT_GetLanAddr32(pstPdpActInd->stIpv4Dns.aucPrimDnsAddr);
    }

    if (pstPdpActInd->stIpv4Dns.bitOpSecDnsAddr)
    {
        ulSecDNS = AT_GetLanAddr32(pstPdpActInd->stIpv4Dns.aucSecDnsAddr);
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^VTDCONNV4:%08X,%08X,%08X,%08X,%08X,%08X,%d%s",
                                                    gaucAtCrLf,
                                                    VOS_HTONL(ulIPAddr),
                                                    VOS_HTONL(ulSubNetMask),
                                                    VOS_HTONL(ulGateWay),
                                                    VOS_HTONL(ulGateWay),
                                                    VOS_HTONL(ulPrimDNS),
                                                    VOS_HTONL(ulSecDNS),
                                                    pstPdpActInd->enRatType,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaVtIpv6PdpActInd
 ��������  : VT IPV6���ؼ���ָʾ������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID AT_RcvImsaVtIpv6PdpActInd(
    VOS_UINT8                           ucIndex,
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength     = 0;
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, TAF_IPV6_ADDR_LEN);

    if (IMSA_AT_IMS_RAT_TYPE_LTE != pstPdpActInd->enRatType)
    {
        AT_WARN_LOG("AT_RcvImsaVtIpv6PdpActInd: WARNING: enRatType is not LTE");
        return;
    }

    usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s^VTDCONNV6:", gaucAtCrLf);

    /* ��дIPV6��ַ */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstPdpActInd->stPdpAddr.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дDHCP IPV6, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstPdpActInd->stIpv6Dns.aucPrimDnsAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstPdpActInd->stIpv6Dns.aucSecDnsAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", pstPdpActInd->enRatType);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                          (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", gaucAtCrLf);


    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaVtIpv4v6PdpActInd
 ��������  : VT IPV4V6���ؼ���ָʾ������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID AT_RcvImsaVtIpv4v6PdpActInd(
    VOS_UINT8                           ucIndex,
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd
)
{
    AT_RcvImsaVtIpv4PdpActInd(ucIndex, pstPdpActInd);
    AT_RcvImsaVtIpv6PdpActInd(ucIndex, pstPdpActInd);
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaVtPdpActInd
 ��������  : VT���ؼ���ָʾ������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaVtPdpActInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_VT_PDP_ACTIVATE_IND_STRU   *pstPdpActInd;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstPdpActInd = (IMSA_AT_VT_PDP_ACTIVATE_IND_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstPdpActInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaVtPdpActInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    switch(pstPdpActInd->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_RcvImsaVtIpv4PdpActInd(ucIndex, pstPdpActInd);
            break;
        case TAF_PDP_IPV6:
            AT_RcvImsaVtIpv6PdpActInd(ucIndex, pstPdpActInd);
            break;
        case TAF_PDP_IPV4V6:
            AT_RcvImsaVtIpv4v6PdpActInd(ucIndex, pstPdpActInd);
            break;
        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaVtPdpDeactInd
 ��������  : VT����ȥ����ָʾ������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaVtPdpDeactInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU *pstPdpDeactInd;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ��ʼ����Ϣ���� */
    usLength       = 0;
    ucIndex        = 0;
    pstPdpDeactInd = (IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstPdpDeactInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaVtPdpDeactInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (IMSA_AT_IMS_RAT_TYPE_LTE != pstPdpDeactInd->enRatType)
    {
        AT_WARN_LOG("AT_RcvImsaVtPdpDeactInd: WARNING: enRatType is not LTE");
        return VOS_ERR;
    }

    switch(pstPdpDeactInd->enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^VTDENDV4:%d%s",
                                               gaucAtCrLf,
                                               pstPdpDeactInd->enRatType,
                                               gaucAtCrLf);
            break;
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                            "%s^VTDENDV6:%d%s",
                                                            gaucAtCrLf,
                                                            pstPdpDeactInd->enRatType,
                                                            gaucAtCrLf);
            break;
        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                            "%s^VTDENDV4:%d%s",
                                                            gaucAtCrLf,
                                                            pstPdpDeactInd->enRatType,
                                                            gaucAtCrLf);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                            "%s^VTDENDV6:%d%s",
                                                            gaucAtCrLf,
                                                            pstPdpDeactInd->enRatType,
                                                            gaucAtCrLf);

            break;
        default:
            return VOS_ERR;
    }

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaMtStateInd
 ��������  : ����״ָ̬ʾ������
 �������  : *pMsg        IMSA�ϱ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��18��
    ��    ��   : m00277840
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaMtStateInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_MT_STATES_IND_STRU          *pstMtStatusInd;
    VOS_UINT8                           ucIndex;
    VOS_CHAR                            acString[AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH + 1];

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstMtStatusInd  = (IMSA_AT_MT_STATES_IND_STRU*)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtStatusInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaImpuSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    VOS_MemSet(acString, 0, sizeof(acString));
    VOS_MemCpy(acString, pstMtStatusInd->aucAsciiCallNum, AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH);

    gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s^IMSMTRPT: %s,%d,%d%s",
                                                   gaucAtCrLf,
                                                   acString,
                                                   pstMtStatusInd->ucMtStatus,
                                                   pstMtStatusInd->ulCauseCode,
                                                   gaucAtCrLf);
    /* ����At_SendResultData���������� */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : AT_RcvImsaImsRegDomainQryCn
 ��������  : ^IMSREGDOMAIN?��ѯ����ظ�������
 �������  : *pMsg        IMSA�ϱ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��18��
    ��    ��   : h00360002
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaImsRegDomainQryCnf(VOS_VOID *pMsg)
{
    /* �ֲ����� */
    IMSA_AT_IMS_REG_DOMAIN_QRY_CNF_STRU     *pstImsRegDomainCnf = VOS_NULL_PTR;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    /* ��ʼ������ */
    ucIndex             = 0;
    ulResult            = 0;
    pstImsRegDomainCnf  = (IMSA_AT_IMS_REG_DOMAIN_QRY_CNF_STRU *)pMsg;

    /* ��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstImsRegDomainCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaImsRegDomainQryCnf: WARNING: AT INDEX NOT FOUND1");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaImsRegDomainQryCnf: WARNING: AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ�����Ƿ�ΪAT_CMD_IMSREGDOMAIN_QRY */
    if (AT_CMD_IMSREGDOMAIN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvImsaImsRegDomainQryCnf: WARNING: Not AT_CMD_IMSREGDOMAIN_QRY!");
        return VOS_ERR;
    }

    /* ��λ״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϷ���ֵ�Ƿ�Ϸ� */
    if (IMSA_AT_IMS_REG_DOMAIN_TYPE_BUTT <= (pstImsRegDomainCnf->enImsRegDomain))
    {
        ulResult = AT_ERROR;
    }
    else
    {
       gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       pstImsRegDomainCnf->enImsRegDomain);
        ulResult= AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaImsCtrlMsg
 ��������  : AT͸��IMSA��MAPCON���͵���Ϣ
 �������  : VOS_VOID * pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvImsaImsCtrlMsg(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_IMS_CTRL_MSG_STRU                              *pstImsCtrlMsgInd;
    AT_IMS_CTRL_MSG_RECEIVE_MODULE_ENUM_UINT8               enModule;
    VOS_UINT16                                              usLength = 0;
    VOS_UINT8                                               ucIndex;

    /* ��ʼ����Ϣ���� */
    enModule          = AT_IMS_CTRL_MSG_RECEIVE_MODULE_MAPCON;
    ucIndex           = 0;
    pstImsCtrlMsgInd  = (IMSA_AT_IMS_CTRL_MSG_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstImsCtrlMsgInd->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaImsCtrlMsg: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^IMSCTRLMSGU: %d,%d,\"",
                                       gaucAtCrLf,
                                       enModule,
                                       pstImsCtrlMsgInd->ulWifiMsgLen);

    usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_UINT8 *)pgucAtSndCodeAddr + usLength,
                                                    pstImsCtrlMsgInd->aucWifiMsg,
                                                    (VOS_UINT16)pstImsCtrlMsgInd->ulWifiMsgLen);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "\"%s",
                                       gaucAtCrLf);

    /* ����At_SendResultData���������� */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_RcvImsaCallEncryptSetCnf
 ��������  : ^CALLENCRYPT��������ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��04��
    ��    ��   : f00179208
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaCallEncryptSetCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_CALL_ENCRYPT_SET_CNF_STRU  *pstCallEncryptCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex           = 0;
    pstCallEncryptCnf = (IMSA_AT_CALL_ENCRYPT_SET_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCallEncryptCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCallEncryptSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaCallEncryptSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CALLENCRYPT_SET */
    if (AT_CMD_CALLENCRYPT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvImsaCallEncryptSetCnf: WARNING:Not AT_CMD_CALLENCRYPT_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if (VOS_OK == pstCallEncryptCnf->ulResult)
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvImsaRoamImsServiceQryCnf
 ��������  : ^ROAMIMSSERVICE��ѯ����ظ�������
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��15��
    ��    ��   : w00316404
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaRoamImsServiceQryCnf(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_ROAMING_IMS_QRY_CNF_STRU   *pstRoamImsServiceCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ��ʼ����Ϣ���� */
    ucIndex              = 0;
    usLength             = 0;
    pstRoamImsServiceCnf = (IMSA_AT_ROAMING_IMS_QRY_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstRoamImsServiceCnf->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaRoamImsServiceQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvImsaRoamImsServiceQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_ROAM_IMS_QRY */
    if ( AT_CMD_ROAM_IMS_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvImsaRoamImsServiceQryCnf: WARNING:Not AT_CMD_ROAM_IMS_QRY!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( VOS_OK == pstRoamImsServiceCnf->ulResult )
    {

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           ((pstRoamImsServiceCnf->enRoamingImsSupportFlag == AT_IMSA_ROAMING_IMS_SUPPORT) ? 1 : 0));

        ulResult  = AT_OK;
    }
    else
    {
        ulResult  = AT_ERROR;
    }

    gstAtSendData.usBufLen  = usLength;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_RcvImsaRatHandoverInd
 ��������  : imsa�����ϱ�ID_IMSA_AT_IMS_RAT_HANDOVER_IND��Ϣ����
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��04��22��
    ��    ��   : m00217266
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvImsaRatHandoverInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_IMS_RAT_HANDOVER_IND_STRU  *pstHandoverInd;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstHandoverInd  = (IMSA_AT_IMS_RAT_HANDOVER_IND_STRU*)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstHandoverInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvImsaRatHandoverInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s^IMSRATHO: %d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   pstHandoverInd->enHoStatus,
                                                   pstHandoverInd->enSrcRat,
                                                   pstHandoverInd->enDstRat,
                                                   pstHandoverInd->enCause,
                                                   gaucAtCrLf);
    /* ����At_SendResultData���������� */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvSrvStatusUpdateInd
 ��������  : imsa�����ϱ�ID_IMSA_AT_IMS_SRV_STATUS_UPDATE_IND��Ϣ����
 �������  : *pMsg        �ظ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��04��22��
    ��    ��   : m00217266
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvSrvStatusUpdateInd(VOS_VOID * pMsg)
{
    /* ����ֲ����� */
    IMSA_AT_IMS_SRV_STATUS_UPDATE_IND_STRU *pstSrvUpdateInd;
    VOS_UINT8                               ucIndex;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstSrvUpdateInd     = (IMSA_AT_IMS_SRV_STATUS_UPDATE_IND_STRU*)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstSrvUpdateInd->usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvSrvStatusUpdateInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen= (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s^IMSSRVSTATUS: %d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   pstSrvUpdateInd->enSmsSrvStatus,
                                                   pstSrvUpdateInd->enSmsSrvRat,
                                                   pstSrvUpdateInd->enVoIpSrvStatus,
                                                   pstSrvUpdateInd->enVoIpSrvRat,
                                                   pstSrvUpdateInd->enVtSrvStatus,
                                                   pstSrvUpdateInd->enVtSrvRat,
                                                   pstSrvUpdateInd->enVsSrvStatus,
                                                   pstSrvUpdateInd->enVsSrvRat,
                                                   gaucAtCrLf);
    /* ����At_SendResultData���������� */
    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}



