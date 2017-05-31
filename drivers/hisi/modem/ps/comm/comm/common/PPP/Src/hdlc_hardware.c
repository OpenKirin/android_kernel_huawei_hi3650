/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/******************************************************************************
   ͷ�ļ�����
******************************************************************************/
#include "product_config.h"
#include "TTFComm.h"
#include "soc_sctrl_interface.h"

#if (VOS_RTOSCK == VOS_OS_VER)
#include "TTFMem.h"
#include "cttf_1x_rrlp_data_pif.h"
#include "ppp_trans_data_pif.h"
#include "rlp_ppp_pub_pif.h"
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "ppp_dbug.h"
#include "fwd_ppp.h"
#else
#include "PPP/Inc/ppp_public.h"
#endif

#include "mdrv.h"
#include "PPP/Inc/hdlc_hardware.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
/*lint -e732*/
/*lint -e40*/
/*lint -e718*/
/*lint -e746*/

/*****************************************************************************
   1 Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_HARDWARE_C
/*lint +e767 */


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
extern VOS_UINT32  VHW_HDLC_Task( VOS_VOID );
extern VOS_UINT8   g_ucScCtrlRegAddr[0xFFC];
#endif


/*****************************************************************************
   3 ˽�ж���
*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsr(unsigned int ulPara);

VOS_UINT32 PPP_HDLC_HARD_FrmIsr(unsigned int ulPara);


#define  PPP_HDLC_MNTN_TRACE_PARA       (1)
#define  PPP_HDLC_MNTN_TRACE_REG        (2)
#define  PPP_HDLC_MNTN_TRACE_DATA       (4)

/*****************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/* ���װ����ķ�����֡��Ϣ */
HDLC_DEF_UNCOMPLETED_INFO_STRU  g_stUncompletedInfo = {0};

/* ������װʹ�õ��ڴ� */
HDLC_DEF_BUFF_INFO_STRU        *g_pstHdlcDefBufInfo = VOS_NULL_PTR;

/* �����װʹ�õ��ڴ� */
HDLC_FRM_BUFF_INFO_STRU        *g_pstHdlcFrmBufInfo = VOS_NULL_PTR;

/* HDLC���������Ϣ */
HDLC_CONFIG_INFO_STRU           g_stHdlcConfigInfo  =
{
    0,
    0,
    0,
    0,
    0,
    HDLC_DEF_INTERRUPT_LIMIT_DEFAULT,
    HDLC_FRM_INTERRUPT_LIMIT_DEFAULT,
    VOS_NULL_PTR,
    0
};

/* ͳ����Ϣ */
PPP_HDLC_HARD_DATA_PROC_STAT_ST g_PppHdlcHardStat   = {0};

/* ������ԭʼ�ж�ʱ��RAW_INT��STATUSֵ */
HDLC_REG_SAVE_INFO_STRU         g_stHdlcRegSaveInfo;

#define    HDLC_IP_BASE_ADDR    (g_stHdlcConfigInfo.ulHDLCIPBaseAddr)

/* ϵͳ����������ַ */
VOS_UINT_PTR    g_ulHdlcScCtrlBaseAddr  = 0;

VOS_UINT_PTR    g_ulPppVirtAddr         = 0;
VOS_UINT_PTR    g_ulPppPhyAddr          = 0;
VOS_UINT32      g_ulPppTotalBufLen      = 0;

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

#if (VOS_RTOSCK == VOS_OS_VER)

/* PPPC�����ݶ���ͳ����Ϣ�ṹ�� */
extern PPP_DATA_Q_STAT_STRU             g_stPppcDataQueueStats;

#ifdef PPPC_HDLC_ST_TEST
VOS_VOID   PPPC_STUB_ProcDlData(PPPC_DATA_LINK_NODE_STRU *pstMem);
VOS_UINT32 PPPC_STUB_ProcUlData(PPPC_DATA_LINK_NODE_STRU *pstData, VOS_UINT16 usDataLen);
#endif

/*****************************************************************************
 �� �� ��  : PPP_MemAlloc
 ��������  : �����㿽���ڴ�
 �������  : usLen      -- ���ݿ鳤��,��λΪ�ֽ�
 �������  : ��
 �� �� ֵ  : �㿽���ڴ�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-04-27
    ��    ��   : c00184031
    �޸�����   : Created
*****************************************************************************/
PPPC_DATA_LINK_NODE_STRU * PPP_MemAlloc
(
    VOS_UINT16                          usLen,
    TTF_MEM_POOL_ID_ENUM_UINT32         ulPoolId
)
{
    /* �ýӿ���������ʱ��Ҫ����MACͷ���ȣ�
      ������ADS�շ���ΪIP����Ϊ��NDIS��E5�������ݽṹͳһ����Ҫ����MACͷ��
      �㿽��ָ���C�˷��ص�ʱ��ͳһƫ�ƹ̶��ֽڣ��ҵ��㿽��ͷ����
    */
    /*
       ��������ʱ����������0��������USB�շ�����Ϊ�ֽ�����ʽ��PPP֡����MACͷ
    */
    PPPC_DATA_LINK_NODE_STRU           *pstNode = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstMem  = VOS_NULL_PTR;


    /* ����ڵ� */
    pstNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(PS_PID_PPP_HDLC, sizeof(PPPC_DATA_LINK_NODE_STRU));

    if (VOS_NULL_PTR != pstNode)
    {
        pstMem  = TTF_MemBlkAlloc(PS_PID_PPP_HDLC, ulPoolId, (VOS_UINT32)usLen);
        if (VOS_NULL_PTR != pstMem)
        {
            PPP_MemSet(pstNode, sizeof(PPPC_DATA_LINK_NODE_STRU), 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
            pstNode->pstPduMem    = pstMem;
            pstNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
            pstNode->ucPdnId      = 0;
            TTF_NodeInit(&(pstNode->stNode));

            if (TTF_MEM_POOL_ID_UL_DATA == ulPoolId)
            {
                /* �������������ܴ��� */
                g_stPppcDataQueueStats.ulMemAllocUplinkCnt++;
            }
            else
            {
                /* �������������ܴ��� */
                g_stPppcDataQueueStats.ulMemAllocDownlinkCnt++;
            }

            return pstNode;
        }
        else
        {
            PPP_HDLC_WARNING_LOG1("alloc ttf memory fail. allocMemlen:%d\n", usLen);
            TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstNode);
        }
    }
    else
    {
        PPP_HDLC_WARNING_LOG1("alloc node memory fail. allocMemlen:%d\n", sizeof(PPPC_DATA_LINK_NODE_STRU));
    }

    if (TTF_MEM_POOL_ID_UL_DATA == ulPoolId)
    {
        /* ������������ʧ�ܴ��� */
        g_stPppcDataQueueStats.ulMemAllocUplinkFailCnt++;
    }
    else
    {
        /* ������������ʧ�ܴ��� */
        g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt++;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : PPP_MemFree
 ��������  : �ͷ��㿽���ڴ�
 �������  : pstNode  --- TTF_MEM��ʽ������
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-04-027
    ��    ��   : c00184031
    �޸�����   : Created
*****************************************************************************/
VOS_VOID PPP_MemFree(PPPC_DATA_LINK_NODE_STRU *pstNode)
{
    if (VOS_NULL_PTR == pstNode)
    {
        return;
    }

    if (VOS_NULL_PTR != pstNode->pstPduMem)
    {
        TTF_MemFree(PS_PID_PPP_HDLC, pstNode->pstPduMem);
        pstNode->pstPduMem = VOS_NULL_PTR;
    }

    if (VOS_NULL_PTR != pstNode->pstUlDataInfo)
    {
        PS_MEM_FREE(PS_PID_PPP_HDLC, pstNode->pstUlDataInfo);
        pstNode->pstUlDataInfo  = VOS_NULL_PTR;
    }

    /* �ͷ��㿽���ڴ� */
    TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstNode);

    g_stPppcDataQueueStats.ulMemFreeCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_MemSingleCopy
 ��������  : ��ȡ�����ڴ浥Ԫʵ��ʹ�õ����ֽ�������������������
 �������  : pMemSrc  -- Ҫ��ȡ���ݵ�TTF�ڴ��ͷָ��
 �������  : ��
 �� �� ֵ  : ���ݳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_VOID PPP_MemSingleCopy(VOS_UINT8 *pucDest, VOS_UINT8 *pucSrc, VOS_UINT32 ulLen)
{
    /* ���޸�ΪEDMA���� */
    PS_MEM_CPY(pucDest, pucSrc, ulLen);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_PeriphClkOpen
 ��������  : ��HDLCʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��13��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_PeriphClkOpen(VOS_VOID)
{
    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_CRG_CLK_BITPOS);
    PPP_HDLC_WRITE_32REG(HDLC_CRG_CLKEN4_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_PeriphClkClose
 ��������  : �ر�HDLCʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��13��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_PeriphClkClose(VOS_VOID)
{
    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_CRG_CLK_BITPOS);
    PPP_HDLC_WRITE_32REG(HDLC_CRG_CLKENDIS4_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnSetConfig
 ��������  : ���ÿ�ά�ɲ�ȼ�
 �������  : ulConfig - ��ά�ɲ�ȼ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_MntnSetConfig(VOS_UINT32 ulConfig)
{
    g_stHdlcConfigInfo.ulHdlcMntnTraceCfg = ulConfig;

    return g_stHdlcConfigInfo.ulHdlcMntnTraceCfg;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnSetDefIntLimit
 ��������  : ���ý��װ�ж�ˮ��
 �������  : ulIntLimit - �ж�ˮ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_MntnSetDefIntLimit(VOS_UINT32 ulIntLimit)
{
    g_stHdlcConfigInfo.ulHdlcDefIntLimit = ulIntLimit;

    return g_stHdlcConfigInfo.ulHdlcDefIntLimit;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnSetFrmIntLimit
 ��������  : ���÷�װ�ж�ˮ��
 �������  : ulIntLimit - �ж�ˮ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_MntnSetFrmIntLimit(VOS_UINT32 ulIntLimit)
{
    g_stHdlcConfigInfo.ulHdlcFrmIntLimit = ulIntLimit;

    return g_stHdlcConfigInfo.ulHdlcFrmIntLimit;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnTraceMsg
 ��������  : ������������
 �������  : pstHead    - ��Ϣ�׵�ַ
             ulMsgname  - ��ϢID
             ulDataLen  - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnTraceMsg
(
    HDLC_MNTN_TRACE_HEAD_STRU          *pstHead,
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulMsgname,
    VOS_UINT32                          ulDataLen
)
{
    pstHead->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstHead->ulReceiverPid   = PS_PID_PPP_HDLC;
    pstHead->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstHead->ulSenderPid     = PS_PID_PPP_HDLC;
    pstHead->ulLength        = ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstHead->ulMsgname       = ulMsgname;

    PPP_MNTN_TRACE_MSG(pstHead);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnDefTraceRegConfig
 ��������  : ��ȡ���װ�Ĵ�����������
 �������  : ulEnable   -   ��װ���װʹ��ǰ����ʹ�ܺ�VOS_TRUE: ʹ�ܺ�,VOS_FALSE: ʹ��ǰ
             ulValue    -   ʹ�ܼĴ������õ�ֵ
             ulEnableInterrupt - �жϷ�ʽ������ѯ��ʽ������ʹ�ܺ�ȡ�Ĵ���ʱ��Ч
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceRegConfig
(
    VOS_UINT32      ulEnable,
    VOS_UINT32      ulValue,
    VOS_UINT32      ulEnableInterrupt
)
{
    HDLC_MNTN_DEF_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_DEF_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;
    VOS_UINT32                              ulDataLen;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_REG) != 0)
    {
        ulDataLen    = sizeof(HDLC_MNTN_DEF_REG_CONFIG_STRU);

        /* ����ȫ���Ĵ������� */
        pstRegConfig->ulStateSwRst             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulPriorTimeoutCtrl       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulRdErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulWrErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefEn              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefRawInt          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefIntStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefIntClr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefCfg             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedLen      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedPro      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompleteStAgo     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefGoOn            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefStatus          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletStNow      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInLliAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktLen            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktLenMax         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefOutSpcAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefOutSpaceDep         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefRptAddr             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefRptDep              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor0       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor1       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor2       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor3       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInfoFr1CntAgo       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInfoFr1CntNow       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

        /* ʹ��ǰ������ʹ�ܼĴ�����û�����ã���Ϊ����֮��HDLC�Ὺʼ��������ı������Ĵ�����ֵ */
        if( VOS_FALSE == ulEnable)
        {
            pstRegConfig->ulHdlcDefEn   = ulValue;
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_DEF_REG_BEFORE_EN, ulDataLen);
        }
        else
        {
            /* ʹ�ܺ󹴰�ʱ����������жϷ�ʽ����RawInt��Statusȡg_stHdlcRegSaveInfo�����ֵ */
            if( VOS_TRUE == ulEnableInterrupt )
            {
                pstRegConfig->ulHdlcDefRawInt   = g_stHdlcRegSaveInfo.ulHdlcDefRawInt;
                pstRegConfig->ulHdlcDefStatus   = g_stHdlcRegSaveInfo.ulHdlcDefStatus;
            }
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_DEF_REG_AFTER_EN, ulDataLen);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefCfgGoOnReg
 ��������  : ����HDLC��ͣ״̬������GO_ON�Ĵ�����Ӧ����λ
 �������  : ulDefStatus  -   ���װ״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefCfgGoOnReg
(
    VOS_UINT32          ulDefStatus
)
{
    /*
    hdlc_def_go_on  (0x84)
     31                  17  16  15    9   8  7   1  0
    |----------------------|----|-------|----|-----|----|
    |         Rsv          |Goon|  Rsv  |Goon| Rsv |Goon|
    Reserved             [31:17] 15'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_rpt_ful_goon     [16]    1'b0    h/s WO   �ⲿ���װ��Ч֡��Ϣ�ϱ��ռ������ͣ���
    Reserved             [15:9]  7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_outspc_ful_goon  [8]     1'b0    h/s WO   �ⲿ���װ������ݴ洢�ռ������ͣ״̬���
    Reserved             [7:1]   7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_lcp_goon         [0]     1'b0    h/s WO   ���һ���Ϸ�LCP֡���µ�Ӳ����ͣ״̬����������װģ��δ������һ������װ�����ݣ�<=2KB(def_in_pkt_len_max)�������һ���Ϸ�LCP֡�������ͣ��֡���ȴ��������˼Ĵ���д"1"���ټ�������ʣ������ݡ�
    */

    /* GO_ONǰ����ϴν��װ��ԭʼ�ж� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    if (HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL == ulDefStatus )
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x10000);
    }
    else if (HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL == ulDefStatus )
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x100);
    }
    else if (HDLC_DEF_STATUS_PAUSE_LCP == ulDefStatus )
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x1);
    }
    else
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_DefCfgGoOnReg, ERROR, Wrong ulDefStatus %d!\r\n", ulDefStatus);
    }

    /* PC��ʹ��HDLCģ���� */
#if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnDefTraceUncompleteInfo
 ��������  : ��ȡ���װ����ķ�����֡��Ϣ
 �������  : pstUncompletedInfo -   ������֡��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceUncompleteInfo
(
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo
)
{
    HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU stMntnUncompletedInfo;


    VOS_MemCpy_s(&stMntnUncompletedInfo.stUncompletedInfo, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU),
               pstUncompletedInfo, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU));

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)&stMntnUncompletedInfo,
                               ID_HDLC_MNTN_DEF_UNCOMPLETED_INFO,
                               sizeof(HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnShowFrmReg
 ��������  : ��ӡ��װ�Ĵ�����ǰ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��30��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowFrmReg(VOS_VOID)
{
    HDLC_MNTN_FRM_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_FRM_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;


    /* ����ȫ���Ĵ������� */
    pstRegConfig->ulStateSwRst          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulPriorTimeoutCtrl    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulRdErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulWrErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmEn           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmRawInt       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmIntStatus    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmIntClr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmCfg          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmAccm         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInLliAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInSublliAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInPktLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInBlkAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInBlkLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutLliAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutSpaceAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutSpaceDep      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmRptAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmRptDep           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));

    vos_printf("\n================HDLC Hardware ShowFrmReg Begin==========================\n");

    vos_printf("ulStateSwRst                    = 0x%x\n", pstRegConfig->ulStateSwRst);
    vos_printf("ulPriorTimeoutCtrl              = 0x%x\n", pstRegConfig->ulPriorTimeoutCtrl);
    vos_printf("ulRdErrCurrAddr                 = 0x%x\n", pstRegConfig->ulRdErrCurrAddr);
    vos_printf("ulWrErrCurrAddr                 = 0x%x\n", pstRegConfig->ulWrErrCurrAddr);
    vos_printf("ulHdlcFrmEn                     = 0x%x\n", pstRegConfig->ulHdlcFrmEn);
    vos_printf("ulHdlcFrmRawInt                 = 0x%x\n", pstRegConfig->ulHdlcFrmRawInt);
    vos_printf("ulHdlcFrmIntStatus              = 0x%x\n", pstRegConfig->ulHdlcFrmIntStatus);
    vos_printf("ulHdlcFrmIntClr                 = 0x%x\n", pstRegConfig->ulHdlcFrmIntClr);
    vos_printf("ulHdlcFrmCfg                    = 0x%x\n", pstRegConfig->ulHdlcFrmCfg);
    vos_printf("ulHdlcFrmAccm                   = 0x%x\n", pstRegConfig->ulHdlcFrmAccm);
    vos_printf("ulHdlcFrmStatus                 = 0x%x\n", pstRegConfig->ulHdlcFrmStatus);
    vos_printf("ulFrmInLliAddr                  = 0x%x\n", pstRegConfig->ulFrmInLliAddr);
    vos_printf("ulFrmInSublliAddr               = 0x%x\n", pstRegConfig->ulFrmInSublliAddr);
    vos_printf("ulFrmInPktLen                   = 0x%x\n", pstRegConfig->ulFrmInPktLen);
    vos_printf("ulFrmInBlkAddr                  = 0x%x\n", pstRegConfig->ulFrmInBlkAddr);
    vos_printf("ulFrmInBlkLen                   = 0x%x\n", pstRegConfig->ulFrmInBlkLen);
    vos_printf("ulFrmOutLliAddr                 = 0x%x\n", pstRegConfig->ulFrmOutLliAddr);
    vos_printf("ulFrmOutSpaceAddr               = 0x%x\n", pstRegConfig->ulFrmOutSpaceAddr);
    vos_printf("ulFrmOutSpaceDep                = 0x%x\n", pstRegConfig->ulFrmOutSpaceDep);
    vos_printf("ulFrmRptAddr                    = 0x%x\n", pstRegConfig->ulFrmRptAddr);
    vos_printf("ulFrmRptDep                     = 0x%x\n", pstRegConfig->ulFrmRptDep);

    vos_printf("\n================HDLC Hardware ShowFrmReg End==========================\n");

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnShowDefReg
 ��������  : ��ӡ���װ�Ĵ�����ǰ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��30��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowDefReg(VOS_VOID)
{
    HDLC_MNTN_DEF_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_DEF_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;


    /* ����ȫ���Ĵ������� */
    pstRegConfig->ulStateSwRst             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulPriorTimeoutCtrl       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulRdErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulWrErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefEn              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefRawInt          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefIntStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefIntClr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefCfg             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedLen      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedPro      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompleteStAgo     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefGoOn            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefStatus          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletStNow      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInLliAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktLen            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktLenMax         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefOutSpcAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefOutSpaceDep         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefRptAddr             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefRptDep              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor0       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor1       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor2       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor3       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInfoFr1CntAgo       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInfoFr1CntNow       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    vos_printf("\n================HDLC Hardware ShowDefReg Begin==========================\n");

    vos_printf("ulStateSwRst             = 0x%x\n", pstRegConfig->ulStateSwRst);
    vos_printf("ulPriorTimeoutCtrl       = 0x%x\n", pstRegConfig->ulPriorTimeoutCtrl);
    vos_printf("ulRdErrCurrAddr          = 0x%x\n", pstRegConfig->ulRdErrCurrAddr);
    vos_printf("ulWrErrCurrAddr          = 0x%x\n", pstRegConfig->ulWrErrCurrAddr);
    vos_printf("ulHdlcDefEn              = 0x%x\n", pstRegConfig->ulHdlcDefEn);
    vos_printf("ulHdlcDefRawInt          = 0x%x\n", pstRegConfig->ulHdlcDefRawInt);
    vos_printf("ulHdlcDefIntStatus       = 0x%x\n", pstRegConfig->ulHdlcDefIntStatus);
    vos_printf("ulHdlcDefIntClr          = 0x%x\n", pstRegConfig->ulHdlcDefIntClr);
    vos_printf("ulHdlcDefCfg             = 0x%x\n", pstRegConfig->ulHdlcDefCfg);
    vos_printf("ulDefUncompletedLen      = 0x%x\n", pstRegConfig->ulDefUncompletedLen);
    vos_printf("ulDefUncompletedPro      = 0x%x\n", pstRegConfig->ulDefUncompletedPro);
    vos_printf("ulDefUncompletedAddr     = 0x%x\n", pstRegConfig->ulDefUncompletedAddr);
    vos_printf("ulDefUncompleteStAgo     = 0x%x\n", pstRegConfig->ulDefUncompleteStAgo);
    vos_printf("ulHdlcDefGoOn            = 0x%x\n", pstRegConfig->ulHdlcDefGoOn);
    vos_printf("ulHdlcDefStatus          = 0x%x\n", pstRegConfig->ulHdlcDefStatus);
    vos_printf("ulDefUncompletStNow      = 0x%x\n", pstRegConfig->ulDefUncompletStNow);
    vos_printf("ulDefInLliAddr           = 0x%x\n", pstRegConfig->ulDefInLliAddr);
    vos_printf("ulDefInPktAddr           = 0x%x\n", pstRegConfig->ulDefInPktAddr);
    vos_printf("ulDefInPktLen            = 0x%x\n", pstRegConfig->ulDefInPktLen);
    vos_printf("ulDefInPktLenMax         = 0x%x\n", pstRegConfig->ulDefInPktLenMax);
    vos_printf("ulDefOutSpcAddr          = 0x%x\n", pstRegConfig->ulDefOutSpcAddr);
    vos_printf("ulDefOutSpaceDep         = 0x%x\n", pstRegConfig->ulDefOutSpaceDep);
    vos_printf("ulDefRptAddr             = 0x%x\n", pstRegConfig->ulDefRptAddr);
    vos_printf("ulDefRptDep              = 0x%x\n", pstRegConfig->ulDefRptDep);
    vos_printf("ulHdlcDefErrInfor0       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor0);
    vos_printf("ulHdlcDefErrInfor1       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor1);
    vos_printf("ulHdlcDefErrInfor2       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor2);
    vos_printf("ulHdlcDefErrInfor3       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor3);
    vos_printf("ulDefInfoFr1CntAgo       = 0x%x\n", pstRegConfig->ulDefInfoFr1CntAgo);
    vos_printf("ulDefInfoFr1CntNow       = 0x%x\n", pstRegConfig->ulDefInfoFr1CntNow);

    vos_printf("\n================HDLC Hardware ShowDefReg End==========================\n");

}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmProcException
 ��������  : �쳣����
 �������  : ulStatus           -   �쳣״̬
             ulEnableInterrupt  - �жϷ�ʽ������ѯ��ʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e{438,550}*/
VOS_VOID PPP_HDLC_HARD_FrmProcException
(
    VOS_UINT32          ulStatus,
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulRawInt;


    if( VOS_TRUE == ulEnableInterrupt )
    {
        /* �������жϷ�������н��������жϲ������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�ԭʼ�жϼĴ���ֵ */
        ulRawInt                        =   g_stHdlcRegSaveInfo.ulHdlcFrmRawInt;
        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_INTERRUPT_IND_BITPOS);
    }
    else
    {
        ulRawInt  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    }

    PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcException, ERROR, Exception ocurr status 0x%x RAW_INT 0x%x\r\n", ulStatus, ulRawInt);
    PPP_HDLC_HARD_MntnShowFrmReg();
    PPP_HDLC_HARD_MntnShowDefReg();

    g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_EXCEPTION_IND_BITPOS);

    /* ��λǰ��Delay 1s��֤��ά�ɲ�������� */
    VOS_TaskDelay(1000);

    /* ���HDLC�����쳣���򵥰��쳣���� */
    mdrv_om_system_error(HDLC_FRM_SYSTEM_ERROR_ID, __LINE__, (VOS_INT)g_PppHdlcHardStat.usFrmExpInfo,
                         (VOS_CHAR *)&g_stHdlcRegSaveInfo,
                         sizeof(HDLC_REG_SAVE_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnFrmTraceRegConfig
 ��������  : ��ȡ�Ĵ�����������
 �������  : ulEnable   -   ��װ���װʹ��ǰ����ʹ�ܺ�VOS_TRUE: ʹ�ܺ�,VOS_FALSE: ʹ��ǰ
             ulValue    -   ʹ�ܼĴ������õ�ֵ
             ulEnableInterrupt - �жϷ�ʽ������ѯ��ʽ������ʹ�ܺ�ȡ�Ĵ���ʱ��Ч
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnFrmTraceRegConfig
(
    VOS_UINT32      ulEnable,
    VOS_UINT32      ulValue,
    VOS_UINT32      ulEnableInterrupt
)
{
    HDLC_MNTN_FRM_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_FRM_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;
    VOS_UINT32                              ulDataLen;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_REG) != 0)
    {
        ulDataLen    = sizeof(HDLC_MNTN_FRM_REG_CONFIG_STRU);

        /* ����ȫ���Ĵ������� */
        pstRegConfig->ulStateSwRst          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulPriorTimeoutCtrl    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulRdErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulWrErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmEn           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmRawInt       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmIntStatus    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmIntClr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmCfg          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmAccm         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInLliAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInSublliAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInPktLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInBlkAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInBlkLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutLliAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutSpaceAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutSpaceDep      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmRptAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmRptDep           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));

        /* ʹ��ǰ������ʹ�ܼĴ�����û�����ã���Ϊ����֮��HDLC�Ὺʼ��������ı������Ĵ�����ֵ */
        if( VOS_FALSE == ulEnable )
        {
            pstRegConfig->ulHdlcFrmEn    = ulValue;
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_FRM_REG_BEFORE_EN, ulDataLen);
        }
        else
        {
            /* ʹ�ܺ󹴰�ʱ����������жϷ�ʽ����RawInt��Statusȡg_stHdlcRegSaveInfo�����ֵ */
            if( VOS_TRUE == ulEnableInterrupt )
            {
                pstRegConfig->ulHdlcFrmRawInt   = g_stHdlcRegSaveInfo.ulHdlcFrmRawInt;
                pstRegConfig->ulHdlcFrmStatus   = g_stHdlcRegSaveInfo.ulHdlcFrmStatus;
            }
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_FRM_REG_AFTER_EN, ulDataLen);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmCfgBufReg
 ��������  : ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ�
 �������  : ulTotalLen --����װ���ݰ����ܳ���
 �������  :
 �� �� ֵ  : VOS_TRUE   - �����ж�ģʽ
             VOS_FALSE  - ������ѯģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmCfgEnReg(VOS_UINT32   ulTotalLen)
{
    /*
    1.hdlc_frm_en   (0x10)
      31   25 24  23 18 17  16  15  14  13  12  11  10   9   8  7    1  0
    |--------|---|-----|---|---|---|---|---|---|---|---|---|---|------|---|
    |   Rsv  |en | Rsv |en |en |en |en |en |en |en |en |en |en |  Rsv |en |

    Reserved            [31:25] 7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_over_int_en     [24]    1'b0    h/s R/W  һ�������װ�����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    Reserved            [23:18] 6'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_rpt_dep_err_en  [17]    1'b0    h/s R/W  ��װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    frm_out_spc_err_en  [16]    1'b0    h/s R/W  ��װ�ⲿ����洢�ռ䲻���ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_rpt_prm_err_en  [15]    1'b0    h/s R/W  ��װ�ϱ��ռ���ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_out_prm_err_en  [14]    1'b0    h/s R/W  ��װ���������ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_in_prm_err_en   [13]    1'b0    h/s R/W  ��װ����������ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_cfg_err_en      [12]    1'b0    h/s R/W  ��װЭ�鼰��ѹ��ָʾ���ô����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_wr_timeout_en   [11]    1'b0    h/s R/W  ��װʱAXI����д����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_rd_timeout_en   [10]    1'b0    h/s R/W  ��װʱAXI���߶�����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_wr_err_en       [9]     1'b0    h/s R/W  ��װʱAXI����д���������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_rd_err_en       [8]     1'b0    h/s R/W  ��װʱAXI���߶����������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    Reserved            [7:1]   7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_en              [0]     1'b0    h/s R/W  һ�������װʹ�ܣ������frm_enд��1'b1������װ����;һ�������װ��ɺ���Ӳ���Զ���frm_en���㣻
                                                 ��װ���̳���ʱ��Ӳ��Ҳ���frm_en�Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
                                                 дʱ����һ�������װʹ��;0����ʹ�ܷ�װ����;1��ʹ�ܷ�װ����;
                                                 ��ʱ����һ�������װ����״̬;0��û�ڽ��з�װ����;1�����ڽ��з�װ����
    */

    VOS_UINT32          ulEnableInterrupt;
    VOS_UINT32          ulValue;
    const VOS_UINT32    ulInterruptValue    = 0x0103FF01;   /* ʹ���жϷ�ʽʱ����ʹ�ܼĴ�����ֵ */
    const VOS_UINT32    ulPollValue         = 0x01;         /* ʹ����ѯ��ʽʱ����ʹ�ܼĴ�����ֵ */


    /* �жϴ���װ���ݵ��ܳ��ȣ�������������ʹ���жϷ�ʽ������ʹ����ѯ��ʽ */
    if( ulTotalLen > HDLC_FRM_INTERRUPT_LIMIT )
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_frm_en��[31:0]λΪ0x0103FF01 */
        ulValue             = ulInterruptValue;
        ulEnableInterrupt   = VOS_TRUE;

        g_PppHdlcHardStat.ulFrmWaitIntCnt++;
    }
    else
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_frm_en��[31:0]λΪ0x01 */
        ulValue             = ulPollValue;
        ulEnableInterrupt   = VOS_FALSE;

        g_PppHdlcHardStat.ulFrmWaitQueryCnt++;
    }

    /* ʹ��ǰ����ϴη�װ�����װ��ԭʼ�ж� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnFrmTraceRegConfig(VOS_FALSE, ulValue, ulEnableInterrupt);

    /* ʹ��Ӳ��֮ǰ��ǿ��ARM˳��ִ�н���ǰ���ָ�� */
    TTF_FORCE_ARM_INSTUCTION();

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    /* PC��ʹ��HDLCģ���� */
#if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
#endif

    return ulEnableInterrupt;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmStartTimer
 ��������  : �����װĿ�Ŀռ�ʧ�ܿ�����ʱ��
 �������  : pstBuildPara   -   ������������Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmStartTimer
(
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara
)
{
    if( VOS_NULL_PTR != g_stHdlcConfigInfo.stHdlcFrmTimerHandle )
    {
        return;
    }

    if (VOS_OK != VOS_StartRelTimer(&g_stHdlcConfigInfo.stHdlcFrmTimerHandle, PS_PID_PPP_HDLC,
                     HDLC_FRM_TIME_INTERVAL,
                     pstBuildPara->usPppId,
                     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL,
                     VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_0))
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmStartTimer, Warning, start reltimer error\r\n");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefProcException
 ��������  : �쳣����
 �������  : ulStatus           -   �쳣״̬
             ulEnableInterrupt  - �жϷ�ʽ������ѯ��ʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e{438,550}*/
VOS_VOID PPP_HDLC_HARD_DefProcException
(
    VOS_UINT32          ulStatus,
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulRawInt;


    if( VOS_TRUE == ulEnableInterrupt )
    {
        /* �������жϷ�������н��������жϲ������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�ԭʼ�жϼĴ���ֵ */
        ulRawInt                        =   g_stHdlcRegSaveInfo.ulHdlcDefRawInt;
        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_INTERRUPT_IND_BITPOS);
    }
    else
    {
        ulRawInt  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    }

    PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_DefProcException, ERROR, Exception ocurr status 0x%x RAW_INT 0x%x\r\n", ulStatus, ulRawInt);
    PPP_HDLC_HARD_MntnShowFrmReg();
    PPP_HDLC_HARD_MntnShowDefReg();

    g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_EXCEPTION_IND_BITPOS);

    /* ���HDLC�����쳣���򵥰��쳣���� */
    mdrv_om_system_error(HDLC_DEF_SYSTEM_ERROR_ID, __LINE__, (VOS_INT)g_PppHdlcHardStat.usDefExpInfo,
                         (VOS_CHAR *)&g_stHdlcRegSaveInfo,
                         sizeof(HDLC_REG_SAVE_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_CommWaitSem
 ��������  : �ȴ���װ���װ��ͣ�����
 �������  : ulHdlcMasterSem  -
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_CommWaitSem
(
    VOS_UINT32          ulHdlcMasterSem,
    VOS_UINT32          ulSemTimeoutLen
)
{
    VOS_UINT32                          ulResult;

    /* �ȴ���װ����װ��� */
    ulResult = VOS_SmP(ulHdlcMasterSem, ulSemTimeoutLen);

    if (VOS_OK != ulResult)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_CommWaitSem, WARNING, VOS_SmP ulHdlcMasterSem 0x%x failed! ErrorNo = 0x%x\r\n",
                      ulHdlcMasterSem, ulResult);

        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_SEM_TIMEOUT_IND_BITPOS);
        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_SEM_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefIsr
 ��������  : HDLC���װ�ж����֪ͨ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsr(unsigned int ulPara)
{
    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* �յ�һ���жϺ����ԭʼ�ж� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* �ͷŷ�װ����ź��� */
    VOS_SmV(g_stHdlcConfigInfo.ulHdlcDefMasterSem);

    g_PppHdlcHardStat.ulDefIsrCnt++;


    /* drv�ṩ�Ľӿڲ����ķ���ֵ */
    return 1; /* IRQ_HANDLED; */
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmIsr
 ��������  : HDLC��װ�ж����֪ͨ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmIsr(unsigned int ulPara)
{
    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* �յ�һ���жϺ����ԭʼ�ж� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* �ͷŷ�װ����ź��� */
    VOS_SmV(g_stHdlcConfigInfo.ulHdlcFrmMasterSem);

    g_PppHdlcHardStat.ulFrmIsrCnt++;

    /* drv�ṩ�Ľӿڲ����ķ���ֵ */
    return 1; /* IRQ_HANDLED; */
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefWaitStatusChange
 ��������  : ��ѯ״̬�Ĵ���
 �������  : ��
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefWaitStatusChange(VOS_VOID)
{
    /*
    hdlc_def_status  (0x88)
      31 30   24 23   8 7 6  5   4   3   2  1  0
    |---|-------|------|---|---|---|---|---|----|
    |Rsv|  Type |  Num |Rsv|Idx|Ful|Ful|Now|Stat|
    Reserved             [31]    1'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_err_type         [30:24] 7'b0    h/s RO   ��֡�ϱ�ʱ������֡���ͣ���Ӧ��bitλΪ1���������������ʹ���
                                                  bit 30����������6��ת���ַ�0x7D�����һ��Flag��
                                                  bit 29����������5����AC����ѹ��ʱ��Address��ֵ��0xFF��
                                                  bit 28����������4����AC����ѹ��ʱ��Control��ֵ��0x03��
                                                  bit 27����������3����P�������ʱ���յ��Ƿ���Protocol��ֵ��
                                                  bit 26����������2�����װ��֡�ֽ���С��4bites��
                                                  bit 25����������1�����װ��֡�ֽ�������1502bytes��PPP֡��Information�򲻳���1500Bytes������Э���򲻳���1502Bytes����
                                                  bit 24����������0�� CRCУ�����
    def_valid_num        [23:8]  16'b0   h/s RO   ��֡�ϱ�ʱ����Ч֡��Ŀ�������������һ�����ܵķ�����֡��
    Reserved             [7:6]   2'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_error_index      [5]     1'b0    h/s RO   ���װ��������ָʾ
    def_rpt_ful          [4]     1'b0    h/s RO   ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ָͣʾ
    def_out_spc_ful      [3]     1'b0    h/s RO   ���װ�ⲿ����洢�ռ������ָͣʾ
    def_uncompleted_now  [2]     1'b0    h/s RO   ����ָʾ��ǰ�����Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����
    def_all_pkt_pro_stat [1:0]   2'b0    h/s RO   һ������������״̬��00��δ���һ������������01��δ���һ�������������ѽ��LCP֡��Ӳ��������ͣ״̬��
                                                  10�����һ����������������֡�ϱ���11: ���һ����������������֡�ϱ���
    */
    VOS_UINT32              ulRsltWaitNum;           /* ��ֹӲ���쳣�ı������� */
    volatile VOS_UINT32     ulStatus;                /* ���װ״̬ */

   /* ��ѯhdlc_frm_status (0x28)�ĵ�[0]λ�͵�[1]λ���κ�һ��Ϊ1���߳�ʱ�򷵻� */

    ulRsltWaitNum = 0UL;

    while (ulRsltWaitNum < HDLC_DEF_MAX_WAIT_RESULT_NUM)
    {
        /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)��0-1��3-5λ���κ�һλ��Ϊ1��ʾ���װģ����ͣ��ֹͣ */
        ulStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

        if (HDLC_DEF_STATUS_DOING != (ulStatus & HDLC_DEF_STATUS_MASK))
        {
            break;
        }

        ulRsltWaitNum++;
    }

    if ( HDLC_DEF_MAX_WAIT_RESULT_NUM <= ulRsltWaitNum )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefWaitStatusChange, WARNING, wait hdlc_def_status timeout %d status 0x%x!\r\n",
                      ulRsltWaitNum, ulStatus);

        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    g_PppHdlcHardStat.ulDefMaxQueryCnt = TTF_MAX(g_PppHdlcHardStat.ulDefMaxQueryCnt, ulRsltWaitNum);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmWaitStatusChange
 ��������  : ��ѯ״̬�Ĵ���
 �������  : ��
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmWaitStatusChange(VOS_VOID)
{
    VOS_UINT32              ulFrmRsltWaitNum;           /* ��ֹӲ���쳣�ı������� */
    volatile VOS_UINT32     ulFrmStatus;                /* ��װ״̬ */


   /* ��ѯhdlc_frm_status (0x28)�ĵ�[0]λ�͵�[1]λ���κ�һ��Ϊ1���߳�ʱ�򷵻� */
    ulFrmRsltWaitNum = 0UL;

    while (ulFrmRsltWaitNum < HDLC_FRM_MAX_WAIT_RESULT_NUM)
    {
        /* ��ȡ hdlc_frm_status��[0][1]λ */
        ulFrmStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));

        if (HDLC_FRM_ALL_PKT_DOING != (ulFrmStatus & HDLC_FRM_STATUS_MASK))
        {
            break;
        }

        ulFrmRsltWaitNum++;
    }

    if ( HDLC_FRM_MAX_WAIT_RESULT_NUM <= ulFrmRsltWaitNum )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmWaitStatusChange, WARNING, wait hdlc_frm_status timeout %d status 0x%x!\r\n",
                      ulFrmRsltWaitNum, ulFrmStatus);

        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    g_PppHdlcHardStat.ulFrmMaxQueryCnt = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxQueryCnt, ulFrmRsltWaitNum);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmWaitResult
 ��������  : �ȴ���װ��ͣ�����
 �������  : ulEnableInterrupt  -   �ж��Ƿ�ʹ��
 �������  : ��
 �� �� ֵ  : ��װ״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmWaitResult
(
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32              ulFrmStatus;        /* ��װ״̬ */
    VOS_UINT32              ulResult;


    if (VOS_TRUE == ulEnableInterrupt)
    {
        /* �ȴ��жϵõ���������״̬ */
        ulResult = PPP_HDLC_HARD_CommWaitSem(g_stHdlcConfigInfo.ulHdlcFrmMasterSem, HDLC_FRM_MASTER_INT_TIMER_LEN);

        /* �������жϷ�������н��������жϲ�������Statusָʾ�Ƿ�����bit��ԭʼ�жϼĴ���
           �������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�״ֵ̬ */
        ulFrmStatus = g_stHdlcRegSaveInfo.ulHdlcFrmStatus;
    }
    else
    {
        /* ��ѯ�õ��������� */
        ulResult = PPP_HDLC_HARD_FrmWaitStatusChange();

        /* ��ѯhdlc_frm_status (0x28)��ȡ��װ״̬�����䷵�� */
        ulFrmStatus  =  PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    }

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnFrmTraceRegConfig(VOS_TRUE, 0, ulEnableInterrupt);

    /* �Ȳ���˵��HDLC���ڹ��� */
    if (VOS_OK != ulResult)
    {
        return HDLC_FRM_ALL_PKT_DOING;
    }

    ulFrmStatus &=  HDLC_FRM_STATUS_MASK;

    return ulFrmStatus;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefWaitResult
 ��������  : �ȴ����װ��ͣ�����
 �������  : ulEnableInterrupt  -   �ж��Ƿ�ʹ��
 �������  : ���װ״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefWaitResult
(
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulStatus;                /* ���װ״̬ */
    VOS_UINT32                          ulResult;


    if (VOS_TRUE == ulEnableInterrupt)
    {
        /* �ȴ��жϵõ���ͣ�����״̬ */
        ulResult = PPP_HDLC_HARD_CommWaitSem(g_stHdlcConfigInfo.ulHdlcDefMasterSem, HDLC_DEF_MASTER_INT_TIMER_LEN);

        /* �������жϷ�������н��������жϲ�������Statusָʾ�Ƿ�����bit��ԭʼ
           �жϼĴ����������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�״ֵ̬ */
        ulStatus = g_stHdlcRegSaveInfo.ulHdlcDefStatus;

    }
    else
    {
        /* ��ѯ�õ���ͣ����� */
        ulResult = PPP_HDLC_HARD_DefWaitStatusChange();

        /* ��ѯhdlc_def_status (0x88)��ȡ���װ״̬�����䷵�� */
        ulStatus  =  PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    }

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnDefTraceRegConfig(VOS_TRUE, 0, ulEnableInterrupt);

    /* �Ȳ���˵��HDLC���ڹ��� */
    if (VOS_OK != ulResult)
    {
        return HDLC_DEF_STATUS_DOING;
    }

    ulStatus &=  HDLC_DEF_STATUS_MASK;

    return ulStatus;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefCfgEnReg
 ��������  : ���ݱ��ν��װ��������С������ʹ�úο���ʽ�ȴ�HDLC�Ľ��
 �������  : ulLinkTotalSize     -   ���ν��װ���������ڵ���������(��λ�ֽ�)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefCfgEnReg
(
    VOS_UINT32                      ulTotalLen
)
{
    /*
    hdlc_def_en   (0x60)
      31   25 24  23 19 18  17  16  15  14  13  12  11  10   9   8   7   1  0
    |--------|---|-----|---|---|---|---|---|---|---|---|---|---|---|------|---|
    |   Rsv  |en | Rsv |en |en |en |en |en |en |en |en |en |en |en |  Rsv |en |

    Reserved            [31:25] 7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_over_int_en     [24]    1'b0    h/s R/W  һ��������װ�����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    Reserved            [23:19] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_rpt_ful_en      [18]    1'b0    h/s R/W  ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    def_out_spc_ful_en  [17]    1'b0    h/s R/W  ���װ�ⲿ����洢�ռ������ͣ�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_lcp_int_en      [16]    1'b0    h/s R/W  ���װ�����ЧLCP֡��ͣ�ж��ϱ�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_rpt_prm_err_en  [15]    1'b0    h/s R/W  ���װ�ϱ��ռ���ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_out_prm_err_en  [14]    1'b0    h/s R/W  ���װ����ռ���ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_in_prm_err_en   [13]    1'b0    h/s R/W  ���װ����������ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_cfg_err_en      [12]    1'b0    h/s R/W  ���װЭ��ѹ��ָʾ���ô����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_wr_timeout_en   [11]    1'b0    h/s R/W  ���װʱAXI����д����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_rd_timeout _en  [10]    1'b0    h/s R/W  ���װʱAXI���߶�����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_wr_err_en       [9]     1'b0    h/s R/W  ���װʱAXI����д���������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_rd_err_en       [8]     1'b0    h/s R/W  ���װʱAXI���߶����������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    Reserved            [7:1]   7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_en              [0]     1'b0    h/s R/W  һ������������װʹ�ܣ������def_enд��1'b1�������װ������һ������������װ��ɺ���Ӳ���Զ���def_en���㣻
                                                 ���װ���̳���ʱ��Ӳ��Ҳ���def_en�Զ����㣬ʹ�ڲ�״̬������IDLE״̬�����üĴ������ؽ��װ����״̬��
                                                 дʱ����һ������������װʹ�ܣ�0����ʹ�ܽ��װ����1��ʹ�ܽ��װ����
                                                 ��ʱ����һ������������װ����״̬��0��û�ڽ��н��װ����1�����ڽ��н��װ����
    */
    VOS_UINT32          ulEnableInterrupt;
    VOS_UINT32          ulValue;
    const VOS_UINT32    ulInterruptValue    = 0x0107FF01;   /* ʹ���жϷ�ʽʱ����ʹ�ܼĴ�����ֵ */
    const VOS_UINT32    ulPollValue         = 0x01;         /* ʹ����ѯ��ʽʱ����ʹ�ܼĴ�����ֵ */


    if( ulTotalLen > HDLC_DEF_INTERRUPT_LIMIT )
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_def_en��[31:0]λΪ0x0107FF01 */
        ulValue             = ulInterruptValue;
        ulEnableInterrupt   = VOS_TRUE;

        g_PppHdlcHardStat.ulDefWaitIntCnt++;
    }
    else
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_frm_en��[31:0]λΪ0x01 */
        ulValue             = ulPollValue;
        ulEnableInterrupt   = VOS_FALSE;

        g_PppHdlcHardStat.ulDefWaitQueryCnt++;
    }

    /* ʹ��ǰ����ϴη�װ�����װ��ԭʼ�ж� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnDefTraceRegConfig(VOS_FALSE, ulValue, ulEnableInterrupt);

    /* ʹ��Ӳ��֮ǰ��ǿ��ARM˳��ִ�н���ǰ���ָ�� */
    TTF_FORCE_ARM_INSTUCTION();

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    /* PC��ʹ��HDLCģ���� */
#if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
#endif

    return ulEnableInterrupt;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_CommCfgReg
 ��������  : ����ͨ�üĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_CommCfgReg(VOS_VOID)
{
    /*
    prior_timeout_ctrl(0x04)
      31  24   23                16   15  9         8             7   2    1          0
    |--------|----------------------|-------|-------------------|-------|---------------|
    |   Rsv  | axireq_timeout_value |  Rsv  | axireq_timeout_en |  Rsv  |hdlc_prior_ctrl|

    Reserved             [31:24] 8'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    axireq_timeout_value [23:16] 8'b0   h/s R/W  �������AXI���߶�д����ʱ���ж�ֵ
    Reserved             [15:9]  2'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    axireq_timeout_en    [8]     1'b0   h/s R/W  �Ƿ�����Ӳ���ж�AXI���߶�д����ʱ����������ã�
                                                   0������
                                                   1����
    Reserved             [7:2]   1'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    hdlc_prior_ctrl      [1:0]   1'b0   h/s R/W  HDLC��װ�����װ���ȼ����üĴ�����
                                                    00��һ���ڹ����У���һ��Ҳ��ʹ������£��Ƚ��Ѵ��ڹ����е��Ǹ������꣬
                                                        ��˭�ȱ�ʹ�����Ƚ�˭�����ꣻ
                                                    01�����з�װ���ȼ��ߣ�
                                                    10�����н��װ���ȼ��ߣ�
                                                    11����Ч��
                                                    (HDLC�ڲ����Ʊ���ͣ�ߵļ�����ʼ�����������װ����ͣ����װ���������������
                                                    ���װ�Ϳ�ʼ��������������װ����ͣ�����װ�������ݰ���������󣬷�װ�Ϳ�ʼ����������)
    */

    VOS_UINT32                          ulValue = 0x0;


    /* ʹ��AXI����ʱ�жϣ�debugʱʹ�ã�����HDLC���ó�ʱʱ����̣�����������ģʽ�²����� */
/*    SET_BIT_TO_DWORD(ulValue, 8); */

    /* ����AXI����ʱʱ������ֵ��SoC�ṩ�����ұ�֤��ƽ̨���� */
    ulValue |= (HDLC_AXI_REQ_TIMEOUT_VALUE << 16);

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnShowConfigInfo
 ��������  : ��ӡ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowConfigInfo(VOS_VOID)
{
    /* ���IP�����Ϣ */
    PPP_HDLC_WARNING_LOG3("HDLC Hardware Info: g_ulHDLCIPBaseAddr 0x%x g_slHdlcISRDef %d g_slHdlcISRFrm %d\r\n",
                  HDLC_IP_BASE_ADDR, g_stHdlcConfigInfo.slHdlcISRDef, g_stHdlcConfigInfo.slHdlcISRFrm);
    PPP_HDLC_WARNING_LOG2("HDLC Hardware Info: g_ulHdlcDefMasterSem 0x%x g_ulHdlcFrmMasterSem 0x%x\r\n",
                  g_stHdlcConfigInfo.ulHdlcDefMasterSem, g_stHdlcConfigInfo.ulHdlcFrmMasterSem);

    /* ����ڴ������Ϣ */
    PPP_HDLC_WARNING_LOG2("HDLC Memory Info: g_pstHdlcDefBufInfo 0x%x TTF_HDLC_MASTER_DEF_BUF_LEN %d\r\n",
                  g_pstHdlcDefBufInfo, TTF_HDLC_MASTER_DEF_BUF_LEN);
    PPP_HDLC_WARNING_LOG2("HDLC Memory Info: g_pstHdlcFrmBufInfo 0x%x TTF_HDLC_MASTER_FRM_BUF_LEN %d\r\n",
                  g_pstHdlcFrmBufInfo, TTF_HDLC_MASTER_FRM_BUF_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnShowStatInfo
 ��������  : ��ӡͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowStatInfo(VOS_VOID)
{
    vos_printf("\n================HDLC Hardware STAT INFO Begin==========================\n");

    vos_printf("���װ����IP���Ͱ�����            = %d\n", g_PppHdlcHardStat.ulDefIpDataProcCnt);
    vos_printf("���װ����PPP���Ͱ�����           = %d\n", g_PppHdlcHardStat.ulDefPppDataProcCnt);
    vos_printf("���װ���������֡����            = %d\n", g_PppHdlcHardStat.ulDefUncompleteCnt);
    vos_printf("���װ�ȴ��жϴ���                = %d\n", g_PppHdlcHardStat.ulDefWaitIntCnt);
    vos_printf("���װ��ѯ����                    = %d\n", g_PppHdlcHardStat.ulDefWaitQueryCnt);
    vos_printf("���װ�жϴ���                    = %d\n", g_PppHdlcHardStat.ulDefIsrCnt);
    vos_printf("���װLCP֡��ͣ����               = %d\n", g_PppHdlcHardStat.ulDefLcpPauseCnt);
    vos_printf("���װ�ռ�����ͣ����              = %d\n", g_PppHdlcHardStat.ulDefFullPauseCnt);
    vos_printf("���װ�����������ݰ�����          = %d\n", g_PppHdlcHardStat.ulDefInputDiscardCnt);

    vos_printf("��װ����IP���Ͱ�����              = %d\n", g_PppHdlcHardStat.ulFrmIpDataProcCnt);
    vos_printf("��װ����PPP���Ͱ�����             = %d\n", g_PppHdlcHardStat.ulFrmPppDataProcCnt);
    vos_printf("��װ�ȴ��жϴ���                  = %d\n", g_PppHdlcHardStat.ulFrmWaitIntCnt);
    vos_printf("��װ��ѯ����                      = %d\n", g_PppHdlcHardStat.ulFrmWaitQueryCnt);
    vos_printf("��װ�жϴ���                      = %d\n", g_PppHdlcHardStat.ulFrmIsrCnt);
    vos_printf("��װ����Ŀ�Ŀռ��ڴ�ʧ�ܴ���      = %d\n", g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt);
    vos_printf("��װ�����һ��Ŀ�Ŀռ��ڴ�ʧ�ܴ���= %d\n", g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt);
    vos_printf("��װ�����������������            = %d\n", g_PppHdlcHardStat.ulFrmOutputLinkFullCnt);
    vos_printf("��װ�����������ݰ�����            = %d\n", g_PppHdlcHardStat.ulFrmInputDiscardCnt);

    vos_printf("���װ�����������ڵ���          = %d\n", g_PppHdlcHardStat.ulDefMaxInputCntOnce);
    vos_printf("���װ������������ܳ���          = %d\n", g_PppHdlcHardStat.ulDefMaxInputSizeOnce);
    vos_printf("���װ�����Ч֡������          = %d\n", g_PppHdlcHardStat.ulDefMaxValidCntOnce);
    vos_printf("���װ��ѯ������                = %d\n", g_PppHdlcHardStat.ulDefMaxQueryCnt);

    vos_printf("��װ�����������ڵ���            = %d\n", g_PppHdlcHardStat.ulFrmMaxInputCntOnce);
    vos_printf("��װ������������ܳ���            = %d\n", g_PppHdlcHardStat.ulFrmMaxInputSizeOnce);
    vos_printf("��װ���ʹ�����ڵ����          = %d\n", g_PppHdlcHardStat.ulFrmMaxOutputCntOnce);
    vos_printf("��װ���ʹ�����ڵ��ܳ���        = %d\n", g_PppHdlcHardStat.ulFrmMaxOutputCntOnce);
    vos_printf("��װ��ѯ������                  = %d\n", g_PppHdlcHardStat.ulFrmMaxQueryCnt);

    vos_printf("���δ������ڵ���                = %d\n", g_PppHdlcHardStat.ulMaxCntOnce);
    vos_printf("�����ܽڵ���                      = %d\n", g_PppHdlcHardStat.ulHdlcHardProcCnt);
    vos_printf("continue����                      = %d\n", g_PppHdlcHardStat.ulContinueCnt);
    vos_printf("usDefExpInfo��ʶ                  = %d\n", g_PppHdlcHardStat.usDefExpInfo);
    vos_printf("usFrmExpInfo��ʶ                  = %d\n", g_PppHdlcHardStat.usFrmExpInfo);

    vos_printf("���HDLC BUG���������ݴ���        = %d\n", g_PppHdlcHardStat.ulForbidHdlcBugNoCpy);
    vos_printf("���HDLC BUG�������ݴ���          = %d\n", g_PppHdlcHardStat.ulForbidHdlcBugCpy);


    vos_printf("================HDLC Hardware STAT INFO End==========================\n");

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnTraceSingleData
 ��������  : ��ȡ��������
 �������  : usDataLen   -   �������ݳ���
             pucDataAddr -   �����׵�ַ
             ulEventType -   ��������
             ulNodeIndex -   ����������������±�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnTraceSingleData
(
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDataAddr,
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulEventType,
    VOS_UINT32                          ulNodeIndex
)
{
    VOS_UINT32                          ulDataLen;
    HDLC_MNTN_NODE_DATA_STRU           *pstNodeData;
    VOS_UINT32                          ulAllocDataLen;


    ulAllocDataLen = TTF_MIN(usDataLen, HDLC_MNTN_ALLOC_MEM_MAX_SIZE);

    /* ��Ϣ���ȵ�����Ϣ�ṹ��С���������ݳ��� */
    ulDataLen   = ulAllocDataLen + sizeof(HDLC_MNTN_NODE_DATA_STRU);

    pstNodeData = (HDLC_MNTN_NODE_DATA_STRU *)PS_MEM_ALLOC(PS_PID_PPP_HDLC, ulDataLen);

    if (VOS_NULL_PTR == pstNodeData)
    {
        PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_MntnTraceSingleData, NORMAL, Alloc mem failed, ulEventType %d!\r\n",
                      ulEventType);
        return;
    }

    /* ���ڱ�ʶ����һ�����������еĵڼ���IP�� */
    pstNodeData->usNodeIndex = (VOS_UINT16)ulNodeIndex;
    pstNodeData->usLen       = usDataLen;

    PPP_MemSingleCopy((VOS_UINT8 *)(pstNodeData + 1), pucDataAddr, ulAllocDataLen);

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstNodeData,
                               ulEventType, ulDataLen);

    PS_MEM_FREE(PS_PID_PPP_HDLC, pstNodeData);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnTraceInputParaLink
 ��������  : ��ȡ���������������
 �������  : ulEventType        - ��������,
             ulLinkNodeCnt      - �������������,
             ulLinkTotalSize    - ���������ܳ���,
             pastLinkNodeBuf    - ������������׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnTraceInputParaLink
(
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulEventType,
    VOS_UINT32                          ulLinkNodeCnt,
    VOS_UINT32                          ulLinkTotalSize,
    HDLC_PARA_LINK_NODE_STRU           *pastLinkNodeBuf
)
{
    HDLC_MNTN_INPUT_PARA_LINK_STRU      stInputPara;
    HDLC_MNTN_INPUT_PARA_LINK_STRU     *pstInputPara = &stInputPara;
    VOS_UINT32                          ulDataLen;


    ulDataLen = sizeof(HDLC_MNTN_INPUT_PARA_LINK_STRU);

    /* ��¼���ϱ������������нڵ����Ϣ*/
    pstInputPara->ulInputLinkNodeCnt   = ulLinkNodeCnt;
    pstInputPara->ulInputLinkTotalSize = ulLinkTotalSize;

    /* ��������ÿ���ڵ������ */
    VOS_MemCpy_s((VOS_UINT8 *)(&pstInputPara->astInputParaLinkNodeBuf[0]),
                ulLinkNodeCnt * sizeof(HDLC_PARA_LINK_NODE_STRU),
               (VOS_UINT8 *)(pastLinkNodeBuf),
               ulLinkNodeCnt * sizeof(HDLC_PARA_LINK_NODE_STRU));

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstInputPara,
                               ulEventType, ulDataLen);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefIsEnabled
 ��������  : ��ѯ��ǰ���װģ���Ƿ�ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��ʹ��
             VOS_FALSE - δʹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsEnabled(VOS_VOID)
{
    VOS_UINT32                          ulValue;


    /* SoC���ڴ�����һ�����������ʱ���Զ���ʹ��λ���� */
    ulValue = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));

    if (0x01 == (ulValue & 0x01))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmIsEnabled
 ��������  : ��ѯ��ǰ��װģ���Ƿ�ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��ʹ��
             VOS_FALSE - δʹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmIsEnabled(VOS_VOID)
{
    VOS_UINT32                          ulValue;


    /* SoC���ڴ�����һ�����������ʱ���Զ���ʹ��λ���� */
    ulValue = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));

    if (0x01 == (ulValue & 0x01))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_SetUp
 ��������  : ��ʼ����·PPP���ӣ�����շ�����֡��Ϣ
 �������  : usPppId - PPP ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_SetUp(PPP_ID usPppId)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU      *pstUncompletedInfo;


    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    VOS_MemSet_s(pstUncompletedInfo, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU),
                 0, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_Disable
 ��������  : ��HDLC����ȥʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_Disable(VOS_VOID)
{
    /* ���޲�������ΪHDLC�Ż���һ�������װ����װ���ʱ����Ӳ���Զ���frm_en��def_en���㣻
       ��װ����װ���̳���ʱ��Ӳ��Ҳ���Զ����㣬ʹ�ڲ�״̬������IDLE״̬��*/
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_Init
 ��������  : ��HDLC���г�ʼ��: HDLC���÷����쳣ʱ, ���쳣�ж��ϱ��Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID)
{
    VOS_UINT_PTR                          ulBaseAddr;

    /* ��ȡHDLC����ַ */
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_HDLC);

    HDLC_IP_BASE_ADDR       = (VOS_UINT_PTR)PPP_IO_ADDRESS(ulBaseAddr);

    if (VOS_NULL_PTR == HDLC_IP_BASE_ADDR)
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init HDLC base addr is null,0x%x\r\n",
                      ulBaseAddr);
        return VOS_ERR;
    }

#if (VOS_OS_VER == VOS_WIN32)
    g_ulHdlcScCtrlBaseAddr  = g_ucScCtrlRegAddr;
#else

#if ((SC_CTRL_MOD_P532 == SC_CTRL_MOD) || (SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6932_SFT == SC_CTRL_MOD))
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL_PD);
#elif (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD)
    /* =========dallas��ʹ��: HDLC�Ĵ�������ַλ��======== */
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL_MDM);
#else
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL);
#endif

    g_ulHdlcScCtrlBaseAddr  = (VOS_UINT_PTR)PPP_IO_ADDRESS(ulBaseAddr);

#endif
    if (VOS_NULL_PTR == g_ulHdlcScCtrlBaseAddr)
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init HDLC SCCTRL base addr is null,0x%x\r\n",
                      ulBaseAddr);
        return VOS_ERR;
    }

    /* �ر�HDLCʱ�� */
    PPP_HDLC_HARD_PeriphClkClose();

    /*��ȡHDLC���װ�жϺ�*/
    g_stHdlcConfigInfo.slHdlcISRDef   = mdrv_int_get_num(BSP_INT_TYPE_HDLC_DEF);

    /*��ȡHDLC��װ�жϺ�*/
    g_stHdlcConfigInfo.slHdlcISRFrm   = mdrv_int_get_num(BSP_INT_TYPE_HDLC_FRM);

    /* ��ʼ���ڴ� */
    if (VOS_OK != PPP_HDLC_HARD_InitBuf())
    {
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmBCreate("HdlcDefMasterSem", 0, VOS_SEMA4_FIFO, (VOS_SEM *)&g_stHdlcConfigInfo.ulHdlcDefMasterSem) )
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_Init, ERROR, Create g_ulHdlcDefMasterSem failed!\r\n");
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmBCreate("HdlcFrmMasterSem", 0, VOS_SEMA4_FIFO, (VOS_SEM *)&g_stHdlcConfigInfo.ulHdlcFrmMasterSem) )
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_Init, ERROR, Create g_ulHdlcFrmMasterSem failed!\r\n");
        return VOS_ERR;
    }

    /* �жϹҽ� */
    if (VOS_OK != mdrv_int_connect(g_stHdlcConfigInfo.slHdlcISRDef, (VOIDFUNCPTR)PPP_HDLC_HARD_DefIsr, 0))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Connect slHdlcISRDef %d to PPP_HDLC_HARD_DefIsr failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRDef);
        return VOS_ERR;
    }

    /* �ж�ʹ�� */
    if (VOS_OK != mdrv_int_enable(g_stHdlcConfigInfo.slHdlcISRDef))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Enable slHdlcISRDef %d failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRDef);
        return VOS_ERR;
    }

    /* �жϹҽ� */
    if (VOS_OK != mdrv_int_connect(g_stHdlcConfigInfo.slHdlcISRFrm, (VOIDFUNCPTR)PPP_HDLC_HARD_FrmIsr, 0))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Connect slHdlcISRFrm %d to PPP_HDLC_HARD_FrmIsr failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRFrm);
        return VOS_ERR;
    }

    if (VOS_OK != mdrv_int_enable(g_stHdlcConfigInfo.slHdlcISRFrm))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Enable slHdlcISRFrm %d failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRFrm);
        return VOS_ERR;
    }

    return VOS_OK;
}    /* link_HDLCInit */

/*****************************************************************************
 �� �� ��  : PPP_Help
 ��������  : ������ӡ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��25��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_Help(VOS_VOID)
{
    vos_printf("********************PPP�����Ϣ************************\n");
    vos_printf("PPP_HDLC_HARD_MntnShowStatInfo      ��ӡͳ����Ϣ\n");
    vos_printf("PPP_INPUT_ShowStatInfo              ��ӡ g_PppDataQCtrl��Ϣ\n");
    vos_printf("PPP_HDLC_HARD_MntnSetConfig         ���ÿ�ά�ɲ�ȼ�:\n");
    vos_printf("                                    1--������2--�Ĵ�����4--����\n");
    vos_printf("PPP_HDLC_HARD_MntnShowDefReg        ��ӡ���װ�Ĵ�����Ϣ\n");
    vos_printf("PPP_HDLC_HARD_MntnShowFrmReg        ��ӡ��װ�Ĵ�����Ϣ\n");
    vos_printf("PPP_HDLC_HARD_MntnSetDefIntLimit    ���ý��װ�ж�ˮ��\n");
    vos_printf("PPP_HDLC_HARD_MntnSetFrmIntLimit    ���÷�װ�ж�ˮ��\n");
    vos_printf("PPP_HDLC_HARD_MntnShowConfigInfo    ��ӡ������Ϣ\n");

    vos_printf("PPP_Info                            ���ַ  :0x%x\n", g_ulPppVirtAddr);
    vos_printf("PPP_Info                            �����ַ:0x%x\n", g_ulPppPhyAddr);
    vos_printf("PPP_Info                            �ڴ泤��:0x%x\n", g_ulPppTotalBufLen);

    return;
}

#if (VOS_RTOSCK == VOS_OS_VER)

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_InitBuf
 ��������  : ��ʼ��HDLC��Ҫ���ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID)
{
    /* �����ڴ泤�ȣ�ʵ��ʹ�ó���Ϊ0x6140�����밴��0x8000(32K)���� */
    g_ulPppTotalBufLen  = TTF_DATA_ALIGN(TTF_HDLC_MASTER_LINK_TOTAL_LEN);

    /* �ڴ����� */
    g_ulPppVirtAddr     = (VOS_UINT_PTR)VOS_UnCacheMemAlloc(g_ulPppTotalBufLen, &g_ulPppPhyAddr);
    if (VOS_NULL_PTR == g_ulPppVirtAddr)
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_InitBuf, ERROR, VOS_UnCacheMemAlloc Fail\r\n");
        return VOS_ERR;
    }

    memset((void *)g_ulPppVirtAddr, 0, g_ulPppTotalBufLen);

    /* ����TtfMemoryMap.h��ʼ��HDLC�����ڴ� */
    g_pstHdlcDefBufInfo = (HDLC_DEF_BUFF_INFO_STRU *)g_ulPppVirtAddr;
    g_pstHdlcFrmBufInfo = (HDLC_FRM_BUFF_INFO_STRU *)(g_ulPppVirtAddr + sizeof(HDLC_DEF_BUFF_INFO_STRU));

    /*lint -e506 -e774*/
    /* TTF_HDLC_MASTER_DEF_BUF_LEN������ṹHDLC_DEF_BUFF_INFO_STRU�Ĵ�Сһ�� */
    if (TTF_HDLC_MASTER_DEF_BUF_LEN != sizeof(HDLC_DEF_BUFF_INFO_STRU))
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_DEF_BUF_LEN %d sizeof(HDLC_DEF_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_DEF_BUF_LEN, sizeof(HDLC_DEF_BUFF_INFO_STRU));
        return VOS_ERR;
    }

    /* TTF_HDLC_MASTER_FRM_BUF_LEN�ձ�����ṹHDLC_FRM_BUFF_INFO_STRU�Ĵ�Сһ�� */
    if (TTF_HDLC_MASTER_FRM_BUF_LEN != sizeof(HDLC_FRM_BUFF_INFO_STRU))
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_FRM_BUF_LEN %d sizeof(HDLC_FRM_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_FRM_BUF_LEN, sizeof(HDLC_FRM_BUFF_INFO_STRU));
        return VOS_ERR;
    }
    /*lint +e506 +e774*/

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_CommReleaseLink
 ��������  : �ͷŴ洢��PPP_ZC_STRU�ṹ
 �������  : ppstLinkNode   -- �洢PPP_ZC_STRUָ�������
             ulRelCnt       -- ���ͷŵĸ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_CommReleaseLink
(
    PPPC_DATA_LINK_NODE_STRU          **ppstLinkNode,
    VOS_UINT32                          ulRelCnt
)
{
    VOS_UINT32                          ulNodeLoop;


    for ( ulNodeLoop = 0; ulNodeLoop < ulRelCnt; ulNodeLoop++ )
    {
        PPP_MemFree(ppstLinkNode[ulNodeLoop]);

        ppstLinkNode[ulNodeLoop] = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefProcErrorFrames
 ��������  : �������֡
 �������  : usPppId    -   PPP��·��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefProcErrorFrames
(
    VOS_UINT16                          usPppId
)
{
    VOS_UINT8                           ucErrType;
    VOS_UINT8                           ucMask;
    VOS_UINT32                          ulErrTypeLoop;
    VOS_UINT8                           ucResult;
    HDLC_DEF_ERR_FRAMES_CNT_STRU        stErrCnt;
    PPPINFO_S                          *pstPppInfo = VOS_NULL_PTR;


    /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)�ĵ�24:30��Ӧ����λΪ1��ʾ��ĳ�ִ���֡�����
       Ϊ0��ʾ��֡��� */
    ucErrType = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR) , 24, 30);

    if (0 == ucErrType)
    {
        return;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, usPppId);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_HDLC_WARNING_LOG1("PPPC_HDLC_HARD_DefProcErrorFrames, Get PPP Ent Fail %d\r\n", usPppId);
        return;
    }

    /*lint -e734*/
    /* get fcs error count */
    stErrCnt.usFCSErrCnt        = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get frame too long error count */
    stErrCnt.usLenLongCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get frame too short error count */
    stErrCnt.usLenShortCnt      = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error protocol count */
    stErrCnt.usErrProtocolCnt   = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error control count */
    stErrCnt.usErrCtrlCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error address count */
    stErrCnt.usErrAddrCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error flag position count */
    stErrCnt.usFlagPosErrCnt    = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR), 0, 15);
    /*lint +e734*/
    for (ulErrTypeLoop = 0UL; ulErrTypeLoop < HDLC_DEF_MAX_TYPE_CNT; ulErrTypeLoop++)
    {
        ucMask   = SET_BITS_VALUE_TO_BYTE(0x01, ulErrTypeLoop);    /* �������� */
        ucResult = (VOS_UINT8)GET_BITS_FROM_BYTE(ucErrType, ucMask);

        if (0 != ucResult)      /* ���ڴ������ */
        {
            if (0UL == ulErrTypeLoop)   /* ��������0: CRCУ����� */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->stats.badfcs       += stErrCnt.usFCSErrCnt;
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors   += stErrCnt.usFCSErrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc fcs\r\n");
            }
            else if (1UL == ulErrTypeLoop)    /* ��������1: ���װ��֡�ֽ�������1502bytes */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usLenLongCnt;
                PPP_HDLC_WARNING_LOG1("bad hdlc frame length too long\r\n", stErrCnt.usLenLongCnt);
            }
            else if (2UL == ulErrTypeLoop)    /* ��������2: ���װ��֡�ֽ���С��4bytes */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usLenShortCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame length too short\r\n");
            }
            else if (3UL == ulErrTypeLoop)    /* ��������3: ��P�������ʱ, �յ��Ƿ���Protocol��ֵ(��*******0 *******1��ʽ) */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usErrProtocolCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame protocol\r\n");
            }
            else if (4UL == ulErrTypeLoop)    /* ��������4: ��AC����ѹ��ʱ, Control��ֵ��0x03 */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usErrCtrlCnt;
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->stats.badcommand += stErrCnt.usErrCtrlCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame control\r\n");
            }
            else if (5UL == ulErrTypeLoop)    /* ��������5: ��AC����ѹ��ʱ, Address��ֵ��0xFF */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usErrAddrCnt;
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->stats.badaddr    += stErrCnt.usErrAddrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame address\r\n");
            }
            else if (6UL == ulErrTypeLoop)    /* ��������6: ת���ַ�0x7D�����һ��Flag�� */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usFlagPosErrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame flag position\r\n");
            }
            else
            {
                PPP_HDLC_WARNING_LOG("link_HDLCDefDealErr err\r\n");
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefSaveUncompletedInfo
 ��������  : ���ݷ�����ָ֡ʾ�����������֡��Ϣ
 �������  : usPppId    -   PPPʵ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefSaveUncompletedInfo
(
    PPP_ID          usPppId
)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo;
    VOS_UINT32                          ulStatus;                /* ���װ״̬ */
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulValidNum;
    VOS_UINT8                          *pucDefOutOneAddr;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;


    pstDefBuffInfo     = HDLC_DEF_GET_BUF_INFO(usPppId);
    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    ulStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)�ĵ�2λ
       Ϊ1��ʾ���ν��װ�з�����֡�����
       Ϊ0��ʾ�޷�����֡��� */
    if (0 == (ulStatus & 0x4))
    {
        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    g_PppHdlcHardStat.ulDefUncompleteCnt++;

    /* def_valid_num        [23:8]  16'b0   h/s RO   ��֡�ϱ�ʱ����Ч֡��Ŀ�������������һ�����ܵķ�����֡�� */
    ulValidNum = (ulStatus & 0xFFFF00) >> 8;

    /* ������֡���ϱ���Ϣ����Ч֡���棬���ǲ�������Ч֡��Ŀ�� */
    if (TTF_HDLC_DEF_RPT_MAX_NUM <= ulValidNum)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefSaveUncompletedInfo, ERROR, ulValidNum %d >= TTF_HDLC_DEF_RPT_MAX_NUM %d!\r\n",
                     ulValidNum, TTF_HDLC_DEF_RPT_MAX_NUM);

        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    /* �з�����֡ʱ��Ҫ��ȡ������def_uncomplet_st_now(0x8C)��def_info_frl_cnt_now(0xC4)
       ��ȡ�������ϱ��ռ���Ч֮֡��ķ�����֡���ȡ�Э������ݵ�ַ */
    pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_EXIST;

    pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulValidNum]);

    pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;


    if (pucDefOutOneAddr != HDLC_DEF_OUTPUT_BUF_START_ADDR)
    {
        if ((pucDefOutOneAddr - HDLC_DEF_OUTPUT_BUF_START_ADDR) >= pstRptNode->usDefOutOneLen)
        {
            mdrv_memcpy(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
        else
        {
            PS_MEM_MOVE(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }

        pstRptNode->pucDefOutOneAddr = HDLC_DEF_OUTPUT_BUF_START_ADDR;

    }


    /* ������֡��Э�顢���Ⱥ��ڴ洢�ռ�ĵ�ַ�����ֻ���ݴ���Щ��Ϣ�����½��װ��ʱ����ԭ�����HDLC */
    pstUncompletedInfo->usDefOutOnePro   = pstRptNode->usDefOutOnePro;
    pstUncompletedInfo->usDefOutOneLen   = pstRptNode->usDefOutOneLen;
    pstUncompletedInfo->pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;

    /* ���ֻ���ݴ���Щ��Ϣ�����½��װ��ʱ����ԭ�����HDLC */
    pstUncompletedInfo->ulDefStAgo         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstUncompletedInfo->ulDefInfoFrlCntAgo = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    PPP_HDLC_HARD_MntnDefTraceUncompleteInfo(pstUncompletedInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_MntnDefTraceOutput
 ��������  : ��ȡ���װ�������
 �������  : pstBuildInfo    -   �����������
             usValidFrameNum -   ��Ч֡����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnDefTraceOutput
(
    VOS_UINT16                          usValidFrameNum,
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo
)
{
    HDLC_MNTN_DEF_OUTPUT_PARA_STRU     *pstOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    VOS_UINT16                          usMaxFrameNum;


    /* ���װ�ϱ��ռ��ά�ɲ� */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        usMaxFrameNum = (HDLC_MNTN_ALLOC_MEM_MAX_SIZE - sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU)) /
                         sizeof(HDLC_DEF_RPT_NODE_STRU);
        usMaxFrameNum = TTF_MIN(usMaxFrameNum, usValidFrameNum);

        ulDataLen     = sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU) + usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU);
        pstOutputPara = (HDLC_MNTN_DEF_OUTPUT_PARA_STRU *)PS_MEM_ALLOC(PS_PID_PPP_HDLC, ulDataLen);

        if (VOS_NULL_PTR == pstOutputPara)
        {
            PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_MntnDefTraceOutput, NORMAL, Alloc mem failed ulDataLen %d!\r\n", ulDataLen);
            return;
        }

        pstOutputPara->usDefValidNum = usValidFrameNum;
        pstOutputPara->usTraceNum    = usMaxFrameNum;

        VOS_MemCpy_s((VOS_UINT8 *)(pstOutputPara + 1),
                    usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU),
                   (VOS_UINT8 *)(&(pstDefBuffInfo->astRptNodeBuf[0])),
                   usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                   ID_HDLC_MNTN_DEF_OUTPUT_PARA, ulDataLen);

        PS_MEM_FREE(PS_PID_PPP_HDLC, pstOutputPara);
    }

    /* ���װĿ�Ŀռ���ÿ����Ч֡��ά�ɲ� */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usValidFrameNum; ulNodeLoop++ )
        {
            pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstRptNode->usDefOutOneLen, pstRptNode->pucDefOutOneAddr,
                                              ID_HDLC_MNTN_DEF_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefProcRptNode
 ��������  : �����ϱ���Ϣ��ַ�ͳ��ȣ������㿽���ڴ棬����������
 �������  : pstRptNode   -   �ϱ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
PPPC_DATA_LINK_NODE_STRU * PPPC_HDLC_HARD_DefProcRptNode
(
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode
)
{
    PPPC_DATA_LINK_NODE_STRU           *pstMem;
    VOS_UINT16                          usFistSegLen;
    VOS_UINT8                          *pucDefOutOneAddr;
    VOS_UINT8                           aucHeadData[4];


    if ( (0 == pstRptNode->usDefOutOneLen) || (HDLC_DEF_OUT_PER_MAX_CNT < pstRptNode->usDefOutOneLen) )
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_DefProcValidFrames, WARNING, invalid usDefOutOneLen %d\r\n",
                      pstRptNode->usDefOutOneLen);

        return VOS_NULL_PTR;
    }

    pstMem = PPP_MemAlloc(sizeof(aucHeadData) + pstRptNode->usDefOutOneLen, TTF_MEM_POOL_ID_DL_PDU);

    if (VOS_NULL_PTR == pstMem)
    {
        PPP_HDLC_WARNING_LOG1("\r\nPPPC_HDLC_HARD_DefProcRptNode allocMemlen:%d\r\n", pstRptNode->usDefOutOneLen);
        return VOS_NULL_PTR;
    }

    /* ��ַ������� */
    aucHeadData[0] = 0xff;
    aucHeadData[1] = 0x03;
    /* Э���� */
    aucHeadData[2] = (VOS_UINT8)((pstRptNode->usDefOutOnePro >> 8) & 0x00FF);
    aucHeadData[3] = (VOS_UINT8)(pstRptNode->usDefOutOnePro & 0x00FF);

    VOS_MemCpy_s(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed], sizeof(aucHeadData),
                    aucHeadData, sizeof(aucHeadData));
    pstMem->pstPduMem->usUsed   += sizeof(aucHeadData);

    pucDefOutOneAddr    = pstRptNode->pucDefOutOneAddr;
    /* �жϸ�֡��ʼ�ӳ����Ƿ񳬹�����ռ�β�����������ƻش��� */
    if ((pucDefOutOneAddr + pstRptNode->usDefOutOneLen) >
        HDLC_DEF_OUTPUT_BUF_END_ADDR)
    {
        if (pucDefOutOneAddr <= HDLC_DEF_OUTPUT_BUF_END_ADDR)
        {
            usFistSegLen = (VOS_UINT16)(HDLC_DEF_OUTPUT_BUF_END_ADDR - pucDefOutOneAddr);

            /* ��������ʼ��ַ������ռ�β�������� */
            VOS_MemCpy_s(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed], usFistSegLen,
                            pucDefOutOneAddr, usFistSegLen);
            pstMem->pstPduMem->usUsed   += usFistSegLen;

            /* ����������ռ��ײ���ʣ������ */
            VOS_MemCpy_s(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed],
                pstRptNode->usDefOutOneLen - usFistSegLen,
                HDLC_DEF_OUTPUT_BUF_START_ADDR, pstRptNode->usDefOutOneLen - usFistSegLen);
            pstMem->pstPduMem->usUsed   += pstRptNode->usDefOutOneLen - usFistSegLen;
        }
        else
        {
            PPP_MemFree(pstMem);

            PPP_HDLC_WARNING_LOG2("\r\nPPP, PPP_HDLC_HARD_DefProcRptNode, ERROR, Error pucDefOutOneAddr.\r\n", pucDefOutOneAddr, HDLC_DEF_OUTPUT_BUF_END_ADDR);

            PPP_HDLC_HARD_MntnShowDefReg();

            return VOS_NULL_PTR;
        }
    }
    else
    {
        VOS_MemCpy_s(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed],
            pstRptNode->usDefOutOneLen,
            pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        pstMem->pstPduMem->usUsed   += pstRptNode->usDefOutOneLen;
    }

    return pstMem;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefProcValidFrames
 ��������  : ������Ч֡
 �������  : ucRatMode  -   ����ģʽ1X/HRPD
             usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefProcValidFrames
(
    VOS_UINT8                           ucRatMode,
    PPP_ID                              usPppId
)
{
    VOS_UINT16                          usValidFrameNum;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulFrameLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    PPPC_DATA_LINK_NODE_STRU           *pstMem;


    pstDefBuffInfo  = HDLC_DEF_GET_BUF_INFO(usPppId);
    usValidFrameNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 23);

    /* �ϱ����װ�����ݿ�ά�ɲ�:�ϱ��ռ���Ϣ��������� */
    PPPC_HDLC_HARD_MntnDefTraceOutput(usValidFrameNum, pstDefBuffInfo);

    /* ��Ч֡�����ֵ��� */
    if (TTF_HDLC_DEF_RPT_MAX_NUM < usValidFrameNum)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefProcValidFrames, WARNING, usValidFrameNum = %d > TTF_HDLC_DEF_RPT_MAX_NUM = %d",
                      usValidFrameNum, TTF_HDLC_DEF_RPT_MAX_NUM);
        return;
    }

    g_PppHdlcHardStat.ulDefMaxValidCntOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxValidCntOnce, usValidFrameNum);

    /* ��Ŀ�Ŀռ����Ч֡���ݿ������㿽���ڴ棬���ݲ������͵������з����ӿ� */
    for ( ulFrameLoop = 0 ; ulFrameLoop < usValidFrameNum; ulFrameLoop++ )
    {
        pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulFrameLoop]);

        pstMem = PPPC_HDLC_HARD_DefProcRptNode(pstRptNode);

        /* ���벻�����ݻ��ϱ���Ϣ���󣬶�������Ч֡ */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        #ifdef PPPC_HDLC_ST_TEST
        PPPC_STUB_ProcDlData(pstMem);
        #else
        FWD_PppDecap(0, 0, pstMem->pstPduMem, ucRatMode, (VOS_UINT8)usPppId);
        pstMem->pstPduMem = VOS_NULL_PTR;
        /* �ͷ��㿽���ڴ� */
        TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstMem);

        #endif
        g_stPppcDataQueueStats.ulDownlinkSndDataCnt++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefCfgReg
 ��������  : ���ý��װ���üĴ���
 �������  : pstLink    -   PPP��·��Ϣ
             pstDefUncompletedInfo  -   ��·PPP�����ϴν��װ���������֡��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_DefCfgReg
(
    VOS_UINT16                      usPppId,
    HDLC_DEF_UNCOMPLETED_INFO_STRU *pstDefUncompletedInfo
)
{
    VOS_UINT32                          ulPppAcFlag = 0;    /* AC��Ĭ����ѹ�� */
    VOS_UINT32                          ulPppPcFlag = 0;    /* P��Ĭ����ѹ�� */


    /*
        hdlc_def_cfg  (0x70)
         31                           4 3     2   1     0
        |-------------------------------|-------|-----|-----|
        |              Rsv              |  Pfc  | Acfc| ago |
        Reserved             [31:4]  28'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��P����ѹ��������룻01��P��ѹ��������룻11��P�򲻰��룻��������Ч��
        def_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ����1����ʾAC��ѹ����
        def_uncompleted_ago  [0]     1'b0    h/s R/W  ����ָʾ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ���������Ƿ��н��������֡��
                                                      Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����
        */

    VOS_UINT32       ulDeframerCfg;
    VOS_UINT8        ucACComp;
    VOS_UINT8        ucPComp;
    VOS_UINT8        ucLowByte;
    VOS_UINT16       usLowWord;

    /* 1.����ulMode��P���AC���Ƿ�ѹ������hdlc_def_cfg (0x70) */

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ */
    (VOS_VOID)FWD_PppGetWantLcpAcfcFlag((VOS_UINT8)usPppId, &ulPppAcFlag);
    (VOS_VOID)FWD_PppGetWantLcpFcFlag((VOS_UINT8)usPppId, &ulPppPcFlag);

    ucACComp = (1 == ulPppAcFlag) ? 1 : 0;

    ucPComp = (1 == ulPppPcFlag)
               ? HDLC_PROTOCOL_REMOVE_WITH_COMPRESS
               : HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS;

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_DEF_PFC_BITPOS);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_ACFC_BITPOS);
    }

    /* 2.���÷�����֡�����Ϣ */
    if ( (VOS_NULL_PTR != pstDefUncompletedInfo) &&
        (HDLC_DEF_UNCOMPLETED_EXIST == pstDefUncompletedInfo->ucExistFlag) )
    {
        /* def_uncompleted_ago��1��ʾ���ϴ�����ķ�����֡���뱾�ν��װ */
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS);

        /*
        def_uncompleted_len  (0x74)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Len          |
        Reserved             [31:16] 16'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_uncompleted_len  [15:0]  16'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡�ĳ��ȣ�Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ�����
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOneLen & 0xFFFF);

        /*
        def_uncompleted_pro  (0x78)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Pro          |
        Reserved             [31:16] 16'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_uncompleted_pro  [15:0]  16'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��
                                                      Э�飬Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��������е�0Byte��1Byte��2Byte��Ч��
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOnePro & 0xFFFF);

        /*
        def_uncompleted_addr  (0x7C)
         31                  0
        |----------------------|
        |         Addr         |
        def_uncompleted_addr [31:0]  32'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��
                                                      �ⲿ�洢��ʼ��ַ��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��õ�ַ��������ԭ���ϱ���ͬ���µ�ַ��
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->pucDefOutOneAddr);

        /*
        def_uncomplet_st_ago  (0x80)
         31                  16 15             5 4     0
        |----------------------|----------------|-------|
        |         Ago          |       Rsv      |  Ago  |
        crc16_result_ago     [31:16] 16'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��CRCУ��ֵ
        Reserved             [15:5]  11'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_data_st_curr_ago [4:0]   5'b0    h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ������״̬����ǰ״̬
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefStAgo);

        /*
        def_info_frl_cnt_ago  (0xC0)
         31        27 26                 16 15   11 10              0
        |------------|---------------------|-------|-----------------|
        |    Rsv     |         Ago         |  Rsv  |       Ago       |
        Reserved             [31:27] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_framel_cnt_ago   [26:16] 11'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��֡����
        Reserved             [15:11] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_info_cnt_ago     [10:0]  11'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ����Ϣ����
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefInfoFrlCntAgo);
    }

    usLowWord     = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulDeframerCfg = HDLC_MAKE_DWORD(0x00, usLowWord);

    /* �����ý��д��Ĵ��� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR),ulDeframerCfg);

    /* ��������������󵥰����� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)HDLC_DEF_IN_PER_MAX_CNT);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefWaitAndProc
 ��������  : �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ���
 �������  : ucRatMode  -   ����ģʽ1X/HRPD
             ulEnableInterrupt  -   �ж��Ƿ�ʹ��
             usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefWaitAndProc
(
    VOS_UINT8                           ucRatMode,
    VOS_UINT32                          ulEnableInterrupt,
    PPP_ID                              usPppId
)
{
    VOS_UINT32                          ulDefStatus;
    VOS_UINT32                          ulContinue;

    for (; ;)
    {
        /* ʹ���жϣ���ȴ��жϸ������ͷ��ź�����������ѯ���װ״̬�Ĵ��� */
        ulDefStatus = PPP_HDLC_HARD_DefWaitResult(ulEnableInterrupt);

        switch ( ulDefStatus )
        {
            case HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL :
            case HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL :
                /* ������Ч֡������GO_ON�Ĵ��� */
                PPPC_HDLC_HARD_DefProcValidFrames(ucRatMode, usPppId);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefFullPauseCnt++;
                break;
            case HDLC_DEF_STATUS_PAUSE_LCP :
                /* ������Ч֡��LCP֡���������üĴ���������GO_ON�Ĵ��� */
                PPPC_HDLC_HARD_DefProcValidFrames(ucRatMode, usPppId);
                PPPC_HDLC_HARD_DefCfgReg(usPppId, VOS_NULL_PTR);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefLcpPauseCnt++;
                break;
            case HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES :
                /* ���ݷ�����ָ֡ʾ�����������֡��Ϣ */
                PPPC_HDLC_HARD_DefSaveUncompletedInfo(usPppId);

                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DONE_WITH_FRAMES :
                /* ������Ч֡������֡��LCP֡(���������һ֡)�����ݷ�����ָ֡ʾ�����������֡��Ϣ */
                PPPC_HDLC_HARD_DefProcValidFrames(ucRatMode, usPppId);
                PPPC_HDLC_HARD_DefProcErrorFrames(usPppId);
                PPPC_HDLC_HARD_DefSaveUncompletedInfo(usPppId);
                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DOING :
            default:
                /* ��ӡ�쳣��־������PPP���� */
                PPP_HDLC_HARD_DefProcException(ulDefStatus, ulEnableInterrupt);

                ulContinue = VOS_FALSE;
                break;
        }

        /* ��ͣ״̬��Ҫ������������״̬���װ����˳� */
        if (VOS_TRUE != ulContinue)
        {
            break;
        }
    }

    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = 0xFFFFFFFFU;

    return;
}

/************************************************************,*****************
 �� �� ��  : PPPC_HDLC_HARD_DefCfgBufReg
 ��������  : ���ý��װʹ�õ��ڴ�����ؼĴ���
 �������  : pstDefBuffInfo    -   ���װʹ�õ��ڴ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefCfgBufReg(HDLC_DEF_BUFF_INFO_STRU *pstDefBuffInfo)
{
    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_in_lli_addr(0x90) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_out_spc_addr(0xA0) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstDefBuffInfo->aucOutputDataBuf[0]));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_out_space_dep(0xA4)��16λ */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN & 0xFFFF);

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ���ʼ��ַ���ø��Ĵ���def_rpt_addr(0xA8) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstDefBuffInfo->astRptNodeBuf[0]));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ�������ø��Ĵ���def_rpt_dep (0xAC)��16λ */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_MntnDefTraceInput
 ��������  : ��ȡ���װ����������������
 �������  : pstFrmBuffInfo -   ��װʹ�õ��ڴ�
             pstBuildInfo   -   �����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnDefTraceInput
(
    HDLC_DEF_BUFF_INFO_STRU         *pstDefBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_DEF_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* ��¼���ϱ������������нڵ���������ݣ�ÿ���ڵ���һ��IP�� */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen,
                            (VOS_UINT8*)pstParaNode->pucDataAddr,
                            ID_HDLC_MNTN_DEF_INPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_ForbiddenHdlcBug
 ��������  : ���HDLCӲ��Bug,����μ����ⵥDTS2014060907737
 �������  : ppstNode     -   �����װ���ݰ�ָ��

 �������  : ppstNode  ���֮������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��17��
    ��    ��   : t00148005
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_ForbiddenHdlcBug(PPPC_DATA_LINK_NODE_STRU **ppstNode)
{
    PPPC_DATA_LINK_NODE_STRU           *pstDataNode;
    TTF_MEM_ST                         *pstSdu;
    VOS_UINT8                          *pstData;
    VOS_UINT16                          usLen;
    const VOS_UINT8                     ucEndByte = 0x7e;


    pstDataNode  = *ppstNode;

    if (VOS_NULL_PTR == pstDataNode)
    {
        return VOS_ERR;
    }

    usLen   = pstDataNode->pstPduMem->usUsed;
    pstData = pstDataNode->pstPduMem->pData;

    if (usLen <= 1)
    {
        return VOS_OK;
    }

    if (ucEndByte != pstData[usLen - 2])
    {
        /* �����ڶ����ֽڲ�Ϊ7e���ô��� */
        return VOS_OK;
    }
    else if ((usLen >= 3) && (ucEndByte == pstData[usLen - 3]))
    {
        /* �����������ֽ�Ϊ7e���ô��� */
        return VOS_OK;
    }
    else
    {
        /* ����֧���������:
            1. usLen����Ϊ2����һ���ֽ�Ϊ7e;
            2. usLen���ȴ���2�������ڶ����ֽ�Ϊ7e,�����������ֽڲ�Ϊ7e;
         */
        /* ������: �����һ���ֽ�ȡ���������������TTF�ڴ��У�
                     ԭ����TTF�ڴ��ֽ�����1���������TTF�ڴ������ԭ����TTF�ڴ���� */
        pstSdu = TTF_MemBlkAlloc(PS_PID_PPP_HDLC, TTF_MEM_POOL_ID_DL_PDU, 1);
        if (VOS_NULL_PTR != pstSdu)
        {
            pstSdu->usUsed                  = 1;
            pstSdu->pData[0]                = pstDataNode->pstPduMem->pData[usLen - 1];
            pstDataNode->pstPduMem->usUsed -= 1;

            pstDataNode->pstPduMem->pNext   = pstSdu;

            return VOS_OK;
        }
        else
        {
            /* ������������ʧ�ܴ��� */
            g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt++;
            return VOS_ERR;
        }
    }


}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefCheckPara
 ��������  : ��鹹���������������ز����Ƿ�Ϸ�
 �������  : pstMem     -   ����װ���ݰ�
 �������  : ��
 �� �� ֵ  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPPC_HDLC_HARD_DefCheckPara
(
    PPPC_DATA_LINK_NODE_STRU           *pstMem
)
{
    VOS_UINT32                          ulDataLen;


    /* �ڲ����ã��ѱ�֤pstMem�ǿ� */


    ulDataLen   = (VOS_UINT32)TTF_MemGetLen(PS_PID_PPP_HDLC, pstMem->pstPduMem);

    /* ���װ������볤�����ڴ�ģ���������󳤶ȣ�Ŀǰ��1536B */
    if ((0 == ulDataLen) || (PPP_ZC_MAX_DATA_LEN < ulDataLen))
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_DefCheckPara, NORMAL, invalid data length %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefBuildInputParaLink
 ��������  : ������װ�����������
 �������  : pstBuildPara   -   ������������Ĳ���
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_DefBuildInputParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU  *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    PPPC_DATA_LINK_NODE_STRU               *pstDataNode;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT16                              usDataLen;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex = 0;
    HDLC_DEF_BUFF_INFO_STRU                *pstDefBuffInfo;
    HDLC_DEF_UNCOMPLETED_INFO_STRU         *pstUncompletedInfo;
    VOS_UINT32                              ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE;
    VOS_UINT32                              ulRemainCnt;
    TTF_MEM_ST                             *pstSdu;


    /* ��������Ϣ */
    VOS_MemSet_s(pstBuildInfo, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU),
                0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(pstBuildPara->usPppId);

    if (HDLC_DEF_UNCOMPLETED_EXIST == pstUncompletedInfo->ucExistFlag)
    {
        ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE - pstUncompletedInfo->usDefOutOneLen;
    }


    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(pstBuildPara->usPppId);

    for (; pstBuildInfo->ulInputLinkNodeCnt < TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM;)
    {
        pstDataNode  = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(PS_PID_PPP_HDLC,
                        pstBuildPara->pstDlDataQ);

        /* ��û�е����ڵ��������Ƕ������Ѿ�û������ */
        if (VOS_NULL_PTR == pstDataNode)
        {
            break;
        }

        enCheckResult = PPPC_HDLC_HARD_DefCheckPara(pstDataNode);

        if ( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                        PS_PID_PPP_HDLC, pstBuildPara->pstDlDataQ, &ulRemainCnt);

            /* �ͷŽڵ��TTFMemory */
            PPP_MemFree(pstDataNode);
            pstDataNode = VOS_NULL_PTR;

            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulDefInputDiscardCnt++;
            continue;
        }

        if ( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* ���HDLC BUG,�ڷ���HDLC BUG�����¶�ԭ�����ݽ����滻,
           �����pstMemΪ�滻����ڴ�ָ��,ԭʼ�ڴ�ָ������Ѿ����ͷ�
         */
        /* �滻�ڴ��ʱ�������ڴ�ʧ��,�´��ٴ���  */
        if (VOS_OK != PPPC_HDLC_HARD_ForbiddenHdlcBug(&pstDataNode))
        {
            break;
        }

        /* �ڴ���ܷ����滻,����ȡ���� */
        usDataLen = TTF_MemGetLen(PS_PID_PPP_HDLC, pstDataNode->pstPduMem);

        /* һ������������д���װ���ݰ��ܳ����ܳ���15KB */
        /* ���HDLC BUG,�������ݱ��޸Ĺ�,����������1�ֽ�,��Ҫ�ŵ������ж� */
        if( pstBuildInfo->ulInputLinkTotalSize + usDataLen  > ulMaxDataLen1Time )
        {
            /* �´��ٴ��� */
            break;
        }

        /* ���HDLC BUG��Node�ڵ���������TTF�ڴ棬���������ֻʣ��һ���ڵ� */
        if ((VOS_NULL_PTR != pstDataNode->pstPduMem->pNext)
            && (pstBuildInfo->ulInputLinkNodeCnt == (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM - 1)))
        {
            /* �´��ٴ��� */
            break;
        }

        /* ��PPP����ȡ��ͷ��㣬������������� pstBuildInfo->apstInputLinkNode */
        pstDataNode  = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                        PS_PID_PPP_HDLC, pstBuildPara->pstDlDataQ, &ulRemainCnt);

        pstSdu  = pstDataNode->pstPduMem;
        while ((VOS_NULL_PTR != pstSdu)
        && (pstBuildInfo->ulInputLinkNodeCnt < TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM))
        {
            /* ��ȡ��ǰҪ��ӽڵ���±� */
            ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

            /* ����Ҫ����Ĳ����ڵ� */
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

            /* �ѽڵ�������� */
            if( 0 != ulNodeIndex )
            {
                pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode
                    = (HDLC_PARA_LINK_NODE_STRU *)(VOS_UINT32)pstParaNode;
            }

            /* ��д������������������ */
            pstParaNode->pucDataAddr = (VOS_UINT8*)(pstSdu->pData);
            pstParaNode->usDataLen   = pstSdu->usUsed;
            pstParaNode->pstNextNode = VOS_NULL_PTR;

            pstBuildInfo->apstInputLinkNode[ulNodeIndex] = VOS_NULL_PTR;
            pstBuildInfo->ulInputLinkNodeCnt++;

            pstSdu = pstSdu->pNext;
        }

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstDataNode;

        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usDataLen;
        pstBuildInfo->ucRatMode                      = pstDataNode->enRatMode;
        pstBuildInfo->ulDealCnt++;
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        return VOS_ERR;
    }

    /* �ϱ���������������ݿ�ά�ɲ� */
    PPPC_HDLC_HARD_MntnDefTraceInput(pstDefBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_DefPacket
 ��������  : Ӳ����ʽIP���ͽ��װ
 �������  : pstDataQ   -   PPP���ݶ���
             ulDealCnt  -   ���δ������ݰ�����
 �������  : �μ�PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_DefPacket
(
    TTF_LINK_ST                        *pstDlDataQ,
    VOS_UINT16                          usPppId,
    VOS_UINT32                         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    stBuildPara.ucDataType = PPP_PUSH_PACKET_TYPE;
    stBuildPara.usProtocol = PPP_IP;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDlDataQ = pstDlDataQ;

    /* ������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult = PPPC_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG1("Build input parameter fail!\r\n", usPppId);
        PPPC_ClearDlDataQ();
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPPC_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* ����ѹ��ָʾ��������֡�����Ϣ�Ĵ��� */
    PPPC_HDLC_HARD_DefCfgReg(usPppId, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ��� */
    PPPC_HDLC_HARD_DefWaitAndProc(stBuildInfo.ucRatMode, ulEnableInterrupt, usPppId);

    /* �ͷ��ѽ��װ��ɵ����� */
    PPPC_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmCfgBufReg
 ��������  : ���÷�װʹ�õ��ڴ�����ؼĴ���
 �������  : pstFrmBuffInfo -   ��װʹ�õ��ڴ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmCfgBufReg(HDLC_FRM_BUFF_INFO_STRU *pstFrmBuffInfo)
{
    /* ����װ��������������ʼ��ַ���ø��Ĵ���frm_in_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���frm_out_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ���ʼ��ַ���ø��Ĵ���frm_rpt_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstFrmBuffInfo->astRptNodeBuf[0]));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ�������ø��Ĵ���frm_rpt_dep��[15:0]λ */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_FRM_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmCfgReg
 ��������  : IPģʽ�����÷�װ��ؼĴ���
 �������  : usPppId    - PPP��·��Ϣ
             usProtocol - ����װ��Э��ֵ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmCfgReg
(
    VOS_UINT16                          usPppId,
    VOS_UINT16                          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  ��װЭ��ֵ����ЧЭ��ֵ�涨�μ�����б�
    Reserved             [15:4]  12'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��Ӳ��ģ�����P��P����ѹ��;
                                                               01��Ӳ��ģ�����P��P��ѹ��;
                                                               11��Ӳ��ģ�鲻���P��;
                                                               ��������Ч;
    frm_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ��;1����ʾAC��ѹ��;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  ��װ����һά���ά����ѡ��ָʾ�Ĵ�����
                                                                0Ϊһά;1Ϊ��ά;

    IPģʽһ�����P��,PPPģʽһ�������P��
      LCP֡: AC��ѹ����P��ѹ��
    */

    VOS_UINT32                          ulFrmCfg;
    VOS_UINT32                          ulPppAcFlag = 0;
    VOS_UINT32                          ulPppPcFlag = 0;
    VOS_UINT32                          ulAccmFlag  = 0;


    /* ���Ĵ���hdlc_frm_cfg��[0]λfrm_in_lli_1dor2d����Ϊ0 */
    ulFrmCfg = 0x0;

    /* ����hdlc_frm_cfg�� P��� AC�� */
    if (PPP_LCP != usProtocol)
    {
        /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ */
        (VOS_VOID)FWD_PppGetHisLcpAcfcFlag((VOS_UINT8)usPppId, &ulPppAcFlag);
        (VOS_VOID)FWD_PppGetHisLcpFcFlag((VOS_UINT8)usPppId, &ulPppPcFlag);
        (VOS_VOID)FWD_PppGetHisAccm((VOS_UINT8)usPppId, &ulAccmFlag);
        if ( 1 == ulPppAcFlag )
        {
            ulFrmCfg |= (1 << HDLC_FRM_ACFC_BITPOS);
        }

        if ( 1 == ulPppPcFlag )
        {
            ulFrmCfg |= (1 << HDLC_FRM_PFC_BITPOS);
        }

        /* ����hdlc_frm_accm */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),
                            ulAccmFlag);
    }
    else
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    }

    /* ���üĴ���hdlc_frm_cfg��[31:16]λfrm_protocolΪusProtocol */
    ulFrmCfg |= ( ((VOS_UINT32)usProtocol) << 16 );

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR), ulFrmCfg);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_MntnFrmTraceOutput
 ��������  : ��ȡ��װ����������������
 �������  : ucFrmValidNum  -   ��Ч֡����
             usFrmOutSegNum -   ��Ч֡�ֶθ���
             pstFrmBuffInfo -   ��װ����ڴ��ַ
             pstBuildInfo   -   �����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnFrmTraceOutput
(
    VOS_UINT8                           ucFrmValidNum,
    VOS_UINT16                          usFrmOutSegNum,
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU     *pstBuildInfo
)
{
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU      stOutputPara;
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU     *pstOutputPara = &stOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        ulDataLen     = sizeof(HDLC_MNTN_FRM_OUTPUT_PARA_STRU);

        pstOutputPara->ulOutputLinkNodeCnt   = pstBuildInfo->ulOutputLinkNodeCnt;
        pstOutputPara->ulOutputLinkTotalSize = pstBuildInfo->ulOutputLinkTotalSize;
        pstOutputPara->ucFrmValidNum         = ucFrmValidNum;
        pstOutputPara->usOutputNodeUsedCnt   = usFrmOutSegNum;

        VOS_MemCpy_s((VOS_UINT8 *)(&(pstOutputPara->astOutputParaLinkNodeBuf[0])),
                    TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])),
                   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU));

        VOS_MemCpy_s((VOS_UINT8 *)(&(pstOutputPara->astRptNodeBuf[0])),
                    TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astRptNodeBuf[0])),
                   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                        ID_HDLC_MNTN_FRM_OUTPUT_PARA, ulDataLen);
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usFrmOutSegNum; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, pstParaNode->pucDataAddr,
                                              ID_HDLC_MNTN_FRM_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmProcValidFram
 ��������  : ������Ч֡�����ͷ�ʣ���ڴ�
 �������  : usPppId        -   PPPʵ��ID
             ucPdnId        -   PDNʵ��ID
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmProcValidFrames
(
    PPP_ID                              usPppId,
    VOS_UINT8                           ucPdnId,
    HDLC_PARA_LINK_BUILD_INFO_STRU     *pstBuildInfo
)
{
    PPPC_DATA_LINK_NODE_STRU           *pstMem;
    VOS_UINT16                          usFrmOutSegNum;
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT32                          ulFrmOutSpaceCnt;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaLink;
    HDLC_FRM_RPT_NODE_STRU             *pstFrmRptNodeStru;
    PPPC_DATA_LINK_NODE_STRU          **ppstInputLinkNode;
    PPPC_DATA_LINK_NODE_STRU          **ppstOutputLinkNode;
    VOS_UINT32                          ucRptSpaceIndex;
    VOS_UINT32                          ulOutputLinkIndex;
    VOS_UINT8                          *pucFrmOutAddr;
    VOS_UINT16                          usFrmOutLen;
    VOS_UINT16                          usDataLen;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;
    VOS_UINT32                          ulRet;


    pstFrmBuffInfo     = HDLC_FRM_GET_BUF_INFO(usPppId);                   /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmRptNodeStru  = &(pstFrmBuffInfo->astRptNodeBuf[0]);              /* ��װ�ϱ��ռ��׵�ַ */
    pstOutputParaLink  = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]);   /* ��װ��������׵�ַ */
    ppstInputLinkNode  = &(pstBuildInfo->apstInputLinkNode[0]);            /* ��װ��������ڵ��Ӧ�㿽���ڴ������׵�ַ */
    ppstOutputLinkNode = &(pstBuildInfo->apstOutputLinkNode[0]);           /* ��װ�������ڵ��Ӧ�㿽���ڴ������׵�ַ */
    ulFrmOutSpaceCnt   = pstBuildInfo->ulOutputLinkNodeCnt;                /* ��װ�������ڵ�ĸ��� */

    /* ��Ч֡���ռ��Ƭ�θ���usFrmOutSegNum= hdlc_frm_status�Ĵ���[31:16]λ��ֵ */
    usFrmOutSegNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* ��Ч֡����usFrmValidNum= hdlc_frm_status�Ĵ���[15:8]λ��ֵ */
    ucFrmValidNum  = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 15);

    /* �ϱ���װ�����ݿ�ά�ɲ�:�ϱ��ռ���Ϣ������������� */
    PPPC_HDLC_HARD_MntnFrmTraceOutput(ucFrmValidNum, usFrmOutSegNum, pstFrmBuffInfo, pstBuildInfo);

    /* ucFrmValidNum�϶�ҪС�ڵ���ʹ�õ��ڴ����usFrmOutSegNum */
    if( ucFrmValidNum > usFrmOutSegNum )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > usFrmOutSegNum = %d",
                      ucFrmValidNum, usFrmOutSegNum);
        PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* ucFrmValidNumӦ��������������ͬulInputLinkNodeCnt��������װ������ܻ�Ⱥ���С */
    if( ucFrmValidNum > pstBuildInfo->ulInputLinkNodeCnt )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > InputLinkNodeCnt = %d",
                      ucFrmValidNum, pstBuildInfo->ulInputLinkNodeCnt);
        PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* usFrmOutSegNumʹ�õ��ڴ�����϶�С�ڵ���ulOutputLinkNodeCnt */
    if( usFrmOutSegNum  > ulFrmOutSpaceCnt )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_out_seg_num = %d > OutputLinkNodeCnt = %d",
                      usFrmOutSegNum, ulFrmOutSpaceCnt);
        PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    ucRptSpaceIndex   = 0;
    ulOutputLinkIndex = 0;

    while( ucRptSpaceIndex < ucFrmValidNum )
    {
        pucFrmOutAddr    = pstFrmRptNodeStru[ucRptSpaceIndex].pucFrmOutOneAddr;
        usFrmOutLen      = pstFrmRptNodeStru[ucRptSpaceIndex].usFrmOutOneLen;

        if ( (0 == usFrmOutLen) || (HDLC_FRM_OUT_PER_MAX_CNT < usFrmOutLen) )
        {
            PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_FrmProcValidFrames, ERROR, invalid usFrmOutOneLen %d\r\n",
                          usFrmOutLen);

            /* �ͷ������Ŀ�Ŀռ� */
            PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        pstMem          = ppstOutputLinkNode[ulOutputLinkIndex];
        enIpDataType    = ppstInputLinkNode[ucRptSpaceIndex]->enIpDataType;

        if( pucFrmOutAddr != pstMem->pstPduMem->pData )
        {
            PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmProcValidFram, ERROR, SOC copy error!\r\n");

            /* �ͷ������Ŀ�Ŀռ� */
            PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        PPP_MemSet(&stRlpSdu, sizeof(stRlpSdu), 0, sizeof(stRlpSdu));
        PPP_MemSet(&stHrpdSdu, sizeof(stHrpdSdu), 0, sizeof(stHrpdSdu));
        stRlpSdu.enIpDataType       = enIpDataType;
        stRlpSdu.ucTotalPppFrgmt    = 1;
        stHrpdSdu.enIpDataType      = enIpDataType;
        stHrpdSdu.ucTotalPppFrgmt   = 1;

        /* For 1x Rlp trace */
        if (VOS_NULL_PTR != ppstInputLinkNode[ucRptSpaceIndex]->pstUlDataInfo)
        {
            PS_MEM_CPY(&stRlpSdu.stUlDataInfo,
                        ppstInputLinkNode[ucRptSpaceIndex]->pstUlDataInfo,
                        sizeof(PS_DATA_EXT_INFO_STRU));
        }

        while( usFrmOutLen > 0 )
        {
            /* ��pstBuildInfo->apstOutputLinkNodeȡ��ͷ��� pstMem */
            pstMem    = ppstOutputLinkNode[ulOutputLinkIndex];

            /* ���������������ָĿ�Ŀռ�Ĵ�С */
            usDataLen = pstOutputParaLink[ulOutputLinkIndex].usDataLen;

            if( usFrmOutLen > usDataLen )
            {
                pstMem->pstPduMem->usUsed   = usDataLen;
                usFrmOutLen                 -= usDataLen;
                stRlpSdu.ucTotalPppFrgmt    = 2;
                stRlpSdu.ucCurrPppFrgmt     = 0;
                stHrpdSdu.ucTotalPppFrgmt   = 2;
                stHrpdSdu.ucCurrPppFrgmt    = 0;
            }
            else
            {
                pstMem->pstPduMem->usUsed   = usFrmOutLen;
                usFrmOutLen                 = 0;
                stRlpSdu.ucCurrPppFrgmt     = (2 == stRlpSdu.ucTotalPppFrgmt) ? (1) : (0);
                stHrpdSdu.ucCurrPppFrgmt    = (2 == stHrpdSdu.ucTotalPppFrgmt) ? (1) : (0);
            }

            #ifdef PPPC_HDLC_ST_TEST
            PPPC_STUB_ProcUlData(pstMem, usDataLen);
            #else

            if (PPPC_RAT_MODE_1X == pstBuildInfo->ucRatMode)
            {
                /* �������ݱ��ķ��͵�RLP */
                stRlpSdu.ucPdnId    = ucPdnId;
                stRlpSdu.ulSduLen   = pstMem->pstPduMem->usUsed;
                stRlpSdu.pstSdu     = pstMem->pstPduMem;

                CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

                /* ����IP�����ļ�����1 */
                g_stPppcDataQueueStats.ul1xUlIPDataSndCnt++;
            }
            else
            {
                /* �����eHRPDģʽ�Ҵ�ʱPDN����open��Ҫ�������� */
                ulRet = PPPC_CheckPdnStateBeforeTransferData(ucPdnId);
                if (VOS_OK == ulRet)
                {
                    /* ��ȡstream2��Ӧ�ð���Ϣ */
                    enAppType                   = PPPC_HRPD_GetAppType();

                    stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber((VOS_UINT8)usPppId);
                    stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
                    stHrpdSdu.ulSduLen          = pstMem->pstPduMem->usUsed;
                    stHrpdSdu.pstSdu            = pstMem->pstPduMem;
                    stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;

                    CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                    /* ����IP�����ļ�����1 */
                    g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt++;
                }
            }
            /* �ͷŽڵ� */
            pstMem->pstPduMem   = VOS_NULL_PTR;
            TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstMem);
            #endif

            g_stPppcDataQueueStats.ulUplinkSndDataCnt++;

            /* ������������ݰ���apstOutputLinkNode����� */
            ppstOutputLinkNode[ulOutputLinkIndex] = VOS_NULL_PTR;

            ulOutputLinkIndex++;
        }

        ucRptSpaceIndex++;
    }

#ifndef PPPC_HDLC_ST_TEST
    if (PPPC_RAT_MODE_1X == pstBuildInfo->ucRatMode)
    {
        /* ����RLP�������б��� */
        CTTF_1X_RLP_ReverseLink_TriggerDataProc();
    }
#endif

    /* �ͷ�ʣ��δ���õ�Ŀ�Ŀռ� */
    PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                  ulFrmOutSpaceCnt - ulOutputLinkIndex);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmWaitAndProc
 ��������  : �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ�
 �������  : ulEnableInterrupt  -   �ж��Ƿ�ʹ��
             usPppId            -   PPPʵ��ID
             ucPdnId            -   PDNʵ��ID
             pstLink            -   PPP��·��Ϣ
 �������  : pstBuildInfo       -   ��������Ľ����Ϣ���������������ȡ�
                                    �ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmWaitAndProc
(
    VOS_UINT32                           ulEnableInterrupt,
    PPP_ID                               usPppId,
    VOS_UINT8                            ucPdnId,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT32                          ulFrmStatus;


    /* ʹ���жϣ���ȴ��жϸ������ͷ��ź�����������ѯ���װ״̬�Ĵ��� */
    ulFrmStatus = PPP_HDLC_HARD_FrmWaitResult(ulEnableInterrupt);

    if ( HDLC_FRM_ALL_PKT_DONE == ulFrmStatus )
    {
        /* ������Ч֡�����ͷ�ʣ���ڴ� */
        PPPC_HDLC_HARD_FrmProcValidFrames(usPppId, ucPdnId, pstBuildInfo);
    }
    else
    {
        /* �ͷ������Ŀ�Ŀռ� */
        PPPC_HDLC_HARD_CommReleaseLink(pstBuildInfo->apstOutputLinkNode, pstBuildInfo->ulOutputLinkNodeCnt);

        /* ��ӡ�쳣��־������PPP���� */
        PPP_HDLC_HARD_FrmProcException(ulFrmStatus, ulEnableInterrupt);
    }

    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = 0xFFFFFFFFU;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmUpdateLink
 ��������  : ����һ���ڴ�����������ؽṹ��Ϣ
 �������  : ulAllocMemCnt      - ����������ڴ�����
             aulAllocLen        - ��¼��������ĸ����ڴ��ĳ���
             papstAllocedMem    - ��¼��������ĸ����ڴ����ƽṹָ��
             pstBuildPara       -   ������������Ĳ���
 �������  : pstBuildInfo       -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmUpdateLink
(
    VOS_UINT32                      ulAllocMemCnt,
    VOS_UINT32 *                    aulAllocLen,
    PPPC_DATA_LINK_NODE_STRU      **ppstAllocedMem,
    HDLC_PARA_LINK_BUILD_PARA_STRU *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU *pstBuildInfo
)
{
    VOS_UINT32                          ulMemLoop;
    VOS_UINT32                          ulNodeIndex;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaNode;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo          = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);

    if( (pstBuildInfo->ulOutputLinkNodeCnt + ulAllocMemCnt) > TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM )
    {
        g_PppHdlcHardStat.ulFrmOutputLinkFullCnt++;

        PPPC_HDLC_HARD_CommReleaseLink(ppstAllocedMem, ulAllocMemCnt);

        return VOS_ERR;
    }

    /* ����Ŀ�Ŀռ����� apstOutputLinkNode�������ͷ�Ŀ�Ŀռ� */
    VOS_MemCpy_s(&(pstBuildInfo->apstOutputLinkNode[pstBuildInfo->ulOutputLinkNodeCnt]),
               ulAllocMemCnt * sizeof(PPPC_DATA_LINK_NODE_STRU *),
               &(ppstAllocedMem[0]),
               ulAllocMemCnt * sizeof(PPPC_DATA_LINK_NODE_STRU *));

    /* ����װ�������������ĸ�����Ա��ֵ */
    for ( ulMemLoop = 0; ulMemLoop < ulAllocMemCnt; ulMemLoop++ )
    {
        ulNodeIndex = pstBuildInfo->ulOutputLinkNodeCnt;

        pstOutputParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex]);

        /* �����ϸ���������������pstNextNode�� */
        if (0 != ulNodeIndex)
        {
            pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = pstOutputParaNode;
        }

        pstOutputParaNode->pucDataAddr = ppstAllocedMem[ulMemLoop]->pstPduMem->pData;
        pstOutputParaNode->usDataLen   = (VOS_UINT16)aulAllocLen[ulMemLoop];
        pstOutputParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->ulOutputLinkNodeCnt++;
        pstBuildInfo->ulOutputLinkTotalSize += aulAllocLen[ulMemLoop];
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_OutputMemAlloc
 ��������  : ��װ���Ŀ�Ŀռ�����
 �������  : usLen          -   ��������ڴ泤��
             pstBuildPara   -   ������������Ĳ���
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmOutputMemAlloc
(
    VOS_UINT16                           usLen,
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT16                  usFrmedMaxLen;                                  /* ��װ��Ŀ��ܵ���󳤶� */
    VOS_UINT16                  usAllocLen;
    VOS_UINT32                  ulAllocLoop;
    VOS_UINT32                  ulLoopCnt;
    VOS_UINT32                  ulAllocMemCnt;                                  /* ����������ڴ���� */
    VOS_UINT32                  aulAllocLen[HDLC_OUTPUT_PARA_LINK_MAX_SIZE] = {0};    /* ��¼��������ĸ����ڴ�鳤�� */
    PPPC_DATA_LINK_NODE_STRU   *apstAllocedMem[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* ��¼��������ĸ����ڴ��ָ�� */
    PPPC_DATA_LINK_NODE_STRU   *pstMem;

    PS_MEM_SET(apstAllocedMem, 0, HDLC_OUTPUT_PARA_LINK_MAX_SIZE * sizeof(PPPC_DATA_LINK_NODE_STRU *));

    /* ��װ����ܵ�������ݳ���(2*ԭʼ���ݳ���+13B) */
    usFrmedMaxLen = (VOS_UINT16)HDLC_FRM_GET_MAX_FRAMED_LEN(usLen);
    ulAllocMemCnt = 0;
    ulLoopCnt     = TTF_CEIL(usFrmedMaxLen, PPP_ZC_MAX_DATA_LEN);

    for ( ulAllocLoop = 0 ; ulAllocLoop < ulLoopCnt; ulAllocLoop++ )
    {
        if (ulAllocLoop != (ulLoopCnt - 1) )
        {
            usAllocLen = PPP_ZC_MAX_DATA_LEN;
        }
        else
        {
            usAllocLen = (VOS_UINT16)(usFrmedMaxLen - ulAllocLoop*PPP_ZC_MAX_DATA_LEN);
        }

        pstMem = PPP_MemAlloc(usAllocLen, TTF_MEM_POOL_ID_UL_DATA);

        if (VOS_NULL_PTR == pstMem)
        {
            PPP_HDLC_WARNING_LOG1("alloc memory fail. allocMemlen:%d\n", usAllocLen);
            break;
        }

        ulAllocMemCnt++;
        aulAllocLen[ulAllocLoop]    = usAllocLen;
        apstAllocedMem[ulAllocLoop] = pstMem;
    }

    /* ����������ڴ�ʧ�ܵ���������ͷű����Ѿ�������ڴ� */
    if (ulLoopCnt > ulAllocMemCnt)
    {
        PPPC_HDLC_HARD_CommReleaseLink(&(apstAllocedMem[0]), ulAllocMemCnt);
        return VOS_ERR;
    }

    return PPPC_HDLC_HARD_FrmUpdateLink(ulAllocMemCnt,
                                       &(aulAllocLen[0]), &(apstAllocedMem[0]),
                                       pstBuildPara, pstBuildInfo);
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_MntnFrmTraceInput
 ��������  : ��ȡ��װ����������������
 �������  : pstFrmBuffInfo -   ��װʹ�õ��ڴ�
             pstBuildInfo   -   �����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnFrmTraceInput
(
    HDLC_FRM_BUFF_INFO_STRU         *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_FRM_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* ��¼���ϱ������������нڵ���������ݣ�ÿ���ڵ���һ��IP�� */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, pstParaNode->pucDataAddr,
                                              ID_HDLC_MNTN_FRM_INPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmBuildParaLink
 ��������  : ��鹹�������������������ز����Ƿ�Ϸ�
 �������  : pstMem     -   ����װ���ݰ�
             ulDataLen  -   ����װ���ݰ�����
             ucDataType -   ����װ���ݰ�����
             usProtocol -   ����װ���ݰ�Э������
 �������  : ��
 �� �� ֵ  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPPC_HDLC_HARD_FrmCheckPara
(
    PPPC_DATA_LINK_NODE_STRU           *pstMem,
    VOS_UINT32                          ulDataLen,
    VOS_UINT16                          usProtocol
)
{
#if 0
    PPP_DATA_TYPE_ENUM_UINT8            ucCurrDataType;
    VOS_UINT32                          ulRlst;
    VOS_UINT16                          usCurrProtocol;
#endif

    /* ����װ���ݰ������쳣 */
    if ( (0 == ulDataLen) || (HDLC_FRM_IN_PER_MAX_CNT < ulDataLen) )
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_FrmCheckPara,IP mode framer data len wrong %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

#if 0
    /* �������PPPģʽ */
    if( PPP_PUSH_RAW_DATA_TYPE != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_PASS;
    }

    ulRlst  = PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usCurrProtocol);

    if( VOS_OK != ulRlst )
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmCheckPara, Warning, PPP mode get framer data protocol error\r\n");
        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* ��֤һ���������ù����з�װЭ��ֵһ�� */
    if( usProtocol != usCurrProtocol )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }
#endif
    return PPP_HDLC_PARA_CHECK_PASS;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmBuildParaLink
 ��������  : ����������������������ϱ������ڴ��ά�ɲ�
 �������  : pstBuildPara   -   ������������Ĳ���
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmBuildParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU         *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU         *pstBuildInfo
)
{
    PPPC_DATA_LINK_NODE_STRU               *pstMem;
    VOS_UINT32                              ulLoop;
    VOS_UINT16                              usUnFrmLen;
    VOS_UINT32                              ulAllocResult;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT32                              ulAllocMemFail;
    HDLC_FRM_BUFF_INFO_STRU                *pstFrmBuffInfo;
    VOS_UINT32                              ulRemainCnt;


    VOS_MemSet_s(pstBuildInfo, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU),
                0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);
    ulAllocMemFail = VOS_FALSE;

    for(ulLoop = 0; ulLoop < 1 /*TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM*/; ulLoop++)
    {
        pstMem = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(PS_PID_PPP_HDLC,
                        pstBuildPara->pstUlDataQ);

        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usUnFrmLen    = TTF_MemGetLen(PS_PID_PPP_HDLC, pstMem->pstPduMem);
        enCheckResult = PPPC_HDLC_HARD_FrmCheckPara(pstMem, usUnFrmLen,
                                                   pstBuildPara->usProtocol);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                    PS_PID_PPP_HDLC, pstBuildPara->pstUlDataQ, &ulRemainCnt);
            /* �ͷŽڵ��TTFMemory */
            PPP_MemFree(pstMem);
            pstMem = VOS_NULL_PTR;

            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulFrmInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* һ������������д���װ���ݰ��ܳ����ܳ���15KB */
        if( pstBuildInfo->ulInputLinkTotalSize + usUnFrmLen > TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE )
        {
            break;
        }

        /* �����װĿ�Ŀռ� */
        ulAllocResult = PPPC_HDLC_HARD_FrmOutputMemAlloc(usUnFrmLen, pstBuildPara, pstBuildInfo);

        if( VOS_OK != ulAllocResult )
        {
            ulAllocMemFail = VOS_TRUE;

            g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt++;
            break;
        }

        /* ��PPP����ȡ��ͷ��㣬������������� pstBuildInfo->apstInputLinkNode */
        pstMem = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                    PS_PID_PPP_HDLC, pstBuildPara->pstUlDataQ, &ulRemainCnt);

        /* ��ȡ��ǰҪ��ӽڵ���±� */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* ����Ҫ����Ĳ����ڵ� */
        pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* ��д������������������ */
        if( 0 != ulNodeIndex )
        {
            pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = pstParaNode;
        }

        pstParaNode->pucDataAddr = pstMem->pstPduMem->pData;
        pstParaNode->usDataLen   = usUnFrmLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usUnFrmLen;
        pstBuildInfo->ucRatMode                      = pstMem->enRatMode;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        if (VOS_TRUE == ulAllocMemFail)
        {
            /* �ȴ�һ��ʱ������³��������ڴ��ٷ�װ */
            PPP_HDLC_HARD_FrmStartTimer(pstBuildPara);

            g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt++;
        }

        return VOS_ERR;
    }

    /* ��������������������ݿ�ά�ɲ� */
    PPPC_HDLC_HARD_MntnFrmTraceInput(pstFrmBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_FrmPacket
 ��������  : IPģʽ���з�װ��������
 �������  : usPppId        -   PPPʵ��ID
             ucPdnId        -   PDNʵ��ID
             usProtocol     -   ����װЭ��
             pstLink        -   PPP��·��Ϣ
             pstDataQ       -   PPP���ݶ���
 �������  : *pulDealCurCnt  -  ָ��ǰ�����PPP�����еĽ�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmPacket
(
    PPP_ID                              usPppId,
    VOS_UINT8                           ucPdnId,
    VOS_UINT16                          usProtocol,
    TTF_LINK_ST                        *pstUlDataQ,
    VOS_UINT32                         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PULL_PACKET_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstUlDataQ = pstUlDataQ;

    /* ����usPppId�ҵ���Ӧ���ڴ� */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* ����������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult  = PPPC_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmPacket, WARNING, BuildParaLink Fail.\r\n");
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPPC_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* ���÷�װ��ؼĴ��� */
    PPPC_HDLC_HARD_FrmCfgReg(usPppId, usProtocol);

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ� */
    PPPC_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, ucPdnId, &stBuildInfo);

    /* �ͷ�pstBuildInfo->apstInputLinkNode�еĽ���ڴ� */
    PPPC_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_SendAsFrmPacketMsg
 ��������  : ��Ϣ���ͺ���
 �������  : usPppId        -- PPPʵ��ID
             usProtocol     -- ����װЭ��ֵ
             pstMem         -- ����װ���ݰ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_SendAsFrmPacketMsg
(
    VOS_UINT16                          usPppId,
    VOS_UINT16                          usProtocol,
    TTF_MEM_ST                         *pstMem
)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstMsg;
    VOS_UINT32                               ulLength;


    ulLength    = sizeof(HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_PPP_HDLC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_SendMsg, ERROR: PS_ALLOC_MSG Failed!\r\n");
        return VOS_ERR;
    }

    /*��д��Ϣͷ:*/
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulLength        = ulLength;

    pstMsg->MsgHeader.ulMsgName       = PPPC_HDLC_PROC_AS_FRM_PACKET_IND;
    /*��д��Ϣ��:*/
    pstMsg->usPppId                   = usPppId;
    pstMsg->usProtocol                = usProtocol;
    pstMsg->pstMem                    = pstMem;

    /*���͸���Ϣ*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_PPP_HDLC, pstMsg))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_SendAsFrmPacketMsg, ERROR : PS_SEND_MSG Failed!");
        TTF_MemFree(PS_PID_PPP_HDLC, pstMem);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_ProcAsFrmPacket
 ��������  : �������з�װ����
 �������  : usPppId        -- PPPʵ��ID
             ucPdnId        -- PDNʵ��ID
             usProtocol     -- ����װЭ��ֵ
             pstMem         -- ����װ���ݰ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16                          usPppId,
    VOS_UINT8                           ucPdnId,
    VOS_UINT16                          usProtocol,
    TTF_MEM_ST                         *pstMem
)
{
    VOS_UINT32                          ulDealCurCnt;
    TTF_LINK_ST                         stDataQ;
    VOS_UINT32                          ulDealResult;
    PPPC_DATA_LINK_NODE_STRU           *pstNode = VOS_NULL_PTR;
    VOS_UINT32                          ulNonEmptyEvent;   /* ��¼�����Ƿ������ɿյ��ǿյ�ת�� */
    VOS_UINT32                          ulRet;

    ulDealCurCnt = 0;

    /* ��ʼ������stDataQ, ���� pstMem ��� */
    PS_MEM_SET(&stDataQ, 0, sizeof(stDataQ));

    TTF_LinkInit(PS_PID_PPP_HDLC, &stDataQ);

    pstNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(PS_PID_PPP_HDLC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        TTF_MemFree(PS_PID_PPP_HDLC, pstMem);
        return;
    }

    PPP_MemSet(pstNode, sizeof(PPPC_DATA_LINK_NODE_STRU), 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstNode->pstPduMem    = pstMem;
    pstNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    TTF_NodeInit(&(pstNode->stNode));

    /* �����ݽ��������β�� */
    ulRet = TTF_LinkSafeInsertTail(PS_PID_PPP_HDLC, &stDataQ,
            &(pstNode->stNode), &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        TTF_MemFree(PS_PID_PPP_HDLC, pstMem);
        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstNode);
        return;
    }

    /* ֱ�ӽ������ݰ���װ���͸�PC */
    ulDealResult = PPPC_HDLC_HARD_FrmPacket(usPppId, ucPdnId, usProtocol, &stDataQ, &ulDealCurCnt);

    if ((VOS_OK != ulDealResult) || (1 != ulDealCurCnt))
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_MakeFrmPacket, ERROR, ulDealResult %d ulDealCurCnt %d!\r\n",
                      ulDealResult, ulDealCurCnt);
#if 0
        /* ˵����ĳ�ִ���������û�дӶ������Ƴ�����Ҫ�ͷ� */
        if (0 < PPP_ZC_GET_QUEUE_LEN(&stDataQ))
        {
            PPP_MemFree(pstMem);
        }
#endif
        return;
    }

    g_PppHdlcHardStat.ulFrmIpDataProcCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HDLC_HARD_ProcProtocolPacket
 ��������  : Ӳ����װPPPЭ��ջ�����Э���
 �������  : pstLink    -   PPP��·��Ϣ
             pstMbuf    -   PPPЭ��ջ�����Э���
             ulPri      -   ���ȼ�,Ĭ����0
             usProto    -   ���ݰ���Ӧ��Э��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_ProcProtocolPacket
(
    VOS_UINT32                          ulPppId,
    VOS_UINT8                           ucPdnId,
    PMBUF_S                            *pstMbuf,
    VOS_INT32                           ulPri,
    VOS_UINT16                          usProtocol
)
{
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT32                          ulFrmResult;
    VOS_UINT32                          ulDefResult;


    pstTtfMem = PPPC_AdapterMBuftoTtfMemory(pstMbuf, TTF_MEM_POOL_ID_UL_DATA, 0, pstMbuf->ulTotalDataLength);

    PMBUF_Destroy(pstMbuf);

    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, pstMem is NULL!\r\n");
        return VOS_ERR;
    }

    /* PPPЭ��ջ�ظ���Э�̰���Ҫ��װ�󷢸�PC��ȷ�ϴ�ʱ�Ƿ��װ����װ���Ѿ���� */
    ulFrmResult     = PPP_HDLC_HARD_FrmIsEnabled();
    ulDefResult     = PPP_HDLC_HARD_DefIsEnabled();

    /* �˺��������н��Э�̰�ʱ��PPPЭ��ջ����Ӧ�����ʱ���װ��Ӧ��ʹ�� */
    if( (VOS_TRUE == ulFrmResult) || (VOS_TRUE == ulDefResult) )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, ulFrmResult %d, ulDefResult %d!\r\n",
                      ulFrmResult, ulDefResult);
        PPPC_HDLC_HARD_SendAsFrmPacketMsg((VOS_UINT16)ulPppId, usProtocol, pstTtfMem);

        return VOS_OK;
    }

    /* �´�PPP������ȵ�ʱ���ٷ�װ��Э�̣���ʱ��װ����װ��δʹ�� */
    PPPC_HDLC_HARD_ProcAsFrmPacket((VOS_UINT16)ulPppId, ucPdnId, usProtocol, pstTtfMem);

    return VOS_OK;
}


#else

extern PPP_DATA_Q_CTRL_ST     g_PppDataQCtrl;

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_InitBuf
 ��������  : ��ʼ��HDLC��Ҫ���ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID)
{
    /* �����ڴ泤�ȣ�ʵ��ʹ�ó���Ϊ0x6140�����밴��0x8000(32K) */
    g_ulPppTotalBufLen  = PAGE_ALIGN(TTF_HDLC_MASTER_LINK_TOTAL_LEN + PAGE_SIZE);

    /* ����ϵͳ�ӿ�dma_alloc_coherent����uncache�ڴ� */
    g_ulPppVirtAddr     = (VOS_UINT_PTR)VOS_UnCacheMemAlloc(g_ulPppTotalBufLen, &g_ulPppPhyAddr);
    if (VOS_NULL_PTR == g_ulPppVirtAddr)
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_InitBuf, ERROR, VOS_UnCacheMemAlloc Fail\r\n");
        return VOS_ERR;
    }

    memset((void *)g_ulPppVirtAddr, 0, g_ulPppTotalBufLen);

    /* ����TtfMemoryMap.h��ʼ��HDLC�����ڴ� */
    g_pstHdlcDefBufInfo = (HDLC_DEF_BUFF_INFO_STRU *)g_ulPppVirtAddr;
    g_pstHdlcFrmBufInfo = (HDLC_FRM_BUFF_INFO_STRU *)(g_ulPppVirtAddr + sizeof(HDLC_DEF_BUFF_INFO_STRU));

    /*lint -e506 -e774*/
    /* TTF_HDLC_MASTER_DEF_BUF_LEN������ṹHDLC_DEF_BUFF_INFO_STRU�Ĵ�Сһ�� */
    if (TTF_HDLC_MASTER_DEF_BUF_LEN != sizeof(HDLC_DEF_BUFF_INFO_STRU))
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_DEF_BUF_LEN %d sizeof(HDLC_DEF_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_DEF_BUF_LEN, sizeof(HDLC_DEF_BUFF_INFO_STRU));
        return VOS_ERR;
    }

    /* TTF_HDLC_MASTER_FRM_BUF_LEN�ձ�����ṹHDLC_FRM_BUFF_INFO_STRU�Ĵ�Сһ�� */
    if (TTF_HDLC_MASTER_FRM_BUF_LEN != sizeof(HDLC_FRM_BUFF_INFO_STRU))
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_FRM_BUF_LEN %d sizeof(HDLC_FRM_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_FRM_BUF_LEN, sizeof(HDLC_FRM_BUFF_INFO_STRU));
        return VOS_ERR;
    }
    /*lint +e506 +e774*/

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnDefTraceInput
 ��������  : ��ȡ���װ����������������
 �������  : pstFrmBuffInfo -   ��װʹ�õ��ڴ�
             pstBuildInfo   -   �����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceInput
(
    HDLC_DEF_BUFF_INFO_STRU         *pstDefBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_DEF_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* ��¼���ϱ������������нڵ���������ݣ�ÿ���ڵ���һ��IP�� */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_DEF_INPUT_DATA, ulNodeLoop);

            /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
            PPP_HDLC_CACHE_FLUSH((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)), pstParaNode->usDataLen);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnDefTraceOutput
 ��������  : ��ȡ���װ�������
 �������  : pstBuildInfo    -   �����������
             usValidFrameNum -   ��Ч֡����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceOutput
(
    VOS_UINT16                          usValidFrameNum,
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo
)
{
    HDLC_MNTN_DEF_OUTPUT_PARA_STRU     *pstOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    VOS_UINT16                          usMaxFrameNum;


    /* ���װ�ϱ��ռ��ά�ɲ� */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        usMaxFrameNum = (HDLC_MNTN_ALLOC_MEM_MAX_SIZE - sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU)) /
                         sizeof(HDLC_DEF_RPT_NODE_STRU);
        usMaxFrameNum = TTF_MIN(usMaxFrameNum, usValidFrameNum);

        ulDataLen     = sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU) + usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU);
        pstOutputPara = (HDLC_MNTN_DEF_OUTPUT_PARA_STRU *)PS_MEM_ALLOC(PS_PID_PPP_HDLC, ulDataLen);

        if (VOS_NULL_PTR == pstOutputPara)
        {
            PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_MntnDefTraceOutput, NORMAL, Alloc mem failed ulDataLen %!\r\n", ulDataLen);
            return;
        }

        pstOutputPara->usDefValidNum = usValidFrameNum;
        pstOutputPara->usTraceNum    = usMaxFrameNum;

        VOS_MemCpy_s((VOS_UINT8 *)(pstOutputPara + 1),
                    usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU),
                   (VOS_UINT8 *)(&(pstDefBuffInfo->astRptNodeBuf[0])),
                   usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                   ID_HDLC_MNTN_DEF_OUTPUT_PARA, ulDataLen);

        PS_MEM_FREE(PS_PID_PPP_HDLC, pstOutputPara);
    }

    /* ���װĿ�Ŀռ���ÿ����Ч֡��ά�ɲ� */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usValidFrameNum; ulNodeLoop++ )
        {
            pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstRptNode->usDefOutOneLen, (VOS_UINT8*)PPP_HDLC_NODE_PHY_TO_VIRT((VOS_UINT32)(pstRptNode->pucDefOutOneAddr)),
                                              ID_HDLC_MNTN_DEF_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnFrmTraceInput
 ��������  : ��ȡ��װ����������������
 �������  : pstFrmBuffInfo -   ��װʹ�õ��ڴ�
             pstBuildInfo   -   �����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnFrmTraceInput
(
    HDLC_FRM_BUFF_INFO_STRU         *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_FRM_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* ��¼���ϱ������������нڵ���������ݣ�ÿ���ڵ���һ��IP�� */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_FRM_INPUT_DATA, ulNodeLoop);

            /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
            PPP_HDLC_CACHE_FLUSH((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)), pstParaNode->usDataLen);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_MntnFrmTraceOutput
 ��������  : ��ȡ��װ����������������
 �������  : ucFrmValidNum  -   ��Ч֡����
             usFrmOutSegNum -   ��Ч֡�ֶθ���
             pstFrmBuffInfo -   ��װ����ڴ��ַ
             pstBuildInfo   -   �����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnFrmTraceOutput
(
    VOS_UINT8                           ucFrmValidNum,
    VOS_UINT16                          usFrmOutSegNum,
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU     *pstBuildInfo
)
{
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU      stOutputPara;
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU     *pstOutputPara = &stOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        ulDataLen     = sizeof(HDLC_MNTN_FRM_OUTPUT_PARA_STRU);

        pstOutputPara->ulOutputLinkNodeCnt   = pstBuildInfo->ulOutputLinkNodeCnt;
        pstOutputPara->ulOutputLinkTotalSize = pstBuildInfo->ulOutputLinkTotalSize;
        pstOutputPara->ucFrmValidNum         = ucFrmValidNum;
        pstOutputPara->usOutputNodeUsedCnt   = usFrmOutSegNum;

        VOS_MemCpy_s((VOS_UINT8 *)(&(pstOutputPara->astOutputParaLinkNodeBuf[0])),
                    TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])),
                   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU));

        VOS_MemCpy_s((VOS_UINT8 *)(&(pstOutputPara->astRptNodeBuf[0])),
                    TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astRptNodeBuf[0])),
                   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                        ID_HDLC_MNTN_FRM_OUTPUT_PARA, ulDataLen);
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usFrmOutSegNum; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_FRM_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_CommReleaseInputData
 ��������  : �ͷŴ洢��PPP_ZC_STRU�ṹ
 �������  : ppstLinkNode   -- �洢PPP_ZC_STRUָ�������
             ulRelCnt       -- ���ͷŵĸ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_CommReleaseLink
(
    PPP_ZC_STRU     **ppstLinkNode,
    VOS_UINT32        ulRelCnt
)
{
    VOS_UINT32                          ulNodeLoop;


    for ( ulNodeLoop = 0; ulNodeLoop < ulRelCnt; ulNodeLoop++ )
    {
        PPP_MemFree(ppstLinkNode[ulNodeLoop]);

        ppstLinkNode[ulNodeLoop] = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefProcRptNode
 ��������  : �����ϱ���Ϣ��ַ�ͳ��ȣ������㿽���ڴ棬����������
 �������  : pstRptNode   -   �ϱ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
PPP_ZC_STRU * PPP_HDLC_HARD_DefProcRptNode
(
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          usFistSegLen;
    VOS_UINT8                          *pucDefOutOneAddr;


    if ( (0 == pstRptNode->usDefOutOneLen) || (HDLC_DEF_OUT_PER_MAX_CNT < pstRptNode->usDefOutOneLen) )
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_DefProcValidFrames, WARNING, invalid usDefOutOneLen %d\r\n",
                      pstRptNode->usDefOutOneLen);

        return VOS_NULL_PTR;
    }

    pstMem = PPP_MemAlloc(pstRptNode->usDefOutOneLen, PPP_ZC_UL_RESERVE_LEN);

    if (VOS_NULL_PTR == pstMem)
    {
        return VOS_NULL_PTR;
    }

    pucDefOutOneAddr    = (VOS_UINT8*)PPP_HDLC_NODE_PHY_TO_VIRT((VOS_UINT32)pstRptNode->pucDefOutOneAddr);
    /* �жϸ�֡��ʼ�ӳ����Ƿ񳬹�����ռ�β�����������ƻش��� */
    if ((pucDefOutOneAddr + pstRptNode->usDefOutOneLen) >
        HDLC_DEF_OUTPUT_BUF_END_ADDR)
    {
        if (pucDefOutOneAddr <= HDLC_DEF_OUTPUT_BUF_END_ADDR)
        {
            usFistSegLen = (VOS_UINT32)(HDLC_DEF_OUTPUT_BUF_END_ADDR - pucDefOutOneAddr);

            /* ��������ʼ��ַ������ռ�β�������� */
            PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucDefOutOneAddr,
                              usFistSegLen);

            /* ����������ռ��ײ���ʣ������ */
            PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem) + usFistSegLen, HDLC_DEF_OUTPUT_BUF_START_ADDR,
                              pstRptNode->usDefOutOneLen - usFistSegLen);
        }
        else
        {
            PPP_MemFree(pstMem);

            PPP_HDLC_ERROR_LOG2("\r\nPPP, PPP_HDLC_HARD_DefProcRptNode, ERROR, Error pucDefOutOneAddr.\r\n",
                    pucDefOutOneAddr, HDLC_DEF_OUTPUT_BUF_END_ADDR);

            PPP_HDLC_HARD_MntnShowDefReg();

            return VOS_NULL_PTR;
        }
    }
    else
    {
        PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucDefOutOneAddr,
                          pstRptNode->usDefOutOneLen);
    }

    /* �����㿽�����ݳ��� */
    PPP_ZC_SET_DATA_LEN(pstMem, pstRptNode->usDefOutOneLen);

    return pstMem;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefProcValidFrames
 ��������  : ������Ч֡
 �������  : ulMode       -   ģʽ��IP��PPP
             usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefProcValidFrames
(
    VOS_UINT32          ulMode,
        PPP_ID          usPppId,
    struct link        *pstLink
)
{
    VOS_UINT16                          usValidFrameNum;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulFrameLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    PPP_ZC_STRU                        *pstMem;


    pstDefBuffInfo  = HDLC_DEF_GET_BUF_INFO(usPppId);
    usValidFrameNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 23);

    /* �ϱ����װ�����ݿ�ά�ɲ�:�ϱ��ռ���Ϣ��������� */
    PPP_HDLC_HARD_MntnDefTraceOutput(usValidFrameNum, pstDefBuffInfo);

    /* ��Ч֡�����ֵ��� */
    if (TTF_HDLC_DEF_RPT_MAX_NUM < usValidFrameNum)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefProcValidFrames, WARNING, usValidFrameNum = %d > TTF_HDLC_DEF_RPT_MAX_NUM = %d",
                      usValidFrameNum, TTF_HDLC_DEF_RPT_MAX_NUM);
        return;
    }

    g_PppHdlcHardStat.ulDefMaxValidCntOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxValidCntOnce, usValidFrameNum);

    /* ��Ŀ�Ŀռ����Ч֡���ݿ������㿽���ڴ棬���ݲ������͵������з����ӿ� */
    for ( ulFrameLoop = 0 ; ulFrameLoop < usValidFrameNum; ulFrameLoop++ )
    {
        pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulFrameLoop]);

        pstMem = PPP_HDLC_HARD_DefProcRptNode(pstRptNode);

        /* ���벻�����ݻ��ϱ���Ϣ���󣬶�������Ч֡ */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        if (HDLC_IP_MODE == ulMode)
        {
            PPP_HDLC_ProcIpModeUlData(pstLink, pstMem, pstRptNode->usDefOutOnePro);
        }
        else
        {
            PPP_HDLC_ProcPppModeUlData(usPppId, pstMem);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefProcErrorFrames
 ��������  : �������֡
 �������  : pstLink    -   PPP��·��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefProcErrorFrames
(
    struct link        *pstLink
)
{
    VOS_UINT8                           ucErrType;
    VOS_UINT8                           ucMask;
    VOS_UINT32                          ulErrTypeLoop;
    VOS_UINT8                           ucResult;
    HDLC_DEF_ERR_FRAMES_CNT_STRU        stErrCnt;


    /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)�ĵ�24:30��Ӧ����λΪ1��ʾ��ĳ�ִ���֡�����
       Ϊ0��ʾ��֡��� */
    ucErrType = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR) , 24, 30);

    if (0 == ucErrType)
    {
        return;
    }

    /*lint -e734*/
    /* get fcs error count */
    stErrCnt.usFCSErrCnt        = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get frame too long error count */
    stErrCnt.usLenLongCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get frame too short error count */
    stErrCnt.usLenShortCnt      = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error protocol count */
    stErrCnt.usErrProtocolCnt   = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error control count */
    stErrCnt.usErrCtrlCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error address count */
    stErrCnt.usErrAddrCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error flag position count */
    stErrCnt.usFlagPosErrCnt    = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR), 0, 15);
    /*lint +e734*/
    for (ulErrTypeLoop = 0UL; ulErrTypeLoop < HDLC_DEF_MAX_TYPE_CNT; ulErrTypeLoop++)
    {
        ucMask   = SET_BITS_VALUE_TO_BYTE(0x01, ulErrTypeLoop);    /* �������� */
        ucResult = (VOS_UINT8)GET_BITS_FROM_BYTE(ucErrType, ucMask);

        if (0 != ucResult)      /* ���ڴ������ */
        {
            if (0UL == ulErrTypeLoop)   /* ��������0: CRCУ����� */
            {
                pstLink->hdlc.stats.badfcs       += stErrCnt.usFCSErrCnt;
                pstLink->hdlc.lqm.SaveInErrors   += stErrCnt.usFCSErrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc fcs\r\n");
            }
            else if (1UL == ulErrTypeLoop)    /* ��������1: ���װ��֡�ֽ�������1502bytes */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usLenLongCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame length too long\r\n");
            }
            else if (2UL == ulErrTypeLoop)    /* ��������2: ���װ��֡�ֽ���С��4bytes */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usLenShortCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame length too short\r\n");
            }
            else if (3UL == ulErrTypeLoop)    /* ��������3: ��P�������ʱ, �յ��Ƿ���Protocol��ֵ(��*******0 *******1��ʽ) */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrProtocolCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame protocol\r\n");
            }
            else if (4UL == ulErrTypeLoop)    /* ��������4: ��AC����ѹ��ʱ, Control��ֵ��0x03 */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrCtrlCnt;
                pstLink->hdlc.stats.badcommand += stErrCnt.usErrCtrlCnt;
                PPP_HDLC_NORMAL_LOG("bad hdlc frame control\r\n");
            }
            else if (5UL == ulErrTypeLoop)    /* ��������5: ��AC����ѹ��ʱ, Address��ֵ��0xFF */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrAddrCnt;
                pstLink->hdlc.stats.badaddr    += stErrCnt.usErrAddrCnt;
                PPP_HDLC_NORMAL_LOG("bad hdlc frame address\r\n");
            }
            else if (6UL == ulErrTypeLoop)    /* ��������6: ת���ַ�0x7D�����һ��Flag�� */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usFlagPosErrCnt;
                PPP_HDLC_NORMAL_LOG("bad hdlc frame flag position\r\n");
            }
            else
            {
                PPP_HDLC_NORMAL_LOG("link_HDLCDefDealErr err\r\n");
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefCfgReg
 ��������  : ���ý��װ���üĴ���
 �������  : ulMode     -   IP��PPPģʽ
             pstLink    -   PPP��·��Ϣ
             pstDefUncompletedInfo  -   ��·PPP�����ϴν��װ���������֡��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefCfgReg
(
    VOS_UINT32                      ulMode,
    struct link                    *pstLink,
    HDLC_DEF_UNCOMPLETED_INFO_STRU *pstDefUncompletedInfo
)
{
    /*
        hdlc_def_cfg  (0x70)
         31                           4 3     2   1     0
        |-------------------------------|-------|-----|-----|
        |              Rsv              |  Pfc  | Acfc| ago |
        Reserved             [31:4]  28'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��P����ѹ��������룻01��P��ѹ��������룻11��P�򲻰��룻��������Ч��
        def_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ����1����ʾAC��ѹ����
        def_uncompleted_ago  [0]     1'b0    h/s R/W  ����ָʾ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ���������Ƿ��н��������֡��
                                                      Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����
        */

    VOS_UINT32       ulDeframerCfg;
    VOS_UINT8        ucACComp;
    VOS_UINT8        ucPComp;
    VOS_UINT8        ucLowByte;
    VOS_UINT16       usLowWord;

    /* 1.����ulMode��P���AC���Ƿ�ѹ������hdlc_def_cfg (0x70) */

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ */
    ucACComp = (1 == pstLink->lcp.want_acfcomp) ? 1 : 0;

    if (HDLC_IP_MODE == ulMode) /* IPģʽ: P�򲻺��� */
    {
        ucPComp = (1 == pstLink->lcp.want_protocomp)
                   ? HDLC_PROTOCOL_REMOVE_WITH_COMPRESS
                   : HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS;
    }
    else                        /* PPPģʽ: P����� */
    {
        ucPComp = HDLC_PROTOCOL_NO_REMOVE;
    }

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_DEF_PFC_BITPOS);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_ACFC_BITPOS);
    }

    /* 2.���÷�����֡�����Ϣ */
    if ( (VOS_NULL_PTR != pstDefUncompletedInfo) &&
        (HDLC_DEF_UNCOMPLETED_EXIST == pstDefUncompletedInfo->ucExistFlag) )
    {
        /* def_uncompleted_ago��1��ʾ���ϴ�����ķ�����֡���뱾�ν��װ */
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS);

        /*
        def_uncompleted_len  (0x74)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Len          |
        Reserved             [31:16] 16'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_uncompleted_len  [15:0]  16'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡�ĳ��ȣ�Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ�����
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOneLen & 0xFFFF);

        /*
        def_uncompleted_pro  (0x78)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Pro          |
        Reserved             [31:16] 16'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_uncompleted_pro  [15:0]  16'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��
                                                      Э�飬Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��������е�0Byte��1Byte��2Byte��Ч��
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOnePro & 0xFFFF);

        /*
        def_uncompleted_addr  (0x7C)
         31                  0
        |----------------------|
        |         Addr         |
        def_uncompleted_addr [31:0]  32'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��
                                                      �ⲿ�洢��ʼ��ַ��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��õ�ַ��������ԭ���ϱ���ͬ���µ�ַ��
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->pucDefOutOneAddr);

        /*
        def_uncomplet_st_ago  (0x80)
         31                  16 15             5 4     0
        |----------------------|----------------|-------|
        |         Ago          |       Rsv      |  Ago  |
        crc16_result_ago     [31:16] 16'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��CRCУ��ֵ
        Reserved             [15:5]  11'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_data_st_curr_ago [4:0]   5'b0    h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ������״̬����ǰ״̬
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefStAgo);

        /*
        def_info_frl_cnt_ago  (0xC0)
         31        27 26                 16 15   11 10              0
        |------------|---------------------|-------|-----------------|
        |    Rsv     |         Ago         |  Rsv  |       Ago       |
        Reserved             [31:27] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_framel_cnt_ago   [26:16] 11'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��֡����
        Reserved             [15:11] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_info_cnt_ago     [10:0]  11'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ����Ϣ����
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefInfoFrlCntAgo);
    }

    usLowWord     = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulDeframerCfg = HDLC_MAKE_DWORD(0x00, usLowWord);

    /* �����ý��д��Ĵ��� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR),ulDeframerCfg);

    /* ��������������󵥰����� */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)HDLC_DEF_IN_PER_MAX_CNT);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefSaveUncompletedInfo
 ��������  : ���ݷ�����ָ֡ʾ�����������֡��Ϣ
 �������  : usPppId    -   PPPʵ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefSaveUncompletedInfo
(
    PPP_ID          usPppId
)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo;
    VOS_UINT32                          ulStatus;                /* ���װ״̬ */
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulValidNum;
    VOS_UINT8                          *pucDefOutOneAddr;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;


    pstDefBuffInfo     = HDLC_DEF_GET_BUF_INFO(usPppId);
    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    ulStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)�ĵ�2λ
       Ϊ1��ʾ���ν��װ�з�����֡�����
       Ϊ0��ʾ�޷�����֡��� */
    if (0 == (ulStatus & 0x4))
    {
        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    g_PppHdlcHardStat.ulDefUncompleteCnt++;

    /* def_valid_num        [23:8]  16'b0   h/s RO   ��֡�ϱ�ʱ����Ч֡��Ŀ�������������һ�����ܵķ�����֡�� */
    ulValidNum = (ulStatus & 0xFFFF00) >> 8;

    /* ������֡���ϱ���Ϣ����Ч֡���棬���ǲ�������Ч֡��Ŀ�� */
    if (TTF_HDLC_DEF_RPT_MAX_NUM <= ulValidNum)
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_DefSaveUncompletedInfo, ERROR, ulValidNum %d >= TTF_HDLC_DEF_RPT_MAX_NUM %d!\r\n",
                     ulValidNum, TTF_HDLC_DEF_RPT_MAX_NUM);

        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    /* �з�����֡ʱ��Ҫ��ȡ������def_uncomplet_st_now(0x8C)��def_info_frl_cnt_now(0xC4)
       ��ȡ�������ϱ��ռ���Ч֮֡��ķ�����֡���ȡ�Э������ݵ�ַ */
    pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_EXIST;

    pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulValidNum]);

    pucDefOutOneAddr = (VOS_UINT8*)PPP_HDLC_NODE_PHY_TO_VIRT((VOS_UINT32)pstRptNode->pucDefOutOneAddr);


    if (pucDefOutOneAddr != HDLC_DEF_OUTPUT_BUF_START_ADDR)
    {
        if ((pucDefOutOneAddr - HDLC_DEF_OUTPUT_BUF_START_ADDR) >= pstRptNode->usDefOutOneLen)
        {
            mdrv_memcpy(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
        else
        {
            PS_MEM_MOVE(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
#ifndef PPP_ST_TEST
        pstRptNode->pucDefOutOneAddr = (VOS_UINT8*)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)HDLC_DEF_OUTPUT_BUF_START_ADDR);
#endif
    }


    /* ������֡��Э�顢���Ⱥ��ڴ洢�ռ�ĵ�ַ�����ֻ���ݴ���Щ��Ϣ�����½��װ��ʱ����ԭ�����HDLC */
    pstUncompletedInfo->usDefOutOnePro   = pstRptNode->usDefOutOnePro;
    pstUncompletedInfo->usDefOutOneLen   = pstRptNode->usDefOutOneLen;
    pstUncompletedInfo->pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;

    /* ���ֻ���ݴ���Щ��Ϣ�����½��װ��ʱ����ԭ�����HDLC */
    pstUncompletedInfo->ulDefStAgo         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstUncompletedInfo->ulDefInfoFrlCntAgo = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    PPP_HDLC_HARD_MntnDefTraceUncompleteInfo(pstUncompletedInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefWaitAndProc
 ��������  : �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ���
 �������  : ulMode     -   ģʽ��IP��PPP
             ulEnableInterrupt  -   �ж��Ƿ�ʹ��
             usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefWaitAndProc
(
    VOS_UINT32          ulMode,
    VOS_UINT32          ulEnableInterrupt,
    PPP_ID              usPppId,
    struct link        *pstLink
)
{
    VOS_UINT32                          ulDefStatus;
    VOS_UINT32                          ulContinue;

    for (; ;)
    {
        /* ʹ���жϣ���ȴ��жϸ������ͷ��ź�����������ѯ���װ״̬�Ĵ��� */
        ulDefStatus = PPP_HDLC_HARD_DefWaitResult(ulEnableInterrupt);

        switch ( ulDefStatus )
        {
            case HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL :
            case HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL :
                /* ������Ч֡������GO_ON�Ĵ��� */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefFullPauseCnt++;
                break;
            case HDLC_DEF_STATUS_PAUSE_LCP :
                /* ������Ч֡��LCP֡���������üĴ���������GO_ON�Ĵ��� */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefCfgReg(ulMode, pstLink, VOS_NULL_PTR);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefLcpPauseCnt++;
                break;
            case HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES :
                /* ���ݷ�����ָ֡ʾ�����������֡��Ϣ */
                PPP_HDLC_HARD_DefSaveUncompletedInfo(usPppId);

                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DONE_WITH_FRAMES :
                /* ������Ч֡������֡��LCP֡(���������һ֡)�����ݷ�����ָ֡ʾ�����������֡��Ϣ */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefProcErrorFrames(pstLink);
                PPP_HDLC_HARD_DefSaveUncompletedInfo(usPppId);
                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DOING :
            default:
                /* ��ӡ�쳣��־������PPP���� */
                PPP_HDLC_HARD_DefProcException(ulDefStatus, ulEnableInterrupt);

                ulContinue = VOS_FALSE;
                break;
        }

        /* ��ͣ״̬��Ҫ������������״̬���װ����˳� */
        if (VOS_TRUE != ulContinue)
        {
            break;
        }
    }

    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = 0xFFFFFFFFU;

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefCheckPara
 ��������  : ��鹹���������������ز����Ƿ�Ϸ�
 �������  : pstMem     -   ����װ���ݰ�
             ulDataLen  -   ����װ���ݰ�����
             ucDataType -   ����װ���ݰ�����
 �������  : ��
 �� �� ֵ  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPP_HDLC_HARD_DefCheckPara
(
    PPP_ZC_STRU                 *pstMem,
    VOS_UINT32                   ulDataLen,
    PPP_DATA_TYPE_ENUM_UINT8     ucDataType
)
{
    PPP_DATA_TYPE_ENUM_UINT8     ucCurrDataType;


    /* ��ȡ����װ���ݰ����� */
    ucCurrDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

    if ( ucDataType != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    /* ���װ������볤�����ڴ�ģ���������󳤶ȣ�Ŀǰ��1536B */
    /* ���HDLC Bug�ڴ��������1 */
    if ( (0 == ulDataLen) || (PPP_ZC_MAX_DATA_LEN < ulDataLen) )
    {
        PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_DefCheckPara, NORMAL, invalid data length %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}


/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_ForbiddenHdlcBug
 ��������  : ���HDLCӲ��Bug,����μ����ⵥDTS2014060907737
 �������  : ppstMem     -   �����װ���ݰ�ָ��

 �������  : ppstMem  ���֮������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��17��
    ��    ��   : t00148005
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_ForbiddenHdlcBug(PPP_ZC_STRU **ppstMem)
{
    PPP_ZC_STRU *pstMem;
    PPP_ZC_STRU *pstTmpMem;
    VOS_UINT8   *pstData;
    VOS_UINT16   usLen;
    const VOS_UINT8    ucEndByte = 0x7e;

    pstMem  = *ppstMem;

    if (VOS_NULL_PTR == pstMem)
    {
        return;
    }

    usLen   = PPP_ZC_GET_DATA_LEN(pstMem);
    pstData = PPP_ZC_GET_DATA_PTR(pstMem);

    if (usLen <= 1)
    {
        return;
    }

    if (ucEndByte != pstData[usLen - 2])
    {
        /* �����ڶ����ֽڲ�Ϊ7e���ô��� */
        return;
    }
    else if ((usLen >= 3) && (ucEndByte == pstData[usLen - 3]))
    {
        /* �����������ֽ�Ϊ7e���ô��� */
        return;
    }
    else
    {
        /*
            �����ڶ����ֽ�Ϊ7e,�����������ֽڲ�Ϊ7e�ĳ���
            �����һ���ֽں�����һ���ֽ�,ͬʱ�ڴ�ĳ���+1

            skb������ڴ�ṹ����
           |--------data(uslen)--------|----32bytes align(0~31)-----|--skb_share_info(256)----|
        */
        if (PPP_ZC_GET_RESERVE_ROOM(pstMem) > 0)
        {
            INSERT_BYTE_LAST(pstMem, pstData, usLen, ucEndByte);
            g_PppHdlcHardStat.ulForbidHdlcBugNoCpy++;
        }
        else
        {
            /* ����һ������1�ֽڵ��ڴ� */

            pstTmpMem = PPP_MemAlloc(usLen + 1, 0);
            if (VOS_NULL_PTR != pstTmpMem)
            {
                PPP_MemWriteData(pstTmpMem, pstData, usLen);

                pstData = PPP_ZC_GET_DATA_PTR(pstTmpMem);

                INSERT_BYTE_LAST(pstTmpMem, pstData, usLen, ucEndByte);
                g_PppHdlcHardStat.ulForbidHdlcBugCpy++;
            }

            /* ������������ڴ��Ƿ�Ϊ�ն�����ȥ,�����洦�� */
            *ppstMem = pstTmpMem;

            /* ��ԭ�ڴ��ͷ� */
            PPP_MemFree(pstMem);
        }
    }
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefBuildInputParaLink
 ��������  : ������װ�����������
 �������  : pstBuildPara   -   ������������Ĳ���
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefBuildInputParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU  *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                              ulLinkLoop;
    PPP_ZC_STRU                            *pstMem;
    PPP_DATA_TYPE_ENUM_UINT8                ucDataType;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT16                              usDataLen;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex;
    HDLC_DEF_BUFF_INFO_STRU                *pstDefBuffInfo;
    HDLC_DEF_UNCOMPLETED_INFO_STRU         *pstUncompletedInfo;
    VOS_UINT32                              ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE;


    /* ��������Ϣ */
    VOS_MemSet_s(pstBuildInfo, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU),
                 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(pstBuildPara->usPppId);

    if (HDLC_DEF_UNCOMPLETED_EXIST == pstUncompletedInfo->ucExistFlag)
    {
        ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE - pstUncompletedInfo->usDefOutOneLen;
    }


    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(pstBuildPara->usPppId);
    ucDataType     = pstBuildPara->ucDataType;

    for ( ulLinkLoop = 0 ; ulLinkLoop < TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM; ulLinkLoop++ )
    {
        pstMem     = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstBuildPara->pstDataQ);

        /* ��û�е����ڵ��������Ƕ������Ѿ�û������ */
        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usDataLen     = PPP_ZC_GET_DATA_LEN(pstMem);
        enCheckResult = PPP_HDLC_HARD_DefCheckPara(pstMem, usDataLen, ucDataType);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);
            PPP_MemFree(pstMem);
            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulDefInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }


        /* ��PPP����ȡ��ͷ��㣬������������� pstBuildInfo->apstInputLinkNode */
        pstMem  = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);

        /* ���HDLC BUG,�ڷ���HDLC BUG�����¶�ԭ�����ݽ����滻,
           �����pstMemΪ�滻����ڴ�ָ��,ԭʼ�ڴ�ָ������Ѿ����ͷ�
         */
        PPP_HDLC_HARD_ForbiddenHdlcBug(&pstMem);

        /* �滻�ڴ��ʱ�������ڴ�ʧ��,ֱ�Ӵ�����һ������  */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        /* �ڴ���ܷ����滻,����ȡ���� */
        usDataLen = PPP_ZC_GET_DATA_LEN(pstMem);

        /* һ������������д���װ���ݰ��ܳ����ܳ���15KB */
        /* ���HDLC BUG,�������ݱ��޸Ĺ�,����������1�ֽ�,��Ҫ�ŵ������ж� */
        if( pstBuildInfo->ulInputLinkTotalSize + usDataLen  > ulMaxDataLen1Time )
        {
            /* �ڴ�Żض���,�´��ٴ��� */
            PPP_ZC_ENQUEUE_HEAD(pstBuildPara->pstDataQ, pstMem);

            break;
        }

        /* ��ȡ��ǰҪ��ӽڵ���±� */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* ����Ҫ����Ĳ����ڵ� */
        pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* �ѽڵ�������� */
        if( 0 != ulNodeIndex )
        {
            pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU *)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)pstParaNode);
        }

        /* ��д������������������ */
        pstParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT_PTR)PPP_ZC_GET_DATA_PTR(pstMem));
        pstParaNode->usDataLen   = usDataLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usDataLen;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;

        /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
        PPP_HDLC_CACHE_FLUSH(PPP_ZC_GET_DATA_PTR(pstMem), PPP_ZC_GET_DATA_LEN(pstMem));
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        return VOS_ERR;
    }

    /* �ϱ���������������ݿ�ά�ɲ� */
    PPP_HDLC_HARD_MntnDefTraceInput(pstDefBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/************************************************************,*****************
 �� �� ��  : PPP_HDLC_HARD_DefCfgBufReg
 ��������  : ���ý��װʹ�õ��ڴ�����ؼĴ���
 �������  : pstDefBuffInfo    -   ���װʹ�õ��ڴ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefCfgBufReg(HDLC_DEF_BUFF_INFO_STRU *pstDefBuffInfo)
{
    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_in_lli_addr(0x90) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->astInputParaLinkNodeBuf[0])));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_out_spc_addr(0xA0) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->aucOutputDataBuf[0])));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_out_space_dep(0xA4)��16λ */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN & 0xFFFF);

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ���ʼ��ַ���ø��Ĵ���def_rpt_addr(0xA8) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->astRptNodeBuf[0])));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ�������ø��Ĵ���def_rpt_dep (0xAC)��16λ */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefPacket
 ��������  : Ӳ����ʽIP���ͽ��װ
 �������  : usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
             pstDataQ   -   PPP���ݶ���
             ulDealCnt  -   ���δ������ݰ�����
 �������  : �μ�PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefPacket
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    stBuildPara.ucDataType = PPP_PULL_PACKET_TYPE;
    stBuildPara.usProtocol = PROTO_IP;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult = PPP_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_DefPacket, WARNING, BuildParaLink Fail.\r\n");
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* ����ѹ��ָʾ��������֡�����Ϣ�Ĵ��� */
    PPP_HDLC_HARD_DefCfgReg(HDLC_IP_MODE, pstLink, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ��� */
    PPP_HDLC_HARD_DefWaitAndProc(HDLC_IP_MODE, ulEnableInterrupt, usPppId, pstLink);

    /* �ͷ��ѽ��װ��ɵ����� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_DefRawData
 ��������  : Ӳ����ʽPPP���ͽ��װ
 �������  : usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
             pstDataQ   -   PPP���ݶ���
             ulDealCnt  -   ���δ������ݰ�����
 �������  : �μ�PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefRawData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    VOS_MemSet_s(&stBuildInfo, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU),
                 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    stBuildPara.ucDataType = PPP_PULL_RAW_DATA_TYPE;
    stBuildPara.usProtocol = PROTO_IP;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult = PPP_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* ����ѹ��ָʾ��������֡�����Ϣ�Ĵ��� */
    PPP_HDLC_HARD_DefCfgReg(HDLC_PPP_MODE, pstLink, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ��� */
    PPP_HDLC_HARD_DefWaitAndProc(HDLC_PPP_MODE, ulEnableInterrupt, usPppId, pstLink);

    /* �ͷ��ѽ��װ��ɵ����� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmUpdateLink
 ��������  : ����һ���ڴ�����������ؽṹ��Ϣ
 �������  : ulAllocMemCnt      - ����������ڴ�����
             aulAllocLen        - ��¼��������ĸ����ڴ��ĳ���
             papstAllocedMem    - ��¼��������ĸ����ڴ����ƽṹָ��
             pstBuildPara       -   ������������Ĳ���
 �������  : pstBuildInfo       -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmUpdateLink
(
    VOS_UINT32                      ulAllocMemCnt,
    VOS_UINT32 *                    aulAllocLen,
    PPP_ZC_STRU                   **ppstAllocedMem,
    HDLC_PARA_LINK_BUILD_PARA_STRU *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU *pstBuildInfo
)
{
    VOS_UINT32                          ulMemLoop;
    VOS_UINT32                          ulNodeIndex;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaNode;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo          = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);

    if( (pstBuildInfo->ulOutputLinkNodeCnt + ulAllocMemCnt) > TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM )
    {
        g_PppHdlcHardStat.ulFrmOutputLinkFullCnt++;

        PPP_HDLC_HARD_CommReleaseLink(ppstAllocedMem, ulAllocMemCnt);

        return VOS_ERR;
    }

    /* ����Ŀ�Ŀռ����� apstOutputLinkNode�������ͷ�Ŀ�Ŀռ� */
    VOS_MemCpy_s(&(pstBuildInfo->apstOutputLinkNode[pstBuildInfo->ulOutputLinkNodeCnt]),
               ulAllocMemCnt * sizeof(PPP_ZC_STRU *),
               &(ppstAllocedMem[0]),
               ulAllocMemCnt * sizeof(PPP_ZC_STRU *));

    /* ����װ�������������ĸ�����Ա��ֵ */
    for ( ulMemLoop = 0; ulMemLoop < ulAllocMemCnt; ulMemLoop++ )
    {
        ulNodeIndex = pstBuildInfo->ulOutputLinkNodeCnt;

        pstOutputParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex]);

        /* �����ϸ���������������pstNextNode�� */
        if (0 != ulNodeIndex)
        {
            pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)pstOutputParaNode);
        }

        pstOutputParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT_PTR)PPP_ZC_GET_DATA_PTR(ppstAllocedMem[ulMemLoop]));
        pstOutputParaNode->usDataLen   = (VOS_UINT16)aulAllocLen[ulMemLoop];
        pstOutputParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->ulOutputLinkNodeCnt++;
        pstBuildInfo->ulOutputLinkTotalSize += aulAllocLen[ulMemLoop];

        PPP_HDLC_CACHE_INVALID((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstOutputParaNode->pucDataAddr)), pstOutputParaNode->usDataLen);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_OutputMemAlloc
 ��������  : ��װ���Ŀ�Ŀռ�����
 �������  : usLen          -   ��������ڴ泤��
             pstBuildPara   -   ������������Ĳ���
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmOutputMemAlloc
(
    VOS_UINT16                           usLen,
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT16                  usFrmedMaxLen;                                  /* ��װ��Ŀ��ܵ���󳤶� */
    VOS_UINT16                  usAllocLen;
    VOS_UINT32                  ulAllocLoop;
    VOS_UINT32                  ulLoopCnt;
    VOS_UINT32                  ulAllocMemCnt;                                  /* ����������ڴ���� */
    VOS_UINT32                  aulAllocLen[HDLC_OUTPUT_PARA_LINK_MAX_SIZE];    /* ��¼��������ĸ����ڴ�鳤�� */
    PPP_ZC_STRU *               apstAllocedMem[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* ��¼��������ĸ����ڴ��ָ�� */
    PPP_ZC_STRU                *pstMem;


    /* ��װ����ܵ�������ݳ���(2*ԭʼ���ݳ���+13B) */
    usFrmedMaxLen = (VOS_UINT16)HDLC_FRM_GET_MAX_FRAMED_LEN(usLen);
    ulAllocMemCnt = 0;
    ulLoopCnt     = TTF_CEIL(usFrmedMaxLen, PPP_ZC_MAX_DATA_LEN);

    for ( ulAllocLoop = 0 ; ulAllocLoop < ulLoopCnt; ulAllocLoop++ )
    {
        if (ulAllocLoop != (ulLoopCnt - 1) )
        {
            usAllocLen = PPP_ZC_MAX_DATA_LEN;
        }
        else
        {
            usAllocLen = (VOS_UINT16)(usFrmedMaxLen - ulAllocLoop*PPP_ZC_MAX_DATA_LEN);
        }

        pstMem = PPP_MemAlloc(usAllocLen, PPP_ZC_DL_RESERVE_LEN);

        if (VOS_NULL_PTR == pstMem)
        {
            break;
        }

        ulAllocMemCnt++;
        aulAllocLen[ulAllocLoop]    = usAllocLen;
        apstAllocedMem[ulAllocLoop] = pstMem;
    }

    /* ����������ڴ�ʧ�ܵ���������ͷű����Ѿ�������ڴ� */
    if (ulLoopCnt > ulAllocMemCnt)
    {
        PPP_HDLC_HARD_CommReleaseLink(&(apstAllocedMem[0]), ulAllocMemCnt);
        return VOS_ERR;
    }

    return PPP_HDLC_HARD_FrmUpdateLink(ulAllocMemCnt,
                                       &(aulAllocLen[0]), &(apstAllocedMem[0]),
                                       pstBuildPara, pstBuildInfo);
}


/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmGetProtocol
 ��������  : PPPģʽ�»�ȡ����װ���ݰ�Э��ֵ
 �������  : pstMem         -   ����װ���ݰ�
 �������  : pusProtocol    -   ����װ���ݰ�Э��ֵ
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmGetProtocol
(
    PPP_ZC_STRU     *pstMem,
    VOS_UINT16      *pusProtocol
)
{
    VOS_UINT8           aucProto[2] = {0, 0};
    VOS_UINT32          ulRtn;


    ulRtn = PPP_MemGet(pstMem, 0, aucProto, 2);

    if ( PS_FAIL == ulRtn )
    {
        return VOS_ERR;
    }

    if ( 0x01 == GET_BITS_FROM_BYTE(aucProto[0], 0x01) )
    {
        *pusProtocol = HDLC_MAKE_WORD(0x00, aucProto[0]);
    }
    else
    {
        if ( 0x01 == GET_BITS_FROM_BYTE(aucProto[1], 0x01) )
        {
            *pusProtocol = HDLC_MAKE_WORD(aucProto[0], aucProto[1]);
        }
        else
        {
            PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmGetProtocol, Warning, PPP mode framer data protocol error\r\n");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmBuildParaLink
 ��������  : ��鹹�������������������ز����Ƿ�Ϸ�
 �������  : pstMem     -   ����װ���ݰ�
             ulDataLen  -   ����װ���ݰ�����
             ucDataType -   ����װ���ݰ�����
             usProtocol -   ����װ���ݰ�Э������
 �������  : ��
 �� �� ֵ  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPP_HDLC_HARD_FrmCheckPara
(
    PPP_ZC_STRU                 *pstMem,
    VOS_UINT32                   ulDataLen,
    PPP_DATA_TYPE_ENUM_UINT8     ucDataType,
    VOS_UINT16                   usProtocol
)
{
    PPP_DATA_TYPE_ENUM_UINT8     ucCurrDataType;
    VOS_UINT32                   ulRlst;
    VOS_UINT16                   usCurrProtocol;


    /* ��ȡ����װ���ݰ����� */
    ucCurrDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

    if ( ucDataType != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    /* ����װ���ݰ������쳣 */
    if ( (0 == ulDataLen) || (HDLC_FRM_IN_PER_MAX_CNT < ulDataLen) )
    {
        PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_FrmCheckPara,IP mode framer data len wrong %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* �������PPPģʽ */
    if( PPP_PUSH_RAW_DATA_TYPE != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_PASS;
    }

    ulRlst  = PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usCurrProtocol);

    if( VOS_OK != ulRlst )
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmCheckPara, Warning, PPP mode get framer data protocol error\r\n");
        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* ��֤һ���������ù����з�װЭ��ֵһ�� */
    if( usProtocol != usCurrProtocol )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmBuildParaLink
 ��������  : ����������������������ϱ������ڴ��ά�ɲ�
 �������  : pstBuildPara   -   ������������Ĳ���
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmBuildParaLink
(
 HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
 HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
 )
{
    PPP_ZC_STRU                             *pstMem;
    VOS_UINT32                               ulLoop;
    VOS_UINT16                               usUnFrmLen;
    VOS_UINT32                               ulAllocResult;
    HDLC_PARA_LINK_NODE_STRU                *pstParaNode;
    VOS_UINT32                               ulNodeIndex;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32   enCheckResult;
    VOS_UINT32                               ulAllocMemFail;
    HDLC_FRM_BUFF_INFO_STRU                 *pstFrmBuffInfo;


    VOS_MemSet_s(pstBuildInfo, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU),
                 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);
    ulAllocMemFail = VOS_FALSE;

    for(ulLoop = 0; ulLoop < TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM; ulLoop++)
    {
        pstMem = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstBuildPara->pstDataQ);

        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usUnFrmLen    = PPP_ZC_GET_DATA_LEN(pstMem);
        enCheckResult = PPP_HDLC_HARD_FrmCheckPara(pstMem, usUnFrmLen,
                                                   pstBuildPara->ucDataType,
                                                   pstBuildPara->usProtocol);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);
            PPP_MemFree(pstMem);
            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulFrmInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* һ������������д���װ���ݰ��ܳ����ܳ���15KB */
        if( pstBuildInfo->ulInputLinkTotalSize + usUnFrmLen > TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE )
        {
            break;
        }

        /* �����װĿ�Ŀռ� */
        ulAllocResult = PPP_HDLC_HARD_FrmOutputMemAlloc(usUnFrmLen, pstBuildPara, pstBuildInfo);

        if( VOS_OK != ulAllocResult )
        {
            ulAllocMemFail = VOS_TRUE;

            g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt++;
            break;
        }

        /* ��PPP����ȡ��ͷ��㣬������������� pstBuildInfo->apstInputLinkNode */
        pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);

        /* ��ȡ��ǰҪ��ӽڵ���±� */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* ����Ҫ����Ĳ����ڵ� */
        pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* ��д������������������ */
        if( 0 != ulNodeIndex )
        {
            pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)pstParaNode);
        }

        pstParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT_PTR)PPP_ZC_GET_DATA_PTR(pstMem));
        pstParaNode->usDataLen   = usUnFrmLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usUnFrmLen;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;

        /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
        PPP_HDLC_CACHE_FLUSH(PPP_ZC_GET_DATA_PTR(pstMem), PPP_ZC_GET_DATA_LEN(pstMem));
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        if (VOS_TRUE == ulAllocMemFail)
        {
            /* �ȴ�һ��ʱ������³��������ڴ��ٷ�װ */
            PPP_HDLC_HARD_FrmStartTimer(pstBuildPara);

            g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt++;
        }

        return VOS_ERR;
    }

    /* ��������������������ݿ�ά�ɲ� */
    PPP_HDLC_HARD_MntnFrmTraceInput(pstFrmBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmCfgBufReg
 ��������  : ���÷�װʹ�õ��ڴ�����ؼĴ���
 �������  : pstFrmBuffInfo -   ��װʹ�õ��ڴ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmCfgBufReg(HDLC_FRM_BUFF_INFO_STRU *pstFrmBuffInfo)
{
    /* ����װ��������������ʼ��ַ���ø��Ĵ���frm_in_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astInputParaLinkNodeBuf[0])));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���frm_out_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ���ʼ��ַ���ø��Ĵ���frm_rpt_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astRptNodeBuf[0])));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ�������ø��Ĵ���frm_rpt_dep��[15:0]λ */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_FRM_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmCfgReg
 ��������  : IPģʽ�����÷�װ��ؼĴ���
 �������  : pstLink    - PPP��·��Ϣ
             usProtocol - ����װ��Э��ֵ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmCfgReg
(
    struct link        *pstLink,
    VOS_UINT16          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  ��װЭ��ֵ����ЧЭ��ֵ�涨�μ�����б�
    Reserved             [15:4]  12'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��Ӳ��ģ�����P��P����ѹ��;
                                                               01��Ӳ��ģ�����P��P��ѹ��;
                                                               11��Ӳ��ģ�鲻���P��;
                                                               ��������Ч;
    frm_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ��;1����ʾAC��ѹ��;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  ��װ����һά���ά����ѡ��ָʾ�Ĵ�����
                                                                0Ϊһά;1Ϊ��ά;

    IPģʽһ�����P��,PPPģʽһ�������P��
      LCP֡: AC��ѹ����P��ѹ��
    */

    VOS_UINT32              ulFrmCfg;


    /* ���Ĵ���hdlc_frm_cfg��[0]λfrm_in_lli_1dor2d����Ϊ0 */
    ulFrmCfg = 0x0;

    /* ����hdlc_frm_cfg�� P��� AC�� */
    if (PROTO_LCP != usProtocol)
    {
        if ( 1 == pstLink->lcp.his_acfcomp )
        {
            ulFrmCfg |= (1 << HDLC_FRM_ACFC_BITPOS);
        }

        if ( 1 == pstLink->lcp.his_protocomp )
        {
            ulFrmCfg |= (1 << HDLC_FRM_PFC_BITPOS);
        }

        /* ����hdlc_frm_accm */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),
                            pstLink->lcp.his_accmap);
    }
    else
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    }

    /* ���üĴ���hdlc_frm_cfg��[31:16]λfrm_protocolΪusProtocol */
    ulFrmCfg |= ( ((VOS_UINT32)usProtocol) << 16 );

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR), ulFrmCfg);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmCfgReg
 ��������  : PPPģʽ�����÷�װ��ؼĴ���
 �������  : pstLink    - PPP��·��Ϣ
             usProtocol - ����װ��Э��ֵ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmRawCfgReg
(
    struct link        *pstLink,
    VOS_UINT16          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  ��װЭ��ֵ����ЧЭ��ֵ�涨�μ�����б�
    Reserved             [15:4]  12'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��Ӳ��ģ�����P��P����ѹ��;
                                                               01��Ӳ��ģ�����P��P��ѹ��;
                                                               11��Ӳ��ģ�鲻���P��;
                                                               ��������Ч;
    frm_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ��;1����ʾAC��ѹ��;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  ��װ����һά���ά����ѡ��ָʾ�Ĵ�����
                                                                0Ϊһά;1Ϊ��ά;

    IPģʽһ�����P��,PPPģʽһ�������P��
      LCP֡: AC��ѹ����P��ѹ��
    */

    VOS_UINT32              ulFrmCfg;
    /*PS_BOOL_ENUM_UINT8      enPComp;       �Ƿ�ѹ��Э���ֶ�, �� - PS_TRUE */
    PS_BOOL_ENUM_UINT8      enACComp;     /* �Ƿ�ѹ����ַ�Ϳ����ֶ�, �� - PS_TRUE */
    VOS_UINT32              ulACCM;
    VOS_UINT8               ucACComp;
    VOS_UINT8               ucPComp;
    VOS_UINT8               ucLowByte;
    VOS_UINT16              usLowWord;


    /* ���Ĵ���hdlc_frm_cfg��[0]λfrm_in_lli_1dor2d����Ϊ0 */
    ulFrmCfg    = 0x0;

    if (PROTO_LCP == usProtocol)
    {
        /* LCP֡P��ѹ��, AC��ѹ��, ACCMΪȫת�� */
        /*enPComp     = PS_FALSE; */
        enACComp    = PS_FALSE;
        ulACCM      = 0xFFFFFFFFU;
    }
    else
    {
        /* ʹ��Ĭ��ֵ */
        /*enPComp     = (1 == pstLink->lcp.his_protocomp) ? PS_TRUE : PS_FALSE; */
        enACComp    = (1 == pstLink->lcp.his_acfcomp) ? PS_TRUE : PS_FALSE;
        /* ����PPP���Ų�֪��ACCM, ������ΪЭ��Ĭ��ֵ */
        ulACCM      = 0xFFFFFFFFU;
    }

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ, Э��ֵ, ACCM */
    ucACComp = (PS_TRUE == enACComp) ? 1 : 0;
    ucPComp = HDLC_PROTOCOL_NO_ADD;

    /* ����accm */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),ulACCM);

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_FRM_PFC_BITPOS);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_FRM_ACFC_BITPOS);
    }
    else
    {
        CLEAR_BIT_TO_BYTE(ucLowByte, HDLC_FRM_ACFC_BITPOS);
    }

    usLowWord   = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulFrmCfg    = HDLC_MAKE_DWORD(usProtocol, usLowWord);

    /* ����AC��ѹ��ָʾ, P��ѹ��ָʾ, Э��ֵ��ʹ�ܷ�װ���, accm */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR),ulFrmCfg);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmProcValidFram
 ��������  : ������Ч֡�����ͷ�ʣ���ڴ�
 �������  : usPppId        -   PPPʵ��ID
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmProcValidFrames
(
    PPP_ID                               usPppId,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT16                          usFrmOutSegNum;
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT32                          ulFrmOutSpaceCnt;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaLink;
    HDLC_FRM_RPT_NODE_STRU             *pstFrmRptNodeStru;
    PPP_ZC_STRU                       **ppstOutputLinkNode;
    VOS_UINT32                          ucRptSpaceIndex;
    VOS_UINT32                          ulOutputLinkIndex;
    VOS_UINT8                          *pucFrmOutAddr;
    VOS_UINT16                          usFrmOutLen;
    VOS_UINT16                          usDataLen;


    pstFrmBuffInfo     = HDLC_FRM_GET_BUF_INFO(usPppId);                   /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmRptNodeStru  = &(pstFrmBuffInfo->astRptNodeBuf[0]);              /* ��װ�ϱ��ռ��׵�ַ */
    pstOutputParaLink  = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]);   /* ��װ��������׵�ַ */
    ppstOutputLinkNode = &(pstBuildInfo->apstOutputLinkNode[0]);           /* ��װ�������ڵ��Ӧ�㿽���ڴ������׵�ַ */
    ulFrmOutSpaceCnt   = pstBuildInfo->ulOutputLinkNodeCnt;                /* ��װ�������ڵ�ĸ��� */

    /* ��Ч֡���ռ��Ƭ�θ���usFrmOutSegNum= hdlc_frm_status�Ĵ���[31:16]λ��ֵ */
    usFrmOutSegNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* ��Ч֡����usFrmValidNum= hdlc_frm_status�Ĵ���[15:8]λ��ֵ */
    ucFrmValidNum  = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 15);

    /* �ϱ���װ�����ݿ�ά�ɲ�:�ϱ��ռ���Ϣ������������� */
    PPP_HDLC_HARD_MntnFrmTraceOutput(ucFrmValidNum, usFrmOutSegNum, pstFrmBuffInfo, pstBuildInfo);

    /* ucFrmValidNum�϶�ҪС�ڵ���ʹ�õ��ڴ����usFrmOutSegNum */
    if( ucFrmValidNum > usFrmOutSegNum )
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > usFrmOutSegNum = %d",
                      ucFrmValidNum, usFrmOutSegNum);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* ucFrmValidNumӦ��������������ͬulInputLinkNodeCnt��������װ������ܻ�Ⱥ���С */
    if( ucFrmValidNum > pstBuildInfo->ulInputLinkNodeCnt )
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > InputLinkNodeCnt = %d",
                      ucFrmValidNum, pstBuildInfo->ulInputLinkNodeCnt);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* usFrmOutSegNumʹ�õ��ڴ�����϶�С�ڵ���ulOutputLinkNodeCnt */
    if( usFrmOutSegNum  > ulFrmOutSpaceCnt )
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_out_seg_num = %d > OutputLinkNodeCnt = %d",
                      usFrmOutSegNum, ulFrmOutSpaceCnt);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    ucRptSpaceIndex   = 0;
    ulOutputLinkIndex = 0;

    while( ucRptSpaceIndex < ucFrmValidNum )
    {
        pucFrmOutAddr    = (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)pstFrmRptNodeStru[ucRptSpaceIndex].pucFrmOutOneAddr);
        usFrmOutLen      = pstFrmRptNodeStru[ucRptSpaceIndex].usFrmOutOneLen;

        if ( (0 == usFrmOutLen) || (HDLC_FRM_OUT_PER_MAX_CNT < usFrmOutLen) )
        {
            PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_FrmProcValidFrames, ERROR, invalid usFrmOutOneLen %d\r\n", usFrmOutLen);

            /* �ͷ������Ŀ�Ŀռ� */
            PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        pstMem      = ppstOutputLinkNode[ulOutputLinkIndex];

        if( pucFrmOutAddr != PPP_ZC_GET_DATA_PTR(pstMem) )
        {
            PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_FrmProcValidFram, ERROR, SOC copy error!\r\n");

            /* �ͷ������Ŀ�Ŀռ� */
            PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        while( usFrmOutLen > 0 )
        {
            /* ��pstBuildInfo->apstOutputLinkNodeȡ��ͷ��� pstMem */
            pstMem    = ppstOutputLinkNode[ulOutputLinkIndex];

            /* ���������������ָĿ�Ŀռ�Ĵ�С */
            usDataLen = pstOutputParaLink[ulOutputLinkIndex].usDataLen;

            if( usFrmOutLen > usDataLen )
            {
                PPP_ZC_SET_DATA_LEN(pstMem, usDataLen);
                usFrmOutLen -= usDataLen;
            }
            else
            {
                PPP_ZC_SET_DATA_LEN(pstMem, usFrmOutLen);
                usFrmOutLen  = 0;
            }

            PPP_HDLC_ProcDlData(usPppId, pstMem);

            g_PppDataQCtrl.stStat.ulDownlinkSndDataCnt++;

            /* ������������ݰ���apstOutputLinkNode����� */
            ppstOutputLinkNode[ulOutputLinkIndex] = VOS_NULL_PTR;

            ulOutputLinkIndex++;
        }

        ucRptSpaceIndex++;
    }

    /* �ͷ�ʣ��δ���õ�Ŀ�Ŀռ� */
    PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                  ulFrmOutSpaceCnt - ulOutputLinkIndex);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmWaitAndProc
 ��������  : �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ�
 �������  : ulEnableInterrupt  -   �ж��Ƿ�ʹ��
             usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
 �������  : pstBuildInfo   -   ��������Ľ����Ϣ���������������ȡ��ڵ�������㿽���ڴ�ָ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmWaitAndProc
(
    VOS_UINT32                           ulEnableInterrupt,
    PPP_ID                               usPppId,
    struct link                         *pstLink,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT32                          ulFrmStatus;


    /* ʹ���жϣ���ȴ��жϸ������ͷ��ź�����������ѯ���װ״̬�Ĵ��� */
    ulFrmStatus = PPP_HDLC_HARD_FrmWaitResult(ulEnableInterrupt);

    if ( HDLC_FRM_ALL_PKT_DONE == ulFrmStatus )
    {
        /* ������Ч֡�����ͷ�ʣ���ڴ� */
        PPP_HDLC_HARD_FrmProcValidFrames(usPppId, pstBuildInfo);
    }
    else
    {
        /* �ͷ������Ŀ�Ŀռ� */
        PPP_HDLC_HARD_CommReleaseLink(pstBuildInfo->apstOutputLinkNode, pstBuildInfo->ulOutputLinkNodeCnt);

        /* ��ӡ�쳣��־������PPP���� */
        PPP_HDLC_HARD_FrmProcException(ulFrmStatus, ulEnableInterrupt);
    }

    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = 0xFFFFFFFFU;

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmPacket
 ��������  : IPģʽ���з�װ��������
 �������  : usPppId        -   PPPʵ��ID
             usProtocol     -   ����װЭ��
             pstLink        -   PPP��·��Ϣ
             pstDataQ       -   PPP���ݶ���
 �������  : *pulDealCurCnt  -  ָ��ǰ�����PPP�����еĽ�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmPacket
(
    PPP_ID              usPppId,
    VOS_UINT16          usProtocol,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PUSH_PACKET_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ����usPppId�ҵ���Ӧ���ڴ� */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* ����������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult  = PPP_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmPacket, WARNING, BuildParaLink Fail.\r\n");
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* ���÷�װ��ؼĴ��� */
    PPP_HDLC_HARD_FrmCfgReg(pstLink, usProtocol);

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ� */
    PPP_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, pstLink, &stBuildInfo);

    /* �ͷ�pstBuildInfo->apstInputLinkNode�еĽ���ڴ� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_FrmRawPacket
 ��������  : PPPģʽ���з�װ��������
 �������  : usPppId        -   PPPʵ��ID
             usProtocol     -   ����װ���ݰ�Э��
             pstLink        -   PPP��·��Ϣ
             pstDataQ       -   PPP���ݶ���
 �������  : *pulDealCurCnt  -  ָ��ǰ�����PPP�����еĽ�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmRawData
(
    PPP_ID              usPppId,
    VOS_UINT16          usProtocol,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PUSH_RAW_DATA_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo         = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* ����������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult  = PPP_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }


    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* ���÷�װ��ؼĴ��� */
    PPP_HDLC_HARD_FrmRawCfgReg(pstLink, usProtocol);

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ� */
    PPP_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, pstLink, &stBuildInfo);

    /* �ͷ�pstBuildInfo->apstInputLinkNode�еĽ���ڴ� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_PROC_FUNC
 ��������  : Ӳ��HDLC���������ڴ���PPPʵ���ʱ�򣬸�����Ҫ�������ؽ�
             �����Ӳ����ʵ�����ʵ�����
 �������  : usPppId    -   PPPʵ��ID
             pstLink    -   PPP��·��Ϣ
             pstDataQ   -   PPP���ݶ���
 �������  :
 �� �� ֵ  : PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          ulDealTotalCnt;
    VOS_UINT32                          ulDealCurCnt;
    VOS_UINT32                          ulDealResult;
    VOS_UINT16                          usProtocol;
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;


    g_PppHdlcHardStat.ulHdlcHardProcCnt++;

    ulDealTotalCnt  = 0;
    ulDealCurCnt    = 0;

    for (;;)
    {
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstDataQ);

        /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
        if ( VOS_NULL_PTR == pstMem )
        {
            return PPP_HDLC_RESULT_COMM_FINISH;
        }

        /*���ѭ������Ľ����������˶���һ�����������������
          ���˳�ѭ��������PPP_DATA_PROC_NOTIFY��Ϣ*/
        if ( (ulDealTotalCnt >= PPP_ONCE_DEAL_MAX_CNT) )
        {
            g_PppHdlcHardStat.ulContinueCnt++;
            return PPP_HDLC_RESULT_COMM_CONTINUE;
        }

        /*����ý��(�����ͷŶ����Ѿ��ڸ��������ڲ���ɣ��������ͷŽ��)*/
        ucDataType   = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);
        ulDealResult = VOS_OK;
        ulDealCurCnt = 0;

        switch ( ucDataType )
        {
            case PPP_PULL_PACKET_TYPE:

                ulDealResult = PPP_HDLC_HARD_DefPacket(usPppId, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulDefIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PUSH_PACKET_TYPE:

                ulDealResult = PPP_HDLC_HARD_FrmPacket(usPppId, PROTO_IP, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulFrmIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PULL_RAW_DATA_TYPE:

                ulDealResult = PPP_HDLC_HARD_DefRawData(usPppId, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulDefIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PUSH_RAW_DATA_TYPE:

                /* ��ȡ����װ���ݰ���Э��ֵusProtocol */
                if (VOS_OK == PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usProtocol))
                {
                    ulDealResult = PPP_HDLC_HARD_FrmRawData(usPppId, usProtocol, pstLink, pstDataQ, &ulDealCurCnt);

                    g_PppHdlcHardStat.ulFrmPppDataProcCnt += ulDealCurCnt;
                }
                else
                {
                    pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);
                    PPP_MemFree(pstMem);
                }
                break;
            default:
                pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);
                PPP_MemFree(pstMem);
                PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_ProcData, WARNING, ucDataType %d is Abnormal!", ucDataType);
                break;
        }

        /*ͳ��*/
        ulDealTotalCnt += ulDealCurCnt;

        if ( ulDealTotalCnt > g_PppHdlcHardStat.ulMaxCntOnce )
        {
            g_PppHdlcHardStat.ulMaxCntOnce = ulDealTotalCnt;
        }

        if (VOS_OK != ulDealResult)
        {
            PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_ProcData, WARNING, ulDealResult = ERROR!");
            break;
        }
    } /* for (;;) */

    return PPP_HDLC_RESULT_COMM_ERROR;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_SendAsFrmPacketMsg
 ��������  : ��Ϣ���ͺ���
 �������  : usPppId        -- PPPʵ��ID
             usProtocol     -- ����װЭ��ֵ
             pstMem         -- ����װ���ݰ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_SendAsFrmPacketMsg
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstMsg;
    VOS_UINT32                               ulLength;


    ulLength    = sizeof(HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_PPP_HDLC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_SendMsg, ERROR: PS_ALLOC_MSG Failed!\r\n");
        return VOS_ERR;
    }

    /*��д��Ϣͷ:*/
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulLength        = ulLength;

    pstMsg->MsgHeader.ulMsgName       = PPP_HDLC_PROC_AS_FRM_PACKET_IND;
    /*��д��Ϣ��:*/
    pstMsg->usPppId                   = usPppId;
    pstMsg->usProtocol                = usProtocol;
    pstMsg->pstMem                    = pstMem;

    /*���͸���Ϣ*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_PPP_HDLC, pstMsg))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_SendAsFrmPacketMsg, ERROR : PS_SEND_MSG Failed!");
        PPP_MemFree(pstMem);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_ProcProtocolPacket
 ��������  : �������з�װ����
 �������  : usPppId        -- PPPʵ��ID
             usProtocol     -- ����װЭ��ֵ
             pstMem         -- ����װ���ݰ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    VOS_UINT32              ulDealCurCnt;
    PPP_ZC_QUEUE_STRU       stDataQ;
    struct link            *pstLink;
    VOS_UINT32              ulDealResult;

    pstLink = PPP_LINK(usPppId);

    ulDealCurCnt = 0;

    /* ��װ������IP�������ݰ� */
    PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PUSH_PACKET_TYPE);

    /* ��ʼ������stDataQ, ���� pstMem ��� */
    PPP_ZC_QUEUE_INIT(&stDataQ);
    PPP_ZC_ENQUEUE_TAIL(&stDataQ, pstMem);

    /* ֱ�ӽ������ݰ���װ���͸�PC */
    ulDealResult = PPP_HDLC_HARD_FrmPacket(usPppId, usProtocol, pstLink, &stDataQ, &ulDealCurCnt);

    if ((VOS_OK != ulDealResult) || (1 != ulDealCurCnt))
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_MakeFrmPacket, ERROR, ulDealResult %d ulDealCurCnt %d!\r\n",
                      ulDealResult, ulDealCurCnt);

        /* ˵����ĳ�ִ���������û�дӶ������Ƴ�����Ҫ�ͷ� */
        if (0 < PPP_ZC_GET_QUEUE_LEN(&stDataQ))
        {
            PPP_MemFree(pstMem);
        }

        return;
    }

    g_PppHdlcHardStat.ulFrmIpDataProcCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_HARD_ProcProtocolPacket
 ��������  : Ӳ����װPPPЭ��ջ�����Э���
 �������  : pstLink    -   PPP��·��Ϣ
             pstMbuf    -   PPPЭ��ջ�����Э���
             ulPri      -   ���ȼ�
             usProto    -   ���ݰ���Ӧ��Э��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32        ulPri,
    VOS_UINT16       usProtocol
)
{
    PPP_ZC_STRU            *pstMem;
    VOS_UINT16              usPppId;
    VOS_UINT32              ulFrmResult;
    VOS_UINT32              ulDefResult;


    usPppId = (VOS_UINT16)PPP_LINK_TO_ID(pstLink);

    pstMem  = ppp_m_alloc_ttfmem_from_mbuf(pstMbuf);

    ppp_m_freem(pstMbuf);
    pstMbuf  = VOS_NULL_PTR;

    /* for lint 438 */
    (VOS_VOID)pstMbuf;

    if (VOS_NULL_PTR == pstMem)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, pstMem is NULL!\r\n");
        return;
    }

    /* PPPЭ��ջ�ظ���Э�̰���Ҫ��װ�󷢸�PC��ȷ�ϴ�ʱ�Ƿ��װ����װ���Ѿ���� */
    ulFrmResult     = PPP_HDLC_HARD_FrmIsEnabled();
    ulDefResult     = PPP_HDLC_HARD_DefIsEnabled();

    /* �˺��������н��Э�̰�ʱ��PPPЭ��ջ����Ӧ�����ʱ���װ��Ӧ��ʹ�� */
    if( (VOS_TRUE == ulFrmResult) || (VOS_TRUE == ulDefResult) )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, ulFrmResult %d, ulDefResult %d!\r\n",
                      ulFrmResult, ulDefResult);
        PPP_HDLC_HARD_SendAsFrmPacketMsg(usPppId, usProtocol, pstMem);

        return;
    }

    /* �´�PPP������ȵ�ʱ���ٷ�װ��Э�̣���ʱ��װ����װ��δʹ�� */
    PPP_HDLC_HARD_ProcAsFrmPacket(usPppId, usProtocol, pstMem);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_PHY_TO_VIRT
 ��������  : ��PPP�е������ַת��Ϊ���ַ
 �������  : unsigned int ulPAddr   ��Ҫת���������ַ
             g_ulPppPhyAddr         PPP�����ַ����ַ
 �������  : ��
 �� �� ֵ  : ��Ӧ�����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��25��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr)
{
    return (VOS_UINT32)phys_to_virt(ulPAddr);
}

/*****************************************************************************
 �� �� ��  : PPP_VIRT_TO_PHY
 ��������  : ��PPP�е����ַת��Ϊ�����ַ
 �������  : VOS_UINT_PTR ulVAddr   ��Ҫת�������ַ
             g_ulPppVirtAddr        PPP���ַ����ַ
 �������  : ��
 �� �� ֵ  : ��Ӧ�������ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��25��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT_PTR PPP_VIRT_TO_PHY(VOS_UINT_PTR ulVAddr)
{
    return virt_to_phys((void *)ulVAddr);
}

/*****************************************************************************
 �� �� ��  : PPP_HDLC_NODE_PHY_TO_VIRT
 ��������  : ��PPP�з�װ���װ�������ַת��Ϊ���ַ
 �������  : unsigned int ulPAddr   ��Ҫת���������ַ
 �������  : ��
 �� �� ֵ  : ��Ӧ�����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��08��14��
    ��    ��   : g00178567
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_NODE_PHY_TO_VIRT(unsigned int ulPAddr)
{
    if ((ulPAddr >= g_ulPppPhyAddr) && (ulPAddr < (g_ulPppPhyAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return HDLC_DMA_PHY_TO_VIRT(ulPAddr);
    }
    else
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_NODE_PHY_TO_VIRT, WARNING, invalid ulPAddr 0x%x\r\n", ulPAddr);
        return g_ulPppPhyAddr;
    }
}


/*****************************************************************************
 �� �� ��  : PPP_HDLC_NODE_VIRT_TO_PHY
 ��������  : ��PPP�з�װ���װ�����ַת��Ϊ�����ַ
 �������  : unsigned int ulVAddr   ��Ҫת�������ַ
 �������  : ��
 �� �� ֵ  : ��Ӧ�������ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��08��14��
    ��    ��   : g00178567
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_HDLC_NODE_VIRT_TO_PHY(unsigned int ulVAddr)
{
    if ((ulVAddr >= g_ulPppVirtAddr) && (ulVAddr < (g_ulPppVirtAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return HDLC_DMA_VIRT_TO_PHY(ulVAddr);
    }
    else
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_NODE_VIRT_TO_PHY, WARNING, invalid ulVAddr 0x%x\r\n", ulVAddr);
        return g_ulPppVirtAddr;
    }
}


/*lint +e732*/
/*lint +e40*/
/*lint +e718*/
/*lint +e746*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


