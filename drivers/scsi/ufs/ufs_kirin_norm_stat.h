#ifndef _UFS_STAT_H_
#define _UFS_STAT_H_


struct ring_fifo_hist
{
	u32   rec_pos;
	u32   depth;  /* 必须是2^n 大小 */
	u32   entry_size;

	void*  fifo_entry;
};

#define UFS_UIC_ERR_HIST_DEPTH    32

struct ufshcd_uic_err_info {
	u32      err_reg;
	ktime_t  tm_stamp;
};

struct ufshcd_uic_err_hist {
	struct ring_fifo_hist       fifo;
	struct ufshcd_uic_err_info  err_entry[UFS_UIC_ERR_HIST_DEPTH];
};

#define UFS_INTR_HIST_DEPTH    32

struct ufshcd_intr_info {
	u32      intr_reg;
	u32      hcs_reg;
	ktime_t  tm_stamp;
};

struct ufshcd_intr_hist {
	struct ring_fifo_hist     fifo;
	struct ufshcd_intr_info   intr_entry[UFS_INTR_HIST_DEPTH];
};

struct scsi_cmd_info {
/* ITLQ nexus 的 cmd 和 lun + task Tag */
	u8   op_code;     /* opcode of CDB  */
	u8   task_tag;
	u8   target_lun;
/* 命令执行的结果 */
	u8   utrd_ocs;    /* ocs reported by HCI */
	u32  res_status;  /* 如果OCS为0，res_status有效为response里的Status */
	u8   sense_key;   /* 如果status为0，sense_key有效 */
	u8   ASC;         /* Additional Sense Code */
	u8   ASCQ;        /* Additional Sense Code Qualifier */
	u8   reserve;
};

/* 一次命令执行的过程信息 */
struct ufs_utp_cmd_info
{
	struct scsi_cmd_info scsi_cmd;

	ktime_t  tm_start;
	ktime_t  tm_end;

	void *   refer_info;
};

#define UFS_STATS_CMD_HIST_DEPTH	32

/* 历史命令记录循环队列 */
struct ufshcd_utp_cmd_hist
{
	struct ring_fifo_hist     fifo;
	struct ufs_utp_cmd_info   cmd_entry[UFS_STATS_CMD_HIST_DEPTH];
};


struct ufshcd_hist
{
	struct ufshcd_intr_hist    intr_hist;

	struct ufshcd_uic_err_hist pa_err;
	struct ufshcd_uic_err_hist dl_err;
	struct ufshcd_uic_err_hist nl_err;
	struct ufshcd_uic_err_hist tl_err;
	struct ufshcd_uic_err_hist dme_err;

	struct ufshcd_utp_cmd_hist utp_cmd_hist;
};


struct ufs_stats;


static inline void init_ring_fifo_hist( struct ring_fifo_hist * rfifo, size_t depth, void * fifo_entry, u32 entry_size )
{
	rfifo->depth      = depth;
	rfifo->rec_pos    = 0;
	rfifo->fifo_entry = fifo_entry;
	rfifo->entry_size = entry_size;  /* 必须是2^n 大小 */
}


static inline void * get_hist_fifo( struct ring_fifo_hist * hist_fifo, u32 pos )
{
	return ( (char *)(hist_fifo->fifo_entry) + ( (pos % hist_fifo->depth) * hist_fifo->entry_size ) );
}

static inline void * add_hist_fifo( struct ring_fifo_hist * hist_fifo )
{
	u32 cur_pos = hist_fifo->rec_pos ++;

	return get_hist_fifo( hist_fifo, cur_pos );
}

#define iter_rfifo_all( hist_fifo, iter ) for( (iter) = 0; (iter) < (hist_fifo)->depth; (iter) ++ )

#define iter_rfifo_backview_all( hist_fifo, iter, t ) \
	for( (t) = 0, (iter) = (hist_fifo)->rec_pos - 1; \
		(t) < (hist_fifo)->depth; \
		(t) ++, (iter)-- )

#undef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


void ufs_add_intr_rec_hist(struct ufshcd_intr_hist *intr_hist, u32 is_reg, u32 hcs_reg);

void ufs_add_uic_err_hist(struct ufshcd_uic_err_hist *err_hist, u32 err_reg);

void ufs_utp_cmd_end_add_hist(struct ufshcd_utp_cmd_hist *cmd_hist,
					void * refer_info, u8 ocs, u32 result);

void ufs_init_hist_all(struct ufshcd_hist *hist_all);


static inline void ufshcd_init_stats(struct ufs_stats *stats)
{
	stats->hist_rec = NULL;
}

static inline void ufs_add_intr_hist(struct ufs_hba *hba, u32 is_reg, u32 hcs_reg)
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if( NULL != hist_rec ) {
		ufs_add_intr_rec_hist(&(hist_rec->intr_hist), is_reg, hcs_reg);
	}
}

static inline void ufs_add_uic_err_hist_pa( struct ufs_hba *hba, u32 err_reg )
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if(NULL != hist_rec) {
		ufs_add_uic_err_hist(&(hist_rec->pa_err), err_reg);
	}
}

static inline void ufs_add_uic_err_hist_dl( struct ufs_hba *hba, u32 err_reg )
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if(NULL != hist_rec) {
		ufs_add_uic_err_hist(&(hist_rec->dl_err), err_reg);
	}
}

static inline void ufs_add_uic_err_hist_nl( struct ufs_hba *hba, u32 err_reg )
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if(NULL != hist_rec) {
		ufs_add_uic_err_hist(&(hist_rec->nl_err), err_reg);
	}
}

static inline void ufs_add_uic_err_hist_tl( struct ufs_hba *hba, u32 err_reg )
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if(NULL != hist_rec) {
		ufs_add_uic_err_hist(&(hist_rec->tl_err), err_reg);
	}
}

static inline void ufs_add_uic_err_hist_dme( struct ufs_hba *hba, u32 err_reg )
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if(NULL != hist_rec) {
		ufs_add_uic_err_hist(&(hist_rec->dme_err), err_reg);
	}
}

static inline void ufs_add_cmd_hist( struct ufs_hba *hba, struct ufshcd_lrb *lrbp, \
				u8 ocs, u32 result )
{
	struct ufshcd_hist *hist_rec;
	hist_rec = hba->ufs_stats.hist_rec;

	if( NULL != hist_rec ) {
		ufs_utp_cmd_end_add_hist(&(hist_rec->utp_cmd_hist), lrbp, ocs, result);
	}
}

#endif
