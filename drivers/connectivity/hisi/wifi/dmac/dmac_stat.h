/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_stat.h
  �� �� ��   : ����
  ��    ��   : x00189397
  ��������   : 2014��1��10��
  ����޸�   :
  ��������   : dmac_stat.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��10��
    ��    ��   : x00189397
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_STAT_H__
#define __DMAC_STAT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_PERFORM_STAT

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_ext_if.h"
#include "hal_ext_if.h"
#include "frw_ext_if.h"
#include "dmac_user.h"
#include "dmac_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STAT_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define	DMAC_STAT_ITEM_LIMIT                    100     /* ʱ�ӣ���������per���ͳ�������� */

#define	DMAC_STAT_TID_DELAY_NODE_LIMIT          128		/* tidʱ��ͳ�����ڵ����� */
#define DMAC_STAT_TID_PER_NODE_LIMIT            128     /* tid perͳ�����ڵ��� */
#define	DMAC_STAT_TID_THRPT_NODE_LIMIT          128		/* tid������ͳ�����ڵ����� */
#define	DMAC_STAT_USER_THRPT_NODE_LIMIT         32		/* user������ͳ�����ڵ����� */
#define DMAC_STAT_VAP_THRPT_NODE_LIMIT          8		/* vap������ͳ�����ڵ����� */
#define DMAC_STAT_TIMER_CYCLE_MS                100     /* Ĭ��ͳ������ */

#define DMAC_STAT_TIME_USEC_INT64(_pst_time) \
    ((oal_int64)((_pst_time)->i_sec) * 1000000 + (_pst_time)->i_usec)

#define DMAC_STAT_TIME_USEC_DIFF(_pst_time1, _pst_time2)    \
    (DMAC_STAT_TIME_USEC_INT64(_pst_time2)- DMAC_STAT_TIME_USEC_INT64(_pst_time1))


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
/* stat_node�ṹ�� */
typedef struct
{
    oal_dlist_head_stru	        st_entry;                               /* ˫������entry */
    frw_timeout_stru            st_timer;		                        /* ��ʱ�� */

    oal_bool_enum_uint8         uc_stat_flag;                           /* ͳ���Ƿ�ʹ�� */
    oal_uint8                   uc_resv[3];                             /* �ֽڶ��� */

    dmac_stat_param_stru       *pst_stat_param;                          /* ͳ�Ʋ��� */
    oal_uint32                  us_total_item;                          /* ��¼������ */
    oal_uint32                  us_curr_item;                           /* ��ǰ�ڼ��� */
    oal_uint32                  aul_stat_cnt[DMAC_STAT_PER_BUTT];            /* ĳ��ͳ�����ڴ��� */
    oal_uint32                  aul_stat_sum[DMAC_STAT_PER_BUTT];            /* ĳ��������ͳ�������ۼ�ֵ */
    dmac_stat_timeout_func      p_inner_func;                           /* �ڲ�ͳ��ģ��ĺ���ָ�� */

    oal_uint32                 *pul_stat_avg;                           /* ��CFGģ��õ���ͳ��ƽ��ֵ����׵�ַ */
}dmac_stat_node_stru;

typedef struct
{
	oal_uint32			 ul_node_num;           /* ͳ�ƽڵ����� */
	oal_dlist_head_stru	 st_stat_node_dlist;    /* ͳ�ƽڵ�˫������ͷ�ڵ� */
}dmac_stat_stru;

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  dmac_stat_init(oal_void);
extern oal_uint32  dmac_stat_exit(oal_void);
extern oal_uint32  dmac_stat_tid_delay(dmac_tid_stru *pst_dmac_tid);
extern oal_uint32  dmac_stat_tx_thrpt(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tidno, hal_tx_dscr_ctrl_one_param st_tx_dscr_param);
extern oal_uint32  dmac_stat_rx_thrpt(frw_event_hdr_stru *pst_event_hdr, mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl);
extern oal_uint32  dmac_stat_display(oam_module_id_enum_uint16       en_module_id,
                                      mac_stat_type_enum_uint8       en_stat_type,
                                      oal_void                      *p_void);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_stat.h */


