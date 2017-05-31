/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Sdt_drv.h
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��1��23��
  ����޸�   :
  ��������   : Sdt_drv.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��23��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __SDT_DRV_H__
#define __SDT_DRV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_workqueue.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_SDT_DRV_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* memory */
#if(_PRE_TARGET_PRODUCT_TYPE_E5 == _PRE_CONFIG_TARGET_PRODUCT)
#define NETLINK_TEST                        23   /* E5ƽ̨��Ϊ23 */
#else
#define NETLINK_TEST                        28   /* ����5610 ATP���̣���ֹЭ��ų�ͻ����һ�޸�Ϊ28 */
#endif
#define DATA_BUF_LEN                        2048

/*head and end */
#define SDT_DRV_PKT_START_FLG               (0x7e)
#define SDT_DRV_PKT_END_FLG                 (0x7e)
#define SDT_DRV_GET_LOW_BYTE(_data)         ((oal_uint8)(_data & 0xff))
#define SDT_DRV_GET_HIGH_BYTE(_data)        ((oal_uint8)((_data & 0xff00)>>8))
#define SDT_DRV_PKT_TAIL_LEN                1

#define MAX_NUM                             256

#define MAX_QUEUE_COUNT                     20
#define MAX_CO_SIZE                         896
#define MAX_NLMSG_LEN                       1024

#define SDT_DRV_REPORT_NO_CONNECT_FREQUENCE 500

#define SDT_DRV_PKT_RECORD_MAX_NUM          100

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum OM_NETLINK_MSG_TYPE_ENUM
{
    NETLINK_MSG_HELLO = 0,               /* netlink connect hello */
    NETLINK_MSG_SDTCMD,                  /* std with device */
    NETLINK_MSG_SDTCMD_OPS               /* device to SDT need encapsulation */
};

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
typedef struct
{
    oal_uint32       ul_cmd;
    oal_uint32       ul_len;
} sdt_drv_netlink_msg_hdr_stru;

/* SDT��������PC�˵�����ͷ�ṹ��һ��8���ֽ� */
typedef struct
{
    oal_uint8    uc_data_start_flg;         /* ���ݿ�ʼ�ı�־��ͬʱҲ�����ݽ����ı�־ */
    oam_data_type_enum_uint8    en_msg_type;               /* ��������(LOG,EVENT,OTA��) */
    oal_uint8    uc_prim_id;                /* ͨѶԭ�� */
    oal_uint8    uc_resv[1];                /* ���� */
    oal_uint8    uc_data_len_low_byte;      /* ���ݳ��ȵĵ�8���� */
    oal_uint8    uc_data_len_high_byte;     /* ���ݳ��ȵĸ�8���� */
    oal_uint8    uc_sequence_num_low_byte;  /* ���кŵ�8���� */
    oal_uint8    uc_sequence_num_high_byte; /* ���кŸ�8���� */
}sdt_drv_pkt_hdr_stru;

/* SDT DRV���ȫ�ֹ���ṹ */
typedef struct
{
    oal_workqueue_stru                      *oam_rx_workqueue;
    oal_work_stru                            rx_wifi_work;
    oal_netbuf_head_stru                     rx_wifi_dbg_seq;
    oal_sock_stru                           *pst_nlsk;
    oal_uint8                               *puc_data;
    oal_uint32                               ul_usepid;
    oal_uint16                               us_sn_num;
    oal_uint8                                auc_resv[2];
    oal_spin_lock_stru                       st_spin_lock;
    oal_atomic                               ul_unconnect_cnt; /* ͳ�ƽ���send����ʱnetlinkû�����ӵĴ��� */
}sdt_drv_mng_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_int32  sdt_drv_main_init(oal_void);
extern oal_void  sdt_drv_main_exit(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Sdt_drv.h */
