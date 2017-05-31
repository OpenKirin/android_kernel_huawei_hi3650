#include <linux/bootdevice.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/types.h>
#include <linux/hisi/kirin_partition.h>
#include <linux/uaccess.h>
#include <linux/printk.h>

#define MAX_NAME_LEN 32

struct __bootdevice {
	enum bootdevice_type type;
	const struct device *dev;
	sector_t size;
	u32 cid[4];
	char product_name[MAX_NAME_LEN + 1];
	u8 pre_eol_info;
	u8 life_time_est_typ_a;
	u8 life_time_est_typ_b;
	unsigned int manfid;
	enum AB_PARTITION_TYPE ab_partition_support;
	u8 ptn_index;

	/* UFS only */
	volatile uint64_t rpmb_blk_count;
	/* we use 0x rpmb to indicate a valid value */
#define RPMB_DONE 0x72706D62 /* 'r', 'p', 'm', 'b' */
	volatile uint32_t rpmb_done;
};

#define MAX_PARTITION_NAME_LENGTH       36
struct flash_find_index_user {
	char name[MAX_PARTITION_NAME_LENGTH];
	int index;
};
#define INDEXEACCESSDATA _IOWR('M', 26, struct flash_find_index_user)

static struct semaphore flash_find_index_sem;

static struct __bootdevice bootdevice;

void set_rpmb_blk_count(uint64_t blk_count)
{
	bootdevice.rpmb_blk_count = blk_count;
	bootdevice.rpmb_done = RPMB_DONE;
}

/*lint -save -e516 -e778 -e774*/
int get_rpmb_blk_count(uint64_t *blk_count, int delay_ms)
{
	int i;

	for (i = 0; i < delay_ms; i++) {
		if (bootdevice.rpmb_done == RPMB_DONE) {
			*blk_count = bootdevice.rpmb_blk_count;
			return 0;
		}
		udelay((u64)1000);
	}

	return -ETIMEDOUT;
}
/*lint -restore*/

void set_bootdevice_type(enum bootdevice_type type)
{
	bootdevice.type = type;
}

enum bootdevice_type get_bootdevice_type()
{
	return bootdevice.type;
}

void set_bootdevice_name(struct device *dev)
{
	bootdevice.dev = dev;
}

static int type_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d", bootdevice.type);
	return 0;
}

static int type_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, type_proc_show, NULL);
}

static const struct file_operations type_proc_fops = {
	.open = type_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int name_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s", dev_name(bootdevice.dev));
	return 0;
}

static int name_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, name_proc_show, NULL);
}

static const struct file_operations name_proc_fops = {
	.open = name_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void set_bootdevice_size(sector_t size)
{
	bootdevice.size = size;
}

#if 0
sector_t get_bootdevice_size()
{
	return bootdevice.size;
}
#endif

static int size_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%llu\n", (unsigned long long)bootdevice.size);
	return 0;
}

static int size_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, size_proc_show, NULL);
}

static const struct file_operations size_proc_fops = {
	.open = size_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void set_bootdevice_cid(u32 *cid)
{
	memcpy(bootdevice.cid, cid, sizeof(bootdevice.cid));
}

#if 0
u32* get_bootdevice_cid()
{
	return bootdevice.cid;
}
#endif

static int cid_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%08x%08x%08x%08x\n", bootdevice.cid[0],
		   bootdevice.cid[1], bootdevice.cid[2], bootdevice.cid[3]);

	return 0;
}

static int cid_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cid_proc_show, NULL);
}

static const struct file_operations cid_proc_fops = {
	.open = cid_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void set_bootdevice_product_name(char *product_name, u32 len)
{
	u32 min_len = min_t(uint8_t, len, MAX_NAME_LEN);

	strlcpy(bootdevice.product_name, product_name, min_len);
	bootdevice.product_name[min_len] = '\0';
}

static int product_name_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", bootdevice.product_name);

	return 0;
}

static int product_name_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, product_name_proc_show, NULL);
}

static const struct file_operations product_name_proc_fops = {
	.open		= product_name_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

void set_bootdevice_pre_eol_info(u8 pre_eol_info)
{
	bootdevice.pre_eol_info = pre_eol_info;
}

static int pre_eol_info_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "0x%02X\n", bootdevice.pre_eol_info);

	return 0;
}

static int pre_eol_info_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, pre_eol_info_proc_show, NULL);
}

static const struct file_operations pre_eol_info_proc_fops = {
	.open		= pre_eol_info_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

void set_bootdevice_life_time_est_typ_a(u8 life_time_est_typ_a)
{
	bootdevice.life_time_est_typ_a = life_time_est_typ_a;
}

static int life_time_est_typ_a_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "0x%02X\n", bootdevice.life_time_est_typ_a);

	return 0;
}

static int life_time_est_typ_a_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, life_time_est_typ_a_proc_show, NULL);
}

static const struct file_operations life_time_est_typ_a_proc_fops = {
	.open		= life_time_est_typ_a_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

void set_bootdevice_life_time_est_typ_b(u8 life_time_est_typ_b)
{
	bootdevice.life_time_est_typ_b = life_time_est_typ_b;
}

static int life_time_est_typ_b_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "0x%02X\n", bootdevice.life_time_est_typ_b);

	return 0;
}

static int life_time_est_typ_b_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, life_time_est_typ_b_proc_show, NULL);
}

static const struct file_operations life_time_est_typ_b_proc_fops = {
	.open		= life_time_est_typ_b_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

void set_bootdevice_manfid(unsigned int manfid)
{
	bootdevice.manfid = manfid;
}

unsigned int get_bootdevice_manfid(void)
{
	return bootdevice.manfid;
}

static int manfid_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "0x%06x\n", bootdevice.manfid);

	return 0;
}

static int manfid_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, manfid_proc_show, NULL);
}

static const struct file_operations manfid_proc_fops = {
	.open		= manfid_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

/*lint -save -e715 -e818*/
static int ab_partition_support_proc_show(struct seq_file *m, void *v)
{
	bootdevice.ab_partition_support = get_device_boot_partition_type();

	if (ERROR_VALUE == bootdevice.ab_partition_support) {
		seq_printf(m, "get device boot partition type error\n");
		return -1;
	}

	seq_printf(m, "%d\n", bootdevice.ab_partition_support);

	return 0;
}

static int ab_partition_support_proc_open(struct inode *p_inode, struct file *p_file)
{
	return single_open(p_file, ab_partition_support_proc_show, NULL);
}

static ssize_t ab_partition_support_proc_write(struct file *p_file, const char __user * userbuf, size_t count, loff_t * ppos)/*lint !e40*/
{
/*We have no B partition in Chicago,disable setting B partition*/
#if 0
	char buf;
	char getvalue;
	int ret;


	if (count == 0)
		return -1;

	if(copy_from_user(&buf, userbuf, sizeof(char)))
		return -1;

	getvalue = buf - 48;

	if ((XLOADER_A != getvalue) && (XLOADER_B != getvalue)) {
		pr_err("Input only support 1 or 2, please try again\n");
		return -1;
	}

	ret = set_device_boot_partition_type(getvalue);
	if (ret < 0) {
		pr_err("boot partition type set error\n");
		return -1;
	}
#endif
	return (ssize_t)count;
}

/*lint -save -e785*/
static const struct file_operations ab_partition_support_proc_fops = {
	.open		= ab_partition_support_proc_open,
	.read		= seq_read,
	.write          = ab_partition_support_proc_write,
	.llseek		= seq_lseek,/*lint !e64 !e65*/ 
	.release	= single_release,
};
/*lint -restore*/

static int flash_find_index_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", bootdevice.ptn_index);

	return 0;
}

static int flash_find_index_proc_open(struct inode *p_inode, struct file *p_file)
{
	return single_open(p_file, flash_find_index_proc_show, NULL);
}

#define INDEXEACCESSDATA _IOWR('M', 26, struct flash_find_index_user)

static long flash_find_index_proc_ioctl(struct file *p_file, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	struct flash_find_index_user info;

	/*ensure only one process can visit flash_find_index device at the same time in API*/
	if (down_interruptible(&flash_find_index_sem))
		return -EBUSY;

	switch (cmd) {
		case INDEXEACCESSDATA:/*lint !e835 !e30*/
			if (copy_from_user(&info, argp, sizeof(struct flash_find_index_user))) {
				up(&flash_find_index_sem);
				return -1;
			}
			/* Make sure we will not get a non-terminate string from
			 * user space */
			info.name[MAX_PARTITION_NAME_LENGTH - 1] = '\0';

			info.index = flash_get_ptn_index(info.name);
			if (info.index < 0)
				return -1;

			bootdevice.ptn_index = (unsigned char)info.index;
			break;

		default:
			pr_err("Unknow command!\n");
			up(&flash_find_index_sem);
			return -1;
	}

	up(&flash_find_index_sem);
	return 0;
}

/*lint -save -e785*/
static const struct file_operations flash_find_index_proc_fops = {
	.open		= flash_find_index_proc_open,
	.read		= seq_read,
	.unlocked_ioctl	= flash_find_index_proc_ioctl,
	.compat_ioctl	= flash_find_index_proc_ioctl,
	.llseek		= seq_lseek,/*lint !e64 !e65*/
	.release	= single_release,
};
/*lint -restore*/
/*lint -restore*/

static int __init proc_bootdevice_init(void)
{
	if (!proc_mkdir("bootdevice", NULL)) {
		pr_err("make proc dir bootdevice failed\n");
		return -EFAULT;
	}

	proc_create("bootdevice/type", 0, NULL, &type_proc_fops);
	proc_create("bootdevice/name", 0, NULL, &name_proc_fops);
	proc_create("bootdevice/size", 0, NULL, &size_proc_fops);
	proc_create("bootdevice/cid", 0, NULL, &cid_proc_fops);
	proc_create("bootdevice/product_name", 0, NULL, &product_name_proc_fops);
	proc_create("bootdevice/pre_eol_info", 0, NULL, &pre_eol_info_proc_fops);
	proc_create("bootdevice/life_time_est_typ_a", 0, NULL,
		&life_time_est_typ_a_proc_fops);
	proc_create("bootdevice/life_time_est_typ_b", 0, NULL,
		&life_time_est_typ_b_proc_fops);
	proc_create("bootdevice/manfid", 0, NULL, &manfid_proc_fops);
	proc_create("bootdevice/ab_partition_support", 0660, (struct proc_dir_entry *)NULL, &ab_partition_support_proc_fops);
	sema_init(&flash_find_index_sem, 1);
	proc_create("bootdevice/flash_find_index", 0660, (struct proc_dir_entry *)NULL, &flash_find_index_proc_fops);

	return 0;
}
module_init(proc_bootdevice_init);
