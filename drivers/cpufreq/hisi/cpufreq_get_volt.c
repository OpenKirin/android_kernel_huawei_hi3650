/*
 * Hisilicon Platforms GET_CPU_VOLT support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/export.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/types.h>
#include <linux/string.h>
#include <global_ddr_map.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/compiler.h>
#include <asm/compiler.h>

#define CPU_VOLT_FN_GET_VAL				(0xc800aa01)
#define AVS_VOLT_MAX_BYTE				(192)

struct tag_cpu_volt_data {
	phys_addr_t phy_addr;
	unsigned char *virt_addr;
	struct mutex cpu_mutex;
};

static struct tag_cpu_volt_data g_cpu_volt_data;

noinline int atfd_hisi_service_get_val_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
	asm volatile (
		__asmeq("%0", "x0")
		__asmeq("%1", "x1")
		__asmeq("%2", "x2")
		__asmeq("%3", "x3")
		"smc	#0\n"
		: "+r" (function_id)
		: "r" (arg0), "r" (arg1), "r" (arg2));

	return (int)function_id;
}
/*********************************************************************
 *                          SYSFS INTERFACE                          *
 *********************************************************************/
static ssize_t show_param(struct kobject *kobj,
			  struct attribute *attr, char *buf)
{
	int i = 0;
	int ret = 0;
	ssize_t cnt = 0;

	mutex_lock(&g_cpu_volt_data.cpu_mutex);

	ret = atfd_hisi_service_get_val_smc(CPU_VOLT_FN_GET_VAL,
					    g_cpu_volt_data.phy_addr,
					    AVS_VOLT_MAX_BYTE, 0);
	if (ret != 0) {
		(void)snprintf(buf, strlen("get val failed.\n") + 1, "%s", "get val failed.\n");
		mutex_unlock(&g_cpu_volt_data.cpu_mutex);
		return cnt;
	}
	for (i = 0; i < AVS_VOLT_MAX_BYTE; i++) {
		cnt +=
		    snprintf(buf + cnt, 5, "0x%-2x ", g_cpu_volt_data.virt_addr[i]);
		if ((i != 0) && (i % 16 == 15))
			cnt += snprintf(buf + cnt, strlen("\n") + 1, "%s", "\n");
	}

	mutex_unlock(&g_cpu_volt_data.cpu_mutex);

	return cnt;
}

static ssize_t store_param(struct kobject *kobj, struct attribute *attr,
			   const char *buf, size_t count)
{
	return 0;
}

/* the param is avs volt,just for security*/
define_one_global_rw(param);

static int __init cpufreq_get_volt_init(void)
{
	int ret = 0;
	struct device_node *np = NULL;
	uint32_t data[2] = { 0 };

	phys_addr_t bl31_smem_base =
	    HISI_SUB_RESERVED_BL31_SHARE_MEM_PHYMEM_BASE;
	np = of_find_compatible_node(NULL, NULL, "hisilicon, get_val");
	if (!np) {
		pr_err("%s: no compatible node found.\n", __func__);
		return ret;
	}

	ret = of_property_read_u32_array(np, "hisi,bl31-share-mem", &data[0], 2);
	if (ret) {
		pr_err("%s , get val mem compatible node err.\n",
		     __func__);
		return ret;
	}

	g_cpu_volt_data.phy_addr = bl31_smem_base + data[0];
	g_cpu_volt_data.virt_addr =
	    (unsigned char *)ioremap(bl31_smem_base + data[0], data[1]);
	if (NULL == g_cpu_volt_data.virt_addr) {
		pr_err
		    ("%s: %d: allocate memory for g_cpu_volt_data.virt_addr failed.\n",
		     __func__, __LINE__);
		return ret;
	}
	mutex_init(&(g_cpu_volt_data.cpu_mutex));

	ret = cpufreq_sysfs_create_file(&param.attr);
	if (ret)
		pr_err("%s: cannot register get_volt sysfs file\n", __func__);

	return ret;
}

module_init(cpufreq_get_volt_init);
