/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_p2p.c
  �� �� ��   : ����
  ��    ��   : duankaiyong
  ��������   : 2014��11��26��
  ����޸�   :
  ��������   : P2P ������Դ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��26��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_P2P


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_util.h"
#include "mac_resource.h"
#include "mac_frame.h"
#include "dmac_vap.h"
#include "dmac_p2p.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_config.h"
#include "hal_ext_if.h"
#include "dmac_psm_ap.h"

//#include "mac_pm.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "pm_extern.h"
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#include "dmac_psm_sta.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_P2P_C

/*****************************************************************************
  2 ��̬��������
*****************************************************************************/


/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/


/* ����Ƿ�ֻ����11B ���ʣ�11b���ʼ�:0x82 = 1Mbps, 0x84 = 2Mbps, 0x8B = 5.5Mbps, 0x96 = 11Mbps */
/*****************************************************************************
 �� �� ��  : dmac_p2p_is_11b_rate
 ��������  : ����Ƿ�Ϊ11b ����
 �������  : oal_uint8 uc_rate
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_is_11b_rate(oal_uint8 uc_rate)
{
    uc_rate &= (oal_uint8)(~BIT7);
    if ((2 == uc_rate)
        || (4 == uc_rate)
        || (11 == uc_rate)
        || (22 == uc_rate))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : mac_is_p2p_action_frame
 ��������  : ����P2P action֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��7��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_is_p2p_action_frame(oal_uint8 *puc_data)
{
    oal_bool_enum_uint8       ul_ret;

    /* ��ȡ֡��ָ�� */

    /* Category */
    switch (puc_data[MAC_ACTION_OFFSET_CATEGORY])
    {

        case MAC_ACTION_CATEGORY_PUBLIC:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_PUB_VENDOR_SPECIFIC:
                {
                    ul_ret =  OAL_TRUE;
                }
                break;
                default:
                {
                    ul_ret =  OAL_FALSE;
                }
                break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_VENDOR:
        {
            ul_ret =  OAL_TRUE;
        }
        break;

        default:
        {
            ul_ret =  OAL_FALSE;
        }
        break;
    }
    return ul_ret;

}

/*****************************************************************************
 �� �� ��  : dmac_is_p2p_pd_disc_req_frame
 ��������  : ����P2P action֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_is_p2p_pd_disc_req_frame(OAL_CONST oal_uint8 *puc_data)
{
    if((MAC_ACTION_CATEGORY_PUBLIC == puc_data[MAC_ACTION_OFFSET_CATEGORY])&&
        (WFA_OUI_BYTE1== puc_data[P2P_PUB_ACT_OUI_OFF1])&&
        (WFA_OUI_BYTE2== puc_data[P2P_PUB_ACT_OUI_OFF2])&&
        (WFA_OUI_BYTE3== puc_data[P2P_PUB_ACT_OUI_OFF3])&&
        (WFA_P2P_v1_0== puc_data[P2P_PUB_ACT_OUI_TYPE_OFF])&&
        (P2P_PAF_PD_REQ== puc_data[P2P_PUB_ACT_OUI_SUBTYPE_OFF]))
        return OAL_TRUE;
    else
        return OAL_FALSE;

}

/*****************************************************************************
 �� �� ��  : dmac_p2p_is_only_11b_rates
 ��������  : ����Ƿ�ֻ֧��11b ����
 �������  : oal_uint8 *puc_frame_body
             oal_uint16 us_frame_len
 �������  : ��
 �� �� ֵ  : oal_uint32 OAL_TRUE  -  ��֧��11B���ʣ�
                        OAL_FALSE -  ����֧��11B���ʣ�����֧��11G����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_p2p_is_only_11b_rates(oal_uint8 *puc_frame_body, oal_uint16 us_frame_len)
{
    oal_uint8      *puc_ie;
    oal_uint8       uc_ie_len;
    oal_uint8       uc_rate;
    oal_uint32      ul_loop;
    oal_uint32      ul_ie_index;
    oal_uint8      *puc_ie_array[2];

    /* ����Ƿ�ֻ����11B ���ʼ���11b���ʼ�:0x82 = 1Mbps, 0x84 = 2Mbps, 0x8B = 5.5Mbps, 0x96 = 11Mbps */

    puc_ie_array[0] = mac_find_ie(MAC_EID_RATES, puc_frame_body, us_frame_len);
    puc_ie_array[1] = mac_find_ie(MAC_EID_XRATES, puc_frame_body, us_frame_len);
    for (ul_ie_index = 0; ul_ie_index < OAL_ARRAY_SIZE(puc_ie_array); ul_ie_index++)
    {
        if (OAL_PTR_NULL == puc_ie_array[ul_ie_index])
        {
            continue;
        }

        puc_ie = puc_ie_array[ul_ie_index];
        uc_ie_len = *(puc_ie + 1);

        for (ul_loop = 0; ul_loop < uc_ie_len; ul_loop++)
        {
            uc_rate = *(puc_ie + MAC_IE_HDR_LEN + ul_loop);
            if (OAL_FALSE == dmac_is_11b_rate(uc_rate))
            {
                return OAL_FALSE;
            }
        }
    }
    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : dmac_is_p2p_presence_req_frame
 ��������  : �Ƿ���P2P presence reqest action֡
 �������  : oal_uint8 *puc_data
 �������  : ��
 �� �� ֵ  : OAL_TRUE ��P2P presence reqest action֡
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_is_p2p_presence_req_frame(oal_uint8 *puc_data)
{
    if((MAC_ACTION_CATEGORY_VENDOR == puc_data[MAC_ACTION_OFFSET_CATEGORY])&&
        (P2P_PRESENCE_REQ == puc_data[P2P_GEN_ACT_OUI_SUBTYPE_OFF]))
        return OAL_TRUE;
    else
        return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_p2p_listen_filter_frame
 ��������  : ����յ���probe request�ǲ���Ҫ
 �������  : puc_frame_body:  probe req ֡��

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_p2p_listen_filter_frame(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_frame_body, oal_uint16 us_frame_len)
{
    oal_uint8                   *puc_p2p_ie     = OAL_PTR_NULL;

    /* ������յ���probe req ֻ֡����11b ���ʣ� �򷵻� */
    if (OAL_TRUE == dmac_p2p_is_only_11b_rates(puc_frame_body, us_frame_len))
    {
        return OAL_FAIL;
    }

    /* ������յ���probe req ֡������SSID "DIRECT-" �� �򷵻� */
    if (!IS_P2P_WILDCARD_SSID(&puc_frame_body[MAC_IE_HDR_LEN], puc_frame_body[1]))
    {
        return OAL_FAIL;
    }

    /* ������յ���probe req ֡������P2P_IE�� �򷵻� */
    //puc_p2p_ie = mac_get_p2p_ie(puc_frame_body, us_frame_len, 0);
    puc_p2p_ie = mac_find_vendor_ie(MAC_WLAN_OUI_WFA, MAC_WLAN_OUI_TYPE_WFA_P2P, puc_frame_body, us_frame_len);
    if (puc_p2p_ie == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_p2p_listen_filter_vap
 ��������  : ���vap״̬�Ƿ�Ҫ����probe request
 �������  : pst_dmac_vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : xiaoyuren 00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_p2p_listen_filter_vap(dmac_vap_stru *pst_dmac_vap)
{

    /* ֻ��P2P CL��P2P DEV����Listen״̬�ҵ�ǰVAP�ŵ���P2P0 Listen Channelһ�µ�����²ſ��Իظ�Probe resp֡ */
    if ((IS_P2P_CL((&pst_dmac_vap->st_vap_base_info)) || IS_P2P_DEV((&pst_dmac_vap->st_vap_base_info)))
         && dmac_vap_is_in_p2p_listen(&(pst_dmac_vap->st_vap_base_info))
         && (pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number == pst_dmac_vap->st_vap_base_info.uc_p2p_listen_channel))
    {
        return OAL_SUCC;
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : dmac_is_p2p_go_neg_req_frame
 ��������  : �Ƿ���P2P GO negotiation request action֡
 �������  : oal_uint8 *puc_data
 �������  : ��
 �� �� ֵ  : OAL_TRUE ��P2P GO negotiation request action֡
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_is_p2p_go_neg_req_frame(OAL_CONST oal_uint8* puc_data)
{
    if((MAC_ACTION_CATEGORY_PUBLIC == puc_data[MAC_ACTION_OFFSET_CATEGORY])&&
        (WFA_OUI_BYTE1== puc_data[P2P_PUB_ACT_OUI_OFF1])&&
        (WFA_OUI_BYTE2== puc_data[P2P_PUB_ACT_OUI_OFF2])&&
        (WFA_OUI_BYTE3== puc_data[P2P_PUB_ACT_OUI_OFF3])&&
        (WFA_P2P_v1_0== puc_data[P2P_PUB_ACT_OUI_TYPE_OFF])&&
        (P2P_PAF_GON_REQ== puc_data[P2P_PUB_ACT_OUI_SUBTYPE_OFF]))
        return OAL_TRUE;
    else
        return OAL_FALSE;
}


/*****************************************************************************
 �� �� ��  : dmac_p2p_listen_rx_mgmt
 ��������  : P2P �豸���յ�����֡����
 �������  : dmac_vap_stru   *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8    OAL_TRUE:�����ϱ�HMAC ����
                                    OAL_FALSE:�����ϱ�HMAC ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 dmac_p2p_listen_rx_mgmt(dmac_vap_stru   *pst_dmac_vap,
                                  oal_netbuf_stru *pst_netbuf)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    mac_device_stru            *pst_mac_device;
    oal_uint8                  *puc_frame_body;
    oal_uint16                  us_frame_len;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_netbuf)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_listen_rx_mgmt::param null.}");
        return OAL_FALSE;
    }

    pst_mac_device  = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{dmac_p2p_listen_rx_mgmt::pst_mac_device null.}");
        return OAL_FALSE;
    }

    /* ��ȡ֡��Ϣ */
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    puc_frame_body = OAL_NETBUF_PAYLOAD(pst_netbuf);
    us_frame_len   = (oal_uint16)oal_netbuf_get_len(pst_netbuf);

    if ((WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type) &&(OAL_TRUE == mac_is_p2p_action_frame(puc_frame_body)))
    {
        /*�ж��Ƿ���presence request action frame*/
        if(OAL_TRUE == dmac_is_p2p_presence_req_frame(puc_frame_body))
        {
            dmac_process_p2p_presence_req(pst_dmac_vap,pst_netbuf);
            return OAL_FALSE;
        }
        else
        {
            /* begin:DTS2015041705894 ���յ�p2p GO negotiation request ���������ʱ��*/
            /* begin:DTS2015071707751 ���յ�provision discovery request֡���ӳ�listenʱ�䣬����action����δ��ɼ����ŵ� */
            if(OAL_TRUE == dmac_is_p2p_go_neg_req_frame(puc_frame_body) || OAL_TRUE == dmac_is_p2p_pd_disc_req_frame(puc_frame_body))
            {
                /* �ӳ�����ʱ�䣬���ڼ�������ɨ��ӿڣ����ӳ�ɨ�趨ʱ�� */
                if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_enabled)
                {
                    FRW_TIMER_STOP_TIMER(&(pst_mac_device->st_scan_timer));
                    FRW_TIMER_RESTART_TIMER(&(pst_mac_device->st_scan_timer),
                                              (pst_mac_device->st_scan_params.us_scan_time), OAL_FALSE);
                }
            }
            /* end:DTS2015041705894 ���յ�p2p GO negotiation request ���������ʱ��*/

            /* �����ACTION ֡�����ϱ� */
            return OAL_TRUE;
        }
    }
    else if (WLAN_PROBE_REQ== pst_frame_hdr->st_frame_control.bit_sub_type)
    {
        if (OAL_SUCC != dmac_p2p_listen_filter_vap(pst_dmac_vap))
        {
            return OAL_FALSE;
        }
        if (OAL_SUCC != dmac_p2p_listen_filter_frame(pst_dmac_vap, puc_frame_body, us_frame_len))
        {
            return OAL_FALSE;
        }

        /* ���յ�probe req ֡������probe response ֡ */
        dmac_ap_up_rx_probe_req(pst_dmac_vap, pst_netbuf);
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : mac_set_p2p0_ssid_ie
 ��������  : ����p2p0��BSSID IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_set_p2p0_ssid_ie(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len, oal_uint16 us_frm_type)
{
    oal_uint8     uc_ssid_len;
    mac_vap_stru *pst_mac_vap = (mac_vap_stru *)pst_vap;

    if (IS_LEGACY_VAP(pst_mac_vap))
    {
        return;
    }

    /***************************************************************************
                    ----------------------------
                    |Element ID | Length | SSID|
                    ----------------------------
           Octets:  |1          | 1      | 0~32|
                    ----------------------------
    ***************************************************************************/
    /***************************************************************************
      A SSID  field  of length 0 is  used  within Probe
      Request management frames to indicate the wildcard SSID.
    ***************************************************************************/
    /* ֻ��beacon������ssid */
    if((pst_mac_vap->st_cap_flag.bit_hide_ssid) && (WLAN_FC0_SUBTYPE_BEACON == us_frm_type))
    {
        /* ssid ie */
        *puc_buffer = MAC_EID_SSID;
        /* ssid len */
        *(puc_buffer + 1) = 0;
        *puc_ie_len = MAC_IE_HDR_LEN;
        return;
    }

    *puc_buffer = MAC_EID_SSID;
    uc_ssid_len = (oal_uint8)OAL_STRLEN((oal_int8 *)DMAC_P2P_WILDCARD_SSID );   /* ������'\0'*/

    *(puc_buffer + 1) = uc_ssid_len;

    oal_memcopy(puc_buffer + MAC_IE_HDR_LEN, DMAC_P2P_WILDCARD_SSID , uc_ssid_len);

    *puc_ie_len = uc_ssid_len + MAC_IE_HDR_LEN;

}

//oal_module_symbol();

/*****************************************************************************
 �� �� ��  : mac_set_p2p_noa
 ��������  : ���p2p noa��Ϣ
 �������  : pst_vap: ָ��vap
             puc_buffer: ָ��buffer
 �������  : puc_ie_len: element�ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��22��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_set_p2p_noa(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    oal_uint8       uc_index;
    mac_vap_stru    *pst_mac_vap = (mac_vap_stru *)pst_vap;
    dmac_vap_stru   *pst_dmac_vap;
    oal_uint8       CTWindow = 0;
    oal_uint32      ul_start_time;
    oal_uint32      ul_duration;
    oal_uint32      ul_interval;
    oal_uint16      us_attr_len;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    /* p2p noa Element                                                       */
    /* --------------------------------------------------------------------- */
    /* |1          |1          |3     | 1        | 1            | 2        | */
    /* --------------------------------------------------------------------- */
    /* |Tag number |Tag length |OUI   | OUI Type | Attribute ID | Length   | */
    /* --------------------------------------------------------------------- */
    /* |  1    |       1        | 13                                       | */
    /* --------------------------------------------------------------------- */
    /* | Index | CTWindow/OppPS |Notice of Absence Descriptor              | */
    /* --------------------------------------------------------------------- */

    /* Tag number */
    puc_buffer[0] = MAC_EID_P2P;

    /* Tag length */
    puc_buffer[1] = P2P_OUI_LEN+ P2P_ATTR_HDR_LEN + (P2P_NOA_DESC_NUM*13) + 2;
    uc_index = MAC_IE_HDR_LEN;

    /* OUI */
    oal_memcopy(&puc_buffer[uc_index], g_auc_p2p_oui, MAC_OUI_LEN);
    uc_index += MAC_OUI_LEN;

    /* OUI Type */
    puc_buffer[uc_index++] = MAC_OUITYPE_P2P;

    /* Notice of Absence attribute*/
    /* Attribute ID*/
    puc_buffer[uc_index++] = NOTICE_OF_ABSENCE;

    /* Length*/
    us_attr_len = (P2P_NOA_DESC_NUM*13) + 2;
    puc_buffer[uc_index++] = us_attr_len & 0x00FF;
    puc_buffer[uc_index++] = us_attr_len >> 8;

    /* Index*/
    puc_buffer[uc_index++] = 0;

    /* CTWindow and Opportunity parameters field */
    if(IS_P2P_OPPPS_ENABLED(pst_dmac_vap))
    {
        CTWindow = pst_dmac_vap->st_p2p_ops_param.uc_ct_window;
        CTWindow |= BIT7;
    }
    puc_buffer[uc_index++] = CTWindow;

    if(!IS_P2P_NOA_ENABLED(pst_dmac_vap))
    {
        *puc_ie_len = MAC_IE_HDR_LEN + P2P_OUI_LEN+ P2P_ATTR_HDR_LEN + 2;
        return;
    }
    /* Notice of Absence Descriptor*/
    puc_buffer[uc_index++] = pst_dmac_vap->st_p2p_noa_param.uc_count;

    ul_duration = pst_dmac_vap->st_p2p_noa_param.ul_duration;
    puc_buffer[uc_index++] = ul_duration & 0x000000FF;
    puc_buffer[uc_index++] = (ul_duration >> 8) & 0x000000FF;
    puc_buffer[uc_index++] = (ul_duration >> 16) & 0x000000FF;
    puc_buffer[uc_index++] = (ul_duration >> 24);

    ul_interval = pst_dmac_vap->st_p2p_noa_param.ul_interval;
    puc_buffer[uc_index++] = ul_interval & 0x000000FF;
    puc_buffer[uc_index++] = (ul_interval >> 8) & 0x000000FF;
    puc_buffer[uc_index++] = (ul_interval >> 16) & 0x000000FF;
    puc_buffer[uc_index++] = (ul_interval >> 24);

    ul_start_time = pst_dmac_vap->st_p2p_noa_param.ul_start_time;
    puc_buffer[uc_index++] = ul_start_time & 0x000000FF;
    puc_buffer[uc_index++] = (ul_start_time >> 8) & 0x000000FF;
    puc_buffer[uc_index++] = (ul_start_time >> 16) & 0x000000FF;
    puc_buffer[uc_index++] = (ul_start_time >> 24);

    *puc_ie_len = MAC_IE_HDR_LEN + P2P_OUI_LEN+ P2P_ATTR_HDR_LEN + (P2P_NOA_DESC_NUM*13) + 2;
}

/*****************************************************************************
 �� �� ��  : mac_set_p2p_none_noa
 ��������  : ���p2p noa��Ϣ������NoA description
 �������  : pst_vap: ָ��vap
             puc_buffer: ָ��buffer
 �������  : puc_ie_len: element�ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��22��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_set_p2p_none_noa(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    oal_uint8       uc_index;

    /* p2p noa Element                                                       */
    /* --------------------------------------------------------------------- */
    /* |1          |1          |3     | 1        | 1            | 2        | */
    /* --------------------------------------------------------------------- */
    /* |Tag number |Tag length |OUI   | OUI Type | Attribute ID | Length   | */
    /* --------------------------------------------------------------------- */
    /* |  1    |       1        | 13                                       | */
    /* --------------------------------------------------------------------- */
    /* | Index | CTWindow/OppPS |Notice of Absence Descriptor              | */
    /* --------------------------------------------------------------------- */

    /* Tag number */
    puc_buffer[0] = MAC_EID_P2P;

    /* Tag length */
    puc_buffer[1] = P2P_OUI_LEN+ P2P_ATTR_HDR_LEN + 2;
    uc_index = MAC_IE_HDR_LEN;

    /* OUI */
    oal_memcopy(&puc_buffer[uc_index], g_auc_p2p_oui, MAC_OUI_LEN);
    uc_index += MAC_OUI_LEN;

    /* OUI Type */
    puc_buffer[uc_index++] = MAC_OUITYPE_P2P;

    /* Notice of Absence attribute*/
    /* Attribute ID*/
    puc_buffer[uc_index++] = NOTICE_OF_ABSENCE;

    /* Length*/
    puc_buffer[uc_index++] = 2;
    puc_buffer[uc_index++] = 0;

    /* Index*/
    puc_buffer[uc_index++] = 0;
    /* Set CTWindow and Opportunity parameters field to 0*/
    puc_buffer[uc_index++] = 0;

    *puc_ie_len = MAC_IE_HDR_LEN + P2P_OUI_LEN+ P2P_ATTR_HDR_LEN + 2;
}


/*****************************************************************************
 �� �� ��  : mac_set_p2p_status
 ��������  : ���p2p status��Ϣ
 �������  : pst_vap: ָ��vap
             puc_buffer: ָ��buffer
 �������  : puc_ie_len: element�ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��22��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_set_p2p_status(oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len, P2P_STATUS_CODE_T status)
{
    oal_uint8       uc_index = 0;
    oal_uint16      us_attr_len;

    /* -------------------------------------------*/
    /* p2p Status Attribute                       */
    /* -------------------------------------------*/
    /* | 1            | 2        | 1             |*/
    /* -------------------------------------------*/
    /* |Attribute ID  | Length   | Status Code   |*/
    /* -------------------------------------------*/

    /* Tag number */
    puc_buffer[0] = MAC_EID_P2P;

    /* Tag length */
    puc_buffer[1] = P2P_OUI_LEN+ P2P_ATTR_HDR_LEN + 1;
    uc_index = MAC_IE_HDR_LEN;

    /* OUI */
    oal_memcopy(&puc_buffer[uc_index], g_auc_p2p_oui, MAC_OUI_LEN);
    uc_index += MAC_OUI_LEN;

    /* OUI Type */
    puc_buffer[uc_index++] = MAC_OUITYPE_P2P;

    /* Attribute ID*/
    puc_buffer[uc_index++] = P2P_STATUS;

    /* Length*/
    us_attr_len = 1;
    puc_buffer[uc_index++] = us_attr_len & 0x00FF;
    puc_buffer[uc_index++] = us_attr_len >> 8;

    puc_buffer[uc_index++] = status;

    *puc_ie_len = uc_index;
}
#if 0
/*****************************************************************************
 �� �� ��  : mac_set_p2p_ie_hdr
 ��������  : ���p2p ie header��Ϣ
 �������  : puc_buffer: ָ��buffer
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��16��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_set_p2p_ie_hdr(oal_uint8 *puc_buffer)
{
   puc_buffer[0] = MAC_EID_P2P;
   puc_buffer[1] = P2P_OUI_LEN + P2P_ATTR_HDR_LEN + 1;
   puc_buffer[2] = WFA_OUI_BYTE1;
   puc_buffer[3] = WFA_OUI_BYTE2;
   puc_buffer[4] = WFA_OUI_BYTE3;
   puc_buffer[5] = WFA_P2P_v1_0;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_process_p2p_presence_req
 ��������  : �յ�presence request����
 �������  : pst_dmac_vap: dmac vap
             pst_netbuf: ���յ���net buffer
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��22��
    ��    ��   : x305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_process_p2p_presence_req(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_netbuf_stru            *pst_mgmt_buf;
    oal_uint16                  us_mgmt_len;
    mac_tx_ctl_stru            *pst_tx_ctl;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint8                  *puc_frame_body;
    oal_uint32                  ul_ret;
    oal_uint16                  us_user_idx = 0;

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info)));
    puc_frame_body = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctl->st_rx_info), pst_netbuf);

    /* �������֡�ڴ� */
    pst_mgmt_buf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_mgmt_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{dmac_process_p2p_presence_req::pst_mgmt_buf null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_set_netbuf_prev(pst_mgmt_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_mgmt_buf, OAL_PTR_NULL);

    OAL_MEM_NETBUF_TRACE(pst_mgmt_buf, OAL_TRUE);

    /* ��װpresence request֡ */
    us_mgmt_len = dmac_mgmt_encap_p2p_presence_rsp(pst_dmac_vap, pst_mgmt_buf, pst_frame_hdr->auc_address2, puc_frame_body);
    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{dmac_process_p2p_presence_req::dmac_mgmt_encap_p2p_presence_rsp. length=%d}\r\n",us_mgmt_len);

    /* ���÷��͹���֡�ӿ� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_buf);

    ul_ret = mac_vap_find_user_by_macaddr((&pst_dmac_vap->st_vap_base_info), pst_frame_hdr->auc_address2, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{dmac_process_p2p_presence_req::no user.}");
        oal_netbuf_free(pst_mgmt_buf);

        return ul_ret;
    }
    OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)   = (oal_uint8)us_user_idx;
    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{dmac_process_p2p_presence_req::us_user_idx=%d}\r\n",us_user_idx);
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)      = OAL_FALSE;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_mgmt_buf, us_mgmt_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{dmac_process_p2p_presence_req::dmac_tx_mgmt failed[%d].", ul_ret);
        oal_netbuf_free(pst_mgmt_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_is_p2p_ie
 ��������  : �Ƿ���P2P IE
 �������  : oal_uint8 *puc_data
 �������  : ��
 �� �� ֵ  : OAL_TRUE ��P2P IE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��28��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_is_p2p_ie(oal_uint8 *puc_data)
{
    if((MAC_EID_P2P   == puc_data[0]) &&
       (WFA_OUI_BYTE1 == puc_data[2]) &&
       (WFA_OUI_BYTE2 == puc_data[3]) &&
       (WFA_OUI_BYTE3 == puc_data[4]) &&
       (WFA_P2P_v1_0  == puc_data[5]))
        return OAL_TRUE;
    else
        return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_encap_presence_response
 ��������  : ��װpresence response֡
 �������  : pst_dmac_vap: DMAC vap
             puc_buffer  : probe response֡�ڴ�
             puc_ra      : ���յ�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��23��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  dmac_mgmt_encap_p2p_presence_rsp(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8 *puc_ra, oal_uint8 *puc_data)
{
    oal_uint8        uc_ie_len;
    mac_vap_stru    *pst_mac_vap    = &(pst_dmac_vap->st_vap_base_info);
    oal_uint8       *puc_mac_header = oal_netbuf_header(pst_netbuf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8       *puc_payload_addr        = oal_netbuf_data(pst_netbuf);
#else
    oal_uint8       *puc_payload_addr        = puc_mac_header + MAC_80211_FRAME_LEN;
#endif
    oal_uint8       *puc_payload_addr_origin = puc_payload_addr;
    oal_uint8       uc_index = 0;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    mac_hdr_set_frame_control(puc_mac_header, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* ���õ�ַ1Ϊ����presence request֡��STA */
    if(OAL_PTR_NULL != puc_ra)
    {
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR1_OFFSET, puc_ra);
    }
#ifdef _PRE_WLAN_FEATURE_P2P
    if (dmac_vap_is_in_p2p_listen(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);

        /* ���õ�ַ3Ϊbssid */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
    }
    else
#endif
    {
        /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /* ���õ�ַ3Ϊbssid */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);
    }

    /* ���÷�Ƭ���, ����֡Ϊ0 */
    mac_hdr_set_fragment_number(puc_mac_header, 0);

    /*************************************************************************/
    /*                  presence response Frame - Frame Body                 */
    /* ----------------------------------------------------------------------*/
    /* |Category |OUI   |OUI type|OUI subtype  | Dialog Token   |Element    |*/
    /* ----------------------------------------------------------------------*/
    /* |1        |3     |1       |1            |1               |variable   |*/
    /* ----------------------------------------------------------------------*/
    /*************************************************************************/

    puc_payload_addr[0] = MAC_ACTION_CATEGORY_VENDOR;
    uc_index = P2P_GEN_ACT_OUI_OFF1;

    /* OUI */
    oal_memcopy(&puc_payload_addr[uc_index], g_auc_p2p_oui, MAC_OUI_LEN);
    uc_index += MAC_OUI_LEN;

    /* OUI Type */
    puc_payload_addr[uc_index++] = MAC_OUITYPE_P2P;

    /* OUI Subtype */
    puc_payload_addr[uc_index++] = P2P_PRESENCE_RESP;

    /* Dialog Token */
    puc_payload_addr[uc_index++] = puc_data[P2P_GEN_ACT_DIALOG_TOKEN_OFF];
    puc_payload_addr += P2P_GEN_ACT_TAG_PARAM_OFF;

    /* Element */
    /* ���p2p Status Attribute*/
    mac_set_p2p_status(puc_payload_addr, &uc_ie_len, P2P_STAT_SUCCESS);
    puc_payload_addr += uc_ie_len;

    /* ���p2p noa Attribute*/
    if(IS_P2P_PS_ENABLED(pst_dmac_vap))
    {
        mac_set_p2p_noa(pst_mac_vap, puc_payload_addr, &uc_ie_len);
        puc_payload_addr += uc_ie_len;
    }
    else
    {
        mac_set_p2p_none_noa(pst_mac_vap, puc_payload_addr, &uc_ie_len);
        puc_payload_addr += uc_ie_len;
    }


    return (oal_uint16)(puc_payload_addr - puc_payload_addr_origin + MAC_80211_FRAME_LEN);
}

/*****************************************************************************
 �� �� ��  : dmac_get_p2p_attr
 ��������  : ��beacon֡�в���P2P NoA attr
 �������  : 1) beacon֡
             2) ֡����
             3) �����֡ͷ��ƫ��λ�ó��ȣ����������
 �������  : ��
 �� �� ֵ  : ָ��beacon֡��p2p NoA attr��λ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��28��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  *dmac_get_p2p_noa_attr(oal_uint8 *puc_frame_body, oal_uint16 us_rx_len, oal_uint16 uc_tag_param_offset, oal_uint16 *pus_attr_len)
{
    oal_uint16  us_index         = 0;
    oal_uint16  us_num_bytes     = 0;
	oal_uint32  ulIndex          = 0;
	oal_uint8  *pucData         = NULL;
    //oal_uint8  *puc_noa_attr    = NULL;
    //oal_uint16  us_loops;
    us_index = uc_tag_param_offset;

    /*************************************************************************/
    /*                       Beacon Frame - Frame Body                       */
    /* --------------------------------------------------------------------- */
    /* |Timestamp |BeaconInt |CapInfo |SSID |SupRates |DSParSet |TAG       | */
    /* --------------------------------------------------------------------- */
    /* |8         |2         |2       |2-34 |3-10     |3        |???       | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
#if 0
        OAL_IO_PRINT("dmac_get_p2p_noa_attr:: us_rx_len=%d\r\n",us_rx_len);
        for (us_loops = 0; us_loops < us_rx_len; us_loops++)
        {
            OAL_IO_PRINT("%02x ", puc_frame_body[us_loops]);
            if ((us_loops+1)%16 == 0)
                OAL_IO_PRINT("\r\n");
        }
        OAL_IO_PRINT("\r\n");
#endif

    while (us_index < (us_rx_len - WLAN_HDR_FCS_LENGTH))
    {
        if(OAL_TRUE == dmac_is_p2p_ie(puc_frame_body + us_index)) /* �ҵ�P2P IE */
        {
            ulIndex = 0;
            /* get the P2P IE len */
			us_num_bytes = puc_frame_body[us_index + 1] - P2P_OUI_LEN;
            pucData    = puc_frame_body + us_index + MAC_IE_HDR_LEN + P2P_OUI_LEN;

            while(ulIndex < us_num_bytes)
            {
                if(NOTICE_OF_ABSENCE == pucData[ulIndex])/* �ҵ�NoA���� */
                {
                    *pus_attr_len = GET_ATTR_LEN(pucData + ulIndex);
                    return (oal_uint8*)(puc_frame_body + us_index + ulIndex + MAC_IE_HDR_LEN + P2P_OUI_LEN + P2P_ATTR_HDR_LEN + 1);
                }
                ulIndex += GET_ATTR_LEN(pucData + ulIndex) + P2P_ATTR_HDR_LEN;
            }
        }
        /* Move to the next IE. */
        us_index += (MAC_IE_HDR_LEN + puc_frame_body[us_index + 1]);
    }
    return OAL_PTR_NULL;
}

/*****************************************************************************
 �� �� ��  : dmac_process_p2p_noa
 ��������  : beacon֡ʱ���Ƿ����p2p noa����
             ����NoA���ܲ���
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_process_p2p_noa(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru            *pst_rx_ctrl;
    mac_rx_ctl_stru             *pst_rx_info;
    oal_uint16                   us_frame_len;
    oal_uint8                   *puc_noa_attr = OAL_PTR_NULL;
    oal_uint8                   *puc_payload;
    mac_cfg_p2p_ops_param_stru   st_p2p_ops;
    mac_cfg_p2p_noa_param_stru   st_p2p_noa;
    oal_uint16                   us_attr_index = 0;
    hal_to_dmac_vap_stru        *pst_hal_vap;
    oal_uint16                   us_attr_len = 0;
    oal_uint32                   ul_current_tsf_lo;

    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_netbuf)
    {
        //OAM_INFO_LOG0(0, OAM_SF_P2P, "{dmac_process_p2p_noa::param null.}");
        return;
    }
    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    us_frame_len     = pst_rx_info->us_frame_len - pst_rx_info->bit_mac_header_len; /*֡�峤��*/
#else
    us_frame_len     = pst_rx_info->us_frame_len - pst_rx_info->uc_mac_header_len; /*֡�峤��*/
#endif
    puc_payload         = OAL_NETBUF_PAYLOAD(pst_netbuf);

    OAL_MEMZERO(&st_p2p_ops, OAL_SIZEOF(st_p2p_ops));
    OAL_MEMZERO(&st_p2p_noa, OAL_SIZEOF(st_p2p_noa));
    /* ȡ��NoA attr*/
    puc_noa_attr = dmac_get_p2p_noa_attr(puc_payload, us_frame_len, MAC_DEVICE_BEACON_OFFSET, &us_attr_len);
    if (OAL_PTR_NULL == puc_noa_attr)
    {
        if(IS_P2P_NOA_ENABLED(pst_dmac_vap) || IS_P2P_OPPPS_ENABLED(pst_dmac_vap))
        {
            /* ֹͣ���� */
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                            "{dmac_process_p2p_noa::puc_noa_attr null. stop p2p ps}");

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
            /*ֹͣp2p noa oppps ʱ�ָ���˯ */
            PM_WLAN_EnableDeepSleep();
#endif
        }
        else
        {
            return;
        }
    }
    else
    {
        /* ����ops����*/
        if((puc_noa_attr[us_attr_index] & BIT7) != 0)
        {
            st_p2p_ops.en_ops_ctrl = 1;
            st_p2p_ops.uc_ct_window = (puc_noa_attr[us_attr_index] & 0x7F);
        }

        if(us_attr_len > 2)
        {
            /* ����NoA����*/
            us_attr_index++;
            st_p2p_noa.uc_count = puc_noa_attr[us_attr_index++];
            st_p2p_noa.ul_duration = OAL_MAKE_WORD32(OAL_MAKE_WORD16(puc_noa_attr[us_attr_index],
                                             puc_noa_attr[us_attr_index + 1]),
                                             OAL_MAKE_WORD16(puc_noa_attr[us_attr_index + 2],
                                             puc_noa_attr[us_attr_index + 3]));
            us_attr_index += 4;
            st_p2p_noa.ul_interval = OAL_MAKE_WORD32(OAL_MAKE_WORD16(puc_noa_attr[us_attr_index],
                                             puc_noa_attr[us_attr_index + 1]),
                                             OAL_MAKE_WORD16(puc_noa_attr[us_attr_index + 2],
                                             puc_noa_attr[us_attr_index + 3]));
            us_attr_index += 4;
            st_p2p_noa.ul_start_time = OAL_MAKE_WORD32(OAL_MAKE_WORD16(puc_noa_attr[us_attr_index],
                                             puc_noa_attr[us_attr_index + 1]),
                                             OAL_MAKE_WORD16(puc_noa_attr[us_attr_index + 2],
                                             puc_noa_attr[us_attr_index + 3]));
        }
    }

    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;
    /* ����GO���ܲ���������P2P ops �Ĵ��� */
    if((pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl != st_p2p_ops.en_ops_ctrl)||
        (pst_dmac_vap->st_p2p_ops_param.uc_ct_window != st_p2p_ops.uc_ct_window))
    {
        pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl = st_p2p_ops.en_ops_ctrl;
        pst_dmac_vap->st_p2p_ops_param.uc_ct_window = st_p2p_ops.uc_ct_window;
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "dmac_process_p2p_noa:ctrl:%d, ct_window:%d\r\n",
                    pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl,
                    pst_dmac_vap->st_p2p_ops_param.uc_ct_window);

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
        /* ����p2p opppsֻ��ǳ˯ */
        if (st_p2p_ops.en_ops_ctrl)
        {
            PM_WLAN_DisbaleDeepSleep();
        }
#endif
        /* ����P2P ops �Ĵ��� */
        hal_vap_set_ops(pst_hal_vap, pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl, pst_dmac_vap->st_p2p_ops_param.uc_ct_window);
    }

    /* ����GO���ܲ���������P2P NoA �Ĵ��� */
    if((pst_dmac_vap->st_p2p_noa_param.uc_count != st_p2p_noa.uc_count)||
        (pst_dmac_vap->st_p2p_noa_param.ul_duration != st_p2p_noa.ul_duration)||
        (pst_dmac_vap->st_p2p_noa_param.ul_interval != st_p2p_noa.ul_interval) ||
        (pst_dmac_vap->st_p2p_noa_param.ul_start_time != st_p2p_noa.ul_start_time))
    {
        pst_dmac_vap->st_p2p_noa_param.uc_count = st_p2p_noa.uc_count;
        pst_dmac_vap->st_p2p_noa_param.ul_duration = st_p2p_noa.ul_duration;
        pst_dmac_vap->st_p2p_noa_param.ul_interval = st_p2p_noa.ul_interval;
        pst_dmac_vap->st_p2p_noa_param.ul_start_time = st_p2p_noa.ul_start_time;
        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "dmac_process_p2p_noa:start_time:%u, duration:%d, interval:%d, count:%d\r\n",
                    pst_dmac_vap->st_p2p_noa_param.ul_start_time,
                    pst_dmac_vap->st_p2p_noa_param.ul_duration,
                    pst_dmac_vap->st_p2p_noa_param.ul_interval,
                    pst_dmac_vap->st_p2p_noa_param.uc_count);

        hal_vap_tsf_get_32bit(pst_hal_vap, &ul_current_tsf_lo);
        if((st_p2p_noa.ul_start_time < ul_current_tsf_lo)&&
          (st_p2p_noa.ul_start_time != 0))
        {
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "dmac_process_p2p_noa:start time %u is less than tsf time %u\r\n",
                    st_p2p_noa.ul_start_time,
                    ul_current_tsf_lo);
            st_p2p_noa.ul_start_time = ul_current_tsf_lo + (st_p2p_noa.ul_interval - (ul_current_tsf_lo - st_p2p_noa.ul_start_time)% st_p2p_noa.ul_interval);
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "dmac_process_p2p_noa:start time update to %u\r\n",
                            st_p2p_noa.ul_start_time);

        }

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
        /* ����p2p NOAֻ��ǳ˯ */
        if (st_p2p_noa.uc_count)
        {
            PM_WLAN_DisbaleDeepSleep();
        }
#endif
        hal_vap_set_noa(pst_hal_vap,
                        st_p2p_noa.ul_start_time,
                        st_p2p_noa.ul_duration,
                        st_p2p_noa.ul_interval,
                        st_p2p_noa.uc_count);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_p2p_go_absence_period_start_sta_prot
 ��������  : This function checks if a WMM service period is in progress.
             If it is, a Trigger frame is queued.
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_p2p_go_absence_period_start_sta_prot(dmac_vap_stru * pst_dmac_vap)
{
#ifdef _PRE_FEATURE_WLAN_STA_UAPSD

    oal_uint8   uc_tid = WLAN_TID_MAX_NUM;

    /* If WMM-PS USP is in process, queue a QoS NULL trigger frame in the    */
    /* highest priority trigger enabled queue                                */
    if(dmac_is_uapsd_sp_not_in_progress() == OAL_FALSE)
    {
        uc_tid = dmac_get_highest_trigger_enabled_priority();

        if(uc_tid != WLAN_TID_MAX_NUM)
        {
            dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE, OAL_TRUE);
        }
    }
#endif
}
/*****************************************************************************
 �� �� ��  : dmac_p2p_noa_absent_start_event
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_p2p_noa_absent_start_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    dmac_vap_stru              *pst_dmac_vap = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_noa_absent_start_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);
    pst_dmac_vap = mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
    #ifdef _PRE_WLAN_FEATURE_STA_PM
        if(STA_PWR_SAVE_STATE_DOZE != dmac_psm_get_state(pst_dmac_vap))
        {
            /* Protocol dependent processing */
            dmac_p2p_go_absence_period_start_sta_prot(pst_dmac_vap);

            if(OAL_TRUE == dmac_is_ps_poll_rsp_pending(pst_dmac_vap))
            {
                if (OAL_SUCC != dmac_send_pspoll_to_ap(pst_dmac_vap))
                {
                    OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_p2p_noa_absent_start_event::dmac_send_pspoll_to_ap fail}");
                }

            }
        }
        if(IS_P2P_NOA_ENABLED(pst_dmac_vap))
        {
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_P2P_SLEEP, 0, OAL_PTR_NULL);
        }
    #endif
    }

    else
    {
        if(IS_P2P_NOA_ENABLED(pst_dmac_vap))
        {
            /* ��ͣ���� */

            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_p2p_noa_absent_end_event
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_p2p_noa_absent_end_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    mac_device_stru            *pst_mac_device;
    mac_vap_stru               *pst_mac_vap = OAL_PTR_NULL;
    dmac_vap_stru              *pst_dmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_noa_absent_end_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_noa_absent_end_event::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = mac_res_get_mac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_P2P, "{dmac_p2p_noa_absent_end_event::mac_res_get_mac_vap fail.vap_id = %u}",pst_event->st_event_hdr.uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    //�жϼĴ���״̬noa count�Ƿ������0:���� 1: ������; ����P2P IE
    if(((hal_p2p_pm_event_stru *)(pst_event->auc_event_data))->p2p_noa_status == OAL_FALSE)
    {
        OAM_WARNING_LOG0(0, OAM_SF_P2P, "{dmac_p2p_noa_absent_end_event::p2p NoA count expired}");
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }

    //OAL_IO_PRINT("dmac_p2p_handle_ps_cl:resume\r\n");
    /* �ָ����� */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
    #ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_P2P_AWAKE, 0, OAL_PTR_NULL);
    #endif
    }
    else
    {
        dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_p2p_oppps_ctwindow_end_event
 ��������  : beacon֡ʱ���Ƿ����p2p noa����
             ����NoA���ܲ���
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_p2p_oppps_ctwindow_end_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    mac_device_stru            *pst_mac_device;
    mac_vap_stru               *pst_mac_vap = OAL_PTR_NULL;
    dmac_vap_stru              *pst_dmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_ctwindow_end_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_ctwindow_end_event::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap = mac_res_get_mac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_P2P, "{dmac_p2p_ctwindow_end_event::mac_res_get_mac_vap fail.vap_id = %u}",pst_event->st_event_hdr.uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* ��¼��ͣ���ŵ���tbtt�жϺ��л� */
        pst_mac_device->st_home_channel = pst_mac_vap->st_channel;
    #ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_P2P_SLEEP, 0, OAL_PTR_NULL);
    #endif
    }
    else
    {
        if(OAL_FALSE == pst_dmac_vap->st_p2p_ops_param.en_pause_ops)
        {
            /* ��¼��ͣ���ŵ���tbtt�жϺ��л� */
            pst_mac_device->st_home_channel = pst_mac_vap->st_channel;
#ifdef _PRE_WLAN_FEATURE_STA_PM
            /* ��ͣ���� */
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);
#endif

        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_p2p_oppps_ctwindow_start_event
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_p2p_oppps_ctwindow_start_event(dmac_vap_stru * pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_PM
    oal_uint32 ui_retval = 0;
#endif

    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_STA_PM
        ui_retval = dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_P2P_AWAKE, 0, OAL_PTR_NULL);
        if(OAL_SUCC != ui_retval)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_p2p_oppps_ctwindow_start_event::[%d]}", ui_retval);
        }
#endif
    }
    else
    {
        /* �ָ����� */
        dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_p2p_reset_ps_status_for_dbac
 ��������  : dbac����ʱ,�ж����p2p�豸��pause,�ָ���״̬
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_p2p_reset_ps_status_for_dbac(
                                mac_device_stru  *pst_device,
                                mac_vap_stru     *pst_led_vap,
                                mac_vap_stru     *pst_flw_vap)
{
    dmac_vap_stru *pst_dmac_p2p_vap;
    mac_vap_stru  *pst_p2p_vap;

#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_cfg_ps_open_stru  st_ps_open;

    st_ps_open.uc_pm_enable      = MAC_STA_PM_SWITCH_OFF;
    st_ps_open.uc_pm_ctrl_type   = MAC_STA_PM_CTRL_TYPE_DBAC;

	/* ����dbacǰ�رյ͹��� */
    if (WLAN_VAP_MODE_BSS_STA == pst_led_vap->en_vap_mode)
    {
        dmac_config_set_sta_pm_on(pst_led_vap, OAL_SIZEOF(mac_cfg_ps_open_stru), (oal_uint8 *)&st_ps_open);
    }

    if(WLAN_VAP_MODE_BSS_STA == pst_flw_vap->en_vap_mode)
    {
        dmac_config_set_sta_pm_on(pst_flw_vap, OAL_SIZEOF(mac_cfg_ps_open_stru), (oal_uint8 *)&st_ps_open);
    }
#endif

    /* ��dbacǰp2p�Ѿ�pause��tid��,��Ҫ�ָ� */
    if (OAL_TRUE == pst_device->st_p2p_info.en_p2p_ps_pause)
    {
        if (WLAN_LEGACY_VAP_MODE != pst_led_vap->en_p2p_mode)
        {
            pst_p2p_vap = pst_led_vap;
        }
        else
        {
            pst_p2p_vap = pst_flw_vap;
        }

        pst_dmac_p2p_vap = mac_res_get_dmac_vap(pst_p2p_vap->uc_vap_id);
        dmac_p2p_handle_ps(pst_dmac_p2p_vap, OAL_FALSE);
    }
}
#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
 �� �� ��  : dmac_p2p_resume_send_null_to_ap
 ��������  : P2P �ָ�����null֡�ӿ�
 �������  : dmac_vap_stru * pst_dmac_vap mac_sta_pm_handler_stru *pst_mac_sta_pm_handle
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_p2p_resume_send_null_to_ap(dmac_vap_stru *pst_dmac_vap,mac_sta_pm_handler_stru *pst_mac_sta_pm_handle)
{
    oal_uint8       uc_power_mgmt = 0xff;

    /* ����Ҫ�ش� */
    if ((0 == pst_mac_sta_pm_handle->en_ps_back_active_pause) && (0 == pst_mac_sta_pm_handle->en_ps_back_doze_pause))
    {
        return;
    }

    /* ����״̬��״̬������Ӧnull֡ */
    if (STA_PWR_SAVE_STATE_ACTIVE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
    {
        if (OAL_TRUE == pst_mac_sta_pm_handle->en_ps_back_doze_pause)
        {
            uc_power_mgmt = 1;
        }
    }
    else
    {
        if (OAL_TRUE == pst_mac_sta_pm_handle->en_ps_back_active_pause)
        {
            if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
            {
                dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TX_DATA, 0, OAL_PTR_NULL);
            }
            uc_power_mgmt = 0;
        }
    }

    if ((0 == uc_power_mgmt) || (1 == uc_power_mgmt))
    {
        if (OAL_SUCC != dmac_psm_process_fast_ps_state_change(pst_dmac_vap, uc_power_mgmt))
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"dmac_p2p_resume_send_null_to_ap::send[%d]null fail",uc_power_mgmt);

            /* ˯�ߵ�null֡����ʧ����Ҫ������ʱ���ȴ���ʱ����,���ѵ�null֡����ʧ��,�ȴ��´η��ͻ���beacon�ٸ�֪���� */
            if (uc_power_mgmt)
            {
                dmac_psm_start_activity_timer(pst_dmac_vap,pst_mac_sta_pm_handle);
            }
        }
    }
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_p2p_handle_ps
 ��������  : ����p2p����״̬
 �������  : dmac_vap_stru * pst_dmac_vap
             oal_uint8 en_pause: OAL_TRUE ��ͣ���� OAL_FALSE �ָ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_p2p_handle_ps(dmac_vap_stru * pst_dmac_vap, oal_bool_enum_uint8 en_pause)
{

#ifdef _PRE_WLAN_FEATURE_STA_PM

    mac_vap_stru               *pst_mac_vap = OAL_PTR_NULL;
    dmac_user_stru             *pst_dmac_user = OAL_PTR_NULL;
    mac_device_stru            *pst_mac_device;
    mac_sta_pm_handler_stru    *pst_mac_sta_pm_handle;
    oal_uint8                  uc_noa_not_sleep_flag;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_handle_ps::pst_dmac_vap null.}");
        return;
    }
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    pst_mac_device  = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_p2p_handle_ps::pst_mac_device is null.}");
        return;
    }

     /* dbac������,ֱ��return */
    if ((OAL_TRUE == mac_is_dbac_running(pst_mac_device)))
    {
        return;
    }

    if(pst_mac_device->st_p2p_info.en_p2p_ps_pause == en_pause)
    {
        return;
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user((oal_uint16)(pst_mac_vap->uc_assoc_vap_id));
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{dmac_p2p_handle_ps::pst_dmac_user null.user idx [%d]}",
                            pst_mac_vap->uc_assoc_vap_id);
            return;
        }
        else
        {
            /* P2P CLIENT оƬ�������P2P CLIENT ע�ᣬ�����ܶ�P2P DEVICE ע�� */
            if(OAL_TRUE == en_pause)
            {
                dmac_user_pause(pst_dmac_user);
            #if 0
                hal_tx_enable_peer_sta_ps_ctrl(pst_dmac_vap->pst_hal_device, pst_dmac_user->uc_lut_index);
            #endif

                /*suspendӲ������*/
                hal_set_machw_tx_suspend(pst_mac_device->pst_device_stru);
                /* ����Ӳ�����У������ڸ��û���֡���Ż�tid */
                dmac_psm_flush_txq_to_tid(pst_mac_device, pst_dmac_vap, pst_dmac_user);
                /* �ָ�Ӳ������ */
                hal_set_machw_tx_resume(pst_mac_device->pst_device_stru);
                pst_mac_device->uc_mac_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;  /* ��¼˯��ʱvap id */

                /* ������˯������,�˴�noa��ǳ˯,���ر�ǰ�� */
                uc_noa_not_sleep_flag = (pst_mac_sta_pm_handle->en_beacon_frame_wait) | (pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait << 1) | (pst_mac_sta_pm_handle->en_more_data_expected << 2)
                        | (pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait << 3) | (pst_mac_sta_pm_handle->en_direct_change_to_active << 4);

                if (uc_noa_not_sleep_flag == 0)
                {
                    PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_DEEPSLEEP_PROCESS); /* ͶƱ���� */
                    pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_P2P_SLEEP]++;
                }
            }
            else
            {
                PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);/* ͶƱ���� */

                /* ���Ѻ����ָ̻�ǰ�� */
                dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);

                pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_P2P_AWAKE]++;
            #if 0
                /* �ָ���vap�µ������û���Ӳ�����еķ��� */
                hal_tx_disable_peer_sta_ps_ctrl(pst_dmac_vap->pst_hal_device, pst_dmac_user->uc_lut_index);
            #endif

                dmac_user_resume(pst_dmac_user);   /* �ָ�user���ָ���user��ÿһ��tid */
                /* �����еĻ���֡���ͳ�ȥ */
                dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_user);

                dmac_p2p_resume_send_null_to_ap(pst_dmac_vap,pst_mac_sta_pm_handle);
            }
        }
    }
    else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {   //P2P GO оƬ������Ҫͨ����������
        if (OAL_TRUE == en_pause)
        {
            dmac_ap_pause_all_user(pst_mac_vap);

            pst_mac_device->uc_mac_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;  /* ��¼˯��ʱvap id */

            //PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_LIGHTSLEEP_PROCESS);/* ͶƱ���� */
        }
        else
        {
            //PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);/* ͶƱ���� */

            dmac_ap_resume_all_user(pst_mac_vap);
        }
    }

    /*��¼Ŀǰp2p����״̬*/
    pst_mac_device->st_p2p_info.en_p2p_ps_pause = en_pause;
#endif
}



#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



