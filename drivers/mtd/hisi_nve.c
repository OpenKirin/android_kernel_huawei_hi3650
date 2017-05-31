/*
 * FileName: kernel/drivers/mtd/nve.c
 * Description: complement NV partition(or called block) read and write
 * in kernel.
 * Copyright (C) Hisilicon technologies Co., Ltd All rights reserved.
 * Revision history:
 */

#include <linux/device.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/random.h>
/* #include <linux/mtd/mtd.h> */
#include <linux/uaccess.h>
#include <linux/semaphore.h>
#include <linux/compat.h>

#include <linux/mtd/hisi_nve_interface.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include "hisi_nve.h"

static struct semaphore nv_sem;
static struct class *nve_class;
static struct NVE_struct *my_nve = NULL;
static int hisi_nv_setup_ok = 0;
static int hisi_init_nv_ok = 0;
static char *nve_block_device_name = NULL;
static char log_nv_info[NV_INFO_LEN];
static char temp_nv_info[NV_INFO_LEN];

/*
 * Function name:nve_increment.
 * Discription:complement NV block' increment automatically, when current block
 * has been writeen, block index will pointer to next block, and if current
 * block
 * is maximum block count ,then block index will be assigned "1", ensuring all
 * of
 * NV block will be used and written circularly.
 */
static void nve_increment(struct NVE_struct *nve)
{
	if (nve->nve_current_id >= nve->nve_partition_count - 1)
		nve->nve_current_id = 1;
	else
		nve->nve_current_id++;

	return;
}

/*
 * Function name:nve_read.
 * Discription:read NV partition.
 * Parameters:
 *          @ mtd:struct mtd_info pointer.
 *          @ from:emmc start block number that will be read.
 *          @ len:total bytes that will be read from emmc.
 *          @ buf:buffer used to store bytes that is read from emmc.
 */
static int nve_read(loff_t from, size_t len, u_char *buf)
{
	int ret;
	int fd;
	mm_segment_t oldfs = get_fs();
	/*lint -e501*/
	set_fs(get_ds());
	/*lint +e501*/
	fd = (int)sys_open(nve_block_device_name, O_RDONLY,
		      (int)S_IRWXU | S_IRWXG | S_IRWXO);

	if (fd < 0) {
		printk(KERN_ERR
		       "[NVE][%s]open nv block device failed, and fd = %x!\n",
		       __func__, fd);
		ret = -ENODEV;
		goto out;
	}

	ret = (int)sys_lseek((unsigned int)fd, from, SEEK_SET);
	if (ret == -1) {
		printk(KERN_ERR "[NVE][%s] Fatal seek error, read flash from = "
				"0x%llx, len = 0x%zx, ret = 0x%x.\n",
		       __func__, from, len, ret);
		ret = -EIO;
		goto out;
	}

	ret = (int)sys_read((unsigned int)fd, (char *)buf, len);
	if (ret == -1) {
		printk(KERN_ERR "[NVE][%s] Fatal read error, read flash from = "
				"0x%llx, len = 0x%zx, ret = 0x%x.\n",
		       __func__, from, len, ret);
		ret = -EIO;
		goto out;
	}

	sys_close((unsigned int)fd);

	set_fs(oldfs);

	return 0;

out:
	if (fd >= 0) {
		sys_close((unsigned int)fd);
	}
	set_fs(oldfs);
	return ret;
}

/*
 * Function name:nve_write.
 * Discription:write NV partition.
 * Parameters:
 *          @ mtd:struct mtd_info pointer.
 *          @ from:emmc start block number that will be written.
 *          @ len:total bytes that will be written from emmc.
 *          @ buf:given buffer whose bytes will be written to emmc.
 */
static int nve_write(loff_t from, size_t len, u_char *buf)
{
	int ret;
	int fd;
	mm_segment_t oldfs = get_fs();
	/*lint -e501*/
	set_fs(get_ds());
	/*lint +e501*/
	fd = (int)sys_open(nve_block_device_name, O_RDWR,
		      (int)S_IRWXU | S_IRWXG | S_IRWXO);

	if (fd < 0) {
		printk(KERN_ERR
		       "[NVE][%s]open nv block device failed, and fd = %x!\n",
		       __func__, fd);
		ret = -ENODEV;
		goto out;
	}

	ret = (int)sys_lseek((unsigned int)fd, from, SEEK_SET);
	if (ret == -1) {
		printk(KERN_ERR "[NVE][%s] Fatal seek error, read flash from = "
				"0x%llx, len = 0x%zx, ret = 0x%x.\n",
		       __func__, from, len, ret);
		ret = -EIO;
		goto out;
	}

	ret = (int)sys_write((unsigned int)fd, (char *)buf, len);
	if (ret == -1) {
		printk(KERN_ERR "[NVE][%s] Fatal write error, read flash from "
				"= 0x%llx, len = 0x%zx, ret = 0x%x.\n",
		       __func__, from, len, ret);
		ret = -EIO;
		goto out;
	}

	ret = (int)sys_fsync((unsigned int)fd);
	if (ret < 0) {
		printk(KERN_ERR "[NVE][%s] Fatal sync error, read flash from = "
				"0x%llx, len = 0x%zx, ret = 0x%x.\n",
		       __func__, from, len, ret);
		ret = -EIO;
		goto out;
	}
	sys_close((unsigned int)fd);

	set_fs(oldfs);
	return 0;
out:
	if (fd >= 0) {
		sys_close((unsigned int)fd);
	}
	set_fs(oldfs);
	return ret;
}

/*
 * Function name:nve_check_partition.
 * Discription:check current NV partition is valid partition or not by means of
 * comparing current partition's name to NVE_HEADER_NAME.
 * Parameters:
 *          @ nve:struct NVE_struct pointer.
 *          @ index:indicates current NV partion that will be checked.
 * return value:
 *          @ 0 - current parition is valid.
 *          @ others - current parition is invalid.
 */
static int nve_check_partition(struct NVE_struct *nve, uint32_t index)
{
	int ret;
	/*lint -e826*/
	struct NVE_partition_header *nve_header =
		(struct NVE_partition_header *)(nve->nve_ramdisk +
						PARTITION_HEADER_OFFSET);
	/*lint +e826*/
	ret = nve_read((loff_t)index * NVE_PARTITION_SIZE, (size_t)NVE_PARTITION_SIZE,
		       nve->nve_ramdisk);
	if (ret) {
		printk(KERN_ERR "[NVE][%s]nve_read error in line %d!\n",
		       __func__, __LINE__);
		return ret;
	}

	printk(KERN_INFO "nve_header->nve_partition_name %s  compare = %s\n",
	       nve_header->nve_partition_name, NVE_HEADER_NAME);
	/*compare nve_partition_name with const name to decide current partition
	 * is valid or not*/
	ret = strncmp(NVE_HEADER_NAME, nve_header->nve_partition_name,
		      strlen(NVE_HEADER_NAME));
	return ret;
}

/*
 * Function name:nve_find_valid_partition.
 * Discription:find valid NV partition in terms of checking every
 * partition circularly. when two or more NV paritions are both valid,
 * nve_age will be used to indicates which one is really valid, i.e. the
 * partition whose age is the biggest is valid partition.
 */
static void nve_find_valid_partition(struct NVE_struct *nve)
{
	uint32_t i;
	uint32_t age_temp = 0;
	int partition_valid = 0;
	/*lint -e826*/
	struct NVE_partition_header *nve_header =
		(struct NVE_partition_header *)(nve->nve_ramdisk +
						PARTITION_HEADER_OFFSET);
	/*lint +e826*/
	for (i = 1; i < nve->nve_partition_count; i++) {
		partition_valid = nve_check_partition(nve, i);

		printk(KERN_INFO "partition_valid =%d\n", partition_valid);
		if (partition_valid)
			continue;

		printk(KERN_INFO "nve = %d age_temp = %d\n", partition_valid, age_temp);
		if (nve_header->nve_age > age_temp) {
			nve->nve_current_id = i;
			age_temp = nve_header->nve_age;
		}
	}

	printk(KERN_INFO "[NVE][%s]current_id = %d.\n", __func__,
	       nve->nve_current_id);

	return;
}

/*
 * Function name:nve_restore.
 * Discription:NV is divided into 8 partitions(partition0 - parititon 7),
 * when we need to add new NV items, we should update partition0 first,
 * and then restore parition0 to current valid partition which shall be
 * one of partition0 - partition7.
 * Parameters:
 *          @ 0  - success
 *          @ -1 - failure
 */
static int nve_restore(struct NVE_struct *nve)
{
	int ret;
	uint32_t i;
	uint32_t valid_items;
	uint32_t id = nve->nve_current_id;
	u_char *nve_ramdisk_temp;
	struct NVE_partition_header *nve_header;
	struct NVE_partition_header *nve_header_temp;
	struct NV_struct *nv;
	struct NV_struct *nv_temp;

	nve_ramdisk_temp =
		(u_char *)kzalloc((size_t)NVE_PARTITION_SIZE, GFP_KERNEL);
	if (NULL == nve_ramdisk_temp) {
		printk(KERN_ERR "[NVE][%s]failed to allocate ramdisk "
					"temp buffer.\n",
			       __func__);
		return -EFAULT;
	}
	if (NVE_INVALID_NVM == id) {
		if (nve_read((loff_t)0, (size_t)NVE_PARTITION_SIZE,
			     (u_char *)nve->nve_ramdisk)) {
			printk(KERN_ERR
			       "[NVE][%s] nve read error in line [%d].\n",
			       __func__, __LINE__);
			kfree(nve_ramdisk_temp);
			return -ENODEV;
		}
		id = 1;
	} else {
			if (nve_read((loff_t)id * NVE_PARTITION_SIZE,
				     (size_t)NVE_PARTITION_SIZE,
				     (u_char *)nve->nve_ramdisk)) {
				printk(KERN_ERR "[NVE][%s] nve read error in "
						"line [%d].\n",
				       __func__, __LINE__);
				kfree(nve_ramdisk_temp);
				return -EFAULT;
			}

			if (nve_read((loff_t)0, (size_t)NVE_PARTITION_SIZE,
				     (u_char *)nve_ramdisk_temp)) {
				printk(KERN_ERR "[NVE][%s] nve read error in "
						"line [%d].\n",
				       __func__, __LINE__);
				kfree(nve_ramdisk_temp);
				return -EFAULT;
			}
			/*lint -e826*/
			nve_header = (struct NVE_partition_header
					      *)(nve->nve_ramdisk +
						 PARTITION_HEADER_OFFSET);
			nve_header_temp = (struct NVE_partition_header
						   *)(nve_ramdisk_temp +
						      PARTITION_HEADER_OFFSET);

			nv = (struct NV_struct *)nve->nve_ramdisk;
			nv_temp = (struct NV_struct *)nve_ramdisk_temp;
			/*lint +e826*/
			valid_items = min(nve_header->valid_items,
					  nve_header_temp->valid_items);

			for (i = 0; i < valid_items; i++, nv++, nv_temp++) {
				/*skip non-volatile NV item*/
				if (nv->nv_header.nv_property)
					continue;

				memcpy((void *)nv, (void *)nv_temp,
				       sizeof(struct NV_struct));
			}

			/* new added item need not check nv_property, copy
			 * directly */
			if (nve_header_temp->valid_items >
			    nve_header->valid_items) {
				memcpy((void *)nv, (void *)nv_temp,
				       sizeof(struct NV_struct) *
					       (nve_header_temp->valid_items -
						nve_header->valid_items));
				nve_header->valid_items =
					nve_header_temp->valid_items;
			}

			nve_header->nve_age++;
			nve_header->nve_version = nve_header_temp->nve_version;

		if (id == nve->nve_partition_count - 1)
			id = 1;
		else
			id++;
	}

	ret = nve_write((loff_t)id * NVE_PARTITION_SIZE, (size_t)NVE_PARTITION_SIZE,
			(u_char *)nve->nve_ramdisk);

	if (ret) {
		kfree(nve_ramdisk_temp);
		printk(KERN_ERR "[NVE][%s]nve_write error in line %d!\n",
		       __func__, __LINE__);
		return ret;
	}

	memset(nve_ramdisk_temp, 0, (size_t)(1 << PAGE_SHIFT));
	/*ensure write success,then erase partition 0*/
	nve_write((loff_t)(NVE_PARTITION_SIZE - (1 << PAGE_SHIFT)), (size_t)(1 << PAGE_SHIFT),
		  nve_ramdisk_temp);

	memset(nve_ramdisk_temp, 0, (size_t)(NVE_PARTITION_SIZE - (1 << PAGE_SHIFT)));
	nve_write((loff_t)0, (size_t)(NVE_PARTITION_SIZE - (1 << PAGE_SHIFT)), nve_ramdisk_temp);
	nve_increment(nve);

	kfree(nve_ramdisk_temp);
	return ret;
}
/*
 * Function name:nve_do_index_table.
 * Discription:create NV index table. Once NV index table has been created, we
 * can
 * visit NV items by means of this nv_index_table conveniently.
 * Parameters:
 *          @ nve:struct NVE_struct pointer.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static int nve_do_index_table(struct NVE_struct *nve)
{
	u_char *p_nv;
	unsigned int i;
	unsigned int nv_offset;
	unsigned int nv_offset_next;
	struct NVE_index *nv_index;
	struct NV_header *nv;
	/*lint -e826*/
	struct NVE_partition_header *nve_header =
		(struct NVE_partition_header *)(nve->nve_ramdisk +
						PARTITION_HEADER_OFFSET);
	/*lint +e826*/
	if (nve_read((loff_t)nve->nve_current_id * NVE_PARTITION_SIZE,
		     (size_t)NVE_PARTITION_SIZE, (u_char *)nve->nve_ramdisk)) {
		printk(KERN_ERR "[NVE][%s] nve read error in line [%d]!\n",
		       __func__, __LINE__);
		return -ENODEV;
	}

	printk(KERN_DEBUG "[NVE]Original valid_items: 0x%x.\n",
	       nve_header->valid_items);

	if (NULL != nve->nve_index_table) {
		kfree(nve->nve_index_table);
		nve->nve_index_table = NULL;
	}
	nve->nve_index_table = kzalloc(
		nve_header->valid_items * sizeof(struct NVE_index), GFP_KERNEL);

	if (NULL == nve->nve_index_table) {
		printk(KERN_ERR "[NVE] nve_do_index_table failed to allocate "
				"index table.\n");
		return -ENOMEM;
	}

	nv_offset = 0;
	for (i = 0; i < nve_header->valid_items; i++) {
		nv_offset_next = nv_offset + sizeof(struct NV_header);

		/*override, the end.Last 128 bytes is reserverd for
		 * nve_partition_header.*/
		if (nv_offset_next > NVE_PARTITION_SIZE - PARTITION_HEADER_SIZE)
			break;

		p_nv = nve->nve_ramdisk + nv_offset;
		/*lint -e826*/
		nv = (struct NV_header *)p_nv;
		/*lint +e826*/
		if (i != nv->nv_number)
			/*invalid nv, the end*/
			break;

		nv_offset_next += NVE_NV_DATA_SIZE;
		/*override, the end.Last 128 bytes is reserverd for
		 * nve_partition_header.*/
		if (nv_offset_next > NVE_PARTITION_SIZE - PARTITION_HEADER_SIZE)
			break;

		nv_index = nve->nve_index_table + i;
		nv_index->nv_offset = nv_offset;
		nv_index->nv_size = nv->valid_size;
		memcpy(nv_index->nv_name, nv->nv_name, (size_t)NV_NAME_LENGTH);

		nv_offset = nv_offset_next;
	}
	nve_header->valid_items = i;

	printk(KERN_DEBUG "[NVE]Actual valid_items: 0x%x.\n",
	       nve_header->valid_items);

	return 0;
}

/* test NV items in kernel. if you want to use this, please set macro
 * TEST_NV_IN_KERNEL to "1".
 */
#if TEST_NV_IN_KERNEL
#define NVE_TEST_TIMES 20
#define NVE_TEST_STRESS_TIMES 50
#define NVE_TEST_WRITE_VALUE "test_data"
#define NVE_TEST_VALID_SIZE sizeof(NVE_TEST_WRITE_VALUE)
#define NVE_TEST_OK 0
#define NVE_TEST_ERR 1
extern u64 hisi_getcurtime(void);
uint64_t g_nve_write_start_time;
uint64_t g_nve_write_end_time;
uint64_t g_nve_read_start_time;
uint64_t g_nve_read_end_time;
uint64_t g_nve_cost_time;
struct hisi_nve_info_user nv_read_info;
struct hisi_nve_info_user nv_write_info;
struct hisi_nve_info_user nv_init_info;
static int nve_print_test(struct NVE_struct *nve)
{
	struct NVE_partition_header *nve_header;
	struct NV_struct *nv;
	uint32_t valid_items;
	uint32_t i;
	/*lint -e826*/
	nve_header = (struct NVE_partition_header *)(nve->nve_ramdisk +
						     PARTITION_HEADER_OFFSET);
	nv = (struct NV_struct *)nve->nve_ramdisk;
	/*lint +e826*/
	valid_items = nve_header->valid_items;

	printk(KERN_ERR "[NVE] testnve: version %d.\n",
	       nve_header->nve_version);
	printk(KERN_ERR "[NVE] testnve: age %d.\n", nve_header->nve_age);
	printk(KERN_ERR "[NVE] testnve: valid_items %d.\n", valid_items);

	for (i = 0; i < valid_items; i++) {
		printk(KERN_ERR
		       "[NVE] testnve: number %d, name %s, NV %d, size %d.\n",
		       nv->nv_header.nv_number, nv->nv_header.nv_name,
		       nv->nv_header.nv_property, nv->nv_header.valid_size);
		printk(KERN_ERR "[NVE] testnve: data %s. \n\n", nv->nv_data);
		nv++;
	}

	return 0;
}

int nve_write_test(uint32_t nv_item_num)
{
	int ret;
	unsigned char *data = (unsigned char *)NVE_TEST_WRITE_VALUE;
	memset(&nv_write_info, 0, sizeof(nv_write_info));
	strncpy(nv_write_info.nv_name, "NVTEST", (sizeof("NVTEST") - 1));
	nv_write_info.nv_name[sizeof("NVTEST") - 1] = '\0';

	nv_write_info.nv_number = nv_item_num;

	nv_write_info.valid_size = NVE_TEST_VALID_SIZE;
	nv_write_info.nv_operation = NV_WRITE;
	memset(nv_write_info.nv_data, 0x0, (size_t)NVE_NV_DATA_SIZE);
	memcpy(nv_write_info.nv_data, data, (size_t)nv_write_info.valid_size);

	ret = hisi_nve_direct_access(&nv_write_info);
	if (ret == 0) {
		printk(KERN_ERR
		       "test nv write 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x success!\n",
		       nv_write_info.nv_data[0], nv_write_info.nv_data[1],
		       nv_write_info.nv_data[2], nv_write_info.nv_data[3],
		       nv_write_info.nv_data[4], nv_write_info.nv_data[5]);
		return NVE_TEST_OK;
	} else {
		printk(KERN_ERR "test nv write faild!\n");
		return NVE_TEST_ERR;
	}
}
EXPORT_SYMBOL(nve_write_test);

int nve_read_init_value(uint32_t nv_item_num){
	int ret;
	memset(&nv_init_info, 0, sizeof(nv_init_info));
	strncpy(nv_init_info.nv_name, "NVTEST", (sizeof("NVTEST") - 1));
	nv_init_info.nv_name[sizeof("NVTEST") - 1] = '\0';
	nv_init_info.nv_number = nv_item_num;
	nv_init_info.valid_size = 0;
	nv_init_info.nv_operation = NV_READ;

	ret = hisi_nve_direct_access(&nv_init_info);
	if (ret == 0) {
		printk(KERN_ERR
		       "test nv read 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x success!\n",
		       nv_init_info.nv_data[0], nv_init_info.nv_data[1],
		       nv_init_info.nv_data[2], nv_init_info.nv_data[3],
		       nv_init_info.nv_data[4], nv_init_info.nv_data[5]);
		printk(KERN_ERR "test nv read value:%s!\n", nv_init_info.nv_data);
		return NVE_TEST_OK;
	} else {
		printk(KERN_ERR "test nv read faild!\n");
		return NVE_TEST_ERR;
	}
}

int nve_write_init_value(void){
	int ret;
	nv_init_info.nv_operation = NV_WRITE;
	ret = hisi_nve_direct_access(&nv_init_info);
	if (ret == 0) {
		printk(KERN_ERR
		       "test nv write 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x success!\n",
		       nv_init_info.nv_data[0], nv_init_info.nv_data[1],
		       nv_init_info.nv_data[2], nv_init_info.nv_data[3],
		       nv_init_info.nv_data[4], nv_init_info.nv_data[5]);
		return NVE_TEST_OK;
	} else {
		printk(KERN_ERR "test nv write faild!\n");
		return NVE_TEST_ERR;
	}
}


int nve_read_test(uint32_t nv_item_num)
{
	int ret;
	memset(&nv_read_info, 0, sizeof(nv_read_info));
	strncpy(nv_read_info.nv_name, "NVTEST", (sizeof("NVTEST") - 1));
	nv_read_info.nv_name[sizeof("NVTEST") - 1] = '\0';
	nv_read_info.nv_number = nv_item_num;
	nv_read_info.valid_size = NVE_TEST_VALID_SIZE;
	nv_read_info.nv_operation = NV_READ;

	ret = hisi_nve_direct_access(&nv_read_info);
	if (ret == 0) {
		printk(KERN_ERR
		       "test nv read 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x success!\n",
		       nv_read_info.nv_data[0], nv_read_info.nv_data[1],
		       nv_read_info.nv_data[2], nv_read_info.nv_data[3],
		       nv_read_info.nv_data[4], nv_read_info.nv_data[5]);
		printk(KERN_ERR "test nv read value:%s!\n", nv_read_info.nv_data);
		return NVE_TEST_OK;
	} else {
		printk(KERN_ERR "test nv read faild!\n");
		return NVE_TEST_ERR;
	}
}
EXPORT_SYMBOL(nve_read_test);

int nve_read_write_auto(uint32_t nv_item_num)
{
	int i;
	int ret;
	ret = nve_read_init_value(nv_item_num);
	if(ret){
		printk(KERN_ERR "nve_read_init_value test failed!\n");
		return ret;
	}
	for (i = 0; i < NVE_TEST_TIMES; i++) {
		ret = nve_write_test(nv_item_num);
		if(ret){
			printk(KERN_ERR "nve_write_test test failed!\n");
			return ret;
		}
		ret = nve_read_test(nv_item_num);
		if(ret){
			printk(KERN_ERR "nve_read_test test failed!\n");
			return ret;
		}
		if (strncmp((const char*)nv_read_info.nv_data, (const char*)nv_write_info.nv_data,
			    (size_t)NVE_TEST_VALID_SIZE) == 0){
			printk(KERN_ERR "test nve write and read value is same, test "
			       "successed!\n");
		}else{
			printk(KERN_ERR "test nve write and read value is not same, "
			       "test failed!\n");
			return NVE_TEST_ERR;
		}
	}
	ret = nve_write_init_value();
	if(ret){
		printk(KERN_ERR "nve_write_init_value test failed!\n");
		return ret;
	}
	printk(KERN_ERR "test nve auto end!\n");
	return ret;
}

EXPORT_SYMBOL(nve_read_write_auto);

uint64_t nve_write_time_test(uint32_t nv_item_num)
{
	uint64_t total_nve_write_time = 0;
	uint64_t average_nve_write_time;
	int i;
	int ret;
	ret = nve_read_init_value(nv_item_num);
	if(ret){
		printk(KERN_ERR "nve_read_init_value test failed!\n");
		return NVE_TEST_ERR;
	}
	for(i = 0;i < NVE_TEST_STRESS_TIMES;i++){
		g_nve_write_start_time = hisi_getcurtime();
		ret = nve_write_test(nv_item_num);
		g_nve_write_end_time = hisi_getcurtime();
		if(ret){
			printk(KERN_ERR "nve_write_test test failed!\n");
			return NVE_TEST_ERR;
		}
		g_nve_cost_time = g_nve_write_end_time - g_nve_write_start_time;
		total_nve_write_time += g_nve_cost_time;
		printk(KERN_ERR "test nv cost time [%llu]ns,test_time = %d!\n", g_nve_cost_time, i);
		msleep(2);
	}
	ret = nve_write_init_value();
	if(ret){
		printk(KERN_ERR "nve_write_init_value test failed!\n");
		return NVE_TEST_ERR;
	}
	average_nve_write_time = total_nve_write_time / NVE_TEST_STRESS_TIMES;
	return average_nve_write_time;
}

EXPORT_SYMBOL(nve_write_time_test);

uint64_t nve_read_time_test(uint32_t nv_item_num)
{
	uint64_t total_nve_read_time = 0;
	uint64_t average_nve_read_time;
	int i;
	int ret;
	for(i = 0;i < NVE_TEST_STRESS_TIMES;i++){
		g_nve_read_start_time = hisi_getcurtime();
		ret = nve_read_test(nv_item_num);
		g_nve_read_end_time = hisi_getcurtime();
		if(ret){
			printk(KERN_ERR "nve_write_test test failed!\n");
			return NVE_TEST_ERR;
		}
		g_nve_cost_time = g_nve_read_end_time - g_nve_read_start_time;
		total_nve_read_time += g_nve_cost_time;
		printk(KERN_ERR "test nv cost time [%llu]ns,test_time = %d!\n", g_nve_cost_time, i);
		msleep(2);
	}
	average_nve_read_time = total_nve_read_time / NVE_TEST_STRESS_TIMES;
	return average_nve_read_time;
}

EXPORT_SYMBOL(nve_read_time_test);

void nve_all_test(void)
{
	nve_print_test(my_nve);
}
EXPORT_SYMBOL(nve_all_test);
#endif

/*
 * Function name:nve_open_ex.
 * Discription:open NV device.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static int nve_open_ex(void)
{
	int ret = 0;
	struct NVE_struct *nve;

	/*use the semaphore to ensure that only one thread can visit the device
	 * at the same time*/
	if (down_interruptible(&nv_sem))
		return -EBUSY;

	/*the driver is not initialized successfully, return error*/
	if (NULL == my_nve) {
		ret = -ENODEV;
		printk(KERN_ERR
		       "[NVE][%s]:my_nve has not been alloced.\n",
		       __func__);
		goto out;
	} else
		nve = my_nve;

	/*if NV has been initiallized,then skip following code in this
	 * function*/
	if (nve->initialized > 0) {
		printk(KERN_INFO "[NVE][%s]:NV ramdisk has been initialized!\n",
		       __func__);
		goto out;
	}

	/*Total avaliable NV partition size is 4M,but we only use 1M*/
	nve->nve_partition_count = NVE_PARTITION_COUNT;

	nve->nve_current_id = NVE_INVALID_NVM;
	printk(KERN_INFO "[NVE] nve->nve_partition_count = 0x%x.\n",
	       nve->nve_partition_count);

	/*
	 * partition count must bigger than 3,
	 * one for partition 0,one for update, the other for runtime.
	 */
	if (nve->nve_partition_count <= 3) {
		ret = -ENODEV;
		goto out;
	}

	nve_find_valid_partition(nve);

	/*check partiton 0 is valid or not*/
	ret = nve_check_partition(nve, 0);

	if (!ret) {
		/*partiton 0 is valid, restore it to current partition*/
		printk(KERN_INFO "[NVE]partition0 is valid, restore it to "
				"current partition.\n");
		ret = nve_restore(nve);
	}

	if (ret) {
		if (NVE_INVALID_NVM == nve->nve_current_id) {
			printk(KERN_ERR "[NVE] nve_open_ex: no valid NVM.\n");
			ret = -ENODEV;
			goto out;
		} else
			ret = 0;
	}

	/*
	 *create NV index table,so we can visit any NV items
	 *that we want to read or write conveniently.
	 */
	if (nve_do_index_table(nve)) {
		ret = -ENODEV;
		goto out;
	}

	printk(KERN_INFO "[NVE][%s]current_id = %d\n", __func__,
	       nve->nve_current_id);

	nve->initialized = 1;

out:
	/*release the semaphore*/
	up(&nv_sem);
	return ret;
}
/*
 * Function name:nve_out_log.
 * Discription:output log of reading and writing nv.
 * Parameters:
 *          @ struct hisi_nve_info_user *user_info pointer.
	    @ bool isRead
 * return value:
 *          void
 */
static void nve_out_log(struct hisi_nve_info_user *user_info, int isRead)
{
	int index;
	if (NULL == user_info) {
		printk(KERN_WARNING "[NVE][%s]:user_info is null! \n",
		       __func__);
		return;
	}
	if (isRead) {
		printk(KERN_WARNING "[NVE][%s]:read nv:ID= %d \n", __func__,
		       user_info->nv_number);
	} else {
		printk(KERN_WARNING "[NVE][%s]:write nv:ID= %d \n", __func__,
		       user_info->nv_number);
	}
	memset(log_nv_info, 0, sizeof(log_nv_info));
	memset(temp_nv_info, 0, sizeof(temp_nv_info));
	for (index = 0; index < (int)user_info->valid_size; index++) {
		snprintf(temp_nv_info, (size_t)(NV_INFO_LEN - 1), "%s,0x%x", log_nv_info,
			 user_info->nv_data[index]);
		memset(log_nv_info, 0, sizeof(log_nv_info));
		snprintf(log_nv_info, (size_t)(NV_INFO_LEN - 1), "%s", temp_nv_info);
		if ((index % 20 == 0) && (index > 0)) {
			printk(KERN_WARNING "%s\n", log_nv_info);
			memset(log_nv_info, 0, sizeof(log_nv_info));
		}
		memset(temp_nv_info, 0, sizeof(temp_nv_info));
	}
	printk(KERN_WARNING "%s\n", log_nv_info);
	if (isRead) {
		printk(KERN_WARNING "[NVE][%s]:read data = %s\n", __func__,
		       user_info->nv_data);
	} else {
		printk(KERN_WARNING "[NVE][%s]:write data = %s\n", __func__,
		       user_info->nv_data);
	}
}
/*
 * Function name:hisi_nve_direct_access_for_rdr.
 * Discription:read or write NV items interfaces that will be called by other
 * functions.
 * Parameters:
 *          @ user_info:struct hisi_nve_info_user pointer.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 *          @ -ENXIO - not rdr nv items.
 */
int hisi_nve_direct_access_for_rdr(struct hisi_nve_info_user *user_info)
{
	int ret;
	u_char *nv_data = NULL;
	struct NVE_struct *nve = NULL;
	struct NVE_index *nve_index = NULL;
	struct NV_header *nv = NULL;
	struct NVE_partition_header *nve_header = NULL;

	/*input parameter invalid, return.*/
	if (NULL == user_info) {
		printk(KERN_ERR "[NVE][%s] input parameter is NULL.\n", __func__);
		ret = -EINVAL;
		goto out;
	}

	/*check driver init status is ready*/
	if(!hisi_init_nv_ok){
		printk(KERN_ERR "[NVE][%s]nve dirver init is not ready!\n", __func__);
		ret = -ENODEV;
		goto out;
	}

	/*open nve to read partition to ramdisk.*/
	ret = nve_open_ex();
	if (ret)
		goto out;

	/*ensure only one process can visit NV device at the same time in
	 * kernel*/
	if (down_interruptible(&nv_sem))
		return -EBUSY;

	/*lint -e826*/
	nve = my_nve;
	nve_header = (struct NVE_partition_header *)(nve->nve_ramdisk +
						     PARTITION_HEADER_OFFSET);
	/*lint +e826*/

	printk(KERN_INFO "[NVE][%s]valid items 0x%x\n", __func__,
	       nve_header->valid_items);

	/*according ramdisk info, check NV number is valid or not, if error return*/
	if (user_info->nv_number >= nve_header->valid_items) {
		printk(KERN_ERR "[NVE][%s] NV items[%d] is not defined.\n",
		       __func__, user_info->nv_number);
		up(&nv_sem);
		return -EINVAL;
	}

	/*Find the NV position in NV index table*/
	nve_index = nve->nve_index_table + user_info->nv_number;

	/*check NV length is valid or not, if is not valid, recover the valid length*/
	if (user_info->valid_size > NVE_NV_DATA_SIZE) {
		printk(KERN_WARNING "[NVE]Bad parameter,inputed NV length is "
				    "bigger than 104,the surplus will be "
				    "neglected\n");
		user_info->valid_size = NVE_NV_DATA_SIZE;
	} else if (0 == user_info->valid_size) {
		user_info->valid_size = nve_index->nv_size;
		printk(KERN_WARNING "[NVE]Bad parameter,inputed NV length is "
				"0,will be reassigned according to NV inedx "
				"table\n");
	}
	/*lint -e826*/
	nv_data = nve->nve_ramdisk + nve_index->nv_offset +
		  sizeof(struct NV_header);
	/*lint +e826*/
	if (NV_READ == user_info->nv_operation) {
		/*read nv from ramdisk*/
		memcpy(user_info->nv_data, nv_data, (size_t)user_info->valid_size);
	} else {
		/*write nv to ramdisk*/
		nv = (struct NV_header *)(nve->nve_ramdisk +
					  nve_index->nv_offset);
		nv->valid_size = user_info->valid_size;
		nve_index->nv_size = user_info->valid_size;
		memset(nv_data, 0x0, (size_t)NVE_NV_DATA_SIZE);
		memcpy(nv_data, user_info->nv_data, (size_t)user_info->valid_size);

		/*update nve_ramdisk*/
		nve_header->nve_age++;

		/*write NV to emmc*/
		nve_increment(nve);
		ret = nve_write((loff_t)(nve->nve_current_id) *
					NVE_PARTITION_SIZE,
				(size_t)NVE_PARTITION_SIZE, (u_char *)nve->nve_ramdisk);
	}

	/*release the semaphore*/
	up(&nv_sem);
out:
	return ret;
}

/*
 * Function name:hisi_nve_direct_access.
 * Discription:read or write NV items interfaces that will be called by other
 * functions.
 * Parameters:
 *          @ user_info:struct hisi_nve_info_user pointer.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
int hisi_nve_direct_access(struct hisi_nve_info_user *user_info)
{
	int ret;
	u_char *nv_data = NULL;
	struct NVE_struct *nve = NULL;
	struct NVE_index *nve_index = NULL;
	struct NV_header *nv = NULL;
	struct NVE_partition_header *nve_header = NULL;

	/*input parameter invalid, return.*/
	if (NULL == user_info) {
		printk(KERN_ERR "[NVE][%s] input parameter is NULL.\n", __func__);
		ret = -EINVAL;
		goto out;
	}

	/*check driver init status is ready*/
	if(!hisi_init_nv_ok){
		printk(KERN_ERR "[NVE][%s]nve dirver init is not ready!\n", __func__);
		ret = -ENODEV;
		goto out;
	}

	/*open nve.*/
	ret = nve_open_ex();
	if (ret)
		goto out;

	/*ensure only one process can visit NV device at the same time in
	 * kernel*/
	if (down_interruptible(&nv_sem))
		return -EBUSY;

	nve = my_nve;
	/*lint -e826*/
	nve_header = (struct NVE_partition_header *)(nve->nve_ramdisk +
						     PARTITION_HEADER_OFFSET);
	/*lint +e826*/
	printk(KERN_INFO "[NVE][%s]valid items 0x%x\n", __func__,
	       nve_header->valid_items);

	/*check NV number is valid or not*/
	if (user_info->nv_number >= nve_header->valid_items) {
		printk(KERN_ERR "[NVE][%s] NV items[%d] is not defined.\n",
		       __func__, user_info->nv_number);
		up(&nv_sem);
		return -EINVAL;
	}

	/*Find the NV position in NV index table*/
	nve_index = nve->nve_index_table + user_info->nv_number;

	/*check NV length is valid or not*/
	if (user_info->valid_size > NVE_NV_DATA_SIZE) {
		printk(KERN_WARNING "[NVE]Bad parameter,inputed NV length is "
				    "bigger than 104,the surplus will be "
				    "neglected\n");
		user_info->valid_size = NVE_NV_DATA_SIZE;
	} else if (0 == user_info->valid_size) {
		user_info->valid_size = nve_index->nv_size;
		printk(KERN_WARNING "[NVE]Bad parameter,inputed NV length is "
				"0,will be reassigned according to NV inedx "
				"table\n");
	}

	nv_data = nve->nve_ramdisk + nve_index->nv_offset +
		  sizeof(struct NV_header);

	if (NV_READ == user_info->nv_operation) {
		/*read nv from ramdisk*/
		memcpy(user_info->nv_data, nv_data, (size_t)user_info->valid_size);
		nve_out_log(user_info, true);
	} else {
		/*write nv to ramdisk*/
		/*lint -e826*/
		nv = (struct NV_header *)(nve->nve_ramdisk +
					  nve_index->nv_offset);
		/*lint +e826*/
		nv->valid_size = user_info->valid_size;
		nve_index->nv_size = user_info->valid_size;
		memset(nv_data, 0x0, (size_t)NVE_NV_DATA_SIZE);
		memcpy(nv_data, user_info->nv_data, (size_t)user_info->valid_size);

		/*update nve_ramdisk*/
		nve_header->nve_age++;

		/*write NV to emmc*/
		nve_increment(nve);
		ret = nve_write((loff_t)nve->nve_current_id *
					NVE_PARTITION_SIZE,
				(size_t)NVE_PARTITION_SIZE, (u_char *)nve->nve_ramdisk);
		nve_out_log(user_info, false);
	}

	/*release the semaphore*/
	up(&nv_sem);
out:
	return ret;
}

/*
 * Function name:nve_open.
 * Discription:open NV device in terms of calling nve_open_ex().
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static int nve_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int nve_close(struct inode *inode, struct file *file)
{
	return 0;
}

/*
 * Function name:nve_ioctl.
 * Discription:complement read or write NV by terms of sending command-words.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static long nve_ioctl(struct file *file, u_int cmd, u_long arg)
{
	int ret = 0;
	void __user *argp = (void __user *)arg;
	u_int size;
	struct hisi_nve_info_user info;
	struct NVE_struct *nve;
	struct NVE_index *nve_index = NULL;
	struct NV_header *nv = NULL;
	struct NVE_partition_header *nve_header = NULL;
	u_char *nv_data = NULL;

	/*ensure only one process can visit NV device at the same time in API*/
	if (down_interruptible(&nv_sem))
		return -EBUSY;

	if (NULL == my_nve) {
		printk(KERN_ERR "[NVE][%s]my_nve not initialized!\n", __func__);
		up(&nv_sem);
		return -EFAULT;
	}

	nve = my_nve;
	size = ((cmd & IOCSIZE_MASK) >> IOCSIZE_SHIFT);

	if (cmd & IOC_IN) {
		if (!access_ok(VERIFY_READ, argp, size)) {
			printk(KERN_ERR "[NVE][%s]access_in error!\n",
			       __func__);
			up(&nv_sem);
			return -EFAULT;
		}
	}

	if (cmd & IOC_OUT) {
		if (!access_ok(VERIFY_WRITE, argp, size)) {
			printk(KERN_ERR "[NVE][%s]access_out error!\n",
			       __func__);
			up(&nv_sem);
			return -EFAULT;
		}
	}

	switch (cmd) {
	case NVEACCESSDATA:
		if (copy_from_user(&info, argp,
				   sizeof(struct hisi_nve_info_user))) {
			up(&nv_sem);
			return -EFAULT;
		}

		nve_header =
			(struct NVE_partition_header
				 *)(nve->nve_ramdisk + PARTITION_HEADER_OFFSET);

		if (info.nv_number >= nve_header->valid_items) {
			printk(KERN_ERR "[NVE][%s], nv[%d] is not defined.\n",
			       __func__, info.nv_number);
			up(&nv_sem);
			return -EFAULT;
		}

		nve_index = nve->nve_index_table + info.nv_number;

		if (info.valid_size > NVE_NV_DATA_SIZE) {
			printk(KERN_WARNING "[NVE]Bad parameter,inputed NV "
					    "length is bigger than 104,the "
					    "surplus will be neglected\n");
			info.valid_size = NVE_NV_DATA_SIZE;
		} else if (info.valid_size == 0) {
			printk(KERN_WARNING "[NVE]Bad parameter,inputed NV length "
					"is 0,will be reassigned according to "
					"NV inedx table\n");
			info.valid_size = nve_index->nv_size;
		}
		nv_data = nve->nve_ramdisk + nve_index->nv_offset +
			  sizeof(struct NV_header);

		if (NV_READ == info.nv_operation) {
			/*read nv from ramdisk*/
			memcpy(info.nv_data, nv_data, (size_t)info.valid_size);
			
			
			nve_out_log(&info, true);
			
			
			/*send back to user*/
			if (copy_to_user(argp, &info,
					 sizeof(struct hisi_nve_info_user))) {
				up(&nv_sem);
				return -EFAULT;
			}
		} else {
			/*write nv to ramdisk*/
			nv = (struct NV_header *)(nve->nve_ramdisk +
						  nve_index->nv_offset);
			nv->valid_size = info.valid_size;
			nve_index->nv_size = info.valid_size;
			memset(nv_data, 0x0, (size_t)NVE_NV_DATA_SIZE);
			memcpy(nv_data, info.nv_data, (size_t)info.valid_size);

			/*update nve_ramdisk*/
			nve_header->nve_age++;

			/*write NVE to emmc*/
			nve_increment(nve);
			ret = nve_write((loff_t)nve->nve_current_id *
						NVE_PARTITION_SIZE,
					(size_t)NVE_PARTITION_SIZE,
					(u_char *)nve->nve_ramdisk);
			
			
			nve_out_log(&info, false);
			
			
		}
		break;
	default:
		printk(KERN_ERR "[NVE][%s] Unknow command!\n", __func__);
		ret = -ENOTTY;
		break;
	}

	up(&nv_sem);
	return (long)ret;
}

#ifdef CONFIG_COMPAT
static long nve_compat_ioctl(struct file *file, u_int cmd, u_long arg)
{
	return nve_ioctl(file, cmd, (unsigned long)compat_ptr((unsigned int)arg));
}
#endif

static const struct file_operations nve_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = nve_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = nve_compat_ioctl,
#endif
	.open = nve_open,
	.release = nve_close,
};

static int __init init_nve(void)
{
	int error;
	struct NVE_struct *nve;

	/*semaphore initial*/
	sema_init(&nv_sem, 1);

	nve = kzalloc(sizeof(struct NVE_struct), GFP_KERNEL);

	if (nve == NULL) {
		printk(KERN_ERR
		       "[NVE][%s]failed to allocate driver data in line %d.\n",
		       __func__, __LINE__);
		return -ENOMEM;
	}
	my_nve = nve;
	memset(nve, 0x0, sizeof(struct NVE_struct));
	nve->nve_ramdisk = (u_char *)kzalloc((size_t)NVE_PARTITION_SIZE, GFP_KERNEL);

	if (NULL == nve->nve_ramdisk) {
		printk(KERN_ERR "[NVE][%s]failed to allocate ramdisk buffer in "
				"line %d.\n",
		       __func__, __LINE__);
		error = -ENOMEM;
		goto failed_free_driver_data;
	}

	/* register a device in kernel, return the number of major device */
	my_nve->nve_major_number = register_chrdev(0, "nve", &nve_fops);

	if (my_nve->nve_major_number < 0) {
		printk(KERN_ERR "[NVE]Can't allocate major number for "
				"Non-Volatile memory Extension device.\n");
		error = -EAGAIN;
		goto failed_free_ramdisk;
	}

	/* register a class, make sure that mdev can create device node in
	 * "/dev" */
	nve_class = class_create(THIS_MODULE, "nve");

	if (IS_ERR(nve_class)) {
		printk(KERN_ERR "[NVE]Error creating nve class.\n");
		unregister_chrdev((unsigned int)my_nve->nve_major_number, "nve");
		error = (int)PTR_ERR(nve_class);
		goto failed_free_driver_data;
	}
	printk(KERN_INFO"[NVE][%s]NV driver init in kernel is ok!\n", __func__);
	hisi_init_nv_ok = 1;

	return 0;
failed_free_ramdisk:
	kfree(my_nve->nve_ramdisk);
	my_nve->nve_ramdisk = NULL;
failed_free_driver_data:
	kfree(my_nve);
	my_nve = NULL;
	return error;
}

static void __exit cleanup_nve(void)
{
	class_destroy(nve_class);
	if (NULL != my_nve) {
		unregister_chrdev((unsigned int)my_nve->nve_major_number, "nve");
		kfree(my_nve->nve_index_table);
		my_nve->nve_index_table = NULL;
		kfree(my_nve->nve_ramdisk);
		my_nve->nve_ramdisk = NULL;
		kfree(my_nve);
		my_nve = NULL;
		kfree(nve_block_device_name);
	}

	return;
}

static int nve_setup(const char *val, struct kernel_param *kp)
{
	int ret;

	if (1 == hisi_nv_setup_ok) {
		printk(KERN_ERR "[NVE][%s]has been done.\n",__func__);
		return 0;
	}

	if (!val)
		return -EINVAL;

	nve_block_device_name = kzalloc(strlen(val) + 1, GFP_KERNEL);
	if(nve_block_device_name == NULL){
		printk(KERN_ERR
		       "[NVE][%s]failed to allocate nve_block_device_name mem in line %d.\n",
		       __func__, __LINE__);
		return -ENOMEM;
	}

	memcpy(nve_block_device_name, val, strlen(val) + 1);
	printk(KERN_INFO "[NVE][%s] device name = %s\n", __func__, nve_block_device_name);

	ret = nve_open_ex();
	if (ret < 0){
		printk(KERN_ERR "[NVE][%s] nve_open_ex failed!\n",__func__);
		return -1;
	}

	/* create a device node */
	device_create(nve_class, NULL, MKDEV((unsigned int)my_nve->nve_major_number, 0), NULL,
		      "nve0");
	hisi_nv_setup_ok = 1;

	return 0;
}

module_param_call(nve, nve_setup, NULL, NULL, 0664);

module_init(init_nve);
module_exit(cleanup_nve);

/*export hisi_nve_direct_access,so we can use it in other procedures*/
EXPORT_SYMBOL(hisi_nve_direct_access);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hisi-nve");
MODULE_DESCRIPTION("Direct character-device access to NVE devices");
