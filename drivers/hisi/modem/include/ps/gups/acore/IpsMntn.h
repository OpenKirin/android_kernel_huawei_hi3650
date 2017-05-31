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

#ifndef _IPS_MNTN_H_
#define _IPS_MNTN_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "TtfOamInterface.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define IPS_IFNAMSIZ                    (16)                    /*�����������Ƴ���*/
#define IPS_END_NAME                    (16)
#define IPS_APP_CMD_INFO_LEN            (200)                   /*����APP��������������*/
#define IPS_MNTN_INFO_LEN               (10000)                 /*����TCP/IPЭ��ջ������Ϣ�����*/
#define IPS_MNTN_TRACE_MAX_BYTE_LEN     (1514)                  /*����TCP/IPЭ��ջ��������� */
#define IPS_MNTN_NAT_MAPPING_INFO_LEN   (40)                    /*����TCP/IPЭ��ջNATӳ����Ϣ��������*/
#define IPS_MNTN_INFO_TYPE_OFFSET       (4)                     /*TCP/IPЭ��ջ������Ϣ����ƫ��*/
#define IPS_MNTN_INFO_LEN_OFFSET        (4)                     /*TCP/IPЭ��ջ������Ϣ����ƫ��*/

/*�����Ϣͷ*/
#define IPS_FILL_MSG_HEADER(pSendMsg, RecvPid)    \
        (pSendMsg)->ulReceiverCpuId  = VOS_LOCAL_CPUID; \
        (pSendMsg)->ulReceiverPid    = RecvPid;

#define MNTN_IP_INFO_LEN                ((VOS_UINT32)sizeof(IPS_MNTN_IP_INFO_STRU))

#define MNTN_FLOW_CTRL_INFO_LEN         ((VOS_UINT32)sizeof(IPS_MNTN_FLOW_CTRL_STRU))

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum IPS_MNTN_TIMER_NAME_ENUM
{
    IPS_MNTN_INFO_TIMER                 = 0x00000001,           /*�����Բ���TCP/IPЭ��ջ������Ϣ��ʱ��*/

    IPS_MNTN_TIMER_NAME_BUTT
};
typedef VOS_UINT32 IPS_MNTN_TIMER_NAME_ENUM_UINT32;

/*TCP/IPЭ��ջ������Ϣ����*/
enum IPS_MNTN_INFO_TYPE_ENUM
{
    ID_IPS_MNTN_IFCONFIG_INFO           = 0x0001,               /*����������Ϣ*/
    ID_IPS_MNTN_NETSTAT_ROUTES_INFO     = 0x0002,               /*·����Ϣ*/
    ID_IPS_MNTN_NETSTAT_ENTRIES_INFO    = 0x0003,               /*����״̬��Ϣ*/
    ID_IPS_MNTN_NAT_RULES_INFO          = 0x0004,               /*NAT�������Ϣ*/
    ID_IPS_MNTN_NAT_STATS_INFO          = 0x0005,               /*NAT��״̬��Ϣ*/
    ID_IPS_MNTN_NAT_PROXIES_INFO        = 0x0006,               /*NAT��Э����Ϣ*/
    ID_IPS_MNTN_NAT_MAPPINGS_INFO       = 0x0007,               /*NAT��ӳ����Ϣ*/

    ID_IPS_MNTN_NAT_TYPE_BUTT           = 0xffff
};
typedef VOS_UINT16 IPS_MNTN_INFO_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 �ṹ����
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
 �ṹ��    : IPS_MNTN_INFO_ENTITY
 �ṹ˵��  : ����TCP/IPЭ��ջ������Ϣʵ��
*****************************************************************************/
typedef struct
{
    HTIMER                              hIpsMntnTimer;          /*��ʱ��*/
    VOS_UINT32                          ulIpsMntnTimerLen;      /*��ʱ�����ȣ��̶�1s*/
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enIpsMntnFlag;          /*����TCP/IPЭ��ջ������Ϣ������־*/
    VOS_UINT8                           aucData[2];
}IPS_MNTN_INFO_ENTITY;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_PKT_INFO_STRU
 �ṹ˵��  : TCP/IPЭ��ջ���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    VOS_UINT8                               aucNetIfName[IPS_IFNAMSIZ]; /* ������������ */
    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_PKT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_BRIDGE_PKT_INFO_STRU
 �ṹ˵��  : ������ת���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    VOS_UINT8                               aucSrcPort[IPS_END_NAME];   /* ��������������Ϣ */
    VOS_UINT8                               aucDestPort[IPS_END_NAME];  /* ���������������� */
    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_BRIDGE_PKT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_APP_CMD_INFO_STRU
 �ṹ˵��  : APP���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_APP_CMD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_INFO_STRU
 �ṹ˵��  : APP���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usType;
    VOS_UINT8                               aucData[2];
    VOS_UINT32                              ulLen;
} IPS_MNTN_INFO_STRU;


typedef struct
{
    VOS_UINT16          usPrimId;
    VOS_UINT16          usToolId;

    VOS_UINT32          ulFcType;
}IPS_MNTN_FLOW_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : IPS_MNTN_IP_INFO_STRU
 �ṹ˵��  : IPЭ��ջ���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    VOS_UINT8                               ucIpVer;        /* IP Э��汾 */
    VOS_UINT8                               ucL4Proto;      /* Э������ICMP,TCP,UDP */
    VOS_UINT8                               ucIcmpType;     /* ICMP��������*/
    VOS_UINT8                               aucRsv[1];
    VOS_UINT16                              usDataLen;      /* IP ���ݰ�����*/
    VOS_UINT16                              usIp4Id;        /* IPv4 IDENTIFY�ֶ� */
    VOS_UINT16                              usSrcPort;      /* IP Դ�˿ں�*/
    VOS_UINT16                              usDstPort;      /* IP Ŀ�Ķ˿ں� */
    VOS_UINT32                              ulL4Id;         /* ��4��IDENTIFY,ICMP IDENTIFY+SN,TCP SEQ */
    VOS_UINT32                              ulTcpAckSeq;    /* TCP ACK SEQ */
    VOS_UINT32                              ulParam1;    /* �Զ������ */
    VOS_UINT32                              ulParam2;    /* �Զ������ */
    VOS_UINT32                              ulParam3;    /* �Զ������ */
    VOS_UINT32                              ulParam4;    /* �Զ������ */
} IPS_MNTN_IP_INFO_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��������
*****************************************************************************/
extern VOS_VOID IPS_MNTN_SndCfgCnf2Om
(
    VOS_UINT32      ulPrimId,
    VOS_UINT32      ulTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
);

extern VOS_VOID IPS_MNTN_TraceAdvancedCfgReq(VOS_VOID *pMsg);

/* IP ���ݰ���ά�ɲ�*/
extern VOS_VOID IPS_MNTN_TraceIpInfo(
    struct sk_buff *skb,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType,
    VOS_UINT32 ulParam1,
    VOS_UINT32 ulParam2,
    VOS_UINT32 ulParam3,
    VOS_UINT32 ulParam4);
extern VOS_UINT32 IPS_MNTN_TransMsg
(
    VOS_UINT8                              *pucTransMsg,
    VOS_UINT32                              ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enMsgName
);
extern VOS_UINT32 IPS_MNTN_GetPktLenByTraceCfg
(
    IPS_MNTN_TRACE_CONFIG_STRU     *pstTraceCfg,
    const VOS_UINT8                *pucPktData,
    VOS_UINT16                      usPktLen,
    VOS_UINT32                     *pulDataLen
);
extern VOS_VOID IPS_MNTN_PktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
);
extern VOS_VOID IPS_MNTN_BridgePktInfoCB
(
    const VOS_UINT8                        *pucSrcPort,
    const VOS_UINT8                        *pucDestPort,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
);
extern VOS_VOID IPS_MNTN_CtrlPktInfoCB
(
    const VOS_UINT8                        *pucNetIfName,
    const VOS_UINT8                        *pucPktData,
    VOS_UINT16                              usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16           enType
);
extern PS_BOOL_ENUM_UINT8  IPS_MNTN_BridgeTraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg);
extern PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg);
extern PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceAdvancedCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg);
extern VOS_VOID IPS_MNTN_FlowCtrl(VOS_UINT32 ulFcType, TTF_MNTN_MSG_TYPE_ENUM_UINT16  enType);
extern VOS_VOID IPS_MNTN_Ipv4DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData);
extern VOS_VOID IPS_MNTN_Ipv6DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData);
extern VOS_UINT32 IPS_MNTN_GetIPInfoCfg(TTF_MNTN_MSG_TYPE_ENUM_UINT16 enType);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*_IPS_MNTN_H_*/


