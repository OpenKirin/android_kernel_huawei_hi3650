

#ifndef __PPP_INTERFACE_H__
#define __PPP_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "PsTypeDef.h"
#if (VOS_WIN32 == VOS_OS_VER) || (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "ImmInterface.h"
#include "AdsDeviceInterface.h"
#endif
/******************************************************************************
  2 �궨��
******************************************************************************/
/*ϵͳ�����Ҫ��PPP ID����Ŀ */
#define PPP_MAX_ID_NUM                      (1)

/*RABID���*/
#define PPP_INVALID_RABID                   (0xFF)

/*PPPID*/
#define PPP_INVLAID_PPP_ID                  (0)


#define AUTHLEN                             (100)    /* Size of authname/authkey(porting from BSD, not alter) */
#define PASSWORDLEN                         (100)    /* Size of authname/authkey(define by fanzhibin) */
#define CHAPCHALLENGELEN                    (48)     /* Maximum chap challenge(porting from BSD, not alter) */
#define MD5DIGESTSIZE                       (16)     /* MD5 (Message-Digest) hash size */

#define PPP_PAP_REQ_BUF_MAX_LEN             (PASSWORDLEN + AUTHLEN)

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
#define PPP_CHAP_CHALLENGE_BUF_MAX_LEN      (1 + 1 + 2 + 1 + CHAPCHALLENGELEN + AUTHLEN)

/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define PPP_CHAP_RESPONSE_BUF_MAX_LEN       (1 + 1 + 2 + 1 + PASSWORDLEN + AUTHLEN)

#define PPP_AUTH_FRAME_BUF_MAX_LEN          (256)
#define PPP_IPCP_FRAME_BUF_MAX_LEN          (256)

/*�ַ���ʽ��IP��ַ���ȣ�����"."��16���ַ�*/
#define PPP_IPV4_ADDR_STR_MAX_LEN           (16)

#ifndef IPV4_ADDR_LEN
#define   IPV4_ADDR_LEN                     (4)       /*IPV4��ַ����*/
#endif

#ifndef IPV6_ADDR_LEN
#define   IPV6_ADDR_LEN                     (16)      /*IPV6��ַ����*/
#endif

/******************************************************************************
  3 ö�ٶ���
******************************************************************************/
enum PPP_AT_CTRL_OPER_TYPE_ENUM
{
    PPP_AT_CTRL_REL_PPP_REQ = 0,              /* �ͷ�IP����PPP��·���� */
    PPP_AT_CTRL_REL_PPP_RAW_REQ = 1,          /* �ͷ�PPP����PPP��·���� */
    PPP_AT_CTRL_HDLC_DISABLE = 2,             /* HDLCӲ��ģ��ȥʹ�ܲ��� */
    PPP_AT_CTRL_CONFIG_INFO_IND = 3,          /* PDP������Ϣ */

    PPP_AT_CTRL_BUTT
};
typedef VOS_UINT32  PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32;

/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
  5 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  6 ��Ϣ����
******************************************************************************/


/******************************************************************************
  7 STRUCT����
******************************************************************************/
#pragma pack(4)

typedef VOS_UINT16 PPP_ID;

/* ��Ȩ���� */
enum PPP_AUTH_TYPE_ENUM
{
    PPP_NO_AUTH_TYPE                     = 0,
    PPP_PAP_AUTH_TYPE                    = 1,
    PPP_CHAP_AUTH_TYPE                   = 2,
    PPP_MS_CHAPV2_AUTH_TYPE              = 3,
    PPP_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 PPP_AUTH_TYPE_ENUM_UINT8;

typedef struct
{
    VOS_UINT16  usPapReqLen;                    /*request����: 24.008Ҫ����[3,253]�ֽ�*/
    VOS_UINT8   aucReserve[2];                  /* ���뱣�� */
    VOS_UINT8  *pPapReq;                        /*request*/
} PPP_AUTH_PAP_CONTENT_STRU;

typedef struct
{
    VOS_UINT16  usChapChallengeLen;             /*challenge����: 24.008Ҫ����[3,253]�ֽ�*/
    VOS_UINT16  usChapResponseLen;              /*response����: 24.008Ҫ����[3,253]�ֽ�*/
    VOS_UINT8  *pChapChallenge;                 /*challenge*/
    VOS_UINT8  *pChapResponse;                  /*response*/
} PPP_AUTH_CHAP_CONTENT_STRU;

typedef struct
{
    PPP_AUTH_TYPE_ENUM_UINT8  ucAuthType;
    VOS_UINT8                 aucReserve[3];

    union
    {
        PPP_AUTH_PAP_CONTENT_STRU  PapContent;
        PPP_AUTH_CHAP_CONTENT_STRU ChapContent;
    } AuthContent;
} PPP_REQ_AUTH_CONFIG_INFO_STRU;

typedef struct
{
    VOS_UINT16  usIpcpLen;                      /*Ipcp֡����*/
    VOS_UINT8   aucReserve[2];                  /* ���뱣�� */
    VOS_UINT8  *pIpcp;                          /*Ipcp֡*/
} PPP_REQ_IPCP_CONFIG_INFO_STRU;

typedef struct
{
    PPP_REQ_AUTH_CONFIG_INFO_STRU stAuth;
    PPP_REQ_IPCP_CONFIG_INFO_STRU stIPCP;
} PPP_REQ_CONFIG_INFO_STRU;

typedef struct
{
    VOS_UINT16  usAuthLen;                      /*��Ȩ֡����*/
    VOS_UINT16  usIpcpLen;                      /*Ipcp֡����*/
    VOS_UINT8  *pAuth;                          /*��Ȩ֡*/
    VOS_UINT8  *pIpcp;                          /*Ipcp֡*/
    VOS_UINT8   aucIpAddr[PPP_IPV4_ADDR_STR_MAX_LEN]; /*Ip��ַ*/
} PPP_IND_CONFIG_INFO_STRU;


/* PPP��AT���͵���Ϣ�������� */
#define AT_PPP_RELEASE_IND_MSG          0x00    /* �ͷ�PDP���ӵ����� */
#define AT_PPP_MODEM_MSC_IND_MSG        0x01    /* ��AT���͹ܽ��ź�ָʾ(����͸���ܽ��źţ�
                                                         �����޷�ģ��AT���Լ�����Ϣ,��ģ��PPP��AT���͸���Ϣ.) */
#define AT_PPP_PROTOCOL_REL_IND_MSG     0x02    /* PPP��·����ͷŵ�ָʾ */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucReserve[3];
}AT_PPP_RELEASE_IND_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    VOS_UINT8                           aucMscInd[2];  /* �ܽ��ź����� */
}AT_PPP_MODEM_MSC_IND_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT8                           ucReserve[2];
}AT_PPP_PROTOCOL_REL_IND_MSG_STRU;


typedef VOS_VOID (*PPP_PULL_MSG_EVENT_CALLBACK)(VOS_UINT32 ulMsgCnt);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION����
******************************************************************************/


/******************************************************************************
  9 OTHERS����
******************************************************************************/


/******************************************************************************
  10 ��������
******************************************************************************/
/* PPP�ṩ��AT�Ľӿ� */
extern VOS_UINT32 Ppp_CreatePppReq ( PPP_ID *pusPppId);
extern VOS_UINT32 Ppp_CreateRawDataPppReq ( PPP_ID *pusPppId);
extern VOS_UINT32 Ppp_ReleasePppReq ( PPP_ID usPppId);
extern VOS_UINT32 Ppp_ReleaseRawDataPppReq ( PPP_ID usPppId);
extern VOS_UINT32 PPP_RcvAtCtrlOperEvent(VOS_UINT16 usPppId, PPP_AT_CTRL_OPER_TYPE_ENUM_UINT32 ulCtrlOperType);
extern VOS_VOID   PPP_UpdateWinsConfig(VOS_UINT8 ucWins);
extern VOS_VOID   PPP_SetRawDataByPassMode(VOS_UINT32 ulRawDataByPassMode);

#if (VOS_WIN32 == VOS_OS_VER) || (OSA_CPU_ACPU == VOS_OSA_CPU)
/* IP��ʽ���ṩ���������ݽ��սӿ� */
extern VOS_UINT32 PPP_PullPacketEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc);

/* IP��ʽ���ṩ���������ݽ��սӿ� */
extern VOS_UINT32 PPP_PushPacketEvent(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);

/* PPP��ʽ���ṩ���������ݽ��սӿ� */
extern VOS_UINT32 PPP_PullRawDataEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc);

/* PPP��ʽ���ṩ���������ݽ��սӿ� */
extern VOS_UINT32 PPP_PushRawDataEvent(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PppInterface.h */

