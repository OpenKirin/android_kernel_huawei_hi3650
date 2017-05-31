/******************************************************************************

                  ��Ȩ���� (C), 2013-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CodecNvInterface.h
  �� �� ��   : ����
  ��    ��   : w00164657
  ��������   : 2013��5��17��
  ����޸�   :
  ��������   : CODECģ��NV�ӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��17��
    ��    ��   : w00164657
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CODECNVINTERFACE_H__
#define __CODECNVINTERFACE_H__

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
/* ������ѧ����NV�������鵥��ID���鳤�� ��λ:int16 */
#define CODEC_PP_NV_ARRAY_ID_LEN  (200)

/* ������ѧ����NV��������ID����  */
#define CODEC_PP_NV_ARRAY_ID_NUM  (3)

/* ��Ƶ��ѧ����NV�������鵥��ID���鳤�� ��λ:int16 */
#define AUDIO_PP_NV_ARRAY_ID_LEN  (200)

/* ��Ƶ��ѧ����NV��������ID����  */
#define AUDIO_PP_NV_ARRAY_ID_NUM  (3)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 ʵ������  : PP_AUDIO_PCM_OMP_NV_STRU
 ��������  : Ƶ�첹��NV��ά���ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enPcmCompEnable;                        /* ������ ʹ�ܱ�־ */
    VOS_INT16                           shwCompGain;                            /* ������ ʩ�����棨���ƣ� */
    VOS_INT16                           shwM;                                   /* ������ �˲����ĳ��� */
    VOS_INT16                           shwReserved;
    VOS_INT16                           ashwCoef[128];                          /* �����˲����� */
} PP_AUDIO_PCM_COMP_NV_STRU;

/*****************************************************************************
 �ṹ��    : NB_MAXVOLLEVEL_NV_STRU
 �ṹ˵��  : NB_MaxVolLevel NV�ṹ��,ID en_NV_Item_MaxVolLevel 12298
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwNBMaxVolLevel;/*Range:[1,20]*/
}NB_MAXVOLLEVEL_NV_STRU;

/*****************************************************************************
 �ṹ��    : HEADSETPARA_AUDIO_NV_STRU
 �ṹ˵��  : HeadSetPara_Audio NV�ṹ��,ID en_NV_HeadSetPara_Audio 12299
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwDownLrOutvol;
    VOS_UINT32                   uwUpRinl2vol;
    VOS_UINT32                   uwUpRl2mnbst;
    VOS_UINT32                   uwFilter;
}HEADSETPARA_AUDIO_NV_STRU;

/*****************************************************************************
 �ṹ��    : CMR_NV_STRU
 �ṹ˵��  : CMR_NV_STRU NV�ṹ��,ID en_NV_CMR 12300
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwCmrEnable;
    VOS_UINT32                   uwCmrMinFerThrd;
    VOS_UINT32                   uwCmrMaxFerThrd;
}CMR_NV_STRU;

/*****************************************************************************
 �ṹ��    : HANDFREEPARA_AUDIO_NV_STRU
 �ṹ˵��  : HandFreePara_Audio NV�ṹ��,ID en_NV_HandFreePara_Audio 12301
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwDownLrOpgavol;
    VOS_UINT32                   uwDownSpkattn;
    VOS_UINT32                   uwDownSpkvol;
    VOS_UINT32                   uwDownDcgain;
    VOS_UINT32                   uwDownAcgain;
    VOS_UINT32                   uwUpLinl2vol;
    VOS_UINT32                   uwUpLl2mnbst;
    VOS_UINT32                   uwFilter;
}HANDFREEPARA_AUDIO_NV_STRU;

/*****************************************************************************
 �ṹ��    : RTP_NV_CFG_STRU
 �ṹ˵��  : RTP_NV_CFG_STRU NV�ṹ��,ID en_NV_Rtp_Cfg 12302
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uwRtpCheckNv;
    VOS_UINT16                   uwRtpKoreaNv;
}RTP_NV_CFG_STRU;

/*****************************************************************************
 �ṹ��    : ERRLOGENABLE_NV_STRU
 �ṹ˵��  : ErrLogEnable NV�ṹ��,ID en_NV_Item_ErrLog_Enable 12304
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwErrLogEnable;
}ERRLOGENABLE_NV_STRU;

/*****************************************************************************
 �ṹ��    : NV_MED_PARA_ERRLOG_STRU
 �ṹ˵��  : NV_MED_Para_ErrLog NV�ṹ��,ID en_NV_Item_ErrLog_DataStru 12305
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwMaxDmaMicReset;
    VOS_UINT16                   uhwMaxDmaSpkReset;
    VOS_UINT16                   uhwMaxDecIntLost;
    VOS_UINT16                   uhwMaxBbpDataNone;
    VOS_UINT16                   uhwMaxBbpDataBad;
    VOS_UINT16                   uhwMaxDecipherLost;
    VOS_UINT16                   uhwMaxBfiFrames;
    VOS_UINT16                   uhwMaxSidFrames;
    VOS_UINT16                   uhwMaxInterpolate;
    VOS_UINT16                   uhwMaxRingBufFull;
}NV_MED_PARA_ERRLOG_STRU;

/*****************************************************************************
 �ṹ��    : HOOKNV_STRU
 �ṹ˵��  : HookNv NV�ṹ��,ID en_NV_Item_Hook_Enable_Target 12306
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwHookEnable;
    VOS_UINT16                   uhwHookTarget;
}HOOKNV_STRU;

/*****************************************************************************
 �ṹ��    : WB_MAXVOLLEVEL_STRU
 �ṹ˵��  : WB_MaxVolLevel NV�ṹ��,ID en_NV_WB_MaxVolLevel 12317
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwWBMaxVolLevel;/*Range:[1,20]*/
}WB_MAXVOLLEVEL_STRU;

/*****************************************************************************
 �ṹ��    : NV_CLVL_VOLUM_STRU
 �ṹ˵��  : NV_CLVL_VOLUM NV�ṹ��,ID en_NV_CLVL_VOLUM 12323
*****************************************************************************/
typedef struct
{
    VOS_INT16                   shwHandSetVolValue;
    VOS_INT16                   shwHandFreeVolValue;
    VOS_INT16                   shwCarFreeVolValue;
    VOS_INT16                   shwEarphoneVolValue;
    VOS_INT16                   shwBlueToothVolValue;
    VOS_INT16                   shwPcVoiceVolValue;
    VOS_INT16                   shwRsv[10];
}NV_CLVL_VOLUM_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_VOICE_HOOK_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݹ�ȡ���ƽṹ��,ID en_NV_VoiceTraceCfg 12324 ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* ʹ���� */
    VOS_UINT16                          uhwTarget;/*Range:[0,2047]*/            /* ���������ϱ���ȡ�㣬��0-10λ��Ч����ЧֵΪ0-2047 */
}CODEC_VOICE_HOOK_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_LOOP_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���뻷�ؿ��ƽṹ��,ID en_NV_VoiceTraceCfg 12324 ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* ʹ���� */
    VOS_UINT16                          uhwType;/*Range:[0,2]*/                 /* ��������: 1. DMA���أ�2. ����ǰ���أ�3. ����󻷻� */
}CODEC_LOOP_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_ERRLOG_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Errlog���ƽṹ��,ID en_NV_VoiceTraceCfg 12324 ���
             ע�⣬����ɾ�ýṹ��������޵ĸ����������ݣ�����ͬ������:
             1. ö��CODEC_ERRLOG_EVENTS_ENUM
             2. ���޽ṹ��CODEC_ERRLOG_THD_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* ʹ���� */
    VOS_INT16                           shwReserved;                            /* ����λ */
    VOS_UINT16                          uhwMaxDmaMicReset;/*Range:[1,65535]*/   /* Mic DMA �������������� */
    VOS_UINT16                          uhwMaxDmaSpkReset;/*Range:[1,65535]*/   /* Spk DMA �������������� */
    VOS_UINT16                          uhwMaxDecIntLost;/*Range:[1,65535]*/    /* WCDMA �����ж϶�ʧ���� */
    VOS_UINT16                          uhwMaxBBPDataNone;/*Range:[1,65535]*/   /* WCDMA BBP �ϱ�����Ϊ�յ����� */
    VOS_UINT16                          uhwMaxBBPDataBad;/*Range:[1,65535]*/    /* WCDMA BBP �ϱ�����Ϊ��֡ */
    VOS_UINT16                          uhwMaxDecipherLost;/*Range:[1,65535]*/  /* WCDMA �������ж�ʧ���� */
    VOS_UINT16                          uhwMaxBFIFrames;/*Range:[1,65535]*/     /* GSM �յ� BFI ֡���� */
    VOS_UINT16                          uhwMaxSIDFrames;/*Range:[1,65535]*/     /* ����֡ΪSID ������ */
    VOS_UINT16                          uhwMaxInterpolate;/*Range:[1,65535]*/   /* PC Voice ��֡��Ŀ���� */
    VOS_UINT16                          uhwMaxRingBufFull;/*Range:[1,65535]*/   /* PC Voice Ring Buffer ���Ĵ������� */
}CODEC_ERRLOG_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_VOICE_TRACE_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����TRACE����NV��ṹ��,ID en_NV_VoiceTraceCfg 12324
*****************************************************************************/
typedef struct
{
    CODEC_VOICE_HOOK_CONFIG_STRU          stVoiceHookCfg;                       /* �������ݹ�ȡ���ƽṹ�� */
    CODEC_LOOP_CONFIG_STRU                stLoopCfg;                            /* ���뻷�ؿ��ƽṹ�� */
    CODEC_ERRLOG_CONFIG_STRU              stErrlogCfg;                          /* Errlog���ƽṹ�� */
}CODEC_NV_PARA_VOICE_TRACE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_LOG_HOOK_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��־��ȡ����,ID en_NV_HifiTraceCfg 12325 ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* ʹ���� */
    VOS_UINT16                          uhwLevel;/*Range:[0,2]*/                /* LOG�ϱ�����0. INFO����1. WARNING����2. ERROR���� */
}CODEC_LOG_HOOK_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_MSG_HOOK_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ��ȡ����,ID en_NV_HifiTraceCfg 12325 ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* ʹ���� */
    VOS_INT16                           shwReserved;                            /* ����λ */
}CODEC_MSG_HOOK_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_HIFI_TRACE_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HIFI TRACE����NV��ṹ��,ID en_NV_HifiTraceCfg 12325
*****************************************************************************/
typedef struct
{
    CODEC_LOG_HOOK_CONFIG_STRU            stLogHookCfg;                         /* �������ݹ�ȡ���ƽṹ�� */
    CODEC_MSG_HOOK_CONFIG_STRU            stMsgHookCfg;                         /* ���뻷�ؿ��ƽṹ�� */
}CODEC_NV_PARA_HIFI_TRACE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_SIO_VOICE_MASTER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : voice SIO��������NV��ṹ��,ID en_NV_Item_SIO_Voice_Master 12326
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwIsPcmMaster;/*Range:[0,1]*/         /* voice SIO�Ƿ�Ϊmasterģʽ */
}CODEC_NV_PARA_SIO_VOICE_MASTER_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_AUDIO_HOOK_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ƶ���ݹ�ȡ���ƽṹ�壬ID en_NV_AudioTraceCfg 12327���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;                              /* ʹ���� */
    VOS_UINT16                          uhwTarget;                              /* ��Ƶ�����ϱ���ȡ�㣬��0-10λ��Ч����ЧֵΪ0-2047 */
}CODEC_AUDIO_HOOK_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_AUDIO_TRACE_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ƵTRACE����NV��ṹ�壬ID ID en_NV_AudioTraceCfg 12327
*****************************************************************************/
typedef struct
{
    CODEC_AUDIO_HOOK_CONFIG_STRU          stAudioHookCfg;                         /* ��Ƶ���ݹ�ȡ���ƽṹ�� */
}CODEC_NV_PARA_AUDIO_TRACE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_SIO_AUDIO_MASTER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : audio SIO��������NV��ṹ��,ID en_NV_Item_SIO_Audio_Master 12328
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwIsPcmMaster;/*Range:[0,1]*/         /* audio SIO�Ƿ�Ϊmasterģʽ */
}CODEC_NV_PARA_SIO_AUDIO_MASTER_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_HIFI_POWEROFF_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HIFI�µ�ʹ��/�ر�����NV��ṹ��,ID en_NV_HifiPowerOffCfg 12333
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwPowerOffEnable;/*Range:[0,1]*/              /* HIFI�µ��Ƿ�ʹ�� */
    VOS_UINT16                   uhwRsv;
    VOS_UINT32                   uwWITimeThd;                                   /* ����͹���ģʽ������ʱ�� */
    VOS_UINT32                   uwPDTimeThd;                                   /* �µ�������ʱ�� */
}CODEC_NV_PARA_HIFI_POWEROFF_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_NV_PARA_HIFI_WATCHDOG_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HIFI Watchdog����NV��ṹ��,ID en_NV_HifiWatchDogCfg 12334
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwWDEnable;/*Range:[0,1]*/                    /* HIFI watchdog�Ƿ�ʹ�� */
    VOS_UINT16                   uhwRsv;
    VOS_UINT32                   uwWDTimeoutLen;                                /* HIFI watchdog timeout length */
}CODEC_NV_PARA_HIFI_WATCHDOG_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CODEC_PP_NV_STRU
 �ṹ˵��  : PPģ���ģʽID�ṹ��,ID 12335 - 12376
*****************************************************************************/
typedef struct
{
    VOS_INT16                      ashwNv[CODEC_PP_NV_ARRAY_ID_LEN];
}CODEC_PP_NV_STRU;

/*****************************************************************************
 �ṹ��    : PHY_MIC_NUM_NV_STRU
 �ṹ˵��  : en_NV_PHY_MIC_NUM NV�ṹ��,ID en_NV_PHY_MIC_NUM 12349
*****************************************************************************/
typedef struct
{
    VOS_INT16                         hwPhyMicNum;
    VOS_INT16                         hwReserv;
}PHY_MIC_NUM_NV_STRU;

/*****************************************************************************
 ʵ������  : VOICE_SMART_PA_CFG_STRU
 ��������  : Smart PA����ģ�飬������NV��ȡ,ID en_NV_SmartPACfg 12350
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enEnable;
    VOS_UINT16                          uhwIsMaster;
    VOS_UINT16                          uhwValidChannel;/*Range:[0,1]*/         /* 0��ʾ��������Ч��1��ʾ��������Ч */
    VOS_UINT16                          auhwReserve[3];
} VOICE_SMART_PA_CFG_NV_STRU;

/*****************************************************************************
 ʵ������  : PP_AUDIO_PCM_TxCOMP_NV_STRU
 ��������  : ����Ƶ�첹��NV��ά���ṹ��,ID en_NV_AudioTxCompCfg 12351
*****************************************************************************/
typedef struct
{
    PP_AUDIO_PCM_COMP_NV_STRU           stTxCompCfg;
} PP_AUDIO_PCM_TxCOMP_NV_STRU;

/*****************************************************************************
 ʵ������  : PP_AUDIO_PCM_RxCOMP_NV_STRU
 ��������  : ����Ƶ�첹��NV��ά���ṹ��,ID en_NV_AudioRxCompCfg 12352
*****************************************************************************/
typedef struct
{
    PP_AUDIO_PCM_COMP_NV_STRU           stRxCompCfg;
} PP_AUDIO_PCM_RxCOMP_NV_STRU;

/*****************************************************************************
 �ṹ��    : AUDIO_PP_NV_STRU
 �ṹ˵��  : PPģ���ģʽID�ṹ��,ID 12379 - 12384
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNv[AUDIO_PP_NV_ARRAY_ID_LEN];       /* ��ƵNV�� */
}AUDIO_PP_NV_STRU;

/*****************************************************************************
 �ṹ��    : EN_FORTE_DATA_STRU
 �ṹ˵��  : Forteʹ�õ�NV��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           usData[256];
} EN_FORTE_DATA_STRU;

/*****************************************************************************
 �ṹ��    : EN_OPENDSP_CONFIG_STRU
 �ṹ˵��  : OpenDSP������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucProfile;                              /* ����ѡ�� */
    VOS_UINT8                           ucReserve[3];
} EN_OPENDSP_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : EN_MBDRC_DATA_STRU
 �ṹ˵��  : �ýṹ���ڵ������㷨��MBDRCʹ�õ�NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           usData[2048];
} EN_MBDRC_DATA_STRU;

/*****************************************************************************
 �ṹ��    : DIAG_CHANNEL_QUALITY_STRU
 �ṹ˵��  : �ýṹ�����������ϼ��ģ�����жϵ�ǰС���źźû���NV��
*****************************************************************************/
typedef struct
{
    VOS_INT16               shwIsIgnoreChanQa;                                  /* ���ʱ�Ƿ�����źźû�״����0��ʾ���ǣ�1��ʾ���� */
    VOS_INT16               shwGsmChanQaThd;                                    /* GSM���ж�С���źźû�����ֵ */
    VOS_INT16               shwUmtsChanQaThd;                                   /* W���ж�С���źźû�����ֵ */
    VOS_INT16               shwTdChanQaThd;                                     /* Td���ж�С���źźû�����ֵ */
    VOS_INT16               shwImsChanQaThd;                                    /* IMS���ж�С���źźû�����ֵ */
}DIAG_CHANNEL_QUALITY_STRU;

/*****************************************************************************
 �ṹ��    : DIAG_LINEIN_STRU
 �ṹ˵��  : �ýṹ���ڼ��LineIn���������ϵ�NV��
*****************************************************************************/
typedef struct
{
    VOS_INT16               shwDiagTime ;                                       /* ͳ��ʱ�䣬��λ(s) */
    VOS_INT16               shwGoodFrmPercentThd;                               /* Q15 (0.8*32767) */
    VOS_INT16               ahwReserve[8];
}DIAG_LINEIN_STRU;

/*****************************************************************************
 �ṹ��    : VOICE_DIAG_NV_STRU
 �ṹ˵��  : �ýṹ�����������ϼ��ģ���NV��
*****************************************************************************/
typedef struct
{
    VOS_INT16                 shwEnable;                                        /* ÿһ��bitλ����һ������ */
    DIAG_CHANNEL_QUALITY_STRU stChanQaPara;
    DIAG_LINEIN_STRU          stLineInPara;
    VOS_INT16                 ashwLineOut[10];
    VOS_INT16                 ashwCodecIn[10];
    VOS_INT16                 ashwCodecOut[10];
    VOS_INT16                 ashwMicIn[10];
    VOS_INT16                 ashwSpeakOut[10];
    VOS_INT16                 ashwAecIn[10];
    VOS_INT16                 ashwAecRef[10];
    VOS_INT16                 ashwReserve[170];
} VOICE_DIAG_NV_STRU;

/*****************************************************************************
 �ṹ��    : VOICE_JB_NV_STRU
 �ṹ˵��  : �ýṹ���ڿ���JB�����ã���ǰ��Ҫ�õ�һ�������������Ƿ�ʹ��AJB
*****************************************************************************/
typedef struct
{
    VOS_UINT16                 uhwAjbEnable;                                     /* �Ƿ�ʹ��AJB,0/1:��/�� */
    VOS_UINT16                 uhwInitBuf;                                       /* ��ʼ���,��λms	*/
    VOS_UINT16                 uhwAjbMinBuf;                                     /* ��С���,��λms */
    VOS_UINT16                 uhwAjbMaxBuf;                                     /* ������,��λms */
    VOS_UINT16                 auhwReserve[12];
} VOICE_JB_NV_STRU;

/*****************************************************************************
 �ṹ��    : DTMF_GEN_CHAN_PARAM_STRU
 �ṹ˵��  : DTMF�����㷨ģ��ĳ�ʼ���������ֵ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                uhwTimeOn;        /* ������Ч����ʱ�� */
    VOS_UINT16                usTimeOff;        /* ���뾲�����ʱ�� */
    VOS_INT16                 shwHFreqLvl;      /* ��Ƶ��ƽ����λ��dBm��*/
    VOS_INT16                 shwLFreqLvl;      /* ��Ƶ��ƽ����λ��dBm��*/
    VOS_UINT16                uhwFrmLen;        /* ������֡ʱ�� */
    VOS_UINT16                uhwReserve;
    VOS_UINT32                uwReserve;
}DTMF_GEN_CHAN_PARAM_STRU;

/*****************************************************************************
 �ṹ��    : DTMF_GEN_PARAM_STRU
 �ṹ˵��  : DTMF����ģ��ʹ�õ�NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                uhwEnable;         /* DTMF����ģ��ʹ�ܿ��� */
    VOS_UINT16                uhwReserve;
    DTMF_GEN_CHAN_PARAM_STRU  stGenChanPara;
}DTMF_GEN_PARAM_STRU;

/****************************************************************************
 �ṹ��    : DTMF_GEN_PARAM_STRU
 �ṹ˵��  : DTMF����ģ���׼�����ò����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                uhwStandard;       /*(0:���� / ��0:����ITU-T Q.24)*/
    VOS_UINT16                uhwTlkOffLvl;      /*(�������ȼ�:0~3, ���ڵ���4ȡȱʡ�ȼ�0)*/
}DTMF_DET_STD_CFG_STRU;

/*****************************************************************************
 �ṹ��    : DTMF_DET_BASIC_STRU
 �ṹ˵��  : DTMF���ģ���������ָ��NV��
*****************************************************************************/
typedef struct
{
    /* ��������ָ���� */
    VOS_INT16                 shwThrshLevlH;              /* ��Ƶ��ƽ���� */
    VOS_INT16                 shwThrshLevlL;              /* ��Ƶ��ƽ���� */
    VOS_UINT16                uhwONTime;                  /* �ɿ�����ONʱ�� */
    VOS_UINT16                uhwOFFTime;                 /* �ɿ�����OFFʱ�� */
    VOS_UINT16                uhwIntvlTime;               /* ������źż��ʱ�� */
    VOS_INT16                 shwTwistLevl;               /* ��ƽ������ */
    VOS_UINT16                uhwdeltaMust;               /* �ɿ�����Ƶƫ���� */
    VOS_UINT16                uhwdeltaReject;             /* �ܾ�����Ƶƫ���� */
    VOS_UINT16                uhwdeltaFactor;             /* Ƶƫ�о����λ�� */
    VOS_UINT16                uhwReserve;
}DTMF_DET_BASIC_STRU;

/*****************************************************************************
 �ṹ��    : DTMF_DET_TALKOFF_STRU
 �ṹ˵��  : DTMF���ģ�鿹��������ʹ�ܿ�����NV��
*****************************************************************************/
typedef struct
{
    /* ����������ʹ�ܿ����� */
    VOS_UINT16                uhwTalkoffSwitch;         /* �������ܿ��� */
    VOS_UINT16                uhwTDSwitch;              /* ʱ���ȶ��Կ��� */
    VOS_UINT16                uhwTwistDEVSwitch;        /* ��ƽ���ȶ��Կ��� */
    VOS_UINT16                uhwSNRSwitch;             /* ����ȿ��� */
    VOS_UINT16                uhwIntvlSwitch;           /* �źż��״̬ʶ�𿪹� */
    VOS_UINT16                uhwECSwitch;              /* EC״̬ʶ�𿪹� */
    VOS_UINT16                uhwLongTimSwitch;         /* ��ʱ�ź��о����� */

    /* ����Ȳ����� */
    VOS_UINT16                uhwSnrBotmK;              /* ���źŷ��ȱ仯����������ޱ������� */
    VOS_UINT16                uhwFreqSeg[5];            /* ����Ȼ���Ƶ�ʶ� */
    VOS_UINT16                uhwSNRSeg[6];             /*��ͬƵ�ʶε���������� */

    /* �ɳڵĹ���ָ���� */
    VOS_UINT16                uhwdeltaDialTone;         /* ������ʶ��Ƶƫ����Χ */
    VOS_UINT16                uhwdeltaRelax;            /* ���ɳڵ�Ƶƫ */
    VOS_UINT16                uhwLevlRelax;             /* ���ɳڵĵ�ƽ���� */
    VOS_UINT16                uhwTwistRelax;            /* ���ɳڵĵ�ƽ������ */

    VOS_INT16                 shwECTimConv;              /* EC����������֡�� */
    VOS_INT16                 shwlgONTime;               /* ��ʱ״̬ʱ������ */
    VOS_INT16                 shwTwistDEV;               /* ��ƽ���ȶ��Բ��� */
}DTMF_DET_TALKOFF_STRU;

/*****************************************************************************
 �ṹ��    : DTMF_DET_PARAM_STRU
 �ṹ˵��  : DTMF���ģ�����ò���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;                              /* DTMF���ģ��ʹ�ܿ��� */
    VOS_UINT16                          uhwParamFlag;                           /* ���ò������ͣ�0Ϊ��׼��1Ϊ�Զ��� */
    DTMF_DET_STD_CFG_STRU               stDetStdCfg;                            /* ������������� */
    DTMF_DET_BASIC_STRU                 stDetBasic;
    DTMF_DET_TALKOFF_STRU               stDetTalkOff;
}DTMF_DET_PARAM_STRU;

/*****************************************************************************
 �ṹ��    : VOICE_DTMF_CFG_NV_STRU
 �ṹ˵��  : DTMFģ��ʹ�õ�NV��
*****************************************************************************/
typedef struct
{
    DTMF_DET_PARAM_STRU                 stDetCfgPara;                           /* DTMF���ģ�����ò��� */
    DTMF_GEN_PARAM_STRU                 stGenCfgPara;                           /* DTMF����ģ�����ò��� */
    VOS_UINT16                          uhwReserve[4];
}VOICE_DTMF_CFG_NV_STRU;

/*****************************************************************************
  7 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

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

#endif /* end of CodecNvInterface.h */

