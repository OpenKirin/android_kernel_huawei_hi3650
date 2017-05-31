/****************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ****************************************************************************
  �� �� ��   : test_asp_cfg.c
  �� �� ��   : ����
  ��    ��   : w00262566
  ��������   : 2015��1��27��
  ����޸�   :
  ��������   : �Զ������Թ�������ģ��
  �����б�   :
                at_util_reg_read_u32
                at_util_reg_write_u32
                at_util_mem_remap_type
                at_util_reg_test
                at_util_log_file_open
                at_util_log_file_close
                at_util_log
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

#include "util.h"
#include "core.h"
#include "asp_cfg.h"


/*****************************************************************************
  2 ȫ�ֱ�����궨�嶨��
*****************************************************************************/
#define DRV_NAME              "tc_cfg_reg"

static int tc_cfg_probe (struct platform_device *pdev);
static int tc_cfg_remove(struct platform_device *pdev);

static struct at_case_type* tc_cfg_reg;

static const struct of_device_id tc_cfg_of_match[] = {
    { .compatible = DRV_NAME, },
    {},
};

static struct platform_driver tc_cfg_driver = {
    .probe      = tc_cfg_probe,
    .remove     = tc_cfg_remove,
    .driver     = {
        .name   = DRV_NAME,
        .owner  = THIS_MODULE,
        .of_match_table = tc_cfg_of_match,
    },
};


struct at_util_reg_test_type asp_cfg_regs[] = {
  //  {0x0  , WO, 0x00000000, 0x0007FFFF, 0x00000000},                    //R_RST_CTRLEN,     外设软复位使能寄存器
    {0x4  , WO, 0x00000000, 0x00000000, 0x00000000},                    //R_RST_CTRLDIS,    外设软复位撤离寄存器


    {0xC  , WO, 0x00000000, 0x00ffffff, 0x00000000},                    //R_GATE_EN,        时钟使能寄存器
    {0x10 , WO, 0x00000000, 0x00ffffff, 0x00000000},                    //R_GATE_DIS,       时钟禁止寄存器
    {0x14 , RO, 0x00000000, 0x00000000, 0x01000000},                    //R_GATE_CLKEN      时钟使能状态寄存器
    {0x18 , RO, 0x00000000, 0x00000000, 0x7fffbfff},                    //R_GATE_CLKSTAT    时钟最终状态寄存器     ?


    {0x1C , RW, 0x000000FF, 0x0000007f, 0x0000007f},                    //R_GATE_CLKDIV_EN  时钟分频器门控使能寄存器
    {0x20 , RW, 0x0147AE14, 0x0147AE14, 0x0147AE14},                    //R_CLK1_DIV        分频比控制寄存器1
    {0x24 , RW, 0x01179EC9, 0x01179EC9, 0x01179EC9},                    //R_CLK2_DIV        分频比控制寄存器2
    {0x28 , RW, 0x00001707, 0xffff1707, 0x00001707},                    //R_CLK3_DIV        分频比控制寄存器3
    {0x2C , RW, 0x00001717, 0xffff1717, 0x00001717},                    //R_CLK4_DIV        分频比控制寄存器4
    {0x30 , RW, 0x00003F3F, 0xffff3f3f, 0x00003f3f},                    //R_CLK5_DIV        分频比控制寄存器5
    {0x34 , RW, 0x00003F3F, 0xffff3f3f, 0x00003f3f},                    //R_CLK6_DIV        分频比控制寄存器6

//    {0x38 , RW, 0x0000000F, 0xffffffff, 0x0000ffff},                    //R_CLK_SEL         时钟选择寄存器
 //   {0x3C , RW, 0x00000000, 0x0000ffff, 0x0000ffff},                    //R_DSP_NMI         DSP NMI中断产生寄存器
    {0x40 , RW, 0x00000000, 0x0000ffff, 0x0000ffff},                    //R_DSP_PRID        DSP PRID设置寄存器
    {0x44 , RW, 0x00000001, 0x00000001, 0x00000001},                    //R_DSP_RUNSTALL    DSP RUNSTALL设置寄存器

    {0x48 , RW, 0x00000000, 0x00000001, 0x00000001},                    //R_DSP_STATVECTORSEL   DSP STATVECTORSEL设置寄存器
    {0x4C , RW, 0x00000000, 0x00000001, 0x00000001},                    //R_DSP_OCDHALTONRESET  DSP OCDHALTONRESET设置寄存器   ?

    {0x50 , RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_DSP_STATUS          DSP 状态寄存器

    {0x54 , RW, 0x00000000, 0xffffffff, 0x0000ffff},                    //R_DMAC_SEL            DMAC通道选择寄存器
    {0x58 , RW, 0x853E4000, 0xffffffff, 0xffffffff},                    //R_BUS_PRIORITY        总线优先级配置寄存器
    {0x5C , RW, 0x00000000, 0xffff0fff, 0x00000fff},                    //R_CG_EN               自动门控使能寄存器 ?
    {0x60 , RW, 0x00000000, 0xffff0fff, 0x00000fff},                    //R_OCRAM_RET           ocram低功耗配置寄存器
    {0x64 , RO, 0x00000000, 0xffffffff, 0x0000ffff},                    //R_INTR_NS_INI         非安全中断原始状态寄存器
    {0x68 , RW, 0x00000000, 0x0000000d, 0x0000000d},                    //R_INTR_NS_EN          非安全中断使能寄存器
    {0x6C , RO, 0x00000000, 0x0000000f, 0x00000000},                    //R_INTR_NS_MASK        非安全中断屏蔽后状态寄存器
    {0x70 , RO, 0x01011111, 0x00000000, 0x0000000f},                    //R_DBG_SET_AHB2AXI     付强桥DBG信号设置寄存器   ?
    {0x74 , RO, 0x00000000, 0x00ffffff, 0x00000000},                    //R_DBG_STATUS_AHB2AXI  付强桥DBG信号状态寄存器   ?
    {0x78 , RO, 0x00000000, 0x00000000, 0x00000000},                    //R_DLOCK_BP            总线防挂死bypass寄存器  ?


    {0x7C, RO,  0x00000000, 0xffffffff, 0x00000001},                    //R_DSP_BINTERRUPT      上报到hifi dsp的中断信号只读寄存器
    {0x84, WO,  0x00000000, 0xffff0000, 0x00000000},                    //R_DSP_RAM_RET         ?
    {0x84, RW,  0x00000000, 0x0000ffff, 0x00000000},
    {0x100, WO, 0x0000FFFF, 0xffff0000, 0x0000FFFF},                    //R_TZ_SECURE_N         ?
    {0x100, WO, 0x0000FFFF, 0xffffffff, 0xffffffff},
  //  {0x104, RW, 0x000003FF, 0x000003ff, 0x000003ff},                    //R_OCRAM_R0SIZE        ?
    {0x108, RW, 0x00000000, 0x0000000f, 0x00000000},                    //R_SIO_LOOP_SECURE_N   ?

    {0x10C, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_INTR_S_INI          安全中断原始状态寄存器
    {0x110, RW, 0x00000000, 0x00000003, 0x00000000},                    //R_INTR_S_EN           安全中断使能寄存器
    {0x114, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_INTR_S_MASK         安全中断屏蔽后状态寄存器
    {0x118, RW, 0x00000000, 0x000001fd, 0x00000000},                    //R_DSP_REMAPPING_EN    dsp地址重映射使能寄存器

    {0x11C, RW, 0x00000000, 0xFFF00000, 0x00000000},                    //R_DSP_REMAPPING_SRC_BASE_ADDR DSP 地址重映射寄存器
    {0x120, RW, 0x00000000, 0xFFF00000, 0x00000000},                    //R_DSP_REMAPPING_DES_BASE_ADDR DSP 地址重映射寄存器

    {0x124, RW, 0x00000000, 0x000003ff, 0x000003ff},                    //R_DDR_HARQ_REMAP_EN               DDR与Harq Memory remap控制寄存器
    {0x128, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_HARQ_REMAP_SRC_BASE_ADDR    DDR与Harq Memory remap源基地址寄存器
    {0x130, RW, 0x00000000, 0x000003FF, 0x000003FF},                    //R_DDR_MMBUF_REMAP_EN              DDR与MMBUF remap控制寄存器
    {0x134, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_MMBUF_REMAP_SRC_BASE_ADDR   DDR与MMBUF remap源基地址寄存器
    {0x138, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_MMBUF_REMAP_DES_BASE_ADDR   DDR与MMBUF remap目标基地址寄存器


    {0x13C, RW, 0x00000000, 0x000003ff, 0x000003ff},                    //R_DDR_OCRAM_REMAP_EN              DDR与OCRAM remap控制寄存器
    {0x140, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_OCRAM_REMAP_SRC_BASE_ADDR   DDR与OCRAM remap源基地址寄存器
    {0x144, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_DDR_OCRAM_REMAP_DES_BASE_ADDR   DDR与OCRAM remap目标基地址寄存器

    {0x148, WO, 0x000000FD, 0xffff0000, 0xffff0000},                    //R_MMBUF_CTRL                      MMBUF CTRL配置寄存器
    {0x148, WO, 0x000000FD, 0xffffffff, 0xffffffff},

    {0x14C, RW, 0x00000000, 0x000007FF, 0x000007FF},                    //R_HIFIDSP_CLK_DIV_AUTO                HIFIDSP时钟频率自动调频配置寄存器
    {0x150, RW, 0x00000110, 0x0000ffff, 0x0000ffff},                    //R_INTR_FREQ_OFFSET_CFG                频偏记录模块配置寄存器
    {0x160, RW, 0x00000000, 0x0000000f, 0x0000000f},                    //R_ACCESS_ADDR_MONITOR_EN_ADDR         内存监控模块使能配置寄存器
    {0x164, WO, 0x00000000, 0X00000001, 0x00000000},                    //R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR   内存监控模块中断清零配置寄存器
    {0x168, RW, 0x00000000, 0x0000000f, 0x0000000f},                    //R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR    内存监控模块中断使能配置寄存器
    {0x16C, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR  内存监控模块中断状态寄存器
    {0x170, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR0_BASE_ADDR      内存监控模块0基地址配置寄存器
    {0x174, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR0_LEN_ADDR       内存监控模块0地址长度配置寄存器
    {0x178, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_ACCESS_ADDR_MONITOR0_HIT_AWADDR     内存监控模块0越界的写地址记录寄存器
    {0x17C, RO, 0x00000000, 0x00000000, 0x00000000},                    //R_ACCESS_ADDR_MONITOR0_HIT_ARADDR     内存监控模块0越界的读地址记录寄存器
    {0x180, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR1_BASE_ADDR      内存监控模块1基地址配置寄存器
    {0x184, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR1_LEN_ADDR       内存监控模块1地址长度配置寄存器
    {0x188, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR1_HIT_AWADDR     内存监控模块1越界的写地址记录寄存器
    {0x18C, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR1_HIT_ARADDR     内存监控模块1越界的读地址记录寄存器
    {0x190, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR2_BASE_ADDR      内存监控模块2基地址配置寄存器
    {0x194, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR2_LEN_ADDR       内存监控模块2地址长度配置寄存器
    {0x198, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR2_HIT_AWADDR     内存监控模块2越界的写地址记录寄存器
    {0x19C, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR2_HIT_ARADDR     内存监控模块2越界的读地址记录寄存器
    {0x1A0, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR3_BASE_ADDR      内存监控模块3基地址配置寄存器
    {0x1A4, RW, 0x00000000, 0xFFFFF000, 0xFFFFF000},                    //R_ACCESS_ADDR_MONITOR3_BASE_ADDR      内存监控模块3地址长度配置寄存器
    {0x1A8, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR3_HIT_AWADDR     内存监控模块3越界的写地址记录寄存器
    {0x1AC, RO, 0x00000000, 0xffffffff, 0x00000000},                    //R_ACCESS_ADDR_MONITOR3_HIT_ARADDR     内存监控模块3越界的读地址记录寄存器
    {0x1B0, RW, 0x01A80090, 0xffffffff, 0xffffffff},                    //R_MEMORY_CTRL                         memory控制配置寄存器


    /*reserved
    {0x1B4, RW, 0x00000001, 0x00000001, 0x00000001},                    //R_SLIMBUS_PRIMARY_ADDR                slimbus primary配置寄存器
    {0x1B8, RW, 0x00000000, 0x00000000, 0x00000001},                    //R_SLIMBUS_ID_ADDR                     slimbus id配置寄存器
    {0x200, RW, 0x00000000, 0x00000000, 0x00000001},                    //R_SECURE_AUTHORITY_EN                 安全访问属性控制寄存器
    */

};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : tc_cfg_read_write_test
 ��������  : ����cfg�еļĴ���
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
void tc_cfg_read_write_test(void)
{
    char* tc_cfg_read_write_test_success = "tc_cfg_read_write_test result success\n";
    char* tc_cfg_read_write_test_failed  = "tc_cfg_read_write_test result faied\n";
    pr_info("Audio: test reg beg\n");

    if(AT_SUCCESS == asp_cfg_reg_rw_test(asp_cfg_regs, sizeof(asp_cfg_regs) / sizeof(asp_cfg_regs[0]))){
        at_util_log(tc_cfg_read_write_test_success,strlen(tc_cfg_read_write_test_success));
    }else {
        at_util_log(tc_cfg_read_write_test_failed,strlen(tc_cfg_read_write_test_failed));
    }

    pr_info("Audio: test reg end\n");
}
EXPORT_SYMBOL(tc_cfg_read_write_test);


/*****************************************************************************
 �� �� ��  : tc_cfg_reg_prepare
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
int tc_cfg_reg_prepare(int test_pram)
{
    pr_info("Audio: tc_cfg_reg_prepare \n");
    asp_cfg_powerup();
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : tc_cfg_reg_beg
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
int tc_cfg_reg_beg(int test_pram)
{
    pr_info("Audio: tc_cfg_reg_beg \n");
    tc_cfg_read_write_test();
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : tc_cfg_reg_stop
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
int tc_cfg_reg_stop(int test_pram)
{
    pr_info("Audio: tc_cfg_reg_stop \n");
    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : tc_cfg_read_write_test_individual
 ��������  : ����cfg�еļĴ���
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
void tc_cfg_read_write_test_individual(void)
{
    pr_info("Audio: tc_cfg_read_write_test_individual beg\n");
    char* tc_cfg_read_log_beg = "tc_cfg_read_write_test_individual beg\n";
    char* tc_cfg_read_log_end = "tc_cfg_read_write_test_individual end\n";
    at_util_log(tc_cfg_read_log_beg,strlen(tc_cfg_read_log_beg));
    tc_cfg_reg_prepare(0);
    tc_cfg_reg_beg(0);
    tc_cfg_reg_stop(0);
    at_util_log(tc_cfg_read_log_end,strlen(tc_cfg_read_log_end));
    pr_info("Audio: tc_cfg_read_write_test_individual end\n");
}
EXPORT_SYMBOL(tc_cfg_read_write_test_individual);

/*****************************************************************************
 �� �� ��  : tc_cfg_probe
 ��������  : tc cfg ������ʼ��
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
static int tc_cfg_probe(struct platform_device *pdev)
{
    pr_info("%s.\n",__FUNCTION__);

    tc_cfg_reg = devm_kmalloc(&pdev->dev,sizeof(struct at_case_type), GFP_ATOMIC);
    if(NULL == tc_cfg_reg){
         return -ENOMEM;
    }

    tc_cfg_reg->test_name   = "tc_cfg_reg";
    tc_cfg_reg->test_params = 0;
    tc_cfg_reg->test_pri    = AT_CASE_PRI_HIG;
    tc_cfg_reg->prepare     = tc_cfg_reg_prepare;
    tc_cfg_reg->begin       = tc_cfg_reg_beg;
    tc_cfg_reg->stop        = tc_cfg_reg_stop;

    //at_core_register_test_case(tc_cfg_reg);

    return 0;
}

/*****************************************************************************
 �� �� ��  : tc_cfg_remove
 ��������  : tc cfg �����Ƴ�
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
static int tc_cfg_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    at_core_unregister_test_case(tc_cfg_reg);
    kfree(tc_cfg_reg);
    return 0;
}

/*****************************************************************************
 �� �� ��  : tc_cfg_init
 ��������  : tc cfg ģ���ʼ��
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
static int __init tc_cfg_init(void)
{
    pr_info("%s \n",__FUNCTION__);

    platform_device_register_simple(DRV_NAME,0,NULL,0);

    return platform_driver_register(&tc_cfg_driver);
}
module_init(tc_cfg_init);


/*****************************************************************************
 �� �� ��  : tc_cfg_exit
 ��������  : tc cfg ģ���˳�
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
static void __exit tc_cfg_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&tc_cfg_driver);
}
module_exit(tc_cfg_exit);


MODULE_AUTHOR("wangbingda 00262566");
MODULE_DESCRIPTION("hisilicon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
