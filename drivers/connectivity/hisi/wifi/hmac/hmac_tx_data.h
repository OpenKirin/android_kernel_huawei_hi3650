/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_tx_data.h
  �� �� ��   : ����
  ��    ��   : c00178899
  ��������   : 2012��11��12��
  ����޸�   :
  ��������   : hmac_tx_bss_ap.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��12��
    ��    ��   : c00178899
    �޸�����   : �����ļ�
  2.��    ��   : 2013��1��8��
    ��    ��   : z52447
    �޸�����   : �ļ����޸�
******************************************************************************/

#ifndef __HMAC_TX_DATA_H__
#define __HMAC_TX_DATA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "mac_frame.h"
#include "dmac_ext_if.h"
#include "hmac_vap.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_mgmt_classifier.h"
#include "mac_resource.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TX_DATA_H


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����������Ϣ�й����Ƿ���QOS������λ */
#define HMAC_CAP_INFO_QOS_MASK 0x0200

#define WLAN_TOS_TO_TID(_tos) (      \
        (((_tos) == 0) || ((_tos) == 3)) ? WLAN_TIDNO_BEST_EFFORT: \
        (((_tos) == 1) || ((_tos) == 2)) ? WLAN_TIDNO_BACKGROUND: \
        (((_tos) == 4) || ((_tos) == 5)) ? WLAN_TIDNO_VIDEO: \
        WLAN_TIDNO_VOICE)

#define WLAN_BA_CNT_INTERVAL 100

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    HMAC_TX_BSS_NOQOS = 0,
    HMAC_TX_BSS_QOS   = 1,

    HMAC_TX_BSS_QOS_BUTT
}hmac_tx_bss_qos_type_enum;

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

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  hmac_tx_encap(hmac_vap_stru    *pst_vap,
                                            hmac_user_stru   *pst_user,
                                            oal_netbuf_stru  *pst_buf);
extern oal_uint32 hmac_tx_ucast_process( hmac_vap_stru   *pst_vap,
                                                oal_netbuf_stru *pst_buf,
                                                hmac_user_stru  *pst_user,
                                                mac_tx_ctl_stru    *pst_tx_ctl);

extern oal_void  hmac_tx_ba_setup(
                hmac_vap_stru          *pst_vap,
                hmac_user_stru         *pst_user,
                oal_uint8               uc_tidno);

extern  oal_void hmac_tx_ba_cnt_vary(
                                hmac_vap_stru   *pst_hmac_vap,
                                hmac_user_stru  *pst_hmac_user,
                                oal_uint8        uc_tidno,
                                oal_netbuf_stru *pst_buf);

#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
extern  oal_uint8 hmac_tx_wmm_acm(oal_bool_enum_uint8  en_wmm, hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_tid);
#endif /* defined(_PRE_PRODUCT_ID_HI110X_HOST) */
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : hmac_tx_get_next_mpdu
 ��������  : ��ȡ��һ��MPDU
 �������  : pst_buf netbuf�ṹ��;uc_netbuf_num netbuf����
 �������  :
 �� �� ֵ  :
 ���ú���  : hmac_tx_event_process_ap
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru *hmac_tx_get_next_mpdu(oal_netbuf_stru *pst_buf, oal_uint8 uc_netbuf_num)
{
    oal_netbuf_stru       *pst_next_buf = OAL_PTR_NULL;
    oal_uint32             ul_netbuf_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
      //  OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_get_next_mpdu::pst_buf null}");
        return OAL_PTR_NULL;
    }

    pst_next_buf = pst_buf;
    for (ul_netbuf_index = 0; ul_netbuf_index < uc_netbuf_num; ul_netbuf_index++)
    {
        pst_next_buf = oal_netbuf_list_next(pst_next_buf);
    }

    return pst_next_buf;
}

/*****************************************************************************
 �� �� ��  : hmac_tx_netbuf_list_enqueue
 ��������  : MPDU���
 �������  : pst_head ��ͷ; pst_buf netbuf�ṹ��;uc_netbuf_num netbuf����
 �������  :
 �� �� ֵ  :
 ���ú���  : hmac_tx_event_process_ap
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_tx_netbuf_list_enqueue(oal_netbuf_head_stru *pst_head, oal_netbuf_stru *pst_buf, oal_uint8 uc_netbuf_num)
{
    oal_uint32             ul_netbuf_index;
    oal_netbuf_stru       *pst_buf_next;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_head) || (OAL_PTR_NULL == pst_buf)))
    {
      //  OAM_ERROR_LOG2(0, OAM_SF_TX, "{hmac_tx_get_next_mpdu::input null %x %x}", pst_head, pst_buf);
        return;
    }

    for (ul_netbuf_index = 0; ul_netbuf_index < uc_netbuf_num; ul_netbuf_index++)
    {
        pst_buf_next = oal_netbuf_list_next(pst_buf);
        oal_netbuf_add_to_list_tail(pst_buf, pst_head);
        pst_buf = pst_buf_next;
    }
}


/*****************************************************************************
 �� �� ��  : hmac_tx_get_addr
 ��������  : ��ȡԭ��ַ��Ŀ�ĵ�ַ
 �������  : pst_hdr 802.11ͷ�ṹ��
 �������  : puc_saddr ԭ��ַ puc_daddr Ŀ�ĵ�ַ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_tx_get_addr(mac_ieee80211_qos_htc_frame_addr4_stru *pst_hdr,
                                                oal_uint8                               *puc_saddr,
                                                oal_uint8                               *puc_daddr)
{
    oal_uint8  uc_to_ds;
    oal_uint8  uc_from_ds;

    uc_to_ds   = mac_hdr_get_to_ds((oal_uint8 *)pst_hdr);
    uc_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_hdr);

    if ((1 == uc_to_ds) && (0 == uc_from_ds))
    {
        /* to AP */
        oal_set_mac_addr(puc_saddr, pst_hdr->auc_address2);
        oal_set_mac_addr(puc_daddr, pst_hdr->auc_address3);
    }
    else if ((0 == uc_to_ds) && (0 == uc_from_ds))
    {
        /* IBSS */
        oal_set_mac_addr(puc_saddr, pst_hdr->auc_address2);
        oal_set_mac_addr(puc_daddr, pst_hdr->auc_address1);
    }
    else if ((1 == uc_to_ds) && (1 == uc_from_ds))
    {
        /* WDS */
        oal_set_mac_addr(puc_saddr, pst_hdr->auc_address4);
        oal_set_mac_addr(puc_daddr, pst_hdr->auc_address3);
    }
    else
    {
        /* From AP */
        oal_set_mac_addr(puc_saddr, pst_hdr->auc_address3);
        oal_set_mac_addr(puc_daddr, pst_hdr->auc_address1);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_tx_set_frame_ctrl
 ��������  : ����֡����
 �������  : ul_qos �Ƿ���QOSվ�� pst_tx_ctl CB�ֶ� pst_hdr 802.11ͷ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_tx_set_frame_ctrl(oal_uint32                               ul_qos,
                                                      mac_tx_ctl_stru                         *pst_tx_ctl,
                                                      mac_ieee80211_qos_htc_frame_addr4_stru  *pst_hdr_addr4)
{
    mac_ieee80211_qos_htc_frame_stru *pst_hdr = OAL_PTR_NULL;
    oal_bool_enum_uint8               en_is_amsdu;
    if (HMAC_TX_BSS_QOS == ul_qos)
    {
        if (1 == pst_tx_ctl->uc_netbuf_num)
        {
            en_is_amsdu = OAL_FALSE;
        }
        else
        {
            en_is_amsdu = pst_tx_ctl->en_is_amsdu;
        }

        /* ����֡�����ֶ� */
        mac_hdr_set_frame_control((oal_uint8 *)pst_hdr_addr4, (WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA));

        /* ����֡ͷ���� */
        if (OAL_FALSE == pst_tx_ctl->en_use_4_addr)
        {
            pst_hdr = (mac_ieee80211_qos_htc_frame_stru *)pst_hdr_addr4;
            /* ����QOS�����ֶ� */
            pst_hdr->bit_qc_tid        = pst_tx_ctl->uc_tid;
            pst_hdr->bit_qc_eosp       = 0;
            pst_hdr->bit_qc_ack_polocy = pst_tx_ctl->en_ack_policy;
            pst_hdr->bit_qc_amsdu      = en_is_amsdu;
            pst_hdr->qos_control.bit_qc_txop_limit = 0;
            pst_tx_ctl->uc_frame_header_length = MAC_80211_QOS_FRAME_LEN;
        }
        else
        {
            /* ����QOS�����ֶ� */
            pst_hdr_addr4->bit_qc_tid        = pst_tx_ctl->uc_tid;
            pst_hdr_addr4->bit_qc_eosp       = 0;
            pst_hdr_addr4->bit_qc_ack_polocy = pst_tx_ctl->en_ack_policy;
            pst_hdr_addr4->bit_qc_amsdu      = en_is_amsdu;
            pst_hdr_addr4->qos_control.qc_txop_limit = 0;
            pst_tx_ctl->uc_frame_header_length = MAC_80211_QOS_4ADDR_FRAME_LEN;
        }

        /* ��DMAC�����Ƿ���ҪHTC */
    }
    else
    {
        /* ����֡�����ֶ� */
        mac_hdr_set_frame_control((oal_uint8 *)pst_hdr_addr4, WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_DATA);

        /* ��QOS����֡֡�����ֶ����� */
        if (pst_tx_ctl->en_use_4_addr)
        {
            pst_tx_ctl->uc_frame_header_length = MAC_80211_4ADDR_FRAME_LEN;
        }
        else
        {
            pst_tx_ctl->uc_frame_header_length = MAC_80211_FRAME_LEN;
        }
    }
}

/*****************************************************************************
 �� �� ��  : hmac_tx_set_addresses
 ��������  : ����֡��ַ����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 hmac_tx_set_addresses(
                hmac_vap_stru                           *pst_vap,
                hmac_user_stru                          *pst_user,
                mac_tx_ctl_stru                         *pst_tx_ctl,
                oal_uint8                               *puc_saddr,
                oal_uint8                               *puc_daddr,
                mac_ieee80211_qos_htc_frame_addr4_stru  *pst_hdr,
                oal_uint16                               us_ether_type)
{
    /* ��Ƭ���ó�0��������Ƭ������Ҫ���¸�ֵ */
    pst_hdr->bit_frag_num    = 0;
    pst_hdr->bit_seq_num     = 0;

    if ((WLAN_VAP_MODE_BSS_AP == pst_vap->st_vap_base_info.en_vap_mode)
          && (!(pst_tx_ctl->en_use_4_addr))) /* From AP */
    {
        /* From DS��ʶλ���� */
        mac_hdr_set_from_ds((oal_uint8 *)pst_hdr, 1);

        /* to DS��ʶλ���� */
        mac_hdr_set_to_ds((oal_uint8 *)pst_hdr, 0);

        /* Set Address1 field in the WLAN Header with destination address */
        oal_set_mac_addr(pst_hdr->auc_address1, puc_daddr);

        /* Set Address2 field in the WLAN Header with the BSSID */
        oal_set_mac_addr(pst_hdr->auc_address2, pst_vap->st_vap_base_info.auc_bssid);

        if (pst_tx_ctl->en_is_amsdu) /* AMSDU�������ַ3��дBSSID */
        {
            /* Set Address3 field in the WLAN Header with the BSSID */
            oal_set_mac_addr(pst_hdr->auc_address3, pst_vap->st_vap_base_info.auc_bssid);
        }
        else
        {
            /* Set Address3 field in the WLAN Header with the source address */
            oal_set_mac_addr(pst_hdr->auc_address3, puc_saddr);
        }

    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode)
    {
        /* From DS��ʶλ���� */
        mac_hdr_set_from_ds((oal_uint8 *)pst_hdr, 0);

        /* to DS��ʶλ���� */
        mac_hdr_set_to_ds((oal_uint8 *)pst_hdr, 1);

        /* Set Address1 field in the WLAN Header with BSSID */
        oal_set_mac_addr(pst_hdr->auc_address1, pst_user->st_user_base_info.auc_user_mac_addr);

        if (us_ether_type == oal_byteorder_host_to_net_uint16(ETHER_LLTD_TYPE))
        {
            /* Set Address2 field in the WLAN Header with the source address */
            oal_set_mac_addr(pst_hdr->auc_address2, puc_saddr);
        }
        else
        {
            /* Set Address2 field in the WLAN Header with the source address */
            oal_set_mac_addr(pst_hdr->auc_address2, pst_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
        }

        if (pst_tx_ctl->en_is_amsdu) /* AMSDU�������ַ3��дBSSID */
        {
            /* Set Address3 field in the WLAN Header with the BSSID */
            oal_set_mac_addr(pst_hdr->auc_address3, pst_user->st_user_base_info.auc_user_mac_addr);
        }
        else
        {
            /* Set Address3 field in the WLAN Header with the destination address */
            oal_set_mac_addr(pst_hdr->auc_address3, puc_daddr);
        }
    }
    else /* WDS */
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
        {
            OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_set_addresses::pst_user null}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* TO DS��ʶλ���� */
        mac_hdr_set_to_ds((oal_uint8 *)pst_hdr, 1);

        /* From DS��ʶλ���� */
        mac_hdr_set_from_ds((oal_uint8 *)pst_hdr, 1);

        /* ��ַ1�� RA */
        oal_set_mac_addr(pst_hdr->auc_address1, pst_user->st_user_base_info.auc_user_mac_addr);

        /* ��ַ2�� TA (��ǰֻ��BSSID) */
        oal_set_mac_addr(pst_hdr->auc_address2, pst_vap->st_vap_base_info.auc_bssid);

        if (pst_tx_ctl->en_is_amsdu) /* AMSDU�������ַ3�͵�ַ4��дBSSID */
        {
            /* ��ַ3�� BSSID */
            oal_set_mac_addr(pst_hdr->auc_address3, pst_vap->st_vap_base_info.auc_bssid);

            /* ��ַ4Ҳ�� BSSID */
            oal_set_mac_addr(pst_hdr->auc_address4, pst_vap->st_vap_base_info.auc_bssid);
        }
        else
        {
            /* ��ַ3�� DA */
            oal_set_mac_addr(pst_hdr->auc_address3, puc_daddr);

            /* ��ַ4�� SA */
            oal_set_mac_addr(pst_hdr->auc_address4, puc_saddr);
        }

    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_vap_ba_is_setup
 ��������  : �жϸ��û���Ӧ��TID�Ƿ��Ѿ�����BA�Ự
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_TRUE�����Ѿ�������BA�Ự
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_vap_ba_is_setup(hmac_user_stru *pst_hmac_user, oal_uint8 uc_tidno)
{
   if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user) || uc_tidno >= WLAN_TID_MAX_NUM)
   {
       return OAL_FALSE;
   }
   return (DMAC_BA_COMPLETE == pst_hmac_user->ast_tid_info[uc_tidno].st_ba_tx_info.en_ba_status) ? OAL_TRUE : OAL_FALSE;/* [false alarm]:����ֵ�ǲ���ֵ�ͺ�������һ��*/
}

/*****************************************************************************
 �� �� ��  : hmac_tx_ba_check
 ��������  : �ж��Ƿ���Ҫ����BA�Ự
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_TRUE������Ҫ����BA�Ự
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��24��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

�޸���ʷ      :
  2.��    ��   : 2015��7��24��
    ��    ��   : lixiaochuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_tid_need_ba_session(
                                    hmac_vap_stru   *pst_hmac_vap,
                                    hmac_user_stru  *pst_hmac_user,
                                    oal_uint8        uc_tidno,
                                    oal_netbuf_stru *pst_buf)
{
    mac_device_stru       *pst_mac_device;
    hmac_tid_stru         *pst_hmac_tid_info;
    mac_action_mgmt_args_stru       st_action_args;   /* ������дACTION֡�Ĳ��� */

    if(OAL_TRUE == hmac_vap_ba_is_setup(pst_hmac_user, uc_tidno))
    {
        if (OAL_FALSE == pst_hmac_vap->en_ampdu_tx_on_switch)
        {
            st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
            st_action_args.uc_action   = MAC_BA_ACTION_DELBA;
            st_action_args.ul_arg1     = uc_tidno;
            st_action_args.ul_arg2     = MAC_ORIGINATOR_DELBA;
            st_action_args.ul_arg3     = MAC_UNSPEC_REASON;
            st_action_args.puc_arg5    = pst_hmac_user->st_user_base_info.auc_user_mac_addr;
            hmac_mgmt_tx_action(pst_hmac_vap,  pst_hmac_user, &st_action_args);
        }
        return OAL_FALSE;
    }

    /* ��������������ۺ�ʱ���� */
    if (OAL_FALSE == pst_hmac_vap->en_ampdu_tx_on_switch)
    {
        return OAL_FALSE;
    }

    if(OAL_FALSE == hmac_user_xht_support(pst_hmac_user))
    {
        return OAL_FALSE;
    }
    if(HMAC_ADDBA_MODE_AUTO != pst_hmac_vap->en_addba_mode)
    {
        return OAL_FALSE;
    }

    /* ���VOҵ��, ����VAP��־λȷ���Ƿ���BA�Ự */
    if ((WLAN_WME_AC_VO == WLAN_WME_TID_TO_AC(uc_tidno)) && (OAL_FALSE == pst_hmac_vap->st_vap_base_info.bit_voice_aggr))
    {
        return OAL_FALSE;
    }

    /* �ж�HMAC VAP���Ƿ�֧�־ۺ� */
    if (!((pst_hmac_vap->en_tx_aggr_on) || (pst_hmac_vap->st_vap_base_info.st_cap_flag.bit_rifs_tx_on)))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_tid_need_ba_session::en_tx_aggr_on of vap is off");
        return OAL_FALSE;
    }

    pst_hmac_tid_info = &(pst_hmac_user->ast_tid_info[uc_tidno]);
    if (OAL_TRUE != pst_hmac_tid_info->st_ba_tx_info.en_ba_switch)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_tid_need_ba_session::en_tx_aggr_on of tid[%d] is off", uc_tidno);
        return OAL_FALSE;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_tid_need_ba_session::pst_mac_dev null");
        return OAL_FALSE;
    }

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    if (pst_hmac_vap->uc_tx_ba_session_num >= WLAN_MAX_TX_BA)
    {
        OAM_INFO_LOG1(0, OAM_SF_BA, "{hmac_tid_need_ba_session::uc_tx_ba_session_num[%d] exceed spec", pst_hmac_vap->uc_tx_ba_session_num);
        return OAL_FALSE;
    }
#else
    if (pst_mac_device->uc_tx_ba_session_num >= WLAN_MAX_TX_BA)
    {
        OAM_INFO_LOG1(0, OAM_SF_BA, "{hmac_tid_need_ba_session::uc_tx_ba_session_num[%d] exceed spec", pst_mac_device->uc_tx_ba_session_num);
        return OAL_FALSE;
    }
#endif
    /* ��Ҫ�ȷ���5������֡���ٽ���BA�Ự�Ľ��� */
    if ((OAL_TRUE == pst_hmac_user->st_user_base_info.st_cap_info.bit_qos) &&
        (pst_hmac_user->auc_ba_flag[uc_tidno] < DMAC_UCAST_FRAME_TX_COMP_TIMES) &&
        (HMAC_ADDBA_MODE_AUTO == pst_hmac_vap->en_addba_mode))
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                      "{hmac_tid_need_ba_session::auc_ba_flag[%d]}", pst_hmac_user->auc_ba_flag[uc_tidno]);
        hmac_tx_ba_cnt_vary(pst_hmac_vap, pst_hmac_user, uc_tidno, pst_buf);
        return OAL_FALSE;
    }
    /* ��Թر�WMM����QOS֡���� */
    else if(OAL_FALSE == pst_hmac_user->st_user_base_info.st_cap_info.bit_qos)
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,"{UnQos Frame pass!!}");
        return OAL_FALSE;
    }

    /* DTS2016012002852 ��Ȼ�����ж���״̬����COMPLETE,����״̬��Ȼ������COMPLETE */
    if ((pst_hmac_tid_info->st_ba_tx_info.en_ba_status == DMAC_BA_INIT)
     && (pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps < HMAC_ADDBA_EXCHANGE_ATTEMPTS))
    {
        pst_hmac_tid_info->st_ba_tx_info.en_ba_status = DMAC_BA_INPROGRESS;
        pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps++;
    }
    else
    {
        OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                     "{hmac_tid_need_ba_session::addba_attemps[%d] of tid[%d] is COMPLETE}", pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps, uc_tidno);
        return OAL_FALSE;
    }

    return OAL_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_tx_data.h */
