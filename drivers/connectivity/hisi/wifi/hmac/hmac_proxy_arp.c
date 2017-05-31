/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_proxy_arp.c
  �� �� ��   : ����
  ��    ��   : z00260280
  ��������   : 2014��7��29��
  ����޸�   :
  ��������   : PROXY ARP
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : create

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_net.h"
#include "wlan_spec.h"
#include "hmac_vap.h"
#include "hmac_ext_if.h"
#include "hmac_proxy_arp.h"
#include "hmac_rx_data.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_PROXYARP_C

/*lint -e778*/ /*lint -e572*/
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : hmac_proxy_get_mac_by_ipv4
 ��������  : ͨ��ipv4�ĵ�ַ��ȡmac
 �������  : pst_hmac_vap: hmac_vapָ��
             ul_ipv4:ipv4��ַ
 �������  : puc_mac:mac��ַ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_get_mac_by_ipv4(mac_vap_stru *pst_mac_vap, oal_uint32 ul_ipv4, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv4_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_entry;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{mac_vap_find_user_by_macaddr::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_user_hash_value = HMAC_PROXY_IPV4_HASH(ul_ipv4);

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv4_hash_stru *)pst_entry;
        if (pst_hash->ul_ipv4 != ul_ipv4)
        {
            continue;
        }

        oal_memcopy(puc_mac, pst_hash->auc_mac, WLAN_MAC_ADDR_LEN);

        return OAL_SUCC;
    }

    return OAL_FAIL;
}


/*****************************************************************************
 �� �� ��  : hmac_proxy_remove_ipv4
 ��������  : ��ipv4�ĵ�ַ��hash����ɾ��
 �������  : pst_hmac_vap: hmac_vapָ��
             ul_ipv4:ipv4��ַ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_remove_ipv4(mac_vap_stru *pst_mac_vap, oal_uint32 ul_ipv4)
{
    oal_uint32                  ul_user_hash_value;
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv4_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_ipv4::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num)
    {
        return OAL_SUCC;
    }

    ul_user_hash_value = HMAC_PROXY_IPV4_HASH(ul_ipv4);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv4_hash_stru *)pst_entry;

        if (pst_hash->ul_ipv4 != ul_ipv4)
        {
            continue;
        }
        oal_dlist_delete_entry(pst_entry);
        OAL_MEM_FREE(pst_hash, OAL_TRUE);
        pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num--;
        return OAL_SUCC;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_proxy_add_ipv4
 ��������  : ��ipv4�ĵ�ַ����hash������¼��Ӧ��mac��ַ
 �������  : pst_hmac_vap: hmac_vapָ��
             ul_ipv4:ipv4��ַ
             puc_mac:mac��ַ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_add_ipv4(mac_vap_stru *pst_mac_vap, oal_uint32 ul_ipv4, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv4_hash_stru  *pst_hash;
    oal_err_code_enum_uint32    en_exist;
    oal_uint8                   auc_mac[OAL_MAC_ADDR_LEN];

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_add_ipv4::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ѯ�Ƿ���� */
    en_exist = hmac_proxy_get_mac_by_ipv4(pst_mac_vap, ul_ipv4, auc_mac);
    if (OAL_SUCC == en_exist)
    {
        if (!oal_memcmp(auc_mac, puc_mac, OAL_MAC_ADDR_LEN))
        {
            return OAL_SUCC;
        }
        /* ������Բ�ͬ��mac����ǰ���¼�Ľ��ɾ�����������̽��µĽ����� */
        hmac_proxy_remove_ipv4(pst_mac_vap, ul_ipv4);
    }

    if (MAC_VAP_USER_HASH_MAX_VALUE <= pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* �����ڴ� */
    pst_hash = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxy_ipv4_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "hmac_proxy_add_ipv4 err! melloc err!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д */
    pst_hash->ul_ipv4 = ul_ipv4;
    oal_memcopy(pst_hash->auc_mac, puc_mac, OAL_MAC_ADDR_LEN);

    /* ����hash�� */
    ul_user_hash_value = HMAC_PROXY_IPV4_HASH(ul_ipv4);
    oal_dlist_add_head(&(pst_hash->st_entry), &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_user_hash_value]));
    pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num++;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_get_mac_by_ipv6
 ��������  : ͨ��ipv6�ĵ�ַ��ȡmac
 �������  : pst_hmac_vap: hmac_vapָ��
             puc_ipv6:ipv6��ַ
 �������  : puc_mac:mac��ַ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_get_mac_by_ipv6(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv6_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_entry;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == pst_ipv6)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_get_mac_by_ipv6::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_user_hash_value = HMAC_PROXY_IPV6_HASH(pst_ipv6);

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv6_hash_stru *)pst_entry;

        if (oal_memcmp(pst_ipv6, &pst_hash->st_ipv6, OAL_SIZEOF(oal_in6_addr)))
        {
            continue;
        }
        oal_memcopy(puc_mac, pst_hash->auc_mac, WLAN_MAC_ADDR_LEN);
        return OAL_SUCC;
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_remove_ipv6
 ��������  : ��ipv6�ĵ�ַ��hash����ɾ��
 �������  : pst_hmac_vap: hmac_vapָ��
             ul_ipv6:ipv6��ַ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_remove_ipv6(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6)
{
    oal_uint32                  ul_user_hash_value;
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv6_hash_stru  *pst_hash;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_ipv4::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num)
    {
        return OAL_SUCC;
    }

    ul_user_hash_value = HMAC_PROXY_IPV6_HASH(pst_ipv6);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_user_hash_value]))
    {
        pst_hash = (hmac_proxy_ipv6_hash_stru *)pst_entry;

        if (oal_memcmp(pst_ipv6, &pst_hash->st_ipv6, OAL_SIZEOF(oal_in6_addr)))
        {
            continue;
        }
        oal_dlist_delete_entry(pst_entry);
        OAL_MEM_FREE(pst_hash, OAL_TRUE);
        pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num--;
        return OAL_SUCC;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_proxy_add_ipv6
 ��������  : ��ipv6�ĵ�ַ����hash������¼��Ӧ��mac��ַ
 �������  : pst_hmac_vap: hmac_vapָ��
             puc_ipv6:ipv6��ַ
             puc_mac:mac��ַ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_add_ipv6(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6, oal_uint8 *puc_mac)
{
    oal_uint32                  ul_user_hash_value;
    hmac_proxy_ipv6_hash_stru  *pst_hash;
    oal_err_code_enum_uint32    en_exist;
    oal_uint8                   auc_mac[OAL_MAC_ADDR_LEN];
    oal_uint8                   auc_ipv6_zero_addr[16] = {0};

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
                  || (OAL_PTR_NULL == puc_mac)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_add_ipv6::param null.}");

        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP;
    }

    if (!oal_memcmp(auc_ipv6_zero_addr, pst_ipv6, OAL_SIZEOF(oal_in6_addr)))
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP;
    }

    /* ��ѯ�Ƿ����,������ڣ����Ƿ�����ͬһ��mac */
    en_exist = hmac_proxy_get_mac_by_ipv6(pst_mac_vap, pst_ipv6, auc_mac);
    if (OAL_SUCC == en_exist)
    {
        if (!oal_memcmp(auc_mac, puc_mac, OAL_MAC_ADDR_LEN))
        {
            return OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP;
        }

        /* ������Բ�ͬ��mac����ǰ���¼�Ľ��ɾ�����������̽��µĽ����� */
        hmac_proxy_remove_ipv6(pst_mac_vap, pst_ipv6);
    }

    if (MAC_VAP_USER_HASH_MAX_VALUE <= pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num)
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP;
    }

    /* ���� */
    pst_hash = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_proxy_ipv6_hash_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hash)
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP;
    }

    /* ��д */
    pst_hash->st_ipv6 = *pst_ipv6;
    oal_memcopy(pst_hash->auc_mac, puc_mac, OAL_MAC_ADDR_LEN);

    /* ����hash�� */
    ul_user_hash_value  = 0;
    ul_user_hash_value = HMAC_PROXY_IPV6_HASH(&pst_hash->st_ipv6);
    oal_dlist_add_head(&(pst_hash->st_entry), &pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_user_hash_value]);
    pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num++;
    return OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_remove_mac
 ��������  : ͨ��mac��ַ����Ӧipv4��ipv6 ���ɾ��
 �������  : pst_mac_vap: mac_vapָ��
             puc_mac:mac��ַ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_remove_mac(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac)
{
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv4_hash_stru  *pst_hash_ipv4;
    hmac_proxy_ipv6_hash_stru  *pst_hash_ipv6;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;
    oal_uint32                  ul_loop = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_mac::vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_LIKELY(OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp))
    {
        OAM_INFO_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_remove_mac::proxyarp null.}");
        return OAL_SUCC;
    }

    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
    {
        return OAL_SUCC;
    }

    if (0 < pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num)
    {
        for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
        {
            OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]))
            {
                pst_hash_ipv6 = (hmac_proxy_ipv6_hash_stru *)pst_entry;
                if (oal_memcmp(puc_mac, &pst_hash_ipv6->auc_mac, OAL_MAC_ADDR_LEN))
                {
                    continue;
                }

                oal_dlist_delete_entry(pst_entry);
                OAL_MEM_FREE(pst_hash_ipv6, OAL_TRUE);
                pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num--;
                break;
            }
        }
    }

    if (0 < pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num)
    {
        for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
        {
            OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]))
            {
                pst_hash_ipv4 = (hmac_proxy_ipv4_hash_stru *)pst_entry;
                if (oal_memcmp(puc_mac, &pst_hash_ipv4->auc_mac, OAL_MAC_ADDR_LEN))
                {
                    continue;
                }

                oal_dlist_delete_entry(pst_entry);
                OAL_MEM_FREE(pst_hash_ipv4, OAL_TRUE);
                pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num--;
                break;
            }
        }
    }
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_proxy_debug_record
 ��������  : ��¼������Ϣ
 �������  : pst_mac_vap: hmac_vapָ��
             puc_mac_src: macָ��
             puc_mac_dst: macָ��
             uc_dir:֡�ķ��ͷ��� 0-�տ� 1-eth
             uc_type:֡����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
oal_void hmac_proxy_debug_record(mac_vap_stru *pst_mac_vap, mac_ether_header_stru *pst_eth_hdr, oal_uint16 us_type, oal_err_code_enum_uint32 en_rst)
{
    mac_vap_proxyarp_stru           *pst_vap_proxyarp;
    oal_uint32                       ul_idx;
    if(OAL_ERR_CODE_PROXY_OTHER_INCOMP == en_rst)
    {
        return;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp)
    {
        return;
    }

    pst_vap_proxyarp = pst_mac_vap->pst_vap_proxyarp;
    ul_idx = pst_vap_proxyarp->us_idx_cur % MAC_VAP_USER_HASH_MAX_VALUE;

    /* ��¼��̫ͷ */
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].st_eth_hdr = *pst_eth_hdr;
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].us_type = us_type;
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].en_rst = en_rst;
    pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_idx].us_proxy_num = pst_vap_proxyarp->us_idx_cur;
    pst_vap_proxyarp->us_idx_cur++;
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_proxy_arp_rcv_req
 ��������  : ������յ���arp req
 �������  : pst_hmac_vap: hmac_vapָ��
             pst_arp_hdr:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_arp_rcv_req(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, oal_eth_arphdr_stru *pst_arp_hdr)
{

    oal_uint32                  ul_src_ipv4 = 0;
    oal_uint8                   auc_src_mac[ETHER_ADDR_LEN];
    oal_uint32                  ul_tgt_ipv4 = 0;
    oal_uint8                   auc_tgt_mac[ETHER_ADDR_LEN];
    oal_uint16                  us_usr_idx;
    oal_err_code_enum_uint32    en_err = OAL_SUCC;
    oal_netbuf_stru            *pst_netbuff;
    oal_uint32                  ul_ret = 0;

    oal_err_code_enum_uint32    en_rst = 0;
    mac_ether_header_stru       st_eth_hdr;
    oal_memcopy(auc_src_mac, pst_arp_hdr->auc_ar_sha, ETHER_ADDR_LEN);
    oal_memcopy(&ul_src_ipv4, pst_arp_hdr->auc_ar_sip, ETH_SENDER_IP_ADDR_LEN);
    oal_memcopy(&ul_tgt_ipv4, pst_arp_hdr->auc_ar_tip, ETH_TARGET_IP_ADDR_LEN);

    /* GARP,���е�ַѧϰ */
    if (ul_src_ipv4 == ul_tgt_ipv4)
    {
        //hmac_proxy_learn();
        if (OAL_SUCC != mac_vap_find_user_by_macaddr(pst_mac_vap, auc_src_mac, &us_usr_idx))
        {
            return OAL_ERR_CODE_PROXY_ARP_LEARN_USR_NOTEXIST_COMP;
        }

        hmac_proxy_add_ipv4(pst_mac_vap, ul_src_ipv4, auc_src_mac);

        return OAL_ERR_CODE_PROXY_ARP_LEARN_USR_COMP;
    }

    /* ��Ŀ�ĵ�ַ���Ǳ�BSS��ARP REQ���˵� */
    en_err = hmac_proxy_get_mac_by_ipv4(pst_mac_vap, ul_tgt_ipv4, auc_tgt_mac);
    if (OAL_SUCC != en_err)
    {
        return OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP;
    }


    pst_netbuff = oal_arp_create(OAL_ARPOP_REPLY, ETHER_TYPE_ARP, ul_src_ipv4, pst_dev, ul_tgt_ipv4,
                                         auc_src_mac, auc_tgt_mac, auc_src_mac);
    if (!pst_netbuff)
    {
        return OAL_ERR_CODE_PROXY_ARP_CREATE_FAIL_COMP;
    }

    pst_netbuff->dev = pst_dev;

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    oal_netbuf_pull(pst_netbuff, 14);
    hmac_rx_report_eth_frame(pst_mac_vap, pst_netbuff);
    oal_netbuf_push(pst_netbuff, 14);
#endif


    /* ��¼һ�£�����������Ĵ�ӡ */
    st_eth_hdr = *(mac_ether_header_stru *)oal_netbuf_data(pst_netbuff);

    /* �ҵ��û���ʹ�ÿտڷ��� */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, auc_src_mac, &us_usr_idx))
    {
        /* dataָ��ָ�������̫ͷ */
        ul_ret = hmac_tx_lan_to_wlan(pst_mac_vap, pst_netbuff);
        if (OAL_SUCC != ul_ret)
        {

            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_arp_rcv_req 2wlan Err[%u]!!}", ul_ret);
            oal_netbuf_free(pst_netbuff);
            pst_netbuff = OAL_PTR_NULL;
        }

        en_rst = OAL_ERR_CODE_PROXY_ARP_REPLY2BSS_COMP;
    }
    else
    {
        /* �͸����ţ���Ҫpullһ�£���dataָ��ָ��arpͷ */
        OAL_NETBUF_PROTOCOL(pst_netbuff) = oal_eth_type_trans(pst_netbuff, pst_dev);

        /* ��������*/
        ul_ret = (oal_uint32)oal_netif_rx(pst_netbuff);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_arp_rcv_req 2br Err[%u]!!}", ul_ret);
        }

        en_rst = OAL_ERR_CODE_PROXY_ARP_REPLY2ETH_COMP;

    }

#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, OAL_ARPOP_REPLY, en_rst);
#endif
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_arp_rcv_req! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        OAL_ARPOP_REPLY,
                        en_rst);

    return en_rst;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_arp_rcv_reply
 ��������  : ������յ���arp reply
 �������  : pst_hmac_vap: hmac_vapָ��
             oal_netbuf_stru:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_arp_rcv_reply(mac_vap_stru *pst_mac_vap, oal_eth_arphdr_stru *pst_arp_hdr, oal_uint8 uc_is_mcst)
{
    oal_uint16                  us_usr_idx = 0;
    if (uc_is_mcst)
    {
        return OAL_ERR_CODE_PROXY_ARP_REPLY_MCAST_COMP;
    }

    /* ����ӿ����߲���GARP,ͨ��arp reply��arp reply���Ͷ˵�ip��mac������ */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, pst_arp_hdr->auc_ar_sha, &us_usr_idx))
    {
        hmac_proxy_add_ipv4(pst_mac_vap, *(oal_uint32 *)pst_arp_hdr->auc_ar_sip, pst_arp_hdr->auc_ar_sha);
    }

    return OAL_ERR_CODE_PROXY_ARP_REPLY_INCOMP;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_arp
 ��������  : ������յ���arp req��arp reply
 �������  : pst_hmac_vap: hmac_vapָ��
             oal_netbuf_stru:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_arp(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru       *pst_ether_hdr; /* ��̫��ͷ */
    oal_uint32                   ul_arp_hdr_len = 0;
    oal_eth_arphdr_stru         *pst_arp_hdr;
    oal_uint8                    uc_is_mcst = 0;
    mac_ether_header_stru       st_eth_hdr;

    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    pst_arp_hdr     = (oal_eth_arphdr_stru *)(pst_ether_hdr + 1);

    ul_arp_hdr_len       = OAL_SIZEOF(oal_eth_arphdr_stru) + OAL_SIZEOF(mac_ether_header_stru);

    /* �˴��ж�skb�У��Ƿ��Ѿ����㹻�Ŀռ䱣����eth hdr + arp hdr����Ϣ */
    if (!oal_pskb_may_pull(pst_buf, ul_arp_hdr_len))
    {
        return OAL_ERR_CODE_PROXY_ARP_INVLD_SKB_INCOMP;
    }

    st_eth_hdr = *(mac_ether_header_stru *)oal_netbuf_data(pst_buf);
#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, pst_arp_hdr->us_ar_op, 0);
#endif
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_arp! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        pst_arp_hdr->us_ar_op,
                        0);

    if (OAL_HOST2NET_SHORT(OAL_ARPOP_REQUEST) == pst_arp_hdr->us_ar_op)
    {
        return hmac_proxy_arp_rcv_req(pst_mac_vap, pst_dev, pst_arp_hdr);
    }
    else if (OAL_HOST2NET_SHORT(OAL_ARPOP_REPLY) == pst_arp_hdr->us_ar_op)
    {
        uc_is_mcst = ETHER_IS_MULTICAST(pst_ether_hdr->auc_ether_dhost);
        return hmac_proxy_arp_rcv_reply(pst_mac_vap, pst_arp_hdr, uc_is_mcst);
    }

    return OAL_ERR_CODE_PROXY_ARP_NOT_REQ_REPLY_INCOMP;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_nd_learn_from_ns
 ��������  : ͨ��DADѧϰ��ַ
 �������  : pst_hmac_vap: hmac_vapָ��
             oal_netbuf_stru:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd_learn_from_ns(mac_vap_stru *pst_mac_vap, oal_in6_addr *pst_ipv6_src, oal_uint8 *puc_mac_src)
{
    oal_uint16                  us_usr_idx = 0;
    oal_uint8                   auc_mac[ETHER_ADDR_LEN];
    oal_err_code_enum_uint32    en_err = OAL_SUCC;

    if (OAL_SUCC != mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_src, &us_usr_idx))
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_NOTEXIST_COMP;
    }

    /* ���ipv6�ĵ�ַ�Ѿ�����,����mac��ַ����ȣ��򽫴�֡���ͳ�ȥ������DAD��� */
    en_err = hmac_proxy_get_mac_by_ipv6(pst_mac_vap, pst_ipv6_src, auc_mac);
    if ((OAL_SUCC == en_err)
        && (oal_memcmp(puc_mac_src, auc_mac, OAL_MAC_ADDR_LEN)))
    {
        return OAL_ERR_CODE_PROXY_ND_LEARN_USR_ALREADY_EXIST_INCOMP;
    }

    return hmac_proxy_add_ipv6(pst_mac_vap, pst_ipv6_src, puc_mac_src);
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_create_na
 ��������  : ����NA�����Դ���ظ�NS
 �������  : pst_hmac_vap: hmac_vapָ��
             pst_ether_hdr:ָ����յ�skb����̫ͷ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 ˵     �� :
 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
 oal_netbuf_stru *hmac_proxy_create_na(oal_net_device_stru *pst_net_dev, oal_uint8 *puc_src_mac, oal_uint8 *puc_dst_mac, oal_uint8 *puc_src_ipv6, oal_uint8 *puc_dst_ipv6)
{
    oal_netbuf_stru             *pst_netbuff = OAL_PTR_NULL;
    oal_uint32                   ul_size = 0;
    oal_ipv6hdr_stru            *pst_ipv6;
    oal_nd_msg_stru             *pst_nd;

    /* sizeof(oal_nd_msg_stru)��ʵ�ʶ���4�ֽڣ�����8�ֽ�����ΪNA��option��8�ֽڡ�add by:w00316376 */
    ul_size = OAL_LL_ALLOCATED_SPACE(pst_net_dev) + sizeof(oal_ipv6hdr_stru) + (sizeof(oal_nd_msg_stru) - 4) + 8;
    pst_netbuff  = oal_netbuf_alloc(ul_size, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_PTR_NULL == pst_netbuff)
    {
        return OAL_PTR_NULL;
    }

    pst_netbuff->dev = pst_net_dev;
    pst_netbuff->protocol = OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6);
    oal_netbuf_reserve(pst_netbuff, OAL_LL_ALLOCATED_SPACE(pst_net_dev));

    pst_ipv6 = (oal_ipv6hdr_stru *)oal_netbuf_put(pst_netbuff, OAL_SIZEOF(oal_ipv6hdr_stru));

    /* skb->len����nd_msg�ĳ��� */
    oal_netbuf_put(pst_netbuff, (sizeof(oal_nd_msg_stru) - 4) + 8);
    pst_nd = (oal_nd_msg_stru *)(pst_ipv6 + 1);

    /* 1. ��д��̫ͷ */
    if (oal_dev_hard_header(pst_netbuff, pst_netbuff->dev, ETHER_TYPE_IPV6, puc_dst_mac,
                                        puc_src_mac, pst_netbuff->len) < 0)
    {
        oal_netbuf_free(pst_netbuff);
        return OAL_PTR_NULL;
    }

    /* 2. ��дIPV6ͷ */
    *(oal_uint32 *)pst_ipv6 = OAL_HOST2NET_LONG(0x60000000);
    pst_ipv6->payload_len = OAL_HOST2NET_SHORT((sizeof(oal_nd_msg_stru) - 4) + 8);
    pst_ipv6->nexthdr = OAL_IPPROTO_ICMPV6;
    pst_ipv6->hop_limit = 0xff;
    oal_ipv6_addr_copy(&pst_ipv6->daddr, (oal_in6_addr *)puc_dst_ipv6);
    oal_ipv6_addr_copy(&pst_ipv6->saddr, (oal_in6_addr *)puc_src_ipv6);

    /* 3. ��дICMPV6 �ھӷ���Э���NA*/
    OAL_MEMZERO(&pst_nd->icmph, OAL_SIZEOF(oal_icmp6hdr_stru));
    pst_nd->icmph.icmp6_type = OAL_NDISC_NEIGHBOUR_ADVERTISEMENT;
    pst_nd->icmph.icmp6_solicited = 1;
    oal_ipv6_addr_copy(&pst_nd->target, (oal_in6_addr *)puc_src_ipv6);
    /* ICMPv6 ѡ�� */
    pst_nd->opt[0] = OAL_ND_OPT_TARGET_LL_ADDR;
    /*lint -e415*/ /*lint -e416*/
    pst_nd->opt[1] = 1;
    oal_memcopy(&pst_nd->opt[2], puc_src_mac, OAL_MAC_ADDR_LEN);
    /*lint +e415*/ /*lint +e416*/
    pst_nd->icmph.icmp6_cksum = oal_csum_ipv6_magic(&pst_ipv6->saddr,
                &pst_ipv6->daddr, (OAL_SIZEOF(*pst_nd) - 4) + 8, OAL_IPPROTO_ICMPV6,
                oal_csum_partial(&pst_nd->icmph, (OAL_SIZEOF(*pst_nd) - 4) + 8, 0));

    return pst_netbuff;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_get_mac_from_opt
 ��������  : ��icmpv6 option�л�ȡipv6��ַ
 �������  : puc_opt:  ipmpv6 optionָ��
             l_optlen: ipmpv6 option����
             en_src:   ��ʶ��ȡԴ��·��ַ����Ŀ����·��ַ 1-Դ 0-Ŀ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 ˵     �� :
 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint  -e574*/
oal_uint8 *hmac_proxy_get_mac_from_opt(oal_uint8 *puc_opt, oal_int32 l_optlen, oal_bool_enum_uint8 en_src)
{
    oal_nd_opt_hdr *pst_ndopt;
    oal_int32       l_ndoptlen;
    oal_uint32      ul_offset;
    oal_int32       l_optlen_tmp;

    pst_ndopt = (oal_nd_opt_hdr *)puc_opt;
    l_optlen_tmp = l_optlen;

    while (0 < l_optlen_tmp)
    {
        if (l_optlen_tmp < (oal_int32)OAL_SIZEOF(oal_nd_opt_hdr))
        {
            return OAL_PTR_NULL;
        }
        l_ndoptlen = pst_ndopt->nd_opt_len << 3;
        if (l_optlen_tmp < l_ndoptlen || l_ndoptlen == 0)
        {
            return OAL_PTR_NULL;
        }

        switch (pst_ndopt->nd_opt_type)
        {
            case OAL_ND_OPT_TARGET_LL_ADDR: /* NA��ʹ�� */
            {
                if (!en_src)
                {
                    return (oal_uint8 *)(pst_ndopt + 1);
                }

                break;
            }

            /* �����ߵ���·���ַ */
            case OAL_ND_OPT_SOURCE_LL_ADDR:/* NS��ʹ�� */
            {
                if (en_src)
                {
                    return (oal_uint8 *)(pst_ndopt + 1);
                }

                break;
            }
            default:
            {
                OAM_WARNING_LOG1(0, OAM_SF_PROXYARP, "{hmac_proxy_get_mac_from_opt::type [%d].}", pst_ndopt->nd_opt_type);
                break;
            }
        }

        l_optlen_tmp -= l_ndoptlen;
        ul_offset = (oal_uint32)l_ndoptlen;
        pst_ndopt = (oal_nd_opt_hdr *)((oal_uint8 *)pst_ndopt + ul_offset);
    }

    return OAL_PTR_NULL;
}
/*lint  +e574*/

/*****************************************************************************
 �� �� ��  : hmac_proxy_nd_rcv_ns
 ��������  : ������յ���NS
 �������  : pst_hmac_vap: hmac_vapָ��
             oal_netbuf_stru:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 ˵     �� :����NAʱ��ע��: NSԴ->NAĿ��
                            NSĿ��->NAԴ
 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd_rcv_ns(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, mac_ether_header_stru *pst_ether_hdr, oal_int32 l_opt_len)
{
    oal_ipv6hdr_stru        *pst_ipv6_hdr;
    oal_int32                l_src_type;
    oal_int32                l_dst_type;
    oal_nd_msg_stru         *pst_msg;
    oal_uint8               *pst_src_mac;
    oal_uint8                ast_dst_mac[ETHER_ADDR_LEN];
    oal_netbuf_stru         *pst_netbuff;
    oal_uint16               us_idx;
    oal_uint32               ul_ret;
    oal_int32                l_netifrx_rst;
    oal_err_code_enum_uint32 en_rst;
    mac_ether_header_stru    st_eth_hdr;

    pst_ipv6_hdr        = (oal_ipv6hdr_stru *)(pst_ether_hdr + 1);
    l_src_type          = oal_ipv6_addr_type(&pst_ipv6_hdr->saddr);
    l_dst_type          = oal_ipv6_addr_type(&pst_ipv6_hdr->daddr);
    pst_msg             = (oal_nd_msg_stru *)(pst_ipv6_hdr + 1);

    /* DAD��� */
    if ((l_src_type == (oal_int32)OAL_IPV6_ADDR_ANY) && (l_dst_type & (oal_int32)OAL_IPV6_ADDR_MULTICAST))
    {
        return hmac_proxy_nd_learn_from_ns(pst_mac_vap, &pst_msg->target, pst_ether_hdr->auc_ether_shost);
    }

    /* ��ȡNS��icmpv6ѡ����Я����mac��ַ������֡�����ߵ�mac��ַ */
    pst_src_mac = hmac_proxy_get_mac_from_opt(pst_msg->opt, l_opt_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_src_mac)
    {
        return OAL_ERR_CODE_PROXY_ND_NS_OPT_INVLD_COMP;
    }

    if (OAL_SUCC != hmac_proxy_get_mac_by_ipv6(pst_mac_vap, &pst_msg->target, ast_dst_mac))
    {
        return OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP;
    }

    /* ����NA*/
    pst_netbuff = hmac_proxy_create_na(pst_dev, ast_dst_mac, pst_src_mac, (oal_uint8 *)&pst_msg->target, (oal_uint8 *)&pst_ipv6_hdr->saddr);
    if (OAL_PTR_NULL == pst_netbuff)
    {
        return OAL_ERR_CODE_PROXY_ND_NS_CREATE_NA_FAIL_COMP;
    }

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    oal_netbuf_pull(pst_netbuff, 14);
    hmac_rx_report_eth_frame(pst_mac_vap, pst_netbuff);
    oal_netbuf_push(pst_netbuff, 14);
#endif

    st_eth_hdr = *(mac_ether_header_stru *)oal_netbuf_data(pst_netbuff);

    /* û�ҵ���skb���ţ��ҵ��˾�ֱ�ӿտڷ��� */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, pst_src_mac, &us_idx))
    {
        ul_ret = hmac_tx_lan_to_wlan(pst_mac_vap, pst_netbuff);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_nd_rcv_ns 2wlan Err[%u]!!}", ul_ret);

            oal_netbuf_free(pst_netbuff);

            pst_netbuff = OAL_PTR_NULL;
        }

        en_rst = OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2BSS_COMP;
    }
    else
    {
        OAL_NETBUF_PROTOCOL(pst_netbuff) = oal_eth_type_trans(pst_netbuff, pst_dev);

        l_netifrx_rst = oal_netif_rx(pst_netbuff);
        if (OAL_SUCC != l_netifrx_rst)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "{hmac_proxy_nd_rcv_ns 2br Err[%d]!!}", l_netifrx_rst);
        }

        en_rst = OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2ETH_COMP;
    }

#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, OAL_NDISC_NEIGHBOUR_ADVERTISEMENT, en_rst);
#endif
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_nd_rcv_ns! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        OAL_NDISC_NEIGHBOUR_ADVERTISEMENT,
                        en_rst);

    return en_rst;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_ipv6_addr_is_mcast
 ��������  : �ж�ipv6�ĵ�ַ�ǲ����鲥��ַ
 �������  : pst_hmac_vap: hmac_vapָ��
             pst_buf:      skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 ˵    ��  :ipv6��ַ ff02:xxxx:xxxx  ���Ϊff����ʾ�鲥

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 hmac_proxy_ipv6_addr_is_mcast(oal_in6_addr *pst_addr)
{
    return (pst_addr->s6_addr32[0] & OAL_HOST2NET_LONG(0xFF000000)) == OAL_HOST2NET_LONG(0xFF000000);
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_nd_rcv_na
 ��������  : ����NA
 �������  : pst_hmac_vap: hmac_vapָ��
             pst_buf:      skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 ˵    ��  : 1.NA��Ӧ��������ʱS��λ,���Դ����Բ�����·��ַ
             2.NA��Ӧ�鲥����ʱ,S����λ��target��ɶಥ������Ҫ����·��ַ
 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd_rcv_na(mac_vap_stru *pst_mac_vap, mac_ether_header_stru *pst_ether_hdr, oal_int32 l_opt_len)
{
    oal_ipv6hdr_stru            *pst_ipv6_hdr;
    oal_icmp6hdr_stru           *pst_icmp6;
    oal_bool_enum_uint8          en_solicited;
    oal_nd_msg_stru             *pst_nd;
    oal_uint8                   *puc_src_mac;
    oal_err_code_enum_uint32     en_err;
    oal_uint16                   us_usr_idx = 0;

    pst_ipv6_hdr        = (oal_ipv6hdr_stru *)(pst_ether_hdr + 1);
    pst_icmp6           = (oal_icmp6hdr_stru *)(pst_ipv6_hdr + 1);
    pst_nd              = (oal_nd_msg_stru *)pst_icmp6;

    /* S����Ӧ�鲥nsʱ��Ӧ����λ */
    if ((pst_nd->icmph.icmp6_dataun.u_nd_advt.solicited)
    && hmac_proxy_ipv6_addr_is_mcast(&pst_nd->target))
    {
        return OAL_ERR_CODE_PROXY_ND_NA_INVLD_COMP;
    }

    en_solicited = (pst_nd->icmph.icmp6_dataun.u_nd_advt.solicited) && !(hmac_proxy_ipv6_addr_is_mcast(&pst_nd->target));

    puc_src_mac = hmac_proxy_get_mac_from_opt(pst_nd->opt, l_opt_len, OAL_FALSE);
    if (OAL_PTR_NULL == puc_src_mac)
    {
        if (en_solicited)
        {
            return OAL_ERR_CODE_PROXY_ND_NA_UCAST_NOT_LLA_INCOMP;

        }

        return OAL_ERR_CODE_PROXY_ND_NA_MCAST_NOT_LLA_COMP;
    }
    /* ��NA��ѧϰһ�µ�ַ */
    if (OAL_SUCC == mac_vap_find_user_by_macaddr(pst_mac_vap, puc_src_mac, &us_usr_idx))
    {
        en_err = hmac_proxy_add_ipv6(pst_mac_vap, &pst_nd->target, puc_src_mac);
        if(OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP != en_err)
        {
            return en_err;
        }
    }

    if (en_solicited)
    {
        return OAL_ERR_CODE_PROXY_ND_NA_SOLICITED_INCOMP;
    }

    return OAL_ERR_CODE_PROXY_ND_NA_UNSOLICITED_COMP;

}

/*****************************************************************************
 �� �� ��  : hmac_proxy_nd
 ��������  : ������յ���NS��NA
 �������  : pst_hmac_vap: hmac_vapָ��
             oal_netbuf_stru:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 hmac_proxy_nd(mac_vap_stru *pst_mac_vap, oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru       *pst_ether_hdr; /* ��̫��ͷ */
    oal_ipv6hdr_stru            *pst_ipv6_hdr;
    oal_icmp6hdr_stru           *pst_icmp6;
    oal_uint32                   ul_hdr_len;
    oal_uint32                   ul_opt_len;         /* icmpv6ѡ��ĳ��� */
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    pst_ipv6_hdr    = (oal_ipv6hdr_stru *)(pst_ether_hdr + 1);
    pst_icmp6       = (oal_icmp6hdr_stru *)(pst_ipv6_hdr + 1);

    ul_hdr_len       = OAL_SIZEOF(oal_ipv6hdr_stru) + OAL_SIZEOF(mac_ether_header_stru);
    if (!oal_pskb_may_pull(pst_buf, ul_hdr_len))
    {
        return OAL_ERR_CODE_PROXY_ND_INVLD_SKB1_INCOMP;
    }

    ul_opt_len = pst_buf->len - ul_hdr_len - (OAL_SIZEOF(oal_nd_msg_stru) - 4);

    if (OAL_IPPROTO_ICMPV6 != pst_ipv6_hdr->nexthdr)
    {
        return OAL_ERR_CODE_PROXY_ND_NOT_ICMPV6_INCOMP;
    }

    ul_hdr_len += OAL_SIZEOF(oal_icmp6hdr_stru);
    if (!oal_pskb_may_pull(pst_buf, ul_hdr_len))
    {
        return OAL_ERR_CODE_PROXY_ND_INVLD_SKB2_INCOMP;
    }

    if ((OAL_NDISC_NEIGHBOUR_SOLICITATION == pst_icmp6->icmp6_type))
    {
        return hmac_proxy_nd_rcv_ns(pst_mac_vap, pst_dev, pst_ether_hdr, (oal_int32)ul_opt_len);
    }
    else if (OAL_NDISC_NEIGHBOUR_ADVERTISEMENT == pst_icmp6->icmp6_type)
    {
        return hmac_proxy_nd_rcv_na(pst_mac_vap, pst_ether_hdr, (oal_int32)ul_opt_len);
    }

    return OAL_ERR_CODE_PROXY_ND_ICMPV6_NOT_NSNA_INCOMP;

}

/*****************************************************************************
 �� �� ��  : hmac_proxy_is_need_drop
 ��������  : ���ݴ���������Ƿ�Ҫ�������skb�ͷŵ�
 �������  : en_rst-������
 �������  : ��
 �� �� ֵ  : 0/1--����Ҫ�ͷ�/��Ҫ�ͷ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_proxy_is_need_drop(oal_err_code_enum_uint32 en_rst)
{
    oal_bool_enum_uint8      en_is_need_drop = OAL_FALSE;

    switch (en_rst)
    {
        case OAL_ERR_CODE_PROXY_ARP_LEARN_USR_COMP:
        //case OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY2BSS_COMP:
        case OAL_ERR_CODE_PROXY_ARP_CREATE_FAIL_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY2ETH_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY_MCAST_COMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP:
        case OAL_ERR_CODE_PROXY_ND_NS_OPT_INVLD_COMP:
        //case OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP:
        case OAL_ERR_CODE_PROXY_ND_NS_CREATE_NA_FAIL_COMP:
        case OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2BSS_COMP:
		case OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2ETH_COMP:
        case OAL_ERR_CODE_PROXY_ARP_LEARN_USR_NOTEXIST_COMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_NOTEXIST_COMP:		/* �˴���A�������е㲻һ��,A�˴���drop��������������� */
        case OAL_ERR_CODE_PROXY_ND_NA_INVLD_COMP:
        case OAL_ERR_CODE_PROXY_ND_NA_MCAST_NOT_LLA_COMP:
        case OAL_ERR_CODE_PROXY_ND_NA_UNSOLICITED_COMP:
        {
           en_is_need_drop = OAL_TRUE;
           break;
        }
        case OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP:
        case OAL_ERR_CODE_PROXY_ARP_REPLY_INCOMP:
        case OAL_ERR_CODE_PROXY_ARP_INVLD_SKB_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_ALREADY_EXIST_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP:
        case OAL_ERR_CODE_PROXY_ARP_NOT_REQ_REPLY_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NA_UCAST_NOT_LLA_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NA_DUP_ADDR_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NA_SOLICITED_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_INVLD_SKB1_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NOT_ICMPV6_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_INVLD_SKB2_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_ICMPV6_NOT_NSNA_INCOMP:
        case OAL_ERR_CODE_PROXY_OTHER_INCOMP:
        case OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP:
        {
            en_is_need_drop = OAL_FALSE;
            break;
        }
        default:
        {
            break;
        }
    }
    return en_is_need_drop;
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_arp_proc
 ��������  : AP����ARP��ND���������ں���
 �������  : pst_mac_vap: mac_vapָ��
             oal_netbuf_stru:skbָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_proxy_arp_proc(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru      *pst_ether_hdr; /* ��̫��ͷ */
    oal_uint16                  us_ether_type;
    oal_err_code_enum_uint32    en_rst = OAL_SUCC;
    mac_vap_stru               *pst_mac_vap;
#ifdef _PRE_DEBUG_MODE
    mac_ether_header_stru       st_eth_hdr;
#endif

    OAM_INFO_LOG0(0, OAM_SF_PROXYARP, "{hmac_proxy_arp_proc!}");
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    us_ether_type      = pst_ether_hdr->us_ether_type;

#ifdef _PRE_DEBUG_MODE
    /* ����netbuff�п��ܻᱻ�ͷţ����Դ˴���Ҫ�ȼ�¼һ�� */
    st_eth_hdr = *pst_ether_hdr;
#endif
    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    switch(us_ether_type)
    {
        case OAL_HOST2NET_SHORT(ETHER_TYPE_ARP):
        {
            en_rst = hmac_proxy_arp(pst_mac_vap, pst_hmac_vap->pst_net_device, pst_buf);

            break;
        }
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):
        {
            en_rst = hmac_proxy_nd(pst_mac_vap, pst_hmac_vap->pst_net_device, pst_buf);

            break;
        }
        default:
        {
            return OAL_FALSE;
        }
    }

#ifdef _PRE_DEBUG_MODE
    hmac_proxy_debug_record(pst_mac_vap, &st_eth_hdr, us_ether_type, en_rst);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PROXYARP, "hmac_proxy_arp_proc! s:%x->d:%x type %x, result %u!",
                        st_eth_hdr.auc_ether_shost[ETHER_ADDR_LEN - 1],
                        st_eth_hdr.auc_ether_dhost[ETHER_ADDR_LEN - 1],
                        us_ether_type,
                        en_rst);
#endif

    return hmac_proxy_is_need_drop(en_rst);
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_arp_init
 ��������  : ��ʼ��proxy��������Ҫ�Ľṹ
 �������  : pst_mac_vap: mac_vapָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_proxy_arp_init(mac_vap_stru *pst_mac_vap)
{
    oal_uint32              ul_loop = 0;

    if ((WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
     || (OAL_PTR_NULL != pst_mac_vap->pst_vap_proxyarp))
    {
        return;
    }


    /* �����ڴ� */
    pst_mac_vap->pst_vap_proxyarp = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_vap_proxyarp_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYARP, "hmac_proxy_arp_init err! malloc err!");
        return;
    }

    OAL_MEMZERO(pst_mac_vap->pst_vap_proxyarp, OAL_SIZEOF(mac_vap_proxyarp_stru));

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        oal_dlist_init_head(&(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]));
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        oal_dlist_init_head(&(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]));
    }
}

/*****************************************************************************
 �� �� ��  : hmac_proxy_exit
 ��������  : �˳�ʱ�ͷ������ڴ�
 �������  : pst_mac_vap: mac_vapָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_proxy_exit(mac_vap_stru *pst_mac_vap)
{
    oal_dlist_head_stru        *pst_entry;
    hmac_proxy_ipv4_hash_stru  *pst_hash_ipv4;
    hmac_proxy_ipv6_hash_stru  *pst_hash_ipv6;
    oal_dlist_head_stru        *pst_dlist_tmp      = OAL_PTR_NULL;
    oal_uint32                  ul_loop = 0;

    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode
     || (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp))
    {
        return;
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]))
        {
            pst_hash_ipv4 = (hmac_proxy_ipv4_hash_stru *)pst_entry;
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_ipv4, OAL_TRUE);
            pst_mac_vap->pst_vap_proxyarp->uc_ipv4_num--;
        }
    }

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]))
        {
            pst_hash_ipv6 = (hmac_proxy_ipv6_hash_stru *)pst_entry;
            oal_dlist_delete_entry(pst_entry);
            OAL_MEM_FREE(pst_hash_ipv6, OAL_TRUE);
            pst_mac_vap->pst_vap_proxyarp->uc_ipv6_num--;
        }
    }

    OAL_MEM_FREE(pst_mac_vap->pst_vap_proxyarp, OAL_TRUE);
    pst_mac_vap->pst_vap_proxyarp = OAL_PTR_NULL;

}

/*****************************************************************************
 �� �� ��  : hmac_proxyarp_on
 ��������  : ����proxy arp���Կ���
 �������  : pst_mac_vap : mac_vapָ��
             en_on:����ֵ 0/1--��/��
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_proxyarp_on(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_on)
{
    if ((OAL_PTR_NULL == pst_mac_vap)
    || (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode))
    {
        return;
    }

    if (en_on)
    {
        hmac_proxy_arp_init(pst_mac_vap);
        pst_mac_vap->pst_vap_proxyarp->en_is_proxyarp = en_on;
        return;
    }

    hmac_proxy_exit(pst_mac_vap);

}

/*****************************************************************************
 �� �� ��  : alg_autorate_command_print_rate_set
 ��������  : ��ӡproxy arp������Ϣ
 �������  : pst_mac_vap : mac_vapָ��
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
oal_uint32 hmac_proxy_display_info(mac_vap_stru *pst_mac_vap)
{

    oal_dlist_head_stru             *pst_entry;
    hmac_proxy_ipv4_hash_stru       *pst_hash_ipv4;
    hmac_proxy_ipv6_hash_stru       *pst_hash_ipv6;
    oal_dlist_head_stru             *pst_dlist_tmp      = OAL_PTR_NULL;
    oal_uint32                       ul_loop = 0;
    oal_uint32                       ul_idx = 0;
    mac_vap_proxyarp_debug_stru     *pst_dbg;

    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
    {
        OAL_IO_PRINT("Err! Please input this cmd in AP!\n");
        return 0;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_vap_proxyarp)
    {
        OAL_IO_PRINT("Err!proxyarp mem alloc fail!\n");
        return 0;
    }

    OAL_IO_PRINT("index\tsrc_mac\t\tdst_mac\t\teth_type\tresult\tfrm_type\n");
    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        pst_dbg = &pst_mac_vap->pst_vap_proxyarp->ast_vap_proxyarp_dbg[ul_loop];

        OAL_IO_PRINT("%u\t%08x%04x\t%08x%04x\t%04x\t\t%u\t0x%x\n", \
                    pst_dbg->us_proxy_num, \
                    OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_dbg->st_eth_hdr.auc_ether_shost[0])),   \
                    OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_dbg->st_eth_hdr.auc_ether_shost[4])),   \
                    OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_dbg->st_eth_hdr.auc_ether_dhost[0])),   \
                    OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_dbg->st_eth_hdr.auc_ether_dhost[4])),   \
                    pst_dbg->st_eth_hdr.us_ether_type,\
                    pst_dbg->en_rst,\
                    pst_dbg->us_type);
    }


    OAL_IO_PRINT("\n ********************ipv4 hash***************************\n");
    OAL_IO_PRINT("index\tipaddr\t\tmac\n");
    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv4_head[ul_loop]))
        {
            pst_hash_ipv4 = (hmac_proxy_ipv4_hash_stru *)pst_entry;
            OAL_IO_PRINT("%u\t%08x\t%08x%04x\n", \
            ul_idx++,  \
            OAL_HOST2NET_LONG(pst_hash_ipv4->ul_ipv4), \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv4->auc_mac[0])),  \
            OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_hash_ipv4->auc_mac[4])));
        }
    }

    ul_idx = 0;
	OAL_IO_PRINT("\n ********************ipv6 hash***************************\n");
	OAL_IO_PRINT("index\tipaddr\t\t\t\t\tmac\n");
    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, &(pst_mac_vap->pst_vap_proxyarp->ast_ipv6_head[ul_loop]))
        {
            pst_hash_ipv6 = (hmac_proxy_ipv6_hash_stru *)pst_entry;
			OAL_IO_PRINT("%u\t%08x:%08x:%08x:%08x\t%08x%04x\n", \
            ul_idx++,  \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[0])), \
			OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[1])), \
			OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[2])), \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->st_ipv6.in6_u.u6_addr32[3])), \
            OAL_HOST2NET_LONG(*(oal_uint32*)(&pst_hash_ipv6->auc_mac[0])),  \
            OAL_HOST2NET_SHORT(*(oal_uint16*)(&pst_hash_ipv6->auc_mac[4])));
        }
    }

    return OAL_SUCC;
}
#endif

/*lint +e778*/ /*lint +e572*/

/*lint -e19*/
oal_module_symbol(hmac_proxy_arp_proc);
oal_module_symbol(hmac_proxyarp_on);

#ifdef _PRE_DEBUG_MODE
oal_module_symbol(hmac_proxy_display_info);
#endif
/*lint +e19*/


#endif /* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


