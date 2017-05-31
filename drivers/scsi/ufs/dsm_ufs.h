#ifndef LINUX_DSM_UFS_H
#define LINUX_DSM_UFS_H

#include <linux/time.h>
#include <dsm/dsm_pub.h>
#include "ufs.h"
#include "ufshcd.h"

#define UFS_DSM_BUFFER_SIZE    2048
#define UFS_MSG_MAX_SIZE        256

#define	DSM_UFS_FASTBOOT_PWMODE_ERR	928008000
#define	DSM_UFS_FASTBOOT_RW_ERR		928008001
#define	DSM_UFS_SYSBUS_ERR		928008002
#define	DSM_UFS_UIC_TRANS_ERR		928008003
#define	DSM_UFS_UIC_CMD_ERR		928008004
#define	DSM_UFS_CONTROLLER_ERR		928008005
#define	DSM_UFS_DEV_ERR			928008006
#define	DSM_UFS_TIMEOUT_ERR		928008007
#define	DSM_UFS_UTP_ERR			928008008
#define	DSM_UFS_SCSI_CMD_ERR		928008009
#define	DSM_UFS_VOLT_GPIO_ERR		928008010
#define	DSM_UFS_LINKUP_ERR		928008011
#define	DSM_UFS_INLINE_CRYPTO_ERR		928008012

#define FASTBOOTDMD_PWR_ERR  BIT(4) /*Power mode change err ,set bit4*/
#define FASTBOOTDMD_RW_ERR  BIT(15) /*read and write err, set bit15*/
#define TEN_BILLION_BITS 10000000000
struct ufs_dsm_log {
	char dsm_log[UFS_DSM_BUFFER_SIZE];
	spinlock_t lock; /*mutex*/
};
extern struct dsm_client *ufs_dclient;
extern unsigned int ufs_dsm_real_upload_size;

struct ufs_uic_err {
	u32 pal_err;
	u32 cdl_err;
	u32 cnl_err;
	u32 ctl_err;
	u32 dme_err;
};

struct ufs_reg_dump {
	u32 cap;
	u32 ver;
	u32 hcpid;
	u32 hcmid;
	u32 ahit;
	u32 is;
	u32 ie;
	u32 hcs;
	u32 hce;
	u32 uecpa;
	u32 uecdl;
	u32 uecn;
	u32 uect;
	u32 uedme;
	/*UTP Transfer Request*/
	u32 utriac;
	u32 utrlba;
	u32 utrlbau;
	u32 utrldbr;
	u32 utrlclr;
	u32 utrlrsr;
	/*UTP Task Managerment Request*/
	u32 utmrlba;
	u32 utmrlbau;
	u32 utmrldbr;
	u32 utmrlclr;
	u32 utmrlrsr;
	/*uic command*/
	u32 uic_cmd;
	u32 uic_arg1;
	u32 uic_arg2;
	u32 uic_arg3;
};

struct ufs_dsm_adaptor {
	unsigned long err_type;
#define	UFS_FASTBOOT_PWMODE_ERR		0
#define	UFS_FASTBOOT_RW_ERR		1
#define	UFS_SYSBUS_ERR			2
#define	UFS_UIC_TRANS_ERR		3
#define	UFS_UIC_CMD_ERR			4
#define	UFS_CONTROLLER_ERR		5
#define	UFS_DEV_ERR			6
#define	UFS_TIMEOUT_ERR			7
#define	UFS_UTP_TRANS_ERR		8
#define	UFS_SCSI_CMD_ERR		9
#define	UFS_VOLT_GPIO_ERR		10
#define	UFS_LINKUP_ERR		11
#define	UFS_INLINE_CRYPTO_ERR	12
	struct ufs_reg_dump dump;
	/*for UIC Transfer Error*/
	unsigned long uic_disable;
	u32 uic_uecpa;
	u32 uic_uecdl;
	u32 uic_uecn;
	u32 uic_uect;
	u32 uic_uedme;
	/*for UIC Command Error*/
	u32 uic_info[4];
	/*for time out error*/
	int timeout_slot_id;
	unsigned long outstanding_reqs;
	u32 tr_doorbell;
	unsigned char timeout_scmd[MAX_CDB_SIZE];
	int scsi_status;
	int ocs;
	char sense_buffer[SCSI_SENSE_BUFFERSIZE];
	uint16_t manufacturer_id;
	unsigned long ice_outstanding;
	u32 ice_doorbell;
};
extern struct ufs_dsm_log g_ufs_dsm_log;
extern struct ufs_uic_err uic_err;

#ifdef CONFIG_HUAWEI_UFS_DSM
int dsm_ufs_update_upiu_info(struct ufs_hba *hba,
				int tag, int err_code);
int dsm_ufs_update_scsi_info(struct ufshcd_lrb *lrbp,
				int scsi_status, int err_code);
int dsm_ufs_update_ocs_info(struct ufs_hba *hba,
				int err_code, int ocs);
int dsm_ufs_update_error_info(struct ufs_hba *hba, int code);
int dsm_ufs_update_uic_info(struct ufs_hba *hba, int err_code);
int dsm_ufs_update_fastboot_info(struct ufs_hba *hba);
int dsm_ufs_get_log(struct ufs_hba *hba, unsigned long code, char *err_msg);
void dsm_ufs_clear_err_type(void);
void dsm_ufs_handle_work(struct work_struct *work);
int dsm_ufs_enabled(void);
void dsm_ufs_enable_uic_err(struct ufs_hba *hba);
int dsm_ufs_disable_uic_err(void);
int dsm_ufs_if_uic_err_disable(void);
unsigned long dsm_ufs_if_err(void);
void dsm_ufs_init(struct ufs_hba *hba);
int dsm_ufs_updata_ice_info(struct ufs_hba *hba);
void dsm_ufs_enable_volt_irq(struct ufs_hba *hba);
void dsm_ufs_disable_volt_irq(struct ufs_hba *hba);

#define DSM_UFS_LOG(hba, no, fmt, a...)\
	do {\
		char msg[UFS_MSG_MAX_SIZE];\
		snprintf(msg, UFS_MSG_MAX_SIZE-1, fmt, ## a);\
		spin_lock(&g_ufs_dsm_log.lock);\
		if (dsm_ufs_get_log(hba, (no), (msg))) {\
			if (!dsm_client_ocuppy(ufs_dclient)) {\
				dsm_client_copy(ufs_dclient, \
						g_ufs_dsm_log.dsm_log, \
						ufs_dsm_real_upload_size+1);\
				dsm_client_notify(ufs_dclient, (no));\
			} \
		} \
		spin_unlock(&g_ufs_dsm_log.lock);\
	} while (0)

#else
int dsm_ufs_update_upiu_info(struct ufs_hba *hba,
				int tag, int err_code) { return 0; }
int dsm_ufs_update_scsi_info(struct ufshcd_lrb *lrbp,
				int scsi_status, int err_code) {return 0; }
int dsm_ufs_update_ocs_info(struct ufs_hba *hba,
				int err_code, int ocs) {return 0; }
int dsm_ufs_update_error_info(struct ufs_hba *hba, int code) {return 0; }
int dsm_ufs_update_uic_info(struct ufs_hba *hba, int err_code) {return 0; }
int dsm_ufs_update_fastboot_info(struct ufs_hba *hba) {return 0; }
int dsm_ufs_get_log(struct ufs_hba *hba, unsigned long code, char *err_msg) {return 0; }
void dsm_ufs_handle_work(struct work_struct *work) {}
int dsm_ufs_enabled(void) { return 0; }
void dsm_ufs_enable_uic_err(struct ufs_hba *hba){return 0; };
int dsm_ufs_disable_uic_err(void){return 0; };
int dsm_ufs_if_uic_err_disable(void){return 0; };
void dsm_ufs_init(struct ufs_hba *hba) {}
unsigned long dsm_ufs_if_err(void){return 0;}
int dsm_ufs_updata_ice_info(struct ufs_hba *hba){return 0;}
void dsm_ufs_enable_volt_irq(struct ufs_hba *hba) {return;}
void dsm_ufs_disable_volt_irq(struct ufs_hba *hba) {return;}
#define DSM_UFS_LOG(hba, no, fmt, a...)
#endif
#endif
