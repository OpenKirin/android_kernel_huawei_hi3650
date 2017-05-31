/*
 *
 * Copyright (c) 2013-2015, Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/err.h>
#include <linux/bootdevice.h>
#include <asm/uaccess.h>
#include <partition.h>
#include <linux/hisi/kirin_partition.h>

#ifdef CONFIG_HISI_AB_PARTITION
#define BOOT_XLOADER_A                 (0x1)
#define BOOT_XLOADER_B                 (0x2)
#define MAX_PARTITION_NAME_LENGTH      (36)

extern int ufs_set_boot_partition_type(int boot_partition_type);
extern int mmc_set_boot_partition_type(int boot_partition_type);
#endif

int get_cunrrent_total_ptn_num(void)
{
	int current_ptn_num = 0;
	enum bootdevice_type boot_device_type = BOOT_DEVICE_EMMC;

	boot_device_type = get_bootdevice_type();

	if (BOOT_DEVICE_EMMC == boot_device_type) {
		current_ptn_num = sizeof(partition_table_emmc) / sizeof(struct partition);
	}
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
	else if (BOOT_DEVICE_UFS  == boot_device_type){
		current_ptn_num = sizeof(partition_table_ufs) / sizeof(struct partition);
	}
#endif
	return current_ptn_num;
}
EXPORT_SYMBOL(get_cunrrent_total_ptn_num);

void flash_find_hisee_ptn(const char* str, char* pblkname)
{
	char device_block_path[] = "/dev/block/";
	char device_path_emmc[]="mmcblk0p27";
	char device_path_ufs[]="sdd23";
	enum bootdevice_type boot_device_type;

	if ((NULL == pblkname) || (NULL == str)) {
		printk(KERN_ERR "Input partition name or device path buffer is NULL\n");
		return;
	}

	boot_device_type = get_bootdevice_type();
	if (BOOT_DEVICE_EMMC == boot_device_type) {
	        strncpy(pblkname, device_block_path, strlen(device_block_path));
	        strncpy(pblkname + strlen(device_block_path), device_path_emmc, strlen(device_path_emmc) + 1);
	}
	else
	{
	        strncpy(pblkname, device_block_path, strlen(device_block_path));
	        strncpy(pblkname + strlen(device_block_path), device_path_ufs, strlen(device_path_ufs) + 1);
	}

}
EXPORT_SYMBOL(flash_find_hisee_ptn);
/*
 *Function: Get the device path by partition name
 *Input : str, partition name
 *Output: pblkname, boot device path, such as:/dev/block/bootdevice/by-name/xxx
 */
int flash_find_ptn(const char* str, char* pblkname)
{
	int n;
	char device_path[] = "/dev/block/bootdevice/by-name/";
	int current_ptn_num = 0;
	struct partition *current_partition_table = NULL;
	enum bootdevice_type boot_device_type = BOOT_DEVICE_EMMC;
#ifdef CONFIG_HISI_AB_PARTITION
	enum AB_PARTITION_TYPE storage_boot_partition_type;
	char partition_name_tmp[MAX_PARTITION_NAME_LENGTH];
#endif

	if ((NULL == pblkname) || (NULL == str)) {
		printk(KERN_ERR "Input partition name or device path buffer is NULL\n");
		return -1;
	}

	boot_device_type = get_bootdevice_type();

	if (BOOT_DEVICE_EMMC == boot_device_type) {
		current_partition_table  = (struct partition *)partition_table_emmc;/*lint !e1773*/
	}
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
	else if (BOOT_DEVICE_UFS  == boot_device_type){
		current_partition_table  = (struct partition *)partition_table_ufs;
	}
#endif
	else {
		printk(KERN_ERR "Invalid boot device type\n");
		return -1;
	}

	current_ptn_num = get_cunrrent_total_ptn_num();
	for(n = 0; n < current_ptn_num; n++) {
		if(!strcmp((current_partition_table + n)->name, str)) {/*[false alarm]:current_partition_table!=NULL*/
			strncpy(pblkname, device_path, strlen(device_path));
			strncpy(pblkname + strlen(device_path), str, strlen(str)+1);
			return 0;
		}
	}
#ifdef CONFIG_HISI_AB_PARTITION
	storage_boot_partition_type = get_device_boot_partition_type();

	strncpy(partition_name_tmp, str, strlen(str));
	if (BOOT_XLOADER_A == storage_boot_partition_type) {
		strncpy(partition_name_tmp + strlen(str), "_a", (unsigned long)3);
	} else if (BOOT_XLOADER_B == storage_boot_partition_type) {
		strncpy(partition_name_tmp + strlen(str), "_b", (unsigned long)3);
	} else {
		return -1;
	}

	current_ptn_num = get_cunrrent_total_ptn_num();
	for(n = 0; n < current_ptn_num; n++) {
		if(!strcmp((current_partition_table + n)->name, partition_name_tmp)) {/*[false alarm]:current_partition_table!=NULL*/
			strncpy(pblkname, device_path, strlen(device_path));
			strncpy(pblkname + strlen(device_path), str, strlen(str)+1);
			return 0;
		}
	}
#endif
	printk(KERN_ERR "partition is not found\n");
	return -1;
}
EXPORT_SYMBOL(flash_find_ptn);

/*
 *Get partition offset in total partitions(all lu), not the current LU
 */
int flash_get_ptn_index(const char* pblkname)
{
	int n;
	int current_ptn_num;
	struct partition *current_partition_table = NULL;
	enum bootdevice_type boot_device_type;
#ifdef CONFIG_HISI_AB_PARTITION
	enum AB_PARTITION_TYPE storage_boot_partition_type;
	char partition_name_tmp[MAX_PARTITION_NAME_LENGTH];
#endif
	if (NULL == pblkname) {
		printk(KERN_ERR "Input partition name is NULL\n");
		return -1;
	}

	boot_device_type = get_bootdevice_type();
	if (BOOT_DEVICE_EMMC == boot_device_type) {
		current_partition_table  = (struct partition *)partition_table_emmc;/*lint !e1773*/
	}
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
	else if (BOOT_DEVICE_UFS  == boot_device_type) {
		current_partition_table  = (struct partition *)partition_table_ufs;
	}
#endif
	else {
		printk(KERN_ERR "Invalid boot device type\n");
		return -1;
	}

	current_ptn_num = get_cunrrent_total_ptn_num();

	if(!strcmp(PART_XLOADER, pblkname)) {
		printk(KERN_ERR "This is boot partition\n");
		return -1;
	}

	/*normal partition*/
	for(n = 0; n < current_ptn_num; n++) {
		if (!strcmp((current_partition_table + n)->name, pblkname)) {
			return n;
		}
	}

#ifdef CONFIG_HISI_AB_PARTITION
	storage_boot_partition_type = get_device_boot_partition_type();

	strncpy(partition_name_tmp, pblkname, strlen(pblkname));
	if (BOOT_XLOADER_A == storage_boot_partition_type) {
		strncpy(partition_name_tmp + strlen(pblkname), "_a", 3);
	} else if (BOOT_XLOADER_B == storage_boot_partition_type) {
		strncpy(partition_name_tmp + strlen(pblkname), "_b", 3);
	} else {
		return -1;
	}

	/*A/B partition*/
	for(n = 0; n < current_ptn_num; n++) {
		if (!strcmp((current_partition_table + n)->name, partition_name_tmp)) {
			return n;
		}
	}
#endif

	printk(KERN_ERR "Input partition is not found\n");
	return -1;
}
EXPORT_SYMBOL(flash_get_ptn_index);

enum AB_PARTITION_TYPE emmc_boot_partition_type = XLOADER_A;
enum AB_PARTITION_TYPE ufs_boot_partition_type = XLOADER_A;

/*
 *Get storage boot partition type:XLOADER_A or XLOADER_B
 */
enum AB_PARTITION_TYPE get_device_boot_partition_type(void)
{
#ifdef CONFIG_HISI_AB_PARTITION
	enum bootdevice_type boot_device_type;

	boot_device_type = get_bootdevice_type();

	if (BOOT_DEVICE_EMMC == boot_device_type) {
		return emmc_boot_partition_type;
	}
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
	else if (BOOT_DEVICE_UFS  == boot_device_type){
		return ufs_boot_partition_type;
	}
#endif
	else {
		printk(KERN_ERR "invalid boot device type\n");
		return ERROR_VALUE;
	}
#else
	printk(KERN_INFO "Not support AB partition\n");
	return NO_SUPPORT_AB;
#endif
}

/*
 *set storage boot partition type
 */
int set_device_boot_partition_type(char boot_partition_type)
{
#ifdef CONFIG_HISI_AB_PARTITION
	int ret;
	enum bootdevice_type boot_device_type;

	boot_device_type = get_bootdevice_type();

	if (BOOT_DEVICE_EMMC == boot_device_type) {
		ret = mmc_set_boot_partition_type(boot_partition_type);
		if (ret) {
			printk(KERN_ERR "set boot device type failed\n");
			return -1;
		}
		emmc_boot_partition_type = boot_partition_type;
	}
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
	else if (BOOT_DEVICE_UFS  == boot_device_type){
		ret = ufs_set_boot_partition_type(boot_partition_type);
		if (ret) {
			printk(KERN_ERR "set boot device type failed\n");
			return -1;
		}
		ufs_boot_partition_type = boot_partition_type;
	}
#endif
	else {
		printk(KERN_ERR "invalid boot device type\n");
		return -1;
	}
#else
	printk(KERN_ERR "Not support AB partition writing\n");
#endif

	return 0;
}
