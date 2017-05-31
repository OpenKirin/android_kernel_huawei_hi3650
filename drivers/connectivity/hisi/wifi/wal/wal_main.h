/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_main
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : wal_main.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __WAL_MAIN_H__
#define __WAL_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_MAIN_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#ifdef _PRE_WLAN_DFT_EVENT
#define WAL_EVENT_WID(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)  oam_event_report(_puc_macaddr, _uc_vap_id, OAM_MODULE_ID_WAL, en_event_type, _puc_string)
#else
#define WAL_EVENT_WID(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* HOST CRX�¼������� */
typedef enum
{
    WAL_HOST_CRX_SUBTYPE_CFG,
    WAL_HOST_CRX_SUBTYPE_RESET_HW,

    WAL_HOST_CRX_SUBTYPE_BUTT
}wal_host_crx_subtype_enum;
typedef oal_uint8 wal_host_crx_subtype_enum_uint8;

/* HOST DRX�¼������� */
typedef enum
{
    WAL_HOST_DRX_SUBTYPE_TX,

    WAL_HOST_DRX_SUBTYPE_BUTT
}wal_host_drx_subtype_enum;
typedef oal_uint8 wal_host_drx_subtype_enum_uint8;

extern oam_wal_func_hook_stru     g_st_wal_drv_func_hook;

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
extern oal_int32  wal_main_init(oal_void);
extern oal_void  wal_main_exit(oal_void);
extern oal_wakelock_stru   g_st_wal_wakelock;
#define wal_wake_lock()  oal_wake_lock(&g_st_wal_wakelock)
#define wal_wake_unlock()  oal_wake_unlock(&g_st_wal_wakelock)
#ifdef _PRE_E5_722_PLATFORM
#define wifi_wake_lock()  oal_wake_lock(&g_st_wifi_wakelock)
#define wifi_wake_unlock()  oal_wake_unlock(&g_st_wifi_wakelock)
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_main */
