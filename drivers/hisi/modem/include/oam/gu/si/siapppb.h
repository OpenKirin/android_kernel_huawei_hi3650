

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : Siapppb.h
Author      : H59254
Version     : V200R001
Date        : 2008-10-10
Description : �绰���ĵ�ͷ�ļ�
History     :
History     :
1.��    ��  : 2006��11��14��
  ��    ��  : H59254
  �޸�����  : Create
************************************************************************/

#ifndef __SIAPPPB_H__
#define __SIAPPPB_H__

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

/**/
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "sitypedef.h"
#include "vos.h"
#include "TafOamInterface.h"
#include "UsimPsInterface.h"
#include "omnvinterface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define SI_PB_PHONENUM_MAX_LEN          40    /*���ؽṹ�к������󳤶ȣ���ָ�ֽ���*/
#define SI_PB_ALPHATAG_MAX_LEN          242   /*���ؽṹ�����ֵ���󳤶ȣ���ָ�ֽ���*/

#define SI_PB_EMAIL_MAX_LEN             64    /*���ؽṹ���ʼ�����󳤶ȣ���ָ�ֽ���*/

#define SI_PB_NUMBER_LEN                (20)  /* Э��ջ�·���BCD���볤�� */

/* ���ױ��Ƕ��Ƴ���5������ʱ�޸�Ϊ֧��16�� */
#define USIM_MAX_ECC_RECORDS    16
#define USIM_ECC_LEN            3

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

typedef SI_UINT32  SI_PB_AlPHATAG_TYPE;
#define SI_PB_ALPHATAG_TYPE_UCS2_80     0x80            /*���ֵı������ͣ�16-bit universal multiple-octet coded character set (ISO/IEC10646 [32])*/
#define SI_PB_ALPHATAG_TYPE_UCS2_81     0x81
#define SI_PB_ALPHATAG_TYPE_UCS2_82     0x82
#define SI_PB_ALPHATAG_TYPE_GSM         0x00            /*���ֵı������ͣ�GSM 7 bit default alphabet (3GPP TS 23.038)*/
#define SI_PB_ALPHATAG_TYPE_UCS2        0x80

#define SI_PB_CONTENT_VALID             0x01
#define SI_PB_CONTENT_INVALID           0x00

#define SI_PB_LAST_TAG_TRUE             1

#define SI_PB_ALPHATAG_TRANSFER_TAG     0x1B

enum PB_FDN_CHECK_RSLT_ENUM
{
    PB_FDN_CHECK_SUCC                   = 0,
    PB_FDN_CHECK_NUM1_FAIL              = 1,
    PB_FDN_CHECK_NUM2_FAIL              = 2,
    PB_FDN_CHECK_BOTH_NUM_FAIL          = 3,
    PB_FDN_CHECK_RSLT_BUTT
};
typedef VOS_UINT32 PB_FDN_CHECK_RSLT_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : SI_PB_REQ_ENUM_UINT32
 �ṹ˵��  : PBģ��������Ϣ����
*****************************************************************************/
enum SI_PB_REQ_ENUM
{
    SI_PB_READ_REQ                      = 0,        /* ���뱾��ȡ����           */
    SI_PB_SET_REQ                       = 1,        /* ���뱾��������           */
    SI_PB_MODIFY_REQ                    = 2,        /* ���뱾�޸�����           */
    SI_PB_DELETE_REQ                    = 3,        /* ���뱾ɾ������           */
    SI_PB_QUERY_REQ                     = 4,        /* ���뱾��ѯ����           */
    SI_PB_ADD_REQ                       = 5,        /* ���뱾�������           */
    SI_PB_SEARCH_REQ                    = 6,        /* ���뱾��������           */
    SI_PB_SREAD_REQ                     = 7,        /* ���Ϻ��뱾��ȡ����       */
    SI_PB_SMODIFY_REQ                   = 8,        /* ���Ϻ��뱾�޸�����       */
    SI_PB_SADD_REQ                      = 9,        /* ���Ϻ��뱾�������       */
    SI_PB_UPDATE_AGOBAL                 = 10,       /* ����Acpu��ȫ�ֱ�������   */
    SI_PB_UPDATE_CURPB                  = 11,       /* ���µ�ǰ�绰������       */
    SI_PB_FDN_CHECK_REQ                 = 12,       /* FDN����ƥ������          */
    SI_PB_ECALL_QRY_REQ                 = 13,       /* ECALL����ƥ������          */
    SI_PB_REQ_BUTT
};
typedef SI_UINT32 SI_PB_REQ_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : SI_PB_CNF_ENUM_UINT32
 �ṹ˵��  : PBģ��ظ����ϱ���Ϣ����
*****************************************************************************/
enum SI_PB_CNF_ENUM
{
    SI_PB_EVENT_INFO_IND                = 0,    /* ���뱾��Ϣ�¼��ϱ�           */
    SI_PB_EVENT_READ_CNF                = 1,    /* ���뱾��ȡ����ظ�           */
    SI_PB_EVENT_QUERY_CNF               = 2,    /* ���뱾��ѯ����ظ�           */
    SI_PB_EVENT_SET_CNF                 = 3,    /* ���뱾���ý���ظ�           */
    SI_PB_EVENT_ADD_CNF                 = 4,    /* ���뱾��ӽ���ظ�           */
    SI_PB_EVENT_MODIFY_CNF              = 5,    /* ���뱾�޸Ľ���ظ�           */
    SI_PB_EVENT_DELETE_CNF              = 6,    /* ���뱾ɾ������ظ�           */
    SI_PB_EVENT_SEARCH_CNF              = 7,    /* ���뱾��������ظ�           */
    SI_PB_EVENT_SREAD_CNF               = 8,    /* ���Ϻ��뱾��ȡ����ظ�       */
    SI_PB_EVENT_SADD_CNF                = 9,    /* ���Ϻ��뱾��ӽ���ظ�       */
    SI_PB_EVENT_SMODIFY_CNF             = 10,   /* ���Ϻ��뱾�޸Ľ���ظ�       */
    SI_PB_EVENT_FDNCHECK_CNF            = 11,   /* FDN����ƥ�����ظ�          */
    SI_PB_EVENT_ECALLQUERY_CNF          = 12,   /* ECALL�����ѯ����ظ�        */
    SI_PB_EVENT_ECALLINIT_IND           = 13,   /* ECALL�����ʼ������ϱ�      */
    SI_PB_EVENT_BUTT
};

typedef VOS_UINT32 SI_PB_CNF_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : SI_PB_STORAGE_ENUM_UINT32
 �ṹ˵��  : PBģ��洢������
*****************************************************************************/
enum SI_PB_STORAGE_ENUM
{
    SI_PB_STORAGE_UNSPECIFIED           = 0,       /*�洢�����Ͳ�ָ������������ȷ����������*/
    SI_PB_STORAGE_SM                    = 1,       /*�洢������ΪADN*/
    SI_PB_STORAGE_ME                    = 2,       /*�洢������ΪNV*/
    SI_PB_STORAGE_BOTH                  = 3,       /*�洢������ΪADN��NV*/
    SI_PB_STORAGE_ON                    = 4,       /*�洢������ΪMSISDN*/
    SI_PB_STORAGE_FD                    = 5,       /*�洢������ΪFDN*/
    SI_PB_STORAGE_EC                    = 6,       /*�洢������ΪECC*/
    SI_PB_STORAGE_BD                    = 7,       /*�洢������ΪBDN*/
    SI_PB_STORAGE_SD                    = 8,       /*�洢������ΪSDN*/
    SI_PB_STORAGE_BUTT
};

typedef VOS_UINT32 SI_PB_STORAGE_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 STRUCT����
*****************************************************************************/
/* �绰����������ö�� */
enum PB_NUMBER_TYPE_ENUM
{
    PB_NUMBER_TYPE_NORMAL        = 129,            /* ��ͨ�������� */
    PB_NUMBER_TYPE_INTERNATIONAL = 145,            /* ���ʺ������� */
    PB_NUMBER_TYPE_BUTT
};

/*�����ݿ���Ʒ֧�ֵ绰����ѯ����*/
typedef struct
{
    SI_UINT16                InUsedNum;           /*��ʹ�ü�¼��Ŀ*/
    SI_UINT16                TotalNum;            /*�ܼ�¼��Ŀ*/
    SI_UINT16                TextLen;             /*֧�ֵ�text����󳤶�*/
    SI_UINT16                NumLen;              /*֧�ֵ�number����󳤶�*/
    SI_UINT16                EMAILTextLen;        /*Emai����*/
    SI_UINT16                ANRNumberLen;        /*ANR���볤��*/
}SI_PB_EVENT_QUERY_CNF_STRU;

typedef struct
{
    SI_UINT16                ADNRecordNum ;              /*ADN��¼����*/
    SI_UINT16                ADNTextLen ;                /*ADN�����ֶγ���*/
    SI_UINT16                ADNNumberLen;              /*ADN���볤��*/
    SI_UINT16                FDNRecordNum ;              /*FDN��¼����*/
    SI_UINT16                FDNTextLen ;                /*FDN�����ֶγ���*/
    SI_UINT16                FDNNumberLen;              /*FDN���볤��*/
    SI_UINT16                BDNRecordNum ;              /*BDN��¼����*/
    SI_UINT16                BDNTextLen ;                /*BDN�����ֶγ���*/
    SI_UINT16                BDNNumberLen;              /*BDN���볤��*/
    SI_UINT16                MSISDNRecordNum;            /*MSISDN��¼����*/
    SI_UINT16                MSISDNTextLen ;             /*MSISDN�����ֶγ���*/
    SI_UINT16                MSISDNNumberLen;           /*MSISDN���볤��*/
    SI_UINT16                EMAILTextLen;              /*EMAIL����*/
    SI_UINT16                ANRNumberLen;              /*ANR���볤��*/
    SI_UINT16                FdnState;                   /*FDNʹ��״̬*/
    SI_UINT16                BdnState;                   /*BDNʹ��״̬*/
    SI_UINT16                CardType;                   /*�����ͣ�0 SIM����1 USIM��*/
}SI_PB_EVENT_INFO_IND_STRU;

typedef struct
{
    SI_UINT16                InUsedNum;           /*��ʹ�ü�¼��Ŀ*/
    SI_UINT16                TotalNum;            /*�ܼ�¼��Ŀ*/
    SI_UINT16                TextLen;             /*֧�ֵ�text����󳤶�*/
    SI_UINT16                NumLen;              /*֧�ֵ�number����󳤶�*/
    SI_UINT16                EMAILTextLen;        /*Emai����*/
    SI_UINT16                ANRNumberLen;        /*ANR���볤��*/
}SI_PB_EVENT_SET_CNF_STRU;

typedef struct
{
    SI_UINT8                 NumberType;                      /*�������ͣ�145��129*/
    SI_UINT8                 NumberLength;                    /*���볤�ȣ��ǲ�����NumberType�ĳ���*/
    SI_UINT8                 Number[SI_PB_PHONENUM_MAX_LEN+2];  /*���룬����ASCII�ı��뷽ʽ*/
}SI_PB_ADDITION_NUM_STRU;

typedef struct
{
    SI_UINT32                EmailLen;                        /*Email����*/
    SI_UINT8                 Email[SI_PB_EMAIL_MAX_LEN];      /*Email������ASCII�ı��뷽ʽ*/
}SI_PB_EMAIL_STRU;

typedef struct
{
    SI_UINT16                Index;                           /*��¼��index*/
    SI_UINT8                 AlphaTag[SI_PB_ALPHATAG_MAX_LEN];/*��¼�������ֶΰ�����������*/
    SI_UINT8                 ucAlphaTagLength;                /*���ֳ���, �ֽ����������UNICODE���������������ָʾ�ֽ�*/
    SI_UINT8                 NumberType;                      /*�������ͣ�145��129*/
    SI_UINT8                 NumberLength;                    /*���볤�ȣ��ǲ�����NumberType�ĳ���*/
    SI_UINT8                 ValidFlag;                       /*��¼��Ч��־*/
    SI_UINT8                 Number[SI_PB_PHONENUM_MAX_LEN];  /*����1������ASCII�ı��뷽ʽ*/
    SI_PB_AlPHATAG_TYPE      AlphaTagType;                    /*��������*/
    SI_PB_ADDITION_NUM_STRU  AdditionNumber[3];
    SI_PB_EMAIL_STRU         Email;
}SI_PB_RECORD_STRU;

typedef struct
{
    SI_UINT16                RecordNum;   /*��¼����Ŀ*/
    SI_UINT16                Rsv;
    SI_PB_RECORD_STRU        PBRecord; /*��һ����¼��*/
}SI_PB_EVENT_READ_CNF_STRU;

typedef struct
{
    SI_UINT16                RecordNum;   /*��¼����Ŀ*/
    SI_UINT16                Rsv;
    SI_PB_RECORD_STRU        PBRecord; /*��һ����¼��*/
}SI_PB_EVENT_SEARCH_CNF_STRU;

typedef struct
{
    SI_UINT16                Index; /*������ӵļ�¼������*/
}SI_PB_EVENT_ADD_CNF_STRU;

typedef struct
{
    SI_UINT16                ClientId;
    SI_UINT8                 OpId;
    SI_UINT8                 Reserve;
    SI_UINT32                PBEventType;
    SI_UINT32                PBError;
    SI_PB_STORATE_TYPE       Storage;
    SI_UINT32                PBLastTag;
    union
    {
        SI_PB_EVENT_QUERY_CNF_STRU      PBQueryCnf ;
        SI_PB_EVENT_INFO_IND_STRU       PBInfoInd ;
        SI_PB_EVENT_SET_CNF_STRU        PBSetCnf ;
        SI_PB_EVENT_READ_CNF_STRU       PBReadCnf ;
        SI_PB_EVENT_ADD_CNF_STRU        PBAddCnf ;
        SI_PB_EVENT_SEARCH_CNF_STRU     PBSearchCnf;
    }PBEvent;
}SI_PB_EVENT_INFO_STRU;

typedef struct
{
    SI_BOOL                  bESC;                       /* ESC�ֽ��Ƿ���ڱ�־ */
    SI_UINT8                 aucEccCode[USIM_ECC_LEN];   /* Emergency Call Code */
    SI_UINT8                 ucESC;                      /* ESC�ֶ�ֵ */
    SI_UINT8                 ucLen;                      /* ESC�ַ����� */
    SI_UINT8                 AlphaIdentifier[253];        /* ESC�ַ����� */
    SI_UINT8                 aucReserved[2];
}SI_PB_ECC_RECORD_STRU;

typedef struct
{
    SI_BOOL                  bEccExists;         /* ECC�ļ��Ƿ���� */
    SI_UINT32                ulReocrdNum;        /* ECC�н������к���ĸ��� */
    SI_PB_ECC_RECORD_STRU    astEccRecord[USIM_MAX_ECC_RECORDS];
}SI_PB_ECC_DATA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ��   */
}PBMsgBlock;


/*****************************************************************************
 �ṹ��    : SI_PB_FDN_NUM_STRU
 �ṹ˵��  : FDN����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulNum1Len;
    VOS_UINT8                   aucNum1[SI_PB_NUMBER_LEN];
    VOS_UINT32                  ulNum2Len;
    VOS_UINT8                   aucNum2[SI_PB_NUMBER_LEN];
}SI_PB_FDN_NUM_STRU;

/*****************************************************************************
 �ṹ��    : SI_PB_FDN_CHECK_REQ_STRU
 �ṹ˵��  : FDN����ƥ��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��Ϣ�� */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT32                          ulSendPara;
    VOS_UINT32                          ulContextIndex;
    SI_PB_FDN_NUM_STRU                  stFDNNum;           /* FDN����ṹ */
}SI_PB_FDN_CHECK_REQ_STRU;

/*****************************************************************************
 �ṹ��    : SI_PB_FDN_CHECK_REQ_STRU
 �ṹ˵��  : FDN���������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��Ϣ�� */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;          /* APP���� */
    VOS_UINT32                          ulSendPara;         /* ͸������ */
    VOS_UINT32                          ulContextIndex;     /* indexֵ */
    PB_FDN_CHECK_RSLT_ENUM_UINT32       enResult;           /* ��֤��� */
}PB_FDN_CHECK_CNF_STRU;

/*****************************************************************************
�ṹ��    : SI_PB_ECALL_QRY_REQ_STRU
�ṹ˵��  : Ecall��ȡFDN��SDN��¼������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��Ϣ�� */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;          /* APP���� */
    SI_PB_STORAGE_ENUM_UINT32           enStorage;          /* �洢�����ͣ�ֻ����SI_PB_STORAGE_FD��SI_PB_STORAGE_SD */
    VOS_UINT8                           ucListLen;          /* ��ȡ��¼�����ĳ��� */
    VOS_UINT8                           aucList[3];         /* ��ȡ��¼���������� */
}SI_PB_ECALLQRY_REQ_STRU;


/*****************************************************************************
�ṹ��    : SI_PB_ECALL_NUM_STRU
�ṹ˵��  : ecall test/recfg number��Ϣ�ṹ��
1.  ��    ��   : 2014��04��25��
    ��    ��   : h59254
    �޸�����   : Creat
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTon;              /* �������� */
    VOS_UINT8                           ucLength;           /* BCD��ĳ��� */
    VOS_UINT8                           ucIndex;            /* ��1��ʼ */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           aucCallNumber[SI_PB_PHONENUM_MAX_LEN/2];
}SI_PB_ECALL_NUM_STRU;


/*****************************************************************************
�ṹ��    : SI_PB_QRY_ECALL_NUMBER_CNF_STRU
�ṹ˵��  : ��ѯECALL�ĺ���ظ�
1.  ��    ��   : 2014��04��25��
    ��    ��   : h59254
    �޸�����   : Creat
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��Ϣ�� */
    VOS_UINT32                          ulRslt;             /* VOS_OK: ��ȡ�ɹ�;VOS_ERR:��ȡʧ��(������������Ƿ����ȡʧ��) */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;          /* APP���� */
    SI_PB_STORAGE_ENUM_UINT32           enStorage;          /* �绰������,��ʱ��ָ��SDN��FDN */
    VOS_UINT32                          ulRecordNum;        /* ��ȡ�绰����¼���ܼ�¼�� */
    SI_PB_ECALL_NUM_STRU                astECallNumber[2];
}SI_PB_ECALLQRY_CNF_STRU;

/*****************************************************************************
�ṹ��    : SI_PB_ECALL_INIT_IND_STRU
�ṹ˵��  : ECALL�����ʼ��ָʾ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* ��Ϣ�� */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;          /* APP���� */
    VOS_UINT16                          usFdnRecordNum;     /* FDN�ܼ�¼�� */
    VOS_UINT16                          usSdnRecordNum;     /* SDN�ܼ�¼�� */
}SI_PB_ECALLINIT_IND_STRU;

/*****************************************************************************
  5 ��������
*****************************************************************************/

extern SI_UINT32 SI_PB_Read(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_UINT16 Index1,SI_UINT16 Index2);

extern SI_UINT32 SI_PB_Set(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage);

extern SI_UINT32 SI_PB_Modify(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU* pRecord) ;

extern SI_UINT32 SI_PB_SModify(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU* pRecord);

extern SI_UINT32 SI_PB_SRead(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage, SI_UINT16 Index1,SI_UINT16 Index2);

extern SI_UINT32 SI_PB_Delete(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_UINT16 Index);

extern SI_UINT32 SI_PB_Add(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU *pRecord);

extern SI_UINT32 SI_PB_SAdd(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU *pRecord);

extern SI_UINT32 SI_PB_Search(SI_UINT16 ClientId,  SI_UINT8 OpId, SI_PB_STORATE_TYPE Storage, SI_UINT8 ucLength, SI_UINT8 *pucContent);

extern SI_UINT32 SI_PB_Query(SI_UINT16 ClientId,SI_UINT8 OpId);

extern VOS_UINT32 SI_PB_GetEccNumber(SI_PB_ECC_DATA_STRU *pstEccData);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 SI_PB_GetXeccNumber(SI_PB_ECC_DATA_STRU *pstEccData);
#endif

extern VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);

extern VOS_VOID SI_PB_MemSet(VOS_UINT8 ucLen, VOS_UINT8 ucValue,VOS_UINT8 *pucMem);

extern VOS_VOID   SI_PB_PidMsgProc(struct MsgCB *pstPBMsg);

extern VOS_UINT32 SI_PB_GetStorateType(VOS_VOID);

extern VOS_UINT32 SI_PB_GetSPBFlag(VOS_VOID);

/*������ӿ�����*/

/*****************************************************************************
�� �� ��  :SI_PB_GetEccNumber_Instance
��������  :��ȡECC����
�������  :enModemID:Modem ID
�������  :pstEccData:ECC�������ݽṹ
�޶���¼  :
1. ��    ��   : 2013��5��27��
   ��    ��   : h59254
   �޸�����   : Creat
*****************************************************************************/
extern VOS_UINT32 SI_PB_GetEccNumber_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_PB_ECC_DATA_STRU                *pstEccData);




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

#endif /* end of SiAppPB.h */

