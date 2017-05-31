/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_acs_test.h
  �� �� ��   : ����
  ��    ��   : ��ɽ��
  ��������   : 2014��4��21��
  ����޸�   :
  ��������   : dmac_acs_test.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��21��
    ��    ��   : w00196298
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_ACS_TEST_H__
#define __DMAC_ACS_TEST_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ACS_TEST_H

#if  defined(_PRE_WLAN_CHIP_TEST)  && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define ACS_CREATE_PROC_ENTRY           create_proc_entry
#define ACS_REMOVE_PROC_ENTRY           remove_proc_entry
#define ACS_VERIFY_PROC_NAME            "acs_meas_result"

#define ACS_SUMMARY_TEST_MODE           0
#define ACS_STATS_TEST_MODE             1
#define ACS_TX_TIME_TEST_MODE           2
#define ACS_READ_REG_MODE               3

#define ACS_SHOW_HW_INFO(title, member)                 \
        do{                                             \
        seq_printf(f, title);                           \
        for (ul_idx = 0; ul_idx < ul_cycles; ul_idx++)  \
        {                                               \
            if (ul_idx && ((ul_idx % 16) == 0))                \
            {                                                   \
                seq_printf(f, "\n");                            \
            }                                                   \
            seq_printf(f, "%-6d", pst_hw_vi->member[ul_idx]);   \
        }                                                     \
        seq_printf(f, "\n");                                  \
        }while(0)

#define ACS_HW_INFO_CLEAR(buffer)       \
                do{                                 \
                    if (OAL_PTR_NULL != buffer)     \
                    {\
                        OAL_MEM_FREE(buffer, OAL_TRUE);\
                        buffer = OAL_PTR_NULL;          \
                    }\
                }while(0)

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
    /* �ŵ�ͳ�� */
    oal_uint32  ul_pri20_free_time_us;
    oal_uint32  ul_pri40_free_time_us;
    oal_uint32  ul_pri80_free_time_us;
    oal_uint32  ul_ch_rx_time_us;
    oal_uint32  ul_ch_tx_time_us;

    /* �ŵ����� */
    oal_int32   l_pri20_idle_power;
    oal_int32   l_pri40_idle_power;
    oal_int32   l_pri80_idle_power;

    /* ͳ�Ƽ��� */
    oal_uint32 aul_stats_cnt[3];
    oal_uint32 aul_meas_cnt[3];
    oal_uint32 ul_test_cnt;
}acs_hw_statics_stru;

typedef struct
{
    acs_hw_statics_stru             st_acs_stats_result;
    oal_int32                      *pul_20m_freetime;
    oal_int32                      *pul_40m_freetime;
    oal_int32                      *pul_80m_freetime;
    oal_int32                      *pul_20m_freepwr;
    oal_int32                      *pul_40m_freepwr;
    oal_int32                      *pul_80m_freepwr;
    oal_uint32                      ul_curr_idx;
    oal_uint32                      ul_cycles;
    oal_uint32                      ul_cycles_backup;
    oal_uint32                      ul_test_running;
    oal_uint32                      ul_test_mode;
    oal_uint32                      ul_reg_data;
}acs_hw_verify_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void  dmac_acs_verify_init(oal_void);
extern oal_void  dmac_acs_verify_exit(oal_void);
extern oal_void  dmac_acs_channel_meas_comp_handler(mac_device_stru *pst_mac_dev, hal_ch_statics_irq_event_stru *pst_mac_stats_result);

#endif /* _PRE_WLAN_CHIP_TEST */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __DMAC_ACS_TEST_H__ */
