/* drivers/misc/pid_cputime.c
 *
 * Copyright (C) 2016 Huawei Device Co.,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/err.h>
#include <linux/hashtable.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/profile.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>

#include <huawei_platform/power/bdat/bdat.h>
#include <huawei_platform/power/bdat/bdat_common.h>
#include <huawei_platform/log/hwlog_kernel.h>

#define PID_HASH_BITS			10
#define UID_ROOT				0
#define MAX_BUFFER_SIZE			1024
#define KTHREAD					"kernel"

struct pid_entry {
	pid_t pid;
	uid_t uid;
	cputime_t utime;
	cputime_t stime;
	cputime_t active_utime;
	cputime_t active_stime;
	bool alive;
	char name[NAME_SIZE];
	struct hlist_node hash;
};

static DECLARE_HASHTABLE(pid_hash_table, PID_HASH_BITS);
static DEFINE_MUTEX(pid_lock);

/*
 * Access another process' address space as given in mm.  If non-NULL, use the
 * given task for page fault accounting.
 */
static int bdat_access_remote_vm(struct task_struct *tsk, struct mm_struct *mm,
		unsigned long addr, void *buf, int len, int write)
{
	struct vm_area_struct *vma;
	void *old_buf = buf;
	int res;

	res = down_read_trylock(&mm->mmap_sem);
	if (res <= 0)
		return res;

	/* ignore errors, just check how much was successfully transferred */
	while (len) {
		int bytes, ret, offset;
		void *maddr;
		struct page *page = NULL;

		ret = get_user_pages(tsk, mm, addr, 1,
				write, 1, &page, &vma);
		if (ret <= 0) {
#ifndef CONFIG_HAVE_IOREMAP_PROT
			break;
#else
			/*
			 * Check if this is a VM_IO | VM_PFNMAP VMA, which
			 * we can access using slightly different code.
			 */
			vma = find_vma(mm, addr);
			if (!vma || vma->vm_start > addr)
				break;
			if (vma->vm_ops && vma->vm_ops->access)
				ret = vma->vm_ops->access(vma, addr, buf,
							  len, write);
			if (ret <= 0)
				break;
			bytes = ret;
#endif
		} else {
			bytes = len;
			offset = addr & (PAGE_SIZE-1);
			if (bytes > PAGE_SIZE-offset)
				bytes = PAGE_SIZE-offset;

			maddr = kmap(page);
			if (write) {
				copy_to_user_page(vma, page, addr,
						  maddr + offset, buf, bytes);
				set_page_dirty_lock(page);
			} else {
				copy_from_user_page(vma, page, addr,
						    buf, maddr + offset, bytes);
			}
			kunmap(page);
			page_cache_release(page);
		}
		len -= bytes;
		buf += bytes;
		addr += bytes;
	}
	up_read(&mm->mmap_sem);

	return buf - old_buf;
}

/*
 * Access another process' address space.
 * Source/target buffer must be kernel space,
 * Do not walk the page table directly, use get_user_pages
 */
static int bdat_access_process_vm(struct task_struct *tsk, unsigned long addr,
		void *buf, int len, int write)
{
	struct mm_struct *mm;
	int ret;

	mm = get_task_mm(tsk);
	if (!mm)
		return 0;

	ret = bdat_access_remote_vm(tsk, mm, addr, buf, len, write);
	mmput(mm);

	return ret;
}

/*
 * Function name: get_pid_cmdline
 * Description: get pid cmdline name
 * Input: struct task_struct *task, task struct
 *        char *buffer, cmdline name buffer
 * Output: none
 * Return: 0, failed
 *         >0, success
 * Date: 2016/03/09
 * Author: Pengyu  ID: 00188486
 */
static int get_pid_cmdline(struct task_struct *task, char *buffer)
{
	int res = 0;
	unsigned int len;
	struct mm_struct *mm = get_task_mm(task);

	if (!mm)
		goto out;
	if (!mm->arg_end)
		goto out_mm;	/* Shh! No looking before we're done */

	len = mm->arg_end - mm->arg_start;

	if (len > PAGE_SIZE)
		len = PAGE_SIZE;

	res = bdat_access_process_vm(task, mm->arg_start, buffer, len, 0);

	/*
	 * If the nul at the end of args has been overwritten, then
	 * assume application is using setproctitle(3).
	 */
	if (res > 0 && buffer[res-1] != '\0' && len < PAGE_SIZE) {
		len = strnlen(buffer, res);
		if (len < res) {
			res = len;
		} else {
			len = mm->env_end - mm->env_start;
			if (len > PAGE_SIZE - res)
				len = PAGE_SIZE - res;
			res += bdat_access_process_vm(task,
				mm->env_start, buffer+res, len, 0);
			res = strnlen(buffer, res);
		}
	}

out_mm:
	mmput(mm);
out:
	return res;
}

/*
 * Function name: find_pid_entry
 * Description: find pid entry
 * Input: pid_t pid, process identifier
 * Output: none
 * Return: struct pid_entry, pid entry
 *         NULL, failed
 * Date: 2016/03/21
 * Author: Pengyu  ID: 00188486
 */
static struct pid_entry *find_pid_entry(pid_t pid)
{
	struct pid_entry *pid_entry;

	hash_for_each_possible(pid_hash_table, pid_entry, hash, pid) {
		if (pid_entry->pid == pid)
			return pid_entry;
	}

	return NULL;
}

/*
 * Function name: find_or_register_pid
 * Description: find or register pid
 * Input: struct task_struct *task, task pointer
 * Output: none
 * Return: struct pid_entry, pid entry
 *         NULL, failed
 * Date: 2016/03/21
 * Author: Pengyu  ID: 00188486
 */
static struct pid_entry *find_or_register_pid(
		struct task_struct *task, uid_t uid)
{
	struct pid_entry *pid_entry = NULL;
	char *buffer = NULL;
	pid_t pid = task->tgid;
	int has_cmd = 0;

	/* combine kernel thread to same pid_entry which pid is 0 */
	if (task->flags & PF_KTHREAD)
		pid = 0;

	pid_entry = find_pid_entry(pid);
	if (pid_entry != NULL)
		return pid_entry;

	buffer = kzalloc(PAGE_SIZE, GFP_ATOMIC);
	if (buffer == NULL) {
		BDAT_LOGE("Failed to alloc buffer");
		return NULL;
	}

	if (pid == 0) {
		strncpy(buffer, KTHREAD, NAME_SIZE);
	} else {
		has_cmd = get_pid_cmdline(task, buffer);
		if (has_cmd == 0)
			strncpy(buffer, task->comm, NAME_SIZE);
	}

	pid_entry = kzalloc(sizeof(struct pid_entry), GFP_ATOMIC);
	if (pid_entry == NULL) {
		BDAT_LOGE("Failed to alloc pid entry");
		kfree(buffer);
		return NULL;
	}
	pid_entry->pid = pid;
	pid_entry->uid = uid;
	pid_entry->alive = true;
	strncpy(pid_entry->name, buffer, NAME_SIZE);
	pid_entry->name[NAME_SIZE - 1] = '\0';
	hash_add(pid_hash_table, &pid_entry->hash, pid);
	kfree(buffer);

	return pid_entry;
}

/*
 * Function name: bdat_cputime_to_usecs
 * Description: convert cputime to microseconds
 * Input: cputime_t time
 * Output: none
 * Return: unsigned long long microseconds
 * Date: 2016/09/16
 * Author: Songzili  ID: 00349876
 */
static unsigned long long bdat_cputime_to_usecs(cputime_t time)
{
	return ((unsigned long long)
		jiffies_to_msecs(cputime_to_jiffies(time)) * USEC_PER_MSEC);
}

/*
 * Function name: bdat_update_pid_cputime
 * Description: update process cputime
 * Input: none
 * Output: none
 * Return: length pid stat length
 * Date: 2016/04/16
 * Author: Songzili  ID: 00349876
 */
int bdat_update_pid_cputime(void)
{
	struct pid_entry *pid_entry;
	struct task_struct *task, *temp, *leader;
	struct hlist_node *tmp;
	cputime_t utime;
	cputime_t stime;
	unsigned long bkt;
	uid_t uid;
	int length = 0;

	mutex_lock(&pid_lock);
	/*
	 * initialize hash list
	 * report dead process and delete hash node
	 */
	hash_for_each_safe(pid_hash_table, bkt, tmp, pid_entry, hash) {
		if (!pid_entry->alive) {
			HWBDAT_LOGE("BDAT_TAG_PROCESS_EXIT",
				"uid=%d pid=%d utime=%llu stime=%llu name=%s",
				pid_entry->uid, pid_entry->pid,
				bdat_cputime_to_usecs(pid_entry->utime),
				bdat_cputime_to_usecs(pid_entry->stime),
				pid_entry->name);
			hash_del(&pid_entry->hash);
			kfree(pid_entry);
			continue;
		}
		pid_entry->active_stime = 0;
		pid_entry->active_utime = 0;
	}

	rcu_read_lock();
	/* update active time from alive task */
	do_each_thread(temp, task) {
		leader = task->group_leader;
		if (leader != NULL && leader->state == TASK_DEAD)
			continue;

		uid = from_kuid_munged(current_user_ns(), task_uid(task));
		pid_entry = find_or_register_pid(task, uid);
		if (pid_entry == NULL) {
			rcu_read_unlock();
			mutex_unlock(&pid_lock);
			BDAT_LOGE("Failed to find the pid_entry for pid %d\n",
				task->tgid);
			return -ENOMEM;
		}
		task_cputime_adjusted(task, &utime, &stime);
		pid_entry->active_utime += utime;
		pid_entry->active_stime += stime;
	} while_each_thread(temp, task);

	/* get active process list length */
	hash_for_each(pid_hash_table, bkt, pid_entry, hash)
		++length;

	rcu_read_unlock();
	mutex_unlock(&pid_lock);

	return length;
}

/*
 * Function name: bdat_get_pid_cputime
 * Description: update process cputime
 * Input: int size, buffer size
 * Output: char *buf, buffer
 * Return: none
 * Date: 2016/04/16
 * Author: Songzili  ID: 00349876
 */
int bdat_get_pid_cputime(int length, char *buf)
{
	unsigned long bkt;
	char *p = buf;
	int count = 0;
	struct pid_entry *pid_entry = NULL;
	struct pid_cputime stat;

	mutex_lock(&pid_lock);
	if (p == NULL) {
		BDAT_LOGE("Invalid parameter\n");
		goto exit;
	}

	hash_for_each(pid_hash_table, bkt, pid_entry, hash) {
		cputime_t total_utime;
		cputime_t total_stime;

		if (++count > length) {
			BDAT_LOGE("Buffer is full\n");
			goto exit;
		}

		total_utime = pid_entry->utime + pid_entry->active_utime;
		total_stime = pid_entry->stime + pid_entry->active_stime;

		memset(&stat, 0, sizeof(struct pid_cputime));
		stat.uid = pid_entry->uid;
		stat.pid = pid_entry->pid;
		stat.utime = bdat_cputime_to_usecs(total_utime);
		stat.stime = bdat_cputime_to_usecs(total_stime);
		memcpy(stat.name, pid_entry->name, NAME_SIZE);

		memcpy(p, &stat, sizeof(struct pid_cputime));
		p += sizeof(struct pid_cputime);
	}

exit:
	mutex_unlock(&pid_lock);
	return 0;
}

/*
 * Function name: process_notifier
 * Description: process notifier
 * Input: struct notifier_block *self, notifier block
 *        unsigned long cmd, command
 *        void *v, data
 * Output: none
 * Return: none
 * Date: 2016/03/21
 * Author: Pengyu  ID: 00188486
 */
static int process_notifier(struct notifier_block *self,
		unsigned long cmd, void *v)
{
	struct task_struct *task = v;
	struct pid_entry *pid_entry;
	cputime_t utime, stime;
	pid_t pid = task->tgid;

	if (task == NULL)
		return NOTIFY_OK;

	mutex_lock(&pid_lock);

	if (task->flags & PF_KTHREAD)
		pid = 0;

	pid_entry = find_pid_entry(pid);
	if (pid_entry == NULL)
		goto exit;

	task_cputime_adjusted(task, &utime, &stime);
	pid_entry->utime += utime;
	pid_entry->stime += stime;

	/* pid has died */
	if (pid_entry->pid == task->pid)
		pid_entry->alive = false;

exit:
	mutex_unlock(&pid_lock);
	return NOTIFY_OK;
}

static struct notifier_block process_notifier_block = {
	.notifier_call	= process_notifier,
};

/*
 * Function name: bdat_pid_cputime_init
 * Description: pid cputime initialize
 * Input: none
 * Output: none
 * Return: none
 * Date: 2016/04/16
 * Author: Songzili  ID: 00349876
 */
int bdat_pid_cputime_init(void)
{
	hash_init(pid_hash_table);
	profile_event_register(PROFILE_TASK_EXIT, &process_notifier_block);

	return 0;
}

/*
 * Function name: bdat_pid_cputime_exit
 * Description: pid cputime exit
 * Input: none
 * Output: none
 * Return: none
 * Date: 2016/04/16
 * Author: Songzili  ID: 00349876
 */
void bdat_pid_cputime_exit(void)
{
	struct pid_entry *pid_entry = NULL;
	struct hlist_node *tmp;
	unsigned long bkt;

	mutex_lock(&pid_lock);
	hash_for_each_safe(pid_hash_table, bkt, tmp, pid_entry, hash) {
		hash_del(&pid_entry->hash);
		kfree(pid_entry);
	}
	profile_event_unregister(PROFILE_TASK_EXIT, &process_notifier_block);

	mutex_unlock(&pid_lock);
}
