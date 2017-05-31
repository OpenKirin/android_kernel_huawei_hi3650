/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_fbt_main.h
  �� �� ��   : ����
  ��    ��   : luolingzhi 00225940
  ��������   : 2015��12��24��
  ����޸�   :
  ��������   : hmac_fbt_main.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��18��
     ��    ��   : x00226265
     �޸�����   : �����ļ�

  2.��    ��   : 2015��12��24��
    ��    ��   : luolingzhi 00225940
    �޸�����   : ���mac vap�еĹ������ַŵ�mac_fbt.h��

******************************************************************************/

#ifndef __HMAC_FBT_MAIN_H__
#define __HMAC_FBT_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oam_ext_if.h"
#include "hmac_vap.h"
#include "hmac_fsm.h"
#include "frw_ext_if.h"
#include "hmac_device.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_FBT_H


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define HMAC_FBT_RSSI_ADJUST_VALUE  100
#define HMAC_FBT_DEFAULT_DISABLE_INTERVAL  0

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    HMAC_FBT_LINK_WEAK       = 0,       /* �ϱ�����Ϊ�����źű�����STA��AP���ź�ǿ��ֵС�ڷ�ֵ�� */
    HMAC_FBT_LINK_STRONG     = 1,       /* �ϱ�����Ϊ�����źű�ǿ��STA��AP���ź�ǿ��ֵ���ڷ�ֵ�� */
    HMAC_FBT_STA_ONLINE      = 2,       /* �ϱ�����Ϊ������������ */
    HMAC_FBT_STA_OFFLINE     = 3,       /* �ϱ�����Ϊ�������˳� */
    HMAC_FBT_STA_FOUND       = 4,       /* �ϱ�����Ϊɨ�赽ָ������ */
    HMAC_FBT_LINK_BUTT
}hmac_fbt_notify_type_enum;
typedef oal_uint8  hmac_fbt_notify_type_enum_uint8;

/* ������������л�������ģʽ:�رպ�ACģʽ */
typedef enum
{
    HMAC_FBT_MODE_CLOSE     = 0,
    HMAC_FBT_MODE_AC        = 1,

    HMAC_FBT_MODE_BUTT
}hmac_fbt_mode_enum;
typedef oal_uint8 hmac_fbt_mode_enum_uint8;

/* ���������ŵ������ķ�Χ */
typedef enum
{
    HMAC_FBT_SCAN_SCOPE_ALL     = 0,     /* ȫ�ŵ����� */
    HMAC_FBT_SCAN_SCOPE_SELECT  = 1,  /* ָ���ŵ����� */

    HMAC_FBT_SCAN_SCOPE_BUTT,
}hmac_fbt_scan_scope_enum;
typedef oal_uint8 hmac_fbt_scan_scope_enum_uint8;

/* ���޳��û���״̬ */
typedef enum
{
    HMAC_FBT_ENABLE_STATE       = 0,       /* δ��ֹ���� */
    HMAC_FBT_DISASSC_STATE      = 1,       /* ��ȥ������δ���ý�ֹ����ʱ�� */
    HMAC_FBT_FORBIDDEN_STATE    = 2,       /* �����ý�ֹ����ʱ�� */

    HMAC_FBT_STATE_BUTT
}hmac_fbt_user_state_enum;
typedef oal_uint8  hmac_fbt_user_state_enum_uint8;


typedef oal_uint8 hmac_fbt_disable_state_enum_uint8;





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
/* ��������ϱ��ṹ�� */
typedef struct
{
    oal_uint8                       auc_user_bssid[WLAN_MAC_ADDR_LEN];  /* ���������ĵ�ǰAP��bssid */
    oal_uint8                       uc_user_channel;                    /* ������ǰ�������ŵ� */
    oal_uint8                       uc_user_rssi;                       /* ��ǰ�������ź�ǿ�� */
    hmac_fbt_notify_type_enum       en_fbt_notify_type;                 /* ��ǰ��Ϣ�ϱ������� */
    oal_uint8                       auc_user_mac_addr[WLAN_MAC_ADDR_LEN];   /* ��ǰ������MAC��ַ */
    oal_uint32                      ul_rssi_timestamp;                  /* ���յ���֡��ʱ��� */
}hmac_fbt_notify_stru;




/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
oal_uint32  hmac_fbt_notify(hmac_vap_stru *pst_hmac_vap, hmac_fbt_notify_stru *pst_notify);
extern oal_uint32  hmac_fbt_init(hmac_vap_stru *pst_hmac_vap);
extern oal_uint32  hmac_config_fbt_set_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_fbt_start_scan(mac_vap_stru *pst_mac_vap);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fbt_main.h */
