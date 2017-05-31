

#ifndef __ATPPPINTERFACE_H__
#define __ATPPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PppInterface.h"
#include "TafTypeDef.h"
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "ImmInterface.h"
#endif

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/
/* ��ΪAPS���棬����ģʽ�£�APS��֪ͨPPP������Э�̣��м�ģʽ�²�֪ͨPPPC */



/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*��ӦPPP_AUTH_PAP_CONTENT_STRU��������Ϣ��ʽ����*/
typedef struct
{
    VOS_UINT16  usPapReqLen;                            /*request����: 24.008Ҫ����[3,253]�ֽ�*/
    VOS_UINT8   aucReserve[2];                          /* ���뱣�� */
    VOS_UINT8   aucPapReqBuf[PPP_PAP_REQ_BUF_MAX_LEN];  /*request*/
} AT_PPP_AUTH_PAP_CONTENT_STRU;

/*��ӦPPP_AUTH_CHAP_CONTENT_STRU��������Ϣ��ʽ����*/
typedef struct
{
    VOS_UINT16  usChapChallengeLen;                     /*challenge����: 24.008Ҫ����[3,253]�ֽ�*/
    VOS_UINT16  usChapResponseLen;                      /*response����: 24.008Ҫ����[3,253]�ֽ�*/
    VOS_UINT8   aucChapChallengeBuf[PPP_CHAP_CHALLENGE_BUF_MAX_LEN];  /*challenge,153B*/
    VOS_UINT8   aucChapResponseBuf[PPP_CHAP_RESPONSE_BUF_MAX_LEN];    /*response,205B*/
    VOS_UINT8   aucReserve[2];
} AT_PPP_AUTH_CHAP_CONTENT_STRU;

/*��ӦPPP_REQ_AUTH_CONFIG_INFO_STRU��������Ϣ��ʽ����*/
typedef struct
{
    PPP_AUTH_TYPE_ENUM_UINT8  ucAuthType;
    VOS_UINT8                 aucReserve[3];              /* ���뱣�� */

    union
    {
        AT_PPP_AUTH_PAP_CONTENT_STRU  PapContent;
        AT_PPP_AUTH_CHAP_CONTENT_STRU ChapContent;
    } AuthContent;
} AT_PPP_REQ_AUTH_CONFIG_INFO_STRU;

/*��ӦPPP_REQ_IPCP_CONFIG_INFO_STRU��������Ϣ��ʽ����*/
typedef struct
{
    VOS_UINT16  usIpcpLen;                              /*Ipcp֡����*/
    VOS_UINT8   aucReserve[2];                          /* ���뱣�� */
    VOS_UINT8   aucIpcp[PPP_IPCP_FRAME_BUF_MAX_LEN];    /*Ipcp֡*/
} AT_PPP_REQ_IPCP_CONFIG_INFO_STRU;

/*��ӦPPP_REQ_CONFIG_INFO_STRU��������Ϣ��ʽ����*/
typedef struct
{
    AT_PPP_REQ_AUTH_CONFIG_INFO_STRU stAuth;
    AT_PPP_REQ_IPCP_CONFIG_INFO_STRU stIPCP;
} AT_PPP_REQ_CONFIG_INFO_STRU;

/*PCO��Я����IPCP��Ϣ*/
typedef struct
{
    VOS_UINT32                          bitOpPriDns    : 1;             /*Primary DNS server Address*/
    VOS_UINT32                          bitOpSecDns    : 1;             /*Secondary DNS server Address*/
    VOS_UINT32                          bitOpGateWay   : 1;             /*Peer IP address*/
    VOS_UINT32                          bitOpPriNbns   : 1;             /*Primary WINS DNS address*/
    VOS_UINT32                          bitOpSecNbns   : 1;             /*Seocndary WINS DNS address*/
    VOS_UINT32                          bitOpSpare     : 27;            /*Secondary DNS server Address*/

    VOS_UINT8                           aucPriDns[IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[IPV4_ADDR_LEN];
    VOS_UINT8                           aucGateWay[IPV4_ADDR_LEN];
    VOS_UINT8                           aucPriNbns[IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[IPV4_ADDR_LEN];
} AT_PPP_PCO_IPV4_ITEM_STRU;

/*��ӦPPP_IND_CONFIG_INFO_STRU��������Ϣ��ʽ����*/
typedef struct
{
    VOS_UINT8                           aucIpAddr[IPV4_ADDR_LEN];       /*����IP��ַ*/
    AT_PPP_PCO_IPV4_ITEM_STRU           stPcoIpv4Item;                  /*PCO��Ϣ*/
} AT_PPP_IND_CONFIG_INFO_STRU;

/* ��ΪAPS���棬����ģʽ�£�APS��֪ͨPPP������Э�̣��м�ģʽ�²�֪ͨPPPC */

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* �������ӿ�ʹ�õ��µĽṹ�壬��˲�����PppInterface.h */
extern VOS_UINT32 At_RcvTeConfigInfoReq (VOS_UINT16 usPppId,AT_PPP_REQ_CONFIG_INFO_STRU *pstPppReqConfigInfo);
extern VOS_UINT32 Ppp_RcvConfigInfoInd (PPP_ID usPppId, AT_PPP_IND_CONFIG_INFO_STRU *pPppIndConfigInfo);
extern TAF_UINT32 At_RcvPppReleaseInd ( TAF_UINT16 usPppId);
extern TAF_UINT32 At_PsRab2PppId (TAF_UINT8 ucRabId, TAF_UINT16 *pusPppId);
extern TAF_UINT32 At_PppId2PsRab (TAF_UINT16 usPppId, TAF_UINT8 *pucRabId);
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 AT_SendZcDataToModem(
    VOS_UINT16                          usPppId,
    IMM_ZC_STRU                        *pstDataBuf
);
#endif

extern VOS_UINT32 Ppp_RegDlDataCallback(PPP_ID usPppId);

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



