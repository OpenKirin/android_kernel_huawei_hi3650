#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/thread_info.h>
#include <linux/hardirq.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/kthread.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/syscalls.h>
#include <linux/preempt.h>
#include <asm/cacheflush.h>
#include <linux/kmsg_dump.h>
#include <linux/slab.h>
#include <linux/kdebug.h>
#include <linux/dirent.h>

//to deal with compile error
#include <linux/vmalloc.h>
#include <linux/hisi/kirin_partition.h>
#include <linux/mfd/hisi_pmic.h>
#include <hisi_partition.h>

#include <linux/time.h>
#include <linux/rtc.h>
#include <linux/statfs.h>

#include <linux/io.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/hisi/util.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/hisi_bootup_keypoint.h>
#include <linux/hisi/rdr_hisi_ap_ringbuffer.h>

#include <chipset_common/hwbfm/hwboot_fail_hisi_interface.h>
#include <chipset_common/hwbfm/hwboot_fail_print.h>
#include <chipset_common/hwbfm/hw_boot_fail_core.h>

#define BFM_PATH_MAXLEN         128
#define BFM_LOG_MAX_COUNT (10)
#define BFM_US_PERSECOND (1000000)
#define BFM_PATH_LEN (1024)
#define BFMR_TEMP_BUF_LEN (4096)
#define BFMR_WAIT_LOG_PART_NORMAL_TIMEOUT (40)
#define BFM_PATH_ROOT           "/splash2/boot_fail/"
#define BFMR_PROC_MOUNTS_PATH "/proc/mounts"
#define BFMR_RW_FLAGS "rw,"
#define BFMR_HISI_LOG_MOUNT_POINT "/splash2"
#define BFI_FILE_NAME "bootFail_info.txt"
#define RCV_FILE_NAME "recovery_info.txt"
#define BFMR_RECOVERY_SUCCESS_FIELD "rcvResult:1\r\n"
#define BFMR_RECOVERY_RESULT_FIELD "rcvResult:"
#define BFMR_LOG_END_TAG_PER_LINE "\r\n"
#define BFMR_BYTES_REDUNDANT_ON_LOG_PART (4 * 1024)
#define BFMR_UPLOADING_NAME "uploading"
#define BFMR_DONE_FILE_NAME "DONE"
#define BFMR_UPLOADED_PATH BFM_PATH_ROOT BFMR_UPLOADING_NAME "/"
#define BFMR_BFI_FILE_CONTENT_FORMAT \
    "time:%s\r\n" \
    "bootFailErrno:%s_%s_%s\r\n" \
    "boot_stage:%s_%s\r\n" \
    "isSystemRooted:%d\r\n" \
    "isUserPerceptible:%d\r\n" \
    "\r\n" \
    "time:0x%llx\r\n" \
    "bootFailErrno:0x%x\r\n" \
    "boot_stage:0x%x\r\n" \
    "isSystemRooted:%d\r\n" \
    "isUserPerceptible:%d\r\n"\
    "\r\n"\
    "the bootlock field in cmdline is: [%s] this time\r\n"

#define BFMR_RCV_FILE_CONTENT_FORMAT \
    "rcvMethod:%s\r\n" \
    "rcvResult:%s\r\n" \
    "\r\n" \
    "rcvMethod:%d\r\n" \
    "rcvResult:%d\r\n"

#define BFMR_CRITICAL_PROCESS_CRASH_LOG_NAME "critical_process_crash.txt"
#define AID_ROOT 0
#define AID_SYSTEM 1000

#define DATA_MAXLEN         14
#define DIR_LIMIT		0775
#define FILE_LIMIT		0664
#define PATH_MAXLEN         128
#define MIN(a, b) (((a) >= (b)) ? (b) : (a))
#define MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define BFMR_LOGCAT_FILE_PATH "/data/log/android_logs/applogcat-log"
#define BFMR_LOGCAT_FILE_NAME "applogcat_log"
#define BFMR_BOOT_FAIL_LOGCAT_FILE_MAX_SIZE ((unsigned int)512 * 1024)
#define BFMR_FRAMEWORK_BOOT_FAIL_LOG_PATH "/data/anr/framework_boot_fail.log"

typedef struct
{
    enum BFM_ERRNO_CODE boot_fail_no;
    char *desc;
} bfmr_boot_fail_no_desc_t;

typedef struct
{
    failure_recovery_method_e recovery_method;
    char *desc;
} bfmr_recovery_method_desc_t;

static unsigned int isSystemRooted = 0;
static char s_boot_lock_info[32] = {0};

static bfmr_boot_fail_no_desc_t s_boot_fail_no_desc[] =
{
    {BL1_DDR_INIT_FAIL, "bl1 ddr init failed"},
    {BL1_EMMC_INIT_FAIL, "bl1 emmc init failed"},
    {BL1_BL2_LOAD_FAIL, "load image image failed"},
    {BL1_BL2_VERIFY_FAIL, "verify image failed"},
    {BL2_EMMC_INIT_FAIL, "bl2 emmc init failed"},
    {BL1_WDT, "bl1 wdt"},
    {BL1_VRL_LOAD_FAIL, "bl1 vrl load error"},
    {BL1_VRL_VERIFY_FAIL, "bl1 vrl verify image error"},
    {BL1_ERROR_GROUP_BOOT, "bl1 group boot error"},
    {BL1_ERROR_GROUP_BUSES, "bl1 group buses error"},
    {BL1_ERROR_GROUP_BAM, "bl1 group bam"},
    {BL1_ERROR_GROUP_BUSYWAIT, "bl1 group busy wait"},
    {BL1_ERROR_GROUP_CLK, "bl1 group clock"},
    {BL1_ERROR_GROUP_CRYPTO, "bl1 group crypto"},
    {BL1_ERROR_GROUP_DAL, "bl1 group dal"},
    {BL1_ERROR_GROUP_DEVPROG, "bl1 group devprog"},
    {BL1_ERROR_GROUP_DEVPROG_DDR, "bl1 group devprog ddr"},
    {BL1_ERROR_GROUP_EFS, "bl1 group efs"},
    {BL1_ERROR_GROUP_EFS_LITE, "bl1 group efs lite"},
    {BL1_ERROR_GROUP_HOTPLUG, "bl1 group hot-plug"},
    {BL1_ERROR_GROUP_HSUSB, "bl1 group high speed usb"},
    {BL1_ERROR_GROUP_ICB, "bl1 group icb"},
    {BL1_ERROR_GROUP_LIMITS, "bl1 group limits"},
    {BL1_ERROR_GROUP_MHI, "bl1 group mhi"},
    {BL1_ERROR_GROUP_PCIE, "bl1 group pcie"},
    {BL1_ERROR_GROUP_PLATFOM, "bl1 group platform"},
    {BL1_ERROR_GROUP_PMIC, "bl1 group pmic"},
    {BL1_ERROR_GROUP_POWER, "bl1 group power"},
    {BL1_ERROR_GROUP_PRNG, "bl1 group prng"},
    {BL1_ERROR_GROUP_QUSB, "bl1 group qusb"},
    {BL1_ERROR_GROUP_SECIMG, "bl1 group secimg"},
    {BL1_ERROR_GROUP_SECBOOT, "bl1 group secboot"},
    {BL1_ERROR_GROUP_SECCFG, "bl1 group seccfg"},
    {BL1_ERROR_GROUP_SMEM, "bl1 group smem"},
    {BL1_ERROR_GROUP_SPMI, "bl1 group spmi"},
    {BL1_ERROR_GROUP_SUBSYS, "bl1 group subsystem"},
    {BL1_ERROR_GROUP_TLMM, "bl1 group tlmm"},
    {BL1_ERROR_GROUP_TSENS, "bl1 group tsensor"},
    {BL1_ERROR_GROUP_HWENGINES, "bl1 group hwengines"},
    {BL1_ERROR_GROUP_IMAGE_VERSION, "bl1 group image version"},
    {BL1_ERROR_GROUP_SECURITY, "bl1 group system security"},
    {BL1_ERROR_GROUP_STORAGE, "bl1 group storage"},
    {BL1_ERROR_GROUP_SYSTEMDRIVERS, "bl1 group system drivers"},
    {BL1_ERROR_GROUP_EXCEPTIONS, "bl1 group exceptions"},
    {BL1_ERROR_GROUP_MPROC, "bl1 group mppoc"},
    {BL2_PANIC, "bl2 panic"},
    {BL2_WDT, "bl2 wdt"},
    {BL2_PL1_OCV_ERROR, "ocv error"},
    {BL2_PL1_BAT_TEMP_ERROR, "battery temperature error"},
    {BL2_PL1_MISC_ERROR, "misc part dmaged"},
    {BL2_PL1_DTIMG_ERROR, "dt image dmaged"},
    {BL2_PL1_LOAD_OTHER_IMGS_ERRNO, "image dmaged"},
    {BL2_PL1_KERNEL_IMG_ERROR, "kernel image verify failed"},
    {BL2_MMC_INIT_FAILED, "bl2 mmc init error"},
    {BL2_QSEECOM_START_ERROR, "bl2 qseecom start error"},
    {BL2_RPMB_INIT_FAILED, "bl2 rpmb init failed"},
    {BL2_LOAD_SECAPP_FAILED, "bl2 load secapp failed"},
    {BL2_ABOOT_DLKEY_DETECTED, "bl2 dlkey failed"},
    {BL2_ABOOT_NORMAL_BOOT_FAIL, "bl2 aboot normal boot failed"},
    {KERNEL_AP_PANIC, "kernel ap panic"},
    {KERNEL_EMMC_INIT_FAIL, "kernel emm init failed"},
    {KERNEL_AP_WDT, "kernel ap wdt"},
    {KERNEL_PRESS10S, "kernel press10s"},
    {KERNEL_BOOT_TIMEOUT, "kernel boot timeout"},
    {KERNEL_AP_COMBINATIONKEY, "kernel ap combinationkey"},
    {KERNEL_AP_S_ABNORMAL, "kernel ap abnormal"},
    {KERNEL_AP_S_TSENSOR0, "kernel ap tsensor0"},
    {KERNEL_AP_S_TSENSOR1, "kernel ap tsensor1"},
    {KERNEL_LPM3_S_GLOBALWDT, "kernel lpm3 global wdt"},
    {KERNEL_G3D_S_G3DTSENSOR, "kernel g3d g3dtsensor"},
    {KERNEL_LPM3_S_LPMCURST, "kernel lpm3 lp mcu reset"},
    {KERNEL_CP_S_CPTSENSOR, "kernel cp cpt sensor"},
    {KERNEL_IOM3_S_IOMCURST, "kernel iom3 io mcu reset"},
    {KERNEL_ASP_S_ASPWD, "kernel asp as pwd"},
    {KERNEL_CP_S_CPWD, "kernel cp cp pwd"},
    {KERNEL_IVP_S_IVPWD, "kernel ivp iv pwd"},
    {KERNEL_ISP_S_ISPWD, "kernel isp is pwd"},
    {KERNEL_AP_S_DDR_UCE_WD, "kernel ap ddr uce wd"},
    {KERNEL_AP_S_DDR_FATAL_INTER, "kernel ap ddr fatal inter"},
    {KERNEL_AP_S_DDR_SEC, "kernel ap ddr sec"},
    {KERNEL_AP_S_MAILBOX, "kernel ap mailbox"},
    {KERNEL_CP_S_MODEMDMSS, "kernel cp modem dmss"},
    {KERNEL_CP_S_MODEMNOC, "kernel cp modem noc"},
    {KERNEL_CP_S_MODEMAP, "kernel cp modem ap"},
    {KERNEL_CP_S_EXCEPTION, "kernel cp exception"},
    {KERNEL_CP_S_RESETFAIL, "kernel cp reset failed"},
    {KERNEL_CP_S_NORMALRESET, "kernel cp normal reset"},
    {KERNEL_CP_S_ABNORMAL, "kernel cp abnormal"},
    {KERNEL_LPM3_S_EXCEPTION, "kernel lpm3 exception"},
    {KERNEL_HIFI_S_EXCEPTION, "kernel hisi exception"},
    {KERNEL_HIFI_S_RESETFAIL, "kernel hisi reset failed"},
    {KERNEL_ISP_S_EXCEPTION, "kernel isp exception"},
    {KERNEL_IVP_S_EXCEPTION, "kernel ivp exception"},
    {KERNEL_IOM3_S_EXCEPTION, "kernel iom3 exception"},
    {KERNEL_TEE_S_EXCEPTION, "kernel tee exception"},
    {KERNEL_MMC_S_EXCEPTION, "kernel mmc exception"},
    {KERNEL_CODECHIFI_S_EXCEPTION, "kernel codec hifi exception"},
    {KERNEL_CP_S_RILD_EXCEPTION, "kernel cp rild exception"},
    {KERNEL_CP_S_3RD_EXCEPTION, "kernel cp 3rd exception"},
    {KERNEL_IOM3_S_USER_EXCEPTION, "kernel iom3 user exception"},
    {KERNEL_MODEM_PANIC, "kernel modem panic"},
    {KERNEL_VENUS_PANIC, "kernel venus panic"},
    {KERNEL_WCNSS_PANIC, "kernel wcnss panic"},
    {KERNEL_SENSOR_PANIC, "kernel sensor panic"},
    {SYSTEM_MOUNT_FAIL, "system part mount failed"},
    {SECURITY_FAIL, "security failed"},
    {CRITICAL_SERVICE_FAIL_TO_START, "zygote or system_server start failed"},
    {DATA_MOUNT_FAILED_AND_ERASED, "data part mount failed"},
    {DATA_MOUNT_RO, "data part mounted ro"},
    {DATA_NOSPC, "no space on data part"},
    {VENDOR_MOUNT_FAIL, "vendor part mount failed"},
    {SYSTEM_SERVICE_LOAD_FAIL, "system service load failed"},
    {PREBOOT_BROADCAST_FAIL, "preboot broadcast failed"},
    {VM_OAT_FILE_DAMAGED, "ota file damaged"},
    {PACKAGE_MANAGER_SETTING_FILE_DAMAGED, "package manager setting file damaged"},
};

static bfmr_recovery_method_desc_t s_recovery_method_desc[] =
{
    {FRM_DO_NOTHING, "do nothing"},
    {FRM_REBOOT, "reboot"},
    {FRM_GOTO_B_SYSTEM, "goto B system"},
    {FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF, "del files in /data part"},
    {FRM_GOTO_ERECOVERY_DEL_FILES_FOR_NOSPC, "del files in /data part because of no space"},
    {FRM_GOTO_ERECOVERY_FACTORY_RESET, "recommend user to do factory reset"},
    {FRM_GOTO_ERECOVERY_FORMAT_DATA_PART, "recommend user to format /data part"},
    {FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY, "download and recovery"},
    {FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_DEL_FILES, "recommend user to del files in /data after download and recovery"},
    {FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET, "recommend user to do factory reset after download and recovery"},
    {FRM_NOTIFY_USER_RECOVERY_FAILURE, "recovery failed, the boot fail fault can't be recoveried by BFRM"},
    {FRM_GOTO_ERECOVERY_LOWLEVEL_FORMAT_DATA, "recommend user to do low-level formatting data"},
};

static int bfmr_lookup_dir_by_create_time(const char *root,
    char *log_path,
    size_t log_path_len,
    int *log_total_count,
    int find_oldest_log);
static bool bfmr_oldest_log_should_be_deleted(char *log_path,
    size_t log_path_len,
    u64 bytes_need_for_this_log);
static int bfmr_find_newest_log(char *log_path, size_t log_path_len);
static void bfmr_delete_oldest_log(u64 bytes_need_for_this_log);
static int bfmr_wait_for_log_part_with_timeout(const char *pmount_point, int timeouts);
static int bfmr_wait_for_log_part_without_timeout(const char *pmount_point);
static int bfmr_read_recovery_info(const char *precovery_info_path,
    char *data_buf, long data_buf_len);
static int bfmr_renew_recovery_info(char *data_buf, long data_len, long pos);
static bool bfmr_is_part_mounted_rw(const char *pmount_point);
static bool bfmr_is_log_existed(u64 rtc_time, enum BFM_ERRNO_CODE bfmErrNo);
static char *bfmr_get_timestamp(u64 rtc_time);
static void bfmr_change_own_mode(char *path, int uid, int gid, int mode);
static void bfmr_save_log_to_bfi_part(u32 modID,
    suggested_recovery_method_e suggested_recovery_method);
static int bfmr_save_log(char *logpath, char *filename,
    void *buf, u32 len, u32 is_append);
static int bfmr_save_boot_fail_log_to_log_part(struct dfx_head_info *dfx_head_info);
static bool bfmr_is_fs_space_sufficient(char *fs_path, u64 bytes_need);
static int __bfmr_create_dir(char *path);
static int bfmr_create_dir(const char *path);
static int bfmr_create_log_path(char *path);
static int bfmr_create_done_file_for_every_log(char *log_root_path);
static int bfmr_create_bfm_log_path(char *path, u64 rtc_time, enum BFM_ERRNO_CODE bfmErrNo);
static int bfmr_get_info_from_bfi_part(struct bfi_every_number_Info  *bfi_rcv_info_buf, u64 rtc_time);
static bool bfmr_is_file_existed(char *pfile_path);
static bool bfmr_is_dir_existed(char *pdir_path);
static int bfmr_save_tombstone_dropbox_log(char *pdir, char *log_path);
static int bfmr_save_user_space_bfmr_log(char *pdir, char *log_path);
static long bfmr_get_file_length(const char *pfile_path);
static char* bfmr_get_timestamp(u64 rtc_time);
static char* bfmr_get_platform_name(void);
static char* bfmr_get_boot_stage_name(unsigned int boot_fail_no, unsigned int boot_stage);
static char* bfmr_get_boot_fail_no_desc(unsigned int boot_fail_no);
static char* bfmr_get_recovery_method_desc(int recovery_method);
static int bfmr_save_logcat_on_beta_version(char *pdst_dir);
static char* bfmr_get_bootlock_value_from_cmdline(void);

static char* bfmr_get_bootlock_value_from_cmdline(void)
{
    return s_boot_lock_info;
}

static char* bfmr_get_platform_name(void)
{
#if defined(CONFIG_HW_BFMR_HISI)
    return "hisi";
#elif defined(CONFIG_HW_BFMR_QCOM)
    return "qcom";
#else
    return "qcom";
#endif
}


static char* bfmr_get_boot_stage_name(unsigned int boot_fail_no, unsigned int boot_stage)
{
    char *boot_stage_name = NULL;

    if (isBL1Errno(boot_fail_no))
    {
        boot_stage_name = "BL1";
    }
    else if (isBL2Errno(boot_fail_no))
    {
        boot_stage_name = "BL2";
    }
    else if (isKernelErrno(boot_fail_no))
    {
        boot_stage_name = "kernel";
    }
    else if (isNativeErrno(boot_fail_no))
    {
        if (isBootSuccess((enum BFM_BOOT_STAGE_CODE)boot_stage))
        {
            boot_stage_name = "native(error occurred after boot success)";
        }
        else
        {
            boot_stage_name = "native";
        }
    }
    else if (isAndroidFrameworkErrno(boot_fail_no))
    {
        boot_stage_name = "framework";
    }
    else
    {
        boot_stage_name = "unknown";
    }

    return boot_stage_name;
}


static char* bfmr_get_boot_fail_no_desc(unsigned int boot_fail_no)
{
    int i = 0;
    int count = sizeof(s_boot_fail_no_desc) / sizeof(s_boot_fail_no_desc[0]);

    for (i = 0; i < count; i++)
    {
        if ((enum BFM_ERRNO_CODE)boot_fail_no == s_boot_fail_no_desc[i].boot_fail_no)
        {
            return s_boot_fail_no_desc[i].desc;
        }
    }

    return "unknown";
}


static char* bfmr_get_recovery_method_desc(int recovery_method)
{
    int i = 0;
    int count = sizeof(s_recovery_method_desc) / sizeof(s_recovery_method_desc[0]);

    for (i = 0; i < count; i++)
    {
        if ((failure_recovery_method_e)recovery_method == s_recovery_method_desc[i].recovery_method)
        {
            return s_recovery_method_desc[i].desc;
        }
    }

    return "unknown";
}


static long bfmr_get_file_length(const char *pfile_path)
{
    mm_segment_t oldfs;
    struct stat st;
    int ret = -1;

    if (unlikely(NULL == pfile_path))
    {
        BFM_PRINT_ERR("func: %s Invalid paramters pfile_path is NULL\n", __func__);
        return 0L;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    memset((void *)&st, 0, sizeof(st));
    ret = sys_newlstat(pfile_path, &st);
    if (0 != ret)
    {
        BFM_PRINT_ERR("func: %s sys_newlstat failed![ret=%d]\n", __func__, ret);
        set_fs(oldfs);
        return 0L;
    }

    set_fs(oldfs);

    return (long)st.st_size;
}

static bool bfmr_is_file_existed(char *pfile_path)
{
    mm_segment_t oldfs;
    struct stat st;
    int ret = -1;

    if (unlikely(NULL == pfile_path))
    {
        BFM_PRINT_ERR("func: %s Invalid paramters pfile_path is NULL\n", __func__);
        return false;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    ret = sys_newlstat(pfile_path, &st);
    set_fs(oldfs);

    return (0 == ret) ? (true) : (false);
}


static bool bfmr_is_dir_existed(char *pdir_path)
{
    return bfmr_is_file_existed(pdir_path);
}


static int bfmr_create_log_path(char *path)
{
    int ret = -1;

    if (unlikely(NULL == path))
    {
        BFM_PRINT_ERR("func: %s Invalid paramters path is NULL\n", __func__);
        return -1;
    }

    if (bfmr_is_dir_existed(path))
    {
        bfmr_change_own_mode(path, AID_ROOT, AID_SYSTEM, DIR_LIMIT);
        return 0;
    }

    ret = bfmr_create_dir(path);
    BFM_PRINT_ERR("Create dir [%s] ret: %d\n", path, ret);
    bfmr_change_own_mode(path, AID_ROOT, AID_SYSTEM, DIR_LIMIT);

    return ret;
}


static int bfmr_create_done_file_for_every_log(char *log_root_path)
{
    int ret = -1;
    int fd = -1;
    void *buf = NULL;
    char *full_path = NULL;
    char *done_file_path = NULL;
    struct linux_dirent64 *dirp;
    int num;
    mm_segment_t oldfs;
    char c = '\0';

    if (unlikely(NULL == log_root_path))
    {
        BFM_PRINT_ERR("func: %s Invalid parameters!!\n", __func__);
        return -1;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(log_root_path, O_RDONLY, 0);
    if (fd < 0)
    {
        BFM_PRINT_ERR("open [%s] failed!\n", log_root_path);
        goto __out;
    }

    buf = vmalloc(BFM_PATH_LEN);
    if (NULL == buf)
    {
        BFM_PRINT_ERR("vmalloc failed!\n");
        goto __out;
    }

    full_path = (char *)vmalloc(BFM_PATH_LEN);
    if (NULL == full_path)
    {
        BFM_PRINT_ERR("vmalloc failed!\n");
        goto __out;
    }

    done_file_path = (char *)vmalloc(BFM_PATH_LEN);
    if (NULL == done_file_path)
    {
        BFM_PRINT_ERR("vmalloc failed!\n");
        goto __out;
    }

    dirp = buf;
    num = sys_getdents64(fd, dirp, BFM_PATH_LEN);
    while (num > 0)
    {
        while (num > 0)
        {
            struct stat st;
            int ret;

            memset(full_path, 0, BFM_PATH_LEN);
            snprintf(full_path, BFM_PATH_LEN - 1, "%s/%s", log_root_path, dirp->d_name);
            if ((0 == strcmp(dirp->d_name, ".")) || (0 == strcmp(dirp->d_name, "..")))
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                continue;
            }

            memset((void *)&st, 0, sizeof(struct stat));
            ret = sys_newlstat(full_path, &st);
            if (0 != ret)
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                BFM_PRINT_ERR("newlstat %s failed!\n", full_path);
                continue;
            }

            if (!S_ISDIR(st.st_mode))
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                BFM_PRINT_ERR("%s is not a dir!\n", full_path);
                continue;
            }

            /* Note: We must exclude the uploaded dir */
            if (0 == strcmp(dirp->d_name, BFMR_UPLOADING_NAME))
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                BFM_PRINT_ERR("%s must be excluded!\n", full_path);
                continue;
            }

            memset((void *)done_file_path, 0, BFM_PATH_LEN);
            snprintf(done_file_path, "%s/%s", full_path, BFMR_DONE_FILE_NAME);
            if (!bfmr_is_file_existed(done_file_path))
            {
                (void)bfmr_save_log(full_path, BFMR_DONE_FILE_NAME, (void *)&c, sizeof(char), 0);
            }
            num -= dirp->d_reclen;
            dirp = (void *)dirp + dirp->d_reclen;
        }
        dirp = buf;
        memset(buf, 0, BFM_PATH_LEN);
        num = sys_getdents64(fd, dirp, BFM_PATH_LEN);
    }

__out:
    if (fd > 0)
    {
        sys_close(fd);
    }
    set_fs(oldfs);
    vfree(buf);
    vfree(full_path);
    vfree(done_file_path);

    return ret;
}


static bool bfmr_is_fs_space_sufficient(char *fs_path, u64 bytes_need)
{
    int ret = -1;
    struct statfs statfs_buf;
    bool is_fs_space_sufficient = false;
    u64 bytes_avail = 0ULL;
    mm_segment_t old_fs;

    if (unlikely(NULL == fs_path))
    {
        BFM_PRINT_ERR("func: %s Invalid paramters path is NULL\n", __func__);
        return false;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    memset((void *)&statfs_buf, 0, sizeof(statfs_buf));
    ret = sys_statfs(fs_path, &statfs_buf);
    if (0 != ret)
    {
        BFM_PRINT_ERR("func: %s sys_statfs failed: %d\n", __func__, ret);
        goto __out;
    }

    bytes_avail = (u64)statfs_buf.f_bavail * (u64)statfs_buf.f_bsize;
    if (bytes_avail > bytes_need)
    {
        is_fs_space_sufficient = true;
    }
    else
    {
        BFM_PRINT_ERR("func: %s Space on [%s] is insufficient, bytes_avail: %llu bytes_need: %llu\n",
            __func__, fs_path, bytes_avail, bytes_need);
        is_fs_space_sufficient = false;
    }

__out:
    set_fs(old_fs);

    return is_fs_space_sufficient;
}


static void bfmr_change_own_mode(char *path, int uid, int gid, int mode)
{
    mm_segment_t oldfs;
    int ret = -1;

    if (unlikely(NULL == path))
    {
        BFM_PRINT_ERR("func: %s Invalid paramters path is NULL\n", __func__);
        return;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    ret = sys_chown(path, uid, gid);
    if (0 != ret)
    {
        BFM_PRINT_ERR("sys_chown [%s] failed, ret: %d\n", path, ret);
        goto __out;
    }

    ret = sys_chmod(path, mode);
    if (0 != ret)
    {
        BFM_PRINT_ERR("sys_chmod [%s] failed, ret: %d\n", path, ret);
        goto __out;
    }

__out:
    set_fs(oldfs);
}

static int bfmr_lookup_dir_by_create_time(const char *root,
    char *log_path,
    size_t log_path_len,
    int *log_total_count,
    int find_oldest_log)
{
    int fd = -1;
    void *buf = NULL;
    char *full_path = NULL;
    struct linux_dirent64 *dirp;
    int num;
    mm_segment_t oldfs;
    unsigned long long special_time = 0;
    unsigned long long cur_time = 0;

    if (unlikely((NULL == log_path) || (NULL == log_total_count)))
    {
        BFM_PRINT_ERR("func: %s Invalid parameters!!\n", __func__);
        return -1;
    }

    memset((void *)log_path, 0, log_path_len);
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    BFM_PRINT_ERR("root path: %s\n", root);
    fd = sys_open(root, O_RDONLY, 0);
    if (fd < 0)
    {
        BFM_PRINT_ERR("open [%s] failed!\n", root);
        set_fs(oldfs);
        return -1;
    }

    buf = kzalloc(BFM_PATH_LEN, GFP_KERNEL);
    if (NULL == buf)
    {
        BFM_PRINT_ERR("kzalloc failed!\n");
        sys_close(fd);
        set_fs(oldfs);
        return -1;
    }

    full_path = (char *)kzalloc(BFM_PATH_LEN, GFP_KERNEL);
    if (NULL == full_path)
    {
        BFM_PRINT_ERR("kzalloc failed!\n");
        sys_close(fd);
        set_fs(oldfs);
        kfree(buf);
        return -1;
    }

    dirp = buf;
    num = sys_getdents64(fd, dirp, BFM_PATH_LEN);
    while (num > 0)
    {
        while (num > 0)
        {
            struct stat st;
            int ret;

            memset(full_path, 0, BFM_PATH_LEN);
            snprintf(full_path, BFM_PATH_LEN - 1, "%s/%s", root, dirp->d_name);
            if ((0 == strcmp(dirp->d_name, ".")) || (0 == strcmp(dirp->d_name, "..")))
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                continue;
            }

            memset((void *)&st, 0, sizeof(struct stat));
            ret = sys_newlstat(full_path, &st);
            if (0 != ret)
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                BFM_PRINT_ERR("newlstat %s failed!\n", full_path);
                continue;
            }

            if (!S_ISDIR(st.st_mode))
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                BFM_PRINT_ERR("%s is not a dir!\n", full_path);
                continue;
            }

            /* Note: We must exclude the uploaded dir */
            if (0 == strcmp(dirp->d_name, BFMR_UPLOADING_NAME))
            {
                num -= dirp->d_reclen;
                dirp = (void *)dirp + dirp->d_reclen;
                BFM_PRINT_ERR("%s must be excluded!\n", full_path);
                continue;
            }

            cur_time = (unsigned long long)st.st_mtime * BFM_US_PERSECOND + st.st_mtime_nsec / 1000;
            if (0 == special_time)
            {
                strncpy(log_path, full_path, log_path_len - 1);
                special_time = cur_time;
            }
            else
            {
                if (0 != find_oldest_log)
                {
                    if (special_time > cur_time)
                    {
                        strncpy(log_path, full_path, log_path_len - 1);
                        special_time = cur_time;
                    }
                }
                else
                {
                    if (special_time < cur_time)
                    {
                        strncpy(log_path, full_path, log_path_len - 1);
                        special_time = cur_time;
                    }
                }
            }
            (*log_total_count)++;
            num -= dirp->d_reclen;
            dirp = (void *)dirp + dirp->d_reclen;
        }
        dirp = buf;
        memset(buf, 0, BFM_PATH_LEN);
        num = sys_getdents64(fd, dirp, BFM_PATH_LEN);
    }

    sys_close(fd);
    BFM_PRINT_DBG("Log count: %d special_log_path: %s\n", *log_total_count, log_path);
    set_fs(oldfs);
    kfree(buf);
    kfree(full_path);

    return 0;
}

static bool bfmr_oldest_log_should_be_deleted(char *log_path,
    size_t log_path_len,
    u64 bytes_need_for_this_log)
{
    int log_count = 0;
    bool oldest_log_should_be_deleted = true; /* it must be true here */

    BFM_PRINT_ERR("bytes need for the following log is: %llu!\n", bytes_need_for_this_log);
    (void)bfmr_lookup_dir_by_create_time(BFM_PATH_ROOT, log_path, log_path_len, &log_count, 1);
    if (log_count < BFM_LOG_MAX_COUNT) /* TO FIXUP */
    {
        oldest_log_should_be_deleted = (bfmr_is_fs_space_sufficient(
            BFMR_HISI_LOG_MOUNT_POINT, bytes_need_for_this_log))
            ? (false) : (true);
    }

    if (oldest_log_should_be_deleted)
    {
        BFM_PRINT_ERR("The oldest log: %s must be deleted!\n", log_path);
    }

    return oldest_log_should_be_deleted;
}

static int bfmr_find_newest_log(char *log_path, size_t log_path_len)
{
    int log_count = 0;
    int ret = -1;

    ret = bfmr_lookup_dir_by_create_time(BFM_PATH_ROOT, log_path, log_path_len, &log_count, 0);
    if (0 == strlen(log_path))
    {
        return -1;
    }
    else
    {
        BFM_PRINT_ERR("The newest log is: %s\n", log_path);
    }

    return 0;
}

static void bfmr_delete_oldest_log(u64 bytes_need_for_this_log)
{
    int fd = -1;
    void *buf = NULL;
    char *full_path = NULL;
    char *oldest_full_path = NULL;
    struct linux_dirent64 *dirp;
    int num;
    mm_segment_t oldfs;

    oldest_full_path = (char *)kzalloc(BFM_PATH_LEN, GFP_KERNEL);
    if (NULL == oldest_full_path)
    {
        BFM_PRINT_ERR("kzalloc failed!\n");
        return;
    }

    if (!bfmr_oldest_log_should_be_deleted(oldest_full_path,
        BFM_PATH_LEN, bytes_need_for_this_log))
    {
        BFM_PRINT_ERR("func: %s the oldest log needn't be deleted!\n", __func__);
        kfree(oldest_full_path);
        return;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(oldest_full_path, O_RDONLY, 0);
    if (fd < 0)
    {
        BFM_PRINT_ERR("open [%s] failed!\n", BFM_PATH_ROOT);
        set_fs(oldfs);
        kfree(oldest_full_path);
        return -1;
    }

    buf = kzalloc(BFM_PATH_LEN, GFP_KERNEL);
    if (NULL == buf)
    {
        BFM_PRINT_ERR("kzalloc failed!\n");
        sys_close(fd);
        set_fs(oldfs);
        kfree(oldest_full_path);
        return -1;
    }

    full_path = (char *)kzalloc(BFM_PATH_LEN, GFP_KERNEL);
    if (NULL == full_path)
    {
        BFM_PRINT_ERR("kzalloc failed!\n");
        sys_close(fd);
        set_fs(oldfs);
        kfree(buf);
        kfree(oldest_full_path);
        return -1;
    }

    dirp = buf;
    num = sys_getdents64(fd, dirp, BFM_PATH_LEN);
    while (num > 0)
    {
        while (num > 0)
        {
            struct stat st;
            int ret;

            memset(full_path, 0, BFM_PATH_LEN);
            snprintf(full_path, BFM_PATH_LEN - 1, "%s/%s", oldest_full_path, dirp->d_name);
            if ((0 != strcmp(dirp->d_name, ".")) && (0 != strcmp(dirp->d_name, "..")))
            {
                ret = sys_newlstat(full_path, &st);
                if (0 == ret)
                {
                    if (S_ISDIR(st.st_mode))
                    {
                        sys_rmdir(full_path);
                    }
                    else
                    {
                        sys_unlink(full_path);
                    }
                }
            }
            num -= dirp->d_reclen;
            dirp = (void *)dirp + dirp->d_reclen;
        }
        dirp = buf;
        memset(buf, 0, BFM_PATH_LEN);
        num = sys_getdents64(fd, dirp, BFM_PATH_LEN);
    }

    sys_close(fd);
    sys_rmdir(oldest_full_path);
    set_fs(oldfs);
    kfree(buf);
    kfree(full_path);
    kfree(oldest_full_path);
}

static int bfmr_read_recovery_info(const char *precovery_info_path,
    char *data_buf, long data_buf_len)
{
    mm_segment_t old_fs;
    int fd = -1;
    long bytes_read = 0;
    int ret = -1;

    if (unlikely((NULL == precovery_info_path) || (NULL == data_buf)))
    {
        BFM_PRINT_ERR("File: %s Line: %d Invalid parameters!\n", __FILE__, __LINE__);
        return -1;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_open(precovery_info_path, O_RDONLY, 0);
    if (fd < 0)
    {
        BFM_PRINT_ERR("File: %s Line: %d Open [%s] failed!fd: %d\n", __FILE__, __LINE__,
            precovery_info_path, fd);
        goto __out;
    }

    bytes_read = sys_read(fd, data_buf, data_buf_len);
    if (bytes_read != data_buf_len)
    {
        BFM_PRINT_ERR("File: %s Line: %d read [%s] failed!bytes_read: %d, it should be: %d\n",
            __FILE__, __LINE__, precovery_info_path, bytes_read, data_buf_len);
        goto __out;
    }
    else
    {
        ret = 0;
    }

__out:
    if (fd > 0)
    {
        sys_close(fd);
    }

    set_fs(old_fs);

    return ret;
}


static int bfmr_renew_recovery_info(char *data_buf, long data_len, long pos)
{
    int ret = -1;
    int flags = 0;
    long bytes_written = 0L;
    struct file *fp = NULL;
    mm_segment_t old_fs;
    char precovery_info_path[PATH_MAXLEN];
    char newest_log_dir[PATH_MAXLEN];
    char *pfile_data = NULL;
    char *ptemp = NULL;
    char *prev = NULL;
    long file_len = 0L;

    if (unlikely((NULL == precovery_info_path) || (NULL == data_buf)))
    {
        BFM_PRINT_ERR("File: %s Line: %d Invalid parameters!\n", __FILE__, __LINE__);
        return -1;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    /* 1. find newest log path */
    memset(newest_log_dir, 0, sizeof(newest_log_dir));
    if (0 != bfmr_find_newest_log(newest_log_dir, PATH_MAXLEN))
    {
        BFM_PRINT_ERR("%s(): No log in log part.\n", __func__);
        goto __out;
    }

    /* 2. read data of recovery_info.text */
    memset(precovery_info_path, 0, sizeof(precovery_info_path));
    snprintf(precovery_info_path, sizeof(precovery_info_path) - 1, "%s/%s",
        newest_log_dir, RCV_FILE_NAME);

    file_len = bfmr_get_file_length(precovery_info_path);
    pfile_data = (char *)vmalloc(file_len + 1);
    if (NULL == pfile_data)
    {
        BFM_PRINT_ERR("%s(): vmalloc failed!\n", __func__);
        goto __out;
    }
    memset((void *)pfile_data, 0, file_len + 1);

    if (0 != bfmr_read_recovery_info(precovery_info_path, pfile_data, file_len))
    {
        BFM_PRINT_ERR("%s(): Read [%s] failed!\n", __func__, precovery_info_path);
        goto __out;
    }

    /* 3. check if the recovery result flag has been modified or not */
    if (NULL != strstr(pfile_data, BFMR_RECOVERY_SUCCESS_FIELD))
    {
        BFM_PRINT_ERR("%s(): recovery success result has been set!\n", __func__);
        ret = 0;
        goto __out;
    }

    /* 4. renew recovery result */
    flags = O_RDWR | O_TRUNC;
    fp = filp_open(precovery_info_path, flags, FILE_LIMIT);
    if (IS_ERR(fp))
    {
        BFM_PRINT_ERR("%s():renew file %s err.\n", __func__, precovery_info_path);
        goto __out;
    }

    /* 5. write header */
    vfs_llseek(fp, pos, SEEK_SET);
    bytes_written = vfs_write(fp, data_buf, data_len, &(fp->f_pos));
    if (bytes_written != data_len)
    {
        BFM_PRINT_ERR("%s():write file %s exception with ret %ld.\n",
            __func__, precovery_info_path, bytes_written);
        goto __out;
    }

    /* 6. find the last fileld "rcvResult:" */
    ptemp = strstr(pfile_data, BFMR_RECOVERY_RESULT_FIELD);
    if (NULL != ptemp)
    {
        prev = ptemp;
        ptemp += strlen(BFMR_RECOVERY_RESULT_FIELD);
        ptemp = strstr(pfile_data, BFMR_RECOVERY_RESULT_FIELD);
        ptemp = (NULL == ptemp) ? (prev) : (ptemp + strlen(BFMR_RECOVERY_RESULT_FIELD));
    }
    else
    {
        BFM_PRINT_ERR("Invalid file data:\n%s\n in file [%s]!\n", pfile_data, precovery_info_path);
        goto __out;
    }

    /* 7. find the first \r\n from the last "rcvResult:" */
    ptemp = strstr(ptemp, BFMR_LOG_END_TAG_PER_LINE);
    if (NULL == ptemp)
    {
        ptemp += strlen(BFMR_LOG_END_TAG_PER_LINE);
        file_len = strlen(ptemp);
        if (0 == file_len)
        {
            goto __out;
        }

        /* 8. save the left data in original file */
        bytes_written = vfs_write(fp, ptemp, file_len, &(fp->f_pos));
        if (bytes_written != file_len)
        {
            BFM_PRINT_ERR("%s():write file %s exception with ret %ld.\n",
                __func__, precovery_info_path, bytes_written);
            goto __out;
        }
    }

__out:
    if (!IS_ERR(fp) && (NULL != fp))
    {
        vfs_fsync(fp, 0);
        filp_close(fp, NULL);
    }

    set_fs(old_fs);
    vfree(pfile_data);

    return ret;
}


static long bfmr_get_proc_file_length(const char *pfile_path)
{
    char c;
    mm_segment_t old_fs;
    int fd = -1;
    long file_size = 0;

    if (unlikely(NULL == pfile_path))
    {
        BFM_PRINT_ERR("File: %s Line: %d Invalid parameters!\n", __FILE__, __LINE__);
        return 0;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_open(pfile_path, O_RDONLY, 0);
    if (fd < 0)
    {
        goto __out;
    }

    while (0 != sys_read(fd, (char *)&c, sizeof(char)))
    {
        file_size++;
    }

__out:
    if (fd > 0)
    {
        sys_close(fd);
    }

    set_fs(old_fs);

    return file_size;
}

static bool bfmr_is_part_mounted_rw(const char *pmount_point)
{
    mm_segment_t old_fs;
    int fd = -1;
    char *data_buf = NULL;
    char *log_part_mount_info = NULL;
    char *pstart = NULL;
    char *pend = NULL;
    bool part_mounted_rw = false;
    long file_size = 0;
    long bytes_read = 0;
    long log_part_mount_info_len = 0L;

    if (unlikely(NULL == pmount_point))
    {
        BFM_PRINT_ERR("File: %s Line: %d Invalid parameters!\n", __FILE__, __LINE__);
        return false;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    /* 1. get file length */
    file_size = bfmr_get_proc_file_length(BFMR_PROC_MOUNTS_PATH);
    if (file_size <= 0)
    {
        goto __out;
    }

    /* 2. open file for read */
    fd = sys_open(BFMR_PROC_MOUNTS_PATH, O_RDONLY, 0);
    if (fd < 0)
    {
        goto __out;
    }

    data_buf = (char *)vmalloc(file_size + 1);
    if (NULL == data_buf)
    {
        BFM_PRINT_ERR("File: %s Line: %d vmalloc failed!\n", __FILE__, __LINE__);
        goto __out;
    }
    memset(data_buf, 0, file_size + 1);

    log_part_mount_info = (char *)vmalloc(BFM_PATH_LEN + 1);
    if (NULL == log_part_mount_info)
    {
        BFM_PRINT_ERR("File: %s Line: %d vmalloc failed!\n", __FILE__, __LINE__);
        goto __out;
    }
    memset(log_part_mount_info, 0, BFM_PATH_LEN + 1);

    bytes_read = sys_read(fd, data_buf, file_size);
    if (bytes_read != file_size)
    {
        BFM_PRINT_ERR("File: %s Line: %d read failed, bytes read: %d it should be: %d\n",
            __FILE__, __LINE__, bytes_read, file_size);
        goto __out;
    }

    pstart = strstr(data_buf, pmount_point);
    if (NULL == pstart)
    {
        goto __out;
    }

    pend = strstr(pstart, "\n");
    if (NULL != pend)
    {
        log_part_mount_info_len = pend - pstart + 1;
        memcpy((void *)log_part_mount_info, (void *)pstart, (log_part_mount_info_len >= BFM_PATH_LEN)
            ? (BFM_PATH_LEN) : (log_part_mount_info_len));
        pstart = log_part_mount_info;
    }

    pend = strstr(pstart, BFMR_RW_FLAGS);
    if (NULL != pend)
    {
        part_mounted_rw = true;
    }
    else
    {
        part_mounted_rw = false;
    }

__out:
    if (fd > 0)
    {
        sys_close(fd);
    }

    if (NULL != data_buf)
    {
        vfree(data_buf);
    }

    if (NULL != log_part_mount_info)
    {
        vfree(log_part_mount_info);
    }

    set_fs(old_fs);

    return part_mounted_rw;
}


static int bfmr_wait_for_log_part_without_timeout(const char *pmount_point)
{
    bool part_mounted_rw = false;

    if (unlikely(NULL == pmount_point))
    {
        BFM_PRINT_PN("invalid parameter. path:%p\n", pmount_point);
        return -1;
    }

    part_mounted_rw = bfmr_is_part_mounted_rw(pmount_point);
    if (part_mounted_rw)
    {
        BFM_PRINT_ERR("Line: %d [%s] has been mounted rw!\n", __LINE__, pmount_point);
    }
    else
    {
        BFM_PRINT_ERR("Line: %d [%s] has not been mounted rw!\n", __LINE__, pmount_point);
    }

    return (part_mounted_rw) ? (0) : (-1);
}


/*
 * func name: bfmr_wait_for_log_part_with_timeout
 * .
 * func args:
 *  char*  path,			path of watit file.
 *  u32 timeouts,       time out.
 * return
 *	<0 fail
 *	0  success
 */
static int bfmr_wait_for_log_part_with_timeout(const char *pmount_point, int timeouts)
{
    bool part_mounted_rw = false;

    if (unlikely(NULL == pmount_point))
    {
        BFM_PRINT_PN("invalid parameter. path:%p\n", pmount_point);
        return -1;
    }

    while (timeouts > 0)
    {
        part_mounted_rw = bfmr_is_part_mounted_rw(pmount_point);
        if (part_mounted_rw)
        {
            BFM_PRINT_ERR("Line: %d [%s] has been mounted rw!\n", __LINE__, pmount_point);
            break;
        }

        current->state = TASK_INTERRUPTIBLE;
        (void)schedule_timeout(HZ); /*wait for 1 second */
        timeouts--;
    }

    if (!part_mounted_rw)
    {
        BFM_PRINT_ERR("func: %s Line: %d failed to check if [%s] has been mounted rw or not!\n",
            __func__, __LINE__, BFMR_PROC_MOUNTS_PATH);
    }

    return (part_mounted_rw) ? (0) : (-1);
}

static bool bfmr_is_log_existed(u64 rtc_time, enum BFM_ERRNO_CODE bfmErrNo)
{
    char full_path[PATH_MAXLEN];
    mm_segment_t oldfs;
    struct stat st;
    int ret;

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    memset((void *)full_path, 0, sizeof(full_path));
    snprintf(full_path, sizeof(full_path) - 1, "%sbootfail_%s_0x%08x/",
        BFM_PATH_ROOT, bfmr_get_timestamp(rtc_time), bfmErrNo);
    ret = sys_newlstat(full_path, &st);
    set_fs(oldfs);
    BFM_PRINT_ERR("func: %s [%s] %s\n", __func__, full_path, (0 == ret) ? ("exists!") : ("does't exist!"));
    return (0 == ret) ? (true) : (false);
}

/*
 * func name: bfmr_save_log
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
static int bfmr_save_log(char *logpath, char *filename,
    void *buf, u32 len, u32 is_append)
{
	int ret = 0, flags;
	struct file *fp;
	mm_segment_t old_fs;
	char path[PATH_MAXLEN];

	BFM_PRINT_START();
	if (logpath == NULL || filename == NULL || buf == NULL || len <= 0) {
		BFM_PRINT_PN("invalid  parameter. path:%p, name:%p buf:%p len:0x%x\n",
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
		BFM_PRINT_ERR("%s():create file %s err.\n", __func__, path);
		ret = -1;
		goto out2;
	}
	vfs_llseek(fp, 0L, is_append ? SEEK_END : SEEK_SET);
	ret = vfs_write(fp, buf, len, &(fp->f_pos));
	if (ret != len) {
		BFM_PRINT_ERR("%s():write file %s exception with ret %d.\n",
			     __func__, path, ret);
		goto out1;
	}

	bfmr_change_own_mode(path, AID_ROOT, AID_SYSTEM, FILE_LIMIT);
	vfs_fsync(fp, 0);
out1:
	filp_close(fp, NULL);

	/*根据权限要求，hisi_logs目录及子目录群组调整为root-system */
    /*
	ret = (int)bbox_chown((const char __user *)path, ROOT_UID,
				SYSTEM_GID, false);
	if (ret) {
		BFM_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		     __func__, path, ROOT_UID, SYSTEM_GID, ret);
	}*/
	set_fs(old_fs);
	BFM_PRINT_END();
out2:
	return ret;
}

static int __init early_parse_bootlock_cmdline(char *p)
{
	if (p) {
		if (!strncmp(p, "locked", strlen("locked")))
			isSystemRooted = 0;
		else
			isSystemRooted = 1;

		BFM_PRINT_DBG("isSystemRooted is %d\n", isSystemRooted);
	}

	memset((void *)s_boot_lock_info, 0, sizeof(s_boot_lock_info));
	snprintf(s_boot_lock_info, sizeof(s_boot_lock_info) - 1, "bootlock=%s", p);

	return 0;
}
early_param("bootlock", early_parse_bootlock_cmdline);


/*******************************************************************************
Function:       get_pmu_rtc_value
Description:    get_pmu_rtc_valuereset
Input:          NA
Output:         NA
Return:         rtc_time
********************************************************************************/
static unsigned int get_pmu_rtc_value(void)
{
	unsigned int temp_val;
	unsigned int time = 0;

	/*
	 * one pmu_reg is 8bit, rtc's value is from four pmu_regs.
	 * we need to the combination of four pmu_regs's value.
	 */
	temp_val = hisi_pmic_reg_read(PMIC_RTCDR0_ADDR(0));
	time |= (temp_val & 0xff) << (0 * 8);

	temp_val = hisi_pmic_reg_read(PMIC_RTCDR1_ADDR(0));
	time |= (temp_val & 0xff) << (1 * 8);

	temp_val = hisi_pmic_reg_read(PMIC_RTCDR2_ADDR(0));
	time |= (temp_val & 0xff) << (2 * 8);

	temp_val = hisi_pmic_reg_read(PMIC_RTCDR3_ADDR(0));
	time |= (temp_val & 0xff) << (3 * 8);

	return time;
}


static int __bfmr_create_dir(char *path)
{
	int fd;
	mm_segment_t old_fs;

	/* BFM_PRINT_START(); */
	if (path == NULL) {
		BFM_PRINT_PN("invalid  parameter. path:%p.\n", path);
		BFM_PRINT_END();
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	fd = sys_access(path, 0);
	if (0 != fd){
		BFM_PRINT_ERR("rdr: need create dir %s !\n", path);
		fd = sys_mkdir(path, DIR_LIMIT);
		if (fd < 0) {
			BFM_PRINT_ERR("rdr: create dir %s failed! ret = %d\n",
				     path, fd);
			set_fs(old_fs);
			BFM_PRINT_END();
			return fd;
		}
		BFM_PRINT_ERR("rdr: create dir %s successed [%d]!!!\n", path, fd);
	}

	set_fs(old_fs);

	/* BFM_PRINT_END(); */
	return 0;
}


static int bfmr_create_dir(const char *path)
{
	char cur_path[64];
	int index = 0;

	BFM_PRINT_START();
	if (path == NULL) {
		BFM_PRINT_PN("invalid  parameter. path:%p\n", path);
		BFM_PRINT_END();
		return -1;
	}
	memset(cur_path, 0, 64);
	if (*path != '/')
		return -1;
	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/')
			__bfmr_create_dir(cur_path);
		cur_path[index] = *path;
		path++;
		index++;
	}

	BFM_PRINT_END();
	return 0;
}

static char* bfmr_get_timestamp(u64 rtc_time)
{
	struct rtc_time tm;
	static char databuf[DATA_MAXLEN + 1];
	BFM_PRINT_START();

	memset(databuf, 0, DATA_MAXLEN + 1);
	memset(&tm, 0, sizeof(struct rtc_time));
	rtc_time_to_tm(rtc_time, &tm);

	snprintf(databuf, DATA_MAXLEN + 1, "%04d%02d%02d%02d%02d%02d",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		 tm.tm_hour, tm.tm_min, tm.tm_sec);

	BFM_PRINT_DBG("bfmr_get_timestamp [%s] !\n", databuf);
	BFM_PRINT_END();
	return databuf;
}


/*******************************************************************************
Function:       bbox_create_dfxlog_path
Description:    create dfx's log_path
Input:          NA
Output:         path;date
Return:         NA
********************************************************************************/
static int bfmr_create_bfm_log_path(char *path, u64 rtc_time, enum BFM_ERRNO_CODE bfmErrNo)
{
	int ret = 0;
	BFM_PRINT_START();

	if (NULL == path) {
		BFM_PRINT_PN("invalid  parameter.\n");
		BFM_PRINT_END();
		return -1;
	}

	memset(path, 0, BFM_PATH_MAXLEN);
	snprintf(path, BFM_PATH_MAXLEN, "%sbootfail_%s_0x%08x/", BFM_PATH_ROOT, bfmr_get_timestamp(rtc_time), bfmErrNo);
	ret = bfmr_create_dir(path);
	bfmr_change_own_mode(path, AID_ROOT, AID_SYSTEM, DIR_LIMIT);
	BFM_PRINT_END();
	return ret;
}

static int bfmr_get_info_from_bfi_part(struct bfi_every_number_Info  *bfi_rcv_info_buf, u64 rtc_time){
	void *buf, *bfi_buf;
	char p_name[BDEVNAME_SIZE + 12];
	static mm_segment_t oldfs;
        int ret, fd_dfx, cnt, i;
	BFM_PRINT_START();

	buf = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf) {
		BFM_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		return -1;
	}

	ret = flash_find_ptn(PART_BFI, buf);
	if (ret != 0) {
	    ret = flash_find_ptn(PART_BFI_TEMP, buf);
	}

	if (ret != 0) {
		BFM_PRINT_ERR(
		    "%s():%d:flash_find_ptn fail[%d]\n",
		    __func__, __LINE__, ret);
              goto out;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_dfx = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
            goto out;
	}
       bfi_buf = (void *)bfi_rcv_info_buf;
       for(i = 0; i<BFI_RECOVERY_LOG_TOTAL_NUMBER+1; i++){
	        memset((void *)bfi_buf, 0, SZ_4K);
        	cnt = sys_read(fd_dfx, bfi_buf, SZ_4K);
        	if (cnt < 0) {
        		BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
                 	sys_close(fd_dfx);
                    goto  out;
        	}
             if(i==0){
                continue;
             }
            if(((struct bfi_every_number_Info *)bfi_buf)->rtcValue == rtc_time){
        	sys_close(fd_dfx);
        	kfree(buf);
              BFM_PRINT_DBG("related recovery information is found!\n");
        	BFM_PRINT_END();
		set_fs(oldfs);
              return 0;
            }
	}
     	sys_close(fd_dfx);
out:
	set_fs(oldfs);
	kfree(buf);
        return -1;
}


static int bfmr_save_logcat_on_beta_version(char *pdst_dir)
{
    int fd_src = -1;
    int ret = -1;
    char *psrc_file_data = NULL;
    char *ptemp = NULL;
    long src_file_len = 0L;
    mm_segment_t oldfs;
    long bytes_to_read = 0L;
    long bytes_to_write = 0L;
    long bytes_read = 0L;
    long seek_pos = 0L;

    if (unlikely((NULL == pdst_dir) || (0 == strlen(pdst_dir))))
    {
        BFM_PRINT_DBG("File: %s Line: %d invalid parameters!\n", __FILE__, __LINE__);
        return -1;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);

    /* get the length of the source file */
    src_file_len = bfmr_get_file_length(BFMR_LOGCAT_FILE_PATH);
    if (src_file_len <= 0)
    {
        BFM_PRINT_ERR("File: %s Line: %d src_file_len: %ld!\n", __FILE__, __LINE__, src_file_len);
        goto __out;
    }

    bytes_to_read = MIN(src_file_len, (long)BFMR_BOOT_FAIL_LOGCAT_FILE_MAX_SIZE);
    psrc_file_data = (char *)vmalloc(bytes_to_read);
    if (NULL == psrc_file_data)
    {
        BFM_PRINT_ERR("File: %s Line: %d src_file_len: %ld!\n", __FILE__, __LINE__, src_file_len);
        goto __out;
    }
    memset((void *)psrc_file_data, 0, bytes_to_read);

    fd_src = sys_open(BFMR_LOGCAT_FILE_PATH, O_RDONLY, 0);
    if (fd_src < 0)
    {
            BFM_PRINT_ERR("File: %s Line: %d sys_open failed: %ld!\n", __FILE__, __LINE__, fd_src);
            goto __out;
    }

    /* lseek for reading the latest log */
    seek_pos = (src_file_len <= (long)BFMR_BOOT_FAIL_LOGCAT_FILE_MAX_SIZE)
        ? (0L) : (src_file_len - (long)BFMR_BOOT_FAIL_LOGCAT_FILE_MAX_SIZE);
    if (sys_lseek(fd_src, (unsigned int)seek_pos, SEEK_SET) < 0)
    {
            BFM_PRINT_ERR("File: %s Line: %d sys_lseek failed!\n", __FILE__, __LINE__);
            goto __out;
    }

    /* read data from the user space source file */
    ptemp = psrc_file_data;
    bytes_to_write = bytes_to_read;
    while (bytes_to_read > 0)
    {
        bytes_read = sys_read(fd_src, ptemp, bytes_to_read);
        if (bytes_read < 0)
        {
            BFM_PRINT_ERR("File: %s Line: %d sys_read failed: %ld!\n", __FILE__, __LINE__, bytes_read);
            goto __out;
        }
        bytes_to_read -= bytes_read;
        ptemp += bytes_read;
    }

    /* write data to dst file */
    ret = bfmr_save_log(pdst_dir, BFMR_LOGCAT_FILE_NAME, psrc_file_data, (u32)bytes_to_write, 0);

__out:
    if (fd_src > 0)
    {
        sys_close(fd_src);
    }

    set_fs(oldfs);
    vfree(psrc_file_data);

    return ret;
}


static int bfmr_save_tombstone_dropbox_log(char *pdir, char *log_path)
{
    return bfmr_save_user_space_bfmr_log(pdir, log_path);
}


static int bfmr_save_user_space_bfmr_log(char *pdir, char *log_path)
{
    int fd_src = -1;
    int ret = -1;
    char dst_file_name[PATH_MAXLEN] = {0};
    char *psrc_file_data = NULL;
    char *ptemp = NULL;
    long src_file_len = 0L;
    mm_segment_t oldfs;
    long bytes_to_read = 0;
    long bytes_read = 0;

    if (unlikely((NULL == pdir) || (NULL == log_path) || (0 == strlen(log_path))))
    {
        BFM_PRINT_DBG("File: %s Line: %d invalid parameters!\n", __FILE__, __LINE__);
        return -1;
    }

    BFM_PRINT_ERR("func: %s pdir: %s log_path: %s\n", __func__, pdir, log_path);

    oldfs = get_fs();
    set_fs(KERNEL_DS);

    /* parse the source file name */
    ptemp = strrchr(log_path, '/');
    ptemp = (NULL == ptemp) ? (log_path) : (ptemp);
    strncpy(dst_file_name, ptemp, MIN((sizeof(dst_file_name) - 1), strlen(ptemp)));

    /* get the length of the source file */
    src_file_len = bfmr_get_file_length(log_path);
    if (src_file_len <= 0)
    {
        BFM_PRINT_ERR("File: %s Line: %d log_path: %s src_file_len: %ld!\n", __FILE__, __LINE__, log_path, src_file_len);
        goto __out;
    }

    psrc_file_data = (char *)vmalloc(src_file_len);
    if (NULL == psrc_file_data)
    {
        BFM_PRINT_ERR("File: %s Line: %d src_file_len: %ld!\n", __FILE__, __LINE__, src_file_len);
        goto __out;
    }
    memset((void *)psrc_file_data, 0, src_file_len);

    fd_src = sys_open(log_path, O_RDONLY, 0);
    if (fd_src < 0)
    {
        BFM_PRINT_ERR("File: %s Line: %d sys_open [%s] failed: %d! src_file_len: %ld\n", __FILE__, __LINE__, log_path, fd_src, src_file_len);
        goto __out;
    }

    /* read data from the user space source file */
    bytes_to_read = src_file_len;
    ptemp = psrc_file_data;
    while (bytes_to_read > 0)
    {
        bytes_read = sys_read(fd_src, ptemp, bytes_to_read);
        if (bytes_read < 0)
        {
            BFM_PRINT_ERR("File: %s Line: %d sys_read failed: %ld!\n", __FILE__, __LINE__, bytes_read);
            goto __out;
        }
        bytes_to_read -= bytes_read;
        ptemp += bytes_read;
    }

    /* write data to dst file */
    ret = bfmr_save_log(pdir, dst_file_name, psrc_file_data, (u32)src_file_len, 0);

__out:
    if (fd_src > 0)
    {
        sys_close(fd_src);
    }

    /* remove critical process crash log in /data */
    if (NULL != strstr(log_path, BFMR_CRITICAL_PROCESS_CRASH_LOG_NAME))
    {
        sys_unlink(log_path);
    }

    set_fs(oldfs);
    vfree(psrc_file_data);

    return ret;
}


/*******************************************************************************
Function:       bfmr_save_boot_fail_log_to_log_part
Description:    save dfx's ddr_buffer to file
Input:          dfx_head_info
Output:         NA
Return:         0:success
********************************************************************************/
static int bfmr_save_boot_fail_log_to_log_part(struct dfx_head_info *dfx_head_info)
{
	char *buf;
	char *pfile_data = NULL;
	int last_number;
	struct every_number_info *every_number_info;
	char path[PATH_MAXLEN];
	int need_save_number;
	enum BFM_ERRNO_CODE bfmErrNo;
	enum BFM_BOOT_STAGE_CODE bfmStageCode;
	void  *bfi_rcv_info_buf;
	need_save_number = dfx_head_info->need_save_number;
	u64 bytes_need_for_this_log = 0LL;
	bool need_save_framework_bfmr_log = false;

	BFM_PRINT_START();

	if (need_save_number > TOTAL_NUMBER) {
		return -1;
	}

    	bfi_rcv_info_buf = kmalloc(SZ_4K, GFP_KERNEL);
    	if (!bfi_rcv_info_buf) {
    		BFM_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
    		return -1;
    	}

	pfile_data = (char *)vmalloc(BFMR_TEMP_BUF_LEN);
	if (NULL == pfile_data)
	{
		kfree(bfi_rcv_info_buf);
		BFM_PRINT_ERR("%s():%d:vmalloc buf failed!\n", __func__, __LINE__);
		return -1;
	}

	bfmr_create_log_path(BFM_PATH_ROOT);
	bfmr_create_log_path(BFMR_UPLOADED_PATH);
	memset(path, 0, sizeof(path));
	last_number = (dfx_head_info->cur_number - dfx_head_info->need_save_number + TOTAL_NUMBER)%TOTAL_NUMBER;
	while (0 != need_save_number) {
		BFM_PRINT_ERR("%s: need_save_number is %d, last_number is %d\n", __func__, need_save_number, last_number);
		buf = (char *)dfx_head_info + dfx_head_info->every_number_addr[last_number];
		every_number_info = (struct every_number_info *)buf;
		memset(path, 0, sizeof(path));

        	BFM_PRINT_ERR("%s: every_number_info->reboot_type is 0x%08x\n", __func__, every_number_info->reboot_type);

		if(bfmr_get_info_from_bfi_part((struct bfi_every_number_Info  *)bfi_rcv_info_buf, every_number_info->rtc_time)){
			BFM_PRINT_ERR("%s():%d:bfmr_get_info_from_bfi_part fail\n", __func__, __LINE__);
			kfree(bfi_rcv_info_buf);
			vfree(pfile_data);
			return -1;
		}

		/* check if the log is existed or not */
		if (bfmr_is_log_existed(every_number_info->rtc_time,
			((struct bfi_every_number_Info *)bfi_rcv_info_buf)->bfmErrNo))
		{
			need_save_number--;
			last_number = (last_number + 1 + TOTAL_NUMBER) % TOTAL_NUMBER;
			continue;
		}

		/* delete the oldest log if necessary */
		bytes_need_for_this_log = (PATH_MAXLEN + PATH_MAXLEN + every_number_info->fastbootlog_size
			+ every_number_info->last_kmsg_size + every_number_info->last_applog_size
			+ BFMR_BYTES_REDUNDANT_ON_LOG_PART);
		if ((-1 != (int)bfmr_get_boot_fail_errno()) && bfmr_is_file_existed(BFMR_LOGCAT_FILE_PATH))
		{
			bytes_need_for_this_log += (bfmr_get_file_length(BFMR_LOGCAT_FILE_PATH) >= (BFMR_BOOT_FAIL_LOGCAT_FILE_MAX_SIZE))
				? ((u64)BFMR_BOOT_FAIL_LOGCAT_FILE_MAX_SIZE) : (bfmr_get_file_length(BFMR_LOGCAT_FILE_PATH));
		}

		if ((bfmr_is_file_existed(bfmr_get_user_space_log_path())))
		{
			bytes_need_for_this_log += bfmr_get_file_length(bfmr_get_user_space_log_path());
		}

		if (((int)bfmr_get_boot_fail_errno() > (int)ANDROID_FRAMEWORK_ERRNO_START)
	            && (NULL != bfmr_get_user_space_log_path())
	            && (0 != strncmp(bfmr_get_user_space_log_path(), BFMR_FRAMEWORK_BOOT_FAIL_LOG_PATH,
	            strlen(BFMR_FRAMEWORK_BOOT_FAIL_LOG_PATH))))
		{
	            need_save_framework_bfmr_log = true;
	            bytes_need_for_this_log += bfmr_get_file_length(BFMR_FRAMEWORK_BOOT_FAIL_LOG_PATH);
		}
		bfmr_delete_oldest_log(bytes_need_for_this_log);

		if (0 != bfmr_create_bfm_log_path(&path[0], every_number_info->rtc_time, ((struct bfi_every_number_Info  *)bfi_rcv_info_buf)->bfmErrNo)) {
			BFM_PRINT_ERR("bbox_create_dfxlog_path fail\n");
			kfree(bfi_rcv_info_buf);
			vfree(pfile_data);
			return -1;
		}
		BFM_PRINT_ERR("Log full path: %s\n", path);

		memset((void *)pfile_data, 0, BFMR_TEMP_BUF_LEN);
		bfmErrNo = (enum BFM_ERRNO_CODE)((struct bfi_every_number_Info *)bfi_rcv_info_buf)->bfmErrNo;
		bfmStageCode = (enum BFM_BOOT_STAGE_CODE)((struct bfi_every_number_Info *)bfi_rcv_info_buf)->bfmStageCode;
		snprintf(pfile_data, BFMR_TEMP_BUF_LEN - 1, BFMR_BFI_FILE_CONTENT_FORMAT,
                    bfmr_get_timestamp(every_number_info->rtc_time),
                    bfmr_get_platform_name(),
                    bfmr_get_boot_stage_name((unsigned int)bfmErrNo, (unsigned int)bfmStageCode),
                    bfmr_get_boot_fail_no_desc((unsigned int)bfmErrNo),
                    bfmr_get_platform_name(),
                    bfmr_get_boot_stage_name((unsigned int)bfmErrNo, (unsigned int)bfmStageCode),
                    ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->isSystemRooted,
                    ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->isUserPerceptiable,
             		every_number_info->rtc_time,
                    (unsigned int)bfmErrNo,
                    (unsigned int)bfmStageCode,
                    ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->isSystemRooted,
                    ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->isUserPerceptiable,
                    bfmr_get_bootlock_value_from_cmdline());
		bfmr_save_log(path, BFI_FILE_NAME, pfile_data, strlen(pfile_data), 0);

		if(bfmr_get_info_from_bfi_part((struct bfi_every_number_Info  *)bfi_rcv_info_buf, every_number_info->rtc_time)){
        		BFM_PRINT_ERR("%s():%d:bfmr_get_info_from_bfi_part fail\n", __func__, __LINE__);
        		kfree(bfi_rcv_info_buf);
        		vfree(pfile_data);
        		return -1;
		}

		memset((void *)pfile_data, 0, BFMR_TEMP_BUF_LEN);
		snprintf(pfile_data, BFMR_TEMP_BUF_LEN - 1, BFMR_RCV_FILE_CONTENT_FORMAT,
                    bfmr_get_recovery_method_desc(((struct bfi_every_number_Info *)bfi_rcv_info_buf)->rcvMethod),
                    (0 != ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->rcvResult) ? "success" : "fail",
                    ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->rcvMethod,
                    ((struct bfi_every_number_Info *)bfi_rcv_info_buf)->rcvResult);
		bfmr_save_log(path, RCV_FILE_NAME, pfile_data, strlen(pfile_data),0);

		if (every_number_info->fastbootlog_size != 0) {
			bfmr_save_log(path,
				"fastboot_log",
				(char *)every_number_info + every_number_info->fastbootlog_start_addr,
				every_number_info->fastbootlog_size,
				0);
		}

		if (every_number_info->last_kmsg_size != 0) {
			bfmr_save_log(path,
				"last_kmsg",
				(char *)every_number_info + every_number_info->last_kmsg_start_addr,
				every_number_info->last_kmsg_size,
				0);
		}

		if (every_number_info->last_applog_size != 0) {
			bfmr_save_log(path,
				"pmsg-ramoops-0",
				(char *)every_number_info + every_number_info->last_applog_start_addr,
				every_number_info->last_applog_size,
				0);
		}

		if (-1 != (int)bfmr_get_boot_fail_errno())
		{
			bfmr_save_logcat_on_beta_version(path);
		}

		need_save_number--;
		last_number = (last_number + 1 + TOTAL_NUMBER)%TOTAL_NUMBER;
	}

	/* release memory */
	kfree(bfi_rcv_info_buf);
	vfree(pfile_data);

	switch ((enum BFM_ERRNO_CODE)bfmr_get_boot_fail_errno())
	{
	case CRITICAL_SERVICE_FAIL_TO_START:
	    {
	        if (0 == strlen(path))
	        {
	            BFM_PRINT_ERR("func: %s line: %d log path is:[%s]\n", __func__, __LINE__, path);
	            break;
	        }
	        (void)bfmr_save_tombstone_dropbox_log(path, bfmr_get_user_space_log_path());
	        break;
	    }
	default:
	    {
	        if (0 == strlen(path))
	        {
	            BFM_PRINT_ERR("func: %s line: %d log path is:[%s]\n", __func__, __LINE__, path);
	            break;
	        }
	        (void)bfmr_save_user_space_bfmr_log(path, bfmr_get_user_space_log_path());
	        if (need_save_framework_bfmr_log)
	        {
	            bfmr_save_user_space_bfmr_log(path, BFMR_FRAMEWORK_BOOT_FAIL_LOG_PATH);
	        }
	        break;
	    }
	}

	return 0;
}


/*******************************************************************************
Function:       save_hwbootfailInfo_to_file
Description:    save dfx and bfi partition's log to file
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void save_hwbootfailInfo_to_file(void)
{
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	void *buf, *dfx_buf, *dfx_buf_temp;
	int ret, fd_dfx, cnt, need_read_size;
	struct dfx_head_info * dfx_head_info;
	bool is_need_save_dfx2file = false;
	int i;

	BFM_PRINT_START();
	fd_dfx = -1;
	BFM_PRINT_DBG("============wait for fs /splash2 ready start =============\n");
	if (0 != bfmr_wait_for_log_part_with_timeout(BFMR_HISI_LOG_MOUNT_POINT,
		BFMR_WAIT_LOG_PART_NORMAL_TIMEOUT)) {
		BFM_PRINT_ERR("%s():%d:/splash2 is not ready\n", __func__, __LINE__);
		return;
	}
	BFM_PRINT_DBG("============wait for fs /splash2 ready end =============\n");

	buf = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf) {
		BFM_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		return;
	}

	dfx_buf = vmalloc(DFX_USED_SIZE);
	if (!dfx_buf) {
		BFM_PRINT_ERR("%s():%d:vmalloc dfx_buf fail\n", __func__, __LINE__);
		kfree(buf);
		return;
	}

	ret = flash_find_ptn(PART_DFX, buf);
	if (ret != 0) {
		BFM_PRINT_ERR(
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
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
		goto out;
	}

	dfx_buf_temp = dfx_buf;
	need_read_size = DFX_USED_SIZE;
	memset((void *)dfx_buf_temp, 0, DFX_USED_SIZE);

	i = 0;
	while (need_read_size > 0) {
		cnt = sys_read(fd_dfx, buf, SZ_4K);
		if (cnt < 0) {
			BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
			goto close;
		}
                if(i==0) {
                	dfx_head_info = (struct dfx_head_info *)buf;
                     BFM_PRINT_DBG("dfx_head_info->need_save_number is %d\n", dfx_head_info->need_save_number);

                	if (DFX_MAGIC_NUMBER == dfx_head_info->magic &&
                	    dfx_head_info->need_save_number > 0 &&
                	    dfx_head_info->need_save_number <= TOTAL_NUMBER) {
                		is_need_save_dfx2file = true;
                	}else{
                	break;
                      }
                }
		memcpy((void *)dfx_buf_temp, (const void *)buf, cnt);
		dfx_buf_temp = dfx_buf_temp + cnt;
		need_read_size -= cnt;
            i++;
	}

	sys_close(fd_dfx);
	fd_dfx = -1;
	if(is_need_save_dfx2file){
		ret = bfmr_save_boot_fail_log_to_log_part((struct dfx_head_info *)dfx_buf);
		if (ret) {
        		BFM_PRINT_ERR(
        		    "%s():%d:save_dfxbuffer_to_file fail[%d]\n",
        		    __func__, __LINE__, ret);
        		goto out;
        	}
        }
        else
        {
            BFM_PRINT_ERR("File: %s Line: %d no log need be saved!\n", __FILE__, __LINE__);
        }

close:
	if (fd_dfx > 0)
	{
		sys_close(fd_dfx);
	}
out:
	set_fs(oldfs);
	vfree(dfx_buf);
	kfree(buf);
	return;
}

void notify_boot_success(){
	void *buf1;
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	struct bfi_head_info *bfi_head_info;
	struct bfi_every_number_Info *bfi_memeber_info;
	int fd_bfi = -1, ret, cnt, cur_number, cfo;
	char *pfile_data = NULL;
	BFM_PRINT_START();
	boot_status_notify(1);
	buf1 = NULL;
	fd_bfi = 0;
	buf1 = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf1) {
		BFM_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		return;
	}

	ret = flash_find_ptn(PART_BFI, buf1);
	if (ret != 0) {
            ret = flash_find_ptn(PART_BFI_TEMP, buf1);
	}

	if (ret != 0) {
		BFM_PRINT_ERR(
		    "%s():%d:flash_find_ptn fail[%d]\n",
		    __func__, __LINE__, ret);
              goto out;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf1, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_bfi = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_bfi < 0) {
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_bfi);
		goto close;
	}

       //read out header of bfi
	memset(buf1, 0, SZ_4K);
	cnt = sys_read(fd_bfi, buf1, SZ_4K);
	if (cnt < 0) {
		BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}
	bfi_head_info = (struct bfi_head_info *)buf1;
	cur_number = bfi_head_info->cur_number;
	cur_number = ((cur_number == 0)?(BFI_RECOVERY_LOG_TOTAL_NUMBER -1):(cur_number-1));
	cfo = BFI_HEAD_SIZE + cur_number * bfi_head_info->every_number_size;
	BFM_PRINT_ERR("bfi_head_info information: bfi_head_info->cur_number is %d, cur_number is %d cfo is %d \n", bfi_head_info->cur_number, cur_number, cfo);

       //read out latest member infor
	ret = sys_lseek(fd_bfi, cfo, SEEK_SET);
	if (ret != cfo) {
		BFM_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}
	memset(buf1, 0, SZ_4K);
	cnt = sys_read(fd_bfi, buf1, SZ_4K);
	if (cnt < 0) {
		BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}
	sys_close(fd_bfi);

	//change the result into success;
	bfi_memeber_info = (struct bfi_every_number_Info *)buf1;
	bfi_memeber_info->rcvResult = 1;
	BFM_PRINT_ERR("bfi_memeber_info information: rtc is 0x%x, rcvResult is %d rcvMethod: %d\n",
		bfi_memeber_info->rtcValue, bfi_memeber_info->rcvResult, bfi_memeber_info->rcvMethod);

	fd_bfi = sys_open(p_name, O_WRONLY, FILE_LIMIT);
	if (fd_bfi < 0) {
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_bfi);
		goto close;
	}

	ret = sys_lseek(fd_bfi, cfo, SEEK_SET);
	if (ret != cfo) {
		BFM_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}

	cnt = sys_write(fd_bfi, buf1, SZ_4K);
	if (cnt <= 0) {
		BFM_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}
	BFM_PRINT_END();

close:
	if (fd_bfi > 0) {
		sys_fsync(fd_bfi);
		sys_close(fd_bfi);
	}

	pfile_data = (char *)vmalloc(BFMR_TEMP_BUF_LEN);
	if (NULL == pfile_data)
	{
            BFM_PRINT_ERR("%s():%d: vmalloc failed!\n", __func__, __LINE__);
            goto out;
	}
	memset(pfile_data, 0, BFMR_TEMP_BUF_LEN);

	snprintf(pfile_data, BFMR_TEMP_BUF_LEN - 1, BFMR_RCV_FILE_CONTENT_FORMAT,
		bfmr_get_recovery_method_desc(bfi_memeber_info->rcvMethod),
		(0 != bfi_memeber_info->rcvResult) ? "success" : "fail",
		bfi_memeber_info->rcvMethod,
		bfi_memeber_info->rcvResult);
	(void)bfmr_renew_recovery_info(pfile_data, strlen(pfile_data), 0L);
	bfmr_create_done_file_for_every_log(BFM_PATH_ROOT);
out:
	if (buf1) {
		kfree(buf1);
	}

	if (NULL != pfile_data)
	{
		vfree(pfile_data);
	}

	set_fs(oldfs);

	return;
}
/*****************************************************************************
Description : 将一个文件的内容copy到另一个文件中
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int rdr_copy_file_apend(char *dst, char *src)
{
	long fddst, fdsrc;
	char buf[SZ_4K / 4];
	static mm_segment_t oldfs;
	long cnt;
	int ret = 0;

	if (NULL == dst || NULL == src) {
		pr_err("rdr:%s():dst(0x%p) or src(0x%p) is NULL.\n",
		       __func__, dst, src);
		return -1;
	}

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fdsrc = sys_open(src, O_RDONLY, FILE_LIMIT);
	if (fdsrc < 0) {
		pr_err("rdr:%s():open %s failed, return [%ld]\n",
		       __func__, src, fdsrc);
		ret = -1;
		goto out;
	}
	fddst =
	    sys_open(dst, O_CREAT | O_WRONLY | O_APPEND, FILE_LIMIT);
	if (fddst < 0) {
		pr_err("rdr:%s():open %s failed, return [%ld]\n",
		       __func__, dst, fddst);
		sys_close(fdsrc);
		ret = -1;
		goto out;
	}

	while (1) {
		cnt = sys_read(fdsrc, buf, SZ_4K / 4);
		if (cnt == 0)
			break;
		if (cnt < 0) {
			pr_err
			    ("rdr:%s():read %s failed, return [%ld]\n",
			     __func__, src, cnt);
			ret = -1;
			goto close;
		}

		cnt = sys_write(fddst, buf, SZ_4K / 4);
		if (cnt <= 0) {
			pr_err
			    ("rdr:%s():write %s failed, return [%ld]\n",
			     __func__, dst, cnt);
			ret = -1;
			goto close;
		}
	}

close:
	sys_close(fdsrc);
	sys_close(fddst);
out:
	set_fs(oldfs);
	return ret;
}

static void bfmr_save_log_to_bfi_part(u32 modID,
    suggested_recovery_method_e suggested_recovery_method)
{
       u64 latestRTCTime;
        void *buf1, *buf2, *dfx_buf, *dfx_buf_temp, *bfi_buf;
	static mm_segment_t oldfs;
	char p_name[BDEVNAME_SIZE + 12];
	struct bfi_head_info *bfi_head_info;
       int fd_dfx, fd_bfi;
	int ret, cnt, cfo, cur_number, need_read_size, need_write_size;
    struct every_number_info *every_number_info_buf;
    struct dfx_head_info * dfx_head_info;
       struct bfi_every_number_Info bfmInfoBuf;
       enum BFM_BOOT_STAGE_CODE latestBootStageCode;
	BFM_PRINT_START();

       buf1 = buf2 = NULL;
       fd_dfx = fd_bfi = -1;

	buf1 = kmalloc(SZ_4K, GFP_KERNEL);
	if (!buf1) {
		BFM_PRINT_ERR("%s():%d:kmalloc buf fail\n", __func__, __LINE__);
		return;
	}


	ret = flash_find_ptn(PART_DFX, buf1);
	if (ret != 0) {
		BFM_PRINT_ERR(
		    "%s():%d:flash_find_ptn fail[%d]\n",
		    __func__, __LINE__, ret);
              goto out;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf1, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fd_dfx = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_dfx < 0) {
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_dfx);
              goto out;
	}

	buf2 = vmalloc(DFX_HEAD_SIZE);
	if (!buf2) {
		BFM_PRINT_ERR("%s():%d:vmalloc dfx_buf fail\n", __func__, __LINE__);
              goto close;
	}
       dfx_buf_temp = dfx_buf = buf2;
	need_read_size = DFX_HEAD_SIZE;
	memset((void *)dfx_buf_temp, 0, DFX_HEAD_SIZE);
	while (need_read_size > 0) {
		cnt = sys_read(fd_dfx, buf1, SZ_4K);
		if (cnt < 0) {
			BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
			goto close;
		}

		memcpy((void *)dfx_buf_temp, (const void *)buf1, cnt);
		dfx_buf_temp = dfx_buf_temp + cnt;
		need_read_size -= cnt;
	}
      	dfx_head_info = (struct dfx_head_info *)dfx_buf;
       cur_number = dfx_head_info->cur_number;
       cur_number = (cur_number == 0)?(TOTAL_NUMBER -1):(cur_number-1);
	cfo = dfx_head_info->every_number_addr[cur_number];
	ret = sys_lseek(fd_dfx, cfo, SEEK_SET);
	if (ret != cfo) {
		BFM_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}
	cnt = sys_read(fd_dfx, buf1, SZ_4K);
	if (cnt < 0) {
		BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}
     	every_number_info_buf = (struct every_number_info *)buf1;
       latestRTCTime = every_number_info_buf->rtc_time;
       BFM_PRINT_ERR("cur_number is %d, latestRTCTime is 0x%x\n", cur_number, latestRTCTime);

	sys_close(fd_dfx);
	fd_dfx = -1;

 	ret = flash_find_ptn(PART_BFI, buf1);
 	if (0 != ret) {
 	    ret = flash_find_ptn(PART_BFI_TEMP, buf1);
 	}

	if (0 != ret) {
		BFM_PRINT_ERR("%s():%d:flash_find_ptn fail\n", __func__, __LINE__);
		goto close;
	}

	memset(p_name, 0, sizeof(p_name));
	strncpy(p_name, buf1, sizeof(p_name));
	p_name[BDEVNAME_SIZE + 11] = '\0';

	fd_bfi = sys_open(p_name, O_RDONLY, FILE_LIMIT);
	if (fd_bfi < 0) {
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_bfi);
		goto close;
	}

       //read out header of bfi
	memset(buf1, 0, SZ_4K);
	cnt = sys_read(fd_bfi, buf1, SZ_4K);
	if (cnt < 0) {
		BFM_PRINT_ERR("%s():%d:read fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}
	bfi_head_info = (struct bfi_head_info *)buf1;
	sys_close(fd_bfi);
	fd_bfi = -1;

       //write bfm information
       bfmInfoBuf.rtcValue = latestRTCTime;
       bfmInfoBuf.bfmErrNo = mntn_modid_to_bfm_errno(modID);
       get_boot_stage(&latestBootStageCode);
       bfmInfoBuf.bfmStageCode = latestBootStageCode;
       bfmInfoBuf.isSystemRooted = isSystemRooted;
       bfmInfoBuf.isUserPerceptiable = g_isUserPerceptible;
       //try_to_recovery();
       bfmInfoBuf.rcvMethod = try_to_recovery(bfmInfoBuf.rtcValue, bfmInfoBuf.bfmErrNo,
           bfmInfoBuf.bfmStageCode, suggested_recovery_method, NULL);
       bfmInfoBuf.rcvResult = 0;
	memset(buf2, 0, DFX_HEAD_SIZE);
	memcpy(buf2, (void *)&bfmInfoBuf, sizeof(struct bfi_every_number_Info));

	fd_bfi = sys_open(p_name, O_WRONLY, FILE_LIMIT);
	if (fd_bfi < 0) {
		BFM_PRINT_ERR("%s():%d:open fail[%d]\n", __func__, __LINE__, fd_bfi);
		goto close;
	}
	cfo = BFI_HEAD_SIZE + bfi_head_info->cur_number * bfi_head_info->every_number_size;
	ret = sys_lseek(fd_bfi, cfo, SEEK_SET);
	if (ret != cfo) {
		BFM_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}
	cnt = sys_write(fd_bfi, buf2, sizeof(struct bfi_every_number_Info));
	if (cnt <= 0) {
		BFM_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}

	ret = sys_lseek(fd_bfi, 0, SEEK_SET);
	if (ret != 0) {
		BFM_PRINT_ERR("%s():%d:lseek fail[%d]\n", __func__, __LINE__, ret);
		goto close;
	}
	bfi_head_info->cur_number = (bfi_head_info->cur_number+1)%BFI_RECOVERY_LOG_TOTAL_NUMBER;
	cnt = sys_write(fd_bfi, buf1, SZ_4K);
	if (cnt <= 0) {
		BFM_PRINT_ERR("%s():%d:write fail[%d]\n", __func__, __LINE__, cnt);
		goto close;
	}
close:
       if(fd_dfx > 0) {
        sys_fsync(fd_dfx);
        sys_close(fd_dfx);
        }
       if(fd_bfi > 0) {
        sys_fsync(fd_bfi);
        sys_close(fd_bfi);
        }
out:
       if(buf1) {
        kfree(buf1);
        }
       if(buf2) {
        vfree(buf2);
        }
	set_fs(oldfs);
	return;
}

void bfmr_save_log_to_log_part(u32 reboot_type, u32 mod_id, int suggested_recovery_method)
{
    systemerror_save_log2dfx(reboot_type);
    bfmr_save_log_to_bfi_part(mod_id,
        (suggested_recovery_method_e)suggested_recovery_method);
    save_hwbootfailInfo_to_file();
}

/*******************************************************************************
Function:       systemerror_save_log2dfx
Description:    save log to dfx partition when bbox_system_error is called
Input:          reboot_type
Output:         NA
Return:         NA
********************************************************************************/
void error_save_log2splash2(u32 etype, u32 mod_id) {
    systemerror_save_log2dfx(etype);
    bfmr_save_log_to_bfi_part(mod_id, NO_SUGGESTION);
    save_hwbootfailInfo_to_file();
}

struct rdr_exception_info_s eInfo[] = {
#if 0
	{{0, 0}, MODID_BFM_BOOT_TIMEOUT, MODID_BFM_BOOT_TIMEOUT, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_BFM, RDR_AP|RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_TIMEOUT, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_NATIVE_START, MODID_BFM_NATIVE_END, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_BFM, RDR_AP|RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_NATIVE_BOOT_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_FRAMEWORK_LEVEL_START, MODID_BFM_FRAMEWORK_LEVEL_END, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_BFM, RDR_AP|RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_FRAMEWORK_BOOT_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED, RDR_ERR,
	 RDR_REBOOT_NO, RDR_BFM, RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, 0, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},
#else
#if 0
	{{0, 0}, MODID_BFM_BOOT_TIMEOUT, MODID_BFM_BOOT_TIMEOUT, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_TIMEOUT, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_NATIVE_START, MODID_BFM_NATIVE_END, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_BFM, RDR_AP|RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_NATIVE_BOOT_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_FRAMEWORK_LEVEL_START, MODID_BFM_FRAMEWORK_LEVEL_END, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_BFM, RDR_AP|RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_FRAMEWORK_BOOT_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED, RDR_ERR,
	 RDR_REBOOT_NO, RDR_BFM, RDR_BFM, RDR_BFM,
	 RDR_REENTRANT_DISALLOW, 0, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},
#else
	{{0, 0}, MODID_BFM_BOOT_TIMEOUT, MODID_BFM_BOOT_TIMEOUT, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP | RDR_BFM, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_TIMEOUT, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_NATIVE_START, MODID_BFM_NATIVE_END, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP | RDR_BFM, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_NATIVE_BOOT_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

        {{0, 0}, MODID_BFM_NATIVE_DATA_START, MODID_BFM_NATIVE_DATA_END, RDR_ERR,
        RDR_REBOOT_NOW, RDR_AP | RDR_BFM, RDR_AP, RDR_AP,
        RDR_REENTRANT_DISALLOW, BFM_S_BOOT_NATIVE_DATA_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
        0, 0, 0},

	{{0, 0}, MODID_BFM_FRAMEWORK_LEVEL_START, MODID_BFM_FRAMEWORK_LEVEL_END, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP | RDR_BFM, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, BFM_S_BOOT_FRAMEWORK_BOOT_FAIL, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

	{{0, 0}, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED, RDR_WARN,
	 RDR_REBOOT_NO, RDR_AP | RDR_BFM, 0, RDR_AP,
	 RDR_REENTRANT_DISALLOW, 0, RDR_UPLOAD_YES, "bfm", "bfm-boot-TO",
	 0, 0, 0},

#endif
#endif
};

/*****************************************************************************
Description : 向rdr注册异常
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static void rdr_hwbfm_register_exception(void)
{
	int i;
	u32 ret;
	for (i = 0;
	     i < sizeof(eInfo) / sizeof(struct rdr_exception_info_s);
	     i++) {
		printk("register exception:%d", eInfo[i].e_exce_type);
		ret = rdr_register_exception(&eInfo[i]);
		if (ret == 0) {
			printk(KERN_ERR
			       "rdr_register_exception fail, ret = [%d]\n",
			       ret);
		}
	}
	printk("[%s], end\n", __func__);
}

void bfmr_dump(u32 modid, u32 etype, u64 coreid, char *log_path,
		     pfn_cb_dump_done pfn_cb)
{
    BFM_PRINT_START();
    if (BFM_S_BOOT_NATIVE_DATA_FAIL == etype)
    {
        preempt_enable();
    }

    systemerror_save_log2dfx(etype);
    bfmr_save_log_to_bfi_part(modid, NO_SUGGESTION);
    if (0 != bfmr_wait_for_log_part_without_timeout(BFMR_HISI_LOG_MOUNT_POINT))
    {
        BFM_PRINT_ERR("%s():%d:/splash2 is not ready\n", __func__, __LINE__);
    }
    else
    {
        save_hwbootfailInfo_to_file();
    }

    pfn_cb(modid, coreid);
    if (BFM_S_BOOT_NATIVE_DATA_FAIL == etype)
    {
        preempt_disable();
    }
    BFM_PRINT_END();
}

/*****************************************************************************
Description : 异常时，ap的reset函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void bfmr_reset(u32 modid, u32 etype, u64 coreid)
{
	BFM_PRINT_START();
	BFM_PRINT_END();
}


/*****************************************************************************
Description : 向rdr注册dump和reset函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int rdr_hwbfm_register_core(void)
{
	struct rdr_module_ops_pub s_soc_ops;
	struct rdr_register_module_result retinfo;
	int ret = 0;
	u64 coreid = RDR_BFM;

	s_soc_ops.ops_dump = bfmr_dump;
	s_soc_ops.ops_reset = bfmr_reset;

	ret = rdr_register_module_ops(coreid, &s_soc_ops, &retinfo);
	if (ret < 0) {
		printk(KERN_ERR
		       "rdr_register_module_ops fail, ret = [%d]\n",
		       ret);
		return ret;
	}
	return ret;
}


/*****************************************************************************
Description : 初始化函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
int __init rdr_hwbfm_init(void)
{
	int ret = 0;

	printk("%s init start\n", __func__);
	ret = rdr_hwbfm_register_core();
	if (ret) {
		printk("%s rdr_hwbfm_register_core fail, ret = [%d]\n",
		       __func__, ret);
		//return ret;
	}
	rdr_hwbfm_register_exception();

	printk("%s init end\n", __func__);

	return 0;
}


static void __exit rdr_hwbfm_exit(void)
{
	return;
}
module_init(rdr_hwbfm_init);
module_exit(rdr_hwbfm_exit);

MODULE_LICENSE("GPL");

