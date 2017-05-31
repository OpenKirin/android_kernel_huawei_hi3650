#ifndef __HISI_SYSCOUNTER_H__
#define __HISI_SYSCOUNTER_H__

#include <soc_syscounter_interface.h>

union syscnt_val {
	u64 val;
	struct {
		u32 l32;
		u32 h32;
	}val_lh32;
};

struct syscnt_to_timespec_record {
	u64 syscnt;
	struct timespec64 ts;
	struct timespec utc;
};

struct syscnt_device {
	struct resource *res;
	void __iomem *base;
	u64 clock_rate;         /* syscounter clock rate */
	spinlock_t r_lock;		/* for read 64bit-syscounter */
	spinlock_t sync_lock;   /* for record syscounter & timespec */
	struct syscnt_to_timespec_record record;
};

#define SYSCOUNTER_L32 SOC_SYSCOUNTER_CNTCV_L32_NS_ADDR(0)
#define SYSCOUNTER_H32 SOC_SYSCOUNTER_CNTCV_H32_NS_ADDR(0)

extern int syscounter_to_timespec64(u64 syscnt, struct timespec64 *ts);
extern u64 hisi_get_syscount(void);

#endif
