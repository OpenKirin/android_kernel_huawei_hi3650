/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_gpio.h
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2014��4��1��
  ����޸�   :
  ��������   : �͹���ƽ̨��ص�GPIO�ӿڷ�װ������Ԥ��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��1��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_GPIO_H__
#define __OAL_GPIO_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#ifdef _PRE_BOARD_SD5115
#include "hi_drv_common.h"
#include "hi_drv_gpio.h"

#endif
#include "arch/oal_gpio.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_GPIO_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef _PRE_BOARD_SD5115
#define oal_gpio_port_e             HI_GPIO_PORT_E
#define oal_gpio_bit_e              HI_GPIO_BIT_E
#define oal_gpio_bit_attr_s         hi_gpio_bit_attr_s
#define oal_gpio_port_attr_s        hi_gpio_port_attr_s
#define oal_level_e                 HI_LEVEL_E
#else

#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

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
#ifdef _PRE_BOARD_SD5115
/*GPIOλ�������Բ���*/
OAL_STATIC OAL_INLINE oal_uint oal_gpio_bit_attr_get(oal_gpio_port_e em_port, oal_gpio_bit_e em_bit, oal_gpio_bit_attr_s *pst_attr)
{
    return hi_kernel_gpio_bit_attr_get(em_port, em_bit, pst_attr);
}

OAL_STATIC OAL_INLINE oal_uint oal_gpio_bit_attr_set(oal_gpio_port_e em_port, oal_gpio_bit_e em_bit, oal_gpio_bit_attr_s *pst_attr)
{
    return hi_kernel_gpio_bit_attr_set(em_port, em_bit, pst_attr);
}

/*GPIO�˿���������,��������Ҫ��Ҫ�ر�GPIO�˿�ʱ�ӣ��ᵼ�¸���GPIO��ص�λ���ܹ���*/
OAL_STATIC OAL_INLINE oal_uint oal_gpio_port_attr_get(oal_gpio_port_e em_port, oal_gpio_port_attr_s *pst_attr)
{
    return hi_kernel_gpio_port_attr_get(em_port, pst_attr);
}

OAL_STATIC OAL_INLINE oal_uint oal_gpio_port_attr_set(oal_gpio_port_e em_port, oal_gpio_port_attr_s *pst_attr)
{
    return hi_kernel_gpio_port_attr_set(em_port, pst_attr);
}

/*GPIO�˿���� ����GPIO�˿�(0~7bit)ȫ������Ϊ���ģʽʱ, ͨ���˽ӿ������������*/
OAL_STATIC OAL_INLINE oal_uint oal_gpio_port_gpio_write(oal_gpio_port_e em_port, uint uc_data)
{
    return hi_kernel_gpio_write(em_port, uc_data);
}

/*GPIO�˿����� ����GPIO�˿�(0~7bit)ȫ������Ϊ����ģʽʱ, ͨ���˽ӿڵõ���������*/
OAL_STATIC OAL_INLINE oal_uint oal_gpio_port_gpio_read(oal_gpio_port_e em_port, uint *puc_data)
{
    return hi_kernel_gpio_read(em_port, puc_data);
}

/*GPIO��ƽ����, ����GPIO����Ϊ���ģʽʱ,ͨ���˽ӿ����������ƽ*/
OAL_STATIC OAL_INLINE oal_uint oal_gpio_bit_write(oal_gpio_port_e em_port, oal_gpio_bit_e em_bit, oal_level_e em_level)
{
    return hi_kernel_gpio_bit_write( em_port, em_bit, em_level);
}

/*GPIO�����ƽ��ȡ������GPIO����Ϊ����ʱ,��ͨ���˽ӿڵõ������ƽ*/
OAL_STATIC OAL_INLINE oal_uint oal_gpio_bit_read(oal_gpio_port_e em_port, oal_gpio_bit_e em_bit, oal_level_e *pem_level)
{
    return hi_kernel_gpio_bit_read( em_port, em_bit, pem_level);
}
#endif   /*_PRE_BOARD_SD5115*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_ext_if.h */
