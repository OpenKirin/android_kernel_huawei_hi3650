#ifndef _UFS_KIRIN_RDR_H_
#define _UFS_KIRIN_RDR_H_

struct ufs_rdr_ctrl {
	uint  total_mem_size;
	uint  log_mem_size;
	uint  nvinfo_mem_size;
	uint  log_mem_length;

	u8 * saved_mem_vaddr;
	u8 * nvinfo_mem_addr;
	u8 * log_mem_addr;

	spinlock_t rdr_lock;
	bool dumping;
};

int ufs_rdr_init(struct ufs_hba *hba);

int ufs_rdr_exit(struct ufs_hba *hba);

int ufs_rdr_hist_init(struct ufs_hba *hba);

void ufs_rdr_log_clean( void );

char * ufs_rdr_log_show( void );

#endif