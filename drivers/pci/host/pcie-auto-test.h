#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/io.h>
#include <linux/sizes.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/printk.h>
#include <linux/random.h>
#include <linux/vmalloc.h>
#include <linux/jiffies.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/dmaengine.h>
#include <linux/wait.h>
#include <linux/freezer.h>

#include <linux/fs.h>
#include <linux/file.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>

#include <linux/pci.h>
#include <linux/pci_ids.h>
#include <linux/pci_regs.h>
#include "pcie-kirin.h"
#include <asm/cacheflush.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 1, 0))
#include "pcie-designware.h"
#else
#include "kirin-pcie-designware.h"
#endif

#define PCIE_STRESS_TEST_MODE_CPU_READ  (0x00000001)    /* enable CPU read */
#define PCIE_STRESS_TEST_MODE_CPU_WRITE (0x00000002)    /* enable CPU write */
#define PCIE_STRESS_TEST_MODE_DMA_READ  (0x00000004)    /* enable DMA read */
#define PCIE_STRESS_TEST_MODE_DMA_WRITE (0x00000008)    /* enable DMA write */
#define PCIE_STRESS_TEST_MODE_INTERRUPT (0x00000010)    /* enable interrupt */
#define PCIE_STRESS_TEST_MODE_LOWPOWER (0x00000020)		/*lowpower test*/
#define PCIE_STRESS_TEST_MODE_LOOPBACK (0x00000040)		/*loopback test*/
#define PCIE_STRESS_TEST_MODE_COMPLIANCE (0x00000080)		/*compliance test*/

#define PCIE_STRESS_TEST_MODE_RANDOM    (0x80000000)    /* enable random address and random size */
#define SIZE_M (1024*1024)

#define PCIE_STRESS_TEST_MODE_VALID	(PCIE_STRESS_TEST_MODE_CPU_READ | \
										PCIE_STRESS_TEST_MODE_CPU_WRITE | \
										PCIE_STRESS_TEST_MODE_DMA_READ | \
										PCIE_STRESS_TEST_MODE_DMA_WRITE | \
										PCIE_STRESS_TEST_MODE_INTERRUPT | \
										PCIE_STRESS_TEST_MODE_LOWPOWER | \
										PCIE_STRESS_TEST_MODE_LOOPBACK | \
										PCIE_STRESS_TEST_MODE_COMPLIANCE | \
										PCIE_STRESS_TEST_MODE_RANDOM)

/*designware register*/


#define L0S_MODE 0
#define L1_MODE 1
#define L0S_L1_MODE 1
#define L1_1_MODE 2
#define L1_2_MODE 3
#define L0_MODE 4
#define LINK_LOWPWR 4
#define LOOPBACK_MODE 5
#define COMPLIANCE_MODE 6
#define AUTO_TEST_RANDOM_DATA 0x1234abcd


#define SCTRL_ADDR	0xfff0a000
#define PCIE_CTRL	0xff3fe000
#define WIFI_FIRMWARE_START 0x180000
#define WIFI_RW_MEMORY_SIZE 0xc0000
#define PCIE_AUTO_TEST_OKAY 0
#define PCIE_AUTO_TEST_OTHER_FAIL 0xde
#define PCIE_AUTO_TEST_LINKUP_FAIL 0xdf
#define PCIE_AUTO_TEST_BUSY 0xe0
#define PCIE_AUTO_TEST_CPU_READ_FAIL 0xe1
#define PCIE_AUTO_TEST_CPU_WRITE_FAIL 0xe2
#define PCIE_AUTO_TEST_DMA_READ_FAIL 0xe3
#define PCIE_AUTO_TEST_DMA_WRITE_FAIL 0xe4
#define PCIE_AUTO_TEST_ENTRY_NEAR_LOOPBACK_FAIL 0xe5
#define PCIE_AUTO_TEST_EXIT_NEAR_LOOPBACK_FAIL 0xe6

#define PCIE_AUTO_TEST_ENTRY_FAR_LOOPBACK_FAIL 0xe7
#define PCIE_AUTO_TEST_EXIT_FAR_LOOPBACK_FAIL 0xe8
#define PCIE_AUTO_TEST_LOOPBACK_OTHER_FAIL 0xe9

#define PCIE_AUTO_TEST_ENTRY_COMPLIANCE_FAIL 0xea
#define PCIE_AUTO_TEST_EXIT_COMPLIANCE_FAIL 0xf0
#define PCIE_AUTO_TEST_COMPLIANCE_OTHER_FAIL 0xf1
#define PCIE_AUTO_TEST_SET_TESTMODE_FAIL 0xf2

extern int kirin_pcie_enumerate(u32 rc_id);
