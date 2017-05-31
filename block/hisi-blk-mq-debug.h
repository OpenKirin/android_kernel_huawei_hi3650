#ifndef _HISI_BLK_MQ_DEBUG_H_
#define _HISI_BLK_MQ_DEBUG_H_

#include <linux/kernel.h>
#include <linux/blkdev.h>
#include <linux/hisi-blk-mq.h>

#ifdef CONFIG_HISI_MQ_DEBUG
extern unsigned char ufshcd_rq_error_enable;
void blk_mq_debug_update_request_error(void);
void blk_mq_debug_rq_timed_out(struct request *req);
static inline void blk_mq_debug_statistics_check(struct blkdev_statistics_info *info)
{
	if (info->blkdev_continue_idle && (info->blkdev_processing_read || info->blkdev_processing_write)) {
		BUG_ON(1);
	}
	if (info->blkdev_processing_read) {
		if (info->blkdev_continue_idle) {
			BUG_ON(1);
		}
	}
	if (info->blkdev_processing_write) {
		if (info->blkdev_continue_idle) {
			BUG_ON(1);
		}
	}
}
void blk_mq_debug_write_decision_init(int is_sync, struct blk_dispatch_decision_para *p);
void blk_mq_debug_write_decision_state_update(struct blk_dispatch_decision_para *p,
				char *debug_log);
void blk_mq_debug_dispatch_check(int is_sync, struct request_queue *q);
void blk_mq_debug_dispatch_rq_record(int is_sync, struct blk_dispatch_decision_para *p);
void blk_mq_debug_write_decision_end_check(int is_sync,
		struct blk_dispatch_decision_para *p,
		int is_dispatch, struct blkdev_statistics_info *info);
void blk_mq_debug_dispatch_rq_clear(int is_sync, struct request *req);
void blk_mq_debug_rq_processing_state_update(struct request *rq,
		enum mq_process_enum rq_state);
#else

static inline void blk_mq_debug_update_request_error(void) {}
static inline void blk_mq_debug_rq_timed_out(struct request *req) {}
static inline void blk_mq_debug_statistics_check(struct blkdev_statistics_info *info){}
static inline void blk_mq_debug_write_decision_init(int is_sync,
		struct blk_dispatch_decision_para *p) {}
static inline void blk_mq_debug_write_decision_state_update(
	struct blk_dispatch_decision_para *p, char *debug_log){}
static inline void blk_mq_debug_dispatch_check(int is_sync, struct request_queue *q) {}
static inline void blk_mq_debug_dispatch_rq_record(int is_sync,
		struct blk_dispatch_decision_para *p) {}
static inline void blk_mq_debug_write_decision_end_check(int is_sync,
		struct blk_dispatch_decision_para *p, int is_dispatch,
		struct blkdev_statistics_info *info) {}
static inline void blk_mq_debug_dispatch_rq_clear(int is_sync, struct request *req) {}
static inline void blk_mq_debug_rq_processing_state_update(struct request *rq,
				enum mq_process_enum rq_state){}
#endif /* CONFIG_HISI_MQ_DEBUG */

#endif /* _HISI_BLK_MQ_DEBUG_H_ */
