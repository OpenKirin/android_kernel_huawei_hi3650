#include "pcie-auto-test.h"
/*lint -e438 -e529 -e550 -e838 -esym(438,*) -esym(529,*) -esym(550,*) -esym(838,*) */
static void auto_pcie_outbound_atu(int index, int type, u64 cpu_addr, u64 pci_addr, u32 size, struct pcie_port *pp);
enum auto_test_result {
	AUTO_TEST_OK,
	FAIL_L0S,
	FAIL_L1,
	FAIL_L0_L1,
	FAIL_L1_1,
	FAIL_L1_2,
};

struct pcie_info {
	struct pci_dev *rc_dev;
	struct pci_dev *ep_dev;

	u32 buffer_size;
	u64 rc_phys_addr;	/* RC buffer's CPU physical address */
	void *rc_virt_addr;

	u64 ep_in_rc_cpu_phys_addr;       /* EP buffer's PCI physical address (CPU domain) */
	void* ep_in_rc_cpu_virt_addr;
};

struct pcie_info g_pcie_info[] = {
	{
		.buffer_size = WIFI_RW_MEMORY_SIZE,
	},
	{
		.buffer_size = WIFI_RW_MEMORY_SIZE,
	},
};
char *temp_memcmp;

static u32 g_pcie_stress_test_sleep_ms;
static u32 g_pcie_stress_test_run_current_count;
static u32 g_pcie_stress_test_run_max_count;
static u32 g_pcie_stress_test_task_running;
static volatile u32 g_pcie_stree_test_mode = (PCIE_STRESS_TEST_MODE_CPU_READ |
										PCIE_STRESS_TEST_MODE_CPU_WRITE);

static int auto_test_wlan_on(u32 rc_id, int on)
{
	struct device_node *np;
	struct kirin_pcie *pcie;
	u32 wl_power = 0;
	int ret;

	pcie = &g_kirin_pcie[rc_id];
	if (!pcie->pp.dev) {
		PCIE_PR_ERR("PCIe No.%d do not work", rc_id);
		return -1;
	}
	np =pcie->pp.dev->of_node;
	if (np) {
		if (!(of_property_read_u32(np, "wl_power", &wl_power))) {
			PCIE_PR_INFO("WL Power On Number is [%d] ", wl_power);
		} else {
			PCIE_PR_INFO("dts has no member as wl_power");
			return -1;
		}
	} else {
		PCIE_PR_INFO("can not find kirin-pcie dts node\n");
		return -1;
	}

	ret = gpio_request(wl_power, "auto_test_wlan_on");
	if (ret < 0)
		PCIE_PR_ERR("Can't request gpio");
	if (on) {
		PCIE_PR_INFO("Power on Wlan");
		gpio_direction_output(wl_power, 1);
	} else {
		PCIE_PR_INFO("Power down Wlan");
		gpio_direction_output(wl_power, 0);
	}
	if (!ret)
		gpio_free(wl_power);

	return 0;

}

static void auto_test_config_aspm_l0s_l1(enum link_aspm_state aspm_state, u32  rc_id)
{
	struct pci_dev *rc_dev;
	struct pci_dev *ep_dev;

	rc_dev = g_pcie_info[rc_id].rc_dev;
	ep_dev = g_pcie_info[rc_id].ep_dev;
	if (ep_dev == NULL || rc_dev == NULL) {
		PCIE_PR_ERR("Failed to get PCI Device");
		return;
	}

	pcie_capability_clear_and_set_word(rc_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_ASPMC, aspm_state);
	pcie_capability_clear_and_set_word(ep_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_ASPMC, aspm_state);
}

int check_lowpower_state(int mode, u32 status4, u32 status5)
{
	int wait_condition = -1;

	switch (mode) {
	case L0S_MODE:
		if ((status4 & 0x3f) == 0x12)
			wait_condition = 0;
		break;
	case L1_MODE:
		if ((status4 & 0x3f) == 0x14)
			wait_condition = 0;
		break;
	case L1_1_MODE:
		if (((status5 & BIT(15)) == 0) && ((status5 & BIT(14)) == BIT(14)))
			wait_condition = 0;
		break;
	case L1_2_MODE:
		if (((status5 & BIT(15)) == BIT(15)) && ((status5 & BIT(14)) == BIT(14)))
			wait_condition = 0;
		break;
	case L0_MODE:
		if ((status4 & 0x3f) == 0x11)
			wait_condition = 0;
		break;
	default:
		PCIE_PR_ERR("unknown lowpower mode\n");
		break;
	}
	return wait_condition;
}
int check_test_state(int mode, u32 status4)
{
	int wait_condition = -1;

	switch (mode) {
	case LOOPBACK_MODE:
		if ((status4 & 0x3f) == 0x1B)
			wait_condition = 0;
		break;
	case COMPLIANCE_MODE:
		if ((status4 & 0x3f) == 0x3)
			wait_condition = 0;
		break;
	default:
		PCIE_PR_ERR("unknown test mode\n");
		break;
	}
	return wait_condition;
}

int check_status(int mode, u32 status4, u32 status5)
{
	if (mode <= LINK_LOWPWR)
		return check_lowpower_state(mode, status4, status5);
	else
		return check_test_state(mode, status4);
}

/* auto_test_wait_for_power_status - wait for link Entry pcie spec mode
 * @mode: pcie mode index
*/
int auto_test_wait_for_power_status(int mode, u32 rc_id)
{
	u32 status4;
	u32 status5;
	unsigned long prev_jffy;

	prev_jffy = jiffies;
	while (!(time_after(jiffies, prev_jffy + HZ / 5))) {
		status4 = kirin_elb_readl(&g_kirin_pcie[rc_id], SOC_PCIECTRL_STATE4_ADDR);
		status5 = kirin_elb_readl(&g_kirin_pcie[rc_id], SOC_PCIECTRL_STATE5_ADDR);
		if (!check_status(mode, status4, status5))
			return 0;
		msleep(20);
	}
	return -1;
}


/**
* slt_enable_l1ss - config l1ss link state;
*/
void auto_test_enable_l1ss(unsigned int flag, u32 rc_id)
{
	unsigned int rc_val = 0;
	unsigned int ep_val = 0;
	int pm;
	int ret;
	struct pci_dev *ep_dev = g_pcie_info[rc_id].ep_dev;
	struct pci_dev *rc_dev = g_pcie_info[rc_id].rc_dev;
	struct kirin_pcie *pcie = &g_kirin_pcie[rc_id];

	auto_test_config_aspm_l0s_l1(ASPM_L1, rc_id);

	if (ep_dev == NULL || rc_dev == NULL) {
		PCIE_PR_ERR("Failed to get PCI Device");
		return;
	}

	pci_read_config_dword(rc_dev, 0x168, &rc_val);
	rc_val &= ~(0x3 << 2);
	rc_val |= flag;
	pci_write_config_dword(rc_dev, 0x168, rc_val);

	pm = pci_find_capability(rc_dev, PCI_CAP_ID_EXP);
	if (pm) {
		pci_read_config_dword(rc_dev, pm + 0x28, &rc_val);
		rc_val |= (0x1 << 10);
		pci_write_config_dword(rc_dev, pm + 0x28, rc_val);
	}

	ret = readl(pcie->apb_base + SOC_PCIECTRL_CTRL7_ADDR);
	ret = ret | (0x1<<10);
	writel(ret, pcie->apb_base + SOC_PCIECTRL_CTRL7_ADDR);

	ret = readl(pcie->apb_base + SOC_PCIECTRL_CTRL8_ADDR);
	ret = ret | (0x1<<3);
	writel(ret, pcie->apb_base + SOC_PCIECTRL_CTRL8_ADDR);

	pci_read_config_dword(ep_dev, 0x248, &ep_val);
	ep_val &= ~(0x3 << 2);
	ep_val |= flag;
	pci_write_config_dword(ep_dev, 0x248, ep_val);

	pci_read_config_dword(ep_dev, 0x24c, &ep_val);
	ep_val &= ~0xFF;
	ep_val |= 0x61;
	pci_write_config_dword(ep_dev, 0x24c, ep_val);

	pci_read_config_dword(ep_dev, 0xD4, &ep_val);
	ep_val |= 0x1 << 10;
	pci_write_config_dword(ep_dev, 0xD4, ep_val);
	pci_write_config_dword(ep_dev, 0x1B4, 0x10031003);

	ret = readl(pcie->apb_base + SOC_PCIECTRL_CTRL1_ADDR);
	ret |= (0x1<<23);
	writel(ret, pcie->apb_base + SOC_PCIECTRL_CTRL1_ADDR);

	mdelay(10);

}

int lowpower_test(u32 rc_id)
{
	int ret = AUTO_TEST_OK;
	struct kirin_pcie *pcie;

	pcie = &g_kirin_pcie[rc_id];

	if (!(g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_LOWPOWER))
		return ret;
	PCIE_PR_INFO("+++  lowpower test +++");
	auto_test_config_aspm_l0s_l1(ASPM_L0S, rc_id);
	if (auto_test_wait_for_power_status(L0S_MODE, rc_id)) {
		PCIE_PR_ERR("Enter L0s fail");
		ret = FAIL_L0S;
		return ret;
	}
	PCIE_PR_INFO("L0S test pass");
	auto_test_config_aspm_l0s_l1(ASPM_L1, rc_id);
	if (auto_test_wait_for_power_status(L1_MODE, rc_id)) {
		PCIE_PR_ERR("Enter L1 fail");
		ret = FAIL_L1;
		return ret;
	}
	PCIE_PR_INFO("L1 test pass");
	auto_test_config_aspm_l0s_l1(ASPM_L0S_L1, rc_id);
	if (auto_test_wait_for_power_status(L0S_L1_MODE, rc_id)) {
		PCIE_PR_ERR("Enter L0s_and_L1 fail");
		ret = FAIL_L0_L1;
		return ret;
	}
	PCIE_PR_INFO("L0s and L1 test pass");
	/*Return to L0*/
	auto_test_config_aspm_l0s_l1(ASPM_CLOSE, rc_id);
	writel(AUTO_TEST_RANDOM_DATA, g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr);
	/*close soft config for clk, controlled by hardware*/
	writel((0x7 << 17), pcie->sctrl_base+ SCTRL_SCPERCLKDIS2);
	writel((0x1 << 20) | (0x1 << 14), pcie->sctrl_base + SCTRL_SCPERCLKEN2);
	auto_test_enable_l1ss(L1_SUB_1_1, rc_id);
	if (auto_test_wait_for_power_status(L1_1_MODE, rc_id)) {
		PCIE_PR_ERR("Enter L1_1 fail");
		ret = FAIL_L1_1;
		return ret;
	}
	PCIE_PR_INFO("L1_1 test pass");
	auto_test_enable_l1ss(L1_SUB_1_2, rc_id);
	if (auto_test_wait_for_power_status(L1_2_MODE, rc_id)) {
		PCIE_PR_ERR("Enter L1_2 fail");
		ret = FAIL_L1_2;
		return ret;
	}
	PCIE_PR_INFO("L1_2 test pass");
	return ret;
}

static u32 get_random(u32 base, u32 scope)
{
	u32 random = 0;

	if (!scope)
		return base;
	get_random_bytes((void *)&random, (int)sizeof(random));
	random = random % scope + base;
	return random;
}

static int ep_to_rc_by_cpu(void *destination, void *source, u32 size, u32 rc_id)
{
	PCIE_PR_INFO("size is %x\n", size);
	memset(g_pcie_info[rc_id].rc_virt_addr, 0xa5, WIFI_RW_MEMORY_SIZE);
	memset_io(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, 0x5a, WIFI_RW_MEMORY_SIZE);
	memcpy_fromio(destination, source, size);
	if (memcmp(destination, source, size) != 0 || memcmp(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, temp_memcmp, size) == 0)
		return -1;
	else
		return 0;
}

static int rc_to_ep_by_cpu(void *destination, void *source, u32 size, u32 rc_id)
{
	memset(g_pcie_info[rc_id].rc_virt_addr, 0xa5, WIFI_RW_MEMORY_SIZE);
	memset_io(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, 0x5a, WIFI_RW_MEMORY_SIZE);
	memcpy_toio(destination, source, size);
	if (memcmp(destination, source, size) != 0 || memcmp(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, temp_memcmp, size) == 0)
		return -1;
	else
		return 0;
}


struct dmatest_done {
	bool			done;
	wait_queue_head_t	*wait;
};

static void dmatest_callback(void *arg)
{
	struct dmatest_done *done = (struct dmatest_done *)arg;

	PCIE_PR_INFO("dmatest callback");
	done->done = true;
	wake_up_all(done->wait);
}

int rc_to_ep_by_dma(u32 size, u32 rc_id)
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
	u64 rc_phys_addr;
	u64 wait_jiffies = msecs_to_jiffies(20000);
	void *rc_virt_addr;

	rc_virt_addr = dma_alloc_coherent(g_kirin_pcie[rc_id].pp.dev, size, &rc_phys_addr, GFP_KERNEL);
	if (!rc_virt_addr) {
		PCIE_PR_ERR("rc_virt_addr is NULL");
		return -1;
	}
	memset(rc_virt_addr, 0xaa, size);
	memset_io(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, 0xdd, size);

	flags = (unsigned long)(DMA_CTRL_ACK | DMA_PREP_INTERRUPT);

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);
	chan = dma_request_channel(mask, NULL, NULL);
	if (chan) {
		dev = chan->device;
		tx = dev->device_prep_dma_memcpy(chan, (dma_addr_t)(g_pcie_info[rc_id].ep_in_rc_cpu_phys_addr + WIFI_FIRMWARE_START),
			rc_phys_addr, size, flags);
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
		dma_async_issue_pending(chan);
		wait_event_freezable_timeout(done_wait, done.done, wait_jiffies);
		status = dma_async_is_tx_complete(chan, cookie, NULL, NULL);
		if (status != DMA_COMPLETE) {
			PCIE_PR_ERR("dma transfer fail, dmatest_error_type = %d", status);
			goto release_dma_channel;
		}
	} else {
		PCIE_PR_ERR("no more channels available");
		goto free_dma;
	}
	if (memcmp(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, rc_virt_addr, size) != 0) {
		PCIE_PR_ERR("data error");
		goto release_dma_channel;
	} else {
		dma_release_channel(chan);
		dma_free_coherent(g_kirin_pcie[rc_id].pp.dev, size, rc_virt_addr, rc_phys_addr);
		rc_virt_addr = NULL;
		return 0;
	}
release_dma_channel:
	dma_release_channel(chan);
free_dma:
	dma_free_coherent(g_kirin_pcie[rc_id].pp.dev, size, rc_virt_addr, rc_phys_addr);
	rc_virt_addr = NULL;
	return -1;
}

int ep_to_rc_by_dma(u32 size, u32 rc_id)
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
	u64 rc_phys_addr;
	u64 wait_jiffies = msecs_to_jiffies(20000);
	void *rc_virt_addr;

	rc_virt_addr = dma_alloc_coherent(g_kirin_pcie[rc_id].pp.dev, size, &rc_phys_addr, GFP_KERNEL);
	if (!rc_virt_addr) {
		PCIE_PR_ERR("rc_virt_addr is NULL");
		return -1;
	}
	memset(rc_virt_addr, 0xaa, size);
	memset_io(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, 0xdd, size);

	flags = (unsigned long)(DMA_CTRL_ACK | DMA_PREP_INTERRUPT);

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);
	chan = dma_request_channel(mask, NULL, NULL);
	if (chan) {
		dev = chan->device;
		rx = dev->device_prep_dma_memcpy(chan, rc_phys_addr,
			(dma_addr_t)(g_pcie_info[rc_id].ep_in_rc_cpu_phys_addr + WIFI_FIRMWARE_START), size, flags);
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
		dma_async_issue_pending(chan);
		wait_event_freezable_timeout(done_wait, done.done, wait_jiffies);
		status = dma_async_is_tx_complete(chan, cookie, NULL, NULL);
		if (status != DMA_COMPLETE) {
			PCIE_PR_ERR("dma transfer fail, dmatest_error_type = %d", status);
			goto release_dma_channel;
		}
	} else {
		PCIE_PR_ERR("no more channels available");
		goto free_dma;
	}
	if (memcmp(g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr, rc_virt_addr, size) != 0) {
		PCIE_PR_ERR("data error");
		goto release_dma_channel;
	} else {
		dma_release_channel(chan);
		dma_free_coherent(g_kirin_pcie[rc_id].pp.dev, size, rc_virt_addr, rc_phys_addr);
		rc_virt_addr = NULL;
		return 0;
	}
release_dma_channel:
	dma_release_channel(chan);
free_dma:
	dma_free_coherent(g_kirin_pcie[rc_id].pp.dev, size, rc_virt_addr, rc_phys_addr);
	rc_virt_addr = NULL;
	return -1;
}
static void auto_ltssm_enable(int enable, u32 rc_id)
{
	u32 val = 0;
	struct kirin_pcie *pcie = &g_kirin_pcie[rc_id];

	if (enable) {
		val = kirin_elb_readl(pcie,  SOC_PCIECTRL_CTRL7_ADDR);
		val |= (0x1 << 11);
		kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL7_ADDR);
	} else {
		val = kirin_elb_readl(pcie,  SOC_PCIECTRL_CTRL7_ADDR);
		val &= ~(0x1 << 11);
		kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL7_ADDR);
	}
}

void auto_test_entry_loopback(u32 local, u32 rc_id)
{
	struct pcie_port *pp = &g_kirin_pcie[rc_id].pp;
	u32 val = 0;

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

void auto_test_exit_loopback(u32 local, u32 rc_id)
{
	struct pcie_port *pp = &g_kirin_pcie[rc_id].pp;
	u32 val = 0;

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

int loopback_test(u32 rc_id)
{
	int ret = 0;
	struct pci_saved_state *ep_default_state;
	struct pci_saved_state *rc_default_state;
	struct pci_dev *ep_dev = g_pcie_info[rc_id].ep_dev;
	struct pci_dev *rc_dev = g_pcie_info[rc_id].rc_dev;
	struct kirin_pcie *pcie = &g_kirin_pcie[rc_id];

	if (!(g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_LOOPBACK))
		return 0;
	PCIE_PR_INFO("+++  LOOPBACK +++");
	if (rc_dev == NULL || ep_dev == NULL) {
		PCIE_PR_INFO("rc_dev is %p\tep_dev is %p\n", rc_dev, ep_dev);
		ret = PCIE_AUTO_TEST_LOOPBACK_OTHER_FAIL;
		return ret;
	}
	auto_test_config_aspm_l0s_l1(ASPM_CLOSE, rc_id);
	pci_save_state(ep_dev);
	ep_default_state = pci_store_saved_state(ep_dev);
	pci_save_state(rc_dev);
	rc_default_state = pci_store_saved_state(rc_dev);

	auto_test_entry_loopback(0, rc_id);
	if (auto_test_wait_for_power_status(LOOPBACK_MODE, rc_id)) {
		ret = PCIE_AUTO_TEST_ENTRY_FAR_LOOPBACK_FAIL;
		goto PCIE_LOOPFAIL;
	}
	auto_test_exit_loopback(0, rc_id);
	mdelay(50);
	if ((kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR) & 0x3f) != 0x11) {
		PCIE_PR_ERR("ltssm is %x", (kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR) & 0x3f));
		ret = PCIE_AUTO_TEST_EXIT_FAR_LOOPBACK_FAIL;
		goto PCIE_LOOPFAIL;
	}
	auto_test_entry_loopback(1, rc_id);
	if (auto_test_wait_for_power_status(LOOPBACK_MODE, rc_id)) {
		ret = PCIE_AUTO_TEST_ENTRY_NEAR_LOOPBACK_FAIL;
		goto PCIE_LOOPFAIL;
	}
	auto_test_exit_loopback(1, rc_id);
	mdelay(50);
	if (auto_test_wait_for_power_status(L0_MODE, rc_id)) {
		PCIE_PR_ERR("ltssm is %x", (kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR) & 0x3f));
		ret = PCIE_AUTO_TEST_EXIT_NEAR_LOOPBACK_FAIL;
		goto PCIE_LOOPFAIL;
	}
	pcie->rc_dev->msi_enabled = 0;
	pci_load_and_free_saved_state(ep_dev, &ep_default_state);
	pci_restore_state(ep_dev);
	pci_load_and_free_saved_state(rc_dev, &rc_default_state);
	pci_restore_state(rc_dev);
	pcie->rc_dev->msi_enabled = 1;

	return ret;

PCIE_LOOPFAIL:
	kfree(ep_default_state);
	ep_default_state = NULL;
	kfree(rc_default_state);
	rc_default_state = NULL;
	return ret;

}

int auto_test_entry_compliance(int entry, u32 rc_id)
{
	struct pci_dev *rc_dev = g_pcie_info[rc_id].rc_dev;
	int pm;
	u32 val = 0;

	if (!rc_dev) {
		PCIE_PR_ERR("Failed to get RC Device");
		return -1;
	}

	pm = pci_find_capability(rc_dev, PCI_CAP_ID_EXP);
	if (!pm) {
		PCIE_PR_ERR("Failed to get PCI Express capability !");
		return -1;
	}
	pci_read_config_dword(rc_dev, pm + PCI_EXP_LNKCTL2, &val);
	if (entry)
		val |= (0x1 << 4);
	else
		val &= ~(0x1 << 4);
	pci_write_config_dword(rc_dev, pm + PCI_EXP_LNKCTL2, val);
	PCIE_PR_INFO("retrain ltssm");
	auto_ltssm_enable(0, rc_id);
	mdelay(10);
	auto_ltssm_enable(1, rc_id);
	mdelay(20);

	return 0;

}

int compliance_test(u32 rc_id)
{
	int ret = 0;
	struct pci_saved_state *ep_default_state;
	struct pci_saved_state *rc_default_state;
	struct pci_dev *ep_dev = g_pcie_info[rc_id].ep_dev;
	struct pci_dev *rc_dev = g_pcie_info[rc_id].rc_dev;

	if (!(g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_COMPLIANCE))
		return 0;
	PCIE_PR_INFO("+++  COMPLIANCE +++");
	if (rc_dev == NULL || ep_dev == NULL) {
		PCIE_PR_INFO("rc_dev is %p\tep_dev is %p\n", rc_dev, ep_dev);
		ret = PCIE_AUTO_TEST_COMPLIANCE_OTHER_FAIL;
		return ret;
	}
	auto_test_config_aspm_l0s_l1(ASPM_CLOSE, rc_id);
	pci_save_state(ep_dev);
	ep_default_state = pci_store_saved_state(ep_dev);
	pci_save_state(rc_dev);
	rc_default_state = pci_store_saved_state(rc_dev);
	ret = auto_test_entry_compliance(1, rc_id);
	if (ret) {
		ret = PCIE_AUTO_TEST_COMPLIANCE_OTHER_FAIL;
		goto COMPLIANCE_FAIL;
	}
	if (auto_test_wait_for_power_status(COMPLIANCE_MODE, rc_id)) {
		ret = PCIE_AUTO_TEST_ENTRY_COMPLIANCE_FAIL;
		goto COMPLIANCE_FAIL;
	}
	ret = auto_test_entry_compliance(0, rc_id);
	if (ret) {
		ret = PCIE_AUTO_TEST_COMPLIANCE_OTHER_FAIL;
		goto COMPLIANCE_FAIL;
	}

	if (auto_test_wait_for_power_status(L0_MODE, rc_id)) {
		ret = PCIE_AUTO_TEST_EXIT_COMPLIANCE_FAIL;
		goto COMPLIANCE_FAIL;
	}

	g_kirin_pcie[rc_id].rc_dev->msi_enabled = 0;
	pci_load_and_free_saved_state(ep_dev, &ep_default_state);
	pci_restore_state(ep_dev);
	pci_load_and_free_saved_state(rc_dev, &rc_default_state);
	pci_restore_state(rc_dev);
	g_kirin_pcie[rc_id].rc_dev->msi_enabled = 1;
	return ret;

COMPLIANCE_FAIL:
	kfree(ep_default_state);
	ep_default_state = NULL;
	kfree(rc_default_state);
	rc_default_state = NULL;
	return ret;
}

static void auto_pcie_outbound_atu(int index,
		int type, u64 cpu_addr, u64 pci_addr, u32 size, struct pcie_port *pp)
{
	void __iomem *dbi_base = pp->dbi_base;

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

static int pcie_auto_test_link_up(struct pcie_port *pp)
{
	struct kirin_pcie *pcie = to_kirin_pcie(pp);
	u32 val = kirin_elb_readl(pcie, PCIE_ELBI_RDLH_LINKUP);

	if ((val & PCIE_LINKUP_ENABLE) == PCIE_LINKUP_ENABLE)
		return 1;

	return 0;
}

static int pcie_test_init(u32 rc_id)
{
	struct kirin_pcie *pcie = &g_kirin_pcie[rc_id];
	struct pcie_info *pcie_info = &g_pcie_info[rc_id];
	struct pci_dev *ep_dev;
	struct pci_dev *rc_dev;
	struct pcie_port *pp = &(pcie->pp);
	u32 bar2_saved;
	int val;
	u32 cmdreg;
	int ret;

	if (!pp->dev) {
		PCIE_PR_ERR("PCIe No.%d do not work", rc_id);
		return -1;
	}
	if (auto_test_wlan_on(rc_id, 1))
		return -1;
	mdelay(100);
	if (kirin_pcie_power_on(pp, 1))
		return -1;
	/*Unreset wifi*/
	val = readl(pcie->apb_base+ SOC_PCIECTRL_CTRL12_ADDR);
	val = val | 0x7;
	writel(val, pcie->apb_base + SOC_PCIECTRL_CTRL12_ADDR);
	dw_pcie_setup_rc(pp);

	if (kirin_pcie_enumerate(rc_id))
		return -1;

	pcie_info->ep_in_rc_cpu_phys_addr = pp->mem_base + TEST_BUS1_OFFSET;
	pcie_info->ep_in_rc_cpu_virt_addr = ioremap_nocache(pcie_info->ep_in_rc_cpu_phys_addr, (unsigned long)4*SIZE_M);
	pcie_info->ep_in_rc_cpu_virt_addr += WIFI_FIRMWARE_START;
	pcie_info->rc_dev = pcie->rc_dev;
	pcie_info->ep_dev = pcie->ep_dev;

	rc_dev = pcie_info->rc_dev;
	ep_dev = pcie_info->ep_dev;
	if (rc_dev == NULL || ep_dev == NULL) {
		PCIE_PR_INFO("rc_dev is %p\tep_dev is %p\n", rc_dev, ep_dev);
		return -1;
	}
	PCIE_PR_INFO("rc_dev and ep_dev get ok");

	ret = pci_enable_device(ep_dev);
	if (ret) {
		PCIE_PR_ERR("pci_enable_device get ret = %d\n", ret);
		return -1;
	}
	pci_set_master(ep_dev);

	pci_read_config_dword(ep_dev, PCI_COMMAND, &cmdreg);
	cmdreg |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	pci_write_config_dword(ep_dev, PCI_COMMAND, cmdreg);

	pci_read_config_dword(ep_dev, PCI_BASE_ADDRESS_2, &bar2_saved);

	PCIE_PR_INFO("bar2 is %x\n", bar2_saved);
	pci_write_config_dword(ep_dev, PCI_BASE_ADDRESS_2, bar2_saved);
	auto_pcie_outbound_atu(0, 0, pcie->pp.mem_base + TEST_BUS1_OFFSET, bar2_saved, 8*SIZE_M, pp);
	return 0;
}



int pcie_stress_test_set_mode(u32 mode, u32 times, u32 sleep_ms)
{
	if (!(mode & PCIE_STRESS_TEST_MODE_VALID)) {
		PCIE_PR_INFO("[WARNING]No valid bit, valid mode is 0x%08X\n", PCIE_STRESS_TEST_MODE_VALID);
		return PCIE_AUTO_TEST_SET_TESTMODE_FAIL;
	}
	g_pcie_stree_test_mode = mode;
	g_pcie_stress_test_run_max_count = times;
	g_pcie_stress_test_sleep_ms = sleep_ms;

	return 0;
}

int cpu_access_test(u32 rc_id)
{
	u32 size = 0;
	void *source = NULL;
	void *destination = NULL;
	int ret = 0;

	if (g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_CPU_READ) {
		PCIE_PR_INFO("+++  cpu read test +++");
		size = g_pcie_info[rc_id].buffer_size;
		source = g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr;
		destination = g_pcie_info[rc_id].rc_virt_addr;

		if (g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_RANDOM) {
			size = get_random(1, g_pcie_info[rc_id].buffer_size - 1);
			source += (g_pcie_info[rc_id].buffer_size - size);
			destination += (g_pcie_info[rc_id].buffer_size - size);
		}

		ret = ep_to_rc_by_cpu(destination, source, size, rc_id);
		if (ret) {
			PCIE_PR_INFO("PCIE CPU READ fail\n");
			ret = PCIE_AUTO_TEST_CPU_READ_FAIL;
			goto CPU_TEST_END;
		}
	}
	if (g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_CPU_WRITE) {
		PCIE_PR_INFO("+++  cpu write test +++");
		size = g_pcie_info[rc_id].buffer_size;
		source = g_pcie_info[rc_id].rc_virt_addr;
		destination = g_pcie_info[rc_id].ep_in_rc_cpu_virt_addr;

		if (g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_RANDOM) {
			size = get_random(1, g_pcie_info[rc_id].buffer_size - 1);
			source += (g_pcie_info[rc_id].buffer_size - size);
			destination += (g_pcie_info[rc_id].buffer_size - size);
		}

		ret = rc_to_ep_by_cpu(destination, source, size, rc_id);
		if (ret) {
			PCIE_PR_ERR("PCIE CPU WRITE fail\n");
			ret = PCIE_AUTO_TEST_CPU_WRITE_FAIL;
			goto CPU_TEST_END;
		}
	}
CPU_TEST_END:
	return ret;
}
int dma_access_test(u32 rc_id)
{
	u32 dma_size = g_pcie_info[rc_id].buffer_size;
	int ret = 0;

	PCIE_PR_INFO("before pcie in, dma_size  is 0x%x", dma_size);
	if (g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_DMA_READ) {
		PCIE_PR_INFO("+++  DMA READ +++");
		ret = ep_to_rc_by_dma(dma_size, rc_id);
		if (ret) {
			PCIE_PR_ERR("EP to RC by DMA  fail\n");
			ret = PCIE_AUTO_TEST_DMA_READ_FAIL;
			goto DMA_TEST_END;
		}
	}
	if (g_pcie_stree_test_mode & PCIE_STRESS_TEST_MODE_DMA_WRITE) {
		PCIE_PR_INFO("+++  DMA WRITE +++");
		ret = rc_to_ep_by_dma(dma_size, rc_id);
		if (ret) {
			PCIE_PR_ERR("RC to EP by DMA fail\n");
			ret = PCIE_AUTO_TEST_DMA_WRITE_FAIL;
			goto DMA_TEST_END;
		}
	}
DMA_TEST_END:
	return ret;
}

int run_test(u32 rc_id)
{
	int ret = 0;

	if (!pcie_auto_test_link_up(&g_kirin_pcie[rc_id].pp)) {
		PCIE_PR_INFO("PCIE link fail\n");
		ret = PCIE_AUTO_TEST_LINKUP_FAIL;
		goto TEST_END;
	}
	ret = cpu_access_test(rc_id);
	if (ret != 0) {
		PCIE_PR_ERR("cpu access test fail, ret is %x", ret);
		goto TEST_END;
	}
	ret = dma_access_test(rc_id);
	if (ret != 0) {
		PCIE_PR_ERR("dma access test fail, ret is %x", ret);
		goto TEST_END;
	}
	ret = lowpower_test(rc_id);
	if (ret != 0) {
		PCIE_PR_ERR("lowpower test fail, ret is %x", ret);
		goto TEST_END;
	}
	ret = loopback_test(rc_id);
	if (ret) {
		PCIE_PR_ERR("loopback test Fail,ret = 0x%x", ret);
		goto TEST_END;
	}
	pcie_test_init(rc_id);
	mdelay(50);
	ret = compliance_test(rc_id);
	if (ret) {
		PCIE_PR_ERR("compliance test Fail,ret = 0x%x", ret);
		goto TEST_END;
	}
	pcie_test_init(rc_id);
	mdelay(50);
TEST_END:
	return ret;
}

int pcie_stress_test_thread(u32 rc_id)
{
	int ret = 0;

	while (g_pcie_stress_test_task_running) {
		ret = run_test(rc_id);
		if (ret)
			goto THREAD_END;
		g_pcie_stress_test_run_current_count++;
		if (g_pcie_stress_test_sleep_ms)
			msleep(g_pcie_stress_test_sleep_ms);
		PCIE_PR_INFO("g_pcie_stress_test_run_current_count is %d\n", g_pcie_stress_test_run_current_count);
		if (g_pcie_stress_test_run_current_count >= g_pcie_stress_test_run_max_count) {
			PCIE_PR_INFO("pcie test okay!\n");
			ret = PCIE_AUTO_TEST_OKAY;
			goto THREAD_END;
		}
	}
THREAD_END:
	g_pcie_stress_test_task_running = 0;
	auto_test_wlan_on(rc_id, 0);
	return ret;
}


int pcie_stress_test_start(u32 rc_id)
{
	int ret;

	if (g_pcie_stress_test_task_running)
		return PCIE_AUTO_TEST_BUSY;
	g_pcie_stress_test_task_running = 1;
	g_pcie_stress_test_run_current_count = 0;
	if (pcie_test_init(rc_id)) {
		PCIE_PR_ERR("pcie test init fail");
		return PCIE_AUTO_TEST_OTHER_FAIL;
	}
	ret = pcie_stress_test_thread(rc_id);
	return ret;
}

int pcie_stress_test(u32 mode, u32 times, u32 sleep_ms, u32 rc_id)
{
	int ret;

	ret = pcie_stress_test_set_mode(mode, times, sleep_ms);
	if (ret)
		return ret;
	if (rc_id > MAX_RC_NUM) {
		PCIE_PR_ERR("There is no rc_id = %d", rc_id);
		return PCIE_AUTO_TEST_OTHER_FAIL;
	}
	/*RC_ID_MAX: test all RC, other: test the given RC*/
	if ( rc_id != MAX_RC_NUM) {
		ret = pcie_stress_test_start(rc_id);
	} else {
		u32 idx;
		ret = 0;
		for (idx = 0; idx < MAX_RC_NUM; idx++)
			ret |= pcie_stress_test_start(idx);
	}

	return ret;
}
static int pcie_test_common_init(void)
{
	u32 idx;

	temp_memcmp = (char *)kmalloc(WIFI_RW_MEMORY_SIZE, GFP_KERNEL);
	if (!temp_memcmp) {
		PCIE_PR_ERR("alloc temp_memcmp fail\n");
		return -1;
	}

	memset(temp_memcmp, 0xff, WIFI_RW_MEMORY_SIZE);

	for (idx = 0; idx < MAX_RC_NUM; idx++) {
		g_pcie_info[idx].rc_virt_addr = kzalloc(4*SIZE_M, GFP_KERNEL);
		if (!g_pcie_info[idx].rc_virt_addr) {
			PCIE_PR_ERR("alloc rc_virt_addr Fail");
			goto fail0;
		}
		g_pcie_info[idx].rc_phys_addr = virt_to_phys(g_pcie_info[idx].rc_virt_addr);
		memset(g_pcie_info[idx].rc_virt_addr, 0xb4, 4*SIZE_M);
	}

	PCIE_PR_INFO("pcie_test_common_init --");
	return 0;

fail0:
	kfree(temp_memcmp);
	temp_memcmp = NULL;

	return -1;

}
/*lint -e438 -e529 -e550 -e838 +esym(438,*) +esym(529,*) +esym(550,*) +esym(838,*) */
module_init(pcie_test_common_init);
