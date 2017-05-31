/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_chan_mgmt.c
  �� �� ��   : ����
  ��    ��   : mayuan
  ��������   : 2014��2��22��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��2��22��
    ��    ��   : mayuan
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
#include "mac_ie.h"
#include "mac_regdomain.h"
#include "mac_device.h"
#include "hmac_mgmt_sta.h"
#include "hmac_sme_sta.h"
#include "hmac_fsm.h"
#include "hmac_dfs.h"
#include "hmac_chan_mgmt.h"
#include "mac_device.h"
#include "hmac_scan.h"
#include "frw_ext_if.h"
#include "hmac_resource.h"
#include "hmac_encap_frame.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CHAN_MGMT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define HMAC_CENTER_FREQ_2G_40M_OFFSET    2   /* ����Ƶ����������ŵ�idx��ƫ���� */
#define HMAC_AFFECTED_CH_IDX_OFFSET       5   /* 2.4GHz�£�40MHz������Ӱ����ŵ��뾶������Ƶ�� +/- 5���ŵ� */
/* 5GƵ�� �ŵ�������Ƶ��ӳ�� */
OAL_CONST mac_freq_channel_map_stru g_ast_freq_map_5g[MAC_CHANNEL_FREQ_5_BUTT] =
{
    { 5180, 36, 0},
    { 5200, 40, 1},
    { 5220, 44, 2},
    { 5240, 48, 3},
    { 5260, 52, 4},
    { 5280, 56, 5},
    { 5300, 60, 6},
    { 5320, 64, 7},
    { 5500, 100, 8},
    { 5520, 104, 9},
    { 5540, 108, 10},
    { 5560, 112, 11},
    { 5580, 116, 12},
    { 5600, 120, 13},
    { 5620, 124, 14},
    { 5640, 128, 15},
    { 5660, 132, 16},
    { 5680, 136, 17},
    { 5700, 140, 18},
    { 5720, 144, 19},
    { 5745, 149, 20},
    { 5765, 153, 21},
    { 5785, 157, 22},
    { 5805, 161, 23},
    { 5825, 165, 24},
    /* for JP 4.9G */
    { 4920, 184, 25},
    { 4940, 188, 26},
    { 4960, 192, 27},
    { 4980, 196, 28},
};

/* 2.4GƵ�� �ŵ�������Ƶ��ӳ�� */
OAL_CONST mac_freq_channel_map_stru g_ast_freq_map_2g[MAC_CHANNEL_FREQ_2_BUTT] =
{
    { 2412, 1, 0},
    { 2417, 2, 1},
    { 2422, 3, 2},
    { 2427, 4, 3},
    { 2432, 5, 4},
    { 2437, 6, 5},
    { 2442, 7, 6},
    { 2447, 8, 7},
    { 2452, 9, 8},
    { 2457, 10, 9},
    { 2462, 11, 10},
    { 2467, 12, 11},
    { 2472, 13, 12},
    { 2484, 14, 13},
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
OAL_STATIC oal_void hmac_chan_stop_40M_recovery_timer(mac_vap_stru *pst_mac_vap);
#endif
/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

oal_uint32 hmac_dump_chan(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param)
{
    dmac_set_chan_stru *pst_chan;

    if ( (OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param) )
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_chan = (dmac_set_chan_stru*)puc_param;
    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "channel mgmt info\r\n");
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_chan_number=%d\r\n", pst_chan->st_channel.uc_chan_number);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_band=%d\r\n", pst_chan->st_channel.en_band);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_bandwidth=%d\r\n", pst_chan->st_channel.en_bandwidth);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_idx=%d\r\n", pst_chan->st_channel.uc_idx);

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "c_announced_channel=%d\r\n", pst_chan->st_ch_switch_info.uc_announced_channel);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_announced_bandwidth=%d\r\n", pst_chan->st_ch_switch_info.en_announced_bandwidth);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_ch_switch_cnt=%d\r\n", pst_chan->st_ch_switch_info.uc_ch_switch_cnt);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_ch_switch_status=%d\r\n", pst_chan->st_ch_switch_info.en_ch_switch_status);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_bw_switch_status=%d\r\n", pst_chan->st_ch_switch_info.en_bw_switch_status);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_csa_present_in_bcn=%d\r\n", pst_chan->st_ch_switch_info.en_csa_present_in_bcn);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_start_chan_idx=%d\r\n", pst_chan->st_ch_switch_info.uc_start_chan_idx);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_end_chan_idx=%d\r\n", pst_chan->st_ch_switch_info.uc_end_chan_idx);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_user_pref_bandwidth=%d\r\n", pst_chan->st_ch_switch_info.en_user_pref_bandwidth);

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_bw_change=%d\r\n", pst_chan->st_ch_switch_info.en_bw_change);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_new_channel=%d\r\n", pst_chan->st_ch_switch_info.uc_new_channel);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_new_bandwidth=%d\r\n", pst_chan->st_ch_switch_info.en_new_bandwidth);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_new_ch_swt_cnt=%d\r\n", pst_chan->st_ch_switch_info.uc_new_ch_swt_cnt);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_waiting_to_shift_channel=%d\r\n",
                pst_chan->st_ch_switch_info.en_waiting_to_shift_channel);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_channel_swt_cnt_zero=%d\r\n", pst_chan->st_ch_switch_info.en_channel_swt_cnt_zero);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_te_b=%d\r\n",pst_chan->st_ch_switch_info.en_te_b);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "ul_chan_report_for_te_a=%d\r\n", pst_chan->st_ch_switch_info.ul_chan_report_for_te_a);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_send_ht_notify_chan_width
 ��������  : ���� ht  notify chan width֡
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��28��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_send_ht_notify_chan_width(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data)
{
    oal_uint16                    us_frame_len;
    oal_netbuf_stru              *pst_netbuf;
    mac_tx_ctl_stru              *pst_tx_ctl;
    oal_uint32                    ul_ret;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_data))
    {
        OAM_ERROR_LOG2(0, OAM_SF_2040, "{hmac_send_ht_notify_chan_width::param null, %p %p.}", pst_mac_vap, puc_data);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����ht_notify_chan_width ֡�ռ� */
    pst_netbuf = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, MAC_80211_FRAME_LEN + MAC_HT_NOTIFY_CHANNEL_WIDTH_LEN, OAL_NETBUF_PRIORITY_MID);
    if(OAL_PTR_NULL == pst_netbuf)
    {
       OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_send_ht_notify_chan_width::Alloc netbuf(size %d) null in normal_netbuf.}", MAC_80211_FRAME_LEN + MAC_HT_NOTIFY_CHANNEL_WIDTH_LEN);
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��װSA Query request֡*/
    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_NETBUF_CB_SIZE());
    us_frame_len = hmac_encap_notify_chan_width(pst_mac_vap, (oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf), puc_data);

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf); /* ��ȡcb�ṹ�� */
    pst_tx_ctl->us_mpdu_len     = us_frame_len;               /* dmac������Ҫ��mpdu���� */
    pst_tx_ctl->us_tx_user_idx  = MAC_INVALID_USER_ID;        /* ���������Ҫ��ȡuser�ṹ�� */
    oal_netbuf_put(pst_netbuf, us_frame_len);

    /* Buffer this frame in the Memory Queue for transmission */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_netbuf, us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_netbuf);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_send_ht_notify_chan_width::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_chan_multi_switch_to_20MHz_ap
 ��������  : ����device������VAP�ŵ�������׼���л���20MHz����
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_multi_switch_to_20MHz_ap(hmac_vap_stru *pst_hmac_vap)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_mac_vap;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    hmac_vap_stru     *pst_hmac_vap_iter;
#endif

    OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
            "{hmac_chan_multi_switch_to_20MHz_ap::bit_2040_channel_switch_prohibited=%d}",
            pst_hmac_vap->en_2040_switch_prohibited);

    /* ����������л�������ֱ�ӷ��� */
    if (OAL_TRUE == pst_hmac_vap->en_2040_switch_prohibited)
    {
        return;
    }

    pst_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_multi_switch_to_20MHz_ap::pst_device null,uc_device_id=%d.}",
                       pst_hmac_vap->st_vap_base_info.uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_multi_switch_to_20MHz_ap::pst_device null,none vap.}");
        return;
    }

    if (mac_is_dbac_running(pst_device))
    {
        pst_mac_vap = &pst_hmac_vap->st_vap_base_info;
        pst_hmac_vap->en_40M_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
        hmac_chan_initiate_switch_to_20MHz_ap(&pst_hmac_vap->st_vap_base_info);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                       pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif
        hmac_send_ht_notify_chan_width(pst_mac_vap, BROADCAST_MACADDR);
        return;
    }

    /* ����device������vap������VAP�ŵ�������׼���л���20MHz���� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                           "{hmac_chan_multi_switch_to_20MHz_ap::pst_mac_vap null,vap_idx=%d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
        pst_hmac_vap_iter = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_vap_iter)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                           "{hmac_chan_multi_switch_to_20MHz_ap::pst_hmac_vap_iter null,vap_idx=%d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 40M��20Mǰ��¼40M����40M�ָ���ʱ������ʹ������ŵ����лָ� */
        pst_hmac_vap_iter->en_40M_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
#endif

        hmac_chan_initiate_switch_to_20MHz_ap(pst_mac_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                       pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif

        hmac_send_ht_notify_chan_width(pst_mac_vap, BROADCAST_MACADDR);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_chan_initiate_switch_to_new_channel
 ��������  : ����VAP�ŵ�������׼���л������ŵ�����
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ���ŵ���(׼���л�����20MHz���ŵ���)
             en_bandwidth: �´���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��22��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_chan_initiate_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    frw_event_mem_stru            *pst_event_mem;
    frw_event_stru                *pst_event;
    oal_uint32                     ul_ret;
    dmac_set_ch_switch_info_stru  *pst_ch_switch_info;
    mac_device_stru               *pst_mac_device;

    /* AP׼���л��ŵ� */
    pst_mac_vap->st_ch_switch_info.en_ch_switch_status    = WLAN_CH_SWITCH_STATUS_1;
    pst_mac_vap->st_ch_switch_info.uc_announced_channel   = uc_channel;
    pst_mac_vap->st_ch_switch_info.en_announced_bandwidth = en_bandwidth;

    /* ��Beacon֡�����Channel Switch Announcement IE */
    pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn  = OAL_TRUE;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_initiate_switch_to_new_channel::uc_announced_channel=%d,en_announced_bandwidth=%d}",
        uc_channel, en_bandwidth);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_initiate_switch_to_new_channel::pst_mac_device null.}");
        return;
    }
    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_set_ch_switch_info_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_initiate_switch_to_new_channel::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN,
                    OAL_SIZEOF(dmac_set_ch_switch_info_stru),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* ��д�¼�payload */
    pst_ch_switch_info = (dmac_set_ch_switch_info_stru *)pst_event->auc_event_data;
    pst_ch_switch_info->en_ch_switch_status    = WLAN_CH_SWITCH_STATUS_1;
    pst_ch_switch_info->uc_announced_channel   = uc_channel;
    pst_ch_switch_info->en_announced_bandwidth = en_bandwidth;
    pst_ch_switch_info->uc_ch_switch_cnt = pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt;
    pst_ch_switch_info->en_csa_present_in_bcn  = OAL_TRUE;
    pst_ch_switch_info->uc_csa_vap_cnt         = pst_mac_device->uc_csa_vap_cnt;


    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_initiate_switch_to_new_channel::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 �� �� ��  : hmac_chan_multi_switch_to_new_channel
 ��������  : ����device������ap������VAP�ŵ�������׼���л������ŵ�����
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ���ŵ���(׼���л�����20MHz���ŵ���)
             en_bandwidth: �´���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFS
oal_void hmac_dfs_set_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_mac_device;
    mac_vap_stru      *pst_vap;
    oal_uint8          uc_chan_idx;
    oal_uint32         ul_ret;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::pst_device(%d) null.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::none vap.}");
        return;
    }

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, uc_channel, &uc_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_device->uc_csa_vap_cnt = 0;

    /* ����device������ap������ap�ŵ�����������CSA֡��׼���л������ŵ����� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::pst_ap(%d) null.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* ֻ��running AP��Ҫ����CSA֡ */
        if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode) &&
            (MAC_VAP_STATE_UP     == pst_vap->en_vap_state))
        {
            pst_mac_device->uc_csa_vap_cnt++;
            if(uc_channel == pst_vap->st_channel.uc_chan_number)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::same channel num %d, no need to change.}", uc_channel);
                return;
            }
            hmac_chan_initiate_switch_to_new_channel(pst_vap, uc_channel, pst_vap->st_channel.en_bandwidth);
        }
    }
}
oal_void  hmac_chan_multi_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_mac_device;
    mac_vap_stru      *pst_vap;
    oal_uint8          uc_chan_idx;
    oal_uint32         ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_multi_switch_to_new_channel::uc_channel=%d,en_bandwidth=%d}",
        uc_channel, en_bandwidth);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::pst_device(%d) null.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::none vap.}");
        return;
    }

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, uc_channel, &uc_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_device->uc_csa_vap_cnt = 0;

    /* ����device������ap������ap�ŵ�����������CSA֡��׼���л������ŵ����� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::pst_ap(%d) null.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* ֻ��running AP��Ҫ����CSA֡ */
        if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode) &&
            (MAC_VAP_STATE_UP     == pst_vap->en_vap_state))
        {
            pst_mac_device->uc_csa_vap_cnt++;
            hmac_chan_initiate_switch_to_new_channel(pst_vap, uc_channel, en_bandwidth);
        }
        else  /* ����վ��ֻ��Ҫ�����ŵ���Ϣ */
        {
            /* ����VAP�µ���20MHz�ŵ��š�����ģʽ���ŵ����� */
            pst_vap->st_channel.uc_chan_number = uc_channel;
            pst_vap->st_channel.uc_idx         = uc_chan_idx;
            pst_vap->st_channel.en_bandwidth   = en_bandwidth;
        }
    }
}

#else

oal_void  hmac_chan_multi_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_ap;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_multi_switch_to_new_channel::uc_channel=%d,en_bandwidth=%d}",
        uc_channel, en_bandwidth);

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_switch_to_new_channel::pst_device null.}");
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_switch_to_new_channel::none vap.}");
        return;
    }

    /* ����device������ap������ap�ŵ�������׼���л������ŵ����� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_ap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_ap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_switch_to_new_channel::pst_ap null.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* ֻ����AP����ŵ��л���Ϣ */
        if (WLAN_VAP_MODE_BSS_AP != pst_ap->en_vap_mode)
        {
            continue;
        }

        hmac_chan_initiate_switch_to_new_channel(pst_ap, uc_channel, en_bandwidth);
    }
}

#endif /* end of _PRE_WLAN_FEATURE_DFS */

oal_void  hmac_chan_sync_init(mac_vap_stru *pst_mac_vap, dmac_set_chan_stru *pst_set_chan)
{
    oal_memset(pst_set_chan, 0, OAL_SIZEOF(dmac_set_chan_stru));
    oal_memcopy(&pst_set_chan->st_channel, &pst_mac_vap->st_channel,
                    OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&pst_set_chan->st_ch_switch_info, &pst_mac_vap->st_ch_switch_info,
                    OAL_SIZEOF(mac_ch_switch_info_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_chan_do_sync
 ��������  : HMACģ�����¼���DMACģ�飬����SW/MAC/PHY/RF�е��ŵ��ʹ���
             ʹVAP���������ŵ���
 �������  : pst_mac_vap : mac_vap_stru
             pst_set_chan  : dmac_set_chan_stru
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��26��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_do_sync(mac_vap_stru *pst_mac_vap, dmac_set_chan_stru *pst_set_chan)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    oal_uint32                ul_ret;
    oal_uint8                 uc_idx;

    hmac_dump_chan(pst_mac_vap, (oal_uint8*)pst_set_chan);
    /* ����VAP�µ���20MHz�ŵ��š�����ģʽ���ŵ����� */
    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_set_chan->st_channel.uc_chan_number, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_chan_sync::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_vap->st_channel.uc_chan_number = pst_set_chan->st_channel.uc_chan_number;
    pst_mac_vap->st_channel.en_bandwidth   = pst_set_chan->st_channel.en_bandwidth;
    pst_mac_vap->st_channel.uc_idx         = uc_idx;


    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_set_chan_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_sync::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN,
                    OAL_SIZEOF(dmac_set_chan_stru),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8 *)pst_set_chan, OAL_SIZEOF(dmac_set_chan_stru));

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_sync::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 �� �� ��  : hmac_chan_sync
 ��������  : HMAC���ŵ�/������Ϣͬ����DMAC
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ��Ҫ�����õ��ŵ���
             en_bandwidth: ��Ҫ�����õĴ���ģʽ
             en_switch_immediately: DMAC���յ�ͬ���¼�֮���Ƿ������л�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��26��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_void hmac_chan_sync(mac_vap_stru *pst_mac_vap,
            oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth,
            oal_bool_enum_uint8 en_switch_immediately)
{
    dmac_set_chan_stru st_set_chan;

    hmac_chan_sync_init(pst_mac_vap, &st_set_chan);
    st_set_chan.st_channel.uc_chan_number = uc_channel;
    st_set_chan.st_channel.en_bandwidth = en_bandwidth;
    st_set_chan.en_switch_immediately = en_switch_immediately;
    hmac_chan_do_sync(pst_mac_vap, &st_set_chan);
}


/*****************************************************************************
 �� �� ��  : hmac_chan_multi_select_channel_mac
 ��������  : ����device������VAP������SW/MAC/PHY/RF�е��ŵ��ʹ���ʹVAP���������ŵ���
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ��Ҫ�����õ��ŵ���
             en_bandwidth: ��Ҫ�����õĴ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_multi_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_vap;

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_select_channel_mac::uc_channel=%d,en_bandwidth=%d}",
            uc_channel, en_bandwidth);

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_multi_select_channel_mac::pst_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_select_channel_mac::none vap.}");
        return;
    }

    if (mac_is_dbac_running(pst_device))
    {
        hmac_chan_sync(pst_mac_vap, uc_channel, en_bandwidth, OAL_TRUE);
        return;
    }

    /* ����device������vap�� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                           "{hmac_chan_multi_select_channel_mac::pst_vap null,vap_id=%d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        hmac_chan_sync(pst_vap, uc_channel, en_bandwidth, OAL_TRUE);
    }
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : hmac_chan_is_this_40MHz_set_possible
 ��������  : �ж��ܷ��ڸ�����"���ŵ� + ���ŵ�ƫ����"�ϣ�������40MHz BSS
 �������  : pst_mac_device      : MAC DEVICE�ṹ��ָ��
             pst_mac_vap         : MAC VAP�ṹ��ָ��
             uc_pri_chan_idx     : ���ŵ�����
             en_sec_chan_offset  : ���ŵ�ƫ����
 �������  : pst_chan_scan_report: �ŵ������ṹ��ָ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_this_40MHz_set_possible(
                mac_device_stru              *pst_mac_device,
                mac_vap_stru                 *pst_mac_vap,
                oal_uint8                     uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8     en_sec_chan_offset,
                hmac_eval_scan_report_stru   *pst_chan_scan_report)
{
    mac_ap_ch_info_stru           *pst_ap_channel_list;
    wlan_channel_band_enum_uint8   en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                      uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8                      uc_affected_ch_idx_offset = mac_get_affected_ch_idx_offset(en_band);
    oal_uint8                      uc_sec_ch_idx_offset = mac_get_sec_ch_idx_offset(en_band);
    oal_uint8                      uc_ch_idx;
    oal_uint8                      uc_sec_chan_idx;
    oal_uint8                      uc_affected_chan_lo = 0, uc_affected_chan_hi = 0;
    hmac_network_type_enum_uint8   en_network_type;
    hmac_chan_op_enum_uint8        en_allowed_bit;
    oal_bool_enum_uint8            en_flag_2040_op_permitted = OAL_TRUE;
    oal_uint32                     ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_is_this_40MHz_set_possible::uc_pri_chan_idx=%d,en_sec_chan_offset=%d}",
        uc_pri_chan_idx, en_sec_chan_offset);

    ul_ret = mac_is_channel_idx_valid(en_band, uc_pri_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    if (MAC_SCA == en_sec_chan_offset)
    {
        /* ������ŵ����� */
        if (uc_num_supp_chan > uc_pri_chan_idx + uc_sec_ch_idx_offset)
        {
            uc_sec_chan_idx = uc_pri_chan_idx + uc_sec_ch_idx_offset;
        }
        else
        {
            return OAL_FALSE;
        }

        en_network_type = HMAC_NETWORK_SCA;
        en_allowed_bit  = HMAC_SCA_ALLOWED;

        /* ������Ӱ����ŵ��������� */
        uc_affected_chan_lo = (uc_pri_chan_idx >= uc_affected_ch_idx_offset) ?
                        (uc_pri_chan_idx - uc_affected_ch_idx_offset) : 0;

        /* ������Ӱ����ŵ��������� */
        uc_affected_chan_hi = (uc_num_supp_chan > uc_sec_chan_idx + uc_affected_ch_idx_offset) ?
                        (uc_sec_chan_idx + uc_affected_ch_idx_offset) : (uc_num_supp_chan - 1);
    }
    else if (MAC_SCB == en_sec_chan_offset)
    {
        /* ������ŵ����� */
        if (uc_pri_chan_idx >= uc_sec_ch_idx_offset)
        {
            uc_sec_chan_idx = uc_pri_chan_idx - uc_sec_ch_idx_offset;
        }
        else
        {
            return OAL_FALSE;
        }

        en_network_type = HMAC_NETWORK_SCB;
        en_allowed_bit  = HMAC_SCB_ALLOWED;

        /* ������Ӱ����ŵ��������� */
        uc_affected_chan_lo = (uc_sec_chan_idx >= uc_affected_ch_idx_offset) ?
                        (uc_sec_chan_idx - uc_affected_ch_idx_offset) : 0;

        /* ������Ӱ����ŵ��������� */
        uc_affected_chan_hi = (uc_num_supp_chan > uc_pri_chan_idx + uc_affected_ch_idx_offset) ?
                        (uc_pri_chan_idx + uc_affected_ch_idx_offset) : (uc_num_supp_chan - 1);
    }
    else
    {
        return OAL_FALSE;
    }

    ul_ret = mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    if(uc_affected_chan_hi >= MAC_MAX_SUPP_CHANNEL)
    {
        return OAL_FALSE;
    }

    /* ���ڸ�����"���ŵ� + ���ŵ�ƫ����"�������ķ�Χ��(����Ƶ�� +/- 5���ŵ�)���ж��ܷ���40MHz BSS */
    for (uc_ch_idx = uc_affected_chan_lo; uc_ch_idx <= uc_affected_chan_hi; uc_ch_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, uc_ch_idx);
        if (OAL_SUCC != ul_ret)
        {
            continue;
        }

        pst_ap_channel_list = &(pst_mac_device->st_ap_channel_list[uc_ch_idx]);

        /* ��������ŵ��ϴ���BSS */
        if (MAC_CH_TYPE_NONE != pst_ap_channel_list->en_ch_type)
        {
            /* �ۼ������ŵ���ɨ�赽��BSS���� */
            pst_chan_scan_report[uc_pri_chan_idx].aus_num_networks[en_network_type] += pst_ap_channel_list->us_num_networks;

            /* ��BSS�����ŵ����������е�20/40MHz BSS�����ŵ��غ� */
            if (uc_ch_idx == uc_pri_chan_idx)
            {
                if (MAC_CH_TYPE_PRIMARY == pst_ap_channel_list->en_ch_type)
                {
                    continue;
                }
            }

            /* ��BSS�Ĵ��ŵ����������е�20/40MHz BSS�Ĵ��ŵ��غ� */
            if (uc_ch_idx == uc_sec_chan_idx)
            {
                if (MAC_CH_TYPE_SECONDARY == pst_ap_channel_list->en_ch_type)
                {
                    continue;
                }
            }

            en_flag_2040_op_permitted = OAL_FALSE;
        }
    }

    /* ���20/40MHz����û��ʹ�ܣ�����Ϊ���Խ���40MHz BSS�������û�������"40MHz������"λ */
    if ((OAL_FALSE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (OAL_FALSE == mac_mib_get_FortyMHzIntolerant(pst_mac_vap)))
    {
        en_flag_2040_op_permitted = OAL_TRUE;
    }
    /* 5GHz����²�����20/40M�������ú�40M���������ã�һ������40MHz BSS */
    else if (WLAN_BAND_5G == en_band)
    {
        en_flag_2040_op_permitted = OAL_TRUE;
    }

    if (OAL_TRUE == en_flag_2040_op_permitted)
    {
        pst_chan_scan_report[uc_pri_chan_idx].en_chan_op |= en_allowed_bit;
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_get_2040_op_chan_list
 ��������  : �����ŵ�ɨ����������ÿ���ŵ��Ƿ��ܹ�����BSS
 �������  : pst_mac_vap         : MAC VAP�ṹ��ָ��
 �������  : pst_chan_scan_report: �ŵ������ṹ��ָ��
 �� �� ֵ  : OAL_TRUE : ��ĳЩ�ŵ����ܹ�����40MHz BSS
             OAL_FALSE: ���κ��ŵ��϶����ܹ�����40MHz BSS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_get_2040_op_chan_list(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report)
{
    mac_device_stru       *pst_mac_device;
    oal_uint8              uc_chan_idx;
    oal_uint8              uc_num_supp_chan = mac_get_num_supp_channel(pst_mac_vap->st_channel.en_band);
    oal_bool_enum_uint8    en_fortyMHz_poss = OAL_FALSE;
    oal_bool_enum_uint8    en_flag;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_get_2040_op_chan_list}");

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_get_2040_op_chan_list::pst_mac_device null.}");
        return OAL_FALSE;
    }

    for (uc_chan_idx = 0; uc_chan_idx < uc_num_supp_chan; uc_chan_idx++)
    {
        /* �ж��ܷ���SCA���͵�40MHz BSS */
        en_flag = hmac_chan_is_this_40MHz_set_possible(pst_mac_device, pst_mac_vap, uc_chan_idx, MAC_SCA, pst_chan_scan_report);
        if (OAL_TRUE == en_flag)
        {
            en_fortyMHz_poss = OAL_TRUE;
        }

        /* �ж��ܷ���SCB���͵�40MHz BSS */
        en_flag = hmac_chan_is_this_40MHz_set_possible(pst_mac_device, pst_mac_vap, uc_chan_idx, MAC_SCB, pst_chan_scan_report);
        if (OAL_TRUE == en_flag)
        {
            en_fortyMHz_poss = OAL_TRUE;
        }
    }

    /* 2.4GHz�£����"40MHz������"λ�Ƿ����ã���������40MHz BSS */
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        if ((OAL_TRUE == pst_mac_device->en_40MHz_intol_bit_recd) ||
            (OAL_TRUE == mac_mib_get_FortyMHzIntolerant(pst_mac_vap)))
        {
            en_fortyMHz_poss = OAL_FALSE;
        }
    }

    return en_fortyMHz_poss;
}



/*****************************************************************************
 �� �� ��  : hmac_chan_del_user
 ��������  : ����40M intolerant user bitmap��Ϣ
 �������  : hmac_vap_stru *pst_hmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��23��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_chan_update_40M_intol_user(mac_vap_stru *pst_mac_vap,
                                    mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_40M_intol_bit)
{
    hmac_vap_stru   *pst_hmac_vap;
    oal_uint16       us_user_id;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_update_40M_intol_user::pst_hmac_vap null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_user_id = pst_mac_user->us_assoc_id;
    if (us_user_id >= 32*MAC_DEV_MAX_40M_INTOL_USER_BITMAP_LEN)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_update_40M_intol_user:: user id exceed max user id %d}",
                       us_user_id);
        return OAL_ERR_CODE_BUTT;
    }

    if (OAL_TRUE == en_40M_intol_bit)
    {
        pst_hmac_vap->aul_40M_intol_user_bitmap[us_user_id/32] |= (1<<(us_user_id%32));
    }
    else
    {
        pst_hmac_vap->aul_40M_intol_user_bitmap[us_user_id/32] &= ~((oal_uint32)(1<<(us_user_id%32)));
    }

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                   "{hmac_chan_update_40M_intol_user:: bitmap 0x%x 0x%x 0x%x 0x%x}",
                   pst_hmac_vap->aul_40M_intol_user_bitmap[0], pst_hmac_vap->aul_40M_intol_user_bitmap[1],
                   pst_hmac_vap->aul_40M_intol_user_bitmap[2], pst_hmac_vap->aul_40M_intol_user_bitmap[3]);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_prepare_for_40M_recovery
 ��������  : �ڻָ�40M֮ǰ��Ҫ���obssɨ������40M��ֹλ��20M requestλ����Ϣ
 �������  : hmac_vap_stru *pst_hmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_chan_prepare_for_40M_recovery(hmac_vap_stru *pst_hmac_vap,
                                            wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_prepare_for_40M_recovery::pst_device null,uc_device_id=%d.}",
                       pst_hmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device->en_40MHz_intol_bit_recd = OAL_FALSE;

    //l00311403 TODO �˴�Ҫȷ��һ���Ƿ���Ҫ��������pst_mac_device�е�
    //st_ap_channel_list�ŵ�?????????????

    /* ����VAP����ģʽΪ20MHz */
    pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth = en_bandwidth;

    /* ���ô����л�״̬��������������һ��DTIMʱ���л���20MHz���� */
    pst_hmac_vap->st_vap_base_info.st_ch_switch_info.en_bw_switch_status = WLAN_BW_SWITCH_20_TO_40;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_40M_recovery_timeout_fn
 ��������  : 40M�ָ���ʱ����ʱ���ָ�40M����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chan_40M_recovery_timeout_fn(void *p_arg)
{
    hmac_vap_stru          *pst_hmac_vap;
    mac_vap_stru           *pst_mac_vap;

    OAM_INFO_LOG0(0, OAM_SF_2040, "{hmac_chan_40M_recovery_timeout_fn::40M recovery timer time out.}");

    pst_hmac_vap = (hmac_vap_stru *)p_arg;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_chan_40M_recovery_timeout_fn::pst_dmac_vap null.}");
        return OAL_FAIL;
    }

    /* ���20M��ص���Ϣ */
    if (pst_hmac_vap->en_40M_bandwidth == WLAN_BAND_WIDTH_20M) /* ���ap��ʼ����Ϊ20M, ��*/
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                "{hmac_chan_40M_recovery_timeout_fn::no need 40M recovery because init 20M.}");
        return OAL_SUCC;
    }

    if (pst_hmac_vap->aul_40M_intol_user_bitmap[0] | pst_hmac_vap->aul_40M_intol_user_bitmap[1]
        | pst_hmac_vap->aul_40M_intol_user_bitmap[2] | pst_hmac_vap->aul_40M_intol_user_bitmap[3])
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                "{hmac_chan_40M_recovery_timeout_fn::no need 40M recovery because 40M intol sta assoc}");
        return OAL_SUCC;
    }

    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;
    if (WLAN_BAND_WIDTH_20M != pst_mac_vap->st_channel.en_bandwidth)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                "{hmac_chan_40M_recovery_timeout_fn::no need 40M recovery because already 20M}");
        hmac_chan_stop_40M_recovery_timer(pst_mac_vap);
        return OAL_SUCC;
    }

    hmac_chan_prepare_for_40M_recovery(pst_hmac_vap, pst_hmac_vap->en_40M_bandwidth);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                        pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_start_40M_recovery_timer
 ��������  : ����obssɨ�趨ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_chan_start_40M_recovery_timer(mac_vap_stru *pst_mac_vap)
{
    hmac_vap_stru                 *pst_hmac_vap;
    oal_uint32                     ul_timeout;

    /* ���ݷ���ɨ���vap id��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_2040, "{hmac_chan_start_40M_recovery_timer:: pst_hmac_vap is NULL.}");
        return;
    }

    //l00311403 TODO ȥ��
#if 1
    ul_timeout = mac_mib_get_BSSWidthTriggerScanInterval(pst_mac_vap) * 2 * 1000;
#else
    ul_timeout = 10000;
#endif
    OAM_INFO_LOG1(0, OAM_SF_2040, "{hmac_chan_start_40M_recovery_timer::ul_timeout=%d}", ul_timeout);

    if (OAL_FALSE == pst_hmac_vap->st_40M_recovery_timer.en_is_registerd)
    {
        FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_40M_recovery_timer),
                               hmac_chan_40M_recovery_timeout_fn,
                               ul_timeout,
                               (void *)pst_hmac_vap,
                               OAL_TRUE,
                               OAM_MODULE_ID_HMAC,
                               pst_mac_vap->ul_core_id);
    }
    else
    {
        FRW_TIMER_RESTART_TIMER(&(pst_hmac_vap->st_40M_recovery_timer), ul_timeout, OAL_TRUE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_stop_40M_recovery_timer
 ��������  : ����obssɨ�趨ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_chan_stop_40M_recovery_timer(mac_vap_stru *pst_mac_vap)
{
    hmac_vap_stru                 *pst_hmac_vap;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_2040, "{hmac_chan_stop_40M_recovery_timer:: pst_hmac_vap is NULL.}");
        return;
    }

    OAM_INFO_LOG0(0, OAM_SF_2040, "{hmac_chan_stop_40M_recovery_timer}");
    FRW_TIMER_STOP_TIMER(&(pst_hmac_vap->st_40M_recovery_timer));

    return;
}

#endif
/*****************************************************************************
 �� �� ��  : hmac_chan_get_40MHz_possibility
 ��������  : �ж��ڵ�ǰ����(ɨ����)�£��ܷ���40MHz BSS
 �������  : pst_mac_vap         : MAC VAP�ṹ��ָ��
 �������  : pst_chan_scan_report: �ŵ������ṹ��ָ��
 �� �� ֵ  : OAL_TRUE : �ܹ�����
             OAL_FALSE: ���ܽ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_chan_get_40MHz_possibility(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report)
{
    oal_bool_enum_uint8   en_fortyMHz_poss = OAL_FALSE;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_get_40MHz_possibility}");
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    if (OAL_TRUE ==  mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
    {
        en_fortyMHz_poss = hmac_chan_get_2040_op_chan_list(pst_mac_vap, pst_chan_scan_report);
    }
#endif

    return en_fortyMHz_poss;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_init_chan_scan_report
 ��������  : �⺯����������Ҫ��Ҫ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_chan_init_chan_scan_report(
                mac_device_stru              *pst_mac_device,
                hmac_eval_scan_report_stru   *pst_chan_scan_report,
                oal_uint8                     uc_num_supp_chan)
{
    oal_uint8    uc_idx;

    OAL_MEMZERO(pst_chan_scan_report, uc_num_supp_chan * OAL_SIZEOF(*pst_chan_scan_report));

    for (uc_idx = 0; uc_idx < uc_num_supp_chan; uc_idx++)
    {
    #ifdef _PRE_WLAN_FEATURE_DFS
        if (OAL_TRUE == mac_dfs_get_dfs_enable(pst_mac_device))
        {
            if ((MAC_CHAN_NOT_SUPPORT        != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status) &&
                (MAC_CHAN_BLOCK_DUE_TO_RADAR != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status))
            {
                pst_chan_scan_report[uc_idx].en_chan_op |= HMAC_OP_ALLOWED;
            }
        }
        else
    #endif
        {
            pst_chan_scan_report[uc_idx].en_chan_op |= HMAC_OP_ALLOWED;
        }
    }
}

/*****************************************************************************
 �� �� ��  : hmac_chan_is_40MHz_sca_allowed
 ��������  : ���ڸ��������ŵ����ж��ܷ���SCA���͵�40MHz BSS
 �������  : pst_mac_vap         : MAC VAP�ṹ��ָ��
             pst_chan_scan_report: �ŵ������ṹ��ָ��
             uc_pri_chan_idx     : ���ŵ�������
             en_user_chan_offset : �û�����ѡ��Ĵ��ŵ�ƫ����
 �������  : ��
 �� �� ֵ  : OAL_TRUE : �ܹ�����40MHz BSS
             OAL_FALSE: ���ܽ���40MHz BSS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_40MHz_sca_allowed(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report,
                oal_uint8                     uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8     en_user_chan_offset)
{
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8                       uc_sec_chan_idx = 0;
    oal_uint32                      ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
            "{hmac_chan_is_40MHz_sca_allowed::uc_pri_chan_idx=%d, en_user_chan_offset=%d}",
            uc_pri_chan_idx, en_user_chan_offset);

    if (MAC_SCB == en_user_chan_offset)
    {
        return OAL_FALSE;
    }

    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (WLAN_BAND_2G == en_band))
    {
        if (!(pst_chan_scan_report[uc_pri_chan_idx].en_chan_op & HMAC_SCA_ALLOWED))
        {
            return OAL_FALSE;
        }
    }

    uc_sec_chan_idx = uc_pri_chan_idx + mac_get_sec_ch_idx_offset(en_band);
    if (uc_sec_chan_idx >= uc_num_supp_chan)
    {
        return OAL_FALSE;
    }

    ul_ret = mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
#else
    return OAL_FALSE;
#endif
}

/*****************************************************************************
 �� �� ��  : hmac_chan_is_40MHz_scb_allowed
 ��������  : ���ڸ��������ŵ����ж��ܷ���SCB���͵�40MHz BSS
 �������  : pst_mac_vap         : MAC VAP�ṹ��ָ��
             pst_chan_scan_report: �ŵ������ṹ��ָ��
             uc_pri_chan_idx     : ���ŵ�������
             en_user_chan_offset : �û�����ѡ��Ĵ��ŵ�ƫ����
 �������  : ��
 �� �� ֵ  : OAL_TRUE : �ܹ�����40MHz BSS
             OAL_FALSE: ���ܽ���40MHz BSS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_40MHz_scb_allowed(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report,
                oal_uint8                     uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8     en_user_chan_offset)
{
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_sec_ch_idx_offset = mac_get_sec_ch_idx_offset(en_band);
    oal_uint8                       uc_sec_chan_idx = 0;
    oal_uint32                      ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
            "{hmac_chan_is_40MHz_sca_allowed::uc_pri_chan_idx=%d, en_user_chan_offset=%d}",
            uc_pri_chan_idx, en_user_chan_offset);

    if (MAC_SCA == en_user_chan_offset)
    {
        return OAL_FALSE;
    }

    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (WLAN_BAND_2G == en_band))
    {
        if (!(pst_chan_scan_report[uc_pri_chan_idx].en_chan_op & HMAC_SCB_ALLOWED))
        {
            return OAL_FALSE;
        }
    }

    if (uc_pri_chan_idx >= uc_sec_ch_idx_offset)
    {
        uc_sec_chan_idx = uc_pri_chan_idx - uc_sec_ch_idx_offset;
    }
    else
    {
        return OAL_FALSE;
    }

    ul_ret = mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
#else
    return OAL_FALSE;
#endif
}

/*****************************************************************************
 �� �� ��  : hmac_chan_get_cumulative_networks
 ��������  : ��ȡ��ǰ�ŵ��ڽ�(+/- 3���ŵ�)��BSS����
 �������  : pst_mac_device : MAC DEVICE�ṹ��ָ��
             en_band        : Ƶ��
             uc_pri_chan_idx: ���ŵ�������
 �������  : ��
 �� �� ֵ  : ��ǰ�ŵ��ڽ���BSS����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  hmac_chan_get_cumulative_networks(
                mac_device_stru                     *pst_mac_device,
                wlan_channel_bandwidth_enum_uint8    en_band,
                oal_uint8                            uc_pri_chan_idx)
{
    oal_uint16   us_cumulative_networks = 0;
    oal_uint8    uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8    uc_affected_ch_idx_offset = mac_get_affected_ch_idx_offset(en_band);
    oal_uint8    uc_affected_chan_lo, uc_affected_chan_hi;
    oal_uint8    uc_chan_idx;
    oal_uint32   ul_ret;

    uc_affected_chan_lo = (uc_pri_chan_idx >= uc_affected_ch_idx_offset) ?
                    (uc_pri_chan_idx - uc_affected_ch_idx_offset) : 0;

    uc_affected_chan_hi = (uc_num_supp_chan > uc_pri_chan_idx + uc_affected_ch_idx_offset) ?
                    (uc_pri_chan_idx + uc_affected_ch_idx_offset) : (uc_num_supp_chan - 1);

    for (uc_chan_idx = uc_affected_chan_lo; uc_chan_idx <= uc_affected_chan_hi; uc_chan_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            us_cumulative_networks += pst_mac_device->st_ap_channel_list[uc_pri_chan_idx].us_num_networks;
        }
    }

    return us_cumulative_networks;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_get_user_pref_primary_ch
 ��������  : ��ȡ�û��������õ��ŵ�
 �������  : pst_mac_device: MAC DEVICE�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �û��������õ��ŵ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  hmac_chan_get_user_pref_primary_ch(mac_device_stru *pst_mac_device)
{
    return pst_mac_device->uc_max_channel;
}

/*****************************************************************************
 �� �� ��  : hmac_get_user_pref_bandwidth
 ��������  : ��ȡ�û��������õĴ���ģʽ
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �û��������õĴ���ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_channel_bandwidth_enum_uint8  hmac_chan_get_user_pref_bandwidth(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->st_ch_switch_info.en_user_pref_bandwidth;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_select_channel_for_operation
 ��������  : ��ѡһ���ŵ�(��)
 �������  : pst_mac_vap      : MAC VAP�ṹ��ָ��
 �������  : puc_new_channel  : ��ѡ���������ŵ���
             pen_new_bandwidth: ��ѡ�����Ĵ���ģʽ
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_chan_select_channel_for_operation(
                mac_vap_stru                        *pst_mac_vap,
                oal_uint8                           *puc_new_channel,
                wlan_channel_bandwidth_enum_uint8   *pen_new_bandwidth)
{
    mac_device_stru                     *pst_mac_device;
    hmac_eval_scan_report_stru          *pst_chan_scan_report;
    oal_uint8                            uc_least_busy_chan_idx = 0xFF;
    oal_uint16                           us_least_networks = 0xFFFF;
    oal_uint16                           us_cumulative_networks = 0;
    oal_bool_enum_uint8                  en_fortyMHz_poss, en_rslt = OAL_FALSE;
    mac_sec_ch_off_enum_uint8            en_user_chan_offset = MAC_SEC_CH_BUTT, en_chan_offset = MAC_SCN;
    oal_uint8                            uc_user_chan_idx = 0xFF, uc_chan_idx = 0xFF;
    oal_uint8                            uc_num_supp_chan = mac_get_num_supp_channel(pst_mac_vap->st_channel.en_band);
    oal_uint8                            uc_max_supp_channle = MAC_MAX_SUPP_CHANNEL;
    oal_uint32                           ul_ret = OAL_FAIL;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,"{hmac_chan_select_channel_for_operation}");

    // cppcheck-suppress * ignore Uninitialized variable: pst_chan_scan_report
    pst_chan_scan_report = (hmac_eval_scan_report_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, uc_max_supp_channle * OAL_SIZEOF(*pst_chan_scan_report), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_chan_scan_report))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_select_channel_for_operation::pst_chan_scan_report memory alloc failed, size[%d].}", (uc_max_supp_channle * OAL_SIZEOF(*pst_chan_scan_report)));
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_select_channel_for_operation::pst_mac_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        OAL_MEM_FREE((oal_void *)pst_chan_scan_report, OAL_TRUE);

        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_chan_init_chan_scan_report(pst_mac_device, pst_chan_scan_report, uc_num_supp_chan);

    /* ���Զ��ŵ�ѡ��û�п��������ȡ�û�ѡ������ŵ��ţ��Լ�����ģʽ */
    if (OAL_FALSE == mac_device_is_auto_chan_sel_enabled(pst_mac_device))
    {
#ifdef _PRE_WLAN_FEATURE_DBAC
        if(mac_is_dbac_enabled(pst_mac_device))
        {
            ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                            pst_mac_vap->st_channel.uc_chan_number, &uc_user_chan_idx) ;
        }
        else
#endif
        {
            ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                            hmac_chan_get_user_pref_primary_ch(pst_mac_device), &uc_user_chan_idx) ;
        }
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_select_channel_for_operation::mac_get_channel_idx_from_num failed[%d].}", ul_ret);
            OAL_MEM_FREE((oal_void *)pst_chan_scan_report, OAL_TRUE);

            return ul_ret;
        }

        en_user_chan_offset = mac_get_sco_from_bandwidth(hmac_chan_get_user_pref_bandwidth(pst_mac_vap));

        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                      "{hmac_chan_select_channel_for_operation::User Preferred Channel id=%d sco=%d.}",
                      uc_user_chan_idx, en_user_chan_offset);
    }

    /* �ж��ڵ�ǰ�������Ƿ��ܹ�����40MHz BSS */
    en_fortyMHz_poss = hmac_chan_get_40MHz_possibility(pst_mac_vap, pst_chan_scan_report);

    /* �û�ѡ�������ŵ� */
    if (uc_user_chan_idx != 0xFF)
    {
        /* ����ܹ�����40MHz BSS�������û�Ҳϣ������40MHz */
        if ((OAL_TRUE == en_fortyMHz_poss) && (MAC_SCN != en_user_chan_offset))
        {
            if (MAC_SCA == en_user_chan_offset)
            {
                en_rslt = hmac_chan_is_40MHz_sca_allowed(pst_mac_vap, pst_chan_scan_report, uc_user_chan_idx, en_user_chan_offset);
            }
            else if (MAC_SCB == en_user_chan_offset)
            {
                en_rslt = hmac_chan_is_40MHz_scb_allowed(pst_mac_vap, pst_chan_scan_report, uc_user_chan_idx, en_user_chan_offset);
            }
        }

        if (OAL_TRUE == en_rslt)
        {
            en_chan_offset = en_user_chan_offset;
        }

        uc_least_busy_chan_idx = uc_user_chan_idx;
    }
    /* �û�û��ѡ���ŵ����Զ�ѡ��һ�����æ���ŵ�(��) */
    else
    {
        for (uc_chan_idx = 0; uc_chan_idx < uc_num_supp_chan; uc_chan_idx++)
        {
            if (!(pst_chan_scan_report[uc_chan_idx].en_chan_op & HMAC_OP_ALLOWED))
            {
                continue;
            }

            /* �ж����ŵ��������Ƿ���Ч */
            ul_ret = mac_is_channel_idx_valid(pst_mac_vap->st_channel.en_band, uc_chan_idx);
            if (OAL_SUCC != ul_ret)
            {
                continue;
            }

            /* �ܹ�����40MHz BSS */
            if ((OAL_TRUE == en_fortyMHz_poss))
            {
                /* �ж����ŵ���(��)����ŵ��Ƿ����Ϊ���ŵ� */
                en_rslt = hmac_chan_is_40MHz_sca_allowed(pst_mac_vap, pst_chan_scan_report, uc_chan_idx, en_user_chan_offset);
                if (OAL_TRUE == en_rslt)
                {
                    /* ��������ŵ����æ����ѡ�������ŵ���Ϊ"��ǰ���æ�ŵ�" */
                    if (pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCA] < us_least_networks)
                    {
                        us_least_networks      = pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCA];
                        uc_least_busy_chan_idx = uc_chan_idx;
                        en_chan_offset         = MAC_SCA;
                    }
                }

                /* �ж����ŵ���(��)����ŵ��Ƿ����Ϊ���ŵ� */
                en_rslt = hmac_chan_is_40MHz_scb_allowed(pst_mac_vap, pst_chan_scan_report, uc_chan_idx, en_user_chan_offset);
                if (OAL_TRUE == en_rslt)
                {
                    /* ��������ŵ����æ����ѡ�������ŵ���Ϊ"��ǰ���æ�ŵ�" */
                    if (pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCB] < us_least_networks)
                    {
                        us_least_networks      = pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCB];
                        uc_least_busy_chan_idx = uc_chan_idx;
                        en_chan_offset         = MAC_SCB;
                    }
                }
            }
            /* ���ܹ�����40MHz BSS */
            else
            {
                /* ��ȡ��ǰ�ŵ��ڽ���BSS���� */
                us_cumulative_networks = hmac_chan_get_cumulative_networks(pst_mac_device,
                                pst_mac_vap->st_channel.en_band, uc_chan_idx);

                /* ѡ���ڽ�BSS���ٵ�һ���ŵ���Ϊ"��ǰ���æ�ŵ�" */
                if (us_cumulative_networks < us_least_networks)
                {
                    us_least_networks      = us_cumulative_networks;
                    uc_least_busy_chan_idx = uc_chan_idx;
                }
            }
        }
    }

    mac_get_channel_num_from_idx(pst_mac_vap->st_channel.en_band, uc_least_busy_chan_idx, puc_new_channel);

    *pen_new_bandwidth = mac_get_bandwidth_from_sco(en_chan_offset);

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                  "{hmac_chan_select_channel_for_operation::Selected Channel=%d, Selected Bandwidth=%d.}",
                  (*puc_new_channel), (*pen_new_bandwidth));

    OAL_MEM_FREE((oal_void *)pst_chan_scan_report, OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_reval_status
 ��������  : ����OBSSɨ����������ѡ��һ������ʵĹ����ŵ�
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             puc_data   : ָ��20/40 BSS Intolerant Channel Report element��
                          "Channel List"��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��22��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_reval_status(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap)
{
    oal_uint8                            uc_new_channel   = 0;
    wlan_channel_bandwidth_enum_uint8    en_new_bandwidth = WLAN_BAND_WIDTH_BUTT;
    oal_uint32                           ul_ret;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_reval_status}");

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_chan_reval_status::pst_mac_device or pst_mac_vap null.}", pst_mac_device, pst_mac_vap);
        return;
    }

    /* ���AP�Ѿ�׼�������ŵ��л�����ֱ�ӷ��أ������κδ��� */
    if (WLAN_CH_SWITCH_STATUS_1 == pst_mac_vap->st_ch_switch_info.en_ch_switch_status)
    {
        return;
    }

    ul_ret = hmac_chan_select_channel_for_operation(pst_mac_vap, &uc_new_channel, &en_new_bandwidth);
    if (OAL_SUCC != ul_ret)
    {
        return;
    }

    ul_ret = mac_is_channel_num_valid(pst_mac_vap->st_channel.en_band, uc_new_channel);
    if ((OAL_SUCC != ul_ret) || (en_new_bandwidth >= WLAN_BAND_WIDTH_BUTT))
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_chan_reval_status::Could not start network using the selected channel[%d] or bandwidth[%d].}",
                         uc_new_channel, en_new_bandwidth);
        return;
    }

    /* ��20MHz�ŵ��ı�(����Ŀǰ���㷨�����ŵ���Ӧ�ò���ı䣬���ܻ�ı��ֻ�Ǵ���ģʽ) */
    if (uc_new_channel != pst_mac_vap->st_channel.uc_chan_number)
    {
        pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt = WLAN_CHAN_SWITCH_DEFAULT_CNT;
        hmac_chan_multi_switch_to_new_channel(pst_mac_vap, uc_new_channel, en_new_bandwidth);
    }
    /* ��20MHz�ŵ����䣬��20MHz or 40MHz�ŵ��ı� */
    else if (en_new_bandwidth != pst_mac_vap->st_channel.en_bandwidth)
    {
        hmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number, en_new_bandwidth);
        hmac_send_ht_notify_chan_width(pst_mac_vap, BROADCAST_MACADDR);
    }
    else
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_reval_status::No Channel change after re-evaluation.}");
    }
}

/*****************************************************************************
 �� �� ��  : hmac_chan_reval_bandwidth_sta
 ��������  : �����Ƿ���Ҫ���д����л�������Ҫ����֪ͨӲ�����д����л�
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_reval_bandwidth_sta(mac_vap_stru *pst_mac_vap, oal_uint32 ul_change)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_chan_reval_bandwidth_sta::pst_mac_vap null.}");
        return;
    }

    /* ��Ҫ���д����л� */
    if (MAC_BW_CHANGE & ul_change)
    {
        hmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);
    }
}


/*****************************************************************************
 �� �� ��  : hmac_chan_ctrl_machw_tx
 ��������  : ����Ӳ���Ƿ���(����֡��ACK��RTS)
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             uc_sub_type: �¼�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��17��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_chan_ctrl_machw_tx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_sub_type)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    oal_uint32                ul_ret;

    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ctrl_machw_tx::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    uc_sub_type,
                    0,
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ctrl_machw_tx::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 �� �� ��  : hmac_chan_disable_machw_tx
 ��������  : ��ֹӲ������(����֡��ACK��RTS)
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_disable_machw_tx(mac_vap_stru *pst_mac_vap)
{
    hmac_chan_ctrl_machw_tx(pst_mac_vap, DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX);
}

/*****************************************************************************
 �� �� ��  : hmac_chan_enable_machw_tx
 ��������  : �ָ�Ӳ������(����֡��ACK��RTS)
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_enable_machw_tx(mac_vap_stru *pst_mac_vap)
{
    hmac_chan_ctrl_machw_tx(pst_mac_vap, DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX);
}

/*****************************************************************************
 �� �� ��  : hmac_chan_check_chan_avail
 ��������  : �Զ��ŵ�ѡ����Ч�Լ��
 �������  : en_band         : Ƶ��(0: 2.4GHz; 1: 5GHz)
 �������  : puc_start_ch_idx: ��Ҫɨ��ĵ�һ���ŵ�����
             puc_end_ch_idx  : ��Ҫɨ������һ���ŵ�����
 �� �� ֵ  : OAL_TRUE : �ɹ�
             OAL_FALSE: ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_chan_check_channnel_avaible(
                wlan_channel_band_enum_uint8    en_band,
                oal_uint8                      *puc_start_ch_idx,
                oal_uint8                      *puc_end_ch_idx)
{
    oal_int32    l_ch_idx;
    oal_uint8    uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint32   ul_ret;

    /* ȡ����Ч�ŵ� */
    for (l_ch_idx = *puc_start_ch_idx; l_ch_idx < uc_num_supp_chan; l_ch_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, (oal_uint8)l_ch_idx);
        if (OAL_SUCC == ul_ret)
        {
            *puc_start_ch_idx = (oal_uint8)l_ch_idx;
            break;
        }
    }

    if (l_ch_idx == uc_num_supp_chan)
    {
        return OAL_FALSE;
    }

    /* ȡ����Ч�ŵ� */
    for (l_ch_idx = *puc_end_ch_idx; l_ch_idx >= 0; l_ch_idx--)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, (oal_uint8)l_ch_idx);
        if (OAL_SUCC == ul_ret)
        {
            *puc_end_ch_idx = (oal_uint8)l_ch_idx;
            break;
        }
    }

    if (l_ch_idx < 0)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_get_affected_channels
 ��������  : ������Ҫɨ����ŵ���Χ��ɨ��ķ�Χ����Ҫ����40MHz BSS������Ƶ�� +/- 5���ŵ���
             ������Ҫ�������ŵ�Ϊ5�����ŵ�Ϊ9��40MHz BSS����ɨ���ŵ�2~12
 �������  : en_band               : Ƶ��(0: 2.4GHz; 1: 5GHz)
             uc_user_pri_ch_idx    : �û�ѡ����ŵ�����
             en_user_pref_bandwidth: �û�ѡ��Ĵ���ģʽ
 �������  : puc_start_ch_idx: ��Ҫɨ��ĵ�һ���ŵ�����
             puc_end_ch_idx  : ��Ҫɨ������һ���ŵ�����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  hmac_chan_get_affected_channels(
                wlan_channel_band_enum_uint8         en_band,
                oal_uint8                            uc_user_pri_ch_idx,
                wlan_channel_bandwidth_enum_uint8    en_user_pref_bandwidth,
                oal_uint8                           *puc_start_ch_idx,
                oal_uint8                           *puc_end_ch_idx)
{
    oal_uint8    uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8    uc_pll_div_idx = 0;   /* ����Ƶ�� */

    /* ��������Ƶ�� */
    if (WLAN_BAND_WIDTH_40PLUS == en_user_pref_bandwidth)
    {
        uc_pll_div_idx = uc_user_pri_ch_idx + HMAC_CENTER_FREQ_2G_40M_OFFSET;
    }
    else if (WLAN_BAND_WIDTH_40MINUS == en_user_pref_bandwidth)
    {
        uc_pll_div_idx = uc_user_pri_ch_idx - HMAC_CENTER_FREQ_2G_40M_OFFSET;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_chan_get_affected_channels::invalid bandwidth[%d].}", en_user_pref_bandwidth);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* ������Ҫɨ����ŵ��������� */
    *puc_start_ch_idx = (uc_pll_div_idx >= HMAC_AFFECTED_CH_IDX_OFFSET) ?
                    (uc_pll_div_idx - HMAC_AFFECTED_CH_IDX_OFFSET) : 0;

    /* ������Ҫɨ����ŵ��������� */
    *puc_end_ch_idx   = (uc_num_supp_chan > uc_pll_div_idx + HMAC_AFFECTED_CH_IDX_OFFSET) ?
                    (uc_pll_div_idx + HMAC_AFFECTED_CH_IDX_OFFSET) : (uc_num_supp_chan - 1);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_is_scan_needed_for_multi_vap
 ��������  : ��VAP����£���BSS����ǰ���ж��Ƿ���Ҫ�����ŵ�ɨ��
 �������  : pst_mac_device  : MAC DEVICE�ṹ��ָ��
             pst_mac_vap     : MAC VAP�ṹ��ָ��(AP)
 �������  : ��
 �� �� ֵ  : OAL_TRUE : ��Ҫ����ɨ��
             OAL_FALSE: ����Ҫ����ɨ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_scan_needed_for_multi_vap(
                mac_device_stru   *pst_mac_device,
                mac_vap_stru      *pst_mac_vap)
{
    mac_vap_stru   *pst_vap;
    oal_uint8       uc_vap_idx;

    /* ��һ��VAP(AP)����ǰ��������Ҫ�����ŵ�ɨ�裬ֱ�ӷ��� */
    if (1 == pst_mac_device->uc_vap_num)
    {
        return OAL_TRUE;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN,
                           "{hmac_chan_is_scan_needed_for_multi_vap::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* ������VAP */
        if (pst_vap->uc_vap_id == pst_mac_vap->uc_vap_id)
        {
            continue;
        }

        if (MAC_VAP_STATE_INIT != pst_vap->en_vap_state)
        {
            return OAL_FALSE;
        }
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_is_chan_scan_needed
 ��������  : �ж���BSS����ǰ���Ƿ���Ҫ�����ŵ�ɨ��
 �������  : pst_mac_device  : MAC DEVICE�ṹ��ָ��
             pst_mac_vap     : MAC VAP�ṹ��ָ��(AP)
 �������  : puc_start_ch_idx: ��Ҫɨ��ĵ�һ���ŵ�����
             puc_end_ch_idx  : ��Ҫɨ������һ���ŵ�����
 �� �� ֵ  : OAL_TRUE : ��Ҫ����ɨ��
             OAL_FALSE: ����Ҫ����ɨ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_chan_scan_needed(
                mac_device_stru   *pst_mac_device,
                mac_vap_stru      *pst_mac_vap,
                oal_uint8         *puc_start_ch_idx,
                oal_uint8         *puc_end_ch_idx)
{
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_bool_enum_uint8             en_rslt;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
	oal_uint8                       uc_user_ch_idx;
    oal_uint32                      ul_ret;
#endif

    /* 5gƵ��û��20/40����,���������BSS����ʱֱ�������ŵ�������Ҫ����ɨ�裬������� */
    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (WLAN_BAND_5G == en_band))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_is_chan_scan_needed::20/40 MHz BSS only in 2.4G.}");
        return OAL_FALSE;
    }

    /* ��������Զ��ŵ�ѡ����BSS����ʱ��Ҫ����ɨ�� */
    if (OAL_TRUE == mac_device_is_auto_chan_sel_enabled(pst_mac_device))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_is_chan_scan_needed::Auto Channel Selection in progress.}");
        *puc_start_ch_idx = 0;
        *puc_end_ch_idx   = uc_num_supp_chan - 1;

        if (OAL_FALSE == hmac_chan_check_channnel_avaible(en_band, puc_start_ch_idx, puc_end_ch_idx))
        {
            return OAL_FALSE;
        }

        return OAL_TRUE;
    }

    en_rslt = hmac_chan_is_scan_needed_for_multi_vap(pst_mac_device, pst_mac_vap);
    if (OAL_TRUE != en_rslt)
    {
    #ifdef _PRE_WLAN_FEATURE_DBAC
        if (OAL_FALSE == mac_is_dbac_enabled(pst_mac_device))
        {
            pst_mac_vap->st_channel.uc_chan_number = pst_mac_device->uc_max_channel;
        }
    #else
        pst_mac_vap->st_channel.uc_chan_number = pst_mac_device->uc_max_channel;
    #endif

        return OAL_FALSE;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* �����ŵ�ɨ�裬���ҽ���: */
    /* (1) 20/40MHz����ʹ�� */
    /* (2) ׼������40MHz BSS */
    /* (3) 2.4GHz */
    if ((OAL_TRUE     == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (OAL_TRUE     == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))        &&
        (WLAN_BAND_2G == en_band))
    {
        ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                        hmac_chan_get_user_pref_primary_ch(pst_mac_device), &uc_user_ch_idx) ;
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_is_chan_scan_needed::mac_get_channel_idx_from_num failed[%d].}", ul_ret);
            return OAL_FALSE;
        }

        //l00311403 TODO ����80M/160M, Ҫ���µ���Ӱ�췶Χ
        /* ��ȡ��Ҫɨ����ŵ���Χ */
        ul_ret = hmac_chan_get_affected_channels(en_band, uc_user_ch_idx, hmac_chan_get_user_pref_bandwidth(pst_mac_vap), puc_start_ch_idx, puc_end_ch_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_is_chan_scan_needed::hmac_chan_get_affected_channels failed[%d].}", ul_ret);
            return OAL_FALSE;
        }

        if (OAL_FALSE == hmac_chan_check_channnel_avaible(en_band, puc_start_ch_idx, puc_end_ch_idx))
        {
            return OAL_FALSE;
        }

        return OAL_TRUE;
    }
#endif

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_start_bss_in_available_channel
 ��������  : ��ָ��(����)�ŵ�������BSS
 �������  : pst_hmac_vap: HMAC VAPָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_start_bss_in_available_channel(hmac_vap_stru *pst_hmac_vap)
{
    hmac_ap_start_rsp_stru          st_ap_start_rsp;
    oal_uint32                      ul_ret;

    /* ����hmac_config_start_vap_event������BSS */
    ul_ret = hmac_config_start_vap_event(&(pst_hmac_vap->st_vap_base_info), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                        "{hmac_start_bss_in_available_channel::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ����bssid */
    mac_vap_set_bssid(&pst_hmac_vap->st_vap_base_info, pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* �����Ż�����ͬƵ���µ�������һ�� */
    if (WLAN_BAND_2G == pst_hmac_vap->st_vap_base_info.st_channel.en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(&(pst_hmac_vap->st_vap_base_info), WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&(pst_hmac_vap->st_vap_base_info), OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(&(pst_hmac_vap->st_vap_base_info), WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&(pst_hmac_vap->st_vap_base_info), OAL_TRUE);
    }

    /* ����AP��״̬��Ϊ UP */
    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_UP);

    /* ������ϱ���sme */
    st_ap_start_rsp.en_result_code = HMAC_MGMT_SUCCESS;
    hmac_send_rsp_to_sme_ap(pst_hmac_vap, HMAC_AP_SME_START_RSP, (oal_uint8 *)&st_ap_start_rsp);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_start_bss
 ��������  : ��ѡһ���ŵ�(��)��������BSS
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             mac_channel_stru *pst_channel,
             wlan_protocol_enum_uint8 en_protocol
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��1��
    ��    ��   : gaolin
    �޸�����   : ������������-�ŵ���Э��ģʽ
*****************************************************************************/
oal_uint32  hmac_chan_start_bss(hmac_vap_stru *pst_hmac_vap, mac_channel_stru *pst_channel, wlan_protocol_enum_uint8 en_protocol)
{
    mac_device_stru                     *pst_mac_device;
    mac_vap_stru                        *pst_mac_vap;
    oal_uint32                           ul_ret;
    mac_cfg_mode_param_stru              st_prot_param;
    mac_channel_stru                    *pst_channel_dst = OAL_PTR_NULL;

    if (!pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_chan_start_bss::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);

    /* ��ȡmac deviceָ�� */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_start_bss::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_channel)
    {
        pst_channel_dst = pst_channel;
    }
#ifdef _PRE_SUPPORT_ACS
    else // use acs-channel only if no channel input
    {
        /* ʹ��acsѡ����ŵ��ʹ��� */
        if (MAC_ACS_SW_INIT == mac_get_acs_switch(pst_mac_device) || MAC_ACS_SW_BOTH == mac_get_acs_switch(pst_mac_device))
        {
            hmac_device_stru   *pst_hmac_device = hmac_res_get_mac_dev(pst_mac_device->uc_device_id);
            if (!pst_hmac_device || 0 == pst_hmac_device->ast_best_channel[pst_mac_vap->st_channel.en_band].uc_chan_number)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                                 "{hmac_chan_start_bss::init acs enabled, but best channel of BAND%d is 0", pst_mac_vap->st_channel.en_band);
            }
            else
            {
                pst_channel_dst = &pst_hmac_device->ast_best_channel[pst_mac_vap->st_channel.en_band];
            }
        }
    }
#endif
    if (!pst_channel_dst)
    {
        pst_channel_dst = &pst_mac_vap->st_channel;
    }

    st_prot_param.en_channel_idx = pst_channel_dst->uc_chan_number;
    st_prot_param.en_bandwidth   = pst_channel_dst->en_bandwidth;
    st_prot_param.en_band        = pst_channel_dst->en_band;

    // use input protocol if exists
    st_prot_param.en_protocol = (en_protocol >= WLAN_PROTOCOL_BUTT) ? pst_mac_vap->en_protocol : en_protocol;

    ul_ret = mac_is_channel_num_valid(st_prot_param.en_band, st_prot_param.en_channel_idx);
    if (OAL_SUCC != ul_ret)
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_chan_start_bss::mac_is_channel_num_valid failed[%d].}", ul_ret);
        return ul_ret;
    }

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                  "{hmac_chan_start_bss::AP: Starting network in Channel: %d, bandwidth: %d.}",
                  st_prot_param.en_channel_idx, st_prot_param.en_bandwidth);

#ifdef _PRE_WLAN_FEATURE_DBAC
    /* ͬʱ���Ķ��VAP���ŵ�����ʱ��Ҫǿ�������¼ */
    /* ��������DBAC������ԭʼ���̽��� */
    if (!mac_is_dbac_enabled(pst_mac_device))
#endif
    {
        pst_mac_device->uc_max_channel = 0;
        pst_mac_device->en_max_bandwidth = WLAN_BAND_WIDTH_BUTT;
    }

    // force channel setting is required
    oal_memcopy(&pst_mac_vap->st_channel, pst_channel_dst, OAL_SIZEOF(mac_channel_stru));

    ul_ret = hmac_config_set_freq(pst_mac_vap, OAL_SIZEOF(oal_uint8), &st_prot_param.en_channel_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                        "{hmac_chan_start_bss::hmac_config_set_freq failed[%d].}", ul_ret);
        return ul_ret;
    }

    ul_ret = hmac_config_set_mode(pst_mac_vap, (oal_uint16)OAL_SIZEOF(st_prot_param), (oal_uint8 *)&st_prot_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_chan_start_bss::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    return hmac_start_bss_in_available_channel(pst_hmac_vap);
}
/*****************************************************************************
 �� �� ��  : hmac_chan_ch_av_chk_timeout_fn
 ��������  : BSS�ϵ�ɨ�賬ʱ����
 �������  : p_arg: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_chan_ch_av_chk_timeout_fn(void *p_arg)
{
    mac_device_stru              *pst_mac_device;
    hmac_vap_stru                *pst_hmac_vap;
    mac_vap_stru                 *pst_mac_vap;
    mac_chnl_av_chk_enum_uint8    en_status;

    pst_mac_vap   = (mac_vap_stru *)p_arg;
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ch_av_chk_timeout_fn::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ch_av_chk_timeout_fn::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_CH_SWITCH_STATUS_1 == pst_mac_vap->st_ch_switch_info.en_ch_switch_status)
    {
        return OAL_SUCC;
    }

    /* ���������ŵ�ɨ�� */
    en_status = hmac_chan_do_channel_availability_check(pst_mac_device, pst_mac_vap, OAL_FALSE);

    /* ����ŵ�ɨ������ɣ���ѡ��һ���ŵ�(��)������BSS */
    if (MAC_CHNL_AV_CHK_COMPLETE == en_status)
    {
        hmac_chan_start_bss(pst_hmac_vap, OAL_PTR_NULL, WLAN_PROTOCOL_BUTT);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chan_do_channel_availability_check
 ��������  : BSS����ʱ������ѡ����ŵ��б���б���ɨ��(����ѡ�񲻽���ɨ��)
 �������  : pst_mac_device: MAC DEVICE�ṹ��ָ��
             pst_mac_vap   : MAC VAP�ṹ��ָ��(AP)
             en_first_time : �Ƿ��ǵ�һ�ν����������(������ʱ����ʱ����������������
                             ��ʱ����ΪOAL_FALSE)
 �������  : ��
 �� �� ֵ  : MAC_CHNL_AV_CHK_NOT_REQ : ����Ҫ�����ŵ�ɨ��
             MAC_CHNL_AV_CHK_IN_PROG : ���ڽ����ŵ�ɨ��
             MAC_CHNL_AV_CHK_COMPLETE: �ŵ�ɨ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

******************************************************************************/
mac_chnl_av_chk_enum_uint8  hmac_chan_do_channel_availability_check(
                mac_device_stru       *pst_mac_device,
                mac_vap_stru          *pst_mac_vap,
                oal_bool_enum_uint8    en_first_time)
{
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    mac_ch_switch_info_stru        *pst_csi = &(pst_mac_vap->st_ch_switch_info);
    oal_uint8                       uc_channel = 0;
    oal_bool_enum_uint8             en_need_for_scan = OAL_FALSE;
    oal_bool_enum_uint8             en_scan_itr_over = OAL_FALSE;

    for(;;)
    {
        if (en_first_time)
        {
            /* �ж��Ƿ���Ҫ�����ŵ�ɨ�� */
	     en_need_for_scan = hmac_chan_is_chan_scan_needed(pst_mac_device, pst_mac_vap, &(pst_csi->uc_start_chan_idx), &(pst_csi->uc_end_chan_idx));
            if (OAL_FALSE == en_need_for_scan)
            {
                OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                              "{hmac_chan_do_channel_availability_check::Channel scanning not needed.}");
		 return MAC_CHNL_AV_CHK_NOT_REQ;
            }
            else
            {
                OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                              "{hmac_chan_do_channel_availability_check::Channel scanning from %d to %d.}",
                              pst_csi->uc_start_chan_idx, pst_csi->uc_end_chan_idx);
            }

            /* ��ʼ���ŵ�ɨ���������ӵ�һ����Ҫɨ����ŵ���ʼ */
            pst_mac_device->uc_ap_chan_idx = pst_csi->uc_start_chan_idx;

            /* ���ŵ�ɨ�����б� */
            OAL_MEMZERO(pst_mac_device->st_ap_channel_list, OAL_SIZEOF(pst_mac_device->st_ap_channel_list));

            /* ��'40MHz������λ' */
            pst_mac_device->en_40MHz_intol_bit_recd = OAL_FALSE;

            /* ��ǰ�ŵ���ɨ�赽��BSS�������� */
            pst_mac_device->st_bss_id_list.us_num_networks = 0;
        }
        else
        {
            /* ���浱ǰ�ŵ�ɨ�赽��BSS���� */
            pst_mac_device->st_ap_channel_list[pst_mac_device->uc_ap_chan_idx].us_num_networks =
                            pst_mac_device->st_bss_id_list.us_num_networks;

            /* ���㣬Ϊɨ����һ���ŵ���׼�� */
            pst_mac_device->st_bss_id_list.us_num_networks = 0;

            /* ɨ�����һ���ŵ���ɨ����� */
            if (pst_mac_device->uc_ap_chan_idx == pst_csi->uc_end_chan_idx)
            {
                en_scan_itr_over = OAL_TRUE;
            }

            /* ����ɨ����ɣ�Ҫɨ����ŵ�����+1 */
            pst_mac_device->uc_ap_chan_idx++;

            if (pst_mac_device->uc_ap_chan_idx >= uc_num_supp_chan)
            {
                pst_mac_device->uc_ap_chan_idx = 0;
            }

            if (pst_mac_device->uc_ap_chan_idx == pst_csi->uc_start_chan_idx)
            {
                en_scan_itr_over = OAL_TRUE;
            }

            if (OAL_TRUE == en_scan_itr_over)
            {
                OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                              "{hmac_chan_do_channel_availability_check::Scan over.}");
                break;
            }
        }

        mac_get_channel_num_from_idx(en_band, pst_mac_device->uc_ap_chan_idx, &uc_channel);

        if (OAL_TRUE == hmac_chan_scan_availability(pst_mac_device,
                        &pst_mac_device->st_ap_channel_list[pst_mac_device->uc_ap_chan_idx]))
        {
            /* �л�����ǰ�ŵ� */
            OAM_INFO_LOG0(0, OAM_SF_2040, "hmac_chan_do_channel_availability_check");
            hmac_chan_sync(pst_mac_vap, uc_channel, WLAN_BAND_WIDTH_20M, OAL_TRUE);

            /* �����ŵ�ɨ�賬ʱʱ�� */
            pst_mac_device->st_scan_params.us_scan_time = WLAN_DEFAULT_PASSIVE_SCAN_TIME;

            /* ������ʱ�� */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_scan_timer,
                                   hmac_chan_ch_av_chk_timeout_fn,
                                   pst_mac_device->st_scan_params.us_scan_time,
                                   pst_mac_vap,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_mac_device->ul_core_id);
            return MAC_CHNL_AV_CHK_IN_PROG;
        }

        en_first_time = OAL_FALSE;
    }

    return MAC_CHNL_AV_CHK_COMPLETE;
}
/*****************************************************************************
 �� �� ��  : hmac_chan_get_ext_chan_info
 ��������  : ��ȡָ��VAP������(��չ)�ŵ���Ϣ
 �������  : pst_mac_vap  : MAC VAPָ��
 �������  : pst_chan_info: ������(��չ)�ŵ���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_chan_get_ext_chan_info(
                oal_uint8                            uc_pri20_channel_idx,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth,
                hmac_channel_list_stru              *pst_chan_info)
{
    switch (en_bandwidth)
    {
        case WLAN_BAND_WIDTH_20M:
            pst_chan_info->ul_channels = 1;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            break;

        case WLAN_BAND_WIDTH_40PLUS:
            pst_chan_info->ul_channels = 2;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            break;

        case WLAN_BAND_WIDTH_40MINUS:
            pst_chan_info->ul_channels = 2;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            break;

        case WLAN_BAND_WIDTH_80PLUSPLUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx + 2];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx + 3];
            break;

        case WLAN_BAND_WIDTH_80PLUSMINUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 2];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            break;

        case WLAN_BAND_WIDTH_80MINUSPLUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx + 2];
            break;

        case WLAN_BAND_WIDTH_80MINUSMINUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 3];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx - 2];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            break;

        default:
            pst_chan_info->ul_channels = 0;
            OAM_ERROR_LOG1(0, OAM_SF_DFS, "{hmac_chan_get_ext_chan_info::Invalid bandwidth %d.}", en_bandwidth);
            break;
    }
}

/*****************************************************************************
 �� �� ��  : hmac_chan_restart_network_after_switch
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��7��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_chan_restart_network_after_switch(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint32            ul_ret;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_restart_network_after_switch}");

    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_restart_network_after_switch::pst_event_mem null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK,
                    0,
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_restart_network_after_switch::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);

        return ul_ret;
    }
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
/*lint -e578*//*lint -e19*/
oal_module_symbol(g_ast_freq_map_5g);
oal_module_symbol(g_ast_freq_map_2g);
/*lint +e578*//*lint +e19*/

/*****************************************************************************
 �� �� ��  : hmac_chan_switch_to_new_chan_complete
 ��������  : �����ŵ�/�����л�����¼�
 �������  : frw_event_mem_stru *pst_event_mem
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��8��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_chan_switch_to_new_chan_complete(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru     *pst_event;
    mac_device_stru    *pst_mac_device;
    hmac_vap_stru      *pst_hmac_vap;
    mac_vap_stru       *pst_mac_vap;
    dmac_set_chan_stru *pst_set_chan;
    oal_uint32          ul_ret;
    oal_uint8           uc_idx;

    OAM_INFO_LOG0(0, OAM_SF_2040, "{hmac_chan_restart_network_after_switch}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_switch_to_new_chan_complete::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
	pst_set_chan = (dmac_set_chan_stru *)pst_event->auc_event_data;
    OAM_INFO_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "hmac_chan_switch_to_new_chan_complete\r\n");

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "{hmac_switch_to_new_chan_complete::pst_hmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    OAM_INFO_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "hmac_chan_switch_to_new_chan_complete");
    hmac_dump_chan(pst_mac_vap, (oal_uint8*)pst_set_chan);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "{hmac_switch_to_new_chan_complete::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                pst_set_chan->st_channel.uc_chan_number, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                "{hmac_switch_to_new_chan_complete::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return OAL_FAIL;
    }

    pst_mac_vap->st_channel.uc_chan_number = pst_set_chan->st_channel.uc_chan_number;
    pst_mac_vap->st_channel.en_bandwidth   = pst_set_chan->st_channel.en_bandwidth;
    pst_mac_vap->st_channel.uc_idx         = uc_idx;


    //pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = pst_set_chan->st_ch_switch_info.en_waiting_for_ap;
    pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel = pst_set_chan->st_ch_switch_info.en_waiting_to_shift_channel;

    pst_mac_vap->st_ch_switch_info.en_ch_switch_status = pst_set_chan->st_ch_switch_info.en_ch_switch_status;
    pst_mac_vap->st_ch_switch_info.en_bw_switch_status = pst_set_chan->st_ch_switch_info.en_bw_switch_status;

    /* aput�����ŵ�ͬ�����ŵ��ı�־λ,��ֹ�����û�����,�Ѵ˱�����ͬ����ȥ */
    pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt   = pst_set_chan->st_ch_switch_info.uc_ch_switch_cnt;
    pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn = pst_set_chan->st_ch_switch_info.en_csa_present_in_bcn;


#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* �����ѳɹ��л���40M, ֹͣ40M�ָ���ʱ�� */
    if ((pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M) &&
         (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode))
    {
        hmac_chan_stop_40M_recovery_timer(&pst_hmac_vap->st_vap_base_info);
    }
#endif

    if (OAL_FALSE == pst_set_chan->en_check_cac)
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_DFS
    if (OAL_TRUE == hmac_dfs_need_for_cac(pst_mac_device, pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number))
    {
        hmac_dfs_cac_start(pst_mac_device, pst_hmac_vap);
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                "{hmac_chan_switch_to_new_chan_complete::[DFS]CAC START!}");

        return OAL_SUCC;
    }

    hmac_chan_restart_network_after_switch(&(pst_hmac_vap->st_vap_base_info));
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_dbac_status_notify
 ��������  : ����dbac status event
 �������  : frw_event_mem_stru *pst_event_mem
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��8��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_dbac_status_notify(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru     *pst_event;
    mac_device_stru    *pst_mac_device;
    oal_bool_enum_uint8 *pen_dbac_enable;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_dbac_status_notify::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
	pen_dbac_enable = (oal_bool_enum_uint8 *)pst_event->auc_event_data;
    OAM_INFO_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040,
        "hmac_dbac_status_notify::dbac switch to enable=%d", *pen_dbac_enable);

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040,
            "{hmac_dbac_status_notify::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device->en_dbac_running = *pen_dbac_enable;

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

