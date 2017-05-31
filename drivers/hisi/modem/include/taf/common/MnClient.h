

#ifndef __MNCLIENT_H__
#define __MNCLIENT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"
#include  "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define AT_MAX_CLIENT_NUM               (AT_CLIENT_ID_BUTT)

/*�㲥Client Id����MODEM��ʹ�� */
#define MN_CLIENT_ID_BROADCAST          (0xFFFF)

/* �㲥ClientId˵������ߵ�2��bitλ��ʾModemId��
   Modem0��Ӧ�Ĺ㲥ClientΪ0011111111111111(0x3FFF)��
   Modem1��Ӧ�Ĺ㲥ClientΪ0111111111111111(0x7FFF)
   Modem1��Ӧ�Ĺ㲥ClientΪ1011111111111111(0xBFFF) */

/* Modem 0�Ĺ㲥Client Id */
#define AT_BROADCAST_CLIENT_ID_MODEM_0  (0x3FFF)

/* Modem 1�Ĺ㲥Client Id */
#define AT_BROADCAST_CLIENT_ID_MODEM_1  (0x7FFF)

/* Modem 2�Ĺ㲥Client Id */
#define AT_BROADCAST_CLIENT_ID_MODEM_2  (0xBFFF)


#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define AT_MAX_APP_CLIENT_ID            (AT_CLIENT_ID_APP26)
#else
#define AT_MAX_APP_CLIENT_ID            (AT_CLIENT_ID_APP1)
#endif

#define AT_MIN_APP_CLIENT_ID            (AT_CLIENT_ID_APP)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : AT_CLIENT_ID_ENUM_UINT8
 ö��˵��  : Client Id

  1.��    ��   : 2011��10��15��
    ��    ��   : ³��/l60609
    �޸�����   : ����AT��Clientid
*****************************************************************************/
enum AT_CLIENT_ID_ENUM
{
    AT_CLIENT_ID_PCUI                 = 0,
    AT_CLIENT_ID_CTRL,
    AT_CLIENT_ID_PCUI2,
    AT_CLIENT_ID_MODEM,
    AT_CLIENT_ID_NDIS,
    AT_CLIENT_ID_UART,
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CLIENT_ID_HSUART,
#endif
    AT_CLIENT_ID_SOCK,
    AT_CLIENT_ID_APPSOCK,
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_CLIENT_ID_HSIC1,
    AT_CLIENT_ID_HSIC2,
    AT_CLIENT_ID_HSIC3,
    AT_CLIENT_ID_HSIC4,
    AT_CLIENT_ID_HSIC_MODEM,
    AT_CLIENT_ID_MUX1,
    AT_CLIENT_ID_MUX2,
    AT_CLIENT_ID_MUX3,
    AT_CLIENT_ID_MUX4,
    AT_CLIENT_ID_MUX5,
    AT_CLIENT_ID_MUX6,
    AT_CLIENT_ID_MUX7,
    AT_CLIENT_ID_MUX8,
#endif
    AT_CLIENT_ID_APP,
    AT_CLIENT_ID_APP1,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    AT_CLIENT_ID_APP2,
    AT_CLIENT_ID_APP3,
    AT_CLIENT_ID_APP4,
    AT_CLIENT_ID_APP5,
    AT_CLIENT_ID_APP6,
    AT_CLIENT_ID_APP7,
    AT_CLIENT_ID_APP8,
    AT_CLIENT_ID_APP9,
    AT_CLIENT_ID_APP10,
    AT_CLIENT_ID_APP11,
    AT_CLIENT_ID_APP12,
    AT_CLIENT_ID_APP13,
    AT_CLIENT_ID_APP14,
    AT_CLIENT_ID_APP15,
    AT_CLIENT_ID_APP16,
    AT_CLIENT_ID_APP17,
    AT_CLIENT_ID_APP18,
    AT_CLIENT_ID_APP19,
    AT_CLIENT_ID_APP20,
    AT_CLIENT_ID_APP21,
    AT_CLIENT_ID_APP22,
    AT_CLIENT_ID_APP23,
    AT_CLIENT_ID_APP24,
    AT_CLIENT_ID_APP25,
    AT_CLIENT_ID_APP26,
#endif

    AT_CLIENT_ID_BUTT
};
typedef VOS_UINT16 AT_CLIENT_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : MN_OAM_CLIENT_ID_ENUM_UINT16
 ö��˵��  : OAM��client

  1.��    ��   : 2011��10��15��
    ��    ��   : ³��/l60609
    �޸�����   : �����ⲿclient idֵ
*****************************************************************************/
enum MN_OAM_CLIENT_ID_ENUM
{
    OAM_CLIENT_ID_OM                 = AT_CLIENT_ID_BUTT,
    OAM_CLIENT_ID_SPY,
    OAM_CLIENT_ID_DIAG,
    OAM_CLIENT_ID_STK,
    OAM_CLIENT_ID_PIH,
    OAM_CLIENT_ID_PB,
    OAM_CLIENT_ID_CBT,
    OMA_CLIENT_ID_BUTT
};
typedef VOS_UINT16 MN_OAM_CLIENT_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : MN_INTERNAL_CLIENT_ID_ENUM_UINT16
 ö��˵��  : INTERNAL��client

  1.��    ��   : 2014��1��11��
    ��    ��   : y00245242
    �޸�����   : ����Э��ջ�ڲ�client ID
  2.��    ��   : 2014��4��3��
    ��    ��   : S00261364
    �޸�����   : ����spm�ڲ�client ID
*****************************************************************************/
enum MN_INTERNAL_CLIENT_ID_ENUM
{
    INTERNAL_CLIENT_ID_SMMA             = OMA_CLIENT_ID_BUTT,
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    INTERNAL_CLIENT_ID_SPM,
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */
    INTERNAL_CLIENT_ID_BUTT
};
typedef VOS_UINT16 MN_INTERNAL_CLIENT_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : AT_CLIENT_TAB_INDEX_UINT8
 ö��˵��  : ÿ��client��gastAtClientTab��indexֵ

  1.��    ��   : 2011��10��15��
    ��    ��   : ³��/l60609
    �޸�����   : ����ATÿ��Client��Ӧ��indexֵ
*****************************************************************************/
enum AT_CLIENT_TAB_INDEX_ENUM
{
    AT_CLIENT_TAB_PCUI_INDEX              = 0,
    AT_CLIENT_TAB_CTRL_INDEX,
    AT_CLIENT_TAB_PCUI2_INDEX,
    AT_CLIENT_TAB_MODEM_INDEX,
    AT_CLIENT_TAB_NDIS_INDEX,
    AT_CLIENT_TAB_UART_INDEX,
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CLIENT_TAB_HSUART_INDEX,
#endif
    AT_CLIENT_TAB_SOCK_INDEX,
    AT_CLIENT_TAB_APPSOCK_INDEX,
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_CLIENT_TAB_HSIC1_INDEX,
    AT_CLIENT_TAB_HSIC2_INDEX,
    AT_CLIENT_TAB_HSIC3_INDEX,
    AT_CLIENT_TAB_HSIC4_INDEX,
    AT_CLIENT_TAB_HSIC_MODEM_INDEX,
    AT_CLIENT_TAB_MUX1_INDEX,
    AT_CLIENT_TAB_MUX2_INDEX,
    AT_CLIENT_TAB_MUX3_INDEX,
    AT_CLIENT_TAB_MUX4_INDEX,
    AT_CLIENT_TAB_MUX5_INDEX,
    AT_CLIENT_TAB_MUX6_INDEX,
    AT_CLIENT_TAB_MUX7_INDEX,
    AT_CLIENT_TAB_MUX8_INDEX,
#endif
    AT_CLIENT_TAB_APP_INDEX,
    AT_CLIENT_TAB_APP1_INDEX,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    AT_CLIENT_TAB_APP2_INDEX,
    AT_CLIENT_TAB_APP3_INDEX,
    AT_CLIENT_TAB_APP4_INDEX,
    AT_CLIENT_TAB_APP5_INDEX,
    AT_CLIENT_TAB_APP6_INDEX,
    AT_CLIENT_TAB_APP7_INDEX,
    AT_CLIENT_TAB_APP8_INDEX,
    AT_CLIENT_TAB_APP9_INDEX,
    AT_CLIENT_TAB_APP10_INDEX,
    AT_CLIENT_TAB_APP11_INDEX,
    AT_CLIENT_TAB_APP12_INDEX,
    AT_CLIENT_TAB_APP13_INDEX,
    AT_CLIENT_TAB_APP14_INDEX,
    AT_CLIENT_TAB_APP15_INDEX,
    AT_CLIENT_TAB_APP16_INDEX,
    AT_CLIENT_TAB_APP17_INDEX,
    AT_CLIENT_TAB_APP18_INDEX,
    AT_CLIENT_TAB_APP19_INDEX,
    AT_CLIENT_TAB_APP20_INDEX,
    AT_CLIENT_TAB_APP21_INDEX,
    AT_CLIENT_TAB_APP22_INDEX,
    AT_CLIENT_TAB_APP23_INDEX,
    AT_CLIENT_TAB_APP24_INDEX,
    AT_CLIENT_TAB_APP25_INDEX,
    AT_CLIENT_TAB_APP26_INDEX,
#endif

    AT_CLIENT_BUTT
};
typedef VOS_UINT8 AT_CLIENT_TAB_INDEX_UINT8;


/*****************************************************************************
 ö����    : MN_CLIENT_ID_TYPE_UINT16
 ö��˵��  : CLIENT ID����

  1.��    ��   : 2011��10��15��
    ��    ��   : ³��/l60609
    �޸�����   : ����CLIENT ID����
  2.��    ��   : 2014��1��11��
    ��    ��   : y00245242
    �޸�����   : ����CLIENT ID����
*****************************************************************************/
enum MN_CLIENT_ID_TYPE
{
    MN_CLIENT_ID_TYPE_AT,
    MN_CLIENT_ID_TYPE_OAM,
    MN_CLIENT_ID_TYPE_INTERNAL,
    MN_CLIENT_ID_TYPE_BUTT
};
typedef VOS_UINT16 MN_CLIENT_ID_TYPE_UINT16;

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 AT_GetModemIdFromClient(
    VOS_UINT16                          usClientId,
    MODEM_ID_ENUM_UINT16               *pModemId
);

extern MN_CLIENT_ID_T AT_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
);

extern MN_CLIENT_ID_T MN_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
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

#endif /* end of MnClient.h */
