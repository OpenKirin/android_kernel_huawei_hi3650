/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_tcp_opt.c
  �� �� ��   : ����
  ��    ��   : zengjun
  ��������   : 2015��5��16��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��16��
    ��    ��   : zengjun
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_TCP_OPT

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*lint -e322*/
#include <linux/jiffies.h>
/*lint +e322*/
#endif
#include "oam_ext_if.h"
#include "hmac_tcp_opt_struc.h"
#include "oal_hcc_host_if.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_tcp_opt.h"
#include "mac_data.h"
#include "oal_net.h"
#include "oal_types.h"
#include "hmac_rx_data.h"
#include "frw_event_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TCP_OPT_C

/*****************************************************************************
  2 �ṹ�嶨��
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*defined for ut test*/
#if defined(WIN32)
oal_uint32 jiffies;

oal_bool_enum_uint8 time_before_eq(oal_uint32 a,oal_uint32 b)
{
    return OAL_TRUE;
}
#endif

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 �ڲ���̬��������
*****************************************************************************/

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_ack_count_reset
 ��������  : ��λTCP ACK��ͳ��ֵ
 �������  : struct hcc_handler *hcc
             hcc_chan_type dir
             oal_uint16 stream
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
void hmac_tcp_opt_ack_count_reset(hmac_vap_stru    *pst_hmac_vap,hcc_chan_type dir, oal_uint16 stream)
{
    OAL_BUG_ON(!pst_hmac_vap);
    oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hmac_tcp_ack_lock);
    pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[stream] = 0;
    pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_duplicate_ack_count[stream] = 0;
    oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hmac_tcp_ack_lock);
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_ack_all_count_reset
 ��������  : ��λ����TCP ACK��ͳ��ֵ
 �������  : struct hcc_handler *hcc
             hcc_chan_type dir
             oal_uint16 stream
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
void hmac_tcp_opt_ack_all_count_reset(hmac_vap_stru    *pst_hmac_vap)
{
    oal_uint16     us_dir_index = 0;
    oal_uint16     us_tcp_index = HCC_TX;

    for(us_tcp_index = 0; us_tcp_index < HMAC_TCP_STREAM; us_tcp_index++)
    {
        hmac_tcp_opt_ack_count_reset(pst_hmac_vap,(hcc_chan_type)us_dir_index, us_tcp_index);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_ack_show_count
 ��������  : ��λ����TCP ACK��ͳ��ֵ
 �������  : struct hcc_handler *hcc
             hcc_chan_type dir
             oal_uint16 stream
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
void hmac_tcp_opt_ack_show_count(hmac_vap_stru    *pst_hmac_vap)
{
    oal_uint16     us_dir_index = 0;
    oal_uint16     us_tcp_index = HCC_TX;

    for(us_dir_index = 0; us_dir_index < HCC_DIR_COUNT; us_dir_index++)
    {
        for(us_tcp_index = 0; us_tcp_index < HMAC_TCP_OPT_QUEUE_BUTT; us_tcp_index++)
        {
            oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack.hmac_tcp_ack_lock);
            OAL_IO_PRINT("dir = %u,tcp_index = %u,all_ack_count = %llu,drop_count = %llu\n",
                us_dir_index,
                us_tcp_index,
                pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].all_ack_count[us_tcp_index],
                pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].drop_count[us_tcp_index]);

            pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].all_ack_count[us_tcp_index] = 0;
            pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].drop_count[us_tcp_index] = 0;
            oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack.hmac_tcp_ack_lock);
        }
    }
}
/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_find_oldest_node
 ��������  : ����ʱ����ɵ�node
 �������  : struct hcc_handler *hcc
             hcc_chan_type dir
 �������  : ��
 �� �� ֵ  : struct tcp_list_node *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
struct tcp_list_node *hmac_tcp_opt_find_oldest_node(hmac_vap_stru    *pst_hmac_vap, hcc_chan_type dir)
{
    struct tcp_list_node *node;
    struct tcp_list_node *oldest_node = NULL;
    oal_uint  oldest_time = jiffies;  /*init current time*/
    struct wlan_perform_tcp_list *tmp_list;
    oal_dlist_head_stru        *pst_entry;

    tmp_list = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack_list;
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &tmp_list->tcp_list)
    {
        node = OAL_DLIST_GET_ENTRY(pst_entry, struct tcp_list_node, list);
        if (OAL_TRUE == time_before_eq(node->ul_last_ts, oldest_time))
        {
            oldest_time = node->ul_last_ts;
            oldest_node = node;
            OAM_INFO_LOG3(0,OAM_SF_ANY,"{dir:%d find last_ts %ld   oldest_time %ld.}", dir,
                            node->ul_last_ts,
                            oldest_time);
        }
    }
    if (NULL != oldest_node)
    {
        oal_dlist_delete_entry(&oldest_node->list);
        oal_dlist_init_head(&oldest_node->list);
//            list_del_init(&oldest_node->list);
    }
    else
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"can't find oldest node xx");
    return oldest_node;
}
/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_get_buf
 ��������  : get buf for tcp ack
 �������  : struct hcc_handler *hcc
             hcc_chan_type dir
 �������  : ��
 �� �� ֵ  : struct tcp_list_node *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
struct tcp_list_node *hmac_tcp_opt_get_buf(hmac_vap_stru    *pst_hmac_vap, hcc_chan_type dir)
{
    struct tcp_list_node *node = NULL;
    oal_uint16  us_tcp_stream_index;
    struct wlan_perform_tcp_list *tmp_ack_list = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack_list;

    if (0 == tmp_ack_list->ul_free_count)
    {
        node = hmac_tcp_opt_find_oldest_node(pst_hmac_vap,dir);
        return node;
    }

    for (us_tcp_stream_index = 0; us_tcp_stream_index < HMAC_TCP_STREAM; us_tcp_stream_index++)
    {
        if ( 0 == tmp_ack_list->tcp_pool[us_tcp_stream_index].ul_used)
        {
            tmp_ack_list->tcp_pool[us_tcp_stream_index].ul_used = 1;
            tmp_ack_list->ul_free_count--;
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAL_IO_PRINT("\r\n====dir:%d get buf %d free:%d====\r\n}", dir, us_tcp_stream_index, tmp_ack_list->ul_free_count);
#endif
            node = &tmp_ack_list->tcp_pool[us_tcp_stream_index];
            break;
        }
    }
    return node;
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_add_node
 ��������  : add node to ack list
 �������  : struct hcc_handler *hcc
             struct wlan_tcp_flow *tcp_info
             hcc_chan_type dir
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_tcp_opt_add_node(hmac_vap_stru    *pst_hmac_vap, struct wlan_tcp_flow *tcp_info, hcc_chan_type dir)
{
    struct tcp_list_node *node;

    if ((NULL == pst_hmac_vap) || (NULL == tcp_info))
    {
        return OAL_FAIL;
    }

    node = hmac_tcp_opt_get_buf(pst_hmac_vap,dir);

    if (NULL == node)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"Invalid NULL node!");
        return OAL_FAIL;
    }

    node->wlan_tcp_info.ul_dst_ip   = tcp_info->ul_dst_ip;
    node->wlan_tcp_info.ul_src_ip   = tcp_info->ul_src_ip;
    node->wlan_tcp_info.us_src_port = tcp_info->us_src_port;
    node->wlan_tcp_info.us_dst_port = tcp_info->us_dst_port;
    node->wlan_tcp_info.uc_protocol = tcp_info->uc_protocol;
    node->ul_last_ts       = jiffies;

    oal_dlist_add_tail(&node->list, &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack_list.tcp_list);

#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAL_IO_PRINT("\r\n====dir:%d,ul_index = %d,add node succ====\r\n", dir,node->ul_index);
#endif

    return node->ul_index;
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_init_filter_tcp_ack_pool
 ��������  : init tcp ack pool
 �������  : struct hcc_handler* hcc
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_tcp_opt_init_filter_tcp_ack_pool(hmac_vap_stru    *pst_hmac_vap)
{
    oal_uint16     us_dir_index = 0;
    oal_uint16     us_tcp_index;
    oal_uint16     us_tcp_queue_index;

    OAL_BUG_ON(OAL_PTR_NULL == pst_hmac_vap);

    /*init downline tcp ack pool*/

    /*init tx_worker_state*/

    for(us_dir_index = 0; us_dir_index < HCC_DIR_COUNT; us_dir_index++)
    {
        for (us_tcp_index = 0; us_tcp_index < HMAC_TCP_STREAM; us_tcp_index++)
        {
            oal_spin_lock_init(&pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack.hmac_tcp_ack_lock);
            oal_netbuf_list_head_init(&pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack.hcc_ack_queue[us_tcp_index]);
            pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack_list.tcp_pool[us_tcp_index].ul_used = 0;
            pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack_list.tcp_pool[us_tcp_index].ul_index = us_tcp_index;
            pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack_list.tcp_pool[us_tcp_index].ul_last_ts = jiffies;
        }
        for (us_tcp_queue_index = 0; us_tcp_queue_index < HMAC_TCP_OPT_QUEUE_BUTT; us_tcp_queue_index++)
        {
            oal_spin_lock_init(&pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].data_queue_lock[us_tcp_queue_index]);
            oal_netbuf_head_init(&pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].data_queue[us_tcp_queue_index]);
        }
        oal_dlist_init_head(&(pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack_list.tcp_list));
        pst_hmac_vap->st_hamc_tcp_ack[us_dir_index].hmac_tcp_ack_list.ul_free_count = HMAC_TCP_STREAM;
        OAM_INFO_LOG1(0,OAM_SF_ANY,"{wifi tcp perform dir:%d init done.}", us_dir_index);
    }
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].filter[HMAC_TCP_ACK_QUEUE] = hmac_tcp_opt_tx_tcp_ack_filter;
    pst_hmac_vap->st_hamc_tcp_ack[HCC_RX].filter[HMAC_TCP_ACK_QUEUE] = hmac_tcp_opt_rx_tcp_ack_filter;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_free_ack_list
 ��������  : ɾ��vapʱ�ͷ�ack list
 �������  : struct hcc_handler *hcc
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
void hmac_tcp_opt_free_ack_list(hmac_vap_stru *pst_hmac_vap,oal_uint8 dir,oal_uint8 type)
{
#if !defined(WIN32)
    oal_netbuf_head_stru  st_head_t;
    oal_netbuf_head_stru *head;
    oal_netbuf_stru* pst_netbuf;
    oal_netbuf_head_stru* hcc_ack_queue;
    struct wlan_perform_tcp_list *tmp_list;
    oal_dlist_head_stru        *pst_entry;
    oal_dlist_head_stru        *pst_entry_temp;
    struct tcp_list_node       *node;

    oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue_lock[type]);

    oal_netbuf_head_init(&st_head_t);
    head = &pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue[type];
    oal_netbuf_queue_splice_tail_init(head, &st_head_t);
    while(!!(pst_netbuf = oal_netbuf_delist(&st_head_t)))
    {
        oal_netbuf_free(pst_netbuf);
    }

    tmp_list = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack_list;
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry,pst_entry_temp, &tmp_list->tcp_list)
    {
        node = OAL_DLIST_GET_ENTRY(pst_entry, struct tcp_list_node, list);

        if (node->ul_used == 0)
        {
            continue;
        }
        hcc_ack_queue = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hcc_ack_queue[node->ul_index];
        while(!!(pst_netbuf = oal_netbuf_delist(hcc_ack_queue)))
        {
            oal_netbuf_free(pst_netbuf);
        }
    }

    oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue_lock[type]);
#endif
}
/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_deinit_list
 ��������  : deinit tcp ack list
 �������  : struct hcc_handler *hcc
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
void hmac_tcp_opt_deinit_list(hmac_vap_stru *pst_hmac_vap)
{
    hmac_tcp_opt_free_ack_list(pst_hmac_vap,HCC_TX,HMAC_TCP_ACK_QUEUE);
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    hmac_tcp_opt_free_ack_list(pst_hmac_vap,HCC_RX,HMAC_TCP_ACK_QUEUE);
#endif
}


/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_get_flow_index
 ��������  : get follow index for each tcp ack
 �������  : struct hcc_handler     *hcc
             oal_ip_header_stru  *ip_hdr
             oal_tcp_header_stru *tcp_hdr
             hcc_chan_type dir
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_tcp_opt_get_flow_index(hmac_vap_stru    *pst_hmac_vap,
                                             oal_ip_header_stru     *pst_ip_hdr,
                                             oal_tcp_header_stru *pst_tcp_hdr,
                                             hcc_chan_type dir)
{
    struct wlan_tcp_flow   tcp_flow_info;
    struct tcp_list_node  *node;
    oal_dlist_head_stru        *pst_entry;
    struct wlan_perform_tcp_list *tmp_list;


    tcp_flow_info.ul_src_ip   = pst_ip_hdr->ul_saddr;
    tcp_flow_info.ul_dst_ip   = pst_ip_hdr->ul_daddr;
    tcp_flow_info.us_src_port = pst_tcp_hdr->us_sport;
    tcp_flow_info.us_dst_port = pst_tcp_hdr->us_dport;
    tcp_flow_info.uc_protocol = pst_ip_hdr->uc_protocol;


#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAL_IO_PRINT("\r\n====hmac_tcp_opt_get_flow_index enter====\r\n");
#endif
    /* get the queue index of tcp ack */
    tmp_list = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack_list;
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &tmp_list->tcp_list)
    {
        node = (struct tcp_list_node *)pst_entry;
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAL_IO_PRINT("\r\n====dir:%d node [index:%d],ul_used = %d====\r\n",
                        dir,node->ul_index,node->ul_used);
#endif
        if ((node->wlan_tcp_info.ul_src_ip == tcp_flow_info.ul_src_ip)
            && (node->wlan_tcp_info.ul_dst_ip == tcp_flow_info.ul_dst_ip)
           && (node->wlan_tcp_info.us_src_port == tcp_flow_info.us_src_port)
           && (node->wlan_tcp_info.us_dst_port == tcp_flow_info.us_dst_port)
           && (node->wlan_tcp_info.uc_protocol == tcp_flow_info.uc_protocol)
           && (node->ul_used == 1))
        {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAL_IO_PRINT("\r\n====dir:%d find the same tcp flow info [index:%d]====\r\n",
                            dir,node->ul_index);
#endif
            node->ul_last_ts = jiffies; /*renew the last pkt time*/
            return node->ul_index;
        }
    }

    /* new follow, save in new node */

    return hmac_tcp_opt_add_node(pst_hmac_vap, &tcp_flow_info, dir);

}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_get_tcp_ack_type
 ��������  : get follow index for each tcp ack
 �������  : hmac_vap_stru    *pst_hmac_vap
             oal_ip_header_stru     *pst_ip_hdr
             hcc_chan_type dir
             oal_uint16 ul_index
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_tcp_ack_type_enum_uint8 hmac_tcp_opt_get_tcp_ack_type(hmac_vap_stru    *pst_hmac_vap,
                                             oal_ip_header_stru     *pst_ip_hdr,
                                             hcc_chan_type dir,
                                             oal_uint16 us_index)
{
    oal_tcp_header_stru *pst_tcp_hdr;
    oal_uint32 tcp_ack_no;
    oal_uint32 *tmp_tcp_ack_no;

#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAL_IO_PRINT("\r\n====hmac_tcp_opt_get_tcp_ack_type:us_index = %d ====\r\n", us_index);
#endif
    /*lint -e522*/
    OAL_WARN_ON(us_index >= HMAC_TCP_STREAM);
    /*lint +e522*/
    pst_tcp_hdr     = (oal_tcp_header_stru *)(pst_ip_hdr + 1);
    tcp_ack_no = pst_tcp_hdr->ul_acknum;

    /*���duplicat ack�Ƿ���ڣ�����������ۼ�ack������Ա��*/
    tmp_tcp_ack_no = pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_tcp_ack_no;
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAL_IO_PRINT("\r\n====stream:%d ack no:%u  tcp ack no:%u ====\r\n", us_index, tcp_ack_no, tmp_tcp_ack_no[us_index]);
#endif
    if (tcp_ack_no == tmp_tcp_ack_no[us_index])
    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG1(0,OAM_SF_ANY,"{dir:%d:**duplicate ack is coming**.}", dir);
#endif
        pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.st_tcp_info[us_index].ull_dup_ack_count++;
        return TCP_ACK_DUP_TYPE;
    }

    tmp_tcp_ack_no[us_index] = pst_tcp_hdr->ul_acknum;

    /*��ֵtcp_cb*/
    return TCP_ACK_FILTER_TYPE;

}

/*****************************************************************************
 �� �� ��  : hmac_judge_rx_netbuf_is_tcp_ack
 ��������  : �жϽ���֡�Ƿ���TCP_ACK֡
 �������  : mac_llc_snap *pst_snap
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_judge_rx_netbuf_is_tcp_ack(mac_llc_snap_stru *pst_snap)
{
    oal_ip_header_stru  *pst_ip_hdr;
    oal_bool_enum_uint8 en_is_tcp_ack = OAL_FALSE;
    oal_tcp_header_stru    *pst_tcp_hdr;

    if(OAL_PTR_NULL == pst_snap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_judge_rx_netbuf_is_tcp_ack:  pst_snap is null!}");
        return OAL_FALSE;
    }
    switch (pst_snap->us_ether_type)
    {
        /*lint -e778*//* ����Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):

            pst_ip_hdr = (oal_ip_header_stru *)(pst_snap + 1);      /* ƫ��һ��snap��ȡipͷ */

#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAM_WARNING_LOG1(0, OAM_SF_RX, "{oal_judge_rx_netbuf_is_tcp_ack:  pst_ip_hdr->uc_protocol = %d**!}",pst_ip_hdr->uc_protocol);
#endif
            if (MAC_TCP_PROTOCAL == pst_ip_hdr->uc_protocol)
            {
                if (OAL_TRUE == oal_netbuf_is_tcp_ack(pst_ip_hdr))
                {
                    pst_tcp_hdr = (oal_tcp_header_stru *)(pst_ip_hdr + 1);
                    /*option3:SYN FIN RST URG��Ϊ1��ʱ�򲻹���*/
                    if ((pst_tcp_hdr->uc_flags) & FILTER_FLAG_MASK)
                    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
                        OAM_WARNING_LOG0(0, OAM_SF_RX, "{hmac_judge_rx_netbuf_is_tcp_ack:  **specific tcp pkt, can't be filter**!}");
#endif
                    }
                    else
                    {
                        en_is_tcp_ack = OAL_TRUE;
                    }
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
                    OAM_WARNING_LOG0(0, OAM_SF_RX, "{oal_judge_rx_netbuf_is_tcp_ack:: tcp ack frame!}");
#endif
                }
            }
            break;
        /*lint +e778*/
        default:
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAL_IO_PRINT("{oal_judge_rx_netbuf_is_tcp_ack::unkown us_ether_type[%d]}\r\n", pst_snap->us_ether_type);
#endif
            break;
    }

    return en_is_tcp_ack;
}

/*****************************************************************************
 �� �� ��  : hmac_judge_rx_netbuf_classify
 ��������  : ����֡���з���
 �������  : oal_netbuf_stru* netbuf
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_judge_rx_netbuf_classify(oal_netbuf_stru *pst_netbuff)
{
    mac_llc_snap_stru             *pst_snap;

    pst_snap = (mac_llc_snap_stru *)(pst_netbuff);
    if(OAL_PTR_NULL == pst_snap)
    {
        return OAL_FALSE;
    }
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAM_WARNING_LOG1(0,OAM_SF_ANY,"**hmac_judge_rx_netbuf_classify, us_ether_type = %d**",pst_snap->us_ether_type);
#endif
    return hmac_judge_rx_netbuf_is_tcp_ack(pst_snap);
}


/*****************************************************************************
 �� �� ��  : hmac_judge_tx_netbuf_is_tcp_ack
 ��������  : �жϽ���֡�Ƿ���TCP_ACK֡
 �������  : oal_ether_header_stru *ps_ethmac_hdr
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_judge_tx_netbuf_is_tcp_ack(oal_ether_header_stru *ps_ethmac_hdr)
{
    oal_ip_header_stru     *pst_ip;
    oal_tcp_header_stru    *pst_tcp_hdr;
    oal_bool_enum_uint8     en_is_tcp_ack = OAL_FALSE;


    if(OAL_PTR_NULL == ps_ethmac_hdr)
    {
        return OAL_FALSE;
    }
    switch (ps_ethmac_hdr->us_ether_type)
    {
        /*lint -e778*//* ����Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):

            pst_ip = (oal_ip_header_stru *)(ps_ethmac_hdr + 1);      /* ƫ��һ��snap��ȡipͷ */

            if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol)
            {

                if (OAL_TRUE == oal_netbuf_is_tcp_ack(pst_ip))
                {
                    pst_tcp_hdr = (oal_tcp_header_stru *)(pst_ip + 1);
                    /*option3:SYN FIN RST URG��Ϊ1��ʱ�򲻹���*/
                    if ((pst_tcp_hdr->uc_flags) & FILTER_FLAG_MASK)
                    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
                        OAM_WARNING_LOG0(0,OAM_SF_ANY,"**specific tcp pkt, can't be filter**");
#endif
                    }
                    else
                    {
                        en_is_tcp_ack = OAL_TRUE;
                    }
                }
            }
            break;

        /*lint +e778*/
        default:
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAL_IO_PRINT("{oal_netbuf_select_queue::unkown us_ether_type[%d]}\r\n", ps_ethmac_hdr->us_ether_type);
#endif
            break;
    }

    return en_is_tcp_ack;
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_get_tcp_ack
 ��������  : get tcp ack from the skb data
 �������  : struct oal_netbuf_stru *skb
             struct hcc_handler *hcc
             oal_uint16 *p_us_index
             uint8 dir
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

******************************************************************************/
oal_tcp_ack_type_enum_uint8  hmac_tcp_opt_rx_get_tcp_ack(oal_netbuf_stru *skb, hmac_vap_stru    *pst_hmac_vap, oal_uint16 *p_us_index, oal_uint8 dir)
{
    oal_ip_header_stru  *pst_ip_hdr;
    oal_tcp_header_stru *pst_tcp_hdr;
    mac_llc_snap_stru             *pst_snap;
    hmac_rx_ctl_stru                   *pst_rx_ctrl;                        /* ָ��MPDU���ƿ���Ϣ��ָ�� */

    pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(skb);
    pst_snap = (mac_llc_snap_stru*)(skb->data + pst_rx_ctrl->st_rx_info.uc_mac_header_len);

    if(OAL_FALSE == hmac_judge_rx_netbuf_is_tcp_ack(pst_snap))
    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        /* not tcp ack data */
        OAM_INFO_LOG0(0,OAM_SF_ANY,"{**not tcp packet return direct**}\r\n");
#endif
        return TCP_TYPE_ERROR;
    }
    pst_ip_hdr = (oal_ip_header_stru *)(pst_snap + 1);      /* ƫ��һ��snap��ȡipͷ */
    pst_tcp_hdr     = (oal_tcp_header_stru *)(pst_ip_hdr + 1);

    /*option4:flow indexȡ����ʱ������*/
    *p_us_index = (oal_uint16)hmac_tcp_opt_get_flow_index(pst_hmac_vap, pst_ip_hdr, pst_tcp_hdr, (hcc_chan_type)dir);
    if(0xFFFF == *p_us_index)
    {
        return TCP_TYPE_ERROR;
    }

    return hmac_tcp_opt_get_tcp_ack_type(pst_hmac_vap,pst_ip_hdr,(hcc_chan_type)dir,*p_us_index);

}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_tx_get_tcp_ack
 ��������  : get tcp ack from the skb data
 �������  : struct oal_netbuf_stru *skb
             struct hcc_handler *hcc
             oal_uint16*p_us_index
             uint8 dir
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_tcp_ack_type_enum_uint8  hmac_tcp_opt_tx_get_tcp_ack(oal_netbuf_stru *skb, hmac_vap_stru    *pst_hmac_vap, oal_uint16 *p_us_index, oal_uint8 dir)
{
    oal_ip_header_stru  *pst_ip_hdr;
    oal_tcp_header_stru *pst_tcp_hdr;
    oal_ether_header_stru *eth_hdr;

    eth_hdr = (oal_ether_header_stru *)oal_netbuf_data(skb);
    if(OAL_FALSE == hmac_judge_tx_netbuf_is_tcp_ack(eth_hdr))
    {
        /* not tcp ack data */
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAL_IO_PRINT("\r\n====**not tcp packet return direct**====\r\n");
#endif
        return TCP_TYPE_ERROR;
    }
    pst_ip_hdr = (oal_ip_header_stru *)(eth_hdr + 1);      /* ƫ��һ��snap��ȡipͷ */
    pst_tcp_hdr     = (oal_tcp_header_stru *)(pst_ip_hdr + 1);
    /*option4:flow indexȡ����ʱ������*/
    *p_us_index = (oal_uint16)hmac_tcp_opt_get_flow_index(pst_hmac_vap, pst_ip_hdr, pst_tcp_hdr, (hcc_chan_type)dir);
    if(0xFFFF == *p_us_index)
    {
        return TCP_TYPE_ERROR;
    }

    return hmac_tcp_opt_get_tcp_ack_type(pst_hmac_vap,pst_ip_hdr,(hcc_chan_type)dir,*p_us_index);

}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_tcp_ack_list_filter
 ��������  : TCP ACK���˺���
 �������  : struct hcc_handler* hcc
             hmac_tcp_opt_queue type
             hcc_chan_type dir
             oal_netbuf_head_stru  *head
 �������  : ��
 �� �� ֵ  : oal_uint16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16 hmac_tcp_opt_tcp_ack_list_filter(hmac_vap_stru    *pst_hmac_vap, hmac_tcp_opt_queue type,hcc_chan_type dir, oal_netbuf_head_stru  *head)
{
    struct tcp_list_node *node;
    oal_netbuf_stru * skb;
    oal_netbuf_head_stru  head_t;
    struct wlan_perform_tcp_list *tmp_list;
    oal_dlist_head_stru        *pst_entry;
    oal_dlist_head_stru        *pst_entry_temp;

    OAL_BUG_ON(!pst_hmac_vap);
    if(!oal_netbuf_list_len(head))
    {
        return 0;
    }
    oal_netbuf_head_init(&head_t);

#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAL_IO_PRINT("\r\n====hmac_tcp_opt_tcp_ack_list_filter:uc_vap_id = %d,dir=%d filter queue qlen %u====\r\n",pst_hmac_vap->st_vap_base_info.uc_vap_id, dir, oal_netbuf_list_len(head));
#endif
    while(!!(skb = oal_netbuf_delist(head)))
    {
        if(hmac_tcp_opt_tcp_ack_filter(skb, pst_hmac_vap, dir))
        {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAL_IO_PRINT("\r\n====not found tcp ack...====\r\n");
#endif
            oal_netbuf_list_tail(&head_t,skb);
        }
        else
        {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAL_IO_PRINT("\r\n====found tcp ack...====\r\n");
#endif
        }
    }
    /*lint -e522*/
    OAL_WARN_ON(!oal_netbuf_list_empty(head));
    /*lint +e522*/
    oal_netbuf_splice_init(&head_t, head);
    pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.ull_ignored_count +=
                oal_netbuf_list_len(head);

    tmp_list = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack_list;
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry,pst_entry_temp, &tmp_list->tcp_list)
    {
        oal_netbuf_head_stru* hcc_ack_queue;

        node = OAL_DLIST_GET_ENTRY(pst_entry, struct tcp_list_node, list);
        OAM_INFO_LOG1(0,OAM_SF_ANY,"{dir:%d --begin to recv packet--.}", dir);
        if (node->ul_used == 0)
        {
            continue;
        }
        hcc_ack_queue = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hcc_ack_queue[node->ul_index];

#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAL_IO_PRINT("\r\n====dir:%d ------recv packet------[qlen:%u].====\r\n", dir,
                    oal_netbuf_list_len(hcc_ack_queue));
#endif
        hmac_tcp_opt_ack_count_reset(pst_hmac_vap, (hcc_chan_type)dir, (oal_uint16)node->ul_index);
        pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.st_tcp_info[node->ul_index].ull_send_count +=
                oal_netbuf_list_len(hcc_ack_queue);

        oal_netbuf_queue_splice_tail_init(hcc_ack_queue, head);

        /* ��������֡������������ɾ�� */
        /* ��Ϊǰ����dup ack�Ѿ������ͣ��Ա�֤ʶ�������duplicate ack����Ҫ��¼duplicate ack seqnum */
#if 0
        oal_dlist_delete_entry(&node->list);
        oal_dlist_init_head(&node->list);

        hmac_tcp_opt_free_buf(pst_hmac_vap, node, dir);
#endif
    }
    return 0;
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_rx_tcp_ack_filter
 ��������  : ����TCP ACK���˺���
 �������  : struct hcc_handler* hcc
             hmac_tcp_opt_queue type
             hcc_chan_type dir
             void* data
 �������  : ��
 �� �� ֵ  : oal_uint16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16 hmac_tcp_opt_rx_tcp_ack_filter(void *hmac_vap, hmac_tcp_opt_queue type,hcc_chan_type dir, void* data)
{
    hmac_vap_stru    *pst_hmac_vap;
    hmac_device_stru    *pst_hmac_device;
    oal_netbuf_head_stru  *head = (oal_netbuf_head_stru  *)data;
    OAL_BUG_ON(!hmac_vap);
    OAL_BUG_ON(!data);
    OAL_BUG_ON(HMAC_TCP_ACK_QUEUE != type);
    OAL_BUG_ON(HCC_RX != dir);

    pst_hmac_vap = (hmac_vap_stru *)hmac_vap;

    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
            "{hmac_tcp_opt_rx_tcp_ack_filter fail: pst_hmac_device is null}\r\n");
        return OAL_FAIL;
    }

    if(!pst_hmac_device->sys_tcp_rx_ack_opt_enable)
    {
        return 0;
    }
    return hmac_tcp_opt_tcp_ack_list_filter(pst_hmac_vap, type, dir, head);
}

/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_tx_tcp_ack_filter
 ��������  : ����TCP ACK���˺���
 �������  : struct hcc_handler* hcc
             hmac_tcp_opt_queue type
             hcc_chan_type dir
             void* data
 �������  : ��
 �� �� ֵ  : oal_uint16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16 hmac_tcp_opt_tx_tcp_ack_filter(void *hmac_device, hmac_tcp_opt_queue type,hcc_chan_type dir, void* data)
{
    hmac_vap_stru    *pst_hmac_vap;
    hmac_device_stru    *pst_hmac_device;
    oal_netbuf_head_stru  *head = (oal_netbuf_head_stru  *)data;
    OAL_BUG_ON(!hmac_device);
    OAL_BUG_ON(!data);
    OAL_BUG_ON(HMAC_TCP_ACK_QUEUE != type);
    OAL_BUG_ON(HCC_TX != dir);
    pst_hmac_vap = (hmac_vap_stru *)hmac_device;

    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
            "{hmac_tcp_opt_tx_tcp_ack_filter fail: pst_hmac_device is null}\r\n");
        return OAL_FAIL;
    }

    if(!pst_hmac_device->sys_tcp_tx_ack_opt_enable)
    {
        return 0;
    }
    return hmac_tcp_opt_tcp_ack_list_filter(pst_hmac_vap, type, dir, head);
}


/*****************************************************************************
 �� �� ��  : hmac_tcp_opt_tcp_ack_filter
 ��������  : save it to tcp ack queue
 �������  : struct oal_netbuf_stru *skb
             struct hcc_handler *hcc
             hcc_chan_type dir
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_tcp_opt_tcp_ack_filter(oal_netbuf_stru *skb, hmac_vap_stru    *pst_hmac_vap, hcc_chan_type dir)
{

    oal_tcp_ack_type_enum_uint8 uc_ret;
    oal_uint16 us_tcp_stream_index;
    oal_uint32 ul_ack_limit;
    oal_netbuf_head_stru* hcc_ack_queue;
    oal_netbuf_stru     *ack          = NULL;
    oal_uint32 ul_ret;

    if(HCC_TX == dir)
    {
        uc_ret = hmac_tcp_opt_tx_get_tcp_ack(skb, pst_hmac_vap, &us_tcp_stream_index, dir);
    }
    else
    {
        uc_ret = hmac_tcp_opt_rx_get_tcp_ack(skb, pst_hmac_vap, &us_tcp_stream_index, dir);
    }

    if (uc_ret == TCP_ACK_DUP_TYPE)
    {
        /* ������dup ack */
        oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hmac_tcp_ack_lock);
        hcc_ack_queue = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hcc_ack_queue[us_tcp_stream_index];
        /* ��dup ack֡�������е�֡ȫ������ */
        while (!!(ack = oal_netbuf_delist(hcc_ack_queue)))
        {
            ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt(&(pst_hmac_vap->st_vap_base_info), ack);
            /* ����ʧ�ܣ�Ҫ�ͷ��ں������netbuff�ڴ�� */
            if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
            {
                oal_netbuf_free(ack);
            }
            else
            {
                pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.st_tcp_info[us_tcp_stream_index].ull_send_count++;
            }

            pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[us_tcp_stream_index]--;
        }
        /* ��ǰdup ack֡���� */
        ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt(&(pst_hmac_vap->st_vap_base_info), skb);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            oal_netbuf_free(skb);
        }
        else
        {
            pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.st_tcp_info[us_tcp_stream_index].ull_send_count++;
        }

        oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hmac_tcp_ack_lock);

        return OAL_SUCC;
    }
    else if(uc_ret == TCP_TYPE_ERROR)
    {
        /* �쳣�߼�����֡����vap queue���� */
        return OAL_FAIL;
    }

    /* ����ack֡�����߼� */
    oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hmac_tcp_ack_lock);
    ul_ack_limit = pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.ul_ack_limit;
    hcc_ack_queue = &pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hcc_ack_queue[us_tcp_stream_index];


    /*if normal ack received, del until ack_limit ack left*/
    while (pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[us_tcp_stream_index] >= ul_ack_limit)
    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG4(0,OAM_SF_ANY,"dir:%d:stream:%d : ack count:%u, qlen:%u", dir, us_tcp_stream_index,
            pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[us_tcp_stream_index],
        oal_netbuf_list_len(hcc_ack_queue));
#endif
        ack = oal_netbuf_delist(hcc_ack_queue);
        if (OAL_PTR_NULL == ack)
        {
            break;
        }
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG1(0,OAM_SF_ANY,"{dir:%d ------drop packet------.}", dir);
#endif
        pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.st_tcp_info[us_tcp_stream_index].ull_drop_count++;
        /*hcc_trans_pkt_count_dec(hcc,dir);*/   /*���TCP ACK������������������Լ�*/
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG4(0,OAM_SF_ANY,"{dir:%d: ack count:%d , dupcount:%d ull_drop_count:%d.}", dir,
                        pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[us_tcp_stream_index],
                        pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_duplicate_ack_count[us_tcp_stream_index],
                        pst_hmac_vap->st_hamc_tcp_ack[dir].filter_info.st_tcp_info[us_tcp_stream_index].ull_drop_count);
#endif
        oal_netbuf_free_any(ack);
        pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[us_tcp_stream_index]--;
    }
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
    OAM_WARNING_LOG3(0,OAM_SF_ANY,"{dir:%d: stream:%d qlen:%u.}", dir,
                us_tcp_stream_index, oal_netbuf_list_len(hcc_ack_queue));
#endif

    oal_netbuf_add_to_list_tail(skb,hcc_ack_queue);
    pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.aul_hcc_ack_count[us_tcp_stream_index]++;
    oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].hmac_tcp_ack.hmac_tcp_ack_lock);

    return OAL_SUCC;
}
void hmac_trans_queue_filter(hmac_vap_stru    *pst_hmac_vap, oal_netbuf_head_stru  *head_t,
                                    hmac_tcp_opt_queue type, hcc_chan_type dir)
{
    oal_uint32 old_len, new_len;

    if(pst_hmac_vap->st_hamc_tcp_ack[dir].filter[type])
    {
        old_len = oal_netbuf_list_len(head_t);
        pst_hmac_vap->st_hamc_tcp_ack[dir].filter[type](pst_hmac_vap, type, dir, head_t);
        new_len = oal_netbuf_list_len(head_t);
        pst_hmac_vap->st_hamc_tcp_ack[dir].all_ack_count[type] += old_len;
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAL_IO_PRINT("\r\n====hmac_trans_queue_filter[Queue:%d]Before filter len:%u,After filter len:%u====\r\n",type,old_len, new_len);
#endif
        if(OAL_UNLIKELY(new_len > old_len))
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX,"The filter len:%u is more than before filter:%u",
                new_len, old_len);
        }else
        {
            pst_hmac_vap->st_hamc_tcp_ack[dir].drop_count[type] += (old_len - new_len);
        }
    }
}
void hmac_tcp_ack_process_hcc_queue(hmac_vap_stru    *pst_hmac_vap,
                                    hcc_chan_type dir,hmac_tcp_opt_queue type)
{
    oal_netbuf_head_stru  st_head_t;
    oal_netbuf_head_stru *head;
    oal_netbuf_stru* pst_netbuf;
    oal_uint32 ul_ret;

    oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue_lock[type]);
    if(OAL_PTR_NULL != pst_hmac_vap->st_hamc_tcp_ack[dir].filter[type])
    {
        oal_netbuf_head_init(&st_head_t);
        head = &pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue[type];
        oal_netbuf_queue_splice_tail_init(head, &st_head_t);
        hmac_trans_queue_filter(pst_hmac_vap, &st_head_t, type, dir);
        oal_netbuf_splice_init(&st_head_t,head);
    }
    if(HCC_RX == dir)
    {
        oal_netbuf_head_init(&st_head_t);
        head = &pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue[type];
        oal_netbuf_queue_splice_tail_init(head, &st_head_t);
        if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
        {
            hmac_rx_process_data_ap_tcp_ack_opt(pst_hmac_vap,&st_head_t);
        }
        else if (WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
        {
            hmac_rx_process_data_sta_tcp_ack_opt(pst_hmac_vap,&st_head_t);
        }
    }
    else
    {
        oal_netbuf_head_init(&st_head_t);
        head = &pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue[type];
        oal_netbuf_queue_splice_tail_init(head, &st_head_t);
        while(!!(pst_netbuf = oal_netbuf_delist(&st_head_t)))
        {
            ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt(&(pst_hmac_vap->st_vap_base_info),pst_netbuf);
            /* ����ʧ�ܣ�Ҫ�ͷ��ں������netbuff�ڴ�� */
            if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
            {
                //hmac_free_netbuf_list(pst_buf);
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
                OAL_IO_PRINT("\r\n====hmac_tcp_ack_process_hcc_queue send fail:uc_vap_id = %d====\r\n",pst_hmac_vap->st_vap_base_info.uc_vap_id);
#endif
                oal_netbuf_free(pst_netbuf);
            }
        }
    }
    oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[dir].data_queue_lock[type]);
}
oal_int32 hmac_tcp_ack_process(void)
{
    oal_uint8 uc_vap_idx;
    hmac_vap_stru* pst_hmac_vap;

    hmac_device_stru    *pst_hmac_device;

    if(!oal_in_interrupt())
        frw_event_task_lock();

    pst_hmac_device = hmac_res_get_mac_dev(0);//��ǰֻ֧��һ��device�����������������
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tcp_ack_process::pst_hmac_device[0] null.}");
    }
    else
    {
        if((OAL_TRUE == pst_hmac_device->sys_tcp_rx_ack_opt_enable) || (OAL_TRUE == pst_hmac_device->sys_tcp_tx_ack_opt_enable))
        {
            for (uc_vap_idx = 0; uc_vap_idx < pst_hmac_device->pst_device_base_info->uc_vap_num; uc_vap_idx++)
            {
                pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_hmac_device->pst_device_base_info->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_hmac_vap)
                {
                    OAM_ERROR_LOG0(uc_vap_idx, OAM_SF_ANY, "{hmac_config_add_vap::pst_hmac_vap null.}");
                    continue;
                }
                if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state) &&
                    (MAC_VAP_STATE_PAUSE != pst_hmac_vap->st_vap_base_info.en_vap_state))
                {
                    continue;
                }
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
                 hmac_tcp_ack_process_hcc_queue(pst_hmac_vap,HCC_TX,HMAC_TCP_ACK_QUEUE);
#endif
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
                 hmac_tcp_ack_process_hcc_queue(pst_hmac_vap,HCC_RX,HMAC_TCP_ACK_QUEUE);
#endif
            }

        }
    }

    if(!oal_in_interrupt())
        frw_event_task_unlock();
    return 0;
}
oal_bool_enum_uint8 hmac_tcp_ack_need_schedule(void)
{
    oal_uint8 uc_vap_idx;
    hmac_vap_stru* pst_hmac_vap;
    oal_netbuf_head_stru *head;
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_FALSE;
    }

    /* �����������֡������Ե��� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_ERROR_LOG0(uc_vap_idx, OAM_SF_ANY, "{hmac_tcp_ack_need_schedule::pst_hmac_vap null.}");
            continue;
        }

        if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state) &&
            (MAC_VAP_STATE_PAUSE != pst_hmac_vap->st_vap_base_info.en_vap_state))
        {
            continue;
        }

        oal_spin_lock_bh(&pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
        head = &pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue[HMAC_TCP_ACK_QUEUE];
        /* ��������ack֡������Ҫ�����߳� */
        if(0 < oal_netbuf_list_len(head))
        {
            oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            return OAL_TRUE;
        }
        oal_spin_unlock_bh(&pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);

        /* ���շ���δʹ�ܣ������ж� */

    }

    return OAL_FALSE;
}


oal_void hmac_sched_transfer(void)
{
    struct hcc_handler * hcc;

    hcc = hcc_get_default_handler();
    OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&hcc->hcc_transer_info.hcc_transfer_wq);
}
oal_int32 hmac_set_hmac_tcp_ack_process_func(hmac_tcp_ack_process_func p_func)
{
    struct hcc_handler* hcc;

    hcc = hcc_get_default_handler();
    if (OAL_PTR_NULL == hcc)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_set_hmac_tcp_ack_process_func::hcc null.}");
    }
    else
    {
        hcc->p_hmac_tcp_ack_process_func = p_func;
    }
    return OAL_SUCC;
}
oal_int32 hmac_set_hmac_tcp_ack_need_schedule(hmac_tcp_ack_need_schedule_func p_func)
{
    struct hcc_handler* hcc;

    hcc = hcc_get_default_handler();
    if (OAL_PTR_NULL == hcc)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_set_hmac_tcp_ack_process_func::hcc null.}");
    }
    else
    {
        hcc->p_hmac_tcp_ack_need_schedule_func = p_func;
    }
    return OAL_SUCC;
}


#endif   /* end of _PRE_WLAN_TCP_OPT */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

