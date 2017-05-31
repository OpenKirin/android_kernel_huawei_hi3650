/*
 * code_protect. (for kernel code protection within ddrc mechanism.)
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/hisi/hisi_drmdriver.h>
#include <asm/sections.h>


static void configure_kernel_code_protect(unsigned long addr, unsigned long usize)
{
	(void)atfd_hisi_service_access_register_smc((u64)ACCESS_REGISTER_FN_MAIN_ID, (u64)addr, (u64)usize, (u64)ACCESS_REGISTER_FN_SUB_ID_DDR_KERNEL_CODE_PROTECT);
	return;
}


static s32 __init code_protect_set_init(void)
{
	unsigned long addr_start = virt_to_phys(_stext);
	unsigned long addr_end = virt_to_phys(_etext);
	unsigned long space_size = 0; /**/

	if (addr_end > addr_start)
	{
		space_size = addr_end - addr_start;
	}
	printk(KERN_ERR "code_protect_set_init, start phy addr is 0x%lx, end addr is 0x%lx.\n", addr_start, addr_end);
	configure_kernel_code_protect(addr_start, space_size);
	return 0;
}

static void __exit code_protect_set_exit(void)
{
	return;
}

module_init(code_protect_set_init);
module_exit(code_protect_set_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("l00212112 <l00212112@hisilicon.com>");
MODULE_DESCRIPTION("for kernel code protection within ddrc mechanism.");
