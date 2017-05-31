/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_frag.c
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2014��2��15��
  ����޸�   :
  ��������   : ��Ƭȥ��Ƭ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��2��15��
    ��    ��   : t00231215
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
#include "hmac_frag.h"
#include "hmac_11i.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_FRAG_C
#if 0
OAL_STATIC oal_void  hmac_defrag_check_seq_addr(hmac_user_stru *pst_hmac_user,
                                                        mac_ieee80211_frame_stru *pst_last_hdr,
                                                        mac_ieee80211_frame_stru *pst_mac_hdr,
                                                        oal_uint16 us_rx_seq,
                                                        oal_uint8 uc_frag_num);
#endif
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : hmac_frag_process
 ��������  : ���ķ�Ƭ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_frag_process(hmac_vap_stru *pst_hmac_vap,
                                   oal_netbuf_stru *pst_netbuf_original,
                                   mac_tx_ctl_stru *pst_tx_ctl,
                                   oal_uint32 ul_cip_hdrsize,
                                   oal_uint32 ul_max_tx_unit)
{
    mac_ieee80211_frame_stru *pst_mac_header;
    mac_ieee80211_frame_stru *pst_frag_header;
    oal_netbuf_stru          *pst_netbuf;
    oal_netbuf_stru          *pst_netbuf_prev;
    oal_uint32                ul_total_hdrsize;
    oal_uint32                ul_frag_num;
    oal_uint32                ul_frag_size;
    oal_int32                 l_remainder;
    oal_uint32                ul_payload  = 0;
    oal_uint32                ul_offset;
    mac_tx_ctl_stru          *pst_tx_ctl_copy;
    oal_uint32                ul_mac_hdr_size;

    ul_mac_hdr_size = MAC_80211_QOS_HTC_4ADDR_FRAME_LEN;

    pst_mac_header = pst_tx_ctl->pst_frame_header;
    pst_mac_header->st_frame_control.bit_more_frag = OAL_TRUE;
    ul_total_hdrsize = ul_mac_hdr_size + ul_cip_hdrsize;
    ul_frag_num = 1;
    /* �����ֽ��������ڷ�Ƭ�����У�Ԥ�������ֽڳ��ȣ���Ӳ����д����ͷ */

    ul_offset       = ul_max_tx_unit - ul_cip_hdrsize - ul_mac_hdr_size;
    l_remainder    = (oal_int32)(OAL_NETBUF_LEN(pst_netbuf_original) - ul_offset - ul_mac_hdr_size);
    pst_netbuf_prev = pst_netbuf_original;

    do
    {
        ul_frag_size = ul_total_hdrsize + (oal_uint32)l_remainder;

        /* �ж��Ƿ��и���ķ�Ƭ */
        if (ul_frag_size > ul_max_tx_unit)
        {
            ul_frag_size = ul_max_tx_unit;
        }

        pst_netbuf = oal_netbuf_alloc(ul_frag_size + MAC_80211_QOS_HTC_4ADDR_FRAME_LEN, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN, 4);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            /* ���ⲿ�ͷ�֮ǰ����ı��� */
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_frag_process::pst_netbuf null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_tx_ctl_copy = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
        /* ����cb�ֶ� */
        oal_memcopy(pst_tx_ctl_copy, pst_tx_ctl, MAC_TX_CTL_SIZE);

        oal_netbuf_copy_queue_mapping(pst_netbuf, pst_netbuf_original);

        /*netbuf��headroom����802.11 macͷ����*/
        pst_frag_header = (mac_ieee80211_frame_stru *)(OAL_NETBUF_PAYLOAD(pst_netbuf)- MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);
        pst_tx_ctl_copy->bit_80211_mac_head_type = 1;  /*ָʾmacͷ����skb��*/

        /* ����֡ͷ���� */
        oal_memcopy(pst_frag_header, pst_mac_header, pst_tx_ctl->uc_frame_header_length);
        /* ��ֵ��Ƭ�� */
        pst_frag_header->bit_frag_num = ul_frag_num;
        ul_frag_num++;
        /* �����Ƭ����֡�峤�� */
        ul_payload = ul_frag_size - ul_total_hdrsize;

        oal_netbuf_copydata(pst_netbuf_original, (ul_offset+ul_mac_hdr_size), OAL_NETBUF_PAYLOAD(pst_netbuf), ul_payload);

        oal_netbuf_set_len(pst_netbuf, ul_payload);
        ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->pst_frame_header = pst_frag_header;
        ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->us_mpdu_len      = (oal_uint16)ul_payload;
        OAL_NETBUF_NEXT(pst_netbuf_prev)                                 = pst_netbuf;
        pst_netbuf_prev                                                  = pst_netbuf;

        if (pst_tx_ctl_copy->bit_80211_mac_head_type == 1)
        {
            oal_netbuf_push(pst_netbuf, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);
        }

        /* ������һ����Ƭ���ĵĳ��Ⱥ�ƫ�� */
        l_remainder    -= (oal_int32)ul_payload;
        ul_offset       += ul_payload;
    }while(l_remainder > 0);

    pst_frag_header->st_frame_control.bit_more_frag = OAL_FALSE;
    OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;

    /* ԭʼ������Ϊ��Ƭ���ĵĵ�һ�� */
    oal_netbuf_trim(pst_netbuf_original, OAL_NETBUF_LEN(pst_netbuf_original) - (ul_max_tx_unit - ul_cip_hdrsize));
    pst_tx_ctl->us_mpdu_len = (oal_uint16)(OAL_NETBUF_LEN(pst_netbuf_original) - ul_mac_hdr_size);


    return OAL_SUCC;
}
#else

/*****************************************************************************
 �� �� ��  : hmac_frag_process
 ��������  : ���ķ�Ƭ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_frag_process(hmac_vap_stru *pst_hmac_vap,
                                   oal_netbuf_stru *pst_netbuf_original,
                                   mac_tx_ctl_stru *pst_tx_ctl,
                                   oal_uint32 ul_cip_hdrsize,
                                   oal_uint32 ul_max_tx_unit)
{
    mac_ieee80211_frame_stru *pst_mac_header;
    mac_ieee80211_frame_stru *pst_frag_header;
    oal_netbuf_stru          *pst_netbuf;
    oal_netbuf_stru          *pst_netbuf_prev;
    oal_uint32                ul_total_hdrsize;
    oal_uint32                ul_frag_num;
    oal_uint32                ul_frag_size;
    oal_int32                 l_remainder;
    oal_uint32                ul_payload  = 0;
    oal_uint32                ul_offset;
    mac_tx_ctl_stru          *pst_tx_ctl_copy;
    oal_uint32                ul_mac_hdr_size;

    ul_mac_hdr_size = pst_tx_ctl->uc_frame_header_length;

    pst_mac_header = pst_tx_ctl->pst_frame_header;
    pst_mac_header->st_frame_control.bit_more_frag = OAL_TRUE;
    ul_total_hdrsize = ul_mac_hdr_size + ul_cip_hdrsize;
    ul_frag_num = 1;
    /* �����ֽ��������ڷ�Ƭ�����У�Ԥ�������ֽڳ��ȣ���Ӳ����д����ͷ */

    ul_offset       = ul_max_tx_unit - ul_cip_hdrsize - ul_mac_hdr_size;
    l_remainder    = (oal_int32)(OAL_NETBUF_LEN(pst_netbuf_original) - ul_offset);
    pst_netbuf_prev = pst_netbuf_original;

    do
    {
        ul_frag_size = ul_total_hdrsize + (oal_uint32)l_remainder;

        /* �ж��Ƿ��и���ķ�Ƭ */
        if (ul_frag_size > ul_max_tx_unit)
        {
            ul_frag_size = ul_max_tx_unit;
        }

        pst_netbuf = oal_netbuf_alloc(ul_frag_size + MAC_80211_QOS_HTC_4ADDR_FRAME_LEN, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN, 4);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            /* ���ⲿ�ͷ�֮ǰ����ı��� */
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_frag_process::pst_netbuf null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_tx_ctl_copy = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
        /* ����cb�ֶ� */
        oal_memcopy(pst_tx_ctl_copy, pst_tx_ctl, MAC_TX_CTL_SIZE);

        /*netbuf��headroom����802.11 macͷ����*/
        pst_frag_header = (mac_ieee80211_frame_stru *)(OAL_NETBUF_PAYLOAD(pst_netbuf)- ul_mac_hdr_size);
        pst_tx_ctl_copy->bit_80211_mac_head_type = 1;  /*ָʾmacͷ����skb��*/

        /* ����֡ͷ���� */
        oal_memcopy(pst_frag_header, pst_mac_header, pst_tx_ctl->uc_frame_header_length);
        /* ��ֵ��Ƭ�� */
        pst_frag_header->bit_frag_num = ul_frag_num;
        ul_frag_num++;
        /* �����Ƭ����֡�峤�� */
        ul_payload = ul_frag_size - ul_total_hdrsize;

        oal_netbuf_copydata(pst_netbuf_original, ul_offset, OAL_NETBUF_PAYLOAD(pst_netbuf), ul_payload);

        oal_netbuf_set_len(pst_netbuf, ul_payload);
        ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->pst_frame_header = pst_frag_header;
        ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->us_mpdu_len      = (oal_uint16)ul_payload;
        OAL_NETBUF_NEXT(pst_netbuf_prev)                                 = pst_netbuf;
        pst_netbuf_prev                                                  = pst_netbuf;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        if (pst_tx_ctl_copy->bit_80211_mac_head_type == 1)
        {
            oal_netbuf_push(pst_netbuf, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);
        }
#endif

        /* ������һ����Ƭ���ĵĳ��Ⱥ�ƫ�� */
        l_remainder    -= (oal_int32)ul_payload;
        ul_offset       += ul_payload;
    }while(l_remainder > 0);

    pst_frag_header->st_frame_control.bit_more_frag = OAL_FALSE;
    OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;

    /* ԭʼ������Ϊ��Ƭ���ĵĵ�һ�� */
    oal_netbuf_trim(pst_netbuf_original, OAL_NETBUF_LEN(pst_netbuf_original) - (ul_max_tx_unit - ul_cip_hdrsize - ul_mac_hdr_size));
    pst_tx_ctl->us_mpdu_len = (oal_uint16)(OAL_NETBUF_LEN(pst_netbuf_original));


    return OAL_SUCC;
}

#endif
/*****************************************************************************
 �� �� ��  : hmac_frag_process_proc
 ��������  : ���ķ�Ƭ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��18��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_frag_process_proc(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint32          ul_threshold    = 0;
    oal_uint8           uc_ic_header    = 0;
    oal_uint32          ul_ret          = OAL_SUCC;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint32          uc_last_frag    = 0;
#endif

    /* ��ȡ��Ƭ���� */
    ul_threshold = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold;

    /* TBD���ü��ܽӿ���ʹ��TKIPʱ��MSDU���м��ܺ��ڽ��з�Ƭ */
    ul_ret = hmac_en_mic(pst_hmac_vap, pst_hmac_user, pst_netbuf, &uc_ic_header);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_frag_process::hmac_en_mic failed[%d].}", ul_ret);
        return ul_ret;
    }
    /*������ⵥDTS2014092901156��D2�ֻ�ping��ͨ����,������ֵ4*n+2*/
    ul_threshold = (ul_threshold & (~(BIT0|BIT1))) + 2;

    /* ���1151Ӳ��bug,������Ƭ���ޣ�TKIP����ʱ�������һ����Ƭ��payload����С�ڵ���8ʱ���޷����м��� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    if (WLAN_80211_CIPHER_SUITE_TKIP == pst_hmac_user->st_user_base_info.st_key_info.en_cipher_type)
    {
        uc_last_frag = OAL_NETBUF_LEN(pst_netbuf) % (ul_threshold - (oal_uint32)uc_ic_header - pst_tx_ctl->uc_frame_header_length);
        if ((uc_last_frag > 0) && (uc_last_frag <= 8))
        {
            ul_threshold = ul_threshold + 8;
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_frag_process_proc::adjust the frag threshold to %d.}", ul_threshold);
        }
    }
#endif
    /* ���з�Ƭ���� */
    ul_ret = hmac_frag_process(pst_hmac_vap, pst_netbuf, pst_tx_ctl, (oal_uint32)uc_ic_header, ul_threshold);

    return ul_ret;

}

/*****************************************************************************
 �� �� ��  : hmac_defrag_timeout_fn
 ��������  : ���Ƭ��ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��20��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_defrag_timeout_fn(oal_void *p_arg)
{
    hmac_user_stru  *pst_hmac_user;
    oal_netbuf_stru *pst_netbuf = OAL_PTR_NULL;
    pst_hmac_user = (hmac_user_stru *)p_arg;


    /* ��ʱ���ͷ���������ķ�Ƭ���� */
    if (pst_hmac_user->pst_defrag_netbuf)
    {
        pst_netbuf = pst_hmac_user->pst_defrag_netbuf;

        OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_FALSE);
        oal_netbuf_free(pst_netbuf);
        pst_hmac_user->pst_defrag_netbuf = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_defrag_process
 ��������  : ȥ��Ƭ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��20��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_netbuf_stru* hmac_defrag_process(hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf, oal_uint32 ul_hrdsize)
{
    mac_ieee80211_frame_stru *pst_mac_hdr   = OAL_PTR_NULL;
    mac_ieee80211_frame_stru *pst_last_hdr  = OAL_PTR_NULL;
    oal_uint16                us_rx_seq     = 0;
    oal_uint16                us_last_seq   = 0;
    oal_uint8                 uc_frag_num   = 0;
    oal_uint8                 uc_last_frag_num  = 0;
    oal_bool_enum_uint8       en_more_frag      = OAL_FALSE;
    oal_netbuf_stru          *pst_new_buf       = OAL_PTR_NULL;
    mac_rx_ctl_stru          *pst_rx_ctl;
    oal_uint32                ul_ret;
    oal_uint8                 uc_device_id;
    mac_device_stru          *pst_mac_device;
    oal_uint32                ul_core_id;


    pst_mac_hdr = (mac_ieee80211_frame_stru *)oal_netbuf_data(pst_netbuf);
    us_rx_seq   = pst_mac_hdr->bit_seq_num;
    uc_frag_num = (oal_uint8)pst_mac_hdr->bit_frag_num;

    en_more_frag = (oal_bool_enum_uint8)pst_mac_hdr->st_frame_control.bit_more_frag;

    /* ���û��ʲô����ȥ��Ƭ����ֱ�ӷ��� */
    if (!en_more_frag && 0 == uc_frag_num && OAL_PTR_NULL == pst_hmac_user->pst_defrag_netbuf)
    {
        return pst_netbuf;
    }

    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_FALSE);

    /* ���ȼ�鵽���ķ�Ƭ�����ǲ���������������ķ�Ƭ���� */
    if (pst_hmac_user->pst_defrag_netbuf)
    {
        frw_timer_restart_timer(&pst_hmac_user->st_defrag_timer, HMAC_FRAG_TIMEOUT, OAL_FALSE);

        pst_last_hdr = (mac_ieee80211_frame_stru *)oal_netbuf_data(pst_hmac_user->pst_defrag_netbuf);

        us_last_seq  = pst_last_hdr->bit_seq_num;
        uc_last_frag_num = (oal_uint8)pst_last_hdr->bit_frag_num;

        /* �����ַ��ƥ�䣬���кŲ�ƥ�䣬��Ƭ�Ų�ƥ�����ͷ�������������ı��� */
        if (us_rx_seq != us_last_seq ||
            uc_frag_num != (uc_last_frag_num + 1) ||
            oal_compare_mac_addr(pst_last_hdr->auc_address1, pst_mac_hdr->auc_address1) ||
            oal_compare_mac_addr(pst_last_hdr->auc_address2, pst_mac_hdr->auc_address2))
        {
            oal_netbuf_free(pst_hmac_user->pst_defrag_netbuf);
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_defrag_timer);

            pst_hmac_user->pst_defrag_netbuf = OAL_PTR_NULL;
        }
    }

    /* �жϵ����ķ�Ƭ�����Ƿ��ǵ�һ����Ƭ */
    if (OAL_PTR_NULL == pst_hmac_user->pst_defrag_netbuf)
    {
        /* ��Ƭ��Ƭ�ķ�Ƭ�Ų�Ϊ0���ͷ� */
        if (uc_frag_num != 0)
        {
            oal_netbuf_free(pst_netbuf);
            OAM_STAT_VAP_INCR(pst_hmac_user->st_user_base_info.uc_vap_id, rx_defrag_process_dropped, 1);
            OAM_INFO_LOG3(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY,
                        "{hmac_defrag_process::The first frag_num is not Zero(%d), seq_num[%d], mor_frag[%d].}",
                           uc_frag_num, us_rx_seq, en_more_frag);

            return OAL_PTR_NULL;
        }

        /* û�з�Ƭ,ֱ�ӷ��� */
        if (0 == en_more_frag && 0 == uc_frag_num)
        {
            return pst_netbuf;
        }

        uc_device_id   = pst_hmac_user->st_user_base_info.uc_device_id;
        pst_mac_device = mac_res_get_dev((oal_uint32)uc_device_id);
        if (OAL_PTR_NULL == pst_mac_device)
        {
            OAM_ERROR_LOG4(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY,
                        "{hmac_defrag_process::user index[%d] user mac:XX:XX:XX:%02X:%02X:%02X}",
                        pst_hmac_user->st_user_base_info.us_assoc_id,
                        pst_hmac_user->st_user_base_info.auc_user_mac_addr[3],
                        pst_hmac_user->st_user_base_info.auc_user_mac_addr[4],
                        pst_hmac_user->st_user_base_info.auc_user_mac_addr[5]);
            /* user�쳣���������� */
            oal_netbuf_free(pst_netbuf);
            OAM_STAT_VAP_INCR(pst_hmac_user->st_user_base_info.uc_vap_id, rx_defrag_process_dropped, 1);
            return OAL_PTR_NULL;
        }
        ul_core_id     = pst_mac_device->ul_core_id;

        /* ������ʱ��ʱ������ʱ�ͷ����鱨�� */
        FRW_TIMER_CREATE_TIMER(&pst_hmac_user->st_defrag_timer,
                                hmac_defrag_timeout_fn,
                                HMAC_FRAG_TIMEOUT,
                                pst_hmac_user,
                                OAL_FALSE,
                                OAM_MODULE_ID_HMAC,
                                ul_core_id);

        /* �ڴ��netbufֻ��1600 ���ܲ���������A��˾����2500����ϵͳԭ��̬���� */
        pst_new_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, HMAC_MAX_FRAG_SIZE, OAL_NETBUF_PRIORITY_MID);
        if (OAL_PTR_NULL == pst_new_buf)
        {
            OAM_ERROR_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_defrag_process::Alloc new_buf null,size[%d].}", HMAC_MAX_FRAG_SIZE);
            return OAL_PTR_NULL;
        }
        OAL_MEM_NETBUF_TRACE(pst_new_buf, OAL_FALSE);

        /* ����Ƭ���Ŀ�����������ı����в��ҽӵ��û��ṹ���£��ͷ�ԭ�еı��� */
        oal_netbuf_init(pst_new_buf, OAL_NETBUF_LEN(pst_netbuf));
        oal_netbuf_copydata(pst_netbuf, 0, oal_netbuf_data(pst_new_buf), OAL_NETBUF_LEN(pst_netbuf));
        oal_memcopy(OAL_NETBUF_CB(pst_new_buf), OAL_NETBUF_CB(pst_netbuf), MAC_TX_CTL_SIZE);
        pst_rx_ctl = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_new_buf);
        pst_rx_ctl->pul_mac_hdr_start_addr = (oal_uint32 *)OAL_NETBUF_HEADER(pst_new_buf);
        pst_hmac_user->pst_defrag_netbuf = pst_new_buf;

        oal_netbuf_free(pst_netbuf);

        pst_netbuf = pst_new_buf;
    }
    else
    {
        /* �������߼��˷�֧�����ܽ�����Ϊ����pc lint���� */
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_last_hdr))
        {
            OAM_ERROR_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_defrag_process::pst_last_hdr is NULL.}");
            return OAL_PTR_NULL;
        }

        /* �˷�Ƭ�������ĵ����ķ�Ƭ��������ʱ�������������� */
        frw_timer_restart_timer(&pst_hmac_user->st_defrag_timer, HMAC_FRAG_TIMEOUT, OAL_FALSE);

        oal_netbuf_pull(pst_netbuf, ul_hrdsize);

        /* ��¼���·�Ƭ���ĵķ�Ƭ�� */
        pst_last_hdr->bit_seq_num   = pst_mac_hdr->bit_seq_num;/* [false alarm]:pst_mac_hdr������Ϊ�գ����Ƕ����е�Ԫ�أ����в�����Ϊ��*/
        pst_last_hdr->bit_frag_num  = pst_mac_hdr->bit_frag_num;

        /*�˽ӿ��ڻ����dev_kfree_skb*/
        oal_netbuf_concat(pst_hmac_user->pst_defrag_netbuf, pst_netbuf);
    }

    /* �ж��Ƿ�������ϣ����ڸ��౨�ķ��ؿ�ָ�룬������Ϸ�����õı��� */
    if (en_more_frag)
    {
        pst_netbuf = OAL_PTR_NULL;
    }
    else
    {
        /* �������߼��˷�֧�����ܽ�����Ϊ����pc lint���� */
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_last_hdr))
        {
            OAM_ERROR_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_defrag_process::pst_last_hdr is NULL.}");
            oal_netbuf_free(pst_netbuf);
            pst_hmac_user->pst_defrag_netbuf = OAL_PTR_NULL;
            return OAL_PTR_NULL;
        }

        pst_netbuf = pst_hmac_user->pst_defrag_netbuf;
        /* ������õı��Ľ���mic��� */
        ul_ret = hmac_de_mic(pst_hmac_user, pst_netbuf);
        if (OAL_SUCC != ul_ret)
        {
            oal_netbuf_free(pst_netbuf);

            OAM_STAT_VAP_INCR(pst_hmac_user->st_user_base_info.uc_vap_id, rx_de_mic_fail_dropped, 1);
            pst_netbuf = OAL_PTR_NULL;

            OAM_INFO_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_defrag_process::hmac_de_mic failed[%d].}", ul_ret);
        }

        pst_hmac_user->pst_defrag_netbuf = OAL_PTR_NULL;

        pst_last_hdr->bit_frag_num = 0;

        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_defrag_timer);
    }

    return pst_netbuf;
}







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

