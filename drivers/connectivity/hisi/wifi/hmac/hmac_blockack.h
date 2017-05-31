/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_blockack.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2013��4��8��
  ����޸�   :
  ��������   : dmac_blockack.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_BLOCKACK_H__
#define __DMAC_BLOCKACK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_ext_if.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_rx_data.h"
#include "hmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_BLOCKACK_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* Default values for receive timeout */
#define HMAC_BA_RX_VO_TIMEOUT      40  /* 40 milliseconds */
#define HMAC_BA_RX_VI_TIMEOUT      100 /* 100 milliseconds */
#define HMAC_BA_RX_BE_TIMEOUT      60 /* 100 milliseconds */
#define HMAC_BA_RX_BK_TIMEOUT      100 /* 100 milliseconds */

#define HMAC_BA_SEQNO_MASK                  0x0FFF      /* max sequece number */
#define HMAC_BA_SEQNO_SUB(_seq1, _seq2)     (((_seq1) - (_seq2)) & HMAC_BA_SEQNO_MASK)
#define HMAC_BA_SEQNO_ADD(_seq1, _seq2)     (((_seq1) + (_seq2)) & HMAC_BA_SEQNO_MASK)

#define HMAC_BA_LUT_IDX_BMAP_LEN            ((HAL_MAX_BA_LUT_SIZE + 7) >> 3)
#define HMAC_TX_BA_LUT_BMAP_LEN             ((HAL_MAX_AMPDU_LUT_SIZE + 7) >> 3)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 inline��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_ba_rx_seqno_lt
 ��������  : �ж�seq1�Ƿ�С��seq2
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��15��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_ba_rx_seqno_lt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 < us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_MAX_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_rx_seqno_gt
 ��������  : �ж�seq1�Ƿ����seq2
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��15��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_ba_rx_seqno_gt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return hmac_ba_rx_seqno_lt(us_seq2, us_seq1);
}

/*****************************************************************************
 �� �� ��  : dmac_ba_seqno_lt
 ��������  : �ж�seq1�Ƿ�С��seq2
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_ba_seqno_lt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 < us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_MAX_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_seqno_gt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_ba_seqno_gt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return hmac_ba_seqno_lt(us_seq2, us_seq1);
}

/*****************************************************************************
 �� �� ��  : hmac_ba_rx_seqno_leq
 ��������  : �ж�seq1�Ƿ�С�ڻ����seq2
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��15��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_ba_rx_seqno_leq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 <= us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_MAX_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_rx_seqno_geq
 ��������  : �ж�seq1�Ƿ���ڻ����seq2
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��15��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_ba_rx_seqno_geq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return hmac_ba_rx_seqno_leq(us_seq2, us_seq1);
}

/* ����seq num��ba��start��ƫ���� */
#define HMAC_BA_INDEX(_st, _seq) (((_seq) - (_st)) & 4095)

#define HMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE 5 /* log2(32) == 5 */
/* ����BA���ڼ�¼seq number��bitmap��ʹ�õ����ͳ��� */
#define HMAC_TX_BUF_BITMAP_WORD_SIZE        32

#define HMAC_TX_BUF_BITMAP_WORD_MASK (HMAC_TX_BUF_BITMAP_WORD_SIZE - 1)

#define HMAC_TX_BUF_BITMAP_SET(_bitmap, _idx)              \
    (_bitmap[_idx >> HMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] |= \
    (1 << (_idx & HMAC_TX_BUF_BITMAP_WORD_MASK)))

#define HMAC_TX_BUF_BITMAP_CLR(_bitmap, _idx)            \
    (_bitmap[_idx >> HMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] &= \
   ~((oal_uint32)(1 << (_idx & HMAC_TX_BUF_BITMAP_WORD_MASK))))


#define HMAC_BA_BMP_SIZE                    64

/* �ж�indexΪn ��bitmap�е�bitλ�Ƿ���1 */
#define HMAC_BA_ISSET(_bm, _n)        (((_n) < (HMAC_BA_BMP_SIZE)) &&          \
                                     ((_bm)[(_n) >> 5] & (1 << ((_n) & 31))))

/* �ж�һ��seq num�Ƿ��ڷ��ʹ����� */
#define HMAC_BAW_WITHIN(_start, _bawsz, _seqno)      \
        ((((_seqno) - (_start)) & 4095) < (_bawsz))

/*****************************************************************************
 �� �� ��  : hmac_ba_isset
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��4��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_ba_isset(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_uint16 us_seqno)
{
    oal_uint16    us_index;


    if (HMAC_BAW_WITHIN(pst_ba_rx_hdl->us_baw_head, HMAC_BA_BMP_SIZE, us_seqno))
    {
        us_index = us_seqno & (HMAC_BA_BMP_SIZE - 1);

        if (HMAC_BA_ISSET(pst_ba_rx_hdl->aul_rx_buf_bitmap, us_index))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_addto_rx_bitmap
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��11��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_ba_addto_rx_bitmap(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_uint16 us_seqno)
{
    oal_uint16    us_index;

    if (HMAC_BAW_WITHIN(pst_ba_rx_hdl->us_baw_head, HMAC_BA_BMP_SIZE, us_seqno))
    {
        us_index = us_seqno  & (HMAC_BA_BMP_SIZE - 1);
        HMAC_TX_BUF_BITMAP_SET(pst_ba_rx_hdl->aul_rx_buf_bitmap, us_index);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_ba_clear_rx_bitmap
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��11��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_ba_clear_rx_bitmap(hmac_ba_rx_stru *pst_ba_rx_hdl)
{
    oal_uint16    us_index;

    us_index = DMAC_BA_SEQNO_SUB(pst_ba_rx_hdl->us_baw_head, 1) & (HMAC_BA_BMP_SIZE - 1);
    HMAC_TX_BUF_BITMAP_CLR(pst_ba_rx_hdl->aul_rx_buf_bitmap, us_index);
}


/*****************************************************************************
 �� �� ��  : hmac_ba_update_rx_bitmap
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��11��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_ba_update_rx_bitmap(hmac_user_stru *pst_hmac_user, mac_ieee80211_frame_stru *pst_frame_hdr)
{
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;
    oal_uint8               uc_tid;
    hmac_ba_rx_stru        *pst_ba_rx_hdl;

    /* �����ĵ�ַ�����ȡ���ĵ�tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;
    uc_tid        = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    pst_ba_rx_hdl = pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info;
    if (OAL_PTR_NULL == pst_ba_rx_hdl)
    {
        return;
    }
    if (DMAC_BA_COMPLETE != pst_ba_rx_hdl->en_ba_status)
    {
        return;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_lock(&pst_ba_rx_hdl->st_ba_lock);
#endif

    while(hmac_ba_seqno_lt(pst_ba_rx_hdl->us_baw_head, DMAC_BA_SEQNO_SUB(pst_ba_rx_hdl->us_baw_start, (HMAC_BA_BMP_SIZE - 1))))
    {
        pst_ba_rx_hdl->us_baw_head = DMAC_BA_SEQNO_ADD(pst_ba_rx_hdl->us_baw_head, 1);
        hmac_ba_clear_rx_bitmap(pst_ba_rx_hdl);
    }

    hmac_ba_addto_rx_bitmap(pst_ba_rx_hdl, mac_get_seq_num((oal_uint8 *)pst_frame_hdr));

    //OAL_IO_PRINT("hmac_ba_filter_serv::head_seq:%d, bit_map:%x %x.\n", pst_ba_rx_hdl->us_baw_head, pst_ba_rx_hdl->aul_rx_buf_bitmap[0], pst_ba_rx_hdl->aul_rx_buf_bitmap[1]);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_unlock(&pst_ba_rx_hdl->st_ba_lock);
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_ba_seqno_bound_chk
 ��������  :
 This function compares the given sequence number with the specified
 upper and lower bounds and returns its position relative to them.
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
OAL_STATIC OAL_INLINE oal_uint8 hmac_ba_seqno_bound_chk(oal_uint16 us_seq_lo, oal_uint16 us_seq_hi, oal_uint16 us_seq)
{
    oal_bool_enum_uint8 en_lo_chk;
    oal_bool_enum_uint8 en_hi_chk;
    oal_uint8 uc_chk_res = 0;

    en_lo_chk  = hmac_ba_rx_seqno_leq(us_seq_lo, us_seq);
    en_hi_chk  = hmac_ba_rx_seqno_leq(us_seq, us_seq_hi);

    if((OAL_TRUE == en_lo_chk) && (OAL_TRUE == en_hi_chk))
    {
        uc_chk_res = DMAC_BA_BETWEEN_SEQLO_SEQHI;
    }
    else if(OAL_FALSE== en_hi_chk)
    {
        uc_chk_res = DMAC_BA_GREATER_THAN_SEQHI;
    }

    return uc_chk_res;
}

/* This function reads out the TX-Dscr indexed by the specified sequence number in */
/* the Retry-Q Ring-Buffer. */
/*****************************************************************************
 �� �� ��  : hmac_remove_frame_from_reorder_q
 ��������  :This function reads out the TX-Dscr indexed by the specified sequence number in
            the Retry-Q Ring-Buffer.
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
OAL_STATIC OAL_INLINE hmac_rx_buf_stru *hmac_remove_frame_from_reorder_q(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_uint16 us_seq_num)
{
    oal_uint16        us_idx;
    hmac_rx_buf_stru *pst_rx_buff;

    us_idx = (us_seq_num & (WLAN_AMPDU_RX_BUFFER_SIZE - 1));

    pst_rx_buff = &(pst_ba_rx_hdl->ast_re_order_list[us_idx]);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_lock(&pst_ba_rx_hdl->st_ba_lock);

    if((pst_rx_buff->in_use == 0) || (pst_rx_buff->us_seq_num != us_seq_num))
    {
        oal_spin_unlock(&pst_ba_rx_hdl->st_ba_lock);
        return OAL_PTR_NULL;
    }

    pst_rx_buff->in_use = 0;

    oal_spin_unlock(&pst_ba_rx_hdl->st_ba_lock);
#else
    if((pst_rx_buff->in_use == 0) || (pst_rx_buff->us_seq_num != us_seq_num))
    {
        return OAL_PTR_NULL;
    }

    pst_rx_buff->in_use = 0;
#endif

    return pst_rx_buff;
}

/*****************************************************************************
 �� �� ��  : dmac_get_frame_from_reorder_q
 ��������  :This function reads out the TX-Dscr indexed by the specified sequence number in
            the Retry-Q Ring-Buffer.
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
OAL_STATIC OAL_INLINE hmac_rx_buf_stru *hmac_get_frame_from_reorder_q(hmac_ba_rx_stru *pst_ba_rx_hdl, oal_uint16 us_seq_num)
{
    oal_uint16        us_idx;
    hmac_rx_buf_stru *pst_rx_buff;

    us_idx = (us_seq_num & (WLAN_AMPDU_RX_BUFFER_SIZE - 1));

    pst_rx_buff = &(pst_ba_rx_hdl->ast_re_order_list[us_idx]);

    if((pst_rx_buff->in_use == 0) || (pst_rx_buff->us_seq_num != us_seq_num))
    {
        return OAL_PTR_NULL;
    }

    return pst_rx_buff;
}


OAL_STATIC OAL_INLINE oal_uint8 hmac_ba_get_lut_index(oal_uint8 *puc_ba_lut_index_table, oal_uint16 us_start, oal_uint16 us_stop)
{
    return oal_get_lut_index(puc_ba_lut_index_table, HMAC_BA_LUT_IDX_BMAP_LEN, HAL_MAX_BA_LUT_SIZE, us_start, us_stop);
}

OAL_STATIC OAL_INLINE oal_void  hmac_ba_del_lut_index(oal_uint8 *puc_ba_lut_index_table, oal_uint8 uc_lut_index)
{
    oal_del_lut_index(puc_ba_lut_index_table, uc_lut_index);
}

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  hmac_ba_filter_serv(mac_vap_stru *pst_vap,
                                      hmac_user_stru *pst_hmac_user,
                                      hmac_rx_ctl_stru *pst_cb_ctrl,
                                      mac_ieee80211_frame_stru  *pst_frame_hdr,
                                      oal_netbuf_head_stru *pst_netbuf_header,
                                      oal_bool_enum_uint8 *pen_is_ba_buf);


extern oal_uint32  hmac_ba_timeout_fn(oal_void *p_arg);

extern oal_uint8  hmac_mgmt_check_set_rx_ba_ok(
                    hmac_vap_stru              *pst_hmac_vap,
                    hmac_ba_rx_stru            *pst_ba_rx_info,
                    mac_device_stru           *pst_device);

extern oal_void hmac_reorder_ba_rx_buffer_bar(hmac_ba_rx_stru *pst_rx_ba, oal_uint16 us_start_seq_num,  mac_vap_stru *pst_vap);
extern oal_uint32  hmac_ba_reset_rx_handle(mac_device_stru *pst_mac_device, hmac_ba_rx_stru **ppst_rx_ba, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_aging);
extern oal_void  hmac_up_rx_bar(hmac_vap_stru *pst_hmac_vap, dmac_rx_ctl_stru *pst_rx_ctl, oal_netbuf_stru *pst_netbuf);
extern oal_bool_enum_uint8 hmac_is_device_ba_setup(void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_blockack.h */
