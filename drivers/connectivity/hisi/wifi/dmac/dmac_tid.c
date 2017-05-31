/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_tid.c
  �� �� ��   : ����
  ��    ��   : mayuan
  ��������   : 2012��11��15��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��15��
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
#include "dmac_tid.h"
#include "dmac_main.h"
#include "dmac_ext_if.h"
#include "dmac_blockack.h"
#include "hal_ext_if.h"
#include "dmac_alg.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_tx_complete.h"
#include "wlan_types.h"
#include "oal_net.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TID_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_tid_tx_queue_init
 ��������  : ��ʼ��һ���û���TID�������
 �������  : past_tx_tid_queue: ����tid�������ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_tx_queue_init(dmac_tid_stru *past_tx_tid_queue, mac_user_stru *pst_user)
{
    oal_uint8        uc_tid;
    dmac_tid_stru   *pst_tid_queue;
    oal_uint32      ul_rst = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == past_tx_tid_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_init::past_tx_tid_queue null.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
    {
        pst_tid_queue = &past_tx_tid_queue[uc_tid];

        pst_tid_queue->uc_retry_num     = 0;

        pst_tid_queue->uc_tid           = uc_tid;
        pst_tid_queue->us_mpdu_num      = 0;
        pst_tid_queue->ul_mpdu_avg_len  = 0;
        pst_tid_queue->us_user_idx      = pst_user->us_assoc_id;
        pst_tid_queue->uc_vap_id        = pst_user->uc_vap_id;

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        oal_dlist_init_head(&pst_tid_queue->st_retry_q);
        oal_netbuf_list_head_init(&pst_tid_queue->st_buff_head);
#else
        oal_dlist_init_head(&pst_tid_queue->st_hdr);
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        /* ��ʼ��HT��ص����� */
        pst_tid_queue->st_ht_tx_hdl.uc_ampdu_max_num    = 0;
        pst_tid_queue->st_ht_tx_hdl.us_ampdu_max_size   = 0;
        pst_tid_queue->st_ht_tx_hdl.ul_ampdu_max_size_vht   = 0;
        pst_tid_queue->en_tx_mode                       = DMAC_TX_MODE_NORMAL;

        /* ��ʼ��BA��ص����� */
        pst_tid_queue->pst_ba_rx_hdl = OAL_PTR_NULL;
        pst_tid_queue->pst_ba_tx_hdl = OAL_PTR_NULL;

        pst_tid_queue->en_is_delba_ing = OAL_FALSE;
        pst_tid_queue->uc_rx_wrong_ampdu_num = 0;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        /* ��ʼ��seq_num 12λȫΪ1 */
        pst_tid_queue->us_last_seq_frag_num   = 65535;

    #ifdef _PRE_WLAN_DFT_STAT
        pst_tid_queue->pst_tid_stats = (dmac_tid_stats_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                                            OAL_SIZEOF(dmac_tid_stats_stru),
                                                                            OAL_TRUE);
        if (OAL_PTR_NULL == pst_tid_queue->pst_tid_stats)
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_init::tid_stats is null.");
            ul_rst = OAL_ERR_CODE_PTR_NULL;
            break;
        }

        OAL_MEMZERO(pst_tid_queue->pst_tid_stats, OAL_SIZEOF(dmac_tid_stats_stru));
    #endif
#endif
    #ifdef _PRE_DEBUG_MODE
        pst_tid_queue->pst_tid_ampdu_stat = (dmac_tid_ampdu_stat_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                                                      OAL_SIZEOF(dmac_tid_ampdu_stat_stru),
                                                                                      OAL_TRUE);
        if (OAL_PTR_NULL == pst_tid_queue->pst_tid_ampdu_stat)
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_init::tid_ampdu_stat is null.");
            ul_rst = OAL_ERR_CODE_PTR_NULL;
            break;
        }

        OAL_MEMZERO(pst_tid_queue->pst_tid_ampdu_stat, OAL_SIZEOF(dmac_tid_ampdu_stat_stru));
    #endif

        OAL_MEMZERO(&(pst_tid_queue->st_rate_stats), OAL_SIZEOF(dmac_tx_normal_rate_stats_stru));
    }

    if(OAL_SUCC != ul_rst)
    {
        for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
        {
             pst_tid_queue = &past_tx_tid_queue[uc_tid];

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
             if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
             {
                OAL_MEM_FREE(pst_tid_queue->pst_tid_stats, OAL_TRUE);
                pst_tid_queue->pst_tid_stats = OAL_PTR_NULL;
             }
#endif
#endif

#ifdef _PRE_DEBUG_MODE

             if (OAL_PTR_NULL != pst_tid_queue->pst_tid_ampdu_stat)
             {
                OAL_MEM_FREE(pst_tid_queue->pst_tid_ampdu_stat, OAL_TRUE);
                pst_tid_queue->pst_tid_ampdu_stat = OAL_PTR_NULL;
             }
#endif
        }
    }

    return ul_rst;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_tx_queue_exit
 ��������  : tid queue�˳�ʱ�ͷ��ڴ棬�û�ɾ��ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_tid_tx_queue_exit(dmac_user_stru *pst_dmac_user)
{
    oal_uint8           uc_tid_idx;
    dmac_tid_stru      *pst_tid_queue;

    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx++)
    {
        pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_idx]);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    #ifdef _PRE_WLAN_DFT_STAT
        if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
        {
            OAL_MEM_FREE(pst_tid_queue->pst_tid_stats, OAL_TRUE);
            pst_tid_queue->pst_tid_stats = OAL_PTR_NULL;
        }
    #endif
#else
        pst_tid_queue = pst_tid_queue;
#endif

    #ifdef _PRE_DEBUG_MODE
        if (OAL_PTR_NULL != pst_tid_queue->pst_tid_ampdu_stat)
        {
            OAL_MEM_FREE(pst_tid_queue->pst_tid_ampdu_stat, OAL_TRUE);
            pst_tid_queue->pst_tid_ampdu_stat = OAL_PTR_NULL;
        }
    #endif
    }


}

/*****************************************************************************
 �� �� ��  : dmac_tid_tx_queue_enqueue_head
 ��������  : ��һ��MPDU����MPDU�����û���TID������е�ͷ��
 �������  : pst_tid_queue: ����tid�������ָ��
             pst_netbuf   : netbufָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_tx_queue_enqueue_head(dmac_tid_stru *pst_tid_queue, oal_dlist_head_stru *pst_tx_dscr_list_hdr, oal_uint8 uc_mpdu_num)
{
    mac_device_stru     *pst_device;
    dmac_user_stru      *pst_user;
#ifdef _PRE_DEBUG_MODE
    hal_tx_dscr_stru    *pst_tx_dscr_trace;
    oal_dlist_head_stru *pst_trace_entry;
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru       *pst_vap;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru *pst_tid_stats;
#endif
#endif
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_tid_queue)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue_head::pst_tid_queue null.");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    pst_tid_stats = pst_tid_queue->pst_tid_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_stats))
    {
        OAM_WARNING_LOG0(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue_head::tid_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
#endif

    pst_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_tid_queue->us_user_idx);
    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG1(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue_head::pst_user[%d] null.}", pst_tid_queue->us_user_idx);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_enqueue_head_ptr_null_cnt, uc_mpdu_num);
#endif
#endif
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ����device�ṹ���µ�ͳ����Ϣ */
    pst_device = mac_res_get_dev(pst_user->st_user_base_info.uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue_head::pst_device[%d] null.}", pst_user->st_user_base_info.uc_device_id);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_enqueue_head_ptr_null_cnt, uc_mpdu_num);
#endif
#endif
        return OAL_ERR_CODE_PTR_NULL;
    }
    if ((pst_device->us_total_mpdu_num + uc_mpdu_num) > WLAN_TID_MPDU_NUM_LIMIT)
    {
        OAM_WARNING_LOG1(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue_head::WLAN_TID_MPDU_NUM_LIMIT exceed, dev_mpdu_num = %d}", pst_device->us_total_mpdu_num);
        OAM_WARNING_LOG4(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue_head::be = %d, bk = %d, vi = %d, vo = %d}",
                            pst_device->aus_ac_mpdu_num[WLAN_WME_AC_BE],
                            pst_device->aus_ac_mpdu_num[WLAN_WME_AC_BK],
                            pst_device->aus_ac_mpdu_num[WLAN_WME_AC_VI],
                            pst_device->aus_ac_mpdu_num[WLAN_WME_AC_VO]);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_enqueue_head_full_cnt, uc_mpdu_num);
#endif
#endif
#ifdef _PRE_WLAN_PERFORM_STAT
        /* ����ͳ����־ */
        dmac_stat_tid_per(&(pst_user->st_user_base_info), pst_tid_queue->uc_tid, 0, uc_mpdu_num, DMAC_STAT_PER_SW_RETRY_OVERFLOW);
#endif
        return OAL_FAIL;
    }

    pst_device->us_total_mpdu_num += uc_mpdu_num;
    pst_tid_queue->us_mpdu_num += uc_mpdu_num;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_enqueue_total_cnt, uc_mpdu_num);
#endif
#endif

    pst_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id] += uc_mpdu_num;
    pst_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)] += (oal_uint16) uc_mpdu_num;

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    pst_vap = mac_res_get_mac_vap(pst_tid_queue->uc_vap_id);
    dmac_alg_flowctl_backp_notify(pst_vap, pst_device->us_total_mpdu_num, pst_device->aus_ac_mpdu_num);
#endif

#ifdef _PRE_DEBUG_MODE
    OAL_DLIST_SEARCH_FOR_EACH(pst_trace_entry, pst_tx_dscr_list_hdr)
    {
        pst_tx_dscr_trace = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_trace_entry, hal_tx_dscr_stru, st_entry);
        OAL_MEM_TRACE(pst_tx_dscr_trace, OAL_FALSE);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_dlist_join_head(&pst_tid_queue->st_retry_q, pst_tx_dscr_list_hdr);
#else
    oal_dlist_join_head(&pst_tid_queue->st_hdr, pst_tx_dscr_list_hdr);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_get_mpdu_by_index
 ��������  : ��ȡTID��ĳ��MPDU,
 �������  : pst_tid      : ָ��tid��ָ��
             us_mpdu_index: MPDU����,��0��ʼ
 �������  : ppst_netbuf_stru: ָ��netbuf��ָ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_get_mpdu_by_index(dmac_tid_stru *pst_tid_queue,
                                        oal_uint16 us_mpdu_index,
                                        oal_netbuf_stru **ppst_netbuf_stru)
{
    oal_uint8              uc_mpdu_idx = 0;
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_netbuf_stru       *pst_netbuf_tmp;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    hal_tx_dscr_stru      *pst_dscr;
    oal_dlist_head_stru   *pst_dscr_entry = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_queue || OAL_PTR_NULL == ppst_netbuf_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_tid_get_mpdu_by_index::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ж�us_mpdu_index�Ƿ񳬳���ǰ��mpdu���� */
    if (OAL_UNLIKELY(us_mpdu_index > pst_tid_queue->us_mpdu_num))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_tid_get_mpdu_by_index::us_mpdu_index[%d] > us_mpdu_num[%d].}",
                         us_mpdu_index, pst_tid_queue->us_mpdu_num);

        *ppst_netbuf_stru = OAL_PTR_NULL;
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* �ȱ����ش����� */
    uc_mpdu_idx     = 0;
    pst_dscr_entry  = OAL_PTR_NULL;
    if (OAL_TRUE != oal_dlist_is_empty(&pst_tid_queue->st_retry_q))
    {
        pst_dscr_entry = pst_tid_queue->st_retry_q.pst_next;
        for (uc_mpdu_idx = 0; uc_mpdu_idx < us_mpdu_index; uc_mpdu_idx++)
        {
            /* ���us_mpdu_index=0��ʾ��һ������� */
            pst_dscr_entry = pst_dscr_entry->pst_next;
            if (pst_dscr_entry == &pst_tid_queue->st_retry_q)
            {
                pst_dscr_entry = OAL_PTR_NULL;
                break;
            }
        }

    }

    /* �ж����ش������Ƿ��ҵ� */
    if ((uc_mpdu_idx == us_mpdu_index) && (pst_dscr_entry != OAL_PTR_NULL))
    {
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        *ppst_netbuf_stru = pst_dscr->pst_skb_start_addr;

        return OAL_SUCC;
    }

    /* ������ش�����û���ҵ� */
    us_mpdu_index -= uc_mpdu_idx;
    uc_mpdu_idx    = 0;
    pst_netbuf_tmp = OAL_PTR_NULL;
    /* �ٱ���netbuf���� */
    if (OAL_TRUE == oal_netbuf_list_empty(&pst_tid_queue->st_buff_head))
    {
        *ppst_netbuf_stru = OAL_PTR_NULL;

        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_tid_get_mpdu_by_index::queue empty.}");
        return OAL_FAIL;
    }

    pst_netbuf_tmp   = pst_tid_queue->st_buff_head.pst_next;
    for (uc_mpdu_idx = 0; uc_mpdu_idx < us_mpdu_index; uc_mpdu_idx++)
    {
        pst_netbuf_tmp = pst_netbuf_tmp->next;
        if (pst_netbuf_tmp == (oal_netbuf_stru *)&pst_tid_queue->st_buff_head)
        {
            pst_netbuf_tmp = OAL_PTR_NULL;
            break;
        }
    }

    /* ��netbuf�����ҵ� */
    if (pst_netbuf_tmp != OAL_PTR_NULL)
    {
        *ppst_netbuf_stru = pst_netbuf_tmp;
        return OAL_SUCC;
    }

    /* û���ҵ� */
    *ppst_netbuf_stru = OAL_PTR_NULL;
    return OAL_FAIL;
#else
    /* ���tid�������Ϊ�գ�����ֱ���˳� */
    if (OAL_TRUE == oal_dlist_is_empty(&pst_tid_queue->st_hdr))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_tid_get_mpdu_by_index::queue empty.}");
        *ppst_netbuf_stru = OAL_PTR_NULL;
        return OAL_FAIL;
    }

    pst_dscr_entry = pst_tid_queue->st_hdr.pst_next;
    for (uc_mpdu_idx = 0; uc_mpdu_idx < us_mpdu_index; uc_mpdu_idx++)
    {
        /* ��ȡCB */
        pst_dscr_entry = pst_dscr_entry->pst_next;
    }
    pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
    *ppst_netbuf_stru = pst_dscr->pst_skb_start_addr;

    return OAL_SUCC;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
}

/*****************************************************************************
 �� �� ��  : dmac_tid_get_min_max_mpdu_length
 ��������  : ��ȡTID����ָ����ĿMPDU�е���С������MPDU����
 �������  : pst_tid         : ָ��tid��ָ��
             us_head_mpdu_num:
 �������  : pus_min_mpdu_len: ��СMPDU����
             pus_max_mpdu_len: ���MPDU����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_get_min_max_mpdu_length(mac_user_stru *pst_mac_user,
                                            oal_uint8 uc_tid_num,
                                        oal_uint16      us_head_mpdu_num,
                                        oal_uint16     *pus_min_mpdu_len,
                                        oal_uint16     *pus_max_mpdu_len)
{
    oal_uint16              us_mpdu_idx;
    oal_uint16              us_mpdu_num;
    hal_tx_dscr_stru       *pst_dscr;
    oal_dlist_head_stru    *pst_dscr_entry;
    oal_netbuf_stru        *pst_netbuf;
    mac_tx_ctl_stru        *pst_tx_ctrl;
    oal_uint16              us_min_mpdu_len = 0xffff;
    oal_uint16              us_max_mpdu_len = 0;
    dmac_user_stru         *pst_dmac_user;
    dmac_tid_stru          *pst_tid_queue;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user || OAL_PTR_NULL == pus_min_mpdu_len ||
        OAL_PTR_NULL == pus_max_mpdu_len))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_tid_get_min_max_mpdu_length::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_tid_by_num::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_num]);
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    us_min_mpdu_len = 0;
    us_max_mpdu_len = 0;

    /* �ȱ����ش����� */
    if (OAL_TRUE != oal_dlist_is_empty(&pst_tid_queue->st_retry_q))
    {
        pst_dscr_entry  = pst_tid_queue->st_retry_q.pst_next;
        us_mpdu_num     = OAL_MIN(pst_tid_queue->uc_retry_num, us_head_mpdu_num);

        for (us_mpdu_idx = 0; us_mpdu_idx < us_mpdu_num; us_mpdu_idx++)
        {
            pst_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            pst_netbuf  = pst_dscr->pst_skb_start_addr;
            pst_tx_ctrl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

            if (MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) < us_min_mpdu_len)
            {
                us_min_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctrl);
            }

            if (MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) > us_max_mpdu_len)
            {
                us_max_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctrl);
            }

            pst_dscr_entry = pst_dscr_entry->pst_next;
        }
    }

    if ((us_head_mpdu_num > pst_tid_queue->uc_retry_num) && (OAL_TRUE != oal_netbuf_list_empty(&pst_tid_queue->st_buff_head)))
    {
        us_mpdu_num = us_head_mpdu_num - pst_tid_queue->uc_retry_num;

        /* �ٱ���������� */
        pst_netbuf   = pst_tid_queue->st_buff_head.pst_next;
        for (us_mpdu_idx = 0; us_mpdu_idx < us_mpdu_num; us_mpdu_idx++)
        {
            pst_tx_ctrl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
            if (MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) < us_min_mpdu_len)
            {
                us_min_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctrl);
            }

            if (MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) > us_max_mpdu_len)
            {
                us_max_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctrl);
            }

            pst_netbuf = pst_netbuf->next;
            if (pst_netbuf == (oal_netbuf_stru *)&pst_tid_queue->st_buff_head)
            {
                break;
            }
        }

    }
#else
    /* ���tid�������Ϊ�գ�����ֱ���˳� */
    if (OAL_TRUE == oal_dlist_is_empty(&pst_tid_queue->st_hdr))
    {
        *pus_min_mpdu_len = 0;
        *pus_max_mpdu_len = 0;
        return OAL_SUCC;
    }

    pst_dscr_entry  = pst_tid_queue->st_hdr.pst_next;
    us_mpdu_num     = OAL_MIN(pst_tid_queue->us_mpdu_num, us_head_mpdu_num);

    for (us_mpdu_idx = 0; us_mpdu_idx < us_mpdu_num; us_mpdu_idx++)
    {
        pst_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        pst_netbuf  = pst_dscr->pst_skb_start_addr;
        pst_tx_ctrl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

        if (MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) < us_min_mpdu_len)
        {
            us_min_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctrl);
        }

        if (MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) > us_max_mpdu_len)
        {
            us_max_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctrl);
        }

        pst_dscr_entry = pst_dscr_entry->pst_next;
    }
#endif /* */

    *pus_min_mpdu_len = us_min_mpdu_len;
    *pus_max_mpdu_len = us_max_mpdu_len;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_tx_queue_remove_list
 ��������  : ��һ��MPDU��TID���������ɾ�����ͷţ��㷨ֻ��ͻ������Ż����,���ܲ�����
 �������  : pst_tid_queue: TID�������
             uc_mpdu_num  : ���tid���������ɾ����MPDU����
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��22��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_delete_mpdu_head(
                dmac_tid_stru              *pst_tid_queue,
                oal_uint16                  us_mpdu_num)
{
    mac_device_stru            *pst_mac_device;
    oal_netbuf_stru            *pst_netbuf = OAL_PTR_NULL;
    hal_tx_dscr_stru           *pst_dscr;
    oal_dlist_head_stru        *pst_dscr_entry;
    dmac_user_stru             *pst_user;
    oal_uint16                  us_mpdu_idx;
    mac_tx_ctl_stru            *pst_cb;
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_uint16                  us_num_tmp;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru               *pst_vap;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_tid_delete_mpdu_head::pst_tid_queue null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_tid_queue->us_user_idx);

    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(pst_tid_queue->uc_vap_id, OAM_SF_ANY, "{dmac_tid_delete_mpdu_head::pst_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_tid_queue->uc_vap_id, OAM_SF_ANY, "{dmac_tid_delete_mpdu_head::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* �ȱ����ش����� */
    us_num_tmp      = OAL_MIN(pst_tid_queue->uc_retry_num, us_mpdu_num);
    for (us_mpdu_idx = 0; us_mpdu_idx < us_num_tmp; us_mpdu_idx++)
    {
        if (OAL_TRUE == oal_dlist_is_empty(&pst_tid_queue->st_retry_q))
        {
            break;
        }
        pst_dscr_entry  = oal_dlist_delete_head(&(pst_tid_queue->st_retry_q));
        pst_dscr        = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        pst_netbuf = pst_dscr->pst_skb_start_addr;
        if ((0 != pst_tid_queue->uc_retry_num) && (OAL_TRUE == pst_dscr->bit_is_retried))
        {
            pst_tid_queue->uc_retry_num--;
            if (OAL_PTR_NULL != pst_tid_queue->pst_ba_tx_hdl)
            {
                pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
                dmac_ba_update_baw(pst_tid_queue->pst_ba_tx_hdl, mac_get_cb_seqnum(pst_cb));
            }
    #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        #ifdef _PRE_WLAN_DFT_STAT
            if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
            {
                DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_dequeue_cnt, 1);
            }
        #endif
    #endif
        }
        OAL_MEM_FREE(pst_dscr, OAL_TRUE);
        dmac_tx_excp_free_netbuf(pst_netbuf);

        pst_tid_queue->us_mpdu_num--;
        pst_mac_device->us_total_mpdu_num--;
        pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
        pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
    }

    if (us_mpdu_num > us_mpdu_idx)
    {
        us_num_tmp = us_mpdu_num - us_mpdu_idx;
        for (us_mpdu_idx = 0; us_mpdu_idx < us_num_tmp; us_mpdu_idx++)
        {
            if (OAL_TRUE == oal_netbuf_list_empty(&pst_tid_queue->st_buff_head))
            {
                break;
            }

            pst_netbuf  = dmac_tx_dequeue_first_mpdu(&pst_tid_queue->st_buff_head);
            dmac_tx_excp_free_netbuf(pst_netbuf);
            pst_tid_queue->us_mpdu_num--;
            pst_mac_device->us_total_mpdu_num--;
            pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
        }
    }
#else
    for (us_mpdu_idx = 0; us_mpdu_idx < us_mpdu_num; us_mpdu_idx++)
    {
        /* ���tid�������Ϊ�գ�����ֱ���˳� */
        if (OAL_TRUE == oal_dlist_is_empty(&pst_tid_queue->st_hdr))
        {
            break;
        }

        pst_dscr_entry  = oal_dlist_delete_head(&(pst_tid_queue->st_hdr));
        pst_dscr        = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);

        pst_netbuf = pst_dscr->pst_skb_start_addr;

        if (0 != pst_tid_queue->uc_retry_num)
        {
            pst_tid_queue->uc_retry_num--;
            if (OAL_PTR_NULL != pst_tid_queue->pst_ba_tx_hdl)
            {
                pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
                dmac_ba_update_baw(pst_tid_queue->pst_ba_tx_hdl, mac_get_cb_seqnum(pst_cb));
            }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)

        #ifdef _PRE_WLAN_DFT_STAT
            if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
            {
                DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_dequeue_cnt, 1);
            }
        #endif
#endif
        }
        OAL_MEM_FREE(pst_dscr, OAL_TRUE);
        dmac_tx_excp_free_netbuf(pst_netbuf);

        pst_tid_queue->us_mpdu_num--;

        pst_mac_device->us_total_mpdu_num--;
        pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
        pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
    }
#endif /* _PRE_TX_DSCR */

    /* ����tid_dlist���� */
    dmac_alg_tid_update_notify(pst_tid_queue);

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    pst_vap = mac_res_get_mac_vap(pst_tid_queue->uc_vap_id);
    dmac_alg_flowctl_backp_notify(pst_vap, pst_mac_device->us_total_mpdu_num, pst_mac_device->aus_ac_mpdu_num);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_delete_mpdu_tail
 ��������  : ɾ�����ͷ�TID��β���ɸ�MPDU,�㷨ֻ��ͻ������Ż����,���ܲ�����
 �������  : pst_tid    : ָ��TID��ָ��
             uc_mpdu_num: MPDU����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_delete_mpdu_tail(dmac_tid_stru *pst_tid_queue, oal_uint16 us_mpdu_num)
{
    mac_device_stru            *pst_mac_device;
    oal_netbuf_stru            *pst_netbuf = OAL_PTR_NULL;
    hal_tx_dscr_stru           *pst_dscr;
    oal_dlist_head_stru        *pst_dscr_entry;
    dmac_user_stru             *pst_user;
    oal_uint16                  us_mpdu_idx;
    mac_tx_ctl_stru            *pst_cb;

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru               *pst_vap;
#endif
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_uint16                  us_num_tmp;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_tid_delete_mpdu_tail::pst_tid_queue null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(pst_tid_queue->us_mpdu_num < us_mpdu_num))
    {
        OAM_WARNING_LOG2(pst_tid_queue->uc_vap_id, OAM_SF_ANY, "{dmac_tid_delete_mpdu_tail::uc_mpdu_num[%d] > tid_queue.us_mpdu_num[%d].}",
                         us_mpdu_num, pst_tid_queue->us_mpdu_num);
        return OAL_FAIL;
    }

    pst_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_tid_queue->us_user_idx);

    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(pst_tid_queue->uc_vap_id, OAM_SF_ANY, "{dmac_tid_delete_mpdu_tail::pst_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_tid_queue->uc_vap_id, OAM_SF_ANY, "{dmac_tid_delete_mpdu_tail::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* ��ɾ��netbuf���� */
    us_num_tmp = us_mpdu_num;
    for (us_mpdu_idx = 0; us_mpdu_idx < us_num_tmp; us_mpdu_idx++)
    {
        if (OAL_TRUE == oal_netbuf_list_empty(&pst_tid_queue->st_buff_head))
        {
            break;
        }

        pst_netbuf  = dmac_tx_dequeue_first_mpdu(&pst_tid_queue->st_buff_head);
        dmac_tx_excp_free_netbuf(pst_netbuf);
        pst_tid_queue->us_mpdu_num--;
        pst_mac_device->us_total_mpdu_num--;
        pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
        pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
    }

    /* ��ɾ���ش����� */
    if (us_mpdu_num > us_mpdu_idx)
    {
        us_num_tmp = us_mpdu_num - us_mpdu_idx;
        for (us_mpdu_idx = 0; us_mpdu_idx < us_num_tmp; us_mpdu_idx++)
        {
            if (OAL_TRUE == oal_dlist_is_empty(&pst_tid_queue->st_retry_q))
            {
                break;
            }
            pst_dscr_entry  = oal_dlist_delete_tail(&(pst_tid_queue->st_retry_q));
            pst_dscr        = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            pst_netbuf = pst_dscr->pst_skb_start_addr;
            if ((0 != pst_tid_queue->uc_retry_num) && (OAL_TRUE == pst_dscr->bit_is_retried))
            {
                pst_tid_queue->uc_retry_num--;
                if (OAL_PTR_NULL != pst_tid_queue->pst_ba_tx_hdl)
                {
                    pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
                    dmac_ba_update_baw(pst_tid_queue->pst_ba_tx_hdl, mac_get_cb_seqnum(pst_cb));
                }
        #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            #ifdef _PRE_WLAN_DFT_STAT
                if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
                {
                    DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_dequeue_cnt, 1);
                }
            #endif
        #endif
            }
            OAL_MEM_FREE(pst_dscr, OAL_TRUE);
            dmac_tx_excp_free_netbuf(pst_netbuf);

            pst_tid_queue->us_mpdu_num--;
            pst_mac_device->us_total_mpdu_num--;
            pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
        }
    }
#else
    /* ɾ����pst_netbuf��ʼ��N��MPDU */
    for (us_mpdu_idx = 0; us_mpdu_idx < us_mpdu_num; us_mpdu_idx++)
    {
        pst_dscr_entry = oal_dlist_delete_tail(&pst_tid_queue->st_hdr);
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        pst_netbuf = pst_dscr->pst_skb_start_addr;

        if (pst_tid_queue->us_mpdu_num == pst_tid_queue->uc_retry_num)
        {
            pst_tid_queue->uc_retry_num--;

            if (OAL_PTR_NULL != pst_tid_queue->pst_ba_tx_hdl)
            {
                pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
                dmac_ba_update_baw(pst_tid_queue->pst_ba_tx_hdl, mac_get_cb_seqnum(pst_cb));
            }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        #ifdef _PRE_WLAN_DFT_STAT
            if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
            {
                DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_dequeue_cnt, 1);
            }
        #endif
#endif
        }
        OAL_MEM_FREE(pst_dscr, OAL_TRUE);
        dmac_tx_excp_free_netbuf(pst_netbuf);

        pst_tid_queue->us_mpdu_num--;

        /*zourongά����֤DTS2014071403907*/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        if(pst_tid_queue->us_mpdu_num < pst_tid_queue->uc_retry_num)
        {
            OAL_IO_PRINT(KERN_CRIT "pst_tid_queue->us_mpdu_num(%d) < pst_tid_queue->uc_retry_num(%d)\n",
                        pst_tid_queue->us_mpdu_num,pst_tid_queue->uc_retry_num);
        }
#endif
        pst_mac_device->us_total_mpdu_num--;
        pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
        pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;

    }
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    /* ����tid_dlist���� */
    dmac_alg_tid_update_notify(pst_tid_queue);

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    pst_vap = mac_res_get_mac_vap(pst_tid_queue->uc_vap_id);
    dmac_alg_flowctl_backp_notify(pst_vap, pst_mac_device->us_total_mpdu_num, pst_mac_device->aus_ac_mpdu_num);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_get_util_ratio
 ��������  : ��ȡdevice������TID��ʹ����,�㷨Լ50ms��һ��
 �������  : uc_chip_id  : chip ID
             uc_device_id: device ID
 �������  : puc_ratio   : ʹ����
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_get_util_ratio(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint8 *puc_ratio)
{
    mac_device_stru *pst_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_ratio))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_tid_get_util_ratio::puc_ratio null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((uc_chip_id >= WLAN_CHIP_MAX_NUM_PER_BOARD) || (uc_device_id >= WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_tid_get_util_ratio::invalid param,uc_chip_id=%d, uc_device_id=%d.}", uc_chip_id, uc_device_id);

        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_device = mac_res_get_dev(uc_device_id);

    /* ʹ����(%) = (��ǰ���� * 100 )/����� = (��ǰ���� * 100 )/256 = (��ǰ���� * 100 ) >> 8 */
    *puc_ratio = (oal_uint8)((pst_device->us_total_mpdu_num * 100 ) >> WLAN_TID_MPDU_NUM_BIT);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_get_normal_rate_stats
 ��������  : ��ȡĳ��TID����ͳ����Ϣ
 �������  : pst_mac_user: ָ��user��ָ��
             uc_tid_id   : TID
 �������  : ppst_rate_stats_info: ָ������ͳ����Ϣ��ָ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_get_normal_rate_stats(
                mac_user_stru                      *pst_mac_user,
                oal_uint8                           uc_tid_id,
                dmac_tx_normal_rate_stats_stru    **ppst_rate_stats_info)
{
    dmac_user_stru     *pst_dmac_user;

    if ((OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == ppst_rate_stats_info))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_tid_get_normal_rate_stats::param null, pst_mac_user=%d, ppst_rate_stats_info=%d.}",
                       pst_mac_user, ppst_rate_stats_info);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (uc_tid_id >= WLAN_TID_MAX_NUM)
    {
        OAM_ERROR_LOG1(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_tid_get_normal_rate_stats::invalid uc_tid_id[%d].", uc_tid_id);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_tid_get_normal_rate_stats::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *ppst_rate_stats_info = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_id].st_rate_stats);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tid_set_normal_rate_stats
 ��������  : ����ĳ��TID������ͳ����Ϣ
 �������  : pst_mac_user: ָ���û���ָ��
             uc_tid_id   : TID
             pst_rate_stats_info: ָ������ͳ����Ϣ��ָ��
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_set_normal_rate_stats(
                mac_user_stru                      *pst_mac_user,
                oal_uint8                           uc_tid_id,
                dmac_tx_normal_rate_stats_stru     *pst_rate_stats_info)
{
    dmac_user_stru     *pst_dmac_user;

    dmac_tx_normal_rate_stats_stru *pst_rate_stats;

    if ((OAL_PTR_NULL == pst_mac_user)
     || (OAL_PTR_NULL == pst_rate_stats_info))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_tid_set_normal_rate_stats::param null, pst_mac_user=%d, pst_rate_stats_info=%d.}",
                       pst_mac_user, pst_rate_stats_info);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (uc_tid_id >= WLAN_TID_MAX_NUM)
    {
        OAM_ERROR_LOG1(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_tid_set_normal_rate_stats::invalid uc_tid_id[%d].", uc_tid_id);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_tid_set_normal_rate_stats::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rate_stats = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_id].st_rate_stats);

	pst_rate_stats->ul_best_rate_goodput_kbps = pst_rate_stats_info->ul_best_rate_goodput_kbps;
    pst_rate_stats->ul_rate_kbps        = pst_rate_stats_info->ul_rate_kbps;
    pst_rate_stats->uc_aggr_subfrm_size = pst_rate_stats_info->uc_aggr_subfrm_size;
    pst_rate_stats->uc_per              = pst_rate_stats_info->uc_per;

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 �� �� ��  : dmac_tid_flush_retry_frame
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_tid_flush_retry_frame(mac_device_stru *pst_device, dmac_tid_stru *pst_tid)
{
    oal_uint8            uc_dscr_index;
    hal_tx_dscr_stru    *pst_dscr;
    oal_dlist_head_stru *pst_dscr_entry;
    oal_netbuf_stru     *pst_netbuf = OAL_PTR_NULL;


    //ά�⣬������tid���еĳ��ȣ���retry_num���Ƚ�
    oal_dlist_head_stru *pst_dlist_pos;
    oal_uint16           us_num = 0 ;

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru        *pst_vap    = OAL_PTR_NULL;
#endif
    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos,&pst_tid->st_hdr)
    {
        us_num++;
    }

    for (uc_dscr_index = 0; uc_dscr_index < pst_tid->uc_retry_num; uc_dscr_index++)
    {
        if (OAL_TRUE == oal_dlist_is_empty(&pst_tid->st_hdr))
        {
            OAM_ERROR_LOG3(0, OAM_SF_ANY, "{dmac_tid_flush_retry_frame::retry num wrong, dscr in tid queue = %d,uc_dscr_index = %d,uc_retry_num = %d.}",us_num,uc_dscr_index,pst_tid->uc_retry_num);
            #if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
            OAL_IO_PRINT(KERN_CRIT"retry num wrong, dscr in tid queue = %d,uc_dscr_index = %d,uc_retry_num = %d\n",us_num,uc_dscr_index,pst_tid->uc_retry_num);
            OAL_BUG_ON(1);
            #endif
            break;
        }

        pst_dscr_entry = oal_dlist_delete_head(&pst_tid->st_hdr);
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);

        pst_netbuf = pst_dscr->pst_skb_start_addr;
        OAL_MEM_FREE(pst_dscr, OAL_TRUE);
        dmac_tx_excp_free_netbuf(pst_netbuf);

        pst_tid->us_mpdu_num--;
        pst_device->us_total_mpdu_num--;
        pst_device->aus_vap_mpdu_num[pst_tid->uc_vap_id]--;
        pst_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid->uc_tid)]--;
    }
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    pst_vap = mac_res_get_mac_vap(pst_tid->uc_vap_id);
    dmac_alg_flowctl_backp_notify(pst_vap, pst_device->us_total_mpdu_num, pst_device->aus_ac_mpdu_num);
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_PTR_NULL != pst_tid->pst_tid_stats)
    {
        DMAC_TID_STATS_INCR(pst_tid->pst_tid_stats->ul_tid_retry_dequeue_cnt, pst_tid->uc_retry_num);
    }
#endif
#endif
    pst_tid->uc_retry_num = 0;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_uint32  dmac_release_tid_buffs_by_user(dmac_user_stru    *pst_dmac_user,
                                        oal_uint32       ul_nums)
{
    oal_uint32                      ul_tid_idx;
    dmac_tid_stru                  *pst_tid_queue;
    oal_uint32                      ul_remain_nums = ul_nums;
    oal_uint32                      ul_free_nums = 0;
    oal_uint32                      ul_free_mpdu_nums = 0;

    for (ul_tid_idx = 0; ul_tid_idx < WLAN_TID_MAX_NUM; ul_tid_idx++)
    {
        pst_tid_queue = &pst_dmac_user->ast_tx_tid_queue[ul_tid_idx];

        if(0 == pst_tid_queue->us_mpdu_num)
            continue;

        if(pst_tid_queue->us_mpdu_num >= ul_remain_nums)
        {
            ul_free_mpdu_nums = ul_remain_nums;
        }
        else
        {
            ul_free_mpdu_nums = (oal_uint32)pst_tid_queue->us_mpdu_num;
        }

        if(OAL_SUCC == dmac_tid_delete_mpdu_tail(pst_tid_queue, (oal_uint16)ul_free_mpdu_nums))
        {
            ul_free_nums += ul_free_mpdu_nums;
        }

        if(ul_free_nums >= ul_nums)
        {
            break;
        }

        ul_remain_nums = ul_nums - ul_free_nums;
    }

    return ul_free_nums;
}

oal_uint32  dmac_release_tid_buffs_by_vap(dmac_vap_stru     *pst_dmac_vap,
                                        oal_uint32       ul_nums)
{
    dmac_user_stru          *pst_dmac_user;
    oal_dlist_head_stru     *pst_entry;
    mac_user_stru           *pst_user_tmp;
    oal_uint32          ul_remain_nums = ul_nums;
    oal_uint32          ul_free_nums = 0;

    if(NULL == pst_dmac_vap)
    {
        return ul_free_nums;
    }

    if(OAL_TRUE == oal_dlist_is_empty(&(pst_dmac_vap->st_vap_base_info.st_mac_user_list_head)))
    {
        return ul_free_nums;
    }

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_dmac_vap->st_vap_base_info.st_mac_user_list_head))
    {
        pst_user_tmp = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_release_tid_buffs_by_vap::null pointer,pst_dmac_user[%d].}", pst_user_tmp->us_assoc_id);
            continue;
        }
        ul_free_nums += dmac_release_tid_buffs_by_user(pst_dmac_user, ul_remain_nums);
        if(ul_free_nums >= ul_nums)
        {
            break;
        }
        ul_remain_nums = ul_nums - ul_free_nums ;
    }

    return ul_free_nums;
}

/*****************************************************************************
 �� �� ��  : dmac_release_tid_buffs
 ��������  : �ڴ����ʱɾ��tid�е����ݣ��ӵ�ǰVAP��ʼ����ɾ�������ȼ�tid����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��14��
    ��    ��   : z00262551 zhouxinfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_release_tid_buffs(dmac_vap_stru     *pst_dmac_vap,
                                        mac_device_stru  *pst_device,
                                        oal_uint32       ul_nums)
{
    oal_uint32 ul_free_nums = 0;
    oal_uint32 ul_remain_nums = ul_nums;
    oal_uint8  uc_vap_idx;
    dmac_vap_stru  *pst_dmac_crr_vap = NULL;

    /*����ɾ����ǰVAP*/
    if(NULL != pst_dmac_vap)
    {
        ul_free_nums += dmac_release_tid_buffs_by_vap(pst_dmac_vap, ul_remain_nums);
    }

    if(ul_free_nums >= ul_nums)
    {
        return ul_free_nums;
    }

    ul_remain_nums = ul_nums - ul_free_nums;

    /* ����device������vap�� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_crr_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_crr_vap)
        {
            OAM_ERROR_LOG1(pst_device->auc_vap_id[uc_vap_idx], OAM_SF_ANY,
                           "{dmac_release_tid_buffs::pst_vap null,uc_vap_idx=%d.}",
                           uc_vap_idx);
            continue;
        }

        if(pst_dmac_crr_vap == pst_dmac_vap)
        {
            continue;
        }

        ul_free_nums += dmac_release_tid_buffs_by_vap(pst_dmac_crr_vap, ul_remain_nums);
        if(ul_free_nums >= ul_nums)
        {
            break;
        }

        ul_remain_nums = ul_nums - ul_free_nums;
    }

    return ul_free_nums;

}
#endif

/*****************************************************************************
 �� �� ��  : dmac_tid_clear
 ��������  : ɾ��tid�����е�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_clear(mac_user_stru *pst_mac_user, mac_device_stru *pst_mac_device)
{
    oal_uint32                      ul_tid_idx;
    dmac_tid_stru                  *pst_tid_queue;
    oal_dlist_head_stru            *pst_entry;
    hal_tx_dscr_stru               *pst_tx_dscr;
    dmac_user_stru                 *pst_dmac_user;
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru                   *pst_vap;
#endif
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_netbuf_stru                *pst_netbuf;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    if (OAL_PTR_NULL == pst_mac_user || OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_tid_clear::param null, pst_mac_user=%d, pst_mac_device=%d.}",
                       pst_mac_user, pst_mac_device);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)pst_mac_user;

    for (ul_tid_idx = 0; ul_tid_idx < WLAN_TID_MAX_NUM; ul_tid_idx++)
    {
        pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[ul_tid_idx]);

    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        /* �ͷ��ش��� */
        pst_entry = pst_tid_queue->st_retry_q.pst_next;
        while (pst_entry != &pst_tid_queue->st_retry_q)
        {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_entry, hal_tx_dscr_stru, st_entry);
            oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
            pst_mac_device->us_total_mpdu_num--;
            pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
            dmac_free_tx_dscr(pst_tx_dscr);

            pst_entry = pst_tid_queue->st_retry_q.pst_next;
        }

        pst_netbuf  = pst_tid_queue->st_buff_head.pst_next;
        while (pst_netbuf != (oal_netbuf_stru *)&pst_tid_queue->st_buff_head)
        {
            /* ���ͷ�netbuf������� */
            pst_netbuf  = dmac_tx_dequeue_first_mpdu(&pst_tid_queue->st_buff_head);
            pst_mac_device->us_total_mpdu_num--;
            pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
            dmac_tx_excp_free_netbuf(pst_netbuf);

            pst_netbuf  = pst_tid_queue->st_buff_head.pst_next;
        }
    #else
        /* �ͷ�TID�����еİ� */
        pst_entry = pst_tid_queue->st_hdr.pst_next;
        if (OAL_PTR_NULL == pst_entry)
        {
            continue;
        }

        while (pst_entry != &pst_tid_queue->st_hdr)
        {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_entry, hal_tx_dscr_stru, st_entry);

            pst_entry = pst_entry->pst_next;

            oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
            pst_mac_device->us_total_mpdu_num--;
            pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
            dmac_free_tx_dscr(pst_tx_dscr);
        }
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        pst_tid_queue->us_mpdu_num = 0;
        pst_tid_queue->uc_retry_num = 0;

        /* �ͷ�BA��ص����� */
        if (OAL_PTR_NULL != pst_tid_queue->pst_ba_rx_hdl)
        {
            //dmac_mgmt_delba(pst_dmac_vap, pst_dmac_user, (oal_uint8)ul_tid_idx, MAC_RECIPIENT_DELBA, MAC_QSTA_LEAVING_NETWORK);
            dmac_ba_reset_rx_handle(pst_mac_device, &(pst_tid_queue->pst_ba_rx_hdl),(oal_uint8)ul_tid_idx, pst_dmac_user);
        }

        if (OAL_PTR_NULL != pst_tid_queue->pst_ba_tx_hdl)
        {
            //dmac_mgmt_delba(pst_dmac_vap, pst_dmac_user, (oal_uint8)ul_tid_idx, MAC_ORIGINATOR_DELBA, MAC_QSTA_LEAVING_NETWORK);
            dmac_ba_reset_tx_handle(pst_mac_device, &(pst_tid_queue->pst_ba_tx_hdl), (oal_uint8)ul_tid_idx);
        }

    }
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    pst_vap = mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    dmac_alg_flowctl_backp_notify(pst_vap, pst_mac_device->us_total_mpdu_num, pst_mac_device->aus_ac_mpdu_num);
#endif

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_DFT_EVENT
/*****************************************************************************
 �� �� ��  : dmac_event_pause_tid
 ��������  : ��ͣ���߻ָ�tid�¼���Ϣ�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��4��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tid_status_change_event_to_sdt(
                                     dmac_tid_stru        *pst_tid,
                                     oal_uint8             uc_is_tid_paused)
{
    oal_uint8       auc_event[50] = {0};

    auc_event[0] = uc_is_tid_paused;

    DMAC_EVENT_PAUSE_OR_RESUME_TID(BROADCAST_MACADDR,
                                   pst_tid->uc_vap_id,
                                   OAM_EVENT_PAUSE_OR_RESUME_TID,
                                   auc_event);

}
#endif

/*****************************************************************************
 �� �� ��  : dmac_tid_pause
 ��������  : ��ͣTID����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_pause(dmac_tid_stru *pst_tid, oal_uint8 uc_type)
{
    oal_uint8   uc_is_paused;

    if (OAL_PTR_NULL == pst_tid)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_is_paused = pst_tid->uc_is_paused;

    if (DMAC_TID_PAUSE_RESUME_TYPE_BA == uc_type)
    {
        pst_tid->uc_is_paused |= BIT0;
    }
    else if (DMAC_TID_PAUSE_RESUME_TYPE_PS == uc_type)
    {
        pst_tid->uc_is_paused |= BIT1;
    }

    if (0 == uc_is_paused)
    {
        /* ֪ͨ�㷨 */
        dmac_alg_tid_update_notify(pst_tid);
    }

#ifdef _PRE_WLAN_DFT_EVENT
    dmac_tid_status_change_event_to_sdt(pst_tid, pst_tid->uc_is_paused);
#endif

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_tid_resume
 ��������  : �ָ�TID����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tid_resume(hal_to_dmac_device_stru *pst_hal_device, dmac_tid_stru *pst_tid, oal_uint8 uc_type)
{
    if ((OAL_PTR_NULL == pst_tid) || (OAL_PTR_NULL == pst_hal_device))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (DMAC_TID_PAUSE_RESUME_TYPE_BA == uc_type)
    {
        pst_tid->uc_is_paused &= ~BIT0;
    }
    else if (DMAC_TID_PAUSE_RESUME_TYPE_PS == uc_type)
    {
        pst_tid->uc_is_paused &= ~BIT1;
    }

    if (0 == pst_tid->uc_is_paused)
    {
#ifdef _PRE_WLAN_DFT_EVENT
        dmac_tid_status_change_event_to_sdt(pst_tid, pst_tid->uc_is_paused);
#endif
        /* ֪ͨ�㷨 */
        dmac_alg_tid_update_notify(pst_tid);
        dmac_tx_complete_schedule(pst_hal_device, WLAN_WME_TID_TO_AC(pst_tid->uc_tid));
    }

    return OAL_SUCC;
}


/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_tid_get_util_ratio);
oal_module_symbol(dmac_tid_get_mpdu_by_index);
oal_module_symbol(dmac_tid_get_min_max_mpdu_length);
oal_module_symbol(dmac_tid_delete_mpdu_tail);
oal_module_symbol(dmac_tid_delete_mpdu_head);
oal_module_symbol(dmac_tid_get_normal_rate_stats);
oal_module_symbol(dmac_tid_set_normal_rate_stats);
oal_module_symbol(dmac_tid_tx_queue_init);
oal_module_symbol(dmac_tid_resume);
oal_module_symbol(dmac_tid_pause);
/*lint +e578*//*lint +e19*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

