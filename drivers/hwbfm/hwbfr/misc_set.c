/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: misc_set.c

    @brief: source file of module-"misc set".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/printk.h>
#include <asm/string.h>
#include <chipset_common/hwbfm/hwbfr/enter_erecovery_reason.h>
#include <chipset_common/hwbfm/hwbfr/emmc_rw.h>


/*----local macroes------------------------------------------------------------------*/

#define MISC_BOOT_ERECOVERY_STR  "boot-erecovery"
#define MISC_DEV_FIRST_PATH "/dev/block/bootdevice/by-name/misc"
#define MISC_DEV_SECOND_PATH "/dev/block/platform/hi_mci.0/by-name/misc"


/*----local prototypes----------------------------------------------------------------*/

typedef struct
{
    char command[32];
    char status[32];
    char recovery[1024];
} misc_message_type;


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

int set_misc_msg_for_erecovery(void)
{
    int ret = -1;
    misc_message_type msg;

    memset((void *)&msg, 0, sizeof(msg));
    memcpy(msg.command, (void *)MISC_BOOT_ERECOVERY_STR, strlen(MISC_BOOT_ERECOVERY_STR));
    ret = write_emmc_part(MISC_DEV_FIRST_PATH, 0x0, (char *)&msg, sizeof(msg));
    if (0 != ret)
    {
        printk("Write misc [%s] failed!\nWrite mics [%s] now!\n",
            MISC_DEV_FIRST_PATH, MISC_DEV_SECOND_PATH);
        ret = write_emmc_part(MISC_DEV_SECOND_PATH, 0x0, (char *)&msg, sizeof(msg));
        if (0 != ret)
        {
            printk("Write misc [%s] failed!\n", MISC_DEV_SECOND_PATH);
        }
    }

    return ret;
}

