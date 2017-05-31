/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : asp_sio.c
  �� �� ��   : ����
  ��    ��   : w00262566
  ��������   : 2015��1��26��
  ����޸�   :
  ��������   : asp sio ģ��
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ļ�
******************************************************************************/

/****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>


#include "asp_sio_reg_offset.h"
#include "asp_sio.h"
#include "util.h"


/*****************************************************************************
  2 ȫ�ֱ�����궨�嶨��
*****************************************************************************/
#define DRV_NAME                    "asp_sio"
#define BASE_ADDR_ASP_SIO_SIZE      0x400
#define BASE_ADDR_ASP_SIO_AUDIO     0xE804F000
#define BASE_ADDR_ASP_SIO_VOICE     0xE804F400
#define BASE_ADDR_ASP_SIO_BT        0xE804F800
#define BASE_ADDR_ASP_SIO_MODEM     0xE804FC00

#define SIO_AUDIO                   1
#define SIO_VOICE                   2
#define SIO_BT                      3
#define SIO_MODEM                   4


static void* g_sio_audio_base_addr  = 0;
static void* g_sio_voice_base_addr  = 0;
static void* g_sio_bt_base_addr     = 0;
static void* g_sio_modem_base_addr  = 0;


static int asp_sio_probe(struct platform_device *pdev);
static int asp_sio_remove(struct platform_device *pdev);

static const struct of_device_id asp_sio_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver asp_sio_driver = {
    .probe      = asp_sio_probe,
    .remove     = asp_sio_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = asp_sio_of_match,
    },
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : asp_sio_reg_read
 ��������  : �Ĵ���������
 �������  : void *             �Ĵ�������ַ
             unsigned int       �Ĵ���ƫ��
 �������  : ��
 �� �� ֵ  : int                �Ĵ���ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int asp_sio_reg_read(void *base,unsigned int reg)
{
    volatile unsigned int ret = 0;
    pr_info("%s.\n",__FUNCTION__);

    ret = readl(base + reg);
    return ret;
}

/***************************************************************************
 �� �� ��  : asp_sio_reg_write
 ��������  : �Ĵ���д����
 �������  : void *             �Ĵ�������ַ
             unsigned int       �Ĵ���ƫ��
             unsigned int       �Ĵ�������ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_reg_write(void *base,unsigned int reg, unsigned int value)
{
    pr_info("%s.\n",__FUNCTION__);

    writel(value, base + reg);
    return;
}

/***************************************************************************
 �� �� ��  : asp_sio_audio_reg_read
 ��������  : sio audio�Ĵ���������
 �������  : unsigned int       �Ĵ���ƫ��
 �������  : ��
 �� �� ֵ  : int                �Ĵ���ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int asp_sio_audio_reg_read(unsigned int reg)
{
    volatile unsigned int ret = 0;
    pr_info("%s.\n",__FUNCTION__);

    ret = readl(g_sio_audio_base_addr + reg);
    return ret;
}

/***************************************************************************
 �� �� ��  : asp_sio_audio_reg_write
 ��������  : sio audio�Ĵ���д����
 �������  : unsigned int       �Ĵ���ƫ��
             unsigned int       �Ĵ���ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_audio_reg_write(unsigned int reg, unsigned int value)
{
    pr_info("%s.\n",__FUNCTION__);

    writel(value, g_sio_audio_base_addr + reg);
    return;
}

/***************************************************************************
 �� �� ��  : asp_sio_voice_reg_read
 ��������  : sio voice�Ĵ���������
 �������  : unsigned int       �Ĵ���ƫ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int asp_sio_voice_reg_read(unsigned int reg)
{
    volatile unsigned int ret = 0;
    pr_info("%s.\n",__FUNCTION__);

    ret = readl(g_sio_voice_base_addr + reg);
    return ret;
}
/***************************************************************************
 �� �� ��  : asp_sio_voice_reg_write
 ��������  : sio voice�Ĵ���д����
 �������  : unsigned int       �Ĵ���ƫ��
             unsigned int       �Ĵ���ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_voice_reg_write(unsigned int reg, unsigned int value)
{
    pr_info("%s.\n",__FUNCTION__);

    writel(value, g_sio_voice_base_addr + reg);
    return;
}

/***************************************************************************
 �� �� ��  : asp_sio_bt_reg_read
 ��������  : sio bt�Ĵ���������
 �������  : unsigned int       �Ĵ���ƫ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int asp_sio_bt_reg_read(unsigned int reg)
{
    volatile unsigned int ret = 0;
    pr_info("%s.\n",__FUNCTION__);

    ret = readl(g_sio_bt_base_addr + reg);
    return ret;
}
/***************************************************************************
 �� �� ��  : asp_sio_bt_reg_write
 ��������  : sio bt�Ĵ���д����
 �������  : unsigned int       �Ĵ���ƫ��
             unsigned int       �Ĵ���ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_bt_reg_write(unsigned int reg, unsigned int value)
{
    pr_info("%s.\n",__FUNCTION__);

    writel(value, g_sio_bt_base_addr + reg);
    return;
}
/***************************************************************************
 �� �� ��  : asp_sio_modem_reg_read
 ��������  : sio modem�Ĵ���������
 �������  : unsigned int       �Ĵ���ƫ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int asp_sio_modem_reg_read(unsigned int reg)
{
    volatile unsigned int ret = 0;
    pr_info("%s.\n",__FUNCTION__);

    ret = readl(g_sio_modem_base_addr + reg);
    return ret;
}
/***************************************************************************
 �� �� ��  : asp_sio_modem_reg_write
 ��������  : sio modem�Ĵ���д����
 �������  : unsigned int       �Ĵ���ƫ��
             unsigned int       �Ĵ���ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_modem_reg_write(unsigned int reg, unsigned int value)
{
    pr_info("%s.\n",__FUNCTION__);

    writel(value, g_sio_modem_base_addr + reg);
    return;
}

/*****************************************************************************
 �� �� ��  : asp_sio_reg_rw_test
 ��������  : sio�Ĵ�����д����
 �������  : int                          sio����
             struct at_util_reg_test_type �Ĵ�����������
             int                          �Ĵ������������С
 �������  : ��
 �� �� ֵ  : int ���Խ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int asp_sio_reg_rw_test(int sio, struct at_util_reg_test_type regs[], int size)
{
    if (SIO_AUDIO == sio ) {
        return at_util_reg_test (regs, size, asp_sio_audio_reg_read, asp_sio_audio_reg_write);
    }

    if (SIO_VOICE == sio ) {
        return at_util_reg_test (regs, size, asp_sio_voice_reg_read, asp_sio_voice_reg_write);
    }
    if (SIO_BT == sio ) {
        return at_util_reg_test (regs, size, asp_sio_bt_reg_read, asp_sio_bt_reg_write);
    }
    if (SIO_MODEM == sio ) {
        return at_util_reg_test (regs, size, asp_sio_modem_reg_read, asp_sio_modem_reg_write);
    }

    return AT_FAILED;
}

/**************************************************************************
 �� �� ��  : asp_sio_get_addr
 ��������  : sio����ַ��ȡ
 �������  : int                          sio����
 �������  : ��
 �� �� ֵ  : void*                        sio����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void *asp_sio_get_addr (int sio)
{
    void*   sio_base_addr = NULL;

    switch (sio) {
        case SIO_AUDIO:
            sio_base_addr = g_sio_audio_base_addr;
            break;
        case SIO_VOICE:
            sio_base_addr = g_sio_voice_base_addr;
            break;
        case SIO_BT:
            sio_base_addr = g_sio_bt_base_addr;
            break;
        case SIO_MODEM:
            sio_base_addr = g_sio_modem_base_addr;
            break;
        default:
            break;
    }

    return sio_base_addr;
}

/**************************************************************************
 �� �� ��  : asp_sio_set_pctrl
 ��������  : sio pctrl�ܽ�����
 �������  : int                          sio����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_set_pctrl(int sio)
{
    switch (sio) {
        case SIO_AUDIO:
        break;
        case SIO_VOICE:
        break;
        case SIO_BT:
        break;
        case SIO_MODEM:
        break;
        default:
        break;
    }
}

/**************************************************************************
 �� �� ��  : asp_sio_loop
 ��������  : sio ��������
 �������  : int                          sio����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_loop(int sio)
{
    void*   sio_base_addr;
    int     loop_bit;
    int     reg;

    // 0X3C bit8 = 0 normal;bi8 = 1 loop;
    loop_bit = 0x1<<8;

    sio_base_addr = asp_sio_get_addr (sio);

    reg = asp_sio_reg_read(sio_base_addr, HI3650_ASP_SIO_VERSION_REG);

    reg = reg | loop_bit;

    asp_sio_reg_write(sio_base_addr,HI3650_ASP_SIO_VERSION_REG, reg);
}

/**************************************************************************
 �� �� ��  : asp_sio_config_and_enable
 ��������  : sio ���ò�ʹ��
 �������  : int                          sio����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void asp_sio_config_and_enable (int sio)
{
    void*   sio_base_addr;

    sio_base_addr = asp_sio_get_addr(sio);

    /* set sio modem = I2S */
    asp_sio_reg_write(sio_base_addr,HI3650_ASP_SIO_MODE_REG, 0x0);

    /* set rx/tx data width = 16bit*/
    asp_sio_reg_write(sio_base_addr,HI3650_ASP_SIO_DATA_WIDTH_SET_REG, 0x09);

    /* set I2S merge = enable*/
    asp_sio_reg_write(sio_base_addr,HI3650_ASP_SIO_I2S_POS_MERGE_EN_REG, 0x1);

    /* set I2S start pos = 1,left first*/
    asp_sio_reg_write(sio_base_addr,HI3650_ASP_SIO_I2S_START_POS_REG, 0x1);
}

/*****************************************************************************
 �� �� ��  : asp_sio_probe
 ��������  : asp sio ������ʼ��
 �������  : struct platform_device* �豸ָ��
 �������  : ��
 �� �� ֵ  : ��ʼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
static int asp_sio_probe(struct platform_device *pdev)
{
    struct device *dev;
    pr_info("%s.\n",__FUNCTION__);

    dev = &pdev->dev;
    g_sio_audio_base_addr = devm_ioremap(dev,BASE_ADDR_ASP_SIO_AUDIO, BASE_ADDR_ASP_SIO_SIZE);
    if (!g_sio_audio_base_addr) {
        pr_info("cannot map register memory\n");
        return -ENOMEM;
    }
    g_sio_voice_base_addr = devm_ioremap(dev,BASE_ADDR_ASP_SIO_VOICE, BASE_ADDR_ASP_SIO_SIZE);
    if (!g_sio_voice_base_addr) {
        pr_info("cannot map register memory\n");
        return -ENOMEM;
    }
    g_sio_bt_base_addr = devm_ioremap(dev,BASE_ADDR_ASP_SIO_BT, BASE_ADDR_ASP_SIO_SIZE);
    if (!g_sio_bt_base_addr) {
        pr_info("cannot map register memory\n");
        return -ENOMEM;
    }
    g_sio_modem_base_addr = devm_ioremap(dev,BASE_ADDR_ASP_SIO_MODEM, BASE_ADDR_ASP_SIO_SIZE);
    if (!g_sio_modem_base_addr) {
        pr_info("cannot map register memory\n");
        return -ENOMEM;
    }

    return 0;
}


/*****************************************************************************
 �� �� ��  : asp_sio_remove
 ��������  : asp sio �����Ƴ�
 �������  : struct platform_device* �豸ָ��
 �������  : ��
 �� �� ֵ  : �����Ƴ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
static int asp_sio_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    if(NULL != g_sio_audio_base_addr){
        iounmap(g_sio_audio_base_addr);
    }
    if(NULL != g_sio_voice_base_addr){
        iounmap(g_sio_voice_base_addr);
    }
    if(NULL != g_sio_bt_base_addr){
        iounmap(g_sio_bt_base_addr);
    }
    if(NULL != g_sio_modem_base_addr){
        iounmap(g_sio_modem_base_addr);
    }
    return 0;
}


/*****************************************************************************
 �� �� ��  : asp_sio_init
 ��������  : asp sio ģ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ģ���ʼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
static int __init asp_sio_init(void)
{
    pr_info("%s \n",__FUNCTION__);
    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&asp_sio_driver);
}
module_init(asp_sio_init);


/*****************************************************************************
 �� �� ��  : asp_sio_exit
 ��������  : asp sio ģ���Ƴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ģ��ģ���Ƴ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
static void __exit asp_sio_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&asp_sio_driver);
}
module_exit(asp_sio_exit);


EXPORT_SYMBOL(asp_sio_reg_rw_test);
EXPORT_SYMBOL(asp_sio_loop);
EXPORT_SYMBOL(asp_sio_config_and_enable);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
