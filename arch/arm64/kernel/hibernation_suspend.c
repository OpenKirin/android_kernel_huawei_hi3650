#include <linux/ftrace.h>
#include <linux/percpu.h>
#include <linux/slab.h>
#include <asm/cacheflush.h>
#include <asm/debug-monitors.h>
#include <asm/pgtable.h>
#include <asm/memory.h>
#include <asm/mmu_context.h>
#include <asm/smp_plat.h>
#include <asm/suspend.h>
#include <asm/tlbflush.h>


/*
 * This hook is provided so that cpu_suspend code can restore HW
 * breakpoints as early as possible in the resume path, before reenabling
 * debug exceptions. Code cannot be run from a CPU PM notifier since by the
 * time the notifier runs debug exceptions might have been enabled already,
 * with HW breakpoints registers content still in an unknown state.
 */
void (*hw_breakpoint_restore)(void *);
void __init cpu_suspend_set_dbg_restorer(void (*hw_bp_restore)(void *))
{
	/* Prevent multiple restore hook initializations */
	if (WARN_ON(hw_breakpoint_restore))
		return;
	hw_breakpoint_restore = hw_bp_restore;
}

void notrace __cpu_suspend_exit(struct mm_struct *mm)
{
	if (mm != &init_mm)
		cpu_switch_mm(mm->pgd, mm);

	/*
	 * Restore per-cpu offset before any kernel
	 * subsystem relying on it has a chance to run.
	 */
	set_my_cpu_offset(per_cpu_offset(smp_processor_id()));

	/*
	 * Restore HW breakpoint registers to sane values
	 * before debug exceptions are possibly reenabled
	 * through local_dbg_restore.
	 */
	if (hw_breakpoint_restore)
		hw_breakpoint_restore(NULL);
}

/*
 * cpu_suspend
 *
 * arg: argument to pass to the finisher function
 * fn: finisher function pointer
 *
 */
int cpu_suspend(unsigned long arg, int (*fn)(unsigned long))
{
	struct mm_struct *mm = current->active_mm;
	int ret = 0;
	unsigned long flags;
	struct sleep_stack_data state;

	/*
	 * From this point debug exceptions are disabled to prevent
	 * updates to mdscr register (saved and restored along with
	 * general purpose registers) from kernel debuggers.
	 */
	local_dbg_save(flags);

	/*
	 * Function graph tracer state gets incosistent when the kernel
	 * calls functions that never return (aka suspend finishers) hence
	 * disable graph tracing during their execution.
	 */
	pause_graph_tracing();

	/*
	 * mm context saved on the stack, it will be restored when
	 * the cpu comes out of reset through the identity mapped
	 * page tables, so that the thread address space is properly
	 * set-up on function return.
	 */
	if (__cpu_suspend_enter(&state)) {
		/* Call the suspend finisher */
		ret = fn(arg);

		/*
		 * Never gets here, unless suspend finisher fails.
		 * Successful cpu_suspend should return from cpu_resume,
		 * returning through this code path is considered an error
		 * If the return value is set to 0 force ret = -EOPNOTSUPP
		 * to make sure a proper error condition is propagated
		 */

		if (!ret)
			ret = -EOPNOTSUPP;
	} else
		__cpu_suspend_exit(mm);unpause_graph_tracing();

	/*
	 * Restore pstate flags. OS lock and mdscr have been already
	 * restored, so from this point onwards, debugging is fully
	 * renabled if it was enabled when core started shutdown.
	 */
	local_dbg_restore(flags);

	return ret;
}

unsigned long *sleep_save_stash;

static int __init cpu_suspend_init(void)
{
	/* ctx_ptr is an array of physical addresses */
	sleep_save_stash = kcalloc(mpidr_hash_size(), sizeof(*sleep_save_stash),
				   GFP_KERNEL);

	if (WARN_ON(!sleep_save_stash))
		return -ENOMEM;

	return 0;
}
early_initcall(cpu_suspend_init);
