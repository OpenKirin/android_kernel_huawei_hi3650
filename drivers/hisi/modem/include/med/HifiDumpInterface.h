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


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "OmCodecInterface.h"

#ifndef __HIFIDUMPINTERFACE_H__
#define __HIFIDUMPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 定义数组变量, 其包含HiFi复位时需要dump保存并成文件的内存块信息 */
#define OM_DEFINE_HIFI_DUMP_BLK_TABLE   \
OM_DUMP_BLK_INFO_STRU g_astOmHiFiToDumpBlks[] = \
{   \
    {0x2bff8000UL,                      0x8000UL},  /* DTCM, 32KB */    \
    {0x2c000000UL,                      0x2000UL},  /* ITCM,  8KB */    \
    {IPC_MAILBOX_HEAD_ADDR_HIFI2CARM,   sizeof(IPC_MAILBOX_HEAD_STRU)}, \
    {IPC_MAILBOX_ADDR_HIFI2CARM,        IPC_MAILBOX_SIZE_HIFI2CARM},    \
    {IPC_MAILBOX_HEAD_ADDR_CARM2HIFI,   sizeof(IPC_MAILBOX_HEAD_STRU)}, \
    {IPC_MAILBOX_ADDR_CARM2HIFI,        IPC_MAILBOX_SIZE_CARM2HIFI},    \
    {IPC_MAILBOX_HEAD_ADDR_HIFI2ZSP,    sizeof(IPC_MAILBOX_HEAD_STRU)}, \
    {IPC_MAILBOX_ADDR_HIFI2ZSP,         IPC_MAILBOX_SIZE_HIFI2ZSP},     \
    {IPC_MAILBOX_HEAD_ADDR_ZSP2HIFI,    sizeof(IPC_MAILBOX_HEAD_STRU)}, \
    {IPC_MAILBOX_ADDR_ZSP2HIFI,         IPC_MAILBOX_SIZE_ZSP2HIFI},     \
    {PC_VOICE_OM_CODEC_ADDR,              sizeof(OMMED_RING_BUFFER_CONTROL_STRU)},\
    {PC_VOICE_CODEC_OM_ADDR,              sizeof(OMMED_RING_BUFFER_CONTROL_STRU)},\
    {0x2bff8000UL,                      0x8000UL}   /* DTCM, 32KB */    \
}

/* 获取HiFi dump内存块信息数组地址 */
#define OM_GetHiFiDumpBlkTbl()          (&g_astOmHiFiToDumpBlks[0])

/* 获取HiFi dump内存块数 */
#define OM_GetHiFiDumpBlkNum()          (sizeof(g_astOmHiFiToDumpBlks)/sizeof(OM_DUMP_BLK_INFO_STRU))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结 构 名  : OM_DUMP_BLK_INFO_STRU
 功能描述  : 定义HiFi DUMP内存块
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwBlkAddr;          /* DUMP块首地址 */
    VOS_UINT32                          uwBlkLen;           /* DUMP块长度, 单位byte */
}OM_DUMP_BLK_INFO_STRU;



/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
/*
 DUMP文件格式:

 时戳(32bit), 内存块1
 时戳(32bit), 内存块2
 时戳(32bit), 内存块3
 ...
 时戳(32bit), 内存块n
*/

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

#endif /* end of HifiDumpInterface.h */
