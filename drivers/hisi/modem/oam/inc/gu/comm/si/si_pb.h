

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SI_PB.h
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
#ifndef __SI_PB_H__
#define __SI_PB_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "siapppb.h"

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "pamom.h"
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "pamappom.h"
#endif

#include "UsimPsInterface.h"
#include "omnvinterface.h"
#include "msp_diag_comm.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SI_PB_XDN_SPACE            (60000)
#define SI_PB_XDN_SUPPORT_NUM      (1000)

#define SI_PB_ADNMAX            10 /*���֧��ADN�绰������*/
#define SI_PB_ANRMAX            3
#define SI_PB_MAX_NUMBER        7  /*���֧�ֵ绰������*/
#define SI_PB_MAX_XDN           16 /*��ʼ��ʱ֧�ֵĵ绰������*/
#define SI_PB_ANR_MAX           3  /*ANR�ļ��ĸ���*/

#define SI_PB_FILE_NOT_EXIST   0
#define SI_PB_FILE_EXIST       1

#define SI_PB_EXCEPT_NAME       14
#define SI_PB_ECC_EXCEPT_NAME   4
#define SI_PB_NUM_LEN           20
#define SI_PB_ECC_LEN           3

#define SI_PB_ANR_LEN           17
#define SI_PB_EXT_LEN           13
#define SI_PB_EXT_NUM_LEN       20
#define SI_PB_NUM_WITHEXT       (SI_PB_NUM_LEN + SI_PB_EXT_NUM_LEN)
#define SI_PB_ADDITIONAL_NUM    2

#define SI_TAGNOTFOUND          0xFFFFFFFF

#define SI_CLEARALL             0x01
#define SI_CLEARXDN             0x02
#define SI_CLEARSPB             0x03

#define EFADNDO_TAG             0xC0
#define EFIAPDO_TAG             0xC1
#define EFEXT1DO_TAG            0xC2
#define EFSNEDO_TAG             0xC3
#define EFANRDO_TAG             0xC4
#define EFPBCDO_TAG             0xC5
#define EFGRPDO_TAG             0xC6
#define EFAASDO_TAG             0xC7
#define EFGASDO_TAG             0xC8
#define EFUIDDO_TAG             0xC9
#define EFEMAILDO_TAG           0xCA
#define EFCCP1DO_TAG            0xCB

#define EFPBR                   0x4F30
#define SIM_EFADN               0x6F3A
#define EFSDN                   0x6F49

#define EFEXT1                  0x6F4A      /* ����ADN�ļ� */
#define EFEXT2                  0x6F4B      /* ����FDN�ļ� */
#define EFEXT3                  0x6F4C      /* ����SDN�ļ� */
#define EFEXT4_USIM             0x6F55      /* ����BDN�ļ� */
#define EFEXT4_SIM              0x6F4E      /* ����BDN�ļ� */
#define EFEXT5                  0x6F4E      /* ��������USIM���е�MSISDN�ļ� */
#define EFEXT6                  0x6FC8      /* ����MBDN�ļ� */
#define EFEXT7                  0x6FCC      /* ����CFIS�ļ� */

#if(OSA_CPU_ACPU == VOS_OSA_CPU)
#define PB_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(ACPU_PID_PB), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define PB_INFO_LOG(string)            (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),ACPU_PID_PB, __FILE__, __LINE__, "%s", string)
#define PB_NORMAL_LOG(string)          (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),ACPU_PID_PB, __FILE__, __LINE__, "%s", string)
#define PB_WARNING_LOG(string)         (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),ACPU_PID_PB, __FILE__, __LINE__, "%s", string)
#define PB_ERROR_LOG(string)           (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),ACPU_PID_PB, __FILE__, __LINE__, "%s", string)

#define PB_INFO1_LOG(string, para1)    (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),ACPU_PID_PB, __FILE__, __LINE__, "%s,%d", string, para1)
#define PB_NORMAL1_LOG(string, para1)  (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),ACPU_PID_PB, __FILE__, __LINE__, "%s,%d", string, para1)
#define PB_WARNING1_LOG(string, para1) (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),ACPU_PID_PB, __FILE__, __LINE__, "%s,%d", string, para1)
#define PB_ERROR1_LOG(string, para1)   (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),ACPU_PID_PB, __FILE__, __LINE__, "%s,%d", string, para1)
#endif

#if(OSA_CPU_CCPU == VOS_OSA_CPU)
#define PB_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(MAPS_PB_PID), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define PB_INFO_LOG(string)            (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s", string)
#define PB_NORMAL_LOG(string)          (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s", string)
#define PB_WARNING_LOG(string)         (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),MAPS_PB_PID, __FILE__, __LINE__, "%s", string)
#define PB_ERROR_LOG(string)           (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),MAPS_PB_PID, __FILE__, __LINE__, "%s", string)

#define PB_INFO1_LOG(string, para1)    (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define PB_NORMAL1_LOG(string, para1)  (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define PB_WARNING1_LOG(string, para1) (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#define PB_ERROR1_LOG(string, para1)   (VOS_VOID)DIAG_LogReport(PB_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1)
#endif

#if(VOS_WIN32 == VOS_OS_VER)
#define PB_MALLOC(LENGTH)               VOS_MemAlloc(MAPS_PB_PID,DYNAMIC_MEM_PT,LENGTH)
#define PB_FREE(MEMADDR)                VOS_MemFree(MAPS_PB_PID, MEMADDR)
#else
#define PB_MALLOC(LENGTH)               mdrv_smalloc((VOS_UINT32)LENGTH, MEM_ICC_DDR_POOL)
#define PB_FREE(MEMADDR)                mdrv_sfree(MEMADDR)
#endif

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/


enum SI_PB_INIT_STEP_ENUM
{
    PB_INIT_PB_STATUS = 0,      /*��ʼ�������绰���ļ���״̬*/
    PB_INIT_EFPBR,              /*��ʼ��PBR����*/
    PB_INIT_XDN_SPACE,          /*��ʼ��XDN�ռ�*/
    PB_INIT_ANR_SPACE,          /*��ʼ��ANR�ռ�*/
    PB_INIT_EML_SPACE,          /*��ʼ��Email�ռ�*/
    PB_INIT_IAP_SPACE,          /*��ʼ��IAP�ռ�*/
    PB_INIT_EXT_SPACE,          /*��ʼ��EXT�ռ�*/
    PB_INIT_IAP_CONTENT,        /*��ʼ��IAP��Email��¼��AND��¼�Ķ�Ӧ��ϵ*/
    PB_INIT_EML_CONTENT,        /*��ʼ��Email����*/
    PB_INIT_ANR_CONTENT,        /*��ʼ��ANR����*/
    PB_INIT_EXTR_CONTENT,       /*��ʼ��ANR EXT����*/
    PB_INIT_XDN_CONTENT,        /*��ʼ��XDN����*/
    PB_INIT_EXT_CONTENT,        /*��ʼ��EXT����*/
    PB_INIT_PBC_CONTENT,        /* ��ʼ��PBC���� */
    PB_INIT_IAP_SEARCH,         /* ����IAP��¼ */
    PB_INIT_IAP_CONTENT2,       /* ���ݲ��ҵĽ������ʼ��IAP�ļ������� */
    PB_INIT_EML_SEARCH,         /* ����EMAIL��¼ */
    PB_INIT_EML_CONTENT2,       /* ���ݲ��ҵĽ������ʼ��EMAIL�ļ������� */
    PB_INIT_ANR_SEARCH,         /* ����ANR��¼ */
    PB_INIT_ANR_CONTENT2,       /* ���ݲ��ҵĽ������ʼ��ANR�ļ������� */
    PB_INIT_XDN_SEARCH,         /* ����XDN��¼ */
    PB_INIT_XDN_CONTENT2,       /* ���ݲ��ҵĽ������ʼ��XDN�ļ������� */
    PB_INIT_PBC_SEARCH,         /* ����PBC��¼ */
    PB_INIT_PBC_CONTENT2,       /* ���ݲ��ҵĽ������ʼ��PBC�ļ������� */
    PB_INIT_SYNCH,              /*3G�绰��ͬ��*/
    PB_INIT_INFO_APP,           /*�ص��ϱ�*/
    PB_INIT_FINISHED,           /*��ʼ������*/
    PB_INIT_BUTT
};
typedef VOS_UINT32  SI_PB_INIT_STEP_ENUM_UINT32;

enum SI_PB_SEARCH_ENUM
{
    PB_SEARCH_DISABLE   = 0,
    PB_SEARCH_ENABLE    = 1,
    PB_SEARCH_BUTT
};
typedef VOS_UINT32 SI_PB_SEARCH_ENUM_UINT32;

enum SI_PB_LOCK_ENUM
{
    PB_UNLOCK = 0,
    PB_LOCKED = 1,
    PB_LOCK_BUTT
};
typedef VOS_UINT32  SI_PB_LOCK_ENUM_UINT32;

enum SI_PB_FILE_TYPE_ENUM
{
    PB_FILE_UNKNOWN = 0,
    PB_FILE_TYPE1   = 0xA8,
    PB_FILE_TYPE2   = 0xA9,
    PB_FILE_TYPE3   = 0xAA,
    PB_FILE_BUTT
};
typedef VOS_UINT32 SI_PB_FILE_TYPE_ENUM_UINT32;

/* ����Ķ���Ҫ��SI_PB_STORAGE_SM���Ķ��屣��һ�� */
enum SI_PB_TYPE_ENUM
{
    PB_ADN            = 1,
    PB_MISDN          = 4,
    PB_FDN            = 5,
    PB_ECC            = 6,
    PB_BDN            = 7,
    PB_SDN            = 8,
    PB_XECC           = 9,
    PB_NULL           = 0xFF,
    PB_TYPE_BUTT
};
typedef VOS_UINT32  SI_PB_TYPE_ENUM_UINT32;

enum SI_PB_CONTENT_TYPE_ENUM
{
    PB_ECC_CONTENT    = 0,
    PB_ADN_CONTENT    = 1,
    PB_FDN_CONTENT    = 2,
    PB_BDN_CONTENT    = 3,
    PB_MSISDN_CONTENT = 4,
    PB_SDN_CONTENT    = 5,
    PB_XECC_CONTENT   = 6,
    PB_CONTENT_BUTT
};
typedef VOS_UINT32  SI_PB_CONTENT_TYPE_ENUM_UINT32;

enum SI_PB_SEND_REQ_STATUS_ENUM
{
    PB_REQ_SEND     = 0,
    PB_REQ_NOT_SEND = 1,
    PB_SEND_REQ_BUTT
};
typedef VOS_UINT32 SI_PB_SEND_REQ_STATUS_ENUM_UINT32;

enum SI_PB_INIT_STATE_ENUM
{
    PB_NOT_INITIALISED = 0,                       /*δ��ʼ�����*/
    PB_INITIALISED     = 1,                       /*�ѳ�ʼ�����*/
    PB_FILE_NOT_EXIST  = 2,                       /*�绰���ļ�������*/
    PB_INIT_STATE_BUTT
};
typedef VOS_UINT8  SI_PB_INIT_STATE_ENUM_UINT8;

enum SI_PB_ACTIVE_STATE_ENUM
{
    SI_PB_DEACTIVE   = USIMM_EFSTATUS_DEACTIVE,
    SI_PB_ACTIVE     = USIMM_EFSTATUS_ACTIVE,
    SI_PB_ACTIVE_STATE_BUTT
};
typedef VOS_UINT32 SI_PB_ACTIVE_STATE_ENUM_UINT32;

enum SI_PB_REFRESH_ENUM
{
    SI_PB_REFRESH_ALL  = 0,
    SI_PB_REFRESH_FILE = 1,
    SI_PB_REFRESH_BUTT
};
typedef VOS_UINT32 SI_PB_REFRESH_ENUM_UNIT32;

enum SI_PB_INIT_STATUS_ENUM
{
    SI_PB_INIT_STATUS_OK      = 0,
    SI_PB_INIT_PBMALLOC_FAIL  = 1,
    SI_PB_INIT_SPBMALLOC_FAIL = 2,
    SI_PB_INIT_PBTYPE_UNKOWN  = 3,
    SI_PB_INIT_USIMPBCNF_ERR  = 4,
    SI_PB_INIT_USIMSPBCNF_ERR = 5,
    SI_PB_INIT_RECORD_REMAIN  = 6,
    SI_PB_INIT_EXT_RECORD     = 7,
    SI_PB_INIT_EXT_ERR        = 8,
    SI_PB_INIT_RECORD_EXCEED  = 9,
    SI_PB_INIT_FILE_DECATIVE  = 10,
    SI_PB_INIT_SEARCH_OK      = 11,
    SI_PB_INIT_SEARCH_ERR     = 12,
    SI_PB_INIT_MSGTYPE_ERR    = 13,
    SI_PB_INIT_ERR_BUTT
};
typedef VOS_UINT32 SI_PB_INIT_STATUS_ENUM_UNIT32;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

/*��ȡ����������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ��   */
    VOS_UINT16                  usClient;                   /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
    VOS_UINT16                  usIndex1;
    VOS_UINT16                  usIndex2;
} SI_PB_READ_REQ_STRU;

/*��ѯ����������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ��   */
    VOS_UINT16                  usClient;                   /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
}SI_PB_QUERY_REQ_STRU;

/*���ú���������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;        /* ��Ϣ��     */
    VOS_UINT16                  usClient;         /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
} SI_PB_SET_REQ_STRU;

/*��Ӻ���������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ��   */
    VOS_UINT16                  usClient;                   /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
    SI_PB_RECORD_STRU           stRecord;
}SI_PB_ADD_REP_STRU;

/*���ĺ���������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ��   */
    VOS_UINT16                  usClient;              /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
    SI_PB_RECORD_STRU           Record;
}SI_PB_MODIFY_REP_STRU;

/*ɾ������������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /*��Ϣ��*/
    VOS_UINT16                  usClient;           /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
    VOS_UINT16                  usIndex;
    VOS_UINT16                  usReserved;
}SI_PB_DELETE_REQ_STRU;

/*���º����ļ�������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;       /* ��Ϣ�� */
    VOS_UINT32                  ulFileNumber;     /*�����ļ�����*/
    SI_PB_REFRESH_ENUM_UNIT32   enRefreshType;
    VOS_UINT16                  pusFile[SI_PB_MAX_XDN];
}SI_PB_REFRESH_REQ_STRU;

/*��������������Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ�� */
    VOS_UINT16                  usClient;           /*�ͻ���ID*/
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucRsv;
    SI_PB_STORATE_TYPE          ulStorage;
    VOS_UINT8                   ucLength;           /* Ҫƥ���ֶεĳ��� */
    VOS_UINT8                   aucContent[243];    /* Ҫƥ����ֶ����� */
}SI_PB_SEARCH_REQ_STRU;

/*EXT������Ϣ*/
typedef struct
{
    VOS_UINT16                     usExtFlag;
    VOS_UINT16                     usExtFileId;
    VOS_UINT16                     usExtTotalNum;
    VOS_UINT16                     usExtUsedNum;
    VOS_UINT8                      *pExtContent;
}SI_EXT_CONTENT_STRU;

/*�绰����Ϣ*/
typedef struct
{
    SI_PB_TYPE_ENUM_UINT32         enPBType;
    SI_PB_ACTIVE_STATE_ENUM_UINT32 enActiveStatus;
    VOS_UINT16                     usTotalNum;
    VOS_UINT16                     usUsedNum;
    VOS_UINT8                      ucRecordLen;
    VOS_UINT8                      ucNameLen;
    VOS_UINT8                      ucNumberLen;
    SI_PB_INIT_STATE_ENUM_UINT8    enInitialState;
    VOS_UINT32                     ulExtInfoNum;            /* ��Ӧ��EXT�ļ�������Ϣ��� */
    VOS_UINT8*                     pIndex;
    VOS_UINT8*                     pContent;
}SI_PB_CONTENT_STRU;


/*����绰����Ϣ*/
typedef struct
{
    SI_PB_ACTIVE_STATE_ENUM_UINT32 enActiveStatus;
    VOS_UINT16                     usTotalNum;
    VOS_UINT16                     usUsedNum;
    VOS_UINT8                      ucRecordLen;
    VOS_UINT8                      ucNumberLen;
    SI_PB_INIT_STATE_ENUM_UINT8    enInitialState;
    VOS_UINT8                      ucRsv;
    VOS_UINT8                      *pContent;
}SI_ANR_CONTENT_STRU;

/*Email�绰����Ϣ*/
typedef struct
{
    SI_PB_ACTIVE_STATE_ENUM_UINT32 enActiveStatus;
    VOS_UINT16                     usTotalNum;
    VOS_UINT16                     usUsedNum;
    VOS_UINT8                      ucRecordLen;
    VOS_UINT8                      ucDataLen;
    SI_PB_INIT_STATE_ENUM_UINT8    enInitialState;
    VOS_UINT8                      ucRsv;
    VOS_UINT8                      *pContent;
}SI_EML_CONTENT_STRU;

/*IAP�ļ���Ϣ*/
typedef struct
{
    VOS_UINT16                     usTotalNum;
    VOS_UINT8                      ucRecordLen;
    VOS_UINT8                      ucRsv;
    VOS_UINT8                      *pIAPContent;
}SI_IAP_CONTENT_STRU;

/*���ϵ绰��������Ϣ�洢*/
typedef struct
{
    VOS_UINT16                  usANRExtIndex[SI_PB_ANR_MAX+1];
    VOS_UINT8                   aucANRContent[SI_PB_ANR_MAX][SI_PB_ANR_LEN+3];/*ANR�ļ��Ϊ17��������20*/
    VOS_UINT8                   aucANRExtContent[SI_PB_ANR_MAX][SI_PB_EXT_LEN+3];
    VOS_UINT8                   aucEMLContent[SI_PB_EMAIL_MAX_LEN];
    VOS_UINT8                   aucIAPContent[20];
}SI_SPB_REQ_UINT_STRU;

/*�ⲿ������Ϣ�洢*/
typedef struct
{
    SI_PB_CNF_ENUM_UINT32       enPBEventType;
    SI_PB_STORATE_TYPE          enPBStoateType;
    SI_PB_LOCK_ENUM_UINT32      enPBLock;
    SI_SPB_REQ_UINT_STRU        stSPBReq;
    VOS_UINT16                  usClientID;
    VOS_UINT8                   ucOpID;
    VOS_UINT8                   ucEqualFlag;
    VOS_UINT16                  usIndex1;
    VOS_UINT16                  usIndex2;
    VOS_UINT16                  usCurIndex;
    VOS_UINT16                  usSearchLen;
    VOS_UINT16                  usExtIndex;
    VOS_UINT8                   aucXDNContent[100];
    VOS_UINT8                   aucEXTContent[SI_PB_EXT_LEN+1];
}SI_PB_REQ_UINT_STRU;

/*ADN��FDN��BDN��MSISDN��Ϣ�洢*/
typedef struct
{
    VOS_UINT16                  usFileID;
    VOS_UINT8                   ucRecordNum;
    VOS_UINT8                   ucRecordLen;
    VOS_UINT8                   ucSFI;
    VOS_UINT8                   aucRsv[3];
}SI_PB_XDN_INFO_STRU;

/*ANR��Ϣ�洢*/
typedef struct
{
    SI_PB_FILE_TYPE_ENUM_UINT32 enANRType;
    VOS_UINT32                  ulANRTagNum;/*ANR��Tag��A9Tag�е�λ�ã����ݴ�λ�ã�
                                            ���IAP�ļ�ȷ��ANR��ADN��¼��Ӧ��ϵ*/
    VOS_UINT16                  usANRFileID;
    VOS_UINT8                   ucRecordNum;
    VOS_UINT8                   ucRecordLen;
}SI_PB_ANR_INFO_STRU;

/*EMAIL��Ϣ�洢*/
typedef struct
{
    SI_PB_FILE_TYPE_ENUM_UINT32 enEMLType;
    VOS_UINT32                  ulEMLTagNum;/*Email��Tag��A9Tag�е�λ�ã����ݴ�λ�ã�
                                            ���IAP�ļ�ȷ��Email��ADN��¼��Ӧ��ϵ*/
    VOS_UINT16                  usEMLFileID;
    VOS_UINT8                   ucRecordNum;
    VOS_UINT8                   ucRecordLen;
}SI_PB_EML_INFO_STRU;

/*IAP��Ϣ�洢����31.102��94ҳ*/
typedef struct
{
    VOS_UINT16                  usIAPFileID;
    VOS_UINT8                   ucRecordNum;
    VOS_UINT8                   ucRecordLen;
}SI_PB_IAP_INFO_STRU;

/*UID��Ϣ�洢*/
typedef struct
{
    VOS_UINT16                  usFileID;
    VOS_UINT16                  usRsv;
}SI_PB_UID_INFO_STRU;

/*PBC��Ϣ�洢������3G��ͬ��*/
typedef struct
{
    VOS_UINT16   usFileID;
    VOS_UINT16   usRsv;
}SI_PB_PBC_INFO_STRU;

typedef struct
{
    VOS_UINT8  ucEntryChangeNum;     /* entry of change in 2G Terminal */
    VOS_UINT8  ucCCUpdateFlag;
    VOS_UINT8  aucRecord[258];
}SI_PB_PBC_UPDATE_STRU;

/*�绰��SEARCH������Ϣ*/
typedef struct
{
    VOS_UINT16  usReadOffset;       /* ��SEARCH��ʽ�õ���Ҫ��ʼ����¼��ƫ���� */
    VOS_UINT16  usReadNum;          /* ��SEARCH��ʽ�õ���Ҫ��ʼ�ļ�¼�� */
    VOS_UINT16  usEfId;             /* ��SEARCH��ʽ����ĵ�ǰ�ļ�ID */
    VOS_UINT16  usRsv;
    VOS_UINT8   aucReadString[256]; /* ��SEARCH��ʽ�õ���Ҫ��ʼ���ļ�¼ */
}SI_PB_SEARCH_CTRL_STRU;

/*�绰��������Ϣ*/
typedef struct
{

    VOS_UINT32                     ulADNFileNum;
    VOS_UINT32                     ulANRFileNum;
    VOS_UINT32                     ulEMLFileNum;
    VOS_UINT32                     ulIAPFileNum;
    VOS_UINT32                     ulANRStorageNum;
    SI_PB_XDN_INFO_STRU            astADNInfo[SI_PB_ADNMAX];
    SI_PB_ANR_INFO_STRU            astANRInfo[SI_PB_ADNMAX][SI_PB_ANRMAX];
    SI_PB_EML_INFO_STRU            astEMLInfo[SI_PB_ADNMAX];
    SI_PB_IAP_INFO_STRU            astIAPInfo[SI_PB_ADNMAX];
    SI_PB_UID_INFO_STRU            astUIDInfo[SI_PB_ADNMAX];
    SI_PB_PBC_INFO_STRU            astPBCInfo[SI_PB_ADNMAX];
    VOS_UINT32                     ulPSCValue;
    VOS_UINT32                     ulTotalUsed;/*���ϵ绰��ʹ�õ��ܼ�¼��*/
    SI_PB_STORATE_TYPE             enPBCurType;
    VOS_UINT16                     usCCValue;
    VOS_UINT16                     usPUIDValue;
    VOS_UINT16                     usUIDMaxValue;
    VOS_UINT16                     usEXT1FileID;
    VOS_UINT16                     usPBCRecordNum;
}SI_PB_CONTROL_STRU;

typedef struct
{
    SI_PB_INIT_STEP_ENUM_UINT32         enPBInitStep;
    SI_PB_SEND_REQ_STATUS_ENUM_UINT32   enReqStatus;
    SI_PB_INIT_STATUS_ENUM_UNIT32       enPBInitState;
    SI_PB_SEARCH_ENUM_UINT32            enPBSearchState;
    VOS_UINT16                          ausFileId[SI_PB_MAX_XDN];
    SI_PB_PBC_UPDATE_STRU               stPBCUpdate;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
}SI_PB_INIT_STATE_STRU;


typedef struct
{
    VOS_UINT16                    usADNFileId;
    VOS_UINT16                    usExtFileId;
    VOS_UINT16                    usEMLFileId;
    VOS_UINT16                    ausANRFileId[SI_PB_ANR_MAX];
    VOS_UINT8                     ucRecordNum;
    VOS_UINT8                     aucRsv[3];
}SI_PB_SPB_UPDATE_STRU;

typedef VOS_UINT32 (*PPBPROC)(PBMsgBlock *pMsg);
typedef VOS_VOID (*PPBINITPROC)(PBMsgBlock *pMsg);
typedef VOS_UINT32  (*PPBREQ)(VOS_VOID);

typedef struct
{
    VOS_UINT32                  ulMsgType;        /*������Ϣ����*/
    PPBPROC                     pProcFun;        /*��Ӧ������*/
}SI_PB_PROC_LIST_STRU;

typedef struct
{
    VOS_UINT32                 ulMsgType;        /*������Ϣ����*/
    PPBREQ                     pReqFun;         /*��Ϣ�ַ�����*/
    PPBINITPROC                pInitProcFun;        /*��Ӧ������*/
}SI_PB_INIT_LIST_STRU;

/*Ccpu���͵�ͬ��ȫ�ֱ�������Ϣ*/
typedef struct
{
    VOS_UINT32                 ulIndexAddr;
    VOS_UINT32                 ulContentAddr;
}SI_PB_CONTENT_PTR_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ�� */
    SI_PB_CONTROL_STRU          stPBCtrlInfo;
    SI_PB_CTRL_INFO_ST          stPBConfigInfo;
    SI_PB_CONTENT_STRU          astPBContent[SI_PB_MAX_NUMBER];
    SI_EXT_CONTENT_STRU         astEXTContent[SI_PB_MAX_NUMBER];
    SI_ANR_CONTENT_STRU         astANRContent[SI_PB_ANRMAX];
    SI_EML_CONTENT_STRU         stEMLContent;
    SI_IAP_CONTENT_STRU         stIAPContent;
    SI_PB_INIT_STATE_STRU       stPBInitState;

    SI_PB_CONTENT_PTR_STRU      astPBContentAddr[SI_PB_MAX_NUMBER];
    VOS_UINT32                  aulExtContentAddr[SI_PB_MAX_NUMBER];
    VOS_UINT32                  aulANRContentAddr[SI_PB_ANRMAX];
    VOS_UINT32                  ulEMLContentAddr;
    VOS_UINT32                  ulIAPContentAddr;
}SI_PB_UPDATEGLOBAL_IND_STRU;

/*Ccpu���͵ĵ�ǰ�绰�����õ���Ϣ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* ��Ϣ�� */
    SI_PB_STORATE_TYPE          enPBCurType;
}SI_PB_SETPB_IND_STRU;



typedef struct
{
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
}SI_PB_GETFILE_INFO_STRU;

typedef struct
{
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
    VOS_UINT32                  ulEfLen ;       /* �������ݳ��� */
    VOS_UINT8                   *pucEfContent;  /* ������������ */
}SI_PB_SETFILE_INFO_STRU;

typedef struct
{
    VOS_UINT16                   usFileID[14];
    VOS_UINT16                   usDataLen[14];
    VOS_UINT8                    ucRecordNum[14];
    VOS_UINT16                   usFileNum;
    VOS_UINT8                    *pContent[14];
}SI_PB_SPBDATA_STRU;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern SI_PB_CONTENT_STRU       gastPBContent[SI_PB_MAX_NUMBER];

extern SI_EXT_CONTENT_STRU      gastEXTContent[SI_PB_MAX_NUMBER];

extern SI_ANR_CONTENT_STRU      gastANRContent[SI_PB_ANRMAX];

extern SI_EML_CONTENT_STRU      gstEMLContent;

extern SI_IAP_CONTENT_STRU      gstIAPContent;

extern SI_PB_CONTROL_STRU       gstPBCtrlInfo;

extern SI_PB_CTRL_INFO_ST       gstPBConfigInfo;

extern SI_PB_INIT_STATE_STRU    gstPBInitState;

extern SI_PB_REQ_UINT_STRU      gstPBReqUnit;

extern SI_PB_SEARCH_CTRL_STRU   gstPBSearchCtrlInfo;

extern VOS_UINT32               gulPBFileCnt;

extern VOS_UINT32               gulPBRecordCnt;

extern VOS_UINT32               gulPBInitFileNum;

extern VOS_UINT32               gulPBInitExtFileNum;

extern VOS_UINT32               gulExtRecord;

extern VOS_UINT8                gucPBCStatus;


/*****************************************************************************
  6 ��������
*****************************************************************************/

extern VOS_UINT32 SI_PB_GetXDNFileID(VOS_UINT32 ulStorage, VOS_UINT16 *pusFileId);

extern VOS_UINT32 SI_PB_InitEccProc(PBMsgBlock *pstMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 SI_PB_InitXeccProc(PBMsgBlock *pstMsg);
#endif

extern VOS_VOID SI_PB_InitPBStatusProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEFpbrProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitXDNSpaceMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitANRSpaceMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEMLSpaceMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitIAPSpaceMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEXTSpaceMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitXDNContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEXTContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitIAPSearchMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEmailSearchMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitANRSearchMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitXDNSearchMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitPBCSearchMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitIAPContentMsgProc2(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEmailContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitANRContentMsgProc2(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitXDNContentMsgProc2(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitPBCContentMsgProc2(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitPBCContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitANRContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEXTRContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitEMLContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitIAPContentMsgProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitSYNCHProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitInfoAppDebug(PBMsgBlock *pstMsg);

extern VOS_UINT16  SI_PB_TransferFileCnt2ExtFileID(VOS_UINT32 PBFileCnt, VOS_UINT32 *pulPBType);

extern VOS_VOID SI_PB_SearchResultProc(VOS_UINT8 *pucReadString, VOS_UINT8 *pucSearchResult, VOS_UINT16 usMatchNum, VOS_UINT8 ucTotalNum);

extern VOS_UINT32 SI_PB_EMLContentProc(USIMM_READFILE_CNF_STRU *pstPBMsg, VOS_UINT8 ucSuffix, VOS_UINT16 usEmailIndex);

extern VOS_UINT32 SI_PB_InitANRType2ValidJudge(VOS_UINT8 ucXSuffix, VOS_UINT8 ucYSuffix, VOS_UINT8 ucRecordNum,VOS_UINT16 *pusRealIndex);

extern VOS_UINT32 SI_PB_FindPBOffset(SI_PB_TYPE_ENUM_UINT32  enPBType, VOS_UINT8 *pucOffset);

extern VOS_UINT32 SI_PB_LocateRecord(SI_PB_TYPE_ENUM_UINT32  enPBType, VOS_UINT16 usIndex1, VOS_UINT16 usIndex2, VOS_UINT8 *pucNumber);

extern VOS_UINT32 SI_PB_CountADNIndex(VOS_UINT16 usFileId, VOS_UINT8 ucRecordNum, VOS_UINT16 *pusIndex);

extern VOS_UINT32 SI_PB_CountADNRecordNum(VOS_UINT16 usIndex, VOS_UINT16 *pusFileId, VOS_UINT8 *pucRecordNum);

extern VOS_UINT32 SI_PB_GetADNSfi(VOS_UINT8 *pucSFI, VOS_UINT16 usFileId);

extern VOS_UINT32 SI_PB_GetADNFidFromSfi(VOS_UINT8 ucSFI, VOS_UINT16 *pusFileId);

extern VOS_UINT32 SI_PB_CheckContentValidity(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT8 *pContent);

extern VOS_UINT32 SI_PB_CheckEccValidity(VOS_UINT8 *pContent);

extern VOS_UINT32 SI_PB_CheckANRValidity(VOS_UINT8 *pContent);

extern VOS_UINT32  SI_PB_FindUnusedExtRecord(SI_EXT_CONTENT_STRU *pstPBContent, VOS_UINT8 *pucRecord, VOS_UINT8 ucRecordCount);

extern VOS_UINT32 SI_PB_CheckExtValidity(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT8 *pContent);

extern VOS_UINT32 SI_PB_ChangeADNNameFormat(VOS_UINT8 *pucInput, VOS_UINT8 *pucOutput, VOS_UINT8 *pucNameLen);

extern VOS_VOID SI_PB_BcdToAscii(VOS_UINT8 ucBcdNumLen,VOS_UINT8 *pucBcdNum, VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucLen);

extern VOS_VOID SI_PB_AsciiToBcd(VOS_UINT8 *pucAsciiNum, VOS_UINT8 ucAsciiNumLen, VOS_UINT8 *pucBcdNum, VOS_UINT8 *pucBcdNumLen);

extern VOS_UINT32 SI_FindTagInBERTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 SI_PB_DecodeEFPBR(VOS_UINT8 ucRecordNum, VOS_UINT8 ucRecordLen, VOS_UINT8 *pContent);

extern VOS_VOID SI_PB_DecodePBName(VOS_UINT8 ucNameMax, VOS_UINT8 *pucName,VOS_UINT32 *pAlphaType, VOS_UINT8 *pNameLen);

extern VOS_VOID SI_PB_TransPBFromate(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT16 usIndex, VOS_UINT8 *pContent, SI_PB_RECORD_STRU *pstRecord);

extern VOS_VOID SI_PB_TransANRFromate(VOS_UINT8 ucANROffset,VOS_UINT8 *pANRContent, SI_PB_RECORD_STRU *pstRecord);

extern VOS_VOID SI_PB_TransEMLFromate(VOS_UINT8 ucEmailMaxLen, VOS_UINT8 *pEMLContent, SI_PB_RECORD_STRU *pstRecord);

extern VOS_UINT32 SI_PB_JudgeADNFid(VOS_UINT16 usFileId);

extern VOS_UINT32 SI_PB_JudgeEXTFid(VOS_UINT16 usFileId, VOS_UINT16 usOffset);

extern VOS_UINT32 SI_PB_JudgeIAPFid(VOS_UINT16 usFileId);

extern VOS_UINT32 SI_PB_GetEXTContentFromReq(VOS_UINT8 ucRecordNum, VOS_UINT8 **ppucContent);

extern VOS_VOID SI_PB_IncreaceCCValue(VOS_UINT16 usIncValue,VOS_UINT8 ucAdnIndex);

extern VOS_VOID SI_PB_SetBitToBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulValue);

extern VOS_UINT32 SI_PB_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo);

extern VOS_UINT32 SI_PB_GetFileCntFromIndex(VOS_UINT16 ucIndex, VOS_UINT8 *pucEMLFileCnt);

extern VOS_UINT32 SI_PBCallback(SI_PB_EVENT_INFO_STRU *pEvent);

extern VOS_VOID SI_PB_InitGlobeVariable(VOS_VOID);

extern VOS_UINT32 SI_PB_InitPBStatusJudge(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEFpbrReq(VOS_VOID);


extern VOS_UINT32 SI_PB_InitXDNSpaceReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEMLSpaceReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitIAPSpaceReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitANRSpaceReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEXTSpaceReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEXTContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitIAPSearchReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEmailSearchReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitANRSearchReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitXDNSearchReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitPBCSearchReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitIAPContentReq2(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEmailContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitANRContentReq2(VOS_VOID);

extern VOS_UINT32 SI_PB_InitXDNContentReq2(VOS_VOID);

extern VOS_UINT32 SI_PB_InitPBCContentReq2(VOS_VOID);

extern VOS_UINT32 SI_PB_InitPBCContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitXDNContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEMLContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitIAPContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitANRContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitEXTRContentReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitSYNCHReq(VOS_VOID);

extern VOS_UINT32 SI_PB_InitInfoApp(VOS_VOID);

extern VOS_VOID SI_PB_ClearPBContent(VOS_UINT32 ulClearType);

extern VOS_BOOL SI_PB_CheckSupportAP(VOS_VOID);

extern VOS_VOID SI_PB_ClearSPBContent(VOS_UINT32 ulClearType);

extern VOS_VOID SI_PB_ExtExceptionProc(VOS_UINT16 usExtFileId);

extern VOS_UINT32 SI_PB_CheckADNFileID(VOS_UINT16 usFileID);

extern VOS_UINT32 SI_PB_CheckXDNFileID(VOS_UINT16 usFileID);

extern VOS_UINT32 SI_PB_GetXDNPBType(VOS_UINT32 *pulPBType, VOS_UINT16 usFileId);

extern VOS_UINT32 SI_PB_GetANRFid(VOS_UINT32 ulANRFileNum,VOS_UINT16 *pusANRFileId);

extern VOS_UINT32 SI_PB_GetANRSuffix(VOS_UINT8 *pucXSuffix,VOS_UINT8 *pucYSuffix,VOS_UINT16 usANRFileId);

extern VOS_UINT32 SI_PB_GetIAPFidFromEML(VOS_UINT16 usEMLFileId, VOS_UINT16 *pusIAPFileId);

extern VOS_UINT32 SI_PB_GetIAPFidFromANR(VOS_UINT16 usANRFileId, VOS_UINT16 *pusIAPFileId);

extern VOS_UINT32 SI_PB_GheckANRLast(VOS_UINT8 ucXSuffix,VOS_UINT8 ucYSuffix);

extern VOS_UINT32 SI_PB_GetEMLFIdFromADN(VOS_UINT16 *pusEMLFileId, VOS_UINT16 usADNId);

extern VOS_UINT32 SI_PB_GetANRFidFromADN(VOS_UINT8 ucANROffset, VOS_UINT16 usADNFileId,VOS_UINT16 *pusANRFileId);

extern VOS_UINT32 SI_PB_GetFreeANRRecordNum(VOS_UINT16 ucANRFid,VOS_UINT8 *pucRecordNum, VOS_UINT16 *pusIAPFid);

extern VOS_UINT32 SI_PB_GetFreeEMLRecordNum(VOS_UINT16 ucEMLFid,VOS_UINT8 *pucRecordNum, VOS_UINT16 *pusIAPFid);

extern VOS_UINT32 SI_PB_GetEMLRecord(VOS_UINT8 **ppEMLContent, VOS_UINT16 usEMLFileId,VOS_UINT8 ucRecordNum);

extern VOS_VOID SI_PB_InitPBStateProc(SI_PB_INIT_STATUS_ENUM_UNIT32 enPBInitState);

extern VOS_VOID SI_PB_InitSYNCHGetProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_InitSYNCHSetProc(PBMsgBlock *pstMsg);

extern VOS_VOID SI_PB_DecodeEFPBCRecord(VOS_UINT8 *pucContent, VOS_UINT8 ucRecordNum);

extern VOS_VOID SI_PB_DecodeEFUIDRecord(VOS_UINT8 *pucContent);

extern VOS_UINT32 SI_PB_CheckSYNCHFileID(VOS_UINT16 usFileID);

extern VOS_UINT32 SI_PB_CheckExtFileID(VOS_UINT16 usFileID);

extern VOS_VOID SI_PBSendGlobalToAcpu(VOS_VOID);

extern VOS_UINT32 SI_PB_CheckFdn(VOS_UINT8 *pucNum, VOS_UINT32 ulNumLength);

extern VOS_UINT32 SI_PB_EcallNumberErrProc(SI_PB_STORATE_TYPE ulStorage, VOS_UINT8 ucListLen, VOS_UINT8 *pucList, VOS_UINT8 *pucPBOffset);

extern VOS_VOID SI_PB_GetEcallNumber(SI_PB_CONTENT_STRU *pstXdnContent, SI_PB_ECALL_NUM_STRU *pstEcallNum, VOS_UINT8 ucListLen, VOS_UINT8 *pucList);

extern VOS_VOID SI_PB_EcallInitInd(VOS_VOID);

extern VOS_VOID SI_PB_JumpToNextPB(VOS_UINT32 ulPBType);

extern VOS_VOID SI_PB_RefreshUIDFile_Stub(VOS_UINT8 ucAdnIndex);

extern VOS_UINT32 SI_PB_UpdataXDNFile(VOS_UINT8 ucPBOffset, VOS_UINT16 usFileId, VOS_UINT16 usExtFileId,  VOS_UINT8 ucRecord,SI_PB_RECORD_STRU *pstRecord);

extern VOS_UINT32 SI_PB_UpdataSPBFile(SI_PB_SPB_UPDATE_STRU *pstPBFid, SI_PB_RECORD_STRU *pstRecord);

extern VOS_VOID SI_PB_DeleteHandleAnr(VOS_UINT16          usFileId,
                                        VOS_UINT16          usIndex,
                                        SI_PB_SPBDATA_STRU *pstSPBReq,
                                        VOS_UINT8           ucRecord);

extern VOS_UINT32 SI_PB_UpdataEML(SI_PB_RECORD_STRU *pstRecord,SI_PB_SPBDATA_STRU *pstSPBReq,SI_PB_SPB_UPDATE_STRU *pstPBFid);

extern VOS_UINT32 SI_PB_UpdataANR(SI_PB_RECORD_STRU *pstRecord, SI_PB_SPBDATA_STRU *pstSPBReq,  VOS_UINT16 *pusExtUsedNum, SI_PB_SPB_UPDATE_STRU *pstPBFid);

extern VOS_UINT32 SI_PB_UpdataADN(SI_PB_RECORD_STRU *pstRecord, SI_PB_SPBDATA_STRU *pstSPBReq, VOS_UINT16 *pusExtUsedNum, SI_PB_SPB_UPDATE_STRU *pstPBFid);

extern VOS_UINT32 SI_PB_DeleteHandle(VOS_UINT16 usFileId, VOS_UINT8 ucRecord, VOS_UINT8 ucOffset,VOS_UINT16 usIndex);

extern VOS_UINT32 SI_PB_RefreshALLContent(VOS_VOID);

extern VOS_VOID SI_PB_UsimGetIndexFile(VOS_UINT8 ucPBOffset, SI_PB_EVENT_INFO_STRU *pstCnfData);

extern VOS_VOID SI_PB_RefreshCardIndMsgSnd(VOS_VOID);

extern VOS_VOID SI_PB_PihRefreshIndProc(USIMM_STKREFRESH_IND_STRU *pstMsg);

extern VOS_BOOL SI_PB_UsimRefreshFileCheck(VOS_UINT16 usPathLen, VOS_UINT8 *pcFilePath, USIMM_CARDAPP_ENUM_UINT32 enAppType);

extern VOS_BOOL SI_PB_SimRefreshFileCheck(VOS_UINT16 usPathLen, VOS_UINT8 *pcFilePath);

extern VOS_BOOL SI_PB_RefreshFileCheck(USIMM_STKREFRESH_IND_STRU *pstMsg);

extern VOS_VOID SI_PB_ReleaseAll(VOS_VOID);

extern VOS_UINT32 SI_PB_SetProc(PBMsgBlock *pMsg);

extern VOS_UINT32 SI_PBInitMsgProc (PBMsgBlock *pMsg);

extern VOS_UINT32 SI_PB_EcallNumberQryProc(PBMsgBlock *pMsg);

extern VOS_VOID SI_PB_InitStatusInd(USIMM_PB_INIT_STATUS_ENUM_UINT16 enPBInitStatus);

extern VOS_UINT32 SI_PB_GetFileReq(SI_PB_GETFILE_INFO_STRU    *pstGetFileInfo);

extern VOS_UINT32 SI_PB_SetFileReq(SI_PB_SETFILE_INFO_STRU    *pstSetFileInfo);

extern VOS_UINT32 SI_PB_QueryFileReq(VOS_UINT16 usEFID);

extern VOS_UINT32  SI_PB_SearchFileReq(USIMM_U8_LVDATA_STRU    *pstData,
                                        VOS_UINT16              usFileId);

extern VOS_UINT32 SI_PB_SetSPBFileReq(SI_PB_SPBDATA_STRU *pstSPBReq);


extern VOS_VOID SI_PB_GetEFIDFromPath(USIMM_FILEPATH_INFO_STRU *pstFilePath,VOS_UINT16 *pusEFID);

extern VOS_UINT32 SI_PB_AsciiToHexCode(VOS_CHAR cSrc, VOS_UINT8 *pucDst);

extern VOS_VOID SI_PB_CardStatusInd(VOS_VOID);

extern VOS_VOID SI_PB_ChangeFileToPathStr(VOS_UINT16 usEFID, USIMM_FILEPATH_INFO_STRU *pstFilePath);

extern VOS_UINT32 SI_PB_SetFileReq(SI_PB_SETFILE_INFO_STRU    *pstSetFileInfo);

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

#endif

