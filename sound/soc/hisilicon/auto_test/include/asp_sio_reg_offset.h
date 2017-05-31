//******************************************************************************
// Copyright (C), 2008-2014, Hisilicon Technologies Co., Ltd.
// Project name   : hiaspv300
// File name      : reg_offset.h
// Author         : xxx
// Abstract       : The offset address definition for the module SIO
// Others         : Generated automatically by nManager 
//------------------------------------------------------------------------------
// Modification History: 
// 
//******************************************************************************

/* SIO ģ��Ĵ�������ַ */
#define HI3650_ASP_BASE                              (0xE804E800)

/******************************************************************************/
/*                      hiaspv300 SIO �Ĵ�������                              */
/******************************************************************************/
#define HI3650_ASP_SIO_VERSION_REG                   (0x3C)           /* �汾�Ĵ��� */
#define HI3650_ASP_SIO_MODE_REG                      (0x40)           /* ģʽ�Ĵ��� */
#define HI3650_ASP_SIO_INTSTATUS_REG                 (0x44)           /* �ж�״̬�Ĵ��� */
#define HI3650_ASP_SIO_INTCLR_REG                    (0x48)           /* �ж�����Ĵ���. */
#define HI3650_ASP_SIO_I2S_LEFT_XD_REG               (0x4C)           /* I2Sģʽ�����������ݷ��ͼĴ��� */
#define HI3650_ASP_SIO_I2S_RIGHT_XD_REG              (0x50)           /* I2Sģʽ�����������ݷ��ͼĴ���/PCMģʽ�µ����ݷ��ͼĴ���SIO_PCM_XD */
#define HI3650_ASP_SIO_I2S_LEFT_RD_REG               (0x54)           /* I2Sģʽ�����������ݽ��ռĴ��� */
#define HI3650_ASP_SIO_I2S_RIGHT_RD_REG              (0x58)           /* I2Sģʽ�����������ݽ��ռĴ���/PCMģʽ�½������ݼĴ��� */
#define HI3650_ASP_SIO_CT_SET_REG                    (0x5C)           /* ���ƼĴ���ʹ�ܼĴ��� */
#define HI3650_ASP_SIO_CT_CLR_REG                    (0x60)           /* ���ƼĴ�������Ĵ��� */
#define HI3650_ASP_SIO_RX_STA_REG                    (0x68)           /* SIO����״̬�Ĵ��� */
#define HI3650_ASP_SIO_TX_STA_REG                    (0x6C)           /* SIO����״̬�Ĵ��� */
#define HI3650_ASP_SIO_DATA_WIDTH_SET_REG            (0x78)           /* ���ݿ�ȼĴ��� */
#define HI3650_ASP_SIO_I2S_START_POS_REG             (0x7C)           /* I2S����������ʼλ�����ÿ��ƼĴ��� */
#define HI3650_ASP_SIO_I2S_POS_FLAG_REG              (0x80)           /* I2S��������������ǰλ��״̬�Ĵ��� */
#define HI3650_ASP_SIO_SIGNED_EXT_REG                (0x84)           /* ��λ���ݷ�����չʹ�ܼĴ��� */
#define HI3650_ASP_SIO_I2S_POS_MERGE_EN_REG          (0x88)           /* I2S�����������ݺϲ�ʹ�ܼĴ��� */
#define HI3650_ASP_SIO_INTMASK_REG                   (0x8C)           /* �ж����μĴ��� */
#define HI3650_ASP_SIO_I2S_DUAL_RX_CHN_REG           (0xA0)           /* ���պϲ����ݼĴ��� */
#define HI3650_ASP_SIO_I2S_DUAL_TX_CHN_REG           (0xC0)           /* ���ͺϲ����ݼĴ��� */

struct sio_congfig{
	 unsigned int tx_en;
	 unsigned int rx_en;
	 unsigned int frame_mode;
	 unsigned int mst_slv;
	 unsigned int lrclk_mode;
	 unsigned int chnnl_mode;
	 unsigned int io_wordlength;

	 unsigned int direct_loop;
	 unsigned int tx_clk_sel;
	 unsigned int rx_clk_sel;
	 unsigned int data_format;
	 unsigned int func_mode;
};