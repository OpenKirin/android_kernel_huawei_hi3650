/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _LINUX_CORESIGHT_TSGEN_H
#define _LINUX_CORESIGHT_TSGEN_H

#include <linux/list.h>

/*times stamp ctrl register.
bit[0]:
	  0£ºtimestamp counter disable
	  1£ºtimestamp counter enable
*/
#define TS_CNTCR		(0x00)
#define TE_ENABLE_BIT	(0)

/**
 * struct tmc_drvdata - specifics associated to an TMC component
 * @base:	memory mapped base address for this component.
 * @dev:	the device entity associated to this component.
 * @csdev:	component vitals needed by the framework.
 * @miscdev:	specifics to handle "/dev/xyz.tmc" entry.
 * @spinlock:	only one at a time pls.
 * @clk: timestamp's clock
 * @freq: timestamp's freq
 * @refcnt: trake the count tsgen is used.
 */
struct tsgen_drvdata {
	void __iomem *base;
	struct device *dev;
	struct coresight_device *csdev;
	spinlock_t spinlock;
	struct clk *clk;
	unsigned int	freq;
	unsigned int 	refcnt;
};

#define CONFIG_CORESIGHT_TSGEN
#ifdef CONFIG_CORESIGHT_TSGEN
extern int coresight_tsgen_enable(void);
extern int coresight_tsgen_disable(void);

#else
static inline int coresight_tsgen_enable(void)
{
	return -1;
}

static inline int coresight_tsgen_disable(void)
{
	return -1;
}
#endif

#endif
