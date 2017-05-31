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
   2 �ⲿ������������
******************************************************************************/
#include "product_config.h"
/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/proto.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/pap.h"
#include "PPP/Inc/ppp_input.h"
#include "PPP/Inc/ppp_atcmd.h"
#include "NVIM_Interface.h"
#include "TtfNvInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767  �޸���: z57034; ������: g45205 ԭ�����: �����־�ļ���ID���� */
#define    THIS_FILE_ID        PS_FILE_ID_PPP_INIT_C
/*lint +e767  �޸���: z57034; ������: g45205 */

/******************************************************************************
   PPP�������ȼ�����modem_send�ߣ���modem_recv�����
******************************************************************************/
#define PPP_TASK_PRI                                  143

extern VOS_VOID PPP_ProcDataNotify(VOS_VOID);
extern VOS_UINT32  PPP_Snd1stDataNotify(VOS_VOID);
extern VOS_VOID PPP_ProcAsFrmDataInd(struct MsgCB * pMsg);

/*Add by y45445 for PS FUSION PC ST*/

/*Add by y45445 for PS FUSION PC ST*/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
/* �����NV���ж�ȡ��WINS���Կ���ֵ*/
VOS_UINT8  g_ucPppConfigWins = WINS_CONFIG_ENABLE;

/* ���������� */
extern      VOS_SPINLOCK           g_stPppASpinLock;

/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 Prototype      : PPP_UpdateWinsConfig()
 Description    : ����PPPģ���WINS����
 Input          :
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_UpdateWinsConfig(VOS_UINT8 ucWins)
{
    if ((WINS_CONFIG_DISABLE != ucWins) && (WINS_CONFIG_ENABLE != ucWins))
    {
        /* ucWinsֵ��Ч */
        return;
    }

    /* ����g_ucPppConfigWins */
    g_ucPppConfigWins = ucWins;

    return;
}

/*****************************************************************************
 Prototype      : PPP_DataQInit()
 Description    : PPP���ݶ��еĳ�ʼ��
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2008-07-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_DataQInit(VOS_VOID)
{
    PPP_ZC_QUEUE_STRU                    *pstDataQ;


    pstDataQ    = &(g_PppDataQCtrl.stDataQ);

    VOS_MemSet(&g_PppDataQCtrl, 0, sizeof(g_PppDataQCtrl));

    PPP_ZC_QUEUE_INIT(pstDataQ);

    return;
}


/*****************************************************************************
 Prototype      : PPP_DataQClear()
 Description    : ���PPP���ݶ�������
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2008-07-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_ClearDataQ(VOS_VOID)
{
    PPP_ZC_STRU    *pstMem;


    for(;;)
    {
        if ( 0 == PPP_ZC_GET_QUEUE_LEN(&g_PppDataQCtrl.stDataQ) )
        {
            break;
        }

        pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(&g_PppDataQCtrl.stDataQ);

        PPP_MemFree(pstMem);
    }

    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                                  "PPP, PPP_ClearDataQ, NORMAL, Clear Stat Info\n");

    return;
} /* PPP_ClearDataQ */


/*****************************************************************************
 Prototype      : PPP_GetMruConfig()
 Description    : ��������,ͨ��NV���ȡPPP�û�����MRU
 Input          : VOS_VOID
 Output         :
 Return Value   : VOS_UINT16 �û����õ�MRU
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : x00138766
    Modification: Created function
*****************************************************************************/
VOS_UINT16 PPP_GetMruConfig(VOS_VOID)
{
    VOS_UINT16                      usPppConfigMru  = DEF_MRU;
    VOS_UINT32                      ulRslt;
    PPP_CONFIG_MRU_TYPE_NV_STRU     stPppConfigMruType;


    PS_MEM_SET(&stPppConfigMruType, 0x00, sizeof(PPP_CONFIG_MRU_TYPE_NV_STRU));

    /* Ϊ�ͻ�����PPP Default MRU��ʹ��NV_Item�����ڴ�NV�ṹΪ16bit�����ǵ��ֽڶ������أ�
       ���ȹ̶�дsizeof(VOS_UINT16) */
    ulRslt = NV_ReadEx(MODEM_ID_0, en_NV_Item_PPP_CONFIG_MRU_Type, &stPppConfigMruType, sizeof(VOS_UINT16));
    usPppConfigMru  = stPppConfigMruType.usPppConfigType;

    if (NV_OK != ulRslt)
    {
        usPppConfigMru = DEF_MRU;
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "Warning: Read en_NV_Item_PPP_DEFAULT_MRU_Type Error!");
    }

    if (usPppConfigMru > MAX_MRU)
    {
        usPppConfigMru = MAX_MRU;
    }

    if (usPppConfigMru < MIN_MRU)
    {
        usPppConfigMru = MIN_MRU;
    }

    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
        "[INFO] PPP -- NV config MRU : <1>", (VOS_INT32)usPppConfigMru);

    return usPppConfigMru;
}

/*****************************************************************************
 Prototype      : PPP_GetConfigWINS()
 Description    : ��������,ͨ��NV���ȡPPP�û�����WINSЭ��ʹ�ܿ���
 Input          : VOS_VOID
 Output         :
 Return Value   : VOS_UINT8 WINS����
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : x00138766
    Modification: Created function
*****************************************************************************/
VOS_UINT8 PPP_GetWinsConfig(VOS_VOID)
{
    WINS_CONFIG_STRU    stWins;

    /* ��������,��ȡWINS���Կ��ƿ���NV�� */

    /* ����ȡen_NV_Item_WINSʧ��,��Ĭ��WINS����Ϊʹ�� */
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, sizeof(WINS_CONFIG_STRU)))
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Warning: Read en_NV_Item_WINS_Config Error!");
        return WINS_CONFIG_ENABLE;
    }

    /* ��en_NV_Item_WINSδ���ã���Ĭ��WINS����Ϊʹ�� */
    if (0 == stWins.ucStatus)
    {
        return WINS_CONFIG_ENABLE;
    }

    /* ��en_NV_Item_WINS����ֵ��Ч����Ĭ��WINS����Ϊʹ�� */
    if ((WINS_CONFIG_ENABLE != stWins.ucWins) && (WINS_CONFIG_DISABLE != stWins.ucWins))
    {
        return WINS_CONFIG_ENABLE;
    }

    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_GetWinsConfig,[INFO] PPP -- NV config WINS : %d", (VOS_INT32)stWins.ucWins);

    return stWins.ucWins;
}


/*****************************************************************************
 Prototype      : PppInit
 Description    : TAF PPPģ���еĳ�ʼ������,�ú�������ϵͳ���뽨��PPPģ������
                  ����Ҫ�ĸ�����Դ������ɹ�������VOS_OK������ΪVOS_ERR��
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
  2. 2006-03-13 MODIFY BY F49086 FOR A32D02474
  3.Date        : 2006-05-22
    Author      : L47619
    Modification: Modify for PN:A32D04462
  4.Date        : 2006-10-08
    Author      : L47619
    Modification: Modify for PN:A32D06578
  5.Data        : 2009-7-14
    Author      : x00138766
    Modification: ����WINSЭ��ʹ�ܿ�������
*****************************************************************************/
VOS_UINT32    PppInit(enum VOS_INIT_PHASE_DEFINE InitPhase )
{
    VOS_INT32               i;

    /*Add by y45445 for PS FUSION PC ST*/
    /*Add by y45445 for PS FUSION PC ST*/

    switch( InitPhase )
    {
    case   VOS_IP_LOAD_CONFIG:
            /*��������,ͨ��NV��,��ȡ�û�����MRU�Լ�WINSЭ�̿���*/
            /*��ȡNV��,��ȡ�û�����MRU*/
            g_usPppConfigMru = PPP_GetMruConfig();

            /*��ȡNV��,��ȡ�û�����WINSʹ�ܿ���*/
            g_ucPppConfigWins = PPP_GetWinsConfig();

            /*��ϵͳ�������һ��ȫ�����õ�link����Ŀռ�*/
            /*lint -e433*/
            pgPppLink = (struct link *)VOS_MemAlloc(PS_PID_APP_PPP, STATIC_MEM_PT, sizeof(struct link)*PPP_MAX_ID_NUM);
            /*lint +e433*/
            if (VOS_NULL_PTR == pgPppLink)
            {
                /*���������Ϣ*/
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"PppInit, malloc of  memory fail\r\n");
                return VOS_ERR;
            }

            /*��ϵͳ�������һ��ȫ�����õ�TAF_PPP_PUBLIC_STRU�Ŀռ�*/
            pgPppId = (PPP_ID *)VOS_MemAlloc(PS_PID_APP_PPP, STATIC_MEM_PT, sizeof(PPP_ID)*PPP_MAX_ID_NUM_ALLOC);
            if (VOS_NULL_PTR == pgPppId)
            {
                /*�ͷ������ȫ�����õ�TAF_PPP_PUBLIC_STRU�Ŀռ�*/
                VOS_MemFree(PS_PID_APP_PPP, pgPppLink);
                pgPppLink = VOS_NULL_PTR;


                /*���������Ϣ*/
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"PppInit, malloc of  memory fail\r\n");
                return VOS_ERR;
            }

            /*����ϵͳ���õ����������ݽṹ����ʼ��*/
            for(i = 0;i < PPP_MAX_ID_NUM; i++)
            {
                link_Init((pgPppLink + i));
            }

            PppIdInit();

            /*��ʼ��PPP�����ݶ���*/
            PPP_DataQInit();

            /* ��ʼ�������� */
            PPP_InitSpinLock();



            /*Add by y45445 for PS FUSION PC ST*/
            /*Add by y45445 for PS FUSION PC ST*/
            break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
    case   VOS_IP_BUTT:
           break;
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : PppMsgTimerProc
 Description    : PPPģ���еĶ�ʱ����Ϣ������
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : fanzhibin
    Modification: Created function
  2.Date        : 2006-05-22
    Author      : L47619
    Modification: Modify for PN:A32D04462
  3.Date        : 2007-01-05
    Author      : L47619
    Modification: Modify for PN:A32D08013
  4.Date        : 2008-10-28
    Author      : liukai
    Modification: support CHAP authentication timer
*****************************************************************************/
VOS_VOID PppMsgTimerProc( struct MsgCB * pMsg )
{
    REL_TIMER_MSG  *pPsMsg = (REL_TIMER_MSG  *)pMsg;
    VOS_UINT16      usPppId = (VOS_UINT16)(pPsMsg->ulName);


    /*�ж����Ǹ��׶������Ķ�ʱ��*/
    switch(pPsMsg->ulPara)
    {
        /*�����LCP�׶������Ķ�ʱ��*/
        case PHASE_ESTABLISH:
            if (PPP_LINK(usPppId)->phase == PHASE_ESTABLISH)
            {
                FsmTimeout(&(PPP_LINK(usPppId)->lcp.fsm),
                    pPsMsg->ulPara);
            }

            break;

        /*�������ֹ�׶������Ķ�ʱ��*/
        case PHASE_TERMINATE:
            if (PPP_LINK(usPppId)->phase == PHASE_TERMINATE)
            {
                FsmTimeout(&(PPP_LINK(usPppId)->lcp.fsm),
                    pPsMsg->ulPara);
            }

            break;

        /*�������֤�׶������Ķ�ʱ��*/
        case PHASE_AUTHENTICATE:
            {
                if (PPP_LINK(usPppId)->phase == PHASE_AUTHENTICATE)
                {
                    AuthTimeout(PPP_LINK(usPppId));
                }

                break;
            }

        /*�����IPCP�׶������Ķ�ʱ��*/
        case PHASE_NETWORK:
            if (PPP_LINK(pPsMsg->ulName)->phase == PHASE_NETWORK)
            {
                FsmTimeout(&(PPP_LINK(usPppId)->ipcp.fsm),
                    pPsMsg->ulPara);
            }

            break;

        /*�����IPCP�׶δ�PDP����Ķ�ʱ��,����������IPCP֡*/
        case PHASE_PDP_ACT_PENDING:
            if (VOS_NULL_PTR != PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame)
            {
                fsm_Input(&(PPP_LINK(usPppId)->ipcp.fsm), PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame);
                PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame = VOS_NULL_PTR;
            }
            PPP_LINK(usPppId)->ipcp.hIpcpPendTimer = VOS_NULL_PTR;
            break;

        case PHASE_TERMINATE_PENDING:
            PPP_LINK(usPppId)->lcp.hLcpCloseTimer = VOS_NULL_PTR;
            PPP_ProcPppDisconnEvent(usPppId);
            break;


        default:
            {
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,"unknow timer!\r\n");
            }
    }


    return;
}


/*****************************************************************************
 Prototype      : PppMsgProc
 Description    : TAF PPPģ���е���Ϣ��������������ʱ����Ϣ�Լ���ATģ���
                  �յ�����֡����Ϣ������ɹ�������VOS_OK������ΪVOS_ERR��
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
  2.Date        : 2006-05-17
    Author      : L47619
    Modification: Modified for PN:A32D04462
*****************************************************************************/
VOS_VOID PppMsgProc( struct MsgCB * pMsg )
{
    PPP_MSG    *pPsMsg  = (PPP_MSG *)pMsg;

    if(pMsg == VOS_NULL_PTR)
    {
        return;
    }


    /*����Ƕ�ʱ����������Ϣ*/
    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        PppMsgTimerProc(pMsg);


        return ;
    }

    /*����ǽ��յ���TE������������֡*/
    switch(pPsMsg->ulMsgType)
    {
        case PPP_DATA_PROC_NOTIFY:
            PPP_ProcDataNotify();
            break;

        case PPP_AT_CTRL_OPERATION:
            PPP_ProcAtCtrlOper(pMsg);
            break;

        case PPP_HDLC_PROC_AS_FRM_PACKET_IND:
            PPP_ProcAsFrmDataInd(pMsg);
            break;

/*Add by y45445 for PS FUSION PC ST*/
/*Add by y45445 for PS FUSION PC ST*/
        default:
            break;
    }


    return;
}

/*****************************************************************************
 Prototype      : PPP_PowerOff()
 Description    : ��ػ������У����Ի���PPPģ����Դ
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-08-28
    Author      : l47619
    Modification: �������ⵥ����:A32D12744
*****************************************************************************/
VOS_VOID    PPP_PowerOff(VOS_VOID)
{
    VOS_UINT8   ucPppId;

    /*��ػ�ʱ����ʱ���������У���ֹͣ�ö�ʱ��:*/
    for(ucPppId = 1; ucPppId <= PPP_MAX_ID_NUM; ucPppId++)
    {
        /*LCP״̬����ʱ��:*/
        if( VOS_NULL_PTR !=((PPP_LINK(ucPppId))->lcp.fsm.timer) )
        {
            VOS_StopRelTimer(&((PPP_LINK(ucPppId))->lcp.fsm.timer));
        }

        /*IPCP״̬����ʱ��:*/
        if( VOS_NULL_PTR !=((PPP_LINK(ucPppId))->ipcp.fsm.timer) )
        {
            VOS_StopRelTimer(&((PPP_LINK(ucPppId))->ipcp.fsm.timer));
        }
    }

    /*�ͷ�PPP���ݶ���*/
    PPP_ClearDataQ();
    return;
}


/*****************************************************************************
 Prototype      : PppStop
 Description    : TAF PPPģ���еĽ�������,�ú���������ϵͳ��������ʱ�ͷ�PPPģ
                  ����ϵͳ�������Դ
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
#define PPP_FREE(point)\
    if(point!=VOS_NULL_PTR)         \
    {                                   \
        /*�ͷ������ȫ�����õĿռ�*/    \
        VOS_MemFree(PS_PID_APP_PPP, point);   \
        point = VOS_NULL_PTR;  \
    }\

VOS_VOID    PppStop(VOS_VOID)
{
    /*VOS_UINT32    dis_interrupt;*/
    VOS_INT32 i;



    /*����ϵͳ���õ���throughout�ṹ���ͷŵ���������ڴ�*/
    for(i = 0;i < PPP_MAX_ID_NUM; i++)
    {
        throughput_destroy(&((pgPppLink + i)->stats.total));
    }

    PPP_FREE(pgPppLink)
    PPP_FREE(pgPppId)

    return;
}





