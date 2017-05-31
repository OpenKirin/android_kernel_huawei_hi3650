#ifndef	__HISI_HISEE_H__
#define	__HISI_HISEE_H__
#include <linux/device.h>
#include <linux/wakelock.h>

/* Hisee module general error code*/
#define HISEE_OK             (0)
#define HISEE_ERROR          (-10002)
#define HISEE_NO_RESOURCES   (-10003)
#define HISEE_INVALID_PARAMS (-6)
#define HISEE_CMA_DEVICE_INIT_ERROR (-10005)
#define HISEE_IOCTL_NODE_CREATE_ERROR (-10006)
#define HISEE_POWER_NODE_CREATE_ERROR (-10007)
#define HISEE_THREAD_CREATE_ERROR     (-10008)
#define HISEE_RPMB_MODULE_INIT_ERROR  (-11)
#define HISEE_BULK_CLK_INIT_ERROR     (-10010)
#define HISEE_BULK_CLK_ENABLE_ERROR   (-10011)

/* Hisee module specific error code*/
#define HISEE_RPMB_KEY_WRITE_ERROR (-1000)
#define HISEE_RPMB_KEY_READ_ERROR  (-1001)
#define HISEE_COS_VERIFICATITON_ERROR  (-1002)
#define HISEE_IMG_PARTITION_MAGIC_ERROR  (-1003)
#define HISEE_IMG_PARTITION_FILES_ERROR  (-1004)
#define HISEE_IMG_SUB_FILE_NAME_ERROR    (-1005)
#define HISEE_SUB_FILE_SIZE_CHECK_ERROR   (-1006)
#define HISEE_SUB_FILE_OFFSET_CHECK_ERROR (-1007)
#define HISEE_IMG_SUB_FILE_ABSENT_ERROR  (-1008)
#define HISEE_FS_SUB_FILE_ABSENT_ERROR   (-1009)

#define HISEE_OPEN_FILE_ERROR    (-2000)
#define HISEE_READ_FILE_ERROR    (-2001)
#define HISEE_WRITE_FILE_ERROR   (-2002)
#define HISEE_CLOSE_FILE_ERROR   (-2003)
#define HISEE_LSEEK_FILE_ERROR   (-2004)
#define HISEE_OUTOF_RANGE_FILE_ERROR   (-2005)

#define HISEE_FS_MALLOC_ERROR          (-3000)
#define HISEE_FS_PATH_ABSENT_ERROR     (-3001)
#define HISEE_FS_OPEN_PATH_ERROR       (-3002)
#define HISEE_FS_COUNT_FILES_ERROR     (-3003)
#define HISEE_FS_PATH_LONG_ERROR       (-3004)
#define HISEE_FS_READ_FILE_ERROR       (-3005)

#define HISEE_POWERCTRL_TIMEOUT_ERROR    (-4000)
#define HISEE_POWERCTRL_NOTIFY_ERROR     (-4001)
#define HISEE_POWERCTRL_RETRY_FAILURE_ERROR     (-4002)
#define HISEE_POWERCTRL_FLOW_ERROR       (-4003)

#define HISEE_FIRST_SMC_CMD_ERROR  (-5000)
#define HISEE_SMC_CMD_TIMEOUT_ERROR  (-5001)
#define HISEE_SMC_CMD_PROCESS_ERROR  (-5002)

#define HISEE_CHANNEL_TEST_CMD_ERROR  (-6000)
#define HISEE_CHANNEL_TEST_RESULT_MALLOC_ERROR  (-6001)
#define HISEE_CHANNEL_TEST_PATH_ABSENT_ERROR  (-6002)
#define HISEE_CHANNEL_TEST_WRITE_RESULT_ERROR  (-6003)

#define HISEE_GET_HISEE_VALUE_ERROR    (-7000)
#define HISEE_SET_HISEE_VALUE_ERROR    (-7001)
#define HISEE_SET_HISEE_STATE_ERROR    (-7002)

#define HISEE_OLD_COS_IMAGE_ERROR      (-8000)


/* ATF service id */
#define HISEE_FN_MAIN_SERVICE_CMD    (0xc5000020)
#define HISEE_FN_CHANNEL_TEST_CMD    (0xc5000040)

/* Lpm3 communication id */
#define HISEE_LPM3_CMD        IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_NOTIFY, 0)
#define HISEE_LPM3_ACK_MAGIC  0xaaccbbdd

#define HISEE_ATF_ACK_SUCCESS 0xaabbccaa
#define HISEE_ATF_ACK_FAILURE 0xaabbcc55

#define HISEE_SM_FLG_OFFSET_IN_EFUSE   (14)
#define HISEE_SM_MODE_MAGIC            (0xffeebbaa)
#define HISEE_DM_MODE_MAGIC            (0xffeebb55)
#define DELAY_BETWEEN_STEPS            (50)

#define HISEE_ATF_MESSAGE_HEADER_LEN   (16)
#define HISEE_ATF_COS_APPDATA_TIMEOUT  (15000)
#define HISEE_ATF_WRITE_RPMBKEY_TIMEOUT (1000)
#define HISEE_ATF_OTP_TIMEOUT        (10000)
#define HISEE_ATF_COS_TIMEOUT        (30000)
#define HISEE_ATF_SLOADER_TIMEOUT    (30000)
#define HISEE_ATF_MISC_TIMEOUT    (30000)
#define HISEE_ATF_APPLICATION_TIMEOUT    (60000)
#define HISEE_ATF_GENERAL_TIMEOUT        (30000)

#define SIZE_1K              (1024)
#define SIZE_1M              (1024 * SIZE_1K)

#define MAX_PATH_NAME_LEN    (128)
#define HISEE_FILESYS_DIR_ENTRY_SIZE    (1024)
#define HISEE_FILESYS_DEFAULT_MODE       0770  /* default mode when creating a file or dir if user doesn't set mode*/

#define HISEE_SHARE_BUFF_SIZE (512 * SIZE_1K)
#define HISEE_CMD_NAME_LEN    (128)
#define HISEE_BUF_SHOW_LEN    (128)
#define HISEE_ERROR_DESCRIPTION_MAX  (64)
#define HISEE_APDU_DATA_LEN_MAX      (261)
#define TEST_RESULT_SIZE_DEFAULT     (0x40000)

#define HISEE_IMAGE_PARTITION_NAME  "hisee_img"
#define HISEE_IMAGE_A_PARTION_NAME   "hisee_img_a"
#define HISEE_IMG_PARTITION_SIZE     (4 * SIZE_1M)
#define HISEE_SW_VERSION_MAGIC_VALUE (0xa5a55a5a)

#define HISEE_MIN_MISC_IMAGE_NUMBER  (1)
#define HISEE_MAX_MISC_IMAGE_NUMBER  (5)

#define HISEE_FS_PARTITION_NAME     "/hisee_fs/"
#define HISEE_FS_APDU_TEST_NAME     "test.apdu.bin"
#define HISEE_FS_APDU_APPLET_NAME   "applet.apdu.bin"

#define HISEE_PWROFF_LOCK	(1)
#define HISEE_PWROFF_NOLOCK	(0)
#define HISEE_FACTORY_TEST_VERSION	(0x12345678)
#define HISEE_SERVICE_WORK_VERSION	(0)
#define HISEE_COS_UPGRADE_RUNNING_FLG (0x87654321u)

/* hisee image info */
#define HISEE_IMG_MAGIC_LEN		    (4)
#define HISEE_IMG_MAGIC_VALUE		"inse"
#define HISEE_IMG_TIME_STAMP_LEN	(20)
#define HISEE_IMG_DATA_LEN	        (4)
#define HISEE_IMG_SUB_FILE_LEN	    (4)
#define HISEE_IMG_HEADER_LEN        (HISEE_IMG_MAGIC_LEN + HISEE_IMG_TIME_STAMP_LEN + HISEE_IMG_DATA_LEN + HISEE_IMG_SUB_FILE_LEN)
#define HISEE_IMG_SUB_FILE_MAX		(8)
#define HISEE_IMG_SUB_FILE_NAME_LEN	(8)
#define HISEE_IMG_SUB_FILE_OFFSET_LEN (4)
#define HISEE_IMG_SUB_FILE_DATA_LEN (4)
#define HISEE_IMG_SUB_FILES_LEN     (HISEE_IMG_SUB_FILE_NAME_LEN + HISEE_IMG_SUB_FILE_OFFSET_LEN + HISEE_IMG_SUB_FILE_DATA_LEN)
#define HISEE_IMG_SLOADER_NAME		"SLOADER"
#define HISEE_IMG_COS_NAME			"COS"
#define HISEE_IMG_OTP_NAME			"OTP"
#define HISEE_IMG_OTP0_NAME			"OTP0"
#define HISEE_IMG_OTP1_NAME			"OTP1"
#define HISEE_IMG_MISC_NAME			"MISC"

#define HISEE_MISC_VERSION0			(0x20)

/* hisee apdu cmd type */
#define HISEE_SET_KEY	(0)
#define HISEE_DEL_TEST_APPLET	(1)

/* timeout of thread exit when waiting semaphore, 30s */
#define HISEE_THREAD_WAIT_TIMEOUT (msecs_to_jiffies(30000))

#define check_and_print_result()  \
do {\
	if (ret != HISEE_OK)\
		pr_err("%s() run failed\n", __func__);\
	else\
		pr_err("%s() run success\n", __func__);\
} while (0)

#define set_errno_and_return(err) \
	ret = err;\
	atomic_set(&g_hisee_errno, ret);\
	return ret

#define bypass_space_char() \
do {\
	if (offset >= HISEE_CMD_NAME_LEN) {\
		pr_err("hisee_cmd is bad.\n");\
		pr_err("%s(): hisee channel test cmd is bad\n", __func__);\
		set_errno_and_return(HISEE_CHANNEL_TEST_CMD_ERROR);\
	}\
	if (0x20 != buff[offset])\
		break;\
	offset++;\
} while (1)

#define hisee_mdelay(n)  msleep(n)
#define hisee_delay(n)   msleep((n) * 1000)

typedef struct _HISEE_ERRCODE_ITEM_DES {
	int err_code;	/* see error code definition */
	char err_description[HISEE_ERROR_DESCRIPTION_MAX]; /* error code description */
} hisee_errcode_item_des;

typedef struct _HISEE_DRIVER_FUNCTION {
	char *function_name;	/* function cmd string */
	int (*function_ptr)(void *buf, int para); /* function cmd process */
} hisee_driver_function;

struct linux_dirent {
	unsigned long d_ino;
	unsigned long d_off;
	unsigned short d_reclen;
	char d_name[1];
};

/* channel test for hisee */
#define CMD_MAX_SIZE            128
#define TEST_DIRECTORY_PATH     "/data/hisee_test"
#define TEST_SUCCESS_FILE       "/data/hisee_test/test_success.txt"
#define TEST_FAIL_FILE          "/data/hisee_test/test_fail.txt"
#define TEST_RESULT_FILE        "/data/hisee_test/test_result.img"

#define ALIGN_UP_4KB(x)     (((x) + 0xFFF)&(~0xFFF))
#define CHANNEL_TEST_RESULT_SIZE_DEFAULT    (0x40000)

typedef union _TIMESTAMP_INFO {
	struct timestamp {
		unsigned char second;
		unsigned char minute;
		unsigned char hour;
		unsigned char day;
		unsigned char month;
		unsigned char padding;
		unsigned short year;
	} timestamp;
	unsigned long value;
} timestamp_info;

typedef struct _COSIMAGE_VERSION_INFO_ {
	unsigned int magic;
	unsigned int img_version_num;
	timestamp_info img_timestamp;
} cosimage_version_info;

typedef struct _HISEE_WORK_STRUCT {
	char *buffer;
	phys_addr_t phy;
	unsigned int size;
} hisee_work_struct;

typedef enum _HISEE_IMAGE_A_ACCESS_TYPE_ {
	SW_VERSION_READ_TYPE = 0,
	SW_VERSION_WRITE_TYPE,
	COS_UPGRADE_RUN_READ_TYPE,
	COS_UPGRADE_RUN_WRITE_TYPE,
	MISC_VERSION_READ_TYPE,
	MISC_VERSION_WRITE_TYPE,
} hisee_image_a_access_type;

typedef enum  _HISEE_IMG_FILE_TYPE {
	SLOADER_IMG_TYPE = 0,
	COS_IMG_TYPE,
	OTP_IMG_TYPE,
	OTP1_IMG_TYPE,
	MISC0_IMG_TYPE,
	MISC1_IMG_TYPE,
	MISC2_IMG_TYPE,
	MISC3_IMG_TYPE,
	MISC4_IMG_TYPE,
	MAX_IMG_TYPE,
} hisee_img_file_type;

typedef enum _HISEE_POWER_OPERATION {
	HISEE_POWER_OFF = 0x01000100,
	HISEE_POWER_ON_BOOTING = 0x01000101,
	HISEE_POWER_ON_UPGRADE = 0x01000102,
	HISEE_POWER_ON_UPGRADE_SM = 0x01000103,
	HISEE_POWER_ON_BOOTING_MISC = 0x01000104,
} hisee_power_operation;

typedef enum _HISEE_STATE {
	HISEE_STATE_POWER_DOWN = 0,
	HISEE_STATE_POWER_UP   = 1,
	HISEE_STATE_MISC_READY = 2,
	HISEE_STATE_COS_READY  = 3,
	HISEE_STATE_POWER_DOWN_DOING = 4,
	HISEE_STATE_POWER_UP_DOING   = 5,
	HISEE_STATE_MAX,
} hisee_state;

typedef enum {
	CMD_UPGRADE_SLOADER = 0,
	CMD_UPGRADE_OTP,
	CMD_UPGRADE_COS,
	CMD_UPGRADE_MISC,
	CMD_UPGRADE_APPLET,
	CMD_PRESAVE_COS_APPDATA,
	CMD_WRITE_RPMB_KEY,
	CMD_SET_LCS_SM,
	CMD_SET_STATE,
	CMD_GET_STATE,
	CMD_APDU_RAWDATA,
	CMD_FACTORY_APDU_TEST,
	CMD_HISEE_CHANNEL_TEST,
	CMD_END,
} se_smc_cmd;

typedef enum {
	HISEE_POWER_NONE = 0,
	HISEE_POWER_ON_BOOTING_SUCCESS,
	HISEE_POWER_ON_BOOTING_FAILURE,
	HISEE_POWER_ON_UPGRADE_SUCCESS,
	HISEE_POWER_ON_UPGRADE_FAILURE,
	HISEE_POWER_OFF_SUCCESS,
	HISEE_POWER_OFF_FAILURE,
} hisee_powerctrl_status;

typedef enum {
	HISEE_FACTORY_TEST_FAIL = -1,
	HISEE_FACTORY_TEST_SUCCESS = 0,
	HISEE_FACTORY_TEST_RUNNING = 1,
	HISEE_FACTORY_TEST_NORUNNING = 2,
} hisee_factory_test_status;
/* hisee_img partition struct */
typedef struct _IMG_FILE_INFO {
	char name[HISEE_IMG_SUB_FILE_NAME_LEN];
	unsigned int offset;
	unsigned int size;
} img_file_info;

typedef struct _HISEE_IMG_HEADER {
	char magic[HISEE_IMG_MAGIC_LEN];
	char time_stamp[HISEE_IMG_TIME_STAMP_LEN];
	unsigned int total_size;
	unsigned int file_cnt;
	img_file_info file[HISEE_IMG_SUB_FILE_MAX];
	unsigned int sw_version_cnt;
	unsigned int misc_image_cnt;
} hisee_img_header;

/* message header between kernel and atf */
typedef struct _ATF_MESSAGE_HEADER {
/* atf cmd execute type, such as otp, cos, sloader at all, kernel set and atf read it*/
	unsigned int cmd;
/* atf cmd execute result indication, use a magic value to indicate success, atf set it and check in kernel*/
	unsigned int ack;
/* tell atf store the result to this buffer when doing channel test */
	unsigned int test_result_phy;
/* tell atf the size of buffer when doing channel test */
	unsigned int test_result_size;
} atf_message_header;

typedef struct _APDU_ACK_HEADER {
	unsigned int ack_len;
	unsigned char ack_buf[HISEE_APDU_DATA_LEN_MAX + 1];
} apdu_ack_header;
typedef struct _HISEE_MODULE_DATA {
	struct device *cma_device; /* cma memory allocator device */
	struct clk *hisee_clk;  /* buck 0 voltage hold at 0.8v */
	void *apdu_command_buff_virt;
	phys_addr_t apdu_command_buff_phy;
	struct semaphore atf_sem;    /* do sync for smc message between kernel and atf */
	hisee_img_header hisee_img_head; /* store the parsed result for hisee_img partition header */
	apdu_ack_header  apdu_ack; /* store the apdu response */
	struct mutex hisee_mutex; /* mutex for global resources */
	hisee_work_struct channel_test_item_result;
	bool img_header_is_parse; /* indicate the hisee_img partition whether is parsed */
	unsigned int rpmb_is_ready; /* indicate the rpmb has been initialiazed */
	unsigned int smc_cmd_running; /*indicate the smc is running */
	int power_on_count;  /*indicate the number of hisee poweron*/
	hisee_factory_test_status factory_test_state; /*indicate the factory test status */
	struct wake_lock wake_lock;
} hisee_module_data;
typedef struct _TIMER_ENTRY_LIST {
	struct list_head list;
	struct timer_list timer;
	atomic_t handled;
} timer_entry_list;

static int hisee_parse_img_header(char *buffer);
static int cos_image_upgrade_func(void *buf, int para);
static int otp_image_upgrade_func(void *buf, int para);
static int misc_image_upgrade_func(void *buf, int para);
static int write_rpmb_key_func(void *buf, int para);
static int set_sm_lcs_func(void *buf, int para);
static int factory_apdu_test_func(void *buf, int para);
static int hisee_channel_test_func(void *buf, int para);
static int hisee_poweron_booting_func(void *buf, int para);
static int hisee_poweron_upgrade_func(void *buf, int para);
static int hisee_poweroff_func(void *buf, int para);
static int hisee_poweron_timeout_func(void *buf, int para);
static int hisee_total_manafacture_func(void *buf, int para);
static int hisee_parallel_manafacture_func(void *buf, int para);
static int write_apdu_command_func (char *apdu_buf, int apdu_len);
#ifdef __SLT_FEATURE__
static int hisee_read_slt_func(void *buf, int para);
static int hisee_parallel_total_slt_func(void *buf, int para);
static int application_upgrade_func(void *buf, int para);
#endif
#endif
