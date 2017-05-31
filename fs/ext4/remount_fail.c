

#include <linux/buffer_head.h>
#include <linux/exportfs.h>
#include <linux/vfs.h>
#include <linux/random.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/quotaops.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/ctype.h>
#include <linux/log2.h>
#include <linux/crc16.h>
#include <linux/cleancache.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/freezer.h>
#include "ext4_dump_info.h"

#include "ext4.h"
#include "ext4_extents.h"	/* Needed for trace points definition */
#include "ext4_jbd2.h"
#include "xattr.h"
#include "acl.h"
#include "mballoc.h"

#include <linux/reboot.h>
#include "../mount.h"

#define USERDATA_MOUNTPOINT "/data"
#define USERDATA_MOUNTPOINT_LEN 5

extern unsigned int get_boot_into_recovery_flag(void);

static int get_datamount_flag(void)
{
	if (strstr(saved_command_line, "normal_reset_type=MountFail"))
		return 1;
	return 0;
}

static int ext4_get_mountpoint(struct super_block *sb)
{
	struct mount *mnt;
	int ret = -1;
	char *path;
	char *p;

	if (unlikely(!sb))
		return -EINVAL;

	path = __getname();
	if (!path)
		return -ENOMEM;

	list_for_each_entry(mnt, &sb->s_mounts, mnt_instance) {
		if (NULL == mnt->mnt_mountpoint)
			continue;
		p = dentry_path_raw(mnt->mnt_mountpoint, path, PATH_MAX);
		if (strncmp(USERDATA_MOUNTPOINT, p,
					USERDATA_MOUNTPOINT_LEN) == 0) {
			ret = 0;
			break;

		}
	}
	__putname(path);

	return ret;
}

void trigger_double_data(struct super_block *sb)
{
#ifndef TARGET_VERSION_FACTORY
	if (get_boot_into_recovery_flag() == 0 && get_datamount_flag() == 0) {
		if (ext4_get_mountpoint(sb) == 0) {
			kernel_restart("mountfail");
		}
	}
#endif
}
