#ifndef __HISI_LOWMEM_DBG_H
#define __HISI_LOWMEM_DBG_H

#ifdef CONFIG_HISI_LOWMEM_DBG

void hisi_lowmem_dbg(short oom_score_adj);
void hisi_lowmem_dbg_timeout(struct task_struct *p, struct task_struct *tsk);

#else

static inline void hisi_lowmem_dbg(short oom_score_adj)
{
}

static inline void hisi_lowmem_dbg_timeout(struct task_struct *p,
					   struct task_struct *leader)
{
}

#endif

#endif /* __HISI_LOWMEM_DBG_H */
