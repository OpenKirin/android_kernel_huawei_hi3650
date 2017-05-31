/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : HifiDrvInterface.h
  �� �� ��   : ����
  ��    ��   : C00137131
  ��������   : 2012��8��16��
  ����޸�   :
  ��������   : Hifi��DRV֮��Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��8��16��
    ��    ��   : C00137131
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����

  notice:  ��Ҫ�����κ�����ͷ�ļ�!!!
           ��ͬʱ�޸�\device\hisi\hi6620\common\audio\hifidrvinterface.h�����������ļ�һ��!!!
*****************************************************************************/


#ifndef __HIFIDRVINTERFACE_H__
#define __HIFIDRVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
 ʵ������  : AP_HIFI_CCPU_RESET_REQ_STRU
 ��������  : AP֪ͨHIFI C�˸�λ����Ϣ�ṹ��
 ����˵��  ����Ҫ��vendor\hisi\modem\include\med\hifidrvinterface.h�ļ��е����ݽṹ���־���һ��
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDDE1*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
} AP_HIFI_CCPU_RESET_REQ_STRU;
/*****************************************************************************
 ʵ������  : HIFI_AP_CCPU_RESET_CNF_STRU
 ��������  : ��ӦID_AP_HIFI_CCPU_RESET_REQ�����hifi������ҵ��ʱ��ֹͣ����ҵ�񣬻ظ�AP
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;          /*0xDDE2*/ /*_H2ASN_Skip */
    unsigned short                          uhwResult;         /* 0��ʾsucc�� 1��ʾfail*/ /*_H2ASN_Replace VOS_UINT16 uhwResult;*/
} HIFI_AP_CCPU_RESET_CNF_STRU;

enum AUDIO_MSG_ENUM
{
    ID_AP_VOICEPP_START_REQ             = 0xDD42,                       /* ����VOICEPPͨ�� */
    ID_VOICEPP_MSG_START                = ID_AP_VOICEPP_START_REQ,
    ID_VOICEPP_AP_START_CNF             = 0xDD43,
    ID_AP_VOICEPP_STOP_REQ              = 0xDD44,                        /* ��ֹVOICEPPͨ�� */
    ID_VOICEPP_AP_STOP_CNF              = 0xDD45,
    ID_VOICEPP_MSG_END                  = 0xDD4A,
    /* AP��Ƶ������HIFI audio playerģ�齻����ϢID */
    ID_AP_AUDIO_PLAY_START_REQ          = 0xDD51,           /* AP����Hifi audio player request���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_AUDIO_AP_PLAY_START_CNF          = 0xDD52,           /* Hifi����audio player��ظ�AP confirm���� */ /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */
    ID_AP_AUDIO_PLAY_PAUSE_REQ          = 0xDD53,           /* APֹͣHifi audio player request���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_PAUSE_REQ_STRU */
    ID_AUDIO_AP_PLAY_PAUSE_CNF          = 0xDD54,           /* Hifiֹͣaudio player��ظ�AP confirm���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_PAUSE_CNF_STRU */
    ID_AUDIO_AP_PLAY_DONE_IND           = 0xDD56,           /* Hifi֪ͨAP audio playerһ�����ݲ�����ϻ��߲����ж�indication */ /* _H2ASN_MsgChoice AUDIO_PLAYER_DONE_IND_STRU */
    ID_AP_AUDIO_PLAY_UPDATE_BUF_CMD     = 0xDD57,           /* AP֪ͨHifi�����ݿ����command */ /* _H2ASN_MsgChoice AUDIO_PLAYER_UPDATE_BUF_CMD_STRU */
    ID_AP_AUDIO_PLAY_QUERY_TIME_REQ     = 0xDD59,           /* AP��ѯHifi audio player���Ž���request���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_TIME_REQ_STRU */
    ID_AP_AUDIO_PLAY_WAKEUPTHREAD_REQ   = 0xDD5A,           /* AP������������ */
    ID_AUDIO_AP_PLAY_QUERY_TIME_CNF     = 0xDD60,           /* Hifi�ظ�AP audio player���Ž���confirm���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_TIME_CNF_STRU */
    ID_AP_AUDIO_PLAY_QUERY_STATUS_REQ   = 0xDD61,           /* AP��ѯHifi audio player����״̬request���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_STATUS_REQ_STRU */
    ID_AUDIO_AP_PLAY_QUERY_STATUS_CNF   = 0xDD62,           /* Hifi�ظ�AP audio player����״̬confirm���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_STATUS_CNF_STRU */
    ID_AP_AUDIO_PLAY_SEEK_REQ           = 0xDD63,           /* AP seek Hifi audio player��ĳһλ��request���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SEEK_REQ_STRU */
    ID_AUDIO_AP_PLAY_SEEK_CNF           = 0xDD64,           /* Hifi�ظ�AP seek���confirm���� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SEEK_CNF_STRU */

    /* AP��Ƶ������audio loop���ؽ�����ϢID */
    ID_AP_AUDIO_LOOP_BEGIN_REQ          = 0xDD65,           /* AP����Hifi begin audio loop request���� */
    ID_AUDIO_AP_LOOP_BEGIN_CNF          = 0xDD66,           /* Hifi�ظ�AP begin audio loop���confirm���� */ /* _H2ASN_MsgChoice AUDIO_LOOP_CNF_STRU */
    ID_AP_AUDIO_LOOP_END_REQ            = 0xDD67,           /* AP����Hifi end audio loop request���� */ /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AUDIO_AP_LOOP_END_CNF            = 0xDD68,           /* Hifi�ظ�AP end audio loop���confirm���� */ /* _H2ASN_MsgChoice AUDIO_LOOP_CNF_STRU */
    ID_AP_AUDIO_PLAY_SET_VOL_CMD        = 0xDD70,           /* AP���ó��͹��Ĳ����������� */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SET_VOL_REQ_STRU */

    /* AP��Ƶ������¼��ģ�齻����Ϣ */
    ID_AP_AUDIO_RECORD_START_CMD        = 0xDD40,           /* _H2ASN_MsgChoice AUDIO_RECORD_START_STRU */
    ID_AP_AUDIO_RECORD_STOP_CMD         = 0xDD41,           /* _H2ASN_MsgChoice AUDIO_RECORD_STOP_STRU */

    /* AP��Ƶ������ENHANCEģ�齻����Ϣ */
    ID_AP_AUDIO_ENHANCE_START_REQ       = 0xDD81,           /* _H2ASN_MsgChoice AP_AUDIO_ENHANCE_START_REQ_STRU */
    ID_AUDIO_AP_ENHANCE_START_CNF       = 0xDD82,           /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */
    ID_AP_AUDIO_ENHANCE_STOP_REQ        = 0xDD83,           /* _H2ASN_MsgChoice AP_AUDIO_ENHANCE_STOP_REQ_STRU */
    ID_AUDIO_AP_ENHANCE_STOP_CNF        = 0xDD84,           /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */
    ID_AP_AUDIO_ENHANCE_SET_DEVICE_REQ  = 0xDD85,           /* _H2ASN_MsgChoice AP_AUDIO_ENHANCE_SET_DEVICE_REQ_STRU */
    ID_AUDIO_AP_ENHANCE_SET_DEVICE_CNF  = 0xDD86,           /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */

    ID_AUDIO_PCM_ENHANCE_SET_DEVICE_IND = 0xDD91,           /* _H2ASN_MsgChoice AUDIO_PCM_ENHANCE_SET_DEVICE_IND_STRU */
    ID_AP_AUDIO_MLIB_SET_PARA_IND       = 0xDD92,           /* _H2ASN_MsgChoice AP_AUDIO_MLIB_SET_PARA_IND_STRU */
    ID_AUDIO_PCM_ENHANCE_START_IND      = 0xDD93,           /* _H2ASN_MsgChoice AUDIO_PCM_ENHANCE_START_IND_STRU */
    ID_AUDIO_PCM_ENHANCE_STOP_IND       = 0xDD94,           /* _H2ASN_MsgChoice AUDIO_PCM_ENHANCE_STOP_IND_STRU */

	/* AP��Ƶ����������ģ�齻����Ϣ */
    ID_AP_AUDIO_CMD_SET_SOURCE_CMD      = 0xDD95,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_DEVICE_CMD      = 0xDD96,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_MODE_CMD        = 0xDD97,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_MLIB_SET_PARA_CMD   = 0xDD92,           /* _H2ASN_MsgChoice AP_AUDIO_MLIB_SET_PARA_IND_STRU */

    /* AP��Ƶ������HIFI��Ƶͨ��ģ�齻����ϢID */
    ID_AP_AUDIO_PCM_OPEN_REQ            = 0xDD25,           /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AP_AUDIO_PCM_CLOSE_REQ           = 0xDD26,           /* _H2ASN_MsgChoice AUDIO_PCM_CLOSE_REQ_STRU */
    ID_AP_AUDIO_PCM_HW_PARA_REQ         = 0xDD27,           /* _H2ASN_MsgChoice AUDIO_PCM_HW_PARAMS_REQ_STRU */
    ID_AP_AUDIO_PCM_HW_FREE_REQ         = 0xDD28,           /* ��δʹ�ã����� */
    ID_AP_AUDIO_PCM_PREPARE_REQ         = 0xDD29,           /* ��δʹ�ã����� */
    ID_AP_AUDIO_PCM_TRIGGER_REQ         = 0xDD2A,           /* _H2ASN_MsgChoice AUDIO_PCM_TRIGGER_REQ_STRU */
    ID_AP_AUDIO_PCM_POINTER_REQ         = 0xDD2B,           /* ��δʹ�ã����� */
    ID_AP_AUDIO_PCM_SET_BUF_CMD         = 0xDD2C,           /* _H2ASN_MsgChoice AUDIO_PCM_SET_BUF_CMD_STRU */
    ID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD  = 0xDD2D,           /* _H2ASN_MsgChoice AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU */

    /* HIFI��Ƶͨ��ģ���ڲ�������ϢID */
    ID_AUDIO_UPDATE_PLAY_BUFF_CMD       = 0xDD2E,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */
    ID_AUDIO_UPDATE_CAPTURE_BUFF_CMD    = 0xDD2F,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */
    ID_AUDIO_AP_PCM_TRIGGER_CNF         = 0xDDA0,           /* _H2ASN_MsgChoice AUDIO_PCM_TRIGGER_CNF_STRU */

    ID_AP_HIFI_TEST_CMD                 = 0xDD32,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */

    /* HIFI PCMģ����audio playerģ���ڲ�������ϢID */
    ID_AUDIO_UPDATE_PLAYER_BUFF_CMD     = 0xDD31,           /* audio PCM֪ͨplayer���²���buff���� */ /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */

    /* AP��HIFI������Ч�Ľ�����Ϣ */
    ID_AP_AUDIO_EFFECT_ENABLE_REQ       = 0xDD34,           /* ���� */  /* _H2ASN_MsgChoice AUDIO_EFFECT_ENABLE_REQ_STRU */
    ID_AP_AUDIO_EFFECT_PARA_REQ         = 0xDD33,           /* ���� */  /* _H2ASN_MsgChoice AUDIO_EFFECT_SET_PARAMS_REQ_STRU */

    /* AP��HIFI��DTS������Ϣ */
    ID_AP_AUDIO_SET_DTS_ENABLE_CMD       = 0xDD36,           /* AP֪ͨHifiʹ��DTS */  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU */
    /* ID_AUDIO_PLAYER_SET_DTS_ENABLE_IND  0xDD37               �ڲ���Ϣռ�� */
    ID_AP_AUDIO_SET_DTS_DEV_CMD          = 0xDD38,           /* AP֪ͨHifi DTS ����豸ģʽ */  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU */

    /* AP��HIFI�Ŀ������ö���hifi codec������Ϣ */
    ID_AP_AUDIO_SET_EXCODEC_BYPASS_CMD    = 0xDD3D,

    /* A��֪ͨHIFI C �˸�λ��ϢID */
    ID_AP_HIFI_CCPU_RESET_REQ           = 0xDDE1,           /* _H2ASN_MsgChoice AP_HIFI_CCPU_RESET_REQ_STRU */

    /* hifi�ظ�ID_AP_HIFI_CCPU_RESET_REQ */
    ID_HIFI_AP_CCPU_RESET_CNF           = 0xDDE2,           /* _H2ASN_MsgChoice HIFI_AP_CCPU_RESET_CNF_STRU */

    /* for 3mic: A��֪ͨHIFI 3Mic/4Mic ͨ·�ѽ�������������DMA */
    ID_AP_AUDIO_ROUTING_COMPLETE_REQ    = 0xDDC0,
    ID_AUDIO_AP_ROUTING_COMPLETE_CNF    = 0xDDC6,
    /* HIFI ֪ͨA��DMA������ɣ����Դ�Codec DPʱ�� */
    ID_AUDIO_AP_DMA_CONFIG_IND          = 0xDDC7,
    /* A��֪ͨHIFI ��Codec DPʱ���Ѵ� */
    ID_AP_AUDIO_DP_OPEN_IND             = 0xDDC8,
	ID_AP_ENABLE_MODEM_LOOP_REQ         = 0xDDCD,/* the audio hal notify HIFI to start/stop  MODEM LOOP*/
	ID_AP_HIFI_REQUEST_VOICE_PARA_REQ   = 0xDF00,          /*AP REQUEST VOICE MSG*/
	ID_HIFI_AP_REQUEST_VOICE_PARA_CNF   = 0xDF01,          /*HIFI REPLAY VOICE MSG*/
};

//for 3mic: struct for ioctl cmd to notify hifi 3Mic/4Mic routing complete
typedef struct {
    unsigned short    msgID;
    unsigned short    reserve;
}AUDIO_COMM_NOTIFY_REQ_STRU;

typedef struct {
    unsigned short    msgID;
    unsigned short    result;       //0��ʾ�ɹ���1��ʾʧ��
}AUDIO_COMM_NOTIFY_CNF_STRU;

typedef struct
{
    unsigned short    uhwMsgId;
    unsigned short    reserve;
} AUDIO_COMM_DMA_CONFIG_DONE_IND_STRU;

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

#endif /* end of hifidrvinterface.h */
