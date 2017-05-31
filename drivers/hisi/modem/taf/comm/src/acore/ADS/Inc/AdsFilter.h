

#ifndef __ADSFILTER_H__
#define __ADSFILTER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AdsDeviceInterface.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ADS_FILTER_MAX_LIST_NUM                 (256)
#define ADS_FILTER_DEFAULT_AGING_TIMELEN        (60)
#define ADS_FILTER_SECOND_TRANSFER_JIFFIES      (1000)

#define ADS_FILTER_IPV4_HDR_LEN                 (20)            /* IPv4 �ײ����� */
#define ADS_FILTER_ICMP_HDR_LEN                 (8)             /* ICMP �ײ����� */

#define ADS_MAX_IPV4_ADDR_LEN                   (16)            /* IPv4��ַ����ַ������� */

#define ADS_IPPROTO_ICMP                        (0x01)          /* ICMP protocol */
#define ADS_IPPROTO_IGMP                        (0x02)          /* IGMP protocol */
#define ADS_IPPROTO_TCP                         (0x06)          /* TCP protocol */
#define ADS_IPPROTO_UDP                         (0x11)          /* UDP protocol */

#define ADS_IP_CE                               (0x8000)        /* Flag: "Congestion" */
#define ADS_IP_DF                               (0x4000)        /* Flag: "Don't Fragment" */
#define ADS_IP_MF                               (0x2000)        /* Flag: "More Fragments" */
#define ADS_IP_OFFSET                           (0x1FFF)        /* "Fragment Offset" part */

/* ICMP���ĵ�type�ֶκ궨�� */
#define ADS_ICMP_ECHOREPLY                      (0)             /* Echo Reply           */
#define ADS_ICMP_DEST_UNREACH                   (3)             /* Destination Unreachable  */
#define ADS_ICMP_SOURCE_QUENCH                  (4)             /* Source Quench        */
#define ADS_ICMP_REDIRECT                       (5)             /* Redirect (change route)  */
#define ADS_ICMP_ECHOREQUEST                    (8)             /* Echo Request         */
#define ADS_ICMP_TIME_EXCEEDED                  (11)            /* Time Exceeded        */
#define ADS_ICMP_PARAMETERPROB                  (12)            /* Parameter Problem    */
#define ADS_ICMP_TIMESTAMP                      (13)            /* Timestamp Request    */
#define ADS_ICMP_TIMESTAMPREPLY                 (14)            /* Timestamp Reply      */
#define ADS_ICMP_INFO_REQUEST                   (15)            /* Information Request  */
#define ADS_ICMP_INFO_REPLY                     (16)            /* Information Reply    */
#define ADS_ICMP_ADDRESS                        (17)            /* Address Mask Request */
#define ADS_ICMP_ADDRESSREPLY                   (18)            /* Address Mask Reply   */

/* ����Ԫ�ظ���������ʹ�õĺ� */
#define ADS_FILTER_ARRAY_SIZE(a)                (sizeof((a)) / sizeof((a[0])))

#define ADS_FILTER_GET_IPV6_ADDR()              (&g_stAdsFilterCtx.unIPv6Addr)
#define ADS_FILTER_GET_LIST(index)              (&(g_stAdsFilterCtx.astLists[index]))
#define ADS_FILTER_GET_AGING_TIME_LEN()         (g_stAdsFilterCtx.ulAgingTimeLen)
#define ADS_FILTER_SET_AGING_TIME_LEN(len)      (g_stAdsFilterCtx.ulAgingTimeLen = (len))

#define ADS_FILTER_GET_DL_ICMP_FUNC_TBL_ADDR(ucType)     (&(g_astAdsFilterDecodeDlIcmpFuncTbl[ucType]))
#define ADS_FILTER_GET_DL_ICMP_FUNC_TBL_SIZE()           (ADS_FILTER_ARRAY_SIZE(g_astAdsFilterDecodeDlIcmpFuncTbl))

/* ��ά�ɲ���Ϣͳ�����ú� */
#define ADS_FILTER_DBG_GET_STATS_ARRAY_ADDR()            (&g_aulAdsFilterStats[0])
#define ADS_FILTER_DBG_GET_STATS_BY_INDEX(enPktType)     (g_aulAdsFilterStats[enPktType])
#define ADS_FILTER_DBG_STATISTIC(enPktType, n)           (g_aulAdsFilterStats[enPktType] += (n))

#define ADS_FILTER_MALLOC(size)                 ADS_FILTER_HeapAlloc(size)
#define ADS_FILTER_FREE(addr)                   ADS_FILTER_HeapFree(addr)

/* ����Ƿ�ﵽ�ϻ�ʱ�� */
#define ADS_FILTER_IS_AGED(time)\
    ((0 != ADS_FILTER_GET_AGING_TIME_LEN()) \
   &&(time_after_eq(jiffies, (ADS_FILTER_GET_AGING_TIME_LEN() + (time)))))

/* ���IP�ײ���������Ϣ�Ƿ�ƥ�� ADS_FILTER_IPV4_HEADER_STRU */
#define ADS_FILTER_IS_IPHDR_MATCH(ipheader1, ipheader2)\
    ( ((ipheader1)->ulSrcAddr == (ipheader2)->ulSrcAddr) \
   && ((ipheader1)->ulDstAddr == (ipheader2)->ulDstAddr) \
   && ((ipheader1)->ucProtocol == (ipheader2)->ucProtocol) )

/* ���TCP���Ĺ��������Ƿ�ƥ�� ADS_FILTER_IPV4_TCP_STRU */
#define ADS_FILTER_IS_TCP_PKT_MATCH(tcppkt1, tcppkt2)\
    ( ((tcppkt1)->usSrcPort == (tcppkt2)->usSrcPort) \
   && ((tcppkt1)->usDstPort == (tcppkt2)->usDstPort) )

/* ���UDP���Ĺ��������Ƿ�ƥ�� ADS_FILTER_IPV4_UDP_STRU */
#define ADS_FILTER_IS_UDP_PKT_MATCH(udppkt1, udppkt2)\
    ( ((udppkt1)->usSrcPort == (udppkt2)->usSrcPort) \
   && ((udppkt1)->usDstPort == (udppkt2)->usDstPort) )

/* ���ICMP���Ĺ��������Ƿ�ƥ�� ADS_FILTER_IPV4_ICMP_STRU */
#define ADS_FILTER_IS_ICMP_PKT_MATCH(icmppkt1, icmppkt2)\
    ( ((icmppkt1)->usIdentifier == (icmppkt2)->usIdentifier) \
   && ((icmppkt1)->usSeqNum == (icmppkt2)->usSeqNum) )

/* ����Ƭ���Ĺ��������Ƿ�ƥ�� ADS_FILTER_IPV4_FRAGMENT_STRU */
#define ADS_FILTER_IS_FRAGMENT_MATCH(fragmentpkt1, fragmentpkt2)\
        ( (fragmentpkt1)->usIdentification == (fragmentpkt2)->usIdentification)

/* ���IPV6��ַ�Ƿ���ͬ ADS_IPV6_ADDR_UN */
#define ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(punIpv6Addr1, punIpv6Addr2) \
    (0 == ( ((punIpv6Addr1)->aulIpAddr[0] ^ (punIpv6Addr2)->aulIpAddr[0]) | \
            ((punIpv6Addr1)->aulIpAddr[1] ^ (punIpv6Addr2)->aulIpAddr[1]) | \
            ((punIpv6Addr1)->aulIpAddr[2] ^ (punIpv6Addr2)->aulIpAddr[2]) | \
            ((punIpv6Addr1)->aulIpAddr[3] ^ (punIpv6Addr2)->aulIpAddr[3]) ) )


/* ���˱�������ӳ���ϵ:
    ����TCP\UCP�������˱�����ֵΪԴ�˿ںŵ�8λ,
    ����ICMP�������˱�����ֵΪSequence Num��8λ,
    �������з�Ƭ��(����Ƭ)ʹ��IP Identification��8λ��Ϊ���� */
#define ADS_FILTER_GET_INDEX(pfilter) \
    ((VOS_UINT8)(VOS_NTOHS(*((VOS_UINT16 *)&((pfilter)->unFilter))) & 0xFF))


/*lint -e778 */
/*lint -e572 */
#ifndef VOS_NTOHL                   /* ��С�ֽ���ת��*/
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ffU) << 24) | \
                         (((x) & 0x0000ff00U) <<  8) | \
                         (((x) & 0x00ff0000U) >>  8) | \
                         (((x) & 0xff000000U) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ffU) << 24) | \
                         (((x) & 0x0000ff00U) <<  8) | \
                         (((x) & 0x00ff0000U) >>  8) | \
                         (((x) & 0xff000000U) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
ö����    : ADS_FILTER_PKT_TYPE_ENUM
ö��˵��  : ADS�������ݰ�����

  1.��    ��   : 2013��6��3��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
enum ADS_FILTER_PKT_TYPE_ENUM
{
    ADS_FILTER_PKT_TYPE_TCP,                                /* ���ݰ�����ΪTCP */
    ADS_FILTER_PKT_TYPE_UDP,                                /* ���ݰ�����ΪUDP */
    ADS_FILTER_PKT_TYPE_ICMP,                               /* ���ݰ�����ΪICMP */
    ADS_FILTER_PKT_TYPE_FRAGMENT,                           /* ���ݰ�����Ϊ��Ƭ��(����Ƭ) */

    ADS_FILTER_PKT_TYPE_BUTT
};
typedef VOS_UINT32 ADS_FILTER_PKT_TYPE_ENUM_UINT32;

/*****************************************************************************
ö����    : ADS_FILTER_ORIG_PKT_ENUM
ö��˵��  : ADS���ݰ�ԭʼ��������

  1.��    ��   : 2013��6��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
enum ADS_FILTER_ORIG_PKT_ENUM
{
    ADS_FILTER_ORIG_PKT_UL_IPV4_TCP,                                   /* ԭʼ���ݰ�����Ϊ����IPv4 TCP */
    ADS_FILTER_ORIG_PKT_UL_IPV4_UDP,                                   /* ԭʼ���ݰ�����Ϊ����IPv4 UDP */
    ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ,                               /* ԭʼ���ݰ�����Ϊ����IPv4 ECHO REQ */
    ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT,                    /* ԭʼ���ݰ�����Ϊ����IPv4 ��Ƭ��(����Ƭ) */
    ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT,                           /* ԭʼ���ݰ�����Ϊ���в�֧�ֵ�IPv4���� */
    ADS_FILTER_ORIG_PKT_UL_IPV6_PKT,                                   /* ԭʼ���ݰ�����Ϊ����IPv6���� */

    ADS_FILTER_ORIG_PKT_DL_IPV4_TCP,                                   /* ԭʼ���ݰ�����Ϊ����IPv4 TCP */
    ADS_FILTER_ORIG_PKT_DL_IPV4_UDP,                                   /* ԭʼ���ݰ�����Ϊ����IPv4 UDP */
    ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY,                             /* ԭʼ���ݰ�����Ϊ����IPv4 ECHO REPLY */
    ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR,                             /* ԭʼ���ݰ�����Ϊ����IPv4 ICMP����� */
    ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT,                        /* ԭʼ���ݰ�����Ϊ����IPv4 ��Ƭ��(��Ƭ) */
    ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT,                    /* ԭʼ���ݰ�����Ϊ����IPv4 ��Ƭ��(����Ƭ) */
    ADS_FILTER_ORIG_PKT_DL_IPV6_PKT,                                   /* ԭʼ���ݰ�����Ϊ����IPv6�� */

    ADS_FILTER_ORIG_PKT_BUTT
};
typedef VOS_UINT32 ADS_FILTER_ORIG_PKT_ENUM_UINT32;

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
  7 UNION����
*****************************************************************************/
/*****************************************************************************
 ��������     : ADS_IPV4_ADDR_UN
 ������˵��   : IPV4��ַ
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef union
{
    VOS_UINT8                           aucIpAddr[ADS_IPV4_ADDR_LEN];
    VOS_UINT32                          ulIpAddr;
} ADS_IPV4_ADDR_UN;

/*****************************************************************************
 ��������     : ADS_IPV6_ADDR_UN
 ������˵��   : IPV6��ַ
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef union
{
    VOS_UINT8                           aucIpAddr[ADS_IPV6_ADDR_LEN];
    VOS_UINT16                          ausIpAddr[ADS_IPV6_ADDR_HALF_LEN];
    VOS_UINT32                          aulIpAddr[ADS_IPV6_ADDR_QUARTER_LEN];
} ADS_IPV6_ADDR_UN;

/*****************************************************************************
  8 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : ADS_IPV4_HDR_STRU
 �ṹ˵��  : IPV4�ײ�
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpHdrLen          : 4;                /* header length */
    VOS_UINT8                           ucIpVersion         : 4;                /* version */
    VOS_UINT8                           ucTypeOfService;                        /* type of service */
    VOS_UINT16                          usTotalLen;                             /* total length */
    VOS_UINT16                          usIdentification;                       /* identification */
    VOS_UINT16                          usFlags_fo;                             /* flags and fragment offset field */
    VOS_UINT8                           ucTTL;                                  /* time to live*/
    VOS_UINT8                           ucProtocol;                             /* protocol */
    VOS_UINT16                          usCheckSum;                             /* checksum */
    ADS_IPV4_ADDR_UN                    unSrcAddr;                              /* source address */
    ADS_IPV4_ADDR_UN                    unDstAddr;                              /* dest address */
} ADS_IPV4_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_IPV6_HDR_STRU
 �ṹ˵��  : IPV6�ײ�
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPriority          : 4;                /* Priority  */
    VOS_UINT8                           ucIpVersion         : 4;                /* ip version, to be 6 */
    VOS_UINT8                           aucFlowLabel[3];                        /* flow lable */
    VOS_UINT16                          usPayloadLen;                           /* not include ipv6 fixed hdr len 40bytes */
    VOS_UINT8                           ucNextHdr;                              /* for l4 protocol or ext hdr */
    VOS_UINT8                           ucHopLimit;
    ADS_IPV6_ADDR_UN                    unSrcAddr;
    ADS_IPV6_ADDR_UN                    unDstAddr;
} ADS_IPV6_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_UDP_HDR_STRU
 �ṹ˵��  : UDP�ײ�
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;                              /* Դ�˿� */
    VOS_UINT16                          usDstPort;                              /* Ŀ�Ķ˿� */
    VOS_UINT16                          usLen;                                  /* UDP������ */
    VOS_UINT16                          usChecksum;                             /* UDPУ��� */
} ADS_UDP_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_TCP_HDR_STRU
 �ṹ˵��  : TCP�ײ�
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    VOS_UINT32                          ulSeqNum;
    VOS_UINT32                          ulAckNum;
    VOS_UINT16                          usOffset            : 4;
    VOS_UINT16                          usReserved          : 6;
    VOS_UINT16                          usUrg               : 1;
    VOS_UINT16                          usAck               : 1;
    VOS_UINT16                          usPsh               : 1;
    VOS_UINT16                          usRst               : 1;
    VOS_UINT16                          usSyn               : 1;
    VOS_UINT16                          usFin               : 1;
    VOS_UINT16                          usWindowSize;
    VOS_UINT16                          usCheckSum;
    VOS_UINT16                          usUrgentPoint;
} ADS_TCP_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_ICMP_ECHO_HDR_STRU
 �ṹ˵��  : ICMP��ECHO���ͱ����ײ��е�Identifier��Sequence Number��
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIdentifier;
    VOS_UINT16                          usSeqNum;

} ADS_ICMP_ECHO_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_ICMP_ERROR_HDR_STRU
 �ṹ˵��  : ICMP������ײ��е�Byte 4~Byte 8��
             ����֧�ֵĲ�������ͣ�type�ֱ�Ϊ3��4��5��11��12
             ��Щtype����Ӧ��Byte 4~Byte 8����Ȼ���岻����ͬ�������Ⱦ�Ϊ4��
             ��ͳһ����Ϊ��ͬ�Ľṹ�����ͣ����ڴ���
             �����͵ı��ĸ�ʽ����:

   Type = 3  -- Destination Unreachable Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 4  -- Source Quench Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 5  -- Redirect Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                 Gateway Internet Address                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 11 -- Time Exceeded Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             unused                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Type = 12 -- Parameter Problem Message
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Type      |     Code      |          Checksum             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |    Pointer    |                   unused                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Internet Header + 64 bits of Original Data Datagram      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUnUsed;

} ADS_ICMP_ERROR_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_ICMP_HDR_STRU
 �ṹ˵��  : ICMP�ײ�
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucCode;
    VOS_UINT16                          usCheckSum;

    union
    {
        ADS_ICMP_ECHO_HDR_STRU          stIcmpEcho;
        ADS_ICMP_ERROR_HDR_STRU         stIcmpError;
    }unIcmp;

} ADS_ICMP_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_IPV4_HEADER_STRU
 �ṹ˵��  : IPV4��IP�ײ���Ϣ�����ڹ���ƥ�������
 1.��    ��   : 2013��06��03��
   ��    ��   : l00198894
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSrcAddr;                              /* source address */
    VOS_UINT32                          ulDstAddr;                              /* dest address */
    VOS_UINT8                           ucProtocol;                             /* protocol */
    VOS_UINT8                           aucReserved[3];                         /* reserved */
} ADS_FILTER_IPV4_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_IPV4_TCP_STRU
 �ṹ˵��  : IPV4��TCP���Ĺ���ƥ������
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;                              /* source port */
    VOS_UINT16                          usDstPort;                              /* dest port */
} ADS_FILTER_IPV4_TCP_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_IPV4_UDP_STRU
 �ṹ˵��  : IPV4��UDP���Ĺ���ƥ������
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef ADS_FILTER_IPV4_TCP_STRU    ADS_FILTER_IPV4_UDP_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_IPV4_ICMP_STRU
 �ṹ˵��  : IPV4��ICMP���Ĺ���ƥ������
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSeqNum;                               /* ICMP�ײ��е�Sequence number */
    VOS_UINT16                          usIdentifier;                           /* ICMP�ײ��е�Identifier */
} ADS_FILTER_IPV4_ICMP_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_IPV4_FRAGMENT_STRU
 �ṹ˵��  : IPV4�����з�Ƭ���ģ���¼��Ƭ��Դ��ַ��Ŀ�ĵ�ַ��IP�ײ��е�
             Identification��Ϊ����ƥ������
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIdentification;                       /* IP�ײ��е�identification */
    VOS_UINT8                           aucReserved[2];                         /* reserved */
} ADS_FILTER_IPV4_FRAGMENT_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_IPV4_INFO_STRU
 �ṹ˵��  : IPV4�Ĺ���ƥ������
 1.��    ��   : 2013��06��03��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    ADS_FILTER_PKT_TYPE_ENUM_UINT32     enPktType;
    VOS_UINT8                           aucReserved[4];
    unsigned long                       ulTmrCnt;
    ADS_FILTER_IPV4_HEADER_STRU         stIPHeader;

    union
    {
        ADS_FILTER_IPV4_TCP_STRU        stTcpFilter;
        ADS_FILTER_IPV4_UDP_STRU        stUdpFilter;
        ADS_FILTER_IPV4_ICMP_STRU       stIcmpFilter;
        ADS_FILTER_IPV4_FRAGMENT_STRU   stFragmentFilter;
    }unFilter;

}ADS_FILTER_IPV4_INFO_STRU;


/*****************************************************************************
 �ṹ��    : ADS_FILTER_DECODE_DL_ICMP_FUNC
 �ṹ˵��  : ����ICMP������ʱ���ýṹ�壬������ӦICMP type�����ĺ���ָ�뼰
              ��Ӧԭʼ��������
 1.��    ��   : 2013��06��18��
   ��    ��   : l00198894
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef VOS_UINT32 (*ADS_FILTER_DECODE_DL_ICMP_FUNC)(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    ADS_FILTER_DECODE_DL_ICMP_FUNC      pFunc;
    ADS_FILTER_ORIG_PKT_ENUM_UINT32     enOrigPktType;
}ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU;
/*lint +e958 +e959 �޸���:l60609;*/


/*****************************************************************************
 �ṹ��    : ADS_FILTER_NODE_STRU
 �ṹ˵��  : ���й�������ڵ�ṹ��
 1.��    ��   : 2013��06��03��
   ��    ��   : l00198894
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    ADS_FILTER_IPV4_INFO_STRU           stFilter;
    HI_LIST_S                           stList;
}ADS_FILTER_NODE_STRU;

/*****************************************************************************
 �ṹ��    : ADS_FILTER_CTX_STRU
 �ṹ˵��  : ADS���˹������������
 1.��    ��   : 2013��06��03��
   ��    ��   : l00198894
   �޸�����   : V3R3 Share-PDP��Ŀ����
*****************************************************************************/
typedef struct
{
    HI_LIST_S                           astLists[ADS_FILTER_MAX_LIST_NUM];      /* ADS�������ݹ��˱� */
    ADS_IPV6_ADDR_UN                    unIPv6Addr;                             /* ADS���ڹ�������IPv6�������� */
    VOS_UINT32                          ulAgingTimeLen;                         /* ADS���˽ڵ��ϻ�ʱ��, ��λ���� */
    VOS_UINT8                           aucReserved[4];
}ADS_FILTER_CTX_STRU;


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID ADS_FILTER_ResetIPv6Addr(VOS_VOID);

VOS_VOID ADS_FILTER_InitListsHead(VOS_VOID);

VOS_VOID ADS_FILTER_InitCtx(VOS_VOID);

VOS_VOID* ADS_FILTER_HeapAlloc(VOS_UINT32 ulSize);

VOS_VOID ADS_FILTER_HeapFree(VOS_VOID *pAddr);

VOS_VOID ADS_FILTER_AddFilter(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter);

VOS_VOID ADS_FILTER_ResetLists(VOS_VOID);

VOS_VOID ADS_FILTER_Reset(VOS_VOID);

VOS_UINT32 ADS_FILTER_IsInfoMatch(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter1,
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter2);

VOS_UINT32 ADS_FILTER_Match(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter);

VOS_VOID ADS_FILTER_SaveIPAddrInfo(
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr);

VOS_UINT32 ADS_FILTER_DecodeUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_VOID ADS_FILTER_ProcUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType);

VOS_VOID ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4EchoReplyPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4IcmpErrorPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_VOID ADS_FILTER_DecodeDlIPv4TcpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_VOID ADS_FILTER_DecodeDlIPv4UdpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4FragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType);

VOS_UINT32 ADS_FILTER_DecodeDlIPv4Packet(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType);

VOS_UINT32 ADS_FILTER_ProcDlIPv4Packet(
    IMM_ZC_STRU                        *pstData);

VOS_UINT32 ADS_FILTER_ProcDlIPv6Packet(
    IMM_ZC_STRU                        *pstData);

VOS_UINT32 ADS_FILTER_ProcDlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType);

VOS_UINT32 ADS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber);

VOS_VOID ADS_FILTER_ShowStatisticInfo(VOS_VOID);

VOS_VOID ADS_FILTER_ResetStatisticInfo(VOS_VOID);

VOS_VOID ADS_FILTER_ShowFilterLists(VOS_VOID);

VOS_VOID ADS_FILTER_ShowIPv6Addr(VOS_VOID);




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

#endif /* end of AdsFilter.h */
