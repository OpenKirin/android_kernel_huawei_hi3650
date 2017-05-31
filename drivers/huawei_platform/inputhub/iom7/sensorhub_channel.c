/*
 *  drivers/misc/inputhub/sensorhub_channel.c
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <qindiwen@huawei.com>
 *
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <huawei_platform/inputhub/sensorhub.h>
#include <sensor_detect.h>
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "sensor_info.h"

int first_start_flag;
int ps_first_start_flag;
int txc_ps_flag;
int ams_tmd2620_ps_flag;
int avago_apds9110_ps_flag;
int als_first_start_flag;
int gyro_first_start_flag;
int handpress_first_start_flag;
int rohm_rgb_flag;
int avago_rgb_flag;
extern char sensor_chip_info[SENSOR_MAX][MAX_CHIP_INFO_LEN];
extern int read_gsensor_offset_from_nv(void);
extern int write_gsensor_offset_to_nv(int* temp);
extern int read_airpress_calibrate_data_from_nv(void);
extern int read_gyro_sensor_offset_from_nv(void);
extern int read_handpress_offset_from_nv(void);
/*******************************************************************************************
Function:       shb_read
Description:    ����/dev/sensorhub�ڵ�Ķ���������kernel���¼��������ж�����
Data Accessed:  ��
Data Updated:   ��
Input:          struct file *file, char __user *buf, size_t count, loff_t *pos
Output:         ��
Return:         ʵ�ʶ�ȡ���ݵĳ���
*******************************************************************************************/
static ssize_t shb_read(struct file *file, char __user *buf, size_t count,
              loff_t *pos)
{
    return inputhub_route_read(ROUTE_SHB_PORT,buf, count);
}

static ssize_t shb_write(struct file *file, const char __user *data,
                        size_t len, loff_t *ppos)
{
    hwlog_info("%s need to do...\n", __func__);
    return len;
}
static void get_acc_calibrate_data(void)
{
    int ret = 0;
    if (0 == first_start_flag)
    {
        ret=read_gsensor_offset_from_nv();
        if(ret) hwlog_err( "get_acc_calibrate_data read from nv fail, ret=%d", ret);
        else
        {
            hwlog_info("read nv success\n");
        }
    }
}

extern int read_mag_calibrate_data_from_nv(void);
static void get_mag_calibrate_data(void)
{
    int ret = 0;
    static int mag_first_start_flag = 0;
    if (0 == mag_first_start_flag)
    {
        ret = read_mag_calibrate_data_from_nv();
        if (ret) {
            hwlog_err("%s read mag data from nv or send to iom3 failed, ret=%d\n", __func__, ret);
        } else {
            hwlog_info("%s read mag data from nv and send to iom3 success\n", __func__);
        }
        mag_first_start_flag = 1;
    }
}

extern int read_cap_prox_calibrate_data_from_nv(void);
static void get_cap_prox_calibrate_data(void)
{
    int ret = 0;
    static int cap_prox_first_start_flag = 0;
    if (0 == cap_prox_first_start_flag)
    {
        ret = read_cap_prox_calibrate_data_from_nv();
        if (ret) {
            hwlog_err("%s read cap_prox data from nv or send to iom3 failed, ret=%d\n", __func__, ret);
        } else {
            hwlog_info("%s read cap_prox data from nv and send to iom3 success\n", __func__);
        }
        cap_prox_first_start_flag = 1;
    }
}

static void get_airpress_calibrate_data(void)
{
     int ret = 0;
    static int airpress_first_start_flag = 0;
    if(0 == strlen(sensor_chip_info[AIRPRESS])){
        return;
    }
    if (0 == airpress_first_start_flag)
    {
        ret = read_airpress_calibrate_data_from_nv();
        if (ret) {
            hwlog_err("%s read airpress data from nv or send to iom3 failed, ret=%d\n", __func__, ret);
        } else {
            hwlog_info("%s read airpress data from nv and send to iom3 success\n", __func__);
            airpress_first_start_flag = 1;
        }
    }
}

extern int read_ps_offset_from_nv(void);
static void get_psensor_calibrate_data(void)
{
    int ret = 0;
    if (0 == ps_first_start_flag &&  (txc_ps_flag == 1 || ams_tmd2620_ps_flag == 1 || avago_apds9110_ps_flag == 1))
    {
        ret=read_ps_offset_from_nv();
        if(ret) hwlog_err( "get_ps_calibrate_data read from nv fail, ret=%d", ret);
        else
        {
            hwlog_info("read nv success\n");
        }
    }
}

extern int read_als_offset_from_nv(void);
static void get_als_calibrate_data(void)
{
    int ret = 0;
    if ((0 == als_first_start_flag) && ((rohm_rgb_flag == 1) || (avago_rgb_flag == 1)))
    {
        ret=read_als_offset_from_nv();
        if(ret) hwlog_err( "get_als_calibrate_data read from nv fail, ret=%d", ret);
        else
        {
            hwlog_info("read nv success\n");
        }
    }
}

extern int read_gyro_offset_from_nv(void);
static void get_gyro_calibrate_data(void)
{
    int ret = 0;
    if(0 == strlen(sensor_chip_info[GYRO])){
        return;
    }
    if (0 == gyro_first_start_flag)
    {
        ret=read_gyro_sensor_offset_from_nv();
        if(ret) hwlog_err( "get_gyro_calibrate_data read from nv fail, ret=%d", ret);
        else
        {
            hwlog_info("gyro_sensor read nv success\n");
        }
    }
}

static void get_handpress_calibrate_data(void)
{
	int ret = 0;

	if(0 == strlen(sensor_chip_info[HANDPRESS])) {
		return;
	}
	if (0 == handpress_first_start_flag) {
		ret = read_handpress_offset_from_nv();
		if(ret)
			hwlog_err( "handpress read from nv fail, ret=%d", ret);
		else
			hwlog_info("handpress read nv success\n");
    }
}

static void send_sensor_calib_data(void)
{
        get_acc_calibrate_data();
        get_mag_calibrate_data();
        get_cap_prox_calibrate_data();
        get_airpress_calibrate_data();
        get_psensor_calibrate_data();
        get_als_calibrate_data();
        get_gyro_calibrate_data();
	get_handpress_calibrate_data();
}

/*******************************************************************************************
Function:       shb_ioctl
Description:    ����/dev/sensorhub�ڵ��ioctl��������Ҫ�������ô���������ͻ�ȡMCU�Ƿ����
Data Accessed:  ��
Data Updated:   ��
Input:          struct file *file, unsigned int cmd, unsigned long arg��cmd�������룬arg��������Ĳ���
Output:         ��
Return:         �ɹ�����ʧ����Ϣ
*******************************************************************************************/
static long shb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    /*begin huangwen 20120706*/
    int sensorMcuMode;
    /*end huangwen 20120706*/

    
    switch (cmd) {
    case SHB_IOCTL_APP_ENABLE_SENSOR:
        break;
    case SHB_IOCTL_APP_DISABLE_SENSOR:
        break;
    case SHB_IOCTL_APP_DELAY_SENSOR:
        break;
    /*begin huangwen 20120706*/
    case SHB_IOCTL_APP_GET_SENSOR_MCU_MODE:
        sensorMcuMode = getSensorMcuMode();
        hwlog_info( "isSensorMcuMode [%d]\n", sensorMcuMode );
        if (copy_to_user(argp, &sensorMcuMode, sizeof(sensorMcuMode)))
            return -EFAULT;
        return 0;
        break;
    /*end huangwen 20120706*/
    case SHB_IOCTL_APP_SENSOR_BATCH:
        hwlog_info("shb_ioctl  cmd : batch flush SHB_IOCTL_APP_SENSOR_BATCH\n");
        break;
    case SHB_IOCTL_APP_SENSOR_FLUSH:
        hwlog_info("shb_ioctl  cmd : batch flush SHB_IOCTL_APP_SENSOR_FLUSH\n");
        break;
    default:
        hwlog_err("shb_ioctl unknown cmd : %d\n", cmd);
        return -ENOTTY;
    }
    send_sensor_calib_data();
    return inputhub_route_cmd(ROUTE_SHB_PORT, cmd, arg);

}

/*******************************************************************************************
Function:       shb_open
Description:    ����/dev/sensorhub�ڵ��open��������δʵ��ʵ�ʹ���
Data Accessed:  ��
Data Updated:   ��
Input:          struct inode *inode, struct file *file
Output:         ��
Return:         �ɹ�����ʧ����Ϣ
*******************************************************************************************/
static int shb_open(struct inode *inode, struct file *file)
{
    hwlog_info("%s ok\n", __func__);
    return 0;
}

/*******************************************************************************************
Function:       shb_release
Description:    ����/dev/sensorhub�ڵ��release��������δʵ��ʵ�ʹ���
Data Accessed:  ��
Data Updated:   ��
Input:          struct inode *inode, struct file *file
Output:         ��
Return:         �ɹ�����ʧ����Ϣ
*******************************************************************************************/
static int shb_release(struct inode *inode, struct file *file)
{
    hwlog_info("%s ok\n", __func__);
    return 0;
}

//--------------------------------------
static const struct file_operations shb_fops = {
    .owner      =   THIS_MODULE,
    .llseek     =   no_llseek,
    .read = shb_read,
    .write      =   shb_write,
    .unlocked_ioctl =   shb_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl =   shb_ioctl,
#endif
    .open       =   shb_open,
    .release    =   shb_release,
};

static struct miscdevice senorhub_miscdev = {
    .minor =    MISC_DYNAMIC_MINOR,
    .name =     "sensorhub",
    .fops =     &shb_fops,
};

/*******************************************************************************************
Function:       sensorhub_init
Description:    ����kernel����������ʼ����дָ�룬ע��msic�豸
Data Accessed:  ��
Data Updated:   ��
Input:          ��
Output:         ��
Return:         �ɹ�����ʧ����Ϣ
*******************************************************************************************/
int __init sensorhub_init(void)
{
    int ret;

    if(is_sensorhub_disabled())
	return -1;    

    ret = inputhub_route_open(ROUTE_SHB_PORT);
    if (ret != 0) {
        hwlog_err( "cannot open inputhub route err=%d\n", ret);
        return ret;
    }

    ret = misc_register(&senorhub_miscdev);
    if (ret != 0) {
        inputhub_route_close(ROUTE_SHB_PORT);
        hwlog_err( "cannot register miscdev err=%d\n", ret);
        return ret;
    }

    hwlog_info("%s ok\n", __func__);

    return 0;
}

/*******************************************************************************************
Function:       sensorhub_exit
Description:    �ͷ�kernel����������ʼ����дָ�룬ע��msic�豸
Data Accessed:  ��
Data Updated:   ��
Input:          ��
Output:         ��
Return:         �ɹ�����ʧ����Ϣ
*******************************************************************************************/
void __exit sensorhub_exit(void)
{
    int ret;

    inputhub_route_close(ROUTE_SHB_PORT);
    ret = misc_deregister(&senorhub_miscdev);

    hwlog_info("%s ret=%d\n", __func__, ret);
}

module_init(sensorhub_init);
module_exit(sensorhub_exit);

MODULE_AUTHOR("SensorHub <smartphone@huawei.com>");
MODULE_DESCRIPTION("SensorHub driver");
MODULE_LICENSE("GPL");
