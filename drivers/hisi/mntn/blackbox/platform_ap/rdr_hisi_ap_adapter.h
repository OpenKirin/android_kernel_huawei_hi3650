/*******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
 文 件 名   : rdr_hisi_platform_kirin.h
 版 本 号   : 初稿
 作    者   : 蒋孝伟 00207786
 生成日期   : 2015年1月12日
 最近修改   :
 功能描述   : AP侧适配RDR框架，相关数据结构及函数定义
 修改历史   :
 1.日    期 : 2015年1月12日
 作    者   : 蒋孝伟 00207786
 修改内容   : 创建文件

 *******************************************************************************/
#include <linux/thread_info.h>
#include <linux/hisi/rdr_hisi_platform.h>

#include <linux/hisi/rdr_hisi_ap_hook.h>

/* 轨迹记录区 */
#define AP_TRACE_IRQ_SIZE			0x80000	/*512k */
#define AP_TRACE_TASK_SIZE			0x80000	/*512k */
#define AP_TRACE_CPU_IDLE_SIZE		0x40000	/*256K */
#define AP_TRACE_CPU_ON_OFF_SIZE	0x400	/*1k */
#define AP_TRACE_SYSCALL_SIZE		0x2000	/*8k */
#define AP_TRACE_HUNG_TASK_SIZE		0x1000	/*4k */
#define AP_TRACE_TASKLET_SIZE		0x2000	/*8k */
#define AP_TRACE_WORKER_SIZE		0x4000	/*16k */
#ifdef CONFIG_HISI_MEM_TRACE
#define AP_TRACE_MEM_ALLOC_SIZE		0x80000	/*512k */
#define AP_TRACE_ION_ALLOC_SIZE		0x80000	/*512k */
#else
#define AP_TRACE_MEM_ALLOC_SIZE		0x2000	/*dummy 8k space*/
#define AP_TRACE_ION_ALLOC_SIZE		0x2000	/*dummy 8k space*/
#endif

/* 任务记录区 */
#define AP_LAST_TASK_STRUCT_SIZE    (NR_CPUS*0xAC0+0x200)	/*0x5800 //22k== 8 * 0xAC0 + 0.5k */
#define AP_LAST_TASK_STACK_SIZE     (NR_CPUS * THREAD_SIZE)	/*0x20000 //128k */


#define REG_NAME_LEN 12
#define PRODUCT_VERSION_LEN 32
#define PRODUCT_DEVICE_LEN 32
#define REGS_DUMP_MAX_NUM   10
#define AP_DUMP_MAGIC   0x19283746
#define BBOX_VERSION    0x10005	/*v1.0.5 */
#define AP_DUMP_END_MAGIC   0x1F2E3D4C
#define SIZE_1K         0x400
#define SYSTEM_BUILD_POP    "/system/build.prop"
#define AMNTN_MODULE_NAME_LEN 12
#define NMI_NOTIFY_LPM3_ADDR 0xFFF0A510
#define WDT_KICK_SLICE_TIMES    (3)

#define PSTORE_PATH            "/sys/fs/pstore/"
#define FASTBOOT_LOG_FILE      "/proc/balong/log/fastboot_log"
#define LAST_FASTBOOT_LOG_FILE "/proc/balong/log/last_fastboot_log"
#define MNTN_FILESYS_MAX_CYCLE    32	/*avoid loop forever! */
#define MNTN_FILESYS_PURE_DIR_NAME_LEN    64	/*the max length of pure name of a file or dir, that is, exclusive path */


typedef struct {
	rdr_hisiap_dump_func_ptr dump_funcptr;
	unsigned char *dump_addr;
	unsigned int dump_size;
	char module_name[AMNTN_MODULE_NAME_LEN];
} module_dump_mem_info;

typedef struct {
	char reg_name[12];
	u32 reg_size;
	u64 reg_base;
	void __iomem *reg_map_addr;
	unsigned char *reg_dump_addr;
} regs_info;

typedef struct {
	unsigned int dump_magic;
	unsigned char version[PRODUCT_VERSION_LEN];
	u32 modid;
	u32 e_exce_type;
	u64 coreid;
	u64 slice;
	struct rdr_register_module_result ap_rdr_info;
	unsigned int enter_times;	/* 重入计数，初始化为0，每次进入++； */

	unsigned int num_reg_regions;
	regs_info dump_regs_info[REGS_DUMP_MAX_NUM];

	unsigned char *hook_buffer_addr[HK_MAX];

	percpu_buffer_info hook_percpu_buffer[HK_PERCPU_TAG];

	unsigned char *last_task_struct_dump_addr[NR_CPUS];
	unsigned char *last_task_stack_dump_addr[NR_CPUS];

	char log_path[LOG_PATH_LEN];
	unsigned char *rdr_ap_area_map_addr;	/* rdr非配给ap内存的映射地址 */
	module_dump_mem_info module_dump_info[MODU_MAX];
	u64 wdt_kick_slice[WDT_KICK_SLICE_TIMES];
	unsigned char device_id[PRODUCT_DEVICE_LEN];
	u64 bbox_version;	/* 表示BBox版本信息 */
	unsigned int end_magic;	/* 标记结构体末尾，用于判断结构体范围 */
	char reserved[1];	/*sizeof(AP_EH_ROOT)=1024byte*/
} AP_EH_ROOT;			/*AP_EH_ROOT占用2K空间，通过get_rdr_hisiap_dump_addr函数预留 */

/*外部可以使用的变量声明*/
void get_product_version(char *version, size_t count);
void print_debug_info(void);
int rdr_hisiap_dump_init(struct rdr_register_module_result *retinfo);
void rdr_hisiap_dump(u32 modid, u32 etype, u64 coreid,
		     char *log_path, pfn_cb_dump_done pfn_cb);

/* 测试函数声明 */
void ap_exch_task_stack_dump(int taskPid);
void ap_exch_buf_show(unsigned int offset, unsigned int size);
void ap_exch_hex_dump(unsigned char *buf, unsigned int size,
		      unsigned char per_row);
int ap_exchUNDEF(void *arg);
int ap_exchSWI(void *arg);
int ap_exchPABT(void *arg);
int ap_exchDABT(void *arg);
