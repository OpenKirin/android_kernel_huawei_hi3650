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


#ifndef __OMCODECINTERFACE_H__
#define __OMCODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CodecInterface.h"
#include  "CodecNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*CODEC����OM��ȡ����ͬ����Ϣָʾ�ṹ��*/
#define MSG_CODEC_OM_HOOK_IND_STRU        MSG_OM_VOICE_HOOK_REQ_STRU

/* ��Ϣ������β����� */
#define VOICE_OM_TRANS_REPLICATED_BYTES (4)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ��ϢID���� */
enum CODEC_OM_MSG_ID_ENUM
{
    ID_VOICE_OM_SET_HOOK_CNF              = 0x491C,           /* ��ӦOM_VOICE_SET_HOOK_REQ*/         /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_VOICE_OM_SET_LOOP_CNF              = 0x491E,           /* ��ӦOM_VOICE_SET_LOOP_REQ*/         /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */

    ID_VOICE_OM_QUERY_STATUS_CNF          = 0x491F,           /* ��ӦOM_VOICE_QUERY_STATUS_REQ*/     /* _H2ASN_MsgChoice MSG_VOICE_OM_QUERY_RSP_STRU */
    ID_VOICE_OM_SET_NV_CNF                = 0x4918,           /* ��ӦOM_VOICE_SET_NV_REQ*/           /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_VOICE_OM_GET_NV_CNF                = 0x4919,           /* ��ӦOM_VOICE_GET_NV_REQ*/           /* _H2ASN_MsgChoice MSG_OM_MLIB_PARA_GET_STRU */
    ID_AUDIO_OM_SET_HOOK_CNF              = 0x491A,           /* ��ӦOM_AUDIO_SET_HOOK_REQ*/         /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_AUDIO_OM_QUERY_STATUS_CNF          = 0x491B,           /* ��ӦOM_AUDIO_QUERY_STATUS_REQ*/     /* _H2ASN_MsgChoice MSG_AUDIO_OM_QUERY_RSP_STRU */

    ID_VOICE_OM_SET_HOOK_IND              = 0x4922,           /* VOICE��OM�������ݹ�ȡ����ͬ�� */    /* _H2ASN_MsgChoice MSG_OM_VOICE_HOOK_REQ_STRU */
    ID_VOICE_OM_HOOK_IND                  = 0x4811,                                                     /* _H2ASN_MsgChoice MSG_VOICE_OM_HOOK_STRU */
    ID_AUDIO_OM_HOOK_IND                  = 0x4812,                                                     /* _H2ASN_MsgChoice MSG_AUDIO_OM_HOOK_STRU */

    ID_OM_VOICE_SET_HOOK_REQ              = 0x941C,           /* ��������򿪻��߹ر��������ݹ�ȡ*/     /* _H2ASN_MsgChoice MSG_OM_VOICE_HOOK_REQ_STRU */
    ID_OM_VOICE_SET_LOOP_REQ              = 0x941E,           /* �����������ز���ģʽ*/                 /* _H2ASN_MsgChoice MSG_OM_VOICE_LOOP_REQ_STRU */
    ID_OM_VOICE_QUERY_STATUS_REQ          = 0x941F,           /* ��ѯ�����������״̬*/                 /* _H2ASN_MsgChoice MSG_VOICE_OM_QUERY_RSP_STRU */
    ID_OM_VOICE_SET_NV_REQ                = 0x9418,           /* ����NV��*/                             /* _H2ASN_MsgChoice MSG_OM_MLIB_PARA_SET_STRU */
    ID_OM_VOICE_GET_NV_REQ                = 0x9419,           /* ��ȡNV�����ֵ*/                       /* _H2ASN_MsgChoice MSG_OM_MLIB_PARA_GET_STRU */

    ID_OM_AUDIO_SET_HOOK_REQ              = 0x941A,           /* �򿪻��߹ر�AUDIO���ݹ�ȡ */           /* _H2ASN_MsgChoice MSG_OM_AUDIO_HOOK_REQ_STRU */
    ID_OM_AUDIO_QUERY_STATUS_REQ          = 0x941B,           /* ��ѯ��Ƶ�������״̬*/                 /* _H2ASN_MsgChoice MSG_AUDIO_OM_QUERY_RSP_STRU */

    ID_AUDIO_OM_SET_NV_REQ                = 0x941C,           /* ����NV��*/                             /* _H2ASN_MsgChoice MSG_CODEC_CNF_STRU */
    ID_AUDIO_OM_GET_NV_REQ                = 0x941D,           /* ��ȡNV�����ֵ*/

    CODEC_OM_MSG_ID_BUTT
};
typedef VOS_UINT16 CODEC_OM_MSG_ID_ENUM_UINT16;

/* �¼��������� */
enum CODEC_ERRLOG_EVENT_MODE_ENUM
{
    CODEC_ERRLOG_EVENT_MODE_GSM                               = 0,
    CODEC_ERRLOG_EVENT_MODE_WCDMA,
    CODEC_ERRLOG_EVENT_MODE_ALL,
    CODEC_ERRLOG_EVENT_MODE_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENT_MODE_ENUM_UINT16;

/* ErrorLog ��¼���¼��� */
enum CODEC_ERRLOG_EVENTS_ENUM
{
    /* -- Ӳ����� -- */
    CODEC_ERRLOG_EVENTS_DMA_MIC_RESET                          = 0,               /* MIC DMA ���� */
    CODEC_ERRLOG_EVENTS_DMA_SPK_RESET,                                            /* SPK DMA ���� */

    /* -- ������� -- */

    /* - WCDMA - */

    CODEC_ERRLOG_EVENTS_WCDMA_DEC_INT_LOST,                                       /* WCDMA �������붪ʧ */
    CODEC_ERRLOG_EVENTS_WCDMA_BBP_DATA_NONE,                                      /* WCDMA BBP �ϱ�����Ϊ�� */
    CODEC_ERRLOG_EVENTS_WCDMA_BBP_DATA_BAD,                                       /* WCDMA BBP �ϱ�����Ϊ��֡ */
    CODEC_ERRLOG_EVENTS_WCDMA_DECIPHER_LOST,                                      /* WCDMA �������ж�ʧ */

    /* - GSM - */

    CODEC_ERRLOG_EVENTS_GSM_BFI_FRAME,                                            /* GSM �յ� BFI ֡ */

    /* - ALL - */
    CODEC_ERRLOG_EVENTS_CODEC_SID_FRAME,                                          /* SID ֡ */

    /* -- PC-Voice -- */

    CODEC_ERRLOG_EVENTS_PCVOICE_INTERPOLATE,                                      /* PC Voice ��֡ */
    CODEC_ERRLOG_EVENTS_PCVOICE_RINGBUF_FULL,                                     /* PC Voice Ring Buffer �� */

    CODEC_ERRLOG_EVENTS_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENTS_ENUM_UINT16;

/* ErrorLog �ϱ�����������Ϣ */
enum CODEC_ERRLOG_ENV_CODEC_ENUM
{
    /* -- WCDMA -- */

    /* AMR 475 - 122 8������ģʽ */

    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_475                      = 0,                /* WCDMA AMR ����ģʽ 4.75 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_515,                                         /* WCDMA AMR ����ģʽ 5.15 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_590,                                         /* WCDMA AMR ����ģʽ 5.90 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_670,                                         /* WCDMA AMR ����ģʽ 6.70 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_740,                                         /* WCDMA AMR ����ģʽ 7.40 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_795,                                         /* WCDMA AMR ����ģʽ 7.95 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_102,                                         /* WCDMA AMR ����ģʽ 10.2 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR_122,                                         /* WCDMA AMR ����ģʽ 12.2 kbits/s */

    /* AMR2  475 - 122 8������ģʽ */

    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_475,                                        /* WCDMA AMR2 ����ģʽ 4.75 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_515,                                        /* WCDMA AMR2 ����ģʽ 5.15 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_590,                                        /* WCDMA AMR2 ����ģʽ 5.90 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_670,                                        /* WCDMA AMR2 ����ģʽ 6.70 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_740,                                        /* WCDMA AMR2 ����ģʽ 7.40 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_795,                                        /* WCDMA AMR2 ����ģʽ 7.95 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_102,                                        /* WCDMA AMR2 ����ģʽ 10.2 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMR2_122,                                        /* WCDMA AMR2 ����ģʽ 12.2 kbits/s */

    /* -- GSM -- */

    /* AMR 475 - 122 8������ģʽ */

    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_475,                                           /* GSM AMR ����ģʽ 4.75 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_515,                                           /* GSM AMR ����ģʽ 5.15 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_590,                                           /* GSM AMR ����ģʽ 5.90 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_670,                                           /* GSM AMR ����ģʽ 6.70 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_740,                                           /* GSM AMR ����ģʽ 7.40 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_795,                                           /* GSM AMR ����ģʽ 7.95 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_102,                                           /* GSM AMR ����ģʽ 10.2 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMR_122,                                           /* GSM AMR-NB ����ģʽ 12.2 kbits/s */

    /* EFR */
    CODEC_ERRLOG_ENV_CODEC_GSM_EFR,                                               /* GSM EFR ������ */

    /* FR */
    CODEC_ERRLOG_ENV_CODEC_GSM_FR,                                                /* GSM FR ������ */

    /* HR */
    CODEC_ERRLOG_ENV_CODEC_GSM_HR,                                                /* GSM HR ������ */

    /* WCDMA AMR-WB 660 - 2385 9������ģʽ */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_660,                                          /* WCDMA AMR-WB ����ģʽ 6.60 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_885,                                          /* WCDMA AMR-WB ����ģʽ 8.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1265,                                         /* WCDMA AMR-WB ����ģʽ 12.65 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1425,                                         /* WCDMA AMR-WB ����ģʽ 14.25 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1585,                                         /* WCDMA AMR-WB ����ģʽ 15.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1825,                                         /* WCDMA AMR-WB ����ģʽ 18.25 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_1985,                                         /* WCDMA AMR-WB ����ģʽ 19.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_2305,                                         /* WCDMA AMR-WB ����ģʽ 23.05 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_WCDMA_AMRWB_2385,                                         /* WCDMA AMR-WB ����ģʽ 23.85 kbits/s */

    /* GSM AMR-WB 660 - 1265 3������ģʽ */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_660,                                          /* GSM AMR-WB ����ģʽ 6.60 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_885,                                          /* GSM AMR-WB ����ģʽ 8.85 kbits/s */
    CODEC_ERRLOG_ENV_CODEC_GSM_AMRWB_1265,                                         /* GSM AMR-WB ����ģʽ 12.65 kbits/s */

    CODEC_ERRLOG_ENV_CODEC_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_ENV_CODEC_ENUM_UINT16;

/* �¼���¼���� */
enum CODEC_ERRLOG_EVENT_TYPE_ENUM
{
    CODEC_ERRLOG_EVENT_TYPE_TOTAL                             = 0,                /* ��¼�¼�����,�������ڸ�ֵ�ϱ� */
    CODEC_ERRLOG_EVENT_TYPE_REPEAT,                                               /* ��¼�ظ��¼�,�������ڸ�ֵ�ϱ� */
    CODEC_ERRLOG_EVENT_TYPE_LOST,                                                 /* ��¼��ʧ�¼�,����С�ڸ�ֵ�ϱ� */
    CODEC_ERRLOG_EVENT_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 CODEC_ERRLOG_EVENT_TYPE_ENUM_UINT16;

/* ���ز������� */
enum CODEC_LOOP_ENUM
{
    CODEC_LOOP_DMA                        = 0,                                    /* DMA���� */
    CODEC_LOOP_BEFORE_CODEC,                                                      /* ����ǰ���� */
    CODEC_LOOP_CODEC,                                                             /* ����󻷻� */
    CODEC_LOOP_BUTT
};
typedef VOS_UINT16  CODEC_LOOP_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/* ����OM��ԭ����Ϣͷ */
typedef struct
{
    VOS_UINT16                                              usTransPrimId;      /* �̶���д0x5100 */
    VOS_UINT16                                              usReserved;

} MSG_CODEC_OM_ERRLOG_HEAD_STRU;

/*******************************************************************************
 �ṹ��    : MNTN_HEAD_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��¼�ṹͷ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulInfoLen;          /* _H2ASN_Skip */ /*������¼�ṹ�ĳ���,��λ:�ֽ�*/
    VOS_UINT32                                              ulErrNo;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulBoardtime;
    VOS_UINT32                                              ulSliceTime;
}MNTN_HEAD_INFO_STRU;

/* �ϱ����������ߵĸ��Ӷ� */
typedef struct
{
    VOS_UINT32                                              uwSN;               /* �ϱ�SN�� */
    VOS_UINT32                                              uwTimeStamp;        /* �ϱ�ʱ�� */
} VOICE_TOOL_EX_HEAD_STRU;

/* ���������ϱ��ṹ�� */
typedef struct
{

    VOS_UINT8                           ucFuncType;
    VOS_UINT8                           ucCpuId;
    VOS_UINT16                          usLength;
    VOICE_TOOL_EX_HEAD_STRU             stToolExHead;                                   /* ����ͷ */
    VOS_UINT8                           aucHookData[VOICE_OM_TRANS_REPLICATED_BYTES];   /* �ϱ��������� */
} VOICE_OM_TRANS_STRU;

/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/* ���ز��Խṹ�� */
typedef struct
{
    CODEC_SWITCH_ENUM_UINT16              enLoopEnable;                           /*�����Ƿ��*/
    CODEC_LOOP_ENUM_UINT16                enLoopType;                             /*��������*/
}CODEC_LOOP_STRU;

/*����������������� */
typedef struct
{
    CODEC_INOUT_ENUM_UINT16               usTxIn;                                 /*��������*/
    CODEC_INOUT_ENUM_UINT16               usTxOut;                                /*�������*/
    CODEC_INOUT_ENUM_UINT16               usRxIn;                                 /*��������*/
    CODEC_INOUT_ENUM_UINT16               usRxOut;                                /*�������*/
} CODEC_INOUT_STRU;

/*����������������� */
typedef struct
{
    VOS_UINT16                          uhwTxIn;                                /* �������� */
    VOS_UINT16                          uhwRxOut;                               /* ������� */
} CODEC_ERRLOG_INOUT_STRU;

/* ���л����ṹ */
typedef struct
{
    CODEC_ERRLOG_ENV_CODEC_ENUM_UINT16    enCodecEnv;                             /* ������������Ϣ */
    VOS_UINT16                          auhwRes[1];                             /* ������ */
    CODEC_ERRLOG_INOUT_STRU               stInout;                                /* ����������������� */
} CODEC_ERRLOG_ENV_STRU;

/* ErrorLog �ϱ��¼��ṹ */
typedef struct
{
    CODEC_ERRLOG_ENV_STRU                 stErrEnv;                               /* �ϱ��Ļ�����Ϣ */
    VOS_UINT16                          uhwErrCnt;                              /* �¼�������� */
    CODEC_ERRLOG_EVENT_TYPE_ENUM_UINT16   enErrType;                              /* �¼�������� */
} CODEC_OM_ERRLOG_EVENT_RPT_STRU;

/* ErrorLog�ϱ��ṹ�� */
typedef struct
{
    MSG_CODEC_OM_ERRLOG_HEAD_STRU         stOmHead;                               /* OM ErrorLog ��Ϣͷ */
    MNTN_HEAD_INFO_STRU                 stRecordHead;                           /* ErrorLog ��Ϣͷ */
    CODEC_OM_ERRLOG_EVENT_RPT_STRU        stEventRpt;                             /* ErrorLog �ϱ��¼���Ϣ */
} MSG_CODEC_ERRLOG_STRU;

/*****************************************************************************
 �ṹ��    : OMMED_RING_BUFFER_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ring buffer������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwProtectWord1;                         /*������ 0x55AA55AA*/
    VOS_UINT32                          uwProtectWord2;                         /*������ 0x5A5A5A5A*/
    VOS_UINT32                          uwWriteAddr;                            /*��һ��д���������Ե�ַ,��ָ��λΪByte*/
    VOS_UINT32                          uwReadAddr;                             /*��һ����ȡ��������Ե�ַ,��ָ��λΪByte*/
    VOS_UINT32                          uwBufSize;                              /*ring buffer�ĳ���,��λbyte */
    VOS_UINT32                          uwReserve;
    VOS_UINT32                          uwBufAddr;                              /*ring buffer�Ļ�ַ*/
    VOS_UINT32                          uwProtectWord3;                         /*������ 0x55AA55AA*/
    VOS_UINT32                          uwProtectWord4;                         /*������ 0x5A5A5A5A*/
}OMMED_RING_BUFFER_CONTROL_STRU;


/*****************************************************************************
  7 ��Ϣ����
*****************************************************************************/

/* ����ά��ָ����ƽṹ�� */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* ԭ������ */  /*_H2ASN_Skip*/
    VOS_UINT16                          uwReserve;                              /* ���� */
}MSG_OM_VOICE_REQ_STRU;

/* �����豸�����ṹ�� */
typedef struct
{
    VOS_UINT16                          usDeviceMode;                           /* �����豸��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ������5 PCVOICE */
    VOS_UINT16                          usNetMode;                              /* ����ģʽ��0 GSM�� 1 WCDMA��   3 TD */
    VOS_UINT16                          usSampleRate;                           /* ������  : 0 8k;   1 16k */
    VOS_UINT16                          usIndex;                                /* �����Ϣ�� ��ID���� */
    VOS_INT16                           ashwNv[CODEC_PP_NV_ARRAY_ID_LEN];       /* ����ID��NV�������� */
}OM_VOICE_NV_STRU;

/* �������ýṹ�� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ԭ������ */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VOS_UINT32                          uwPathID;                               /* ·��ID */
    VOS_UINT32                          uwModuleID;                             /* ģ��ID */
    VOS_UINT32                          uwSize;                                 /* ���ݴ�С */
    VOS_UINT8                           aucData[4];                             /* ������ʼ */

}MSG_OM_MLIB_PARA_SET_STRU;

/* ������ȡ�ṹ�� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ԭ������ */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VOS_UINT32                          uwPathID;                               /* ·��ID */
    VOS_UINT32                          uwModuleID;                             /* ģ��ID */
    VOS_UINT32                          uwSize;                                 /* ���ݴ�С */
    VOS_UINT8                           aucData[4];                             /* ������ʼ */

}MSG_OM_MLIB_PARA_GET_STRU;

/* �������ݹ�ȡ����ԭ��ṹ�� */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /*ԭ��ID*/
    VOS_UINT16                          usReserve;
    CODEC_SWITCH_ENUM_UINT16            enHookEnable;                           /*��ȡ�����Ƿ��*/
    VOS_UINT16                          usHookTarget;                           /*��ȡ����Ŀ��*/
}MSG_OM_VOICE_HOOK_REQ_STRU;

/* ��Ƶ���ݹ�ȡ����ԭ��ṹ�� */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /*ԭ��ID*/
    VOS_UINT16                          usReserve;
    CODEC_SWITCH_ENUM_UINT16            enHookEnable;                           /*��ȡ�����Ƿ��*/
    VOS_UINT16                          usHookTarget;                           /*��ȡ����Ŀ��*/
}MSG_OM_AUDIO_HOOK_REQ_STRU;

/* �������ݹ�ȡ�ϱ�ԭʼ�ṹ�� */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* ԭ��ID */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulFrameTick;                            /* ��ǰ����֡֡��     */
    VOS_UINT32                          ulTimeStamp;                            /* ��ǰ����֡ʱ��     */
    VOS_UINT16                          usHookTarget;                           /* ��ȡ����Ŀ��       */
    VOS_UINT16                          usHookLength;                           /* ��ȡ���ݳ���(8bit) */
}MSG_VOICE_OM_HOOK_STRU;

/* ��Ƶ���ݹ�ȡ�ϱ�ԭʼ�ṹ�� */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* ԭ��ID */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulTimeStamp;                            /* ��ǰ����֡֡��     */
    VOS_UINT16                          usHookTarget;                           /* ��ȡ����Ŀ��       */
    VOS_UINT16                          usHookLength;                           /* ��ȡ���ݳ���(8bit) */
}MSG_AUDIO_OM_HOOK_STRU;

/* �������ز�������ԭ��ṹ�� */
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /*ԭ��ID*/ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved;
    CODEC_LOOP_STRU                     stLoop;                                 /*�������*/
}MSG_OM_VOICE_LOOP_REQ_STRU;

/* VOICE_OM_QUERY_STATUS_RSP ԭʼ�ṹ */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* ԭ��ID */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved1;                            /* ���� */
    CODEC_NET_MODE_ENUM_UINT16          enNetMode;                              /* ͨѶ������ʽ��0 G��1 W */
    CODEC_ENUM_UINT16                   enCodecType;                            /* ���������0 AMR��1 EFR��2 FR��3 HR */
    CODEC_SWITCH_ENUM_UINT16            enDtxMode;                              /* DTXʹ�ܣ�0 ��ֹ��1 ʹ�� */
    VOS_UINT16                          enAmrMode;                              /* ����ģʽ֮һ */
    CODEC_INOUT_STRU                    stInout;                                /* ��������ṹ�� */
    VOS_UINT16                          usState;                                /* �������״̬ */
    VOS_UINT16                          usReserve2;                             /* ���� */
}MSG_VOICE_OM_QUERY_RSP_STRU;

/* AUDIO_OM_QUERY_STATUS_RSP ԭʼ�ṹ */
typedef struct
{
    VOS_UINT16                          usMsgId;                                /* ԭ��ID */  /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved1;                            /* ���� */
    AUDIO_PCM_STATUS_ENUM_UINT16        enPlayBackStatus;                       /* ������Ƶͨ·״̬ */
    VOS_UINT16                          usReserved2;                            /* ���� */
    VOS_UINT32                          uwPlayBackSampleRate;                   /* ���ŵ�ǰͨ�������� */
    VOS_UINT32                          uwPlayBackChannelNum;                   /* ����ͨ���������� */
    AUDIO_PCM_STATUS_ENUM_UINT16        enCaptureStatus;                        /* ¼����Ƶͨ·״̬ */
    AUDIO_CAPTURE_MODE_ENUM_UINT16      enCaptureMode;                          /* ¼��ģʽ������¼��ͨ����Ч */
    VOS_UINT32                          uwCaptureSampleRate;                    /* ¼����ǰͨ�������� */
    VOS_UINT32                          uwCaptureChannelNum;                    /* ¼��ͨ���������� */
    VOS_UINT32                          uwEnhanceModule;                        /* ��Ƶ��ǿ��ǰʹ�õ�ģ�� */
}MSG_AUDIO_OM_QUERY_RSP_STRU;

/* ��Ƶ�豸�����ṹ�� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ԭ������ */  /*_H2ASN_Skip*/
    VOS_UINT16                          usDeviceMode;                           /* �����豸��0 ���᣻1 ���� */
    VOS_UINT32                          usSampleRate;                           /* ������   */
    VOS_UINT16                          usIndex;                                /* �����Ϣ�� ��ID���� */
    VOS_INT16                           ashwNv[AUDIO_PP_NV_ARRAY_ID_LEN];       /* ����ID��NV�������� */
    VOS_INT16                           shwReserved;
}MSG_OM_AUDIO_NV_REQ_STRU;

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
    CODEC_OM_MSG_ID_ENUM_UINT16           enMsgID;            /* _H2ASN_MsgChoice_Export CODEC_OM_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CODEC_OM_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_OM_TRANS_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOICE_OM_TRANS_MSG_DATA                     stMsgData;
}VoiceOmTrans_MSG;

#endif                                                     /* _H2ASN_Skip */

/*****************************************************************************
  10 ��������
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of VcCodecInterface.h */
