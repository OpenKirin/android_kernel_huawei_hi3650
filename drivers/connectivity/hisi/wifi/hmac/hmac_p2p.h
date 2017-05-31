/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_p2p.h
  �� �� ��   : ����
  ��    ��   : duankaiyong 00194999
  ��������   : 2014��11��25��
  ����޸�   :
  ��������   :  hmac_p2p.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��25��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_P2P_H__
#define __HMAC_P2P_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hmac_fsm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_P2P_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/* p2p ״̬�� */
typedef enum {
	P2P_STATUS_DISCOVERY_ON = 0,
	P2P_STATUS_SEARCH_ENABLED,
	P2P_STATUS_IF_ADD,
	P2P_STATUS_IF_DEL,
	P2P_STATUS_IF_DELETING,
	P2P_STATUS_IF_CHANGING,
	P2P_STATUS_IF_CHANGED,
	P2P_STATUS_LISTEN_EXPIRED,
	P2P_STATUS_ACTION_TX_COMPLETED,
	P2P_STATUS_ACTION_TX_NOACK,
	P2P_STATUS_SCANNING,
	P2P_STATUS_GO_NEG_PHASE,
	P2P_STATUS_DISC_IN_PROGRESS
}hmac_cfgp2p_status_enum;
typedef oal_uint32 hmac_cfgp2p_status_enum_uint32;

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
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_uint32 hmac_check_p2p_vap_num(mac_device_stru *pst_mac_device, wlan_p2p_mode_enum_uint8 en_p2p_mode);
extern oal_uint32 hmac_p2p_send_listen_expired_to_host(hmac_vap_stru *pst_hmac_vap);
extern oal_uint32 hmac_p2p_send_listen_expired_to_device(hmac_vap_stru *pst_hmac_vap);
extern oal_uint32 hmac_add_p2p_cl_vap(mac_vap_stru *pst_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_del_p2p_cl_vap(mac_vap_stru *pst_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_p2p_check_can_enter_state(mac_vap_stru *pst_mac_vap,
                                            hmac_fsm_input_type_enum_uint8 en_input_req);
extern oal_uint32 hmac_p2p_get_home_channel(mac_vap_stru                     *pst_mac_vap,
                                    oal_uint32                        *pul_home_channel,
                                    wlan_channel_bandwidth_enum_uint8 *pen_home_channel_type);
extern oal_void hmac_disable_p2p_pm(hmac_vap_stru *pst_hmac_vap);
extern oal_bool_enum_uint8 hmac_is_p2p_go_neg_req_frame(OAL_CONST oal_uint8* puc_data);
extern oal_uint8 hmac_get_p2p_status(oal_uint32 ul_p2p_status, hmac_cfgp2p_status_enum_uint32 en_status);
extern oal_void hmac_set_p2p_status(oal_uint32 *pul_p2p_status, hmac_cfgp2p_status_enum_uint32 en_status);
extern oal_void hmac_clr_p2p_status(oal_uint32 *pul_p2p_status, hmac_cfgp2p_status_enum_uint32 en_status);

#else   /* _PRE_WLAN_FEATURE_P2P */
OAL_STATIC OAL_INLINE oal_uint32 hmac_check_p2p_vap_num(mac_device_stru *pst_mac_device, wlan_p2p_mode_enum_uint8 en_p2p_mode)
{
    return OAL_TRUE;
}

OAL_STATIC OAL_INLINE oal_uint32 hmac_p2p_send_listen_expired_to_host(hmac_vap_stru *pst_hmac_vap)
{
    pst_hmac_vap = pst_hmac_vap;
    return OAL_TRUE;
}

OAL_STATIC OAL_INLINE oal_uint32 hmac_p2p_send_listen_expired_to_device(hmac_vap_stru *pst_hmac_vap)
{
    pst_hmac_vap = pst_hmac_vap;
    return OAL_TRUE;
}

OAL_STATIC OAL_INLINE oal_uint32 hmac_p2p_check_can_enter_state(mac_vap_stru *pst_mac_vap,
                                            hmac_fsm_input_type_enum_uint8 en_input_req)
{
    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_uint32 hmac_p2p_get_home_channel(mac_vap_stru                     *pst_mac_vap,
                                    oal_uint32                        *pul_home_channel,
                                    wlan_channel_bandwidth_enum_uint8 *pen_home_channel_type)
{
    return OAL_SUCC;
}

#endif  /* _PRE_WLAN_FEATURE_P2P */




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_p2p.h */
