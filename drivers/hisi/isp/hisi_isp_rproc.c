/*
 * hisilicon efuse driver, hisi_isp_rproc.c
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 */

/*lint -e747 -e715
 -esym(747,*) -esym(715,*)*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/mod_devicetable.h>
#include <linux/amba/bus.h>
#include <linux/dma-mapping.h>
#include <linux/remoteproc.h>
#include <linux/platform_data/remoteproc-hisi.h>
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/hisi_mailbox_dev.h>
#include <linux/delay.h>
#include <linux/kfifo.h>
#include <linux/mutex.h>
#include <linux/regulator/consumer.h>
#include <linux/clk.h>
#include <linux/rproc_share.h>
#include <linux/sched/rt.h>
#include <linux/kthread.h>
#include <global_ddr_map.h>
#include <linux/iommu.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/miscdevice.h>
#include "./hisi_isp_rproc.h"

#define ISP_MEM_SIZE    0x10000
#define TMP_SIZE		0x1000
#define MAX_SIZE		64

enum ISP_CLK_TYPE {
    A7_CLK = 0,
    FUNC_CLK = 1,
    CLK_MAX
};

struct hisp_pwr_ops {
    struct mutex lock;
    unsigned int refs_a7;
	unsigned int refs_isp;
    unsigned int refs_ispinit;
	int (*ispup)(struct hisp_pwr_ops *);
	int (*ispdn)(struct hisp_pwr_ops *);
    int (*ispinit)(struct hisp_pwr_ops *);
    int (*ispexit)(struct hisp_pwr_ops *);
    int (*a7up)(struct hisp_pwr_ops *);
    int (*a7dn)(struct hisp_pwr_ops *);
};

struct hisi_isp_nsec {
    struct device *device;
    struct platform_device *isp_pdev;
    struct hisp_pwr_ops *isp_ops;
    void __iomem *crgperi_base;
    void __iomem *vivobus_base;
	void __iomem *isp_regs_base;
    struct regulator *ispsrt_supply;
    struct clk *ispclk[CLK_MAX];
    unsigned int ispclk_value[CLK_MAX];
    void *isp_dma_va;
    dma_addr_t isp_dma;
    unsigned int pgd_base;
    unsigned int remap_addr;
};

struct hisi_ispmmu_regs_s {
    unsigned int offset;
    unsigned int data;
    int num;
};

/* Define the union U_VP_WR_PREFETCH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpwr_index_id0        : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    vpwr_index_id1        : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 16  ; /* [30..15]  */
        unsigned int    vpwr_prefetch_bypass  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP_WR_PREFETCH;

/* Define the union U_VP_RD_PREFETCH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vprd_index_id0        : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    vprd_index_id1        : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 16  ; /* [30..15]  */
        unsigned int    vprd_prefetch_bypass  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP_RD_PREFETCH;

/* Define the union U_CVDR_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    du_write_threshold    : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    stall_srt_du_threshold : 8  ; /* [15..8]  */
        unsigned int    max_axiread_id        : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 3   ; /* [23..21]  */
        unsigned int    max_axiwrite_tx       : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 1   ; /* [29]  */
        unsigned int    force_rd_clk_on       : 1   ; /* [30]  */
        unsigned int    force_wr_clk_on       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CVDR_CFG;

/* Define the union U_CVDR_WR_QOS_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr_qos_threshold_01_stop  : 4  ; /* [3..0] */
        unsigned int    wr_qos_threshold_01_start : 4  ; /* [7..4] */
        unsigned int    wr_qos_threshold_10_stop  : 4  ; /* [11..8] */
        unsigned int    wr_qos_threshold_10_start : 4  ; /* [15..12] */
        unsigned int    wr_qos_threshold_11_stop  : 4  ; /* [19..16] */
        unsigned int    wr_qos_threshold_11_start : 4  ; /* [23..20] */
        unsigned int    reserved_0                : 2  ; /* [25..24] */
        unsigned int    wr_qos_rt_min             : 2  ; /* [27..26] */
        unsigned int    wr_qos_srt_max            : 2  ; /* [29..28] */
        unsigned int    wr_qos_sr                 : 2  ; /* [31..30] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CVDR_WR_QOS_CFG;

static struct hisi_isp_nsec nsec_rproc_dev;

struct hisi_ispmmu_regs_s ispmmu_up_regs[] = {
    {SMMU_APB_REG_SMMU_SCR_REG, SCR_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_INTMASK_NS_REG, INTMASK_NS, 1},
    {SMMU_APB_REG_SMMU_INTMAS_S_REG, INTMASK_S, 1},
    {SMMU_APB_REG_SMMU_CB_TTBR0_REG, PGD_BASE, 1},
    {SMMU_APB_REG_SMMU_RLD_EN0_NS_REG, RLD_EN0_NS_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_RLD_EN1_NS_REG, RLD_EN1_NS_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_RLD_EN2_NS_REG, RLD_EN2_NS_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_SMRX_NS_0_REG, SMRX_NS_DEFAULT, 80},
    {SMMU_APB_REG_SMMU_SCR_S_REG, SCR_S_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_RLD_EN0_S_REG, RLD_EN0_S_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_RLD_EN1_S_REG, RLD_EN1_S_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_RLD_EN2_S_REG, RLD_EN2_S_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_SCB_TTBCR_REG, SCB_TTBCR_DEFAULT, 1},
    {SMMU_APB_REG_SMMU_SCB_TTBR_REG, PGD_BASE, 1},
    {SMMU_APB_REG_SMMU_SMRX_S_0_REG, SMRX_NS_DEFAULT, 80},
};

static inline int is_ispup(void)
{
	struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    return ((readl(dev->crgperi_base + CRG_C88_PERIPHISP_SEC_RSTSTAT) & BIT_RST_ISP) ?
        1 : 0);
}

static int need_powerup(unsigned int refs)
{
	if (refs == 0xffffffff)
		pr_err("%s:need_powerup exc, refs == 0xffffffff\n", __func__);

	return ((refs == 0) ? 1 : 0);
}

static int need_powerdn(unsigned int refs)
{
    if (refs == 0xffffffff)
		pr_err("%s:need_powerdn exc, refs == 0xffffffff\n", __func__);

    return ((refs == 1) ? 1 : 0);
}

static void ispmmu_init(void)
{
	struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    int i = 0, num = 0;
	void __iomem *smmu_base = dev->isp_regs_base + ISP_BASE_ADDR_SSMMU;
	unsigned int pgt_addr = dev->pgd_base;

    pr_info("%s: +\n", __func__);

    writel((readl(ISP_020010_MODULE_CGR_TOP + dev->isp_regs_base) | SMMU_CLK_ENABLE),
            ISP_020010_MODULE_CGR_TOP + dev->isp_regs_base);

	for (i = 0; i < sizeof(ispmmu_up_regs) / sizeof(struct hisi_ispmmu_regs_s); i++) {
        for (num = 0; num < ispmmu_up_regs[i].num; num++) {
            writel(ispmmu_up_regs[i].data, smmu_base + ispmmu_up_regs[i].offset + num * 4);
        }
	}

	writel(pgt_addr, SMMU_APB_REG_SMMU_CB_TTBR0_REG + smmu_base);
	writel(pgt_addr, SMMU_APB_REG_SMMU_SCB_TTBR_REG + smmu_base);
	writel(0x1, SMMU_APB_REG_SMMU_SCB_TTBCR_REG + smmu_base);
	writel(0x1, SMMU_APB_REG_SMMU_CB_TTBCR_REG + smmu_base);
	/*set jpeg for nosec*/
    //writel(0x6,ISP_BASE_ADDR_SUB_CTRL + ISP_CORE_CTRL_S);
    //writel(0x8,ISP_SUB_CTRL_S + ISP_BASE_ADDR_SUB_CTRL);

	/*set mid*/
    writel(MID_FOR_JPGEN, dev->isp_regs_base + ISP_BASE_ADDR_CVDR_SRT + CVDR_SRT_AXI_CFG_VP_WR_25);
    writel(MID_FOR_JPGEN, dev->isp_regs_base + ISP_BASE_ADDR_CVDR_SRT + CVDR_SRT_AXI_CFG_NR_RD_1);

    pr_info("%s: -\n", __func__);
}

static int ispmmu_exit(void)
{
    pr_info("%s: +\n", __func__);

    return 0;
}

static void ispcvdr_init(void)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    void __iomem *isp_base = dev->isp_regs_base;
    void __iomem *isprt_base = dev->isp_regs_base + ISP_BASE_ADDR_CVDR_RT;
    void __iomem *ispsrt_base = dev->isp_regs_base + ISP_BASE_ADDR_CVDR_SRT;
    void __iomem *ispsctrl_base = dev->isp_regs_base + ISP_SUB_CTRL_BASE_ADDR;

    pr_info("%s: +\n", __func__);
    writel((readl(ISP_020010_MODULE_CGR_TOP + isp_base) | CVDR_CLK_ENABLE),
            ISP_020010_MODULE_CGR_TOP + isp_base);

    /* CVDR RT*/
    writel(0x0B0B4001, isprt_base + CVDR_RT_CVDR_CFG_REG);
    /* CVDR SRT*/
    writel(0x0B132201, ispsrt_base + CVDR_SRT_CVDR_CFG_REG);
    //CVDR_RT QOS
    writel(0xF8765432, isprt_base + CVDR_RT_CVDR_WR_QOS_CFG_REG);
    writel(0xF8122334, isprt_base + CVDR_RT_CVDR_RD_QOS_CFG_REG);

    //CVDR_SRT QOS
    writel(0xD0765432, ispsrt_base + CVDR_SRT_CVDR_WR_QOS_CFG_REG);
    writel(0xD0122334, ispsrt_base + CVDR_SRT_CVDR_RD_QOS_CFG_REG);

    //CVDR SRT PORT STOP
    writel(0x00020000, ispsrt_base + CVDR_SRT_NR_RD_CFG_3_REG);
    writel(0x00020000, ispsrt_base + CVDR_SRT_VP_WR_IF_CFG_10_REG);
    writel(0x00020000, ispsrt_base + CVDR_SRT_VP_WR_IF_CFG_11_REG);

    //JPGENC limiter DU=8
    writel(0x00000000, ispsrt_base + CVDR_SRT_VP_WR_IF_CFG_25_REG);
    writel(0x80060100, ispsrt_base + CVDR_SRT_NR_RD_CFG_1_REG);
    writel(0x0F001111, ispsrt_base + CVDR_SRT_LIMITER_NR_RD_1_REG);

    //SRT READ
    writel(0x00026E10, ispsctrl_base + SUB_CTRL_ISP_FLUX_CTRL2_0_REG);
    writel(0x0000021F, ispsctrl_base + SUB_CTRL_ISP_FLUX_CTRL2_1_REG);
    //SRT WRITE
    writel(0x00027210, ispsctrl_base + SUB_CTRL_ISP_FLUX_CTRL3_0_REG);
    writel(0x0000024E, ispsctrl_base + SUB_CTRL_ISP_FLUX_CTRL3_1_REG);
    pr_info("%s: -\n", __func__);
}

static void set_isp_nonsec(void)
{
    pr_alert("%s: +\n", __func__);
    atfisp_set_nonsec();
    pr_alert("%s: -\n", __func__);
}

static void disreset_a7(unsigned int remap_addr)
{
    pr_info("%s:enter\n", __func__);
    atfisp_disreset_a7(remap_addr);
    pr_info("%s:exit\n", __func__);
}

static void isp_a7_qos_cfg(struct hisi_isp_nsec *dev)
{
    void __iomem* vivobus_base = dev->vivobus_base;

    pr_info("[%s] +\n", __func__);
    if (vivobus_base == NULL) {
        pr_err("%s: vivobus_base remap fail\n", __func__);
        return;
    }

    __raw_writel(QOS_PRIO_3,      (volatile void __iomem*)(vivobus_base + ISP_RD_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE, (volatile void __iomem*)(vivobus_base + ISP_RD_QOS_MODE));
    __raw_writel(QOS_PRIO_3,      (volatile void __iomem*)(vivobus_base + ISP_WR_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE, (volatile void __iomem*)(vivobus_base + ISP_WR_QOS_MODE));
    __raw_writel(QOS_PRIO_4,      (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_PRIORITY));
    __raw_writel(QOS_FIX_MODE,    (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_MODE));
    __raw_writel(QOS_PRIO_4,      (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_PRIORITY));
    __raw_writel(QOS_FIX_MODE,    (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_MODE));
    __raw_writel(QOS_PRIO_3,      (volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE, (volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_MODE));
    __raw_writel(QOS_PRIO_3,      (volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE, (volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_MODE));

    pr_info("QOS : ISP.rd.(prio.0x%x, mode.0x%x), ISP.wr.(prio.0x%x, mode.0x%x), A7.rd.(prio.0x%x, mode.0x%x), A7.wr.(prio.0x%x, mode.0x%x),ISP1.rd.(prio.0x%x, mode.0x%x), ISP1.wr.(prio.0x%x, mode.0x%x)\n",
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP_RD_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP_RD_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP_WR_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP_WR_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_MODE)));

}

static int nsec_a7_powerup(struct hisp_pwr_ops *ops)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;

    pr_info("[%s] + refs_a7.0x%x\n", __func__, ops->refs_a7);

    if (!need_powerup(ops->refs_a7)) {
        ops->refs_a7++;
        pr_info("[%s] + refs_isp.0x%x\n", __func__, ops->refs_a7);
        return 0;
    }

    /* need config by secure core */
    disreset_a7(dev->remap_addr);

    ops->refs_a7++;
    pr_info("[%s] - refs_a7.0x%x\n", __func__, ops->refs_a7);
    return 0;
}

static int nsec_a7_powerdn(struct hisp_pwr_ops *ops)
{
    pr_info("[%s] + refs_a7.0x%x\n", __func__, ops->refs_a7);

    if (!need_powerdn(ops->refs_a7)) {
        ops->refs_a7--;
        pr_info("[%s] + refs_a7.0x%x\n", __func__, ops->refs_a7);
        return 0;
    }

    //writel(0x00000030, dev->crgperi_base + CRG_C80_PERIPHISP_SEC_RSTEN);
    ops->refs_a7--;
    pr_info("[%s] - refs_a7.0x%x\n", __func__, ops->refs_a7);
    return 0;
}

static int ispa7_setclk_enable(struct hisi_isp_nsec *dev)
{
	int ret;

    if ((ret = clk_set_rate(dev->ispclk[A7_CLK], dev->ispclk_value[A7_CLK])) < 0) {
        pr_err("[%s] Failed: clk_set_rate.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = clk_prepare_enable(dev->ispclk[A7_CLK])) < 0) {
        pr_err("[%s] Failed: clk_prepare_enable.%d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static int ispfunc_setclk_enable(struct hisi_isp_nsec *dev)
{
    int ret;

    if ((ret = clk_set_rate(dev->ispclk[FUNC_CLK], dev->ispclk_value[FUNC_CLK])) < 0) {
        pr_err("[%s] Failed: clk_set_rate.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = clk_prepare_enable(dev->ispclk[FUNC_CLK])) < 0) {
        pr_err("[%s] Failed: clk_prepare_enable.%d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static void ispa7_clk_disable(struct hisi_isp_nsec *dev)
{
    clk_disable_unprepare(dev->ispclk[A7_CLK]);
}

static void ispfunc_clk_disable(struct hisi_isp_nsec *dev)
{
    clk_disable_unprepare(dev->ispclk[FUNC_CLK]);
}

static int nsec_isp_powerup(struct hisp_pwr_ops *ops)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    int ret;

    pr_info("[%s] + refs_isp.0x%x\n", __func__, ops->refs_isp);
    if (!need_powerup(ops->refs_isp)) {
        ops->refs_isp++;
        pr_info("[%s] + refs_isp.0x%x\n", __func__, ops->refs_isp);
        return 0;
    }

    if ((ret = ispfunc_setclk_enable(dev)) < 0) {
        pr_err("Failed: ispfunc_setclk_enable.%d\n", ret);
        return ret;
    }

    if ((ret = ispa7_setclk_enable(dev)) < 0) {
        pr_err("Failed: ispa7_setclk_enable.%d\n", ret);
        goto ispa7_err;
    }

    if ((ret = regulator_enable(dev->ispsrt_supply)) != 0) {
        pr_err("Failed: regulator_enable.%d\n", ret);
        goto regulator_err;
    }

    ops->refs_isp++;
    pr_err("[%s] - refs_isp.0x%x\n", __func__, ops->refs_isp);

    return 0;

regulator_err:
    ispa7_clk_disable(dev);
ispa7_err:
    ispfunc_clk_disable(dev);

    return ret;
}

static int nsec_isp_powerdn(struct hisp_pwr_ops *ops)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    int ret = 0;

    pr_info("[%s] + refs_isp.0x%x\n", __func__, ops->refs_isp);

    if (!need_powerdn(ops->refs_isp)) {
        ops->refs_isp--;
        pr_info("[%s] + refs_isp.0x%x\n", __func__, ops->refs_isp);
        return 0;
    }

    if ((ret = regulator_disable(dev->ispsrt_supply)) != 0)
        pr_err("Failed: regulator_disable.%d\n", ret);

    ispa7_clk_disable(dev);
    ispfunc_clk_disable(dev);

    ops->refs_isp--;
    pr_info("[%s] - refs_isp.0x%x\n", __func__, ops->refs_isp);

    return 0;
}

static int nsec_isp_init(struct hisp_pwr_ops *ops)
{
    pr_info("[%s] + refs_ispinit.0x%x\n", __func__, ops->refs_ispinit);
    if (!need_powerup(ops->refs_ispinit)) {
        ops->refs_ispinit++;
        pr_info("[%s] + refs_ispinit.0x%x\n", __func__, ops->refs_ispinit);
        return 0;
    }

	ispmmu_init();
	ispcvdr_init();

	ops->refs_ispinit++;
    pr_err("[%s] - refs_ispinit.0x%x\n", __func__, ops->refs_ispinit);

	return 0;
}

static int nsec_isp_exit(struct hisp_pwr_ops *ops)
{
    int ret;

    pr_info("[%s] + refs_ispinit.%x\n", __func__, ops->refs_ispinit);
    if (!need_powerdn(ops->refs_ispinit)) {
        ops->refs_ispinit--;
        pr_info("[%s] + refs_ispinit.%x\n", __func__, ops->refs_ispinit);
        return 0;
    }

	if ((ret = ispmmu_exit()))
		pr_err("%s: failed, ispmmu_exit, ret.%d\n", __func__, ret);

	ops->refs_ispinit--;
    pr_err("[%s] - refs_ispinit.%x\n", __func__, ops->refs_ispinit);

    return 0;
}

static struct hisp_pwr_ops isp_pwr_ops = {
    .lock   = __MUTEX_INITIALIZER(isp_pwr_ops.lock),
    .a7up   = nsec_a7_powerup,
    .a7dn   = nsec_a7_powerdn,
	.ispup  = nsec_isp_powerup,
	.ispdn  = nsec_isp_powerdn,
    .ispinit = nsec_isp_init,
    .ispexit = nsec_isp_exit,
};

int hisp_nsec_jpeg_powerup(void)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    struct hisp_pwr_ops *ops = dev->isp_ops;
    int ret = 0;

    pr_info("%s: +\n", __func__);
    if (!ops) {
        pr_err("%s: failed, isp_ops.0x%p is null.\n", __func__, ops);
		return -EINVAL;
    }

    mutex_lock(&ops->lock);

    ret = ops->ispup(ops);
    if (0 != ret) {
        pr_err("%s: ispup failed, ret.%d\n", __func__, ret);
        return ret;
    }

    if (need_powerup(ops->refs_ispinit)) {
        isp_a7_qos_cfg(dev);
        set_isp_nonsec();
	}

	ret = ops->ispinit(ops);
    if (0 != ret) {
        pr_err("%s: jpegup failed, ret.%d\n", __func__, ret);
        goto isp_down;
    }

    pr_info("%s:refs_a7.0x%x, refs_isp.0x%x, refs_ispinit.0x%x\n", __func__,
            ops->refs_a7, ops->refs_isp, ops->refs_ispinit);

    mutex_unlock(&ops->lock);
    return 0;

isp_down:
    if ((ops->ispdn(ops)) != 0)
        pr_err("%s: failed, ispdn\n", __func__);

    pr_info("%s:refs_a7.0x%x, refs_isp.0x%x, refs_ispinit.0x%x\n", __func__,
            ops->refs_a7, ops->refs_isp, ops->refs_ispinit);

    mutex_unlock(&ops->lock);
    pr_info("%s: -\n", __func__);
    return ret;
}
EXPORT_SYMBOL(hisp_nsec_jpeg_powerup);

int hisp_nsec_jpeg_powerdn(void)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    struct hisp_pwr_ops *ops = dev->isp_ops;
    int ret = 0;

    pr_info("%s: +\n", __func__);
    if (!ops) {
        pr_err("%s: failed, isp_ops is null.\n", __func__);
    }

    mutex_lock(&ops->lock);

    if ((ret = ops->ispexit(ops)))
        pr_err("%s: jpegdn faled, ret.%d\n", __func__, ret);

    if ((ret = ops->ispdn(ops)) != 0)
        pr_err("%s: ispdn faled, ret.%d\n", __func__, ret);

    pr_info("%s:refs_a7.0x%x, refs_isp.0x%x, refs_ispinit.0x%x\n", __func__,
            ops->refs_a7, ops->refs_isp, ops->refs_ispinit);

    mutex_unlock(&ops->lock);
    pr_info("%s: -\n", __func__);
    return 0;
}
EXPORT_SYMBOL(hisp_nsec_jpeg_powerdn);

int nonsec_isp_device_enable(void)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    struct hisp_pwr_ops *ops = dev->isp_ops;
    int ret = 0;

    if (!ops) {
        pr_err("%s: failed, isp_ops is null.\n", __func__);
    }

    mutex_lock(&ops->lock);

    ret = ops->ispup(ops);
    if (0 != ret) {
        pr_err("%s: ispup failed, ret.%d\n", __func__, ret);
        return ret;
    }

    if (need_powerup(ops->refs_ispinit)) {
		isp_a7_qos_cfg(dev);
		set_isp_nonsec();
	}

    ret = ops->ispinit(ops);
    if (0 != ret) {
        pr_err("%s: jpegup failed, ret.%d\n", __func__, ret);
        goto isp_down;
    }

    ret = ops->a7up(ops);
    if (0 != ret) {
        pr_err("%s: a7up failed, ret.%d\n", __func__, ret);
        goto isp_exit;
    }

    pr_info("%s:%d refs_a7.0x%x, refs_isp.0x%x, refs_ispinit.0x%x\n", __func__, __LINE__,
            ops->refs_a7, ops->refs_isp, ops->refs_ispinit);

    mutex_unlock(&ops->lock);
    return ret;

isp_exit:
    if ((ops->ispexit(ops)) != 0)
        pr_err("%s: failed, jpegdn\n", __func__);
isp_down:
    if ((ops->ispdn(ops)) != 0)
        pr_err("%s: failed, ispdn\n", __func__);

    pr_info("%s:refs_a7.0x%x, refs_isp.0x%x, refs_ispinit.0x%x\n", __func__,
            ops->refs_a7, ops->refs_isp, ops->refs_ispinit);
    mutex_unlock(&ops->lock);

    return ret;
}
EXPORT_SYMBOL(nonsec_isp_device_enable);

int nonsec_isp_device_disable(void)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    struct hisp_pwr_ops *ops = dev->isp_ops;
    int ret = 0;

    if (!ops) {
        pr_err("%s: failed, isp_ops is null.\n", __func__);
    }

    mutex_lock(&ops->lock);

    if ((ret = ops->a7dn(ops)) != 0)
        pr_err("%s: a7dn faled, ret.%d\n", __func__, ret);

    if ((ret = ops->ispexit(ops)))
        pr_err("%s: jpegdn faled, ret.%d\n", __func__, ret);

    if ((ret = ops->ispdn(ops)) != 0)
        pr_err("%s: ispdn faled, ret.%d\n", __func__, ret);

    pr_info("%s:refs_a7.0x%x, refs_isp.0x%x, refs_ispinit.0x%x\n", __func__,
            ops->refs_a7, ops->refs_isp, ops->refs_ispinit);

    mutex_unlock(&ops->lock);

    return 0;
}
EXPORT_SYMBOL(nonsec_isp_device_disable);

static int set_nonsec_pgd(struct rproc *rproc)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    struct iommu_domain_data *info = NULL;
    struct iommu_domain *domain = rproc->domain;
    struct rproc_shared_para *share_para = rproc_get_share_para();

    if (!share_para) {
        pr_err("%s:rproc_get_share_para failed.\n", __func__);
        return -EINVAL;
    }

    if (NULL == domain) {
        pr_info("%s:%d get_nonsec_pgd failed.\n", __func__, __LINE__);
        return -EINVAL;
    }

    info = (struct iommu_domain_data *)domain->priv;
    if (NULL == info) {
        pr_info("%s:%d get_nonsec_pgd failed.\n", __func__, __LINE__);
        return -EINVAL;
    }

    dev->pgd_base = (unsigned int)info->phy_pgd_base;
    share_para->dynamic_pgtable_base = dev->pgd_base;

    pr_info("%s: dev->pgd_base.0x%x == info->phy_pgd_base.0x%llx\n", __func__,
            dev->pgd_base, info->phy_pgd_base);

    return 0;
}

int hisi_isp_rproc_pgd_set(struct rproc *rproc)
{
    int err = 0;

    if (use_nonsec_isp()) {
        pr_info("%s: enter.\n", __func__);
        err = set_nonsec_pgd(rproc);
        if (0 != err) {
            pr_err("Failed : set_nonsec_pgd.%d\n", err);
            return err;
        }
    }

    return 0;
}

static int hisi_isp_nsec_getdts(struct platform_device *pdev, struct hisi_isp_nsec *dev)
{
    struct device *device = &pdev->dev;
    struct device_node *np = device->of_node;
    int ret, i;

    const char *clk_name[CLK_MAX];
    if (!np) {
        pr_err("[%s] Failed : np.%p.\n", __func__, np);
        return -ENODEV;
    }

    pr_info("%s:%d +\n", __func__, __LINE__);
    dev->device = device;
    dev->ispsrt_supply = get_isp_regulator();
    if (IS_ERR(dev->ispsrt_supply)) {
        pr_err("[%s] Failed : devm_regulator_get.%p\n", __func__, dev->ispsrt_supply);
        return -EINVAL;
    }

    dev->remap_addr = dev->isp_dma;
    set_a7mem_pa(dev->remap_addr);
    set_a7mem_va(dev->isp_dma_va);
    pr_info("%s: remap_addr.0x%x, dma_va.0x%p\n", __func__, dev->remap_addr, dev->isp_dma_va);

    if ((ret = of_property_read_string_array(np, "clock-names", clk_name, CLK_MAX)) < 0) {
        pr_err("[%s] Failed : of_property_read_string_array.%d\n", __func__, ret);
        return -EINVAL;
    }

    if ((ret = of_property_read_u32_array(np, "clock-value", dev->ispclk_value, CLK_MAX)) < 0) {
        pr_err("[%s] Failed: of_property_read_u32_array.%d\n", __func__, ret);
        return -EINVAL;
    }

    for (i = 0; i < CLK_MAX; i++) {
        dev->ispclk[i] = devm_clk_get(device, clk_name[i]);
        if (IS_ERR_OR_NULL(dev->ispclk[i])) {
            pr_err("[%s] Failed : ispclk.%s.%d.%li\n", __func__, clk_name[i], i, PTR_ERR(dev->ispclk[i]));
            return -EINVAL;
        }
        pr_info("[%s] ISP clock.%d.%s: %d M\n", __func__, i, clk_name[i], dev->ispclk_value[i]);
    }

    pr_info("%s:%d -\n", __func__, __LINE__);
    return 0;
}

static int isp_remap_rsc(struct hisi_isp_nsec *dev)
{
    dev->crgperi_base = (void __iomem *)ioremap(REG_BASE_CRGPERI_PHY, SZ_4K);
    if (dev->crgperi_base == NULL) {
        pr_err("crgperi_base err 0x%x(0x%x)\n", REG_BASE_CRGPERI_PHY, SZ_4K);
        return -ENOMEM;
    }

    dev->vivobus_base = (void __iomem *)ioremap(REG_BASE_VIVOBUS_PHY, SZ_4K);
    if (dev->vivobus_base == NULL) {
        pr_err("vivobus_base err 0x%x(0x%x)\n", REG_BASE_VIVOBUS_PHY, SZ_4K);
        goto free_crgperi_base;
    }

	dev->isp_regs_base = (void __iomem *)ioremap(REG_BASE_ISP_PHY, REG_BASE_ISP_SIZE);
	if (unlikely(!dev->isp_regs_base)) {
        pr_err("%s: isp_regs_base 0x%x.0x%x\n", __func__, REG_BASE_ISP_PHY, REG_BASE_ISP_SIZE);
        goto free_vivobus_base;
    }

    dev->isp_dma_va = dma_alloc_coherent(dev->device, ISP_MEM_SIZE, &dev->isp_dma, GFP_KERNEL);
    if (unlikely(!dev->isp_dma_va)) {
        pr_err("%s: isp_dma_va failed\n", __func__);
        goto free_regs_base;
    }

	pr_info("%s: crgperi_base.0x%p, vivobus_base.0x%p, isp_regs_base.0x%p, isp_dma_va.0x%p, dma.0x%llx\n", __func__,
			dev->crgperi_base, dev->vivobus_base, dev->isp_regs_base, dev->isp_dma_va, dev->isp_dma);

    return 0;

free_regs_base:
    iounmap(dev->isp_regs_base);
free_vivobus_base:
    iounmap(dev->vivobus_base);
free_crgperi_base:
    iounmap(dev->crgperi_base);

    dev->crgperi_base = NULL;
    dev->vivobus_base = NULL;
    dev->isp_regs_base = NULL;

    return -ENOMEM;
}

static void isp_unmap_rsc(struct hisi_isp_nsec *dev)
{
    if (dev->crgperi_base)
        iounmap(dev->crgperi_base);
    if (dev->vivobus_base)
        iounmap(dev->vivobus_base);
    if (dev->isp_regs_base)
        iounmap(dev->isp_regs_base);
    if (dev->isp_dma_va)
        dma_free_coherent(dev->device, ISP_MEM_SIZE, dev->isp_dma_va, dev->isp_dma);

    dev->crgperi_base = NULL;
    dev->vivobus_base = NULL;
	dev->isp_regs_base = NULL;
    dev->isp_dma_va = NULL;
}

static ssize_t sec_nsec_isp_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
	ssize_t size = 0;
	char *tmp;
	pr_info("%s: +.\n", __func__);

	tmp = (char *)kzalloc(TMP_SIZE, GFP_KERNEL);
	if (unlikely(!tmp)) { /*lint !e730 */
		pr_err("%s: kzalloc failed.\n", __func__);
		return 0;
	}

	size += snprintf(tmp, MAX_SIZE, "\nISP Types(Current ISP Type:%u):\n", hisi_isp_rproc_case_get());
	size += snprintf(tmp + size, MAX_SIZE, "0. DEFAULT_CASE(only support Austin and Dalls)\n");
	size += snprintf(tmp + size, MAX_SIZE, "1. SEC_CASE(if current platform support, e.g. Chicago)\n");
	size += snprintf(tmp + size, MAX_SIZE, "2. NONSEC_CASE(if current platform support, e.g. Chicago)\n");
	size += snprintf(tmp + size, MAX_SIZE, "3. INVAL_CASE\n");

	size += snprintf(tmp + size, MAX_SIZE, "\nISP Type Set:\n");
	size += snprintf(tmp + size, MAX_SIZE, "e.g. echo SEC_CASE > sec_nsec_isp:\n");

	memcpy((void *)buf, (void *)tmp, TMP_SIZE);
	kfree((void *)tmp);

	pr_info("%s: -.\n", __func__);
	return size;
}

static ssize_t sec_nsec_isp_store(struct device *dev, struct device_attribute *attr,
                 const char *buf, size_t count)
{
	pr_info("%s: +.\n", __func__);
	if (!strncmp("DEFAULT_CASE", buf, sizeof("DEFAULT_CASE") -1 )) {
		pr_info("%s: DEFAULT_CASE.\n", __func__);
		hisi_isp_rproc_case_set(DEFAULT_CASE);
	} else if (!strncmp("SEC_CASE", buf, sizeof("SEC_CASE") -1 )) {
		pr_info("%s: SEC_CASE.\n", __func__);
		hisi_isp_rproc_case_set(SEC_CASE);
	} else if (!strncmp("NONSEC_CASE", buf, sizeof("NONSEC_CASE") -1 )) {
		pr_info("%s: NONSEC_CASE.\n", __func__);
		hisi_isp_rproc_case_set(NONSEC_CASE);
	} else {
		pr_info("%s: INVAL_CASE.\n", __func__);
	}
	pr_info("%s: -.\n", __func__);
	return count; /*lint !e713*/
}

static DEVICE_ATTR(sec_nsec_isp, (S_IRUGO | S_IWUSR | S_IWGRP), sec_nsec_isp_show,
					sec_nsec_isp_store);

static struct miscdevice nsec_isp_miscdev = {
	.minor = 255,
	.name = "nsec_isp_miscdev",
};

int hisi_isp_nsec_probe(struct platform_device *pdev)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    struct hisp_pwr_ops *ops = &isp_pwr_ops;
    int ret = 0;

    pr_alert("%s:%d +\n", __func__, __LINE__);
    ops->refs_a7 = 0;
    ops->refs_isp = 0;
    ops->refs_ispinit = 0;

    dev->device = &pdev->dev;
    dev->isp_pdev = pdev;
    dev->isp_ops = ops;

    if ((ret = isp_remap_rsc(dev)) != 0) {
        pr_err("%s: failed, isp_remap_src.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = hisi_isp_nsec_getdts(pdev, dev)) != 0) {
        pr_err("[%s] Failed : hisi_isp_nsec_getdts.%d.\n", __func__, ret);
        goto out;
    }

	ret = misc_register(&nsec_isp_miscdev);
	if (0 != ret) {
		pr_err("%s: misc_register failed, ret.%d\n", __func__, ret);
		goto out;
	}

	ret = device_create_file(nsec_isp_miscdev.this_device, &dev_attr_sec_nsec_isp);
	if (0 != ret) {
		pr_err("%s: device_create_file failed, ret.%d\n", __func__, ret);
		goto misc_de;
	}

    pr_alert("%s:%d -\n", __func__, __LINE__);
    return 0;
misc_de:
	misc_deregister(&nsec_isp_miscdev);
out:
    isp_unmap_rsc(dev);
    return ret;
}

int hisi_isp_nsec_remove(struct platform_device *pdev)
{
    struct hisi_isp_nsec *dev = &nsec_rproc_dev;
    isp_unmap_rsc(dev);
	misc_deregister(&nsec_isp_miscdev);

    return 0;
}

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiStar V150 rproc driver");
