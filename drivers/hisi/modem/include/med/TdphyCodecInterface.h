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

#ifndef __TDPHYCODECINTERFACE_H__
#define __TDPHYCODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* _H2ASN_Include v_typedef.h */
/* _H2ASN_Include codec_typedefine.h */
/* _H2ASN_Include PhyCodecInterface.h */
#include "vos.h"
#include "CodecInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TDPHY_VOICE_MSG_ID_ENUM
{
    /*====== VOICE->VOICE ======*/
    ID_VOICE_VOICE_TD_SYNC_IND                      = 0xDD06,                   /* TD�µ�ͬ���ж� */               /* _H2ASN_MsgChoice VOICE_VOICE_TD_SYNC_IND_STRU */

    /*====== TDPHY->VOICE ======*/
    ID_TDPHY_VOICE_RX_DATA_IND                      = 0xBD11,                   /* TD ��������ָʾ */              /* _H2ASN_MsgChoice TDPHY_VOICE_RX_DATA_IND_STRU */
    ID_TDPHY_VOICE_BACKGROUND_CNF                   = 0xBD21,                   /* TD �����ظ��ѽ��뾲Ĭģʽ */  /* _H2ASN_MsgChoice TDPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_TDPHY_VOICE_FOREGROUND_CNF                   = 0xBD31,                   /* TD �����ظ����˳���Ĭģʽ */  /* _H2ASN_MsgChoice TDPHY_VOICE_FOREGROUND_CNF_STRU */

    /*====== VOICE->TDPHY ======*/
    ID_VOICE_TDPHY_TX_DATA_IND                      = 0xDB11,                   /* TD ���������� */              /* _H2ASN_MsgChoice VOICE_TDPHY_TX_DATA_IND_STRU */
    ID_VOICE_TDPHY_BACKGROUND_REQ                   = 0xDB12,                   /* TD ֪ͨPHY���뾲Ĭ����ģʽ */   /* _H2ASN_MsgChoice VOICE_TDPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_TDPHY_FOREGROUND_REQ                   = 0xDB13,                   /* TD ֪ͨPHY�˳���Ĭģʽ */       /* _H2ASN_MsgChoice VOICE_TDPHY_FOREGROUND_REQ_STRU */

    TDPHY_VOICE_MSG_ID_BUTT
};
typedef unsigned short TDPHY_VOICE_MSG_ID_ENUM_UINT16;

enum TDPHY_VOICE_RESULT_ENUM
{
    TDPHY_VOICE_RESULT_SUCC,
    TDPHY_VOICE_RESULT_FAIL,

    TDPHY_VOICE_RESULT_BUTT,
};
typedef VOS_UINT16 TDPHY_VOICE_RESULT_ENUM_UINT16;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
 ʵ������  : VOICE_VOICE_TD_SYNC_IND_STRU
 ��������  : ����ҵ�������󣬽���֡�жϺ���ͬ����Ϣ���Լ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    unsigned short                      uhwMsgId;                               /* 0xDD06*/ /*_H2ASN_Skip*/
    unsigned short                      uhwReserve;                             /* ����*/   /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
}VOICE_VOICE_TD_SYNC_IND_STRU;

/*****************************************************************************
 ʵ������  : TDPHY_VOICE_RX_DATA_IND_STRU
 ��������  : TDPHYȡ��AMR�����󣬽��н��ܣ���������͸���Ϣ��VOICE�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    unsigned short                      uhwMsgId;                               /* 0xBD11*/ /*_H2ASN_Skip*/
    unsigned short                      uhwReserved;                            /* ���� */  /*_H2ASN_Replace VOS_UINT16 uhwReserved;*/
    WPHY_VOICE_DATA_STRU
}TDPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_TDPHY_TX_DATA_IND_STRU
 ��������  : VOICE����������OK�󣬷��͸���Ϣ��TDPHY�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    unsigned short                      uhwMsgId;                               /* 0xDB11*/  /*_H2ASN_Skip*/
    unsigned short                      uhwFrameType;                           /* ֡���� */ /*_H2ASN_Replace CODEC_AMR_TYPE_TX_ENUM_UINT16 uhwFrameType;*/
    WPHY_VOICE_DATA_STRU
}VOICE_TDPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_TDPHY_BACKGROUND_REQ_STRU
 �ṹ˵��  : VOICEģ��֪ͨPHY���뾲Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve;
} VOICE_TDPHY_BACKGROUND_REQ_STRU;

/*****************************************************************************
 ʵ������  :  VOICE_TDPHY_FOREGROUND_REQ_STRU
 �ṹ˵��  :  VOICEģ��֪ͨPHY�˳���Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VOICE_TDPHY_FOREGROUND_REQ_STRU;

/*****************************************************************************
 ʵ������  : GUPHY_VOICE_FOREGROUND_CNF_STRU
 �ṹ˵��  : PHY�ظ�CODEC�ѽ�����������ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserve[2];
} TDPHY_VOICE_FOREGROUND_CNF_STRU;

/*****************************************************************************
 ʵ������  : PHY_CODEC_BACKGROUND_CNF_STRU
 �ṹ˵��  : PHY�ظ�CODEC�ѽ��뾲Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserve[2];
} TDPHY_VOICE_BACKGROUND_CNF_STRU;

/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
#if 0                                                                           /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    TDPHY_VOICE_MSG_ID_ENUM_UINT16          enMsgID;                              /* _H2ASN_MsgChoice_Export TDPHY_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TDPHY_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_TDPHY_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_TDPHY_TRACE_MSG_DATA              stMsgData;
}VoiceTdphyTrace_MSG;

#endif                                                                          /* _H2ASN_Skip */

/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of tdphycodecinterface.h */

