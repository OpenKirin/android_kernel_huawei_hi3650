/*
 *  kernel/drivers/hisi/memory_dump/Kernel_dump.c
 *
 * balong memory/register proc-fs  dump implementation
 *
 * Copyright (C) 2012 Hisilicon, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 #include <linux/stddef.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/interrupt.h>
#include <linux/pagemap.h>
#include <linux/jiffies.h>
#include <linux/bootmem.h>
#include <linux/memblock.h>
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <linux/kmemcheck.h>
#include <linux/module.h>
#include <linux/suspend.h>
#include <linux/pagevec.h>
#include <linux/blkdev.h>
#include <linux/slab.h>
#include <linux/ratelimit.h>
#include <linux/oom.h>
#include <linux/notifier.h>
#include <linux/topology.h>
#include <linux/sysctl.h>
#include <linux/cpu.h>
#include <linux/cpuset.h>
#include <linux/memory_hotplug.h>
#include <linux/nodemask.h>
#include <linux/vmalloc.h>
#include <linux/vmstat.h>
#include <linux/mempolicy.h>
#include <linux/stop_machine.h>
#include <linux/sort.h>
#include <linux/pfn.h>
#include <linux/backing-dev.h>
#include <linux/fault-inject.h>
#include <linux/page-isolation.h>
#include <linux/debugobjects.h>
#include <linux/kmemleak.h>
#include <linux/compaction.h>
#include <trace/events/kmem.h>
#include <linux/ftrace_event.h>
#include <linux/memcontrol.h>
#include <linux/prefetch.h>
#include <linux/migrate.h>
#include <linux/hugetlb.h>
#include <linux/sched/rt.h>
#include <linux/io.h>
#include <linux/of_fdt.h>

#include <asm/tlbflush.h>
/*lint -e451*/
#include <asm/div64.h>
/*lint +e451*/
#include "kernel_dump.h"
#include <linux/hisi/mntn_dump.h>

extern int pcpu_base_size;
extern struct memblock memblock;
extern struct mm_struct init_mm;
extern char _text[];
extern char _end[];


struct kernel_dump_cb *g_kdump_cb;
static struct table_extra{
    u64 extra_mem_phy_base;
    u64 extra_mem_size;
} g_tbl_extra_mem[MAX_EXTRA_MEM] = {{0, 0} };
static int extra_index;
static DEFINE_RAW_SPINLOCK(g_kdump_lock);

int add_extra_table(u64 phys_addr, u64 size)
{
	int i;
	if ((phys_addr == 0) || (size == 0) || (extra_index >= MAX_EXTRA_MEM)) {
		return -1;
	}

	raw_spin_lock(&g_kdump_lock);
	/* Kernel dump is not inited */
	if (!g_kdump_cb) {
			g_tbl_extra_mem[extra_index].extra_mem_phy_base = phys_addr;
			g_tbl_extra_mem[extra_index].extra_mem_size = size;
			extra_index++;
	} else {
		i = extra_index;
		if (i < MAX_EXTRA_MEM) {
			g_kdump_cb->extra_mem_phy_base[i] = phys_addr;
			g_kdump_cb->extra_mem_size[i] = size;
			extra_index += 1;
		} else {
			printk(KERN_ERR "%s: extra memory(nums:%d) is out of range. \r\n", __func__, extra_index);
			goto err;
		}
	}
	raw_spin_unlock(&g_kdump_lock);
	return 0;
err:
	raw_spin_unlock(&g_kdump_lock);
	return -1;
}

int kernel_dump_init(void)
{
	int i, j;
	struct kernel_dump_cb *cb;
	struct memblock_type *print_mb_cb;
	if (register_mntn_dump(MNTN_DUMP_KERNEL_DUMP, sizeof(struct kernel_dump_cb), (void **)&cb)) {
		printk(KERN_ERR "%s: fail to get reserve memory\r\n", __func__);
		goto err;
	}
	printk(KERN_ERR "%s begin, 0x%llx!\r\n", __func__, (unsigned long long)cb);

	memset((void *)cb, 0, sizeof(struct kernel_dump_cb));
	cb->magic = KERNELDUMP_CB_MAGIC;
	cb->page_shift = PAGE_SHIFT;
	cb->struct_page_size = sizeof(struct page);
	cb->phys_offset = PHYS_OFFSET;
	cb->page_offset = PAGE_OFFSET;
	cb->extra_mem_phy_base[0] = virt_to_phys(_text);
	cb->extra_mem_size[0] = ALIGN(_end - _text, PAGE_SIZE);
	cb->extra_mem_phy_base[1] = virt_to_phys(pcpu_base_addr); /* per cpu info*/
	cb->extra_mem_size[1] = ALIGN(pcpu_base_size, PAGE_SIZE)*CONFIG_NR_CPUS;
	cb->extra_mem_phy_base[2] = virt_to_phys(initial_boot_params); /* DTB address*/
	cb->extra_mem_size[2] = MAX_DTB_SIZE; /*DTB size 512K*/
	for (i = 3, j = 0; i < MAX_EXTRA_MEM && j < extra_index; i++, j++) {
		cb->extra_mem_phy_base[i] = g_tbl_extra_mem[j].extra_mem_phy_base;
		cb->extra_mem_size[i] = g_tbl_extra_mem[j].extra_mem_size;
	}
	extra_index = i;

	printk("_text:0x%pK _end:0x%pK\n", _text, _end);

	cb->page = mem_map;
	cb->pfn_offset = PHYS_PFN_OFFSET;
	cb->section_size = 0;
       /*Subtract the base address that TTBR1 maps*/
	cb->kern_map_offset = (UL(0xffffffffffffffff) << VA_BITS);

	cb->ttbr = virt_to_phys(init_mm.pgd);
	printk("%s: ttbr:%pK\n", __FUNCTION__, (void *)cb->ttbr);

	cb->mb_cb = (struct memblock_type *)virt_to_phys(&memblock.memory);
	print_mb_cb = &memblock.memory;
	cb->mbr_size = sizeof(struct memblock_region);

	printk("cb->page is 0x%llx\n", (unsigned long long)(cb->page));
	printk("cb->page_shift is 0x%x\n", cb->page_shift);
	printk("cb->struct_page_size is 0x%x\n", cb->struct_page_size);
	printk("cb->phys_offset is 0x%llx\n", cb->phys_offset);
	printk("cb->page_offset is 0x%llx\n", cb->page_offset);
	printk("cb->pfn_offset is 0x%llx\n", cb->pfn_offset);
	printk("cb->ttbr is 0x%llx\n", cb->ttbr);
	printk("cb->mb_cb is 0x%llx\n", (unsigned long long)(cb->mb_cb));
	printk("cb->section_size is 0x%llx\n", cb->section_size);
	printk("cb->pmd_size is 0x%llx\n", cb->pmd_size);
	printk("cb->mbr_size is 0x%x\n", cb->mbr_size);
	printk("cb->kern_map_offset is 0x%llx\n", (unsigned long long)(cb->kern_map_offset));

	printk("mem_map is %pK\n", mem_map);
	printk("vmemmap is %pK\n", vmemmap);
	for (i = 0; i < print_mb_cb->cnt; i++) {
		printk("print_mb_cb->regions is 0x%llx\n", (print_mb_cb->regions+i)->base);
		printk("print_mb_cb->regions is 0x%llx\n", (print_mb_cb->regions+i)->size);
	}
	g_kdump_cb = cb;
	return 0;
err:
	return -1;
}
early_initcall(kernel_dump_init);

