

#include "AtCheckFunc.h"
#include "ATCmdProc.h"
#include "AtCmdMsgProc.h"
#include "AtInputProc.h"

#include "at_common.h"

#include "AcpuReset.h"

#include "AtInternalMsg.h"

#include "AtParseCore.h"

#include "AtDataProc.h"



/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSECORE_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/


/* �����ͷ��� */
HI_LIST_S g_stCmdTblList = {0};

/* �������̲��� */
AT_PARSECMD_STRU g_stATParseCmd;

/* �����б� */
VOS_UINT8 gucAtParaIndex = 0;

AT_PARSE_PARA_TYPE_STRU gastAtParaList[AT_MAX_PARA_NUMBER];

/* ÿ���ͻ��˵Ľ�����Ϣ */
AT_PARSE_CONTEXT_STRU g_stParseContext[AT_MAX_CLIENT_NUM];

/* ����SMS��������ͨ�����ʽ��һ�£���������SMS�������Ӧ������ */
/* �����������֧�ֶ�ͨ����������������������
   ��g_stCmdElement=> g_stCmdElement[AT_MAX_CLIENT_NUM] */
AT_PAR_CMD_ELEMENT_STRU g_stCmdElement[AT_MAX_CLIENT_NUM];



/*****************************************************************************
 �� �� ��  : At_ParseInit
 ��������  : ��������ʼ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��21��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : �������warning

*****************************************************************************/
VOS_VOID At_ParseInit(VOS_VOID)
{
    VOS_UINT32 i = 0;

    PS_MEM_SET(&g_stATParseCmd,   0, sizeof(g_stATParseCmd));
    PS_MEM_SET(g_stParseContext,  0, sizeof(g_stParseContext));
    PS_MEM_SET(g_stCmdElement,    0, sizeof(g_stCmdElement));

    /*lint -e717*/

    HI_INIT_LIST_HEAD(&g_stCmdTblList);

    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        HI_INIT_LIST_HEAD(&(g_stParseContext[i].stCombineCmdInfo.stCombineCmdList));
    }

    /*lint -e717*/

    return;
}

/******************************************************************************
 ��������: AT_RegisterCmdTable
 ��������: �����ע��

 ����˵��:
   pstCmdTblEntry [in] �����ָ��
   usCmdNum [in] ��������������

 ��    ��: �޾�ǿ/00064416 [2011-09-30]
******************************************************************************/
VOS_UINT32 AT_RegisterCmdTable(const AT_PAR_CMD_ELEMENT_STRU* pstCmdTblEntry, VOS_UINT16 usCmdNum)
{
    HI_LIST_S* pCmdTblHeader = NULL;
    AT_PAR_CMDTBL_LIST_STRU* pstCmdTblNode = NULL;

    /* �����Ϊ�գ������������Ϊ0 */
    if((NULL == pstCmdTblEntry) || (0 == usCmdNum))
    {
        return ERR_MSP_FAILURE;
    }

    pCmdTblHeader = &g_stCmdTblList;

    /* ���������errcodetbl��ӵ������� */
    pstCmdTblNode = (AT_PAR_CMDTBL_LIST_STRU *)AT_MALLOC(sizeof(AT_PAR_CMDTBL_LIST_STRU));
    if(NULL == pstCmdTblNode)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstCmdTblNode->usCmdNum = usCmdNum;

    pstCmdTblNode->pstCmdElement = (AT_PAR_CMD_ELEMENT_STRU*)pstCmdTblEntry;

    msp_list_add_tail((&pstCmdTblNode->stCmdTblList), pCmdTblHeader);

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : AT_ClacCmdProc
 ��������  : +CLAC ������Ϣ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_ClacCmdProc(VOS_VOID)
{
    VOS_UINT16 i = 0;
    HI_LIST_S* me = NULL;
    AT_PAR_CMDTBL_LIST_STRU* pstCmdTblNode = NULL;
    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement = NULL;

    msp_list_for_each(me, &g_stCmdTblList)
    {
        pstCmdTblNode = msp_list_entry(me, AT_PAR_CMDTBL_LIST_STRU , stCmdTblList);

        pstCmdElement = pstCmdTblNode->pstCmdElement;

        if(NULL == pstCmdElement)
        {
            continue;
        }

        for(i = 0; i < pstCmdTblNode->usCmdNum; i++)
        {
            /* �ж��Ƿ���Ҫ��ʾ */
            if(0 == (pstCmdElement[i].ulChkFlag & CMD_TBL_CLAC_IS_INVISIBLE))
            {
                gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                  "%s%c%c", pstCmdElement[i].pszCmdName, ucAtS3, ucAtS4);
            }
        }
    }

    return ;
}


/*****************************************************************************
 �� �� ��  : AT_BlockCmdCheck
 ��������  : ����Ƿ�������������
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_BlockCmdCheck(VOS_VOID)
{
    VOS_UINT8 i = 0;
    VOS_UINT8 ucBlockid = AT_MAX_CLIENT_NUM;

    /* ��ѯ����ͨ��״̬ */
    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        /* ���ĳͨ�����ڷ�ready̬����ֱ�ӷ��أ������� */
        if(AT_FW_CLIENT_STATUS_READY != g_stParseContext[i].ucClientStatus)
        {
            return AT_MAX_CLIENT_NUM;
        }

        if((0 != g_stParseContext[i].usBlockCmdLen) && (NULL != g_stParseContext[i].pBlockCmd))
        {
            ucBlockid = i;
        }
    }

    return ucBlockid;
}


/*****************************************************************************
 �� �� ��  : AT_ClearBlockCmdInfo
 ��������  : ��ձ�������������Ϣ
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_ClearBlockCmdInfo(VOS_UINT8 ucIndex)
{
    if(NULL != g_stParseContext[ucIndex].pBlockCmd)
    {
        AT_FREE(g_stParseContext[ucIndex].pBlockCmd);
        g_stParseContext[ucIndex].pBlockCmd = NULL;
    }

    g_stParseContext[ucIndex].usBlockCmdLen = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : AT_CheckProcBlockCmd
 ��������  : ���ʹ�����������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_CheckProcBlockCmd(VOS_VOID)
{
    VOS_UINT8 ucIndex;
    VOS_UINT32 ulRet;


    /* �ж��Ƿ��л�������� */
    ucIndex = AT_BlockCmdCheck();
    if(ucIndex < AT_MAX_CLIENT_NUM)
    {
        /* ������Ϣ���������� */
        ulRet = At_SendCmdMsg(ucIndex, &ucIndex, sizeof(ucIndex), AT_COMBIN_BLOCK_MSG);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            /* �ɶ�ʱ����ʱȥ���� */
        }
    }

    return ;
}


/*****************************************************************************
 �� �� ��  : AT_ParseCmdOver
 ��������  : ��ͨ���ĵ�ǰ�����������������ʱֻ��ʾһ���������ϣ�
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_ParseCmdOver(VOS_UINT8 ucIndex)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;

    if(ucIndex >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    pstCombineCmdInfo = &pClientContext->stCombineCmdInfo;

    if(pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum)
    {
        pstCombineCmdInfo->usProcNum++;
    }
    else    /* ���ⱻ����� */
    {
        pstCombineCmdInfo->usProcNum = pstCombineCmdInfo->usTotalNum;
    }

    /* �ж���������Ƿ������ */
    if((pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum))
    {
        /* ������Ϣ������һ������ */
        ulRet = At_SendCmdMsg(ucIndex, &ucIndex, sizeof(ucIndex), AT_COMBIN_BLOCK_MSG);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            /* ��Ϣ����ʧ�ָܻ�������״̬ */
            pClientContext->ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        }

        return ;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : AT_BlockCmdTimeOutProc
 ��������  : �������ʱ������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_BlockCmdTimeOutProc(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = 0;

    At_FormatResultData(ucIndex, AT_ERROR);

    AT_ClearBlockCmdInfo(ucIndex);

    return ;
}


/*****************************************************************************
 �� �� ��  : AT_PendClientProc
 ��������  : PEND�ͻ��˴���
 �������  : ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��18��
    ��    ��   : l00171473
    �޸�����   : V7R1C50_At_Abort

  3.��    ��   : 2013��10��19��
    ��    ��   : w00167002
    �޸�����   : NETSCAN:֧�ֶ�ͨ��AT���
*****************************************************************************/
VOS_VOID AT_PendClientProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    if ((4 == usLen)
        && ('S' == At_UpChar(pData[0])) && ('T' == At_UpChar(pData[1]))
        && ('O' == At_UpChar(pData[2])) && ('P' == At_UpChar(pData[3])))
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_ResetCombinParseInfo(ucIndex);
    }
    else if(AT_CMD_A_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        if(('A' != At_UpChar(pData[0])) || ('T' != At_UpChar(pData[1]))
            || ('H' != At_UpChar(pData[2])))
        {
        }
        else
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_ResetCombinParseInfo(ucIndex);
        }
    }

    else if ( VOS_TRUE == AT_IsAbortCmdStr(ucIndex, pData, usLen) )
    {
        /* AT��ϵ�ǰPEND״̬�Ĵ��� */
        AT_AbortCmdProc(ucIndex);
    }

    else
    {
    }

    return ;
}


/*****************************************************************************
 �� �� ��  : AT_HoldBlockCmd
 ��������  : �������������ַ���
 �������  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��11��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_HoldBlockCmd(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32 ulTimerName = 0;
    VOS_UINT32 ulTempIndex = 0;
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    pstClientContext = &(g_stParseContext[ucIndex]);

    /* ֻ֧�ֻ���һ�����ݣ������µ�AT�����ַ����򸲸Ǳ�ͨ��֮ǰ�����������Ϣ */
    if(NULL != pstClientContext->pBlockCmd)
    {
        AT_FREE(pstClientContext->pBlockCmd);
    }

    pstClientContext->pBlockCmd = (VOS_UINT8*)AT_MALLOC(usLen);
    if(NULL == pstClientContext->pBlockCmd)
    {
        pstClientContext->usBlockCmdLen = 0;
        return ;
    }

    PS_MEM_CPY(pstClientContext->pBlockCmd, pData, usLen);
    pstClientContext->usBlockCmdLen = usLen;

    ulTempIndex  = (VOS_UINT32)ucIndex;
    ulTimerName  = AT_HOLD_CMD_TIMER;
    ulTimerName |= AT_INTERNAL_PROCESS_TYPE;
    ulTimerName |= (ulTempIndex<<12);

    /* ������ʱ�� */
    VOS_StopRelTimer(&pstClientContext->hTimer);

    AT_StartRelTimer(&pstClientContext->hTimer, AT_HOLD_CMD_TIMER_LEN, ulTimerName, 0, VOS_RELTIMER_NOLOOP);

    return ;
}


/*****************************************************************************
 �� �� ��  : AT_ParseCmdIsComb
 ��������  : �ж��Ƿ���ͨ���������û�д����������ͨ�����������û�д����
             ��������������������ͨ���������������
 �������  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : L47619
    �޸�����   : �޸�ATͨ�����������߼���������������������жϣ����������߼��ж�

*****************************************************************************/
VOS_UINT32 AT_ParseCmdIsComb(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    pstClientContext = &(g_stParseContext[ucIndex]);

    /* ��ʾ��ͨ��������������ڴ��� */
    if(pstClientContext->stCombineCmdInfo.usProcNum < pstClientContext->stCombineCmdInfo.usTotalNum)
    {
        CmdStringFormat(ucIndex, pData, &usLen);

        AT_PendClientProc(ucIndex, pData, usLen);

        return ERR_MSP_FAILURE;
    }

    return ERR_MSP_SUCCESS;

}


/*****************************************************************************
 �� �� ��  : AT_ParseCmdIsPend
 ��������  : �ж��Ƿ������ڴ����ͨ�����еĻ������򻺴�
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : ERR_MSP_FAILURE : ��ͨ����������״̬������Ҫ��������
             ERR_MSP_SUCCESS : ������ͨ�����������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��02��20��
    ��    ��   : f00179208
    �޸�����   : ����AT����RIL��Ӧ��HSIC ATͨ���Ĳ���ִ��
  3.��    ��   : 2012��06��19��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:DTS2012061505515��GCF����31.9.1.1 ��ΪSTOP����ʧЧʧ��
*****************************************************************************/
VOS_UINT32 AT_ParseCmdIsPend(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32 i = 0;
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        pstClientContext = &(g_stParseContext[i]);

        if (i == ucIndex)
        {
            /* ��ͨ������PEND״̬ʱ��Ҫ�ж��Ƿ���STOP��ATH */
            if (AT_FW_CLIENT_STATUS_PEND == pstClientContext->ucClientStatus)
            {
                CmdStringFormat(ucIndex, pData, &usLen);

                AT_PendClientProc(ucIndex, pData, usLen);
                return ERR_MSP_FAILURE;
            }
        }
        /* ����ͨ������PEND״̬�����״̬ */
        else if ((AT_FW_CLIENT_STATUS_PEND == pstClientContext->ucClientStatus)
              || (AT_SMS_MODE == pstClientContext->ucMode))
        {
            /* Added by L60609 for MUX��2012-08-03,  Begin */
            /* �жϱ�ͨ���Լ���������ͨ���Ƿ���Բ��� */
            if (VOS_TRUE == AT_IsConcurrentPorts(ucIndex, (VOS_UINT8)i))
            {
                /* ����ǣ����������ͨ�� */
                continue;
            }
            /* Added by L60609 for MUX��2012-08-03,  End */
            else
            {
                /* ������ǣ��򻺴������ */
                AT_HoldBlockCmd(ucIndex, pData, usLen);
                return ERR_MSP_FAILURE;
            }
        }
        else
        {
        }
    }

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : AT_DiscardInvalidCharForSms
 ��������  : +CMGS,+CMGW,+CMGC����ļ������⴦��
 �������  : TAF_UINT8* pData
             TAF_UINT16 *pusLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_DiscardInvalidCharForSms(TAF_UINT8* pData, TAF_UINT16 *pusLen)
{
    TAF_CHAR   aucCMGSCmd[] = "AT+CMGS=";
    TAF_CHAR   aucCMGWCmd[] = "AT+CMGW=";
    TAF_CHAR   aucCMGCCmd[] = "AT+CMGC=";
    TAF_CHAR   aucTmpCmd[9];
    VOS_INT    iCMGSResult;
    VOS_INT    iCMGWResult;
    VOS_INT    iCMGCResult;

    if (*pusLen < VOS_StrLen(aucCMGSCmd))
    {
        return;
    }

    PS_MEM_CPY(aucTmpCmd, pData, sizeof(aucTmpCmd) - 1);
    At_UpString((TAF_UINT8 *)aucTmpCmd, sizeof(aucTmpCmd) - 1);
    aucTmpCmd[8] = '\0';

    iCMGSResult = VOS_StrCmp(aucCMGSCmd, aucTmpCmd);
    iCMGWResult = VOS_StrCmp(aucCMGWCmd, aucTmpCmd);
    iCMGCResult = VOS_StrCmp(aucCMGCCmd, aucTmpCmd);
    if ((0 != iCMGSResult) && (0 != iCMGWResult)&&(0 != iCMGCResult))
    {
        return;
    }

    /*  MACϵͳ�ϵ�MP��̨����:AT+CMGS=**<CR><^z><Z>(��AT+CMGW=**<CR><^z><Z>)
       Ϊ�˹�ܸ����⣬��Ҫ�ڽ��յ�������ʽ��������
       ��Ҫ����������Ч�ַ�<^z><Z>ɾȥ  */
    /*lint -e960 Note -- Violates MISRA 2004 Required Rule 4.1, Prohibited escape sequence used (hexadecimal)*/
    if ((ucAtS3 == pData[*pusLen - 3]) && ('\x1a' == pData[*pusLen - 2])
        && (('z' == pData[*pusLen - 1]) || ('Z' == pData[*pusLen - 1])))
    /*lint +e960*/
    {
        /* ɾȥ��β��<^z><Z>�ַ� */
        *pusLen -= 2;
    }
    /* MACϵͳSFR��̨����: AT+CMGS=<LENGTH><CR><LF><CR>*/
    else if ((ucAtS3 == pData[*pusLen - 3])
          && (ucAtS4 == pData[*pusLen - 2])
          && (ucAtS3 == pData[*pusLen - 1]))
    {
        /* ɾȥ��β��<LF><CR>�ַ� */
        *pusLen -= 2;
    }
    /* �ж�pData�����Ľ�β�Ƿ�Ϊ<CR><LF>��ʽ */
    else if ((ucAtS3 == pData[*pusLen - 2]) && (ucAtS4 == pData[*pusLen - 1]))
    {
        /* ɾȥ��β��<LF>�ַ� */
        *pusLen -= 1;
    }
    else
    {
    }

    return;
}



/*****************************************************************************
 �� �� ��  : AT_ResetParseVariable
 ��������  : ���³�ʼ��������ȫ�ֱ���
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��28��
    ��    ��   : o00132663
    �޸�����   : AT�ں���Ŀ��AT�����б�δ��ʼ�����½���ʧ��
*****************************************************************************/
VOS_VOID AT_ResetParseVariable(VOS_VOID)
{
    PS_MEM_SET(&g_stATParseCmd, 0 , sizeof(AT_PARSECMD_STRU));

    PS_MEM_SET(gastAtParaList, 0 , sizeof(gastAtParaList));

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_BUTT;
    g_stATParseCmd.ucCmdFmtType = AT_CMD_TYPE_BUTT;

    gucAtParaIndex = 0;
    return;
}


/*****************************************************************************
 �� �� ��  : AT_ParseCmdType
 ��������  : �����������ͽ��������ַ���
 �������  :  VOS_UINT8 * pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_ParseCmdType( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usDataTmpLen = usLen - 2;
    VOS_UINT8* pDataTmp = pData + 2;
    VOS_UINT32 ulResult = 0;

    /* ���õĵط���֤pData��Ϊ�� */

    if(usLen < 2)
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS == At_CheckCharA(*pData))   /* �����'A'/'a' */
    {
        if(AT_SUCCESS == At_CheckCharT(*(pData+1)))   /* �����'T'/'t' */
        {
            if(2 == usLen)
            {
                return AT_OK;
            }

            if(3 == usLen)
            {
                if(AT_SUCCESS == At_CheckSemicolon(pData[2]))
                {
                    return AT_OK;
                }
            }

            AT_ResetParseVariable();    /* ���ý��������õ�ȫ�ֱ��� */

            pDataTmp = pData + 2;
            usDataTmpLen = usLen - 2;

            /* ��D�����Ҫȥ�������β��';' */
            if(AT_SUCCESS != (At_CheckCharD(*pDataTmp)) && (';' == *(pDataTmp+usDataTmpLen-1)))
            {
                usDataTmpLen--;
            }

            switch(*pDataTmp)      /* ���ݵ������ַ����зַ� */
            {
            case '^':   /* ��չ���� */
            case '+':   /* ��չ���� */
            case '$':   /* ��չ���� */
                return atParseExtendCmd(pDataTmp, usDataTmpLen);

            case 'd':
            case 'D':   /* D���� */

                return ParseDCmdPreProc(pDataTmp, usDataTmpLen);

            case 's':
            case 'S':   /* S���� */
                return atParseSCmd(pDataTmp, usDataTmpLen);

            default:    /*�������� */
                {
                    ulResult = atParseBasicCmd(pDataTmp, usDataTmpLen);

                    if(AT_FAILURE == ulResult)
                    {
                        ulResult = AT_ERROR;
                    }

                    return ulResult;
                }
            }
        }
    }

    return AT_ERROR;
}


/*****************************************************************************
 �� �� ��  : At_MatchSmsCmdName
 ��������  : ��SMS�������ƥ��������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��19��
    ��    ��   : l00171473
    �޸�����   : V7R1C50_At_Abort, ��Ӷ�������ABORT֧��
  3.��    ��   : 2012��11��19��
    ��    ��   : f62575
    �޸�����   : DTS2012112010227, �����������֧�ֶ�ͨ���������������������⣻
  4.��    ��   : 2013��3��5��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 At_MatchSmsCmdName(VOS_UINT8 ucIndex, VOS_CHAR *pszCmdName)
{
    VOS_UINT32                          i = 0;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    for (i = 0; i < gusAtSmsCmdNum; i++)
    {
        if (VOS_NULL_PTR != (TAF_CHAR*)gastAtSmsCmdTab[i].pszCmdName)
        {
            if (ERR_MSP_SUCCESS == AT_STRCMP(pszCmdName, (TAF_CHAR*)gastAtSmsCmdTab[i].pszCmdName))
            {
                if ( AT_CMGF_MSG_FORMAT_TEXT == pstSmsCtx->enCmgfMsgFormat)
                {
                    g_stCmdElement[ucIndex].pszParam = gastAtSmsCmdTab[i].ParaText;
                }
                else
                {
                    g_stCmdElement[ucIndex].pszParam = gastAtSmsCmdTab[i].ParaPDU;
                }

                g_stCmdElement[ucIndex].ulCmdIndex      = gastAtSmsCmdTab[i].ulCmdIndex;
                g_stCmdElement[ucIndex].pfnSetProc      = gastAtSmsCmdTab[i].pfnSetProc;
                g_stCmdElement[ucIndex].ulSetTimeOut    = gastAtSmsCmdTab[i].ulSetTimeOut;
                g_stCmdElement[ucIndex].pfnQryProc      = NULL;
                g_stCmdElement[ucIndex].ulQryTimeOut    = 0;
                g_stCmdElement[ucIndex].pfnTestProc     = gastAtSmsCmdTab[i].pfnTestProc;
                g_stCmdElement[ucIndex].ulTestTimeOut   = gastAtSmsCmdTab[i].ulTestTimeOut;

                g_stCmdElement[ucIndex].pfnAbortProc    = gastAtSmsCmdTab[i].pfnAbortProc;
                g_stCmdElement[ucIndex].ulAbortTimeOut  = gastAtSmsCmdTab[i].ulAbortTimeOut;

                g_stCmdElement[ucIndex].ulParamErrCode  = gastAtSmsCmdTab[i].ulParamErrCode;
                g_stCmdElement[ucIndex].ulChkFlag       = gastAtSmsCmdTab[i].ulChkFlag;
                g_stCmdElement[ucIndex].pszCmdName      = gastAtSmsCmdTab[i].pszCmdName;

                g_stParseContext[ucIndex].pstCmdElement = &g_stCmdElement[ucIndex];

                return AT_SUCCESS;
            }
        }
    }

    g_stParseContext[ucIndex].pstCmdElement = NULL;

    return AT_FAILURE;
}


/******************************************************************************
 ��������: atMatchCmdName
 ��������: ƥ����������

 ����˵��:
   CmdType [in] ��������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 atMatchCmdName (VOS_UINT8 ucClientId, VOS_UINT32 CmdType)
{
    VOS_UINT32 i = 0;
    /* VOS_UINT32 ulRet = ERR_MSP_FAILURE; */
    HI_LIST_S* me = NULL;
    HI_LIST_S* pCmdTblList = NULL;
    AT_PAR_CMDTBL_LIST_STRU* pstCmdNode = NULL;
    VOS_CHAR *pszCmdName = NULL;

    /* ���õĵط���֤�����ָ�벻Ϊ�� */

    pCmdTblList = &(g_stCmdTblList);

    /* ȫ����ʽ��Ϊ��д�ַ� */
    if(AT_FAILURE == At_UpString(g_stATParseCmd.stCmdName.aucCmdName,g_stATParseCmd.stCmdName.usCmdNameLen))
    {
        return AT_ERROR;
    }

    pszCmdName = (VOS_CHAR *)g_stATParseCmd.stCmdName.aucCmdName;

    if((AT_EXTEND_CMD_TYPE == CmdType) || (AT_BASIC_CMD_TYPE == CmdType))
    {
        /* ����������Ҫ���⴦�� */
        if(ERR_MSP_SUCCESS == At_MatchSmsCmdName(ucClientId, pszCmdName))
        {
            return ERR_MSP_SUCCESS;
        }

        msp_list_for_each(me, pCmdTblList)
        {
            pstCmdNode = msp_list_entry(me, AT_PAR_CMDTBL_LIST_STRU, stCmdTblList);

            for(i = 0; i < pstCmdNode->usCmdNum; i++)
            {
                if((NULL == pstCmdNode->pstCmdElement) || (NULL == pstCmdNode->pstCmdElement[i].pszCmdName))
                {
                    continue;
                }

                if(ERR_MSP_SUCCESS == AT_STRCMP((VOS_CHAR *)pszCmdName, (VOS_CHAR *)pstCmdNode->pstCmdElement[i].pszCmdName))
                {
                    g_stParseContext[ucClientId].pstCmdElement = &(pstCmdNode->pstCmdElement[i]);

                    return ERR_MSP_SUCCESS;
                }
            }
        }
    }

    return AT_CMD_NOT_SUPPORT;
}


/******************************************************************************
 ��������: ParseParam
 ��������: ��������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ParseParam(AT_PAR_CMD_ELEMENT_STRU* pstCmdElement)
{
    VOS_UINT32 ulParaLen = 0;

    if(AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType)
    {
        if((NULL != pstCmdElement) && (NULL != pstCmdElement->pszParam))
        {
            ulParaLen = AT_STRLEN((VOS_CHAR *)pstCmdElement->pszParam);  /* ��ȡ�����ű����� */
            if(AT_SUCCESS != atParsePara((VOS_UINT8*)pstCmdElement->pszParam,(VOS_UINT16)ulParaLen))  /* ����ƥ�� */
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }
    }

    return ERR_MSP_SUCCESS;
}


AT_RRETURN_CODE_ENUM_UINT32 fwCmdTestProc(VOS_UINT8 ucIndex, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    /* ���õĵط���ָ֤�벻Ϊ�� */

    if(NULL != pstCmdElement->pfnTestProc)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)pstCmdElement->pfnTestProc(ucIndex);

        if(AT_WAIT_ASYNC_RETURN == ulResult)
        {
            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

            /* ����ʱ�� */
            if(AT_SUCCESS != At_StartTimer(pstCmdElement->ulTestTimeOut, ucIndex))
            {
                return AT_ERROR;
            }

            At_SetAtCmdAbortTickInfo(ucIndex, VOS_GetTick());
        }

        return ulResult;
    }
    else if(NULL != pstCmdElement->pszParam)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
           (TAF_CHAR*)pgucAtSndCodeAddr, (TAF_CHAR*)pgucAtSndCodeAddr,
           "%s: %s", pstCmdElement->pszCmdName, pstCmdElement->pszParam);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}


/******************************************************************************
 ��������: atCmdDispatch
 ��������: ����ַ�

 ����˵��:
   ucClientId [in] client id

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
AT_RRETURN_CODE_ENUM_UINT32 atCmdDispatch (VOS_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    PFN_AT_FW_CMD_PROC pfnCmdProc = NULL;
    VOS_UINT32 ulTimerLen = 0;
    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement = g_stParseContext[ucIndex].pstCmdElement;

    switch (g_stATParseCmd.ucCmdOptType)
    {
    case AT_CMD_OPT_SET_PARA_CMD:
    case AT_CMD_OPT_SET_CMD_NO_PARA:
        pfnCmdProc = pstCmdElement->pfnSetProc;          /* �����޲������� */
        ulTimerLen = pstCmdElement->ulSetTimeOut;
        break;

    case AT_CMD_OPT_READ_CMD:
        pfnCmdProc = pstCmdElement->pfnQryProc;          /* ��ѯ���� */
        ulTimerLen = pstCmdElement->ulQryTimeOut;
        break;

    case AT_CMD_OPT_TEST_CMD:
        return fwCmdTestProc(ucIndex, pstCmdElement);         /* ���Բ��� */

    default:
        return AT_ERROR;                        /* ����������򷵻ش��� */
    }

    if(NULL == pfnCmdProc)
    {
        return AT_ERROR;
    }

    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)pfnCmdProc(ucIndex);

    if(AT_WAIT_ASYNC_RETURN == ulResult)
    {
        /* ����ʱ�� */
        if(AT_SUCCESS != At_StartTimer(ulTimerLen, ucIndex))
        {
            return AT_ERROR;
        }

        At_SetAtCmdAbortTickInfo(ucIndex, VOS_GetTick());

        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    }

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : LimitedCmdProc
 ��������  : �������޲�ѯ�ʹ���
 �������  : VOS_UINT8 ucClientId
             VOS_UINT8 *pData
             VOS_UINT16 usLen
             AT_PAR_CMD_ELEMENT_STRU* pstCmdElement
 �������  : ��
 �� �� ֵ  : AT_OK      : ��ʾ�������������㣬��Ҫ��������
             AT_ERROR   : ��ʾ�����������㣬��Ҫ����ERROR
             AT_SUCCESS : ��ʾDOCK����ת����E5ͨ����������Ҫ����Ӧ��
             ����       : �ض�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��10��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  3.��    ��   : 2012��04��07��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012032702424,�򿪶�DOCK�����֧��
*****************************************************************************/
VOS_UINT32 LimitedCmdProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement)
{
    VOS_BOOL bE5CheckRight = VOS_TRUE;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;

    if(NULL == pstCmdElement)
    {
        return AT_ERROR;
    }


     /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ���E5���뱣�����ޣ�����ò�ѯE5���������ӿڣ����޵Ļ�����AT_ERROR�����򷵻�AT_OK */
    if(0 == (pstCmdElement->ulChkFlag & CMD_TBL_E5_IS_LOCKED))
    {
        /* ��ATͨ�� ��WIFIͨ��, ���������뱣�� */
        if ( (AT_USBCOM_USER != gastAtClientTab[ucClientId].UserType)
          && (AT_SOCK_USER != gastAtClientTab[ucClientId].UserType)
          && (AT_APP_SOCK_USER != gastAtClientTab[ucClientId].UserType))
        {
            /* ��������PIN�뱣���ļ�� */
        }
        else
        {
            bE5CheckRight = AT_E5CheckRight(ucClientId, pData, usLen);
            if(VOS_TRUE == bE5CheckRight)
            {
                /* E5�ѽ�������������PIN�뱣���ļ�� */
            }
            else
            {
                return AT_SUCCESS;  /* AT_E5CheckRight �ڲ��ѷ����ϱ���� */
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* �����E5 DOCK�����ֱ�ӵ���DOCK����ת���ӿڣ�����AT_SUCCESS */
    if(pstCmdElement->ulChkFlag & CMD_TBL_IS_E5_DOCK)
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucClientId].UserType)
        {
            ulResult = (AT_RRETURN_CODE_ENUM_UINT32)AT_DockHandleCmd(ucClientId, pData, usLen);
            if(AT_SUCCESS == ulResult)
            {
                return AT_SUCCESS;  /* ����������ת����E5ͨ������ͨ���������κν�� */
            }
            else
            {
                return AT_ERROR;    /* ����ʧ�ܣ�����ERROR */
            }
        }
    }

    /* ���PIN�뱣�����ޣ�����ò�ѯPIN�����������ӿڣ����޵Ļ�����AT_ERROR�����򷵻�AT_OK */
    if(0 == (pstCmdElement->ulChkFlag & CMD_TBL_PIN_IS_LOCKED))
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CheckUsimStatus((VOS_UINT8*)pstCmdElement->pszCmdName, ucClientId);
        if(AT_SUCCESS == ulResult)
        {
            /* PIN���ѽ��������������ļ�鴦�� */
        }
        else
        {
            return ulResult;    /* ���ؾ���������ԭ��ֵ */
        }
    }


    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : CmdParseProc
 ��������  : �����������
 �������  : VOS_UINT8 ucClientId
              VOS_UINT8 *pDataIn
             VOS_UINT16 usLenIn
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CmdParseProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_FAILURE;
    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement = NULL;

    /* �ú������ô��ɱ�֤ucClientId�ĺϷ��ԣ�pDataIn��Ϊ�� */


    /* ƥ���������� */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)atMatchCmdName(ucClientId, g_stATParseCmd.ucCmdFmtType);
    if(ERR_MSP_SUCCESS != ulResult)
    {
        /* HAL_DIAG_SDM_FUN(EN_SDM_AT_FW_PARSE_FAILURE, 6, 0, 0); */
        return ulResult;
    }

    pstCmdElement = g_stParseContext[ucClientId].pstCmdElement;

    if(NULL == pstCmdElement)
    {
        return AT_ERROR;
    }

    /* ���������жϺʹ���ӿڣ�����ʧ�ܱ�ʾ��������������ֱ�ӷ��ش����� */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)LimitedCmdProc(ucClientId, pData, usLen, pstCmdElement);
    if(AT_OK != ulResult)
    {
        return ulResult;
    }

    /* ƥ��������� */
    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)ParseParam(pstCmdElement);

    if(ERR_MSP_SUCCESS != ulResult)
    {
        /* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
        if(AT_CMD_SD == pstCmdElement->ulCmdIndex)
        {
            return AT_SDParamErrCode();
        }
       /* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

        /* HAL_DIAG_SDM_FUN(EN_SDM_AT_FW_PARSE_FAILURE, 7, 0, 0); */
        if(AT_RRETURN_CODE_BUTT == pstCmdElement->ulParamErrCode)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            return (AT_RRETURN_CODE_ENUM_UINT32)(pstCmdElement->ulParamErrCode);
        }
    }


    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)atCmdDispatch(ucClientId);

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : RepeatCmdProc
 ��������  : A/����Ĵ���
 �������  : VOS_UINT8 ucClientId
             AT_FW_CLIENT_CONTEXT_STRU* pstClientContext
             AT_FW_CLIENT_CMD_CTRL_STRU* pstCmdfmtCtrl
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RepeatCmdProc(AT_PARSE_CONTEXT_STRU* pstClientContext)
{
    VOS_UINT8* pData = pstClientContext->aucDataBuff;
    VOS_UINT32 ulLen = pstClientContext->usDataLen;

    if(ucAtS4 == *pData)
    {
        pData++;
        ulLen--;
    }

    /* ����Ƿ���"A/" */
    if(3 == ulLen)
    {
        if(AT_SUCCESS == At_CheckCharA(*pData))
        {
            if(AT_SUCCESS == atCheckChar0x2f(*(pData+1)))
            {
                if(0 == pstClientContext->usCmdLineLen)
                {
                    pstClientContext->usDataLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pstClientContext->aucDataBuff,
                        (VOS_CHAR *)pstClientContext->aucDataBuff, "AT%c", ucAtS3);
                }
                else
                {
                   PS_MEM_CPY(pstClientContext->aucDataBuff, (VOS_UINT8*)pstClientContext->pucCmdLine,
                        pstClientContext->usCmdLineLen);

                   pstClientContext->usDataLen = pstClientContext->usCmdLineLen;
                }
            }
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : SaveRepeatCmd
 ��������  : ���浱ǰ�����ַ���
 �������  : pstClientContext : ������������
             pData            : AT�����ַ���
             usLen            : AT�����ַ�������
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID SaveRepeatCmd(AT_PARSE_CONTEXT_STRU* pstClientContext, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    /* ����A/����� */
    if(NULL != pstClientContext->pucCmdLine)
    {
        AT_FREE(pstClientContext->pucCmdLine);
    }

    pstClientContext->pucCmdLine = (VOS_UINT8 *)AT_MALLOC(usLen);
    if(NULL == pstClientContext->pucCmdLine)
    {
        return;
    }

    PS_MEM_CPY(pstClientContext->pucCmdLine, pData, usLen);
    pstClientContext->usCmdLineLen = usLen;

    return;
}


/******************************************************************************
 ��������: ScanDelChar
 ��������: ɨ���˸��

 ����˵��:
   pData [in/out] �ַ�������
   pLen [in/out] �ַ�������
   AtS5 [in] �˸��

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ScanDelChar( VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS5)
{
    VOS_UINT16 usChkLen  = 0;
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = pData;
    VOS_UINT8  *pRead    = pData;
    VOS_UINT16 usNum     = 0;    /* ��¼���ŵĸ��� */

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* ���������� */
    while ( usChkLen++ < *pLen )
    {
        if('"' == *pRead)
        {
            usNum++;
            *pWrite++ = *pRead;
            usLen++;
        }
        else if((AtS5 == *pRead) && (0 == (usNum%2)))       /*ɾ����һ�ַ�,�����ڵ�ɾ����������*/
        {
            if( usLen > 0 )
            {
                pWrite--;
                usLen--;
            }
        }
        else                        /*ѡ����Ч�ַ�*/
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pLen  =  usLen;
    return AT_SUCCESS;
}


/******************************************************************************
 ��������: ScanCtlChar
 ��������: ɨ����Ʒ�(ȥ���ַ�����С��0x20���ַ�)

 ����˵��:
   pData [in/out] �ַ�������
   pLen [in/out] �ַ�������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ScanCtlChar( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT8  *pWrite    = pData;
    VOS_UINT8  *pRead     = pData;
    VOS_UINT16 usChkLen   = 0;
    VOS_UINT16 usLen      = 0;
    VOS_UINT16 usNum      = 0;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* Added by c64416 for �����еĿ����ַ���ɾ��, DTS2011120903650 2011/12/21, begin */
    while( usChkLen++ < *pLen )
    {
        if( 0x20 <= *pRead )   /* ѡ����Ч�ַ� */
        {
            if('"' == *pRead)
            {
                usNum++;
            }
            *pWrite++ = *pRead;
            usLen++;
        }
        else
        {
            if(usNum%2)            /* ˫�����ڵ�С��0x20���ַ���ȥ�� */
            {
                *pWrite++ = *pRead;
                usLen++;
            }
        }
        pRead++;
    }
    /* Added by c64416 for �����еĿ����ַ���ɾ��, DTS2011120903650 2011/12/21, end */

    *pLen  =  usLen;
    return AT_SUCCESS;
}


/******************************************************************************
 ��������: ScanBlankChar
 ��������: ɨ��������ո��

 ����˵��:
   pData [in/out] �ַ�������
   pLen [in/out] �ַ�������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 ScanBlankChar( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    /* VOS_UINT8  *pCheck        = pData; */
    VOS_UINT8  *pWrite        = pData;
    VOS_UINT8  *pRead         = pData;
    VOS_UINT16 usChkLen       = 0;
    VOS_UINT16 usLen          = 0;
    VOS_UINT16 usColonBankCnt = 0;
    VOS_BOOL bIsColonBack  = FALSE;
    VOS_BOOL bIsEqual      = FALSE;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }


    /* ��� */
    while( usChkLen++ < *pLen )
    {
        if('=' == *pRead)
        {
            bIsEqual = TRUE;
        }

        if((' ' == *pRead) && (TRUE != bIsEqual))
        {
            /* �Ⱥ�ǰ�Ŀո�ȥ�� */
        }
        else    /* rim����ǰ��Ŀո� */
        {
            if(0x20 != *pRead && ',' != *pRead)
            {
                /* rim','��ո� */
                if(bIsColonBack)
                {
                    pWrite -= usColonBankCnt;
                    usLen  -= usColonBankCnt;
                    usColonBankCnt = 0;
                    bIsColonBack   = FALSE;
                }
                else
                {
                    usColonBankCnt = 0;
                }
            }
            else if(',' == *pRead)
            {
                /* rim','ǰ�ո� */
                pWrite -= usColonBankCnt;
                usLen  -= usColonBankCnt;
                usColonBankCnt = 0;
                bIsColonBack   = TRUE;
            }
            else
            {
                usColonBankCnt++;
            }

            *pWrite++ = *pRead;
            usLen++;
        }

        pRead++;
    }

    /* pWrite -= usColonBankCnt; */
    usLen  -= usColonBankCnt;

    *pLen  =  usLen;
    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : ScanBlankCharAfterEq
 ��������  : ɾ�������ŵȺź���Ŀո�,ScanBlankChar�����Ĳ�������
 �������  : IN OUT U8_T *pData
             IN OUT U16_T *pLen
 �������  : ��
 �� �� ֵ  : PRIVATE U32_T

 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : c64416
    �޸�����   : DTS2012102905864, �����ɺ���

*****************************************************************************/
PRIVATE VOS_UINT32 ScanBlankCharAfterEq(IN OUT VOS_UINT8 *pData,IN OUT VOS_UINT16 *pLen)
{
    VOS_UINT8  *pWrite        = pData;
    VOS_UINT8  *pRead         = pData;
    VOS_UINT16 usChkLen       = 0;
    VOS_UINT16 usLen          = 0;
    VOS_BOOL   bIsEqual      = FALSE;
    VOS_BOOL   bIsEqualNoSp  = FALSE;

    if(0 == *pLen)
    {
        return AT_FAILURE;
    }

    /* ��� */
    while( usChkLen++ < *pLen )
    {
        if('=' == *pRead)
        {
            bIsEqual = TRUE;
        }
        else
        {
            if((TRUE != bIsEqual) || (TRUE == bIsEqualNoSp))
            {
                /* �Ⱥ�ǰ���ַ�ȫ�����ƣ��Ⱥź�ķǿո��ַ�ȫ������ */
            }
            else
            {
                if(' ' == *pRead)
                {
                    pRead++;
                    continue;
                }
                else
                {
                    bIsEqualNoSp = TRUE;
                }
            }
        }

        *pWrite++ = *pRead;
        usLen++;

        pRead++;
    }

    *pLen  =  usLen;
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_FormatCmdStr
 Description    : ��ʽ�������ַ���
 Input          : pData --- �ַ���
                  pLen  --- ���ȵ�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    ��   : 2008��12��8��
    ��    ��   : o00132663
    �޸�����   : AT2D07342, AT�������Ӷ�˫�ֽ�ASCII�����֧�֡�
*****************************************************************************/
VOS_UINT32 FormatCmdStr (VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS3)
{
    VOS_UINT8  *pCheck    = pData;
    VOS_UINT32 ulChkS3Len = 0;
    VOS_UINT32 ulFlg      = 0;
    VOS_UINT16 usLen      = 0;

    /* �����н�����֮ǰ���ַ� */
    while ( ulChkS3Len++ < *pLen  )
    {
        if(AtS3 == *pCheck++)
        {
            ulFlg = 1;
            break;
        }
        else
        {
            /* *pCheck &= 0x7f; */   /* ����ÿ���ֽڵ����bitλ */
            usLen++;
        }
    }

    if( 1 !=  ulFlg )
    {
        return AT_FAILURE;
    }
    else
    {
        *pLen  =  usLen;
        return AT_SUCCESS;
    }
}

/*****************************************************************************
 �� �� ��  : AT_DiscardInvalidChar
 ��������  : ���˳�����"AT"֮ǰ������
 �������  : VOS_UINT8* pData
             VOS_UINT16 *pusLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��2��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��2��
   ��    ��   : �޾�ǿ/00064416
   �޸�����   : ����Ч���Ż�

*****************************************************************************/
VOS_UINT32  AT_DiscardInvalidChar(VOS_UINT8* pucData, VOS_UINT16 *pusLen)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usLen;

    /*DTS2011122400231 AT������󳤶������޸� : h00135900 start in 2011-12-24*/
    if ((*pusLen == 0) || (AT_CMD_MAX_LEN < *pusLen))
    {
        (VOS_VOID)vos_printf("AT_DiscardInvalidChar: usLen > AT_CMD_MAX_LEN or usLen = 0. usLen :%d", *pusLen);
        return ERR_MSP_FAILURE;
    }
    /*DTS2011122400231 AT������󳤶������޸� : h00135900 end in 2011-12-24*/
    for(i = 0; i < (*pusLen); i++)
    {
        if(AT_SUCCESS != At_CheckCharA(pucData[i]))
        {
            continue;
        }
        else if(AT_SUCCESS != At_CheckCharT(pucData[i+1]))
        {
            continue;
        }
        else
        {
            if (0 != i)
            {
                usLen = (*pusLen - i);
                PS_MEM_CPY(pucData, (pucData+i), usLen);
                *pusLen = usLen;
            }

            return ERR_MSP_SUCCESS;
        }
    }

    return ERR_MSP_FAILURE;
}


/******************************************************************************
 ��������: CmdStringFormat
 ��������: ��ʽ�������ַ���

 ����˵��:
   ucClientId [in] client id
   pData [in/out] �ַ�������
   pusLen [in/out] �ַ�������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
  2.��    ��   : 2012��10��31��
    ��    ��   : c64416
    �޸�����   : DTS2012102905864
******************************************************************************/
VOS_UINT32 CmdStringFormat(VOS_UINT8 ucClientId, VOS_UINT8 *pData,VOS_UINT16* pusLen)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;

    ulRet = FormatCmdStr(pData,pusLen, ucAtS3);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    /* ɨ���˸�� */
    ulRet = ScanDelChar(pData,pusLen, ucAtS5);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* ɨ����Ʒ� */
    ulRet = ScanCtlChar(pData,pusLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* ɨ��ո�� */
    ulRet = ScanBlankChar(pData,pusLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* ɨ������ŵȺź���Ŀո�� */
    ulRet = ScanBlankCharAfterEq(pData,pusLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    return ERR_MSP_SUCCESS;
}
/*****************************************************************************
 �� �� ��  : CheckAnyCharCmdName
 ��������  : ƥ�������ַ��������������
 �������  : VOS_UINT8 *pData
             VOS_UINT16* usLen
             VOS_UINT8 *plName
             VOS_UINT8 *pbName
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��31��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL CheckAnyCharCmdName(VOS_UINT8 *pData, VOS_UINT16* pusLen, VOS_UINT8 *plName, VOS_UINT8 *pbName)
{
    VOS_UINT16 i;
    VOS_UINT8  bFound   = 0;      /* check if found string ANY CHAR CMD */
    VOS_UINT8  ucOffset = 0;
    VOS_UINT8* pHeader = pData;   /* remember the header of the pointer */

    for(i=0; i < *pusLen; i++,pHeader++)
    {
        if (' ' == *pHeader)
        {
            continue;          /* skip space char */
        }
        else if ((plName[ucOffset] == *pHeader) || (pbName[ucOffset] == *pHeader))
        {
            ucOffset++;

            if ('?' == plName[ucOffset])
            {
                bFound = 1;    /* found string ANY CHAR CMD  */
            }
        }
        else
        {
            break;             /* not ANY CHAR CMD, go out */
        }
    }

    if (bFound)
    {
        if ((VOS_StrLen((VOS_CHAR *)plName) - 1) == ucOffset)
        {                          /* found string ANY CHAR CMD */
            *pusLen -= i;            /* remove string "AT^CPBW=" */
            PS_MEM_MOVE(pData, pData+i, *pusLen);
            return TRUE;
        }
    }

    return FALSE;
}

/*****************************************************************************
 �� �� ��  : AnyCharCmdParse
 ��������  : �����ַ������������
 �������  : VOS_UINT8* pData
             VOS_UINT16 usLen
             VOS_UINT8* pName
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��31��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AnyCharCmdParse(VOS_UINT8* pData, VOS_UINT16 usLen, VOS_UINT8* pName)
{
    VOS_UINT16 i,j;
    VOS_UINT8  bInQoute = 0;

    VOS_UINT8  aucPara[AT_PARA_MAX_LEN + 1]  = {0};     /* �������ý������Ĳ����ַ��� */
    VOS_UINT16 usParaLen                     = 0;       /* ������ʶ�����ַ������� */

    AT_ResetParseVariable();    /* ���ý��������õ�ȫ�ֱ��� */

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* ���������������*/
    g_stATParseCmd.ucCmdFmtType = AT_EXTEND_CMD_TYPE;       /* ������������*/

    g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)pName) - 2;    /* ������ ^CPBW ����*/

    PS_MEM_CPY(g_stATParseCmd.stCmdName.aucCmdName, pName, g_stATParseCmd.stCmdName.usCmdNameLen);

    /* ^CPBW=[<index>][,<number>[,<type>[,<text>,<coding>]]] */
    /* ^SCPBW= (1-65535),(numa),(0-255),(numb),(0-255),(numc),(0-255),(numd),(0-255),(text),(0,1),(email)*/
    /* +CPBW=[<index>][,<number>[,<type>[,<text>]]] */

    /* seperate para by char ',' */
    for(i=0; i < usLen; i++,pData++)
    {
        if ((' ' == *pData) && (0 == bInQoute))
        {
            continue;          /* skip space char not in quatation*/
        }
        else if (',' == *pData)
        {
            if (bInQoute)
            {
                if (1 == bInQoute)
                {
                    /* ������','���ǲ�����һ���֣����ǲ����ָ��� */
                    aucPara[usParaLen] = *pData;
                    usParaLen++;

                    continue;
                }

                bInQoute = 0;      /* ˫�����ڿ��ܻ���˫���ţ������ٸ��ݵڶ���˫������Ϊ�ַ������� , �Բ����ָ��','��Ϊ�ַ�����������*/

                /* ���������쳣 : ���ַ������棬','ǰ�����Ч�ո� */
                for(j=usParaLen-1; j>0; j--)
                {
                    if(' ' == aucPara[j])
                    {
                        usParaLen --;
                    }
                    else if ('"' == aucPara[j])
                    {
                        break;
                    }
                    else
                    {
                        return AT_CME_INCORRECT_PARAMETERS;    /* ���һ��˫���ź����������ַ������ش��� */
                    }
                }
            }

            if(i < (usLen-1))
            {
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(aucPara, usParaLen))
                {
                    return AT_ERROR;
                }

                usParaLen = 0;

                /* too many para */
            }

            continue;
        }
        else
        {
            /* �洢������ȫ�ֱ����� */
            aucPara[usParaLen] = *pData;
            usParaLen++;

            if ('"' == *pData)
            {
                bInQoute++;
            }
        }
    }

    if(ERR_MSP_SUCCESS != atfwParseSaveParam(aucPara, usParaLen))
    {
        return AT_ERROR;
    }

    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : AnyCharCmdProc
 ��������  : ֧�������ַ����ַ�������������Ĵ���
            (����V3R1�����󣬴������֧���������)
 �������  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��31��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AnyCharCmdProc(VOS_UINT8 *pData, VOS_UINT16* pusLen)
{
    VOS_UINT16 i;
    VOS_UINT32 ulRet = 0;
    VOS_UINT8  ucCmdName_lowercase[3][16]={"at^cpbw=?", "at+cpbw=?", "at^scpbw=?"};
    VOS_UINT8  ucCmdName_uppercase[3][16]={"AT^CPBW=?", "AT+CPBW=?", "AT^SCPBW=?"};

    for(i = 0; i < 3; i++)
    {
        if(TRUE == CheckAnyCharCmdName(pData, pusLen, ucCmdName_lowercase[i], ucCmdName_uppercase[i]))
        {
            ulRet = FormatCmdStr(pData,pusLen, ucAtS3);
            if(ERR_MSP_SUCCESS != ulRet)
            {
                return AT_ERROR;
            }

            return AnyCharCmdParse(pData, *pusLen, &(ucCmdName_uppercase[i][2]));
        }
    }

    return AT_FAILURE;
}



/*****************************************************************************
 �� �� ��  : At_ReadyClientCmdProc
 ��������  : Ready״̬��ͨ���������
 �������  : VOS_UINT8 ucIndex
             VOS_UINT8 *pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��2��
    ��    ��   : L00171473
    �޸�����   : ���˳�����"AT"֮ǰ������
*****************************************************************************/
VOS_VOID At_ReadyClientCmdProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32 ulRet                           = ERR_MSP_FAILURE;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult         = AT_WAIT_ASYNC_RETURN;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;

    if(usLen < 3)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    SaveRepeatCmd(pClientContext, pData, usLen);

    At_ResetCombinParseInfo(ucIndex);

    /* Modified by l00171473 for DTS2011120801675 UARTͨ��У׼ , 2011-12-3, begin */
    ulRet = AT_DiscardInvalidChar(pData, &usLen);
    if (ERR_MSP_SUCCESS != ulRet)
    {
        return ;
    }
    /* Modified by l00171473 for DTS2011120801675 UARTͨ��У׼ , 2011-12-3, end */

    ulRet = AnyCharCmdProc(pData, &usLen);

    if(AT_SUCCESS == ulRet)     /* �������ַ����������� */
    {
        /* ����� */
        ulRet = CmdParseProc(ucIndex, pData, usLen);
        if((AT_OK != ulRet) && (AT_WAIT_ASYNC_RETURN != ulRet))
        {
            At_ResetCombinParseInfo(ucIndex);
        }

        At_FormatResultData(ucIndex, ulRet);

        return ;
    }
    else if(AT_FAILURE != ulRet)    /* �������ַ��������������������ʧ�� */
    {
        At_FormatResultData(ucIndex, ulRet);

        return;
    }
    else    /* ���������ַ����������� */
    {
        /* do nothing */
    }

    ulRet = CmdStringFormat(ucIndex, pData, &usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        At_FormatResultData(ucIndex, ulRet);

        return;
    }

    /* ����V3R1Ҫ��ǰ�����ַ�����"AT"���������κ���Ϣ */
    if(AT_SUCCESS != At_CheckCharA(*pData))   /* �������'A'/'a' */
    {
        return;
    }

    if(AT_SUCCESS != At_CheckCharT(*(pData+1)))   /* �������'T'/'t' */
    {
        return;
    }

    /* SIMLOCK���������61�����������⴦�� */
    if (AT_SUCCESS == At_ProcSimLockPara(ucIndex, pData, usLen))
    {
        return;
    }

    /* ^DOCK������滹��"^"��"="�����⴦�� */
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (AT_SUCCESS == AT_HandleDockSetCmd(ucIndex, pData, usLen))
    {
        return;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* AP-Modem��̬�£���������AT^FACAUTHPUBKEY��AT^SIMLOCKDATAWRITE��������������Ѿ������˽�������
       ������������512����Ҫ���⴦��*/
    if (AT_SUCCESS == At_HandleApModemSpecialCmd(ucIndex, pData, usLen))
    {
        return;
    }

    ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CombineCmdChkProc(ucIndex, pData, usLen);

    /* ���ؽ�� */
    if((AT_FAILURE == ulResult) || (AT_SUCCESS == ulResult))
    {
        return ;
    }

    if(AT_WAIT_ASYNC_RETURN != ulResult)
    {
        At_FormatResultData(ucIndex, ulResult);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : atCmdMsgProc
 ��������  : �����
 �������  : VOS_UINT8 ucClientId
              VOS_UINT8 *pDataIn
             VOS_UINT16 usLenIn
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : c64416
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ������AT_XML_MODE��ģʽ�Ĵ���
  3.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_VOID atCmdMsgProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen)
{
    VOS_UINT32                          ulRet = ERR_MSP_FAILURE;
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_WAIT_ASYNC_RETURN;
    AT_PARSE_CONTEXT_STRU              *pClientContext = NULL;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    if ((0 == usLen) || (AT_CMD_MAX_LEN < usLen))
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    if (AT_SMS_MODE == pClientContext->ucMode)
    {
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_SmsProc(ucIndex, pData, usLen);

        if ((AT_SUCCESS == ulResult)
         || (AT_WAIT_SMS_INPUT == ulResult))
        {
            At_FormatResultData(ucIndex,ulResult);
            return ;
        }

        gastAtClientTab[ucIndex].usSmsTxtLen = 0;   /* ����BUFFER��� */

        At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);         /* �û�����״̬ */

        if (AT_WAIT_ASYNC_RETURN == ulResult)
        {
            if (NULL != pClientContext->pstCmdElement)
            {
                /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, begin*/
                if (AT_SUCCESS != At_StartTimer(pClientContext->pstCmdElement->ulSetTimeOut, ucIndex))
                {
                    AT_ERR_LOG("atCmdMsgProc():ERROR:Start Timer Failed");
                }
                /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, end*/

                pClientContext->ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
            }
            return;
        }

        At_FormatResultData(ucIndex,ulResult);
        return;
    }
    else if (AT_XML_MODE == pClientContext->ucMode)
    {
        /* ����XML���봦���� */
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_ProcXmlText(ucIndex, pData, usLen);

        /* ����ɹ��������ʾ��">" */
        if (AT_WAIT_XML_INPUT == ulResult)
        {
            At_FormatResultData(ucIndex,ulResult);
            return;
        }

        /* ��ջ����� */
        PS_MEM_FREE(WUEPS_PID_AT, pstAgpsCtx->stXml.pcXmlTextHead);                         /* XML BUFFER��� */
        pstAgpsCtx->stXml.pcXmlTextHead = VOS_NULL_PTR;
        pstAgpsCtx->stXml.pcXmlTextCur  = VOS_NULL_PTR;

        At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);                           /* �û�����״̬ */

        if (AT_WAIT_ASYNC_RETURN == ulResult)
        {
            if (NULL != pClientContext->pstCmdElement)
            {
                if (AT_SUCCESS != At_StartTimer(pClientContext->pstCmdElement->ulSetTimeOut, ucIndex))
                {
                    AT_ERR_LOG("atCmdMsgProc():ERROR:Start Timer Failed");
                }

                pClientContext->ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
            }
            return;
        }

        At_FormatResultData(ucIndex,ulResult);
        return;
    }
    else
    {
    }

    /* ���������������������ͨ������������ */
    ulRet = AT_ParseCmdIsComb(ucIndex, pData, usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return;
    }

    /* �ж��Ƿ���PEND״̬��ͨ�� */
    ulRet = AT_ParseCmdIsPend(ucIndex, pData, usLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return;
    }

    At_ReadyClientCmdProc(ucIndex, pData, usLen);

    return ;
}


/*****************************************************************************
 �� �� ��  : At_CmdStreamRcv
 ��������  : AT�����ַ�����Ԥ����
 �������  : VOS_UINT8 ucIndex
             VOS_UINT8* pData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_CmdStreamRcv(VOS_UINT8 ucIndex, VOS_UINT8* pData, VOS_UINT16 usLen)
{
    VOS_UINT8* pHead = NULL;
    VOS_UINT16 usCount = 0;  /* ��ǰָ����ַ�λ�� */
    VOS_UINT16 usTotal = 0;  /* �Ѿ�������ַ����� */
    AT_PARSE_CONTEXT_STRU* pstClientContext = NULL;

    /* ucIndexֻ���һ�Σ��������Ӻ������ټ�� */
    if((NULL == pData) || (ucIndex >= AT_MAX_CLIENT_NUM))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstClientContext = &(g_stParseContext[ucIndex]);

    pHead = pData;

    /* �н�����(<CR>�����û�ָ��) */
    while(usCount++ < usLen)
    {
        /*lint -e960 Note -- Violates MISRA 2004 Required Rule 4.1, Prohibited escape sequence used (hexadecimal)*/
        if(At_CheckCmdSms(*(pData+usCount-1), pstClientContext->ucMode))
        /*lint +e960*/
        {
            /* �������Ѿ������� */
            if(pstClientContext->usDataLen > 0)
            {
                if((pstClientContext->usDataLen + usCount) >= AT_CMD_MAX_LEN)
                {
                    pstClientContext->usDataLen = 0;
                    return ERR_MSP_INSUFFICIENT_BUFFER;
                }

                PS_MEM_CPY(&pstClientContext->aucDataBuff[pstClientContext->usDataLen], pHead, usCount);
                pstClientContext->usDataLen += usCount;
            }
            else    /* ������������ */
            {
                PS_MEM_CPY(&pstClientContext->aucDataBuff[0], pHead, (VOS_SIZE_T)(usCount-usTotal));
                pstClientContext->usDataLen = usCount-usTotal;
            }

            RepeatCmdProc(pstClientContext);

            atCmdMsgProc(ucIndex, pstClientContext->aucDataBuff, pstClientContext->usDataLen);

            pHead = pData+usCount;
            usTotal = usCount;
            pstClientContext->usDataLen = 0;
        }
    }

    /* �в����ַ�δ������Ҫ���� */
    if(usTotal < usLen)
    {
        if((pstClientContext->usDataLen + (usLen-usTotal)) >= AT_CMD_MAX_LEN)
        {
            pstClientContext->usDataLen = 0;
            return ERR_MSP_INSUFFICIENT_BUFFER;
        }

        PS_MEM_CPY(&pstClientContext->aucDataBuff[pstClientContext->usDataLen],pHead,(VOS_UINT32)(usLen-usTotal));

        pstClientContext->usDataLen += (VOS_UINT16)(usLen-usTotal); /* (pData-pHead+ulLen); */
    }

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : At_CombineBlockCmdProc
 ��������  : �������ͻ�������Ĵ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID At_CombineBlockCmdProc(VOS_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM_UINT32         ulResult = AT_WAIT_ASYNC_RETURN;
    AT_PARSE_CONTEXT_STRU* pClientContext = NULL;
    AT_FW_COMBINE_CMD_INFO_STRU* pstCombineCmdInfo = NULL;
    VOS_UINT8* pucBlockCmd = NULL;
    VOS_UINT16 usBlockCmdLen = 0;

    if(ucIndex >= AT_MAX_CLIENT_NUM)
    {
        return;
    }

    pClientContext = &(g_stParseContext[ucIndex]);

    pstCombineCmdInfo = &pClientContext->stCombineCmdInfo;

    /* �ж���������Ƿ������ */
    if((pstCombineCmdInfo->usProcNum < pstCombineCmdInfo->usTotalNum))
    {
        /* ������һ������ */
        ulResult = (AT_RRETURN_CODE_ENUM_UINT32)At_CombineCmdProc(ucIndex);

        /* ���ؽ�� */
        if((AT_FAILURE == ulResult) || (AT_SUCCESS == ulResult))
        {
            return ;
        }

        if(AT_WAIT_ASYNC_RETURN != ulResult)
        {
            At_FormatResultData(ucIndex, ulResult);
        }

        return ;
    }

    /* �ж��Ƿ��л�������� */
    ucIndex = AT_BlockCmdCheck();
    if(ucIndex < AT_MAX_CLIENT_NUM)
    {
        pClientContext = &(g_stParseContext[ucIndex]);

        /* ֹͣ��������Ķ�ʱ�� */
        AT_StopRelTimer(ucIndex, &pClientContext->hTimer);

        usBlockCmdLen = pClientContext->usBlockCmdLen;
        pucBlockCmd = (VOS_UINT8*)AT_MALLOC(usBlockCmdLen);
        if(NULL == pucBlockCmd)
        {
            /* ������ʱ���ػ��������������󴥷� */
            return ;
        }

        PS_MEM_CPY(pucBlockCmd, pClientContext->pBlockCmd, usBlockCmdLen);

        AT_ClearBlockCmdInfo(ucIndex);

        /* ���������� */
        At_ReadyClientCmdProc(ucIndex, pucBlockCmd, usBlockCmdLen);

        AT_FREE(pucBlockCmd);
        /* pucBlockCmd = NULL; */

        return ;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : At_CmdMsgDistr
 ��������  : AT�Դ�����Ϣ�ַ�
 �������  : AT_MSG_STRU* pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��19��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��04��17��
    ��    ��   : f00179208
    �޸�����   : C�˵�����λ��Ŀ

  3.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: ����ģʽ�л������

  4.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III

  5.��    ��   : 2015��3��12��
    ��    ��   : A00165503
    �޸�����   : DTS2015032409785: ����ˮ�߼�⹦��

  6.��    ��   : 2015��9��5��
    ��    ��   : A00165503
    �޸�����   : DTS2015090105100: NDIS���������޷��Ͽ�����
*****************************************************************************/
VOS_VOID At_CmdMsgDistr(AT_MSG_STRU *pstMsg)
{
    AT_CMD_MSG_NUM_CTRL_STRU           *pstMsgNumCtrlCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLen = 0;
    VOS_UINT8                          *pData = NULL;
    VOS_UINT8                           ucIndex = 0;
    VOS_ULONG                           ulLockLevel;

    if (AT_NORMAL_TYPE_MSG == pstMsg->ucType)
    {
        pstMsgNumCtrlCtx = AT_GetMsgNumCtrlCtxAddr();

        /* ���м��� */
        /*lint -e571*/
        VOS_SpinLockIntLock(&(pstMsgNumCtrlCtx->stSpinLock), ulLockLevel);
        /*lint +e571*/

        if ( pstMsgNumCtrlCtx->ulMsgCount > 0)
        {
            pstMsgNumCtrlCtx->ulMsgCount--;
        }

        VOS_SpinUnlockIntUnlock(&(pstMsgNumCtrlCtx->stSpinLock), ulLockLevel);
    }

    usLen   = pstMsg->usLen;
    pData   = pstMsg->aucValue;
    ucIndex = pstMsg->ucIndex;

    /* C��/HIFI��λʱ��ģ�����AT��AT������Ϣ */
    switch(pstMsg->ucType)
    {
        case ID_CCPU_AT_RESET_START_IND:
            AT_RcvCcpuResetStartInd(pstMsg);
            return;

        case ID_CCPU_AT_RESET_END_IND:
            AT_RcvCcpuResetEndInd(pstMsg);
            return;

        case ID_HIFI_AT_RESET_START_IND:
            AT_RcvHifiResetStartInd(pstMsg);
            return;

        case ID_HIFI_AT_RESET_END_IND:
             AT_RcvHifiResetEndInd(pstMsg);
            return;

        default:
            break;
    }

    AT_AddUsedClientId2Tab(ucIndex);

    /* �������C�˸�λǰ�򲻴����κ�AT���� */
    if (VOS_TRUE == AT_GetResetFlag())
    {
        return;
    }

    if (AT_SWITCH_CMD_MODE_MSG == pstMsg->ucType)
    {
        AT_RcvSwitchCmdModeMsg(pstMsg->ucIndex);
        return;
    }

    if (AT_WATER_LOW_MSG == pstMsg->ucType)
    {
        AT_RcvWaterLowMsg(pstMsg->ucIndex);
        return;
    }

    if (AT_NCM_CONN_STATUS_MSG == pstMsg->ucType)
    {
        AT_NDIS_ConnStatusChgProc(NCM_IOCTL_STUS_BREAK);
        return;
    }


    if(AT_COMBIN_BLOCK_MSG == pstMsg->ucType)
    {
        At_CombineBlockCmdProc(ucIndex);
        return;
    }

    At_CmdStreamRcv(ucIndex, pData, usLen);

    return;
}


/******************************************************************************
 ��������: atfwParseSaveParam
 ��������: �����ַ��������������ȫ�ֱ���

 ����˵��:
   pStringBuf [in/out] �ַ�������
   usLen [in] �ַ�������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
 2.��    ��   : 2013��03��11��
   ��    ��   : l00198894
   �޸�����   : Body SAR��Ŀ

******************************************************************************/
VOS_UINT32 atfwParseSaveParam(VOS_UINT8* pStringBuf, VOS_UINT16 usLen)
{
    if ((usLen > AT_PARA_MAX_LEN) || (gucAtParaIndex >= AT_MAX_PARA_NUMBER))
    {
        return ERR_MSP_FAILURE;
    }

    /* �������Ϊ0���������ַ���ָ��Ϊ�գ����򷵻�ʧ�� */
    if ((NULL == pStringBuf) && (0 != usLen))
    {
        return ERR_MSP_FAILURE;
    }

    /* ����ַ�������Ϊ0������Ҫ���� */
    if((0 != usLen) && (NULL != pStringBuf))
    {
        PS_MEM_CPY(gastAtParaList[gucAtParaIndex].aucPara, pStringBuf, usLen);
    }

    gastAtParaList[gucAtParaIndex].usParaLen = usLen;

    gucAtParaIndex++;

    return ERR_MSP_SUCCESS;
}

/******************************************************************************
 �� �� ��  : AT_SaveCdataDialParam
 ��������  : ���沦����Ϣ"#777"
 �������  : VOS_UINT8                          *pStringBuf
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

******************************************************************************/
VOS_UINT32 AT_SaveCdataDialParam(
    VOS_UINT8                          *pStringBuf,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                          *pucCurrPtr = pStringBuf;
    VOS_UINT16                          usLength;

    if ((usLen > AT_PARA_MAX_LEN) || (NULL == pStringBuf))
    {
        return ERR_MSP_FAILURE;
    }
    /* Ϊ�������"*99#", "*98#",
       ��"#777"������Ϊ:
       #,
       #777,
       777
    */

    if (AT_CDATA_DIAL_777_LEN < usLen)
    {
        /* ָ������'D' */
        pucCurrPtr++;

        /* ����'#' */
        gastAtParaList[gucAtParaIndex].aucPara[0] = *pucCurrPtr;
        gastAtParaList[gucAtParaIndex].usParaLen  = 1;

        /* ����'#777' */
        gucAtParaIndex++;
        usLength = usLen - 1;
        PS_MEM_CPY(gastAtParaList[gucAtParaIndex].aucPara, pucCurrPtr, usLength);
        gastAtParaList[gucAtParaIndex].usParaLen = usLength;

        /* ����'777' */
        pucCurrPtr++;
        gucAtParaIndex++;
        usLength--;
        PS_MEM_CPY(gastAtParaList[gucAtParaIndex].aucPara, pucCurrPtr, usLength);
        gastAtParaList[gucAtParaIndex].usParaLen = usLength;

    }

    gucAtParaIndex++;

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : At_CmdTestProcOK
 ��������  : ����Ĳ���ģʽ�·���OK�Ĵ�����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_CmdTestProcOK(VOS_UINT8 ucIndex)
{
    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_CmdTestProcERROR
 ��������  : ����Ĳ���ģʽ�·���ERROR�Ĵ�����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_CmdTestProcERROR(VOS_UINT8 ucIndex)
{
    return AT_ERROR;
}


/******************************************************************************
 ��������: atFWSendMsg
 ��������: AT��ܸ�����ģ�鷢����Ϣ

 ����˵��:
   TaskId [in] ����ID
   MsgId [in] ��ϢID
   VOS_VOID * pData [in/out] ������Ϣ������
   uLen [in] ������Ϣ�ĳ���

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 atFWSendMsg(VOS_UINT32 TaskId,  VOS_VOID* pData, VOS_UINT32 uLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    MsgBlock *pMsgBlock = NULL;

    pMsgBlock = VOS_AllocMsg(WUEPS_PID_AT, uLen);
    if(NULL == pMsgBlock)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pMsgBlock->ulReceiverPid = TaskId;
    pMsgBlock->ulSenderPid   = WUEPS_PID_AT;

    VOS_MemCpy(pMsgBlock->aucValue, pData, uLen);

    ulRet = VOS_SendMsg(WUEPS_PID_AT, pMsgBlock);
    if (VOS_OK != ulRet)
    {

    }
    else
    {
        ulRet = ERR_MSP_SUCCESS;
    }

    return ulRet;
}


/******************************************************************************
 ��������: AT_FwSendClientMsg
 ��������: ��������Ϣ�ظ�����ӿ�

 ����˵��:
   ucClientId [in] client id
   ulMsgId [in] message id
   usMsgParamSize [in] ��Ϣ���С
   VOS_VOID* pMsgParam [in] ��Ϣ������

 ��    ��: �޾�ǿ/00064416 [2011-04-01]
******************************************************************************/
VOS_UINT32 AT_FwSendClientMsg(VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgId, VOS_UINT16 usMsgParamSize, VOS_VOID* pMsgParam)
{
    VOS_UINT32 ulRet = ERR_MSP_FAILURE;
    VOS_UINT32 ulMsgLen = 0;
    AT_FW_MSG_STRU* pstAtFwMsg = NULL;
    AT_FW_CMD_BINARY_MSG_STRU* pstBinaryInfo = NULL;

    if ((0 == usMsgParamSize) || (NULL == pMsgParam))
    {
        return ERR_MSP_FAILURE;
    }

    ulMsgLen = sizeof(AT_FW_MSG_STRU) + sizeof(AT_FW_CMD_BINARY_MSG_STRU) + usMsgParamSize;

    pstAtFwMsg = (AT_FW_MSG_STRU*)AT_MALLOC(ulMsgLen);
    if (NULL == pstAtFwMsg)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstAtFwMsg->ulMsgId = ID_MSG_AT_FW_CMD_BINARY_MSG;
    pstBinaryInfo = (AT_FW_CMD_BINARY_MSG_STRU*)pstAtFwMsg->pMsgParam;
    pstBinaryInfo->ucClientId = 0;
    pstBinaryInfo->ucSysMode = 0;
    pstBinaryInfo->usMsgSize = usMsgParamSize;
    pstBinaryInfo->ulMsgId = ulMsgId;
    PS_MEM_CPY(pstBinaryInfo->pMsg, pMsgParam, usMsgParamSize);

    ulRet = atFWSendMsg(ulRcvPid, pstAtFwMsg, ulMsgLen);
    if (ERR_MSP_SUCCESS != ulRet)
    {
        (VOS_VOID)vos_printf("atFWSendMsg failed ulRet %d", ulRet);
    }

    AT_FREE(pstAtFwMsg);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : AT_IsAbortCmdStr
 ��������  : �ж������ַ����Ƿ���NV�еĴ������һ��, ���Ƿ��Ǵ������.
             ���ֻ���Ʒ��ȷ��Balongƽ̨�Ĵ�ϻ���������AT�˿�����һ��AT��������������֧�ִ�ϣ�
             �����ö˿ڽ��յ�"AT"�ַ�����ʾ��Ҫ��������ִ�У������ɺ��ڸö˿����"ABORT"��
             ��ʾ�����ɣ����Խ�����һ�������������֧�ִ�ϣ�ʵ����Ŀǰ����һ�£�
             ��������ִ����ǰ���ö˿ڽ��յ��������ַ�����������

 �������  :ucIndex : ��ǰͨ������
            pucData : AT�����ַ���, ������ַ��Ѿ�ȥ���˲��ɼ��ַ�(<0x20��ASCII�ַ�),
                       �ո�,�س����ַ�. ��û���ַ���������
             usLen   : AT�����ַ�������, ��ȥ���˿ո� �س����ַ���ĳ���
 �������  : ��
 �� �� ֵ  : VOS_TRUE : �Ǵ������
             VOS_FALSE: ���Ǵ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, V7R1C50_At_Abort
  2.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : NETSCAN��������޸�

  3.��    ��   : 2013��10��19��
    ��    ��   : w00167002
    �޸�����   : �޸ĵ�ǰ����������index,֧�ָ�ͨ���µ������ϣ�

  4.��    ��   : 2013��10��31��
    ��    ��   : w00167002
    �޸�����   : NETSCAN:���ٷ�ת�����Ż�
  5.��    ��   : 2013��10��31��
    ��    ��   : w00167002
    �޸�����   : NETSCAN:TICK����ʱ��Ҳ����
*****************************************************************************/

VOS_UINT32 AT_IsAbortCmdStr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara = VOS_NULL_PTR;
    VOS_UINT32                          ulAbortCmdStrLen;
    VOS_UINT32                          ulAtCurrSetTick;
    AT_CMD_ABORT_TICK_INFO             *pstCmdAbortTick     = VOS_NULL_PTR;
    VOS_UINT32                          ulTimeInternal;

    ulAtCurrSetTick = VOS_GetTick();
    pstCmdAbortTick = At_GetAtCmdAbortTickInfo();

    /* ������ַ��Ѿ�ȥ���˲��ɼ��ַ�(<0x20��ASCII�ַ�),�ո�, S3, S5���ַ�. ��û���ַ��������� */

    ulAbortCmdStrLen = 0;

    /* ��ȡ�������Ĳ��� */
    pstAbortCmdPara  = AT_GetAbortCmdPara();

    if (VOS_NULL_PTR == pstAbortCmdPara)
    {
        return VOS_FALSE;
    }

    /* �ж��Ƿ�ʹ�ܴ������� */
    if ( VOS_TRUE != pstAbortCmdPara->ucAbortEnableFlg )
    {
        return VOS_FALSE;
    }



    /* ��⵱ǰ���tickֵ�Ƿ��������125ms����,��������㣬��ֱ�ӷ��ز���� */
    if  ( ulAtCurrSetTick >= pstCmdAbortTick->ulAtSetTick[ucIndex] )
    {

        ulTimeInternal = ulAtCurrSetTick - pstCmdAbortTick->ulAtSetTick[ucIndex];
    }
    else
    {
        ulTimeInternal = ulAtCurrSetTick + (AT_MAX_TICK_TIME_VALUE - pstCmdAbortTick->ulAtSetTick[ucIndex]);
    }

    if ( ulTimeInternal < AT_MIN_ABORT_TIME_INTERNAL)
    {
        return VOS_FALSE;
    }

    /* ��⵱ǰ�Ƿ��������ַ���ϣ�����ǣ���ֱ�ӷ��ش�� */
    if  ( VOS_TRUE == At_GetAtCmdAnyAbortFlg() )
    {
        return VOS_TRUE;
    }

    /* �����ж� */
    ulAbortCmdStrLen = VOS_StrLen((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr);
    if ( (0 == usLen) || (usLen != ulAbortCmdStrLen) )
    {
        return VOS_FALSE;
    }

    /* ��ǰ���������ַ���ϣ�����Ҫ���AT������ݣ��Ǵ������򷵻ش�� */
    if ( (0 == VOS_StrNiCmp((VOS_CHAR *)pucData, (VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, usLen)) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_AbortCmdProc
 ��������  : AT��ϵ�ͳһ�������
 �������  :  VOS_UINT8 ucIndex : ������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, V7R1C50_At_Abort

*****************************************************************************/
VOS_VOID AT_AbortCmdProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulTimerLen;
    VOS_UINT32                          ulResult;

    /* ��ָ���� */
    if ( VOS_NULL_PTR == g_stParseContext[ucIndex].pstCmdElement )
    {
        AT_WARN_LOG("AT_AbortCmdProc: pstCmdElement NULL.");
        return;
    }

    if ( VOS_NULL_PTR == g_stParseContext[ucIndex].pstCmdElement->pfnAbortProc )
    {
        return;
    }

    /* ���õ�ǰ���ڴ����AT�����Abort���� */
    ulResult = g_stParseContext[ucIndex].pstCmdElement->pfnAbortProc(ucIndex);
    if ( AT_WAIT_ASYNC_RETURN == ulResult )
    {
        /* ���ڵ�ǰAT�˿ڵ�״̬�Ѿ�����PEND״̬, �˴�����Ҫ�ٸ��¶˿�״̬ */

        /* ������ϱ�����ʱ��, ��ʱ����Ҫ��AT�˿��ϱ�ABORT */
        ulTimerLen = g_stParseContext[ucIndex].pstCmdElement->ulAbortTimeOut;
        if ( 0 == ulTimerLen )
        {
            AT_WARN_LOG("AT_AbortCmdProc: TimerLen 0.");
            return;
        }

        /* �𱣻���ʱ�� */
        if ( AT_SUCCESS != At_StartTimer(ulTimerLen, ucIndex) )
        {
            AT_WARN_LOG("AT_AbortCmdProc: StartTimer Err.");
            return;
        }
    }
    /* ��ʾATֱ�Ӵ�� ����Ҫ���첽��Ϣ */
    else if ( (AT_ABORT == ulResult)
           || (AT_OK    == ulResult) )
    {
        ulResult               = AT_ABORT;
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex,ulResult);
    }
    /* �����쳣������Ϣ����ʧ�� �ڴ�����ʧ�ܣ���ǰ����������Ͳ�֧�ִ��
       (����ָ���ѹ����յ��������, ����ǰָ���Ѳ�֧�ִ��)�ȣ����� ������ϴ��� */
    else
    {
        AT_WARN_LOG1("AT_AbortCmdProc, WARNING, Return Code %d!", ulResult);
    }

}

/*****************************************************************************
 �� �� ��  : AT_GetCmdElementInfo
 ��������  : �ڸ�������в���ָ������
 �������  : pucCmdName : �������ַ���
             ulCmdType  : ��������
 �������  : ��
 �� �� ֵ  : ������и�ָ�������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, V7R1C50_At_Abort

*****************************************************************************/
AT_PAR_CMD_ELEMENT_STRU* AT_GetCmdElementInfo(
    VOS_UINT8                          *pucCmdName,
    VOS_UINT32                          ulCmdType
)
{
    HI_LIST_S                          *pstCurList    = VOS_NULL_PTR;
    HI_LIST_S                          *pstCmdTblList = VOS_NULL_PTR;
    AT_PAR_CMDTBL_LIST_STRU            *pstCurCmdNode = VOS_NULL_PTR;
    VOS_UINT32                          i;


    /* ���õĵط���֤�����ָ�벻Ϊ�� */

    pstCmdTblList   = &(g_stCmdTblList);

    /* ����������Ͳ�����չ����Ҳ���ǻ������ֱ�ӷ��ؿ�ָ�� */
    if ((AT_EXTEND_CMD_TYPE != ulCmdType) && (AT_BASIC_CMD_TYPE != ulCmdType))
    {
        return VOS_NULL_PTR;
    }

    /* �ڸ�������в���ָ������ */
    msp_list_for_each(pstCurList, pstCmdTblList)
    {
        pstCurCmdNode = msp_list_entry(pstCurList, AT_PAR_CMDTBL_LIST_STRU, stCmdTblList);

        for (i = 0; i < pstCurCmdNode->usCmdNum; i++)
        {
            /* û�ҵ�ʱ����������в�����һ������ */
            if ((NULL == pstCurCmdNode->pstCmdElement) || (NULL == pstCurCmdNode->pstCmdElement[i].pszCmdName))
            {
                continue;
            }
            /* �ҵ�ʱ��ָ��ָ����Ӧ������ */
            if (ERR_MSP_SUCCESS == AT_STRCMP((VOS_CHAR*)pucCmdName, (VOS_CHAR*)pstCurCmdNode->pstCmdElement[i].pszCmdName))
            {
                return &(pstCurCmdNode->pstCmdElement[i]);
            }
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : AT_SaveCmdElementInfo
 ��������  : �ڸ��������ƥ��ָ���������������������������Ϣ
 �������  : ucIndex    : ATͨ����index
             pucCmdName : �������ַ���
             ulCmdType  : ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, V7R1C50_At_Abort

*****************************************************************************/
VOS_VOID AT_SaveCmdElementInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucCmdName,
    VOS_UINT32                          ulCmdType
)
{
    AT_PAR_CMD_ELEMENT_STRU            *pstGetCmdElemnet;

    if (VOS_NULL_PTR == pucCmdName)
    {
        return;
    }

    /* û���ҵ���Ӧ��ָ������ʱ��ֱ�ӷ��� */
    pstGetCmdElemnet = AT_GetCmdElementInfo(pucCmdName, ulCmdType);
    if (VOS_NULL_PTR == pstGetCmdElemnet)
    {
        AT_ERR_LOG("AT_SaveCmdElementInfo: GetCmdElementInfo Failed.");
        return;
    }

    /* �ҵ�ʱ�����浽ȫ�ֱ��� */
    g_stParseContext[ucIndex].pstCmdElement = pstGetCmdElemnet;

    return;
}


/*****************************************************************************
 �� �� ��  : AT_IsAnyParseClientPend
 ��������  : �ж��Ƿ��ж˿ڴ���PEND״̬
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : ����һ��ͨ������PEND״̬���򷵻�VOS_UINT32
             ������ͨ��������READY״̬���򷵻�VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
*****************************************************************************/
VOS_UINT32 AT_IsAnyParseClientPend(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucClientIndex;

    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /* ���ݵ�ǰ��¼��ͨ����ѯͨ��״̬ */
    for (i = 0; i < pstPortBuffCfg->ucNum; i++)
    {
        ucClientIndex = (VOS_UINT8)pstPortBuffCfg->ulUsedClientID[i];

        if (ucClientIndex >= AT_CLIENT_ID_BUTT)
        {
            continue;
        }

        if (AT_FW_CLIENT_STATUS_PEND == g_stParseContext[ucClientIndex].ucClientStatus)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_IsAllClientDataMode
 ��������  : �ж��Ƿ����ж˿ڶ�����DADAģʽ
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : ����ǰ����ʹ�õ�ͨ������������ģʽ���򷵻�AT_DATA_MODE
             ����ǰ����ʹ�õ�ͨ����һ������������ģʽ�Ҳ�����pend״̬���򷵻�AT_CMD_MODE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
*****************************************************************************/
VOS_UINT32 AT_IsAllClientDataMode(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT32                          ulDataModeNum;

    ulDataModeNum = 0;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    if (pstPortBuffCfg->ucNum > AT_MAX_CLIENT_NUM)
    {
        pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM;
    }

    /* �鿴�ж��ٸ�ͨ������dataģʽ */
    for (i = 0; i < pstPortBuffCfg->ucNum; i++)
    {
        ucClientIndex = (VOS_UINT8)pstPortBuffCfg->ulUsedClientID[i];
        if (ucClientIndex >= AT_CLIENT_ID_BUTT)
        {
            continue;
        }

        if (AT_DATA_MODE == gastAtClientTab[ucClientIndex].Mode)
        {
            ulDataModeNum++;
        }
    }

    /* ����ͨ���д���dataģʽ */
    if (ulDataModeNum == pstPortBuffCfg->ucNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : atCmdIsSupportedByCLMode
 ��������  : �жϵ�ǰ��at ������CLIģʽ���Ƿ���Ҫ����
 �������  : VOS_UINT8 ucIndex
 �������  : VOS_UINT8
 �� �� ֵ  :
            ���·���AT�����cmdindex�������е���CLģʽ�´�������AT�����index������VOS_TRUE
            ���·���AT�����cmdindex���������е���CLģʽ�´�������AT�����index������VOS_FALSE

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : f00279542
    �޸�����   : new add
  2.�޸���ʷ   : 2015��12��22��
    ��    ��   : c00299063
    �޸�����   : �޸�AT_CMD_CCMGS AT_CMD_CCMGW AT_CMD_CCMGD
*****************************************************************************/
VOS_UINT8 atCmdIsSupportedByCLMode(VOS_UINT8 ucIndex)
{
    AT_PAR_CMD_ELEMENT_STRU            *pstCmdElement = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulCmdArraySize;
    VOS_UINT32                          aulCmdIndex[]  = {
                                                             AT_CMD_CLIP,
                                                             AT_CMD_DTMF,
                                                             AT_CMD_CARDMODE,
                                                             AT_CMD_CMGS,
                                                             AT_CMD_CSCB,
                                                             AT_CMD_CNMI,
                                                             AT_CMD_CSCA,
                                                             AT_CMD_CSASM,
                                                             AT_CMD_CUSD,
                                                             AT_CMD_CMGW,
                                                             AT_CMD_CMGD,
                                                             AT_CMD_CCWA,
                                                             AT_CMD_CCFC,
                                                             AT_CMD_CLIR,
                                                             AT_CMD_CMMS,
                                                             AT_CMD_CSSN,
                                                             AT_CMD_CELLINFO,
                                                             AT_CMD_CPMS,
                                                             AT_CMD_RELEASERRC,
                                                             AT_CMD_EOPLMN,
                                                             AT_CMD_CNMR,
                                                             AT_CMD_CALL_MODIFY_INIT,
                                                             AT_CMD_CALL_MODIFY_ANS,
                                                             AT_CMD_ECONFDIAL,
                                                             AT_CMD_CLCCECONF,
                                                             AT_CMD_ECONFERR,
                                                             AT_CMD_CACMIMS,
                                                             AT_CMD_CHLD_EX};

    ulCmdArraySize = sizeof((aulCmdIndex)) / sizeof((aulCmdIndex[0]));

    pstCmdElement = g_stParseContext[ucIndex].pstCmdElement;

    /* CLCK�Ĳ�������ΪSC��FD����Ҫ������������Ҫ���� */
    if (AT_CMD_CLCK == pstCmdElement->ulCmdIndex)
    {
        if ((AT_CLCK_SC_TYPE == gastAtParaList[0].ulParaValue)
         || (AT_CLCK_FD_TYPE == gastAtParaList[0].ulParaValue))
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* CPWD�Ĳ�������ΪSC��FD����Ҫ������������Ҫ���� */
    if (AT_CMD_CPWD == pstCmdElement->ulCmdIndex)
    {
        if ((AT_CLCK_SC_TYPE == gastAtParaList[0].ulParaValue)
         || (AT_CLCK_P2_TYPE == gastAtParaList[0].ulParaValue))
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* �ж��·���AT�����cmdindex�Ƿ��������е���CLģʽ�´�������AT�����index */
    for (ulLoop = 0; ulLoop < ulCmdArraySize; ulLoop++)
    {
        if (pstCmdElement->ulCmdIndex == aulCmdIndex[ulLoop])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


