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
  1 其他头文件包含
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
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TDPHY_VOICE_MSG_ID_ENUM
{
    /*====== VOICE->VOICE ======*/
    ID_VOICE_VOICE_TD_SYNC_IND                      = 0xDD06,                   /* TD下的同步中断 */               /* _H2ASN_MsgChoice VOICE_VOICE_TD_SYNC_IND_STRU */

    /*====== TDPHY->VOICE ======*/
    ID_TDPHY_VOICE_RX_DATA_IND                      = 0xBD11,                   /* TD 语音解码指示 */              /* _H2ASN_MsgChoice TDPHY_VOICE_RX_DATA_IND_STRU */
    ID_TDPHY_VOICE_BACKGROUND_CNF                   = 0xBD21,                   /* TD 物理层回复已进入静默模式 */  /* _H2ASN_MsgChoice TDPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_TDPHY_VOICE_FOREGROUND_CNF                   = 0xBD31,                   /* TD 物理层回复已退出静默模式 */  /* _H2ASN_MsgChoice TDPHY_VOICE_FOREGROUND_CNF_STRU */

    /*====== VOICE->TDPHY ======*/
    ID_VOICE_TDPHY_TX_DATA_IND                      = 0xDB11,                   /* TD 语音编码结果 */              /* _H2ASN_MsgChoice VOICE_TDPHY_TX_DATA_IND_STRU */
    ID_VOICE_TDPHY_BACKGROUND_REQ                   = 0xDB12,                   /* TD 通知PHY进入静默工作模式 */   /* _H2ASN_MsgChoice VOICE_TDPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_TDPHY_FOREGROUND_REQ                   = 0xDB13,                   /* TD 通知PHY退出静默模式 */       /* _H2ASN_MsgChoice VOICE_TDPHY_FOREGROUND_REQ_STRU */

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
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/
/*****************************************************************************
 实体名称  : VOICE_VOICE_TD_SYNC_IND_STRU
 功能描述  : 语音业务启动后，接收帧中断后发送同步消息给自己
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    unsigned short                      uhwMsgId;                               /* 0xDD06*/ /*_H2ASN_Skip*/
    unsigned short                      uhwReserve;                             /* 保留*/   /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
}VOICE_VOICE_TD_SYNC_IND_STRU;

/*****************************************************************************
 实体名称  : TDPHY_VOICE_RX_DATA_IND_STRU
 功能描述  : TDPHY取出AMR码流后，进行解密，解密完后发送该消息给VOICE将数据发送过去
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    unsigned short                      uhwMsgId;                               /* 0xBD11*/ /*_H2ASN_Skip*/
    unsigned short                      uhwReserved;                            /* 保留 */  /*_H2ASN_Replace VOS_UINT16 uhwReserved;*/
    WPHY_VOICE_DATA_STRU
}TDPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_TDPHY_TX_DATA_IND_STRU
 功能描述  : VOICE在上行数据OK后，发送该消息给TDPHY将数据发送过去
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    unsigned short                      uhwMsgId;                               /* 0xDB11*/  /*_H2ASN_Skip*/
    unsigned short                      uhwFrameType;                           /* 帧类型 */ /*_H2ASN_Replace CODEC_AMR_TYPE_TX_ENUM_UINT16 uhwFrameType;*/
    WPHY_VOICE_DATA_STRU
}VOICE_TDPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_TDPHY_BACKGROUND_REQ_STRU
 结构说明  : VOICE模块通知PHY进入静默工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve;
} VOICE_TDPHY_BACKGROUND_REQ_STRU;

/*****************************************************************************
 实体名称  :  VOICE_TDPHY_FOREGROUND_REQ_STRU
 结构说明  :  VOICE模块通知PHY退出静默工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
} VOICE_TDPHY_FOREGROUND_REQ_STRU;

/*****************************************************************************
 实体名称  : GUPHY_VOICE_FOREGROUND_CNF_STRU
 结构说明  : PHY回复CODEC已进入正常工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserve[2];
} TDPHY_VOICE_FOREGROUND_CNF_STRU;

/*****************************************************************************
 实体名称  : PHY_CODEC_BACKGROUND_CNF_STRU
 结构说明  : PHY回复CODEC已进入静默工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserve[2];
} TDPHY_VOICE_BACKGROUND_CNF_STRU;

/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
#if 0                                                                           /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    TDPHY_VOICE_MSG_ID_ENUM_UINT16          enMsgID;                              /* _H2ASN_MsgChoice_Export TDPHY_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TDPHY_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_TDPHY_TRACE_MSG_DATA;

/* 协议消息结构*/
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
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of tdphycodecinterface.h */

