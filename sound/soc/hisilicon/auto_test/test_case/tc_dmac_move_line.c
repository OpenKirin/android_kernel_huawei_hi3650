/****************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ****************************************************************************
  �� �� ��   : tc_dmac_move_line.c
  �� �� ��   : ����
  ��    ��   : w00262566
  ��������   : 2015��1��27��
  ����޸�   :
  ��������   : ���԰���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��1��27��
    ��    ��   : w00262566
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/syscalls.h>


#include "asp_edmac_reg_offset.h"
#include "util.h"
#include "core.h"
#include "asp_cfg.h"
#include "asp_dmac.h"


/*****************************************************************************
  2 ȫ�ֱ�����궨�嶨��
*****************************************************************************/
#define DRV_NAME              "tc_dmac_move_line"
#define TX_SIZE               0x100
static int tc_dmac_move_line_probe (struct platform_device *pdev);
static int tc_dmac_move_line_remove(struct platform_device *pdev);

static struct at_case_type  *tc_dmac_move_line;
static struct device        *tc_dev;

static const struct of_device_id tc_dmac_move_line_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver tc_dmac_move_line_driver = {
    .probe      = tc_dmac_move_line_probe,
    .remove     = tc_dmac_move_line_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = tc_dmac_move_line_of_match,
    },
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

static int tc_dmac_move_line_get_result(void* src,void* des,int len)
{
    int i,value_src,value_des,result;

    result = AT_SUCCESS;

    for (i = 0; i < len;i=i+4) {
        value_src = *(int*)(src+i);
        value_des = *(int*)(src+i);

        if(value_src != value_des){
            result = AT_FAILED;
            pr_err("%s, dmac_move error\n", __FUNCTION__);
            break;
        }
    }
    return result;
}
int tc_dmac_move_line_ddr2ddr(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    //alloc memery for dma
    src_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&src_addr_phys,GFP_KERNEL);
    des_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&des_addr_phys,GFP_KERNEL);

    pr_info("audio:src_addr_virts:0x%pK,src_addr_phys = 0x%x \n",src_addr_virts, src_addr_phys);
    pr_info("audio:des_addr_virts:0x%pK,des_addr_phys = 0x%x \n",des_addr_virts, des_addr_phys);

    if (NULL == src_addr_virts || NULL == des_addr_virts) {
        pr_err("%s, malloc memary error\n", __FUNCTION__);
        return AT_FAILED;
    }

    //init memery
    pr_info("audio:init memery to 0x12345678");
    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(src_addr_virts+i)) = 0x12345678;
        *((unsigned int *)(des_addr_virts+i)) = 0x87654321;
    }

     asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

     return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);

}

int tc_dmac_move_line_ddr2ocram(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    src_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&src_addr_phys,GFP_KERNEL);

    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(src_addr_virts+i)) = 0x12345678;
    }

    des_addr_phys = 0xE8000000;

    des_addr_virts = at_util_mem_remap_and_init (des_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}


int tc_dmac_move_line_ocram2ddr(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    des_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&des_addr_phys,GFP_KERNEL);

    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(des_addr_virts+i)) = 0x12345678;
    }

    src_addr_phys = 0xE8000000;

    src_addr_virts = at_util_mem_remap_and_init (src_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}


int tc_dmac_move_line_ddr2itcm(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    src_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&src_addr_phys,GFP_KERNEL);

    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(src_addr_virts+i)) = 0x12345678;
    }

    des_addr_phys = 0xE8070000;

    des_addr_virts = at_util_mem_remap_and_init (des_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}


int tc_dmac_move_line_itcm2ddr(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    des_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&des_addr_phys,GFP_KERNEL);

    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(des_addr_virts+i)) = 0x12345678;
    }

    src_addr_phys = 0xE8070000;

    src_addr_virts = at_util_mem_remap_and_init (src_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}


int tc_dmac_move_line_ddr2dtcm(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    src_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&src_addr_phys,GFP_KERNEL);

    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(src_addr_virts+i)) = 0x12345678;
    }

    des_addr_phys = 0xE8058000;

    des_addr_virts = at_util_mem_remap_and_init (des_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}

int tc_dmac_move_line_dtcm2ddr(void)
{
    int i;
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;

    des_addr_virts = dma_alloc_coherent (tc_dev, TX_SIZE,&des_addr_phys,GFP_KERNEL);

    for (i = 0; i < TX_SIZE;i=i+4) {
        *((unsigned int *)(des_addr_virts+i)) = 0x12345678;
    }

    src_addr_phys = 0xE8058000;

    src_addr_virts = at_util_mem_remap_and_init (src_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}

int tc_dmac_move_line_ocram2dtcm(void)
{
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;


    src_addr_phys  = 0xE8000000;
    des_addr_virts = 0xE8070000;

    src_addr_virts = at_util_mem_remap_and_init (src_addr_phys, TX_SIZE, 0x12345678);
    des_addr_virts = at_util_mem_remap_and_init (des_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);
}


int tc_dmac_move_line_dtcm2ocram(void)
{
    dma_addr_t  src_addr_phys;
    dma_addr_t  des_addr_phys;
    void       *src_addr_virts;
    void       *des_addr_virts;


    src_addr_phys  = 0xE8070000;
    des_addr_virts = 0xE8000000;

    src_addr_virts = at_util_mem_remap_and_init (src_addr_phys, TX_SIZE, 0x12345678);
    des_addr_virts = at_util_mem_remap_and_init (des_addr_phys, TX_SIZE, 0x87654321);

    asp_dmac_move_line(src_addr_phys,des_addr_phys,TX_SIZE, 0);

    return tc_dmac_move_line_get_result(src_addr_virts,des_addr_virts,TX_SIZE);

}

/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_test
 ��������  : dmac move line ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
void tc_dmac_move_line_test(void)
{
    char tmp_buf[100];
    int  tmp_len;

    if(AT_FAILED == tc_dmac_move_line_ddr2ddr()){
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_ddr2ddr failed");
    } else {
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_ddr2ddr success");
    }
    at_util_log(tmp_buf,tmp_len);
//    tc_dmac_move_line_ddr2ocram();
//    tc_dmac_move_line_ocram2ddr();

    if(AT_FAILED == tc_dmac_move_line_ddr2itcm()){
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_ddr2itcm failed");
    } else {
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_ddr2itcm success");
    }
    at_util_log(tmp_buf,tmp_len);

    if(AT_FAILED == tc_dmac_move_line_itcm2ddr()){
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_itcm2ddr failed");
    } else {
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_itcm2ddr success");
    }
    at_util_log(tmp_buf,tmp_len);

    if(AT_FAILED == tc_dmac_move_line_ddr2dtcm()){
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_ddr2dtcm failed");
    } else {
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_ddr2dtcm success");
    }
    at_util_log(tmp_buf,tmp_len);


    if(AT_FAILED == tc_dmac_move_line_dtcm2ddr()){
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_dtcm2ddr failed");
    }else {
        tmp_len = sprintf(tmp_buf,"%s\n","tc_dmac_move_line_dtcm2ddr success");
    }
    at_util_log(tmp_buf,tmp_len);

//    tc_dmac_move_line_ocram2dtcm();
//    tc_dmac_move_line_dtcm2ocram();
}
EXPORT_SYMBOL(tc_dmac_move_line_test);


/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_prepare
 ��������  : ����ǰ����
 �������  : int ���Բ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int tc_dmac_move_line_prepare(int test_pram)
{
    asp_cfg_powerup();
    asp_cfg_ip_init();
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_beg
 ��������  : ���Դ���
 �������  : int ���Բ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int tc_dmac_move_line_beg(int test_pram)
{
    tc_dmac_move_line_test();
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_stop
 ��������  : ���Ժ���
 �������  : int ���Բ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
int tc_dmac_move_line_stop(int test_pram)
{
    return AT_SUCCESS;
}



/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_probe
 ��������  : tc dmac move line ������ʼ��
 �������  : struct platform_device* �豸ָ��
 �������  : ��
 �� �� ֵ  : ��ʼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��27��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
static int tc_dmac_move_line_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    tc_dmac_move_line = devm_kmalloc(&pdev->dev,sizeof(struct at_case_type), GFP_ATOMIC);
    if(NULL == tc_dmac_move_line){
         return -ENOMEM;
    }

    tc_dmac_move_line->test_name   = "tc_dmac_move_line";
    tc_dmac_move_line->test_params = 0;
    tc_dmac_move_line->test_pri    = AT_CASE_PRI_NOR;
    tc_dmac_move_line->prepare     = tc_dmac_move_line_prepare;
    tc_dmac_move_line->begin       = tc_dmac_move_line_beg;
    tc_dmac_move_line->stop        = tc_dmac_move_line_stop;

    at_core_register_test_case(tc_dmac_move_line);
    tc_dev = &pdev->dev;
    return 0;
}

/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_remove
 ��������  : tc dmac move line �����Ƴ�
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
static int tc_dmac_move_line_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    at_core_unregister_test_case(tc_dmac_move_line);
    kfree(tc_dmac_move_line);
    return 0;
}

/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_init
 ��������  : tc dmac move line ģ���ʼ��
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
static int __init tc_dmac_move_line_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&tc_dmac_move_line_driver);
}
module_init(tc_dmac_move_line_init);


/*****************************************************************************
 �� �� ��  : tc_dmac_move_line_exit
 ��������  : tc dmac reg ģ���˳�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ģ���˳����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : w00262566
    �޸�����   : �����ɺ���

*****************************************************************************/
static void __exit tc_dmac_move_line_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&tc_dmac_move_line_driver);
}
module_exit(tc_dmac_move_line_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
