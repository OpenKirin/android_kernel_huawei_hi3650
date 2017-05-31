#include <asm/compiler.h>
#include <linux/compiler.h>
#include <linux/fd.h>
#include <linux/tty.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/semaphore.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_reserved_mem.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/atomic.h>
#include <linux/notifier.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/hisi/ipc_msg.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/kirin_partition.h>
#include <linux/clk.h>
#include "hisi_hisee.h"

#define DSM_NFC_HISEE_COS_IMAGE_UPGRADE_ERROR_NO ((long)923002015)
#define DSM_NFC_HISEE_POWER_ON_OFF_ERROR_NO ((long)923002016)
#define DSM_NFC_HISEE_APDU_COMMAND_OPERATION_ERROR_NO ((long)923002017)


static hisee_module_data g_hisee_data;
static atomic_t g_hisee_errno;
static hisee_powerctrl_status powerctrl_status;
static unsigned int g_misc_version = 0;
static bool g_daemon_created = false;
static int g_unhandled_timer_cnt = 0;
static struct semaphore g_hisee_poweroff_sem;
static struct mutex g_poweron_timeout_mutex;
static struct list_head g_unhandled_timer_list;

extern int nfc_record_dmd_info(long dmd_no, const char *dmd_info);
extern int get_rpmb_init_status(void);
extern int get_rpmb_key_status(void);
extern int get_efuse_hisee_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);
extern int set_efuse_hisee_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);
extern void register_flash_hisee_otp_fn(int (*fn_ptr)(void));
extern void release_hisee_semphore(void);

static hisee_errcode_item_des g_errcode_items_des[] = {
	{HISEE_OK, "no error\n"},
	{HISEE_ERROR, "general error\n"},
	{HISEE_NO_RESOURCES, "general no resources\n"},
	{HISEE_INVALID_PARAMS, "general invalid paramters\n"},
	{HISEE_CMA_DEVICE_INIT_ERROR, "cma device init error\n"},
	{HISEE_IOCTL_NODE_CREATE_ERROR, "ioctl node create error\n"},
	{HISEE_POWER_NODE_CREATE_ERROR, "power node create error\n"},
	{HISEE_THREAD_CREATE_ERROR, "thread create error\n"},
	{HISEE_RPMB_MODULE_INIT_ERROR, "rpmb module init error\n"},
	{HISEE_BULK_CLK_INIT_ERROR, "bulk clk dts node init error\n"},
	{HISEE_BULK_CLK_ENABLE_ERROR, "bulk clk error\n"},

	{HISEE_RPMB_KEY_WRITE_ERROR, "write rpmb key fail\n"},
	{HISEE_RPMB_KEY_READ_ERROR, "read rpmb key fail\n"},
	{HISEE_COS_VERIFICATITON_ERROR, "cos img verify fail\n"},
	{HISEE_IMG_PARTITION_MAGIC_ERROR, "img partition magic error\n"},
	{HISEE_IMG_PARTITION_FILES_ERROR, "img partition files error\n"},
	{HISEE_IMG_SUB_FILE_NAME_ERROR, "sub image invalid error\n"},
	{HISEE_SUB_FILE_SIZE_CHECK_ERROR, "sub file size error\n"},
	{HISEE_SUB_FILE_OFFSET_CHECK_ERROR, "sub file offset error\n"},
	{HISEE_IMG_SUB_FILE_ABSENT_ERROR, "sub image absent error\n"},
	{HISEE_FS_SUB_FILE_ABSENT_ERROR, "sub fs file absent error\n"},

	{HISEE_OPEN_FILE_ERROR, "open file error\n"},
	{HISEE_READ_FILE_ERROR, "read file error\n"},
	{HISEE_WRITE_FILE_ERROR, "write file error\n"},
	{HISEE_CLOSE_FILE_ERROR, "close file error\n"},
	{HISEE_LSEEK_FILE_ERROR, "seek file error\n"},
	{HISEE_OUTOF_RANGE_FILE_ERROR, "out of file threshold error\n"},

	{HISEE_FS_MALLOC_ERROR, "fs partition malloc error\n"},
	{HISEE_FS_PATH_ABSENT_ERROR, "fs partition absent error\n"},
	{HISEE_FS_OPEN_PATH_ERROR, "fs partition open error\n"},
	{HISEE_FS_COUNT_FILES_ERROR, "fs partition calculate files error\n"},
	{HISEE_FS_PATH_LONG_ERROR, "sub fs file path too long error\n"},
	{HISEE_FS_READ_FILE_ERROR, "sub fs file read error\n"},

	{HISEE_POWERCTRL_TIMEOUT_ERROR, "hisee powerctrl timeout error\n"},
	{HISEE_POWERCTRL_NOTIFY_ERROR, "hisee powerctrl notify error\n"},
	{HISEE_POWERCTRL_RETRY_FAILURE_ERROR, "hisee powerctrl retry failure error\n"},
	{HISEE_POWERCTRL_FLOW_ERROR, "hisee powerctrl flow error\n"},

	{HISEE_FIRST_SMC_CMD_ERROR, "the fisrt step in smc transcation error\n"},
	{HISEE_SMC_CMD_TIMEOUT_ERROR, "the smc transcation timeout error\n"},
	{HISEE_SMC_CMD_PROCESS_ERROR, "the smc transcation failure error\n"},

	{HISEE_CHANNEL_TEST_CMD_ERROR, "invalid channel test cmd error\n"},
	{HISEE_CHANNEL_TEST_RESULT_MALLOC_ERROR, "channel test result buf malloc error\n"},
	{HISEE_CHANNEL_TEST_PATH_ABSENT_ERROR, "channel test input file error\n"},
	{HISEE_CHANNEL_TEST_WRITE_RESULT_ERROR, "channel test write result file error\n"},

	{HISEE_GET_HISEE_VALUE_ERROR,"get hisee lcs mode error\n"},
	{HISEE_SET_HISEE_VALUE_ERROR,"set hisee lcs mode error\n"},
	{HISEE_SET_HISEE_STATE_ERROR,"set hisee state error\n"},

	{HISEE_OLD_COS_IMAGE_ERROR,"old cos image error\n"}
};

/* create a virtual device for dma_alloc */
#define HISEE_DEVICE_NAME "hisee"
#define MANAFACTOR_CMD_INDEX 2

static hisee_driver_function g_hisee_atf_function_list[] = {
	{"cos_image_upgrade", cos_image_upgrade_func},
	{"hisee_channel_test", hisee_channel_test_func},
	{"hisee_parallel_factory_action", hisee_parallel_manafacture_func},
#ifdef __SLT_FEATURE__
	{"hisee_slt_action", hisee_parallel_total_slt_func},
	{"hisee_check_slt", hisee_read_slt_func},
#endif
	{NULL, NULL},
};

static hisee_driver_function g_hisee_lpm3_function_list[] = {
	{"hisee_poweron_upgrade", hisee_poweron_upgrade_func},
	{"hisee_poweron_timeout", hisee_poweron_timeout_func},
	{"hisee_poweron", hisee_poweron_booting_func},
	{"hisee_poweroff", hisee_poweroff_func},
	{NULL, NULL},
};


noinline static int atfd_hisee_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)function_id;
} /*lint !e715*/

static int set_hisee_state(hisee_state state)
{
	int ret = HISEE_OK;
	if (state >= HISEE_STATE_MAX) {
		pr_err("%s() state=%d invalid\n", __func__, (int)state);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	ret = atfd_hisee_smc((u64)HISEE_FN_MAIN_SERVICE_CMD, (u64)CMD_SET_STATE, (u64)state, (u64)0);
	return ret;
}
static int get_hisee_lcs_mode(unsigned int *mode)
{
	int ret;
	int hisee_value[2] = {0};

	ret = get_efuse_hisee_value((unsigned char *)hisee_value, 8, 1000);
	if (HISEE_OK != ret) {
		pr_err("%s() get_efuse_hisee_value failed,ret=%d\n", __func__, ret);
		set_errno_and_return(HISEE_GET_HISEE_VALUE_ERROR);
	}
	*mode = ((hisee_value[1] >> HISEE_SM_FLG_OFFSET_IN_EFUSE) & 1) ? HISEE_SM_MODE_MAGIC : HISEE_DM_MODE_MAGIC;
	return ret;
}
static int set_hisee_lcs_sm_flg(void)
{
	int ret;
	int hisee_value[2] = {0};

	hisee_value[1] = (1 << HISEE_SM_FLG_OFFSET_IN_EFUSE);
	ret = set_efuse_hisee_value((unsigned char *)hisee_value, 8, 1000);
	if (HISEE_OK != ret) {
		pr_err("%s() set_efuse_hisee_value failed,ret=%d\n", __func__, ret);
		set_errno_and_return(HISEE_SET_HISEE_VALUE_ERROR);
	}
	return ret;
}

static int check_sw_version_null(const cosimage_version_info *info)
{
	if (!info->magic && !info->img_version_num &&
		!info->img_timestamp.timestamp.year && !info->img_timestamp.timestamp.month
		&& !info->img_timestamp.timestamp.day && !info->img_timestamp.timestamp.hour
		&& !info->img_timestamp.timestamp.minute && !info->img_timestamp.timestamp.second)
		return 1;
	else
		return 0;
}

static int check_timestamp_valid(const cosimage_version_info *info)
{
	if (info->img_timestamp.timestamp.year < 2016)
		return 0;

	/*the year of deadline is 2050? I Don't konw! */
	if (info->img_timestamp.timestamp.year >= 2050)
		return 0;

	if (info->img_timestamp.timestamp.month > 12)
		return 0;

	/*the judge is not accurate, because not all month has 31 day,
	  depend on the value of year and month*/
	if (info->img_timestamp.timestamp.day > 31)
		return 0;

	if (info->img_timestamp.timestamp.hour >= 24)
		return 0;

	if (info->img_timestamp.timestamp.minute >= 60)
		return 0;

	if (info->img_timestamp.timestamp.second >= 60)
		return 0;

	return 1;
}

static void parse_timestamp(const char *timestamp_str, cosimage_version_info *info)
{
	unsigned short value_short;
	unsigned char  value_char;

	info->img_timestamp.value = 0x0;

	value_short = (timestamp_str[0] - 0x30) * 1000 + (timestamp_str[1] - 0x30) * 100
			+ (timestamp_str[2] - 0x30) * 10 + (timestamp_str[3] - 0x30); /*lint !e734*/
	info->img_timestamp.timestamp.year = value_short;

	value_char = (timestamp_str[5] - 0x30) * 10 + (timestamp_str[6] - 0x30); /*lint !e734*/
	info->img_timestamp.timestamp.month = value_char;

	value_char = (timestamp_str[8] - 0x30) * 10 + (timestamp_str[9] - 0x30); /*lint !e734*/
	info->img_timestamp.timestamp.day = value_char;

	value_char = (timestamp_str[11] - 0x30) * 10 + (timestamp_str[12] - 0x30); /*lint !e734*/
	info->img_timestamp.timestamp.hour = value_char;

	value_char = (timestamp_str[14] - 0x30) * 10 + (timestamp_str[15] - 0x30); /*lint !e734*/
	info->img_timestamp.timestamp.minute = value_char;

	value_char = (timestamp_str[17] - 0x30) * 10 + (timestamp_str[18] - 0x30); /*lint !e734*/
	info->img_timestamp.timestamp.second = value_char;

	return;
}

#ifdef HISEE_DEBUG
static void dump_partition_version(const cosimage_version_info *info, unsigned int access_type)
{
	pr_err("%s(): enter, access_type=%d.\n", __func__, access_type);
	pr_err("sw_version_magic=%x.\n", info->magic);
	pr_err("sw_version_num=%d.\n", info->img_version_num);
	pr_err("%d-%d-%d %d:%d:%d\n", info->img_timestamp.timestamp.year,
		    info->img_timestamp.timestamp.month, info->img_timestamp.timestamp.day, info->img_timestamp.timestamp.hour,
		    info->img_timestamp.timestamp.minute, info->img_timestamp.timestamp.second);
	return;
}
#endif

static int access_hisee_image_partition(char *data_buf, hisee_image_a_access_type access_type)
{
	int fd = -1;
	ssize_t cnt;
	mm_segment_t old_fs;
	char fullpath[128] = {0};
	long file_offset;
	unsigned long size;
	int ret;

	flash_find_hisee_ptn(HISEE_IMAGE_A_PARTION_NAME, fullpath);
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	if ((SW_VERSION_WRITE_TYPE == access_type)
		|| (COS_UPGRADE_RUN_WRITE_TYPE == access_type)
		|| (MISC_VERSION_WRITE_TYPE == access_type))
		fd = (int)sys_open(fullpath, O_WRONLY, HISEE_FILESYS_DEFAULT_MODE);
	else
		fd = (int)sys_open(fullpath, O_RDONLY, HISEE_FILESYS_DEFAULT_MODE);
	if (fd < 0) {
		pr_err("%s():open %s failed\n", __func__, fullpath);
		ret = HISEE_OPEN_FILE_ERROR;
		set_fs(old_fs);
		set_errno_and_return(ret);
	}
	if ((SW_VERSION_WRITE_TYPE == access_type)
		|| (SW_VERSION_READ_TYPE == access_type)) {
		file_offset = HISEE_IMG_PARTITION_SIZE - SIZE_1K;
		size = sizeof(cosimage_version_info);
	} else if ((COS_UPGRADE_RUN_WRITE_TYPE == access_type)
		|| (COS_UPGRADE_RUN_READ_TYPE == access_type)){
		file_offset = (long)((HISEE_IMG_PARTITION_SIZE - SIZE_1K) + 32);
		size = sizeof(unsigned int);
	} else {
		file_offset = (long)((HISEE_IMG_PARTITION_SIZE - SIZE_1K) + 32 + 32);
		size = sizeof(cosimage_version_info);
	}

	ret = (int)sys_lseek((unsigned int)fd, file_offset, SEEK_SET);
	if (ret < 0) {
		pr_err("%s(): sys_lseek failed,ret=%d.\n", __func__, ret);
		ret = HISEE_LSEEK_FILE_ERROR;
		sys_close((unsigned int)fd);
		set_fs(old_fs);
		set_errno_and_return(ret);
	}
	if ((SW_VERSION_WRITE_TYPE == access_type)
		|| (COS_UPGRADE_RUN_WRITE_TYPE == access_type)
		|| (MISC_VERSION_WRITE_TYPE == access_type))
		cnt = sys_write((unsigned int)fd, (char __user *)data_buf, size);
	else
		cnt = sys_read((unsigned int)fd, (char __user *)data_buf, size);	

	if (cnt < (ssize_t)(size)) {
		pr_err("%s(): access %s failed, return [%ld]\n", __func__, fullpath, cnt);
		ret = ((SW_VERSION_READ_TYPE == access_type)
			|| (COS_UPGRADE_RUN_READ_TYPE == access_type)
			|| (MISC_VERSION_READ_TYPE == access_type)) ?
			HISEE_READ_FILE_ERROR : HISEE_WRITE_FILE_ERROR;
	} else
		ret = HISEE_OK;

#ifdef HISEE_DEBUG
	if ((SW_VERSION_WRITE_TYPE == access_type)
		|| (SW_VERSION_READ_TYPE == access_type))
		dump_partition_version((const cosimage_version_info *)data_buf, (unsigned int)access_type);
#endif
	sys_close((unsigned int)fd);
	set_fs(old_fs);
	set_errno_and_return(ret);

}


static int exist_newest_cosimage(const cosimage_version_info *curr_ptr, const cosimage_version_info *previous_ptr)
{
	if (!check_timestamp_valid(curr_ptr))
		return 0;
	if (!check_timestamp_valid(previous_ptr))
		return 0;

	if (HISEE_SW_VERSION_MAGIC_VALUE != curr_ptr->magic
		|| HISEE_SW_VERSION_MAGIC_VALUE != previous_ptr->magic)
		return 0;

	if (curr_ptr->img_version_num > previous_ptr->img_version_num)
		return 1;
	else if (curr_ptr->img_version_num < previous_ptr->img_version_num)
		return 0;
	else {
		if (curr_ptr->img_timestamp.value > previous_ptr->img_timestamp.value)
			return 1;
		else if (curr_ptr->img_timestamp.value <= previous_ptr->img_timestamp.value)
			return 0;
	}
	return 0;
}

static void check_misc_version(void)
{
	cosimage_version_info cos_version, misc_version;
	unsigned char v_first_info[] = {0x5a, 0x5a, 0xa5, 0xa5, 0x00, 0x00, 0x00, 0x00,
						 0x1c, 0x38, 0x15, 0x0c, 0x09, 0x00, 0xe0 ,0x07};

	/* get current misc version from record area */
	access_hisee_image_partition((char *)&misc_version, MISC_VERSION_READ_TYPE);
	pr_err("%s(): magic=%x,version=%x\n", __func__, misc_version.magic, misc_version.img_version_num);

	if (HISEE_SW_VERSION_MAGIC_VALUE == misc_version.magic) {
		/* compare misc version */
		if (g_misc_version <= misc_version.img_version_num) {
			pr_err("%s(): magic is valid,misc version is old\n", __func__);
			g_hisee_data.hisee_img_head.misc_image_cnt = 0;
		}
	} else {
		/* get current cos version from record area */
		access_hisee_image_partition((char *)&cos_version, SW_VERSION_READ_TYPE);
		if (0 == memcmp((char *)&cos_version, (char *)v_first_info, sizeof(cosimage_version_info))) {
			if (HISEE_MISC_VERSION0 == g_misc_version) {
				pr_err("%s(): magic is invalid,misc version is old\n", __func__);
				g_hisee_data.hisee_img_head.misc_image_cnt = 0;
				/* write current misc version into record area */
				misc_version.magic = HISEE_SW_VERSION_MAGIC_VALUE;
				misc_version.img_version_num = g_misc_version;
				access_hisee_image_partition((char *)&misc_version, MISC_VERSION_WRITE_TYPE);
			}
		}
	}
}

static int check_new_cosimage(int *is_new_cosimage)
{
	hisee_img_header *p_img_header;
	cosimage_version_info curr = {0};
	cosimage_version_info previous = {0};
	int ret;

	if (NULL == is_new_cosimage) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	if (!g_hisee_data.img_header_is_parse) {
		ret = hisee_parse_img_header((char *)&(g_hisee_data.hisee_img_head));
		if (HISEE_OK != ret) {
			pr_err("%s():hisee_parse_img_header failed, ret=%d\n", __func__, ret);
			set_errno_and_return(ret);
		}
		check_misc_version();
		g_hisee_data.img_header_is_parse = 1;
	}
	p_img_header = &(g_hisee_data.hisee_img_head);
	parse_timestamp(p_img_header->time_stamp, &curr);
	curr.img_version_num = p_img_header->sw_version_cnt;
	curr.magic = HISEE_SW_VERSION_MAGIC_VALUE;

	ret = access_hisee_image_partition((char *)&previous, SW_VERSION_READ_TYPE);
	if (HISEE_OK != ret) {
		pr_err("%s access_hisee_image_partition fail,ret=%d\n", __func__, ret);
		return ret;
	}
	if (check_sw_version_null(&previous))
		*is_new_cosimage = 1;
	else
		*is_new_cosimage = exist_newest_cosimage(&curr, &previous);
	return HISEE_OK;
}

static void record_hisee_log_by_dmd(long dmd_errno, int hisee_errno)
{
	int ret;
	char buff[HISEE_CMD_NAME_LEN];
	int i;

	memset(buff, 0, (unsigned long)HISEE_CMD_NAME_LEN);
	for (i = 0; i < ARRAY_SIZE(g_errcode_items_des); i++) {/*lint !e846 !e514 !e866 !e30 !e84 !e574 !e737*/
		if (hisee_errno == g_errcode_items_des[i].err_code) {
			break;
		}
	}
	if ((unsigned long)i == ARRAY_SIZE(g_errcode_items_des)) {/*lint !e846 !e514 !e866 !e30 !e84 !e574 !e737 !e571*/
		pr_err("%s(): can't find errcode=%d definition\n", __func__, hisee_errno);
		return;
	}

	snprintf(buff, (unsigned long)8, "%d,", hisee_errno);
	strncat(buff, g_errcode_items_des[i].err_description, (unsigned long)((HISEE_ERROR_DESCRIPTION_MAX - 1) - strlen(buff)));/*lint !e662*/

#ifdef CONFIG_PN547_NFC_64
	ret = nfc_record_dmd_info(dmd_errno, (const char *)buff);
	if (0 != ret)
		pr_err("%s(): nfc_record_dmd_for_hisee return %d failed\n", __func__, ret);
#endif

	return;
}

/** read full path file interface
 * @fullname: input, the full path name should be read
 * @buffer: output, save the data
 * @offset: the offset in this file started to read
 * @size: the count bytes should be read.if zero means read total file
 * On success, the number of bytes read is returned (zero indicates end of file),
 * On error, the return value is less than zero, please check the errcode in hisee module.
 */
static int hisee_read_file(const char *fullname, char *buffer, size_t offset, size_t size)
{
	struct file *fp;
	int ret = HISEE_OK;
	ssize_t cnt;
	ssize_t read_bytes = 0;
	loff_t pos = 0;
	mm_segment_t old_fs;

	if (NULL == fullname || NULL == buffer) {
		pr_err("%s(): passed ptr is NULL\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (offset >= HISEE_SHARE_BUFF_SIZE || size > HISEE_SHARE_BUFF_SIZE) {
		pr_err("%s(): passed size is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp = filp_open(fullname, O_RDONLY, 0600);
	if (IS_ERR(fp)) {
		pr_err("%s():open %s failed\n", __func__, fullname);
		ret = HISEE_OPEN_FILE_ERROR;
		goto out;
	}
	ret = vfs_llseek(fp, 0, SEEK_END);
	if (ret < 0) {
		pr_err("%s():lseek %s failed from end.\n", __func__, fullname);
		ret = HISEE_LSEEK_FILE_ERROR;
		goto close;
	}
	pos = fp->f_pos;
	if ((offset + size) > (size_t)pos) {
		pr_err("%s(): offset(%lx), size(%lx) both invalid.\n", __func__, offset, size);
		ret = HISEE_OUTOF_RANGE_FILE_ERROR;
		goto close;
	}
	ret = vfs_llseek(fp, offset, SEEK_SET);
	if (ret < 0) {
		pr_err("%s():lseek %s failed from begin.\n", __func__, fullname);
		ret = HISEE_LSEEK_FILE_ERROR;
		goto close;
	}
	read_bytes = (ssize_t)(pos - fp->f_pos);
	pos = fp->f_pos;
	if (0 != size)
		read_bytes = size;
	cnt = vfs_read(fp, (char __user *)buffer, read_bytes, &pos);
	if (cnt < read_bytes) {
		pr_err("%s():read %s failed, return [%ld]\n", __func__, fullname, cnt);
		ret = HISEE_READ_FILE_ERROR;
		goto close;
	}
	read_bytes = cnt;
close:
	filp_close(fp, NULL);
out:
	set_fs(old_fs);
	if (ret >= HISEE_OK) {
		atomic_set(&g_hisee_errno, HISEE_OK);
		ret = read_bytes;
	} else {
		atomic_set(&g_hisee_errno, ret);
	}
	return ret;
}

static int check_img_header_is_valid(hisee_img_header *p_img_header)
{
	int i;
	int ret = HISEE_OK;
	unsigned int cnt = 0;

	for (i = 0; i <  p_img_header->file_cnt; i++) {
		if (!strncmp(p_img_header->file[i].name, HISEE_IMG_MISC_NAME, strlen(HISEE_IMG_MISC_NAME)))
			cnt++;
		if (p_img_header->file[i].size >= HISEE_SHARE_BUFF_SIZE) {
			pr_err("%s():size check %s failed\n", __func__, p_img_header->file[i].name);
			ret = HISEE_SUB_FILE_SIZE_CHECK_ERROR;
			return ret;
		}
		if (0 == i && (p_img_header->file[i].offset != (HISEE_IMG_HEADER_LEN + HISEE_IMG_SUB_FILES_LEN * p_img_header->file_cnt))) {
			pr_err("%s():offset check %s failed\n", __func__, p_img_header->file[i].name);
			ret = HISEE_SUB_FILE_OFFSET_CHECK_ERROR;
			return ret;
		}
		if (i > 0 && (p_img_header->file[i].offset < p_img_header->file[i - 1].offset)) {
			pr_err("%s():offset check %s failed\n", __func__, p_img_header->file[i].name);
			ret = HISEE_SUB_FILE_OFFSET_CHECK_ERROR;
			return ret;
		}

		/* get misc version */
		if (cnt == HISEE_MAX_MISC_IMAGE_NUMBER) {
			cnt--;
			g_misc_version = p_img_header->file[i].size;
			pr_err("%s():misc version =%d\n", __func__, g_misc_version);
		}
	}
	if (/*cnt < HISEE_MIN_MISC_IMAGE_NUMBER ||*/ cnt > HISEE_MAX_MISC_IMAGE_NUMBER) {
		pr_err("%s():misc cnt =%d is invalid\n", __func__, cnt);
		ret = HISEE_SUB_FILE_OFFSET_CHECK_ERROR;
		return ret;
	}
	p_img_header->misc_image_cnt = cnt;
	return ret;
}


/*static int hisee_erase_hisee_img_head(void)
{
	struct file *fp;
	char fullname[MAX_PATH_NAME_LEN + 1] = { 0 };
	char erase_head_data[HISEE_IMG_HEADER_LEN] = {0};
	int ret;
	loff_t pos;
	ssize_t cnt;
	mm_segment_t old_fs;

	ret = flash_find_ptn(HISEE_IMAGE_PARTITION_NAME, fullname);
	if (0 != ret) {
	    pr_err("%s():flash_find_ptn fail\n", __func__);
		ret = HISEE_OPEN_FILE_ERROR;
	    set_errno_and_return(ret);
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp = filp_open(fullname, O_WRONLY, 0600);
	if (IS_ERR(fp)) {
		pr_err("%s():open %s failed\n", __func__, fullname);
		ret = HISEE_OPEN_FILE_ERROR;
		set_fs(old_fs);
		set_errno_and_return(ret);
	}

	pos = fp->f_pos;
	cnt = vfs_write(fp, (char __user *)erase_head_data, (unsigned long)HISEE_IMG_HEADER_LEN, &pos);
	if (cnt < HISEE_IMG_HEADER_LEN) {
		pr_err("%s():write failed, return [%ld]\n", __func__, cnt);
		ret = HISEE_WRITE_FILE_ERROR;
	}

	filp_close(fp, NULL);
	set_fs(old_fs);
	check_and_print_result();
	set_errno_and_return(ret);
}*/

/** parse the hisee_img partition header interface
 * @buffer: output, save the data
 * On success, zero is return,
 * On error, the return value is less than zero, please check the errcode in hisee module.
 */
static int hisee_parse_img_header(char *buffer)
{
	struct file *fp;
	hisee_img_header *p_img_header;
	unsigned int sw_version_num;
	char fullname[MAX_PATH_NAME_LEN + 1] = { 0 };
	char cos_img_rawdata[HISEE_IMG_SUB_FILES_LEN] = {0};
	int ret;
	loff_t pos;
	ssize_t cnt;
	mm_segment_t old_fs;

	ret = flash_find_ptn(HISEE_IMAGE_PARTITION_NAME, fullname);
	if (0 != ret) {
	    pr_err("%s():flash_find_ptn fail\n", __func__);
		ret = HISEE_OPEN_FILE_ERROR;
	    set_errno_and_return(ret);
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fp = filp_open(fullname, O_RDONLY, 0600);
	if (IS_ERR(fp)) {
		pr_err("%s():open %s failed\n", __func__, fullname);
		ret = HISEE_OPEN_FILE_ERROR;
		set_fs(old_fs);
		set_errno_and_return(ret);
	}

	pos = fp->f_pos;
	cnt = vfs_read(fp, (char __user *)buffer, HISEE_IMG_HEADER_LEN, &pos);
	if (cnt < HISEE_IMG_HEADER_LEN) {
		pr_err("%s():read %s failed, return [%ld]\n", __func__, fullname, cnt);
		ret = HISEE_READ_FILE_ERROR;
		goto error;
	}
	fp->f_pos = pos;
	p_img_header = (hisee_img_header *)buffer;
	if (strncmp(p_img_header->magic, HISEE_IMG_MAGIC_VALUE, HISEE_IMG_MAGIC_LEN)) {
		pr_err("%s() hisee_img magic value is wrong.\n", __func__);
		ret = HISEE_IMG_PARTITION_MAGIC_ERROR;
		goto error;
	}
	if (p_img_header->file_cnt > HISEE_IMG_SUB_FILE_MAX) {
		pr_err("%s() hisee_img file numbers is invalid.\n", __func__);
		ret = HISEE_IMG_PARTITION_FILES_ERROR;
		goto error;
	}
	cnt = vfs_read(fp, (char __user *)(buffer + HISEE_IMG_HEADER_LEN), (HISEE_IMG_SUB_FILES_LEN * p_img_header->file_cnt), &pos);
	if (cnt < (HISEE_IMG_SUB_FILES_LEN * p_img_header->file_cnt)) {
		pr_err("%s():read %s failed, return [%ld]\n", __func__, fullname, cnt);
		ret = HISEE_READ_FILE_ERROR;
		goto error;
	}

	ret = check_img_header_is_valid(p_img_header);
	if (HISEE_OK != ret) {
		pr_err("%s(): check_img_header_is_valid fail,ret=%d.\n", __func__, ret);
		goto error;
	}

	/*there is a assumption: the first file in hisee.img is always the cos image*/
	fp->f_pos = pos;
	cnt = vfs_read(fp, (char __user *)cos_img_rawdata, (unsigned long)HISEE_IMG_SUB_FILES_LEN, &pos);
	if (cnt < HISEE_IMG_SUB_FILES_LEN) {
		pr_err("%s():read %s failed, return [%ld]\n", __func__, fullname, cnt);
		ret = HISEE_READ_FILE_ERROR;
		goto error;
	}

	sw_version_num = *((unsigned int *)(&cos_img_rawdata[12]));
	p_img_header->sw_version_cnt = sw_version_num;

error:
	filp_close(fp, NULL);
	set_fs(old_fs);
	set_errno_and_return(ret);
}

/* read hisee_fs partition file interface
* @type: input, the file type need to read in hisee_img partiton
* @buffer: output, save the data
* On success, the number of bytes read is returned (zero indicates end of file),
* On error, the return value is less than zero, please check the errcode in hisee module.
*/
static int filesys_hisee_read_image(hisee_img_file_type type, char *buffer)
{
	int ret = HISEE_OK;
	char sub_file_name[HISEE_IMG_SUB_FILE_NAME_LEN] = {0};
	char fullname[MAX_PATH_NAME_LEN + 1] = { 0 };
	int i;

	if (NULL == buffer) {
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	switch (type) {
	case SLOADER_IMG_TYPE:
		strncat(sub_file_name, HISEE_IMG_SLOADER_NAME, HISEE_IMG_SUB_FILE_NAME_LEN);
		break;
	case COS_IMG_TYPE:
		strncat(sub_file_name, HISEE_IMG_COS_NAME, HISEE_IMG_SUB_FILE_NAME_LEN);
		break;
	case OTP_IMG_TYPE:
	case OTP1_IMG_TYPE:
		strncat(sub_file_name, HISEE_IMG_OTP0_NAME, HISEE_IMG_SUB_FILE_NAME_LEN);
		break;
	case MISC0_IMG_TYPE:
	case MISC1_IMG_TYPE:
	case MISC2_IMG_TYPE:
	case MISC3_IMG_TYPE:
	case MISC4_IMG_TYPE:
		strncat(sub_file_name, HISEE_IMG_MISC_NAME, HISEE_IMG_SUB_FILE_NAME_LEN);
		sub_file_name[4] = (char)'0' + (char)(type - MISC0_IMG_TYPE);
		break;
	default:
		ret = HISEE_IMG_SUB_FILE_NAME_ERROR;
		set_errno_and_return(ret);
	}

	mutex_lock(&g_hisee_data.hisee_mutex);
	if (!g_hisee_data.img_header_is_parse) {
		ret = hisee_parse_img_header((char *)&(g_hisee_data.hisee_img_head));
		if (HISEE_OK != ret) {
			pr_err("%s():hisee_read_img_header failed, ret=%d\n", __func__, ret);
			mutex_unlock(&g_hisee_data.hisee_mutex);
			set_errno_and_return(ret);
		}
		g_hisee_data.img_header_is_parse = 1;
	}

	mutex_unlock(&g_hisee_data.hisee_mutex);
	for (i = 0; i < HISEE_IMG_SUB_FILE_MAX; i++) {
		if (!g_hisee_data.hisee_img_head.file[i].name[0])
			continue;
		if (OTP_IMG_TYPE == type) {
			if (!strncmp(sub_file_name, g_hisee_data.hisee_img_head.file[i].name, (unsigned long)HISEE_IMG_SUB_FILE_NAME_LEN) ||
				!strncmp(HISEE_IMG_OTP_NAME, g_hisee_data.hisee_img_head.file[i].name, (unsigned long)HISEE_IMG_SUB_FILE_NAME_LEN))
				break;
		} else if (OTP1_IMG_TYPE == type) {
			if (!strncmp(HISEE_IMG_OTP1_NAME, g_hisee_data.hisee_img_head.file[i].name, (unsigned long)HISEE_IMG_SUB_FILE_NAME_LEN))
				break;
		}
		else {
			if (!strncmp(sub_file_name, g_hisee_data.hisee_img_head.file[i].name, (unsigned long)HISEE_IMG_SUB_FILE_NAME_LEN))
				break;
		}
	}
	if (i == HISEE_IMG_SUB_FILE_MAX) {
		pr_err("%s():hisee_read_img_header failed, ret=%d\n", __func__, ret);
		ret = HISEE_IMG_SUB_FILE_ABSENT_ERROR;
		set_errno_and_return(ret);
	}

	ret = flash_find_ptn(HISEE_IMAGE_PARTITION_NAME, fullname);
	if (0 != ret) {
		pr_err("%s():flash_find_ptn fail\n", __func__);
		ret = HISEE_OPEN_FILE_ERROR;
		atomic_set(&g_hisee_errno, ret);
		return ret;
	}

	ret = hisee_read_file((const char *)fullname, buffer,
							g_hisee_data.hisee_img_head.file[i].offset,
							g_hisee_data.hisee_img_head.file[i].size);
	if (ret < HISEE_OK) {
		pr_err("%s():hisee_read_file failed, ret=%d\n", __func__, ret);
		atomic_set(&g_hisee_errno, ret);
		return ret;
	}
	ret = g_hisee_data.hisee_img_head.file[i].size;
	atomic_set(&g_hisee_errno, HISEE_OK);
	return ret;
}

/*
 * hisi_hisee_active - handle hisee request from ATF
 * if wait_sem_timeout is not zero, means there has been a timeout
 * before this IPI happens, then only decrease it;
 * another case:if smc_cmd_running is zero, there nothing need to do;
 * otherwise, do up() a semaphore
 */
void hisi_hisee_active(void)
{
/*
	pr_err("%s() sem_timeout=%d smc_cmd_running=%d, count=%d\n", __func__,
		atomic_read(&g_hisee_data.wait_sem_timeout), g_hisee_data.smc_cmd_running, g_hisee_data.atf_sem.count);

	if (atomic_sub_return(1, &(g_hisee_data.wait_sem_timeout)) >= 0) {
		return;
	} else {
		atomic_set(&(g_hisee_data.wait_sem_timeout), 0);
	}
*/
	if (g_hisee_data.smc_cmd_running) {
		up(&(g_hisee_data.atf_sem));
	}
	return;
}
EXPORT_SYMBOL(hisi_hisee_active);

static void set_message_header(atf_message_header *header, unsigned int cmd_type)
{
	header->ack = 0;
	header->cmd = cmd_type;
	header->test_result_phy = 0;
	header->test_result_size = 0;
	return;
}

static int send_smc_process(atf_message_header *p_message_header, phys_addr_t phy_addr, unsigned int size,
							unsigned int timeout, se_smc_cmd smc_cmd)
{
	int ret = HISEE_OK;
	long local_jiffies;

	mutex_lock(&g_hisee_data.hisee_mutex);
	g_hisee_data.smc_cmd_running = 1;

	if (CMD_HISEE_CHANNEL_TEST != smc_cmd)
		ret = atfd_hisee_smc((u64)HISEE_FN_MAIN_SERVICE_CMD, (u64)smc_cmd, (u64)phy_addr, (u64)size);
	else
		ret = atfd_hisee_smc((u64)HISEE_FN_CHANNEL_TEST_CMD, (u64)smc_cmd, (u64)phy_addr, (u64)size);
	if (ret != HISEE_OK) {
		pr_err("%s(): atfd_hisee_smc failed, ret=%d\n", __func__, ret);
		g_hisee_data.smc_cmd_running = 0;
		mutex_unlock(&g_hisee_data.hisee_mutex);
		set_errno_and_return(HISEE_FIRST_SMC_CMD_ERROR);
	}

	/*notice! while starting a new smc message, no need to set wait_sem_timeout to zero.
	 *because this flag only set in timeout scenario, so only clear in IPI context.
	 *If the wait_sem_timeout is set in the second smc message, there may be a uncorrection:
	 *the fisrt IPI interrupt should make the semaphore availble, then the second acquire semaphore
	 *success directly.
	*/
	if (CMD_HISEE_CHANNEL_TEST != smc_cmd)
		local_jiffies = msecs_to_jiffies(timeout);
	else
		local_jiffies = MAX_SCHEDULE_TIMEOUT;
	ret = down_timeout(&(g_hisee_data.atf_sem), local_jiffies);
	if (-ETIME == ret) {
		ret = HISEE_SMC_CMD_TIMEOUT_ERROR;
	} else {
		if (!(p_message_header->cmd == smc_cmd &&
			p_message_header->ack == HISEE_ATF_ACK_SUCCESS))
			ret = HISEE_SMC_CMD_PROCESS_ERROR;
		else
			ret = HISEE_OK;
		/*ret = get_hisee_lcs_mode(&hisee_lcs_mode);
		if (HISEE_OK == ret) {
			if (CMD_FACTORY_APDU_TEST == smc_cmd &&
				HISEE_SM_MODE_MAGIC == hisee_lcs_mode) {
				if (!(p_message_header->cmd == smc_cmd &&
					p_message_header->ack == HISEE_ATF_ACK_FAILURE)) {
					ret = HISEE_SMC_CMD_PROCESS_ERROR;
				}
			} else {
				if (!(p_message_header->cmd == smc_cmd &&
					p_message_header->ack == HISEE_ATF_ACK_SUCCESS)) {
					ret = HISEE_SMC_CMD_PROCESS_ERROR;
				}
			}
		} else
			ret = HISEE_SMC_CMD_PROCESS_ERROR;*/
	}

	pr_err("%s() ret=%d\n", __func__, ret);
	g_hisee_data.smc_cmd_running = 0;
	mutex_unlock(&g_hisee_data.hisee_mutex);
	return ret;
}

static int load_cosimg_appdata_ddr(void)
{
	char *buff_virt;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size = 0;

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, SIZE_1K * 4,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(buff_virt, 0, SIZE_1K * 4);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_PRESAVE_COS_APPDATA);
	image_size = HISEE_ATF_MESSAGE_HEADER_LEN;
	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_COS_APPDATA_TIMEOUT, CMD_PRESAVE_COS_APPDATA);
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)(SIZE_1K * 4), buff_virt, buff_phy);
	check_and_print_result();
	set_errno_and_return(ret);
}

static int write_hisee_otp_value(hisee_img_file_type otp_img_index)
{
	char *buff_virt;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size;

	if (otp_img_index < OTP_IMG_TYPE || otp_img_index > OTP1_IMG_TYPE) {
		pr_err("%s(): otp_img_index=%d invalid\n", __func__, (int)otp_img_index);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, HISEE_SHARE_BUFF_SIZE,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}

	pr_err("%s(): entering, otp_img_index=%d\n", __func__, (int)otp_img_index);
	memset(buff_virt, 0, HISEE_SHARE_BUFF_SIZE);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_UPGRADE_OTP);
	ret = filesys_hisee_read_image(otp_img_index, (buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN));
	if (ret < HISEE_OK) {
		pr_err("%s(): filesys_hisee_read_image failed, ret=%d\n", __func__, ret);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
		set_errno_and_return(ret);
	}
	image_size = (ret + HISEE_ATF_MESSAGE_HEADER_LEN);
	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_OTP_TIMEOUT, CMD_UPGRADE_OTP);
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
	return ret;
}

static int otp_image_upgrade_func(void *buf, int para)
{
	int ret;
	ret = write_hisee_otp_value(OTP_IMG_TYPE);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

static int misc_image_upgrade_func(void *buf, int para)
{
	char *buff_virt;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size;
	hisee_img_file_type type = MISC0_IMG_TYPE;
	unsigned int misc_image_cnt = 1;

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, HISEE_SHARE_BUFF_SIZE,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}

do_loop:
	memset(buff_virt, 0, HISEE_SHARE_BUFF_SIZE);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_UPGRADE_MISC);
	ret = filesys_hisee_read_image(type, (buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN));
	if (ret < HISEE_OK) {
		pr_err("%s(): filesys_hisee_read_image failed, ret=%d\n", __func__, ret);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
		set_errno_and_return(ret);
	}

	image_size = (ret + HISEE_ATF_MESSAGE_HEADER_LEN);
	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_MISC_TIMEOUT, CMD_UPGRADE_MISC);
	if (HISEE_OK != ret) {
		pr_err("%s(): send_smc_process failed, ret=%d\n", __func__, ret);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
		set_errno_and_return(ret);
	}
	if (type == MISC0_IMG_TYPE)
		misc_image_cnt = g_hisee_data.hisee_img_head.misc_image_cnt;
	if ((--misc_image_cnt) > 0) {
		type++;
		goto do_loop;
	}

	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

static void wait_hisee_ready(hisee_state ready_state, unsigned int timeout_ms)
{
	hisee_state state = HISEE_STATE_MAX;
	unsigned int cnt = timeout_ms / 50;

	do {
		state = (hisee_state)atfd_hisee_smc((u64)HISEE_FN_MAIN_SERVICE_CMD, (u64)CMD_GET_STATE, (u64)0, (u64)0);
		if (ready_state == state)
			break;
		hisee_mdelay(50);
	} while (cnt--);
	if (cnt == 0)
		pr_err("%s() timeout!\n", __func__);
	return;
}

static int send_apdu_cmd(int type)
{
	int ret;
	/*set key cmd */
	unsigned char cmd0[21] = {	0xF0, 0x10, 0x00, 0x00, \
								0x10, 0x01, 0x23, 0x45, \
								0x67, 0x89, 0xab, 0xcd, \
								0xef, 0xfe, 0xdc, 0xba, \
								0x98, 0x76, 0x54, 0x32, \
								0x10};
	unsigned char cmd1[5] = {0xF0,0xd8, 0x00,0x00,0x00};
	/* delete test applet cmd */
	unsigned char cmd2[5] = {0x00, 0xa4, 0x04, 0x00, 0x00};
	unsigned char cmd3[12] = {0x80, 0xe4, 0x00, 0x80,0x07, \
							0x4f, 0x05, 0x12, 0x34, 0x56, \
							0x78, 0x90};
	unsigned char *sel_cmd[2];
	int sel_cmd_len[2];

	if (HISEE_SET_KEY == type) {
		sel_cmd[0] = cmd0;
		sel_cmd[1] = cmd1;
		sel_cmd_len[0] = 21;
		sel_cmd_len[1] = 5;
	}
	else if (HISEE_DEL_TEST_APPLET == type) {
		sel_cmd[0] = cmd2;
		sel_cmd[1] = cmd3;
		sel_cmd_len[0] = 5;
		sel_cmd_len[1] = 12;
	}
	else {
		return HISEE_INVALID_PARAMS;
	}

	/* send apdu key command */
	ret = write_apdu_command_func((char *)sel_cmd[0], sel_cmd_len[0]);
	if (HISEE_OK != ret) {
		pr_err("%s()  apdu0 failed,ret=%d\n", __func__, ret);
		return ret;
	}
	hisee_mdelay(DELAY_BETWEEN_STEPS);
	ret = write_apdu_command_func((char *)sel_cmd[1], sel_cmd_len[1]);
	if (HISEE_OK != ret) {
		pr_err("%s()  apdu1 failed,ret=%d\n", __func__, ret);
		return ret;
	}
	hisee_mdelay(DELAY_BETWEEN_STEPS);

	return ret;
}


static int hisee_misc_process(void)
{
	cosimage_version_info misc_version;
	int ret = HISEE_OK;

	if (0 == g_hisee_data.hisee_img_head.misc_image_cnt) {
		return ret;
	}
	/* check misc version */

	ret = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret) {
		pr_err("%s()  hisee poweroff failed,ret=%d\n", __func__, ret);
		return ret;
	}
	hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
	ret = hisee_poweron_booting_func(NULL, HISEE_POWER_ON_BOOTING_MISC);
	if (HISEE_OK != ret) {
		pr_err("%s()  hisee poweron booting failed,ret=%d\n", __func__, ret);
		return ret;
	}

	wait_hisee_ready(HISEE_STATE_MISC_READY, 30000);

	ret = misc_image_upgrade_func(NULL, 0);
	if (HISEE_OK != ret) {
		pr_err("%s() misc_image_upgrade_func failed,ret=%d\n", __func__, ret);
		return ret;
	}

	wait_hisee_ready(HISEE_STATE_COS_READY, 3000);

	/* write current misc version into record area */
	if (g_misc_version) {
		misc_version.magic = HISEE_SW_VERSION_MAGIC_VALUE;
		misc_version.img_version_num = g_misc_version;
		access_hisee_image_partition((char *)&misc_version, MISC_VERSION_WRITE_TYPE);
	}

	return ret;
}

static int cos_image_upgrade_func(void *buf, int para)
{
	char *buff_virt;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	cosimage_version_info curr = {0};
	int ret;
	int ret_tmp;
	int image_size;
	int new_cos_exist = 0;
	unsigned int upgrade_run_flg;
	int retry = 2; /* retry 2 more times if failed */
	/*unsigned int hisee_lcs_mode = 0;*/

	/* hisee factory test(include slt test) don't check there is new cos image */
	if ((int)HISEE_FACTORY_TEST_VERSION != para) {
		ret = check_new_cosimage(&new_cos_exist);
		if (HISEE_OK == ret) {
			if (!new_cos_exist) {
				pr_err("%s(): there is no new cosimage\n", __func__);
				goto upgrade_bypass;
			}
		} else {
			pr_err("%s(): check_new_cosimage failed,ret=%d\n", __func__, ret);
			ret = HISEE_OLD_COS_IMAGE_ERROR;
			goto upgrade_bypass;
		}
	}

	upgrade_run_flg = HISEE_COS_UPGRADE_RUNNING_FLG;
	access_hisee_image_partition((char *)&upgrade_run_flg, COS_UPGRADE_RUN_WRITE_TYPE);

upgrade_retry:
	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, HISEE_SHARE_BUFF_SIZE,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		ret = HISEE_NO_RESOURCES;
		goto upgrade_exit;
	}

	memset(buff_virt, 0, HISEE_SHARE_BUFF_SIZE);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_UPGRADE_COS);
	ret = filesys_hisee_read_image(COS_IMG_TYPE, (buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN));
	if (ret < HISEE_OK) {
		pr_err("%s(): filesys_hisee_read_image failed, ret=%d\n", __func__, ret);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
		goto upgrade_exit;
	}
	image_size = (ret + HISEE_ATF_MESSAGE_HEADER_LEN);
	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_COS_TIMEOUT, CMD_UPGRADE_COS);

	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
	if (HISEE_OK == ret) {
		parse_timestamp(g_hisee_data.hisee_img_head.time_stamp, &curr);
		if (!check_timestamp_valid(&curr)) {
			ret = HISEE_INVALID_PARAMS;
			pr_err("%s(): check_timestamp_valid failed\n", __func__);
			goto upgrade_exit;
		}

		/* add misc upgrade for normal case */
		if ((int)HISEE_FACTORY_TEST_VERSION != para) {
			check_misc_version();
			ret = hisee_misc_process();
		}
	} else {
		g_hisee_data.hisee_img_head.sw_version_cnt = 0;
		/*get_hisee_lcs_mode(&hisee_lcs_mode);
		if ((int)HISEE_FACTORY_TEST_VERSION != para && (unsigned int)HISEE_SM_MODE_MAGIC == hisee_lcs_mode) { 
			hisee_erase_hisee_img_head();
		}*/
	}

upgrade_exit:
	if (HISEE_OK == ret) {
		curr.img_version_num = g_hisee_data.hisee_img_head.sw_version_cnt;
		curr.magic = HISEE_SW_VERSION_MAGIC_VALUE;
		access_hisee_image_partition((char *)&curr, SW_VERSION_WRITE_TYPE);
		upgrade_run_flg = 0;
		access_hisee_image_partition((char *)&upgrade_run_flg, COS_UPGRADE_RUN_WRITE_TYPE);
	} else {
		while (retry > 0) {
			int ret1, ret2;
			pr_err("%s() failed and retry. retcode=%d\n", __func__, ret);
			retry--;
			ret1 = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
			hisee_mdelay(200);
			ret2 = hisee_poweron_upgrade_func(NULL, 0);
			hisee_mdelay(200);
			if (HISEE_OK != ret1 || HISEE_OK != ret2)
				continue;
			goto upgrade_retry;
		}
	}
upgrade_bypass:
	/* clear parse flag */
	g_hisee_data.img_header_is_parse = 0;
	ret_tmp = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret_tmp) {
		pr_err("%s() poweroff failed. retcode=%d\n", __func__, ret_tmp);
		if (HISEE_OK == ret) ret = ret_tmp;
	}
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

static int write_rpmb_key_func (void *buf, int para)
{
	char *buff_virt = NULL;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size = 0;

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, SIZE_1K * 4,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(buff_virt, 0, SIZE_1K * 4);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_WRITE_RPMB_KEY);
	image_size = HISEE_ATF_MESSAGE_HEADER_LEN;
	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_WRITE_RPMBKEY_TIMEOUT, CMD_WRITE_RPMB_KEY);
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)(SIZE_1K * 4), buff_virt, buff_phy);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

static int set_sm_lcs_func(void *buf, int para)
{
	char *buff_virt = NULL;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size;

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, SIZE_1K * 4,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(buff_virt, 0, SIZE_1K * 4);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_SET_LCS_SM);
	image_size = HISEE_ATF_MESSAGE_HEADER_LEN;
	ret = send_smc_process(p_message_header, buff_phy, (unsigned int)image_size,
							HISEE_ATF_GENERAL_TIMEOUT, CMD_SET_LCS_SM);
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)(SIZE_1K * 4), buff_virt, buff_phy);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

static int upgrade_one_file_func(char *filename, se_smc_cmd cmd)
{
	char *buff_virt;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size = 0;

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, HISEE_SHARE_BUFF_SIZE,
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(buff_virt, 0, HISEE_SHARE_BUFF_SIZE);
	p_message_header = (atf_message_header *)buff_virt; /*lint !e826*/
	set_message_header(p_message_header, cmd);

	ret = hisee_read_file((const char *)filename, (buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN), 0, 0);
	if (ret < HISEE_OK) {
		pr_err("%s(): hisee_read_file failed, filename=%s, ret=%d\n", __func__, filename, ret);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
		set_errno_and_return(ret);
	}
	image_size = (ret + HISEE_ATF_MESSAGE_HEADER_LEN);
	ret = send_smc_process(p_message_header, buff_phy, (unsigned int)image_size,
							HISEE_ATF_GENERAL_TIMEOUT, cmd);
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
	check_and_print_result();
	set_errno_and_return(ret);
}


static int factory_apdu_test_func(void *buf, int para)
{
	int ret = HISEE_OK;
	ret = upgrade_one_file_func("/hisee_fs/test.apdu.bin", CMD_FACTORY_APDU_TEST);
	check_and_print_result();
	set_errno_and_return(ret);
}

#ifdef CONFIG_HISI_DEBUG_FS

static int hisee_test(char *path, phys_addr_t result_phy, size_t result_size)
{
	char *buff_virt = NULL;
	phys_addr_t buff_phy = 0;
	char fullname[MAX_PATH_NAME_LEN + 1] = { 0 };
	int fd;
	int i = 0;
	mm_segment_t fs;
	atf_message_header *p_message_header;
	int ret;
	int image_size;

	do {
		if (0xa == path[i] || 0x20 == path[i]) {
			break;
		}
		fullname[i] = path[i];
		i++;
	} while (i < MAX_PATH_NAME_LEN);
	if (i <= 0) {
		pr_err("%s() filename is invalid\n", __func__);
		set_errno_and_return(HISEE_CHANNEL_TEST_PATH_ABSENT_ERROR);
	}

	fs = get_fs();
	set_fs(KERNEL_DS);
	fd = (int)sys_open(fullname, O_RDONLY, HISEE_FILESYS_DEFAULT_MODE);
	if (fd < 0) {
		pr_err("%s(): open %s failed, fd=%d\n", __func__, fullname, fd);
		set_fs(fs);
		set_errno_and_return(HISEE_CHANNEL_TEST_PATH_ABSENT_ERROR);
	}
	image_size = sys_lseek(fd, 0, SEEK_END);
	if (image_size < 0) {
		pr_err("%s(): sys_lseek failed from set.\n", __func__);
		sys_close(fd);
		set_fs(fs);
		set_errno_and_return(HISEE_LSEEK_FILE_ERROR);
	}
	image_size += HISEE_ATF_MESSAGE_HEADER_LEN;
	pr_err("%s() file size is 0x%x\n", __func__, image_size);
	sys_close(fd);

	sys_unlink(TEST_SUCCESS_FILE);
	sys_unlink(TEST_FAIL_FILE);
	sys_unlink(TEST_RESULT_FILE);
	set_fs(fs);

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, ALIGN_UP_4KB(image_size),
											&buff_phy, GFP_KERNEL);
	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(buff_virt, 0, ALIGN_UP_4KB(image_size));
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_HISEE_CHANNEL_TEST);
	p_message_header->test_result_phy = result_phy;
	p_message_header->test_result_size = result_size;

	ret = hisee_read_file(fullname, buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN, 0, image_size - HISEE_ATF_MESSAGE_HEADER_LEN);
	if (ret < HISEE_OK) {
		pr_err("%s(): hisee_read_file failed, ret=%d\n", __func__, ret);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)ALIGN_UP_4KB(image_size), buff_virt, buff_phy);
		set_errno_and_return(ret);
	}

	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_GENERAL_TIMEOUT, CMD_HISEE_CHANNEL_TEST);

	fs = get_fs();
	set_fs(KERNEL_DS);
	fd = (int)sys_mkdir(TEST_DIRECTORY_PATH, HISEE_FILESYS_DEFAULT_MODE);
	if (fd < 0 && (-EEXIST != fd)) {/*EEXIST(File exists), don't return error*/
		set_fs(fs);
		dma_free_coherent(g_hisee_data.cma_device, (unsigned long)ALIGN_UP_4KB(image_size), buff_virt, buff_phy);
		pr_err("create dir %s fail, ret: %d.\n", TEST_DIRECTORY_PATH, fd);
		return fd;
	}
	if (HISEE_OK == ret) {
		/* create file for test flag */
		pr_err("%s(): rcv result size is 0x%x\r\n", __func__, p_message_header->test_result_size);
		if ((g_hisee_data.channel_test_item_result.phy == p_message_header->test_result_phy) &&
			(g_hisee_data.channel_test_item_result.size >= (long)p_message_header->test_result_size)) {
			fd = (int)sys_open(TEST_RESULT_FILE, O_RDWR|O_CREAT, 0);
			if (fd < 0) {
				pr_err("sys_open %s fail, fd: %d.\n", TEST_RESULT_FILE, fd);
				ret = fd;
				goto error;
			}
			sys_write(fd, g_hisee_data.channel_test_item_result.buffer, p_message_header->test_result_size);
			sys_close(fd);
			fd = (int)sys_open(TEST_SUCCESS_FILE, O_RDWR|O_CREAT, 0);
			if (fd < 0) {
				pr_err("sys_open %s fail, fd: %d.\n", TEST_SUCCESS_FILE, fd);
				ret = fd;
				goto error;
			}
			sys_close(fd);
			ret = HISEE_OK;
		} else {
			fd = (int)sys_open(TEST_FAIL_FILE, O_RDWR|O_CREAT, 0);
			if (fd < 0) {
				pr_err("sys_open %s fail, fd: %d.\n", TEST_FAIL_FILE, fd);
				ret = fd;
				goto error;
			}
			sys_close(fd);
			ret = HISEE_CHANNEL_TEST_WRITE_RESULT_ERROR;
		}
	} else {
		fd = (int)sys_open(TEST_FAIL_FILE, O_RDWR|O_CREAT, 0);
		if (fd < 0) {
			pr_err("sys_open %s fail, fd: %d.\n", TEST_FAIL_FILE, fd);
			ret = fd;
			goto error;
		}
		sys_close(fd);
		ret = HISEE_CHANNEL_TEST_WRITE_RESULT_ERROR;
	}

error:
	set_fs(fs);
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)ALIGN_UP_4KB(image_size), buff_virt, buff_phy);
	set_errno_and_return(ret);
}
#endif

static int hisee_channel_test_func(void *buf, int para)
{
#ifdef CONFIG_HISI_DEBUG_FS
	char *buff = buf;
	int ret = HISEE_OK;
	int i, j, k, value;
	int offset = 0;

	if (NULL == buf) {
		pr_err("%s(): input buf is NULL.\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	bypass_space_char();

	/* check buffer size */
	if (0 == strncmp(buff + offset, "result_size:0x", sizeof("result_size:0x") - 1)) {
		offset += sizeof("result_size:0x") - 1;
		/* find last size char */
		i = 0;
		while (0x20 != buff[offset + i]) {
			i++;
		}

		if (0 == i) {
			pr_err("result size is bad, use default size.\n");
			k = 0;
			g_hisee_data.channel_test_item_result.size = CHANNEL_TEST_RESULT_SIZE_DEFAULT;
		} else {
			g_hisee_data.channel_test_item_result.size = 0;
			k = i;
			i--;
			j = 0;
			while (i >= 0) {
				if ((buff[offset + i] >= '0') && (buff[offset + i] <= '9')) {
					value = buff[offset + i] - 0x30;
				} else if ((buff[offset + i] >= 'a') && (buff[offset + i] <= 'f')) {
					value = buff[offset + i] - 'a' + 0x10;
				} else if ((buff[offset + i] >= 'A') && (buff[offset + i] <= 'F')) {
					value = buff[offset + i] - 'A' + 0x10;
				} else {
					pr_err("result size is bad, use default size.\n");
					g_hisee_data.channel_test_item_result.size = TEST_RESULT_SIZE_DEFAULT;
					break;
				}
				g_hisee_data.channel_test_item_result.size += (value << (unsigned int)j);
				i--;
				j += 4;
			}
		}
		offset += k;
	} else {
		g_hisee_data.channel_test_item_result.size = TEST_RESULT_SIZE_DEFAULT;
	}

	pr_err("result size is 0x%x.\n", g_hisee_data.channel_test_item_result.size);
	if (0 == g_hisee_data.channel_test_item_result.size) {
		pr_err("result size is bad.\r\n");
		set_errno_and_return(HISEE_CHANNEL_TEST_CMD_ERROR);
	}

	bypass_space_char();

	if (0 == buff[offset]) {
		pr_err("test file path is bad.\n");
		set_errno_and_return(HISEE_CHANNEL_TEST_CMD_ERROR);
	}

	if (NULL != g_hisee_data.channel_test_item_result.buffer) {
		dma_free_coherent(g_hisee_data.cma_device,
					(unsigned long)ALIGN_UP_4KB(g_hisee_data.channel_test_item_result.size),
					g_hisee_data.channel_test_item_result.buffer,
					g_hisee_data.channel_test_item_result.phy);
	}

	g_hisee_data.channel_test_item_result.buffer = (char *)dma_alloc_coherent(g_hisee_data.cma_device,
													ALIGN_UP_4KB(g_hisee_data.channel_test_item_result.size),
													(dma_addr_t *)&g_hisee_data.channel_test_item_result.phy,
													GFP_KERNEL);
	if (NULL == g_hisee_data.channel_test_item_result.buffer) {
		pr_err("%s(): alloc 0x%x fail.\r\n", __func__, ALIGN_UP_4KB(g_hisee_data.channel_test_item_result.size));
		set_errno_and_return(HISEE_CHANNEL_TEST_RESULT_MALLOC_ERROR);
	}


    ret = hisee_test(buff + offset, g_hisee_data.channel_test_item_result.phy, g_hisee_data.channel_test_item_result.size);
	if (HISEE_OK != ret) {
		pr_err("%s(): hisee_test fail, ret = %d\n", __func__, ret);
	}
	dma_free_coherent(g_hisee_data.cma_device,
				(unsigned long)ALIGN_UP_4KB(g_hisee_data.channel_test_item_result.size),
				g_hisee_data.channel_test_item_result.buffer,
				g_hisee_data.channel_test_item_result.phy);
	g_hisee_data.channel_test_item_result.buffer = NULL;
	g_hisee_data.channel_test_item_result.phy = 0;
	g_hisee_data.channel_test_item_result.size = 0;
	check_and_print_result();
	set_errno_and_return(ret);
#else
	int ret = HISEE_OK;
	check_and_print_result();
	set_errno_and_return(ret);
#endif
}/*lint !e715*/

#ifdef __SLT_FEATURE__
static int application_upgrade_func(void *buf, int para)
{
	char *buff_virt = NULL;
	phys_addr_t buff_phy = 0;
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size = 0;

	buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, HISEE_SHARE_BUFF_SIZE,
										&buff_phy, GFP_KERNEL);

	if (buff_virt == NULL) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(buff_virt, 0, HISEE_SHARE_BUFF_SIZE);
	p_message_header = (atf_message_header *)buff_virt;
	set_message_header(p_message_header, CMD_UPGRADE_APPLET);
	ret = hisee_read_file((const char *)"/hisee_fs/applet.apdu.bin", (buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN), 0, 0);
	if (ret < HISEE_OK) {
		pr_err("%s(): filesys_hisee_read_image failed, ret=%d\n", __func__, ret);
		goto oper_over1;
	}
	image_size = (ret + HISEE_ATF_MESSAGE_HEADER_LEN);
	ret = send_smc_process(p_message_header, buff_phy, image_size,
							HISEE_ATF_APPLICATION_TIMEOUT, CMD_UPGRADE_APPLET);
	if (HISEE_OK != ret) {
		pr_err("%s(): send_smc_process failed, ret=%d\n", __func__, ret);
		goto oper_over1;
	}
oper_over1:
	dma_free_coherent(g_hisee_data.cma_device, (unsigned long)HISEE_SHARE_BUFF_SIZE, buff_virt, buff_phy);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/
#endif

static int hisee_powerctrl_func(hisee_power_operation op_type)
{
	int retry;
	int ret = HISEE_OK;
	rproc_id_t rproc_id = HISI_RPROC_LPM3_MBX27;
	rproc_msg_t tx_buffer[2] = {0};
	rproc_msg_t ack_buffer[2] = {0};

	if ((op_type != HISEE_POWER_OFF) && (op_type != HISEE_POWER_ON_BOOTING) &&\
		(op_type != HISEE_POWER_ON_UPGRADE) && (op_type != HISEE_POWER_ON_BOOTING_MISC) &&\
		(op_type != HISEE_POWER_ON_UPGRADE_SM)) {
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if ((HISEE_POWER_ON_BOOTING == op_type) || (HISEE_POWER_ON_UPGRADE == op_type) ||\
		(HISEE_POWER_ON_BOOTING_MISC == op_type) ||(HISEE_POWER_ON_UPGRADE_SM == op_type) )
		ret = set_hisee_state(HISEE_STATE_POWER_UP);
	else
		ret = set_hisee_state(HISEE_STATE_POWER_DOWN);
	if (HISEE_OK != ret) {
		pr_err("%s(): set_hisee_state faile,ret=%d.\n",  __func__, ret);
		set_errno_and_return(HISEE_SET_HISEE_STATE_ERROR);
	}

	tx_buffer[0] = IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_NOTIFY, 0);
	tx_buffer[1] = op_type;
	retry = 3;

	do {
		ret = RPROC_SYNC_SEND(rproc_id, tx_buffer, 2, ack_buffer, 2);
		if ((0 == ret) && (HISEE_LPM3_CMD == ack_buffer[0]) && (HISEE_LPM3_ACK_MAGIC == ack_buffer[1])) {
			/* the send is reponsed by the remote process, break out */
			ret = HISEE_OK;
			break;
		}
		else if (-ETIMEOUT == ret) {
			/*the timeout will print out, below message to tell it's normal*/
		    retry--;
			ret = HISEE_POWERCTRL_TIMEOUT_ERROR;
			pr_err("%s(): the ack of sending ipc is timeout.\n",  __func__);
			continue;
		} else {
			pr_err("%s(): send ipc failed\n", __func__);
			ret = HISEE_POWERCTRL_NOTIFY_ERROR;
			retry = 0;
			break;
		}
	} while (retry);
	if (0 == retry) {
		pr_err("%s(): send ipc with retry still failed\n", __func__);
		ret = HISEE_POWERCTRL_RETRY_FAILURE_ERROR;
	}
	set_errno_and_return(ret);
}

static int rpmb_ready_body(void *arg)
{
	int timeout = 500;
	int retry = 10;
	int ret = HISEE_OK;
	unsigned int upgrade_run_flg = 0;

	/*the task sleep 16 second until the kernel init completed */
	//msleep(16000);
	/*poll rpmb module ready status about 90 seconds*/
	do {
		if (get_rpmb_init_status()) {
			g_hisee_data.rpmb_is_ready = 1;
			break;
		}
		msleep(timeout);
		retry--;
	} while (retry > 0);

	if (0 == retry) {
		pr_err("%s BUG_ON\n", __func__);
		BUG_ON(1);
	} else {
		access_hisee_image_partition((char *)&upgrade_run_flg, COS_UPGRADE_RUN_READ_TYPE);
		if (HISEE_COS_UPGRADE_RUNNING_FLG == upgrade_run_flg) {
			if (get_rpmb_key_status()) { /*key ready*/
				wake_lock(&g_hisee_data.wake_lock);
				hisee_poweron_upgrade_func(NULL, 0);
				hisee_mdelay(200);
				ret = cos_image_upgrade_func(NULL, 0);
				wake_unlock(&g_hisee_data.wake_lock);
			}
		}
		else
			ret = load_cosimg_appdata_ddr();
	}

	/*ret = hisee_poweron_booting_func(NULL, 0);*/
	check_and_print_result();
	set_errno_and_return(ret);
}

static int hisee_poweron_booting_func(void *buf, int para)
{
	int ret = HISEE_OK;
	hisee_state state;

	mutex_lock(&g_hisee_data.hisee_mutex);
	if (HISEE_POWER_ON_UPGRADE_SUCCESS == powerctrl_status) {
		ret = hisee_poweroff_func(NULL, HISEE_PWROFF_NOLOCK);
		if (HISEE_OK != ret) {
			pr_err("%s() hisee_poweroff_func failed ret=%d\n", __func__, ret);
			goto end;
		}
	}

	state = (hisee_state)atfd_hisee_smc((u64)HISEE_FN_MAIN_SERVICE_CMD, (u64)CMD_GET_STATE, (u64)0, (u64)0);
	/*case1: 灭屏下hisee处于下电，直接通过NFC刷卡，hisee低功耗流程生效，lpm3给hisee上电。此时要by pass该上电操作
	 *case2: 灭屏下hisee处于下电，亮屏后通过NFC刷卡，hisee低功耗流程不生效，此时不要by pass该上电操作
	 */
	if (state == HISEE_STATE_POWER_UP || state == HISEE_STATE_COS_READY ||
		state == HISEE_STATE_MISC_READY || state == HISEE_STATE_POWER_UP_DOING) {
		g_hisee_data.power_on_count++;
		powerctrl_status = HISEE_POWER_ON_BOOTING_SUCCESS;
		goto end; /*bypass power_on*/
	} else {
		g_hisee_data.power_on_count = 0;
		powerctrl_status = HISEE_POWER_OFF_SUCCESS;
	}

	if (0 == g_hisee_data.power_on_count) {
		ret = clk_prepare_enable(g_hisee_data.hisee_clk);
		if (ret < 0) {
			pr_err("%s() clk_prepare_enable failed ret=%d.\n", __func__, ret);
			ret = HISEE_BULK_CLK_ENABLE_ERROR;
			goto end;
		}

		if (HISEE_POWER_ON_BOOTING_MISC == para)
			ret = hisee_powerctrl_func(HISEE_POWER_ON_BOOTING_MISC);
		else
			ret = hisee_powerctrl_func(HISEE_POWER_ON_BOOTING);
		if (ret == HISEE_OK) {
			powerctrl_status = HISEE_POWER_ON_BOOTING_SUCCESS;
		} else {
			powerctrl_status = HISEE_POWER_ON_BOOTING_FAILURE;
		}
	}
	g_hisee_data.power_on_count++;
end:
	mutex_unlock(&g_hisee_data.hisee_mutex);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

static int hisee_poweron_upgrade_func(void *buf, int para)
{
	int ret;
	hisee_state state;
	unsigned int hisee_lcs_mode = 0;

	ret = get_hisee_lcs_mode(&hisee_lcs_mode);
	if (HISEE_OK != ret) {
		pr_err("%s() get_hisee_lcs_mode failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}
	if (HISEE_SM_MODE_MAGIC == hisee_lcs_mode)
	{
		para = HISEE_POWER_ON_UPGRADE_SM;
	}

	mutex_lock(&g_hisee_data.hisee_mutex);

	if (HISEE_POWER_ON_BOOTING_SUCCESS == powerctrl_status) {
		ret = hisee_poweroff_func(NULL, HISEE_PWROFF_NOLOCK);
		if (HISEE_OK != ret) {
			pr_err("%s() hisee_poweroff_func failed ret=%d\n", __func__, ret);
			goto end;
		}
	}

	state = (hisee_state)atfd_hisee_smc((u64)HISEE_FN_MAIN_SERVICE_CMD, (u64)CMD_GET_STATE, (u64)0, (u64)0);
	/*case1: 灭屏下hisee处于下电，直接通过NFC刷卡，hisee低功耗流程生效，lpm3给hisee上电。此时要by pass该上电操作
	 *case2: 灭屏下hisee处于下电，亮屏后通过NFC刷卡，hisee低功耗流程不生效，此时不要by pass该上电操作
	 */
	if (state == HISEE_STATE_POWER_UP || state == HISEE_STATE_COS_READY ||
		state == HISEE_STATE_MISC_READY || state == HISEE_STATE_POWER_UP_DOING) {
		g_hisee_data.power_on_count++;
		goto end; /*bypass power_on*/
	} else {
		g_hisee_data.power_on_count = 0;
		powerctrl_status = HISEE_POWER_OFF_SUCCESS;
	}

	if (0 == g_hisee_data.power_on_count) {
		ret = clk_prepare_enable(g_hisee_data.hisee_clk);
		if (ret < 0) {
			pr_err("%s() clk_prepare_enable failed ret=%d.\n", __func__, ret);
			ret = HISEE_BULK_CLK_ENABLE_ERROR;
			goto end;
		}

		if (HISEE_POWER_ON_UPGRADE_SM == para)
			ret = hisee_powerctrl_func(HISEE_POWER_ON_UPGRADE_SM);
		else
			ret = hisee_powerctrl_func(HISEE_POWER_ON_UPGRADE);
		if (ret == HISEE_OK) {
			powerctrl_status = HISEE_POWER_ON_UPGRADE_SUCCESS;
		} else {
			powerctrl_status = HISEE_POWER_ON_UPGRADE_FAILURE;
		}
	}
	g_hisee_data.power_on_count++;
end:
	mutex_unlock(&g_hisee_data.hisee_mutex);
	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/


static int hisee_poweroff_func(void *buf, int para)
{
	int ret = HISEE_OK;

	if (HISEE_PWROFF_NOLOCK != para) {
		mutex_lock(&g_hisee_data.hisee_mutex);
	}
	if (powerctrl_status == HISEE_POWER_NONE)
		goto end;

	if (g_hisee_data.power_on_count > 0)
		g_hisee_data.power_on_count--;
	if (0 == g_hisee_data.power_on_count) {
		ret = hisee_powerctrl_func(HISEE_POWER_OFF);
		clk_disable_unprepare(g_hisee_data.hisee_clk);

		if (ret == HISEE_OK) {
			powerctrl_status = HISEE_POWER_OFF_SUCCESS;
		} else {
			powerctrl_status = HISEE_POWER_OFF_FAILURE;
		}

		g_hisee_data.smc_cmd_running = 0;
		if (g_hisee_data.apdu_command_buff_virt) {
			dma_free_coherent(g_hisee_data.cma_device, (unsigned long)(SIZE_1K * 4),
							g_hisee_data.apdu_command_buff_virt, g_hisee_data.apdu_command_buff_phy);
			g_hisee_data.apdu_command_buff_virt = NULL;
			g_hisee_data.apdu_command_buff_phy = 0;
		}
	}
end:
	if (HISEE_PWROFF_NOLOCK != para) {
		mutex_unlock(&g_hisee_data.hisee_mutex);
	}
	check_and_print_result();
	set_errno_and_return(ret);
}

static int hisee_poweroff_daemon_body(void *arg)
{
	int ret;
	timer_entry_list *cursor = NULL, *next = NULL;

	for (;;) {
		if (down_timeout(&g_hisee_poweroff_sem, (long)HISEE_THREAD_WAIT_TIMEOUT)) {
			mutex_lock(&g_poweron_timeout_mutex);
			if (0 == g_unhandled_timer_cnt) {
				/* exit this thread if wait sema timeout and theres no timer to be handled */
				g_daemon_created = false;
				mutex_unlock(&g_poweron_timeout_mutex);
				return 0;
			} else {
				mutex_unlock(&g_poweron_timeout_mutex);
				continue;
			}
		}
		/* got the sema */
		mutex_lock(&g_poweron_timeout_mutex);
		if (g_unhandled_timer_cnt > 0) {
			g_unhandled_timer_cnt--;
			ret = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
			if (HISEE_OK != ret)
				pr_err("%s  hisee poweroff failed, ret=%d\n", __func__, ret);
		}
		/*lint -e{613,529,438,64,826}*/
		list_for_each_entry_safe(cursor, next, &g_unhandled_timer_list, list) {
			if (atomic_read(&(cursor->handled))) {
				list_del(&(cursor->list));
				kfree(cursor);
			}
		}
		mutex_unlock(&g_poweron_timeout_mutex);
	}
}/*lint !e715*/

static int create_hisee_poweroff_daemon(void)
{
	struct task_struct *hisee_poweroff_daemon;

	/* create semaphore for daemon to wait poweroff signal */
	sema_init(&g_hisee_poweroff_sem, 0);

	hisee_poweroff_daemon = kthread_run(hisee_poweroff_daemon_body, NULL, "hisee_poweroff_daemon");
	if (IS_ERR(hisee_poweroff_daemon)) {
		pr_err("hisee err create hisee_poweroff_daemon failed\n");
		return HISEE_THREAD_CREATE_ERROR;
	}

	g_daemon_created = true;

	return HISEE_OK;
}

static void poweroff_handle(unsigned long arg)
{
	timer_entry_list *p_timer_entry = (timer_entry_list *)arg;

	atomic_set(&(p_timer_entry->handled), 1);

	up(&g_hisee_poweroff_sem);

	return;
}

static unsigned int parse_arg_get_timeout(void *buf, int para)
{
	char *cmd = (char *)buf;
	char *p = cmd;
	unsigned int num = 0;
	/* interface for direct call */
	if (NULL == buf) {
		if (para <= 0) return 0;
		return (unsigned int)para;
	}
	/* called through powerctrl_cmd */
	while ('\0' != *p && ' ' != *p) p++;
	if ('\0' == *p) return 0;
	while (' ' == *p) p++;
	if (kstrtouint(p, 0, &num)) /*its ok that cmd end with new line*/
		return 0;
	return num;
}

/* poweron hisee and add a timer to poweroff hisee _msecs_ ms later */
static int hisee_poweron_timeout_func(void *buf, int para)
{
	int ret;
	struct timer_list *p_timer;
	timer_entry_list *p_timer_entry;
	unsigned int msecs;
	msecs = parse_arg_get_timeout(buf, para);
	if (0 == msecs) {
		pr_err("%s()  invalid para, timeout not specified or not larger than 0\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	mutex_lock(&g_poweron_timeout_mutex);

	if (!g_daemon_created) {
		ret = create_hisee_poweroff_daemon();
		if (HISEE_OK != ret)
			goto end;
	}

	p_timer_entry = (timer_entry_list *)kmalloc(sizeof(timer_entry_list), GFP_KERNEL);
	if (NULL == p_timer_entry) {
		pr_err("%s()  timer kmalloc failed\n", __func__);
		ret = HISEE_NO_RESOURCES;
		goto end;
	}
	atomic_set(&(p_timer_entry->handled), 0);

	p_timer = &(p_timer_entry->timer);
	init_timer(p_timer);
	p_timer->function = poweroff_handle;
	p_timer->data     = (unsigned long)p_timer_entry;
	p_timer->expires  = jiffies + msecs_to_jiffies(msecs) + 1; /*+1 makes timeout >= msecs*/

	ret = hisee_poweron_booting_func(NULL, 0);
	if (HISEE_OK != ret) {
		(void)hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
		kfree(p_timer_entry);
		pr_err("%s()  hisee poweron booting failed, ret=%d\n", __func__, ret);
		goto end;
	}

	add_timer(p_timer);
	list_add(&(p_timer_entry->list), &g_unhandled_timer_list);
	g_unhandled_timer_cnt++;

end:
	mutex_unlock(&g_poweron_timeout_mutex);
	set_errno_and_return(ret);
}/*lint !e715*/

#ifdef __SLT_FEATURE__
static int hisee_total_slt_func(void *buf, int para)
{
	int ret1, ret = HISEE_OK;

	ret = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret) {
		pr_err("%s() hisee_poweroff_func 1 failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}
	ret = hisee_poweron_upgrade_func(NULL, 0);
	if (HISEE_OK != ret) {
		pr_err("%s() poweron upgrade failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}
	hisee_mdelay(300); /*lint !e744 !e747 !e748*/
	ret = cos_image_upgrade_func(NULL, HISEE_FACTORY_TEST_VERSION);
	if (HISEE_OK != ret) {
		pr_err("%s() cos_image_upgrade_func failed,ret=%d\n", __func__, ret);
		goto err_process;
	}

	hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
	ret = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret) {
		pr_err("%s() hisee_poweroff_func 2 failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}

	hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
	ret = hisee_poweron_booting_func(NULL, 0);
	if (HISEE_OK != ret) {
		pr_err("%s() poweron booting failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}

	hisee_delay(15); /*lint !e744 !e747 !e748*/

	ret = application_upgrade_func(NULL, 0);
	if (HISEE_OK != ret) {
		pr_err("%s() application_upgrade_func failed,ret=%d\n", __func__, ret);
		goto err_process;
	}
	hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
	pr_err("%s() success!\n", __func__);
	ret = HISEE_OK;
err_process:
	ret1 = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret1) {
		pr_err("%s() hisee poweroff entry failed,ret=%d\n", __func__, ret1);
		ret = ret1;
	}
	set_errno_and_return(ret);
}

static int hisee_read_slt_func(void *buf, int para)
{
	int err_code;
	int ret = HISEE_OK;

	err_code = atomic_read(&g_hisee_errno);

	if (HISEE_OK == err_code) {
		if (HISEE_FACTORY_TEST_SUCCESS != g_hisee_data.factory_test_state) {
			pr_err("%s() SLT test is not success, test_state=%x\n", __func__, g_hisee_data.factory_test_state);
			ret = HISEE_ERROR;
		}
	} else {
		ret = err_code;
		pr_err("%s() ret=%d\n", __func__, ret);
	}
	return ret;
}
static int slt_test_body(void *arg)
{
	int ret;
	int try_cnt = 3;

	if (g_hisee_data.factory_test_state != HISEE_FACTORY_TEST_RUNNING) {
		pr_err("%s BUG_ON\n", __func__);
		BUG_ON(1);
	}
	do {
		ret = hisee_total_slt_func(NULL, 0);
		if (HISEE_OK == ret) {
			g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_SUCCESS;
			check_and_print_result();
			set_errno_and_return(ret);
		}
		try_cnt--;
	} while(try_cnt > 0);
	g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_FAIL;
	check_and_print_result();
	set_errno_and_return(ret);
} /*lint !e715*/

static int hisee_parallel_total_slt_func(void *buf, int para)
{
	int ret = HISEE_OK;
	struct task_struct *slt_test_task = NULL;

	if (HISEE_FACTORY_TEST_RUNNING != g_hisee_data.factory_test_state) {
		g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_RUNNING;
		slt_test_task = kthread_run(slt_test_body, NULL, "slt_test_body");
		if (!slt_test_task) {
			ret = HISEE_THREAD_CREATE_ERROR;
			g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_FAIL;
			pr_err("hisee err create slt_test_task failed\n");
		} else
			pr_err("%s() success!\n", __func__);
	}
	set_errno_and_return(ret);
}/*lint !e715*/

#endif

static int g_hisee_debug_flag = 0;
void hisee_debug(void)
{
#ifdef CONFIG_HISI_DEBUG_FS
	g_hisee_debug_flag = 1;
#endif
}

static int flash_hisee_debug_switchs(void)
{
	int ret, ret1;

	ret = hisee_poweron_booting_func(NULL, 0);
	if (HISEE_OK != ret) {
		pr_err("%s() poweron booting failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}
	hisee_mdelay(500);
	ret = write_hisee_otp_value(OTP1_IMG_TYPE);
	if (HISEE_OK != ret)
		pr_err("%s() write_hisee_otp_value failed,ret=%d\n", __func__, ret);

	hisee_mdelay(DELAY_BETWEEN_STEPS);
	ret1 = hisee_poweroff_func(NULL, (int)HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret1)
		pr_err("%s() hisee_poweroff_func failed,ret=%d\n", __func__, ret1);

	check_and_print_result();
	set_errno_and_return(ret);
}

static int hisee_total_manafacture_func(void *buf, int para)
{
	int ret1, ret = HISEE_OK;
	unsigned int hisee_lcs_mode = 0;
	int write_rpmbkey_try = 5;
	/*unsigned char apdu_key_cmd0[21] = {	0xF0, 0x10, 0x00, 0x00, \
								0x10, 0x01, 0x23, 0x45, \
								0x67, 0x89, 0xab, 0xcd, \
								0xef, 0xfe, 0xdc, 0xba, \
								0x98, 0x76, 0x54, 0x32, \
								0x10};
	unsigned char apdu_key_cmd1[5] = {0xF0,0xd8, 0x00,0x00,0x00};
	unsigned char apdu_key_cmd2[5] = {0x00, 0xa4, 0x04, 0x00, 0x00};
	unsigned char apdu_key_cmd3[12] = {0x80, 0xe4, 0x00, 0x80,0x07, \
									  0x4f, 0x05, 0x12, 0x34, 0x56, \
									  0x78, 0x90};*/

	ret = get_hisee_lcs_mode(&hisee_lcs_mode);
	if (HISEE_OK != ret) {
		pr_err("%s() get_hisee_lcs_mode failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}
write_rpmbkey_retry_process:
	ret = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret) {
		pr_err("%s() hisee_poweroff_func 1 failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}
	if (HISEE_DM_MODE_MAGIC == hisee_lcs_mode) {
		ret = hisee_poweron_upgrade_func(NULL, 0);
	} else {
		ret = hisee_poweron_upgrade_func(NULL, HISEE_POWER_ON_UPGRADE_SM);
	}
	if (HISEE_OK != ret) {
		pr_err("%s() poweron upgrade failed,ret=%d\n", __func__, ret);
		set_errno_and_return(ret);
	}

	hisee_mdelay(200); /*lint !e744 !e747 !e748*/
	if (HISEE_DM_MODE_MAGIC == hisee_lcs_mode) {
		ret = write_rpmb_key_func(NULL, 0);
		if (HISEE_OK != ret) {
			write_rpmbkey_try--;
			if (0 == write_rpmbkey_try) {
				pr_err("%s() write_rpmb_key_func failed,ret=%d\n", __func__, ret);
				goto err_process;
			}
			goto write_rpmbkey_retry_process;
		}
	}

	hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
	ret = cos_image_upgrade_func(NULL, HISEE_FACTORY_TEST_VERSION);
	if (HISEE_OK != ret) {
		pr_err("%s() cos_image_upgrade_func failed,ret=%d\n", __func__, ret);
		goto err_process;
	}

	if (HISEE_DM_MODE_MAGIC == hisee_lcs_mode) {
#if 0
		hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
		ret = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
		if (HISEE_OK != ret) {
			pr_err("%s() hisee_poweroff_func 2 failed,ret=%d\n", __func__, ret);
			set_errno_and_return(ret);
		}
#endif
		hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
		ret = hisee_poweron_booting_func(NULL, 0);
		if (HISEE_OK != ret) {
			pr_err("%s() poweron booting failed,ret=%d\n", __func__, ret);
			set_errno_and_return(ret);
		}
		wait_hisee_ready(HISEE_STATE_MISC_READY, 30000);

		ret = otp_image_upgrade_func(NULL, 0);
		if (HISEE_OK != ret) {
			pr_err("%s() otp_image_upgrade_func failed,ret=%d\n", __func__, ret);
			goto err_process;
		}

		hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/

		ret = misc_image_upgrade_func(NULL, 0);
		if (HISEE_OK != ret) {
			pr_err("%s() misc_image_upgrade_func failed,ret=%d\n", __func__, ret);
			return ret;
		}
	}else {
		ret = hisee_misc_process();
		if (HISEE_OK != ret) {
			pr_err("%s() hisee_misc_process failed,ret=%d\n", __func__, ret);
			goto err_process;
		}
	}

	wait_hisee_ready(HISEE_STATE_COS_READY, 30000);
	ret = factory_apdu_test_func(NULL, 0);
	if (HISEE_OK != ret) {
		pr_err("%s() factory_apdu_test_func failed,ret=%d\n", __func__, ret);
		goto err_process;
	}

	/* send command to delete test applet */
	ret = send_apdu_cmd(HISEE_DEL_TEST_APPLET);
	if (HISEE_OK != ret) {
		pr_err("%s() send_apdu_cmd failed,ret=%d\n", __func__, ret);
		goto err_process;
	}

	if (HISEE_DM_MODE_MAGIC == hisee_lcs_mode) {
		if (g_hisee_debug_flag == 0) {

			ret = set_sm_lcs_func(NULL, 0);
			if (HISEE_OK != ret) {
				pr_err("%s() set_sm_lcs_func failed,ret=%d\n", __func__, ret);
				goto err_process;
			}

			hisee_mdelay(DELAY_BETWEEN_STEPS); /*lint !e744 !e747 !e748*/
			ret = set_hisee_lcs_sm_flg();
			if (HISEE_OK != ret) {
				pr_err("%s() set_hisee_lcs_sm_flg failed,ret=%d\n", __func__, ret);
				set_errno_and_return(ret);
				BUG_ON(1);
			}
		} else { 
		}
	}
	pr_err("%s() success!\n", __func__);
	ret = HISEE_OK;

err_process:
	ret1 = hisee_poweroff_func(NULL, HISEE_PWROFF_LOCK);
	if (HISEE_OK != ret1) {
		pr_err("%s() hisee poweroff entry failed,ret=%d\n", __func__, ret1);
		ret = ret1;
	}
	hisee_mdelay(DELAY_BETWEEN_STEPS);
	if (HISEE_OK == ret)
		release_hisee_semphore();

	set_errno_and_return(ret);
}

static int factory_test_body(void *arg)
{
	int ret;

	if (g_hisee_data.factory_test_state != HISEE_FACTORY_TEST_RUNNING) {
		pr_err("%s BUG_ON\n", __func__);
		BUG_ON(1);
	}
	ret = hisee_total_manafacture_func(NULL, 0);
	if (HISEE_OK != ret)
		g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_FAIL;
	else
		g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_SUCCESS;

	check_and_print_result();
	set_errno_and_return(ret);
} /*lint !e715*/

static int hisee_parallel_manafacture_func(void *buf, int para)
{
	int ret = HISEE_OK;
	struct task_struct *factory_test_task = NULL;

	if (HISEE_FACTORY_TEST_RUNNING != g_hisee_data.factory_test_state) {
		g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_RUNNING;
		factory_test_task = kthread_run(factory_test_body, NULL, "factory_test_body");
		if (!factory_test_task) {
			ret = HISEE_THREAD_CREATE_ERROR;
			g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_FAIL;
			pr_err("hisee err create factory_test_task failed\n");
		}
	}
	set_errno_and_return(ret);
}/*lint !e715*/

static void show_hisee_module_status(char *buff)
{
	char counter_value[12] = {0};
	char *index_name = "rpmb_is_ready=";
	snprintf(counter_value, sizeof(counter_value), "%d\n", g_hisee_data.rpmb_is_ready);
	strncpy(buff, index_name, strlen(index_name));
	strncpy(buff + strlen(buff), counter_value, strlen(counter_value));

	memset(counter_value, 0, 12);
	index_name = "smc_cmd_running=";
	snprintf(counter_value, sizeof(counter_value), "%d\n", g_hisee_data.smc_cmd_running);
	strncpy(buff + strlen(buff), index_name, strlen(index_name));
	strncpy(buff + strlen(buff), counter_value, strlen(counter_value));

	memset(counter_value, 0, 12);
	index_name = "img_header_is_parse=";
	snprintf(counter_value, sizeof(counter_value), "%d\n", g_hisee_data.img_header_is_parse);
	strncpy(buff + strlen(buff), index_name, strlen(index_name));
	strncpy(buff + strlen(buff), counter_value, strlen(counter_value));

	return;
}

/** read the ioctl_cmd execute status
 * @buf: output, save the ioctl_cmd execute status, the size should less than 64 bytes
 */
static ssize_t hisee_ioctl_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int err_code;
	int ret = 0;
	char buff[HISEE_CMD_NAME_LEN] = {0};
	int i;

	if (NULL == buf) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	memset(buff, 0, HISEE_CMD_NAME_LEN);
	err_code = atomic_read(&g_hisee_errno);
	for (i = 0; i < ARRAY_SIZE(g_errcode_items_des); i++) {
		if (err_code == g_errcode_items_des[i].err_code) {
			break;
		}
	}
	if (i == ARRAY_SIZE(g_errcode_items_des)) {
		pr_err("%s(): can't find errcode=%d definition\n", __func__, err_code);
		strncpy(buf, "-1,failed!", sizeof("-1,failed!"));
		return strlen(buf);
	}
	if (HISEE_OK == err_code) {
		if (HISEE_FACTORY_TEST_NORUNNING == g_hisee_data.factory_test_state) {
			snprintf(buff, 8, "%d,", 2);
			strncat(buff, "no running", (unsigned long)(HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff)));
		} else if (HISEE_FACTORY_TEST_RUNNING == g_hisee_data.factory_test_state) {
			snprintf(buff, 8, "%d,", 1);
			strncat(buff, "running", (unsigned long)(HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff)));
		} else if (HISEE_FACTORY_TEST_SUCCESS == g_hisee_data.factory_test_state) {
			snprintf(buff, 8, "%d,", 0);
			strncat(buff, "no error", (unsigned long)(HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff)));
		}
	} else {
	snprintf(buff, 8, "%d,", err_code);
	strncat(buff, g_errcode_items_des[i].err_description, (unsigned long)(HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff)));
	}
	memcpy(buf, buff, HISEE_ERROR_DESCRIPTION_MAX);

	memset(buff, 0, HISEE_CMD_NAME_LEN);
	show_hisee_module_status(buff);
	pr_err("%s\n", buff);

	return strlen(buf);
}

/** write the ioctl_cmd to execute
 * @buf: input, save the ioctl_cmd string should be execute
 */
static ssize_t hisee_ioctl_store (struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	int i = 0;
	int cmd_index = 0;
	char *ptr_name = NULL;

	if (NULL == buf || (strlen(buf) >= HISEE_CMD_NAME_LEN)) {
		pr_err("%s buf paramters is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (count <= 0 || (count >= HISEE_CMD_NAME_LEN)) {
		pr_err("%s count paramters is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (!g_hisee_data.rpmb_is_ready) {
		pr_err("%s rpmb is not ready now\n", __func__);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_COS_IMAGE_UPGRADE_ERROR_NO, HISEE_RPMB_MODULE_INIT_ERROR);
		set_errno_and_return(HISEE_RPMB_MODULE_INIT_ERROR);
	}
	for (ptr_name = g_hisee_atf_function_list[i].function_name; ptr_name != NULL;) {
		if (!strncmp(buf, ptr_name, strlen(ptr_name))) {
			cmd_index = i;
			break;
		}
		i++;
		ptr_name = g_hisee_atf_function_list[i].function_name;
	}
	if (!ptr_name) {
		pr_err("%s cmd=%s invalid\n", __func__, buf);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	/* one of the three cases makes this condition is false, than do next operation:
	 * 1. cmd index is hisee_factory_action or hisee_slt_action or hisee_slt_read
	 * 2. powerctrl_status is HISEE_POWER_ON_BOOTING_SUCCESS
	 * 3. powerctrl_status is HISEE_POWER_ON_UPGRADE_SUCCESS
	 */
	if ((MANAFACTOR_CMD_INDEX > cmd_index) && (powerctrl_status != HISEE_POWER_ON_BOOTING_SUCCESS && powerctrl_status != HISEE_POWER_ON_UPGRADE_SUCCESS)) {
		pr_err("%s hisee is not poweron\n", __func__);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_COS_IMAGE_UPGRADE_ERROR_NO, HISEE_POWERCTRL_FLOW_ERROR);
		set_errno_and_return(HISEE_POWERCTRL_FLOW_ERROR);
	}
	ret = g_hisee_atf_function_list[cmd_index].function_ptr((void *)(buf + strlen(g_hisee_atf_function_list[cmd_index].function_name)),
															(int)(long)dev);
	if (ret !=  HISEE_OK) {
		pr_err("%s ioctl_cmd:%s failed, retcode=%d\n", __func__, g_hisee_atf_function_list[cmd_index].function_name, ret);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_COS_IMAGE_UPGRADE_ERROR_NO, ret);
		return HISEE_INVALID_PARAMS;
	} else {
		pr_err("%s ioctl_cmd:%s success\n", __func__, g_hisee_atf_function_list[cmd_index].function_name);
		return count;
	}
}

/** read the powerctrl_cmd execute status
 * @buf: output, save the ioctl_cmd execute status, the size not less than 160 bytes
 */
static ssize_t hisee_powerctrl_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret = 0;
	char buff[HISEE_ERROR_DESCRIPTION_MAX];

	if (NULL == buf) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	memset(buff, 0, HISEE_ERROR_DESCRIPTION_MAX);
	switch (powerctrl_status) {
	case HISEE_POWER_ON_BOOTING_SUCCESS:
		strncat(buff, "1", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	case HISEE_POWER_ON_BOOTING_FAILURE:
		strncat(buff, "2", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	case HISEE_POWER_ON_UPGRADE_SUCCESS:
		strncat(buff, "3", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	case HISEE_POWER_ON_UPGRADE_FAILURE:
		strncat(buff, "4", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	case HISEE_POWER_OFF_SUCCESS:
		strncat(buff, "5", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	case HISEE_POWER_OFF_FAILURE:
		strncat(buff, "6", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	case HISEE_POWER_NONE:
		strncat(buff, "7", HISEE_ERROR_DESCRIPTION_MAX - 1 - strlen(buff));
		break;
	default:
		pr_err("%s(): invalid powerctrl status\n", __func__);
		strncpy(buf, "0", sizeof("0"));
		return strlen(buf);
	}

	memcpy(buf, buff, HISEE_ERROR_DESCRIPTION_MAX);
	pr_err("%s(): success.\n", __func__);
	return strlen(buf);
}/*lint !e715*/

/** write the powerctrl_cmd to execute
 * @buf: input, save the powerctrl_cmd string should be execute
 */
static ssize_t hisee_powerctrl_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	int i = 0;
	int cmd_index = 0;
	unsigned int upgrade_run_flg;
	unsigned int hisee_lcs_mode = 0;
	char *ptr_name = NULL;
	if (NULL == buf || (strlen(buf) >= HISEE_CMD_NAME_LEN)) {
		pr_err("%s buf paramters is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (count <= 0 || (count >= HISEE_CMD_NAME_LEN)) {
		pr_err("%s count paramters is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	for (ptr_name = g_hisee_lpm3_function_list[i].function_name; ptr_name != NULL;) {
		if (!strncmp(buf, ptr_name, strlen(ptr_name))) {
			cmd_index = i;
			break;
		}
		i++;
		ptr_name = g_hisee_lpm3_function_list[i].function_name;
	}
	if (!ptr_name) {
		pr_err("%s cmd=%s invalid\n", __func__, buf);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	ret = get_hisee_lcs_mode(&hisee_lcs_mode);
	if (HISEE_OK != ret) {
		pr_err("%s() get_hisee_lcs_mode failed,ret=%d\n", __func__, ret);
		if (0 == cmd_index) set_errno_and_return(ret);
	}
	if ((unsigned int)HISEE_SM_MODE_MAGIC == hisee_lcs_mode && (0 == cmd_index)) {
		upgrade_run_flg = HISEE_COS_UPGRADE_RUNNING_FLG;
		access_hisee_image_partition((char *)&upgrade_run_flg, COS_UPGRADE_RUN_WRITE_TYPE);
	}
	if (!g_hisee_data.rpmb_is_ready) {
		pr_err("%s rpmb is not ready now\n", __func__);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_POWER_ON_OFF_ERROR_NO, HISEE_RPMB_MODULE_INIT_ERROR);
		set_errno_and_return(HISEE_RPMB_MODULE_INIT_ERROR);
	}
	ret = g_hisee_lpm3_function_list[cmd_index].function_ptr((void *)buf, (int)(long)dev);
	if (ret !=  HISEE_OK) {
		pr_err("%s ioctl_cmd:%s failed, retcode=%d\n", __func__, g_hisee_lpm3_function_list[cmd_index].function_name, ret);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_POWER_ON_OFF_ERROR_NO, ret);
		return HISEE_INVALID_PARAMS;
	} else {
		pr_err("%s ioctl_cmd:%s success\n", __func__, g_hisee_lpm3_function_list[cmd_index].function_name);
		if ((unsigned int)HISEE_SM_MODE_MAGIC == hisee_lcs_mode && (0 == cmd_index)) {
			upgrade_run_flg = 0;
			access_hisee_image_partition((char *)&upgrade_run_flg, COS_UPGRADE_RUN_WRITE_TYPE);
		}
		return count;
	}
}

static int write_apdu_command_func (char *apdu_buf, int apdu_len)
{
	atf_message_header *p_message_header;
	int ret = HISEE_OK;
	int image_size;

	if (NULL == g_hisee_data.apdu_command_buff_virt) {
		g_hisee_data.apdu_command_buff_virt = (void *)dma_alloc_coherent(g_hisee_data.cma_device, (u64)(SIZE_1K * 4),
											&(g_hisee_data.apdu_command_buff_phy), GFP_KERNEL);
	}
	if (NULL == g_hisee_data.apdu_command_buff_virt) {
		pr_err("%s(): dma_alloc_coherent failed\n", __func__);
		set_errno_and_return(HISEE_NO_RESOURCES);
	}
	memset(g_hisee_data.apdu_command_buff_virt, 0, (u64)(SIZE_1K * 4));
	p_message_header = (atf_message_header *)g_hisee_data.apdu_command_buff_virt; /*lint !e826*/
	set_message_header(p_message_header, CMD_APDU_RAWDATA);

	apdu_len = (apdu_len > HISEE_APDU_DATA_LEN_MAX) ?  HISEE_APDU_DATA_LEN_MAX : apdu_len;
	memcpy(g_hisee_data.apdu_command_buff_virt + HISEE_ATF_MESSAGE_HEADER_LEN, (void *)apdu_buf, (u64)apdu_len);/*lint !e124*/
	image_size = HISEE_ATF_MESSAGE_HEADER_LEN + apdu_len;
	p_message_header->test_result_phy = (u32)(g_hisee_data.apdu_command_buff_phy + (SIZE_1K * 2));
	p_message_header->test_result_size = (unsigned int)SIZE_1K;
	ret = send_smc_process(p_message_header, g_hisee_data.apdu_command_buff_phy, (u32)image_size,
							HISEE_ATF_GENERAL_TIMEOUT, CMD_APDU_RAWDATA);

	if (HISEE_OK == ret && p_message_header->test_result_size <= HISEE_APDU_DATA_LEN_MAX) {
		memcpy(g_hisee_data.apdu_ack.ack_buf, (g_hisee_data.apdu_command_buff_virt + (SIZE_1K * 2)), (u64)p_message_header->test_result_size);
		g_hisee_data.apdu_ack.ack_len = p_message_header->test_result_size;
	} else {
		g_hisee_data.apdu_ack.ack_len = 0;
		pr_err("%s(): p_message_header->test_result_size=%x failed\n", __func__, p_message_header->test_result_size);
	}

	check_and_print_result();
	set_errno_and_return(ret);
}/*lint !e715*/

/** read the apdu command response,size is 0--255 bytes
 * @buf: output, save the apdu command ack data, the size is 0--255 bytes
 */
static ssize_t hisee_apdu_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret = 0;

	if (NULL == buf) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (HISEE_APDU_DATA_LEN_MAX < g_hisee_data.apdu_ack.ack_len) {
		pr_err("%s BUG_ON\n", __func__);
		BUG_ON(1);/*lint !e730*/
	}
#ifdef HISEE_DEBUG
	int i;
	pr_err("%s(): ack_len=%d.\n", __func__, g_hisee_data.apdu_ack.ack_len);
	for (i = 0; i < g_hisee_data.apdu_ack.ack_len; i++)
		pr_err("[i=%3d]:%x\n", i, g_hisee_data.apdu_ack.ack_buf[i]);
#endif
	if (g_hisee_data.smc_cmd_running) {
		pr_err("%s(): apdu is running,no response\n", __func__);
		g_hisee_data.apdu_ack.ack_len = 0;
		buf[0] = 0;
	} else {
		memcpy(buf, g_hisee_data.apdu_ack.ack_buf, (u64)g_hisee_data.apdu_ack.ack_len);
		buf[g_hisee_data.apdu_ack.ack_len] = 0;
	}

	return (ssize_t)g_hisee_data.apdu_ack.ack_len;
}/*lint !e715*/

/** write the apdu command function, size is 0--261 bytes
 * @buf: input, save the  apdu command data should be execute
 */
static ssize_t hisee_apdu_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;

	if (NULL == buf) {
		pr_err("%s buf paramters is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (count == 0 || (count > HISEE_APDU_DATA_LEN_MAX)) {
		pr_err("%s count paramters is invalid\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	if (!g_hisee_data.rpmb_is_ready) {
		pr_err("%s rpmb is not ready now\n", __func__);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_APDU_COMMAND_OPERATION_ERROR_NO, HISEE_RPMB_MODULE_INIT_ERROR);
		set_errno_and_return(HISEE_RPMB_MODULE_INIT_ERROR);
	}

	if ((powerctrl_status != HISEE_POWER_ON_BOOTING_SUCCESS && powerctrl_status != HISEE_POWER_ON_UPGRADE_SUCCESS)) {
		pr_err("%s hisee is not poweron\n", __func__);
		record_hisee_log_by_dmd(DSM_NFC_HISEE_APDU_COMMAND_OPERATION_ERROR_NO, HISEE_POWERCTRL_FLOW_ERROR);
		set_errno_and_return(HISEE_POWERCTRL_FLOW_ERROR);
	}

#ifdef HISEE_DEBUG
	int i;
	for (i = 0; i < count; i++)
		pr_err("[%3d]:%x\n", i, buf[i]);
#endif
	ret = write_apdu_command_func((char *)buf, (int)count);
	if (ret !=  HISEE_OK) {
		record_hisee_log_by_dmd(DSM_NFC_HISEE_APDU_COMMAND_OPERATION_ERROR_NO, ret);
		return HISEE_INVALID_PARAMS;
	} else {
		pr_err("%s write_apdu_command_func success, retcode=%d\n", __func__, ret);
		return (ssize_t)count;
	}
}/*lint !e715*/

/** check whether the hisee is ready
 * @buf: output, return the hisee ready status
 */
static ssize_t hisee_check_ready_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	hisee_state state;
	int ret;

	if (NULL == buf) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}
	state = (hisee_state)atfd_hisee_smc((u64)HISEE_FN_MAIN_SERVICE_CMD, (u64)CMD_GET_STATE, (u64)0, (u64)0);
	if (HISEE_STATE_COS_READY == state) {
		snprintf(buf, (u64)3, "%d,", 0);
		strncat(buf, "cos ready", (unsigned long)strlen("cos ready"));
	} else if (HISEE_STATE_POWER_DOWN == state
				|| HISEE_STATE_POWER_UP == state
				|| HISEE_STATE_MISC_READY == state
				|| HISEE_STATE_POWER_DOWN_DOING == state
				|| HISEE_STATE_POWER_UP_DOING == state) {
		snprintf(buf, (u64)3, "%d,", 1);
		strncat(buf, "cos unready", (unsigned long)strlen("cos unready"));
	} else {
		snprintf(buf, (u64)4, "%d,", -1);
		strncat(buf, "failed", (unsigned long)strlen("failed"));
	}

	pr_err("%s(): state=%d, %s\n", __func__, (int)state, buf);
	return (ssize_t)strlen(buf);
}/*lint !e715*/

static ssize_t hisee_has_new_cos_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int new_cos_exist = 0;
	int ret;

	if (NULL == buf) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	ret = check_new_cosimage(&new_cos_exist);
	if (HISEE_OK == ret) {
		if (1 == new_cos_exist) {/*lint !e774*/
			snprintf(buf, (u64)3, "%d,", 0);
			strncat(buf, "exsited new cosimage", (unsigned long)strlen("exsited new cosimage"));
		} else {
			snprintf(buf, (u64)3, "%d,", 1);
			strncat(buf, "no exsited new cosimage", (unsigned long)strlen("no exsited new cosimage"));
		}
	} else {
		snprintf(buf, (u64)4, "%d,", -1);
		strncat(buf, "failed", (unsigned long)strlen("failed"));
	}
	pr_err("%s(): %s\n", __func__, buf);
	return (ssize_t)strlen(buf);
}/*lint !e715*/

static ssize_t hisee_check_upgrade_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int upgrade_run_flg = 0;
	int ret;

	if (NULL == buf) {
		pr_err("%s buf paramters is null\n", __func__);
		set_errno_and_return(HISEE_INVALID_PARAMS);
	}

	access_hisee_image_partition((char *)&upgrade_run_flg, COS_UPGRADE_RUN_READ_TYPE);
	if (0 == upgrade_run_flg) {
		snprintf(buf, HISEE_BUF_SHOW_LEN, "0,cos upgrade success");
	} else if (HISEE_COS_UPGRADE_RUNNING_FLG == upgrade_run_flg) {
		snprintf(buf, HISEE_BUF_SHOW_LEN, "1,cos upgrade failed last time");
	} else {
		snprintf(buf, HISEE_BUF_SHOW_LEN, "-1,failed");
	}

	pr_err("%s(): %s\n", __func__, buf);
	return (ssize_t)strlen(buf);
}/*lint !e715*/

/* only root permissions can access this sysfs node */
/*lint -e84 -esym(84,*) */
/*lint -e846 -esym(846,*) */
/*lint -e514 -esym(514,*) */
/*lint -e866 -esym(866,*) */
/*lint -e778 -esym(778,*) */
static DEVICE_ATTR(hisee_ioctl, (S_IRUSR | S_IWUSR), hisee_ioctl_show, hisee_ioctl_store);
static DEVICE_ATTR(hisee_power, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP), hisee_powerctrl_show, hisee_powerctrl_store);
static DEVICE_ATTR(hisee_apdu, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP), hisee_apdu_show, hisee_apdu_store);
static DEVICE_ATTR(hisee_check_ready, (S_IRUSR | S_IRGRP), hisee_check_ready_show, NULL);
static DEVICE_ATTR(hisee_has_new_cos, (S_IRUSR | S_IRGRP), hisee_has_new_cos_show, NULL);
static DEVICE_ATTR(hisee_check_upgrade, (S_IRUSR | S_IRGRP), hisee_check_upgrade_show, NULL);
/*lint +e778 +esym(778,*) */
/*lint +e84 +esym(84,*) */
/*lint +e846 +esym(846,*) */
/*lint +e514 +esym(514,*) */
/*lint +e866 +esym(866,*) */

static int hisee_remove(struct platform_device *pdev)
{
	int ret = HISEE_OK;
	if (g_hisee_data.cma_device) {
		device_remove_file(g_hisee_data.cma_device, &dev_attr_hisee_ioctl);
		device_remove_file(g_hisee_data.cma_device, &dev_attr_hisee_power);
		device_remove_file(g_hisee_data.cma_device, &dev_attr_hisee_apdu);
		device_remove_file(g_hisee_data.cma_device, &dev_attr_hisee_check_ready);
		device_remove_file(g_hisee_data.cma_device, &dev_attr_hisee_has_new_cos);
		device_remove_file(g_hisee_data.cma_device, &dev_attr_hisee_check_upgrade);
		of_reserved_mem_device_release(g_hisee_data.cma_device);
	}
	return ret;
}

static int __init hisee_probe(struct platform_device *pdev)
{
	struct device *pdevice = &(pdev->dev);
	struct task_struct *rpmb_ready_task = NULL;
	int ret = HISEE_OK;

	memset((void *)&g_hisee_data, 0, sizeof(g_hisee_data));
	ret = of_reserved_mem_device_init(pdevice);
	if (ret != HISEE_OK) {
		pr_err("hisee shared cma pool with ATF registered failed!\n");
		set_errno_and_return(HISEE_CMA_DEVICE_INIT_ERROR);
	}
	g_hisee_data.cma_device = pdevice;
	pr_err("hisee shared cma pool with ATF registered success!\n");

	if (device_create_file(pdevice, &dev_attr_hisee_ioctl)) {
		ret = HISEE_IOCTL_NODE_CREATE_ERROR;
		pr_err("hisee err unable to create hisee_ioctl attributes\n");
		goto err_mem_release;
	}

	if (device_create_file(pdevice, &dev_attr_hisee_power)) {
		ret = HISEE_POWER_NODE_CREATE_ERROR;
		pr_err("hisee err unable to create hisee_power attributes\n");
		goto err_device_remove_file;
	}
	if (device_create_file(pdevice, &dev_attr_hisee_apdu)) {
		ret = HISEE_IOCTL_NODE_CREATE_ERROR;
		pr_err("hisee err unable to create hisee_apdu attributes\n");
		goto err_device_remove_file1;
	}

	if (device_create_file(pdevice, &dev_attr_hisee_check_ready)) {
		ret = HISEE_POWER_NODE_CREATE_ERROR;
		pr_err("hisee err unable to create hisee_check_ready attributes\n");
		goto err_device_remove_file2;
	}
	if (device_create_file(pdevice, &dev_attr_hisee_has_new_cos)) {
		ret = HISEE_POWER_NODE_CREATE_ERROR;
		pr_err("hisee err unable to create hisee_has_new_cos attributes\n");
		goto err_device_remove_file3;
	}
	if (device_create_file(pdevice, &dev_attr_hisee_check_upgrade)) {
		ret = HISEE_POWER_NODE_CREATE_ERROR;
		pr_err("hisee err unable to create hisee_check_upgrade attributes\n");
		goto err_device_remove_file4;
	}

	g_hisee_data.hisee_clk = clk_get(NULL, "hise_volt_hold");
	if (IS_ERR_OR_NULL(g_hisee_data.hisee_clk)) {
		ret = HISEE_BULK_CLK_INIT_ERROR;
		pr_err("hisee err clk_get failed\n");
		goto err_device_remove_file_end;
	}

	mutex_init(&(g_hisee_data.hisee_mutex));
	sema_init(&(g_hisee_data.atf_sem), 0);
	atomic_set(&g_hisee_errno, HISEE_OK);
	g_hisee_data.factory_test_state = HISEE_FACTORY_TEST_NORUNNING;
	powerctrl_status = HISEE_POWER_NONE;
	mutex_init(&g_poweron_timeout_mutex);
	g_unhandled_timer_cnt = 0;
	INIT_LIST_HEAD(&g_unhandled_timer_list);
	wake_lock_init(&g_hisee_data.wake_lock, WAKE_LOCK_SUSPEND, "hisi-hisee"); /*used in rpmb_ready_task*/

	rpmb_ready_task = kthread_run(rpmb_ready_body, NULL, "rpmb_ready_task");
	if (!rpmb_ready_task) {
		ret = HISEE_THREAD_CREATE_ERROR;
		pr_err("hisee err create rpmb_ready_task failed\n");
		goto err_device_remove_file_end;
	}

	register_flash_hisee_otp_fn(flash_hisee_debug_switchs);
	pr_err("hisee module init success!\n");
	set_errno_and_return(HISEE_OK);
err_device_remove_file_end:
	device_remove_file(pdevice, &dev_attr_hisee_check_upgrade);
err_device_remove_file4:
	device_remove_file(pdevice, &dev_attr_hisee_has_new_cos);
err_device_remove_file3:
	device_remove_file(pdevice, &dev_attr_hisee_check_ready);
err_device_remove_file2:
	device_remove_file(pdevice, &dev_attr_hisee_apdu);
err_device_remove_file1:
	device_remove_file(pdevice, &dev_attr_hisee_power);
err_device_remove_file:
	device_remove_file(pdevice, &dev_attr_hisee_ioctl);
err_mem_release:
	of_reserved_mem_device_release(g_hisee_data.cma_device);

	pr_err("hisee module init failed!\n");
	set_errno_and_return(ret);
}

static int hisee_suspend(struct platform_device *pdev, struct pm_message state)
{
	timer_entry_list *cursor = NULL, *next = NULL;
	pr_err("hisi_hisee_suspend: +\n");
	mutex_lock(&g_poweron_timeout_mutex);

	/*lint -e{64,826,838} */
	list_for_each_entry_safe(cursor, next, &g_unhandled_timer_list, list) {
		list_del(&(cursor->list));
		del_timer_sync(&(cursor->timer));
		kfree(cursor);
	}

	sema_init(&g_hisee_poweroff_sem, 0);
	g_unhandled_timer_cnt = 0;

	mutex_unlock(&g_poweron_timeout_mutex);
	pr_err("hisi_hisee_suspend: -\n");
	return HISEE_OK;
}/*lint !e715*/

static const struct of_device_id hisee_of_match[] = {
	{.compatible = "hisilicon,hisee-device" },
	{ }
};
MODULE_DEVICE_TABLE(of, hisee_of_match);

static struct platform_driver hisee_driver = {
	.probe = hisee_probe,
	.remove = hisee_remove,
	.suspend = hisee_suspend,
	.driver = {
		.name  = HISEE_DEVICE_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisee_of_match),
	},
};

static int __init hisee_module_init(void)
{
	int ret = 0;
	ret = platform_driver_register(&hisee_driver);
	if (ret) {
		pr_err("register hisee driver failed.\n");
	}
	return ret;
}
static void __exit hisee_module_exit(void)
{
	platform_driver_unregister(&hisee_driver);
}
module_init(hisee_module_init);
module_exit(hisee_module_exit);

MODULE_AUTHOR("<lvtaolong@hisilicon.com>");
MODULE_DESCRIPTION("HISEE KERNEL DRIVER");
MODULE_LICENSE("GPL V2");
