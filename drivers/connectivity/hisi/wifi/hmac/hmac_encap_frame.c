/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_encap_frame.c
  �� �� ��   : ����
  ��    ��   : y00184180
  ��������   : 2013��6��28��
  ����޸�   :
  ��������   : APģʽ��STAģʽ����֡����֡�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��28��
    ��    ��   : y00184180
    �޸�����   : �����ļ�

*******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "wlan_spec.h"
#include "mac_resource.h"
#include "hmac_encap_frame.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ENCAP_FRAME_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
     �� �� ��  : hmac_encap_sa_query_req
     ��������  : ��sa query ����֡
     �������  : pst_mac_vap :mac vap�ṹ��
                 puc_data    :netbuf dataָ��
                 puc_da      :Ŀ���û���mac��ַ
                 trans_id    :sa query ie,���ڱ��response��request�Ƿ�һ��
     �������  : ��
     �� �� ֵ  : ֡ͷ+֡��ĳ���
     ���ú���  :
     ��������  :

     �޸���ʷ      :
      1.��    ��   : 2014��4��19��
        ��    ��   : z00273164
        �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16 hmac_encap_sa_query_req(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da,oal_uint16 us_trans_id)
{
    oal_uint16 us_len = 0;

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
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_ACTION);
    /*  Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  SA Query Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* |   Category   |SA Query Action |  Transaction Identifier           | */
    /* --------------------------------------------------------------------- */
    /* |1             |1               |2 Byte                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
     puc_data[MAC_80211_FRAME_LEN] = MAC_ACTION_CATEGORY_SA_QUERY;
     puc_data[MAC_80211_FRAME_LEN+1] = MAC_SA_QUERY_ACTION_REQUEST;
     puc_data[MAC_80211_FRAME_LEN+2] = (us_trans_id & 0x00FF);
     puc_data[MAC_80211_FRAME_LEN+3] = (us_trans_id & 0xFF00) >> 8;

     us_len = MAC_80211_FRAME_LEN + MAC_SA_QUERY_LEN;
     return us_len;
}

/*****************************************************************************
     �� �� ��  : hmac_encap_sa_query_rsp
     ��������  : ��sa query ����֡
     �������  : pst_hdr:sa query request frame
                 puc_data:sa query response frame
     �������  : ��
     �� �� ֵ  : ֡ͷ+֡��ĳ���
     ���ú���  :
     ��������  :

     �޸���ʷ      :
      1.��    ��   : 2014��4��19��
        ��    ��   : z00273164
        �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16 hmac_encap_sa_query_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 *pst_hdr, oal_uint8 *puc_data)
{
    oal_uint16 us_len = 0;

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
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_ACTION);
    /* Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, ((mac_ieee80211_frame_stru *)pst_hdr)->auc_address2);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);
    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  SA Query Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* |   Category   |SA Query Action |  Transaction Identifier           | */
    /* --------------------------------------------------------------------- */
    /* |1             |1               |2 Byte                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_data[MAC_80211_FRAME_LEN] = pst_hdr[MAC_80211_FRAME_LEN];
    puc_data[MAC_80211_FRAME_LEN+1] = MAC_SA_QUERY_ACTION_RESPONSE;
    puc_data[MAC_80211_FRAME_LEN+2] = pst_hdr[MAC_80211_FRAME_LEN+2];
    puc_data[MAC_80211_FRAME_LEN+3] = pst_hdr[MAC_80211_FRAME_LEN+3];

    us_len = MAC_80211_FRAME_LEN + MAC_SA_QUERY_LEN;
    return us_len;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_prepare_deauth
 ��������  : ��ȥ��֤֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_deauth(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da, oal_uint16 us_err_code)
{
    oal_uint16          us_deauth_len = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_up_vap1;
    mac_vap_stru       *pst_up_vap2;
    oal_uint32          ul_ret;
#endif

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

    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_DEAUTH);

    /* Set DA to address of unauthenticated STA */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);

#ifdef _PRE_WLAN_FEATURE_P2P
    if (us_err_code & MAC_SEND_TWO_DEAUTH_FLAG)
    {
        us_err_code = us_err_code & ~MAC_SEND_TWO_DEAUTH_FLAG;

        pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
        {
            us_deauth_len = 0;
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_mgmt_encap_deauth::pst_mac_device[%d] null!}", pst_mac_vap->uc_device_id);
            return us_deauth_len;
        }

        ul_ret = mac_device_find_2up_vap(pst_mac_device, &pst_up_vap1, &pst_up_vap2);
        if (OAL_SUCC == ul_ret)
        {
            /* ��ȡ����һ��VAP����֡ʱ�޸ĵ�ַ2Ϊ����1��VAP��MAC��ַ */
            if (pst_mac_vap->uc_vap_id != pst_up_vap1->uc_vap_id)
            {
                pst_up_vap2 = pst_up_vap1;
            }

            if (OAL_PTR_NULL == pst_up_vap2->pst_mib_info)
            {
                us_deauth_len = 0;
                OAM_ERROR_LOG0(pst_up_vap2->uc_vap_id, OAM_SF_AUTH, "hmac_mgmt_encap_deauth: pst_up_vap2 mib ptr null.");
                return us_deauth_len;
            }
            oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_up_vap2->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
            oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_up_vap2->auc_bssid);
        }

        OAM_WARNING_LOG1(0, OAM_SF_AUTH, "hmac_mgmt_encap_deauth: send the second deauth frame. error code:%d", us_err_code);
    }
    else
#endif
    {
        if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
        {
            us_deauth_len = 0;
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "hmac_mgmt_encap_deauth: pst_mac_vap mib ptr null.");
            return us_deauth_len;
        }

        /* SA is the dot11MACAddress */
        oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
        oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);
    }
    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  Deauthentication Frame - Frame Body                  */
    /* --------------------------------------------------------------------- */
    /* |                           Reason Code                             | */
    /* --------------------------------------------------------------------- */
    /* |2 Byte                                                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* Set Reason Code to 'Class2 error' */
    puc_data[MAC_80211_FRAME_LEN]     = (us_err_code & 0x00FF);
    puc_data[MAC_80211_FRAME_LEN + 1] = (us_err_code & 0xFF00) >> 8;

    us_deauth_len = MAC_80211_FRAME_LEN + WLAN_REASON_CODE_LEN;

    return us_deauth_len;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_disassoc
 ��������  : ��ȥ����֡
 �������  : vapָ��,DA,ErrCode
 �������  : ֡������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_disassoc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da, oal_uint16 us_err_code)
{
    oal_uint16 us_disassoc_len = 0;

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
    /*                            ����֡ͷ                                   */
    /*************************************************************************/

    /* ����subtype   */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_DISASSOC);

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        us_disassoc_len = 0;
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "hmac_mgmt_encap_disassoc: pst_mac_vap mib ptr null.");
        return us_disassoc_len;
    }
    /* ����DA */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);

    /* ����SA */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ����bssid */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_AP ?
                                                            pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID : pst_mac_vap->auc_bssid);



    /*************************************************************************/
    /*                  Disassociation ֡ - ֡��                  */
    /* --------------------------------------------------------------------- */
    /* |                           Reason Code                             | */
    /* --------------------------------------------------------------------- */
    /* |2 Byte                                                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* ����reason code*/
    puc_data[MAC_80211_FRAME_LEN]     = (us_err_code & 0x00FF);
    puc_data[MAC_80211_FRAME_LEN + 1] = (us_err_code & 0xFF00) >> 8;

    us_disassoc_len = MAC_80211_FRAME_LEN + WLAN_REASON_CODE_LEN;

    return us_disassoc_len;
}

/*****************************************************************************
 �� �� ��  : hmac_check_sta_base_rate
 ��������  : ��鵱ǰSTA�Ƿ�֧��AP�Ļ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_check_sta_base_rate(oal_uint8 *pst_user, mac_status_code_enum_uint16 *pen_status_code)
{
    oal_uint8            num_basic_rates;
    oal_uint8            uc_loop;
    oal_uint8            uc_index;
    oal_bool_enum_uint8  en_found;
    oal_uint8            uc_num_rates;
    oal_uint8            uc_ap_base_rate;
    mac_vap_stru        *pst_mac_vap;
    hmac_user_stru      *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)pst_user;

    /* ��ȡVAP */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hmac_user->st_user_base_info.uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return;
    }

    num_basic_rates = pst_mac_vap->st_curr_sup_rates.uc_br_rate_num;
    uc_num_rates    = pst_hmac_user->st_op_rates.uc_rs_nrates;


    for (uc_loop = 0; uc_loop < num_basic_rates; uc_loop++)
    {
        en_found = OAL_FALSE;
        uc_ap_base_rate = mac_vap_get_curr_baserate(pst_mac_vap,uc_loop);

        for (uc_index = 0; uc_index < uc_num_rates; uc_index++)
        {
            if ((pst_hmac_user->st_op_rates.auc_rs_rates[uc_index] & 0x7F) == (uc_ap_base_rate & 0x7F))
            {
                en_found = OAL_TRUE;
                break;
            }
        }

        /* ��֧��ĳ�������ʣ�����false  */
        if (OAL_FALSE == en_found)
        {
            *pen_status_code = MAC_UNSUP_RATE;
            return;
        }
    }
}
/*****************************************************************************
 �� �� ��  : hmac_encap_notify_chan_width
 ��������  : ��װNotify Channel Width Action֡
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��28��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16 hmac_encap_notify_chan_width(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da)
{
    oal_uint16 us_len = 0;

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
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_ACTION);
    /*  Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  SA Query Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* |   Category   |SA Query Action |  Transaction Identifier           | */
    /* --------------------------------------------------------------------- */
    /* |1             |1               |2 Byte                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
     puc_data[MAC_80211_FRAME_LEN] = MAC_ACTION_CATEGORY_HT;
     puc_data[MAC_80211_FRAME_LEN+1] = MAC_HT_ACTION_NOTIFY_CHANNEL_WIDTH;
     puc_data[MAC_80211_FRAME_LEN+2] = (pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M) ? 1 : 0;

     us_len = MAC_80211_FRAME_LEN + MAC_HT_NOTIFY_CHANNEL_WIDTH_LEN;
     return us_len;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

