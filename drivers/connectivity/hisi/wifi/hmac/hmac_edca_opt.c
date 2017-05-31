/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_edca_opt.c
  �� �� ��   : ����
  ��    ��   : xiechunhui
  ��������   : 2014��12��1��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "hmac_edca_opt.h"
#include "hmac_vap.h"
#include "oam_wdk.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_EDCA_OPT_C
/*****************************************************************************
  2 �ṹ�嶨��
*****************************************************************************/


/*****************************************************************************
  3 �궨��
*****************************************************************************/
#define HMAC_EDCA_OPT_ADJ_STEP      2

/* (3-a)/3*X + a/3*Y */
#define WLAN_EDCA_OPT_MOD(X, Y, a) (((X)*(WLAN_EDCA_OPT_MAX_WEIGHT_STA - a) + (Y)*(a))/WLAN_EDCA_OPT_MAX_WEIGHT_STA);

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
#if 0 //����ͨ���󣬴˶δ����ɾ��-wanran
OAL_STATIC oal_uint32 g_aast_ul_traffic_vs_cwmin[HMAC_EDCA_OPT_ADJ_STEP][2] =
{
    /* be_num   cwmin */
    {1,         4},
    {3,         6}
};
#endif

/*****************************************************************************
  5 �ڲ���̬��������
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_edca_opt_check_is_tcp_data(mac_ip_header_stru *pst_ip);
OAL_STATIC oal_uint32  hmac_edca_opt_stat_traffic_num(hmac_vap_stru *pst_hmac_vap, oal_uint8 (*ppuc_traffic_num)[WLAN_TXRX_DATA_BUTT]);
#if 0 //����ͨ���󣬴˶δ����ɾ��-wanran
OAL_STATIC oal_uint32  hmac_edca_opt_adj_param_ap(hmac_vap_stru *pst_hmac_vap, oal_uint8 (*ppuc_traffic_num)[WLAN_TXRX_DATA_BUTT]);
#endif
/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : hmac_check_is_tcp_data
 ��������  : ����Ƿ�Ϊtcp data����
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_edca_opt_check_is_tcp_data(mac_ip_header_stru *pst_ip)
{
    oal_uint8   *puc_ip             = (oal_uint8 *)pst_ip;
    oal_uint16   us_ip_len          = 0;
    oal_uint8    uc_ip_header_len   = ((*puc_ip) & 0x0F) << 2; /* IP_HDR_LEN */
    oal_uint8    uc_tcp_header_len  = 0;

    /* ��ȡip���ĳ��� */
    us_ip_len  = (*(puc_ip + 2 /* length in ip header */)) << 8;
    us_ip_len |= *(puc_ip + 2 /* length in ip header */+1);

    /* ��ȡtcp header���� */
    uc_tcp_header_len = *(puc_ip + uc_ip_header_len + 12/* length in tcp header */);
    uc_tcp_header_len = (uc_tcp_header_len >> 4) << 2;

    if ((us_ip_len - uc_ip_header_len) == uc_tcp_header_len)
    {
        OAM_INFO_LOG3(0, OAM_SF_TX, "{hmac_edca_opt_check_is_tcp_data:is tcp ack, us_ip_len = %d, uc_ip_header_len = %d, uc_tcp_header_len = %d",
            us_ip_len, uc_ip_header_len, uc_tcp_header_len);
        return OAL_FALSE;
    }
    else
    {
        OAM_INFO_LOG3(0, OAM_SF_TX, "{hmac_edca_opt_check_is_tcp_data:is tcp data, us_ip_len = %d, uc_ip_header_len = %d, uc_tcp_header_len = %d",
            us_ip_len, uc_ip_header_len, uc_tcp_header_len);
        return OAL_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : hmac_edca_opt_stat_traffic_num
 ��������  : edca����ͳ����/���У�TCP/UDP����Ŀ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_edca_opt_stat_traffic_num(hmac_vap_stru *pst_hmac_vap, oal_uint8 (*ppuc_traffic_num)[WLAN_TXRX_DATA_BUTT])
{
    mac_user_stru   *pst_user;
    hmac_user_stru  *pst_hmac_user;
    oal_uint8        uc_ac_idx;
    oal_uint8        uc_data_idx;
    mac_vap_stru    *pst_vap            = &(pst_hmac_vap->st_vap_base_info);
    oal_dlist_head_stru *pst_list_pos   = OAL_PTR_NULL;

    pst_list_pos = pst_vap->st_mac_user_list_head.pst_next;

    for (; pst_list_pos != &(pst_vap->st_mac_user_list_head); pst_list_pos = pst_list_pos->pst_next)
    {
        pst_user = OAL_DLIST_GET_ENTRY(pst_list_pos, mac_user_stru, st_user_dlist);
        pst_hmac_user = mac_res_get_hmac_user(pst_user->us_assoc_id);

        if (OAL_PTR_NULL == pst_hmac_user)
        {
            continue;
        }

        for (uc_ac_idx = 0; uc_ac_idx < WLAN_WME_AC_BUTT; uc_ac_idx++)
        {
            for (uc_data_idx = 0; uc_data_idx < WLAN_TXRX_DATA_BUTT; uc_data_idx++)
            {
                OAM_INFO_LOG4(0, OAM_SF_TX, "mac_edca_opt_stat_traffic_num, assoc_id = %d, uc_ac = %d, uc_idx = %d, pkt_num = %d",
                    pst_user->us_assoc_id,
                    uc_ac_idx,
                    uc_data_idx,
                    pst_hmac_user->aaul_txrx_data_stat[uc_ac_idx][uc_data_idx]);

                if (pst_hmac_user->aaul_txrx_data_stat[uc_ac_idx][uc_data_idx] > HMAC_EDCA_OPT_PKT_NUM)
                {
                    ppuc_traffic_num[uc_ac_idx][uc_data_idx]++;
                }

                /* ͳ�������0 */
                pst_hmac_user->aaul_txrx_data_stat[uc_ac_idx][uc_data_idx] = 0;
            }
        }
    }

#if 0
    OAM_WARNING_LOG4(0, OAM_SF_TX,
        "mac_edca_opt_stat_traffic_num:be_tx_tcp = %d, be_rx_tcp = %d, be_tx_udp = %d, be_rx_udp = %d",
         ppuc_traffic_num[0][WLAN_TX_TCP_DATA], ppuc_traffic_num[0][WLAN_RX_TCP_DATA],
         ppuc_traffic_num[0][WLAN_TX_UDP_DATA], ppuc_traffic_num[0][WLAN_RX_UDP_DATA]);

    OAM_INFO_LOG4(0, OAM_SF_TX,
        "mac_edca_opt_stat_traffic_num:bk_tx_tcp = %d, bk_rx_tcp = %d, bk_tx_udp = %d, bk_rx_udp = %d",
         ppuc_traffic_num[1][WLAN_TX_TCP_DATA], ppuc_traffic_num[1][WLAN_RX_TCP_DATA],
         ppuc_traffic_num[1][WLAN_TX_UDP_DATA], ppuc_traffic_num[1][WLAN_RX_UDP_DATA]);

    OAM_INFO_LOG4(0, OAM_SF_TX,
        "mac_edca_opt_stat_traffic_num:vi_tx_tcp = %d, vi_rx_tcp = %d, vi_tx_udp = %d, vi_rx_udp = %d",
         ppuc_traffic_num[2][WLAN_TX_TCP_DATA], ppuc_traffic_num[2][WLAN_RX_TCP_DATA],
         ppuc_traffic_num[2][WLAN_TX_UDP_DATA], ppuc_traffic_num[2][WLAN_RX_UDP_DATA]);

    OAM_INFO_LOG4(0, OAM_SF_TX,
        "mac_edca_opt_stat_traffic_num:vo_tx_tcp = %d, vo_rx_tcp = %d, vo_rx_udp = %d,vo_rx_udp = %d",
         ppuc_traffic_num[3][WLAN_TX_TCP_DATA], ppuc_traffic_num[3][WLAN_RX_TCP_DATA],
         ppuc_traffic_num[3][WLAN_TX_UDP_DATA], ppuc_traffic_num[3][WLAN_RX_UDP_DATA]);
#endif

    return OAL_SUCC;
}

#if 0//����ͨ���󣬴˺�����ɾ��-wanran
/*****************************************************************************
 �� �� ��  : hmac_edca_opt_adj_param_ap
 ��������  : ����edca����ͳ����/���У�TCP/UDP����Ŀ������edca����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_edca_opt_adj_param_ap(hmac_vap_stru *pst_hmac_vap, oal_uint8 (*ppuc_traffic_num)[WLAN_TXRX_DATA_BUTT])
{
    oal_uint8        uc_ac_idx       = 0;
    oal_uint8        uc_idx          = 0;
    oal_uint8        uc_be_tcp_num   = 0;
    oal_uint8        ul_ret          = OAL_SUCC;
    oal_uint32       ul_new_cwmin    = 0;
    hmac_config_wmm_para_stru   st_wmm_config;

    uc_be_tcp_num = ppuc_traffic_num[WLAN_WME_AC_BE][WLAN_TX_TCP_DATA];

    /* û��ҵ�񣬲���Ҫ���е��� */
    if (0 == uc_be_tcp_num)
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: no be_tx_tcp traffic, donot adj");
        return OAL_SUCC;
    }

    /* �������be tx_tcpҵ�����⣬ ����������ҵ���򲻽��е��� */
    for (uc_ac_idx = 0; uc_ac_idx < WLAN_WME_AC_BUTT; uc_ac_idx++)
    {
        for (uc_idx = 0; uc_idx < WLAN_TXRX_DATA_BUTT; uc_idx++)
        {
            if (((WLAN_WME_AC_BE != uc_ac_idx) || (WLAN_TX_TCP_DATA != uc_idx)) && (0 != ppuc_traffic_num[uc_ac_idx][uc_idx]))
            {
                OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: not only be_tx_tcp traffic, donot adj params");

                /* ��Ϊdefault cwminֵ */
                st_wmm_config.ul_cfg_id = WLAN_CFGID_QEDCA_TABLE_CWMIN;
                st_wmm_config.ul_ac     = WLAN_WME_AC_BUTT;
                st_wmm_config.ul_value = g_aast_ul_traffic_vs_cwmin[0][1];

                /*lint -e734*/
                ul_ret = hmac_config_set_wmm_params(&(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(st_wmm_config), (oal_uint8 *) &st_wmm_config);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: hmac_config_set_wmm_params failed");
                    return ul_ret;
                }
                return OAL_SUCC;
            }
        }
    }

    /* Ѱ�Ҹ�ҵ������Ŀ�¶�Ӧ������cwmin���� */
    if (uc_be_tcp_num >= g_aast_ul_traffic_vs_cwmin[HMAC_EDCA_OPT_ADJ_STEP - 1][0])
    {
        ul_new_cwmin = g_aast_ul_traffic_vs_cwmin[HMAC_EDCA_OPT_ADJ_STEP - 1][1];
    }
    else
    {
        for (uc_idx = 0; uc_idx < HMAC_EDCA_OPT_ADJ_STEP - 1; uc_idx++)
        {

            if ((uc_be_tcp_num >= g_aast_ul_traffic_vs_cwmin[uc_idx][0])
                    && (uc_be_tcp_num < g_aast_ul_traffic_vs_cwmin[uc_idx + 1][0]))
            {
                ul_new_cwmin = g_aast_ul_traffic_vs_cwmin[uc_idx][1];
                break;
            }
        }
    }

    if (ul_new_cwmin == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin)
    {
        OAM_WARNING_LOG1(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: no need to adj cwmin, cwmin = %d}", ul_new_cwmin);
        return OAL_SUCC;
    }

    /* ����ǰcwminֵ */
    OAM_WARNING_LOG1(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: before adj: cwmin = %d}",
            pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin);

    st_wmm_config.ul_cfg_id = WLAN_CFGID_QEDCA_TABLE_CWMIN;
    st_wmm_config.ul_ac     = WLAN_WME_AC_BE;
    st_wmm_config.ul_value  = ul_new_cwmin;

    /*lint -e734*/
    ul_ret = hmac_config_set_wmm_params(&(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(st_wmm_config), (oal_uint8 *) &st_wmm_config);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: hmac_config_set_wmm_params failed");
        return ul_ret;
    }

    /* ������cwminֵ */
    OAM_WARNING_LOG1(0, OAM_SF_TX, "{hmac_edca_opt_adj_param_ap: after adj: cwmin = %d}",
         pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin);

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_edca_opt_timeout_fn
 ��������  : edca������ʱ�����ڴ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��5��
    ��    ��   : wanran
    �޸�����   : �������¼��������������µ���alg

*****************************************************************************/
oal_uint32  hmac_edca_opt_timeout_fn(oal_void *p_arg)
{
    oal_uint8        aast_uc_traffic_num[WLAN_WME_AC_BUTT][WLAN_TXRX_DATA_BUTT];
    hmac_vap_stru   *pst_hmac_vap       = OAL_PTR_NULL;

    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_edca_opt_timeout_fn::p_arg is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)p_arg;

    /* ������ʼ�� */
    OAL_MEMZERO(aast_uc_traffic_num, OAL_SIZEOF(aast_uc_traffic_num));

    /* ͳ��device�������û���/���� TPC/UDP����Ŀ */
    hmac_edca_opt_stat_traffic_num(pst_hmac_vap, aast_uc_traffic_num);

    /***************************************************************************
        ���¼���dmacģ��,��ͳ����Ϣ����dmac
    ***************************************************************************/

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(aast_uc_traffic_num));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANTI_INTF, "{hmac_edca_opt_timeout_fn::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPR_EDCA_OPT,
                    OAL_SIZEOF(aast_uc_traffic_num),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_hmac_vap->st_vap_base_info.uc_chip_id,
                    pst_hmac_vap->st_vap_base_info.uc_device_id,
                    pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* �������� */
    oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8 *)aast_uc_traffic_num, OAL_SIZEOF(aast_uc_traffic_num));

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

#if 0 //����ͨ���󣬴˺�����ɾ��-wanran
    /* ����edca���� */
    hmac_edca_opt_adj_param_ap(pst_hmac_vap, aast_uc_traffic_num);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_edca_opt_rx_pkts_stat
 ��������  : edca��������ͳ�Ʒ��ͱ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_edca_opt_rx_pkts_stat(oal_uint16 us_assoc_id,oal_uint8 uc_tidno, mac_ip_header_stru *pst_ip)
{
    hmac_user_stru  *pst_hmac_user = OAL_PTR_NULL;
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_assoc_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{hmac_edca_opt_rx_pkts_stat::null param,pst_hmac_user[%d].}",us_assoc_id);
        return;
    }
    OAM_INFO_LOG0(0, OAM_SF_RX, "{hmac_edca_opt_rx_pkts_stat}");

    /* ����IP_LEN С�� HMAC_EDCA_OPT_MIN_PKT_LEN�ı��� */
    if (OAL_NET2HOST_SHORT(pst_ip->us_tot_len) < HMAC_EDCA_OPT_MIN_PKT_LEN)
    {
        return;
    }

    if (MAC_UDP_PROTOCAL == pst_ip->uc_protocol)
    {
        pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_RX_UDP_DATA]++;
        OAM_INFO_LOG4(0, OAM_SF_RX, "{hmac_edca_opt_rx_pkts_stat:is udp_data, assoc_id = %d, tidno = %d, type = %d, num = %d",
                        pst_hmac_user->st_user_base_info.us_assoc_id, uc_tidno, WLAN_RX_UDP_DATA, pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_RX_UDP_DATA]);
    }
    else if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol)
    {
        if (hmac_edca_opt_check_is_tcp_data(pst_ip))
        {
            pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_RX_TCP_DATA]++;
            OAM_INFO_LOG4(0, OAM_SF_RX, "{hmac_edca_opt_rx_pkts_stat:is tcp_data, assoc_id = %d, tidno = %d, type = %d, num = %d",
                            pst_hmac_user->st_user_base_info.us_assoc_id, uc_tidno, WLAN_RX_TCP_DATA, pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_RX_TCP_DATA]);
        }
    }
    else
    {
        OAM_INFO_LOG0(0, OAM_SF_RX, "{hmac_tx_pkts_stat_for_edca_opt: neither UDP nor TCP ");
    }
}


/*****************************************************************************
 �� �� ��  : hmac_edca_opt_tx_pkts_stat
 ��������  : edca��������ͳ�Ʒ��ͱ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_edca_opt_tx_pkts_stat(mac_tx_ctl_stru  *pst_tx_ctl,oal_uint8 uc_tidno, mac_ip_header_stru *pst_ip)
{
    hmac_user_stru  *pst_hmac_user = OAL_PTR_NULL;

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{hmac_edca_opt_rx_pkts_stat::null param,pst_hmac_user[%d].}",MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
        return;
    }
    OAM_INFO_LOG0(0, OAM_SF_RX, "{hmac_edca_opt_tx_pkts_stat}");

    /* ����IP_LEN С�� HMAC_EDCA_OPT_MIN_PKT_LEN�ı��� */
    if (OAL_NET2HOST_SHORT(pst_ip->us_tot_len) < HMAC_EDCA_OPT_MIN_PKT_LEN)
    {
        return;
    }

    if (MAC_UDP_PROTOCAL == pst_ip->uc_protocol)
    {
        pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_TX_UDP_DATA]++;
        OAM_INFO_LOG4(0, OAM_SF_TX, "{hmac_edca_opt_tx_pkts_stat:is udp_data, assoc_id = %d, tidno = %d, type = %d, num = %d",
                        pst_hmac_user->st_user_base_info.us_assoc_id, uc_tidno, WLAN_TX_UDP_DATA, pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_TX_UDP_DATA]);
    }
    else if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol)
    {
        if (hmac_edca_opt_check_is_tcp_data(pst_ip))
        {
            pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_TX_TCP_DATA]++;
            OAM_INFO_LOG4(0, OAM_SF_TX, "{hmac_edca_opt_tx_pkts_stat:is tcp_data, assoc_id = %d, tidno = %d, type = %d, num = %d",
                            pst_hmac_user->st_user_base_info.us_assoc_id, uc_tidno, WLAN_TX_TCP_DATA, pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tidno)][WLAN_TX_TCP_DATA]);
        }
    }
    else
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_edca_opt_tx_pkts_stat: neither UDP nor TCP");
    }
}

#if 0//����ͨ���󣬴˺�����ɾ��-wanran

/*****************************************************************************
 �� �� ��  : hmac_edca_opt_adj_param_sta
 ��������  : sta����edca����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��3��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_edca_opt_adj_param_sta(oal_void *pst_void)
{
    oal_uint32  ul_new_set           = 0;
    oal_uint32  aul_higher_set[3]    = {1, 1, 1};
    oal_uint32  ul_new_txop_limit    = 0;
    oal_uint8   uc_idx               = 0;
    hmac_vap_stru               *pst_hmac_vap       = (hmac_vap_stru *)pst_void;
    wlan_mib_ieee802dot11_stru  *pst_mib            = pst_hmac_vap->st_vap_base_info.pst_mib_info;
    oal_uint32                   ul_max_txop_limit  = pst_mib->st_wlan_mib_qap_edac[0].ul_dot11QAPEDCATableTXOPLimit;

    /* sta����ǰ���� */
    OAM_WARNING_LOG4(0, OAM_SF_WMM, "be before adj, cwmin= %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit);

    OAM_WARNING_LOG4(0, OAM_SF_WMM, "bk before adj, cwmin = %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);

    OAM_WARNING_LOG4(0, OAM_SF_WMM, "vi before adj, cwmin = %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);

    OAM_WARNING_LOG4(0, OAM_SF_WMM, "vo before adj, cwmin = %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit);

    for(uc_idx = 1; uc_idx< WLAN_WME_AC_BUTT; uc_idx++)
    {
        if(ul_max_txop_limit < pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableTXOPLimit)
        {
            ul_max_txop_limit = pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableTXOPLimit;
        }
    }

    for(uc_idx = WLAN_WME_AC_BUTT - 1; uc_idx != 0xFF; uc_idx--)
    {
        /* 1101 ��1151 be/bk����պ��෴ */
        if (WLAN_WME_AC_BE == uc_idx)
        {
            uc_idx = WLAN_WME_AC_BK;
        }
        else if (WLAN_WME_AC_BK == uc_idx)
        {
            uc_idx = WLAN_WME_AC_BE;
        }

        if (0 == pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableTXOPLimit)
        {
            ul_new_txop_limit = 0;
        }
        else
        {
            ul_new_txop_limit = WLAN_EDCA_OPT_MOD(ul_max_txop_limit, pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableTXOPLimit, pst_hmac_vap->uc_edca_opt_weight_sta)
        }

        pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableTXOPLimit = ul_new_txop_limit;

        ul_new_set          = WLAN_EDCA_OPT_MOD(aul_higher_set[0], pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableAIFSN, pst_hmac_vap->uc_edca_opt_weight_sta);
        aul_higher_set[0]   = pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableAIFSN;
        pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableAIFSN = ul_new_set;

        ul_new_set          = WLAN_EDCA_OPT_MOD(aul_higher_set[1], pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableCWmin, pst_hmac_vap->uc_edca_opt_weight_sta);
        aul_higher_set[1]   = pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableCWmin;
        pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableCWmin = ul_new_set;

        ul_new_set          = WLAN_EDCA_OPT_MOD(aul_higher_set[2], pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableCWmax, pst_hmac_vap->uc_edca_opt_weight_sta);
        aul_higher_set[2]   = pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableCWmax;
        pst_mib->st_wlan_mib_qap_edac[uc_idx].ul_dot11QAPEDCATableCWmax = ul_new_set;
    }

    /* STA��������� */
    OAM_WARNING_LOG4(0, OAM_SF_WMM, "be after adj, cwmin= %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit);

    OAM_WARNING_LOG4(0, OAM_SF_WMM, "bk after adj, cwmin = %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);

    OAM_WARNING_LOG4(0, OAM_SF_WMM, "vi after adj, cwmin = %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);

    OAM_WARNING_LOG4(0, OAM_SF_WMM, "vo after adj, cwmin = %d, cwmax = %d, aifsn = %d, txoplimit = %d",
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN,
    pst_mib->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit);
}
#endif

#endif   /* end of _PRE_WLAN_FEATURE_EDCA_OPT_AP */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

