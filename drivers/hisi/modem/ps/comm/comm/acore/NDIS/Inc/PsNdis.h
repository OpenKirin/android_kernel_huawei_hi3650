

#ifndef __PSNDIS_H__
#define __PSNDIS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "ImmInterface.h"
#include "AtNdisInterface.h"
#include "AdsDeviceInterface.h"
#include "PsTypeDef.h"
#include "TTFComm.h"
#if (VOS_OS_VER != VOS_WIN32)
#include "NdisDrv.h"
#include <msp_nvim.h>
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*hujianbo:���º���������岻һ�£�����ȥ�����ĳ�ֱ�Ӱ���DrvInterface.h*/


/* DHCPѡ���������Լʱ�䳤�ȣ���λСʱ��366�� */
#define TTF_NDIS_DHCP_MAX_LEASE_HOUR            8784

/*IPV6 MTU NV��Ĭ��ȡֵ*/
#define TTF_NDIS_IPV6_MTU_DEFAULT               1500      /*��λΪ�ֽ�*/

#define Ndis_NvimItem_Read( ulId, pItemData, usItemDataLen ) \
    NDIS_NV_READX( MODEM_ID_0, ulId, (VOS_VOID *)(pItemData), usItemDataLen)

/*ARP*/
#define ETH_ARP_REQ_TYPE                0x0100      /*ARP Request*/
#define ETH_ARP_RSP_TYPE                0x0200      /*ARP Reply*/
#define ETH_ARP_FIXED_MSG_LEN           8           /*ARP�̶����ֳ���*/

/*IP*/
/*#define IPPACKET_MIN_LEN                (1500)
 */
#define IPV4_FIX_HDR_LEN                (20)       /* IPV4�̶�ͷ����*/
#define IPV4_HDR_TTL                    (128)      /* IPV4 ͷ�е�TTL�ֶ�Ĭ��ֵ*/

#define IP_IPV4_VERSION                 (4)        /* IP V4�汾��      */
#define IP_PROTOCOL_UDP                 (0x11)     /* IP����Э����UDP  */
#define IP_PROTOCOL_TCP                 (0x06)     /* IP����Э����TCP  */
#define IP_PROTOCOL_ICMP                (0x01)     /* IP����Э����ICMP */

/*DHCP����Ŀ�Ķ˿�67,����Ϊ�����ֽ���*/
#define UDP_DHCP_SERVICE_PORT           (0x4300)   /* DHCP����Ķ˿ں� */
#define UDP_DHCP_CLIENT_PORT            (0x4400)   /* DHCP Client�Ķ˿ں�*/

/*NDIS���������¼�*/
#define NDIS_UL_EVENT_RECIVE_USB_DATA      (0x0001)

/*NDIS���������¼�*/
#define NDIS_DL_EVENT_RECIVE_ADS_DATA      (0x0002)

/*Userplane huibo begin*/
#define NDIS_ENTITY_RABNUM                 (2)
#define NDIS_ENTITY_IPV4INDEX              (0)
#define NDIS_ENTITY_IPV6INDEX              (1)
#define NDIS_ENTITY_IPV4ADDRNUM            (9)

#define NDIS_ENTITY_IPV4                   (0x1)    /*��NDISʵ���Ӧ����֧��IPV4*/
#define NDIS_ENTITY_IPV6                   (0x2)    /*��NDISʵ���Ӧ����֧��IPV4*/
/*NDIS ����RabId���Index*/
/*#define NDIS_GetIndexByRabId(ucRabId)      ((ucRabId) - MIN_VAL_EPSID)*/
/*Userplane huibo end*/

#define NDIS_SPE_CACHE_HDR_SIZE         (IMM_MAC_HEADER_RES_LEN + sizeof(ETH_IPFIXHDR_STRU))


#if (VOS_OS_VER != VOS_WIN32)
    /*����PID,FID��������*/
    #define NDIS_TASK_PID     PS_PID_APP_NDIS
    #define NDIS_TASK_FID     PS_FID_APP_NDIS_PPP_DIPC

#ifdef MSP_GUNAS_AT_UNITE
    #define APP_AT_PID        WUEPS_PID_AT
#else
    #define APP_AT_PID        MSP_APP_DS_MUX_PID
#endif
#else
    #define NDIS_TASK_PID     PS_PID_NDIS
    /*#define NDIS_ULTASK_PID     LUEPS_PID_NDIS_UL
 */

    /*#define NDIS_ULTASK_FID     LUEPS_FID_APP_UL_NDIS
 */
    #define NDIS_TASK_FID     LUEPS_FID_APP_NDIS

    #define APP_AT_PID        LUEPS_PID_AT
#endif


#define NDIS_MODULE_UL          UE_MODULE_NDIS_UL
#define NDIS_MODULE_DL          UE_MODULE_NDIS_DL
#define NDIS_MODULE_COM          UE_MODULE_NDIS_COM

#define NDIS_L4_AT              0xF030 /* MSP AT��ģ��ID*/

/*A�˼��-�ؼ��¼��ϱ��¼�IDƫ��,�豣֤��PS����IDֵ���ظ�*/
#define NDIS_OM_KEY_EVENT_BASE_ID         0x11000



#define NDIS_OM_ID(ulModuleId, ulLogType)     DIAG_ID(ulModuleId, ulLogType)


#define NDIS_ReportEventLog(ulModuleId,ulLogType, ulEventID)
#define NDIS_LOG(ModulePID, SubMod, Level, pcString)
#define NDIS_LOG1(ModulePID, SubMod, Level, pcString, lPara1)
#define NDIS_LOG2(ModulePID, SubMod, Level, pcString, lPara1,lPara2)
#define NDIS_LOG3(ModulePID, SubMod, Level, pcString, lPara1,lPara2,lPara3)
#define NDIS_LOG4(ModulePID, SubMod, Level, pcString, lPara1,lPara2,lPara3,lPara4)

#define NDIS_INFO_LOG(ModuleId, String)
#define NDIS_INFO_LOG1(ModuleId, String,Para1)
#define NDIS_INFO_LOG2(ModuleId, String,Para1,Para2)
#define NDIS_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)
#define NDIS_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)


#define NDIS_WARNING_LOG(ModuleId, String)
#define NDIS_WARNING_LOG1(ModuleId, String,Para1)
#define NDIS_WARNING_LOG2(ModuleId, String,Para1,Para2)
#define NDIS_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)
#define NDIS_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define NDIS_ERROR_LOG(ModuleId, String)
#define NDIS_ERROR_LOG1(ModuleId, String,Para1)
#define NDIS_ERROR_LOG2(ModuleId, String,Para1,Para2)
#define NDIS_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)
#define NDIS_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)


/*ͨ��ModemId��BearerID��ϳ�ExBearerID����2bitΪModemId,��6bitΪBearerID*/
#define NDIS_FORM_EXBID(ModemId,BearerId)          ((VOS_UINT8)(((ModemId) << 6) | (BearerId)))

/*����չExBearerID�л��ModemId*/
#define NDIS_GET_MODEMID_FROM_EXBID(ExBearerId)    (VOS_UINT16)(((ExBearerId) & 0xC0) >> 6)

/*����չExBearerID�л��BearerID*/
#define NDIS_GET_BID_FROM_EXBID(ExBearerId)      (VOS_UINT8)((ExBearerId) & 0x3F)

#if (defined(CONFIG_BALONG_SPE))
#define NDIS_SPE_MEM_CB(pstImmZc)       ((NDIS_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))

/*lint -emacro({717}, NDIS_SPE_MEM_MAP)*/
#define NDIS_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == NDIS_IsSpeMem(pstImmZc))\
                {\
                    NDIS_SpeMemMapRequset(pstImmZc, ulLen);\
                }\
            } while(0)

/*lint -emacro({717}, NDIS_SPE_MEM_UNMAP)*/
#define NDIS_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == NDIS_IsSpeMem(pstImmZc))\
                {\
                    NDIS_SpeMemUnmapRequset(pstImmZc, ulLen);\
                }\
            } while(0)
#else
#define NDIS_SPE_MEM_MAP(pstImmZc, ulLen)
#define NDIS_SPE_MEM_UNMAP(pstImmZc, ulLen)
#endif



#ifdef _lint
#define ACPU_PID_ADS_UL     211
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
   ARP_PAYLOAD   = 0x0608,
   IP_PAYLOAD    = 0x0008,
   IPV6_PAYLOAD  = 0xdd86,
   GMAC_PAYLOAD_BUTT
}GMAC_PAYLOAD_TYPE_ENUM;

typedef enum IP_CLASS_TYPE
{
    IP_A_CLASS                              = 0x0,/*A����IP*/
    IP_B_CLASS                              = 0x1,/*B����IP*/
    IP_C_CLASS                              = 0x2,/*C����IP*/
    IP_CLASS_BUTT
}IP_CLASS_TYPE_ENUM;
typedef VOS_UINT32  IP_CLASS_TYPE_UINT32;

/*****************************************************************************
 �ṹ��    : NDIS_RAB_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NDIS��������ö��
*****************************************************************************/
typedef enum
{
    NDIS_RAB_NULL     = 0,                /*�ó���δ����*/
    NDIS_RAB_IPV4     = 1,                /*�ó���ֻ֧��IPV4*/
    NDIS_RAB_IPV6     = 2,                /*�ó���ֻ֧��IPV6*/
    NDIS_RAB_IPV4V6   = 3,                /*�ó���ͬʱ֧��IPV4��IPV6*/
    NDIS_RAB_BUTT
}NDIS_RAB_TYPE_ENUM;
typedef VOS_UINT8 NDIS_RAB_TYPE_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
#define NAS_NDIS_MAX_ITEM   11
/*****************************************************************************
�ṹ��    : IPV4_CFG_ITEM_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucUeIpV4Addr[IPV4_ADDR_LEN];
    VOS_UINT8    aucGwIpV4Addr[IPV4_ADDR_LEN];
    VOS_UINT8    aucNmaskIpV4Addr[IPV4_ADDR_LEN];
    VOS_UINT32   ulDnsServerNum;


} IPV4_CFG_ITEM_STRU;

/*****************************************************************************
�ṹ��    : IPV6_CFG_ITEM_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8    aucUeIpV6Addr[IPV6_ADDR_LEN];
    VOS_UINT8    aucGwIpV6Addr[IPV6_ADDR_LEN];
    VOS_UINT8    aucNmaskIpV6Addr[IPV6_ADDR_LEN];
} IPV6_CFG_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NDIS_ARPCFG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS NDIS����
*****************************************************************************/
typedef struct
{
    VOS_UINT32           ulIpV4ValidNum;
    IPV4_CFG_ITEM_STRU   autIpV4Cfg[NAS_NDIS_MAX_ITEM];

    VOS_UINT32           ulIpV6ValidNum;
    IPV4_CFG_ITEM_STRU   autIpV6Cfg[NAS_NDIS_MAX_ITEM];
}NAS_NDIS_ARPCFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IPV4_ADDR_ITEM_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[IPV4_ADDR_LEN];
    VOS_UINT32   ulIpAddr;
} IPV4_ADDR_ITEM_UN;

/*****************************************************************************
�ṹ��    : IPV6_ADDR_ITEM_UN
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[IPV6_ADDR_LEN];
    VOS_UINT32   ulIpAddr[4];
} IPV6_ADDR_ITEM_UN;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)   /*���ֽڶ���*/
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

/*lint -e958*/
/*lint -e959*/
    /*****************************************************************************
     �ṹ��    : ARP֡�ṹ
     Э����  :
     ASN.1���� :
     �ṹ˵��  :
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT8            aucDstAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT8            aucSrcAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT16           usFrameType;

        VOS_UINT16           usHardwareType;
        VOS_UINT16           usProtoType;
        VOS_UINT8            ucHardwareLen;
        VOS_UINT8            ucProtoLen;
        VOS_UINT16           usOpCode;

        VOS_UINT8            aucSenderAddr[ETH_MAC_ADDR_LEN];
        IPV4_ADDR_ITEM_UN    unSenderIP;
        VOS_UINT8            aucTargetAddr[ETH_MAC_ADDR_LEN];
        IPV4_ADDR_ITEM_UN    unTargetIP;

        VOS_UINT8   aucRev[18];
    }ETH_ARP_FRAME_STRU;
    /*****************************************************************************
         �ṹ��    :  ����SPE��MACͷ
         Э����  :
         ASN.1���� :
         �ṹ˵��  :
        *****************************************************************************/
        typedef struct
        {
            VOS_UINT8            aucDstAddr[ETH_MAC_ADDR_LEN];
            VOS_UINT8            aucSrcAddr[ETH_MAC_ADDR_LEN];
            VOS_UINT32           ulResv;
        }SPE_MAC_ETHER_HEADER_STRU;

    /*****************************************************************************
     �ṹ��    : ETH_IPFIXHDR_STRU
     Э����  :
     ASN.1���� :
     �ṹ˵��  : IP�̶�ͷ
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT8    ucIpHdrLen:4;                 /* header length */
        VOS_UINT8    ucIpVer:4;                    /* version */

        VOS_UINT8    ucServiceType;                /* type of service */
        VOS_UINT16   usTotalLen;                   /* total length */
        VOS_UINT16   usIdentification;             /* identification */
        VOS_UINT16   usOffset;                     /* fragment offset field */
        VOS_UINT8    ucTTL;                        /* time to live*/
        VOS_UINT8    ucProtocol;                   /* protocol */
        VOS_UINT16   usCheckSum;                   /* checksum */
        VOS_UINT32   ulSrcAddr;                    /* source address */
        VOS_UINT32   ulDestAddr;                   /* dest address */
    }ETH_IPFIXHDR_STRU;

    /*****************************************************************************
     �ṹ��    : ETH_UDPHDR_STRU
     Э����  :
     ASN.1���� :
     �ṹ˵��  : UDPͷ
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT16      usSrcPort;                 /* source port */
        VOS_UINT16      usDstPort;                 /* dest port */
        VOS_UINT16      usLen;                     /* udp length */
        VOS_UINT16      usChecksum;                /* udp check sum*/
    }ETH_UDPHDR_STRU;

    /*****************************************************************************
     �ṹ��    : IPV4 UDP���ṹ
     Э����  :
     ASN.1���� :
     �ṹ˵��  :
    *****************************************************************************/
    typedef struct
    {
        VOS_UINT8           aucDstAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT8           aucSrcAddr[ETH_MAC_ADDR_LEN];
        VOS_UINT16          usFrameType;

    ETH_IPFIXHDR_STRU   stIpHdt;
    VOS_UINT8           aucRev[4];
}ETHFRM_IPV4_PKT_STRU;

/*****************************************************************************
 �ṹ��    : IPV4 IP���ṹ
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    ETH_IPFIXHDR_STRU   stIpHdt;
    VOS_UINT8           aucRev[4];
}ETHFRM_IPV4_IPPKT_STRU;

/*lint -e959*/
/*lint -e958*/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#if (defined(CONFIG_BALONG_SPE))
/*****************************************************************************
 �ṹ��    : NDIS_SPE_MEM_CB_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SPE MEM CB�ṹ
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} NDIS_SPE_MEM_CB_STRU;
#endif

/*****************************************************************************
 �ṹ��    : NDIS_ARP_PERIOD_TIMER_STRU
 Э����  :
 ASN.1���� :��
 �ṹ˵��  : ARP���ڶ�ʱ���ṹ��
*****************************************************************************/
typedef struct
{
    HTIMER                              hTm;                                    /* ��ʱ��ָ�� */
    VOS_UINT32                          ulName;                                 /* ��ʱ������ */
    VOS_UINT32                          ulTimerValue;                           /* ��ʱ��ʱ��*/
}NDIS_ARP_PERIOD_TIMER_STRU;

/*****************************************************************************
 �ṹ��    : NDIS_IPV4_INFO_STRU���ṹ
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32           ulArpInitFlg;   /*�Ƿ��ѻ��UE��ARPӳ��*/
    VOS_UINT32           ulArpRepFlg;    /*ARP�����ͺ��ܵ�Reply��־*/
    IPV4_ADDR_ITEM_UN    unUeIpInfo;     /*UE IP,Դ��NAS����*/
    IPV4_ADDR_ITEM_UN    unGwIpInfo;     /*GW IP,Դ��NAS����*/
    IPV4_ADDR_ITEM_UN    unNmIpInfo;     /*NetMask,Դ��NAS����*/
    VOS_UINT8            aucUeMacAddr[ETH_MAC_ADDR_LEN];
    VOS_UINT8            aucMacFrmHdr[ETH_MAC_HEADER_LEN]; /*������̫֡ͷ���������*/
    NDIS_ARP_PERIOD_TIMER_STRU  stArpPeriodTimer; /*Ϊ��ͬ64λ����ϵͳ���ݣ�������8�ֽڶ���λ��*/

    /*DHCP Server Info*/
    VOS_UINT32           ulIpAssignStatus;
    IPV4_ADDR_ITEM_UN    unPrimDnsAddr;
    IPV4_ADDR_ITEM_UN    unSecDnsAddr;
    IPV4_ADDR_ITEM_UN    unPrimWinsAddr;
    IPV4_ADDR_ITEM_UN    unSecWinsAddr;

} NDIS_IPV4_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NDIS_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    NDIS_RAB_TYPE_UINT8             ucRabType;
    VOS_UINT8                       ucRabId; /*�������ExRabId��ֵ*/
    PS_BOOL_ENUM_UINT8              enUsed;  /*PS_TRUE:��ʵ�屻ʹ�ã�PS_FALSE:��ʵ�����*/
    VOS_UINT8                       ucRev;   /*Ԥ���ֽ�*/
    UDI_HANDLE                      ulHandle;
    NDIS_IPV4_INFO_STRU             stIpV4Info;
    VOS_INT32                       lSpePort;
    VOS_UINT32                      ulSpeIpfFlag;
} NDIS_ENTITY_STRU;

/*****************************************************************************
�ṹ��    : NDIS_STAT_INFO_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : NDISͳ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulDicardUsbFrmNum;        /*���ж�����USB���ݰ�����*/
    VOS_UINT32      ulRecvUsbPktSuccNum;      /*���гɹ����յ�USB�İ��ĸ���*/
    VOS_UINT32      ulSendPktToAdsSucNum;     /*���з��͵�ADS�ɹ��ĸ���*/
    VOS_UINT32      ulDicardAdsPktNum;        /*���б�������ADS ���ݰ�NUM*/
    VOS_UINT32      ulRecvAdsPktSuccNum;      /*���д�ADS�յ����ɹ�����*/
    VOS_UINT32      ulGetIpv6MacFailNum;      /*���з���ʱ��ȡIPV6 MAC��ַʧ�ܸ��� */
    VOS_UINT32      ulDlPktDiffRabNum;        /*�������ݰ����ͺͳ������Ͳ�һ�¸���*/
    VOS_UINT32      ulAddMacHdrFailNum;       /*���MACͷʧ�ܵ�ͳ��*/
    VOS_UINT32      ulDlSendPktFailNum;       /*���Ͱ�ʧ�ܵ�ͳ����*/
    VOS_UINT32      ulDlSendPktSuccNum;       /*���гɹ��������ݰ��������ͳ����*/

    VOS_UINT32      ulRecvDhcpPktNum;         /*���յ���DHCP��*/

    /*ARP ͳ����Ϣ*/
    VOS_UINT32      ulRecvArpReq;             /*�յ���ARP Request��*/
    VOS_UINT32      ulRecvArpReply;           /*�յ���ARP Reply��*/
    VOS_UINT32      ulProcArpError;           /*����ARPʧ�ܸ���*/
    VOS_UINT32      ulSendArpReqSucc;         /*����ARP Request�ɹ���*/
    VOS_UINT32      ulSendArpReqFail;         /*����ARP Requestʧ����*/
    VOS_UINT32      ulArpReplyNotRecv;        /*ARP����û���յ�Rely�ļ���*/
    VOS_UINT32      ulSendArpReply;           /*����ARP REPLY����*/
    VOS_UINT32      ulSendArpDhcpNDFailNum;   /*����ARP��DHCP��ND��ʧ�ܸ���*/
}NDIS_STAT_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern NDIS_STAT_INFO_STRU        g_stNdisStatStru;
#define   NDIS_STAT_UL_DISCARD_USBPKT(n)              (g_stNdisStatStru.ulDicardUsbFrmNum          += (n))
#define   NDIS_STAT_UL_RECV_USBPKT_SUCC(n)            (g_stNdisStatStru.ulRecvUsbPktSuccNum        += (n))
#define   NDIS_STAT_UL_SEND_ADSPKT(n)                 (g_stNdisStatStru.ulSendPktToAdsSucNum        += (n))
#define   NDIS_STAT_DL_DISCARD_ADSPKT(n)              (g_stNdisStatStru.ulDicardAdsPktNum          += (n))
#define   NDIS_STAT_DL_RECV_ADSPKT_SUCC(n)            (g_stNdisStatStru.ulRecvAdsPktSuccNum        += (n))
#define   NDIS_STAT_DL_GET_IPV6MAC_FAIL(n)            (g_stNdisStatStru.ulGetIpv6MacFailNum        += (n))
#define   NDIS_STAT_DL_PKT_DIFF_RAB_NUM(n)            (g_stNdisStatStru.ulDlPktDiffRabNum          += (n))
#define   NDIS_STAT_DL_ADDMACFRM_FAIL(n)              (g_stNdisStatStru.ulAddMacHdrFailNum         += (n))
#define   NDIS_STAT_DL_SEND_USBPKT_FAIL(n)            (g_stNdisStatStru.ulDlSendPktFailNum         += (n))
#define   NDIS_STAT_DL_SEND_USBPKT_SUCC(n)            (g_stNdisStatStru.ulDlSendPktSuccNum         += (n))

#define   NDIS_STAT_UL_RECV_DHCPPKT(n)                (g_stNdisStatStru.ulRecvDhcpPktNum           += (n))

#define   NDIS_STAT_UL_RECV_ARP_REQUEST(n)            (g_stNdisStatStru.ulRecvArpReq               += (n))
#define   NDIS_STAT_DL_RECV_ARP_REPLY(n)              (g_stNdisStatStru.ulRecvArpReply             += (n))
#define   NDIS_STAT_PROC_ARP_FAIL(n)                  (g_stNdisStatStru.ulProcArpError             += (n))
#define   NDIS_STAT_DL_SEND_ARP_REQUEST_SUCC(n)       (g_stNdisStatStru.ulSendArpReqSucc           += (n))
#define   NDIS_STAT_DL_SEND_ARP_REQUEST_FAIL(n)       (g_stNdisStatStru.ulSendArpReqFail           += (n))
#define   NDIS_STAT_ARPREPLY_NOTRECV(n)               (g_stNdisStatStru.ulArpReplyNotRecv          += (n))
#define   NDIS_STAT_DL_SEND_ARP_REPLY(n)              (g_stNdisStatStru.ulSendArpReply             += (n))
#define   NDIS_STAT_DL_SEND_ARPDHCPPKT_FAIL(n)        (g_stNdisStatStru.ulSendArpDhcpNDFailNum     += (n))

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 Ndis_Init( VOS_VOID );
extern VOS_UINT32 Ndis_ProcArpMsg(ETH_ARP_FRAME_STRU* pstArpMsg, VOS_UINT8 ucRabId);
extern VOS_VOID Ndis_UlNcmFrmProc(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pstImmZc);
extern VOS_UINT32 Ndis_DlSendNcm(VOS_UINT8 ucRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);
extern VOS_UINT32  Ndis_SendRequestArp(NDIS_IPV4_INFO_STRU  *pstArpInfoItem, VOS_UINT8 ucRabId);
extern VOS_UINT32 Ndis_ChkRabIdValid(VOS_UINT8 ucRabId);
extern NDIS_ENTITY_STRU* NDIS_GetEntityByRabId(VOS_UINT8 ucExRabId);
extern NDIS_ENTITY_STRU* NDIS_AllocEntity(VOS_VOID);
extern VOS_VOID Ndis_StopARPTimer(NDIS_ARP_PERIOD_TIMER_STRU *pstArpPeriodTimer);

extern VOS_UINT32 Ndis_MsgHook (VOS_UINT8 *pucData,VOS_UINT32 ulLength,
     AT_NDIS_MSG_TYPE_ENUM_UINT32 enMsgId);

extern VOS_VOID Ndis_LomTraceRcvUlData(VOS_VOID);
extern VOS_VOID Ndis_LomTraceRcvDlData(VOS_VOID);
extern VOS_UINT8 Ndis_FindRabIdBySpePort(VOS_INT32 lPort, VOS_UINT16 usFrameType);
extern VOS_UINT8 Ndis_FindRabIdByHandle(UDI_HANDLE ulhandle, VOS_UINT16 usFrameType);
extern VOS_UINT32 Ndis_DlUsbSendNcm(VOS_UINT8 ucExRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);



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

#endif /* end of LUPNdis.c */

