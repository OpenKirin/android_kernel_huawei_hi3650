#include "ufshcd.h"
#include "unipro.h"
#include "ufshci.h"
#include "ufs_kirin_norm_stat.h"


void ufs_init_intr_hist(struct ufshcd_intr_hist *intr_hist)
{
	memset(intr_hist->intr_entry, 0, sizeof(intr_hist->intr_entry));

	init_ring_fifo_hist(&intr_hist->fifo, ARRAY_SIZE(intr_hist->intr_entry), \
			intr_hist->intr_entry, (u32)sizeof(intr_hist->intr_entry[0]));
}

void ufs_add_intr_rec_hist(struct ufshcd_intr_hist *intr_hist, u32 is_reg, u32 hcs_reg)
{
	struct ufshcd_intr_info *intr_info;
	intr_info = (struct ufshcd_intr_info *)add_hist_fifo(&intr_hist->fifo);

	intr_info->intr_reg = is_reg;
	intr_info->hcs_reg  = hcs_reg;

	intr_info->tm_stamp = ktime_get();
}

void ufs_init_uic_err_hist( struct ufshcd_uic_err_hist * err_hist )
{
	memset( err_hist->err_entry, 0, sizeof(err_hist->err_entry) );

	init_ring_fifo_hist( &err_hist->fifo, ARRAY_SIZE(err_hist->err_entry), \
				err_hist->err_entry, (u32)sizeof(err_hist->err_entry[0]) );

}

void ufs_add_uic_err_hist( struct ufshcd_uic_err_hist * err_hist, u32 err_reg )
{
	struct ufshcd_uic_err_info * err_ent = (struct ufshcd_uic_err_info *)add_hist_fifo( &err_hist->fifo );

	err_ent->err_reg  = err_reg;
	err_ent->tm_stamp = ktime_get();
}


void ufs_init_utp_cmd_hist( struct ufshcd_utp_cmd_hist *cmd_hist )
{
	struct ring_fifo_hist   * rfifo = &cmd_hist->fifo;
	struct ufs_utp_cmd_info * cmd_info;
	u32 iter;

	iter_rfifo_all( rfifo, iter ) {
		cmd_info = (struct ufs_utp_cmd_info *)get_hist_fifo( rfifo, iter ); 
		cmd_info->refer_info = (void *)-1;
	}

	init_ring_fifo_hist( &cmd_hist->fifo, ARRAY_SIZE(cmd_hist->cmd_entry), \
				cmd_hist->cmd_entry, (u32)sizeof(cmd_hist->cmd_entry[0]) );

}


void ufs_utp_cmd_end_add_hist( struct ufshcd_utp_cmd_hist * cmd_hist, 
					void * refer_info, u8 ocs, u32 result )
{
	struct ufs_utp_cmd_info * cmd_info;
	struct ufshcd_lrb *       lrbp;
	struct scsi_cmd_info *    scsi_cmd;
	
	if( NULL == cmd_hist || NULL == refer_info ) {
		return ;
	}

	cmd_info = (struct ufs_utp_cmd_info *)add_hist_fifo( &cmd_hist->fifo );

	lrbp = (struct ufshcd_lrb *)refer_info;
	scsi_cmd = &(cmd_info->scsi_cmd);
	scsi_cmd->op_code    = lrbp->cmd->cmnd[0];
	scsi_cmd->task_tag   = (u8)lrbp->task_tag;
	scsi_cmd->target_lun = lrbp->lun;
	scsi_cmd->utrd_ocs   = ocs;
	scsi_cmd->res_status = result;

	if( lrbp->saved_sense_len ) {
		scsi_cmd->sense_key = lrbp->sense_buffer[2];
		scsi_cmd->ASC  = lrbp->sense_buffer[12];
		scsi_cmd->ASCQ = lrbp->sense_buffer[13];
	} else {
		scsi_cmd->sense_key = 0;
		scsi_cmd->ASC  = 0;
		scsi_cmd->ASCQ = 0;
	}

	cmd_info->refer_info = NULL;
	cmd_info->tm_start   = lrbp->issue_time_stamp;
	cmd_info->tm_end     = lrbp->complete_time_stamp;
}



void ufs_init_hist_all(struct ufshcd_hist *hist_all)
{
	ufs_init_intr_hist(&hist_all->intr_hist);

	ufs_init_uic_err_hist(&hist_all->pa_err);
	ufs_init_uic_err_hist(&hist_all->dl_err);
	ufs_init_uic_err_hist(&hist_all->nl_err);
	ufs_init_uic_err_hist(&hist_all->tl_err);
	ufs_init_uic_err_hist(&hist_all->dme_err);

	ufs_init_utp_cmd_hist(&hist_all->utp_cmd_hist);
}
