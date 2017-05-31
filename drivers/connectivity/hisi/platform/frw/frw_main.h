/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_main
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : frw_main.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __FRW_MAIN_H__
#define __FRW_MAIN_H__

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
#include "frw_ext_if.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_MAIN_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define FRW_ERR_LOG(_uc_vap_id, _puc_string)
#define FRW_ERR_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_ERR_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define FRW_ERR_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define FRW_ERR_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define FRW_ERR_VAR(_uc_vap_id, _c_fmt, ...)

#define FRW_WARNING_LOG(_uc_vap_id, _puc_string)
#define FRW_WARNING_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_WARNING_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define FRW_WARNING_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define FRW_WARNING_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define FRW_WARNING_VAR(_uc_vap_id, _c_fmt, ...)

#define FRW_INFO_LOG(_uc_vap_id, _puc_string)
#define FRW_INFO_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_INFO_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define FRW_INFO_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define FRW_INFO_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define FRW_INFO_VAR(_uc_vap_id, _c_fmt, ...)

#ifdef _PRE_DEBUG_MODE
#define FRW_EVENT_INTERNAL(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)       oam_event_report(_puc_macaddr, _uc_vap_id, OAM_MODULE_ID_FRW, en_event_type, _puc_string)
#else
#define FRW_EVENT_INTERNAL(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)
#endif



#define FRW_TIMER_DEFAULT_TIME          10


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    FRW_TIMEOUT_TIMER_EVENT,      /* ��FRW_TIMER_DEFAULT_TIMEΪ���ڵĶ�ʱ���¼������� */

    FRW_TIMEOUT_SUB_TYPE_BUTT
}hmac_timeout_event_sub_type_enum;
typedef oal_uint8 hmac_timeout_event_sub_type_enum_uint8;



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
extern oal_int32  frw_main_init(oal_void);
extern oal_void  frw_main_exit(oal_void);
extern oal_void  frw_set_init_state(frw_init_enum_uint16 en_init_state);
extern frw_init_enum_uint16  frw_get_init_state(oal_void);












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_main */
