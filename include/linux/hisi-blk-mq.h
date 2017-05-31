#ifndef _HISI_BLK_MQ_H_
#define _HISI_BLK_MQ_H_

#include <linux/blkdev.h>

struct blkdev_statistics_info{
	int blkdev_processing_read;
	int blkdev_processing_write;
	int blkdev_continue_read;
	int blkdev_continue_sync_io;
	int blkdev_continue_sync_write;
	int blkdev_continue_async_write;
	int blkdev_continue_idle;
};

/*
 * struct for multiqueue dispatch decision function
 */
struct blk_dispatch_decision_para{
	struct request_queue *queue;
	unsigned long rq_start_jiffies;
	union{
		struct bio *bio;
		struct request *req;
	};
#ifdef CONFIG_HISI_MQ_DEBUG
	int write_dispatch_num_before_decision;
	char* write_dispatch_debug_log;
#endif
};

enum {
	HISI_MQ_FORCE_DISPATCH_CTX	= 0,
	HISI_MQ_FORCE_SOFTIRQ	,
	HISI_MQ_FLUSH_REDUCING,
	HISI_MQ_DISPATCH_DICISION	,
};

#ifdef CONFIG_HISI_BLK_MQ
static inline void hisi_blk_mq_set_queue_quirk(struct request_queue *q,
						int quirks)
{
	if (q)
		__set_bit(quirks, &q->hisi_blk_mq_quirk_flags);
}

static inline bool hisi_blk_mq_test_queue_quirk(struct request_queue *q,
						int quirks)
{
	if (q)
		return test_bit(quirks, &q->hisi_blk_mq_quirk_flags);
	return false;
}

static inline void hisi_blk_mq_clear_queue_quirk(struct request_queue *q)
{
	if (q)
		q->hisi_blk_mq_quirk_flags = 0;
}
#else
static inline void hisi_blk_mq_set_queue_quirk(struct request_queue *q,
						int quirks){}
static inline bool hisi_blk_mq_test_queue_quirk(struct request_queue *q,
						int quirks)
{
	return false;
}
static inline void hisi_blk_mq_clear_queue_quirk(struct request_queue *q){}
#endif /* CONFIG_HISI_BLK_MQ */

#endif /* _HISI_BLK_MQ_H_ */
