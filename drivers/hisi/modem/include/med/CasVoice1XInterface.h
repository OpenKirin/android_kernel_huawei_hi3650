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

#ifndef _CASVOICE1XINTERFACE_H
#define _CASVOICE1XINTERFACE_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*******************************************************************************
 2. Macro definitions
*******************************************************************************/


/*******************************************************************************
 3. Enumerations declarations
*******************************************************************************/
/** ****************************************************************************
 * Name        : CAS_VOICE_1X_MSG_ID_ENUM_UINT16
 * Description :
 *******************************************************************************/
enum CAS_VOICE_1X_MSG_ID_ENUM
{
    ID_CAS_VOICE_1X_HO_START_IND                            = 0x9460,   /* Ho切换开始，向MED下发开始消息 */ /* _H2ASN_MsgChoice CAS_VOICE_1X_HO_START_IND_STRU */
    ID_CAS_VOICE_1X_HO_COMPLETE_IND                         = 0x9461,   /* Ho切换结束，向MED下发开始消息 */ /* _H2ASN_MsgChoice CAS_VOICE_1X_HO_COMPLETE_IND_STRU */
    ID_CAS_VOICE_1X_MSG_ID_BUTT
};
typedef VOS_UINT16 CAS_VOICE_1X_MSG_ID_ENUM_UINT16;


/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/
/*****************************************************************************
 实体名称  : CAS_VOICE_1X_HO_START_IND_STRU
 功能描述  : Handover切换的时候，需要给MED下发该消息告诉MED开始切换
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /*_H2ASN_Skip*/
    VOS_UINT16                          uhwOpId;                                /* 保留 */
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳,精度按20ms输出 */
}CAS_VOICE_1X_HO_START_IND_STRU;

/*****************************************************************************
 实体名称  : CAS_VOICE_1X_HO_COMPLETE_IND_STRU
 功能描述  : Handover切换结束，需要向MED下发该消息告诉MED切换结束
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /*_H2ASN_Skip*/
    VOS_UINT16                          uhwOpId;                                /* 保留 */
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳,精度按20ms输出 */
}CAS_VOICE_1X_HO_COMPLETE_IND_STRU;
/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/

/*******************************************************************************
 8. Global  declaration
*******************************************************************************/

/*******************************************************************************
 9. Function declarations
*******************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
