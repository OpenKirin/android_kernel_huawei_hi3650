

#ifndef __ATCTXPACKET_H__
#define __ATCTXPACKET_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_id.h"
#include "AtTypeDef.h"
#include "MnClient.h"
#include "TafApsApi.h"
/* Added by wx270776 for OM�ں�, 2015-7-25, begin */
#include "TafNvInterface.h"
/* Added by wx270776 for OM�ں�, 2015-7-25, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define AT_IPV6_CAPABILITY_IPV4_ONLY            (1)
#define AT_IPV6_CAPABILITY_IPV6_ONLY            (2)
#define AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP  (4)
#define AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP  (8)

/* PS����������� */
#define AT_PS_MAX_CALL_NUM              (3)


#define AT_PS_RABID_OFFSET              (5)                 /* RABIDƫ�� */
#define AT_PS_RABID_MAX_NUM             (11)                /* RABID���� */
#define AT_PS_MIN_RABID                 (5)                 /* RABID��Сֵ */
#define AT_PS_MAX_RABID                 (15)                /* RABID���ֵ */
#define AT_PS_INVALID_RABID             (0xFF)              /* RABID��Чֵ */
#define AT_PS_RABID_MODEM_1_MASK        (0x40)

#define IPV6_ADDRESS_TEST_MODE_ENABLE                    (0x55aa55aa)           /* 0x55aa55aaֵIPV6��ַΪ����ģʽ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum AT_PDP_STATE_ENUM
{
    AT_PDP_STATE_IDLE                = 0,
    AT_PDP_STATE_ACTED               = 1,
    AT_PDP_STATE_ACTING              = 2,
    AT_PDP_STATE_DEACTING            = 3,
    AT_PDP_STATE_BUTT
};
typedef VOS_UINT8 AT_PDP_STATE_ENUM_U8;

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
 �ṹ����   : AT_DIAL_PARAM_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : �����û����Ų���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           ucPdpTypeValidFlag;

    VOS_UINT8                           ucAPNLen;                               /*APN����*/
    VOS_UINT8                           aucAPN[TAF_MAX_APN_LEN + 1];             /*ָ��APNָ��*/

    VOS_UINT16                          usUsernameLen;                          /*username����*/
    VOS_UINT16                          usRsv3;
    VOS_UINT8                           aucUsername[TAF_MAX_GW_AUTH_USERNAME_LEN];  /*ָ��usernameָ��*/
    VOS_UINT8                           ucRsv4;

    VOS_UINT16                          usPasswordLen;                          /*password����*/
    VOS_UINT16                          usRsv5;
    VOS_UINT8                           aucPassword[TAF_MAX_GW_AUTH_PASSWORD_LEN];  /*ָ��passwordָ��*/
    VOS_UINT8                           ucRsv6;

    VOS_UINT16                          usAuthType;
    VOS_UINT8                           ucBitRatType;
    VOS_UINT8                           aucRsv7[1];                             /*���λ*/

    VOS_UINT32                          ulIPv4ValidFlag;
    VOS_UINT8                           aucIPv4Addr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulPrimIPv4DNSValidFlag;
    VOS_UINT8                           aucPrimIPv4DNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulSndIPv4DNSValidFlag;
    VOS_UINT8                           aucSndIPv4DNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulPrimIPv4WINNSValidFlag;
    VOS_UINT8                           aucPrimIPv4WINNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulSndIPv4WINNSValidFlag;
    VOS_UINT8                           aucSndIPv4WINNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulPrimIPv6DNSValidFlag;
    VOS_UINT8                           aucPrimIPv6DNSAddr[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulSndIPv6DNSValidFlag;
    VOS_UINT8                           aucSndIPv6DNSAddr[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulPrimIPv6WINNSValidFlag;
    VOS_UINT8                           aucPrimIPv6WINNSAddr[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulSndIPv6WINNSValidFlag;
    VOS_UINT8                           aucSndIPv6WINNSAddr[TAF_IPV6_ADDR_LEN];

}AT_DIAL_PARAM_STRU;

/*****************************************************************************
 �ṹ��    : AT_IPV6_DHCP_PARAM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6���͵�PDP�������ָ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv6PriDns   : 1;
    VOS_UINT32                          bitOpIpv6SecDns   : 1;
    VOS_UINT32                          bitOpIpv6PriPCSCF : 1;
    VOS_UINT32                          bitOpIpv6SecPCSCF : 1;
    VOS_UINT32                          bitOpIpv6ThiPCSCF : 1;
    VOS_UINT32                          bitOpIpv6Spare    : 27;

    VOS_UINT8                           ucRabId;                                /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucIpv6Addr[TAF_IPV6_ADDR_LEN];      /* �� PDP�����Ĵ�����IPV6��ַ���ȣ�������":" */

    VOS_UINT8                           aucIpv6PrimDNS[TAF_IPV6_ADDR_LEN];   /* �� PDP�����Ĵ�����IPV6��DNS���ȣ�������":" */
    VOS_UINT8                           aucIpv6SecDNS[TAF_IPV6_ADDR_LEN];    /* �� PDP�����Ĵ�����IPV6��DNS���ȣ�������":" */
    VOS_UINT8                           aucPrimPcscfAddr[TAF_IPV6_ADDR_LEN]; /* IPV6����P-CSCF�������� */
    VOS_UINT8                           aucSecPcscfAddr[TAF_IPV6_ADDR_LEN];  /* IPV6�ĸ�P-CSCF�������� */
    VOS_UINT8                           aucThiPcscfAddr[TAF_IPV6_ADDR_LEN];  /* IPV6�ĵ���P-CSCF�������� */
}AT_IPV6_DHCP_PARAM_STRU;

/*****************************************************************************
 �ṹ��    : AT_IPV4_DHCP_PARAM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4���͵�PDP�������ָ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PriDns   : 1;
    VOS_UINT32                          bitOpIpv4SecDns   : 1;
    VOS_UINT32                          bitOpIpv4PriWINNS : 1;
    VOS_UINT32                          bitOpIpv4SecWINNS : 1;
    VOS_UINT32                          bitOpIpv4PriPCSCF : 1;
    VOS_UINT32                          bitOpIpv4Secpcscf : 1;
    VOS_UINT32                          bitOpIpv4Thipcscf : 1;
    VOS_UINT32                          bitOpSpare        : 25;

    VOS_UINT8                           ucRabId;                                /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    VOS_UINT8                           aucRsv1[3];
    VOS_UINT32                          ulIpv4Addr;                             /* IPV4��IP��ַ�������� */
    VOS_UINT32                          ulIpv4NetMask;                          /* IPV4�����룬������ */
    VOS_UINT32                          ulIpv4GateWay;                          /* IPV4�����ص�ַ�������� */


    VOS_UINT32                          ulIpv4PrimDNS;                          /* IPV4����DNS�������� */
    VOS_UINT32                          ulIpv4SecDNS;                           /* IPV4����DNS�������� */
    VOS_UINT32                          ulIpv4PrimWINNS;                        /* IPV4����WINNS�������� */
    VOS_UINT32                          ulIpv4SecWINNS;                         /* IPV4�ĸ�WINNS�������� */
    VOS_UINT32                          ulIpv4PrimPCSCF;                        /* IPV4����P-CSCF�������� */
    VOS_UINT32                          ulIpv4SecPCSCF;                         /* IPV4�ĸ�P-CSCF�������� */
    VOS_UINT32                          ulIpv4ThiPCSCF;                         /* IPV4�ĵ���P-CSCF�������� */
    VOS_UINT8                           aucRsv2[4];
}AT_IPV4_DHCP_PARAM_STRU;


/*****************************************************************************
 �ṹ��  : AT_PS_USER_INFO_STRU
 �ṹ˵��: PS���û���Ϣ�ṹ

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
typedef struct
{
    AT_CLIENT_TAB_INDEX_UINT8           enPortIndex;
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;
    AT_USER_TYPE                        ucUsrType;
    VOS_UINT8                           ucUsrCid;
} AT_PS_USER_INFO_STRU;

/*****************************************************************************
 �ṹ����   : AT_IPV6_RA_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : RA��Ϣ����ز����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLanAddr            : 1;
    VOS_UINT32                          bitOpPrefixAddr         : 1;
    VOS_UINT32                          bitOpMtuSize            : 1;
    VOS_UINT32                          bitOpPreferredLifetime  : 1;
    VOS_UINT32                          bitOpValidLifetime      : 1;
    VOS_UINT32                          bitOpSpare              : 27;


    VOS_UINT8                           aucLanAddr[TAF_IPV6_ADDR_LEN];       /* IPv6 ·����LAN�˿ڵ�ַ */
    VOS_UINT8                           aucPrefixAddr[TAF_IPV6_ADDR_LEN];    /* IPv6ǰ׺ */
    VOS_UINT32                          ulPrefixBitLen;                         /* IPv6ǰ׺���� */
    VOS_UINT32                          ulMtuSize;                              /* RA��Ϣ�й㲥��IPv6��MTU��ȡֵ */
    VOS_UINT32                          ulPreferredLifetime;                    /* IPv6ǰ׺��Preferred lifetime */
    VOS_UINT32                          ulValidLifetime;                        /* IPv6ǰ׺��Valid lifetime */
} AT_IPV6_RA_INFO_STRU;


/*��Ϣ������ָ��*/
typedef VOS_VOID (*AT_PS_RPT_CONN_RSLT_FUNC)(\
    VOS_UINT8                           ucCid, \
    VOS_UINT8                           ucPortIndex, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

/*****************************************************************************
 �ṹ��    : AT_PS_REPORT_CONN_RESULT_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc;
}AT_PS_REPORT_CONN_RESULT_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*��Ϣ������ָ��*/
typedef VOS_VOID (*AT_PS_RPT_END_RSLT_FUNC)(\
    VOS_UINT8                           ucCid, \
    VOS_UINT8                           ucPortIndex, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType, \
    TAF_PS_CAUSE_ENUM_UINT32            enCause);

/*****************************************************************************
 �ṹ��    : AT_PS_REPORT_END_RESULT_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc;
}AT_PS_REPORT_END_RESULT_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*��Ϣ������ָ��*/
typedef VOS_VOID (*AT_PS_REG_FC_POINT_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent);

/*****************************************************************************
 �ṹ��    : AT_PS_REG_FC_POINT_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_REG_FC_POINT_FUNC             pRegFcPoint;
}AT_PS_REG_FC_POINT_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*��Ϣ������ָ��*/
typedef VOS_VOID (*AT_PS_DEREG_FC_POINT_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent);

/*****************************************************************************
 �ṹ��    : AT_PS_DEREG_FC_POINT_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2013��4��26��
    ��    ��   : L60609
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_DEREG_FC_POINT_FUNC           pDeRegFcPoint;
}AT_PS_DEREG_FC_POINT_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*��Ϣ������ָ��*/
typedef VOS_VOID (*AT_PS_SND_PDP_ACT_IND_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

/*****************************************************************************
 �ṹ��    : AT_PS_SND_PDP_ACT_IND_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2013��4��26��
    ��    ��   : L60609
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_SND_PDP_ACT_IND_FUNC          pSndPdpActInd;
}AT_PS_SND_PDP_ACT_IND_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*��Ϣ������ָ��*/
typedef VOS_VOID (*AT_PS_SND_PDP_DEACT_IND_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

/*****************************************************************************
 �ṹ��    : AT_PS_SND_PDP_DEACT_IND_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2013��4��26��
    ��    ��   : L60609
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_SND_PDP_DEACT_IND_FUNC        pSndPdpDeActInd;
}AT_PS_SND_PDP_DEACT_IND_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*****************************************************************************
 �ṹ��    : AT_PS_DATA_CHANL_CFG_STRU
 �ṹ˵��  : AT^CHDATA���õ�����ͨ����Ϣ

  1.��    ��   : 2013��4��24��
    ��    ��   : l60609
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsed;                                 /* ָ��CID�Ƿ��Ѿ�ͨ��CHDATA����������ͨ����VOS_TRUE:�Ѿ����ã�VOS_FALSE:δ���� */
    VOS_UINT32                          ulRmNetId;                              /* ����ͨ��ID
                                                                                   HSICͨ�� :UDI_ACM_HSIC_ACM1_ID��UDI_ACM_HSIC_ACM3_ID��UDI_ACM_HSIC_ACM5_ID�����δ������Ϊ��ЧֵUDI_INVAL_DEV_ID
                                                                                   VCOMͨ�� :RNIC_RMNET_ID_0 ~ RNIC_RMNET_ID_4
                                                                                   */
    VOS_UINT32                          ulRmNetActFlg;                          /* ָ��CID�Ƿ��Ѿ�PDP���VOS_TRUE:�Ѿ����VOS_FALSE:δ���� */
}AT_PS_DATA_CHANL_CFG_STRU;

#if (FEATURE_ON == FEATURE_IPV6)

/*****************************************************************************
 �ṹ��  : AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU
 �ṹ˵��: IPv4v6˫ջ���Ż��˴�����չԭ��ֵ(PS Cause)�ṹ��

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCauseNum;
    VOS_UINT8                           aucReserved[4];
    TAF_PS_CAUSE_ENUM_UINT32            aenPsCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];
} AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU;
#endif

/*****************************************************************************
 �ṹ��  : AT_PS_CALL_ENTITY_STRU
 �ṹ˵��: PS�����ʵ��ṹ

  1.��    ��   : 2012��12��10��
    ��    ��   : Y00213812
    �޸�����   : C50 IPv6 ��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsedFlg;          /* ����ʵ������־ */
    TAF_PDP_TYPE_ENUM_UINT8             enCurrPdpType;      /* ��ǰ�������� */
    VOS_UINT8                           aucRsv1[3];         /* ����λ */
    AT_PS_USER_INFO_STRU                stUserInfo;         /* ����ʵ���û���Ϣ */
    AT_DIAL_PARAM_STRU                  stUsrDialParam;     /* ����ʵ�岦�Ų��� */

    VOS_UINT8                           ucIpv4Cid;          /* IPv4 CID */
    AT_PDP_STATE_ENUM_U8                enIpv4State;        /* IPv4 ״̬ */
    VOS_UINT8                           aucRsv2[2];         /* ����λ */
    AT_IPV4_DHCP_PARAM_STRU             stIpv4DhcpInfo;     /* IPv4 DHCP��Ϣ */

#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucIpv6Cid;          /* IPv6 CID */
    AT_PDP_STATE_ENUM_U8                enIpv6State;        /* IPv6 ״̬ */
    VOS_UINT8                           aucRsv3[2];         /* ����λ */
    AT_IPV6_RA_INFO_STRU                stIpv6RaInfo;       /* IPv6 ·�ɹ�����Ϣ */
    AT_IPV6_DHCP_PARAM_STRU             stIpv6DhcpInfo;     /* IPv6 DHCP��Ϣ */
#endif

} AT_PS_CALL_ENTITY_STRU;

/*****************************************************************************
 �ṹ��  : AT_COMM_PS_CTX_STRU
 �ṹ˵��: PS�򹫹������Ľṹ

  1.��    ��   : 2013��4��24��
    ��    ��   : l60609
    �޸�����   : V9R1 IPv6&TAF/SM�ӿ��Ż���Ŀ����
  2.��    ��   : 2013��6��4��
    ��    ��   : z00214637
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
typedef struct
{
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucIpv6Capability;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulIpv6AddrTestModeCfg;

    /* �����û����Ƶ����ڻ��˴����PS��ԭ��ֵ */
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU  stIpv6BackProcExtCauseTbl;
#endif

    VOS_UINT8                           ucSharePdpFlag;
    VOS_UINT8                           aucReserved2[7];

    VOS_INT32                           lSpePort;
    VOS_UINT32                          ulIpfPortFlg;

}AT_COMM_PS_CTX_STRU;

/*****************************************************************************
 �ṹ��  : AT_MODEM_PS_CTX_STRU
 �ṹ˵��: PS��MODEM��������Ľṹ

  1.��    ��   : 2013��4��24��
    ��    ��   : l60609
    �޸�����   : V9R1 IPv6&TAF/SM�ӿ��Ż���Ŀ����

  2.��    ��   : 2013��11��11��
    ��    ��   : A00165503
    �޸�����   : DTS2013110900839: ���ӳ���IP��RABIDӳ���Ա
*****************************************************************************/
typedef struct
{
    /* �����CID������PS�����ʵ������� */
    VOS_UINT8                           aucCidToIndexTbl[TAF_MAX_CID + 1];

    /* PS�����ʵ�� */
    AT_PS_CALL_ENTITY_STRU              astCallEntity[AT_PS_MAX_CALL_NUM];

    /* CID������ͨ���Ķ�Ӧ��ϵ */
    AT_PS_DATA_CHANL_CFG_STRU           astChannelCfg[TAF_MAX_CID + 1];

    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    /* PS����д����� */
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    /* IP��ַ��RABID��ӳ���, IP��ַΪ������ */
    VOS_UINT32                          aulIpAddrRabIdMap[AT_PS_RABID_MAX_NUM];

} AT_MODEM_PS_CTX_STRU;


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

#endif /* end of AtCtxPacket.h */
