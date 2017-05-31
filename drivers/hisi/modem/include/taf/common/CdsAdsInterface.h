

#ifndef __CDSADSINTERFACE_H__
#define __CDSADSINTERFACE_H__

/*****************************************************************************
  1 ͷ�ļ�����
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
/* !!!!!!!!!!!��ʱ���壬���յ�ֵ�ɱ���ȷ�� */
#define ADS_CDS_MSG_HDR                (0x00)
#define CDS_ADS_MSG_HDR                (0x10)

#define CDS_ADS_ALL_RABID               (0xFF)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
ö����    : CDS_ADS_MSG_ID_ENUM
�ṹ˵��  : CDS��ADS��֮�����Ϣ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDS��ADS֮�����Ϣ
*****************************************************************************/
enum CDS_ADS_MSG_ID_ENUM
{
    ID_CDS_ADS_STOP_SENDDATA_IND     = CDS_ADS_MSG_HDR + 0x01,                  /* CDS->ADS STOP SENDDATA IND */
    ID_CDS_ADS_STOP_SENDDATA_RSP     = ADS_CDS_MSG_HDR + 0x01,                  /* ADS->CDS STOP SENDDATA RSP */
    ID_CDS_ADS_START_SENDDATA_IND    = CDS_ADS_MSG_HDR + 0x02,                  /* CDS->ADS START SENDDATA IND */
    ID_CDS_ADS_START_SENDDATA_RSP    = ADS_CDS_MSG_HDR + 0x02,                  /* ADS->CDS START SENDDATA RSP */
    ID_CDS_ADS_CLEAR_DATA_IND        = CDS_ADS_MSG_HDR + 0x03,                  /* CDS->ADS CLEAR DATA IND */
    ID_CDS_ADS_CLEAR_DATA_RSP        = ADS_CDS_MSG_HDR + 0x03,                  /* ADS->CDS CLEAR DATA RSP */
    ID_CDS_ADS_IP_PACKET_IND         = CDS_ADS_MSG_HDR + 0x04,                  /* CDS->ADS IP PACKET IND */
    ID_CDS_ADS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  CDS_ADS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
ö����    : CDS_ADS_IP_PACKET_TYPE_ENUM_UINT8
�ṹ˵��  : CDS��ADS��IP��Ϣ�����Ͷ���

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDS��ADS����Ϣ������
*****************************************************************************/
enum CDS_ADS_IP_PACKET_TYPE_ENUM
{
    CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4   = 0x00,
    CDS_ADS_IP_PACKET_TYPE_ND_SERVERDHCPV6 = 0x01,
    CDS_ADS_IP_PACKET_TYPE_ICMPV6          = 0x02,
    CDS_ADS_IP_PACKET_TYPE_LINK_FE80       = 0x03,
    CDS_ADS_IP_PACKET_TYPE_LINK_FF         = 0x04,
    CDS_ADS_IP_PACKET_TYPE_BUTT
};
typedef VOS_UINT8 CDS_ADS_IP_PACKET_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : CDS_ADS_DL_IPF_BEARER_ID_ENUM
�ṹ˵��  : CDS��ADS���е�IPF Bearer Id����

  1.��    ��   : 2011��12��16��
    ��    ��   : ³��/l60609
    �޸�����   : CDS��ADS���е�IPF Bearer Id����
*****************************************************************************/
enum CDS_ADS_DL_IPF_BEARER_ID_ENUM
{
    CDS_ADS_DL_IPF_BEARER_ID_RSV0     = 0,                                      /* 0~4���� */
    CDS_ADS_DL_IPF_BEARER_ID_EPSBID5  = 5,                                      /* 5~15 EPS Bearer ID*/
    CDS_ADS_DL_IPF_BEARER_ID_EPSBID15 = 15,
    CDS_ADS_DL_IPF_BEARER_ID_DHCPV4   = 16,                                     /* ����DHCP */
    CDS_ADS_DL_IPF_BEARER_ID_DHCPV6   = 17,                                     /* ����DHCPv6*/
    CDS_ADS_DL_IPF_BEARER_ID_ICMPV4   = 18,                                     /* ����ICMP */
    CDS_ADS_DL_IPF_BEARER_ID_ICMPV6   = 19,                                     /* ����ICMPv6 */
    CDS_ADS_DL_IPF_BEARER_ID_LL_FE80  = 20,
    CDS_ADS_DL_IPF_BEARER_ID_LL_FF    = 21,
    CDS_ADS_DL_IPF_BEARER_ID_INVALID  = 63                                      /* ��ƥ���κ�Filter��0x3F*/
};
typedef VOS_UINT32 CDS_ADS_DL_IPF_BEARER_ID_ENUM_UINT32;

/*****************************************************************************
ö����    : ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8
�ṹ˵��  : ADS��CDS�����ݰ�����

  1.��    ��   : 2013��05��22��
    ��    ��   : ����/00179208
    �޸�����   : ����ADS��CDS�����ݰ�����
*****************************************************************************/
enum ADS_CDS_PKT_TYPE_ENUM
{
    ADS_CDS_IPF_PKT_TYPE_IP   = 0x00,                                           /* IP���� */
    ADS_CDS_IPF_PKT_TYPE_PPP  = 0x01,                                           /* PPP���� */
    ADS_CDS_IPF_PKT_TYPE_BUTT
};
typedef VOS_UINT8 ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8;

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
�ṹ��    : CDS_ADS_STOP_SENDDATA_IND_STRU
�ṹ˵��  : CDSָʾADSֹͣ���ݷ��ͽṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDSָʾADSֹͣ���ݷ��͵Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* ��ϢID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];

} CDS_ADS_STOP_SENDDATA_IND_STRU;

/*****************************************************************************
�ṹ��    : CDS_ADS_STOP_SENDDATA_RSP_STRU
�ṹ˵��  : ADS�ظ�CDSֹͣ���ݷ��ͽṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS�ظ�CDSֹͣ���ݷ��͵Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* ��ϢID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];
} CDS_ADS_STOP_SENDDATA_RSP_STRU;

/*****************************************************************************
�ṹ��    : CDS_ADS_START_SENDDATA_IND_STRU
�ṹ˵��  : CDSָʾADS�������ݷ��ͽṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDSָʾADS�������ݷ��ͽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* ��ϢID */
    MODEM_ID_ENUM_UINT16                enModemId ;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];
} CDS_ADS_START_SENDDATA_IND_STRU;

/*****************************************************************************
�ṹ��    : CDS_ADS_START_SENDDATA_RSP_STRU
�ṹ˵��  : ADS�ظ�CDS�ָ����ݷ��ͽṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS�ظ�CDS�ָ����ݷ��ͽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* ��ϢID */
    MODEM_ID_ENUM_UINT16                enModemId ;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];
} CDS_ADS_START_SENDDATA_RSP_STRU;

/*****************************************************************************
�ṹ��    : CDS_ADS_CLEAR_DATA_IND_STRU
�ṹ˵��  : CDSָʾADS��ջ������ݽṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDSָʾADS��ջ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* ��ϢID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucRsv[1];                              /* ����*/
} CDS_ADS_CLEAR_DATA_IND_STRU;

/*****************************************************************************
�ṹ��    : CDS_ADS_CLEAR_DATA_RSP_STRU
�ṹ˵��  : ADS�ظ�CDS��ջ������ݽṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS�ظ�CDS��ջ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* ��ϢID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucRsv[1];                              /* ����*/
} CDS_ADS_CLEAR_DATA_RSP_STRU;

/*****************************************************************************
 �ṹ��    : CDS_ADS_DATA_IND_STRU
 �ṹ˵��  : CDS��ADS֮������ݰ���Ϣ�ṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDS��ADS֮������ݰ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    CDS_ADS_IP_PACKET_TYPE_ENUM_UINT8   enIpPacketType;                         /* IP PACKET TYPE*/
    VOS_UINT16                          usLen;                                  /* Zc Len*/
    VOS_UINT8                           aucRsv[2];                              /* ����*/
    VOS_UINT8                           aucData[4];                             /* ���ݰ� */
} CDS_ADS_DATA_IND_STRU;

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

#endif

