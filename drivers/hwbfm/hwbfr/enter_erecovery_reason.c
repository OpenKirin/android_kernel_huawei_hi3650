/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: enter_erecovery_reason.c

    @brief: source file of module-"enter erecovery reason".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/printk.h>
#include <chipset_common/hwbfm/hwbfr/recovery_record.h>
#include <chipset_common/hwbfm/hwbfr/emmc_rw.h>
#include <chipset_common/hwbfm/hwbfr/enter_erecovery_reason.h>


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

int save_enter_erecovery_reason(enter_erecovery_reason_param_t *reason_param)
{
    if (NULL == reason_param)
    {
        printk("Invalid paramers!\n");
        return -1;
    }

    if (0 != write_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH,
        ENTER_ERECOVERY_REASON_OFFSET, (char *)reason_param,
        (unsigned long long)sizeof(enter_erecovery_reason_param_t)))
    {
        if (0 != write_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH,
            ENTER_ERECOVERY_REASON_OFFSET, (char *)reason_param,
            (unsigned long long)sizeof(enter_erecovery_reason_param_t)))
        {
            printk("Write enter eRecovery reason failed!\n");
            return -1;
        }
    }

    return 0;
}

int read_enter_erecovery_reason(enter_erecovery_reason_param_t *reason_param)
{
    if (NULL == reason_param)
    {
        printk("Invalid paramers!\n");
        return -1;
    }

    if (0 != read_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH,
        ENTER_ERECOVERY_REASON_OFFSET, (char *)reason_param,
        (unsigned long long)sizeof(enter_erecovery_reason_param_t)))
    {
        if (0 != read_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH,
            ENTER_ERECOVERY_REASON_OFFSET, (char *)reason_param,
            (unsigned long long)sizeof(enter_erecovery_reason_param_t)))
        {
            printk("Read enter eRecovery reason failed!\n");
            return -1;
        }
    }

    return 0;
}

