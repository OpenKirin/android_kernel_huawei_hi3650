/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __IPV4DHCPSERVER_H__
#define __IPV4DHCPSERVER_H__

#include "vos.h"
#include "PsNdis.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push,4)
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifndef NDIS_RELEASE

#if (VOS_WIN32 == VOS_OS_VER)
#define NDIS_ASSERT vos_printf("Assert, File: %s, Line:%d\n", __FILE__,__LINE__)
#else
#define NDIS_ASSERT vos_assert((VOS_UINT32)__FILE__, (VOS_INT)__LINE__)
#endif


#define IP_NDIS_ASSERT(exp) \
    if(!(exp))\
    {\
        NDIS_ASSERT;\
        return;\
    }

#define IP_NDIS_ASSERT_RTN(exp,ret) \
    if (!(exp)) \
    {\
        NDIS_ASSERT;\
        return (ret); \
    }

#else
#define IP_NDIS_ASSERT(exp)                ((VOS_VOID)0)
#define IP_NDIS_ASSERT_RTN(exp,ret)        ((VOS_VOID)0)
#endif

/*ȡ�ṹ��Ա��ƫ�Ƶ�ַ*/
#define IP_OFFSETOF(TYPE,MEMBER)      ((VOS_UINT32)&(((TYPE*)0)->MEMBER))

/* ���������ֽ��������ֽ���ת��*/
#if (VOS_BYTE_ORDER == VOS_BIG_ENDIAN)

#define IP_NTOHL(x)                  (x)
#define IP_HTONL(x)                  (x)
#define IP_NTOHS(x)                  (x)
#define IP_HTONS(x)                  (x)

#else

/* _BYTE_ORDER==_LITTLE_ENDIAN */
#define IP_NTOHL(x)                  ((((x) & 0x000000ff) << 24) | \
                                       (((x) & 0x0000ff00) <<  8) | \
                                       (((x) & 0x00ff0000) >>  8) | \
                                       (((x) & 0xff000000) >> 24))

#define IP_HTONL(x)                  ((((x) & 0x000000ff) <<  24) | \
                                       (((x) & 0x0000ff00) <<  8) | \
                                       (((x) & 0x00ff0000) >>  8) | \
                                       (((x) & 0xff000000) >> 24))

#define IP_NTOHS(x)                  ((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8))
#define IP_HTONS(x)                  ((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8))

#endif



/*��Ե�ǰ��ӡ���к궨��*/
#ifndef NDIS_RELEASE
#define IP_INFO_LOG(STRING)                              PS_PRINTF("%s,%d,%s \r\n",__FILE__,__LINE__,STRING)
#define IP_ERROR_LOG(STRING)                             PS_PRINTF("%s,%d,%s \r\n",__FILE__,__LINE__,STRING)
#define IP_ERROR_LOG1(STRING,lPara)                      PS_PRINTF("%s,%d,%s,%d \r\n", __FILE__,__LINE__,STRING,lPara)
#define IP_ERROR_LOG2(STRING,lPara1,lPara2)              PS_PRINTF("%s,%d,%s,%d,%d \r\n",__FILE__,__LINE__,STRING,lPara1,lPara2)
#else
#define IP_INFO_LOG(STRING)
#define IP_ERROR_LOG(STRING)
#define IP_ERROR_LOG1(STRING,lPara)
#define IP_ERROR_LOG2(STRING,lPara1,lPara2)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*UDP Э��ͷ����*/
#define IP_UDP_HDR_LEN                                (8)

/*IPV4 DHCP���ݰ�����*/

/* IPV4 DHCP Pkt Hostname Length*/
#define IPV4_DHCP_SERVER_HOST_NAME_LEN                (64)

/* IPV4 DHCP Pkt Filename Length*/
#define IPV4_DHCP_FILE_NAME_LEN                       (128)

/* IP Address Lease Time ��λΪs  */
#define IPV4_DHCP_LEASE_TIME                          (g_ulLeaseTime)

/*  Renewal (T1) Time Value*/
#define IPV4_DHCP_T1                                  (IPV4_DHCP_LEASE_TIME/2)

/* Rebinding (T2) Time Value */
#define IPV4_DHCP_T2                                  ((IPV4_DHCP_LEASE_TIME * 7) / 8)

/* DHCPЭ��option����ʼƫ�� */
#define IPV4_DHCP_OPTION_OFFSET                       (240)

/*DHCP Option ÿһ��ͷ��ռ�ĳ���*/
#define IP_DHCPV4_OPTION_ITEM_HDR_LEN                 (2)

/* dhcp ����ͷcookie�ֶγ��� */
#define IPV4_DHCP_HEAD_COOKIE_LEN                     (4)

/*DHCPЭ�鵥Ԫ��Ӳ����ַ����*/
#define IPV4_DHCP_HARDWARE_LEN                        (16)

/* DHCP ��������*/
#define IPV4_DHCP_OPERATION_REQUEST                   (1)
#define IPV4_DHCP_OPERATION_REPLY                     (2)

/* ��̫��Ӳ������ */
#define IPV4_DHCP_ETHERNET_HTYPE                      (1)

/* dhcp ����IP Address Lease Time ���� */
#define IPV4_DHCP_OPTION_LEASE_TIME_LEN               (4)

/*DHCP ������Your IP Addr Offset*/
#define IPV4_DHCP_HEAD_YIADDR_OFFSET                  (16)

/*dhcp msg type���ͳ���*/
#define IPV4_DHCP_OPTION_MSG_TYPE_LEN                 (1)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : IPV4_DHCP_ADDR_STATUS_ENUM
 Э����  : ����IPV4 DHCP ��ַ��״̬
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef enum
{
    IPV4_DHCP_ADDR_STATUS_FREE            = 0,
    IPV4_DHCP_ADDR_STATUS_ASSIGNED        = 1,
    IPV4_DHCP_ADDR_STATUS_BUTT
}IPV4_DHCP_ADDR_STATUS_ENUM;

typedef VOS_UINT32  IPV4_DHCP_ADDR_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : IP_CAST_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ͷ�ʽ
*****************************************************************************/
enum IP_CAST_TYPE_ENUM
{
    IP_CAST_TYPE_UNICAST                             = 0,
    IP_CAST_TYPE_BRODCAST                            = 1,
    IP_CAST_TYPE_BUTT
};
typedef VOS_UINT8 IP_CAST_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : IPV4_DHCP_OPTION_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  IPV4 DHCP options����
*****************************************************************************/
enum IPV4_DHCP_OPTION_TYPE_ENUM
{
    IPV4_DHCP_OPTION_PAD_OPTIOIN        = 0,                                    /* padding�����ֶ���*/
    IPV4_DHCP_OPTION_SUBNET_MASK        = 1,                                    /* �������� */
    IPV4_DHCP_OPTION_ROUTER_IP          = 3,                                    /* Ĭ������ */
    IPV4_DHCP_OPTION_DOMAIN_NAME_SERVER = 6,                                    /* DNS */
    IPV4_DHCP_OPTION_NETBIOS_NAME_SERVER = 44,                                   /* WINS NAME Server*/
    IPV4_DHCP_OPTION_REQUEST_IP_ADDR    = 50,                                   /* Request IP Address*/
    IPV4_DHCP_OPTION_LEASE_TIME         = 51,                                   /* ���� */
    IPV4_DHCP_OPTION_MSG_TYPE           = 53,                                   /* �������� */
    IPV4_DHCP_OPTION_SERVER_IP          = 54,                                   /* Server Identifier */
    IPV4_DHCP_OPTION_REQUEST_LIST       = 55,                                   /* request parameter list */
    IPV4_DHCP_OPTION_T1                 = 58,                                   /* Rebinding (T1) Time Value */
    IPV4_DHCP_OPTION_T2                 = 59,                                   /* Rebinding (T2) Time Value */
    IPV4_DHCP_OPTION_RAPID_COMMIT       = 80,                                   /* rapid commit */
    IPV4_DHCP_OPTION_END_OPTION         = 255,                                  /* option�������*/
    IPV4_DHCP_OPTION_BUTT
};

typedef VOS_UINT8 IPV4_DHCP_OPTION_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : IPV4_DHCP_MSG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IPV4 DHCP ������Ϣ���ͣ�Э��涨RFC2131
*****************************************************************************/
enum IPV4_DHCP_MSG_ENUM
{
    IPV4_DHCP_MSG_DISCOVER            = 1,
    IPV4_DHCP_MSG_OFFER               = 2,
    IPV4_DHCP_MSG_REQUEST             = 3,
    IPV4_DHCP_MSG_DECLINE             = 4,
    IPV4_DHCP_MSG_ACK                 = 5,
    IPV4_DHCP_MSG_NAK                 = 6,
    IPV4_DHCP_MSG_RELEASE             = 7,
    IPV4_DHCP_MSG_INFORM              = 8,
    IPV4_DHCP_MSG_BUTT
};

typedef VOS_UINT32  IPV4_DHCP_MSG_ENUM_UINT32;

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
/*��������ֽ�������Ϊ1�ֽڶ���*/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

/*****************************************************************************
 �ṹ��    : IPV4_UDPIPFAKEHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ڼ���UDP CRC
*****************************************************************************/
typedef struct
{
    /*Fake Hdr*/
    VOS_UINT8                           aucRec0[8];                             /*ȫ��Ϊ0��Ӱ��CRC���㣬Ϊ��ͬIPͷ��С������ͬ*/
    IPV4_ADDR_ITEM_UN                   unSrcIP;                                /*ԴIP��ַ*/
    IPV4_ADDR_ITEM_UN                   unDstIP;                                /*Ŀ��IP��ַ*/
    VOS_UINT8                           ucAll0;                                 /*ȫ��Ϊ0*/
    VOS_UINT8                           ucProtocol;                             /*IP�ײ���Э���ֶ�*/
    VOS_UINT16                          usLength;                               /*����UDP���ȣ�������α�ײ�����*/

    /*Udp Hdr*/
    VOS_UINT16                          usSrcPort;                              /* source port */
    VOS_UINT16                          usDstPort;                              /* dest port */
    VOS_UINT16                          usLen;                                  /* udp length */
    VOS_UINT16                          usChecksum;                             /* udp check sum*/

}IPV4_UDPIPFAKEHDR_STRU;

/*****************************************************************************
 �ṹ��    : IPV4_DHCPSERVER_PROTOCL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DHCPV4Э��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOP;                                   /*�������ͣ�1���ͻ��������ģ�2����������Ӧ����*/
    VOS_UINT8                           ucHardwareType;                         /*Ӳ�����ͣ�1����̫��*/
    VOS_UINT8                           ucHardwareLength;                       /*Ӳ����ַ����*/
    VOS_UINT8                           ucHops;                                 /*�������м���Ŀ*/
    VOS_UINT32                          ulTransactionID;                        /*�û�ѡȡ���������ʹ�������Ļظ����û��ı��������*/
    VOS_UINT16                          usSeconds;                              /*�ͻ����ڿ�ʼDHCP��������ȥ������*/
    VOS_UINT16                          usFlags;                                /*ֻ�б�־�ֶε����λ�������壬�����λ������Ϊ0�����λ0���������Ե�����ʽ������Ӧ���ģ����λ1���������Թ㲥��ʽ������Ӧ����*/
    IPV4_ADDR_ITEM_UN                   unClientIPAddr;                         /*�ͻ��˵�IP��ַ*/
    IPV4_ADDR_ITEM_UN                   unYourIPAddr;                           /*������������ͻ��˵�IP��ַ*/
    IPV4_ADDR_ITEM_UN                   unNextServerIPAddr;                     /*��������IP��ַ*/
    IPV4_ADDR_ITEM_UN                   unRelayIPAddr;                          /*�м̵�IP��ַ*/
    VOS_UINT8                           aucClientHardwardAddr[IPV4_DHCP_HARDWARE_LEN]; /*�ͻ��˵�MAC��ַ*/
    VOS_UINT8                           aucServerHostName[IPV4_DHCP_SERVER_HOST_NAME_LEN];/*����������*/
    VOS_UINT8                           aucFileName[IPV4_DHCP_FILE_NAME_LEN];     /*�ͻ��˵����������ļ���*/
    VOS_UINT8                           aucMagicCookie[IPV4_DHCP_HEAD_COOKIE_LEN];/* MAGIC COOKIE */
}IPV4_DHCP_PROTOCL_STRU;

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif
/*****************************************************************************
 �ṹ��    : IPV4_DHCP_ANALYSE_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����DHCP�����
*****************************************************************************/
typedef struct
{
    IPV4_ADDR_ITEM_UN                 unSrcIPAddr;
    IPV4_ADDR_ITEM_UN                 unDstIpAddr;
    VOS_UINT32                        ulTransactionID;
    IPV4_ADDR_ITEM_UN                 unClientIPAddr;
    IPV4_ADDR_ITEM_UN                 unYourIPAddr;
    IPV4_DHCP_MSG_ENUM_UINT32         enMsgType;
    IPV4_ADDR_ITEM_UN                 unRequestIPAddr;
    IPV4_ADDR_ITEM_UN                 unServerIPAddr;

    VOS_UINT8                         ucHardwareLen;
    VOS_UINT8                         ucRec[3];

    VOS_UINT16                        usCastFlg;
    VOS_UINT8                         aucHardwareAddr[ETH_MAC_ADDR_LEN];
}IPV4_DHCP_ANALYSE_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : IPV4_DHCP_OPTION_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4 DHCP Option�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucOptionType;
    VOS_UINT8       ucOptionLen;
    VOS_UINT8       aucOptionValue[254];
}IPV4_DHCP_OPTION_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : IPV4_DHCP_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4 DHCP ͳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulRecvDhcpPkt;
    VOS_UINT32      ulRecvDiscoverMsg;
    VOS_UINT32      ulRecvRequestMsg;
    VOS_UINT32      ulRecvSelectingReqMsg;
    VOS_UINT32      ulRecvOtherReqMsg;
    VOS_UINT32      ulRecvReleaseMsg;
    VOS_UINT32      ulRecvOtherTypeMsg;
    VOS_UINT32      ulSendOffer;
    VOS_UINT32      ulSendAck;
    VOS_UINT32      ulSendNack;
    VOS_UINT32      ulProcErr;
    VOS_UINT32      ulSendDhcpPktSucc;
    VOS_UINT32      ulSendDhcpPktFail;
}IPV4_DHCP_STAT_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

extern IPV4_DHCP_STAT_INFO_STRU   g_stDhcpStatStru;
extern VOS_UINT32  g_ulLeaseTime;

/*define dhcp server stat macro*/
#define   IPV4_DHCP_STAT_RECV_DHCP_PKT(n)              (g_stDhcpStatStru.ulRecvDhcpPkt          += (n))
#define   IPV4_DHCP_STAT_RECV_DISCOVER_MSG(n)          (g_stDhcpStatStru.ulRecvDiscoverMsg      += (n))
#define   IPV4_DHCP_STAT_RECV_REQUEST_MSG(n)           (g_stDhcpStatStru.ulRecvRequestMsg       += (n))
#define   IPV4_DHCP_STAT_RECV_SELETING_REQ_MSG(n)      (g_stDhcpStatStru.ulRecvSelectingReqMsg  += (n))
#define   IPV4_DHCP_STAT_RECV_OTHER_REQ_MSG(n)         (g_stDhcpStatStru.ulRecvOtherReqMsg      += (n))
#define   IPV4_DHCP_STAT_RECV_RELEASE_MSG(n)           (g_stDhcpStatStru.ulRecvReleaseMsg       += (n))
#define   IPV4_DHCP_STAT_RECV_OTHER_TYPE_MSG(n)        (g_stDhcpStatStru.ulRecvOtherTypeMsg     += (n))
#define   IPV4_DHCP_STAT_SEND_OFFER(n)                 (g_stDhcpStatStru.ulSendOffer            += (n))
#define   IPV4_DHCP_STAT_SEND_ACK(n)                   (g_stDhcpStatStru.ulSendAck              += (n))
#define   IPV4_DHCP_STAT_SEND_NACK(n)                  (g_stDhcpStatStru.ulSendNack             += (n))
#define   IPV4_DHCP_STAT_PROC_ERR(n)                   (g_stDhcpStatStru.ulProcErr              += (n))
#define   IPV4_DHCP_STAT_SEND_PKT_SUCC(n)              (g_stDhcpStatStru.ulSendDhcpPktSucc      += (n))
#define   IPV4_DHCP_STAT_SEND_PKT_FAIL(n)              (g_stDhcpStatStru.ulSendDhcpPktFail      += (n))


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID IPV4_DHCP_ProcDhcpPkt(VOS_UINT8  *pucIpPkt, VOS_UINT8 ucRabId,VOS_UINT32 ulPktMemLen);
extern NDIS_IPV4_INFO_STRU * IPV4_DHCP_FindIPV4Entity(VOS_UINT8 ucExRabId);


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif


#endif /* end of Ipv4DhcpServer.h */


