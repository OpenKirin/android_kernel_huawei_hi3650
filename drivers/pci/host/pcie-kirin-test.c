/*
 * PCIe host controller driver for Kirin 960 SoCs
 *
 * Copyright (C) 2015 Huawei Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*lint -e438 -e529 -e550 -e774 -e838 -esym(438,*) -esym(529,*) -esym(550,*) -esym(774,*) -esym(838,*) */

#include "pcie-kirin.h"
#include <linux/pci-aspm.h>
#include <asm/memory.h>
#include <linux/pci_regs.h>

#define TEST_MEM_SIZE 0x400000
#define TRANSFER_TIMES 50

struct pcie_test_st {
	struct kirin_pcie *pcie;
	u32 is_ep_wifi;
	u64 rc_mem_addr;
	u64 ep_mem_addr;
	u32 wl_power;
};

struct pcie_test_st g_test_kirin_pcie[MAX_RC_NUM];


/**
 * test_enable_dbi - make it possible to access the rc configuration registers in the CDM,
 * or the ep configuration registers.
 * @flag: If flag equals 0, you can access the ep configuration registers in the CDM;
 *  If not, you can access the rc configuration registers in the CDM.
 */
void test_enable_dbi(u32 rc_id, int flag)
{
	int ret1;
	int ret2;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;

	ret1 = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL0_ADDR);
	ret2 = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL1_ADDR);
	if (flag) {
		ret1 = ret1 | PCIE_ELBI_SLV_DBI_ENABLE;
		ret2 = ret2 | PCIE_ELBI_SLV_DBI_ENABLE;
	} else {
		ret1 = ret1 & (~PCIE_ELBI_SLV_DBI_ENABLE);
		ret2 = ret2 & (~PCIE_ELBI_SLV_DBI_ENABLE);
	}
	kirin_elb_writel(pcie, ret1, SOC_PCIECTRL_CTRL0_ADDR);
	kirin_elb_writel(pcie, ret2, SOC_PCIECTRL_CTRL1_ADDR);

	udelay(2);
	ret1 = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL0_ADDR);
	ret2 = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL1_ADDR);

	PCIE_PR_INFO("apb register 0x0=[0x%x], 0x4=[0x%x]", ret1, ret2);
}

/**
 * set_bme - enable bus master or not.
 * @flag: If flag equals 0, bus master is disabled. If not, bus master is enabled.
 */
void set_bme(u32 rc_id, int flag)
{
	int ret;
	struct pcie_port *pp;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);

	test_enable_dbi(rc_id, ENABLE);
	ret = readl(pp->dbi_base + PCI_COMMAND);
	if (flag) {
		PCIE_PR_INFO("Enable Bus master!!!");
		ret |= PCI_COMMAND_MASTER;
	} else {
		PCIE_PR_INFO("Disable Bus master!!!");
		ret &= ~PCI_COMMAND_MASTER;/* [false alarm]:fortify */
	}
	writel(ret, pp->dbi_base + PCI_COMMAND);
	udelay(5);
	ret = readl(pp->dbi_base + PCI_COMMAND);
	PCIE_PR_INFO("register[0x4] value is [0x%x]", ret);
	test_enable_dbi(rc_id, DISABLE);
}

/**
 * set_mse - enable mem space or not.
 * @flag: If flag equals 0, mem space is disabled. If not, mem space is enabled.
 */
void set_mse(u32 rc_id, int flag)
{
	int ret;
	struct pcie_port *pp;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);

	test_enable_dbi(rc_id, ENABLE);
	ret = readl(pp->dbi_base + PCI_COMMAND);
	if (flag) {
		PCIE_PR_INFO("Enable MEM space!!!");
		ret |= PCI_COMMAND_MEMORY;
	} else {
		PCIE_PR_INFO("Disable MEM space!!!");
		ret &= ~PCI_COMMAND_MEMORY;/* [false alarm]:fortify */
	}
	writel(ret, pp->dbi_base + PCI_COMMAND);
	udelay(5);
	ret = readl(pp->dbi_base + PCI_COMMAND);
	PCIE_PR_INFO("register[0x4] value is [0x%x]", ret);
	test_enable_dbi(rc_id, DISABLE);
}

noinline int hisi_service_pcie_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
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
void test_set_iomux(u32 write_flag, u32 value)
{
	if (write_flag)
		hisi_service_pcie_smc(ACCESS_REGISTER_FN_SUB_ID_PCIE_IO_SET, WR_FLAG, value, 0x0);
	else
		hisi_service_pcie_smc(ACCESS_REGISTER_FN_SUB_ID_PCIE_IO_SET, RD_FLAG, 0x0, 0x0);
}

int retrain_link(u32 rc_id)
{
	u16 reg16;
	unsigned long start_jiffies;
	struct pci_dev *rc_dev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	rc_dev = test_kirin_pcie->pcie->rc_dev;
	if (!rc_dev) {
		PCIE_PR_ERR("Failed to get RC device");
		return -1;
	}

	pcie_capability_read_word(rc_dev, PCI_EXP_LNKCTL, &reg16);

	/* Retrain link */
	reg16 |= PCI_EXP_LNKCTL_RL;
	pcie_capability_write_word(rc_dev, PCI_EXP_LNKCTL, reg16);

	/* Wait for link training end. Break out after waiting for timeout */
	start_jiffies = jiffies;
	for (;;) {
		pcie_capability_read_word(rc_dev, PCI_EXP_LNKSTA, &reg16);
		if (!(reg16 & PCI_EXP_LNKSTA_LT))
			break;
		if (time_after(jiffies, start_jiffies + HZ))
			break;
		msleep(1);
	}
	if (!(reg16 & PCI_EXP_LNKSTA_LT))
		return 0;
	return -1;
}

int set_link_speed(u32 rc_id, enum link_speed gen)
{
	u16 val = 0x1;
	int ret = 0;
	struct pci_dev *rc_dev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	rc_dev = test_kirin_pcie->pcie->rc_dev;
	if (!rc_dev) {
		PCIE_PR_ERR("Failed to get RC device");
		return -1;
	}
	switch (gen) {
	case GEN1:
		val = 0x1;
		break;
	case GEN2:
		val = 0x2;
		break;
	case GEN3:
		val = 0x4;
		break;
	default:
		ret = -1;
	}
	pcie_capability_write_word(rc_dev, PCI_EXP_LNKCTL2, val);
	if (!ret)
		return retrain_link(rc_id);
	return ret;
}
int show_link_speed(u32 rc_id)
{
	unsigned int val;
	struct kirin_pcie *pcie;

	pcie = g_test_kirin_pcie[rc_id].pcie;
	val = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR);
	val = val & 0xc0;
	switch (val) {
	case 0x0:
		PCIE_PR_INFO("Link speed: gen1");
		break;
	case 0x40:
		PCIE_PR_INFO("Link speed: gen2");
		break;
	case 0x80:
		PCIE_PR_INFO("Link speed: gen3");
		break;
	default:
		PCIE_PR_INFO("Link speed info unknow");
	}
    
	return val;
}
/**
 * show_link_state - show the rc link state.
 */
u32 show_link_state(u32 rc_id)
{
	unsigned int val;
	struct kirin_pcie *pcie;

	pcie = g_test_kirin_pcie[rc_id].pcie;
	if (!pcie)
		return 0xFFFFFFFF;
	val = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR);

	PCIE_PR_INFO("Register 0x410 value [0x%x]", val);

	val = val & 0x3f;

	switch (val) {
	case 0x3:
		PCIE_PR_INFO("L-state: Compliance");
		break;
	case 0x11:
		PCIE_PR_INFO("L-state: L0");
		break;
	case 0x12:
		PCIE_PR_INFO("L-state: L0S");
		break;
	case 0x14: {
		val = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE5_ADDR);
		PCIE_PR_INFO("Register 0x414 value [0x%x]", val);
		val = val & 0xC000;
		if (val == 0x4000)
			PCIE_PR_ERR("L-state: L1.1");
		else if (val == 0xC000)
			PCIE_PR_ERR("L-state: L1.2");
		else {
			PCIE_PR_ERR("L-state: L1.0");
			val = 0x14;
		}
		break;
	}
	case 0x15:
		PCIE_PR_INFO("L-state: L2");
		break;
	case 0x1B:
		PCIE_PR_INFO("L-state: LoopBack");
		break;
	default:
		val = 0x0;
		PCIE_PR_ERR("other state");
	}
	return val;
}
/**
 * show_trans_rate - show data transmission rate.
 * @begin_time: The time before transmission;
 * @end_time: The time after transmission;
 * @size: The size of datas.
 */
long int show_trans_rate(u64 begin_time, u64 end_time, u64 size)
{
	u64 time_count = end_time - begin_time;
	long int rate = ((size * sizeof(char) * 8 * 100 * TRANSFER_TIMES)/time_count);

	PCIE_PR_INFO("data size [%lld], time sapce [%lld]",
		(size * sizeof(char) * 8 * 100 * TRANSFER_TIMES), time_count);
	PCIE_PR_INFO("time sapce [%lld]. Transferring Rate is :[%ld] Bit/s", time_count, rate);

	return rate;
}

void show_pci_dev_state(u32 rc_id)
{
	int pm;
	u32 reg_value;
	struct pcie_port *pp;
	struct pci_dev *ep_dev;
	struct pci_dev *rc_dev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	ep_dev = test_kirin_pcie->pcie->ep_dev;
	rc_dev = test_kirin_pcie->pcie->rc_dev;
	pp = &(test_kirin_pcie->pcie->pp);

	if (rc_dev == NULL || ep_dev == NULL) {
		PCIE_PR_ERR("Failed to get Device");
		return;
	}

	pm = pci_find_capability(rc_dev, PCI_CAP_ID_PM);
	if (pm) {
		kirin_pcie_rd_own_conf(pp, pm + PCI_PM_CTRL, 4, &reg_value);
		PCIE_PR_INFO("rc: pci_pm_ctrl reg value = [0x%x]", reg_value & 0x3);
	}

	pm = pci_find_capability(ep_dev, PCI_CAP_ID_PM);
	if (pm) {
		pci_read_config_dword(ep_dev, pm + PCI_PM_CTRL, &reg_value);
		PCIE_PR_INFO("EP: pci_pm_ctrl reg value = [0x%x]", reg_value & 0x3);
	}
}

int config_aspm_l0s_l1(u32 rc_id, enum link_aspm_state aspm_state)
{
	struct pci_dev *ep_dev;
	struct pci_dev *rc_dev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	ep_dev = test_kirin_pcie->pcie->ep_dev;
	rc_dev = test_kirin_pcie->pcie->rc_dev;

	if (ep_dev == NULL || rc_dev == NULL) {
		PCIE_PR_ERR("Failed to get PCI Device");
		return -1;
	}

	pcie_capability_clear_and_set_word(rc_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_ASPMC, aspm_state);
	pcie_capability_clear_and_set_word(ep_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_ASPMC, aspm_state);
	return 0;
}

int config_enable_l1ss(u32 rc_id, enum l1ss_ctrl_state state)
{
	unsigned int pm;
	unsigned int reg_val;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	
	if ((pcie->ep_dev == NULL) || (pcie->rc_dev == NULL)){
		PCIE_PR_ERR("Failed to get Device");
		return -1;
	}
	enable_req_clk(pcie, 0);
	pm = pci_find_ext_capability(pcie->rc_dev, PCI_EXT_L1SS_CAP_ID);
	if (pm)
		pci_write_config_byte(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, state);

	pcie_capability_read_dword(pcie->rc_dev, PCI_EXP_DEVCTL2, &reg_val);
	reg_val |= (0x1 << 10);
	pcie_capability_write_dword(pcie->rc_dev, PCI_EXP_DEVCTL2, reg_val);

	pm = pci_find_ext_capability(pcie->ep_dev, PCI_EXT_L1SS_CAP_ID);
	if (pm) {
		pci_read_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL2, &reg_val);
		reg_val &= ~0xFF;
		reg_val |= 0x61;
		pci_write_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL2, reg_val);

		pci_write_config_byte(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, state);
	}
	pm = pci_find_ext_capability(pcie->ep_dev, PCI_EXT_LTR_CAP_ID);
	if (pm)
		pci_write_config_dword(pcie->ep_dev, pm + LTR_MAX_SNOOP_LATENCY, 0x10031003);

	pm = pci_find_capability(pcie->ep_dev, PCI_CAP_ID_EXP);
	if (pm) {
		pci_read_config_dword(pcie->ep_dev, pm + PCI_EXP_DEVCTL2, &reg_val);
		reg_val |= (0x1 << 10);
		pci_write_config_dword(pcie->ep_dev, pm + PCI_EXP_DEVCTL2, reg_val);
	}

	return 0;
}

int config_disable_l1ss(u32 rc_id)
{
	int pm;
	unsigned int reg_val;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;

	if ((pcie->ep_dev == NULL) || (pcie->rc_dev == NULL)){
		PCIE_PR_ERR("Failed to get Device");
		return -1;
	}

	enable_req_clk(pcie, 1);
	pm = pci_find_ext_capability(pcie->rc_dev, PCI_EXT_L1SS_CAP_ID);
	if (pm) {
		pci_read_config_dword(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, &reg_val);
		reg_val &= ~L1SS_PM_ALL;
		pci_write_config_dword(pcie->rc_dev, pm + PCI_EXT_L1SS_CTRL1, reg_val);
	}

	pm = pci_find_ext_capability(pcie->ep_dev, PCI_EXT_L1SS_CAP_ID);
	if (pm) {
		pci_read_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, &reg_val);
		reg_val &= ~L1SS_PM_ALL;
		pci_write_config_dword(pcie->ep_dev, pm + PCI_EXT_L1SS_CTRL1, reg_val);
	}
	return 0;
}


/**
* config_rc_l23 - config rc's l2 or l3 link state;
* @l3_flag: 0----rc link state is configured to be l2 ,
*               others----rc link state is configured to be l3.
*/
int config_rc_l23(u32 rc_id, int l3_flag)
{
	int ret;
	u32 value;
	int pm;
	struct pcie_port *pp;
	struct pci_dev *rc_dev;
	struct pci_dev *ep_dev;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	pp = &(pcie->pp);
	rc_dev = pcie->rc_dev;
	ep_dev = pcie->ep_dev;
	if (ep_dev == NULL || rc_dev == NULL) {
		PCIE_PR_ERR("Failed to get Device");
		return -1;
	}

	/*EP wake signal Select*/
	value = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL12_ADDR);
	value |= (0x3<<12);
	kirin_elb_writel(pcie, value, SOC_PCIECTRL_CTRL12_ADDR);

	/*Enable PME*/
	/*RC */
	pm = pci_find_capability(rc_dev, PCI_CAP_ID_PM);
	if (pm) {
		kirin_pcie_rd_own_conf(pp, pm + PCI_PM_CTRL, 4, &value);
		value |= PCI_PM_CTRL_PME_ENABLE;
		value |= PCI_PM_CTRL_STATE_MASK;
		kirin_pcie_wr_own_conf(pp, pm + PCI_PM_CTRL, 4, value);
	}
	/*EP devices*/
	pm = pci_find_capability(ep_dev, PCI_CAP_ID_PM);
	if (pm) {
		pci_read_config_dword(ep_dev, pm + PCI_PM_CTRL, &value);
		value |= PCI_PM_CTRL_PME_ENABLE;
		pci_write_config_dword(ep_dev, pm + PCI_PM_CTRL, value);
	}

	/*Change PHY reset signal to software*/
	value = kirin_phy_readl(pcie, SOC_PCIEPHY_CTRL1_ADDR);
	value |= (0x1<<17);
	kirin_phy_writel(pcie, value, SOC_PCIEPHY_CTRL1_ADDR);

	/*send PME_turn_off*/
	value = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	value |= (0x5<<8);
	value &= ~(0x1<<8);
	kirin_elb_writel(pcie, value, SOC_PCIECTRL_CTRL7_ADDR);

	ret = pci_save_state(rc_dev);
	if (ret) {
		PCIE_PR_ERR("Failed to save state of RC.");
		return ret;
	}

	ret = pci_save_state(ep_dev);
	if (ret) {
		PCIE_PR_ERR("Failed to save state of EP.");
		return ret;
	}

	PCIE_PR_INFO("Waiting for PME_TO_ACK MSG");
	ret = 0;
	do {
		udelay(1);
		value = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE1_ADDR);
		ret++;
	} while ((value & (0x1<<16)) != (0x1 << 16) && ret < 20);

	PCIE_PR_INFO("Getton PME_TO_ACK MSG");

	if (l3_flag) {
		ret = kirin_pcie_power_on(pp, 0);
		if (ret) {
			PCIE_PR_ERR("Failed to Power OFF");
			return -EINVAL;
		}
	}

	return 0;
}

void config_ep_l23(u32 rc_id)
{
	unsigned int ret;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;

	/*EP wake signal Select*/
	ret = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL12_ADDR);
	ret |= (0x1<<12);
	ret &= ~(0x1<<13);
	kirin_elb_writel(pcie, ret, SOC_PCIECTRL_CTRL12_ADDR);

	ret = kirin_pcie_rd_own_conf(&(pcie->pp), 0x44, 4, &ret);
	ret |= (0x1 << 8);
	kirin_pcie_wr_own_conf(&(pcie->pp), 0x44, 4, ret);


	/*Change PHY reset signal to software*/
	ret = kirin_elb_readl(pcie, SOC_PCIEPHY_CTRL1_ADDR);
	ret |= (0x1<<17);
	kirin_elb_writel(pcie, ret, SOC_PCIEPHY_CTRL1_ADDR);

	ret = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	ret |= (0x1<<10);
	ret |= (0x1<<2);
	kirin_elb_writel(pcie, ret, SOC_PCIECTRL_CTRL7_ADDR);
}

void kirin_pcie_outbound_atu(u32 rc_id, int index,
		int type, u64 cpu_addr, u64 pci_addr, u32 size)
{
	struct pcie_port *pp;
	void __iomem *dbi_base;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);
	dbi_base = pp->dbi_base;

	kirin_pcie_writel_rc(pp, PCIE_ATU_REGION_OUTBOUND | (u32)index,
			  dbi_base + PCIE_ATU_VIEWPORT);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr), dbi_base + PCIE_ATU_LOWER_BASE);
	kirin_pcie_writel_rc(pp, upper_32_bits(cpu_addr), dbi_base + PCIE_ATU_UPPER_BASE);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr + size - 1),
			  dbi_base + PCIE_ATU_LIMIT);
	kirin_pcie_writel_rc(pp, lower_32_bits(pci_addr), dbi_base + PCIE_ATU_LOWER_TARGET);
	kirin_pcie_writel_rc(pp, upper_32_bits(pci_addr), dbi_base + PCIE_ATU_UPPER_TARGET);
	kirin_pcie_writel_rc(pp, type, dbi_base + PCIE_ATU_CR1);
	kirin_pcie_writel_rc(pp, PCIE_ATU_ENABLE, dbi_base + PCIE_ATU_CR2);
}

void kirin_pcie_inbound_atu(u32 rc_id, int index,
		int type, u64 cpu_addr, u64 pci_addr, u32 size)
{
	struct pcie_port *pp;
	void __iomem *dbi_base;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);
	dbi_base = pp->dbi_base;

	kirin_pcie_writel_rc(pp, PCIE_ATU_REGION_INBOUND | (u32)index,
			  dbi_base + PCIE_ATU_VIEWPORT);
	kirin_pcie_writel_rc(pp, lower_32_bits(pci_addr), dbi_base + PCIE_ATU_LOWER_BASE);
	kirin_pcie_writel_rc(pp, upper_32_bits(pci_addr), dbi_base + PCIE_ATU_UPPER_BASE);
	kirin_pcie_writel_rc(pp, lower_32_bits(pci_addr + size - 1),
			  dbi_base + PCIE_ATU_LIMIT);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr), dbi_base + PCIE_ATU_LOWER_TARGET);
	kirin_pcie_writel_rc(pp, upper_32_bits(cpu_addr), dbi_base + PCIE_ATU_UPPER_TARGET);
	kirin_pcie_writel_rc(pp, type, dbi_base + PCIE_ATU_CR1);
	kirin_pcie_writel_rc(pp, PCIE_ATU_ENABLE, dbi_base + PCIE_ATU_CR2);
}

u64 g_dma_begin_time;
u64 g_dma_end_time;

struct dmatest_done {
	bool			done;
	wait_queue_head_t	*wait;
};

static void dmatest_callback(void *arg)
{
	struct dmatest_done *done = (struct dmatest_done *)arg;
	g_dma_end_time = hisi_getcurtime();
	PCIE_PR_INFO("dmatest callback, begin_time = %llu,  end_time = %llu", g_dma_begin_time, g_dma_end_time);
	done->done = true;
	wake_up_all(done->wait);
}

int rc_read_ep_by_dma(u64 addr, u32 size, u32 rc_id)
{
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(done_wait);
	dma_cap_mask_t mask;
	struct dma_chan		*chan;
	struct dma_device	*dev;
	unsigned long flags;
	enum dma_status status;
	dma_cookie_t cookie;
	struct dmatest_done	done = { .wait = &done_wait };
	struct dma_async_tx_descriptor *tx;
	u64 rc_phys_addr, ep_in_rc_cpu_phys_addr;
	u64 wait_jiffies = msecs_to_jiffies(20000);
	struct pcie_port *pp;


	pp = &g_test_kirin_pcie[rc_id].pcie->pp;

	rc_phys_addr = addr;
	ep_in_rc_cpu_phys_addr = pp->mem_base + TEST_BUS1_OFFSET;
	flags = (unsigned long)(DMA_CTRL_ACK | DMA_PREP_INTERRUPT);

	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, ep_in_rc_cpu_phys_addr,
		TEST_BUS1_OFFSET, size);

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);
	chan = dma_request_channel(mask, NULL, NULL);
	if (chan) {
		dev = chan->device;
		tx = dev->device_prep_dma_memcpy(chan, rc_phys_addr, ep_in_rc_cpu_phys_addr, size, flags);
		if (!tx) {
			PCIE_PR_ERR("tx is NULL");
			goto release_dma_channel;
		}
		done.done = false;
		tx->callback = dmatest_callback;
		tx->callback_param = &done;
		cookie = tx->tx_submit(tx);

		if (dma_submit_error(cookie)) {
			PCIE_PR_ERR("dma submit error");
			goto release_dma_channel;
		}
		g_dma_begin_time = hisi_getcurtime();
		dma_async_issue_pending(chan);
		wait_event_freezable_timeout(done_wait, done.done, wait_jiffies);
		status = dma_async_is_tx_complete(chan, cookie, NULL, NULL);
		if (status != DMA_COMPLETE) {
			PCIE_PR_ERR("dma transfer fail, dmatest_error_type = %d", status);
			goto release_dma_channel;
		}
	} else {
		PCIE_PR_ERR("no more channels available");
		return -1;
	}
	dma_release_channel(chan);
	return 0;
release_dma_channel:
	dma_release_channel(chan);
	return -1;
}

int rc_write_ep_by_dma(u64 addr, u32 size, u32 rc_id)
{
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(done_wait);
	dma_cap_mask_t mask;
	struct dma_chan		*chan;
	struct dma_device	*dev;
	unsigned long flags;
	enum dma_status status;
	dma_cookie_t cookie;
	struct dmatest_done	done = { .wait = &done_wait };
	struct dma_async_tx_descriptor *rx;
	u64 rc_phys_addr, ep_in_rc_cpu_phys_addr;
	u64 wait_jiffies = msecs_to_jiffies(20000);
	struct pcie_port *pp;

	pp = &g_test_kirin_pcie[rc_id].pcie->pp;

	rc_phys_addr = addr;
	ep_in_rc_cpu_phys_addr = pp->mem_base + TEST_BUS1_OFFSET;

	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, ep_in_rc_cpu_phys_addr,
		TEST_BUS1_OFFSET, size);

	flags = (unsigned long)(DMA_CTRL_ACK | DMA_PREP_INTERRUPT);

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);
	chan = dma_request_channel(mask, NULL, NULL);
	if (chan) {
		dev = chan->device;
		rx = dev->device_prep_dma_memcpy(chan, ep_in_rc_cpu_phys_addr, rc_phys_addr, size, flags);
		if (!rx) {
			PCIE_PR_ERR("rx is NULL");
			goto release_dma_channel;
		}
		done.done = false;
		rx->callback = dmatest_callback;
		rx->callback_param = &done;
		cookie = rx->tx_submit(rx);

		if (dma_submit_error(cookie)) {
			PCIE_PR_ERR("dma submit error");
			goto release_dma_channel;
		}
		g_dma_begin_time = hisi_getcurtime();
		dma_async_issue_pending(chan);
		wait_event_freezable_timeout(done_wait, done.done, wait_jiffies);
		status = dma_async_is_tx_complete(chan, cookie, NULL, NULL);
		if (status != DMA_COMPLETE) {
			PCIE_PR_ERR("dma transfer fail, dmatest_error_type = %d", status);
			goto release_dma_channel;
		}
	} else {
		PCIE_PR_ERR("no more channels available");
		return -1;
	}
	dma_release_channel(chan);
	return 0;
release_dma_channel:
	dma_release_channel(chan);
	return -1;
}


static void calc_rate(char* description,    /* print description */
                      u32 size,       /* transfer's block size */
                      u64 start_time,       /* transfer's start time */
                      u64 end_time)         /* transfer's end time */
{
    /* HZ: system timer interrupt number per seconds */
	u64 cost_ns = end_time - start_time;

	u64 kbyte_size = size >> 10;
	u64 mbyte_size = size >> 20;
	u64 gbyte_size = size >> 30;

	u64 kbit_rate = (cost_ns) ? (kbyte_size * 8 * 1000000000) / (cost_ns) : 0;
	u64 mbit_rate = (cost_ns) ? (mbyte_size * 8 * 1000000000) / (cost_ns) : 0;
	u64 gbit_rate = (cost_ns) ? (mbyte_size * 8 * 1000000) / (cost_ns) : 0;

	printk(KERN_ALERT"%s total size: %llu MB(%llu GB)(%llu KB), cost times: %llu ns, rate:%llu Mb/s(%llu Gb/s)(%llu Kb/s)\n",
		description, mbyte_size, gbyte_size, kbyte_size, cost_ns, mbit_rate, gbit_rate, kbit_rate);
}

int dma_trans_rate(u32 rc_id, int direction, u32 size, u64 addr)
{
	struct kirin_pcie *kirin_pcie;
	int ret = 0;
	void __iomem *dbi_base;

	g_dma_begin_time = 0;
	g_dma_end_time = 0;
	if (rc_id >= MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_id);
		return -1;
	}
	kirin_pcie = &g_kirin_pcie[rc_id];
	if (!kirin_pcie->is_power_on) {
		PCIE_PR_ERR("PCIe No.%d is power off", rc_id);
		return -1;
	}

	dbi_base = ioremap(kirin_pcie->pp.mem_base, 0x2000);
	test_enable_dbi(rc_id, 1);
	writel(0xfffffff, dbi_base + 0x1010);
	test_enable_dbi(rc_id, 0);

	switch (direction) {
		case 0: {
			ret = rc_read_ep_by_dma(addr, size, rc_id);
			if (ret) {
				PCIE_PR_ERR("RC read EP by DMA  fail\n");
				return -1;
			}
			calc_rate ("EP_TO_RC_BY_DMA rate :", size, g_dma_begin_time, g_dma_end_time);
			break;
		}
		case 1: {
			ret = rc_write_ep_by_dma(addr, size, rc_id);
			if (ret) {
				PCIE_PR_ERR("RC write EP by DMA  fail\n");
				return -1;
			}
			calc_rate ("RC_TO_EP_BY_DMA rate :", size, g_dma_begin_time, g_dma_end_time);
			break;
		}
		default:
			PCIE_PR_ERR("input param is wrong");
			return -1;
	}
	return 0;
}




void rc_read_ep_cfg(u32 rc_id)
{
	unsigned int index;
	u64 ep_vaddr_in_cpu;
	u64 busdev;
	struct pci_dev *ep_dev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	ep_dev = test_kirin_pcie->pcie->ep_dev;

	if (ep_dev == NULL) {
		PCIE_PR_ERR("Failed to get EP Device");
		return;
	}

	busdev = TEST_BUS1_OFFSET;
	ep_vaddr_in_cpu = pci_resource_start(ep_dev, 0);

	PCIE_PR_INFO("ep addr in cpu physical is [0x%llx]", ep_vaddr_in_cpu);
	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_CFG0, ep_vaddr_in_cpu, busdev, 0x1000);
	ep_vaddr_in_cpu = (__force u64)ioremap(ep_vaddr_in_cpu, 0x1000);
	PCIE_PR_INFO("ep addr in cpu virtual is [0x%llx]", ep_vaddr_in_cpu);

	test_enable_dbi(rc_id, DISABLE);
	for (index = 0; index < 0x100; index += 4)
		PCIE_PR_INFO("cfg register: offset[%d] = [0x%x]", index, readl((void *)ep_vaddr_in_cpu + index));
	iounmap((void __iomem *)ep_vaddr_in_cpu);
}

int rc_read_ep_mem(u32 rc_id)
{
	unsigned int index;
	u64 cpu_addr;
	u64 begin_time;
	u64 end_time;
	int ret;
	char *temp_memcmp;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	cpu_addr = test_kirin_pcie->pcie->pp.mem_base + TEST_BUS1_OFFSET;
	PCIE_PR_INFO("ep addr in cpu physical is [0x%llx], size is [0x%x]", cpu_addr, TEST_MEM_SIZE);

	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, cpu_addr, TEST_BUS1_OFFSET, TEST_MEM_SIZE);

	cpu_addr = (__force u64)ioremap(cpu_addr, TEST_MEM_SIZE);
	if (!cpu_addr) {
		PCIE_PR_ERR("cpu addr ioremap fail");
		return -1;
	}

	temp_memcmp = (char *)kmalloc(TEST_MEM_SIZE, GFP_KERNEL);
	if (!temp_memcmp) {
		PCIE_PR_ERR("alloc temp_memcmp fail\n");
		iounmap((void __iomem *)cpu_addr);
		return -1;
	}
	memset(temp_memcmp, 0xff, TEST_MEM_SIZE);

	PCIE_PR_INFO("Reading from EP mem");
	begin_time = jiffies;

	for (index = 0; index < TRANSFER_TIMES; index++)
		memcpy((void *)test_kirin_pcie->rc_mem_addr, (void *)cpu_addr, TEST_MEM_SIZE);

	end_time = jiffies;
	show_trans_rate(begin_time, end_time, TEST_MEM_SIZE);

	if (memcmp((void *)test_kirin_pcie->rc_mem_addr, (void *)cpu_addr, TEST_MEM_SIZE) != 0 ||
		memcmp((void *)test_kirin_pcie->rc_mem_addr, temp_memcmp, TEST_MEM_SIZE) == 0)
		ret = -1;
	else
		ret = 0;

	iounmap((void __iomem *)cpu_addr);
	kfree(temp_memcmp);

	return ret;
}

/**
** RC springs data-transfer between RC and EP
**/
void set_ep_mem_inbound(u32 rc_id)
{
	u64 busdev, cpu_addr, temp_addr;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	set_bme(rc_id, ENABLE);
	set_mse(rc_id, ENABLE);
	busdev = TEST_BUS1_OFFSET;

	temp_addr = virt_to_phys((void *)test_kirin_pcie->ep_mem_addr);
	cpu_addr = test_kirin_pcie->ep_mem_addr;

	PCIE_PR_INFO("inbound pci_add [0x%llx] to cpu_addr[0x%llx]", busdev, temp_addr);
	kirin_pcie_inbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, temp_addr, busdev, TEST_MEM_SIZE);

	memset((void *)cpu_addr, 0xaa, TEST_MEM_SIZE);/* [false alarm]:fortify */

}

void read_ep_addr(u32 rc_id)
{
	u32 index;
	u32 val;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	if (test_kirin_pcie->ep_mem_addr)
		for (index = 0; index < 0x100; index += 4) {
			val = readl((void *)test_kirin_pcie->ep_mem_addr + index);
			PCIE_PR_INFO("index[0x%x], value=[0x%x]", index, val);
		}
}

int rc_write_ep_mem(u32 rc_id, unsigned int size)
{
	u64 cpu_addr;
	u64 begin_time;
	u64 end_time;
	int index;
	int ret;
	char *temp_memcmp;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	memset((void *)test_kirin_pcie->rc_mem_addr, 0xef, TEST_MEM_SIZE);

	if (size > TEST_MEM_SIZE || size == 0)
		size = TEST_MEM_SIZE;

	cpu_addr = test_kirin_pcie->pcie->pp.mem_base + TEST_BUS1_OFFSET;

	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, cpu_addr, TEST_BUS1_OFFSET, TEST_MEM_SIZE);

	cpu_addr = (__force u64)ioremap_nocache(cpu_addr, TEST_MEM_SIZE);
	if (!cpu_addr) {
		PCIE_PR_ERR("cpu addr ioremap fail");
		return -1;
	}

	temp_memcmp = (char *)kmalloc(size, GFP_KERNEL);
	if (!temp_memcmp) {
		PCIE_PR_ERR("alloc temp_memcmp fail\n");
		iounmap((void __iomem *)cpu_addr);
		return -1;
	}
	memset(temp_memcmp, 0xff, size);

	PCIE_PR_INFO("Writing 0xef to EP mem");

	begin_time = jiffies;

	for (index = 0; index < TRANSFER_TIMES; index++)
		memcpy((void *)cpu_addr, (void *)test_kirin_pcie->rc_mem_addr, size);

	end_time = jiffies;

	show_trans_rate(begin_time, end_time, size);

	if (memcmp((void *)test_kirin_pcie->rc_mem_addr, (void *)cpu_addr, size) != 0 ||
		memcmp((void *)cpu_addr, temp_memcmp, size) == 0)
		ret = -1;
	else
		ret = 0;

	iounmap((void __iomem *)cpu_addr);
	kfree(temp_memcmp);
	return ret;
}
int data_trans_ok(u32 rc_id)
{
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	if (memcmp((void *)test_kirin_pcie->ep_mem_addr, (void *)test_kirin_pcie->rc_mem_addr, TEST_MEM_SIZE) != 0)
		return -1;
	else
		return 0;
}
/**
** EP springs data-transfer between RC and EP
**/
void set_rc_mem_inbound(u32 rc_id)
{
	unsigned int index;
	u64 busdev, cpu_addr, temp_addr;
	u32 val;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	set_bme(rc_id, ENABLE);
	set_mse(rc_id, ENABLE);
	busdev = TEST_BUS0_OFFSET;

	temp_addr = virt_to_phys((void *)test_kirin_pcie->rc_mem_addr);
	cpu_addr = test_kirin_pcie->rc_mem_addr;

	PCIE_PR_INFO("inbound pci_add [0x%llx] to cpu_addr[0x%llx]", busdev, temp_addr);
	kirin_pcie_inbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, temp_addr, busdev, TEST_MEM_SIZE);

	memset((void *)cpu_addr, 0xbb, TEST_MEM_SIZE);

	for (index = 0; index < 0x100; index += 4) {
		val = readl((char *)cpu_addr+index);
		PCIE_PR_INFO("offset[0x%x], value=[0x%x]", index, val);
	}
}


void read_rc_addr(u32 rc_id)
{
	u32 index;
	u32 val;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	if (test_kirin_pcie->rc_mem_addr)
		for (index = 0; index < 0x100; index += 4) {
			val = readl((void *)test_kirin_pcie->rc_mem_addr+index);
			PCIE_PR_INFO("offset[0x%x], value=[0x%x]", index, val);
		}
}

int ep_read_rc_mem(u32 rc_id)
{
	u64 cpu_addr;
	u32 index;
	u64 begin_time;
	u64 end_time;
	int ret;
	char *temp_memcmp;
	struct resource *dbi;
	struct platform_device *pdev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pdev = to_platform_device(test_kirin_pcie->pcie->pp.dev);
	dbi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	if (!dbi) {
		PCIE_PR_ERR("Can't get dbi base");
		return -1;
	}

	cpu_addr = dbi->start + TEST_BUS0_OFFSET;
	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, cpu_addr, TEST_BUS0_OFFSET, TEST_MEM_SIZE);

	cpu_addr = (__force u64)ioremap(cpu_addr, TEST_MEM_SIZE);
	if (!cpu_addr) {
		PCIE_PR_ERR("cpu addr ioremap fail");
		return -1;
	}

	temp_memcmp = (char *)kmalloc(TEST_MEM_SIZE, GFP_KERNEL);
	if (!temp_memcmp) {
		PCIE_PR_ERR("alloc temp_memcmp fail\n");
		iounmap((void __iomem *)cpu_addr);
		return -1;
	}
	memset(temp_memcmp, 0xff, TEST_MEM_SIZE);

	PCIE_PR_INFO("Reading from RX mem");
	begin_time = jiffies;

	memset((void *)test_kirin_pcie->ep_mem_addr, 0xbc, TEST_MEM_SIZE);
	for (index = 0; index < TRANSFER_TIMES; index++)
		memcpy((void *)test_kirin_pcie->ep_mem_addr, (void *)cpu_addr, TEST_MEM_SIZE);

	end_time = jiffies;

	show_trans_rate(begin_time, end_time, TEST_MEM_SIZE);

	if (memcmp((void *)test_kirin_pcie->ep_mem_addr, (void *)cpu_addr, TEST_MEM_SIZE) != 0 ||
		memcmp((void *)test_kirin_pcie->ep_mem_addr, temp_memcmp, TEST_MEM_SIZE) == 0)
		ret = -1;
	else
		ret = 0;

	iounmap((void __iomem *)cpu_addr);
	kfree(temp_memcmp);
	return ret;
}

int ep_write_rc_mem(u32 rc_id, unsigned int size)
{
	u64 cpu_addr;
	u64 begin_time;
	u64 end_time;
	int index;
	int ret;
	char *temp_memcmp;
	struct resource *dbi;
	struct platform_device *pdev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	if (size > TEST_MEM_SIZE || size <= 0)
		size = TEST_MEM_SIZE;

	pdev = to_platform_device(test_kirin_pcie->pcie->pp.dev);
	dbi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	if (!dbi) {
		PCIE_PR_ERR("Can't get dbi base");
		return -1;
	}

	cpu_addr = dbi->start + TEST_BUS0_OFFSET;

	kirin_pcie_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, cpu_addr, TEST_BUS0_OFFSET, TEST_MEM_SIZE);

	cpu_addr = (__force u64)ioremap_nocache(cpu_addr, TEST_MEM_SIZE);
	if (!cpu_addr) {
		PCIE_PR_ERR("cpu addr ioremap fail");
		return -1;
	}

	temp_memcmp = (char *)kmalloc(size, GFP_KERNEL);
	if (!temp_memcmp) {
		PCIE_PR_ERR("alloc temp_memcmp fail\n");
		iounmap((void __iomem *)cpu_addr);
		return -1;
	}
	memset(temp_memcmp, 0xff, size);

	PCIE_PR_INFO("Writing 0xbc to RC mem");

	begin_time = jiffies;
	memset((void *)test_kirin_pcie->ep_mem_addr, 0xbc, size);

	for (index = 0; index < TRANSFER_TIMES; index++)
		memcpy((void *)cpu_addr, (void *)test_kirin_pcie->ep_mem_addr, size);

	end_time = jiffies;

	show_trans_rate(begin_time, end_time, size);
	if (memcmp((void *)test_kirin_pcie->ep_mem_addr, (void *)cpu_addr, size) != 0 ||
		memcmp((void *)cpu_addr, temp_memcmp, size) == 0)
		ret = -1;
	else
		ret = 0;

	iounmap((void __iomem *)cpu_addr);
	kfree(temp_memcmp);
	return ret;
}


void ltssm_enable(u32 rc_id, int yes)
{
	u32 val;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	if (yes) {
		val = kirin_elb_readl(pcie,  SOC_PCIECTRL_CTRL7_ADDR);
		val |= PCIE_LTSSM_ENABLE_BIT;
		kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL7_ADDR);
	} else {
		val = kirin_elb_readl(pcie,  SOC_PCIECTRL_CTRL7_ADDR);
		val &= ~PCIE_LTSSM_ENABLE_BIT;
		kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL7_ADDR);
	}
}
int test_compliance(u32 rc_id, u32 entry)
{
	u32 val;
	struct pci_dev *rc_dev;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	rc_dev = test_kirin_pcie->pcie->rc_dev;
	if (!rc_dev) {
		PCIE_PR_ERR("Failed to get RC Device");
		return -1;
	}
	pcie_capability_read_dword(rc_dev, PCI_EXP_LNKCTL2, &val);
	if (entry)
		val |= ENTER_COMPLIANCE;
	else
		val &= ~ENTER_COMPLIANCE;
	pcie_capability_write_dword(rc_dev, PCI_EXP_LNKCTL2, val);

	ltssm_enable(rc_id, DISABLE);
	ltssm_enable(rc_id, ENABLE);

	show_link_state(rc_id);
	return 0;
}

void test_wlan_on(u32 rc_id, int on)
{
	int ret;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	ret = gpio_request(test_kirin_pcie->wl_power, "wl_on");
	if (ret < 0) {
		PCIE_PR_ERR("Can't request gpio");
		return;
	}
	if (on) {
		PCIE_PR_INFO("Power on Wlan");
		gpio_direction_output(test_kirin_pcie->wl_power, 1);
	} else {
		PCIE_PR_INFO("Power down Wlan");
		gpio_direction_output(test_kirin_pcie->wl_power, 0);
	}
	gpio_free(test_kirin_pcie->wl_power);
}
void test_entry_loopback(u32 rc_id, u32 local)
{
	u32 val;
	struct pcie_port *pp;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);

	kirin_pcie_rd_own_conf(pp, PORT_LINK_CTRL_REG, 4, &val);
	val |= (0x1 << 2);
	kirin_pcie_wr_own_conf(pp, PORT_LINK_CTRL_REG, 4, val);

	if (local) {
		kirin_pcie_rd_own_conf(pp, PORT_GEN3_CTRL_REG, 4, &val);
		val |= (0x1 << 16);
		kirin_pcie_wr_own_conf(pp, PORT_GEN3_CTRL_REG, 4, val);

		kirin_pcie_rd_own_conf(pp, PORT_PIPE_LOOPBACK_REG, 4, &val);
		val |= (0x1 << 31);
		kirin_pcie_wr_own_conf(pp, PORT_PIPE_LOOPBACK_REG, 4, val);
	}

}

void test_exit_loopback(u32 rc_id, u32 local)
{
	u32 val;
	struct pcie_port *pp;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);

	kirin_pcie_rd_own_conf(pp, PORT_LINK_CTRL_REG, 4, &val);
	val &= ~(0x1 << 2);
	kirin_pcie_wr_own_conf(pp, PORT_LINK_CTRL_REG, 4, val);

	if (local) {
		kirin_pcie_rd_own_conf(pp, PORT_GEN3_CTRL_REG, 4, &val);
		val &= ~(0x1 << 16);
		kirin_pcie_wr_own_conf(pp, PORT_GEN3_CTRL_REG, 4, val);

		kirin_pcie_rd_own_conf(pp, PORT_PIPE_LOOPBACK_REG, 4, &val);
		val &= ~(0x1 << 31);
		kirin_pcie_wr_own_conf(pp, PORT_PIPE_LOOPBACK_REG, 4, val);
	}

}


void ep_triggle_intr(u32 rc_id)
{
	u32 value_temp;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	value_temp = kirin_elb_readl(pcie, 0x8);
	value_temp |= (0x1 << 26);
	kirin_elb_writel(pcie, value_temp, 0x8);
	udelay(2);

	value_temp &= ~(0x1 << 26);
	kirin_elb_writel(pcie, value_temp, 0x8);
	PCIE_PR_INFO("read after write, ctl2 is %x", kirin_elb_readl(pcie, 0x8));
	PCIE_PR_INFO("ep_triggle_msi_intr ");
}

void config_ep_msi(u32 rc_id)
{
	u16 val;
	int pm;
	struct pci_dev *ep_dev;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	ep_dev = pcie->ep_dev;

	pm = pci_find_capability(ep_dev, PCI_CAP_ID_MSI);
	if (!pm) {
		PCIE_PR_ERR("Failed to get ep PCI Express capability !");
		return;
	}
	pci_write_config_dword(ep_dev, pm + PCI_MSI_ADDRESS_LO, 0xffff0000);
	pci_write_config_dword(ep_dev, pm + PCI_MSI_ADDRESS_HI, 0xffff0000);
	pci_write_config_dword(ep_dev, pm + PCI_MSI_DATA_64, 0x0);
	pci_read_config_word(ep_dev, pm + PCI_MSI_FLAGS, &val);
	val |= PCI_MSI_FLAGS_ENABLE;
	pci_write_config_word(ep_dev, pm + PCI_MSI_FLAGS, val);
	PCIE_PR_INFO("config ep msi ***");
}
void config_rc_msi(u32 rc_id)
{
	struct pci_dev *rc_dev;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	rc_dev = pcie->rc_dev;

	pci_write_config_dword(rc_dev, PORT_MSI_CTRL_ADDR, 0xffff0000);
	pci_write_config_dword(rc_dev, PORT_MSI_CTRL_UPPER_ADDR, 0xffff0000);
	pci_write_config_dword(rc_dev, PORT_MSI_CTRL_INT0_ENABLE, ENABLE);
	PCIE_PR_INFO("config rc msi ***");
}

void ep_triggle_intA_intr(u32 rc_id)
{
	u32 value_temp;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	value_temp = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	value_temp |= (0x1 << 5);
	kirin_elb_writel(pcie, value_temp, SOC_PCIECTRL_CTRL7_ADDR);

	value_temp = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	PCIE_PR_INFO("read after write, ctl7 is %x", value_temp);
	PCIE_PR_INFO("ep_triggle_inta_intr");
}

void ep_clr_intA_intr(u32 rc_id)
{
	u32 value_temp;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	value_temp = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	value_temp &= ~(0x1 << 5);
	kirin_elb_writel(pcie, value_temp, SOC_PCIECTRL_CTRL7_ADDR);

	value_temp = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL7_ADDR);
	PCIE_PR_INFO("read after write, ctl7 is %x", value_temp);
	PCIE_PR_INFO("ep_clr_inta_intr");
}

void msg_pcie_prog_outbound_atu(u32 rc_id, int index,
				u64 cpu_addr, u64 pci_addr, u32 size, u32 ctl2)
{
	struct pcie_port *pp;
	void __iomem *dbi_base;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);
	dbi_base = pp->dbi_base;
	kirin_pcie_writel_rc(pp, PCIE_ATU_REGION_OUTBOUND | (u32)index,
						  dbi_base + PCIE_ATU_VIEWPORT);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr), dbi_base + PCIE_ATU_LOWER_BASE);
	kirin_pcie_writel_rc(pp, upper_32_bits(cpu_addr), dbi_base + PCIE_ATU_UPPER_BASE);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr + size - 1),
					  dbi_base + PCIE_ATU_LIMIT);
	kirin_pcie_writel_rc(pp, lower_32_bits(pci_addr), dbi_base + PCIE_ATU_LOWER_TARGET);
	kirin_pcie_writel_rc(pp, upper_32_bits(pci_addr), dbi_base + PCIE_ATU_UPPER_TARGET);
	kirin_pcie_writel_rc(pp, PCIE_ATU_TYPE_MSG, dbi_base + PCIE_ATU_CR1);
	kirin_pcie_writel_rc(pp, ctl2, dbi_base + PCIE_ATU_CR2);
}
void msg_pcie_prog_inbound_atu(u32 rc_id, int index,
				u64 cpu_addr, u64 pci_addr, u32 size, u32 ctl2)
{
	struct pcie_port *pp;
	void __iomem *dbi_base;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pp = &(test_kirin_pcie->pcie->pp);
	dbi_base = pp->dbi_base;
	kirin_pcie_writel_rc(pp, PCIE_ATU_REGION_INBOUND | (u32)index,
						  dbi_base + PCIE_ATU_VIEWPORT);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr), dbi_base + PCIE_ATU_LOWER_BASE);
	kirin_pcie_writel_rc(pp, upper_32_bits(cpu_addr), dbi_base + PCIE_ATU_UPPER_BASE);
	kirin_pcie_writel_rc(pp, lower_32_bits(cpu_addr + size - 1),
					  dbi_base + PCIE_ATU_LIMIT);
	kirin_pcie_writel_rc(pp, lower_32_bits(pci_addr), dbi_base + PCIE_ATU_LOWER_TARGET);
	kirin_pcie_writel_rc(pp, upper_32_bits(pci_addr), dbi_base + PCIE_ATU_UPPER_TARGET);
	kirin_pcie_writel_rc(pp, PCIE_ATU_TYPE_MSG, dbi_base + PCIE_ATU_CR1);
	kirin_pcie_writel_rc(pp, ctl2, dbi_base + PCIE_ATU_CR2);
}

/*msg test */
void generate_msg(u32 rc_id, int msg_code)
{
	u64 cpu_addr;
	struct pcie_test_st *test_kirin_pcie;
	struct resource *dbi;
	struct platform_device *pdev;;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pdev = to_platform_device(test_kirin_pcie->pcie->pp.dev);
	dbi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	if (!dbi) {
		PCIE_PR_ERR("Can't get dbi base");
		return;
	}

	cpu_addr = dbi->start + TEST_BUS0_OFFSET;

	PCIE_PR_ERR("cpu_addr = 0x%llx", cpu_addr);
	msg_code += 0x80400000;
	msg_pcie_prog_outbound_atu(rc_id, PCIE_ATU_REGION_INDEX0, cpu_addr,
		TEST_BUS1_OFFSET, TEST_BUS1_OFFSET, msg_code);
	cpu_addr = (__force u64)ioremap(cpu_addr, 0x1000);
	if (!cpu_addr) {
		PCIE_PR_ERR("cpu_addr is NULL");
		return;
	}
	writel(0x0, (void *)cpu_addr);
	iounmap((void __iomem *)cpu_addr);
}
void msg_triggle_clr(u32 rc_id, u32 offset, u32 bit)
{
	u32 value_temp;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;

	value_temp = kirin_elb_readl(pcie, offset);
	value_temp &= ~(0x1 << bit);
	kirin_elb_writel(pcie, value_temp, offset);
	value_temp |= (0x1 << bit);
	kirin_elb_writel(pcie, value_temp, offset);
}

int msg_received(u32 rc_id, u32 offset, u32 bit)
{
	u32 value_temp;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;
	value_temp = kirin_elb_readl(pcie, offset);
	if (value_temp & (0x1 << bit)) 
		return 1;
	else 
		return 0;
}

void pcie_enable_msg_num(u32 rc_id, int num, int local)
{
	u32 val;
	struct pci_dev *dev;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	pcie = test_kirin_pcie->pcie;

	if (local)
		dev = pcie->rc_dev;
	else
		dev = pcie->ep_dev;

	pcie_capability_read_dword(dev, PCI_EXP_DEVCTL2, &val);

	switch (num) {
	case 13:
		PCIE_PR_INFO("enable obff message");
		val |= PCI_EXP_DEVCTL2_OBFF_MSGA_EN;
		pcie_capability_write_dword(dev, PCI_EXP_DEVCTL2, val);
		break;
	case 10:
		PCIE_PR_INFO("enable LTR message");
		val |= PCI_EXP_DEVCTL2_LTR_EN;
		pcie_capability_write_dword(dev, PCI_EXP_DEVCTL2, val);
		break;
	default:
		PCIE_PR_INFO("unsupport function");
		break;
	}

}

void test_get_ep_dev(u32 rc_id, u32 ep_venid, u32 ep_devid, u32 wifi_flag)
{
	struct pcie_test_st *test_kirin_pcie;
	struct pci_dev *rc_dev;

	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	rc_dev = test_kirin_pcie->pcie->rc_dev;
	if (wifi_flag)
		test_kirin_pcie->is_ep_wifi = 1;
	else
		test_kirin_pcie->is_ep_wifi = 0;

	test_kirin_pcie->pcie->ep_dev = pci_get_device(ep_venid, ep_devid, rc_dev);
	if (!test_kirin_pcie->pcie->ep_dev) {
		PCIE_PR_ERR("Failed to get EP Device");
		return;
	}
}

int kirin_pcie_test_init(u32 rc_id)
{
	struct device_node *np;
	struct kirin_pcie *pcie;
	struct pcie_test_st *test_kirin_pcie;

	if (rc_id >= MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_id);
		return -EINVAL;
	}
	pcie = &g_kirin_pcie[rc_id];
	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	test_kirin_pcie->pcie = pcie;
	test_kirin_pcie->rc_mem_addr = __get_free_pages(GFP_KERNEL, 10);
	test_kirin_pcie->ep_mem_addr = __get_free_pages(GFP_KERNEL, 10);
	if (!test_kirin_pcie->rc_mem_addr || !test_kirin_pcie->ep_mem_addr) {
		PCIE_PR_ERR("Failed to alloc ep or rc mem_space ");
		return -EINVAL;
	}

	np = pcie->pp.dev->of_node;
	if (np) {
		if (of_property_read_u32(np, "wl_power", &test_kirin_pcie->wl_power)) {
			PCIE_PR_ERR("Can't find wl_power dts property");
			return -EINVAL;
		}
		PCIE_PR_INFO("WL Power On Number is [%d] ", test_kirin_pcie->wl_power);
	} else {
		PCIE_PR_INFO("can not find kirin-pcie\n");
		return -EINVAL;
	}
	return 0;
}

int kirin_pcie_test_exist(u32 rc_id)
{
	struct pcie_test_st *test_kirin_pcie;

	if (rc_id >= MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_id);
		return -EINVAL;
	}
	test_kirin_pcie = &g_test_kirin_pcie[rc_id];
	if (test_kirin_pcie->rc_mem_addr) {
		free_page(test_kirin_pcie->rc_mem_addr);
		test_kirin_pcie->rc_mem_addr = 0;
	}
	if (test_kirin_pcie->ep_mem_addr) {
		free_page(test_kirin_pcie->ep_mem_addr);
		test_kirin_pcie->ep_mem_addr = 0;
	}
	test_kirin_pcie->pcie = NULL;
	test_kirin_pcie->wl_power = 0;
	return 0;
}
/*lint -e438 -e529 -e550 -e774 -e838 +esym(438,*) +esym(529,*) +esym(550,*) +esym(774,*) +esym(838,*) */
MODULE_DESCRIPTION("Hisilicon Kirin pcie driver");
MODULE_LICENSE("GPL");


