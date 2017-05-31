/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_mgmt_sta.c
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2013��6��7��
  ����޸�   :
  ��������   : sta�����֡����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��7��
    ��    ��   : zhangheng
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
#include "mac_ie.h"
#include "dmac_mgmt_sta.h"
#include "dmac_main.h"
#include "oal_net.h"
#include "dmac_chan_mgmt.h"
#include "dmac_device.h"
#include "dmac_resource.h"
#include "dmac_alg_if.h"
#include "dmac_mgmt_sta.h"
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#endif
#include "dmac_scan.h"
#include "dmac_config.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_tx_complete.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_STA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_mgmt_wmm_update_edca_machw_sta
 ��������  : STAģʽ��VAP����EDCA�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��29��
    ��    ��   : s00304087
    �޸�����   : 02����ͬ��hmac mib����
*****************************************************************************/
oal_uint32 dmac_mgmt_wmm_update_edca_machw_sta(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_sta_asoc_set_edca_reg_stru *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_vap_stru                       *pst_dmac_sta;
    wlan_wme_ac_type_enum_uint8          en_ac_type;
    dmac_device_stru                    *pst_dmac_device;
#ifdef _PRE_WLAN_FEATURE_WMMAC
    mac_user_stru                       *pst_mac_user;
    oal_uint8                            uc_wmm_ac_loop;
#endif

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_sta_asoc_set_edca_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_device[idx=%d] null.}", pst_event_hdr->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_sta = mac_res_get_dmac_vap(pst_reg_params->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_sta)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_dmac_vap[idx=%d] null.}", pst_reg_params->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_WMM_SET_PARAM_TYPE_DEFAULT == pst_reg_params->en_set_param_type)
    {
        pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_FALSE;

        /* DTS2016090905626 Del Code ��VAP����ʱSTA��֧��WMM���ر�Ӳ��EDCA���ܣ�GO����֧��WMM��δ����Ӳ��EDCA���ܣ�
           ����Ӳ��������VO�������ݣ������������ݲ����ͣ��ڴ�ľ� */
   #if 0
        /*ȥʹ��EDCA*/
        hal_disable_machw_edca(pst_device->pst_device_stru);

        pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_FALSE;

        /* ����VOĬ�ϲ��� */
        hal_vap_set_machw_aifsn_ac(pst_dmac_sta->pst_hal_vap, WLAN_WME_AC_VO, DMAC_WMM_VO_DEFAULT_DECA_AIFSN);

        hal_vap_set_edca_machw_cw(pst_dmac_sta->pst_hal_vap,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin,
                                  WLAN_WME_AC_VO);
        hal_vap_set_machw_prng_seed_val_all_ac(pst_dmac_sta->pst_hal_vap);
   #endif

        return OAL_SUCC;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy((oal_uint8*)&pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac, (oal_uint8*)&pst_reg_params->ast_wlan_mib_qap_edac, (OAL_SIZEOF(wlan_mib_Dot11QAPEDCAEntry_stru) * WLAN_WME_AC_BUTT));
#endif

#ifdef _PRE_WLAN_FEATURE_WMMAC
    pst_mac_user = mac_res_get_mac_user(pst_dmac_sta->st_vap_base_info.uc_assoc_vap_id);
    if (OAL_PTR_NULL != pst_mac_user)
    {
        /* User��Ϊ���ǣ����ÿһ��AC������EDCA��������ʼ��TS״̬ */
        for (uc_wmm_ac_loop = 0; uc_wmm_ac_loop < WLAN_WME_AC_BUTT; uc_wmm_ac_loop++)
        {
            pst_mac_user->st_ts_info[uc_wmm_ac_loop].en_ts_status =
                (1 == pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_wmm_ac_loop].en_dot11QAPEDCATableMandatory) ?
                 MAC_TS_INIT : MAC_TS_NONE;
        }
    }
#endif //_PRE_WLAN_FEATURE_WMMAC

    hal_enable_machw_edca(pst_dmac_sta->pst_hal_device);
    pst_dmac_device = dmac_res_get_mac_dev(pst_device->uc_device_id);
    if(OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_dmac_device[idx=%d] null.}", pst_event_hdr->uc_device_id);
        return OAL_SUCC;
    }
    /* alg edca opt ��Чʱ, ������BEACON�в��� */
    if(DMAC_ALG_CCA_OPT_NO_INTF != pst_dmac_device->st_dmac_alg_stat.en_cca_intf_state ||
       OAL_TRUE == pst_dmac_device->st_dmac_alg_stat.en_co_intf_state)
    {
        return OAL_SUCC;
    }
    /* ����edca�Ĵ������� */
    hal_vap_set_machw_aifsn_all_ac(pst_dmac_sta->pst_hal_vap,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN);

    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_dmac_sta->pst_hal_vap,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmin,
                                  en_ac_type);
    }

    /* TXOP��ʹ��ʱ,ͬ��AP����;����ʹ������ֵ */
    if(OAL_FALSE == pst_device->en_txop_enable)
    {
        hal_vap_set_machw_txop_limit_bkbe(pst_dmac_sta->pst_hal_vap,
                                          (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                          (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    }

    hal_vap_set_machw_txop_limit_vivo(pst_dmac_sta->pst_hal_vap,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);

    /*DTS: 1102 beacon֡��EDCA������û��LIFETIMEֵ��STA���ݱ���mibֵ����(mibֵΪ0),
    ע�͵�������ã����ռĴ�����������Ч���� */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    hal_vap_set_machw_edca_bkbe_lifetime(pst_dmac_sta->pst_hal_vap,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableMSDULifetime,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableMSDULifetime);
    hal_vap_set_machw_edca_vivo_lifetime(pst_dmac_sta->pst_hal_vap,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableMSDULifetime,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableMSDULifetime);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_chan_adjust_bandwidth_sta
 ��������  : ����AP��(STA)���������������׼��Ҫ�л����Ĵ���ģʽ
 �������  : pst_mac_vap  : MAC VAP�ṹ��ָ�룬ָ��STA
 �������  : pen_bandwidth: ���º�Ĵ���ģʽ
 �� �� ֵ  : ��+ ���ú���  :+ ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_void  dmac_chan_adjust_bandwidth_sta(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 *pen_bandwidth)
{
    wlan_channel_bandwidth_enum_uint8   en_curr_bandwidth;
    wlan_channel_bandwidth_enum_uint8   en_announced_bandwidth;
    en_curr_bandwidth      = pst_mac_vap->st_channel.en_bandwidth;
    en_announced_bandwidth = pst_mac_vap->st_ch_switch_info.en_new_bandwidth;
    *pen_bandwidth = en_curr_bandwidth;

    /* �����ǰ����ģʽ���´���ģʽ��ͬ����ֱ�ӷ��� */
    if (en_announced_bandwidth == en_curr_bandwidth)
    {
        return;
    }

    if (WLAN_BAND_WIDTH_20M == en_announced_bandwidth)
    {
        *pen_bandwidth = WLAN_BAND_WIDTH_20M;
    }
    else   /* �´���ģʽ����20MHz����STA�����ģʽ��Ҫ����������������ƥ�� */
    {
        /* ʹ��40MHz */
        /* (1) �û�����"40MHz����"����(��STA�� dot11FortyMHzOperationImplementedΪtrue) */
        /* (2) AP��40MHz���� */
        if (OAL_TRUE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
        {
            switch (en_announced_bandwidth)
            {
                case WLAN_BAND_WIDTH_40PLUS:
                case WLAN_BAND_WIDTH_80PLUSPLUS:
                case WLAN_BAND_WIDTH_80PLUSMINUS:
                    *pen_bandwidth = WLAN_BAND_WIDTH_40PLUS;
                    break;

                case WLAN_BAND_WIDTH_40MINUS:
                case WLAN_BAND_WIDTH_80MINUSPLUS:
                case WLAN_BAND_WIDTH_80MINUSMINUS:
                    *pen_bandwidth = WLAN_BAND_WIDTH_40MINUS;
                    break;

                default:
                    *pen_bandwidth = WLAN_BAND_WIDTH_20M;
                    break;
            }
        }

        /* ʹ��80MHz */
        /* (1) �û�֧��80MHz����(��STA�� dot11VHTChannelWidthOptionImplementedΪ0) */
        if (OAL_TRUE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        {
            if (WLAN_MIB_VHT_SUPP_WIDTH_80 == mac_mib_get_VHTChannelWidthOptionImplemented(pst_mac_vap))
            {
                *pen_bandwidth = en_announced_bandwidth;
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_chan_multi_select_channel_mac
 ��������  : ����device������VAP������SW/MAC/PHY/RF�е��ŵ��ʹ���ʹVAP���������ŵ���
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ��
             uc_channel  : ��Ҫ�����õ��ŵ���
             en_bandwidth: ��Ҫ�����õĴ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  dmac_chan_multi_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_channel_stru   st_channel;
    oal_uint8          uc_old_chan_number;
    mac_vap_stru      *pst_vap;
    oal_uint8          uc_idx;
    oal_uint32         ul_ret;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
        "{hmac_chan_multi_select_channel_mac::pst_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_select_channel_mac::none vap.}");
        return;
    }

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_chan_select_channel_mac:: Switching channel to %d! BW %d mode,hal chan is %d.}",
                     uc_channel, en_bandwidth, pst_device->pst_device_stru->uc_current_chan_number);

    /* ����VAP�µ���20MHz�ŵ��š�����ģʽ���ŵ����� */
    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, uc_channel, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_chan_select_channel_mac::mac_get_channel_idx_from_num failed[%d].}", ul_ret);
        return;
    }

    uc_old_chan_number = pst_mac_vap->st_channel.uc_chan_number;
    pst_mac_vap->st_channel.uc_chan_number = uc_channel;
    pst_mac_vap->st_channel.en_bandwidth   = en_bandwidth;
    pst_mac_vap->st_channel.uc_idx         = uc_idx;

    /* ֪ͨ�㷨�ŵ��ı� */
    dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);
    /* ֪ͨ�㷨����ı� */
    dmac_alg_cfg_bandwidth_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

#ifdef _PRE_WLAN_FEATURE_DBAC
    ul_ret = mac_fcs_dbac_state_check(pst_device);
    if ((mac_is_dbac_running(pst_device)) && (MAC_FCS_DBAC_NEED_CLOSE == ul_ret))
    {
        /* DBAC������,�л��ŵ���Ϊͬ�ŵ�,��Ҫ�ر�DBAC,��������2��vap������ */
        dmac_alg_update_dbac_fcs_config(pst_mac_vap);
        dmac_alg_vap_down_notify(pst_mac_vap);

        st_channel = pst_mac_vap->st_channel;
        dmac_chan_select_real_channel(pst_device, &st_channel);
        /* DBACͬ�ŵ�����������Ҫ���FIFO */
        dmac_mgmt_switch_channel(pst_device, &st_channel, OAL_FALSE);
    }
    else if((mac_is_dbac_running(pst_device)) && (MAC_FCS_DBAC_NEED_OPEN == ul_ret))
    {
        /* DBAC������,�л��ŵ����������ŵ�,ֻ��Ҫ����dbac���� */
        dmac_alg_update_dbac_fcs_config(pst_mac_vap);
        if(pst_device->pst_device_stru->uc_current_chan_number == uc_old_chan_number)
        {
            /* �����ǰʱ����wlanʱ��������wlan�ŵ��仯,�л����ܷ��ͱ��� */
            dmac_vap_pause_tx(pst_mac_vap);
        }
    }
    else if((!mac_is_dbac_running(pst_device)) && (MAC_FCS_DBAC_NEED_OPEN == ul_ret))
    {
        /* ��DBAC������,�л��ŵ���Ϊ���ŵ�, ��Ҫ����DBAC */
        /* wlan vap�������ŵ�����Ҫ��ͣ����. */
        dmac_vap_pause_tx(pst_mac_vap);
        dmac_alg_vap_up_notify(pst_mac_vap);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_chan_select_channel_mac:: start dbac,hal chan is %d.}",
                         pst_device->pst_device_stru->uc_current_chan_number);

        if(pst_device->pst_device_stru->uc_current_chan_number == pst_mac_vap->st_channel.uc_chan_number)
        {
            /* ���DBAC������ʼ��wlan vap��������resume wlan vap����,������DBAC��resume vap�Ķ��� */
            mac_vap_resume_tx(pst_mac_vap);
        }
    }
    else
    /* �������,������2��up��vap,DBAC���ڹر�״̬ */
#endif
    {
        /* ����device������vap */
        for (uc_vap_idx = 0; uc_vap_idx <pst_device->uc_vap_num; uc_vap_idx++)
        {
            pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                "{hmac_chan_multi_select_channel_mac::pst_vap null,vap_id=%d.}", pst_device->auc_vap_id[uc_vap_idx]);
                continue;
            }

            /* �л������ŵ����� */
            dmac_chan_select_channel_mac(pst_mac_vap, uc_channel, en_bandwidth);
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_chan_sta_switch_channel
 ��������  : STA�л��ŵ�
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  dmac_chan_sta_switch_channel(mac_vap_stru *pst_mac_vap)
{
    wlan_channel_bandwidth_enum_uint8   en_new_bandwidth = WLAN_BAND_WIDTH_20M;
    wlan_bw_cap_enum_uint8              en_bwcap_vap;
    mac_user_stru                      *pst_mac_user;
    dmac_user_stru                     *pst_dmac_user;

    mac_channel_stru                    st_old_channel;    /* vap���ڵ��ŵ� */
    mac_scan_req_stru                   st_scan_req_params;

    if (WLAN_BAND_WIDTH_BUTT != pst_mac_vap->st_ch_switch_info.en_new_bandwidth)
    {
        dmac_chan_adjust_bandwidth_sta(pst_mac_vap, &en_new_bandwidth);
    }
    oal_memcopy(&st_old_channel, &pst_mac_vap->st_channel, OAL_SIZEOF(st_old_channel));

    /* ��ֹӲ��ȫ������ֱ��STA�ŵ��л���� */
    dmac_chan_disable_machw_tx(pst_mac_vap);
    /* �л��ŵ� */
    dmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_ch_switch_info.uc_new_channel, en_new_bandwidth);

    /* ���øñ���������STA���ŵ��л�ʱ����link loss */
    //pst_mac_vap->st_ch_switch_info.en_waiting_for_ap           = OAL_TRUE;

    /* STA���л������ŵ��� */
    pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero     = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.en_new_bandwidth            = WLAN_BAND_WIDTH_BUTT;
    pst_mac_vap->st_ch_switch_info.uc_csa_rsv_cnt              = 0;
    pst_mac_vap->st_ch_switch_info.bit_bad_ap                  = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.uc_ch_swt_start_cnt         = 0;


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif

    /* ����user��������֪ͨ�㷨��ͬ��host */
    mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_vap);
    pst_mac_user = mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id);
    if (pst_mac_user != OAL_PTR_NULL)
    {
        mac_vap_get_bandwidth_cap(pst_mac_vap,&en_bwcap_vap);
        mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, en_bwcap_vap);

        /* user��������㷨�ı����֪ͨ�� */
        dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, pst_mac_user);
        dmac_config_d2h_user_info_syn(pst_mac_vap, pst_mac_user);
    }

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* �ŵ��л���ɰ�������dtim˯�߻��� */
    dmac_psm_update_dtime_period(pst_mac_vap,
                                    (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod,
                                    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

#endif

    dmac_chan_enable_machw_tx(pst_mac_vap);

    /* �����ŵ���ɾ��BA����ֹ�л��ŵ������н�Ӳ��������յ���BA�ƴ��쳣 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_vap->uc_assoc_vap_id);
    if(OAL_PTR_NULL != pst_dmac_user)
    {
        dmac_tx_delete_ba(pst_dmac_user);
    }

    dmac_trigger_csa_scan(&st_scan_req_params, pst_mac_vap, &st_old_channel);
}

/*****************************************************************************
 �� �� ��  : dmac_handle_tbtt_chan_mgmt_sta
 ��������  : STA��TBTT�ж��н����ŵ�����
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��+ �� �� ֵ  : ��+ ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  dmac_handle_tbtt_chan_mgmt_sta(dmac_vap_stru *pst_dmac_vap)
{
    mac_vap_stru *pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    if ((OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap)) || (OAL_TRUE == pst_mac_vap->st_ch_switch_info.bit_bad_ap))
    {
        return;
    }

    /* ���AP���͵�CSA IE�е�"�ŵ��л�����"Ϊ�㣬�������л��ŵ� */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero)
    {
        dmac_chan_sta_switch_channel(pst_mac_vap);
        dmac_vap_linkloss_clean(pst_dmac_vap);      //�е����ŵ�,linkloss�������¿�ʼ����
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,"{dmac_handle_tbtt_chan_mgmt_sta::beacon cnt zero to switch channel %d}",
                 pst_mac_vap->st_channel.uc_chan_number);
    }
#if 0
    /* �ŵ��л��Ѿ���ɡ��������ŵ��ϵȴ�����AP���͵�Beacon֡ */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_for_ap)
    {
        /* �ȴ�һ��ʱ��������ŵ��ϻָ�Ӳ������(������ʱAP�п��ܻ�û���л������ŵ�) */
        if (pst_dmac_vap->st_linkloss_info.us_link_loss > WLAN_LINKLOSS_OFFSET_11H)
        {
            pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = OAL_FALSE;
            dmac_chan_enable_machw_tx(pst_mac_vap);
            dmac_vap_linkloss_clean(pst_dmac_vap);
        }
    }
#endif
    /* ���AP���͵�CSA IE�е�"�ŵ��л�����"��Ϊ�㣬��ÿһ��TBTT�ж��м�һ */
    if (pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt > 0)
    {
        pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt--;
        if (0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)
        {
            if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel)
            {
                dmac_chan_sta_switch_channel(pst_mac_vap);
                dmac_vap_linkloss_clean(pst_dmac_vap);      //�е����ŵ�,linkloss�������¿�ʼ����
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,"{dmac_handle_tbtt_chan_mgmt_sta::tbtt cnt to switch channel %d}",
                                 pst_mac_vap->st_channel.uc_chan_number);

            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_is_active_htsta
 ��������  : �ж�sta�Ƿ�Ϊ��Ծsta
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��+ �� �� ֵ  : ��+ ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint8  dmac_mgmt_is_active_htsta(mac_vap_stru *pst_mac_vap)
{
    //TODO Ŀǰ�ú���ʼ�շ���true, ���б�Ҫ�ڴ˴������ж�sta�Ƿ�Ϊ��Ծht sta�Ĵ���
    return OAL_TRUE;
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : dmac_mgmg_need_obss_scan
 ��������  : �ж��Ƿ���Ҫ����obss scan
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ�룬ָ��sta
 �������  : ��+ �� �� ֵ  : ��+ ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint8  dmac_mgmt_need_obss_scan(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru                     *pst_device;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "dmac_mgmt_need_obss_scan::null param");
        return OAL_FALSE;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN,
            "{dmac_mgmt_need_obss_scan::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    if (0 != pst_device->st_p2p_info.uc_p2p_goclient_num)
    {
        return OAL_FALSE;
    }
#endif

    //l00311403 ��ǰvht������obssɨ��,����״̬��vap��up��pause����״̬,ɨ��ʱpause,obssɨ��ᱻͣ��
    if ( (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode) &&
         ((MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state)) &&
         (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)&&
         (OAL_TRUE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap)) &&
         (OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
         (OAL_TRUE == mac_vap_get_peer_obss_scan(pst_mac_vap)) &&
         (OAL_TRUE == dmac_mgmt_is_active_htsta(pst_mac_vap))
          )
     {
        return OAL_TRUE;
     }

    return OAL_FALSE;
}
/*****************************************************************************
 �� �� ��  : dmac_ie_proc_obss_scan_ie
 ��������  : ����Overlapping BSS Scan Parameters IE��������STA��ӦMIB��
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             puc_payload: ָ��Overlapping BSS Scan Parameters IE��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : OAL_SUCC������������
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��6��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_ie_proc_obss_scan_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload)
{
    dmac_vap_stru *pst_dmac_vap;
    oal_uint32    ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{dmac_ie_proc_obss_scan_ie::param null,pst_mac_vap = [%p],puc_payload = [%p]}",
                            pst_mac_vap,puc_payload);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ie_proc_obss_scan_ie::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    ul_ret = mac_ie_proc_obss_scan_ie(pst_mac_vap, puc_payload);
    if (OAL_SUCC != ul_ret)
    {
        //OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ie_proc_obss_scan_ie::mac_ie_proc_obss_scan_ie fail,ret:%u.}", ul_ret);
        return OAL_FAIL;
    }

    /* 20/40�����߼�����ʱ���ж��Ƿ�����obssɨ�趨ʱ�� */
    /* STAģʽ������Ҫobssɨ�趨ʱ��������ʱ�� */
    if ((OAL_TRUE == dmac_mgmt_need_obss_scan(pst_mac_vap)) &&
         (OAL_FALSE == pst_dmac_vap->uc_obss_scan_timer_started) )
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_ie_proc_obss_scan_ie:: start obss scan}");
        dmac_scan_start_obss_timer(pst_mac_vap);
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_sta_up_update_ht_params
 ��������  : STA�յ�Beacon֡�󣬴���HT�����ϢԪ��
 �������  : pst_mac_vap    : MAC VAP�ṹ��ָ�룬ָ��STA
             puc_payload    : ָ��Beacon֡���ָ��
             us_frame_len   : Beacon֡��ĳ���(������֡ͷ)
             us_frame_offset: Beacon֡�е�һ��IE���֡���ַ��ƫ��
 �������  : pst_mac_user   : MAC USER�ṹ��ָ�룬ָ��AP
 �� �� ֵ  : oal_bool_enum_uint8:�����Ϣ�Ƿ��иı䣬�Ƿ���Ҫͬ��?
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��4��6��
    ��    ��   : liuzhengqi
    �޸�����   : ���Ƶ�device

*****************************************************************************/
oal_uint32 dmac_sta_up_update_ht_params(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload,
                                                   oal_uint16 us_frame_len,mac_user_stru *pst_mac_user)
{
    mac_user_ht_hdl_stru   st_ht_hdl;
    oal_uint32             ul_change             = MAC_NO_CHANGE;
    oal_uint8             *puc_ie                = OAL_PTR_NULL;

    mac_user_get_ht_hdl(pst_mac_user, &st_ht_hdl);

    puc_ie = mac_find_ie(MAC_EID_HT_OPERATION, puc_payload, us_frame_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        ul_change |= mac_proc_ht_opern_ie(pst_mac_vap, puc_ie, pst_mac_user);
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    puc_ie = mac_find_ie(MAC_EID_OBSS_SCAN, puc_payload, us_frame_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        /* ���� Overlapping BSS Scan Parameters IE */
        dmac_ie_proc_obss_scan_ie(pst_mac_vap, puc_ie);
    }
    else
    {
        /* �Ҳ���OBSS IE����OBSSɨ���־��ΪFalse������else��֧�������ڲ���OBSS IE֮ǰ��Ϊ�˱���֮ǰ�Ѿ���ΪTRUE��
           ʵ����OBSS IE�����ڲ���֮ǰ��ΪFALSE������������*/
        mac_vap_set_peer_obss_scan(pst_mac_vap, OAL_FALSE);
    }
#endif /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

    if (0 != OAL_MEMCMP((oal_uint8 *)(&st_ht_hdl), (oal_uint8 *)(&pst_mac_user->st_ht_hdl), OAL_SIZEOF(mac_user_ht_hdl_stru)))
    {
        return (ul_change | MAC_HT_CHANGE);
    }

    return ul_change;
}
/*****************************************************************************
 �� �� ��  : dmac_sta_up_update_vht_params
 ��������  : STA�յ�Beacon֡�󣬴���VHT�����ϢԪ��
 �������  : pst_mac_vap    : MAC VAP�ṹ��ָ�룬ָ��STA
             puc_payload    : ָ��Beacon֡���ָ��
             us_frame_len   : Beacon֡��ĳ���(������֡ͷ)
             us_frame_offset: Beacon֡�е�һ��IE���֡���ַ��ƫ��
 �������  : MAC USER�ṹ��ָ�룬ָ��AP
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��18��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��4��6��
    ��    ��   : liuzhengqi
    �޸�����   : ���Ƶ�device
*****************************************************************************/
oal_uint32 dmac_sta_up_update_vht_params(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload,
                                                   oal_uint16   us_frame_len,mac_user_stru *pst_mac_user)
{
    mac_vht_hdl_stru  st_vht_hdl;
    oal_uint8        *puc_vht_opern_ie;
    oal_uint32        ul_change = MAC_NO_CHANGE;

    /* ֧��11ac���Ž��к����Ĵ��� */
    if (OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
    {
        return ul_change;
    }

    mac_user_get_vht_hdl(pst_mac_user, &st_vht_hdl);

    puc_vht_opern_ie = mac_find_ie(MAC_EID_VHT_OPERN, puc_payload, us_frame_len);
    if (OAL_PTR_NULL == puc_vht_opern_ie)
    {
        return ul_change;
    }

    ul_change = mac_ie_proc_vht_opern_ie(pst_mac_vap, puc_vht_opern_ie, pst_mac_user);

    if (0 != OAL_MEMCMP((oal_uint8 *)(&st_vht_hdl), (oal_uint8 *)(&pst_mac_user->st_vht_hdl), OAL_SIZEOF(mac_vht_hdl_stru)))
    {
        return (MAC_VHT_CHANGE | ul_change);
    }

    return ul_change;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

