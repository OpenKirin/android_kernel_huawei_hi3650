

#ifndef __ATMTAINTERFACE_H__
#define __ATMTAINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "AtMnInterface.h"
/* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-27, begin */
#include "NasNvInterface.h"
/* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-27, end */
#include "TafNvInterface.h"
#include "MtaCommInterface.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MTA_CPOS_XML_MAX_LEN            (1024)              /* MTA����AT�·���XML������󳤶� */
#define MTA_CPOSR_XML_MAX_LEN           (1024)              /* MTA��AT�ϱ���XML������󳤶�Ϊ1024 */
#define MTA_SEC_PACKET_MAX_LEN          (272)               /* AP��ȫ�������󳤶� */
#define MTA_SIMLOCK_PASSWORD_LEN        (16)                /* ����������������ĳ��� */

#define MTA_CLIENTID_BROADCAST          (0xFFFF)
#define MTA_INVALID_TAB_INDEX           (0x00)


#define AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM          (10) /* autotest�����·����������� */
#define MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM         (20) /* autotest�����ϱ���������� */
#define MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM       (8)  /* һ�β���������С�������� */
#define MTA_AT_WRR_MAX_MEANRPT_NUM                (10) /* �ϱ������������������� */

#define MTA_AT_WRR_MAX_NCELL_NUM                  (8)

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
#define AT_MTA_RPT_CFG_MAX_SIZE                   (8)
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

#define AT_MTA_HANDLEDECT_MIN_TYPE                (0)
#define AT_MTA_HANDLEDECT_MAX_TYPE                (4)

#define AT_RSA_CIPHERTEXT_LEN           (128)

#define  AT_MTA_INTEREST_FREQ_MAX_NUM         (0x05)
#define  AT_MTA_MBMS_AVL_SERVICE_MAX_NUM      (0x10)
#define  AT_MTA_ISMCOEX_BANDWIDTH_NUM         (0x06)

#define AT_MTA_MEID_DATA_LEN                         (7)

#define MTA_AT_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define MTA_AT_EFRUIMID_OCTET_LEN_FIVE                    (5)

#define MTA_AT_UIMID_OCTET_LEN                            (4)

#define AT_MTA_GPS_XO_COEF_NUM                       (4)

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
#define MTA_FREQLOCK_MAX_MODE                     (4)
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : AT_MTA_MSG_TYPE_ENUM
 �ṹ˵��  : AT��MTA��Ϣ�ӿ�ö��
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
2.��    ��   : 2012��11��21��
  ��    ��   : z00161729
  �޸�����  : ֧��cerssi��nmr
3.��    ��   : 2012��12��26��
  ��    ��   : m00217266
  �޸�����   :  ���WAS�ӿڵ���ϢID
4.��    ��  : 2013��03��13��
  ��    ��  : z00214637
  �޸�����  : BodySAR��Ŀ
5.��    ��   : 2013��3��25��
  ��    ��   : s00217060
  �޸�����   : ��������ϱ�������C�˵���ϢID
*****************************************************************************/
enum AT_MTA_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /* ��ϢID */        /* ��ע, ����ASN */
    /* AT����MTA����Ϣ */
    ID_AT_MTA_CPOS_SET_REQ              = 0x0000,           /* _H2ASN_MsgChoice AT_MTA_CPOS_REQ_STRU        */
    ID_AT_MTA_CGPSCLOCK_SET_REQ         = 0x0001,           /* _H2ASN_MsgChoice AT_MTA_CGPSCLOCK_REQ_STRU   */
    ID_AT_MTA_APSEC_SET_REQ             = 0x0002,           /* _H2ASN_MsgChoice AT_MTA_APSEC_REQ_STRU       */
    ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ     = 0x0003,           /* _H2ASN_MsgChoice AT_MTA_SIMLOCKUNLOCK_REQ_STRU */

    ID_AT_MTA_QRY_NMR_REQ               = 0x0004,           /* _H2ASN_MsgChoice AT_MTA_QRY_NMR_REQ_STRU */

    ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF  = 0x0005,           /* _H2ASN_MsgChoice AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU */
    ID_AT_MTA_WRR_AUTOTEST_QRY_REQ      = 0x0006,           /* _H2ASN_MsgChoice AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU */
    ID_AT_MTA_WRR_CELLINFO_QRY_REQ      = 0x0007,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_MEANRPT_QRY_REQ       = 0x0008,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_FREQLOCK_SET_REQ      = 0x0009,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_CTRL_STRU     */
    ID_AT_MTA_WRR_RRC_VERSION_SET_REQ   = 0x000A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_CELLSRH_SET_REQ       = 0x000B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU*/
    ID_AT_MTA_WRR_FREQLOCK_QRY_REQ      = 0x000C,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ   = 0x000D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_WRR_CELLSRH_QRY_REQ       = 0x000E,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_BODY_SAR_SET_REQ          = 0x000F,           /* _H2ASN_MsgChoice AT_MTA_BODY_SAR_SET_REQ_STRU */
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
    ID_AT_MTA_CURC_SET_NOTIFY           = 0x0010,           /* _H2ASN_MsgChoice AT_MTA_CURC_SET_NOTIFY_STRU */
    ID_AT_MTA_CURC_QRY_REQ              = 0x0011,           /* _H2ASN_MsgChoice AT_MTA_CURC_QRY_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_SET_REQ   = 0x0012,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU */
    ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ   = 0x0013,           /* _H2ASN_MsgChoice AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU */
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

    ID_AT_MTA_IMEI_VERIFY_QRY_REQ       = 0x0014,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CGSN_QRY_REQ              = 0x0015,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NCELL_MONITOR_SET_REQ     = 0x0016,           /* _H2ASN_MsgChoice AT_MTA_NCELL_MONITOR_SET_REQ_STRU */
    ID_AT_MTA_NCELL_MONITOR_QRY_REQ     = 0x0017,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_REFCLKFREQ_SET_REQ        = 0x0018,           /* _H2ASN_MsgChoice AT_MTA_REFCLKFREQ_SET_REQ_STRU */
    ID_AT_MTA_REFCLKFREQ_QRY_REQ        = 0x0019,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_HANDLEDECT_SET_REQ        = 0x001A,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_HANDLEDECT_QRY_REQ        = 0x001B,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    /* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
    ID_AT_MTA_ECID_SET_REQ              = 0x001C,           /* _H2ASN_MsgChoice AT_MTA_ECID_SET_REQ_STRU */
    /* Added by l00198894 for ����+ECID����, 2013-12-09, end */

    ID_AT_MTA_MIPICLK_QRY_REQ           = 0x001D,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_DPDTTEST_FLAG_REQ     = 0x001E,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU */
    ID_AT_MTA_SET_DPDT_VALUE_REQ        = 0x001F,           /* _H2ASN_MsgChoice AT_MTA_SET_DPDT_VALUE_REQ_STRU */
    ID_AT_MTA_QRY_DPDT_VALUE_REQ        = 0x0020,           /* _H2ASN_MsgChoice AT_MTA_QRY_DPDT_VALUE_REQ_STRU */

    ID_AT_MTA_RRC_PROTECT_PS_REQ        = 0x0021,
    ID_AT_MTA_PHY_INIT_REQ              = 0x0022,

    ID_AT_MTA_SET_JAM_DETECT_REQ        = 0x0023,           /* _H2ASN_MsgChoice AT_MTA_SET_JAM_DETECT_REQ_STRU */

    ID_AT_MTA_SET_FREQ_LOCK_REQ         = 0x0024,           /* _H2ASN_MsgChoice AT_MTA_SET_FREQ_LOCK_REQ_STRU */

    ID_AT_MTA_SET_GSM_FREQLOCK_REQ      = 0x0025,          /* _H2ASN_MsgChoice AT_MTA_SET_GSM_FREQLOCK_REQ_STRU */
    ID_AT_MTA_SET_FEMCTRL_REQ           = 0x0026,

    ID_AT_MTA_NVWRSECCTRL_SET_REQ       = 0x0027,

    ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ   = 0x0028,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU */
    ID_AT_MTA_MBMS_PREFERENCE_SET_REQ       = 0x0029,      /* _H2ASN_MsgChoice AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU */
    ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ    = 0x002A,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ     = 0x002B,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_NETWORK_INFO_QRY_REQ          = 0x002C,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_EMBMS_STATUS_QRY_REQ          = 0x002D,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ  = 0x002E,      /* _H2ASN_MsgChoice AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU */
    ID_AT_MTA_LTE_LOW_POWER_SET_REQ         = 0x002F,      /* _H2ASN_MsgChoice AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU */
    ID_AT_MTA_INTEREST_LIST_SET_REQ         = 0x0030,      /* _H2ASN_MsgChoice AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU */
    ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ    = 0x0031,      /* _H2ASN_MsgChoice AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU */
    ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ = 0x0032,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_SET_REQ         = 0x0033,      /* _H2ASN_MsgChoice AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU */
    ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ         = 0x0034,      /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */

    ID_AT_MTA_SET_FR_REQ                = 0x0035,

    ID_AT_MTA_MEID_SET_REQ              = 0x0036,     /* _H2ASN_MsgChoice AT_MTA_MEID_SET_REQ_STRU */
    ID_AT_MTA_MEID_QRY_REQ              = 0x0037,

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_AT_MTA_SET_M2M_FREQLOCK_REQ      = 0x0038,           /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_REQ_STRU */
    ID_AT_MTA_QRY_M2M_FREQLOCK_REQ      = 0x0039,           /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
#endif

    ID_AT_MTA_TRANSMODE_QRY_REQ         = 0x0044,

    ID_AT_MTA_UE_CENTER_SET_REQ         = 0x0045,     /* _H2ASN_MsgChoice AT_MTA_SET_UE_CENTER_REQ_STRU */
    ID_AT_MTA_UE_CENTER_QRY_REQ         = 0x0046,

    ID_AT_MTA_SET_NETMON_SCELL_REQ      = 0x0047,
    ID_AT_MTA_SET_NETMON_NCELL_REQ      = 0x0048,

    ID_AT_MTA_RFICSSIRD_QRY_REQ         = 0x0049,

    ID_AT_MTA_ANQUERY_QRY_REQ           = 0x004A,
    ID_AT_MTA_CSNR_QRY_REQ              = 0x004B,
    ID_AT_MTA_CSQLVL_QRY_REQ            = 0x004C,

    ID_AT_MTA_EVDO_SYS_EVENT_SET_REQ    = 0x004d,     /* _H2ASN_MsgChoice AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU */
    ID_AT_MTA_EVDO_SIG_MASK_SET_REQ     = 0x004e,     /* _H2ASN_MsgChoice AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU */

    ID_AT_MTA_XCPOSR_SET_REQ            = 0x004F,                               /* _H2ASN_MsgChoice AT_MTA_SET_XCPOSR_REQ_STRU */
    ID_AT_MTA_XCPOSR_QRY_REQ            = 0x0050,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_XCPOSRRPT_SET_REQ         = 0x0051,                               /* _H2ASN_MsgChoice AT_MTA_SET_XCPOSRRPT_REQ_STRU */
    ID_AT_MTA_XCPOSRRPT_QRY_REQ         = 0x0052,                               /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_AT_MTA_CLEAR_HISTORY_FREQ_REQ    = 0x0053,       /* _H2ASN_MsgChoice AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU */

    ID_AT_MTA_SET_SENSOR_REQ            = 0x0054,                               /* _H2ASN_MsgChoice AT_MTA_SET_SENSOR_REQ_STRU*/
    ID_AT_MTA_SET_SCREEN_REQ            = 0x0055,                               /* _H2ASN_MsgChoice AT_MTA_SET_SCREEN_REQ_STRU*/

    /* MTA����AT����Ϣ */
    ID_MTA_AT_CPOS_SET_CNF              = 0x1000,           /* _H2ASN_MsgChoice MTA_AT_CPOS_CNF_STRU        */
    ID_MTA_AT_CGPSCLOCK_SET_CNF         = 0x1001,           /* _H2ASN_MsgChoice MTA_AT_CGPSCLOCK_CNF_STRU   */
    ID_MTA_AT_CPOSR_IND                 = 0x1002,           /* _H2ASN_MsgChoice MTA_AT_CPOSR_IND_STRU       */
    ID_MTA_AT_XCPOSRRPT_IND             = 0x1003,           /* _H2ASN_MsgChoice MTA_AT_XCPOSRRPT_IND_STRU   */
    ID_MTA_AT_APSEC_SET_CNF             = 0x1004,           /* _H2ASN_MsgChoice MTA_AT_APSEC_CNF_STRU       */
    ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF     = 0x1005,           /* _H2ASN_MsgChoice MTA_AT_SIMLOCKUNLOCK_CNF_STRU */

    ID_MTA_AT_QRY_NMR_CNF               = 0x1006,           /* _H2ASN_MsgChoice MTA_AT_QRY_NMR_CNF_STRU */

    ID_MTA_AT_WRR_AUTOTEST_QRY_CNF      = 0x1007,           /* _H2ASN_MsgChoice MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_CELLINFO_QRY_CNF      = 0x1008,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLINFO_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_MEANRPT_QRY_CNF       = 0x1009,           /* _H2ASN_MsgChoice MTA_AT_WRR_MEANRPT_QRY_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_SET_CNF      = 0x100A,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_SET_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_SET_CNF   = 0x100B,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_SET_CNF       = 0x100C,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_SET_CNF_STRU        */
    ID_MTA_AT_WRR_FREQLOCK_QRY_CNF      = 0x100D,           /* _H2ASN_MsgChoice MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU       */
    ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF   = 0x100E,           /* _H2ASN_MsgChoice MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    */
    ID_MTA_AT_WRR_CELLSRH_QRY_CNF       = 0x100F,           /* _H2ASN_MsgChoice MTA_AT_WRR_CELLSRH_QRY_CNF_STRU        */

    ID_MTA_AT_BODY_SAR_SET_CNF          = 0x1010,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
    ID_MTA_AT_CURC_QRY_CNF              = 0x1011,           /* _H2ASN_MsgChoice MTA_AT_CURC_QRY_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_SET_CNF   = 0x1012,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU */
    ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF   = 0x1013,           /* _H2ASN_MsgChoice MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU */
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

    ID_MTA_AT_IMEI_VERIFY_QRY_CNF       = 0x1014,            /* _H2ASN_MsgChoice AT_MTA_RESERVE_STRU */
    ID_MTA_AT_CGSN_QRY_CNF              = 0x1015,            /* _H2ASN_MsgChoice MTA_AT_CGSN_QRY_CNF_STRU */
    ID_MTA_AT_NCELL_MONITOR_SET_CNF     = 0x1016,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_QRY_CNF     = 0x1017,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_QRY_CNF_STRU        */
    ID_MTA_AT_NCELL_MONITOR_IND         = 0x1018,           /* _H2ASN_MsgChoice MTA_AT_NCELL_MONITOR_IND_STRU        */

    ID_MTA_AT_REFCLKFREQ_SET_CNF        = 0x1019,           /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_QRY_CNF        = 0x101A,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_QRY_CNF_STRU */
    ID_MTA_AT_REFCLKFREQ_IND            = 0x101B,           /* _H2ASN_MsgChoice MTA_AT_REFCLKFREQ_IND_STRU */

    ID_MTA_AT_HANDLEDECT_SET_CNF        = 0x101C,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_SET_CNF_STRU */
    ID_MTA_AT_HANDLEDECT_QRY_CNF        = 0x101D,           /* _H2ASN_MsgChoice MTA_AT_HANDLEDECT_QRY_CNF_STRU */

    ID_MTA_AT_PS_TRANSFER_IND           = 0x101E,           /* _H2ASN_MsgChoice MTA_AT_PS_TRANSFER_IND_STRU */

    /* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
    ID_MTA_AT_ECID_SET_CNF              = 0x101F,           /* _H2ASN_MsgChoice MTA_AT_ECID_SET_CNF_STRU */
    /* Added by l00198894 for ����+ECID����, 2013-12-09, end */

    ID_MTA_AT_MIPICLK_QRY_CNF           = 0x1020,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_CNF_STRU */
    ID_MTA_AT_MIPICLK_INFO_IND          = 0x1021,           /* _H2ASN_MsgChoice MTA_AT_RF_LCD_MIPICLK_IND_STRU */

    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF     = 0x1022,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU */
    ID_MTA_AT_SET_DPDT_VALUE_CNF        = 0x1023,           /* _H2ASN_MsgChoice MTA_AT_SET_DPDT_VALUE_CNF_STRU */
    ID_MTA_AT_QRY_DPDT_VALUE_CNF        = 0x1024,           /* _H2ASN_MsgChoice MTA_AT_QRY_DPDT_VALUE_CNF_STRU */

    ID_MTA_AT_RRC_PROTECT_PS_CNF        = 0x1025,
    ID_MTA_AT_PHY_INIT_CNF              = 0x1026,

    ID_MTA_AT_SET_JAM_DETECT_CNF        = 0x1027,           /* _H2ASN_MsgChoice MTA_AT_SET_JAM_DETECT_CNF_STRU */
    ID_MTA_AT_JAM_DETECT_IND            = 0x1028,           /* _H2ASN_MsgChoice MTA_AT_JAM_DETECT_IND_STRU */

    ID_MTA_AT_SET_FREQ_LOCK_CNF         = 0x1029,           /* _H2ASN_MsgChoice MTA_AT_SET_FREQ_LOCK_CNF_STRU */

    ID_MTA_AT_SET_GSM_FREQLOCK_CNF      = 0x102A,           /* _H2ASN_MsgChoice MTA_AT_SET_GSM_FREQLOCK_CNF_STRU */

    ID_AT_MTA_SET_FEMCTRL_CNF           = 0x102B,

    ID_MTA_AT_XPASS_INFO_IND            = 0x102C,

    ID_MTA_AT_NVWRSECCTRL_SET_CNF       = 0x102D,

    ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF   = 0x102E,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_PREFERENCE_SET_CNF       = 0x102F,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF    = 0x1030,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU */
    ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF     = 0x1031,       /* _H2ASN_MsgChoice MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU */
    ID_MTA_AT_NETWORK_INFO_QRY_CNF          = 0x1032,       /* _H2ASN_MsgChoice MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU */
    ID_MTA_AT_EMBMS_STATUS_QRY_CNF          = 0x1033,       /* _H2ASN_MsgChoice MTA_AT_EMBMS_STATUS_QRY_CNF_STRU */
    ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF  = 0x1034,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_EVENT_IND        = 0x1035,       /* _H2ASN_MsgChoice MTA_AT_MBMS_SERVICE_EVENT_IND_STRU */
    ID_MTA_AT_LTE_LOW_POWER_SET_CNF         = 0x1036,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_INTEREST_LIST_SET_CNF         = 0x1037,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF    = 0x1038,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF = 0x1039,       /* _H2ASN_MsgChoice MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_SET_CNF         = 0x103A,       /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF         = 0x103B,       /* _H2ASN_MsgChoice MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU */

    ID_MTA_AT_SET_FR_CNF                = 0x103C,

    ID_MTA_AT_MEID_SET_CNF              = 0x103d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_RFICSSIRD_QRY_CNF         = 0x103e,

    ID_MTA_AT_MEID_QRY_CNF              = 0x103f,     /* _H2ASN_MsgChoice MTA_AT_MEID_QRY_CNF_STRU */

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_MTA_AT_SET_M2M_FREQLOCK_CNF      = 0x1040,           /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_CNF_STRU */
    ID_MTA_AT_QRY_M2M_FREQLOCK_CNF      = 0x1041,           /* _H2ASN_MsgChoice MTA_AT_QRY_FREQLOCK_CNF_STRU */
#endif

    ID_MTA_AT_TRANSMODE_QRY_CNF         = 0x1052,

    ID_MTA_AT_UE_CENTER_SET_CNF         = 0x1053,
    ID_MTA_AT_UE_CENTER_QRY_CNF         = 0x1054,     /* _H2ASN_MsgChoice MTA_AT_QRY_UE_CENTER_CNF_STRU */

    ID_MTA_AT_SET_NETMON_SCELL_CNF      = 0x1055,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */
    ID_MTA_AT_SET_NETMON_NCELL_CNF      = 0x1056,     /* _H2ASN_MsgChoice MTA_AT_NETMON_CELL_INFO_STRU */

    ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ = 0x1057, /* _H2ASN_MsgChoice AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU */
    ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF = 0x1058, /* _H2ASN_MsgChoice MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU */
    ID_MTA_AT_ANQUERY_QRY_CNF           = 0x1059,       /* _H2ASN_MsgChoice MTA_AT_ANTENNA_INFO_QRY_CNF_STRU */
    ID_MTA_AT_CSNR_QRY_CNF              = 0x105A,       /* _H2ASN_MsgChoice MTA_AT_CSNR_QRY_CNF_STRU */
    ID_MTA_AT_CSQLVL_QRY_CNF            = 0x105B,       /* _H2ASN_MsgChoice MTA_AT_CSQLVL_QRY_CNF_STRU */

    ID_MTA_AT_EVDO_SYS_EVENT_CNF        = 0x105c,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_EVDO_SIG_MASK_CNF         = 0x105d,     /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_EVDO_REVA_RLINK_INFO_IND  = 0x105e,
    ID_MTA_AT_EVDO_SIG_EXEVENT_IND      = 0x105f,

    ID_MTA_AT_XCPOSR_SET_CNF            = 0x1060,                               /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_XCPOSR_QRY_CNF            = 0x1061,                               /* _H2ASN_MsgChoice MTA_AT_QRY_XCPOSR_CNF_STRU */
    ID_MTA_AT_XCPOSRRPT_SET_CNF         = 0x1062,                               /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */
    ID_MTA_AT_XCPOSRRPT_QRY_CNF         = 0x1063,                               /* _H2ASN_MsgChoice MTA_AT_QRY_XCPOSRRPT_CNF_STRU */
    ID_MTA_AT_CLEAR_HISTORY_FREQ_CNF    = 0x1064,   /* _H2ASN_MsgChoice MTA_AT_RESULT_CNF_STRU */

    ID_MTA_AT_SET_SENSOR_CNF           = 0x1065,     /* _H2ASN_MsgChoice MTA_AT_SET_SENSOR_CNF_STRU */
    ID_MTA_AT_SET_SCREEN_CNF           = 0x1066,     /* _H2ASN_MsgChoice MTA_AT_SET_SCREEN_CNF_STRU */

    /* ���һ����Ϣ */
    ID_AT_MTA_MSG_TYPE_BUTT

};
typedef VOS_UINT32 AT_MTA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MTA_AT_RESULT_ENUM
 �ṹ˵��  : MTA��AT�ظ��Ľ����ö��
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
enum MTA_AT_RESULT_ENUM
{
    /* ��ATģ���Ӧ�ı�׼������ */
    MTA_AT_RESULT_NO_ERROR                      = 0x000000,                     /* ��Ϣ�������� */
    MTA_AT_RESULT_ERROR,                                                        /* ��Ϣ������� */
    MTA_AT_RESULT_INCORRECT_PARAMETERS,
    MTA_AT_RESULT_OPTION_TIMEOUT,

    /* Ԥ����ӦAT��׼��������� */

    /* װ���������д����� */
    MTA_AT_RESULT_DEVICE_ERROR_BASE             = 0x100000,
    MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL,                                     /* ���߼�Ȩʧ�� */
    MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL,                                    /* ǩ��У��ʧ�� */
    MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT,                                      /* �˿�������� */
    MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT,                              /* ����������� */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_LEN_ERROR,                               /* ����ų��ȴ��� */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_VALUE_ERROR,                             /* ���������� */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_TYPE_ERROR,                              /* ��������ʹ��� */
    MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL,                                  /* RSA����ʧ�� */
    MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL,                                  /* RSA����ʧ�� */
    MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL,                              /* ��ȡ�����ʧ��(crypto_rand) */
    MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL,                                    /* HUKд����� */
    MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR,                                       /* Flash���� */
    MTA_AT_RESULT_DEVICE_SEC_NV_ERROR,                                          /* NV��д���� */
    MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR,                                       /* �������� */


    /* ˽���������д����� */
    MTA_AT_RESULT_PRICMD_ERROR_BASE             = 0x200000,

    MTA_AT_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MTA_AT_CGPSCLOCK_ENUM
 �ṹ˵��  : RFоƬGPSʱ��״̬ö��
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*****************************************************************************/
enum MTA_AT_CGPSCLOCK_ENUM
{
    MTA_AT_CGPSCLOCK_STOP           = 0,
    MTA_AT_CGPSCLOCK_START,
    MTA_AT_CGPSCLOCK_BUTT
};
typedef VOS_UINT32 MTA_AT_CGPSCLOCK_ENUM_UINT32;


/*****************************************************************************
 ö����    : MTA_AT_CPOS_OPERATE_TYPE_ENUM
 �ṹ˵��  : +CPOS XML���������������ö��
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*****************************************************************************/
enum MTA_AT_CPOS_OPERATE_TYPE_ENUM
{
    MTA_AT_CPOS_SEND                = 0,
    MTA_AT_CPOS_CANCEL,
    MTA_AT_CPOS_BUTT
};
typedef VOS_UINT32 MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32;

/*****************************************************************************
ö����    : AT_MTA_PERS_CATEGORY_ENUM
ö��˵��  : ����������Category����

  1.��    ��   : 2012��9��18��
    ��    ��   : l00198894
    �޸�����   : STK�������Լ�DCM���󿪷���Ŀ����ö��
*****************************************************************************/
enum AT_MTA_PERS_CATEGORY_ENUM
{
    AT_MTA_PERS_CATEGORY_NETWORK                    = 0x00,                     /* Category: ���� */
    AT_MTA_PERS_CATEGORY_NETWORK_SUBSET             = 0x01,                     /* Category: ������ */
    AT_MTA_PERS_CATEGORY_SERVICE_PROVIDER           = 0x02,                     /* Category: ��SP */
    AT_MTA_PERS_CATEGORY_CORPORATE                  = 0x03,                     /* Category: ������ */
    AT_MTA_PERS_CATEGORY_SIM_USIM                   = 0x04,                     /* Category: ��(U)SIM�� */

    AT_MTA_PERS_CATEGORY_BUTT
};
typedef VOS_UINT8 AT_MTA_PERS_CATEGORY_ENUM_UINT8;

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
/*****************************************************************************
ö����    : AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
ö��˵��  : �����ϱ���������

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM
{
    AT_MTA_RPT_GENERAL_CONTROL_NO_REPORT      = 0x00,                           /* ��ֹ���е������ϱ� */
    AT_MTA_RPT_GENERAL_CONTROL_REPORT         = 0x01,                           /* �����е������ϱ� */
    AT_MTA_RPT_GENERAL_CONTROL_CUSTOM         = 0x02,                           /* ��BITλ���ƶ�Ӧ����������ϱ� */

    AT_MTA_RPT_GENERAL_CONTROL_BUTT
};
typedef VOS_UINT8 AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : AT_MTA_RPT_SET_TYPE_ENUM
ö��˵��  : �����ϱ���������

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_MTA_RPT_SET_TYPE_ENUM
{
    AT_MTA_SET_MODE_RPT_TYPE            = 0,                                 /* Category: ����ģʽ�仯�Ƿ������ϱ� */
    AT_MTA_SET_SRVST_RPT_TYPE,
    AT_MTA_SET_RSSI_RPT_TYPE,
    AT_MTA_SET_TIME_RPT_TYPE,
    AT_MTA_SET_CTZR_RPT_TYPE,
    AT_MTA_SET_DSFLOWRPT_RPT_TYPE,
    AT_MTA_SET_SIMST_RPT_TYPE,
    AT_MTA_SET_CREG_RPT_TYPE,
    AT_MTA_SET_CGREG_RPT_TYPE,
    AT_MTA_SET_CEREG_RPT_TYPE,
    AT_MTA_SET_CSID_RPT_TYPE,
    AT_MTA_SET_CLOCINFO_RPT_TYPE,
    AT_MTA_SET_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_SET_TYPE_ENUM_UINT32;

/*****************************************************************************
ö����    : AT_MTA_RPT_QRY_TYPE_ENUM
ö��˵��  : �����ϱ���������

  1.��    ��   : 2013��4��10��
    ��    ��   : l00167671
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_MTA_RPT_QRY_TYPE_ENUM
{
    AT_MTA_QRY_TIME_RPT_TYPE = 0,
    AT_MTA_QRY_CTZR_RPT_TYPE,
    AT_MTA_QRY_CSSN_RPT_TYPE,
    AT_MTA_QRY_CUSD_RPT_TYPE,
    AT_MTA_QRY_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RPT_QRY_TYPE_ENUM_UINT32;

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

/*****************************************************************************
 ö����    : AT_MTA_CMD_RPT_FLG_ENUM
 �ṹ˵��  : AT�����ϱ����ر�־ö��

  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
enum AT_MTA_CMD_RPT_FLG_ENUM
{
    AT_MTA_CMD_RPT_FLG_OFF              = 0,                        /* AT��������ϱ� */
    AT_MTA_CMD_RPT_FLG_ON,                                          /* AT���������ϱ� */
    AT_MTA_CMD_RPT_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RPT_FLG_ENUM_UINT8;
/*****************************************************************************
 ö����    : AT_MTA_CMD_CLEAR_FREQ_FLG_ENUM
 �ṹ˵��  : �����ʷƵ����Ϣö��

  1.��    ��   : 2016��2��4��
    ��    ��   : y00358807
    �޸�����   :
*****************************************************************************/
enum AT_MTA_CLEAR_FREQ_FLG_ENUM
{
    AT_MTA_CLEAR_FREQ_FLG_NOT_CSG_HISTORY_FREQ              = 0,                /* �����CSG��ʷƵ�� */
    AT_MTA_CLEAR_FREQ_FLG_CSG_HISTORY_FREQ,                                     /* ���CSG��ʷƵ�� */
    AT_MTA_CLEAR_FREQ_FLG_ALL_FREQ,                                         /* ���������ʷƵ�� */
    AT_MTA_CLEAR_FREQ_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CLEAR_FREQ_FLG_ENUM_UINT8;


/*****************************************************************************
 ö����    : AT_MTA_CMD_RATMODE_ENUM
 �ṹ˵��  : AT���������ģʽRatModeö��

  1.��    ��   : 2014��04��8��
    ��    ��   : g00261581
    �޸�����   : �½�
*****************************************************************************/
enum AT_MTA_CMD_RATMODE_ENUM
{
    AT_MTA_CMD_RATMODE_GSM              = 0,
    AT_MTA_CMD_RATMODE_WCDMA,
    AT_MTA_CMD_RATMODE_LTE,
    AT_MTA_CMD_RATMODE_TD,
    AT_MTA_CMD_RATMODE_CDMA,
    AT_MTA_CMD_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_CMD_RATMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MTA_AT_JAM_RESULT_ENUM
 �ṹ˵��  : JAM DETECT REPORT�ϱ����ö��

  1.��    ��   : 2014��05��5��
    ��    ��   : g00261581
    �޸�����   : �½�
*****************************************************************************/
enum MTA_AT_JAM_RESULT_ENUM
{
    MTA_AT_JAM_RESULT_JAM_DISAPPEARED        = 0x00,                            /* ״̬�����޸��� */
    MTA_AT_JAM_RESULT_JAM_DISCOVERED,                                           /* ���Ŵ��� */

    MTA_AT_JAM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_JAM_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : AT_MTA_FREQLOCK_RATMODE_ENUM
 �ṹ˵��  : ATģ����MTA֮��Ľ���ģʽö��

  1.��    ��   : 2014��06��11��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
enum AT_MTA_FREQLOCK_RATMODE_ENUM
{
    AT_MTA_FREQLOCK_RATMODE_GSM         = 0x01,
    AT_MTA_FREQLOCK_RATMODE_WCDMA,
    AT_MTA_FREQLOCK_RATMODE_LTE,
    AT_MTA_FREQLOCK_RATMODE_CDMA1X,
    AT_MTA_FREQLOCK_RATMODE_TD,
    AT_MTA_FREQLOCK_RATMODE_WIMAX,
    AT_MTA_FREQLOCK_RATMODE_EVDO,

    AT_MTA_FREQLOCK_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_GSM_BAND_ENUM
 �ṹ˵��  : ATģ����MTA֮���BANDֵö��

  1.��    ��   : 2014��06��11��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
enum AT_MTA_GSM_BAND_ENUM
{
    AT_MTA_GSM_BAND_850                 = 0x00,
    AT_MTA_GSM_BAND_900,
    AT_MTA_GSM_BAND_1800,
    AT_MTA_GSM_BAND_1900,

    AT_MTA_GSM_BAND_BUTT
};
typedef VOS_UINT16 AT_MTA_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
 ö����    : AT_MTA_CFG_ENUM
 �ṹ˵��  : ʹ��/ȥʹ��ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum AT_MTA_CFG_ENUM
{
    AT_MTA_CFG_DISABLE                  = 0,
    AT_MTA_CFG_ENABLE                   = 1,
    AT_MTA_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_CFG_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
 �ṹ˵��  : MBMS Service״̬����ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum AT_MTA_MBMS_SERVICE_STATE_SET_ENUM
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ACTIVE       = 0,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE     = 1,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL = 2,
    AT_MTA_MBMS_SERVICE_STATE_SET_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_MBMS_CAST_MODE_ENUM
 �ṹ˵��  : MBMS�㲥ģʽ�ǵ���/�鲥ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum AT_MTA_MBMS_CAST_MODE_ENUM
{
    AT_MTA_MBMS_CAST_MODE_UNICAST       = 0,
    AT_MTA_MBMS_CAST_MODE_MULTICAST     = 1,
    AT_MTA_MBMS_CAST_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_CAST_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
 �ṹ˵��  : EMBMS ����״̬ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM
{
    MTA_AT_EMBMS_FUNTIONALITY_OFF       = 0,
    MTA_AT_EMBMS_FUNTIONALITY_ON        = 1,
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_BUTT
};
typedef VOS_UINT8 MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : MTA_AT_MBMS_SERVICE_EVENT_ENUM
 �ṹ˵��  : MBMS ����״̬�¼�ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum MTA_AT_MBMS_SERVICE_EVENT_ENUM
{
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_CHANGE       = 0,
    MTA_AT_MBMS_SERVICE_EVENT_NO_SERVICE           = 1,
    MTA_AT_MBMS_SERVICE_EVENT_ONLY_UNICAST         = 2,
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_AVAILABLE    = 3,
    MTA_AT_MBMS_SERVICE_EVENT_BUTT
};
typedef VOS_UINT8 MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_COEX_BW_TYPE_ENUM
 ö��˵��  : LTE&WIFI�������ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum AT_MTA_COEX_BW_TYPE_ENUM
{
    AT_MTA_COEX_BAND_WIDTH_6RB          = 0,                                    /* ���1.4M */
    AT_MTA_COEX_BAND_WIDTH_15RB         = 1,                                    /* ���3M */
    AT_MTA_COEX_BAND_WIDTH_25RB         = 2,                                    /* ���5M */
    AT_MTA_COEX_BAND_WIDTH_50RB         = 3,                                    /* ���10M */
    AT_MTA_COEX_BAND_WIDTH_75RB         = 4,                                    /* ���15M */
    AT_MTA_COEX_BAND_WIDTH_100RB        = 5,                                    /* ���20M */
    AT_MTA_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_BW_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : AT_MTA_COEX_CFG_ENUM
 ö��˵��  : LTE&WIFI���淽������ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����

*****************************************************************************/
enum AT_MTA_COEX_CFG_ENUM
{
    AT_MTA_COEX_CFG_DISABLE             = 0,
    AT_MTA_COEX_CFG_ENABLE              = 1,
    AT_MTA_COEX_CFG_BUTT
};
typedef VOS_UINT16 AT_MTA_COEX_CFG_ENUM_UINT16;

/*****************************************************************************
 ö����    : AT_MTA_LTE_LOW_POWER_ENUM
 ö��˵��  : �͹���ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����

*****************************************************************************/
enum AT_MTA_LTE_LOW_POWER_ENUM
{
    AT_MTA_LTE_LOW_POWER_NORMAL         = 0,
    AT_MTA_LTE_LOW_POWER_LOW            = 1,
    AT_MTA_LTE_LOW_POWER_BUTT
};
typedef VOS_UINT8 AT_MTA_LTE_LOW_POWER_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_MBMS_PRIORITY_ENUM
 ö��˵��  : ��������ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����

*****************************************************************************/
enum AT_MTA_MBMS_PRIORITY_ENUM
{
    AT_MTA_MBMS_PRIORITY_UNICAST        = 0,
    AT_MTA_MBMS_PRIORITY_MBMS           = 1,
    AT_MTA_MBMS_PRIORITY_BUTT
};
typedef VOS_UINT8 AT_MTA_MBMS_PRIORITY_ENUM_UINT8;


enum AT_MTA_UE_CENTER_TYPE_ENUM
{
    AT_MTA_UE_CENTER_VOICE_CENTRIC                          = 0,
    AT_MTA_UE_CENTER_DATA_CENTRIC                           = 1,
    AT_MTA_UE_CENTER_BUTT
};
typedef VOS_UINT32 AT_MTA_UE_CENTER_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : AT_MTA_BODY_SAR_STATE_ENUM
 �ṹ˵��  : Body SAR ״̬ö��
 1.��    ��   : 2015��10��30��
   ��    ��   : w00316404
   �޸�����   : ����ö��(��Դ����A��C�˽���)
*****************************************************************************/
enum AT_MTA_BODY_SAR_STATE_ENUM
{
    AT_MTA_BODY_SAR_OFF                 = 0,                                    /* Body SAR���ܹر� */
    AT_MTA_BODY_SAR_ON,                                                         /* Body SAR���ܿ��� */
    AT_MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 AT_MTA_BODY_SAR_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_AT_REFCLOCK_STATUS_ENUM
 ö��˵��  : GPS�ο�ʱ������״̬ö��

 1.��    ��   : 2015��10��30��
   ��    ��   : w00316404
   �޸�����   : ����ö��(��Դ����A��C�˽���)
*****************************************************************************/
enum MTA_AT_REFCLOCK_STATUS_ENUM
{
    MTA_AT_REFCLOCK_UNLOCKED            = 0,                                    /* GPS�ο�ʱ��Ƶ�ʷ�����״̬ */
    MTA_AT_REFCLOCK_LOCKED,                                                     /* GPS�ο�ʱ��Ƶ������״̬ */
    MTA_AT_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 MTA_AT_REFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_AT_GPHY_XPASS_MODE_ENUM
 ö��˵��  : G XPASSģʽ

 1.��    ��   : 2015��10��30��
   ��    ��   : w00316404
   �޸�����   : ����ö��(��Դ����A��C�˽���)
*****************************************************************************/
enum MTA_AT_GPHY_XPASS_MODE_ENUM
{
    MTA_AT_GPHY_XPASS_MODE_DISABLE      = 0,                                    /* ��XPASSģʽ�����Ƹ��� */
    MTA_AT_GPHY_XPASS_MODE_ENABLE,                                              /* XPASSģʽ�����Ƹ��� */
    MTA_AT_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_AT_WPHY_HIGHWAY_MODE_ENUM
 ö��˵��  : W����ģʽ

 1.��    ��   : 2015��10��30��
   ��    ��   : w00316404
   �޸�����   : ����ö��(��Դ����A��C�˽���)
*****************************************************************************/
enum MTA_AT_WPHY_HIGHWAY_MODE_ENUM
{
    MTA_AT_WPHY_HIGHWAY_MODE_DISABLE    = 0,                                    /* W�Ǹ���ģʽ */
    MTA_AT_WPHY_HIGHWAY_MODE_ENABLE,                                            /* W����ģʽ */
    MTA_AT_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_AT_NETMON_GSM_STATE_ENUM
 �ṹ˵��  : network monitor ��ȡGSMfС����Ϣ״̬ö��

  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : �½�
*****************************************************************************/
enum MTA_AT_NETMON_GSM_STATE_ENUM
{
   MTA_AT_NETMON_GSM_STATE_INIT   = 0,
   MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO  = 1,
   MTA_AT_NETMON_GSM_STATTE_WAIT_TA  = 2,
   MTA_AT_NETMON_GSM_STATTE_BUTT
};

typedef VOS_UINT32 MTA_AT_NETMON_GSM_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MTA_AT_NETMON_CELL_INFO_RESULT_ENUM
 �ṹ˵��  : network monitor С����Ϣ��ѯ��ʽö��

  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : �½�
*****************************************************************************/

enum MTA_AT_NETMON_CELL_INFO_RAT_ENUM
{
    MTA_AT_NETMON_CELL_INFO_GSM         = 0,
    MTA_AT_NETMON_CELL_INFO_UTRAN_FDD   = 1,
    MTA_AT_NETMON_CELL_INFO_UTRAN_TDD   = 2,
    MTA_AT_NETMON_CELL_INFO_LTE         = 3,
    MTA_AT_NETMON_CELL_INFO_RAT_BUTT
};
typedef VOS_UINT32 MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32;


/*****************************************************************************
 ö����    : MTA_TAF_CTZR_TYPE
 �ṹ˵��  : CTZR�ϱ���ʽö��

  1.��    ��   : 2015��11��17��
    ��    ��   : h00360002
    �޸�����   : �½�
*****************************************************************************/

enum MTA_TAF_CTZR_TYPE
{
    MTA_TAF_CTZR_OFF            = 0x00,            /* CTZRȥʹ�� */
    MTA_TAF_CTZR_CTZV           = 0x01,            /* CTZR:CTZV */
    MTA_TAF_CTZR_CTZE           = 0x02,            /* CTZR:CTZE */
    MTA_TAF_CTZR_BUTT
};
typedef VOS_UINT32 MTA_TAF_CTZR_TYPE_ENUM_UINT32;

/*****************************************************************************
ö����    : AT_MTA_TYPE_ENUM
ö��˵��  : �����ϱ�ͨ������

  1.��    ��   : 2015��12��25��
    ��    ��   : C00299064
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_MTA_AFC_CLK_STATUS_ENUM
{
    AT_MTA_AFC_CLK_UNLOCKED           = 0,                                     /* AFC UNLOCKED */
    AT_MTA_AFC_CLK_LOCKED,                                                     /* AFC LOCKED */

    AT_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT32 AT_MTA_AFC_CLK_STATUS_ENUM_UINT32;

/*****************************************************************************
ö����    : AT_MTA_XCPOSR_CFG_ENUM
ö��˵��  : AT^XCPOSR��GPSоƬ֧��������渨����Ϣ������

  1.��    ��   : 2016��03��08��
    ��    ��   : h00360002
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_MTA_XCPOSR_CFG_ENUM
{
    AT_MTA_XCPOSR_CFG_DISABLE        = 0,                                       /* ��֧��������� */
    AT_MTA_XCPOSR_CFG_ENABLE,                                                   /* ֧��������� */
    AT_MTA_XCPOSR_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_XCPOSR_CFG_ENUM_UNIT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
  5 ��Ϣͷ����
*******************************s**********************************************/
/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
�ṹ��    : AT_MTA_MSG_STRU
�ṹ˵��  : ATģ����MTAģ������Ϣ�ṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* ��Ϣ�� */
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
} AT_MTA_MSG_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_CPOS_REQ_MSG_STRU
�ṹ˵��  : ����AT��+CPOS������Ϣ�ӽṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_CPOS_OPERATE_TYPE_ENUM_UINT32    enCposOpType;
    VOS_UINT32                              ulXmlLength;
    VOS_CHAR                                acXmlText[MTA_CPOS_XML_MAX_LEN];
} AT_MTA_CPOS_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_CPOS_CNF_STRU
�ṹ˵��  : ����AT��+CPOS�ظ���Ϣ�ӽṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ����ִ�н�� */
} MTA_AT_CPOS_CNF_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_CPOSR_IND_STRU
�ṹ˵��  : +CPOSR�����ϱ�����Ϣ�ṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    /* AT��MTA�ϱ���XML������󳤶�Ϊ1024��ͬʱ����Ԥ��һ���ֽڴ���ַ�����β�Ŀ��ַ� */
    VOS_CHAR                            acXmlText[MTA_CPOSR_XML_MAX_LEN + 1];
    VOS_UINT8                           aucRsv[3];
} MTA_AT_CPOSR_IND_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_XCPOSRRPT_IND_STRU
�ṹ˵��  : ^XCPOSRRPT�����ϱ�����Ϣ�ṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulClearFlg;
} MTA_AT_XCPOSRRPT_IND_STRU;

/*****************************************************************************
�ṹ��    : AT_MTA_CGPSCLOCK_REQ_STRU
�ṹ˵��  : AT^CGPSCLOCK�Ļظ���Ϣ�ṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_CGPSCLOCK_ENUM_UINT32        enGpsClockState;                        /* RFоƬGPSʱ��״̬ */
} AT_MTA_CGPSCLOCK_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_CGPSCLOCK_CNF_STRU
�ṹ˵��  : AT^CGPSCLOCK�Ļظ���Ϣ�ṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ����ִ�н�� */
} MTA_AT_CGPSCLOCK_CNF_STRU;

/*****************************************************************************
�ṹ��    : AT_MTA_APSEC_REQ_STRU
�ṹ˵��  : AT^APSEC��������Ϣ�ṹ
1.��    ��  : 2012��08��28��
  ��    ��  : l00198894
  �޸�����  : ISDB ��ȫ�洢��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSPLen;
    VOS_UINT8                           aucSecPacket[MTA_SEC_PACKET_MAX_LEN];
} AT_MTA_APSEC_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_APSEC_CNF_STRU
�ṹ˵��  : AT^APSEC�Ļظ���Ϣ�ṹ
1.��    ��  : 2012��08��28��
  ��    ��  : l00198894
  �޸�����  : ISDB ��ȫ�洢��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ����ִ�н�� */
    VOS_UINT32                          ulSPLen;
    VOS_UINT8                           aucSecPacket[MTA_SEC_PACKET_MAX_LEN];
} MTA_AT_APSEC_CNF_STRU;

/*****************************************************************************
�ṹ��    : AT_MTA_SIMLOCKUNLOCK_REQ_STRU
�ṹ˵��  : AT^SIMLOCKUNLOCK��������Ϣ�ṹ
1.��    ��  : 2012��09��18��
  ��    ��  : l00198894
  �޸�����  : STK�������Լ�DCM���󿪷���Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    AT_MTA_PERS_CATEGORY_ENUM_UINT8     enCategory;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPassword[MTA_SIMLOCK_PASSWORD_LEN];
} AT_MTA_SIMLOCKUNLOCK_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_SIMLOCKUNLOCK_CNF_STRU
�ṹ˵��  : AT^SIMLOCKUNLOCK�Ļظ���Ϣ�ṹ
1.��    ��  : 2012��09��18��
  ��    ��  : l00198894
  �޸�����  : STK�������Լ�DCM���󿪷���Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ����ִ�н�� */
} MTA_AT_SIMLOCKUNLOCK_CNF_STRU;


/*****************************************************************************
 �ṹ��    : AT_MTA_QRY_NMR_REQ_STRU
 �ṹ˵��  : AT��ȡNMR����Ϣ����ṹ

  1.��    ��   : 2012��11��23��
    ��    ��   : z00161729
    �޸�����   : NMR�����ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRatType;
    VOS_UINT8                           aucReserve[3];                          /* Ԥ������ʹ�� */
}AT_MTA_QRY_NMR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_QRY_NMR_CNF_STRU
 �ṹ˵��  : mta�ظ�atģ��nmr��ѯ����ӿڽṹ

  1.��    ��   : 2012��11��23��
    ��    ��   : z00161729
    �޸�����   : NMR�����ṹ

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32         enResult;
    VOS_UINT8                         ucTotalIndex;
    VOS_UINT8                         ucCurrIndex;
    VOS_UINT16                        usNMRLen;                                 /* NMR���ݳ��� */
    VOS_UINT8                         aucNMRData[4];                            /* NMR�����׵�ַ */
}MTA_AT_QRY_NMR_CNF_STRU;



/*****************************************************************************
 �ṹ��    : AT_MTA_RESEL_OFFSET_CFG_SET_REQ_STRU
 �ṹ˵��  : AT��MTA����WLTHRESHOLDCFG����ѡ����
  1.��    ��   : 2012��12��10��
    ��    ��   : t00212959
    �޸�����   : WLTHRESHOLDCFG�����ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucOffsetFlg;                    /* 0:������1:����*/
    VOS_UINT8                                   aucReserve[3];                  /* Ԥ������ʹ�� */
}AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU
 �ṹ˵��  : AS�����������

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM];
}AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU
 �ṹ˵��  : WAS��������ؽ��

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM];
}MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU
 �ṹ˵��  : WAS��������ؽ����Ϣ�ṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_AUTOTEST_QRY_RSLT_STRU   stWrrAutoTestRslt;
} MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_CELLINFO_STRU
 �ṹ˵��  : С����Ϣ�ṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usCellFreq;
    VOS_UINT16                      usPrimaryScramCode;
    VOS_INT16                       sCpichRscp;
    VOS_INT16                       sCpichEcN0;

}MTA_AT_WRR_CELLINFO_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_CELLINFO_RSLT_STRU
 �ṹ˵��  : WRR�ظ�MTAС����Ϣ��ѯ�ṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
     VOS_UINT32                     ulCellNum;
     MTA_AT_WRR_CELLINFO_STRU       astWCellInfo[MTA_AT_WRR_MAX_NCELL_NUM];         /*���֧��W 8�������Ĳ�ѯ*/

} MTA_AT_WRR_CELLINFO_RSLT_STRU;
/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_CELLINFO_QRY_CNF_STRU
 �ṹ˵��  : WRR�ظ�MTAС����Ϣ��ѯ�ṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_CELLINFO_RSLT_STRU       stWrrCellInfo;
} MTA_AT_WRR_CELLINFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_MEANRPT_STRU
 �ṹ˵��  : ���������е��¼�+С��

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usEventId;                                  /*��Ӧ���¼�����*/
    VOS_UINT16                      usCellNum;
    VOS_UINT16                      ausPrimaryScramCode[MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM];
}MTA_AT_WRR_MEANRPT_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_MEANRPT_RSLT_STRU
 �ṹ˵��  : �Զ�������AT^MEANRPT,
             ��ѯ������10�β��������е��¼�+С��

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulRptNum;
    MTA_AT_WRR_MEANRPT_STRU         astMeanRptInfo[MTA_AT_WRR_MAX_MEANRPT_NUM];
}MTA_AT_WRR_MEANRPT_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_MEANRPT_QRY_CNF_STRU
 �ṹ˵��  : WRR��MTA�ظ�^MEANRPT�������Ϣ�ṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_MEANRPT_RSLT_STRU        stMeanRptRslt;
} MTA_AT_WRR_MEANRPT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_CSNR_QRY_CNF_STRU
 �ṹ˵��  : WRR��MTA�ظ�CSNR��ѯ�����MTA����ѯ�õ���Rscp EcNoֵ��������Rssi CellId
            ����һ���ϱ���AT

  1.��    ��   : 2015��12��24��
    ��    ��   : n00355355
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}MTA_AT_ANTENNA_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_FREQLOCK_CTRL_STRU
 �ṹ˵��  : WAS��Ƶ���ƽṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFreqLockEnable;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLockedFreq;
} MTA_AT_WRR_FREQLOCK_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_FREQLOCK_SET_CNF_STRU
 �ṹ˵��  : MTA��AT�ص���Ƶ���ƽṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU
 �ṹ˵��  : MTA��AT�ص���Ƶ���ƽṹ

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    MTA_AT_WRR_FREQLOCK_CTRL_STRU       stFreqLockInfo;
} MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU
 �ṹ˵��  : WRR��MTA�ϱ�version���ý��

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU
 �ṹ˵��  : WRR��MTA�ϱ�version��ѯ���

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRrcVersion;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_CELLSRH_SET_CNF_STRU
 �ṹ˵��  : WRR��MTA�ϱ�cellsrh���ý��

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
} MTA_AT_WRR_CELLSRH_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_WRR_CELLSRH_QRY_CNF_STRU
 �ṹ˵��  : WRR��MTA�ϱ�cellsrh��ѯ���

  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCellSearchType;
    VOS_UINT8                           aucReserve[3];
} MTA_AT_WRR_CELLSRH_QRY_CNF_STRU;

/*****************************************************************************
�ṹ��    : AT_MMA_ANQUERY_2G_3G_PARA_STRU
�ṹ˵��  : AT^ANQUERY��ѯ������2G/3G����ϱ��ṹ
  1.��    ��   : 2016��1��12��
    ��    ��   : n00355355
    �޸�����   : ������
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucRssi;                                 /* Rssi, GU��ʹ��*/
    VOS_UINT8                           aucReserve[3];

}AT_MTA_ANQUERY_2G_3G_PARA_STRU;

/*****************************************************************************
�ṹ��    : AT_MMA_ANQUERY_4G_PARA_STRU
�ṹ˵��  : AT^ANQUERY��ѯ������LTE����ϱ��ṹ

  1.��    ��   : 2016��1��12��
    ��    ��   : n00355355
    �޸�����   : ������
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sRsrp;                                  /* ��Χ��(-141,-44), 99Ϊ��Ч */
    VOS_INT16                           sRsrq;                                  /* ��Χ��(-40, -6) , 99Ϊ��Ч */
    VOS_INT16                           sRssi;                                  /* Rssi, LTE��ʹ��*/
    VOS_UINT8                           aucReserve[2];
}AT_MTA_ANQUERY_4G_PARA_STRU;

/*****************************************************************************
�ṹ��    : AT_MMA_ANQUERY_PARA_STRU
�ṹ˵��  : AT^ANQUERY��ѯ�����Ľ���ϱ��ṹ
  1.��    ��   : 2016��1��12��
    ��    ��   : n00355355
    �޸�����   : ������
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               enServiceSysMode;                       /* ָʾ�ϱ�ģʽ*/
    VOS_UINT8                               aucReserve[3];
    union
    {
        AT_MTA_ANQUERY_2G_3G_PARA_STRU      st2G3GCellSignInfo;                     /* Rssi, GU��ʹ��*/
        AT_MTA_ANQUERY_4G_PARA_STRU         st4GCellSignInfo;                       /* Rssi, LTE��ʹ��*/
    }u;
}AT_MTA_ANQUERY_PARA_STRU;

/*****************************************************************************
�ṹ��    : MMA_AT_ANTENNA_INFO_QRY_CNF_STRU
�ṹ˵��  : Antenna Info qry cnf stru

  1.��    ��   : 2015��12��23��
    ��    ��   : n00355355
    �޸�����   : �½�
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ������� */
    AT_MTA_ANQUERY_PARA_STRU            stAntennaInfo;
}MTA_AT_ANTENNA_INFO_QRY_CNF_STRU;

/*****************************************************************************
�ṹ��    : AT_MMA_CSNR_PARA_STRU
�ṹ˵��  : AT+CSNR��ѯ�����Ľ���ϱ��ṹ

  1.��    ��   : 2016��1��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}AT_MTA_CSNR_PARA_STRU;

/*****************************************************************************
�ṹ��    : MMA_AT_ANTENNA_INFO_QRY_CNF_STRU
�ṹ˵��  : Csnr Info qry cnf stru

  1.��    ��   : 2015��12��23��
    ��    ��   : n00355355
    �޸�����   : �½�
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ������� */
    AT_MTA_CSNR_PARA_STRU              stCsnrPara;
}MTA_AT_CSNR_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MMA_CSQLVL_PARA_STRU
 �ṹ˵��  : CSQLVL��ѯ�����Ľ���ϱ��ṹ
             ����RSCP �ȼ���RSCP �ľ���ֵ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRscp;                                 /* RSCP �ȼ� */
    VOS_UINT16                          usLevel;                                /* RSCP �ľ���ֵ */
}AT_MTA_CSQLVL_PARA_STRU;

/*****************************************************************************
�ṹ��     : AT_MMA_CSQLVLEXT_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSQLVLEX��ѯ�����Ľ���ϱ��ṹ
             ����CSQLVLEX��ѯ��ȡ�����źŸ����ͱ��������ʰٷֱȣ���ǰ�汾��֧��BER��ѯ����99

  1.��    ��   : 2016��1��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           enRssilv;                         /* CSQLVLEX��ѯ��ȡ�����źŸ��� */
    VOS_UINT8                           enBer;                            /* ���������ʰٷֱȣ���ʱ��֧��BER��ѯ����99*/
}AT_MTA_CSQLVLEXT_PARA_STRU;

/*****************************************************************************
�ṹ��    : MMA_AT_ANTENNA_INFO_QRY_CNF_STRU
�ṹ˵��  : CSQLVL Info qry cnf stru

  1.��    ��   : 2015��12��23��
    ��    ��   : n00355355
    �޸�����   : �½�
******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ������� */
    AT_MTA_CSQLVL_PARA_STRU             stCsqLvlPara;
    AT_MTA_CSQLVLEXT_PARA_STRU          stCsqLvlExtPara;
    VOS_UINT8                           aucReserved[2];
}MTA_AT_CSQLVL_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_BODY_SAR_SET_REQ_STRU
 �ṹ˵��  : AT��MTA����BODYSAR�������ò���
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : ^BODYSARON�����ṹ
*****************************************************************************/
typedef struct
{
    AT_MTA_BODY_SAR_STATE_ENUM_UINT16   enState;       /* Body SAR״̬ */
    VOS_UINT16                          usRsv;         /* ����λ */
    MTA_BODY_SAR_PARA_STRU              stBodySARPara; /* Body SAR�������޲��� */
}AT_MTA_BODY_SAR_SET_REQ_STRU;

/*******************************************************************************
 �ṹ��    : MTA_AT_RESULT_CNF_STRU
 �ṹ˵��  : AT������Ϣ��������Ļظ���Ϣ�ṹ��
 1.��    ��   : 2013��03��11��
   ��    ��   : z00214637
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;      /* ������� */
}MTA_AT_RESULT_CNF_STRU;

/*******************************************************************************
 �ṹ��    : AT_MTA_RESERVE_STRU
 �ṹ˵��  : AT��MTA��Ϣ�����ṹ��
 1.��    ��   : 2013��03��11��
   ��    ��   : z00214637
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4]; /* ����λ */
}AT_MTA_RESERVE_STRU;

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
/*****************************************************************************
 �ṹ��    : AT_MTA_CSSN_RPT_FLG_STRU
 �ṹ˵��  : CSSN�Ƿ������ϱ���ʶ�ṹ�壬����CSSI�Ƿ������ϱ���CSSU�Ƿ������ϱ�

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCssiRptFlg;                           /* ��ֹ��ʹ��+CSSI�Ĳ���ҵ��֪ͨ 0:���ϱ�;1:�ϱ� */
    VOS_UINT8                           ucCssuRptFlg;                           /* ��ֹ��ʹ��+CSSU�Ĳ���ҵ��֪ͨ 0:���ϱ�;1:�ϱ� */
} AT_MTA_CSSN_RPT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_CURC_SET_NOTIFY_STRU
 �ṹ˵��  : AT��MTA��������CURC����

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                  /* �����ϱ�ģʽ��0:�ر����е������ϱ���1:�����е������ϱ���2:����RptCfg����������Ӧ��bitλ�Ƿ������ϱ� */
    VOS_UINT8                                   aucReserve[3];                  /* �����ֶ� */
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];                   /* 64bit�����ϱ���ʶ */
} AT_MTA_CURC_SET_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_CURC_QRY_REQ_STRU
 �ṹ˵��  : AT��MTA���Ͳ�ѯCURC����

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];
} AT_MTA_CURC_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU
 �ṹ˵��  : AT��MTA���͵����������������ϱ�����

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_SET_TYPE_ENUM_UINT32     enReqType;                              /* �������� */

    union
    {
        VOS_UINT8                       ucModeRptFlg;                           /* mode�Ƿ������ϱ���ʶ 0:���ϱ���1:�ϱ� */
        VOS_UINT8                       ucSrvstRptFlg;                          /* service status�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucRssiRptFlg;                           /* rssi�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucTimeRptFlg;                           /* time�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucCtzrRptFlg;                           /* ctzr�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucDsFlowRptFlg;                         /* �����Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucSimstRptFlg;                          /* sim��״̬�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucCregRptFlg;                           /* cs��ע��״̬�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucCgregRptFlg;                          /* ps��ע��״̬�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucCeregRptFlg;                          /* Lע��״̬�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucCsidRptFlg;                           /* CSID�Ƿ������ϱ���ʶ */
        VOS_UINT8                       ucClocinfoRptFlg;                       /* CLOCINFO�Ƿ������ϱ���ʶ */
    }u;

    VOS_UINT8                           aucReserve[3];

 } AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU
 �ṹ˵��  : AT��MTA���Ͳ�ѯ�������������ϱ�����

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;
} AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_NCELL_MONITOR_SET_REQ_STRU
 �ṹ˵��  : AT��MTA����NCELLMONITOR��������

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           aucReserve[3];
} AT_MTA_NCELL_MONITOR_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU
 �ṹ˵��  : AT��MTA����CHISFREQ��������

  1.��    ��   : 2016��2��4��
    ��    ��   : y00358807
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_CLEAR_FREQ_FLG_ENUM_UINT8    enMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_CLEAR_HISTORY_FREQ_REQ_STRU;


/*****************************************************************************
 �ṹ��    : MTA_AT_CURC_QRY_CNF_STRU
 �ṹ˵��  : MTA��AT���Ͳ�ѯCURC�ظ�

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8     enCurcRptType;                          /* �����ϱ�ģʽ��0:�ر����е������ϱ���1:�����е������ϱ���2:����ReportCfg����������Ӧ��bitλ�Ƿ������ϱ� */
    VOS_UINT8                                   aucReserve[3];
    VOS_UINT8                                   aucRptCfg[AT_MTA_RPT_CFG_MAX_SIZE];  /* �����ϱ���ʶ */
} MTA_AT_CURC_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU
 �ṹ˵��  : MTA��AT���͵����������������ϱ��ظ�

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU
 �ṹ˵��  : MTA��AT���Ͳ�ѯ�������������ϱ��ظ�

  1.��    ��   : 2013��3��25��
    ��    ��   : s00217060
    �޸�����   : ����
  2.��    ��   : 2015��11��19��
    ��    ��   : h00360002
    �޸�����   : ctzr���ctze�ϱ�
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32     enReqType;

    union
    {
        VOS_UINT8                       ucTimeRptFlg;                           /* time�Ƿ������ϱ���ʶ */
        MTA_TAF_CTZR_TYPE_ENUM_UINT32   ucCtzrRptFlg;                           /* ctzr�Ƿ������ϱ���ʶ */
        AT_MTA_CSSN_RPT_FLG_STRU        stCssnRptFlg;                           /* cssn�Ƿ������ϱ���ʶ�ṹ�� */
        VOS_UINT8                       ucCusdRptFlg;                           /* cusd�Ƿ������ϱ���ʶ�ṹ�� */
    }u;

} MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU;

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */


/*******************************************************************************
 �ṹ��    : MTA_AT_CGSN_QRY_CNF_STRU
 �ṹ˵��  : ID_MTA_AT_CGSN_QRY_CNF��Ϣ
 1.��    ��   : 2013��05��25��
   ��    ��   : Y00213812
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImei[NV_ITEM_IMEI_SIZE]; /* IMEI���� */
}MTA_AT_CGSN_QRY_CNF_STRU;
/*****************************************************************************
 �ṹ��    : MTA_AT_NCELL_MONITOR_QRY_CNF_STRU
 �ṹ˵��  : MTA����AT�Ĳ�ѯ��ϵͳС���仯��Ϣ����������Ϣ�Ļظ�

  1.��    ��   : 2013��5��31��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucSwitch;
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[2];
} MTA_AT_NCELL_MONITOR_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_NCELL_MONITOR_IND_STRU
 �ṹ˵��  : MTA����AT����ϵͳС���仯�����ϱ���Ϣ

  1.��    ��   : 2013��5��31��
    ��    ��   : s00217060
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNcellState;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_NCELL_MONITOR_IND_STRU;


/*****************************************************************************
�ṹ��    : AT_MTA_REFCLKFREQ_SET_REQ_STRU
�ṹ˵��  : AT^REFCLKFREQ���������������Ϣ�ṹ

1.��    ��   : 2013��07��22��
  ��    ��   : l00198894
  �޸�����   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /* �����ϱ����ر�־ */
    VOS_UINT8                           aucReserved1[3];                        /* ����λ */
} AT_MTA_REFCLKFREQ_SET_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_REFCLKFREQ_QRY_CNF_STRU
�ṹ˵��  : AT^REFCLKFREQ��ѯ����Ļظ���Ϣ�ṹ

1.��    ��   : 2013��07��22��
  ��    ��   : l00198894
  �޸�����   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulFreq;                                 /* GPS�ο�ʱ�ӵ�Ƶ��ֵ����λHz */
    VOS_UINT32                          ulPrecision;                            /* ��ǰGPS�ο�ʱ�ӵľ��ȣ���λppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /* ʱ��Ƶ������״̬ */
    VOS_UINT8                           aucReserved1[2];                        /* ����λ */
} MTA_AT_REFCLKFREQ_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : AT_MTA_RFICSSIRD_REQ_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��10��29��
   ��    ��   : x00316382
   �޸�����   : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannelNo;                            /* ���ն˵�ַ */
    VOS_UINT16                          usRficReg;
}AT_MTA_RFICSSIRD_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_RFICSSIRD_CNF_STRU
�ṹ˵��  : AT^SSIRD��ѯ����Ļظ���Ϣ�ṹ

1.��    ��   : 2015��10��29��
  ��    ��   : x00316382
  �޸�����   : Rfic SSI Rd
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRegValue;                             /* �ظ��ļĴ�����ֵ */
} MTA_AT_RFICSSIRD_CNF_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_REFCLKFREQ_IND_STRU
�ṹ˵��  : GPS�ο�ʱ��״̬��Ϣ�����ϱ���Ϣ�ṹ

1.��    ��   : 2013��07��22��
  ��    ��   : l00198894
  �޸�����   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFreq;                                 /* GPS�ο�ʱ�ӵ�Ƶ��ֵ����λHz */
    VOS_UINT32                          ulPrecision;                            /* ��ǰGPS�ο�ʱ�ӵľ��ȣ���λppb */
    MTA_AT_REFCLOCK_STATUS_ENUM_UINT16  enStatus;                               /* ʱ��Ƶ������״̬ */
    VOS_UINT8                           aucReserved1[2];                        /* ����λ */
} MTA_AT_REFCLKFREQ_IND_STRU;


/*****************************************************************************
�ṹ��    : MTA_AT_HANDLEDECT_SET_CNF_STRU
�ṹ˵��  : ����������������ֳ�״̬��Ϣcnf��Ϣ

1.��    ��   : 2013��08��08��
  ��    ��   : m00217266
  �޸�����   : AP Sensor
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ������� */
} MTA_AT_HANDLEDECT_SET_CNF_STRU;

/*****************************************************************************
�ṹ��    : MTA_AT_HANDLEDECT_QRY_CNF_STRU
�ṹ˵��  : ��ѯ������������ֳ�״̬��Ϣcnf��Ϣ

1.��    ��   : 2013��08��08��
  ��    ��   : m00217266
  �޸�����   : AP Sensor
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHandle;                               /* ���������� */
    VOS_UINT16                          aucReserved1[1];
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ������� */
} MTA_AT_HANDLEDECT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_PS_TRANSFER_IND_STRU
 �ṹ˵��  : �ϱ�PS��Ǩ��ָʾ�ṹ��

  1.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : V9R1C50 SVLTE������ѡ��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCause;                                /* PS��Ǩ��ԭ��ֵ */
    VOS_UINT8                           aucReserved1[3];                        /* ����λ */
} MTA_AT_PS_TRANSFER_IND_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_RF_LCD_MIPICLK_IND_STRU
 �ṹ˵��  : �ϱ�MIPICLK�ṹ��

  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* �����ϱ�MIPICLKֵ */
    VOS_UINT8                           aucReserved1[2];                        /* ����λ */
} MTA_AT_RF_LCD_MIPICLK_IND_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_RF_LCD_MIPICLK_CNF_STRU
 �ṹ˵��  : �ϱ�MIPICLK�ṹ��

  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMipiClk;                              /* �����ϱ�MIPICLKֵ */
    VOS_UINT16                          usResult;
} MTA_AT_RF_LCD_MIPICLK_CNF_STRU;

/* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
/*******************************************************************************
 �ṹ��    : AT_MTA_ECID_SET_REQ_STRU
 �ṹ˵��  : AT��MTA����+ECID����������Ϣ�ṹ��

  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulVersion;                              /* ����汾�� */
}AT_MTA_ECID_SET_REQ_STRU;

/*******************************************************************************
 �ṹ��    : MTA_AT_ECID_SET_CNF_STRU
 �ṹ˵��  : AT��MTA����+ECID���ûظ���Ϣ�ṹ��

  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           aucCellInfoStr[4];                      /* ��ǿ��С����Ϣ�ַ��� */
}MTA_AT_ECID_SET_CNF_STRU;
/* Added by l00198894 for ����+ECID����, 2013-12-09, end */

/*****************************************************************************
 �ṹ��    : AT_MTA_RRC_PROTECT_PS_REQ_STRU
 �ṹ˵��  : AT��ȡPSPROTECTMODE����Ϣ����ṹ

  1.��    ��   : 2014��3��25��
    ��    ��   : y00176023
    �޸�����   : PSPROTECTMODE�����ṹ

*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enPsProtectFlg;
    VOS_UINT8                           aucReserve[3];                          /* Ԥ������ʹ�� */
}AT_MTA_RRC_PROTECT_PS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_RRC_PROTECT_PS_CNF_STRU
 �ṹ˵��  : AT��ȡPSPROTECTMODE����Ϣ����ṹ

  1.��    ��   : 2014��3��25��
    ��    ��   : y00176023
    �޸�����   : PSPROTECTMODE�����ṹ

*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* ���ظ�AT�Ľ�� */
}MTA_AT_RRC_PROTECT_PS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_PHY_INIT_CNF_STRU
 �ṹ˵��  : AT��ȡPHYINIT����Ϣ����ṹ

  1.��    ��   : 2014��3��25��
    ��    ��   : y00176023
    �޸�����   : PHYINIT�����ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[4];                          /* Ԥ������ʹ�� */
}AT_MTA_PHY_INIT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_PHY_INIT_CNF_STRU
 �ṹ˵��  : AT����������ʼ�������ظ�����Ϣ�ṹ

  1.��    ��   : 2014��3��26��
    ��    ��   : y00176023
    �޸�����   : PHYINIT�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                          /* ���ظ�AT�Ľ�� */
}MTA_AT_PHY_INIT_CNF_STRU;


/*****************************************************************************
 �ṹ��    : AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU
 �ṹ˵��  : AT����MTA������DPDT TEST FLAG����Ϣ�ṹ

  1.��    ��   : 2014��4��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_DPDT_VALUE_REQ_STRU
 �ṹ˵��  : AT����MTA������DPDT��ǰ����ʹ��״̬����Ϣ�ṹ

  1.��    ��   : 2014��4��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulDpdtValue;
} AT_MTA_SET_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_QRY_DPDT_VALUE_PARA_STRU
 �ṹ˵��  : AT����MTA�Ĳ�ѯDPDT VAlUE����Ϣ�ṹ

  1.��    ��   : 2014��4��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode;
    VOS_UINT8                           aucReserved[3];
} AT_MTA_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU
 �ṹ˵��  : MTA����AT������DPDTTEST Flag���ػظ���Ϣ�ṹ

  1.��    ��   : 2014��4��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_DPDT_VALUE_CNF_STRU
 �ṹ˵��  : MTA����AT������DPDT Value�ظ���Ϣ�ṹ

  1.��    ��   : 2014��4��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_QRY_DPDT_VALUE_CNF_STRU
 �ṹ˵��  : MTA����AT�Ļظ���ѯDPDT VAlUE����Ϣ�ṹ

  1.��    ��   : 2014��4��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDpdtValue;
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_JAM_DETECT_REQ_STRU
 �ṹ˵��  : AT����MTA������Jamming Dectection Report����Ϣ�ṹ

  1.��    ��   : 2014��5��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFlag;
    VOS_UINT8                           ucMethod;
    VOS_UINT8                           ucThreshold;
    VOS_UINT8                           ucFreqNum;
} AT_MTA_SET_JAM_DETECT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_JAM_DETECT_CNF_STRU
 �ṹ˵��  : MTA����AT������Jamming Dectection Report��Cnf��Ϣ�ṹ

  1.��    ��   : 2014��5��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_JAM_DETECT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_JAM_DETECT_IND_STRU
 �ṹ˵��  : MTA����AT��Jamming Dectection Report��Ind�ϱ���Ϣ�ṹ

  1.��    ��   : 2014��5��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_JAM_RESULT_ENUM_UINT32       enJamResult;
} MTA_AT_JAM_DETECT_IND_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_FREQ_LOCK_REQ_STRU
 �ṹ˵��  : AT����MTA��������Ƶ�������Ϣ�ṹ

  1.��    ��   : 2014��6��11��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* 1:��Ƶ���ܴ򿪣�0:���ܹر� */
    AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8  enRatMode;
    VOS_UINT16                          usLockedFreq;
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;
    VOS_UINT8                           aucReserved[2];
} AT_MTA_SET_FREQ_LOCK_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_FREQ_LOCK_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT������Ƶ�ظ��������Ϣ�ṹ

  1.��    ��   : 2014��6��11��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FREQ_LOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_GSM_FREQLOCK_REQ_STRU
 �ṹ˵��  : AT����MTA������Gģ��Ƶ�������Ϣ�ṹ

  1.��    ��   : 2014��08��05��
    ��    ��   : j00174725
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enableFlag;                             /* PS_TRUE:������PS_FALSE:ȥ���� */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
    VOS_UINT16                          usFreq;                                 /* Ƶ��ֵ */
    AT_MTA_GSM_BAND_ENUM_UINT16         enBand;                                 /* GSMƵ�� */
} AT_MTA_SET_GSM_FREQLOCK_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_GSM_FREQLOCK_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT����Gģ��Ƶ�ظ��������Ϣ�ṹ

  1.��    ��   : 2014��08��05��
    ��    ��   : j00174725
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_GSM_FREQLOCK_CNF_STRU;

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
/*****************************************************************************
 ö����    : AT_FREQLOCK_W_TYPE_ENUM
 �ṹ˵��  : FREQLOCK����W��ʽ����Ƶ����ö��
1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
enum AT_FREQLOCK_W_TYPE_ENUM
{
    AT_MTA_WCDMA_FREQLOCK_CMD_FREQ_ONLY         = 8,                            /* ��ӦCWAS��Ƶ���� */
    AT_MTA_WCDMA_FREQLOCK_CMD_COMBINED          = 9,                            /* ��ӦCWAS��Ƶ+�������� */
    AT_MTA_WCDMA_FREQLOCK_CMD_BUTT
};
typedef VOS_UINT8 AT_MTA_WCDMA_FREQLOCK_CMD_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_M2M_FREQLOCK_TYPE_ENUM
 �ṹ˵��  : FREQLOCK����W��ʽ����Ƶ����ö��
1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
enum AT_MTA_M2M_FREQLOCK_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY     = 1,                            /* ��ƵONLY���� */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_COMBINED = 2,                            /* ��Ƶ+������/����/����С��ID */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU
 �ṹ˵��  : AT����MTA������Gģ��Ƶ�������Ϣ�ṹ

  1.��    ��   : 2014��12��15��
    ��    ��   : z00214637
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFreq;                         /* Ƶ��ֵ */
    AT_MTA_GSM_BAND_ENUM_UINT16                 enBand;                         /* GSMƵ�� */
	VOS_UINT32									nReserve;						/* 8�ֽڶ���-������� */
} AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU
 �ṹ˵��  : AT����MTA������Wģ��Ƶ�������Ϣ�ṹ

1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /* ��Ƶ���� */
    VOS_UINT8                                   aucReserved[3];                 /* ����λ */
    VOS_UINT16                                  usFreq;                         /* Ƶ��ֵ */
    VOS_UINT16                                  usPsc;                          /* WCDMA������ */
}AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU
 �ṹ˵��  : AT����MTA������TDģ��Ƶ�������Ϣ�ṹ

1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /* ��Ƶ���� */
    VOS_UINT8                                   aucReserved[3];                 /* ����λ */
    VOS_UINT16                                  usFreq;                         /* Ƶ��ֵ */
    VOS_UINT16                                  usSc;                           /* TD-SCDMA���� */
}AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU
 �ṹ˵��  : AT����MTA������Wģ��Ƶ�������Ϣ�ṹ

1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_UINT8         ucFreqType;                     /* ��Ƶ���� */
    VOS_UINT8                                   aucReserved[3];                 /* ����λ */
    VOS_UINT16                                  usFreq;                         /* Ƶ��ֵ */
    VOS_UINT16                                  usPci;                          /* LTE����С��ID */
}AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU;

/*****************************************************************************
 ö����    : AT_FREQLOCK_FLAG_TYPE_ENUM
 �ṹ˵��  : FREQLOCK����FLAG��ʶ(�������ֿ���/�ر���Ƶ)ö��
1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
enum AT_FREQLOCK_FLAG_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_MODE_GSM            = 1,                                /* GSM��ʽ */
    AT_MTA_M2M_FREQLOCK_MODE_WCDMA          = 2,                                /* WCDMA��ʽ */
    AT_MTA_M2M_FREQLOCK_MODE_TDSCDMA        = 3,                                /* TD-SCDMA��ʽ */
    AT_MTA_M2M_FREQLOCK_MODE_LTE            = 4,                                /* LTE��ʽ */
    AT_MTA_M2M_FREQLOCK_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8
 �ṹ˵��  : FREQLOCK����FLAG��ʶ(�������ֿ���/�ر���Ƶ)ö��
1.��    ��  : 2014��10��21��
  ��    ��  : z00214637
  �޸�����  : �����ṹ
*****************************************************************************/
enum AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ENUM
{
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF       = 0,                                /* ��Ƶ�ر� */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ON        = 1,                                /* ��Ƶ���� */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_M2M_FREQLOCK_REQ_STRU
 �ṹ˵��  : AT���͸�MTA��������Ƶ������Ϣ�ṹ

  1.��    ��   : 2014��10��20��
    ��    ��   : z00214637
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_M2M_FREQLOCK_FLAG_ENUM_UINT8         enMode;                                 	/* ʹ�ܱ�ʶ */
    AT_MTA_M2M_FREQLOCK_MODE_ENUM_UINT8         ucMode;                                     /* ��Ƶ��ʽ */
    VOS_UINT8                                   aucReserved[6];                             /* ���� */
    AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU           stGFreqPara;                                /* Gģ��Ƶ��Ϣ�ṹ */
    AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU         stWFreqPara;                                /* Wģ��Ƶ��Ϣ�ṹ */
    AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU       stTDFreqPara;                               /* TDģ��Ƶ��Ϣ�ṹ */
    AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU           stLFreqPara;                                /* Lģ��Ƶ��Ϣ�ṹ */
} AT_MTA_SET_M2M_FREQLOCK_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_M2M_FREQLOCK_CNF_STRU
 �ṹ˵��  : MTA�ظ�AT��Ƶ���õĻظ���Ϣ�ṹ

  1.��    ��   : 2014��10��20��
    ��    ��   : z00214637
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           ulResult;
} MTA_AT_SET_M2M_FREQLOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_FREQLOCK_QRY_CNF_STRU
 �ṹ˵��  : MTA�ظ�AT��ѯFREQLOCK�������Ϣ�ṹ

  1.��    ��   : 2014��10��20��
    ��    ��   : z00214637
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucFreqState[MTA_FREQLOCK_MAX_MODE];     /* GUTLģʽ����Ƶ״̬ */
    AT_MTA_M2M_GSM_FREQLOCK_PARA_STRU           stGFreqLockInfo;                        /* GSM��Ƶ״̬��ѯ��� */
    AT_MTA_M2M_WCDMA_FREQLOCK_PARA_STRU         stWFreqLockInfo;                        /* WCDMA��Ƶ״̬��ѯ��� */
    AT_MTA_M2M_TDSCDMA_FREQLOCK_PARA_STRU       stTFreqLockInfo;                        /* TD-SCDMA��Ƶ״̬��ѯ��� */
    AT_MTA_M2M_LTE_FREQLOCK_PARA_STRU           stLFreqLockInfo;                        /* LTE��Ƶ״̬��ѯ��� */
} MTA_AT_QRY_M2M_FREQLOCK_CNF_STRU;
#endif


/*****************************************************************************
 �ṹ��    : MTA_AT_XPASS_INFO_IND_STRU
 �ṹ˵��  : MTA�����ϱ���XPASS��Ϣ����Ϣ�ṹ

  1.��    ��   : 2014��12��25��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_GPHY_XPASS_MODE_ENUM_UINT16            enGphyXpassMode;
    VOS_UINT16                                    usResev1;
    MTA_AT_WPHY_HIGHWAY_MODE_ENUM_UINT16          enWphyXpassMode;
    VOS_UINT16                                    usResev2;
} MTA_AT_XPASS_INFO_IND_STRU;
/*****************************************************************************
 �ṹ��    : AT_MTA_SET_FEMCTRL_REQ_STRU
 �ṹ˵��  : AT����MTA�����õ���gpio��mipi�ڵ���Ϣ�ṹ

  1.��    ��   : 2014��12��11��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulCtrlType;
    VOS_UINT32      ulPara1;
    VOS_UINT32      ulPara2;
    VOS_UINT32      ulPara3;
} AT_MTA_SET_FEMCTRL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_FEMCTRL_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT���õ���gpio��mipi�ڵ���Ϣ�ṹ

  1.��    ��   : 2014��12��11��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_FEMCTRL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_NVWRSECCTRL_SET_REQ_STRU
 �ṹ˵��  : AT����MTA������NVWR���ȫ���Ƶ���Ϣ�ṹ

  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSecType;                              /* ��ȫ�������� */
    VOS_UINT8                           ucSecStrFlg;                            /* �Ƿ�Я����ȫУ������ */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucSecString[AT_RSA_CIPHERTEXT_LEN];    /* ��ȫУ������ */
} AT_MTA_NVWRSECCTRL_SET_REQ_STRU;

/*******************************************************************************
 �ṹ��    : AT_MTA_SET_FR_REQ_STRU
 �ṹ˵��  : AT����MTA����FR����
 1.��    ��   : 2015��06��01��
   ��    ��   : wx270776
   �޸�����   : FR��̬�������
*******************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enActFrFlag;                    /* ����FR��־��0:������  1:���� */
    VOS_UINT8                                   aucRsv[3];                      /* ����λ */
}AT_MTA_SET_FR_REQ_STRU;

/*******************************************************************************
 �ṹ��    : MTA_AT_SET_FR_CNF_STRU
 �ṹ˵��  : MTA�ظ�AT��FR������Ӧ
 1.��    ��   : 2015��06��01��
   ��    ��   : wx270776
   �޸�����   : FR��̬�������
*******************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enRslt;                         /* FR���ü���� */
}MTA_AT_SET_FR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU
 �ṹ˵��  : AT����MTA������MBMS�������Բ�������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8               enCfg;                                  /* 0:ȥʹ�ܣ�1:ʹ�� */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
} AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU;


/*****************************************************************************
 �ṹ��    : AT_MTA_PLMN_ID_STRU
 �ṹ˵��  : PLMN ID�ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC, 3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC, 2 or 3 bytes */
} AT_MTA_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MBMS_TMGI_STRU
 �ṹ˵��  : TMGI�ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMbmsSerId;                            /* Service ID */
    AT_MTA_PLMN_ID_STRU                 stPlmnId;                               /* PLMN ID */
} AT_MTA_MBMS_TMGI_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU
 �ṹ˵��  : AT֪ͨMTA MBMS����״̬��������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_MBMS_SERVICE_STATE_SET_ENUM_UINT8    enStateSet;                     /* ״̬���� */
    VOS_UINT8                                   aucReserved[3];                 /* ����λ */
    VOS_UINT32                                  ulAreaId;                       /* Area ID */
    AT_MTA_MBMS_TMGI_STRU                       stTMGI;                         /* TMGI */
} AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU
 �ṹ˵��  : AT����MTA������MBMS�㲥ģʽΪ�������鲥��������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_MBMS_CAST_MODE_ENUM_UINT8    enCastMode;                             /* 0:����,1:�鲥 */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
} AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT��ѯSIB16����ʱ����

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          aulUTC[2];                              /* (0..549755813887) */
} MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT��ѯBSSI�ź�ǿ�Ƚ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT8                           ucBSSILevel;                            /* BSSI�ź�ǿ��,0xFF:��ʾBSSI�ź�ǿ����Ч */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
} MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT��ѯ������Ϣ���

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulCellId;                               /* С��ID */
} MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_EMBMS_STATUS_QRY_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT��ѯEMBMS����״̬���

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_ENUM_UINT8 enStatus;                       /* ����״̬ */
    VOS_UINT8                                   aucReserved[3];                 /* ����λ */
} MTA_AT_EMBMS_STATUS_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU
 �ṹ˵��  : AT����MTA������MBMS�����ϱ����ò�������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_CFG_ENUM_UINT8                       enCfg;                          /* 0:�ر�,1:�� */
    VOS_UINT8                                   aucReserved[3];                 /* ����λ */
} AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MBMS_SERVICE_EVENT_IND_STRU
 �ṹ˵��  : MTA����AT��MBMS�����¼������ϱ���Ϣ

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_MBMS_SERVICE_EVENT_ENUM_UINT8    enEvent;                            /* �����¼� */
    VOS_UINT8                               aucReserved[3];                     /* ����λ */
} MTA_AT_MBMS_SERVICE_EVENT_IND_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU
 �ṹ˵��  : AT����MTA�����õ͹��Ĳ�������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_LTE_LOW_POWER_ENUM_UINT8         enLteLowPowerFlg;                   /* 0: Normal;1: Low Power Consumption */
    VOS_UINT8                               aucReserved[3];                     /* ����λ */
} AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU
 �ṹ˵��  : AT����MTA������Interest�б��������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulFreqList[AT_MTA_INTEREST_FREQ_MAX_NUM];  /* Ƶ���б� */
    AT_MTA_MBMS_PRIORITY_ENUM_UINT8     enMbmsPriority;                             /* VOS_FALSE: ��������;VOS_TRUE: MBMS���� */
    VOS_UINT8                           aucReserved[3];                             /* ����λ */
} AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MBMS_AVL_SERVICE_STRU
 �ṹ˵��  : MBMS���÷���ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpSessionId  : 1;
    VOS_UINT32                          bitSpare        : 31;
    VOS_UINT32                          ulAreaId;                               /* Area ID */
    AT_MTA_MBMS_TMGI_STRU               stTMGI;                                 /* TMGI */
    VOS_UINT32                          ulSessionId;                            /* Session ID */
} MTA_AT_MBMS_AVL_SERVICE_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU
 �ṹ˵��  : MTA�ظ���AT��ѯ���÷����б�������

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
    VOS_UINT32                          ulAvlServiceNum;                                    /* ���÷�����,0:��ʾû�п��÷��� */
    MTA_AT_MBMS_AVL_SERVICE_STRU        astAvlServices[AT_MTA_MBMS_AVL_SERVICE_MAX_NUM];    /* ���÷����б� */
} MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_LRRC_COEX_PARA_STRU
 �ṹ˵��  : LTE&WIFI��������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_COEX_BW_TYPE_ENUM_UINT16             enCoexBWType;
    AT_MTA_COEX_CFG_ENUM_UINT16                 enCfg;
    VOS_UINT16                                  usTxBegin;
    VOS_UINT16                                  usTxEnd;
    VOS_INT16                                   sTxPower;
    VOS_UINT16                                  usRxBegin;
    VOS_UINT16                                  usRxEnd;
    VOS_UINT8                                   aucReserved[2];                 /* ����λ */
} AT_MTA_COEX_PARA_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU
 �ṹ˵��  : AT����MTA������LTE&WIFI������������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCoexParaNum;
    VOS_UINT16                          usCoexParaSize;
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU
 �ṹ˵��  : MTA����AT�Ĳ�ѯLTE&WIFI������������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_COEX_PARA_STRU               astCoexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_MEID_SET_REQ_STRU
 �ṹ˵��  : AT^MEID��������ṹ

 �޸���ʷ      :
  1.��    ��   : 2015��07��23��
    ��    ��   : z00316370
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMeid[AT_MTA_MEID_DATA_LEN];
    VOS_UINT8                           aucRsv[1];
}AT_MTA_MEID_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_MEID_QRY_CNF_STRU
 �ṹ˵��  : AT^MEID��ѯ����ṹ

 �޸���ʷ      :
  1.��    ��   : 2015��12��18��
    ��    ��   : z00316370
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ��ѯ�������*/
    VOS_UINT8                           aucEFRUIMID[MTA_AT_EFRUIMID_OCTET_LEN_EIGHT];
}MTA_AT_MEID_QRY_CNF_STRU;




/*****************************************************************************
 �ṹ��    : MTA_AT_TRANSMODE_QRY_CNF_STRU
 �ṹ˵��  : MTA����AT��ѯ����ģʽ�������Ϣ�ṹ

  1.��    ��   : 2015��07��30��
    ��    ��   : lwx277467
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ��ѯ�������*/
    VOS_UINT8                           ucTransMode;                            /* ����ģʽ*/
    VOS_UINT8                           aucReserved[3];                         /*����λ*/
} MTA_AT_TRANSMODE_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_UE_CENTER_REQ_STRU
 �ṹ˵��  : AT����MTA����UE Mode����Ϣ�ṹ

  1.��    ��   : 2015��09��07��
    ��    ��   : lwx277467
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UEģʽ*/
} AT_MTA_SET_UE_CENTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_SET_UE_CENTER_CNF_STRU
 �ṹ˵��  : MTA����AT����UE Mode�������Ϣ�ṹ

  1.��    ��   : 2015��09��07��
    ��    ��   : lwx277467
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ��ѯ�������*/
} MTA_AT_SET_UE_CENTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_QRY_UE_CENTER_CNF_STRU
 �ṹ˵��  : MTA����AT��ѯUEģʽ�������Ϣ�ṹ

  1.��    ��   : 2015��09��07��
    ��    ��   : lwx277467
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ��ѯ�������*/
    AT_MTA_UE_CENTER_TYPE_ENUM_UINT32   enUeCenter;                             /*UEģʽ*/
} MTA_AT_QRY_UE_CENTER_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MTA_AT_NETMON_GSM_SCELL_INFO_STRU
 �ṹ˵��  : MTA�ظ���AT network monitorС����ѯ���

  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpTa     :1;
    VOS_UINT32                          bitOpSpare  :31;
    GRR_MTA_NETMON_SCELL_INFO_STRU      stSCellInfo;
    VOS_UINT16                          usTa;
    VOS_UINT8                           aucReserved[2];
}MTA_AT_NETMON_GSM_SCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_NETMON_SCELLL_INFO_UN
 �ṹ˵��  : MTA ����С��������ṹ

  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ����
*****************************************************************************/
typedef union
{
    MTA_AT_NETMON_GSM_SCELL_INFO_STRU       stGsmSCellInfo;    /* GSM����С����Ϣ */
    RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU    stUtranSCellInfo;  /* WCDMA����С����Ϣ */
    MTA_NETMON_EUTRAN_SCELL_INFO_STRU       stLteSCellInfo;    /* LTE����С����Ϣ*/
}MTA_AT_NETMON_SCELL_INFO_UN;

/*****************************************************************************
 �ṹ��    : MTA_AT_NETMON_GSM_SCELL_INFO_STRU
 �ṹ˵��  : MTA�ظ���AT network monitorС����ѯ���

  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32                   enResult;               /* ��ѯ����Ƿ�ɹ� */
    MTA_NETMON_CELL_TYPE_ENUM_UINT32            enCellType;             /* 0:��ѯ����С����1:��ѯ���� */
    RRC_MTA_NETMON_NCELL_INFO_STRU              stNCellInfo;            /*������Ϣ*/
    MTA_AT_NETMON_CELL_INFO_RAT_ENUM_UINT32     enRatType;              /* ����С���Ľ��뼼������ */
    MTA_AT_NETMON_SCELL_INFO_UN                 unSCellInfo;
} MTA_AT_NETMON_CELL_INFO_STRU;



/*****************************************************************************
 �ṹ��    : AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU
 �ṹ˵��  :

  1.��    ��   : 2015��12��25��
    ��    ��   : C00299064
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReserveValue;
} AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU
 �ṹ˵��  :

  1.��    ��   : 2015��12��25��
    ��    ��   : C00299064
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    AT_MTA_AFC_CLK_STATUS_ENUM_UINT32   enStatus;
    VOS_INT32                           lDeviation;                                 /* Ƶƫ */

    /* �¶ȷ�Χ */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /* ����ʽϵ�� */
    VOS_UINT32                          aulCoeffMantissa[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3β�� */
    VOS_UINT16                          ausCoeffExponent[AT_MTA_GPS_XO_COEF_NUM];  /* a0,a1,a2,a3ָ�� */

} MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU;


/*****************************************************************************
 �ṹ��    : AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU
 �ṹ˵��  : AT^DOSYSEVENT��������ṹ

 �޸���ʷ      :
  1.��    ��   : 2015��12��30��
    ��    ��   : z00316370
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDoSysEvent;
}AT_MTA_EVDO_SYS_EVENT_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU
 �ṹ˵��  : AT^DOSIGMASK��������ṹ

 �޸���ʷ      :
  1.��    ��   : 2015��12��30��
    ��    ��   : z00316370
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDoSigMask;
}AT_MTA_EVDO_SIG_MASK_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_EVDO_REVA_RLINK_INFO_IND_STRU
 �ṹ˵��  : MTA����AT��EVDO REVA RLING�ϱ���Ϣ�ṹ

  1.��    ��   : 2014��5��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} MTA_AT_EVDO_REVA_RLINK_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_EVDO_SIG_EXEVENT_IND_STRU
 �ṹ˵��  : MTA����AT��EVDO SIG EX EVENT�ϱ���Ϣ�ṹ

  1.��    ��   : 2014��5��04��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulParaLen;
    VOS_UINT8                           aucContent[4];
} MTA_AT_EVDO_SIG_EXEVENT_IND_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_XCPOSR_REQ_STRU
 �ṹ˵��  :

  1.��    ��   : 2016��03��08��
    ��    ��   : h00360002
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_MTA_XCPOSR_CFG_ENUM_UNIT8        enXcposrEnableCfg;                            /* GPSоƬ�Ƿ�֧�����������λ��Ϣ���ϵ翪��Ĭ��Ϊ��֧�� */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_SET_XCPOSR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_QRY_XCPOSR_CNF_STRU
 �ṹ˵��  :

  1.��    ��   : 2016��03��08��
    ��    ��   : h00360002
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ����ִ�н�� */
    AT_MTA_XCPOSR_CFG_ENUM_UNIT8        enXcposrEnableCfg;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_XCPOSR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_MTA_SET_XCPOSRRPT_REQ_STRU
 �ṹ˵��  :

  1.��    ��   : 2016��03��09��
    ��    ��   : h00360002
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucXcposrRptFlg;                         /* +XCPOSRRPT���������ϱ����ƣ��ϵ翪��Ĭ��Ϊ�����������ϱ� */
    VOS_UINT8                           aucReserved[3];
} AT_MTA_SET_XCPOSRRPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MTA_AT_QRY_XCPOSR_CNF_STRU
 �ṹ˵��  :

  1.��    ��   : 2016��03��08��
    ��    ��   : h00360002
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;                               /* ����ִ�н�� */
    VOS_UINT8                           ucXcposrRptFlg;
    VOS_UINT8                           aucReserved[3];
} MTA_AT_QRY_XCPOSRRPT_CNF_STRU;

/*******************************************************************************
 �ṹ��    : AT_MTA_SET_SENSOR_REQ_STRU
 �ṹ˵��  :

  1.��    ��   : 2016��03��22��
    ��    ��   : z00347560
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSensorStat;                              /* Sensor Hub ״̬ */
    VOS_UINT8                           aucReserved[3];
}AT_MTA_SET_SENSOR_REQ_STRU;
/*****************************************************************************
 �ṹ��    : MTA_AT_SET_SENSOR_CNF_STRU
 �ṹ˵��  : MTA���ظ���AT����Sensor Hub״̬����Ϣ�ṹ

  1.��    ��   : 2016��03��22��
    ��    ��   : z00347560
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_SENSOR_CNF_STRU;

/*******************************************************************************
 �ṹ��    : AT_MTA_SET_SCREEN_REQ_STRU
 �ṹ˵��  :

  1.��    ��   : 2016��03��22��
    ��    ��   : z00347560
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucScreenStat;                              /* Screen ״̬ */
    VOS_UINT8                           aucReserved[3];
}AT_MTA_SET_SCREEN_REQ_STRU;
/*****************************************************************************
 �ṹ��    : MTA_AT_SET_SCREEN_CNF_STRU
 �ṹ˵��  : MTA���ظ���AT����������״̬����Ϣ�ṹ

  1.��    ��   : 2016��03��22��
    ��    ��   : z00347560
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MTA_AT_RESULT_ENUM_UINT32           enResult;
} MTA_AT_SET_SCREEN_CNF_STRU;
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
    AT_MTA_MSG_TYPE_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_MTA_MSG_TYPE_ENUM_UINT32*/
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MTA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_DATA                     stMsgData;
}AtMtaInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
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

