/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_ie.c
  �� �� ��   : ����
  ��    ��   : zourong
  ��������   : 2013��1��8��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��1��8��
    ��    ��   : zourong
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
#include "mac_frame.h"
#include "mac_device.h"
#include "dmac_chan_mgmt.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_IE_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mac_ie_get_vht_rx_mcs_map
 ��������  : ��ȡVHT��ϢԪ���еĽ��շ����mcs����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��23��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_ie_get_vht_rx_mcs_map(mac_rx_max_mcs_map_stru    *pst_mac_rx_mcs_sta,
                                               mac_rx_max_mcs_map_stru    *pst_mac_rx_mcs_ap)
{
    oal_uint16      *pus_rx_mcs_sta;

    /* ��ȡ�ռ���1���ռ���2��������Ϣ��Ŀǰ1151���֧��2���ռ��� */
    if ((pst_mac_rx_mcs_sta->us_max_mcs_1ss != 0x3) && (pst_mac_rx_mcs_ap->us_max_mcs_1ss != 0x3))
    {
        pst_mac_rx_mcs_sta->us_max_mcs_1ss = pst_mac_rx_mcs_sta->us_max_mcs_1ss > pst_mac_rx_mcs_ap->us_max_mcs_1ss
                                             ? pst_mac_rx_mcs_ap->us_max_mcs_1ss : pst_mac_rx_mcs_sta->us_max_mcs_1ss;
    }
    else
    {
        pst_mac_rx_mcs_sta->us_max_mcs_1ss = 0x3;
    }

    if ((pst_mac_rx_mcs_sta->us_max_mcs_2ss != 0x3) && (pst_mac_rx_mcs_ap->us_max_mcs_2ss != 0x3))
    {
        pst_mac_rx_mcs_sta->us_max_mcs_2ss = pst_mac_rx_mcs_sta->us_max_mcs_2ss > pst_mac_rx_mcs_ap->us_max_mcs_2ss
                                             ? pst_mac_rx_mcs_ap->us_max_mcs_2ss : pst_mac_rx_mcs_sta->us_max_mcs_2ss;
    }
    else
    {
        pst_mac_rx_mcs_sta->us_max_mcs_2ss = 0x3;
    }

    /* �������Ŀռ�����Ŀ */
    pus_rx_mcs_sta = (oal_uint16 *)pst_mac_rx_mcs_sta;

    *pus_rx_mcs_sta = (*pus_rx_mcs_sta) | 0xFFF0;
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_ht_supported_channel_width
 ��������  : ����ht cap ie�е� supported channel width
 �������  :
            pst_mac_user_sta           : user�ṹ��ָ��
            pst_mac_vap                : vap�ṹ��ָ��
            uc_supported_channel_width : �Ƿ�֧��40Mhz����  0: ��֧�֣� 1: ֧��
            en_prev_asoc_ht            : user֮ǰ�Ƿ���htվ����ݹ�����ap  0: ֮ǰδ������ 1: ֮ǰ������
 �������  : ��
 �� �� ֵ  :�û��й��������st_ht_hdl.bit_supported_channel_width��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_ie_proc_ht_supported_channel_width(
                                        mac_user_stru    *pst_mac_user_sta ,
                                        mac_vap_stru     *pst_mac_vap,
                                        oal_uint8         uc_supported_channel_width,
                                        oal_bool_enum     en_prev_asoc_ht)
{

    /* ��֧��20/40MhzƵ��*/
    if (0 == uc_supported_channel_width)
    {
        /*  ���STA֮ǰû����ΪHTվ����AP������ ����STA֮ǰ�Ѿ���Ϊ֧��20/40MhzƵ���HTվ����AP����*/
        if ((OAL_FALSE == en_prev_asoc_ht) || (OAL_TRUE == pst_mac_user_sta->st_ht_hdl.bit_supported_channel_width))
        {
            pst_mac_vap->st_protection.uc_sta_20M_only_num++;
        }

        return OAL_FALSE;
    }
    else/* ֧��20/40MhzƵ�� */
    {
        /*  ���STA֮ǰ�Ѿ���Ϊ��֧��20/40MhzƵ���HTվ����AP����*/
        if ((OAL_TRUE == en_prev_asoc_ht) && (OAL_FALSE == pst_mac_user_sta->st_ht_hdl.bit_supported_channel_width))
        {
            pst_mac_vap->st_protection.uc_sta_20M_only_num--;
        }

        return OAL_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_ht_green_field
 ��������  : ����ht cap ie�е� ht green field  BIT4
 �������  :
            pst_mac_user_sta  : user�ṹ��ָ��
            pst_mac_vap       : vap�ṹ��ָ��
            uc_ht_green_field : �Ƿ�֧��gf�� 0: ��֧�֣� 1: ֧��
            en_prev_asoc_ht   : user֮ǰ�Ƿ���htվ����ݹ�����ap  0: ֮ǰδ������ 1: ֮ǰ������
 �������  : ��
 �� �� ֵ  :�û����������st_ht_hdl.bit_ht_green_field��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��12��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_ie_proc_ht_green_field(
                                        mac_user_stru    *pst_mac_user_sta ,
                                        mac_vap_stru     *pst_mac_vap,
                                        oal_uint8         uc_ht_green_field,
                                        oal_bool_enum     en_prev_asoc_ht)
{
    /* ��֧��Greenfield */
    if (0 == uc_ht_green_field)
    {
        /*  ���STA֮ǰû����ΪHTվ����AP������ ����STA֮ǰ�Ѿ���Ϊ֧��GF��HTվ����AP����*/
        if ((OAL_FALSE == en_prev_asoc_ht ) || (OAL_TRUE == pst_mac_user_sta->st_ht_hdl.bit_ht_green_field))
        {
            pst_mac_vap->st_protection.uc_sta_non_gf_num++;
        }

        return OAL_FALSE;
    }
    else/* ֧��Greenfield */
    {
        /*  ���STA֮ǰ�Ѿ���Ϊ��֧��GF��HTվ����AP����*/
        if ((OAL_TRUE == en_prev_asoc_ht ) && (OAL_FALSE == pst_mac_user_sta->st_ht_hdl.bit_ht_green_field))
        {
            pst_mac_vap->st_protection.uc_sta_non_gf_num--;
        }

        return OAL_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_lsig_txop_protection_support
 ��������  : ����ht cap ie�е� lsig_txop_protection_support
 �������  :
            pst_mac_user_sta                : user�ṹ��ָ��
            pst_mac_vap                     : vap�ṹ��ָ��
            uc_lsig_txop_protection_support : �Ƿ�֧��lsig txop������ 0: ��֧�֣� 1: ֧��
            en_prev_asoc_ht                 : user֮ǰ�Ƿ���htվ����ݹ�����ap  0: ֮ǰδ������ 1: ֮ǰ������
 �������  : ��
 �� �� ֵ  :�û����������st_ht_hdl.bit_lsig_txop_protection��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_ie_proc_lsig_txop_protection_support(
                                        mac_user_stru    *pst_mac_user_sta,
                                        mac_vap_stru     *pst_mac_vap,
                                        oal_uint8         uc_lsig_txop_protection_support,
                                        oal_bool_enum     en_prev_asoc_ht)
{
    /* ��֧��L-sig txop protection */
    if (0 == uc_lsig_txop_protection_support)
    {
        /*  ���STA֮ǰû����ΪHTվ����AP������ ����STA֮ǰ�Ѿ���Ϊ֧��Lsig txop protection��HTվ����AP����*/
        if ((OAL_FALSE == en_prev_asoc_ht) || (OAL_TRUE == pst_mac_user_sta->st_ht_hdl.bit_lsig_txop_protection))
        {
            pst_mac_vap->st_protection.uc_sta_no_lsig_txop_num++;
        }

        return OAL_FALSE;
    }
    else /* ֧��L-sig txop protection */
    {
        /*  ���STA֮ǰ�Ѿ���Ϊ��֧��Lsig txop protection��HTվ����AP����*/
        if ((OAL_TRUE == en_prev_asoc_ht ) && (OAL_FALSE == pst_mac_user_sta->st_ht_hdl.bit_lsig_txop_protection))
        {
            pst_mac_vap->st_protection.uc_sta_no_lsig_txop_num--;
        }

        return OAL_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_ht_sta
 ��������  : ����asoc rsp frame֡�е�HT cap IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��10��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_ie_proc_ht_sta(
                   mac_vap_stru            *pst_mac_sta,
                   oal_uint8                *puc_payload,
                   oal_uint16               *pus_index,
                   mac_user_stru           *pst_mac_user_ap,
                   oal_uint16               *pus_ht_cap_info,
                   oal_uint16               *pus_amsdu_maxsize)
{
    oal_uint8                           uc_mcs_bmp_index;
    oal_uint8                           uc_smps;
    oal_uint16                          us_offset;
    mac_user_ht_hdl_stru               *pst_ht_hdl;
    mac_user_ht_hdl_stru                st_ht_hdl;
    mac_user_stru                      *pst_mac_user;
    oal_uint16					        us_tmp_info_elem;
	oal_uint16					        us_tmp_txbf_low;
	oal_uint32					        ul_tmp_txbf_elem;

    if ((OAL_PTR_NULL == pst_mac_sta) || (OAL_PTR_NULL == puc_payload)
        ||(OAL_PTR_NULL == pus_index) || (OAL_PTR_NULL == pst_mac_user_ap)|| (OAL_PTR_NULL == pus_ht_cap_info)
        || (OAL_PTR_NULL == pus_amsdu_maxsize))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_ie_proc_ht_sta::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    us_offset       = *pus_index;
    pst_mac_user    = pst_mac_user_ap;
    pst_ht_hdl      = &st_ht_hdl;
    mac_user_get_ht_hdl(pst_mac_user, pst_ht_hdl);

    /* ���� HT Capability Element �� AP����ʾ������HT capable. */
    pst_ht_hdl->en_ht_capable = OAL_TRUE;

    us_offset += MAC_IE_HDR_LEN;

    /********************************************/
    /*     ���� HT Capabilities Info Field      */
    /********************************************/
    *pus_ht_cap_info = OAL_MAKE_WORD16(puc_payload[us_offset], puc_payload[us_offset + 1]);

    /* ���STA��֧�ֵ�LDPC�������� B0��0:��֧�֣�1:֧�� */
    pst_ht_hdl->bit_ldpc_coding_cap = (*pus_ht_cap_info & BIT0);

    /* ��ȡAP��֧�ֵĴ�������  */
    pst_ht_hdl->bit_supported_channel_width = ((*pus_ht_cap_info & BIT1) >> 1);

    /* ���ռ临�ý���ģʽ B2~B3 */
    uc_smps = (*pus_ht_cap_info & (BIT2 | BIT3));
    pst_ht_hdl->bit_sm_power_save = mac_ie_proc_sm_power_save_field(pst_mac_user, uc_smps);

    /* ��ȡAP֧��Greenfield��� */
    pst_ht_hdl->bit_ht_green_field = ((*pus_ht_cap_info & BIT4) >> 4);

    /* ��ȡAP֧��20MHz Short-GI��� */
    pst_ht_hdl->bit_short_gi_20mhz = ((*pus_ht_cap_info & BIT5) >> 5);

    /* ��ȡAP֧��40MHz Short-GI��� */
    pst_ht_hdl->bit_short_gi_40mhz = ((*pus_ht_cap_info & BIT6) >> 6);

    /* ��ȡAP֧��STBC PPDU��� */
    pst_ht_hdl->bit_rx_stbc = (oal_uint8)((*pus_ht_cap_info & 0x30) >> 4);

    /* ��ȡAP֧�����A-MSDU������� */
    if(0 == (*pus_ht_cap_info & BIT11))
    {
        *pus_amsdu_maxsize = WLAN_MIB_MAX_AMSDU_LENGTH_SHORT;
    }
    else
    {
        *pus_amsdu_maxsize = WLAN_MIB_MAX_AMSDU_LENGTH_LONG;
    }

    /* ��ȡAP 40M��DSSS/CCK��֧����� */
    pst_ht_hdl->bit_dsss_cck_mode_40mhz = ((*pus_ht_cap_info & BIT12) >> 12);

    /* ��ȡAP L-SIG TXOP ������֧����� */
    pst_ht_hdl->bit_lsig_txop_protection = ((*pus_ht_cap_info & BIT15) >> 15);

    us_offset += MAC_HT_CAPINFO_LEN;

    /********************************************/
    /*     ���� A-MPDU Parameters Field         */
    /********************************************/

    /* ��ȡ Maximum Rx A-MPDU factor (B1 - B0) */
    pst_ht_hdl->uc_max_rx_ampdu_factor = (puc_payload[us_offset] & 0x03);

    /* ��ȡ Minmum Rx A-MPDU factor (B3 - B2) */
    pst_ht_hdl->uc_min_mpdu_start_spacing = (puc_payload[us_offset] >> 2) & 0x07;

    us_offset += MAC_HT_AMPDU_PARAMS_LEN;

    /********************************************/
    /*     ���� Supported MCS Set Field         */
    /********************************************/
    for(uc_mcs_bmp_index = 0; uc_mcs_bmp_index < WLAN_HT_MCS_BITMASK_LEN; uc_mcs_bmp_index++)
    {
        pst_ht_hdl->uc_rx_mcs_bitmask[uc_mcs_bmp_index] =
        (pst_mac_sta->pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[uc_mcs_bmp_index])&
        (*(oal_uint8 *)(puc_payload + us_offset + uc_mcs_bmp_index));
    }

    pst_ht_hdl->uc_rx_mcs_bitmask[WLAN_HT_MCS_BITMASK_LEN - 1] &= 0x1F;

    us_offset += MAC_HT_SUP_MCS_SET_LEN;

    /********************************************/
    /* ���� HT Extended Capabilities Info Field */
    /********************************************/
    *pus_ht_cap_info = OAL_MAKE_WORD16(puc_payload[us_offset], puc_payload[us_offset + 1]);

    /* ��ȡ HTC support Information */
    if ((*pus_ht_cap_info & BIT10) != 0)
    {
        pst_ht_hdl->uc_htc_support = 1;
    }
    us_offset += MAC_HT_EXT_CAP_LEN;

    /********************************************/
    /*  ���� Tx Beamforming Field               */
    /********************************************/
    us_tmp_info_elem = OAL_MAKE_WORD16(puc_payload[us_offset], puc_payload[us_offset + 1]);
    us_tmp_txbf_low	 = OAL_MAKE_WORD16(puc_payload[us_offset + 2], puc_payload[us_offset + 3]);
	ul_tmp_txbf_elem = OAL_MAKE_WORD32(us_tmp_info_elem, us_tmp_txbf_low);
    pst_ht_hdl->bit_imbf_receive_cap				= (ul_tmp_txbf_elem & BIT0);
    pst_ht_hdl->bit_receive_staggered_sounding_cap  = ((ul_tmp_txbf_elem & BIT1) >> 1);
    pst_ht_hdl->bit_transmit_staggered_sounding_cap = ((ul_tmp_txbf_elem & BIT2) >> 2);
    pst_ht_hdl->bit_receive_ndp_cap					= ((ul_tmp_txbf_elem & BIT3) >> 3);
    pst_ht_hdl->bit_transmit_ndp_cap				= ((ul_tmp_txbf_elem & BIT4) >> 4);
    pst_ht_hdl->bit_imbf_cap						= ((ul_tmp_txbf_elem & BIT5) >> 5);
    pst_ht_hdl->bit_calibration						= ((ul_tmp_txbf_elem & 0x000000C0) >> 6);
    pst_ht_hdl->bit_exp_csi_txbf_cap				= ((ul_tmp_txbf_elem & BIT8) >> 8);
    pst_ht_hdl->bit_exp_noncomp_txbf_cap			= ((ul_tmp_txbf_elem & BIT9) >> 9);
    pst_ht_hdl->bit_exp_comp_txbf_cap				= ((ul_tmp_txbf_elem & BIT10) >> 10);
    pst_ht_hdl->bit_exp_csi_feedback				= ((ul_tmp_txbf_elem & 0x00001800) >> 11);
    pst_ht_hdl->bit_exp_noncomp_feedback			= ((ul_tmp_txbf_elem & 0x00006000) >> 13);
    pst_ht_hdl->bit_exp_comp_feedback				= ((ul_tmp_txbf_elem & 0x0001C000) >> 15);
    pst_ht_hdl->bit_min_grouping					= ((ul_tmp_txbf_elem & 0x00060000) >> 17);
    pst_ht_hdl->bit_csi_bfer_ant_number				= ((ul_tmp_txbf_elem & 0x001C0000) >> 19);
    pst_ht_hdl->bit_noncomp_bfer_ant_number			= ((ul_tmp_txbf_elem & 0x00600000) >> 21);
    pst_ht_hdl->bit_comp_bfer_ant_number			= ((ul_tmp_txbf_elem & 0x01C00000) >> 23);
    pst_ht_hdl->bit_csi_bfee_max_rows				= ((ul_tmp_txbf_elem & 0x06000000) >> 25);
    pst_ht_hdl->bit_channel_est_cap					= ((ul_tmp_txbf_elem & 0x18000000) >> 27);


    mac_user_set_ht_hdl(pst_mac_user, pst_ht_hdl);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_ie_check_p2p_action
 ��������  : ���action֡�ǲ���p2p֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_ie_check_p2p_action(oal_uint8 *puc_payload)
{
    //oal_uint8   auc_p2p_oui[MAC_OUI_LEN] = {0x50, 0x6F, 0x9A};

    /* �ҵ�WFA OUI */
    if ((0 == oal_memcmp(puc_payload, g_auc_p2p_oui, MAC_OUI_LEN)) &&
        (MAC_OUITYPE_P2P == puc_payload[MAC_OUI_LEN]))
    {
        /*  �ҵ�WFA P2P v1.0 oui type */
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_update_sm_power_save
 ��������  : ����ht cap ie�е� sm power save field B2~B3
 �������  : pst_mac_user_sta --�û��ṹ��ָ�룬uc_smps--�û�smpsģʽ
 �������  : ��
 �� �� ֵ  : �û���Ϣ��st_ht_hdl.bit_sm_power_save����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��12��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
wlan_mib_mimo_power_save_enum_uint8 mac_ie_proc_sm_power_save_field(mac_user_stru *pst_mac_user, oal_uint8 uc_smps)
{
    if (MAC_SMPS_STATIC_MODE == uc_smps)
    {
        return WLAN_MIB_MIMO_POWER_SAVE_STATIC;
    }
    else if (MAC_SMPS_DYNAMIC_MODE == uc_smps)
    {
        return WLAN_MIB_MIMO_POWER_SAVE_DYNAMIC;
    }
    else
    {
        return WLAN_MIB_MIMO_POWER_SAVE_MIMO;
    }

}

/*****************************************************************************
 �� �� ��  : mac_ie_get_chan_num
 ��������  : ��֡���н���ie�е�chan��Ϣ������HT operation IE����chan��Ϣ������ҵ��ͷ��أ����Ҳ���������DSSS Param set ie��Ѱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  mac_ie_get_chan_num(oal_uint8 *puc_frame_body, oal_uint16 us_frame_len, oal_uint16 us_offset,oal_uint8 uc_curr_chan)
{
    oal_uint8   uc_chan_num = 0;
    oal_uint8  *puc_ie_start_addr;

    /* ��DSSS Param set ie�н���chan num */
    puc_ie_start_addr = mac_find_ie(MAC_EID_DSPARMS, puc_frame_body + us_offset, us_frame_len - us_offset);
    if ((OAL_PTR_NULL != puc_ie_start_addr) && (puc_ie_start_addr[1] == MAC_DSPARMS_LEN))
    {
        uc_chan_num = puc_ie_start_addr[2];
        if (mac_is_channel_num_valid(mac_get_band_by_channel_num(uc_chan_num), uc_chan_num) == OAL_SUCC)
        {
            return  uc_chan_num;
        }
    }

    /* ��HT operation ie�н��� chan num */
    puc_ie_start_addr = mac_find_ie(MAC_EID_HT_OPERATION, puc_frame_body + us_offset, us_frame_len - us_offset);

    if ((OAL_PTR_NULL != puc_ie_start_addr) && (puc_ie_start_addr[1] >= 1))
    {
        uc_chan_num = puc_ie_start_addr[2];
        if (mac_is_channel_num_valid(mac_get_band_by_channel_num(uc_chan_num), uc_chan_num) == OAL_SUCC)
        {
            return  uc_chan_num;
        }
    }

    uc_chan_num = uc_curr_chan;
    return uc_chan_num;
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_ext_cap_ie
 ��������  : ����Extended Capabilities IE
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
             puc_payload : ָ��Extended Capabilities IE��ָ��
 �������  :
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_ie_proc_ext_cap_ie(mac_user_stru *pst_mac_user, oal_uint8 *puc_payload)
{
    mac_user_cap_info_stru   *pst_cap_info;
    oal_uint8                 uc_len;
    oal_uint8                 auc_cap[8] = {0};

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_ie_proc_ext_cap_ie::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_cap_info = &(pst_mac_user->st_cap_info);
    uc_len = puc_payload[1];
    if (uc_len >= MAC_IE_HDR_LEN && uc_len <= 8)
    {
        oal_memcopy(auc_cap, &puc_payload[MAC_IE_HDR_LEN], uc_len - MAC_IE_HDR_LEN);
    }

    /* ��ȡ BIT12: ֧��proxy arp */
    pst_cap_info->bit_proxy_arp = ((auc_cap[1] & BIT4) == 0) ? OAL_FALSE : OAL_TRUE;
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 �� �� ��  : mac_check_is_assoc_frame
 ��������  : �ж�֡�����Ƿ�Ϊ(��)��������/��Ӧ
 �������  : uc_mgmt_frm_type: ֡����
 �������  :
 �� �� ֵ  : ��OAL_TRUE/��OAL_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��2��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  mac_check_is_assoc_frame(oal_uint8 uc_mgmt_frm_type)
{
    if ((uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_ASSOC_RSP) ||
        (uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_REASSOC_REQ) ||
        (uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_REASSOC_RSP) ||
        (uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_ASSOC_REQ))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
#endif
#if 0
/*****************************************************************************
 �� �� ��  : mac_set_channel_switch_wrapper_ie
 ��������  : Ϊ11AC ģʽ�£���װchannel switch wrapper IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��6��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_set_channel_switch_wrapper_ie(
                oal_uint8                            uc_channel,
                wlan_channel_bandwidth_enum_uint8    en_bw,
                oal_uint8                           *pauc_buffer,
                oal_uint8                           *puc_output_len)
{
    oal_bool_enum_uint8  en_need_wideband_sub_ie;
    oal_uint8            uc_total_len = 0, uc_sub_len;
    oal_uint8           *puc_wrapper_ie_len;

    if ((OAL_PTR_NULL == pauc_buffer) || (OAL_PTR_NULL == puc_output_len))
    {

        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{mac_set_channel_switch_wrapper_ie::null param.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* Ĭ�����Ϊ�� */
    *pauc_buffer    = '\0';
    *puc_output_len = 0;

    /* 11ac ����Channel Switch Wrapper IE                             */
    /******************************************************************/
    /* -------------------------------------------------------------- */
    /* |ID |Length |New Country IE|Wideband IE |VHT power IE          */
    /* -------------------------------------------------------------- */
    /* |1  |1      |None          |5           |None                  */
    /*                                                                */
    /******************************************************************/
    pauc_buffer[0] = 196;
    pauc_buffer[1] = 0;
    puc_wrapper_ie_len = &pauc_buffer[1];
    pauc_buffer += 2;

    /* COUNTRY SUB ELEMENT --- N/A                       */
    /* ��ǰ���ŵ��л���������DFS���������ᵼ�¹������л� */

    /* WIDEBAND SUB ELEMENT  */
    /* ����20M���ϴ������Ч */
    en_need_wideband_sub_ie = OAL_TRUE;
    uc_sub_len = 0;
    if (WLAN_BAND_WIDTH_20M == en_bw)
    {
        en_need_wideband_sub_ie = OAL_FALSE;
    }

    if (OAL_TRUE == en_need_wideband_sub_ie)
    {
        uc_sub_len = 0;
        /* ��дWideband ��IE */
        pauc_buffer[0] = 194;
        pauc_buffer[1] = 3;
        switch(en_bw)
        {
            case WLAN_BAND_WIDTH_40PLUS:
                pauc_buffer[2] = 0;
                pauc_buffer[3] = uc_channel + 2;
                break;

            case WLAN_BAND_WIDTH_40MINUS:
                pauc_buffer[2] = 0;
                pauc_buffer[3] = uc_channel - 2;
                break;

            case WLAN_BAND_WIDTH_80PLUSPLUS:
                pauc_buffer[2] = 1;
                pauc_buffer[3] = uc_channel + 6;
                break;

            case WLAN_BAND_WIDTH_80PLUSMINUS:
                pauc_buffer[2] = 1;
                pauc_buffer[3] = uc_channel - 2;
                break;

            case WLAN_BAND_WIDTH_80MINUSPLUS:
                pauc_buffer[2] = 1;
                pauc_buffer[3] = uc_channel + 2;
                break;

            case WLAN_BAND_WIDTH_80MINUSMINUS:
                pauc_buffer[2] = 1;
                pauc_buffer[3] = uc_channel - 6;
                break;

            default:
                OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{mac_set_channel_switch_wrapper_ie::invalid bandwidth.}");

                return OAL_FAIL;
        }

        pauc_buffer[4] = 0; /* reserved. Not support 80M + 80M */

        uc_sub_len = 5;
    }
    pauc_buffer += uc_sub_len;
    uc_total_len += uc_sub_len;

    /* VHT POWER SUB ELEMENT --- N/A  */
    /* Ŀǰ���л����ᵼ�¹��ʸı�     */

    /* ����WRAPPER IE LEN */
    *puc_wrapper_ie_len = uc_total_len;

    *puc_output_len = uc_total_len + 2;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_set_second_channel_offset_ie
 ��������  : ������20M�ŵ�ƫ��IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��5��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_set_second_channel_offset_ie(
                wlan_channel_bandwidth_enum_uint8    en_bw,
                oal_uint8                           *pauc_buffer,
                oal_uint8                           *puc_output_len)
{
    if ((OAL_PTR_NULL == pauc_buffer) || (OAL_PTR_NULL == puc_output_len))
    {

        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{mac_set_second_channel_offset_ie::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* Ĭ�����Ϊ�� */
    *pauc_buffer    = '\0';
    *puc_output_len = 0;

    /* 11n ����Secondary Channel Offset Element */
    /******************************************************************/
    /* -------------------------------------------------------------- */
    /* |Ele. ID |Length |Secondary channel offset |                   */
    /* -------------------------------------------------------------- */
    /* |1       |1      |1                        |                   */
    /*                                                                */
    /******************************************************************/
    pauc_buffer[0] = 62;
    pauc_buffer[1] = 1;

    switch(en_bw)
    {
        case WLAN_BAND_WIDTH_20M:
            pauc_buffer[2] = 0;  /* no secondary channel */
            break;

        case WLAN_BAND_WIDTH_40PLUS:
        case WLAN_BAND_WIDTH_80PLUSPLUS:
        case WLAN_BAND_WIDTH_80PLUSMINUS:
            pauc_buffer[2] = 1;  /* secondary 20M channel above */
            break;

        case WLAN_BAND_WIDTH_40MINUS:
        case WLAN_BAND_WIDTH_80MINUSPLUS:
        case WLAN_BAND_WIDTH_80MINUSMINUS:
            pauc_buffer[2] = 3;  /* secondary 20M channel below */
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{mac_set_second_channel_offset_ie::invalid bandwidth[%d].}", en_bw);

            return OAL_FAIL;
    }

    *puc_output_len = 3;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_set_11ac_wideband_ie
 ��������  : Ϊ11ACģʽ�£��ŵ��л��������IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��5��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_set_11ac_wideband_ie(
                oal_uint8                            uc_channel,
                wlan_channel_bandwidth_enum_uint8    en_bw,
                oal_uint8                           *pauc_buffer,
                oal_uint8                           *puc_output_len)
{
    if ((OAL_PTR_NULL == pauc_buffer) || (OAL_PTR_NULL == puc_output_len))
    {

        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{mac_set_11ac_wideband_ie::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* Ĭ�����Ϊ�� */
    *pauc_buffer     = '\0';
    *puc_output_len  = 0;

    /* 11ac ����Wide Bandwidth Channel Switch Element                 */
    /******************************************************************/
    /* -------------------------------------------------------------- */
    /* |ID |Length |New Ch width |Center Freq seg1 |Center Freq seg2  */
    /* -------------------------------------------------------------- */
    /* |1  |1      |1            |1                |1                 */
    /*                                                                */
    /******************************************************************/
    pauc_buffer[0] = 194;
    pauc_buffer[1] = 3;
    switch(en_bw)
    {
        case WLAN_BAND_WIDTH_20M:
        case WLAN_BAND_WIDTH_40PLUS:
        case WLAN_BAND_WIDTH_40MINUS:
            pauc_buffer[2] = 0;
            pauc_buffer[3] = 0;
            break;

        case WLAN_BAND_WIDTH_80PLUSPLUS:
            pauc_buffer[2] = 1;
            pauc_buffer[3] = uc_channel + 6;
            break;

        case WLAN_BAND_WIDTH_80PLUSMINUS:
            pauc_buffer[2] = 1;
            pauc_buffer[3] = uc_channel - 2;
            break;

        case WLAN_BAND_WIDTH_80MINUSPLUS:
            pauc_buffer[2] = 1;
            pauc_buffer[3] = uc_channel + 2;
            break;

        case WLAN_BAND_WIDTH_80MINUSMINUS:
            pauc_buffer[2] = 1;
            pauc_buffer[3] = uc_channel - 6;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{mac_set_11ac_wideband_ie::invalid bandwidth[%d].}", en_bw);

            return OAL_FAIL;
    }

    pauc_buffer[4] = 0; /* reserved. Not support 80M + 80M */

    *puc_output_len = 5;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : mac_ie_proc_chwidth_field
 ��������  : ����Channel Width Field
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
             puc_payload : ָ��Operating Mode Notification IE��ָ��
 �������  :
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  mac_ie_proc_chwidth_field(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user,oal_uint8 uc_chwidth)
{
    wlan_bw_cap_enum_uint8      en_bwcap_vap = 0;        /* vap����������� */
    wlan_bw_cap_enum_uint8      en_bwcap_user = 0;       /* user֮ǰ�Ĵ�����Ϣ */

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_2040, "{mac_ie_proc_opmode_field::pst_mac_user = [%x], pst_opmode_notify = [%x], pst_mac_vap = [%x]!}\r\n",
                       pst_mac_user, pst_mac_vap);
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_bwcap_user = pst_mac_user->en_avail_bandwidth;

    mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_vap);
    en_bwcap_vap = OAL_MIN(en_bwcap_vap, (wlan_bw_cap_enum_uint8)uc_chwidth);
    mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, en_bwcap_vap);

    //l00311403TODO
    if (en_bwcap_user != pst_mac_user->en_avail_bandwidth)
    {
        /* �����㷨���Ӻ��� */
        //������Ҫ���¼���dmac, dmac_alg_cfg_user_spatial_stream_notify(pst_mac_user);
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : mac_config_set_mib
 ��������  : ����VAP mibֵ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  mac_config_set_mib(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_set_mib_stru   *pst_set_mib;
    oal_uint32              ul_ret = OAL_SUCC;

    pst_set_mib = (mac_cfg_set_mib_stru *)puc_param;

    switch(pst_set_mib->ul_mib_idx)
    {
        case WLAN_MIB_INDEX_LSIG_TXOP_PROTECTION_OPTION_IMPLEMENTED:
            pst_mac_vap->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11LsigTxopProtectionOptionImplemented = (oal_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_HT_GREENFIELD_OPTION_IMPLEMENTED:
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11HTGreenfieldOptionImplemented = (oal_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_SPEC_MGMT_IMPLEMENT:
            pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementImplemented = (oal_bool_enum_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_FORTY_MHZ_OPERN_IMPLEMENT:
            mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, (oal_bool_enum_uint8)(pst_set_mib->ul_mib_value));
            break;

        case WLAN_MIB_INDEX_2040_COEXT_MGMT_SUPPORT:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot112040BSSCoexistenceManagementSupport = (oal_bool_enum_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_FORTY_MHZ_INTOL:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11FortyMHzIntolerant = (oal_bool_enum_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_VHT_CHAN_WIDTH_OPTION_IMPLEMENT:
            pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.uc_dot11VHTChannelWidthOptionImplemented = (oal_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_MINIMUM_MPDU_STARTING_SPACING:
            pst_mac_vap->pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11MinimumMPDUStartSpacing = (oal_uint8)(pst_set_mib->ul_mib_value);
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_TRIGGER_INTERVAL:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthTriggerScanInterval =
                pst_set_mib->ul_mib_value;
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_TRANSITION_DELAY_FACTOR:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthChannelTransitionDelayFactor =
                pst_set_mib->ul_mib_value;
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_PASSIVE_DWELL:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveDwell =
                pst_set_mib->ul_mib_value;
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_ACTIVE_DWELL:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveDwell =
                pst_set_mib->ul_mib_value;
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_PASSIVE_TOTAL_PER_CHANNEL:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveTotalPerChannel =
                pst_set_mib->ul_mib_value;
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_ACTIVE_TOTAL_PER_CHANNEL:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveTotalPerChannel =
                pst_set_mib->ul_mib_value;
            break;

        case WLAN_MIB_INDEX_OBSSSCAN_ACTIVITY_THRESHOLD:
            pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActivityThreshold =
                pst_set_mib->ul_mib_value;
            break;

        default :
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_set_mib::invalid ul_mib_idx[%d].}", pst_set_mib->ul_mib_idx);
            break;
    }

    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : mac_ie_proc_sec_chan_offset_2040
 ��������  : ֻ���HT Operation IE�е�Secondary Channel Offset(SCO)���д���
 �������  : pst_mac_vap       : MAC VAP�ṹ��ָ��
             en_sec_chan_offset: HT Operation IE�еĴ��ŵ�ƫ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ��    ע  : �˺�����HT Operation IE�е�SCO��STA�����SCO���бȽϣ�
             �����һ�£�����Ҫ����AP��SCO�������������е���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  mac_ie_proc_sec_chan_offset_2040(mac_vap_stru *pst_mac_vap, mac_sec_ch_off_enum_uint8 en_sec_chan_offset)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{mac_ie_proc_sec_chan_offset_2040::pst_mac_vap null.}");
        return MAC_NO_CHANGE;
    }

    /* ���ж��Ƿ�֧��HTģʽ,�Լ�40M,��֧������������� */
    if ((OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap)))
    {
        return MAC_NO_CHANGE;
    }

    /* HT Operation IE�е�"���ŵ�ƫ����"�뵱ǰSTA��"����ģʽ"���� */
    if (en_sec_chan_offset != mac_get_sco_from_bandwidth(pst_mac_vap->st_channel.en_bandwidth))
    {
        pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;

        /* ���´���ģʽ */
        if (MAC_SCA == en_sec_chan_offset)
        {
            pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40PLUS;
        }
        else if (MAC_SCB == en_sec_chan_offset)
        {
            pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40MINUS;
        }

        /* ��Ҫ����Ӳ�����л����� */
        return MAC_BW_CHANGE;
    }

    return MAC_NO_CHANGE;
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_ht_opern_ie
 ��������  : ����HT Operation IE
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ�룬ָ��STA
             puc_payload : ָ��HT Operation IE��ָ��
             pst_mac_user: MAC VAP�ṹ��ָ�룬ָ��AP
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_proc_ht_opern_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, mac_user_stru *pst_mac_user)
{
    mac_ht_opern_stru       *pst_ht_opern;
    mac_user_ht_hdl_stru     st_ht_hdl;
/* #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST */
    wlan_bw_cap_enum_uint8   en_bwcap_vap;
    oal_uint32               ul_change = MAC_NO_CHANGE;
/* #endif */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_mac_user)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_proc_ht_opern_ie::param null.}");
        return ul_change;
    }

    /* ����У�飬�˴����õ�ǰ6�ֽڣ�����Basic MCS Setδ�漰 */
    if (puc_payload[1] < 6)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_proc_ht_opern_ie::invalid ht opern ie len[%d].}", puc_payload[1]);
        return ul_change;
    }

    mac_user_get_ht_hdl(pst_mac_user, &st_ht_hdl);

    /************************ HT Operation Element *************************************
      ----------------------------------------------------------------------
      |EID |Length |PrimaryChannel |HT Operation Information |Basic MCS Set|
      ----------------------------------------------------------------------
      |1   |1      |1              |5                        |16           |
      ----------------------------------------------------------------------
    ***************************************************************************/

    /************************ HT Information Field ****************************
     |--------------------------------------------------------------------|
     | Primary | Seconday  | STA Ch | RIFS |           reserved           |
     | Channel | Ch Offset | Width  | Mode |                              |
     |--------------------------------------------------------------------|
     |    1    | B0     B1 |   B2   |  B3  |    B4                     B7 |
     |--------------------------------------------------------------------|

     |----------------------------------------------------------------|
     |     HT     | Non-GF STAs | resv      | OBSS Non-HT  | Reserved |
     | Protection |   Present   |           | STAs Present |          |
     |----------------------------------------------------------------|
     | B0     B1  |     B2      |    B3     |     B4       | B5   B15 |
     |----------------------------------------------------------------|

     |-------------------------------------------------------------|
     | Reserved |  Dual  |  Dual CTS  | Seconday | LSIG TXOP Protn |
     |          | Beacon | Protection |  Beacon  | Full Support    |
     |-------------------------------------------------------------|
     | B0    B5 |   B6   |     B7     |     B8   |       B9        |
     |-------------------------------------------------------------|

     |---------------------------------------|
     |  PCO   |  PCO  | Reserved | Basic MCS |
     | Active | Phase |          |    Set    |
     |---------------------------------------|
     |  B10   |  B11  | B12  B15 |    16     |
     |---------------------------------------|
    **************************************************************************/

    pst_ht_opern  = (mac_ht_opern_stru *)(&puc_payload[MAC_IE_HDR_LEN]);

/* #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST */
    /* ��ȡHT Operation IE�е�"STA Channel Width" */
    mac_user_set_bandwidth_info(pst_mac_user, pst_ht_opern->bit_sta_chan_width, pst_mac_user->en_cur_bandwidth);

    /* ��ȡHT Operation IE�е�"Secondary Channel Offset" */
    st_ht_hdl.bit_secondary_chan_offset = pst_ht_opern->bit_secondary_chan_offset;

    /* Ϊ�˷�ֹ5G���û�����20M��������80M���ݵ��������5G����¸ñ������л� */
    if ((0 == pst_mac_user->en_avail_bandwidth) && (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band))
    {
        st_ht_hdl.bit_secondary_chan_offset = MAC_SCN;
    }

    ul_change = mac_ie_proc_sec_chan_offset_2040(pst_mac_vap, pst_ht_opern->bit_secondary_chan_offset);

    /* �û���VAP��������ȡ���� */
    mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_vap);
    //en_bwcap_vap = OAL_MIN(pst_mac_user->en_bandwidth_cap, en_bwcap_vap);  //ע����ԭ��:��������20M,��ֵΪ20m,���ֵһֱ����,����ap����40M,��������user �� avail��ֻ��20m
    en_bwcap_vap = OAL_MIN(pst_mac_user->en_avail_bandwidth, en_bwcap_vap);
    mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, en_bwcap_vap);

/* #endif *//* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

    /* ������� */
    st_ht_hdl.bit_rifs_mode                         = pst_ht_opern->bit_rifs_mode;/*������������дʱ����Ҫ��ֵ*/
    st_ht_hdl.bit_HT_protection                     = pst_ht_opern->bit_HT_protection;
    st_ht_hdl.bit_nongf_sta_present                 = pst_ht_opern->bit_nongf_sta_present;
    st_ht_hdl.bit_obss_nonht_sta_present            = pst_ht_opern->bit_obss_nonht_sta_present;
    st_ht_hdl.bit_lsig_txop_protection_full_support = pst_ht_opern->bit_lsig_txop_protection_full_support;

    mac_user_set_ht_hdl(pst_mac_user, &st_ht_hdl);

    return ul_change;
}
/*****************************************************************************
 �� �� ��  : mac_ie_proc_obss_ie
 ��������  : ����Overlapping BSS Scan Parameters IE��������STA��ӦMIB��
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             puc_payload: ָ��Overlapping BSS Scan Parameters IE��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : OAL_SUCC������������
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_ie_proc_obss_scan_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload)
{
    oal_uint16 us_trigger_scan_interval;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{mac_ie_proc_obss_scan_ie::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /********************Overlapping BSS Scan Parameters element******************
     |ElementID |Length |OBSS    |OBSS   |BSS Channel   |OBSS Scan  |OBSS Scan   |
     |          |       |Scan    |Scan   |Width Trigger |Passive    |Active Total|
     |          |       |Passive |Active |Scan Interval |Total Per  |Per         |
     |          |       |Dwell   |Dwell  |              |Channel    |Channel     |
     ----------------------------------------------------------------------------
     |1         |1      |2       |2      |2             |2          |2           |
     ----------------------------------------------------------------------------
     |BSS Width   |OBSS Scan|
     |Channel     |Activity |
     |Transition  |Threshold|
     |Delay Factor|         |
     ------------------------
     |2           |2        |
    ***************************************************************************/
    if ( puc_payload[1] < MAC_OBSS_SCAN_IE_LEN)
    {
        return OAL_FAIL;
    }

    us_trigger_scan_interval = OAL_MAKE_WORD16(puc_payload[6], puc_payload[7]);
    if (0 == us_trigger_scan_interval)
    {
        mac_vap_set_peer_obss_scan(pst_mac_vap, OAL_FALSE);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    mac_mib_set_OBSSScanPassiveDwell(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[2], puc_payload[3]));
    mac_mib_set_OBSSScanActiveDwell(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[4], puc_payload[5]));
    /* obssɨ��������С300��,���600S, ��ʼ��Ĭ��Ϊ300�� */
    mac_mib_set_BSSWidthTriggerScanInterval(pst_mac_vap, OAL_MIN(OAL_MAX(us_trigger_scan_interval, 300), 600));
    mac_mib_set_OBSSScanPassiveTotalPerChannel(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[8], puc_payload[9]));
    mac_mib_set_OBSSScanActiveTotalPerChannel(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[10], puc_payload[11]));
    mac_mib_set_BSSWidthChannelTransitionDelayFactor(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[12], puc_payload[13]));
    mac_mib_set_OBSSScanActivityThreshold(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[14], puc_payload[15]));
    mac_vap_set_peer_obss_scan(pst_mac_vap, OAL_TRUE);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_ie_proc_vht_opern_ie
 ��������  : ����VHT Operation IE
 �������  : pst_mac_vap : MAC VAP�ṹ��ָ�룬ָ��STA
             puc_payload : ָ��VHT Operation IE��ָ��
             pst_mac_user: MAC USER�ṹ��ָ�룬ָ��AP
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_ie_proc_vht_opern_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, mac_user_stru *pst_mac_user)
{
    mac_vht_hdl_stru                     st_vht_hdl;
    mac_vht_hdl_stru                    *pst_vht_hdl = &st_vht_hdl;

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    wlan_channel_bandwidth_enum_uint8    en_bandwidth;
    wlan_bw_cap_enum_uint8               en_bwcap_vap;
#endif

    oal_uint16                           us_basic_mcs_set_all_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_ie_proc_vht_opern_ie::param null.}");

        return MAC_NO_CHANGE;
    }

    /* ����У�� */
    if (puc_payload[1] < MAC_VHT_OPERN_LEN)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_ie_proc_vht_opern_ie::invalid vht opern len[%d].}", puc_payload[1]);
        return MAC_NO_CHANGE;
    }

    mac_user_get_vht_hdl(pst_mac_user, pst_vht_hdl);

    /* ���� "VHT Operation Information" */
    pst_vht_hdl->uc_channel_width            = puc_payload[MAC_IE_HDR_LEN];
    pst_vht_hdl->uc_channel_center_freq_seg0 = puc_payload[MAC_IE_HDR_LEN + 1];
    pst_vht_hdl->uc_channel_center_freq_seg1 = puc_payload[MAC_IE_HDR_LEN + 2];

    /* 0 -- 20/40M, 1 -- 80M, 2 -- 160M, 3--80M+80M */
    if (pst_vht_hdl->uc_channel_width > 3)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_ie_proc_vht_opern_ie::invalid channel width[%d], use 20M chn width.}", pst_vht_hdl->uc_channel_width);
        pst_vht_hdl->uc_channel_width = 0;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* ֻ���л���>=80MHz�Ž��д�����80MHz+�л������͵ȼ��Ĵ����������账��(�ڽ���HT Operation IE�д���) */
    if (pst_vht_hdl->uc_channel_width >= 1)
    {
        en_bandwidth = mac_get_bandwith_from_center_freq_seg0(pst_mac_vap->st_channel.uc_chan_number, pst_vht_hdl->uc_channel_center_freq_seg0);

        /* VHT Operation IE�������"����ģʽ"�뵱ǰSTA��"����ģʽ"���� */
        if (en_bandwidth != pst_mac_vap->st_channel.en_bandwidth)
        {
            if (WLAN_MIB_VHT_SUPP_WIDTH_80 == mac_mib_get_VHTChannelWidthOptionImplemented(pst_mac_vap))
            {
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
                /* ���´���ģʽ */
                pst_mac_vap->st_channel.en_bandwidth = en_bandwidth;

                /* ��Ҫ����Ӳ�����л����� */
                return MAC_BW_CHANGE;
#endif

            }
        }

        /* DTS2014121506679:����û�����80M������Ϣ */
        /* �û���VAP��������ȡ���� */
        en_bwcap_vap = (pst_vht_hdl->uc_channel_width == 1) ? WLAN_BW_CAP_80M : WLAN_BW_CAP_160M;
        mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, pst_mac_user->en_cur_bandwidth);

        mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_vap);

        //en_bwcap_vap = OAL_MIN(pst_mac_user->en_bandwidth_cap, en_bwcap_vap);
        en_bwcap_vap = OAL_MIN(pst_mac_user->en_avail_bandwidth, en_bwcap_vap);
        mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, en_bwcap_vap);
    }
#endif

    /* ���� "VHT Basic MCS Set field" */
    us_basic_mcs_set_all_user = OAL_MAKE_WORD16(puc_payload[MAC_IE_HDR_LEN + 3], puc_payload[MAC_IE_HDR_LEN + 4]);
    pst_vht_hdl->us_basic_mcs_set = us_basic_mcs_set_all_user;

    mac_user_set_vht_hdl(pst_mac_user, pst_vht_hdl);

    return MAC_NO_CHANGE;
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 �� �� ��  : mac_ie_check_proc_opmode_param
 ��������  : ���Operating Mode�ֶβ����Ƿ����
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
             puc_payload : ָ��Operating Mode Notification IE��ָ��
 �������  :
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  mac_ie_check_proc_opmode_param(mac_user_stru *pst_mac_user, mac_opmode_notify_stru *pst_opmode_notify)
{
    /* USER���޶������ռ������������������ */
    if ((pst_mac_user->en_bandwidth_cap < pst_opmode_notify->bit_channel_width)
       ||(pst_mac_user->uc_num_spatial_stream < pst_opmode_notify->bit_rx_nss))
    {
        OAM_WARNING_LOG4(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{hmac_ie_check_proc_opmode_param::user cap over limit! en_bandwidth_cap = [%d], opmode bandwidth = [%d],user spatial stream = [%d], opmode rx nss = [%d]!}\r\n",
                         pst_mac_user->en_bandwidth_cap,
                         pst_opmode_notify->bit_channel_width,
                         pst_mac_user->uc_num_spatial_stream,
                         pst_opmode_notify->bit_rx_nss);
        return OAL_FAIL;
    }

    /* Nss TypeֵΪ1�����ʾbeamforming Rx Nss���ܳ���������ֵ */
    if (1 == pst_opmode_notify->bit_rx_nss_type)
    {
        if (pst_mac_user->st_vht_hdl.bit_num_bf_ant_supported < pst_opmode_notify->bit_rx_nss)
        {
            OAM_WARNING_LOG2(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{hmac_ie_check_proc_opmode_param::bit_rx_nss is over limit!bit_num_bf_ant_supported = [%d],bit_rx_nss = [%d]!}\r\n",
                             pst_mac_user->st_vht_hdl.bit_num_bf_ant_supported,
                             pst_opmode_notify->bit_rx_nss);
            return OAL_FAIL;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_ie_proc_opmode_field
 ��������  : ����Operating Mode�ֶ�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
             puc_payload : ָ��Operating Mode Notification IE��ָ��
 �������  :
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  mac_ie_proc_opmode_field(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, mac_opmode_notify_stru *pst_opmode_notify)
{
    wlan_bw_cap_enum_uint8      en_bwcap_vap = 0;        /* vap����������� */
    wlan_bw_cap_enum_uint8      en_avail_bw  = 0;        /* vap����������� */

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == pst_opmode_notify)|| (OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{mac_ie_proc_opmode_field::pst_mac_user = [%x], pst_opmode_notify = [%x], pst_mac_vap = [%x]!}\r\n",
                       pst_mac_user, pst_opmode_notify, pst_mac_vap);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FAIL == mac_ie_check_proc_opmode_param(pst_mac_user, pst_opmode_notify))
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::hmac_ie_check_proc_opmode_param return fail!}\r\n");
        return OAL_FAIL;
    }

    /* �ж�Rx Nss Type�Ƿ�Ϊbeamformingģʽ */
    if (1 == pst_opmode_notify->bit_rx_nss_type)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::pst_opmode_notify->bit_rx_nss_type == 1!}\r\n");

        /* �ж�Rx Nss�Ƿ���user֮ǰʹ��Rx Nss��ͬ */
        if (pst_opmode_notify->bit_rx_nss != pst_mac_user->uc_avail_bf_num_spatial_stream)
        {
            mac_user_avail_bf_num_spatial_stream(pst_mac_user, pst_opmode_notify->bit_rx_nss);

        }

        return OAL_SUCC;
    }

    /* �ж�Rx Nss�Ƿ���user֮ǰʹ��Rx Nss��ͬ */
    if (pst_opmode_notify->bit_rx_nss != pst_mac_user->uc_avail_num_spatial_stream)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::pst_opmode_notify->bit_rx_nss = [%x], pst_mac_user->uc_avail_num_spatial_stream = [%x]!}\r\n",
                      pst_opmode_notify->bit_rx_nss, pst_mac_user->uc_avail_num_spatial_stream);
        /* ��AP������ȡ���� */
        mac_user_set_avail_num_spatial_stream(pst_mac_user, OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_opmode_notify->bit_rx_nss));

        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::change rss. pst_mac_vap->en_vap_rx_nss = [%x], pst_mac_user->uc_avail_num_spatial_stream = [%x]!}\r\n",
                      pst_mac_vap->en_vap_rx_nss, pst_mac_user->uc_avail_num_spatial_stream);

    }

    /* �ж�channel_width�Ƿ���user֮ǰʹ��channel_width��ͬ */
    if (pst_opmode_notify->bit_channel_width != pst_mac_user->en_avail_bandwidth)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::pst_opmode_notify->bit_channel_width = [%x], pst_mac_user->en_avail_bandwidth = [%x]!}\r\n",
                      pst_opmode_notify->bit_channel_width, pst_mac_user->en_avail_bandwidth);

        /* ��ȡvap�����������û����������Ľ��� */
        mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_vap);

        en_avail_bw = OAL_MIN(en_bwcap_vap, pst_opmode_notify->bit_channel_width);
        mac_user_set_bandwidth_info(pst_mac_user, en_avail_bw, en_avail_bw);

        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::change bandwidth. en_bwcap_vap = [%x], pst_mac_user->en_avail_bandwidth = [%x]!}\r\n",
                      en_bwcap_vap, pst_mac_user->en_avail_bandwidth);
    }


    return OAL_SUCC;
}
#endif

/*lint -e19*/
oal_module_symbol(mac_ie_proc_sm_power_save_field);
oal_module_symbol(mac_ie_proc_ht_green_field);
oal_module_symbol(mac_ie_get_chan_num);
oal_module_symbol(mac_ie_proc_ht_supported_channel_width);
oal_module_symbol(mac_ie_proc_lsig_txop_protection_support);
oal_module_symbol(mac_ie_proc_ext_cap_ie);
#if 0
oal_module_symbol(mac_set_channel_switch_wrapper_ie);
#endif
oal_module_symbol(mac_set_second_channel_offset_ie);
oal_module_symbol(mac_set_11ac_wideband_ie);
oal_module_symbol(mac_config_set_mib);
oal_module_symbol(mac_ie_proc_ht_sta);
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
oal_module_symbol(mac_ie_proc_chwidth_field);
#endif
oal_module_symbol(mac_ie_get_vht_rx_mcs_map);
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
oal_module_symbol(mac_ie_proc_opmode_field);
#endif
oal_module_symbol(mac_ie_proc_obss_scan_ie);
oal_module_symbol(mac_ie_proc_sec_chan_offset_2040);
oal_module_symbol(mac_proc_ht_opern_ie);
oal_module_symbol(mac_ie_proc_vht_opern_ie);


/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

