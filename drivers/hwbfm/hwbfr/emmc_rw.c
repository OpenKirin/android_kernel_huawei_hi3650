/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: emmc_rw.c

    @brief: source file of module-"emmc read write".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/printk.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/thread_info.h>
#include <chipset_common/hwbfm/hwbfr/emmc_rw.h>


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

int read_emmc_part(const char *part_name, unsigned long long offset, char *buf, unsigned long long buf_size)
{
    int fd = -1;
    long long ret = -1;
    //char dev_path[256] = {0};
    mm_segment_t fs = 0;

    if (unlikely(NULL == part_name) || unlikely(NULL == buf))
    {
        printk("Invalid parameters!\n");
        return -1;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(part_name, O_RDONLY, 0);
    if (fd < 0)
    {
        printk("Open file [%s] failed!\n", part_name);
        set_fs(fs);
        return -1;
    }

    ret = sys_lseek(fd, (off_t)offset, SEEK_SET);
    if ((off_t)offset != ret)
    {
        printk("lseek file [%s] offset: %lld failed![ret: %lld]\n", part_name, (off_t)offset, ret);
        sys_close(fd);
        set_fs(fs);
        return -1;
    }

    ret = sys_read(fd, buf, buf_size);
    if ((long long)buf_size != ret)
    {
        printk("read file [%s] failed!buf_size: %lld [%lld]\n", part_name, (long long)buf_size, ret);
        sys_close(fd);
        set_fs(fs);
        return -1;
    }

    sys_close(fd);
    set_fs(fs);

    return 0;
}


int write_emmc_part(const char *part_name, unsigned long long offset, char *buf, unsigned long long buf_size)
{
    int fd = -1;
    long long ret = -1;
    mm_segment_t fs = 0;

    if (unlikely(NULL == part_name) || unlikely(NULL == buf))
    {
        printk("Invalid parameters!\n");
        return -1;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(part_name, O_WRONLY, 0);
    if (fd < 0)
    {
        printk("Open file [%s] failed!\n", part_name);
        set_fs(fs);
        return -1;
    }

    ret = sys_lseek(fd, (off_t)offset, SEEK_SET);
    if ((off_t)offset != ret)
    {
        printk("lseek file [%s] offset: %d failed![ret: %d]\n", part_name, (off_t)offset, ret);
        sys_close(fd);
        set_fs(fs);
        return -1;
    }

    ret = sys_write(fd, buf, buf_size);
    if ((long long)buf_size != ret)
    {
        printk("write file [%s] failed!buf_size: %lld [%lld]\n", part_name, (long long)buf_size, ret);
        sys_close(fd);
        set_fs(fs);
        return -1;
    }

    sys_fsync(fd);
    sys_close(fd);
    set_fs(fs);

    return 0;
}

