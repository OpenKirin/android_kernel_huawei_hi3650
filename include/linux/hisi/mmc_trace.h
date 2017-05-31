/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mmc_trace.h
  �� �� ��   : ����
  ��    ��   : Ԭ�� 00145322
  ��������   : 2015��3��9��
  ����޸�   :
  ��������   : mmc_trace.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��9��
    ��    ��   : Ԭ�� 00145322
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __MMC_TRACE__
#define __MMC_TRACE__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MMC_TRACE_TOTAL_SIZE         (0x40000) /*256k*/

#define MMC_TRACE_BUFFER_START       (g_mmc_trace_buffer_addr)
#define MMC_TRACE_FD_SIZE            (g_mmc_trace_fd_size)

#define MMC_TRACE_INIT_START_ADDR    (MMC_TRACE_BUFFER_START + MMC_TRACE_FD_SIZE)
#define MMC_TRACE_INIT_SIZE          (0x6C00) /*27K*/

#define MMC_TRACE_RESERVE_START_ADDR (MMC_TRACE_INIT_START_ADDR + MMC_TRACE_INIT_SIZE)
#define MMC_TRACE_RESERVE_SIZE       (0x400) /*1K*/

#define MMC_TRACE_COMM_START_ADDR    (MMC_TRACE_RESERVE_START_ADDR + MMC_TRACE_RESERVE_SIZE)
#define MMC_TRACE_COMM_SIZE          (0x20000 - MMC_TRACE_RESERVE_SIZE - MMC_TRACE_INIT_SIZE - MMC_TRACE_FD_SIZE)

#define MMC_TRACE_PERF_START_ADDR    (MMC_TRACE_COMM_START_ADDR + MMC_TRACE_COMM_SIZE)
#define MMC_TRACE_PERF_SIZE          (0x20000-8)/*128K-8*/

#define MMC_PERFORMANCE_FLAG   	 (0x1 << 0)
#define MMC_COMMON_FLAG		(0x1 << 1)

#define MMC_TRACE_INIT_NAME          "mmc_trace_init"
#define MMC_TRACE_COMM_NAME          "mmc_trace_comm"
#define MMC_TRACE_PERF_NAME          "mmc_trace_perf"

#define MMC_TRACE_INIT_PATH    		 "/data/hisi_logs/mmc_trace_init.bin"
#define MMC_TRACE_COMM_PATH    	     "/data/hisi_logs/mmc_trace_comm.bin"
#define MMC_TRACE_PERF_PATH    		 "/data/hisi_logs/mmc_trace_perf.bin"
#define MMC_TRACE_PERF_RAWDATA_PATH  "/data/hisi_logs/mmc_trace_perf_rawdata.bin"
#define MMC_TRACE_RAW_DATA_PATH      "/data/hisi_logs/mmc_trace_rawdata.bin"

/* ��ģ���쳣,�ݶ���������ֵ���޸�,rdrΪEMMC�����ID��ΧΪ0x81fffeff~0x81ffffff��������rdr_pub.h��*/
#define RDR_MODID_MMC_START HISI_BB_MOD_EMMC_START
#define RDR_MODID_MMC_INIT_FAIL    		0x81ffff00
#define RDR_MODID_MMC_CMD_TIMEOUT 		0x81ffff01
#define RDR_MODID_MMC_END HISI_BB_MOD_EMMC_END

#define MMC_TRACE_SCRATCH_SIZE     16
#define MMC_TRACE_TIME_SIZE        18
#define MMC_TRACE_DEVNAME_SIZE     5

#define QUEUE_NAME_LEN 16

#define MOD_ADD(x, y, m)  (((x + y) > m) ? ((x + y) - m) : (x + y))
#define MOD_SUB(x, y, m)  ((x < y) ? (x + m - y) : (x - y))
#define MOD_INC(x, m)     (((x + 1) == m) ? 0 : (x + 1))


/*���ܼ�¼����*/
#define MMC_PERF_TRACE_FLAG

#define MMCTRACE_DEBUGPL(lvl, x...) do { \
	if ((lvl)&g_mmctrace_dbg_lvl) { \
		printk(x); \
		printk("\n");\
	} \
} while (0)

/* cmd defines */
#define CMD13                           13
#define CMD18                           18
#define CMD25                           25

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
   	EMMC = 0,       /*1*/
	SD,
	SDIO,
	DEV_TRACE_MAX
}MMC_DEVICE_TYPE;

typedef enum
{
	TRACE_INIT = 0,       /*1*/
	TRACE_COMM,
	TRACE_PERF,
	TRACE_MAX
}MMC_TRACE_TYPE;

typedef enum
{
    /*file system*/
	POS_EXT4_DA_WRTITE_BEGIN = 0x0,
	POS_EXT4_DA_WRTITE_END   = 0x1,

	/*block*/
	POS_BLOCK_GETRQ          = 0x10,
	POS_BLOCK_SLEEP_RQ       = 0x11,
	POS_BLOCK_RQ_ISSUE       = 0x12,
	POS_BLOCK_RQ_COM         = 0x13,

	/*mmc*/
	POS_MMC_RW_START         = 0x20,
	POS_MMC_RW_END           = 0x21,

	MMC_PERF_POS_MAX
}MMC_PERF_POS;


struct queue
{
    char name[QUEUE_NAME_LEN];
    spinlock_t lock;
    unsigned int max;
    unsigned int head; /*to write in index*/
    unsigned int tail; /*to read out index*/
    unsigned int in;   /*in times*/
    unsigned int out;  /*out times*/
    long long reserve;	/* make sure to keep 8B aligning */
    char data[4];
};

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
struct mmc_trace_client{
	char *client_name;
	void *mmc_trace_init;
	void *mmc_trace_comm;
	void *mmc_trace_perf;
	int   mmc_trace_init_mmc_flag;
	int   mmc_trace_init_sd_flag;
	int   mmc_trace_init_sdio_flag;
	bool  mmc_trace_emmc_init_status;
	bool  mmc_trace_sd_init_status;
	bool  mmc_trace_sdio_status;
	bool  mmc_trace_reset_initfail;
	bool  mmc_trace_tofile_comm;
	bool  mmc_trace_tofile_perf;
	bool  mmc_trace_reset_cmdtimeout;
	spinlock_t init_lock;
	spinlock_t comm_lock;
	spinlock_t lock;
	int id;
	u64 proc_flag;
	int reserved[16];
	size_t buff_size;
	u8 buff[];
};

struct mmc_trace_init{
	char *init_save_filepath;
	char *name;
	int reserved[16];
	size_t buff_size;
	u8 init_buff[];
};

struct mmc_trace_comm{
	char *comm_save_filepath;
	char *name;
	int reserved[16];
	size_t buff_size;
	u8 comm_buff[];
};

struct mmc_trace_perf{
	char *perf_save_filepath;
	char *name;
	int reserved[16];
	size_t buff_size;
	u8 perf_buff[];
};

struct mmc_trace_perf_point_record{
	char  id;
	char  pos;
	short int reserved;
	unsigned int  reserved1;
	unsigned int  arg1;
	unsigned int  arg2;
};

struct mmc_trace_perf_record_exp{
	u64   time;
	char  id;
	char  pos;
	short int reserved;
	unsigned int  reserved1;
	unsigned int  arg1;
	unsigned int  arg2;
};

struct mmc_trace_perf_record_act{
	char time[16];
	char device[8];
	char cmd[8];
	char flag1[8];
	char flag2[8];
	char end[3];
};

struct snprintf_ctxt
{
    char *next;
    int avail;
};

typedef void (*mmc_trace_printf_putc_ptr)(unsigned , struct mmc_trace_client *);

/*****************************************************************************
  7 UNION����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/

/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

extern struct mmc_trace_client *mmc_trace_client_init (void);
extern int mmc_trace_comm_record (struct mmc_host *host,const char *fmt,...);
extern void mmc_trace_record(struct mmc_host *host, struct mmc_request *mrq);
extern void mmc_trace_init_begin(struct mmc_host *host);
extern void mmc_trace_init_end(struct mmc_host *host);
extern void mmc_trace_perf_record (struct mmc_trace_perf_point_record * record);
extern void mmc_trace_emmc_init_fail_reset(void);
extern void mmc_trace_emmc_cmd_timeout_reset(void);
extern void dw_mci_reg_dump_fortrace(struct mmc_host *mmc);
extern int mntn_filesys_rm_file(const char *fullname);
extern void mmc_trace_fd_init(void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

