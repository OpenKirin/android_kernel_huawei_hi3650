#ifndef _HISI_BLK_MQ_DISPATCH_STRATEGY_H_
#define _HISI_BLK_MQ_DISPATCH_STRATEGY_H_

#include <linux/blkdev.h>

#ifdef CONFIG_HISI_MQ_DISPATCH_DECISION
static inline void hisi_blk_mq_init_req_timestamp(struct request *req)
{
	req->rq_start_jiffies = 0;
}

static inline void blk_mq_request_summary_copy(struct request *new_rq,
		struct request *orig_rq)
{
	new_rq->q = orig_rq->q;
	new_rq->cmd_type = orig_rq->cmd_type;
	new_rq->cmd_flags = orig_rq->cmd_flags;
	new_rq->rq_start_jiffies = orig_rq->rq_start_jiffies;
	new_rq->req_iosche_bypass = orig_rq->req_iosche_bypass;
#ifdef CONFIG_HISI_MQ_DEBUG
	new_rq->mq_count_type = orig_rq->mq_count_type;
	new_rq->mq_count_num = orig_rq->mq_count_num;
#endif
}

void hisi_blk_mq_dispatch_strategy_init(struct request_queue *q);

void blk_mq_update_statistics(struct request_queue *q, struct request *req);
bool blk_mq_dispatch_busy(struct request_queue *q, struct request *rq);
static inline void hisi_blk_mq_set_rq_start_jiffies(struct request *rq, unsigned long rq_start_jiffies)
{
	rq->rq_start_jiffies = rq_start_jiffies;
}
struct blk_mq_ctx *dispatch_decision(struct request *rq,
			struct blk_mq_ctx *ctx, struct blk_mq_hw_ctx *hctx);


#else /* CONFIG_HISI_MQ_DISPATCH_DECISION */
static inline void hisi_blk_mq_init_req_timestamp(struct request *req) {}
static inline void blk_mq_request_summary_copy(struct request *new_rq,
		struct request *orig_rq) {}
static inline void hisi_blk_mq_dispatch_strategy_init(struct request_queue *q) {}
static inline void blk_mq_update_statistics(struct request_queue *q, struct request *req) {}
static inline bool blk_mq_dispatch_busy(struct request_queue *q, struct request *rq)
{
	return false;
}


static inline void hisi_blk_mq_set_rq_start_jiffies(struct request *rq, unsigned long rq_start_jiffies)
{
}
static inline struct blk_mq_ctx *dispatch_decision(struct request *rq,
		struct blk_mq_ctx *ctx, struct blk_mq_hw_ctx *hctx)
{
	return ctx;
}

#endif /* CONFIG_HISI_MQ_DISPATCH_DECISION */

#endif
