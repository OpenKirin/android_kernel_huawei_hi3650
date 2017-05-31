/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_data_acq.h
  �� �� ��   : ����
  ��    ��   : z00241943
  ��������   : 2014��4��22��
  ����޸�   :
  ��������   : dmac_data_acq.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��22��
    ��    ��   : z00241943
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_DATA_ACQ_H__
#define __DMAC_DATA_ACQ_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_mem.h"
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "frw_ext_if.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "hal_witp_rf.h"
#include "oal_net.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DATA_ACQ_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DMAC_DATA_ACQ_MAX_UNITLEN 65528
#define DMAC_DATA_ACQ_MAX_UNITNUM 65535
#define DMAC_DATA_ACQ_MAX_LEN     (1024 * 4096)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/********************* ��������� *********************/
typedef enum
{
    DMAC_DATA_ACQ_PRE      = 0,       /* ���ݲɼ�׼������ MAC�Ĵ��� */
    DMAC_DATA_ACQ_COND     = 1,       /* ���ݲɼ��������� PHY�Ĵ��� */
    DMAC_DATA_ACQ_ENABLE   = 2,       /*       ���ݲɼ�ʹ�ܱ�־     */
    DMAC_DATA_ACQ_STATUS   = 3,       /*    ���ݲɼ����״̬��ѯ    */
    DMAC_DATA_ACQ_RECODE   = 4,       /*    ���ݲɼ���ɻ�ȡ����    */

    DMAC_DATA_ACQ_BUTT
} dmac_data_acq_enum;
typedef oal_uint8 dmac_data_acq_enum_uint8;

/********************* �ɼ��������� *********************/
typedef enum
{
    DMAC_DATA_ACQ_COND_ADC_TH     = 1,  /* ADC�����޶� */
    DMAC_DATA_ACQ_COND_AGC_BH     = 2,  /*   AGC����   */
    DMAC_DATA_ACQ_COND_AGC_LOCK   = 4,  /*   AGC����   */
    DMAC_DATA_ACQ_COND_PACK_L     = 8,  /*  �������Ч */

    DMAC_DATA_ACQ_COND_BUTT       = 16
} dmac_data_acq_cond_enum;
typedef oal_uint8 dmac_data_acq_cond_enum_uint8;

/********************* BITλѡ���� *********************/
typedef enum
{
    DMAC_DATA_ACQ_BIT_0_7          = 0,  /* �ɼ�[7:0]bits ADC ����������Ͳ��� */
    DMAC_DATA_ACQ_BIT_1_8          = 1,  /* �ɼ�[8:1]bits ADC ����������Ͳ��� */
    DMAC_DATA_ACQ_BIT_2_9          = 2,  /* �ɼ�[9:2]bits ADC ����������Ͳ��� */

    DMAC_DATA_ACQ_BIT_BUTT
} dmac_data_acq_bit_enum;
typedef oal_uint8 dmac_data_acq_bit_enum_uint8;

/********************* ���ݲɼ�״̬ *********************/
typedef enum
{
    DMAC_DATA_ACQ_STATUS_INIT            = 0,  /*       ��ʼ��״̬      */
    DMAC_DATA_ACQ_STATUS_MAC_REG         = 1,  /* ��������MAC�Ĵ���״̬ */
    DMAC_DATA_ACQ_STATUS_PHY_REG         = 2,  /* ��������PHY�Ĵ���״̬ */
    DMAC_DATA_ACQ_STATUS_ENABLE          = 3,  /*    �������ݲɼ�״̬   */
    DMAC_DATA_ACQ_STATUS_COMPLETE        = 4,  /*  �������ݲɼ����״̬ */

    DMAC_DATA_ACQ_STATUS_BUTT
} dmac_data_acq_status_enum;
typedef oal_uint8 dmac_data_acq_status_enum_uint8;

/********************* ���ݲɼ�״̬ *********************/
typedef enum
{
    DMAC_DATA_ACQ_SEND_TYPE_INFO         = 0,  /* ������APP�����ݲɼ���Ϣ */
    DMAC_DATA_ACQ_SEND_TYPE_UNIT         = 1,  /*    ������APP�����ݵ�Ԫ  */
    DMAC_DATA_ACQ_SEND_TYPE_READY        = 2,  /*   APP����Խ������ݣ�Driver��������  */
    DMAC_DATA_ACQ_SEND_TYPE_FAIL         = 3,  /*   APP����Խ������ݣ�Driver��������  */
    DMAC_DATA_ACQ_SEND_TYPE_ACK          = 4,  /*   APP����Խ������ݣ�Driver��������  */

    DMAC_DATA_ACQ_SEND_TYPE_BUTT
} dmac_data_acq_send_type_enum;
typedef oal_uint8 dmac_data_acq_send_type_enum_uint8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_uint8  *g_puc_daq_mem_addr;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* PHY�Ĵ�����Ӧ���ݲɼ������Ĵ����ṹ�� */
typedef struct
{
    oal_uint32   bit_cfg_real_sample_bits_sel      :   2,    /*   bitλѡ��   */
                 bit_cfg_real_sample_data_th       :   9,    /*    ADC����    */
                 bit_reserved                      :   5,    /*     ����      */
                 bit_cfg_real_sample_cond_ctrl     :   4,    /*   ��������    */
                 bit_cfg_real_sample_ch_sel        :   2,    /*   ͨ��ѡ��    */
                 bit_cfg_real_sample_en            :   1,    /*   ʹ�ܱ�־    */
                 bit_reserved1                     :   9;    /*     ����      */
}dmac_data_acq_cond_stru;

/* MAC������ݲɼ��Ĵ����ṹ�� */
typedef struct
{
    oal_uint8                *puc_start_addr;    /*   ��ʼ��ַ   */
    oal_bool_enum_uint8       en_daq_enable;     /* �Ƿ�ʹ������ */
    oal_uint8                 uc_resv[1];
    oal_uint16                us_num;            /* �ɼ���Ԫ���� */
    oal_uint16                us_depth;          /*   �ɼ����   */
    oal_uint16                us_len_unit;       /* �ɼ���Ԫ���� */
}dmac_data_acq_prep_stru;

typedef struct
{
    oal_workqueue_stru                      *daq_rx_workqueue;
    oal_work_stru                            rx_daq_work;
    oal_netbuf_head_stru                     rx_daq_dbg_seq;
}dmac_data_acq_workqueue_stru;

/* ���ݲɼ����ýṹ�� */
typedef struct
{
    dmac_data_acq_status_enum_uint8       en_daq_status;         /*   ��ǰ�Ƿ�����ʹ�����ݲɼ�����    */
    oal_bool_enum_uint8                   en_daq_apprecv_ready;  /*   ��ǰAPP�Ƿ���������ϴ�����  */
    oal_bool_enum_uint8                   uc_ack_flag;           /*          ackȷ�ϱ�־           */
    oal_bool_enum_uint8                   en_daq_app_error;      /*            app�쳣             */
    oal_uint32                            ul_length;             /*       ��� * ��С <= 4M      */
    oal_uint32                            ul_daq_sn;             /*            �������            */
    dmac_data_acq_workqueue_stru          st_daq_workqueue;
    dmac_data_acq_cond_stru               st_daq_cond;
    dmac_data_acq_prep_stru               st_daq_prep_info;
}dmac_data_acq_stru;

/* �����ϱ�app�Ľṹ�� */
typedef struct
{
    oal_uint32      ul_daq_addr;         /* ���������׵�ַ */
    oal_uint32      ul_data_len;         /* ���������ܵĳ��� */
    oal_uint32      ul_unit_len;         /* ��Ԫ���ݵ���󳤶�:������(daq_unit_head)ͷ���� */
}dmac_data_acq_info_stru;

/* ���ɵ�Ԫͷ�ṹ�� */
typedef struct
{
    dmac_data_acq_send_type_enum_uint8  en_send_type;        /* ���ɵ�Ԫ�������к� */
    oal_uint8                           uc_resv[3];
    oal_uint32                          ul_msg_sn;           /* ���ɵ�Ԫ�������к� */
    oal_uint32                          ul_data_len;         /* ��ǰ��Ԫ���� */
}dmac_data_acq_data_head_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern dmac_data_acq_stru g_st_data_acq;

extern oal_uint32  dmac_config_data_acq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_data_acq_init(oal_void);
extern oal_uint32  dmac_data_acq_exit(oal_void);


#endif  /* end of _PRE_WLAN_FEATURE_DAQ */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_data_acq.h */
