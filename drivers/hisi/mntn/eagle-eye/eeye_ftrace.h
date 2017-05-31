
#ifndef _EEYE_FTRACE_H
#define	_EEYE_FTRACE_H

#include <linux/mmzone.h>
#include <linux/kallsyms.h>
#include <linux/hisi/rdr_hisi_ap_hook.h>

#define FTRACE_BUF_MAGIC	0xF748FDE2

#define KMALLOC_SIZE_MAX	(MAX_ORDER_NR_PAGES * PAGE_SIZE) /*0x400000*/
#define AP_TRACE_FTRACE_HEAD_MAX_SIZE	0x400

#define AP_TRACE_FTRACE_BUF_A_SIZE	0x80000	/*512k*/
#define AP_TRACE_FTRACE_BUF_B_SIZE	\
	(KMALLOC_SIZE_MAX - AP_TRACE_FTRACE_BUF_A_SIZE - \
	AP_TRACE_FTRACE_HEAD_MAX_SIZE)
#define AP_TRACE_FTRACE_BUF_Z_SIZE	0x0 /*空间有限，暂不启用*/

#define FTRACE_BUFFER_LIFETIME		(10*60) /*10min*/

#define PATH_FTRACE_BIN		PATH_ROOT"/running_trace/ftrace/"
#define PREFIX_FTRACE_BIN	"ftrace-"
#define SUFFIX_FTRACE_BIN	".bin"
#define KSYMS_BIN	"ksyms.txt"
#define ROOT_UID		0
#define SYSTEM_GID		1000
#define DIR_LIMIT		0770
#define FILE_LIMIT		0660
#define FTRACE_BIN_NUM_LIMIT  2
#define DATE_MAXLEN         14
#define PATH_MAXLEN         128
#define FILE_NAME_LEN    64
#define U64_STR_LEN		16

#define LOOP_COUNT_MAX  1000
#define TMP_BUF_SIZE	1024

#define FTRACE_REG_DELAY	(20*1000) /*ms*/

typedef enum {
	HK_FTRACE_BUF_START,
	HK_FTRACE_BUF_A = HK_FTRACE_BUF_START, /*this buffer is ringbuffer.*/
	HK_FTRACE_BUF_B,	/*buffer below is not ringbuffer.*/
	HK_FTRACE_BUF_Z,
	HK_FTRACE_BUF_MAX
}
ftrace_buf_type;

/****MEMORY LAYOUT****
***********************
*	struct ftrace_root
***********************
*struct ftrace_buffer_head
-----------------------
*		BUF A
***********************
*struct ftrace_buffer_head
-----------------------
*		BUF B
***********************
*struct ftrace_buffer_head
-----------------------
*		BUF Z
***********************/

struct ftrace_buffer_head {
	struct list_head list;
	u32 reason;/*例如正常记录，或预警RCU、task、work不调度后记录，
				或者是异常复位*/
	u8	idx;
	bool is_inuse;
	bool is_percpu;
	bool is_loop;
	u64 buffer_addr;
	u64 buffer_len;
	u64 start_timestamp; /*ktime*/
	u64 stop_timestamp;/*ktime*/
	percpu_buffer_info ftrace_buffer;
};

struct ftrace_root {
	u32 magic;
	u32 buffer_total_num;
	struct ftrace_buffer_head *finfo[HK_FTRACE_BUF_MAX];
};

struct function_trace_info {
	char comm[TASK_COMM_LEN];
	int pid;
	u8 cpu;
	u8 flags;/*irq flags、need_resched、hardirq or softirq*/
	u8 preempt_count;
	u64 timestamp;
	u64 ip;
	u64 parent_ip;
};

struct ksym_info {
	unsigned long addr;
	char namebuf[KSYM_NAME_LEN];
};

struct kallsyms_info {
	unsigned long num_syms;
	unsigned long index;
	struct ksym_info *kallsyms_ptr;
};

struct ftrace_bin_info {
	struct list_head list;
	u64	file_tm;
	char filename[32];
};

#ifdef CONFIG_HISI_EAGLE_EYE
extern void set_ftrace_buffer_lifetime(unsigned long lifetime);
#else
static inline void set_ftrace_buffer_lifetime(unsigned long lifetime)
{ return; }
#endif

#endif /*_EEYE_FTRACE_H*/
