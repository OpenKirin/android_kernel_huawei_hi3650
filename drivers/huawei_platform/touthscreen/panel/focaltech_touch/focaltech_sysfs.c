
#include "focaltech_core.h"
#include "focaltech_flash.h"

/*
 * Name: fts_get_fw_version_show
 * Brief:  show tp fw vwersion
 * Input: device, device attribute, char buf
 * Output: no
 * Return: char number
 */
static ssize_t fts_get_fw_version_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int ret = 0;
	u8 fwver = 0;
	ssize_t size = 0;

	mutex_lock(&fts_input_dev->mutex);
	ret = fts_read_reg(FTS_REG_FW_VER, &fwver);
	if (ret < 0) {
		TS_LOG_ERR("Failed to get fw version, ret = %d\n", ret);
		mutex_unlock(&fts_input_dev->mutex);
		return -ENODEV;
	}

	if (fwver == 255) {
		size = snprintf(buf, PAGE_SIZE, "get tp fw version fail!");
		TS_LOG_DEBUG("Failed to get fw version! Error value.");
	} else {
		size = snprintf(buf, PAGE_SIZE, "FW Version: %02X\n", fwver);
		TS_LOG_DEBUG("FW Version = 0x%02x.",  fwver);
	}

	mutex_unlock(&fts_input_dev->mutex);

	return size;
}

/*
 * Name: fts_get_fw_version_store
 * Brief:  no
 * Input: device, device attribute, char buf, char count
 * Output: no
 * Return: EPERM
 */
static ssize_t fts_get_fw_version_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	/* place holder for future use */
	return -EPERM;
}

/*
 * Name: fts_hw_reset_show
 * Brief:  set hardware reset
 * Input: device, device attribute, char buf
 * Output: no
 * Return: char number
 */
static ssize_t fts_hw_reset_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int ret = 0;
	ssize_t size = 0;

	ret = fts_hardware_reset_to_normal_model(fts_platform_data);

	if (ret < 0) {
		size = snprintf(buf, PAGE_SIZE, "Failed to reset TP!\n");
		TS_LOG_INFO("Failed to reset TP!");
	} else {
		size = snprintf(buf, PAGE_SIZE, "Reset TP succeeded.\n");
		TS_LOG_INFO("Reset TP succeeded.");
	}

	return size;
}

static ssize_t fts_hw_reset_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	/* place holder for future use */
	return -EPERM;
}

/*
 * Name: fts_read_reg_show
 * Brief:  no
 * Input: device, device attribute, char buf
 * Output: no
 * Return: EPERM
 */
static ssize_t fts_read_reg_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	/* place holder for future use */
	return -EPERM;
}

/*
 * Name: fts_read_reg_store
 * Brief:  read/write register
 * Input: device, device attribute, char buf, char count
 * Output: print register value
 * Return: char count
 */
static ssize_t fts_read_reg_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	ssize_t size = 0;
	u8 reg_addr = 0xff;
	u8 reg_value = 0xff;
	u8 val_buf[5] = {0};
	unsigned long int wm_reg = 0;

	memset(val_buf, 0, sizeof(val_buf));
	mutex_lock(&fts_input_dev->mutex);
	size = count - 1;
	if (size != 2) {
		TS_LOG_ERR("%s\n",
			"please input 2 character, e.g: echo a6 > fts_read_reg");
		goto error_return;
	}

	memcpy(val_buf, buf, size);
	ret = kstrtoul(val_buf, 16, &wm_reg);
	if (0 != ret) {
		TS_LOG_DEBUG("Parse input number fail, input is:%s\n", buf);
		goto error_return;
	}

	/* read register */
	reg_addr = wm_reg;
	TS_LOG_INFO("Read Reg : (Addr = 0x%02x)\n", reg_addr);

	ret = fts_read_reg(reg_addr, &reg_value);
	if (ret < 0)
		TS_LOG_ERR("Could not read the reg(0x%02x)\n", reg_addr);
	else
		TS_LOG_INFO("read reg success, addr=0x%02x, value=0x%02x\n",
			reg_addr, reg_value);

error_return:
	mutex_unlock(&fts_input_dev->mutex);

	return count;

}
/*
 * Name: fts_write_reg_show
 * Brief:  no
 * Input: device, device attribute, char buf
 * Output: no
 * Return: EPERM
 */
static ssize_t fts_write_reg_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	/* place holder for future use */
	return -EPERM;
}

/*
 * Name: fts_write_reg_store
 * Brief:  read/write register
 * Input: device, device attribute, char buf, char count
 * Output: print register value
 * Return: char count
 */
static ssize_t fts_write_reg_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	ssize_t size = 0;

	u8 reg_addr = 0xff;
	u8 reg_value = 0xff;
	u8 val_buf[5] = {0};

	unsigned long int wm_reg = 0;

	memset(val_buf, 0, sizeof(val_buf));
	mutex_lock(&fts_input_dev->mutex);
	size = count - 1;

	TS_LOG_INFO("input buff = %s, size = %d", buf, (int)count);

	if (size != 4) {
		TS_LOG_ERR("%s%s\n",
			"please input 4 character,",
			" e.g: echo a601 > fts_write_reg");
		goto error_return;
	}

	memcpy(val_buf, buf, size);
	ret = kstrtoul(val_buf, 16, &wm_reg);
	if (0 != ret) {
		TS_LOG_ERR("parse input number fail, input = %s\n", buf);
		goto error_return;
	}

	reg_addr = wm_reg >> 8;
	reg_value = wm_reg;
	ret = fts_write_reg(reg_addr, reg_value);
	if (ret < 0)
		TS_LOG_ERR("Could not write the reg(0x%02x)", reg_addr);
	else
		TS_LOG_INFO("Write 0x%02x into reg(0x%02x) successfully",
			reg_value, reg_addr);

error_return:
	mutex_unlock(&fts_input_dev->mutex);

	return count;
}

/*
 * Name: fts_upgrade_i_file_show
 * Brief:  no
 * Input: device, device attribute, char buf
 * Output: no
 * Return: EPERM
 */
static ssize_t fts_upgrade_i_file_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	/* place holder for future use */
	return -EPERM;
}

/*
 * Name: fts_upgrade_i_file_store
 * Brief:  upgrade from *.i
 * Input: device, device attribute, char buf, char count
 * Output: no
 * Return: char count
 */
static ssize_t fts_upgrade_i_file_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	return count;
}
/*
 * Name: fts_upgrade_bin_file_show
 * Brief:  no
 * Input: device, device attribute, char buf
 * Output: no
 * Return: EPERM
 */
static ssize_t fts_upgrade_bin_file_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	/* place holder for future use */
	return -EPERM;
}

/*
 * Name: fts_upgrade_bin_file_store
 * Brief:  upgrade from app.bin
 * Input: device, device attribute, char buf, char count
 * Output: no
 * Return: char count
 */
static ssize_t fts_upgrade_bin_file_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	char fw_name[128] = {0};
	struct i2c_client *client = fts_i2c_client;

	memset(fw_name, 0, sizeof(fw_name));
	sprintf(fw_name, "%s", buf);
	fw_name[count - 1] = '\0';

	mutex_lock(&fts_input_dev->mutex);

	disable_irq(client->irq);
//	fts_flash_upgrade_with_bin_file(fts_platform_data, fw_name);
	enable_irq(client->irq);

	mutex_unlock(&fts_input_dev->mutex);

	return count;
}

/*
 * upgrade from *.i
 * example: echo 1.i > fts_upgrade_i_file
 */
static DEVICE_ATTR(fts_upgrade_i_file, S_IRUGO | S_IWUSR,
	fts_upgrade_i_file_show, fts_upgrade_i_file_store);

/*
 * upgrade from app.bin
 * example:echo "*_app.bin" > fts_upgrade_bin_file
 */
static DEVICE_ATTR(fts_upgrade_bin_file, S_IRUGO | S_IWUSR,
	fts_upgrade_bin_file_show, fts_upgrade_bin_file_store);

/*
 * read and write register
 * read example: echo 88 > fts_rw_reg ---read register 0x88
 * note:the number of input must be 4.if it not enough,please fill in the 0.
 */
static DEVICE_ATTR(fts_read_reg, S_IRUGO | S_IWUSR,
	fts_read_reg_show, fts_read_reg_store);

/*
 * read and write register
 * write example:echo 8807 > fts_rw_reg ---write 0x07 into register 0x88
 * note:the number of input must be 2 or 4.
 *      if it not enough, please fill in the 0.
 */
static DEVICE_ATTR(fts_write_reg, S_IRUGO | S_IWUSR,
	fts_write_reg_show, fts_write_reg_store);

/* set hardware reset
 * example:cat fts_hw_reset
 */
static DEVICE_ATTR(fts_hw_reset, S_IRUGO | S_IWUSR,
	fts_hw_reset_show, fts_hw_reset_store);

static DEVICE_ATTR(fts_get_fw_version, S_IRUGO | S_IWUSR,
	fts_get_fw_version_show, fts_get_fw_version_store);

/* add your attr in here*/
static struct attribute *fts_attributes[] = {
	&dev_attr_fts_get_fw_version.attr,
	&dev_attr_fts_upgrade_i_file.attr,
	&dev_attr_fts_upgrade_bin_file.attr,
	&dev_attr_fts_read_reg.attr,
	&dev_attr_fts_write_reg.attr,
	&dev_attr_fts_hw_reset.attr,
	NULL
};

static struct attribute_group fts_attribute_group = {
	.attrs = fts_attributes
};

/*
 * Name: fts_sysfs_init
 * Brief:  create sysfs for debug
 * Input: i2c info
 * Output: no
 * Return: success =0
 */
int fts_sysfs_init(struct i2c_client *client)
{
	int ret = 0;

	TS_LOG_INFO("fts sysfs init called\n");

	ret = sysfs_create_group(&client->dev.kobj, &fts_attribute_group);
	if (0 != ret) {
		TS_LOG_ERR("sysfs_create_group() failed, ret=%d\n", ret);
		sysfs_remove_group(&client->dev.kobj, &fts_attribute_group);
		return -EIO;
	} else {
		TS_LOG_INFO("sysfs_create_group() succee.");
	}

	return ret;
}

/*
 * Name: fts_sysfs_exit
 * Brief:  remove sysfs
 * Input: i2c info
 * Output: no
 * Return: no
 */
int fts_sysfs_exit(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &fts_attribute_group);
	return 0;
}

