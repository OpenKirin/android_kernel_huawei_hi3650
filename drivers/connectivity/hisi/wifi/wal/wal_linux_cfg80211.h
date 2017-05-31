/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_linux_cfg80211.h
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : wal_linux_cfg80211.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : zhangheng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __WAL_LINUX_CFG80211_H__
#define __WAL_LINUX_CFG80211_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_types.h"
#include "wal_ext_if.h"
#include "frw_ext_if.h"
#include "hmac_ext_if.h"
#include "wal_linux_ioctl.h"
#include "wal_linux_scan.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_CFG80211_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define     WAL_MAX_SCAN_TIME_PER_CHANNEL  400

#define     WAL_MAX_SCAN_TIME_PER_SCAN_REQ (5 * 1000)      /* wpa_s�·�ɨ�����󣬳�ʱʱ��Ϊ5s����λΪms */

/* channel index and frequence */
#define WAL_MIN_CHANNEL_2G      1
#define WAL_MAX_CHANNEL_2G      14

#define WAL_MIN_CHANNEL_5G      36
#define WAL_MAX_CHANNEL_5G      165

#define WAL_MIN_CHANNEL_4_9G    184
#define WAL_MAX_CHANNEL_4_9G    196

#define WAL_MIN_FREQ_2G    (2412 + 5*(WAL_MIN_CHANNEL_2G - 1))
#define WAL_MAX_FREQ_2G    (2484)
#define WAL_MIN_FREQ_5G    (5000 + 5*(WAL_MIN_CHANNEL_5G))
#define WAL_MAX_FREQ_5G    (5000 + 5*(WAL_MAX_CHANNEL_5G))

/* channel nums */
#define WAL_SCAN_CHANNEL_MAX_NUM ((WAL_MAX_CHANNEL_2G - WAL_MIN_CHANNEL_2G + 1) + (WAL_MAX_CHANNEL_4_9G - WAL_MIN_CHANNEL_5G + 1))

/* wiphy �ṹ���ʼ������ */
//#define WAL_MAX_PROBED_SSID_NUM     1
#define WAL_MAX_SCAN_IE_LEN        1000
/* 802.11n HT �������� */
#define IEEE80211_HT_CAP_LDPC_CODING        0x0001
#define IEEE80211_HT_CAP_SUP_WIDTH_20_40    0x0002
#define IEEE80211_HT_CAP_SM_PS          0x000C
#define IEEE80211_HT_CAP_SM_PS_SHIFT    2
#define IEEE80211_HT_CAP_GRN_FLD        0x0010
#define IEEE80211_HT_CAP_SGI_20         0x0020
#define IEEE80211_HT_CAP_SGI_40         0x0040
#define IEEE80211_HT_CAP_TX_STBC        0x0080
#define IEEE80211_HT_CAP_RX_STBC        0x0300
#define IEEE80211_HT_CAP_DELAY_BA       0x0400
#define IEEE80211_HT_CAP_MAX_AMSDU      0x0800
#define IEEE80211_HT_CAP_DSSSCCK40      0x1000
#define IEEE80211_HT_CAP_RESERVED       0x2000
#define IEEE80211_HT_CAP_40MHZ_INTOLERANT   0x4000
#define IEEE80211_HT_CAP_LSIG_TXOP_PROT     0x8000

/* 802.11ac VHT Capabilities */
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895			0x00000000
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991			0x00000001
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454			0x00000002
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ		0x00000004
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ	0x00000008
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK			0x0000000C
#define IEEE80211_VHT_CAP_RXLDPC				0x00000010
#define IEEE80211_VHT_CAP_SHORT_GI_80				0x00000020
#define IEEE80211_VHT_CAP_SHORT_GI_160				0x00000040
#define IEEE80211_VHT_CAP_TXSTBC				0x00000080
#define IEEE80211_VHT_CAP_RXSTBC_1				0x00000100
#define IEEE80211_VHT_CAP_RXSTBC_2				0x00000200
#define IEEE80211_VHT_CAP_RXSTBC_3				0x00000300
#define IEEE80211_VHT_CAP_RXSTBC_4				0x00000400
#define IEEE80211_VHT_CAP_RXSTBC_MASK				0x00000700
#define IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE			0x00000800
#define IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE			0x00001000
#define IEEE80211_VHT_CAP_BEAMFORMER_ANTENNAS_MAX		0x00006000
#define IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MAX		0x00030000
#define IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE			0x00080000
#define IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE			0x00100000
#define IEEE80211_VHT_CAP_VHT_TXOP_PS				0x00200000
#define IEEE80211_VHT_CAP_HTC_VHT				0x00400000
#define IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT	23
#define IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK	\
		(7 << IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT)
#define IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB	0x08000000
#define IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB	0x0c000000
#define IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN			0x10000000
#define IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN			0x20000000

/* management */
#define IEEE80211_STYPE_ASSOC_REQ       0x0000
#define IEEE80211_STYPE_ASSOC_RESP      0x0010
#define IEEE80211_STYPE_REASSOC_REQ     0x0020
#define IEEE80211_STYPE_REASSOC_RESP    0x0030
#define IEEE80211_STYPE_PROBE_REQ       0x0040
#define IEEE80211_STYPE_PROBE_RESP      0x0050
#define IEEE80211_STYPE_BEACON          0x0080
#define IEEE80211_STYPE_ATIM            0x0090
#define IEEE80211_STYPE_DISASSOC        0x00A0
#define IEEE80211_STYPE_AUTH            0x00B0
#define IEEE80211_STYPE_DEAUTH          0x00C0
#define IEEE80211_STYPE_ACTION          0x00D0

#define WAL_COOKIE_ARRAY_SIZE           8       /* ����8bit ��map ��Ϊ����cookie ������״̬ */
#define WAL_MGMT_TX_TIMEOUT_MSEC        100     /* WAL ���͹���֡��ʱʱ�� */
#define WAL_MGMT_TX_RETRY_CNT           8       /* WAL ���͹���֡����ش����� */

#define IEEE80211_FCTL_FTYPE            0x000c
#define IEEE80211_FCTL_STYPE            0x00f0
#define IEEE80211_FTYPE_MGMT            0x0000

#define WAL_GET_STATION_THRESHOLD 1000 /* �̶�ʱ��������һ�����¼���DMAC RSSI */

typedef struct cookie_arry
{
    oal_uint64  ull_cookie;
    oal_uint32  ul_record_time;
}cookie_arry_stru;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#define RATETAB_ENT(_rate, _rateid, _flags)     \
{                                                               \
    .bitrate        = (_rate),                                  \
    .hw_value       = (_rateid),                                \
    .flags          = (_flags),                                 \
}

#define CHAN2G(_channel, _freq, _flags)  \
{                       \
    .band                   = IEEE80211_BAND_2GHZ,          \
    .center_freq            = (_freq),                      \
    .hw_value               = (_channel),                   \
    .flags                  = (_flags),                     \
    .max_antenna_gain       = 0,                            \
    .max_power              = 30,                           \
}

#define CHAN5G(_channel, _flags) \
{                                              \
    .band                   = IEEE80211_BAND_5GHZ,          \
    .center_freq            = 5000 + (5 * (_channel)),      \
    .hw_value               = (_channel),                   \
    .flags                  = (_flags),                     \
    .max_antenna_gain       = 0,                            \
    .max_power              = 30,                           \
}

#define CHAN4_9G(_channel, _flags) \
{                                              \
    .band                   = IEEE80211_BAND_5GHZ,          \
    .center_freq            = 4000 + (5 * (_channel)),      \
    .hw_value               = (_channel),                   \
    .flags                  = (_flags),                     \
    .max_antenna_gain       = 0,                            \
    .max_power              = 30,                           \
}

#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)

#define RATETAB_ENT(_rate, _rateid, _flags)     \
{                                               \
    (_flags),                                   \
    (_rate),                  \
    (_rateid),                \
}

#define CHAN2G(_channel, _freq, _flags)  \
{                       \
    IEEE80211_BAND_2GHZ,          \
    (_freq),                      \
    (_channel),                   \
    (_flags),                     \
    0,                            \
    30,                           \
}

#define CHAN5G(_channel, _flags)  \
{                                 \
    IEEE80211_BAND_5GHZ,          \
    5000 + (5 * (_channel)),      \
    (_channel),                   \
    (_flags),                     \
    0,                            \
    30,                           \
}

#define CHAN4_9G(_channel, _flags) \
{                                 \
    IEEE80211_BAND_5GHZ,          \
    4000 + (5 * (_channel)),      \
    (_channel),                   \
    (_flags),                     \
    0,                            \
    30,                           \
}


#else
    error "WRONG OS VERSION"
#endif


#define WAL_MIN_RTS_THRESHOLD 256
#define WAL_MAX_RTS_THRESHOLD 0xFFFF

#define WAL_MAX_FRAG_THRESHOLD 7536
#define WAL_MIN_FRAG_THRESHOLD 256

#define WAL_MAX_WAIT_TIME 3000
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_workqueue_stru  *g_pst_del_virtual_inf_workqueue;
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
extern oal_uint8 g_uc_vowifi_report_cnt;
#endif


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
        /* �˴�02����koʱ���֣��Ҳ������ŵĴ��󣬴�������� TBD */
/*****************************************************************************
 �� �� ��  : oal_ieee80211_is_probe_resp
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��7��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��7��
    ��    ��   : xiaoyuren 00305155
    �޸�����   : �ж��Ƿ���probe response
    check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_PROBE_RESP
    @fc: frame control bytes in little-endian byteorder

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_ieee80211_is_probe_resp(oal_uint16 fc)
{
	return (fc &  (IEEE80211_FCTL_FTYPE | IEEE80211_FCTL_STYPE)) ==
	       (IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_PROBE_RESP);
}

extern oal_void  wal_cfg80211_exit(oal_void);

extern oal_uint32  wal_cfg80211_init(oal_void);

extern oal_uint32  wal_cfg80211_init_evt_handle(frw_event_mem_stru *pst_event_mem);
#if (_PRE_CONFIG_TARGET_PRODUCT != _PRE_TARGET_PRODUCT_TYPE_E5)  //E5��hostapd�����ͳһ����
extern oal_uint32  wal_cfg80211_mgmt_tx_status(frw_event_mem_stru *pst_event_mem);
#endif

#ifdef _PRE_WLAN_FEATURE_VOWIFI
extern oal_uint32  wal_cfg80211_vowifi_report(frw_event_mem_stru *pst_event_mem);
#endif /* wal_cfg80211_vowifi_report */

#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32  wal_roam_comp_proc_sta(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
extern oal_uint32  wal_ft_event_proc_sta(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_11R

extern oal_void wal_cfg80211_unregister_netdev(oal_net_device_stru *pst_net_dev);

extern oal_uint32 wal_del_p2p_group(mac_device_stru *pst_mac_device);


extern oal_uint32 wal_cfg80211_add_vap(mac_cfg_add_vap_param_stru *pst_add_vap_param);

extern oal_void wal_cfg80211_reset_bands(oal_void);
extern oal_void wal_cfg80211_save_bands(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_cfg80211.h */
