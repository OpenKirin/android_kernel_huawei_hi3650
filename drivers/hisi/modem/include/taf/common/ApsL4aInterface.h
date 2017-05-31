

#ifndef _APS_L4A_INTERFACE_H_
#define _APS_L4A_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
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
#define APS_L4A_MAX_IPV6_PREFIX_NUM             (6)                             /* ���IPv6��ַǰ׺���� */

#define APS_L4A_MAX_APN_LEN                     (99)                            /* APN��󳤶� */
#define APS_L4A_MAX_IPV4_ADDR_LEN               (4)
#define APS_L4A_MAX_IPV6_ADDR_LEN               (16)

#define APS_L4A_MAX_ACCESS_NUM_LEN              (32)                            /* Lģ����, �ݲ�ʹ�� */
#define APS_L4A_MAX_USERNAME_LEN                (255)                           /* ��Ȩ�û������� */
#define APS_L4A_MAX_PASSWORD_LEN                (255)                           /* ��Ȩ���볤�� */

#define APS_L4A_MAX_SDF_PF_NUM                  (16)

#define APS_L4A_LTE_MAX_CID                     (31)

#define APS_L4A_AUTHDATA_MAX_USERNAME_LEN       (127)
#define APS_L4A_AUTHDATA_MAX_PASSWORD_LEN       (127)

/*****************************************************************************
  Maximum length of challenge used in authentication. The maximum length
  challenge name is the same as challenge.
*****************************************************************************/
#define APS_L4A_PPP_CHAP_CHALLNGE_LEN       (16)

/*****************************************************************************
  Maximum length of challenge name used in authentication.
*****************************************************************************/
#define APS_L4A_PPP_CHAP_CHALLNGE_NAME_LEN  (16)

/*****************************************************************************
  Maximum length of response used in authentication.
*****************************************************************************/
#define APS_L4A_PPP_CHAP_RESPONSE_LEN   (16)


/*****************************************************************************
  Maximum length of username used in authentication. It should be equal to
  the AUTHLEN(include one byte length) defined in PppInterface.h
*****************************************************************************/
#define APS_L4A_PPP_MAX_USERNAME_LEN    (99)


/*****************************************************************************
  Maximum length of password used in authentication. It should be equal to
  the PASSWORDLEN(include one byte length) defined in PppInterface.h
*****************************************************************************/
#define APS_L4A_PPP_MAX_PASSWORD_LEN    (99)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����: APS_L4A_MSG_ID_ENUM
 ö��˵��: APS��L4A֮���ԭ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_MSG_ID_ENUM
{
    ID_APS_L4A_SET_CGACT_REQ            = 0x0001020A,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGACT_REQ_STRU */
    ID_APS_L4A_SET_CGCMOD_REQ           = 0x0001022A,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGCMOD_REQ_STRU */
    ID_APS_L4A_SET_NDISCONN_REQ         = 0x00010291,                           /* _H2ASN_MsgChoice APS_L4A_SET_NDISCONN_REQ_STRU */
    ID_APS_L4A_SET_CGDCONT_REQ          = 0x00010222,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGDCONT_REQ_STRU */
    ID_APS_L4A_SET_CGDSCONT_REQ         = 0x00010226,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGDSCONT_REQ_STRU */
    ID_APS_L4A_SET_CGTFT_REQ            = 0x0001022C,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGTFT_REQ_STRU */
    ID_APS_L4A_SET_CGANS_REQ            = 0x00010212,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGANS_REQ_STRU */
    ID_APS_L4A_SET_CGAUTO_REQ           = 0x00010214,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGAUTO_REQ_STRU */
    ID_APS_L4A_SET_CGCONTRDP_REQ        = 0x00010232,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGCONTRDP_REQ_STRU */
    ID_APS_L4A_SET_CGSCONTRDP_REQ       = 0x00010234,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGSCONTRDP_REQ_STRU */
    ID_APS_L4A_SET_CGTFTRDP_REQ         = 0x00010230,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGTFTRDP_REQ_STRU */
    ID_APS_L4A_SET_CGEQOS_REQ           = 0x00010240,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGEQOS_REQ_STRU */
    ID_APS_L4A_SET_CGEQOSRDP_REQ        = 0x00010244,                           /* _H2ASN_MsgChoice APS_L4A_SET_CGEQOSRDP_REQ_STRU */
    ID_APS_L4A_SET_AUTHDATA_REQ         = 0x00010298,                           /* _H2ASN_MsgChoice APS_L4A_SET_AUTHDATA_REQ_STRU */
    ID_APS_L4A_IPV6_INFO_NOTIFY_IND     = 0x00010299,                           /* _H2ASN_MsgChoice APS_L4A_IPV6_INFO_NOTIFY_IND_STRU */
    ID_APS_L4A_ABORT_REQ                = 0x0001029A,                           /* _H2ASN_MsgChoice APS_L4A_ABORT_REQ_STRU */

    /* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
    ID_APS_L4A_GET_LTE_CS_REQ           = 0x000102A4,                           /* _H2ASN_MsgChoice APS_L4A_GET_LTE_CS_REQ_STRU */
    ID_APS_L4A_SET_PDPROFMOD_REQ        = 0x000102A5,                           /* _H2ASN_MsgChoice APS_L4A_SET_PDPROFMOD_REQ_STRU */
    ID_APS_L4A_GET_CEMODE_REQ           = 0x000102A6,

    /* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

    ID_APS_L4A_PPP_DIAL_REQ             = 0x000102A7,                           /* _H2ASN_MsgChoice APS_L4A_PPP_DIAL_REQ_STRU */
    ID_APS_L4A_PS_CALL_END_REQ          = 0x000102A8,                           /* _H2ASN_MsgChoice APS_L4A_PS_CALL_END_REQ_STRU */

    ID_L4A_APS_PDP_ACTIVATE_CNF         = 0x1001,                               /* _H2ASN_MsgChoice APS_L4A_PDP_ACTIVATE_CNF_STRU */
    ID_L4A_APS_PDP_ACTIVATE_REJ         = 0x1002,                               /* _H2ASN_MsgChoice APS_L4A_PDP_ACTIVATE_REJ_STRU */
    ID_L4A_APS_PDP_ACTIVATE_IND         = 0x1003,                               /* _H2ASN_MsgChoice APS_L4A_PDP_ACTIVATE_IND_STRU */
    ID_L4A_APS_PDP_MODIFY_CNF           = 0x1004,                               /* _H2ASN_MsgChoice APS_L4A_PDP_MODIFY_CNF_STRU */
    ID_L4A_APS_PDP_MODIFY_REJ           = 0x1005,                               /* _H2ASN_MsgChoice APS_L4A_PDP_MODIFY_REJ_STRU */
    ID_L4A_APS_PDP_MODIFY_IND           = 0x1006,                               /* _H2ASN_MsgChoice APS_L4A_PDP_MODIFY_IND_STRU */
    ID_L4A_APS_PDP_DEACTIVATE_CNF       = 0x1007,                               /* _H2ASN_MsgChoice APS_L4A_PDP_DEACTIVATE_CNF_STRU */
    ID_L4A_APS_PDP_DEACTIVATE_IND       = 0x1008,                               /* _H2ASN_MsgChoice APS_L4A_PDP_DEACTIVATE_IND_STRU */
    ID_L4A_APS_SET_NDISCONN_CNF         = 0x1009,                               /* _H2ASN_MsgChoice APS_L4A_SET_NDISCONN_CNF_STRU */
    ID_L4A_APS_SET_CGDCONT_CNF          = 0x100A,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGDCONT_CNF_STRU */
    ID_L4A_APS_SET_CGDSCONT_CNF         = 0x100B,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGDSCONT_CNF_STRU */
    ID_L4A_APS_SET_CGTFT_CNF            = 0x100C,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGTFT_CNF_STRU */
    ID_L4A_APS_SET_CGANS_CNF            = 0x100D,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGANS_CNF_STRU */
    ID_L4A_APS_SET_CGAUTO_CNF           = 0x100E,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGAUTO_CNF_STRU */
    ID_L4A_APS_SET_CGCONTRDP_CNF        = 0x100F,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGCONTRDP_CNF_STRU */
    ID_L4A_APS_SET_CGSCONTRDP_CNF       = 0x1010,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGSCONTRDP_CNF_STRU */
    ID_L4A_APS_SET_CGTFTRDP_CNF         = 0x1011,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGTFTRDP_CNF_STRU */
    ID_L4A_APS_SET_CGEQOS_CNF           = 0x1012,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGEQOS_CNF_STRU */
    ID_L4A_APS_SET_CGEQOSRDP_CNF        = 0x1013,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGEQOSRDP_CNF_STRU */
    ID_L4A_APS_SET_AUTHDATA_CNF         = 0x1014,                               /* _H2ASN_MsgChoice APS_L4A_SET_AUTHDATA_CNF_STRU */

    ID_L4A_APS_SET_CGACT_CNF            = 0x1015,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGACT_CNF_STRU */
    ID_L4A_APS_SET_CGCMOD_CNF           = 0x1016,                               /* _H2ASN_MsgChoice APS_L4A_SET_CGCMOD_CNF_STRU */
    ID_L4A_APS_PDP_DEACTIVATE_REJ       = 0x1017,                               /* _H2ASN_MsgChoice APS_L4A_PDP_DEACTIVATE_REJ_STRU */

    /* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
    ID_L4A_APS_GET_LTE_CS_CNF           = 0x1018,                               /* _H2ASN_MsgChoice APS_L4A_GET_LTE_CS_CNF_STRU */
    ID_L4A_APS_SET_PDPROFMOD_CNF        = 0x1019,                               /* _H2ASN_MsgChoice APS_L4A_SET_PDPROFMOD_CNF_STRU */
    ID_L4A_APS_GET_CEMODE_CNF           = 0x101d,                               /* _H2ASN_MsgChoice APS_L4A_GET_LTE_CS_CNF_STRU */

    /* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

    ID_L4A_APS_PPP_DIAL_CNF             = 0x101E,                               /* _H2ASN_MsgChoice APS_L4A_PPP_DIAL_CNF_STRU */
    ID_L4A_APS_PS_CALL_END_CNF          = 0x101F,                               /* _H2ASN_MsgChoice APS_L4A_PS_CALL_END_CNF_STRU */

    ID_L4A_APS_PDP_SETUP_IND            = 0x1020,                               /* _H2ASN_MsgChoice APS_L4A_PDP_SETUP_IND_STRU */

    ID_APS_L4A_MSG_BUTT
};
typedef VOS_UINT32 APS_L4A_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����: APS_L4A_PDP_TYPE_ENUM_UINT8
 ö��˵��: APS��L4A֮��PDP������
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_PDP_TYPE_ENUM
{
    APS_L4A_PDP_IPV4                            = 0x01,                         /* IPV4���� */
    APS_L4A_PDP_IPV6                            = 0x02,                         /* IPV6���� */
    APS_L4A_PDP_IPV4V6                          = 0x03,                         /* IPV4V6���� */
    APS_L4A_PDP_PPP                             = 0x04,                         /* PPP���� */

    APS_L4A_PDP_BUTT                            = 0xFF
};
typedef VOS_UINT8 APS_L4A_PDP_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����: APS_L4A_PDP_DATA_COMP_ENUM_UINT8
 ö��˵��: PDP����ѹ����ʽ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_PDP_DATA_COMP_ENUM
{
    APS_L4A_PDP_DATA_COMP_OFF                   = 0x00,                         /* default if value is omitted */
    APS_L4A_PDP_DATA_COMP_ON                    = 0x01,                         /* manufacturer preferred compression */
    APS_L4A_PDP_DATA_COMP_V42                   = 0x02,                         /* V42ѹ���㷨 */

    APS_L4A_PDP_DATA_COMP_BUTT                  = 0xFF
};
typedef VOS_UINT8 APS_L4A_PDP_DATA_COMP_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_PDP_HEAD_COMP_ENUM_UINT8
 ö��˵��: PDPͷѹ����ʽ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_PDP_HEAD_COMP_ENUM
{
    APS_L4A_PDP_HEAD_COMP_OFF                   = 0x00,                         /* default if value is omitted */
    APS_L4A_PDP_HEAD_COMP_ON                    = 0x01,                         /* manufacturer preferred compression */
    APS_L4A_PDP_HEAD_COMP_RFC1144               = 0x02,                         /* RFC1144ѹ���㷨��applicable for SNDCP only */
    APS_L4A_PDP_HEAD_COMP_RFC2507               = 0x03,                         /* RFC2507��applicable for SNDCP only */

    APS_L4A_PDP_HEAD_COMP_BUTT                  = 0xFF
};
typedef VOS_UINT8 APS_L4A_PDP_HEAD_COMP_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_TRAFFIC_CLASS_ENUM_UINT8
 ö��˵��: Traffic Class���͵Ķ���
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_TRAFFIC_CLASS_ENUM
{
    APS_L4A_TRAFFIC_CONVERSATIONAL_CLASS        = 0x00,                         /* Conversational class */
    APS_L4A_TRAFFIC_STREAMING_CLASS             = 0x01,                         /* Streaming class */
    APS_L4A_TRAFFIC_BACKGROUND_CLASS            = 0x02,                         /* Interactive class */
    APS_L4A_TRAFFIC_SUBSCRIBED_VALUE            = 0x03,                         /* Background class */

    APS_L4A_TRAFFIC_CLASS_BUTT                  = 0xFF
};
typedef VOS_UINT8 APS_L4A_TRAFFIC_CLASS_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_TRAFFIC_CLASS_ENUM_UINT8
 ö��˵��: �������ȼ��Ķ���
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_DELIVER_ORDER_ENUM
{
    APS_L4A_DELIVER_WITHOUT_DELIVER_ORDER       = 0x00,                         /* 0 : Without delivery order */
    APS_L4A_DELIVER_WITH_DELIVER_ORDER          = 0x01,                         /* 1 : With delivery order */
    APS_L4A_DELIVER_SUBSCRIBED_VAL              = 0x02,                         /* 2 : Subscribed value */

    APS_L4A_DELIVER_ORDER_BUTT                  = 0xFF
};
typedef VOS_UINT8 APS_L4A_DELIVER_ORDER_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_ERR_SDU_DELIVERED_ENUM_UINT8
 ö��˵��: ����� SDU�Ƿ񱻷���
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_ERR_SDU_DELIVERED_ENUM
{
    APS_L4A_ERR_SDU_NOT_DELIVERED               = 0x00,                         /* 0 : Erroneous SDUs are not delivered */
    APS_L4A_ERR_SDU_DELIVERED                   = 0x01,                         /* 1 : Erroneous SDUs are delivered */
    APS_L4A_ERR_SDU_NOT_DETECT                  = 0x02,                         /* 2 : No detect */
    APS_L4A_ERR_SDU_SUBSCRIBED_VAl              = 0x03,                         /* 3 : subscribed value */

    APS_L4A_ERR_SDU_DELIVERED_BUTT              = 0xFF
};
typedef VOS_UINT8 APS_L4A_ERR_SDU_DELIVERED_ENUM_UINT8;


/*****************************************************************************
 ö����: APS_L4A_RESIDUAL_BER_ENUM_UINT8
 ö��˵��: SDU��������������
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_RESIDUAL_BER_ENUM
{
    APS_L4A_RESIDUAL_BER_SUBSCRIBED_VAL         = 0x00,                         /* 0 : subscribed value */
    APS_L4A_RESIDUAL_BER_5E2                    = 0x01,                         /* 1 : 5*10-2 */
    APS_L4A_RESIDUAL_BER_1E2                    = 0x02,                         /* 2 : 1*10-2 */
    APS_L4A_RESIDUAL_BER_5E3                    = 0x03,                         /* 3 : 5*10-3 */
    APS_L4A_RESIDUAL_BER_4E3                    = 0x04,                         /* 4 : 4*10-3 */
    APS_L4A_RESIDUAL_BER_1E3                    = 0x05,                         /* 5 : 1*10-3 */
    APS_L4A_RESIDUAL_BER_1E4                    = 0x06,                         /* 6 : 1*10-4 */
    APS_L4A_RESIDUAL_BER_1E5                    = 0x07,                         /* 7 : 1*10-5 */
    APS_L4A_RESIDUAL_BER_1E6                    = 0x08,                         /* 8 : 1*10-6 */
    APS_L4A_RESIDUAL_BER_6E8                    = 0x09,                         /* 9 : 6*10-8 */

    APS_L4A_RESIDUAL_BER_BUTT                   = 0xFF
};
typedef VOS_UINT8 APS_L4A_RESIDUAL_BER_ENUM_UINT8;



/*****************************************************************************
 ö����: APS_L4A_SDU_ERR_RATIO_ENUM_UINT8
 ö��˵��: SDU������
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_SDU_ERR_RATIO_ENUM
{
    APS_L4A_SDU_ERR_RATIO_SUBSCRIBED_VAL        = 0x00,                           /* 0 : subscribed value */
    APS_L4A_SDU_ERR_RATIO_1E2                   = 0x01,                           /* 1 : 5*10-2 */
    APS_L4A_SDU_ERR_RATIO_7E3                   = 0x02,                           /* 2 : 1*10-2 */
    APS_L4A_SDU_ERR_RATIO_1E3                   = 0x03,                           /* 3 : 5*10-3 */
    APS_L4A_SDU_ERR_RATIO_1E4                   = 0x04,                           /* 4 : 4*10-3 */
    APS_L4A_SDU_ERR_RATIO_1E5                   = 0x05,                           /* 5 : 1*10-3 */
    APS_L4A_SDU_ERR_RATIO_1E6                   = 0x06,                           /* 6 : 1*10-4 */
    APS_L4A_SDU_ERR_RATIO_1E1                   = 0x07,                           /* 7 : 1*10-5 */

    APS_L4A_SDU_ERR_RATIO_BUTT                  = 0xFF
};
typedef VOS_UINT8 APS_L4A_SDU_ERR_RATIO_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_TRAFFIC_HANDLE_PRIO_ENUM_UINT8
 ö��˵��: �����������ȼ�
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_TRAFFIC_HANDLE_PRIO_ENUM
{
    APS_L4A_TRAFFIC_HANDLE_PRIO_SUBSCRIBED      = 0x00,                           /* 0 : Subscribed value */
    APS_L4A_TRAFFIC_HANDLE_PRIO_LEV1            = 0x01,                           /* 1 : Priority level 1 */
    APS_L4A_TRAFFIC_HANDLE_PRIO_LEV2            = 0x02,                           /* 2 : Priority level 2 */
    APS_L4A_TRAFFIC_HANDLE_PRIO_LEV3            = 0x03,                           /* 3 : Priority level 3 */

    APS_L4A_TRAFFIC_HANDLE_PRIO_BUTT            = 0xFF
};
typedef VOS_UINT8 APS_L4A_TRAFFIC_HANDLE_PRIO_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_PDP_STATE_ENUM_UINT8
 ö��˵��: PDP״̬
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_PDP_STATE_ENUM
{
    APS_L4A_PDP_STATE_INACTIVE                  = 0x00,                         /* PDPû���� */
    APS_L4A_PDP_STATE_ACTIVE                    = 0x01,                         /* PDP�Ѽ��� */

    APS_L4A_PDP_STATE_BUTT                      = 0xFF
};
typedef VOS_UINT32 APS_L4A_PDP_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����: APS_L4A_TFT_FILTER_ENUM_UINT8
 ö��˵��: TFT����������
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_TFT_FILTER_ENUM
{
    APS_L4A_TFT_FILTER_PRE_REL7                 = 0x00,                         /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162) */
    APS_L4A_TFT_FILTER_UPLINK                   = 0x01,                         /* 1 - Uplink */
    APS_L4A_TFT_FILTER_DOWNLINK                 = 0x02,                         /* 2 - Downlink */
    APS_L4A_TFT_FILTER_BIDIRECTION              = 0x03,                         /* 3 - Birectional (Up & Downlink) (default if omitted) */

    APS_L4A_TFT_FILTER_BUTT                     = 0xFF
};
typedef VOS_UINT8 APS_L4A_TFT_FILTER_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_AUTO_ANS_MODE_ENUM_UINT32
 ö��˵��: �Զ�Ӧ��ģʽ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_AUTO_ANS_MODE_ENUM
{
    APS_L4A_AUTO_ANS_MODE_TURN_OFF              = 0x00,                         /* 0 turn off automatic response for Packet Domain only */
    APS_L4A_AUTO_ANS_MODE_TURN_ON               = 0x01,                         /* 1 turn on automatic response for Packet Domain only */
    APS_L4A_AUTO_ANS_MODE_PS_ONLY               = 0x02,                         /* 2 modem compatibility mode, Packet Domain only */
    APS_L4A_AUTO_ANS_MODE_PS_CS                 = 0x03,                         /* 3 modem compatibility mode, Packet Domain and circuit switched calls (default) */
    APS_L4A_AUTO_ANS_MODE_PS_ONLY_NEG_RSP       = 0x04,                         /* 4 turn on automatic negative response for Packet Domain only */

    APS_L4A_AUTO_ANS_MODE_BUTT                  = 0xFF
};
typedef VOS_UINT32 APS_L4A_AUTO_ANS_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����: APS_L4A_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8
 ö��˵��: IPV4��ַ��ȡ��ʽ
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_IPV4_ADDR_ALLOC_TYPE_ENUM
{
   APS_L4A_IPV4_ADDR_ALLOC_TYPE_NAS_SIGNALING   = 0x00,
   APS_L4A_IPV4_ADDR_ALLOC_TYPE_DHCP            = 0x01,

   APS_L4A_IPV4_ADDR_ALLOC_TYPE_BUTT            = 0xFF
};
typedef VOS_UINT8 APS_L4A_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_BEARER_TYPE_ENUM_UINT8
 ö��˵��: ��������
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_BEARER_TYPE_ENUM
{
    APS_L4A_BEARER_TYPE_DEFAULT                 = 0x00,                         /* ȱʡ���� */
    APS_L4A_BEARER_TYPE_DEDICATED               = 0x01,                         /* ר�г��� */

    APS_L4A_BEARER_TYPE_BUTT                    = 0xFF
};
typedef VOS_UINT8 APS_L4A_BEARER_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_BEARER_TYPE_ENUM_UINT8
 ö��˵��: ��Ȩ����
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_GW_AUTH_TYPE_ENUM
{
    APS_L4A_GW_AUTH_TYPE_NONE                   = 0x00,
    APS_L4A_GW_AUTH_TYPE_PAP                    = 0x01,
    APS_L4A_GW_AUTH_TYPE_CHAP                   = 0x02,

    APS_L4A_GW_AUTH_TYPE_BUTT                   = 0xFF
};
typedef VOS_UINT32 APS_L4A_GW_AUTH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����: APS_L4A_BEARER_MANAGE_TYPE_ENUM_UINT8
 ö��˵��: Ӧ������(Ӧ��, �ܾ�)
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_BEARER_MANAGE_TYPE_ENUM
{
    APS_L4A_BEARER_MANAGE_TYPE_ACCEPT           = 0x00,                         /* ���� */
    APS_L4A_BEARER_MANAGE_TYPE_REJ              = 0x01,                         /* �ܾ� */

    APS_L4A_BEARER_MANANGE_TYPE_BUTT            = 0xFF
};
typedef VOS_UINT8 APS_L4A_BEARER_MANAGE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: APS_L4A_BEARER_MANAGE_MODE_ENUM_UINT8
 ö��˵��: Ӧ��ģʽ(�ֶ�, �Զ�)
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
enum APS_L4A_BEARER_MANAGE_MODE_ENUM
{
    APS_L4A_BEARER_MANAGE_MODE_AUTO             = 0x00,                         /* �Զ� */
    APS_L4A_BEARER_MANAGE_MODE_MANUAL           = 0x01,                         /* �ֶ� */

    APS_L4A_BEARER_MANAGE_MODE_BUTT             = 0xFF
};
typedef VOS_UINT8 APS_L4A_BEARER_MANAGE_MODE_ENUM_UINT8;

/*****************************************************************************
 ö������: APS_L4A_AUTH_TYPE_ENUM
 ö��˵��: Authentication Type
 1.��    ��   : 2012��08��10��
   ��    ��   : f00179208
   �޸�����   : Added for LTE PPP
*****************************************************************************/
enum APS_L4A_AUTH_TYPE_ENUM
{
    APS_L4A_AUTH_TYPE_NONE              = 0x00,
    APS_L4A_AUTH_TYPE_PAP               = 0x01,                                 /* _H2ASN_IeChoice_Export APS_L4A_PAP_PARAM_STRU */
    APS_L4A_AUTH_TYPE_CHAP              = 0x02,                                 /* _H2ASN_IeChoice_Export APS_L4A_CHAP_PARAM_STRU */
    APS_L4A_AUTH_TYPE_BUTT              = 0xFF
};
typedef VOS_UINT8 APS_L4A_AUTH_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö������: APS_L4A_EMC_IND_ENUM_UINT8
 ö��˵��: PDP�������Ƿ�Ϊ������
 �޸���ʷ      :
  1.��    ��   : 2013��07��18��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum APS_L4A_EMC_IND_ENUM
{
    APS_L4A_PDP_NOT_FOR_EMC             = 0x00,
    APS_L4A_PDP_FOR_EMC                 = 0x01,

    APS_L4A_EMC_IND_BUTT
};
typedef VOS_UINT8 APS_L4A_EMC_IND_ENUM_UINT8;

/*****************************************************************************
 ö����  : TAF_PDP_PCSCF_DISCOVERY_ENUM
 ö��˵��: P-CSCF DISCOVERY

 �޸���ʷ      :
  1.��    ��   : 2013��07��18��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum APS_L4A_PCSCF_DISCOVERY_ENUM
{
    APS_L4A_PCSCF_DISCOVERY_NOT_INFLUENCED  = 0x00,
    APS_L4A_PCSCF_DISCOVERY_THROUGH_NAS_SIG = 0x01,
    APS_L4A_PCSCF_DISCOVERY_THROUGH_DHCP    = 0x02,

    APS_L4A_PCSCF_DISCOVERY_BUTT
};
typedef VOS_UINT8 APS_L4A_PCSCF_DISCOVERY_ENUM_UINT8;

/*****************************************************************************
 ö����  : APS_L4A_IMS_CN_SIG_FLAG_ENUM
 ö��˵��: IMSר�г��ر�־

 �޸���ʷ      :
  1.��    ��   : 2013��07��18��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum APS_L4A_IMS_CN_SIG_FLAG_ENUM
{
    APS_L4A_PDP_NOT_FOR_IMS_CN_SIG_ONLY     = 0x00,
    APS_L4A_PDP_FOR_IMS_CN_SIG_ONLY         = 0x01,

    APS_L4A_IMS_CN_SIG_FLAG_BUTT
};
typedef VOS_UINT8 APS_L4A_IMS_CN_SIG_FLAG_ENUM_UINT8;


/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
/*****************************************************************************
 ö����  : APS_L4A_PDN_REQUEST_TYPE_ENUM
 ö��˵��: Table 10.5.173/3GPP TS24.008: Request type information element

 �޸���ʷ      :
  1.��    ��   : 2014��01��06��
    ��    ��   : l60609
    �޸�����   : ����ö��
*****************************************************************************/
enum APS_L4A_PDN_REQUEST_TYPE_ENUM
{
    /* initial request: when the MS is establishing connectivity to an additional PDN for the first time */
    APS_L4A_PDN_REQUEST_TYPE_INITIAL     = 0x1,

    /* Handover: when the connectivity to a PDN is established upon handover from a non-3GPP access network
        and the MS was connected to that PDN before the handover to the 3GPP access network */
    APS_L4A_PDN_REQUEST_TYPE_HANDOVER    = 0x2,

    /* Unused. If received, the network shall interpret this as "initial request". */
    APS_L4A_PDN_REQUEST_TYPE_UNUSED      = 0x3,

    /* emergency: the network shall use the APN or the GGSN/PDN GW configured for emergency bearer services. */
    APS_L4A_PDN_REQUEST_TYPE_EMERGENCY   = 0x4,

    APS_L4A_PDN_REQUEST_TYPE_BUTT
};

typedef VOS_UINT8 APS_L4A_PDN_REQUEST_TYPE_ENUM_UINT8;

/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */


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
 �ṹ��    : APS_L4A_APPCTRL_STRU
 �ṹ˵��  : Ϊ֧�ֶ�ͨ����������Ҫ��L4A����Ӧ�õĿ���ͷ������ָ�����ĸ�client��Ӧ�Ļظ�
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;                                  /* ���AT����DIAG�Ķ�Ӧ�� L4A����Ϣ����PID */
    VOS_UINT32                          ulClientId;                             /* ��AT���� */
    VOS_UINT32                          ulOpId;                                 /* �����֣���Զ������ÿ�������һ,���û���� */
} APS_L4A_APPCTRL_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_GW_AUTH_INFO_STRU
 �ṹ˵��  : ��Ȩ����
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    APS_L4A_GW_AUTH_TYPE_ENUM_UINT32    enGwAuthType;
    VOS_UINT8                           ucAccNumLen;
    VOS_UINT8                           aucRsv1[3];
    VOS_UINT8                           auAccessNum[APS_L4A_MAX_ACCESS_NUM_LEN];/*�˲�����������ʱ��ʹ��*/
    VOS_UINT8                           ucUserNameLen;
    VOS_UINT8                           aucRsv2[3];
    VOS_UINT8                           aucUserName[APS_L4A_MAX_USERNAME_LEN];
    VOS_UINT8                           ucPwdLen;
    VOS_UINT8                           aucRsv3[1];
    VOS_UINT8                           aucPwd[APS_L4A_MAX_PASSWORD_LEN];
}APS_L4A_GW_AUTH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_APN_INFO_STRU
 �ṹ˵��  : APN��Ϣ, aucApnName�������ַ���������
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApnName[APS_L4A_MAX_APN_LEN];
}APS_L4A_APN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_PDP_MANAGE_INFO_STRU
 �ṹ˵��  : PDP����ģʽ
 1.��    ��   : 2011��12��12��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    APS_L4A_BEARER_MANAGE_MODE_ENUM_UINT8   enMode;                             /* ���ع���ģʽ */
    APS_L4A_BEARER_MANAGE_TYPE_ENUM_UINT8   enType;                             /* ���ع������� */
    VOS_UINT8                               aucReserved[2];                     /* ���ֽڶ��룬���� */
}APS_L4A_PDP_MANAGE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_EPS_QOS_STRU
 �ṹ˵��  : EPS��QOS����
 1.��    ��   : 2011��12��10��
   ��    ��   : A00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    /* 0 QCI is selected by network
       [1 - 4]value range for guranteed bit rate Traffic Flows
       [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           ucReserved[3];

    /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULMBR;

}APS_L4A_EPS_QOS_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_PDP_TFT_STRU
 �ṹ˵��  : PDP�����ĵı��Ĺ�����(TFT)�Ĳ���
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
 2.��    ��   : 2015��9��28��
   ��    ��   : W00316404
   �޸�����   : R11 TFT Э������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask        : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask        : 1;
    VOS_UINT32                          bitOpProtocolId                : 1;
    VOS_UINT32                          bitOpSingleLocalPort           : 1;
    VOS_UINT32                          bitOpLocalPortRange            : 1;
    VOS_UINT32                          bitOpSingleRemotePort          : 1;
    VOS_UINT32                          bitOpRemotePortRange           : 1;
    VOS_UINT32                          bitOpSecuParaIndex             : 1;
    VOS_UINT32                          bitOpTypeOfService             : 1;
    VOS_UINT32                          bitOpFlowLabelType             : 1;
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask      : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask      : 1;
    VOS_UINT32                          bitOpSpare                     : 20;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    VOS_UINT8                           enDirection;
    VOS_UINT8                           ucPrecedence;             /*packet filter evaluation precedence*/

    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;             /*Э���*/
    VOS_UINT8                           ucTypeOfService;          /*TOS*/
    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucRmtIpv4AddreTAFss[APS_L4A_MAX_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpAddress[0]ΪIP��ַ���ֽ�λ
                                                                    ucSourceIpAddress[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv4Mask[APS_L4A_MAX_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpMask[0]ΪIP��ַ���ֽ�λ ,
                                                                    ucSourceIpMask[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv6Address[APS_L4A_MAX_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Address[0]ΪIPv6�ӿڱ�ʶ���ֽ�λ
                                                                    ucRmtIpv6Address[7]ΪIPv6�ӿڱ�ʶ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv6Mask[APS_L4A_MAX_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Mask[0]Ϊ���ֽ�λ
                                                                    ucRmtIpv6Mask[7]Ϊ���ֽ�λ*/

    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/

    VOS_UINT8                           aucLocalIpv4Addr[APS_L4A_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[APS_L4A_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[APS_L4A_MAX_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];

}APS_L4A_PDP_TFT_STRU;

/*****************************************************************************
 �ṹ����: APS_L4A_PDP_IPV6_PREFIX_STRU
 �ṹ˵��: IPv6ǰ׺��ַ�ṹ
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrefixLen;
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPrefix[APS_L4A_MAX_IPV6_ADDR_LEN];

} APS_L4A_PDP_IPV6_PREFIX_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_PDP_ADDR_STRU
 �ṹ˵��  : PDP��ַ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    APS_L4A_PDP_TYPE_ENUM_UINT8         enPdpType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucIpv4Addr[APS_L4A_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpv6Addr[APS_L4A_MAX_IPV6_ADDR_LEN];

} APS_L4A_PDP_ADDR_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGDCONT_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGDCONT_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_CGDCONT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGDSCONT_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGDSCONT_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_CGDSCONT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGTFT_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGTFT_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_CGTFT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGANS_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGANS_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* �ͻ���ID   */
    VOS_UINT8                           ucOpId;                                 /* ������ID   */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_CGANS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGAUTO_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGAUTO_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_CGAUTO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU
 �ṹ˵��  :
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
 2.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������enImCnSignalFlg

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBearerId        : 1;               /* BearerId */
    VOS_UINT32                          bitOpApn             : 1;               /* aucApn */
    VOS_UINT32                          bitOpIpAddr          : 1;               /* aucIpaddr */
    VOS_UINT32                          bitOpSubMask         : 1;               /* aucSubnetMask */
    VOS_UINT32                          bitOpGwAddr          : 1;               /* aucGWAddr */
    VOS_UINT32                          bitOpDNSPrimAddr     : 1;               /* aucDNSPrimAddr */
    VOS_UINT32                          bitOpDNSSecAddr      : 1;               /* aucDNSSecAddr */
    VOS_UINT32                          bitOpPCSCFPrimAddr   : 1;               /* aucPCSCFPrimAddr */
    VOS_UINT32                          bitOpPCSCFSecAddr    : 1;               /* aucPCSCFSecAddr */
    VOS_UINT32                          bitOpImCnSignalFlg   : 1;               /* enImCnSignalFlg */
    VOS_UINT32                          bitOpPadding         : 22;

    VOS_UINT8                           ucPrimayCid;                            /* default EPS bearer context */
    VOS_UINT8                           ucBearerId;                             /* a numeric parameter which identifies the bearer */

    /* the IM CN subsystem-related signalling flag */
    APS_L4A_IMS_CN_SIG_FLAG_ENUM_UINT8  enImCnSignalFlg;

    VOS_UINT8                           aucReserved[1];

    /* Access Pointer Name */
    VOS_UINT8                           aucApn[APS_L4A_MAX_APN_LEN + 1];

    /* the IP Address of the MT */
    APS_L4A_PDP_ADDR_STRU               stPdpAddr;

    /* the subnet mask for the IP Address of the MT */
    APS_L4A_PDP_ADDR_STRU               stSubnetMask;

    /* the Gateway Address of the MT */
    APS_L4A_PDP_ADDR_STRU               stGWAddr;

    /* the IP Address of the primary DNS Server */
    APS_L4A_PDP_ADDR_STRU               stDNSPrimAddr;

    /* the IP address of the secondary DNS Server */
    APS_L4A_PDP_ADDR_STRU               stDNSSecAddr;

    /* the IP Address of the primary P-CSCF Server */
    APS_L4A_PDP_ADDR_STRU               stPCSCFPrimAddr;

    /* the IP Address of the secondary P-CSCF Server */
    APS_L4A_PDP_ADDR_STRU               stPCSCFSecAddr;

} APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGCONTRDP_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGCONTRDP_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������   */
    VOS_UINT32                          ulCidNum;                               /* CID����  */
    APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU   astPrimParaInfo[0];                     /* ȱʡ���ض�̬���� */

} APS_L4A_SET_CGCONTRDP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU
 �ṹ˵��  :
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;

    /* default EPS bearer context */
    VOS_UINT8                           ucPrimaryCid;

    /* a numeric parameter which identifies the bearer */
    VOS_UINT8                           ucBearerId;

    VOS_UINT8                           ucReserved[1];

} APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGSCONTRDP_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGSCONTRDP_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������   */
    VOS_UINT32                          ulCidNum;                               /* CID����  */
    APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU    astSecParaInfo[0];                      /* ר�ó��ض�̬���� */

} APS_L4A_SET_CGSCONTRDP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_PDP_TFT_EXT_STRU
 �ṹ˵��  :
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
 2.��    ��   : 2015��9��28��
   ��    ��   : W00316404
   �޸�����   : R11 TFT Э������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPktFilterId    : 1;                /* ucPacketFilterId */
    VOS_UINT32                          bitOpPrecedence     : 1;                /* ucPrecedence */
    VOS_UINT32                          bitOpSrcIp          : 1;                /* aucSourceIpAddr,Mask */
    VOS_UINT32                          bitOpProtocolId     : 1;                /* ucProtocolId */
    VOS_UINT32                          bitOpDestPortRange  : 1;                /* destination port range */
    VOS_UINT32                          bitOpSrcPortRange   : 1;                /* source port range */
    VOS_UINT32                          bitOpSpi            : 1;                /* ipsec security parameter index */
    VOS_UINT32                          bitOpTosMask        : 1;                /* type of service */
    VOS_UINT32                          bitOpFlowLable      : 1;                /* ulFlowLable */
    VOS_UINT32                          bitOpDirection      : 1;                /* Direction */
    VOS_UINT32                          bitOpNwPktFilterId  : 1;                /* NWPacketFltId */
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask      : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask      : 1;
    VOS_UINT32                          bitOpSpare          : 19;

    VOS_UINT8                           ucPacketFilterId;                       /* Packet Filter Id,value range from 1 to 16 */
    VOS_UINT8                           ucPrecedence;                           /* evaluation precedence index,The value range is from 0 to 255 */
    VOS_UINT8                           ucProtocolId;                           /* protocol number,value range from 0 to 255 */
    VOS_UINT8                           ucReserved1;
    APS_L4A_PDP_ADDR_STRU               stSourceIpaddr;
    APS_L4A_PDP_ADDR_STRU               stSourceIpMask;
    VOS_UINT16                          usLowDestPort;                          /* value range from 0 to 65535 */
    VOS_UINT16                          usHighDestPort;                         /* value range from 0 to 65535 */
    VOS_UINT16                          usLowSourcePort;                        /* value range from 0 to 65535 */
    VOS_UINT16                          usHighSourcePort;                       /* value range from 0 to 65535 */
    VOS_UINT32                          ulSecuParaIndex;
    VOS_UINT8                           ucTypeOfService;                        /* value range from 0 to 255 */
    VOS_UINT8                           ucTypeOfServiceMask;                    /* value range from 0 to 255 */
    APS_L4A_TFT_FILTER_ENUM_UINT8       enTftFilterDirection;
    VOS_UINT8                           ucNwPktFilterId;                        /* value range from 1 to 16 */
    VOS_UINT32                          ulFlowLable;                            /* value range is from 00000 to FFFFF */
    VOS_UINT8                           aucLocalIpv4Addr[APS_L4A_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[APS_L4A_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[APS_L4A_MAX_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];
} APS_L4A_PDP_TFT_EXT_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_SDF_PF_TFT_STRU
 �ṹ˵��  :
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulPfNum;
    APS_L4A_PDP_TFT_EXT_STRU            astTftInfo[APS_L4A_MAX_SDF_PF_NUM];

} APS_L4A_SDF_PF_TFT_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGTFTRDP_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGTFTRDP_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������      */
    VOS_UINT32                          ulCidNum;                               /* CID����     */
    APS_L4A_SDF_PF_TFT_STRU             astPfTftInfo[0];                        /* ��̬TFT���� */

} APS_L4A_SET_CGTFTRDP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGEQOS_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGEQOS_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_CGEQOS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_EPS_QOS_EXT_STRU
 �ṹ˵��  :
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpQCI            : 1;                /* QCI */
    VOS_UINT32                          bitOpDLGBR          : 1;                /* DLGBR */
    VOS_UINT32                          bitOpULGBR          : 1;                /* ULGBR */
    VOS_UINT32                          bitOpDLMBR          : 1;                /* DLMBR */
    VOS_UINT32                          bitOpULMBR          : 1;                /* ULMBR */
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucCid;

    /* 0 QCI is selected by network
       [1 - 4]value range for guranteed bit rate Traffic Flows
       [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           ucReserved[2];

    /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULMBR;

}APS_L4A_EPS_QOS_EXT_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGEQOSRDP_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGEQOSRDP_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������      */
    VOS_UINT32                          ulCidNum;                               /* CID����     */
    APS_L4A_EPS_QOS_EXT_STRU            astEpsQosInfo[0];                       /* ��̬EPS QOS */

} APS_L4A_SET_CGEQOSRDP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGEQOS_CNF_STRU
 �ṹ˵��  : ID_L4A_APS_SET_CGEQOS_CNF��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_AUTHDATA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_IPV6_INFO_NOTIFY_IND_STRU
 �ṹ˵��  : ID_APS_L4A_IPV6_INFO_NOTIFY_IND��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucIpv6PrefixNum;                        /* IPv6��ַǰ׺���� */
    VOS_UINT8                           aucReserved[2];
    APS_L4A_PDP_IPV6_PREFIX_STRU        astIpv6PrefixArray[APS_L4A_MAX_IPV6_PREFIX_NUM];

} APS_L4A_IPV6_INFO_NOTIFY_IND_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_ABORT_REQ_STRU
 �ṹ˵��  : ID_APS_L4A_ABORT_REQ��Ϣ�ṹ��
 1.��    ��   : 2011��12��10��
   ��    ��   : a00165503
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} APS_L4A_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_PRIM_PDP_EXT_STRU
 �ṹ˵��  : ��PDP��������Ϣ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
 2.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������enImCnSignalFlg��enPcscfDiscovery
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdpType         : 1;               /* PdpType */
    VOS_UINT32                          bitOpApn             : 1;               /* aucApn */
    VOS_UINT32                          bitOpPdpAddr         : 1;               /* aucPdpAddr */
    VOS_UINT32                          bitOpPdpDcomp        : 1;               /* PdpDcomp */
    VOS_UINT32                          bitOpPdpHcomp        : 1;               /* PdpHcomp */
    VOS_UINT32                          bitOpIPV4ADDRALLOC   : 1;               /* IPV4ADDRALLOC */
    VOS_UINT32                          bitOpEmergency       : 1;               /* Emergency Indication */
    VOS_UINT32                          bitOpPcscfDiscovery  : 1;               /* P-CSCF discovery */
    VOS_UINT32                          bitOpImCnSignalFlg   : 1;               /* IM CN Signalling Flag */
    VOS_UINT32                          bitOpPadding         : 23;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucApn[APS_L4A_MAX_APN_LEN + 1];
    VOS_UINT8                           aucReserved1[3];
    APS_L4A_PDP_TYPE_ENUM_UINT8         enPdpType;
    VOS_UINT8                           aucReserved2[3];
    APS_L4A_PDP_ADDR_STRU               stPdpAddr;
    APS_L4A_PDP_DATA_COMP_ENUM_UINT8    enPdpDataComp;
    APS_L4A_PDP_HEAD_COMP_ENUM_UINT8    enPdpHeadComp;
    VOS_UINT8                           ucIPV4ADDRALLOC;                        /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted)
                                                                                   1 - IPv4 Address Allocated through DHCP */
    APS_L4A_EMC_IND_ENUM_UINT8          enEmergency;                            /* 0 - PDP context is not for emergency bearer services
                                                                                   1 - PDP context is for emergency bearer services */
    APS_L4A_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;                       /* 0 - Preference of P-CSCF address discovery not influenced by +CGDCONT */
                                                                                /* 1 - Preference of P-CSCF address discovery through NAS Signalling */
                                                                                /* 2 - Preference of P-CSCF address discovery through DHCP */

    APS_L4A_IMS_CN_SIG_FLAG_ENUM_UINT8  enImCnSignalFlg;                        /* 0 - UE indicates that the PDP context is not for IM CN subsystem-related signalling only */
                                                                                /* 1 - UE indicates that the PDP context is for IM CN subsystem-related signalling only */

    VOS_UINT8                           aucReserved3[2];
}APS_L4A_PRIM_PDP_EXT_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGDCONT_REQ_STRU
 �ṹ˵��  : AT����CGDCONT����������PDP�����Ĳ�����������Ϣ��L4A
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    APS_L4A_PRIM_PDP_EXT_STRU           stCgdcontInfo;

}APS_L4A_SET_CGDCONT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_SEC_PDP_EXT_STRU
 �ṹ˵��  : ��PDP��������Ϣ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimaryCid      : 1;               /* ucPrimaryCid */
    VOS_UINT32                          bitOpPdpDcomp        : 1;               /* PdpDcomp */
    VOS_UINT32                          bitOpPdpHcomp        : 1;               /* PdpHcomp */
    VOS_UINT32                          bitOpPadding         : 29;

    VOS_UINT8                           ucSecondaryCid;                         /* dedicated EPS Bearer context */
    VOS_UINT8                           ucPrimaryCid;                           /* Default EPS Bearer context */
    APS_L4A_PDP_DATA_COMP_ENUM_UINT8    enPdpDataComp;
    APS_L4A_PDP_HEAD_COMP_ENUM_UINT8    enPdpHeadComp;

}APS_L4A_SEC_PDP_EXT_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGDSCONT_REQ_STRU
 �ṹ˵��  : AT����CGDSCONT�������ø�PDP�����Ĳ�����������Ϣ��L4A
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    APS_L4A_SEC_PDP_EXT_STRU            stCgdscontInfo;

}APS_L4A_SET_CGDSCONT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGTFT_REQ_STRU
 �ṹ˵��  : AT����CGTFT��������PDP �����ĵı��Ĺ�����������������Ϣ��L4A
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulCid;
    APS_L4A_PDP_TFT_EXT_STRU            stTftInfo;

}APS_L4A_SET_CGTFT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGAUTO_REQ_STRU
 �ṹ˵��  : AT����CGAUTO,�����Զ�Ӧ��ģʽ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    APS_L4A_AUTO_ANS_MODE_ENUM_UINT32   enAnsMode;
    VOS_UINT32                          ulTimeout;                              /* �û��ظ�IND�ĳ�ʱ�趨, msΪ��λ, ������ʱ��δ�������Զ����� */

}APS_L4A_SET_CGAUTO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGPADDR_REQ_STRU
 �ṹ˵��  : AT����CGPADDR,��ѯPDP��ַ
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          aulCid[APS_L4A_LTE_MAX_CID+1];          /* cid:1~L4A_LTE_MAX_CID */

}APS_L4A_SET_CGPADDR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGCONTRDP_REQ_STRU
 �ṹ˵��  : AT����CGCONTRDP,��ȡCID��Ӧ����PDP��̬����
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT8                           aucCid[APS_L4A_LTE_MAX_CID + 1];                                  /* 0xff-if the parameter <cid> is omitted */

}APS_L4A_SET_CGCONTRDP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGSCONTRDP_REQ_STRU
 �ṹ˵��  : AT����CGSCONTRDP,��ȡCID��Ӧ�ĸ�PDP��̬����
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT8                           aucCid[APS_L4A_LTE_MAX_CID + 1];                                  /* 0xff-if the parameter <cid> is omitted */

}APS_L4A_SET_CGSCONTRDP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGTFTRDP_REQ_STRU
 �ṹ˵��  : AT����CGTFTRDP,��ȡTFT��̬����
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT8                           aucCid[APS_L4A_LTE_MAX_CID + 1];                                  /* 0xff-if the parameter <cid> is omitted */

}APS_L4A_SET_CGTFTRDP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_PS_CGEQOS_STRU
 �ṹ˵��  : EQOS�Ĳ���
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpQCI         : 1;                   /* ValQCI */
    VOS_UINT32                          bitOpDLGBR       : 1;                   /* ValDLGBR */
    VOS_UINT32                          bitOpULGBR       : 1;                   /* ValULGBR */
    VOS_UINT32                          bitOpDLMBR       : 1;                   /* ValDLMBR */
    VOS_UINT32                          bitOpULMBR       : 1;                   /* ValULMBR */
    VOS_UINT32                          bitOpPadding     : 27;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucValQCI;                               /* 0 QCI is selected by network
                                                                                  [1 - 4]value range for guranteed bit rate Traffic Flows
                                                                                  [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulValDLGBR;                             /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulValULGBR;                             /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulValDLMBR;                             /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulValULMBR;                             /* UL MBR in case of GBR QCI, The value is in kbit/s */

}APS_L4A_PS_CGEQOS_STRU;


/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGEQOS_REQ_STRU
 �ṹ˵��  : AT����CGEQOS,����EQOS����
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    APS_L4A_PS_CGEQOS_STRU              stCgeqosInfo;

}APS_L4A_SET_CGEQOS_REQ_STRU;



/*****************************************************************************
 �ṹ��    : APS_L4A_SET_CGEQOSRDP_REQ_STRU
 �ṹ˵��  : AT����CGEQOSRDP,��ȡEQOS��������
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT8                           aucCid[APS_L4A_LTE_MAX_CID + 1];

}APS_L4A_SET_CGEQOSRDP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_PDP_AUTHDATA_STRU
 �ṹ˵��  : AUTH����
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;                                  /* 1~16 */
    VOS_UINT8                           ucDefined;                              /* 0:undefined,1:defined */
    VOS_UINT16                          usAuthType;                             /* 0,1,2,0xFF */
    VOS_UINT32                          ulPLMN;                                 /* 16���ƴ洢 */
    VOS_UINT8                           ucPwdLen;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucPassword[APS_L4A_AUTHDATA_MAX_PASSWORD_LEN + 1];
    VOS_UINT8                           ucUserNameLen;
    VOS_UINT8                           aucReserved2[3];
    VOS_UINT8                           aucUserName[APS_L4A_AUTHDATA_MAX_USERNAME_LEN + 1];

}APS_L4A_PDP_AUTHDATA_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SET_AUTHDATA_REQ_STRU
 �ṹ˵��  : AT����CGEQOSRDP,��ȡEQOS��������
 1.��    ��   : 2011��12��12��
   ��    ��   : h44270
   �޸�����   : Added for PS�ں�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    APS_L4A_PDP_AUTHDATA_STRU           stAuthData;

}APS_L4A_SET_AUTHDATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_SDF_PARA_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2011��12��12��
   ��    ��   : l00198894
   �޸�����   : Added for PS�ں�
 2.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������enImCnSignalFlg��enPcscfDiscovery
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdnType            : 1;
    VOS_UINT32                          bitOpApn                : 1;
    VOS_UINT32                          bitOpSdfQos             : 1;
    VOS_UINT32                          bitOpLinkdCId           : 1;
    VOS_UINT32                          bitIpv4AddrAllocType    : 1;
    VOS_UINT32                          bitOpGwAuthInfo         : 1;
    VOS_UINT32                          bitOpEmergencyInd       : 1;
    VOS_UINT32                          bitOpPcscfDiscovery     : 1;
    VOS_UINT32                          bitOpImsCnSignalFlag    : 1;
    VOS_UINT32                          bitImsSuppFlag          : 1;
    VOS_UINT32                          bitOpSpare              : 22;

    APS_L4A_PDP_TYPE_ENUM_UINT8         enPdnType;
    APS_L4A_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;
    APS_L4A_BEARER_TYPE_ENUM_UINT8      enBearerCntxtType;                      /* SM�����Ķ�Ӧ���ص����� */

    APS_L4A_EMC_IND_ENUM_UINT8          enEmergencyInd;
    APS_L4A_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    APS_L4A_IMS_CN_SIG_FLAG_ENUM_UINT8  enImsCnSignalFlag;
    VOS_UINT8                           enImsSuppFlag;
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          ulCid;                                  /* ����������ID */
    VOS_UINT32                          ulLinkdCid;                             /* ����CID */

    VOS_UINT32                          ulPfNum;
    APS_L4A_EPS_QOS_STRU                stSdfQosInfo;
    APS_L4A_APN_INFO_STRU               stApnInfo;
    APS_L4A_GW_AUTH_INFO_STRU           stGwAuthInfo;
    APS_L4A_PDP_TFT_STRU                astCntxtTftInfo[APS_L4A_MAX_SDF_PF_NUM];

}APS_L4A_SDF_PARA_STRU;

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */

/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;

}APS_L4A_GET_CEMODE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;

    VOS_UINT32                          ulCurrentUeMode;                        /*��ǰUEģʽ*/
    VOS_UINT32                          ulSupportModeCnt;                       /*UE�ܹ�֧�ֵ�ģʽ�ĸ���*/
    VOS_UINT32                          aulSupportModeList[4];                  /*UE�ܹ�֧�ֵ�ģʽ*/
} APS_L4A_GET_CEMODE_CNF_STRU;
/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;

}APS_L4A_GET_LTE_CS_REQ_STRU;
/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

    VOS_UINT8                             ucSmsOverSGs;
    VOS_UINT8                             ucSmsOverIMS;
    VOS_UINT8                             ucCSFB;
    VOS_UINT8                             ucSrVcc;
    VOS_UINT8                             ucVoLGA;
    VOS_UINT8                             aucRsv[3];
} APS_L4A_GET_LTE_CS_CNF_STRU;
/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/

/* DTS2012031901936            : x00126983 2012-3-19 �ֽڶ��� + */
typedef struct
{
    VOS_UINT32                          bitOpPdpType        : 1;                /* PdpType */
    VOS_UINT32                          bitOpApn            : 1;                /* aucApn */
    VOS_UINT32                          bitOpUsername       : 1;                /* AuthUsername */
    VOS_UINT32                          bitOpPassword       : 1;                /* AuthPassword */
    VOS_UINT32                          bitOpAuthType       : 1;                /* AuthType */
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucDefined;                              /* 0:undefined, 1:defined */

    VOS_UINT8                           ucCid;

    /* 1 IP Internet Protocol (IETF STD 5) */
    /* 2 IPV6 Internet Protocol, version 6 (IETF RFC 2460) */
    /* 3 IPV4V6 Virtual <PDP_type> introduced to handle dual IP stack UE capability. (See 3GPP TS 24.301 [83]) */
    APS_L4A_PDP_TYPE_ENUM_UINT8             enPdpType;

    VOS_UINT8                           aucReserved1[1];

    /* Access Point Name */
    VOS_UINT8                           aucApn[APS_L4A_MAX_APN_LEN + 1];

    VOS_UINT8                           aucPassWord[APS_L4A_AUTHDATA_MAX_USERNAME_LEN + 1];
    VOS_UINT8                           ucPwdLen;
    VOS_UINT8                           aucReserved2[3];
    VOS_UINT8                           aucUserName[APS_L4A_AUTHDATA_MAX_PASSWORD_LEN + 1];
    VOS_UINT8                           ucUserNameLen;
    VOS_UINT8                           ucAuthType;
    VOS_UINT8                           aucReserved3[2];

}APS_L4A_PDP_PDPROFMOD_STRU;
/* DTS2012031901936            : x00126983 2012-3-19 �ֽڶ��� - */
/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    APS_L4A_PDP_PDPROFMOD_STRU          stPdprofmod;

}APS_L4A_SET_PDPROFMOD_REQ_STRU;
/*****************************************************************************
 �ṹ��    : APS_L4A_GET_CEMODE_REQ_STRU
 �ṹ˵��  : PDP�����������洢�Ĳ���
 1.��    ��   : 2012��04��21��
   ��    ��   : w00182550
   �޸�����   : V7����ͬ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT32                          ulErrorCode;                            /* ������     */

} APS_L4A_SET_PDPROFMOD_CNF_STRU;
/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

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
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_MsgChoice_Export APS_L4A_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          APS_L4A_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} APS_L4A_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    APS_L4A_INTERFACE_MSG_DATA          stMsgData;

} ApsL4aInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCidSdfParaInfo
 ��������  : ��ȡCID��Ӧ��SDF����, ��APS��֤��ȡ��SDF������Ч, ���CID��Ӧ��
             SDF������Ч, ����VOS_ERR, ���򷵻�VOS_OK
 �������  : ucCid                      - CID
 �������  : pstSdfParaInfo             - CID��Ӧ��SDF����
 �� �� ֵ  : VOS_OK                     - CID��Ӧ��SDF������Ч, ��ȡ�ɹ�
             VOS_ERR                    - CID��Ӧ��SDF������Ч, ��ȡʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 TAF_APS_GetCidSdfParaInfo(
    VOS_UINT8                           ucCid,
    APS_L4A_SDF_PARA_STRU              *pstSdfParaInfo
);

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCidImsCfgFlag
 ��������  : ��ȡCID��Ӧ��IMS����
 �������  : ucCid                      - CID
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - CID֧��IMS
             VOS_FALSE                  - CID��֧��IMS
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT8 TAF_APS_GetCidImsCfgFlag(VOS_UINT8 ucCid);


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpManageInfo
 ��������  : ��ȡPDP����ģʽ(�Զ�Ӧ��/�ܾ�), ��ʧ�ܳ���
 �������  : ��
 �������  : pstPdpManageInfo           - PDP����ģʽ
 �� �� ֵ  : VOS_OK                     - ��ȡPDP����ģʽ�ɹ�
             VOS_ERR                    - ��ȡPDP����ģʽʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
extern VOS_UINT32 TAF_APS_GetPdpManageInfo(
    APS_L4A_PDP_MANAGE_INFO_STRU       *pstPdpManageInfo
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
