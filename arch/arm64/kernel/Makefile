#
# Makefile for the linux kernel.
#

CPPFLAGS_vmlinux.lds	:= -DTEXT_OFFSET=$(TEXT_OFFSET)
AFLAGS_head.o		:= -DTEXT_OFFSET=$(TEXT_OFFSET)
CFLAGS_efi-stub.o 	:= -DTEXT_OFFSET=$(TEXT_OFFSET)
CFLAGS_armv8_deprecated.o := -I$(src)

KASAN_SANITIZE_efi-stub.o	:= n

CFLAGS_REMOVE_ftrace.o = -pg
CFLAGS_REMOVE_insn.o = -pg
CFLAGS_REMOVE_return_address.o = -pg

# Object file lists.
arm64-obj-y		:= debug-monitors.o entry.o irq.o fpsimd.o		\
			   entry-fpsimd.o process.o ptrace.o setup.o signal.o	\
			   sys.o stacktrace.o time.o traps.o io.o vdso.o	\
			   psci.o psci-call.o cpu_ops.o insn.o			\
			   return_address.o cpuinfo.o cpu_errata.o		\
			   cpufeature.o alternative.o cacheinfo.o		\
			   smp.o smp_spin_table.o

ifeq ($(CONFIG_HIBERNATION),y)
arm64-obj-y            +=hibernation_hyp-stub.o
else
arm64-obj-y            +=hyp-stub.o
endif

stub-obj				:= efi-stub.o efi-entry.o
extra-y					:= $(stub-obj)
stub-obj				:= $(patsubst %.o,%.stub.o,$(stub-obj))

OBJCOPYFLAGS := --prefix-symbols=__efistub_
$(obj)/%.stub.o: $(obj)/%.o FORCE
	$(call if_changed,objcopy)

arm64-obj-$(CONFIG_COMPAT)		+= sys32.o kuser32.o signal32.o 	\
					   sys_compat.o entry32.o		\
					   ../../arm/kernel/opcodes.o
arm64-obj-$(CONFIG_FUNCTION_TRACER)	+= ftrace.o entry-ftrace.o
arm64-obj-$(CONFIG_MODULES)		+= arm64ksyms.o module.o
arm64-obj-$(CONFIG_SMP)			+= smp.o smp_spin_table.o
arm64-obj-$(CONFIG_PERF_EVENTS)		+= perf_regs.o
arm64-obj-$(CONFIG_HW_PERF_EVENTS)	+= perf_event.o
arm64-obj-$(CONFIG_HAVE_HW_BREAKPOINT)	+= hw_breakpoint.o
arm64-obj-$(CONFIG_HAVE_HW_BREAKPOINT_ADDR_MASK)	+= hisi_arch_watchpoint.o
ifeq ($(CONFIG_HIBERNATION),y)
arm64-obj-$(CONFIG_CPU_PM)             += hibernation_sleep.o hibernation_suspend.o
else
arm64-obj-$(CONFIG_CPU_PM)		+= sleep.o suspend.o
endif
arm64-obj-$(CONFIG_CPU_IDLE)		+= cpuidle.o
arm64-obj-$(CONFIG_JUMP_LABEL)		+= jump_label.o
arm64-obj-$(CONFIG_KGDB)		+= kgdb.o
arm64-obj-$(CONFIG_KPROBES)		+= kprobes.o kprobes-arm64.o		\
					   probes-simulate-insn.o		\
					   probes-condn-check.o
arm64-obj-$(CONFIG_EFI)		+= efi.o $(stub-obj)
arm64-obj-$(CONFIG_PCI)			+= pci.o
arm64-obj-$(CONFIG_ARMV8_DEPRECATED)	+= armv8_deprecated.o
arm64-obj-$(CONFIG_ACPI)		+= acpi.o

ifeq ($(CONFIG_SCHED_HMP),y)
arm64-obj-$(CONFIG_SCHED_HMP)		+= hmp_topology.o
else
arm64-obj-y				+= topology.o
endif

arm64-obj-$(CONFIG_HIBERNATION)		+= hibernate.o hibernate-asm.o

obj-y					+= $(arm64-obj-y) vdso/
obj-m					+= $(arm64-obj-m)
head-y					:= head.o
extra-y					+= $(head-y) vmlinux.lds

# vDSO - this must be built first to generate the symbol offsets
$(call objectify,$(arm64-obj-y)): $(obj)/vdso/vdso-offsets.h
$(obj)/vdso/vdso-offsets.h: $(obj)/vdso
