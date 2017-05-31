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


#ifndef __IPIPMGLOBAL_H__
#define __IPIPMGLOBAL_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "TTFComm.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/
#define IP_NULL                         (0)
#define IP_OK                           (VOS_OK)
#define IP_NULL_PTR                     (VOS_NULL_PTR)
#define IP_MAX_PDN_NUM                  (10)

#define IP_DNS_MAX_NUM                  (4)

#define IP_IPM_MTU                          (1500)

/* ��ʱ���ʱ�䣬��λ�� */
#define IP_TIMER_MAX_LENGTH             (64800000 / 1000)

/*IP��ַ����*/
#define IP_IPV4_ADDR_LEN                (4)

#define IP_IPV6_ADDR_LEN                (16)

#define IP_UDP_FAKEHEAD_LEN             (12)

#define IP_UDP_HEAD_LEN                 (8)

#define IP_UDP_DHCP_HDR_SIZE            (4)

#define IP_ICMPV6_HEAD_LEN              (8)

#define IP_ETHERNET_HEAD_LEN            (14)

#ifndef  IP_IPV4_HEAD_LEN
#define IP_IPV4_HEAD_LEN             20     /* IPV4����ͷͷ������ */
#endif

#ifndef  IP_IPV6_HEAD_LEN
#define IP_IPV6_HEAD_LEN             40     /* IPV6����ͷͷ������ */
#endif

/* MAC��ַ���� */
#define IP_MAC_ADDR_LEN                 (6)
#define IP_ETH_MAC_HEADER_LEN           (14)     /*MAC֡ͷ����*/
#define IP_IPV6_PAYLOAD                 (0xdd86) /*IPV6 payload*/

/* ip��ͷУ��ɹ�ֵ,16λ */
#define IP_CHECKSUM_SUCCESS             (0xFFFF)

/* ip��ͷУ��ĳ���,��16λ���м�� */
#define IPCHECKLEN                      (10)

#define IP_BITMOVE_24                   (24)

#define IP_BITMOVE_16                   (16)

#define IP_BITMOVE_8                    (8)

#define IP_BITMOVE_4                    (4)

#define IP_8_LOW_BYTE                   (0x0F)

#define IP_8_HIGH_BYTE                  (0xF0)

#define IP_32_HIGH_BYTE                 (0xFFFF0000)

#define IP_32_LOW_BYTE                  (0x0000FFFF)

#define IP_32_FIRST_BYTE                (0xFF000000)

#define IP_32_SECOND_BYTE               (0x00FF0000)

#define IP_32_THIRD_BYTE                (0x0000FF00)

#define IP_32_FOURTH_BYTE               (0x000000FF)

#define IP_16_HIGH_BYTE                 (0xFF00)

#define IP_16_LOW_BYTE                  (0x00FF)

#define IP_IPM_TTL                          (128)

#define IP_OP_TRUE                      (1)

#define IP_OP_FALSE                     (0)

#define IP_DHCPV4_MSG_REPLY             (2)

/* ��̫��Ӳ������ */
#define IP_ETHERNET_HTYPE               (1)

/* DHCPЭ��option����ʼƫ�� */
#define IP_DHCPV4_OPTION_OFFSET         (240)

/* DHCP ����OPTIONS code ���� */
#define IP_DHCPV4_OPTION_CODE_LEN                           (1)

/* DHCP ����OPTIONS code + length ���� */
#define IP_DHCPV4_OPTION_CODELEN_LEN                        (2)

/* dhcp ����DHCP Message Type ���� */
#define IP_DHCPV4_OPTION_MSG_TYPE_LEN                       (1)

/* dhcp ����IP Address Lease Time ���� */
#define IP_DHCPV4_OPTION_LEASE_TIME_LEN                     (4)

/* dhcp ����ͷcookie�ֶγ��� */
#define IP_DHCPV4_HEAD_COOKIE_LEN                           (4)

/* dhcp ����ͷXID�ֶγ��� */
#define IP_DHCPV4_HEAD_XID_LEN                              (4)

/* dhcp ����ͷsecs�ֶγ��� */
#define IP_DHCPV4_HEAD_SECS_LEN                             (2)

/* dhcp ����ͷflags�ֶγ��� */
#define IP_DHCPV4_HEAD_FLAGS_LEN                            (2)

#define IP_MIN(n1,n2)                   (((n1)>(n2))?(n2):(n1))


#define IP_COMPARE(IPADDR1, IPADDR2)    ((IPADDR1[0]==IPADDR2[0]) && (IPADDR1[1]==IPADDR2[1]) && \
                                         (IPADDR1[2]==IPADDR2[2]) && (IPADDR1[3]==IPADDR2[3]))

#define IP_SET_TIMER_NULL(TIMER)        ((TIMER) = VOS_NULL_PTR)

#define IP_GET_MSG_ENTITY(pMsg)         ((VOS_VOID*)&((pMsg)->ulMsgId))

#define IP_GET_MSG_LENGTH(pMsg)         ((pMsg)->ulLength)

#define IP_GetMsgSenderPid(pMsg)        (((PS_MSG_HEADER_STRU*)pMsg)->ulSenderPid)
#define IP_GetMsgLength(pMsg)           (((PS_MSG_HEADER_STRU*)pMsg)->ulLength)
#define IP_GetMsgId(pMsg)               (((PS_MSG_HEADER_STRU*)pMsg)->ulMsgName)
#define IP_GetTimerPara(pMsg)           (((REL_TIMER_MSG *)pMsg)->ulPara)
#define IP_GetTimerName(pMsg)           (((REL_TIMER_MSG *)pMsg)->ulName)

/* �Ӷ�ʱ�����л�ȡ��ʱ������ */
#define IP_GetTimerType(ulTimerName)\
            (ulTimerName & IP_32_LOW_BYTE)

/* �Ӷ�ʱ�����л�ȡʵ������ */
#define IP_GetEntityIndex(ulTimerName)\
            (((ulTimerName & IP_32_SECOND_BYTE) >> IP_BITMOVE_16))


#define IP_GetNameFromMsg(ulMsgId, pMsg)\
{\
    if(VOS_PID_TIMER == IP_GetMsgSenderPid(pMsg))\
    {\
        ulMsgId = IP_GetTimerName(pMsg);\
        ulMsgId = (ulMsgId & IP_32_THIRD_BYTE) >> IP_BITMOVE_8;\
        ulMsgId = IP_ROUTER_TIMERMSG_ET(ulMsgId);\
    }\
    else\
    {\
        ulMsgId = IP_GetMsgId(pMsg);\
        ulMsgId = IP_ROUTER_LAYERMSG_ET(ulMsgId);\
    }\
}

/*��װдESM��Ϣͷ�ĺ�*/
#define IP_WRITE_ESM_MSG_HEAD(pstMsg, ulEsmMsgID)\
                    (pstMsg)->ulMsgId   = (ulEsmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ESM;

/*��װдRABM��Ϣͷ�ĺ�*/
#define IP_WRITE_RABM_MSG_HEAD(pstMsg, ulRabmMsgID)\
                    (pstMsg)->ulMsgId   = (ulRabmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_RABM;


#define IP_ADDR_IS_INVALID(IPADDR)\
     ((IPADDR[0] == 0)&&(IPADDR[1] == 0)&&(IPADDR[2] == 0)&&(IPADDR[3] == 0))\

#define IP_ADDR_IS_IDENTICAL(IPADDR1, IPADDR2)\
     ((IPADDR1[0] == IPADDR2[0])&&(IPADDR1[1] == IPADDR2[1])&&(IPADDR1[2] == IPADDR2[2])&&(IPADDR1[3] == IPADDR2[3]))\

/* ��ȡIP�汾�� */
#define IP_GetIpVersion(pucIpMsg)\
            ((pucIpMsg)[0] >> IP_BITMOVE_4 )

/* ��ȡIPV4��ͷ������ */
#define IP_GetIpv4HeaderLen(pucIpMsg)\
            (((pucIpMsg)[0] & IP_8_LOW_BYTE) *4 )

/* ��ȡЭ��� */
#define IP_GetProtocol(pucIpMsg)\
            ((pucIpMsg)[IP_HEAD_PROTOCOL_OFF])

/* ��ȡIPV4���ݰ����� */
#define IP_GetIpv4PacketLen(pucIpMsg, usIpv4PacketLen)\
            {\
                usIpv4PacketLen = (VOS_UINT16)(*((pucIpMsg) + IP_HEAD_IP_LEN)) << IP_BITMOVE_8;\
                usIpv4PacketLen = usIpv4PacketLen |(VOS_UINT16)(*((pucIpMsg) + IP_HEAD_IP_LEN + 1));\
            }

/* ��ȡUDP��Ŀ�Ķ˿� */
#define IP_GetUdpDesPort(pucUdpMsg, usDesPort)\
            {\
                usDesPort = (VOS_UINT16)(*((pucUdpMsg) + 2)) << IP_BITMOVE_8;\
                usDesPort = usDesPort | (VOS_UINT16)(*((pucUdpMsg) + 3));\
            }

#define IP_FormTimerType(ulModule, ulTimerIndex)\
            (((ulModule & IP_32_FOURTH_BYTE) << IP_BITMOVE_8) | (ulTimerIndex & IP_32_FOURTH_BYTE))

#define IP_MOVEMENT_4_BITS              (4)
#define IP_IPDATA_HIGH_4_BIT_MASK       (0xF0)
#define IP_IPDATA_LOW_4_BIT_MASK        (0x0F)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : IP_HEAD_OFFSET_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  IP���ֶ�ƫ��
*****************************************************************************/
enum IP_HEAD_OFFSET_ENUM
{
    IP_HEAD_VERSION_OFF                 = 0,                                    /* �汾ƫ�� */
    IP_HEAD_IP_LEN                      = 2,                                    /* ����ƫ�� */
    IP_HEAD_PROTOCOL_OFF                = 9,                                    /* Э��ƫ�� */
    IP_HEAD_CHECK_SUM_OFF               = 10,
    IP_HEAD_SRC_IP_OFF                  = 12,                                   /* ԴIPƫ�� */
    IP_HEAD_DESC_IP_OFF                 = 16,                                   /* Ŀ��IPƫ�� */

    IP_HEAD_BUTT
};
typedef VOS_UINT16 IP_HEAD_OFFSET_ENUM_UINT16;

/*****************************************************************************
 ö����    : IP_PORT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  �����˿�ö��
*****************************************************************************/
enum IP_PORT_TYPE_ENUM
{
    IP_PORT_DHCPV4_SERVER               = 67,
    IP_PORT_DHCPV4_CLIENT               = 68,

    IP_PORT_BUTT
};
typedef VOS_UINT16 IP_PORT_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : IP_VERSION_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IP�汾
*****************************************************************************/
enum IP_VERSION_TYPE_ENUM
{
    IP_VERSION_4                        = 4,
    IP_VERSION_6                        = 6,

    IP_VERSION_BUTT
};
typedef VOS_UINT8 IP_VERSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : IP_HEAD_PROTOCOL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ͷ�ʽ
*****************************************************************************/
enum IP_HEAD_PROTOCOL_ENUM
{
    IP_HEAD_PROTOCOL_ICMPV4             = 1,
    IP_HEAD_PROTOCOL_TDP                = 6,
    IP_HEAD_PROTOCOL_UDP                = 17,
    IP_HEAD_PROTOCOL_ICMPV6             = 58,

    IP_HEAD_PROTOCOL_BUTT
};
typedef VOS_UINT32 IP_HEAD_PROTOCOL_ENUM_UINT32;

/*****************************************************************************
 ö����    : IP_DHCPV4_OPTION_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  DHCPV4 options����
*****************************************************************************/
enum IP_DHCPV4_OPTION_TYPE_ENUM
{
    IP_DHCPV4_OPTION_SUBNET_MASK        = 1,                                    /* �������� */
    IP_DHCPV4_OPTION_ROUTER_IP          = 3,                                    /* Ĭ������ */
    IP_DHCPV4_OPTION_DOMAIN_NAME_SERVER = 6,                                    /* DNS */
    IP_DHCPV4_OPTION_REQUEST_IP_ADDR    = 50,                                   /* Request IP Address*/
    IP_DHCPV4_OPTION_LEASE_TIME         = 51,                                   /* ���� */
    IP_DHCPV4_OPTION_MSG_TYPE           = 53,                                   /* �������� */
    IP_DHCPV4_OPTION_SERVER_IP          = 54,                                   /* Server Identifier */
    IP_DHCPV4_OPTION_REQUEST_LIST       = 55,                                   /* request parameter list */
    IP_DHCPV4_OPTION_T1                 = 58,                                   /* Rebinding (T1) Time Value */
    IP_DHCPV4_OPTION_T2                 = 59,                                   /* Rebinding (T2) Time Value */
    IP_DHCPV4_OPTION_RAPID_COMMIT       = 80,                                   /* rapid commit */

    IP_DHCPV4_OPTION_BUTT
};
typedef VOS_UINT8 IP_DHCPV4_OPTION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : IP_DHCPV4_HEAD_OFFSET_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :   DHCPV4 ����ͷƫ��
*****************************************************************************/
enum IP_DHCPV4_HEAD_OFFSET_ENUM
{
    IP_DHCPV4_HEAD_OP_OFF               = 0,
    IP_DHCPV4_HEAD_HTYPE_OFF            = 1,
    IP_DHCPV4_HEAD_HLEN_OFF             = 2,
    IP_DHCPV4_HEAD_HOPS_OFF             = 3,
    IP_DHCPV4_HEAD_XID_OFF              = 4,
    IP_DHCPV4_HEAD_SECS_OFF             = 8,
    IP_DHCPV4_HEAD_FLAGS_OFF            = 10,
    IP_DHCPV4_HEAD_CIADDR_OFF           = 12,
    IP_DHCPV4_HEAD_YIADDR_OFF           = 16,
    IP_DHCPV4_HEAD_SIADDR_OFF           = 20,
    IP_DHCPV4_HEAD_GIADDR_OFF           = 24,
    IP_DHCPV4_HEAD_CHADDR_OFF           = 28,
    IP_DHCPV4_HEAD_COOKIE_OFF           = 236,

    IP_DHCPV4_HEAD_BUTT
};
typedef VOS_UINT16 IP_DHCPV4_HEAD_OFFSET_ENUM_UINT16;

/*****************************************************************************
 ö����    : IP_DHCPV4_MSG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :   DHCPV4 ��������
*****************************************************************************/
enum IP_DHCPV4_MSG_ENUM
{
    IP_DHCPV4_MSG_DISCOVER              = 1,
    IP_DHCPV4_MSG_OFFER                 = 2,
    IP_DHCPV4_MSG_REQUEST               = 3,
    IP_DHCPV4_MSG_DECLINE               = 4,
    IP_DHCPV4_MSG_ACK                   = 5,
    IP_DHCPV4_MSG_NAK                   = 6,
    IP_DHCPV4_MSG_RELEASE               = 7,
    IP_DHCPV4_MSG_INFORM                = 8,

    IP_DHCPV4_MSG_BUTT
};
typedef VOS_UINT32 IP_DHCPV4_MSG_ENUM_UINT32;


/*****************************************************************************
 ö����    : IP_GMAC_PAYLOAD_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��̫��Э��payloadö��
*****************************************************************************/
enum IP_GMAC_PAYLOAD_TYPE_ENUM
{
   IP_GMAC_PAYLOAD_TYPE_ARP             = 0x0806,
   IP_GMAC_PAYLOAD_TYPE_IPV4            = 0x0800,
   IP_GMAC_PAYLOAD_TYPE_IPV6            = 0X86dd,

   IP_GMAC_PAYLOAD_TYPE_BUTT
};
typedef VOS_UINT32 IP_GMAC_PAYLOAD_TYPE_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : IP_IPV4HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4ͷ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitVersion          : 4;                /*�汾*/
    VOS_UINT8                           bitHeadLength       : 4;                /*�ײ����ȣ���λΪ4�ֽ�*/
    VOS_UINT8                           bitPriority         : 3;                /*���ȼ�*/
    VOS_UINT8                           bitD                : 1;                /*��ʾҪ���и��͵�ʱ��*/
    VOS_UINT8                           bitT                : 1;                /*��ʾҪ���и��ߵ�������*/
    VOS_UINT8                           bitR                : 1;                /*��ʾ�и��ߵĿɿ���*/
    VOS_UINT8                           bitC                : 1;                /*��ʾҪ��ѡ����۸�С��·��*/
    VOS_UINT8                           bitReserved         : 1;                /*Ŀǰ��δʹ��*/
    VOS_UINT16                          usLength;                               /*�ܳ��ȣ���λ:�ֽ�*/
    VOS_UINT16                          usIdentification;                       /*��ʶ*/
    VOS_UINT16                          bitFlagMF           : 1;                /*MF=1��ʾ�з�Ƭ*/
    VOS_UINT16                          bitFlagDF           : 1;                /*DF=0��ʾ�����Ƭ*/
    VOS_UINT16                          bitFlagReserved     : 1;                /*Ŀǰδʹ��*/
    VOS_UINT16                          bitFlagmentExcursion: 13;               /*Ƭƫ��*/
    VOS_UINT8                           ucTTL;                                  /*����ʱ��*/
    VOS_UINT8                           ucProtocol;                             /*Э��*/
    VOS_UINT16                          usFCS;                                  /*�ײ������*/
    VOS_UINT8                           aucIPSrc[IP_IPV4_ADDR_LEN];             /*ԴIP��ַ*/
    VOS_UINT8                           aucIPDes[IP_IPV4_ADDR_LEN];             /*Ŀ��IP��ַ*/
}IP_IPV4HEAD_STRU;                              /*IP���ݱ�ͷ���ṹ��*/

/*****************************************************************************
 �ṹ��    : IP_UDPHEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UDPͷ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPortSrc;                              /*Դ�˿ں�*/
    VOS_UINT16                          usPortDes;                              /*Ŀ�Ķ˿ں�*/
    VOS_UINT16                          usLength;                               /*����UDP����*/
    VOS_UINT16                          usFCS;                                  /*����UDP�����*/
}IP_UDPHEAD_STRU;                                                           /*UDP���ݱ�ͷ�ṹ��*/

/*****************************************************************************
 �ṹ��    : IP_UDPFAKEHEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UDPα�ײ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucIPSrc[IP_IPV4_ADDR_LEN];             /*ԴIP��ַ*/
    VOS_UINT8                           aucIPDes[IP_IPV4_ADDR_LEN];             /*Ŀ��IP��ַ*/
    VOS_UINT8                           ucAll0;                                 /*ȫ��Ϊ0*/
    VOS_UINT8                           ucProtocol;                             /*IP�ײ���Э���ֶ�*/
    VOS_UINT16                          usLength;                               /*����UDP���ȣ�������α�ײ�����*/
}IP_UDPFAKEHEAD_STRU;                                                      /*UDPα�ײ��ṹ��*/


/*****************************************************************************
 �ṹ��    : IP_TIMER_STRU
 Э����  :
 ASN.1���� :��
 �ṹ˵��  : ��ʱ���ṹ��
*****************************************************************************/
typedef struct
{
    HTIMER                              hTm;                                    /* ��ʱ��ָ�� */
    VOS_UINT32                          ulName;                                 /* ��ʱ������ */
    VOS_UINT8                           ucLoopTimes;                            /* ѭ���������� */
    VOS_UINT8                           ucStatus;                               /* ��ʱ����״̬ */
    VOS_UINT8                           aucReserved[2];
}IP_TIMER_STRU;                                                              /* ��ʱ���ṹ�� */


/*****************************************************************************
 �ṹ��    : IP_GMAC_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��̫��֡ͷ�ṹ��
*****************************************************************************/
typedef struct
{
  VOS_UINT8                             aucMacAddrDes[IP_MAC_ADDR_LEN];
  VOS_UINT8                             aucMacAddrSrc[IP_MAC_ADDR_LEN];
  VOS_UINT16                            usFrmType;
  VOS_UINT8                             aucReserved[2];
}IP_GMAC_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : IP_DHCPV4_LEASE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DHCPv4���ڽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLeaseT;
    VOS_UINT32                          ulLeaseT1;
    VOS_UINT32                          ulLeaseT2;
}IP_DHCPV4_LEASE_STRU;


/*****************************************************************************
6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










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

#endif /* end of IpIpmGlobal.h */
