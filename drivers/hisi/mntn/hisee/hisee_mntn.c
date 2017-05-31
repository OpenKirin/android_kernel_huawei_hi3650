#include <linux/dma-mapping.h>
#include <linux/device.h>
#include <linux/of_reserved_mem.h>
#include <linux/platform_device.h>
#include <linux/workqueue.h>

#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/util.h>
#include <linux/hisi/ipc_msg.h>

#include <asm/compiler.h>
#include <m3_interrupts.h>

#include "hisee_mntn.h"
#include "../mntn_filesys.h"

/*lint -e785*/
struct rdr_exception_info_s hisee_excetption_info[] = {
	{
		.e_modid            = MODID_HISEE_EXC_SENSOR_CTRL,
		.e_modid_end        = MODID_HISEE_EXC_SENSOR_CTRL,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECSOR",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SIC,
		.e_modid_end        = MODID_HISEE_EXC_SIC,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SIC",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_MED_ROM,
		.e_modid_end        = MODID_HISEE_EXC_MED_ROM,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE ROM",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_MED_RAM,
		.e_modid_end        = MODID_HISEE_EXC_MED_RAM,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE RAM",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_OTPC,
		.e_modid_end        = MODID_HISEE_EXC_OTPC,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE OTPC",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_HARD,
		.e_modid_end        = MODID_HISEE_EXC_HARD,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE HARD",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_IPC_MAILBOX,
		.e_modid_end        = MODID_HISEE_EXC_IPC_MAILBOX,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE IPC MAILBOX",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_MPU,
		.e_modid_end        = MODID_HISEE_EXC_MPU,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE MPU",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_BUS,
		.e_modid_end        = MODID_HISEE_EXC_BUS,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE BUS",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_TIMER,
		.e_modid_end        = MODID_HISEE_EXC_TIMER,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE TIMER",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SEC_EXTERN,
		.e_modid_end        = MODID_HISEE_EXC_SEC_EXTERN,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE EXTERN",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_WDG,
		.e_modid_end        = MODID_HISEE_EXC_WDG,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE WDG",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SYSALARM,
		.e_modid_end        = MODID_HISEE_EXC_SYSALARM,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SYSALARM",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_TRNG,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_TRNG,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG TRNG",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_TRIM,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_TRIM,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG TRIM",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_SCE,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_SCE,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG SCE",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_RSA,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_RSA,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG RSA",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_SM2,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_SM2,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG SM2",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_KM,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_KM,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG KM",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SECENG_SCRAMBLING,
		.e_modid_end        = MODID_HISEE_EXC_SECENG_SCRAMBLING,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SECENG SCRAMBLING",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_BOTTOM,
		.e_modid_end        = MODID_HISEE_EXC_BOTTOM,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE BOTTOM",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_ALARM0,
		.e_modid_end        = MODID_HISEE_EXC_ALARM0,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE ALARM0",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_ALARM1,
		.e_modid_end        = MODID_HISEE_EXC_ALARM1,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE ALARM1",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_AS2AP_IRQ,
		.e_modid_end        = MODID_HISEE_EXC_AS2AP_IRQ,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE AS2AP IRQ",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_DS2AP_IRQ,
		.e_modid_end        = MODID_HISEE_EXC_DS2AP_IRQ,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE DS2AP IRQ",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_SENC2AP_IRQ,
		.e_modid_end        = MODID_HISEE_EXC_SENC2AP_IRQ,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE SENC2AP IRQ",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_LOCKUP,
		.e_modid_end        = MODID_HISEE_EXC_LOCKUP,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE LOCKUP",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_EH2H_SLV,
		.e_modid_end        = MODID_HISEE_EXC_EH2H_SLV,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE EH2H SLV",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_TSENSOR1,
		.e_modid_end        = MODID_HISEE_EXC_TSENSOR1,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE TSENSOR1",
		.e_desc             = "HISEE",
	},
	{
		.e_modid            = MODID_HISEE_EXC_UNKNOWN,
		.e_modid_end        = MODID_HISEE_EXC_UNKNOWN,
		.e_process_priority = RDR_ERR,
		.e_reboot_priority  = RDR_REBOOT_NO,
		.e_notify_core_mask = RDR_HISEE,
		.e_reset_core_mask  = RDR_HISEE,
		.e_from_core        = RDR_HISEE,
		.e_reentrant        = (u32)RDR_REENTRANT_DISALLOW,
		.e_exce_type        = HISEE_S_EXCEPTION,
		.e_upload_flag      = (u32)RDR_UPLOAD_YES,
		.e_from_module      = "HISEE UNKNOWN",
		.e_desc             = "HISEE",
	}
};
/*lint +e785*/

/*for translation from original irq no to exception type that module id*/
hisee_exc_trans_s hisee_exc_trans[] = {
	{IRQ_INTR_HISEE_ALARM0, MODID_HISEE_EXC_ALARM0},
	{IRQ_INTR_HISEE_ALARM1, MODID_HISEE_EXC_ALARM1},
	{IRQ_INTR_HISEE_AS2AP_IRQ, MODID_HISEE_EXC_AS2AP_IRQ},
	{IRQ_INTR_HISEE_DS2AP_IRQ, MODID_HISEE_EXC_DS2AP_IRQ},
	{IRQ_INTR_HISEE_SENC2AP_IRQ, MODID_HISEE_EXC_SENC2AP_IRQ},
	{IRQ_INTR_HISEE_LOCKUP, MODID_HISEE_EXC_LOCKUP},
	{IRQ_INTR_HISEE_EH2H_SLV, MODID_HISEE_EXC_EH2H_SLV},
	{IRQ_INTR_HISEE_TSENSOR1, MODID_HISEE_EXC_TSENSOR1},

	/*Please add your new member above!!!!*/
};

static u32 hisee_exception_modid;
static struct notifier_block hisee_ipc_block;
static struct rdr_register_module_result hisee_info;
static void *hisee_mntn_addr;
static dma_addr_t hisee_log_phy;
static void __iomem *hisee_log_addr;


static void __hisee_exception_func(struct work_struct *work);
static DECLARE_WORK(hisee_exception_work, __hisee_exception_func);
static struct ipc_msg g_msg;

#ifdef CONFIG_HISI_HISEE_MNTN_TEST
/********************************************************************
Description:	hisee exception test
input:	modid:module id
output:	NA
return:	NA
********************************************************************/
int rdr_hisee_test(u32 modid)
{
	int ret;
	unsigned long i;
	unsigned int msg[3];
	u32 irq_no = 0;

	msg[0] = LPM3_HISEE_MNTN;

	if (modid < (u32)HISI_BB_MOD_HISEE_START ||
		modid > (u32)HISI_BB_MOD_HISEE_END)
		return -ENOEXEC;

	for (i = 0; i < sizeof(hisee_exc_trans) /
		sizeof(hisee_exc_trans_s); i++)
		if (modid == hisee_exc_trans[i].module_value) {
			irq_no = hisee_exc_trans[i].irq_value;
			break;
		}
	if (modid == MODID_HISEE_START) {
		msg[1] = HISEE_TEST_RECORD;
		msg[2] = 1;
	} else if (irq_no) {
		msg[1] = HISEE_TEST_IRQ;
		msg[2] = irq_no;
	} else {
		msg[1] = HISEE_TEST_EXCEPTION;
		msg[2] = modid - MODID_HISEE_START;
	}
	pr_err("%s:msg[1]:%x,msg[2]:%x\n", __func__, msg[1], msg[2]);
	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)&msg, 3);
	if (ret != 0)
		pr_err("%s:RPROC_ASYNC_SEND failed! return 0x%x, msg:(%x)\n",
			__func__, ret, msg[0]);

	return ret;
}
int rdr_hisee_test2(u32 data)
{
	int ret;
	unsigned int msg[3];

	msg[0] = LPM3_HISEE_MNTN;
	msg[1] = HISEE_TEST_RECORD;
	msg[2] = data;

	pr_err("%s:msg[1]:%x,msg[2]:%x\n", __func__, msg[1], msg[2]);
	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)&msg, 3);
	if (ret != 0)
		pr_err("%s:RPROC_ASYNC_SEND failed! return 0x%x, msg:(%x)\n",
			__func__, ret, msg[0]);

	return ret;
}
#endif

/********************************************************************
description:  translate the irq number to the exception type defined by kernel,
		so kernel can know what exception it is.
input: irq_no, irq number id.
output: NA
return: exception type
********************************************************************/
static unsigned int translate_exc_type(u32 irq_no)
{
	unsigned long i;
	u32 module_id = MODID_HISEE_EXC_UNKNOWN;

	for (i = 0; i < sizeof(hisee_exc_trans) /
		sizeof(hisee_exc_trans_s); i++)
		if (irq_no == hisee_exc_trans[i].irq_value) {
			module_id = hisee_exc_trans[i].module_value;
			break;
		}

	return module_id;
}


/********************************************************************
Description:	kenrel send msg to ATF
input:	NA
output:	NA
return:	NA
********************************************************************/
/*lint -e715*/
noinline int atfd_hisi_service_hisee_mntn_smc(u64 function_id,
	u64 arg0,
	u64 arg1,
	u64 arg2)
{
	return (int)function_id;
}
/*lint +e715*/
/********************************************************************
Description:	trigger the hisee exception by its type
input:	NA
output:	NA
return:	NA
********************************************************************/
/*lint -e715*/
static void __hisee_exception_func(struct work_struct *work)
{
	pr_err("fi[0x%x] fv[0x%x] ss[0x%x] sc[0x%x]\n",
			g_msg.data[2], g_msg.data[3], g_msg.data[4],
			g_msg.data[5]);
	memset(&g_msg, 0, sizeof(struct ipc_msg));
	/* trigger the hisee exception by its type */
	rdr_system_error(hisee_exception_modid, 0, 0);
}
/*lint +e715*/
/********************************************************************
Description:	receive ipc message
input:	msg£ºipc message
output:	NA
return:	NA
********************************************************************/
/*lint -e715*/
int rdr_hisee_msg_handler(struct notifier_block *nb,
	unsigned long action,
	void *msg)
{
	g_msg = *(struct ipc_msg*)msg;

	if (g_msg.data[0] == HISEE_EXCEPTION) {
		pr_info("%s:exception msg : %x\n", __func__, g_msg.data[0]);
		hisee_exception_modid = g_msg.data[1] + MODID_HISEE_START;
		if (hisee_exception_modid > MODID_HISEE_EXC_UNKNOWN) {
			hisee_exception_modid = MODID_HISEE_EXC_UNKNOWN;
		}
		schedule_work(&hisee_exception_work);
	} else if (g_msg.data[0] == HISEE_IRQ) {
		pr_info("%s:exception msg : %x\n", __func__, g_msg.data[0]);
		hisee_exception_modid = translate_exc_type(g_msg.data[1]);
		if (!hisee_exception_modid) {
			pr_err("%s:exception module id:%x\n",
				__func__, hisee_exception_modid);
			return -1;
		}
		schedule_work(&hisee_exception_work);
	}

	return 0;
}
/*lint +e715*/

/********************************************************************
Description: notify lpm3 reset hisee
input:	modid:module id
		etype:exception type
		coreid:core id
output:	NA
return:	NA
********************************************************************/
void rdr_hisee_reset(u32 modid, u32 etype, u64 coreid)
{
	int ret;
	unsigned int msg[2];

	msg[0] = LPM3_HISEE_MNTN;
	msg[1] = HISEE_RESET;

	pr_err(" ====================================\n");
	pr_err(" modid:          [0x%x]\n", modid);
	pr_err(" coreid:         [0x%llx]\n", coreid);
	pr_err(" exce tpye:      [0x%x]\n", etype);
	pr_err(" ====================================\n");

	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17,
		(mbox_msg_t *)&msg, 2);
	if (ret != 0) {
		pr_err("%s:RPROC_ASYNC_SEND failed! return 0x%x, msg:(%x)\n",
			__func__, ret, msg[0]);
	}

}
/********************************************************************
Description: save hisee log to file system
input:	modid: module id
		etype:exception type
		coreid: core id
		pathname: log path
		pfn_cb: callback function
output:	NA
return:	NA
********************************************************************/
void rdr_hisee_dump(u32 modid,
	u32 etype,
	u64 coreid,
	char *pathname,
	pfn_cb_dump_done pfn_cb)
{
	char path[PATH_MAXLEN] = {0};
	int ret;
	hlog_header *hisee_log_head = (hlog_header *)hisee_log_addr;

	pr_err(" ====================================\n");
	pr_err(" modid:          [0x%x]\n",   modid);
	pr_err(" coreid:         [0x%llx]\n", coreid);
	pr_err(" exce tpye:      [0x%x]\n",   etype);
	pr_err(" path name:      [%s]\n",     pathname);
	pr_err(" ====================================\n");

	atfd_hisi_service_hisee_mntn_smc((u64)HISEE_MNTN_ID,
		(u64)HISEE_MNTN_GET_LOG, (u64)0x0, (u64)0x0);
	snprintf(path, (unsigned long)PATH_MAXLEN, "%s/%s", pathname, HISEE_LOG_FLIENAME);
	if (hisee_log_head->magic != HISEE_LOG_MAGIC)
		pr_err("%s:hisee log magic %x\n", __func__,
			hisee_log_head->magic);

	/* save hisee log to data/hisi_logs/time/hisee_log */
	/*lint -e124*/
	ret = mntn_filesys_write_log(path,
			(void *)(hisee_log_addr + sizeof(hlog_header)),
			hisee_log_head->offset,
			HISEE_FILE_PERMISSION);
	/*lint +e124*/
	if (0 == ret)
		pr_err("%s:hisee log save fail\n", __func__);
	hisee_log_head->offset = 0;
	/* save to 8M */
	memcpy(hisee_mntn_addr, hisee_log_addr, (unsigned long)hisee_info.log_len);

	if (pfn_cb)
		pfn_cb(modid, coreid);

}

/********************************************************************
Description:	register hisee dump and reset function
input:	NA
output:	NA
return:	NA
********************************************************************/
static int hisee_register_core(void)
{
	int ret;
	struct rdr_module_ops_pub s_soc_ops;

	s_soc_ops.ops_dump = rdr_hisee_dump;
	s_soc_ops.ops_reset = rdr_hisee_reset;
	/* register hisee core dump and reset function */
	ret = rdr_register_module_ops((u64)RDR_HISEE, &s_soc_ops, &hisee_info);
	if (ret < 0) {
		pr_err("%s:hisee core register fail, ret = [%d]\n",
			__func__, ret);
		return ret;
	};
	return 0;
}

/********************************************************************
Description:	close dump mask if hisee mntn nv is off
input:	NONE
output:
return:	NA
********************************************************************/
static void hisee_close_dump_mask(void)
{
	unsigned long i;

	if (0 == check_himntn(HIMNTN_HISEE)) {
		pr_err("hisee mntn nv is off, so set dump mask with 0\n");
		for (i = 0; i < sizeof(hisee_excetption_info) /
			sizeof(struct rdr_exception_info_s); i++) {
			hisee_excetption_info[i].e_notify_core_mask = 0;
		}
	}
}
/********************************************************************
Description:	register hisee exception
input:	hisee_einfo: hisee exception list
output:
return:	NA
********************************************************************/
static void hisee_register_exception(void)
{
	u32 ret;
	unsigned long i;

	/*we should close dump hisee data if hisee mntn nv is off(for final release version)*/
	hisee_close_dump_mask();
	for (i = 0; i < sizeof(hisee_excetption_info) /
		sizeof(struct rdr_exception_info_s); i++) {
		/* error return 0, ok return modid */
		ret = rdr_register_exception(&hisee_excetption_info[i]);
		if (!ret)
			pr_err("register hisee exception fail hisee_einfo[%lu]\n", i);
	}
}
/********************************************************************
Description: Check whether hisee chip is valid
input:	NA
output:	NA
return:	false:invalid
		true:valid
********************************************************************/
int is_hisee_efuse_valid(void)
{
	int ret;
	unsigned int hisee_value[2] = {0};

	ret = get_efuse_hisee_value((unsigned char *)hisee_value, EFUSE_LENGTH, EFUSE_READ_TIMEOUT);
	if (ret) {
		pr_err("%s() get_efuse_hisee_value failed,ret=%d\n", __func__, ret);
		return false;
	}
	if (!((hisee_value[1] >> HISEE_MNTN_OFFSET_EFUSE) & 1))
		return false;

	return true;
}


/********************************************************************
Description:	hisee mntn initialization
input:	NA
output:	NA
return:	NA
********************************************************************/
static int hisee_mntn_probe(struct platform_device *pdev)
{
	int ret;
	unsigned int msg[2];

	msg[0] = LPM3_HISEE_MNTN;
	msg[1] = HISEE_MNTN_OFF;

	if (false == is_hisee_efuse_valid()) {
		ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17,
			(mbox_msg_t *)&msg, 2);
		if (ret != 0)
			pr_err("%s:RPROC_ASYNC_SEND failed! return 0x%x, msg:(%x)\n",
				__func__, ret, msg[0]);
		pr_err("%s:hisee mntn disable\n", __func__);
		return -EACCES;
	}
	ret = of_reserved_mem_device_init(&pdev->dev);
	if (0 != ret) {
		pr_err("%s: init failed, ret.%d\n", __func__, ret);
		return ret;
	}
	/* register hisee exception */
	hisee_register_exception();

	/* register hisee dump and reset function */
	ret = hisee_register_core();
	if (ret < 0)
		return ret;

	hisee_mntn_addr = hisi_bbox_map(
		(phys_addr_t)hisee_info.log_addr, (size_t)hisee_info.log_len);
	if (NULL == hisee_mntn_addr) {
		pr_err("%s:memory map fail\n", __func__);
		return -EFAULT;
	}
	/*lint -e747 -esym(747,*)*/
	hisee_log_addr = dma_alloc_coherent(&pdev->dev,
		(size_t)hisee_info.log_len, &hisee_log_phy, GFP_KERNEL);
	/*lint -e747 +esym(747,*)*/
	if (!hisee_log_addr) {
		pr_err("%s:memory alloc fail\n", __func__);
		return -ENOMEM;
	}

	/* initialization mailbox */
	hisee_ipc_block.next = NULL;
	hisee_ipc_block.notifier_call = rdr_hisee_msg_handler;
	ret = RPROC_MONITOR_REGISTER(HISI_RPROC_LPM3_MBX0, &hisee_ipc_block);
	if (ret != 0) {
		pr_err("%s:RPROC_MONITOR_REGISTER failed\n", __func__);
		return ret;
	}
	pr_info("%s : v:%pK, phy : %llx\n", __func__,
		hisee_log_addr, (u64)hisee_log_phy);
	atfd_hisi_service_hisee_mntn_smc((u64)HISEE_MNTN_ID,
		(u64)HISEE_MNTN_INIT, hisee_log_phy, (u64)hisee_info.log_len);
	pr_err("exit %s\n", __func__);
	return 0;
}

static int hisee_mntn_remove(struct platform_device *pdev)
{
	/*lint -e747 -esym(747,*)*/
	dma_free_coherent(&pdev->dev, (size_t)hisee_info.log_len,
		&hisee_log_phy, GFP_KERNEL);
	/*lint -e747 +esym(747,*)*/
	return 0;
}
/*lint -e785*/
static const struct of_device_id hisee_mntn_match[] = {
	{.compatible = "hisee-mntn"},
	{}
};

static struct platform_driver hisee_mntn_driver = {
	.probe = hisee_mntn_probe,
	.remove = hisee_mntn_remove,
	.driver = {
		   .name = "hisee-mntn",
		   .of_match_table = hisee_mntn_match,
	},
};
/*lint +e785*/

static int __init hisee_mntn_init(void)
{
	/*lint -e64 -esym(64,*)*/
	return platform_driver_register(&hisee_mntn_driver);
	/*lint -e64 +esym(64,*)*/
}

static void __exit hisee_mntn_exit(void)
{
	platform_driver_unregister(&hisee_mntn_driver);
}
/*lint -e528 -esym(528,*)*/
module_init(hisee_mntn_init);
module_exit(hisee_mntn_exit);
/*lint -e528 +esym(528,*)*/
/*lint -e753 -esym(753,*)*/
MODULE_LICENSE("GPL");
/*lint -e753 +esym(753,*)*/

