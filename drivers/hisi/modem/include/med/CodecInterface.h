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

#ifndef __CODECINTERFACE_H__
#define __CODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "VcCodecInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define HIFI_TASK_NUM                   (4)                                     /* HiFi����ϵͳ֧��������� */
#define HIFI_INTR_NUM                   (32)                                    /* HiFiϵͳ�жϸ���         */
#define VOICE_MAX_HOOK_LEN              (640*3)                                 /* �������ȡ���ݳ��ȣ���λ2 Byte */
#define AUDIO_MAX_HOOK_LEN              (3840)                                  /* ��Ƶ���ȡ���ݳ��ȣ���λ2 Byte���ݶ� */
#define WPHY_VOICE_AMR_SUBFRAME_NUM     (3)                                     /* W�������CODEC����������������֡���� */
#define WPHY_VOICE_AMR_FRAME_LEN        (16)                                    /* W�������CODEC�������������ݳ���,��λ32Bit,�����г���һ�� */

/*WPHY_CODEC_DATA_STRU�ṹ��������
uhwQualityIdx   --AMR֡������־, 0��ʾ
auhwLen         --���δ��A/B/C�����ĳ��ȣ���BITΪ��λ
auwData         --���δ��A/B/C�������ݣ�ABC�����ֱ�32BIT����*/
#define WPHY_VOICE_DATA_STRU                                                      \
    CODEC_AMR_FQI_QUALITY_ENUM_UINT16       enQualityIdx;                         \
    VOS_UINT16                              auhwLen[WPHY_VOICE_AMR_SUBFRAME_NUM]; \
    VOS_UINT32                              auwData[WPHY_VOICE_AMR_FRAME_LEN];

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum VOICE_VOICE_MSG_ID_ENUM
{
    ID_VOICE_VOICE_TX_PP_REQ          = 0xDD30,           /* �������ʹ��, ���ڴ�������PP���� */
    ID_VOICE_VOICE_RX_PP_REQ          = 0xDD31,           /* �������ʹ��, ���ڴ�������PP���� */
    VOICE_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 VOICE_VOICE_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : UCOM_RET_ENUM
 ö��˵��  : ��Ϣ������ִ�н��
*****************************************************************************/
enum UCOM_RET_ENUM
{
    UCOM_RET_SUCC                       = VOS_OK,                               /*�ɹ�*/
    UCOM_RET_FAIL                       = VOS_ERR,                              /*ʧ��*/
    UCOM_RET_NUL_PTR                    = 2,                                    /*��ָ��*/
    UCOM_RET_ERR_PARA                   = 3,                                    /*��������*/
    UCOM_RET_ERR_STATE                  = 4,                                    /*״̬����*/
    UCOM_RET_ERR_MSG                    = 5,                                    /*δ֪��Ϣ*/
    UCOM_RET_ERR_NOMEM                  = 6,                                    /*�ռ䲻��*/
    UCOM_RET_FUNC_DISABLE               = 7,                                    /*���ܲ�֧��*/
    UCOM_RET_SEND_FAIL                  = 8,                                    /*��Ϣ����ʧ��*/
    UCOM_RET_MSG_DELAY                  = 9,                                    /*��Ϣ��ʱ��ʱ*/
    UCOM_RET_BUTT
};
typedef VOS_UINT16 UCOM_RET_ENUM_UINT16;

/* ������ö�� */
enum CODEC_SWITCH_ENUM
{
    CODEC_SWITCH_OFF                      = 0,
    CODEC_SWITCH_ON,
    CODEC_SWITCH_BUTT
};
typedef VOS_UINT16  CODEC_SWITCH_ENUM_UINT16;

/* �������ö�� */
enum CODEC_INOUT_ENUM
{
    CODEC_INOUT_DEFAULT                   = 0,                                    /* default:TxIn=SIO;TxOut=UL;RxIn=DL;RxOut=SIO */
    CODEC_INOUT_SOUND,                                                            /* SOUND�ϳ�, reserve */
    CODEC_INOUT_DATA,                                                             /* ���ݽӿ�, reserve  */
    CODEC_INOUT_BUTT
};
typedef VOS_UINT16  CODEC_INOUT_ENUM_UINT16;

/* ������ʽö�� */
enum CODEC_NET_MODE_ENUM
{
	CODEC_NET_MODE_G			= VCVOICE_NET_MODE_GSM,               /* G net mode */
	CODEC_NET_MODE_W			= VCVOICE_NET_MODE_WCDMA,             /* W net mode */
	CODEC_NET_MODE_TD			= VCVOICE_NET_MODE_TDSCDMA,           /* TD net mode*/
	CODEC_NET_MODE_L			= VCVOICE_NET_MODE_IMS_EUTRAN,        /* Lte net mode */
	CODEC_NET_MODE_C			= VCVOICE_NET_MODE_CDMA,              /* CDMA net mode */
	CODEC_NET_MODE_WIFI			= VCVOICE_NET_MODE_WIFI,              /* WIFI net mode */
	CODEC_NET_MODE_BUTT			= VCVOICE_NET_MODE_BUTT
};
typedef VOS_UINT16  CODEC_NET_MODE_ENUM_UINT16;

/* ����������ö�� */
enum CODEC_ENUM
{
    CODEC_AMR                       = VCVOICE_TYPE_AMR,
    CODEC_EFR                       = VCVOICE_TYPE_EFR,
    CODEC_FR                        = VCVOICE_TYPE_FR,
    CODEC_HR                        = VCVOICE_TYPE_HR,
    CODEC_AMR2                      = VCVOICE_TYPE_AMR2,
    CODEC_AMRWB                     = VCVOICE_TYPE_AMRWB,
    CODEC_G711                      = VCVOICE_TYPE_G711,
    CODEC_EVRC                      = VCVOICE_TYPE_EVRC,
    CODEC_EVRCB                     = VCVOICE_TYPE_EVRCB,
    CODEC_BUTT                      = VCVOICE_TYPE_BUTT
};
typedef VOS_UINT16  CODEC_ENUM_UINT16;

/* AMR����ģʽ */
enum CODEC_AMR_RATE_MODE_ENUM
{
    CODEC_AMR_RATE_MODE_475K              = 0,
    CODEC_AMR_RATE_MODE_515K,
    CODEC_AMR_RATE_MODE_590K,
    CODEC_AMR_RATE_MODE_670K,
    CODEC_AMR_RATE_MODE_740K,
    CODEC_AMR_RATE_MODE_795K,
    CODEC_AMR_RATE_MODE_102K,
    CODEC_AMR_RATE_MODE_122K,
    CODEC_AMR_RATE_MODE_BUTT
};
typedef VOS_UINT16  CODEC_AMR_RATE_MODE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_DTX_ENUM
 ��������  : DTXȡֵ����
*****************************************************************************/
enum CODEC_DTX_ENUM
{
    CODEC_DTX_DISABLE               = 0,                                    /* DTX��ʹ�� */
    CODEC_DTX_ENABLE                = 1,                                    /* DTXʹ��   */
    CODEC_DTX_BUTT
};
typedef VOS_UINT16 CODEC_DTX_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_DTXSTATE_ENUM
 ��������  : DTX_STATEȡֵ����
*****************************************************************************/
enum CODEC_DTX_STATE_ENUM
{
    CODEC_DTX_NO                    = 0,                                    /* speech̬ */
    CODEC_DTX_YES                   = 1,                                    /* dtx̬ */
    CODEC_DTX_STATE_BUTT
};
typedef VOS_UINT16 CODEC_DTX_STATE_ENUM_UINT16;


/*****************************************************************************
 ʵ������  : CODEC_VAD_ENUM
 ��������  : EFR,HR,FR VAD flagȡֵ����, �μ�3GPP TS 46.081
*****************************************************************************/
enum CODEC_VAD_ENUM
{
    CODEC_VAD_SILENCE               = 0,                                    /* ���Ϊ���� */
    CODEC_VAD_SPEECH                = 1,                                    /* ���Ϊ���� */
    CODEC_VAD_BUTT
};
typedef VOS_UINT16 CODEC_VAD_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_SP_ENUM
 ��������  : EFR,HR,FR SP flagȡֵ����, �μ�3GPP TS 46.081
*****************************************************************************/
enum CODEC_SP_ENUM
{
    CODEC_SP_SID                    = 0,                                    /* ���SID֡    */
    CODEC_SP_SPEECH                 = 1,                                    /* ���SPEECH֡ */
    CODEC_SP_BUTT
};
typedef VOS_UINT16 CODEC_SP_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_BFI_ENUM
 ��������  : EFR,HR,FR ��֡��־bfi,ufiȡֵ����, �μ�3GPP TS 46.081, 46.041
*****************************************************************************/
enum CODEC_BFI_ENUM
{
    CODEC_BFI_NO                    = 0,                                    /* ��֡ */
    CODEC_BFI_YES                   = 1,                                    /* ��֡ */
    CODEC_BFI_BUTT
};
typedef VOS_UINT16 CODEC_BFI_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_SID_ENUM
 ��������  : EFR,HR,FR SID flagȡֵ����, �μ�3GPP TS 46.041
*****************************************************************************/
enum CODEC_SID_ENUM
{
    CODEC_SID_SPEECH                = 0,                                    /* ����֡        */
    CODEC_SID_ACCEPT                = 1,                                    /* �ɽ��ܵ�SID֡ */
    CODEC_SID_VALID                 = 2,                                    /* �Ϸ���SID֡   */
    CODEC_SID_BUTT
};
typedef VOS_UINT16 CODEC_SID_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_TAF_ENUM
 ��������  : EFR,HR,FR TAFȡֵ����, �μ�3GPP TS 46.081, 46.041
*****************************************************************************/
enum CODEC_TAF_ENUM
{
    CODEC_TAF_NONE                  = 0,                                    /* ��ʱ����� */
    CODEC_TAF_ALIGNED               = 1,                                    /* ʱ�����, Ӧ�ý��յ�SID */
    CODEC_TAF_BUTT
};
typedef VOS_UINT16 CODEC_TAF_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_HR_UFI_ENUM
 ��������  : HR UFIȡֵ����, 0-�ŵ��ȶ�, 1-�ŵ�����
*****************************************************************************/
enum CODEC_HR_UFI_ENUM
{
    CODEC_HR_UFI_GOOD               = 0,                                    /* �ŵ��ȶ� */
    CODEC_HR_UFI_BAD                = 1,                                    /* �ŵ����� */
    CODEC_HR_UFI_BUTT
};
typedef VOS_UINT16 CODEC_HR_UFI_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_FORMAT_ENUM
 ��������  : AMR������ʽ����, �μ�3GPP TS 26.101
*****************************************************************************/
enum CODEC_AMR_FORMAT_ENUM
{
    CODEC_AMR_FORMAT_IF1              = 0,                                      /* IF1������ʽ,UMTS��ʹ�� */
    CODEC_AMR_FORMAT_BITS             = 1,                                      /* GSM-AMR������ʽ */
    CODEC_AMR_FORMAT_IMS              = 2,                                      /* IMS������ʽ */
    CODEC_AMR_FORMAT_BUTT
};
typedef VOS_UINT16 CODEC_AMR_FORMAT_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_FRM_TYPE_ENUM
 ��������  : AMR IF֡����, �μ�3GPP TS 26.101 Table 1a
*****************************************************************************/
enum CODEC_AMR_FRM_TYPE_ENUM
{
    CODEC_AMR_FRM_TYPE_475K         = 0,
    CODEC_AMR_FRM_TYPE_515K         = 1,
    CODEC_AMR_FRM_TYPE_590K         = 2,
    CODEC_AMR_FRM_TYPE_670K         = 3,
    CODEC_AMR_FRM_TYPE_740K         = 4,
    CODEC_AMR_FRM_TYPE_795K         = 5,
    CODEC_AMR_FRM_TYPE_102K         = 6,
    CODEC_AMR_FRM_TYPE_122K         = 7,
    CODEC_AMR_FRM_TYPE_AMR_SID      = 8,
    CODEC_AMR_FRM_TYPE_GSM_EFR_SID  = 9,
    CODEC_AMR_FRM_TYPE_TDMA_EFR_SID = 10,
    CODEC_AMR_FRM_TYPE_PDC_EFR_SID  = 11,
    CODEC_AMR_FRM_TYPE_NO_DATA      = 15,
    CODEC_AMR_FRM_TYPE_BUTT
};
typedef VOS_UINT16 CODEC_AMR_FRM_TYPE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_TYPE_RX_ENUM
 ��������  : AMR����֡���Ͷ���, �μ�3GPP TS 26.093��26.073 frame.h
*****************************************************************************/
enum CODEC_AMR_TYPE_RX_ENUM
{
    CODEC_AMR_TYPE_RX_SPEECH_GOOD   = 0,
    CODEC_AMR_TYPE_RX_SPEECH_DEGRADED,
    CODEC_AMR_TYPE_RX_ONSET,
    CODEC_AMR_TYPE_RX_SPEECH_BAD,
    CODEC_AMR_TYPE_RX_SID_FIRST,
    CODEC_AMR_TYPE_RX_SID_UPDATE,
    CODEC_AMR_TYPE_RX_SID_BAD,
    CODEC_AMR_TYPE_RX_NO_DATA,
    CODEC_AMR_TYPE_RX_BUTT
};
typedef VOS_UINT16 CODEC_AMR_TYPE_RX_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_TYPE_TX_ENUM
 ��������  : AMR����֡���Ͷ���, �μ�3GPP TS 26.093��26.073 frame.h
*****************************************************************************/
enum CODEC_AMR_TYPE_TX_ENUM
{
    CODEC_AMR_TYPE_TX_SPEECH_GOOD   = 0,
    CODEC_AMR_TYPE_TX_SID_FIRST,
    CODEC_AMR_TYPE_TX_SID_UPDATE,
    CODEC_AMR_TYPE_TX_NO_DATA,
    CODEC_AMR_TYPE_TX_SPEECH_DEGRADED,
    CODEC_AMR_TYPE_TX_SPEECH_BAD,
    CODEC_AMR_TYPE_TX_SID_BAD,
    CODEC_AMR_TYPE_TX_ONSET,
    CODEC_AMR_TYPE_TX_BUTT
};
typedef VOS_UINT16 CODEC_AMR_TYPE_TX_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_NSYNC_ENUM
 ��������  : AMR NSYNC��������, �ò���DTXʹ��ʱʹ��, �μ�3GPP TS 26.093 A5.1
*****************************************************************************/
enum CODEC_AMR_NSYNC_ENUM
{
    CODEC_AMR_NSYNC_INIT            = 0,                                    /* ��ʼ��ֵ */
    CODEC_AMR_NSYNC_HANDOVER        = 12,                                   /* ������С���л�ʱTx RSS���͸�Tx DTX handler */
    CODEC_AMR_NSYNC_BUTT
};
typedef VOS_UINT16 CODEC_AMR_NSYNC_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_FQI_QUALITY_ENUM
 ��������  : ��W�����Լ����AMR֡���͵ĺû�
*****************************************************************************/
enum CODEC_AMR_FQI_QUALITY_ENUM
{
    CODEC_AMR_FQI_QUALITY_BAD   = 0,
    CODEC_AMR_FQI_QUALITY_GOOD,
    CODEC_AMR_FQI_QUALITY_BUTT
};
typedef VOS_UINT16 CODEC_AMR_FQI_QUALITY_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMR_STI_SID_ENUM
 ��������  : SID��־��0��ʾSID_FIRST��1��ʾSID_UPDATE
*****************************************************************************/
enum CODEC_AMR_STI_SID_ENUM
{
    CODEC_AMR_STI_SID_FIRST   = 0,
    CODEC_AMR_STI_SID_UPDATE,
    CODEC_AMR_STI_SID_BUTT
};
typedef VOS_UINT16 CODEC_AMR_STI_SID_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMRWB_RATE_MODE_ENUM_UINT16
 ��������  : AMR-WB����ģʽ
*****************************************************************************/
enum CODEC_AMRWB_RATE_MODE_ENUM
{
    CODEC_AMRWB_RATE_MODE_660K              = 0,
    CODEC_AMRWB_RATE_MODE_885K,
    CODEC_AMRWB_RATE_MODE_1265K,
    CODEC_AMRWB_RATE_MODE_1425K,
    CODEC_AMRWB_RATE_MODE_1585K,
    CODEC_AMRWB_RATE_MODE_1825K,
    CODEC_AMRWB_RATE_MODE_1985K,
    CODEC_AMRWB_RATE_MODE_2305K,
    CODEC_AMRWB_RATE_MODE_2385K,
    CODEC_AMRWB_RATE_MODE_BUTT
};
typedef VOS_UINT16  CODEC_AMRWB_RATE_MODE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMRWB_FRM_TYPE_ENUM
 ��������  : AMR-WB IF֡����, �μ�3GPP TS 26.201 Table 1a
*****************************************************************************/
enum CODEC_AMRWB_FRM_TYPE_ENUM
{
    CODEC_AMRWB_FRM_TYPE_660K         = 0,
    CODEC_AMRWB_FRM_TYPE_885K         = 1,
    CODEC_AMRWB_FRM_TYPE_1265K        = 2,
    CODEC_AMRWB_FRM_TYPE_1425K        = 3,
    CODEC_AMRWB_FRM_TYPE_1585K        = 4,
    CODEC_AMRWB_FRM_TYPE_1825K        = 5,
    CODEC_AMRWB_FRM_TYPE_1985K        = 6,
    CODEC_AMRWB_FRM_TYPE_2305K        = 7,
    CODEC_AMRWB_FRM_TYPE_2385K        = 8,
    CODEC_AMRWB_FRM_TYPE_SID          = 9,
    CODEC_AMRWB_FRM_TYPE_NO_DATA      = 15,
    CODEC_AMRWB_FRM_TYPE_BUTT
};
typedef VOS_UINT16 CODEC_AMRWB_FRM_TYPE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMRWB_TYPE_RX_ENUM
 ��������  : AMR-WB����֡���Ͷ���, �μ�3GPP TS 26.193��26.173 frame.h
*****************************************************************************/
enum CODEC_AMRWB_TYPE_RX_ENUM
{
    CODEC_AMRWB_TYPE_RX_SPEECH_GOOD   = 0,
    CODEC_AMRWB_TYPE_RX_SPEECH_DEGRADED,
    CODEC_AMRWB_TYPE_RX_ONSET,
    CODEC_AMRWB_TYPE_RX_SPEECH_BAD,
    CODEC_AMRWB_TYPE_RX_SID_FIRST,
    CODEC_AMRWB_TYPE_RX_SID_UPDATE,
    CODEC_AMRWB_TYPE_RX_SID_BAD,
    CODEC_AMRWB_TYPE_RX_NO_DATA,
    CODEC_AMRWB_TYPE_RX_SPEECH_LOST,
    CODEC_AMRWB_TYPE_RX_BUTT
};
typedef VOS_UINT16 CODEC_AMRWB_TYPE_RX_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : CODEC_AMRWB_TYPE_TX_ENUM
 ��������  : AMR-WB����֡���Ͷ���, �μ�3GPP TS 26.193��26.173 frame.h
*****************************************************************************/
enum CODEC_AMRWB_TYPE_TX_ENUM
{
    CODEC_AMRWB_TYPE_TX_SPEECH_GOOD   = 0,
    CODEC_AMRWB_TYPE_TX_SID_FIRST,
    CODEC_AMRWB_TYPE_TX_SID_UPDATE,
    CODEC_AMRWB_TYPE_TX_NO_DATA,
    CODEC_AMRWB_TYPE_TX_SPEECH_DEGRADED,
    CODEC_AMRWB_TYPE_TX_SPEECH_BAD,
    CODEC_AMRWB_TYPE_TX_SID_BAD,
    CODEC_AMRWB_TYPE_TX_ONSET,
    CODEC_AMRWB_TYPE_TX_SPEECH_LOST,
    CODEC_AMRWB_TYPE_TX_BUTT
};
typedef VOS_UINT16 CODEC_AMRWB_TYPE_TX_ENUM_UINT16;


/*****************************************************************************
 ʵ������  : MED_CODEC_FRAME_FACCH_ENUM
 ��������  : �����Ƿ�͵֡��־
*****************************************************************************/
enum CODEC_FRAME_FACCH_ENUM
{
    CODEC_FRAME_FACCH_NO              = 0,
    CODEC_FRAME_FACCH_YES,
    CODEC_FRAME_FACCH_BUTT
};
typedef VOS_UINT16 CODEC_FRAME_FACCH_ENUM_UINT16;

/*��Ƶ¼��ģʽ*/
enum AUDIO_CAPTURE_MODE_ENUM
{
    AUDIO_CAPTURE_MODE_DISABLE = 0,                              /*¼����ֹ*/
    AUDIO_CAPTURE_MODE_CALL    = 1,                              /*��ͨCSͨ��¼��*/
    AUDIO_CAPTURE_MODE_CAMCORD = 2,                              /*ͨ��ʱ����*/
    AUDIO_CAPTURE_MODE_EXT_CALL= 3,                              /*������Modemͨ��¼��*/
    AUDIO_CAPTURE_MODE_AUDIO   = 4,                              /*��ͨ��Ƶ¼��*/
    AUDIO_CAPTURE_MODE_FM      = 5,                              /*��ͨFM¼��*/
    AUDIO_CAPTURE_MODE_VQM     = 6,                              /*���������������*/
    AUDIO_CAPTURE_MODE_BUT
};
typedef VOS_UINT16  AUDIO_CAPTURE_MODE_ENUM_UINT16;

/* ��Ƶ����ͨ·״̬ö�� */
enum AUDIO_PCM_STATUS_ENUM
{
    AUDIO_PCM_STATUS_DEACTIVE= 0,
    AUDIO_PCM_STATUS_ACTIVE,
    AUDIO_PCM_STATUS_BUT
};
typedef VOS_UINT16  AUDIO_PCM_STATUS_ENUM_UINT16;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : MSG_CODEC_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ִ��responseͨ�ýṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    UCOM_RET_ENUM_UINT16                enExeRslt;                              /* ִ�н�� */
    VOS_UINT16                          usReserve2;
}MSG_CODEC_CNF_STRU;

/*****************************************************************************
 ʵ������  : VOICE_WPHY_AMR_SERIAL_STRU
 ��������  : ��W�����֮��Լ����AMR������������ʽ�ṹ��
*****************************************************************************/
typedef struct
{
    WPHY_VOICE_DATA_STRU
}VOICE_WPHY_AMR_SERIAL_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


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

#endif /* end of CodecInterface.h */
