/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_sme_sta.c
  �� �� ��   : ����
  ��    ��   : y00184180
  ��������   : 2013��6��28��
  ����޸�   :
  ��������   : HMAC�� STAģʽSME�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��28��
    ��    ��   : y00184180
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "mac_regdomain.h"
#include "hmac_main.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_mgmt_sta.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"

#ifdef _PRE_WIFI_DMT
#include "hal_witp_dmt_if.h"
#include "dmt_stub.h"
#include "frame_public.h"
#endif
#include "hmac_p2p.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "hmac_proxysta.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_SME_STA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
    g_handle_rsp_func_sta: ������sme����Ϣ
*****************************************************************************/
OAL_STATIC hmac_sme_handle_rsp_func g_handle_rsp_func_sta[HMAC_SME_RSP_BUTT] =
{
    hmac_handle_scan_rsp_sta,
    hmac_handle_join_rsp_sta,
    hmac_handle_auth_rsp_sta,
    hmac_handle_asoc_rsp_sta,
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

OAL_STATIC oal_void  hmac_cfg80211_scan_comp_cb(void  *p_scan_record);
oal_void  hmac_send_rsp_to_sme_sta(hmac_vap_stru *pst_hmac_vap, hmac_sme_rsp_enum_uint8 en_type, oal_uint8 *puc_msg);


/*****************************************************************************
 �� �� ��  : hmac_prepare_scan_req
 ��������  : ׼��ɨ������
 �������  : ul_chip_ver: оƬ�汾
             pc_desired_ssid: mib�����õ�ssid
 �������  : pst_scan_params: ɨ�����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_prepare_scan_req(mac_scan_req_stru *pst_scan_params, oal_int8 *pc_desired_ssid)
{

#ifndef  _PRE_WLAN_FPGA_DIGITAL
    oal_uint8       uc_chan_idx;
    oal_uint32      ul_ret;
    oal_uint8       uc_2g_chan_num = 0;
    oal_uint8       uc_5g_chan_num = 0;
    oal_uint8       uc_chan_number;
#endif

    OAL_MEMZERO(pst_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    /* ���ó�ʼɨ������Ĳ��� */
    pst_scan_params->en_bss_type         = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_scan_params->en_scan_type        = WLAN_SCAN_TYPE_ACTIVE;
    pst_scan_params->us_scan_time        = WLAN_DEFAULT_ACTIVE_SCAN_TIME;
    pst_scan_params->uc_probe_delay      = 0;
    pst_scan_params->uc_scan_func        = MAC_SCAN_FUNC_BSS;               /* Ĭ��ɨ��bss */
    pst_scan_params->p_fn_cb             = hmac_cfg80211_scan_comp_cb;      /* ʹ��cfg80211�ӿڻص�����Ϊut/dmt��������ӿ���� */
    pst_scan_params->uc_max_send_probe_req_count_per_channel = WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL;

    /* ���ó�ʼɨ�������ssid */
    /* ��ʼɨ������ָֻ��1��ssid, Ҫô��ͨ��, Ҫô��mibֵ */
    if ('\0' == pc_desired_ssid[0])
    {
        pst_scan_params->ast_mac_ssid_set[0].auc_ssid[0] = '\0';   /* ͨ��ssid */
    }
    else
    {
        oal_memcopy(pst_scan_params->ast_mac_ssid_set[0].auc_ssid, pc_desired_ssid, OAL_STRLEN(pc_desired_ssid) + 1);    /* copy�����ַ�����β��0 */
    }

    pst_scan_params->uc_ssid_num = 1;

    /* ���ó�ʼɨ�������bssid */
    /* ��ʼɨ������ָֻ��1��bssid��Ϊ�㲥��ַ */
    oal_set_mac_addr(pst_scan_params->auc_bssid[0], BROADCAST_MACADDR);
    pst_scan_params->uc_bssid_num = 1;

#ifndef  _PRE_WLAN_FPGA_DIGITAL

#ifdef _PRE_WIFI_DMT
    if (0 == g_ul_dmt_scan_flag)
    {
        OAL_IO_PRINT("2G scan \n");
        for (uc_chan_idx = 0; uc_chan_idx < 2; uc_chan_idx++)
#else
        /* 2G��ʼɨ���ŵ�, ȫ�ŵ�ɨ�� */
        for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
#endif
        {
            /* �ж��ŵ��ǲ����ڹ������� */
            ul_ret = mac_is_channel_idx_valid(WLAN_BAND_2G, uc_chan_idx);
            if (OAL_SUCC == ul_ret)
            {
                mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_number);

                pst_scan_params->ast_channel_list[uc_2g_chan_num].uc_chan_number = uc_chan_number;
                pst_scan_params->ast_channel_list[uc_2g_chan_num].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[uc_2g_chan_num].uc_idx         = uc_chan_idx;
                pst_scan_params->uc_channel_nums++;
                uc_2g_chan_num++;
            }
        }

#ifdef _PRE_WIFI_DMT
    }
#endif

    OAM_INFO_LOG1(0, OAM_SF_SCAN, "{hmac_prepare_scan_req::after regdomain filter, the 2g total channel num is %d", uc_2g_chan_num);

#ifdef _PRE_WIFI_DMT
    if (1 == g_ul_dmt_scan_flag)
    {
        OAL_IO_PRINT("5G scan \n");
        for (uc_chan_idx = 0; uc_chan_idx < 2; uc_chan_idx++)
#else
    /* 5G��ʼɨ���ŵ�, ȫ�ŵ�ɨ�� */
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
#endif
    {
        /* �ж��ŵ��ǲ����ڹ������� */
        ul_ret = mac_is_channel_idx_valid(WLAN_BAND_5G, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_chan_idx, &uc_chan_number);

            pst_scan_params->ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].uc_chan_number = uc_chan_number;
            pst_scan_params->ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].en_band        = WLAN_BAND_5G;
            pst_scan_params->ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].uc_idx         = uc_chan_idx;
            pst_scan_params->uc_channel_nums++;
            uc_5g_chan_num++;
        }
    }
#ifdef _PRE_WIFI_DMT
    }
#endif
    OAM_INFO_LOG1(0, OAM_SF_SCAN, "{hmac_prepare_scan_req::after regdomain filter, the 5g total channel num is %d", uc_5g_chan_num);
#endif
}
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0))
/*****************************************************************************
 �� �� ��  : hmac_cfg80211_dump_survey
 ��������  :���ں��ϱ��ŵ�ͳ�ƽ��
 �������  :

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��30��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32   hmac_cfg80211_dump_survey(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_netdev,
                                      oal_int32 l_idx, oal_survey_info_stru *pst_info)
{
    mac_vap_stru             *pst_mac_vap;
    hmac_device_stru         *pst_hmac_dev;
    mac_scan_chan_stats_stru *pst_record;

    if ((OAL_PTR_NULL == pst_wiphy) || (OAL_PTR_NULL == pst_netdev) || (OAL_PTR_NULL == pst_info) || l_idx < 0)
    {
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{hmac_cfg80211_dump_survey::pst_wiphy = %x, pst_netdev = %x, pst_info = %x l_idx=%d!}",
                       pst_wiphy, pst_netdev, pst_info, l_idx);
        return -OAL_EINVAL;
    }

    oal_memset(pst_info, 0, OAL_SIZEOF(oal_survey_info_stru));

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_netdev);
    if (!pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_cfg80211_dump_survey::pst_mac_vap = NULL}");
        return -OAL_EINVAL;
    }

    pst_hmac_dev = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (!pst_hmac_dev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_cfg80211_dump_survey::pst_hmac_dev = NULL}");
        return -OAL_EINVAL;
    }

    if (pst_hmac_dev->st_scan_mgmt.en_is_scanning)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_cfg80211_dump_survey::drop request while scan running}");
        return -OAL_EINVAL;
    }

    pst_record = pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.ast_chan_results;

    if (l_idx >= pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.uc_chan_numbers)
    {
        return -ENOENT;
    }
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,0,0))
    pst_info->time          = pst_record[l_idx].ul_total_stats_time_us / 1000;
    pst_info->time_busy     = (pst_record[l_idx].ul_total_stats_time_us -
                                      pst_record[l_idx].ul_total_free_time_20M_us) / 1000;
    pst_info->time_ext_busy = 0;
    pst_info->time_rx = pst_record[l_idx].ul_total_recv_time_us / 1000;
    pst_info->time_tx = pst_record[l_idx].ul_total_send_time_us / 1000;

    pst_info->filled = SURVEY_INFO_TIME
                     | SURVEY_INFO_TIME_BUSY
                     | SURVEY_INFO_TIME_RX
                     | SURVEY_INFO_TIME_TX;
#else
    pst_info->channel_time          = pst_record[l_idx].ul_total_stats_time_us / 1000;
    pst_info->channel_time_busy     = (pst_record[l_idx].ul_total_stats_time_us -
                                      pst_record[l_idx].ul_total_free_time_20M_us) / 1000;
    pst_info->channel_time_ext_busy = 0;
    pst_info->channel_time_rx = pst_record[l_idx].ul_total_recv_time_us / 1000;
    pst_info->channel_time_tx = pst_record[l_idx].ul_total_send_time_us / 1000;

    pst_info->filled = SURVEY_INFO_CHANNEL_TIME
                     | SURVEY_INFO_CHANNEL_TIME_BUSY
                     | SURVEY_INFO_CHANNEL_TIME_RX
                     | SURVEY_INFO_CHANNEL_TIME_TX;
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4,0,0)) */

    if (pst_record[l_idx].uc_free_power_cnt && pst_record[l_idx].s_free_power_stats_20M < 0)
    {
        pst_info->noise = pst_record[l_idx].s_free_power_stats_20M / pst_record[l_idx].uc_free_power_cnt;
        pst_info->filled |= SURVEY_INFO_NOISE_DBM;
    }

    pst_info->channel = oal_ieee80211_get_channel(pst_wiphy,
            oal_ieee80211_channel_to_frequency(pst_record[l_idx].uc_channel_number,
                                                   mac_get_band_by_channel_num(pst_record[l_idx].uc_channel_number)));
    return 0;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_cfg80211_scan_comp_cb
 ��������  : wpa_supplicant�·���ɨ������Ļص����������ڶ�ɨ�����ʱ�Խ���Ĵ���
 �������  : void  *p_scan_record��ɨ���¼������ɨ�跢������Ϣ��ɨ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_cfg80211_scan_comp_cb(void  *p_scan_record)
{
    hmac_scan_record_stru           *pst_scan_record = (hmac_scan_record_stru *)p_scan_record;
    hmac_vap_stru                   *pst_hmac_vap = OAL_PTR_NULL;
    hmac_scan_rsp_stru               st_scan_rsp;

    /* ��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_scan_record->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_cfg80211_scan_comp_cb::pst_hmac_vap is null.");
        return;
    }

    /* �ϱ�ɨ�����ṹ���ʼ�� */
    OAL_MEMZERO(&st_scan_rsp, OAL_SIZEOF(st_scan_rsp));

    st_scan_rsp.uc_result_code = pst_scan_record->en_scan_rsp_status;

    /* ɨ��������sme */
    hmac_send_rsp_to_sme_sta(pst_hmac_vap, HMAC_SME_SCAN_RSP, (oal_uint8 *)&st_scan_rsp);

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_cfg80211_prepare_scan_req_sta
 ��������  : �����ں��·���ɨ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��10��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_cfg80211_prepare_scan_req_sta(mac_vap_stru *pst_mac_vap, mac_scan_req_stru *pst_scan_params, oal_int8 *puc_param)
{
    oal_uint8                       uc_loop;            /* forѭ�������±� */
    oal_uint8                       uc_channel_number;  /* �ŵ��� */
    oal_uint8                       uc_channel_idx = 0;     /* �ŵ������� */
    mac_cfg80211_scan_param_stru   *pst_cfg80211_scan_param;
    mac_device_stru                *pst_mac_device;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_vap_stru                   *pst_mac_vap_temp;
#endif
    oal_uint32                      ul_ret;
    oal_bool_enum_uint8             en_scan_when_go_up = OAL_FALSE;
    oal_uint8                       uc_chan_num_2g = 0;
    oal_uint8                       uc_chan_num_5g = 0;

    pst_cfg80211_scan_param = (mac_cfg80211_scan_param_stru *)puc_param;

	/* �ⲿ�Ѿ�zero */
    //OAL_MEMZERO(pst_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    pst_scan_params->en_bss_type  = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_scan_params->en_scan_type = pst_cfg80211_scan_param->en_scan_type;

    /* ����ɨ��ʱ�� */
    if (WLAN_SCAN_TYPE_ACTIVE == pst_scan_params->en_scan_type)
    {
        pst_scan_params->us_scan_time = WLAN_DEFAULT_ACTIVE_SCAN_TIME;
    }
    else
    {
        pst_scan_params->us_scan_time = WLAN_DEFAULT_PASSIVE_SCAN_TIME;
    }

    pst_scan_params->uc_probe_delay      = 0;
    pst_scan_params->uc_scan_func        = MAC_SCAN_FUNC_BSS;               /* Ĭ��ɨ��bss */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0)
    pst_scan_params->uc_scan_func        |= MAC_SCAN_FUNC_MEAS|MAC_SCAN_FUNC_STATS;
#endif
    pst_scan_params->p_fn_cb             = hmac_cfg80211_scan_comp_cb;      /* ɨ����ɻص����� */
    pst_scan_params->uc_max_scan_count_per_channel    = 2;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_device_id, OAM_SF_SCAN,
                         "{hmac_cfg80211_prepare_scan_req_sta::mac_res_get_dev fail.device_id:%u}",pst_mac_vap->uc_device_id);
        return;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* p2p Go����ɨ��ʱ����ʹ��p2p device�豸���� */
    if (WLAN_P2P_DEV_MODE == pst_mac_vap->en_p2p_mode)
    {
        ul_ret = mac_device_find_up_p2p_go(pst_mac_device, &pst_mac_vap_temp);
        if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_mac_vap_temp))
        {
            en_scan_when_go_up    = OAL_TRUE;
        }
    }
#endif  /* _PRE_WLAN_FEATURE_P2P */

    if (OAL_TRUE ==  en_scan_when_go_up ||
        MAC_VAP_STATE_UP ==  pst_mac_vap->en_vap_state ||
        MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state ||
        (MAC_VAP_STATE_STA_LISTEN == pst_mac_vap->en_vap_state && pst_mac_vap->us_user_nums > 0))
    {
        pst_scan_params->uc_max_scan_count_per_channel    = 1;
    }

    if ('\0' == pst_cfg80211_scan_param->st_ssids[0].auc_ssid[0])
    {
        pst_scan_params->ast_mac_ssid_set[0].auc_ssid[0] = '\0';   /* ͨ��ssid */

        /* ����ϲ�δ�·�ָ��ssid�������Ĭ��ֵ(��������bcm����Ϊ����Ӧ����) */
        pst_scan_params->uc_max_send_probe_req_count_per_channel = WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL;
    }
    else
    {
        for (uc_loop = 0; uc_loop < pst_cfg80211_scan_param->l_ssid_num; uc_loop++)
        {
            oal_memcopy(pst_scan_params->ast_mac_ssid_set[uc_loop].auc_ssid, pst_cfg80211_scan_param->st_ssids[uc_loop].auc_ssid,
                        pst_cfg80211_scan_param->st_ssids[uc_loop].uc_ssid_len);
            pst_scan_params->ast_mac_ssid_set[uc_loop].auc_ssid[pst_cfg80211_scan_param->st_ssids[uc_loop].uc_ssid_len] = '\0';   /* ssidĩβ��'\0' */
        }

        /* ����ϲ��·���ָ��ssid����ÿ��ɨ�跢�͵�probe req֡�ĸ���Ϊ�·���ssid���� */
        pst_scan_params->uc_max_send_probe_req_count_per_channel = (oal_uint8)pst_cfg80211_scan_param->l_ssid_num;

        if((pst_scan_params->uc_max_send_probe_req_count_per_channel > 3)
           && (WLAN_SCAN_TYPE_ACTIVE == pst_scan_params->en_scan_type))
        {
            /* ���ָ��SSID��������3��,��������ͳ�ʱʱ��Ϊ40ms,Ĭ�Ϸ��͵ȴ���ʱ20ms */
            pst_scan_params->us_scan_time = WLAN_LONG_ACTIVE_SCAN_TIME;
        }
    }

    pst_scan_params->uc_ssid_num = (oal_uint8)pst_cfg80211_scan_param->l_ssid_num;

    oal_set_mac_addr(pst_scan_params->auc_bssid[0], BROADCAST_MACADDR);
    pst_scan_params->uc_bssid_num = 1;  /* ��ʼɨ������ָ��1��bssid��Ϊ�㲥��ַ */

#if((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)&&(_PRE_TEST_MODE_UT != _PRE_TEST_MODE))
    /* DTS:DTS2015102705738, ���51˫оƬ, chip1ֻ֧��2G, chip0ֻ֧��5G, ��Ҫ���ݸ���֧��Ƶ��ѡ��֧�ֵ��ŵ�����ɨ��  */
    //if (WLAN_BAND_2G == pst_mac_device->en_max_band || WLAN_BAND_BUTT == pst_mac_device->en_max_band)
    /* STAUTģʽ�£�������Э��ģʽʱΪ WLAN_BAND_BUTT, �Ի���ȫ�ŵ�ɨ��,���ﰴ��оƬ��ɨ��2G/5G�����ϲ�Ʒ��̬ */
#ifndef _PRE_WLAN_FEATURE_SINGLE_CHIP_DUAL_BAND
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP
    if(WLAN_DOUBLE_CHIP_2G_ID == pst_mac_vap->uc_chip_id)
#else
    if(WLAN_SINGLE_CHIP_2G_ID == pst_mac_vap->uc_chip_id)
#endif
#endif
#endif

    {
        /* 2G��ʼɨ���ŵ� */
        for (uc_loop = 0; uc_loop < pst_cfg80211_scan_param->uc_num_channels_2G; uc_loop++)
        {
            uc_channel_number = (oal_uint8)pst_cfg80211_scan_param->pul_channels_2G[uc_loop];

            /* �ж��ŵ��ǲ����ڹ������� */
            ul_ret = mac_is_channel_num_valid(WLAN_BAND_2G, uc_channel_number);
            if (OAL_SUCC == ul_ret)
            {
                ul_ret = mac_get_channel_idx_from_num(WLAN_BAND_2G, uc_channel_number, &uc_channel_idx);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{WLAN_BAND_2G::hmac_cfg80211_prepare_scan_req_sta::mac_get_channel_idx_from_num fail. channel_number: %u.}", uc_channel_number);
                }

                pst_scan_params->ast_channel_list[uc_chan_num_2g].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[uc_chan_num_2g].uc_chan_number = uc_channel_number;
                pst_scan_params->ast_channel_list[uc_chan_num_2g].uc_idx         = uc_channel_idx;

                pst_scan_params->uc_channel_nums++;
                uc_chan_num_2g++;
            }
        }
    }

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)&&(_PRE_TEST_MODE_UT != _PRE_TEST_MODE))
#ifndef _PRE_WLAN_FEATURE_SINGLE_CHIP_DUAL_BAND
    else
#endif
#endif
    {
        /* 5G��ʼɨ���ŵ�*/
        for (uc_loop = 0; uc_loop < pst_cfg80211_scan_param->uc_num_channels_5G; uc_loop++)
        {
            uc_channel_number = (oal_uint8)pst_cfg80211_scan_param->pul_channels_5G[uc_loop];

            /* �ж��ŵ��ǲ����ڹ�������  */
            ul_ret = mac_is_channel_num_valid(WLAN_BAND_5G, uc_channel_number);
            if (OAL_SUCC == ul_ret)
            {
                ul_ret = mac_get_channel_idx_from_num(WLAN_BAND_5G, uc_channel_number, &uc_channel_idx);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{WLAN_BAND_5G::hmac_cfg80211_prepare_scan_req_sta::mac_get_channel_idx_from_num fail. channel_number: %u}", uc_channel_number);
                }


                pst_scan_params->ast_channel_list[uc_chan_num_2g + uc_chan_num_5g].en_band        = WLAN_BAND_5G;
                pst_scan_params->ast_channel_list[uc_chan_num_2g + uc_chan_num_5g].uc_chan_number = uc_channel_number;
                pst_scan_params->ast_channel_list[uc_chan_num_2g + uc_chan_num_5g].uc_idx         = uc_channel_idx;

                pst_scan_params->uc_channel_nums++;
                uc_chan_num_5g++;
            }
        }
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* WLAN/P2P ����ʱ���ж��Ƿ�p2p0 ����ɨ�� */
    pst_scan_params->bit_is_p2p0_scan = pst_cfg80211_scan_param->bit_is_p2p0_scan;
    if (pst_cfg80211_scan_param->bit_is_p2p0_scan)
    {
        pst_scan_params->en_bss_type = 0;
    }
#endif  /* _PRE_WLAN_FEATURE_P2P */
}

/*****************************************************************************
 �� �� ��  : hmac_prepare_join_req
 ��������  : ׼����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_prepare_join_req(hmac_join_req_stru *pst_join_req, mac_bss_dscr_stru *pst_bss_dscr)
{
    OAL_MEMZERO(pst_join_req, OAL_SIZEOF(hmac_join_req_stru));

    oal_memcopy(&(pst_join_req->st_bss_dscr), pst_bss_dscr, OAL_SIZEOF(mac_bss_dscr_stru));

    pst_join_req->us_join_timeout = WLAN_JOIN_START_TIMEOUT;
    pst_join_req->us_probe_delay  = WLAN_PROBE_DELAY_TIME;
}

/*****************************************************************************
 �� �� ��  : hmac_prepare_auth_req
 ��������  : ׼����֤����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_prepare_auth_req(mac_vap_stru *pst_mac_vap, hmac_auth_req_stru *pst_auth_req)
{
    OAL_MEMZERO(pst_auth_req, OAL_SIZEOF(hmac_auth_req_stru));

    /* ����AUTH���Ĵ����󣬽���ʱʱ����� */
    pst_auth_req->us_timeout = (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticationResponseTimeOut >> 1;
}

/*****************************************************************************
 �� �� ��  : hmac_prepare_asoc_req
 ��������  : ׼����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_prepare_asoc_req(mac_vap_stru *pst_mac_vap, hmac_asoc_req_stru *pst_asoc_req)
{
    OAL_MEMZERO(pst_asoc_req, OAL_SIZEOF(hmac_asoc_req_stru));

    /* ����ASOC���Ĵ����󣬽���ʱʱ����� */
    pst_asoc_req->us_assoc_timeout = (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationResponseTimeOut >> 1;
}

/*****************************************************************************
 �� �� ��  : hmac_sta_initiate_scan
 ��������  : STA�����ʼɨ��
 �������  : pst_hmac_vap: HMAC VAP
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_sta_initiate_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32              ul_ret;
    mac_scan_req_stru       st_scan_params;
    hmac_vap_stru          *pst_hmac_vap;
    oal_int8               *pc_desired_ssid;

#ifdef  _PRE_WLAN_FPGA_DIGITAL
    oal_uint8               uc_chan_number = 0;
    mac_device_stru        *pst_mac_device;
#endif

#ifdef  _PRE_WLAN_FEATURE_P2P
    mac_device_stru        *pst_mac_device;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_sta_initial_scan: pst_mac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������vap������ */
    if (WLAN_VAP_MODE_CONFIG == pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_sta_initiate_scan::this is config vap! can't get info.}");
        return OAL_FAIL;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_initiate_scan::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pc_desired_ssid = (oal_int8 *)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;
    hmac_prepare_scan_req(&st_scan_params, pc_desired_ssid);
#ifdef _PRE_WLAN_FEATURE_P2P//TBD:P2P BUG
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_initial_scan: pst_mac_device is null device id[%d].}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    st_scan_params.bit_is_p2p0_scan = puc_param[0];
    /* ��¼ɨ�������Ϣ��device�ṹ�� */
    oal_memcopy(&(pst_mac_device->st_scan_params), &st_scan_params, OAL_SIZEOF(mac_scan_req_stru));
#endif  /* _PRE_WLAN_FEATURE_P2P */

#ifdef _PRE_WLAN_FPGA_DIGITAL
    /* ��ʼɨ���б���0 */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_initiate_scan::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ֶ�ͨ������ֻɨ��1���ŵ� */
    st_scan_params.ast_channel_list[0].en_band = pst_hmac_vap->st_vap_base_info.st_channel.en_band;
    mac_get_channel_num_from_idx(pst_hmac_vap->st_vap_base_info.st_channel.en_band, 0, &uc_chan_number);
    st_scan_params.ast_channel_list[0].uc_chan_number = uc_chan_number;
    st_scan_params.uc_channel_nums++;
    /*���ֶ�ͨ������ʹ�����õ��ŵ���Ƚ���ɨ�裬����տ�ֻʹ��20mƵ��ɨ��*/
    st_scan_params.ast_channel_list[0].en_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
#endif

    /* ״̬������: hmac_scan_proc_scan_req_event */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_SCAN_REQ, (oal_void *)(&st_scan_params));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_initiate_scan::hmac_fsm_call_func_sta fail[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_cfg80211_check_can_start_sched_scan
 ��������  : ����Ƿ������������ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_cfg80211_check_can_start_sched_scan(mac_vap_stru *pst_mac_vap)
{
    hmac_device_stru      *pst_hmac_device;
    mac_vap_stru          *pst_mac_vap_tmp = OAL_PTR_NULL;
    oal_uint32             ul_ret = OAL_SUCC;

    /* ��ȡmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_cfg80211_check_can_start_sched_scan::pst_hmac_device[%d] null.}",
                         pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���vap��ģʽ����STA���򷵻أ���֧������ģʽ��vap�ĵ���ɨ�� */
    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_cfg80211_check_can_start_sched_scan::vap mode[%d] don't support sched scan.}",
                         pst_mac_vap->en_vap_mode);

        pst_hmac_device->st_scan_mgmt.pst_sched_scan_req = OAL_PTR_NULL;
        pst_hmac_device->st_scan_mgmt.en_sched_scan_complete = OAL_TRUE;
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    /* ������ڵ�ǰdevice����up��vap������������ɨ�� */
    ul_ret = mac_device_find_up_vap(pst_hmac_device->pst_device_base_info, &pst_mac_vap_tmp);
    if (OAL_SUCC == ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_cfg80211_check_can_start_sched_scan::exist up vap, don't start sched scan.}");

        pst_hmac_device->st_scan_mgmt.pst_sched_scan_req = OAL_PTR_NULL;
        pst_hmac_device->st_scan_mgmt.en_sched_scan_complete = OAL_TRUE;
        return OAL_ERR_CODE_CONFIG_BUSY;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_cfg80211_start_sched_scan
 ��������  : �����ں��·���������ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_cfg80211_start_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_vap_stru                       *pst_hmac_vap;
    mac_pno_scan_stru                   *pst_cfg80211_pno_scan_params;
    mac_pno_scan_stru                    st_pno_scan_params;
    oal_uint32                           ul_ret = OAL_FAIL;
    oal_bool_enum_uint8                  en_is_random_mac_addr_scan;
    hmac_device_stru                     *pst_hmac_device;

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_cfg80211_start_sched_scan::input null %p %p.}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ϲ㴫���ǵ�ַ�������Ҫȡֵ��ȡ��������pnoɨ��������ڵĵ�ַ */
    pst_cfg80211_pno_scan_params = (mac_pno_scan_stru *)(*(oal_uint *)puc_param);

    /* ��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_cfg80211_start_sched_scan::pst_hmac_vap null.}");

        OAL_MEM_FREE(pst_cfg80211_pno_scan_params, OAL_TRUE);
        return OAL_ERR_CODE_PTR_NULL;
    }
        /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_cfg80211_start_sched_scan::device id[%d],hmac_device null.}",pst_hmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* �����ϲ��·���pnoɨ����� */
    oal_memcopy(&st_pno_scan_params, pst_cfg80211_pno_scan_params, OAL_SIZEOF(mac_pno_scan_stru));

    /* �ͷű����ڴ�ص��ڴ� */
    OAL_MEM_FREE(pst_cfg80211_pno_scan_params, OAL_TRUE);

    /* ��⵱ǰdevice�Ƿ������������ɨ�� */
    ul_ret = hmac_cfg80211_check_can_start_sched_scan(pst_mac_vap);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* ����PNO����ɨ�����ʱ������н���ϱ������ϱ�ɨ�����Ļص����� */
    st_pno_scan_params.p_fn_cb = hmac_cfg80211_scan_comp_cb;

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    en_is_random_mac_addr_scan = g_st_wlan_customize.uc_random_mac_addr_scan;
#else
    en_is_random_mac_addr_scan = pst_hmac_device->st_scan_mgmt.en_is_random_mac_addr_scan;
#endif

    /* ���÷��͵�probe req֡��Դmac addr */
    st_pno_scan_params.en_is_random_mac_addr_scan = en_is_random_mac_addr_scan;
    hmac_scan_set_sour_mac_addr_in_probe_req(pst_hmac_vap, st_pno_scan_params.auc_sour_mac_addr,
                                             en_is_random_mac_addr_scan, OAL_FALSE);

    /* ״̬������: hmac_scan_proc_scan_req_event */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_SCHED_SCAN_REQ, (oal_void *)(&st_pno_scan_params));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_cfg80211_start_sched_scan::hmac_fsm_call_func_sta fail[%d].}", ul_ret);
        pst_hmac_device->st_scan_mgmt.pst_sched_scan_req     = OAL_PTR_NULL;
        pst_hmac_device->st_scan_mgmt.en_sched_scan_complete = OAL_TRUE;
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_cfg80211_stop_sched_scan
 ��������  : �����ں��·�����ֹͣPNO����ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_cfg80211_stop_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32      ul_ret;

    /***************************************************************************
                         ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap,
                                    WLAN_CFGID_STOP_SCHED_SCAN,
                                    us_len,
                                    puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_cfg80211_stop_sched_scan::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_cfg80211_start_scan_sta
 ��������  : �����ں��·���������ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��10��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_cfg80211_start_scan_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_scan_req_stru                    st_scan_params;
    hmac_vap_stru                       *pst_hmac_vap;
    mac_device_stru                     *pst_mac_device;
    mac_cfg80211_scan_param_pst_stru    *pst_cfg80211_scan_param_pst;
    oal_app_ie_stru                      st_app_ie;
    oal_uint32                           ul_ret = OAL_FAIL;
#ifdef _PRE_WLAN_FPGA_DIGITAL
    oal_uint8                            uc_channel = 0;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_cfg80211_start_scan_sta::scan failed, null ptr, %p %p.}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    pst_cfg80211_scan_param_pst = (mac_cfg80211_scan_param_pst_stru *)puc_param;

    /* ��ʼɨ���б���0 */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_cfg80211_start_scan_sta::scan failed, null ptr, pst_mac_device null.}");
        /*lint -e801*/
        goto ERROR_STEP;
        /*lint +e801*/
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_cfg80211_start_scan_sta::scan failed, null ptr, pst_hmac_vap null.}");
        /*lint -e801*/
        goto ERROR_STEP;
        /*lint +e801*/
    }

    /* ���ں��·���ɨ��������µ�����ɨ������ṹ���� */
    hmac_cfg80211_prepare_scan_req_sta(pst_mac_vap, &st_scan_params, (oal_int8 *)pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param);

    /* ����P2P/WPS IE ��Ϣ�� vap �ṹ���� */
    /* BEGIN:DTS2015080801057 WLAN���͵� probe request ��Я��P2P IE */
    if (IS_LEGACY_VAP(pst_mac_vap))
    {
        hmac_config_del_p2p_ie((oal_uint8 *)(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->puc_ie), &(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->ul_ie_len));
    }
    /* END:DTS2015080801057 WLAN���͵� probe request ��Я��P2P IE */

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P0 ɨ��ʱ��¼P2P listen channel */
    if (OAL_TRUE == pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->bit_is_p2p0_scan)
    {
        hmac_find_p2p_listen_channel(pst_mac_vap,
                                     (oal_uint16)(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->ul_ie_len),
                                     (oal_uint8 *)(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->puc_ie));
        st_scan_params.uc_p2p0_listen_channel = pst_mac_vap->uc_p2p_listen_channel;
    }
#endif
    st_app_ie.ul_ie_len = pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->ul_ie_len;
    oal_memcopy(st_app_ie.auc_ie, pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->puc_ie, st_app_ie.ul_ie_len);
    st_app_ie.en_app_ie_type = OAL_APP_PROBE_REQ_IE;
    hmac_config_set_app_ie_to_vap(pst_mac_vap, &st_app_ie, st_app_ie.en_app_ie_type);

#ifdef _PRE_WLAN_FPGA_DIGITAL
    for (uc_channel = 0; uc_channel < WLAN_MAX_CHANNEL_NUM; uc_channel++)
    {
        st_scan_params.ast_channel_list[uc_channel].en_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
    }
#endif

#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
            /* ut do noting */
#else
    /* ��Ϊɨ�������·��޸�Ϊ��������ʽ����ˣ��ŵ�������ڴ���Ҫ�ٴ˴��ͷ� */
    oal_free(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->pul_channels_2G);
    oal_free(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->pul_channels_5G);
#endif
    /* �ͷ�wal��alloc���ڴ� */
    OAL_MEM_FREE(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param, OAL_FALSE);

    /* ״̬������: hmac_scan_proc_scan_req_event */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_SCAN_REQ, (oal_void *)(&st_scan_params));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_cfg80211_start_scan_sta::hmac_fsm_call_func_sta fail[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;


ERROR_STEP:
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    /* ut do noting */
#else
    /* ��Ϊɨ�������·��޸�Ϊ��������ʽ����ˣ��ŵ�������ڴ���Ҫ�ٴ˴��ͷ� */
    oal_free(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->pul_channels_2G);
    oal_free(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param->pul_channels_5G);
#endif
    OAL_MEM_FREE(pst_cfg80211_scan_param_pst->pst_mac_cfg80211_scan_param, OAL_FALSE);
    return OAL_ERR_CODE_PTR_NULL;
}

/*****************************************************************************
 �� �� ��  : hmac_sta_initiate_join
 ��������  : �������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_sta_initiate_join(mac_vap_stru *pst_mac_vap, mac_bss_dscr_stru *pst_bss_dscr)
{
    hmac_join_req_stru  st_join_req;
    hmac_vap_stru      *pst_hmac_vap;
    oal_uint32          ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_bss_dscr)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_sta_initiate_join::input null %x %x.}", pst_mac_vap, pst_bss_dscr);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_initiate_join::mac_res_get_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /*DTS2015052811128:����Ҫ���������ʷ���hmac_vap��*/
    oal_memcopy(pst_hmac_vap->auc_supp_rates,pst_bss_dscr->auc_supp_rates ,pst_bss_dscr->uc_num_supp_rates);
    pst_hmac_vap->uc_rs_nrates = pst_bss_dscr->uc_num_supp_rates;

    hmac_prepare_join_req(&st_join_req, pst_bss_dscr);

    /* ״̬������  */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_JOIN_REQ, (oal_void *)(&st_join_req));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_initiate_join::hmac_fsm_call_func_sta fail[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_sta_initiate_auth
 ��������  : ������֤
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_sta_initiate_auth(mac_vap_stru *pst_mac_vap)
{
    hmac_auth_req_stru  st_auth_req;
    hmac_vap_stru      *pst_hmac_vap;
    oal_uint32          ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_sta_initiate_auth: pst_mac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_sta_initiate_auth: pst_hmac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_prepare_auth_req(pst_mac_vap, &st_auth_req);

    /* ״̬������  */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_AUTH_REQ, (oal_void *)(&st_auth_req));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_initiate_join::hmac_fsm_call_func_sta fail[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_sta_initiate_asoc
 ��������  : �������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_sta_initiate_asoc(mac_vap_stru *pst_mac_vap)
{
    hmac_asoc_req_stru  st_asoc_req;
    hmac_vap_stru      *pst_hmac_vap;
    oal_uint32          ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_sta_initiate_asoc::pst_mac_vap null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "hmac_sta_initiate_asoc: pst_hmac_vap null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_prepare_asoc_req(pst_mac_vap, &st_asoc_req);

    /* ״̬������  */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_ASOC_REQ, (oal_void *)(&st_asoc_req));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "hmac_sta_initiate_asoc::hmac_fsm_call_func_sta fail[%d]", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
/*****************************************************************************
 �� �� ��  : hmac_join_bss_sta
 ��������  : ����ɨ�赽��������AP�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_join_bss_sta(hmac_vap_stru *pst_hmac_vap)
{
    mac_bss_dscr_stru   *pst_bss_dscr;
    oal_uint32           ul_bss_idx;
    hmac_device_stru    *pst_hmac_device;

    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "hmac_join_bss_sta::pst_mac_device null");
        return;
    }

    /* �Ƿ���������AP���� */
    if (pst_hmac_device->uc_desired_bss_num > 0)
    {
        ul_bss_idx   = pst_hmac_device->auc_desired_bss_idx[pst_hmac_device->uc_desired_bss_num - 1];  /* �Ӻ���ǰȡ������bss */
        pst_bss_dscr = hmac_scan_find_scanned_bss_dscr_by_index(pst_hmac_vap->st_vap_base_info.uc_device_id, ul_bss_idx);

        pst_hmac_device->uc_desired_bss_num--;      /* ���������AP����-1 */

        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_join_bss_sta::try to join bss[%d].}", ul_bss_idx);

        /* �������� */
        hmac_sta_initiate_join(&pst_hmac_vap->st_vap_base_info, pst_bss_dscr);
    }

}


/*****************************************************************************
 �� �� ��  : hmac_prepare_bss_list
 ��������  : �������������bss�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_prepare_bss_list(hmac_vap_stru *pst_hmac_vap)
{
    oal_int8               *pc_mib_ssid;
    oal_uint32              ul_bss_idx = 0;
    hmac_device_stru       *pst_hmac_device;
    hmac_bss_mgmt_stru     *pst_bss_mgmt;
    hmac_scanned_bss_info  *pst_scanned_bss;
    mac_bss_dscr_stru      *pst_bss_dscr;
    oal_dlist_head_stru    *pst_entry;
    oal_uint8               uc_device_id;

    /* ��ȡdevice id */
    uc_device_id = pst_hmac_vap->st_vap_base_info.uc_device_id;

    /* ��ȡhmac device�ṹ�� */
    pst_hmac_device = hmac_res_get_mac_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ASSOC, "hmac_prepare_bss_list::pst_hmac_device null");
        return;
    }

    pc_mib_ssid = (oal_int8 *)pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;

    /* û������������ssid, ��������ɨ�� */
    if (0 == pc_mib_ssid[0])
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_prepare_bss_list::desired ssid is not set.}");
        return;
    }

    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    /* ��ȡ�� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ����������ap�б�����ɨ�赽��bss, ���Ƿ��������� */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);

        if (0 == oal_strcmp(pc_mib_ssid, pst_bss_dscr->ac_ssid))
        {
            /* �������join ��AP������Ϣ�Ƿ�ƥ�� */
            if(OAL_SUCC != hmac_check_capability_mac_phy_supplicant(&pst_hmac_vap->st_vap_base_info, pst_bss_dscr))
            {
                continue;
            }

            pst_bss_dscr->en_desired = OAL_TRUE;

            pst_hmac_device->auc_desired_bss_idx[pst_hmac_device->uc_desired_bss_num] = (oal_uint8)ul_bss_idx;  /* ��¼������AP��bss list�е������� */
            pst_hmac_device->uc_desired_bss_num++;
        }
        else
        {
            pst_bss_dscr->en_desired = OAL_FALSE;
        }

        ul_bss_idx++;
    }

    /* ����� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    hmac_join_bss_sta(pst_hmac_vap);
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_handle_scan_rsp_sta
 ��������  : ����ɨ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_handle_scan_rsp_sta(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_msg)
{
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;
    hmac_scan_rsp_stru  *pst_scan_rsp;


    /* ��ɨ������¼���WAL */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_scan_rsp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_handle_scan_rsp_sta::FRW_EVENT_ALLOC fail.}");
        return;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_SCAN_COMP_STA,
                       OAL_SIZEOF(hmac_scan_rsp_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    pst_scan_rsp = (hmac_scan_rsp_stru *)pst_event->auc_event_data;

    oal_memcopy(pst_scan_rsp, puc_msg , OAL_SIZEOF(hmac_scan_rsp_stru));

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    /* ׼�����������bss�б�*/
    hmac_prepare_bss_list(pst_hmac_vap);
#endif

}

/*****************************************************************************
 �� �� ��  : hmac_handle_join_rsp_sta
 ��������  : ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_handle_join_rsp_sta(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_msg)
{
    hmac_join_rsp_stru  *pst_join_rsp = (hmac_join_rsp_stru *)puc_msg;

    if (HMAC_MGMT_SUCCESS == pst_join_rsp->en_result_code)
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_join_rsp_sta::join succ.}");

        /* ��ʼ��AUTH���� */
        pst_hmac_vap->uc_auth_cnt = 1;
        hmac_sta_initiate_auth(&(pst_hmac_vap->st_vap_base_info));
    }
    else
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "hmac_handle_join_rsp_sta::join fail[%d]", pst_join_rsp->en_result_code);

        hmac_send_connect_result_to_dmac_sta(pst_hmac_vap, OAL_FAIL);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_report_connect_failed_result
 ��������  : ���͹���ʧ�ܽ����wpa_supplicant
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_report_connect_failed_result(hmac_vap_stru *pst_hmac_vap, mac_status_code_enum_uint16 reason_code)
{
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;
    hmac_asoc_rsp_stru   st_asoc_rsp;

    memset(&st_asoc_rsp, 0 ,sizeof(st_asoc_rsp));
    st_asoc_rsp.en_result_code       = HMAC_MGMT_TIMEOUT;
    st_asoc_rsp.en_status_code       = reason_code;
    /* ɨ�賬ʱ��Ҫ�ͷŶ�ӦHMAC VAP�µĹ�������buff */
    st_asoc_rsp.puc_asoc_req_ie_buff = pst_hmac_vap->puc_asoc_req_ie_buff;

    /* �׼�������¼���WAL */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_asoc_rsp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_report_connect_failed_result::FRW_EVENT_ALLOC fail!}");
        return;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_ASOC_COMP_STA,
                       OAL_SIZEOF(hmac_asoc_rsp_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    oal_memcopy(frw_get_event_payload(pst_event_mem), &st_asoc_rsp, OAL_SIZEOF(hmac_asoc_rsp_stru));

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

}

/*****************************************************************************
 �� �� ��  : hmac_handle_auth_rsp_sta
 ��������  : ������֤���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_handle_auth_rsp_sta(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_msg)
{
    hmac_auth_rsp_stru     *pst_auth_rsp = (hmac_auth_rsp_stru *)puc_msg;
    hmac_user_stru         *pst_hmac_user;
    oal_uint8               auc_param[] = "all";

    if (HMAC_MGMT_SUCCESS == pst_auth_rsp->us_status_code)
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_handle_auth_rsp_sta::auth succ.}");

        /* ��ʼ��AOSC���� */
        pst_hmac_vap->uc_asoc_cnt = 1;
        hmac_sta_initiate_asoc(&pst_hmac_vap->st_vap_base_info);
        return;
    }

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "hmac_handle_auth_rsp_sta::auth fail[%d],cnt[%d]",
                     pst_auth_rsp->us_status_code, pst_hmac_vap->uc_auth_cnt);

    if ((MAC_UNSUPT_ALG == pst_auth_rsp->us_status_code ||
         MAX_AUTH_CNT <= pst_hmac_vap->uc_auth_cnt) &&
        (WLAN_WITP_AUTH_AUTOMATIC == pst_hmac_vap->en_auth_mode))
    {
        pst_hmac_vap->en_auth_mode = WLAN_WITP_AUTH_SHARED_KEY;
        /* ��Ҫ��״̬������Ϊ */
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_JOIN_COMP);

        /* ����AUTH�Ĵ��� */
        pst_hmac_vap->uc_auth_cnt = 0;

        /* ���·���������� */
        hmac_sta_initiate_auth(&(pst_hmac_vap->st_vap_base_info));

        return;
    }

    if (pst_hmac_vap->uc_auth_cnt < MAX_AUTH_CNT)
    {
        /* ��Ҫ��״̬������Ϊ */
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_JOIN_COMP);

        /* ����AUTH�Ĵ��� */
        pst_hmac_vap->uc_auth_cnt++;

        /* ���·���������� */
        hmac_sta_initiate_auth(&(pst_hmac_vap->st_vap_base_info));

        return;
    }
    else
    {
        hmac_config_reg_info(&(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(auc_param), auc_param);
    }

    hmac_send_connect_result_to_dmac_sta(pst_hmac_vap, OAL_FAIL);

    /* The MAC state is changed to fake up state. Further MLME     */
    /* requests are processed in this state.                       */
    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);

    /* ��ȡ�û�ָ�� */
    pst_hmac_user = mac_res_get_hmac_user((oal_uint16)pst_hmac_vap->st_vap_base_info.uc_assoc_vap_id);
    if (OAL_PTR_NULL != pst_hmac_user)
    {
        /* ɾ����Ӧ�û� */
        hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
    }
    else
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "auth pst_hmac_user NULL.");
    }

    /* �ϱ�����ʧ�ܵ�wpa_supplicant */
    hmac_report_connect_failed_result(pst_hmac_vap, pst_auth_rsp->us_status_code);

}

/*****************************************************************************
 �� �� ��  : hmac_handle_asoc_rsp_sta
 ��������  : ������֤���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_handle_asoc_rsp_sta(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_msg)
{
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;
    hmac_asoc_rsp_stru  *pst_asoc_rsp = (hmac_asoc_rsp_stru *)puc_msg;
    hmac_user_stru      *pst_hmac_user;
    oal_uint8           *puc_mgmt_data;

    if(HMAC_MGMT_SUCCESS == pst_asoc_rsp->en_result_code)
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_asoc_rsp_sta::asoc succ.}");
        /* �׼�������¼���WAL */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_asoc_rsp_stru));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_handle_asoc_rsp_sta::FRW_EVENT_ALLOC fail!}");
            return;
        }

        /* DTS2016102405092: asoc_rsp ֡����һ���ϱ��ϲ�,��ֹ֡�����ϱ�wal�ദ���hmac���ͷ� */
        puc_mgmt_data = (oal_uint8*)oal_memalloc(pst_asoc_rsp->ul_asoc_rsp_ie_len);
        if(OAL_PTR_NULL == puc_mgmt_data)
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_asoc_rsp_sta::pst_mgmt_data alloc null.}");
            FRW_EVENT_FREE(pst_event_mem);
            return;
        }
        oal_memcopy(puc_mgmt_data, (oal_uint8 *)pst_asoc_rsp->puc_asoc_rsp_ie_buff, pst_asoc_rsp->ul_asoc_rsp_ie_len);
        pst_asoc_rsp->puc_asoc_rsp_ie_buff = puc_mgmt_data;

        /* ��д�¼� */
        pst_event = (frw_event_stru *)pst_event_mem->puc_data;

        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                           FRW_EVENT_TYPE_HOST_CTX,
                           HMAC_HOST_CTX_EVENT_SUB_TYPE_ASOC_COMP_STA,
                           OAL_SIZEOF(hmac_asoc_rsp_stru),
                           FRW_EVENT_PIPELINE_STAGE_0,
                           pst_hmac_vap->st_vap_base_info.uc_chip_id,
                           pst_hmac_vap->st_vap_base_info.uc_device_id,
                           pst_hmac_vap->st_vap_base_info.uc_vap_id);

        oal_memcopy((oal_uint8 *)frw_get_event_payload(pst_event_mem), (oal_uint8 *)puc_msg, OAL_SIZEOF(hmac_asoc_rsp_stru));

        /* �ַ��¼� */
        frw_event_dispatch_event(pst_event_mem);
        FRW_EVENT_FREE(pst_event_mem);
    }
    else
    {
        OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_handle_asoc_rsp_sta::asoc fail[%d], assoc_cnt[%d]}",
          pst_asoc_rsp->en_result_code, pst_hmac_vap->uc_asoc_cnt);

        if (pst_hmac_vap->uc_asoc_cnt >= MAX_ASOC_CNT)
        {
            /* ��ȡ�û�ָ�� */
            pst_hmac_user = mac_res_get_hmac_user((oal_uint16)pst_hmac_vap->st_vap_base_info.uc_assoc_vap_id);
            if (NULL != pst_hmac_user)
            {
                /* ����ȥ��֤֡��AP */
                hmac_mgmt_send_deauth_frame(&pst_hmac_vap->st_vap_base_info, pst_hmac_user->st_user_base_info.auc_user_mac_addr, MAC_AUTH_NOT_VALID, OAL_FALSE);

                /* ɾ����Ӧ�û� */
                hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
            }
            else
            {
                OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "asoc:pst_hmac_user NULL.");
            }

            /* ����״̬ΪFAKE UP */
            hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);

            /* ͬ��DMAC״̬ */
            hmac_send_connect_result_to_dmac_sta(pst_hmac_vap, OAL_FAIL);

            /* �ϱ�����ʧ�ܵ�wpa_supplicant */
            hmac_report_connect_failed_result(pst_hmac_vap, pst_asoc_rsp->en_status_code);

        }
        else
        {
            /* ��Ҫ��״̬������Ϊ */
            hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_AUTH_COMP);

            /* ����ASOC�Ĵ��� */
            pst_hmac_vap->uc_asoc_cnt++;

            /* ���·���������� */
            hmac_sta_initiate_asoc(&pst_hmac_vap->st_vap_base_info);
        }
    }

}



/*****************************************************************************
 �� �� ��  : hmac_send_rsp_to_sme
 ��������  : ������״̬������ϱ���SME
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_send_rsp_to_sme_sta(hmac_vap_stru *pst_hmac_vap, hmac_sme_rsp_enum_uint8 en_type, oal_uint8 *puc_msg)
{

#ifdef _PRE_WIFI_DMT
    /* ����DMT����ϱ���������֤Ԥ�ڽ�� */
    hmac_scan_rsp_stru              *pst_scan_rsp;
    hmac_join_rsp_stru              *pst_join_rsp;
    hmac_auth_rsp_stru              *pst_auth_rsp;
    hmac_asoc_rsp_stru              *pst_asoc_rsp;

    EXPECT_EVENT_STATUS              stEventStatus;

    stEventStatus.ucMsgType   = en_type;
    stEventStatus.usMsgStatus = pst_hmac_vap->st_vap_base_info.en_vap_state;
    stEventStatus.usMsgLength= sizeof(EXPECT_EVENT_STATUS);

    if (HMAC_SME_SCAN_RSP == en_type)
    {
        pst_scan_rsp = (hmac_scan_rsp_stru *)puc_msg;
        stEventStatus.usMsgSubStatus = pst_scan_rsp->uc_result_code;
    }
    else if (HMAC_SME_JOIN_RSP == en_type)
    {
        pst_join_rsp = (hmac_join_rsp_stru *)puc_msg;
        stEventStatus.usMsgSubStatus = pst_join_rsp->en_result_code;
    }
    else if (HMAC_SME_AUTH_RSP == en_type)
    {
        pst_auth_rsp = (hmac_auth_rsp_stru *)puc_msg;
        stEventStatus.usMsgSubStatus = pst_auth_rsp->us_status_code;
    }
    else if (HMAC_SME_ASOC_RSP == en_type)
    {
        pst_asoc_rsp = (hmac_asoc_rsp_stru *)puc_msg;
        stEventStatus.usMsgSubStatus = pst_asoc_rsp->en_result_code;
    }

    OAL_IO_PRINT("[EVENT_REPORT] RspType=%d VapState=%d ResultCode=%d \n", \
                  stEventStatus.ucMsgType, stEventStatus.usMsgStatus, stEventStatus.usMsgSubStatus);

    DmtStub_Sta2DmtSendMsg(DEV_DMT_EVENT_STATUS_MSG, (oal_uint8 *)&stEventStatus, sizeof(EXPECT_EVENT_STATUS));
#endif

    g_handle_rsp_func_sta[en_type](pst_hmac_vap, puc_msg);
}

/*****************************************************************************
 �� �� ��  : hmac_send_rsp_to_sme_ap
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_send_rsp_to_sme_ap(hmac_vap_stru *pst_hmac_vap, hmac_ap_sme_rsp_enum_uint8 en_type, oal_uint8 *puc_msg)
{
    /* Ŀǰֻ��DMTʹ�� */

#ifdef _PRE_WIFI_DMT
    /* ����DMT����ϱ���������֤Ԥ�ڽ�� */
    hmac_ap_start_rsp_stru   *pst_ap_start_rsp;
    EXPECT_EVENT_STATUS       stEventStatus;

    stEventStatus.ucMsgType   = en_type;
    stEventStatus.usMsgStatus = pst_hmac_vap->st_vap_base_info.en_vap_state;
    stEventStatus.usMsgLength= sizeof(EXPECT_EVENT_STATUS);

    if (HMAC_AP_SME_START_RSP == en_type)
    {
        pst_ap_start_rsp = (hmac_ap_start_rsp_stru *)puc_msg;
        stEventStatus.usMsgSubStatus = pst_ap_start_rsp->en_result_code;
    }

    OAL_IO_PRINT("[EVENT_REPORT] RspType=%d VapState=%d ResultCode=%d \n", \
                  stEventStatus.ucMsgType, stEventStatus.usMsgStatus, stEventStatus.usMsgSubStatus);

    DmtStub_Sta2DmtSendMsg(DEV_DMT_EVENT_STATUS_MSG, (oal_uint8 *)&stEventStatus, sizeof(EXPECT_EVENT_STATUS));
#endif
}


/*****************************************************************************
 �� �� ��  : hmac_send_connect_fail_to_dmac_sta
 ��������  : ����ʧ��֪ͨDMAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_send_connect_result_to_dmac_sta(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_result)
{
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (ul_result != OAL_SUCC)
    {
        hmac_psta_proc_join_result(pst_hmac_vap, OAL_FALSE);
    }
#endif

    /* ���¼���DMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint32));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "pst_event_mem null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_CONN_RESULT,
                       OAL_SIZEOF(oal_uint32),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    *((oal_uint32 *)(pst_event->auc_event_data)) = ul_result;

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}





/*lint -e578*//*lint -e19*/
oal_module_symbol(hmac_sta_initiate_scan);
oal_module_symbol(hmac_sta_initiate_join);
oal_module_symbol(hmac_cfg80211_start_scan_sta);
oal_module_symbol(hmac_cfg80211_start_sched_scan);
oal_module_symbol(hmac_cfg80211_stop_sched_scan);
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0))
oal_module_symbol(hmac_cfg80211_dump_survey);
#endif
/*lint +e578*//*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

