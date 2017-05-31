#ifndef __HW_BOOT_FAIL_INTERFACE_H__
#define __HW_BOOT_FAIL_INTERFACE_H__

#include <linux/types.h>

extern int g_isUserPerceptible;
extern char bfmLogFilePath[];

/*******************************************************************************
Function:       save_hwbootfailInfo_to_file
Description:    save dfx and bfi partition's log to file
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void save_hwbootfailInfo_to_file(void);

#ifdef CONFIG_HUAWEI_BFM
bool bfmr_is_enabled(void);
#else
static inline bool bfmr_is_enabled(void)
{
    return false;
}
#endif

void notify_boot_success(void);

void error_save_log2splash2(u32 etype, u32 mod_id);

void bfmr_save_log_to_log_part(u32 reboot_type, u32 mod_id, int suggested_recovery_method);

#endif

