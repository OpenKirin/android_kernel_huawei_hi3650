/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_bus_if.h
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��10��31��
  ����޸�   :
  ��������   : oal_bus_if.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��31��
    ��    ��   : t00231215
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_BUS_IF_H__
#define __OAL_BUS_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_mem.h"
#include "oal_schedule.h"
#include "oal_util.h"
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#include "oal_pci_if.h"
#endif
/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  4 �궨��
*****************************************************************************/
#define OAL_MAX_BAR_NUM          6          /* ÿ���豸���BAR���� */

/*****************************************************************************
  5 STRUCT����
*****************************************************************************/




/* �����豸��DEVICE�� */
typedef struct
{
    oal_uint32       ul_device_id;                       /* �豸��,��0x1151 */
    oal_void        *p_dev;                              /* ָ���豸��ָ�� */
    oal_uint32       ul_irq_num;                         /* �豸�жϺ� */
    oal_uint8        uc_chip_id;                         /* PCIe�ţ���PCIe0 */
    oal_uint8        uc_bar_num;                         /* BAR���� */
    oal_uint8        auc_resv[2];
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint32       aul_mem_start[OAL_WITP_MAX_BARS];   /* PCI�豸I/O������ʼ��ַ */
#else
    oal_uint32       aul_mem_start[1];
#endif
    oal_irq_dev_stru st_irq_info;
}oal_bus_dev_stru;

/* �����豸��CHIP�� */
typedef struct
{
    oal_uint8           uc_chip_id;                                /* PCIe�ţ���PCIe0 */
    oal_uint8        uc_device_num;			/* ��оƬ��device������Ӧ��С��WLAN_DEVICE_MAX_NUM_PER_CHIP */
    oal_uint8        auc_resv[2];
	oal_pci_dev_stru   *pst_pci_device;                            /* ָ������PCI�豸��ָ�� */
    oal_void           *p_pci_dbi_base;                            /* ָ��PCI�豸DBI�ӿڵ�ָ�룬��������PCIE�ڲ��Ĵ��� */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* оƬ����ַ */
    oal_uint32       aul_mem_start[OAL_WITP_MAX_BARS];
#else
    oal_uint32       aul_mem_start[1];
#endif
    /* device��Ϣ */
    oal_bus_dev_stru st_bus_dev[WLAN_DEVICE_MAX_NUM_PER_CHIP];
}oal_bus_chip_stru;


/*****************************************************************************
  6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 ��Ϣ����
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
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  oal_bus_exit(oal_bus_dev_stru *pst_bus_dev);
extern oal_void  oal_bus_find_dev_instance(oal_bus_dev_stru **ppst_bus_dev, oal_void *p_dev);
extern oal_uint32  oal_bus_send(oal_bus_dev_stru *pst_bus, oal_mem_stru *pst_msg_input);
extern oal_uint32  oal_bus_register_irq(oal_void *pst, oal_irq_intr_func p_func, oal_uint8 uc_chip_id, oal_uint8 uc_device_id);
extern oal_void oal_bus_unregister_irq(oal_uint8 uc_chip_id, oal_uint8 uc_device_id);
extern oal_void  oal_bus_get_chip_instance(oal_bus_chip_stru **ppst_bus_chip, oal_uint8 uc_index);
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
extern oal_void oal_bus_irq_affinity_init(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint32 ul_core_id);
#endif
#endif

extern oal_uint8  oal_bus_get_chip_num(oal_void);
extern oal_uint32  oal_bus_inc_chip_num(oal_void);
extern oal_void oal_bus_init_chip_num(oal_void);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_bus_if.h */
