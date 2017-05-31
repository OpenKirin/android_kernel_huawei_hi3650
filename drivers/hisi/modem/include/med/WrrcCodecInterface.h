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


#ifndef __WRRCCODECINTERFACE_H__
#define __WRRCCODECINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CODEC_WRRC_MSG_TYPE_ENUM
 结构说明  : 原语的ulMsgName
*****************************************************************************/
enum CODEC_WRRC_MSG_TYPE_ENUM
{
    ID_CODEC_WRR_NOISE_STATUS_IND           = 0x0000,   /* _H2ASN_MsgChoice CODEC_WRR_NOISE_STATUS_IND_STRU */
    ID_WRR_CODEC_SILENCE_STATUS_IND         = 0x0001,   /* _H2ASN_MsgChoice WRR_CODEC_SILENCE_STATUS_IND_STRU */
    ID_CODEC_WRR_MSG_TYPE_BUTT              = 0xFFFF
};
typedef VOS_UINT16 CODEC_WRRC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : CODEC_WRR_NOISE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 流水声状态指示
*****************************************************************************/
enum CODEC_WRR_NOISE_STATUS_ENUM
{
    CODEC_WRR_NO_NOISE    = 0x00,
    CODEC_WRR_NOISE       = 0x01,
    CODEC_WRR_NOISE_BUTT
};

typedef VOS_UINT8 CODEC_WRR_NOISE_STATUS_ENUM_UINT8;

/*******************************************************************************
 结构名    : CODEC_WRR_NOISE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 CODEC_WRR_NOISE_STATUS_IND 的结构
             该消息用于向协议栈指示流水声发生或消失
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                      usMsgName;                  /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                      usReserve1;                 /* 保留 */
    CODEC_WRR_NOISE_STATUS_ENUM_UINT8               enNoiseStatus;              /* 是否存在流水声 */
    VOS_UINT8                                       aucReserve[3];              /* 保留位 */
}CODEC_WRR_NOISE_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : WRR_CODEC_SILENCE_STATUS_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 静默音枚举值
*****************************************************************************/
enum WRR_CODEC_SILENCE_STATUS_ENUM
{
    CODEC_WRR_SILENCE_START = 0x00,
    CODEC_WRR_SILENCE_END   = 0X01,
    CODEC_WRR_SILENCE_BUTT
};
typedef VOS_UINT8 WRR_CODEC_SILENCE_STATUS_ENUM_UINT8;

/*******************************************************************************
 结构名    : WRR_CODEC_SILENCE_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息 WRR_CODEC_SILENCE_STATUS_IND 的结构
             该消息用于WRR指示CODEC启动静默音或关闭静默音
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                      usMsgName;                  /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                      usReserve1;                 /* 保留 */
    WRR_CODEC_SILENCE_STATUS_ENUM_UINT8             enSilenceStatus;            /* 关闭、启动静默音指示 */
    VOS_UINT8                                       aucReserve[3];              /* 保留位 */
}WRR_CODEC_SILENCE_STATUS_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

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

#endif /* end of WrrcCodecInterface.h */



