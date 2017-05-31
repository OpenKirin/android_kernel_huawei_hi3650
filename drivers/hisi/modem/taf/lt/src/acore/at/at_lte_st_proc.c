

/******************************************************************************
 */
/* PROJECT   :
 */
/* SUBSYSTEM :
 */
/* MODULE    :
 */
/* OWNER     :
 */
/******************************************************************************
 */


/******************************************************************************
 */
/*����AT����CheckList(chenpeng/00173035 2010-12-17):
 */
/*
 */
/*
 */
/* �������checklist:
 */
/*   1��AT���������Ƿ���ȷ
 */
/*      typedef VOS_UINT8 AT_CMD_OPT_TYPE;
 */
/*      #define AT_CMD_OPT_SET_CMD_NO_PARA     0
 */
/*      #define AT_CMD_OPT_SET_PARA_CMD        1
 */
/*      #define AT_CMD_OPT_READ_CMD            2
 */
/*      #define AT_CMD_OPT_TEST_CMD            3
 */
/*      #define AT_CMD_OPT_BUTT                4
 */
/*
 */
/*   2�����������Ƿ����Ҫ��
 */
/*      gucAtParaIndex
 */
/*
 */
/*   3��ÿ�������ĳ����Ƿ���ȷ���Ƿ�Ϊ0
 */
/*      gastAtParaList[0].usParaLen
 */
/*      gastAtParaList[1].usParaLen
 */
/*
 */
/*   4��ÿ������ȡֵ��Լ��(ȡֵ��Χ��������������������)�Ƿ�����
 */
/*      ע:����ȡֵԼ��Ӧ�÷��ھ���������ģ�鱣֤���˴���͸������
 */
/*      gastAtParaList[0].ulParaValue
 */
/*      gastAtParaList[1].ulParaValue
 */
/******************************************************************************
 */
/*lint -save -e537 -e516 -e830 -e713 -e734 -e813 -e958 -e718 -e746*/
#include "osm.h"
#include "gen_msg.h"

#include "at_lte_common.h"

#include "gen_msg.h"
#include "ATCmdProc.h"

/*lint -e826*/

#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_ST_PROC_C


#define MAX_DATA_TYPE_LEN   50
/* BAND������Ŀ:A/E/F
 */
#define BAND_TYPE_NUM       3

const VOS_UCHAR g_AtTdsCnfStr[][MAX_DATA_TYPE_LEN] =
{
    "APCOFFSETFLAG",
    "APCOFFSET(BAND A)","APCOFFSET(BAND E)","APCOFFSET(BAND F)",
    "APC(BAND A)","APC(BAND E)","APC(BAND F)",
    "APCFREQ(BAND A)","APCFREQ(BAND E)","APCFREQ(BAND F)",
    "AGC(BAND A)","AGC(BAND E)","AGC(BAND F)",
    "AGCFREQ(BAND A)","AGCFREQ(BAND E)","AGCFREQ(BAND F)"
};

/*********************************************************************************
 */
/*
 */
/*********************************************************************************
 */
VOS_UINT32 atSetSRXPOWPara(VOS_UINT8 ucClientId)
{
    FTM_SET_SRXPOW_REQ_STRU stSetReq = {0};
    VOS_UINT32 ulRst;

    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(2 != gucAtParaIndex)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if( 0 == gastAtParaList[0].usParaLen ||
        0 == gastAtParaList[1].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }
    stSetReq.usSwitch = (VOS_UINT16)(gastAtParaList[0].ulParaValue);

    if((stSetReq.usSwitch == 0) || (stSetReq.usSwitch == 1))
    {
        ulRst = initParaListS16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[1])),1,&stSetReq.usulPower);
        if(ulRst != ERR_MSP_SUCCESS)
        {
            return ERR_MSP_INVALID_PARAMETER;
        }
    }

    /* lkf58113 @ 20110929 �����µķ��ͺ���:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_SRXPOW_REQ, ucClientId, (VOS_VOID*)(&stSetReq), sizeof(stSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_SRXPOW_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;

}

VOS_UINT32 atSetSRXPOWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_SRXPOW_CNF_STRU *pstCnf = NULL;

    /*vos_printf("\n enter atSetFFCHANSParaCnfProc !!!\n");
 */

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_SRXPOW_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

VOS_UINT32 atQrySRXPOWPara(VOS_UINT8 ucClientId)
{
    FTM_RD_SRXPOW_REQ_STRU stQryReq = {0};
    VOS_UINT32 ulRst;

    /* lkf58113 @ 20110929 �����µķ��ͺ���:atSendFtmDataMsg
 */
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_SRXPOW_REQ, ucClientId, (VOS_VOID*)(&stQryReq), sizeof(stQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_SRXPOW_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}

VOS_UINT32 atQrySRXPOWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	FTM_RD_SRXPOW_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_SRXPOW_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

	usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^SRXPOW:%d,%d",pstCnf->usSwitch,pstCnf->usulPower);

	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;

}

/*lint -restore*/

