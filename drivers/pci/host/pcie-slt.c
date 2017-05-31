#ifdef __SLT_FEATURE__
#include "pcie-kirin.h"
#include <linux/file.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/compat.h>
#include <linux/poll.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <linux/pci-aspm.h>
#include <linux/pci.h>
#include <linux/fs.h>
#include <asm/memory.h>
#include <linux/pci_regs.h>


#define WIFI_FIRMWARE_START 0x180000
#define SLT_RANDOM_DATA 0x1234abcd
#define SLT_TEST_DATA_SIZE 0xc0000

#define SIZE_M	(0x100000)
#define L0S_MODE 0
#define L1_MODE 1
#define L0S_L1_MODE 1
#define L1_1_MODE 2
#define L1_2_MODE 3



extern struct kirin_pcie g_kirin_pcie[MAX_RC_NUM];
extern int kirin_pcie_enumerate(u32 rc_idx);
extern void kirin_pcie_writel_rc(struct pcie_port *pp, u32 val, void __iomem *dbi_base);
#define PCIETESTCMD	        _IOWR('p', 0xc1, unsigned long)


static void slt_pcie_outbound_atu(struct pcie_port *pp, int index,
		int type, u64 cpu_addr, u64 pci_addr, u32 size)
{
	char *dbi_base = pp->dbi_base;

	kirin_pcie_writel_rc(pp, PCIE_ATU_REGION_OUTBOUND | index,
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
static int slt_wlan_on(struct kirin_pcie *pcie, int on)
{
	struct device_node *np;
	int wl_power;
	int ret = 0;

	np = pcie->pp.dev->of_node;
	if (np) {
		if (!(of_property_read_u32(np, "wl_power", &wl_power))) {
			PCIE_PR_INFO("WL Power On Number is [%d] ", wl_power);
		} else {
			PCIE_PR_INFO("dts has no member as wl_power");
			return -1;
		}
	} else {
		PCIE_PR_INFO("can not find kirin-pcie\n");
		return -1;
	}

	ret = gpio_request(wl_power, "slt_wlan_on");
	if (ret < 0) {
		PCIE_PR_ERR("Can't request gpio");
		ret = 0;
	}
	if (on) {
		PCIE_PR_INFO("Power on Wlan");
		gpio_direction_output(wl_power, 1);
	} else {
		PCIE_PR_INFO("Power down Wlan");
		gpio_direction_output(wl_power, 0);
	}
	gpio_free(wl_power);

	return ret;

}
/**
 * slt_enable_dbi - make it possible to access the rc configuration registers in the CDM,
 * or the ep configuration registers.
 * @flag: If flag equals 0, you can access the ep configuration registers in the CDM;
 *  If not, you can access the rc configuration registers in the CDM.
 */
static void slt_enable_dbi(struct kirin_pcie *pcie, int flag)
{
	int ret1;
	int ret2;

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
 * @flag: If flag equals 0, bus master and mem space is disabled. If not, bus master and mem space is enabled.
 */
static void set_bme_mse(struct kirin_pcie *pcie, int flag)
{
	int ret = 0;

	slt_enable_dbi(pcie, 1);
	ret = readl(pcie->pp.dbi_base + PCI_COMMAND);
	if (flag) {
		PCIE_PR_INFO("Enable Bus master!!!");
		ret |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
	} else {
		PCIE_PR_INFO("Disable Bus master!!!");
		ret &= ~(PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY);
	}
	writel(ret, pcie->pp.dbi_base + PCI_COMMAND);
	udelay(5);
	ret = readl(pcie->pp.dbi_base + PCI_COMMAND);
	PCIE_PR_INFO("register[0x4] value is [0x%x]", ret);
	slt_enable_dbi(pcie, 0);
}

static void slt_config_aspm_l0s_l1(struct kirin_pcie *pcie, enum link_aspm_state aspm_state)
{
	struct pci_dev *rc_dev;
	struct pci_dev *ep_dev;

	rc_dev = pcie->rc_dev;
	ep_dev = pcie->ep_dev;
	if (ep_dev == NULL || rc_dev == NULL) {
		PCIE_PR_ERR("Failed to get PCI Device");
		return;
	}

	pcie_capability_clear_and_set_word(rc_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_ASPMC, aspm_state);
	pcie_capability_clear_and_set_word(ep_dev, PCI_EXP_LNKCTL,
				   PCI_EXP_LNKCTL_ASPMC, aspm_state);
}

/* wait_for_power_status - wait for link Entry lowpower mode
 * @mode: lowpower mode index
*/
int wait_for_power_status(struct kirin_pcie *pcie, int mode)
{
	int status4;
	int status5;
	int wait_condition = 0;
	unsigned long prev_jffy;

	prev_jffy = jiffies;
	while (!(time_after(jiffies, prev_jffy + HZ / 10))) {
		status4 = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE4_ADDR);
		status5 = kirin_elb_readl(pcie, SOC_PCIECTRL_STATE5_ADDR);
		switch (mode) {
		case 0:
			if ((status4 & 0x3f) == 0x12)
				wait_condition = 1;
			break;
		case 1:
			if ((status4 & 0x3f) == 0x14)
				wait_condition = 1;
			break;
		case 2:
			if (((status5 & BIT(15)) == 0) && ((status5 & BIT(14)) == BIT(14)))
				wait_condition = 1;
			break;
		case 3:
			if (((status5 & BIT(15)) == BIT(15)) && ((status5 & BIT(14)) == BIT(14)))
				wait_condition = 1;
			break;
		default:
			PCIE_PR_ERR("unknown lowpower mode\n");
			break;
		}
		if (wait_condition == 1)
			return 0;
		msleep(10);
	}
	return -1;
}


/**
* slt_enable_l1ss - config l1ss link state;
*/
void slt_enable_l1ss(struct kirin_pcie *pcie, unsigned int flag)
{
	unsigned int val;
	unsigned int pm;
	int ret;
	struct pci_dev *ep_dev;
	struct pci_dev *rc_dev;

	slt_config_aspm_l0s_l1(pcie, ASPM_L1);

	rc_dev = pcie->rc_dev;
	ep_dev = pcie->ep_dev;
	if (ep_dev == NULL || rc_dev == NULL) {
		PCIE_PR_ERR("Failed to get PCI Device");
		return;
	}
	pm = pci_find_ext_capability(rc_dev, PCI_EXT_L1SS_CAP_ID);
	if (pm) {
		pci_read_config_dword(rc_dev, pm + PCI_EXT_L1SS_CTRL1, &val);
		val &= ~(0x3 << 2);
		val |= flag;
		pci_write_config_dword(rc_dev, pm + PCI_EXT_L1SS_CTRL1, val);
	}

	pcie_capability_read_dword(pcie->rc_dev, PCI_EXP_DEVCTL2, &val);
	val |= (0x1 << 10);
	pcie_capability_write_dword(pcie->rc_dev, PCI_EXP_DEVCTL2, val);

	ret = readl(pcie->apb_base + SOC_PCIECTRL_CTRL7_ADDR);
	ret |= (0x1<<10);
	writel(ret, pcie->apb_base + SOC_PCIECTRL_CTRL7_ADDR);

	ret = readl(pcie->apb_base + SOC_PCIECTRL_CTRL8_ADDR);
	ret |= (0x1<<3);
	writel(ret, pcie->apb_base + SOC_PCIECTRL_CTRL8_ADDR);

	pcie_capability_read_dword(ep_dev, PCI_EXP_LNKCTL, &val);
	val &= ~0x3;
	val |= 0x142;
	pcie_capability_write_dword(ep_dev, PCI_EXP_LNKCTL, val);
	/*Read register to check*/
	val = 0;
	pcie_capability_read_dword(ep_dev, PCI_EXP_LNKCTL, &val);
	PCIE_PR_INFO("WIFI CFG Register[0xbc] value=[0x%x] ", val);

	pm = pci_find_ext_capability(ep_dev, PCI_EXT_L1SS_CAP_ID);
	if (pm) {
		pci_read_config_dword(ep_dev, pm + PCI_EXT_L1SS_CTRL1, &val);
		val &= ~(0x3 << 2);
		val |= flag;
		pci_write_config_dword(ep_dev, pm + PCI_EXT_L1SS_CTRL1, val);

		pci_read_config_dword(ep_dev, pm + PCI_EXT_L1SS_CTRL2, &val);
		val &= ~0xFF;
		val |= 0x61;
		pci_write_config_dword(ep_dev, pm + PCI_EXT_L1SS_CTRL2, val);
	}
	pcie_capability_read_dword(ep_dev, PCI_EXP_DEVCTL2, &val);
	val |= (0x1 << 10);
	pcie_capability_write_dword(ep_dev, PCI_EXP_DEVCTL2, val);

	pm = pci_find_ext_capability(ep_dev, PCI_EXT_LTR_CAP_ID);
	if (pm)
		pci_write_config_dword(ep_dev, pm + LTR_MAX_SNOOP_LATENCY, 0x10031003);

	ret = readl(pcie->apb_base + SOC_PCIECTRL_CTRL1_ADDR);
	ret |= (0x1 << 23);
	writel(ret, pcie->apb_base + SOC_PCIECTRL_CTRL1_ADDR);

	mdelay(10);
}

enum pcie_test_result set_loopback_test(struct kirin_pcie *pcie)
{
	u32 value_temp = 0;
	int index = 0;
	int ret = 0;
	int bar2 = 0;
	static int prev_ret = 0xaa;
	unsigned int val = 0;
	struct pci_dev *ep_dev;
	struct pcie_port *pp;
	void __iomem *dbi_base;
	void __iomem *loop_back_cmp;
	void __iomem *loop_back_src;

	loop_back_cmp = kmalloc(SLT_TEST_DATA_SIZE, GFP_KERNEL);
	if (!loop_back_cmp) {
		PCIE_PR_ERR("can not alloc loop_back_cmp memory");
		return ERR_OTHER;
	}
	if (!pcie) {
		PCIE_PR_ERR("FATAL!kirin_pcie is null, we do nothing!");
		ret =  ERR_OTHER;
		goto TEST_FAIL;
	}
	pp = &(pcie->pp);
	dbi_base = pcie->pp.dbi_base;
	if (prev_ret == 0xaa) {
		if (slt_wlan_on(pcie, 1)) {
			ret =  ERR_OTHER;
			goto TEST_FAIL;
		}
		mdelay(100);
		ret = kirin_pcie_power_on(&pcie->pp, 1);
		if (ret) {
			PCIE_PR_ERR("Failed to Power On RC");
			ret = ERR_OTHER;
			goto TEST_FAIL;
		}
		/*Unreset wifi*/
		val = readl(pcie->apb_base+ SOC_PCIECTRL_CTRL12_ADDR);
		val |= 0x7;
		writel(val, pcie->apb_base + SOC_PCIECTRL_CTRL12_ADDR);
		kirin_pcie_enumerate(pcie->rc_id);
	}
	mdelay(10);
	set_bme_mse(pcie, 1);
	ep_dev = pcie->ep_dev;
	if (!ep_dev) {
		PCIE_PR_ERR("Failed to get EP Device");
		ret = ERR_OTHER;
		goto TEST_FAIL;
	}
	if (prev_ret == 0xaa) {
		pci_enable_device(ep_dev);
		pci_set_master(ep_dev);
		prev_ret = 0x55;
	}

	pci_read_config_dword(ep_dev, 0x18, &bar2);
	PCIE_PR_INFO("bar2 is %x", bar2);
	loop_back_src = ioremap_nocache(pcie->pp.mem_base, 4*SIZE_M);
	slt_pcie_outbound_atu(pp, PCIE_ATU_REGION_INDEX0, PCIE_ATU_TYPE_MEM, pp->mem_base, (bar2 & (~0x3)), 8*SIZE_M);
	for (index = 0; index < SLT_TEST_DATA_SIZE; index = index + 4) {
		writel((SLT_RANDOM_DATA + index), (loop_back_cmp + index));
		writel((SLT_RANDOM_DATA + index), (loop_back_src + index + WIFI_FIRMWARE_START));
	}
	if (memcmp((loop_back_src + WIFI_FIRMWARE_START), loop_back_cmp, SLT_TEST_DATA_SIZE)) {
		PCIE_PR_ERR("loop back fail");
		ret = ERR_DATA_TRANS;
		goto TEST_FAIL;
	}
	PCIE_PR_INFO("loop back OK");
	slt_config_aspm_l0s_l1(pcie, ASPM_L0S);
	if (wait_for_power_status(pcie, L0S_MODE)) {
		PCIE_PR_ERR("Enter L0s fail");
		ret = ERR_L0S;
		goto TEST_FAIL;
	}
	PCIE_PR_INFO("L0S test pass");
	slt_config_aspm_l0s_l1(pcie, ASPM_L1);
	if (wait_for_power_status(pcie, L1_MODE)) {
		PCIE_PR_ERR("Enter L1 fail");
		ret = ERR_L1;
		goto TEST_FAIL;
	}
	PCIE_PR_INFO("L1 test pass");
	slt_config_aspm_l0s_l1(pcie, ASPM_L0S_L1);
	if (wait_for_power_status(pcie, L1_MODE)) {
		PCIE_PR_ERR("Enter L0s_and_L1 fail");
		ret = ERR_L0_L1;
		goto TEST_FAIL;
	}
	PCIE_PR_INFO("L0s and L1 test pass");
	/*Return to L0*/
	slt_config_aspm_l0s_l1(pcie, ASPM_CLOSE);
	writel(SLT_RANDOM_DATA, loop_back_src + WIFI_FIRMWARE_START);
	/*close soft config for clk, controlled by hardware*/
	writel((0x7 << 17), pcie->sctrl_base + SCTRL_SCPERCLKDIS2);
	writel((0x1 << 20) | (0x1 << 14), pcie->sctrl_base + SCTRL_SCPERCLKEN2);
	slt_enable_l1ss(pcie, L1_SUB_1_1);
	if (wait_for_power_status(pcie, L1_1_MODE)) {
		PCIE_PR_ERR("Enter L1_1 fail");
		ret = ERR_L1_1;
		goto TEST_FAIL;
	}
	PCIE_PR_INFO("L1SS test pass");
	slt_enable_l1ss(pcie, L1_SUB_1_2);
	if (wait_for_power_status(pcie, L1_2_MODE)) {
		PCIE_PR_ERR("Enter L1_2 fail");
		ret = ERR_L1_2;
		goto TEST_FAIL;
	}
	PCIE_PR_INFO("L1SS test pass");
	ret = RESULT_OK;
TEST_FAIL:
	iounmap(loop_back_src);
	kfree(loop_back_cmp);
	loop_back_cmp = NULL;
	return ret;
}
EXPORT_SYMBOL(set_loopback_test);

struct pcie_slt {
	atomic_t ioctl_excl;
	atomic_t open_excl;
	int pcie_slt_major_number;
};
struct pcie_slt g_pcie_slt;

static inline int pcie_slt_lock(atomic_t *excl)
{
	if (atomic_inc_return(excl) == 1) {
		return 0;
	} else {
		atomic_dec(excl);
		return -1;
	}
}

static inline void pcie_slt_unlock(atomic_t *excl)
{
	atomic_dec(excl);
}

static int pcie_slt_ioctl(struct file *file, u_int cmd, unsigned long result)
{
	int ret;
	int test_result, val;
	int id;

	if (pcie_slt_lock(&(g_pcie_slt.ioctl_excl)))
		return -EBUSY;

	for (id = 0; id < MAX_RC_NUM; id++) {
		switch (cmd) {
		case PCIETESTCMD:
			val = set_loopback_test(&g_kirin_pcie[id]);
			if (val) {
				PCIE_PR_ERR("PCIe No.%d slt fail = 0x%x", val);
				test_result = val;
			}
			ret = 0;
			break;
		default:
			ret = -1;
			goto FAIL;
		}
	}
	copy_to_user((unsigned long *)result, &test_result, sizeof(int));
FAIL:
	pcie_slt_unlock(&(g_pcie_slt.ioctl_excl));
	return ret;
}


static int pcie_slt_open(struct inode *ip, struct file *fp)
{
	PCIE_PR_INFO("pcie_slt_open\n");

	if (pcie_slt_lock(&(g_pcie_slt.open_excl)))

		return -EBUSY;
	PCIE_PR_INFO("pcie_slt_open success\n");
	return 0;
}

static int pcie_slt_release(struct inode *ip, struct file *fp)
{

	PCIE_PR_INFO("pcie_slt_release\n");

	pcie_slt_unlock(&(g_pcie_slt.open_excl));

	return 0;
}

static const struct file_operations pcie_slt_fops = {
	.owner             = THIS_MODULE,
	.unlocked_ioctl    = pcie_slt_ioctl,
	.open              = pcie_slt_open,
	.release           = pcie_slt_release,
};

static int __init pcie_slt_init(void)
{
	int error;
	struct device *pdevice;

	struct class *pcie_slt_class;

	/*semaphore initial*/
	g_pcie_slt.pcie_slt_major_number = register_chrdev(0, "pcie-slt", &pcie_slt_fops);

	if (g_pcie_slt.pcie_slt_major_number < 0) {
		PCIE_PR_ERR("Can't allocate major number for pcie slt device.\n");
		error = -EAGAIN;
		goto failed_register_pcie;
	}
	atomic_set(&g_pcie_slt.open_excl, 0);
	atomic_set(&g_pcie_slt.ioctl_excl, 0);

	pcie_slt_class = class_create(THIS_MODULE, "pcie-slt");

	if (IS_ERR(pcie_slt_class)) {
		PCIE_PR_ERR("Error creating pcie-slt class.\n");
		unregister_chrdev(g_pcie_slt.pcie_slt_major_number, "pcie-slt");
		error = PTR_ERR(pcie_slt_class);
		goto failed_register_pcie;
	}

	 pdevice = device_create(pcie_slt_class, NULL, MKDEV(g_pcie_slt.pcie_slt_major_number, 0), NULL, "pcie-slt");
	if (IS_ERR(pdevice)) {
		error = -EFAULT;
		PCIE_PR_ERR("slt pcie: device_create error.\n");
		goto failed_register_pcie;
	}

	PCIE_PR_INFO("pcie-slt init ok!\n");

	return 0;

failed_register_pcie:
	return error;
}
static void __exit pcie_slt_cleanup(void)
{
	unregister_chrdev(g_pcie_slt.pcie_slt_major_number, "pcie-slt");
}
module_init(pcie_slt_init);
module_exit(pcie_slt_cleanup);
MODULE_DESCRIPTION("Hisilicon Kirin pcie driver");
MODULE_LICENSE("GPL");
#endif
