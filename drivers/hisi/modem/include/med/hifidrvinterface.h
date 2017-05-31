


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
/* AP��Kernel��Ƶ�����������ݸ�hifiʱ��buff������bufAddrΪ���ߵ�ַ��bufSize��dataSize��λbyte */
#if 0                                                                           /*_H2ASN_Skip*/
#define DRV_SEND_DATA_STRU                                                      \
    VOS_UINT32                              uwBufAddr;                          \
    VOS_UINT32                              uwBufSize;                          \
    VOS_UINT32                              uwDataSize;
#else
#define DRV_SEND_DATA_STRU                                                      \
    unsigned int                           uwBufAddr;                          \
    unsigned int                           uwBufSize;                          \
    unsigned int                           uwDataSize;
#endif

#define MSG_HEADER  VOS_UINT32 uwSenderCpuId;  \
                    VOS_UINT32 uwSenderPid;    \
                    VOS_UINT32 uwReceiverCpuId;\
                    VOS_UINT32 uwReceiverPid;  \
                    VOS_UINT32 uwLength;

#define AUDIO_HIFIMISC_MSG_SN_DEFAULT       (0xffffffff)                        /* Hifi�����ϱ���SN�� */
#define HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX    (128)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ��Ƶ�������ģʽ������/¼�� */
enum AUDIO_PCM_MODE_ENUM
{
    AUDIO_PCM_MODE_PLAYBACK = 0,
    AUDIO_PCM_MODE_CAPTURE,
/*    AUDIO_PCM_MODE_HDMI,
    AUDIO_PCM_MODE_WIFIDISPLAY,*/
    AUDIO_PCM_MODE_BUT
};
typedef unsigned short  AUDIO_PCM_MODE_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : AUDIO_RECORD_TYPE_ENUM
 ��������  : ¼������ö��
*****************************************************************************/
enum AUDIO_RECORD_TYPE_ENUM
{
    AUDIO_RECORD_TYPE_DISABLE   = 0,                            /*û��¼������*/
    AUDIO_RECORD_TYPE_CALL      = 1,                            /*��ͨͨ��¼��*/
    AUDIO_RECORD_TYPE_CAMCORD   = 2,                            /*ͨ��ʱ����*/
    AUDIO_RECORD_TYPE_3RD_MODEM = 3,                            /*������modem¼��*/
    AUDIO_RECORD_TYPE_AUDIO     = 4,                            /*��ͨ��Ƶ¼��*/
    AUDIO_RECORD_TYPE_FM        = 5,                            /*��ͨFM¼��*/
	AUDIO_RECORD_TYPE_VQM       = 6,                            /*���������������*/
    AUDIO_RECORD_TYPE_BUT
};
typedef unsigned short  AUDIO_RECORD_TYPE_ENUM_UINT16;

/* ��Ƶ�����������ö�� */
enum AUDIO_PCM_OBJ_ENUM
{
    AUDIO_PCM_OBJ_AP = 0,
    AUDIO_PCM_OBJ_HIFI,
    AUDIO_PCM_OBJ_BUT
};
typedef unsigned short  AUDIO_PCM_OBJ_ENUM_UINT16;

/* ��Ƶ���ݰ��˴�������ö�٣���ö����AP��궨��SNDRV_PCM_TRIGGER_XXXXһһ��Ӧ */
enum AUDIO_PCM_TRIGGER_CMD_ENUM
{
    AUDIO_PCM_TRIGGER_STOP          = 0,            /* ��Ƶͨ·ֹͣ */
    AUDIO_PCM_TRIGGER_START         = 1,            /* ��Ƶͨ·���� */
    AUDIO_PCM_TRIGGER_PAUSE_PUSH    = 3,            /* ��Ƶͨ·��ͣ */
    AUDIO_PCM_TRIGGER_PAUSE_RELEASE = 4,            /* ��Ƶͨ·�ͷ���ͣ */
    AUDIO_PCM_TRIGGER_SUSPEND       = 5,            /* ��Ƶͨ·��ͣ */
    AUDIO_PCM_TRIGGER_RESUME        = 6,            /* ��Ƶͨ·���� */
    AUDIO_PCM_TRIGGER_BUT
};
typedef unsigned short  AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16;

/* AUDIO PLAYER��Ƶ�������ݸ�ʽ״̬ö�� */
enum AUDIO_FILE_FORMAT_ENUM
{
    AUDIO_FILE_FORMAT_MP3 = 0,
    AUDIO_FILE_FORMAT_AAC,
    AUDIO_FILE_FORMAT_WAV,
    AUDIO_FILE_FORMAT_BUT
};
typedef unsigned short  AUDIO_FILE_FORMAT_ENUM_UINT16;


/* AUDIO PLAYER��Ƶ���ݲ������״̬ö�� */
enum AUDIO_PLAY_DONE_IND_ENUM
{
    AUDIO_PLAY_DONE_NORMAL   = 0,                           /* һ����Ƶ��������������� */
    AUDIO_PLAY_DONE_COMPLETE,                               /* һ��������Ƶ�ļ������������ */
    AUDIO_PLAY_DONE_ABNORMAL,                               /* ���Ź��̳��������ж� */
    AUDIO_PLAY_DONE_RESET,                                     /*ap command : listen thread exit*/
    AUDIO_PLAY_DONE_BUTT
};

typedef unsigned short  AUDIO_PLAY_DONE_IND_ENUM_UINT16;

/* AUDIO PLAYERִ�й����гɹ�ʧ��ö�� */
enum AUDIO_PLAY_RESULT_CNF_ENUM
{
    AUDIO_PLAY_RESULT_OK = 0,                               /* �ɹ� */
    AUDIO_PLAY_RESULT_FAIL,                                 /* ʧ�� */
    AUDIO_PLAY_RESULT_BUT
};

typedef unsigned short  AUDIO_PLAY_RESULT_CNF_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_ENABLE_ENUM
 ��������  : ��Чʹ��ö��
*****************************************************************************/
enum AUDIO_EFFECT_ENABLE_ENUM
{
    AUDIO_EFFECT_NONE        = 0,   /* ��Ч�ر� */
    AUDIO_EFFECT_DTS_ENABLE,        /* DTS��Чʹ�� */
    AUDIO_EFFECT_DTS_DISABLE,
    AUDIO_EFFECT_DM3_ENABLE,        /* dobly��Чʹ�� */
    AUDIO_EFFECT_DM3_DISABLE,
    AUDIO_EFFECT_ENABLE_BUT
};
typedef unsigned short AUDIO_EFFECT_ENABLE_UINT16;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_DEVICE_ENUM
 ��������  : ��ǰ�豸
*****************************************************************************/
enum AUDIO_EFFECT_DEVICE_ENUM
{
    AUDIO_EFFECT_DEVICE_HEADPHONE = 0,
    AUDIO_EFFECT_DEVICE_SPK,
    AUDIO_EFFECT_DEVICE_BUT
};
typedef unsigned short AUDIO_EFFECT_DEVICE_UINT16;

/* ��Ч���� */
enum AUDIO_EFFECT_TYPE_ENUM
{
    AUDIO_EFFECT_DTS = 0, /* DTS��Ч */
    AUDIO_EFFECT_DM3,     /* dolby��Ч */
    AUDIO_EFFECT_TYPE_BUT
};
typedef unsigned short AUDIO_EFFECT_TYPE_UINT16;

/* ������Ч���� */
enum AUDIO_EFFECT_SETPARAMS_ENUM
{
    AUDIO_EFFECT_DM3_BYPASS = 1,
    AUDIO_EFFECT_DM3_SINGLE_DEVICE_VALUE = 2,
    AUDIO_EFFECT_DM3_ALL_VALUES = 3,
    AUDIO_EFFECT_DM3_BUT
};
typedef unsigned short AUDIO_EFFECT_SETPARAMS_UINT16;

/* ����setLoop */
enum AUDIO_PLAYER_SET_LOOP_ENUM
{
    AUDIO_PLAYER_SET_LOOP_FLASE = 0,
    AUDIO_PLAYER_SET_LOOP_TRUE  = 1,
    AUDIO_PLAYER_SET_LOOP_BUTT
};
typedef unsigned int AUDIO_PLAYER_SET_LOOP_ENUM_UINT32;

/* ͨ�����ϱ�����Ƶҵ������� */
enum VOICE_AUDIO_ERR_IND_ENUM
{
    VOICE_AUDIO_NO_ERR          = 0,
    VOICE_AUDIO_ERR_IND         = 1,
    VOICE_AUDIO_FATAL_ERR_IND   = 2,
    VOICE_AUDIO_ERR_BUTT
};
typedef unsigned int VOICE_AUDIO_ERR_IND_ENUM_UINT32;

/* ͨ�����ϱ�����Ƶҵ������ö�� */
enum VOICE_AUDIO_MODE_ENUM
{
    VOICE_AUDIO_MODE_PLAY       = 0,
    VOICE_AUDIO_MODE_RECORD     = 1,
    VOICE_AUDIO_MODE_BUT
};
typedef unsigned int VOICE_AUDIO_MODE_ENUM_UINT32;

enum AUDIO_MSG_ENUM
{
    ID_AP_VOICEPP_START_REQ             = 0xDD42,                       /* ����VOICEPPͨ�� */
    ID_VOICEPP_MSG_START                = ID_AP_VOICEPP_START_REQ,
    ID_VOICEPP_AP_START_CNF             = 0xDD43,
    ID_AP_VOICEPP_STOP_REQ              = 0xDD44,                        /* ��ֹVOICEPPͨ�� */
    ID_VOICEPP_AP_STOP_CNF              = 0xDD45,
    ID_AP_VOICEPP_SET_DEVICE_REQ        = 0xDD46,                  /* ������������豸 */
    ID_VOICEPP_AP_SET_DEVICE_CNF        = 0xDD47,
    ID_AP_VOICEPP_SET_WB_REQ            = 0xDD48,                      /* ���ÿ�խ�� */
    ID_VOICEPP_AP_SET_WB_CNF            = 0xDD49,
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

    ID_AUDIO_PLAYER_START_REQ           = 0xDD71,
    ID_AUDIO_PLAYER_START_CNF           = 0xDD72,
    ID_AUDIO_PLAYER_STOP_REQ            = 0xDD73,
    ID_AUDIO_PLAYER_STOP_CNF            = 0xDD74,

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
    ID_AP_AUDIO_CMD_SET_MMI_MODE_CMD    = 0xDD98,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
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
    ID_AP_AUDIO_SET_DTS_GEQ_TYPE_CMD     = 0xDD39,           /* AP֪ͨHifi DTS GEQ��Ч����*/  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_GEQ_TYPE_REQ_STRU */
    ID_AP_AUDIO_SET_DTS_GEQ_ENABLE_CMD   = 0xDD3B,           /* AP֪ͨHifi DTS GEQʹ��*/

    /* AP��HIFI�Ŀ������ö���hifi codec������Ϣ */
    ID_AP_AUDIO_SET_EXCODEC_BYPASS_CMD    = 0xDD3D,

    /* A��֪ͨHIFI C �˸�λ��ϢID */
    ID_AP_HIFI_CCPU_RESET_REQ           = 0xDDE1,           /* _H2ASN_MsgChoice AP_HIFI_CCPU_RESET_REQ_STRU */

    /* hifi�ظ�ID_AP_HIFI_CCPU_RESET_REQ */
    ID_HIFI_AP_CCPU_RESET_CNF           = 0xDDE2,           /* _H2ASN_MsgChoice HIFI_AP_CCPU_RESET_CNF_STRU */

    ID_AP_HIFI_REMOTE_SET_BUF_CMD       = 0xDDE3,           /* _H2ASN_MsgChoice AP_VOICE_SET_BUF_CMD_STRU */
    ID_HIFI_AP_REMOTE_PERIOD_ELAPSED_CMD= 0xDDE4,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_PERIOD_ELAPSED_IND_STRU */

    ID_AP_HIFI_REMOTE_RECORD_START_REQ  = 0xDDE5,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_RECORD_START_CNF  = 0xDDE6,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_HIFI_AP_REMOTE_RECORD_DATA_ERR_IND = 0xDDE7,         /* _H2ASN_MsgChoice VOICE_AP_REMOTE_DATA_ERR_IND_STRU */

    ID_AP_HIFI_REMOTE_RECORD_STOP_REQ   = 0xDDE8,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_RECORD_STOP_CNF   = 0xDDE9,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_AP_HIFI_REMOTE_PLAY_START_REQ    = 0xDDEA,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_PLAY_START_CNF    = 0xDDEB,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_AP_HIFI_REMOTE_PLAY_DATA_ERR_IND = 0xDDEC,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_DATA_ERR_IND_STRU */

    ID_AP_HIFI_REMOTE_PLAY_STOP_REQ     = 0xDDED,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_PLAY_STOP_CNF     = 0xDDEE,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_HIFI_AP_REMOTE_VOICE_STOP_CMD    = 0xDDEF,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */
    ID_AP_HIFI_CLEAN_RINGBUF_CMD        = 0xDDF0,          /* AP֪ͨhifi����������λ���������ϢID */
};
typedef unsigned short  AUDIO_MSG_ENUM_UINT16;

/* misc�豸commad�ֶ�ö�� */
enum AUDIO_MISC_CMD_ENUM
{
    AUDIO_MISC_CMD_SYNC = 0,
    AUDIO_MISC_CMD_NOTIFY,
    AUDIO_MISC_CMD_ASYNC,
    AUDIO_MISC_CMD_BUTT,
};
typedef unsigned int  AUDIO_MISC_CMD_ENUM_UINT32;

/* VOIPͨ��ģʽö�� */
enum AUDIO_VOIP_DEVICE_ENUM
{
    AUDIO_VOIP_DEVICE_HANDSET           = 0,                /* �ֳ�ģʽ */
    AUDIO_VOIP_DEVICE_HANDFREE,                             /* ����ģʽ */
    AUDIO_VOIP_DEVICE_CARFREE,                              /* ��������ģʽ */
    AUDIO_VOIP_DEVICE_HEADSET,                              /* ����ģʽ */
    AUDIO_VOIP_DEVICE_BLUETOOTH,                            /* ����ģʽ */
    AUDIO_VOIP_DEVICE_PCVOICE,                              /* PC-VOICEģʽ */
    AUDIO_VOIP_DEVICE_HEADPHONE,                            /* ��������MIC�Ķ���ͨ�� */
    AUDIO_VOIP_DEVICE_BUTT
};
typedef unsigned int  AUDIO_VOIP_DEVICE_ENUM_UINT32;

/* ��ѧ��ǿģʽö�� */
enum AUDIO_ENHANCE_DEVICE_ENUM
{
    AUDIO_ENHANCE_DEVICE_HANDSET        = 0,                /* �ֳ�ģʽ */
    AUDIO_ENHANCE_DEVICE_HANDFREE       = 1,                /* ����ģʽ */
    AUDIO_ENHANCE_DEVICE_CARFREE        = 2,                /* ��������ģʽ */
    AUDIO_ENHANCE_DEVICE_HEADSET        = 3,                /* ����ģʽ */
    AUDIO_ENHANCE_DEVICE_BLUETOOTH      = 4,                /* ����ģʽ */
    AUDIO_ENHANCE_DEVICE_PCVOICE        = 5,                /* PC-VOICEģʽ */
    AUDIO_ENHANCE_DEVICE_HEADPHONE      = 6,                /* ��������MIC�Ķ���ͨ�� */
    AUDIO_ENHANCE_DEVICE_SUPER_HANDFREE = 7,
    AUDIO_ENHANCE_DEVICE_HANDSET_AVE    = 8,
    AUDIO_ENHANCE_DEVICE_BUTT
};
typedef unsigned int  AUDIO_ENHANCE_DEVICE_ENUM_UINT32;

/* ��ѧ��ǿģ��ö�� */
enum AUDIO_ENHANCE_MODULE_ENUM
{
    AUDIO_ENHANCE_MODULE_DEFAULT        = 0,                /* ��ͨ��Ƶ���� */
    AUDIO_ENHANCE_MODULE_VOIP,                              /* VOIP��Ƶ���� */
    AUDIO_ENHANCE_MODULE_SIRI,                              /* ����ʶ����Ƶ���� */
    AUDIO_ENHANCE_MODULE_INCALL,                         /* ����ͨ������ */
    AUDIO_ENHANCE_MODULE_OUTCALL,                         /* �˳�ͨ������ */
    AUDIO_ENHANCE_MODULE_BUTT,

};
typedef unsigned int   AUDIO_ENHANCE_MODULE_ENUM_UINT32;


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
 ʵ������  : AUDIO_HIFIMISC_MSG_TAIL_STRU
 ��������  : AP HifiMisc�豸����Ϣ��ʶ�ṹ�壬������Ϣ���͡���Ϣ��ţ�Ҫ�������
             ԭ��Ϣ����д����Ϣĩβ
*****************************************************************************/
 typedef struct
{
    unsigned int                           uwCmdId;            /*_H2ASN_Replace VOS_UINT32 uwCmdId;*/
    unsigned int                           uwSn;               /*_H2ASN_Replace VOS_UINT32 uwSn;*/
} AUDIO_HIFIMISC_MSG_TAIL_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_OPEN_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_PCM_OPEN_REQ��DSP_PID_AUDIO��֪ͨHifi����
             �������ͨ������
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD25*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ������������/������� */
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_PCM_OPEN_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_CLOSE_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_PCM_CLOSE_REQ��DSP_PID_AUDIO��֪ͨHifiֹͣ
             �������ͨ������
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD26*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ֹͣ��������/������� */
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_PCM_CLOSE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_HW_PARAMS_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_PCM_HW_PARAMS_REQ��DSP_PID_AUDIO��֪ͨHifi
             ������Դ��س�ʼ��
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD27*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ���ʼ�������Դ��ͨ�� */
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
    unsigned int                            uwChannelNum;       /* ͨ���������� */ /*_H2ASN_Replace VOS_UINT32 uwChannelNum;*/
    unsigned int                            uwSampleRate;       /* ��ǰͨ�������� */ /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
} AUDIO_PCM_HW_PARAMS_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_TRIGGER_REQ_STRU
 ��������  : AP��Hifi���͸���ϢID_AP_AUDIO_PCM_TRIGGER_REQ��DSP_PID_AUDIO������
             Hifi��ĳ����ͨ������״̬����
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD2A*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ����ͨ��ģʽ */
    AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16       enCmd;              /* ���������� */
    AUDIO_PCM_OBJ_ENUM_UINT16               enPcmObj;           /* �����Ķ���ΪAP����Hifi */
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
    //void                                   *pSubStream;         /* ��ǰBuff��Ӧ����Ƶ�������,��AP����Ч */
    unsigned int                            uwSubStream_l;
    unsigned int                            uwSubStream_h;
    unsigned int                            uwBufAddr;          /* �������׵�ַ */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                            uwBufSize;          /* �������Ĵ�С����λbyte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
} AUDIO_PCM_TRIGGER_REQ_STRU;
/*****************************************************************************
 ʵ������  : AUDIO_PCM_TRIGGER_CNF_STRU
 ��������  : Hifi������ϢID_AUDIO_AP_PCM_TRIGGER_CNF֪ͨAP
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ����ͨ��ģʽ */
    AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16       enCmd;
    //void                                   *pSubStream;         /* ��ǰBuff��Ӧ����Ƶ�������,��AP����Ч */
    unsigned int                            uwSubStream_l;
    unsigned int                            uwSubStream_h;
} AUDIO_PCM_TRIGGER_CNF_STRU;
/*****************************************************************************
 ʵ������  : AUDIO_PCM_SET_BUF_CMD_STRU
 ��������  : AP��Hifi������ϢID_AP_AUDIO_PCM_SET_BUF_CMD��DSP_PID_AUDIO������ĳ
             ����ͨ�����������Buffer��ַ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD2C*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ����ͨ��ģʽ */
    AUDIO_PCM_OBJ_ENUM_UINT16               enPcmObj;           /* �����Ķ���ΪAP����Hifi */
    unsigned int                            uwBufAddr;          /* �������׵�ַ */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                            uwBufSize;          /* �������Ĵ�С����λbyte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
} AUDIO_PCM_SET_BUF_CMD_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU
 ��������  : Hifi������ϢID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD֪ͨAP��Hifiһ��PERIOD
             ���������������������
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD2D*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* ����ͨ��ģʽ */
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
    // void                                   *pSubStream;         /* ��ǰBuff��Ӧ����Ƶ�������,��AP����Ч */
    unsigned int                             uwSubStream_l;
    unsigned int                             uwSubStream_h;
} AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_RECORD_START_STRU
 ��������  : AP��HAL��ͨ��DSP����������ϢID_AP_AUDIO_RECORD_START_REQ֪ͨHIFI��
             ʼ¼��
*****************************************************************************/
/* ��ʼ¼����Ϣ */
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD40*/ /*_H2ASN_Skip*/
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_RECORD_TYPE_ENUM_UINT16           enRecordType;       /* ¼������ */
    unsigned short                          uhwTarSmpRate;      /*_H2ASN_Replace VOS_UINT16 uhwTarSmpRate;*/
} AUDIO_RECORD_START_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_RECORD_STOP_STRU
 ��������  : AP��HAL��ͨ��DSP����������ϢID_AP_AUDIO_RECORD_STOP_REQ֪ͨHIFIͣ
             ֹ¼��
*****************************************************************************/
/* ����¼����Ϣ */
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD41*/ /*_H2ASN_Skip*/
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_RECORD_TYPE_ENUM_UINT16           enRecordType;       /* ¼������ */
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_RECORD_STOP_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_DECODE_REQ_STRU
 ��������  : AP��HAL��ͨ��DSP����������ϢID_AP_AUDIO_PLAY_DECODE_REQ������Hifi
             ��һ֡���ݽ��н��벢��д��ָ����ַ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    AUDIO_FILE_FORMAT_ENUM_UINT16           enFormat;           /* ��Ƶ��ʽ */
    unsigned int                            uwSampleRate;       /* ��Ƶ���ݲ����� */ /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
    unsigned int                            uwChannels;         /* ��Ƶ���������� */ /*_H2ASN_Replace VOS_UINT32 uwChannels;*/
    unsigned int                            uwDataAddr;         /* δ�������ݻ��� */ /*_H2ASN_Replace VOS_UINT32 uwDataAddr;*/
    unsigned int                            uwDataLen;          /* �������ݳ��� */ /*_H2ASN_Replace VOS_UINT32 uwDataLen;*/
    unsigned int                            uwPcmAddr;          /* �������������ݵĻ��� */ /*_H2ASN_Replace VOS_UINT32 uwPcmAddr;*/
    unsigned int                            uwPcmLen;           /* �������ݳ��� */ /*_H2ASN_Replace VOS_UINT32 uwPcmLen;*/
} AUDIO_PLAYER_DECODE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_DECODE_RSP_STRU
 ��������  : HIFI������ϢID_AUDIO_AP_PLAY_DECODE_RSP���ظ�AP���������
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned short                          uhwRet;             /* �����ؽ�� */ /*_H2ASN_Replace VOS_UINT16 uhwRet;*/
    unsigned short                          uhwReserved1;       /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_PLAYER_DECODE_RSP_STRU;


/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_START_REQ_STRU
 ��������  : ����Ϣ����Hifi�������͹��Ĳ���
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD51*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                            uwStartPos;         /* ��ʼ����λ�ã����ļ�ͷ */ /*_H2ASN_Replace VOS_UINT32 uwStartPos;*/
    unsigned short                          uhwWithHeader;      /* AP����µ�Buff���Ƿ����512K���ļ�ͷ��0��ʾ�����ڣ�1��ʾ���� */ /*_H2ASN_Replace VOS_UINT16 uhwWithHeader;*/
    AUDIO_FILE_FORMAT_ENUM_UINT16           enFormat;           /* ��Ƶ�ļ���ʽ */
    unsigned int                            uwSampleRate;       /* ��Ƶ���ݲ����� */ /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
    unsigned int                            uwOutputDevice;     /* ��������豸(��������speaker) */ /*_H2ASN_Replace VOS_UINT32 uwOutputDevice;*/
    unsigned int                            uwTotalFileSize;    /* ����MP3/AAC���ֵĴ�С�����ļ�ͷ��Ϣ����λbyte */ /*_H2ASN_Replace VOS_UINT32 uwTotalFileSize;*/
    unsigned int                            wavDataSize;        /* ����wav�ļ����ݴ�С,�������ļ�ͷ */
} AUDIO_PLAYER_START_REQ_STRU;
/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_SET_VOL_REQ_STRU
 ��������  : ����Ϣ��������Hifi���͹��Ĳ���
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD70*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                            uwValue;            /* ����ֵ��Q15  */ /*_H2ASN_Replace VOS_UINT32 uwValue;*/
} AUDIO_PLAYER_SET_VOL_REQ_STRU;

/*****************************************************************************
 ʵ������  : AP_HIFI_CCPU_RESET_REQ_STRU
 ��������  : AP֪ͨHIFI C�˸�λ����Ϣ�ṹ��
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

/*****************************************************************************
 ʵ������  : APAUDIO_OP_RSLT_STRU
 ��������  : ����Ϣ��AP�ظ�����ִ��ִ�н��
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwResult;          /* �Ƿ�ִ�гɹ� */ /*_H2ASN_Replace VOS_UINT16 uhwResult;*/
} APAUDIO_OP_RSLT_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_DONE_IND_STRU
 ��������  : ����Ϣ֪ͨAP��ǰ��Ƶ�ļ����Ž��
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD56*/ /*_H2ASN_Skip */
    AUDIO_PLAY_DONE_IND_ENUM_UINT16         enPlayDone;         /* ���Ž��ö�� */
} AUDIO_PLAYER_DONE_IND_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_PAUSE_REQ_STRU
 ��������  : ����Ϣ����Hifi��ͣ��ֹͣ���͹��Ľ���
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD53*/ /*_H2ASN_Skip */
    unsigned short                          uhwPlayPending;     /* ��ͣ����ֹͣ���� */ /*_H2ASN_Replace VOS_UINT16 uhwPlayPending;*/
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned short                          uhwIsChangeDev;     /*_H2ASN_Replace VOS_UINT16 uhwIsChangeDev;*/
} AUDIO_PLAYER_PAUSE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_PAUSE_CNF_STRU
 ��������  : ����Ϣ����Hifi��ͣʱ���ŵ��������ͽ��
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwResult;          /* �Ƿ�ִ�гɹ� */ /*_H2ASN_Replace VOS_UINT16 uhwResult;*/
    unsigned int                            uwPlayedBytes;      /* ��ǰ�Ѳ��ŵ������� */ /*_H2ASN_Replace VOS_UINT32 uwPlayedBytes;*/
} AUDIO_PLAYER_PAUSE_CNF_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_PLAYDONE_SIGNAL_REQ_STRU
 ��������  : AP����HIFI�Ĳ��Ž����ź�������Ϣ�ṹ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwPlayDone;        /* AP������������ */ /*_H2ASN_Replace VOS_UINT16 uhwPlayDone;*/
} AUDIO_PLAYER_PLAYDONE_SIGNAL_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_SEEK_REQ_STRU
 ��������  : AP����HIFI��seek req��Ϣ�ṹ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD63*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                           uwSeekPos;          /* seekλ�� */ /*_H2ASN_Replace VOS_UINT32 uwSeekPos;*/
    AUDIO_PLAYER_SET_LOOP_ENUM_UINT32       enSetLoop;          /* ����ѭ����־λ */ /*_H2ASN_Replace VOS_UINT32 enSetLoop;*/
} AUDIO_PLAYER_SEEK_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_SEEK_CNF_STRU
 ��������  : ����Ϣ֪ͨAP seek result
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD64*/ /*_H2ASN_Skip */
    AUDIO_PLAY_RESULT_CNF_ENUM_UINT16       enSeekResult;       /* seek��� */ /*_H2ASN_Replace VOS_UINT32 enSeekResult;*/
} AUDIO_PLAYER_SEEK_CNF_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_UPDATE_BUF_CMD_STRU
 ��������  : ����Ϣ֪ͨHifi���²���BUFFER
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD57*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    DRV_SEND_DATA_STRU
} AUDIO_PLAYER_UPDATE_BUF_CMD_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_QUERY_TIME_REQ_STRU
 ��������  : ����Ϣ��ѯHifi���Ž���״̬��Ϣ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD59*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
} AUDIO_PLAYER_QUERY_TIME_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_QUERY_TIME_CNF_STRU
 ��������  : ����ϢHifi�ϱ����Ž���״̬��Ϣ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD60*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                            uwPlayedBytes;      /* ��ǰ�Ѳ��ŵ������ļ���С����λbyte�����ļ�ͷ */ /*_H2ASN_Replace VOS_UINT32 uwPlayedBytes;*/
} AUDIO_PLAYER_QUERY_TIME_CNF_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_QUERY_STATUS_REQ_STRU
 ��������  : ����Ϣ��ѯHifi����״̬��Ϣ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD61*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
} AUDIO_PLAYER_QUERY_STATUS_REQ_STRU;


/*****************************************************************************
 ʵ������  : AUDIO_PLAYER_QUERY_STATUS_CNF_STRU
 ��������  : ����ϢHifi�ϱ�����״̬��Ϣ
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD62*/ /*_H2ASN_Skip */
    AUDIO_PLAY_DONE_IND_ENUM_UINT16         enPlayStatus;       /* ���Ž��ö�� */
} AUDIO_PLAYER_QUERY_STATUS_CNF_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_ENABLE_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_EFFECT_ENABLE_REQ��DSP_PID_AUDIO��֪ͨHifi
      ʹ����Ч
*****************************************************************************/
typedef struct{
    unsigned short                          uhwMsgId;           /*0xDD34*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_EFFECT_TYPE_UINT16                enEffectType;       /*_H2ASN_Replace VOS_UINT16 enEffectType;*/
    AUDIO_EFFECT_ENABLE_UINT16              enEffectEnable;     /*_H2ASN_Replace VOS_UINT16 enEffectEnable;*/
}AUDIO_EFFECT_ENABLE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_SET_PARAMS_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_EFFECT_PARAM_REQ��DSP_PID_AUDIO��֪ͨHifi
             ������Ч����
*****************************************************************************/
typedef struct{
    unsigned short                          uhwMsgId;           /*0xDD33*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_EFFECT_TYPE_UINT16                enEffectType;       /* ��Ч���� */ /*_H2ASN_Replace VOS_UINT16 enEffectType;*/
    AUDIO_EFFECT_SETPARAMS_UINT16           enEffectSetParam;   /* �������� */ /*_H2ASN_Replace VOS_UINT16 enEffectSetParam;*/
    DRV_SEND_DATA_STRU
}AUDIO_EFFECT_SET_PARAMS_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_COMP_FILT_SET_PARAMS_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_EFFECT_PARAM_REQ��DSP_PID_AUDIO��֪ͨHifi
             ������Ч����
*****************************************************************************/
typedef struct{
    unsigned short            uhwMsgId;                         /*_H2ASN_Skip */
    unsigned short            uhwReserve;                       /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned short            uhwPcmCompEnable;                 /* ������ ʹ�ܱ�־ */ /*_H2ASN_Replace VOS_UINT16 uhwPcmCompEnable;*/
    short                     shwCompGain;                      /* ������ ʩ�����棨���ƣ� */ /*_H2ASN_Replace VOS_INT16 shwCompGain;*/
    short                     shwM;                             /* ������ �˲����ĳ��� */ /*_H2ASN_Replace VOS_INT16 shwM; */
    short                     shwReserved;                      /*_H2ASN_Replace VOS_INT16 shwReserved;*/
    short                     ashwCoef[HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX];  /* �����˲����� */ /*_H2ASN_Replace VOS_INT16 ashwCoef[HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX];*/
}AUDIO_COMP_FILT_SET_PARAMS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AP_AUDIO_ENHANCE_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģ�鴦����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    unsigned short                      uhwMsgId;           /*0xDD81*/ /*_H2ASN_Skip */
    unsigned short                      uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                        uwSampleRate;       /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* ��Ҫ������ģ�� */
}AP_AUDIO_ENHANCE_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AP_AUDIO_ENHANCE_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣģ�鴦����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    unsigned short                      uhwMsgId;           /*0xDD83*/ /*_H2ASN_Skip */
    unsigned short                      uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* ��Ҫֹͣ��ģ�� */
}AP_AUDIO_ENHANCE_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AP_AUDIO_ENHANCE_SET_DEVICE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����豸ģʽ
*****************************************************************************/
typedef struct
{
    unsigned short                      uhwMsgId;               /*0xDD85*/ /*_H2ASN_Skip */
    unsigned short                      uhwReserve;             /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_ENHANCE_DEVICE_ENUM_UINT32    uwDevice;
}AP_AUDIO_ENHANCE_SET_DEVICE_REQ_STRU;


/* �������ýṹ�� */
typedef struct
{
    unsigned short                      usMsgName;              /* ԭ������ */  /*0xDD92*/ /*_H2ASN_Skip*/
    unsigned short                      usReserve;              /* ���� */      /*_H2ASN_Replace VOS_UINT16 usReserve;*/
    unsigned int                        uwPathID;               /* ·��ID */    /*_H2ASN_Replace VOS_UINT32 uwPathID;*/
    unsigned int                        uwModuleID;             /* ģ��ID */    /*_H2ASN_Replace VOS_UINT32 uwModuleID;*/
    unsigned int                        uwSize;                 /* ���ݴ�С */  /*_H2ASN_Replace VOS_UINT32 uwSize;*/
    unsigned char                       aucData[4];             /* ������ʼ */  /*_H2ASN_Replace VOS_UINT8 aucData;*/

}AP_AUDIO_MLIB_SET_PARA_IND_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_SET_DTS_ENABLE_REQ��DSP_PID_AUDIO��֪ͨHifi����DTS��Чʹ�����
*****************************************************************************/
typedef struct{
    unsigned short                      uhwMsgId;               /*0xDD36*/ /*_H2ASN_Skip */ /* ����DTS��Чʹ�����ID */
    unsigned short                      uhwEnableFlag;          /* DTS��Ч�Ƿ�ʹ�� */ /*_H2ASN_Replace VOS_UINT16 uhwEnableFlag;*/
}AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_DTS_SET_GEQ_TYPE_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_SET_DTS_GEQ_TYPE__REQ��DSP_PID_AUDIO��֪ͨHifi����DTS��Ч����
*****************************************************************************/
typedef struct{
    unsigned short                      uhwMsgId;               /*0xDD39*/ /* ����DTS��Ч��Ч����ID */
    unsigned short                      uhwGEQTypeIndex;        /* DTS��Ч�������� */
}AUDIO_EFFECT_DTS_SET_GEQ_TYPE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_DTS_SET_GEQ_ENABLE_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_SET_DTS_GEQ_ENABLE_REQ��DSP_PID_AUDIO��֪ͨHifi����DTS GEQʹ��
*****************************************************************************/
typedef struct{
    unsigned short                      uhwMsgId;               /*0xDD3B*/ /* ����DTS��Ч GEQʹ��ID */
    unsigned short                      uhwGEQEnableFlag;       /* DTS��ЧGEQ �Ƿ�ʹ�� */
}AUDIO_EFFECT_DTS_SET_GEQ_ENABLE_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU
 ��������  : AP���͸���ϢID_AP_AUDIO_SET_DTS_DEV_REQ��DSP_PID_AUDIO��֪ͨHifi����DTS�豸ģʽ
*****************************************************************************/
 typedef struct
{
    unsigned short                      uhwMsgId;              /*0xDD38*/ /*_H2ASN_Skip */ /* ����DTS��Ч�豸ģʽID */
    unsigned short                      uhwDevMode;           /* DTS��Ч�豸ģʽ */ /*_H2ASN_Replace VOS_UINT16 uhwDevMode;*/
} AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_CMD_COMMON_SET_STRU
 ��������  : ͨ������
*****************************************************************************/
typedef struct {
    unsigned short                      uhwMsgId;
    unsigned short                      uhwReserve;
    unsigned int                        uwValue;
} AUDIO_CMD_COMMON_SET_STRU;

/*****************************************************************************
 ʵ������  : AP_VOICE_REMOTE_AUDIO_REQ_STRU
 ��������  : Զ�˲��š�¼����ʼ
*****************************************************************************/
typedef struct {
    MSG_HEADER
    unsigned short              uhwMessageId;
    unsigned short              uhwReserve;
    unsigned int                uwSampeRate;
    unsigned int                uwBufAddr;          /* �������׵�ַ */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                uwBufSize;          /* �������Ĵ�С����λbyte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
}AP_VOICE_REMOTE_AUDIO_REQ_STRU;

/*****************************************************************************
 ʵ������  : VOICE_AP_REMOTE_AUDIO_CNF_STRU
 ��������  : Զ�˲��š�¼���ظ�
*****************************************************************************/
typedef struct {
    MSG_HEADER
    unsigned short                  uhwMessageId;
    unsigned short                  uhwReserve;
    unsigned int                    uwResult;
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;
}VOICE_AP_REMOTE_AUDIO_CNF_STRU;

/*****************************************************************************
 ʵ������  : AP_VOICE_SET_BUF_CMD_STRU
 ��������  : ����Զ��¼�����������ݵ�ַ
*****************************************************************************/
typedef struct {
    MSG_HEADER
    unsigned short                  uhwMessageId;       /*_H2ASN_Skip */
    unsigned short                  uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;
    unsigned int                    uwBufAddr;          /* �������׵�ַ */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                    uwBufSize;          /* �������Ĵ�С����λbyte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
}AP_VOICE_SET_BUF_CMD_STRU;

/*****************************************************************************
 ʵ������  : VOICE_AP_REMOTE_PERIOD_ELAPSED_IND_STRU
 ��������  : Զ��¼��������HIFI�ദ����ϵ���Ϣ
*****************************************************************************/
typedef struct {
    MSG_HEADER
    unsigned short                  uhwMessageId;       /*_H2ASN_Skip */
    unsigned short                  uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;
}VOICE_AP_REMOTE_PERIOD_ELAPSED_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_AP_REMOTE_DATA_ERR_IND_STRU
 ��������  : ��ʱ�Դ�����ǲ��ɻָ��Ĵ��������ϱ��ṹ�嶨��
*****************************************************************************/
typedef struct {
    MSG_HEADER
    unsigned short  uhwMessageId;
    unsigned short  uhwReserve;
    unsigned int    uwErrorCode;
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;
}VOICE_AP_REMOTE_DATA_ERR_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_NO_PARAM_MSG_STRU
 ��������  : ��������Ϣֻ����ϢID��û�и��ӵ���Ϣ������
*****************************************************************************/
typedef struct {
    MSG_HEADER
    unsigned short   usMessageId;
    unsigned short   usReserve;
}VOICE_AP_NO_PARAM_MSG_STRU;

#if 0                                                        /* _H2ASN_Skip */
/*****************************************************************************
 ʵ������  : AUDIO_LOOP_CNF_STRU
 ��������  : ����Ϣ֪ͨAP��Ƶ���ش򿪻�ر��Ƿ�ɹ�
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;                           /*_H2ASN_Skip */
    AUDIO_PLAY_RESULT_CNF_ENUM_UINT16       enAudioLoopCnf;
} AUDIO_LOOP_CNF_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU
 ��������  : ����Ϣ����Hifi�Ĳ���Buff��Ϣ����ʾһ֡�����Ѿ��������
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*0xDD31*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU;

/*****************************************************************************
 ʵ������  : AUDIO_PCM_UPDATE_CAPTURE_BUFF_CMD_STRU
 ��������  : ����Ϣ����Hifi��¼��Buff��Ϣ����ʾһ֡�����Ѿ�¼�����
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*0xDD2F*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} AUDIO_PCM_UPDATE_CAPTURE_BUFF_CMD_STRU;

/*****************************************************************************
 �ṹ��    : AUDIO_PCM_ENHANCE_START_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ƶ��ǿ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwSampleRate;
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* ��Ҫ������ģ�� */
}AUDIO_PCM_ENHANCE_START_IND_STRU;

/*****************************************************************************
 �ṹ��    : AUDIO_PCM_ENHANCE_STOP_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ��Ƶ��ǿ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* ��Ҫ������ģ�� */
}AUDIO_PCM_ENHANCE_STOP_IND_STRU;

/*****************************************************************************
 �ṹ��    : AUDIO_PCM_ENHANCE_SET_DEVICE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����豸ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    AUDIO_ENHANCE_DEVICE_ENUM_UINT32    uwDevice;
}AUDIO_PCM_ENHANCE_SET_DEVICE_IND_STRU;


#endif                                                      /* _H2ASN_Skip */

/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    AUDIO_MSG_ENUM_UINT16               enMsgID;            /* _H2ASN_MsgChoice_Export AUDIO_MSG_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AUDIO_MSG_ENUM_UINT16
    ****************************************************************************/
}AUDIO_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    AUDIO_TRACE_MSG_DATA                 stMsgData;
}AudioTrace_MSG;

#endif                                                     /* _H2ASN_Skip */


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
