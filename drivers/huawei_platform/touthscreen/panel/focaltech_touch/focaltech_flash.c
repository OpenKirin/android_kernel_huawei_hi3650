

#include <../../huawei_touchscreen_chips.h>
#include <huawei_platform/log/log_jank.h>

#include "../../huawei_touchscreen_algo.h"
#include "focaltech_flash.h"
#include "focaltech_dts.h"

#if defined(CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

/*
 * Global variable or extern global variabls/functions
 */
struct fts_upgrade_info fts_upgrade_info_curr;
struct fts_upgrade_delay_time fts_upgrade_delay;

static int fts_firmware_update(struct fts_ts_platform_data *fts_pdata,
	const u8 *pbt_buf, u32 dw_lenth);

static int fts_get_data_check_sum(const unsigned char *data, size_t data_size,
	unsigned char *check_sum);

static int fts_enter_work_model_from_pram(void);
static int fts_enter_pram_model(struct fts_ts_platform_data *fts_pdata);
static int fts_flash_get_fw_file_size(char *fw_name);
static int fts_flash_read_fw_file(char *fw_name, unsigned char *fw_buf);

static int fts_enter_work_model_form_pram_update(void);
static int fts_flash_pram(struct fts_ts_platform_data *fts_pdata,
	const unsigned char *pram_data, size_t pram_size);
static int fts_enter_work_model_by_hardware(void);

static int fts_read_check_sum_in_pram(struct fts_ts_platform_data *fts_pdata,
	unsigned int start_addr, unsigned int crc_length,
	unsigned char *check_sum);

static int fts_enter_work_model_from_rom_update(void);

/*
 * description : get ic status
 *
 * param - status : buffer to receive ic status
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_get_status(unsigned int *status)
{
	int ret = 0;

	unsigned char cmd = 0x00;
	unsigned char reg_val[2] = {0};

	if (NULL == status) {
		TS_LOG_ERR("%s:input parameter is null\n", __func__);
		return -ENOMEM;
	}

	memset(reg_val, 0, sizeof(reg_val));
	cmd = FTS_CMD_GET_STATUS;

	ret = fts_i2c_read(&cmd, 1, reg_val, 2);
	if (ret) {
		TS_LOG_ERR("%s:read status fail, ret=%d\n", __func__, ret);
		return ret;
	}

	*status = (reg_val[0] << 8) | (reg_val[1]);

	return 0;
}

/*
 * description : enter bootloader model by hardware reset ic
 *
 * param - fts_data : struct fts_ts_platform_data *fts_pdata
 *
 * return : return 0 if read ic status success, otherwize return error code
 *
 * notice : this function only work in normal model
 */
static int fts_enter_rom_update_model_by_hardware(
	struct fts_ts_platform_data *fts_pdata)
{
	return fts_hardware_reset_to_rom_update_model(fts_pdata);
}

/*
 * return: if read project id success, return 0, else return error code
 *
 * notice: this function work when ic is in normal model
 */
int fts_enter_rom_update_model_by_software(void)
{
	int ret = 0;

	ret = fts_write_reg(FTS_REG_SOFT_RESET_FC, FTS_UPGRADE_AA);
	if (ret < 0) {
		TS_LOG_ERR("%s:write 0xAA to soft reset ic fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	ret = fts_write_reg(FTS_REG_SOFT_RESET_FC, FTS_UPGRADE_55);
	if (ret < 0) {
		TS_LOG_ERR("%s:write 0x55 to soft reset ic fail, ret=%d\n",
			__func__, ret);
		return ret;
	}
	msleep(fts_upgrade_delay.reboot_delay);

	return 0;
}


/*
 * description : check if firmware package have write to ic
 *
 * param - command : firmware write command, such as FTS_CMD_WRITE_PRAM
 *
 * param - start_addr : addr in ic to receive the first firmware package
 *
 * param - start_write_addr : addr in ic to receive current firmware pachage
 *
 * param - data_size : current package data size
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_wait_firmware_write_finish(
	unsigned char command,
	unsigned int start_addr,
	unsigned int start_write_addr,
	unsigned int data_size)
{

	int i = 0;
	int ret = 0;
	unsigned int ic_status = 0;
	unsigned int driver_status = 0;

	/* no need to wait when write pram */
	if (FTS_CMD_WRITE_PRAM == command)
		return 0;

	driver_status = start_addr + start_write_addr / data_size;
	for (i = 0; i < fts_upgrade_delay.write_flash_max_query_time; i++) {

		ret = fts_get_status(&ic_status);
		if (ret) {
			TS_LOG_ERR("%s:get ic status fail, ret=%d\n",
				__func__, ret);
			return ret;
		}

		if (ic_status == driver_status)
			return 0;

		msleep(1);
	}


	TS_LOG_ERR("%s:%s, ic status=0x%X, driver status=0x%X\n",
			__func__, "time out for check ic status",
			ic_status, driver_status);

	return -ETIMEDOUT;
}

/*
 * description : write firmware data to ic
 *
 * param - fw_data : firmware data to write
 *
 * param - fw_length : firmware data length
 *
 * param - command : firmware write command, like FTS_CMD_WRITE_PRAM
 *
 * param - start_addr : addr in ic that first firmware package to write
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_write_firmware_data(
	const unsigned char *fw_data,
	unsigned int fw_length,
	unsigned char command,
	unsigned int start_addr)
{
	int i = 0;
	int ret = 0;

	unsigned int data_size = 0;
	unsigned int package_count = 0;
	unsigned int copy_offset = 0;
	unsigned int start_write_addr = 0;

	unsigned char package_buf[FTS_PACKAGE_SIZE + 6] = {0};

	TS_LOG_DEBUG("%s:Write firmware to ic\n", __func__);
	TS_LOG_DEBUG("%s:fw write:data_length=%u, package_count=%u\n",
		__func__, fw_length, package_count);

	package_count = fw_length / FTS_PACKAGE_SIZE;
	if (fw_length % FTS_PACKAGE_SIZE != 0)
		package_count += 1;

	start_write_addr = start_addr;
	package_buf[0] = command;
	for (i = 0; i < package_count; i++) {

		/* the last package to write */
		if ((i + 1 == package_count)
			&& (fw_length % FTS_PACKAGE_SIZE != 0)) {
			data_size = fw_length % FTS_PACKAGE_SIZE;
		} else {
			data_size = FTS_PACKAGE_SIZE;
		}

		/* offset */
		package_buf[1] = (unsigned char)(start_write_addr >> 16);
		package_buf[2] = (unsigned char)(start_write_addr >> 8);
		package_buf[3] = (unsigned char)(start_write_addr);

		/* data size */
		package_buf[4] = (unsigned char)(data_size >> 8);
		package_buf[5] = (unsigned char)(data_size);

		copy_offset = start_write_addr - start_addr;
		memcpy(&package_buf[6],	&fw_data[copy_offset], data_size);

		ret = fts_i2c_write(package_buf, data_size + 6);
		if (ret < 0) {
			TS_LOG_ERR("%s:write fw data fail, index=%d, ret=%d\n",
				__func__, i, ret);
			return -EIO;
		}

		ret = fts_wait_firmware_write_finish(
			command, start_addr, start_write_addr, data_size);
		if (ret) {
			TS_LOG_ERR("%s:%s, ret=%d\n", __func__,
				"wait firmware write finish fail", ret);
			return ret;
		}

		start_write_addr += data_size;
		TS_LOG_DEBUG("%s:%s:index=%d, data_size=%u, writed_size=%u\n",
			__func__, "fw write", i, data_size, start_write_addr);
	}

	return 0;
}

/*
 * description : write pram data to ic
 *
 * param - fw_data : firmware data to write
 *
 * param - fw_length : firmware data length
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_write_pram_data(
	const unsigned char *fw_data,
	unsigned int fw_length)
{
	return fts_write_firmware_data(fw_data, fw_length,
		FTS_CMD_WRITE_PRAM, 0);
}

/*
 * description : write app data to ic
 *
 * param - fw_data : firmware data to write
 *
 * param - fw_length : firmware data length
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_write_app_data(
	const unsigned char *fw_data,
	unsigned int fw_length)
{
	return fts_write_firmware_data(fw_data, fw_length,
		FTS_CMD_WRITE_FLASH, FTS_FW_IC_ADDR_START);
}

/*
 * description : read pram in ic to buf
 *
 * param - buf : buffer to receive pram data
 *
 * param - size : size
 *
 * param - pram_size : firmware data length
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_read_pram_from_ic(
	unsigned char *buf,
	unsigned int size,
	unsigned pram_size)
{
	int i = 0;
	int ret = 0;

	unsigned int data_size = 0;
	unsigned int package_count = 0;
	unsigned int readed_size = 0;

	if (size < pram_size) {
		TS_LOG_ERR("%s:buffer is not enough to receive pram\n",
			__func__);
		TS_LOG_ERR("%s:buffer size=%u, pram size=%u\n", __func__,
			size, pram_size);
		return -ENOMEM;
	}

	package_count = pram_size / FTS_PACKAGE_SIZE;
	if (pram_size % FTS_PACKAGE_SIZE != 0)
		package_count += 1;

	TS_LOG_DEBUG("%s:pram_size=%u, package_count=%u\n", __func__,
		pram_size, package_count);

	for (i = 0; i < package_count; i++) {

		if ((i + 1 == package_count)
			&& (pram_size % FTS_PACKAGE_SIZE != 0)) {
			data_size = pram_size % FTS_PACKAGE_SIZE;
		} else {
			data_size = FTS_PACKAGE_SIZE;
		}

		ret = fts_read_pram_package(readed_size, &buf[readed_size],
			data_size);
		if (ret) {
			TS_LOG_ERR("%s:read pram package error\n", __func__);
			TS_LOG_ERR("%s:read_size=%u, data_size=%u, index=%d\n",
				__func__, readed_size, data_size, i);
			return ret;
		}

		readed_size += data_size;
	}

	return 0;
}

/*
 * description : read pram in ic to buf
 *
 * param - buf : buffer to receive pram data
 *
 * param - size : size
 *
 * param - pram_size : firmware data length
 *
 * return : return 0 if read ic status success, otherwize return error code
 */
static int fts_erasure_app_area(void)
{
	int i = 0;
	int ret = 0;
	unsigned int ic_state = 0;
	unsigned char cmd = 0x00;

	cmd = FTS_CMD_ERASURE_APP;
	ret = fts_i2c_write(&cmd, 1);
	if (ret) {
		TS_LOG_ERR("%s:send erase command fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	msleep(fts_upgrade_delay.erase_min_delay);

	for (i = 0; i < fts_upgrade_delay.erase_flash_max_query_time; i++) {

		ret = fts_get_status(&ic_state);
		if (ret) {
			TS_LOG_ERR("%s:get ic status fail, ret=%d\n",
				__func__, ret);
		} else {
			if (FTS_ERASURE_OK_STATUS == ic_state)
				return 0;
		}

		msleep(fts_upgrade_delay.erase_query_per_time_delay);
	}

	return -EIO;
}

/*
 * return : if success, return 0, otherwize return error code
 *
 * notice : this function is working when ic is in pram model
 */
static int fts_enter_pram_update_model_from_pram(void)
{
	int ret = 0;
	unsigned char cmd[2] = {0};

	cmd[0] = FTS_CMD_SET_MODE;
	cmd[1] = FTS_MODE_UPGRADE;

	ret = fts_i2c_write(cmd, 2);
	if (ret) {
		TS_LOG_ERR("%s:set pram update model fail, ret = %d\n",
			__func__, ret);
		return ret;
	}

	msleep(50);

	return 0;
}

/*
 * return : if success, return 0, otherwize return error code
 */
static int fts_auto_config_clock(void)
{
	int ret = 0;
	unsigned char reg_val = 0;
	unsigned char cmd[3] = {0};

	cmd[0] = FTS_REG_FLASH_TYPE;
	ret = fts_i2c_read(cmd, 1, &reg_val, 1);
	if (ret) {
		TS_LOG_ERR("%s:read flash type fail, ret=%d\n", __func__, ret);
		return ret;
	}

	cmd[0] = FTS_REG_FLASH_TYPE;
	cmd[1] = reg_val;
	cmd[2] = 0x00;

	ret = fts_i2c_write(cmd, 3);
	if (ret) {
		TS_LOG_ERR("%s:%s, flash type=0x%02x, ret=%d\n", __func__,
			"write flash type fail",
			reg_val, ret);
		return ret;
	}

	return 0;
}

/*
 * param - start_addr : addr in ic to start check sum
 *
 * param - crc_length : length of data to check sum
 *
 * param - check_sum : buffer to receive check sum value
 *
 * return : if success, return 0, otherwize return error code
 */
static int fts_read_check_sum(
	unsigned int start_addr,
	unsigned int crc_length,
	unsigned char *check_sum)
{
	int i = 0;
	int ret = 0;

	unsigned int ic_status = 0;

	unsigned char cmd[4] = {0};
	unsigned char reg_val = 0;

	if (crc_length > LEN_FLASH_ECC_MAX) {
		TS_LOG_ERR("%s:%s, crc_length=%u, max=%d\n",
			__func__, "crc length out of range",
			crc_length, LEN_FLASH_ECC_MAX);
		return -EINVAL;
	}

	/* start verify */
	cmd[0] = FTS_CMD_CALC_CRC;
	ret = fts_i2c_write(cmd, 1);
	if (ret) {
		TS_LOG_ERR("%s:start verify fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	msleep(fts_upgrade_delay.calc_crc_delay);

	cmd[0] = FTS_CMD_SET_CALC_ADDR;

	cmd[1] = (unsigned char)(start_addr >> 16);
	cmd[2] = (unsigned char)(start_addr >> 8);
	cmd[3] = (unsigned char)(start_addr);

	cmd[4] = (unsigned char)(crc_length >> 8);
	cmd[5] = (unsigned char)(crc_length);

	ret = fts_i2c_write(cmd, 6);
	if (ret) {
		TS_LOG_ERR("%s:write verify parameter fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	msleep(crc_length / 256);

	cmd[0] = FTS_CMD_GET_STATUS;
	for (i = 0; i < fts_upgrade_delay.read_ecc_max_query_time; i++) {

		ret = fts_get_status(&ic_status);
		if (ret) {
			TS_LOG_ERR("%s:get ic status fail, ret=%d\n",
				__func__, ret);
		} else {
			if (FTS_ECC_OK_STATUS == ic_status)
				break;
		}

		if (i == fts_upgrade_delay.read_ecc_max_query_time - 1) {
			TS_LOG_ERR("%s:%s, out of max retry times\n",
				__func__, "status check fail");
		}

		msleep(1);
	}

	cmd[0] = FTS_CMD_READ_CRC;
	ret = fts_i2c_read(cmd, 1, &reg_val, 1);
	if (ret) {
		TS_LOG_ERR("%s:read crc fail, ret=%d\n", __func__, ret);
		return ret;
	}

	*check_sum = reg_val;

	return 0;
}

/*
 * param - flash_type : buffer to receive flash type
 *
 * return : if success, return 0, otherwize return error code
 */
static int fts_read_flash_type(unsigned char *flash_type)
{
	int ret = 0;

	unsigned char cmd = 0;

	cmd = FTS_REG_FLASH_TYPE;
	ret = fts_i2c_read(&cmd, 1, flash_type, 1);
	if (ret) {
		TS_LOG_ERR("%s:read flash type fail, ret=%d\n", __func__, ret);
		return ret;
	}

	return 0;
}

/*
 * description : fts may use two kinds of memery,
 *               one is winbond and other one is ft5003,
 *               but almost not use ft5003, because ft5003 is made by focal,
 *               and the performance is not very will.
 *
 * param - fw_len : firmware size
 *
 * return : if success, return 0, otherwize return error code
 */
static int fts_check_firmware_size_in_pram_model(unsigned int fw_len)
{
	int ret = 0;
	unsigned char flash_type = 0;
	unsigned int max_fw_len = 0;

	ret = fts_read_flash_type(&flash_type);
	if (ret) {
		TS_LOG_ERR("%s:read flash type fail, ret=%d\n", __func__, ret);
		return ret;
	}

	TS_LOG_INFO("%s:flash type=0x%X\n", __func__, flash_type);

	switch (flash_type) {
	case FTS_FLASH_TYPE_FT5003:
		max_fw_len = FTS_FLASH_MAX_LEN_FT5003;
		break;
	case FTS_FLASH_TYPE_WINBOND:
		max_fw_len = FTS_FLASH_MAX_LEN_WINBOND;
		break;
	default:
		TS_LOG_ERR("%s:%s, flash_type=0x%X\n", __func__,
			"no flash type maech, use default", flash_type);
		max_fw_len = FTS_FLASH_MAX_LEN_WINBOND;
	}

	TS_LOG_INFO("%s:fw_len=%u, max_fw_len=%u\n", __func__,
		fw_len, max_fw_len);

	if (max_fw_len < fw_len) {
		TS_LOG_ERR("%s:firmware length check fail\n", __func__);
		return -ENODATA;
	}

	return 0;
}

/*
 * description : give this function the firmware data,
 *               and the lengthe of the firmware data,
 *               this function can finish firmeare update
 *
 * param - fts_pdata : struct fts_ts_platform_data *fts_pdata
 *
 * param - fw_data : firmware data to update
 *
 * param - fw_len : the length of firmware data
 *
 * return : if success, return 0, otherwize return error code
 */
static int fts_firmware_update(
	struct fts_ts_platform_data *fts_pdata,
	const unsigned char *fw_data,
	unsigned int fw_len)
{
	int ret = 0;

	unsigned char check_sum_of_fw = 0;
	unsigned char check_sum_in_ic = 0;

	ret = fts_enter_pram_model(fts_pdata);
	if (ret) {
		TS_LOG_ERR("%s:enter pram model fail, ret=%d\n", __func__, ret);
		goto enter_work_model_from_pram;
	} else {
		TS_LOG_ERR("%s:enter pram model success\n", __func__);
	}

	ret = fts_check_firmware_size_in_pram_model(fw_len);
	if (ret) {
		TS_LOG_ERR("%s:check firmware size fail, ret-%d\n",
			__func__, ret);
		goto enter_work_model_from_pram;
	}

	fts_get_data_check_sum(fw_data, fw_len, &check_sum_of_fw);

	ret = fts_auto_config_clock();
	if (ret) {
		TS_LOG_ERR("%s:config clock fail, ret=%d\n", __func__, ret);
		goto enter_work_model_from_pram;
	} else {
		TS_LOG_INFO("%s:config clock success\n", __func__);
	}

	ret = fts_enter_pram_update_model_from_pram();
	if (ret) {
		TS_LOG_ERR("%s:enter update model fail, ret=%d\n",
			__func__, ret);
		goto enter_work_model_from_pram;
	} else {
		TS_LOG_INFO("%s:enter update model success\n", __func__);
	}

	ret = fts_erasure_app_area();
	if (ret) {
		TS_LOG_ERR("%s:erasure app fail, ret=%d\n", __func__, ret);
		goto enter_work_model_from_update_model;
	} else {
		TS_LOG_INFO("%s:erasure app success\n", __func__);
	}

	ret = fts_write_app_data(fw_data, fw_len);
	if (ret) {
		TS_LOG_ERR("%s:write app data fail, ret=%d\n", __func__, ret);
		goto enter_work_model_from_update_model;
	} else {
		TS_LOG_INFO("%s:write app data success\n", __func__);
	}

	ret = fts_read_check_sum(FTS_FW_IC_ADDR_START,
		fw_len, &check_sum_in_ic);
	if (ret) {
		TS_LOG_ERR("%s:read check sum in ic fail, ret=%d\n",
			__func__, ret);
		goto enter_work_model_from_update_model;
	}

	TS_LOG_INFO("%s:crc_in_ic=0x%02X, crc_of_fw=0x%02X\n",
			__func__, check_sum_in_ic, check_sum_of_fw);

	if (check_sum_in_ic != check_sum_of_fw) {
		TS_LOG_ERR("%s:check sum check fail\n", __func__);
		ret = -EIO;
	}

enter_work_model_from_update_model:
	if (fts_enter_work_model_form_pram_update()) {
		TS_LOG_ERR("%s:enter work model fail, ret=%d\n", __func__, ret);
	} else {
		TS_LOG_INFO("%s:enter work model success\n", __func__);
		return ret;
	}

enter_work_model_from_pram:
	/* 6. enter work model */
	if (fts_enter_work_model_from_pram()) {
		TS_LOG_ERR("%s:enter work mode from pram fail, ret=%d\n",
			__func__, ret);
	} else {
		TS_LOG_INFO("%s:enter work mode from pram success\n", __func__);
	}

	return ret;
}

/*
 * param - fw_file_path : firmware file path
 *
 * return : if success, return file size, other wize return error code
 */
static int fts_flash_get_fw_file_size(char *fw_file_path)
{
	off_t file_size = 0;
	unsigned long magic = 0;

	struct file *pfile = NULL;
	struct inode *inode = NULL;
#if 0
	if (NULL == fw_file_path) {
		TS_LOG_ERR("%s:fw file path is null\n", __func__);
		return -EINVAL;
	}

	pfile = filp_open(fw_file_path, O_RDONLY, 0);
	if (IS_ERR(pfile)) {
		TS_LOG_ERR("%s:fw file open fail, path=%s\n",
			__func__, fw_file_path);
		return -EIO;
	}

	inode = pfile->f_dentry->d_inode;
	magic = inode->i_sb->s_magic;
	file_size = inode->i_size;
	filp_close(pfile, NULL);
#endif
	return file_size;
}

/*
 * param - fw_file_path : fw file path
 *
 * param - fw_buf : buff to store firmware file data
 *
 * return : if success, return 0, otherwize return error code
 */
static int fts_flash_read_fw_file(
	char *fw_file_path,
	unsigned char *fw_buf)
{
	loff_t pos = 0;
	off_t fsize = 0;
	mm_segment_t old_fs;
	unsigned long magic = 0;

	struct file *pfile = NULL;
	struct inode *inode = NULL;

	if (NULL == fw_file_path || NULL == fw_buf) {
		TS_LOG_ERR("%s:input parameter is null\n", __func__);
		return -EINVAL;
	}

	pfile = filp_open(fw_file_path, O_RDONLY, 0);
	if (IS_ERR(pfile)) {
		TS_LOG_ERR("%s:open firmware file fail, path=%s\n",
			__func__, fw_file_path);
		return -EIO;
	}
#if 0
	inode = pfile->f_dentry->d_inode;
	magic = inode->i_sb->s_magic;
	fsize = inode->i_size;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	pos = 0;
	vfs_read(pfile, fw_buf, fsize, &pos);
	filp_close(pfile, NULL);
	set_fs(old_fs);
#endif
	return NO_ERR;
}

/*
 * param - project_id : the vendor id value
 *
 * param - pram_name : buff to store pram file name
 *
 * param - size : size of #pram_name
 *
 * return : if success, return file size, other wize return error code
 */
int fts_get_pram_file_name(
	struct fts_ts_platform_data *fts_pdata,
	char *pram_name,
	size_t size)
{
	int ret = 0;
	unsigned int chip_id = 0;

	if (NULL == fts_pdata || NULL == pram_name) {
		TS_LOG_ERR("%s:input parameter is null\n", __func__);
		return -EINVAL;
	}

	ret = fts_read_chip_id_from_rom(fts_pdata, &chip_id);
	if (ret) {
		TS_LOG_ERR("%s:read chip id fail, ret=%d\n", __func__, ret);
		return ret;
	}

	return snprintf(pram_name, size, "ts/%s_fts_pram_%x.img",
		g_ts_data.product_name,	chip_id);

}

/*
 * return : if need to update firmware, return 1, else return 0
 */
static int fts_start_app_from_rom_update_model(void)
{
	int ret = 0;

	ret = fts_write_command(FTS_CMD_START_APP);
	if (ret < 0) {
		TS_LOG_INFO("%s:start app fail\n", __func__);
		return ret;
	}

	msleep(10);

	return 0;
}

/*
 * return : if need to update firmware, return 1, else return 0
 */
static int fts_start_pram(void)
{
	int i = 0;
	int ret = 0;

	unsigned int chip_id = 0;
	unsigned char cmd[2] = {0};

	/* 1. start pram */
	TS_LOG_INFO("%s:start pram\n", __func__);
	ret = fts_start_app_from_rom_update_model();
	if (ret) {
		TS_LOG_INFO("%s:start pram fail, ret=%d\n", __func__, ret);
		return ret;
	}

	/* 2. check if pram have start success */
	for (i = 0; i < 5; i++) {

		cmd[0] = FTS_UPGRADE_55;
		cmd[1] = FTS_UPGRADE_AA;
		ret = fts_i2c_write(cmd, 2);
		if (ret < 0) {
			TS_LOG_INFO("%s:write command fail, ret=%d\n",
				__func__, ret);
			continue;
		}

		msleep(10);

		ret = fts_read_chip_id(&chip_id);
		if (ret || chip_id == 0) {
			TS_LOG_ERR("%s:chip id read fail, retry=%d\n",
				__func__, i);
			continue;
		} else {
			TS_LOG_INFO("%s:check chip id success\n",
				__func__);
			return 0;
		}
	}

	return -EINVAL;

}

/*
 * param fts_pdata - fts_ts_platform_data *fts_pdata
 *
 * return : if need to update firmware, return 1, else return 0
 */
static int fts_enter_pram_model(
	struct fts_ts_platform_data *fts_pdata)
{
	int ret = 0;
	char pram_name[PRAM_NAME_DEFAULT_LEN] = {0};
	const struct firmware *pram_fw = NULL;

	struct device *dev = NULL;

	dev = &fts_pdata->fts_platform_dev->dev;

	/* 1. get pram name */
	ret = fts_get_pram_file_name(fts_pdata, pram_name,
		PRAM_NAME_DEFAULT_LEN);
	if (ret >= PRAM_NAME_DEFAULT_LEN) {
		TS_LOG_ERR("%s:pram name buffer overflow\n", __func__);
		return ret;
	}

	TS_LOG_DEBUG("%s:pram name is:%s\n", __func__, pram_name);

	/* 2. request pram */
	ret = request_firmware(&pram_fw, pram_name, dev);
	if (ret) {
		TS_LOG_ERR("%s:request firmware fail, ret=%d, pram name=%s\n",
			__func__, ret, pram_name);
		return ret;
	}

	/* 3. enter bootloader */
	TS_LOG_DEBUG("%s:enter rom update model\n", __func__);
	ret = fts_enter_rom_update_model_by_hardware(fts_pdata);
	if (ret) {
		fts_hardware_reset_to_normal_model(fts_pdata);
		return -ENODEV;
	}

	/* 4. write flash pram */
	ret = fts_flash_pram(fts_pdata, pram_fw->data, pram_fw->size);
	if (ret) {
		TS_LOG_INFO("%s:flash pram fail, ret=%d\n", __func__, ret);
		return ret;
	}

	/* 5. start pram */
	ret = fts_start_pram();
	if (ret) {
		TS_LOG_INFO("%s:start pram fail, ret=%d\n", __func__, ret);
		return ret;
	}

	/* 6. release pram */
	release_firmware(pram_fw);
	pram_fw = NULL;

	return 0;
}

/*
 * param - fts_pdata : fts_ts_platform_data *fts_pdata
 *
 * param - pram_data : pram firmware
 *
 * param - pram_size : pram firmware size
 *
 * return : if need to update firmware, return 1, else return 0
 */
static int fts_flash_pram(
	struct fts_ts_platform_data *fts_pdata,
	const unsigned char *pram_data,
	size_t pram_size)
{
	int i = 0;
	int ret = 0;
	unsigned char *pcheck_buffer = NULL;

	TS_LOG_DEBUG("%s:pram file size is:%lu\n", __func__, pram_size);
	if (pram_size > FTS_MAX_PRAM_SIZE || pram_size == 0) {
		TS_LOG_ERR("%s:pram file size overflow %lu\n",
			__func__, pram_size);
		return -EINVAL;
	}

	TS_LOG_DEBUG("%s:write pram data\n", __func__);
	ret = fts_write_pram_data(pram_data, pram_size);
	if (ret) {
		TS_LOG_ERR("%s: write pram data fail, ret=%d\n", __func__, ret);
		return ret;
	}

	msleep(100);

	pcheck_buffer = (unsigned char *)kmalloc(pram_size, GFP_KERNEL);
	if (NULL == pcheck_buffer) {
		TS_LOG_ERR("%s: malloc mem for pcheck_buffer fail\n", __func__);
		return -ENOMEM;
	}

	TS_LOG_DEBUG("%s:read pram data from ic\n", __func__);
	ret = fts_read_pram_from_ic(pcheck_buffer, pram_size, pram_size);
	if (ret) {
		TS_LOG_ERR("%s: read pram data from ic fail, ret=%d\n",
			__func__, ret);
		goto release_pcheck_buffer;
	}

	for (i = 0; i < pram_size; i++) {
		if (pcheck_buffer[i] != pram_data[i]) {
			TS_LOG_ERR("%s:%s,index=%d, src=0x%02x, cut=0x%02x\n",
				__func__, "pram write check fail,",
				i, pram_data[i], pcheck_buffer[i]);
			ret = -EINVAL;
			goto release_pcheck_buffer;
		}
	}

	ret = 0;

release_pcheck_buffer:
	if (pcheck_buffer != NULL) {
		kfree(pcheck_buffer);
		pcheck_buffer = NULL;
	}

	return ret;
}

/*
 * param - fts_pdata : struct fts_ts_platform_data *fts_pdata
 *
 * param - fw_name : firmware file path
 *
 * return : if success, return 0, otherwize return error code
 */
int fts_flash_upgrade_with_bin_file(
	struct fts_ts_platform_data *fts_pdata,
	char *fw_name)
{
	int ret = 0;
	int fw_size = 0;
	unsigned char *pbt_buf = NULL;

	fw_size = fts_flash_get_fw_file_size(fw_name);
	if (fw_size <= 0) {
		TS_LOG_ERR("%s:get fw file size fail, ret=%d, fw_name=%s\n",
			__func__, fw_size, fw_name);
		return fw_size;
	}

	pbt_buf = (unsigned char *)kzalloc(fw_size + 1, GFP_ATOMIC);
	if (NULL == pbt_buf) {
		TS_LOG_ERR("%s:alloc memory fail\n", __func__);
		return -ENOMEM;
	}

	if (fts_flash_read_fw_file(fw_name, pbt_buf)) {
		TS_LOG_ERR("%s:read fw file data fail\n", __func__);
		kfree(pbt_buf);
		return -EIO;
	}

	 /* call the write pram function */
	ret = fts_enter_pram_model(fts_pdata);
	if (ret) {
		TS_LOG_ERR("%s:write pram fail i_ret = %d\n", __func__, ret);
		return ret;
	} else {
		TS_LOG_INFO("%s:wirte pram success\n", __func__);
	}

	/* call upgrade function */
	ret = fts_firmware_update(fts_pdata, pbt_buf, fw_size);
	if (ret != 0)
		TS_LOG_ERR("%s:upgrade failed. err=%d.\n", __func__, ret);
	else
		TS_LOG_INFO("%s:upgrade successful.\n", __func__);

	fts_enter_work_model();

	kfree(pbt_buf);

	return ret;
}

/*
 * param - fw : const struct firmware *fw
 *
 * param - fw_ver : buffer to receive firmware version
 *
 * return : if success, return 0, otherwize return error code
 */
int fts_get_img_file_version(
	const struct firmware *fw,
	unsigned char *fw_ver)
{
	int fw_len = 0;
	const unsigned char *fw_data = NULL;

	if (NULL == fw || NULL == fw->data) {
		TS_LOG_ERR("%s:fw or fw data is null.\n", __func__);
		return -ENODATA;
	}

	fw_data = fw->data;
	fw_len = fw->size;

	if (fw_len <= FTS_FW_IMG_ADDR_VER) {
		TS_LOG_ERR("%s:fw length is to long, len=%d.\n",
			__func__, fw_len);
		return -ENOMEM;
	}

	*fw_ver = fw_data[FTS_FW_IMG_ADDR_VER];

	return 0;
}

/*
 * param - version : buffer to receive version
 *
 * return : if need to update firmware, return 1, else return 0
 */
int fts_get_ic_firmware_version(unsigned char *version)
{
	int ret = 0;
	unsigned char fw_ver = 0;

	if (NULL == version) {
		TS_LOG_ERR("%s:version is null\n", __func__);
		return -ENOMEM;
	}

	ret = fts_read_reg(FTS_REG_FW_VER, &fw_ver);
	if (ret < 0) {
		TS_LOG_ERR("%s:read firmware version in ic fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	TS_LOG_INFO("%s:fw version in ic is:0x%x\n", __func__, fw_ver);

	*version = fw_ver;

	return 0;
}


/*
 * param - fts_pdata : struct fts_ts_platform_data *fts_pdata
 *
 * param - product_name : struct fts_ts_platform_data *fts_pdata
 *
 * param - fw_name : struct fts_ts_platform_data *fts_pdata
 *
 * param - size : size of fw_name
 *
 * return : if need to update firmware, return 1, else return 0
 */
static int fts_get_firmware_name(
	struct fts_ts_platform_data *fts_pdata,
	const char *product_name,
	char *fw_name,
	size_t size)
{
	int ret = 0;
	char vendor_name[FTS_VENDOR_NAME_LEN] = {0};
	char project_id[FTS_PROJECT_ID_LEN + 1] = {0};

	/*  1. get project id */
	ret = fts_read_project_id_from_pram(fts_pdata,
		project_id, FTS_PROJECT_ID_LEN);
	if (ret) {
		TS_LOG_ERR("%s:get project id fail, ret=%d\n", __func__, ret);
		return ret;
	}

	/* 2. get vendor name */
	ret = fts_get_vendor_name_from_dts(project_id,
		vendor_name, FTS_VENDOR_NAME_LEN);
	if (ret) {
		TS_LOG_ERR("%s:get vendor fail, ret=%d\n", __func__, ret);
		return ret;
	}

	strtolow(project_id, FTS_PROJECT_ID_LEN + 1);
	ret = snprintf(fw_name, size, "ts/%s%s_%s.img",
		product_name, project_id, vendor_name);
	if (ret >= size) {
		TS_LOG_ERR("%s:fw name buffer out of range, ret=%d\n",
			__func__, ret);
		return -ENOMEM;
	}

	TS_LOG_INFO("%s:fw name:%s\n", __func__, fw_name);

	return 0;
}

static int fts_get_data_check_sum(
	const unsigned char *data,
	size_t data_size,
	unsigned char *check_sum)
{
	int i = 0;

	if (NULL == check_sum || NULL == data) {
		TS_LOG_ERR("%s:input parameter is null\n", __func__);
		return -ENODATA;
	}

	/* get check sum */
	for (i = 0; i < data_size; i++)
		*check_sum ^= data[i];

	return 0;
}

static int fts_read_check_sum_in_pram(
	struct fts_ts_platform_data *fts_pdata,
	unsigned int start_addr,
	unsigned int crc_length,
	unsigned char *check_sum)
{
	int ret = 0;

	ret = fts_enter_pram_model(fts_pdata);
	if (ret) {
		TS_LOG_ERR("%s:enter pram model fail, ret=%d\n", __func__, ret);
		goto enter_work_model_from_pram;
	} else {
		TS_LOG_ERR("%s:enter pram model success\n", __func__);
	}

	ret = fts_auto_config_clock();
	if (ret) {
		TS_LOG_ERR("%s:config clock fail, ret=%d\n", __func__, ret);
		goto enter_work_model_from_pram;
	} else {
		TS_LOG_INFO("%s:config clock success\n", __func__);
	}

	ret = fts_enter_pram_update_model_from_pram();
	if (ret) {
		TS_LOG_ERR("%s:enter update model fail, ret=%d\n",
			__func__, ret);
		goto enter_work_model_from_pram;
	} else {
		TS_LOG_INFO("%s:enter update model success\n", __func__);
	}

	ret = fts_read_check_sum(FTS_FW_IC_ADDR_START, crc_length, check_sum);
	if (ret) {
		TS_LOG_ERR("%s:read check sum in ic fail, ret=%d\n",
			__func__, ret);
		goto enter_work_model_from_update_model;
	}

enter_work_model_from_update_model:
	if (fts_enter_work_model_form_pram_update()) {
		TS_LOG_ERR("%s:enter work model fail, ret=%d\n", __func__, ret);
	} else {
		TS_LOG_INFO("%s:enter work model success\n", __func__);
		return ret;
	}

enter_work_model_from_pram:
	/* 6. enter work model */
	if (fts_enter_work_model_from_pram()) {
		TS_LOG_ERR("%s:enter work mode from pram fail, ret=%d\n",
			__func__, ret);
	} else {
		TS_LOG_INFO("%s:enter work mode from pram success\n", __func__);
	}

	return ret;
}

/*
 * param - fw : const struct firmware *fw
 *
 * return : if need to update firmware, return 1, else return 0
 */
static int fts_check_firmware_version(
	struct fts_ts_platform_data *fts_pdata,
	const struct firmware *fw)
{
	int ret = 0;
	char fw_ver_in_ic = 0;
	char fw_ver_in_file = 0;

#ifdef FTS_FIRMWARE_UPDATE_CHECK_CRC
	unsigned char check_sum_in_ic = 0;
	unsigned char check_sum_of_fw = 0;
#endif /* FTS_FIRMWARE_UPDATE_CHECK_CRC */

	ret = fts_get_ic_firmware_version(&fw_ver_in_ic);
	/* if get ic firmware version fail, update firmware direct */
	if (ret || fw_ver_in_ic == 0xEF) {
		TS_LOG_INFO("%s:%s, ret=%d, fw_version_in_ic=%d\n", __func__,
			"firmware in ic is damaged, update firmware",
			ret, fw_ver_in_ic);
		return 1;
	}

	TS_LOG_INFO("%s:firmware version in ic is:%d\n",
		__func__, fw_ver_in_ic);

	ret = fts_get_img_file_version(fw, &fw_ver_in_file);
	/* do not update firmware, because firmware file may be damaged */
	if (ret) {
		TS_LOG_INFO("%s:%s, don't update firmware, ret=%d\n",
			__func__, "firmware file is damaged", ret);
		return 0;
	}

	TS_LOG_INFO("%s:firmware version in file is:%d\n",
		__func__, fw_ver_in_file);

	/* if firmware version is different, update */
	if (fw_ver_in_file != fw_ver_in_ic) {
		TS_LOG_INFO("%s:%s, update firmware\n",
			__func__, "firmware version is different");
		return 1;
	} else {
		TS_LOG_INFO("%s:firmware version is same\n", __func__);
	}

#ifdef FTS_FIRMWARE_UPDATE_CHECK_CRC
	/* crc firmware */
	TS_LOG_INFO("%s:goto check check-sum\n", __func__);
	ret = fts_read_check_sum_in_pram(fts_pdata, FTS_FW_IC_ADDR_START,
		fw->size, &check_sum_in_ic);
	if (ret) {
		TS_LOG_INFO("%s:%s, ret=%d\n", __func__,
			"check sum in ic read fail, update firmware", ret);
		return 1;
	}

	fts_get_data_check_sum(fw->data, fw->size, &check_sum_of_fw);

	TS_LOG_INFO("%s:check_sum_of_fw=0x%X, check_sum_in_ic=0x%x\n",
				__func__, check_sum_of_fw, check_sum_in_ic);
	if (check_sum_of_fw != check_sum_in_ic) {
		TS_LOG_INFO("%s:check sum is different, update firmware\n",
			__func__);
		return 1;
	}
#endif /* FTS_FIRMWARE_UPDATE_CHECK_CRC */

	return 0;
}

/*
 * param - fts_pdata : struct fts_ts_platform_data *fts_pdata
 *
 * param - product_name : any string is ok,
 *                        this string will be used to create firmware file name,
 *                        how to create firmeare file name please see function:
 *                        fts_get_firmware_name
 *
 * return: if read project id success, return 0, else return error code
 */
int fts_firmware_auto_update(
	struct fts_ts_platform_data *fts_pdata,
	const char *product_name)
{
	int ret = 0;
	char fw_name[FTS_FW_NAME_LEN] = {0};

	struct device *dev = NULL;
	const struct firmware *fw = NULL;

	dev = &fts_pdata->fts_platform_dev->dev;

	/* 1. get firmware name */
	ret = fts_get_firmware_name(fts_pdata,
		product_name, fw_name, FTS_FW_NAME_LEN);
	if (ret) {
		TS_LOG_ERR("%s:get firmware name fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	/* 2. request firmware */
	ret = request_firmware(&fw, fw_name, dev);
	if (ret != 0) {
		TS_LOG_ERR("%s:firmware request fail, ret=%d, fw_name=%s\n",
			__func__, ret, fw_name);
		return ret;
	}

	/* 3. compare firmware version */
	ret = fts_check_firmware_version(fts_pdata, fw);
	if (!ret) {
		TS_LOG_INFO("%s:no need to update firmware\n", __func__);
		goto release_fw;
	} else {
		TS_LOG_INFO("%s:going to update firmware\n", __func__);
	}

	/* 4. firmware update */
	ret = fts_firmware_update(fts_pdata, fw->data, fw->size);
	if (ret)
		TS_LOG_ERR("%s:firmware update fail, ret=%d\n",	__func__, ret);

release_fw:
	/* 5. release firmware */
	release_firmware(fw);
	fw = NULL;

	return ret;
}

/*
 * param - fts_pdata : struct fts_ts_platform_data *fts_pdata
 *
 * param - fw_name : frimware name, use this function to update firmware,
 *                   you should put the firmware file to /system/etc/firmware/
 *
 * return: if read project id success, return 0, else return error code
 */
int fts_firmware_manual_update(
	struct fts_ts_platform_data *fts_pdata,
	const char *fw_name)
{
	int ret = 0;
	struct device *dev = NULL;
	const struct firmware *fw = NULL;

	dev = &fts_pdata->fts_platform_dev->dev;

	/* 1. request firmware */
	ret = request_firmware(&fw, fw_name, dev);
	if (ret != 0) {
		TS_LOG_ERR("%s:firmware request fail, ret=%d, fw_name=%s\n",
			__func__, ret, fw_name);
		return ret;
	}

	/* 2. firmware update */
	ret = fts_firmware_update(fts_pdata, fw->data, fw->size);
	if (ret) {
		TS_LOG_ERR("%s:firmware update fail, ret=%d\n",	__func__, ret);
		return ret;
	}

	/* 3. release firmware */
	release_firmware(fw);
	fw = NULL;

	return 0;
}

static int fts_read_vendor_id_in_pram(unsigned char *vendor_id)
{
	int ret = 0;
	unsigned char reg_val = 0;
	unsigned char cmd[4] = {0};

	cmd[0] = FTS_CMD_READ_FLASH;
	cmd[1] = 0x00;
	cmd[2] = FTS_BOOT_VENDER_ID_ADDR1;
	cmd[3] = FTS_BOOT_VENDER_ID_ADDR2;

	ret = fts_i2c_read(cmd, 4, &reg_val, 1);
	if (ret) {
		TS_LOG_ERR("%s:vendor id read fail, ret=%d\n", __func__, ret);
		return ret;
	}

	if (0 == reg_val) {
		TS_LOG_ERR("%s:vendor id read fail\n", __func__);
		return -EINVAL;
	}

	*vendor_id = reg_val;

	return 0;
}

/*
 * param - fts_pdata : struct fts_ts_platform_data *fts_pdata
 *
 * param - vendor_id : buffer to recevice vendor id
 *
 * return: if read project id success, return 0, else return error code
 */
int fts_read_vendor_id(
	struct fts_ts_platform_data *fts_pdata,
	unsigned char *vendor_id)
{
	int i = 0;
	int ret = 0;

	ret = fts_enter_pram_model(fts_pdata);
	if (ret) {
		TS_LOG_ERR("%s:write pram fail, ret=%d\n", __func__, ret);
		goto exit;
	}

	ret = fts_auto_config_clock();
	if (ret) {
		TS_LOG_ERR("%s:auto config clock fail, ret = %d\n",
			__func__, ret);
		goto exit;
	}

	ret = fts_enter_pram_update_model_from_pram();
	if (ret) {
		TS_LOG_ERR("%s:enter pram update model fail, ret=%d\n",
			__func__, ret);
		goto exit;
	}

	for (i = 0; i < fts_upgrade_delay.upgrade_loop_time; i++) {
		ret = fts_read_vendor_id_in_pram(vendor_id);
		if (!ret) {
			break;
		} else {
			TS_LOG_INFO("%s:%s, ret=%d, retry=%d\n",
				__func__, "read vendor id fail", ret, i);
			msleep(5);
		}
	}

exit:
	fts_enter_work_model_from_rom_update();
	fts_enter_work_model_by_hardware();

	return ret;
}

/*
 * param - offset : addr in ic to start read pram
 *
 * param - buf : buffer to recevice pram data
 *
 * param - size : data size will be read
 *
 * return: if read project id success, return 0, else return error code
 */
bool fts_read_pram_package(
	unsigned int offset,
	unsigned char *buf,
	unsigned short size)
{
	int ret = -1;
	unsigned char command[4];

	command[0] = FTS_CMD_READ_PRAM;
	command[1] = 0x00;
	command[2] = offset >> 8;
	command[3] = offset;

	ret = fts_i2c_read(command, 4, buf, size);
	if (ret < 0) {
		TS_LOG_ERR("%s:read pram package fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	return 0;
}


/*
 * param - chip_id : buffer to receive chip id
 *
 * return: if read project id success, return 0, else return error code
 */
int fts_read_chip_id(unsigned int *chip_id)
{
	int ret = 0;
	unsigned char cmd[4] = {0};
	unsigned char reg_val[2] = {0};

	if (NULL == chip_id)
		return -ENOMEM;

	cmd[0] = FTS_REG_BOOT_CHIP_ID;
	cmd[1] = 0x00;
	cmd[2] = 0x00;
	cmd[3] = 0x00;

	ret = fts_i2c_read(cmd, 4, reg_val, 2);
	if (ret) {
		TS_LOG_ERR("%s:read chip id fail, ret=%d\n", __func__, ret);
		return ret;
	}

	*chip_id = (reg_val[0] << 8) | reg_val[1];

	return 0;
}

/*
 * param - fts_pdata : struct fts_ts_platform_data * fts_pdata
 *
 * param - chip_id   : buffer to receive chip id
 *
 * return: if read project id success, return 0, else return error code
 */
int fts_read_chip_id_from_rom(
	struct fts_ts_platform_data *fts_pdata,
	unsigned int *chip_id)
{
	int ret = 0;
	ret = fts_enter_rom_update_model_by_hardware(fts_pdata);
	if (ret) {
		TS_LOG_ERR("%s:enter bootloader fail, ret=%d\n", __func__, ret);
		return ret;
	}

	ret = fts_read_chip_id(chip_id);
	if (ret) {
		TS_LOG_ERR("%s:chip id read fail, ret=%d\n", __func__, ret);
		return ret;
	}

	ret = fts_enter_work_model_from_rom_update();

	return 0;
}

/*
 * return : if read project id success, return 0, else return error code
 *
 * notice : this function is not dependable,
 *          because the value of FTS_WORK_MODE_VALUE is 0,
 *          if read work model fail, the value is also 0,
 *          so we can not guarantee than the ic is in work model
 */
int fts_enter_work_model_by_software(void)
{
	int i = 0;
	int ret = 0;
	unsigned char work_mode = 0;

	for (i = 0; i < FTS_MODEL_SET_NO; i++) {
		/* read ic run mode */
		ret = fts_read_reg(FTS_IC_MODE_ADDR, &work_mode);
		if (ret) {
			TS_LOG_ERR("%s:read work model fail, ret=%d\n",
				__func__, ret);
			return ret;
		}

		/* check if ic is in work mode */
		if (FTS_WORK_MODE_VALUE == work_mode)
			return 0;

		if (i + 1 == FTS_MODEL_SET_NO)
			break;

		/* set to work mode */
		ret = fts_write_reg(FTS_IC_MODE_ADDR, FTS_WORK_MODE_VALUE);
		if (ret) {
			TS_LOG_ERR("%s:write work mode fail, ret=%d\n",
				__func__, ret);
			return ret;
		}

		msleep(20);
	}

	return -ENODEV;
}

/*
 * return: if read project id success, return 0, else return error code
 */
static int fts_enter_work_model_by_hardware(void)
{
	int ret = 0;
	unsigned char work_mode = 0;

	ret = fts_hardware_reset_to_normal_model(fts_platform_data);
	if (ret) {
		TS_LOG_ERR("%s: hardware reset fail, ret=%d\n", __func__, ret);
		return -ENODEV;
	}

	/* check again */
	ret = fts_read_reg(FTS_IC_MODE_ADDR, &work_mode);
	if (ret < 0) {
		TS_LOG_ERR("%s:enter work mode fail, ret=%d\n", __func__, ret);
		return -EIO;
	}

	if (FTS_WORK_MODE_VALUE != work_mode) {
		TS_LOG_ERR("%s:enter work mode fail, mode=%d\n",
			__func__, work_mode);
		return -EINVAL;
	}

	TS_LOG_INFO("%s:enter work mode success\n", __func__);

	return 0;
}

/*
 * return: if read project id success, return 0, else return error code
 *
 * notice : this function is not dependable,
 *          because the value of FTS_WORK_MODE_VALUE is 0,
 *          if read work model fail, the value is also 0,
 *          so we can not guarantee than the ic is in work model
 */
int fts_enter_work_model(void)
{
	int ret = 0;
	ret = fts_enter_work_model_by_software();
	if (ret) {
		TS_LOG_INFO("%s:%s\n", __func__,
			"enter work mode by software fail, try hardware.");
		ret = fts_enter_work_model_by_hardware();
	}

	return ret;
}

/*
 * return: if read project id success, return 0, else return error code
 */
static int fts_enter_work_model_form_pram_update(void)
{
	int ret = 0;
	unsigned char cmd = 0x00;

	cmd = FTS_CMD_REBOOT_APP;
	ret = fts_i2c_write(&cmd, 1);
	if (ret) {
		TS_LOG_ERR("%s:write reboot app command fail, ret = %d\n",
			__func__, ret);
		return ret;
	}

	msleep(fts_upgrade_delay.reboot_delay);
	return 0;
}

/*
 * return: if read project id success, return 0, else return error code
 */
static int fts_enter_work_model_from_rom_update(void)
{
	int ret = 0;
	unsigned char cmd = 0x00;

	/* this command tell ic shift from pram tp app */
	cmd = FTS_REG_RESET_FW;
	ret = fts_i2c_write(&cmd, 1);
	if (ret) {
		TS_LOG_ERR("%s:reset command send fail, ret = %d\n",
			__func__, ret);
		return ret;
	}

	/* make sure CTP startup normally */
//	msleep(fts_platform_data.upgrade_delay_time->reboot_delay);
    msleep(120);

	ret = fts_enter_work_model();

	return ret;
}

/*
 * return: if read project id success, return 0, else return error code
 */
static int fts_enter_work_model_from_pram(void)
{
	return fts_enter_work_model_from_rom_update();
}

int fts_read_project_id_from_app(unsigned char *project_id_out, size_t size)
{
	int ret = 0;
	unsigned char cmd[2] = {0};
	unsigned char project_id[FTS_PROJECT_ID_LEN + 1] = {0};

	cmd[0] = FTS_REG_OFFSET_CODE;
	cmd[1] = 0x20;
	ret = fts_i2c_write(cmd, 2);
	if (ret) {
		TS_LOG_ERR("%s:write offset code fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	cmd[0] = FTS_REG_PROJ_CODE;
	ret = fts_i2c_read(cmd, 1, project_id, FTS_PROJECT_ID_LEN);
	if (ret < 0) {
		TS_LOG_ERR("%s:read app project id error, ret=%d\n",
			__func__, ret);
		return ret;
	} else {
		strncpy(project_id_out, project_id, size);
		TS_LOG_INFO("%s:read project id:%s\n", __func__, project_id);
	}

	return 0;
}

/*
 * name: fts_read_project_id_from_pram
 *
 * param: project_id - buffer to receive project id
 *
 * param: size       - size of project_id
 *
 * return: if read project id success, return 0, else return error code
 *
 * notice: this function may made ic reset
 */
int fts_read_project_id_from_pram(
	struct fts_ts_platform_data *fts_pdata,
	char *project_id,
	size_t size)
{
	int ret = 0;
	int is_read_project_id_success = -EINVAL;

	unsigned int i = 0;
	unsigned char cmd[4] = {0};
	unsigned char reg_val[FTS_PROJECT_ID_LEN + 1] = {0};

	/* 1. enter pram model */
	ret = fts_enter_pram_model(fts_pdata);
	if (ret) {
		TS_LOG_ERR("%s:write pram fail ret = %d\n", __func__, ret);
		goto out;
	} else {
		TS_LOG_INFO("%s:wirte pram success\n", __func__);
	}

	/* 2. config click */
	ret = fts_auto_config_clock();
	if (ret) {
		TS_LOG_ERR("%s:config click fail, ret = %d\n", __func__, ret);
		goto out;
	} else {
		TS_LOG_INFO("%s:config click success\n", __func__);
	}

	/* 3. enter pramboot upgrade mode */
	ret = fts_enter_pram_update_model_from_pram();
	if (ret) {
		TS_LOG_ERR("%s:enter update mode fail, ret=%d\n",
			__func__, ret);
		goto out;
	} else {
		TS_LOG_INFO("%s:enter update mode success\n", __func__);
	}

	cmd[0] = FTS_CMD_READ_FLASH;
	cmd[1] = 0x00;
	cmd[2] = FTS_BOOT_PROJ_CODE_ADDR1;
	cmd[3] = FTS_BOOT_PROJ_CODE_ADDR2;
	for (i = 0; i < fts_upgrade_delay.upgrade_loop_time; i++) {
		reg_val[0] = reg_val[1] = 0x00;
		ret = fts_i2c_write(cmd, 4);
		msleep(1);
		fts_i2c_read(NULL, 0, reg_val, FTS_PROJECT_ID_LEN);
		ret = fts_i2c_read(cmd, 4, reg_val, FTS_PROJECT_ID_LEN);
		if (ret) {
			TS_LOG_ERR("%s:%s, ret=%d, retry=%d\n",
				__func__, "read project id fail", ret, i);
			msleep(5);
			continue;
		}

		if (0 == reg_val[0]) {
			TS_LOG_INFO("%s:read project id fail, retry=%d\n",
				__func__, i);
			msleep(5);
			continue;
		} else {
			memcpy(project_id, reg_val, size);
			is_read_project_id_success = 0;
			break;
		}
	}

	if (is_read_project_id_success == 0)
		TS_LOG_INFO("%s:read project id success\n", __func__);
	else
		TS_LOG_ERR("%s:read project id fail\n", __func__);

out:
	fts_enter_work_model_from_rom_update();
	//fts_enter_work_model_by_hardware();

	return is_read_project_id_success;
}

#define READ_PROJECT_FROM_APP
int fts_read_project_id(
	struct fts_ts_platform_data *fts_pdata,
	char *project_id, size_t size)
{
	int ret = NO_ERR;
	char proj[]="VENS30110";
#ifdef READ_PROJECT_FROM_APP
	memset(project_id, 0, size);
	memcpy(project_id, proj, size);

	ret = fts_read_project_id_from_app(project_id, size);
	if (!ret && strlen(project_id) > 0) {
		TS_LOG_INFO("%s:read project id from app success\n", __func__);
		return 0;
	}
#endif /* READ_PROJECT_FROM_APP */

	ret = fts_read_project_id_from_pram(fts_pdata, project_id, size);
	if (ret) {
		TS_LOG_ERR("%s:read project id from pram fail, ret=%d\n",
			__func__, ret);
		return -EINVAL;
	} else {
		return 0;
	}
}

int fts_flash_init(struct i2c_client *client)
{
	return NO_ERR;
}

int fts_flash_exit(void)
{
	return NO_ERR;
}

