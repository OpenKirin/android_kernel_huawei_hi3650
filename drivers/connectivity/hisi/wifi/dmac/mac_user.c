/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_user.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
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
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "mac_user.h"
//#include "mac_11i.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_USER_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mac_user_add_wep_key
 ��������  : ���wep��Կ��ָ������Կ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��14��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_add_wep_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key)
{
    if (uc_key_index >= WLAN_NUM_TK)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    if ((oal_uint32)pst_key->key_len > WLAN_WEP104_KEY_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    if ((oal_uint32)pst_key->seq_len > WLAN_WPA_SEQ_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_cipher    = pst_key->cipher;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_key_len   = (oal_uint32)pst_key->key_len;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_seq_len   = (oal_uint32)pst_key->seq_len;

    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_key, pst_key->auc_key, (oal_uint32)pst_key->key_len);
    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_seq, pst_key->auc_seq, (oal_uint32)pst_key->seq_len);

    pst_mac_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_add_rsn_key
 ��������  : ����rsn������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_add_rsn_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key)
{
    if (uc_key_index >= WLAN_NUM_TK)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }
    if ((oal_uint32)pst_key->key_len > WLAN_WPA_KEY_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    if ((oal_uint32)pst_key->seq_len > WLAN_WPA_SEQ_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_cipher    = pst_key->cipher;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_key_len   = (oal_uint32)pst_key->key_len;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_seq_len   = (oal_uint32)pst_key->seq_len;

    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_key, pst_key->auc_key, (oal_uint32)pst_key->key_len);
    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_seq, pst_key->auc_seq, (oal_uint32)pst_key->seq_len);

    pst_mac_user->st_key_info.en_cipher_type    = (oal_uint8)pst_key->cipher;
    pst_mac_user->st_key_info.uc_default_index  = uc_key_index;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_add_bip_key
 ��������  : ����bip��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_add_bip_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key)
{

    /* keyidУ�� */
    if (uc_key_index < WLAN_NUM_TK || uc_key_index > WLAN_MAX_IGTK_KEY_INDEX)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_cipher    = pst_key->cipher;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_key_len   = (oal_uint32)pst_key->key_len;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_seq_len   = (oal_uint32)pst_key->seq_len;

    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_key, pst_key->auc_key, (oal_uint32)pst_key->key_len);
    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_seq, pst_key->auc_seq, (oal_uint32)pst_key->seq_len);

    pst_mac_user->st_key_info.uc_igtk_key_index = uc_key_index;

    return  OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_get_key
 ��������  : ����en_key_type��������Ӧ�ĺ���������vap��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
wlan_priv_key_param_stru *mac_user_get_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_id)
{
    if(uc_key_id >= WLAN_NUM_TK + WLAN_NUM_IGTK)
    {
        return OAL_PTR_NULL;
    }
    return &pst_mac_user->st_key_info.ast_key[uc_key_id];
}

/*****************************************************************************
 �� �� ��  : mac_user_set_port
 ��������  : ��λ11X�˿�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_set_port(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_port_valid)
{
    pst_mac_user->en_port_valid = en_port_valid;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_init_key
 ��������  : ��ʼ���û�����Կ��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��14��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_init_key(mac_user_stru *pst_mac_user)
{

    OAL_MEMZERO(&pst_mac_user->st_key_info, sizeof(mac_key_mgmt_stru));
    pst_mac_user->st_key_info.en_cipher_type  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    pst_mac_user->st_key_info.uc_last_gtk_key_idx = 0xFF;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_set_key
 ��������  : �����û��İ�ȫ��Ϣ
 �������  :
 �������  :
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :
 ��    ��  : ��ֹ�˺�����дʱ��ֻ��keyid�õ�ʹ�ã�multiuser�µİ�ȫ��Ϣ�����Ż�һ��
 �޸���ʷ      :
  1.��    ��   : 2015��03��17��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_set_key(mac_user_stru *pst_multiuser,
                            wlan_cipher_key_type_enum_uint8 en_keytype,
                            wlan_ciper_protocol_type_enum_uint8 en_ciphertype,
                            oal_uint8       uc_keyid)
{

    pst_multiuser->st_user_tx_info.st_security.en_cipher_key_type      = en_keytype;
    pst_multiuser->st_user_tx_info.st_security.en_cipher_protocol_type = en_ciphertype;
    pst_multiuser->st_user_tx_info.st_security.uc_cipher_key_id        = uc_keyid;
    OAM_WARNING_LOG4(0, OAM_SF_WPA,
                   "{mac_user_set_key::keytpe==%u, ciphertype==%u, keyid==%u, usridx==%u}",
                   en_keytype, en_ciphertype, uc_keyid, pst_multiuser->us_assoc_id);


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_init
 ��������  : ��ʼ��mac user��������
 �������  : pst_mac_user: ָ��user�Ľṹ��
             us_user_idx : �û�����
             puc_mac_addr: MAC��ַ
             uc_chip_id  :
             uc_device_id:
             uc_vap_id   :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_user_init(
                mac_user_stru  *pst_mac_user,
                oal_uint16      us_user_idx,
                oal_uint8      *puc_mac_addr,
                oal_uint8       uc_chip_id,
                oal_uint8       uc_device_id,
                oal_uint8       uc_vap_id)
{
#ifdef _PRE_WLAN_FEATURE_WMMAC
    oal_uint8    uc_ac_loop;
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_user_init::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ��chip id, device ip, vap id */
    pst_mac_user->uc_chip_id    = uc_chip_id;
    pst_mac_user->uc_device_id  = uc_device_id;
    pst_mac_user->uc_vap_id     = uc_vap_id;
    pst_mac_user->us_assoc_id   = us_user_idx;

    /* ��ʼ����Կ */
    pst_mac_user->st_user_tx_info.st_security.en_cipher_key_type      = WLAN_KEY_TYPE_PTK;
    pst_mac_user->st_user_tx_info.st_security.en_cipher_protocol_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    //pst_mac_user->st_user_tx_info.st_security.en_cipher_protocol_type = WLAN_NO_ENCRYP;

    /* ��ʼ����ȫ������Ϣ */
    mac_user_init_key(pst_mac_user);
    mac_user_set_key(pst_mac_user, WLAN_KEY_TYPE_PTK, WLAN_80211_CIPHER_SUITE_NO_ENCRYP, 0);
    mac_user_set_port(pst_mac_user, OAL_FALSE);
    pst_mac_user->en_user_asoc_state = MAC_USER_STATE_BUTT;

    if (OAL_PTR_NULL == puc_mac_addr)
    {
        pst_mac_user->en_is_multi_user   = OAL_TRUE;
        pst_mac_user->en_user_asoc_state = MAC_USER_STATE_ASSOC;
    }
    else
    {
        /* ��ʼ��һ���û��Ƿ����鲥�û��ı�־���鲥�û���ʼ��ʱ������ñ����� */
        pst_mac_user->en_is_multi_user = OAL_FALSE;

        /* ����mac��ַ */
        oal_set_mac_addr(pst_mac_user->auc_user_mac_addr, puc_mac_addr);
    }

    /* ��ʼ������ */
    mac_user_set_pmf_active(pst_mac_user, OAL_FALSE);
    pst_mac_user->st_cap_info.bit_proxy_arp = OAL_FALSE;

    mac_user_set_avail_num_spatial_stream(pst_mac_user, MAC_USER_INIT_STREAM);
#ifdef _PRE_WLAN_FEATURE_WMMAC
    /*TS��Ϣ��ʼ��*/
    for (uc_ac_loop = 0; uc_ac_loop < WLAN_WME_AC_BUTT; uc_ac_loop++)
    {
       pst_mac_user->st_ts_info[uc_ac_loop].uc_up            = WLAN_WME_AC_TO_TID(uc_ac_loop);
       pst_mac_user->st_ts_info[uc_ac_loop].en_ts_status     = MAC_TS_NONE;
       pst_mac_user->st_ts_info[uc_ac_loop].uc_vap_id        = pst_mac_user->uc_vap_id;
       pst_mac_user->st_ts_info[uc_ac_loop].us_mac_user_idx  = pst_mac_user->us_assoc_id;
       pst_mac_user->st_ts_info[uc_ac_loop].uc_tsid          = 0xFF;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_set_avail_bf_num_spatial_stream
 ��������  : ����user��������uc_avail_num_spatial_stream Tx��Rx֧��Nss�Ľ���,���㷨���õ�ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_avail_bf_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value)
{
    pst_mac_user->uc_avail_bf_num_spatial_stream = uc_value;
}

/*****************************************************************************
 �� �� ��  : mac_user_set_avail_num_spatial_stream
 ��������  : ����user��������uc_avail_num_spatial_stream Tx��Rx֧��Nss�Ľ���,���㷨���õ�ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_avail_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value)
{
    pst_mac_user->uc_avail_num_spatial_stream = uc_value;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_num_spatial_stream
 ��������  : ����user��������uc_num_spatial_stream�û�֧�ֿռ���������ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value)
{
    pst_mac_user->uc_num_spatial_stream = uc_value;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_bandwidth_cap
 ��������  : �����û���bandwidth����
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��27��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_bandwidth_cap(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bandwidth_value)
{
    pst_mac_user->en_bandwidth_cap = en_bandwidth_value;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_bandwidth_info
 ��������  : ���ÿ��ô������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��27��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��5��27��
    ��    ��   : liwenjun 68207
    �޸�����   : ���Э���л�, �Դ�����½��������ж�

*****************************************************************************/
oal_void mac_user_set_bandwidth_info(mac_user_stru *pst_mac_user,
                                                wlan_bw_cap_enum_uint8 en_avail_bandwidth,
                                                wlan_bw_cap_enum_uint8 en_cur_bandwidth)
{
    pst_mac_user->en_avail_bandwidth = en_avail_bandwidth;
    pst_mac_user->en_cur_bandwidth   = en_cur_bandwidth;

    /* Autorate��Э���11n�л���11b��, cur_bandwidth���Ϊ20M
       ��ʱ�������������Ϊ40M, cur_bandwidth����Ҫ����20M */
    if ((WLAN_LEGACY_11B_MODE == pst_mac_user->en_cur_protocol_mode) &&
        (WLAN_BW_CAP_20M != pst_mac_user->en_cur_bandwidth))
    {
        pst_mac_user->en_cur_bandwidth = WLAN_BW_CAP_20M;
    }
}

/*****************************************************************************
 �� �� ��  : mac_user_get_sta_cap_bandwidth
 ��������  : ��ȡ�û��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_user_get_sta_cap_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap)
{
    mac_user_ht_hdl_stru         *pst_mac_ht_hdl;
    mac_vht_hdl_stru             *pst_mac_vht_hdl;
    wlan_bw_cap_enum_uint8        en_bandwidth_cap;

    /* ��ȡHT��VHT�ṹ��ָ�� */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        if (0 == pst_mac_vht_hdl->bit_supported_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_80M;
        }
        else
        {
            en_bandwidth_cap = WLAN_BW_CAP_160M;
        }
    }
    else if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (1 == pst_mac_ht_hdl->bit_supported_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_40M;
        }
        else

        {
            en_bandwidth_cap = WLAN_BW_CAP_20M;
        }
    }
    else
    {
        en_bandwidth_cap = WLAN_BW_CAP_20M;
    }

    mac_user_set_bandwidth_cap(pst_mac_user, en_bandwidth_cap);

    /* ������ֵ�ɳ��δ��� */
    *pen_bandwidth_cap = en_bandwidth_cap;
}

/*****************************************************************************
 �� �� ��  : mac_user_get_ap_opern_bandwidth
 ��������  : ����AP��operation ie��ȡap�Ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_user_get_ap_opern_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap)
{
    mac_user_ht_hdl_stru         *pst_mac_ht_hdl;
    mac_vht_hdl_stru             *pst_mac_vht_hdl;
    wlan_bw_cap_enum_uint8        en_bandwidth_cap;

    /* ��ȡHT��VHT�ṹ��ָ�� */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    en_bandwidth_cap = WLAN_BW_CAP_20M;


    if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (MAC_SCN != pst_mac_ht_hdl->bit_secondary_chan_offset)
        {
            en_bandwidth_cap = WLAN_BW_CAP_40M;
        }
    }

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        /* uc_channel_width��ȡֵ��0 -- 20/40M, 1 -- 80M, 2 -- 160M */

        if (1 == pst_mac_vht_hdl->uc_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_80M;
        }
        else if (2 == pst_mac_vht_hdl->uc_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_160M;
        }
    }
    *pen_bandwidth_cap = en_bandwidth_cap;
    mac_user_set_bandwidth_cap(pst_mac_user, en_bandwidth_cap);
}
/*****************************************************************************
 �� �� ��  : mac_user_update_bandwidth
 ��������  : ����AP��operation ie��ȡap�Ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_user_update_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bwcap)
{
    mac_user_ht_hdl_stru           *pst_mac_ht_hdl;
    mac_vht_hdl_stru               *pst_mac_vht_hdl;
    ;

    if (OAL_PTR_NULL == pst_mac_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡHT��VHT�ṹ��ָ�� */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_20M;

    if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (MAC_SCN != pst_mac_ht_hdl->bit_secondary_chan_offset)
        {
            pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_40M;
        }
    }

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        /* uc_channel_width��ȡֵ��0 -- 20/40M, 1 -- 80M, 2 -- 160M */

        if (1 == pst_mac_vht_hdl->uc_channel_width)
        {
            pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_80M;
        }
        else if (2 == pst_mac_vht_hdl->uc_channel_width)
        {
            pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_160M;
        }
    }

    pst_mac_user->en_avail_bandwidth = OAL_MIN(en_bwcap, pst_mac_user->en_bandwidth_cap);
    pst_mac_user->en_cur_bandwidth   = pst_mac_user->en_avail_bandwidth;
    return OAL_SUCC;
}


#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 �� �� ��  : mac_user_change_info_event
 ��������  : ���û�״̬���������仯����Ϣ�ϱ�
 �������  : auc_user_macaddr: �û�mac��ַ
             uc_vap_id       : ��Ϊvap��vap_id
             ul_val_old      : �仯ǰ��ֵ
             ul_val_new      : �仯���ֵ
             en_mod          : ģ���
             en_type         : ��һ����Ϣ�仯
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_user_change_info_event(
                                    oal_uint8  auc_user_macaddr[],
                                    oal_uint8  uc_vap_id,
                                    oal_uint32 ul_val_old,
                                    oal_uint32 ul_val_new,
                                    oam_module_id_enum_uint16 en_mod,
                                    oam_user_info_change_type_enum_uint8 en_type)
{

    oal_uint8       auc_event_info[OAM_EVENT_INFO_MAX_LEN] = {0};
    oam_user_info_change_stru  *pst_change_info;

    pst_change_info = (oam_user_info_change_stru *)auc_event_info;
    pst_change_info->en_change_type = en_type;
    pst_change_info->ul_val_before_change = ul_val_old;
    pst_change_info->ul_val_after_change  = ul_val_new;

    oam_event_report(auc_user_macaddr, uc_vap_id, en_mod, OAM_EVENT_USER_INFO_CHANGE, auc_event_info);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : mac_user_set_assoc_id
 ��������  : ����user��assoc id
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_assoc_id(mac_user_stru *pst_mac_user, oal_uint16 us_assoc_id)
{
    pst_mac_user->us_assoc_id = us_assoc_id;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_avail_protocol_mode
 ��������  : ��ֻmac user�е�user��vapЭ��ģʽ�Ľ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_coid
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_avail_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_avail_protocol_mode)
{
    pst_mac_user->en_avail_protocol_mode = en_avail_protocol_mode;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_cur_protocol_mode
 ��������  : ����mac user�е�cur_protocol_mode
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_coid
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_cur_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_cur_protocol_mode)
{
    pst_mac_user->en_cur_protocol_mode = en_cur_protocol_mode;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_cur_bandwidth
 ��������  : ����mac user�еĴ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_user_set_cur_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8  en_cur_bandwidth)
{
    pst_mac_user->en_cur_bandwidth = en_cur_bandwidth;
}

/*****************************************************************************
 �� �� ��  : mac_user_set_avail_protocol_mode
 ��������  : ��ֻmac user�е�user��vapЭ��ģʽ�Ľ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_coid
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_protocol_mode)
{
    pst_mac_user->en_protocol_mode = en_protocol_mode;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_asoc_state
 ��������  : ����en_user_asoc_state ��ͳһ�ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��3��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_asoc_state(mac_user_stru *pst_mac_user, mac_user_asoc_state_enum_uint8 en_value)
{
    pst_mac_user->en_user_asoc_state = en_value;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_avail_op_rates
 ��������  : ����user�¿������ʼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��5��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_avail_op_rates(mac_user_stru *pst_mac_user, oal_uint8 uc_rs_nrates, oal_uint8 *puc_rs_rates)
{
    pst_mac_user->st_avail_op_rates.uc_rs_nrates = uc_rs_nrates;
    oal_memcopy(pst_mac_user->st_avail_op_rates.auc_rs_rates, puc_rs_rates, WLAN_RATE_MAXSIZE);
}
/*****************************************************************************
 �� �� ��  : mac_user_set_vht_hdl
 ��������  : ���û���vht��Ϣ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_vht_hdl)
{
   oal_memcopy((oal_uint8 *)(&pst_mac_user->st_vht_hdl), (oal_uint8 *)pst_vht_hdl, OAL_SIZEOF(mac_vht_hdl_stru));
}
/*****************************************************************************
 �� �� ��  : mac_user_get_vht_hdl
 ��������  : ��ȡ�û���vht��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_get_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_vht_hdl)
{
    oal_memcopy((oal_uint8 *)pst_vht_hdl, (oal_uint8 *)(&pst_mac_user->st_vht_hdl), OAL_SIZEOF(mac_vht_hdl_stru));
}

/*****************************************************************************
 �� �� ��  : mac_user_set_vht_hdl
 ��������  : ���û���vht��Ϣ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl)
{
   oal_memcopy((oal_uint8 *)(&pst_mac_user->st_ht_hdl), (oal_uint8 *)pst_ht_hdl, OAL_SIZEOF(mac_user_ht_hdl_stru));
}
/*****************************************************************************
 �� �� ��  : mac_user_get_ht_hdl
 ��������  : ��ȡ�û���ht��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_get_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl)
{
    oal_memcopy((oal_uint8 *)pst_ht_hdl, (oal_uint8 *)(&pst_mac_user->st_ht_hdl), OAL_SIZEOF(mac_user_ht_hdl_stru));
}
/*****************************************************************************
 �� �� ��  : mac_user_set_ht_capable
 ��������  : ����ht cap��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��7��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_ht_capable(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_ht_capable)
{
    pst_mac_user->st_ht_hdl.en_ht_capable = en_ht_capable;
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : mac_user_set_sm_power_save
 ��������  : �����û���ht������sm_power_save����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_sm_power_save(mac_user_stru *pst_mac_user, oal_uint8 uc_sm_power_save)
{
    pst_mac_user->st_ht_hdl.bit_sm_power_save = uc_sm_power_save;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_user_set_pmf_active
 ��������  : �������û�pmf����Э�̵Ľ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��11��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_pmf_active(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_pmf_active)
{
    pst_mac_user->st_cap_info.bit_pmf_active = en_pmf_active;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_barker_preamble_mode
 ��������  : �����û�barker_preamble��ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��11��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_barker_preamble_mode(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_barker_preamble_mode)
{
    pst_mac_user->st_cap_info.bit_barker_preamble_mode = en_barker_preamble_mode;
}

/*****************************************************************************
 �� �� ��  : mac_user_set_qos
 ��������  : �������û���qosʹ�ܽ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��11��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_qos(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_qos_mode)
{
    pst_mac_user->st_cap_info.bit_qos = en_qos_mode;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_spectrum_mgmt
 ��������  : ���ø����û�bit_spectrum_mgmt��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��11��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_user_set_spectrum_mgmt(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_spectrum_mgmt)
{
    pst_mac_user->st_cap_info.bit_spectrum_mgmt = en_spectrum_mgmt;
}
/*****************************************************************************
 �� �� ��  : mac_user_set_apsd
 ��������  : �����û����������bit_apsd����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_user_set_apsd(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_apsd)
{
    pst_mac_user->st_cap_info.bit_apsd = en_apsd;
}
/*****************************************************************************
 �� �� ��  : mac_user_update_wep_key
 ��������  : �����û�wep������Կ��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��26��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_user_update_wep_key(mac_user_stru *pst_mac_usr, oal_uint16 us_multi_user_idx)
{
    mac_user_stru        *pst_multi_user   = OAL_PTR_NULL;

    MAC_11I_ASSERT(OAL_PTR_NULL != pst_mac_usr, OAL_ERR_CODE_PTR_NULL);

    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    if (pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_104 &&
        pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_40)
    {

        OAM_ERROR_LOG1(0, OAM_SF_WPA, "{mac_wep_add_usr_key::en_cipher_type==%d}",
                       pst_multi_user->st_key_info.en_cipher_type);
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    if (pst_multi_user->st_key_info.uc_default_index >= WLAN_MAX_WEP_KEY_COUNT)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    /* wep�����£������鲥�û�����Կ��Ϣ�������û� */
    oal_memcopy(&pst_mac_usr->st_key_info, &pst_multi_user->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));

    /* TBD ������ϢҪŲ��ȥ */
    pst_mac_usr->st_user_tx_info.st_security.en_cipher_key_type = pst_mac_usr->st_key_info.uc_default_index + HAL_KEY_TYPE_PTK;//��ȡWEP default key id

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_addr_is_zero
 ��������  : �ж�mac��ַ�Ƿ�ȫ0
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_addr_is_zero(oal_uint8 *puc_mac)
{
    oal_uint8    auc_mac_zero[OAL_MAC_ADDR_LEN] = {0};

    MAC_11I_ASSERT((OAL_PTR_NULL != puc_mac), OAL_TRUE);

    return (0 == oal_memcmp(auc_mac_zero, puc_mac, OAL_MAC_ADDR_LEN));
}

/*****************************************************************************
 �� �� ��  : mac_res_get_mac_user
 ��������  : ��ȡ��ӦMAC USER�������ڴ�
 �������  : ��ӦMAC USER�ڴ�����
 �������  : ��
 �� �� ֵ  : ��Ӧ�ڴ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : lingxuemeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void*  mac_res_get_mac_user(oal_uint16 us_idx)
{
    mac_user_stru*    pst_mac_user;

    pst_mac_user = (mac_user_stru*)_mac_res_get_mac_user(us_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        return OAL_PTR_NULL;
    }

    /* �쳣: �û���Դ�ѱ��ͷ� */ /* user id=0Ϊ����user,������Ϊ0 */
    if ((MAC_USER_ALLOCED != pst_mac_user->uc_is_user_alloced) && (0 != us_idx))
    {
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        /*lint -e718*//*lint -e746*/
        OAM_WARNING_LOG2(0, OAM_SF_UM, "{mac_res_get_mac_user::[E]user has been freed,user_idx=%d, func[%x].}", us_idx, (oal_uint32)__return_address());
        /*lint +e718*//*lint +e746*/
#else
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{mac_res_get_mac_user::[E]user has been freed,user_idx=%d.}", us_idx);
#endif
        //return OAL_PTR_NULL;
    }

    return  (void*)pst_mac_user;
}


/*lint -e19*/

oal_module_symbol(mac_user_get_key);

oal_module_symbol(mac_user_set_port);

oal_module_symbol(mac_user_set_key);
oal_module_symbol(mac_user_init);
oal_module_symbol(mac_user_set_avail_num_spatial_stream);
oal_module_symbol(mac_user_set_num_spatial_stream);
oal_module_symbol(mac_user_set_bandwidth_cap);
oal_module_symbol(mac_user_get_sta_cap_bandwidth);
oal_module_symbol(mac_user_get_ap_opern_bandwidth);

#ifdef _PRE_DEBUG_MODE_USER_TRACK
oal_module_symbol(mac_user_change_info_event);
#endif

oal_module_symbol(mac_user_set_bandwidth_info);
oal_module_symbol(mac_user_set_assoc_id);
oal_module_symbol(mac_user_set_protocol_mode);
oal_module_symbol(mac_user_set_avail_protocol_mode);
oal_module_symbol(mac_user_set_cur_protocol_mode);
oal_module_symbol(mac_user_set_cur_bandwidth);

oal_module_symbol(mac_user_avail_bf_num_spatial_stream);
oal_module_symbol(mac_user_set_asoc_state);
oal_module_symbol(mac_user_set_avail_op_rates);
oal_module_symbol(mac_user_set_vht_hdl);
oal_module_symbol(mac_user_get_vht_hdl);
oal_module_symbol(mac_user_set_ht_hdl);
oal_module_symbol(mac_user_get_ht_hdl);
oal_module_symbol(mac_user_set_ht_capable);
#ifdef _PRE_WLAN_FEATURE_SMPS
oal_module_symbol(mac_user_set_sm_power_save);
#endif
oal_module_symbol(mac_user_set_pmf_active);
oal_module_symbol(mac_user_set_barker_preamble_mode);
oal_module_symbol(mac_user_set_qos);
oal_module_symbol(mac_user_set_spectrum_mgmt);
oal_module_symbol(mac_user_set_apsd);

oal_module_symbol(mac_user_init_key);
oal_module_symbol(mac_user_update_wep_key);
oal_module_symbol(mac_addr_is_zero);
oal_module_symbol(mac_res_get_mac_user);
/*lint +e19*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

