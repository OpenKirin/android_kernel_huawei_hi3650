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


#ifndef __WTTFCODECINTERFACE_H__
#define __WTTFCODECINTERFACE_H__

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
#define WTTFVOICE_AMR_CODEC_MODE_NUM    (11)             /* AMR-NB��AMR-WB���ã�ȡ���ֵ��CODEC_MODE ��������11�֣�������SID */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum WTTFVOICE_AMR_CODECMODE_TYPE_ENUM
{
    WTTFVOICE_AMR_CODECMODE_TYPE_475K          = 0,                             /* 4.75K���ݸ�ʽ: class a 42bit, b 53bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_515K          = 1,                             /* 5.15K���ݸ�ʽ: class a 49bit, b 54bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_590K          = 2,                             /* 5.9 K���ݸ�ʽ: class a 55bit, b 63bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_670K          = 3,                             /* 6.7 K���ݸ�ʽ: class a 58bit, b 76bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_740K          = 4,                             /* 7.4 K���ݸ�ʽ: class a 61bit, b 87bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_795K          = 5,                             /* 7.95K���ݸ�ʽ: class a 75bit, b 84bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_102K          = 6,                             /* 10.2K���ݸ�ʽ: class a 65bit, b 99bit , c 40bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_122K          = 7,                             /* 12.2K���ݸ�ʽ: class a 81bit, b 103bit, c 60bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_BUTT
};
typedef  VOS_UINT16 WTTFVOICE_AMR_CODECMODE_TYPE_ENUM_UINT16; 

enum WTTFVOICE_AMRWB_CODECMODE_TYPE_ENUM
{
    WTTFVOICE_AMRWB_CODECMODE_TYPE_660K        = 0,                             /* 6.60K���ݸ�ʽ:   class a 54bit, b 78bit , c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_885K        = 1,                             /* 8.85K���ݸ�ʽ:   class a 64bit, b 113bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1265K       = 2,                             /* 12.65 K���ݸ�ʽ: class a 72bit, b 181bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1425K       = 3,                             /* 14.25 K���ݸ�ʽ: class a 72bit, b 213bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1585K       = 4,                             /* 15.85 K���ݸ�ʽ: class a 72bit, b 245bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1825K       = 5,                             /* 18.25K���ݸ�ʽ:  class a 72bit, b 293bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1985K       = 6,                             /* 19.85K���ݸ�ʽ:  class a 72bit, b 325bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_2305K       = 7,                             /* 23.05K���ݸ�ʽ:  class a 72bit, b 389bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_2385K       = 8,                             /* 23.85K���ݸ�ʽ:  class a 72bit, b 405bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1585K_B     = 9,                             /* 15.85 K���ݸ�ʽ: class a 72bit, b 245bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_2385K_B     = 10,                             /* 23.85K���ݸ�ʽ:  class a 72bit, b 405bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_BUTT
};
typedef  VOS_UINT16 WTTFVOICE_AMRWB_CODECMODE_TYPE_ENUM_UINT16;

enum WTTFVOICE_AMR_FRAME_TYPE_ENUM
{
    WTTFVOICE_AMR_FRAME_TYPE_475K         = 0,    /* 4.75K���ݸ�ʽ: class a 42bit, b 53bit */
    WTTFVOICE_AMR_FRAME_TYPE_515K         = 1,    /* 5.15K���ݸ�ʽ: class a 49bit, b 54bit */
    WTTFVOICE_AMR_FRAME_TYPE_590K         = 2,    /* 5.9 K���ݸ�ʽ: class a 55bit, b 63bit */
    WTTFVOICE_AMR_FRAME_TYPE_670K         = 3,    /* 6.7 K���ݸ�ʽ: class a 58bit, b 76bit */
    WTTFVOICE_AMR_FRAME_TYPE_740K         = 4,    /* 7.4 K���ݸ�ʽ: class a 61bit, b 87bit */
    WTTFVOICE_AMR_FRAME_TYPE_795K         = 5,    /* 7.95K���ݸ�ʽ: class a 75bit, b 84bit */
    WTTFVOICE_AMR_FRAME_TYPE_102K         = 6,    /* 10.2K���ݸ�ʽ: class a 65bit, b 99bit , c 40bit */
    WTTFVOICE_AMR_FRAME_TYPE_122K         = 7,    /* 12.2K���ݸ�ʽ: class a 81bit, b 103bit, c 60bit */
    WTTFVOICE_AMR_FRAME_TYPE_SID          = 8,    /* SID֡���ݸ�ʽ: class a 39bit */

    WTTFVOICE_AMR_FRAME_TYPE_BUTT
};
typedef  VOS_UINT8    WTTFVOICE_AMR_FRAME_TYPE_ENUM_UINT8;

enum WTTFVOICE_AMRWB_FRAME_TYPE_ENUM
{
    WTTFVOICE_AMRWB_FRAME_TYPE_660K         = 0,    /* 6.60K���ݸ�ʽ: class a 54bit, b 78bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_885K         = 1,    /* 8.85K���ݸ�ʽ: class a 64bit, b 113bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1265K        = 2,    /* 12.65K���ݸ�ʽ: class a 72bit, b 181bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1425K        = 3,    /* 14.25K���ݸ�ʽ: class a 72bit, b 213bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1585K        = 4,    /* 15.85K���ݸ�ʽ: class a 72bit, b 245bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1825K        = 5,    /* 18.25K���ݸ�ʽ: class a 72bit, b 293bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1985K        = 6,    /* 19.85K���ݸ�ʽ: class a 72bit, b 325bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_2305K        = 7,    /* 23.05K���ݸ�ʽ: class a 72bit, b 389bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_2385K        = 8,    /* 23.85K���ݸ�ʽ: class a 72bit, b 405bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_SID          = 9,    /* SID֡1.75K���ݸ�ʽ: class a 40bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1585K_B      = 10,   /* 15.85K���ݸ�ʽ: class a 73bit, b 244bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_2385K_B      = 11,   /* 23.85K���ݸ�ʽ: class a 74bit, b 403bit */

    WTTFVOICE_AMRWB_FRAME_TYPE_BUTT
};
typedef  VOS_UINT16    WTTFVOICE_AMRWB_FRAME_TYPE_ENUM_UINT16;


enum WTTFVOICE_AMR_TYPE_ENUM
{
    WTTFVOICE_AMR_TYPE_AMR2               = 0,
    WTTFVOICE_AMR_TYPE_AMR                = 1,
    WTTFVOICE_AMR_TYPE_AMRWB              = 2,
    WTTFVOICE_AMR_TYPE_BUTT
};
typedef VOS_UINT16 WTTFVOICE_AMR_TYPE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_FORMAT_ENUM
 ��������  : AMRխ���Ϳ������, �μ�3GPP TS 26.101
*****************************************************************************/
enum WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM
{
    WTTFVOICE_AMR_BANDWIDTH_TYPE_NB             = 0,
    WTTFVOICE_AMR_BANDWIDTH_TYPE_WB             = 1,
    WTTFVOICE_AMR_BANDWIDTH_TYPE_BUTT
};
typedef VOS_UINT16 WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : WTTFVOICE_RSLT_ENUM
 ��������  : WTTF��CODEC֮�䷵��ֵ����
*****************************************************************************/
enum WTTFVOICE_RSLT_ENUM
{
    WTTFVOICE_RSLT_SUCC             = 0,                                    /* ���ظ�MAC, �ɹ� */
    WTTFVOICE_RSLT_FAIL             = 1,                                    /* ���ظ�MAC, ʧ�� */
    WTTFVOICE_RSLT_BUTT
};
typedef VOS_UINT16 WTTFVOICE_RSLT_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
enum WTTFVOICE_MSG_TYPE_ENUM
{
    ID_MAC_VOICE_MODE_SET_IND           = 0x9450,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_VOICE_MODE_SET_IND_STRU */
    ID_VOICE_MAC_MODE_SET_RSP           = 0x3050,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_MODE_SET_RSP_STRU */

    ID_MAC_VOICE_MODE_CHANGE_IND        = 0x9451,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU */
    ID_VOICE_MAC_MODE_CHANGE_RSP        = 0x3051,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_MODE_CHANGE_RSP_STRU */

    ID_VOICE_MAC_AMR_TYPE_REQ           = 0x3052,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_AMR_TYPE_REQ_STRU */

    ID_MAC_VOICE_AMR_DATA_IND           = 0x1101,           /* δʹ�� */ /*_H2ASN_Skip */ 
    ID_VOICE_MAC_AMR_DATA_REQ           = 0x3101,           /*_H2ASN_Skip */

    WTTFVOICE_MSG_TYPE_BUTT                                 /*_H2ASN_Skip */
} ;
typedef VOS_UINT16  WTTFVOICE_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 ʵ������  : WTTFVOICE_MAC_CODEC_MODE_SET_IND_STRU
 ��������  : WTTF MAC����Ϣ֪ͨCodec��֧�ֵ�CodecMode��
           ĿǰӦ�ó����ǵ�����ID_RRC_MAC_D_CONFIG_REQ �� ID_RRC_MAC_TFC_CONTROL_REQʱ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16           enMsgName;             /* ��ϢID */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;                /*������ʶ*/
    VOS_UINT16                               usSidEnable;           /*�Ƿ�ʹ��SID֡[0,1] 0:��ʹ��, 1:ʹ��*/
    WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16 enCodecType;           /*0: NB;   1:WB*/ /*_H2ASN_Replace VOS_UINT16 enCodecType;*/
    VOS_UINT16                               usCodecModeCnt;        /* AMR �������ʼ��ϰ������������ʸ�����enCodecType =NBʱ��Χ[1..8]��enCodecType =WBʱ��Χ[1..9]*/
    VOS_UINT16                               aenCodecModes[WTTFVOICE_AMR_CODEC_MODE_NUM]; /* AMR �������ʼ���, enCodecType =NBʱ�������ʷ�Χ[0..7] 0: 4.75kbps, 7: 12.2kbps��enCodecType =WBʱ�������ʷ�Χ[0..8] 0: 6.60kbps, 8: 23.85kbps */
} WTTFVOICE_MAC_VOICE_MODE_SET_IND_STRU;

/******************************************************************************************************
�ṹ��    : WTTFVOICE_MAC_MODE_SET_RSP_STRU
�ṹ˵��  : Codec����Ϣ��ӦMAC�� WTTFVOICE_MAC_CODEC_MODE_SET_IND_STRU ��Ϣ
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16           enMsgName;             /* ��ϢID */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;                /*������ʶ*/
    WTTFVOICE_RSLT_ENUM_UINT16               enResult;              /*���ؽ��[0,1] 0:= PS_SUCC , 1:= PS_FAIL */ /*_H2ASN_Replace VOS_UINT16 enResult;*/
    VOS_UINT16                               enCurrMode;            /*��ǰAMR �������ʣ�enCodecType=NBʱ��Χ[0..7] 0: 4.75kbps, 7: 12.2kbps��enCodecType=WBʱ���������ʷ�Χ[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    WTTFVOICE_AMR_TYPE_ENUM_UINT16           enAmrType;             /*enCodecType=NBʱ��AMR ��������[0,1] 0: AMR2, 1: AMR��enCodecType=WBʱ�˲��������� *//*_H2ASN_Replace VOS_UINT16 enAmrType;*/
    VOS_UINT16                               ausRsv[1];
} WTTFVOICE_MAC_MODE_SET_RSP_STRU;

/******************************************************************************************************
�ṹ��    : WTTFVOICE_MAC_CODEC_MODE_CHANGE_IND_STRU
�ṹ˵��  : WTTF MAC����Ϣ֪ͨCodec���Ա������ʸı�ΪĿ������
          ĿǰӦ�ó����ǵ�MAC��TFC״̬�仯���������ʸı�ʱ
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* ��ϢID */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;             /*������ʶ*/
    WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16    enCodecType;        /*0: NB; 1:WB*/ /*_H2ASN_Replace VOS_UINT16 enCodecType;*/
    VOS_UINT16                                  enCurrMode;         /*��ǰAMR �������ʣ�enCodecType=NBʱ��Χ[0..7] 0: 4.75kbps, 7: 12.2kbps��enCodecType=WBʱ��Χ[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    VOS_UINT16                                  enTargetMode;       /*Ŀ��AMR �������ʣ�enCodecType=NBʱ��Χ[0..7] 0: 4.75kbps, 7: 12.2kbps��enCodecType=WBʱ��Χ[0..8] 0: 6.60kbps, 8: 23.85kbps */
    VOS_UINT16                                  ausRsv[1];          /*����*/
} WTTFVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU;

/******************************************************************************************************
�ṹ��    : WTTFVOICE_MAC_MODE_CHANGE_RSP_STRU
�ṹ˵��  : Codec����Ϣ��ӦMAC�� WTTFVOICE_MAC_CODEC_MODE_CHANGE_IND_STRU ��Ϣ
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* ��ϢID */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;             /*������ʶ*/
    WTTFVOICE_RSLT_ENUM_UINT16                  enResult;           /*���ؽ��[0,1] 0:= PS_SUCC , 1:= PS_FAIL *//*_H2ASN_Replace VOS_UINT16 enResult;*/
    VOS_UINT16                                  enCurrMode;         /*��ǰAMR �������ʣ� enCodecType =NBʱ��Χ[0..7] 0: 4.75kbps, 7: 12.2kbps��enCodecType=WBʱ��Χ[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    VOS_UINT16                                  enTargetMode;       /*Ŀ��AMR �������ʣ� enCodecType =NBʱ��Χ[0..7] 0: 4.75kbps, 7: 12.2kbps��enCodecType=WBʱ��Χ[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    VOS_UINT16                                  ausRsv[1];
} WTTFVOICE_MAC_MODE_CHANGE_RSP_STRU;

/******************************************************************************************************
�ṹ��    : WTTFVOICE_MAC_AMR_TYPE_REQ_STRU
�ṹ˵��  : Codec����Ϣ֪ͨMAC��Ϣ��ǰ��AMR����
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* ��ϢID */ /*_H2ASN_Skip*/
    WTTFVOICE_AMR_TYPE_ENUM_UINT16              enAmrType;          /*AMR ��������[0,1,2] 0: AMR2, 1: AMR, 2: AMRWB */ /*_H2ASN_Replace VOS_UINT16 enAmrType;*/
    VOS_UINT16                                  ausRsv[2];
}WTTFVOICE_MAC_AMR_TYPE_REQ_STRU;

/******************************************************************************************************
�ṹ��    : WTTFVOICE_MAC_AMR_DATA_STRU
�ṹ˵��  : Codec��MAC AMR��Ϣ�����ݽṹ
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* ��ϢID */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usMuteFlag;         /* 1��ʾ��д�룬0��ʾ�Ѷ��� */
    WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16    enCodecType;        /* 0: NB;  1: WB */ /*_H2ASN_Replace VOS_UINT16 enCodecType;*/
    VOS_UINT16                                  enFrameType;        /* AMR����֡���� */
}WTTFVOICE_MAC_AMR_DATA_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */
/*****************************************************************************
  H2ASN���ɵ�ASN�ļ���Ҫ���
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    WTTFVOICE_MSG_TYPE_ENUM_UINT16      enMsgID;            /* _H2ASN_MsgChoice_Export WTTFVOICE_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          WTTFVOICE_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}VOICE_WTTF_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_WTTF_TRACE_MSG_DATA             stMsgData;
}VoiceWttfTrace_MSG;

#endif                                                     /* _H2ASN_Skip */

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

#endif /* end of WttfCodecInterface.h */



