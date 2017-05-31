

/*lint --e{10,718,746,628,830,539, 534, 586}*/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include  "vos.h"
#include  "diag_common.h"
#include  "SCMProc.h"
#include  "SOCPInterface.h"
#include  "diag_api.h"
#include  "diag_cfg.h"
#include  "msp_diag.h"
#include  "msp_errno.h"
#include  "diag_debug.h"
#include  "mdrv.h"
#include  "soc_socp_adapter.h"
/*lint -restore*/


/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_API_C
/*lint -restore +e767*/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

extern VOS_UINT8 g_EventModuleCfg[DIAG_CFG_PID_NUM];


VOS_UINT32 diag_CheckMsgPara(DIAG_AIR_MSG_LOG_STRU* pstRptMessage);
VOS_UINT32 diag_GetLayerMsgCfg(VOS_UINT32 ulCatId, VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetLayerSrcCfg(VOS_UINT32 ulModuleId);
VOS_UINT32 diag_GetLayerDstCfg(VOS_UINT32 ulModuleId);
VOS_UINT32 diag_GetLayerCfg(VOS_UINT32 ulSrcModuleId, VOS_UINT32 ulDstModuleId, VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetPrintCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulLevel);


VOS_UINT32 g_ulTransId = 0;

DIAG_LOG_PKT_NUM_ACC_STRU g_DiagLogPktNum ={0};
DIAG_TraceFilterFunc g_pFilterFunc = VOS_NULL;
DIAG_TraceMatchFunc  g_pMatchFunc  = VOS_NULL;


/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name   : DIAG_GetConnState
 Description     : ��ȡ��ǰ��������״̬
 Return          : 1:connect; 0:disconnect

 History         :
    1.c00326366      2015-6-24  Draft Enact
*****************************************************************************/
VOS_UINT32 DIAG_GetConnState(VOS_VOID)
{
    return (VOS_UINT32)((DIAG_IS_CONN_ON)?1:0);
}


/*****************************************************************************
 Function Name   : diag_GetMsgCfg
 Description     : ��ȡ�����Ϣ���˿���
 Input           :VOS_UINT32 ulCatId
                VOS_UINT32 ulMsgId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetLayerMsgCfg(VOS_UINT32 ulCatId, VOS_UINT32 ulMsgId)
{
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU *pstItemCfg =NULL;
    VOS_UINT32 i =  0;

    for(i = 0 ; i < g_stMsgCfg.ulCfgCnt; i++)
    {
       pstItemCfg = (g_stMsgCfg.astMsgCfgList + i);

       if(ulMsgId == pstItemCfg->ulId )
       {
           if(DIAG_CFG_SWT_CLOSE == pstItemCfg->ulSwt)
           {
              return ERR_MSP_CFG_LOG_NOT_ALLOW;
           }
           else if(DIAG_CFG_SWT_OPEN == pstItemCfg->ulSwt)
           {
              return ERR_MSP_SUCCESS;
           }
           else
           {
              return ERR_MSP_DIAG_MSG_CFG_NOT_SET;
           }
       }
    }

    return ERR_MSP_DIAG_MSG_CFG_NOT_SET;
}


VOS_UINT32 diag_GetLayerSrcCfg(VOS_UINT32 ulModuleId)
{
    VOS_UINT32 ulOffset = 0;

    if(DOPRA_PID_TIMER == ulModuleId)
    {
        return ERR_MSP_SUCCESS;
    }

    if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

		if(DIAG_CFG_SWT_OPEN == g_ALayerSrcModuleCfg[ulOffset])
		{
			return	ERR_MSP_SUCCESS;
		}
    }
    else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

		if(DIAG_CFG_SWT_OPEN == g_CLayerSrcModuleCfg[ulOffset])
		{
			return	ERR_MSP_SUCCESS;
		}
    }

	return ERR_MSP_CFG_LOG_NOT_ALLOW;
}

VOS_UINT32 diag_GetLayerDstCfg(VOS_UINT32 ulModuleId)
{
    VOS_UINT32 ulOffset = 0;

    if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

        if(DIAG_CFG_SWT_OPEN == g_ALayerDstModuleCfg[ulOffset])
        {
            return  ERR_MSP_SUCCESS;
        }
    }
    else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

        if(DIAG_CFG_SWT_OPEN == g_CLayerDstModuleCfg[ulOffset])
        {
            return  ERR_MSP_SUCCESS;
        }
    }

    return ERR_MSP_CFG_LOG_NOT_ALLOW;
}

/*****************************************************************************
 Function Name   : diag_GetLayerCfg
 Description     : ��ȡ�����Ϣ����״̬
 Input           :VOS_UINT32 ulSrcModuleId
                VOS_UINT32 ulDstModuleId
                VOS_UINT32 ulMsgId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetLayerCfg(VOS_UINT32 ulSrcModuleId, VOS_UINT32 ulDstModuleId, VOS_UINT32 ulMsgId)
{
    VOS_UINT32 ret = ERR_MSP_CFG_LOG_NOT_ALLOW;
    VOS_UINT32 ret2 = ERR_MSP_CFG_LOG_NOT_ALLOW;
    VOS_UINT32 ulMsgCfg = ERR_MSP_DIAG_MSG_CFG_NOT_SET;

    /*���ж���ϢID���˹����Ƿ�򿪣�����У��������ϢID����*/
    ulMsgCfg = diag_GetLayerMsgCfg(DIAG_CMD_LOG_CATETORY_LAYER_ID, ulMsgId);
    if(ERR_MSP_DIAG_MSG_CFG_NOT_SET == ulMsgCfg )
    {
        ret = diag_GetLayerSrcCfg(ulSrcModuleId);
        ret2 = diag_GetLayerDstCfg(ulDstModuleId);
        if((ERR_MSP_SUCCESS != ret) && (ERR_MSP_SUCCESS != ret2))
        {
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
        else
        {
            return ERR_MSP_SUCCESS;
        }
    }
    else if(ERR_MSP_SUCCESS == ulMsgCfg )
    {
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_CFG_LOG_NOT_ALLOW;
    }
}

/*****************************************************************************
 Function Name   : diag_GetPrintCfg
 Description     : ��ȡ��ӡ����״̬
 Input           :VOS_UINT32 ulModuleId
                VOS_UINT32 ulLevel
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-6  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetPrintCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulLevel)
{
    VOS_UINT32 ulLevelFilter = 0;
    VOS_UINT32 ulTmp = 0;

    /*��Э��ջ��LEVELֵת����MSP��HSO֮���LEVELֵ*/
    /*0x80000000<->0;0x40000000<->1;0x20000000<->2;0x10<->3;0x08000000<->4*/
	if((PS_LOG_LEVEL_OFF == ulLevel)||(ulLevel >= PS_LOG_LEVEL_BUTT))
	{
        diag_LNR(EN_DIAG_LNR_LOG_LOST, ulLevel, 0xAAAAAAAA);/* [false alarm]:alarm */
		return ERR_MSP_CFG_LOG_NOT_ALLOW;
	}

    ulLevelFilter = ((VOS_UINT32)1<<(7-ulLevel));

    ulTmp = (ulLevelFilter << 16) | g_PrintTotalCfg;

    /* ��ӡ�ܿ���ģ������*/
    if(DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE != g_PrintTotalCfg)
    {
        if(ulLevelFilter & g_PrintTotalCfg)
        {
            return ERR_MSP_SUCCESS;
        }
        else
        {
            diag_LNR(EN_DIAG_LNR_LOG_LOST, ulTmp, ulModuleId);
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
    }
    else
    {
        /*lint -save -e40*/
        /*��ȡģ���ӡ����״̬*/
        if(DIAG_CFG_MODULE_IS_INVALID((VOS_INT32)ulModuleId))
        {
            diag_LNR(EN_DIAG_LNR_LOG_LOST, ulModuleId, 0xBBBBBBBB);/* [false alarm]:alarm */
            return  ERR_MSP_CFG_LOG_NOT_ALLOW;
        }

        ulTmp = (ulLevelFilter << 16) | g_PrintModuleCfg[ulModuleId - VOS_PID_DOPRAEND];

        if(ulLevelFilter & g_PrintModuleCfg[ulModuleId - VOS_PID_DOPRAEND])
        {
            return ERR_MSP_SUCCESS;
        }
        else
        {
            diag_LNR(EN_DIAG_LNR_LOG_LOST, ulTmp, ulModuleId);
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
        /*lint -restore +e40*/
    }

    return ERR_MSP_SUCCESS;/*lint !e527*/
}


#define LTE_DIAG_PRINTF_LEN             (256+sizeof(VOS_UINT32)+sizeof(VOS_UINT32))

#define LTE_LOG_AFFIRM(c) \
do{ \
    if(!(c)) \
    { \
        vos_printf("LTE_LOG_ASSERT %d.\n", __LINE__); \
        return -1; \
    } \
}while(0)


/******************************************************************************
��������: DIAG_LogIdReport
��������: ��ӡ�����͵Ĵ�ӡ�ӿں���
����˵��:
            ulModuleId[in]  : ( 31-24:modemid,23-16:modeid,15-12:level )
            ulPid[in]       : PID
            ulLogId[in]     : ���ļ��ź��кŸ���DIAG_LOG_ID����
            amount[in]      : �ɱ����������������ulModuleId/ulLevel/ulLogId/amout��
            ...             : �ɱ����
����Լ��:
            1. ���Խ�ֹ�Դ˺������ж��η�װ��ֻ��ת����
            2. ֧�ֿɱ�Ĳ����������������ڵ���ʱ�ɲ���amountָ����������
            3. �ɱ����ֻ֧��int����
            4. Ŀǰ�汾��֧�ֵ�������������6���������Ĳ���Ĭ�϶���
******************************************************************************/
VOS_INT32 DIAG_LogIdReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid,
                        VOS_UINT32 ulLogId, VOS_UINT32 amount, ...)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulDataLength =0;
    VOS_CHAR ucDiagPrintData[LTE_DIAG_PRINTF_LEN]={0};
    VOS_INT32 val, i, lTmpLen, lSpareLen, lOccupyLen;
    va_list vl;
    VOS_UINT32 paranum;

    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT, ulLogId, 0, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_NO_INITILIZATION, ulLogId, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    ret = diag_GetPrintCfg(ulPid, DIAG_GET_PRINTF_LEVEL(ulModuleId));
    if(ERR_MSP_SUCCESS != ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_UNAVAILABLE, ulLogId, 2);
        return ERR_MSP_UNAVAILABLE;
    }

    *((VOS_UINT32*)ucDiagPrintData) = ulPid;
    *(VOS_UINT32*)(ucDiagPrintData + sizeof(VOS_UINT32)) = DIAG_GET_PRINTF_LEVEL(ulModuleId);

    lOccupyLen = 8;
    /*lint -save -e713 -e732*/
    lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;

    lTmpLen    = VOS_nsprintf(ucDiagPrintData + lOccupyLen, lSpareLen, "%d, ", ulLogId);
    LTE_LOG_AFFIRM(0 <= lTmpLen);

    lOccupyLen += lTmpLen;
    LTE_LOG_AFFIRM(LTE_DIAG_PRINTF_LEN >= (VOS_UINT32)lOccupyLen);
    lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;

    lTmpLen    = VOS_nsprintf(ucDiagPrintData + lOccupyLen, lSpareLen, "%u, ", VOS_GetTick());
    LTE_LOG_AFFIRM(0 <= lTmpLen);

    lOccupyLen += lTmpLen;
    LTE_LOG_AFFIRM(LTE_DIAG_PRINTF_LEN >= (VOS_UINT32)lOccupyLen);
    lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;

    va_start(vl, amount);/*lint !e530*/
    paranum = (amount > LTE_DIAG_PRINTF_PARAM_MAX_NUM) ? LTE_DIAG_PRINTF_PARAM_MAX_NUM : amount;

    for(i = 0; i < (VOS_INT32)paranum; i++)
    {
        val = va_arg(vl, int);
        /* coverity[overrun-local] */
        lTmpLen = VOS_nsprintf(ucDiagPrintData + lOccupyLen, lSpareLen, "%d, ", val);
        if(0 > lTmpLen)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_TOO_SMALL_BUFFER, lSpareLen, 3);
            va_end(vl);
            return -1;
        }

        lOccupyLen += lTmpLen;
        /* coverity[cond_at_most] */
        if(LTE_DIAG_PRINTF_LEN < (VOS_UINT32)lOccupyLen)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_TOO_SMALL_BUFFER, lOccupyLen, 4);
            va_end(vl);
            return -1;
        }
        lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;
    }
    va_end(vl);

    ulDataLength = lOccupyLen;


    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(ulModuleId);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_DOT;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(ulModuleId);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = 0;
    stDiagHead.pHeaderData      = VOS_NULL;

    stDiagHead.ulDataSize       = ulDataLength;
    stDiagHead.pData            = ucDiagPrintData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ret, 0, 5);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_OK, 0, 0, 0);
    }

	return ret;
    /*lint -restore*/
}


/*****************************************************************************
 �� �� ��  : diag_GetFileNameFromPath
 ��������  : �õ��ļ�·������ƫ��ֵ
 �������  : char* pcFileName
  1. cuijunqiang
*****************************************************************************/
VOS_CHAR * diag_GetFileNameFromPath(VOS_CHAR* pcFileName)
{
    VOS_CHAR    *pcPathPos1;
    VOS_CHAR    *pcPathPos2;
    VOS_CHAR    *pcPathPos;

    /* ����ϵͳ����ʹ��'\'������·�� */
    pcPathPos1 = (VOS_CHAR*)strrchr(pcFileName, '\\');

    /* ����ϵͳ����ʹ��'/'������·�� */
    pcPathPos2 = (VOS_CHAR*)strrchr(pcFileName, '/');

    pcPathPos = (pcPathPos1 > pcPathPos2) ? pcPathPos1 : pcPathPos2;/*lint !e613*/

    /* ���û�ҵ�'\'��'/'��ʹ��ԭ�����ַ���������ʹ�ýضϺ���ַ��� */
    if (VOS_NULL_PTR == pcPathPos)
    {
        pcPathPos = pcFileName;
    }
    else
    {
        pcPathPos++;
    }

    return pcPathPos;
}


/*****************************************************************************
 �� �� ��  : DIAG_LogReport
 ��������  : ��ӡ�ϱ��ӿ�
 �������  : ulModuleId( 31-24:modemid,23-16:modeid,15-12:level )
             pcFileName(�ϱ�ʱ����ļ�·��ɾ����ֻ�����ļ���)
             ulLineNum(�к�)
             pszFmt(�ɱ����)
*****************************************************************************/
VOS_UINT32 DIAG_LogReport(VOS_UINT32 ulModuleId, VOS_UINT32 ulPid, VOS_CHAR *cFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU stRptInfo;
    VOS_CHAR   *cOffsetName;
    VOS_UINT32 ulDataLength =0;
    VOS_UINT32 ulModule = 0;
    VOS_UINT32 ulLevel = 0;
    va_list    arg;/*lint !e830*/
    VOS_INT32  ulParamLen =0;
    VOS_ULONG  ulLockLevel;

    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_ERR, ERR_MSP_NO_INITILIZATION, ulModuleId, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    if(VOS_NULL == cFileName)
    {
        cFileName= " ";
    }

    /*��ȡ�����±�*/
    ulModule = ulPid;

    /*��ȡģ�鿪��״̬*/
    ulLevel = DIAG_GET_PRINTF_LEVEL(ulModuleId);

    ret = diag_GetPrintCfg(ulModule, ulLevel);
    if(ERR_MSP_SUCCESS != ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_ERR, ERR_MSP_UNAVAILABLE, ulModuleId, 2);
        return ERR_MSP_UNAVAILABLE;
    }

    /* �ļ����ض� */
    cOffsetName = diag_GetFileNameFromPath(cFileName);

    /*��HSO�Ĵ�ӡ�ַ�����ʽ����:pszFileName[ulLineNum]data��HSO����������[]ȥ��ȡ��Ӧ����Ϣ*/
	ulParamLen = VOS_nsprintf(stRptInfo.szText, DIAG_PRINTF_MAX_LEN,"%s[%d]", cOffsetName, ulLineNum);

    if(ulParamLen > DIAG_PRINTF_MAX_LEN)
    {
        /* �ڴ�Խ�磬������λ */
        mdrv_om_system_error((VOS_INT)DIAG_ERROR_MODID_OVERFLOW, __LINE__, ulParamLen, 0, 0);
        return ERR_MSP_FAILURE;
    }

    va_start(arg, pszFmt);/*lint !e530 !e586*/
    ulParamLen += VOS_nvsprintf((stRptInfo.szText + ulParamLen),\
				 (VOS_UINT32)(DIAG_PRINTF_MAX_LEN - ulParamLen), (const VOS_CHAR *)pszFmt, arg);
    if(ulParamLen > DIAG_PRINTF_MAX_LEN)
    {
        /* �ڴ�Խ�磬������λ */
        mdrv_om_system_error((VOS_INT)DIAG_ERROR_MODID_OVERFLOW, __LINE__, ulParamLen, 0, 0);
    }
    va_end(arg);/*lint !e530 !e586*/

	stRptInfo.szText[DIAG_PRINTF_MAX_LEN-1] = '\0';/*lint !e661*/
	ulDataLength = VOS_StrLen(stRptInfo.szText)+1;

    /*��װDIAG�������*/
    stRptInfo.ulModule = ulModule;
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulPrintLock, ulLockLevel);
    stRptInfo.ulNo = (g_DiagLogPktNum.ulPrintNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulPrintLock, ulLockLevel);

    /* 1:error, 2:warning, 3:normal, 4:info */
    /* (0|ERROR|WARNING|NORMAL|INFO|0|0|0) */
    stRptInfo.ulLevel  = (0x80000000) >> ulLevel;

    /* �ַ����ĳ��ȼ�����Ϣ�ĳ��� */
    ulDataLength += (sizeof(DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU) - (DIAG_PRINTF_MAX_LEN+1));

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(ulModuleId);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_PRINT;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(ulModuleId);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = 0;
    stDiagHead.pHeaderData      = VOS_NULL;

    stDiagHead.ulDataSize       = ulDataLength;
    stDiagHead.pData            = &stRptInfo;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_PRINTFV_OK, 0, 0, 4);
    }

    return ret;
}


/*****************************************************************************
 �� �� ��  : DIAG_TransReport_Ex
 ��������  : �ṹ�������ϱ���չ�ӿ�(��DIAG_TransReport�ഫ����DIAG_MESSAGE_TYPE)
 �������  : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-8:groupid )
             DIAG_TRANS_IND_STRU->ulMsgId(͸������ID)
             DIAG_TRANS_IND_STRU->ulLength(͸����Ϣ�ĳ���)
             DIAG_TRANS_IND_STRU->pData(͸����Ϣ)

*****************************************************************************/
VOS_UINT32 DIAG_TransReport_Ex(DIAG_TRANS_IND_STRU *pstData)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_TRANS_IND_STRU stTransInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    if((VOS_NULL_PTR == pstData) || (NULL == pstData->pData) || (0 == pstData->ulLength))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    diag_LNR(EN_DIAG_LNR_TRANS_IND, pstData->ulMsgId, VOS_GetSlice());

    stTransInfo.ulModule = pstData->ulPid;
    stTransInfo.ulMsgId  = pstData->ulMsgId;
    
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulTransLock, ulLockLevel);
    stTransInfo.ulNo     = (g_DiagLogPktNum.ulTransNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulTransLock, ulLockLevel);

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_GET_GROUP_ID(pstData->ulModule);
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstData->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_STRUCT;
    stDiagHead.u.stID.cmdid19b  = (pstData->ulMsgId)&0x7ffff;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstData->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stTransInfo);
    stDiagHead.pHeaderData      = &stTransInfo;

    stDiagHead.ulDataSize       = pstData->ulLength;
    stDiagHead.pData            = pstData->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ret, 0, 4);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_OK, pstData->ulMsgId, VOS_GetSlice(), 5);
    }

    return ret;
}


/*****************************************************************************
 �� �� ��  : DIAG_TransReport
 ��������  : �ṹ�������ϱ��ӿ�(�滻ԭ����DIAG_ReportCommand)
 �������  : DIAG_TRANS_IND_STRU->ulModule( 31-24:modemid,23-16:modeid )
             DIAG_TRANS_IND_STRU->ulMsgId(͸������ID)
             DIAG_TRANS_IND_STRU->ulLength(͸����Ϣ�ĳ���)
             DIAG_TRANS_IND_STRU->pData(͸����Ϣ)

 History   :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 DIAG_TransReport(DIAG_TRANS_IND_STRU *pstData)
{
    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    if((VOS_NULL_PTR == pstData) || (NULL == pstData->pData) || (0 == pstData->ulLength))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRANS_ERR, ERR_MSP_NO_INITILIZATION, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstData->ulModule = DIAG_GEN_MODULE_EX( DIAG_GET_MODEM_ID(pstData->ulModule), \
                                            DIAG_GET_MODE_ID(pstData->ulModule),  \
                                            DIAG_MSG_TYPE_PS);

    return DIAG_TransReport_Ex(pstData);
}


/*****************************************************************************
 �� �� ��  : DIAG_EventReport
 ��������  : �¼��ϱ��ӿڣ���PSʹ��(�滻ԭ����DIAG_ReportEventLog)
 �������  : DIAG_EVENT_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_EVENT_IND_STRU->ulEventId(event ID)
             DIAG_EVENT_IND_STRU->ulLength(event�ĳ���)
             DIAG_EVENT_IND_STRU->pData(event��Ϣ)

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 DIAG_EventReport(DIAG_EVENT_IND_STRU *pstEvent)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_EVENT_IND_STRU stEventIndInfo;
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*����Ƿ������¼��ϱ�*/
    if(!DIAG_IS_EVENT_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    if(VOS_NULL_PTR == pstEvent)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    /* �ں�GU��event���ƺ���Ҫ�ж��ӿ��� */
    if(0 == g_EventModuleCfg[pstEvent->ulPid - VOS_PID_DOPRAEND])
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ERR_MSP_INVALID_PARAMETER, 0, 3);
        return ERR_MSP_INVALID_PARAMETER;
    }

    /*��װDIAG�������*/
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulEventLock, ulLockLevel);
    stEventIndInfo.ulNo     = (g_DiagLogPktNum.ulEventNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulEventLock, ulLockLevel);
    
    stEventIndInfo.ulId     = pstEvent->ulEventId;
    stEventIndInfo.ulModule = pstEvent->ulPid;

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstEvent->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_EVENT;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstEvent->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stEventIndInfo);
    stDiagHead.pHeaderData      = &stEventIndInfo;

    stDiagHead.ulDataSize       = pstEvent->ulLength;
    stDiagHead.pData            = pstEvent->pData;

    ret = diag_ServicePackData(&stDiagHead);
    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_ERR, ret, 0, 4);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_EVENT_OK, 0, 0, 5);
    }
    return ret;
}


/*****************************************************************************
 �� �� ��  : DIAG_AirMsgReport
 ��������  : �տ���Ϣ�ϱ��ӿڣ���PSʹ��(�滻ԭ����DIAG_ReportAirMessageLog)
 �������  : DIAG_AIR_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_AIR_IND_STRU->ulMsgId(�տ���ϢID)
             DIAG_AIR_IND_STRU->ulDirection(�տ���Ϣ�ķ���)
             DIAG_AIR_IND_STRU->ulLength(�տ���Ϣ�ĳ���)
             DIAG_AIR_IND_STRU->pData(�տ���Ϣ��Ϣ)

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 DIAG_AirMsgReport(DIAG_AIR_IND_STRU *pstAir)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_AIR_IND_STRU stRptInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*����Ƿ�����LT �տ��ϱ�*/
    if (!DIAG_IS_LT_AIR_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    if((VOS_NULL == pstAir) || (VOS_NULL == pstAir->pData) || (0 == pstAir->ulLength))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    stRptInfo.ulModule  = pstAir->ulPid;
    stRptInfo.ulId      = pstAir->ulMsgId;
    stRptInfo.ulSide    = pstAir->ulDirection;
    
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulAirLock, ulLockLevel);
    stRptInfo.ulNo      = (g_DiagLogPktNum.ulAirNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulAirLock, ulLockLevel);

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstAir->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_AIR;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstAir->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stRptInfo);
    stDiagHead.pHeaderData      = &stRptInfo;

    stDiagHead.ulDataSize       = pstAir->ulLength;
    stDiagHead.pData            = pstAir->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_AIR_OK, 0, 0, 4);
    }

    return ret;
}


/*****************************************************************************
 Function Name   : DIAG_ReportVoLTELog
 Description     : VoLTE��Ϣ�ϱ��ӿ�
 Input           : DIAG_VoLTE_LOG_STRU* pRptMessage
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.fuxin      2013-12-30  create
    2.c64416         2014-11-18  �����µ���ϼܹ�
*****************************************************************************/
VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VOLTE_LOG_STRU* pRptMessage)
{
    VOS_UINT32 ret         = ERR_MSP_SUCCESS;
    VOS_UINT32 ulModuleId;
    DIAG_CMD_LOG_VOLTE_IND_STRU stRptInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG  ulLockLevel;

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    if((VOS_NULL == pRptMessage) || (VOS_NULL == pRptMessage->pData) || (0 == pRptMessage->ulDataSize))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulModuleId  = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    ret = diag_GetLayerCfg(ulModuleId, ulModuleId, pRptMessage->ulMessageID);

    if(ERR_MSP_SUCCESS != ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ERR_MSP_CFG_LOG_NOT_ALLOW, 0, 3);
	    return ERR_MSP_CFG_LOG_NOT_ALLOW;
    }

    stRptInfo.ulModule  = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    stRptInfo.ulId      = pRptMessage->ulMessageID;
    stRptInfo.ulSide    = pRptMessage->ulSideId;

    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulVoLTELock, ulLockLevel);
    stRptInfo.ulNo      = (g_DiagLogPktNum.ulVoLTENum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulVoLTELock, ulLockLevel);

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pRptMessage->ulId);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_VOLTE;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pRptMessage->ulId);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stRptInfo);
    stDiagHead.pHeaderData      = &stRptInfo;

    stDiagHead.ulDataSize       = pRptMessage->ulDataSize;
    stDiagHead.pData            = pRptMessage->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_VOLTE_OK, 0, 0, 5);
    }
	return ret;
}


/*****************************************************************************
 �� �� ��  : DIAG_TraceReport
 ��������  : �����Ϣ�ϱ��ӿڣ���PSʹ��(�滻ԭ����DIAG_ReportLayerMessageLog)
 �������  : pMsg(��׼��VOS��Ϣ�壬Դģ�顢Ŀ��ģ����Ϣ����Ϣ���л�ȡ)

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg)
{
    VOS_UINT32 ret, ulSrcModule, ulDstModule, ulMsgId;
    DIAG_OSA_MSG_STRU *pDiagMsg = (DIAG_OSA_MSG_STRU *)pMsg;
    DIAG_OSA_MSG_STRU *pNewMsg  = NULL;
    DIAG_CMD_LOG_LAYER_IND_STRU stTrace;

    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG    ulLockLevel;

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ;
    }

    if(VOS_NULL == pDiagMsg)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ERR_MSP_INVALID_PARAMETER, 0, 1);
        return ;
    }

    ulSrcModule = pDiagMsg->ulSenderPid;
    ulDstModule = pDiagMsg->ulReceiverPid;
    ulMsgId     = pDiagMsg->ulMsgId;

    /*����Ƿ���������Ϣ�ϱ�*/
    ret = diag_GetLayerCfg(ulSrcModule, ulDstModule, ulMsgId);
    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ERR_MSP_CFG_LOG_NOT_ALLOW, 0, 1);
        return ;
    }

    /* �����ṩ�Ĺ��˽ӿڣ�����0��ʾ�������ϱ� */
    if(VOS_NULL != g_pFilterFunc)
    {
        if(g_pFilterFunc(pDiagMsg))
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_FILTER, ulSrcModule, ulDstModule, ulMsgId);
            return ;
        }
    }

    pNewMsg = pDiagMsg;

    /* �����ṩ����Ϣƥ��ӿڣ����ܶ���Ϣ�����滻 */
    /* ����ֵΪ�ձ�ʾ���˲��ϱ������طǿ���ѷ��ص���Ϣ�ϱ� */
    if(VOS_NULL != g_pMatchFunc)
    {
        pNewMsg = g_pMatchFunc(pDiagMsg);
        if(VOS_NULL == pNewMsg)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_MATCH, ulSrcModule, ulDstModule, ulMsgId);
            return ;
        }
    }

    stTrace.ulModule    = ulSrcModule;
    stTrace.ulDestMod   = ulDstModule;
    stTrace.ulId        = ulMsgId;
    
    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulLayerLock, ulLockLevel);
    stTrace.ulNo        = (g_DiagLogPktNum.ulLayerNum++);
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulLayerLock, ulLockLevel);

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_MODE_COMM;       /* �����Ϣ����ʶ��ģʽ */
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_LAYER;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;

    ret = (DIAG_CFG_MODULE_IS_INVALID(ulSrcModule))?ulDstModule:ulSrcModule;

    stDiagHead.ulModemId        = VOS_GetModemIDFromPid(ret);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(stTrace);
    stDiagHead.pHeaderData      = &stTrace;

    stDiagHead.ulDataSize       = sizeof(DIAG_OSA_MSG_STRU) - sizeof(pNewMsg->ulMsgId) + pNewMsg->ulLength;
    stDiagHead.pData            = pNewMsg;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_TRACE_OK, 0, 0, 5);
    }
    return ;
}


/*****************************************************************************
 Function Name   : DIAG_TraceFilterFuncReg
 Description     : �����Ϣ����ע��ӿ�(�˽ӿڲ�֧���ظ�ע�ᣬ���ע�᷵��ʧ��)
 Input           : ���˴�����
 Output          : None
 Return          : ����ֵΪע����: 0-ע��ɹ�������-ע��ʧ��

 History         :
    1.c64416      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceFilterFuncReg(DIAG_TraceFilterFunc pFun)
{
    if(VOS_NULL == g_pFilterFunc)
    {
        g_pFilterFunc = pFun;
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_FAILURE;
    }
}


/*****************************************************************************
 Function Name   : DIAG_TraceMatchFuncReg
 Description     : �����Ϣƥ��ע��ӿ�(�˽ӿڲ�֧���ظ�ע�ᣬ���ע�᷵��ʧ��)
                    ��ע��ӿ��ṩ��TTFʹ�ã�ƥ�䴦��ӿ��п��ܶ���Ϣ������滻
 Input           : ���˴�����
 Output          : None
 Return          : ����ֵΪע����: 0-ע��ɹ�������-ע��ʧ��

 History         :
    1.c00326366      2015-06-16  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_TraceMatchFuncReg(DIAG_TraceMatchFunc pFun)
{
    if(VOS_NULL == g_pMatchFunc)
    {
        g_pMatchFunc = pFun;
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_FAILURE;
    }
}


/*****************************************************************************
 �� �� ��  : DIAG_UserPlaneReport
 ��������  : �û����ϱ��ӿڣ���PSʹ��(�滻ԭ����DIAG_ReportUserPlaneMessageLog)
 �������  : DIAG_USER_IND_STRU->ulModule( 31-24:modemid,23-16:modeid,15-12:level,11-0:pid )
             DIAG_USER_IND_STRU->ulMsgId(�û�����ϢID)
             DIAG_USER_IND_STRU->ulLength(�û�����Ϣ�ĳ���)
             DIAG_USER_IND_STRU->pData(�û�����Ϣ)

 History         :
    1.w00182550      2012-11-20  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 DIAG_UserPlaneReport(DIAG_USER_IND_STRU *pstUser)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_USERPLANE_IND_STRU stRptInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;
    VOS_ULONG    ulLockLevel;

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_ERR, ERR_MSP_NO_INITILIZATION, 0, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    if((NULL == pstUser)||((0 == pstUser->ulLength) && (NULL == pstUser->pData)))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_ERR, ERR_MSP_INVALID_PARAMETER, 0, 2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    VOS_SpinLockIntLock(&g_DiagLogPktNum.ulUserLock, ulLockLevel);
    stRptInfo.ulNo          = (g_DiagLogPktNum.ulUserNum)++;
    VOS_SpinUnlockIntUnlock(&g_DiagLogPktNum.ulUserLock, ulLockLevel);
    
    stRptInfo.ulId          = pstUser->ulMsgId;
    stRptInfo.ulModule      = pstUser->ulPid;

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = DIAG_MSG_TYPE_PS;
    stDiagHead.u.stID.mode4b    = DIAG_GET_MODE_ID(pstUser->ulModule);
    stDiagHead.u.stID.sec5b     = DIAG_MSG_PS_USER;
    stDiagHead.u.stID.cmdid19b  = 0;
    stDiagHead.ulSsid           = DIAG_SSID_CPU;
    stDiagHead.ulModemId        = DIAG_GET_MODEM_ID(pstUser->ulModule);
    stDiagHead.ulDirection      = DIAG_MT_IND;
    stDiagHead.ulMsgTransId     = g_ulTransId++;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

    stDiagHead.ulHeaderSize     = sizeof(DIAG_CMD_LOG_USERPLANE_IND_STRU);
    stDiagHead.pHeaderData      = &stRptInfo;

    stDiagHead.ulDataSize       = pstUser->ulLength;
    stDiagHead.pData            = pstUser->pData;

    ret = diag_ServicePackData(&stDiagHead);

    if(ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_ERR, ret, 0, 3);
    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_CBT_API_USER_OK, 0, 0, 4);
    }

    return ret;
}


/* ΪMBB�ṩ��errorlog���ܣ�Ӧ�ƶ�MBB��phone��ͨ */
VOS_UINT32 DIAG_ErrorLog(VOS_CHAR * cFileName,VOS_UINT32 ulFileId, VOS_UINT32 ulLine,
                VOS_UINT32 ulErrNo, VOS_VOID * pBuf, VOS_UINT32 ulLen)
{
    return 0;
}


/*****************************************************************************
 Function Name   : diag_SendMsg
 Description     : DIAG��ģ�鷢��Ϣ��װ�ӿ�
 Input           :VOS_UINT32 ulSenderId
                VOS_UINT32 ulRecverId
                VOS_UINT32 ulMsgId
                VOS_VOID* pDta
                VOS_UINT32 dtaSize
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-11-20  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_SendMsg(VOS_UINT32 ulSenderId, VOS_UINT32 ulRecverId, VOS_UINT32 ulMsgId, VOS_UINT8* pDta, VOS_UINT32 dtaSize)
{
    VOS_UINT32 ret = ERR_MSP_UNKNOWN;
    DIAG_DATA_MSG_STRU* pDataMsg = NULL;

    pDataMsg = (DIAG_DATA_MSG_STRU*)VOS_AllocMsg(ulSenderId,(sizeof(DIAG_DATA_MSG_STRU)+ dtaSize - VOS_MSG_HEAD_LENGTH));

    if (pDataMsg != NULL)
    {
        pDataMsg->ulReceiverPid = ulRecverId;
        pDataMsg->ulSenderPid   = ulSenderId;
        pDataMsg->ulLength      = sizeof(DIAG_DATA_MSG_STRU)+ dtaSize - 20;

        pDataMsg->ulMsgId    = ulMsgId;
        pDataMsg->ulLen      = dtaSize;
        if(0 != dtaSize)
        {
            VOS_MemCpy(pDataMsg->pContext,pDta,dtaSize);
        }

        ret = VOS_SendMsg(ulSenderId, pDataMsg);
        if (ret != VOS_OK)
        {
			diag_printf("diag_SendMsg ulSenderId=%d,ulRecverId=%d,ulMsgId=0x%x,pDta=%p,dtaSize=%d!\n",ulSenderId,ulRecverId,ulMsgId,pDta,dtaSize);
        }
        else
        {
            ret = ERR_MSP_SUCCESS;
        }
    }

    return ret;
}


VOS_UINT32 Diag_GetLogLevel(VOS_UINT32 ulPid)
{
    VOS_UINT8 level;

    /*�ж�ģ��ID�Ƿ���CCPU֧�ֵ�PS��Χ��*/
    if ((VOS_PID_DOPRAEND <= ulPid) && (VOS_PID_BUTT > ulPid))
    {
        level = g_PrintModuleCfg[ulPid - VOS_PID_DOPRAEND];

        /* level�д洢��ֵ(0|ERROR|WARNING|NORMAL|INFO|0|0|0) bit 6-3 �ֱ��ʾERROR-INFO */

        if(level & 0x08)
        {
            return PS_LOG_LEVEL_INFO;
        }
        else if(level & 0x10)
        {
            return PS_LOG_LEVEL_NORMAL;
        }
        else if(level & 0x20)
        {
            return PS_LOG_LEVEL_WARNING;
        }
        else if(level & 0x40)
        {
            return PS_LOG_LEVEL_ERROR;
        }
        else
        {
            return PS_LOG_LEVEL_OFF;
        }
    }

    return PS_LOG_LEVEL_OFF;
}



/*****************************************************************************
 Function Name   : diag_FailedCmdCnf
 Description     : MSP����ʧ�ܵ��������Ӧ����
 Input           : pData     ����������������
                   ulErrcode �����߷��صĴ�����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2016-02-15  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_FailedCmdCnf(DIAG_FRAME_INFO_STRU *pData, VOS_UINT32 ulErrcode)
{
    DIAG_COMM_CNF_STRU stCnfCmd   = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    DIAG_MSG_COMMON_PROC(stDiagInfo, stCnfCmd, pData);

    stDiagInfo.ulMsgType = pData->stID.pri4b;

    stCnfCmd.ulRet = ulErrcode;

    return DIAG_MsgReport(&stDiagInfo, &stCnfCmd, sizeof(stCnfCmd));
}




