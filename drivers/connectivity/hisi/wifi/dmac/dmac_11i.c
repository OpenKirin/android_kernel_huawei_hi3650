/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_11i.c
  �� �� ��   : ����
  ��    ��   : louyueyun
  ��������   : 2013��8��15��
  ����޸�   :
  ��������   : 11i DMAC���ܴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��8��15��
    ��    ��   : louyueyun
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
#include "oal_list.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_resource.h"
#include "wlan_types.h"
#include "mac_vap.h"
#include "mac_user.h"
//#include "mac_11i.h"
#include "dmac_main.h"
#include "oal_net.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_mgmt_ap.h"
#include "dmac_11i.h"
#include "dmac_wep.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_11I_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define MAC_ADDR(_puc_mac)   ((oal_uint32)(((oal_uint32)_puc_mac[2] << 24) |\
                                                  ((oal_uint32)_puc_mac[3] << 16) |\
                                                  ((oal_uint32)_puc_mac[4] << 8) |\
                                                  ((oal_uint32)_puc_mac[5])))

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_check_igtk_exist
 ��������  : ͨ��igtk index���igtk�Ƿ����
 �������  : uc_igtk_index : igtk��indexֵ
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :
            <����Hi1102 Device�ڴ����ޣ���ʱɾ��aes.c/h,oam_config.c/h�ļ������Դ˺������Ƶ��˴���
            ԭ��Ϊoal_check_igtk_exist>
 �޸���ʷ      :
  1.��    ��   : 2014��5��3��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_check_igtk_exist(oal_uint8 uc_igtk_index)
{
    /* igtk��key index Ϊ4��5 */
    if ((WLAN_MAX_IGTK_KEY_INDEX < uc_igtk_index) ||
        ((WLAN_MAX_IGTK_KEY_INDEX - WLAN_NUM_IGTK) >= uc_igtk_index))
    {
        return OAL_ERR_CODE_PMF_IGTK_NOT_EXIST;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_update_key_to_ce
 ��������  : ����������Կд�Ĵ����ӿڣ���һ����Կд��Ӳ��Lut��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_update_key_to_ce(mac_vap_stru *pst_mac_vap, hal_security_key_stru *pst_key, oal_uint8 *puc_addr)
{
    dmac_vap_stru           *pst_dmac_vap;

    /*2.1 ��ȡdmac_vap*/
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_key))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /* ��Ҫ��Ϣ��ӡwarning */
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_update_key_to_ce::keyid=%u, keytype=%u,lutidx=%u,cipher=%u}",
                     pst_key->uc_key_id, pst_key->en_key_type, pst_key->uc_lut_idx, pst_key->en_cipher_type);
    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_update_key_to_ce::en_update_key=%u, en_key_origin=%u}",
                     pst_key->en_update_key, pst_key->en_key_origin);

    /* 3.1 дӲ���Ĵ���   */
    hal_ce_add_key(pst_dmac_vap->pst_hal_device, pst_key, puc_addr);

#ifdef _PRE_WLAN_INIT_PTK_TX_PN
    /* 3.2 ��ʼ��TX PN */
    hal_init_ptk_tx_pn(pst_dmac_vap->pst_hal_device, pst_key);
    dmac_init_iv_word_lut(pst_dmac_vap->pst_hal_device, pst_key);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_del_key_to_ce
 ��������  : ��һ����Կ��Ӳ��LUT����ɾ��
 �������  :
 �������  : oal_uint32
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_del_key_to_ce(mac_vap_stru                   *pst_mac_vap,
                                            oal_uint8                       uc_key_id,
                                            hal_cipher_key_type_enum_uint8  en_key_type,
                                            oal_uint8                       uc_lut_index)
{
    hal_security_key_stru    st_security_key    = {0};
    dmac_vap_stru           *pst_dmac_vap       = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    st_security_key.uc_key_id      = uc_key_id;
    st_security_key.en_key_type    = en_key_type;
    st_security_key.uc_lut_idx     = uc_lut_index;
    st_security_key.en_update_key  = OAL_TRUE;
    st_security_key.puc_cipher_key = OAL_PTR_NULL;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;

    /* ��Ҫ��Ϣ��ӡwarning */
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                     "{dmac_11i_del_key_to_ce::keyid=%u, keytype=%u,lutidx=%u}", uc_key_id, en_key_type, uc_lut_index);

    /* дӲ���Ĵ���   */
    hal_ce_del_key(pst_dmac_vap->pst_hal_device, &st_security_key);

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    /*�����鲥��ԿӦ��ɾ��2��*/
    if ((HAL_KEY_TYPE_RX_GTK == en_key_type) || (HAL_KEY_TYPE_RX_GTK2 == en_key_type))
    {
        st_security_key.en_key_type = (HAL_KEY_TYPE_RX_GTK == en_key_type) ? HAL_KEY_TYPE_RX_GTK2 : HAL_KEY_TYPE_RX_GTK;
        OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                         "{dmac_11i_del_key_to_ce::keyid=%u, keytype=%u,lutidx=%u}", uc_key_id, en_key_type, uc_lut_index);
        hal_ce_del_key(pst_dmac_vap->pst_hal_device, &st_security_key);
    }
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_11i_get_auth_type
 ��������  : ����vap����ȡ��֤����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC hal_key_origin_enum_uint8 dmac_11i_get_auth_type(mac_vap_stru *pst_mac_vap)
{
    if (IS_AP(pst_mac_vap))
    {
        return HAL_AUTH_KEY;
    }
    return HAL_SUPP_KEY;
}
/*****************************************************************************
 �� �� ��  : dmac_11i_get_key_type
 ��������  : ����vap����ȡ��Կ����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC hal_cipher_key_type_enum_uint8 dmac_11i_get_gtk_key_type(mac_vap_stru *pst_mac_vap, wlan_ciper_protocol_type_enum_uint8 en_cipher_type)
{
    oal_uint8           uc_rx_gtk        = HAL_KEY_TYPE_RX_GTK;
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
    mac_user_stru      *pst_multi_user   = OAL_PTR_NULL;
#endif
    if (IS_AP(pst_mac_vap) && (WLAN_80211_CIPHER_SUITE_BIP != en_cipher_type))
    {
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
        /* 1102 �鲥����֡��Կ��key type���͸ı� */
        return HAL_KEY_TYPE_RX_GTK;
#else
        return HAL_KEY_TYPE_TX_GTK;
#endif
    }

#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))

    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_get_gtk_key_type::mac_res_get_mac_user null.}");
        return HAL_KEY_TYPE_TX_GTK;
    }

    if (WLAN_80211_CIPHER_SUITE_BIP == en_cipher_type)
    {
        /* Hi1102: HAL_KEY_TYPE_IGTK */
        uc_rx_gtk = HAL_KEY_TYPE_TX_GTK;
    }
    else if (0 == pst_multi_user->st_key_info.bit_gtk)
    {
        uc_rx_gtk = HAL_KEY_TYPE_RX_GTK;
        //pst_mac_vap->st_key_mgmt.bit_gtk = 1;
    }
    else
    {
        uc_rx_gtk = HAL_KEY_TYPE_RX_GTK2;
        //pst_mac_vap->st_key_mgmt.bit_gtk = 0;
    }
#endif
    return uc_rx_gtk;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_gtk_token
 ��������  : ��λgtkƹ��λ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_reset_gtk_token(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru  *pst_multi_user          = OAL_PTR_NULL;

    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_add_gtk_key::mac_res_get_mac_user[%d] null.}", pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    pst_multi_user->st_key_info.bit_gtk = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_del_peer_macaddr
 ��������  : ��һ����Կ��Ӳ��LUT����ɾ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : louyueyun 218984
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_del_peer_macaddr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_lut_index)
{
    dmac_vap_stru           *pst_dmac_vap       = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /* дӲ���Ĵ���   */
    hal_ce_del_peer_macaddr(pst_dmac_vap->pst_hal_device, uc_lut_index);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_add_ptk_key
 ��������  : ���õ�����Կ
 �������  :
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
 oal_uint32  dmac_11i_add_ptk_key(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint8 uc_key_index)
{
    oal_uint32                          ul_ret;
    dmac_user_stru                     *pst_current_dmac_user                  = OAL_PTR_NULL;
    mac_user_stru                      *pst_current_mac_user                   = OAL_PTR_NULL;
    wlan_priv_key_param_stru           *pst_key                                = OAL_PTR_NULL;
    oal_uint8                           auc_mic_key[WLAN_TEMPORAL_KEY_LENGTH]  = {0};
    oal_uint16                          us_user_idx                            = 0;
    hal_security_key_stru               st_security_key;

    /*1.0 ptk index ��� */
    if(uc_key_index >= WLAN_NUM_TK)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }
    if (OAL_PTR_NULL == puc_mac_addr)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.1 ����mac��ַ�ҵ�user����*/
    pst_current_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, puc_mac_addr);
    if (OAL_PTR_NULL == pst_current_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_ptk_key::pst_current_dmac_user null.}");

        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    pst_current_mac_user = &pst_current_dmac_user->st_user_base_info;

    /*2.1 ����׼��*/
    pst_key = &pst_current_mac_user->st_key_info.ast_key[uc_key_index];
    if ((WLAN_80211_CIPHER_SUITE_TKIP !=(oal_uint8)pst_key->ul_cipher)
        && (WLAN_80211_CIPHER_SUITE_CCMP != (oal_uint8)pst_key->ul_cipher))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_ptk_key::invalid chiper type[%d], uc_key_index=%d.}", uc_key_index, pst_key->ul_cipher);

        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    st_security_key.uc_key_id      = uc_key_index;
    st_security_key.en_key_type    = HAL_KEY_TYPE_PTK;
    st_security_key.en_key_origin  = dmac_11i_get_auth_type(pst_mac_vap);
    st_security_key.en_update_key  = OAL_TRUE;
    st_security_key.uc_lut_idx     = pst_current_dmac_user->uc_lut_index;
    st_security_key.en_cipher_type = pst_current_mac_user->st_key_info.en_cipher_type;
    st_security_key.puc_cipher_key = pst_key->auc_key;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;



    if (WLAN_TEMPORAL_KEY_LENGTH < pst_key->ul_key_len)
    {
        st_security_key.puc_mic_key = auc_mic_key;
        /* ����TKIPģʽ��MIC����txrx����bit˳����������Ҫת��˳��*/
        if ((WLAN_80211_CIPHER_SUITE_TKIP == st_security_key.en_cipher_type) && (IS_STA(pst_mac_vap)))
        {
            oal_memcopy(auc_mic_key, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH + WLAN_MIC_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
            oal_memcopy(auc_mic_key + WLAN_MIC_KEY_LENGTH, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
        }
        else
        {
            oal_memcopy(auc_mic_key, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
            oal_memcopy(auc_mic_key + WLAN_MIC_KEY_LENGTH, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH + WLAN_MIC_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
        }
    }

    /*3.1 �û����MIB��Ϣ����*/
    us_user_idx = pst_current_mac_user->us_assoc_id;
    mibset_RSNAStatsSTAAddress(puc_mac_addr,pst_mac_vap, us_user_idx);
    mibset_RSNAStatsSelectedPairwiseCipher(pst_current_mac_user->st_key_info.en_cipher_type, pst_mac_vap, us_user_idx);
    mac_mib_set_RSNAPairwiseCipherSelected(pst_mac_vap, pst_current_mac_user->st_key_info.en_cipher_type);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_vap_is_vsta(pst_mac_vap))
    {
        puc_mac_addr = mac_mib_get_StationID(pst_mac_vap);
    }
#endif
    /* 4.1 �����ܷ�ʽ�ͼ�����Կд��CE��, ͬʱ���Ӽ����û� */
    ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, puc_mac_addr);

    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_update_key_to_ce::dmac_11i_update_key_to_ce failed[%d].}", ul_ret);

        return ul_ret;
    }


    /* �Ĵ���д��ɹ��󣬸��µ����û���Կ */
    mac_user_set_key(pst_current_mac_user, st_security_key.en_key_type, st_security_key.en_cipher_type, st_security_key.uc_key_id);

    /*5.1 ��1X�˿���֤״̬*/
    mac_user_set_port(pst_current_mac_user, OAL_TRUE);

    /*6.1 �򿪷����������ļ�������*/
    pst_current_mac_user->st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_PTK;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_11i_add_gtk_key
 ��������  : �����鲥��Կ
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_add_gtk_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    oal_uint32                          ul_ret;
    dmac_vap_stru                      *pst_dmac_vap            = OAL_PTR_NULL;
    mac_user_stru                      *pst_multi_user          = OAL_PTR_NULL;
    wlan_priv_key_param_stru           *pst_key                 = OAL_PTR_NULL;
    oal_uint8                           auc_mic_key[8]          = {0};
    hal_security_key_stru               st_security_key;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*1.1 ���������ҵ��鲥user�ڴ�����*/
    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.2 ����mac_vap��ȡdmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /*2.1 ����׼��*/
    pst_key = &pst_multi_user->st_key_info.ast_key[uc_key_index];

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_SW_BIP)

    if (WLAN_80211_CIPHER_SUITE_BIP == (oal_uint8)pst_key->ul_cipher)
    {
        /* BIP�������ɣ�����Ҫ���ø�mac*/
        return OAL_SUCC;
    }
#endif
    if (WLAN_80211_CIPHER_SUITE_TKIP != (oal_uint8)pst_key->ul_cipher
        && WLAN_80211_CIPHER_SUITE_CCMP != (oal_uint8)pst_key->ul_cipher
        && WLAN_80211_CIPHER_SUITE_BIP != (oal_uint8)pst_key->ul_cipher)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_gtk_key::invalid chiper type[%d].}", pst_key->ul_cipher);

        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /* ���AP�����鲥��Կʹ�õ�����ͬ��keyid�������鲥��Կ�۵�keyidһ�£��鲥����ʧ��
       keyidһ�£�����ԭ����Կ������������Կ */
    if (uc_key_index == pst_multi_user->st_key_info.uc_last_gtk_key_idx)
    {
        pst_multi_user->st_key_info.bit_gtk ^= BIT0; /* GTK ��λƹ��ʹ�� */
    }

    st_security_key.en_cipher_type = (oal_uint8)pst_key->ul_cipher;
    st_security_key.uc_key_id      = uc_key_index;
    st_security_key.en_key_type    = dmac_11i_get_gtk_key_type(pst_mac_vap, st_security_key.en_cipher_type);
    pst_multi_user->st_key_info.bit_gtk ^= BIT0; /* GTK ��λƹ��ʹ�� */
    pst_multi_user->st_key_info.uc_last_gtk_key_idx = uc_key_index;

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_add_gtk_key::new bit_gtk=%u, keyidx = %u.}",
                     pst_multi_user->st_key_info.bit_gtk, pst_multi_user->st_key_info.uc_last_gtk_key_idx);

    st_security_key.en_key_origin  = dmac_11i_get_auth_type(pst_mac_vap);
    st_security_key.en_update_key  = OAL_TRUE;
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    st_security_key.uc_lut_idx     = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#else
    st_security_key.uc_lut_idx     = (IS_AP(pst_mac_vap)) ? pst_dmac_vap->pst_hal_vap->uc_vap_id : 0;
#endif
    st_security_key.puc_cipher_key = pst_key->auc_key;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;
    if (WLAN_TEMPORAL_KEY_LENGTH < pst_key->ul_key_len)
    {
        st_security_key.puc_mic_key = pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH;
        /* ����TKIPģʽ��MIC����txrx����bit˳����������Ҫת��˳��*/
        if ((WLAN_80211_CIPHER_SUITE_TKIP == st_security_key.en_cipher_type) && (IS_STA(pst_mac_vap)))
        {
            oal_memcopy(auc_mic_key, st_security_key.puc_mic_key, 8);
            oal_memcopy(st_security_key.puc_mic_key, st_security_key.puc_mic_key + 8, 8);
            oal_memcopy(st_security_key.puc_mic_key + 8, auc_mic_key, 8);
        }
    }

    /*3.1 �����ܷ�ʽ�ͼ�����Կд��CE��*/
    ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_gtk_key::dmac_11i_update_key_to_ce failed[%d].}", ul_ret);

        return ul_ret;
    }

    /* ���óɹ��󣬸���һ��multiuser�еİ�ȫ��Ϣ,Ŀǰֻ��keyid�ڷ����鲥֡ʱ��ʹ�õ� */
    mac_user_set_key(pst_multi_user, st_security_key.en_key_type, st_security_key.en_cipher_type, st_security_key.uc_key_id);

    /*4.1 ��1X�˿���֤״̬*/
    mac_user_set_port(pst_multi_user, OAL_TRUE);

    /*5.1 �򿪷����������ļ�������*/
    if (WLAN_KEY_TYPE_TX_GTK == st_security_key.en_key_type)
    {
        pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_add_wep_key
 ��������  : �����鲥��Կ
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_add_wep_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    mac_user_stru                      *pst_multi_user;
    wlan_priv_key_param_stru           *pst_key                   = OAL_PTR_NULL;
    hal_security_key_stru               st_security_key;
    dmac_vap_stru                      *pst_dmac_vap              = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE != mac_is_wep_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }


    /*1.1 ���������ҵ��鲥user�ڴ�����*/
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.2 ����mac_vap��ȡdmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    if (WLAN_80211_CIPHER_SUITE_WEP_104 != pst_multi_user->st_key_info.en_cipher_type
        && WLAN_80211_CIPHER_SUITE_WEP_40 != pst_multi_user->st_key_info.en_cipher_type)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_wep_key::invalid ul_cipher type[%d].}", pst_multi_user->st_key_info.en_cipher_type);

        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }
    pst_key = &pst_multi_user->st_key_info.ast_key[uc_key_index];
    /*2.1 ����׼��*///δ����
    st_security_key.uc_key_id      = uc_key_index;
    st_security_key.en_cipher_type = pst_multi_user->st_key_info.en_cipher_type;

    st_security_key.en_key_type    = dmac_11i_get_gtk_key_type(pst_mac_vap, st_security_key.en_cipher_type);
    st_security_key.en_key_origin  = dmac_11i_get_auth_type(pst_mac_vap);
    st_security_key.en_update_key  = OAL_TRUE;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_vap_is_vsta(&pst_dmac_vap->st_vap_base_info))
    {
        if (WLAN_KEY_TYPE_PTK == st_security_key.en_key_type)
        {
            st_security_key.uc_lut_idx = dmac_vap_psta_lut_idx(pst_dmac_vap); /* Proxy STA ��Ҫ��lut idx���� */
        }
        else
        {
            st_security_key.uc_lut_idx = 0; /* Proxy STA ��Ҫ��lut idx���� */
        }
    }
    else if(mac_vap_is_msta(&pst_dmac_vap->st_vap_base_info))
    {
        st_security_key.uc_lut_idx = pst_dmac_vap->pst_hal_vap->uc_vap_id;
        if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode && WLAN_KEY_TYPE_RX_GTK == st_security_key.en_key_type)
        {
            /* sta0��rx gtk��lut idxΪ0 */
            st_security_key.uc_lut_idx = 0;
        }
    }
    else
#endif
    {
        st_security_key.uc_lut_idx = pst_dmac_vap->pst_hal_vap->uc_vap_id;
    }
    st_security_key.puc_cipher_key = pst_key->auc_key;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;

    /*3.1 �����ܷ�ʽ�ͼ�����Կд��CE��*/
    if (OAL_SUCC != dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, OAL_PTR_NULL))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_wep_key::dmac_11i_update_key_to_ce invalid.}");

        return OAL_FAIL;
    }

    /*5.1 �򿪷����������ļ�������*/
    if (WLAN_KEY_TYPE_TX_GTK == st_security_key.en_key_type)
    {
        pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_TX_GTK;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_del_ptk_key
 ��������  : ɾ��������Կ
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_11i_del_ptk_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index, oal_uint8 *puc_mac_addr)
{
    oal_uint32                          ul_ret;
    dmac_user_stru                     *pst_current_dmac_user     = OAL_PTR_NULL;
    oal_uint8                           uc_key_id;
    oal_uint8                           uc_ce_lut_index;
    hal_cipher_key_type_enum_uint8      en_key_type;

    /*1.1 ����mac��ַ�ҵ�user����*/
    pst_current_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, puc_mac_addr);
    if (OAL_PTR_NULL == pst_current_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_WPA, "{dmac_11i_del_ptk_key::mac_vap_find_user_by_macaddr failed.}");
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*2.1 ����׼��*/
    en_key_type     = HAL_KEY_TYPE_PTK;
    uc_key_id       = uc_key_index;
    uc_ce_lut_index = pst_current_dmac_user->uc_lut_index;

    /*3.2 ɾ��CE�еĶ�Ӧ��Կ*/
    ul_ret = dmac_11i_del_key_to_ce(pst_mac_vap, uc_key_id, en_key_type, uc_ce_lut_index);
    if (OAL_SUCC != ul_ret)
    {//weifugai
        OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_11i_del_ptk_key::dmac_11i_del_key_to_cefailed[%d],uc_key_id=%d en_key_type=%d uc_ce_lut_index=%d.}",
                       ul_ret, uc_key_id, en_key_type, uc_ce_lut_index);

        return ul_ret;
    }

    /*4.1 �ر�1X�˿���֤״̬*/
    mac_user_set_port(&pst_current_dmac_user->st_user_base_info, OAL_FALSE);
    /* ��ʼ���û�����Կ��Ϣ */
    mac_user_init_key(&pst_current_dmac_user->st_user_base_info);

    /*5.1 �رշ����������ļ�������*/
    pst_current_dmac_user->st_user_base_info.st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_BUTT;


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_del_gtk_key
 ��������  : ɾ���鲥��Կ
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_11i_del_gtk_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    oal_uint32                          ul_ret;
    dmac_vap_stru                      *pst_dmac_vap;
    mac_user_stru                      *pst_current_mac_user;
    oal_uint8                           uc_key_id;
    oal_uint8                           uc_ce_lut_index;
    hal_cipher_key_type_enum_uint8      en_key_type;

    if(OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*1.1 ���������ҵ��鲥user�ڴ�����*/
    pst_current_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if(OAL_PTR_NULL == pst_current_mac_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.2 ����mac_vap��ȡdmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    /*2.1 ����׼��*/
    uc_key_id = 0;
    en_key_type = dmac_11i_get_gtk_key_type(pst_mac_vap, pst_current_mac_user->st_key_info.en_cipher_type);
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    uc_ce_lut_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#else
    uc_ce_lut_index = (IS_AP(pst_mac_vap)) ? pst_dmac_vap->pst_hal_vap->uc_vap_id : 0;
#endif

    /*3.1 ɾ��CE�еĶ�Ӧ��Կ*/
    ul_ret = dmac_11i_del_key_to_ce(pst_mac_vap, uc_key_id, en_key_type, uc_ce_lut_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_11i_del_gtk_key::dmac_11i_del_key_to_ce[%d],uc_key_id=%d en_key_type=%d uc_ce_lut_index=%d.}",
                       ul_ret, uc_key_id, en_key_type, uc_ce_lut_index);

        return ul_ret;
    }

    /*4.1 �ر�1X�˿���֤״̬*/
    mac_user_set_port(pst_current_mac_user, OAL_FALSE);
    mac_user_init_key(pst_current_mac_user);

    /*5.1 �رշ����������ļ�������*/
    if (HAL_KEY_TYPE_TX_GTK == en_key_type)
    {
        pst_current_mac_user->st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_BUTT;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_add_key_from_user
 ��������  : �����û��ļ����׼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_add_key_from_user(mac_vap_stru *pst_mac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint8                           uc_key_id;
    oal_uint8                          *puc_cipkey;
    oal_uint8                          *puc_mickey;
    oal_uint8                           en_auth_supp;
    oal_uint32                          ul_ret;
    hal_security_key_stru               st_security_key;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == pst_dmac_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        en_auth_supp = HAL_AUTH_KEY;
    }
    else
    {
        en_auth_supp = HAL_SUPP_KEY;
    }

    /* wep����ʱ����Ҫ�ָ�PTK��Կ */
    if(OAL_TRUE == mac_is_wep_allowed(pst_mac_vap))
    {
        return OAL_SUCC;
    }


    for(uc_key_id=0; uc_key_id <= pst_dmac_user->uc_max_key_index; uc_key_id++)
    {
        puc_cipkey = pst_dmac_user->st_user_base_info.st_key_info.ast_key[uc_key_id].auc_key;        /* ǰ16�ֽ���cipherkey */
        puc_mickey = pst_dmac_user->st_user_base_info.st_key_info.ast_key[uc_key_id].auc_key + 16;   /* ��16�ֽ���mickey */

        st_security_key.uc_key_id      = uc_key_id;
        st_security_key.en_key_type    = HAL_KEY_TYPE_PTK;
        st_security_key.en_key_origin  = en_auth_supp;
        st_security_key.en_update_key  = OAL_TRUE;
        st_security_key.uc_lut_idx     = pst_dmac_user->uc_lut_index;
        st_security_key.en_cipher_type = pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type;
        st_security_key.puc_cipher_key = puc_cipkey;
        st_security_key.puc_mic_key    = puc_mickey;

        ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, pst_dmac_user->st_user_base_info.auc_user_mac_addr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_11i_add_key_from_user::dmac_11i_update_key_to_ce failed[%d].}", ul_ret);

            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_remove_key_from_user
 ��������  : ɾ���û������׼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_11i_remove_key_from_user(mac_vap_stru *pst_mac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint8   uc_key_id;
    oal_uint32  ul_ret;

    /*ֻ��Ҫɾ��TIKP/CCMP������Կ*/
    switch (pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type)
    {
        case WLAN_80211_CIPHER_SUITE_GROUP_CIPHER:
        case WLAN_80211_CIPHER_SUITE_WEP_40:
        case WLAN_80211_CIPHER_SUITE_NO_ENCRYP:
        case WLAN_80211_CIPHER_SUITE_WEP_104:
        case WLAN_80211_CIPHER_SUITE_BIP:
        case WLAN_80211_CIPHER_SUITE_GROUP_DENYD:
        {
            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_11i_remove_key_from_user::cipher type=%d.}", pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type);
            break;
        }
        case WLAN_80211_CIPHER_SUITE_TKIP:
        case WLAN_80211_CIPHER_SUITE_CCMP:
        {
            for(uc_key_id=0; uc_key_id <= pst_dmac_user->uc_max_key_index; uc_key_id++)
            {
                ul_ret = dmac_11i_del_key_to_ce(pst_mac_vap, uc_key_id, HAL_KEY_TYPE_PTK, pst_dmac_user->uc_lut_index);
                if (OAL_SUCC != ul_ret)
                {//weifugai
                    OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                                   "{dmac_11i_remove_key_from_user::dmac_11i_del_key_to_ce failed[%d], uc_key_id=%d uc_lut_index=%d.}",
                                   ul_ret, uc_key_id, pst_dmac_user->uc_lut_index);
                }
            }
            break;
        }
        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_11i_remove_key_from_user::invalid cipher type[%d].}", pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type);

            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_11i_init_port
 ��������  : ��ʼ��port
 �������  :
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_config_11i_init_port(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_user_stru                               *pst_mac_user;

    MAC_11I_ASSERT(OAL_PTR_NULL != pst_mac_vap, OAL_ERR_CODE_PTR_NULL);

    /* ����mac�ҵ���ӦAP USER�ṹ */
    pst_mac_user = mac_vap_get_user_by_addr(pst_mac_vap, puc_param);
    MAC_11I_ASSERT(OAL_PTR_NULL != pst_mac_user, OAL_ERR_CODE_PTR_NULL);

    mac_vap_init_user_security_port(pst_mac_vap, pst_mac_user);
#endif
    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_config_11i_add_key_set_reg
 ��������  : add key ����
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_11i_add_key_set_reg(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index, oal_uint8 *puc_mac_addr)
{
    oal_uint32                            ul_ret;

    /*1.1 ��μ��*/
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 ����ǵ�������Ҫ����PTK*/
    if (OAL_PTR_NULL != puc_mac_addr)
    {
        ul_ret = dmac_11i_add_ptk_key(pst_mac_vap, puc_mac_addr, uc_key_index);
    }
    /*2.2 ������鲥����Ҫ����GTK*/
    else
    {
        ul_ret = dmac_11i_add_gtk_key(pst_mac_vap, uc_key_index);
    }
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_config_11i_add_key
 ��������  : add key����key,��Ҫ���¼Ĵ�������ص�mib��������������
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  :
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :
 ����˵��  :1.����1102 hmac2dmac��ʵ�壬Ŀǰһ���¼��ڴ��ԼΪ52�ֽڣ�����addkey
                �¼�����ֳ������¼��·���
            2.���ڿ�ʵ�壬hmac�����ݱ���ͬ����dmac��
 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_11i_add_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32                       ul_ret;
    mac_addkey_param_stru           *pst_payload_addkey_params;
    oal_uint8                       *puc_mac_addr;
    oal_uint8                        uc_key_index;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_stru                   *pst_mac_user;
    mac_key_params_stru             *pst_key;
    oal_uint16                       us_user_idx;
#endif
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_config_11i_add_key::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 ��ȡ����*/
    pst_payload_addkey_params = (mac_addkey_param_stru *)puc_param;
    uc_key_index = pst_payload_addkey_params->uc_key_index;
    puc_mac_addr = (oal_uint8*)pst_payload_addkey_params->auc_mac_addr;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    pst_key      = &(pst_payload_addkey_params->st_key);

    /*2.2 ����ֵ���ֵ���*/
    if(uc_key_index >= WLAN_NUM_TK + WLAN_NUM_IGTK)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::invalid uc_key_index[%d].}", uc_key_index);
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }


    /*2.3 ��Կ����ָ�벻��Ϊ��*/
    if (OAL_PTR_NULL == pst_key)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::pst_params null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_payload_addkey_params->en_pairwise)
    {
        /* ������Կ����ڵ����û��� */
        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::find_user_by_macaddr fail[%d].}", ul_ret);
            return ul_ret;
        }
    }
    else
    {
        /* �鲥��Կ������鲥�û��� */
        us_user_idx  = pst_mac_vap->us_multi_user_idx;
    }

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::get_mac_user null.}");
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*3.1 ���������Ը��µ��û���*/
    ul_ret = mac_vap_add_key(pst_mac_vap, pst_mac_user, uc_key_index, pst_key);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{hmac_config_11i_add_key::mac_11i_add_key fail[%d].}", ul_ret);
        return ul_ret;
    }

#endif /* #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) */

    /* WEPģʽ�²���Ҫ��addkey�������üĴ��� */
    if (OAL_TRUE == mac_is_wep_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    if (OAL_FALSE == pst_payload_addkey_params->en_pairwise)
    {
        puc_mac_addr = OAL_PTR_NULL;
    }

    /* ����Ӳ���Ĵ��� */
    ul_ret = dmac_config_11i_add_key_set_reg(pst_mac_vap, uc_key_index, puc_mac_addr);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::set_reg fail[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_WAPI
/*****************************************************************************
 �� �� ��  : dmac_config_wapi_add_key
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 ����˵��  :1.
 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_wapi_add_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru       *pst_dmac_vap;

    /*1.2 ����mac_vap��ȡdmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_wapi_add_key::pst_dmac_vap null.}");
        return OAL_FAIL;
    }

    /* �ص�Ӳ���ļӽ��ܹ��� */
    hal_disable_ce(pst_dmac_vap->pst_hal_device);

    return OAL_SUCC;
}

#endif



/*****************************************************************************
 �� �� ��  : dmac_config_11i_remove_key
 ��������  : remove key
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��4��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_config_11i_remove_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32                       ul_ret;
    oal_uint8                        uc_key_index;
    oal_bool_enum_uint8              en_pairwise;
    oal_uint8                       *puc_mac_addr = OAL_PTR_NULL;
    mac_removekey_param_stru        *pst_removekey_params         = OAL_PTR_NULL;

    /*1.1 ��μ��*/
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_config_11i_remove_key::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 ��ȡ����*/
    pst_removekey_params = (mac_removekey_param_stru *)puc_param;
    uc_key_index = pst_removekey_params->uc_key_index;
    en_pairwise  = pst_removekey_params->en_pairwise;
    puc_mac_addr = (oal_uint8*)pst_removekey_params->auc_mac_addr;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_vap_is_vsta(pst_mac_vap) &&(OAL_FALSE == en_pairwise))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_11i_remove_key::proxysta vsta donot need remove multi GTK.}");
        return OAL_SUCC;
    }
#endif

    /*3.1 ����ǵ���*/
    if((OAL_TRUE != mac_addr_is_zero(puc_mac_addr)) && (OAL_TRUE == en_pairwise))
    {
        ul_ret = dmac_11i_del_ptk_key(pst_mac_vap, uc_key_index, puc_mac_addr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_config_11i_remove_key::dmac_11i_del_ptk_key failed[%d].}", ul_ret);

            return ul_ret;
        }
    }
    /*3.2 ������鲥*/
    else
    {
        ul_ret = dmac_11i_del_gtk_key(pst_mac_vap, uc_key_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_config_11i_remove_key::dmac_11i_del_gtk_key failed[%d].}", ul_ret);

            return ul_ret;
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_set_default_key
 ��������  : set deault key �߼�����
 �������  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

2.��    ��   : 2014��11��25��
  ��    ��   : ��ʹ���ø��¼Ĵ�����02Ҳ��Ҫͬ��hmac�����ã���˰� �Ǽ����׼���
                �ж�Ų��dmac
  �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  dmac_config_11i_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_setdefaultkey_param_stru    *pst_defaultkey_params = OAL_PTR_NULL;
    oal_uint32                       ul_ret;
    oal_uint8                        uc_key_index;
    oal_bool_enum_uint8              en_unicast;
    oal_bool_enum_uint8              en_multicast;

    /*1.1 ��μ��*/
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_config_11i_set_default_key::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 ��ȡ����*/
    pst_defaultkey_params = (mac_setdefaultkey_param_stru *)puc_param;
    uc_key_index = pst_defaultkey_params->uc_key_index;

    /*2.2 ����ֵ���ֵ���*/
    if(uc_key_index >= (WLAN_NUM_TK + WLAN_NUM_IGTK))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_config_11i_set_default_key::invalid uc_key_index[%d].}", uc_key_index);

        return OAL_FAIL;
    }
    en_unicast   = pst_defaultkey_params->en_unicast;
    en_multicast = pst_defaultkey_params->en_multicast;
    /*2.3 ������Ч�Լ��*/
    if ((OAL_FALSE == en_multicast) && (OAL_FALSE == en_unicast))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_set_default_key::invalid mode.}");
        return OAL_FAIL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    if (uc_key_index >= WLAN_NUM_TK)
    {
        /*3.1 ����default mgmt key����*/
        ul_ret = mac_vap_set_default_mgmt_key(pst_mac_vap, uc_key_index);
    }
    else
    {
        /*3.2 ���� WEP default key����*/
        ul_ret = mac_vap_set_default_key(pst_mac_vap, uc_key_index);
    }

    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_config_11i_set_default_key::set key[%d] failed[%d].}", uc_key_index, ul_ret);
        return ul_ret;
    }

#endif

    if (uc_key_index < WLAN_NUM_TK)
    {
        ul_ret = dmac_11i_add_wep_key(pst_mac_vap, uc_key_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                        "{dmac_config_11i_set_default_key::dmac_11i_add_wep_key failed[%d].}", ul_ret);
            return ul_ret;
        }
    }


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_11i_tkip_mic_failure_handler
 ��������  : ��mic�¼��ϱ���hmac
 �������  :
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_11i_tkip_mic_failure_handler(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_user_mac, oal_nl80211_key_type en_key_type)
{
    frw_event_mem_stru           *pst_event_mem;          /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru               *pst_dmac_to_hmac_event; /* ָ�������¼���payloadָ�� */
    dmac_to_hmac_mic_event_stru  *pst_mic_event;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_user_mac))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_11i_tkip_mic_failure_handler::param null.}");

        return;
    }
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_mic_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_tkip_mic_failure_handler::pst_event_mem null.}");
        return;
    }

    /* ����¼�ָ�� */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_DRX,
                       DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE,/* DMAC tkip mic faile �ϱ���HMAC */
                       OAL_SIZEOF(dmac_to_hmac_mic_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /*��mic��Ϣ�ϱ���hmac*/
    pst_mic_event = (dmac_to_hmac_mic_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);
    oal_memcopy(pst_mic_event->auc_user_mac, puc_user_mac, WLAN_MAC_ADDR_LEN);
    pst_mic_event->en_key_type   = en_key_type;
    pst_mic_event->l_key_id     = 0;/*tkip ֻ֧��1����Կ��д��0*/

    /* �ַ� */
    frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

