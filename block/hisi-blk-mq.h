#ifndef _INTERNAL_HISI_BLK_MQ_H_
#define _INTERNAL_HISI_BLK_MQ_H_

#include <linux/blkdev.h>
#include <linux/hisi-blk-mq.h>

#ifdef CONFIG_HISI_BLK_MQ

#define MQ_MERGE_MAX_SIZE 0x40000

extern void blk_mq_flush_device_cache(int emergency);

static inline void blk_request_queue_disk_register(struct gendisk *disk,struct request_queue *q)
{
	q->request_queue_disk = disk;
}
static void blk_mq_flush_work_fn(struct work_struct* work)
{
	struct request_queue *q = container_of(work, struct request_queue, flush_work.work);/*lint !e826*/
	q->mq_ops->direct_flush(q,1);
	atomic_set(&q->flush_work_trigger, 0);
}

static inline bool flush_insert(struct request_queue *q, struct bio *bio)
{
	if((bio->bi_rw & REQ_FLUSH)&&(bio->bi_iter.bi_size == 0)){
		if(bio->bi_async_flush == 1 && hisi_blk_mq_test_queue_quirk(q, HISI_MQ_FLUSH_REDUCING) && q->mq_ops->direct_flush){
			if(atomic_read(&q->flush_work_trigger) == 0){
				kblockd_schedule_delayed_work(&q->flush_work,0);
				atomic_set(&q->flush_work_trigger, 1);
			}
			else if(kblockd_schedule_delayed_work_cancel(&q->flush_work)){
				kblockd_schedule_delayed_work(&q->flush_work,0);
			}
			return false;
		}
		if(atomic_read(&q->wio_after_flush_fua) == 0)
			return false;
	}
	return true;
}

static inline void flush_reducing_stats_update(struct request_queue *q,
		struct request *rq, struct request *processing_rq)
{
	if (processing_rq->cmd_flags & REQ_FLUSH) {
		atomic_set(&q->wio_after_flush_fua, 0);
	} else if ((processing_rq->cmd_type == REQ_TYPE_FS)
			   && (processing_rq->cmd_flags & REQ_WRITE) && rq->__data_len
			   && (atomic_read(&q->wio_after_flush_fua) == 0)) {
		atomic_set(&q->wio_after_flush_fua, 1);
	}
}

static inline void hisi_blk_mq_init(struct request_queue *q)
{
	INIT_DELAYED_WORK(&q->flush_work, blk_mq_flush_work_fn);
	atomic_set(&q->flush_work_trigger, 0);
	atomic_set(&q->wio_after_flush_fua,0);
}

#else /* CONFIG_HISI_BLK_MQ */

static inline void blk_mq_flush_device_cache(int emergency){}

static inline void blk_request_queue_disk_register(struct gendisk *disk,struct request_queue *q){}

static inline void hisi_blk_mq_init(struct request_queue *q){}

static inline bool flush_insert(struct request_queue *q, struct bio *bio)
{
	return true;
}

static inline void flush_reducing_stats_update(struct request_queue *q,
		struct request *rq, struct request *processing_rq) {}

#endif /* CONFIG_HISI_BLK_MQ */

#endif /* _INTERNAL_HISI_BLK_MQ_H_ */
