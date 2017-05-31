#ifndef __HISEE_MNTN_H__
#define __HISEE_MNTN_H__

#include <linux/hisi/ipc_msg.h>

/* used for translation from original value to exception module id */
typedef struct {
	u32		irq_value;
	u32		module_value;
} hisee_exc_trans_s;

typedef struct {
	unsigned int magic;
	uint64_t addr;
	uint64_t size;
	unsigned int offset;
} hlog_header;

typedef enum {
	MODID_HISEE_START = (unsigned int)HISI_BB_MOD_HISEE_START,
	MODID_HISEE_EXC_SENSOR_CTRL,
	MODID_HISEE_EXC_SIC,
	MODID_HISEE_EXC_MED_ROM,
	MODID_HISEE_EXC_MED_RAM,
	MODID_HISEE_EXC_OTPC,
	MODID_HISEE_EXC_HARD,
	MODID_HISEE_EXC_IPC_MAILBOX,
	MODID_HISEE_EXC_MPU,
	MODID_HISEE_EXC_BUS,
	MODID_HISEE_EXC_TIMER,
	MODID_HISEE_EXC_SEC_EXTERN,
	MODID_HISEE_EXC_WDG,
	MODID_HISEE_EXC_SYSALARM,

	MODID_HISEE_EXC_SECENG_TRNG,
	MODID_HISEE_EXC_SECENG_TRIM,
	MODID_HISEE_EXC_SECENG_SCE,
	MODID_HISEE_EXC_SECENG_RSA,
	MODID_HISEE_EXC_SECENG_SM2,
	MODID_HISEE_EXC_SECENG_KM,
	MODID_HISEE_EXC_SECENG_SCRAMBLING,
	MODID_HISEE_EXC_BOTTOM,
	/* Please don't remove this comment,
	These have to leave for E_HISEE_EXC_TYPE defined in Lpm3 module code*/

	MODID_HISEE_EXC_ALARM0 = 0x87000100,
	MODID_HISEE_EXC_ALARM1,
	MODID_HISEE_EXC_AS2AP_IRQ,
	MODID_HISEE_EXC_DS2AP_IRQ,
	MODID_HISEE_EXC_SENC2AP_IRQ,
	MODID_HISEE_EXC_LOCKUP,
	MODID_HISEE_EXC_EH2H_SLV,
	MODID_HISEE_EXC_TSENSOR1,

	/*Please your type above !!!*/
	MODID_HISEE_EXC_UNKNOWN,
	MODID_HISEE_EXC_END = HISI_BB_MOD_HISEE_END
} hisee_module_id;

typedef enum {
	HISEE_TYPE_START,
	/* lpm3 -> kernel hisee mntn driver */
	HISEE_EXCEPTION_TYPE,
	HISEE_IRQ_TYPE,
	/* kernel hisee mntn driver -> lpm3 */
	HISEE_MNTN_TYPE,
	HISEE_TYPE_END
} hisee_type;

typedef enum {
	HISEE_STATUS_START,
	HISEE_MNTN_ON,
	HISEE_MNTN_OFF,
	HISEE_RESET,
	HISEE_TEST_IRQ,
	HISEE_TEST_EXCEPTION,
	HISEE_TEST_RECORD,
	HISEE_STATUS_END
} hisee_status;

typedef enum {
	HISEE_MNTN_INIT = 1,
	HISEE_MNTN_GET_LOG
} hisee_mntn_smc_cmd;

#define HISEE_MNTN_ID             (0xc500cc00u)

#define PATH_MAXLEN         128
#define HISEE_LOG_MAGIC 0x20160628
#define HISEE_LOG_FLIENAME "hisee_log"
#define HISEE_FILE_PERMISSION 0660
#define HISEE_MNTN_OFFSET_EFUSE 14
#define EFUSE_LENGTH 8
#define EFUSE_READ_TIMEOUT 1000

#define LPM3_HISEE_MNTN IPC_CMD(OBJ_AP, OBJ_INSE, CMD_INQUIRY, HISEE_MNTN_TYPE)

#define HISEE_EXCEPTION IPC_CMD(OBJ_LPM3, OBJ_INSE, CMD_NOTIFY, HISEE_EXCEPTION_TYPE)
#define HISEE_IRQ IPC_CMD(OBJ_LPM3, OBJ_INSE, CMD_NOTIFY, HISEE_IRQ_TYPE)

extern int get_efuse_hisee_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);

#endif
