


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include "diag_common.h"
#include "diag_cfg.h"
#include "diag_msgmsp.h"
#include "diag_msgphy.h"
#include "SCMProc.h"
#include "diag_api.h"
#include "diag_debug.h"
#include "msp_errno.h"
#include "LPsNvInterface.h"
#include "mdrv.h"
#include "msp_nv_id.h"
#include "soc_socp_adapter.h"
/*lint -restore*/



/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_CFG_C
/*lint -restore*/


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define DIAG_CFG_PRINT_MODULE_NUM              (44)

/*lint -save -e40*/

VOS_UINT32 g_ulDiagCfgInfo = 0;

VOS_UINT8 g_ALayerSrcModuleCfg[VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND] = {0};
VOS_UINT8 g_CLayerSrcModuleCfg[VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND] = {0};

VOS_UINT8 g_ALayerDstModuleCfg[VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND] = {0};
VOS_UINT8 g_CLayerDstModuleCfg[VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND] = {0};

VOS_UINT8 g_EventModuleCfg[DIAG_CFG_PID_NUM] = {0};

VOS_UINT8 g_PrintModuleCfg[DIAG_CFG_PID_NUM] = {0};
VOS_UINT32 g_PrintTotalCfg = DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE;
DIAG_CFG_LOG_CAT_CFG_STRU g_stMsgCfg = {0};

VOS_UINT32 g_ulDiagDfsCtrl = 0;
/*lint -restore*/

HTIMER          g_DebugTimer;

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : diag_CfgResetAllSwt
 Description     : ���ÿ���״̬
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-1  Draft Enact

*****************************************************************************/
VOS_VOID diag_CfgResetAllSwt(VOS_VOID)
{
    /*��տտڿ��ص�״̬�����1����ΪDIAG��ʼ��״̬������*/
    g_ulDiagCfgInfo = 0x1;

    /*��ղ�俪��״̬*/
    (VOS_VOID)VOS_MemSet(g_ALayerSrcModuleCfg,0,sizeof(g_ALayerSrcModuleCfg));
    (VOS_VOID)VOS_MemSet(g_CLayerSrcModuleCfg,0,sizeof(g_CLayerSrcModuleCfg));
    (VOS_VOID)VOS_MemSet(g_ALayerDstModuleCfg,0,sizeof(g_ALayerDstModuleCfg));
    (VOS_VOID)VOS_MemSet(g_CLayerDstModuleCfg,0,sizeof(g_CLayerDstModuleCfg));

    /* Ϊ����ԭTL�����EVENT���ػ��ƣ�Ĭ�ϰ�����EVENT�ӿ��ض�����Ϊ�� */
    (VOS_VOID)VOS_MemSet(g_EventModuleCfg,0x1,sizeof(g_EventModuleCfg));

    /*��մ�ӡ����״̬*/
    (VOS_VOID)VOS_MemSet(g_PrintModuleCfg,0,sizeof(g_PrintModuleCfg));

    /*��մ�ӡ�ܿ���״̬*/
	g_PrintTotalCfg = DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE;

    /*�����Ϣ���˿���״̬*/
    (VOS_VOID)VOS_MemSet(&g_stMsgCfg,0,sizeof(DIAG_CFG_LOG_CAT_CFG_STRU));

    return;
}

/*****************************************************************************
 Function Name   : diag_CfgSetGlobalBitValue
 Description     : ����DIAG�տڵȿ���״̬
 Input           :VOS_UINT32* pstDiagGlobal
                ENUM_DIAG_CFG_BIT enBit
                VOS_UINT32 enSwtich
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-1  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_CfgSetGlobalBitValue(VOS_UINT32* pstDiagGlobal,ENUM_DIAG_CFG_BIT_U32 enBit,ENUM_DIAG_CFG_SWT_U8 enSwtich)
{
    /*����Ϊopen 1ʱ����Ҫʹ��|�����ø�bit Ϊ1*/
    if(DIAG_CFG_SWT_OPEN == enSwtich)
    {
        *pstDiagGlobal |=  ((VOS_UINT)1 << enBit);
    }
    /*����Ϊclose 0ʱ����Ҫʹ��&�����ø�bit Ϊ0*/
    else if(DIAG_CFG_SWT_CLOSE == enSwtich)
    {
        /*lint -save -e502*/
        *pstDiagGlobal &= ~((VOS_UINT)1 << enBit);
        /*lint -restore*/
    }
    else
    {
        return ERR_MSP_INVALID_PARAMETER;
    }
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 Function Name   : diag_AirCfgProc
 Description     : �ú������ڴ���CfgProcEntry�������Ŀտڿ�������
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_AirCfgProc (VOS_UINT8* pstReq)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_LOG_CAT_AIR_REQ_STRU* pstAirSwtReq = NULL;
    DIAG_CMD_LOG_CAT_AIR_CNF_STRU stAirSwtCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    ENUM_DIAG_CFG_SWT_U8 enLSwitch = 0;
    ENUM_DIAG_CFG_SWT_U8 enGuSwitch = 0;

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstAirSwtReq = (DIAG_CMD_LOG_CAT_AIR_REQ_STRU*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    /*����LT�տڿ���ֵ*/
    enLSwitch = DIAG_GET_CFG_SWT(pstAirSwtReq->ulSwitch);
    enGuSwitch = DIAG_GET_CFG_SWT(pstAirSwtReq->ulGuSwitch);

    ret = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_LT_AIR_BIT,enLSwitch);
    if(ret)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    /* TODO: ��ɾ�� ����GU�տڿ���ֵ */
    ret = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_GU_AIR_BIT,enGuSwitch);
    if(ret)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stAirSwtCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stAirSwtCnf.ulRc = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stAirSwtCnf, sizeof(stAirSwtCnf));

    return ret;
}

/*lint -save -e830 -e539*/

/*****************************************************************************
 Function Name   : diag_CfgSetLayerSwt
 Description     : ���ò����Ϣ����
 Input           :DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq
                VOS_UINT32 ulCfgCnt
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-11-29  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_CfgSetLayerSwt(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq, VOS_UINT32 ulCfgSize)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 j = 0;
    VOS_UINT32 ulOffset = 0;
    ENUM_DIAG_CFG_SWT_U8 enSwitch = 0;

    if((0 == ulCfgSize)||(0 !=ulCfgSize %sizeof(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU)))
    {
        return  ERR_MSP_INVALID_PARAMETER;
    }

    /* ����ĳCategory�Ŀ����������б����Ҷ�Ӧ���������������*/
    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU);j++)
    {
        enSwitch = DIAG_GET_CFG_SWT((pstLayerReq + j)->ulSwitch);

        if(DIAG_CFG_LAYER_MODULE_IS_ACORE((pstLayerReq + j)->ulModuleId))
        {
            ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET((pstLayerReq + j)->ulModuleId);
            
            if( DIAG_CMD_LAYER_MOD_SRC == (pstLayerReq + j)->ulIsDestModule)
            {
                g_ALayerSrcModuleCfg[ulOffset] = (VOS_UINT8)enSwitch;
            }
            else
            {
                g_ALayerDstModuleCfg[ulOffset] = (VOS_UINT8)enSwitch;
            }
        }
        else if(DIAG_CFG_LAYER_MODULE_IS_CCORE((pstLayerReq + j)->ulModuleId ))
        {
            ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET((pstLayerReq + j)->ulModuleId);
            
            if( DIAG_CMD_LAYER_MOD_SRC == (pstLayerReq + j)->ulIsDestModule)
            {
                g_CLayerSrcModuleCfg[ulOffset] = (VOS_UINT8)enSwitch;
            }
            else
            {
                g_CLayerDstModuleCfg[ulOffset] = (VOS_UINT8)enSwitch;
            }
        }
    }

	return ret;
}

/*lint -restore*/

/*****************************************************************************
 Function Name   : diag_LayerCfgProc
 Description     : �ú������ڴ���CfgProcEntry�������Ĳ�俪������
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_LayerCfgProc (VOS_UINT8* pstReq)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerSwtReq = NULL;
    DIAG_CMD_LOG_CAT_LAYER_CNF_STRU stLayerSwtCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstLayerSwtReq = (DIAG_CMD_LOG_CAT_LAYER_REQ_STRU*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    /*���ò��ģ�鿪�ص�ȫ�ֱ�����*/
    ret = diag_CfgSetLayerSwt(pstLayerSwtReq, pstDiagHead->ulMsgLen - sizeof(MSP_DIAG_DATA_REQ_STRU));
    if(ret)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stLayerSwtCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stLayerSwtCnf.ulRc = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stLayerSwtCnf, sizeof(stLayerSwtCnf));

    return ret;
}


/*****************************************************************************
 Function Name   : diag_EventCfgProc
 Description     : �ú������ڴ���CfgProcEntry���������¼���������
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_EventCfgProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_LOG_CAT_EVENT_REQ_STRU* pstEvtSwtReq = NULL;
    DIAG_CMD_LOG_CAT_EVENT_CNF_STRU stEvtSwtCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 i, pid;
    ENUM_DIAG_CFG_SWT_U8 enSwitch =0;

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)pstReq;

    pstEvtSwtReq = (DIAG_CMD_LOG_CAT_EVENT_REQ_STRU*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    enSwitch = (ENUM_DIAG_CFG_SWT_U8)pstEvtSwtReq->ulSwt;

    /* �򿪺͹رն������ù̶���ģ�飬ֻ���ܿ����Ǵ�ʱ�����õ���ģ�� */
    if(enSwitch)
    {
        for(i = 0; i < pstEvtSwtReq->ulCount; i++)
        {
            pid = DIAG_EVENT_MODID(pstEvtSwtReq->aulModuleId[i]);
            if(DIAG_CFG_MODULE_IS_INVALID(pid))
            {
                continue;
            }
            
            g_EventModuleCfg[pid - VOS_PID_DOPRAEND] = DIAG_EVENT_SWT(pstEvtSwtReq->aulModuleId[i]);
        }
    }
    
    ret = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo, DIAG_CFG_EVENT_BIT, enSwitch);
    if(ret)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stEvtSwtCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stEvtSwtCnf.ulRc = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stEvtSwtCnf, sizeof(stEvtSwtCnf));

    return ret;
}

/*****************************************************************************
 Function Name   : diag_SetMsgCfgSwt
 Description     : ��ϢID���˿�������
 Input           :DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq
                VOS_UINT32 ulCfgSize
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_CfgSetMsgSwt(DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq,VOS_UINT32 ulCfgSize)
{
    /*lint -save -e958*/
    VOS_UINT32 i = 0,j = 0;
    ENUM_DIAG_CFG_SWT_U8 enSwitch =0;
    VOS_UINT32 ulRst = ERR_MSP_INVALID_PARAMETER;
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU *pstItemCfg =NULL;
    /*lint -restore*/
    /*�������*/
    if((0 == ulCfgSize)||(0 !=ulCfgSize % sizeof(DIAG_CMD_LOG_CAT_CFG_REQ_STRU)))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG_ERR, ulCfgSize, 0, 0);
        return ERR_MSP_DIAG_CMD_SIZE_INVALID;
    }

    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_CFG_REQ_STRU);j++)
    {

        /*��֧�ֲ����ϢCATEGORY����*/
        if(DIAG_CMD_LOG_CATETORY_LAYER_ID != (pstCatCfgReq + j)->ulCategory)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG_ERR, (pstCatCfgReq + j)->ulCategory, 0, 1);
            return ERR_MSP_NOT_SUPPORT;
        }
    }


    /* ����ĳCategory�Ŀ����������б����Ҷ�Ӧ���������������*/   /* [false alarm]:����Fortify */
    /* coverity[unreachable] */
    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_CFG_REQ_STRU);j++)
    {
        enSwitch = DIAG_GET_CFG_SWT((pstCatCfgReq + j)->ulSwitch);

        for(i = 0; i < g_stMsgCfg.ulCfgCnt; i++)
        {
            pstItemCfg = (g_stMsgCfg.astMsgCfgList + i);

            if((pstCatCfgReq + j)->ulId == pstItemCfg->ulId)
            {
                pstItemCfg->ulSwt = enSwitch;
                ulRst = ERR_MSP_SUCCESS;
                break;
            }
        }
        if(i >= g_stMsgCfg.ulCfgCnt)
        {
            /*Ŀǰ��һ��֧��DIAG_CFG_CAT_CFG_NUM����Ϣ����*/
            if((g_stMsgCfg.ulCfgCnt < DIAG_CFG_CAT_CFG_NUM))
            {
                pstItemCfg = g_stMsgCfg.astMsgCfgList + g_stMsgCfg.ulCfgCnt;

                pstItemCfg->ulId  = (pstCatCfgReq + j)->ulId;
                pstItemCfg->ulSwt = enSwitch;

                g_stMsgCfg.ulCfgCnt++;
                ulRst = ERR_MSP_SUCCESS;
            }
            else
            {
                DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG_ERR, g_stMsgCfg.ulCfgCnt, 0, 3);
                return ERR_MSP_INVALID_PARAMETER;
            }
        }
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : diag_MsgCfgProc
 Description     : �ú������ڴ���CfgProcEntry����������Ϣ��������
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_MsgCfgProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_LOG_CAT_CFG_CNF_STRU stCatSwtCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_CMD_LOG_CAT_CFG_REQ_STRU* pstCatCfgReq = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstCatCfgReq = (DIAG_CMD_LOG_CAT_CFG_REQ_STRU*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    /*������Ϣ���˿��ص�ȫ�ֱ�����*/
    ret = diag_CfgSetMsgSwt(pstCatCfgReq, pstDiagHead->ulMsgLen - sizeof(MSP_DIAG_DATA_REQ_STRU));
    if(ret)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stCatSwtCnf, pstDiagHead);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_MSP;

    stCatSwtCnf.ulRc = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stCatSwtCnf, sizeof(stCatSwtCnf));

    return ret;

}


/*****************************************************************************
 Function Name   : diag_CfgSetPrintSwt
 Description     : ���ô�ӡ����״̬
 Input           :DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq
                VOS_UINT32 ulCfgCnt
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-6  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_CfgSetPrintSwt(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq, VOS_UINT32 ulCfgSize)
{
    /*lint -save -e958*/
    VOS_UINT32 j = 0;
    VOS_UINT8 ucLevelFilter = 0;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    /*lint -restore*/
    if ((0 == ulCfgSize)||(0 != ulCfgSize % sizeof(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU)))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(DIAG_CFG_PRINT_TOTAL_MODULE == pstPrintReq->ulModuleId)
    {
        /*����PRINTʱ������������ģ������*/
         (VOS_VOID)VOS_MemSet(g_PrintModuleCfg,0,sizeof(g_PrintModuleCfg));

        /*���ô�ӡ�ܿ���*/
        ucLevelFilter = DIAG_GET_PRINT_CFG_SWT(pstPrintReq->ulLevelFilter);
        g_PrintTotalCfg = ucLevelFilter;
    }
    else
    {
        /* ����PRINT�ܿ���0xFFģ��*/
        g_PrintTotalCfg = DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE;

        /* ����ĳCategory�Ŀ����������б����Ҷ�Ӧ���������������*/
        for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU);j++)
        {
              /*lint -save -e40 -e63*/
            if(DIAG_CFG_MODULE_IS_INVALID((VOS_INT32)((pstPrintReq + j)->ulModuleId )))
            {
                /* TODO:����¼ */
                //ret = ERR_MSP_INVALID_PARAMETER;
                continue;
            }

            ucLevelFilter = DIAG_GET_PRINT_CFG_SWT((pstPrintReq +j)->ulLevelFilter);

            g_PrintModuleCfg[(pstPrintReq +j)->ulModuleId - VOS_PID_DOPRAEND] = ucLevelFilter;
            /*lint -restore*/
        }
    }
    /*lint -save -e539*/
	return ret;
    /*lint -restore */

}


/*****************************************************************************
 Function Name   : diag_PrintCfgProc
 Description     : �ú������ڴ���CfgProcEntry�������Ĵ�ӡ��������
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_PrintCfgProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintSwtReq = NULL;
    DIAG_CMD_LOG_CAT_PRINT_CNF_STRU stPrintSwtCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstPrintSwtReq = (DIAG_CMD_LOG_CAT_PRINT_REQ_STRU*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    /*���ô�ӡ���ص�ȫ�ֱ�����*/
    ret = diag_CfgSetPrintSwt(pstPrintSwtReq, pstDiagHead->ulMsgLen - sizeof(MSP_DIAG_DATA_REQ_STRU));
    if(ret)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stPrintSwtCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stPrintSwtCnf.ulRc = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stPrintSwtCnf, sizeof(stPrintSwtCnf));

    return ret;
}

/*****************************************************************************
 Function Name   : diag_FwSetChanSta
 Description     : ��C�˷�������״̬����USB�γ������ʹ�õ�
 Input           : VOS_UINT32 flag
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-15  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_SetChanDisconn(MsgBlock* pMsgBlock)
{
    if(!DIAG_IS_CONN_ON)
    {
        return 0;
    }
    else
    {
        diag_CfgResetAllSwt();
        
        mdrv_om_set_hsoflag(0);

        /*��״̬���͸�C��*/
        diag_SendMsg(MSP_PID_DIAG_APP_AGENT,MSP_PID_DIAG_AGENT,ID_MSG_DIAG_HSO_DISCONN_IND, VOS_NULL, 0);
        diag_AgentVoteToSocp(SOCP_VOTE_FOR_SLEEP);
    }

    return 0;

}




/*****************************************************************************
 Function Name   : diag_DisConnProc
 Description     : �ú������ڴ���ConnProcEntry��������HSO�Ͽ�����
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_DisConnProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_HOST_DISCONNECT_CNF_STRU stCnfDisConn = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead;

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    diag_PTR(EN_DIAG_PTR_MSGMSP_DISCONN_IN);

    pstDiagHead = (DIAG_FRAME_INFO_STRU *)pstReq;

    /*�������п���״̬Ϊδ��*/
    diag_CfgResetAllSwt();

    /* ɾ����ʱ�� */
    (VOS_VOID)VOS_StopRelTimer(&g_DebugTimer);

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);

    /* ��SOCPģ����Զ���Ƶ */
    mdrv_socp_enalbe_dfs();

    /*����Ͷ˯��Ʊ��agent��Ͷ*/
    diag_AgentVoteToSocp(SOCP_VOTE_FOR_SLEEP);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stCnfDisConn, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stCnfDisConn.ulRc   = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stCnfDisConn, sizeof(stCnfDisConn));

    diag_AgentVoteToSocp(SOCP_VOTE_FOR_SLEEP);

    diag_printf("diag disconnect failed.\n");

    return ret;
}


/*****************************************************************************
 Function Name   : diag_GetFrameTime
 Description     : ��ȡʱ���
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-19  Draft Enact

*****************************************************************************/
VOS_UINT64 diag_GetFrameTime(VOS_VOID)
{
    VOS_UINT32 ultimelow = 0;
    VOS_UINT32 ultimehigh= 0;
    VOS_UINT64 ulFrameCount = 0;
    VOS_INT32 ret;

    ret = mdrv_timer_get_accuracy_timestamp(&ultimehigh, &ultimelow);
    if(ERR_MSP_SUCCESS != ret)
    {
       ulFrameCount = 0;
    }
    else
    {
        ulFrameCount = ((VOS_UINT64)ultimehigh << 32) | ((VOS_UINT64)ultimelow);
    }
    return ulFrameCount;
}

/*****************************************************************************
 Function Name   : diag_GetTimeStampInitValue
 Description     : �ú�������hidis��ȡ������TL��Gu��ʱ�����ʼֵ����
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

    2.c64416         2014-11-18  �����µ���ϼܹ�
*****************************************************************************/
VOS_UINT32 diag_GetTimeStampInitValue(VOS_UINT8* pstReq)
{
    VOS_UINT ret = ERR_MSP_SUCCESS;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_TIMESTAMP_CNF_STRU timestampCnf = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    DIAG_MSG_COMMON_PROC(stDiagInfo, timestampCnf, pstDiagHead);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_MSP;

    timestampCnf.ulGuTimeStampInitValue = mdrv_timer_get_normal_timestamp();
    timestampCnf.ulTLTimeStampInitValue = diag_GetFrameTime();
    timestampCnf.ulErrcode              = ret;

    /*�����FW�ظ�*/
    ret = DIAG_MsgReport(&stDiagInfo, &timestampCnf, sizeof(timestampCnf));

    return (VOS_UINT32)ret;
}


#define DIAG_NV_IMEI_LEN                             15
/*****************************************************************************
 Function Name   : diag_GetImei
 Description     : ��ȡimei��
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-12-19  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetImei(VOS_CHAR szimei [ 16 ])
{
    VOS_UINT32  ret;
    VOS_UINT32  uslen = 0;
    VOS_UINT32  subscript = 0;
    VOS_CHAR   checkdata = 0;
    VOS_CHAR   auctemp[DIAG_NV_IMEI_LEN+1] = {0};

    uslen = DIAG_NV_IMEI_LEN+1;

    ret = NV_Read(0, auctemp, uslen);

    if(ret != 0)
    {
        return ret;
    }
    else
    {
        for (subscript = 0; subscript < (DIAG_NV_IMEI_LEN - 1); subscript += 2)
        {
            checkdata += (VOS_CHAR)(((auctemp[subscript])
                           +((auctemp[subscript + 1] * 2) / 10))
                           +((auctemp[subscript + 1] * 2) % 10));
        }
        checkdata = (10 - (checkdata%10)) % 10;

        for (subscript = 0; subscript < uslen; subscript++)
        {
            *(szimei + subscript) = *(auctemp + subscript) + 0x30; /*�ַ�ת��*/
        }

        szimei[DIAG_NV_IMEI_LEN - 1] = checkdata + 0x30;
        szimei[DIAG_NV_IMEI_LEN] = 0;
    }

    return 0;
}


/*****************************************************************************
 Function Name   : diag_GetModemInfo
 Description     : ��ȡmodem��Ϣ(���ڹ���δ����ʱ�����ߺ�̨��ѯ������Ϣ)
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2016-02-15  Draft Enact

*****************************************************************************/
VOS_VOID diag_GetModemInfo(DIAG_FRAME_INFO_STRU *pstDiagHead)
{
    VOS_UINT32 ulCnfRst                     = ERR_MSP_UNAVAILABLE;
    DIAG_CMD_HOST_CONNECT_CNF_STRU stCnf    = {0};
    const MODEM_VER_INFO_S* pstVerInfo      = VOS_NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo       = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead    = {0};
    
    /*������*/
    stCnf.ulAuid = ((MSP_DIAG_DATA_REQ_STRU*)(pstDiagHead->aucData))->ulAuid;
    stCnf.ulSn   = ((MSP_DIAG_DATA_REQ_STRU*)(pstDiagHead->aucData))->ulSn;

    (VOS_VOID)VOS_MemSet(&(stCnf.stBuildVersion), 0, sizeof(DIAG_CMD_UE_BUILD_VER_STRU));

    /*��ȡ�汾��Ϣ*/
    pstVerInfo = mdrv_ver_get_info();
	if(pstVerInfo!=NULL)
	{
        stCnf.stBuildVersion.usVVerNo        = pstVerInfo->stswverinfo.ulVVerNO;
        stCnf.stBuildVersion.usRVerNo        = pstVerInfo->stswverinfo.ulRVerNO;
        stCnf.stBuildVersion.usCVerNo        = pstVerInfo->stswverinfo.ulCVerNO;
        stCnf.stBuildVersion.usBVerNo        = pstVerInfo->stswverinfo.ulBVerNO;
        stCnf.stBuildVersion.usSpcNo         = pstVerInfo->stswverinfo.ulSpcNO;
        stCnf.stBuildVersion.usHardwareVerNo = pstVerInfo->stswverinfo.ulCustomNOv;
        stCnf.stBuildVersion.ulProductNo     = pstVerInfo->stswverinfo.ulProductNo;

        /*��ȡ���ɻ���ַ*/
        stCnf.ulChipBaseAddr = (VOS_UINT32)pstVerInfo->stproductinfo.echiptype;
	}

    /*��ȡIMEI��*/
    (VOS_VOID)diag_GetImei(stCnf.szImei);

    /*��ȡ����汾��*/
    (VOS_VOID)VOS_MemSet(&stCnf.stUeSoftVersion,0,sizeof(DIAG_CMD_UE_SOFT_VERSION_STRU));

    /*·����Ϣ��ȡ*/
    (VOS_VOID)NV_Read(EN_NV_ID_AGENT_FLAG,&(stCnf.stAgentFlag),sizeof(NV_ITEM_AGENT_FLAG_STRU));

    stCnf.diag_cfg.UintValue = 0;

    /* 010: OMͨ���ںϵİ汾 */
    /* 110: OM�ں�GUδ�ںϵİ汾 */
    /* 100: OM��ȫ�ںϵİ汾 */
    stCnf.diag_cfg.CtrlFlag.ulDrxControlFlag    = 0; /*��HIDSȷ�ϴ˴�����ʹ��,��׮������*/
    stCnf.diag_cfg.CtrlFlag.ulPortFlag          = 0;
    stCnf.diag_cfg.CtrlFlag.ulOmUnifyFlag       = 1;
    
	stCnf.ulLpdMode                             = 0x5a5a5a5a;
    stCnf.ulRc                                  = ERR_MSP_SUCCESS;

    (VOS_VOID)VOS_MemCpy(stCnf.szProduct, PRODUCT_FULL_VERSION_STR, sizeof(PRODUCT_FULL_VERSION_STR));

    DIAG_MSG_COMMON_PROC(stDiagInfo, stCnf, pstDiagHead);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_MSP;

    stDiagHead.u.stID.pri4b     = (stDiagInfo.ulMsgType & 0xf);
    stDiagHead.u.stID.mode4b    = (stDiagInfo.ulMode & 0xf);
    stDiagHead.u.stID.sec5b     = (stDiagInfo.ulSubType & 0x1f);
    stDiagHead.u.stID.cmdid19b  = (stDiagInfo.ulMsgId & 0x7ffff);
    stDiagHead.ulSsid           = stDiagInfo.ulSSId;
    stDiagHead.ulModemId        = stDiagInfo.ulModemid;
    stDiagHead.ulDirection      = stDiagInfo.ulDirection;
    stDiagHead.ulMsgTransId     = stDiagInfo.ulTransId;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_CNF;
    stDiagHead.ulDataSize       = sizeof(stCnf);
    stDiagHead.pData            = &stCnf;

    ulCnfRst = diag_ServicePackData(&stDiagHead);

    if(ERR_MSP_SUCCESS != ulCnfRst)
    {
        diag_printf("diag_GetModemInfo failed.\n");
    }

    return;
}


/*****************************************************************************
 Function Name   : diag_ConnProc
 Description     : �ú������ڴ���ConnProcEntry��������HSO��������
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_ConnProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret;
    VOS_UINT32 ulCnfRst = ERR_MSP_UNAVAILABLE;
    DIAG_MSG_MSP_CONN_STRU *pstConn;
    DIAG_CMD_HOST_CONNECT_CNF_STRU stCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    const MODEM_VER_INFO_S* pstVerInfo = VOS_NULL;
    DIAG_CMD_REPLAY_SET_REQ_STRU stReplay={0};
    DIAG_FRAME_INFO_STRU *pstDiagHead;
    DIAG_CMD_GET_MDM_INFO_REQ_STRU *pstInfo = VOS_NULL;

    diag_PTR(EN_DIAG_PTR_MSGMSP_CONN_IN);

    pstDiagHead = (DIAG_FRAME_INFO_STRU *)pstReq;

    /* ������ȡmodem��Ϣ���������ڹ��߲�ѯ������Ϣ */
    if(sizeof(DIAG_CMD_GET_MDM_INFO_REQ_STRU) == pstDiagHead->ulMsgLen)
    {
        pstInfo = (DIAG_CMD_GET_MDM_INFO_REQ_STRU *)pstDiagHead->aucData;
        if((VOS_NULL != pstInfo) && (DIAG_GET_MODEM_INFO == pstInfo->ulInfo))
        {
            diag_GetModemInfo(pstDiagHead);
            
            return ERR_MSP_SUCCESS;
        }
    }

    pstConn = (DIAG_MSG_MSP_CONN_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, (sizeof(DIAG_MSG_MSP_CONN_STRU)-VOS_MSG_HEAD_LENGTH));
    if(VOS_NULL == pstConn)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    /*��������״̬����ֵ*/
    ulCnfRst = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_CONN_BIT,DIAG_CFG_SWT_OPEN);
    if(ulCnfRst)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }
    
    /* �ر�SOCPģ����Զ���Ƶ */
    mdrv_socp_disalbe_dfs();

    (VOS_VOID)VOS_MemSet(&(pstConn->stConnInfo.stBuildVersion), 0, sizeof(DIAG_CMD_UE_BUILD_VER_STRU));

    /*��ȡ�汾��Ϣ*/
    pstVerInfo = mdrv_ver_get_info();
	if(pstVerInfo!=NULL)
	{
        pstConn->stConnInfo.stBuildVersion.usVVerNo        = pstVerInfo->stswverinfo.ulVVerNO;
        pstConn->stConnInfo.stBuildVersion.usRVerNo        = pstVerInfo->stswverinfo.ulRVerNO;
        pstConn->stConnInfo.stBuildVersion.usCVerNo        = pstVerInfo->stswverinfo.ulCVerNO;
        pstConn->stConnInfo.stBuildVersion.usBVerNo        = pstVerInfo->stswverinfo.ulBVerNO;
        pstConn->stConnInfo.stBuildVersion.usSpcNo         = pstVerInfo->stswverinfo.ulSpcNO;
        pstConn->stConnInfo.stBuildVersion.usHardwareVerNo = pstVerInfo->stswverinfo.ulCustomNOv;
        pstConn->stConnInfo.stBuildVersion.ulProductNo     = pstVerInfo->stswverinfo.ulProductNo;

        /*��ȡ���ɻ���ַ*/
        pstConn->stConnInfo.ulChipBaseAddr = (VOS_UINT32)pstVerInfo->stproductinfo.echiptype;
	}

    /*��ȡIMEI��*/
    (VOS_VOID)diag_GetImei(pstConn->stConnInfo.szImei);

    /*��ȡ����汾��*/
    (VOS_VOID)VOS_MemSet(&pstConn->stConnInfo.stUeSoftVersion,0,sizeof(DIAG_CMD_UE_SOFT_VERSION_STRU));

    /*·����Ϣ��ȡ*/
    (VOS_VOID)NV_Read(EN_NV_ID_AGENT_FLAG,&(pstConn->stConnInfo.stAgentFlag),sizeof(NV_ITEM_AGENT_FLAG_STRU));

    pstConn->stConnInfo.diag_cfg.UintValue = 0;

    /* 010: OMͨ���ںϵİ汾 */
    /* 110: OM�ں�GUδ�ںϵİ汾 */
    /* 100: OM��ȫ�ںϵİ汾 */
    pstConn->stConnInfo.diag_cfg.CtrlFlag.ulDrxControlFlag = 0; /*��HIDSȷ�ϴ˴�����ʹ��,��׮������*/
    pstConn->stConnInfo.diag_cfg.CtrlFlag.ulPortFlag = 0;
    pstConn->stConnInfo.diag_cfg.CtrlFlag.ulOmUnifyFlag = 1;
    
	pstConn->stConnInfo.ulLpdMode = 0x5a5a5a5a;

    (VOS_VOID)VOS_MemCpy(pstConn->stConnInfo.szProduct, PRODUCT_FULL_VERSION_STR, sizeof(PRODUCT_FULL_VERSION_STR));

	ulCnfRst = diag_SendMsg(MSP_PID_DIAG_APP_AGENT,PS_PID_MM,ID_MSG_DIAG_CMD_REPLAY_TO_PS,(VOS_UINT8*)&stReplay,\
					sizeof(DIAG_CMD_REPLAY_SET_REQ_STRU));
    if(ulCnfRst)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    /*������*/
    pstConn->stConnInfo.ulAuid = ((MSP_DIAG_DATA_REQ_STRU*)(pstDiagHead->aucData))->ulAuid;
    pstConn->stConnInfo.ulSn   = ((MSP_DIAG_DATA_REQ_STRU*)(pstDiagHead->aucData))->ulSn;
    pstConn->stConnInfo.ulRc   = ERR_MSP_SUCCESS;

    pstConn->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstConn->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstConn->ulCmdId       = pstDiagHead->ulCmdId;
    pstConn->ulMsgId       = DIAG_MSG_MSP_CONN_REQ;

    diag_AgentVoteToSocp(SOCP_VOTE_FOR_WAKE);

    ulCnfRst = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstConn);
    if(ulCnfRst)
    {
        goto DIAG_ERROR;/*lint !e801*/
    }

    /* ������ʱ���ϱ���ά�ɲ���Ϣ�����߶�λ�������� */
    ret = VOS_StartRelTimer(&g_DebugTimer, MSP_PID_DIAG_APP_AGENT, DIAG_DEBUG_TIMER_LEN, DIAG_DEBUG_TIMER_NAME, \
                            DIAG_DEBUG_TIMER_PARA, VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if(ret != ERR_MSP_SUCCESS)
    {
        diag_printf("VOS_StartRelTimer fail [%s]\n", __FUNCTION__);
    }
 

    return ulCnfRst;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stCnf.ulRc   = ERR_HIDS_CORE_ERROR;

    ulCnfRst = DIAG_MsgReport(&stDiagInfo, &stCnf, sizeof(stCnf));

    diag_printf("diag connect failed.\n");

    return ulCnfRst;
}





