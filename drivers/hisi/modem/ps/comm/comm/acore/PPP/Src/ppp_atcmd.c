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



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767  �޸���: z57034; ������: g45205 ԭ�����: �����־�ļ���ID���� */
#define    THIS_FILE_ID        PS_FILE_ID_PPP_ATCMD_C
/*lint +e767  �޸���: z57034; ������: g45205 */

#include "product_config.h"

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/ppp_atcmd.h"
#include "PPP/Inc/ppp_input.h"
#include "PPP/Inc/hdlc_software.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
extern VOS_VOID PPP_ClearDataQ(VOS_VOID);
extern VOS_VOID Ppp_ProcConfigInfoInd(VOS_UINT16 usPppId);

extern VOS_UINT32 PPP_SavePcoInfo
(
    PPP_ID usPppId,
    AT_PPP_IND_CONFIG_INFO_STRU *pstAtPppIndConfigInfo
);

extern VOS_VOID PPP_GetReqConfigInfo
(
    PPP_REQ_CONFIG_INFO_STRU    *pstPppReqConfigInfo,
    AT_PPP_REQ_CONFIG_INFO_STRU *pstPppAtReqConfigInfo
);
/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
/* �����NV���ж�ȡ��WINS���Կ���ֵ*/
extern VOS_UINT8                        g_ucPppConfigWins;

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : PPP_InitHdlcConfig
 ��������  : ����PPP ID��ʼ��HDLC������ã���Ҫ�������������Ӳ�����װ��
             ��ǰʵ�ֻ�ֻ��һ·PPP��ֱ�Ӹ���g_ulHDLCConfig������·����
 �������  : usPppId    -   PPPʵ��ID
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-04-19
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_InitHdlcConfig(PPP_ID usPppId)
{
    PPP_HDLC_CONFIG_STRU               *pstHdlcConfig;


    if ((usPppId == 0) || (PPP_MAX_ID_NUM < usPppId))
    {
        return VOS_ERR;
    }

    pstHdlcConfig = PPP_CONFIG(usPppId);


    pstHdlcConfig->pFunProcData            = PPP_HDLC_SOFT_ProcData;
    pstHdlcConfig->pFunProcProtocolPacket  = PPP_HDLC_SOFT_ProcProtocolPacket;
    pstHdlcConfig->pFunDisable             = VOS_NULL_PTR;
    pstHdlcConfig->pFunProcAsFrmData       = VOS_NULL_PTR;

    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                 "\r\nPPP, PPP_InitHdlcConfig, INFO, Soft HDLC.\r\n");


    return VOS_OK;
}

/*****************************************************************************
 Prototype      : Ppp_CreatePppReq
 Description    : ΪATģ��"����PPP��·"�ṩ��Ӧ��API������

 Input          : ---
 Output         : ---�����ɹ��󷵻ص�PPP ID
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_CreatePppReq ( PPP_ID *pusPppId)
{
    PPP_ID pppid_get;


    if(pusPppId == VOS_NULL)
    {
        return VOS_ERR;
    }

    /*��PPP ID�����еõ�һ�����е�PPP ID*/
    pppid_get = PppGetId();

    /*���û�п��е�PPP ID*/
    if(pppid_get == 0)
    {
        return VOS_ERR;
    }

    /*����п��е�PPP ID�����Ƚ�����õ���PPP ID��ֵ��AT_CMD*/
    *pusPppId = pppid_get;

    /*Ȼ�����PPPģ���Ӧ�ĺ���*/
    link_Init(PPP_LINK(pppid_get));
    PPP_LINK(pppid_get)->phase = PHASE_ESTABLISH;
    PPP_LINK(pppid_get)->lcp.fsm.state = ST_CLOSED;

    fsm_Open(&(PPP_LINK(pppid_get)->lcp.fsm));

    /*�ͷ�PPP���ݶ���*/
    PPP_ClearDataQ();

    /* ��ʼ��HDLC������� */
    PPP_InitHdlcConfig(pppid_get);

    /* ��ά�ɲ���Ϣ�ϱ�*/
    Ppp_EventMntnInfo(pppid_get, AT_PPP_CREATE_PPP_REQ);

    /*������ȷ*/
    return VOS_OK;
}


/*****************************************************************************
 Prototype      : Ppp_CreateRawDataPppReq
 Description    : ����PDP����ΪPPP��PPPʵ�壬��������·����ֻ�����ݵķ�װ�ͽ��װ

 Input          : ---
 Output         : ---�����ɹ��󷵻ص�PPP ID
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_CreateRawDataPppReq ( PPP_ID *pusPppId)
{
    PPP_ID  pppid_get;


    if (VOS_NULL_PTR == pusPppId)
    {
        return VOS_ERR;
    }

    /*��PPP ID�����еõ�һ�����е�PPP ID*/
    pppid_get = PppGetId();

    /*���û�п��е�PPP ID*/
    if (0 == pppid_get)
    {
        return VOS_ERR;
    }

    /* PPP����PDP����ʱ���޷���֪TE������˵�Э�̽����ǿ�Ƹ�ֵ */
    PPP_LINK(pppid_get)->lcp.his_accmap = 0xffffffff;

    /*����п��е�PPP ID�����Ƚ�����õ���PPP ID��ֵ��AT_CMD*/
    *pusPppId = pppid_get;

    /* ��ʼ��HDLC������� */
    PPP_InitHdlcConfig(pppid_get);

    /* ��ά�ɲ���Ϣ�ϱ�*/
    Ppp_EventMntnInfo(pppid_get, AT_PPP_CREATE_RAW_PPP_REQ);

    /*������ȷ*/
    return VOS_OK;
} /* Ppp_CreateRawDataPppReq */

/*****************************************************************************
 Prototype      : Ppp_ReleasePppReq
 Description    : ΪATģ��"�ͷ�PPP��·"�ṩ��Ӧ��API������

 Input          : ---Ҫ�ͷŵ�PPP��·��Ӧ��PPP ID
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_ReleasePppReq ( PPP_ID usPppId)
{
    VOS_UINT32                          ulRet;


    /* ��ά�ɲ���Ϣ�ϱ�*/
    Ppp_EventMntnInfo(usPppId, AT_PPP_RELEASE_PPP_REQ);

    if(VOS_OK != PppIsIdValid(usPppId))
    {
        return VOS_ERR;
    }

    /* �����ǰPPP��PHASE_NETWORK�׶�,������������ȥ����
       ��ʱPPP�ȴ���PC��PPPЭ�������֪ͨAT���ܽ��ź�,����ʱ������*/
    if (PHASE_NETWORK == (PPP_LINK(usPppId)->phase))
    {
        if (VOS_NULL_PTR != (PPP_LINK(usPppId)->lcp.hLcpCloseTimer))
        {
            PS_STOP_REL_TIMER(&(PPP_LINK(usPppId)->lcp.hLcpCloseTimer));
            PPP_LINK(usPppId)->lcp.hLcpCloseTimer= VOS_NULL_PTR;
        }

        /*��ʱ��,ȷ��֪ͨ��AT�ܽ��ź�*/
        ulRet = VOS_StartRelTimer(&(PPP_LINK(usPppId)->lcp.hLcpCloseTimer),  PS_PID_APP_PPP,
            1000,  usPppId,  PHASE_TERMINATE_PENDING,  VOS_RELTIMER_NOLOOP,  VOS_TIMER_PRECISION_5 );

        if (VOS_OK != ulRet)
        {
            PPP_LINK(usPppId)->lcp.hLcpCloseTimer = VOS_NULL_PTR;
            PPP_ProcPppDisconnEvent(usPppId);
        }
    }

    /*���ȵ���PPPģ���Ӧ�ĺ���*/
#if (SC_CTRL_MOD_3650_SFT != SC_CTRL_MOD)
    fsm_Close(&(PPP_LINK(usPppId)->ipcp.fsm));
#endif
    fsm_Close(&(PPP_LINK(usPppId)->lcp.fsm));

    /*ֹͣIPCP״̬����ʱ��:*/
    if( VOS_NULL_PTR !=((PPP_LINK(usPppId))->ipcp.fsm.timer) )
    {
        VOS_StopRelTimer(&((PPP_LINK(usPppId))->ipcp.fsm.timer));
        (PPP_LINK(usPppId))->ipcp.fsm.timer = VOS_NULL_PTR;
    }

    /*ֹͣCHAP״̬����ʱ��:*/
    if( VOS_NULL_PTR !=((PPP_LINK(usPppId))->chap.auth.hAuthTimer) )
    {
        VOS_StopRelTimer(&((PPP_LINK(usPppId))->chap.auth.hAuthTimer));
        (PPP_LINK(usPppId))->chap.auth.hAuthTimer = VOS_NULL_PTR;
    }

    /*ֹͣLCP״̬����ʱ��:*/
    if( VOS_NULL_PTR !=((PPP_LINK(usPppId))->lcp.fsm.timer) )
    {
        VOS_StopRelTimer(&((PPP_LINK(usPppId))->lcp.fsm.timer));
        (PPP_LINK(usPppId))->lcp.fsm.timer = VOS_NULL_PTR;
    }

    /*�ͷŴ�PDP���ʱ��*/
    if (VOS_NULL_PTR != (PPP_LINK(usPppId)->ipcp.hIpcpPendTimer))
    {
        PS_STOP_REL_TIMER(&(PPP_LINK(usPppId)->ipcp.hIpcpPendTimer));
        PPP_LINK(usPppId)->ipcp.hIpcpPendTimer = VOS_NULL_PTR;
    }

    /*�ͷŴ�����IPCP֡*/
    if (VOS_NULL_PTR != (PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame))
    {
        ppp_m_freem(PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame);
        PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame = VOS_NULL_PTR;
    }

    PppFreeId(usPppId);

    /* �����ͷ�PPP���ݶ��У���ΪֻҪ�������������ݣ�PPP����ͻᱻ������������
       ���HDLC������ɶ�PPPʵ���Ѿ��ͷţ���ô��װ����װ������������Ȼ�ᱻ������
       ���API����AT�����ﱻ���ã������������ݷŵ���PPP�����п�������ʹ�� */
    /* PPP_ClearDataQ(); */

    /*������ȷ*/
    return VOS_OK;
}


/*****************************************************************************
 Prototype      : Ppp_ReleaseRawDataPppReq
 Description    : ΪATģ��"�ͷ�PDP����ΪPPP��PPP��·"�ṩ��Ӧ��API������

 Input          : ---Ҫ�ͷŵ�PPP��·��Ӧ��PPP ID
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_ReleaseRawDataPppReq ( PPP_ID usPppId)
{
    /* ��ά�ɲ���Ϣ�ϱ�*/
    Ppp_EventMntnInfo(usPppId, AT_PPP_RELEASE_RAW_PPP_REQ);

    if(VOS_OK != PppIsIdValid(usPppId))
    {
        return VOS_ERR;
    }

    PppFreeId(usPppId);

    /*������ȷ*/
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_SndTeConfigInfo
 ��������  : ����PDP��������
 �������  : usPppId            -   PPPʵ��ID
             pPppReqConfigInfo  -   PDP�����������
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_ProcTeConfigInfo (VOS_UINT16 usPppId, PPP_REQ_CONFIG_INFO_STRU *pPppReqConfigInfo)
{
    AT_PPP_REQ_CONFIG_INFO_STRU         stPppAtReqConfigInfo;


    PPP_GetReqConfigInfo(pPppReqConfigInfo, &stPppAtReqConfigInfo);

    return At_RcvTeConfigInfoReq(usPppId,&stPppAtReqConfigInfo);
}

/*****************************************************************************
 �� �� ��  : PPP_ProcPppRelEvent
 ��������  : PPP��������PDPȥ����
 �������  : usPppId    -   PPPʵ��ID
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_ProcPppRelEvent (VOS_UINT16 usPppId)
{
    return At_RcvPppReleaseInd (usPppId);
}

/*****************************************************************************
 �� �� ��  : PPP_ProcPppDisconnEvent
 ��������  : PPP���ӶϿ�֪ͨ
 �������  : usPppId    -   PPPʵ��ID
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_ProcPppDisconnEvent (VOS_UINT16 usPppId)
{
    return Ppp_SndPPPDisconnIndtoAT(usPppId);
}

/*****************************************************************************
 Prototype      : Ppp_RcvConfigInfoInd
 Description    : ΪATģ��"PPPģ���������ָʾ��������Ϣ"�ṩ��Ӧ��API������
                  ��AT��GGSN��֤�ɹ��󣬵��ô˺�����PPP��ָʾ��

 Input          : usPppId---Ҫ��ָʾ��PPP��·���ڵ�PPP ID
                  pPppIndConfigInfo---��GGSN�����ĸ�PPP��·��IP��ַ����Ϣ
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_RcvConfigInfoInd
(
    PPP_ID usPppId,
    AT_PPP_IND_CONFIG_INFO_STRU         *pstAtPppIndConfigInfo
)
{
    VOS_UINT8                               ucRabId = 0;

    VOS_UINT32                              ulResult;


    if(VOS_OK != PppIsIdValid(usPppId))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP, Ppp_RcvConfigInfoInd, WARNING, Invalid PPP Id %d",
                      usPppId);
        return VOS_ERR;
    }


    /* ͨ��usPppId��Ѱ�ҵ�usRabId */
    if ( !PPP_PPPID_TO_RAB(usPppId, &ucRabId) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                      "PPP, Ppp_RcvConfigInfoInd, WARNING, Can not get PPP Id %d, RabId %d",
                      usPppId, ucRabId);

        return VOS_ERR;
    }

    /* ���ʱ��PDP�Ѿ����ע���������ݽ��սӿڡ����⵱ǰ��֧��PPP���Ͳ��š� */
    ulResult= ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)PPP_PushPacketEvent, 0);

    if ( VOS_OK != ulResult )
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP, Ppp_RcvConfigInfoInd, WARNING, Register DL CB failed! RabId %d",
                      ucRabId);

        return VOS_ERR;
    }

    /* ����PCO��Ϣ */
    PPP_SavePcoInfo(usPppId, pstAtPppIndConfigInfo);

    Ppp_RcvConfigInfoIndMntnInfo(usPppId, pstAtPppIndConfigInfo);

    PPP_RcvAtCtrlOperEvent(usPppId, PPP_AT_CTRL_CONFIG_INFO_IND);

    /*������ȷ*/
    return VOS_OK;
}

/*****************************************************************************
 Prototype      : PPP_RcvAtCtrlOperEvent
 Description    : ΪATģ��"��PPP���Ϳ��Ʋ���"�ṩ��Ӧ��API������
 Input          : usPppId---Ҫ��ָʾ��PPP��·���ڵ�PPP ID
                  ulCtrlOperType---AT��PPP���͵Ŀ��Ʋ�������
 Output         : ---
 Return Value   : VOS_OK        --�����ɹ�
                  VOS_ERR       --����ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-04-17
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_UINT32 PPP_RcvAtCtrlOperEvent(VOS_UINT16 usPppId, PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32 ulCtrlOperType)
{
    PPP_AT_CTRL_OPERATION_MSG *pSndMsg;

    if(PPP_AT_CTRL_BUTT <= ulCtrlOperType)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                "PPP_RcvAtCtrlOperEvent:ulCtrlOperType ERROR!",(VOS_INT32)ulCtrlOperType);
        return VOS_ERR;
    }

    pSndMsg = (PPP_AT_CTRL_OPERATION_MSG *)PS_ALLOC_MSG(PS_PID_APP_PPP, sizeof(PPP_AT_CTRL_OPERATION_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pSndMsg)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
            "PPP, PPP_RcvAtCtrlOperEvent, WARNING, Alloc msg fail!\r\n");
        return VOS_ERR;
    }

    pSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pSndMsg->ulReceiverPid      = PS_PID_APP_PPP;
    pSndMsg->ulMsgType          = PPP_AT_CTRL_OPERATION;
    pSndMsg->usPppId            = usPppId;
    pSndMsg->ulCtrlOpType       = ulCtrlOperType;

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG(PS_PID_APP_PPP, pSndMsg) )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP, PPP_RcvAtCtrlOperEvent, WARNING, Send msg fail!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : Ppp_SndPPPDisconnIndtoAT
 Description    : PPPЭ���ͷź���֪ͨATģ�����ܽ��ź�,
                  ԭ��XP��,�Ͽ�ʱֱ�����ܽ��ź�,������MAC����ϵͳ����ȱ��
                  MAC����ϵͳ,�Ͽ�(PC��������������)ʱ����Ҫ���PPP�ĶϿ�Э��
                  ����MAC�ϵ�����ӿ�״̬��Ȼ����ʾ������̬
                  �ýӿ�����֪ͨATģ�����ܽ��ź�,��PPP��ɶϿ�Э��ʱ����
 Input          : PPPID
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2010-03-05
    Author      : x00138766
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_SndPPPDisconnIndtoAT(VOS_UINT16 usPppId)
{
    AT_PPP_PROTOCOL_REL_IND_MSG_STRU    *pstMsg;
    VOS_UINT32                           ulLength;


    /* ��ά�ɲ���Ϣ�ϱ�*/
    Ppp_EventMntnInfo(usPppId, PPP_PROTOCOL_RELEASED_IND);

    if(PPP_MAX_ID_NUM < usPppId)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"Ppp_SndPPPDisconnIndtoAT usPppId Wrong!\r\n");
        return VOS_ERR;
    }

    /*��ATģ�鷢��AT_PPP_RELEASE_IND_MSG*/
    ulLength    = sizeof(AT_PPP_PROTOCOL_REL_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (AT_PPP_PROTOCOL_REL_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_APP_PPP, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"Ppp_SndPPPDisconnIndtoAT : PS_ALLOC_MSG Failed!\r\n");
        return VOS_ERR;
    }
    /*��д��Ϣͷ:*/
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = PS_PID_APP_PPP;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->MsgHeader.ulLength        = ulLength;

    pstMsg->MsgHeader.ulMsgName       = AT_PPP_PROTOCOL_REL_IND_MSG;
    /*��д��Ϣ��:*/
    pstMsg->usPppId                   = usPppId;

    /*���͸���Ϣ*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_PPP, pstMsg))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"Ppp_SndPPPDisconnIndtoAT : PS_SEND_MSG Failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_SavePcoInfo
 ��������  : ����PCO��Ϣ
 �������  : usPppId -   PPP id
             pstAtPppIndConfigInfo - AT���͵�PCO��Ϣ
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_SavePcoInfo
(
    PPP_ID usPppId,
    AT_PPP_IND_CONFIG_INFO_STRU *pstAtPppIndConfigInfo
)
{
    struct ipcp                         *pstIpcp;
    AT_PPP_PCO_IPV4_ITEM_STRU           *pstPcoIpv4Item;
    VOS_UINT32                          ucIpv4Address;


    pstIpcp        = &(PPP_LINK(usPppId)->ipcp);
    pstPcoIpv4Item = &(pstAtPppIndConfigInfo->stPcoIpv4Item);


    ua_htonl(pstAtPppIndConfigInfo->aucIpAddr, &ucIpv4Address);
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_SavePcoInfo, aucIpAddr %x\r\n",
                  ucIpv4Address);
    ua_htonl(pstPcoIpv4Item->aucPriDns, &ucIpv4Address);
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_SavePcoInfo, bitOpPriDns %d, aucPriDns %x\r\n",
                  (VOS_INT)pstPcoIpv4Item->bitOpPriDns, ucIpv4Address);
    ua_htonl(pstPcoIpv4Item->aucSecDns, &ucIpv4Address);
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_SavePcoInfo, bitOpSecDns %d, aucSecDns %x\r\n",
                  (VOS_INT)pstPcoIpv4Item->bitOpSecDns, ucIpv4Address);
    ua_htonl(pstPcoIpv4Item->aucPriNbns, &ucIpv4Address);
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_SavePcoInfo, bitOpPriNbns %d, aucPriNbns %x\r\n",
                  (VOS_INT)pstPcoIpv4Item->bitOpPriNbns, ucIpv4Address);
    ua_htonl(pstPcoIpv4Item->aucSecNbns, &ucIpv4Address);
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_SavePcoInfo, bitOpSecNbns %d, aucSecNbns %x\r\n",
                  (VOS_INT)pstPcoIpv4Item->bitOpSecNbns, ucIpv4Address);

    /* ������DNS��������ַ */
    if ( pstPcoIpv4Item->bitOpPriDns )
    {
        PS_MEM_CPY(&(pstIpcp->PriDnsAddr.s_addr), pstPcoIpv4Item->aucPriDns, IPV4_ADDR_LEN);
        pstIpcp->PriDns_neg |= NEG_ACCEPTED;
    }

    /* ���渨DNS��������ַ */
    if ( pstPcoIpv4Item->bitOpSecDns )
    {
        PS_MEM_CPY(&(pstIpcp->SecDnsAddr.s_addr), pstPcoIpv4Item->aucSecDns, IPV4_ADDR_LEN);
        pstIpcp->SecDns_neg |= NEG_ACCEPTED;
    }

    /* ������NBNS��������ַ */
    if ( (pstPcoIpv4Item->bitOpPriNbns)
         && (WINS_CONFIG_ENABLE == g_ucPppConfigWins))
    {
        PS_MEM_CPY(&(pstIpcp->PriNbnsAddr.s_addr), pstPcoIpv4Item->aucPriNbns, IPV4_ADDR_LEN);
        pstIpcp->PriNbns_neg |= NEG_ACCEPTED;
    }

    /* ���渨NBNS��������ַ */
    if ( (pstPcoIpv4Item->bitOpSecNbns)
         && (WINS_CONFIG_ENABLE == g_ucPppConfigWins))
    {
        PS_MEM_CPY(&(pstIpcp->SecNbnsAddr.s_addr), pstPcoIpv4Item->aucSecNbns, IPV4_ADDR_LEN);
        pstIpcp->SecNbns_neg |= NEG_ACCEPTED;
    }

    /* �ο�Ppp_RcvConfigInfoIndʵ�֣�peer_ip��������ַaucIpAddr */
    PS_MEM_CPY(&(pstIpcp->peer_ip.s_addr), pstAtPppIndConfigInfo->aucIpAddr, IPV4_ADDR_LEN);
    pstIpcp->IpAddr_neg |= NEG_ACCEPTED;

    /* �л�IPCPЭ��״̬ */
    if(pstIpcp->stage == IPCP_REQ_RECEIVED)
    {
        pstIpcp->stage = IPCP_SUCCESS_FROM_GGSN;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_GetReqConfigInfo
 ��������  : ����PDP�����������
 �������  : pstPppReqConfigInfo    -   PPP_REQ_CONFIG_INFO_STRUָ��
             pstPppAtReqConfigInfo  -   PPP_AT_REQ_CONFIG_INFO_STRUָ��
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_VOID PPP_GetReqConfigInfo
(
    PPP_REQ_CONFIG_INFO_STRU    *pstPppReqConfigInfo,
    AT_PPP_REQ_CONFIG_INFO_STRU *pstPppAtReqConfigInfo
)
{
    PPP_AUTH_PAP_CONTENT_STRU           *pstSrcPapContent;
    PPP_AUTH_CHAP_CONTENT_STRU          *pstSrcChapContent;
    AT_PPP_AUTH_PAP_CONTENT_STRU        *pstDestPapContent;
    AT_PPP_AUTH_CHAP_CONTENT_STRU       *pstDestChapContent;


    pstPppAtReqConfigInfo->stAuth.ucAuthType = pstPppReqConfigInfo->stAuth.ucAuthType;

    /* ��ȡPPP_AT_AUTH_CHAP_CONTENT_STRU */
    if ( PPP_CHAP_AUTH_TYPE == pstPppReqConfigInfo->stAuth.ucAuthType )
    {
        pstDestChapContent = &(pstPppAtReqConfigInfo->stAuth.AuthContent.ChapContent);
        pstSrcChapContent  = &(pstPppReqConfigInfo->stAuth.AuthContent.ChapContent);

        pstDestChapContent->usChapChallengeLen = pstSrcChapContent->usChapChallengeLen;
        pstDestChapContent->usChapResponseLen  = pstSrcChapContent->usChapResponseLen;

        PS_MEM_CPY(pstDestChapContent->aucChapChallengeBuf, pstSrcChapContent->pChapChallenge,
                   pstSrcChapContent->usChapChallengeLen);

        PS_MEM_CPY(pstDestChapContent->aucChapResponseBuf, pstSrcChapContent->pChapResponse,
                   pstSrcChapContent->usChapResponseLen);
    }
    /* ��ȡPPP_AT_AUTH_PAP_CONTENT_STRU */
    else if ( PPP_PAP_AUTH_TYPE == pstPppReqConfigInfo->stAuth.ucAuthType )
    {
        pstDestPapContent = &(pstPppAtReqConfigInfo->stAuth.AuthContent.PapContent);
        pstSrcPapContent  = &(pstPppReqConfigInfo->stAuth.AuthContent.PapContent);

        pstDestPapContent->usPapReqLen = pstSrcPapContent->usPapReqLen;

        PS_MEM_CPY(pstDestPapContent->aucPapReqBuf, pstSrcPapContent->pPapReq,
                   pstSrcPapContent->usPapReqLen);
    }
    else
    {
        /* PPP_NO_AUTH_TYPE */
    }

    /* ��ȡPPP_AT_REQ_IPCP_CONFIG_INFO_STRU */
    pstPppAtReqConfigInfo->stIPCP.usIpcpLen = pstPppReqConfigInfo->stIPCP.usIpcpLen;

    PS_MEM_CPY(pstPppAtReqConfigInfo->stIPCP.aucIpcp,
               pstPppReqConfigInfo->stIPCP.pIpcp,
               pstPppReqConfigInfo->stIPCP.usIpcpLen);

    return;
}

/*****************************************************************************
 Prototype      : Ppp_RegDlDataCallback
 Description    : ΪATģ���ṩע�����з������ݵ�API

 Input          : usPppId---Ҫ��ָʾ��PPP��·���ڵ�PPP ID
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-06-04
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_RegDlDataCallback(PPP_ID usPppId)
{
    VOS_UINT8                               ucRabId = 0;

    VOS_UINT32                              ulResult;


    if(VOS_OK != PppIsIdValid(usPppId))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP, Ppp_RegDlDataCallback, WARNING, Invalid PPP Id %d",
                      usPppId);
        return VOS_ERR;
    }


    /* ͨ��usPppId��Ѱ�ҵ�usRabId */
    if (!PPP_PPPID_TO_RAB(usPppId, &ucRabId))
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                      "PPP, Ppp_RegDlDataCallback, WARNING, Can not get PPP Id %d, RabId %d",
                      usPppId, ucRabId);

        return VOS_ERR;
    }

    /* ���ʱ��PDP�Ѿ����ע���������ݽ��սӿ� */
    ulResult= ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)PPP_PushRawDataEvent, 0);

    if ( VOS_OK != ulResult )
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP, Ppp_RegDlDataCallback, WARNING, Register DL CB failed! RabId %d",
                      ucRabId);

        return VOS_ERR;
    }

    return VOS_OK;
}



