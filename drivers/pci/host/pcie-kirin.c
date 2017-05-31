/*
 * PCIe host controller driver for Kirin SoCs
 *
 * Copyright (C) 2015 Hilisicon Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 * Author: Xiaowei Song <songxiaowei@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include "pcie-kirin.h"
/*lint -e438 -e529 -e550 -e838 -esym(438,*) -esym(529,*) -esym(550,*) -esym(838,*) */
struct kirin_pcie g_kirin_pcie[] = {
	{
		.irq = {
				{
					.name = "kirin-pcie0-inta",
				},
				{
					.name = "kirin-pcie0-msi",
				},
				{
					.name = "kirin-pcie0-intc",
				},
				{
					.name = "kirin-pcie0-intd",
				},
				{
					.name = "kirin-pcie0-linkdown",
				}
			},
	},
#ifndef CONFIG_KIRIN_PCIE_HI3660
	{
		.irq = {
				{
					.name = "kirin-pcie1-inta",
				},
				{
					.name = "kirin-pcie1-msi",
				},
				{
					.name = "kirin-pcie1-intc",
				},
				{
					.name = "kirin-pcie1-intd",
				},
				{
					.name = "kirin-pcie1-linkdown",
				}
			},
	},
#endif
};

noinline int atfd_hisi_service_pcie_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
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
void enable_req_clk(struct kirin_pcie *pcie, u32 enable_flag)
{
	u32 val;

	val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL1_ADDR);

	if (enable_flag)
		val &= ~PCIE_APB_CLK_REQ;
	else
		val |= PCIE_APB_CLK_REQ;

	kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL1_ADDR);
}

static int kirin_pcie_link_up(struct pcie_port *pp);

void kirin_elb_writel(struct kirin_pcie *pcie, u32 val, u32 reg)
{
	writel(val, pcie->apb_base + reg);
}

u32 kirin_elb_readl(struct kirin_pcie *pcie, u32 reg)
{
	return readl(pcie->apb_base + reg);
}

/*Registers in PCIePHY*/
void kirin_phy_writel(struct kirin_pcie *pcie, u32 val, u32 reg)
{
	writel(val, pcie->phy_base + reg);
}

u32 kirin_phy_readl(struct kirin_pcie *pcie, u32 reg)
{
	return readl(pcie->phy_base + reg);
}
static void kirin_pcie_oe_ctrl(struct kirin_pcie *pcie, int en_flag)
{
	u32 val;

	val = readl(pcie->sctrl_base + SCTRL_SCPERCLKEN3);

	/* set phy_debounce in&out time: 300ns*/
	val |= 0xF0F000;

	/*select oe_gt_mode */
	val |= 0x400;

	/*IO bypass */
	val &= ~IO_HARD_CTRL_DEBOUNCE_BYPASS;

	if (en_flag)
		val &= ~IO_OE_EN_HARD_BYPASS;
	else
		val |= IO_OE_EN_HARD_BYPASS;

	writel(val, pcie->sctrl_base + SCTRL_SCPERCLKEN3);

}

static void kirin_pcie_iso_ctrl(struct kirin_pcie *pcie, int en_flag)
{
	if (en_flag)
		writel(pcie->isoen_value, pcie->sctrl_base + pcie->isoen_offset);
	else
		writel(pcie->isodis_value, pcie->sctrl_base + pcie->isodis_offset);
}

static void kirin_pcie_mtcmos_ctrl(struct kirin_pcie *pcie, int enable)
{
	if (pcie->mtcmos_used) {
		if (enable)/* [false alarm]:fortify */
			writel(MTCMOS_CTRL_BIT, pcie->sctrl_base + SCTRL_SCPWREN);
		else
			writel(MTCMOS_CTRL_BIT, pcie->sctrl_base + SCTRL_SCPWRDIS);
	}
}

static void kirin_pcie_reset_ctrl(struct kirin_pcie *pcie, int reset)
{
	u32 val;

	if (reset) {
		val = pcie->core_assert_value | pcie->phy_assert_value;
		writel(val, pcie->crg_base + pcie->core_assert_offset);
	} else {
		val = pcie->core_deassert_value | pcie->phy_deassert_value;
		writel(val, pcie->crg_base + pcie->core_deassert_offset);
	}
}

static int kirin_pcie_clk_ctrl(struct kirin_pcie *pcie, int clk_on)
{
	int ret = 0;
	unsigned long ref_clk_rate = REF_CLK_FREQ;

	if (clk_on) {
		ret = clk_set_rate(pcie->phy_ref_clk, ref_clk_rate);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to set ref clk rate 100MHz ");
			return ret;
		}

		ret = clk_prepare_enable(pcie->phy_ref_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable phy_ref_clk ");
			return ret;
		}

		ret = clk_prepare_enable(pcie->apb_sys_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable apb_sys_clk ");
			clk_disable_unprepare(pcie->phy_ref_clk);
			return ret;
		}

		ret = clk_prepare_enable(pcie->apb_phy_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable apb_phy_clk ");
			clk_disable_unprepare(pcie->apb_sys_clk);
			clk_disable_unprepare(pcie->phy_ref_clk);
			return ret;
		}

		ret = clk_prepare_enable(pcie->pcie_aclk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable pcie_aclk ");
			clk_disable_unprepare(pcie->apb_phy_clk);
			clk_disable_unprepare(pcie->phy_ref_clk);
			clk_disable_unprepare(pcie->apb_sys_clk);
			return ret;
		}

		ret = clk_prepare_enable(pcie->pcie_aux_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable pcie_pclk ");
			clk_disable_unprepare(pcie->pcie_aclk);
			clk_disable_unprepare(pcie->apb_phy_clk);
			clk_disable_unprepare(pcie->phy_ref_clk);
			clk_disable_unprepare(pcie->apb_sys_clk);
			return ret;
		}
	} else {
		clk_disable_unprepare(pcie->apb_sys_clk);
		clk_disable_unprepare(pcie->apb_phy_clk);
		clk_disable_unprepare(pcie->pcie_aclk);
		clk_disable_unprepare(pcie->phy_ref_clk);
		clk_disable_unprepare(pcie->pcie_aux_clk);
	}

	return ret;
}

static int32_t kirin_pcie_get_clk(struct kirin_pcie *pcie, struct platform_device *pdev)
{
	pcie->phy_ref_clk = devm_clk_get(&pdev->dev, "pcie_phy_ref");
	if (IS_ERR(pcie->phy_ref_clk)) {
		PCIE_PR_ERR("Failed to get pcie_phy_ref clock");
		return PTR_ERR(pcie->phy_ref_clk);
	}

	pcie->pcie_aux_clk = devm_clk_get(&pdev->dev, "pcie_aux");
	if (IS_ERR(pcie->pcie_aux_clk)) {
		PCIE_PR_ERR("Failed to get pcie_aux clock");
		return PTR_ERR(pcie->pcie_aux_clk);
	}

	pcie->apb_phy_clk = devm_clk_get(&pdev->dev, "pcie_apb_phy");
	if (IS_ERR(pcie->apb_phy_clk)) {
		PCIE_PR_ERR("Failed to get pcie_apb_phy clock");
		return PTR_ERR(pcie->apb_phy_clk);
	}

	pcie->apb_sys_clk = devm_clk_get(&pdev->dev, "pcie_apb_sys");
	if (IS_ERR(pcie->apb_sys_clk)) {
		PCIE_PR_ERR("Failed to get pcie_apb_sys clock");
		return PTR_ERR(pcie->apb_sys_clk);
	}

	pcie->pcie_aclk = devm_clk_get(&pdev->dev, "pcie_aclk");
	if (IS_ERR(pcie->pcie_aclk)) {
		PCIE_PR_ERR("Failed to get pcie_aclk clock");
		return PTR_ERR(pcie->pcie_aclk);
	}
	PCIE_PR_INFO("Successed to get all clock");

	return 0;
}


static int32_t kirin_pcie_get_resource(struct pcie_port *pp, struct platform_device *pdev)
{
	struct resource *apb;
	struct resource *phy;
	struct resource *dbi;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);
	struct device_node *np;

	apb = platform_get_resource_byname(pdev, IORESOURCE_MEM, "apb");
	pcie->apb_base = devm_ioremap_resource(&pdev->dev, apb);
	if (IS_ERR(pcie->apb_base)) {
		PCIE_PR_ERR("cannot get apb base");
		return PTR_ERR(pcie->apb_base);
	}

	phy = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	pcie->phy_base = devm_ioremap_resource(&pdev->dev, phy);
	if (IS_ERR(pcie->phy_base)) {
		PCIE_PR_ERR("cannot get PCIePHY base");
		return PTR_ERR(pcie->phy_base);
	}

	dbi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	pp->dbi_base = devm_ioremap_resource(&pdev->dev, dbi);
	if (IS_ERR(pp->dbi_base)) {
		PCIE_PR_ERR("cannot get PCIe dbi base");
		return PTR_ERR(pp->dbi_base);
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		PCIE_PR_ERR("Failed to find crgctrl Node ");
		return -1;
	}
	pcie->crg_base = of_iomap(np, 0);
	if (!pcie->crg_base) {
		PCIE_PR_ERR("crg_base iomap fail");
		return -1;
	}
	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		PCIE_PR_ERR("Failed to find sysctrl Node ");
		return -1;
	}
	pcie->sctrl_base = of_iomap(np, 0);
	if (!pcie->sctrl_base) {
		PCIE_PR_ERR("sctrl_base iomap fail");
		return -1;
	}
	PCIE_PR_INFO("Successed to get all resource");
	return 0;
}

static void kirin_pcie_config_l1ss(struct kirin_pcie *pcie, enum l1ss_ctrl_state enable)
{
	u32 reg_val;
	int pm;

	if (pcie->board_type != BOARD_ASIC)
		return;
	if (!pcie->rc_dev) {
		PCIE_PR_ERR("Failed to get RC_dev ");
		return;
	}
	if (enable) {
		enable_req_clk(pcie, DISABLE);
		pm = pci_find_ext_capability(pcie->rc_dev, PCI_EXT_L1SS_CAP_ID);
		if (pm) {
			pci_read_config_dword(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, &reg_val);
			reg_val |= 0xF;
			pci_write_config_dword(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, reg_val);
		}

		pcie_capability_read_dword(pcie->rc_dev, PCI_EXP_DEVCTL2, &reg_val);
		reg_val |= (0x1 << 10);
		pcie_capability_write_dword(pcie->rc_dev, PCI_EXP_DEVCTL2, reg_val);

		if (!pcie->ep_dev) {
			PCIE_PR_ERR("NO EP Device Found ");
			return;
		}
		pm = pci_find_ext_capability(pcie->ep_dev, PCI_EXT_L1SS_CAP_ID);
		if (pm) {
			/*EP: Power On Value & Scale*/
			if (pcie->ep_l1ss_ctrl2) {
				pci_read_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL2, &reg_val);
				reg_val &= ~0xFF;
				reg_val |= pcie->ep_l1ss_ctrl2;
				pci_write_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL2, reg_val);
			}

			pci_read_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, &reg_val);
			reg_val |= 0xF;
			pci_write_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, reg_val);
		}
		/*EP: LTR Latency*/
		if (pcie->ep_ltr_latency) {
			pm = pci_find_ext_capability(pcie->ep_dev, PCI_EXT_LTR_CAP_ID);
			if (pm)
				pci_write_config_dword(pcie->ep_dev, pm + LTR_MAX_SNOOP_LATENCY, pcie->ep_ltr_latency);
		}
		pm = pci_find_capability(pcie->ep_dev, PCI_CAP_ID_EXP);
		if (pm) {
			pci_read_config_dword(pcie->ep_dev, pm + PCI_EXP_DEVCTL2, &reg_val);
			reg_val |= (0x1 << 10);
			pci_write_config_dword(pcie->ep_dev, pm + PCI_EXP_DEVCTL2, reg_val);
		}
	} else {
		enable_req_clk(pcie, ENABLE);

		pm = pci_find_ext_capability(pcie->rc_dev, PCI_EXT_L1SS_CAP_ID);
		if (pm) {
			pci_read_config_dword(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, &reg_val);
			reg_val &= ~L1SS_PM_ALL;
			pci_write_config_dword(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, reg_val);
		}

		if (!pcie->ep_dev) {
			PCIE_PR_ERR("NO EP Device Found ");
			return;
		}

		pm = pci_find_ext_capability(pcie->ep_dev, PCI_EXT_L1SS_CAP_ID);
		if (pm) {
			pci_read_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, &reg_val);
			reg_val &= ~L1SS_PM_ALL;
			pci_write_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, reg_val);
		}
	}
}

/**param: flag == 0   disable aspm L0sL1
**        flag == 1   enalbe  aspm L0sL1
**/
static void kirin_pcie_config_l0sl1(struct kirin_pcie *pcie, enum link_aspm_state aspm_state)
{
	if (pcie->board_type != BOARD_ASIC)
		return;
	if (!pcie->rc_dev) {
		PCIE_PR_ERR("Failed to get RC_dev ");
		return;
	}
	pcie_capability_clear_and_set_word(pcie->rc_dev, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC, aspm_state);

	if (!pcie->ep_dev) {
		PCIE_PR_ERR("NO EP Device Found ");
		return;
	}
	pcie_capability_clear_and_set_word(pcie->ep_dev, PCI_EXP_LNKCTL,
				PCI_EXP_LNKCTL_ASPMC, aspm_state);

}

static int32_t kirin_pcie_get_boardtype(struct kirin_pcie *pcie, struct platform_device *pdev)
{
	int len;
	int ret;
	u32 eye_param;
	size_t array_num = 2;
	struct device_node *np;
	u32 val[2];

	np = pdev->dev.of_node;
	if (of_property_read_u32(np, "board_type", &pcie->board_type)) {
		PCIE_PR_ERR("Failed to get BoardType");
		pcie->board_type = 2;
	}
	PCIE_PR_INFO("BoardType value [%d] ", pcie->board_type);

	if (of_property_read_u32(np, "mtcmos-used", &pcie->mtcmos_used)) {
		PCIE_PR_ERR("Failed to get mtcmos-used info");
		return -1;
	}
	PCIE_PR_INFO("mtcmos-used value [%d] ", pcie->mtcmos_used);

	if (of_find_property(np, "ep_flag", &len)) {
		pcie->ep_flag = 1;
		PCIE_PR_INFO("EndPoint Device");
	} else {
		pcie->ep_flag = 0;
		PCIE_PR_INFO("RootComplex");
	}
	ret = of_property_read_u32(np, "eye_param_ctrl2", &eye_param);
	if (ret) {
		PCIE_PR_ERR("Failed to get eye param");
		pcie->pcie_eye_param_ctrl2 = 0x0;
	} else {
		pcie->pcie_eye_param_ctrl2 = eye_param;
		PCIE_PR_INFO("eye param value [0x%x] ", eye_param);
	}

	ret = of_property_read_u32(np, "eye_param_ctrl3", &eye_param);
	if (ret) {
		PCIE_PR_ERR("Failed to get eye param");
		pcie->pcie_eye_param_ctrl3 = 0x0;
	} else {
		pcie->pcie_eye_param_ctrl3 = eye_param;
		PCIE_PR_INFO("eye param value [0x%x] ", eye_param);
	}
	if (of_property_read_u32_array(np, "isoen", val, array_num)) {
		PCIE_PR_ERR("Failed to read isoen dts info");
		return -1;
	}
	pcie->isoen_offset = val[0];
	pcie->isoen_value = val[1];
	if (of_property_read_u32_array(np, "isodis", val, array_num)) {
		PCIE_PR_ERR("Failed to read isodis dts info");
		return -1;
	}
	pcie->isodis_offset = val[0];
	pcie->isodis_value = val[1];

	if (of_property_read_u32_array(np, "phy_assert", val, array_num)) {
		PCIE_PR_ERR("Failed to read phy_assert dts info");
		return -1;
	}
	pcie->phy_assert_offset = val[0];
	pcie->phy_assert_value = val[1];
	if (of_property_read_u32_array(np, "phy_deassert", val, array_num)) {
		PCIE_PR_ERR("Failed to read phy_deassert dts info");
		return -1;
	}
	pcie->phy_deassert_offset = val[0];
	pcie->phy_deassert_value = val[1];
	if (of_property_read_u32_array(np, "core_assert", val, array_num)) {
		PCIE_PR_ERR("Failed to read phy_assert dts info");
		return -1;
	}
	pcie->core_assert_offset = val[0];
	pcie->core_assert_value = val[1];
	if (of_property_read_u32_array(np, "core_deassert", val, array_num)) {
		PCIE_PR_ERR("Failed to read phy_deassert dts info");
		return -1;
	}
	pcie->core_deassert_offset = val[0];
	pcie->core_deassert_value = val[1];

	return 0;
}

static void kirin_pcie_get_epinfo(struct kirin_pcie *pcie, struct platform_device *pdev)
{
	int ret;

	ret = of_property_read_u32(pdev->dev.of_node, "ep_ltr_latency", &pcie->ep_ltr_latency);
	if (ret) {
		PCIE_PR_DEBUG("Not to set ep ltr_latency ?");
		pcie->ep_ltr_latency = 0x0;
	}

	ret = of_property_read_u32(pdev->dev.of_node, "ep_l1ss_ctrl2", &pcie->ep_l1ss_ctrl2);
	if (ret) {
		PCIE_PR_DEBUG("Not to set ep L1ss_ctrl2 ?");
		pcie->ep_l1ss_ctrl2 = 0x0;
	}

	PCIE_PR_DEBUG(" set ltr_latency to [0x%x], set l1ss_ctrl2 to [0x%x] ",
			pcie->ep_ltr_latency, pcie->ep_l1ss_ctrl2);
}

static void kirin_pcie_sideband_dbi_w_mode(struct pcie_port *pp, bool on)
{
	u32 val;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL0_ADDR);
	if (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	else
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL0_ADDR);
}

static void kirin_pcie_sideband_dbi_r_mode(struct pcie_port *pp, bool on)
{
	u32 val;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL1_ADDR);
	if (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	else
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL1_ADDR);
}

static int kirin_pcie_phy_init(struct kirin_pcie *pcie);
int kirin_pcie_power_on(struct pcie_port *pp, int on_flag)
{
	struct kirin_pcie *pcie = to_kirin_pcie(pp);
	int ret;
	u32 reg_val;

	/*power on*/
	if (on_flag) {
		kirin_pcie_mtcmos_ctrl(pcie, ENABLE);
		udelay(100);
		PCIE_PR_DEBUG("mtcmos on Done ");

		if (pcie->board_type == BOARD_ASIC) {
			kirin_pcie_oe_ctrl(pcie, ENABLE);
			PCIE_PR_DEBUG("OE CFG Done ");
		}
			/*clk enable*/
		ret = kirin_pcie_clk_ctrl(pcie, ENABLE);
		udelay(1);
		if (ret)
			return -EINVAL;
		PCIE_PR_DEBUG("clock on Done ");
		/*clk disable*/
		ret = kirin_pcie_clk_ctrl(pcie, DISABLE);
		if (ret)
			return -EINVAL;
		udelay(1);
		PCIE_PR_DEBUG("clk off Done ");

		/*ISO disable*/
		kirin_pcie_iso_ctrl(pcie, DISABLE);
		PCIE_PR_DEBUG("iso disable Done ");

		/*unset module*/
		kirin_pcie_reset_ctrl(pcie, DISABLE);
		PCIE_PR_DEBUG("module unreset Done ");

		/*clk on*/
		ret = kirin_pcie_clk_ctrl(pcie, ENABLE);
		if (ret)
			return -EINVAL;
		PCIE_PR_DEBUG("clk on Done ");

		/*disable hardware auto-gate, enable software vote*/
		if (pcie->board_type == BOARD_ASIC) {
			writel(HW_AUTO_CF_BIT, pcie->sctrl_base + SCTRL_SCPERCLKEN2);
			ret = kirin_pcie_phy_init(pcie);
			if (ret) {
				PCIE_PR_ERR("Phy Init Failed ");
				return ret;
			}
			PCIE_PR_DEBUG("Phy Init Done ");
		}

		pcie->is_power_on = 1;

		/*rst EP*/

		reg_val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL12_ADDR);
		reg_val |= PERST_FUN_SEC;
		reg_val |= PERST_ASSERT_EN;
		kirin_elb_writel(pcie, reg_val, SOC_PCIECTRL_CTRL12_ADDR);

		if (pcie->board_type == BOARD_ASIC) {
			/*IOMUX-clkreq*/
			ret = atfd_hisi_service_pcie_smc(ACCESS_REGISTER_FN_SUB_ID_PCIE_IO_SET,
					WR_FLAG, IOMG_CLKREQ, 0x0);
			if (ret) {
				PCIE_PR_ERR("Failed to set IO to clk_req ");
				return ret;
			}
		}
	} else {
		/*rst EP*/
		reg_val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL12_ADDR);
		reg_val |= PERST_FUN_SEC;
		reg_val &= ~PERST_ASSERT_EN;
		kirin_elb_writel(pcie, reg_val, SOC_PCIECTRL_CTRL12_ADDR);
		kirin_pcie_reset_ctrl(pcie, ENABLE);

		ret = kirin_pcie_clk_ctrl(pcie, DISABLE);

		if (ret)
			return -EINVAL;
		kirin_pcie_iso_ctrl(pcie, ENABLE);
		kirin_pcie_mtcmos_ctrl(pcie, DISABLE);
		if (pcie->board_type == BOARD_ASIC) {
			kirin_pcie_oe_ctrl(pcie, DISABLE);
			PCIE_PR_DEBUG("OE CFG Done ");
			/*enable hardware auto-gate, disable software vote*/
			writel(HW_AUTO_CF_BIT, pcie->sctrl_base + SCTRL_SCPERCLKDIS2);
			/*IOMUX-gpio*/
			ret = atfd_hisi_service_pcie_smc(ACCESS_REGISTER_FN_SUB_ID_PCIE_IO_SET,
					WR_FLAG, IOMG_GPIO, 0x0);
			if (ret) {
				PCIE_PR_ERR("Failed to set IO to GPIO ");
				return ret;
			}
		}

		pcie->is_power_on = 0;
	}
	return 0;
}


static int kirin_pcie_establish_link(struct pcie_port *pp)
{
	int count = 0;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	PCIE_PR_INFO("++");

	if (kirin_pcie_link_up(pp)) {
		PCIE_PR_ERR("Link already up");
		return 0;
	}

	/* setup root complex */
	dw_pcie_setup_rc(pp);
	PCIE_PR_DEBUG("setup rc Done ");

	/* assert LTSSM enable */
	kirin_elb_writel(pcie, PCIE_LTSSM_ENABLE_BIT,
			  PCIE_APP_LTSSM_ENABLE);

	/* check if the link is up or not */
	while (!kirin_pcie_link_up(pp)) {
		mdelay(1);
		count++;
		if (count == 20) {
			PCIE_PR_ERR("Link Fail, Reg should be 0x11 or 0x41 not [0x%x] ",
				 kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR));
			return -EINVAL;
		}
	}

	PCIE_PR_INFO("PCIe Link Success ");
	return 0;
}

/*EP rigist hook fun for link event notification*/
int kirin_pcie_register_event(struct kirin_pcie_register_event *reg)
{
	int ret = 0;
	struct pci_dev *dev;
	struct pcie_port *pp;
	struct kirin_pcie *pcie;

	if (!reg || !reg->user) {
		PCIE_PR_INFO("Event registration or User of event is NULL");
		return -ENODEV;
	}

	dev = (struct pci_dev *)reg->user;
	pp = (struct pcie_port *)(dev->bus->sysdata);
	/*lint -e826 -esym(826,*)*/
	pcie = container_of(pp, struct kirin_pcie, pp);
	/*lint -e826 +esym(826,*)*/

	if (pp) {
		pcie->event_reg = reg;
		PCIE_PR_INFO("Event 0x%x is registered for RC", reg->events);
	} else {
		PCIE_PR_INFO("PCIe: did not find RC for pci endpoint device");
		ret = -ENODEV;
	}
	return ret;
}

int kirin_pcie_deregister_event(struct kirin_pcie_register_event *reg)
{
	int ret = 0;
	struct pci_dev *dev;
	struct pcie_port *pp;
	struct kirin_pcie *pcie;

	if (!reg || !reg->user) {
		PCIE_PR_INFO("Event registration or User of event is NULL");
		return -ENODEV;
	}

	dev = (struct pci_dev *)reg->user;
	pp = (struct pcie_port *)(dev->bus->sysdata);
	/*lint -e826 -esym(826,*)*/
	pcie = container_of(pp, struct kirin_pcie, pp);
	/*lint -e826 +esym(826,*)*/

	if (pp) {
		pcie->event_reg = NULL;
		PCIE_PR_INFO("deregistered ");
	} else {
		PCIE_PR_INFO("No RC for this EP device ");
		ret = -ENODEV;
	}
	return ret;
}

/*print apb and cfg-register of RC*/
static void dump_link_register(struct kirin_pcie *pcie)
{
	struct pcie_port *pp = &pcie->pp;
	int i;
	u32 j;
	u32 val0, val1, val2, val3;

	if (!pcie->is_power_on)
		return;

	PCIE_PR_INFO("####DUMP RC CFG Register ");
	for (i = 0; i < 0x18; i++) {
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x0, 4, &val0);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x4, 4, &val1);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x8, 4, &val2);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0xC, 4, &val3);
		printk(KERN_INFO "0x%-8x: %8x %8x %8x %8x \n", 0x10 * i, val0, val1, val2, val3);
	}
	for (i = 0; i < 6; i++) {
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x0 + 0x700, 4, &val0);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x4 + 0x700, 4, &val1);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x8 + 0x700, 4, &val2);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0xC + 0x700, 4, &val3);
		printk(KERN_INFO "0x%-8x: %8x %8x %8x %8x \n", 0x10 * i + 0x700, val0, val1, val2, val3);
	}
	for (i = 0; i < 0x9; i++) {
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x0 + 0x8A0, 4, &val0);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x4 + 0x8A0, 4, &val1);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0x8 + 0x8A0, 4, &val2);
		kirin_pcie_rd_own_conf(pp, 0x10 * i + 0xC + 0x8A0, 4, &val3);
		printk(KERN_INFO "0x%-8x: %8x %8x %8x %8x \n", 0x10 * i + 0x8A0, val0, val1, val2, val3);
	}



	PCIE_PR_INFO("####DUMP APB CORE Register : ");
	for (j = 0; j < 0x4; j++) {
		printk(KERN_INFO "0x%-8x: %8x %8x %8x %8x \n",
			0x10 * j,
			kirin_elb_readl(pcie, 0x10 * j + 0x0),
			kirin_elb_readl(pcie, 0x10 * j + 0x4),
			kirin_elb_readl(pcie, 0x10 * j + 0x8),
			kirin_elb_readl(pcie, 0x10 * j + 0xC));
	}
	for (j = 0; j < 0x2; j++) {
		printk(KERN_INFO "0x%-8x: %8x %8x %8x %8x \n",
			0x10 * j + 0x400,
			kirin_elb_readl(pcie, 0x10 * j + 0x0 + 0x400),
			kirin_elb_readl(pcie, 0x10 * j + 0x4 + 0x400),
			kirin_elb_readl(pcie, 0x10 * j + 0x8 + 0x400),
			kirin_elb_readl(pcie, 0x10 * j + 0xC + 0x400));
	}


	PCIE_PR_INFO("####DUMP APB PHY Register : ");
	printk(KERN_INFO "0x%-8x: %8x %8x %8x %8x %8x ",
		0x0,
		kirin_phy_readl(pcie, 0x0),
		kirin_phy_readl(pcie, 0x4),
		kirin_phy_readl(pcie, 0x8),
		kirin_phy_readl(pcie, 0xc),
		kirin_phy_readl(pcie, 0x400));
	printk("\n");

	return;

}


/*notify EP about link-down event*/
static void kirin_pcie_notify_callback(struct kirin_pcie *pcie, enum kirin_pcie_event event)
{
	if ((pcie->event_reg != NULL) && (pcie->event_reg->callback != NULL) &&
			(pcie->event_reg->events & event)) {
		struct kirin_pcie_notify *notify = &pcie->event_reg->notify;
		notify->event = event;
		notify->user = pcie->event_reg->user;
		PCIE_PR_INFO("Callback for the event : %d", event);
		pcie->event_reg->callback(notify);
	} else {
		PCIE_PR_INFO("EP does not register this event : %d", event);
	}
}

static void kirin_handle_work(struct work_struct *work)
{
	/*lint -e826 -esym(826,*)*/
	struct kirin_pcie *pcie = container_of(work, struct kirin_pcie, handle_work);
	/*lint -e826 +esym(826,*)*/

	kirin_pcie_notify_callback(pcie, KIRIN_PCIE_EVENT_LINKDOWN);

	dump_link_register(pcie);

}


static irqreturn_t kirin_pcie_linkdown_irq_handler(int irq, void *arg)
{
	struct pcie_port *pp = arg;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	PCIE_PR_ERR("linkdown irq[%d] triggled", irq);

	schedule_work(&pcie->handle_work);

	return IRQ_HANDLED;
}
static irqreturn_t kirin_pcie_msi_irq_handler(int irq, void *arg)
{
	struct pcie_port *pp = arg;

	PCIE_PR_ERR("msi irq[%d] triggled", irq);
	return dw_handle_msi_irq(pp);
}

#ifdef CONFIG_KIRIN_PCIE_TEST
static irqreturn_t kirin_pcie_intx_irq_handler(int irq, void *arg)
{
	PCIE_PR_ERR("intx irq[%d] triggled", irq);
	return IRQ_HANDLED;
}
#endif

static void kirin_pcie_msi_init(struct pcie_port *pp)
{
	dw_pcie_msi_init(pp);

}

static void kirin_pcie_enable_interrupts(struct pcie_port *pp)
{
	if (IS_ENABLED(CONFIG_PCI_MSI))
		kirin_pcie_msi_init(pp);
}

void kirin_pcie_readl_rc(struct pcie_port *pp,
					void __iomem *dbi_base, u32 *val)
{
	kirin_pcie_sideband_dbi_r_mode(pp, true);
	*val = readl(dbi_base);
	kirin_pcie_sideband_dbi_r_mode(pp, false);
}

void kirin_pcie_writel_rc(struct pcie_port *pp,
					u32 val, void __iomem *dbi_base)
{
	kirin_pcie_sideband_dbi_w_mode(pp, true);
	writel(val, dbi_base);
	kirin_pcie_sideband_dbi_w_mode(pp, false);
}

int kirin_pcie_rd_own_conf(struct pcie_port *pp, int where, int size,
				u32 *val)
{
	int ret;

	kirin_pcie_sideband_dbi_r_mode(pp, true);
	ret = dw_pcie_cfg_read(pp->dbi_base + (where & ~0x3), where, size, val);
	kirin_pcie_sideband_dbi_r_mode(pp, false);
	return ret;
}

int kirin_pcie_wr_own_conf(struct pcie_port *pp, int where, int size,
				u32 val)
{
	int ret;

	kirin_pcie_sideband_dbi_w_mode(pp, true);
	ret = dw_pcie_cfg_write(pp->dbi_base + (where & ~0x3),
			where, size, val);
	kirin_pcie_sideband_dbi_w_mode(pp, false);
	return ret;
}

static int kirin_pcie_link_up(struct pcie_port *pp)
{
	struct kirin_pcie *pcie = to_kirin_pcie(pp);
	u32 val = kirin_elb_readl(pcie, PCIE_ELBI_RDLH_LINKUP);

	if ((val & PCIE_LINKUP_ENABLE) == PCIE_LINKUP_ENABLE)
		return 1;

	return 0;
}
static void set_phy_eye_param(struct kirin_pcie *pcie)
{
	u32 eye_param;

	if (pcie->pcie_eye_param_ctrl2)
		kirin_phy_writel(pcie, pcie->pcie_eye_param_ctrl2, SOC_PCIEPHY_CTRL2_ADDR);

	if (pcie->pcie_eye_param_ctrl3)
		kirin_phy_writel(pcie, pcie->pcie_eye_param_ctrl3, SOC_PCIEPHY_CTRL3_ADDR);

	eye_param = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL2_ADDR);
	PCIE_PR_INFO("pcie_eye_param_ctrl2 is 0x%x", eye_param);
	eye_param = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL3_ADDR);
	PCIE_PR_INFO("pcie_eye_param_ctrl3 is 0x%x", eye_param);

}

static int kirin_pcie_phy_init(struct kirin_pcie *pcie)
{
	u32 reg_val;
	u32 pipe_clk_stable = 0x1 << 19;
	u32 time = 10;

	set_phy_eye_param(pcie);

	/*choose 100MHz clk src: Bit[8]==1 pll, Bit[8]==0 Board */
	reg_val = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL1_ADDR);
	reg_val &= ~(0x1 << 8);
	kirin_phy_writel(pcie, reg_val, SOC_PCIEPHY_CTRL1_ADDR);

	/*pull down phy_test_powerdown signal */
	reg_val = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL0_ADDR);
	reg_val &= ~(0x1 << 22);
	kirin_phy_writel(pcie, reg_val, SOC_PCIEPHY_CTRL0_ADDR);
	udelay(10);

	/*derst PHY */
	reg_val = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL1_ADDR);
	reg_val &= ~(0x1 << 16);
	kirin_phy_writel(pcie, reg_val, SOC_PCIEPHY_CTRL1_ADDR);


	reg_val = kirin_phy_readl(pcie, SOC_PCIEPHY_STATE0_ADDR);
	while (reg_val & pipe_clk_stable) {
		udelay(100);
		if (time == 0) {
			PCIE_PR_INFO("PIPE clk is not stable");
			return -EINVAL;
		}
		time--;
		reg_val = kirin_phy_readl(pcie, SOC_PCIEPHY_STATE0_ADDR);
	}
	return 0;
}

static void kirin_pcie_host_init(struct pcie_port *pp)
{
	kirin_pcie_establish_link(pp);
	kirin_pcie_enable_interrupts(pp);
}

static struct pcie_host_ops kirin_pcie_host_ops = {
	.readl_rc = kirin_pcie_readl_rc,
	.writel_rc = kirin_pcie_writel_rc,
	.rd_own_conf = kirin_pcie_rd_own_conf,
	.wr_own_conf = kirin_pcie_wr_own_conf,
	.link_up = kirin_pcie_link_up,
	.host_init = kirin_pcie_host_init,
};

static int __init kirin_add_pcie_port(struct pcie_port *pp,
					   struct platform_device *pdev)
{
	int ret;
	int index;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	PCIE_PR_INFO("++");
	for (index = 0; index < MAX_IRQ_NUM; index++) {
		pcie->irq[index].num = platform_get_irq(pdev, index);
		if (!pcie->irq[index].num) {
			PCIE_PR_ERR("failed to get [%s] irq ,num = [%d]", pcie->irq[index].name,
				pcie->irq[index].num);
			return -ENODEV;
		}
	}
#ifdef CONFIG_KIRIN_PCIE_TEST
	ret = devm_request_irq(&pdev->dev, (unsigned int)pcie->irq[IRQ_INTC].num,
				kirin_pcie_intx_irq_handler,
				(unsigned long)IRQF_TRIGGER_RISING, pcie->irq[IRQ_INTC].name, pp);
	ret |= devm_request_irq(&pdev->dev, (unsigned int)pcie->irq[IRQ_INTD].num,
				kirin_pcie_intx_irq_handler,
				(unsigned long)IRQF_TRIGGER_RISING, pcie->irq[IRQ_INTD].name, pp);
	if (ret) {
		PCIE_PR_ERR("failed to request intx irq");
		return ret;
	}
#endif
	pp->irq[IRQ_INTA] = pcie->irq[IRQ_INTA].num;
	pp->irq[IRQ_INTB] = pcie->irq[IRQ_INTB].num;
	pp->irq[IRQ_INTC] = pcie->irq[IRQ_INTC].num;
	pp->irq[IRQ_INTD] = pcie->irq[IRQ_INTD].num;
	pp->link_down_irq = pcie->irq[IRQ_LINKDOWN].num;
	ret = devm_request_irq(&pdev->dev, pp->link_down_irq,
				kirin_pcie_linkdown_irq_handler,
				IRQF_TRIGGER_RISING, pcie->irq[IRQ_LINKDOWN].name, pp);
	if (ret) {
		PCIE_PR_ERR("failed to request link-down irq");
		return ret;
	}
	PCIE_PR_INFO("pcie->irq[1].name = [%s], pcie->irq[4].name = [%s]",pcie->irq[IRQ_MSI].name, pcie->irq[IRQ_LINKDOWN].name);
	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		pp->msi_irq = pcie->irq[IRQ_MSI].num;
		ret = devm_request_irq(&pdev->dev, pp->msi_irq,
					kirin_pcie_msi_irq_handler,
					IRQF_SHARED | IRQF_TRIGGER_RISING, pcie->irq[IRQ_MSI].name, pp);
		if (ret) {
			PCIE_PR_ERR("failed to request msi irq");
			return ret;
		}
	}

	pp->root_bus_nr = -1;
	pp->ops = &kirin_pcie_host_ops;

	PCIE_PR_INFO("Add pcie port sucessed ");
	return 0;
}


#ifdef CONFIG_KIRIN_PCIE_TEST
static int kirin_pcie_ep_init(struct pci_dev *pdev,
							const struct pci_device_id *ent)
{
	int ret;

	PCIE_PR_DEBUG("pci dev on bus[0x%d] has dev_id[0x%x] and ven_id[0x%x]",
			pdev->bus->number, ent->device, ent->vendor);

	ret = pci_enable_device(pdev);
	if (ret) {
		PCIE_PR_ERR("Cannot enable PCI device");
		return ret;
	}
	pci_set_master(pdev);

	PCIE_PR_DEBUG("--");
	return 0;
}

static struct pci_device_id kirin_pci_devid[] = {
	{ .vendor = 0x19e5,
	.device = 0x0,
	.subvendor = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
	.class = 0x028000,
	.class_mask = 0xffff00,
	.driver_data = 0,
	},
	{ .vendor = 0x19e5,
	.device = 0x1,
	.subvendor = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
	.class = 0x028000,
	.class_mask = 0xffff00,
	.driver_data = 0,
	},
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, kirin_pci_devid);

static struct pci_driver kirin_pcie_ep_driver = {
	node:		{},
	name :		"kirin-pcie-ep",
	id_table :	kirin_pci_devid,
	probe :		kirin_pcie_ep_init,
};

#endif

static int kirin_pcie_probe(struct platform_device *pdev)
{
	struct kirin_pcie *pcie;
	struct pcie_port *pp;
	int ret;
	u32 rc_id;

	PCIE_PR_INFO("++");

	if (pdev->dev.of_node == NULL) {
		PCIE_PR_ERR("of node is NULL ");
		return -EINVAL;
	}

	if (of_property_read_u32(pdev->dev.of_node, "rc-id", &rc_id)) {
		dev_err(&pdev->dev, "Failed to get rc id form dts\n");
		return -EINVAL;
	}
	if (rc_id >= MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_id);
		return -EINVAL;
	}
	PCIE_PR_INFO("PCIe No.%d probe", rc_id);
	pcie = &g_kirin_pcie[rc_id];
	pcie->rc_id = rc_id;
	pcie->rc_dev = NULL;
	pcie->ep_dev = NULL;
	pp = &pcie->pp;

	pp->dev = &(pdev->dev);

	ret = kirin_pcie_get_boardtype(pcie, pdev);
	if (ret != 0)
		return -ENODEV;

	kirin_pcie_get_epinfo(pcie, pdev);

	ret = kirin_pcie_get_clk(pcie, pdev);
	if (ret != 0)
		return -ENODEV;

	ret = kirin_pcie_get_resource(pp, pdev);
	if (ret != 0)
		return -ENODEV;

	if (pcie->ep_flag) {
		PCIE_PR_INFO("@@@EP Mode");
		ret = kirin_pcie_power_on(pp, 1);
		if (ret) {
			PCIE_PR_ERR("Failed to Power On EP ");
			return -EINVAL;
		}
		kirin_elb_writel(pcie, 0x200000, 0x0);
		writel(0x10023, pp->dbi_base + 0x710);
		writel(0x10001, pp->dbi_base + 0xa0);
		kirin_elb_writel(pcie, 0x800, 0x1c);
		kirin_pcie_sideband_dbi_r_mode(pp, 1);
		kirin_pcie_sideband_dbi_w_mode(pp, 1);
		ret = 0x19e5 + (rc_id << 16);
		writel(ret, pp->dbi_base);
		ret = readl(pcie->pp.dbi_base);
		PCIE_PR_INFO("DevID&VendorID is [0x%x]", ret);
		/*Modify EP device class from 0x0(unsupport) to net devices*/
		ret = readl(pcie->pp.dbi_base + 0x8);
		ret |= 0x02800000;
		writel(ret, pp->dbi_base + 0x8);
		ret = readl(pcie->pp.dbi_base + 0x8);
		PCIE_PR_INFO("Device class is [0x%x]", ret);

		pp->ops = &kirin_pcie_host_ops;
	} else {
		PCIE_PR_INFO("###RC Mode");
		pcie->is_enumerated = 0;
		pcie->is_power_on = 0;
		pcie->usr_suspend = 1;
		ret = kirin_add_pcie_port(pp, pdev);
		if (ret < 0) {
			PCIE_PR_ERR("Failed to assign resource, ret=[%d]", ret);
			return ret;
		}
	}

	platform_set_drvdata(pdev, pcie);

	INIT_WORK(&pcie->handle_work, kirin_handle_work);

#if defined(CONFIG_KIRIN_PCIE_TEST) && defined(CONFIG_DEBUG_FS)
	pcie_debug_init(pcie);
#endif
	PCIE_PR_INFO("--");
	return 0;

}

#ifdef CONFIG_PM
/*resume complete*/
static void kirin_pcie_complete(struct device *dev)
{
	struct kirin_pcie *pcie;

	PCIE_PR_INFO("++");

	pcie = dev_get_drvdata(dev);
	if (pcie == NULL) {
		PCIE_PR_ERR("Can't get drvdata");
		return;
	}
	if (pcie->is_power_on) {
		if (pcie->usr_suspend) {
			if (kirin_pcie_power_on(&pcie->pp, DISABLE)) {
				PCIE_PR_ERR("Failed to Power OFF ");
				return;
			}
		}
		else {
			kirin_pcie_config_l0sl1(pcie, ASPM_L0S_L1);
			kirin_pcie_config_l1ss(pcie, L1SS_PM_ASPM_ALL);
		}
	}

	PCIE_PR_INFO("--");
}


/*prepare for sleep*/
static int kirin_pcie_prepare(struct device *dev)
{
	struct kirin_pcie *pcie;
	PCIE_PR_INFO("++");
	pcie = dev_get_drvdata(dev);
	if (pcie == NULL) {
		PCIE_PR_ERR("Can't get drvdata");
		return -EINVAL;
	}

	if (!pcie->is_power_on && pcie->is_enumerated) {
		if (kirin_pcie_power_on(&pcie->pp, 1)) {
			PCIE_PR_ERR("Failed to Power On RC ");
			return -EINVAL;
		}
	}

	PCIE_PR_INFO("--");
	return 0;
}


static int kirin_pcie_resume(struct device *dev)
{
	struct kirin_pcie *pcie;
	struct pci_dev *rc_dev;

	PCIE_PR_INFO("++");

	pcie = dev_get_drvdata(dev);
	if (pcie == NULL) {
		PCIE_PR_ERR("Can't get drvdata");
		return -EINVAL;
	}
	rc_dev = pcie->rc_dev;
	if (!pcie->usr_suspend) {
		PCIE_PR_ERR("begin to recover RC cfg ");
		pci_load_saved_state(rc_dev, pcie->rc_saved_state);
		pci_restore_state(rc_dev);
	}

	PCIE_PR_INFO("--");
	return 0;
}

static int kirin_pcie_suspend(struct device *dev)
{
	PCIE_PR_INFO("--");

	return 0;
}

static int kirin_pcie_resume_noirq(struct device *dev)
{
	struct pcie_port *pp;
	struct kirin_pcie *pcie;

	PCIE_PR_INFO("++");

	pcie = dev_get_drvdata(dev);
	if (pcie == NULL) {
		PCIE_PR_ERR("Can't get drvdata");
		return -EINVAL;
	}
	pp = &pcie->pp;
	if (pcie->is_enumerated) {
		if (kirin_pcie_power_on(pp, 1)) {
			PCIE_PR_ERR("Failed to Power On ");
			return -EINVAL;
		}

		if (!pcie->usr_suspend) {
			/* assert LTSSM enable */
			kirin_elb_writel(pcie, PCIE_LTSSM_ENABLE_BIT,
					PCIE_APP_LTSSM_ENABLE);
		}
	}

	PCIE_PR_INFO("--");

	return 0;
}


static void kirin_pcie_shutdown_prepare(struct pci_dev *dev)
{
	int ret;
	u32 pm;
	u32 value;
	int index = 0;
	struct pcie_port *pp;
	struct kirin_pcie *pcie;

	PCIE_PR_INFO("++");

	pp = dev->sysdata;
	pcie = to_kirin_pcie(pp);
	kirin_pcie_config_l0sl1(pcie, ASPM_CLOSE);
	kirin_pcie_config_l1ss(pcie, L1SS_CLOSE);
	/*Enable PME*/
	pm = pci_find_capability(dev, PCI_CAP_ID_PM);
	if (!pm) {
		PCIE_PR_ERR("Can't find PCI_CAP_ID_PM");
		return;
	}
	kirin_pcie_rd_own_conf(pp, pm + PCI_PM_CTRL, 4, &value);
	value |= 0x100;
	kirin_pcie_wr_own_conf(pp, pm + PCI_PM_CTRL, 4, value);

	/*Broadcast PME_turn_off MSG*/
	ret = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	ret |= PME_TURN_OFF_BIT;
	kirin_elb_writel(pcie, ret, SOC_PCIECTRL_CTRL7_ADDR);

	do {
		ret = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE1_ADDR);
		ret = ret & PME_ACK_BIT;
		if (index >= 10) {
			PCIE_PR_ERR("Failed to get PME_TO_ACK");
			break;
		}
		index++;
		udelay(1);
	} while (ret != PME_ACK_BIT);

	/*Entry L23*/
	ret = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	ret |= ENTRY_L23_BIT;
	kirin_elb_writel(pcie, ret, SOC_PCIECTRL_CTRL7_ADDR);

	/*phy rst from sys to pipe */
	ret = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL1_ADDR);
	ret |= 0x1 << 17;
	kirin_phy_writel(pcie, ret, SOC_PCIEPHY_CTRL1_ADDR);

	ret = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR);
	PCIE_PR_INFO("L23 register value: 0x%x ", ret);

	PCIE_PR_INFO("--");
}

static int kirin_pcie_suspend_noirq(struct device *dev)
{
	struct kirin_pcie *pcie;
	struct pci_dev *rc_dev;
	struct pcie_port *pp;

	PCIE_PR_INFO("++");

	pcie = dev_get_drvdata(dev);
	if (pcie == NULL) {
		PCIE_PR_ERR("Can't get drvdata");
		return -EINVAL;
	}
	rc_dev = pcie->rc_dev;
	pp = &pcie->pp;

	if (pcie->is_power_on) {
		if (!pcie->usr_suspend)
			kirin_pcie_shutdown_prepare(rc_dev);
		if (kirin_pcie_power_on(pp, 0)) {
			PCIE_PR_ERR("Failed to Power OFF ");
			return -EINVAL;
		}
	}

	PCIE_PR_INFO("--");

	return 0;
}

#else

#define kirin_pcie_suspend_noirq NULL
#define kirin_pcie_resume_noirq NULL
#define kirin_pcie_suspend NULL
#define kirin_pcie_resume NULL
#define kirin_pcie_complete NULL
#define kirin_pcie_prepare NULL

#endif

static const struct dev_pm_ops kirin_pcie_dev_pm_ops = {
	.suspend_noirq	= kirin_pcie_suspend_noirq,
	.resume_noirq	= kirin_pcie_resume_noirq,
	.suspend	= kirin_pcie_suspend,
	.resume	= kirin_pcie_resume,
	.complete	= kirin_pcie_complete,
	.prepare	= kirin_pcie_prepare,
};

static const struct of_device_id kirin_pcie_match_table[] = {
	{
		.compatible = "hisilicon,kirin-pcie",
		.data = NULL,
	},
	/*lint -e785 -esym(785,*)*/
	{},
	/*lint -e785 +esym(785,*)*/
};

MODULE_DEVICE_TABLE(of, kirin_pcie_match_table);

struct platform_driver kirin_pcie_driver = {
	.probe			= kirin_pcie_probe,
	.driver			= {
		.name			= "Kirin-pcie",
		.owner			= THIS_MODULE,
		.pm				= &kirin_pcie_dev_pm_ops,
		.of_match_table = of_match_ptr(kirin_pcie_match_table),
	},
};

static int kirin_pcie_usr_suspend(u32 rc_idx)
{
	int ret;
	struct pcie_port *pp;
	struct pci_dev *rc_dev;
	struct kirin_pcie *pcie = &g_kirin_pcie[rc_idx];

	PCIE_PR_INFO("++");
	PCIE_PR_DEBUG("rc_id = [%d] ", rc_idx);

	pp = &pcie->pp;
	rc_dev = pcie->rc_dev;
	kirin_pcie_shutdown_prepare(rc_dev);

	/*关闭所有时钟*/
	ret = kirin_pcie_power_on(pp, DISABLE);
	if (ret) {
		PCIE_PR_ERR("PCIe No.%d failed to Power OFF ", rc_idx);
		return -EINVAL;
	}
	pcie->usr_suspend = 1;
	rc_dev->msi_enabled = 0;

	PCIE_PR_INFO("--");
	return 0;
}

static int kirin_pcie_usr_resume(u32 rc_idx)
{
	int ret;
	struct pcie_port *pp;
	struct pci_dev *rc_dev;
	struct kirin_pcie *pcie = &g_kirin_pcie[rc_idx];

	PCIE_PR_INFO("++");
	PCIE_PR_DEBUG("rc_id = [%ud] ", rc_idx);

	pp = &pcie->pp;
	rc_dev = pcie->rc_dev;
	ret = kirin_pcie_power_on(pp, ENABLE);
	if (ret) {
		PCIE_PR_ERR("PCIe No.%d failed to Power ON ", rc_idx);
		return -EINVAL;
	}
	ret = kirin_pcie_establish_link(&pcie->pp);
	if (ret)
		return -EINVAL;
	pci_load_saved_state(rc_dev, pcie->rc_saved_state);
	pci_restore_state(rc_dev);
	kirin_pcie_config_l0sl1(pcie, ASPM_L0S_L1);
	kirin_pcie_config_l1ss(pcie, L1SS_PM_ASPM_ALL);
	pcie->usr_suspend = 0;
	rc_dev->msi_enabled = 1;

	PCIE_PR_INFO("--");

	return 0;
}

/*
* EP Power ON/OFF callback Function:
* param: rc_idx---which rc the EP link with
*        resume_flag---1:PowerOn, 0: PowerOFF
*/
int kirin_pcie_pm_control(int resume_flag, u32 rc_idx)
{
	PCIE_PR_DEBUG("RC = [%u] ", rc_idx);

	if (rc_idx >= MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_idx);
		return -EINVAL;
	}
	if (resume_flag) {
		PCIE_PR_INFO("EP Notify to PowerON");
		return kirin_pcie_usr_resume(rc_idx);
	} else {
		PCIE_PR_INFO("EP Notify to Poweroff");
		return kirin_pcie_usr_suspend(rc_idx);
	}
}
EXPORT_SYMBOL_GPL(kirin_pcie_pm_control);

/*
* Enumerate Function:
* param: rc_idx---which rc the EP link with
*/
int kirin_pcie_enumerate(u32 rc_idx)
{
	int ret;
	u32 val;
	u32 dev_id;
	u32 vendor_id;
	struct pcie_port *pp;
	struct pci_bus *bus1;
	struct pci_dev *dev;
	struct kirin_pcie *pcie;

	PCIE_PR_INFO("++");
	PCIE_PR_DEBUG("RC[%u] begin to Enumerate ", rc_idx);

	if (rc_idx >= MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_idx);
		return -EINVAL;
	}
	pcie = &g_kirin_pcie[rc_idx];
	pp = &pcie->pp;

	if (pcie->is_enumerated) {
		PCIE_PR_ERR("Enumeration was done Successed Before");
		return 0;
	}

	/*clk on*/
	ret = kirin_pcie_power_on(pp, ENABLE);
	if (ret) {
		PCIE_PR_ERR("Failed to Power RC");
		return ret;
	}
	kirin_pcie_readl_rc(pp, pp->dbi_base, &val);
	val += rc_idx;
	kirin_pcie_writel_rc(pp, val, pp->dbi_base);

	if (pcie->board_type == BOARD_FPGA) {
		kirin_pcie_writel_rc(pp, 0x10002, pp->dbi_base + 0xa0);
	}

	ret = dw_pcie_host_init(pp);
	if (ret) {
		PCIE_PR_ERR("failed to initialize host");
		return ret;
	}
	kirin_pcie_rd_own_conf(pp, PCI_VENDOR_ID, 2, &vendor_id);
	kirin_pcie_rd_own_conf(pp, PCI_DEVICE_ID, 2, &dev_id);
	pcie->rc_dev = pci_get_device(vendor_id, dev_id, pcie->rc_dev);
	if (!pcie->rc_dev) {
		PCIE_PR_ERR("Failed to get RC Device ");
		return -1;
	}
	ret = pci_save_state(pcie->rc_dev);
	pcie->rc_saved_state = pci_store_saved_state(pcie->rc_dev);
	if (ret) {
		PCIE_PR_ERR("Failed to save state of RC.");
		return ret;
	}
	bus1 = pcie->rc_dev->subordinate;
	if (bus1) {
		list_for_each_entry(dev, &bus1->devices, bus_list) {
			if (pci_is_pcie(dev)) {
				pcie->ep_dev = dev;
				pcie->is_enumerated = 1;
				pcie->ep_devid = dev->device;
				pcie->ep_venid = dev->vendor;
				PCIE_PR_INFO("ep vendorid = 0x%x, deviceid = 0x%x", pcie->ep_venid, pcie->ep_devid);
			}
		}
	} else {
		PCIE_PR_ERR("bus1 is NULL");
		pcie->ep_dev = NULL;
	}
	if (!pcie->ep_dev) {
		PCIE_PR_ERR("there is no ep dev");
		return -1;
	}

		kirin_pcie_config_l0sl1(pcie, ASPM_L0S_L1);
		kirin_pcie_config_l1ss(pcie, L1SS_PM_ASPM_ALL);

	PCIE_PR_INFO("--");

	return 0;
}
EXPORT_SYMBOL(kirin_pcie_enumerate);

int __init kirin_pcie_init(void)
{
	int ret = 0;

#ifdef CONFIG_KIRIN_PCIE_TEST
	ret = pci_register_driver(&kirin_pcie_ep_driver);
	if (ret)
		PCIE_PR_ERR("Failed to register kirin ep driver");
#endif

	ret = platform_driver_probe(&kirin_pcie_driver, kirin_pcie_probe);
	return ret;
}
/*lint -e438 -e529 -e550 -e838 +esym(438,*) +esym(529,*) +esym(550,*) +esym(838,*) */

subsys_initcall(kirin_pcie_init);

MODULE_AUTHOR("Xiaowei Song<songxiaowei@huawei.com>");
MODULE_DESCRIPTION("Hisilicon Kirin pcie driver");
MODULE_LICENSE("GPL");
