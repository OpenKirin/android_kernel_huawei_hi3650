/****************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_tx_amsdu.c
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��11��12��
  ����޸�   :
  ��������   : amsdu�ۺ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��12��
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
#include "hmac_tx_amsdu.h"
#include "hmac_tx_data.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TX_AMSDU_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OAL_STATIC oal_uint32  hmac_amsdu_tx_timeout_process(oal_void *p_arg);
OAL_STATIC oal_bool_enum_uint8 hmac_tx_amsdu_is_overflow(
                hmac_amsdu_stru    *pst_amsdu,
                mac_tx_ctl_stru    *pst_tx_ctl,
                oal_uint32          ul_frame_len,
                hmac_user_stru     *pst_user);


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
/*****************************************************************************
 �� �� ��  : hmac_amsdu_encap
 ��������  : amsdu��֡ͷ��װ
 �������  : pst_amsdu: amsdu�ṹ��ָ��
             pst_buf: �¼������֡
             ul_framelen: �����ĳ���
 �������  : ��
 �� �� ֵ  : �ɹ�:OAL_SUCC;ʧ��OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_amsdu_encap_hdr(hmac_amsdu_stru *pst_amsdu, oal_netbuf_stru **pst_netbuf, oal_uint32 ul_framelen)
{
    oal_uint32              ul_headroom;    /* �ݴ�skbʣ��ͷ���ռ� */
    oal_uint32              ul_tailroom;    /* �ݴ�skbʣ��β���ռ� */
    oal_uint8               uc_align;       /* Ϊ4�ֽڶ���β����Ҫ��ƫ���� */
    mac_ether_header_stru   st_ether_head;  /* �ݴ���̫��������skb����̫��ͷ */
    mac_ether_header_stru  *pst_amsdu_head; /* Ϊ��дamsdu��֡ͷ����ʱָ�� */
    mac_llc_snap_stru      *pst_snap_head;  /* Ϊ��дsnapͷ����ʱָ�� */
    mac_tx_ctl_stru        *pst_cb;
    oal_netbuf_stru        *pst_first_netbuf;
    mac_tx_ctl_stru        *pst_first_cb;
    oal_netbuf_stru        *pst_buf;
    oal_uint32              ul_netbuf_len;
    /* ��μ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_netbuf)
     || (OAL_PTR_NULL == pst_amsdu)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_AMPDU, "{hmac_amsdu_encap::input error}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_first_netbuf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);
    pst_first_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_first_netbuf);
    pst_buf = * pst_netbuf;
    pst_cb  = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    pst_first_cb->us_mpdu_bytes += pst_cb->us_mpdu_bytes;

#if 0
    /* WLAN TO WLAN �� AMSDU���� */
    if ((FRW_EVENT_TYPE_WLAN_DTX == pst_cb->en_event_type)
        && ((OAL_TRUE == pst_cb->en_is_amsdu)))
    {
        hmac_tx_netbuf_list_enqueue(&pst_amsdu->st_msdu_head, pst_buf, pst_cb->uc_netbuf_num);

        /* ����amsdu��Ϣ */
        pst_amsdu->uc_msdu_num += pst_cb->uc_netbuf_num;
        pst_amsdu->us_amsdu_size += pst_cb->us_mpdu_len;
        pst_amsdu->uc_netbuf_num += pst_cb->uc_netbuf_num;

        return OAL_SUCC;
    }
#endif

    /* �ݴ�����ʣ��ռ���Ϣ */
    ul_headroom = oal_netbuf_headroom(pst_buf);
    ul_tailroom = oal_netbuf_tailroom(pst_buf);
    if (ul_framelen < oal_netbuf_get_len(pst_buf))
    {
        ul_netbuf_len = oal_netbuf_get_len(pst_buf);
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_amsdu_encap::framelen[%d] < netbuflen[%d]!}", ul_framelen, ul_netbuf_len);
        return OAL_FAIL;
    }

    uc_align    = (oal_uint8)(ul_framelen - oal_netbuf_get_len(pst_buf));

    OAM_INFO_LOG3(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::headroom[%d] tailroom[%d] offset[%d].}", ul_headroom, ul_tailroom, uc_align);

    /* ͷ��ʣ��ռ䲻����Ҫ��չͷ���ռ� */
    if (OAL_UNLIKELY(ul_headroom < SNAP_LLC_FRAME_LEN))
    {
        OAM_INFO_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::headroom[%d] need realloc.}", ul_headroom);
        pst_buf = oal_netbuf_realloc_headroom(pst_buf, (SNAP_LLC_FRAME_LEN - ul_headroom));
        if (OAL_PTR_NULL == pst_buf)
        {
            OAM_ERROR_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::headroom[%d] realloc fail.}", ul_headroom);
            return OAL_FAIL;
        }
        *pst_netbuf = pst_buf;
    }

    /* �ݴ���̫��ͷ����Ϣ */
    st_ether_head.us_ether_type = ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->us_ether_type;
    oal_set_mac_addr(st_ether_head.auc_ether_dhost, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_dhost);
    oal_set_mac_addr(st_ether_head.auc_ether_shost, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_shost);
    oal_set_mac_addr(pst_amsdu->auc_eth_da, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_dhost);
    oal_set_mac_addr(pst_amsdu->auc_eth_sa, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_shost);

    /* ��дsnapͷ */
    pst_snap_head = (mac_llc_snap_stru *)oal_netbuf_pull(pst_buf, ETHER_HDR_LEN - SNAP_LLC_FRAME_LEN);
    if (OAL_PTR_NULL == pst_snap_head)
    {
        return OAL_FAIL;
    }

    pst_snap_head->uc_llc_dsap      = SNAP_LLC_LSAP;
    pst_snap_head->uc_llc_ssap      = SNAP_LLC_LSAP;
    pst_snap_head->uc_control       = LLC_UI;
    pst_snap_head->auc_org_code[0]  = SNAP_RFC1042_ORGCODE_0;
    pst_snap_head->auc_org_code[1]  = SNAP_RFC1042_ORGCODE_1;
    pst_snap_head->auc_org_code[2]  = SNAP_RFC1042_ORGCODE_2;
    pst_snap_head->us_ether_type    = st_ether_head.us_ether_type;

    /* ��дamsdu��֡ͷ */
    pst_amsdu_head = (mac_ether_header_stru *)oal_netbuf_push(pst_buf, ETHER_HDR_LEN);

    oal_set_mac_addr(pst_amsdu_head->auc_ether_dhost, st_ether_head.auc_ether_dhost);
    oal_set_mac_addr(pst_amsdu_head->auc_ether_shost, st_ether_head.auc_ether_shost);
    pst_amsdu_head->us_ether_type = oal_byteorder_host_to_net_uint16((oal_uint16)(oal_netbuf_get_len(pst_buf) - ETHER_HDR_LEN));

    /* β���ռ䲻���ֽڶ�������չβ���ռ� */
    if (OAL_UNLIKELY(ul_tailroom < uc_align))
    {
        OAM_INFO_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::tailroom[%d] need realloc.}", ul_tailroom);
        pst_buf = oal_netbuf_realloc_tailroom(pst_buf, uc_align - ul_tailroom);
        if (OAL_PTR_NULL == pst_buf)
        {
            OAM_ERROR_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::tailroom[%d] realloc fail.}", ul_tailroom);
            return OAL_FAIL;
        }
        *pst_netbuf = pst_buf;
    }

    oal_netbuf_put(pst_buf, uc_align);

    pst_amsdu->uc_last_pad_len = uc_align;

    /* ����amsdu��Ϣ */
    pst_amsdu->uc_msdu_num++;
    pst_amsdu->us_amsdu_size += (oal_uint16)oal_netbuf_get_len(pst_buf);

    /* ����frame len */
    pst_cb->us_mpdu_len = (oal_uint16)oal_netbuf_get_len(pst_buf);

    OAM_INFO_LOG2(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::msdu_num[%d] amsdu_size[%d].}", pst_amsdu->uc_msdu_num, pst_amsdu->us_amsdu_size);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_amsdu_send
 ��������  : ����amsdu
 �������  : pst_user: �û��ṹ��ָ��
             pst_amsdu: Ҫ���͵�amsdu
 �������  : ��
 �� �� ֵ  : �ɹ�OAL_SUCC��ʧ��OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_amsdu_send(hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, hmac_amsdu_stru *pst_amsdu)
{
    frw_event_mem_stru *pst_amsdu_send_event_mem;
    frw_event_stru     *pst_amsdu_send_event;
    oal_uint32          ul_ret;
    mac_tx_ctl_stru    *pst_cb;
    oal_netbuf_stru    *pst_buf_temp;
    oal_netbuf_stru    *pst_net_buf;
    dmac_tx_event_stru *pst_amsdu_event;
    mac_ieee80211_qos_htc_frame_stru *mac_header;

    /* ��μ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user) || (OAL_PTR_NULL == pst_amsdu)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_AMPDU, "{hmac_amsdu_send::input error %x %x %x}", pst_vap, pst_user, pst_amsdu);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��dmac���͵�amsdu��ص���Ϣ�Լ�802.11ͷ�ҽ� */
    pst_net_buf = oal_netbuf_peek(&(pst_amsdu->st_msdu_head));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_buf))
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::pst_net_buf null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_net_buf);
    pst_cb->us_mpdu_len         = pst_amsdu->us_amsdu_size - pst_amsdu->uc_last_pad_len;
    pst_cb->uc_mpdu_num         = 1;

    /* Ϊ����amsdu��װ802.11ͷ */
    ul_ret = hmac_tx_encap(pst_vap, pst_user, pst_net_buf);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        pst_buf_temp = oal_netbuf_delist(&(pst_amsdu->st_msdu_head));

        oal_netbuf_free(pst_buf_temp);

        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);

        OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::hmac_tx_encap failed[%d]}", ul_ret);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʾamsdu */
    mac_header                  = (mac_ieee80211_qos_htc_frame_stru *)pst_cb->pst_frame_header;
    mac_header->bit_qc_amsdu    = 1;

    /* �����һ����֡��PADȥ�� */
    oal_netbuf_trim(pst_net_buf, pst_amsdu->uc_last_pad_len);

    /* ���ֻ��һ��֡(amsdu��ʱ���Σ�tid��ֻ��һ��amsdu�ȴ��ۺϣ�����һֱû�б��
       msdu����)����ȥ����֡����̫��ͷ�����շ�AMSDU����
    */
    if (1 == pst_amsdu->uc_msdu_num)
    {
        OAM_INFO_LOG0(0, OAM_SF_AMSDU, "{hmac_amsdu_send::this amsdu has only one subframe sent as msdu");
        oal_netbuf_pull(pst_net_buf, ETHER_HDR_LEN);
        if ( WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode)
        {
           oal_set_mac_addr(pst_cb->pst_frame_header->auc_address3, pst_amsdu->auc_eth_da);
        }
        else if (!(pst_cb->en_use_4_addr)) /*����AP*/
        {
           oal_set_mac_addr(pst_cb->pst_frame_header->auc_address3, pst_amsdu->auc_eth_sa);
        }
        else /*WDS  TBD �ݲ�֧��*/
        {
            oal_set_mac_addr(pst_cb->pst_frame_header->auc_address3, pst_amsdu->auc_eth_da);/* ��ַ3�� DA */
            //oal_set_mac_addr(pst_cb->pst_frame_header->auc_address4, pst_amsdu->auc_eth_sa);/* ��ַ4�� SA */
        }

        pst_cb->en_is_amsdu = OAL_FALSE;
        pst_cb->us_mpdu_len -= ETHER_HDR_LEN;
        mac_header->bit_qc_amsdu = 0;
    }

    /* ����ͷβ���� */
    if (OAL_PTR_NULL != oal_netbuf_tail(&pst_amsdu->st_msdu_head) && OAL_PTR_NULL != oal_netbuf_peek(&pst_amsdu->st_msdu_head))
    {
        OAL_NETBUF_PREV(oal_netbuf_peek(&pst_amsdu->st_msdu_head)) = OAL_PTR_NULL;
        OAL_NETBUF_NEXT(oal_netbuf_tail(&pst_amsdu->st_msdu_head)) = OAL_PTR_NULL;
    }
    /* ���¼� */
    pst_amsdu_send_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_amsdu_send_event_mem))
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::pst_amsdu_send_event_mem null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���¼�ͷ */
    pst_amsdu_send_event = (frw_event_stru *)(pst_amsdu_send_event_mem->puc_data);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_amsdu_send_event))
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::pst_amsdu_send_event null}");
        FRW_EVENT_FREE(pst_amsdu_send_event_mem);
        return OAL_ERR_CODE_PTR_NULL;
    }

    FRW_EVENT_HDR_INIT(&(pst_amsdu_send_event->st_event_hdr),
                        FRW_EVENT_TYPE_HOST_DRX,
                        DMAC_TX_HOST_DRX,
                        OAL_SIZEOF(dmac_tx_event_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_vap->st_vap_base_info.uc_chip_id,
                        pst_vap->st_vap_base_info.uc_device_id,
                        pst_vap->st_vap_base_info.uc_vap_id);

    pst_amsdu_send_event = (frw_event_stru *)(pst_amsdu_send_event_mem->puc_data);

    pst_amsdu_event = (dmac_tx_event_stru *)(pst_amsdu_send_event->auc_event_data);
    pst_amsdu_event->pst_netbuf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);

    ul_ret = frw_event_dispatch_event(pst_amsdu_send_event_mem);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
    #ifdef _PRE_DEBUG_MODE
        hmac_free_netbuf_list(pst_amsdu_event->pst_netbuf);

        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "hmac_amsdu_send::frw_event_dispatch_event fail[%d]", ul_ret);
    #else
        hmac_free_netbuf_list(pst_amsdu_event->pst_netbuf);
    #endif
    }

    /* ����amsdu�ṹ����Ϣ */
    pst_amsdu->us_amsdu_size = 0;
    pst_amsdu->uc_msdu_num   = 0;
    oal_netbuf_list_head_init(&pst_amsdu->st_msdu_head);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_amsdu_send_event_mem);

    OAM_INFO_LOG0(0, OAM_SF_AMSDU, "{hmac_amsdu_send::amsdu send success.");

    return  ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_build_netbuf
 ��������  : �ۺ���װamsdu
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_amsdu_build_netbuf(hmac_vap_stru *pst_vap, hmac_amsdu_stru *pst_amsdu, oal_netbuf_stru *pst_buf)
{
    oal_uint16       us_buf_len;
    oal_uint16       us_offset;
    oal_netbuf_stru *pst_dest_buf;


    us_buf_len = (oal_uint16)oal_netbuf_get_len(pst_buf);
    pst_dest_buf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);
    if (OAL_PTR_NULL == pst_dest_buf)
    {
        OAM_ERROR_LOG0(0,OAM_SF_AMSDU,"{hmac_amsdu_build_netbuf::oal_netbuf_peek return NULL}");
        oal_netbuf_free(pst_buf);
        return;
    }

    /*����pad�������� ȥ��last pad*/
    if(oal_netbuf_tailroom(pst_dest_buf) < us_buf_len)
    {
        us_buf_len -= pst_amsdu->uc_last_pad_len;
        pst_amsdu->uc_last_pad_len = 0;
    }

    us_offset = (oal_uint16)oal_netbuf_get_len(pst_dest_buf);
    oal_netbuf_put(pst_dest_buf, us_buf_len);
    oal_memcopy(oal_netbuf_data(pst_dest_buf) + us_offset, oal_netbuf_data(pst_buf), us_buf_len);

    oal_netbuf_free(pst_buf);

    return;
}
/*****************************************************************************
 �� �� ��  : hmac_amsdu_alloc_netbuf
 ��������  : ����netbuf���ھۺ���װamsdu
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 hmac_amsdu_alloc_netbuf(hmac_amsdu_stru *pst_amsdu, oal_netbuf_stru *pst_dest_buf, oal_netbuf_stru *pst_buf)
{
    mac_tx_ctl_stru *pst_cb;

    pst_dest_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if(OAL_PTR_NULL == pst_dest_buf)
    {
        return OAL_FAIL;
    }
    /* ��֡����amsduβ�� */
    oal_netbuf_add_to_list_tail(pst_dest_buf, &pst_amsdu->st_msdu_head);

    oal_memcopy(oal_netbuf_cb(pst_dest_buf), oal_netbuf_cb(pst_buf), OAL_SIZEOF(mac_tx_ctl_stru));

    oal_netbuf_copy_queue_mapping(pst_dest_buf, pst_buf);

    pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_dest_buf);
    pst_cb->uc_is_first_msdu    = OAL_TRUE;
    pst_cb->en_is_amsdu         = OAL_TRUE;
    pst_cb->uc_netbuf_num       = 1;
    pst_cb->us_mpdu_bytes       = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_tx_process
 ��������  : amsdu�ۺϷ��ʹ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_amsdu_tx_process(hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    oal_uint8           uc_tid_no;
    oal_uint32          ul_frame_len;
    oal_uint32          ul_ret;
    oal_netbuf_stru    *pst_dest_buf = NULL;
    hmac_amsdu_stru    *pst_amsdu;
    mac_tx_ctl_stru    *pst_tx_ctl;

    pst_tx_ctl = (mac_tx_ctl_stru *)(oal_netbuf_cb(pst_buf));

    ul_frame_len = oal_netbuf_get_len(pst_buf);

    /* ��¼�ֽ�������������̫��ͷ���ȣ�ά���� */
    pst_tx_ctl->us_mpdu_bytes = (oal_uint16)(ul_frame_len - ETHER_HDR_LEN);

    uc_tid_no    = pst_tx_ctl->uc_tid;
    pst_amsdu    = &(pst_user->ast_hmac_amsdu[uc_tid_no]);

    if (hmac_tx_amsdu_is_overflow(pst_amsdu, pst_tx_ctl, ul_frame_len, pst_user))
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::the length of amsdu is exceeded, so it is to be sent.}");

        /* ������ʱ�� */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_amsdu->st_amsdu_timer);

        ul_ret = hmac_amsdu_send(pst_vap, pst_user, pst_amsdu);

        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU,
                             "{hmac_amsdu_process::in amsdu notify, in the situation of length or number overflow, amsdu send fails. erro code is %d}", (oal_int32)ul_ret);
            return HMAC_TX_PASS;
        }
    }
    if (0 == pst_amsdu->uc_msdu_num)
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::there is no msdu in the amsdu.}");

        oal_netbuf_list_head_init(&(pst_amsdu->st_msdu_head));

        /* ����netbuf���ھۺ�amsdu */
        if(OAL_SUCC != hmac_amsdu_alloc_netbuf(pst_amsdu, pst_dest_buf, pst_buf))
        {
            OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::failed to alloc netbuf.}");
            return HMAC_TX_DROP_AMSDU_ENCAP_FAIL;
        }

        /* ������ʱ�� */
        FRW_TIMER_CREATE_TIMER(&pst_amsdu->st_amsdu_timer,
                               hmac_amsdu_tx_timeout_process,
                               HMAC_AMSDU_LIFE_TIME,
                               pst_amsdu,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_vap->st_vap_base_info.ul_core_id);

    }
    /* 4�ֽڶ�����֡�ĳ��� */
    ul_frame_len = OAL_ROUNDUP(ul_frame_len, 4);

    ul_ret = hmac_amsdu_encap_hdr(pst_amsdu, &pst_buf, ul_frame_len);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{in amsdu notify, amsdu encapsulation fails. erro code is %d.}", (oal_int32)ul_ret);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_AMSDU_ENCAP_FAIL;
    }

    /*����ۺ�amsdu ��װbuffer*/
    hmac_amsdu_build_netbuf(pst_vap, pst_amsdu, pst_buf);

    return HMAC_TX_BUFF;
}

/*****************************************************************************
 �� �� ��  : hmac_tx_amsdu_is_overflow
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  oal_bool_enum_uint8 hmac_tx_amsdu_is_overflow(
                hmac_amsdu_stru    *pst_amsdu,
                mac_tx_ctl_stru    *pst_tx_ctl,
                oal_uint32          ul_frame_len,
                hmac_user_stru     *pst_user)
{
    mac_tx_ctl_stru     *pst_head_ctl;
    oal_netbuf_stru     *pst_head_buf;

    if (0 == pst_amsdu->uc_msdu_num)
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::uc_msdu_num=0.}");
        return OAL_FALSE;
    }

    pst_head_buf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);
    if (OAL_PTR_NULL == pst_head_buf)
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::pst_head_buf null.}");
        return OAL_FALSE;
    }

    pst_head_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_head_buf);
    /* amsdu��Ϊ�գ�����amsdu�е���֡��Դ(lan����wlan)�뵱ǰҪ��װ��netbuf��ͬ����amsdu���ͳ�ȥ��
       ����������Ϊ�ڷ���������ͷ�һ��mpduʱ���Ǹ��ݵ�һ��netbuf��cb����д���¼�������ѡ���ͷŲ��ԣ�
       ���һ��mpdu�е�netbuf��Դ��ͬ��������ڴ�й©
    */
    if (pst_tx_ctl->en_event_type != pst_head_ctl->en_event_type)
    {
        OAM_INFO_LOG2(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::en_event_type mismatched. %d %d.}",
                      pst_tx_ctl->en_event_type, pst_head_ctl->en_event_type);
        return OAL_TRUE;
    }

    OAM_INFO_LOG3(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::us_amsdu_size=%d uc_msdu_num=%d us_amsdu_maxsize=%d.}",
                  pst_amsdu->us_amsdu_size, pst_amsdu->uc_msdu_num, pst_amsdu->us_amsdu_maxsize);

    /* payload + padmax(3) ���ܴ���1568 */
    if (((pst_amsdu->us_amsdu_size + ul_frame_len + SNAP_LLC_FRAME_LEN + 3) > 1568)
     || ((pst_amsdu->uc_msdu_num + 1) > pst_amsdu->uc_amsdu_maxnum) || ((pst_amsdu->us_amsdu_size + ul_frame_len + SNAP_LLC_FRAME_LEN) > WLAN_AMSDU_FRAME_MAX_LEN))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

#elif(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

/*****************************************************************************
 �� �� ��  : hmac_amsdu_encap
 ��������  : amsdu��֡ͷ��װ
 �������  : pst_amsdu: amsdu�ṹ��ָ��
             pst_buf: �¼������֡
             ul_framelen: �����ĳ���
 �������  : ��
 �� �� ֵ  : �ɹ�:OAL_SUCC;ʧ��OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_amsdu_encap(hmac_amsdu_stru *pst_amsdu, oal_netbuf_stru *pst_buf, oal_uint32 ul_framelen)
{
    oal_uint32              ul_headroom;    /* �ݴ�skbʣ��ͷ���ռ� */
    oal_uint32              ul_tailroom;    /* �ݴ�skbʣ��β���ռ� */
    oal_uint8               uc_align;       /* Ϊ4�ֽڶ���β����Ҫ��ƫ���� */
    mac_ether_header_stru   st_ether_head;  /* �ݴ���̫��������skb����̫��ͷ */
    mac_ether_header_stru  *pst_amsdu_head; /* Ϊ��дamsdu��֡ͷ����ʱָ�� */
    mac_llc_snap_stru      *pst_snap_head;  /* Ϊ��дsnapͷ����ʱָ�� */
    mac_tx_ctl_stru        *pst_cb;
    oal_netbuf_stru        *pst_first_netbuf;
    mac_tx_ctl_stru        *pst_first_cb;

    /* ��μ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_buf)
     || (OAL_PTR_NULL == pst_amsdu)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_AMPDU, "{hmac_amsdu_encap::input error}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);

    pst_first_netbuf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);
    if (OAL_PTR_NULL != pst_first_netbuf)
    {
        /* ȡ����һ��bufΪ�գ�˵����ʱamsdu���л�û��msdu,��������amsdu���ֽ���,����Ѿ�������msdu��
           ����Ҫ���µ�msdu���ֽ����ӵ���һ��msdu��cb�ֶ��У���Ϊ������װ���mpdu���ֽ�������ά����
        */
        pst_first_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_first_netbuf);
        pst_first_cb->us_mpdu_bytes += pst_cb->us_mpdu_bytes;
    }

#if 0
    /* WLAN TO WLAN �� AMSDU���� */
    if ((FRW_EVENT_TYPE_WLAN_DTX == pst_cb->en_event_type)
        && ((OAL_TRUE == pst_cb->en_is_amsdu)))
    {
        hmac_tx_netbuf_list_enqueue(&pst_amsdu->st_msdu_head, pst_buf, pst_cb->uc_netbuf_num);

        /* ����amsdu��Ϣ */
        pst_amsdu->uc_msdu_num += pst_cb->uc_netbuf_num;
        pst_amsdu->us_amsdu_size += pst_cb->us_mpdu_len;
        pst_amsdu->uc_netbuf_num += pst_cb->uc_netbuf_num;

        return OAL_SUCC;
    }
#endif

    /* �ݴ�����ʣ��ռ���Ϣ */
    ul_headroom = oal_netbuf_headroom(pst_buf);
    ul_tailroom = oal_netbuf_tailroom(pst_buf);
    if (ul_framelen < oal_netbuf_get_len(pst_buf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_amsdu_encap::framelen[%d] < netbuflen[%d]!}", ul_framelen, oal_netbuf_get_len(pst_buf));
        return OAL_FAIL;
    }

    uc_align    = (oal_uint8)(ul_framelen - oal_netbuf_get_len(pst_buf));

    OAM_INFO_LOG3(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::headroom[%d] tailroom[%d] offset[%d].}", ul_headroom, ul_tailroom, uc_align);

    /* ͷ��ʣ��ռ䲻����Ҫ��չͷ���ռ� */
    if (OAL_UNLIKELY(ul_headroom < SNAP_LLC_FRAME_LEN))
    {
        OAM_INFO_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::headroom[%d] need realloc.}", ul_headroom);
        pst_buf = oal_netbuf_realloc_headroom(pst_buf, (SNAP_LLC_FRAME_LEN - ul_headroom));
        if (OAL_PTR_NULL == pst_buf)
        {
            OAM_ERROR_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::headroom[%d] realloc fail.}", ul_headroom);
            return OAL_FAIL;
        }
    }

    /* �ݴ���̫��ͷ����Ϣ */
    st_ether_head.us_ether_type = ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->us_ether_type;
    oal_set_mac_addr(st_ether_head.auc_ether_dhost, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_dhost);
    oal_set_mac_addr(st_ether_head.auc_ether_shost, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_shost);
    oal_set_mac_addr(pst_amsdu->auc_eth_da, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_dhost);
    oal_set_mac_addr(pst_amsdu->auc_eth_sa, ((mac_ether_header_stru *)oal_netbuf_data(pst_buf))->auc_ether_shost);

    /* ��дsnapͷ */
    pst_snap_head = (mac_llc_snap_stru *)oal_netbuf_pull(pst_buf, ETHER_HDR_LEN - SNAP_LLC_FRAME_LEN);
    if (OAL_PTR_NULL == pst_snap_head)
    {
        return OAL_FAIL;
    }

    pst_snap_head->uc_llc_dsap      = SNAP_LLC_LSAP;
    pst_snap_head->uc_llc_ssap      = SNAP_LLC_LSAP;
    pst_snap_head->uc_control       = LLC_UI;
    pst_snap_head->auc_org_code[0]  = SNAP_RFC1042_ORGCODE_0;
    pst_snap_head->auc_org_code[1]  = SNAP_RFC1042_ORGCODE_1;
    pst_snap_head->auc_org_code[2]  = SNAP_RFC1042_ORGCODE_2;
    pst_snap_head->us_ether_type    = st_ether_head.us_ether_type;

    /* ��дamsdu��֡ͷ */
    pst_amsdu_head = (mac_ether_header_stru *)oal_netbuf_push(pst_buf, ETHER_HDR_LEN);

    oal_set_mac_addr(pst_amsdu_head->auc_ether_dhost, st_ether_head.auc_ether_dhost);
    oal_set_mac_addr(pst_amsdu_head->auc_ether_shost, st_ether_head.auc_ether_shost);
    pst_amsdu_head->us_ether_type = oal_byteorder_host_to_net_uint16((oal_uint16)(oal_netbuf_get_len(pst_buf) - ETHER_HDR_LEN));

    /* β���ռ䲻���ֽڶ�������չβ���ռ� */
    if (OAL_UNLIKELY(ul_tailroom < uc_align))
    {
        OAM_INFO_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::tailroom[%d] need realloc.}", ul_tailroom);
        pst_buf = oal_netbuf_realloc_tailroom(pst_buf, uc_align - ul_tailroom);

        if (OAL_PTR_NULL == pst_buf)
        {
            OAM_ERROR_LOG1(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::tailroom[%d] realloc fail.}", ul_tailroom);
            return OAL_FAIL;
        }
    }

    oal_netbuf_put(pst_buf, uc_align);

    pst_amsdu->uc_last_pad_len = uc_align;

    /* ��֡����amsduβ�� */
    oal_netbuf_add_to_list_tail(pst_buf, &pst_amsdu->st_msdu_head);

    /* ����amsdu��Ϣ */
    pst_amsdu->uc_msdu_num++;
    pst_amsdu->us_amsdu_size += (oal_uint16)oal_netbuf_get_len(pst_buf);

    /* ����frame len */
    pst_cb->us_mpdu_len = (oal_uint16)oal_netbuf_get_len(pst_buf);

    OAM_INFO_LOG2(0, OAM_SF_AMSDU, "{hmac_amsdu_encap::msdu_num[%d] amsdu_size[%d].}", pst_amsdu->uc_msdu_num, pst_amsdu->us_amsdu_size);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_send
 ��������  : ����amsdu
 �������  : pst_user: �û��ṹ��ָ��
             pst_amsdu: Ҫ���͵�amsdu
 �������  : ��
 �� �� ֵ  : �ɹ�OAL_SUCC��ʧ��OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_amsdu_send(hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, hmac_amsdu_stru *pst_amsdu)
{
    frw_event_mem_stru *pst_amsdu_send_event_mem;
    frw_event_stru     *pst_amsdu_send_event;
    oal_uint32          ul_ret;
    mac_tx_ctl_stru    *pst_cb;
    oal_uint32          ul_index;
    oal_netbuf_stru    *pst_buf_temp;
    oal_netbuf_stru    *pst_net_buf;
    dmac_tx_event_stru *pst_amsdu_event;
#ifdef _PRE_DEBUG_MODE
    oal_uint16          us_buf_num = 0;
#endif

    /* ��μ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user) || (OAL_PTR_NULL == pst_amsdu)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_AMPDU, "{hmac_amsdu_send::input error %x %x %x}", pst_vap, pst_user, pst_amsdu);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��dmac���͵�amsdu��ص���Ϣ�Լ�802.11ͷ�ҽ� */
    pst_net_buf = oal_netbuf_peek(&(pst_amsdu->st_msdu_head));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_buf))
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::pst_net_buf null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_net_buf);
    pst_cb->en_is_amsdu         = OAL_TRUE;
    pst_cb->us_mpdu_len         = pst_amsdu->us_amsdu_size - pst_amsdu->uc_last_pad_len;
    pst_cb->uc_is_first_msdu                  = OAL_TRUE;
    pst_cb->uc_netbuf_num       = pst_amsdu->uc_msdu_num;
    pst_cb->uc_mpdu_num         = 1;

    /* Ϊ����amsdu��װ802.11ͷ */
    ul_ret = hmac_tx_encap(pst_vap, pst_user, pst_net_buf);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        for (ul_index = 0; ul_index < pst_amsdu->uc_msdu_num; ul_index++)
        {
            pst_buf_temp = oal_netbuf_delist(&(pst_amsdu->st_msdu_head));

            oal_netbuf_free(pst_buf_temp);

            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        }

        OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::hmac_tx_encap failed[%d]}", ul_ret);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����һ����֡��PADȥ�� */
    pst_buf_temp = oal_netbuf_tail(&pst_amsdu->st_msdu_head);
    if (OAL_PTR_NULL == pst_buf_temp)
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::pst_buf_temp null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_netbuf_trim(pst_buf_temp, pst_amsdu->uc_last_pad_len);

    /* ���ֻ��һ��֡(amsdu��ʱ���Σ�tid��ֻ��һ��amsdu�ȴ��ۺϣ�����һֱû�б��
       msdu����)����ȥ����֡����̫��ͷ�����շ�AMSDU����
    */
    if (1 == pst_amsdu->uc_msdu_num)
    {
        OAM_INFO_LOG0(0, OAM_SF_AMSDU, "{hmac_amsdu_send::this amsdu has only one subframe sent as msdu");
        oal_netbuf_pull(pst_buf_temp, ETHER_HDR_LEN);
        if ( WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode)
        {
           oal_set_mac_addr(pst_cb->pst_frame_header->auc_address3, pst_amsdu->auc_eth_da);
        }
        else if (!(pst_cb->en_use_4_addr)) /*����AP*/
        {
           oal_set_mac_addr(pst_cb->pst_frame_header->auc_address3, pst_amsdu->auc_eth_sa);
        }
        else /*WDS  TBD �ݲ�֧��*/
        {
            oal_set_mac_addr(pst_cb->pst_frame_header->auc_address3, pst_amsdu->auc_eth_da);/* ��ַ3�� DA */
            //oal_set_mac_addr(pst_cb->pst_frame_header->auc_address4, pst_amsdu->auc_eth_sa);/* ��ַ4�� SA */
        }

        pst_cb->en_is_amsdu = OAL_FALSE;
        pst_cb->us_mpdu_len -= ETHER_HDR_LEN;
    }

    /* ����ͷβ���� */
    OAL_NETBUF_PREV(oal_netbuf_peek(&pst_amsdu->st_msdu_head)) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(oal_netbuf_tail(&pst_amsdu->st_msdu_head)) = OAL_PTR_NULL;

    /* ���¼� */
    pst_amsdu_send_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_amsdu_send_event_mem))
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_amsdu_send::pst_amsdu_send_event_mem null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���¼�ͷ */
    pst_amsdu_send_event = (frw_event_stru *)(pst_amsdu_send_event_mem->puc_data);

    FRW_EVENT_HDR_INIT(&(pst_amsdu_send_event->st_event_hdr),
                        pst_cb->en_event_type,
                        pst_cb->uc_event_sub_type,
                        OAL_SIZEOF(dmac_tx_event_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_vap->st_vap_base_info.uc_chip_id,
                        pst_vap->st_vap_base_info.uc_device_id,
                        pst_vap->st_vap_base_info.uc_vap_id);

    pst_amsdu_send_event = (frw_event_stru *)(pst_amsdu_send_event_mem->puc_data);

    pst_amsdu_event = (dmac_tx_event_stru *)(pst_amsdu_send_event->auc_event_data);
    pst_amsdu_event->pst_netbuf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);

    ul_ret = frw_event_dispatch_event(pst_amsdu_send_event_mem);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_amsdu_event->pst_netbuf);
        OAL_MEM_FREE((oal_void *)pst_cb->pst_frame_header, OAL_TRUE);
    #ifdef _PRE_DEBUG_MODE
        us_buf_num = hmac_free_netbuf_list(pst_amsdu_event->pst_netbuf);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, us_buf_num);
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "hmac_amsdu_send::frw_event_dispatch_event fail[%d]", ul_ret);
    #else
        hmac_free_netbuf_list(pst_amsdu_event->pst_netbuf);
    #endif
    }

    /* ����amsdu�ṹ����Ϣ */
    pst_amsdu->us_amsdu_size = 0;
    pst_amsdu->uc_msdu_num   = 0;
    oal_netbuf_list_head_init(&pst_amsdu->st_msdu_head);

    /* ����amsdu�̰�����    */
    pst_amsdu->uc_short_pkt_num = 0x00;

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_amsdu_send_event_mem);

    OAM_INFO_LOG0(0, OAM_SF_AMSDU, "{hmac_amsdu_send::amsdu send success.");

    return  ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_update_cap
 ��������  : ����AMSDU�ۺ�����
 �������  : pst_hmac_user_sta: �û��ṹ��ָ��
             pst_amsdu: Ҫ���͵�amsdu
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��06��
    ��    ��   : ywx282918
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_amsdu_update_cap(hmac_user_stru *pst_hmac_user_sta, hmac_amsdu_stru *pst_amsdu)
{
    mac_user_stru      *pst_mac_user;
    oal_uint16      us_amsdu_maxsize;

    /* AMSDU���ۺϳ��Ȼ�ȡ    */
    if ((WLAN_VHT_MODE == pst_hmac_user_sta->st_user_base_info.en_cur_protocol_mode)
    || (WLAN_VHT_ONLY_MODE == pst_hmac_user_sta->st_user_base_info.en_cur_protocol_mode))
    {
        /* VHTģʽ���AMSDU��󳤶ȸ��� */
        pst_mac_user = &pst_hmac_user_sta->st_user_base_info;
        us_amsdu_maxsize  = pst_mac_user->st_vht_hdl.us_max_mpdu_length;

        if (WLAN_80211_CIPHER_SUITE_NO_ENCRYP == pst_mac_user->st_key_info.en_cipher_type)
        {
            /* ��������:11ac�ۺ�11454�ֽ�ʱ���ܻ��½�����������open���ۺϳ���Ϊ7935�ֽ�   */
            if(us_amsdu_maxsize > WLAN_AMSDU_FRAME_MAX_LEN_LONG)
            {
                us_amsdu_maxsize = WLAN_AMSDU_FRAME_MAX_LEN_LONG;
            }
        }
        else
        {
            /* 11ac�ۺ�7935�ֽ�ʱ��asus ac68�������ܳ������������������Ƽ������ۺϳ���Ϊ3839�ֽ�   */
            if(us_amsdu_maxsize > WLAN_AMSDU_FRAME_MAX_LEN_SHORT)
            {
                us_amsdu_maxsize = WLAN_AMSDU_FRAME_MAX_LEN_SHORT;
            }
        }
    }
    else
    {
        /* HTģʽ���AMSDU��󳤶ȸ���  */
        /* 11n������Delimeter MPDU�������ƣ�ǿ��Amsdu��С���Ⱦۺ�   */
        us_amsdu_maxsize = WLAN_AMSDU_FRAME_MAX_LEN_SHORT;
    }

    /* AMSUD��󳤶Ⱥ����ۺϸ�������  */
    pst_amsdu->us_amsdu_maxsize = us_amsdu_maxsize;
    if (1 == pst_hmac_user_sta->st_user_base_info.st_ht_hdl.uc_htc_support)
    {
        /* Account for HT-MAC Header, FCS & Security headers */
        pst_amsdu->us_amsdu_maxsize -= (30 + 4 + 16);
    }
    else
    {
        /* Account for QoS-MAC Header, FCS & Security headers */
        pst_amsdu->us_amsdu_maxsize -= (26 + 4 + 16);
    }

    if (1 == pst_hmac_user_sta->uc_is_wds)
    {
        /* Account for the 4th address in WDS-MAC Header */
        pst_amsdu->us_amsdu_maxsize -= (6);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_process
 ��������  : amsdu������
 �������  : pst_user: �û��ṹ��ָ��
             pst_buf: skb�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��12��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_amsdu_tx_process(hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    oal_uint8           uc_tid_no;
    oal_uint32          ul_frame_len;
    hmac_amsdu_stru    *pst_amsdu;
    oal_uint32          ul_ret;         /* �����ú����ķ���ֵ */
    mac_tx_ctl_stru    *pst_tx_ctl;

    pst_tx_ctl = (mac_tx_ctl_stru *)(oal_netbuf_cb(pst_buf));

    ul_frame_len = oal_netbuf_get_len(pst_buf);

    /* ��¼�ֽ�������������̫��ͷ���ȣ�ά���� */
    pst_tx_ctl->us_mpdu_bytes = (oal_uint16)(ul_frame_len - ETHER_HDR_LEN);

    uc_tid_no    = pst_tx_ctl->uc_tid;

    OAM_INFO_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::uc_tid_no=%d.}", uc_tid_no);

    /* ����CB�ṹ���е�TID��Ϣ�����û��ṹ���л�ȡamsdu�ṹ�� */
    pst_amsdu    = &(pst_user->ast_hmac_amsdu[uc_tid_no]);

    pst_tx_ctl->uc_is_first_msdu = 0;

    /* ��������λ��̬�趨���ۺϳ���   */
    hmac_amsdu_update_cap(pst_user, pst_amsdu);

    /* ��ȡ����amsdu��������֡�����µ���֡������amsdu������󳤶ȣ�����amsdu���װ����֡�������amsdu */
    if (hmac_tx_amsdu_is_overflow(pst_amsdu, pst_tx_ctl, ul_frame_len, pst_user))
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::the length of amsdu is exceeded, so it is to be sent.}");

        /* ������ʱ�� */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_amsdu->st_amsdu_timer);

        ul_ret = hmac_amsdu_send(pst_vap, pst_user, pst_amsdu);

        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU,
                             "{hmac_amsdu_process::in amsdu notify, in the situation of length or number overflow, amsdu send fails. erro code is %d}", (oal_int32)ul_ret);

            return HMAC_TX_PASS;
        }
    }

    /* С��500�ֽڵĶ̰�AMSDU�ۺϲ�����2��,����ᵼ��TX DATAFLOW BREAK�߸��ʳ���,��������   */
    if( pst_amsdu->uc_short_pkt_num >= HMAC_AMSDU_SHORT_PACKET_NUM )
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::the short packet num is overflow, so it is to be sent.}");

        /* ������ʱ�� */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_amsdu->st_amsdu_timer);

        ul_ret = hmac_amsdu_send(pst_vap, pst_user, pst_amsdu);

        /* ��һ��MPDUΪ��AMSDU֡    */
        return HMAC_TX_PASS;
    }

    /* ����ȡ����amsdu��Ϊ�����ʼ��amsdu��msdu����ͷ��¼��amsdu����ʱ�䣬��װ��֡�������amsdu */
    if (0 == pst_amsdu->uc_msdu_num)
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_process::there is no msdu in the amsdu.}");

        oal_netbuf_list_head_init(&(pst_amsdu->st_msdu_head));

        /* ������ʱ�� */
        FRW_TIMER_CREATE_TIMER(&pst_amsdu->st_amsdu_timer,
                               hmac_amsdu_tx_timeout_process,
                               HMAC_AMSDU_LIFE_TIME,
                               pst_amsdu,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_vap->st_vap_base_info.ul_core_id);

    }

    /* 4�ֽڶ�����֡�ĳ��� */
    ul_frame_len = OAL_ROUNDUP(ul_frame_len, 4);

    /* ��ȡ����amsdu��������֡�����µ���֡������amsduû�г�����󳤶ȣ����װ����֡�������amsdu */
    ul_ret = hmac_amsdu_encap(pst_amsdu, pst_buf, ul_frame_len);

    /* С��500�ֽڵĶ̰�����ͳ��    */
    if(OAL_TRUE == hmac_amsdu_is_short_pkt(ul_frame_len))
    {
        pst_amsdu->uc_short_pkt_num++;
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{in amsdu notify, amsdu encapsulation fails. erro code is %d.}", (oal_int32)ul_ret);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);

        return HMAC_TX_DROP_AMSDU_ENCAP_FAIL;
    }

    return HMAC_TX_BUFF;
}


/*****************************************************************************
 �� �� ��  : hmac_tx_amsdu_is_overflow
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  oal_bool_enum_uint8 hmac_tx_amsdu_is_overflow(
                hmac_amsdu_stru    *pst_amsdu,
                mac_tx_ctl_stru    *pst_tx_ctl,
                oal_uint32          ul_frame_len,
                hmac_user_stru     *pst_user)
{
    mac_tx_ctl_stru     *pst_head_ctl;
    oal_netbuf_stru     *pst_head_buf;

    if (0 == pst_amsdu->uc_msdu_num)
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::uc_msdu_num=0.}");
        return OAL_FALSE;
    }

    pst_head_buf = oal_netbuf_peek(&pst_amsdu->st_msdu_head);
    if (OAL_PTR_NULL == pst_head_buf)
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::pst_head_buf null.}");
        return OAL_FALSE;
    }

    pst_head_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_head_buf);
    /* amsdu��Ϊ�գ�����amsdu�е���֡��Դ(lan����wlan)�뵱ǰҪ��װ��netbuf��ͬ����amsdu���ͳ�ȥ��
       ����������Ϊ�ڷ���������ͷ�һ��mpduʱ���Ǹ��ݵ�һ��netbuf��cb����д���¼�������ѡ���ͷŲ��ԣ�
       ���һ��mpdu�е�netbuf��Դ��ͬ��������ڴ�й©
    */
    if (pst_tx_ctl->en_event_type != pst_head_ctl->en_event_type)
    {
        OAM_INFO_LOG2(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::en_event_type mismatched. %d %d.}",
                      pst_tx_ctl->en_event_type, pst_head_ctl->en_event_type);
        return OAL_TRUE;
    }

    OAM_INFO_LOG3(0, OAM_SF_TX, "{hmac_tx_amsdu_is_overflow::us_amsdu_size=%d uc_msdu_num=%d us_amsdu_maxsize=%d.}",
                  pst_amsdu->us_amsdu_size, pst_amsdu->uc_msdu_num, pst_amsdu->us_amsdu_maxsize);
    if (((pst_amsdu->us_amsdu_size + ul_frame_len + SNAP_LLC_FRAME_LEN) > pst_amsdu->us_amsdu_maxsize)
     || ((pst_amsdu->uc_msdu_num + 1) > pst_amsdu->uc_amsdu_maxnum))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_amsdu_notify
 ��������  : amsdu��ں���
 �������  : pst_user: �û��ṹ��ָ��
             pst_buf: skb�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��12��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_amsdu_notify(hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    oal_uint8           uc_tid_no;
    oal_uint32          ul_ret;         /* �����ú����ķ���ֵ */
    mac_tx_ctl_stru    *pst_tx_ctl;
    hmac_amsdu_stru    *pst_amsdu;

    pst_tx_ctl = (mac_tx_ctl_stru *)(oal_netbuf_cb(pst_buf));

    /* ��ȡcb�е�tid��Ϣ */
    uc_tid_no    = pst_tx_ctl->uc_tid;

    pst_amsdu    = &(pst_user->ast_hmac_amsdu[uc_tid_no]);
    oal_spin_lock_bh(&pst_amsdu->st_amsdu_lock);

    /* ��Թر�WMM����QOS֡���� */
    if(OAL_FALSE == pst_user->st_user_base_info.st_cap_info.bit_qos)
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,"{hmac_amsdu_notify::UnQos Frame pass!!}");
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }

    /* �жϸ�tid�Ƿ���ampdu�����֧��amsdu�ķ��� */
    if (0 == HMAC_USER_IS_AMSDU_SUPPORT(pst_user, uc_tid_no))
    {
        OAM_INFO_LOG2(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_notify::AMPDU NOT SUPPORT AMSDU uc_tid_no=%d uc_amsdu_supported=%d}",
                      uc_tid_no, pst_user->uc_amsdu_supported);
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if(OAL_TRUE == oal_netbuf_is_tcp_ack((oal_ip_header_stru *)(oal_netbuf_data(pst_buf) + ETHER_HDR_LEN)))
    {
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    /* Ϊ�˽��ҵ����Сʱping���ӳٵ�����   */
    if(OAL_TRUE == oal_netbuf_is_icmp((oal_ip_header_stru *)(oal_netbuf_data(pst_buf) + ETHER_HDR_LEN)))
    {
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }
#endif
#endif

    if(oal_netbuf_get_len(pst_buf) > WLAN_MSDU_MAX_LEN)
    {
        if(pst_amsdu->uc_msdu_num)
        {
            /* ������ʱ�� */
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_amsdu->st_amsdu_timer);

            ul_ret = hmac_amsdu_send(pst_vap, pst_user, pst_amsdu);
            if(OAL_SUCC != ul_ret)
            {
               OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU,
                             "{hmac_amsdu_process::in amsdu notify, in the situation of length or number overflow, amsdu send fails. erro code is %d}", ul_ret);
            }
            
        }
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }

    /* ���amsdu�����Ƿ�� */
    if (OAL_TRUE != pst_vap->en_amsdu_active)
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_notify::amsdu is unenable in amsdu notify}");
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }

    /* ����û��Ƿ���HT/VHT */
    if (OAL_FALSE == hmac_user_xht_support(pst_user))
    {
        OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_notify::user is not qos in amsdu notify}");
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }

    if (OAL_UNLIKELY(uc_tid_no >= WLAN_TID_MAX_NUM))
    {
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_notify::invalid tid number obtained from the cb in asmdu notify function}");
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
        return HMAC_TX_PASS;
    }

    if (WLAN_TIDNO_VOICE == uc_tid_no)
    {
        OAM_INFO_LOG2(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "{hmac_amsdu_notify::VO TID NOT SUPPORT AMSDU uc_tid_no=%d uc_amsdu_supported=%d",
                                                                           uc_tid_no, pst_user->uc_amsdu_supported);
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);

        return HMAC_TX_PASS;
    }

    ul_ret = hmac_amsdu_tx_process(pst_vap, pst_user, pst_buf);
    oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);
    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_tx_timeout_process
 ��������  : ʱ���ж��¼��Ĵ�����
 �������  : pst_hmac_vap:
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��31��
    ��    ��   : s00304087
    �޸�����   : ���뻥����

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_amsdu_tx_timeout_process(oal_void *p_arg)
{
    hmac_amsdu_stru         *pst_temp_amsdu;
    mac_tx_ctl_stru         *pst_cb;
    hmac_user_stru          *pst_user;
    oal_uint32               ul_ret;
    oal_netbuf_stru         *pst_netbuf;
    hmac_vap_stru           *pst_hmac_vap;
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_AMPDU, "{hmac_amsdu_tx_timeout_process::input null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_temp_amsdu = (hmac_amsdu_stru *)p_arg;

    oal_spin_lock_bh(&pst_temp_amsdu->st_amsdu_lock);

    if (0 == pst_temp_amsdu->uc_msdu_num)
    {
        OAM_WARNING_LOG1(0, OAM_SF_AMSDU, "hmac_amsdu_tx_timeout_process::msdu_num error[%d]", pst_temp_amsdu->uc_msdu_num);
        oal_spin_unlock_bh(&pst_temp_amsdu->st_amsdu_lock);
        return OAL_FAIL;
    }

    /* ����Ҫ���͵�amsdu�µ�һ��msdu��֡��cb�ֶε���ϢѰ�Ҷ�Ӧ�û��ṹ�� */
    pst_netbuf      = oal_netbuf_peek(&pst_temp_amsdu->st_msdu_head);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG1(0, OAM_SF_AMSDU, "hmac_amsdu_tx_timeout_process::pst_netbuf NULL. msdu_num[%d]", pst_temp_amsdu->uc_msdu_num);
        oal_spin_unlock_bh(&pst_temp_amsdu->st_amsdu_lock);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_cb          = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_hmac_vap    = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_cb->uc_tx_vap_index);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        oal_spin_unlock_bh(&pst_temp_amsdu->st_amsdu_lock);
        OAM_ERROR_LOG0(0, OAM_SF_AMPDU, "{hmac_amsdu_tx_timeout_process::pst_hmac_vap null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user        = (hmac_user_stru *)mac_res_get_hmac_user(pst_cb->us_tx_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
    {
        oal_spin_unlock_bh(&pst_temp_amsdu->st_amsdu_lock);
        OAM_ERROR_LOG0(0, OAM_SF_AMPDU, "{hmac_amsdu_tx_timeout_process::pst_user null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_amsdu_send(pst_hmac_vap, pst_user, pst_temp_amsdu);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMSDU, "hmac_amsdu_tx_timeout_process::hmac_amsdu_send fail[%d]", ul_ret);
    }

    oal_spin_unlock_bh(&pst_temp_amsdu->st_amsdu_lock);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_amsdu_init_user
 ��������  : ��ʼ���û�tid���е�AMSDU����ֵ
 �������  : hmac_user_stru *pst_hmac_user_sta
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��12��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��31��
    ��    ��   : s00304087
    �޸�����   : ��ʼ��������

*****************************************************************************/
oal_void hmac_amsdu_init_user(hmac_user_stru *pst_hmac_user_sta)
{
    oal_uint32           ul_amsdu_idx;
    hmac_amsdu_stru     *pst_amsdu;

    if(OAL_PTR_NULL == pst_hmac_user_sta)
    {
        OAM_ERROR_LOG0(0, OAM_SF_AMPDU, "{hmac_amsdu_init_user::pst_hmac_user_sta null}");
        return;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    /* Hi1151ֻ����ʼ������ */
    pst_hmac_user_sta->uc_amsdu_supported = AMSDU_ENABLE_ALL_TID;

    for (ul_amsdu_idx = 0; ul_amsdu_idx < WLAN_WME_MAX_TID_NUM; ul_amsdu_idx++)
    {
        pst_amsdu = &(pst_hmac_user_sta->ast_hmac_amsdu[ul_amsdu_idx]);
        oal_spin_lock_init(&pst_amsdu->st_amsdu_lock);

        pst_amsdu->uc_short_pkt_num = 0x00;

        hmac_amsdu_set_maxnum(pst_amsdu, WLAN_AMSDU_MAX_NUM);
    }
#else
    /* ����amsdu�� */
    pst_hmac_user_sta->us_amsdu_maxsize   = WLAN_AMSDU_FRAME_MAX_LEN_LONG;
    pst_hmac_user_sta->uc_amsdu_supported = AMSDU_ENABLE_ALL_TID;

    for (ul_amsdu_idx = 0; ul_amsdu_idx < WLAN_WME_MAX_TID_NUM; ul_amsdu_idx++)
    {
        pst_amsdu = &(pst_hmac_user_sta->ast_hmac_amsdu[ul_amsdu_idx]);
        hmac_amsdu_set_maxsize(pst_amsdu, pst_hmac_user_sta, WLAN_AMSDU_FRAME_MAX_LEN_LONG);
        hmac_amsdu_set_maxnum(pst_amsdu, WLAN_AMSDU_MAX_NUM);

        oal_spin_lock_init(&pst_amsdu->st_amsdu_lock);
    }
#endif
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

