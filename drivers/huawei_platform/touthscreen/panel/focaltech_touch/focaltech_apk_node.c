
#include "focaltech_core.h"

#define FOCALTECH_APK_NODE_INFO \
	"File Version of  focaltech_apk_node.c:  V1.0.0 2016-03-16"

/*ft_rw_iic_drv main device number*/
#define FTS_CHAR_DEVICE_NAME			"ft_rw_iic_drv"
#define FTS_CHAR_DEVICE_MAJOR			210
#define FTS_I2C_RDWR_MAX_QUEUE			36
#define FTS_I2C_SLAVEADDR				11
#define FTS_I2C_RW						12

/* create apk debug channel */
#define PROC_UPGRADE					0
#define PROC_READ_REGISTER				1
#define PROC_WRITE_REGISTER				2
#define PROC_AUTOCLB					4
#define PROC_UPGRADE_INFO				5
#define PROC_WRITE_DATA					6
#define PROC_READ_DATA					7
#define PROC_SET_TEST_FLAG				8
#define FTS_DEBUG_DIR_NAME				"fts_debug"
#define PROC_NAME					"ftxxxx-debug"
#define WRITE_BUF_SIZE					512
#define READ_BUF_SIZE					512

/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* Static variables
*******************************************************************************/

static unsigned char proc_operate_mode			= PROC_UPGRADE;
static struct proc_dir_entry *fts_proc_entry;

/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* Static function prototypes
*******************************************************************************/

/*interface of write proc*/
/************************************************************************
*	Name: fts_proc_write
*  Brief:interface of write proc
* Input: file point, data buf, data len, no use
* Output: no
* Return: data len
***********************************************************************/
static ssize_t fts_proc_write(struct file *filp,
const char __user *buff, size_t count, loff_t *ppos)
{
	unsigned char writebuf[WRITE_BUF_SIZE];
	int buflen = count;
	int writelen = 0;
	int ret = 0;
	char upgrade_file_path[128];
	if (buflen >= WRITE_BUF_SIZE) {
		TS_LOG_DEBUG("%s:buflen is too large", __func__);
		return -EFAULT;
	}
	if (copy_from_user(&writebuf, buff, buflen)) {
		TS_LOG_DEBUG("%s:copy from user error",	__func__);
		return -EFAULT;
	}
	proc_operate_mode = writebuf[0];

	switch (proc_operate_mode) {
	case PROC_UPGRADE:
		memset(upgrade_file_path, 0, sizeof(upgrade_file_path));
		sprintf(upgrade_file_path, "%s", writebuf + 1);
		upgrade_file_path[buflen-1] = '\0';
		TS_LOG_DEBUG("%s",  upgrade_file_path);

		disable_irq(fts_i2c_client->irq);
//		ret = fts_flash_upgrade_with_bin_file(fts_platform_data,
//			upgrade_file_path);
		enable_irq(fts_i2c_client->irq);
		if (ret < 0) {
			TS_LOG_DEBUG("%s:upgrade failed.",  __func__);
			return ret;
		}

	    break;
	case PROC_SET_TEST_FLAG:
		break;
	case PROC_READ_REGISTER:
		writelen = 1;
		ret = fts_i2c_write(writebuf + 1, writelen);
		if (ret < 0) {
			TS_LOG_DEBUG("%s:write iic error",  __func__);
			return ret;
		}
		break;
	case PROC_WRITE_REGISTER:
		writelen = 2;
		ret = fts_i2c_write(writebuf + 1, writelen);
		if (ret < 0) {
			TS_LOG_DEBUG("%s:write iic error",  __func__);
			return ret;
		}
		break;
	case PROC_AUTOCLB:
		TS_LOG_DEBUG("%s: autoclb",  __func__);
		break;
	case PROC_READ_DATA:
	case PROC_WRITE_DATA:
		writelen = count - 1;
		if (writelen > 0) {
			ret = fts_i2c_write(writebuf + 1, writelen);
			if (ret < 0) {
				TS_LOG_DEBUG("%s:write iic error",  __func__);
				return ret;
			}
		}
		break;
	default:
		break;
	}

	return count;
}

/* interface of read proc */
/************************************************************************
*	Name: fts_proc_read
*  Brief:interface of read proc
* Input: point to the data, no use, no use, read len, no use, no use
* Output: page point to data
* Return: read char number
***********************************************************************/
static ssize_t
fts_proc_read(struct file *filp, char __user *buff, size_t count, loff_t *ppos)
{
	int ret = 0;
	int num_read_chars = 0;
	int readlen = 0;
	u8 regvalue = 0x00, regaddr = 0x00;
	unsigned char buf[READ_BUF_SIZE] = {0};

	switch (proc_operate_mode) {
	case PROC_UPGRADE:
		regaddr = 0xA6;
		ret = fts_read_reg(regaddr, &regvalue);
		if (ret < 0)
			num_read_chars =
			sprintf(buf, "%s", "get fw ver failed.");
		else
			num_read_chars =
			sprintf(buf, "cur fw ver:0x%02x", regvalue);
		break;
	case PROC_READ_REGISTER:
		readlen = 1;
		ret = fts_i2c_read(NULL, 0, buf, readlen);
		if (ret < 0) {
			TS_LOG_DEBUG("%s:read iic error",  __func__);
			return ret;
		}
		num_read_chars = 1;
		break;
	case PROC_READ_DATA:
		readlen = count;
		ret = fts_i2c_read(NULL, 0, buf, readlen);
		if (ret < 0) {
			TS_LOG_DEBUG("%s:read iic error",  __func__);
			return ret;
		}

		num_read_chars = readlen;
		break;
	case PROC_WRITE_DATA:
		break;
	default:
		break;
	}

	if (num_read_chars > count) {
		TS_LOG_DEBUG("%s:num_read_chars is too large",  __func__);
		return -EFAULT;
	}
	if (copy_to_user(buff, buf, num_read_chars)) {
		TS_LOG_DEBUG("%s:copy to user error",  __func__);
		return -EFAULT;
	}

	return num_read_chars;
}
static const struct file_operations fts_proc_fops = {
		.owner	= THIS_MODULE,
		.read	= fts_proc_read,
		.write	= fts_proc_write,
};

static int fts_proc_init(void);
static void fts_proc_exit(void);

/*******************************************************************************
* functions body
*******************************************************************************/

int fts_apk_node_init(void)
{
	int err = 0;

	/* show version */
	TS_LOG_DEBUG("call fts_apk_node_init %s ", FOCALTECH_APK_NODE_INFO);

	/* init proc */
	err = fts_proc_init();
	if (err < 0)
		return err;

	return 0;
}

int fts_apk_node_exit(void)
{
	fts_proc_exit();
	return 0;
}

/************************************************************************
* Name: fts_create_apk_debug_channel
* Brief:  create apk debug channel
* Input: i2c info
* Output: no
* Return: success =0
***********************************************************************/
static int fts_proc_init(void)
{

	fts_proc_entry = proc_create(PROC_NAME, 0777, NULL, &fts_proc_fops);

	if (NULL == fts_proc_entry) {
		TS_LOG_INFO("Couldn't create proc entry!");
		return -ENOMEM;
	} else {
		TS_LOG_INFO("Create proc entry success!");
	}

	return 0;
}
/************************************************************************
* Name: fts_release_apk_debug_channel
* Brief:  release apk debug channel
* Input: no
* Output: no
* Return: no
***********************************************************************/
static void fts_proc_exit(void)
{
	if (fts_proc_entry)
		proc_remove(fts_proc_entry);
}

