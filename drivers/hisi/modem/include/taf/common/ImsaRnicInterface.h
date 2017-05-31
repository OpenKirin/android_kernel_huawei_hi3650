
#ifndef __IMSA_RNIC_INTERFACE_H__
#define __IMSA_RNIC_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "RnicInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
#define   IMSA_RNIC_IPV4_ADDR_LENGTH          (4)     /* IPV4��ַ���ȣ���λ�ֽ� */
#define   IMSA_RNIC_IPV6_ADDR_LENGTH          (16)    /* IPV6��ַ����, ��λ�ֽ� */

#define   IMSA_RNIC_MAX_DNS_SERVER_NUM        (4)     /* ��������4��DNS��������һ������ */

/*================================================*/
/* ���ܺ����궨�� */
/*================================================*/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

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
 ö����    : IMSA_RNIC_MSG_ID_ENUM
 ö��˵��  : IMSA��RNIC����Ϣ����
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : ����
*****************************************************************************/
enum IMSA_RNIC_MSG_ID_ENUM
{
    /* IMSA����RNIC����Ϣö�� */
    ID_IMSA_RNIC_PDN_ACT_IND        = 0x0001,   /* PDN����ָʾ */               /* _H2ASN_MsgChoice IMSA_RNIC_PDN_ACT_IND_STRU */
    ID_IMSA_RNIC_PDN_DEACT_IND      = 0x0002,   /* PDNȥ����ָʾ */             /* _H2ASN_MsgChoice IMSA_RNIC_PDN_DEACT_IND_STRU */
    ID_IMSA_RNIC_PDN_MODIFY_IND     = 0x0003,   /* PDN�޸�ָʾ */               /* _H2ASN_MsgChoice IMSA_RNIC_PDN_MODIFY_IND_STRU */

    /* RNIC����IMSA����Ϣö�� */


    ID_IMSA_RNIC_MSG_ID_ENUM_BUTT

};
typedef VOS_UINT32 IMSA_RNIC_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : IMSA_RNIC_IMS_RAT_TYPE_ENUM
 ö��˵��  : IMSע��������
 1.��    ��   : 2015��10��07��
   ��    ��   : f00179208
   �޸�����   : ����
*****************************************************************************/
enum IMSA_RNIC_IMS_RAT_TYPE_ENUM
{
    IMSA_RNIC_IMS_RAT_TYPE_LTE          = 0x00,
    IMSA_RNIC_IMS_RAT_TYPE_WIFI         = 0x01,
    IMSA_RNIC_IMS_RAT_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_RNIC_IMS_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : IMSA_RNIC_IPV4_PDN_INFO_STRU
 �ṹ˵��  : IPV4 ������Ϣ�ṹ
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* �ⲿģ����д��ָʾaucDnsPrimAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* �ⲿģ����д��ָʾaucDnsSecAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT8                           aucIpV4Addr[IMSA_RNIC_IPV4_ADDR_LENGTH];       /* IP��ַ */
    VOS_UINT8                           aucDnsPrimAddr[IMSA_RNIC_IPV4_ADDR_LENGTH];    /* ��DNS������IP */
    VOS_UINT8                           aucDnsSecAddr[IMSA_RNIC_IPV4_ADDR_LENGTH];     /* ��DNS������IP */
}IMSA_RNIC_IPV4_PDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_RNIC_IPV6_PDN_INFO_STRU
 �ṹ˵��  : IPV6 ������Ϣ�ṹ
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* �ⲿģ����д��ָʾaucDnsPrimAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* �ⲿģ����д��ָʾaucDnsSecAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT32                          ulBitPrefixLen;                              /* IPV6ǰ׺����,��λΪbit */
    VOS_UINT8                           aucIpV6Addr[IMSA_RNIC_IPV6_ADDR_LENGTH];       /* IP��ַ */
    VOS_UINT8                           aucDnsPrimAddr[IMSA_RNIC_IPV6_ADDR_LENGTH];    /* ��DNS������IP */
    VOS_UINT8                           aucDnsSecAddr[IMSA_RNIC_IPV6_ADDR_LENGTH];     /* ��DNS������IP */
}IMSA_RNIC_IPV6_PDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_RNIC_SOCK_PORT_INFO_STRU
 �ṹ˵��  : �˿ڷ�Χ������Ϣ�ṹ
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSockMinPort;      /* socket �˿ڷ�Χ���� */
    VOS_UINT16                          usSockMaxPort;      /* socket �˿ڷ�Χ���� */
}IMSA_RNIC_SOCK_PORT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_RNIC_PDN_INFO_CONFIG_STRU
 �ṹ˵��  : IMSA��RNIC����������PDN������Ϣ
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSockPortInfo: 1;
    VOS_UINT32                          bitOpSpare       : 29;

    MODEM_ID_ENUM_UINT16                enModemId;                  /* ��ǰModem�� */
    VOS_UINT8                           ucRabId;                    /* ���غţ�ȡֵ��Χ[5,15] */
    IMSA_RNIC_IMS_RAT_TYPE_ENUM_UINT8   enRatType;                  /* ע���� */

    IMSA_RNIC_IPV4_PDN_INFO_STRU        stIpv4PdnInfo;
    IMSA_RNIC_IPV6_PDN_INFO_STRU        stIpv6PdnInfo;
    IMSA_RNIC_SOCK_PORT_INFO_STRU       stSockPortInfo;
}IMSA_RNIC_PDN_INFO_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_RNIC_PDN_ACT_IND_STRU
 �ṹ˵��  : IMSA��RNIC��PDN����ָʾ
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                    /* ��Ϣ���� */  /* _H2ASN_Skip */
    IMSA_RNIC_PDN_INFO_CONFIG_STRU      stPdnInfo;
}IMSA_RNIC_PDN_ACT_IND_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_RNIC_PDN_DEACT_IND_STRU
 �ṹ˵��  : IMSA��RNIC��PDNȥ����ָʾ
 1.��    ��   : 2014��07��31��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                    /* ��Ϣ���� */  /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;                  /* ��ǰModem�� */
    VOS_UINT8                           ucRabId;                    /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    IMSA_RNIC_IMS_RAT_TYPE_ENUM_UINT8   enRatType;                  /* ע���� */
}IMSA_RNIC_PDN_DEACT_IND_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_RNIC_PDN_MODIFY_IND_STRU
 �ṹ˵��  : IMSA��RNIC��PDN�޸�ָʾ
 1.��    ��   : 2016��03��16��
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                    /* ��Ϣ���� */  /* _H2ASN_Skip */
    IMSA_RNIC_PDN_INFO_CONFIG_STRU      stPdnInfo;
}IMSA_RNIC_PDN_MODIFY_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    IMSA_RNIC_MSG_ID_ENUM_UINT32        enMsgId;            /* _H2ASN_MsgChoice_Export IMSA_RNIC_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_RNIC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} IMSA_RNIC_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    IMSA_RNIC_INTERFACE_MSG_DATA          stMsgData;
} ImsaRnicInterface_MSG;

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

#endif /* ImsaRnicInterface.h */

