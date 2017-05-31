/*
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ASM__VIRT_H
#define __ASM__VIRT_H

/*
 * The arm64 hcall implementation uses the ISS field of the ESR_EL2 register to
 * specify the hcall type.  The exception handlers are allowed to use registers
 * x17 and x18 in their implementation.  Any routine issuing an hcall must not
 * expect these registers to be preserved.
 */

/*
 * HVC_CALL_HYP - Execute a hyp routine.
 */

#define HVC_CALL_HYP 0

/*
 * HVC_GET_VECTORS - Return the value of the vbar_el2 register.
 */

#define HVC_GET_VECTORS 1

/*
 * HVC_SET_VECTORS - Set the value of the vbar_el2 register.
 *
 * @x0: Physical address of the new vector table.
 */

#define HVC_SET_VECTORS 2

/*
 * HVC_CALL_FUNC - Execute a function at EL2.
 *
 * @x0: Physical address of the function to be executed.
 * @x1: Passed as the first argument to the function.
 * @x2: Passed as the second argument to the function.
 * @x3: Passed as the third argument to the function.
 *
 * The called function must preserve the contents of register x18.
 */

#define HVC_CALL_FUNC 3

/*
 * HVC_RESET_CPU - Reset cpu in EL2 to initial state.
 *
 * @x0: entry address in trampoline code in va
 * @x1: identical mapping page table in pa
 */

#define HVC_RESET_CPU 4

#define BOOT_CPU_MODE_EL1	(0xe11)
#define BOOT_CPU_MODE_EL2	(0xe12)

#ifndef __ASSEMBLY__

/*
 * __boot_cpu_mode records what mode CPUs were booted in.
 * A correctly-implemented bootloader must start all CPUs in the same mode:
 * In this case, both 32bit halves of __boot_cpu_mode will contain the
 * same value (either 0 if booted in EL1, BOOT_CPU_MODE_EL2 if booted in EL2).
 *
 * Should the bootloader fail to do this, the two values will be different.
 * This allows the kernel to flag an error when the secondaries have come up.
 */
extern u32 __boot_cpu_mode[2];

void __hyp_set_vectors(phys_addr_t phys_vector_base);
phys_addr_t __hyp_get_vectors(void);

/* Reports the availability of HYP mode */
static inline bool is_hyp_mode_available(void)
{
	return (__boot_cpu_mode[0] == BOOT_CPU_MODE_EL2 &&
		__boot_cpu_mode[1] == BOOT_CPU_MODE_EL2);
}

/* Check if the bootloader has booted CPUs in different modes */
static inline bool is_hyp_mode_mismatched(void)
{
	return __boot_cpu_mode[0] != __boot_cpu_mode[1];
}

/* The section containing the hypervisor text */
extern char __hyp_text_start[];
extern char __hyp_text_end[];

#endif /* __ASSEMBLY__ */

#endif /* ! __ASM__VIRT_H */
