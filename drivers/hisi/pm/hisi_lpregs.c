/*
 *
 * Copyright (C) 2015 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#include <linux/version.h>
#include <linux/init.h>
#include <linux/cpu_pm.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/irqflags.h>
#include <linux/arm-cci.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/slab.h>
#include <linux/console.h>
#include <linux/wakelock.h>
#include <soc_crgperiph_interface.h>
#include <soc_uart_interface.h>
#include <soc_sctrl_interface.h>
#include "hisi_lpregs.h"
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
/*lint -e322 -esym(750,*) -e7*/
#include <linux/hisi/hisi_gpio_auto_gen.h>
#include "m3_rdr_ddr_map.h"

#include <huawei_platform/power/hw_power_monitor.h>

#define PM_WAKE_STATUS_OFFSET			(0x034)
#define PM_SYS_SLEEP_CNT_OFFSET			(0x060)
#define PM_SYS_WAKE_CNT_OFFSET			(0x064)
#define PM_AP_WAKE_CNT_OFFSET			(0x068)
#define PM_HIFI_WAKE_CNT_OFFSET			(0x06C)
#define PM_MODEM_WAKE_CNT_OFFSET		(0x070)
#define PM_IOMCU_WAKE_CNT_OFFSET			(0x074)
#define PM_LPM3_WAKE_CNT_OFFSET			(0x078)
#define PM_AP_SUSPEND_CNT_OFFSET			(0x07C)
#define PM_AP_RESUME_CNT_OFFSET			(0x080)
#define PM_IOMCU_SUSPEND_CNT_OFFSET		(0x084)
#define PM_IOMCU_RESUME_CNT_OFFSET		(0x088)
#define PM_MODEM_SUSPEND_CNT_OFFSET		(0x08C)
#define PM_MODEM_RESUME_CNT_OFFSET		(0x090)
#define PM_HIFI_SUSPEND_CNT_OFFSET		(0x094)
#define PM_HIFI_RESUME_CNT_OFFSET			(0x098)
#define PM_WAKE_IRQ_OFFSET				(0x09C)
#define PM_AP_WAKE_IRQ_OFFSET			(0x0A0)
#define PM_AP_NSIPC_IRQ_OFFSET			(0x0A4)
#define SLEEP_CNT_OFFSET			(0x0C4)
#define SLEEP_WAKE_IRQ_OFFSET			(0x0C8)
#define SLEEP_WAKE_IRQ1_OFFSET			(0x0CC)
#define IDLE_SLEEP_CNT_OFFSET			(0x0F4)
#define IDLE_RESUME_CNT_OFFSET			(0x0F8)
#define PM_WAKE_IRQ1_OFFSET				(0x0FC)

#define SCINT_STAT_OFFSET					(0x458)
#define SCINT_STAT1_OFFSET					(0x468)

#define PM_BUFFER_SIZE						(256)

#define WAKE_STATUS_AP_MASK     (0x01)
#define WAKE_STATUS_MODEM_MASK  (0x02)
#define WAKE_STATUS_HIFI_MASK   (0x04)
#define WAKE_STATUS_IOMCU_MASK  (0x08)
#define WAKE_STATUS_LPMCU_MASK  (0x10)
#define WAKE_STATUS_GPS_MASK    (0x20)
#define WAKE_STATUS_HOTPLUG_MASK(cluster)       (0x1 << ((cluster) + 6))

/* FIXME: need to supplement */
/***************************
 * SCINT_STAT
	bit 0:gpio_22_int,
	bit 1:gpio_23_int,
	bit 2:gpio_24_int,
	bit 3:gpio_25_int,
	bit 5:gpio_27_int,
	bit 6:rtc_int,
	bit 7:rtc1_int,
	bit 11:timer11_int, for secure os
***************************/
#define AP_INT_MASK (0x000008ef)

/*******************
 * SCINT_STAT
 *  bit 31: intr_wakeup_iomcu
 *  bit 28: intr_iomcu_wdog
*******************/
#define IOMCU_INT_MASK (0x90000000)

/*******************
 * SCINT_STAT
	bit 4:gpio_26_int,
	bit 9:timer01_int
	bit 12:timer20_int
	bit 13:timer21_int
	bit 14:timer30_int
	bit 15:timer31_int
*******************/
#define MODEM_INT_MASK (0x0000f210)

/*******************
 * SCINT_STAT1
 * bit 0: drx0_int
 * bit 1: drx1_int
 * bit 2: drx2_int
 * bit 3: drx3_int
 * bit 4: drx4_int
 * bit 5: drx5_int
********************/
#define MODEM_DRX_INT_MASK (0x0000003f)

/*******************
 * FIXME: need to supplement
 * #define LPM3_INT_MASK (0x0000)
*******************/

/*******************
 * bit 26: intr_asp_ipc_arm
 * bit 27: intr_asp_watchdog
*******************/
#define HIFI_INT_MASK  (0x0c000000)



#define WAKE_IRQ_NUM_MAX 30

#define DEBG_SUSPEND_PRINTK		(1<<0)
#define DEBG_SUSPEND_IO_SHOW		(1<<1)
#define DEBG_SUSPEND_PMU_SHOW	(1<<2)
#define DEBG_SUSPEND_IO_SET		(1<<3)
#define DEBG_SUSPEND_PMU_SET		(1<<4)
#define DEBG_SUSPEND_IO_S_SET		(1<<5)
#define DEBG_SUSPEND_RTC_EN		(1<<6)
#define DEBG_SUSPEND_TIMER_EN		(1<<7)
#define DEBG_SUSPEND_WAKELOCK	(1<<8)
#define DEBG_SUSPEND_AUDIO		(1<<9)
#define DEBG_SUSPEND_CLK_SHOW	(1<<10)
#define DEBG_SUSPEND_IPC_DATA_SHOW	(1<<11)
#define DEBUG_INFO				(1<<31)

/* pmu */
#define PMUSSI_REG(x) (sysreg_base.pmic_base + ((x)<<2))

#define SCTRLBASE       0xfff0a000
#define CRGBASE          0xfff35000
#define PMCBASE          0xfff31000
#define PMUBASE          0xfff34000
#define PCTRLBASE		0xE8A09000

/* FIXME */
#define IPC_COMBO_AP		181

/*ipc processor max*/
#define IPC_PROCESSOR_MAX		6
/*ipc mailbox max*/
#define NSIPC_MAILBOX_MAX		27

#define AP_IPC_PROC_MAX			2

#define IPC_MBXDATA_MAX			8
#define IPC_MBX_SOURCE_OFFSET(m)		((m) << 6)
#define IPC_MBX_DSTATUS_OFFSET(m)		(0x0C + ((m) << 6))
#define IPC_MBXDATA_OFFSET(m, idex)		(0x20 + 4 * (idex) + ((m) << 6))

#define CLK_DEBUG_FILE_MODE     (S_IRUSR)
#define PMU_DEBUG_FILE_MODE     (S_IRUSR)
#define IO_DEBUG_FILE_MODE     (S_IRUSR)
#define CFG_DEBUG_FILE_MODE     (S_IRUSR | S_IWUSR)
#define DEBUGSR_DEBUG_FILE_MODE     (S_IRUSR)
#define NO_SEQFILE 0
#define LOWPM_MSG(seq_file, fmt, args ...) \
		{		\
			if (NO_SEQFILE == seq_file)	\
				printk(KERN_INFO fmt, ##args);	\
			else	\
				seq_printf(seq_file, fmt, ##args);	\
		}

#define CRG_PERRSTDIS2_ip_prst_uart0_BIT	SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_START

/* struct sysreg_bases to hold the base address of some system registers.*/
struct sysreg_base_addr {
	void __iomem *uart_base;
	void __iomem *pctrl_base;
	void __iomem *pmctrl_base;
	void __iomem *sysctrl_base;
	void __iomem **gpio_base;
	void __iomem *crg_base;
	void __iomem *pmic_base;
	void __iomem *reserved_base;
	void __iomem *nsipc_base;
};

struct sysreg_base_addr sysreg_base;

struct lp_clk {
	unsigned int reg_base;
	unsigned int reg_off;
	unsigned int bit_idx;
	const char *clk_name;
	unsigned int status;
};

struct sys_reg {
	unsigned int reg_base;
	unsigned int reg_off;
	const char *reg_name;
};

unsigned int g_io_group_num;
unsigned int g_lpmcu_irq_num;
unsigned int g_lp_pmu_num;
unsigned int g_pmu_addr_end;
unsigned int g_lp_clk_num;
const char **g_lpmcu_irq_name;
void __iomem **g_ioc_reg;
int g_sec_reg_num;

unsigned char *processor_name[IPC_PROCESSOR_MAX] = {
	"gic1",
	"gic2",
	"iomcu",
	"lpm3",
	"hifi",
	"modem"
};

#define PMU_NAME(a, b, c, d) \
	{ .name = a, .module = b, .status = c, .status_name = d}

/* note: g_hisi_pmu_idx[k] must be matched with g_pmuregs_lookups[k],
 * otherwise the array may be out of range.
 */
static struct pmu_idx **g_hisi_pmu_idx;
#define PMU_LOW(x, y, z) \
		{ .ucoffset = (x), .cval = (y), .cmask = (z), .old_val = 0,}
static struct pmuregs **g_pmuregs_lookups;

static struct lp_clk **g_clk_lookups;

static unsigned g_usavedcfg;
static int g_suspended;
extern int get_console_index(void);

static struct wake_lock lowpm_wake_lock;


#define BUFFER_LENGTH		40

unsigned int g_boardid;

static int map_io_regs(void)
{
	int i = 0;
	int ret = 0;
	struct device_node *np = NULL;
	char *io_buffer = NULL;
	unsigned int boardid[4] = {0};

	io_buffer = kmalloc(BUFFER_LENGTH * sizeof(char), GFP_KERNEL);
	if (NULL == io_buffer) {
		pr_err("%s: io buffer kmalloc fail.\n", __func__);
		ret = -ENOMEM;
		goto err;
	}

	ret = of_property_read_u32_array(of_find_node_by_path("/"),
			"hisi,boardid", &boardid[0], 4);
	if (ret) {
		pr_err("%s: not find boardid.\n", __func__);
		ret = -ENODEV;
		goto err_free_buffer;
	}

	g_boardid = boardid[0] * 1000 + boardid[1] * 100
				+ boardid[2] * 10 + boardid[3];

	pr_info("%s: boardid %x\n", __func__, g_boardid);

	/* find io group max num */
	i = 0;
	while (1) {
		memset(io_buffer, 0, BUFFER_LENGTH * sizeof(char));
		snprintf(io_buffer, BUFFER_LENGTH * sizeof(char),
				"arm,primecell%d", i);
		np = of_find_compatible_node(NULL, NULL, io_buffer);
		if (!np) {
			pr_err("%s[%d]: gpio%d not find.\n", __func__, __LINE__, i);
			if (0 == i) {
				pr_err("%s: no group num!\n", __func__);
				ret = -ENODEV;
				goto err_free_buffer;
			}
			break;
		}
		i++;
		of_node_put(np);
	}
	g_io_group_num = i;
	pr_info("%s: find gpio group num: %u\n", __func__, g_io_group_num);

	sysreg_base.gpio_base = kzalloc(g_io_group_num * sizeof(void __iomem *), GFP_KERNEL);
	if (!sysreg_base.gpio_base) {
		pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
		ret = -ENOMEM;
		goto err_free_buffer;
	}

	for (i = 0; i < g_io_group_num; i++) {
		memset(io_buffer, 0, BUFFER_LENGTH * sizeof(char));
		snprintf(io_buffer, BUFFER_LENGTH * sizeof(char),
				"arm,primecell%d", i);
		np = of_find_compatible_node(NULL, NULL, io_buffer);
		if (!np) {
			pr_err("%s[%d]: gpio%d not find.\n", __func__, __LINE__, i);
			ret = -ENODEV;
			goto err_free_io;
		}
		sysreg_base.gpio_base[i] = of_iomap(np, 0);
		pr_debug("%s: sysreg_base.gpio_base[%d] %p\n",
				__func__, i, sysreg_base.gpio_base[i]);
		if (!sysreg_base.gpio_base[i]) {
			pr_err("%s: gpio%d iomap err.\n", __func__, i);
			ret = -ENOMEM;
			goto err_put_node;
		}
		of_node_put(np);
	}

	kfree(io_buffer);
	io_buffer = NULL;
	return 0;

err_put_node:
	of_node_put(np);
err_free_io:
	kfree(sysreg_base.gpio_base);
	sysreg_base.gpio_base = NULL;
err_free_buffer:
	kfree(io_buffer);
	io_buffer = NULL;
err:
	pr_err("%s: failed!\n", __func__);
	return ret;
}

/*map system registers*/
static int map_sysregs(void)
{
	int ret = 0;
	unsigned int uart_idx = 0;
	struct device_node *np = NULL;

	uart_idx = get_console_index();
	switch (uart_idx) {
	case 0:
		np = of_find_compatible_node(NULL, NULL, "arm,pl011");
		if (!np) {
			pr_err("%s: dts[%s] node not found\n",
					__func__, "arm,pl011");
			ret = -ENODEV;
			goto err;
		}
		break;
	case 6:
		/* FIXME */
		np = of_find_compatible_node(NULL, NULL,
						"hisilicon,lowpm_func");
		if (!np) {
			pr_err("%s: dts[%s] node not found\n",
					__func__, "hisilicon,lowpm_func");
			ret = -ENODEV;
			goto err;
		}
		break;
	default:
		pr_err("%s:uart default:%d\n", __func__, uart_idx);
		ret = -ENODEV;
		goto err;
	}

	sysreg_base.uart_base = of_iomap(np, 0);
	pr_debug("%s: uart_base:%p\n", __func__, sysreg_base.uart_base);
	if (!sysreg_base.uart_base) {
		pr_err("%s: uart_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,sysctrl");
		ret = -ENODEV;
		goto err;
	}
	sysreg_base.sysctrl_base = of_iomap(np, 0);
	pr_debug("%s: sysctrl_base:%p\n", __func__, sysreg_base.sysctrl_base);
	if (!sysreg_base.sysctrl_base) {
		pr_err("%s: sysctrl_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (!np) {
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,pctrl");
		ret = -ENODEV;
		goto err;
	}
	sysreg_base.pctrl_base = of_iomap(np, 0);
	pr_debug("%s: pctrl_base:%p\n", __func__, sysreg_base.pctrl_base);
	if (!sysreg_base.pctrl_base) {
		pr_err("%s: pctrl_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");
	if (!np) {
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,pmctrl");
		ret = -ENODEV;
		goto err;
	}
	sysreg_base.pmctrl_base = of_iomap(np, 0);
	pr_debug("%s: pmctrl_base:%p\n", __func__, sysreg_base.pmctrl_base);
	if (!sysreg_base.pmctrl_base) {
		pr_err("%s: pmctrl_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,crgctrl");
		ret = -ENODEV;
		goto err;
	}
	sysreg_base.crg_base = of_iomap(np, 0);
	pr_debug("%s: crg_base:%p\n", __func__, sysreg_base.crg_base);
	if (!sysreg_base.crg_base) {
		pr_err("%s: crg_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmu");
	if (!np) {
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,pmu");
		ret = -ENODEV;
		goto err;
	}
	sysreg_base.pmic_base = of_iomap(np, 0);
	pr_debug("%s: pmic_base:%p\n", __func__, sysreg_base.pmic_base);
	if (!sysreg_base.pmic_base) {
		pr_err("%s: pmic_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	/* FIXME */
	np = of_find_compatible_node(NULL, NULL, "hisilicon,HiIPCV230");
	if (!np) {
		pr_err("%s: dts[%s] node not found\n",
				__func__, "hisilicon,HiIPCV230");
		ret = -ENODEV;
		goto err;
	}
	sysreg_base.nsipc_base = of_iomap(np, 0);
	pr_info("%s: nsipc_base:%p\n", __func__, sysreg_base.nsipc_base);
	if (!sysreg_base.nsipc_base) {
		pr_err("%s: nsipc_base of iomap fail!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	return 0;

err_put_node:
	of_node_put(np);
err:
	pr_err("%s[%d]: fail!\n", __func__, __LINE__);
	return ret;
}

/****************************************
 *function: debuguart_reinit
 *description:
 *  reinit debug uart.
 *****************************************/
void debuguart_reinit(void)
{
	unsigned int uart_idx = 0;
	unsigned int uregv = 0;

	if ((1 == console_suspend_enabled)
			|| (NULL == sysreg_base.uart_base)
			|| (NULL == sysreg_base.crg_base))
		return;

	uart_idx = get_console_index();

	if (uart_idx == 6) {
		/* enable clk */
		uregv = readl(SOC_SCTRL_SCLPMCUCLKEN_ADDR(sysreg_base.sysctrl_base))
				| BIT(SOC_SCTRL_SCLPMCUCLKEN_uart_clk_clkoff_sys_n_START);
		writel(uregv,
			SOC_SCTRL_SCLPMCUCLKEN_ADDR(sysreg_base.sysctrl_base));

		/* reset undo */
		writel(BIT(SOC_SCTRL_SCLPMCURSTDIS_uart_soft_rst_req_START),
			SOC_SCTRL_SCLPMCURSTDIS_ADDR(sysreg_base.sysctrl_base));
	} else if (uart_idx == 0) {
		/* enable clk */
		writel(BIT(SOC_CRGPERIPH_PEREN2_gt_clk_uart0_START),
				SOC_CRGPERIPH_PEREN2_ADDR(sysreg_base.crg_base));

		/* reset undo */
		writel(BIT(CRG_PERRSTDIS2_ip_prst_uart0_BIT),
				SOC_CRGPERIPH_PERRSTDIS2_ADDR(sysreg_base.crg_base));
	} else {
		return;
	}

	/* disable uart */
	writel(0x0, SOC_UART_UARTCR_ADDR(sysreg_base.uart_base));

	/* set baudrate: 19.2M 115200 */
	writel(0xa, SOC_UART_UARTIBRD_ADDR(sysreg_base.uart_base));
	writel(0x1b, SOC_UART_UARTFBRD_ADDR(sysreg_base.uart_base));

	/* disable FIFO */
	writel(0x0, SOC_UART_UARTLCR_H_ADDR(sysreg_base.uart_base));

	/* set FIFO depth: 1/2 */
	writel(0x92, SOC_UART_UARTIFLS_ADDR(sysreg_base.uart_base));

	/* set int mask */
	uregv = BIT(SOC_UART_UARTIMSC_rtim_START)
		| BIT(SOC_UART_UARTIMSC_rxim_START);
	writel(uregv, SOC_UART_UARTIMSC_ADDR(sysreg_base.uart_base));

	/* enable FIFO */
	writel(0x70, SOC_UART_UARTLCR_H_ADDR(sysreg_base.uart_base));

	/* enable uart trans */
	uregv = BIT(SOC_UART_UARTCR_uarten_START)
			| BIT(SOC_UART_UARTCR_rxe_START)
			| BIT(SOC_UART_UARTCR_txe_START);
	writel(uregv, SOC_UART_UARTCR_ADDR(sysreg_base.uart_base));
}


unsigned int proc_mask_to_id(unsigned int mask)
{
	unsigned int i = 0;

	for (i = 0; i < IPC_PROCESSOR_MAX; i++) {
		if (mask & BIT(i))
			break;
	}

	return i;
}

void ipc_mbx_irq_show(struct seq_file *s, void __iomem *base, unsigned int mbx)
{
	unsigned int ipc_source = 0;
	unsigned int ipc_dest = 0;
	unsigned int src_id = 0;
	unsigned int dest_id = 0;
	unsigned int i = 0;

	ipc_source = readl(base + IPC_MBX_SOURCE_OFFSET(mbx));
	src_id = proc_mask_to_id(ipc_source);
	if (src_id < AP_IPC_PROC_MAX) {
		/*is ack irq*/
		ipc_dest = readl(base + IPC_MBX_DSTATUS_OFFSET(mbx));
		dest_id = proc_mask_to_id(ipc_dest);
		if (dest_id < IPC_PROCESSOR_MAX) {
			LOWPM_MSG(s, "SR:mailbox%u: ack from %s\n", mbx, processor_name[dest_id]);
		} else {
			LOWPM_MSG(s, "SR:mailbox%u: ack from unknown(dest_id = %u)\n", mbx, dest_id);
		}
	} else if (src_id < IPC_PROCESSOR_MAX) {
		/*is receive irq*/
		LOWPM_MSG(s, "SR:mailbox%u: send by %s\n",
				mbx, processor_name[src_id]);
	} else {
		LOWPM_MSG(s, "SR:mailbox%u: src id unknown(src_id = %u)\n", mbx, src_id);
	}


	/*if ((g_usavedcfg & DEBG_SUSPEND_IPC_DATA_SHOW) > 0) {*/
	for (i = 0; i < IPC_MBXDATA_MAX; i++) {
		LOWPM_MSG(s, "SR:[MBXDATA%u]:0x%x\n",
				i, readl(base + IPC_MBXDATA_OFFSET(mbx, i)));
	}
}

void combo_ipc_irq_show(struct seq_file *s, unsigned int nsipc_state)
{
	unsigned int mbx = 0;

	/*ns ipc irq detail show*/
	LOWPM_MSG(s, "SR:nsipc irq state:0x%x\n", nsipc_state);
	if (sysreg_base.nsipc_base == NULL) {
		LOWPM_MSG(s, "SR:nsipc base is NULL\n");
		return;
	}
	for (mbx = 0; mbx <= NSIPC_MAILBOX_MAX; mbx++) {
		if ((nsipc_state & BIT(mbx)) > 0)
			ipc_mbx_irq_show(s, sysreg_base.nsipc_base, mbx);
	}

}

/****************************************
 *function: pm_status_show
 *description:
 *  show pm status.
 *****************************************/
void pm_status_show(struct seq_file *s)
{
	unsigned int wake_status = 0;
	unsigned int wake_irq = 0;
	unsigned int wake_irq1 = 0;
	unsigned int bit_shift = 0;
	unsigned int i = 0;
	unsigned int ap_irq = 0;

	if (!sysreg_base.reserved_base) {
		if (M3_RDR_SYS_CONTEXT_BASE_ADDR)
			sysreg_base.reserved_base = M3_RDR_SYS_CONTEXT_RUNTIME_VAR_ADDR;
		else
			return;
	}

	wake_status = readb(sysreg_base.reserved_base + PM_WAKE_STATUS_OFFSET);
	LOWPM_MSG(s,
		"SR:wakelock status, ap:%d, modem:%d, hifi:%d, iomcu:%d, gps:%d, hotplug:%d,%d.\n",
		(wake_status & WAKE_STATUS_AP_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_MODEM_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_HIFI_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_IOMCU_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_GPS_MASK) ? 1 : 0,
		(wake_status & WAKE_STATUS_HOTPLUG_MASK(0)) ? 1 : 0,
		(wake_status & WAKE_STATUS_HOTPLUG_MASK(1)) ? 1 : 0);
    power_monitor_report(MODEM_SLEEP,"%d",(wake_status & WAKE_STATUS_MODEM_MASK) ? 1 : 0);
    power_monitor_report(IOM3_SLEEP,"%d",(wake_status & WAKE_STATUS_IOMCU_MASK) ? 1 : 0);

	LOWPM_MSG(s, "SR:system sleeped %u times.\n",
		readl(sysreg_base.reserved_base + PM_SYS_SLEEP_CNT_OFFSET));
	LOWPM_MSG(s,
		"SR:wake times, system:%u, woken up by ap:%u, modem:%u, hifi:%u, iomcu:%u, lpm3:%u.\n",
		readl(sysreg_base.reserved_base + PM_SYS_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_AP_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_MODEM_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_HIFI_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_IOMCU_WAKE_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_LPM3_WAKE_CNT_OFFSET));
	LOWPM_MSG(s,
		"SR:sr times of sub system, ap:s-%u, r-%u, modem:s-%u, r-%u, hifi:s-%u, r-%u, iomcu:s-%u, r-%u.\n",
		readl(sysreg_base.reserved_base + PM_AP_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_AP_RESUME_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_MODEM_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_MODEM_RESUME_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_HIFI_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_HIFI_RESUME_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_IOMCU_SUSPEND_CNT_OFFSET),
		readl(sysreg_base.reserved_base + PM_IOMCU_RESUME_CNT_OFFSET));

	if (sysreg_base.sysctrl_base != NULL) {
		LOWPM_MSG(s, "SR:SCINT_STAT:0x%x.\n",
				readl(sysreg_base.sysctrl_base + SCINT_STAT_OFFSET));
		LOWPM_MSG(s, "SR:SCINT_STAT1:0x%x.\n",
				readl(sysreg_base.sysctrl_base + SCINT_STAT1_OFFSET));
	}

	wake_irq = readl(sysreg_base.reserved_base + PM_WAKE_IRQ_OFFSET);
	wake_irq1 = readl(sysreg_base.reserved_base + PM_WAKE_IRQ1_OFFSET);
	LOWPM_MSG(s, "SR:WAKE_IRQ:0x%x, WAKE_IRQ1:0x%x\n", wake_irq, wake_irq1);
	for (i = 0; i < WAKE_IRQ_NUM_MAX; i++) {
		bit_shift = (1 << i);
		if ((wake_irq & AP_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(AP)\n", i);

		if ((wake_irq & IOMCU_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(IOMCU)\n", i);

		if ((wake_irq & MODEM_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(MODEM)\n", i);

		if ((wake_irq1 & MODEM_DRX_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE DRX_BIT: %d(MODEM)\n", i);

		if ((wake_irq & HIFI_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST DEEPSLEEP WAKE BIT: %d(HIFI)\n", i);
	}

	wake_irq = readl(sysreg_base.reserved_base + SLEEP_WAKE_IRQ_OFFSET);
	wake_irq1 = readl(sysreg_base.reserved_base + SLEEP_WAKE_IRQ1_OFFSET);
	for (i = 0; i < WAKE_IRQ_NUM_MAX; i++) {
		bit_shift = (1 << i);
		if ((wake_irq & AP_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST SLEEP WAKE BIT: %d(AP)\n", i);

		if ((wake_irq & IOMCU_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST SLEEP WAKE BIT: %d(IOMCU)\n", i);

		if ((wake_irq & MODEM_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST SLEEP WAKE BIT: %d(MODEM)\n", i);

		if ((wake_irq1 & MODEM_DRX_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST SLEEP WAKE DRX_BIT: %d(MODEM)\n", i);

		if ((wake_irq & HIFI_INT_MASK) & bit_shift)
			LOWPM_MSG(s, "LAST SLEEP WAKE BIT: %d(HIFI)\n", i);
	}

	ap_irq = readl(sysreg_base.reserved_base + PM_AP_WAKE_IRQ_OFFSET);
	if ((g_lpmcu_irq_num > ap_irq)
		&& (g_lpmcu_irq_name != NULL)){
		LOWPM_MSG(s, "SR:AP WAKE IRQ(LPM3 NVIC): %d (%s)\n",
				ap_irq, g_lpmcu_irq_name[ap_irq]);
	} else {
		LOWPM_MSG(s,
			"SR:AP WAKE IRQ(LPM3 NVIC): %d (no exist)\n", ap_irq);
	}
	if (IPC_COMBO_AP == ap_irq)
		combo_ipc_irq_show(s,
			readl(sysreg_base.reserved_base + PM_AP_NSIPC_IRQ_OFFSET));

	LOWPM_MSG(s, "light sleep 0x%x times,resume 0x%x times.\n",
		readl(sysreg_base.reserved_base + IDLE_SLEEP_CNT_OFFSET),
		readl(sysreg_base.reserved_base + IDLE_RESUME_CNT_OFFSET));

	LOWPM_MSG(s, "sleep 0x%x times.\n",
		readl(sysreg_base.reserved_base + SLEEP_CNT_OFFSET));
}

void set_wakelock(int iflag)
{
	if ((1 == iflag) && (0 == wake_lock_active(&lowpm_wake_lock)))
		wake_lock(&lowpm_wake_lock);
	else if ((0 == iflag) && (0 != wake_lock_active(&lowpm_wake_lock)))
		wake_unlock(&lowpm_wake_lock);
}

#define GPIO_DIR(x)		((x) + 0x400)
#define GPIO_DATA(x, y)		((x) + (1 << (2 + y)))
#define GPIO_BIT(x, y)		((x) << (y))
#define GPIO_IS_SET(x, y)	(((x) >> (y)) & 0x1)

/* check all io status */
void dbg_io_status_show(void)
{
	int i = 0;
	int gpio_id = 0;
	int value = 0;
	int	data = 0;
	unsigned int len = 0;
	void __iomem *addr, *addr1;
	struct iocfg_lp *hisi_iocfg_lookups = NULL;

	if (!(g_usavedcfg & DEBG_SUSPEND_IO_SHOW))
		return;

	hisi_iocfg_lookups = boardid_tables[0].iocfg;

	if (NULL == hisi_iocfg_lookups) {
		pr_err("%s: hisi_iocfg_lookups is null\n", __func__);
		return;
	}

	/* calc hisi_iocfg_lookups[] length */
	for (i = 0; hisi_iocfg_lookups[i].iomg_offset != CFG_END; i++)
		len = i;

	printk("io list length is %d\n", len);
	for (i = 0; i <= len; i++) {
		gpio_id = ((hisi_iocfg_lookups[i].gpio_group_id << 3)
					+ hisi_iocfg_lookups[i].ugpio_bit);

		printk("gpio - %d  gpio_logic - %s\t",
				gpio_id, hisi_iocfg_lookups[i].gpio_logic);

		/* show iomg register's value */
		if (hisi_iocfg_lookups[i].iomg_offset != -1) {
			if ((g_sec_reg_num > 0)
					&&(g_ioc_reg != NULL)) {
				addr = (void __iomem *)(unsigned long)(hisi_iocfg_lookups[i].iomg_base
								+ hisi_iocfg_lookups[i].iomg_offset);
				if (((addr >= g_ioc_reg[0]) && (addr <= g_ioc_reg[1]))
						|| ((addr >= g_ioc_reg[2]) && (addr <= g_ioc_reg[3]))
						|| ((addr >= g_ioc_reg[4]) && (addr <= g_ioc_reg[5]))
						|| ((addr >= g_ioc_reg[6]) && (addr <= g_ioc_reg[7]))) {
					printk("sec iomg, can't access!\n");
					continue;
				}
			}
			addr = ioremap(hisi_iocfg_lookups[i].iomg_base
					+ hisi_iocfg_lookups[i].iomg_offset, 0x4);
			if (NULL == addr) {
				pr_err("%s[%d]: i:%d, ioremap fail!\n", __func__, __LINE__, i);
				return;
			}
			value = readl(addr);
			iounmap(addr);
			printk("iomg = Func-%d", value);
			if (FUNC1 == value)
				printk("(%s)", hisi_iocfg_lookups[i].gpio_func1);
			if (FUNC2 == value)
				printk("(%s)", hisi_iocfg_lookups[i].gpio_func2);
			if (FUNC3 == value)
				printk("(%s)", hisi_iocfg_lookups[i].gpio_func3);

			if (value != hisi_iocfg_lookups[i].iomg_val) {
				printk(" -E [Func-%d]", hisi_iocfg_lookups[i].iomg_val);
				if (FUNC1 == hisi_iocfg_lookups[i].iomg_val)
					printk("(%s)", hisi_iocfg_lookups[i].gpio_func1);
				if (FUNC2 == hisi_iocfg_lookups[i].iomg_val)
					printk("(%s)", hisi_iocfg_lookups[i].gpio_func2);
				if (FUNC3 == hisi_iocfg_lookups[i].iomg_val)
					printk("(%s)", hisi_iocfg_lookups[i].gpio_func3);
			} else {
				printk("             ");
			}
			printk("\t");
		} else {
			printk("iomg = Null               \t");
		}

		/* show iocg register */
		if ((g_sec_reg_num > 0)
				&&(g_ioc_reg != NULL)) {
			addr = (void __iomem *)(unsigned long)(hisi_iocfg_lookups[i].iocg_base
					+ hisi_iocfg_lookups[i].iocg_offset);
			if (((addr >= g_ioc_reg[0]) && (addr <= g_ioc_reg[1]))
					|| ((addr >= g_ioc_reg[2]) && (addr <= g_ioc_reg[3]))
					|| ((addr >= g_ioc_reg[4]) && (addr <= g_ioc_reg[5]))
					|| ((addr >= g_ioc_reg[6]) && (addr <= g_ioc_reg[7]))) {
				printk("sec iocg, can't access!\n");
				continue;
			}
		}
		addr = ioremap(hisi_iocfg_lookups[i].iocg_base
				+ hisi_iocfg_lookups[i].iocg_offset, 0x4);
		if (NULL == addr) {
			pr_err("%s[%d]: i:%d, ioremap fail!\n", __func__, __LINE__, i);
			return;
		}
		value = readl(addr);
		iounmap(addr);

		printk("[0x%x]iocg = %s", value, pulltype[value&0x3]);

		if ((value != hisi_iocfg_lookups[i].iocg_val) &&
				(hisi_iocfg_lookups[i].iocg_val != -1)) {
			printk(" -E [%s]", pulltype[hisi_iocfg_lookups[i].iocg_val]);
		} else {
			printk("        ");
		}
		printk("\t");

		/* if this is gpio pin*/
		if (hisi_iocfg_lookups[i].iomg_val == FUNC0) {
			addr = GPIO_DIR(sysreg_base.gpio_base[hisi_iocfg_lookups[i].gpio_group_id]);
			addr1 = GPIO_DATA(sysreg_base.gpio_base[hisi_iocfg_lookups[i].gpio_group_id], hisi_iocfg_lookups[i].ugpio_bit);

			value = GPIO_IS_SET(readl(addr), hisi_iocfg_lookups[i].ugpio_bit);
			data = GPIO_IS_SET(readl(addr1), hisi_iocfg_lookups[i].ugpio_bit);
			printk("[0x%x 0x%x]gpio - %s", value, data, value ? "O" : "I ");

			if (value)
				printk("%s", data ? "H" : "L");

			if (value != hisi_iocfg_lookups[i].gpio_dir) {
				printk("     -E [%s", hisi_iocfg_lookups[i].gpio_dir ? "O" : "I");
				if (hisi_iocfg_lookups[i].gpio_dir && (data != hisi_iocfg_lookups[i].gpio_val))
					printk("%s", hisi_iocfg_lookups[i].gpio_val ? "H" : "L");
				printk("]");
			}

			printk("\n");
		} else {
			printk("\n");
		}

	}
}

/*****************************************************************
 * function:    dbg_pmu_status_show
 * description:
 *  show the pmu status.
 ******************************************************************/
void dbg_pmu_status_show(void)
{
	unsigned int i = 0;
	unsigned int k = 0;
	unsigned int uregv;

	if (!(g_usavedcfg & DEBG_SUSPEND_PMU_SHOW))
		return;
	printk("[%s] %d enter.\n", __func__, __LINE__);
	printk("PMU_CTRL register value list:\n");

	for (i = 0x0; i <= g_pmu_addr_end; i++) {
		uregv = readl(PMUSSI_REG(i));
		printk("PMU_CTRL 0x%02X=0x%02X", i, uregv);
		printk("\t");

		/* NOTE!! g_pmuregs_lookups[k] must be matched with g_hisi_pmu_idx[k],
		 * otherwise the array may be out of range.
		 */
		if ((k < g_lp_pmu_num)
			&& (g_hisi_pmu_idx != NULL)
			&& (g_pmuregs_lookups != NULL)
			&& (g_hisi_pmu_idx[k] != NULL)
			&& (g_pmuregs_lookups[k] != NULL)
			&& (i == g_pmuregs_lookups[k]->ucoffset)) {
			printk("[%s]", g_hisi_pmu_idx[k]->name);
			if ((uregv & g_pmuregs_lookups[k]->cmask) == g_pmuregs_lookups[k]->cval)
				printk("enabled  %s\t",
						(g_hisi_pmu_idx[k]->status & AP_DIS) ? "-E" : "");
			printk("[%s]owner:%s",
					g_hisi_pmu_idx[k]->status_name, g_hisi_pmu_idx[k]->module);
			k++;
		}

		printk("\n");
	}

	printk("[%s] %d leave.\n", __func__, __LINE__);
}


#define NULL_CLOSE	0
#define AP_CLOSE	1
#define LPM3_CLOSE	2
#define	AP_ON		3
#define AO_ON		4
#define ON_OFF		5
#define MODEM_ON	6

#define LP_CLK(_base, _offset, _bit, _clk_name, _status) \
{                               \
	.reg_base = _base, \
	.reg_off = _offset,  \
	.bit_idx    = _bit, \
	.clk_name = _clk_name,  \
	.status = _status,	\
}

void clk_showone(char *ctrl_name, int index)
{
	u32 regval = 0;
	u32	bitval = 0;
	u32 regoff = 0;
	u32 bit_idx = 0;
	void __iomem *regbase = NULL;

	if((NULL == g_clk_lookups)
		|| (NULL == g_clk_lookups[index])) {
		pr_err("%s: g_clk_lookups = NULL!\n", __func__);
		return;
	}

	switch (g_clk_lookups[index]->reg_base) {
	case SCTRLBASE:
		strncpy(ctrl_name, "SYSCTRL", sizeof(char) * 10);
		regbase = sysreg_base.sysctrl_base;
		break;
	case CRGBASE:
		strncpy(ctrl_name, "CRGPERI", sizeof(char) * 10);
		regbase = sysreg_base.crg_base;
		break;
	case PMCBASE:
		strncpy(ctrl_name, "PMCCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pctrl_base;
		break;
	case PMUBASE:
		strncpy(ctrl_name, "PMUCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pmic_base;
		g_clk_lookups[index]->reg_off =  g_clk_lookups[index]->reg_off << 2;
		break;
	}

	regoff = g_clk_lookups[index]->reg_off;
	bit_idx = g_clk_lookups[index]->bit_idx;
	regval = readl(regbase + regoff);
	bitval = regval & BIT(bit_idx);

	printk("[%s] offset:0x%x regval:0x%x bit_idx:%s%d state:%d %s",
			ctrl_name, regoff, regval, bit_idx > 9 ? "" : "0",
			bit_idx, bitval ? 1 : 0, g_clk_lookups[index]->clk_name);

	if (bitval) {
		if ((NULL_CLOSE == g_clk_lookups[index]->status)
				|| (AP_CLOSE == g_clk_lookups[index]->status))
			printk(" -E[OFF]");
	} else {
		if ((AP_ON == g_clk_lookups[index]->status)
				|| (AO_ON == g_clk_lookups[index]->status))
			printk(" -E[ON]");
	}
	if (ON_OFF == g_clk_lookups[index]->status)
		printk("[on/off]");
	if (MODEM_ON == g_clk_lookups[index]->status)
		printk("[MODEM: on or off]");

	printk("\n");
}

#define SYS_REG(_base, _offset, _reg_name) \
{                               \
	.reg_base = _base, \
	.reg_off = _offset,  \
	.reg_name = _reg_name,  \
}
static struct sys_reg sysreg_lookups[] = {
	/*sysctrlregs*/
	SYS_REG(SCTRLBASE, 0x020, "SCPPLLCTRL0"),
	SYS_REG(SCTRLBASE, 0x024, "SCPPLLCTRL1"),
	SYS_REG(SCTRLBASE, 0x028, "SCPPLLSSCCTRL"),
	SYS_REG(SCTRLBASE, 0x02C, "SCPPLLSTAT"),
	SYS_REG(SCTRLBASE, 0x038, "SCPERCLKEN0"),
	SYS_REG(SCTRLBASE, 0x048, "SCPERCLKEN1"),
	SYS_REG(SCTRLBASE, 0x088, "SCPERRSTSTAT0"),
	SYS_REG(SCTRLBASE, 0x094, "SCPERRSTSTAT1"),
	SYS_REG(SCTRLBASE, 0x0A0, "SCPERRSTSTAT2"),
	SYS_REG(SCTRLBASE, 0x0A4, "SCIPCLKRSTBUS"),
	SYS_REG(SCTRLBASE, 0x0C8, "SCISOSTAT"),
	SYS_REG(SCTRLBASE, 0x0D8, "SCPWRSTAT"),
	SYS_REG(SCTRLBASE, 0x100, "SCCLKDIV0"),
	SYS_REG(SCTRLBASE, 0x104, "SCCLKDIV1"),
	SYS_REG(SCTRLBASE, 0x108, "SCCLKDIV2"),
	SYS_REG(SCTRLBASE, 0x10C, "SCCLKDIV3"),
	SYS_REG(SCTRLBASE, 0x110, "SCCLKDIV4"),
	SYS_REG(SCTRLBASE, 0x114, "SCCLKDIV5"),
	SYS_REG(SCTRLBASE, 0x204, "SCPERCTRL1"),
	SYS_REG(SCTRLBASE, 0x208, "SCPERCTRL2"),
	SYS_REG(SCTRLBASE, 0x20C, "SCPERCTRL3"),
	SYS_REG(SCTRLBASE, 0x21C, "SCPERSTATUS0"),
	SYS_REG(SCTRLBASE, 0x220, "SCPERSTATUS1"),
	SYS_REG(SCTRLBASE, 0x224, "SCPERSTATUS2"),
	SYS_REG(SCTRLBASE, 0x228, "SCPERSTATUS3"),
	SYS_REG(SCTRLBASE, 0x22C, "SCPERSTATUS4"),
	SYS_REG(SCTRLBASE, 0x300, "SCDEEPSLEEPED"),
	SYS_REG(SCTRLBASE, 0x304, "SCMRBBUSYSTAT"),
	SYS_REG(SCTRLBASE, 0x314, "SCBAKDATA0"),
	SYS_REG(SCTRLBASE, 0x318, "SCBAKDATA1"),
	SYS_REG(SCTRLBASE, 0x31C, "SCBAKDATA2"),
	SYS_REG(SCTRLBASE, 0x320, "SCBAKDATA3"),
	SYS_REG(SCTRLBASE, 0x324, "SCBAKDATA4"),
	SYS_REG(SCTRLBASE, 0x328, "SCBAKDATA5"),
	SYS_REG(SCTRLBASE, 0x32C, "SCBAKDATA6"),
	SYS_REG(SCTRLBASE, 0x330, "SCBAKDATA7"),
	SYS_REG(SCTRLBASE, 0x334, "SCBAKDATA8"),
	SYS_REG(SCTRLBASE, 0x338, "SCBAKDATA9"),
	SYS_REG(SCTRLBASE, 0x33C, "SCBAKDATA10"),
	SYS_REG(SCTRLBASE, 0x340, "SCBAKDATA11"),
	SYS_REG(SCTRLBASE, 0x344, "SCBAKDATA12"),
	SYS_REG(SCTRLBASE, 0x348, "SCBAKDATA13"),
	SYS_REG(SCTRLBASE, 0x34C, "SCBAKDATA14"),
	SYS_REG(SCTRLBASE, 0x350, "SCBAKDATA15"),
	SYS_REG(SCTRLBASE, 0x450, "SCINT_GATHER_STAT"),
	SYS_REG(SCTRLBASE, 0x454, "SCINT_MASK"),
	SYS_REG(SCTRLBASE, 0x458, "SCINT_STAT"),
	SYS_REG(SCTRLBASE, 0x45C, "SCDRX_INT_CFG"),
	SYS_REG(SCTRLBASE, 0x460, "SCLPM3WFI_INT_CLR"),
	SYS_REG(SCTRLBASE, 0x48C, "SCMALIBYPCFG"),
	SYS_REG(SCTRLBASE, 0x500, "SCLPM3CLKEN"),
	SYS_REG(SCTRLBASE, 0x50C, "SCLPM3RSTSTAT"),
	SYS_REG(SCTRLBASE, 0x510, "SCLPM3CTRL"),
	SYS_REG(SCTRLBASE, 0x514, "SCLPM3STAT"),
	SYS_REG(SCTRLBASE, 0x518, "SCLPM3RAMCTRL"),
	SYS_REG(SCTRLBASE, 0x530, "SCBBPDRXSTAT0"),
	SYS_REG(SCTRLBASE, 0x550, "SCA7_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x554, "SCA15_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x558, "SCIOM3_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x55C, "SCLPM3_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x560, "SCMCPU_EVENT_MASK"),
	SYS_REG(SCTRLBASE, 0x564, "SCEVENT_STAT"),
	/*crgperiregs*/
	SYS_REG(CRGBASE, 0x008, "PERCLKEN0"),
	SYS_REG(CRGBASE, 0x018, "PERCLKEN1"),
	SYS_REG(CRGBASE, 0x028, "PERCLKEN2"),
	SYS_REG(CRGBASE, 0x038, "PERCLKEN3"),
	SYS_REG(CRGBASE, 0x048, "PERCLKEN4"),
	SYS_REG(CRGBASE, 0x058, "PERCLKEN5"),
	SYS_REG(CRGBASE, 0x068, "PERRSTSTAT0"),
	SYS_REG(CRGBASE, 0x074, "PERRSTSTAT1"),
	SYS_REG(CRGBASE, 0x080, "PERRSTSTAT2"),
	SYS_REG(CRGBASE, 0x08C, "PERRSTSTAT3"),
	SYS_REG(CRGBASE, 0x098, "PERRSTSTAT4"),
	SYS_REG(CRGBASE, 0x0A8, "CLKDIV0"),
	SYS_REG(CRGBASE, 0x0AC, "CLKDIV1"),
	SYS_REG(CRGBASE, 0x0B0, "CLKDIV2"),
	SYS_REG(CRGBASE, 0x0B4, "CLKDIV3"),
	SYS_REG(CRGBASE, 0x0B8, "CLKDIV4"),
	SYS_REG(CRGBASE, 0x0BC, "CLKDIV5"),
	SYS_REG(CRGBASE, 0x0C0, "CLKDIV6"),
	SYS_REG(CRGBASE, 0x0C4, "CLKDIV7"),
	SYS_REG(CRGBASE, 0x0C8, "CLKDIV8"),
	SYS_REG(CRGBASE, 0x0CC, "CLKDIV9"),
	SYS_REG(CRGBASE, 0x0D0, "CLKDIV10"),
	SYS_REG(CRGBASE, 0x0D4, "CLKDIV11"),
	SYS_REG(CRGBASE, 0x0D8, "CLKDIV12"),
	SYS_REG(CRGBASE, 0x0DC, "CLKDIV13"),
	SYS_REG(CRGBASE, 0x0E0, "CLKDIV14"),
	SYS_REG(CRGBASE, 0x0E4, "CLKDIV15"),
	SYS_REG(CRGBASE, 0x0E8, "CLKDIV16"),
	SYS_REG(CRGBASE, 0x0EC, "CLKDIV17"),
	SYS_REG(CRGBASE, 0x0F0, "CLKDIV18"),
	SYS_REG(CRGBASE, 0x0F4, "CLKDIV19"),
	SYS_REG(CRGBASE, 0x0F8, "CLKDIV20"),
	SYS_REG(CRGBASE, 0x0FC, "CLKDIV21"),
	SYS_REG(CRGBASE, 0x100, "CLKDIV22"),
	SYS_REG(CRGBASE, 0x104, "CLKDIV23"),
	SYS_REG(CRGBASE, 0x108, "CLKDIV24"),
	SYS_REG(CRGBASE, 0x10C, "CLKDIV25"),
	SYS_REG(CRGBASE, 0x114, "PER_STAT1"),
	SYS_REG(CRGBASE, 0x118, "PER_STAT2"),
	SYS_REG(CRGBASE, 0x11C, "PER_STAT3"),
	SYS_REG(CRGBASE, 0x120, "PERCTRL0"),
	SYS_REG(CRGBASE, 0x124, "PERCTRL1"),
	SYS_REG(CRGBASE, 0x128, "PERCTRL2"),
	SYS_REG(CRGBASE, 0x12C, "PERCTRL3"),
	SYS_REG(CRGBASE, 0x130, "PERCTRL4"),
	SYS_REG(CRGBASE, 0x134, "PERCTRL5"),
	SYS_REG(CRGBASE, 0x138, "PERCTRL6"),
	SYS_REG(CRGBASE, 0x140, "PERTIMECTRL"),
	SYS_REG(CRGBASE, 0x14C, "ISOSTAT"),
	SYS_REG(CRGBASE, 0x158, "PERPWRSTAT"),
	SYS_REG(CRGBASE, 0x160, "A53CLKEN"),
	SYS_REG(CRGBASE, 0x16C, "A53RSTSTAT"),
	SYS_REG(CRGBASE, 0x174, "A53ADBLPSTAT"),
	SYS_REG(CRGBASE, 0x178, "A53CTRL0"),
	SYS_REG(CRGBASE, 0x17C, "A53CTRL1"),
	SYS_REG(CRGBASE, 0x180, "A53CTRL2"),
	SYS_REG(CRGBASE, 0x194, "A53STAT"),
	SYS_REG(CRGBASE, 0x1C0, "MAIACLKEN"),
	SYS_REG(CRGBASE, 0x1CC, "MAIARSTSTAT"),
	SYS_REG(CRGBASE, 0x1D4, "MAIAADBLPSTAT"),
	SYS_REG(CRGBASE, 0x1D8, "MAIACTRL0"),
	SYS_REG(CRGBASE, 0x1DC, "MAIACTRL1"),
	SYS_REG(CRGBASE, 0x1E0, "MAIACTRL2"),
	SYS_REG(CRGBASE, 0x1F4, "MAIASTAT"),

	SYS_REG(CRGBASE, 0x204, "CORESIGHTLPSTAT"),
	SYS_REG(CRGBASE, 0x208, "CORESIGHTCTRL0"),
	SYS_REG(CRGBASE, 0x20C, "CORESIGHTETFINT"),
	SYS_REG(CRGBASE, 0x210, "CORESIGHTETRINT"),

	SYS_REG(CRGBASE, 0x21C, "CCI400STAT1"),
	SYS_REG(CRGBASE, 0x220, "ADB400STAT"),
	SYS_REG(CRGBASE, 0x228, "CCI400CTRL0"),
	SYS_REG(CRGBASE, 0x22C, "CCI400CTRL1"),
	SYS_REG(CRGBASE, 0x230, "CCI400STAT"),
	SYS_REG(CRGBASE, 0x234, "G3D_0_ADBLPSTAT"),
	SYS_REG(CRGBASE, 0x238, "G3D_1_ADBLPSTAT"),
	/*pmctrlregs*/
	SYS_REG(PMCBASE, 0x004, "PMCINTSTAT"),
	SYS_REG(PMCBASE, 0x00C, "PMCSTATUS"),
	SYS_REG(PMCBASE, 0x010, "APLL0CTRL0"),
	SYS_REG(PMCBASE, 0x014, "APLL0CTRL1"),
	SYS_REG(PMCBASE, 0x018, "APLL1CTRL0"),
	SYS_REG(PMCBASE, 0x01C, "APLL1CTRL1"),
	SYS_REG(PMCBASE, 0x020, "APLL2CTRL0"),
	SYS_REG(PMCBASE, 0x024, "APLL2CTRL1"),
	SYS_REG(PMCBASE, 0x038, "PPLL1CTRL0"),
	SYS_REG(PMCBASE, 0x03C, "PPLL1CTRL1"),
	SYS_REG(PMCBASE, 0x040, "PPLL2CTRL0"),
	SYS_REG(PMCBASE, 0x044, "PPLL2CTRL1"),
	SYS_REG(PMCBASE, 0x048, "PPLL3CTRL0"),
	SYS_REG(PMCBASE, 0x04C, "PPLL3CTRL1"),
	SYS_REG(PMCBASE, 0x070, "APLL0SSCCTRL"),
	SYS_REG(PMCBASE, 0x074, "APLL1SSCCTRL"),
	SYS_REG(PMCBASE, 0x078, "APLL2SSCCTRL"),
	SYS_REG(PMCBASE, 0x084, "PPLL1SSCCTRL"),
	SYS_REG(PMCBASE, 0x088, "PPLL2SSCCTRL"),
	SYS_REG(PMCBASE, 0x08C, "PPLL3SSCCTRL"),
	/*pctrlregs*/
	SYS_REG(PCTRLBASE, 0x408, "RESOURCE0_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x414, "RESOURCE1_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x420, "RESOURCE2_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x42C, "RESOURCE3_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x808, "RESOURCE4_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x814, "RESOURCE5_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x820, "RESOURCE6_LOCK_ST"),
	SYS_REG(PCTRLBASE, 0x82C, "RESOURCE7_LOCK_ST"),
};

#define SYSREG_LIST_LENGTH	\
		(int)(sizeof(sysreg_lookups)/sizeof(sysreg_lookups[0]))

void sysreg_showone(char *ctrl_name, int index)
{
	u32 regval = 0;
	u32 regoff = 0;
	void __iomem *regbase = NULL;

	switch (sysreg_lookups[index].reg_base) {
	case SCTRLBASE:
		strncpy(ctrl_name, "SYSCTRL", sizeof(char) * 10);
		regbase = sysreg_base.sysctrl_base;
		break;
	case CRGBASE:
		strncpy(ctrl_name, "CRGPERI", sizeof(char) * 10);
		regbase = sysreg_base.crg_base;
		break;
	case PCTRLBASE:
		strncpy(ctrl_name, "PCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pctrl_base;
		break;
	case PMCBASE:
		strncpy(ctrl_name, "PMCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pmctrl_base;
		break;
	case PMUBASE:
		strncpy(ctrl_name, "PMUCTRL", sizeof(char) * 10);
		regbase = sysreg_base.pmic_base;
		sysreg_lookups[index].reg_off = sysreg_lookups[index].reg_off << 2;
		break;
	default:
		pr_err("%s not exist the ip defined field\n",
				__func__);
		return;
	}

	regoff = sysreg_lookups[index].reg_off;
	regval = readl(regbase + regoff);

	pr_info("[%7s]%s [%17s]%s [0x%3x]%s  val = 0x%x\n",
			ctrl_name, "", sysreg_lookups[index].reg_name, "", regoff, "", regval);

}

void hisi_sysregs_dump(void)
{
	int i = 0;
	char *ctrl_name;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	ctrl_name = kzalloc(sizeof(char) * 10, GFP_ATOMIC);
	if (!ctrl_name) {
		pr_err("Cannot allocate ctrl_name.\n");
		return;
	}

	for (i = 0; i < SYSREG_LIST_LENGTH; i++)
		sysreg_showone(ctrl_name, i);

	kfree(ctrl_name);
	ctrl_name = NULL;

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}
EXPORT_SYMBOL_GPL(hisi_sysregs_dump);

/*****************************************************************
 * function:    dbg_clk_status_show
 * description:
 *  show the clk status.
 ******************************************************************/
void dbg_clk_status_show(void)
{
	int i = 0;
	char *ctrl_name;
	unsigned int clk_list_len = g_lp_clk_num;

	if (!(g_usavedcfg & DEBG_SUSPEND_CLK_SHOW))
		return;
	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	ctrl_name = kzalloc(sizeof(char) * 10, GFP_KERNEL);
	if (!ctrl_name) {
		pr_err("%s: Cannot allocate clk_name.\n", __func__);
		return;
	}

	for (i = 0; i < clk_list_len; i++)
		clk_showone(ctrl_name, i);

	kfree(ctrl_name);

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}




static int init_pmu_table(void)
{
	int ret = 0;
	u32 i = 0;
	struct device_node *np = NULL;
	char *buffer = NULL;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,lowpm_func");
	if (!np) {
		pr_err("%s[%d]: hisilicon,lowpm_func No compatible node found\n",
				__func__, __LINE__);
		ret = -ENODEV;
		goto err;
	}

	ret = of_property_read_u32(np, "pmu-addr-end", &g_pmu_addr_end);
	if (ret) {
		pr_err("%s[%d], no pmu-addr-end!\n", __func__, __LINE__);
		ret = -ENODEV;
		goto err_put_node;
	}

	buffer = kmalloc(BUFFER_LENGTH * sizeof(char), GFP_KERNEL);
	if (NULL == buffer) {
		pr_err("%s: buffer kmalloc fail.\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	/* find lp_pmu max num */
	i = 0;
	while (1) {
		memset(buffer, 0, BUFFER_LENGTH * sizeof(char));
		snprintf(buffer, BUFFER_LENGTH * sizeof(char),
				"hisilicon, lp_pmu%d", i);
		np = of_find_compatible_node(NULL, NULL, buffer);
		if (!np) {
			pr_err("%s[%d]: lp_pmu%d not find.\n", __func__, __LINE__, i);
			ret = -ENODEV;
			break;
		}
		i++;
	}
	g_lp_pmu_num = i;
	pr_info("%s: find lp pmu num: %u\n", __func__, g_lp_pmu_num);

	g_hisi_pmu_idx = kzalloc(g_lp_pmu_num * sizeof(struct pmu_idx *), GFP_KERNEL);
	if (!g_hisi_pmu_idx) {
		pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
		ret = -ENOMEM;
		goto err_free_buffer;
	}
	g_pmuregs_lookups = kzalloc(g_lp_pmu_num * sizeof(struct pmuregs *), GFP_KERNEL);
	if (!g_pmuregs_lookups) {
		pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
		ret = -ENOMEM;
		goto err_free_pmu_idx;
	}

	/* init pmu idx and lookup table */
	for (i = 0; i < g_lp_pmu_num; i++) {
		memset(buffer, 0, BUFFER_LENGTH * sizeof(char));
		snprintf(buffer, BUFFER_LENGTH * sizeof(char),
				"hisilicon, lp_pmu%d", i);
		np = of_find_compatible_node(NULL, NULL, buffer);
		if (!np) {
			pr_err("%s[%d]: lp_pmu%d not find.\n", __func__, __LINE__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		g_hisi_pmu_idx[i] = kzalloc(sizeof(struct pmu_idx), GFP_KERNEL);
		if (!g_hisi_pmu_idx[i]) {
			pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
			ret = -ENOMEM;
			goto err_free_lookups;
		}
		ret = of_property_read_string(np, "lp-pmu-name", &(g_hisi_pmu_idx[i]->name));
		if (ret) {
			pr_err("%s, [%d]no lp-pmu-name!\n", __func__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		ret = of_property_read_string(np, "lp-pmu-module", &(g_hisi_pmu_idx[i]->module));
		if (ret) {
			pr_err("%s, [%d]no lp-pmu-module!\n", __func__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		ret = of_property_read_u32(np, "lp-pmu-status-value", &(g_hisi_pmu_idx[i]->status));
		if (ret) {
			pr_err("%s, [%d]no lp-pmu-module!\n", __func__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		ret = of_property_read_string(np, "lp-pmu-status", &(g_hisi_pmu_idx[i]->status_name));
		if (ret) {
			pr_err("%s, [%d]no lp-pmu-status!\n", __func__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		g_pmuregs_lookups[i] = kzalloc(sizeof(struct pmuregs), GFP_KERNEL);
		if (!g_pmuregs_lookups[i]) {
			pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
			ret = -ENOMEM;
			goto err_free_lookups;
		}
		ret = of_property_read_u32(np, "offset", &(g_pmuregs_lookups[i]->ucoffset));
		if (ret) {
			pr_err("%s, [%d]no offset!\n", __func__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		ret = of_property_read_u32(np, "mask", &(g_pmuregs_lookups[i]->cmask));
		if (ret) {
			pr_err("%s, [%d]no mask!\n", __func__, i);
			ret = -ENODEV;
			goto err_free_lookups;
		}
		g_pmuregs_lookups[i]->cval = g_pmuregs_lookups[i]->cmask;

	}

	kfree(buffer);

	pr_info("%s, init pmu table success.\n", __func__);

	return ret;

err_free_lookups:
	kfree(g_pmuregs_lookups);
	g_pmuregs_lookups = NULL;
err_free_pmu_idx:
	kfree(g_hisi_pmu_idx);
	g_hisi_pmu_idx = NULL;
err_free_buffer:
	kfree(buffer);
	buffer = NULL;
err_put_node:
	of_node_put(np);
err:
	pr_err("%s init failed.\n", __func__);
	return ret;
}

static int init_clk_table(void)
{
	int ret = 0;
	u32 i = 0;
	u32 j = 0;
	u32 k = 0;
	u32 reg_base = 0;
	u32 reg_offset = 0;
	u32 bit_num = 0;
	u32 clk_reg_num = 0;
	struct device_node *np = NULL;
	char *buffer = NULL;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,lowpm_func");
	if (!np) {
		pr_err("%s: hisilicon,lowpm_func No compatible node found\n",
				__func__);
		ret = -ENODEV;
		goto err;
	}

	buffer = kmalloc(BUFFER_LENGTH * sizeof(char), GFP_KERNEL);
	if (NULL == buffer) {
		pr_err("%s: buffer kmalloc fail.\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	/* find lp_clk max num */
	i = 0;
	while (1) {
		memset(buffer, 0, BUFFER_LENGTH * sizeof(char));
		snprintf(buffer, BUFFER_LENGTH * sizeof(char),
				"hisilicon, lp_clk%d", i);
		np = of_find_compatible_node(NULL, NULL, buffer);
		if (!np) {
			pr_err("%s[%d]: lp_clk%d not find.\n", __func__, __LINE__, i);
			break;
		}
		ret = of_property_read_u32(np, "bit-num", &bit_num);
		if (ret) {
			pr_err("%s, [%d]no bit-num!\n", __func__, i);
			goto err_free_buffer;
		}
		g_lp_clk_num += bit_num;
		i++;
	}
	clk_reg_num = i;
	pr_info("%s: find lp clk num: %u, lp clk reg num: %u\n",
				__func__, g_lp_clk_num, clk_reg_num);

	g_clk_lookups = kzalloc(g_lp_clk_num * sizeof(struct lp_clk *), GFP_KERNEL);
	if (!g_clk_lookups) {
		pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
		ret = -ENOMEM;
		goto err_free_buffer;
	}

	/* init lp clk table */
	for (i = 0; i < clk_reg_num; i++) {
		if (k >= g_lp_clk_num) {
			pr_err("%s[%d]: k >= g_lp_clk_num, k:%d,i:%d!\n",
					__func__, __LINE__, k, i);
			goto err_free_lookups;
		}
		memset(buffer, 0, BUFFER_LENGTH * sizeof(char));
		snprintf(buffer, BUFFER_LENGTH * sizeof(char),
				"hisilicon, lp_clk%d", i);
		np = of_find_compatible_node(NULL, NULL, buffer);
		if (!np) {
			pr_err("%s[%d]: lp_clk%d not find.\n", __func__, __LINE__, i);
			goto err_free_lookups;
		}
		ret = of_property_read_u32(np, "lp-clk-base", &reg_base);
		if (ret) {
			pr_err("%s, [%d]no lp-clk-base!\n", __func__, i);
			goto err_free_lookups;
		}
		ret = of_property_read_u32(np, "offset", &reg_offset);
		if (ret) {
			pr_err("%s, [%d]no offset!\n", __func__, i);
			goto err_free_lookups;
		}
		ret = of_property_read_u32(np, "bit-num", &bit_num);
		if (ret) {
			pr_err("%s, [%d]no bit-num!\n", __func__, i);
			goto err_free_lookups;
		}

		for (j = 0; j < bit_num; j++) {
			g_clk_lookups[k] = kzalloc(sizeof(struct lp_clk), GFP_KERNEL);
			if (!g_clk_lookups[k]) {
				pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
				ret = -ENOMEM;
				goto err_free_lookups;
			}

			g_clk_lookups[k]->reg_base = reg_base;
			g_clk_lookups[k]->reg_off = reg_offset;
			g_clk_lookups[k]->bit_idx = j;

			ret = of_property_read_string_index(np, "lp-clk-name", j, &(g_clk_lookups[k]->clk_name));
			if (ret) {
				pr_err("%s, [%d %d]no lp-clk-name!\n", __func__, i, j);
				goto err_free_lookups;
			}

			ret = of_property_read_u32_index(np, "lp-clk-status-value", j, &(g_clk_lookups[k]->status));
			if (ret) {
				pr_err("%s, [%d %d]no lp-clk-status-value!\n", __func__, i, j);
				goto err_free_lookups;
			}

			k++;
		}

	}

	kfree(buffer);

	pr_info("%s, init clk table success.\n", __func__);

	return ret;

err_free_lookups:
	kfree(g_clk_lookups);
	g_clk_lookups = NULL;
err_free_buffer:
	kfree(buffer);
	buffer = NULL;
err_put_node:
	of_node_put(np);
err:
	pr_err("%s init failed.\n", __func__);
	return ret;
}

static int init_lowpm_data(void)
{
	int ret = 0;
	u32 i = 0;
	struct device_node *np = NULL;
	const char *plat_name = NULL;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,lowpm_func");
	if (!np) {
		pr_err("%s: hisilicon,lowpm_func No compatible node found\n",
				__func__);
		ret = -ENODEV;
		goto err;
	}

	ret = of_property_read_string(np, "plat-name", &plat_name);
	if (ret) {
		pr_err("%s[%d], no plat-name!\n", __func__, __LINE__);
		ret = -ENODEV;
		goto err_put_node;
	}

	if (!strncmp("hi3660", plat_name, strlen(plat_name))) {
		/* find ioc sec reg range */
		g_sec_reg_num = of_property_count_u32_elems(np, "sec-reg");
		if (g_sec_reg_num < 0) {
			pr_err("%s[%d], no sec-reg!\n", __func__, __LINE__);
			ret = -ENODEV;
			goto err_put_node;
		}
		pr_info("%s[%d], find sec-reg num: %d\n", __func__, __LINE__, g_sec_reg_num);
		g_ioc_reg = kzalloc(g_sec_reg_num * sizeof(void __iomem *), GFP_KERNEL);
		if (!g_ioc_reg) {
			pr_err("%s[%d]: kzalloc err!!\n", __func__, __LINE__);
			ret = -ENOMEM;
			goto err_put_node;
		}
		for (i = 0; i < g_sec_reg_num; i++) {
			ret = of_property_read_u32_index(np, "sec-reg", i, (u32 *) &g_ioc_reg[i]);
			if (ret) {
				pr_err("%s[%d], i = %d, no sec-reg!\n", __func__, __LINE__, i);
				ret = -ENODEV;
				goto err_free_ioc;
			}
		}
	}

	/* init lpmcu irq table */
	ret = of_property_count_strings(np, "lpmcu-irq-table");
	if (ret < 0) {
		pr_err("%s, not find irq-table property!\n", __func__);
		goto err_free_ioc;
	}

	g_lpmcu_irq_num = ret;
	pr_info("%s, lpmcu-irq-table num: %d!\n", __func__, g_lpmcu_irq_num);

	g_lpmcu_irq_name = kzalloc(g_lpmcu_irq_num * sizeof(char *), GFP_KERNEL);
	if (!g_lpmcu_irq_name) {
		pr_err("%s: kzalloc err!!\n", __func__);
		ret = -ENOMEM;
		goto err_free_ioc;
	}

	for (i = 0; i < g_lpmcu_irq_num; i++) {
		ret = of_property_read_string_index(np, "lpmcu-irq-table",
				i, &g_lpmcu_irq_name[i]);
		if (ret) {
			pr_err("%s, no lpmcu-irq-table %d!\n", __func__, i);
			goto err_free;
		}
	}

	ret = init_pmu_table();
	if (ret)
		goto err_free;

	ret = init_clk_table();
	if (ret)
		goto err_free;

	pr_info("%s, init lowpm data success.\n", __func__);

	return ret;

err_free:
	kfree(g_lpmcu_irq_name);
	g_lpmcu_irq_name = NULL;
err_free_ioc:
	kfree(g_ioc_reg);
	g_ioc_reg = NULL;
err_put_node:
	of_node_put(np);
err:
	pr_err("%s: init fail!\n", __func__);
	return ret;
}

/*****************************************************************
 * function:    lowpm_func_probe
 * description:
 *  driver interface.
 ******************************************************************/
static int lowpm_func_probe(struct platform_device *pdev)
{
	int ret = 0;


	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	g_suspended = 0;

	ret = map_sysregs();
	if (ret)
		goto err;
	ret = map_io_regs();
	if (ret)
		goto err;
	ret = init_lowpm_data();
	if (ret)
		goto err;

	wake_lock_init(&lowpm_wake_lock, WAKE_LOCK_SUSPEND, "lowpm_func");



	pr_info("[%s] %d leave.\n", __func__, __LINE__);

	return ret;

err:
	pr_err("%s: fail!\n", __func__);
	return ret;
}

/*****************************************************************
 * function:    lowpm_func_remove
 * description:
 *  driver interface.
 ******************************************************************/
static int lowpm_func_remove(struct platform_device *pdev)
{
	return 0;
}

static int lowpm_func_suspend(struct platform_device *pdev,
		pm_message_t state)
{
	g_suspended = 1;
	return 0;
}

static int lowpm_func_resume(struct platform_device *pdev)
{
	g_suspended = 0;
	return 0;
}

#define MODULE_NAME		"hisilicon,lowpm_func"

static const struct of_device_id lowpm_func_match[] = {
	{ .compatible = MODULE_NAME },
	{},
};

static struct platform_driver lowpm_func_drv = {
	.probe		= lowpm_func_probe,
	.remove		= lowpm_func_remove,
	.suspend	= lowpm_func_suspend,
	.resume		= lowpm_func_resume,
	.driver = {
		.name	= MODULE_NAME,
		.of_match_table = of_match_ptr(lowpm_func_match),
	},
};

static int __init lowpmreg_init(void)
{
	return platform_driver_register(&lowpm_func_drv);
}

static void __exit lowpmreg_exit(void)
{
	platform_driver_unregister(&lowpm_func_drv);
}


module_init(lowpmreg_init);
module_exit(lowpmreg_exit);
