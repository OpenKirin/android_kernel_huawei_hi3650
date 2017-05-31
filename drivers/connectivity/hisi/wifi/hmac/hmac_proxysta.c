/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hal_proxysta.c
  �� �� ��   : ����
  ��    ��   : gaolin g00196511
  ��������   : 2016��3��15��
  ����޸�   :
  ��������   : Proxy STA ����������غ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��3��15��
    ��    ��   : gaolin g00196511
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
#include "wlan_spec.h"
#include "mac_vap.h"
#include "mac_frame.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "hmac_device.h"
#include "hmac_vap.h"
#include "hmac_resource.h"
#include "hmac_proxysta.h"
#include "hmac_fsm.h"
#include "hmac_chan_mgmt.h"
#include "hmac_mgmt_ap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_PROXYSTA_C

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/* repeater mgr struct */
OAL_STATIC hmac_psta_mgr_stru  g_st_psta_mgr;
#if  (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*****************************************************************************
 �� �� ��  : hmac_psta_fdb_change_handler
 ��������  : handler of fdb changing
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��18��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_void  hmac_psta_fdb_change_handler(struct br_fdb_change_info *info)
{
    vamp_nlc_msg_stru  st_rsp;

    oal_memcopy(st_rsp.auc_payload, info, OAL_SIZEOF(struct br_fdb_change_info));
    st_rsp.en_type = VAMP_RESP_TYPE_FDB_CHANGE;
    st_rsp.uc_size = OAL_SIZEOF(struct br_fdb_change_info) + 2; // header size=2

    oam_netlink_kernel_send((oal_uint8 *)&st_rsp, st_rsp.uc_size, OAM_NL_CMD_PSTA);
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_psta_receive_msg
 ��������  : recv msg from app_vamp
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��18��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  hmac_psta_receive_msg(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    // TODO
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_find_net_dev
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_psta_find_net_dev(hmac_psta_rep_stru       *pst_dev_psta,
                                                 oal_uint8                *puc_mac_addr,
                                                 oal_net_device_stru     **ppst_net_device)
{
    oal_uint8              uc_hash_value;
    hmac_vap_stru         *pst_hmac_vap;
    oal_dlist_head_stru   *pst_entry;

    uc_hash_value = MAC_PROXYSTA_CALCULATE_HASH_VALUE(puc_mac_addr);
    oal_rw_lock_read_lock(&pst_dev_psta->st_lock);
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &pst_dev_psta->ast_hash[uc_hash_value])
    {
        pst_hmac_vap = OAL_DLIST_GET_ENTRY(pst_entry, hmac_vap_stru, st_psta.st_hash_entry);
        if (0 == oal_compare_mac_addr(hmac_vap_psta_oma(pst_hmac_vap), puc_mac_addr))
        {
            if (OAL_PTR_NULL == pst_hmac_vap->pst_net_device)
            {
                oal_rw_lock_read_unlock(&pst_dev_psta->st_lock);
                return OAL_FAIL;
            }

            *ppst_net_device = pst_hmac_vap->pst_net_device;
            oal_rw_lock_read_unlock(&pst_dev_psta->st_lock);

            return OAL_SUCC;
        }
    }
    oal_rw_lock_read_unlock(&pst_dev_psta->st_lock);

    return OAL_FAIL;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_tx_process
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_psta_tx_process(oal_netbuf_stru *pst_buf, mac_vap_stru **ppst_vap)
{
    mac_ether_header_stru  *pst_ether_header;
    hmac_vap_stru          *pst_hmac_vap;
    oal_net_device_stru    *pst_net_device = OAL_PTR_NULL;

    if (OAL_UNLIKELY(!ppst_vap || !*ppst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_psta_tx_process::null ptr}");
        return OAL_FAIL;
    }

    pst_hmac_vap = mac_res_get_hmac_vap((*ppst_vap)->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{hmac_psta_tx_process::pst_hmac_vap[%d] = OAL_PTR_NULL!}", (*ppst_vap)->uc_vap_id);
        return OAL_FAIL;
    }

    /* ��skb��dataָ��ָ����̫����֡ͷ */
    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);

    if (mac_vap_is_vsta(*ppst_vap))
    {
        if (ETHER_IS_MULTICAST(pst_ether_header->auc_ether_dhost))
        {
            /* vsta�˿ڲ�����mcast���������ض��� */
            OAM_INFO_LOG0((*ppst_vap)->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_tx_process::drop mcast pkt via vsta}");
            return OAL_FAIL;
        }

        if (!OAL_MEMCMP(hmac_vap_psta_oma(pst_hmac_vap), pst_ether_header->auc_ether_dhost, WLAN_MAC_ADDR_LEN))
        {
            OAM_WARNING_LOG0((*ppst_vap)->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_tx_process::drop pkt to oma of vsta}");
            return OAL_FAIL;
        }
    }
    else if (mac_vap_is_msta(*ppst_vap))
    {
        if (OAL_SUCC != hmac_psta_find_net_dev(hmac_psta_get_rep(pst_hmac_vap),
                pst_ether_header->auc_ether_shost, &pst_net_device))
        {
            OAM_WARNING_LOG0((*ppst_vap)->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_tx_process::drop pkt from unknown oma}");
            return OAL_FAIL;
        }

        *ppst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_device);
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_rx_process
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_rx_process(oal_netbuf_stru *pst_buf, hmac_vap_stru *pst_hmac_vap)
{
    mac_ether_header_stru   *pst_ether_header;
    oal_bool_enum_uint8      en_is_mcast;
    hmac_vap_stru           *pst_tmp_hvap;
    oal_dlist_head_stru     *pst_list;
    hmac_psta_rep_stru      *pst_rep;
    mac_device_stru         *pst_mac_device;
    hmac_vap_stru           *pst_mainsta;

    if (!pst_buf || !pst_hmac_vap)
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "{hmac_psta_rx_process::null ptr pst_buf=%x pst_hmac_vap=%x}", pst_buf, pst_hmac_vap);
        return OAL_FAIL;
    }

    /* ��skb��dataָ��ָ����̫����֡ͷ */
    oal_netbuf_push(pst_buf, ETHER_HDR_LEN);

    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);

    /* ��ԭskb��dataָ�� */
    oal_netbuf_pull(pst_buf, ETHER_HDR_LEN);

    if (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == pst_ether_header->us_ether_type)
    {
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (!pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_rx_mat::null device id=%d}", pst_hmac_vap->st_vap_base_info.uc_vap_id);
        return OAL_FAIL;
    }

    en_is_mcast   = ETHER_IS_MULTICAST(pst_ether_header->auc_ether_dhost);

    /* main sta��proxysta��root ap���͹㲥����root ap�Ὣ�յ��Ĺ㲥������������������û�ת���˰���
       ��ˣ�main sta���յ�root ap�����͵Ĺ㲥�������յ���Щ�㲥����main sta���ж��Ƿ�Ϊ��device�ϵ�
       sta���͵Ĺ㲥��������ǽ��䶪�����������κδ��� */
    if (OAL_TRUE == en_is_mcast)
    {
        pst_rep = hmac_psta_get_rep(pst_hmac_vap);

        OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_msta_list)
        {
            pst_tmp_hvap = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_xsta_entry);
            if (pst_tmp_hvap != pst_hmac_vap && !oal_compare_mac_addr(pst_ether_header->auc_ether_shost, mac_mib_get_StationID(&pst_tmp_hvap->st_vap_base_info)))
            {
                OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_rx_mat::drop pkt to vsta}");
                return OAL_FAIL;
            }
        }

        OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_vsta_list)
        {
            pst_tmp_hvap = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_xsta_entry);
            if (pst_tmp_hvap != pst_hmac_vap && !oal_compare_mac_addr(pst_ether_header->auc_ether_shost, mac_mib_get_StationID(&pst_tmp_hvap->st_vap_base_info)))
            {
                /* vsta�˿ڲ�����mcast���������� */
                OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_rx_mat::drop pkt to vsta}");
                return OAL_FAIL;
            }
        }
    }

    pst_mainsta = hmac_psta_get_msta(pst_hmac_vap);
    if (!pst_mainsta)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_psta_rx_mat::no msta found on rep!}");
        return OAL_FAIL;
    }

    OAL_NETBUF_DEV(pst_buf) = pst_mainsta->pst_net_device;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_init_vap
 ��������  : ��ʼ��psta
 �������  : pst_hmac_vap
             pst_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_init_vap(hmac_vap_stru *pst_hmac_vap, mac_cfg_add_vap_param_stru *pst_param)
{
    pst_hmac_vap->st_psta.uc_rep_id = pst_param->uc_rep_id;
    oal_memset(pst_hmac_vap->st_psta.auc_oma, 0, WLAN_MAC_ADDR_LEN);
    oal_dlist_init_head(&pst_hmac_vap->st_psta.st_hash_entry);
    oal_dlist_init_head(&pst_hmac_vap->st_psta.st_xsta_entry);

    return mac_psta_init_vap(&pst_hmac_vap->st_vap_base_info, pst_param);
}
/*****************************************************************************
 �� �� ��  : hmac_psta_add_vap
 ��������  : ���psta
 �������  : pst_hmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_add_vap(hmac_vap_stru *pst_hmac_vap)
{
    oal_uint8        uc_hash_value;
    oal_uint32       ul_psta_switch;
    mac_device_stru *pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    mac_vap_stru    *pst_mac_vap    = &pst_hmac_vap->st_vap_base_info;

    hmac_psta_rep_stru  *pst_rep;

    if (!pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_psta_add_vap::null dev ptr}");
        return OAL_FAIL;
    }

    if (!mac_vap_is_msta(pst_mac_vap) && !mac_vap_is_vsta(pst_mac_vap) && !mac_vap_is_pbss(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    if (hmac_vap_psta_in_rep(pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{hmac_psta_add_vap::already in repeater, vid=%d}", pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    pst_rep = hmac_psta_get_rep(pst_hmac_vap);

    if (mac_vap_is_pbss(pst_mac_vap))
    {
        oal_rw_lock_write_lock(&pst_rep->st_lock);
        oal_dlist_add_tail(&pst_hmac_vap->st_psta.st_hash_entry, &pst_rep->st_pbss_list);
        oal_rw_lock_write_unlock(&pst_rep->st_lock);

        return OAL_SUCC;
    }

    /* ����ǵ�һ��Proxy STA�� ע�ṳ�Ӻ��� */
    if (0 == mac_dev_xsta_num(pst_mac_device))
    {
        oam_netlink_ops_register(OAM_NL_CMD_PSTA, hmac_psta_receive_msg);
        ul_psta_switch = OAL_TRUE;
        hmac_config_proxysta_switch(pst_mac_vap, OAL_SIZEOF(ul_psta_switch), (oal_uint8 *)&ul_psta_switch);
#if  (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        br_fdb_change_register_hook(hmac_psta_fdb_change_handler);
#endif
    }

    /* ���Proxy STA�� hash����*/
    uc_hash_value  = MAC_PROXYSTA_CALCULATE_HASH_VALUE(hmac_vap_psta_oma(pst_hmac_vap));
    oal_rw_lock_write_lock(&pst_rep->st_lock);
    oal_dlist_add_head(&pst_hmac_vap->st_psta.st_hash_entry, &pst_rep->ast_hash[uc_hash_value]);
    oal_dlist_add_head(&pst_hmac_vap->st_psta.st_xsta_entry,
                       mac_vap_is_msta(pst_mac_vap) ?  &pst_rep->st_msta_list : &pst_rep->st_vsta_list);
    mac_dev_xsta_num(pst_mac_device)++;
    oal_rw_lock_write_unlock(&pst_rep->st_lock);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_del_vap
 ��������  : ɾ��psta
 �������  : pst_hmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_del_vap(hmac_vap_stru *pst_hmac_vap)
{
    oal_uint32                   uc_hash_value;
    oal_uint32                   ul_psta_switch;
    oal_uint8                    auc_proxysta_oma[WLAN_MAC_ADDR_LEN];
    oal_dlist_head_stru         *pst_hash_head;
    oal_dlist_head_stru         *pst_entry;
    oal_dlist_head_stru         *pst_entry_temp;
    mac_device_stru             *pst_mac_device;
    hmac_vap_stru               *pst_vap;
    mac_vap_stru                *pst_mac_vap = &pst_hmac_vap->st_vap_base_info;
    hmac_psta_rep_stru          *pst_rep;

    if (!mac_vap_is_msta(pst_mac_vap) && !mac_vap_is_vsta(pst_mac_vap) && !mac_vap_is_pbss(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    if (!hmac_vap_psta_in_rep(pst_hmac_vap))
    {
        return OAL_SUCC;
    }

    pst_rep = hmac_psta_get_rep(pst_hmac_vap);

    if (mac_vap_is_pbss(pst_mac_vap))
    {
        oal_rw_lock_write_lock(&pst_rep->st_lock);
        oal_dlist_delete_entry(&pst_hmac_vap->st_psta.st_hash_entry);
        oal_dlist_init_head(&pst_hmac_vap->st_psta.st_hash_entry);
        oal_rw_lock_write_unlock(&pst_rep->st_lock);

        return OAL_SUCC;
    }

    /* ��ȡmac_device_stru */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_del_vap::get mac_device ptr is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ��Ҫɾ����proxysta oma��ַ */
    oal_memcopy(auc_proxysta_oma, hmac_vap_psta_oma(pst_hmac_vap), WLAN_MAC_ADDR_LEN);

    uc_hash_value  = MAC_PROXYSTA_CALCULATE_HASH_VALUE(auc_proxysta_oma);
    oal_rw_lock_write_lock(&pst_rep->st_lock);
    pst_hash_head = &(pst_rep->ast_hash[uc_hash_value]);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_entry_temp, pst_hash_head)
    {
        pst_vap = OAL_DLIST_GET_ENTRY(pst_entry, hmac_vap_stru, st_psta.st_hash_entry);

        if (0 == oal_compare_mac_addr(hmac_vap_psta_oma(pst_vap), auc_proxysta_oma))
        {
            oal_dlist_delete_entry(&pst_vap->st_psta.st_hash_entry);
            oal_dlist_delete_entry(&pst_vap->st_psta.st_xsta_entry); // whatever
            oal_dlist_init_head(&pst_vap->st_psta.st_hash_entry);
            oal_dlist_init_head(&pst_vap->st_psta.st_xsta_entry); // whatever

            mac_dev_xsta_num(pst_mac_device)--;
            if (0 == mac_dev_xsta_num(pst_mac_device))
            {
                ul_psta_switch = OAL_FALSE;
                hmac_config_proxysta_switch(pst_mac_vap, OAL_SIZEOF(ul_psta_switch), (oal_uint8 *)&ul_psta_switch);
                oam_netlink_ops_unregister(OAM_NL_CMD_PSTA);
#if  (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
                br_fdb_change_register_hook(NULL);
#endif
            }
            oal_rw_lock_write_unlock(&pst_rep->st_lock);
            return OAL_SUCC;
        }
    }

    oal_rw_lock_write_unlock(&pst_rep->st_lock);
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_write_proc
 ��������  : proc write hook
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32   hmac_psta_write_proc (oal_file_stru *pst_file, const oal_int8 *pc_buffer, oal_uint32 ul_len, oal_void *p_data)
{
    return -1;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_read_proc
 ��������  : proc read hook
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 hmac_psta_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    hmac_psta_rep_stru  *pst_rep;
    oal_dlist_head_stru *pst_list;
    hmac_vap_stru       *pst_hmac_vap;
    oal_uint8           *puc_vma, *puc_oma;
    oal_uint32           ul_rep_id;

    for (ul_rep_id = 0; ul_rep_id < WLAN_PROXY_STA_MAX_REP; ul_rep_id++)
    {
        pst_rep = g_st_psta_mgr.ast_rep + ul_rep_id;

        OAL_IO_PRINT("===repeater id=%d\n", ul_rep_id);
        oal_rw_lock_read_lock(&pst_rep->st_lock);

        // show all pbss
        OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_pbss_list)
        {
            pst_hmac_vap = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_hash_entry);
            puc_vma = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
            puc_oma = hmac_vap_psta_oma(pst_hmac_vap);
            OAL_IO_PRINT("   pbss:oma=%02x:%02x:%02x:%02x:%02x:%02x vma=%02x:%02x:%02x:%02x:%02x:%02x %s\n",
                puc_oma[0], puc_oma[1], puc_oma[2], puc_oma[3], puc_oma[4], puc_oma[5],
                puc_vma[0], puc_vma[1], puc_vma[2], puc_vma[3], puc_vma[4], puc_vma[5], pst_hmac_vap->pst_net_device->name);
        }

        // show all msta
        OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_msta_list)
        {
            pst_hmac_vap = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_xsta_entry);
            puc_vma = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
            puc_oma = hmac_vap_psta_oma(pst_hmac_vap);
            OAL_IO_PRINT("   msta:oma=%02x:%02x:%02x:%02x:%02x:%02x vma=%02x:%02x:%02x:%02x:%02x:%02x %s\n",
                puc_oma[0], puc_oma[1], puc_oma[2], puc_oma[3], puc_oma[4], puc_oma[5],
                puc_vma[0], puc_vma[1], puc_vma[2], puc_vma[3], puc_vma[4], puc_vma[5], pst_hmac_vap->pst_net_device->name);
        }

        // show all vsta
        OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_vsta_list)
        {
            pst_hmac_vap = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_xsta_entry);
            puc_vma = mac_mib_get_StationID(&pst_hmac_vap->st_vap_base_info);
            puc_oma = hmac_vap_psta_oma(pst_hmac_vap);
            OAL_IO_PRINT("   vsta:oma=%02x:%02x:%02x:%02x:%02x:%02x vma=%02x:%02x:%02x:%02x:%02x:%02x %s\n",
                puc_oma[0], puc_oma[1], puc_oma[2], puc_oma[3], puc_oma[4], puc_oma[5],
                puc_vma[0], puc_vma[1], puc_vma[2], puc_vma[3], puc_vma[4], puc_vma[5], pst_hmac_vap->pst_net_device->name);
        }

        oal_rw_lock_read_unlock(&pst_rep->st_lock);
    }
    *eof = 1;
    return -1;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_get_rep
 ��������  : get rep of vap
 �������  : pst_hmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_psta_rep_stru *hmac_psta_get_rep(hmac_vap_stru *pst_hmac_vap)
{
    return g_st_psta_mgr.ast_rep + pst_hmac_vap->st_psta.uc_rep_id;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_get_msta
 ��������  : choose msta for vap
 �������  : pst_hmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_vap_stru *hmac_psta_get_msta(hmac_vap_stru *pst_hmac_vap)
{
    oal_dlist_head_stru *pst_list;
    hmac_psta_rep_stru  *pst_rep = hmac_psta_get_rep(pst_hmac_vap);

    // NOTE:do what you wish for multi-msta repeater!
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_msta_list)
    {
        return OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_xsta_entry);
    }

    return OAL_PTR_NULL;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_rep_init
 ��������  : init repeater
 �������  : pst_rep
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void    hmac_psta_rep_init(hmac_psta_rep_stru *pst_rep)
{
    oal_uint32  ul_idx;

    pst_rep->en_isolation = OAL_FALSE;
    pst_rep->uc_use_cnt   = 0;
    oal_rw_lock_init(&pst_rep->st_lock);
    oal_dlist_init_head(&pst_rep->st_msta_list);
    oal_dlist_init_head(&pst_rep->st_vsta_list);
    oal_dlist_init_head(&pst_rep->st_pbss_list);

    for (ul_idx = 0; ul_idx < MAC_VAP_PROXY_STA_HASH_MAX_VALUE; ul_idx++)
    {
        oal_dlist_init_head(pst_rep->ast_hash + ul_idx);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_psta_mgr_init
 ��������  : init repeater mgr
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_mgr_init(oal_void)
{
    OAL_STATIC  oal_bool_enum_uint8 en_inited = OAL_FALSE;
    oal_uint32           ul_idx;
    hmac_psta_mgr_stru  *pst_mgr = &g_st_psta_mgr;

    if (en_inited)  // just init once for dual chip
    {
        return OAL_TRUE;
    }

    en_inited = OAL_TRUE;
    oal_memset(pst_mgr, 0, OAL_SIZEOF(hmac_psta_mgr_stru));

    for (ul_idx = 0; ul_idx < WLAN_PROXY_STA_MAX_REP; ul_idx++)
    {
        hmac_psta_rep_init(g_st_psta_mgr.ast_rep + ul_idx);
    }

#if  (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    pst_mgr->pst_proc_entry = oal_create_proc_entry("psta", 0420, NULL);
    if (!pst_mgr->pst_proc_entry)
    {
        return OAL_FAIL;
    }

    pst_mgr->pst_proc_entry->data       = 0;
    pst_mgr->pst_proc_entry->nlink      = 1;
    pst_mgr->pst_proc_entry->read_proc  = (write_proc_t *)hmac_psta_read_proc;
    pst_mgr->pst_proc_entry->write_proc = (write_proc_t *)hmac_psta_write_proc;
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_mgr_exit
 ��������  : exit repeater mgr
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_mgr_exit(oal_void)
{
#if  (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    hmac_psta_mgr_stru  *pst_mgr = &g_st_psta_mgr;

    if (!pst_mgr->pst_proc_entry)
    {
        oal_remove_proc_entry("psta", NULL);
        pst_mgr->pst_proc_entry = NULL;
    }
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_rx_checksum
 ��������  : ����checksum
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��29��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_psta_rx_checksum(oal_uint16 us_osum,
                                  oal_uint8  uc_omac[6],
                                  oal_uint8  uc_nmac[6])

{
    oal_uint16 us_nsum = us_osum;
    oal_uint32 ul_sum;
    oal_uint32 ul_loop;

    if (0 == us_osum)
    {
        return us_nsum;
    }

    for (ul_loop = 0;ul_loop < 3; ul_loop++)
    {
        ul_sum = us_nsum;
        ul_sum += *(oal_uint16 *)&uc_omac[ul_loop * 2] + (~(*(oal_uint16 *)&uc_nmac[ul_loop * 2]) & 0XFFFF);
        ul_sum  = (ul_sum >> 16) + (ul_sum & 0XFFFF);
        us_nsum = (oal_uint16)((ul_sum >> 16) + ul_sum);
    }

    return us_nsum;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_rx_arp_mat
 ��������  : arp����ַת��
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��11��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_psta_rx_arp_mat(mac_vap_stru            *pst_mac_vap,
                                                      mac_ether_header_stru   *pst_ether_header,
                                                      mac_device_stru         *pst_mac_device,
                                                      oal_uint32               ul_pkt_len)
{
    oal_eth_arphdr_stru *pst_arp          = OAL_PTR_NULL;
    oal_uint8           *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8           *puc_arp_dmac     = OAL_PTR_NULL;
    hmac_vap_stru       *pst_hmac_temp_vap= OAL_PTR_NULL;
    oal_uint8           *puc_des_mac      = OAL_PTR_NULL;
    oal_uint8           uc_vap_idx;
    oal_bool_enum_uint8 en_is_mcast;
    oal_uint32          ul_contig_len;
    oal_bool_enum_uint8 en_is_arp_mac_changed = OAL_FALSE;
    hmac_vap_stru      *pst_hmac_vap;

    /***************************************************************************/
    /*                      ARP Frame Format                                   */
    /* ----------------------------------------------------------------------- */
    /* |��̫��Ŀ�ĵ�ַ|��̫��Դ��ַ|֡����|Ӳ������|Э������|Ӳ����ַ����|     */
    /* ----------------------------------------------------------------------- */
    /* | 6 (���滻)   |6           |2     |2       |2       |1           |     */
    /* ----------------------------------------------------------------------- */
    /* |Э���ַ����|op|���Ͷ���̫����ַ|���Ͷ�IP��ַ|Ŀ����̫����ַ|Ŀ��IP��ַ*/
    /* ----------------------------------------------------------------------- */
    /* | 1          |2 |6               |4           |6 (���滻)    |4         */
    /* ----------------------------------------------------------------------- */
    /*                                                                         */
    /***************************************************************************/

    /* �����Ϸ��Լ�� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_ether_header) || (OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_psta_rx_arp_mat::The input parameter of hmac_psta_rx_arp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }
    pst_hmac_vap = OAL_DLIST_GET_ENTRY(pst_mac_vap, hmac_vap_stru, st_vap_base_info);

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);

    /* ��ȡ��̫��Ŀ��mac�����ݶ� */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    /* ��ȡ��̫��֡Ŀ�ĵ�ַ�Ƿ�Ϊ�ಥ��ַ */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);

    /* ARP ����ַת�� */
    pst_arp = (oal_eth_arphdr_stru *)puc_eth_body;
    ul_contig_len += OAL_SIZEOF(oal_eth_arphdr_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_rx_arp_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_eth_arphdr_stru.}");
        return OAL_FAIL;
    }

    /*lint -e778*/
    if ((ETHER_ADDR_LEN == pst_arp->uc_ar_hln) && (OAL_NET2HOST_SHORT(ETHER_TYPE_IP) == pst_arp->us_ar_pro))
    {
        puc_arp_dmac = pst_arp->auc_ar_tha;
    }
    else
    {
        pst_arp = OAL_PTR_NULL;
    }
    /*lint +e778*/

    if (OAL_PTR_NULL != pst_arp)
    {
        if (OAL_TRUE != en_is_mcast)
        {
            switch (OAL_NET2HOST_SHORT(pst_arp->us_ar_op))
            {
                case OAL_ARPOP_REQUEST:
                case OAL_ARPOP_REPLY:
                    /* �滻mac��ַΪout vap��mac��ַ */
                    oal_set_mac_addr(puc_arp_dmac, hmac_vap_psta_oma(pst_hmac_vap));

                    break;
                default:
                    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_rx_arp_mat::do not replace arp addr.}");
            }
        }
        else
        {
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_rx_arp_mat::received arp broadcast packet, start process.}");

            /* root ap�����������й㲥����ֻ��sta0�����յ�����arp����arp_dmacΪstax���ĵ�ַ���ҵ�stax��,�滻Ϊ������oma��ַ */
            if (OAL_FALSE != oal_compare_mac_addr(puc_arp_dmac, hmac_vap_psta_oma(pst_hmac_vap)))
            {
                OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                   "{hmac_psta_rx_arp_mat::start into if.}");

               /* ����Device�µ�vap(STAģʽ)����Ŀ�ĵ�ַΪ��vap�Լ��ĵ�ַ��ͬʱ������oma��ַ�滻֡��Ŀ�ĵ�ַ */
               for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
               {
                   pst_hmac_temp_vap = mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                   if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_temp_vap))
                   {
                       OAM_WARNING_LOG0(uc_vap_idx, OAM_SF_PROXYSTA, "{hmac_psta_rx_arp_mat::pst_mac_vap is null ptr!}");
                       return OAL_SUCC;
                   }

                   if (OAL_FALSE == oal_compare_mac_addr(puc_arp_dmac, mac_mib_get_StationID(&pst_hmac_temp_vap->st_vap_base_info)))
                   {
                       /* �滻mac��ַΪout vap��mac��ַ */
                       oal_set_mac_addr(puc_arp_dmac, hmac_vap_psta_oma(pst_hmac_temp_vap));

                       OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                     "{hmac_psta_rx_arp_mat::changed multi arp des mac with proxysta's oma mac.}");

                       en_is_arp_mac_changed = OAL_TRUE;
                       break;
                   }
               }

               /* ���arm macû�иı䣬���������arp�㲥�������軻��ַ��ֱ�ӷ��� */
               if (OAL_FALSE == en_is_arp_mac_changed)
               {
                    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                   "{hmac_psta_rx_arp_mat::do not changed multi arp des mac, return succ.}");
                    return OAL_SUCC;
                }
            }
        }
    }

    oal_set_mac_addr(puc_des_mac, hmac_vap_psta_oma(pst_hmac_vap));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_rx_ip_mat
 ��������  : ip����ַת������Ҫ�����������ֱ��ĵĴ���:
             1.DHCP���ĵĴ���
             2.����IP���ͱ��ĵĴ���
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��11��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_psta_rx_ip_mat(mac_vap_stru           *pst_mac_vap,
                                                     mac_ether_header_stru  *pst_ether_header,
                                                     mac_device_stru        *pst_mac_device,
                                                     oal_uint32              ul_pkt_len)
{
    oal_ip_header_stru   *pst_ip_header    = OAL_PTR_NULL;
    oal_udp_header_stru  *pst_udp_header   = OAL_PTR_NULL;
    oal_dhcp_packet_stru *pst_dhcp_packet  = OAL_PTR_NULL;
    hmac_vap_stru        *pst_hmac_temp_vap;
    oal_uint8            *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8            *puc_des_mac      = OAL_PTR_NULL;
    oal_uint16           us_ip_header_len;
    oal_uint8            uc_vap_idx;
    oal_bool_enum_uint8  en_is_mcast;
    oal_uint32           ul_contig_len;
    hmac_vap_stru       *pst_hmac_vap;
    /* �����Ϸ��Լ�� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_ether_header) || (OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_psta_rx_ip_mat::The input parameter of hmac_psta_rx_ip_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_hmac_vap = OAL_DLIST_GET_ENTRY(pst_mac_vap, hmac_vap_stru, st_vap_base_info);

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                  "{hmac_psta_rx_ip_mat::start into hmac_psta_rx_ip_mat.}");

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);

    /* ��ȡ��̫��Ŀ��mac�����ݶ� */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    /* ��ȡ��̫��֡Ŀ�ĵ�ַ�Ƿ�Ϊ�ಥ��ַ */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);

    /*************************************************************************/
    /*                      DHCP Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |��̫��ͷ        |   IPͷ         | UDPͷ           |DHCP����       | */
    /* --------------------------------------------------------------------- */
    /* | 14             |20              |8                | ����          | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    pst_ip_header = (oal_ip_header_stru *)puc_eth_body;

    /*************************************************************************/
    /*                    IPͷ��ʽ (oal_ip_header_stru)                      */
    /* --------------------------------------------------------------------- */
    /* | �汾 | ��ͷ���� | �������� | �ܳ���  |��ʶ  |��־  |��ƫ����
|      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  4bits   | 1        | 2       | 2    |3bits | 13bits  |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | ������ | Э��        | ͷ��У���| Դ��ַ��SrcIp��|Ŀ�ĵ�ַ��DstIp��*/
    /* --------------------------------------------------------------------- */
    /* | 1      |  1 (17ΪUDP)| 2         | 4              | 4               */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/

    ul_contig_len += OAL_SIZEOF(oal_ip_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_rx_ip_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_ip_header_stru.}");
        return OAL_FAIL;
    }

    us_ip_header_len = pst_ip_header->us_ihl * 4;

    /* �����UDP����������DHCPЭ��ı��ĵ�ַת�� */
    if (OAL_IPPROTO_UDP == pst_ip_header->uc_protocol)
    {
        pst_udp_header  = (oal_udp_header_stru *)((oal_uint8 *)pst_ip_header + us_ip_header_len);

        ul_contig_len += OAL_SIZEOF(oal_udp_header_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_rx_ip_mat::The length of buf is invalid.}");
            return OAL_FAIL;
        }

        /*************************************************************************/
        /*                      UDP ͷ (oal_udp_header_stru)                     */
        /* --------------------------------------------------------------------- */
        /* |Դ�˿ںţ�SrcPort��|Ŀ�Ķ˿ںţ�DstPort��| UDP����    | UDP�����  | */
        /* --------------------------------------------------------------------- */
        /* | 2                 | 2                   |2           | 2          | */
        /* --------------------------------------------------------------------- */
        /*                                                                       */
        /*************************************************************************/

/*lint -e778*/
/*lint -e572*/

        /* DHCP request UDP Client SP = 68 (bootpc), DP = 67 (bootps) */
        if (OAL_NET2HOST_SHORT(67) == pst_udp_header->source)
        {
/*lint +e778*/
/*lint +e572*/
            /*************************************************************************/
            /*                    DHCP ���ĸ�ʽ (oal_dhcp_packet_stru)               */
            /* --------------------------------------------------------------------- */
            /* | op | htpe | hlen | hops  |xid(����IP)  |secs(����)   |flags(��־)|  */
            /* --------------------------------------------------------------------- */
            /* | 1  | 1    | 1    | 1     | 4           | 2           | 2          | */
            /* --------------------------------------------------------------------- */
            /* --------------------------------------------------------------------- */
            /* | ciaddr(4)�ͻ�ip��ַ | yiaddr��4�����IP��ַ |siaddr(4)������IP��ַ| */
            /* --------------------------------------------------------------------- */
            /* | giaddr��4���м̴���IP��ַ      | chaddr��16���ͻ���Ӳ����ַ(���滻)|*/
            /* --------------------------------------------------------------------- */
            /* |sname��64����������������|file��128�������ļ���|option����������ѡ��|*/
            /* --------------------------------------------------------------------- */
            /*************************************************************************/
            pst_dhcp_packet = (oal_dhcp_packet_stru *)(((oal_uint8 *)pst_udp_header) + OAL_SIZEOF(oal_udp_header_stru));

            ul_contig_len += OAL_SIZEOF(oal_dhcp_packet_stru);
            if (ul_pkt_len < ul_contig_len)
            {
                return OAL_FAIL;
            }

            if (OAL_FALSE == en_is_mcast)
            {
                /* ������ */
                if (OAL_FALSE == oal_compare_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_vap)))
                {
                    /* ��UDP���еĵ�ַ�滻Ϊ�Լ��ĵ�ַ */
                    oal_set_mac_addr(pst_dhcp_packet->chaddr, hmac_vap_psta_oma(pst_hmac_vap));

                    /* ���¼���udp checksum */
                    pst_udp_header->check = hmac_psta_rx_checksum(pst_udp_header->check,
                                                                                  mac_mib_get_StationID(pst_mac_vap),
                                                                                  hmac_vap_psta_oma(pst_hmac_vap));

                    /* ά�ֵ��� */
                    oal_set_mac_addr(puc_des_mac, hmac_vap_psta_oma(pst_hmac_vap));
                }
                else
                {
                    return OAL_SUCC;
                }
            }
            else
            {
                /* main sta�յ��㲥DHCP����֡��dhcp�����пͻ���mac��ַ�ͽ��ն˿ڵĵ�ַ��ͬ����������е�vap(��proxysta)��
                   �ҵ���dhcp�����еĿͻ���mac��ַ��ͬ��vap mac(��proxysta)��ַ�����ͻ���mac��ַ�滻Ϊproxysta��oma��ַ��
                   ������udp check */
                if (OAL_FALSE != oal_compare_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_vap)))
                {
                   /* ����Device�µ�vap(STAģʽ)����Ŀ�ĵ�ַΪ��vap�Լ��ĵ�ַ��ͬʱ������oma��ַ�滻֡��Ŀ�ĵ�ַ */
                   for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
                   {
                       pst_hmac_temp_vap = mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                       if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_temp_vap))
                       {
                           OAM_WARNING_LOG0(uc_vap_idx, OAM_SF_PROXYSTA,
                                            "{hmac_psta_rx_ip_mat::pst_mac_vap is null ptr!}");
                           return OAL_SUCC;
                       }

                       if (OAL_FALSE == oal_compare_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(&pst_hmac_temp_vap->st_vap_base_info)))
                       {
                           /* �滻mac��ַΪout vap��mac��ַ */
                           oal_set_mac_addr(pst_dhcp_packet->chaddr, hmac_vap_psta_oma(pst_hmac_temp_vap));

                           /* ���¼���udp checksum */
                           pst_udp_header->check = hmac_psta_rx_checksum(pst_udp_header->check,
                                                                                         mac_mib_get_StationID(&pst_hmac_temp_vap->st_vap_base_info),
                                                                                         hmac_vap_psta_oma(pst_hmac_temp_vap));

                           break;
                       }
                   }
                }
            }
        }
        else
        {
            /* ����DHCP������UDP����Ҳ��Ҫ������̫��Ŀ�ĵ�ַΪproxysta��vma */
            oal_set_mac_addr(puc_des_mac, hmac_vap_psta_oma(pst_hmac_vap));
        }
    }
    /* ��������IP���ĵĵ�ַת������ */
    else
    {
        /* ������̫��Ŀ�ĵ�ַΪproxysta��vma */
        oal_set_mac_addr(puc_des_mac, hmac_vap_psta_oma(pst_hmac_vap));
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_rx_mat
 ��������  : ARP��DHCP��ICMPv6�Ȱ����ϱ�����ǰ��ַת������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��25��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_rx_mat(oal_netbuf_stru *pst_buf, hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru            *pst_mac_vap;
    mac_ether_header_stru   *pst_ether_header;
    oal_uint16               us_ether_type;
    oal_uint8               *puc_des_mac;
    oal_uint32               ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    oal_uint32               ul_pkt_len;
    mac_device_stru         *pst_mac_device;
    oal_uint32               ul_ret;

    if (!pst_buf || !pst_hmac_vap)
    {
        OAM_ERROR_LOG2(0, OAM_SF_PROXYSTA, "null ptr pst_buf=%x pst_hmac_vap=%x\n", pst_buf, pst_hmac_vap);
        return OAL_FAIL;
    }

    /* ��skb��dataָ��ָ����̫����֡ͷ */
    oal_netbuf_push(pst_buf, ETHER_HDR_LEN);

    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);

    /* ��ԭskb��dataָ�� */
    oal_netbuf_pull(pst_buf, ETHER_HDR_LEN);

    if (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == pst_ether_header->us_ether_type)
    {
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (!pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA, "{hmac_psta_rx_mat::null device id=%d}", pst_hmac_vap->st_vap_base_info.uc_vap_id);
        return OAL_FAIL;
    }

    ul_pkt_len = OAL_NETBUF_LEN(pst_buf) + ETHER_HDR_LEN;

    /* ��ȡVAP�ṹ�� */
    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_rx_mat::drop for invalid len, ul_pkt_len=%d ul_contig_len=%d}", ul_pkt_len, ul_contig_len);
        return OAL_FAIL;
    }

    us_ether_type = pst_ether_header->us_ether_type;
    puc_des_mac   = pst_ether_header->auc_ether_dhost;

    /* ARP ����ַת�� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_ARP) == us_ether_type)
    {
        ul_ret = hmac_psta_rx_arp_mat(pst_mac_vap,
                                          pst_ether_header,
                                          pst_mac_device,
                                          ul_pkt_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_rx_mat::hmac_psta_rx_arp_mat returns %d.}", ul_ret);
        }
        return ul_ret;
    }

/*lint -e778*/
    /* IP����ַת�� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == us_ether_type)
    {
/*lint +e778*/
        ul_ret = hmac_psta_rx_ip_mat(pst_mac_vap,
                                         pst_ether_header,
                                         pst_mac_device,
                                         ul_pkt_len);
        if (OAL_SUCC != ul_ret)
        {
           OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_rx_mat::hmac_psta_rx_ip_mat returns %d.}", ul_ret);
        }
        return ul_ret;
    }

    /*icmpv6 ����ַת�� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == us_ether_type)
    {
        /*TBD A��˾��������todo */
    }

    oal_set_mac_addr(puc_des_mac, hmac_vap_psta_oma(pst_hmac_vap));

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_tx_checksum
 ��������  : ���㱨�ĵ�У���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��29��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  hmac_psta_tx_checksum(oal_uint16   us_protocol,
                                                 oal_uint16   us_len,
                                                 oal_uint8    auc_src_addr[],
                                                 oal_uint8    auc_dest_addr[],
                                                 oal_uint16   us_addrleninbytes,
                                                 oal_uint8   *puc_buff)
{
    oal_uint16 us_pad = 0;
    oal_uint16 us_word16;
    oal_uint32 ul_sum = 0;
    oal_int    l_loop;

    if (us_len & 1)
    {
        us_len -= 1;
        us_pad  = 1;
    }

    for (l_loop = 0; l_loop < us_len; l_loop = l_loop + 2)
    {
        us_word16 = puc_buff[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + puc_buff[l_loop+1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    if (us_pad)
    {
        us_word16 = puc_buff[us_len];
        us_word16 <<= 8;
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    for (l_loop = 0; l_loop < us_addrleninbytes; l_loop = l_loop + 2)
    {
        us_word16 = auc_src_addr[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + auc_src_addr[l_loop + 1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }


    for (l_loop = 0; l_loop < us_addrleninbytes; l_loop = l_loop + 2)
    {
        us_word16 = auc_dest_addr[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + auc_dest_addr[l_loop + 1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    ul_sum = ul_sum + (oal_uint32)us_protocol + (oal_uint32)(us_len+us_pad);

    while (ul_sum >> 16)
    {
        ul_sum = (ul_sum & 0xFFFF) + (ul_sum >> 16);
    }

    ul_sum = ~ul_sum;

    return ((oal_uint16) ul_sum);
}

/*****************************************************************************
 �� �� ��  : hmac_psta_tx_arp_mat
 ��������  : arp����ַת��
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��8��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_psta_tx_arp_mat(mac_vap_stru *pst_mac_vap,
                                                      oal_uint8 *puc_eth_body,
                                                      oal_uint32 ul_pkt_len,
                                                      oal_uint32 ul_contig_len)
{
    oal_eth_arphdr_stru *pst_arp      = OAL_PTR_NULL;
    oal_uint8           *puc_arp_smac = OAL_PTR_NULL;

   /***************************************************************************/
   /*                      ARP Frame Format                                   */
   /* ----------------------------------------------------------------------- */
   /* |��̫��Ŀ�ĵ�ַ|��̫��Դ��ַ|֡����|Ӳ������|Э������|Ӳ����ַ����|     */
   /* ----------------------------------------------------------------------- */
   /* | 6            |6(���滻)   |2     |2       |2       |1           |     */
   /* ----------------------------------------------------------------------- */
   /* |Э���ַ����|op|���Ͷ���̫����ַ|���Ͷ�IP��ַ|Ŀ����̫����ַ|Ŀ��IP��ַ*/
   /* ----------------------------------------------------------------------- */
   /* | 1          |2 |6(���滻)       |4           |6             |4         */
   /* ----------------------------------------------------------------------- */
   /*                                                                         */
   /***************************************************************************/

    /* �����Ϸ��Լ�� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_eth_body))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_arp_mat::The input parameter of hmac_psta_tx_arp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_arp = (oal_eth_arphdr_stru *)puc_eth_body;
    ul_contig_len += (oal_int32)OAL_SIZEOF(oal_eth_arphdr_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_arp_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_eth_arphdr_stru.}");
        return OAL_FAIL;
    }

    /*lint -e778*/
    if ((ETHER_ADDR_LEN == pst_arp->uc_ar_hln) && (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == pst_arp->us_ar_pro))
    {
        puc_arp_smac = pst_arp->auc_ar_sha;
    }
    /*lint +e778*/
    else
    {
        pst_arp = OAL_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_arp)
    {
        switch (OAL_NET2HOST_SHORT(pst_arp->us_ar_op))
        {
            case OAL_ARPOP_REQUEST:
            case OAL_ARPOP_REPLY:

            // �滻mac��ַΪout vap��mac��ַ
            oal_set_mac_addr(puc_arp_smac,  mac_mib_get_StationID(pst_mac_vap));
            break;
            default:
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                             "{hmac_psta_tx_arp_mat::do not replace arp addr.}");
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_tx_ip_mat
 ��������  : ip����ַת��
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��8��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_psta_tx_ip_mat(mac_vap_stru           *pst_mac_vap,
                                                     mac_ether_header_stru  *pst_ether_header,
                                                     oal_uint8              *puc_eth_body,
                                                     oal_uint32             ul_pkt_len,
                                                     oal_uint32             ul_contig_len)
{
    oal_ip_header_stru   *pst_ip_header   = OAL_PTR_NULL;
    oal_udp_header_stru  *pst_udp_header  = OAL_PTR_NULL;
    oal_dhcp_packet_stru *pst_dhcp_packet = OAL_PTR_NULL;
    oal_uint8            *puc_scr_mac     = OAL_PTR_NULL;
    oal_uint16            us_ip_header_len;

    /*************************************************************************/
    /*                      DHCP Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |��̫��ͷ        |   IPͷ         | UDPͷ           |DHCP����       | */
    /* --------------------------------------------------------------------- */
    /* | 14             |20              |8                | ����          | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* �����Ϸ��Լ�� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_ether_header) || (OAL_PTR_NULL == puc_eth_body))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_ip_mat::The input parameter of hmac_psta_tx_dhcp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_ip_header =  (oal_ip_header_stru *)puc_eth_body;

    /*************************************************************************/
    /*                    IPͷ��ʽ (oal_ip_header_stru)                      */
    /* --------------------------------------------------------------------- */
    /* | �汾 | ��ͷ���� | �������� | �ܳ���  |��ʶ  |��־  |��ƫ����
|      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  4bits   | 1        | 2       | 2    |3bits | 13bits  |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | ������ | Э��        | ͷ��У���| Դ��ַ��SrcIp��|Ŀ�ĵ�ַ��DstIp��*/
    /* --------------------------------------------------------------------- */
    /* | 1      |  1 (17ΪUDP)| 2         | 4              | 4               */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/

    ul_contig_len += OAL_SIZEOF(oal_ip_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_ip_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_ip_header_stru.}");
        return OAL_FAIL;
    }

    us_ip_header_len = pst_ip_header->us_ihl * 4;

    /* �����UDP */
    if (OAL_IPPROTO_UDP == pst_ip_header->uc_protocol)
    {
        pst_udp_header  = (oal_udp_header_stru *)((oal_uint8 *)pst_ip_header + us_ip_header_len);

        ul_contig_len += OAL_SIZEOF(oal_udp_header_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_ip_mat::The length of buf is invalid.}");
            return OAL_FAIL;
        }

        /*************************************************************************/
        /*                      UDP ͷ (oal_udp_header_stru)                     */
        /* --------------------------------------------------------------------- */
        /* |Դ�˿ںţ�SrcPort��|Ŀ�Ķ˿ںţ�DstPort��| UDP����    | UDP�����  | */
        /* --------------------------------------------------------------------- */
        /* | 2                 | 2                   |2           | 2          | */
        /* --------------------------------------------------------------------- */
        /*                                                                       */
        /*************************************************************************/

        /* DHCP request UDP Client SP = 68 (bootpc), DP = 67 (bootps) */

/*lint -e778*/
/*lint -e572*/

        if (OAL_HOST2NET_SHORT(67)== pst_udp_header->dest)
        {
/*lint +e778*/
/*lint +e572*/

            /*************************************************************************/
            /*                    DHCP ���ĸ�ʽ (oal_dhcp_packet_stru)               */
            /* --------------------------------------------------------------------- */
            /* | op | htpe | hlen | hops  |xid(����IP)  |secs(����)   |flags(��־)|  */
            /* --------------------------------------------------------------------- */
            /* | 1  | 1    | 1    | 1     | 4           | 2           | 2          | */
            /* --------------------------------------------------------------------- */
            /* --------------------------------------------------------------------- */
            /* | ciaddr(4)�ͻ�ip��ַ | yiaddr��4�����IP��ַ |siaddr(4)������IP��ַ| */
            /* --------------------------------------------------------------------- */
            /* | giaddr��4���м̴���IP��ַ      | chaddr��16���ͻ���Ӳ����ַ(���滻)|*/
            /* --------------------------------------------------------------------- */
            /* |sname��64����������������|file��128�������ļ���|option����������ѡ��|*/
            /* --------------------------------------------------------------------- */
            /*************************************************************************/

            pst_dhcp_packet = (oal_dhcp_packet_stru *)(((oal_uint8 *)pst_udp_header) + OAL_SIZEOF(oal_udp_header_stru));

            ul_contig_len += OAL_SIZEOF(oal_dhcp_packet_stru);
            if (ul_pkt_len < ul_contig_len)
            {
                OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_ip_mat::The length of buf is invalid.}");
                return OAL_FAIL;
            }

            puc_scr_mac = pst_ether_header->auc_ether_shost;

            if (OAL_FALSE == oal_compare_mac_addr(pst_dhcp_packet->chaddr, pst_ether_header->auc_ether_shost))
            {
                /* ��UDP���еĵ�ַ�滻Ϊ�Լ��ĵ�ַ */
                oal_set_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_vap));

                /* ���ڰ������Ѿ�����д������Ҫ����дUDP ֡��checksum */
                pst_udp_header->check = hmac_psta_rx_checksum(pst_udp_header->check,
                                                                              puc_scr_mac,
                                                                              mac_mib_get_StationID(pst_mac_vap));
            }

        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_tx_icmpv6_mat
 ��������  : icmpv6����ַת��
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��8��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_psta_tx_icmpv6_mat(mac_vap_stru *pst_mac_vap,
                                                           oal_uint8 *puc_eth_body,
                                                           oal_uint32 ul_pkt_len,
                                                           oal_uint32 ul_contig_len)
{
    oal_ipv6hdr_stru          *pst_ipv6hdr          = OAL_PTR_NULL;
    oal_icmp6hdr_stru         *pst_icmp6hdr         = OAL_PTR_NULL;
    oal_eth_icmp6_lladdr_stru *pst_eth_icmp6_lladdr = OAL_PTR_NULL;
    oal_uint16                 us_icmp6len;
    oal_bool_enum_uint8        en_packet_changed = OAL_TRUE;
    oal_uint16                 us_check_sum = 0;

    /* �����Ϸ��Լ�� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_eth_body))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_icmpv6_mat::The input parameter of hmac_psta_tx_icmpv6_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_ipv6hdr = (oal_ipv6hdr_stru *)puc_eth_body;

    ul_contig_len += OAL_SIZEOF(oal_ipv6hdr_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_icmpv6_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_ipv6hdr_stru.  ul_pkt_len[%d], ul_contig_len[%d]}", ul_pkt_len, ul_contig_len);
        return OAL_FAIL;
    }

    if (OAL_IPPROTO_ICMPV6 == pst_ipv6hdr->nexthdr)
    {
        pst_icmp6hdr = (oal_icmp6hdr_stru *)(pst_ipv6hdr + 1);
        us_icmp6len  = pst_ipv6hdr->payload_len;

        ul_contig_len += OAL_SIZEOF(oal_icmp6hdr_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_icmpv6_mat::The length of buf is invalid.}");
            return OAL_FAIL;
        }

        /*
         * It seems that we only have to modify IPv6 packets being
         * sent by a Proxy STA. Both the solicitation and advertisement
         * packets have the STA's OMA. Flip that to the VMA.
        */
        switch (pst_icmp6hdr->icmp6_type)
        {
            case OAL_NDISC_NEIGHBOUR_SOLICITATION:
            case OAL_NDISC_NEIGHBOUR_ADVERTISEMENT:
            {
                ul_contig_len += OAL_IPV6_MAC_ADDR_LEN;
                /* ������IcmpV6 option,Դ��ַ�����ڣ�����Ҫת�� */
                if (ul_pkt_len == ul_contig_len)
                {
                    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                          "{hmac_psta_tx_icmpv6_mat::No source addr.}");
                    return OAL_SUCC;
                }

                /* ����Դ��ַ������ת�� */
                ul_contig_len += OAL_SIZEOF(oal_eth_icmp6_lladdr_stru);
                if (ul_pkt_len < ul_contig_len)
                {
                    OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_icmpv6_mat ABNORMAL::The length of buf is invalid ul_pkt_len[%d], ul_contig_len[%d] icmp6_type[%d].}", ul_pkt_len, ul_contig_len, pst_icmp6hdr->icmp6_type);
                    return OAL_FAIL;
                }

                pst_eth_icmp6_lladdr = (oal_eth_icmp6_lladdr_stru *)((oal_uint8 *)(pst_icmp6hdr + 1) + 16);

                /* �滻��ַ */
                oal_set_mac_addr(pst_eth_icmp6_lladdr->uc_addr, mac_mib_get_StationID(pst_mac_vap));

                us_check_sum = hmac_psta_tx_checksum((oal_uint16)OAL_IPPROTO_ICMPV6,us_icmp6len,
                                   pst_ipv6hdr->saddr.s6_addr, pst_ipv6hdr->daddr.s6_addr,16,(oal_uint8 *)pst_icmp6hdr);

                pst_icmp6hdr->icmp6_cksum = OAL_HOST2NET_SHORT(us_check_sum);
                break;
            }
            case OAL_NDISC_ROUTER_SOLICITATION:
            {
                ul_contig_len += OAL_SIZEOF(oal_eth_icmp6_lladdr_stru);
                if (ul_pkt_len < ul_contig_len)
                {
                    OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                   "{hmac_psta_tx_icmpv6_mat::The length of buf is invalid.}");
                    return OAL_FAIL;
                }

                /* replace the HW address with the VMA */
                pst_eth_icmp6_lladdr =(oal_eth_icmp6_lladdr_stru *)((oal_uint8 *)(pst_icmp6hdr + 1));
                break;
            }
            default:
                en_packet_changed = OAL_FALSE;
                break;
        }

        if ((OAL_TRUE == en_packet_changed) && (OAL_PTR_NULL != pst_eth_icmp6_lladdr))
        {
            oal_set_mac_addr(pst_eth_icmp6_lladdr->uc_addr, pst_mac_vap->auc_bssid);
            us_check_sum = hmac_psta_tx_checksum((oal_uint16)OAL_IPPROTO_ICMPV6, us_icmp6len,
                               pst_ipv6hdr->saddr.s6_addr, pst_ipv6hdr->daddr.s6_addr,16,(oal_uint8 *)pst_icmp6hdr);

            pst_icmp6hdr->icmp6_cksum = OAL_HOST2NET_SHORT(us_check_sum);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_tx_mat
 ��������  : ARP��DHCP��ICMPv6�Ȱ��ĵ�ַת�� ����ǰ��ַת������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��25��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_tx_mat(oal_netbuf_stru *pst_buf, hmac_vap_stru *pst_hmac_vap)
{
    mac_ether_header_stru  *pst_ether_header;
    mac_vap_stru           *pst_mac_vap;
    oal_uint8              *puc_eth_body;
    oal_uint16              us_ether_type;
    oal_uint8              *puc_scr_mac;
    oal_uint32              ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    oal_uint32              ul_pkt_len;
    oal_uint32              ul_ret = OAL_SUCC;

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_buf) || (OAL_PTR_NULL == pst_hmac_vap)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_mat::The input parameter of hmac_psta_tx_arp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    /* �����Ϸ��Լ��󣬻�ȡpst_buf�ĳ��� */
    ul_pkt_len = OAL_NETBUF_LEN(pst_buf);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_psta_tx_mat::The length of buf is invalid.}");
        return OAL_FAIL;
    }

    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);

    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    us_ether_type = pst_ether_header->us_ether_type;
    puc_scr_mac   = pst_ether_header->auc_ether_shost;

    if (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == us_ether_type)
    {
        return OAL_SUCC;
    }

    /* ARP����ַת�� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_ARP)  == us_ether_type)
    {
        ul_ret = hmac_psta_tx_arp_mat(pst_mac_vap, puc_eth_body, ul_pkt_len, ul_contig_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_mat::hmac_psta_tx_arp_mat return value is %d.}", ul_ret);
            return ul_ret;
        }
    }

/*lint -e778*/
    /*DHCP ����ַת�� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == us_ether_type)
    {
/*lint +e778*/
        ul_ret = hmac_psta_tx_ip_mat(pst_mac_vap,
                                         pst_ether_header,
                                         puc_eth_body,
                                         ul_pkt_len,
                                         ul_contig_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_mat::hmac_psta_tx_dhcp_mat return value is %d.}", ul_ret);
            return ul_ret;
        }
    }

    /*icmpv6 ����ַת�� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == us_ether_type)
    {
        ul_ret = hmac_psta_tx_icmpv6_mat(pst_mac_vap, puc_eth_body, ul_pkt_len, ul_contig_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_psta_tx_mat::hmac_psta_tx_icmpv6_mat return value is %d.}", ul_ret);
            return ul_ret;
        }
    }

    oal_set_mac_addr(puc_scr_mac, mac_mib_get_StationID(pst_mac_vap));

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_pause_bss
 ��������  : MAIN STA�������ʱPAUSE������UP״̬��AP
 �������  : hmac_vap_stru *pst_hmac_vap,
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��24��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 hmac_psta_pause_bss(hmac_vap_stru *pst_hmac_vap)
{
    if (!pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_psta_pause_bss::null pst_hmac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_ap_clean_bss(pst_hmac_vap);

    /* ����AP��״̬��Ϊ WAIT_START */
    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_AP_WAIT_START);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_resume_bss
 ��������  : MAIN STA�������ʱDOWN������UP״̬��AP
 �������  : hmac_vap_stru *pst_hmac_vap,
             mac_channel_stru *pst_channel,
             wlan_protocol_enum_uint8 en_proto

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��24��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 hmac_psta_resume_bss(hmac_vap_stru *pst_hmac_vap, mac_channel_stru *pst_channel, wlan_protocol_enum_uint8 en_proto)
{
    if (OAL_SUCC == hmac_chan_start_bss(pst_hmac_vap, pst_channel, en_proto))
    {
        return hmac_ap_clean_bss(pst_hmac_vap);
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : hmac_psta_proc_wait_join
 ��������  : MAIN STA�������ʱDOWN������UP״̬��AP
 �������  : hmac_vap_stru *pst_hmac_sta,
             hmac_join_req_stru *pst_join_req
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��24��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  hmac_psta_proc_wait_join(hmac_vap_stru *pst_hmac_sta, hmac_join_req_stru *pst_join_req)
{
    mac_device_stru                     *pst_mac_device;
    hmac_vap_stru                       *pst_hmac_vap_temp;
    oal_uint8                            uc_vap_idx;
    oal_dlist_head_stru                 *pst_list;
    hmac_psta_rep_stru                  *pst_rep;
    oal_uint32                           ul_ret = OAL_SUCC;

    if (!pst_hmac_sta || !pst_join_req)
    {
       OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_psta_proc_wait_join::null ptr, sta=%p join_req=%p}", pst_hmac_sta, pst_join_req);
       return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_sta->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_psta_proc_wait_join::pst_mac_device null.}");
       return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rep = hmac_psta_get_rep(pst_hmac_sta);

    // ֻ��main sta����ʱ����Ҫdown/up������
    if (!mac_is_proxysta_enabled(pst_mac_device)
    || (!mac_vap_is_msta(&pst_hmac_sta->st_vap_base_info)))
    {
        return OAL_SUCC;
    }

    // ͬdevice������bss���ŵ���Ҫ�ı�
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_hmac_vap_temp = mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (pst_hmac_vap_temp && pst_hmac_vap_temp->st_vap_base_info.en_vap_mode == WLAN_VAP_MODE_BSS_AP)
        {
            if (OAL_SUCC != hmac_psta_pause_bss(pst_hmac_vap_temp))
            {
                ul_ret = OAL_FAIL;
            }
        }
    }

    // ͬrepeater������BSSҲ��Ҫdown������ɾ���û�
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_pbss_list)
    {
        pst_hmac_vap_temp = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_hash_entry);
        if (pst_hmac_vap_temp->st_vap_base_info.uc_device_id != pst_hmac_sta->st_vap_base_info.uc_device_id)
        {
            if (OAL_SUCC != hmac_psta_pause_bss(pst_hmac_vap_temp))
            {
                ul_ret = OAL_FAIL;
            }
        }
    }

    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : hmac_psta_proc_join_result
 ��������  : MAIN STA�����ɹ���UP���б�DOWN����AP
 �������  : hmac_vap_stru *pst_hmac_sta
             oal_bool_enum_uint8 en_succ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��24��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_psta_proc_join_result(hmac_vap_stru *pst_hmac_sta, oal_bool_enum_uint8 en_succ)
{
    mac_device_stru                     *pst_mac_device;
    hmac_vap_stru                       *pst_hmac_vap_temp;
    oal_uint8                            uc_vap_idx;
    oal_dlist_head_stru                 *pst_list;
    hmac_psta_rep_stru                  *pst_rep;
    oal_uint32                           ul_ret = OAL_SUCC;

    if (!pst_hmac_sta)
    {
       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_psta_proc_join_result::pst_hmac_sta null.}");
       return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_sta->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_psta_proc_join_result::pst_mac_device null.}");
       return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rep = hmac_psta_get_rep(pst_hmac_sta);

    // ֻ��main sta����ʱ����Ҫdown/up������
    if (!mac_is_proxysta_enabled(pst_mac_device)
    || (!mac_vap_is_msta(&pst_hmac_sta->st_vap_base_info)))
    {
        return OAL_SUCC;
    }

    // ͬdevice������bss���ŵ�����Ҫ�ı�
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_hmac_vap_temp = mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (pst_hmac_vap_temp
            && (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap_temp->st_vap_base_info.en_vap_mode)
            && (pst_hmac_vap_temp->st_vap_base_info.en_vap_state == MAC_VAP_STATE_AP_WAIT_START))
        {
            if(OAL_SUCC != hmac_psta_resume_bss(pst_hmac_vap_temp, &pst_hmac_sta->st_vap_base_info.st_channel, pst_hmac_sta->st_vap_base_info.en_protocol))
            {
                ul_ret = OAL_FAIL;
            }
        }
    }

    // ͬrepeater������bss�ŵ�����Ҫ�ı�
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_rep->st_pbss_list)
    {
        pst_hmac_vap_temp = OAL_DLIST_GET_ENTRY(pst_list, hmac_vap_stru, st_psta.st_hash_entry);
        if (pst_hmac_vap_temp->st_vap_base_info.uc_device_id != pst_hmac_sta->st_vap_base_info.uc_device_id)
        {
            if (OAL_SUCC != hmac_psta_resume_bss(pst_hmac_vap_temp, OAL_PTR_NULL, WLAN_PROTOCOL_BUTT))
            {
                ul_ret = OAL_FAIL;
            }
        }
    }

    return ul_ret;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
