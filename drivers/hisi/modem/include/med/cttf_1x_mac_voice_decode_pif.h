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

#ifndef CTTF_1X_MAC_VOICE_DECODE_PIF_H
#define CTTF_1X_MAC_VOICE_DECODE_PIF_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/
#include "vos.h"
#include "CodecInterface.h"
#include "cttf_1x_voice_data_public_pif.h"

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
 * Name        : CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_UINT16
 * Description :
 *******************************************************************************/
enum CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM
{
    ID_CTTF_VOICE_1X_RX_DATA_IND                            = 0x9471, /* _H2ASN_MsgChoice CTTF_VOICE_1X_RX_DATA_IND_STRU*/ /**< @sa CTTF_VOICE_1X_RX_DATA_IND_STRU */
    ID_CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_BUTT      = 0xFFFF
};
typedef VOS_UINT16 CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_UINT16;


/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/

/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/
/** ****************************************************************************
 * Name        : CTTF_VOICE_1X_RX_DATA_IND_STRU
 * Description : 1x_MAC_Demux uses this signal to deliver received speech data
 * to voice SO. Frame_quality roots from PHY.
 * If @enCodecType is EVRC, it's SO 3 data, and EVRC-B, it's SO 68. Using
 * @enCodecType, Voice can check whether SO are the same in MAC and Voice,
 * now. If not matched, Voice should discard current voice data.
 * @ulSenderPid: It's convenient for MAC that only receiving message from one
 * PID. So @ulSenderPid is always DSP_PID_VOICE in this message.
 * @ulReceiverPid: As requirement from CTTF team, it's MSPS_PID_1X_RMAC in
 * this message.
 * @usOpId: We used it to debug. It's like swift number or running number in
 * bank. The 1st message, it's 0, the next message, it's 1, and so on. In
 * debug tool, like SDT or HiDS, we can know whether there is any message
 * lost, if @usOpId is not consecutive. It's maintained by sender--MAC,
 * receiver--Voice can ignore it in this message.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                           /* _H2ASN_Skip */
    CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_UINT16       enMsgId;         /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              enFrameQuality;
    CODEC_ENUM_UINT16                                       enCodecType;
    MACITF_VOICE_RATE_TYPE_ENUM_UINT16                      enVoiceDataRate;
    VOS_UINT16                                              ausData[CTTF_1X_MAX_VOICE_DATA_BLOCK_SIZE];
}CTTF_VOICE_1X_RX_DATA_IND_STRU;


/*******************************************************************************
 8. Global  declaration
*******************************************************************************/

/*******************************************************************************
 9. Function declarations
*******************************************************************************/
/** ****************************************************************************
 * Name        : CTTF_1x_MAC_Voice_Decode_PIF_MSG_DATA
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_UINT16       enMsgId;     /* _H2ASN_MsgChoice_Export CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_UINT16 */
    VOS_UINT8                                               aucMsgBlock[2];

    /* _H2ASN_MsgChoice_When_Comment CTTF_1X_MAC_VOICE_DECODE_PIF_MSG_TYPE_ENUM_UINT16 */
}CTTF_1x_MAC_Voice_Decode_PIF_MSG_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : CTTF_1x_MAC_Voice_Decode_PIF
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CTTF_1x_MAC_Voice_Decode_PIF_MSG_DATA                   stMsgData;
}CTTF_1x_MAC_Voice_Decode_PIF;


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
