


#ifndef __VCCODECINTERFACE_H__
#define __VCCODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define VC_VOICE_MAX_MSD_LEN (140)                                              /* ECALL��С���ݼ�(MSD)����󳤶� ��λ:byte */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum VC_VOICE_MSG_ID_ENUM
{
    /*  ARM->HIFI */
    ID_VC_VOICE_BASE            = 0x9400,
    ID_VC_VOICE_START_REQ       = 0x9402,       /*������������*/                /* _H2ASN_MsgChoice VCVOICE_START_REQ_STRU */
    ID_VC_VOICE_STOP_REQ        = 0x9403,       /*�������ֹͣ����*/            /* _H2ASN_MsgChoice VCVOICE_STOP_REQ_STRU */
    ID_VC_VOICE_SET_DEVICE_REQ  = 0x9404,       /*���������������*/            /* _H2ASN_MsgChoice VCVOICE_SET_DEVICE_REQ_STRU */
    ID_VC_VOICE_SET_VOLUME_REQ  = 0x9405,       /*���������������*/            /* _H2ASN_MsgChoice VCVOICE_SET_VOLUME_REQ_STRU */
    ID_VC_VOICE_SET_CODEC_REQ   = 0x9407,       /*������Դ��������*/          /* _H2ASN_MsgChoice VCVOICE_SET_CODEC_REQ_STRU */
    ID_VC_VOICE_FOREGROUND_REQ  = 0x940A,       /*����Ϊǰ̨ͨ·*/              /* _H2ASN_MsgChoice VCVOICE_FOREGROUND_REQ_STRU */
    ID_VC_VOICE_BACKGROUND_REQ  = 0x940B,       /*����Ϊ��̨ͨ·*/              /* _H2ASN_MsgChoice VCVOICE_BACKGROUND_REQ_STRU */
    ID_VC_VOICE_GROUND_QRY      = 0x940C,       /*��ѯͨ·״̬ */               /* _H2ASN_MsgChoice VCVOICE_GROUND_QRY_STRU */
    ID_VC_VOICE_LOOP_REQ        = 0x940D,       /* ���û��� */                  /* _H2ASN_MsgChoice VCVOICE_LOOP_REQ_STRU */
    ID_VC_VOICE_SET_MSD_REQ             = 0x940E,       /*ECAL���ݲ�������*/            /* _H2ASN_MsgChoice VCVOICE_SET_MSD_REQ_STRU */
    ID_VC_VOICE_SET_ECALLCFG_REQ        = 0x940F,       /*ECAL���ò�������*/            /* _H2ASN_MsgChoice VCVOICE_SET_ECALLCFG_REQ_STRU */
    ID_VC_VOICE_SO_CTRL_ORDER_IND   = 0x9415,       /*CDMA�¿���SO��״̬������*/    /* _H2ASN_MsgChoice VCVOICE_SO_CTRL_ORDER_IND_STRU */
    ID_VC_VOICE_SO_CTRL_MSG_IND     = 0x9416,       /*CDMA�¿���SO��״̬������*/    /* _H2ASN_MsgChoice VCVOICE_SO_CTRL_MSG_IND_STRU */
//    ID_VC_VOICE_SO_CTRL_SEND_SPECIAL_PACKETS = 0x9417,  /*VC����conversation״̬����Ҫ�������������������ýӿڴ������ཻ����ȷ��*/
    ID_VC_VOICE_SET_TTYMODE_IND = 0x9440,       /* ͨ��������֪ͨVOICE�µ�TTYģʽ */    /* _H2ASN_MsgChoice VCVOICE_SET_TTYMODE_IND_STRU */

    /*  HIFI->ARM */
    ID_VOICE_VC_BASE            = 0x4900,
    ID_VOICE_VC_START_CNF       = 0x4902,       /*��ӦVC_VOICE_START_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_CNF        = 0x4903,       /*��ӦVC_VOICE_STOP_REQ*/       /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_DEVICE_CNF  = 0x4904,       /*��ӦVC_VOICE_SET_DEVICE_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_VOLUME_CNF  = 0x4905,       /*��ӦVC_VOICE_SET_VOLUME_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_CODEC_CNF   = 0x4907,       /*��ӦVC_VOICE_SET_CODEC_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_FOREGROUND_CNF  = 0x490A,       /*��ӦVC_VOICE_FOREGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_BACKGROUND_CNF  = 0x490B,       /*��ӦVC_VOICE_BACKGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_GROUND_RSP      = 0x490C,       /*��ӦVC_VOICE_GROUND_QRY*/     /* _H2ASN_MsgChoice VCVOICE_GROUND_RSP_STRU */
    ID_VOICE_VC_LOOP_CNF        = 0x490D,       /* ���û�����Ӧ */              /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_ECALLCFG_CNF        = 0x490F,      /*��ӦID_VC_VOICE_SET_ECALLCFG_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_ECALL_TRANS_STATUS_NTF  = 0x4910,      /*�ظ�ECALL����״̬*/           /* _H2ASN_MsgChoice VCVOICE_ECALL_TRANS_STATUS_NTF_STRU */
    ID_VOICE_VC_START_SEND_MSD_IND      = 0x4930,      /*Ҫ��NAS���·���MSD����*/           /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */

    ID_VOICE_VC_DTMF_IND                = 0x4911,       /* �����ϱ�DTMF�������� */              /* _H2ASN_MsgChoice VOICEVC_DTMF_IND_STRU */
    ID_VOICE_VC_AL_ACK_REPORT_IND       = 0x4914,

    /* CODEC->CODEC */
    ID_VOICE_VOICE_ECALL_UPDATE_IND     = 0xDD0A,      /*Ecall���ݸ���*/                     /* _H2ASN_MsgChoice VOICE_VOICE_ECALL_UPDATE_IND_STRU */
    ID_VOICE_VOICE_ECALL_PULLSTART_IND  = 0xDD0B,      /*Ecallʹ�þɵ�Ecall��������MSD����*/ /* _H2ASN_MsgChoice VOICE_VOICE_ECALL_PULLSTART_IND_STRU */

    VC_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 VC_VOICE_MSG_ID_ENUM_UINT16;


enum VC_VOICE_DTMF_MSG_ID_ENUM
{
    ID_VC_VOICE_DTMF_BASE               = 0x9420,
    ID_VC_VOICE_START_DTMF_REQ          = 0x9421,       /* VC֪ͨVOICE��ʼDTMF���ͺͲ��� */ /* _H2ASN_MsgChoice VCVOICE_START_DTMF_REQ_STRU */
    ID_VOICE_VC_START_DTMF_CNF          = 0x4921,       /* ��ӦVC_VOICE_START_DTMF_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_DTMF_OVER_IND           = 0x4922,       /* VOICE֪ͨVC�����DTMF���뷢��*/    /* _H2ASN_MsgChoice VOICEVC_DTMF_OVER_IND_STRU */
    ID_VC_VOICE_STOP_DTMF_REQ           = 0x9423,       /* VC֪ͨVOICE�ж�DTMF���ͺͲ���*/    /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_DTMF_CNF           = 0x4923,       /* ��ӦID_VC_VOICE_STOP_DTMF_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VC_VOICE_SET_DTMF_DETECT_REQ     = 0x9424,       /* ��ӦID_VC_VOICE_SET_DTMF_DETECT_REQ*/  /* _H2ASN_MsgChoice VC_VOICE_DTMF_DETECT_REQ_STRU */
    ID_VOICE_VC_SET_DTMF_DETECT_CNF     = 0x4924,       /* ��ӦID_VOICE_VC_SET_DTMF_DETECT_CNF*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VC_VOICE_DTMF_MSG_ID_MAX,
};
typedef VOS_UINT16 VC_VOICE_DTMF_MSG_ID_ENUM_UINT16;


enum VCVOICE_NET_MODE_ENUM
{
    VCVOICE_NET_MODE_GSM         = 0,
    VCVOICE_NET_MODE_WCDMA,
    VCVOICE_NET_MODE_TDSCDMA,
    VCVOICE_NET_MODE_IMS_EUTRAN,
    VCVOICE_NET_MODE_CDMA,
    VCVOICE_NET_MODE_WIFI,
    VCVOICE_NET_MODE_BUTT
};
typedef VOS_UINT16 VCVOICE_NET_MODE_ENUM_UINT16;

enum VCVOICE_TYPE_ENUM
{
    VCVOICE_TYPE_AMR      = 0,                                                  /* amr */
    VCVOICE_TYPE_EFR,                                                           /* enhanced full rate */
    VCVOICE_TYPE_FR,                                                            /* full rate */
    VCVOICE_TYPE_HR,                                                            /* half rate */
    VCVOICE_TYPE_AMR2,                                                          /* amr2 */
    VCVOICE_TYPE_AMRWB,                                                         /* AMR-WB */
    VCVOICE_TYPE_G711,                                                          /* G711 */
    VCVOICE_TYPE_EVRC,                                                          /* EVRC */
    VCVOICE_TYPE_EVRCB,                                                         /* EVRCB */
    VCVOICE_TYPE_BUTT                                                           /* invalid value */
};
typedef VOS_UINT16  VCVOICE_TYPE_ENUM_UINT16;

enum VCVOICE_EXECUTE_RSLT_ENUM
{
    VCVOICE_EXECUTE_RSLT_SUCC = 0,                                              /* 0 �ɹ� */
    VCVOICE_EXECUTE_RSLT_FAIL,                                                  /* 1 ʧ�� */
    VCVOICE_EXECUTE_RSLT_NULL_PTR,                                              /* 2 ��ָ�� */
    VCVOICE_EXECUTE_RSLT_PARA_ERR,                                              /* 3 �������� */
    VCVOICE_EXECUTE_RSLT_STATE_ERR,                                             /* 4 ״̬���� */
    VCVOICE_EXECUTE_RSLT_UNKNOWN_MSG,                                           /* 5 δ֪��Ϣ */

    VCVOICE_EXECUTE_RSLT_BUTT
};
typedef VOS_UINT16  VCVOICE_EXECUTE_RSLT_ENUM_UINT16;

enum VCVOICE_VOLUME_TARGET_ENUM
{
    VCVOICE_VOLUME_TARGET_UP = 0,                                               /* 0 ���� */
    VCVOICE_VOLUME_TARGET_DOWN,                                                 /* 1 ���� */

    VCVOICE_VOLUME_TARGET_BUTT
};
typedef VOS_UINT16  VCVOICE_VOLUME_TARGET_ENUM_UINT16;

enum VCVOICE_WORK_TYPE_ENUM
{
    VCVOICE_WORK_TYPE_NORMAL = 0,                                               /* 0 ��������ģʽ */
    VCVOICE_WORK_TYPE_TEST,                                                     /* 1 ����ģʽ */
    VCVOICE_WORK_TYPE_ECALL,                                                    /* 2 ECALLģʽ */
    VCVOICE_WORK_TYPE_TTY_FULL,                                                 /* 3 TTY FULLģʽ */
    VCVOICE_WORK_TYPE_TTY_VCO,                                                  /* 4 TTY VCOģʽ */
    VCVOICE_WORK_TYPE_TTY_HCO,                                                  /* 5 TTY HCOģʽ */
    VCVOICE_WORK_TYPE_BUTT
};
typedef VOS_UINT16  VCVOICE_WORK_TYPE_ENUM_UINT16;

/* ͨ��ģʽö�� */
enum VCVOICE_DEV_MODE_ENUM
{
    VCVOICE_DEV_MODE_HANDSET                = 0,                                /* �ֳ�ģʽ */
    VCVOICE_DEV_MODE_HANDFREE,                                                  /* ����ģʽ */
    VCVOICE_DEV_MODE_CARFREE,                                                   /* ��������ģʽ */
    VCVOICE_DEV_MODE_HEADSET,                                                   /* ����ģʽ */
    VCVOICE_DEV_MODE_BLUETOOTH,                                                 /* ����ģʽ */
    VCVOICE_DEV_MODE_PCVOICE,                                                   /* PC-VOICEģʽ */
    VCVOICE_DEV_MODE_HEADPHONE,                                                 /* ��������MIC�Ķ���ͨ�� */
    VCVOICE_DEV_MODE_SUPER_HANDFREE,                                            /* �������� */
    VCVOICE_DEV_MODE_SMART_TALK,                                                /* ����ͨ�� */
    VCVOICE_DEV_MODE_USBVOICE,
    VCVOICE_DEV_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_DEV_MODE_ENUM_UINT16;

/* ͨ·״̬ */
enum VCVOICE_GROUND_ENUM
{
    VCVOICE_GROUND_FOREGROUND               = 0,                                /* ǰ̨ģʽ */
    VCVOICE_GROUND_BACKGROUND,                                                  /* ��̨ģʽ */
    VCVOICE_GROUND_INVALID,                                                     /* �Ƿ� */
    VCVOICE_GROUND_BUTT
};
typedef VOS_UINT16  VCVOICE_GROUND_ENUM_UINT16;

/* ����״̬ */
enum VCVOICE_LOOP_ENUM
{
    VCVOICE_LOOP_STOP                       = 0,                                /* �˳�����ģʽ */
    VCVOICE_LOOP_START,                                                         /* ���뻷��ģʽ */
    VCVOICE_LOOP_BUTT
};
typedef VOS_UINT16  VCVOICE_LOOP_ENUM_UINT16;

enum VCVOICE_ECALL_TRANS_STATUS_ENUM
{
    VCVOICE_ECALL_MSD_TRANSMITTING_START,                                      /* ��ǰMSD�����Ѿ���ʼ���� */
    VCVOICE_ECALL_MSD_TRANSMITTING_SUCCESS,                                    /* ��ǰMSD�����Ѿ����ͳɹ� */
    VCVOICE_ECALL_MSD_TRANSMITTING_FAIL,                                       /* ��ǰMSD�����Ѿ�����ʧ�� */
    VCVOICE_ECALL_PSAP_MSD_REQUIRETRANSMITTING,                                /* PSAPҪ�����MSD���� */
    VCVOICE_ECALL_MSD_TRANSMITTING_STOP,                                       /* ��ǰMSD�����Ѿ�ֹͣ���� */
    VCVOICE_ECALL_TRANS_STATUS_BUTT
};
typedef VOS_UINT8  VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8;

enum VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM
{
    VCVOICE_ECALL_CAUSE_WAIT_PSAP_TIME_OUT,                                    /* �ȴ�PSAP�Ĵ���ָʾ��ʱ */
    VCVOICE_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT,                             /* MSD���ݴ��䳬ʱ */
    VCVOICE_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT,                                  /* �ȴ�Ӧ�ò��ȷ�ϳ�ʱ */
    VCVOICE_ECALL_CAUSE_UNSPECIFIC_ERROR,                                      /* �����쳣���� */
    VCVOICE_ECALL_CAUSE_BUTT
};
typedef VOS_UINT8  VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8;

enum VCVOICE_ECALL_MSD_MODE_ENUM
{
    VCVOICE_ECALL_MSD_MODE_TRANSPARENT,                                         /* MSD����Ϊ͸��ģʽ*/
    VCVOICE_ECALL_MSD_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_ECALL_MSD_MODE_ENUM_UINT16;

enum VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM
{
    VCVOICE_ECALL_MSD_VOICE_NOT_ABANDON,                                        /* MSD���ݴ�����̴���ʾ��*/
    VCVOICE_ECALL_MSD_VOICE_ABANDON,                                            /* MSD���ݴ�����̲�����ʾ��*/
    VCVOICE_ECALL_MSD_VOICE_BUTT
};
typedef VOS_UINT16  VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16;

/* CDMA��ƽ�����ʿ���ö�٣�ORDQֵ��ǰ3��bit */
enum VCVOICE_ORDQ_3MSBS_ENUM
{
    VCVOICE_ORDQ_ZERO = 0,                              /* ���������ʴ��� */
    VCVOICE_ORDQ_FOURTH,                                /* �����ŵ�4���������У����һ������Ϊ������ */
    VCVOICE_ORDQ_HALF,                                  /* �����ŵ�2���������У���һ������Ϊ������ */
    VCVOICE_ORDQ_THREE_FOURTHS,                         /* �����ŵ�4���������У���3������Ϊ������ */
    VCVOICE_ORDQ_FULL,                                  /* �����ŵ�һ����������Ϊ������*/
    VCVOICE_ORDQ_BUTT
};
typedef VOS_UINT8 VCVOICE_ORDQ_3MSBS_ENUM_UINT8;

/* CDMA��ƽ�����ʿ���ö�� */
enum VCVOICE_EVRC_RATE_REDUC_ENUM
{
    VCVOICE_EVRC_RATE_REDUC_ZERO = 0,                   /* ���������ʴ��� */
    VCVOICE_EVRC_RATE_REDUC_FOURTH,                     /* �����ŵ�4���������У����һ������Ϊ������ */
    VCVOICE_EVRC_RATE_REDUC_HALF,                       /* �����ŵ�2���������У���һ������Ϊ������ */
    VCVOICE_EVRC_RATE_REDUC_THREE_FOURTHS,              /* �����ŵ�4���������У���3������Ϊ������ */
    VCVOICE_EVRC_RATE_REDUC_FULL,                       /* �����ŵ�һ����������Ϊ������*/
    VCVOICE_EVRC_RATE_REDUC_BUTT
};
typedef VOS_UINT8 VCVOICE_EVRC_RATE_REDUC_ENUM_UINT8;

/* CDMA��ƽ�����ʿ���ö�� */
enum VCVOICE_EVRCB_RATE_REDUC_ENUM
{
    VCVOICE_EVRCB_RATE_REDUC_830K = 0,                  /* ������Ϊ8.3kbps */
    VCVOICE_EVRCB_RATE_REDUC_757K = 1,
    VCVOICE_EVRCB_RATE_REDUC_664K = 2,
    VCVOICE_EVRCB_RATE_REDUC_618K = 3,
    VCVOICE_EVRCB_RATE_REDUC_582K = 4,
    VCVOICE_EVRCB_RATE_REDUC_545K = 5,
    VCVOICE_EVRCB_RATE_REDUC_508K = 6,
    VCVOICE_EVRCB_RATE_REDUC_400K = 7,
    VCVOICE_EVRCB_RATE_REDUC_BUTT
};
typedef VOS_UINT8 VCVOICE_EVRCB_RATE_REDUC_ENUM_UINT8;

enum VCVOICE_MOBILE_TO_MOBILE_ENUM
{
    VCVOICE_MOBILE_TO_MOBILE_OFF = 0,
    VCVOICE_MOBILE_TO_MOBILE_ON  = 1,                   /* ֵΪ1����Ҫ�������������ͣ1s */
    VCVOICE_MOBILE_TO_MOBILE_BUTT
};
typedef VOS_UINT8 VCVOICE_MOBILE_TO_MOBILE_ENUM_UINT8;

enum VCVOICE_INTI_CODEC_ENUM
{
    VCVOICE_INTI_CODEC_DISABLE = 0,
    VCVOICE_INTI_CODEC_ENABLE  = 1,                     /* ֵΪ1�����³�ʼ�������� */
    VCVOICE_INTI_CODEC_BUTT
};
typedef VOS_UINT8 VCVOICE_INTI_CODEC_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : VCCODEC_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* ͨѶ������ʽ��0 G��1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* ���������0 AMR��1 EFR��2 FR��3 HR��4 AMR2�� 5 AMRWB */
    VCVOICE_WORK_TYPE_ENUM_UINT16       enWorkType;                             /* ����ģʽ:0 ��������ģʽ 1: ����ģʽ */
    VOS_UINT16                          usReserve2;                             /* ���� */
}VCVOICE_START_REQ_STRU;


/*****************************************************************************
 �ṹ��    : VCCODEC_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ����������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
}VCVOICE_STOP_REQ_STRU;


/*****************************************************************************
 �ṹ��    : VCVOICE_SET_DEVICE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����豸�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_DEV_MODE_ENUM_UINT16        usDeviceMode;                           /* �����豸��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ������ 5 PC-VOICE  */
    VOS_UINT16                          usReserve2;                             /* ���� */
}VCVOICE_SET_DEVICE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCCODEC_SET_VOLUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������������������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_VOLUME_TARGET_ENUM_UINT16   enVolTarget;
    VOS_INT16                           sVolValue;
}VCVOICE_SET_VOLUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCCODEC_SET_CODEC_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������Դ��������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* ͨѶ������ʽ��0 G��1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* ���������0 AMR��1 EFR��2 FR��3 HR; 4 AMR2; 5 AMRWB */
}VCVOICE_SET_CODEC_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_FOREGROUND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VCģ������MED����·�绰����, ������������������ָ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VCVOICE_FOREGROUND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_BACKGROUND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VCģ������MED����·�绰ȥ������н����˾���״̬�����е��������ͨ·�Ͽ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VCVOICE_BACKGROUND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_GROUND_QRY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VCģ���ѯ��ǰͨ·״̬(ǰ̨/��̨)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VCVOICE_GROUND_QRY_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_GROUND_RSP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ظ���ǰͨ·״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_GROUND_ENUM_UINT16          enState;                                /* ��ǰ״̬ */
    VOS_UINT16                          usReserve2;                             /* ���� */
} VCVOICE_GROUND_RSP_STRU;

/*****************************************************************************
 �ṹ��    : VCCODEC_OP_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��VC��Ϣ������Ӧ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt;                              /* ִ�н�� */
    VOS_UINT16                          usReserve2;
}VCVOICE_OP_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_LOOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    VCVOICE_LOOP_ENUM_UINT16            enMode;                                 /* ��ǰ״̬ */
    VOS_UINT16                          usReserve2;
}VCVOICE_LOOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VOICEVC_DTMF_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������������ϱ�DTMF�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usDtmfCode;                             /* DTMF����ֵ */
} VOICEVC_DTMF_IND_STRU;

/*****************************************************************************
 �ṹ��    : VC_VOICE_DTMF_DETECT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������������ϱ�DTMF���ʹ������
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16 usMessageId;
    VOS_UINT16 usReserve;
    VOS_UINT32 ulDtmfDetectOn;  /*0 off, 1 on */
}VC_VOICE_DTMF_DETECT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_ECALL_TRANS_STATUS_NTF_STRU
 �ṹ˵��  : MEDģ��֪ͨVC����ǰ�Ĵ���״̬
 1.��    ��   : 2014��3��23��
   ��    ��   : y00241934
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ���� */
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus ;            /* ��ǰ�Ĵ���״̬ */
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause ;         /* ECALL�Ĵ���ʧ��ԭ�� */
    VOS_UINT16                                  usReserve2;                     /* ���� */
    VOS_UINT32                                  ulTimeWindow;                   /* ������ʱ�䴰 */
}VCVOICE_ECALL_TRANS_STATUS_NTF_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_SET_MSD_REQ_STRU
 �ṹ˵��  : VCģ��ͨ������Ϣ����MSD���ݷ��͵�MED
 1.��    ��   : 2014��3��23��
   ��    ��   : y00241934
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ���� */
    VOS_UINT32                                  ulMsdLen ;                      /* MSD���ݵĳ��� */
    VOS_UINT8                                   aucMsd[VC_VOICE_MAX_MSD_LEN];   /* MSD�������� */
} VCVOICE_SET_MSD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_SET_ECALLCFG_REQ_STRU
 �ṹ˵��  : VCģ��ͨ������Ϣ����ECALL���÷��͵�MED
 1.��    ��   : 2014��3��24��
   ��    ��   : y00241934
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ���� */
    VCVOICE_ECALL_MSD_MODE_ENUM_UINT16          enMsdMode;                      /* �����ȡMSD����ģʽ 0:͸�� */
    VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16 enNoVoice;                      /* MSD���ݴ���������Ƿ����������� 0:������ 1:������ */
} VCVOICE_SET_ECALLCFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VOICE_VOICE_ECALL_UPDATE_IND_STRU
 �ṹ˵��  : ECALL״̬����
 1.��    ��   : 2014��3��23��
   ��    ��   : y00241934
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ���� */
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus ;            /* ��ǰ�Ĵ���״̬ */
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause ;         /* ECALL�Ĵ���ʧ��ԭ�� */
    VOS_UINT8                                   aucReserve2[2];                 /* ���� */
}VOICE_VOICE_ECALL_UPDATE_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_VOICE_ECALL_PULLSTART_IND_STRU
 ��������  : ʹ��ԭ��MSD��������eCall
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved;
}VOICE_VOICE_ECALL_PULLSTART_IND_STRU;

/*****************************************************************************
 �ṹ��    : VOICEVC_AL_ACK_REPORT_IND_STRU
 �ṹ˵��  : ECALL AL ACK�ϱ�
 1.��    ��   : 2014��3��23��
   ��    ��   : y00241934
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* ���� */
    VOS_UINT32                                  ulTimeStamp;
    VOS_UINT8                                   ucAlAckValue;
    VOS_UINT8                                   aucReserve2[3];
} VOICEVC_AL_ACK_REPORT_IND_STRU;


/*****************************************************************************
 �ṹ��    : VCVOICE_SO_CTRL_ORDER_IND_STRU
 Э����  : Э��C.S0014-D_v3.0_EVRC   2.2.2.1 С��
 ASN.1���� :
 �ṹ˵��  : VC�յ��տ���ϢService Option Control Orders,
             ��Ҫ֪ͨVOICE��ʼ�����������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;                                  /* ԭ������ */ /*_H2ASN_Skip*/
    VCVOICE_TYPE_ENUM_UINT16        enCodecType;
    VOS_UINT8                       ucORDQ;
    VOS_UINT8                       ucReserve[3];                               /* ���� */
}VCVOICE_SO_CTRL_ORDER_IND_STRU;

/*****************************************************************************
 �ṹ��    : SO_CTRL_MSG_CODEC_STRU
 Э����  : Э��C.S0014-D_v3.0_EVRC   2.2.2.2С�ں�2.4.1.2С��
 ASN.1���� :
 �ṹ˵��  :  �տ���ϢService Option Control Messages�������Ŀ��ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                  ucRateReduc;          /* ���ʿ��ƣ�EVRC:ֵΪ0~4    EVRCB:ֵΪ0~7 */
    VOS_UINT8                                  ucReserved;           /**/
    VCVOICE_MOBILE_TO_MOBILE_ENUM_UINT8        ucMobileToMobile;     /* ֵΪ1ʱ����Ҫ����������ʼ��������������ͣ1s*/
    VCVOICE_INTI_CODEC_ENUM_UINT8              ucInitCodec;          /* ��ʼ����������־λ */
}SO_CTRL_MSG_CODEC_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_SO_CTRL_MSG_IND_STRU
 Э����  : Э��C.S0014-D_v3.0_EVRC   2.2.2.2С�ں�2.4.1.2С��
 ASN.1���� :
 �ṹ˵��  :  VC�յ��տ���ϢService Option Control Messages, ��Ҫ֪ͨ
              VOICE��ʼ�����������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;                                  /* ԭ������ */ /*_H2ASN_Skip*/
    VCVOICE_TYPE_ENUM_UINT16        enCodecType;
    SO_CTRL_MSG_CODEC_STRU          stSoCtrlMsg;
}VCVOICE_SO_CTRL_MSG_IND_STRU;

/*****************************************************************************
 �ṹ��    : VC_VOICE_START_DTMF_REQ_STRU
 ASN.1���� :
 �ṹ˵��  : VC֪ͨVOICE��ʼDTMF���ͺͲ���
*****************************************************************************/
typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usDtmfCode;                     /*���͵�����*/
    VOS_UINT16                      usLocalPlayOn;                  /*�Ƿ�ͬʱ���б��ز���*/
    VOS_UINT16                      usInBand;                       /*�Ƿ���ڷ���*/
    VOS_UINT16                      usDtmfTimeOn;                   /*����ʱ������λ:ms*/
    VOS_UINT16                      usDtmfTimeOff;                  /*���ʱ������λ:ms*/
}VCVOICE_START_DTMF_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VOICEVC_STOP_DTMF_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VOICE֪ͨVC DTMF���뷢�ͺͲ������
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
    VOS_UINT32                      ulResult;  /*0 success, others error code */
}VOICEVC_STOP_DTMF_IND_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_STOP_DTMF_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VC֪ͨVOICE�ж�DTMF���ͺͲ���
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
}VCVOICE_STOP_DTMF_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VOICEVC_DTMF_OVER_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VOICE֪ͨVC�����DTMF���ͺͲ���
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
    VOS_UINT32                      ulResult;  /*0 success, others error code */
}VOICEVC_DTMF_OVER_IND_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_SET_TTYMODE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͨ��������VC֪ͨVOICE�µ�TTYģʽ
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VC_VOICE_MSG_ID_ENUM_UINT16     usMsgName;
    VOS_UINT16                      usReserved1;
    VCVOICE_WORK_TYPE_ENUM_UINT16   enWorkType;                                 /* TTYģʽ, 3: FULL 4: VCO 5: HCO*/
    VOS_UINT16                      usReserved2;
}VCVOICE_SET_TTYMODE_IND_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    VC_VOICE_MSG_ID_ENUM_UINT16         enMsgID;            /* _H2ASN_MsgChoice_Export VC_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          VC_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_VC_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_VC_TRACE_MSG_DATA               stMsgData;
}VoiceVcTrace_MSG;

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
