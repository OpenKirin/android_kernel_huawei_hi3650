//******************************************************************************
// Copyright (C), 2008-2014, Hisilicon Technologies Co., Ltd.
// Project name   : hiaspv300
// File name      : reg_offset.h
// Author         : hexiangnan
// Abstract       : The offset address definition for the module ASP_HDMI
// Others         : Generated automatically by nManager 
//------------------------------------------------------------------------------
// Modification History: 
// 
//******************************************************************************

/* ASP_HDMI ģ��Ĵ�������ַ */
#define HI3650_ASP_HDMI_BASE                      (0xe804e400)

/******************************************************************************/
/*                      hiaspv300 ASP_HDMI �Ĵ�������                         */
/******************************************************************************/
#define HI3650_ASP_HDMI_TX3_REG               (HI3650_ASP_HDMI_BASE + 0x0)    /* ����ͨ��TX3���ƼĴ��� */
#define HI3650_ASP_HDMI_DER_REG               (HI3650_ASP_HDMI_BASE + 0x4)    /* ASP DMAʹ�ܼĴ��� */
#define HI3650_ASP_HDMI_DSTOP_REG             (HI3650_ASP_HDMI_BASE + 0x8)    /* ASP DMAֹͣʹ�ܼĴ��� */
#define HI3650_ASP_HDMI_ASS_ISR_REG           (HI3650_ASP_HDMI_BASE + 0xC)    /* ASPȫ���ж�״̬�Ĵ��� */
#define HI3650_ASP_HDMI_IRSR_REG              (HI3650_ASP_HDMI_BASE + 0x10)   /* ASPԭʼ״̬�Ĵ��� */
#define HI3650_ASP_HDMI_IER_REG               (HI3650_ASP_HDMI_BASE + 0x14)   /* ASP�ж�ʹ�ܼĴ��� */
#define HI3650_ASP_HDMI_IMSR_REG              (HI3650_ASP_HDMI_BASE + 0x18)   /* ASP���κ�״̬�Ĵ��� */
#define HI3650_ASP_HDMI_ICR_REG               (HI3650_ASP_HDMI_BASE + 0x1C)   /* ASP�ж�����Ĵ��� */
#define HI3650_ASP_HDMI_PCMNSSR_REG           (HI3650_ASP_HDMI_BASE + 0x20)   /* ͨ���¸���ʼ�Ĵ��� */
#define HI3650_ASP_HDMI_P30CGR_REG            (HI3650_ASP_HDMI_BASE + 0x28)   /* PCM3ͨ��0��������Ĵ��� */
#define HI3650_ASP_HDMI_P31CGR_REG            (HI3650_ASP_HDMI_BASE + 0x2C)   /* PCM3ͨ��1��������Ĵ��� */
#define HI3650_ASP_HDMI_P32CGR_REG            (HI3650_ASP_HDMI_BASE + 0x30)   /* PCM3ͨ��2��������Ĵ��� */
#define HI3650_ASP_HDMI_P33CGR_REG            (HI3650_ASP_HDMI_BASE + 0x34)   /* PCM3ͨ��3��������Ĵ��� */
#define HI3650_ASP_HDMI_P34CGR_REG            (HI3650_ASP_HDMI_BASE + 0x38)   /* PCM3ͨ��4��������Ĵ��� */
#define HI3650_ASP_HDMI_P35CGR_REG            (HI3650_ASP_HDMI_BASE + 0x3C)   /* PCM3ͨ��5��������Ĵ��� */
#define HI3650_ASP_HDMI_P36CGR_REG            (HI3650_ASP_HDMI_BASE + 0x40)   /* PCM3ͨ��6��������Ĵ��� */
#define HI3650_ASP_HDMI_P37CGR_REG            (HI3650_ASP_HDMI_BASE + 0x44)   /* PCM3ͨ��7��������Ĵ��� */
#define HI3650_ASP_HDMI_P3ASAR_REG            (HI3650_ASP_HDMI_BASE + 0x48)   /* PCM3Aͨ��������ʼ��ַ�Ĵ��� */
#define HI3650_ASP_HDMI_P3ADLR_REG            (HI3650_ASP_HDMI_BASE + 0x4C)   /* PCM3Aͨ�����˳��ȼĴ��� */
#define HI3650_ASP_HDMI_P3BSAR_REG            (HI3650_ASP_HDMI_BASE + 0x50)   /* PCM3Bͨ��������ʼ��ַ�Ĵ��� */
#define HI3650_ASP_HDMI_P3BDLR_REG            (HI3650_ASP_HDMI_BASE + 0x54)   /* PCM3Bͨ�����˳��ȼĴ��� */
#define HI3650_ASP_HDMI_SPDIFSEL_REG          (HI3650_ASP_HDMI_BASE + 0x58)   /* �������ݲ��Žӿ�ѡ��Ĵ��� */
#define HI3650_ASP_HDMI_P3ADLS_REG            (HI3650_ASP_HDMI_BASE + 0x5C)   /* DMAֹͣʱPCM3Aͨ�����˳���״̬�Ĵ��� */
#define HI3650_ASP_HDMI_P3BDLS_REG            (HI3650_ASP_HDMI_BASE + 0x60)   /* DMAֹͣʱPCM3Bͨ�����˳���״̬�Ĵ��� */
#define HI3650_ASP_HDMI_FDS_REG               (HI3650_ASP_HDMI_BASE + 0x64)   /* DMA�������ݻ���FIFO״̬�Ĵ��� */
#define HI3650_ASP_HDMI_P3ADL_REG             (HI3650_ASP_HDMI_BASE + 0x68)   /* PCM3Aͨ��DMA����ʣ�೤��״̬�Ĵ��� */
#define HI3650_ASP_HDMI_P3BDL_REG             (HI3650_ASP_HDMI_BASE + 0x6C)   /* PCM3Bͨ��DMA����ʣ�೤��״̬�Ĵ��� */
#define HI3650_ASP_HDMI_SECURE_REG            (HI3650_ASP_HDMI_BASE + 0x70)   /* ASP_HDMIģ�鰲ȫ�Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_ASPIF_SEL_REG        (HI3650_ASP_HDMI_BASE + 0x400)  /* SIO1��Ƶ�ӿ�ѡ��Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_RAW_INT_REG          (HI3650_ASP_HDMI_BASE + 0x408)  /* SIO1�ж�ԭʼ״̬�Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_INT_CLR_REG          (HI3650_ASP_HDMI_BASE + 0x40C)  /* SIO1�ж�����Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_INT_ENABLE_REG       (HI3650_ASP_HDMI_BASE + 0x410)  /* SIO1�ж�ʹ�ܼĴ��� */
#define HI3650_ASP_HDMI_SIO1_INT_MASKED_STATUS_REG  (HI3650_ASP_HDMI_BASE + 0x414)  /* SIO1�ж����κ�״̬�Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_I2S_SET_REG          (HI3650_ASP_HDMI_BASE + 0x41C)  /* SIO1 I2Sģʽ���� */
#define HI3650_ASP_HDMI_SIO1_I2S_CLR_REG          (HI3650_ASP_HDMI_BASE + 0x420)  /* SIO1 I2Sģʽ������� */
#define HI3650_ASP_HDMI_SIO1_TX_STA_REG           (HI3650_ASP_HDMI_BASE + 0x42C)  /* SIO1 ����ͨ��״̬�Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_CLR_REG              (HI3650_ASP_HDMI_BASE + 0x438)  /* SIO1��fifo����Ĵ��� */
#define HI3650_ASP_HDMI_SIO1_TST_TX0_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x440)  /* SIO1����0������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX1_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x444)  /* SIO1����1������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX2_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x448)  /* SIO1����2������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX3_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x44C)  /* SIO1����3������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX4_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x450)  /* SIO1����4������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX5_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x454)  /* SIO1����5������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX6_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x458)  /* SIO1����6������������ */
#define HI3650_ASP_HDMI_SIO1_TST_TX7_DATA_REG     (HI3650_ASP_HDMI_BASE + 0x45C)  /* SIO1����7������������ */
#define HI3650_ASP_HDMI_SPDIF_CTRL_REG            (HI3650_ASP_HDMI_BASE + 0x800)  /* SPDIF���ƼĴ��� */
#define HI3650_ASP_HDMI_SPDIF_CONFIG_REG          (HI3650_ASP_HDMI_BASE + 0x804)  /* SPDIF���üĴ��� */
#define HI3650_ASP_HDMI_SPDIF_INTRUPT_REG         (HI3650_ASP_HDMI_BASE + 0x808)  /* SPDIF���κ��ж�״̬�Ĵ��� */
#define HI3650_ASP_HDMI_SPDIF_INTR_MASK_REG       (HI3650_ASP_HDMI_BASE + 0x80C)  /* SPDIF�ж����μĴ��� */
#define HI3650_ASP_HDMI_SPDIF_FIFO_STATE_REG      (HI3650_ASP_HDMI_BASE + 0x810)  /* SPDIF FIFO״̬�Ĵ��� */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS1_REG      (HI3650_ASP_HDMI_BASE + 0x820)  /* �ŵ�״̬��Ϣ�Ĵ���1 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS2_REG      (HI3650_ASP_HDMI_BASE + 0x824)  /* �ŵ�״̬��Ϣ�Ĵ���2 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS3_REG      (HI3650_ASP_HDMI_BASE + 0x828)  /* �ŵ�״̬��Ϣ�Ĵ���3 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS4_REG      (HI3650_ASP_HDMI_BASE + 0x82C)  /* �ŵ�״̬��Ϣ�Ĵ���4 */
#define HI3650_ASP_HDMI_SPDIF_CH_STATUS5_REG      (HI3650_ASP_HDMI_BASE + 0x830)  /* �ŵ�״̬��Ϣ�Ĵ���5 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA1_REG      (HI3650_ASP_HDMI_BASE + 0x840)  /* �û����ݼĴ���1 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA2_REG      (HI3650_ASP_HDMI_BASE + 0x844)  /* �û����ݼĴ���2 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA3_REG      (HI3650_ASP_HDMI_BASE + 0x848)  /* �û����ݼĴ���3 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA4_REG      (HI3650_ASP_HDMI_BASE + 0x84C)  /* �û����ݼĴ���4 */
#define HI3650_ASP_HDMI_SPDIF_USER_DATA5_REG      (HI3650_ASP_HDMI_BASE + 0x850)  /* �û����ݼĴ���5 */
#define HI3650_ASP_HDMI_SPDIF_EDITION_REG         (HI3650_ASP_HDMI_BASE + 0x8F0)  /* �汾��Ϣ�Ĵ��� */
