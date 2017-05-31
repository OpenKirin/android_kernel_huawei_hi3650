/* Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * UFS debugfs - add debugfs interface to the ufshcd.
 * This is currently used for statistics collection and exporting from the
 * UFS driver.
 * This infrastructure can be used for debugging or direct tweaking
 * of the driver from userspace.
 *
 */

#ifndef _UFS_DEBUGFS_H
#define _UFS_DEBUGFS_H

#include <linux/debugfs.h>
#include "ufshcd.h"

#ifdef CONFIG_DEBUG_FS
void ufsdbg_add_debugfs(struct ufs_hba *hba);

void ufsdbg_remove_debugfs(struct ufs_hba *hba);
void ufsdbg_pr_buf_to_std(struct ufs_hba *hba, int offset, int num_regs,
				char *str, void *priv);
void update_req_stats(struct ufs_hba *hba, struct ufshcd_lrb *lrbp);
int ufshcd_tag_req_type(struct request *rq);
#define UFSHCD_UPDATE_ERROR_STATS(hba, type)	\
	do {					\
		if (type < UFS_ERR_MAX)	\
			hba->ufs_stats.err_stats[type]++;	\
	} while (0)

#define UFSHCD_UPDATE_TAG_STATS(hba, tag)			\
	do {							\
		struct request *rq;	\
		u64 **tag_stats = hba->ufs_stats.tag_stats;	\
		int rq_type;					\
		rq = hba->lrb[task_tag].cmd ?	\
			hba->lrb[task_tag].cmd->request : NULL;	\
		if (!rq) \
			break; \
		if (!hba->ufs_stats.enabled) \
			break;					\
		tag_stats[tag][TS_TAG]++;			\
		    if (!(rq->cmd_type & REQ_TYPE_FS))	\
			    break;					\
		WARN_ON(hba->ufs_stats.q_depth > hba->nutrs);	\
		rq_type = ufshcd_tag_req_type(rq);		\
		tag_stats[hba->ufs_stats.q_depth++][rq_type]++;	\
	} while (0)

#define UFSHCD_UPDATE_TAG_STATS_COMPLETION(hba, cmd)		\
	do {							\
		struct request *rq = cmd ? cmd->request : NULL;	\
		if (rq)	\
		    if (rq->cmd_type & REQ_TYPE_FS) \
				hba->ufs_stats.q_depth--; \
	} while (0)

#define UFSDBG_ADD_DEBUGFS(hba)		ufsdbg_add_debugfs(hba);

#define UFSDBG_REMOVE_DEBUGFS(hba)	ufsdbg_remove_debugfs(hba);

#else
void ufsdbg_add_debugfs(struct ufs_hba *hba)
{
}
void ufsdbg_remove_debugfs(struct ufs_hba *hba)
{
}
void ufsdbg_fail_request(struct ufs_hba *hba, u32 *intr_status)
{
}
void ufsdbg_pr_buf_to_std(struct ufs_hba *hba, int offset, int num_regs,
				char *str, void *priv)
{
}
#define UFSHCD_UPDATE_TAG_STATS(hba, tag)
#define UFSHCD_UPDATE_TAG_STATS_COMPLETION(hba, cmd)
#define UFSDBG_ADD_DEBUGFS(hba)
#define UFSDBG_REMOVE_DEBUGFS(hba)
#define UFSHCD_UPDATE_ERROR_STATS(hba, type)
void update_req_stats(struct ufs_hba *hba, struct ufshcd_lrb *lrbp) {}
int ufshcd_tag_req_type(struct request *rq) {}
#endif
#endif /* End of Header */
