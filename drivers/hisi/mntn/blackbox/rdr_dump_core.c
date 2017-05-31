/*
 * blackbox. (kernel run data recorder.)
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/uaccess.h>
#include <linux/rtc.h>
#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/vmalloc.h>

#include <linux/hisi/hisi_bootup_keypoint.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>
#include "rdr_inner.h"
#include "rdr_print.h"
#include "rdr_field.h"
#include <hisi_partition.h>
#include <linux/hisi/kirin_partition.h>
#include <linux/mfd/hisi_pmic.h>

/*
 * func name: rdr_save_history_log
 * save exce info to history.log .
 * func args:
 *  struct rdr_exception_info_s,	exec info.
 *  char*,                          path.
 * return
 *	!0   fail
 *	== 0 success
 */
#define HISTORY_LOG_SIZE 256
#define HISTORY_LOG_MAX  0x400000	/*64*16*1024*4 = 4M */

int rdr_save_history_log(struct rdr_exception_info_s *p, char *date,
			 bool is_save_done, u32 bootup_keypoint)
{
	int ret = 0;
	char buf[HISTORY_LOG_SIZE];
	struct kstat historylog_stat;
	mm_segment_t old_fs;
	char local_path[PATH_MAXLEN];
	char *reboot_from_ap;

	if (!check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		return 0;
	}
	BB_PRINT_START();
	if (DATATIME_MAXLEN < (strlen(date) + 1)) {
		date[DATATIME_MAXLEN - 1] = '\0';
	}
	memset(buf, 0, HISTORY_LOG_SIZE);

	if (p->e_reset_core_mask & RDR_AP)
		reboot_from_ap = "true";
	else
		reboot_from_ap = "false";
	/*����˴θ�λ���߼������̵ģ���������¼��������Ҫ����last_save_not_done�ַ��� */
	if (is_save_done) {
		snprintf(buf, HISTORY_LOG_SIZE,
			 "system exception core [%s], reason [%s], time [%s], sysreboot[%s], bootup_keypoint [%d]\n",
			 rdr_get_exception_core(p->e_from_core),
			 rdr_get_exception_type(p->e_exce_type), date, reboot_from_ap, bootup_keypoint);
	} else {
		snprintf(buf, HISTORY_LOG_SIZE,
			 "system exception core [%s], reason [%s], time [%s][last_save_not_done], sysreboot[%s]\n",
			 rdr_get_exception_core(p->e_from_core),
			 rdr_get_exception_type(p->e_exce_type), date, reboot_from_ap);
	}

	memset(local_path, 0, PATH_MAXLEN);
	snprintf(local_path, PATH_MAXLEN, "%s/%s", PATH_ROOT, "history.log");

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	if (0 == vfs_stat(local_path, &historylog_stat) &&
	    historylog_stat.size > HISTORY_LOG_MAX) {
		sys_unlink(local_path);	/* delete history.log */
	}

	if (0 != vfs_stat(PATH_ROOT, &historylog_stat)) {
		ret = rdr_dump_init(NULL);
		if (ret) {
			BB_PRINT_ERR("%s():rdr_create_dir fail\n", __func__);
			set_fs(old_fs);
			return ret;
		}
	}

	set_fs(old_fs);

	rdr_savebuf2fs(PATH_ROOT, "history.log", buf, strlen(buf), 1);
	BB_PRINT_END();
	return ret;
}

int rdr_save_history_log_for_undef_exception(struct rdr_syserr_param_s *p)
{
	int ret = 0;
	char buf[HISTORY_LOG_SIZE];
	struct kstat historylog_stat;
	mm_segment_t old_fs;
	char local_path[PATH_MAXLEN];

	if (!check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		return 0;
	}
	BB_PRINT_START();
	memset(buf, 0, HISTORY_LOG_SIZE);
	snprintf(buf, HISTORY_LOG_SIZE,
		 "system exception undef. modid[0x%x], arg [0x%x], arg [0x%x].\n",
		 p->modid, p->arg1, p->arg2);

	memset(local_path, 0, PATH_MAXLEN);
	snprintf(local_path, PATH_MAXLEN, "%s/%s", PATH_ROOT, "history.log");

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	if (0 == vfs_stat(local_path, &historylog_stat) &&
	    historylog_stat.blksize > HISTORY_LOG_MAX) {
		sys_unlink(local_path);	/* delete history.log */
	}

	set_fs(old_fs);

	rdr_savebuf2fs(PATH_ROOT, "history.log", buf, strlen(buf), 1);
	BB_PRINT_END();
	return ret;
}

/*
 * func name: rdr_savebuf2fs
 * append(save) data to path.
 * func args:
 *  char*  path,			path of save file.
 *  void*  buf,             save data.
 *  u32 len,            data lenght.
 *  u32 is_append,      determine whether write with append
 * return
 *	>=len fail
 *	==len success
 */
int rdr_savebuf2fs(char *logpath, char *filename,
		   void *buf, u32 len, u32 is_append)
{
	int ret = 0, flags;
	struct file *fp;
	mm_segment_t old_fs;
	char path[PATH_MAXLEN];

	BB_PRINT_START();
	if (logpath == NULL || filename == NULL || buf == NULL || len <= 0) {
		BB_PRINT_PN("invalid  parameter. path:%pK, name:%pK buf:%pK len:0x%x\n",
		     logpath, filename, buf, len);
		ret = -1;
		goto out2;
	}

	snprintf(path, PATH_MAXLEN, "%s/%s", logpath, filename);

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	flags = O_CREAT | O_RDWR | (is_append ? O_APPEND : O_TRUNC);
	fp = filp_open(path, flags, FILE_LIMIT);
	if (IS_ERR(fp)) {
		set_fs(old_fs);
		BB_PRINT_ERR("%s():create file %s err.\n", __func__, path);
		ret = -1;
		goto out2;
	}
	vfs_llseek(fp, 0L, SEEK_END);
	ret = vfs_write(fp, buf, len, &(fp->f_pos));
	if (ret != len) {
		BB_PRINT_ERR("%s():write file %s exception with ret %d.\n",
			     __func__, path, ret);
		goto out1;
	}

	vfs_fsync(fp, 0);
out1:
	filp_close(fp, NULL);

	/*����Ȩ��Ҫ��hisi_logsĿ¼����Ŀ¼Ⱥ�����Ϊroot-system */
	ret = (int)bbox_chown((const char __user *)path, ROOT_UID,
				SYSTEM_GID, false);
	if (ret) {
		BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		     __func__, path, ROOT_UID, SYSTEM_GID, ret);
	}
	set_fs(old_fs);
	BB_PRINT_END();
out2:
	return ret;
}

void rdr_save_cur_baseinfo(char *logpath)
{
	BB_PRINT_START();
	/* save pbb to fs */
	rdr_savebuf2fs(logpath, RDR_BIN, rdr_get_pbb(), rdr_get_pbb_size(), 0);

	BB_PRINT_END();
	return;
}

void rdr_save_last_baseinfo(char *logpath)
{
	BB_PRINT_START();
	/* save pbb to fs */
	rdr_savebuf2fs(logpath, RDX_BIN,
		       rdr_get_tmppbb(), rdr_get_pbb_size(), 0);

	BB_PRINT_END();
	return;
}

/*******************************************************************************
Function:       get_system_time
Description:    get_system_time
Input:          NA
Output:         NA
Return:         system_time
********************************************************************************/
static u64 get_system_time(void)
{
	struct timeval tv = {0};

	do_gettimeofday(&tv);

	return (u64)tv.tv_sec;
}

/*******************************************************************************
Function:       is_need_save_dfx2file
Description:    judge whether need save dfx to file
Input:          NA
Output:         NA
Return:         true:need
********************************************************************************/
bool is_need_save_dfx2file(void)
{
	char *buf;
	int ret, fd_dfx, cnt;
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	bool is_need_save_dfx2file = false;
	struct dfx_head_info *dfx_head_info;

	if (!check_himntn(HIMNTN_DFXPARTITION_TO_FILE)) {
		BB_PRINT_ERR("%s():%d:switch is close\n", __func__, __LINE__);
		goto out;
	}

	if (0 != rdr_wait_partition("/data/lost+found", 1000)) {
		BB_PRINT_ERR("%s():%d:data is not ready\n", __func__, __LINE__);
		goto out;
	}

	buf = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf) {
		BB_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		goto out;
	}

	ret = flash_find_ptn(PART_DFX, buf);
	if (ret != 0) {
		BB_PRINT_ERR("%s():%d:flash_find_ptn fail[%d]\n", __func__, __LINE__, ret);
		kfree(buf);
		goto out;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_dfx = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open %s fail[%d]\n", __func__, __LINE__, p_name, fd_dfx);
		kfree(buf);
		set_fs(oldfs);
		goto out;
	}

	memset(buf, 0, SZ_4K);
	cnt = sys_read(fd_dfx, buf, SZ_4K);
	if (cnt < 0) {
		BB_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}

	dfx_head_info = (struct dfx_head_info *)buf;
	if (DFX_MAGIC_NUMBER == dfx_head_info->magic &&
	    dfx_head_info->need_save_number > 0 &&
	    dfx_head_info->need_save_number <= TOTAL_NUMBER) {
		is_need_save_dfx2file = true;
	}

close:
	sys_close(fd_dfx);
	set_fs(oldfs);
	kfree(buf);
out:
	return is_need_save_dfx2file;
}

/*******************************************************************************
Function:       need_save_dfxbuffer2file
Description:    judge need_save_dfxbuffer2file
Input:          reboot_type, bootup_keypoint
Output:         NA
Return:         true:need save; false:not need save
********************************************************************************/
bool need_save_dfxbuffer2file(u64 reboot_type, u64 bootup_keypoint)
{
	if (BFM_S_BOOT_NATIVE_DATA_FAIL == reboot_type) {
		BB_PRINT_ERR("%s():%d:reboot_type is [0x%llx]\n",
			__func__, __LINE__, reboot_type);
		return true;
	}

	if ((bootup_keypoint < STAGE_XLOADER_START ||
		bootup_keypoint >= STAGE_FASTBOOT_END)
		&& (AP_S_PRESS6S != reboot_type)) {
		BB_PRINT_ERR("%s():%d:bootup_keypoint is [0x%llx]\n",
			__func__, __LINE__, bootup_keypoint);
		return false;
	}

	if ((REBOOT_REASON_LABEL1 <= reboot_type
	    && REBOOT_REASON_LABEL3 > reboot_type)
	    || MMC_S_EXCEPTION == reboot_type
	    || LPM3_S_EXCEPTION == reboot_type) {
		BB_PRINT_ERR("%s():%d:reboot_type is [0x%llx]\n",
			__func__, __LINE__, reboot_type);
		return false;
	}

	if (REBOOT_REASON_LABEL5 <= reboot_type
	    && REBOOT_REASON_LABEL6 > reboot_type) {
		BB_PRINT_ERR("%s():%d:reboot_type is [0x%llx]\n",
			__func__, __LINE__, reboot_type);
		return false;
	}

	if (REBOOT_REASON_LABEL8 <= reboot_type
	    && REBOOT_REASON_LABEL9 > reboot_type) {
		BB_PRINT_ERR("%s():%d:reboot_type is [0x%llx]\n",
			__func__, __LINE__, reboot_type);
		return false;
	}

	return true;
}

/*******************************************************************************
Function:       save_dfxbuffer_to_file
Description:    save dfx's ddr_buffer to file
Input:          dfx_head_info
Output:         NA
Return:         0:success
********************************************************************************/
static int save_dfxbuffer_to_file(struct dfx_head_info *dfx_head_info)
{
	char *buf;
	int last_number, fd;
	struct rdr_exception_info_s temp;
	struct every_number_info *every_number_info;
	char path[PATH_MAXLEN], date[DATATIME_MAXLEN];
	BB_PRINT_START();

	if (dfx_head_info->need_save_number > TOTAL_NUMBER) {
		BB_PRINT_ERR("need_save_number error %d\n", dfx_head_info->need_save_number);
		dfx_head_info->need_save_number = TOTAL_NUMBER;
	}

	memset(&temp, 0, sizeof(struct rdr_exception_info_s));
	last_number = (dfx_head_info->cur_number - dfx_head_info->need_save_number + TOTAL_NUMBER)%TOTAL_NUMBER;

	while (0 != dfx_head_info->need_save_number) {
		buf = (char *)dfx_head_info + dfx_head_info->every_number_addr[last_number];
		every_number_info = (struct every_number_info *)buf;

		if (!need_save_dfxbuffer2file(every_number_info->reboot_type,
				every_number_info->bootup_keypoint)) {
			dfx_head_info->need_save_number--;
			last_number = (last_number + 1 + TOTAL_NUMBER)%TOTAL_NUMBER;
			BB_PRINT_ERR("save_dfxbuffer_to_file continue here, dfx_head_info->need_save_number is %d\n", dfx_head_info->need_save_number);
			continue;
		}

		temp.e_from_core = RDR_AP;
		temp.e_reset_core_mask = RDR_AP;
		temp.e_exce_type = every_number_info->reboot_type;

		memset(path, 0, sizeof(path));
		memset(date, 0, sizeof(date));
		if (0 != bbox_create_dfxlog_path(&path[0], &date[0])) {
			BB_PRINT_ERR("bbox_create_dfxlog_path fail\n");
			return -1;
		}

		strncat(path, "/ap_log/", ((PATH_MAXLEN - 1) - strlen(path)));
		fd = sys_mkdir(path, DIR_LIMIT);
		if (fd < 0) {
			BB_PRINT_ERR(
			    "%s():%d:mkdir %s fail[%d]\n",
			    __func__, __LINE__, path, fd);
			return -1;
		}

		if (every_number_info->fastbootlog_size != 0) {
			rdr_savebuf2fs(path,
				"fastboot_log",
				(char *)every_number_info + every_number_info->fastbootlog_start_addr,
				every_number_info->fastbootlog_size,
				0);
		}

		if (every_number_info->last_kmsg_size != 0) {
			rdr_savebuf2fs(path,
				"last_kmsg",
				(char *)every_number_info + every_number_info->last_kmsg_start_addr,
				every_number_info->last_kmsg_size,
				0);
		}

		if (every_number_info->last_applog_size != 0) {
			rdr_savebuf2fs(path,
				"pmsg-ramoops-0",
				(char *)every_number_info + every_number_info->last_applog_start_addr,
				every_number_info->last_applog_size,
				0);
		}

		rdr_save_history_log(&temp, &date[0], true, every_number_info->bootup_keypoint);

		path[strlen(path) - strlen("/ap_log/")] = '\0';
		bbox_save_done(path, BBOX_SAVE_STEP_DONE);
		dfx_head_info->need_save_number--;
		last_number = (last_number + 1 + TOTAL_NUMBER)%TOTAL_NUMBER;
	}

	return 0;
}

/*******************************************************************************
Function:       save_dfxpartition_to_file
Description:    save dfx partition's log to file
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void save_dfxpartition_to_file(void)
{
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	void *buf, *dfx_buf, *dfx_buf_temp;
	int ret, fd_dfx, cnt, need_read_size;
	BB_PRINT_START();

	if (0 != rdr_wait_partition("/data/lost+found", 1000)) {
		BB_PRINT_ERR("%s():%d:data is not ready\n", __func__, __LINE__);
		return;
	}

	buf = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf) {
		BB_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		return;
	}

	dfx_buf = vmalloc(DFX_USED_SIZE);
	if (!dfx_buf) {
		BB_PRINT_ERR("%s():%d:vmalloc dfx_buf fail\n", __func__, __LINE__);
		kfree(buf);
		return;
	}

	ret = flash_find_ptn(PART_DFX, buf);
	if (ret != 0) {
		BB_PRINT_ERR(
		    "%s():%d:flash_find_ptn fail[%d]\n",
		    __func__, __LINE__, ret);
		kfree(buf);
		vfree(dfx_buf);
		return;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_dfx = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto out;
	}

	dfx_buf_temp = dfx_buf;
	need_read_size = DFX_USED_SIZE;
	memset((void *)dfx_buf_temp, 0, DFX_USED_SIZE);

	while (need_read_size > 0) {
		cnt = sys_read(fd_dfx, buf, SZ_4K);
		if (cnt < 0) {
			BB_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
			goto close;
		}

		memcpy((void *)dfx_buf_temp, (const void *)buf, cnt);
		dfx_buf_temp = dfx_buf_temp + cnt;
		need_read_size -= cnt;
	}

	sys_close(fd_dfx);

	ret = save_dfxbuffer_to_file((struct dfx_head_info *)dfx_buf);
	if (ret) {
		BB_PRINT_ERR(
		    "%s():%d:save_dfxbuffer_to_file fail[%d]\n",
		    __func__, __LINE__, ret);
		goto out;
	}

	fd_dfx = sys_open(p_name, O_WRONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto out;
	}

	cnt = sys_write(fd_dfx, (void *)dfx_buf, SZ_4K);
	if (cnt <= 0) {
		BB_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}

close:
	sys_close(fd_dfx);
out:
	set_fs(oldfs);
	vfree(dfx_buf);
	kfree(buf);
	return;
}

/*******************************************************************************
Function:       save_buffer_to_dfx_loopbuffer
Description:    write input arg to dfx_partition's loopbuffer
Input:          every_number_info:the data that need to write
Output:         NA
Return:         NA
********************************************************************************/
static void save_buffer_to_dfx_loopbuffer(struct every_number_info *every_number_info)
{
	void *buf1, *buf2;
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	struct dfx_head_info *dfx_head_info;
	int ret, fd_dfx, cnt, cfo, need_write_size;
	BB_PRINT_START();

	buf1 = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf1) {
		BB_PRINT_ERR("%s():%d:kmalloc buf1 fail\n", __func__, __LINE__);
		return;
	}

	ret = flash_find_ptn(PART_DFX, buf1);
	if (0 != ret) {
		BB_PRINT_ERR("%s():%d:flash_find_ptn fail\n", __func__, __LINE__);
		kfree(buf1);
		return;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf1, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	kfree(buf1);
	buf1 = kmalloc((unsigned long)DFX_HEAD_SIZE, GFP_KERNEL);
	if (!buf1) {
		BB_PRINT_ERR("%s():%d:kmalloc buf1 fail\n", __func__, __LINE__);
		return;
	}
	memset(buf1, 0, DFX_HEAD_SIZE);
	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_dfx = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto open_fail;
	}

	cnt = sys_read(fd_dfx, buf1, DFX_HEAD_SIZE);
	if (cnt < 0) {
		BB_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}

	sys_close(fd_dfx);

	fd_dfx = sys_open(p_name, O_WRONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto open_fail;
	}

	dfx_head_info = (struct dfx_head_info *)buf1;
	cfo = dfx_head_info->every_number_addr[dfx_head_info->cur_number];
	ret = sys_lseek(fd_dfx, cfo, SEEK_SET);
	if (ret != cfo) {
		BB_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}

	buf2 = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf2) {
		BB_PRINT_ERR("%s():%d:kmalloc buf2 fail\n", __func__, __LINE__);
		goto close;
	}

	memset(buf2, 0, SZ_4K);
	need_write_size = EVERY_NUMBER_SIZE;
	while (need_write_size > 0) {
		memcpy(buf2, every_number_info, SZ_4K);
		cnt = sys_write(fd_dfx, buf2, SZ_4K);
		if (cnt <= 0) {
			BB_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
			kfree(buf2);
			goto close;
		}
		need_write_size -= cnt;
		every_number_info =
		    (struct every_number_info *)((char *)every_number_info + SZ_4K);
	}

	ret = sys_lseek(fd_dfx, 0, SEEK_SET);
	if (ret != 0) {
		BB_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		kfree(buf2);
		goto close;
	}

	dfx_head_info->need_save_number++;
	if (dfx_head_info->need_save_number > TOTAL_NUMBER)
		dfx_head_info->need_save_number = TOTAL_NUMBER;
	dfx_head_info->cur_number = (dfx_head_info->cur_number+1)%TOTAL_NUMBER;
	cnt = sys_write(fd_dfx, buf1, DFX_HEAD_SIZE);
	if (cnt <= 0) {
		BB_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
		kfree(buf2);
		goto close;
	}
	kfree(buf2);

close:
	sys_fsync(fd_dfx);
	sys_close(fd_dfx);
open_fail:
	set_fs(oldfs);
	kfree(buf1);
	return;
}

/*******************************************************************************
Function:       systemerror_save_log2dfx
Description:    save log to dfx partition when bbox_system_error is called
Input:          reboot_type
Output:         NA
Return:         NA
********************************************************************************/
void systemerror_save_log2dfx(u32 reboot_type)
{
	void *buf, *fastbootlog_addr, *pstore_addr, *last_kmsg_addr, *last_applog_addr;
	struct every_number_info *every_number_info;
	BB_PRINT_START();

	if (in_atomic() || irqs_disabled() || in_irq()) {
		BB_PRINT_ERR(
		    "%s():%d:unsupport in atomic or irqs disabled or in irq\n",
		    __func__, __LINE__);
		return;
	}

	buf = vmalloc(EVERY_NUMBER_SIZE);
	if (!buf) {
		BB_PRINT_ERR("%s():%d:vmalloc buf fail\n", __func__, __LINE__);
		return;
	}

	fastbootlog_addr = ioremap_wc(HISI_SUB_RESERVED_FASTBOOT_LOG_PYHMEM_BASE,
		HISI_SUB_RESERVED_FASTBOOT_LOG_PYHMEM_SIZE);
	if (!fastbootlog_addr) {
		BB_PRINT_ERR("%s():%d:ioremap_wc fastbootlog_addr fail\n", __func__, __LINE__);
		vfree(buf);
		return;
	}

	pstore_addr = bbox_vmap(HISI_RESERVED_PSTORE_PHYMEM_BASE,
		HISI_RESERVED_PSTORE_PHYMEM_SIZE);
	if (!pstore_addr) {
		BB_PRINT_ERR("%s():%d:bbox_vmap pstore_addr fail\n", __func__, __LINE__);
		vfree(buf);
		iounmap(fastbootlog_addr);
		return;
	}

	last_applog_addr = pstore_addr +
		HISI_RESERVED_PSTORE_PHYMEM_SIZE -
		LAST_APPLOG_SIZE;
	last_kmsg_addr = last_applog_addr - LAST_KMSG_SIZE;

	memset(buf, 0, EVERY_NUMBER_SIZE);
	every_number_info = (struct every_number_info *)buf;
	every_number_info->rtc_time = get_system_time();
	every_number_info->bootup_keypoint = get_boot_keypoint();
	every_number_info->reboot_type = reboot_type;
	every_number_info->fastbootlog_start_addr = DFX_HEAD_SIZE;
	every_number_info->fastbootlog_size = FASTBOOTLOG_SIZE;
	every_number_info->last_kmsg_start_addr = every_number_info->fastbootlog_start_addr + FASTBOOTLOG_SIZE;
	every_number_info->last_kmsg_size = 0;
	every_number_info->last_applog_start_addr = every_number_info->last_kmsg_start_addr + LAST_KMSG_SIZE;
	every_number_info->last_applog_size = 0;

	memcpy((char *)every_number_info + every_number_info->fastbootlog_start_addr,
	       fastbootlog_addr,
	       every_number_info->fastbootlog_size);

	if (0 != readl(last_kmsg_addr+4)) {
		every_number_info->last_kmsg_size = LAST_KMSG_SIZE;
		memcpy((char *)every_number_info + every_number_info->last_kmsg_start_addr,
		       last_kmsg_addr,
		       every_number_info->last_kmsg_size);
	}

	if (0 != readl(last_applog_addr+4)) {
		every_number_info->last_applog_size = LAST_APPLOG_SIZE;
		memcpy((char *)every_number_info + every_number_info->last_applog_start_addr,
		       last_applog_addr,
		       every_number_info->last_applog_size);
	}

	save_buffer_to_dfx_loopbuffer(every_number_info);

	vfree(buf);
	iounmap(fastbootlog_addr);
	vunmap(pstore_addr);
	return;
}

/*******************************************************************************
Function:       save_buffer_to_dfx_tempbuffer
Description:    write input arg to dfx_partition's tempbuffer
Input:          every_number_info:the data that need to write
Output:         NA
Return:         NA
********************************************************************************/
static void save_buffer_to_dfx_tempbuffer(struct every_number_info *every_number_info)
{
	void *buf;
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	struct dfx_head_info *dfx_head_info;
	int ret, fd_dfx, cnt, cfo, need_write_size;

	if (0 != rdr_wait_partition("/data/lost+found", 1000)) {
		BB_PRINT_ERR("%s():%d:data is not ready\n", __func__, __LINE__);
		return;
	}

	buf = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf) {
		BB_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		return;
	}

	ret = flash_find_ptn(PART_DFX, buf);
	if (0 != ret) {
		BB_PRINT_ERR("%s():%d:flash_find_ptn fail\n", __func__, __LINE__);
		kfree(buf);
		return;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_dfx = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto open_fail;
	}

	memset(buf, 0, SZ_4K);
	cnt = sys_read(fd_dfx, buf, SZ_4K);
	if (cnt < 0) {
		BB_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}

	sys_close(fd_dfx);

	fd_dfx = sys_open(p_name, O_WRONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BB_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto open_fail;
	}

	dfx_head_info = (struct dfx_head_info *)buf;

	if (DFX_MAGIC_NUMBER != dfx_head_info->magic) {
		BB_PRINT_ERR("%s():%d:magic error\n", __func__, __LINE__);
		goto close;
	}

	cfo = dfx_head_info->temp_number_addr;
	ret = sys_lseek(fd_dfx, cfo, SEEK_SET);
	if (ret != cfo) {
		BB_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}

	memset(buf, 0, SZ_4K);
	need_write_size = EVERY_NUMBER_SIZE;
	while (need_write_size > 0) {
		memcpy(buf, every_number_info, SZ_4K);
		cnt = sys_write(fd_dfx, buf, SZ_4K);
		if (cnt <= 0) {
			BB_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
			goto close;
		}
		need_write_size -= cnt;
		every_number_info =
		    (struct every_number_info *)((char *)every_number_info + SZ_4K);
	}

close:
	sys_close(fd_dfx);
open_fail:
	set_fs(oldfs);
	kfree(buf);
	return;
}

/*******************************************************************************
Function:       save_log_to_dfx_tempbuffer
Description:    save log to the tempbuffer of dfx partition
Input:          reboot_type
Output:         NA
Return:         NA
********************************************************************************/
void save_log_to_dfx_tempbuffer(u32 reboot_type)
{
	void *buf, *fastbootlog_addr, *pstore_addr, *last_kmsg_addr, *last_applog_addr;
	struct every_number_info *every_number_info;

	buf = vmalloc(EVERY_NUMBER_SIZE);
	if (!buf) {
		BB_PRINT_ERR("%s():%d:vmalloc buf fail\n", __func__, __LINE__);
		return;
	}

	fastbootlog_addr = ioremap_wc(HISI_SUB_RESERVED_FASTBOOT_LOG_PYHMEM_BASE,
		HISI_SUB_RESERVED_FASTBOOT_LOG_PYHMEM_SIZE);
	if (!fastbootlog_addr) {
		BB_PRINT_ERR("%s():%d:ioremap_wc fastbootlog_addr fail\n", __func__, __LINE__);
		vfree(buf);
		return;
	}

	pstore_addr = bbox_vmap(HISI_RESERVED_PSTORE_PHYMEM_BASE,
		HISI_RESERVED_PSTORE_PHYMEM_SIZE);
	if (!pstore_addr) {
		BB_PRINT_ERR("%s():%d:bbox_vmap pstore_addr fail\n", __func__, __LINE__);
		vfree(buf);
		iounmap(fastbootlog_addr);
		return;
	}

	last_applog_addr = pstore_addr +
		HISI_RESERVED_PSTORE_PHYMEM_SIZE -
		LAST_APPLOG_SIZE;
	last_kmsg_addr = last_applog_addr - LAST_KMSG_SIZE;

	memset(buf, 0, EVERY_NUMBER_SIZE);
	every_number_info = (struct every_number_info *)buf;
	every_number_info->rtc_time = get_system_time();
	every_number_info->bootup_keypoint = get_boot_keypoint();
	every_number_info->reboot_type = reboot_type;
	every_number_info->fastbootlog_start_addr = DFX_HEAD_SIZE;
	every_number_info->fastbootlog_size = FASTBOOTLOG_SIZE;
	every_number_info->last_kmsg_start_addr = every_number_info->fastbootlog_start_addr + FASTBOOTLOG_SIZE;
	every_number_info->last_kmsg_size = 0;
	every_number_info->last_applog_start_addr = every_number_info->last_kmsg_start_addr + LAST_KMSG_SIZE;
	every_number_info->last_applog_size = 0;

	memcpy((char *)every_number_info + every_number_info->fastbootlog_start_addr,
	       fastbootlog_addr,
	       every_number_info->fastbootlog_size);

	if (0 != readl(last_kmsg_addr+4)) {
		every_number_info->last_kmsg_size = LAST_KMSG_SIZE;
		memcpy((char *)every_number_info + every_number_info->last_kmsg_start_addr,
		       last_kmsg_addr,
		       every_number_info->last_kmsg_size);
	}

	if (0 != readl(last_applog_addr+4)) {
		every_number_info->last_applog_size = LAST_APPLOG_SIZE;
		memcpy((char *)every_number_info + every_number_info->last_applog_start_addr,
		       last_applog_addr,
		       every_number_info->last_applog_size);
	}

	save_buffer_to_dfx_tempbuffer(every_number_info);

	vfree(buf);
	iounmap(fastbootlog_addr);
	vunmap(pstore_addr);
	return;
}

/*******************************************************************************
Function:       clear_dfx_tempbuffer
Description:    clear the tempbuffer of dfx partition
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void clear_dfx_tempbuffer(void)
{
	void *buf;

	buf = vmalloc(EVERY_NUMBER_SIZE);
	if (!buf) {
		BB_PRINT_ERR("%s():%d:vmalloc buf fail\n", __func__, __LINE__);
		return;
	}
	memset(buf, 0, EVERY_NUMBER_SIZE);
	save_buffer_to_dfx_tempbuffer((struct every_number_info *)buf);

	vfree(buf);
	return;
}

