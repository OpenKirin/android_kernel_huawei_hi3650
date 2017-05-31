#include <linux/module.h>
#include <linux/time.h>
#include <linux/workqueue.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/hisi/hisi_bootup_keypoint.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/kthread.h>
#include <linux/vmalloc.h>
#include <linux/mutex.h>
#include <chipset_common/hwbfm/hwboot_fail_hisi_interface.h>
#include <chipset_common/hwbfm/hwboot_fail_print.h>
#include <chipset_common/hwbfm/hw_boot_fail_core.h>

int g_isUserPerceptible = FALSE;
char bfmLogFilePath[MAX_LOGPATH] = {0,};
enum BFM_ERRNO_CODE g_bfmErrNo;

#define BFRM_BLOCK_CALLING_PROCESS_IMTERVAL (3600 * 1000)

typedef struct bfmr_process_boot_fail_err_param
{
    enum BFM_ERRNO_CODE bf_errno;
    u32 modid;
    enum SUGGESTED_RECOVERY_METHOD suggested_recovery_method;
    u32 reboot_type;
} bfmr_process_boot_fail_err_param_t;

static struct bfmToMntnStageNo bfm_to_mntn_stagecode_map[] = {
	{BL1_STAGE_START, STAGE_XLOADER_START},
	{BL1_PL1_STAGE_DDR_INIT_FAIL, STAGE_XLOADER_DDR_INIT_FAIL},
	{BL1_PL1_STAGE_DDR_INIT_OK, STAGE_XLOADER_DDR_INIT_OK},
	{BL1_PL1_STAGE_EMMC_INIT_FAIL, STAGE_XLOADER_EMMC_INIT_FAIL},
	{BL1_PL1_STAGE_EMMC_INIT_OK, STAGE_XLOADER_EMMC_INIT_OK},
	{BL1_PL1_STAGE_RD_VRL_FAIL, STAGE_XLOADER_RD_VRL_FAIL},
	{BL1_PL1_STAGE_CHECK_VRL_ERROR, STAGE_XLOADER_CHECK_VRL_ERROR},
	{BL1_PL1_STAGE_READ_FASTBOOT_FAIL, STAGE_XLOADER_READ_FASTBOOT_FAIL},
	{BL1_PL1_STAGE_LOAD_HIBENCH_FAIL, STAGE_XLOADER_LOAD_HIBENCH_FAIL},
	{BL1_PL1_STAGE_SEC_VERIFY_FAIL, STAGE_XLOADER_SEC_VERIFY_FAIL},
 	{BL1_PL1_STAGE_VRL_CHECK_ERROR, STAGE_XLOADER_VRL_CHECK_ERROR},
	{BL1_PL1_SECURE_VERIFY_ERROR, STAGE_XLOADER_SECURE_VERIFY_ERROR},
	{BL1_STAGE_END, STAGE_XLOADER_END},

	{BL2_STAGE_START, STAGE_FASTBOOT_START},
	{BL2_STAGE_EMMC_INIT_START, STAGE_FASTBOOT_EMMC_INIT_START},
	{BL2_STAGE_EMMC_INIT_FAIL, STAGE_FASTBOOT_EMMC_INIT_FAIL},
	{BL2_STAGE_EMMC_INIT_OK, STAGE_FASTBOOT_EMMC_INIT_OK},
	{BL2_PL1_STAGE_DDR_INIT_START, STAGE_FASTBOOT_DDR_INIT_START},
	{BL2_PL1_STAGE_DISPLAY_INIT_START, STAGE_FASTBOOT_DISPLAY_INIT_START},
	{BL2_PL1_STAGE_PRE_BOOT_INIT_START, STAGE_FASTBOOT_PRE_BOOT_INIT_START},
	{BL2_PL1_STAGE_LD_OTHER_IMGS_START, STAGE_FASTBOOT_LD_OTHER_IMGS_START},
	{BL2_PL1_STAGE_LD_KERNEL_IMG_START, STAGE_FASTBOOT_LD_KERNEL_IMG_START},
	{BL2_PL1_STAGE_BOOT_KERNEL_START, STAGE_FASTBOOT_BOOT_KERNEL_START},
	{BL2_STAGE_END, STAGE_FASTBOOT_END},

    {KERNEL_EARLY_INITCALL, STAGE_KERNEL_EARLY_INITCALL},
    {KERNEL_PURE_INITCALL, STAGE_KERNEL_PURE_INITCALL},
    {KERNEL_CORE_INITCALL_SYNC, STAGE_KERNEL_CORE_INITCALL},
    {KERNEL_CORE_INITCALL_SYNC, STAGE_KERNEL_CORE_INITCALL_SYNC},
    {KERNEL_POSTCORE_INITCALL, STAGE_KERNEL_POSTCORE_INITCALL},
    {KERNEL_POSTCORE_INITCALL_SYNC, STAGE_KERNEL_POSTCORE_INITCALL_SYNC},
    {KERNEL_ARCH_INITCALL, STAGE_KERNEL_ARCH_INITCALL},
    {KERNEL_ARCH_INITCALLC, STAGE_KERNEL_ARCH_INITCALLC},
    {KERNEL_SUBSYS_INITCALL, STAGE_KERNEL_SUBSYS_INITCALL},
    {KERNEL_SUBSYS_INITCALL_SYNC, STAGE_KERNEL_SUBSYS_INITCALL_SYNC},
    {KERNEL_FS_INITCALL, STAGE_KERNEL_FS_INITCALL},
    {KERNEL_FS_INITCALL_SYNC, STAGE_KERNEL_FS_INITCALL_SYNC},

    {KERNEL_ROOTFS_INITCALL, STAGE_KERNEL_ROOTFS_INITCALL},
    {KERNEL_DEVICE_INITCALL, STAGE_KERNEL_DEVICE_INITCALL},
    {KERNEL_DEVICE_INITCALL_SYNC, STAGE_KERNEL_DEVICE_INITCALL_SYNC},
    {KERNEL_LATE_INITCALL, STAGE_KERNEL_LATE_INITCALL},
    {KERNEL_LATE_INITCALL_SYNC, STAGE_KERNEL_LATE_INITCALL_SYNC},
    {KERNEL_CONSOLE_INITCALL, STAGE_KERNEL_CONSOLE_INITCALL},
    {KERNEL_SECURITY_INITCALL, STAGE_KERNEL_SECURITY_INITCALL},
    {KERNEL_BOOTANIM_COMPLETE, STAGE_KERNEL_BOOTANIM_COMPLETE},

    {STAGE_INIT_START, STAGE_INIT_INIT_START},
    {STAGE_ON_EARLY_INIT, STAGE_INIT_ON_EARLY_INIT},
    {STAGE_ON_INIT, STAGE_INIT_ON_INIT},
    {STAGE_ON_EARLY_FS, STAGE_INIT_ON_EARLY_FS},
    {STAGE_ON_FS, STAGE_INIT_ON_FS},
    {STAGE_ON_POST_FS, STAGE_INIT_ON_POST_FS},
    {STAGE_ON_POST_FS_DATA, STAGE_INIT_ON_POST_FS_DATA},
    {STAGE_ON_EARLY_BOOT, STAGE_INIT_ON_EARLY_BOOT},
    {STAGE_ON_BOOT, STAGE_INIT_ON_BOOT},

    {STAGE_ZYGOTE_START, STAGE_ANDROID_ZYGOTE_START},
    {STAGE_VM_START, STAGE_ANDROID_VM_START},
    {STAGE_PHASE_WAIT_FOR_DEFAULT_DISPLAY, STAGE_ANDROID_PHASE_WAIT_FOR_DEFAULT_DISPLAY},
    {STAGE_PHASE_LOCK_SETTINGS_READY, STAGE_ANDROID_PHASE_LOCK_SETTINGS_READY},
    {STAGE_PHASE_SYSTEM_SERVICES_READY, STAGE_ANDROID_PHASE_SYSTEM_SERVICES_READY},
    {STAGE_PHASE_ACTIVITY_MANAGER_READY, STAGE_ANDROID_PHASE_ACTIVITY_MANAGER_READY},
    {STAGE_PHASE_THIRD_PARTY_APPS_CAN_START, STAGE_ANDROID_PHASE_THIRD_PARTY_APPS_CAN_START},

    {STAGE_BOOT_SUCCESS, STAGE_ANDROID_BOOT_SUCCESS},
};

static struct bfmToMntnModID bfm_to_mntn_modid_map[] = {
	{KERNEL_BOOT_TIMEOUT, MODID_BFM_BOOT_TIMEOUT},


	{SYSTEM_MOUNT_FAIL, MODID_BFM_NATIVE_SYS_MOUNT_FAIL},
	{SECURITY_FAIL, MODID_BFM_NATIVE_SECURITY_FAIL},
	{CRITICAL_SERVICE_FAIL_TO_START, MODID_BFM_NATIVE_CRITICAL_SERVICE_FAIL_TO_START},
	{DATA_MOUNT_FAILED_AND_ERASED, MODID_BFM_NATIVE_DATA_MOUNT_FAILED_AND_ERASED},
	{DATA_MOUNT_RO, MODID_BFM_NATIVE_DATA_MOUNT_RO},
	{DATA_NOSPC, MODID_BFM_NATIVE_DATA_NOSPC},
	{VENDOR_MOUNT_FAIL, MODID_BFM_NATIVE_VENDOR_MOUNT_FAIL},

	{SYSTEM_SERVICE_LOAD_FAIL, MODID_BFM_FRAMEWORK_SYS_SERVICE_LOAD_FAIL},
	{PREBOOT_BROADCAST_FAIL, MODID_BFM_FRAMEWORK_PREBOOT_BROADCAST_FAIL},
	{VM_OAT_FILE_DAMAGED, MODID_BFM_FRAMEWORK_VM_OAT_FILE_DAMAGED},
	{PACKAGE_MANAGER_SETTING_FILE_DAMAGED, MODID_BFM_FRAMEWORK_PACKAGE_MANAGER_SETTING_FILE_DAMAGED},

        //TBD: add more bootErrNo from kernel and application level.
};

static struct bfmToMntnRebootReason bfm_to_mntn_reboot_reason_map[] = {
	{BL1_DDR_INIT_FAIL, XLOADER_S_DDRINIT_FAIL},
	{BL1_EMMC_INIT_FAIL, XLOADER_S_EMMCINIT_FAIL},
	{BL1_BL2_LOAD_FAIL, XLOADER_S_LOAD_FAIL},
	{BL1_BL2_VERIFY_FAIL, XLOADER_S_VERIFY_FAIL},
	{BL1_WDT, XLOADER_S_WATCHDOG},

	{BL2_EMMC_INIT_FAIL, FASTBOOT_S_EMMCINIT_FAIL},
	{BL2_PANIC, FASTBOOT_S_PANIC},
	{BL2_WDT, FASTBOOT_S_WATCHDOG},
	{BL2_PL1_OCV_ERROR, FASTBOOT_S_OCV_VOL_ERR},
	{BL2_PL1_BAT_TEMP_ERROR, FASTBOOT_S_BAT_TEMP_ERR},
	{BL2_PL1_MISC_ERROR, FASTBOOT_S_MISC_ERR},
	{BL2_PL1_DTIMG_ERROR, FASTBOOT_S_LOAD_DTIMG_ERR},
	{BL2_PL1_LOAD_OTHER_IMGS_ERRNO, FASTBOOT_S_LOAD_OTHER_IMGS_ERR},
	{BL2_PL1_KERNEL_IMG_ERROR, FASTBOOT_S_KERNEL_IMG_ERR},

	{KERNEL_AP_PANIC, AP_S_PANIC},
	//{KERNEL_EMMC_INIT_FAIL, FASTBOOT_S_PANIC},
	{KERNEL_AP_WDT, AP_S_AWDT},
	{KERNEL_PRESS10S, AP_S_PRESS6S},
	{KERNEL_BOOT_TIMEOUT, BFM_S_BOOT_TIMEOUT},
	{KERNEL_AP_COMBINATIONKEY, KERNEL_AP_COMBINATIONKEY},

	{KERNEL_AP_S_ABNORMAL, AP_S_ABNORMAL},
	{KERNEL_AP_S_TSENSOR0, AP_S_TSENSOR0},
	{KERNEL_AP_S_TSENSOR1, AP_S_TSENSOR1},
	{KERNEL_LPM3_S_GLOBALWDT, LPM3_S_GLOBALWDT},
	{KERNEL_G3D_S_G3DTSENSOR, G3D_S_G3DTSENSOR},
	{KERNEL_LPM3_S_LPMCURST, LPM3_S_LPMCURST},
	{KERNEL_CP_S_CPTSENSOR, CP_S_CPTSENSOR},
	{KERNEL_IOM3_S_IOMCURST, IOM3_S_IOMCURST},
	{KERNEL_ASP_S_ASPWD, ASP_S_ASPWD},
	{KERNEL_CP_S_CPWD, CP_S_CPWD},
	{KERNEL_IVP_S_IVPWD, IVP_S_IVPWD},
	{KERNEL_ISP_S_ISPWD, ISP_S_ISPWD},

	{KERNEL_AP_S_DDR_UCE_WD, AP_S_DDR_UCE_WD},
	{KERNEL_AP_S_DDR_FATAL_INTER, AP_S_DDR_FATAL_INTER},
	{KERNEL_AP_S_DDR_SEC, AP_S_DDRC_SEC},
	{KERNEL_AP_S_MAILBOX, AP_S_MAILBOX},

	{KERNEL_CP_S_MODEMDMSS, CP_S_MODEMDMSS},
	{KERNEL_CP_S_MODEMNOC, CP_S_MODEMNOC},
	{KERNEL_CP_S_MODEMAP, CP_S_MODEMAP},
	{KERNEL_CP_S_EXCEPTION, CP_S_EXCEPTION},
	{KERNEL_CP_S_RESETFAIL, CP_S_RESETFAIL},
	{KERNEL_CP_S_NORMALRESET, CP_S_NORMALRESET},
	{KERNEL_CP_S_ABNORMAL, CP_S_NORMALRESET},

	{KERNEL_LPM3_S_EXCEPTION, LPM3_S_EXCEPTION},
	{KERNEL_HIFI_S_EXCEPTION, SOCHIFI_S_EXCEPTION},
	{KERNEL_HIFI_S_RESETFAIL, HIFI_S_RESETFAIL},
	{KERNEL_ISP_S_EXCEPTION, ISP_S_EXCEPTION},
	{KERNEL_IVP_S_EXCEPTION, IVP_S_EXCEPTION},
	{KERNEL_IOM3_S_EXCEPTION, IOM3_S_EXCEPTION},
	{KERNEL_TEE_S_EXCEPTION, TEE_S_EXCEPTION},
	{KERNEL_MMC_S_EXCEPTION, MMC_S_EXCEPTION},

	{KERNEL_CODECHIFI_S_EXCEPTION, CODECHIFI_S_EXCEPTION},
	{KERNEL_CP_S_RILD_EXCEPTION, CP_S_RILD_EXCEPTION},
	{KERNEL_CP_S_3RD_EXCEPTION, CP_S_3RD_EXCEPTION},
	{KERNEL_IOM3_S_USER_EXCEPTION, IOM3_S_USER_EXCEPTION},

	{NATIVE_ERRNO_START, BFM_S_BOOT_NATIVE_BOOT_FAIL},
	{ANDROID_FRAMEWORK_ERRNO_START, BFM_S_BOOT_FRAMEWORK_BOOT_FAIL},
};

static unsigned int s_boot_fail_errno = (unsigned int)(-1);
static char s_user_space_log_path[4096] = {0};
static DEFINE_MUTEX(s_process_boot_fail_mutex);

static unsigned int get_bfm_to_mntn_map_stagecode_size(void);
static unsigned int get_bfm_to_mntn_reboot_reason_map_size(void);
static unsigned int get_bfm_to_mntn_modid_map_size(void);
static void bfmr_block_calling_process_when_boot_fail(void);
static int bfmr_process_boot_fail_err(void *param);

static unsigned int get_bfm_to_mntn_map_stagecode_size(void)
{
    return (unsigned int)(sizeof(bfm_to_mntn_stagecode_map) /
    		      sizeof(struct bfmToMntnStageNo));
}

u32 bfm_to_mntn_stagecode(enum BFM_BOOT_STAGE_CODE stageCode){
    unsigned int i;
    unsigned int size = get_bfm_to_mntn_map_stagecode_size();
    for (i = 0; i < size; i++) {
        if(bfm_to_mntn_stagecode_map[i].bfmStageCode == stageCode) {
            return bfm_to_mntn_stagecode_map[i].mntnStageNo;
    	}
    }
    return -1;
}
enum BFM_BOOT_STAGE_CODE mntn_to_bfm_stagecode(u32 stageNo){
    unsigned int i;
    for (i = 0; i < get_bfm_to_mntn_map_stagecode_size(); i++) {
        if((bfm_to_mntn_stagecode_map[i].mntnStageNo) == stageNo) {
            return bfm_to_mntn_stagecode_map[i].bfmStageCode;
        }
    }
    return -1;
}

static unsigned int get_bfm_to_mntn_reboot_reason_map_size(void)
{
	return (unsigned int)(sizeof(bfm_to_mntn_reboot_reason_map) /
			      sizeof(struct bfmToMntnRebootReason));
}
u32 bfm_to_mntn_reboot_reason(enum BFM_ERRNO_CODE bootErrNo){
	unsigned int i;
       unsigned int size = get_bfm_to_mntn_reboot_reason_map_size();
       for (i = 0; i < size; i++) {
		if(bfm_to_mntn_reboot_reason_map[i].bfmErrNo == bootErrNo) {
			return bfm_to_mntn_reboot_reason_map[i].mntnRebootReason;
		}
	}
	return -1;
}

enum BFM_ERRNO_CODE mntn_reboot_reason_to_bfm_errno(u32 mntnRBReason){
	unsigned int i;
	for (i = 0; i < get_bfm_to_mntn_reboot_reason_map_size(); i++) {
		if(bfm_to_mntn_reboot_reason_map[i].mntnRebootReason == mntnRBReason) {
			return bfm_to_mntn_reboot_reason_map[i].bfmErrNo;
		}
	}
	return -1;
}

static unsigned int get_bfm_to_mntn_modid_map_size(void)
{
	return (unsigned int)(sizeof(bfm_to_mntn_modid_map) /
			      sizeof(struct bfmToMntnModID));
}
u32 bfm_to_mntn_modid(enum BFM_ERRNO_CODE bootErrNo){
	unsigned int i;
       unsigned int size = get_bfm_to_mntn_modid_map_size();

	for (i = 0; i < size; i++) {
		if(bfm_to_mntn_modid_map[i].bfmErrNo == bootErrNo) {
			return bfm_to_mntn_modid_map[i].mntnModID;
		}
	}
	return -1;
}

enum BFM_ERRNO_CODE mntn_modid_to_bfm_errno(u32 modID){
	unsigned int i;
       unsigned int size = get_bfm_to_mntn_modid_map_size();

	for (i = 0; i < size; i++) {
		if(bfm_to_mntn_modid_map[i].mntnModID == modID) {
			return bfm_to_mntn_modid_map[i].bfmErrNo;
		}
	}
	return -1;
}

/************************************************************
Function:      get_boot_stage
Description:   get current boot stage during boot process
Input:          pBootStageValue:   address of returned boot stage value
Output:         boot stage value to be saved into pBootStageValue if valid
Return:        0 -- SUCCESS/OK
                   1 -- FAIL/ERROR
*************************************************************/
int get_boot_stage(enum BFM_BOOT_STAGE_CODE *pBootStageCode){
    u32 mntnStageCode;
    mntnStageCode = get_boot_keypoint();
    *pBootStageCode = mntn_to_bfm_stagecode(mntnStageCode);
    BFM_PRINT_DBG("get_boot_stage: mntnStageCode is 0x%x, pBootStageCode is 0x%x\n", mntnStageCode, *pBootStageCode);
    return 0;
}

static int do_notify_boot_success(void *param)
{
    notify_boot_success();
}

/************************************************************
Function:      set_boot_stage
Description:   set boot stage as input value
Input:          bootStageValue:   boot stage value to be set
Output:        N/A
Return:        0 -- SUCCESS/OK
                   1 -- FAIL/ERROR
*************************************************************/
int set_boot_stage(enum BFM_BOOT_STAGE_CODE bootStageCode){
    u32 mntnStageCode;
    mntnStageCode = bfm_to_mntn_stagecode(bootStageCode);
    set_boot_keypoint(mntnStageCode);
    BFM_PRINT_DBG("set_boot_stage: mntnStageCode is 0x%x, bootStageCode is 0x%x\n", mntnStageCode, bootStageCode);
    if(isBootSuccess(bootStageCode)) {
        BFM_PRINT_DBG("boot success!\n");
        boot_timer_stop();
        kthread_run(do_notify_boot_success, NULL, "notify_boot_success");
    }
    return 0;
}

static void bfmr_block_calling_process_when_boot_fail(void)
{
    while (1)
    {
        msleep(BFRM_BLOCK_CALLING_PROCESS_IMTERVAL);
    }
}

static int bfmr_process_boot_fail_err(void *param)
{
    bfmr_process_boot_fail_err_param_t *pparam =
        (bfmr_process_boot_fail_err_param_t*)param;

    if (DO_NOTHING == pparam->suggested_recovery_method)
    {
        BFM_PRINT_ERR("func: %s suggested recovery method is: \"DO_NOTHING\"\n", __func__);
        bfmr_save_log_to_log_part(pparam->reboot_type, pparam->modid,
            pparam->suggested_recovery_method);
        mutex_unlock(&s_process_boot_fail_mutex);
        return 0;
    }

    switch (pparam->bf_errno)
    {
    case SYSTEM_MOUNT_FAIL:
    case DATA_MOUNT_FAILED_AND_ERASED:
    case DATA_MOUNT_RO:
    case DATA_NOSPC:
    case VENDOR_MOUNT_FAIL:
        {
            rdr_syserr_process_for_ap(pparam->modid, 0, 0);
            break;
        }
    default:
        {
            rdr_system_error(pparam->modid, 0, 0);
            break;
        }
    }

    vfree(pparam);

    return 0;
}

void bfmr_set_boot_fail_errno(unsigned int boot_fail_errno)
{
    s_boot_fail_errno = boot_fail_errno;
}

unsigned int bfmr_get_boot_fail_errno(void)
{
    return s_boot_fail_errno;
}

void bfmr_set_user_space_log_path(char *log_path)
{
    unsigned int log_path_len = 0;
    unsigned int local_buf_len = sizeof(s_user_space_log_path);

    if (unlikely(NULL == log_path))
    {
        return;
    }

    log_path_len = (unsigned int)strlen(log_path);
    memcpy((void *)s_user_space_log_path, log_path,
        ((local_buf_len - 1) <= log_path_len) ? (local_buf_len - 1) : (log_path_len));
}

char *bfmr_get_user_space_log_path(void)
{
    return s_user_space_log_path;
}

/************************************************************
Function:      boot_fail_err
Description:   to save the log and do proper recovery actions,
                    while meet with error during system booting process.
Input:          bootErrNo:   boot fail errorNo.
                   sugRcvMtd:  suggested recovery method.
                   pLogFilePath:  path of logFile, if an additional log file existed
                                      and need to be saved.
Output:         NA
Return:        0 -- SUCCESS/OK
                   1 -- FAIL/ERROR
*************************************************************/
int boot_fail_err(enum BFM_ERRNO_CODE bootErrNo, enum SUGGESTED_RECOVERY_METHOD sugRcvMtd/* = NO_SUGGESTION*/, char *pLogFilePath/* = NULL*/){
    int ret = -1;
    u32 mntnModID = bfm_to_mntn_modid(bootErrNo);
    int pBootStageCode;
    bfmr_process_boot_fail_err_param_t *pparam = NULL;

    mutex_lock(&s_process_boot_fail_mutex);
    msleep(1000); /* sleep 1s to distinguish the log name in case of the 2 boot fail occurs at the same time*/
    get_boot_stage(&pBootStageCode);
    if (STAGE_BOOT_SUCCESS == (enum BFM_BOOT_STAGE_CODE)pBootStageCode
        && (CRITICAL_SERVICE_FAIL_TO_START != bootErrNo)){
        BFM_PRINT_ERR("Error: can't set errno after device boot success!\n");
        goto __out;
    }

    g_isUserPerceptible = (sugRcvMtd!=DO_NOTHING);
    memset(bfmLogFilePath, 0x0, MAX_LOGPATH);
    if(pLogFilePath) {
        strncpy(bfmLogFilePath, pLogFilePath, MAX_LOGPATH);
    }

    BFM_PRINT_ERR("mntnModID: is 0x%x bootErrNo: 0x%x\n", mntnModID, bootErrNo);

    if (-1 == (int)mntnModID)
    {
        BFM_PRINT_ERR("Error: mntnModID: is 0x%x\n", mntnModID);
        goto __out;
    }

    pparam = (bfmr_process_boot_fail_err_param_t*)vmalloc(sizeof(bfmr_process_boot_fail_err_param_t));
    if (NULL == pparam)
    {
        BFM_PRINT_ERR("Error: func: %s kmalloc failed!\n", __func__);
        goto __out;
    }

    ret = 0;
    memset((void *)pparam, 0, sizeof(bfmr_process_boot_fail_err_param_t));
    pparam->bf_errno = bootErrNo;
    pparam->modid = mntnModID;
    pparam->suggested_recovery_method = sugRcvMtd;
    pparam->reboot_type = REBOOT_REASON_LABEL9;
    bfmr_set_boot_fail_errno((unsigned int)bootErrNo);
    bfmr_set_user_space_log_path(pLogFilePath);
    kthread_run(bfmr_process_boot_fail_err, (void *)pparam, "bfmr_process_boot_fai");
    if (DO_NOTHING != sugRcvMtd)
    {
        bfmr_block_calling_process_when_boot_fail();
    }
    else
    {
        return ret;
    }

__out:
    mutex_unlock(&s_process_boot_fail_mutex);

    return ret;
}


