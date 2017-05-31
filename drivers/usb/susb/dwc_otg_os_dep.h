#ifndef _DWC_OS_DEP_H_
#define _DWC_OS_DEP_H_

/**
 * @file
 *
 * This file contains OS dependent structures.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/dma-mapping.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/stat.h>
#include <linux/pci.h>
#include <linux/io.h>
#include <linux/version.h>
#include <linux/wakelock.h>
#include <linux/platform_device.h>
#include <asm/cacheflush.h>

#ifdef __cplusplus
extern "C" {
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 20)
# include <linux/irq.h>
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 21)
# include <linux/usb/ch9.h>
#else
# include <linux/usb_ch9.h>
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
# include <linux/usb/gadget.h>
#else
# include <linux/usb_gadget.h>
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 20)
# include <asm/irq.h>
#endif

#ifdef PCI_INTERFACE
# include <asm/io.h>
#endif

#ifdef LM_INTERFACE
# include <asm/unaligned.h>
# include <asm/sizes.h>
# include <asm/param.h>
# include <asm/io.h>
# include "lm.h"
#endif

/** The OS page size */
#define DWC_OS_PAGE_SIZE	PAGE_SIZE

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 14)
typedef int gfp_t;
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 18)
# define IRQF_SHARED SA_SHIRQ
#endif

typedef struct os_dependent {
	/** Base address returned from ioremap() */
	void *base;

	/** Register offset for Diagnostic API */
	uint32_t reg_offset;

#ifdef LM_INTERFACE
	struct lm_device *lmdev;
#elif defined(PCI_INTERFACE)
	struct pci_dev *pcidev;

	/** Start address of a PCI region */
	resource_size_t rsrc_start;

	/** Length address of a PCI region */
	resource_size_t rsrc_len;
#endif
} os_dependent_t;

#ifdef __cplusplus
}
#endif

#endif /* _DWC_OS_DEP_H_ */
