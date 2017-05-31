/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: boot_fail_recovery.c

    @brief: source file of module-"boot fail recovery".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/printk.h>
#include <asm/string.h>
#include <chipset_common/hwbfm/hwboot_fail_public_interface.h>
#include <chipset_common/hwbfm/hwbfr/boot_fail_recovery.h>
#include <chipset_common/hwbfm/hwbfr/recovery_record.h>
#include <chipset_common/hwbfm/hwbfr/misc_set.h>
#include <chipset_common/hwbfm/hwbfr/enter_erecovery_reason.h>


/*----local macroes------------------------------------------------------------------*/

#define RECOVERY_RECORD_READ_MAX_COUNT (5)
#define MAX_FAILURE_TIMES_ALLOWED_BEFORE_GOTO_ERECOVERY (2)
#define DEBUG_BFR 1
#if DEBUG_BFR
#define PRINT_ENTER_PROMPT() do {printk(KERN_ERR "Enter File: %s Line:%d func: %s\n", __FILE__, __LINE__, __FUNCTION__);} while (0)
#define PRINT_EXIT_PROMPT() do {printk(KERN_ERR "Exit File: %s Line:%d func: %s\n", __FILE__, __LINE__, __FUNCTION__);} while (0)
#define PRINTLINE() do {printk(KERN_ERR "File: %s Line:%d func: %s\n", __FILE__, __LINE__, __FUNCTION__);} while (0)
#else
#define PRINT_ENTER_PROMPT() do {;} while (0)
#define PRINT_EXIT_PROMPT() do {;} while (0)
#endif


/*----local prototypes----------------------------------------------------------------*/

typedef struct recovery_method_select_param
{
    unsigned int cur_boot_fail_stage; //本次不开机发生的阶段
    unsigned int cur_boot_fail_no; //本次不开机的故障原因
    suggested_recovery_method_e suggested_recovery_method; //本次不开机的建议恢复方法
    int latest_valid_recovery_record_count; //最近有效的不开机记录总数
    failure_recovery_record_t latest_recovery_record[RECOVERY_RECORD_READ_MAX_COUNT]; //最近5次未恢复的不开机记录
} recovery_method_select_param_t;


/*----local variables------------------------------------------------------------------*/

static boot_fail_enter_erecovery_reason_map_t s_enter_erecovery_reason_map[] =
{
    {{BL1_ERRNO_START, BL1_PL1_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL},
    {{BL1_PL1_START, BL1_PL2_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL},
    {{BL1_PL2_START, BL2_ERRNO_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL},
    {{BL2_ERRNO_START, BL2_PL1_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL},
    {{BL2_PL1_START, BL2_PL2_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL},
    {{BL2_PL2_START, KERNEL_ERRNO_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_BOOTLOADER_BOOT_FAIL},
    {{KERNEL_ERRNO_START, KERNEL_PL1_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_KERNEL_BOOT_FAIL},
    {{KERNEL_PL1_START, KERNEL_PL2_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_KERNEL_BOOT_FAIL},
    {{KERNEL_PL2_START, NATIVE_ERRNO_START - 1}, ENTER_ERECOVERY_REASON_BECAUSE_KERNEL_BOOT_FAIL},
    {{SYSTEM_MOUNT_FAIL, SYSTEM_MOUNT_FAIL}, ENTER_ERECOVERY_BECAUSE_SYSTEM_MOUNT_FAILED},
    {{SECURITY_FAIL, SECURITY_FAIL}, ENTER_ERECOVERY_BECAUSE_SECURITY_FAIL},
    {{CRITICAL_SERVICE_FAIL_TO_START, CRITICAL_SERVICE_FAIL_TO_START}, ENTER_ERECOVERY_BECAUSE_KEY_PROCESS_START_FAILED},
    {{DATA_MOUNT_FAILED_AND_ERASED, DATA_MOUNT_FAILED_AND_ERASED}, ENTER_ERECOVERY_BECAUSE_DATA_MOUNT_FAILED},
    {{DATA_MOUNT_RO, DATA_MOUNT_RO}, ENTER_ERECOVERY_BECAUSE_DATA_MOUNT_RO},
    {{VENDOR_MOUNT_FAIL, VENDOR_MOUNT_FAIL}, ENTER_ERECOVERY_BECAUSE_VENDOR_MOUNT_FAILED},
    {{NATIVE_ERRNO_START, PACKAGE_MANAGER_SETTING_FILE_DAMAGED}, ENTER_ERECOVERY_BECAUSE_APP_BOOT_FAIL},
};

#if defined(CONFIG_USE_AB_SYSTEM)
static failure_recovery_policy_e s_fixed_recovery_policy[] =
{
    {
        SYSTEM_MOUNT_FAIL, 1,
        {
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY}
        },
    },
};
#else
static failure_recovery_policy_e s_fixed_recovery_policy[] =
{
    {
        SYSTEM_MOUNT_FAIL, 1,
        {
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY}
        },
    },
    {
        VENDOR_MOUNT_FAIL, 1,
        {
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY}
        },
    },
    {
        CRITICAL_SERVICE_FAIL_TO_START, 1,
        {
            {1, FRM_REBOOT},
            {1, FRM_GOTO_ERECOVERY_FACTORY_RESET},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
        },
    },
    {
        DATA_MOUNT_FAILED_AND_ERASED, 1,
        {
            {1, FRM_REBOOT},
            {1, FRM_GOTO_ERECOVERY_FACTORY_RESET},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
        },
    },
    {
        DATA_MOUNT_RO, 1,
        {
            {1, FRM_REBOOT},
            {1, FRM_GOTO_ERECOVERY_LOWLEVEL_FORMAT_DATA},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
        },
    },
    {
        DATA_NOSPC, 1,
        {
            {1, FRM_GOTO_ERECOVERY_DEL_FILES_FOR_NOSPC},
            {1, FRM_GOTO_ERECOVERY_FACTORY_RESET},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
            {1, FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY},
        },
    },
};
#endif


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

static failure_recovery_method_e select_recovery_method(
    recovery_method_select_param_t *pselect_param);
static int run_recovery_method(failure_recovery_method_e recovery_method,
    unsigned int boot_fail_stage,
    unsigned int boot_fail_no);
static unsigned int get_enter_erecovery_reason(unsigned int boot_fail_no);
static bool boot_fail_no_has_fixed_recovery_method(
    unsigned int boot_fail_no,
    int failed_times_in_application,
    failure_recovery_method_e *pfixed_recovery_method);
static recovery_method_running_status_code_e init_recovery_method_running_status_code(
    failure_recovery_method_e recovery_method);
static recovery_method_run_result_e init_recovery_method_run_result(
    failure_recovery_method_e recovery_method);
#if defined(CONFIG_USE_AB_SYSTEM)
static int another_system_is_ok(void);
static void goto_another_system(void);
#endif


/*----function definitions--------------------------------------------------------------*/

#if defined(CONFIG_USE_AB_SYSTEM)
static int another_system_is_ok(void)
{
    return 1;
}


static void goto_another_system(void)
{
    return;
}
#endif


static bool boot_fail_no_has_fixed_recovery_method(
    unsigned int boot_fail_no,
    int failed_times_in_application,
    failure_recovery_method_e *pfixed_recovery_method)
{
    int count = sizeof(s_fixed_recovery_policy) / sizeof(s_fixed_recovery_policy[0]);
    int i = 0;

    if (unlikely(NULL == pfixed_recovery_method))
    {
        printk(KERN_ERR "Invalid parameters!\n");
        return false;
    }

    for (i = 0; i < count; i++)
    {
        if (boot_fail_no != s_fixed_recovery_policy[i].boot_fail_no)
        {
            continue;
        }

        if (0 != s_fixed_recovery_policy[i].has_fixed_policy)
        {
            int method_count = sizeof(s_fixed_recovery_policy[i].param)
                / sizeof(s_fixed_recovery_policy[i].param[0]);

            if ((failed_times_in_application <= 0) || (failed_times_in_application > method_count))
            {
                *pfixed_recovery_method = FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY;
                return true;
            }

            failed_times_in_application--;
            if (0 != s_fixed_recovery_policy[i].param[failed_times_in_application].enable_this_method)
            {
                *pfixed_recovery_method = s_fixed_recovery_policy[i].param[failed_times_in_application].recovery_method;
            }
            else
            {
                *pfixed_recovery_method = FRM_DO_NOTHING;
            }

            printk(KERN_ERR "ErrNo: %x recovery_method: %x\n", boot_fail_no, *pfixed_recovery_method);

            return true;
        }
        else
        {
            break;
        }
    }

    return false;
}


static failure_recovery_method_e select_recovery_method(
    recovery_method_select_param_t *pselect_param)
{
    int i = 0;
    int recovery_failed_times_total = 0;
    int recovery_failed_times_in_bottom_layer = 0;
    int recovery_failed_times_in_application = 0;
    failure_recovery_method_e fixed_recovery_method = FRM_DO_NOTHING;
    bool has_fixed_recovery_method = false;

    PRINT_ENTER_PROMPT();

    if (NULL == pselect_param)
    {
        printk(KERN_ERR "File: %s Line: %d Invalid parameters!\n", __FILE__, __LINE__);
        return FRM_DO_NOTHING;
    }

    /* record count is >= 3 */
    for (i= 0; i < pselect_param->latest_valid_recovery_record_count; i++)
    {
        if (BOOT_FAIL_RECOVERY_SUCCESS == pselect_param->latest_recovery_record[i].recovery_result)
        {
            recovery_failed_times_total = 0;
            recovery_failed_times_in_bottom_layer = 0;
        }
        else
        {
            recovery_failed_times_total++;
            if (pselect_param->latest_recovery_record[i].boot_fail_stage < NATIVE_STAGE_START)
            {
                recovery_failed_times_in_bottom_layer++;
            }
        }
    }

    recovery_failed_times_total++;
    if (pselect_param->cur_boot_fail_stage < NATIVE_STAGE_START)
    {
        recovery_failed_times_in_bottom_layer++;
    }
    recovery_failed_times_in_application = recovery_failed_times_total - recovery_failed_times_in_bottom_layer;
    printk(KERN_ERR "bf_total_times:%d bf_bottom_layer_times: %d bf_app_times: %d\n",
        recovery_failed_times_total, recovery_failed_times_in_bottom_layer,
        recovery_failed_times_in_application);

    /* It is the first failure */
    has_fixed_recovery_method = boot_fail_no_has_fixed_recovery_method(
        pselect_param->cur_boot_fail_no, recovery_failed_times_in_application, &fixed_recovery_method);
    if (0 == pselect_param->latest_valid_recovery_record_count)
    {
        printk(KERN_ERR "System has no valid recovery record, the boot fail occurs in [%s]\n",
            (pselect_param->cur_boot_fail_stage < NATIVE_STAGE_START)
            ? ("Bottom layer") : ("APP"));
        if (has_fixed_recovery_method)
        {
            return fixed_recovery_method;
        }

        return FRM_REBOOT;
    }

    switch (recovery_failed_times_in_bottom_layer)
    {
    case 0:
        {
            if (has_fixed_recovery_method)
            {
                printk(KERN_ERR "[Bottom layer has no boot fail] APP has fixed recovery method: [%d]\n",
                    fixed_recovery_method);
                return fixed_recovery_method;
            }

            switch (recovery_failed_times_in_application)
            {
            case 1:
                {
                    printk(KERN_ERR "[Bottom layer has no boot fail] FRM_REBOOT\n");
                    return FRM_REBOOT;
                }
            case 2:
                {
                    printk(KERN_ERR "[Bottom layer has no boot fail] FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF\n");
                    return FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF;
                }
            case 3:
                {
                    printk(KERN_ERR "[Bottom layer has no boot fail] FRM_GOTO_ERECOVERY_FACTORY_RESET\n");
                    return FRM_GOTO_ERECOVERY_FACTORY_RESET;
                }
            case 4:
            default:
                {
                    printk(KERN_ERR "[Bottom layer has no boot fail] FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY\n");
                    return FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY;
                }
            }
            break;
        }
    case 1:
    case 2:
        {
            if (has_fixed_recovery_method)
            {
                printk(KERN_ERR "[Bottom layer has 1 or 2 boot fail] APP has fixed recovery method\n");
                return fixed_recovery_method;
            }

            switch (recovery_failed_times_in_application)
            {
            case 0:
                {
                    printk(KERN_ERR "[APP has no Bootfail] FRM_REBOOT\n");
                    return FRM_REBOOT;
                }
            case 1:
                {
                    printk(KERN_ERR "[Bottom layer has boot fail] FRM_REBOOT\n");
                    return FRM_REBOOT;
                }
            case 2:
                {
                    printk(KERN_ERR "[Bottom layer has boot fail] FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF\n");
                    return FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF;
                }
            case 3:
            default:
                {
                    printk(KERN_ERR "[Bottom layer has boot fail] FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET\n");
                    return FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET;
                }
            }
            break;
        }
    case 3:
    default:
        {
            printk(KERN_ERR "[APP has no boot fail] FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY\n");
            return FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY;
        }
    }

    PRINT_EXIT_PROMPT();

    return FRM_REBOOT;
}


static unsigned int get_enter_erecovery_reason(unsigned int boot_fail_no)
{
    int i = 0;
    int count = sizeof(s_enter_erecovery_reason_map) / sizeof(s_enter_erecovery_reason_map[0]);

    for (i = 0; i < count; i++)
    {
        if ((boot_fail_no >= s_enter_erecovery_reason_map[i].range.start)
            && boot_fail_no <= s_enter_erecovery_reason_map[i].range.end)
        {
            return s_enter_erecovery_reason_map[i].enter_erecovery_reason;
        }
    }

    return ENTER_ERECOVERY_UNKNOWN;
}


static int run_recovery_method(failure_recovery_method_e recovery_method,
    unsigned int boot_fail_stage,
    unsigned int boot_fail_no)
{
    switch (recovery_method)
    {
#if defined(CONFIG_USE_AB_SYSTEM)
    case FRM_GOTO_B_SYSTEM:
        {
            goto_another_system();
            break;
        }
#endif
    case FRM_GOTO_ERECOVERY_DEL_FILES_FOR_BF:
    case FRM_GOTO_ERECOVERY_DEL_FILES_FOR_NOSPC:
    case FRM_GOTO_ERECOVERY_FACTORY_RESET:
    case FRM_GOTO_ERECOVERY_FORMAT_DATA_PART:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_DEL_FILES:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY:
    case FRM_GOTO_ERECOVERY_LOWLEVEL_FORMAT_DATA:
        {
            enter_erecovery_reason_param_t reason_param;

            memset((void *)&reason_param, 0, sizeof(reason_param));
            memcpy((void *)reason_param.command, (void *)ENTER_ERECOVEYR_COMMAND,
                strlen(ENTER_ERECOVEYR_COMMAND));/*[false alarm]:strlen*/
            reason_param.enter_erecovery_reason = EER_BOOT_FAIL_SOLUTION;
            reason_param.enter_erecovery_reason_number = get_enter_erecovery_reason(boot_fail_no);
            reason_param.boot_fail_stage_for_erecovery = BFS_BOOTLOADER;
            reason_param.recovery_method = (unsigned int)recovery_method;
            reason_param.boot_fail_no = (unsigned int)boot_fail_no;
            (void)save_enter_erecovery_reason(&reason_param);
            (void)set_misc_msg_for_erecovery();
            break;
        }
    case FRM_NOTIFY_USER_RECOVERY_FAILURE:
        {
            break;
        }
    default:
        {
            return 0;
        }
    }

    return 0;
}


void boot_status_notify(int is_success)
{
    failure_recovery_record_t recovery_record;

    PRINT_ENTER_PROMPT();
    printk(KERN_ERR "Recovery boot fail: %s!\n", (is_success) ? ("Successfully") : ("Failed"));
    memset((void *)&recovery_record, 0, sizeof(recovery_record));
    recovery_record.recovery_result = (0 == is_success) ? (BOOT_FAIL_RECOVERY_FAILURE)
        : (BOOT_FAIL_RECOVERY_SUCCESS);
    (void)renew_recovery_record(&recovery_record);
    PRINT_EXIT_PROMPT();
}


static recovery_method_running_status_code_e init_recovery_method_running_status_code(
    failure_recovery_method_e recovery_method)
{
    switch (recovery_method)
    {
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_DEL_FILES:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET:
        {
            return RMRSC_ERECOVERY_BOOT_FAILED;
        }
    default:
        {
            break;
        }
    }

    return RMRSC_EXEC_COMPLETED;
}


static recovery_method_run_result_e init_recovery_method_run_result(
    failure_recovery_method_e recovery_method)
{
    switch (recovery_method)
    {
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_DEL_FILES:
    case FRM_GOTO_ERECOVERY_DOWNLOAD_RECOVERY_AND_FACTORY_RESET:
        {
            return RMRR_FAILED;
        }
    default:
        {
            break;
        }
    }

    return RMRR_SUCCESS;
}


failure_recovery_method_e try_to_recovery(
    unsigned long long boot_fail_detected_time,
    unsigned int boot_fail_no,
    unsigned int boot_fail_stage,
    suggested_recovery_method_e suggested_recovery_method,
    char *args)
{
    int ret = -1;
    int record_count_actually_read = -1;
    failure_recovery_method_e recovery_method = FRM_DO_NOTHING;
    recovery_method_select_param_t pselect_param;
    failure_recovery_record_t recovery_record[RECOVERY_RECORD_READ_MAX_COUNT];
    failure_recovery_record_t cur_recovery_record;

    PRINT_ENTER_PROMPT();
    printk(KERN_ERR "boot_fail_stage:%x NATIVE_STAGE_START: %x boot_fail_no: %x "
        "suggested_recovery_method: %d\n", boot_fail_stage, NATIVE_STAGE_START,
        boot_fail_no, suggested_recovery_method);

    if (DO_NOTHING == suggested_recovery_method)
    {
        return FRM_DO_NOTHING;
    }

    /* 1. read recovery record */
    printk(KERN_ERR "File: %s Line: %d read_recovery_record\n", __FILE__, __LINE__);
    memset(recovery_record, 0, sizeof(recovery_record));
    ret = read_recovery_record(recovery_record, RECOVERY_RECORD_READ_MAX_COUNT,
        &record_count_actually_read);
    if (0 != ret)
    {
        printk(KERN_ERR "read_recovery_record failed!\n");
        return FRM_DO_NOTHING;
    }

    /* 2. select recovery method */
    printk(KERN_ERR "File: %s Line: %d select_recovery_method\n", __FILE__, __LINE__);
    memset((void *)&pselect_param, 0, sizeof(pselect_param));
    pselect_param.cur_boot_fail_stage = boot_fail_stage;
    pselect_param.cur_boot_fail_no = boot_fail_no;
    pselect_param.suggested_recovery_method = suggested_recovery_method;
    pselect_param.latest_valid_recovery_record_count = record_count_actually_read;
    memcpy(&pselect_param.latest_recovery_record, recovery_record, sizeof(recovery_record));
    recovery_method = select_recovery_method(&pselect_param);

    /* 3.save recovery record */
    printk(KERN_ERR "File: %s Line: %d create_recovery_record\n", __FILE__, __LINE__);
    memset((void *)&cur_recovery_record, 0, sizeof(cur_recovery_record));
    cur_recovery_record.boot_fail_detected_time = boot_fail_detected_time;
    cur_recovery_record.boot_fail_stage = boot_fail_stage;
    cur_recovery_record.boot_fail_no = boot_fail_no;
    cur_recovery_record.recovery_method = recovery_method;
    cur_recovery_record.running_status_code = init_recovery_method_running_status_code(recovery_method);
    cur_recovery_record.method_run_result = init_recovery_method_run_result(recovery_method);
    cur_recovery_record.recovery_result = BOOT_FAIL_RECOVERY_FAILURE;
    ret = create_recovery_record(&cur_recovery_record);
    if (0 != ret)
    {
        printk(KERN_ERR "read_recovery_record failed!\n");
        return FRM_DO_NOTHING;
    }

    /* 4. run recovery method. Note: reboot is executed by the caller now */
    printk(KERN_ERR "File: %s Line: %d run_recovery_method\n", __FILE__, __LINE__);
    ret = run_recovery_method(recovery_method, boot_fail_stage, boot_fail_no);
    if (0 != ret)
    {
        printk(KERN_ERR "Failed to run recovery method!\n");
    }

    PRINT_EXIT_PROMPT();

    /* 5. return recovery method to the caller */
    return recovery_method;
}

