/*
 * Copyright (c) 2013-2015, Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/bootdevice.h>
#include <linux/time.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <soc_crgperiph_interface.h>
#include <linux/gpio.h>
#include <soc_sctrl_interface.h>
#include <soc_ufs_sysctrl_interface.h>

#include "ufshcd.h"
#include "unipro.h"
#include "ufs-kirin.h"
#include "ufshci.h"
#include "ufs_kirin_spec_log.h"
#include "../scsi_logging.h"
#include "dsm_ufs.h"
#ifdef CONFIG_UFS_DEVICE_RELATED_CONFIGS
#include <soc_ioc_fix_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#endif

extern unsigned int scsi_logging_level;

#define LOGGING_LEVEL(name, level)                                             \
	((level & ((1 << (SCSI_LOG_##name##_BITS)) - 1))                       \
	 << (SCSI_LOG_##name##_SHIFT))

#define UFS_SCSI_LOGGING_LEVEL                                                 \
	(LOGGING_LEVEL(ERROR, 5) | LOGGING_LEVEL(TIMEOUT, 1) |                 \
	 LOGGING_LEVEL(SCAN, 1) | LOGGING_LEVEL(MLQUEUE, 1) |                  \
	 LOGGING_LEVEL(MLCOMPLETE, 1) | LOGGING_LEVEL(LLQUEUE, 1) |            \
	 LOGGING_LEVEL(LLCOMPLETE, 1) | LOGGING_LEVEL(HLQUEUE, 1) |            \
	 LOGGING_LEVEL(HLCOMPLETE, 1) | LOGGING_LEVEL(IOCTL, 1))

static char ufs_product_name[32] = { 0 };
static int __init early_parse_ufs_product_name_cmdline(char *arg)
{
	if (arg) {
		strncpy(ufs_product_name, arg, strnlen(arg, sizeof(ufs_product_name)));
		pr_info("cmdline ufs_product_name=%s\n", ufs_product_name);
	} else {
		pr_info("no ufs_product_name cmdline\n");
	}
	return 0;
}
/*lint -e528 -esym(528,*)*/
early_param("ufs_product_name", early_parse_ufs_product_name_cmdline);
/*lint -e528 +esym(528,*)*/
/* Here external BL31 function declaration for UFS inline encrypt*/
#ifdef CONFIG_SCSI_UFS_INLINE_CRYPTO
noinline int atfd_hisi_uie_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
	asm volatile(
		__asmeq("%0", "x0")
		__asmeq("%1", "x1")
		__asmeq("%2", "x2")
		__asmeq("%3", "x3")
		"smc    #0\n"
	: "+r" (function_id)
	: "r" (arg0), "r" (arg1), "r" (arg2));

	return (int)function_id;
}
#endif

static u64 kirin_ufs_dma_mask = DMA_BIT_MASK(64);

static void ufs_kirin_reg_dump(struct ufs_hba *hba, u32 err_type)
{
	ufs_kirin_log_hci_vendor_regs( hba, err_type );
	ufs_kirin_log_soc_all_regs( hba, err_type );

#if 0
	dev_err(hba->dev,
		": --------------------------------------------------- \n");
	dev_err(hba->dev, ": \t\tHCI STANDARD REGISTER DUMP\n");
	dev_err(hba->dev,
		": --------------------------------------------------- \n");
	dev_err(hba->dev, ": CAPABILITIES:                 0x%08x\n",
		ufshcd_readl(hba, REG_CONTROLLER_CAPABILITIES));
	dev_err(hba->dev, ": UFS VERSION:                  0x%08x\n",
		ufshcd_readl(hba, REG_UFS_VERSION));
	dev_err(hba->dev, ": PRODUCT ID:                   0x%08x\n",
		ufshcd_readl(hba, REG_CONTROLLER_DEV_ID));
	dev_err(hba->dev, ": MANUFACTURE ID:               0x%08x\n",
		ufshcd_readl(hba, REG_CONTROLLER_PROD_ID));
	dev_err(hba->dev, ": INTERRUPT STATUS:             0x%08x\n",
		ufshcd_readl(hba, REG_INTERRUPT_STATUS));
	dev_err(hba->dev, ": INTERRUPT ENABLE:             0x%08x\n",
		ufshcd_readl(hba, REG_INTERRUPT_ENABLE));
	dev_err(hba->dev, ": CONTROLLER STATUS:            0x%08x\n",
		ufshcd_readl(hba, REG_CONTROLLER_STATUS));
	dev_err(hba->dev, ": CONTROLLER ENABLE:            0x%08x\n",
		ufshcd_readl(hba, REG_CONTROLLER_ENABLE));
	dev_err(hba->dev, ": UIC ERR PHY ADAPTER LAYER:    0x%08x\n",
		ufshcd_readl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER));
	dev_err(hba->dev, ": UIC ERR DATA LINK LAYER:      0x%08x\n",
		ufshcd_readl(hba, REG_UIC_ERROR_CODE_DATA_LINK_LAYER));
	dev_err(hba->dev, ": UIC ERR NETWORK LATER:        0x%08x\n",
		ufshcd_readl(hba, REG_UIC_ERROR_CODE_NETWORK_LAYER));
	dev_err(hba->dev, ": UIC ERR TRANSPORT LAYER:      0x%08x\n",
		ufshcd_readl(hba, REG_UIC_ERROR_CODE_TRANSPORT_LAYER));
	dev_err(hba->dev, ": UIC ERR DME:                  0x%08x\n",
		ufshcd_readl(hba, REG_UIC_ERROR_CODE_DME));
	dev_err(hba->dev, ": UTP TRANSF REQ INT AGG CNTRL: 0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL));
	dev_err(hba->dev, ": UTP TRANSF REQ LIST BASE L:   0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_BASE_L));
	dev_err(hba->dev, ": UTP TRANSF REQ LIST BASE H:   0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_BASE_H));
	dev_err(hba->dev, ": UTP TRANSF REQ DOOR BELL:     0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL));
	dev_err(hba->dev, ": UTP TRANSF REQ LIST CLEAR:    0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_CLEAR));
	dev_err(hba->dev, ": UTP TRANSF REQ LIST RUN STOP: 0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_RUN_STOP));
	dev_err(hba->dev, ": UTP TASK REQ LIST BASE L:     0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_BASE_L));
	dev_err(hba->dev, ": UTP TASK REQ LIST BASE H:     0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_BASE_H));
	dev_err(hba->dev, ": UTP TASK REQ DOOR BELL:       0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TASK_REQ_DOOR_BELL));
	dev_err(hba->dev, ": UTP TASK REQ LIST CLEAR:      0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_CLEAR));
	dev_err(hba->dev, ": UTP TASK REQ LIST RUN STOP:   0x%08x\n",
		ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_RUN_STOP));
	dev_err(hba->dev, ": UIC COMMAND:                  0x%08x\n",
		ufshcd_readl(hba, REG_UIC_COMMAND));
	dev_err(hba->dev, ": UIC COMMAND ARG1:             0x%08x\n",
		ufshcd_readl(hba, REG_UIC_COMMAND_ARG_1));
	dev_err(hba->dev, ": UIC COMMAND ARG2:             0x%08x\n",
		ufshcd_readl(hba, REG_UIC_COMMAND_ARG_2));
	dev_err(hba->dev, ": UIC COMMAND ARG3:             0x%08x\n",
		ufshcd_readl(hba, REG_UIC_COMMAND_ARG_3));
	dev_err(hba->dev, ": DWC HCLKDIV:                  0x%08x\n",
		ufshcd_readl(hba, UFS_REG_HCLKDIV));
#endif
}

static int ufs_kirin_check_hibern8(struct ufs_hba *hba)
{
	int err = 0;
	u32 tx_fsm_val_0 = 0;
	u32 tx_fsm_val_1 = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(HBRN8_POLL_TOUT_MS);

	do {
		err = ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 0),
				     &tx_fsm_val_0);
		err |= ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 1),
				     &tx_fsm_val_1);
		if (err || (tx_fsm_val_0 == TX_FSM_HIBERN8 && tx_fsm_val_1 == TX_FSM_HIBERN8))
			break;

		/* sleep for max. 200us */
		usleep_range(100, 200);
	} while (time_before(jiffies, timeout));

	/*
	 * we might have scheduled out for long during polling so
	 * check the state again.
	 */
	if (time_after(jiffies, timeout)) {
		err = ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 0),
				     &tx_fsm_val_0);
		err |= ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(MPHY_TX_FSM_STATE, 1),
				     &tx_fsm_val_1);
	}

	if (err) {
		dev_err(hba->dev, "%s: unable to get TX_FSM_STATE, err %d\n",
			__func__, err);
	} else if (tx_fsm_val_0 != TX_FSM_HIBERN8 || tx_fsm_val_1 != TX_FSM_HIBERN8) {
		err = -1;
		dev_err(hba->dev, "%s: invalid TX_FSM_STATE, lane0 = %d, lane1 = %d\n",
			__func__, tx_fsm_val_0, tx_fsm_val_1);
	}

	return err;
}

#ifdef CONFIG_SCSI_UFS_INLINE_CRYPTO
static int ufs_kirin_uie_config_init(struct ufs_hba *hba)
{
	int reg_value = 0;
	int err = 0;

#ifdef CONFIG_SCSI_UFS_KIRIN_V21
	struct ufs_kirin_host *host = hba->priv;
	writel(1<<SOC_UFS_Sysctrl_UFS_UMECTRL_ufs_ies_en_mask_START,\
		SOC_UFS_Sysctrl_UFS_UMECTRL_ADDR(host->ufs_sys_ctrl));
#endif

	/* enable UFS cryptographic operations on transactions */
	reg_value = ufshcd_readl(hba, REG_CONTROLLER_ENABLE);
	reg_value |= CRYPTO_GENERAL_ENABLE;
	ufshcd_writel(hba, reg_value, REG_CONTROLLER_ENABLE);

	/* Here UFS driver, which set SECURITY reg 0x1 in BL31,
	 * has the permission to write scurity key registers.
	 */
	err = atfd_hisi_uie_smc(RPMB_SVC_UFS_TEST, 0x0, 0x0, 0x0);

	return err;
}

/* the func to config key */
static void ufs_kirin_uie_key_prepare(struct ufs_hba *hba, int key_len,
					 int key_index, void *key)
{
	struct ufs_kirin_host *host = hba->priv;
	int reg_value = 0;
	int i = 0;
	int key_cfg = 0;
	u32 key_reg_offset = 0;
	u32 key_reg_data = 0;

#ifndef CONFIG_SCSI_UFS_KIRIN_V21
	/*
	 * when writing key reg of the number 22 ~ 31,
	 * we must set reg apb_addr of ufs_sys_ctrl
	 */
	if (key_index > 21) {
		ufs_sys_ctrl_writel(host, 0x10001, UFS_APB_ADDR_MASK);
		key_cfg = key_index - 22;
	} else
		key_cfg = key_index;
#else
	key_cfg = key_index;
#endif

	/* key operation start */
	reg_value = ufshcd_readl(hba, UFS_REG_CRYPTOCFG_0_16 + (key_cfg * 0x80));
	if ((reg_value >> 31) & 0x1) {
		/* TODO step 1st
		 * Verify that no pending transactions reference x-CRYPTOCFG
		 * in their CCI field, i.e. UTRD.CCI != x for all pending transactions
		 */

		/*step 2nd writing 0x0 to clear x-CRYPTOCFG reg*/
		ufshcd_writel(hba, 0, UFS_REG_CRYPTOCFG_0_16 + (key_cfg * 0x80));
	}

	/* step 3rd write the cryptographic key to x-CRYPTOKEY field
	 * The key is organized according to the algorithm-specific layout.
	 * Unused regions of CRYPTOKEY should be written with zeros.
	 * The key is written in little-endian format, sequentially
	 * and in one atomic set of operations.
	 */
	for (i = 0; i < 16; i++) {
		key_reg_offset = UFS_REG_CRYPTOCFG_0_0 + (i * 0x4) + (key_cfg * 0x80);
		key_reg_data = (u32)(*((u32 *)key + i));
		ufshcd_writel(hba, key_reg_data, key_reg_offset);
	}

	/* step 4th set x-CRYPTOCFG with CAPIDX, DUSIZE, and CFGE=1 */
	ufshcd_writel(hba, 0x80000108, UFS_REG_CRYPTOCFG_0_16 + (key_cfg * 0x80));
	/* key operation end */

#ifndef CONFIG_SCSI_UFS_KIRIN_V21
	/* clear reg apb_addr of ufs_sys_ctrl */
	if (key_index > 21)
		ufs_sys_ctrl_writel(host, 0x10000, UFS_APB_ADDR_MASK);
#endif
}

/* configure UTRD to enable cryptographic operations for this transaction. */
static void ufs_kirin_uie_utrd_prepare(struct ufs_hba *hba,
		struct ufshcd_lrb *lrbp)
{
	struct utp_transfer_req_desc *req_desc = lrbp->utr_descriptor_ptr;
	u32 dword_0, dword_1, dword_3;
	u64 dun;
	u32 crypto_enable;
	u32 crypto_cci;
	unsigned long flags;

	/*
	 * According to UFS 2.1 SPEC
	 * decrypte incoming payload if the command is SCSI READ operation
	 * encrypte outgoing payload if the command is SCSI WRITE operation
	 * And Kirin UFS controller only support SCSI cmd as below:
	 * READ_6/READ_10/WRITE_6/WRITE_10
	 */
	switch (lrbp->cmd->cmnd[0]) {
	case READ_10:
	case WRITE_10:
		crypto_enable = UTP_REQ_DESC_CRYPTO_ENABLE;
		break;
	default:
		return;
	}

	if (lrbp->cmd->request && lrbp->cmd->request->ci_key) {
		crypto_cci = lrbp->task_tag;
		spin_lock_irqsave(hba->host->host_lock, flags);
		ufs_kirin_uie_key_prepare(hba, lrbp->cmd->request->ci_key_len,
					 crypto_cci, lrbp->cmd->request->ci_key);
		spin_unlock_irqrestore(hba->host->host_lock, flags);
	} else {
		return;
	}

#if 0
	dun = lrbp->cmd->cmnd[2] << 24 |
		lrbp->cmd->cmnd[3] << 16 |
		lrbp->cmd->cmnd[4] << 8 |
		lrbp->cmd->cmnd[5];
#endif

	dun = (u64)lrbp->cmd->request->bio->index;

	/* dev_err(hba->dev, "%s: dun is 0x%llx\n", __func__, dun); */

	dword_0 = crypto_enable | crypto_cci;
	dword_1 = (u32)(dun & 0xffffffff);
	dword_3 = (u32)((dun >> 32)  & 0xffffffff);

	req_desc->header.dword_0 |= cpu_to_le32(dword_0);
	req_desc->header.dword_1 = cpu_to_le32(dword_1);
	req_desc->header.dword_3 = cpu_to_le32(dword_3);
}
#endif

static void ufs_kirin_regulator_init(struct ufs_hba *hba)
{
	struct device *dev = hba->dev;

	hba->vreg_info.vcc =
		devm_kzalloc(dev, sizeof(struct ufs_vreg), GFP_KERNEL);
	if (!hba->vreg_info.vcc) {
		dev_err(dev, "vcc alloc error\n");
		goto error;
	}

	hba->vreg_info.vcc->reg = devm_regulator_get(dev, "vcc");
	if (!hba->vreg_info.vcc->reg) {
		dev_err(dev, "get regulator vcc failed\n");
		goto error;
	}

	if (regulator_set_voltage(hba->vreg_info.vcc->reg, 2950000, 2950000)) {
		dev_err(dev, "set vcc voltage failed\n");
		goto error;
	}

	if (regulator_enable(hba->vreg_info.vcc->reg))
		dev_err(dev, "regulator vcc enable failed\n");

error:
	return;
}

#if 0
void ufs_kirin_clk_init(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = hba->priv;
	u32 ufs_clk_type;
	u32 count = 0;

	ufs_pericrg_writel(host, CLK_UFSIO, PERDIS7_OFFSET);
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	if (ufs_sys_ctrl_readl(host, PHY_CLK_CTRL) & BIT_SYSCTRL_REF_CLOCK_EN)
		mdelay(1);
	ufs_clk_type = ufs_sctrl_readl(host, SCDEEPSLEEPED_OFFSET);
	ufs_clk_type = (ufs_clk_type & BIT_SYS_UFS_CLK_TYPE_MASK) >> BIT_SYS_UFS_CLK_TYPE_OFF;

	if (1 == ufs_clk_type) {
		/* use pll clk */
		pr_info("UFS use pll clk\n");
		ufs_sys_ctrl_set_bits(host, BIT_UFS_REFCLK_SRC_SEl, UFS_SYSCTRL);
		ufs_pericrg_writel(host, 0x01ff01ff, CLKDIV21_OFFSET);
		ufs_pmctrl_writel(host, 0x03000000, PPLL3CTRL1_OFFSET);
		if (0x03000000 != ufs_pmctrl_readl(host, PPLL3CTRL1_OFFSET))
			mdelay(1);
		ufs_pmctrl_writel(host, 0x00904005, PPLL3CTRL0_OFFSET);
		for (count = 0; count < 10; count++) {
			mdelay(1);
			if (PPLL3_LOCK & ufs_pmctrl_readl(host, PPLL3CTRL0_OFFSET))
				break;
		}
		ufs_pmctrl_writel(host, 0x07000000, PPLL3CTRL1_OFFSET);
		ufs_pericrg_writel(host, 0x01ff01bf, CLKDIV21_OFFSET);
		ufs_pericrg_writel(host, CLK_ABB_BACKUP, PEREN5_OFFSET);
	} else if (2 == ufs_clk_type) {
		/* use 19.2 clk */
		pr_info("UFS use 19.2 digtal clk\n");
		ufs_sys_ctrl_set_bits(host, BIT_UFS_REFCLK_SRC_SEl, UFS_SYSCTRL);
		ufs_pericrg_writel(host, 0x1c00040, CLKDIV21_OFFSET);
		ufs_pericrg_writel(host, CLK_ABB_BACKUP, PEREN5_OFFSET);
	} else {
		/* use abb clk */
		pr_info("UFS use abb clk\n");
		ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_SRC_SEl, UFS_SYSCTRL);
		ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_ISO_EN, PHY_ISO_EN);
		ufs_pctrl_writel(host, UFS_TCXO_EN_WITH_MASK, PCTRL_PERI_CTRL3_OFFSET);
		mdelay(1);
	}

	ufs_pericrg_writel(host, CLK_UFSIO, PEREN7_OFFSET); /* open device ref clock */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL); /* open mphy ref clk */
	return;
}
#else
#ifdef CONFIG_UFS_DEVICE_RELATED_CONFIGS
static int config_refclk_drive_to_4ma = 0;
int force_link_to_1lane = 0;
#endif
static void ufs_kirin_clk_init(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = hba->priv;

	pr_info("%s ++\n", __func__);
	pr_info("UFS use abb clk\n");
#if 0
	ufs_pericrg_writel(host, CLK_UFSIO, PERDIS7_OFFSET);
#else
	(void)clk_prepare_enable(host->clk_ref);
	clk_disable_unprepare(host->clk_ref);
	if (CLK_UFSIO & ufs_pericrg_readl(host, PERCLKEN7_OFFSET)) {
		pr_err("%s:disable clk ref err. PERDIS7 = 0x%x\n", __func__,
			ufs_pericrg_readl(host, PERCLKEN7_OFFSET));
	}
#endif
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	if (ufs_sys_ctrl_readl(host, PHY_CLK_CTRL) & BIT_SYSCTRL_REF_CLOCK_EN)
		mdelay(1);
	/* use abb clk */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_SRC_SEl, UFS_SYSCTRL);
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_REFCLK_ISO_EN, PHY_ISO_EN);
#if 0
	ufs_pctrl_writel(host, UFS_TCXO_EN_WITH_MASK, PCTRL_PERI_CTRL3_OFFSET);
	mdelay(1);
	ufs_pericrg_writel(host, CLK_UFSIO, PEREN7_OFFSET); /* open device ref clock */
#else
	(void)clk_prepare_enable(host->clk_ref);
	if (!(0x1 & ufs_pctrl_readl(host, PCTRL_PERI_CTRL3_OFFSET))) {
		pr_err("%s:enable clk ref err. PERI_CTRL3 = 0x%x\n", __func__,
			ufs_pctrl_readl(host, PCTRL_PERI_CTRL3_OFFSET));
	}
	if (!(CLK_UFSIO & ufs_pericrg_readl(host, PERCLKEN7_OFFSET))) {
		pr_err("%s:enable clk ref err. PERDIS7 = 0x%x\n", __func__,
			ufs_pericrg_readl(host, PERCLKEN7_OFFSET));
	}
#endif
#ifdef CONFIG_UFS_DEVICE_RELATED_CONFIGS
	if(config_refclk_drive_to_4ma) {
		writel(0x90, SOC_IOC_FIX_IOCG_000_ADDR(ioremap(SOC_ACPU_IOC_FIX_BASE_ADDR, PAGE_SIZE)));
	}
#endif
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL); /* open mphy ref clk */
	pr_info("%s --\n", __func__);
	return;
}
#endif

static void ufs_kirin_soc_init(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;
	u32 reg;

	pr_info("%s ++\n", __func__);

	ufs_pericrg_writel(host, RST_UFS, PERRSTEN3_OFFSET);

	ufs_sys_ctrl_set_bits(host, BIT_UFS_PSW_MTCMOS_EN, PSW_POWER_CTRL); /* HC_PSW powerup */
	udelay(10);
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PWR_READY, HC_LP_CTRL); /* notify PWR ready */
	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | 0,
		UFS_DEVICE_RESET_CTRL);

	if (host->reset_gpio != 0xFFFFFFFF) {
		if (0 > gpio_direction_output(host->reset_gpio, 0))
			pr_err("%s: could not set gpio %d output push down\n", __func__, host->reset_gpio);
	}

	if (!(host->caps & USE_FPGA_BOARD_CLK)) {
		ufs_pericrg_writel(host, 0 | BIT(14 + 16), CLKDIV17_OFFSET); /* set hc hclk div */
		ufs_pericrg_writel(host, (0x3 << 9) | (0x3 << (9 + 16)), CLKDIV16_OFFSET); /* set mphy cfg clk div */
	}

	reg = ufs_sys_ctrl_readl(host, PHY_CLK_CTRL);
	reg = (reg & ~MASK_SYSCTRL_CFG_CLOCK_FREQ) | UFS_FREQ_CFG_CLK;
	ufs_sys_ctrl_writel(host, reg, PHY_CLK_CTRL); /* set cfg clk freq */
	ufs_sys_ctrl_clr_bits(host, MASK_SYSCTRL_REF_CLOCK_SEL, PHY_CLK_CTRL); /* set ref clk freq */
	/* bypass ufs clk gate */
	ufs_sys_ctrl_set_bits(host, MASK_UFS_CLK_GATE_BYPASS, CLOCK_GATE_BYPASS);
	ufs_sys_ctrl_set_bits(host, MASK_UFS_SYSCRTL_BYPASS, UFS_SYSCTRL);

	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PSW_CLK_EN, PSW_CLK_CTRL); /* open psw clk */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PSW_ISO_CTRL, PSW_POWER_CTRL); /* disable ufshc iso */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PHY_ISO_CTRL, PHY_ISO_EN); /* disable phy iso */
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_LP_ISOL_EN, HC_LP_CTRL); /* notice iso disable */
	ufs_pericrg_writel(host, UFS_ARESET, PERRSTDIS3_OFFSET); /* disable aresetn */
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_LP_RESET_N, RESET_CTRL_EN); /* disable lp_reset_n */
	mdelay(1);

	if (host->reset_gpio != 0xFFFFFFFF) {
		if (0 > gpio_direction_output(host->reset_gpio, 1))
			pr_err("%s: could not set gpio %d output pull up\n", __func__, host->reset_gpio);
	}
	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | BIT_UFS_DEVICE_RESET,
		UFS_DEVICE_RESET_CTRL);

	mdelay(20);

	/* enable the fix of linereset recovery, and enable rx_reset/tx_rest beat */
	/* enable ref_clk_en override(bit5) & override value = 1(bit4), with mask */
	ufs_sys_ctrl_writel(host, 0x03300330, UFS_DEVICE_RESET_CTRL);

	ufs_pericrg_writel(host, RST_UFS, PERRSTDIS3_OFFSET);
	if (ufs_pericrg_readl(host, PERRSTSTAT3_OFFSET) & RST_UFS)
		mdelay(1);

	/*set SOC_SCTRL_SCBAKDATA11_ADDR 0xffffffff when init*/
	writel(0xffffffff, SOC_SCTRL_SCBAKDATA11_ADDR(host->sysctrl));

	pr_info("%s --\n", __func__);
	return;
}

static void ufs_kirin_device_hw_reset(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = hba->priv;

	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | 0,
			    UFS_DEVICE_RESET_CTRL);
	if (host->reset_gpio != 0xFFFFFFFF) {
		if (0 > gpio_direction_output(host->reset_gpio, 0))
			pr_err("%s: could not set gpio %d output push down\n", __func__, host->reset_gpio);
	}

	mdelay(1);

	if (host->reset_gpio != 0xFFFFFFFF) {
		if (0 > gpio_direction_output(host->reset_gpio, 1))
			pr_err("%s: could not set gpio %d output pull up\n", __func__, host->reset_gpio);
	}
	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | BIT_UFS_DEVICE_RESET,
			    UFS_DEVICE_RESET_CTRL);
	/* some device need at least 40ms */
	mdelay(40);
}

/**
 * Soc init will reset host controller, all register value will lost
 * including memory address, doorbell and AH8 AGGR
 */
static void ufs_kirin_full_reset(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = hba->priv;

	/*
	 * disable ref clock, clk_init will re-enable
	 */
	clk_disable_unprepare(host->clk_ref);

	ufs_kirin_clk_init(hba);

	dsm_ufs_disable_volt_irq(hba);
	disable_irq(hba->irq);

	/* wait for 1s to be sure axi entered to idle state */
	msleep(1000);

	spin_lock(hba->host->host_lock);
	ufs_kirin_soc_init(hba);
	spin_unlock(hba->host->host_lock);
	enable_irq(hba->irq);
	dsm_ufs_enable_volt_irq(hba);
}

static void ufs_kirin_pre_hce_notify(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;

	BUG_ON(!host->pericrg || !host->ufs_sys_ctrl ||
	    !host->pctrl || !host->sysctrl || !host->pmctrl);

	return;
}


static int ufs_kirin_hce_enable_notify(struct ufs_hba *hba, bool status)
{
	int err = 0;

	switch (status) {
	case PRE_CHANGE:
		ufs_kirin_pre_hce_notify(hba);
		break;
	case POST_CHANGE:
		break;
	default:
		dev_err(hba->dev, "%s: invalid status %d\n", __func__, status);
		err = -EINVAL;
		break;
	}
	return err;
}

#if 1
static void ufs_kirin_phy_init(struct ufs_kirin_host *host)
{
	struct ufs_hba *hba = host->hba;

	if (host->avail_ln_rx == 0 || host->avail_ln_tx == 0) {
		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_AVAILRXDATALANES),
			       &host->avail_ln_rx);
		ufshcd_dme_get(hba, UIC_ARG_MIB(PA_AVAILTXDATALANES),
			       &host->avail_ln_tx);
		if (host->avail_ln_rx != host->avail_ln_tx)
			dev_warn(hba->dev, "available data lane is not "
					   "equal(rx:%d, tx:%d)\n",
				 host->avail_ln_rx, host->avail_ln_tx);
	}
}
#endif

/* snps mphy testchip specific configuration */
static int ufs_kirin_dme_setup_snps_mphy(struct ufs_hba *hba)
{
	uint32_t val;
	uint64_t retry = 1000;
	struct ufs_kirin_host *host = hba->priv;

	pr_info("%s ++\n", __func__);
	while (retry--) {
		ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0xD010, 0x0), &val);
		if (val == 1)
			break;
		if (!retry)
			return -EIO;
	}

	/* PLS put test UIC command here */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00c0, 0x0), 0x24);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xd0a0, 0x0), 0x18);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xd09e, 0x0), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f2, 0x4), 0x3);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f2, 0x5), 0x3);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00bd, 0x4), 0x16);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00bd, 0x5), 0x16);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00c7, 0x4), 0x42);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00c7, 0x5), 0x42);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80f8, 0x0), 0x00);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f3, 0x4), 0xa4);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f3, 0x4), 0xa4);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00b4, 0x4), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00b4, 0x5), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f4, 0x4), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f4, 0x5), 0x1);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00e9, 0x4), 0x28);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00e9, 0x5), 0x28);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00b5, 0x4), 0x1e);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00b5, 0x5), 0x1e);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00bf, 0x4), 0x2f);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00bf, 0x5), 0x2f);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80e6, 0x0), 0x4);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80cd, 0x0), 0x2);

	/******************************************************/
	/*                  Common Block                      */
	/******************************************************/

	/* Common block Tx Global Hibernate Exit */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x802b, 0x0), 0x00);
	/* Common block Reference Clokc Mode 26MHzt */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80bf, 0x0), 0x01);
	/* Common block DCO Target Frequency MAX PWM G1:9Mpbs */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80ea, 0x0), 0x80);
	/* Common block TX and RX Div Factor is 4 7Mbps/20 = 350KHz */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80f1, 0x0), 0x04);
	/* Common Block  */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80f3, 0x0), 0x64);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80fb, 0x0), 0x09);
	/* Common Block Real Time Observe Select; For debugging */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x80f0, 0x0), 0x00);

	/******************************************************/
	/*                       Lane 0                       */
	/******************************************************/

	/* Tx0 Reference Clock 26MHz */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00eb, 0x0), 0x0d);
	/* TX0 Configuration Clock Frequency Val; Divider setting */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00ec, 0x0), 0x12);
	/* TX0 20bit RMMI Interface */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f0, 0x0), 0x12);
	/* TX0  */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f1, 0x0), 0xd6);
	/* Rx0 Reference Clock 26MHz */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00eb, 0x4), 0x01);
	/* RX0 Configuration Clock Frequency Val; Divider setting */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00ec, 0x4), 0x12);
	/* RX0 20bit RMMI Interface */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f0, 0x4), 0x02);
	/* RX0 Squelch Detector output is routed to RX hibernate Exit Type1
	 * signal */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00ba, 0x4), 0x80);

	/******************************************************/
	/*                       Lane 1                       */
	/******************************************************/

	if (host->avail_ln_tx == 2) {
		/* Tx1 Reference Clock 26MHz */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00eb, 0x1), 0x0d);
		/* TX1 Configuration Clock Frequency Val; Divider setting */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00ec, 0x1), 0x12);
		/* TX1 20bit RMMI Interface */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f0, 0x1), 0x12);
		/* TX1  */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f1, 0x1), 0xd6);
	}

	if (host->avail_ln_rx == 2) {
		/* Rx1 Reference Clock 26MHz */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00eb, 0x5), 0x01);
		/* RX1 Configuration Clock Frequency Val; Divider setting */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00ec, 0x5), 0x12);
		/* RX1 20bit RMMI Interface */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00f0, 0x5), 0x02);
		/* RX1 Squelch Detector output is routed to RX hibernate Exit
		 * Type1 signal */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00ba, 0x5), 0x80);
	}

	/*TX_Controlled_ActTimer set to 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8001, 0x4), 0x00);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8002, 0x4), 0x00);

	/*disable termination resister switch. if delete, can not work in
	 * fastauto. need to check in ASIC...*/
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00bb, 0x0), 0x8);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x00bb, 0x1), 0x8);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xd0b6, 0x0), 0x1);

	/* To write Shadow register bank to effective configuration block */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xd085, 0x0), 0x01);
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xd000, 0x0), 0x01);

	pr_info("%s --\n", __func__);
	return 0;
}

/*lint -e648 -e845*/
uint16_t ufs_kirin_mphy_read(struct ufs_hba *hba, uint16_t addr)
{
	uint16_t result;
	uint32_t value;
	/*DME_SET(16'h8117, cr_para_addr.MSB );*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x8117), (addr & 0xFF00) >> 8);
	/*DME_SET(16'h8116, cr_para_addr.LSB);*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x8116), (addr & 0xFF));
	/*DME_SET(16'h811c, 0x0);*//*trigger read*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x811C), 0);
	/*DME_GET(16'h811b, read_data.MSB);*/
	ufshcd_dme_get(hba, UIC_ARG_MIB(0x811B), &value); /* Unipro VS_mphy_disable */
	result = (uint16_t)(value & 0xFF);
	result <<= 8;
	/*DME_GET(16'h811a, read_data.LSB);*/
	ufshcd_dme_get(hba, UIC_ARG_MIB(0x811A), &value); /* Unipro VS_mphy_disable */
	result |= (uint16_t)(value & 0xFF);
	return result;
}

void ufs_kirin_mphy_write(struct ufs_hba *hba, uint16_t addr, uint16_t value)
{
	/*DME_SET(16'h8117, cr_para_addr.MSB );*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x8117), (addr & 0xFF00) >> 8);
	/*DME_SET(16'h8116, cr_para_addr.LSB);*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x8116), (addr & 0xFF));
	/*DME_SET(16'h8119, cr_para_wr_data.MSB);*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x8119), (value & 0xFF00) >> 8);
	/*DME_SET(16'h8118, cr_para_wr_data.LSB );*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x8118), (value & 0xFF));
	/*DME_SET(16'h811c, 0x0);*//*trigger write*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x811C), 1);
}

void ufs_kirin_set_vol(struct ufs_hba *hba, int v_tx, int v_rx)
{
	pr_err("ufs v_tx:%d v_rx:%d\n", v_tx, v_rx);
	if ((v_rx > 0) && (v_rx < 4)) {
		ufs_kirin_mphy_write(hba, 0x004A, 0x0090);
		ufs_kirin_mphy_write(hba, 0x90cb, 0x0080);
		ufs_kirin_mphy_write(hba, 0x90ce, 0x0010);
		if (v_rx == 3) {
			ufs_kirin_mphy_write(hba, 0x0060, 0x36E4);
			ufs_kirin_mphy_write(hba, 0x0060, 0x36E0);
		}
		if (v_rx == 2) {
			ufs_kirin_mphy_write(hba, 0x0060, 0x3884);
			ufs_kirin_mphy_write(hba, 0x0060, 0x3880);
		}
		if (v_rx == 1) {
			ufs_kirin_mphy_write(hba, 0x0060, 0x3A24);
			ufs_kirin_mphy_write(hba, 0x0060, 0x3A20);
		}
		ufs_kirin_mphy_write(hba, 0x9005, 0x4000);
		ufs_kirin_mphy_write(hba, 0x9005, 0x0000);
	}
	if ((v_tx > 0) && (v_tx < 4)) {
		ufs_kirin_mphy_write(hba, 0x004A, 0x0090);
		ufs_kirin_mphy_write(hba, 0x90C3, 0x0010);
		ufs_kirin_mphy_write(hba, 0x90C9, 0x0001);
		ufs_kirin_mphy_write(hba, 0x90C5, 0x0002);

		if (v_tx == 3) {
			ufs_kirin_mphy_write(hba, 0x0060, 0x36E4);
			ufs_kirin_mphy_write(hba, 0x0060, 0x36E0);
		}
		if (v_tx == 2) {
			ufs_kirin_mphy_write(hba, 0x0060, 0x3884);
			ufs_kirin_mphy_write(hba, 0x0060, 0x3880);
		}
		if (v_tx == 1) {
			ufs_kirin_mphy_write(hba, 0x0060, 0x3A24);
			ufs_kirin_mphy_write(hba, 0x0060, 0x3A20);
		}
	}
}
/*lint +e648 +e845*/
#define UFS_TX_EQUALIZER_35DB
//#define UFS_TX_EQUALIZER_60DB

/*lint -e648 -e845*/
static int ufs_kirin_link_startup_pre_change(struct ufs_hba *hba)
{
	int err = 0;
	uint32_t value = 0;
	uint32_t reg = 0;
	struct ufs_kirin_host *host = hba->priv;

	pr_info("%s ++\n", __func__);
	if (!(host->caps & USE_SNPS_MPHY_TC)) {
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD0C1, 0x0), 0x1); /* Unipro VS_mphy_disable */
		if (host->caps & USE_RATE_B) {
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x156A, 0x0), 0x2); /* PA_HSSeries */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8114, 0x0), 0x1); /* MPHY CBRATESEL */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8121, 0x0), 0x2D); /* MPHY CBOVRCTRL2 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8122, 0x0), 0x1); /* MPHY CBOVRCTRL3 */

#ifdef CONFIG_SCSI_UFS_KIRIN_V21
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8127, 0x0), 0x82); /* MPHY CBOVRCTRL4 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8128, 0x0), 0x1); /* MPHY CBOVRCTRL5 */
#endif

			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1); /* Unipro VS_MphyCfgUpdt */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800D, 0x4), 0x58); /* MPHY RXOVRCTRL4 rx0 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800D, 0x5), 0x58); /* MPHY RXOVRCTRL4 rx1 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800E, 0x4), 0xB); /* MPHY RXOVRCTRL5 rx0 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800E, 0x5), 0xB); /* MPHY RXOVRCTRL5 rx1 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8009, 0x4), 0x1); /* MPHY RXSQCONTROL rx0 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8009, 0x5), 0x1); /* MPHY RXSQCONTROL rx1 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1); /* Unipro VS_MphyCfgUpdt */
		} else {
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x156A, 0x0), 0x1); /* PA_HSSeries */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8114, 0x0), 0x0); /* MPHY CBRATESEL */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8121, 0x0), 0x4C); /* MPHY CBOVRCTRL2 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8122, 0x0), 0x1); /* MPHY CBOVRCTRL3 */

#ifdef CONFIG_SCSI_UFS_KIRIN_V21
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8127, 0x0), 0x82); /* MPHY CBOVRCTRL4 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8128, 0x0), 0x1); /* MPHY CBOVRCTRL5 */
#endif
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1); /* Unipro VS_MphyCfgUpdt */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800D, 0x4), 0x18); /* MPHY RXOVRCTRL4 rx0 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800D, 0x5), 0x18); /* MPHY RXOVRCTRL4 rx1 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800E, 0x4), 0xD); /* MPHY RXOVRCTRL5 rx0 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800E, 0x5), 0xD); /* MPHY RXOVRCTRL5 rx1 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8009, 0x4), 0x1); /* MPHY RXSQCONTROL rx0 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8009, 0x5), 0x1); /* MPHY RXSQCONTROL rx1 */
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1); /* Unipro VS_MphyCfgUpdt */
		}

		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8113, 0x0), 0x1);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0095, 0x4), 0x4F); /* Gear3 Synclength */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0095, 0x5), 0x4F); /* Gear3 Synclength */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0094, 0x4), 0x4F); /* Gear2 Synclength */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0094, 0x5), 0x4F); /* Gear2 Synclength */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008B, 0x4), 0x4F); /* Gear1 Synclength */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008B, 0x5), 0x4F); /* Gear1 Synclength */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008F, 0x4), 0x7); /* Tactive RX */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x008F, 0x5), 0x7); /* Tactive RX */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x000F, 0x0), 0x5); /* Thibernate Tx */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x000F, 0x1), 0x5); /* Thibernate Tx */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);

		ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0xD0C1, 0x0), &value); /* Unipro VS_mphy_disable */
		if (value != 0x1)
			pr_warn("Warring!!! Unipro VS_mphy_disable is 0x%x\n", value);

		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD0C1, 0x0), 0x0); /* Unipro VS_mphy_disable */
		err = ufs_kirin_check_hibern8(hba);
		if (err)
			pr_err("ufs_kirin_check_hibern8 error\n");
		ufs_kirin_set_vol(hba, hba->v_tx, hba->v_rx);
	}

	if (host->caps & USE_FPGA_BOARD_CLK) {
		ufshcd_writel(hba, UFS_HCLKDIV_FPGA_VALUE, UFS_REG_HCLKDIV);
	} else {
		ufshcd_writel(hba, UFS_HCLKDIV_NORMAL_VALUE, UFS_REG_HCLKDIV);
	}

	/* disable auto H8 */
	reg = ufshcd_readl(hba, REG_CONTROLLER_AHIT);
	reg = reg & (~UFS_AHIT_AH8ITV_MASK);
	ufshcd_writel(hba, reg, REG_CONTROLLER_AHIT);

	if (host->caps & USE_SNPS_MPHY_TC) {
		ufs_kirin_phy_init(host);
		/* SNPS mphy test chip specific configration */
		err = ufs_kirin_dme_setup_snps_mphy(hba);
		if (err)
			return err;
	}

	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | BIT_UFS_DEVICE_RESET,\
		UFS_DEVICE_RESET_CTRL); /* disable Device Reset */

	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x155E, 0x0), 0x0); /* Unipro PA_Local_TX_LCC_Enable */
	ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD0AB, 0x0), 0x0); /* close Unipro VS_Mk2ExtnSupport */
	ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0xD0AB, 0x0), &value);
	if (0 != value) {
		/* Ensure close success */
		pr_warn("Warring!!! close VS_Mk2ExtnSupport failed\n");
	}
	if (35 == host->tx_equalizer) {
		ufs_kirin_mphy_write(hba, 0x1002, 0xAC78);
		ufs_kirin_mphy_write(hba, 0x1102, 0xAC78);
		ufs_kirin_mphy_write(hba, 0x1003, 0x2440);
		ufs_kirin_mphy_write(hba, 0x1103, 0x2440);
	}
	else if (60 == host->tx_equalizer) {
		ufs_kirin_mphy_write(hba, 0x1002, 0xAA78);
		ufs_kirin_mphy_write(hba, 0x1102, 0xAA78);
		ufs_kirin_mphy_write(hba, 0x1003, 0x2640);
		ufs_kirin_mphy_write(hba, 0x1103, 0x2640);
	}
#ifdef CONFIG_UFS_DEVICE_RELATED_CONFIGS
	if(force_link_to_1lane) {
		ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0x8006, 0x1), &value);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x8006, 0x1), value | 0x47); /* Disable TX and Data_En */
		ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0x800A, 0x5), &value);
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x800A, 0x5), value | 0x30); /* Disable RX */
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0xD085, 0x0), 0x1);
	}
#endif
	pr_info("%s --\n", __func__);

	return err;
}
/*lint +e648 +e845*/

/*lint -e648 -e845*/
static int ufs_kirin_link_startup_post_change(struct ufs_hba *hba)
{
	uint32_t value;
	struct ufs_kirin_host *host = hba->priv;

	pr_info("%s ++\n", __func__);
	if (host->caps & USE_SNPS_MPHY_TC) {
		/*set the granularity to 2. need to check in ASIC...*/
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x15aa, 0x0), 0x2);
		/*set the PA_TActivate to 128. need to check in ASIC...*/
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x15a8, 0x0), 128);

		/* disable power-gating in auto hibernate 8 */
		ufshcd_rmwl(hba, LP_AH8_PGE, 0, UFS_REG_OCPTHRTL);

		/* disable Ultra Low Power Hibenate feature of Synopsys MPHY */
		ufshcd_dme_get(hba, UIC_ARG_MIB(VS_ULPH8_Cntrl), &value);
		value &= (uint32_t)(~Ulp_Ulp_CtrlMode);
		ufshcd_dme_set(hba, UIC_ARG_MIB(VS_ULPH8_Cntrl), value);
	} else {
		ufshcd_dme_set(hba, UIC_ARG_MIB(0x2044), 0x0); /* Unipro DL_AFC0CreditThreshold */
		ufshcd_dme_set(hba, UIC_ARG_MIB(0x2045), 0x0); /* Unipro DL_TC0OutAckThreshold */
		ufshcd_dme_set(hba, UIC_ARG_MIB(0x2040), 0x9); /* Unipro DL_TC0TXFCThreshold */
	}

	if (host->caps & BROKEN_CLK_GATE_BYPASS) {
		/* not bypass ufs clk gate */
		ufs_sys_ctrl_clr_bits(host, MASK_UFS_CLK_GATE_BYPASS, CLOCK_GATE_BYPASS);
		ufs_sys_ctrl_clr_bits(host, MASK_UFS_SYSCRTL_BYPASS, UFS_SYSCTRL);
	}

	if (host->caps & USE_AUTO_H8) {
		/* disable power-gating in auto hibernate 8 */
		ufshcd_rmwl(hba, LP_AH8_PGE, 0, UFS_REG_OCPTHRTL);

		/* enable auto H8 */
		ufshcd_writel(hba, UFS_AHIT_AUTOH8_TIMER, REG_CONTROLLER_AHIT);
	}

	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09a), 0x80000000); /* select received symbol cnt */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09c), 0x00000005); /* reset counter0 and enable */

	pr_info("%s --\n", __func__);
	return 0;
}
/*lint +e648 +e845*/

static int ufs_kirin_link_startup_notify(struct ufs_hba *hba, bool status)
{
	int err = 0;
	switch (status) {
	case PRE_CHANGE:
		err = ufs_kirin_link_startup_pre_change(hba);
		break;
	case POST_CHANGE:
		err = ufs_kirin_link_startup_post_change(hba);
		break;
	default:
		break;
	}

	return err;
}

/* TODO: get limit information from dts */
struct ufs_kirin_dev_params {
	u32 pwm_rx_gear; /* pwm rx gear to work in */
	u32 pwm_tx_gear; /* pwm tx gear to work in */
	u32 hs_rx_gear;  /* hs rx gear to work in */
	u32 hs_tx_gear;  /* hs tx gear to work in */
	u32 rx_lanes;    /* number of rx lanes */
	u32 tx_lanes;    /* number of tx lanes */
	u32 rx_pwr_pwm;  /* rx pwm working pwr */
	u32 tx_pwr_pwm;  /* tx pwm working pwr */
	u32 rx_pwr_hs;   /* rx hs working pwr */
	u32 tx_pwr_hs;   /* tx hs working pwr */
	u32 hs_rate;     /* rate A/B to work in HS */
	u32 desired_working_mode;
};

static int ufs_kirin_get_pwr_dev_param(struct ufs_kirin_dev_params *kirin_param,
				       struct ufs_pa_layer_attr *dev_max,
				       struct ufs_pa_layer_attr *agreed_pwr)
{
	int min_kirin_gear;
	int min_dev_gear;
	bool is_dev_sup_hs = false;
	bool is_kirin_max_hs = false;

	if (dev_max->pwr_rx == FASTAUTO_MODE || dev_max->pwr_rx == FAST_MODE)
		is_dev_sup_hs = true;

	if (kirin_param->desired_working_mode == FAST) {
		is_kirin_max_hs = true;
		min_kirin_gear = min_t(u32, kirin_param->hs_rx_gear,
				       kirin_param->hs_tx_gear);
	} else {
		min_kirin_gear = min_t(u32, kirin_param->pwm_rx_gear,
				       kirin_param->pwm_tx_gear);
	}

	/*
	 * device doesn't support HS but kirin_param->desired_working_mode is
	 * HS, thus device and kirin_param don't agree
	 */
	if (!is_dev_sup_hs && is_kirin_max_hs) {
		pr_err("%s: failed to agree on power mode (device doesn't "
		       "support HS but requested power is HS)\n",
		       __func__);
		return -ENOTSUPP;
	} else if (is_dev_sup_hs && is_kirin_max_hs) {
		/*
		 * since device supports HS, it supports FAST_MODE.
		 * since kirin_param->desired_working_mode is also HS
		 * then final decision (FAST/FASTAUTO) is done according
		 * to kirin_params as it is the restricting factor
		 */
		agreed_pwr->pwr_rx = agreed_pwr->pwr_tx =
			kirin_param->rx_pwr_hs;
	} else {
		/*
		 * here kirin_param->desired_working_mode is PWM.
		 * it doesn't matter whether device supports HS or PWM,
		 * in both cases kirin_param->desired_working_mode will
		 * determine the mode
		 */
		agreed_pwr->pwr_rx = agreed_pwr->pwr_tx =
			kirin_param->rx_pwr_pwm;
	}

	/*
	 * we would like tx to work in the minimum number of lanes
	 * between device capability and vendor preferences.
	 * the same decision will be made for rx
	 */
	agreed_pwr->lane_tx =
		min_t(u32, dev_max->lane_tx, kirin_param->tx_lanes);
	agreed_pwr->lane_rx =
		min_t(u32, dev_max->lane_rx, kirin_param->rx_lanes);

	/* device maximum gear is the minimum between device rx and tx gears */
	min_dev_gear = min_t(u32, dev_max->gear_rx, dev_max->gear_tx);

	/*
	 * if both device capabilities and vendor pre-defined preferences are
	 * both HS or both PWM then set the minimum gear to be the chosen
	 * working gear.
	 * if one is PWM and one is HS then the one that is PWM get to decide
	 * what is the gear, as it is the one that also decided previously what
	 * pwr the device will be configured to.
	 */
	if ((is_dev_sup_hs && is_kirin_max_hs) ||
	    (!is_dev_sup_hs && !is_kirin_max_hs))
		agreed_pwr->gear_rx = agreed_pwr->gear_tx =
			min_t(u32, min_dev_gear, min_kirin_gear);
	else
		agreed_pwr->gear_rx = agreed_pwr->gear_tx = min_kirin_gear;

	agreed_pwr->hs_rate = kirin_param->hs_rate;

	pr_err("ufs final power mode: gear = %d, lane = %d, pwr = %d, "
		"rate = %d\n",
		agreed_pwr->gear_rx, agreed_pwr->lane_rx, agreed_pwr->pwr_rx,
		agreed_pwr->hs_rate);
	return 0;
}

/*lint -e845*/
static void ufs_kirin_pwr_change_pre_change(struct ufs_hba *hba)
{
	uint32_t value;
	pr_info("%s ++\n", __func__);

	pr_info("device manufacturer_id is 0x%x\n", hba->manufacturer_id);
	if (UFS_VENDOR_HYNIX == hba->manufacturer_id) {
		pr_info("H**** device must set VS_DebugSaveConfigTime 0x10\n");
		ufshcd_dme_set(hba, UIC_ARG_MIB(0xD0A0), 0x10); /* VS_DebugSaveConfigTime */
		ufshcd_dme_set(hba, UIC_ARG_MIB(0x1556), 0x48); /* sync length */
		/* no need to update in unipro register */
		/* ufshcd_dme_set(hba, UIC_ARG_MIB(0xD085), 0x01); */
	}
	ufshcd_dme_get(hba, UIC_ARG_MIB(0x15A8), &value);
	if (value < 0x7)
		ufshcd_dme_set(hba, UIC_ARG_MIB(0x15A8), 0x7); /* update PaTactive */

	ufshcd_dme_set(hba, UIC_ARG_MIB(0x155c), 0x0); /* PA_TxSkip */

	/*PA_PWRModeUserData0 = 8191, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b0), 8191);
	/*PA_PWRModeUserData1 = 65535, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b1), 65535);
	/*PA_PWRModeUserData2 = 32767, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b2), 32767);
	/*DME_FC0ProtectionTimeOutVal = 8191, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd041), 8191);
	/*DME_TC0ReplayTimeOutVal = 65535, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd042), 65535);
	/*DME_AFC0ReqTimeOutVal = 32767, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd043), 32767);
	/*PA_PWRModeUserData3 = 8191, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b3), 8191);
	/*PA_PWRModeUserData4 = 65535, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b4), 65535);
	/*PA_PWRModeUserData5 = 32767, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0x15b5), 32767);
	/*DME_FC1ProtectionTimeOutVal = 8191, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd044), 8191);
	/*DME_TC1ReplayTimeOutVal = 65535, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd045), 65535);
	/*DME_AFC1ReqTimeOutVal = 32767, default is 0*/
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd046), 32767);

	pr_info("%s --\n", __func__);
	return;
}
/*lint +e845*/

static int ufs_kirin_pwr_change_notify(struct ufs_hba *hba,
				       bool status,
				       struct ufs_pa_layer_attr *dev_max_params,
				       struct ufs_pa_layer_attr *dev_req_params)
{
	struct ufs_kirin_dev_params ufs_kirin_cap;
	struct ufs_kirin_host *host = hba->priv;
	int ret = 0;
#if 0
	uint32_t value;
#endif

	if (!dev_req_params) {
		pr_err("%s: incoming dev_req_params is NULL\n", __func__);
		ret = -EINVAL;
		goto out;
	}

	switch (status) {
	case PRE_CHANGE:
		if (host->caps & USE_ONE_LANE) {
			ufs_kirin_cap.tx_lanes = 1;
			ufs_kirin_cap.rx_lanes = 1;
		} else {
			ufs_kirin_cap.tx_lanes = 2;
			ufs_kirin_cap.rx_lanes = 2;
		}

#ifdef CONFIG_SCSI_UFS_HS_ERROR_RECOVER
		if (hba->hs_single_lane) {
			ufs_kirin_cap.tx_lanes = 1;
			ufs_kirin_cap.rx_lanes = 1;
		}
#endif

		if (host->caps & USE_HS_GEAR3) {
			ufs_kirin_cap.hs_rx_gear = UFS_HS_G3;
			ufs_kirin_cap.hs_tx_gear = UFS_HS_G3;
			ufs_kirin_cap.desired_working_mode = FAST;
		} else if (host->caps & USE_HS_GEAR2) {
			ufs_kirin_cap.hs_rx_gear = UFS_HS_G2;
			ufs_kirin_cap.hs_tx_gear = UFS_HS_G2;
			ufs_kirin_cap.desired_working_mode = FAST;
		} else if (host->caps & USE_HS_GEAR1) {
			ufs_kirin_cap.hs_rx_gear = UFS_HS_G1;
			ufs_kirin_cap.hs_tx_gear = UFS_HS_G1;
			ufs_kirin_cap.desired_working_mode = FAST;
		} else {
			ufs_kirin_cap.hs_rx_gear = 0;
			ufs_kirin_cap.hs_tx_gear = 0;
			ufs_kirin_cap.desired_working_mode = SLOW;
		}

#ifdef CONFIG_SCSI_UFS_HS_ERROR_RECOVER
		if (hba->use_pwm_mode)
			ufs_kirin_cap.desired_working_mode = SLOW;
#endif

		ufs_kirin_cap.pwm_rx_gear = UFS_KIRIN_LIMIT_PWMGEAR_RX;
		ufs_kirin_cap.pwm_tx_gear = UFS_KIRIN_LIMIT_PWMGEAR_TX;
		ufs_kirin_cap.rx_pwr_pwm = UFS_KIRIN_LIMIT_RX_PWR_PWM;
		ufs_kirin_cap.tx_pwr_pwm = UFS_KIRIN_LIMIT_TX_PWR_PWM;
		/*hynix not support fastauto now*/
		if ((host->caps & BROKEN_FASTAUTO) ||
		    (UFS_VENDOR_HYNIX == host->hba->manufacturer_id) ||
		    (UFS_VENDOR_SAMSUNG == host->hba->manufacturer_id)) {
			ufs_kirin_cap.rx_pwr_hs = FAST_MODE;
			ufs_kirin_cap.tx_pwr_hs = FAST_MODE;
		} else {
			ufs_kirin_cap.rx_pwr_hs = FASTAUTO_MODE;
			ufs_kirin_cap.tx_pwr_hs = FASTAUTO_MODE;
		}

		if (host->caps & USE_RATE_B)
			ufs_kirin_cap.hs_rate = PA_HS_MODE_B;
		else
			ufs_kirin_cap.hs_rate = PA_HS_MODE_A;

		ret = ufs_kirin_get_pwr_dev_param(
			&ufs_kirin_cap, dev_max_params, dev_req_params);
		if (ret) {
			pr_err("%s: failed to determine capabilities\n",
			       __func__);
			goto out;
		}
#if 0
#ifdef UFS_TX_EQUALIZER_35DB
		pr_info("set TX_EQUALIZER 3.5db\n");
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0037, 0x0), 0x1);
		if ((dev_req_params->lane_tx > 1) && (dev_req_params->lane_rx > 1))
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0037, 0x1), 0x1);
#endif
#ifdef UFS_TX_EQUALIZER_60DB
		pr_info("set TX_EQUALIZER 6db\n");
		ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0037, 0x0), 0x2);
		if ((dev_req_params->lane_tx > 1) && (dev_req_params->lane_rx > 1))
			ufshcd_dme_set(hba, UIC_ARG_MIB_SEL(0x0037, 0x1), 0x2);
#endif
#endif
		ufs_kirin_pwr_change_pre_change(hba);
		break;
	case POST_CHANGE:
#if 0
		ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0x0037, 0x0), &value);
		pr_info("check TX_EQUALIZER DB value lane0 = 0x%x\n", value);
		if ((dev_req_params->lane_tx > 1) && (dev_req_params->lane_rx > 1)) {
			ufshcd_dme_get(hba, UIC_ARG_MIB_SEL(0x0037, 0x1), &value);
			pr_info("check TX_EQUALIZER DB value lane1 = 0x%x\n", value);
		}
#endif
		break;
	default:
		ret = -EINVAL;
		break;
	}
out:
	return ret;
}

#ifdef FEATURE_KIRIN_UFS_PSW
static int ufs_kirin_wait_ufssys_bitset_timeout(struct ufs_kirin_host *host,
		uint32_t mask, uint32_t off, int timeout_us)
{
	while (--timeout_us > 0) {
		if (mask & ufs_sys_ctrl_readl(host, off))
			break;
		udelay(1);
	}
	if (timeout_us <= 0) {
		pr_err("%s: wait ufs sys bit time out\n", __func__);
		return -1;
	}
	return 0;
}
#endif

static int ufs_kirin_suspend_before_set_link_state(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
#ifdef FEATURE_KIRIN_UFS_PSW
	struct ufs_kirin_host *host = hba->priv;

	if (ufshcd_is_runtime_pm(pm_op))
		return 0;

	/*step1:store BUSTHRTL register*/
	host->busthrtl_backup = ufshcd_readl(hba, UFS_REG_OCPTHRTL);
	/*enable PowerGating*/
	ufshcd_rmwl(hba, LP_PGE, LP_PGE, UFS_REG_OCPTHRTL);
#endif
	return 0;
}

static int ufs_kirin_suspend(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_kirin_host *host = hba->priv;

	/*set SOC_SCTRL_SCBAKDATA11_ADDR 0 when idle*/
	writel(0, SOC_SCTRL_SCBAKDATA11_ADDR(host->sysctrl));

	if (ufshcd_is_runtime_pm(pm_op))
		return 0;

	pr_info("ufs_sys_ctrl 0x3C: 0x%x\n", ufs_sys_ctrl_readl(host, 0x3C));
	pr_info("ufs_sys_ctrl 0x40: 0x%x\n", ufs_sys_ctrl_readl(host, 0x40));

	if (host->in_suspend) {
		WARN_ON(1);/*lint !e730*/
		return 0;
	}

	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	udelay(10);
	/* set ref_dig_clk override of PHY PCS to 0 */
	ufs_sys_ctrl_writel(host, 0x00100000, UFS_DEVICE_RESET_CTRL);

#ifdef FEATURE_KIRIN_UFS_PSW
	/*step 10: poll HC_LP_CTRL(0x0C)bit0*/
	if (ufs_kirin_wait_ufssys_bitset_timeout(host,
			BIT_SYSCTRL_LP_PWR_GATE, HC_LP_CTRL, 10000)) {
		pr_err("%s: LP_PWR_GATE time out\n", __func__);
		return -1;
	}

	/*step 11:set PSW_CLK_CTRL(0x14) bit[4] to 0,close psw clk*/
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_PSW_CLK_EN, PSW_CLK_CTRL);

	/*step 12:set HC_LP_CTRL(0x0C) bit[16] to 1,set PSW_POWER_CTRL(0x04) bit[16] to 1*/
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_LP_ISOL_EN, HC_LP_CTRL);
	ufs_sys_ctrl_set_bits(host, BIT_UFS_PSW_ISO_CTRL, PSW_POWER_CTRL);

	/*step 13:set UFS_SC RESET_CTRL_EN(0x1C) bit[0] to 0,reset UFSHCPSW area*/
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_LP_RESET_N, RESET_CTRL_EN);

	/*step 14:set UFS_SC PSW_POWER_CTRL(0x04) bit[0] to 0,power off psw area*/
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PSW_MTCMOS_EN, PSW_POWER_CTRL);
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_PWR_READY, HC_LP_CTRL);
#endif

	udelay(100);
	clk_disable_unprepare(host->clk_ref);
	if (CLK_UFSIO & ufs_pericrg_readl(host, PERCLKEN7_OFFSET)) {
		pr_err("%s:disable clk ref err. PERDIS7 = 0x%x\n", __func__,
			ufs_pericrg_readl(host, PERCLKEN7_OFFSET));
	}

	/* close ufsphy cfg clk */
	ufs_pericrg_writel(host, CLK_UFSPHY, PERDIS7_OFFSET);
	if (CLK_UFSPHY & ufs_pericrg_readl(host, PERCLKEN7_OFFSET)) {
		pr_err("%s:disable phy cfg clk err. PERCLKEN7 = 0x%x\n",__func__,
			ufs_pericrg_readl(host, PERCLKEN7_OFFSET));
	}

	/* ufs_pericrg_writel(host, CLK_UFS_SUBSYS, PERDIS5_OFFSET); */

	host->in_suspend = true;

	return 0;
}

static int ufs_kirin_resume(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_kirin_host *host = hba->priv;

	/*set SOC_SCTRL_SCBAKDATA11_ADDR 1 when busy*/
	writel(0x1, SOC_SCTRL_SCBAKDATA11_ADDR(host->sysctrl));

	if (!host->in_suspend)
		return 0;

	/* ufs_pericrg_writel(host, CLK_UFS_SUBSYS, PEREN5_OFFSET); */

	/* open ufsphy cfg clk */
	ufs_pericrg_writel(host, CLK_UFSPHY, PEREN7_OFFSET);
	if (!(CLK_UFSPHY & ufs_pericrg_readl(host, PERCLKEN7_OFFSET))) {
		pr_err("%s:enable phy cfg clk err. PERCLKEN7 = 0x%x\n", __func__,
			ufs_pericrg_readl(host, PERCLKEN7_OFFSET));
	}

	(void)clk_prepare_enable(host->clk_ref);
	if (!(0x1 & ufs_pctrl_readl(host, PCTRL_PERI_CTRL3_OFFSET))) {
		pr_err("%s:enable clk ref err. PERI_CTRL3 = 0x%x\n", __func__,
			ufs_pctrl_readl(host, PCTRL_PERI_CTRL3_OFFSET));
	}
	if (!(CLK_UFSIO & ufs_pericrg_readl(host, PERCLKEN7_OFFSET))) {
		pr_err("%s:enable clk ref err. PERDIS7 = 0x%x\n", __func__,
			ufs_pericrg_readl(host, PERCLKEN7_OFFSET));
	}

	udelay(1);
	/* set ref_dig_clk override of PHY PCS to 1 */
	ufs_sys_ctrl_writel(host, 0x00100010, UFS_DEVICE_RESET_CTRL);
	udelay(10);
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);

#ifdef FEATURE_KIRIN_UFS_PSW
	/*step5: set UFS_SC PSW_POWER_CTRL(0x04) bit[0] to 1,power up psw area*/
	ufs_sys_ctrl_set_bits(host, BIT_UFS_PSW_MTCMOS_EN, PSW_POWER_CTRL);
	udelay(10);

	/*step6:set UFS_SC HC_LP_CTRL(0x0C) bit[8] to 1,make LP_pwr_ready effective*/
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PWR_READY, HC_LP_CTRL);

	/*step7:set UFS_SC PSW_CLK_CTRL(0x14) bit[4] to 1,enable clk of PSW*/
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PSW_CLK_EN, PSW_CLK_CTRL);

	/*step8:set UFS_SC RESET_CTRL_EN(0x1C) bit[0] to 1,reset PSW area*/
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_LP_RESET_N, RESET_CTRL_EN);

	if (ufs_kirin_wait_ufssys_bitset_timeout(host,
			BIT_STATUS_LP_RESETCOMPLETE, PHY_RESET_STATUS, 10000)) {
		pr_err("%s: wait lp_resetcomplete time out\n", __func__);
		return -1;
	}

	/*step 9 set PSW_POWER_CTRL(0x04) bit[16] to 0,disable Isolation*/

	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PSW_ISO_CTRL, PSW_POWER_CTRL);
	if (BIT_UFS_PSW_ISO_CTRL & ufs_sys_ctrl_readl(host, PSW_POWER_CTRL)) {
		pr_err("%s: set psw_iso_ctrl fail\n", __func__);
		mdelay(1);
	}
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_LP_ISOL_EN, HC_LP_CTRL);
#endif

	host->in_suspend = false;
	return 0;
}

static int ufs_kirin_resume_after_set_link_state(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
#ifdef FEATURE_KIRIN_UFS_PSW
	struct ufs_kirin_host *host = hba->priv;

	if (ufshcd_is_runtime_pm(pm_op))
		return 0;

	ufshcd_writel(hba, host->busthrtl_backup, UFS_REG_OCPTHRTL);
#endif
	return 0;
}
/* platform_get_resource will require resource exclusively, ufs_sys_ctrl used
 * for ufs only, but pctrl and pericrg are common resource */
static int ufs_kirin_get_resource(struct ufs_kirin_host *host)
{
	struct resource *mem_res;
	struct device_node *np = NULL;
	struct device *dev = host->hba->dev;
	struct platform_device *pdev = to_platform_device(dev);

	/* get resource of ufs sys ctrl */
	mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	host->ufs_sys_ctrl = devm_ioremap_resource(dev, mem_res);
	if (!host->ufs_sys_ctrl) {
		dev_err(dev, "cannot ioremap for ufs sys ctrl register\n");
		return -ENOMEM;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		dev_err(host->hba->dev,
			"can't find device node \"hisilicon,crgctrl\"\n");
		return -ENXIO;
	}

	host->pericrg = of_iomap(np, 0);
	if (!host->pericrg) {
		dev_err(host->hba->dev, "crgctrl iomap error!\n");
		return -ENOMEM;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (!np) {
		dev_err(host->hba->dev,
			"can't find device node \"hisilicon,pctrl\"\n");
		return -ENXIO;
	}

	host->pctrl = of_iomap(np, 0);
	if (!host->pctrl) {
		dev_err(host->hba->dev, "pctrl iomap error!\n");
		return -ENOMEM;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");
	if (!np) {
		dev_err(host->hba->dev,
			"can't find device node \"hisilicon,pmctrl\"\n");
		return -ENXIO;
	}

	host->pmctrl = of_iomap(np, 0);
	if (!host->pmctrl) {
		dev_err(host->hba->dev, "pmctrl iomap error!\n");
		return -ENOMEM;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		dev_err(host->hba->dev,
			"can't find device node \"hisilicon,sysctrl\"\n");
		return -ENXIO;
	}

	host->sysctrl = of_iomap(np, 0);
	if (!host->sysctrl) {
		dev_err(host->hba->dev, "sysctrl iomap error!\n");
		return -ENOMEM;
	}

	/* we only use 64 bit dma */
	dev->dma_mask = &kirin_ufs_dma_mask;

	return 0;
}

/*lint -save -e715*/
static ssize_t ufs_kirin_inline_stat_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
#ifdef CONFIG_SCSI_UFS_INLINE_CRYPTO
	struct ufs_hba *hba = dev_get_drvdata(dev);
#endif
	int ret_show = 0;

#ifdef CONFIG_SCSI_UFS_INLINE_CRYPTO
	if (ufshcd_readl(hba, REG_CONTROLLER_CAPABILITIES)
					& MASK_INLINE_ENCRYPTO_SUPPORT)
		ret_show = 1;
#endif

	return snprintf(buf, PAGE_SIZE, "%d\n", ret_show);
}
/*lint -restore*/

static void ufs_kirin_inline_crypto_attr(struct ufs_hba *hba)
{
	hba->inline_state.inline_attr.show = ufs_kirin_inline_stat_show;

	sysfs_attr_init(&hba->inline_state.inline_attr.attr);
	hba->inline_state.inline_attr.attr.name = "ufs_inline_stat";
	hba->inline_state.inline_attr.attr.mode = S_IRUGO;
	if (device_create_file(hba->dev, &hba->inline_state.inline_attr))
		dev_err(hba->dev, "Failed to create sysfs for ufs_inline_state\n");
}

static void ufs_kirin_set_pm_lvl(struct ufs_hba *hba)
{
	hba->rpm_lvl = UFS_PM_LVL_1;
	hba->spm_lvl = UFS_PM_LVL_3;
}

/**
 * ufs_kirin_advertise_quirks - advertise the known KIRIN UFS controller quirks
 * @hba: host controller instance
 *
 * KIRIN UFS host controller might have some non standard behaviours (quirks)
 * than what is specified by UFSHCI specification. Advertise all such
 * quirks to standard UFS host controller driver so standard takes them into
 * account.
 */
static void ufs_kirin_advertise_quirks(struct ufs_hba *hba)
{
	/* put all our quirks here */
//	hba->quirks |= UFSHCD_QUIRK_BROKEN_LCC;
}

static void ufs_kirin_populate_dt(struct device *dev,
				  struct ufs_kirin_host *host)
{
	struct device_node *np = dev->of_node;
	int ret;

	if (!np) {
		dev_err(dev, "can not find device node\n");
		return;
	}

	if (of_find_property(np, "ufs-kirin-use-snps-mphy-tc", NULL))
		host->caps |= USE_SNPS_MPHY_TC;

	if (of_find_property(np, "ufs-kirin-use-fpga-board-clk", NULL))
		host->caps |= USE_FPGA_BOARD_CLK;

	if (of_find_property(np, "ufs-kirin-use-rate-B", NULL))
		host->caps |= USE_RATE_B;

	if (of_find_property(np, "ufs-kirin-broken-fastauto", NULL))
		host->caps |= BROKEN_FASTAUTO;

	if (of_find_property(np, "ufs-kirin-use-one-line", NULL))
		host->caps |= USE_ONE_LANE;

	if (of_find_property(np, "ufs-kirin-use-HS-GEAR3", NULL))
		host->caps |= USE_HS_GEAR3;

	if (of_find_property(np, "ufs-kirin-use-HS-GEAR2", NULL))
		host->caps |= USE_HS_GEAR2;

	if (of_find_property(np, "ufs-kirin-use-HS-GEAR1", NULL))
		host->caps |= USE_HS_GEAR1;

	if (of_find_property(np, "ufs-kirin-use-auto-H8", NULL)) {
		host->caps |= USE_AUTO_H8;
		host->hba->caps |= UFSHCD_CAP_AUTO_HIBERN8;
		host->hba->ahit_ts = 4; /* 4 -> 10ms */
		host->hba->ahit_ah8itv = 1;
	}
#ifdef CONFIG_SCSI_UFS_KIRIN_LINERESET_CHECK
	if (of_find_property(np, "ufs-kirin-linereset-check-disable", NULL))
		host->hba->bg_task_enable = false;
	else
		host->hba->bg_task_enable = true;
#endif

	if (of_find_property(np, "ufs-kirin-broken-clk-gate-pypass", NULL))
		host->caps |= BROKEN_CLK_GATE_BYPASS;

	if (of_find_property(np, "ufs-kirin-unipro-termination", NULL))
		host->hba->quirks |= UFSHCD_QUIRK_UNIPRO_TERMINATION;

	if (of_find_property(np, "ufs-kirin-unipro-scrambing", NULL))
		host->hba->quirks |= UFSHCD_QUIRK_UNIPRO_SCRAMBLING;

	if (!of_property_read_u32(np, "reset-gpio", &(host->reset_gpio))) {
		if (0 > gpio_request(host->reset_gpio, "ufs_device_reset")) {
			pr_err("%s: could not request gpio %d\n", __func__,
			       host->reset_gpio);
			host->reset_gpio = 0xFFFFFFFF;
		}
	} else {
		host->reset_gpio = 0xFFFFFFFF;
	}

	if (of_find_property(np, "ufs-kirin-ssu-by-self", NULL))
		host->hba->caps |= UFSHCD_CAP_SSU_BY_SELF;

	ret = of_property_match_string(np, "ufs-0db-equalizer-product-names", ufs_product_name);
	if ( ret >= 0) {
		dev_info(dev, "find %s in dts\n", ufs_product_name);
		host->tx_equalizer = 0;
	} else {
#ifdef UFS_TX_EQUALIZER_35DB
		host->tx_equalizer = 35;
#endif
#ifdef UFS_TX_EQUALIZER_60DB
		host->tx_equalizer = 60;
#endif
	}
#ifdef CONFIG_UFS_DEVICE_RELATED_CONFIGS
	ret = of_property_match_string(np, "ufs-refclk-drive-4ma-product-names", ufs_product_name);
	if ( ret >= 0) {
		config_refclk_drive_to_4ma = 1;
		dev_info(dev, "config_refclk_drive_to_4ma\n");
	}
	ret = of_property_match_string(np, "ufs-force-link-llane-product-names", ufs_product_name);
	if ( ret >= 0) {
		force_link_to_1lane = 1;
		dev_info(dev, "force_link_to_1lane\n");
	}
#endif
}

/**
 * ufs_kirin_init
 * @hba: host controller instance
 */
static int ufs_kirin_init(struct ufs_hba *hba)
{
	int err = 0;
	struct device *dev = hba->dev;
	struct ufs_kirin_host *host;

#ifdef CONFIG_HISI_BOOTDEVICE
	if (get_bootdevice_type() == BOOT_DEVICE_UFS)
		set_bootdevice_name(dev);
#endif

	host = devm_kzalloc(dev, sizeof(*host), GFP_KERNEL);
	if (!host) {
		err = -ENOMEM;
		dev_err(dev, "%s: no memory for kirin ufs host\n", __func__);
		goto out;
	}

	host->hba = hba;
	hba->priv = (void *)host;

	host->clk_ref = devm_clk_get(dev, "clk_ref");
	if (IS_ERR(host->clk_ref)) {
		err = PTR_ERR(host->clk_ref);
		dev_err(dev, "clk_ref clock not found.\n");
		goto out;
	}

	if( 0 == ufs_rdr_init(hba) ) {
		(void)ufs_rdr_hist_init(hba);
	}

	ufs_kirin_advertise_quirks(hba);

	ufs_kirin_set_pm_lvl(hba);

	ufs_kirin_populate_dt(dev, host);

	err = ufs_kirin_get_resource(host);
	if (err)
		goto host_free;

	ufs_kirin_regulator_init(hba);

	ufs_kirin_clk_init(hba);

	ufs_kirin_soc_init(hba);

	ufs_kirin_inline_crypto_attr(hba);

	scsi_logging_level = UFS_SCSI_LOGGING_LEVEL;

	goto out;

host_free:
	devm_kfree(dev, host);
	hba->priv = NULL;
out:
	return err;
}

static void ufs_kirin_exit(struct ufs_hba *hba)
{
	(void)ufs_rdr_exit(hba);

	return;
}

#ifdef CONFIG_SCSI_UFS_KIRIN_LINERESET_CHECK
/*lint -e550 -e732 -e527 -e529*/
static bool ufs_kirin_can_checking(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = hba->priv;
	if (hba->ufshcd_state != UFSHCD_STATE_OPERATIONAL) {
		return false;
	}
	if (hba->is_hibernate) {
		return false;
	}
	if (hba->pm_op_in_progress) {
		return false;
	}
	if (host->in_suspend) {
		return false;
	}

	return true;
}

static int ufs_kirin_daemon_thread(void *d)
{
	struct ufs_hba *hba = d;
	struct ufs_kirin_host *host = hba->priv;
	unsigned long flags;
	u32 link_state;
	u32 lane0_tx_state, lane0_rx_state, lane1_rx_state;
	u32 linereset_ind;
	u32 lane0_tx_state_p;
	u32 check_times;

	do {
		msleep(1000);
		if (!ufs_kirin_can_checking(hba))
			continue;
		ufs_sys_ctrl_writel(host, 0x08081010, PHY_MPX_TEST_CTRL);
		wmb();
		link_state = ufs_sys_ctrl_readl(host, PHY_MPX_TEST_OBSV);

		lane0_tx_state = (link_state & (0xF << 24)) >> 24;
		lane0_rx_state = (link_state & (0x7 << 8)) >> 8;
		lane1_rx_state = (link_state & (0x7 << 16)) >> 16;

		if (((lane0_tx_state == 0x6) || (lane0_tx_state == 0x7)) && ((lane0_rx_state == 0x2) || (lane1_rx_state == 0x2))) {
			msleep(5);
			if (!ufs_kirin_can_checking(hba))
				continue;
			hba->reg_uecpa = ufshcd_readl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER);
			check_times = 0;
re_check:
			lane0_tx_state_p = lane0_tx_state;
			msleep(50);
			if (!ufs_kirin_can_checking(hba))
				continue;
			ufs_sys_ctrl_writel(host, 0x08081010, PHY_MPX_TEST_CTRL);
			wmb();
			link_state = ufs_sys_ctrl_readl(host, PHY_MPX_TEST_OBSV);

			lane0_tx_state = (link_state & (0xF << 24)) >> 24;
			lane0_rx_state = (link_state & (0x7 << 8)) >> 8;
			lane1_rx_state = (link_state & (0x7 << 16)) >> 16;

			if ((lane0_tx_state == lane0_tx_state_p) && ((lane0_rx_state == 0x2) || (lane1_rx_state == 0x2))) {
				msleep(5);
				if (!ufs_kirin_can_checking(hba))
					continue;
				hba->reg_uecpa = ufshcd_readl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER);
				linereset_ind = (hba->reg_uecpa & (0x1 << 4)) >> 4;
				if (linereset_ind) {
					check_times = 0;
					goto re_check;
				} else if (check_times < 3) {
					check_times++;
					goto re_check;
				} else {
					dev_err(hba->dev, "unipro register error happy, reset hba\n");
					spin_lock_irqsave(hba->host->host_lock, flags);
					/* block commands from scsi mid-layer */
					scsi_block_requests(hba->host);

					/* transfer error masks to sticky bits */
					hba->ufshcd_state = UFSHCD_STATE_EH_SCHEDULED;
					hba->force_reset_hba = 1;
					schedule_work(&hba->eh_work);
					spin_unlock_irqrestore(hba->host->host_lock, flags);
					msleep(4000);
				}
			}

		}
	} while(1);

	return 0;
}
/*lint +e550 +e732 +e527 +e529*/
#endif

/*lint -save -e529 -e438 -e732*/
#ifdef CONFIG_SCSI_UFS_HS_ERROR_RECOVER
int ufs_kirin_get_pwr_by_sysctrl(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;
	u32 link_state;
	u32 lane0_rx_state;

	ufs_sys_ctrl_writel(host, 0x08081010, PHY_MPX_TEST_CTRL);
	wmb();
	link_state = ufs_sys_ctrl_readl(host, PHY_MPX_TEST_OBSV);
	lane0_rx_state = (link_state & (0x7 << 8)) >> 8;

	if (lane0_rx_state == 2)
		return SLOW;
	else if (lane0_rx_state == 3)
		return FAST;
	else
		return -1;
}
#endif
/*lint -restore*/

/**
 * struct ufs_hba_kirin_vops - UFS KIRIN specific variant operations
 *
 * The variant operations configure the necessary controller and PHY
 * handshake during initialization.
 */
const struct ufs_hba_variant_ops ufs_hba_kirin_vops = {
	.name = "kirin",
	.init = ufs_kirin_init,
	.exit = ufs_kirin_exit,
	.setup_clocks = NULL,
	.hce_enable_notify = ufs_kirin_hce_enable_notify,
	.link_startup_notify = ufs_kirin_link_startup_notify,
	.pwr_change_notify = ufs_kirin_pwr_change_notify,
	.full_reset = ufs_kirin_full_reset,
	.device_reset = ufs_kirin_device_hw_reset,
	.suspend_before_set_link_state = ufs_kirin_suspend_before_set_link_state,
	.suspend = ufs_kirin_suspend,
	.resume = ufs_kirin_resume,
	.resume_after_set_link_state = ufs_kirin_resume_after_set_link_state,
#ifdef CONFIG_SCSI_UFS_INLINE_CRYPTO
	.uie_config_init = ufs_kirin_uie_config_init,
	.uie_utrd_pre = ufs_kirin_uie_utrd_prepare,
#endif
	.dump_reg = ufs_kirin_reg_dump,
#ifdef CONFIG_SCSI_UFS_KIRIN_LINERESET_CHECK
	.background_thread = ufs_kirin_daemon_thread,
#endif
#ifdef CONFIG_SCSI_UFS_HS_ERROR_RECOVER
	.get_pwr_by_debug_register = ufs_kirin_get_pwr_by_sysctrl,
#endif
};


#ifdef CONFIG_SCSI_UFS_KIRIN_V21

static void ufs_kirin_v21_soc_init(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;
	u32 reg;

	pr_info("%s ++\n", __func__);

	writel(1<<(SOC_UFS_Sysctrl_CRG_UFS_CFG_ip_rst_ufs_START+16) | 0, \
		SOC_UFS_Sysctrl_CRG_UFS_CFG_ADDR(host->ufs_sys_ctrl));

	ufs_sys_ctrl_set_bits(host, BIT_UFS_PSW_MTCMOS_EN, PSW_POWER_CTRL); /* HC_PSW powerup */
	udelay(10);
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PWR_READY, HC_LP_CTRL); /* notify PWR ready */
#if 0
	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | 0,
		UFS_DEVICE_RESET_CTRL);
#endif

	reg = ufs_sys_ctrl_readl(host, PHY_CLK_CTRL);
	reg = (reg & ~MASK_SYSCTRL_CFG_CLOCK_FREQ) | 0x14;
	ufs_sys_ctrl_writel(host, reg, PHY_CLK_CTRL); /* set cfg clk freq */
	ufs_sys_ctrl_clr_bits(host, MASK_SYSCTRL_REF_CLOCK_SEL, PHY_CLK_CTRL); /* set ref clk freq */

	/* enable ref_clk_en override(bit5) & override value = 1(bit4), with mask */
	ufs_sys_ctrl_writel(host, 0x00300030, UFS_DEVICE_RESET_CTRL);

	/* bypass ufs clk gate */
	ufs_sys_ctrl_set_bits(host, MASK_UFS_CLK_GATE_BYPASS, CLOCK_GATE_BYPASS);
	ufs_sys_ctrl_set_bits(host, MASK_UFS_SYSCRTL_BYPASS, UFS_SYSCTRL);

	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_PSW_CLK_EN, PSW_CLK_CTRL); /* open psw clk */
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PSW_ISO_CTRL, PSW_POWER_CTRL); /* disable ufshc iso */
#if 0
	ufs_sys_ctrl_clr_bits(host, BIT_UFS_PHY_ISO_CTRL, PHY_ISO_EN); /* disable phy iso */
#endif
	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_LP_ISOL_EN, HC_LP_CTRL); /* notice iso disable */

	writel(1<<(SOC_UFS_Sysctrl_CRG_UFS_CFG_ip_arst_ufs_START+16) |\
		1<<SOC_UFS_Sysctrl_CRG_UFS_CFG_ip_arst_ufs_START,\
		SOC_UFS_Sysctrl_CRG_UFS_CFG_ADDR(host->ufs_sys_ctrl));

	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_LP_RESET_N, RESET_CTRL_EN); /* disable lp_reset_n */
	mdelay(1);

	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL); /* open clock of M-PHY */
	ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | 0,\
		UFS_DEVICE_RESET_CTRL); /* reset device */
	writel((1<<SOC_SCTRL_SCPEREN4_gt_clk_ufsio_ref_START),\
		SOC_SCTRL_SCPEREN4_ADDR(host->sysctrl)); /* open clock of device */

	mdelay(2);

	reg = readl(SOC_SCTRL_SCDEEPSLEEPED_ADDR(host->sysctrl));
	if (0 == (reg & (1<<21))) {
		mdelay(1);
		ufs_sys_ctrl_writel(host, MASK_UFS_DEVICE_RESET | BIT_UFS_DEVICE_RESET,\
			UFS_DEVICE_RESET_CTRL); /* disable Device Reset */
	}
	mdelay(40);

#if 0
	/* enable the fix of linereset recovery, and enable rx_reset/tx_rest beat */
	/* enable ref_clk_en override(bit5) & override value = 1(bit4), with mask */
	ufs_sys_ctrl_writel(host, 0x03300330, UFS_DEVICE_RESET_CTRL);
#endif

	writel(1<<(SOC_UFS_Sysctrl_CRG_UFS_CFG_ip_rst_ufs_START+16) |\
		1<<SOC_UFS_Sysctrl_CRG_UFS_CFG_ip_rst_ufs_START,\
		SOC_UFS_Sysctrl_CRG_UFS_CFG_ADDR(host->ufs_sys_ctrl));

	reg = readl(SOC_UFS_Sysctrl_CRG_UFS_CFG_ADDR(host->ufs_sys_ctrl));
	if (reg & (1<<SOC_UFS_Sysctrl_CRG_UFS_CFG_ip_rst_ufs_START))
		mdelay(1);

	/*set SOC_SCTRL_SCBAKDATA11_ADDR 0xffffffff when init*/
	writel(0xffffffff, SOC_SCTRL_SCBAKDATA11_ADDR(host->sysctrl));

	pr_info("%s --\n", __func__);
	return;
}

/**
 * ufs_kirin_v21_init
 * @hba: host controller instance
 */
static int ufs_kirin_v21_init(struct ufs_hba *hba)
{
	int err = 0;
	struct device *dev = hba->dev;
	struct ufs_kirin_host *host;

#ifdef CONFIG_HISI_BOOTDEVICE
	if (get_bootdevice_type() == BOOT_DEVICE_UFS)
		set_bootdevice_name(dev);
#endif

	host = devm_kzalloc(dev, sizeof(*host), GFP_KERNEL);
	if (!host) {
		err = -ENOMEM;
		dev_err(dev, "%s: no memory for kirin ufs host\n", __func__);
		goto out;
	}

	host->hba = hba;
	hba->priv = (void *)host;

	host->clk_ref = devm_clk_get(dev, "clk_ref");
	if (IS_ERR(host->clk_ref)) {
		err = PTR_ERR(host->clk_ref);
		dev_err(dev, "clk_ref clock not found.\n");
		goto out;
	}

	if( 0 == ufs_rdr_init(hba) ) {
		(void)ufs_rdr_hist_init(hba);
	}

	ufs_kirin_advertise_quirks(hba);

	ufs_kirin_set_pm_lvl(hba);

	ufs_kirin_populate_dt(dev, host);

	err = ufs_kirin_get_resource(host);
	if (err)
		goto host_free;

	ufs_kirin_regulator_init(hba);

	ufs_kirin_v21_soc_init(hba);

	goto out;

host_free:
	devm_kfree(dev, host);
	hba->priv = NULL;
out:
	return err;
}

static int ufs_kirin_v21_suspend(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_kirin_host *host = hba->priv;

	/*set SOC_SCTRL_SCBAKDATA11_ADDR 0 when idle*/
	writel(0, SOC_SCTRL_SCBAKDATA11_ADDR(host->sysctrl));

	if (ufshcd_is_runtime_pm(pm_op))
		return 0;

	if (host->in_suspend) {
		WARN_ON(1);/*lint !e730*/
		return 0;
	}

	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	udelay(10);
	/* set ref_dig_clk override of PHY PCS to 0 */
	ufs_sys_ctrl_writel(host, 0x00100000, UFS_DEVICE_RESET_CTRL);
#if 0
	clk_disable_unprepare(host->clk_ref);
#else
	writel((1<<SOC_SCTRL_SCPERDIS4_gt_clk_ufsio_ref_START),\
		SOC_SCTRL_SCPERDIS4_ADDR(host->sysctrl)); /* 关闭Device 的参考时钟 */
#endif

	host->in_suspend = true;

	return 0;
}


static int ufs_kirin_v21_resume(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_kirin_host *host = hba->priv;

	/*set SOC_SCTRL_SCBAKDATA11_ADDR 1 when busy*/
	writel(0x1, SOC_SCTRL_SCBAKDATA11_ADDR(host->sysctrl));

	if (!host->in_suspend)
		return 0;
#if 0
	(void)clk_prepare_enable(host->clk_ref);
#else
	writel((1<<SOC_SCTRL_SCPEREN4_gt_clk_ufsio_ref_START),\
		SOC_SCTRL_SCPEREN4_ADDR(host->sysctrl)); /* 打开Device 的参考时钟 */
#endif
	udelay(1);
	/* set ref_dig_clk override of PHY PCS to 1 */
	ufs_sys_ctrl_writel(host, 0x00100010, UFS_DEVICE_RESET_CTRL);
	udelay(10);
	ufs_sys_ctrl_set_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);


	host->in_suspend = false;
	return 0;
}


/**
 * struct ufs_hba_kirin_vops - UFS KIRIN specific variant operations
 *
 * The variant operations configure the necessary controller and PHY
 * handshake during initialization.
 */
const struct ufs_hba_variant_ops ufs_hba_kirin_v21_vops = {
	.name = "kirin",
	.init = ufs_kirin_v21_init,
	.exit = ufs_kirin_exit,
	.setup_clocks = NULL,
	.hce_enable_notify = ufs_kirin_hce_enable_notify,
	.link_startup_notify = ufs_kirin_link_startup_notify,
	.pwr_change_notify = ufs_kirin_pwr_change_notify,
	.full_reset = ufs_kirin_full_reset,
	.device_reset = ufs_kirin_device_hw_reset,
	.suspend_before_set_link_state = ufs_kirin_suspend_before_set_link_state,
	.suspend = ufs_kirin_v21_suspend,
	.resume = ufs_kirin_v21_resume,
	.resume_after_set_link_state = ufs_kirin_resume_after_set_link_state,
#ifdef CONFIG_SCSI_UFS_INLINE_CRYPTO
	.uie_config_init = ufs_kirin_uie_config_init,
	.uie_utrd_pre = ufs_kirin_uie_utrd_prepare,
#endif
	.dump_reg = ufs_kirin_reg_dump,
};
#endif

EXPORT_SYMBOL(ufs_hba_kirin_vops);
