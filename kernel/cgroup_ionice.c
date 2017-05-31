/*
 * cgroup_ionice.c - control group ionice subsystem
 *
 * Copyright Huawei Corparation, 2014
 * Author: Freeman.Yao
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/cgroup.h>
#include <linux/err.h>
#include <linux/ioprio.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

struct cgroup_subsys ionice_cgrp_subsys;
struct ionice_cgroup {
	struct cgroup_subsys_state css;
	int prio;
	spinlock_t lock;
};

static struct ionice_cgroup *cgroup_to_ionice(struct cgroup_subsys_state *css)
{
	return css ? container_of(css, struct ionice_cgroup, css) : NULL;
}

static struct ionice_cgroup *task_to_ionice(struct task_struct *task)
{
	return container_of(task_css(task, ionice_cgrp_id),
		struct ionice_cgroup, css);
}

static struct cgroup_subsys_state *ionice_alloc(struct cgroup_subsys_state
		*parent_css)
{
	struct ionice_cgroup *ionice_cgroup;

	ionice_cgroup = kzalloc(sizeof(*ionice_cgroup), GFP_KERNEL);
	if (!ionice_cgroup)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&ionice_cgroup->lock);

	return &ionice_cgroup->css;
}

static void ionice_free(struct cgroup_subsys_state *css)
{
	kfree(cgroup_to_ionice(css));
}

static s64 ionice_read_prio(struct cgroup_subsys_state *css, struct cftype *cft)
{
	return (s64)cgroup_to_ionice(css)->prio;
}

static void ionice_apply_prio(struct cgroup_subsys_state *css,
		struct ionice_cgroup *ionice, int prio)
{
	struct css_task_iter it;
	struct task_struct *task;

	/*we don't want to set root group ionice*/
	if (!css->parent)
		return;

	/* also synchronizes against task migration, see ionice_attach() */
	lockdep_assert_held(&ionice->lock);

	rcu_read_lock();
	css_task_iter_start(css, &it);
	while ((task = css_task_iter_next(&it)))
		set_task_ioprio(task, prio);
	css_task_iter_end(&it);
	rcu_read_unlock();
}

static int ionice_write_prio(struct cgroup_subsys_state *css,
		struct cftype *cft, s64 val)
{
	int prio = (int)val;
	int class = IOPRIO_PRIO_CLASS(prio);
	int data = IOPRIO_PRIO_DATA(prio);
	struct ionice_cgroup *ionice = cgroup_to_ionice(css);

	switch (class) {
	case IOPRIO_CLASS_RT:
	/* fall through, rt has prio field too */
	case IOPRIO_CLASS_BE:
		if (data >= IOPRIO_BE_NR || data < 0)
			return -EINVAL;
		break;
	case IOPRIO_CLASS_IDLE:
		break;
	case IOPRIO_CLASS_NONE:
		if (data)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	spin_lock_irq(&ionice->lock);
	ionice_apply_prio(css, ionice, prio);
	ionice->prio = prio;
	spin_unlock_irq(&ionice->lock);

	return 0;
}

static const char *ionice_class_strs(int class)
{
	switch (class) {
	case IOPRIO_CLASS_NONE:
		return "none";
	case IOPRIO_CLASS_IDLE:
		return "idle";
	case IOPRIO_CLASS_RT:
		return "rt(real time)";
	case IOPRIO_CLASS_BE:
		return "be(best effort)";
	default:
		return "error";
	}
}

static int ionice_read_class(struct seq_file *m, void *V)
{
	int prio;
	int class;
	const char *str;
	struct cgroup_subsys_state *css = seq_css(m);

	rcu_read_lock();
	prio = (int)ionice_read_prio(css, NULL);
	rcu_read_unlock();

	class = IOPRIO_PRIO_CLASS(prio);
	str   = ionice_class_strs(class);
	seq_puts(m, str);
	seq_putc(m, '\n');
	return 0;
}

static s64 ionice_read_level(struct cgroup_subsys_state *css,
		struct cftype *cft)
{
	int prio;

	rcu_read_lock();
	prio = (int)ionice_read_prio(css, cft);
	rcu_read_unlock();

	return (s64)IOPRIO_PRIO_DATA(prio);
}

static void ionice_attach(struct cgroup_subsys_state *css,
		struct cgroup_taskset *tset)
{
	struct ionice_cgroup *ionice = cgroup_to_ionice(css);
	struct task_struct *task;

	/*we don't want to set root group ionice*/
	if (!css->parent)
		return;

	spin_lock_irq(&ionice->lock);
	cgroup_taskset_for_each(task, tset) {
		set_task_ioprio(task, ionice->prio);
	}
	spin_unlock_irq(&ionice->lock);
}

static int ionice_allow_attach(struct cgroup_subsys_state *css,
		struct cgroup_taskset *tset)
{
	return subsys_cgroup_allow_attach(css, tset);
}

static void ionice_fork(struct task_struct *task)
{
	struct ionice_cgroup *ionice = task_to_ionice(task);

	/*we don't want to set root group ionice*/
	if (task_css_is_root(task, ionice_cgrp_id))
		return;

	rcu_read_lock();
	set_task_ioprio(task, ionice->prio);
	rcu_read_unlock();
}

static struct cftype files[] = {
	{
		.name = "class",
		.mode = S_IRUGO,
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = ionice_read_class,
	},
	{
		.name = "level",
		.mode = S_IRUGO,
		.flags = CFTYPE_NOT_ON_ROOT,
		.read_s64 = ionice_read_level,
	},
	{
		.name = "prio",
		.mode = S_IWUSR|S_IWGRP|S_IRUSR|S_IRGRP,
		.flags = CFTYPE_NOT_ON_ROOT,
		.read_s64 = ionice_read_prio,
		.write_s64 = ionice_write_prio,
	},
	{ }    /* terminate */
};

struct cgroup_subsys ionice_cgrp_subsys = {
	.css_alloc        = ionice_alloc,
	.css_free    = ionice_free,
	.attach        = ionice_attach,
	.allow_attach = ionice_allow_attach,
	.fork        = ionice_fork,
	.legacy_cftypes    = files,
};
