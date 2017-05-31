	/*
  * hisilicon efuse driver, hisi_efuse.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */
#include <asm/compiler.h>
#include <linux/compiler.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/cpumask.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/memory.h>
#include <linux/proc_fs.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/smp.h>
#include <linux/hisi/hisi_efuse.h>
#include <linux/dma-mapping.h>
#include <linux/workqueue.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <global_ddr_map.h>

#define EFUSE_DEV_NAME "efuse"
static EFUSE_LOG_LEVEL g_efuse_print_level = log_level_error;
static EFUSEC_DATA g_efusec_data;
static char* g_efusec_attributions[]={
            "efuse_mem_attr_huk",
            "efuse_mem_attr_scp",
            "efuse_mem_attr_authkey",
            "efuse_mem_attr_chipid",
            "efuse_mem_attr_tsensor_calibration",
            "efuse_mem_attr_huk_rd_disable",
            "efuse_mem_attr_authkey_rd_disable",
            "efuse_mem_attr_dbg_class_ctrl",
            "efuse_mem_attr_dieid",
            "efuse_mem_attr_max"
};
#define EFUSE_GROUP_MAX_STRING      "efuse_mem_attr_group_max"
#define EFUSE_MEM_START_ADDRESS     "hisi,share-memory-efuse"
#define GET_GROUP_NUM(width_bit)    (((width_bit) + 31)/32)
#define GET_BYTE_NUM(width_bit)     (GET_GROUP_NUM(width_bit)*4)

#define GET_BITS_WIDTH(width, attr_id) do { \
    width = g_efusec_data.efuse_attrs_parsed_from_dts[(unsigned int)attr_id].bits_width; \
} while (0)

#define efuse_print_info(level, fmt, ...) do {\
    if (level <= g_efuse_print_level) { \
        printk(KERN_ERR fmt, ##__VA_ARGS__); \
    } \
} while (0)


#define EFUSE_FN_GET_DIEID                                       0xc5000001
#define EFUSE_FN_GET_CHIPID                                      0xc5000002
#define EFUSE_FN_SET_CHIPID                                      0xc5000003
#define EFUSE_FN_GET_AUTHKEY                                     0xc5000004
#define EFUSE_FN_SET_AUTHKEY                                     0xc5000005
#define EFUSE_FN_GET_SECURITYDEBUG                               0xc5000006
#define EFUSE_FN_SET_SECURITYDEBUG                               0xc5000007
#define EFUSE_FN_GET_THERMAL                                     0xc5000008
#define EFUSE_FN_TEST_DISPLAY                                    0xc5000009 //lint !e750
#define EFUSE_FN_GET_KCE                                         0xc500000B
#define EFUSE_FN_SET_KCE                                         0xc500000C
#define EFUSE_FN_GET_FREQ                                        0xc500000E
#define EFUSE_FN_SET_HISEE                                0xc5000013
#define EFUSE_FN_GET_HISEE                                0xc5000014

noinline int atfd_hisi_service_efusec_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
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
}

int get_efuse_hisee_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
	int ret;

	if (NULL == pu8Buffer || (u32Length > EFUSE_HISEE_LENGTH_BYTES))
	{
		efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
		return -EFAULT;
	}
	BUG_ON(in_interrupt());
	mutex_lock(&g_efusec_data.efuse_mutex);
	ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_HISEE, (u64)g_efusec_data.buf_phy_addr, u32Length, timeout);
	if (OK == ret)
	{
		memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
	}
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
	return ret;
}


int set_efuse_hisee_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
	{
	int ret;

	if (NULL == pu8Buffer || (u32Length > EFUSE_HISEE_LENGTH_BYTES))
	{
		efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
		return -EFAULT;
	}
	BUG_ON(in_interrupt());
	mutex_lock(&g_efusec_data.efuse_mutex);
	memmove((void *)g_efusec_data.buf_virt_addr, (void *)pu8Buffer, u32Length);
	ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_SET_HISEE, (u64)g_efusec_data.buf_phy_addr, u32Length, timeout);
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
	return ret;
}

int get_efuse_dieid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_DIEID_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
       return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_DIEID, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    if (OK == ret)
    {
        memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
    return ret;
}
int get_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_CHIPID_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
        return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_CHIPID, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    if (OK == ret)
    {
        memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}
int set_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_CHIPID_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
		return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    memmove((void *)g_efusec_data.buf_virt_addr, (void *)pu8Buffer, u32Length);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_SET_CHIPID, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}
int get_efuse_authkey_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_AUTHKEY_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
       return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_AUTHKEY, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    if (OK == ret)
    {
        memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
    }
    mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}
int set_efuse_authkey_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_AUTHKEY_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
       return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    memmove((void *)g_efusec_data.buf_virt_addr, (void *)pu8Buffer, u32Length);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_SET_AUTHKEY, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}
int get_efuse_securitydebug_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_SECDBG_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
       return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_SECURITYDEBUG, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    if (OK == ret)
    {
        memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}
int set_efuse_securitydebug_value(unsigned char *pu8Buffer, unsigned int timeout)
{
	int ret;

	if (NULL == pu8Buffer)
	{
		efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
	   return -EFAULT;
	}
	BUG_ON(in_interrupt());
	mutex_lock(&g_efusec_data.efuse_mutex);
	memmove((void *)g_efusec_data.buf_virt_addr, (void *)pu8Buffer, sizeof(unsigned int));
	ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_SET_SECURITYDEBUG, (u64)g_efusec_data.buf_phy_addr, (u64)0, (u64)timeout);
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
	return ret;
}
int get_efuse_thermal_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_THERMAL_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
       return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_THERMAL, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    if (OK == ret)
    {
        memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}

int get_efuse_freq_value(unsigned char *pu8Buffer, unsigned int u32Length)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length > EFUSE_FREQ_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
       return -EFAULT;
    }
	BUG_ON(in_interrupt());
	mutex_lock(&g_efusec_data.efuse_mutex);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_FREQ, (u64)g_efusec_data.buf_phy_addr, sizeof(unsigned int), (u64)0);
    if (OK == ret)
    {
        memmove((void *)pu8Buffer, (void *)g_efusec_data.buf_virt_addr, u32Length);
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}


int get_efuse_kce_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret = OK;

	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}


int set_efuse_kce_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout)
{
    int ret;

    if (NULL == pu8Buffer || (u32Length != EFUSE_KCE_LENGTH_BYTES))
    {
        efuse_print_info(log_level_error, "%s: %d: pu8Buffer is NULL.\n", __func__, __LINE__);
        return -EFAULT;
    }
	BUG_ON(in_interrupt());
    mutex_lock(&g_efusec_data.efuse_mutex);
    memmove((void *)g_efusec_data.buf_virt_addr, (void *)pu8Buffer, u32Length);
    ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_SET_KCE, (u64)g_efusec_data.buf_phy_addr, (u64)u32Length, (u64)timeout);
    mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}

int bsp_efuse_read(unsigned int * pBuf, const unsigned int group, const unsigned int num)
{
    int ret;
    int bytes;

    if (NULL == pBuf)
    {
        efuse_print_info(log_level_error, "%s: %d: pBuf is NULL.\n", __func__, __LINE__);
        return -EFAULT;
    }
	BUG_ON(in_interrupt());
	mutex_lock(&g_efusec_data.efuse_mutex);
    switch(group)
    {
        case EFUSE_CHIPID_GROUP_START:
            if (EFUSE_CHIPID_GROUP_WIDTH != num)
            {
                efuse_print_info(log_level_error, "bsp_efuse_read, invalid parameters,group=%d, num=%d.\n", group, num);
                ret = ERROR;
				break;
            }
            bytes = num*4;
			ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_CHIPID, (u64)g_efusec_data.buf_phy_addr, bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
			if (OK != ret)
    		{
				efuse_print_info(log_level_error, "%s: %d: get_efuse_chipid_value failed.\n", __func__, __LINE__);
				break;
    		}
			if (pBuf != (unsigned int *)g_efusec_data.buf_virt_addr) {
				memcpy((void *)pBuf, (void *)g_efusec_data.buf_virt_addr, bytes);
			}
            break;
        case EFUSE_DIEID_GROUP_START:
            if (EFUSE_DIEID_GROUP_WIDTH != num)
            {
				efuse_print_info(log_level_error, "bsp_efuse_read, invalid parameters,group=%d, num=%d.\n", group, num);
                ret = ERROR;
				break;
			}
            bytes = num*4;
			ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_DIEID, (u64)g_efusec_data.buf_phy_addr, bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
			if (OK != ret) {
    			efuse_print_info(log_level_error, "%s: %d: get_efuse_dieid_value failed.\n", __func__, __LINE__);
                ret = ERROR;
				break;
    		}
			if (pBuf != (unsigned int *)g_efusec_data.buf_virt_addr) {
				memcpy((void *)pBuf, (void *)g_efusec_data.buf_virt_addr, bytes);
			}
            break;
        case EFUSE_KCE_GROUP_START:
            if (EFUSE_KCE_GROUP_WIDTH != num)
            {
                efuse_print_info(log_level_error, "bsp_efuse_read, invalid parameters,group=%d, num=%d.\n", group, num);
                ret = ERROR;
				break;
            }
            bytes = num*4;
			ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_GET_KCE, (u64)g_efusec_data.buf_phy_addr, bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
			if (OK != ret)
    		{
				efuse_print_info(log_level_error, "%s: %d: get_efuse_dieid_value failed.\n", __func__, __LINE__);
                ret = ERROR;
				break;
    		}
			if (pBuf != (unsigned int *)g_efusec_data.buf_virt_addr) {
				memcpy((void *)pBuf, (void *)g_efusec_data.buf_virt_addr, bytes);
			}
            break;

        default:
            efuse_print_info(log_level_error, "bsp_efuse_read, invalid group=%d\n", group);
            ret = OK;
            break;
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}

int bsp_efuse_write(unsigned int *pBuf, const unsigned int group, const unsigned int num)
{
    int ret;
    int bytes;

    if (NULL == pBuf)
    {
        efuse_print_info(log_level_error, "%s: %d: pBuf is NULL.\n", __func__, __LINE__);
        return -EFAULT;
    }
	BUG_ON(in_interrupt());
	mutex_lock(&g_efusec_data.efuse_mutex);
    switch(group)
    {
        case EFUSE_KCE_GROUP_START:
            if (EFUSE_KCE_GROUP_WIDTH != num)
            {
                efuse_print_info(log_level_error, "bsp_efuse_write, invalid parameters,group=%d, num=%d.\n", group, num);
                ret = ERROR;
				break;
            }
            bytes = num*4;
			if (pBuf != (unsigned int *)g_efusec_data.buf_virt_addr) {
				memcpy((void *)g_efusec_data.buf_virt_addr, (void *)pBuf, bytes);
			}
			ret = g_efusec_data.invoke_efuse_fn(EFUSE_FN_SET_KCE, (u64)g_efusec_data.buf_phy_addr, bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
			if (OK != ret)
    		{
				efuse_print_info(log_level_error, "%s: %d: set_efuse_kce_value failed.\n", __func__, __LINE__);
    		}
            break;
        default:
            efuse_print_info(log_level_error, "bsp_efuse_write, invalid group=%d\n", group);
            ret = OK;
            break;
    }
	mutex_unlock(&g_efusec_data.efuse_mutex);
	efuse_print_info(log_level_error, "%s: ret=%d.\n", __func__, ret);
    return ret;
}




/*
 * Function name:efusec_ioctl.
 * Discription:complement read/write efuse by terms of sending command-words.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static long efusec_ioctl(struct file *file, u_int cmd, u_long arg)
{
	int ret = OK;
	void __user *argp = (void __user *)arg;
	int i;
	unsigned int bits_width, bytes;
	/*20 bytes be enough for these efuse field now, need to make larger if
	 *the length of efuse field more than 20!
	 */
	unsigned char buffer[20] = {0};

    efuse_print_info(log_level_error, "%s: %d: cmd=0x%x.\n", __func__, __LINE__, cmd);
	if (!arg) {
		ret = -EFAULT;
		return ret;
	}
	switch (cmd) {
	case HISI_EFUSE_READ_CHIPID:
	    GET_BITS_WIDTH(bits_width, efuse_mem_attr_chipid);
		bytes = GET_BYTE_NUM(bits_width);
		ret = get_efuse_chipid_value(&buffer[0], bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
		if (OK != ret )
		{
			efuse_print_info(log_level_error, "%s: %d: get_efuse_chipid_value failed,ret=%d\n", __func__, __LINE__, ret);
			break;
		}

		for (i = 0; i < bytes; i++)
		{
			efuse_print_info(log_level_error, "line%d, get_efuse_chipid_value[%d] = %2x.\n", __LINE__, i, buffer[i]);
		}

		/*send back to user*/
		if (copy_to_user(argp, &buffer[0], bytes))
		{
			ret = -EFAULT;
		}

		break;
	case HISI_EFUSE_WRITE_CHIPID:
		GET_BITS_WIDTH(bits_width, efuse_mem_attr_chipid);
		bytes = GET_BYTE_NUM(bits_width);
        /*get data from user*/
		if (copy_from_user(&buffer[0], argp, bytes))
		{
			ret = -EFAULT;
			break;
		}
		for (i = 0; i < bytes; i++)
		{
			efuse_print_info(log_level_error, "line%d, set_efuse_chipid_value[%d] = %2x.\n", __LINE__, i, buffer[i]);
		}
		ret = set_efuse_chipid_value(&buffer[0], bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
		if (OK != ret )
		{
			efuse_print_info(log_level_error, "%s: %d: efuse_set_chipID failed,ret=%d\n", __func__, __LINE__, ret);
		}

		break;
	case HISI_EFUSE_READ_CHIPIDLEN:
        GET_BITS_WIDTH(bits_width, efuse_mem_attr_chipid);

		/*send back to user*/
		if (copy_to_user(argp, &bits_width, sizeof(bits_width)))
		{
			ret = -EFAULT;
		}

		break;
	case HISI_EFUSE_READ_AUTHKEY:
	    GET_BITS_WIDTH(bits_width, efuse_mem_attr_authkey);
		bytes = GET_BYTE_NUM(bits_width);
		ret = get_efuse_authkey_value(&buffer[0], bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
		if (OK != ret)
		{
            efuse_print_info(log_level_error, "%s: %d: get_efuse_authkey_value failed,ret=%d\n", __func__, __LINE__, ret);
			break;
		}

        for (i = 0; i < bytes; i++)
        {
            efuse_print_info(log_level_error, "line%d, get_efuse_authkey_value[%d] = %2x.\n", __LINE__, i, buffer[i]);
        }

		/*send back to user*/
        if (copy_to_user(argp, &buffer[0], bytes))
		{
            ret = -EFAULT;
        }

		break;
	case HISI_EFUSE_WRITE_AUTHKEY:
        GET_BITS_WIDTH(bits_width, efuse_mem_attr_authkey);
		bytes = GET_BYTE_NUM(bits_width);
        /*get data from user*/
		if (copy_from_user(&buffer[0], argp, bytes)) {
			ret = -EFAULT;
			break;
		}
		for (i = 0; i < bytes; i++)
		{
			efuse_print_info(log_level_error, "line%d, set_efuse_authkey_value[%d] = %2x.\n", __LINE__, i, buffer[i]);
		}

		ret = set_efuse_authkey_value(&buffer[0], bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
		if (OK != ret)
		{
			efuse_print_info(log_level_error, "%s: %d: set_efuse_authkey_value failed,ret=%d\n", __func__, __LINE__, ret);
		}
		break;
	case HISI_EFUSE_READ_DEBUGMODE:
	    GET_BITS_WIDTH(bits_width, efuse_mem_attr_huk_rd_disable);
		bytes = GET_BYTE_NUM(bits_width);
		ret = get_efuse_securitydebug_value(&buffer[0], bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
		if (OK != ret)
		{
            efuse_print_info(log_level_error, "%s: %d: efuse_get_SecureDebugMode failed,ret=%d\n", __func__, __LINE__, ret);
            break;
        }

        efuse_print_info(log_level_info, "line%d: get_efuse_securitydebug_value = %2x.\n", __LINE__, *((int *)&buffer[0]));

		/*send back to user*/
		if (copy_to_user(argp, &buffer[0], bytes))
		{
			ret = -EFAULT;
			break;
		}

		break;
	case HISI_EFUSE_WRITE_DEBUGMODE:
	    GET_BITS_WIDTH(bits_width, efuse_mem_attr_huk_rd_disable);
	    bytes = GET_BYTE_NUM(bits_width);
		/*get data from user*/
		if (copy_from_user(&buffer[0], argp, bytes))
		{
			ret = -EFAULT;
			break;
		}

		efuse_print_info(log_level_debug, "line%d: set_efuse_securitydebug_value = %2x.\n", __LINE__, *((int *)&buffer[0]));

		ret = set_efuse_securitydebug_value(&buffer[0], EFUSE_MAILBOX_TIMEOUT_1000MS);
		if (OK != ret)
		{
			efuse_print_info(log_level_error, "%s: %d: efuse_set_SecureDebugMode failed,ret=%d\n", __func__, __LINE__, ret);
		}

		break;
    case HISI_EFUSE_READ_DIEID:
	    GET_BITS_WIDTH(bits_width, efuse_mem_attr_dieid);
		bytes = GET_BYTE_NUM(bits_width);
        ret = get_efuse_dieid_value(&buffer[0], bytes, EFUSE_MAILBOX_TIMEOUT_1000MS);
        if (OK != ret)
		{
            efuse_print_info(log_level_error, "%s: %d: get_efuse_dieid_value failed,ret=%d\n", __func__, __LINE__, ret);
            break;
        }

        for (i = 0; i < bytes; i++)
        {
            efuse_print_info(log_level_debug, "line%d, get_efuse_dieid_vlaue[%d] = %2x.\n", __LINE__, i, buffer[i]);
        }

        /*send back to user*/
        if (copy_to_user(argp, &buffer[0], bytes))
		{
            ret = -EFAULT;
        }

        break;



	default:
	    efuse_print_info(log_level_error, "[EFUSE][%s] Unknow command!\n", __func__);
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static const struct file_operations efusec_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = efusec_ioctl,
};

static int __init hisi_efusec_init(void)
{
	int ret = 0;
	int major = 0;
	struct class *efuse_class;
    struct device *pdevice;
	struct device_node *np = NULL;
	unsigned int bit_width;
	unsigned int i;
	u32 data[2] = {0};
	phys_addr_t bl31_smem_base = HISI_SUB_RESERVED_BL31_SHARE_MEM_PHYMEM_BASE;

	memset(&g_efusec_data, 0, sizeof(g_efusec_data));
    np = of_find_compatible_node(NULL, NULL, "hisilicon, efuse");
    if (!np)
    {
        efuse_print_info(log_level_error, "hisi efuse: No efusec compatible node found.\n");
        return -ENODEV;
    }
    if (OK != (ret = of_property_read_u32(np, EFUSE_GROUP_MAX_STRING, &(g_efusec_data.efuse_group_max))))
    {
        if (-EINVAL == ret)
        {
            efuse_print_info(log_level_error, "%s in efusec compatible node does not exist\n", EFUSE_GROUP_MAX_STRING);
        }
        else
        {
            efuse_print_info(log_level_error, "%s in efusec compatible node has invalid value\n", EFUSE_GROUP_MAX_STRING);
        }
        return ret;
    }

    /* currently, parse the dts configurations follow the strategy:
     * 1.Assume the values in correspondings attribution is correct both for Balong and K3V3+ platfrom, so the values in DTS must be filled correctly;
     * 2.Assume to parse the attributions one by one according to g_efusec_attributions[] until one does not exist, treat it as failure, so these attributions
     * contained in g_efusec_attributions[] must be configured in dts;
     * 3.if the value are 0xffffffff, indicate the attribution is reserved for future use, it's process depend on software. A example is the dieid attribution.
     */
    for (i = 0; i < (unsigned int)efuse_mem_attr_max; i++)
    {
        if (OK != (ret = of_property_read_u32(np, g_efusec_attributions[i], &bit_width)))
        {
            if (-EINVAL == ret)
            {
                efuse_print_info(log_level_error, "%d: %s in efusec compatible node does not exist\n", i, g_efusec_attributions[i]);
            }
            else
            {
                efuse_print_info(log_level_error, "%d: %s in efusec compatible node has invalid value\n", i, g_efusec_attributions[i]);
            }
            return ret;
        }
        efuse_print_info(log_level_debug, "%d: %s in efusec compatible node value::%d\n", i, g_efusec_attributions[i], bit_width);
        g_efusec_data.efuse_attrs_parsed_from_dts[i].bits_width = bit_width;
    }

    efuse_print_info(log_level_debug, "g_efusec_data.efuse_group_max=%d, parse the dts configuration success\n", g_efusec_data.efuse_group_max);

	/*�����ַ����豸�ļ��ڵ�*/
	major = register_chrdev(0, EFUSE_DEV_NAME, &efusec_fops);
	if (major <= 0)
	{
		ret = -EFAULT;
		efuse_print_info(log_level_error, "hisi efuse: unable to get major for memory devs.\n");
		return ret;
	}

	efuse_class = class_create(THIS_MODULE, EFUSE_DEV_NAME);
	if (IS_ERR(efuse_class))
	{
		ret = -EFAULT;
		efuse_print_info(log_level_error, "hisi efuse: class_create error.\n");
		goto error1;
	}

	pdevice = device_create(efuse_class, NULL, MKDEV(major, 0), NULL, EFUSE_DEV_NAME);
	if (IS_ERR(pdevice))
	{
		ret = -EFAULT;
		efuse_print_info(log_level_error, "hisi efuse: device_create error.\n");
		goto error2;
	}

	g_efusec_data.invoke_efuse_fn = atfd_hisi_service_efusec_smc;
	mutex_init(&(g_efusec_data.efuse_mutex));

/*
 * in 64bit arch, the share memory block between kernel and bl31 exist the cache coherence problem. So in 64bit arch, the memory
 * block allocated by dma_alloc_coherent.
 * Because bl31 enable date cache and create the mmu page table, so the share memory be requested from reserved memory, not allocate dynamically
 */
    np = of_find_compatible_node(NULL, NULL, EFUSE_MEM_START_ADDRESS);
    if (!np)
    {
        efuse_print_info(log_level_error, "hisi efuse: No share-memory-efuse compatible node found.\n");
        goto error2;
    }

    if (OK != (ret = of_property_read_u32_array(np, "reg", &data[0], 2))) {
        if (-EINVAL == ret) {
            efuse_print_info(log_level_error, "%s in bl31-kernel-shared-memory compatible node does not exist\n", "reg");
        }
        else {
            efuse_print_info(log_level_error, "%s in bl31-kernel-shared-memory compatible node has invalid value\n","reg");
        }
        goto error2;
    }
    g_efusec_data.buf_phy_addr = bl31_smem_base + data[0];
    g_efusec_data.buf_virt_addr = (unsigned char *)ioremap(bl31_smem_base + data[0], data[1]);
    if (NULL == g_efusec_data.buf_virt_addr) {
        ret = -EFAULT;
        efuse_print_info(log_level_error, "%s: %d: allocate memory for g_efusec_data.buf_virt_addr failed.\n", __func__, __LINE__);
        goto error2;
    }
	efuse_print_info(log_level_error, "g_efusec_data.buf_phy_addr=0x%lx, g_efusec_data.buf_virt_addr=0x%lx, efuse init success", (unsigned long)g_efusec_data.buf_phy_addr, (unsigned long)g_efusec_data.buf_virt_addr);
	return ret;
error2:
	class_destroy(efuse_class);
error1:
	unregister_chrdev(major, EFUSE_DEV_NAME);
	return ret;

}


rootfs_initcall(hisi_efusec_init);

MODULE_DESCRIPTION("Hisilicon efuse module");
MODULE_AUTHOR("lvtaolong@huawei.com.sh");
MODULE_LICENSE("GPL");

