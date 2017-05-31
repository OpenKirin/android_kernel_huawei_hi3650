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


#ifndef __HDLC_INTERFACE_H__
#define __HDLC_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "vos.h"

#if (VOS_RTOSCK == VOS_OS_VER)
#include "TTFMem.h"
#include "PsTypeDef.h"
#else
#include "ImmInterface.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/chap.h"
#include "PPP/Inc/pap.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/proto.h"
#endif /* end of VOS_RTOSCK */

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

#if (VOS_RTOSCK == VOS_OS_VER)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����PPPC_HDLC_ST_TESTʱ����PppcHdlcStTest.c��������ڵ���������ST��������ʽ�汾������˺� */
/* #define PPPC_HDLC_ST_TEST */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ��Ӳ��HDLC�����ؽ��
*****************************************************************************/
enum PPP_HDLC_RESULT_TYPE_ENUM
{
    PPP_HDLC_RESULT_COMM_FINISH           = 0,      /* ���δ���������� */
    PPP_HDLC_RESULT_COMM_CONTINUE         = 1,      /* ���δ��������������������ڶ����д��´μ��������������Ƶ����������� */
    PPP_HDLC_RESULT_COMM_ERROR            = 2,      /* ���δ������ */

    PPP_HDLC_RESULT_BUTT
};
typedef VOS_UINT32   PPP_HDLC_RESULT_TYPE_ENUM_UINT32;

/*****************************************************************************
 PPP��������
*****************************************************************************/
enum PPP_DATA_TYPE_ENUM
{
    PPP_PULL_PACKET_TYPE = 1,                       /* IP������������ */
    PPP_PUSH_PACKET_TYPE,                           /* IP������������ */
    PPP_PULL_RAW_DATA_TYPE,                         /* PPP������������ */
    PPP_PUSH_RAW_DATA_TYPE                          /* PPP������������ */
};
typedef VOS_UINT8   PPP_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT16                          usProtocol;
    VOS_UINT8                           aucReserve[4];
    TTF_MEM_ST                         *pstMem;
}HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU;

#else
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NPROTOSTAT                  (13)

extern struct link*                 pgPppLink;

#define PPP_LINK(PppId)             ((pgPppLink + PppId) - 1)
#define PPP_LINK_TO_ID(pLink)       ((pLink - pgPppLink) + 1)

#define LINK_QUEUES(link) (sizeof (link)->Queue / sizeof (link)->Queue[0])
#define LINK_HIGHQ(link) ((link)->Queue + LINK_QUEUES(link) - 1)

#define PPP_HDLC_PROC_AS_FRM_PACKET_IND         (100)

#if (VOS_WIN32 == VOS_OS_VER)
#define PPP_ST_TEST
#define PPP_ONCE_DEAL_MAX_CNT       (2000)
#else
/* ����PPP_ST_TESTʱ����PppStTest.c��������ڵ���������ST��������ʽ�汾������˺� */
#define PPP_ONCE_DEAL_MAX_CNT       (100)
#endif
/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ��Ӳ��HDLC�����ؽ��
*****************************************************************************/
enum PPP_HDLC_RESULT_TYPE_ENUM
{
    PPP_HDLC_RESULT_COMM_FINISH           = 0,      /* ���δ���������� */
    PPP_HDLC_RESULT_COMM_CONTINUE         = 1,      /* ���δ��������������������ڶ����д��´μ��������������Ƶ����������� */
    PPP_HDLC_RESULT_COMM_ERROR            = 2,      /* ���δ������ */

    PPP_HDLC_RESULT_BUTT
};
typedef VOS_UINT32   PPP_HDLC_RESULT_TYPE_ENUM_UINT32;

/*****************************************************************************
 PPP��������
*****************************************************************************/
enum PPP_DATA_TYPE_ENUM
{
    PPP_PULL_PACKET_TYPE = 1,                       /* IP������������ */
    PPP_PUSH_PACKET_TYPE,                           /* IP������������ */
    PPP_PULL_RAW_DATA_TYPE,                         /* PPP������������ */
    PPP_PUSH_RAW_DATA_TYPE                          /* PPP������������ */
};
typedef VOS_UINT8   PPP_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����Ϣ���Ͷ���
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 ��Ӳ��HDLC������ԭ�ͣ��ڴ���PPPʵ���ʱ�򣬸�����Ҫ�������ؽ�
 �����Ӳ����ʵ�����ʵ�����
*****************************************************************************/
typedef PPP_HDLC_RESULT_TYPE_ENUM_UINT32 (* PPP_HDLC_PROC_DATA_FUNC )
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

/*****************************************************************************
 ����PPPЭ��ջ�����Э�������Ҫ��װ�󷢸�PC����Ҫ��PPPЭ���ڼ����
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_PROC_PROTOCOL_PACKET_FUNC )
(
    struct link *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32 ulPri,
    VOS_UINT16 usProtocol
);

/*****************************************************************************
 ����PPPЭ��ջ�����Э��������з�װ�Ĵ���������Ҫ��PPPЭ���ڼ����
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_PROC_AS_FRM_PACKET_FUNC )
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);

/*****************************************************************************
 ȥʹ��HDLC����ԭ�ͣ�Ӳ��HDLC��Ҫʵ�ִ˽ӿڣ��������Ҫ
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_DISABLE_FUNC )(VOS_VOID);

struct link {
  VOS_INT32 type;                           /* _LINK type */
  VOS_INT32 len;                            /* full size of parent struct */
  const VOS_CHAR *name;                     /* Points to datalink::name */
  struct {
    unsigned gather : 1;                    /* Gather statistics ourself ? */
    struct pppThroughput total;             /* Link throughput statistics */
    struct pppThroughput *parent;           /* MP link throughput statistics */
  } stats;
  struct ppp_mqueue Queue[2];               /* Our output queue of mbufs */

  VOS_UINT32 proto_in[NPROTOSTAT];          /* outgoing protocol stats */
  VOS_UINT32 proto_out[NPROTOSTAT];         /* incoming protocol stats */

  struct lcp lcp;                           /* Our line control FSM */

  VOS_UINT32 phase;                         /* Curent phase */
  VOS_INT32 timer_state;
  struct ipcp ipcp;
  struct pap  pap;
  struct chap chap;                         /* Authentication using chap, added by liukai */

  struct async async;
  struct hdlc hdlc;

  struct layer const *layer[LAYER_MAX];     /* i/o layers */
  VOS_INT32 nlayers;

  VOS_UINT32 DropedPacketFromGgsn;
};

/*****************************************************************************
 ��Ӳ��HDLC���ýṹ��
*****************************************************************************/
typedef struct _PPP_HDLC_CONFIG_STRU
{
    PPP_HDLC_PROC_DATA_FUNC                 pFunProcData;           /* ָ�������Ӳ������������ݺ���ָ�� */
    PPP_HDLC_PROC_PROTOCOL_PACKET_FUNC      pFunProcProtocolPacket; /* ָ�������Ӳ������Э��ջ������ݺ���ָ�� */
    PPP_HDLC_DISABLE_FUNC                   pFunDisable;            /* ָ�������Ӳ������ȥʹ�ܺ���ָ�� */
    PPP_HDLC_PROC_AS_FRM_PACKET_FUNC        pFunProcAsFrmData;      /* ָ�������Ӳ�������Է�װ��ʽ������ָ�� */
}PPP_HDLC_CONFIG_STRU;
extern PPP_HDLC_CONFIG_STRU        *g_pstHdlcConfig;

/*****************************************************************************
 Э��ջ���Э�̰���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT16                          usProtocol;
    VOS_UINT8                           aucReserve[4];
    PPP_ZC_STRU                        *pstMem;
}HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : PPP_HDLC_ProcIpModeUlData
 ��������  : IP���Ͳ��ţ������Ӳ�����װ��ɺ󣬵��ô˽ӿڴ����������
 �������  : pstLink    -   PPP��·��Ϣ
             pstMem     -   ���װ�󵥸�������ݰ�
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
VOS_VOID PPP_HDLC_ProcIpModeUlData
(
    struct link *pstLink,
    PPP_ZC_STRU *pstMem,
    VOS_UINT16  usProto
);

/*****************************************************************************
 �� �� ��  : PPP_HDLC_ProcPppModeUlData
 ��������  : PPP���Ͳ��ţ������Ӳ�����װ��ɺ󣬵��ô˽ӿڴ����������
 �������  : usPppId    -   PPPʵ��ID
             pstMem     -   ���װ�󵥸�������ݰ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_ProcPppModeUlData
(
    PPP_ID      usPppId,
    PPP_ZC_STRU *pstMem
);


/*****************************************************************************
 �� �� ��  : PPP_HDLC_ProcDlData
 ��������  : �����Ӳ����װ��ɺ󣬵��ô˽ӿڴ����������
 �������  : usPppId    -   PPPʵ��ID
             pstMem     -   ��װ��IP����Ӧ��PPP֡���ݣ�����IP����װ����ֳܷɶ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��10��
    ��    ��   : l00164359
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HDLC_ProcDlData(VOS_UINT16 usPppId, PPP_ZC_STRU *pstMem);

#endif /* end of VOS_RTOSCK */

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of hdlc_interface.h */

