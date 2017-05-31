/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_test_sch.c
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2014��2��19��
  ����޸�   :
  ��������   : alg_sch�㷨��֤��dmac����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��2��19��
    ��    ��   : x00189397
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
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#include "dmac_mgmt_ap.h"
#include "dmac_scan.h"
#include "hal_witp_mac.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TEST_SCH_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_test_sch_modify_txdscp_timestamp
 ��������  : ����tx_dscp��timestamp
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��19��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_sch_modify_txdscp_timestamp(oal_uint16 *p_us_tsf, oal_int16 s_adjust_time_ms)
{
    /* �жϿ����Ƿ�� */
    if (0 == g_st_dmac_test_mng.uc_lifetime_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_modify_txdscp_timestamp::uc_lifetime_flag closed}\r\n");
        return;
    }

    OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_test_sch_modify_txdscp_timestamp::delay_ms,tsf_before %d}\r\n", *p_us_tsf);
    *p_us_tsf = (oal_uint16)((oal_int16 )*p_us_tsf + s_adjust_time_ms);

    OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_test_sch_modify_txdscp_timestamp::tsf_after=%d}\r\n", *p_us_tsf);
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_test_sch_stat_tx_mpdu_num
 ��������  : ���·���mdpu�����ͷ��ͳɹ���mpdu����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��19��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_sch_stat_tx_mpdu_num(dmac_user_stru *pst_dmac_user,
                                        oal_uint8 uc_tidno,
                                        hal_tx_dscr_ctrl_one_param st_tx_dscr_param,
                                        mac_tx_ctl_stru *pst_cb)
{
    if ((OAL_PTR_NULL == pst_dmac_user) || (OAL_PTR_NULL == pst_cb))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_stat_tx_mpdu_num::invalid input params}\r\n");
        return;
    }

    /* ֻͳ������֡ */
    if (WLAN_DATA_BASICTYPE != pst_cb->en_frame_type)
    {
        return;
    }

    /* �жϿ����Ƿ�� */
    if (0 == g_st_dmac_test_mng.uc_lifetime_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_stat_tx_mpdu_num::uc_lifetime_flag closed}\r\n");
        return;
    }

    g_st_dmac_test_mng.ul_tx_mpdu_num += st_tx_dscr_param.uc_mpdu_num;
    g_st_dmac_test_mng.ul_tx_succ_mpdu_num +=
            st_tx_dscr_param.uc_mpdu_num - st_tx_dscr_param.uc_error_mpdu_num;

    OAM_INFO_LOG2(0, OAM_SF_ANY, "{dmac_test_sch_stat_tx_mpdu_num::tx_mpdu_num=%d,tx_succ_mpdu_num=%d}\r\n",
                                    g_st_dmac_test_mng.ul_tx_mpdu_num,
                                    g_st_dmac_test_mng.ul_tx_succ_mpdu_num);
}

/*****************************************************************************
 �� �� ��  : dmac_test_sch_stat_rx_mpdu_num
 ��������  : ���½��յ�mpdu����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��19��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_sch_stat_rx_mpdu_num(frw_event_hdr_stru *pst_event_hdr,
                                        mac_vap_stru *pst_vap,
                                        dmac_rx_ctl_stru *pst_rx_ctl)
{
    if ((OAL_PTR_NULL == pst_event_hdr) || (OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_rx_ctl))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_mpdu_num::invalid input params}\r\n");
        return;
    }

    /* ����֡����Ҫͳ�� */
    if (FRW_EVENT_TYPE_WLAN_DRX != pst_event_hdr->en_type)
    {
        return;
    }

    /* �жϿ����Ƿ�� */
    if (0 == g_st_dmac_test_mng.uc_lifetime_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_mpdu_num::uc_lifetime_flag closed}\r\n");
        return;
    }

    g_st_dmac_test_mng.ul_rx_mpdu_num++;

    OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_mpdu_num::rx_mpdu_num=%d}\r\n", g_st_dmac_test_mng.ul_rx_mpdu_num);
}

/*****************************************************************************
 �� �� ��  : dmac_test_sch_set_long_nav_enable
 ��������  : ���÷���������long nav�Ƿ�ʹ��
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��27��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_sch_set_long_nav_enable(hal_tx_dscr_stru *pst_tx_dscr)
{
    hi1151_tx_ctrl_dscr_one_stru          *pst_tx_dscr_one;
    hi1151_tx_ctrl_dscr_two_stru          *pst_tx_dscr_two;

    if (OAL_PTR_NULL == pst_tx_dscr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_set_long_nav_enable::invalid inputs}\r\n");
        return;
    }

	/* �жϿ����Ƿ�� */
    if (0 == g_st_dmac_test_mng.uc_long_nav_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_set_long_nav_enable::uc_long_nav_flag closed}\r\n");
        return;
    }

    pst_tx_dscr_one     = (hi1151_tx_ctrl_dscr_one_stru *)pst_tx_dscr->data;
    pst_tx_dscr_two     = (hi1151_tx_ctrl_dscr_two_stru *)((oal_uint8 *)pst_tx_dscr_one + OAL_SIZEOF(hi1151_tx_ctrl_dscr_one_stru));


    pst_tx_dscr_two->st_phy_mode_two.bit_long_nav_enable
                = g_st_dmac_test_mng.uc_long_nav_is_enabled;

    OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_test_sch_set_long_nav_enable::bit_long_nav_enable=%d}\r\n",
                                    g_st_dmac_test_mng.uc_long_nav_is_enabled);

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_test_sch_stat_rx_sta_num
 ��������  : ���½��յĹ㲥���ĵ�mpdu����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_sch_stat_rx_sta_num(frw_event_hdr_stru *pst_event_hdr,
                                            mac_vap_stru *pst_vap,
                                            dmac_rx_ctl_stru *pst_rx_ctl)
{
    mac_ieee80211_frame_stru    *pst_frame_hdr;
    oal_uint8                    auc_sta_addr[6] = {0x28, 0x6E, 0xD4, 0x18, 0x93, 0x98};
    oal_uint8                    auc_ap_addr[6] = {0x28, 0x6E, 0xD4, 0x18, 0x93, 0x97};
    oal_uint8                   *puc_tx_addr;
    oal_uint8                   *puc_rx_addr;

    if ((OAL_PTR_NULL == pst_event_hdr) || (OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_rx_ctl))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_sta_num::invalid input params}\r\n");
        return;
    }

    /* ����֡����Ҫͳ�� */
    if (FRW_EVENT_TYPE_WLAN_DRX != pst_event_hdr->en_type)
    {
        return;
    }

    /* �жϿ����Ƿ�� */
    if (0 == g_st_dmac_test_mng.uc_cca_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_sta_num::uc_cca_flag closed}\r\n");
        return;
    }

    /* ��ȡ802.11ͷָ�롢���Ͷ˵�ַ */
    pst_frame_hdr       = (mac_ieee80211_frame_stru *)(pst_rx_ctl->st_rx_info.pul_mac_hdr_start_addr);
    puc_rx_addr         = pst_frame_hdr->auc_address1;
    puc_tx_addr         = pst_frame_hdr->auc_address2;

    /* ������յ�ַAP���ҷ��͵�ַΪ��Ӧ��STA */
    if (0 == (oal_compare_mac_addr(auc_ap_addr, puc_rx_addr))
            && 0 == (oal_compare_mac_addr(auc_sta_addr, puc_tx_addr)))
    {
        g_st_dmac_test_mng.ul_cca_rx_sta_num++;
        OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_sta_num::ul_cca_rx_sta_num=%d}\r\n",
                                        g_st_dmac_test_mng.ul_cca_rx_sta_num);
    }

    /* ������յ�ַΪSTA���ҷ��͵�ַΪ��Ӧ��AP */
    if (0 == (oal_compare_mac_addr(auc_sta_addr, puc_rx_addr))
            && 0 == (oal_compare_mac_addr(auc_ap_addr, puc_tx_addr)))
    {
        g_st_dmac_test_mng.ul_cca_rx_ap_num++;
        OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_test_sch_stat_rx_sta_num::ul_cca_rx_ap_num=%d}\r\n",
                                        g_st_dmac_test_mng.ul_cca_rx_ap_num);
    }

    return;
}

#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

