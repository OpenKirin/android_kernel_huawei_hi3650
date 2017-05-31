#include <linux/linkage.h>
#include <linux/errno.h>

#include <asm/asm-offsets.h>
#include <asm/assembler.h>
#include <asm/cputype.h>
#include <asm/memory.h>
#include <asm/page.h>

/*
 * Corrupt memory.
 *
 * Loads temporary page tables then restores the memory image.
 * Finally branches to cpu_resume() to restore the state saved by
 * swsusp_arch_suspend().
 *
 * Because this code has to be copied to a safe_page, it can't call out to
 * other functions by PC-relative address. Also remember that it may be
 * mid-way through over-writing other functions. For this reason it contains
 * a copy of copy_page() and code from flush_icache_range().
 *
 * All of memory gets written to, including code. We need to clean the kernel
 * text to the Point of Coherence (PoC) before secondary cores can be booted.
 * Because the kernel modules and executable pages mapped to user space are
 * also written as data,  we clean all pages we touch to the Point of
 * Unification (PoU).
 *
 * x0: physical address of temporary page tables
 * x1: physical address of swapper page tables
 * x2: address of kernel_start
 * x3: address of kernel_end
 */
.pushsection    ".hibernate_exit.text", "ax"
ENTRY(swsusp_arch_suspend_exit)
	/* Temporary page tables are a copy, so no need for a trampoline here */
	msr	ttbr1_el1, x0
	isb
	tlbi	vmalle1is
	ic	ialluis
	isb

	mov	x21, x1
	mov	x22, x2
	mov	x23, x3

	/* walk the restore_pblist and use copy_page() to over-write memory */
	ldr	x19, =restore_pblist
	ldr	x19, [x19]

2:	ldr	x10, [x19, #HIBERN_PBE_ORIG]
	mov	x0, x10
	ldr	x1, [x19, #HIBERN_PBE_ADDR]

	/* arch/arm64/lib/copy_page.S:copy_page() */
	prfm	pldl1strm, [x1, #64]
3:	ldp	x2, x3, [x1]
	ldp	x4, x5, [x1, #16]
	ldp	x6, x7, [x1, #32]
	ldp	x8, x9, [x1, #48]
	add	x1, x1, #64
	prfm	pldl1strm, [x1, #64]
	stnp	x2, x3, [x0]
	stnp	x4, x5, [x0, #16]
	stnp	x6, x7, [x0, #32]
	stnp	x8, x9, [x0, #48]
	add	x0, x0, #64
	tst	x1, #(PAGE_SIZE - 1)
	b.ne	3b

	dsb	ish		//  memory restore must finish before cleaning

	add	x1, x10, #PAGE_SIZE
	/* Clean the copied page to PoU - based on flush_icache_range() */
	dcache_line_size x2, x3
	sub	x3, x2, #1
	bic	x4, x10, x3
4:	dc	cvau, x4	// clean D line / unified line
	add	x4, x4, x2
	cmp	x4, x1
	b.lo	4b

	ldr	x19, [x19, #HIBERN_PBE_NEXT]
	cbnz	x19, 2b

	/* Clean the kernel text to PoC - based on flush_icache_range() */
	dcache_line_size x2, x3
	sub	x3, x2, #1
	bic	x4, x22, x3
5:	dc	cvac, x4
	add	x4, x4, x2
	cmp	x4, x23
	b.lo	5b

	/*
	 * branch into the restored kernel - so that when we restore the page
	 * tables, code continues to be executable.
	 */
	ldr	x1, =__hibernate_exit
	mov	x0, x21		// physical address of swapper page tables.
	br	x1

	.ltorg
ENDPROC(swsusp_arch_suspend_exit)
.popsection

/*
 * Reset the page tables, and wake up in cpu_resume().
 * Temporary page tables were a copy, so again, no trampoline here.
 *
 * x0: physical address of swapper_pg_dir
 */
ENTRY(__hibernate_exit)
	msr	ttbr1_el1, x0
	isb
	tlbi	vmalle1is
	ic	ialluis
	isb
	b	_cpu_resume
ENDPROC(__hibernate_exit)
