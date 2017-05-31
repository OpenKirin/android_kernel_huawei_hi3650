

/******************************************************************************

                  ��Ȩ���� (C), 2001-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : bbp_colltion.h
  �� �� ��      : ����
  ��    ��      : j00174725
  ��������      : 2012��11��06��
  ����޸�      :
  ��������      : ��ͷ�ļ�ΪBBP������ͷ�ļ�
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2012��11��06��
    ��    ��    : ���±� 00174725
    �޸�����    : �����ļ�

******************************************************************************/
#ifndef _OM_BBP_LOG_H_
#define _OM_BBP_LOG_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define OM_BBP_REG(reg)   (*(volatile VOS_UINT32 *)((VOS_UINT32)(reg)))

#define OM_BBP_REG_SETBITS(reg, pos, bits, val) (OM_BBP_REG(reg) = (OM_BBP_REG(reg) \
                                        & (~((((VOS_UINT32)1 << (bits)) - 1) << (pos)))) \
                                        | ((VOS_UINT32)((val) & (((VOS_UINT32)1 << (bits)) - 1)) << (pos)))

#define OM_BBP_WRITE_REG(reg,value)                 (OM_BBP_REG(reg) = (value))

#define OM_BBP_READ_REG(value,reg)                  ((value) = OM_BBP_REG(reg))

/* BBP��ά�ɲ�ÿ��ͨ����Ҫ�ҽӵĽ���� */
#define BBP_DBG_NODE_NUM                            (4)

#define OM_BBP_BITN(n)                              (0x1 << n)

/* ����BBP��ά�ɲ��SOCPͨ������ */
#define BBP_DBG_CODER_SRC_NUM                       (2)

/* ÿ��������Ŀռ��С 4Kbyte */
#define BBP_DBG_NODE_SIZE                           (2 * 1024)

/* ÿ��SOCPͨ������Դ�ռ�Ĵ�С 8K  */
#define BBP_DBG_CODER_SRC_SIZE                      (BBP_DBG_NODE_NUM * BBP_DBG_NODE_SIZE)

/* BBP��ά�ɲ���Ҫ������ܿռ��С 16K*/
#define BBP_DBG_TOTAL_MEM_LENTH                     (BBP_DBG_CODER_SRC_SIZE * BBP_DBG_CODER_SRC_NUM)

/* BBP ������С���� 30.75 * 1024 KB:ԭ����С�Ĳ�������Ϊ30.72MB,��������32KB�������� */
#define BBP_DUMP_MIN_LEN                            (31488)

/* BBP ������󳤶� 2G */
#define BBP_DUMP_MAX_LEN                            (2 * 1024 * 1024)

/* BBP ���ɳ��ȱ�����32KB�������� */
#define BBP_DUMP_UNIT_LEN                           (32)

/* BBP��Ҫ���ݻָ��ļĴ������� */
#define BBP_DBG_BACK_REG_NUM                        (20)

#define BBP_DUMP_EDMA_INT                           (BALONG_DMA_INT_DONE \
                                                    | BALONG_DMA_INT_TRANSFER_ERR \
                                                    | BALONG_DMA_INT_CONFIG_ERR)

#define BBP_DBG_EDMA_INT                            (BALONG_DMA_INT_DONE \
                                                    | BALONG_DMA_INT_TRANSFER_ERR \
                                                    | BALONG_DMA_INT_CONFIG_ERR \
                                                    | BALONG_DMA_INT_LLT_DONE \
                                                    | BALONG_DMA_INT_READ_ERR)

#define MAX_BBP_OFFSET_ADDR                         (0xFFFFFF)

#define BBP_DBG_MAGIC_SIGN                          (0x48495349)

#define BBP_DBG_PACKAGE_LENTH                       (2040)

#define BBP_DBG_ERR_PACKAGE_SIGN                    (0x5555AAAA)

#define OM_BBP_DBG_START                            (0x5555aaaa)   /* ���� */
#define OM_BBP_DBG_STOP                             (0xaaaa5555)   /* ֹͣ */

#define WAITING_ACPU_CNF_TIMEOUT_LEN                (5000)
/* CCPU��ACPU���͵�������Ϣ,��ȴ��ظ� */
#define BBP_QUERY_DUMP_INFO_REQ                     (0xFA01)
#define BBP_QUERY_DUMP_INFO_CNF                     (0xFA02)


/* PC���·�BBP�������� */
#define APP_OM_BBP_DUMP_SET_REQ                   0x8103
#define OM_APP_BBP_DUMP_SET_CNF                   0x8104

/* PC���·�BBP ��ά�ɲ����� */
#define APP_OM_BBP_DBG_SET_REQ                    0x8105
#define OM_APP_BBP_DBG_SET_CNF                    0x8106

/* ��BBP �����ж���ģ�⹤���·���һ����Ϣ��֪ͨCCPU OM ���ɽ��� */
#define APP_OM_BBP_DUMP_END_REQ                   0x8107

/* ����������� */
#define OM_APP_BBP_DUMP_END_CNF                   0x8110

/* BBP��ά�ɲ�EDMA�ϱ��쳣��ģ�ƹ��߷�����Ϣ֪ͨCCPU OM */
#define APP_OM_BBP_EDMA_ERR_REQ                   0x8113

/* ֪ͨ����EDMA ���� */
#define OM_APP_BBP_EDMA_ERR_CNF                   0x8114

/* BPP dump����ѡ�� */
#define APP_OM_BBP_DUMP_DUMP_REQ                  0x8115
#define OM_APP_BBP_DUMP_DUMP_CNF                  0x8116

/* ֪ͨ����C���Ѿ���λ */
#define OM_APP_CCORE_RESET_CNF                    0x8118

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  ö����    : OM_TOOL_CPUID_ENUM
  �ṹ˵��  : OM��TOOL CPU IDö��
1.��    ��  : 2012��08��08��
  ��    ��  : J00168360
  �޸�����  : V9R1 MSP��ֺͿ�ά�ɲ⿪����Ŀ�����ṹ
*****************************************************************************/
enum OM_TOOL_CPUID_ENUM
{
     OM_TOOL_RSV_ID,
     OM_TOOL_ACPU_ID,
     OM_TOOL_CCPU_ID,
     OM_TOOL_LDSP_ID,
     OM_TOOL_LBBP_ID,
     OM_TOOL_HIFI_ID,
     OM_TOOL_GUDSP_ID,
     OM_TOOL_TDSDSP_ID,
     OM_TOOL_TDSBBP_ID,
     OM_TOOL_MCU_ID,
     OM_TOOL_GPU_ID,
     OM_TOOL_GUBBP_ID,
     OM_TOOL_CPUID_BUTT
};
typedef VOS_UINT8 OM_TOOL_CPUID_ENUM_UINT8;

/*****************************************************************************
ö����    : BBP_DUMP_FIFO_WATERMARKER_ENUM
ö��˵��  : BBP����ˮ������

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_DUMP_WATERMARKER0 = 0,      /* 0����ʾˮ�����2 */
    BBP_DUMP_WATERMARKER1,          /* 1����ʾˮ�����4 */
    BBP_DUMP_WATERMARKER2,          /* 2����ʾˮ�����8 */
    BBP_DUMP_WATERMARKER3,          /* 3����ʾˮ�����16 */
    BBP_DUMP_WATERMARKER4,          /* 4����ʾˮ�����32 */
    BBP_DUMP_WATERMARKER5,          /* 5����ʾˮ�����64 */
    BBP_DUMP_WATERMARKER6,          /* 6����ʾˮ�����128 */
    BBP_DUMP_WATERMARKER_BUTT
}BBP_DUMP_FIFO_WATERMARKER_ENUM;

typedef VOS_UINT32 BBP_DUMP_FIFO_WATERMARKER_ENUM_U32;

/*****************************************************************************
ö����    : OM_BBP_STATUS_ENUM
ö��˵��  : BBP DBG��DUMP״̬

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    OM_BBP_START = 0,   /* ���� */
    OM_BBP_STOP,        /* ֹͣ */
    OM_BBP_BUTT
}OM_BBP_STATUS_ENUM;

typedef VOS_UINT32 OM_BBP_STATUS_ENUM_U32;

/*****************************************************************************
ö����    : OM_BBP_DUMP_MODE_ENUM
ö��˵��  : BBP DUMPģʽѡ��

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    OM_BBP_DUMP_MODE_W = 0,   /* Wģ */
    OM_BBP_DUMP_MODE_G1,      /* G1ģ */
    OM_BBP_DUMP_MODE_Rev,
    OM_BBP_DUMP_MODE_G2,      /* G2ģ */
    OM_BBP_DUMP_MODE_BUTT
}OM_BBP_DUMP_MODE_ENUM;

typedef VOS_UINT32 OM_BBP_DUMP_MODE_ENUM_U32;

/*****************************************************************************
ö����    : BBP_DBG_IF_SEL_ENUM
ö��˵��  : BBP DBG �ӿ�ѡ���ź�

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_IF_SEL_LOCALBUS = 0,    /* 0����ʾѡ��LocalBus�����������BBP������Ϣ */
    BBP_IF_SEL_WBBP_IMI,        /* 1����ʾѡ��WBBP IMI�ӿڣ��������WBBP������Ϣ */
    BBP_IF_SEL_GBBP_IMI,        /* 2����ʾѡ��GBBP IMI�ӿڣ��������GBBP������Ϣ */
    BBP_IF_SEL_REV,             /* 3���������� */
    BBP_IF_SEL_BUTT
}BBP_DBG_IF_SEL_ENUM;

typedef VOS_UINT32 BBP_DBG_IF_SEL_ENUM_U32;

/*****************************************************************************
ö����    : BBP_DBG_CLK_IN_SEL_EN_ENUM
ö��˵��  : BBP DBG����ʱ��ѡ��

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_DBG_CLK_IN_SEL0 = 0,    /* 0����ʾʹ��ģʽһʱ�ӣ� */
    BBP_DBG_CLK_IN_SEL1,        /* 1����ʾʹ��ģʽ��ʱ�ӣ� */
    BBP_DBG_CLK_IN_SEL2,        /* 2����ʾʹ��ģʽ��ʱ�ӣ� */
    BBP_DBG_CLK_IN_SEL_BUTT
}BBP_DBG_CLK_IN_SEL_EN_ENUM;

typedef VOS_UINT32 BBP_DBG_CLK_IN_SEL_ENUM_U32;

/*****************************************************************************
ö����    : BBP_DBG_FIFO_WATERMARKER_ENUM
ö��˵��  : BBP DBGˮ������

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_DBG_WATERMARKER0 = 0,   /* 0����ʾˮ�����2 */
    BBP_DBG_WATERMARKER1,       /* 1����ʾˮ�����4 */
    BBP_DBG_WATERMARKER2,       /* 2����ʾˮ�����8 */
    BBP_DBG_WATERMARKER3,       /* 3����ʾˮ�����16 */
    BBP_DBG_WATERMARKER4,       /* 4����ʾˮ�����32 */
    BBP_DBG_WATERMARKER5,       /* 5����ʾˮ�����64 */
    BBP_DBG_WATERMARKER_BUTT
}BBP_DBG_FIFO_WATERMARKER_ENUM;

typedef VOS_UINT32 BBP_DBG_FIFO_WATERMARKER_ENUM_U32;

/*****************************************************************************
ö����    : OM_APP_BBP_DUMP_CHOOSE_ENUM
ö��˵��  : BBP DUMP ��������ѡ��

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_DUMP_CHOOSE_YES = 0,    /* �û�ѡ�񵼳����� */
    BBP_DUMP_CHOOSE_NO,         /* �û��������� */
    BBP_DUMP_CHOOSE_BUTT
}OM_APP_BBP_DUMP_CHOOSE_ENUM;

typedef VOS_UINT32 OM_APP_BBP_DUMP_CHOOSE_ENUM_U32;

/*****************************************************************************
ö����    : OM_APP_BBP_DBG_ERRCODE_ENUM
ö��˵��  : BBP ��ά�ɲ���PCԼ���Ĵ�����

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_DBG_OK = 0,             /* �ɹ� */
    BBP_DBG_ALLOC_ERR,          /* ���价��bufferʧ�� */
    BBP_DBG_ALLOC_MSG_ERR,      /* ������Ϣ�ڴ�ʧ�� */
    BBP_DBG_INIT_SOCP_ERR,      /* ��ʼ��SOCPʧ�� */
    BBP_DBG_START_SOCP_ERR,     /* ʹ��SOCPͨ��ʧ�� */
    BBP_DBG_ENABLE_EDMA_ERR,    /* ʹ��EDMAͨ��ʧ�� */
    BBP_DBG_STOP_EDMA_ERR,      /* �ر�EDMAʧ�� */
    BBP_DBG_IF_SEL_ERR,         /* �ӿ�ѡ����Ϣ���� */
    BBP_DBG_CLK_IN_SEL_ERR,     /* ʱ��ѡ����Ϣ���� */
    BBP_DBG_INIT_EDMA_ERR,      /* ��ʼ��EDMAʧ�� */
    BBP_DBG_CONFIG_EDMA_ERR,    /* ����EDMAʧ�� */
    BBP_DBG_ALLOC_CYC_ERR,      /* ���价��buffʧ�� */
    BBP_DBG_GET_CONFIGADD_ERR,  /* ��ȡEDMA���õ�ַʧ�� */
    BBP_DBG_CREATE_SEM_ERR,     /* �����ź���ʧ�� */
    BBP_DBG_ADDR_ERR,           /* ��ַ��Χ����ȷ */
    BBP_DBG_MODE_ERR,           /* ģʽѡ����� */
    BBP_DBG_BUTT
}OM_APP_BBP_DBG_ERRCODE_ENUM;

typedef VOS_UINT32 OM_APP_BBP_DBG_ERRCODE_ENUM_U32;

/*****************************************************************************
ö����    : OM_APP_BBP_DUMP_ERRCODE_ENUM
ö��˵��  : BBP ������PCԼ���Ĵ�����

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    BBP_DUMP_OK = 0,              /* ���óɹ� */
    BBP_DUMP_MEM_SMALL,           /* �·����ɳ��ȹ�С */
    BBP_DUMP_MEM_BIG,             /* �·����ɳ���̫��*/
    BBP_DUMP_MEM_NOT_32KB,        /* ��32kB�������� */
    BBP_DUMP_ALLOC_MEM_ERR,       /* ���������ڴ�ʧ�� */
    BBP_DUMP_START_EDMA_ERR,      /* ����EDMAʧ�� */
    BBP_DUMP_ACORE_MSG_NULL,      /* A�˷�����MSGΪ�� */
    BBP_DUMP_END,                 /* ����ֹͣ */
    BBP_DUMP_READ_NV_ERR,         /* ��NVʧ�� */
    BBP_DUMP_DISABLE,             /* NV���ֹBBP����*/
    BBP_DUMP_STOP_EDMA_ERR,       /* ֹͣEDMAʧ�� */
    BBP_DUMP_MODE_ERR,            /* ģʽ���� */
    BBP_DUMP_WAITING_CNF_TIMEOUT, /* �ȴ��ظ���ʱ */
    BBP_DUMP_RCV_MSG_NOT_MATCH,   /* �յ���Ϣ��ƥ�� */
    BBP_DUMP_BUTT
}OM_APP_BBP_DUMP_ERRCODE_ENUM;

typedef VOS_UINT32 OM_APP_BBP_DUMP_ERRCODE_ENUM_U32;

/*****************************************************************************
ö����    : OM_APP_BBP_EDMA_ERR_ENUM
ö��˵��  : ��ʶEDMA�����ж����ɿ�ά�ɲ�����ģ��������ɲ�����

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    OM_BBP_DUMP_EDMA_ERR = 0, /* ����EDMA���� */
    OM_BBP_DBG_EDMA_ERR,      /* ��ά�ɲ�EDMA���� */
    OM_BBP_EDMA_ERR_BUTT
}OM_APP_BBP_EDMA_ERR_ENUM;

typedef VOS_UINT16 OM_APP_BBP_EDMA_ERR_ENUM_U16;

/*****************************************************************************
ö����    : OM_BBP_DUMP_ENABLE_ENUM
ö��˵��  : NV �б�ע�Ƿ�ʹ������

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
typedef enum
{
    OM_BBP_DUMP_DISABLE = 0, /* ��ֹ���� */
    OM_BBP_DUMP_ENABLE,      /* ʹ������ */
    OM_BBP_DUMP_BUTT
}OM_BBP_DUMP_ENABLE_ENUM;

typedef VOS_UINT16 OM_BBP_DUMP_ENABLE_ENUM_U16;

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
�ṹ��    : BBP_DBG_SOCP_INFO_STRU
�ṹ˵��  : BBP DBG SOCP������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulWriteDoneOk;      /* ��¼д�ɹ��Ĵ��� */
    VOS_UINT32  ulWriteDoneErr;     /* ��¼дʧ�ܵĴ��� */
    VOS_UINT32  ulGetWriteBuffErr;  /* ��¼��ȡдbufferʧ�ܵĴ��� */
    VOS_UINT32  ulBuffNotEnough;    /* ��¼�ռ䲻���Ĵ��� */
    VOS_UINT32  ulWriteBufSize;     /* ��¼ʣ��ռ��С */
}BBP_DBG_SOCP_INFO_STRU;

/*****************************************************************************
�ṹ��    : BBP_DBG_ERR_INFO_STRU
�ṹ˵��  : BBP DBG ������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usAllocErr;                                 /* ��¼�ڴ����ʧ�� */
    VOS_UINT16                  usInitSocpErr;                              /* ��¼��ʼ��SOCPʧ�� */
    VOS_UINT16                  usStartSocpErr;                             /* ��¼����SOCPʧ�� */
    VOS_UINT16                  usInitEdmaErr;                              /* ��¼EDMA��ʼ��ʧ�� */
    VOS_UINT16                  usConfigEdmaErr;                            /* ��¼EDMA����ʧ�� */
    VOS_UINT16                  usEdmaErrCode;                              /* ��¼EDMA����ʧ���жϴ��� */
    VOS_UINT16                  usAllocCycErr;                              /* ��¼����EDMAѭ��������ʧ�� */
    VOS_UINT16                  usGetConAddrErr;                            /* ��¼��ȡEDMA���õ�ַʧ��*/
    VOS_UINT16                  usStartEdmaErrNum;                          /* ��¼����EDMAʧ�ܵĴ��� */
    VOS_UINT16                  usStopEdmaErrNum;                           /* �ر�EDMAʧ�� */
    VOS_UINT16                  usCreateSemErr;                             /* �����ź���ʧ�� */
    VOS_UINT16                  usRev;
    BBP_DBG_SOCP_INFO_STRU      astBbpDbgSocpInfo[BBP_DBG_CODER_SRC_NUM];   /* ��¼SOCP�ĵ�����Ϣ */
}BBP_DBG_ERR_INFO_STRU;

/*****************************************************************************
�ṹ��    : BBP_DBG_INFO_STRU
�ṹ˵��  : BBP DBG ������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_INT                             lBbpEdmaChanID;                         /* ��¼��ά�ɲ�EDMAͨ���� */
    VOS_UINT32                          ulBbpDbgStatus;                         /* ��¼��ά�ɲ��״̬*/
    VOS_UINT32                          ulBbpErrCode;                           /* ��¼BBP��ά�ɲ��ʼ�������� */
    VOS_UINT32                          ulBbpSelfTaskNum;                       /* ��¼�Դ���������Ĵ��� */
    VOS_UINT32                          ulBbpEdmaCallBackNum;                   /* ��¼BBP��ά�ɲ�EDMA ��ɻص����� */
    VOS_UINT32                          ulPhyAddr;                              /* ��¼�����ڴ�������ַ */
    VOS_UINT32                          ulIndexValue;                           /* �ܰ��� */
    VOS_UINT32                          ulLastAddr;                             /* EDMAǰһ�ΰ�������ʼ��ַ */
    VOS_UINT32                          ulFlowNum;                              /* BBP����Ĵ��� */
}BBP_DBG_INFO_STRU;

/*****************************************************************************
�ṹ��    : BBP_DUMP_ERR_INFO_STRU
�ṹ˵��  : BBP DUMP ������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usInitEdmaErr;  /* ��ʼ��EDMAʧ�� */
    VOS_UINT16  usConfigEdmaErr;/* ����EDMAʧ�� */
    VOS_UINT16  usStartEdmaErr; /* ����EDMAʧ�� */
    VOS_UINT16  usEdmaErrCode;  /* �����ж����� */
    VOS_UINT16  usAllocMsgErr;  /* ������Ϣ�ռ�ʧ�� */
    VOS_UINT16  usCloseEdmaErr; /* �ر�EDMAʧ��*/
    VOS_UINT16  usStopEdmaErr;  /* ֹͣEDMAʧ�� */
    VOS_UINT16  usRev;
}BBP_DUMP_ERR_INFO_STRU;


/*****************************************************************************
�ṹ��    : BBP_DUMP_CHOOSE_STRU
�ṹ˵��  : BBP DUMP ��������ѡ��

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulChooseRelt;

}BBP_DUMP_CHOOSE_STRU;

/*****************************************************************************
�ṹ��    : OM_APP_BBP_DUMP_EDMA_STRU
�ṹ˵��  : BBP DUMP �ظ�PC���·���EDMA������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    OM_APP_BBP_DUMP_ERRCODE_ENUM_U32    enErr;      /* ��������������¼�����룬���ΪOK,���������һ������ */
    VOS_UINT32                          ulPhyAddr;
}OM_APP_BBP_DUMP_EDMA_STRU;

/*****************************************************************************
�ṹ��    : APP_OM_BBP_DUMP_SET_STRU
�ṹ˵��  : BBP DUMP PC�·���Wģ������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    OM_BBP_DUMP_MODE_ENUM_U32               enMode;             /* 0x5E820334��ʾ����Gģ����Wģ */
    VOS_UINT32                              ulDataLen;          /* 0x014c �ɼ����ݵĳ��� ��0��ʾ���޳�,PC�·�ʱ����KByteΪ��λ */

    /* Wģʽ���� start */
    BBP_DUMP_FIFO_WATERMARKER_ENUM_U32      enFifoWaterW;       /* 0x0154 ��ʾˮ����� */
    VOS_UINT32                              ulStartTimeW;       /* 0x0150 ������ʼλ�� */
    VOS_UINT32                              ulDataModelSelW;    /* 0x12dc DMA�������ݰ���ѡ�� */
    VOS_UINT32                              ulWtDbgEnW;         /* 0x96000 DBG���ݽ��й���ʹ��*/
    /* Wģʽ���� end */

    /* Gģʽ���� start */
    VOS_UINT32                              ulStartLowTimeG;    /* 0xf00c ������ʼλ�� */
    VOS_UINT32                              ulStartHiTimeG;     /* 0xf010 ������ʼλ�� */
    VOS_UINT32                              ulGenConfig;        /* 0xF004 Gģ�������� */
    /* Gģʽ���� end */
}APP_OM_BBP_DUMP_SET_STRU;

/*****************************************************************************
�ṹ��    : BBP_DUMP_GET_FIX_DDR_ADDR
�ṹ˵��  : ��ŵ������������ַ���ڴ��С

  1.��    ��   : 2014��10��08��
    ��    ��   : d00212987
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPhyAddr;    /* ��¼BBP����ʹ�õ�EDMAͨ���� */
    VOS_UINT32                          ulPhySize;    /* ��¼����״̬ */
}BBP_DUMP_GET_FIX_DDR_ADDR;

/*****************************************************************************
�ṹ��    : BBP_DUMP_MSG_STRU
�ṹ˵��  : ��ŵ������������ַ���ڴ��С

  1.��    ��   : 2014��10��08��
    ��    ��   : d00212987
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          ausRsv[3];
    BBP_DUMP_GET_FIX_DDR_ADDR           stDumpDdrInfo;
}BBP_DUMP_MSG_STRU;

/*****************************************************************************
�ṹ��    : APP_OM_BBP_DBG_SET_W_STRU
�ṹ˵��  : BBP ��ά�ɲ� PC�·���������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    OM_BBP_DUMP_MODE_ENUM_U32           enMode;             /* 0x5E820334��ʾ����Gģ����Wģ */
    OM_BBP_STATUS_ENUM_U32              enStatus;           /* �رջ��Ǵ�BBP DBG�ϱ� */
    BBP_DBG_IF_SEL_ENUM_U32             enBBPIfSel;         /* 0x008 ��ʾBBP�ӿ�ѡ���ź�*/
    BBP_DBG_CLK_IN_SEL_ENUM_U32         enClkInSel;         /* 0x010 DBG����ʱ��ѡ�� */
    VOS_UINT32                          ulTimeSel;          /* 0x01c �ӿ���Ϣʹ��ʱ���ѡ�� */
    VOS_UINT32                          ulMaskAddrStart0;   /* 0x020 ��һ�����ε�ַ��ʼλ�� */
    VOS_UINT32                          ulMaskAddrEnd0;     /* 0x024 ��һ�����ε�ַ����λ�� */
    VOS_UINT32                          ulMaskAddrStart1;   /* 0x028 �ڶ������ε�ַ��ʼλ�� */
    VOS_UINT32                          ulMaskAddrEnd1;     /* 0x02c �ڶ������ε�ַ����λ�� */
    VOS_UINT32                          ulMaskAddrStart2;   /* 0x030 ���������ε�ַ��ʼλ�� */
    VOS_UINT32                          ulMaskAddrEnd2;     /* 0x034 ���������ε�ַ����λ�� */
    VOS_UINT32                          ulMaskAddrStart3;   /* 0x038 ���Ķ����ε�ַ��ʼλ�� */
    VOS_UINT32                          ulMaskAddrEnd3;     /* 0x03c ���Ķ����ε�ַ����λ�� */
    BBP_DBG_FIFO_WATERMARKER_ENUM_U32   enFifoWater;        /* 0x040 DBG FIFOˮ��ѡ�� */
    VOS_UINT32                          ulDbgSwitch;        /* 0x044 DBG�ϱ���Ϣ���� �������Ϊ1����2������Ҫ���� 0x008��0x010*/
}APP_OM_BBP_DBG_SET_W_STRU;

/*****************************************************************************
�ṹ��    : BBP_DUMP_INFO_STRU
�ṹ˵��  : ��¼BBP������Ϣ

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_INT                             lEdmaChanID;    /* ��¼BBP����ʹ�õ�EDMAͨ���� */
    VOS_UINT16                          usDUMPStatus;   /* ��¼����״̬ */
    VOS_UINT16                          usDUMPDone;     /* EDMA�ж���ɻص� */
    VOS_UINT16                          usDUMPMode;     /* ��¼��ǰ���Ǹ�ģʽ */
    VOS_UINT16                          usRev;
    VOS_UINT32                          ulPhyAddr;      /* ��¼DRV�����DUMP�����ַ */
    VOS_UINT32                          ulPhySize;      /* ��¼DRV�����DUMP�ռ��С */
}BBP_DUMP_INFO_STRU;

/*****************************************************************************
�ṹ��    : BBP_EDMA_ERR_STRU
�ṹ˵��  : ����֪ͨACPU OM EDMA���������ж�

  1.��    ��   : 2012��11��06��
    ��    ��   : j00174725
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    OM_APP_BBP_EDMA_ERR_ENUM_U16        enEdmaErr;      /* ��¼�ǿ�ά�ɲ�����Ĵ��󣬻������ɲ����Ĵ��� */
    VOS_UINT16                          usRsv;
}BBP_EDMA_ERR_STRU;

/*****************************************************************************
�ṹ��    : APP_BBP_DUMP_REQ_MSG_STRU
�ṹ˵��  : DIAGģ��ת����PC��BBP DUMP�����͸����Ϣ�ṹ

  1.��    ��   : 2015��06��17��
    ��    ��   : H00300778
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;

    /* PC��͸����Ϣ�·������ݣ���CNF��Ϣ�����ȥ */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT8                           aucValue[4];
}APP_BBP_DUMP_REQ_MSG_STRU;

/*****************************************************************************
�ṹ��    : APP_BBP_DUMP_CNF_MSG_STRU
�ṹ˵��  : ��DIAGģ��ת����PC���͸����Ϣ�ṹ������ָʾPC��UE�Ѿ��յ�֮ǰ����
            BBP DUMP��Ϣ�Ѿ��յ�

  1.��    ��   : 2015��06��17��
    ��    ��   : H00300778
    �޸�����   : BBP��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;

    /* PC��͸����Ϣ�·������ݣ���CNF��Ϣ�����ȥ */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT32                          ulRslt;
}APP_BBP_DUMP_CNF_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID Om_CcpuBbpLogConfigCnf(
    APP_BBP_DUMP_REQ_MSG_STRU              *pstAppToOmMsg,
    VOS_UINT32                              ulMsgName,
    VOS_UINT32                              ulRslt);

extern VOS_VOID Om_CcpuBbpLogConfigMsgProc(MsgBlock *pRcvMsg);

extern VOS_UINT32 Om_ConfigBbpDump(
    APP_OM_BBP_DUMP_SET_STRU           *pstAppToOmMsg);

extern VOS_UINT32 Om_EndBbpDump(VOS_VOID);

extern VOS_UINT32 Om_ConfigBbpDbg(
    APP_OM_BBP_DBG_SET_W_STRU          *pstAppToOmMsg);

extern VOS_UINT32 Om_SendEdmaErrToPc(
    BBP_EDMA_ERR_STRU                  *pstEdmaErr,
    VOS_UINT16                          usReturnPrimId);

extern VOS_UINT32 Om_SendQueryDumpMsg(VOS_VOID);

extern VOS_VOID Om_BbpDumpAddrQueryMsgProc(MsgBlock *pMsg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


