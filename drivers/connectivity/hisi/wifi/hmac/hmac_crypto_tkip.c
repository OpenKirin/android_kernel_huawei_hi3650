/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_crypto_tkip.c
  �� �� ��   : ����
  ��    ��   : g00260350
  ��������   : 2014��3��1��
  ����޸�   :
  ��������   : tkip�ӽ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��3��1��
    ��    ��   : g00260350
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
#include "mac_frame.h"
#include "dmac_ext_if.h"
#include "hmac_crypto_tkip.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define     MAX_TKIP_PN_GAP_ERR    1  /* Max. gap in TKIP PN before doing MIC sanity check */


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : hmac_crypto_tkip_michael_hdr
 ��������  : mic�����Դmac��Ŀ��mac����TID��Ϣ����
 �������  :
 �������  : oal_void
 �� �� ֵ  : null
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_crypto_tkip_michael_hdr(mac_ieee80211_frame_stru *pst_frame_header, oal_uint8 auc_hdr[16])
{
    mac_ieee80211_frame_addr4_stru *pst_frame_4addr_hdr = OAL_PTR_NULL;
    oal_uint8                       uc_frame_dir        = 0;

    pst_frame_4addr_hdr = (mac_ieee80211_frame_addr4_stru *)pst_frame_header;

    uc_frame_dir  = (pst_frame_4addr_hdr->st_frame_control.bit_to_ds) ? 1 : 0;
    uc_frame_dir += (pst_frame_4addr_hdr->st_frame_control.bit_from_ds) ? 2 : 0;

    switch (uc_frame_dir)
    {
        case IEEE80211_FC1_DIR_NODS:
            oal_memcopy(auc_hdr, pst_frame_4addr_hdr->auc_address1, WLAN_MAC_ADDR_LEN);
            oal_memcopy(auc_hdr + WLAN_MAC_ADDR_LEN, pst_frame_4addr_hdr->auc_address2, WLAN_MAC_ADDR_LEN);
            break;
        case IEEE80211_FC1_DIR_TODS:
            oal_memcopy(auc_hdr, pst_frame_4addr_hdr->auc_address3, WLAN_MAC_ADDR_LEN);
            oal_memcopy(auc_hdr + WLAN_MAC_ADDR_LEN, pst_frame_4addr_hdr->auc_address2, WLAN_MAC_ADDR_LEN);
            break;
        case IEEE80211_FC1_DIR_FROMDS:
            oal_memcopy(auc_hdr, pst_frame_4addr_hdr->auc_address1, WLAN_MAC_ADDR_LEN);
            oal_memcopy(auc_hdr + WLAN_MAC_ADDR_LEN, pst_frame_4addr_hdr->auc_address3, WLAN_MAC_ADDR_LEN);
            break;
        default:
            oal_memcopy(auc_hdr, pst_frame_4addr_hdr->auc_address3, WLAN_MAC_ADDR_LEN);
            oal_memcopy(auc_hdr + WLAN_MAC_ADDR_LEN, pst_frame_4addr_hdr->auc_address4, WLAN_MAC_ADDR_LEN);
            break;
    }
    auc_hdr[12] = 0;

    if (WLAN_QOS_DATA == pst_frame_4addr_hdr->st_frame_control.bit_sub_type)
    {
        if (IEEE80211_FC1_DIR_DSTODS == uc_frame_dir)
        {
            auc_hdr[12] = ((mac_ieee80211_qos_frame_addr4_stru *)pst_frame_4addr_hdr)->bit_qc_tid;
        }
        else
        {
            auc_hdr[12] = ((mac_ieee80211_qos_frame_stru *)pst_frame_4addr_hdr)->bit_qc_tid;
        }
    }


    auc_hdr[13] = auc_hdr[14] = auc_hdr[15] = 0; /* reserved */
}
/*****************************************************************************
 �� �� ��  : hmac_crypto_tkip_michael_mic
 ��������  : ����micУ����
 �������  : key ��Կ(8byte)
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_crypto_tkip_michael_mic(oal_uint8 *puc_key,
                                                              oal_netbuf_stru *pst_netbuf,
															  mac_ieee80211_frame_stru *pst_frame_header,
                                                              oal_uint32       ul_offset,
                                                              oal_uint32       ul_data_len,
                                                              oal_uint8        auc_mic[IEEE80211_WEP_MICLEN])
{
    oal_uint8                  auc_hdr[16]    = {0};
    oal_uint32                 ul_msb         = 0;
    oal_uint32                 ul_lsb         = 0;
    const oal_uint8           *puc_data       = OAL_PTR_NULL;
    oal_uint32                 ul_space       = 0;
    const oal_uint8           *puc_data_next  = OAL_PTR_NULL;

    hmac_crypto_tkip_michael_hdr(pst_frame_header, auc_hdr);

    ul_msb = get_le32(puc_key);
    ul_lsb = get_le32(puc_key + 4);

    /* Michael MIC pseudo header: DA, SA, 3 x 0, Priority */
    ul_msb ^= get_le32(auc_hdr);
    michael_block(ul_msb, ul_lsb);
    ul_msb ^= get_le32(&auc_hdr[4]);
    michael_block(ul_msb, ul_lsb);
    ul_msb ^= get_le32(&auc_hdr[8]);
    michael_block(ul_msb, ul_lsb);
    ul_msb ^= get_le32(&auc_hdr[12]);
    michael_block(ul_msb, ul_lsb);

    /* first buffer has special handling */
    puc_data = OAL_NETBUF_DATA(pst_netbuf) + ul_offset;
    ul_space = OAL_NETBUF_LEN(pst_netbuf) - ul_offset;
    for (;;)
    {
        if (ul_space > ul_data_len)
        {
            ul_space = ul_data_len;
        }

        /* collect 32-bit blocks from current buffer */
        while (ul_space >= sizeof(oal_uint32))
        {
            ul_msb ^= get_le32(puc_data);
            michael_block(ul_msb, ul_lsb);
            puc_data  += sizeof(oal_uint32);
            ul_space -= sizeof(oal_uint32);
            ul_data_len -= sizeof(oal_uint32);
        }

        if (ul_data_len < sizeof(oal_uint32))
        {
            break;
        }

        pst_netbuf = oal_netbuf_list_next(pst_netbuf);
        if (pst_netbuf == NULL)
        {
            return OAL_ERR_CODE_SECURITY_BUFF_NUM;
        }
        if (ul_space != 0)
        {
            /*
            * Block straddles buffers, split references.
            */
            puc_data_next = OAL_NETBUF_DATA(pst_netbuf);
            if (OAL_NETBUF_LEN(pst_netbuf) < sizeof(oal_uint32) - ul_space)
            {
                return OAL_ERR_CODE_SECURITY_BUFF_LEN;
            }
            switch (ul_space)
            {
                case 1:
                    ul_msb ^= get_le32_split(puc_data[0], puc_data_next[0], puc_data_next[1], puc_data_next[2]);
                    puc_data = puc_data_next + 3;
                    ul_space = OAL_NETBUF_LEN(pst_netbuf) - 3;
                    break;
                case 2:
                    ul_msb ^= get_le32_split(puc_data[0], puc_data[1], puc_data_next[0], puc_data_next[1]);
                    puc_data = puc_data_next + 2;
                    ul_space = OAL_NETBUF_LEN(pst_netbuf) - 2;
                    break;
                case 3:
                    ul_msb ^= get_le32_split(puc_data[0], puc_data[1], puc_data[2], puc_data_next[0]);
                    puc_data = puc_data_next + 1;
                    ul_space = OAL_NETBUF_LEN(pst_netbuf) - 1;
                    break;
                default:
                    break;
            }

            michael_block(ul_msb, ul_lsb);
            ul_data_len -= sizeof(oal_uint32);
        }
        else
        {
            /*
            * Setup for next buffer.
            */
            puc_data = OAL_NETBUF_DATA(pst_netbuf);
            ul_space = OAL_NETBUF_LEN(pst_netbuf);
        }
    }
    /* Last block and padding (0x5a, 4..7 x 0) */
    switch (ul_data_len)
    {
        case 0:
            ul_msb ^= get_le32_split(0x5a, 0, 0, 0);
            break;
        case 1:
            ul_msb ^= get_le32_split(puc_data[0], 0x5a, 0, 0);
            break;
        case 2:
            ul_msb ^= get_le32_split(puc_data[0], puc_data[1], 0x5a, 0);
            break;
        case 3:
            ul_msb ^= get_le32_split(puc_data[0], puc_data[1], puc_data[2], 0x5a);
            break;
        default:
            break;
    }
    michael_block(ul_msb, ul_lsb);
    /* l ^= 0; */
    michael_block(ul_msb, ul_lsb);

    put_le32(auc_mic, ul_msb);
    put_le32(auc_mic + 4, ul_lsb);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_crypto_tkip_enmic
 ��������  : ���tikip micУ��
 �������  :
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_crypto_tkip_enmic(wlan_priv_key_param_stru *pst_key, oal_netbuf_stru *pst_netbuf)
{
    oal_uint32                     ul_hdrlen      = 0;/*����ʱ��ul_pktlen�ﲻ��80211macͷ*/
    oal_uint32                     ul_pktlen      = 0;
    oal_uint32                     ul_ret         = OAL_FAIL;
    oal_uint8                     *puc_mic_tail   = OAL_PTR_NULL;
    oal_uint8                     *puc_tx_mic_key = OAL_PTR_NULL;
    oal_uint8                      auc_mic[IEEE80211_WEP_MICLEN] = {0};
    mac_tx_ctl_stru               *pst_cb         = OAL_PTR_NULL;


    if (WLAN_80211_CIPHER_SUITE_TKIP != ((oal_uint8)pst_key->ul_cipher))
    {
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /*1.1 �����������ĵĳ��ȣ���������ڶ��netbuf�����*/
    ul_pktlen = OAL_NETBUF_LEN(pst_netbuf);
    if (OAL_PTR_NULL != OAL_NETBUF_NEXT(pst_netbuf))
    {
        return OAL_ERR_CODE_SECURITY_BUFF_NUM;
    }

    /*2.1 ��netbuf������mic�ռ�*/
    if (oal_netbuf_tailroom(pst_netbuf) < IEEE80211_WEP_MICLEN)
    {
        /*2.2 ���ԭ����netbuf���Ȳ�������Ҫ��������*/
        oal_netbuf_realloc_tailroom(pst_netbuf, IEEE80211_WEP_MICLEN);
    }

    /*3.1 ��ȡmic����Կ */
    puc_mic_tail   = (oal_uint8 *)OAL_NETBUF_TAIL(pst_netbuf);
    puc_tx_mic_key = pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH; 
    
    oal_netbuf_put(pst_netbuf, IEEE80211_WEP_MICLEN);

    pst_cb    = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /*4.1 ����mic */
	ul_ret = hmac_crypto_tkip_michael_mic(puc_tx_mic_key, pst_netbuf, pst_cb->pst_frame_header, ul_hdrlen, ul_pktlen - ul_hdrlen, auc_mic);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /*4.1 ����mic��֡β�� */
    oal_memcopy(puc_mic_tail, auc_mic, IEEE80211_WEP_MICLEN);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_crypto_tkip_demic
 ��������  : �Ƚ�tkip micУ�飬������micβ
 �������  :
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_crypto_tkip_demic(wlan_priv_key_param_stru *pst_key, oal_netbuf_stru *pst_netbuf)
{
    mac_rx_ctl_stru          *pst_cb                              = OAL_PTR_NULL;
    oal_uint32                ul_hdrlen                           = 0;/*����ʱ��ul_pktlen�����80211macͷ*/
    oal_uint8                *puc_rx_mic_key                      = OAL_PTR_NULL;
    oal_uint32                ul_ret                              = OAL_FAIL;
    oal_uint32                ul_pktlen                           = 0;
    oal_uint8                 auc_mic[IEEE80211_WEP_MICLEN]       = {0};
    oal_uint8                 auc_mic_peer[IEEE80211_WEP_MICLEN]  = {0};

    if (WLAN_80211_CIPHER_SUITE_TKIP != ((oal_uint8)pst_key->ul_cipher))
    {
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /*1.1 �����������ĵĳ��ȣ���������ڶ��netbuf�����*/
    ul_pktlen         = OAL_NETBUF_LEN(pst_netbuf);
    if (OAL_PTR_NULL != oal_netbuf_list_next(pst_netbuf))
    {
        return OAL_ERR_CODE_SECURITY_BUFF_NUM;
    }

    /*2.1 ��CB�л�ȡ80211ͷ����*/
    pst_cb    = (mac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    ul_hdrlen = pst_cb->uc_mac_header_len;

    /*3.1 ֻ��������֡*/

    /*4.1 ��ȡ������Կ��������Կ��Ҫƫ��8���ֽ�*/
    puc_rx_mic_key = pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH + WLAN_MIC_KEY_LENGTH;

    /*5.1 ����mic */
	ul_ret = hmac_crypto_tkip_michael_mic(puc_rx_mic_key, pst_netbuf, (mac_ieee80211_frame_stru *)pst_cb->pul_mac_hdr_start_addr, ul_hdrlen, ul_pktlen - (ul_hdrlen + IEEE80211_WEP_MICLEN), auc_mic);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /*6.1 ��ȡ�Զ˵�mic�������ؼ����mic���бȽ�*/
    oal_netbuf_copydata(pst_netbuf, ul_pktlen - IEEE80211_WEP_MICLEN, (oal_void *)auc_mic_peer, IEEE80211_WEP_MICLEN);
    if (oal_memcmp(auc_mic, auc_mic_peer, IEEE80211_WEP_MICLEN))
    {

        /* NB: 802.11 layer handles statistic and debug msg
        ieee80211_notify_michael_failure(vap, wh, k->wk_keyix); */
        return OAL_ERR_CODE_SECURITY_WRONG_KEY;
    }

   /*7.1 ȥ��micβ��*/
    oal_netbuf_trim(pst_netbuf, IEEE80211_WEP_MICLEN);
    return OAL_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

