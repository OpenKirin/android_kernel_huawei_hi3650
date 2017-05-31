/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_blockack.c
  �� �� ��   : ����
  ��    ��   : houyin
  ��������   : 2014��11��25��
  ����޸�   :
  ��������   : AMPDU�ۺϡ�BA����ӿڶ���Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��25��
    ��    ��   : houyin
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
#include "hmac_blockack.h"
#include "hmac_main.h"
#include "hmac_rx_data.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_user.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_BLOCKACK_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_ba_buffer_frame_in_reorder
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC hmac_rx_buf_stru* hmac_ba_buffer_frame_in_reorder(hmac_ba_rx_stru* pst_ba_rx_hdl, oal_uint16 us_seq_num)
{
    oal_uint16          us_buf_index;
    hmac_rx_buf_stru*   pst_rx_buf;

    us_buf_index = (us_seq_num & (WLAN_AMPDU_RX_BUFFER_SIZE - 1));

    pst_rx_buf = &(pst_ba_rx_hdl->ast_re_order_list[us_buf_index]);

    if (1 == pst_rx_buf->in_use)
    {
        hmac_rx_free_netbuf_list(&pst_rx_buf->st_netbuf_head, pst_rx_buf->uc_num_buf);
        OAM_INFO_LOG1(0, OAM_SF_BA, "{hmac_ba_buffer_frame_in_reorder::slot already used, seq[%d].}", us_seq_num);
    }
    else
    {
        pst_ba_rx_hdl->uc_mpdu_cnt++;
    }

    pst_rx_buf->in_use = 1;

    return pst_rx_buf;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_send_frames_with_gap
 ��������  : ��ˢ�����򻺳�����������sequence numberλ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ba_send_frames_with_gap(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_netbuf_head_stru *pst_netbuf_header, oal_uint16 us_last_seqnum, mac_vap_stru *pst_vap)
{
    oal_uint8            uc_num_frms  = 0;
    oal_uint16           us_seq_num;
    hmac_rx_buf_stru    *pst_rx_buf  = OAL_PTR_NULL;
    oal_uint8            uc_loop_index;
    oal_netbuf_stru     *pst_netbuf;

    us_seq_num   = pst_ba_rx_hdl->us_baw_start;

    OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_send_frames_with_gap::to seq[%d].}", us_last_seqnum);

    while(us_seq_num != us_last_seqnum)
    {
        if((pst_rx_buf = hmac_remove_frame_from_reorder_q(pst_ba_rx_hdl, us_seq_num)) != OAL_PTR_NULL)
        {
            pst_ba_rx_hdl->uc_mpdu_cnt--;
            pst_netbuf = oal_netbuf_peek(&pst_rx_buf->st_netbuf_head);
            if (OAL_UNLIKELY(pst_netbuf == OAL_PTR_NULL))
            {
                OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_send_frames_with_gap::gap[%d].\r\n}", us_seq_num);

                us_seq_num = DMAC_BA_SEQNO_ADD(us_seq_num, 1);
                pst_rx_buf->uc_num_buf = 0;

                continue;
            }

            for (uc_loop_index = 0; uc_loop_index < pst_rx_buf->uc_num_buf; uc_loop_index++)
            {
                pst_netbuf = oal_netbuf_delist(&pst_rx_buf->st_netbuf_head);
                OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_FALSE);
                if (OAL_PTR_NULL != pst_netbuf)
                {
                    oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_header);
                }
            }
            pst_rx_buf->uc_num_buf = 0;
            uc_num_frms++;
        }

        us_seq_num = DMAC_BA_SEQNO_ADD(us_seq_num, 1);
    }

    if (0 != pst_ba_rx_hdl->uc_mpdu_cnt)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_send_frames_with_gap::uc_mpdu_cnt=%d.}", pst_ba_rx_hdl->uc_mpdu_cnt);
    }

    return uc_num_frms;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_send_frames_in_order
 ��������  : All MSDUs with sequence number starting from the
             start of the BA-Rx window are processed in order and
             are added to the list which will be passed up to hmac.
             Processing is stopped when the first missing MSDU is encountered.
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  hmac_ba_send_frames_in_order(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_netbuf_head_stru *pst_netbuf_header, mac_vap_stru *pst_vap)
{
    oal_uint16          us_seq_num;
    hmac_rx_buf_stru   *pst_rx_buf  = OAL_PTR_NULL;
    oal_uint8           uc_loop_index;
    oal_netbuf_stru    *pst_netbuf;

    us_seq_num   = pst_ba_rx_hdl->us_baw_start;
    while((pst_rx_buf = hmac_remove_frame_from_reorder_q(pst_ba_rx_hdl, us_seq_num)) != OAL_PTR_NULL)
    {
        pst_ba_rx_hdl->uc_mpdu_cnt--;
        us_seq_num = HMAC_BA_SEQNO_ADD(us_seq_num, 1);
        pst_netbuf = oal_netbuf_peek(&pst_rx_buf->st_netbuf_head);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_send_frames_in_order::[%d] slot error.}", us_seq_num);
            pst_rx_buf->uc_num_buf = 0;
            continue;
        }

        for (uc_loop_index = 0; uc_loop_index < pst_rx_buf->uc_num_buf; uc_loop_index++)
        {
            pst_netbuf = oal_netbuf_delist(&pst_rx_buf->st_netbuf_head);
            OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_FALSE);
            if (OAL_PTR_NULL != pst_netbuf)
            {
                oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_header);
            }
        }

        pst_rx_buf->uc_num_buf = 0;
    }

    return us_seq_num;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_buffer_rx_frame
 ��������  : �����Ļ��������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_ba_buffer_rx_frame(hmac_ba_rx_stru *pst_ba_rx_hdl,
                                                                   hmac_rx_ctl_stru *pst_cb_ctrl,
                                                                   oal_netbuf_head_stru *pst_netbuf_header,
                                                                   oal_uint16 us_seq_num,
                                                                   mac_vap_stru *pst_vap)
{
    hmac_rx_buf_stru   *pst_rx_netbuf = OAL_PTR_NULL;
    oal_netbuf_stru    *pst_netbuf;
    oal_uint8           uc_netbuf_index;
#ifdef _PRE_DEBUG_MODE
    oal_uint32          ul_netbuf_num;
#endif

    /* Get the pointer to the buffered packet */
    pst_rx_netbuf = hmac_ba_buffer_frame_in_reorder(pst_ba_rx_hdl, us_seq_num);

    /* Update the buffered receive packet details */
    pst_rx_netbuf->us_seq_num   = us_seq_num;
    pst_rx_netbuf->uc_num_buf   = pst_cb_ctrl->st_rx_info.bit_buff_nums;  //��ʶ��MPDUռ�õ�netbuff������һ������AMSDU
    pst_rx_netbuf->ul_rx_time   = (oal_uint32)OAL_TIME_GET_STAMP_MS();

#ifdef _PRE_DEBUG_MODE
    ul_netbuf_num = oal_netbuf_get_buf_num(&pst_rx_netbuf->st_netbuf_head);
    if (0 != ul_netbuf_num)
    {
        OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_buffer_rx_frame::%d netbuf miss here.}", ul_netbuf_num);
    }

    if (1 != pst_rx_netbuf->uc_num_buf)
    {
        OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_buffer_rx_frame:find amsdu netbuff cnt %d.}", pst_rx_netbuf->uc_num_buf);
    }
#endif

    /* all buffers of this frame must be deleted from the buf list */
    for (uc_netbuf_index = pst_rx_netbuf->uc_num_buf; uc_netbuf_index > 0; uc_netbuf_index--)
    {
        pst_netbuf = oal_netbuf_delist(pst_netbuf_header);

        OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);
        if (OAL_UNLIKELY(OAL_PTR_NULL != pst_netbuf))
        {
            oal_netbuf_add_to_list_tail(pst_netbuf, &pst_rx_netbuf->st_netbuf_head);
        }
        else
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_buffer_rx_frame:netbuff error in amsdu.}");
        }
    }

}

/*****************************************************************************
 �� �� ��  : hmac_ba_reorder_rx_data
 ��������  : ������������п����ϴ��ı��ļӵ�buf�����β��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_ba_reorder_rx_data(hmac_ba_rx_stru        *pst_ba_rx_hdl,
                                                        oal_netbuf_head_stru   *pst_netbuf_header,
                                                        mac_vap_stru           *pst_vap,
                                                        oal_uint16              us_seq_num)
{
    oal_uint8 uc_seqnum_pos;
    oal_uint16 us_temp_winend;
    oal_uint16 us_temp_winstart;

    uc_seqnum_pos = hmac_ba_seqno_bound_chk(pst_ba_rx_hdl->us_baw_start, pst_ba_rx_hdl->us_baw_end, us_seq_num);

    if(DMAC_BA_BETWEEN_SEQLO_SEQHI == uc_seqnum_pos)
    {
        pst_ba_rx_hdl->us_baw_start = hmac_ba_send_frames_in_order(pst_ba_rx_hdl, pst_netbuf_header, pst_vap);
        pst_ba_rx_hdl->us_baw_end   = DMAC_BA_SEQNO_ADD(pst_ba_rx_hdl->us_baw_start, (pst_ba_rx_hdl->us_baw_size - 1));
    }
    else if(DMAC_BA_GREATER_THAN_SEQHI == uc_seqnum_pos)
    {
        us_temp_winend   = us_seq_num;
        us_temp_winstart = HMAC_BA_SEQNO_SUB(us_temp_winend, (pst_ba_rx_hdl->us_baw_size - 1));

        hmac_ba_send_frames_with_gap(pst_ba_rx_hdl, pst_netbuf_header, us_temp_winstart, pst_vap);
        pst_ba_rx_hdl->us_baw_start = us_temp_winstart;
        pst_ba_rx_hdl->us_baw_start = hmac_ba_send_frames_in_order(pst_ba_rx_hdl, pst_netbuf_header, pst_vap);
        pst_ba_rx_hdl->us_baw_end   = HMAC_BA_SEQNO_ADD(pst_ba_rx_hdl->us_baw_start, (pst_ba_rx_hdl->us_baw_size - 1));
    }
    else
    {
        OAM_INFO_LOG3(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_reorder_rx_data::else branch seqno[%d] ws[%d] we[%d].}",
                      us_seq_num, pst_ba_rx_hdl->us_baw_start, pst_ba_rx_hdl->us_baw_end);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_ba_flush_reorder_q
 ��������  : ��ˢ���������
 �������  : pst_rx_ba: ���ջỰ���
 �������  : pst_rx_ba: ���ջỰ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ba_flush_reorder_q(hmac_ba_rx_stru *pst_rx_ba)
{
    hmac_rx_buf_stru   *pst_rx_buf = OAL_PTR_NULL;
    oal_uint16          us_index;

    for (us_index = 0; us_index < WLAN_AMPDU_RX_BUFFER_SIZE; us_index++)
    {
        pst_rx_buf = &(pst_rx_ba->ast_re_order_list[us_index]);

        if (OAL_TRUE == pst_rx_buf->in_use)
        {
            hmac_rx_free_netbuf_list(&pst_rx_buf->st_netbuf_head, pst_rx_buf->uc_num_buf);

            pst_rx_buf->in_use = OAL_FALSE;
            pst_rx_buf->uc_num_buf = 0;
            pst_rx_ba->uc_mpdu_cnt--;
        }
    }

    if (0 != pst_rx_ba->uc_mpdu_cnt)
    {
        OAM_WARNING_LOG1(0, OAM_SF_BA, "{hmac_ba_flush_reorder_q:: %d mpdu cnt left.}", pst_rx_ba->uc_mpdu_cnt);
    }
}
/*****************************************************************************
 �� �� ��  : hmac_ba_check_rx_aggr
 ��������  : ����Ƿ�����ba��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  hmac_ba_check_rx_aggr(mac_vap_stru               *pst_vap,
                                             mac_ieee80211_frame_stru   *pst_frame_hdr)
{
    /* ��vap�Ƿ���ht */
    if (OAL_FALSE == pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_check_rx_aggr::ht not supported by this vap.}");
        return OAL_FAIL;
    }

    /* �жϸ�֡�ǲ���qos֡ */
    if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
    {
        OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_check_rx_aggr::not qos data.}");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_need_update_hw_baw
 ��������  : �ж��Ƿ���Ҫ����Ӳ����BAW
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_ba_need_update_hw_baw(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_uint16 us_seq_num)
{
    if ((OAL_TRUE == hmac_ba_seqno_lt(us_seq_num, pst_ba_rx_hdl->us_baw_start))
     && (OAL_FALSE == hmac_ba_rx_seqno_lt(us_seq_num, pst_ba_rx_hdl->us_baw_start)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_filter_serv
 ��������  : ����ampdu��ÿһ��mpdu ��δȷ�ϱ�����Ҫ���ش�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��OAL_SUCC:��ʾ�쳣�����洦��ֱ��Drop
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ba_filter_serv(
                mac_vap_stru               *pst_vap,
                hmac_user_stru             *pst_hmac_user,
                hmac_rx_ctl_stru           *pst_cb_ctrl,
                mac_ieee80211_frame_stru   *pst_frame_hdr,
                oal_netbuf_head_stru       *pst_netbuf_header,
                oal_bool_enum_uint8        *pen_is_ba_buf)
{
    oal_uint8               uc_tid;
    hmac_ba_rx_stru        *pst_ba_rx_hdl;
    oal_uint16              us_seq_num;
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;
    oal_uint16              us_baw_start_temp;
    oal_uint32              ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf_header ||
        OAL_PTR_NULL == pst_hmac_user ||
        OAL_PTR_NULL == pst_cb_ctrl ||
        OAL_PTR_NULL == pst_frame_hdr ||
        OAL_PTR_NULL == pen_is_ba_buf ||
        OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{hmac_ba_filter_serv::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_ba_check_rx_aggr(pst_vap, pst_frame_hdr);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_SUCC;
    }

    /* �����ĵ�ַ�����ȡ���ĵ�tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;
    uc_tid        = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    //OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::uc_tid=%d.}", uc_tid);

    pst_ba_rx_hdl = pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info;
    if (OAL_PTR_NULL == pst_ba_rx_hdl)
    {
        return OAL_SUCC;
    }
    if (DMAC_BA_COMPLETE != pst_ba_rx_hdl->en_ba_status)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::ba_status = %d.", pst_ba_rx_hdl->en_ba_status);
        return OAL_SUCC;
    }

    /* ��ʱ����BA���ڵ����кţ����ڼ����Ƿ���֡�ϱ� */
    us_baw_start_temp = pst_ba_rx_hdl->us_baw_start;

    us_seq_num = mac_get_seq_num((oal_uint8 *)pst_frame_hdr);

    /*DTS2015083108367 ���ݽ��շ���ۺϺͷ�Ƭ�������� */
    if (OAL_TRUE == (oal_bool_enum_uint8)pst_frame_hdr->st_frame_control.bit_more_frag)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::We get a frag_frame[seq_num=%d] When BA_session is set UP!", us_seq_num);
        return OAL_SUCC;
    }

    /* duplicate frame�ж� */
    if (OAL_TRUE == hmac_ba_rx_seqno_lt(us_seq_num, pst_ba_rx_hdl->us_baw_start))
    {
        /* �ϴηǶ�ʱ���ϱ���ֱ��ɾ��duplicate frame֡������ֱ���ϱ� */
        if (OAL_FALSE == pst_ba_rx_hdl->en_timer_triggered)
        {
            /* ȷʵ�Ѿ��յ���֡ */
            /* DTS2016031104629 ������bitmap��¼�հ� ��ֹdup�󶪰� */
            if (hmac_ba_isset(pst_ba_rx_hdl, us_seq_num))
            {
                //OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::duplicate frame,us_seq_num=%d baw_start=%d.",
                //                us_seq_num, pst_ba_rx_hdl->us_baw_start);

                HMAC_USER_STATS_PKT_INCR(pst_hmac_user->ul_rx_pkt_drop, 1);
                return OAL_FAIL;
            }
        }

        return OAL_SUCC;
    }
    /* restart ba timer */
    //frw_timer_restart_timer(&pst_ba_rx_hdl->st_ba_timer, pst_ba_rx_hdl->st_ba_timer.us_timeout, OAL_TRUE);
    if (OAL_TRUE == hmac_ba_seqno_lt(pst_ba_rx_hdl->us_baw_tail, us_seq_num))
    {
        pst_ba_rx_hdl->us_baw_tail = us_seq_num;
    }

    /* ���յ���֡�����кŵ���BAW_START�����һ������֡����Ϊ0����ֱ���ϱ���HMAC */
    if ((us_seq_num == pst_ba_rx_hdl->us_baw_start) && (0 == pst_ba_rx_hdl->uc_mpdu_cnt))
    {
        //OAM_TID_AMPDU_STATS_INCR(pst_tid_queue->pst_tid_ampdu_stat->ul_ba_recipient_direct_up_count, 1);

        pst_ba_rx_hdl->us_baw_start = DMAC_BA_SEQNO_ADD(pst_ba_rx_hdl->us_baw_start, 1);
        pst_ba_rx_hdl->us_baw_end  = DMAC_BA_SEQNO_ADD(pst_ba_rx_hdl->us_baw_end, 1);

        //OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::new packet need not be buffered, ws[%d].}\r\n", pst_ba_rx_hdl->us_baw_start);
        //OAL_IO_PRINT("{hmac_ba_filter_serv::new packet need not be buffered, ws[%d].}\r\n", pst_ba_rx_hdl->us_baw_start);
    }
    else
    {
        //OAM_TID_AMPDU_STATS_INCR(pst_tid_queue->pst_tid_ampdu_stat->ul_ba_recipient_buffer_frame_count, 1);
        //OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::new packet need buffered, ws[%d],sq[%d].}\r\n", pst_ba_rx_hdl->us_baw_start, us_seq_num);
        //OAL_IO_PRINT("{hmac_ba_filter_serv::new packet need buffered, ws[%d],sq[%d].}\r\n", pst_ba_rx_hdl->us_baw_start, us_seq_num);

        /* Buffer the new MSDU */
        *pen_is_ba_buf = OAL_TRUE;

        hmac_ba_buffer_rx_frame(pst_ba_rx_hdl, pst_cb_ctrl, pst_netbuf_header, us_seq_num, pst_vap);

        /* put the reordered netbufs to the end of the list */
        hmac_ba_reorder_rx_data(pst_ba_rx_hdl, pst_netbuf_header, pst_vap, us_seq_num);

        /* Check for Sync loss and flush the reorder queue when one is detected */
        if((pst_ba_rx_hdl->us_baw_tail == DMAC_BA_SEQNO_SUB(pst_ba_rx_hdl->us_baw_start, 1)) &&
            (pst_ba_rx_hdl->uc_mpdu_cnt > 0))
        {
            //OAM_TID_AMPDU_STATS_INCR(pst_tid_queue->pst_tid_ampdu_stat->ul_ba_recipient_sync_loss_count, 1);

            OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::Sync loss and flush the reorder queue.}");
            hmac_ba_flush_reorder_q(pst_ba_rx_hdl);
        }
    }

#if 0 /* ����hmac_ba_need_update_hw_baw�߼������Ҳ�δ�������ķ������κ�ʵ���ԵĲ�����Ӧ�����Ƶ�hmac��Ĳ������� */
    if (OAL_TRUE == hmac_ba_need_update_hw_baw(pst_ba_rx_hdl, us_seq_num))
    {
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_ba_filter_serv::need to check mac ba ssn.}");
    }
#endif
    if (us_baw_start_temp != pst_ba_rx_hdl->us_baw_start)
    {
        pst_ba_rx_hdl->en_timer_triggered = OAL_FALSE;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_reorder_ba_rx_buffer_bar
 ��������  : This function reorders the Reciver buffer and sends frames to the higher
             layer on reception of a Block-Ack-Request frame. It also updates the
             receiver buffer window.
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��29��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_reorder_ba_rx_buffer_bar(hmac_ba_rx_stru *pst_rx_ba, oal_uint16 us_start_seq_num,  mac_vap_stru *pst_vap)
{
    oal_netbuf_head_stru    st_netbuf_head;
    oal_uint8               uc_seqnum_pos;

    if (OAL_PTR_NULL == pst_rx_ba)
    {
        OAM_WARNING_LOG0(0, OAM_SF_BA, "{hmac_reorder_ba_rx_buffer_bar::receive a bar, but ba session doesnot set up.}");
        return;
    }

    /* ��� BAR ��SSN�ʹ��ڵ�start_num���ʱ������Ҫ�ƴ� */
    if(pst_rx_ba->us_baw_start == us_start_seq_num)
    {
        OAM_INFO_LOG0(0, OAM_SF_BA, "{hmac_reorder_ba_rx_buffer_bar::seq is equal to start num.}");
        return;
    }

    oal_netbuf_list_head_init(&st_netbuf_head);

    uc_seqnum_pos = hmac_ba_seqno_bound_chk(pst_rx_ba->us_baw_start, pst_rx_ba->us_baw_end, us_start_seq_num);
    /* ���BAR�ĵ�SSN�ڴ����ڲ��ƴ� */
    if (DMAC_BA_BETWEEN_SEQLO_SEQHI == uc_seqnum_pos)
    {
        hmac_ba_send_frames_with_gap(pst_rx_ba, &st_netbuf_head, us_start_seq_num, pst_vap);
        pst_rx_ba->us_baw_start = us_start_seq_num;
        pst_rx_ba->us_baw_start = hmac_ba_send_frames_in_order(pst_rx_ba, &st_netbuf_head, pst_vap);
        pst_rx_ba->us_baw_end   = HMAC_BA_SEQNO_ADD(pst_rx_ba->us_baw_start, (pst_rx_ba->us_baw_size - 1));

        OAM_INFO_LOG3(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_reorder_ba_rx_buffer_bar::receive a bar, us_baw_start=%d us_baw_end=%d. us_seq_num=%d.}",
          pst_rx_ba->us_baw_start, pst_rx_ba->us_baw_end, us_start_seq_num);

        hmac_rx_lan_frame(&st_netbuf_head);
    }
    else if (DMAC_BA_GREATER_THAN_SEQHI == uc_seqnum_pos)
    {
        /* �쳣 */
        OAM_WARNING_LOG3(pst_vap->uc_vap_id, OAM_SF_BA, "{hmac_reorder_ba_rx_buffer_bar::receive a bar and ssn is out of winsize, us_baw_start=%d us_baw_end=%d, us_seq_num=%d.}",
          pst_rx_ba->us_baw_start, pst_rx_ba->us_baw_end, us_start_seq_num);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_ba_rx_prepare_bufflist
 ��������  : ������������л�ȡskb��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��21��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ba_rx_prepare_bufflist(hmac_vap_stru *pst_hmac_vap, hmac_rx_buf_stru *pst_rx_buf, oal_netbuf_head_stru *pst_netbuf_head)
{
    oal_netbuf_stru     *pst_netbuf;
    oal_uint8            uc_loop_index;

    pst_netbuf = oal_netbuf_peek(&pst_rx_buf->st_netbuf_head);
    if (pst_netbuf == OAL_PTR_NULL)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_ba_rx_prepare_bufflist::pst_netbuf null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_loop_index = 0; uc_loop_index < pst_rx_buf->uc_num_buf; uc_loop_index++)
    {
        pst_netbuf = oal_netbuf_delist(&pst_rx_buf->st_netbuf_head);
        if (OAL_PTR_NULL != pst_netbuf)
        {
            oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_head);
            //OAL_IO_PRINT("hmac_ba_rx_prepare_bufflist: out 0x%x", pst_netbuf);
        }
        else
        {
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_ba_rx_prepare_bufflist::uc_num_buf in reorder list is error.}");
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_send_reorder_timeout
 ��������  : �ϱ�����������г�ʱ�ı���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ba_send_reorder_timeout(hmac_ba_rx_stru *pst_rx_ba, hmac_vap_stru *pst_hmac_vap, hmac_ba_alarm_stru *pst_alarm_data,
                                                    oal_uint16 *pus_timeout)
{
    oal_uint32                  ul_time_diff;
    oal_uint32                  ul_rx_timeout;
    oal_netbuf_head_stru        st_netbuf_head;
    oal_uint16                  us_baw_head;
    oal_uint16                  us_baw_start;   /* ��������Ĵ�����ʼ���к� */
    hmac_rx_buf_stru           *pst_rx_buf;
    oal_uint8                   uc_buff_count = 0;
    oal_uint32                  ul_ret;
    oal_uint16                  us_baw_end;


    oal_netbuf_list_head_init(&st_netbuf_head);
    us_baw_head     = pst_rx_ba->us_baw_start;
    us_baw_start    = pst_rx_ba->us_baw_start;
    ul_rx_timeout   = (oal_uint32)pst_hmac_vap->us_rx_timeout[WLAN_WME_TID_TO_AC(pst_alarm_data->uc_tid)];
    us_baw_end      = HMAC_BA_SEQNO_ADD(pst_rx_ba->us_baw_tail, 1);

    /* OAM_INFO_LOG2(0, OAM_SF_BA, "{hmac_ba_send_reorder_timeout::us_baw_head=%d us_baw_end=%d.}",
                  us_baw_head, us_baw_end); */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_lock(&pst_rx_ba->st_ba_lock);
#endif

    while (us_baw_head != us_baw_end)
    {
        pst_rx_buf = hmac_get_frame_from_reorder_q(pst_rx_ba, us_baw_head);
        if (OAL_PTR_NULL == pst_rx_buf)
        {
            uc_buff_count++;
            us_baw_head = HMAC_BA_SEQNO_ADD(us_baw_head, 1);
            continue;
        }

        ul_time_diff = (oal_uint32)OAL_TIME_GET_STAMP_MS() - pst_rx_buf->ul_rx_time;
        if (ul_time_diff < ul_rx_timeout)
        {
            /* frw_timer_restart_timer(&pst_rx_ba->st_ba_timer, (oal_uint16)(ul_rx_timeout - ul_time_diff), OAL_TRUE); */
            *pus_timeout = (oal_uint16)(ul_rx_timeout - ul_time_diff);
            break;
        }

        pst_rx_ba->uc_mpdu_cnt--;
        pst_rx_buf->in_use = 0;

        ul_ret = hmac_ba_rx_prepare_bufflist(pst_hmac_vap, pst_rx_buf, &st_netbuf_head);
        if (ul_ret != OAL_SUCC)
        {
            uc_buff_count++;
            us_baw_head = HMAC_BA_SEQNO_ADD(us_baw_head, 1);
            continue;
        }

        uc_buff_count++;
        us_baw_head = HMAC_BA_SEQNO_ADD(us_baw_head, 1);
        pst_rx_ba->us_baw_start = HMAC_BA_SEQNO_ADD(pst_rx_ba->us_baw_start, uc_buff_count);
        pst_rx_ba->us_baw_end   = HMAC_BA_SEQNO_ADD(pst_rx_ba->us_baw_start, (pst_rx_ba->us_baw_size - 1));

        uc_buff_count = 0;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_unlock(&pst_rx_ba->st_ba_lock);
#endif

    /* �жϱ��ζ�ʱ����ʱ�Ƿ���֡�ϱ� */
    if (us_baw_start != pst_rx_ba->us_baw_start)
    {
        //hmac_ba_update_rx_baw(pst_rx_ba, us_baw_start);
        pst_rx_ba->en_timer_triggered = OAL_TRUE;

        //OAL_IO_PRINT("hmac_ba_send_reorder_timeout: old seq %d, new seq %d\r\n", us_baw_start, pst_rx_ba->us_baw_start);
    }

    hmac_rx_lan_frame(&st_netbuf_head);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_timeout_fn
 ��������  : ba�Ự��ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��12��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ba_timeout_fn(oal_void *p_arg)
{
    hmac_ba_rx_stru                    *pst_rx_ba;
    hmac_vap_stru                      *pst_vap;
    hmac_user_stru                     *pst_hmac_user;
    hmac_ba_alarm_stru                 *pst_alarm_data;
    mac_delba_initiator_enum_uint8      en_direction;
    oal_uint8                           uc_tid = 0;
    mac_device_stru                    *pst_mac_device;
    oal_uint16                          us_timeout= 0;

    pst_alarm_data = (hmac_ba_alarm_stru *)p_arg;

    en_direction = pst_alarm_data->en_direction;

    uc_tid = pst_alarm_data->uc_tid;
    if (uc_tid >= WLAN_TID_MAX_NUM)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{hmac_ba_timeout_fn::tid %d overflow.}", uc_tid);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_alarm_data->uc_vap_id);
    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{hmac_ba_timeout_fn::pst_vap null. vap id %d.}", pst_alarm_data->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_alarm_data->us_mac_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{hmac_ba_timeout_fn::pst_hmac_user null. user idx %d.}", pst_alarm_data->us_mac_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{hmac_ba_timeout_fn::pst_mac_device null. uc_device_id id %d.}", pst_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }


//    if (pst_mac_device->ul_core_id >= 1)
    /* DTS2015030604659,����Ҫʹ��core num����Ϊ�ж�  */
    if (pst_mac_device->ul_core_id >= WLAN_FRW_MAX_NUM_CORES)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{hmac_ba_timeout_fn::core id %d overflow.}", pst_mac_device->ul_core_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    if (MAC_RECIPIENT_DELBA == en_direction)
    {
        pst_rx_ba = (hmac_ba_rx_stru *)pst_alarm_data->pst_ba;

        if (OAL_PTR_NULL == pst_rx_ba)
        {
            OAM_ERROR_LOG0(0, OAM_SF_BA, "{hmac_ba_timeout_fn::pst_rx_ba is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        us_timeout = pst_vap->us_rx_timeout[WLAN_WME_TID_TO_AC(uc_tid)];

        if (pst_rx_ba->uc_mpdu_cnt > 0)
        {
            //OAL_IO_PRINT("{hmac_ba_timeout_fn::us_ba_timeout=%d uc_mpdu_cnt=%d.\r\n}", pst_rx_ba->us_ba_timeout, pst_rx_ba->uc_mpdu_cnt);
            hmac_ba_send_reorder_timeout(pst_rx_ba, pst_vap, pst_alarm_data, &us_timeout);

            //pst_alarm_data->us_timeout_times = 0;
        }
#if 0
        else
        {
            /* frw_timer_restart_timer(&pst_rx_ba->st_ba_timer, pst_vap->us_rx_timeout[WLAN_WME_TID_TO_AC(pst_alarm_data->uc_tid)], OAL_TRUE); */
            pst_alarm_data->us_timeout_times++;
        }
#endif
        FRW_TIMER_CREATE_TIMER(&(pst_hmac_user->ast_tid_info[uc_tid].st_ba_timer),
                               hmac_ba_timeout_fn,
                               us_timeout,
                               pst_alarm_data,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_mac_device->ul_core_id);
#if 0  /*����us_timeout_timesû��ʹ�ã�������Ҫ��ֵ*/
        if (pst_alarm_data->us_timeout_times == pst_vap->us_del_timeout && pst_vap->us_del_timeout != 0)
        {
            //pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_alarm_data->us_mac_user_idx);
            //uc_tid        = pst_alarm_data->uc_tid;
            //dmac_mgmt_delba(pst_vap, pst_dmac_user, uc_tid, en_direction, MAC_QSTA_TIMEOUT);
            pst_alarm_data->us_timeout_times = 0;
        }
#endif
    }
    else
    {
        /* tx ba��ɾ�� */
        FRW_TIMER_CREATE_TIMER(&(pst_hmac_user->ast_tid_info[uc_tid].st_ba_timer),
                               hmac_ba_timeout_fn,
                               pst_vap->us_rx_timeout[WLAN_WME_TID_TO_AC(uc_tid)],
                               pst_alarm_data,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_mac_device->ul_core_id);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_reset_rx_handle
 ��������  : ����rx ba�ṹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��5��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ba_reset_rx_handle(mac_device_stru *pst_mac_device, hmac_ba_rx_stru **ppst_rx_ba, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_aging)
{
    hmac_vap_stru    *pst_hmac_vap;
    hmac_user_stru   *pst_hmac_user;
    oal_bool_enum     en_need_del_lut = OAL_TRUE;

    if (OAL_UNLIKELY((OAL_PTR_NULL == *ppst_rx_ba) || (OAL_TRUE != (*ppst_rx_ba)->en_is_ba)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_BA, "{hmac_ba_reset_rx_handle::rx ba not set yet.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (uc_tid >= WLAN_TID_MAX_NUM)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{hmac_ba_reset_rx_handle::tid %d overflow.}", uc_tid);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap((*ppst_rx_ba)->st_alarm_data.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{hmac_ba_reset_rx_handle::pst_hmac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*Step1: disable the flag of ba session*/
    (*ppst_rx_ba)->en_is_ba = OAL_FALSE;

    /*Step2: flush reorder q*/
    hmac_ba_flush_reorder_q(*ppst_rx_ba);

    if (DMAC_INVALID_BA_LUT_INDEX == (*ppst_rx_ba)->uc_lut_index)
    {
        en_need_del_lut = OAL_FALSE;
        OAM_WARNING_LOG1(0, OAM_SF_BA, "{hmac_ba_reset_rx_handle::no need to del lut index, lut index[%d]}\n", (*ppst_rx_ba)->uc_lut_index);
    }

    /*Step3: if lut index is valid, del lut index alloc before*/
    if ((MAC_BA_POLICY_IMMEDIATE == (*ppst_rx_ba)->uc_ba_policy) && (OAL_TRUE == en_need_del_lut))
    {
        hmac_ba_del_lut_index(pst_mac_device->auc_rx_ba_lut_idx_table, (*ppst_rx_ba)->uc_lut_index);
    }

    /*Step4: dec the ba session cnt maitence in device struc*/
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    hmac_rx_ba_session_decr(pst_hmac_vap, uc_tid);
#else
    hmac_rx_ba_session_decr(pst_mac_device, uc_tid);
#endif
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user((*ppst_rx_ba)->st_alarm_data.us_mac_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*Step5: Del Timer*/
    if (pst_hmac_user->ast_tid_info[uc_tid].st_ba_timer.en_is_registerd == OAL_TRUE)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_user->ast_tid_info[uc_tid].st_ba_timer));
    }

    /*Step6: Free rx handle */
    OAL_MEM_FREE(*ppst_rx_ba, OAL_TRUE);
    *ppst_rx_ba = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_check_set_rx_ba_ok
 ��������  : �ӿտڽ���ADDBA_REQ֡�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  hmac_mgmt_check_set_rx_ba_ok(
                hmac_vap_stru     *pst_hmac_vap,
                hmac_ba_rx_stru   *pst_ba_rx_info,
                mac_device_stru   *pst_device)
{
    pst_ba_rx_info->uc_lut_index = DMAC_INVALID_BA_LUT_INDEX;

    /* ������ȷ���ж� */
    if (MAC_BA_POLICY_IMMEDIATE == pst_ba_rx_info->uc_ba_policy)
    {
        if (OAL_FALSE == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11ImmediateBlockAckOptionImplemented)
        {
            /* ��֧��������ȷ�� */
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_check_set_rx_ba_ok::not support immediate Block Ack.}");
            return MAC_INVALID_REQ_PARAMS;
        }
        else
        {
            if (pst_ba_rx_info->en_back_var != MAC_BACK_COMPRESSED)
            {
                /* ��֧�ַ�ѹ����ȷ�� */
                OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_check_set_rx_ba_ok::not support non-Compressed Block Ack.}");
                return MAC_REQ_DECLINED;
            }
        }
    }
    else if (MAC_BA_POLICY_DELAYED == pst_ba_rx_info->uc_ba_policy)
    {
        /* �ӳٿ�ȷ�ϲ�֧�� */
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_check_set_rx_ba_ok::not support delayed Block Ack.}");
        return MAC_INVALID_REQ_PARAMS;
    }
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    if (pst_hmac_vap->uc_rx_ba_session_num > WLAN_MAX_RX_BA)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_check_set_rx_ba_ok::uc_rx_ba_session_num[%d] is up to max.}\r\n",
                         pst_hmac_vap->uc_rx_ba_session_num);
        return MAC_REQ_DECLINED;
    }
#else
    if (pst_device->uc_rx_ba_session_num > WLAN_MAX_RX_BA)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_check_set_rx_ba_ok::uc_rx_ba_session_num[%d] is up to max.}\r\n",
                         pst_device->uc_rx_ba_session_num);
        return MAC_REQ_DECLINED;
    }
#endif

    /* ��ȡBA LUT INDEX */
    pst_ba_rx_info->uc_lut_index = hmac_ba_get_lut_index(pst_device->auc_rx_ba_lut_idx_table, 0, HAL_MAX_BA_LUT_SIZE);

        /* LUT index������ */
    if (DMAC_INVALID_BA_LUT_INDEX == pst_ba_rx_info->uc_lut_index)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_check_set_rx_ba_ok::ba lut index table full.");
        return MAC_REQ_DECLINED;
    }

    return MAC_SUCCESSFUL_STATUSCODE;
}

/*****************************************************************************
 �� �� ��  : hmac_up_rx_bar
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
oal_void  hmac_up_rx_bar(hmac_vap_stru *pst_hmac_vap, dmac_rx_ctl_stru *pst_rx_ctl, oal_netbuf_stru *pst_netbuf)
{
    oal_uint8                 *puc_payload;
    mac_ieee80211_frame_stru  *pst_frame_hdr;
    oal_uint8                 *puc_sa_addr;
    oal_uint8                  uc_tidno;
    hmac_user_stru            *pst_ta_user;
    oal_uint16                 us_start_seqnum;
    hmac_ba_rx_stru           *pst_ba_rx_info;

    pst_frame_hdr = (mac_ieee80211_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));
    puc_sa_addr = pst_frame_hdr->auc_address2;

    /*  ��ȡ�û�ָ�� */
    pst_ta_user = mac_vap_get_hmac_user_by_addr(&(pst_hmac_vap->st_vap_base_info), puc_sa_addr);
    if (OAL_PTR_NULL == pst_ta_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_up_rx_bar::pst_ta_user  is null.}");
        return;
    }

    /* ��ȡ֡ͷ��payloadָ��*/
    puc_payload = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctl->st_rx_info), pst_netbuf);

    /*************************************************************************/
    /*                     BlockAck Request Frame Format                     */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BAR Control|BlockAck Starting    |FCS|  */
    /* |             |        |  |  |           |Sequence number      |   |  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |2          |2                    |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    uc_tidno        = (puc_payload[1] & 0xF0) >> 4;
    us_start_seqnum = mac_get_bar_start_seq_num(puc_payload);

    pst_ba_rx_info  = pst_ta_user->ast_tid_info[uc_tidno].pst_ba_rx_info;

    hmac_reorder_ba_rx_buffer_bar(pst_ba_rx_info, us_start_seqnum, &(pst_hmac_vap->st_vap_base_info));
}
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
oal_bool_enum_uint8 hmac_is_device_ba_setup(void)
{
    oal_uint8 uc_vap_id;
    hmac_vap_stru *pst_hmac_vap;

    for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_is_device_ba_setup pst_mac_vap is null.}");
            continue;
        }
        if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state) &&
            (MAC_VAP_STATE_PAUSE != pst_hmac_vap->st_vap_base_info.en_vap_state))
        {
            continue;
        }
        if ((pst_hmac_vap->uc_tx_ba_session_num != 0) ||
            (pst_hmac_vap->uc_rx_ba_session_num != 0))
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}
#else
oal_bool_enum_uint8 hmac_is_device_ba_setup(void)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_is_device_ba_setup pst_mac_device is null.}");
        return OAL_FALSE;
    }
    if ((pst_mac_device->uc_tx_ba_session_num != 0) ||
        (pst_mac_device->uc_rx_ba_session_num != 0))
    {
        return OAL_TRUE;
    }
    return OAL_FALSE;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

