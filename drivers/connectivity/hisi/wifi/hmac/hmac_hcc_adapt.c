/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_hcc_adapt.c
  �� �� ��   : ����
  ��    ��   : h00217255
  ��������   : 2014��10��8��
  ����޸�   :
  ��������   : HMACģ��HCC������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��8��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_profiling.h"
#include "hmac_hcc_adapt.h"
#include "mac_resource.h"
#include "oal_hcc_host_if.h"
#include "frw_event_main.h"
#include "hmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_HCC_ADAPT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OAL_STATIC oal_uint8  g_hcc_sched_stat[FRW_EVENT_TYPE_BUTT];
OAL_STATIC oal_uint8  g_hcc_flowctrl_stat[FRW_EVENT_TYPE_BUTT];
OAL_STATIC oal_uint32  g_hcc_sched_event_pkts[FRW_EVENT_TYPE_BUTT]={0};
OAL_STATIC oal_uint8  g_wlan_queue_to_dmac_queue[WLAN_NET_QUEUE_BUTT];

extern oal_uint32 g_ul_pm_wakeup_event;
oal_uint32  g_ul_print_wakeup_mgmt = OAL_FALSE;

extern oal_uint32 hmac_hcc_tx_netbuf(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len,
                                    oal_uint32 fc_type,
                                    oal_uint32 queue_id);
oal_uint32 hmac_hcc_tx_netbuf_auto(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len);
extern oal_uint32 hmac_hcc_tx_data(frw_event_mem_stru * pst_hcc_event_mem, oal_netbuf_stru *pst_netbuf);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
oal_void hmac_tx_net_queue_map_init(oal_void)
{
    oal_memset(g_wlan_queue_to_dmac_queue,DATA_LO_QUEUE,OAL_SIZEOF(g_wlan_queue_to_dmac_queue));
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    g_wlan_queue_to_dmac_queue[WLAN_HI_QUEUE] = DATA_HI_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_NORMAL_QUEUE] = DATA_LO_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_TCP_DATA_QUEUE] = DATA_TCP_DATA_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_TCP_ACK_QUEUE] = DATA_TCP_ACK_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_BK_QUEUE] = DATA_UDP_BK_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_BE_QUEUE] = DATA_UDP_BE_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_VI_QUEUE] = DATA_UDP_VI_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_VO_QUEUE] = DATA_UDP_VO_QUEUE;


    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_HI_QUEUE,WLAN_HI_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_LO_QUEUE,WLAN_NORMAL_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_TCP_DATA_QUEUE,WLAN_TCP_DATA_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_TCP_ACK_QUEUE,WLAN_TCP_ACK_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_BK_QUEUE,WLAN_UDP_BK_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_BE_QUEUE,WLAN_UDP_BE_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_VI_QUEUE,WLAN_UDP_VI_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_VO_QUEUE,WLAN_UDP_VO_QUEUE);
#endif

}

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
oal_int32 hmac_tx_event_pkts_info_print(oal_void* data, char* buf, oal_int32 buf_len)
{
    int i;
    oal_int32 ret = 0;
    oal_uint64 total = 0;
    struct hcc_handler* hcc = hcc_get_default_handler();
    if(NULL == hcc)
        return ret;

    ret +=  snprintf(buf + ret , buf_len - ret,"tx_event_pkts_info_show\n");
    for(i = 0; i < FRW_EVENT_TYPE_BUTT; i++)
    {
        if(g_hcc_sched_event_pkts[i])
            ret +=  snprintf(buf + ret , buf_len - ret,"event:%d, pkts:%10u\n", i,g_hcc_sched_event_pkts[i]);
        total += g_hcc_sched_event_pkts[i];
    }

    if(total)
        ret +=  snprintf(buf + ret , buf_len - ret,"total:%llu\n",total);
    return ret;
}
#endif

#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
OAL_STATIC DECLARE_WIFI_PANIC_STRU(hmac_panic_hcc_adapt,hmac_tx_event_pkts_info_print);
#endif

oal_void hmac_tx_sched_info_init(oal_void)
{
    oal_memset(g_hcc_sched_stat,DATA_LO_QUEUE,OAL_SIZEOF(g_hcc_sched_stat));

    /*set the event sched PRI, TBD*/
    g_hcc_sched_stat[FRW_EVENT_TYPE_HIGH_PRIO] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_CRX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_DRX] = DATA_LO_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_CTX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_SDT_REG] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_CRX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_DRX] = DATA_LO_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_CTX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_TX_COMP] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_TBTT] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_TIMEOUT] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_DMAC_MISC] = DATA_HI_QUEUE;

    oal_memset(g_hcc_flowctrl_stat,HCC_FC_NONE,OAL_SIZEOF(g_hcc_flowctrl_stat));
#if 0
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HIGH_PRIO] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_CRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_DRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_CTX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_SDT_REG] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_CRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_DRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_CTX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_TX_COMP] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_TBTT] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_TIMEOUT] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HMAC_MISC] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_DMAC_MISC] = HCC_FC_NONE;
#endif
    /*����HOST���¼��������Kernel Net����ѡ�����������+�����ķ�ʽ��
    �����Wlan To Wlan �ķ�ʽ��ֱ�Ӷ���!*/
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_DRX] = HCC_FC_DROP|HCC_FC_NET;
    //g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_DRX] = HCC_FC_DROP;

    //g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_DTX] = HCC_FC_NET;
}

OAL_STATIC OAL_INLINE oal_void hmac_hcc_adapt_extend_hdr_init(frw_event_mem_stru *pst_hcc_event_mem,oal_netbuf_stru *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr;
    frw_event_hdr_stru   *pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hdr = (struct frw_hcc_extend_hdr*)OAL_NETBUF_DATA(pst_netbuf);
    pst_hdr->en_nest_type = pst_event_hdr->en_type;
    pst_hdr->uc_nest_sub_type = pst_event_hdr->uc_sub_type;
    pst_hdr->device_id = pst_event_hdr->uc_device_id;
    pst_hdr->chip_id = pst_event_hdr->uc_chip_id;
    pst_hdr->vap_id = pst_event_hdr->uc_vap_id;
}

oal_void get_simple_mac_tx_ctl(mac_tx_ctl_cut_stru  *pst_simple_mac_tx_ctl, mac_tx_ctl_stru  *pst_tx_ctrl)
{
    pst_simple_mac_tx_ctl->uc_alg_pktno = (oal_uint8)pst_tx_ctrl->ul_alg_pktno;
    pst_simple_mac_tx_ctl->bit_en_event_type  = pst_tx_ctrl->en_event_type;
    pst_simple_mac_tx_ctl->bit_frame_header_length = pst_tx_ctrl->uc_frame_header_length;
    pst_simple_mac_tx_ctl->bit_is_needretry = pst_tx_ctrl->bit_is_needretry;
    pst_simple_mac_tx_ctl->bit_is_vipframe  = pst_tx_ctrl->bit_is_vipframe;
    pst_simple_mac_tx_ctl->bit_mpdu_num = pst_tx_ctrl->uc_mpdu_num;
    pst_simple_mac_tx_ctl->bit_netbuf_num = pst_tx_ctrl->uc_netbuf_num;
    pst_simple_mac_tx_ctl->bit_retried_num = pst_tx_ctrl->uc_retried_num;
    pst_simple_mac_tx_ctl->bit_tx_user_idx = (oal_uint8)pst_tx_ctrl->us_tx_user_idx;
    pst_simple_mac_tx_ctl->bit_tx_vap_index = pst_tx_ctrl->uc_tx_vap_index;
    pst_simple_mac_tx_ctl->en_ismcast = pst_tx_ctrl->en_ismcast;
    pst_simple_mac_tx_ctl->en_is_eapol = pst_tx_ctrl->en_is_eapol;
    pst_simple_mac_tx_ctl->en_is_first_msdu = pst_tx_ctrl->uc_is_first_msdu;
    pst_simple_mac_tx_ctl->en_is_get_from_ps_queue = pst_tx_ctrl->en_is_get_from_ps_queue;
    pst_simple_mac_tx_ctl->en_is_probe_data = pst_tx_ctrl->en_is_probe_data;
    /*useless struct member*/
    //pst_simple_mac_tx_ctl->st_timestamp_us = pst_tx_ctrl->st_timestamp_us;
    pst_simple_mac_tx_ctl->us_mpdu_bytes = pst_tx_ctrl->us_mpdu_bytes;
    pst_simple_mac_tx_ctl->bit_mgmt_frame_id = pst_tx_ctrl->bit_mgmt_frame_id;
    pst_simple_mac_tx_ctl->bit_is_eapol_key_ptk = pst_tx_ctrl->bit_is_eapol_key_ptk;
    pst_simple_mac_tx_ctl->bit_need_rsp      = pst_tx_ctrl->bit_need_rsp;
    pst_simple_mac_tx_ctl->bit_ac            = pst_tx_ctrl->uc_ac;
    pst_simple_mac_tx_ctl->en_is_amsdu       = pst_tx_ctrl->en_is_amsdu;
    pst_simple_mac_tx_ctl->en_ack_policy     = pst_tx_ctrl->en_ack_policy;
    pst_simple_mac_tx_ctl->bit_tid           = (pst_tx_ctrl->uc_tid & 0x0F);
    /* mayuan TBD ���STA user idx����0�����⣬�˴���bit_reserved4��Ϊuser idx�ı��� */
    pst_simple_mac_tx_ctl->bit_tx_user_idx_bak = (oal_uint8)pst_tx_ctrl->us_tx_user_idx;
}

/*****************************************************************************
 �� �� ��  : get_mac_rx_ctl
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void get_mac_rx_ctl(mac_rx_ctl_stru  *pst_mac_rx_ctl, mac_rx_ctl_cut_stru  *pst_mac_rx_cut_ctl)
{
    pst_mac_rx_ctl->bit_amsdu_enable    = pst_mac_rx_cut_ctl->bit_amsdu_enable;
    pst_mac_rx_ctl->bit_buff_nums       = pst_mac_rx_cut_ctl->bit_buff_nums;
    pst_mac_rx_ctl->us_da_user_idx      = pst_mac_rx_cut_ctl->bit_da_user_idx;
    pst_mac_rx_ctl->bit_is_first_buffer = pst_mac_rx_cut_ctl->bit_is_first_buffer;
    pst_mac_rx_ctl->bit_is_fragmented   = pst_mac_rx_cut_ctl->bit_is_fragmented;
    pst_mac_rx_ctl->uc_mac_header_len   = pst_mac_rx_cut_ctl->bit_mac_header_len;
    pst_mac_rx_ctl->us_ta_user_idx      = pst_mac_rx_cut_ctl->bit_ta_user_idx;
    pst_mac_rx_ctl->bit_vap_id          = pst_mac_rx_cut_ctl->bit_vap_id;
    pst_mac_rx_ctl->uc_msdu_in_buffer   = pst_mac_rx_cut_ctl->uc_msdu_in_buffer;
    pst_mac_rx_ctl->us_frame_len        = pst_mac_rx_cut_ctl->us_frame_len;
    pst_mac_rx_ctl->uc_mac_vap_id       = pst_mac_rx_cut_ctl->uc_mac_vap_id;
    pst_mac_rx_ctl->uc_channel_number   = pst_mac_rx_cut_ctl->uc_channel_number;
    pst_mac_rx_ctl->bit_is_beacon       = pst_mac_rx_cut_ctl->bit_is_beacon;
}

/*****************************************************************************
 �� �� ��  : check_headroom_add_length
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��12��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 check_headroom_add_length(mac_tx_ctl_stru *pst_tx_ctrl, frw_event_type_enum_uint8  en_nest_type, oal_uint8  uc_nest_sub_type)
{
    oal_uint32 ul_headroom_add;

    if (1 == pst_tx_ctrl->bit_80211_mac_head_type)
    {
        /*case 1: data from net, mac head is maintence in netbuff*/
         /*lint -e778*/
        ul_headroom_add = OAL_SIZEOF(mac_tx_ctl_cut_stru) - (MAC_80211_QOS_HTC_4ADDR_FRAME_LEN - MAX_MAC_HEAD_LEN);//�ṹ��϶�����4
         /*lint +e778*/
    }
    else if ((FRW_EVENT_TYPE_WLAN_CTX == en_nest_type) &&
            ((DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT == uc_nest_sub_type) || (DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION == uc_nest_sub_type)))
    {
        /*case 2: mgmt frame, mac header is maintence in payload part*/
        ul_headroom_add = OAL_SIZEOF(mac_tx_ctl_cut_stru)+(MAX_MAC_HEAD_LEN - MAC_80211_FRAME_LEN);
    }
    else
    {
        /*case 3: data from net, mac head not maintence in netbuff*/
        /*case 4: netbuff alloced in adapt layer */
        ul_headroom_add = MAX_MAC_HEAD_LEN + OAL_SIZEOF(mac_tx_ctl_cut_stru);
    }

    return ul_headroom_add;
}

/*****************************************************************************
 �� �� ��  : hmac_adjust_netbuf_data
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��12��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_adjust_netbuf_data(oal_netbuf_stru *pst_netbuf, mac_tx_ctl_stru *pst_tx_ctrl, frw_event_type_enum_uint8  en_nest_type, oal_uint8  uc_nest_sub_type)
{
    oal_uint8                       *puc_data_hdr;
    mac_tx_ctl_cut_stru             st_simple_mac_tx_ctl;

    /*�ڽ���HCC֮ǰ����CB�ֶκ�Macͷ���������payload֮ǰ*/
    puc_data_hdr      = OAL_NETBUF_DATA(pst_netbuf);

    oal_memset(&st_simple_mac_tx_ctl,0,OAL_SIZEOF(mac_tx_ctl_cut_stru));
    get_simple_mac_tx_ctl(&st_simple_mac_tx_ctl, pst_tx_ctrl);

    if ((FRW_EVENT_TYPE_WLAN_CTX == en_nest_type) &&
       ((DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT == uc_nest_sub_type) || (DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION == uc_nest_sub_type)))
    {

        /*case 1: mgmt frame, mac header is maintence in payload part*/
        oal_memcopy(puc_data_hdr, (oal_uint8 *)&st_simple_mac_tx_ctl, OAL_SIZEOF(mac_tx_ctl_cut_stru));
        /*copy mac hdr*/
        oal_memmove(puc_data_hdr + OAL_SIZEOF(mac_tx_ctl_cut_stru),
                    puc_data_hdr + OAL_SIZEOF(mac_tx_ctl_cut_stru)+(MAX_MAC_HEAD_LEN - MAC_80211_FRAME_LEN),
                    MAC_80211_FRAME_LEN);
    }
    else if (OAL_PTR_NULL != pst_tx_ctrl->pst_frame_header)
    {
        /*case 2: data from net, mac head not maintence in netbuff*/
        /*case 3: netbuff alloced in adapt layer */
        oal_memmove(puc_data_hdr + OAL_SIZEOF(mac_tx_ctl_cut_stru), (oal_uint8 *)pst_tx_ctrl->pst_frame_header, MAX_MAC_HEAD_LEN);
        oal_memcopy(puc_data_hdr, (oal_uint8 *)&st_simple_mac_tx_ctl, OAL_SIZEOF(mac_tx_ctl_cut_stru));

        /* ֡ͷ��֡�岻������֡ͷ�����������¼��ڴ棬�˴���Ҫ�ͷ� */
        if (0 == pst_tx_ctrl->bit_80211_mac_head_type)
        {
            OAL_MEM_FREE((oal_uint8 *)pst_tx_ctrl->pst_frame_header, OAL_TRUE);
        }
    }
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_netbuf_auto
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��6��18��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_hcc_tx_netbuf_auto(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len)
{
    oal_uint32      fc_type,queue_id;
    frw_event_hdr_stru              *pst_event_hdr;
    frw_event_type_enum_uint8        en_type;
    pst_event_hdr           = frw_get_event_hdr(pst_hcc_event_mem);
    en_type                 = pst_event_hdr->en_type;

    if(OAL_WARN_ON(en_type >= FRW_EVENT_TYPE_BUTT))
    {
        oal_netbuf_free(pst_netbuf);
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_hcc_tx_netbuf_auto::FRW_EVENT_TYPE[%d] over limit!}",en_type);
        return OAL_FAIL;
    }

    queue_id = g_hcc_sched_stat[en_type];
    fc_type = g_hcc_flowctrl_stat[en_type];

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    /* ���ڴ���̫�����Ļ�ȡ����к� */
    if (FRW_EVENT_TYPE_HOST_DRX == en_type)
    {
        queue_id = oal_skb_get_queue_mapping(pst_netbuf);
        if(OAL_WARN_ON(queue_id >= WLAN_NET_QUEUE_BUTT))
        {
            queue_id = DATA_LO_QUEUE;
        }
        else
        {
            queue_id = g_wlan_queue_to_dmac_queue[queue_id];
        }
    }
#endif
    return hmac_hcc_tx_netbuf(pst_hcc_event_mem,pst_netbuf,ul_hdr_len,fc_type,queue_id);
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_netbuf
 ��������  : ������ͨnetbuf,��netbuf->data��ʼ�ĳ���Ϊul_hdr_len�Ŀռ����TCM
             �����˼�ͨ�Ž�����ô˺���
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015/4/10
    ��    ��   : Z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_hcc_tx_netbuf(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len,
                                    oal_uint32 fc_type,
                                    oal_uint32 queue_id)
{
#ifdef CONFIG_PRINTK
    frw_event_hdr_stru *pst_event_hdr = OAL_PTR_NULL;
#endif
    oal_int32                       ul_headroom_add = 0;
    oal_uint32                       ret = OAL_SUCC;

    DECLARE_HCC_TX_PARAM_INITIALIZER(st_hcc_transfer_param,
                                     HCC_ACTION_TYPE_WIFI,
                                     0,
                                     ul_hdr_len + OAL_SIZEOF(struct frw_hcc_extend_hdr),
                                     fc_type,
                                     queue_id);

    OAL_BUG_ON(NULL == pst_netbuf);

    if(OAL_UNLIKELY(oal_netbuf_headroom(pst_netbuf) < OAL_SIZEOF(struct frw_hcc_extend_hdr)))
    {
        ul_headroom_add =  (oal_int32)OAL_SIZEOF(struct frw_hcc_extend_hdr) - (oal_int32)oal_netbuf_headroom(pst_netbuf);
    }

    if(ul_headroom_add > 0)
    {
        oal_int32 ul_head_room = (oal_int32)oal_netbuf_headroom(pst_netbuf);
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_hcc_tx_netbuf expand head done![%d]}",ul_head_room);
        ret = (oal_uint32)oal_netbuf_expand_head(pst_netbuf, (oal_int32) ul_headroom_add, 0, GFP_ATOMIC);
        if(OAL_WARN_ON(OAL_SUCC != ret))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_tx_data:: alloc head room failed.}");
            oal_netbuf_free(pst_netbuf);
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    }

    /*add frw hcc extend area*/
    oal_netbuf_push(pst_netbuf, OAL_SIZEOF(struct frw_hcc_extend_hdr));
    hmac_hcc_adapt_extend_hdr_init(pst_hcc_event_mem,pst_netbuf);

    //expand 14B�������½�40%,��ȷ��!
    //oal_netbuf_expand_head(pst_netbuf, 4, 0, GFP_ATOMIC);
#ifdef CONFIG_PRINTK
    pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);

    ret = (oal_uint32)hcc_tx(hcc_get_default_handler(), pst_netbuf, &st_hcc_transfer_param);
    if(OAL_UNLIKELY(OAL_SUCC != ret))
    {
        /*hcc �ر�ʱ�·�������,������Ҫ����*/
        if(OAL_WARN_ON(-OAL_EBUSY == ret))
        {
            OAL_IO_PRINT("[E]hmac_tx event[%u:%u] drop!\n", pst_event_hdr->en_type, pst_event_hdr->uc_sub_type);
            ret = OAL_SUCC;
            DECLARE_DFT_TRACE_KEY_INFO("hcc_is_busy",OAL_DFT_TRACE_OTHER);
        }

        if(-OAL_EIO == ret)
        {
            /*hcc exception, drop the pkts*/
            ret = OAL_SUCC;
        }

        oal_netbuf_free(pst_netbuf);
    }
    else
    {
        //frw_event_hdr_stru              *pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);
        if(OAL_LIKELY(pst_event_hdr->en_type < FRW_EVENT_TYPE_BUTT))
            g_hcc_sched_event_pkts[pst_event_hdr->en_type]++;
    }
    OAL_MIPS_TX_STATISTIC(HOST_PROFILING_FUNC_HCC_TX);

    return ret;
#else
    /*UT Failed! Should remove this macro when DMT!*/
    return ret;
#endif
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_data
 ��������  : hmac tx data adapt function,�����������������ݰ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015/4/9
    ��    ��   : Z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_hcc_tx_data(frw_event_mem_stru * pst_hcc_event_mem, oal_netbuf_stru *pst_netbuf)
{
    frw_event_hdr_stru              *pst_event_hdr;

    frw_event_type_enum_uint8        en_type;
    oal_uint8                        uc_sub_type;

    mac_tx_ctl_stru                *pst_tx_ctrl;
    oal_uint32                      ul_headroom_add;

    oal_int32                       ret = OAL_SUCC;

    oal_uint                        ul_netbuf_old_addr;
    oal_uint                        ul_netbuf_new_addr;
    oal_uint                        ul_addr_offset;
    oal_uint8                       auc_macheader[MAC_80211_QOS_HTC_4ADDR_FRAME_LEN] = {0};

    /*��ȡǶ�׵�ҵ���¼�����*/
    pst_event_hdr           = frw_get_event_hdr(pst_hcc_event_mem);

    en_type                 = pst_event_hdr->en_type;
    uc_sub_type             = pst_event_hdr->uc_sub_type;

    OAL_BUG_ON(NULL == pst_netbuf);

    pst_tx_ctrl  = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
    if (OAL_WARN_ON(pst_tx_ctrl->en_use_4_addr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_tx_data:: use 4 address.}");
        oal_netbuf_free(pst_netbuf);
        return OAL_FAIL;
    }

    ul_headroom_add = check_headroom_add_length(pst_tx_ctrl, en_type, uc_sub_type);

    if(ul_headroom_add > oal_netbuf_headroom(pst_netbuf))
    {
        if (1 == pst_tx_ctrl->bit_80211_mac_head_type)
        {
            oal_memcopy(auc_macheader, (oal_uint8 *)pst_tx_ctrl->pst_frame_header, MAX_MAC_HEAD_LEN);
        }

        ret = oal_netbuf_expand_head(pst_netbuf,
                                    (oal_int32)ul_headroom_add - (oal_int32)oal_netbuf_headroom(pst_netbuf),
                                    0, GFP_ATOMIC);
        if(OAL_WARN_ON(OAL_SUCC != ret))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_tx_data:: alloc head room failed.}");
            oal_netbuf_free(pst_netbuf);
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        if (1 == pst_tx_ctrl->bit_80211_mac_head_type)
        {
            oal_memcopy(OAL_NETBUF_DATA(pst_netbuf), auc_macheader, MAX_MAC_HEAD_LEN);
            pst_tx_ctrl->pst_frame_header = (mac_ieee80211_frame_stru *)OAL_NETBUF_DATA(pst_netbuf);
        }
    }

    /*�޸�netbuff��dataָ���len*/
    oal_netbuf_push(pst_netbuf, ul_headroom_add);
    hmac_adjust_netbuf_data(pst_netbuf, pst_tx_ctrl,en_type, uc_sub_type);

    /* ʹnetbuf���ֽڶ��� */
    ul_netbuf_old_addr = (oal_uint)(OAL_NETBUF_DATA(pst_netbuf) + OAL_SIZEOF(mac_tx_ctl_cut_stru) + MAX_MAC_HEAD_LEN);
    ul_netbuf_new_addr = OAL_ROUND_DOWN(ul_netbuf_old_addr, 4);
    ul_addr_offset = ul_netbuf_old_addr - ul_netbuf_new_addr;

    /* δ����ʱ��host�������ݰ��ƣ��˴�����host�����device */
    if (ul_addr_offset)
    {
        if(ul_addr_offset < oal_netbuf_headroom(pst_netbuf))
        {
            oal_memmove((oal_uint8*)OAL_NETBUF_DATA(pst_netbuf) - ul_addr_offset, (oal_uint8*)OAL_NETBUF_DATA(pst_netbuf), OAL_NETBUF_LEN(pst_netbuf));
            oal_netbuf_push(pst_netbuf, ul_addr_offset);
            oal_netbuf_trim(pst_netbuf, ul_addr_offset);
        }
    }

    OAL_MIPS_TX_STATISTIC(HOST_PROFILING_FUNC_HCC_TX_DATA);
    /*netbuf���ܳɹ�����ɷ��ͺ����ͷ�!*/
    hmac_hcc_tx_netbuf_auto(pst_hcc_event_mem,pst_netbuf,
                        OAL_SIZEOF(mac_tx_ctl_cut_stru) + MAX_MAC_HEAD_LEN);
    return OAL_SUCC;
}

oal_uint32 hmac_hcc_tx_netbuf_adapt(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf)
{
    return hmac_hcc_tx_netbuf_auto(pst_hcc_event_mem,pst_netbuf,0);
}

oal_uint32 hmac_hcc_tx_event_buf_to_netbuf(frw_event_mem_stru   *pst_event_mem,
                                                         oal_uint8 *           pst_buf,
                                                         oal_uint32            payload_size)
{
    oal_netbuf_stru                 *pst_netbuf;
    /*����netbuf����¼�payload*/
    pst_netbuf = hcc_netbuf_alloc(payload_size);
    if (OAL_WARN_ON(NULL == pst_netbuf))
    {
       OAL_IO_PRINT("hmac_hcc_tx_event_buf_to_netbuf alloc netbuf failed!\n");
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /*���ṹ�忽����netbuff������*/
    //OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
    oal_netbuf_put(pst_netbuf, payload_size);
    oal_memcopy((oal_uint8 *)(OAL_NETBUF_DATA(pst_netbuf)), (oal_uint8 *)pst_buf, payload_size);

    return hmac_hcc_tx_netbuf_adapt(pst_event_mem,pst_netbuf);
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_event_payload_to_netbuf
 ��������  :

 �������  : frw_event_mem_stru *pst_event_mem�������¼�
             oal_uint32          payload_size   ��Ч����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� eventת����netbuf���͵��Զ˳ɹ���ʧ�ܻ��ڷ��ͺ������ͷš�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015/4/9
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_hcc_tx_event_payload_to_netbuf(frw_event_mem_stru   *pst_event_mem,
                                                         oal_uint32            payload_size)
{
    oal_uint8          *pst_event_payload;

    if(OAL_WARN_ON(NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_hcc_tx_event_payload_to_netbuf:pst_event_mem null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*ȡҵ���¼���Ϣ*/
    pst_event_payload    = frw_get_event_payload(pst_event_mem);
    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem,pst_event_payload,payload_size);
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_rx_event_comm_adapt
 ��������  : Hmac rx ҵ���¼����亯������Ҫ����wlan��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_hcc_rx_event_comm_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    oal_uint8                       bit_mac_header_len;
    frw_event_hdr_stru              *pst_event_hdr;
    hcc_event_stru                  *pst_hcc_event_payload;

    mac_rx_ctl_stru                 *pst_rx_ctrl;
    oal_uint8                       *puc_hcc_extend_hdr;

    /*step1 ��ȡǶ�׵�ҵ���¼�����*/
    pst_event_hdr           = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru*)frw_get_event_payload(pst_hcc_event_mem);


    /*��ɴ�51Mac rx ctl ��02 Mac rx ctl�Ŀ���,
    �����˴�,pad_payload�Ѿ���0*/

    /* hcc protocol header
    |-------hcc total(64B)-----|-----------package mem--------------|
    |hcc hdr|pad hdr|hcc extend|pad_payload|--------payload---------|*/

    if(OAL_WARN_ON(NULL == pst_hcc_event_payload->pst_netbuf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_hcc_rx_event_comm_adapt:did't found netbuf!");
        return OAL_FAIL;
    }

    puc_hcc_extend_hdr  = OAL_NETBUF_DATA((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf);
    bit_mac_header_len = ((mac_rx_ctl_cut_stru *)puc_hcc_extend_hdr)->bit_mac_header_len;
    if (bit_mac_header_len)
    {
        if(bit_mac_header_len > MAX_MAC_HEAD_LEN)
        {
            OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "invaild mac header len:%d,main:%d,sub:%d",
                            bit_mac_header_len,pst_event_hdr->en_type, pst_event_hdr->uc_sub_type);
            oal_print_hex_dump(puc_hcc_extend_hdr, (oal_int32)OAL_NETBUF_LEN((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf), 32, "invaild mac header len");
            return OAL_FAIL;
        }

        pst_rx_ctrl  = (mac_rx_ctl_stru *)OAL_NETBUF_CB((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf);
        get_mac_rx_ctl(pst_rx_ctrl, (mac_rx_ctl_cut_stru *)puc_hcc_extend_hdr) ;

        /*��Ҫ�޸�pst_rx_ctrl������ָ��*/
        pst_rx_ctrl->pul_mac_hdr_start_addr = (oal_uint32 *)(puc_hcc_extend_hdr + OAL_MAX_CB_LEN + MAX_MAC_HEAD_LEN - pst_rx_ctrl->uc_mac_header_len);

        /* ��mac header��������ߵ�ַƫ��8���ֽڿ�����ʹ��mac header��payload���������� */
        oal_memmove((oal_uint8 *)pst_rx_ctrl->pul_mac_hdr_start_addr,
                    (oal_uint8 *)((oal_uint8 *)pst_rx_ctrl->pul_mac_hdr_start_addr - (MAX_MAC_HEAD_LEN - pst_rx_ctrl->uc_mac_header_len)),
                    pst_rx_ctrl->uc_mac_header_len);

        /*��netbuff dataָ���Ƶ�payloadλ��*/
        oal_netbuf_pull(pst_hcc_event_payload->pst_netbuf, OAL_MAX_CB_LEN + (MAX_MAC_HEAD_LEN - pst_rx_ctrl->uc_mac_header_len));

        //OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_rx_event_handler::cut short}");
    }
    else
    {
        oal_netbuf_pull(pst_hcc_event_payload->pst_netbuf, (OAL_MAX_CB_LEN + MAX_MAC_HEAD_LEN));

        //OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_rx_event_handler::cut short}");
    }


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_expand_rx_adpat_event
 ��������  : hmac event ��չ����������һ��rx event�¼�,�¼�����ʧ�����ͷ�ԭ�¼��е�netbuf!
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_expand_rx_adpat_event(frw_event_mem_stru *pst_hcc_event_mem, oal_uint32 event_size)
{
    frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    frw_event_type_enum_uint8       en_type;
    oal_uint8                       uc_sub_type;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_vap_id;
    frw_event_mem_stru             *pst_event_mem;              /* ҵ���¼������Ϣ */

   /* ��ȡHCC�¼���Ϣ */
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    en_type                 = pst_hcc_event_hdr->en_type;
    uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /* ����ҵ���¼� */
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)event_size);
    if (OAL_WARN_ON(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_WARNING_LOG1(0,OAM_SF_ANY,"hmac_hcc_rx_netbuf_convert_to_event  alloc event failed,event len:%d",event_size);
        /* �ͷ�hcc�¼��������netbuf�ڴ� */
        oal_netbuf_free(pst_hcc_netbuf);
        return OAL_PTR_NULL;
    }

    /* ��ҵ���¼�ͷ*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       (oal_uint16)event_size,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_rx_netbuf_convert_to_event
 ��������  : Dmacģ�齫netbuf�е��¼����ݻ�ԭ���¼��ڴ���
 �������  : frw_event_mem_stru *pst_hcc_event_mem
             oal_uint32 revert_size
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_rx_netbuf_convert_to_event(frw_event_mem_stru *pst_hcc_event_mem, oal_uint32 revert_size)
{
    //frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    //frw_event_type_enum_uint8       en_type;
    //oal_uint8                       uc_sub_type;
    frw_event_mem_stru             *pst_event_mem;              /* ҵ���¼������Ϣ */

    if(OAL_WARN_ON(NULL == pst_hcc_event_mem))
    {
        return NULL;
    }

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    //pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    //en_type                 = pst_hcc_event_hdr->en_type;
    //uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;

    if(OAL_WARN_ON(NULL == pst_hcc_netbuf))
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"Fatal Error,payload did't contain any netbuf!");
        return OAL_PTR_NULL;
    }

    if(revert_size > OAL_NETBUF_LEN(pst_hcc_netbuf))
    {
        revert_size = OAL_NETBUF_LEN(pst_hcc_netbuf);
    }

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,revert_size);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_PTR_NULL;
    }

    if(revert_size)
        oal_memcopy((oal_uint8 *)frw_get_event_payload(pst_event_mem),
                (oal_uint8 *)OAL_NETBUF_DATA(pst_hcc_netbuf), revert_size);

    /* �ͷ�hcc�¼��������netbuf�ڴ� */
    oal_netbuf_free(pst_hcc_netbuf);

    return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_rx_convert_netbuf_to_event_default
 ��������  : Dmacģ�齫netbuf�е��¼����ݻ�ԭ���¼��ڴ���,
             netbuf ������� event����һ��!
 �������  : frw_event_mem_stru *pst_hcc_event_mem

 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_rx_convert_netbuf_to_event_default(frw_event_mem_stru *pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    if(OAL_WARN_ON(OAL_PTR_NULL == pst_hcc_event_mem))
    {
        return OAL_PTR_NULL;
    }

    pst_hcc_event_payload = (hcc_event_stru*)frw_get_event_payload(pst_hcc_event_mem);
    return hmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,pst_hcc_event_payload->ul_buf_len);
}

/*****************************************************************************
 �� �� ��  : hmac_common_rx_adapt
 ��������  : hmac����и��payload�¼��Ĺ�����������ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_test_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    hcc_event_stru                  *pst_hcc_rx_event;

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(hcc_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    /*��ҵ���¼���Ϣ*/
    pst_hcc_rx_event                 = (hcc_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_hcc_rx_event->pst_netbuf     = pst_hcc_event_payload->pst_netbuf;
    pst_hcc_rx_event->ul_buf_len     = (oal_uint32)OAL_NETBUF_LEN((oal_netbuf_stru*)pst_hcc_event_payload->pst_netbuf);

    return pst_event_mem;
}

frw_event_mem_stru * hmac_rx_convert_netbuf_to_netbuf_default(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;

    dmac_tx_event_stru              *pst_ctx_event;

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_tx_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    pst_ctx_event               = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);

    pst_ctx_event->pst_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_ctx_event->us_frame_len = (oal_uint16)OAL_NETBUF_LEN((oal_netbuf_stru*)pst_hcc_event_payload->pst_netbuf);

    OAM_INFO_LOG2(0, OAM_SF_ANY, "{hmac_rx_convert_netbuf_to_netbuf_default::netbuf = %p, frame len = %d.}",
                  pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len);

    return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : hmac_rx_process_data_sta_rx_adapt
 ��������  : rx_process_data_sta��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * hmac_rx_process_data_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    dmac_wlan_drx_event_stru        *pst_wlan_rx_event;

    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_DATA_ADAPT);

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_wlan_drx_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    /*��ҵ���¼���Ϣ*/
    pst_wlan_rx_event                 = (dmac_wlan_drx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_wlan_rx_event->pst_netbuf     = pst_hcc_event_payload->pst_netbuf;
    pst_wlan_rx_event->us_netbuf_num  = 1;//Ŀǰ��֧��ͨ��SDIO��������Ĭ�϶��ǵ�֡

    return pst_event_mem;
}

frw_event_mem_stru *  hmac_rx_process_mgmt_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    dmac_wlan_crx_event_stru        *pst_crx_event;

    /*ȡHCC�¼���Ϣ*/
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_wlan_crx_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    /*��ҵ���¼���Ϣ*/
    pst_crx_event                     = (dmac_wlan_crx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_crx_event->pst_netbuf         = pst_hcc_event_payload->pst_netbuf;

    return pst_event_mem;

}

#ifdef _PRE_WLAN_FEATRUE_FLOWCTL

/*****************************************************************************
 �� �� ��  : hmac_alg_flowctl_backp_rx_adapt
 ��������  : hmac��ѹ�������亯��
 �������  : frw_event_mem_stru *
 �������  : ��
 �� �� ֵ  : frw_event_mem_stru*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru* hmac_alg_flowctl_backp_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    frw_event_stru                  *pst_hcc_event;
    hcc_event_stru                  *pst_hcc_event_payload;
    frw_event_hdr_stru              *pst_hcc_event_hdr;

    oal_uint8                        uc_chip_id;
    oal_uint8                        uc_device_id;
    oal_uint8                        uc_vap_id;

    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event;

    if (OAL_PTR_NULL == pst_hcc_event_mem)
    {
        return OAL_PTR_NULL;
    }

    /*step1 ȡHCC�¼�ͷ*/
    pst_hcc_event           = (frw_event_stru *)pst_hcc_event_mem->puc_data;
    pst_hcc_event_hdr       = &(pst_hcc_event->st_event_hdr);
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /*step2 ȡHCC�¼���Ϣ*/
    pst_hcc_event_payload   = (hcc_event_stru *)pst_hcc_event->auc_event_data;


    /*step3 ����ҵ���¼�*/
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)pst_hcc_event_payload->ul_buf_len);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        oal_netbuf_free(pst_hcc_event_payload->pst_netbuf);
        return OAL_PTR_NULL;
    }

    pst_event =  (frw_event_stru *)pst_event_mem->puc_data;

    /*step4 ��ҵ���¼�ͷ*/
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                   pst_hcc_event_payload->en_nest_type,
                   pst_hcc_event_payload->uc_nest_sub_type,
                   (oal_uint16)pst_hcc_event_payload->ul_buf_len,
                   FRW_EVENT_PIPELINE_STAGE_1,
                   uc_chip_id,
                   uc_device_id,
                   uc_vap_id);

    /*step5 ��HCC�¼���Ϣ*/
    oal_memcopy(pst_event->auc_event_data, (oal_uint8 *)(OAL_NETBUF_DATA((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf)), pst_hcc_event_payload->ul_buf_len);

    oal_netbuf_free(pst_hcc_event_payload->pst_netbuf);

    return pst_event_mem;
}


#endif

/*****************************************************************************
 �� �� ��  : hmac_rx_process_data_sta_rx_adapt
 ��������  : rx_process_data_sta��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * hmac_cali2hmac_misc_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    hal_cali_hal2hmac_event_stru    *pst_cali_save_event;

    //OAL_IO_PRINT("hmac_cali2hmac_misc_event_rx_adapt start\r\n");

    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_DATA_ADAPT);

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(hal_cali_hal2hmac_event_stru));
    if (NULL == pst_event_mem)
    {
        OAL_IO_PRINT("cali_hmac_rx_adapt_fail\r\n");
        return NULL;
    }

    /*��ҵ���¼���Ϣ*/
    pst_cali_save_event                 = (hal_cali_hal2hmac_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_cali_save_event->pst_netbuf     = pst_hcc_event_payload->pst_netbuf;
    pst_cali_save_event->us_netbuf_num  = 1;//Ŀǰ��֧��ͨ��SDIO��������Ĭ�϶��ǵ�֡

    return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : hmac_proc_add_user_tx_adapt
 ��������  : add_userģ�鷢������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_proc_add_user_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_add_user_stru));
}


/*****************************************************************************
 �� �� ��  : hmac_proc_del_user_tx_adapt
 ��������  : del_userģ�鷢������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint32 hmac_proc_del_user_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_del_user_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_proc_config_syn_tx_adapt
 ��������  : config_synģ�鷢������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015/4/9
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e413*/
oal_uint32 hmac_proc_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    hmac_to_dmac_cfg_msg_stru       *pst_syn_cfg_payload;
    pst_syn_cfg_payload    = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem,
                                              (pst_syn_cfg_payload->us_len + (oal_uint32)OAL_OFFSET_OF(hmac_to_dmac_cfg_msg_stru,auc_msg_body)));
}
/*lint +e413*/


/*****************************************************************************
 �� �� ��  : hmac_proc_config_syn_alg_tx_adapt
 ��������  : config_alg_synģ�鷢������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e413*/
oal_uint32 hmac_proc_config_syn_alg_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    hmac_to_dmac_cfg_msg_stru       *pst_syn_cfg_payload;
    pst_syn_cfg_payload    = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem,
                                              (pst_syn_cfg_payload->us_len + (oal_uint32)OAL_OFFSET_OF(hmac_to_dmac_cfg_msg_stru,auc_msg_body)));
}
/*lint +e413*/

/*****************************************************************************
 �� �� ��  : hmac_proc_tx_host_tx_adapt
 ��������  : tx_host_event��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/

oal_uint32 hmac_proc_tx_host_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    oal_netbuf_stru                 *pst_current_netbuf;
    oal_netbuf_stru                 *pst_current_netbuf_tmp = NULL;
    dmac_tx_event_stru              *pst_dmac_tx_event_payload;

    /*ȡҵ���¼���Ϣ*/
    pst_dmac_tx_event_payload = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_current_netbuf        = pst_dmac_tx_event_payload->pst_netbuf;

    while(OAL_PTR_NULL != pst_current_netbuf)
    {
        /*������netbuf�׳�֮ǰָ����һ��netbuf����ֹfrw_event_dispatch_event ������ netbuf->next */
        pst_current_netbuf_tmp = pst_current_netbuf;
        pst_current_netbuf = OAL_NETBUF_NEXT(pst_current_netbuf);

        /*netbuf ʧ���ɱ��������ͷ�!*/
        OAL_MIPS_TX_STATISTIC(HOST_PROFILING_FUNC_HCC_TX_ADAPT);
        hmac_hcc_tx_data(pst_event_mem, pst_current_netbuf_tmp);

    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_proc_mgmt_ctx_tx_adapt
 ��������  : mgmt_ctx��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint32 hmac_proc_mgmt_ctx_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_proc_tx_host_tx_adapt(pst_event_mem);
}

/*****************************************************************************
 �� �� ��  : hmac_proc_tx_process_action_event_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��3��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_proc_tx_process_action_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_proc_tx_host_tx_adapt(pst_event_mem);
}

/*****************************************************************************
 �� �� ��  : hmac_proc_set_edca_param_tx_adapt
 ��������  : set_edca_param��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��29��
    ��    ��   : s00304087
    �޸�����   : �޸�edca���䴫����������
*****************************************************************************/
oal_uint32 hmac_proc_set_edca_param_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_scan_proc_scan_req_event_tx_adapt
 ��������  : ͨ��SDIO�·�ɨ������ǰ�����亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_scan_proc_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    mac_scan_req_stru          *pst_h2d_scan_req_params;        /* �·���ɨ����� */

	if(OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
	{
	    return OAL_ERR_CODE_PTR_NULL;
	}

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_scan_proc_scan_req_event_tx_adapt:: scan req, enter into tx adapt.}");
    pst_h2d_scan_req_params = (mac_scan_req_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8*)pst_h2d_scan_req_params, OAL_SIZEOF(mac_scan_req_stru));
}
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
oal_uint32   hmac_dpd_data_processed_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    dmac_tx_event_stru          *pst_dmac_tx_event;

    if(OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: dpd data, enter into tx adapt.}");
    pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8*)OAL_NETBUF_DATA(pst_dmac_tx_event->pst_netbuf), pst_dmac_tx_event->us_frame_len);
}

#endif

oal_uint32   hmac_send_cali_data_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    dmac_tx_event_stru          *pst_dmac_tx_event;

    if(OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    //OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: dpd data, enter into tx adapt.}");
    pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
    //OAL_IO_PRINT("hmac_send_cali_data_tx_adapt : pst_dmac_tx_event->us_frame_len %d\r\n", pst_dmac_tx_event->us_frame_len);
    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8*)OAL_NETBUF_DATA(pst_dmac_tx_event->pst_netbuf), pst_dmac_tx_event->us_frame_len);
}

/*****************************************************************************
 �� �� ��  : hmac_scan_proc_sched_scan_req_event_tx_adapt
 ��������  : ͨ��SDIO�·�PNO����ɨ������ǰ�����亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_scan_proc_sched_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    mac_pno_scan_stru   *pst_h2d_pno_scan_req_params;     /* �·�PNO����ɨ������ */

	if(OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
	{
	    return OAL_ERR_CODE_PTR_NULL;
	}

    pst_h2d_pno_scan_req_params = (mac_pno_scan_stru *)(*(oal_uint *)frw_get_event_payload(pst_event_mem));

    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8 *)pst_h2d_pno_scan_req_params, OAL_SIZEOF(mac_pno_scan_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_update_user_qos_table_tx_adapt
 ��������  : ͨ��SDIO�·����¹���user����ǰ�����亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_mgmt_update_user_qos_table_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_join_set_reg_event_tx_adapt
 ��������  : ͨ��SDIO�·�join����ǰ�����亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_proc_join_set_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_proc_join_set_reg_event_tx_adapt::tx adapt.}");
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru));
}


/*****************************************************************************
 �� �� ��  : hmac_join_set_dtim_reg_event_tx_adapt
 ��������  : ͨ��SDIO�·�����dtim�Ĵ���ǰ�ķ������亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_proc_join_set_dtim_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_proc_join_set_dtim_reg_event_tx_adapt::tx adapt.}");
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_convert_event_to_netbuf_uint32
 ��������  : hmac ��event ת��Ϊ netbuf,��dmac ��netbuf��ԭΪevent,event��payload����Ϊ4B
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������
  3.��    ��   : 2016��1��23��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint32(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint32));
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_convert_event_to_netbuf_uint16
 ��������  : hmac ��event ת��Ϊ netbuf,��dmac ��netbuf��ԭΪevent,event��payload����Ϊ2B
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��23��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint16(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint16));
}

/*****************************************************************************
 �� �� ��  : hmac_hcc_tx_convert_event_to_netbuf_uint8
 ��������  : hmac ��event ת��Ϊ netbuf,��dmac ��netbuf��ԭΪevent,event��payload����Ϊ1B
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��23��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint8(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint8));
}

/*****************************************************************************
 �� �� ��  : hmac_user_add_notify_alg_tx_adapt
 ��������  : ͨ��SDIO�·����ݣ�֪ͨdmac���㷨���Ӻ���
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : z00262551
    �޸�����   : �˼�ͨ�ź�������

*****************************************************************************/
oal_uint32 hmac_user_add_notify_alg_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_user_add_notify_alg_tx_adapt::tx adapt.}");
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_add_user_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_proc_rx_process_sync_event_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��3��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_proc_rx_process_sync_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_action_event_stru));
}

oal_uint32 hmac_chan_select_channel_mac_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_set_chan_stru));
}

/*****************************************************************************
 �� �� ��  : hmac_chan_initiate_switch_to_new_channel_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��16��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_chan_initiate_switch_to_new_channel_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_set_ch_switch_info_stru));
}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/*****************************************************************************
 �� �� ��  : hmac_edca_opt_stat_event_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : wanran 00222654
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_edca_opt_stat_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint8) * 16);
}

#endif

oal_int32 hmac_rx_extend_hdr_vaild_check(struct frw_hcc_extend_hdr* pst_extend_hdr)
{
    if(OAL_UNLIKELY(pst_extend_hdr->en_nest_type >= FRW_EVENT_TYPE_BUTT))
    {
        return OAL_FALSE;
    }
#if 0
    if(OAL_UNLIKELY(pst_extend_hdr->vap_id > WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;
}

/*
oal_int32 dmac_rx_wifi_pre_action_function(oal_uint8 stype, hcc_netbuf_stru* pst_hcc_netbuf,
                                                  oal_uint8  **pre_do_context)
{
    return OAL_SUCC;
}
*/

oal_int32 hmac_rx_wifi_post_action_function(oal_uint8 stype,
                                             hcc_netbuf_stru* pst_hcc_netbuf, oal_uint8 *pst_context)
{
    oal_int32 ret = OAL_SUCC;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_vap_stru             *pst_hmac_vap;
#endif
    struct frw_hcc_extend_hdr* pst_extend_hdr;

    frw_event_mem_stru   *pst_event_mem;      /*event mem */
    frw_event_stru       *pst_event;
    hcc_event_stru       *pst_event_payload;
    mac_rx_ctl_cut_stru  *pst_rx_ctl;
    oal_uint8            *puc_hcc_extend_hdr;

    pst_extend_hdr = (struct frw_hcc_extend_hdr*)OAL_NETBUF_DATA(pst_hcc_netbuf->pst_netbuf);
    if(OAL_TRUE != hmac_rx_extend_hdr_vaild_check(pst_extend_hdr))
    {
        oal_print_hex_dump(OAL_NETBUF_DATA(pst_hcc_netbuf->pst_netbuf), (oal_int32)OAL_NETBUF_LEN(pst_hcc_netbuf->pst_netbuf),
                           32, "invaild frw extend hdr: ");
        return -OAL_EINVAL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_extend_hdr->vap_id);

    frw_event_task_lock();
    if(OAL_UNLIKELY(NULL == pst_hmac_vap))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "hmac rx adapt ignored,pst vap is null, vap id:%u", pst_extend_hdr->vap_id);
        frw_event_task_unlock();
        oal_netbuf_free(pst_hcc_netbuf->pst_netbuf);
        return -OAL_EINVAL;
    }

    if(OAL_UNLIKELY(MAC_VAP_VAILD != pst_hmac_vap->st_vap_base_info.uc_init_flag))
    {
        if(0 == pst_extend_hdr->vap_id)
        {
            /*����VAP������*/
        }
        else
        {
            OAM_WARNING_LOG2(pst_extend_hdr->vap_id, OAM_SF_ANY, "hmac rx adapt ignored,main:%u,sub:%u", pst_extend_hdr->en_nest_type,pst_extend_hdr->uc_nest_sub_type);
            frw_event_task_unlock();
            oal_netbuf_free(pst_hcc_netbuf->pst_netbuf);
            return -OAL_ENOMEM;
        }
    }
    frw_event_task_unlock();
#endif

    if(OAL_TRUE == g_ul_pm_wakeup_event)
    {
        g_ul_pm_wakeup_event = OAL_FALSE;
        if(FRW_EVENT_TYPE_WLAN_CRX == pst_extend_hdr->en_nest_type)
        {
          g_ul_print_wakeup_mgmt = OAL_TRUE;
        }
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hcc_event_stru));
    if (NULL == pst_event_mem)
    {
        OAL_IO_PRINT("[WARN]event mem alloc failed\n");
        return -OAL_ENOMEM;
    }

    /*trim the frw hcc extend header*/
    oal_netbuf_pull(pst_hcc_netbuf->pst_netbuf, OAL_SIZEOF(struct frw_hcc_extend_hdr));

    /*event hdr point*/
    pst_event = frw_get_event_stru(pst_event_mem);

    /*fill event hdr*/
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       pst_extend_hdr->en_nest_type,
                       pst_extend_hdr->uc_nest_sub_type,
                       OAL_SIZEOF(hcc_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_extend_hdr->chip_id,
                       pst_extend_hdr->device_id,
                       pst_extend_hdr->vap_id);


    pst_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_event_payload->pst_netbuf = pst_hcc_netbuf->pst_netbuf;
    pst_event_payload->ul_buf_len = OAL_NETBUF_LEN(pst_hcc_netbuf->pst_netbuf);
    //pst_event_payload->ul_buf_len = pst_hcc_netbuf->len;

    puc_hcc_extend_hdr  = OAL_NETBUF_DATA((oal_netbuf_stru *)pst_event_payload->pst_netbuf);
    pst_rx_ctl    = (mac_rx_ctl_cut_stru *)puc_hcc_extend_hdr;


    if(!(pst_rx_ctl->bit_is_beacon))
    {
        #ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
        if(OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_count_func)
        {
            g_pst_alg_process_func.p_auto_freq_count_func(1);
        }
        #endif

        //wlan_pm_feed_wdg();
    }

    frw_event_task_lock();
    ret = (oal_int32)frw_event_dispatch_event(pst_event_mem);
    frw_event_task_unlock();
    if(OAL_WARN_ON(OAL_SUCC != ret))
    {
        /*����¼����ʧ�ܣ��ڴ�ʧ���ɸú����ͷţ�ֱ�ӵ��õ���rx adapt�����ͷ�!*/
        OAL_IO_PRINT("[WARN]hcc rx post event failed!!!ret=%u,main:%d,sub:%d\n",
                    ret,
                    pst_extend_hdr->en_nest_type,
                    pst_extend_hdr->uc_nest_sub_type);
    }
    FRW_EVENT_FREE(pst_event_mem);

    return ret;
}

oal_int32 hmac_hcc_adapt_init(oal_void)
{
    hmac_tx_net_queue_map_init();
    hmac_tx_sched_info_init();
    hcc_rx_register(hcc_get_default_handler(), HCC_ACTION_TYPE_WIFI, hmac_rx_wifi_post_action_function, NULL);
#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
    hwifi_panic_log_register(&hmac_panic_hcc_adapt,NULL);
#endif
    return OAL_SUCC;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


