#include <dsm/dsm_pub.h>
#include <linux/async.h>
#include <linux/of_gpio.h>
#include "ufs.h"
#include "ufshcd.h"
#include "unipro.h"
#include "dsm_ufs.h"

/*lint -e747 -e713 -e715 -e732 -e835*/
struct ufs_dsm_log  g_ufs_dsm_log;
static struct ufs_dsm_adaptor g_ufs_dsm_adaptor;
struct dsm_client *ufs_dclient;
unsigned int ufs_dsm_real_upload_size;
static int dsm_ufs_enable;
struct ufs_uic_err uic_err;

struct dsm_dev dsm_ufs = {
	.name = "dsm_ufs",
	.buff_size = UFS_DSM_BUFFER_SIZE,
};
EXPORT_SYMBOL(ufs_dclient);

unsigned long dsm_ufs_if_err(void)
{
	return g_ufs_dsm_adaptor.err_type;
}

int dsm_ufs_update_upiu_info(struct ufs_hba *hba, int tag, int err_code)
{
	struct scsi_cmnd *scmd;
	int i;

	if (!dsm_ufs_enable)
		return -1;
	if (test_and_set_bit_lock(UFS_TIMEOUT_ERR, &g_ufs_dsm_adaptor.err_type))
		return -1;
	if ((tag != -1) && (hba->lrb[tag].cmd)) {
	    scmd = hba->lrb[tag].cmd;
	    for (i = 0; i < COMMAND_SIZE(scmd->cmnd[0]); i++)
		g_ufs_dsm_adaptor.timeout_scmd[i] = scmd->cmnd[i];
	} else {
	    for (i = 0; i < MAX_CDB_SIZE; i++)
		g_ufs_dsm_adaptor.timeout_scmd[i] = 0;
	}
	g_ufs_dsm_adaptor.timeout_slot_id = tag;
	g_ufs_dsm_adaptor.tr_doorbell = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	g_ufs_dsm_adaptor.outstanding_reqs = hba->outstanding_reqs;

	return 0;

}
static u32 crypto_conf_index[32];
int dsm_ufs_updata_ice_info(struct ufs_hba *hba)
{
	unsigned int i;
	if(!dsm_ufs_enable)
		return -1;
	if(test_and_set_bit_lock(UFS_INLINE_CRYPTO_ERR, &g_ufs_dsm_adaptor.err_type))
		return -1;
	g_ufs_dsm_adaptor.ice_outstanding = hba->outstanding_reqs;
	g_ufs_dsm_adaptor.ice_doorbell = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	for(i = 0; i < 32; i++)
	{
		if(!((g_ufs_dsm_adaptor.ice_doorbell >> i)&0x1))
		{
			continue;
		}
		crypto_conf_index[i] = (hba->lrb[i].utr_descriptor_ptr)->header.dword_0;
	}
	return 0;
}
int dsm_ufs_update_scsi_info(struct ufshcd_lrb *lrbp, int scsi_status, int err_code)
{
	struct scsi_cmnd *scmd;
	int i;

	if (!dsm_ufs_enable)
		return -1;
	if (test_and_set_bit_lock(UFS_SCSI_CMD_ERR, &g_ufs_dsm_adaptor.err_type))
		return -1;
	if (lrbp->cmd)
	    scmd = lrbp->cmd;
	else
	    return -1;
	g_ufs_dsm_adaptor.scsi_status = scsi_status;
	for (i = 0; i < COMMAND_SIZE(scmd->cmnd[0]); i++)
		g_ufs_dsm_adaptor.timeout_scmd[i] = scmd->cmnd[i];

	for (i = 0; i < SCSI_SENSE_BUFFERSIZE; i++)
		g_ufs_dsm_adaptor.sense_buffer[i] = lrbp->sense_buffer[i];

	return 0;
}

int dsm_ufs_update_ocs_info(struct ufs_hba *hba, int err_code, int ocs)
{
	if (!dsm_ufs_enable)
		return -1;
	if (test_and_set_bit_lock(UFS_UTP_TRANS_ERR, &g_ufs_dsm_adaptor.err_type))
		return -1;
	g_ufs_dsm_adaptor.ocs = ocs;
	return 0;
}

int dsm_ufs_update_fastboot_info(struct ufs_hba *hba)
{
	char *pstr, *dstr;
	char tmp[64];
	int err;
	unsigned int err_code;

	if (!dsm_ufs_enable)
		return -1;

	pstr = strstr(saved_command_line, "fastbootdmd=");
	if (!pstr) {
		pr_err("No fastboot dmd info\n");
		return -EINVAL;
	}
	pstr += strlen("fastbootdmd=");
	dstr = strstr(pstr, " ");
	if (!dstr) {
		pr_err("No find the fastboot dmd end\n");
		return -EINVAL;
	}

	memcpy(tmp, pstr, (unsigned long)(dstr - pstr));
	tmp[dstr - pstr] = '\0';
	err = kstrtol(tmp, 10, (long *)&err_code);
	if (err) {
		pr_info("Dsm_fastboot_dmd: kstrtol failed, err: %d\n",
			err);
		return err;
	}
	if (err_code) {
		if (err_code & FASTBOOTDMD_PWR_ERR) {
			if (test_and_set_bit_lock(UFS_FASTBOOT_PWMODE_ERR,
				&g_ufs_dsm_adaptor.err_type))
				return -1;
		}
		if (err_code & FASTBOOTDMD_RW_ERR) {
			if (test_and_set_bit_lock(UFS_FASTBOOT_RW_ERR,
				&g_ufs_dsm_adaptor.err_type))
				return -1;
		}
	} else
		return -EINVAL;

	return 0;
}

static void dsm_ufs_fastboot_async(void *data, async_cookie_t cookie)
{
	int ret;
	struct ufs_hba *hba = (struct ufs_hba *)data;

	ret = dsm_ufs_update_fastboot_info(hba);
	if (!ret) {
		pr_info("Ufs get fastboot dmd err info\n");
		if (dsm_ufs_enabled())
			schedule_work(&hba->dsm_work);
	}
}

void dsm_ufs_enable_uic_err(struct ufs_hba *hba)
{
	unsigned long flags;

	clear_bit_unlock( 0x0, &(g_ufs_dsm_adaptor.uic_disable));
	spin_lock_irqsave(hba->host->host_lock, flags);/*lint !e550*/
	ufshcd_enable_intr(hba, UIC_ERROR);
	spin_unlock_irqrestore(hba->host->host_lock, flags);/*lint !e550*/
	return;
}

int dsm_ufs_disable_uic_err(void)
{
	return (test_and_set_bit_lock( 0x0, &(g_ufs_dsm_adaptor.uic_disable)));
}

int dsm_ufs_if_uic_err_disable(void)
{
	return (test_bit( 0x0, &(g_ufs_dsm_adaptor.uic_disable)));
}

int dsm_ufs_update_uic_info(struct ufs_hba *hba, int err_code)
{
	if (!dsm_ufs_enable)
	    return -1;
	if (dsm_ufs_if_uic_err_disable())
		return 0;
	if (test_and_set_bit_lock(UFS_UIC_TRANS_ERR, &g_ufs_dsm_adaptor.err_type))
	    return -1;
	g_ufs_dsm_adaptor.uic_uecpa = uic_err.pal_err;
	g_ufs_dsm_adaptor.uic_uecdl = uic_err.cdl_err;
	g_ufs_dsm_adaptor.uic_uecn = uic_err.cnl_err;
	g_ufs_dsm_adaptor.uic_uect = uic_err.ctl_err;
	g_ufs_dsm_adaptor.uic_uedme = uic_err.dme_err;
	return 0;
}

int dsm_ufs_update_error_info(struct ufs_hba *hba, int code)
{
	struct ufs_reg_dump *ufs_dump;

	if (!dsm_ufs_enable)
		return -1;
	ufs_dump = &(g_ufs_dsm_adaptor.dump);
	switch (code) {
	case DSM_UFS_VOLT_GPIO_ERR:
		(void)test_and_set_bit_lock(UFS_VOLT_GPIO_ERR, &g_ufs_dsm_adaptor.err_type);
		break;
	case DSM_UFS_LINKUP_ERR:
		(void)test_and_set_bit_lock(UFS_LINKUP_ERR, &g_ufs_dsm_adaptor.err_type);
		break;
	case DSM_UFS_UIC_CMD_ERR:
		if (test_and_set_bit_lock(UFS_UIC_CMD_ERR, &g_ufs_dsm_adaptor.err_type))
			break;
		g_ufs_dsm_adaptor.uic_info[0] = ufshcd_readl(hba, REG_UIC_COMMAND);
		g_ufs_dsm_adaptor.uic_info[1] = ufshcd_readl(hba, REG_UIC_COMMAND_ARG_1);
		g_ufs_dsm_adaptor.uic_info[2] = ufshcd_readl(hba, REG_UIC_COMMAND_ARG_2);
		g_ufs_dsm_adaptor.uic_info[3] = ufshcd_readl(hba, REG_UIC_COMMAND_ARG_3);
		break;
	case DSM_UFS_CONTROLLER_ERR:
	case DSM_UFS_DEV_ERR:
		if (code == DSM_UFS_CONTROLLER_ERR) {
			if (test_and_set_bit_lock(UFS_CONTROLLER_ERR, &g_ufs_dsm_adaptor.err_type))
				break;
		} else {
			if (test_and_set_bit_lock(UFS_DEV_ERR, &g_ufs_dsm_adaptor.err_type))
				break;
		}
		ufs_dump->cap = ufshcd_readl(hba, REG_CONTROLLER_CAPABILITIES);
		ufs_dump->ver = ufshcd_readl(hba, REG_UFS_VERSION);
		ufs_dump->hcpid = ufshcd_readl(hba, REG_CONTROLLER_DEV_ID);
		ufs_dump->hcmid = ufshcd_readl(hba, REG_CONTROLLER_PROD_ID);
		ufs_dump->ahit = ufshcd_readl(hba, REG_CONTROLLER_AHIT);
		ufs_dump->is = ufshcd_readl(hba, REG_INTERRUPT_STATUS);
		ufs_dump->ie = ufshcd_readl(hba, REG_INTERRUPT_ENABLE);
		ufs_dump->hcs = ufshcd_readl(hba, REG_CONTROLLER_STATUS);
		ufs_dump->hce = ufshcd_readl(hba, REG_CONTROLLER_ENABLE);
#ifdef CONFIG_SCSI_UFS_KIRIN_LINERESET_CHECK
		ufs_dump->uecpa = hba->reg_uecpa;
#else
		ufs_dump->uecpa = ufshcd_readl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER);
#endif
		ufs_dump->uecdl = ufshcd_readl(hba, REG_UIC_ERROR_CODE_DATA_LINK_LAYER);
		ufs_dump->uecn = ufshcd_readl(hba, REG_UIC_ERROR_CODE_NETWORK_LAYER);
		ufs_dump->uect = ufshcd_readl(hba, REG_UIC_ERROR_CODE_TRANSPORT_LAYER);
		ufs_dump->uedme = ufshcd_readl(hba, REG_UIC_ERROR_CODE_DME);
		ufs_dump->utriac = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL);
		ufs_dump->utrlba = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_BASE_L);
		ufs_dump->utrlbau = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_BASE_H);
		ufs_dump->utrldbr = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
		ufs_dump->utrlclr = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_CLEAR);
		ufs_dump->utrlrsr = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_RUN_STOP);
		ufs_dump->utmrlba = ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_BASE_L);
		ufs_dump->utmrlbau = ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_BASE_H);
		ufs_dump->utmrldbr = ufshcd_readl(hba, REG_UTP_TASK_REQ_DOOR_BELL);
		ufs_dump->utmrlclr = ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_CLEAR);
		ufs_dump->utmrlrsr = ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_RUN_STOP);
		ufs_dump->uic_cmd = ufshcd_readl(hba, REG_UIC_COMMAND);
		ufs_dump->uic_arg1 = ufshcd_readl(hba, REG_UIC_COMMAND_ARG_1);
		ufs_dump->uic_arg2 = ufshcd_readl(hba, REG_UIC_COMMAND_ARG_2);
		ufs_dump->uic_arg3 = ufshcd_readl(hba, REG_UIC_COMMAND_ARG_3);
		break;
	default:
		return 0;
	}
	return 0;
}

/*put error message into buffer*/
int dsm_ufs_get_log(struct ufs_hba *hba, unsigned long code, char *err_msg)
{
	int i, ret = 0;
	int buff_size = sizeof(g_ufs_dsm_log.dsm_log);
	char *dsm_log_buff = g_ufs_dsm_log.dsm_log;
	struct ufs_reg_dump *ufs_dump;
	ufs_dump = &(g_ufs_dsm_adaptor.dump);

	if (!dsm_ufs_enable)
		return 0;

	pr_err("dj enter dsm_ufs_get_log\n");
	g_ufs_dsm_adaptor.manufacturer_id = hba->manufacturer_id;
	memset(g_ufs_dsm_log.dsm_log, 0, buff_size);/**/
	ret = snprintf(dsm_log_buff, buff_size, "manufacturer_id:%04x Error Num:%lu, %s\n",
					g_ufs_dsm_adaptor.manufacturer_id, code, err_msg);
	dsm_log_buff += ret;
	buff_size -= ret;
	/*print vendor info*/
	switch (code) {
	case DSM_UFS_FASTBOOT_PWMODE_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_FASTBOOT_PWMODE_ERR))) {
			pr_err("UFS DSM Error! Err Num:%lu err_type:%lu\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"Fastboot Power Mode Change Err\n");
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_FASTBOOT_RW_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_FASTBOOT_RW_ERR))) {
			pr_err("UFS DSM Error! Err Num:%lu err_type:%lu\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size, "Fastboot Read Write Err\n");
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_UIC_TRANS_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1<<UFS_UIC_TRANS_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %lu\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size, "UECPA:%08x,UECDL:%08x,UECN:%08x,UECT:%08x,UEDME:%08x\n",
			g_ufs_dsm_adaptor.uic_uecpa, g_ufs_dsm_adaptor.uic_uecdl, g_ufs_dsm_adaptor.uic_uecn,
			g_ufs_dsm_adaptor.uic_uect, g_ufs_dsm_adaptor.uic_uedme);
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_UIC_CMD_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1<<UFS_UIC_CMD_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %ld\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size, "UIC_CMD:%08x,ARG1:%08x,ARG2:%08x,ARG3:%08x\n",
				g_ufs_dsm_adaptor.uic_info[0], g_ufs_dsm_adaptor.uic_info[1],
				g_ufs_dsm_adaptor.uic_info[2], g_ufs_dsm_adaptor.uic_info[3]);
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_CONTROLLER_ERR:
	case DSM_UFS_DEV_ERR:
		if (code == DSM_UFS_CONTROLLER_ERR) {
			if (!(g_ufs_dsm_adaptor.err_type&((1 << UFS_CONTROLLER_ERR)|
				(1 << UFS_INLINE_CRYPTO_ERR)))) {
				pr_err("UFS DSM Error! Err Num: %lu, %ld\n",
					code, g_ufs_dsm_adaptor.err_type);
			    break;
		    }
			if(g_ufs_dsm_adaptor.err_type&(1 << UFS_INLINE_CRYPTO_ERR)) {
				ret = snprintf(dsm_log_buff, buff_size, "outstanding:0x%lx, doorbell: 0x%x\n",
					g_ufs_dsm_adaptor.ice_outstanding, g_ufs_dsm_adaptor.ice_doorbell);
				dsm_log_buff += ret;
				buff_size-= ret;
				for(i = 0; i < 32; i++) {
					if(crypto_conf_index[i]) {
						ret = snprintf(dsm_log_buff, buff_size, "UTP_DESC[%d]: 0x%x\n", i, crypto_conf_index[i]);
						dsm_log_buff += ret;
						buff_size-= ret;
						crypto_conf_index[i] = 0;
					}
				}
			}
			if(!(g_ufs_dsm_adaptor.err_type&(1 << UFS_CONTROLLER_ERR))) {
				break;
			}else {
				ret = snprintf(dsm_log_buff, buff_size, "And controller error\n");
				dsm_log_buff += ret;
				buff_size-= ret;
			}
		} else {
			if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_DEV_ERR))) {
				pr_err("UFS DSM Error! Err Num: %lu, %ld\n",
				code, g_ufs_dsm_adaptor.err_type);
			    break;
			}
		}
		/*get ufs reg dump*/
		ret = snprintf(dsm_log_buff, buff_size, "UFSDUMP:\n");
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "CAP:%08x,VER:%08x\n", ufs_dump->cap, ufs_dump->ver);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "HCPID:%08x,HCMID:%08x\n", ufs_dump->hcpid, ufs_dump->hcmid);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "AHIT:%08x,IS:%08x\n", ufs_dump->ahit, ufs_dump->is);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "IE:%08x,HCS:%08x\n", ufs_dump->ie, ufs_dump->hcs);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "HCE:%08x,UECPA:%08x\n", ufs_dump->hce, ufs_dump->uecpa);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UECDL:%08x,UECN:%08x\n", ufs_dump->uecdl, ufs_dump->uecn);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UECT:%08x,UEDME:%08x\n", ufs_dump->uect, ufs_dump->uedme);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UTRIAC:%08x,UTRLBA:%08x\n", ufs_dump->utriac, ufs_dump->utrlba);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UTRLBAU:%08x,UTRLDBR:%08x\n", ufs_dump->utrlbau, ufs_dump->utrldbr);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UTRLCLR:%08x,UTRLRSR:%08x\n", ufs_dump->utrlclr, ufs_dump->utrlrsr);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UTMRLBA:%08x,UTMRLBAU:%08x\n", ufs_dump->utmrlba, ufs_dump->utmrlbau);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UTMRLBR:%08x,UTMRLCLR:%08x\n", ufs_dump->utmrldbr, ufs_dump->utmrlclr);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size, "UTMRLRSR:%08x,UICCMD:%08x\n", ufs_dump->utmrlrsr, ufs_dump->uic_cmd);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size,
				"UICARG1:%08x,UICARG2:%08x\n",
				ufs_dump->uic_arg1, ufs_dump->uic_arg2);
		dsm_log_buff += ret;
		buff_size -= ret;
		ret = snprintf(dsm_log_buff, buff_size,
				"UICARG3:%08x\n",
				ufs_dump->uic_arg3);
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_UTP_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_UTP_TRANS_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %lu\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"UTP_OCS_ERR:%d\n", g_ufs_dsm_adaptor.ocs);
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_TIMEOUT_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_TIMEOUT_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %ld\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"UTP_tag:%02x,doorbell:%08x,outstandings:%lu scsi_cdb:\n",
				g_ufs_dsm_adaptor.timeout_slot_id,
				g_ufs_dsm_adaptor.tr_doorbell,
				g_ufs_dsm_adaptor.outstanding_reqs);
		dsm_log_buff += ret;
		buff_size -= ret;
		for (i = 0; i < COMMAND_SIZE(g_ufs_dsm_adaptor.timeout_scmd[0]); i++) {
			ret = snprintf(dsm_log_buff, buff_size, "%02x", g_ufs_dsm_adaptor.timeout_scmd[i]);/*[false alarm]: buff_size is nomal*/
			dsm_log_buff += ret;
			buff_size -= ret;
		}
		break;
	case DSM_UFS_SCSI_CMD_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_SCSI_CMD_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %ld\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"scsi_status:%x scsi_cdb:\n",
				g_ufs_dsm_adaptor.scsi_status);
		dsm_log_buff += ret;
		buff_size -= ret;
		for (i = 0; i < COMMAND_SIZE(g_ufs_dsm_adaptor.timeout_scmd[0]); i++) {
			ret = snprintf(dsm_log_buff, buff_size, "%02x", g_ufs_dsm_adaptor.timeout_scmd[i]);/*[false alarm]: buff_size is nomal*/
			dsm_log_buff += ret;
			buff_size -= ret;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"\t\tResponse_code:%02x, Sense_key:%02x, ASC:%02x, ASCQ:%x\n",
				g_ufs_dsm_adaptor.sense_buffer[0], g_ufs_dsm_adaptor.sense_buffer[2],
				g_ufs_dsm_adaptor.sense_buffer[12],g_ufs_dsm_adaptor.sense_buffer[13]);
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	case DSM_UFS_VOLT_GPIO_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_VOLT_GPIO_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %lu\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"UFS BUCK has got a falling down Volt\n");
		dsm_log_buff += ret;
		buff_size -= ret;
		dev_err(hba->dev, "%s: UFS BUCK got a falling Volt \n",
			__func__);
		break;
	case DSM_UFS_LINKUP_ERR:
		if (!(g_ufs_dsm_adaptor.err_type&(1 << UFS_LINKUP_ERR))) {
			pr_err("UFS DSM Error! Err Num: %lu, %lu\n",
				code, g_ufs_dsm_adaptor.err_type);
			break;
		}
		ret = snprintf(dsm_log_buff, buff_size,
				"UFS Linkup Line not correct,"
				"lane_rx:%d, lane_tx:%d\n",
				hba->max_pwr_info.info.lane_rx,
				hba->max_pwr_info.info.lane_tx);
		dsm_log_buff += ret;
		buff_size -= ret;
		break;
	default:
		pr_err("unknown error code: %lu\n", code);
		return 0;
	}
	ufs_dsm_real_upload_size = sizeof(g_ufs_dsm_log.dsm_log)-buff_size;
	if (buff_size <= 0) {
		ufs_dsm_real_upload_size = sizeof(g_ufs_dsm_log.dsm_log)-1;
		pr_err("dsm log buff overflow!\n");
	}
	pr_err("dsm_log:\n %s\n", g_ufs_dsm_log.dsm_log);
	pr_err("buff_size = %d\n", buff_size);
	return 1;
}

int dsm_ufs_enabled(void)
{
	return dsm_ufs_enable;
}

/*lint -e648 -e845*/
extern int get_rpmb_key_status(void);
int dsm_ufs_utp_err_need_report(void)
{
    if ((0 == get_rpmb_key_status()) && (OCS_FATAL_ERROR == g_ufs_dsm_adaptor.ocs)) {
        return 0;
    }
    return 1;
}

void dsm_ufs_enable_volt_irq(struct ufs_hba *hba)
{
	if (hba->volt_irq < 0)
		return;
	else
		enable_irq(hba->volt_irq);
}

void dsm_ufs_disable_volt_irq(struct ufs_hba *hba)
{
	if (hba->volt_irq < 0)
		return;
	else
		disable_irq(hba->volt_irq);
}

int dsm_ufs_uic_cmd_err_need_report(void)
{
	u32 uic_cmd = g_ufs_dsm_adaptor.uic_info[0];
	if((UIC_CMD_DME_HIBER_ENTER == uic_cmd) || (UIC_CMD_DME_HIBER_EXIT == uic_cmd))
		return 0;
	return 1;
}

int dsm_ufs_linkup_err_need_report(void)
{
#ifdef CONFIG_UFS_DEVICE_RELATED_CONFIGS
	extern int force_link_to_1lane;
	if(force_link_to_1lane) {
		pr_info("%s: force_link_to_llane, do not report\n", __func__);
		return 0;
	}
#endif
	return 1;
}

int dsm_ufs_uic_err_need_report(struct ufs_hba *hba)
{
	u32 ov_flag = 0;
	u32 counter = 0;
	static unsigned long uic_err_cnt = 0;
	static unsigned long tmp_bits = 0;
	static unsigned long ten_billon_bits_cnt = 0;

	uic_err_cnt++;
	ufshcd_dme_get(hba, UIC_ARG_MIB(0xd09d), &ov_flag); /* get ov flag */
	ufshcd_dme_get(hba, UIC_ARG_MIB(0xd098), &counter); /* get synbol cnt / 1024 */
	ufshcd_dme_set(hba, UIC_ARG_MIB(0xd09c), 0x5); /* reset cnter0 and enable it */
	if (ov_flag & 0x1)
		tmp_bits += (1UL << 32) * 1024 * 2 * 8;

	tmp_bits += (unsigned long)counter * 1024 * 2 * 8;
	ten_billon_bits_cnt +=  tmp_bits / TEN_BILLION_BITS;
	tmp_bits = tmp_bits % TEN_BILLION_BITS;

	pr_info("%s: errcnt = %lu, 10^10_cnt = %lu, tmpbits = %lu, ovflag = %u, counter = %u\n",
		   __func__,
		   uic_err_cnt,
		   ten_billon_bits_cnt,
		   tmp_bits,
		   ov_flag & 0x1,
		   counter);

	if ((ten_billon_bits_cnt > 0) && (uic_err_cnt > ten_billon_bits_cnt))
		return 1;

	pr_info("%s: UECPA:%08x,UECDL:%08x,UECN:%08x,UECT:%08x,UEDME:%08x\n", __func__,
		   g_ufs_dsm_adaptor.uic_uecpa,
		   g_ufs_dsm_adaptor.uic_uecdl,
		   g_ufs_dsm_adaptor.uic_uecn,
		   g_ufs_dsm_adaptor.uic_uect,
		   g_ufs_dsm_adaptor.uic_uedme);
	pr_info("%s: UIC error cnt below threshold, do not report!\n", __func__);
	return 0;
}
/*lint +e648 +e845*/
void dsm_ufs_handle_work(struct work_struct *work)
{
	struct ufs_hba *hba;
	unsigned long flags;

	hba = container_of(work, struct ufs_hba, dsm_work);

	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_FASTBOOT_PWMODE_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_FASTBOOT_PWMODE_ERR, "Fastboot PwrMode Error");/* !e713*/
		clear_bit_unlock((unsigned int)UFS_FASTBOOT_PWMODE_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_FASTBOOT_RW_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_FASTBOOT_RW_ERR, "Fastboot RW Error");/* !e713*/
		clear_bit_unlock((unsigned int)UFS_FASTBOOT_RW_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_UIC_TRANS_ERR)) {
		if (dsm_ufs_uic_err_need_report(hba)) {
			DSM_UFS_LOG(hba, DSM_UFS_UIC_TRANS_ERR, "UIC No Fatal Error");
		}
		clear_bit_unlock(UFS_UIC_TRANS_ERR, &g_ufs_dsm_adaptor.err_type);

		msleep(100);
		spin_lock_irqsave(hba->host->host_lock, flags);/*lint !e550*/
		ufshcd_enable_intr(hba, UIC_ERROR);
		spin_unlock_irqrestore(hba->host->host_lock, flags);/*lint !e550*/
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_UIC_CMD_ERR)) {
		if (dsm_ufs_uic_cmd_err_need_report()) {
			DSM_UFS_LOG(hba, DSM_UFS_UIC_CMD_ERR, "UIC Cmd Error");
		}
		clear_bit_unlock(UFS_UIC_CMD_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_CONTROLLER_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_CONTROLLER_ERR, "UFS Controller Error");
		clear_bit_unlock(UFS_CONTROLLER_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_DEV_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_DEV_ERR, "UFS Device Error");
		clear_bit_unlock(UFS_DEV_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_UTP_TRANS_ERR)) {
		if (dsm_ufs_utp_err_need_report()) {
			DSM_UFS_LOG(hba, DSM_UFS_UTP_ERR, "UTP Transfer Error");
		}
		clear_bit_unlock(UFS_UTP_TRANS_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_TIMEOUT_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_TIMEOUT_ERR, "UFS TimeOut Error");
		clear_bit_unlock(UFS_TIMEOUT_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_SCSI_CMD_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_SCSI_CMD_ERR, "UFS SCSI CMD Error");
		clear_bit_unlock(UFS_SCSI_CMD_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_VOLT_GPIO_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_VOLT_GPIO_ERR, "UFS Volt Fall Error");
		clear_bit_unlock(UFS_VOLT_GPIO_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_LINKUP_ERR)) {
		if(dsm_ufs_linkup_err_need_report()) {
			DSM_UFS_LOG(hba, DSM_UFS_LINKUP_ERR, "UFS Linkup Error");
		}
		clear_bit_unlock(UFS_LINKUP_ERR, &g_ufs_dsm_adaptor.err_type);
	}
	if (g_ufs_dsm_adaptor.err_type & (1 << UFS_INLINE_CRYPTO_ERR)) {
		DSM_UFS_LOG(hba, DSM_UFS_CONTROLLER_ERR, "UFS inline crypto error");
		clear_bit_unlock(UFS_INLINE_CRYPTO_ERR, &g_ufs_dsm_adaptor.err_type);
	}
}

static irqreturn_t ufs_gpio_irq_handle(int irq, void *__hba)
{
	struct ufs_hba *hba = __hba;

	dsm_ufs_update_error_info(hba, DSM_UFS_VOLT_GPIO_ERR);
	return IRQ_HANDLED;
}


static int ufs_volt_gpio_init(struct device *dev)
{
	int err;
	int irq;
	struct device_node *node =  dev->of_node;
	unsigned int gpio;

	gpio = of_get_named_gpio(node, "volt-irq,ufs-gpios", 0);
	if (!gpio_is_valid(gpio)) {
		pr_err("gpio is unvalid!\n");
		return -ENOENT;
	}

	err = gpio_request(gpio, "ufs_volt");
	if (err < 0) {
		pr_info("Can`t request UFS_VOLT gpio %d\n", gpio);
		return -EIO;
	}

	err = gpio_direction_input(gpio);
	if (err < 0)
		goto out_free;

	irq = gpio_to_irq(gpio);
	if (irq < 0) {
		pr_info("Could not set UFS_VOLT_GPIO irq = %d!, err = %d\n",
				gpio, irq);
		goto out_free;
	}

	err = request_irq((unsigned int)irq,
			ufs_gpio_irq_handle, (unsigned long)IRQF_TRIGGER_FALLING,
			"ufs_volt", NULL);
	if (err) {
		free_irq(gpio, NULL);
		pr_info("Request ufs volt gpio irq failed.\n");
		goto out_free;
	}

	return irq;
out_free:
	gpio_free(gpio);
	return -EIO;
}

void dsm_ufs_init(struct ufs_hba *hba)
{
	int ufs_volt_irq;
	struct device *dev = hba->dev;

	ufs_volt_irq = ufs_volt_gpio_init(dev);
	if (ufs_volt_irq < 0) {
		hba->volt_irq = -1;
		pr_err("ufs volt gpio irq failed.\n");
	} else {
		hba->volt_irq = ufs_volt_irq;
	}

	ufs_dclient = dsm_register_client(&dsm_ufs);
	if (!ufs_dclient) {
		pr_err("ufs dclient init error");
		return;
	}

	INIT_WORK(&hba->dsm_work, dsm_ufs_handle_work);
	spin_lock_init(&g_ufs_dsm_log.lock);
	dsm_ufs_enable = 1;
	async_schedule(dsm_ufs_fastboot_async, hba);
}
/*lint +e747 +e713 +e715 +e732 +e835*/
