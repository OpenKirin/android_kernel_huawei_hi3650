/*:
 * Hibernate support specific for ARM64
 *
 * Derived from work on ARM hibernation support by:
 *
 * Ubuntu project, hibernation support for mach-dove
 * Copyright (C) 2010 Nokia Corporation (Hiroshi Doyu)
 * Copyright (C) 2010 Texas Instruments, Inc. (Teerth Reddy et al.)
 *  https://lkml.org/lkml/2010/6/18/4
 *  https://lists.linux-foundation.org/pipermail/linux-pm/2010-June/027422.html
 *  https://patchwork.kernel.org/patch/96442/
 *
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 *
 * License terms: GNU General Public License (GPL) version 2
 */
#define pr_fmt(x) "hibernate: " x
#include <linux/kvm_host.h>
#include <linux/mm.h>
#include <linux/pm.h>
#include <linux/sched.h>
#include <linux/suspend.h>
#include <linux/version.h>

#include <asm/barrier.h>
#include <asm/cacheflush.h>
#include <asm/irqflags.h>
#include <asm/memory.h>
#include <asm/mmu_context.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>
#include <asm/pgtable-hwdef.h>
#include <asm/sections.h>
#include <asm/suspend.h>

/* These are necessary to build without ifdefery */
#ifndef pmd_index
#define pmd_index(x)	0
#endif
#ifndef pud_index
#define pud_index(x)	0
#endif

/*
 * Start/end of the hibernate exit code, this must be copied to a 'safe'
 * location in memory, and executed from there.
 */
extern char __hibernate_exit_text_start[], __hibernate_exit_text_end[];

int pfn_is_nosave(unsigned long pfn)
{
	unsigned long nosave_begin_pfn = virt_to_pfn(&__nosave_begin);
	unsigned long nosave_end_pfn = virt_to_pfn(&__nosave_end - 1);

	return (pfn >= nosave_begin_pfn) && (pfn <= nosave_end_pfn);
}

void notrace save_processor_state(void)
{
	WARN_ON(num_online_cpus() != 1);
	local_fiq_disable();
}

void notrace restore_processor_state(void)
{
	local_fiq_enable();
}

/*
 * Copies src_length bytes, starting at src_start into an new page,
 * perform cache maintentance, then map it at the top of memory as executable.
 *
 * This is used by hibernate to copy the code it needs to execute when
 * overwriting the kernel text.
 *
 * Suggested allocators are get_safe_page() or get_zeroed_page(). Your chosen
 * mask must cause zero'd pages to be returned.
 */
static int create_safe_exec_page(void *src_start, size_t length,
				 void **dst_addr,
				 unsigned long (*allocator)(gfp_t mask),
				 gfp_t mask)
{
	int rc = 0;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	unsigned long dst = allocator(mask);

	if (!dst) {
		rc = -ENOMEM;
		goto out;
	}

	memcpy((void *)dst, src_start, length);
	flush_icache_range(dst, dst + length);

	pgd = pgd_offset(&init_mm, (unsigned long)-1);
	if (!pgd_val(*pgd) && PTRS_PER_PGD > 1) {
		pud = (pud_t *)allocator(mask);
		if (!pud) {
			rc = -ENOMEM;
			goto out;
		}
		set_pgd(pgd, __pgd(virt_to_phys(pud) | PUD_TYPE_TABLE));
	}

	pud = pud_offset(pgd, (unsigned long)-1);
	if (!pud_val(*pud) && PTRS_PER_PUD > 1) {
		pmd = (pmd_t *)allocator(mask);
		if (!pmd) {
			rc = -ENOMEM;
			goto out;
		}
		set_pud(pud, __pud(virt_to_phys(pmd) | PUD_TYPE_TABLE));
	}

	pmd = pmd_offset(pud, (unsigned long)-1);
	if (!pmd_val(*pmd) && PTRS_PER_PMD > 1) {
		pte = (pte_t *)allocator(mask);
		if (!pte) {
			rc = -ENOMEM;
			goto out;
		}
		set_pmd(pmd, __pmd(virt_to_phys(pte) | PMD_TYPE_TABLE));
	}

	pte = pte_offset_kernel(pmd, (unsigned long)-1);
	set_pte_at(&init_mm, dst, pte,
		   __pte(virt_to_phys((void *)dst)
			 | pgprot_val(PAGE_KERNEL_EXEC)));

	/* this is a new mapping, so no need for a tlbi */

	*dst_addr = (void *)((unsigned long)-1 & PAGE_MASK);

out:
	return rc;
}


int swsusp_arch_suspend(void)
{
	int ret = 0;
	unsigned long flags;
	struct sleep_stack_data state;
	struct mm_struct *mm = current->active_mm;

	local_dbg_save(flags);

	if (__cpu_suspend_enter(&state))
		ret = swsusp_save();
	else
		__cpu_suspend_exit(mm);

	local_dbg_restore(flags);

	return ret;
}

static int copy_pte(pmd_t *dst, pmd_t *src, unsigned long *start_addr)
{
	int i;
	pte_t *old_pte = pte_offset_kernel(src, *start_addr);
	pte_t *new_pte = pte_offset_kernel(dst, *start_addr);

	for (i = pte_index(*start_addr); i < PTRS_PER_PTE;
	     i++, old_pte++, new_pte++) {
		if (pte_val(*old_pte))
			set_pte(new_pte,
				__pte(pte_val(*old_pte) & ~PTE_RDONLY));
	}

	*start_addr &= PAGE_MASK;

	return 0;
}

static int copy_pmd(pud_t *dst, pud_t *src, unsigned long *start_addr)
{
	int i;
	int rc = 0;
	pte_t *new_pte;
	pmd_t *old_pmd = pmd_offset(src, *start_addr);
	pmd_t *new_pmd = pmd_offset(dst, *start_addr);

	for (i = pmd_index(*start_addr); i < PTRS_PER_PMD;
	     i++, *start_addr += PMD_SIZE, old_pmd++, new_pmd++) {
		if (!pmd_val(*old_pmd))
			continue;

		if (pmd_table(*(old_pmd))) {
			new_pte = (pte_t *)get_safe_page(GFP_ATOMIC);
			if (!new_pte) {
				rc = -ENOMEM;
				break;
			}

			set_pmd(new_pmd, __pmd(virt_to_phys(new_pte)
					       | PMD_TYPE_TABLE));

			rc = copy_pte(new_pmd, old_pmd, start_addr);
			if (rc)
				break;
		} else
			set_pmd(new_pmd,
				__pmd(pmd_val(*old_pmd) & ~PMD_SECT_RDONLY));

		*start_addr &= PMD_MASK;
	}

	return rc;
}

static int copy_pud(pgd_t *dst, pgd_t *src, unsigned long *start_addr)
{
	int i;
	int rc = 0;
	pmd_t *new_pmd;
	pud_t *old_pud = pud_offset(src, *start_addr);
	pud_t *new_pud = pud_offset(dst, *start_addr);

	for (i = pud_index(*start_addr); i < PTRS_PER_PUD;
	     i++, *start_addr += PUD_SIZE, old_pud++, new_pud++) {
		if (!pud_val(*old_pud))
			continue;

		if (pud_table(*(old_pud))) {
			if (PTRS_PER_PMD != 1) {
				new_pmd = (pmd_t *)get_safe_page(GFP_ATOMIC);
				if (!new_pmd) {
					rc = -ENOMEM;
					break;
				}

				set_pud(new_pud, __pud(virt_to_phys(new_pmd)
						       | PUD_TYPE_TABLE));
			}

			rc = copy_pmd(new_pud, old_pud, start_addr);
			if (rc)
				break;
		} else
			set_pud(new_pud,
				__pud(pud_val(*old_pud) & ~PMD_SECT_RDONLY));

		*start_addr &= PUD_MASK;
	}

	return rc;
}

static int copy_page_tables(pgd_t *new_pgd, unsigned long start_addr)
{
	int i;
	int rc = 0;
	pud_t *new_pud;
	pgd_t *old_pgd = pgd_offset_k(start_addr);

	new_pgd += pgd_index(start_addr);

	for (i = pgd_index(start_addr); i < PTRS_PER_PGD;
	     i++, start_addr += PGDIR_SIZE, old_pgd++, new_pgd++) {
		if (!pgd_val(*old_pgd))
			continue;

		if (PTRS_PER_PUD != 1) {
			new_pud = (pud_t *)get_safe_page(GFP_ATOMIC);
			if (!new_pud) {
				rc = -ENOMEM;
				break;
			}

			set_pgd(new_pgd, __pgd(virt_to_phys(new_pud)
					       | PUD_TYPE_TABLE));
		}

		rc = copy_pud(new_pgd, old_pgd, &start_addr);
		if (rc)
			break;

		start_addr &= PGDIR_MASK;
	}

	return rc;
}

/*
 * Setup then Resume from the hibernate image using swsusp_arch_suspend_exit().
 *
 * Memory allocated by get_safe_page() will be dealt with by the hibernate code,
 * we don't need to free it here.
 *
 * Allocate a safe zero page to use as ttbr0, as all existing page tables, and
 * even the empty_zero_page will be overwritten.
 */
int swsusp_arch_resume(void)
{
	int rc = 0;
	size_t exit_size;
	pgd_t *tmp_pg_dir;
	void *safe_zero_page_mem;
	unsigned long tmp_pg_start;
	void __noreturn (*hibernate_exit)(phys_addr_t, phys_addr_t,
					  void *, void *);

	/* Copy swsusp_arch_suspend_exit() to a safe page. */
	exit_size = __hibernate_exit_text_end - __hibernate_exit_text_start;
	rc = create_safe_exec_page(__hibernate_exit_text_start, exit_size,
			(void **)&hibernate_exit, get_safe_page, GFP_ATOMIC);
	if (rc) {
		pr_err("Failed to create safe executable page for"
		       " hibernate_exit code.");
		goto out;
	}

	/*
	 * Even the zero page may get overwritten during restore.
	 * get_safe_page() only returns zero'd pages.
	 */
	safe_zero_page_mem = (void *)get_safe_page(GFP_ATOMIC);
	if (!safe_zero_page_mem) {
		pr_err("Failed to allocate memory for zero page.");
		rc = -ENOMEM;
		goto out;
	}
	empty_zero_page = virt_to_page(safe_zero_page_mem);
	cpu_set_reserved_ttbr0();

	/*
	 * Restoring the memory image will overwrite the ttbr1 page tables.
	 * Create a second copy, of the kernel and linear map, and use this
	 * when restoring.
	 */
	tmp_pg_dir = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!tmp_pg_dir) {
		pr_err("Failed to allocate memory for temporary page tables.");
		rc = -ENOMEM;
		goto out;
	}
	tmp_pg_start = min((unsigned long)KERNEL_START,
			   (unsigned long)PAGE_OFFSET);
	rc = copy_page_tables(tmp_pg_dir, tmp_pg_start);
	if (rc)
		goto out;

	/*
	 * EL2 may get upset if we overwrite its page-tables/stack.
	 * kvm_arch_hardware_disable() returns EL2 to the hyp stub. This
	 * isn't needed on normal suspend/resume as PSCI prevents us from
	 * ruining EL2.
	 */
	if (IS_ENABLED(CONFIG_KVM_ARM_HOST))
		kvm_arch_hardware_disable();

	/*
	 * Some pages are read directly into their final location by
	 * kernel/power/snapshot.c, these are listed in
	 * restored_inplace_pblist. Some of them may be executable, we
	 * need to clean them to the PoU.
	 */
	while (restored_inplace_pblist != NULL) {
		struct pbe *pbe = restored_inplace_pblist;

		flush_icache_range((unsigned long)pbe->address,
				   (unsigned long)pbe->address + PAGE_SIZE);
		restored_inplace_pblist = pbe->next;
	}

	hibernate_exit(virt_to_phys(tmp_pg_dir), virt_to_phys(swapper_pg_dir),
		       KERNEL_START, KERNEL_END);

out:
	return rc;
}
