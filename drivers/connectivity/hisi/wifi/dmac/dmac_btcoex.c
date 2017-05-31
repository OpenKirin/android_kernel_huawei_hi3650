/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_btcoex.c
  �� �� ��   : ����
  ��    ��   : c00221210
  ��������   : 2014��12��02��
  ����޸�   :
  ��������   : WiFi��bt���������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��02��
    ��    ��   : c00221210
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "mac_data.h"
#include "dmac_btcoex.h"
#include "dmac_alg_if.h"
#include "dmac_alg.h"
#include "dmac_auto_adjust_freq.h"
#include "dmac_device.h"
#include "dmac_resource.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BTCOEX_C

#define WLAN_TIDNO_COEX_QOSNULL     WLAN_TIDNO_ANT_TRAINING_HIGH_PRIO   /* ����qos null�����������߸����ȼ�ѵ��֡ */
#define BTCOEX_RATE_THRESHOLD_MIN   0
#define BTCOEX_RATE_THRESHOLD_MAX   1
#define BTCOEX_RATE_THRESHOLD_BUTT  2


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern oal_uint32  dmac_send_sys_event(mac_vap_stru *pst_mac_vap,
                                                wlan_cfgid_enum_uint16 en_cfg_id,
                                                oal_uint16 us_len,
                                                oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
extern oal_uint32 dmac_config_set_device_freq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

OAL_STATIC OAL_INLINE oal_void dmac_btcoex_rx_average_rate_calculate (dmac_user_btcoex_rx_info_stru *pst_btcoex_wifi_rx_rate_info,
                                                                                oal_uint32 *pul_rx_rate, oal_uint16 *pus_rx_count);

oal_uint8 g_auc_rx_win_size[BTCOEX_RX_WINDOW_SIZE_GRADES][BTCOEX_RX_WINDOW_SIZE_INDEX_MAX] = {
    {2, 4, 8, 64}, {4, 8, 32, 64}
};
/****************************************
              ����    �绰    ����
    2G/20M      0       0       0
    5G/20M      0       0       0
    2G/40M      0       1       1
    5G/40M      0       0       1
    5G/80M      1       1       1
*****************************************/
oal_uint8 g_auc_rx_win_size_grage[WLAN_BAND_BUTT][WLAN_BW_CAP_BUTT][BTCOEX_BT_NUM_OF_ACTIVE_MODE] = {
    /* 2G */
    /* 20M */  /* 40M */
    /* ����, �绰, ���� */
    {{0, 0, 0}, {0, 1, 1}, {1, 1, 1}, {1, 1, 1}},
    /* 5G */
    /* 20M */  /* 40M */  /* 80M */
    /* ����, �绰, ���� */
    {{0, 0, 0}, {0, 0, 1}, {1, 1, 1}, {1, 1, 1}}
};
oal_uint16 g_aus_btcoex_rate_thresholds[WLAN_BAND_BUTT][WLAN_BW_CAP_BUTT][BTCOEX_RATE_THRESHOLD_BUTT] = {
    /* 2G */
    /* 20M */  /* 40M */
    {{23, 60}, {50, 130}, {0, 0},     {0, 0}},
    /* 5G */
    /* 20M */  /* 40M */  /* 80M */
    {{23, 80}, {50, 160}, {108, 340}, {0, 0}}
};

oal_uint32 g_rx_statistics_print = 0;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_btcoex_encap_preempt_sta
 ��������  : ����ָ����PSλ��null data֡
 �������  : oal_uint8 *puc_frame

 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��10��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_btcoex_encap_preempt_sta(oal_uint8 *puc_frame,
                                                               oal_uint8 *puc_da,
                                                               oal_uint8 *puc_sa,
                                                               coex_preempt_frame_enum_uint8 en_preempt_type)
{
    oal_uint32                        ul_qosnull_seq_num = 0;
    /* ��д֡ͷ,����from dsΪ1��to dsΪ0��ps=1 ���frame control�ĵڶ����ֽ�Ϊ12 */
    if (BTCOEX_NULLDATA == en_preempt_type)
    {

        mac_ieee80211_frame_stru *pst_mac_header = (mac_ieee80211_frame_stru *)puc_frame;
        mac_null_data_encap(puc_frame,
                            WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA | 0x1100,
                            puc_da,
                            puc_sa);
        /* �趨seq num��frag */
        puc_frame[22] = 0;
        puc_frame[23] = 0;
        pst_mac_header->st_frame_control.bit_power_mgmt = 1;
    }
    else if (BTCOEX_QOSNULL == en_preempt_type)
    {
        dmac_btcoex_qosnull_frame_stru *pst_mac_header = (dmac_btcoex_qosnull_frame_stru *)puc_frame;
        mac_null_data_encap(puc_frame,
                            WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL | 0x1100,
                            puc_da,
                            puc_sa);
        pst_mac_header->st_frame_control.bit_power_mgmt = 1;
        pst_mac_header->bit_qc_tid = WLAN_TIDNO_COEX_QOSNULL;
        pst_mac_header->bit_qc_eosp = 0;

        /* ����seq�����к� */
        hal_get_btcoex_abort_qos_null_seq_num(&ul_qosnull_seq_num);
        pst_mac_header->bit_sc_seq_num = (ul_qosnull_seq_num + 1);
        hal_set_btcoex_abort_qos_null_seq_num(pst_mac_header->bit_sc_seq_num);

        /*Э��涨������QOS NULL DATAֻ����normal ack ��������Ҫ����0�ǶԷ����ack */
        pst_mac_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;

    }
    else
    {
    }

}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_init_preempt
 ��������  :
 �������  : pst_dmac_vap
             pst_dmac_user
 �������  : ��
 �� �� ֵ  : OAL_SUCC��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��10��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_init_preempt(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, coex_preempt_frame_enum_uint8 en_preempt_type)
{
    dmac_vap_stru *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
    /* ��д֡ͷ*/
    dmac_btcoex_encap_preempt_sta(pst_dmac_vap->st_dmac_vap_btcoex.auc_null_qosnull_frame,
                                  pst_mac_user->auc_user_mac_addr,
                                  pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                                  en_preempt_type);

    hal_set_btcoex_abort_null_buff_addr((oal_uint32)pst_dmac_vap->st_dmac_vap_btcoex.auc_null_qosnull_frame);

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_status_event_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_update_ba_size(mac_vap_stru *pst_mac_vap, dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba, hal_btcoex_btble_status_stru *pst_btble_status)
{
    bt_status_stru *pst_bt_status;
    ble_status_stru *pst_ble_status;
    oal_uint8 uc_bt_active_mode;
    oal_uint8 uc_bt_rx_win_size_grade;
    oal_uint8 uc_band;
    oal_uint8 uc_bandwidth;

    pst_bt_status = &(pst_btble_status->un_bt_status.st_bt_status);
    pst_ble_status = &(pst_btble_status->un_ble_status.st_ble_status);

    uc_band = pst_mac_vap->st_channel.en_band;
    mac_vap_get_bandwidth_cap(pst_mac_vap, &uc_bandwidth);
    if ((uc_band >= WLAN_BAND_BUTT) || (uc_bandwidth >= WLAN_BW_CAP_BUTT))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_ba_size::band %d, bandwidth %d exceed scale!}",
                         uc_band, uc_bandwidth);
        return;
    }
    if (pst_dmac_user_btcoex_delba->uc_ba_size_index >= BTCOEX_RX_WINDOW_SIZE_INDEX_MAX)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_ba_size::ba_size_index %d exceed scale!}",
                         pst_dmac_user_btcoex_delba->uc_ba_size_index);
        return;
    }

    if (pst_bt_status->bit_bt_sco)
    {
        uc_bt_active_mode = 1;
        /* 6slot �豸 */
        if (2 == pst_ble_status->bit_bt_6slot)
        {
            pst_dmac_user_btcoex_delba->uc_ba_size = 1;
            return;
        }
    }
    else if (pst_bt_status->bit_bt_a2dp)
    {
        uc_bt_active_mode = 0;
    }
    else if (pst_ble_status->bit_bt_transfer)
    {
        uc_bt_active_mode = 2;
    }
    else
    {
        uc_bt_active_mode = BTCOEX_BT_NUM_OF_ACTIVE_MODE;
    }

    /* BTû��ҵ��, �ۺ�64 */
    if (uc_bt_active_mode >= BTCOEX_BT_NUM_OF_ACTIVE_MODE)
    {
        uc_bt_active_mode = 0;
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
    }

    uc_bt_rx_win_size_grade = g_auc_rx_win_size_grage[uc_band][uc_bandwidth][uc_bt_active_mode];

    pst_dmac_user_btcoex_delba->uc_ba_size = g_auc_rx_win_size[uc_bt_rx_win_size_grade][pst_dmac_user_btcoex_delba->uc_ba_size_index];
}

/*****************************************************************************
 �� �� ��  : dmac_bt_transfer_status_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : c000221210
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_bt_transfer_status_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    mac_device_stru *pst_mac_device;
    mac_vap_stru *pst_mac_vap;
    hal_to_dmac_device_stru *pst_hal_device;
    dmac_user_stru *pst_dmac_user;
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_btcoex_get_legacy_sta(pst_mac_device, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;
    pst_btcoex_btble_status = &(pst_hal_device->st_btcoex_btble_status);

    if (pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_transfer)
    {
        dmac_alg_cfg_btcoex_state_notify(pst_mac_device,BT_TRANSFER_ON);
    }
    else
    {
        dmac_alg_cfg_btcoex_state_notify(pst_mac_device,BT_TRANSFER_OFF);
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);

    /* ����bt�򿪺͹رճ����£��ԾۺϽ��д��� */
    if ((pst_btcoex_btble_status->un_bt_status.st_bt_status.bit_bt_on) && (pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_transfer))
    {
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
        pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
    }
    else
    {
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
        pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
    }
    dmac_btcoex_update_ba_size(pst_mac_vap, pst_dmac_user_btcoex_delba, pst_btcoex_btble_status);
    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::bt transfer status changed:%d, bar_size: %d}",
            pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_transfer,
            pst_dmac_user_btcoex_delba->uc_ba_size);

    dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, pst_dmac_user_btcoex_delba->uc_ba_size);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_rx_rate_statistics_flag_callback
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_rx_rate_statistics_flag_callback(oal_void *p_arg)
{
    mac_device_stru *pst_mac_device;
    mac_vap_stru *pst_mac_vap;
    dmac_vap_stru *pst_dmac_vap;
    dmac_user_stru *pst_dmac_user;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_user_btcoex_rx_info_stru *pst_dmac_user_btcoex_rx_info;

    pst_mac_vap = (mac_vap_stru *)p_arg;
    pst_dmac_vap = (dmac_vap_stru *)p_arg;
    if (OAL_FALSE == dmac_btcoex_check_legacy_sta(pst_mac_vap))
    {
        return OAL_SUCC;
    }
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_rx_rate_statistics_flag_callback::pst_device[id:%d] NULL}",
                    pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_rx_rate_statistics_flag_callback::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_btcoex_btble_status = &(pst_mac_device->pst_device_stru->st_btcoex_btble_status);
    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_dmac_user_btcoex_rx_info = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_rx_info);

    /* BTҵ����� */
    if (OAL_FALSE == pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_ba)
    {
        dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;
        pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);
        pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_flag = OAL_FALSE;
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_statistics_timer));
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_low_rate_timer));
        if (BTCOEX_RX_WINDOW_SIZE_INDEX_3 != pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index)
        {
            pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            dmac_btcoex_update_ba_size(pst_mac_vap, pst_dmac_user_btcoex_delba, pst_btcoex_btble_status);
            dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, pst_dmac_user_btcoex_delba->uc_ba_size);
        }
        OAL_MEMZERO(pst_dmac_user_btcoex_rx_info, OAL_SIZEOF(dmac_user_btcoex_rx_info_stru));
        return OAL_SUCC;
    }

    if (pst_dmac_user_btcoex_rx_info->us_rx_rate_stat_count < BTCOEX_RX_COUNT_LIMIT)
    {
        OAL_MEMZERO(pst_dmac_user_btcoex_rx_info, OAL_SIZEOF(dmac_user_btcoex_rx_info_stru));
        return OAL_SUCC;
    }

    pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_timeout = OAL_TRUE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_sco_rx_rate_statistics_flag_callback
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_sco_rx_rate_statistics_flag_callback(oal_void *p_arg)
{
    mac_device_stru *pst_mac_device;
    dmac_device_stru *pst_dmac_device;
    mac_vap_stru *pst_mac_vap;
    dmac_vap_stru *pst_dmac_vap;
    dmac_user_stru *pst_dmac_user;
    dmac_user_btcoex_sco_rx_rate_status_stru *pst_dmac_user_btcoex_sco_rx_rate_status;
    oal_uint32 ul_rx_rate = 0;
    oal_uint16 us_rx_count = 0;
    oal_uint8 uc_notify_bt = OAL_FALSE;
    oal_uint8 uc_notify_bt_value = 0;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_user_btcoex_rx_info_stru *pst_btcoex_wifi_rx_rate_info;

    pst_mac_vap = (mac_vap_stru *)p_arg;
    pst_dmac_vap = (dmac_vap_stru *)p_arg;
    if (OAL_FALSE == dmac_btcoex_check_legacy_sta(pst_mac_vap))
    {
        return OAL_SUCC;
    }
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_sco_rx_rate_statistics_flag_callback::pst_device[id:%d] NULL}",
                    pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_rx_rate_statistics_flag_callback::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_rx_rate_statistics_flag_callback::pst_dmac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_btcoex_btble_status = &(pst_mac_device->pst_device_stru->st_btcoex_btble_status);
    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_btcoex_wifi_rx_rate_info = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_sco_rx_info);

    /* BTҵ����� */
    if (!pst_btcoex_btble_status->un_bt_status.st_bt_status.bit_bt_sco)
    {
        if (!pst_btcoex_btble_status->un_bt_status.st_bt_status.bit_bt_a2dp)
        {
            dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;
            pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);
            pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            dmac_btcoex_update_ba_size(pst_mac_vap, pst_dmac_user_btcoex_delba, pst_btcoex_btble_status);
            dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, pst_dmac_user_btcoex_delba->uc_ba_size);
        }
        pst_dmac_vap_btcoex_rx_statistics->uc_sco_rx_rate_statistics_flag = OAL_FALSE;
        OAL_MEMZERO(pst_btcoex_wifi_rx_rate_info, OAL_SIZEOF(dmac_user_btcoex_rx_info_stru));
        return OAL_SUCC;
    }

    /* ����������� */
    dmac_btcoex_rx_average_rate_calculate(pst_btcoex_wifi_rx_rate_info, &ul_rx_rate, &us_rx_count);

    /* ����������� */
    if (pst_dmac_device->st_dmac_alg_stat.en_dmac_device_distance_enum < DMAC_ALG_TPC_FAR_DISTANCE)
    {
        pst_dmac_user_btcoex_sco_rx_rate_status = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_sco_rx_rate_status);

        /* ���ݲ�ͬ����ȷ����ͬ�����ʵȼ�:���١����١����١������� */
        if (0 == us_rx_count)
        {
            switch (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
            {
            case BTCOEX_RATE_STATE_M:
            case BTCOEX_RATE_STATE_L:
            case BTCOEX_RATE_STATE_SL:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_H;
                uc_notify_bt = OAL_TRUE;
                break;
            default:
                break;
            }
        }
        else if (us_rx_count <= 2)
        {
            switch (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
            {
            case BTCOEX_RATE_STATE_SL:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_L;
                uc_notify_bt = OAL_TRUE;
                break;
            default:
                break;
            }
        }
        else if (1 == ul_rx_rate)
        {
            switch (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
            {
            case BTCOEX_RATE_STATE_H:
            case BTCOEX_RATE_STATE_M:
            case BTCOEX_RATE_STATE_L:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_SL;
                uc_notify_bt = OAL_TRUE;
                break;
            default:
                break;
            }
        }
        else if (ul_rx_rate <= 11)
        {
            switch (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
            {
            case BTCOEX_RATE_STATE_H:
            case BTCOEX_RATE_STATE_M:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_L;
                uc_notify_bt = OAL_TRUE;
                break;
            default:
                break;
            }
        }
        else if (ul_rx_rate < 35)
        {
            switch (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
            {
            case BTCOEX_RATE_STATE_H:
            case BTCOEX_RATE_STATE_L:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_M;
                uc_notify_bt = OAL_TRUE;
                break;
            case BTCOEX_RATE_STATE_SL:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_L;
                uc_notify_bt = OAL_TRUE;
                break;
            default:
                break;
            }
        }
        /* ���ʴ���50Mb/s������հ�������500������Ϊ��ǰ������������֪BT��ǰWifi���ڸ���״̬ */
        else if (us_rx_count >= 250 || ul_rx_rate >= 50)
        {
            switch (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
            {
            case BTCOEX_RATE_STATE_M:
            case BTCOEX_RATE_STATE_L:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_H;
                uc_notify_bt = OAL_TRUE;
                break;
            case BTCOEX_RATE_STATE_SL:
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status = BTCOEX_RATE_STATE_L;
                uc_notify_bt = OAL_TRUE;
                break;
            default:
                break;
            }
        }
        else
        {}
        uc_notify_bt_value = pst_dmac_user_btcoex_sco_rx_rate_status->uc_status;

        /* ��ֹһֱ�ڳ����ٵ��µ绰̫�������ó�ʱ�ָ��ɵ��٣�����״̬���䣬��֪ͨBT��Ϣ�ı� */
        if (BTCOEX_RATE_STATE_SL == pst_dmac_user_btcoex_sco_rx_rate_status->uc_status)
        {
            pst_dmac_user_btcoex_sco_rx_rate_status->uc_status_sl_time++;
            if (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status_sl_time > (ALL_MID_PRIO_TIME + ALL_HIGH_PRIO_TIME))
            {
                pst_dmac_user_btcoex_sco_rx_rate_status->uc_status_sl_time = 0;
                uc_notify_bt = OAL_TRUE;
                uc_notify_bt_value = BTCOEX_RATE_STATE_SL;
            }
            else if (pst_dmac_user_btcoex_sco_rx_rate_status->uc_status_sl_time > ALL_MID_PRIO_TIME)
            {
                uc_notify_bt = OAL_TRUE;
                uc_notify_bt_value = BTCOEX_RATE_STATE_L;
            }
        }
        else
        {
            pst_dmac_user_btcoex_sco_rx_rate_status->uc_status_sl_time = 0;
        }

        if (OAL_TRUE == uc_notify_bt)
        {
            hal_set_btcoex_soc_gpreg1(uc_notify_bt_value, BIT4 | BIT5, 4);
            hal_coex_sw_irq_set(BIT5);
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_sco_rx_rate_process::uc_notify_status: %d, uc_stay_status %d, uc_rate: %d, count %d.}",
                                uc_notify_bt_value, pst_dmac_user_btcoex_sco_rx_rate_status->uc_status, ul_rx_rate, us_rx_count);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_status_event_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : c000221210
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_a2dp_status_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    mac_vap_stru *pst_mac_vap;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    dmac_vap_stru *pst_dmac_vap;
    dmac_user_stru *pst_dmac_user;
    hal_btcoex_btble_status_stru *pst_btble_status;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;
    oal_uint8 uc_need_delba;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_btcoex_get_legacy_sta(pst_mac_device, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);
    pst_btble_status = &(pst_hal_device->st_btcoex_btble_status);
    uc_need_delba = OAL_FALSE;

    /* ����bt�򿪺͹رճ����£��ԾۺϽ��д��� */
    if (pst_btble_status->un_bt_status.st_bt_status.bit_bt_a2dp)
    {
        if (BTCOEX_RX_WINDOW_SIZE_INDEX_3 == pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index)
        {
            pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_1;
        }
        else
        {
            pst_dmac_user_btcoex_delba->uc_ba_size_index = pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index;
        }
        pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_flag = OAL_TRUE;
    }
    /* ֻ�е绰���ֶ�û�е�����Ž��лָ���64�ľۺ� */
    else if(!pst_btble_status->un_bt_status.st_bt_status.bit_bt_sco)
    {
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
        pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_flag = OAL_FALSE;
    }
    /* ���ֽ�����ʱ���е绰�ĳ����������ﲻ����BAɾ�������ɵ绰�����̿��� */
    else
    {
        return OAL_SUCC;
    }

    dmac_btcoex_update_ba_size(pst_mac_vap, pst_dmac_user_btcoex_delba, pst_btble_status);
    OAM_WARNING_LOG3(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::bt ba status changed:%d, bar_size: %d uc_need_delba:%d}",
            pst_btble_status->un_bt_status.st_bt_status.bit_bt_a2dp,
            pst_dmac_user_btcoex_delba->uc_ba_size,uc_need_delba);
    dmac_btcoex_delba_trigger(pst_mac_vap, uc_need_delba, pst_dmac_user_btcoex_delba->uc_ba_size);

    pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_timeout = OAL_FALSE;
    FRW_TIMER_CREATE_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_statistics_timer),
                               dmac_btcoex_rx_rate_statistics_flag_callback,
                               BTCOEX_RX_STATISTICS_TIME,
                               (void *)pst_mac_vap,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,
                               pst_mac_device->ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_page_scan_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��13��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_page_scan_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    mac_vap_stru *pst_mac_vap;
    mac_device_stru *pst_mac_device;
    dmac_vap_stru *pst_dmac_vap;
    dmac_vap_btcoex_occupied_stru *pst_dmac_vap_btcoex_occupied;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_page_scan_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_page_scan_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_btcoex_get_legacy_sta(pst_mac_device, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
    pst_dmac_vap_btcoex_occupied = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied);

    hal_btcoex_update_ap_beacon_count(&(pst_dmac_vap_btcoex_occupied->ul_ap_beacon_count));
    pst_dmac_vap_btcoex_occupied->uc_ap_beacon_miss = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_sco_status_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : c000221210
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_sco_status_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    mac_vap_stru *pst_mac_vap;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    dmac_vap_stru *pst_dmac_vap;
    dmac_user_stru *pst_dmac_user;
    bt_status_stru *pst_bt_status;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;
    hal_btcoex_btble_status_stru *pst_btble_status;
    oal_uint8 uc_need_delba = OAL_TRUE;
    oal_uint16 us_timeout_ms;
    oal_uint8 uc_periodic;
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    config_device_freq_h2d_stru st_device_freq;
    oal_uint8 uc_index;
    device_pps_freq_level_stru*    device_ba_pps_freq_level;
#endif
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_status_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_status_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_status_handler::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_btcoex_get_legacy_sta(pst_mac_device, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    pst_btble_status = &(pst_hal_device->st_btcoex_btble_status);
    pst_bt_status = &(pst_btble_status->un_bt_status.st_bt_status);

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_device_freq.uc_set_type = FREQ_SET_MODE;
    if (!pst_bt_status->bit_bt_sco)
    {
        /* �����Զ���Ƶ */
        st_device_freq.uc_device_freq_enable = OAL_TRUE;
        device_ba_pps_freq_level = dmac_get_ba_pps_freq_level();
        for(uc_index = 0; uc_index < 4; uc_index++)
        {
            st_device_freq.st_device_data[uc_index].ul_speed_level = device_ba_pps_freq_level->ul_speed_level;
            st_device_freq.st_device_data[uc_index].ul_cpu_freq_level = device_ba_pps_freq_level->ul_cpu_freq_level;
            device_ba_pps_freq_level++;
        }
        dmac_config_set_device_freq(pst_mac_vap, 0, (oal_uint8 *)&st_device_freq);

    }
#endif
#endif
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);

    /* ����bt�򿪺͹رճ����£��ԾۺϽ��д��� */
    if (pst_bt_status->bit_bt_sco)
    {
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* �ر��Զ���Ƶ */
        st_device_freq.uc_device_freq_enable = OAL_FALSE;
        dmac_config_set_device_freq(pst_mac_vap, 0, (oal_uint8 *)&st_device_freq);
#endif
#endif
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_1;
        if (pst_dmac_user_btcoex_delba->uc_ba_size_index == pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index)
        {
            uc_need_delba = OAL_FALSE;
        }

        pst_dmac_vap_btcoex_rx_statistics->uc_sco_rx_rate_statistics_flag = OAL_TRUE;
        us_timeout_ms = BTCOEX_SCO_CALCULATE_TIME;
        uc_periodic = OAL_TRUE;

    }
    /* ֻ�е绰���ֶ�û�е�����Ž��лָ���64�ľۺ� */
    else if(!pst_btble_status->un_bt_status.st_bt_status.bit_bt_a2dp)
    {
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
        hal_set_btcoex_soc_gpreg1(0, BIT4 | BIT5, 4);
        uc_need_delba = OAL_FALSE;
        pst_dmac_vap_btcoex_rx_statistics->uc_sco_rx_rate_statistics_flag = OAL_FALSE;
        us_timeout_ms = BTCOEX_RX_STATISTICS_TIME;
        uc_periodic = OAL_FALSE;
    }
    /* �绰�ҶϺ������ֵĳ�����������BA��ɾ���������������̴��� */
    else
    {
        return OAL_SUCC;
    }

    FRW_TIMER_CREATE_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_sco_statistics_timer),
                                       dmac_btcoex_sco_rx_rate_statistics_flag_callback,
                                       us_timeout_ms,
                                       (void *)pst_mac_vap,
                                       uc_periodic,
                                       OAM_MODULE_ID_DMAC,
                                       pst_mac_device->ul_core_id);

    dmac_btcoex_update_ba_size(pst_mac_vap, pst_dmac_user_btcoex_delba, pst_btble_status);

    dmac_btcoex_delba_trigger(pst_mac_vap, uc_need_delba, pst_dmac_user_btcoex_delba->uc_ba_size);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_btcoex_register_dmac_misc_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 dmac_btcoex_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *))
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT || NULL == p_func)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_register_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_unregister_dmac_misc_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  dmac_btcoex_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type)
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_unregister_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = NULL;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_init()
 ��������  : ��ʼ��������صĲ���
 �������  : ��
 �� �� ֵ  : oal_err_code_enum_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��02��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��25��
    ��    ��   : g00306640
    �޸�����   : �޸�

*****************************************************************************/
oal_uint32 dmac_btcoex_init(oal_void)
{
    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_BT_A2DP, dmac_btcoex_a2dp_status_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event HAL_EVENT_DMAC_BT_A2DP fail!}");
        return OAL_FAIL;
    }
    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_BT_TRANSFER, dmac_bt_transfer_status_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event HAL_EVENT_DMAC_BT_TRANSFER fail!}");
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_A2DP);
        return OAL_FAIL;
    }
    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_BT_PAGE_SCAN, dmac_btcoex_page_scan_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event HAL_EVENT_DMAC_PAGE_SCAN fail!}");
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_A2DP);
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_TRANSFER);
        return OAL_FAIL;
    }
    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_BT_SCO, dmac_btcoex_sco_status_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event HAL_EVENT_DMAC_BT_SCO fail!}");
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_A2DP);
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_TRANSFER);
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_PAGE_SCAN);
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_exit()
 ��������  : ��ʼ��������صĲ���
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��02��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_btcoex_exit(oal_void)
{
    /* init coexit wifi bt param */
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_A2DP);
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_TRANSFER);
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_PAGE_SCAN);
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_SCO);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_wlan_priority_set()
 ��������  : ����趨�����ȼ�����
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_wlan_priority_set(mac_vap_stru *pst_mac_vap, oal_uint8 uc_value, oal_uint8 uc_timeout_ms)
{
    dmac_vap_stru *pst_dmac_vap;
    dmac_vap_btcoex_occupied_stru *pst_dmac_vap_btcoex_occupied;
    oal_uint32 ul_now_ms;
    oal_uint8 uc_set = OAL_FALSE;

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
    pst_dmac_vap_btcoex_occupied = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied);

    /* ��Ҫ����prio */
    if (OAL_TRUE == uc_value)
    {
        /* ��ǰû������prio���ҿ�������prio */
        if (OAL_FALSE == pst_dmac_vap_btcoex_occupied->uc_prio_occupied_state)
        {

            /* ��Ҫ����һ������ʱ��������100ms */
            ul_now_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            if (ul_now_ms - pst_dmac_vap_btcoex_occupied->ul_timestamp > 50)
            {
                /* ����priority��ʱ�� */
                FRW_TIMER_CREATE_TIMER(&pst_dmac_vap_btcoex_occupied->bt_coex_priority_timer,
                                           dmac_btcoex_wlan_priority_timeout_callback,
                                           uc_timeout_ms,
                                           (oal_void *)pst_dmac_vap,
                                           OAL_FALSE,
                                           OAM_MODULE_ID_DMAC,
                                           0);
                pst_dmac_vap_btcoex_occupied->uc_prio_occupied_state = OAL_TRUE;

                uc_set = OAL_TRUE;
            }
            else
            {
            }
        }
    }
    /* ��Ҫ����prio */
    else
    {
        if (OAL_TRUE == pst_dmac_vap_btcoex_occupied->uc_prio_occupied_state)
        {
            pst_dmac_vap_btcoex_occupied->uc_prio_occupied_state = OAL_FALSE;

            pst_dmac_vap_btcoex_occupied->ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        }
        uc_set = OAL_TRUE;
    }

    if (OAL_TRUE == uc_set)
    {
        /* uc_value == 1, ������ø����ȼ���uc_value == 0, ���ظ�Ӳ������ */
        hal_set_btcoex_hw_rx_priority_dis((oal_uint8)(!uc_value));

        /* ��������������ȼ� */
        hal_set_btcoex_hw_priority_en((oal_uint8)(!uc_value));

        /* ����������ȼ� */
        hal_set_btcoex_sw_priority_flag(uc_value);
    }

}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_wlan_priority_timeout_callback()
 ��������  : ����趨�����ȼ�������ʱ����
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_btcoex_wlan_priority_timeout_callback(oal_void *p_arg)
{
    mac_vap_stru *pst_mac_vap = (mac_vap_stru *)p_arg;

    dmac_btcoex_wlan_priority_set(pst_mac_vap, 0, 0);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_change_state_syn
 ��������  : ͬ��dmac vap״̬
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��25��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_change_state_syn(mac_vap_stru *pst_mac_vap)
{
    switch (pst_mac_vap->en_vap_state)
    {
    case MAC_VAP_STATE_STA_WAIT_SCAN:
    case MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2:
    case MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4:
    case MAC_VAP_STATE_STA_AUTH_COMP:
    case MAC_VAP_STATE_STA_WAIT_ASOC:
    case MAC_VAP_STATE_STA_OBSS_SCAN:
    case MAC_VAP_STATE_STA_BG_SCAN:
        hal_set_btcoex_hw_rx_priority_dis(0);
        break;
    default:
        hal_set_btcoex_hw_rx_priority_dis(1);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_rx_delba_trigger
 ��������  : Change ba size
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_need_delba,oal_uint8 uc_ba_size)
{
    dmac_to_hmac_btcoex_rx_delba_trigger_event_stru  st_dmac_to_hmac_btcoex_rx_delba;

    st_dmac_to_hmac_btcoex_rx_delba.uc_need_delba = uc_need_delba;
    st_dmac_to_hmac_btcoex_rx_delba.us_ba_size = uc_ba_size;
    st_dmac_to_hmac_btcoex_rx_delba.us_user_id = pst_mac_vap->uc_assoc_vap_id;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_BTCOEX_RX_DELBA_TRIGGER, OAL_SIZEOF(dmac_to_hmac_btcoex_rx_delba_trigger_event_stru), (oal_uint8 *)&st_dmac_to_hmac_btcoex_rx_delba);
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_vap_up_handle
 ��������  : ����vap_up����BT�����ж�
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_vap_up_handle(mac_vap_stru *pst_mac_vap)
{
    oal_uint8 uc_chan_idx;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    bt_status_stru *pst_bt_status;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_up_handle::pst_mac_device null.}");
        return;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_vap_up_handle::pst_hal_device null.}");
        return;
    }

    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_band, BIT0, 0);   // Ƶ��
    mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &uc_chan_idx);
    hal_set_btcoex_soc_gpreg0(uc_chan_idx, BIT5 | BIT4 | BIT3 | BIT2 | BIT1, 1);   // �ŵ�
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_bandwidth, BIT8 | BIT7 | BIT6, 6);   // ����
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT13, 13);
    hal_coex_sw_irq_set(BIT5);

    hal_update_btcoex_btble_status(pst_hal_device);

    pst_bt_status = &(pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status);

    if (pst_bt_status->bit_bt_on)
    {
        hal_set_btcoex_sw_all_abort_ctrl(OAL_TRUE);
    }

    /* ״̬�ϱ�BT: �ŵ�������Ƶ�ʵ�*/
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                 "{dmac_btcoex_vap_up_handle::VAP state->TRUE, channel state: band->%d, channel->%d, bandwidth->%d, bit status[%d]",
                 pst_mac_vap->st_channel.en_band,
                 pst_mac_vap->st_channel.uc_chan_number,
                 pst_mac_vap->st_channel.en_bandwidth,
                 pst_bt_status->bit_bt_on);
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_vap_down_handle
 ��������  : ����vap_down����BT�����ж�
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_vap_down_handle(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_down_handle::pst_mac_device null.}");

        return;
    }

    if (0 == mac_device_calc_up_vap_num(pst_mac_device))
    {
        /* ״̬�ϱ�BT */
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_down_handle::Notify BT cancel AFH.}");
        hal_set_btcoex_soc_gpreg1(OAL_FALSE, BIT3, 3);
        hal_coex_sw_irq_set(BIT5);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_update_rx_rate_threshold
 ��������  : ��ȡ��������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��23��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_update_rx_rate_threshold (mac_vap_stru *pst_mac_vap, dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba)
{
    oal_uint8 uc_band;
    oal_uint8 uc_bandwidth;

    uc_band = pst_mac_vap->st_channel.en_band;
    mac_vap_get_bandwidth_cap(pst_mac_vap, &uc_bandwidth);

    if ((uc_band >= WLAN_BAND_BUTT) || (uc_bandwidth >= WLAN_BW_CAP_BUTT))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_rx_rate_threshold::band %d, bandwidth %d exceed scale!}",
                         uc_band, uc_bandwidth);
        return;
    }
    pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_min = g_aus_btcoex_rate_thresholds[uc_band][uc_bandwidth][BTCOEX_RATE_THRESHOLD_MIN];
    pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_max = g_aus_btcoex_rate_thresholds[uc_band][uc_bandwidth][BTCOEX_RATE_THRESHOLD_MAX];

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_rx_rate_threshold:: min: %d, max: %d, band %d, bandwidth %d.}",
                        pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_min, pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_max, uc_band, uc_bandwidth);

}

/*****************************************************************************
 �� �� ��  : dmac_config_btcoex_assoc_state_syn
 ��������  : ͬ��������mac��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��28��
    ��    ��   : g00306640
    �޸�����   : ������sta��ap

*****************************************************************************/
oal_uint32 dmac_config_btcoex_assoc_state_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    dmac_vap_stru *pst_dmac_vap;
    dmac_user_stru *pst_dmac_user;
    dmac_vap_btcoex_stru *pst_dmac_vap_btcoex;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    oal_uint8 uc_chan_idx;
    oal_uint8 uc_need_delba;
    ble_status_stru *pst_ble_status;
    bt_status_stru *pst_bt_status;
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    config_device_freq_h2d_stru st_device_freq;
#endif
#endif

    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_band, BIT0, 0);    // Ƶ��
    mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &uc_chan_idx);
    hal_set_btcoex_soc_gpreg0(uc_chan_idx, BIT5 | BIT4 | BIT3 | BIT2 | BIT1, 1);    // �ŵ�
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_bandwidth, BIT8 | BIT7 | BIT6, 6); // ����
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT13, 13);
    hal_set_btcoex_soc_gpreg1(OAL_FALSE, BIT2, 2);
    hal_set_btcoex_soc_gpreg1(OAL_TRUE, BIT3, 3);
    hal_coex_sw_irq_set(BIT5);

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    pst_dmac_vap_btcoex = &(pst_dmac_vap->st_dmac_vap_btcoex);

    pst_dmac_vap_btcoex->en_all_abort_preempt_type = BTCOEX_NOFRAME;
    dmac_btcoex_init_preempt(pst_mac_vap, pst_mac_user, pst_dmac_vap_btcoex->en_all_abort_preempt_type);

    if (OAL_FALSE == dmac_btcoex_check_legacy_sta(pst_mac_vap))
    {
        if (WLAN_LEGACY_VAP_MODE != pst_mac_vap->en_p2p_mode)
        {
            /* Notify Bt the P2P Connected state */
            hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT15, 15);
            hal_coex_sw_irq_set(BIT5);
        }
        OAM_WARNING_LOG3(0, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::ba process skip! vap mode is %d, p2p mode is %d, vap_state: %d.}",
            pst_mac_vap->en_vap_mode, pst_mac_vap->en_p2p_mode, pst_mac_vap->en_vap_state);
        return OAL_SUCC;
    }

    /* ����AP STAģʽ�����ã��������STA */
    pst_dmac_user = (dmac_user_stru *)pst_mac_user;

    pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);

    dmac_btcoex_update_rx_rate_threshold(pst_mac_vap, pst_dmac_user_btcoex_delba);

    pst_mac_device = mac_res_get_dev((oal_uint32)pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::pst_mac_device is null.}");
        return OAL_FAIL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    pst_btcoex_btble_status = &(pst_hal_device->st_btcoex_btble_status);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    pst_hal_device->st_dual_antenna_check_status.bit_bt_on = pst_btcoex_btble_status->un_bt_status.st_bt_status.bit_bt_on;
#endif
    pst_ble_status = &(pst_btcoex_btble_status->un_ble_status.st_ble_status);
    pst_bt_status = &(pst_btcoex_btble_status->un_bt_status.st_bt_status);

    uc_need_delba = OAL_FALSE;
    pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
    pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;

    /* DTS2016010901179 BT��ҵ��ʱ,�ָ�wifi���ƾۺ� */
    if (0 == pst_ble_status->bit_bt_transfer && 0 == pst_ble_status->bit_bt_ba)
    {
        dmac_btcoex_delba_trigger(pst_mac_vap, OAL_FALSE, 0);
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::bt not working, ba size to default.}");
        return OAL_SUCC;
    }

    /* �绰�����½�������ͳ�ƣ�����ĿǰΪ0.5�� */
    if (pst_bt_status->bit_bt_sco)
    {
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* �ر��Զ���Ƶ */
        st_device_freq.uc_set_type = FREQ_SET_MODE;
        st_device_freq.uc_device_freq_enable = OAL_FALSE;
        dmac_config_set_device_freq(pst_mac_vap, 0, (oal_uint8 *)&st_device_freq);
#endif
#endif

        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_1;
        pst_dmac_vap_btcoex->st_dmac_vap_btcoex_rx_statistics.uc_sco_rx_rate_statistics_flag = OAL_TRUE;
        FRW_TIMER_CREATE_TIMER(&(pst_dmac_vap_btcoex->st_dmac_vap_btcoex_rx_statistics.bt_coex_sco_statistics_timer),
                                   dmac_btcoex_sco_rx_rate_statistics_flag_callback,
                                   BTCOEX_SCO_CALCULATE_TIME,
                                   (void *)pst_mac_vap,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
    }
    else if (pst_bt_status->bit_bt_a2dp)
    {
        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
        pst_dmac_vap_btcoex->st_dmac_vap_btcoex_rx_statistics.uc_rx_rate_statistics_flag = OAL_TRUE;
        pst_dmac_vap_btcoex->st_dmac_vap_btcoex_rx_statistics.uc_rx_rate_statistics_timeout = OAL_FALSE;
        FRW_TIMER_CREATE_TIMER(&(pst_dmac_vap_btcoex->st_dmac_vap_btcoex_rx_statistics.bt_coex_statistics_timer),
                                   dmac_btcoex_rx_rate_statistics_flag_callback,
                                   BTCOEX_RX_STATISTICS_TIME,
                                   (void *)pst_mac_vap,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
    }
    else if (pst_ble_status->bit_bt_transfer)
    {
        dmac_alg_cfg_btcoex_state_notify(pst_mac_device, BT_TRANSFER_ON);

        pst_dmac_user_btcoex_delba->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
        pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
    }

    dmac_btcoex_update_ba_size(pst_mac_vap, pst_dmac_user_btcoex_delba, pst_btcoex_btble_status);
    OAM_WARNING_LOG4(0, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::bt ba status:%d, transfer status:%d, bar_size:%d, uc_need_delba:%d}",
                        pst_ble_status->bit_bt_ba,
                        pst_ble_status->bit_bt_transfer,
                        pst_dmac_user_btcoex_delba->uc_ba_size,
                        uc_need_delba);
    dmac_btcoex_delba_trigger(pst_mac_vap, uc_need_delba, pst_dmac_user_btcoex_delba->uc_ba_size);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_btcoex_disassoc_state_syn
 ��������  : ͬ��������mac��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��04��21��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_config_btcoex_disassoc_state_syn(mac_vap_stru *pst_mac_vap)
{
    dmac_vap_stru *pst_dmac_vap;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_vap_btcoex_occupied_stru *pst_dmac_vap_btcoex_occupied;

    if (OAL_FALSE == dmac_btcoex_check_legacy_sta(pst_mac_vap))
    {
        if (WLAN_LEGACY_VAP_MODE != pst_mac_vap->en_p2p_mode)
        {
            /* Notify Bt the P2P Disconnected state */
            hal_set_btcoex_soc_gpreg0(OAL_FALSE, BIT15, 15);
            hal_coex_sw_irq_set(BIT5);
        }
        OAM_WARNING_LOG2(0, OAM_SF_COEX, "{dmac_config_btcoex_disassoc_state_syn::ba process skip! vap mode is %d, p2p mode is %d.}",
                pst_mac_vap->en_vap_mode, pst_mac_vap->en_p2p_mode);
        return OAL_SUCC;
    }
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::pst_dmac_vap is null.}");
        return OAL_FAIL;
    }
    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_dmac_vap_btcoex_occupied = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied);

    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_statistics_timer));
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_low_rate_timer));
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_sco_statistics_timer));
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_occupied->bt_coex_occupied_timer));
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_dmac_vap_btcoex_occupied->bt_coex_priority_timer));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_sco_rx_average_rate_calculate
 ��������  : ͳ��Wifi��ƽ������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��04��06��
    ��    ��   : h00240371
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_rx_average_rate_calculate (dmac_user_btcoex_rx_info_stru *pst_btcoex_wifi_rx_rate_info,
                                                                                oal_uint32 *pul_rx_rate, oal_uint16 *pus_rx_count)
{
    if (0 != pst_btcoex_wifi_rx_rate_info->us_rx_rate_stat_count)
    {
        pst_btcoex_wifi_rx_rate_info->ull_rx_rate_mbps /= 1000;
        *pus_rx_count = pst_btcoex_wifi_rx_rate_info->us_rx_rate_stat_count;
        *pul_rx_rate = (oal_uint32)(pst_btcoex_wifi_rx_rate_info->ull_rx_rate_mbps / pst_btcoex_wifi_rx_rate_info->us_rx_rate_stat_count);
    }
    else
    {
        pst_btcoex_wifi_rx_rate_info->ull_rx_rate_mbps = 0;
        *pus_rx_count = 0;
        return;
    }
    OAL_MEMZERO(pst_btcoex_wifi_rx_rate_info, OAL_SIZEOF(dmac_user_btcoex_rx_info_stru));
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_low_rate_callback
 ��������  : ���ս��ٺ���
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_low_rate_callback(oal_void *p_arg)
{
    mac_vap_stru *pst_vap = (mac_vap_stru *)p_arg;
    mac_device_stru *pst_mac_device;
    dmac_device_stru *pst_dmac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    hal_btcoex_btble_status_stru *pst_btble_status;
    dmac_vap_stru *pst_dmac_vap = (dmac_vap_stru *)p_arg;
    dmac_user_stru *pst_dmac_user;
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;
    oal_uint32 ul_rx_rate = 0;
    oal_uint16 us_rx_count = 0;
    oal_uint32 ul_rate_threshold_min;
    oal_uint32 ul_rate_threshold_max;
    dmac_user_btcoex_rx_info_stru *pst_btcoex_wifi_rx_rate_info;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DBAC, "{dmac_btcoex_low_rate_callback::pst_device[id:0] is NULL}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DBAC, "{dmac_btcoex_low_rate_callback::pst_dmac_user is NULL}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::pst_dmac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);
    pst_btble_status = &(pst_hal_device->st_btcoex_btble_status);
    ul_rate_threshold_min = pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_min;
    ul_rate_threshold_max = pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_max;
    pst_btcoex_wifi_rx_rate_info = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_rx_info);

    if (OAL_FALSE == pst_dmac_user_btcoex_delba->uc_get_addba_req_flag)
    {
        dmac_btcoex_rx_average_rate_calculate(pst_btcoex_wifi_rx_rate_info, &ul_rx_rate, &us_rx_count);

        if (pst_dmac_device->st_dmac_alg_stat.en_dmac_device_distance_enum < DMAC_ALG_TPC_FAR_DISTANCE)
        {
            if (((BTCOEX_RX_WINDOW_SIZE_DECREASE == pst_dmac_user_btcoex_delba->uc_ba_size_tendence)
                    && (ul_rx_rate < pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_min))
                || ((BTCOEX_RX_WINDOW_SIZE_INCREASE == pst_dmac_user_btcoex_delba->uc_ba_size_tendence)
                    && (ul_rx_rate > pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_max))
                || ((BTCOEX_RX_WINDOW_SIZE_DECREASE == pst_dmac_user_btcoex_delba->uc_ba_size_tendence)
                    && (BTCOEX_RX_WINDOW_SIZE_INDEX_3 == pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index)
                    && (ul_rx_rate < (ul_rate_threshold_min + (ul_rate_threshold_max >> 1)))))
            {
                pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = pst_dmac_user_btcoex_delba->uc_ba_size_index;
                dmac_btcoex_update_ba_size(pst_vap, pst_dmac_user_btcoex_delba, pst_btble_status);
                dmac_btcoex_delba_trigger(pst_vap, OAL_TRUE, pst_dmac_user_btcoex_delba->uc_ba_size);
                OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::ba_size change to: %d, rate: %d.}", pst_dmac_user_btcoex_delba->uc_ba_size, ul_rx_rate);
            }
            else
            {
                /* �������оۺϲ��� */
                pst_dmac_user_btcoex_delba->uc_ba_size_index = pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index;
                dmac_btcoex_update_ba_size(pst_vap, pst_dmac_user_btcoex_delba, pst_btble_status);
                OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::ba_size dont change: %d, rate: %d.}", pst_dmac_user_btcoex_delba->uc_ba_size, ul_rx_rate);
            }
        }
    }
    else
    {
        pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = pst_dmac_user_btcoex_delba->uc_ba_size_index;
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::receive addba req before delba.}");
    }

    FRW_TIMER_RESTART_TIMER(&(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics.bt_coex_statistics_timer),
                                BTCOEX_RX_STATISTICS_TIME, OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_bt_low_rate_process
 ��������  : ���ս��ٺ���
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_bt_low_rate_process (mac_vap_stru *pst_vap,
                                                hal_to_dmac_device_stru *pst_hal_device)
{
    oal_uint32 ul_rx_rate = 0;
    oal_uint16 us_rx_count = 0;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    dmac_vap_stru *pst_dmac_vap;
    bt_status_stru *pst_bt_status;
    oal_uint32 ul_rate_threshold_min;
    oal_uint32 ul_rate_threshold_max;
    dmac_user_stru *pst_dmac_user;
    dmac_device_stru* pst_dmac_device;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_user_btcoex_rx_info_stru *pst_dmac_user_btcoex_rx_info;
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;

    if (OAL_FALSE == dmac_btcoex_check_legacy_sta(pst_vap))
    {
        return;
    }
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::pst_dmac_vap null.}");
        return;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::pst_dmac_user null.}");
        return;
    }

    pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::pst_dmac_device null.}");
        return;
    }


    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_dmac_user_btcoex_rx_info = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_rx_info);
    pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);

    /* �ۼӽ������� */
    if (pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_flag)
    {
        if (0 != pst_hal_device->ul_rx_rate)
        {
            pst_dmac_user_btcoex_rx_info->ull_rx_rate_mbps += pst_hal_device->ul_rx_rate;
            pst_dmac_user_btcoex_rx_info->us_rx_rate_stat_count++;
        }
    }
    else
    {
        return;
    }

    /* ����������� */
    if (pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_timeout)
    {
        pst_dmac_vap_btcoex_rx_statistics->uc_rx_rate_statistics_timeout = OAL_FALSE;

        dmac_btcoex_rx_average_rate_calculate(pst_dmac_user_btcoex_rx_info, &ul_rx_rate, &us_rx_count);

        if (g_rx_statistics_print)
        {
            OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::rate: %d, coute: %d.}", ul_rx_rate, us_rx_count);
        }
    }
    else
    {
        return;
    }

    /* ����������� */
    if (pst_dmac_device->st_dmac_alg_stat.en_dmac_device_distance_enum < DMAC_ALG_TPC_FAR_DISTANCE)
    {
        pst_btcoex_btble_status = &(pst_hal_device->st_btcoex_btble_status);
        pst_bt_status = &(pst_btcoex_btble_status->un_bt_status.st_bt_status);
        /* �绰�̶��ۺ� */
        if (pst_bt_status->bit_bt_sco)
        {
            return;
        }
        pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_HOLD;
        pst_dmac_user_btcoex_delba->uc_ba_size_index = pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index;
        ul_rate_threshold_min = pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_min;
        ul_rate_threshold_max = pst_dmac_user_btcoex_delba->ul_rx_rate_threshold_max;

        /* 5G80M���̶ֹ�2�� */
        if ((WLAN_BAND_5G == pst_vap->st_channel.en_band) && (pst_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_40MINUS)
                && (pst_bt_status->bit_bt_a2dp))
        {
            if ((BTCOEX_RX_WINDOW_SIZE_INDEX_3 == pst_dmac_user_btcoex_delba->uc_ba_size_index)
                    && (ul_rx_rate < (ul_rate_threshold_min + (ul_rate_threshold_max >> 1))))
            {
                pst_dmac_user_btcoex_delba->uc_ba_size_index--;
                pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
            }
            else if (pst_dmac_user_btcoex_delba->uc_ba_size_index < BTCOEX_RX_WINDOW_SIZE_INDEX_2)
            {
                pst_dmac_user_btcoex_delba->uc_ba_size_index++;
                pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_INCREASE;
            }
        }
        else
        {
            switch (pst_dmac_user_btcoex_delba->uc_ba_size_index)
            {
                case BTCOEX_RX_WINDOW_SIZE_INDEX_3:
                    if (ul_rx_rate < (ul_rate_threshold_min + (ul_rate_threshold_max >> 1)))
                    {
                        pst_dmac_user_btcoex_delba->uc_ba_size_index--;
                        pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
                    }
                    break;
                case BTCOEX_RX_WINDOW_SIZE_INDEX_2:
                    if (ul_rx_rate < ul_rate_threshold_min)
                    {
                        pst_dmac_user_btcoex_delba->uc_ba_size_index--;
                        pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
                    }
                    break;
                case BTCOEX_RX_WINDOW_SIZE_INDEX_1:
                    if (ul_rx_rate < ul_rate_threshold_min)
                    {
                        pst_dmac_user_btcoex_delba->uc_ba_size_index--;
                        pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
                    }
                    else if (ul_rx_rate > ul_rate_threshold_max)
                    {
                        pst_dmac_user_btcoex_delba->uc_ba_size_index++;
                        pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_INCREASE;
                    }
                    break;
                case BTCOEX_RX_WINDOW_SIZE_INDEX_0:
                    if (ul_rx_rate > ul_rate_threshold_max)
                    {
                        pst_dmac_user_btcoex_delba->uc_ba_size_index++;
                        pst_dmac_user_btcoex_delba->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_INCREASE;
                    }
                    break;
                default:
                    OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::ba_size_index error: %d.}",
                                pst_dmac_user_btcoex_delba->uc_ba_size_index);
                    break;
            }
        }

        if (BTCOEX_RX_WINDOW_SIZE_HOLD != pst_dmac_user_btcoex_delba->uc_ba_size_tendence)
        {
            dmac_btcoex_update_ba_size(pst_vap, pst_dmac_user_btcoex_delba, pst_btcoex_btble_status);
            dmac_btcoex_delba_trigger(pst_vap, OAL_FALSE, pst_dmac_user_btcoex_delba->uc_ba_size);

            OAM_WARNING_LOG3(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::ba_size will change to: %d in 5s, rate: %d, count: %d.}",
                                pst_dmac_user_btcoex_delba->uc_ba_size, ul_rx_rate, us_rx_count);

            pst_dmac_user_btcoex_delba->uc_get_addba_req_flag = OAL_FALSE;

            FRW_TIMER_STOP_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_statistics_timer));
            FRW_TIMER_CREATE_TIMER(&(pst_dmac_vap_btcoex_rx_statistics->bt_coex_low_rate_timer),
                                           dmac_btcoex_low_rate_callback,
                                           BTCOEX_RX_LOW_RATE_TIME,
                                           (oal_void *)pst_vap,
                                           OAL_FALSE,
                                           OAM_MODULE_ID_DMAC,
                                           0);
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_release_rx_prot
 ��������  : ������ڹؼ�֡�Ĳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��27��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_release_rx_prot(mac_vap_stru *pst_mac_vap, oal_uint8 uc_data_type)
{
    mac_device_stru *pst_mac_device;
    bt_status_stru              *pst_bt_status;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_release_rx_prot::pst_mac_devicenull.}");
        return;
    }
    pst_bt_status = &(pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status);
    if (!pst_bt_status->bit_bt_on || (uc_data_type == MAC_DATA_BUTT))
    {
        return;
    }
    /* �յ�EAPOL֡�Ժ�ˢ��occupied_period�Ա�֤BT������ */
    if ((uc_data_type == MAC_DATA_EAPOL) && !(pst_bt_status->bit_bt_sco))
    {
        hal_set_btcoex_occupied_period(0);
    }
    else if ((MAC_DATA_EAPOL == uc_data_type)
          || (MAC_DATA_DHCP == uc_data_type)
          || (MAC_DATA_ARP_RSP == uc_data_type))
    {
        dmac_btcoex_wlan_priority_set(pst_mac_vap, 0, 0);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_tx_vip_frame
 ��������  : ������ڹؼ�֡�ķ��ͱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��7��13��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_tx_vip_frame(hal_to_dmac_device_stru *pst_hal_device, mac_vap_stru *pst_mac_vap, oal_dlist_head_stru *pst_tx_dscr_list_hdr)
{
    oal_dlist_head_stru    *pst_dscr_entry;
    hal_tx_dscr_stru       *pst_dscr_temp;
    oal_uint8               uc_data_type;
    oal_uint8               uc_coex_data_type;    // ֪ͨBT������������,�Ĵ���ֻ��2bit
    bt_status_stru         *pst_bt_status;

    /* EAPOL֡��DHCP��ARP֡�Ĺ��汣�� */
    pst_bt_status = &(pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status);
    if (!pst_bt_status->bit_bt_on
#ifdef _PRE_WLAN_FEATURE_LTECOEX
        && !pst_hal_device->ul_lte_coex_status
#endif
        )
    {
        return;
    }

    OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, pst_tx_dscr_list_hdr)
    {
        pst_dscr_temp = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        uc_data_type = mac_get_data_type(pst_dscr_temp->pst_skb_start_addr);
        if (uc_data_type > MAC_DATA_EAPOL)
        {
            continue;
        }
        switch (uc_data_type)
        {
            case MAC_DATA_DHCP:
                uc_coex_data_type = 1;
                dmac_btcoex_wlan_priority_set(pst_mac_vap, 1, BTCOEX_PRIO_TIMEOUT_100MS);
                break;

            case MAC_DATA_ARP_REQ:
            case MAC_DATA_ARP_RSP:
                uc_coex_data_type = 2;
                dmac_btcoex_wlan_priority_set(pst_mac_vap, 1, BTCOEX_PRIO_TIMEOUT_60MS);
                break;

            case MAC_DATA_EAPOL:
                uc_coex_data_type = 3;
                /* Ϊ���p2p��Գɹ��ʣ��ڷ�BT�绰�����£�����EAPOL֡�շ� */
                if (!(pst_bt_status->bit_bt_sco))
                {
                    hal_set_btcoex_occupied_period(60000);//60ms
                }
                else
                {
                    /* �������priority */
                    dmac_btcoex_wlan_priority_set(pst_mac_vap, 1, BTCOEX_PRIO_TIMEOUT_100MS);
                }
                break;

            default:
                uc_coex_data_type = 0;
        }
        hal_set_btcoex_soc_gpreg0(uc_coex_data_type, BIT10 | BIT11 | BIT12, 10);   // ���͹ؼ�֡
        hal_coex_sw_irq_set(BIT5);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_btcoex_bt_low_rate_process
 ��������  : ���ս��ٺ���
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_btcoex_sco_rx_rate_process (mac_vap_stru *pst_vap,
                                                hal_to_dmac_device_stru *pst_hal_device)
{
    dmac_vap_stru *pst_dmac_vap;
    dmac_user_stru *pst_dmac_user;
    dmac_vap_btcoex_rx_statistics_stru *pst_dmac_vap_btcoex_rx_statistics;
    dmac_user_btcoex_rx_info_stru *pst_dmac_user_btcoex_sco_rx_info;


    if (OAL_FALSE == dmac_btcoex_check_legacy_sta(pst_vap))
    {
        return;
    }
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_rx_rate_process::pst_dmac_vap null.}");
        return;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_vap->uc_assoc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_sco_rx_rate_process::pst_dmac_user null.}");
        return;
    }
    pst_dmac_vap_btcoex_rx_statistics = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_rx_statistics);
    pst_dmac_user_btcoex_sco_rx_info = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_sco_rx_info);

    /* �ۼӽ������� */
    if (pst_dmac_vap_btcoex_rx_statistics->uc_sco_rx_rate_statistics_flag)
    {
        if (0 != pst_hal_device->ul_rx_rate)
        {
            pst_dmac_user_btcoex_sco_rx_info->ull_rx_rate_mbps += pst_hal_device->ul_rx_rate;
            pst_dmac_user_btcoex_sco_rx_info->us_rx_rate_stat_count++;
        }
    }
    else
    {
        return;
    }

}
#endif /* end of _PRE_WLAN_FEATURE_COEXIST_BT */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

