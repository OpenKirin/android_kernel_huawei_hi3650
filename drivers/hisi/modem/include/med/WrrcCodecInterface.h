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
 ö����    : CODEC_WRRC_MSG_TYPE_ENUM
 �ṹ˵��  : ԭ���ulMsgName
*****************************************************************************/
enum CODEC_WRRC_MSG_TYPE_ENUM
{
    ID_CODEC_WRR_NOISE_STATUS_IND           = 0x0000,   /* _H2ASN_MsgChoice CODEC_WRR_NOISE_STATUS_IND_STRU */
    ID_WRR_CODEC_SILENCE_STATUS_IND         = 0x0001,   /* _H2ASN_MsgChoice WRR_CODEC_SILENCE_STATUS_IND_STRU */
    ID_CODEC_WRR_MSG_TYPE_BUTT              = 0xFFFF
};
typedef VOS_UINT16 CODEC_WRRC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : CODEC_WRR_NOISE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ˮ��״ָ̬ʾ
*****************************************************************************/
enum CODEC_WRR_NOISE_STATUS_ENUM
{
    CODEC_WRR_NO_NOISE    = 0x00,
    CODEC_WRR_NOISE       = 0x01,
    CODEC_WRR_NOISE_BUTT
};

typedef VOS_UINT8 CODEC_WRR_NOISE_STATUS_ENUM_UINT8;

/*******************************************************************************
 �ṹ��    : CODEC_WRR_NOISE_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ CODEC_WRR_NOISE_STATUS_IND �Ľṹ
             ����Ϣ������Э��ջָʾ��ˮ����������ʧ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                      usMsgName;                  /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                      usReserve1;                 /* ���� */
    CODEC_WRR_NOISE_STATUS_ENUM_UINT8               enNoiseStatus;              /* �Ƿ������ˮ�� */
    VOS_UINT8                                       aucReserve[3];              /* ����λ */
}CODEC_WRR_NOISE_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WRR_CODEC_SILENCE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ĭ��ö��ֵ
*****************************************************************************/
enum WRR_CODEC_SILENCE_STATUS_ENUM
{
    CODEC_WRR_SILENCE_START = 0x00,
    CODEC_WRR_SILENCE_END   = 0X01,
    CODEC_WRR_SILENCE_BUTT
};
typedef VOS_UINT8 WRR_CODEC_SILENCE_STATUS_ENUM_UINT8;

/*******************************************************************************
 �ṹ��    : WRR_CODEC_SILENCE_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ WRR_CODEC_SILENCE_STATUS_IND �Ľṹ
             ����Ϣ����WRRָʾCODEC������Ĭ����رվ�Ĭ��
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                      usMsgName;                  /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                      usReserve1;                 /* ���� */
    WRR_CODEC_SILENCE_STATUS_ENUM_UINT8             enSilenceStatus;            /* �رա�������Ĭ��ָʾ */
    VOS_UINT8                                       aucReserve[3];              /* ����λ */
}WRR_CODEC_SILENCE_STATUS_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


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

#endif /* end of WrrcCodecInterface.h */



