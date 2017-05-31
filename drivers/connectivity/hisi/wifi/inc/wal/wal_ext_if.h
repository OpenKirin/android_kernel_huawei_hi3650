/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_ext_if.h
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2012��9��20��
  ����޸�   :
  ��������   : wal���⹫���ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��20��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __WAL_EXT_IF_H__
#define __WAL_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_schedule.h"
#include "wlan_types.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_EXT_IF_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WAL_SDT_MEM_MAX_LEN             32      /* SDT��д�ڴ����󳤶� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* offloadʱ����ʾ��һ���˵�ö�� */
typedef enum
{
    WAL_OFFLOAD_CORE_MODE_HMAC,
    WAL_OFFLOAD_CORE_MODE_DMAC,

    WAL_OFFLOAD_CORE_MODE_BUTT
}wal_offload_core_mode_enum;
typedef oal_uint8 wal_offload_core_mode_enum_uint8;

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
/* SDT�ϴ��ӿڵ�ע�ắ������ */
typedef oal_int32   (* wal_sdt_up_func)(oal_netbuf_stru *pst_netbuf);

/*lint -e958*/ /*lint -e959*/
/* ��ȡ������ȫ�ֱ����Ľṹ�� */
#define WAL_GLB_VAR_NAME_LEN         (31)
#define WAL_GLB_VAR_VAL_LEN          (128)
typedef struct
{
	oal_uint8	uc_mode;             /* ��дģʽ */
	oal_uint16  us_len;              /* ��д���� */
	oal_uint8   en_offload_core_mode;
	oal_uint8	auc_global_value_name[WAL_GLB_VAR_NAME_LEN + 1];
	oal_uint8   auc_global_value[WAL_GLB_VAR_VAL_LEN];
}wal_sdt_global_var_stru;
/*lint -e958*/ /*lint -e959*/

/* ��ȡ�����üĴ����Ľṹ�� */
typedef struct
{
    oal_uint8       auc_vapname[16];
    oal_uint32      ul_addr;
    oal_uint16      us_len;
    oal_uint8       uc_mode;
    oal_uint8       auc_resv[1];
    oal_uint32      ul_reg_val;
}wal_sdt_reg_frame_stru;

/* ��ȡ�������ڴ�Ľṹ�� */
typedef struct
{
    oal_uint                            ul_addr;
    oal_uint16                          us_len;
    oal_uint8                           uc_mode;
    wal_offload_core_mode_enum_uint8    en_offload_core_mode;
    oal_uint8                           auc_data[WAL_SDT_MEM_MAX_LEN];
}wal_sdt_mem_frame_stru;

/* ά�⣬����ĳһ�־���event�ϱ����صĲ����ṹ�� */
typedef struct
{
    oal_int32                           l_event_type;
    oal_int32                           l_param;
}wal_specific_event_type_param_stru;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

extern oal_uint8         g_uc_custom_cali_done; /* ��ʶ�Ƿ����ϵ��һ��У׼ */

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_int32  wal_main_init(oal_void);
extern oal_void  wal_main_exit(oal_void);
extern oal_int32  wal_recv_memory_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_int32  wal_recv_global_var_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_int32  wal_recv_reg_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_int32  wal_recv_config_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);

extern oal_uint32  wal_hipriv_get_mac_addr(oal_int8 *pc_param,
                                            oal_uint8 auc_mac_addr[],
                                            oal_uint32 *pul_total_offset);

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
extern oal_uint32 wal_hipriv_register_inetaddr_notifier(oal_void);
extern oal_uint32 wal_hipriv_unregister_inetaddr_notifier(oal_void);
extern oal_uint32 wal_hipriv_register_inet6addr_notifier(oal_void);
extern oal_uint32 wal_hipriv_unregister_inet6addr_notifier(oal_void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_ext_if.h */
