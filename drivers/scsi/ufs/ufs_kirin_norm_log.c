#include "ufshcd.h"
#include "unipro.h"
#include "ufshci.h"
#include "ufs_kirin_norm_stat.h"
#include "ufs_kirin_norm_log.h"



struct ufs_dme_att_mib_info ufs_dme_attr_tab[] = {
  {"PA_PACPFrameCount",  0x15C0, 0 },
  {"PA_PACPErrorCount",  0x15C1, 0 },
  {"DL_ReInitCount",     0x2100, 0 },
  {"DME_ErrPHYInd",      0xD060, 0 },
  {"DME_ErrPAInd",       0xD061, 0 },
  {"DME_ErrDInd",        0xD062, 0 },
  {"DME_ErrNInd",        0xD063, 0 },
  {"DME_ErrTInd",        0xD064, 0 },
  {"VS_L2Status",        0xD082, 0 },
  {"VS_PowerState",      0xD083, 0 },
  {"VS_DebugLinkStartup",0xD095, 0 },
  {"VS_DebugPwrChg",     0xD096, 0 },
  {"VS_DebugStates",     0xD097, 0 },
 };


void ufs_log_hba_print( struct ufs_hba *hba, const char * format, va_list args )
{
	struct va_format vaf;
	vaf.fmt = format;
	vaf.va = &args;

	printk(KERN_ERR"%pV", &vaf);
}

void ufs_log_hba_dump( struct ufs_hba * hba, const char * prefix_str,
				const void * buffer, size_t buf_size )
{
	print_hex_dump(KERN_ERR, prefix_str,
		DUMP_PREFIX_NONE, 16, 1, buffer, buf_size, (bool)false );
}

void ufs_log_hba_print_caller( struct ufs_hba *hba, const char * format, ... )
{
	struct ufs_log_attr * log_attr;
	pfn_ufs_hba_print print_hba_fn;
	ulong flags;

	va_list args;
	va_start(args, format);

	log_attr = &(hba->log_attr);

	if( log_attr->log_allowed ) {
		spin_lock_irqsave( &(log_attr->log_lock), flags );
		print_hba_fn = log_attr->log_hba_print_fn;
		spin_unlock_irqrestore( &(log_attr->log_lock), flags );

		print_hba_fn( hba, format, args );
	}

	va_end(args);
}


void ufs_log_hba_dump_caller( struct ufs_hba * hba, const char * prefix_str,
					const void * buffer, size_t buf_size )
{
	struct ufs_log_attr * log_attr;
	pfn_ufs_hba_dump dump_hba_fn;
	ulong flags;

	log_attr = &(hba->log_attr);

	if( log_attr->log_allowed ) {
		spin_lock_irqsave( &(log_attr->log_lock), flags );
		dump_hba_fn = log_attr->log_hba_dump_fn;
		spin_unlock_irqrestore( &(log_attr->log_lock), flags );

		dump_hba_fn( hba, prefix_str, buffer, buf_size );
	}
}

void ufs_log_get_fn( struct ufs_hba * hba, pfn_ufs_hba_print * print_hba_pfn, pfn_ufs_hba_dump * dump_hba_pfn )
{
	struct ufs_log_attr * log_attr;
	ulong flags;

	log_attr = &(hba->log_attr);

	spin_lock_irqsave( &(log_attr->log_lock), flags );
	*print_hba_pfn = log_attr->log_hba_print_fn;
	*dump_hba_pfn  = log_attr->log_hba_dump_fn;
	spin_unlock_irqrestore( &(log_attr->log_lock), flags );
}

void ufs_log_fn_redir( struct ufs_hba * hba, pfn_ufs_hba_print print_hba_fn, pfn_ufs_hba_dump dump_hba_fn )
{
	struct ufs_log_attr * log_attr;
	ulong flags;

	log_attr = &(hba->log_attr);

	spin_lock_irqsave( &(log_attr->log_lock), flags );
	log_attr->log_hba_print_fn = print_hba_fn;
	log_attr->log_hba_dump_fn  = dump_hba_fn;
	spin_unlock_irqrestore( &(log_attr->log_lock), flags );
}


bool log_rate_limit_minute( uint *log_cnt, ktime_t *log_start_tm, uint cnt_period, uint period_minute )
{
	ktime_t cur_tm, sub_tm;

	if( *log_cnt >= cnt_period ) {
		cur_tm = ktime_get();
		sub_tm = ktime_sub(cur_tm, (*log_start_tm));

		if( ktime_to_ms(sub_tm) <= ((s64)period_minute * 60 * 1000) ) {
			return false;
		}

		*log_cnt = 0;
		*log_start_tm = cur_tm;
	}
	*log_cnt = *log_cnt + 1;

	return true;
}

void ufs_log_memreg_list( struct ufs_hba *hba, void __iomem * memreg_base, t_reg_info * reg_list, u32 reg_num  )
{
	u32 t;

	for( t = 0; t < reg_num; t ++, reg_list++ ){
		UFS_INFO_LOG( hba, "%s[%08x]", reg_list->reg_name, readl( memreg_base + reg_list->reg_offset ) );
	}
}

int ufs_log_dme_attr_list( struct ufs_hba *hba, struct ufs_dme_att_mib_info * attr_list, u32 attr_num, bool peer )
{
	u32 t;
	u32 attr_val;
	u32 attr_mib_sel;
	int err;
	u8  dme_end;

	if(peer) {
		dme_end = DME_PEER;
	} else {
		dme_end = DME_LOCAL;
	}
	err = 0;
	for( t = 0; t < attr_num; t ++, attr_list++ ){

		attr_mib_sel = attr_list->attr_mib;
		attr_mib_sel = ( attr_mib_sel << 16 ) | attr_list->gen_sel_index;

		err = ufshcd_dme_get_attr( hba, attr_mib_sel, &attr_val, dme_end );

		if( 0 != err ) {
			UFS_INFO_LOG( hba, "ufshcd get dme attr value of %08x failed with error %d", attr_mib_sel, err );
			break;
		}

		UFS_INFO_LOG( hba, "%s_%d[%08x]", attr_list->attr_name, attr_list->gen_sel_index, attr_val );
	}

	return err;
}


static void ufs_log_hci_cap_regs( struct ufs_hba *hba, u32 err_type )
{
	UFS_EXC_INFO_LOG( hba, err_type,\
			"HCI Cap Regs log[%08x;%08x;%08x;%08x;%08x]", \
			ufshcd_readl(hba, REG_CONTROLLER_CAPABILITIES),
			ufshcd_readl(hba, REG_UFS_VERSION),
			ufshcd_readl(hba, REG_CONTROLLER_DEV_ID),
			ufshcd_readl(hba, REG_CONTROLLER_PROD_ID),
			ufshcd_readl(hba, REG_CONTROLLER_AHIT) );
}

static void ufs_log_hci_oprun_regs( struct ufs_hba *hba, u32 err_type )
{
	UFS_EXC_INFO_LOG( hba, err_type, \
			"HCI OpRun Status Regs log[%08x;%08x;%08x;%08x]",\
			ufshcd_readl(hba, REG_INTERRUPT_STATUS),
			ufshcd_readl(hba, REG_INTERRUPT_ENABLE),
			ufshcd_readl(hba, REG_CONTROLLER_STATUS),
			ufshcd_readl(hba, REG_CONTROLLER_ENABLE) );

#ifdef CONFIG_SCSI_UFS_KIRIN_LINERESET_CHECK
	UFS_EXC_INFO_LOG( hba, err_type, \
			"HCI UIC ERR Regs log[%08x;%08x;%08x;%08x;%08x]",\
			hba->reg_uecpa,
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_DATA_LINK_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_NETWORK_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_TRANSPORT_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_DME));
#else
	UFS_EXC_INFO_LOG( hba, err_type, \
			"HCI UIC ERR Regs log[%08x;%08x;%08x;%08x;%08x]",\
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_DATA_LINK_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_NETWORK_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_TRANSPORT_LAYER),
			ufshcd_readl(hba, REG_UIC_ERROR_CODE_DME));
#endif
}

static void ufs_log_hci_utp_regs( struct ufs_hba *hba, u32 err_type )
{
	UFS_EXC_INFO_LOG( hba, err_type, \
			"HCI UTP TR Regs log[%08x;%08x;%08x;%08x;%08x;%08x]",\
			ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL),
			ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_BASE_L),
			ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_BASE_H),
			ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL),
			ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_CLEAR),
			ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_LIST_RUN_STOP) );

	UFS_EXC_INFO_LOG( hba, err_type, \
			"HCI UTP TM Regs log[%08x;%08x;%08x;%08x;%08x]",\
			ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_BASE_L),
			ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_BASE_H),
			ufshcd_readl(hba, REG_UTP_TASK_REQ_DOOR_BELL),
			ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_CLEAR),
			ufshcd_readl(hba, REG_UTP_TASK_REQ_LIST_RUN_STOP));
}

static void ufs_log_hci_uic_regs( struct ufs_hba *hba, u32 err_type )
{
	UFS_EXC_INFO_LOG( hba, err_type, \
			"HCI UIC Regs log[%08x;%08x;%08x;%08x]",\
			ufshcd_readl(hba, REG_UIC_COMMAND),
			ufshcd_readl(hba, REG_UIC_COMMAND_ARG_1),
			ufshcd_readl(hba, REG_UIC_COMMAND_ARG_2),
			ufshcd_readl(hba, REG_UIC_COMMAND_ARG_3) );
}

void ufs_log_hci_all_regs( struct ufs_hba *hba, u32 err_type )
{
	ufs_log_hci_cap_regs( hba, err_type );
	ufs_log_hci_oprun_regs( hba, err_type );
	ufs_log_hci_utp_regs( hba, err_type );
	ufs_log_hci_uic_regs( hba, err_type );
}

void ufs_log_dme_attrs( struct ufs_hba *hba, u32 err_type )
{
	UFS_EXC_INFO_LOG( hba, err_type, "DME key attributes log Start" );

	(void)ufs_log_dme_attr_list( hba, ufs_dme_attr_tab, (u32)ARRAY_SIZE(ufs_dme_attr_tab), (bool)false );

	UFS_EXC_INFO_LOG( hba, err_type, "DME key attributes log end" );
}

static void ufs_log_uic_err_hist( struct ufs_hba *hba, struct ufshcd_uic_err_hist * err_hist, const char * layer_name )
{
	struct ring_fifo_hist      * rfifo;
	struct ufshcd_uic_err_info * err_info;

	u32 t, iter;

	rfifo = &err_hist->fifo;

	iter_rfifo_backview_all( rfifo, iter, t ) {
		err_info = (struct ufshcd_uic_err_info *)get_hist_fifo( rfifo, iter );
		if( 0 != err_info->err_reg ) {
			UFS_INFO_LOG( hba, "%s got error[%x] at %lld us", layer_name, err_info->err_reg, ktime_to_us(err_info->tm_stamp) );
		}
	}
}

void ufs_log_intr_hist( struct ufs_hba *hba, u32 err_type )
{
	struct ring_fifo_hist   *rfifo;
	struct ufshcd_intr_info *intr_info;
	struct ufshcd_hist      *hist;
	u32 t, iter;

	hist = hba->ufs_stats.hist_rec;
	if( NULL == hist )
		return ;

	UFS_EXC_INFO_LOG( hba, err_type, "all interrupts history log Start" );

	rfifo = &(hist->intr_hist.fifo);
	iter_rfifo_backview_all( rfifo, iter, t ) {
		intr_info = (struct ufshcd_intr_info *)get_hist_fifo( rfifo, iter );
		if( 0 != intr_info->intr_reg ) {
			UFS_INFO_LOG( hba, "interrupt with[%x,%x] at %lld us",
				intr_info->intr_reg,
				intr_info->hcs_reg,
				ktime_to_us(intr_info->tm_stamp) );
		}
	}

	UFS_EXC_INFO_LOG( hba, err_type, "all interrupts history log End" );
}


void ufs_log_uic_err_hist_all( struct ufs_hba *hba, u32 err_type )
{
	struct ufshcd_hist *hist = hba->ufs_stats.hist_rec;

	if( NULL == hist )
		return ;

	UFS_EXC_INFO_LOG( hba, err_type, "UIC all error histry log Start" );

	ufs_log_uic_err_hist( hba, &(hist->pa_err), "pa_L1.5" );
	ufs_log_uic_err_hist( hba, &(hist->dl_err), "dl_L2" );
	ufs_log_uic_err_hist( hba, &(hist->nl_err), "nl_L3" );
	ufs_log_uic_err_hist( hba, &(hist->tl_err), "tl_L4" );
	ufs_log_uic_err_hist( hba, &(hist->dme_err),"dme_layer" );

	UFS_EXC_INFO_LOG( hba, err_type, "UIC all error histry log End" );
}


void ufs_log_utp_cmd_hist( struct ufs_hba *hba, u32 err_type )
{
	struct ring_fifo_hist   *rfifo;
	struct ufs_utp_cmd_info *cmd_info;
	struct scsi_cmd_info    *scsi_cmd;
	struct ufshcd_hist      *hist;
	u32 t, iter;

	hist = hba->ufs_stats.hist_rec;

	if( NULL == hist )
		return ;

	UFS_EXC_INFO_LOG( hba, err_type, "UTP cmd history log Start" );

	rfifo = &(hist->utp_cmd_hist.fifo);

	iter_rfifo_backview_all( rfifo, iter, t ) {
		cmd_info = (struct ufs_utp_cmd_info *)get_hist_fifo( rfifo, iter );

		if( (void *)-1 == cmd_info->refer_info )
			continue;

		scsi_cmd = &(cmd_info->scsi_cmd);

		UFS_INFO_LOG( hba, "cmd_tag[%x]start at %lld us "
				"with request[%x:%x];",\
				scsi_cmd->task_tag,
				ktime_to_us(cmd_info->tm_start),
				scsi_cmd->op_code,
				scsi_cmd->target_lun );

		if( NULL == cmd_info->refer_info ) {
			UFS_INFO_LOG( hba, "cmd_tag[%x] end at %lld us "
					"with result[%x,%x,%x,%x,%x];",\
					scsi_cmd->task_tag,
					ktime_to_us(cmd_info->tm_end),
					scsi_cmd->utrd_ocs,
					scsi_cmd->res_status,
					scsi_cmd->sense_key,
					scsi_cmd->ASC,
					scsi_cmd->ASCQ );
		} else {
			UFS_INFO_LOG( hba, "cmd_tag[%x] is waitint for end", cmd_info->scsi_cmd.task_tag );
		}
	} 

	UFS_EXC_INFO_LOG( hba, err_type, "UTP cmd history log end" );
}



void ufs_log_host_state( struct ufs_hba *hba, u32 err_type )
{
	UFS_EXC_INFO_LOG( hba, err_type, "host state log start:");

	UFS_INFO_LOG(hba, "UFS Host state=%d", hba->ufshcd_state);
	UFS_INFO_LOG(hba, "lrb in use=0x%lx, outstanding reqs=0x%lx tasks=0x%lx",
		hba->lrb_in_use, hba->outstanding_tasks, hba->outstanding_reqs);
	UFS_INFO_LOG(hba, "saved_err=0x%x, saved_uic_err=0x%x",
		hba->saved_err, hba->saved_uic_err);
	UFS_INFO_LOG(hba, "Device power mode=%d, UIC link state=%d",
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	UFS_INFO_LOG(hba, "PM in progress=%d, sys. suspended=%d",
		hba->pm_op_in_progress, hba->is_sys_suspended);
	UFS_INFO_LOG(hba, "Auto BKOPS=%d, Host self-block=%d",
		hba->auto_bkops_enabled, hba->host->host_self_blocked);
	UFS_INFO_LOG(hba, "Clk gate=%d",
		hba->clk_gating.state );
	UFS_INFO_LOG(hba, "Host capabilities=0x%x, caps=0x%x",
		hba->capabilities, hba->caps);
	UFS_INFO_LOG(hba, "quirks=0x%x, dev. quirks=0x%x", hba->quirks,
		hba->dev_quirks);

	UFS_EXC_INFO_LOG( hba, err_type, "host state log end");
}

void ufs_log_pwr_info(struct ufs_hba *hba, u32 err_type)
{
	char *names[] = {
		"INVALID MODE",
		"FAST MODE",
		"SLOW_MODE",
		"INVALID MODE",
		"FASTAUTO_MODE",
		"SLOWAUTO_MODE",
		"INVALID MODE",
	};

	UFS_EXC_INFO_LOG( hba, err_type, "pwr info[RX,TX]:gear[%d,%d]lane[%d,%d]pwr[%s,%s]rate=%d",
		 hba->pwr_info.gear_rx, hba->pwr_info.gear_tx,
		 hba->pwr_info.lane_rx, hba->pwr_info.lane_tx,
		 names[hba->pwr_info.pwr_rx],
		 names[hba->pwr_info.pwr_tx],
		 hba->pwr_info.hs_rate );
}

static u8 ufs_log_utrd( struct ufs_hba *hba, struct utp_transfer_req_desc * utrdp, int tag )
{
	UFS_INFO_LOG( hba, "UPIU[%d] UTRD CType&DD&I[%x]OCS[%x]ucd_adr[%x:%x]rsp[%x,%x]prd[%x,%x]", tag,
			le32_to_cpu(utrdp->header.dword_0) >> 24,
			le32_to_cpu(utrdp->header.dword_2) & MASK_OCS,
			le32_to_cpu(utrdp->command_desc_base_addr_lo),
			le32_to_cpu(utrdp->command_desc_base_addr_hi),
			le16_to_cpu(utrdp->response_upiu_length),
			le16_to_cpu(utrdp->response_upiu_offset),
			le16_to_cpu(utrdp->prd_table_length),
			le16_to_cpu(utrdp->prd_table_offset) );

	return le32_to_cpu(utrdp->header.dword_2) & MASK_OCS;
}

static void ufs_log_upiu_cmd_req( struct ufs_hba *hba, struct utp_upiu_req * upiu_req, int tag )
{
	u32 dword0, dword1, dword2;
	struct utp_upiu_cmd * upiu_cmd = &(upiu_req->sc);

	dword0 = be32_to_cpu(upiu_req->header.dword_0);
	dword1 = be32_to_cpu(upiu_req->header.dword_1);
	dword2 = be32_to_cpu(upiu_req->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] cmd req Fags[%x]LUN[%x]Tag[%x]"\
			"SetType[%x]"\
			"EHSLen[%x]SegLen[%x]"\
			"ExpDataLen[%x]", 
			tag,
			(dword0>>16)&0x0FF, (dword0>>8)&0x0FF, (dword0)&0x0FF,
			(dword1>>24)&0x0F,
			(dword2>>24)&0x0FF, dword2&0x0FFFF,
			be32_to_cpu(upiu_cmd->exp_data_transfer_len) );

	UFS_HEX_DUMP(hba, "UPIU CDB dump:", upiu_cmd->cdb, sizeof(upiu_cmd->cdb) );
}


static void ufs_log_upiu_query_req( struct ufs_hba *hba, struct utp_upiu_req * upiu_req, int tag )
{
	u32 dword0, dword1, dword2;
	struct utp_upiu_query * upiu_query = &(upiu_req->qr);

	dword0 = be32_to_cpu(upiu_req->header.dword_0);
	dword1 = be32_to_cpu(upiu_req->header.dword_1);
	dword2 = be32_to_cpu(upiu_req->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] query Fags[%x]Tag[%x]"\
			"Func[%x]"\
			"EHSLen[%x]SegLen[%x]",
			tag,
			(dword0>>16)&0x0FF, (dword0)&0x0FF,
			(dword1>>16)&0x0FF,
			(dword2>>24)&0x0FF, dword2&0x0FFFF );

	UFS_INFO_LOG(hba, "UPIU[%d] query req OpCode[%x]idn[%x]index[%x]sel[%x]len[%x]val[%x]", tag,
			upiu_query->opcode, upiu_query->idn, upiu_query->index,
			upiu_query->selector, be16_to_cpu(upiu_query->length), be32_to_cpu(upiu_query->value) );
}

static void ufs_log_upiu_nopout_req( struct ufs_hba *hba, struct utp_upiu_req * upiu_req, int tag )
{
	u32 dword0, dword2;

	dword0 = be32_to_cpu(upiu_req->header.dword_0);
	dword2 = be32_to_cpu(upiu_req->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] nopout Fags[%x]Tag[%x]EHSLen[%x]SegLen[%x]",
			tag,
			(dword0>>16)&0x0FF, (dword0)&0x0FF,
			(dword2>>24)&0x0FF, dword2&0x0FFFF );
}

static void ufs_log_upiu_req( struct ufs_hba *hba, struct utp_upiu_req * upiu_req, int tag )
{
	u32 transaction;

	transaction = be32_to_cpu(upiu_req->header.dword_0) >> 24;

	switch( transaction ){
	case UPIU_TRANSACTION_COMMAND:
		ufs_log_upiu_cmd_req( hba, upiu_req, tag );
		break;
	case UPIU_TRANSACTION_QUERY_REQ:
		ufs_log_upiu_query_req( hba, upiu_req, tag );
		break;
	case UPIU_TRANSACTION_NOP_OUT:
		ufs_log_upiu_nopout_req( hba, upiu_req, tag );
		break;
	default:
		UFS_INFO_LOG(hba, "UPIU[%d] req use wrong transaction[%x]", tag, transaction );
		UFS_HEX_DUMP(hba, "UPIU req dump:", upiu_req, sizeof(struct utp_upiu_req) );
		return ;
	}
}

static void ufs_log_upiu_cmd_rsp( struct ufs_hba *hba, struct utp_upiu_rsp * upiu_rsp, int tag )
{
	u32 dword0, dword1, dword2;
	u16 sense_len;

	struct utp_cmd_rsp * cmd_rsp = &(upiu_rsp->sr);

	dword0 = be32_to_cpu(upiu_rsp->header.dword_0);
	dword1 = be32_to_cpu(upiu_rsp->header.dword_1);
	dword2 = be32_to_cpu(upiu_rsp->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] cmd rsp Fags[%x]LUN[%x]Tag[%x]"\
			"SetType[%x]Rsp[%x]Stat[%x]"\
			"EHSLen[%x]DevInfo[%x]SegLen[%x]"\
			"ResTrCnt[%x]",
			tag,
			(dword0>>16)&0x0FF, (dword0>>8)&0x0FF, (dword0)&0x0FF,
			(dword1>>24)&0x0F,(dword1>>8)&0x0FF, (dword1)&0x0FF,
			(dword2>>24)&0x0FF, (dword2>>16)&0x0FF, dword2&0x0FFFF,
			be32_to_cpu(cmd_rsp->residual_transfer_count) );

	sense_len = be16_to_cpu(cmd_rsp->sense_data_len);
	/* need focous on sense key & ASC 12BYTE & ASCQ 13BYTE */
	UFS_INFO_LOG(hba, "UPIU[%d] cmd rsp sense len(18) %d", tag, sense_len );
	if( 0 != sense_len ) {
		UFS_HEX_DUMP(hba, "UPIP RSP Sense Dump", cmd_rsp->sense_data, min_t(size_t, sense_len, (size_t)RESPONSE_UPIU_SENSE_DATA_LENGTH) );
	}
}

static void ufs_log_upiu_query_rsp( struct ufs_hba *hba, struct utp_upiu_rsp * upiu_rsp, int tag )
{
	u32 dword0, dword1, dword2;

	struct utp_upiu_query * query_rsp = &(upiu_rsp->qr);

	dword0 = be32_to_cpu(upiu_rsp->header.dword_0);
	dword1 = be32_to_cpu(upiu_rsp->header.dword_1);
	dword2 = be32_to_cpu(upiu_rsp->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] query rsp Fags[%x]Tag[%x]"\
			"func[%x]Rsp[%x]"\
			"EHSLen[%x]DevInfo[%x]SegLen[%x]",
			tag,
			(dword0>>16)&0x0FF, (dword0)&0x0FF,
			(dword1>>16)&0x0FF,(dword1>>8)&0x0FF,
			(dword2>>24)&0x0FF, (dword2>>16)&0x0FF, dword2&0x0FFFF );

	UFS_INFO_LOG(hba, "UPIU[%d] query rsp OpCode[%x]idn[%x]index[%x]sel[%x]len[%x]val[%x]", tag,
			query_rsp->opcode, query_rsp->idn, query_rsp->index,
			query_rsp->selector, be16_to_cpu(query_rsp->length), be32_to_cpu(query_rsp->value) );
}

static void ufs_log_upiu_reject_rsp( struct ufs_hba *hba, struct utp_upiu_rsp * upiu_rsp, int tag )
{
	u32 dword0, dword1, dword2;

	dword0 = be32_to_cpu(upiu_rsp->header.dword_0);
	dword1 = be32_to_cpu(upiu_rsp->header.dword_1);
	dword2 = be32_to_cpu(upiu_rsp->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] reject rsp Fags[%x]LUN[%x]Tag[%x]"\
			"Rsp[%x]"\
			"EHSLen[%x]DevInfo[%x]SegLen[%x]",
			tag,
			(dword0>>16)&0x0FF, (dword0>>8)&0x0FF, (dword0)&0x0FF,
			(dword1>>8)&0x0FF,
			(dword2>>24)&0x0FF, (dword2>>16)&0x0FF, dword2 & 0x0FFFF );
}

static void ufs_log_upiu_nopin_rsp( struct ufs_hba *hba, struct utp_upiu_rsp * upiu_rsp, int tag )
{
	u32 dword0, dword1, dword2;

	dword0 = be32_to_cpu(upiu_rsp->header.dword_0);
	dword1 = be32_to_cpu(upiu_rsp->header.dword_1);
	dword2 = be32_to_cpu(upiu_rsp->header.dword_2);

	UFS_INFO_LOG(hba, "UPIU[%d] nopin rsp Fags[%x]Tag[%x]"\
			"rsp[%x]"\
			"EHSLen[%x]DevInfo[%x]SegLen[%x]", 
			tag,
			(dword0>>16)&0x0FF, (dword0)&0x0FF,
			(dword1>>8)&0x0FF,
			(dword2>>24)&0x0FF, (dword2>>16)&0x0FF, dword2 & 0x0FFFF );
}

static void ufs_log_upiu_rsp( struct ufs_hba *hba, struct utp_upiu_rsp * upiu_rsp, int tag )
{
	u32 transaction;

	transaction = be32_to_cpu(upiu_rsp->header.dword_0) >> 24;

	switch( transaction ){
	case UPIU_TRANSACTION_RESPONSE:
		ufs_log_upiu_cmd_rsp( hba, upiu_rsp, tag );
		break;
	case UPIU_TRANSACTION_QUERY_RSP:
		ufs_log_upiu_query_rsp( hba, upiu_rsp, tag );
		break;
	case UPIU_TRANSACTION_REJECT_UPIU:
		ufs_log_upiu_reject_rsp( hba, upiu_rsp, tag );
		break;
	case UPIU_TRANSACTION_NOP_IN:
		ufs_log_upiu_nopin_rsp( hba, upiu_rsp, tag );
		break;
	default:
		UFS_INFO_LOG(hba, "UPIU[%d] rsp use wrong transaction[%x]", tag, transaction );
		UFS_HEX_DUMP(hba, "UPIU rsp dump:", upiu_rsp, sizeof(struct utp_upiu_rsp) );
	return ;
	}
}


void ufs_log_utrd_upiu_detail(struct ufs_hba *hba, struct ufshcd_lrb * lrbp, u32 err_type)
{
	u16 prdt_length;
	int tag;
	u8  req_ocs;

	tag = lrbp->task_tag;

	UFS_EXC_INFO_LOG(hba, err_type, "UTRD[%d] start at %lld us",
		tag, ktime_to_us(lrbp->issue_time_stamp));

	req_ocs = ufs_log_utrd( hba, lrbp->utr_descriptor_ptr, tag );

	ufs_log_upiu_req( hba, lrbp->ucd_req_ptr, tag );

	if( OCS_SUCCESS == req_ocs ) {
		ufs_log_upiu_rsp( hba, lrbp->ucd_rsp_ptr, tag );
	}

	if( OCS_INVALID_PRDT_ATTR == req_ocs ) {
		prdt_length = le16_to_cpu(lrbp->utr_descriptor_ptr->prd_table_length);
		UFS_HEX_DUMP(hba, "UPIU RPDT:", lrbp->ucd_prdt_ptr, sizeof(struct ufshcd_sg_entry) * prdt_length );
	}

	if( OCS_INVALID_COMMAND_STATUS != req_ocs ) {
		UFS_EXC_INFO_LOG(hba, err_type, "UTRD[%d] end at %lld us",
				tag, ktime_to_us(lrbp->complete_time_stamp));
	} else {
		UFS_EXC_INFO_LOG(hba, err_type, "UTRD[%d] is waiting..", tag );
	}
}

void ufs_log_hba_outstanding_upiu( struct ufs_hba *hba, u32 err_type )
{
	ulong tag;
	UFS_EXC_INFO_LOG(hba, err_type, "log all outstanding request start");

	for_each_set_bit( tag, &(hba->outstanding_reqs), (ulong)hba->nutrs ) {
		ufs_log_utrd_upiu_detail( hba, &hba->lrb[tag], err_type );
	}

	UFS_EXC_INFO_LOG(hba, err_type, "log all outstanding request end");
}

void ufs_log_all_info( struct ufs_hba *hba, u32 err_type )
{
	ufs_log_host_state(hba, err_type);
	ufs_log_pwr_info(hba, err_type);
	ufs_log_hci_all_regs(hba, err_type);
	ufshcd_vops_dump_reg(hba, err_type);
	ufs_log_intr_hist(hba, err_type);
	ufs_log_uic_err_hist_all(hba, err_type);
	ufs_log_dme_attrs(hba, err_type);
	ufs_log_hba_outstanding_upiu( hba, err_type);
}

void ufs_log_all_info_limit_rate( struct ufs_hba *hba, u32 err_type )
{
	static ktime_t ufs_log_start_tm = {.tv64 = 0UL};
	static uint    ufs_log_cnt = 0;
	ulong flags;
	bool log_allowed;

	struct ufs_log_attr * log_attr;

	log_attr = &(hba->log_attr);

	spin_lock_irqsave( &(log_attr->log_lock), flags );
	log_allowed = log_rate_limit_minute( &ufs_log_cnt, &ufs_log_start_tm,\
					log_attr->rate_cnt_per, log_attr->rate_per_min );
	spin_unlock_irqrestore( &(log_attr->log_lock), flags );

	if( log_allowed ) {
		ufs_log_all_info(hba, err_type);
	}
}


void ufs_log_utr_limit_rate_spec( struct ufs_hba *hba, struct ufshcd_lrb * lrbp,
				u32 err_type, uint cnt_period, uint period_minute )
{
	static ktime_t ufs_log_start_tm = {.tv64 = 0UL};
	static uint    ufs_log_cnt = 0;
	ulong flags;
	bool log_allowed;

	struct ufs_log_attr * log_attr;

	log_attr = &(hba->log_attr);

	spin_lock_irqsave( &(log_attr->log_lock), flags );
	log_allowed = log_rate_limit_minute( &ufs_log_cnt, &ufs_log_start_tm,\
					cnt_period, period_minute );
	spin_unlock_irqrestore( &(log_attr->log_lock), flags );

	if( log_allowed ) {
		ufs_log_utrd_upiu_detail(hba, lrbp, err_type);
	}
}


static void ufs_log_more_delay_work( struct work_struct *work )
{
	struct ufs_hba *hba;
	struct ufs_log_attr * log_attr;

	log_attr = container_of( work, struct ufs_log_attr, elog_work );

	hba = container_of( log_attr, struct ufs_hba, log_attr );

	ufs_log_all_info_limit_rate( hba, log_attr->saved_log_err );
}

void ufs_log_more_delay( struct ufs_hba *hba, u32 err_type )
{
	struct ufs_log_attr * log_attr = &(hba->log_attr);

	log_attr->saved_log_err = err_type;

	schedule_work( &(log_attr->elog_work) );
}

void ufs_log_rate_limit_set( struct ufs_hba *hba, uint cnt_period, uint period_minute )
{
	struct ufs_log_attr * log_attr;

	log_attr = &(hba->log_attr);
	log_attr->rate_cnt_per = cnt_period;
	log_attr->rate_per_min = period_minute;
}

void ufs_log_close( struct ufs_hba * hba )
{
	struct ufs_log_attr * log_attr;

	log_attr = &(hba->log_attr);

	log_attr->log_allowed = false;

	pr_err("ufsdev log is closed\n");
}

void ufs_log_open( struct ufs_hba * hba )
{
	struct ufs_log_attr * log_attr;

	log_attr = &(hba->log_attr);

	log_attr->log_allowed = true;

	pr_err("ufsdev log is opened\n");
}


void ufs_log_init( struct ufs_log_attr * log_attr, uint cnt_period, uint period_minute )
{
	spin_lock_init( &(log_attr->log_lock) );

	log_attr->log_allowed = true;
	log_attr->rate_cnt_per = cnt_period;
	log_attr->rate_per_min = period_minute;

	log_attr->log_hba_print_fn = ufs_log_hba_print;
	log_attr->log_hba_dump_fn  = ufs_log_hba_dump;

	INIT_WORK( &(log_attr->elog_work), ufs_log_more_delay_work );
}

