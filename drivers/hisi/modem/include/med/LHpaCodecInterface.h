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


#ifndef __LHPACODECINTERFACE_H__
#define __LHPACODECINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
enum LHPA_VOICE_MSG_TYPE_ENUM
{
    ID_LHPA_VOICE_SYNC_IND           = 0x94D0,           /* _H2ASN_MsgChoice LHPA_VOICE_SYNC_IND_STRU */

    LHPA_VOICE_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16  LHPA_VOICE_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
 ʵ������  : LHPA_VOICE_SYNC_IND_STRU
 ��������  : VoLTE����ҵ��������LHPA���͸���Ϣ��CODEC����ʱ��ͬ��
            |------------------|-------------------|-----OnDuration-----|
            |                  |<--uhwSendOffset-->|
            |<---uhwWakeUpOffset------------------>|
            |                  |                   |
            |                  |                   |
            HIFI����ʱ��       HIFI����������ʱ��  CDRX OnDuration��ʼʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* ����*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwOpId;                                /* ÿ����1����Ϣ�����ֶμ�1*/

    VOS_UINT32                          uwForceSyncFlag;                        /* LPHY֪ͨHIFI��ǿ��ͬ����ʶ*/
    VOS_UINT32                          uwOnDurationSlice;                      /* LPHY������LTE CDRX OnDuration��ʼʱ��*/
    VOS_UINT16                          uhwWakeUpOffset;                        /* ��uwOnDurationSliceΪ���㣬HIFI������ǰ��*/
    VOS_UINT16                          uhwSendOffset;                          /* ��uwOnDurationSliceΪ���㣬HIFI����������ǰ�� */
}LHPA_VOICE_SYNC_IND_STRU;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/
#if 0                                                                           /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    LHPA_VOICE_MSG_TYPE_ENUM_UINT16          enMsgID;                              /* _H2ASN_MsgChoice_Export LHPA_VOICE_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LHPA_VOICE_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}VOICE_LHPA_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_LHPA_TRACE_MSG_DATA              stMsgData;
}VoiceLhpaTrace_MSG;

#endif    																		/* _H2ASN_Skip */


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
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

#endif /* end of LHpaCodecInterface.h */



