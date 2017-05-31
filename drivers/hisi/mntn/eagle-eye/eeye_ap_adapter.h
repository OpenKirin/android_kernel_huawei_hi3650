#ifndef __HISI_EEYE_AP_ADAPTER_H
#define __HISI_EEYE_AP_ADAPTER_H

/* default timeout in seconds */
#define DEFAULT_WDT_TIMEOUT     9

#define SLICE_COUNT_PER_SEC     32768
#define WDT_KICK_TIMEOUT_DELTA	2

#define NO_SCHED_TIMEOUT		(1*1000000000L) /*nanosecond*/

/*�ں�������ȼ��ʹ�õ����ݽṹ*/
struct sched_stat_info {
	u64 last_arrival;
	u64 delta;
	char comm[TASK_COMM_LEN];
};

/*����Ϊ����ʱ�����У�
��Ҫ��ȡcpu0 timer��ʱʱ������Ҫ�����ݽṹ*/
#define TVN_BITS (CONFIG_BASE_SMALL ? 4 : 6)
#define TVR_BITS (CONFIG_BASE_SMALL ? 6 : 8)
#define TVN_SIZE (1 << TVN_BITS)
#define TVR_SIZE (1 << TVR_BITS)

struct tvec {
	struct list_head vec[TVN_SIZE];
};

struct tvec_root {
	struct list_head vec[TVR_SIZE];
};

struct tvec_base {
	spinlock_t lock;
	struct timer_list *running_timer;
	unsigned long timer_jiffies;
	unsigned long next_timer;
	unsigned long active_timers;
	unsigned long all_timers;
	int cpu;
	struct tvec_root tv1;
	struct tvec tv2;
	struct tvec tv3;
	struct tvec tv4;
	struct tvec tv5;
} ____cacheline_aligned;
/*����Ϊ����ʱ�����У�
��Ҫ��ȡcpu0 timer��ʱʱ������Ҫ�����ݽṹ*/

#endif /*__HISI_EEYE_AP_ADAPTER_H*/
