/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_ext_if.h
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2012��9��20��
  ����޸�   :
  ��������   : oal���⹫���ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��20��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_EXT_IF_H__
#define __OAL_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_util.h"
#include "oal_hardware.h"
#include "oal_schedule.h"
#include "oal_bus_if.h"
#include "oal_mem.h"
#include "oal_net.h"
#include "oal_list.h"
#include "oal_queue.h"
#include "oal_workqueue.h"
#include "arch/oal_ext_if.h"
#include "oal_thread.h"

//#include "oal_gpio.h"
#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
#include "oal_aes.h"
#include "oal_gpio.h"
#endif

/*infusion����Ԥ�����֧�ֲ��ã��ڴ˶����֧��infusion��飬��ʽ���벻��Ҫ*/
#ifdef _PRE_INFUSION_CHECK
#include "oal_infusion.h"
#endif
/*end infusion*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_exception_rst.h"
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    OAL_TRACE_ENTER_FUNC,
    OAL_TRACE_EXIT_FUNC,

    OAL_TRACE_DIRECT_BUTT
}oal_trace_direction_enum;
typedef oal_uint8 oal_trace_direction_enum_uint8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_void                       *g_pst_5115_sys_ctl;
extern oal_void                       *g_pst_5610_mode;
extern oal_void                       *g_pst_5610_gpio;
#if(_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
#if(_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)
extern oal_void                       *g_pst_5610_gpio1;
extern oal_void                       *g_pst_5610_gpio2;
#endif
#endif

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
extern oal_int32   oal_main_init(oal_void);
extern oal_void    oal_main_exit(oal_void);
extern oal_uint32 oal_chip_get_version(oal_void);
extern oal_uint8 oal_chip_get_device_num(oal_uint32 ul_chip_ver);

#ifdef HAVE_HISI_NFC
extern oal_void save_nfc_lowpower_log(oal_void);
extern oal_void hi_wlan_power_off(void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_ext_if.h */
