

#ifndef __MDRV_SOCP_COMMON_H__
#define __MDRV_SOCP_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <product_config.h>

/**************************************************************************
  �궨��
**************************************************************************/
#define SOCP_CODER_SRC_CHAN                 0x00
#define SOCP_CODER_DEST_CHAN                0x01
#define SOCP_DECODER_SRC_CHAN               0x02
#define SOCP_DECODER_DEST_CHAN              0x03


#define SOCP_CHAN_DEF(chan_type, chan_id)   ((chan_type<<16)|chan_id)
#define SOCP_REAL_CHAN_ID(unique_chan_id)   (unique_chan_id & 0xFFFF)
#define SOCP_REAL_CHAN_TYPE(unique_chan_id) (unique_chan_id>>16)

/* ����Դͨ��IDö�ٶ��� */
/* ��soc_socp_adapter.h ��enum SOCP_CODER_SRC_ENUMö�ٶ��� */
typedef unsigned int SOCP_CODER_SRC_ENUM_U32;

/*����Դͨ��IDö�ٶ���*/
enum SOCP_DECODER_SRC_ENUM
{
    SOCP_DECODER_SRC_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,0),   /* LTE OM���� */
    SOCP_DECODER_SRC_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,1),   /* HDLC�������ʽAT���� */
    SOCP_DECODER_SRC_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,2),   /* GU OM���� */
    SOCP_DECODER_SRC_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,3),   /* ���� */
    SOCP_DECODER_SRC_BUTT
};
typedef unsigned int SOCP_DECODER_SRC_ENUM_U32;

/*����Ŀ��ͨ��IDö�ٶ���*/
enum SOCP_CODER_DST_ENUM
    {
    SOCP_CODER_DST_OM_CNF        = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,0), /* LTE OM������Ӧ��� */
    SOCP_CODER_DST_OM_IND        = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,1), /* LTE OM�����ϱ���� */
    SOCP_CODER_DST_HDLC_AT       = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,2), /* ��ʽAT������Ӧ��� */
    SOCP_CODER_DST_RFU0          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,3), /* GU OMĿ��ͨ�� */
    SOCP_CODER_DST_RFU1          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,4), /* ���� */
    SOCP_CODER_DST_RFU2          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,5), /* ���� */
    SOCP_CODER_DST_RFU3          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,6), /* ���� */
    SOCP_CODER_DST_BUTT
};
typedef unsigned int SOCP_CODER_DST_ENUM_U32;

/*����Ŀ��ͨ��IDö�ٶ���*/
enum SOCP_DECODER_DST_ENUM
    {
    SOCP_DECODER_DST_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,0),  /* LTE OM���� */
    SOCP_DECODER_DST_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,1),  /* HDLC�������ʽAT���� */
    SOCP_DECODER_DST_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,2),  /* GU OM���� */
    SOCP_DECODER_DST_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,3),  /* ���� */
    SOCP_DECODER_CBT            = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,16), /* GU CBT */
    SOCP_DECODER_DST_BUTT
};
typedef unsigned int SOCP_DECODER_DST_ENUM_U32;

#define SOCP_CODER_SRC_CHAN_BASE            0x00000000
#define SOCP_CODER_DEST_CHAN_BASE           0x00010000
#define SOCP_DECODER_SRC_CHAN_BASE          0x00020000
#define SOCP_DECODER_DEST_CHAN_BASE         0x00030000

/**************************************************************************
  �ṹ����
**************************************************************************/
/* SCMʹ�����ݽṹ����V9ͬ�� begin */
enum SOCP_BD_TYPE_ENUM
{
    SOCP_BD_DATA            = 0,    /* SOCP BD���ݿռ�ʹ��ʵ������ */
    SOCP_BD_LIST            = 1,    /* SOCP BD���ݿռ�ʹ��ʵ�����ݵ�ָ�� */
    SOCP_BD_BUTT
};
typedef unsigned short SOCP_BD_TYPE_ENUM_UINT16;

enum SOCP_HDLC_FLAG_ENUM
    {
    SOCP_HDLC_ENABLE         = 0,    /* ��ǰHDLC���ܴ� */
    SOCP_HDLC_DISABLE        = 1,    /* ��ǰHDLC���ܹر� */
    SOCP_HDLC_FLAG_BUTT
};

enum SOCP_STATE_ENUM
    {
    SOCP_IDLE               = 0,    /* SOCP���ڿ���̬ */
    SOCP_BUSY,                      /* SOCP��æ */
    SOCP_UNKNOWN_BUTT              /*  δ֪״̬ */
};
typedef unsigned int SOCP_STATE_ENUM_UINT32;

/* ��������ö��ֵ*/
enum SCM_DATA_TYPE_ENUM
    {
    SCM_DATA_TYPE_TL            = 0,            /* LTE OAM���� */
    SCM_DATA_TYPE_GU,                           /* GU OAM���� */
    SCM_DATA_TYPE_BUTT
};
typedef unsigned  char SOCP_DATA_TYPE_ENUM_UIN8;
/*����SOCPͨ����BD����Ƭ�ṹ*/
typedef struct
{
    unsigned int                      ulDataAddr;       /* ���ݵ�ָ�� */
    unsigned short                      usMsgLen;       /* ���ݳ��� */
    SOCP_BD_TYPE_ENUM_UINT16     enDataType;     /* ʵ���������ͣ�����������ʵ���� */
}SOCP_BD_DATA_STRU;

/*����SOCPͨ����RD����Ƭ�ṹ*/
typedef struct
{
    unsigned int                     ulDataAddr;       /*����ָ��*/
    unsigned short                     usMsgLen;       /*���ݳ���*/
    SOCP_BD_TYPE_ENUM_UINT16    enDataType;     /*ʵ���������ͣ�����������ʵ����*/
}SOCP_RD_DATA_STRU;
/* SCMʹ�����ݽṹ����V9ͬ�� end */

enum tagSOCP_EVENT_E
{
        SOCP_EVENT_PKT_HEADER_ERROR         = 0x1,    /* ��ͷ������"HISI" */
        SOCP_EVENT_OUTBUFFER_OVERFLOW       = 0x2,    /* Ŀ��buffer���� */
        SOCP_EVENT_RDBUFFER_OVERFLOW        = 0x4,    /* RDbuffer���� */
        SOCP_EVENT_DECODER_UNDERFLOW        = 0x8,    /* ����Դbuffer���� */
        SOCP_EVENT_PKT_LENGTH_ERROR         = 0x10,   /* ��������ȼ����� */
        SOCP_EVENT_CRC_ERROR                = 0x20,   /* ����CRCУ����� */
        SOCP_EVENT_DATA_TYPE_ERROR          = 0x40,   /* �����������ʹ���*/
        SOCP_EVENT_HDLC_HEADER_ERROR        = 0x80,   /* ����HDLC������ */
        SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW = 0x100, /* Ŀ��buffer��ֵ����ж� */
        SOCP_EVENT_BUTT
};
typedef unsigned int SOCP_EVENT_ENUM_UIN32;

/* ����Դ�����ݽṹģʽ */
enum tagSOCP_ENCSRC_CHNMODE_E
{
    SOCP_ENCSRC_CHNMODE_CTSPACKET       = 0,    /* �������ݰ����λ����� */
    SOCP_ENCSRC_CHNMODE_FIXPACKET,              /* �̶��������ݰ����λ����� */
    SOCP_ENCSRC_CHNMODE_LIST,                   /* ��ʽ���λ����� */
    SOCP_ENCSRC_CHNMODE_BUTT
};
typedef unsigned int SOCP_ENCSRC_CHNMODE_ENUM_UIN32;

/* ����Դ�����ݽṹģʽ */
enum tagSOCP_DECSRC_CHNMODE_E
{
    SOCP_DECSRC_CHNMODE_BYTES        = 0,       /* �����ֽڻ��λ����� */
    SOCP_DECSRC_CHNMODE_LIST,                   /* ��ʽ���λ����� */
    SOCP_DECSRC_CHNMODE_BUTT
};
typedef unsigned int SOCP_DECSRC_CHNMODE_ENUM_UIN32;

/* ��ʱѡ��ʹ�����ݽṹ��SOCP_TIMEOUT_DECODE_TRF */
/* 2014��2��22��15:34:11 l00258701 modify add */
enum tagSOCP_TIMEOUT_EN_E
{
    SOCP_TIMEOUT_BUFOVF_DISABLE        = 0,       /* buffer��������ϱ��ж� */
    SOCP_TIMEOUT_BUFOVF_ENABLE,                   /* buffer�������ʱ�����ϱ��ж� */
    SOCP_TIMEOUT_TRF,                             /* �����жϳ�ʱ���� */
    SOCP_TIMEOUT_DECODE_TRF,                      /* �����жϳ�ʱ */
    SOCP_TIMEOUT_BUTT
};
typedef unsigned int SOCP_TIMEOUT_EN_ENUM_UIN32;

/* ͬһ���͵�ͨ����ͬ���ȼ�ö��ֵ*/
enum tagSOCP_CHAN_PRIORITY_E
{
    SOCP_CHAN_PRIORITY_0     = 0,               /* ������ȼ�*/
    SOCP_CHAN_PRIORITY_1,                       /* �ε����ȼ�*/
    SOCP_CHAN_PRIORITY_2,                       /* �θ����ȼ�*/
    SOCP_CHAN_PRIORITY_3,                       /* ������ȼ�*/
    SOCP_CHAN_PRIORITY_BUTT
};
typedef unsigned int SOCP_CHAN_PRIORITY_ENUM_UIN32;

/* ��������ö��ֵ*/
enum tagSOCP_DATA_TYPE_E
{
    SOCP_DATA_TYPE_0            = 0,            /* LTE OAM���� */
    SOCP_DATA_TYPE_1,                           /* GU OAM���� */
    SOCP_DATA_TYPE_2,                           /* ���� */
    SOCP_DATA_TYPE_3,                           /* ���� */
    SOCP_DATA_TYPE_BUTT
};
typedef unsigned int SOCP_DATA_TYPE_ENUM_UIN32;


/* BBP ����ģʽ�����ݶ����򸲸� */
enum tagSOCP_BBP_DS_MODE_E
{
    SOCP_BBP_DS_MODE_DROP           = 0,        /* ���ݶ��� */
    SOCP_BBP_DS_MODE_OVERRIDE,                  /* ���ݸ��� */
    SOCP_BBP_DS_MODE_BUTT
};
typedef unsigned int SOCP_BBP_DS_MODE_ENUM_UIN32;

/* ����Դͨ��data type ʹ��λ */
enum tagSOCP_DATA_TYPE_EN_E
{
    SOCP_DATA_TYPE_EN           = 0,        /* data type ʹ�ܣ�Ĭ��ֵ */
    SOCP_DATA_TYPE_DIS,                     /* data type ��ʹ�� */
    SOCP_DATA_TYPE_EN_BUTT
};
typedef unsigned int SOCP_DATA_TYPE_EN_ENUM_UIN32;

/* ����Դͨ��debug ʹ��λ */
enum tagSOCP_ENC_DEBUG_EN_E
{
    SOCP_ENC_DEBUG_DIS          = 0,       /* debug ��ʹ�ܣ�Ĭ��ֵ */
    SOCP_ENC_DEBUG_EN,                     /* debug ʹ�� */
    SOCP_ENC_DEBUG_EN_BUTT
};
typedef unsigned int SOCP_ENC_DEBUG_EN_ENUM_UIN32;

/* ����ͨ·�������ýṹ�� */
typedef struct tagSOCP_DEC_PKTLGTH_S
{
    unsigned int             u32PktMax;         /*���������ֵ*/
    unsigned int             u32PktMin;         /*��������Сֵ*/
}SOCP_DEC_PKTLGTH_STRU;


/* ͨ��Դͨ��buffer�ṹ�嶨��*/
typedef struct
{
    unsigned  char                 *pucInputStart;      /* ����ͨ����ʼ��ַ*/
    unsigned  char                 *pucInputEnd;        /* ����ͨ��������ַ*/
    unsigned  char                 *pucRDStart;         /* RD buffer��ʼ��ַ*/
    unsigned  char                 *pucRDEnd;           /* RD buffer������ַ*/
    unsigned int                 u32RDThreshold;     /* RD buffer�����ϱ���ֵ*/
    unsigned int                 ulRsv;              /* reserve */
}SOCP_SRC_SETBUF_STRU;

/* ͨ��Ŀ��ͨ��buffer�ṹ�嶨��*/
typedef struct
{
    unsigned  char                 *pucOutputStart;     /* ���ͨ����ʼ��ַ*/
    unsigned  char                 *pucOutputEnd;       /* ���ͨ��������ַ*/
    unsigned int                 u32Threshold;       /* ���ͨ������ֵ */
    unsigned int                 ulRsv;              /* reserve */
}SOCP_DST_SETBUF_STRU;

/* ����Դͨ���ṹ�嶨��*/
typedef struct tagSOCP_CODER_SRC_CHAN_S
{
    unsigned int                         u32DestChanID;      /* Ŀ��ͨ��ID*/
    unsigned int                         u32BypassEn;        /* ͨ��bypassʹ��*/
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;          /* �������ͣ�ָ�����ݷ�װЭ�飬���ڸ��ö�ƽ̨*/
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;        /* ��������ʹ��λ*/
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;           /* ����λʹ��*/
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eMode;              /* ͨ������ģʽ*/
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;          /* ͨ�����ȼ�*/
    SOCP_SRC_SETBUF_STRU            sCoderSetSrcBuf;
}SOCP_CODER_SRC_CHAN_S;

/* ����Ŀ�����ýṹ�嶨��*/
typedef struct tagSOCP_CODER_DEST_CHAN_S
{
    unsigned int                 u32EncDstThrh;     /* ����Ŀ��ͨ����ֵ���ޣ��ٲ�ͨ��ʱʹ��*/
    SOCP_DST_SETBUF_STRU       sCoderSetDstBuf;
}SOCP_CODER_DEST_CHAN_S;

/* ����Դͨ���ṹ�嶨��*/
typedef struct tagSOCP_DECODER_SRC_CHAN_S
{
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;        /* ��������ʹ��λ*/
    SOCP_DECSRC_CHNMODE_ENUM_UIN32   eMode;              /* ͨ��ģʽ*/
    SOCP_SRC_SETBUF_STRU       sDecoderSetSrcBuf;
}SOCP_DECODER_SRC_CHAN_STRU;

/* ����Ŀ��ͨ���ṹ�嶨��*/
typedef struct tagSOCP_DECODER_DEST_CHAN_S
{
    unsigned int                 u32SrcChanID;       /* ������Դͨ��ID*/
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;          /* �������ͣ�ָ�����ݷ�װЭ�飬���ڸ��ö�ƽ̨*/
    SOCP_DST_SETBUF_STRU       sDecoderDstSetBuf;
}SOCP_DECODER_DEST_CHAN_STRU;

/* ͨ��buffer�����ṹ�嶨��*/
typedef struct tagSOCP_BUFFER_RW_S
{
    char    *pBuffer;                        /* bufferָ��*/
    char    *pRbBuffer;                      /* �ؾ�bufferָ��*/
    unsigned int     u32Size;                        /* ����buffer��С*/
    unsigned int     u32RbSize;                      /* �ؾ�buffer��С*/
}SOCP_BUFFER_RW_STRU;

/* ����Դͨ����������ṹ�嶨��*/
typedef struct tagSOCP_DECODER_ERROR_CNT_S
{
    unsigned int     u32PktlengthCnt;                /* �������������*/
    unsigned int     u32CrcCnt;                      /* CRCУ��������*/
    unsigned int     u32DataTypeCnt;                 /* �����������ͼ���������*/
    unsigned int     u32HdlcHeaderCnt;               /* 0x7EУ�����*/
}SOCP_DECODER_ERROR_CNT_STRU;

/* ����Դ����ͨ�����ýṹ�� */
typedef struct tagSOCP_ENCSRC_RSVCHN_SCOPE_S
{
    unsigned int                 u32RsvIDMin;        /*����Դ����ͨ��ID��Сֵ*/
    unsigned int                 u32RsvIDMax;        /*����Դ����ͨ��ID���ֵ*/
}SOCP_ENCSRC_RSVCHN_SCOPE_STRU;

/* SOCPͶƱ��� */
enum SOCP_VOTE_ID_ENUM
{
    SOCP_VOTE_GU_DSP,       /* GU DSP */
    SOCP_VOTE_DIAG_APP,     /* DIAG APP,����DRV APP */
    SOCP_VOTE_DIAG_COMM,    /* DIAG COMM,����LDSP��DRV COMM */
    SOCP_VOTE_TL_DSP,       /* TL DSP*/
    SOCP_VOTE_SOCP_REG,     /* SOCP�Ĵ�������*/
    SOCP_VOTE_ID_BUTT
};
typedef unsigned int SOCP_VOTE_ID_ENUM_U32;

/* SOCPͶƱ���� */
enum SOCP_VOTE_TYPE_ENUM
{
    SOCP_VOTE_FOR_SLEEP,    /* ����˯�� */
    SOCP_VOTE_FOR_WAKE,     /* ����˯�� */
    SOCP_VOTE_TYPE_BUTT
};
typedef unsigned int SOCP_VOTE_TYPE_ENUM_U32;

typedef int (*socp_event_cb)(unsigned int u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, unsigned int u32Param);
typedef int (*socp_read_cb)(unsigned int u32ChanID);
typedef int (*socp_rd_cb)(unsigned int u32ChanID);

/* log2.0 2014-03-19 Begin:*/
typedef struct SOCP_ENC_DST_BUF_LOG_CFG
{
    void*           pVirBuffer;      /* SOCP����Ŀ��ͨ����������BUFFER����32λϵͳ����4�ֽڣ���64λϵͳ����8�ֽ� */
    unsigned long   ulPhyBufferAddr; /* SOCP����Ŀ��ͨ����������BUFFER��ַ */
    unsigned int    BufferSize;      /* SOCP����Ŀ��ͨ������BUFFER��С */
    unsigned int    overTime;        /* NVE�����õĳ�ʱʱ�� */
    unsigned int    logOnFlag;       /* ��������buffer����������־(SOCP_DST_CHAN_CFG_TYPE_ENUM) */
    unsigned int    ulCurTimeout;    /* SOCP����Ŀ��ͨ�����ݴ��䳬ʱʱ�� */
} SOCP_ENC_DST_BUF_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/

#define INNER_LOG_DATA_MAX                   0x40

typedef struct
{
    unsigned int                  ulSlice;
    unsigned int                  ulFileNO;
    signed int                   lLineNO;
    unsigned int                  ulP1;
    unsigned int                  ulP2;
}INNER_LOG_RECORD_STRU;

typedef struct
{
    unsigned int                  ulCnt;
    INNER_LOG_RECORD_STRU       astLogData[INNER_LOG_DATA_MAX];
}INNER_LOG_DATA_STRU;

/**************************************************************************
  ��������
**************************************************************************/
/*****************************************************************************
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��ʼ���ɹ��ı�ʶ��
*****************************************************************************/
int DRV_SOCP_INIT(void);

/*****************************************************************************
�� �� ��  : mdrv_socp_corder_set_src_chan
��������  : �˽ӿ����SOCP������Դͨ���ķ��䣬���ݱ�����Դͨ����������ͨ�����ԣ�����Ŀ��ͨ�������غ���ִ�н����
�������  : pSrcAttr:������Դͨ�������ṹ��ָ�롣
     pSrcChanID:���뵽��Դͨ��ID��
*  �������  : �ޡ�
*  �� �� ֵ  : SOCP_OK:     ����Դͨ������ɹ���
*              SOCP_ERROR:  ����Դͨ������ʧ�ܡ�
*****************************************************************************/
int mdrv_socp_corder_set_src_chan(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr);

/*****************************************************************************
*  �� �� ��  : mdrv_socp_coder_set_dest_chan_attr
*  ��������  : �˽ӿ����ĳһ����Ŀ��ͨ�������ã����غ���ִ�еĽ����
*  �������  : u32DestChanID:   SOCP��������Ŀ��ͨ��ID��
*                  pDestAttr:   SOCP������Ŀ��ͨ�������ṹ��ָ�롣
*  �������  : �ޡ�
*  �� �� ֵ  : SOCP_OK:      ����Ŀ��ͨ�����óɹ���
*              SOCP_ERROR:   ����Ŀ��ͨ������ʧ�ܡ�
******************************************************************************/
int mdrv_socp_coder_set_dest_chan_attr(unsigned int u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr);

/*****************************************************************************
*  �� �� ��  : mdrv_socp_decoder_set_dest_chan
*  ��������  : �˽ӿ����SOCP������Ŀ��ͨ���ķ��䣬
*              ���ݽ���Ŀ��ͨ����������ͨ�����ԣ�
*              ������Դͨ�������غ���ִ�н����
�������  : pAttr:������Ŀ��ͨ�������ṹ��ָ��
     pDestChanID:���뵽��Ŀ��ͨ��ID
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:����Ŀ��ͨ������ɹ���
     SOCP_ERROR:����Ŀ��ͨ������ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_STRU *pAttr);

/*****************************************************************************
�� �� ��  : DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
��������  : �˽ӿ����ĳһ����Դͨ�������ã����غ���ִ�еĽ����
�������  : u32SrcChanID:������Դͨ��ID
     pInputAttr:������Դͨ�������ṹ��ָ��
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:����Դͨ�����óɹ�
     SOCP_ERROR:����Դͨ������ʧ��
*****************************************************************************/
int DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( unsigned int u32SrcChanID,SOCP_DECODER_SRC_CHAN_STRU *pInputAttr);

/*****************************************************************************
�� �� ��  : DRV_SOCP_DECODER_GET_ERR_CNT
��������  :�˽ӿڸ�������ͨ���������쳣����ļ���ֵ��
�������  : u32ChanID:������ͨ��ID
                 pErrCnt:�������쳣�����ṹ��ָ��
�������  : �ޡ�
�� �� ֵ      : SOCP_OK:�����쳣�����ɹ�
                     SOCP_ERROR:�����쳣����ʧ��
*****************************************************************************/
int DRV_SOCP_DECODER_GET_ERR_CNT (unsigned int u32ChanID, SOCP_DECODER_ERROR_CNT_STRU *pErrCnt);

/*****************************************************************************
�� �� ��  : DRV_SOCP_FREE_CHANNEL
��������  : �˽ӿڸ���ͨ��ID�ͷŷ���ı����ͨ����
�������  : u32ChanID:ͨ��ID��
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:ͨ���ͷųɹ���
     SOCP_ERROR:ͨ���ͷ�ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_FREE_CHANNEL(unsigned int u32ChanID);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* ��������  : ��ձ���Դͨ����ͬ��V9 SOCP�ӿ�
*
* �������  : enSrcChanID       ����ͨ����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/
unsigned int DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID);
#define SOCP_CleanEncSrcChan(enSrcChanID)  DRV_SOCP_CLEAN_ENCSRC_CHAN(enSrcChanID)

/*****************************************************************************
�� �� ��  : DRV_SOCP_REGISTER_EVENT_CB
��������  : �˽ӿ�Ϊ����ͨ��ע���¼��ص�������
�������  : u32ChanID:ͨ��ID��
     EventCB:�¼��ص��������ο�socp_event_cb��������
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:ע���¼��ص������ɹ���
     SOCP_ERROR:ע���¼��ص�����ʧ�ܡ�
*****************************************************************************/
int DRV_SOCP_REGISTER_EVENT_CB(unsigned int u32ChanID, socp_event_cb EventCB);

/*****************************************************************************
�� �� ��  : mdrv_socp_start
��������  : �˽ӿ�����Դͨ��������������߽��롣
�������  : u32SrcChanID:Դͨ��ID��
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:�������������ɹ���
      SOCP_ERROR:������������ʧ�ܡ�
*****************************************************************************/
int mdrv_socp_start(unsigned int u32SrcChanID);

/*****************************************************************************
�� �� ��  : mdrv_socp_stop
��������  : �˽ӿ�����Դͨ����ֹͣ������߽��롣
�������  : u32SrcChanID:Դͨ��ID��
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:��������ֹͣ�ɹ���
     SOCP_ERROR:��������ֹͣʧ�ܡ�
*****************************************************************************/
int mdrv_socp_stop(unsigned int u32SrcChanID);
static inline void SOCP_Stop1SrcChan(unsigned int u32SrcChanID)
{
    (void)mdrv_socp_stop(u32SrcChanID);
}

/*****************************************************************************
�� �� ��  : DRV_SOCP_SET_TIMEOUT
��������  : �˽ӿ����ó�ʱ��ֵ��
�������  : u32Timeout:��ʱ��ֵ

�������  : �ޡ�
�� �� ֵ  : SOCP_OK:���ó�ʱʱ����ֵ�ɹ���
     SOCP_ERROR:���ó�ʱʱ����ֵʧ��
*****************************************************************************/
int DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_ENUM_UIN32 eTmOutEn, unsigned int u32Timeout);

/*****************************************************************************
�� �� ��  : DRV_SOCP_SET_DEC_PKT_LGTH
��������  : ���ý�������ȼ���ֵ
�������  : pPktlgth:��������ȼ�ֵ

�������  : �ޡ�
�� �� ֵ  : SOCP_OK:���óɹ���
     ����ֵ:����ʧ��
*****************************************************************************/
int DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_STRU *pPktlgth);

/*****************************************************************************
�� �� ��  : DRV_SOCP_SET_DEBUG
��������  : ���ý���Դͨ����debugģʽ
�������  : u32ChanID:ͨ��ID
     u32DebugEn: debug��ʶ
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:���óɹ���
     ����ֵ:����ʧ��
*****************************************************************************/
int DRV_SOCP_SET_DEBUG(unsigned int u32DestChanID, unsigned int u32DebugEn);

/*****************************************************************************
�� �� ��  : DRV_SOCP_CHAN_SOFT_RESET
��������  : Դͨ����λ
�������  : u32ChanID:ͨ��ID
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:�踴λ�ɹ���
     ����ֵ:��λʧ��
*****************************************************************************/
int DRV_SOCP_CHAN_SOFT_RESET(unsigned int u32ChanID);

/*****************************************************************************
�� �� ��  : mdrv_socp_get_write_buff
��������  : �˽ӿ����ڻ�ȡд����buffer��
�������  : u32SrcChanID:Դͨ��ID
     pBuff:           :д����buffer

�������  : �ޡ�
�� �� ֵ  : SOCP_OK:��ȡд����buffer�ɹ���
     SOCP_ERROR:��ȡд����bufferʧ��
*****************************************************************************/
int mdrv_socp_get_write_buff( unsigned int u32SrcChanID, SOCP_BUFFER_RW_STRU *pBuff);

/*****************************************************************************
�� �� ��  : mdrv_socp_write_done
��������  : �ýӿ��������ݵ�д�������ṩд�����ݵĳ��ȡ�
�������  : u32SrcChanID:Դͨ��ID
     u32WrtSize:   ��д�����ݵĳ���
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:д�����ݳɹ���
       SOCP_ERROR:д������ʧ��
*****************************************************************************/
int mdrv_socp_write_done(unsigned int u32SrcChanID, unsigned int u32WrtSize);

/*****************************************************************************
�� �� ��  : mdrv_socp_register_rd_cb
��������  : �ýӿ�����ע���RD�������ж�ȡ���ݵĻص�������
�������  : u32SrcChanID:Դͨ��ID
     RdCB:  �¼��ص�����
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:ע��RD���λ����������ݻص������ɹ���
     SOCP_ERROR:ע��RD���λ����������ݻص�����ʧ��
*****************************************************************************/
int DRV_SOCP_REGISTER_RD_CB(unsigned int u32SrcChanID, socp_rd_cb RdCB);

/*****************************************************************************
�� �� ��  : mdrv_socp_get_rd_buffer
��������  : �ô˽ӿ����ڻ�ȡRD buffer������ָ�롣
�������  : u32SrcChanID:Դͨ��ID
     pBuff:  RD buffer
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:��ȡRD���λ������ɹ�
     SOCP_ERROR:��ȡRD���λ�����ʧ��
*****************************************************************************/
int mdrv_socp_get_rd_buffer( unsigned int u32SrcChanID,SOCP_BUFFER_RW_STRU *pBuff);


/*****************************************************************************
�� �� ��  : bsp_socp_read_rd_done
��������  : �˽ӿ������ϲ�֪ͨSOCP��������RD buffer��ʵ�ʶ�ȡ�����ݡ�
�������  : u32SrcChanID:Դͨ��ID
      u32RDSize:  ��RD buffer��ʵ�ʶ�ȡ�����ݳ���
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:��ȡRDbuffer�е����ݳɹ�
      SOCP_ERROR:��ȡRDbuffer�е�����ʧ��
*****************************************************************************/
int mdrv_socp_read_rd_done(unsigned int u32SrcChanID, unsigned int u32RDSize);

/*****************************************************************************
�� �� ��  : bsp_socp_register_read_cb
��������  : �ýӿ�����ע������ݵĻص�������
�������  : u32DestChanID:Ŀ��ͨ��ID
     ReadCB: �¼��ص�����
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:ע������ݻص������ɹ�
     SOCP_ERROR:ע������ݻص�����ʧ��
*****************************************************************************/
int DRV_SOCP_REGISTER_READ_CB( unsigned int u32DestChanID, socp_read_cb ReadCB);
#define BSP_SOCP_RegisterReadCB(u32DestChanID,ReadCB)  \
    DRV_SOCP_REGISTER_READ_CB(u32DestChanID,ReadCB)

/*****************************************************************************
�� �� ��  : DRV_SOCP_GET_READ_BUFF
��������  : �ô˽ӿ����ڻ�ȡ�����ݻ�����ָ�롣
�������  : u32DestChanID:Ŀ��ͨ��ID
     ReadCB: ������buffer
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:��ȡ�����ݻ������ɹ���
     SOCP_ERROR:��ȡ�����ݻ������ɹ���
*****************************************************************************/
int DRV_SOCP_GET_READ_BUFF(unsigned int u32DestChanID,SOCP_BUFFER_RW_STRU *pBuffer);
#define BSP_SOCP_GetReadBuff(u32SrcChanID,pBuff)  \
        DRV_SOCP_GET_READ_BUFF(u32SrcChanID,pBuff)

/*****************************************************************************
�� �� ��  : DRV_SOCP_READ_DATA_DONE
��������  : �ýӿ������ϲ����SOCP��������Ŀ��ͨ���ж��ߵ�ʵ�����ݡ�
�������  : u32DestChanID:Ŀ��ͨ��ID
     u32ReadSize: �Ѷ������ݵĳ���
�������  : �ޡ�
�� �� ֵ  : SOCP_OK:�����ݳɹ���
     SOCP_ERROR:������ʧ��
*****************************************************************************/
int DRV_SOCP_READ_DATA_DONE(unsigned int u32DestChanID,unsigned int u32ReadSize);
#define BSP_SOCP_ReadDataDone(u32DestChanID,u32ReadSize) \
        DRV_SOCP_READ_DATA_DONE(u32DestChanID,u32ReadSize)

/*****************************************************************************
�� �� ��  : DRV_SOCP_SET_BBP_ENABLE
��������  : ʹ�ܻ�ֹͣBBPͨ����
�������  : bEnable:ͨ��ID
�������  : �ޡ�
�� �� ֵ      : SOCP_OK:���óɹ���
           ����ֵ:����ʧ��
*****************************************************************************/
int DRV_SOCP_SET_BBP_ENABLE(int bEnable);

/*****************************************************************************
�� �� ��  : DRV_SOCP_SET_BBP_DS_MODE
��������  : ����BBP DSͨ�������������ģʽ��
�������  : eDsMode:DSͨ���������ʱ����ģʽ����
�������  : �ޡ�
�� �� ֵ      : SOCP_OK:���óɹ���
           ����ֵ:����ʧ��
*****************************************************************************/
int DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_ENUM_UIN32 eDsMode);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_START
* ��������  : enable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_START(void);


/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_STOP
* ��������  : disable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
void  DRV_SOCP_DSPCHN_STOP(void);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_GET_STATE
*
* ��������  : ��ȡSOCP״̬
*
* �� �� ֵ  : SOCP_IDLE    ����
*             SOCP_BUSY    æµ
*****************************************************************************/
SOCP_STATE_ENUM_UINT32  DRV_SOCP_GET_STATE(void);

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_BAK_REG
* ��������  : BBPDMA����
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
int  DRV_BBPDMA_DRX_BAK_REG(void);

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_RESTORE_REG
* ��������  : �ָ�BBPDMA
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
int  DRV_BBPDMA_DRX_RESTORE_REG(void);

/*****************************************************************************
* �� �� ��  : mdrv_socp_get_sd_logcfg
* ��������  : ��ѯˢ�º�LOG2.0 SOCP��ʱ������Ϣ
* �������  : ��
* �������  : ��
* �� �� ֵ  : SOCP_ENC_DST_BUF_LOG_CFG_STRUָ��
*****************************************************************************/
unsigned int mdrv_socp_get_sd_logcfg(SOCP_ENC_DST_BUF_LOG_CFG_STRU* cfg);
/*****************************************************************************
* �� �� ��  : mdrv_socp_set_log_int_timeout
* ��������  : ʹ��CMD LINE�еĳ�ʱʱ��������LOG2.0 SOCP��ʱ����
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
void mdrv_socp_set_log_int_timeout(void);
/*****************************************************************************
* �� �� ��  : mdrv_socp_set_log_int_default_timeout
* ��������  : ʹ��Ĭ�ϵĳ�ʱʱ��������LOG2.0 SOCP��ʱ����
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
void mdrv_socp_set_log_int_default_timeout(void);

unsigned int  DRV_SOCP_INIT_LTE_DSP(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

unsigned int  DRV_SOCP_INIT_LTE_BBP_LOG(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

unsigned int  DRV_SOCP_INIT_LTE_BBP_DS(unsigned int ulChanId,unsigned int ulPhyAddr,unsigned int ulSize);

void DRV_SOCP_ENABLE_LTE_BBP_DSP(unsigned int ulChanId);

void BSP_SOCP_RefreshSDLogCfg(unsigned int ulTimerLen);

/*****************************************************************************
* �� �� ��  : mdrv_socp_set_autodiv_enalbe
*
* ��������  : ʹ��SOCP���Զ���Ƶ
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void mdrv_socp_enalbe_dfs(void);

/*****************************************************************************
* �� �� ��  : mdrv_socp_set_autodiv_disalbe
*
* ��������  : ȥʹ��SOCP���Զ���Ƶ
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void mdrv_socp_disalbe_dfs(void);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_VOTE
* ��������  : SOCPͶƱ�ӿڣ�����ͶƱ�������SOCP�Ƿ�˯�ߣ��ýӿ�ֻ��A���ṩ
* �������  : id --- ͶƱ���ID��type --- ͶƱ����
* �������  : ��
* �� �� ֵ  : int 0 --- ͶƱ�ɹ���0xFFFFFFFF --- ͶƱʧ��
*****************************************************************************/
int DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_VOTE_TO_MCORE
* ��������  : SOCPͶƱ�ӿڣ��ýӿ�ֻ��C���ṩ������LDSP�״μ��ص�SOCP�ϵ�����
* �������  : type --- ͶƱ����
* �������  : ��
* �� �� ֵ  : int 0 --- ͶƱ�ɹ���0xFFFFFFFF --- ͶƱʧ��
*****************************************************************************/
int DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type);



#ifdef __cplusplus
}
#endif
#endif //__MDRV_SOCP_COMMON_H__
