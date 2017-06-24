#include <linux/module.h>
#include <linux/device.h>
#include <linux/time.h>
#include <linux/workqueue.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/hisi/hisi_bootup_keypoint.h>
#include <chipset_common/hwbfm/hwboot_fail_public_interface.h>
#include <chipset_common/hwbfm/hw_boot_fail_core.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/fs.h>

static int g_hw_bfm_enable = 0;

#define BOOT_SATGE_SET_CMD ((int)0x00000001)
#define BOOT_SATGE_GET_CMD BOOT_SATGE_SET_CMD
#define BOOT_FAIL_ERRNO_SET_CMD ((int)0x00000002)
#define BOOT_FAIL_ERRNO_GET_CMD BOOT_FAIL_ERRNO_SET_CMD
#define TIMER_ENABLE_DISABLE_CMD ((int)0x00000003)
#define TIMEOUT_VALUE_SET_CMD ((int)0x00000004)
#define TIMEOUT_VALUE_GET_CMD TIMEOUT_VALUE_SET_CMD

static struct semaphore s_bfm_file_sem;
static int s_latest_cmd = 0;

bool bfmr_is_enabled(void)
{
    return (0 == g_hw_bfm_enable) ? (false) : (true);
}

static int __init early_parse_HW_BFM_MODE_cmdline(char *p)
{
	if (p) {
		if (!strncmp(p, "1", strlen("1"))) {
                   g_hw_bfm_enable = 1;
          }else {
			g_hw_bfm_enable = 0;
            }

		pr_debug("g_hw_bfm_enable is %d\n", g_hw_bfm_enable);
	}
	return 0;
}
early_param("hw_bfm_enable", early_parse_HW_BFM_MODE_cmdline);

struct delayed_work check_bootup_timeout_work;

static void check_bootup_timeout_work_func(struct work_struct *work)
{
    enum BFM_BOOT_STAGE_CODE bootStageCode;
    pr_debug("enter into check_bootup_timeout_work_func\n");
    get_boot_stage(&bootStageCode);
    if (bootStageCode != STAGE_BOOT_SUCCESS){
        pr_err("boot up timeout!\n");
        boot_fail_err(KERNEL_BOOT_TIMEOUT, NO_SUGGESTION, NULL);
	}else{
		pr_info("boot success\n");
	}
    return;
}

static ssize_t bfm_ctl_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int value = -1;

    if(!g_hw_bfm_enable)
	 {
        return -EINVAL;
     }

    switch (s_latest_cmd)
    {
    case BOOT_SATGE_GET_CMD:
        {
            get_boot_stage((enum BFM_BOOT_STAGE_CODE *)&value);
            break;
        }
    case TIMEOUT_VALUE_GET_CMD:
        {
            (void)boot_timer_get((u32 *)&value);
            break;
        }
    default:
        {
            pr_info("File: %s Line: %d invalid CMD: %08x\n", __FILE__, __LINE__, s_latest_cmd);
            return -EINVAL;
        }
    }

    s_latest_cmd = 0;
    up(&s_bfm_file_sem);

    return sprintf(buf, "%x\n", value);
}

static bool bfm_is_file_existed(char *pfile_path)
{
    mm_segment_t oldfs;
    struct stat st;
    int ret = -1;

    if (unlikely(NULL == pfile_path))
    {
        printk(KERN_ERR "func: %s Invalid paramters pfile_path is NULL\n", __func__);
        return false;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    ret = sys_newlstat(pfile_path, &st);
    set_fs(oldfs);

    return (0 == ret) ? (true) : (false);
}

static long bfm_get_file_length(const char *pfile_path)
{
    mm_segment_t oldfs;
    struct stat st;
    long file_length = 0L;

    if (likely(NULL != pfile_path))
    {
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        memset((void *)&st, 0, sizeof(st));
        file_length = (0 == sys_newlstat(pfile_path, &st)) ? ((long)st.st_size) : (0L);
        set_fs(oldfs);
    }

    return file_length;
}

static ssize_t bfm_ctl_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    int cmd;
    int value;
    int sugRcvMethod = 0;
    int field_count = 0;
    char logFilePath[MAX_LOGPATH] = {0};
    int result = -1;
    bool need_up_bfm_file_sem = true; /* It must be true for default */
    enum BFM_BOOT_STAGE_CODE boot_stage = BL1_STAGE_START;
    char *ptemp = NULL;

    if(!g_hw_bfm_enable) {
        printk(KERN_ERR "func: %s Line: %d BFMR is not enabled!\n", __func__, __LINE__);
        return -EINVAL;
    }

    if (unlikely(NULL == buf))
    {
        printk(KERN_ERR "func: %s Line: %d input buf is NULL\n", __func__, __LINE__);
        return -EINVAL;
    }

    /* find the first '/' */
    ptemp = strchr(buf, '/');
    if ((NULL != ptemp) && (strlen(ptemp) > (sizeof(logFilePath) - 1)))
    {
        printk(KERN_ERR "func: %s Line: %d file [%s] len is: %d, > %d!\n", __func__, __LINE__,
            ptemp, strlen(ptemp), (sizeof(logFilePath) - 1));
        return -EINVAL;
    }

    down(&s_bfm_file_sem);
    printk(KERN_ERR "func: %s Line: %d input buf: [%s] count: %u\n", __func__, __LINE__, buf, (unsigned int)count);
    memset(logFilePath, 0, sizeof(logFilePath));
    field_count = sscanf(buf,"0x%x 0x%x %d %s", &cmd, &value, &sugRcvMethod, logFilePath);
    printk(KERN_ERR "func: %s Line: %d parsed param: field_count: %d (cmd: %08x value: %08x sugRcvMethod: %d logFilePath: %s)\n",
        __func__, __LINE__, field_count, cmd, value, sugRcvMethod, logFilePath);
    if (0 != strlen(logFilePath))
    {
        printk(KERN_ERR "func: %s line: %d file [%s] %s, file length: %ld!\n", __func__, __LINE__, logFilePath,
            bfm_is_file_existed(logFilePath) ? "exists" : "dosn't exist", bfm_get_file_length(logFilePath));
    }
    result = count;
    switch (field_count)
    {
    case 4:
        {
            /* Native or Framework set boot fail errno here */
            switch (cmd)
            {
            case BOOT_FAIL_ERRNO_SET_CMD:
                {
                    if (!((value > BL1_ERRNO_START) && (value < BFM_ERRNO_MAX_COUNT)))
                    {
                        pr_info("File: %s Line: %d invalid value\n", __FILE__, __LINE__, value);
                        result = -EINVAL;
                        break;
                    }

                    (void)boot_fail_err((enum BFM_ERRNO_CODE)value,
                        (enum SUGGESTED_RECOVERY_METHOD)sugRcvMethod, logFilePath);
                    break;
                }
            default:
                {
                    pr_info("File: %s Line: %d invalid CMD: %08x\n", __FILE__, __LINE__, cmd);
                    result = -EINVAL;
                    break;
                }
            }

            break;
        }
    case 2:
        {
            /* Native or Framework set boot stage or process timer here  */
            switch (cmd)
            {
            case BOOT_SATGE_SET_CMD:
                {
                    if (!((value > BL1_STAGE_START) && (value <= STAGE_BOOT_SUCCESS)))
                    {
                        pr_info("File: %s Line: %d invalid value\n", __FILE__, __LINE__, value);
                        result = -EINVAL;
                        break;
                    }

                    get_boot_stage(&boot_stage);
                    if ((unsigned int)boot_stage < (unsigned int)(value)) {
                        (void)set_boot_stage((enum BFM_BOOT_STAGE_CODE)(value));
                    }
                    break;
                }
            case TIMER_ENABLE_DISABLE_CMD:
                {
                    boot_timer_set_enable((bool)value);
                    break;
                }
            case TIMEOUT_VALUE_SET_CMD:
                {
                    boot_timer_set((u32)value);
                    break;
                }
            default:
                {
                    pr_info("File: %s Line: %d invalid CMD: %08x\n", __FILE__, __LINE__, cmd);
                    result = -EINVAL;
                    break;
                }
            }
            break;
        }
    case 1:
        {
            /* Native or Framework want to get boot stage or timeout value here */
            switch (cmd)
            {
            case BOOT_SATGE_GET_CMD:
            case TIMEOUT_VALUE_GET_CMD:
                {
                    s_latest_cmd = cmd;
                    need_up_bfm_file_sem = false;
                    break;
                }
            default:
                {
                    pr_info("File: %s Line: %d invalid CMD: %08x\n", __FILE__, __LINE__, cmd);
                    result = -EINVAL;
                    break;
                }
            }
            break;
        }
    default:
        {
            pr_info("File: %s Line: %d invalid input buf: [%s]\n", __FILE__, __LINE__, buf);
            result = -EINVAL;
            break;
        }
    }

    if (need_up_bfm_file_sem)
    {
        up(&s_bfm_file_sem);
    }

    return result;
}

static struct miscdevice hw_bfm_miscdev = {
	.minor = 255,
	.name = "hw_bfm",
};

static DEVICE_ATTR(bfm_ctl, (S_IRUGO | S_IWUSR), bfm_ctl_show,
		   bfm_ctl_store);

#define BOOTUP_TIMEOUT_TIME (3*60)    // 30 minutes

int __init hw_boot_fail_monitor_init(void)
{
    struct timespec curBootUpTime;
    long int leftTimeSec = 0;
    int ret;

	pr_info("%s init start\n", __func__);
    if(!g_hw_bfm_enable) {
	pr_info("func: [%s]hw_bfm system is disabled\n", __func__);
        return 0;
    }

	ret = misc_register(&hw_bfm_miscdev);
	if (0 != ret) {
		pr_err("%s: misc_register failed, ret.%d.\n", __func__, ret);
		return ret;
	}

	ret = device_create_file(hw_bfm_miscdev.this_device, &dev_attr_bfm_ctl);
	if (0 != ret) {
		pr_err("%s: Faield : dev_attr_boot_stage device_create_file.%d\n",
			__func__, ret);
		return ret;
	}

    get_monotonic_boottime(&curBootUpTime);
    leftTimeSec = BOOTUP_TIMEOUT_TIME - curBootUpTime.tv_sec;

    pr_debug("leftTimeSec is %ld\n", leftTimeSec);
    pr_err("leftTimeSec is %ld\n", leftTimeSec);
    BUG_ON(leftTimeSec <= 0);

    sema_init(&s_bfm_file_sem, 1);
    boot_timer_init();
    //INIT_DELAYED_WORK(&check_bootup_timeout_work, check_bootup_timeout_work_func);
    //schedule_delayed_work(&check_bootup_timeout_work, msecs_to_jiffies(leftTimeSec*1000));

    return 0;
}

static void __exit hw_boot_fail_monitor_exit(void)
{
	return;
}

module_init(hw_boot_fail_monitor_init);
module_exit(hw_boot_fail_monitor_exit);

MODULE_LICENSE("GPL");


