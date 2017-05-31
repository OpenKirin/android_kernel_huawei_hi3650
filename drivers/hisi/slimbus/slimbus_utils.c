/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/mutex.h>

#include <linux/delay.h>

#include "slimbus_utils.h"
#include "hi3630_asp_common.h"

/*lint -e838 -e715*/

#define SLIMBUS_CLK_24576 (24576)
#define SLIMBUS_CLK_21777 (21777)
static int slimbus_freq_cnt = 0;
static struct mutex slimbus_freq_mutex;
static void __iomem *asp_reg_base_addr;
static int clk_asp_subsys = 480000;

static void slimbus_reg_write(void __iomem *reg_addr, unsigned int value)
{
	writel(value, reg_addr);
}

static void slimbus_reg_set_bit(void __iomem *reg_addr, unsigned int offset){
	unsigned int value = 0;
	value = readl(reg_addr);
	value |= (1 << offset);
	writel(value, reg_addr);
}


static void slimbus_reg_write_bits(void __iomem *reg_addr, unsigned int value, unsigned int mask)
{
	unsigned int val = 0;

	val = readl(reg_addr);
	val &= (~mask);
	val |= (value & mask);
	writel(val, reg_addr);
}

uint32_t slimbus_port_state_get(void __iomem *slimbus_base_addr)
{
	uint32_t portstate = 0;
	uint32_t result = 0;
	uint32_t port = 0;
	for (port=0; port<HI6402_SLIMBUS_PORT_NUM; port++) {
		portstate = readl((slimbus_base_addr + SLIMBUS_PORT_BASE_ADDR) + (port*SLIMBUS_PORT_OFFSET));
		result |= ((portstate & SLIMBUS_PORT_ACTIVE)<<port);
	}
	return result;
}

static unsigned int get_clk_asp_div(uint64_t target_freq)
{
	unsigned int param;

	/* target_freq = (param * clk_asp_subsys)  / (2 * pow(2, 27) */
	param = (unsigned int)((target_freq*2*0x8000000)/clk_asp_subsys);

	return param;
}

void slimbus_freq_request()
{
	unsigned int div_siobclk = get_clk_asp_div(SLIMBUS_CLK_24576);

	if (NULL == asp_reg_base_addr) {
		pr_err("slimbus_utils not init\n");
		return;
	}

	mutex_lock(&slimbus_freq_mutex);
	slimbus_freq_cnt++;

	/* When anyone request, Slimbus clk change to 24.576M */
	if (slimbus_freq_cnt == 1) {
		slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CLK1_DIV_REG), div_siobclk);
	}
	mutex_unlock(&slimbus_freq_mutex);
}
EXPORT_SYMBOL(slimbus_freq_request);

void slimbus_freq_release()
{
	unsigned int div_siobclk = get_clk_asp_div(SLIMBUS_CLK_21777);

	if (NULL == asp_reg_base_addr) {
		pr_err("slimbus_utils not init\n");
		return;
	}

	mutex_lock(&slimbus_freq_mutex);
	if (slimbus_freq_cnt >= 1) {
		slimbus_freq_cnt--;
	} else {
		pr_err("slimbus_freq_release err: slimbus_freq_cnt:%d\n", slimbus_freq_cnt);
	}

	/* When all req released, Slimbus clk change to 21.777 to avoid signal interference to GPS*/
	if (slimbus_freq_cnt == 0) {
		slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CLK1_DIV_REG), div_siobclk);
	}
	mutex_unlock(&slimbus_freq_mutex);
}
EXPORT_SYMBOL(slimbus_freq_release);

uint32_t slimbus_asp_state_get(void __iomem *asppower_base_addr, uint32_t offset)
{
	uint32_t aspreg = 0;

	if (asppower_base_addr) {
		aspreg = readl(asppower_base_addr + offset);
	}

	return aspreg;
}

void slimbus_module_enable(slimbus_device_info_t *dev, bool enable)
{
	slimbus_rf_type_t	rf	= dev->rf;
	void __iomem * ioc_base_addr  = 0;
	unsigned int div_siobclk = get_clk_asp_div(SLIMBUS_CLK_21777);

	if (NULL == asp_reg_base_addr) {
		pr_err("slimbus_utils not init\n");
		return;
	}

	if (enable) {
		ioc_base_addr = ioremap(IOC_BASE_ADDR, IOC_REG_SIZE);
		if (NULL == ioc_base_addr) {
			pr_info("ioc_base_addr remap error\n");
			return;
		}

		/* For FPGA */
		if (SLIMBUS_RF_6144 == rf) {
			/* IOMG slimbus clk*/
			slimbus_reg_write((void __iomem *)((uint64_t)ioc_base_addr + IOC_SYS_IOMG_011), 0x00000001);
			/* IOMG slimbus data*/
			slimbus_reg_write((void __iomem *)((uint64_t)ioc_base_addr + IOC_SYS_IOMG_012), 0x00000001);
		}

		/* IOCG slimbus clk drv 6ma slew rate*/
		slimbus_reg_write((void __iomem *)((uint64_t)ioc_base_addr + IOC_SYS_IOCG_013), dev->slimbusclk_drv);
		/* IOCG slimbus data drv 6ma pu pd*/
		slimbus_reg_write((void __iomem *)((uint64_t)ioc_base_addr + IOC_SYS_IOCG_014), dev->slimbusdata_drv);
		iounmap(ioc_base_addr);

		slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_RST_CTRLDIS_REG),		0xffffffff);
		slimbus_reg_write_bits((asp_reg_base_addr + HI3630_CFG_R_GATE_EN_REG),		0x1030800, 0x1030800);
		slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CG_EN_REG), 			0x0fff0fff);

		/*bit2:gt_siobclk_div bit7:gt_asp_tcxo_div bit8:gt_slimbus_clk_div	*/
		slimbus_reg_write_bits((asp_reg_base_addr + HI3630_CFG_R_GATE_CLKDIV_EN_REG),	0x184, 0x184);

		/* clock select and div param set */
		if (SLIMBUS_RF_24576 == rf) {
			/* SRC 480M divided to 43.55556M to avoid signal interference to GPS */
			slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CLK1_DIV_REG),		   div_siobclk);

			/* Sel 480M_clk as clk src*/
			slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CLK_SEL_REG),			0x700070);

			/* bit24:gt_clk_ppll0_slimbus disable */
			slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_GATE_DIS_REG),		 0x1000000);
		} else if (SLIMBUS_RF_6144 == rf) {
			slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CLK1_DIV_REG),			0x68db8c);
			slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_CLK_SEL_REG),			0x600060);
		}

		/* copyright information */
		slimbus_reg_write((asp_reg_base_addr + HI3630_CFG_R_SLIMBUS_ID),			0xaaaa);

		/* interupt enable */
		slimbus_reg_set_bit((asp_reg_base_addr + HI3630_CFG_R_INTR_NS_EN_REG),		ASP_CFG_SLIMBUS_INTR_MASK_OFFSET);
	} else {
		slimbus_reg_write_bits(asp_reg_base_addr + HI3630_CFG_R_GATE_DIS_REG, 0x30000, 0x30000);
	}

}

void slimbus_utils_init(void __iomem * addr, int src_freq)
{
	asp_reg_base_addr = addr;
	clk_asp_subsys = src_freq;
	mutex_init(&slimbus_freq_mutex);
}

void slimbus_utils_deinit(void)
{
	asp_reg_base_addr = NULL;
	mutex_destroy(&slimbus_freq_mutex);
}

