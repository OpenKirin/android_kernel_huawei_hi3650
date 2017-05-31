#ifndef _UFS_KIRIN_LOG_H_
#define _UFS_KIRIN_LOG_H_

void ufs_kirin_log_hci_vendor_regs( struct ufs_hba *hba, int errType );

void ufs_kirin_log_soc_all_regs( struct ufs_hba *hba, int errType );

void ufs_kirin_log_phy_mpx_tst( struct ufs_hba *hba );

#endif

