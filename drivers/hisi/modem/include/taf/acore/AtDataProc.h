


#ifndef __AT_DATA_PROC_H__
#define __AT_DATA_PROC_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "mdrv.h"

#include "AtCtx.h"
#include "AtInputProc.h"
#include "AtNdisInterface.h"
#include "AtRnicInterface.h"
/* Modified by m00217266 for L-C��������Ŀ, 2014-2-11, begin */
#include "RnicConfigInterface.h"
#include "AdsInterface.h"
/* Modified by m00217266 for L-C��������Ŀ, 2014-2-11, end */
#include "AtPppInterface.h"

#include "FcInterface.h"
#include "PppInterface.h"

#include "TafApsApi.h"

#include "AtCmdMsgProc.h"

#include "AtInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

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

#define AT_PPP_CODE_REQ                 (1)
#define AT_PPP_CODE_ACK                 (2)
#define AT_PPP_DEF_ID                   (1)

#define AT_AP_PPP_CODE_CHALLENGE        (1)
#define AT_AP_PPP_CODE_RESPONSE         (2)

#define AT_AP_PPP_PRIMARY_DNS           (129)
#define AT_AP_PPP_PRIMARY_WINNS         (130)
#define AT_AP_PPP_SECONDARY_DNS         (131)
#define AT_AP_PPP_SECONDARY_WINNS       (132)

#define AT_AP_PPP_CHAP_CHALLENGE_LEN    (16)
#define AT_AP_PPP_CHAP_RESPONSE_LEN     (16)
#define AT_AP_MAX_IPV4_ADDR_LEN         (15)

#define AT_AP_AUTH_NO_PROTO             (0)
#define AT_AP_AUTH_PAP_PROTO            (1)
#define AT_AP_AUTH_CHAP_PROTO           (2)

#define AT_DEF_DISPLAY_SPEED            (81920000)                              /* 10 M*/

#define AT_MAX_IPV4_DNS_LEN             (16)
#define AT_MAX_IPV4_NBNS_LEN            (16)
#define AT_MAX_IPV6_DNS_LEN             (16)
#define AT_MAX_IPV6_NBNS_LEN            (16)

#define AT_MAX_IPV6_STR_DOT_NUM          (3)
#define AT_MAX_IPV4V6_STR_COLON_NUM      (6)
#define AT_MAX_IPV6_STR_COLON_NUM        (7)

#define AT_IPV6_STR_MAX_TOKENS                  (16)                            /* IPV6�ַ�����ʽʹ�õķָ������������ */
#define AT_IPV4_STR_DELIMITER                   '.'                             /* RFCЭ��ʹ�õ�IPV4�ı���﷽ʽʹ�õķָ��� */
#define AT_IPV6_STR_DELIMITER                   ':'                             /* RFC2373ʹ�õ�IPV6�ı���﷽ʽʹ�õķָ��� */

#if (FEATURE_ON == FEATURE_IPV6)
#define AT_GetIpv6Capability()                  (AT_GetCommPsCtxAddr()->ucIpv6Capability)
#endif

#define AT_PS_GET_SHARE_PDP_FLG()               (AT_GetCommPsCtxAddr()->ucSharePdpFlag)

#define AT_APP_GetPdpEntInfoAddr()              (&g_stAtAppPdpEntity)

#define AT_APP_GetDailParaAddr()                (&g_stAtAppDialPara)

#define AT_APP_GetFirstActPdpType()             (g_enAtAppFirstActPdpType)
#define AT_APP_SetFirstActPdpType(ucPdpType)    (g_enAtAppFirstActPdpType = (ucPdpType))

#define AT_APP_GetActPdpType()                  (g_enAtAppActPdpType)
#define AT_APP_SetActPdpType(ucPdpType)         (g_enAtAppActPdpType = (ucPdpType))

/* ��ȡAPP�ͻ���ID */
#define AT_APP_GET_CLIENT_ID()          (gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId)

/* ��ȡAPP���Ŷ˿����� */
#define AT_APP_GET_USR_PORT_INDEX()     (g_stAtAppPdpEntity.stUsrInfo.enPortIndex)

/* ��ȡAPP�����û��·���cid */
#define AT_APP_GET_USR_CID()            (g_stAtAppPdpEntity.stUsrInfo.ucUsrCid)


/* ��ȡNDIS���ŵ�ǰ����������� */
#define AT_APP_GET_CURR_CMD_OPT()       (gastAtClientTab[AT_APP_GET_USR_PORT_INDEX()].CmdCurrentOpt)

#define AT_APP_GetRaInfoAddr()                  (&g_stAtAppRaInfo)

/*----------------------------------------------------------------------
   ^NDISSTAT: <stat>[,<err_code>[,<wx_stat>[,<PDP_type]]]
   <err_code> value defined as follows:
   0      - Unknown error/Unspecified error
   others - (E)SM Cause
            SM Cause is defined in TS 24.008 section 10.5.6.6
            ESM Cause is defined in TS 24.301 section 9.9.4.4
*---------------------------------------------------------------------*/
#define AT_NDISSTAT_ERR_UNKNOWN                 (0)

/* NDIS��������NDISCONN��NDISDUP����������� index */
#define AT_NDIS_CID_IDX                         (0)
#define AT_NDIS_CONN_IDX                        (1)
#define AT_NDIS_APN_IDX                         (2)
#define AT_NDIS_NAME_IDX                        (3)
#define AT_NDIS_PWD_IDX                         (4)
#define AT_NDIS_AUTH_IDX                        (5)

#define AT_NDIS_GetPdpEntInfoAddr()             (&g_stAtNdisDhcpPara)

/* ��ȡNDIS�ͻ���ID */
#define AT_NDIS_GET_CLIENT_ID()         (gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].usClientId)

/* ��ȡNDIS���Ŷ˿����� */
#define AT_NDIS_GET_USR_PORT_INDEX()    (g_stAtNdisDhcpPara.stUsrInfo.enPortIndex)

/* ��ȡNDIS�����û��·���cid */
#define AT_NDIS_GET_USR_CID()           (g_stAtNdisDhcpPara.stUsrInfo.ucUsrCid)



/* ��ȡNDIS���ŵ�ǰ����������� */
#define AT_NDIS_GET_CURR_CMD_OPT()      (gastAtClientTab[AT_NDIS_GET_USR_PORT_INDEX()].CmdCurrentOpt)

#define AT_GetNdisConnParaAddr()                (&g_stAtNdisConnPara)

#define AT_APS_IP6_ADDR_PREFIX_BYTE_LEN  (8)

#define AT_MAC_LEN                       (6)
#define AT_IPV6_ADDR_PREFIX_BYTE_LEN     (8)
#define AT_IPV6_ADDR_PREFIX_BIT_LEN      (64)

#define AT_REG_FC                        (1)
#define AT_DEREG_FC                      (0)

/* QOS_TRAFFIC_CLASS */
#define AT_QOS_TRAFFIC_CLASS_SUBSCRIBE                (0)
#define AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (1)
#define AT_QOS_TRAFFIC_CLASS_STREAMING                (2)
#define AT_QOS_TRAFFIC_CLASS_INTERACTIVE              (3)
#define AT_QOS_TRAFFIC_CLASS_BACKGROUND               (4)

/* Deleted by m00217266 for L-C��������Ŀ, 2014-1-26, begin */
#if 0
/* APP QOS: */
#define AT_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (0)
#define AT_APP_QOS_TRAFFIC_CLASS_STREAMING                (1)
#define AT_APP_QOS_TRAFFIC_CLASS_INTERACTIVE              (2)
#define AT_APP_QOS_TRAFFIC_CLASS_BACKGROUND               (3)

/* APP QOS: Traffic Handling */
#define AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1            (1)
#define AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2            (2)
#define AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_3            (3)

/* APP QOS: Source Statistic Descriptor */
#define AT_APP_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN           (0)
#define AT_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH            (1)

/* APP QOS: Transfer Delay */
#define AT_APP_QOS_TRANSFER_DELAY_150MS                   (150)

/* APP QOS: Signal Ind */
#define AT_APP_QOS_SIGNAL_IND_NOT_OPTIMISE                (0)
#define AT_APP_QOS_SIGNAL_IND_OPTIMISE                    (1)
#endif
/* Deleted by m00217266 for L-C��������Ŀ, 2014-1-26, end */


#define AT_IPV6_STR_RFC2373_TOKENS                    (8)   /* �ָ�����ǵ������� */



#define AT_IPPROTO_UDP                  (0x11)              /* IPͷ����UDPЭ���*/
#define AT_IP_VERSION                   (4)                 /* IPͷ����IP V4�汾�� */
#define AT_IP_DEF_TTL                   (0xFF)              /* IPͷ����IP TTLȱʡֵ */
#define AT_IP_RAND_ID                   (61468)             /* IPͷ��IDֵ�����ȡ*/
#define AT_IP_HDR_LEN                   (20)                /* IP ͷ������ */
#define AT_UDP_HDR_LEN                  (8)                 /* UDP ͷ������ */

/* �����û���CID��ĿǰӦ��ֻ���·�1��2��3 */
#define AT_PS_USER_CID_1                (1)
#define AT_PS_USER_CID_2                (2)
#define AT_PS_USER_CID_3                (3)

/* PS�������ЧCID */
#define AT_PS_CALL_INVALID_CID          (0xFF)
#define AT_PS_CALL_INVALID_CALLID       (0xFF)

/* IPV6��ַ��8���ֽ�ȫ�㣬����Ϊ����Ч�� */
#define AT_PS_IS_IPV6_ADDR_IID_VALID(aucIpv6Addr)\
            !((aucIpv6Addr[8] == 0x00) && (aucIpv6Addr[9] == 0x00)\
             && (aucIpv6Addr[10] == 0x00) && (aucIpv6Addr[11] == 0x00)\
             && (aucIpv6Addr[12] == 0x00) && (aucIpv6Addr[13] == 0x00)\
             && (aucIpv6Addr[14] == 0x00) && (aucIpv6Addr[15] == 0x00))


#if (FEATURE_ON == FEATURE_IPV6)
/* IPv6 �ӿ�ID, ����Ϊ64bit */
#define AT_PS_IPV6_IID_LEN              (8)
#define AT_PS_IPV6_IID_OFFSET           (8)

#endif

#define AT_PS_INVALID_RMNET_ID   (0xFFFF)

#if (FEATURE_ON == FEATURE_IPV6)
#define AT_PS_IS_PDP_TYPE_SUPPORT(pdptype)  \
            ( (TAF_PDP_IPV4 == (pdptype))   \
             || (TAF_PDP_IPV6 == (pdptype)) \
             || (TAF_PDP_IPV4V6 == (pdptype)))
#else
#define AT_PS_IS_PDP_TYPE_SUPPORT(pdptype)  \
            (TAF_PDP_IPV4 == (pdptype))
#endif

#define AT_PS_IS_RABID_VALID(ucRabId)\
    (((ucRabId) >= AT_PS_MIN_RABID) && ((ucRabId) <= AT_PS_MAX_RABID))

#define AT_PS_GET_CURR_CMD_OPT(index)   (gastAtClientTab[index].CmdCurrentOpt)
#define AT_PS_GET_CURR_DATA_MODE(index) (gastAtClientTab[index].DataMode)
#define AT_PS_GET_PPPID(index)          (gastAtClientTab[index].usPppId)

#define AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_PTR()      (g_astAtRptConnectedResultTab)
#define AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_SIZE()     (AT_ARRAY_SIZE(g_astAtRptConnectedResultTab))

#define AT_PS_GET_RPT_END_RSLT_FUNC_TBL_PTR()       (g_astAtRptEndedResultTab)
#define AT_PS_GET_RPT_END_RSLT_FUNC_TBL_SIZE()      (AT_ARRAY_SIZE(g_astAtRptEndedResultTab))

#define AT_PS_GET_REG_FC_POINT_FUNC_TBL_PTR()       (g_astAtRegFCPointTab)
#define AT_PS_GET_REG_FC_POINT_FUNC_TBL_SIZE()      (AT_ARRAY_SIZE(g_astAtRegFCPointTab))

#define AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_PTR()     (g_astAtDeRegFCPointTab)
#define AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_SIZE()    (AT_ARRAY_SIZE(g_astAtDeRegFCPointTab))

#define AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_PTR()    (g_astAtSndPdpActIndTab)
#define AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtSndPdpActIndTab))

#define AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_PTR()  (g_astAtSndPdpDeActIndTab)
#define AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_SIZE() (AT_ARRAY_SIZE(g_astAtSndPdpDeActIndTab))

#define AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR()    (g_astAtChdataRnicRmNetIdTab)
#define AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtChdataRnicRmNetIdTab))


#define AT_PS_DIAL_RAT_TYPE_NO_ASTRICT              (0)
#define AT_PS_DIAL_RAT_TYPE_1X_OR_HRPD              (24)
#define AT_PS_DIAL_RAT_TYPE_LTE_OR_EHRPD            (36)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum AT_PDP_STATUS_ENUM
{
    AT_PDP_STATUS_DEACT                    = 0,
    AT_PDP_STATUS_ACT                      = 1,
    AT_PDP_STATUS_BUTT
};
typedef VOS_UINT32 AT_PDP_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö������   : AT_PDP_TYPE_ENUM_ENUM
 Э����   :
 ASN.1 ���� :
 ö��˵��   : PDP����
*****************************************************************************/
enum AT_PDP_TYPE_ENUM
{
    AT_PDP_IPV4                         = 1,
    AT_PDP_IPV6                         = 2,
    AT_PDP_IPV4V6                       = 3,
    AT_PDP_PPP                          = 4,
    AT_PDP_TYPE_BUTT
};
typedef VOS_UINT8 AT_PDP_TYPE_ENUM_ENUM_U8;

/*****************************************************************************
 �ṹ����   : AT_IPV6_STR_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IPV6 String��ʽö��
              HEXΪRFC2373Ҫ��ʹ��':'��Ϊ�ָ���
              DEXΪRFCҪ��ʹ��'.'��Ϊ�ָ���
*****************************************************************************/
enum AT_IPV6_STR_TYPE_ENUM
{
    AT_IPV6_STR_TYPE_HEX                = 0x01,
    AT_IPV6_STR_TYPE_DEC                = 0x02,

    AT_IPV6_STR_TYPE_BUTT               = 0xFF
};
typedef VOS_UINT8 AT_IPV6_STR_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : AT_IP_ADDR_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ������SOURCE����LOCAL��IP ADDR
*****************************************************************************/
enum AT_IP_ADDR_TYPE_ENUM
{
    AT_IP_ADDR_TYPE_SOURCE              = 0x01,
    AT_IP_ADDR_TYPE_LOCAL               = 0x02,

    AT_IP_ADDR_TYPE_BUTT                = 0xFF
};
typedef VOS_UINT8 AT_IP_ADDR_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö������   : AT_HILINK_MODE_ENUM
 Э����   :
 ASN.1 ���� :
 ö��˵��   : HiLinkģʽ
*****************************************************************************/
enum AT_HILINK_MODE_ENUM
{
    AT_HILINK_NORMAL_MODE,
    AT_HILINK_GATEWAY_MODE,
    AT_HILINK_MODE_BUTT
};
typedef VOS_UINT8 AT_HILINK_MODE_ENUM_U8;

/* APP����״̬*/
/*****************************************************************************
 ö������   : AT_APP_CONN_STATE_ENUM
 Э����   :
 ASN.1 ���� :
 ö��˵��   : APP����״̬
*****************************************************************************/
enum AT_APP_CONN_STATE_ENUM
{
    AT_APP_DIALING,                     /*0: indicates is connecting*/
    AT_APP_DIALED,                      /*1: indicates connected*/
    AT_APP_UNDIALED,                    /*2: indicates disconnected*/
    AT_APP_BUTT
};
typedef VOS_UINT32 AT_APP_CONN_STATE_ENUM_U32;

/*****************************************************************************
 PPP���ź������������ʾ���������������:
 1.2Gģʽ�£�����ݵ�ǰפ����С��ģʽ��GSM/GPRS/EDGE�������������ݵ���ʾ,��Ӧ����:
     GSM          - 9600
     GPRS         - 85600
     GPRS Class33 - 107800
     EDGE         - 236800
     EDGE Class33 - 296000
     Ĭ�� -
 2.3gģʽ�£������RRC�汾��HSDPA��category��Ϣ�������������ݵ���ʾ����Ӧ����:
     RRC�汾ΪR99   - 384000
     RRC�汾Ϊ��R99 - �ж�HSDPA��category��Ϣ
                   6  - 3600000
                   8  - 7200000
                   9  - 10200000
                   10 - 14400000
                   12 - 1800000
                   14 - 21600000
                   18 - 28800000
                   24 - 43200000
                   26 - 57600000
                   28 - 86400000
     ����չ��category�Ļ���Ĭ�� - 21600000
     ����չ��category�Ļ���Ĭ�� - 7200000
*****************************************************************************/
enum PPP_RATE_DISPLAY_ENUM
{
    PPP_RATE_DISPLAY_GSM = 0,
    PPP_RATE_DISPLAY_GPRS,
    PPP_RATE_DISPLAY_GPRS_CALSS33,
    PPP_RATE_DISPLAY_EDGE,
    PPP_RATE_DISPLAY_EDGE_CALSS33,

    PPP_RATE_DISPLAY_R99,
    PPP_RATE_DISPLAY_DPA_CATEGORY_6,
    PPP_RATE_DISPLAY_DPA_CATEGORY_8,
    PPP_RATE_DISPLAY_DPA_CATEGORY_9,
    PPP_RATE_DISPLAY_DPA_CATEGORY_10,
    PPP_RATE_DISPLAY_DPA_CATEGORY_12,
    PPP_RATE_DISPLAY_DPA_CATEGORY_14,
    PPP_RATE_DISPLAY_DPA_CATEGORY_18,
    PPP_RATE_DISPLAY_DPA_CATEGORY_24,
    PPP_RATE_DISPLAY_DPA_CATEGORY_26,
    PPP_RATE_DISPLAY_DPA_CATEGORY_28,

    PPP_RATE_DISPLAY_BUTT
};
typedef VOS_UINT32 PPP_RATE_DISPLAY_ENUM_UINT32;


/*****************************************************************************
 ö����    : AT_CH_DATA_CHANNEL_ENUM
 �ṹ˵��  : AT^CHDATA�������õ�<datachannelid>��ȡֵ


  1.��    ��   : 2013��05��07��
    ��    ��   : y00213812
    �޸�����   : V9R1 IPv6&TAF/SM Project����ö��

*****************************************************************************/
enum AT_CH_DATA_CHANNEL_ENUM
{
    AT_CH_DATA_CHANNEL_ID_1             = 1,
    AT_CH_DATA_CHANNEL_ID_2,
    AT_CH_DATA_CHANNEL_ID_3,
    AT_CH_DATA_CHANNEL_ID_4,
    AT_CH_DATA_CHANNEL_ID_5,
    AT_CH_DATA_CHANNEL_ID_6,
    AT_CH_DATA_CHANNEL_ID_7,

    AT_CH_DATA_CHANNEL_BUTT
};
typedef VOS_UINT32 AT_CH_DATA_CHANNEL_ENUM_UINT32;



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDLEnqueuedPkts;                       /*�������ݰ��ܸ���*/
    VOS_UINT32                          ulDLDequeuedPkts;                       /*���з��͸���*/
    VOS_UINT32                          ulDLDroppedPkts;                        /*���ж�������*/
    VOS_UINT32                          ulDLMaxBlkPkts;                         /*���ж��������������*/
    VOS_UINT32                          ulDLMaxDequeueOnce;                     /*���е��η��Ͱ��������ֵ*/
} AT_AP_DL_DATA_Q_STAT_ST;


/* DHCP���ã�ȫ������*/
typedef struct
{
    VOS_UINT32                          ulIPAddr;                               /* IP ��ַ���������*/
    VOS_UINT32                          ulSubNetMask;                           /* ���������ַ������IP��ַ����*/
    VOS_UINT32                          ulGateWay;                              /* ���ص�ַ��Ҳ�Ǳ�DHCP Server�ĵ�ַ*/
    VOS_UINT32                          ulPrimDNS;                              /* �� DNS��ַ���������*/
    VOS_UINT32                          ulSndDNS;                               /* �� DNS��ַ���������*/
}AT_DHCP_CONFIG_STRU;


typedef struct
{
    VOS_UINT16                          usClientID;                             /* Client ID*/
    VOS_UINT8                           ucRabID;                                /* Rab ID*/
    VOS_UINT8                           ucCid;                                  /* CID*/
    AT_PDP_STATE_ENUM_U8                enState;                                /* State*/
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulFlowCtrlState;                        /* Flow Ctrl State ; 1: flow ctrl ,0: no flow ctrl*/
    VOS_UINT32                          ulSpeed;                                /* Um Speed*/

    VOS_UINT32                          ulDLMaxRate;                            /* ���������������*/
    VOS_UINT32                          ulULMaxRate;                            /* ���������������*/
    VOS_UINT32                          ulDLCurrentRate;                        /* ��ǰ��������*/
    VOS_UINT32                          ulULCurrentRate;                        /* ��ǰ��������*/
    VOS_UINT32                          ulRateCalcPeriod;                       /* ����ͳ������*/
    AT_DHCP_CONFIG_STRU                 stDhcpCfg;
}AT_CTRL_ENTITY_STRU;

typedef struct AT_DHCP_PARA
{
    VOS_UINT16                          usClientID;                             /* Client ID*/
    VOS_UINT8                           ucRabID;                                /* Rab ID*/
    VOS_UINT8                           ucCid;                                  /* CID*/
    VOS_UINT32                          ulSpeed;                                /* Um Speed*/
    VOS_UINT32                          ulDLMaxRate;                            /* ���������������*/
    VOS_UINT32                          ulULMaxRate;                            /* ���������������*/
    AT_DHCP_CONFIG_STRU                 stDhcpCfg;
}AT_DHCP_PARA_STRU;

typedef struct
{
  VOS_UINT8                             ucCode;                                 /* Request code */
  VOS_UINT8                             ucId;                                   /* Identification */
  VOS_UINT16                            usLength;                               /* Length of packet */
}AT_PPP_FRAME_HEAD_STRU;

/* IP��ַ�ṹ U32���ͣ������ֽ���洢*/
typedef struct
{
    VOS_UINT32                          ulIpAddr;                               /*U32���ͣ������ֽ���洢*/
}IN_ADDR_ST;


typedef struct
{
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucCode;
    VOS_UINT16                          usCheckSum;
    VOS_UINT16                          usId;
    VOS_UINT16                          usSeq;
}ICMP_ECHO_HEAD_ST;

typedef struct
{
    VOS_UINT32                          ulIPAddr;                               /* IP ��ַ*/
    VOS_UINT32                          ulPrimDNS;                              /* �� DNS��ַ*/
    VOS_UINT32                          ulSndDNS;                               /* �� DNS��ַ*/
    VOS_UINT32                          ulPrimWINNS;                            /* �WINNS*/
    VOS_UINT32                          ulSncWINNS;                             /* ��WINNS */
}AT_DHCP_SETUP_PARAM_ST;


/* DHCP ��������Ϣ�ṹ*/
typedef struct
{
    AT_DHCP_CONFIG_STRU                 stDHCPConfig;                           /* DHCP����������*/
    VOS_UINT32                          ulDHCPServerOn;                         /* DHCP�Ƿ��Ѿ���*/
}AT_DHCP_ENTITY_ST;

/* PDP״̬�ϱ�����ʹ�õĽṹ��*/
typedef struct
{
    VOS_UINT32                          ulspeed;                                /* �����ٶȣ���λbps */
    AT_PDP_STATUS_ENUM_UINT32           enActiveSatus;                          /* ��������0Ϊ�ɹ�������Ϊʧ�� */
}AT_NDIS_PRO_STRU;

/*****************************************************************************
 �ṹ����   : AT_PDP_SAVE_STATE_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���沦��״̬
*****************************************************************************/
typedef struct
{

    AT_PDP_STATE_ENUM_U8                enIpv4State;
    AT_PDP_STATE_ENUM_U8                enIpv6State;
    AT_PDP_STATE_ENUM_U8                enIpv4v6State;

} AT_PDP_SAVE_STATE_INFO_STRU;





/*****************************************************************************
 �ṹ��    : AT_NDIS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :

  1.��    ��   : 2011��12��24��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��ɾ������AT_NDIS_DHCPINFO_RPT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucClientId;
    VOS_UINT8                           ucSysMode;
    VOS_UINT16                          usMsgSize;
    VOS_UINT32                          ulMsgId;
    union
    {
        AT_NDIS_PDNINFO_CFG_CNF_STRU    stNdisPdnInfoCfgCnf;
        AT_NDIS_PDNINFO_REL_CNF_STRU    stNdisPdnInfoRelCnf;
        AT_NDIS_USBABNORMAL_IND_STRU    stNdisUsbabnormalInd;
    }unMsg;
} AT_NDIS_MSG_STRU;

/*****************************************************************************
 �ṹ��    : AT_NDISCONN_PARA_STRU
 �ṹ˵��  : ����NDIS���ŵĲ�������NDISCONN ��ѯ����ʱʹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulConnectState;                                                 /* ���ű�־, 0 �Ͽ���1 ���� */
    VOS_UINT8   ucCID;                                                          /* AT �����������CID*/
    VOS_UINT8   aucAPN[TAF_MAX_APN_LEN+1];                                      /* AT�����������APN */
    VOS_UINT8   aucUsername[TAF_MAX_GW_AUTH_USERNAME_LEN+1];                    /* usernameָ��*/
    VOS_UINT8   aucPassword[TAF_MAX_GW_AUTH_PASSWORD_LEN+1];                    /* passwordָ��*/
    VOS_UINT8   ucReserved;
    VOS_UINT16  usAuthType;
} AT_NDISCONN_PARA_STRU;

/*****************************************************************************
 �ṹ��    : AT_CLINTID_RABID_MAP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :

  1.��    ��   : 2012��2��18��
    ��    ��   : L47619
    �޸�����   : AP-MODEM��Ŀ
  2.��    ��   : 2013��04��15��
    ��    ��   : f00179208
    �޸�����   : C�˵�����λ��Ŀ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsed;   /* ָ��FCID��Ӧ�Ľ���Ƿ���Ч��VOS_TRUE:��Ч��VOS_FALSE:��Ч */
    VOS_UINT32                          ulRabIdMask;
    MODEM_ID_ENUM_UINT16                enModemId;
    FC_PRI_ENUM_UINT8                   enFcPri;
    VOS_UINT8                           aucReserve[1];                          /* ���� */
} AT_FCID_MAP_STRU;

/*****************************************************************************
 �ṹ��     : AT_IPHDR_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : IPv4 packet header �ṹ
  1.��    ��   : 2012��6��12��
    ��    ��   : S62952
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
#if (VOS_LITTLE_ENDIAN == VOS_BYTE_ORDER)                   /* С���ֽ���*/
    VOS_UINT8                           ucIpHdrLen  :4;     /* IPͷ������ */
    VOS_UINT8                           ucIpVer     :4;     /* IP�汾��*/
#elif (VOS_BIG_ENDIAN == VOS_BYTE_ORDER)                    /* ����ֽ���*/
    VOS_UINT8                           ucIpVer     :4;     /* IP�汾��*/
    VOS_UINT8                           ucIpHdrLen  :4;     /* IPͷ������ */
#else
#error  "Please fix Macro VOS_BYTE_ORDER"                   /* VOS_BYTE_ORDERδ����*/
#endif
    VOS_UINT8                           ucServiceType;      /* IP TOS�ֶ�*/
    VOS_UINT16                          usTotalLen;         /* IP���ݰ��ܳ���*/
    VOS_UINT16                          usIdentification;   /* IP���ݰ�ID*/
    VOS_UINT16                          usOffset;           /* IP��Ƭƫ����*/
    VOS_UINT8                           ucTTL;              /* IPTTL*/
    VOS_UINT8                           ucProtocol;         /* IP�����غɲ���Э��*/
    VOS_UINT16                          usCheckSum;         /* IPͷ��У���*/
    VOS_UINT32                          ulSrcAddr;          /* ԴIP��ַ*/
    VOS_UINT32                          ulDstAddr;          /* Ŀ��IP��ַ*/
} AT_IPHDR_STRU;

/*****************************************************************************
 �ṹ��     : AT_UDP_HDR_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : UDP header �ṹ
  1.��    ��   : 2012��6��12��
    ��    ��   : S62952
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;          /* Դ�˿� */
    VOS_UINT16                          usDstPort;          /* Ŀ�Ķ˿� */
    VOS_UINT16                          usLen;              /* UDP������ */
    VOS_UINT16                          usChecksum;         /* UDPУ��� */
} AT_UDP_HDR_STRU;

/*****************************************************************************
 �ṹ��     : AT_UDP_PACKET_FORMAT_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : UDP packet �ṹ
  1.��    ��   : 2012��6��12��
    ��    ��   : S62952
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{

    AT_IPHDR_STRU                       stIpHdr;            /* IPͷ */
    AT_UDP_HDR_STRU                     stUdpHdr;           /* UDPͷ */
    VOS_UINT32                          ulBody;
} AT_UDP_PACKET_FORMAT_STRU;

/*****************************************************************************
 �ṹ��    : AT_PS_RMNET_ID_TAB
 �ṹ˵��  : PS�򲦺�������ModemId,cid,FcId��ӳ���
   1.��    ��   : 2012��12��18��
     ��    ��   : L60609
     �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucUsrCid;
}AT_PS_RMNET_ID_TAB;

/*****************************************************************************
 �ṹ����   : AT_PDP_ENTITY_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ����ʹ�õ�PDPʵ����Ϣ
*****************************************************************************/
typedef struct
{
    AT_PS_USER_INFO_STRU                stUsrInfo;
    VOS_UINT8                           ucIpv4Cid;
    VOS_UINT8                           ucIpv6Cid;
    VOS_UINT8                           ucIpv4v6Cid;
    AT_PDP_STATE_ENUM_U8                enIpv4State;
    AT_PDP_STATE_ENUM_U8                enIpv6State;
    AT_PDP_STATE_ENUM_U8                enIpv4v6State;
    VOS_UINT8                           aucRsv[2];

    AT_IPV4_DHCP_PARAM_STRU             stIpv4Dhcp;
    AT_IPV6_DHCP_PARAM_STRU             stIpv6Dhcp;

}AT_PDP_ENTITY_STRU;


/*****************************************************************************
 �ṹ��    : AT_CHDATA_RNIC_RMNET_ID_STRU
 �ṹ˵��  : AT^CHDATA��RNIC����ӳ���ϵ�Ľṹ

  1.��    ��   : 2013��4��26��
    ��    ��   : L60609
    �޸�����   : V9R1 IPv6&TAF/SM�ӿ��Ż���Ŀ����
*****************************************************************************/
typedef struct
{
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enChdataValue;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;

    VOS_UINT8                           aucReserved[3];
}AT_CHDATA_RNIC_RMNET_ID_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

/*��¼���翨�汾���ϵ絽���ųɹ�����ʱ�䣬��λ�� */
extern VOS_UINT32                       g_ulLcStartTime;

extern AT_PDP_ENTITY_STRU               g_stAtNdisDhcpPara;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtFirstNdisActPdpType;

extern AT_NDISCONN_PARA_STRU            g_stAtNdisConnPara;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtNdisActPdpType;

extern AT_DIAL_PARAM_STRU               gstAtNdisAddParam;

extern AT_HILINK_MODE_ENUM_U8           g_enHiLinkMode;

extern AT_PDP_ENTITY_STRU               g_stAtAppPdpEntity;

extern AT_DIAL_PARAM_STRU               g_stAtAppDialPara;

extern AT_PDP_STATE_ENUM_U8             g_enAtAppSaveState;

extern AT_PDP_SAVE_STATE_INFO_STRU      g_stAtAppSaveStateInfo;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtAppActPdpType;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtAppFirstActPdpType;

extern AT_IPV6_RA_INFO_STRU             g_stAtAppRaInfo;

extern AT_FCID_MAP_STRU                 g_stFcIdMaptoFcPri[];

extern AT_PS_RMNET_ID_TAB               g_astPsRmNetIdTab[];

extern AT_PS_REPORT_CONN_RESULT_STRU    g_astAtRptConnectedResultTab[];

extern AT_PS_REPORT_END_RESULT_STRU     g_astAtRptEndedResultTab[];

extern AT_PS_REG_FC_POINT_STRU          g_astAtRegFCPointTab[];


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : AT_GetDhcpPara
 ��������  : ��ȡDHCP����(DHCP����Ϊ������)
 �������  : pstConfig                  - DHCP����(������)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_GetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig,
    AT_IPV4_DHCP_PARAM_STRU            *pstIpv4Dhcp
);


/******************************************************************************
 �� �� ��  : AT_GetDisplayRate
 ��������  : ��ȡ�տ����۴�����NAS��ȡ���ҽ��ַ�����ʽתΪ����
 �������  : ulSpeed
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
******************************************************************************/
VOS_UINT32 AT_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT32                         *ulSpeed
);


/******************************************************************************
 �� �� ��  : AT_CtrlConnIndProc
 ��������  : ��Ҫ�������������ģ�����DHCP������
 �������  : pstEventָ��TAF_PS_CALL_EVENT_INFO_STRUȥ�����ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��23��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_VOID AT_CtrlConnIndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_USER_TYPE                        ucUserType
);

/******************************************************************************
 Function:      AT_CtrlGetPDPAuthType
 Description:    ��ȡPC���õ�PDP�������ж�Ӧ���͵�����
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP�������ڴ泤��
 Output:
 Return:        0   no auth
                1   pap
                2   chap
******************************************************************************/
PPP_AUTH_TYPE_ENUM_UINT8 AT_CtrlGetPDPAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
);
/*****************************************************************************
 �� �� ��  : AT_CtrlGetTapPdpAuthType
 ��������  : CLģʽ�»�ȡ�û��·���ppp��Ȩ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_PDP_AUTH_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_PDP_AUTH_TYPE_ENUM_UINT8 AT_ClGetPdpAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
);

/******************************************************************************
 Function:       AT_CtrlFreePCOContext
 Description:    �ͷ�PCO�е�ָ��
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP�������ڴ泤��
 Output:
 Return:        0   no auth
                1   pap
                2   chap
******************************************************************************/
VOS_VOID AT_CtrlFreePCOContext(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo
);


/******************************************************************************
 Function:       AT_CtrlMakePCOPapAuthInfo
 Description:    ��AT�����õ��û�����������PCO�ṹ
 Calls:
 Data Accessed:
 Data Updated:
 Input:         pstPppReqCfgInfo    ָ�����ø�PCO��Ϣ��ָ��
                pucUserName         �û���
                usUserNameLen       �û�������
                pucPassWord         ����
                usPassWordLen       ���볤��
 Output:
 Return:        VOS_OK
                VOS_ERR
 Others:        pap֡��ʽ
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- username length
                x byte    -- username
                1 byte    -- password length
                x byte    -- password
                ע��:�����������ڴ���TTF_NDIS_CtrlFreePCOContext���ͷ�
******************************************************************************/
VOS_UINT32 AT_CtrlMakePCOPapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo,
    VOS_UINT8                           *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                           *pucPassWord,
    VOS_UINT16                          usPassWordLen
);


/******************************************************************************
 Function:       AT_CtrlMakePCOChapAuthInfo
 Description:    ��AT�����õ��û�����������PCO�ṹ
 Calls:
 Data Accessed:
 Data Updated:
 Input:         pstPppReqCfgInfo    ָ�����ø�PCO��Ϣ��ָ��
                pucUserName         �û���
                usUserNameLen       �û�������
                pucPassWord         ����
                usPassWordLen       ���볤��
 Output:
 Return:
 Others:        chap challenge ֡��ʽ
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- challenge length   (16 bytes)
                x byte    -- challenge
                x byte    -- name               ("huawei.com" )
                chap response ֡��ʽ
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- response length    (16 bytes)
                x byte    -- response
                x byte    -- name               (from username)
******************************************************************************/
VOS_UINT32 AT_CtrlMakePCOChapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo,
    VOS_UINT8                           *pucUserName,
    VOS_UINT16                           usUserNameLen,
    VOS_UINT8                           *pucPassWord,
    VOS_UINT16                           usPassWordLen
);

/******************************************************************************
 ��������: AT_Ipv4AddrAtoi
 ��������: ��IPV4��ַ���ַ�����ʽת�������ָ�ʽ

 ����˵��:
   pcString [in] �ַ�����ʽ��IP��ַ,char * pcString="192.168.0.1"
   pucNumber [out] ���ָ�ʽ��IP��ַ,char pucNumber[4]={192,168,0,1};

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrAtoi(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/******************************************************************************
 ��������: AT_Ipv4AddrItoa
 ��������: ��IPV4��ַ�����ָ�ʽת�����ַ�����ʽ

 ����˵��:
   pcString [out] �ַ�����ʽ��IP��ַ,char * pcString="192.168.0.1"
   pucNumber [in] ���ָ�ʽ��IP��ַ,char pucNumber[4]={192,168,0,1};

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrItoa(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/*****************************************************************************
 �� �� ��  : AT_Ipv4Addr2Str
 ��������  : IPV4���͵ĵ�ַת��Ϊ�ַ�������
 �������  : pucNumber      - IPV4��ַ
 �������  : pcString       - �ַ���
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_Ipv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT32 AT_Ipv6AddrAtoi(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/*****************************************************************************
 �� �� ��  : AT_Ipv6LenStrToAddrProc
 ��������  : ���ַ�����ʽ��IP��ַת��ΪSMЭ��IP��ַ��ʽ(IPV6).
 �������  : pucStr - �ַ�����ʽ��IP��ַ
             pucColonCount - ð�Ÿ���
             pucDotCount   - ��Ÿ���
 �������  : pucIpAddr - SMЭ�鶨���IP��ַ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_Ipv6LenStrToAddrProc(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount
);


/******************************************************************************
 �� �� ��  : AT_Ipv6LenStrToAddrProcCompressed
 ��������  : ��IPV6ѹ���ַ�����ʽת��Ϊ��ѹ����ʽ.
 �������  : pucStr       - �ַ�����ʽ��IP��ַ
             ucColonCount - ð�Ÿ���
             ucDotCount   - ��Ÿ���
             ucStrlen     - �ַ�������
             ucIdxPos     - ����ð�Ų���λ��
 �������  : pucIpAddr - ��ѹ����ʽ��IP��ַ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
******************************************************************************/
VOS_VOID  AT_Ipv6LenStrToAddrProcCompressed(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount,
    VOS_UINT8                           ucStrlen,
    VOS_UINT8                           ucIdxPos
);


/*****************************************************************************
 �� �� ��  : AT_Ipv6LenStrToAddrAccess
 ��������  : ����IPV6��ַ�ַ�����ȡ��ð�š���Ÿ���
 �������  : pucStr        - �ַ�����ʽ��IP��ַ
 �������  : pucColonCount - ð�Ÿ���
             pucDotCount   - ��Ÿ���
             pucStrlen     - IPV6�ַ�������
             pucIdxPos     - ���鲹��ð������
 �� �� ֵ  : VOS_OK - ת���ɹ�
             VOS_ERR - ת��ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_Ipv6LenStrToAddrAccess(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucColonCount,
    VOS_UINT8                          *pucDotCount,
    VOS_UINT8                          *pucStrlen,
    VOS_UINT8                          *pucIdxPos
);


/******************************************************************************
 �� �� ��  : AT_Ipv6LenStrToAddr
 ��������  : ���ַ�����ʽ��IP��ַת��ΪSMЭ��IP��ַ��ʽ(IPV6).
 �������  : pucStr - �ַ�����ʽ��IP��ַ
 �������  : pucIpAddr - SMЭ�鶨���IP��ַ
 �� �� ֵ  : VOS_OK  - ת���ɹ�
             VOS_ERR - ת��ʧ��
 ���ú���  :
 ��������  :
******************************************************************************/
VOS_UINT32  AT_Ipv6LenStrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
);

/*****************************************************************************
 �� �� ��  : AT_Ipv6AddrToStr
 ��������  : ��IPV6��ַ��ʽת��Ϊ�ַ�����ʽ
 �������  : aucIpAddr[]    - IPV6��ַ(Э���ʽ)
             enIpStrType    - IPV6�ַ�����ʽ�������
 �������  : aucAddrStr[]   - IPV6��ַ(�ַ�����ʽ)
 �� �� ֵ  : VOS_OK         - ת���ɹ�
             VOS_ERR        - ת��ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_Ipv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    AT_IPV6_STR_TYPE_ENUM_UINT8         enIpStrType
);

/*****************************************************************************
 �� �� ��  : AT_Itoa
 ��������  : ����ת������(10��16), ������ת��ΪASCII��, �����������ַ���
 �������  : usValue    - ��ת��ΪASCII�������
             pcStr      - ���������ַ���
             usRadix    - ת������
 �������  : ��
 �� �� ֵ  : VOS_CHAR*
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_CHAR* AT_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
);

/******************************************************************************
 �� �� ��  : AT_AtoI
 ��������  : �ַ���ת����
 �������  : pString �ַ���
 �������  : ��
 �� �� ֵ  : ���� IP��ַ
 ���ú���  :
 ��������  :
******************************************************************************/
VOS_UINT32  AT_AtoI(
    VOS_UINT8                         *pString
);

/*****************************************************************************
 �� �� ��  : AT_FindIpv6AddrZeroFieldsToBeCompressed
 ��������  : �ҳ���Ҫʹ��"::"��ʾ��IP��ַ�ε���ʼλ��
 �������  : ausAddrValue[]     - IPV6��ַ������
             ucTokensNum        - ��ַ�θ���
 �������  : pucZeroFieldStart  - ��ֵ����Ϊ0��IP��ַ����ʼλ��
             pucZeroFieldCount  - ��ֵ����Ϊ0��IP��ַ�θ���
 �� �� ֵ  : VOS_OK             - �ɹ�
             VOS_ERR            - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                          ausAddrValue[],
    VOS_UINT8                           ucTokensNum
);


/*****************************************************************************
 �� �� ��  : AT_ConvertIpv6AddrToCompressedStr
 ��������  : ��IPV6��ַ��ʽת��Ϊ�ַ���ѹ����ʽ
 �������  : aucIpAddr[]    - IPV6��ַ(Э���ʽ)
             ucTokensNum    - ��ַ�θ���
 �������  : aucAddrStr[]   - IPV6��ַ(�ַ�����ʽ)
 �� �� ֵ  : VOS_OK         - ת���ɹ�
             VOS_ERR        - ת��ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    VOS_UINT8                           ucTokensNum
);

VOS_UINT32 AT_GetLanAddr32(
  VOS_UINT8                            *pucAddr
);
TAF_UINT32 AT_DHCPGetIPMask(
    TAF_UINT32                          ulIpAddrHL
);
VOS_UINT32 AT_DHCPGetGateWay(
    VOS_UINT32                          ulIpAddrHL,
    VOS_UINT32                          ulMaskHL
);

/*****************************************************************************
 �� �� ��  : AT_CalcIpHdrCRC16
 ��������  : ����IPͷCRCУ���
 �������  : pucData    - IPͷ��Ϣ
             usSize     - IPͷ����
 �������  : ��
 �� �� ֵ  : ulCheckSum - CRCУ���
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT16 AT_CalcIpHdrCRC16(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usSize
);


/*****************************************************************************
 �� �� ��  : AT_BuildUdpHdr
 ��������  : ����IP��UDPͷ����Ϣ(���ڹ������ʹ�õ�UDP��)
 �������  : pstUdpPkt  - UDP����Ϣ
             usLen      - UDP������
             ulSrcAddr  - ԴIP��ַ
             ulDstAddr  - Ŀ��IP��ַ
             usSrcPort  - Դ�˿ں�
             usDstPort  - Ŀ��˿ں�
 �������  : ��
 �� �� ֵ  : VOS_OK     - ����ɹ�
             VOS_ERR    - ����ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_BuildUdpHdr(
    AT_UDP_PACKET_FORMAT_STRU          *pstUdpPkt,
    VOS_UINT16                          usLen,
    VOS_UINT32                          ulSrcAddr,
    VOS_UINT32                          ulDstAddr,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort
);


/*****************************************************************************
 �� �� ��  : AT_NidsGet3gppSmCauseByPsCause
 ��������  : ��PS����д�����ת����3GPPЭ�鶨���(E)SM Cause, ��3GPPЭ�鶨��
             �Ĵ�����ͳһת����0(Unknown error/Unspecified error)
 �������  : enCause - PS����д�����
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_Get3gppSmCauseByPsCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


/*****************************************************************************
 �� �� ��  : AT_SaveNdisConnDailPara
 ��������  : ����NDISCONN����ʱ�Ĳ�������NDISCONN��ѯ����ʹ��
 �������  : AT_PARSE_PARA_TYPE_STRU            *pstParaList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_SaveNdisConnDailPara(
    AT_PARSE_PARA_TYPE_STRU            *pstParaList
);


/*****************************************************************************
 �� �� ��  : AT_SendNdisRelReq
 ��������  : ����PDN�����ͷ���Ϣ
 �������  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_SendNdisRelReq(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_RcvNdisPdnInfoCfgCnf
 ��������  : NDIS���õĽ������
 �������  : AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoCfgCnf(
    AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
);

/*****************************************************************************
 �� �� ��  : AT_RcvNdisPdnInfoRelCnf
 ��������  : NDIS�ͷ�Ӧ����
 �������  : AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoRelCnf(
    AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
);



#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_NdisIpv6DhcpRest
 ��������  : ���IPV6��ַ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NdisIpv6DhcpRest(VOS_VOID);


/*****************************************************************************
 �� �� ��  : AT_NdisCtrlConnIpv6IndProc
 ��������  : ����IPV6��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID  AT_NdisCtrlConnIpv6IndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_NdisCheckIpv6PdpState
 ��������  : ����Ƿ�������IPv6״̬��PDP����
 �������  : enPdpState - PDP״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE   - PDP���Ӵ���
             VOS_FALSE  - PDP���Ӳ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);
#endif


/*****************************************************************************
 �� �� ��  : AT_NdisStateChangeProc
 ��������  : NDIS����ʱ֪ͨPC����״̬�ı�
 �������  : ucPdpType --- PDP����
             ulStat    --- NDIS����״̬:0-���ӶϿ�; 1-������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NdisStateChangeProc(
    VOS_UINT8                           ucPdpType,
    VOS_UINT32                          ulStat,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


/******************************************************************************
 �� �� ��  : AT_NdisGetState
 ��������  : ��ȡNDIS״̬������̬/�Ǽ���̬
 �������  : ucIndex --- �û�����
 �������  : ��
 �� �� ֵ  : AT_PDP_STATE_ENUM_U8 ��ǰ״̬ ����̬/�Ǽ���̬

 ���ú���  :
 ��������  :
******************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_NdisGetState(
    VOS_UINT8                           ucCid
);


/*****************************************************************************
 �� �� ��  : AT_NdisCheckPdpIdleState
 ��������  : �����Ƿ���idel��deacting��PDP
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpIdleState(VOS_VOID);

/*****************************************************************************
 �� �� ��  : AT_NdisAddrProc
 ��������  : ����NDIS��ַ����
 �������  : pstConfig --- ָ��DHCP������ָ��
             pstEvent  --- �ϱ��¼�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NdisAddrProc(
    AT_DHCP_CONFIG_STRU                 *pstConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NdisCheckIpv6PdpState
 ��������  : ����Ƿ�������IPv4״̬��PDP����
 �������  : enPdpState - PDP״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE   - PDP���Ӵ���
             VOS_FALSE  - PDP���Ӳ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);


/*****************************************************************************
 �� �� ��  : AT_NdisGetDhcpPara
 ��������  : ��ȡDHCP����
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NdisGetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig
);


/*****************************************************************************
 �� �� ��  : AT_NdisSetState
 ��������  : ����NDIS״̬
 �������  : ucPdpType --- PDP����
             enState   --- PDP״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NdisSetState(
    VOS_UINT8                              ucPdpType,
    AT_PDP_STATE_ENUM_U8                   enState
);

/*****************************************************************************
 �� �� ��  : AT_NdisPsRspPdpActEvtRejProc
 ��������  : pdp����ʧ�ܣ�NDIS����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NdisPsRspPdpActEvtCnfProc
 ��������  : pdp����ɹ���Ndis����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NdisPsRspPdpDeactEvtCnfProc
 ��������  : pdpȥ����ɹ���Ndis����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NdisPsRspPdpDeactivatedEvtProc
 ��������  : pdpȥ����ɹ���Ndis����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NDIS_ParseUsrInfo
 ��������  : ��ȡNDIS�û���Ϣ
 �������  : ucIndex     - �˿ں�(ClientId)����
 �������  : pstUserInfo - �û���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_NDIS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
);

VOS_VOID AT_NDIS_ConnStatusChgProc(NCM_IOCTL_CONNECT_STUS_E enStatus);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_CalcIpv6LanAddrFromIpv6Prefix
 ��������  : ����IPV6��ַǰ׺����IPV6ȫ�ֵ�ַ
 �������  : pucPrefix
             ulPrefixByteLen
             pucIpv6LanAddr
             ulIpv6LanAddrLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr,
    VOS_UINT32                          ulIpv6LanAddrLen
);


/*****************************************************************************
 �� �� ��  : AT_AppRcvIpv6LanAddr
 ��������  : NAS��HOSTע��Ļص���������HOST��ȡIPv6ȫ�ֵ�ַ����NAS�ϱ�-
             IPv6ȫ�ֵ�ַ���Լ�ȫ�ֵ�ַ���ȡ�
 �������  : aucLanAddr       - Ipv6ȫ�ֵ�ַ
             ulLanAddrByteLen - ��ַ����, ��λ��BYTE
             ulPrefixBitLen   - ǰ׺����, ��λ��BIT
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LanAddr(
    VOS_UINT8                           aucLanAddr[],
    VOS_UINT32                          ulLanAddrByteLen,
    VOS_UINT32                          ulPrefixBitLen
);


/*****************************************************************************
 �� �� ��  : AT_AppRcvIpV6Prefix
 ��������  : NAS��HOSTע��Ļص���������HOST�յ�GGSN�·���RA֮����NAS�ϱ�-
             IPv6��ַǰ׺���Լ���ַǰ׺���ȡ�
 �������  : VOS_UINT8  aucPrefix   Ipv6ǰ׺
             VOS_UINT32 ulPrefixLen ǰ׺���ȣ���λ��BIT
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6Prefix(
    VOS_UINT8                           aucPrefix[],
    VOS_UINT32                          ulPrefixBitLen
);


/*****************************************************************************
 �� �� ��  : AT_AppRcvPrefixIpV6PreferredLifetime
 ��������  : �����ϱ�PreferredLifetime
 �������  : ulPrefixPreferredLifetime - ǰ׺����ʹ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6PreferredLifetime(
    VOS_UINT32                          ulPrefixPreferredLifetime
);


/*****************************************************************************
 �� �� ��  : AT_RcvPrefixIpV6ValidLifetime
 ��������  : �����ϱ�ValidLifetime
 �������  : ulValidLifetime - ǰ׺��Ч������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6ValidLifetime(
    VOS_UINT32                          ulValidLifetime
);


/*****************************************************************************
 �� �� ��  : AT_RcvIpV6LinkMtu
 ��������  : ���յ�HOSTģ���MTU���ݵĴ�����: ����MTU���ݵ����أ�ͬʱ�����ϱ���APP
             ���յ�RA���ݺ�HOSTģ����ñ�����֪ͨNAS�µ�MTU����
 �������  : ulMTU - MTU Size
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LinkMtu(
    VOS_UINT32                          ulMtu
);


/*****************************************************************************
 �� �� ��  : AT_RcvEnableIpV6Prefix
 ��������  : ֪ͨӦ�������µ�IPV6ǰ׺
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppRcvEnableIpv6Prefix(VOS_VOID);


/*****************************************************************************
 �� �� ��  : AT_AppProcIpv6RaInfo
 ��������  : �յ�Router Advertisement IP����, ���д���ͷַ�
 �������  : pstRaInfoNotifyInd         - RA������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd);


/*****************************************************************************
 �� �� ��  : AT_AppCtrlConnIpv6IndProc
 ��������  : ����IPv6��ַ
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppCtrlConnIpv6IndProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppDhcpv6Reset
 ��������  : ���IPv6��ַ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppDhcpv6Reset(VOS_VOID);
#endif


/*****************************************************************************
 �� �� ��  : AT_AppDhcpReset
 ��������  : ���APP��DHCP����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppDhcpReset(VOS_VOID);

/*****************************************************************************
 �� �� ��  : AT_AppPdpAddrProc
 ��������  : ����IPv4��ַ����
 �������  : pstAppPdpEntity - PDPʵ��
             pstDhcpConfig   - DCHP��Ϣ
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppPdpAddrProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_AppCheckPdpIdleState
 ��������  : ����Ƿ��д���IDLE��DEACTIVATING״̬��PDP
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��������������PDP
             VOS_FALSE - ����������������PDP
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppCheckPdpIdleState(VOS_VOID);

/*****************************************************************************
 �� �� ��  : AT_AppCheckIpv4PdpState
 ��������  : ����Ƿ�������IPv4״̬��PDP����
 �������  : enPdpState - PDP״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE   - PDP���Ӵ���
             VOS_FALSE  - PDP���Ӳ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_AppCheckIpv6PdpState
 ��������  : ����Ƿ�������IPv6״̬��PDP����
 �������  : enPdpState - PDP״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE   - PDP���Ӵ���
             VOS_FALSE  - PDP���Ӳ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);
#endif


/*****************************************************************************
 �� �� ��  : AT_AppGetPdpState
 ��������  : ��ȡAPP��PDP״̬������̬/�Ǽ���̬
 �������  : ucPdpType - PDP����
 �������  : ��
 �� �� ֵ  : AT_PDP_STATE_ENUM_U8
 ���ú���  :
 ��������  :
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpState(
    VOS_UINT8                           ucPdpType
);


/*****************************************************************************
 �� �� ��  : AT_AppSetPdpState
 ��������  : ����APP��PDP״̬
 �������  : ucPdpType  - PDP����
             enPdpState - PDP״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppSetPdpState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
);


/*****************************************************************************
 �� �� ��  : AT_AppSndCallConnectedResult
 ��������  : �ϱ����ӽ��^DCONN, ֪ͨAPP���ųɹ�
 �������  : ucCid                      - CID
             enPdpType                  - ��������(IPv4/IPv6)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppSndCallConnectedResult(
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


/*****************************************************************************
 �� �� ��  : AT_AppSndCallEndedResult
 ��������  : �ϱ����ӽ��^DCONN, ֪ͨAPP���ųɹ�
 �������  : ucCid     - CID
             enCause   - ������
             enPdpType - ��������(IPv4/IPv6)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppSndCallEndedResult(
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


/*****************************************************************************
 �� �� ��  : AT_AppPdpActOrig
 ��������  : ����PDP����
 �������  : usClientId - �ͻ���ID
             ucCid      - CID
             ucPdpType  - PDP����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_AppActCnfBackProc
 ��������  : PDP����ɹ���Ļ��˴���
 �������  : pstEvent   - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
#endif


/*****************************************************************************
 �� �� ��  : AT_AppIpv4ActCnfProc
 ��������  : ����IPV4��PDP����ɹ����¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_AppIpv6ActCnfProc
 ��������  : ����IPV6��PDP����ɹ����¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppIpv4v6ActCnfProc
 ��������  : ����IPv4v6��PDP����ɹ����¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
#endif

/*****************************************************************************
 �� �� ��  : AT_AppIpv4DeactCnfProc
 ��������  : ����IPv4��PDPȥ�����¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_AppIpv6DeactCnfProc
 ��������  : ����IPv4��PDPȥ�����¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppIpv4v6DeactCnfProc
 ��������  : ����IPv4v6��PDPȥ�����¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);
#endif


/*****************************************************************************
 �� �� ��  : AT_AppIpv4v6PdpActRejProc
 ��������  : ����IPv4��PDP������¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_AppIpv6PdpActRejProc
 ��������  : ����IPv6��PDP������¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppIpv4v6PdpActRejProc
 ��������  : ����IPv4��PDP������¼�
 �������  : pstAppPdpEntity - PDPʵ��
             pstEvent        - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);
#endif


/*****************************************************************************
 �� �� ��  : AT_AppPsRspPdpActEvtCnfProc
 ��������  : PDP����ɹ���APP����
 �������  : ucIndex  - �ͻ���ʶ��
             pstEvent - �ϱ��¼�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppPsRspPdpActEvtRejProc
 ��������  : PDP����ʧ�ܣ�APP����
 �������  : ucIndex  - �ͻ���ʶ��
             pstEvent - �ϱ��¼�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppPsRspPdpDeactEvtCnfProc
 ��������  : PDPȥ����ɹ���APP����
 �������  : ucIndex  - �ͻ���ʶ��
             pstEvent - �ϱ��¼�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppPsRspPdpDeactivatedEvtProc
 ��������  : ����ȥ����PDP, APP����
 �������  : ucIndex  - �ͻ���ʶ��
             pstEvent - �ϱ��¼�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppSetFlowCtrl
 ��������  : ����·���豸����
 �������  : ulParam1   - Ŀǰ��ʹ��
             ulParam2   - Ŀǰ��ʹ��
 �������  : ��
 �� �� ֵ  : VOS_OK     - �������سɹ�
             VOS_ERR    - ��������ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppSetFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);


/*****************************************************************************
 �� �� ��  : AT_AppClearFlowCtrl
 ��������  : ֹͣ·���豸����
 �������  : ulParam1   - Ŀǰ��ʹ��
             ulParam2   - Ŀǰ��ʹ��
 �������  : ��
 �� �� ֵ  : VOS_OK     - ֹͣ���سɹ�
             VOS_ERR    - ֹͣ����ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppClearFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);


/*****************************************************************************
 �� �� ��  : AT_AppRegFCPoint
 ��������  : ע��·�ɶ˿����ص�
 �������  : FC_ID_ENUM_UINT8                    enFcId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppRegFCPoint(
    FC_ID_ENUM_UINT8                    enFcId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    VOS_UINT8                           ucRmNetId
);


/*****************************************************************************
 �� �� ��  : AT_AppDeRegFCPoint
 ��������  : ȥע��·���豸���ص�
 �������  : FC_ID_ENUM_UINT8                      enFcId,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_OK     - ȥע�����ص�ɹ�
             VOS_ERR    - ȥע�����ص�ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_AppDeRegFCPoint(
    FC_ID_ENUM_UINT8                     enFcId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_APP_ParseUsrInfo
 ��������  : ��ȡAPP�û���Ϣ
 �������  : ucIndex     - �˿ں�(ClientId)����
 �������  : pstUserInfo - �û���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_APP_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
);

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/*****************************************************************************
 �� �� ��  : AT_ModemPsRspPdpActEvtRejProc
 ��������  : pdp����ʧ�ܣ�AP MODEM����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��5��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pEvent
);


/*****************************************************************************
 �� �� ��  : AT_ModemPsRspPdpActEvtCnfProc
 ��������  : pdp����ʧ�ܣ�Modem����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��5��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pEvent
);

/*****************************************************************************
 �� �� ��  : AT_ModemPsRspPdpDeactEvtCnfProc
 ��������  : pdpȥ����ɹ���Modem����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��5��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pEvent
);

/*****************************************************************************
 �� �� ��  : AT_MODEM_ProcCallEndedEvent
 ��������  : ����PS_CALL_END_CNF�¼�
 �������  : ucIndex  - �˿�����
             pstEvent - ID_EVT_TAF_PS_CALL_END_CNF�¼�ָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MODEM_ProcCallEndCnfEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_END_CNF_STRU           *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_MODEM_HangupCall
 ��������  : �Ҷ�PPP��������
 �������  : ucIndex - �˿�����
 �������  : ��
 �� �� ֵ  : AT_XXX  - ATC������
*****************************************************************************/
VOS_UINT32 AT_MODEM_HangupCall(VOS_UINT8 ucIndex);


VOS_VOID  AT_AnswerPdpActInd(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_ModemPsRspPdpDeactivatedEvtProc
 ��������  : pdpȥ����ɹ���Modem����
 �������  : ucIndex --- ��֪�Ŀͻ���ʶ��
             pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��5��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pEvent
);





/*****************************************************************************
 �� �� ��  : AT_GetLCStartTime
 ��������  : ��ȡ���ϵ絽���ųɹ�ʱ�䣬��λ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :  ����ʱ�䣬��λ��
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_GetLCStartTime(VOS_VOID);

/*****************************************************************************
�� �� ��  : AT_SendRnicPdpDeactInd
��������  : APP�˿ڲ���ʱ֪ͨ��������
�������  : VOS_UINT8 ucRabId
�������  : ��
�� �� ֵ  : �ɹ�
            ʧ��
���ú���  :
��������  :
*****************************************************************************/
extern VOS_UINT32 AT_SendRnicPdpDeactInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
 �� �� ��  : AT_DeRegModemPsDataFCPoint
 ��������  : ȥע��Modem�˿����ص㡣
 �������  : MN_CLIENT_ID_T                      usClientID,
             VOS_UINT8                           ucRabId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_DeRegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
 �� �� ��  : AT_RegModemPsDataFCPoint
 ��������  : ע��Modem�˿����ص㡣
 �������  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent
             FC_ID_ENUM_UINT8                      enFcId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_RegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
);

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
 �� �� ��  : AT_RegModemVideoPhoneFCPoint
 ��������  : ע��Modem�˿�CST���ص㡣
 �������  : FC_ID_ENUM_UINT8                    enFcId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RegModemVideoPhoneFCPoint(
    VOS_UINT8                           ucIndex,
    FC_ID_ENUM_UINT8                    enFcId
);

/*****************************************************************************
 �� �� ��  : AT_DeRegModemVideoPhoneFCPoint
 ��������  : ȥע��Modem�˿�CST���ص㡣
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_DeRegModemVideoPhoneFCPoint(VOS_UINT8 ucIndex);
#endif


/*****************************************************************************
 �� �� ��  : AT_ProcNdisRegFCPoint
 ��������  : NDIS�û�����PDP״̬�ı�Ϊ����ʱ�Ĵ���
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ����

*****************************************************************************/
VOS_VOID  AT_ProcNdisRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 �� �� ��  : AT_ProcNdisDeRegFCPoint
 ��������  : NDIS�û�����PDP״̬�ı�Ϊȥ����ʱ�Ĵ���
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ����

*****************************************************************************/
VOS_VOID  AT_ProcNdisDeRegFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 �� �� ��  : AT_RegNdisFCPoint
 ��������  : ע��NDIS�˿����ص㡣
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_RegNdisFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
);

/*****************************************************************************
 �� �� ��  : AT_DeRegNdisFCPoint
 ��������  : ȥע��NDIS�˿����ص㡣
 �������  : VOS_UINT8                           ucRabId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_DeRegNdisFCPoint(
    VOS_UINT8                           ucRabId,
    MODEM_ID_ENUM_UINT16                enModemId
);

/*****************************************************************************
 �� �� ��  : AT_NdisPdpActOrig
 ��������  : ����PDP����
 �������  :  VOS_UINT16                  usClientId
              VOS_UINT8                   ucCid
              TAF_PDP_TYPE_ENUM_UINT8     ucPdpType
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID AT_NdisPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_NdisActCnfBackProc
 ��������  : PDP����ɹ���Ļ��˴���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID  AT_NdisActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_SendNdisIPv6PdnInfoCfgReq
 ��������  : ����IPV6��PDN��Ϣ
 �������  : TAF_PS_IPV6_INFO_IND_STRU* pRaInfo
 �������  : ��
 �� �� ֵ  : AT_APS_IPV6_RA_INFO_STRU* pIPv6RaInfo
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_SendNdisIPv6PdnInfoCfgReq(
           MODEM_ID_ENUM_UINT16                 enModemId,
           TAF_PS_IPV6_INFO_IND_STRU* pIPv6RaNotify);

/*****************************************************************************
 �� �� ��  : AT_NdisIpv4ActCnfProc
 ��������  : ����IPV4��PDP����ɹ����¼�
 �������  : pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv4ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_NdisIpv6ActCnfProc
 ��������  : ����IPV6��PDP����ɹ����¼�
 �������  : pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_NdisIpv4v6ActCnfProc
 ��������  : ����IPV4v6��PDP����ɹ����¼�
 �������  : pstEvent --- �¼�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv4v6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
#endif


/*****************************************************************************
 �� �� ��  : AT_GetFCPriFromQos
 ��������  : Qosת��ΪFC���ȼ�
 �������  : TAF_UMTS_QOS_STRU                  *pstUmtsQos
 �������  : ��
 �� �� ֵ  : FC_PRI_ENUM_UINT8
 ���ú���  :
 ��������  :
*****************************************************************************/
extern FC_PRI_ENUM_UINT8 AT_GetFCPriFromQos(
    TAF_UMTS_QOS_STRU                  *pstUmtsQos
);

/*****************************************************************************
 �� �� ��  : AT_GetPsDialParamFromAtDialParam
 ��������  : ��ȡ���Ų���
 �������  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID AT_GetPsDialParamFromAtDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstPsDialParam,
    AT_DIAL_PARAM_STRU                 *pstDialParam
);

/*****************************************************************************
 �� �� ��  : AT_GetPdpContextFromAtDialParam
 ��������  : ��ȡpdp������
 �������  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :s
*****************************************************************************/
extern VOS_VOID AT_GetPdpContextFromAtDialParam(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
    AT_DIAL_PARAM_STRU                 *pstDialParam
);

/*****************************************************************************
 �� �� ��  : AT_GetFcPriFromMap
 ��������  : ��ȡָ��FC ID��FC PRI
 �������  : FC_ID_ENUM_UINT8                   enFcId,
             AT_FCID_MAP_STRU                  *pstFcIdMap
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_GetFcPriFromMap(
    FC_ID_ENUM_UINT8                   enFcId,
    AT_FCID_MAP_STRU                  *pstFcIdMap
);


/*****************************************************************************
 �� �� ��  : AT_NotifyFcWhenPdpModify
 ��������  : ������PDP MODIFY(UE��������෢��)ʱ����FCָʾ�޸����ص�
 �������  : pstEvt       TAF_PS_CALL_EVENT_INFO_STRU�¼�
             enFcId        ����ʵ��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��18��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_NotifyFcWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
);

/* Deleted by m00217266 for L-C��������Ŀ, 2014-1-26, begin */
#if 0
/*****************************************************************************
 �� �� ��  : AT_NotifyAdsWhenPdpModify
 ��������  : ������PDP MODIFY(UE��������෢��)ʱ����ADSָʾ������PDP�޸�
 �������  : pstEvt       TAF_PS_CALL_EVENT_STRU�¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��18��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU   *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NotifyAdsWhenPdpAvtivated
 ��������  : ֪ͨADS���ؼ���
 �������  : pstEvent - ���ؼ����¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_NotifyAdsWhenPdpDeactivated
 ��������  : ֪ͨADSȥ���ؼ���
 �������  : pstEvent - ����ȥ�����¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_SendAdsPdpStatusInd
 ��������  : AT��ADS������Ϣ
 �������  : VOS_UINT32                          ulPid,
             ADS_PDP_STATUS_IND_STRU            *pstAdsInd
 �������  : ��
 �� �� ֵ  : �ɹ�
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
);
#endif
/* Deleted by m00217266 for L-C��������Ŀ, 2014-1-26, end */

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_SaveIPv6Dns
 ��������  : ����IPV6��DNS��PDPʵ����
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_VOID  AT_SaveIPv6Dns(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
);

/*****************************************************************************
 �� �� ��  : AT_SaveIPv6Pcscf
 ��������  : ����IPV6��Pcscf��PDPʵ����
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Pcscf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
);
#endif


/*****************************************************************************
 �� �� ��  : AT_UsbEthHostAccumTuneCB
 ��������  : ��FC(����)ģ��ע��Ķ�̬����HOST��NCM/ECM��������Ļص�����
 �������  : pstFcDrvAssemPara - NCM/ECM�������, �������²���:
                                 1. HOST OUT���ʱ��
 �������  : ��
 �� �� ֵ  : VOS_OK            - �����ɹ�
             VOS_ERR           - ����ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_UsbEthHostAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
);


/*****************************************************************************
 �� �� ��  : AT_UsbEthDeviceAccumTuneCB
 ��������  : ��FC(����)ģ��ע��Ķ�̬����DEVICE��NCM/ECM��������Ļص�����
 �������  : pstFcDrvAssemPara - NCM/ECM�������, �������²���:
                                 1. TX�������
                                 2. TX���ʱ��
                                 3. RX�������
                                 4. RX���ʱ��
 �������  : ��
 �� �� ֵ  : VOS_OK            - �����ɹ�
             VOS_ERR           - ����ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_UsbEthDeviceAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
);


/*****************************************************************************
 �� �� ��  : AT_ChangeFCPoint
 ��������  : �������ص����ȼ���
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
             FC_PRI_ENUM_UINT8                    enFCPri,
             FC_ID_ENUM_UINT8                     enFcId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 AT_ChangeFCPoint(
    TAF_CTRL_STRU                       *pstCtrl,
    FC_PRI_ENUM_UINT8                    enFCPri,
    FC_ID_ENUM_UINT8                     enFcId
);

extern VOS_UINT32 AT_EnableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
);
extern VOS_UINT32 AT_DisableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
);
extern VOS_UINT32 AT_RegHsicFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_UINT32 AT_DeRegHsicFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpDeactCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);
/* Modified by l60609 for AP������Ŀ ��2012-09-10 Begin */
extern VOS_VOID  AT_ProcAppPsRspEvtPdpActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
extern VOS_VOID  AT_ProcAppPsRspEvtPdpDeActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);
/* Modified by l60609 for AP������Ŀ ��2012-09-10 End */
extern VOS_VOID AT_ProcAppPsRspEvtPdpDeactivated(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);
extern VOS_VOID AT_NotifyFcWhenAppPdpModify(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
#if (FEATURE_ON == FEATURE_LTE)
/* ATģ���FTM ģ�鷢����Ϣ */
extern VOS_UINT32 atSendFtmDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_UINT32 ulClientId, VOS_VOID* pData, VOS_UINT32 uLen);
#endif
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/

extern VOS_UINT32 AT_SendRnicCgactIpv4ActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
 �� �� ��  : AT_PS_AddIpAddrRabIdMap
 ��������  : ��ӳ���IP��RABID��ӳ��
 �������  : usClientId - �ͻ���ID
             pstEvent   - PS������¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_AddIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_PS_DeleteIpAddrRabIdMap
 ��������  : ɾ������IP��RABID��ӳ��
 �������  : usClientId - �ͻ���ID
             pstEvent   - PS������¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_DeleteIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_PS_GetIpAddrByRabId
 ��������  : ����RABID��ȡ����IP��ַ
 �������  : usClientId - �ͻ���ID
             ucRabId    - RABID [5,15]
 �������  : ��
 �� �� ֵ  : ulIpAddr   - IP��ַ(������)
*****************************************************************************/
VOS_UINT32 AT_PS_GetIpAddrByRabId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucRabId
);


extern VOS_UINT32 AT_PS_GetRmNetIdByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucRmNetId
);
extern VOS_VOID AT_PS_SetPsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
);
extern TAF_PS_CAUSE_ENUM_UINT32 AT_PS_GetPsCallErrCause(
    VOS_UINT16                          usClientId
);

extern VOS_UINT32 AT_ResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);
VOS_UINT32 AT_PS_GetRnicRmNetIdFromChDataValue(
    VOS_UINT8                           ucIndex,
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId,
    RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
);

VOS_UINT32 AT_PS_GetChDataValueFromRnicRmNetId(
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId,
    AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
);

AT_PS_CALL_ENTITY_STRU* AT_PS_GetCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT8 AT_PS_TransCidToCallId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 AT_PS_IsCallIdValid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_VOID AT_PS_ReportDCONN(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID AT_PS_ReportDEND(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID AT_PS_RegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_DeRegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_RegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_DeRegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID  AT_PS_SndDipcPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID  AT_PS_SndDipcPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID  AT_PS_SndRnicPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID AT_PS_SndRnicPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT32 AT_PS_IsIpv6CapabilityValid(VOS_UINT8 ucCapability);

VOS_UINT32 AT_CheckIpv6Capability(
    VOS_UINT8                           ucPdpType
);

VOS_UINT32 AT_PS_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
);


VOS_VOID  AT_PS_SaveIPv6Dns(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID  AT_PS_SaveIPv6Pcscf(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcConnectedIpv6Addr(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd);


VOS_UINT32 AT_PS_MatchIpv4v6ConnFailFallbackCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


VOS_UINT32 AT_PS_SetupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


VOS_UINT32 AT_PS_HangupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


VOS_VOID AT_PS_ProcDualStackCallConn(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);


VOS_VOID AT_PS_ProcIpv6ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_UINT32 AT_PS_ProcIpv4ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


VOS_UINT32 AT_PS_ProcIpv4v6ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);
#endif

VOS_VOID AT_PS_ProcIpv4CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID AT_PS_ProcIpv6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_VOID AT_PS_ProcIpv4v6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_VOID AT_PS_ProcIpv6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4v6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_ProcIpv4v6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_UINT8 AT_CalcIpv6PrefixLength(
    VOS_UINT8                           *pucLocalIpv6Mask
);

VOS_VOID AT_GetIpv6MaskByPrefixLength(
    VOS_UINT8                            ucLocalIpv6Prefix,
    VOS_UINT8                           *pucLocalIpv6Mask
);

#endif

VOS_VOID AT_PS_ProcCallConnectedEvent(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcCallRejectEvent(
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   *pstEvent
);

VOS_VOID AT_PS_ProcCallEndedEvent(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_ProcCallOrigCnfEvent(TAF_PS_CALL_ORIG_CNF_STRU *pstCallOrigCnf);

VOS_VOID AT_PS_ProcCallEndCnfEvent(TAF_PS_CALL_END_CNF_STRU *pstCallEndCnf);

VOS_UINT32 AT_PS_ProcCallModifyEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

VOS_UINT32 AT_PS_AllocCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *pucCallId
);

VOS_VOID AT_PS_FreeCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_ValidateDialParam(VOS_UINT8 ucIndex);

VOS_VOID AT_PS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUserInfo
);

TAF_PDP_TYPE_ENUM_UINT8 AT_PS_GetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_SetupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    AT_DIAL_PARAM_STRU                 *pstCallDialParam
);

VOS_UINT32 AT_PS_HangupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_ProcDialUp(VOS_UINT8 ucIndex);

VOS_UINT32 AT_PS_ProcDialDown(VOS_UINT8 ucIndex);

VOS_UINT32 AT_PS_ProcDialCmd(VOS_UINT8 ucIndex);


extern VOS_UINT32 AT_CheckApnFormat(
    VOS_UINT8                          *pucApn,
    VOS_UINT16                          usApnLen
);


VOS_VOID AT_PS_AssignCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucCallId
);

VOS_VOID AT_PS_FreeCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);


/*****************************************************************************
 �� �� ��  : AT_PS_ProcDeactSharePdpState
 ��������  : PDP״̬�仯ʱ��Share PDP������صĴ���
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID  AT_PS_ProcDeactSharePdpState(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 �� �� ��  : AT_PS_ProcActSharePdpState
 ��������  : PDP״̬�仯ʱ��Share PDP������صĴ���
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID  AT_PS_ProcActSharePdpState(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_PS_ProcSharePdpIpv6RaInfo
 ��������  : Share-PDP���Կ�������£��յ�Router Advertisement IP����, �洢��ӦPDN��Ϣ
 �������  : pstRaInfoNotifyInd         - RA������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��6��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ����

*****************************************************************************/
VOS_VOID AT_PS_ProcSharePdpIpv6RaInfo(
    TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd
);
#endif

/******************************************************************************
 �� �� ��  : AT_PS_SaveRnicPdpDhcpPara
 ��������  : �յ�NDIS PDP����ɹ���Ϣ�󣬱���DHCP��Ϣ��APP PDPʵ����
 �������  : TAF_PDP_TYPE_ENUM_UINT8              ucPdpType,
              TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : z00214637
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_VOID AT_PS_SaveRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/******************************************************************************
 �� �� ��  : AT_PS_ResetRnicPdpDhcpPara
 ��������  : �յ�NDIS PDPȥ����ɹ���Ϣ������AppPdpEntity
 �������  : ucPdpType - PDP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : z00214637
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_VOID AT_PS_ResetRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);

/*****************************************************************************
 �� �� ��  : AT_PS_SendRnicPdnInfoCfgInd
 ��������  : ��RNIC����PDN������Ϣ
 �������  : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             VOS_UINT8                           ucRabId,
             AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoCfgInd(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    VOS_UINT8                           ucRabId,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
);

/*****************************************************************************
 �� �� ��  : AT_PS_SendRnicPdnInfoRelInd
 ��������  : ��RNIC����PDN�����ͷ�������Ϣ
 �������  : AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoRelInd(
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
 �� �� ��  : AT_PS_GetRptConnResultFunc
 ��������  : ��ȡ���ӽ�������ϱ�����ָ��
 �������  : ucUsrType - �û�����
 �������  : ��
 �� �� ֵ  : AT_PS_RPT_CONN_RSLT_FUNC
*****************************************************************************/
AT_PS_RPT_CONN_RSLT_FUNC AT_PS_GetRptConnResultFunc(AT_USER_TYPE ucUsrType);

/*****************************************************************************
 �� �� ��  : AT_PS_GetRptEndResultFunc
 ��������  : ��ȡ���ӶϿ�����ϱ�����ָ��
 �������  : ucUsrType - �û�����
 �������  : ��
 �� �� ֵ  : AT_PS_RPT_END_RSLT_FUNC
*****************************************************************************/
AT_PS_RPT_END_RSLT_FUNC AT_PS_GetRptEndResultFunc(AT_USER_TYPE ucUsrType);


VOS_UINT32 AT_PS_SetQosPara(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUserCid,
    VOS_UINT8                           ucActCid
);

/* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-17, begin */
VOS_UINT32 Taf_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *ucSpeed
);
/* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-17, end */

/* Added by m00217266 for L-C��������Ŀ, 2014-1-26, begin */
#if 0
/*****************************************************************************
 �� �� ��  : AT_QosParaTransferToQci
 ��������  : ����QOS����ת��ΪQCI�ȼ�
 �������  : TAF_UMTS_QOS_STRU                   *pQos
 �������  : ��
 �� �� ֵ  : QCI����

*****************************************************************************/
ADS_QCI_TYPE_ENUM_UINT8 AT_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                   *pQos
);
#endif
/* Added by m00217266 for L-C��������Ŀ, 2014-1-26, end */

/*****************************************************************************
 �� �� ��  : AT_ProcAppRegFCPoint
 ��������  : APP�û�����PDP״̬�ı�Ϊ����ʱ�Ĵ���
 �������  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID  AT_ProcAppRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_SendRnicIpv4ActInd
 ��������  : APP����ʱ֪ͨ��������IPV4����
 �������  : VOS_UINT8 ucRmNetId
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4ActInd(VOS_UINT8 ucRmNetId);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
�� �� ��  : AT_SendRnicIpv6ActInd
��������  : APP����ʱ֪ͨ��������IPV6����
�������  : VOS_UINT8 ucRmNetId
�������  : ��
�� �� ֵ  : �ɹ�
            ʧ��
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv6ActInd(VOS_UINT8 ucRmNetId);

/*****************************************************************************
�� �� ��  : AT_SendRnicIpv4v6ActInd
��������  : APP����ʱ֪ͨ��������IPV4V6����
�������  : VOS_UINT8 ucRmNetId
�������  : ��
�� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4v6ActInd(VOS_UINT8 ucRmNetId);

#endif

/*****************************************************************************
 �� �� ��  : AT_NdisIPv4DeactiveCnfProc
 ��������  : IPV4���͵�pdpȥ����ɹ���Ndis����
 �������  : pEvent  --- �¼�����
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID AT_NdisIPv4DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_DeActiveUsbNet
 ��������  : ȥ����USB��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_DeActiveUsbNet(VOS_VOID);

/*****************************************************************************
 �� �� ��  : AT_PS_GetDataChanlCfg
 ��������  : ��ȡ����ͨ��������Ϣ
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 �������  : ��
 �� �� ֵ  : AT_PS_DATA_CHANL_CFG_STRU*

*****************************************************************************/
AT_PS_DATA_CHANL_CFG_STRU* AT_PS_GetDataChanlCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 �� �� ��  : AT_PS_RegFCPoint
 ��������  : ע�����ص�
 �������  : ucCallId   - ����ʵ��ID
             pstEvent   - �¼���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_RegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_PS_GetCidByCallType
 ��������  : ��ȡ�������Ͷ�Ӧ��CID
 �������  : usClientId - �˿�ID
             ucCallId  - ����ʵ������
             enPdpType - PDP����
 �������  : ��
 �� �� ֵ  : VOS_UINT8 - CID

*****************************************************************************/
VOS_UINT8 AT_PS_GetCidByCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 �� �� ��  : AT_PS_SetCallStateByType
 ��������  : ����PDP�������ú���״̬
 �������  : usClientId - �˿�ID
             ucCallId   - ����ʵ������
             enPdpType  - PDP����(IPv4, IPv6 or IPv4v6)
             enPdpState - PDP״̬
 �������  : ��
*****************************************************************************/
VOS_VOID AT_PS_SetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
);

/*****************************************************************************
 �� �� ��  : AT_PS_SndCallConnectedResult
 ��������  : ���ӽ���״̬�ϱ�
 �������  : ucCallId  - ����ʵ������
             enPdpType - PDP����
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_SndCallConnectedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 �� �� ��  : AT_PS_SndCallEndedResult
 ��������  : �ϱ�����״̬^DEND
 �������  : ucCallId  - ����ʵ������
             enPdpType - PDP����
             enCause   - ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_SndCallEndedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/*****************************************************************************
 �� �� ��  : AT_PS_IsLinkGoingUp
 ��������  : �жϲ��������Ƿ��ѽ���/���ڽ���
 �������  : usClientId - �˿�ID
             ucCallId  - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �����ѽ���/���ڽ���
             VOS_FALSE - ����δ����
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingUp(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 �� �� ��  : AT_PS_IsLinkGoingDown
 ��������  : �жϲ��������Ƿ����ڶϿ�
 �������  : usClientId - �˿�ID
             ucCallId   - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 �� �� ��  : AT_PS_IsLinkDown
 ��������  : �жϲ��������Ƿ��Ѿ��Ͽ�
 �������  : usClientId - �˿�ID
             ucCallId   - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ���Ӳ�����
             VOS_FALSE - ���Ӵ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 �� �� ��  : AT_PS_GetFcIdFromRnicByRmNetId
 ��������  : ��ȡRNIC������FCID
 �������  : VOS_UINT32                          ulRmNetId
 �������  : ��
 �� �� ֵ  : FC_ID_ENUM_UINT8
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdFromRnicByRmNetId(
    VOS_UINT32                          ulRmNetId
);

/*****************************************************************************
 �� �� ��  : AT_PS_GetFcIdByUdiDeviceId
 ��������  : ͨ��DIPCͨ��ID���FCID
 �������  : UDI_DEVICE_ID                       enDataChannelId
 �������  : ��
 �� �� ֵ  : FC_ID_ENUM_UINT8
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdByUdiDeviceId(
    UDI_DEVICE_ID_E                     enDataChannelId
);

/*****************************************************************************
 �� �� ��  : AT_PS_ProcConflictDialUpWithCurrCall
 ��������  : ���������ӽ�����ͻ
 �������  : ucIndex  - �˿ں�(ClientId)����
             ucCallId - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_OK   - �ɹ�
             VOS_ERR  - ʧ��
*****************************************************************************/
VOS_UINT32 AT_PS_ProcConflictDialUpWithCurrCall(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 �� �� ��  : AT_PS_ReportCurrCallConnState
 ��������  : �ϱ���ǰ�ѽ����Ĳ�������״̬
 �������  : usClientId - �˿�ID
             ucCallId   - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallConnState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);


/*****************************************************************************
 �� �� ��  : AT_PS_ReportCurrCallEndState
 ��������  : �ϱ���ǰ�ѶϿ��Ĳ�������״̬
 �������  : usClientId - �˿�ID
             ucCallId   - ����ʵ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallEndState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 �� �� ��  : AT_PS_IsIpv6Support
 ��������  : �ж��Ƿ�֧��IPV6
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6Support(VOS_VOID);

/*****************************************************************************
 �� �� ��  : AT_PS_GetCallStateByCid
 ��������  : ����CID��ȡ����״̬
 �������  : usClientId - �˿�ID
             ucCallId   - ����ʵ������
             ucCid      - CID
 �������  : ��
 �� �� ֵ  : AT_PDP_STATE_ENUM_U8
 ���ú���  :
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 �� �� ��  : AT_PS_SndRnicIpv4PdpActInd
 ��������  : ��RNIC����PDP�����¼�, IPv4����
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv4PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_PS_SndRnicIpv6PdpActInd
 ��������  : ��RNIC����PDP�����¼�, IPv6����
 �������  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv6PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 �� �� ��  : AT_PS_SndDipcPdpDeactBearerTypeInd
 ��������  : AT��DIPCͨ������PDPȥ������Ϣ
 �������  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactBearerTypeInd(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
);

/*****************************************************************************
 �� �� ��  : AT_PS_SndDipcPdpActBearerTypeInd
 ��������  : AT��DIPCͨ������PDP������Ϣ
 �������  : ucCid          ----  CID
             pstEvent       ----  PsCallEventInfo
             enBearerType   ----  BearerType
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActBearerTypeInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
);

/******************************************************************************
 �� �� ��  : AT_LenStr2IpAddr
 ��������  : ���ַ�����ʽ��IP��ַת��ΪSMЭ��IP��ַ��ʽ.��ȫ�̳�V100R001
 �������  : pucStr - �ַ�����ʽ��IP��ַ
 �������  : pucIpAddr - SMЭ�鶨���IP��ַ
 �� �� ֵ  : TAF_SUCCESS - ת���ɹ�
             TAF_FAILURE - ת��ʧ��
******************************************************************************/
VOS_UINT32  AT_LenStr2IpAddr(
    VOS_UINT8                           *pucStr,
    VOS_UINT8                           *pucIpAddr
);

/******************************************************************************
 �� �� ��  : AT_DHCPServerSetUp
 ��������  : ����ptrDHCPParam��������DHCP Server��״̬����ͨ��ptrDHCPConfig
                ����DHCP Server���յ�����(�����������ء������)
                ���ر�DHCP Serverʱ����������������Ϊ��
 �������  : pstEventָ��PDPȥ�����ָ��
 �������  : AT_DHCP_SETUP_PARAM_ST *ptrDHCPCfg       DHCP���ò���
             AT_DHCP_CONFIG_STRU    *ptrDHCPConfig    ����DHCP��������
 �� �� ֵ  : VOS_OK      ��ȷ
             VOS_ERR     ����
******************************************************************************/
VOS_UINT32  AT_DHCPServerSetUp(
    AT_DHCP_SETUP_PARAM_ST              *ptrDHCPParam,
    AT_DHCP_CONFIG_STRU                 *ptrDHCPConfig
);

/*****************************************************************************
 �� �� ��  : AT_PS_ReportAllCallEndState
 ��������  : �ϱ����в������ӶϿ�״̬
 �������  : ucIndex - �˿ں�(ClientId)����
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_ReportAllCallEndState(VOS_UINT8 ucIndex);

/*****************************************************************************
 �� �� ��  : AT_PS_SetCid2CurrCall
 ��������  : ���õ�ǰ����CID
 �������  : usClientId - �˿�ID
             ucCallId  - ����ʵ������
             enPdpType - PDP����
             ucCid     - CID
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SetCid2CurrCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 �� �� ��  : AT_PS_PdpAddrProc
 ��������  : ����IPv4��ַ����
 �������  : ucCallId      - ����ʵ������
             pstDhcpConfig - DCHP��Ϣ
             pstEvent      - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_PdpAddrProc(
    VOS_UINT8                           ucCallId,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 �� �� ��  : AT_AppSndRnicPdpActInd
 ��������  : APP����ʱ����PDP���͸�RNIC���ͼ�����Ϣ
 �������  : enPdpType      PDP����
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_AppSndRnicPdpActInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 �� �� ��  : AT_PS_BuildExClientId
 ��������  : ������չ��ClientId(ModemId + ClientId)
 �������  : usClientId                 - ClientId
 �������  : ��
 �� �� ֵ  : VOS_UINT16                 - ���ɵ���չClientId
*****************************************************************************/
VOS_UINT16 AT_PS_BuildExClientId(VOS_UINT16 usClientId);

/*****************************************************************************
 �� �� ��  : AT_PS_BuildNdisExClientId
 ��������  : ������չ��ClientId(ModemId + ClientId)
 �������  : usPortIndex                - ���Ŷ˿�
             usClientId                 - ClientId
 �������  : ��
 �� �� ֵ  : VOS_UINT16                 - ���ɵ���չClientId
*****************************************************************************/
VOS_UINT16 AT_PS_BuildNdisExClientId(
    VOS_UINT16                          usPortIndex,
    VOS_UINT16                          usClientId
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 AT_PS_CheckDialRatType(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucBitRatType
);
#endif

VOS_VOID AT_PS_ProcRabidChangedEvent(
    TAF_PS_CALL_PDP_RABID_CHANGE_IND_STRU  *pstEvent
);


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


