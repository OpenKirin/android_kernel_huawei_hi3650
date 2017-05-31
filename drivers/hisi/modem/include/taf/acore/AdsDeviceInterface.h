

#ifndef __ADSDEVINTERFACE_H__
#define __ADSDEVINTERFACE_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ImmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����IPV6 MTU��󳤶�ֵ */
#define ADS_MTU_LEN_MAX                 (1500)

/* !!!!!!!!!!!��ʱ���壬���յ�ֵ�ɱ���ȷ�� */
#define ADS_NDIS_MSG_HDR                (0x00)
#define NDIS_ADS_MSG_HDR                (0x00)

#define ADS_IPV4_ADDR_LEN               (4)
#define ADS_IPV6_ADDR_LEN               (16)
#define ADS_IPV6_ADDR_HALF_LEN          (8)
#define ADS_IPV6_ADDR_QUARTER_LEN       (4)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
ö����    : ADS_PKT_TYPE_ENUM
�ṹ˵��  : PDP���Ͷ���

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDS��ADS����Ϣ������
*****************************************************************************/
enum ADS_PKT_TYPE_ENUM
{
    ADS_PKT_TYPE_IPV4 = 0x00,                                                   /* IPV4 */
    ADS_PKT_TYPE_IPV6 = 0x01,                                                   /* IPV6 */
    ADS_PKT_TYPE_BUTT
};
typedef VOS_UINT8 ADS_PKT_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : ADS_NDIS_IP_PACKET_TYPE_ENUM
�ṹ˵��  : IP PACKET���Ͷ���

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����IP PACKET����
*****************************************************************************/
enum ADS_NDIS_IP_PACKET_TYPE_ENUM
{
    ADS_NDIS_IP_PACKET_TYPE_DHCPV4      = 0x00,
    ADS_NDIS_IP_PACKET_TYPE_DHCPV6      = 0x01,
    ADS_NDIS_IP_PACKET_TYPE_ICMPV6      = 0x02,
    ADS_NDIS_IP_PACKET_TYPE_LINK_FE80   = 0x03,
    ADS_NDIS_IP_PACKET_TYPE_LINK_FF     = 0x04,
    ADS_NDIS_IP_PACKET_TYPE_BUTT
};
typedef VOS_UINT8 ADS_NDIS_IP_PACKET_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : ADS_NDIS_MSG_ID_ENUM
�ṹ˵��  : ADS��NDIS��֮�����Ϣ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����ADS��NDIS֮�����Ϣ
*****************************************************************************/
enum ADS_NDIS_MSG_ID_ENUM
{
    ID_ADS_NDIS_DATA_IND               = ADS_NDIS_MSG_HDR + 0x00,               /* ADS->CDS IP PACKET IND */
    ID_ADS_NDIS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  ADS_NDIS_MSG_ID_ENUM_UINT32;


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
 �ṹ��    : ADS_NDIS_DATA_IND_STRU
 �ṹ˵��  : ADS��NDIS֮������ݰ���Ϣ�ṹ

  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : ����CDS��ADS֮������ݰ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    ADS_NDIS_MSG_ID_ENUM_UINT32         enMsgId;                                /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    ADS_NDIS_IP_PACKET_TYPE_ENUM_UINT8  enIpPacketType;
    VOS_UINT8                           aucReserved[4];
    IMM_ZC_STRU                        *pstSkBuff;                              /* ���ݰ��ṹָ�� */
} ADS_NDIS_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��  : ADS_FILTER_IP_ADDR_INFO_STRU
 �ṹ˵��: IP��ַ��Ϣ
  1.��    ��   : 2013��6��3��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4Addr       : 1;
    VOS_UINT32                          bitOpIpv6Addr       : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucIpv4Addr[ADS_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpv6Addr[ADS_IPV6_ADDR_LEN];
} ADS_FILTER_IP_ADDR_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : ADS_UL_SendPacket
 ��������  : ADS����Ϊ�ϲ�ģ���ṩ�����ݷ��ͺ��������ӿڲ��ͷ��ڴ档
            �ϲ�ģ����ݷ���ֵ�ж��Ƿ���Ҫ�ͷ��ڴ�
 �������  : pstImmZc  --- IMM����
             ucExRabId --- RABID [5, 15]
             (*****ucExRabIdΪ��չ��RabId����2bit��ʾModemId����6bit��ʾRabId*****)
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/

VOS_UINT32 ADS_UL_SendPacket(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT8                           ucExRabId
);

typedef VOS_UINT32 (*RCV_DL_DATA_FUNC)(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pData, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam);

/*****************************************************************************
 �� �� ��  : ADS_DL_RegDlDataCallback
 ��������  : ADS�������ݴ���ģ��Ϊ�ϲ�ģ���ṩ��ע���������ݽ��պ����ӿ�
 �������  : ucExRabId --- ��չ���غ�
             (*****ucExRabIdΪ��չ��RabId����2bit��ʾModemId����6bit��ʾRabId*****)
             pFunc     --- ���ݽ��ջص�����ָ��
             ulExParam --- ��չ����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucExRabId,
    RCV_DL_DATA_FUNC                    pFunc,
    VOS_UINT32                          ulExParam
);

/*****************************************************************************
 �� �� ��  : ADS_DL_RegFilterDataCallback
 ��������  : ע���������ݹ��˻ص���չ
 �������  : ucRabId         - RABID [5, 15]
             pstFilterIpAddr - IP��ַ��Ϣ
             pFunc           - ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_OK          - ע��ɹ�
             VOS_ERR         - ע��ʧ��
*****************************************************************************/
VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
);

/*****************************************************************************
 �� �� ��  : ADS_DL_DeregFilterDataCallback
 ��������  : ȥע���������ݹ��˻ص���չ
 �������  : ucRabId - RABID [5, 15]
 �������  : ��
 �� �� ֵ  : VOS_OK  - ȥע��ɹ�
             VOS_ERR - ȥע��ʧ��
*****************************************************************************/
VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT8 ucRabId);

/*****************************************************************************
 �� �� ��  : ADS_UL_SendPacketEx
 ��������  : ���з���������չ�ӿ�, ʹ�øýӿڷ��͵�������ADS��¼����Ϣ, ����
             �������ݹ���ƥ��, �ýӿڱ����ADS_DL_RegFilterDataCallback���
             ʹ��, ֻ��ʹ��ADS_DL_RegFilterDataCallbackע������й��˻ص���,
             �������ݲ���Ҫ����ʹ�øýӿڼ�¼����Ϣ���й���
 �������  : pstImmZc  --- IMM����
             enIpType  --- IP����
             ucExRabId --- RABID [5, 15]
             (*****ucExRabIdΪ��չ��RabId����2bit��ʾModemId����6bit��ʾRabId*****)
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
VOS_UINT32 ADS_UL_SendPacketEx(
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    VOS_UINT8                           ucExRabId
);

#if (defined(CONFIG_BALONG_SPE))
/*****************************************************************************
 �� �� ��  : ADS_IPF_SpeIntWakeupADS
 ��������  : SPE�жϴ����¼�, ����ADS��������������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID ADS_IPF_SpeIntWakeupADS(VOS_VOID);

/*****************************************************************************
 �� �� ��  : ADS_IPF_RecycleMem
 ��������  : �����ڴ�
 �������  : pstImmZc --- imm memory
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERROR
*****************************************************************************/
VOS_INT ADS_IPF_RecycleMem(IMM_ZC_STRU *pstImmZc);

/*****************************************************************************
 �� �� ��  : ADS_IPF_RegSpeWPort
 ��������  : ע��SPE�˿�
 �������  : lPort --- �˿�
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID ADS_IPF_RegSpeWPort(VOS_INT32 lPort);

/*****************************************************************************
 �� �� ��  : ADS_IPF_GetSpeWPortTdDepth
 ��������  : ��ȡSPE WPORT�˿ڵ�TD�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : 0    --- ʹ��SPE��Ĭ������
             ���� --- ����ADSԤ�����ڴ��������������
*****************************************************************************/
VOS_UINT32 ADS_IPF_GetSpeWPortTdDepth(VOS_VOID);
#endif



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

