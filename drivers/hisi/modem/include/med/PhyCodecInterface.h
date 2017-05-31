

#ifndef __PHYCODECINTERFACE_H__
#define __PHYCODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CodecInterface.h"

/* _H2ASN_Include CODEC_ctrl_mc.h */
/* _H2ASN_Include codec_typedefine.h */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define GPHY_VOICE_DATA_LEN                                   (17)                /* G�������CODEC�������������ݳ���,��λ16Bit */
#define WPHY_VOICE_WCDMA_MAX_CELL_NUM                         (6)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum DSP_VOICE_MSG_ID_ENUM
{
    /*====== WPHY->CODEC ======*/
    ID_WPHY_VOICE_RX_DATA_IND                         = 0xBD01,                 /* W ��������ָʾ */             /* _H2ASN_MsgChoice WPHY_VOICE_RX_DATA_IND_STRU */
    ID_WPHY_VOICE_SYNC_IND                            = 0xBD02,                 /* W ͬ��ָʾ */                 /* _H2ASN_MsgChoice WPHY_VOICE_SYNC_IND_STRU */
    ID_WPHY_VOICE_BACKGROUND_CNF                      = 0xBD03,                 /* W �����ظ��ѽ��뾲Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_WPHY_VOICE_FOREGROUND_CNF                      = 0xBD04,                 /* W �����ظ����˳���Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_FOREGROUND_CNF_STRU */
    ID_WPHY_VOICE_CHANNEL_QUALITY_IND                 = 0xBD05,                 /* W ������ϱ��ŵ����������ں�̨��ά�ɲ� *//* _H2ASN_MsgChoice WPHY_VOICE_CHANNEL_QUALITY_IND_STRU */
    ID_WPHY_VOICE_BSD_CS_IND                          = 0xBD06,                 /* W �����ά����Ϣ����ΪBSD3.0�㷨������ */ /* _H2ASN_MsgChoice WPHY_VOICE_BSD_CS_IND_STRU */

    /*====== CODEC->WPHY ======*/
    ID_VOICE_WPHY_TX_DATA_IND                         = 0xDB01,                 /* W ���������� */             /* _H2ASN_MsgChoice VOICE_WPHY_TX_DATA_IND_STRU */
    ID_VOICE_WPHY_BACKGROUND_REQ                      = 0xDB03,                 /* W ֪ͨPHY���뾲Ĭ����ģʽ */  /* _H2ASN_MsgChoice VOICE_GUPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_WPHY_FOREGROUND_REQ                      = 0xDB04,                 /* W ֪ͨPHY�˳���Ĭ����ģʽ */  /* _H2ASN_MsgChoice VOICE_GUPHY_FOREGROUND_REQ_STRU */

    /*====== GPHY->CODEC ======*/
    ID_GPHY_VOICE_RX_DATA_IND                         = 0xCD01,                 /* GSM ��������ָʾ */           /* _H2ASN_MsgChoice GPHY_VOICE_RX_DATA_IND_STRU */
    ID_GPHY_VOICE_UPDATE_PARA_CMD                     = 0xCD02,                 /* GSM ��������������� */       /* _H2ASN_MsgChoice GPHY_VOICE_UPDATE_PARA_CMD_STRU */
    ID_GPHY_VOICE_PLAY_IND                            = 0xCD04,                 /* GSM ����������������ָʾ */   /* _H2ASN_MsgChoice GPHY_VOICE_PLAY_IND_STRU */
    ID_GPHY_VOICE_RECORD_IND                          = 0xCD05,                 /* GSM ���������ɼ�����ָʾ */   /* _H2ASN_MsgChoice GPHY_VOICE_RECORD_IND_STRU */
    ID_GPHY_VOICE_BACKGROUND_CNF                      = 0xCD07,                 /* G �����ظ��ѽ��뾲Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_GPHY_VOICE_FOREGROUND_CNF                      = 0xCD08,                 /* G �����ظ����˳���Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_FOREGROUND_CNF_STRU */
    ID_GPHY_VOICE_SYNC_IND                            = 0xCD10,                 /* G ͬ��ָʾ */                /* _H2ASN_MsgChoice GPHY_VOICE_SYNC_IND_STRU */
    ID_GPHY_VOICE_CHANNEL_QUALITY_IND                 = 0xCD11,                 /* G ������ŵ�������ά�ɲ� */ /* _H2ASN_MsgChoice GPHY_VOICE_CHANNEL_QUALITY_IND_STRU */
    ID_GPHY_VOICE_BSD_CS_IND                          = 0xCD12,                 /* G �����ά����Ϣ����ΪBSD3.0�㷨������ */ /* _H2ASN_MsgChoice GPHY_VOICE_BSD_CS_IND_STRU */
    ID_GPHY_VOICE_HO_START_REQ                        = 0xCD13,                 /* Ho�л���ʼ����MED�·���ʼ��Ϣ */ /* _H2ASN_MsgChoice GPHY_VOICE_HO_START_REQ_STRU */
    ID_GPHY_VOICE_HO_COMPLETE_REQ                     = 0xCD14,                 /* Ho�л���ɣ���MED�·������Ϣ */ /* _H2ASN_MsgChoice GPHY_VOICE_HO_Complete_REQ_STRU */

    /*====== CODEC->GPHY ======*/
    ID_VOICE_GPHY_TX_DATA_IND                         = 0xDC02,                 /* GSM ���������� */           /* _H2ASN_MsgChoice VOICE_GPHY_TX_DATA_IND_STRU */
    ID_VOICE_GPHY_SYNC_REQ                            = 0xDC03,                 /* GSM ����ʱ��ͬ������GPHY�յ�������ָʾ������ʼ�����������ɼ������� */ /* _H2ASN_MsgChoice VOICE_GPHY_SYNC_REQ_STRU */
    ID_VOICE_GPHY_PLAY_CNF                            = 0xDC04,                 /* GSM ����������������ȷ�� */   /* _H2ASN_MsgChoice VOICE_GPHY_PLAY_CNF_STRU */
    ID_VOICE_GPHY_RECORD_CNF                          = 0xDC05,                 /* GSM ����������������ȷ�� */   /* _H2ASN_MsgChoice VOICE_GPHY_RECORD_CNF_STRU */
    ID_VOICE_GPHY_SET_CODEC_IND                       = 0xDC06,                 /* GSM �������л�ָʾ */         /* _H2ASN_MsgChoice VOICE_GPHY_SET_CODEC_IND_STRU */
    ID_VOICE_GPHY_BACKGROUND_REQ                      = 0xDC07,                 /* GSM ֪ͨPHY���뾲Ĭ����ģʽ *//* _H2ASN_MsgChoice VOICE_GUPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_GPHY_FOREGROUND_REQ                      = 0xDC08,                 /* GSM ֪ͨPHY�˳���Ĭ����ģʽ *//* _H2ASN_MsgChoice VOICE_GUPHY_FOREGROUND_REQ_STRU */

    /*====== CODEC->CODEC ======*/
    ID_VOICE_VOICE_ENC_REQ                            = 0xDD03,                   /* G/U������Ϣ,������DMA�������ʱ���� */
    ID_VOICE_VOICE_RECORD_IND                         = 0xDD04,                   /* UMTS ����DMA����������Ϣ,��3ms��ʱ���ж��з��� */        /* _H2ASN_MsgChoice GPHY_VOICE_RECORD_IND_STRU */
    ID_VOICE_VOICE_PLAY_IND                           = 0xDD05,                   /* UMTS ������������,��6ms��ʱ���ж��з��� */               /* _H2ASN_MsgChoice GPHY_VOICE_PLAY_IND_STRU */
    ID_VOICE_VOICE_UPDATE_REQ                         = 0xDD07,                   /* ���������ͱ仯ʱ,�������������д��� */                   /* _H2ASN_Skip */
    ID_VOICE_VOICE_DEC_REQ                            = 0xDD08,                   /* G/U������Ϣ,������DMA�������ʱ���� */                   /* _H2ASN_Skip */
    ID_VOICE_VOICE_REMAP_IND                          = 0xDD0C,                   /* mmbuf������ɣ�֪ͨvoice remap */                       /* _H2ASN_Skip */
    ID_VOICE_VOICE_REQUEST_MMBUF_IND                  = 0xDD0D,                   /* voice remap��ɣ��ٴ�����mmbuf */                       /* _H2ASN_Skip */

    /*lwx26324 add @20140327 for external modem��begin*/
    ID_VOICEPP_VOICEPP_MICIN_IND                      = 0xDD10,                 /* micin loop dma start msg */  /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_LINEIN_IND                     = 0xDD11,                 /* linein loop dma start msg */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_SPKOUT_IND                     = 0xDD12,                 /* spkout loop dma start msg */  /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_LINEOUT_IND                    = 0xDD13,                 /* lineout loop dma start msg */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_PROC_IND                       = 0xDD14,                 /* �����������ݰ��� */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_RXPROC_IND                     = 0xDD15,                 /* ���������㷨���� */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_TXPROC_IND                     = 0xDD16,                 /* ���������㷨���� */ /* _H2ASN_Skip */
    /*lwx26324 add @20140327 for external modem��end*/ 

    /*====== UCOM->CODEC ======*/
    ID_UCOM_VOICE_SUSPEND_CMD                         = 0xCD09,                 /* ���������ͣ���ָ���Ϣ����G/U������ϵͳ�л������з��� */ /* _H2ASN_MsgChoice GUPHY_VOICE_SUSPEND_CMD_STRU */

    MSG_ID_BUTT                                                                  /* _H2ASN_Skip */
};
typedef VOS_UINT16 DSP_VOICE_MSG_ID_ENUM_UINT16;

enum RCM_VOICE_MSG_ID_ENUM
{
    /*====== CODEC->RCM ======*/
    ID_VOICE_RCM_CALL_STATE_IND         = 0xEF01,                               /* CODEC֪ͨRCM���뾲Ĭ����ģʽ��mode��modem */  /* _H2ASN_MsgChoice VOICE_RCM_CALL_STATE_IND_STRU */

    /*====== RCM->CODEC ======*/
    ID_RCM_VOICE_CALL_STATE_CNF         = 0xEF02,                               /* RCM�ظ�CODEC */ /* _H2ASN_MsgChoice RCM_VOICE_CALL_STATE_CNF_STRU */

    ID_RCM_VOICE_MSG_ID_ENUM_BUTT                                               /* _H2ASN_Skip */                                           
};
typedef VOS_UINT16 RCM_VOICE_MSG_ID_ENUM_UINT16;



/* PHY��MED����ȷ���гɹ���ʧ��ָʾö�� */
enum DSP_VOICE_RESULT_ENUM
{
    DSP_VOICE_RESULT_SUCC,
    DSP_VOICE_RESULT_FAIL,

    DSP_VOICE_RESULT_BUTT,
};
typedef VOS_UINT16 DSP_VOICE_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_VOICE_MODEM_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MODEM ID
*****************************************************************************/
enum RCM_VOICE_MODEM_ID_ENUM
{
    RCM_VOICE_MODEM_1                         = 0,                              /* MODEM0 */
    RCM_VOICE_MODEM_2                         = 1,                              /* MODEM1 */
    RCM_VOICE_MODEM_3                         = 2,                              /* MODEM2 */
    RCM_VOICE_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_VOICE_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_VOICE_CALL_STATE_ENUM_UINT16
 ö��˵��  : modem Background or Active Call״̬
             0:Active Call״̬
             1:Background Call״̬
*****************************************************************************/
enum RCM_VOICE_CALL_STATE_ENUM
{
    RCM_VOICE_CALL_ACTIVE           = 0,
    RCM_VOICE_CALL_BACKGROUND       = 1,
    RCM_VOICE_CALL_BUTT
};
typedef VOS_UINT16 RCM_VOICE_CALL_STATE_ENUM_UINT16;


/*****************************************************************************
 ö����    : GPHY_VOICE_CHANNEL_TYPE_ENUM_UINT16
 ö��˵��  : TCHҵ���ŵ�����
*****************************************************************************/
enum GPHY_VOICE_CHANNEL_TYPE_ENUM
{
    GPHY_VOICE_CHANNEL_TYPE_TCH_FS          = 0,
    GPHY_VOICE_CHANNEL_TYPE_TCH_EFS         = 1,
    GPHY_VOICE_CHANNEL_TYPE_TCH_HS          = 2,
    GPHY_VOICE_CHANNEL_TYPE_TCH_AFS         = 3,
    GPHY_VOICE_CHANNEL_TYPE_TCH_AHS         = 4,

    GPHY_VOICE_CHANNEL_TYPE_BUTT
};
typedef VOS_UINT16 GPHY_VOICE_CHANNEL_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM_UINT16
 ö��˵��  : ���������ŵ�
*****************************************************************************/
enum GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM
{
    GPHY_VOICE_TCHHS_SUB_CHANNEL_0          = 0,
    GPHY_VOICE_TCHHS_SUB_CHANNEL_1          = 1,

    GPHY_VOICE_TCH_SUB_CHANNEL_BUTT
};
typedef VOS_UINT16 GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM_UINT16;


/*****************************************************************************
 ö����    : GPHY_VOICE_CRC_RESULT_ENUM_UINT16
 ö��˵��  : CRC У����
*****************************************************************************/
enum GPHY_VOICE_CRC_RESULT_ENUM
{
    GPHY_VOICE_CRC_RESULT_ERROR             = 0,
    GPHY_VOICE_CRC_RESULT_CORRECT           = 1,

    GPHY_VOICE_CRC_BUTT
};
typedef VOS_UINT16 GPHY_VOICE_CRC_RESULT_ENUM_UINT16;


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
 ʵ������  : WPHY_VOICE_SYNC_IND_STRU
 ��������  : ����ҵ��������WPHY��9ms�жϷ��͸���Ϣ��CODEC����ʱ��ͬ��ָʾ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD02*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* ����*/
    VOS_UINT16                          uhwCfn;                                 /* ��ǰCFN */
    VOS_UINT16                          uhwSlotOffset;                          /* ͬ����Ϣƫ��֡ͷλ�õ�slotֵ */
    VOS_UINT16                          uhwChipOffset;                          /* ͬ����Ϣƫ��֡ͷλ�õ�chipֵ */
    VOS_UINT16                          uhwReserve2;
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}WPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_RX_DATA_IND_STRU
 ��������  : WPHYȡ��AMR�����󣬽��н��ܣ���������͸���Ϣ��CODEC�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwCfn;
    WPHY_VOICE_DATA_STRU                                                         /*_H2ASN_Skip*/
}WPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_WPHY_TX_DATA_IND_STRU
 ��������  : CODEC����������OK�󣬷��͸���Ϣ��WPHY�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDB01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    WPHY_VOICE_DATA_STRU
}VOICE_WPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_CELL_INFO_STRU
 ��������  : WС��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwCpichRscp;                           /* CPICH RSCP����ֵ */
    VOS_INT16                           shwCpichEcN0;                           /* CPICH EcN0����ֵ */
}WPHY_VOICE_CELL_INFO_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 ��������  : W������ά�ɲ⣬�ϱ�С���ŵ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDB01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwCellNum;                             /* �ϱ�С������ */
    VOS_UINT16                          uhwServCellId;                          /* ����С����Ӧ��ID */
    VOS_UINT16                          uhwReserved;                            /* �����ֶΣ���֤4�ֽڶ��� */
    WPHY_VOICE_CELL_INFO_STRU           astCellInfo[WPHY_VOICE_WCDMA_MAX_CELL_NUM];
}WPHY_VOICE_CHANNEL_QUALITY_IND_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_BSD_CS_IND_STRU
 ��������  : WPHY��CODEC����W�ŵ�����������BSD����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          uhwReserved;
    VOS_INT16                           shwCpichEcN0;                           /* CPICH Ec/N0��1/8dBm���� */
    VOS_INT16                           shwCpichRscp;                           /* CPICH RSCP */
    VOS_UINT16                          uhwSIR;                                 /* �����ŵ�SIRƽ��ֵ */
    VOS_UINT16                          uhwCRCErrBlkNum;                        /* CRC���������block���� */
    VOS_UINT16                          uhwTotalCRCBlkNum;                      /* ����blockͳ������ */
    VOS_UINT16                          uhwErrPilotBitNum;                      /* Pilot bit�������� */
    VOS_UINT16                          uhwTotalPilotBitNum;                    /* Pilot bitͳ������ */
    VOS_UINT16                          uhwDCHOutOfSyncInd;                     /* DCH out of sync ָʾ*/
}WPHY_VOICE_BSD_CS_IND_STRU;


/*****************************************************************************
 ʵ������  : GPHY_VOICE_UPDATE_PARA_CMD_STRU
 ��������  : GPHY�ڳ�ʼ����ͱ�����������仯ʱ���͸���Ϣ����CODEC���б����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD02*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    CODEC_ENUM_UINT16                   enCodecType;                            /*����������: 0 AMR-NB, 1 EFR, 2 FR, 3 HR , 4 AMR-NB 5 AMR-WB*/
    CODEC_DTX_ENUM_UINT16               enDtxMode;                              /* DTXʹ�ܱ�־��0 ��ʹ�ܣ�1 ʹ��*/
    VOS_UINT16                          enAmrMode;                              /* AMR��������ģʽ, �����AMR-NB��ȡֵ��7-0�ֱ��Ӧ8�ֲ�ͬ������ģʽ12.2-4.75�������AMR-WB��ȡֵ2��1��0���ֱ��Ӧ12.65��8.85��6.60*/
    CODEC_AMR_NSYNC_ENUM_UINT16         enAmrNsync;                             /*һ��Ϊ0���л����µĻ�վʱ��ȡ12*/
}GPHY_VOICE_UPDATE_PARA_CMD_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_PLAY_IND_STRU
 ��������  : GPHY���͸���Ϣ����CODEC����������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD04*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}GPHY_VOICE_PLAY_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_PLAY_CNF_STRU
 ��������  : CODEC���͸���Ϣ�ظ�GPHY��ԭ��ID_VOICE_GPHY_PLAY_CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC04*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRslt;                                 /*ִ�н��,0�ɹ�/1ʧ��*/
}VOICE_GPHY_PLAY_CNF_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_RECORD_IND_STRU
 ��������  : GPHY���͸���Ϣ����CODEC�������������ɼ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD05*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}GPHY_VOICE_RECORD_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_RECORD_CNF_STRU
 ��������  : CODEC���͸���Ϣ�ظ�GPHY��ԭ��ID_VOICE_GPHY_RECORD_CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC05*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRslt;                                 /*ִ�н��,0�ɹ�/1ʧ��*/
}VOICE_GPHY_RECORD_CNF_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_RX_DATA_IND_STRU
 ��������  : GPHY����������ͨ������Ϣ���͸�CODEC�������н���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD01 */ /*_H2ASN_Skip*/
    CODEC_ENUM_UINT16                   enCodecType;                            /* ����������: 0-AMR, 1-EFR, 2-FR, 3-HR */
    CODEC_BFI_ENUM_UINT16               enBfi;                                  /* ��֡��־,HR/FR/EFRʹ�� 0 dis 1 enable,bad*/
    CODEC_SID_ENUM_UINT16               enSid;                                  /* HR/FR/EFRʹ�� */
    CODEC_TAF_ENUM_UINT16               enTaf;                                  /* ͬ����־,HR/FR/EFRʹ�� */
    CODEC_HR_UFI_ENUM_UINT16            enUfi;                                  /* 0-�ŵ��ȶ�, 1-�ŵ�����, HRʹ�� */
    VOS_UINT16                          enAmrMode;                              /* AMR��������ģʽ*/
    CODEC_AMR_TYPE_RX_ENUM_UINT16       enAmrFrameType;                         /* AMR֡����, TX_SPEECH_GOOD/TX_SID_FIRST/TX_SID_UPDATA/TX_NO_DATA */
    VOS_UINT16                          puhwData[GPHY_VOICE_DATA_LEN];            /* AMRΪ����ǰ������Ϊ���ź���������ݣ���16bit�������У�������Чλ�ΪFR��260/16�� */
    CODEC_FRAME_FACCH_ENUM_UINT16       enIsFrameFacch;
    VOS_UINT16                          uhwDtxSpeechState;                      /* 0����speech,1����DTX */
    GPHY_VOICE_CRC_RESULT_ENUM_UINT16   enCrcFlag;                              /* CRC��ʶ, 0: crc_error, 1: crc_correct */
    VOS_UINT16                          uhwPber;                                /* Pber */
    VOS_UINT16                          uhwReserve;                             /* rsv�� */
} GPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_TX_DATA_IND_STRU
 ��������  : CODEC�����������󣬷��͸���Ϣ��GPHY��������������ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC02 */ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* ���� */
    CODEC_VAD_ENUM_UINT16               enVadFlag;                              /* VAD��־, 0-����֡, 1-������֡, HR/FR/EFRʱʹ��*/
    CODEC_SP_ENUM_UINT16                enSpFlag;                               /* Speech��־: 0Ϊ������֡��1Ϊ����֡, HR/FR/EFRʱʹ��*/
    CODEC_AMR_TYPE_TX_ENUM_UINT16       enAmrFrameType;                         /*����AMR֡����,TX_SPEECH_GOOD,TX_SPEECH_FIRST,TX_SID_UPDATA,TX_NODATA */
    VOS_UINT16                          enAmrMode;                              /* AMR�������� */
    VOS_UINT16                          auhwData[GPHY_VOICE_DATA_LEN];          /* AMRΪ���ź�����Ϊ����ǰ���������ݣ���16bit�������У�������Чλ�ΪFR��260/16��*/
    CODEC_ENUM_UINT16                   enCodecType;                            /* ����������: 0-AMR, 1-EFR, 2-FR, 3-HR, 5-AMRWB */
}VOICE_GPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_SYNC_REQ_STRU
 ��������  : CODEC���͸���Ϣ��GPHY����ʱ��ͬ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC03*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} VOICE_GPHY_SYNC_REQ_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_SET_CODEC_IND_STRU
 ��������  : CODEC�յ�NAS����������ʱ���͸���Ϣ֪ͨGPHY�����������¼�
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC06*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* ������ */
} VOICE_GPHY_SET_CODEC_IND_STRU;

/*****************************************************************************
 ʵ������  : GUPHY_VOICE_SUSPEND_CMD_STRU
 ��������  : GU-PHY��2G3��3G2ʱ���͸���Ϣ����CODEC��ͣ��������
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD08*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} GUPHY_VOICE_SUSPEND_CMD_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GUPHY_BACKGROUND_REQ_STRU
 �ṹ˵��  : VOICEģ��֪ͨPHY���뾲Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserved;
} VOICE_GUPHY_BACKGROUND_REQ_STRU;

/*****************************************************************************
 ʵ������  : PHY_CODEC_BACKGROUND_CNF_STRU
 �ṹ˵��  : PHY�ظ�CODEC�ѽ��뾲Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserved[2];
} GUPHY_VOICE_BACKGROUND_CNF_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GUPHY_FOREGROUND_REQ_STRU
 �ṹ˵��  : VOICEģ��֪ͨPHY������������ģʽ(�˳���Ĭģʽ)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserved;
} VOICE_GUPHY_FOREGROUND_REQ_STRU;

/*****************************************************************************
 ʵ������  : GUPHY_VOICE_FOREGROUND_CNF_STRU
 �ṹ˵��  : PHY�ظ�CODEC�ѽ�����������ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserved[2];
} GUPHY_VOICE_FOREGROUND_CNF_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_SYNC_IND_STRU
 ��������  : ����ҵ��������GPHY�ڵ�12֡��0ʱ϶�͸���Ϣ��CODEC����ʱ��ͬ��ָʾ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* ���� */
    VOS_UINT32                          uwFn;                                   /* ֡�� */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
    VOS_UINT16                          uhwTsn;                                 /* ʱ϶�� 0~7 */
    VOS_UINT16                          uhwChanCodeTime;                        /* ���б���ʱ��, ��λ:0.1 ms */
    VOS_UINT16                          uhwChanDecodeTime;                      /* ��������ʱ��, ��λ:0.1 ms */

    GPHY_VOICE_CHANNEL_TYPE_ENUM_UINT16                     enChanType;         /* �ŵ����� */
    GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM_UINT16                enSubChanNum;       /* ���ŵ���,������ʱ��Ч */

    VOS_UINT16                          uhwReserved2;                           /* ���� */
}GPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 ��������  : GPHY��CODEC����G�ŵ����������ڿ�ά�ɲ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          uhwDTX;
    VOS_UINT16                          uhwRxlevFull;                            /* �ź�ǿ��+ƫ��(316) */
    VOS_UINT16                          uhwRxlevSub;                             /* �ź�ǿ��+ƫ��(316) */
    VOS_UINT16                          uhwFrmNumFull;                           /* FULL���ĵ�ƽͳ��֡�� */
    VOS_UINT16                          uhwFrmNumSub;                            /* SUB���ĵ�ƽͳ��֡�� */
    VOS_UINT16                          uhwErrBitsFull;                          /* FULL��������BIT�� */
    VOS_UINT16                          uhwErrBitsSub;                           /* SUB��������BIT�� */
    VOS_UINT16                          uhwTotalBitsFull;                        /* FULL���ܵı����� */
    VOS_UINT16                          uhwTotalBitsSub;                         /* SUB���ܵı����� */
    VOS_UINT16                          uhwRxLevVal;
    VOS_UINT16                          uhwMeanBep;
    VOS_UINT16                          uhwCvBep;
    VOS_UINT16                          uhwReserved;
}GPHY_VOICE_CHANNEL_QUALITY_IND_STRU;

/*****************************************************************************
 �ṹ��    : VOICE_RCM_CALL_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CODEC֪ͨRCM Voice �Ƿ񱳾�Call ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_VOICE_MSG_ID_ENUM_UINT16                enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    CODEC_NET_MODE_ENUM_UINT16                  enModeID;                       /* ģʽID */
    RCM_VOICE_MODEM_ID_ENUM_UINT16              enModemID;                      /* modem ID */
    RCM_VOICE_CALL_STATE_ENUM_UINT16            enVoiceCallState;               /* voice state */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}VOICE_RCM_CALL_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : RCM_VOICE_CALL_STATE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM��CODEC Voice Call ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_VOICE_MSG_ID_ENUM_UINT16                enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    CODEC_NET_MODE_ENUM_UINT16                  enModeID;                       /* ģʽID */
    RCM_VOICE_MODEM_ID_ENUM_UINT16              enModemID;                      /* modem ID */
    RCM_VOICE_CALL_STATE_ENUM_UINT16            enVoiceCallState;               /* voice state */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}RCM_VOICE_CALL_STATE_CNF_STRU;


/*****************************************************************************
 ʵ������  : GPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 ��������  : GPHY��CODEC����G�ŵ����������ڿ�ά�ɲ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          uhwChannelType;                         /* �ŵ����� */
    VOS_UINT16                          uhwAssignRxTs;                          /* ҵ��ʱ϶ */
    VOS_UINT16                          uhwRxlev;                               /* �ź�ǿ�� */
    VOS_UINT16                          uhwCIAverage;                           /* CIƽ��ֵ */
    VOS_UINT16                          uhwErrBitSub;                           /* SUB��bit���� */
    VOS_UINT16                          uhwTotalBitSub;                         /* SUB bitͳ������ */
    VOS_UINT16                          uhwReserved;
}GPHY_VOICE_BSD_CS_IND_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_HO_START_REQ_STRU
 ��������  : Handover�л���ʱ����Ҫ��MED�·�����Ϣ����MED��ʼ�л�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* ���� */
    VOS_UINT32                          uwFn;                                   /* ֡�� */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}GPHY_VOICE_HO_START_REQ_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_HO_Complete_REQ_STRU
 ��������  : Handover�л���������Ҫ��MED�·�����Ϣ����MED�л�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* ���� */
    VOS_UINT32                          uwFn;                                   /* ֡�� */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}GPHY_VOICE_HO_Complete_REQ_STRU;

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
    DSP_VOICE_MSG_ID_ENUM_UINT16          enMsgID;            /* _H2ASN_MsgChoice_Export DSP_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          DSP_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_PHY_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_PHY_TRACE_MSG_DATA              stMsgData;
}VoicePhyTrace_MSG;

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

#endif /* end of phycodecinterface.h */
