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
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "dmac_user.h"
#include "dmac_main.h"
#include "dmac_tx_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BLOCKACK_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* �ж�һ��seq num�Ƿ��ڷ��ʹ����� */
#define DMAC_BAW_WITHIN(_start, _bawsz, _seqno)      \
        ((((_seqno) - (_start)) & 4095) < (_bawsz))

/* ����seq num��ba��start��ƫ���� */
#define DMAC_BA_INDEX(_st, _seq) (((_seq) - (_st)) & 4095)

#define DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE 5 /* log2(32) == 5 */
#define DMAC_TX_BUF_BITMAP_WORD_MASK (DMAC_TX_BUF_BITMAP_WORD_SIZE - 1)

/* TX_BUF_BITMAP_SET, TX_BUF_BITMAP_CLR -
 * Find the word by dividing the index by the number of bits per word.
 * Find the bit within the word by masking out all but the LSBs of the index.
 * Set or clear the relevant bit within the relevant word.
 */
#define DMAC_TX_BUF_BITMAP_SET(_bitmap, _idx)              \
    (_bitmap[_idx >> DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] |= \
    (1 << (_idx & DMAC_TX_BUF_BITMAP_WORD_MASK)))

#define DMAC_TX_BUF_BITMAP_CLR(_bitmap, _idx)              \
    (_bitmap[_idx >> DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] &= \
    ~((oal_uint32)(1 << (_idx & DMAC_TX_BUF_BITMAP_WORD_MASK))))

#define DMAC_TX_BUF_BITMAP_IS_SET(_bitmap, _idx) \
    ((_bitmap[_idx >> DMAC_TX_BUF_BITMAP_LOG2_WORD_SIZE] & \
    (1 << (_idx & DMAC_TX_BUF_BITMAP_WORD_MASK))) != 0)

/* �ж�indexΪn ��bitmap�е�bitλ�Ƿ���1 */
#define DMAC_BA_ISSET(_bm, _n)        (((_n) < (DMAC_BA_BMP_SIZE)) &&          \
                                     ((_bm)[(_n) >> 5] & (1 << ((_n) & 31))))

#define DMAC_BA_MAX_SW_RETRIES  3

/* Default values for receive timeout */
#define DMAC_BA_RX_VO_TIMEOUT      40  /* 40 milliseconds */
#define DMAC_BA_RX_VI_TIMEOUT      100 /* 100 milliseconds */
#define DMAC_BA_RX_BE_TIMEOUT      100 /* 100 milliseconds */
#define DMAC_BA_RX_BK_TIMEOUT      100 /* 100 milliseconds */

#define DMAC_DUMP_BA_BITMAP_PATH "/tmp/dump_ba_bitmap.txt"

#define WLAN_AMPDU_TX_MAX_NUM_DEBUG 32

#define WLAN_RX_RESET_BA_THREHOLD 32 /* BA�Ựδ�����յ�һ���ۺ�֡����DELBA */

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
typedef struct
{
    oal_uint32              ul_bitmap_low;
    oal_uint32              ul_bitmap_high;
    oal_uint8               auc_bitmap[DMAC_BA_BMP_SIZE >> 3];
    oal_uint8               uc_tid;
    oal_uint8               auc_resv[3];

    oal_uint16              us_ba_ssn;
    oal_uint16              us_ba_sw_barlsn;

    dmac_ba_tx_stru        *pst_tx_ba;
}dmac_ba_tx_status_stru;

typedef struct
{
    /*����*/
    oal_bool_enum_uint8 en_is_before_tx_track;

    /*tid���������Ϣ*/
    oal_uint8       uc_tid;                    /*tid*/
    oal_uint16      us_tid_total_mpdu_num;     /*tid�������ܵ�mpdu��Ŀ*/
    oal_uint8       uc_tid_retry_mpdu_num;     /*tid�����д��ڶ��ٸ��ش�mpdu*/
    oal_uint8       uc_tid_record_mpdu_num;    /*aus_tid_seqnum�м�¼��tid�����ж��ٸ�mpdu��seqnum*/
    oal_uint16      aus_tid_seqnum[WLAN_AMPDU_TX_MAX_NUM_DEBUG];        /*����tid�����е�seqnum*/

    /*ba handle�������Ϣ*/
    oal_uint32      aul_bitmap[4];             /*ba handle�е�bitmap*/
    oal_uint16      us_seq_start;
    oal_uint16      us_lsn;
    oal_uint16      us_baw_head;
    oal_uint16      us_baw_tail;

    union
    {
        struct
        {
            /*���ȳ�������������Ϣ*/
            oal_uint16      aus_schedule_seqnum[WLAN_AMPDU_TX_MAX_NUM_DEBUG];
            oal_uint8       uc_schedule_mpdu_num;
            oal_uint8       auc_resv0[3];
        } st_schedule;
        struct
        {
            /*��������ϱ�������������Ϣ*/
            oal_uint16      aus_report_seqnum[WLAN_AMPDU_TX_MAX_NUM_DEBUG];     /*���������������seqnum*/
            oal_uint8       uc_report_mpdu_num;        /*������ɵ�mpdu��Ŀ*/
            oal_uint8       uc_tx_status;              /*�������������״̬*/
            oal_uint8       auc_resv1[2];
        } st_report;

    } un_mix_dscr;

}dmac_seq_track_stru;

typedef struct
{
    dmac_seq_track_stru             ast_seq_bitmap_log[OAM_SEQ_TRACK_NUM];
    oal_uint16                      us_track_head;
    oal_uint16                      us_track_tail;
    oal_bool_enum_uint8             en_track_off;
    oal_uint8                       uc_tid;
    oal_uint8                       uc_track_remain;
    oal_uint8                       auc_reserve[1];
}dmac_tx_ba_track_stru;
#ifdef _PRE_WLAN_FEATURE_AMPDU
//#if (_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)
//extern dmac_tx_ba_track_stru g_ast_tx_ba_track[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][HAL_MAX_AMPDU_LUT_SIZE];
//#endif
#endif

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
 �� �� ��  : dmac_ba_rx_seqno_lt
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_lt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 < us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO)))
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_gt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_rx_seqno_lt(us_seq2, us_seq1);
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_seqno_lt(oal_uint16 us_seq1, oal_uint16 us_seq2)
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_seqno_gt(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_seqno_lt(us_seq2, us_seq1);
}

/*****************************************************************************
 �� �� ��  : dmac_ba_rx_seqno_leq
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_leq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 <= us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_rx_seqno_geq
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_rx_seqno_geq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_rx_seqno_leq(us_seq2, us_seq1);
}

/*****************************************************************************
 �� �� ��  : dmac_ba_seqno_leq
 ��������  : �ж�seq1�Ƿ�С�ڻ����seq2
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_seqno_leq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    if(((us_seq1 <= us_seq2) && ((us_seq2 - us_seq1) < DMAC_BA_MAX_SEQNO_BY_TWO)) ||
       ((us_seq1 > us_seq2) && ((us_seq1 - us_seq2) > DMAC_BA_MAX_SEQNO_BY_TWO)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_seqno_geq
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_seqno_geq(oal_uint16 us_seq1, oal_uint16 us_seq2)
{
    return dmac_ba_seqno_leq(us_seq2, us_seq1);
}


/*****************************************************************************
 �� �� ��  : dmac_ba_seqnum_out_window
 ��������  : ȷ��seqnum�Ƿ���ba������
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_ba_seqnum_out_window(dmac_ba_tx_stru *pst_ba_hdl, oal_uint16 us_seq_num)
{
    return (oal_bool_enum_uint8)(dmac_ba_seqno_gt(us_seq_num, pst_ba_hdl->us_last_seq_num) || dmac_ba_seqno_gt(pst_ba_hdl->us_baw_start, us_seq_num));
}

/*****************************************************************************
 �� �� ��  : dmac_ba_seqno_bound_chk
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
OAL_STATIC OAL_INLINE oal_uint8 dmac_ba_seqno_bound_chk(oal_uint16 us_seq_lo, oal_uint16 us_seq_hi, oal_uint16 us_seq)
{
    oal_bool_enum_uint8 en_lo_chk;
    oal_bool_enum_uint8 en_hi_chk;
    oal_uint8 uc_chk_res = 0;

    en_lo_chk  = dmac_ba_rx_seqno_leq(us_seq_lo, us_seq);
    en_hi_chk  = dmac_ba_rx_seqno_leq(us_seq, us_seq_hi);

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

/*****************************************************************************
 �� �� ��  : dmac_ba_get_lut_index
 ��������  : ��BA LUT index bitmap table�л�ȡһ��BA lut index�����BA LUT index
             bitmap table�Ѿ����ˣ��򷵻�һ�������õ�index
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_ba_get_lut_index(oal_uint8 *puc_ba_lut_index_table, oal_uint16 us_start, oal_uint16 us_stop)
{
    return oal_get_lut_index(puc_ba_lut_index_table, DMAC_BA_LUT_IDX_BMAP_LEN, HAL_MAX_BA_LUT_SIZE, us_start, us_stop);
}

/*****************************************************************************
 �� �� ��  : dmac_ba_del_lut_index
 ��������  : ��BA LUT index bitmap table��ɾ��һ��BA lut index
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_ba_del_lut_index(oal_uint8 *puc_ba_lut_index_table, oal_uint8 uc_lut_index)
{
    oal_del_lut_index(puc_ba_lut_index_table, uc_lut_index);
}

/*****************************************************************************
 �� �� ��  : dmac_update_txba_session_params_ap
 ��������  : ��AMPDU��ȷ�ϲ���ΪNORMAL ACKʱ����Ҫ����AMPDU�Ĳ�������BA�Ĳ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_update_txba_session_params_ap(
                dmac_tid_stru          *pst_dmac_tid,
                oal_uint8               uc_ampdu_max_num)
{
    if(OAL_PTR_NULL != pst_dmac_tid->pst_ba_tx_hdl)
    {
        /*  ampdu�����ľۺϸ������ܳ���BA���Ĵ�С */
        pst_dmac_tid->pst_ba_tx_hdl->us_baw_size = OAL_MIN(pst_dmac_tid->pst_ba_tx_hdl->us_baw_size, uc_ampdu_max_num);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_ba_update_start_seq_num
 ��������  : This function updates the start sequence number for the block-ack session
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_ba_update_start_seq_num(dmac_ba_tx_stru *pst_tx_ba, oal_uint16 us_seq_num)
{
    pst_tx_ba->us_baw_start = us_seq_num;
    pst_tx_ba->us_last_seq_num = DMAC_BA_SEQ_SUB(us_seq_num, 1);
    pst_tx_ba->us_baw_head = 0;
    pst_tx_ba->us_baw_tail = 0;
}


/*****************************************************************************
 �� �� ��  : dmac_ba_is_tx_data_useful
 ��������  : This function checks whether the Transmitted Data frame is useful enough
             to be buffered.
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_is_tx_data_useful(dmac_ba_tx_stru *pst_tx_ba, oal_uint16 us_seq_num)
{
   return dmac_ba_seqno_geq(us_seq_num, pst_tx_ba->us_baw_start);
}

/*****************************************************************************
 �� �� ��  : dmac_reset_tx_ampdu_session
 ��������  : ɾ��AMPDU�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_reset_tx_ampdu_session(
                hal_to_dmac_device_stru    *pst_hal_device,
                dmac_user_stru             *pst_dmac_user,
                oal_uint8                   uc_tid)
{
    dmac_tid_stru      *pst_tid_queue;

    pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

    /* ������AMPDU��ص�HT��Ϣ */
    pst_tid_queue->st_ht_tx_hdl.uc_ampdu_max_num  = 0;
    pst_tid_queue->en_tx_mode = DMAC_TX_MODE_NORMAL;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_tx_ba_state_prot
 ��������  : ɾ��HT��صĲ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_reset_tx_ba_state_prot(
                hal_to_dmac_device_stru    *pst_hal_device,
                dmac_user_stru             *pst_dmac_user,
                oal_uint8                   uc_tid)

{
    dmac_reset_tx_ampdu_session(pst_hal_device, pst_dmac_user, uc_tid);
}


/*****************************************************************************
 �� �� ��  : dmac_ba_addto_baw
 ��������  : һ����mpdu����ampdu ���¼�¼seq num�Ĵ���
 �������  : ��
 �������  : return TRUE��ʾ���ش��� ����Ҫ�ټ��봰��bitmap, FALSE��ʾ�����ش���������baw bitmap
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��7��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 dmac_ba_addto_baw(dmac_ba_tx_stru *pst_tx_ba_handle)
{
    oal_uint16    us_index;
    oal_uint16    us_cindex;
#if 0
    /* �ش�������Ҫ�ƴ����� */
    if (pst_tx_dscr->bit_is_retried)
    {
        return OAL_TRUE;
    }
#endif
    /*���������MPDU���к�*/
    pst_tx_ba_handle->us_last_seq_num = DMAC_BA_SEQ_ADD(pst_tx_ba_handle->us_last_seq_num, 1);

    /*��ȡ�����MPDU�͵�һ��δȷ��MPDU֮������кŲ�ֵ*/
    us_index = DMAC_BA_INDEX(pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_last_seq_num);

    /*��ȡbitmap�У������MPDU��Ӧλ��*/
    us_cindex = (pst_tx_ba_handle->us_baw_head + us_index) & (DMAC_TID_MAX_BUFS - 1);

    /*��λbitmap�ж�Ӧbit*/
    DMAC_TX_BUF_BITMAP_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, us_cindex);

    if (us_index >= ((pst_tx_ba_handle->us_baw_tail - pst_tx_ba_handle->us_baw_head) & (DMAC_TID_MAX_BUFS - 1)))
    {
        pst_tx_ba_handle->us_baw_tail = us_cindex;
        OAL_INCR(pst_tx_ba_handle->us_baw_tail, DMAC_TID_MAX_BUFS);
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_update_baw
 ��������  : ����ba��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��9��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_ba_update_baw(dmac_ba_tx_stru *pst_tx_ba_handle, oal_uint16 us_seqno)
{
    oal_uint16  us_index;
    oal_uint16  us_cindex;
    oal_uint32  ul_cindex;

    us_index  = DMAC_BA_INDEX(pst_tx_ba_handle->us_baw_start, us_seqno);
    us_cindex = (pst_tx_ba_handle->us_baw_head + us_index) & (DMAC_TID_MAX_BUFS - 1);
    ul_cindex = (oal_uint32)us_cindex;

    DMAC_TX_BUF_BITMAP_CLR(pst_tx_ba_handle->aul_tx_buf_bitmap, ul_cindex);

    while (pst_tx_ba_handle->us_baw_head != pst_tx_ba_handle->us_baw_tail &&
           !DMAC_TX_BUF_BITMAP_IS_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, pst_tx_ba_handle->us_baw_head))
    {
        pst_tx_ba_handle->us_baw_start = DMAC_BA_SEQNO_ADD(pst_tx_ba_handle->us_baw_start, 1);
        OAL_INCR(pst_tx_ba_handle->us_baw_head, DMAC_TID_MAX_BUFS);
    }
}

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  dmac_ba_filter_serv(mac_vap_stru *pst_vap,
                                      dmac_user_stru *pst_dmac_user,
                                      dmac_rx_ctl_stru *pst_cb_ctrl,
                                      mac_ieee80211_frame_stru  *pst_frame_hdr);

extern oal_void  dmac_ba_reset_rx_handle(mac_device_stru *pst_device, dmac_ba_rx_stru **ppst_rx_ba, oal_uint8 uc_tid, dmac_user_stru *pst_dmac_user);
extern oal_void  dmac_ba_reset_tx_handle(mac_device_stru *pst_device, dmac_ba_tx_stru **ppst_tx_ba, oal_uint8 uc_tid);

extern oal_uint32  dmac_ba_timeout_fn(oal_void *p_arg);
extern oal_uint32  dmac_ba_send_bar(dmac_ba_tx_stru *pst_tx_ba_handle, dmac_user_stru *pst_dmac_user, dmac_tid_stru *pst_tid_queue);
extern oal_uint16  dmac_ba_calculate_min_mpdu_len(dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg);
extern oal_void dmac_ba_addto_baw_multi(dmac_ba_tx_stru *pst_tx_ba_handle, oal_uint8 uc_new_mpdu_num);
extern oal_uint32  dmac_ba_send_bar(dmac_ba_tx_stru *pst_tx_ba_handle, dmac_user_stru *pst_dmac_user, dmac_tid_stru *pst_tid_queue);
extern oal_void  dmac_move_ba_window_ahead(dmac_ba_tx_stru *pst_ba_hdl, oal_uint16 us_lsn);

extern oal_void  dmac_ba_track_tail_update(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx);
extern oal_void  dmac_ba_track_ba_hander(oal_uint8 uc_device_id, dmac_ba_tx_stru *pst_tx_ba, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_before_tx);
extern oal_void  dmac_ba_track_tid_queue(oal_uint8 uc_device_id, hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_lut_idx, dmac_tid_stru *pst_tid_queue);
extern oal_void  dmac_ba_track_report_seqnum(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx, oal_uint8 uc_dscr_idx, oal_uint16 us_seq_num);
extern oal_void  dmac_ba_track_schedule_seqnum(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx, oal_dlist_head_stru *pst_sch_dscr_head);
extern oal_void  dmac_ba_track_stop(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx);
extern oal_void dmac_nontxop_txba_num_updata(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_addba);
extern oal_bool_enum dmac_is_ba_setup(oal_void);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_blockack.h */
