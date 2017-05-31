#ifndef _UFS_LOG_H_
#define _UFS_LOG_H_


struct ufs_hba;

struct ufshcd_lrb;

typedef void (*pfn_ufs_hba_print)( struct ufs_hba *, const char *, va_list );

typedef void (*pfn_ufs_hba_dump)( struct ufs_hba *, const char *, const void *, size_t );

void ufs_log_hba_print_caller( struct ufs_hba *hba, const char * format, ... );

void ufs_log_hba_dump_caller( struct ufs_hba * hba, const char * prefix_str,
						const void * buffer, size_t buf_size );

#define UFS_EXC_INFO_LOG(hba, ExcType, format, ...) \
		ufs_log_hba_print_caller((hba), "ufsdev_err_%x:"format"\n", (ExcType), ## __VA_ARGS__)

#define UFS_INFO_LOG(hba, format, ...) \
		ufs_log_hba_print_caller((hba), "ufsdev_log:"format"\n", ## __VA_ARGS__)

#define UFS_HEX_DUMP(hba, prefix_str, buf, len) \
		ufs_log_hba_dump_caller(hba, "ufsdev_log:"prefix_str, buf, len)


typedef struct _t_reg_info {
	const char * reg_name;
	u32          reg_offset;
} t_reg_info;

struct ufs_dme_att_mib_info {
	const char * attr_name;
	u16          attr_mib;
	u16          gen_sel_index;
};

struct ufs_log_attr {
	bool log_allowed;
	uint rate_cnt_per;
	uint rate_per_min;

	u32 saved_log_err;

	struct work_struct elog_work;

	spinlock_t log_lock;

	pfn_ufs_hba_print log_hba_print_fn;

	pfn_ufs_hba_dump  log_hba_dump_fn;
};

#define	UFS_LOG_UTR_RATE_CNT	5

#define	UFS_LOG_UTR_RATE_PER_MIN	3


void ufs_log_open( struct ufs_hba * hba );

void ufs_log_close( struct ufs_hba * hba );

void ufs_log_init( struct ufs_log_attr * log_attr, uint cnt_period, uint period_minute );

void ufs_log_fn_redir( struct ufs_hba *hba, pfn_ufs_hba_print log_hba_fn, pfn_ufs_hba_dump log_hba_dump_fn );

void ufs_log_get_fn( struct ufs_hba *hba, pfn_ufs_hba_print * log_hba_pfn, pfn_ufs_hba_dump * log_hba_dump_pfn );

void ufs_log_memreg_list( struct ufs_hba *hba, void __iomem * memreg_base, t_reg_info * reg_list, u32 reg_num  );

int ufs_log_dme_attr_list( struct ufs_hba *hba, struct ufs_dme_att_mib_info * attr_list, u32 attr_num, bool peer );

void ufs_log_hci_all_regs( struct ufs_hba *hba, u32 err_type );

void ufs_log_dme_attrs( struct ufs_hba *hba, u32 err_type );

void ufs_log_intr_hist( struct ufs_hba *hba, u32 err_type );

void ufs_log_uic_err_hist_all( struct ufs_hba *hba, u32 err_type );

void ufs_log_host_state( struct ufs_hba *hba, u32 err_type );

void ufs_log_pwr_info(struct ufs_hba *hba, u32 err_type);

void ufs_log_utrd_upiu_detail(struct ufs_hba *hba, struct ufshcd_lrb * lrbp, u32 err_type);

void ufs_log_hba_outstanding_upiu( struct ufs_hba *hba, u32 err_type );

void ufs_log_more_delay( struct ufs_hba *hba, u32 err_type );

void ufs_log_all_info( struct ufs_hba *hba, u32 err_type );

void ufs_log_all_info_limit_rate( struct ufs_hba *hba, u32 err_type );

void ufs_log_utr_limit_rate_spec( struct ufs_hba *hba, struct ufshcd_lrb * lrbp,
				u32 err_type, uint cnt_period, uint period_minute );

void ufs_log_utp_cmd_hist( struct ufs_hba *hba, u32 err_type );

void ufs_log_rate_limit_set( struct ufs_hba *hba, uint cnt_period, uint period_minute );

static inline void ufs_log_utr_limit_rate( struct ufs_hba *hba, struct ufshcd_lrb * lrbp, u32 err_type )
{
	ufs_log_utr_limit_rate_spec( hba, lrbp, err_type,\
			UFS_LOG_UTR_RATE_CNT, UFS_LOG_UTR_RATE_PER_MIN );
}

#endif

