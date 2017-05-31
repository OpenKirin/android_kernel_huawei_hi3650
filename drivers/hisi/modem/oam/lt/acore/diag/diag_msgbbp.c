/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */




#include <product_config.h>
#include <mdrv.h>
#include <diag_mem.h>
#include "diag_msgbbp.h"
#include "diag_debug.h"
#include "msp_diag_comm.h"
#include "soc_socp_adapter.h"

#include "diag_acore_common.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGBBP_C


DIAG_TRANS_HEADER_STRU g_stBbpTransHead = {{VOS_NULL, VOS_NULL}, 0};
DIAG_BBP_DS_ADDR_INFO_STRU g_stBbpDsAddrInfo={DIAG_BBP_DS_ENABLE,DDR_SOCP_SIZE,DDR_SOCP_ADDR};


DIAG_BBP_PROC_FUN_STRU g_DiagBbpFunc[] = {
    {diag_DrxSampleGetChnSizeProc        ,DIAG_CMD_DRX_SAMPLE_CHNSIZE_REQ       ,0},
};




/*****************************************************************************
 Function Name	 : diag_DrxSampleGetChnSizeProc
 Description	 : �͹������ɻ�ȡͨ����С
 Input			 :VOS_UINT8* pstReq
				VOS_UINT32 ulCmdSn
 Output 		 : None
 Return 		 : VOS_UINT32

 History		 :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetChnSizeProc(DIAG_FRAME_INFO_STRU *pData)
{
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BBP_DS_ADDR_INFO_STRU  *psDrxDsInfo = NULL;
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU stCnfDrxSample = {0};

    VOS_UINT32 ulLen;
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;

    /*AP�ڷ��͸�CP����ʱ����Ҫ�����ɵ�ַ�ռ���Ϣһ���͹�ȥ*/
    ulLen = sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen+sizeof(DIAG_BBP_DS_ADDR_INFO_STRU);
    
    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid  = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid    = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId        = DIAG_MSG_BBP_A_TRANS_C_REQ;
    
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pData, ulLen);
    
    psDrxDsInfo = (DIAG_BBP_DS_ADDR_INFO_STRU*)((VOS_UINT8*)pstInfo+sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)+pData->ulMsgLen);
    psDrxDsInfo->ulAddr     = g_stBbpDsAddrInfo.ulAddr;
    psDrxDsInfo->ulSize     = g_stBbpDsAddrInfo.ulSize;
    psDrxDsInfo->ulenable   = g_stBbpDsAddrInfo.ulenable;

    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;
DIAG_ERROR:

	stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU));

    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_BbpMsgProc
 Description     : MSP bbp������Ϣ������
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_BbpMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER ;
    DIAG_CMD_DRX_SAMPLE_COMM_CNF_STRU stCnfDrxSample;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    VOS_UINT32 i = 0;
    VOS_UINT32 ulLen;
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;
    if(DIAG_MSG_TYPE_BBP != pData->stID.pri4b)
    {
        diag_printf("%s Rcv Error Msg Id 0x%x\n",__FUNCTION__,pData->ulCmdId);
        return ulRet;
    }

    for(i = 0; i< sizeof(g_DiagBbpFunc)/sizeof(g_DiagBbpFunc[0]);i++)
    {
        if(g_DiagBbpFunc[i].ulCmdId == pData->ulCmdId)
        {
            g_DiagBbpFunc[i].ulReserve ++;
            ulRet = g_DiagBbpFunc[i].pFunc(pData);
            return ulRet;
        }
    }


    /* GU��BBP�������͸��������� */
    if((DIAG_MODE_GSM == pData->stID.mode4b) || (DIAG_MODE_UMTS == pData->stID.mode4b))
    {
        return diag_TransReqProcEntry(pData, &g_stBbpTransHead);
    }

    /*AP�ڷ��͸�CP����ʱ����Ҫ�����ɵ�ַ�ռ���Ϣһ���͹�ȥ*/
    ulLen = sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen;
    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_BBP_A_TRANS_C_REQ;
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pData, ulLen);

    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;

DIAG_ERROR:

    stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU));

    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_BbpMsgInit
 Description     : MSP bbp���ֳ�ʼ��
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_BbpMsgInit(VOS_VOID)
{

    VOS_UINT32 ulRet;

    /* �����ڵ㱣���ź���, Diag Trans Bbp */
    ulRet = VOS_SmBCreate("DTB", 1, VOS_SEMA4_FIFO,&g_stBbpTransHead.TransSem);
    if(VOS_OK != ulRet)
    {
        diag_printf("diag_BbpMsgInit VOS_SmBCreate failed.\n");
    }

    /* ��ʼ���������� */
    blist_head_init(&g_stBbpTransHead.TransHead);

    /*ע��message��Ϣ�ص�*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_BBP,diag_BbpMsgProc);
    return;
}
/*lint -save -e102 -e10 -e2 -e40 -e533 -e31 -e830 -e522 -e718 -e746 -e702 -e565   -e64 -e23 -e63 -e26 -e578 -e132*/
extern unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);
/*****************************************************************************
* �� �� ��  : socp_logbuffer_sizeparse
*
* ��������  : �ڴ������׶ν�CMD LINE�е�BUFFER��С������������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
static int __init diag_BbpDrxDdrEnable(char *pucChar)
{
    u32      flag;

    flag = (u32)simple_strtoul(pucChar, NULL, 0);
    if(flag)
    {
        g_stBbpDsAddrInfo.ulenable  = DIAG_BBP_DS_ENABLE;
        g_stBbpDsAddrInfo.ulAddr    = DDR_SOCP_ADDR;
        g_stBbpDsAddrInfo.ulSize    = DDR_SOCP_SIZE;
        printk(KERN_ERR"[%s] enable!\n",__FUNCTION__);
        printk(KERN_ERR"base addr :0x%x,base size: 0x%x\n",DDR_SOCP_ADDR,DDR_SOCP_SIZE);
    }
    else
    {
        g_stBbpDsAddrInfo.ulenable  = 0;
        g_stBbpDsAddrInfo.ulAddr    = 0;
        g_stBbpDsAddrInfo.ulSize    = 0;
        printk(KERN_ERR"[%s] not enable!\n",__FUNCTION__);
    }
    return 0;
}

early_param("modem_socp_enable",diag_BbpDrxDdrEnable);
/*lint -restore*/




