

#include <linux/clk-provider.h>
#include <linux/clk/clk-conf.h>
#include <linux/debugfs.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include "clk.h"
#include "hisi-clk-debug.h"
#ifdef CONFIG_HISI_CLK_TRACE
#include <linux/hisi/util.h>
#include <linux/hisi/rdr_hisi_ap_ringbuffer.h>
#include <linux/hisi/rdr_pub.h>
#include <soc_pmctrl_interface.h>
#include <linux/of_address.h>
#endif

#define CLK_INPUT_MAX_NUM 100

#ifdef CONFIG_HISI_CLK_TRACE
#define CLK_NAME_LEN   32
#define CLK_MAGIC_NUM  0x20160322
#define CLK_ERR_NUM     0xFF
/*lint -e750 -esym(750,*) */
#define CLK_DVFS_ADDR_0(Base)  SOC_PMCTRL_PERI_CTRL4_ADDR(Base)
#define CLK_DVFS_ADDR_1(Base)  SOC_PMCTRL_PERI_CTRL5_ADDR(Base)
/*lint -e750 +esym(750,*) */

typedef enum {
	TRACK_ON_OFF = 0,
	TRACK_SET_FREQ,
	TRACK_SET_DVFS,
	TRACK_CLK_MAX
} track_clk_type;

typedef enum {
	SWITCH_CLOSE = 0,
	SWITCH_OPEN,
	SWITCH_MAX
} himntn_trace_switch;

typedef struct {
	unsigned int    dump_magic;
	unsigned int    buffer_size;
	unsigned char  *buffer_addr;
	unsigned char  *percpu_addr[NR_CPUS];
	unsigned int    percpu_length[NR_CPUS];
} pc_record_info;

typedef struct {
	u64   current_time;
	u16   item;
	u16   enable_count;
	u32   current_rate;
	u32   cpu_l;
	u32   cpu_b;
	u32   ppll;
	u32   ddr_freq;
	u32   peri_dvfs_vote0;
	u32   peri_dvfs_vote1 ;
	char  comm[CLK_NAME_LEN];
} clk_record_info;

typedef struct {
	void __iomem   *pmuctrl;
	struct clk     *clk_cpu_l;
	struct clk     *clk_cpu_b;
	struct clk     *clk_ddr;
} hs_trace_clk_info;

typedef enum {
	SINGLE_BUFF = 0,
	MULTI_BUFF,
} buf_type_en;


static u64 clk_rdr_core_id = RDR_CLK;
static pc_record_info *g_clk_track_addr;
static unsigned char g_clk_hook_on;
static buf_type_en  clk_sel_buf_type = MULTI_BUFF;
static hs_trace_clk_info hs_trace_info;

extern int __clk_get_source(struct clk *clk);
#endif

extern struct list_head clocks;

static struct dentry *clock;
static struct dentry *test_all_clocks;
static struct dentry *test_one_clock;

static DEFINE_MUTEX(clock_list_lock);

#define to_clk_gate(_hw) container_of(_hw, struct clk_gate, hw)
#define to_clk_mux(_hw) container_of(_hw, struct clk_mux, hw)

extern bool clk_core_is_enabled(struct clk_core *clk);
extern unsigned long clk_core_get_rate(struct clk_core *clk);


static char g_clk_status[4][10] = {"NOREG", "OK", "ERR", "NULL"};
struct clk_core *__clk_core_get_parent(struct clk_core *clk)
{
	if (!clk)
		return NULL;

	/* TODO: Create a per-user clk and change callers to call clk_put */
	return !clk->parent ? NULL : clk->parent;
}

const char *__clk_core_get_name(struct clk_core *clk)
{
	return !clk ? NULL : clk->name;
}

unsigned int __clk_core_get_enable_count(struct clk_core *clk)
{
	return !clk ? 0 : clk->enable_count;
}

char *clk_enreg_check(struct clk_core *c)
{
	int val = 0;

	if (IS_ERR(c))
		return g_clk_status[2];

	if (!c->ops->is_enabled)
		return g_clk_status[0];

	val = c->ops->is_enabled(c->hw);

	if (val == 2)
		return g_clk_status[0];

	if ((val && c->enable_count) || ((val == 0) && (c->enable_count == 0)))
		return g_clk_status[1];
	else
		return g_clk_status[2];
}

char *clk_selreg_check(struct clk_core *c)
{
	int val = 0;

	if (IS_ERR(c))
		return g_clk_status[2];

	if (!c->ops->check_selreg) {
		return g_clk_status[0];
	}

	val = c->ops->check_selreg(c->hw);

	if (3 == val) {
		return g_clk_status[3];
	}

	return val ? g_clk_status[1] : g_clk_status[2];
}

char *clk_divreg_check(struct clk_core *c)
{
	int val = 0;

	if (IS_ERR(c))
		return g_clk_status[2];

	if (!c->ops->check_divreg)
		return g_clk_status[0];

	val = c->ops->check_divreg(c->hw);

	return val ? g_clk_status[1] : g_clk_status[2];
}

int clock_get_show(struct seq_file *s, void *data)
{
	struct clk_core *clk, *clock;
	struct clk *clock_get;
	const char *status = NULL;

	seq_printf(s, "%18s%-3s%5s%-3s%10s\n", "clock", "", "status", "", "rate");
	seq_printf(s, "---------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	/* Output all clocks in the clocks list, test clk_get() interface.*/
	list_for_each_entry(clk, &clocks, node) {
		if (!clk)
			goto out;

		clock_get = clk_get(NULL, clk->name);
		if (IS_ERR(clock_get)) {
			pr_err("%s clock_get failed!\n", clk->name);
			continue;
		}
		clock = clock_get->core;
		if (!clock) {
			pr_err("%s get failed!\n", clk->name);
			continue;
		}

		if (clock->enable_count)
			status = "on";
		else
			status = "off";

		seq_printf(s, "%18s%-3s%5s%-3s%10ld\n", clock->name, "", status, "", clock->rate);
	}
out:
	mutex_unlock(&clock_list_lock);
	return 0;
}

int clock_lookup_show(struct seq_file *s, void *data)
{
	struct clk_core *clk, *clock;
	struct clk *clock_get;
	const char *status = NULL;

	seq_printf(s, "%14s%-3s%5s%-3s%10s\n", "clock", "", "status", "", "rate");
	seq_printf(s, "---------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	/* Output all clocks in the clocks list, test __clk_lookup() interface.*/
	list_for_each_entry(clk, &clocks, node) {
		if (!clk)
			goto out;

		clock_get = __clk_lookup(clk->name);
		if (!clock_get) {
			pr_err("%s clock_get failed!\n", clk->name);
			goto out;
		}
		clock = clock_get->core;
		if (!clock) {
			pr_err("%s get failed!\n", clk->name);
			goto out;
		}

		if (clock->enable_count)
			status = "on";
		else
			status = "off";

		seq_printf(s, "%20s%-3s%5s%-3s%10ld\n", clock->name, "", status, "", clock->rate);
	}
out:
	mutex_unlock(&clock_list_lock);
	return 0;
}

int clock_enable_show(struct seq_file *s, void *data)
{
	struct clk_core *clk;
	int ret = 0;

	printk("%20s%-3s%5s%-3s%5s\n", "clock", "", "refcnt_pre", "", "refcnt_now");
	printk("---------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	/* Output all clocks in the clocks list, test clk_enable() interface.*/
	list_for_each_entry(clk, &clocks, node) {
		if (!clk->ops->enable)
			continue;

		printk("%20s%-3s%5d", clk->name, "", clk->enable_count);

		ret = clk_prepare_enable(clk->hw->clk);
		if (ret) {
			pr_err("%s enable failed!\n", clk->name);
			goto out;
		}

		printk("%-3s%5d\n", "", clk->enable_count);
	}
out:
	mutex_unlock(&clock_list_lock);
	return ret;
}

int clock_disable_show(struct seq_file *s, void *data)
{
	struct clk_core *clk;

	printk("%20s%-3s%5s%-3s%5s\n", "clock", "", "refcnt_pre", "", "refcnt_now");
	printk("---------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	/* Output all clocks in the clocks list, test clk_disable() interface.*/
	list_for_each_entry(clk, &clocks, node) {
		if (!clk->ops->enable)
			continue;

		printk("%20s%-3s%5d", clk->name, "", clk->enable_count);

		clk_disable_unprepare(clk->hw->clk);

		printk("%-3s%5d\n", "", clk->enable_count);
	}

	mutex_unlock(&clock_list_lock);
	return 0;
}

int clock_getparent_show(struct seq_file *s, void *data)
{
	struct clk_core *clk;
	int i;

	seq_printf(s, "%20s%-5s%8s\n", "clock", "", "parent");
	seq_printf(s, "---------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	/* Output all clocks in the clocks list, test clk_get_parent() interface.*/
	list_for_each_entry(clk, &clocks, node) {
		if (clk->num_parents == 0)
			seq_printf(s, "%20s%-5s%8s\n", clk->name, "", "");
		else {
			seq_printf(s, "%20s", clk->name);

			for (i = 0; i < clk->num_parents; i++)
				seq_printf(s, "%-5s%20s", "", clk->parent_names[i]);

			seq_printf(s, "\n");
		}
	}
	mutex_unlock(&clock_list_lock);
	return 0;
}

int clock_getrate_show(struct seq_file *s, void *data)
{
	struct clk_core *clk;

	seq_printf(s, "%20s%-5s%10s\n", "clock", "", "rate");
	seq_printf(s, "---------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	/* Output all clocks in the clocks list, test clk_get_rate() interface.*/
	list_for_each_entry(clk, &clocks, node)
		seq_printf(s, "%20s%-5s%10ld\n", clk->name, "", clk->rate);

	mutex_unlock(&clock_list_lock);

	return 0;
}

int clock_tree_show(struct seq_file *s, void *data)
{
	struct clk_core *clk;
	struct clk_core *parent;
	const char *state = NULL;
	const char *pstate = NULL;

	/* Output gating clock and fixed rate clock in the clocks list */
	seq_printf(s, "%17s%-6s%4s%-2s%6s%-2s%6s%-2s%6s%-s%7s%-2s%5s%-s%16s%-2s%4s%-2s%5s%-3s%5s\n",
		"clock", "", "status", "", "enreg", "", "selreg", "", "divreg", "", "refcnt", "", "rate",
		"", "parent", "", "status", "", "refcnt", "", "rate");
	seq_printf(s, "--------------------------------------------------------------------------------------------------\n\n");

	mutex_lock(&clock_list_lock);

	list_for_each_entry(clk, &clocks, node) {
		if (clk_core_is_enabled(clk))
			state = "on";
		else
			state = "off";

		if (clk->ops->check_divreg || clk->ops->check_selreg || clk->ops->round_rate)
			continue;

		parent = __clk_core_get_parent(clk);
		if (NULL == parent)
			seq_printf(s, "%18s%-2s%4s%-2s%6s%-2s%6s%-2s%6s%-2s%3d%-2s%10ld%-s%18s%-2s%4s%-2s%3s%-3s%5s%-s%15s\n",
			__clk_core_get_name(clk), "", state, "", clk_enreg_check(clk), "",
			clk_selreg_check(clk), "", clk_divreg_check(clk), "", __clk_core_get_enable_count(clk), "",
			clk_core_get_rate(clk), "", "", "", "", "", "", "", "", "", "");
		else {
			/*judge register status of this parent clock .*/
			if (clk_core_is_enabled(parent))
				pstate = "on";
			else
				pstate = "off";

			seq_printf(s, "%18s%-2s%4s%-2s%6s%-2s%6s%-2s%6s%-2s%3d%-2s%10ld%-s%18s%-2s%4s%-2s%3d%-3s%10ld\n",
			__clk_core_get_name(clk), "", state, "", clk_enreg_check(clk), "", clk_selreg_check(clk),
			"", clk_divreg_check(clk), "", __clk_core_get_enable_count(clk), "",
			clk_core_get_rate(clk), "", __clk_core_get_name(parent), "", pstate, "",
			__clk_core_get_enable_count(parent), "", clk_core_get_rate(parent));
		}
	}

	/* Output multiplexer clock in the clocks list */
	seq_printf(s, "-----------------------------------------------------------------------------------------------------------------------\n");
	seq_printf(s, "-----------------------------------------------------[mux clock]--------------------------------------------------------\n");
	seq_printf(s, "-------------------------------------------------------------------------------------------------------------------------\n");

	seq_printf(s, "%17s%-6s%4s%-2s%6s%-2s%6s%-2s%6s%-s%7s%-2s%5s%-s%16s%-2s%4s%-2s%5s%-3s%5s\n",
		"clock", "", "status", "", "enreg", "", "selreg", "", "divreg", "", "refcnt", "", "rate",
		"", "parent", "", "status", "", "refcnt", "", "rate");
	seq_printf(s, "--------------------------------------------------------------------------------------------------------\n\n");

	list_for_each_entry(clk, &clocks, node) {
		if (clk_core_is_enabled(clk))
			state = "on";
		else
			state = "off";

		if (!(clk->ops->set_parent))
			continue;

		parent = __clk_core_get_parent(clk);

		if (clk_core_is_enabled(parent))
			pstate = "on";
		else
			pstate = "off";

		seq_printf(s, "%20s%-2s%4s%-2s%6s%-2s%6s%-2s%6s%-2s%3d%-2s%10ld%-s%20s%-2s%4s%-2s%3d%-3s%10ld\n",
			__clk_core_get_name(clk), "", state, "", clk_enreg_check(clk), "", clk_selreg_check(clk),
			"", clk_divreg_check(clk), "", __clk_core_get_enable_count(clk), "",
			clk_core_get_rate(clk), "", __clk_core_get_name(parent), "", pstate, "",
			__clk_core_get_enable_count(parent), "", clk_core_get_rate(parent));
	}

	/* Output adjustable divider clock / fixed multiplier and divider clock in the clocks list */
	seq_printf(s, "--------------------------------------------------------------------------------------------------------------------------\n");
	seq_printf(s, "---------------------------------------[div clock] [fixed-factor clock]---------------------------------------------------\n");
	seq_printf(s, "----------------------------------------------------------------------------------------------------------------------------\n");

	seq_printf(s, "%17s%-6s%4s%-2s%6s%-2s%6s%-2s%6s%-s%7s%-2s%5s%-s%16s%-2s%4s%-2s%5s%-3s%5s\n",
		"clock", "", "status", "", "enreg", "", "selreg", "", "divreg", "", "refcnt", "", "rate",
		"", "parent", "", "status", "", "refcnt", "", "rate");
	seq_printf(s, "--------------------------------------------------------------------------------------------------------\n\n");

	list_for_each_entry(clk, &clocks, node) {
		if (clk_core_is_enabled(clk))
			state = "on";
		else
			state = "off";

		if (!(clk->ops->set_rate))
			continue;

		parent = __clk_core_get_parent(clk);

		if (clk_core_is_enabled(parent))
			pstate = "on";
		else
			pstate = "off";

		seq_printf(s, "%20s%-2s%4s%-2s%6s%-2s%6s%-2s%6s%-2s%3d%-2s%10ld%-s%20s%-2s%4s%-2s%3d%-3s%10ld\n",
			__clk_core_get_name(clk), "", state, "", clk_enreg_check(clk), "", clk_selreg_check(clk),
			"", clk_divreg_check(clk), "", __clk_core_get_enable_count(clk), "",
			clk_core_get_rate(clk), "", __clk_core_get_name(parent), "", pstate, "",
			__clk_core_get_enable_count(parent), "", clk_core_get_rate(parent));
	}

	mutex_unlock(&clock_list_lock);

	return 0;
}

#define MODULE_FUNCS_DEFINE(func_name)					\
static int func_name##_open(struct inode *inode, struct file *file)		\
{																		\
	return single_open(file, func_name##_show, inode->i_private);		\
}

MODULE_FUNCS_DEFINE(clock_get);
MODULE_FUNCS_DEFINE(clock_tree);
MODULE_FUNCS_DEFINE(clock_lookup);
MODULE_FUNCS_DEFINE(clock_enable);
MODULE_FUNCS_DEFINE(clock_disable);
MODULE_FUNCS_DEFINE(clock_getrate);
MODULE_FUNCS_DEFINE(clock_getparent);

ssize_t
clock_enable_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *clk_name = NULL;
	int ret = 0;
	int err = 0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}

	mutex_lock(&clock_list_lock);

	/*copy clock name from user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}

	/* Check if we have such a clock in the clocks list. if exist, prepare and enable it.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			pr_info("[old]:enable_refcnt = %d\n", clk->enable_count);

			ret = clk_prepare_enable(clk->hw->clk);
			if (ret) {
				err = -EINVAL;
				goto out;
			}

			pr_info("[new]:enable_refcnt = %d\n", clk->enable_count);
			err = cnt;
			goto out;
		}
	}

	pr_err("clk name error!\n");

out:
	kfree(clk_name);
	mutex_unlock(&clock_list_lock);
	return err;
}

ssize_t
clock_disable_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *clk_name = NULL;
	int err = 0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}

	mutex_lock(&clock_list_lock);

	/*copy clock name from user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}

	/* Check if we have such a clock in the clocks list. if exist, disable and unprepare it.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			pr_info("[old]:enable_refcnt = %d\n", clk->enable_count);

			clk_disable_unprepare(clk->hw->clk);

			pr_info("[new]:enable_refcnt = %d\n", clk->enable_count);
			err = cnt;
			goto out;
		}
	}
	pr_err("clk name error!\n");

out:
	kfree(clk_name);
	mutex_unlock(&clock_list_lock);
	return err;
}

ssize_t
clock_getparent_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *clk_name;
	int i;
	int err = 0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}

	mutex_lock(&clock_list_lock);

	/*copy clock name from user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}
	/* Check if we have such a clock in the clocks list. if exist, get parent of this clock.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			pr_info("[%s]:", clk->name);

			if (clk->num_parents)
				for (i = 0; i < clk->num_parents; i++)
					pr_info("[%d]:%s\n", i, clk->parent_names[i]);
			else
				pr_info("null \n");

			pr_info("\n------[current_parent]------\n");

			pr_info("%s\n\n\n", clk->parent->name);
			err = cnt;
			goto out;
		}
	}

	pr_err("clk name error!\n");

out:
	kfree(clk_name);
	mutex_unlock(&clock_list_lock);
	return err;
}


ssize_t
clock_getrate_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *clk_name;
	int err = 0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}

	/*copy clock name from user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}
	mutex_lock(&clock_list_lock);

	/* Check if we have such a clock in the clocks list. if exist, get rate of this clock.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			pr_info("\n[%s]: %ld\n\n\n", clk->name, clk_get_rate(clk->hw->clk));
			err = cnt;
			goto out;
		}
	}

	pr_err("clk name error!\n\n");

out:
	kfree(clk_name);
	mutex_unlock(&clock_list_lock);
	return err;
}

ssize_t
clock_setrate_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *str;
	char *clk_name;
	unsigned long rate;
	int ret = 0;
	int err = 0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}
	mutex_lock(&clock_list_lock);
	str = clk_name;
	/*copy clock name and clock rate from user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}
	/*get clock rate*/
	while (*str != ' ')
		str++;

	*str = '\0';

	str++;

	rate = simple_strtoul(str, NULL, 10);
	if (!rate) {
		pr_err("please input clk rate!\n");
		err = -EINVAL;
		goto out;
	}

	pr_info("rate = %ld\n\n", rate);

	/* Check if we have such a clock in the clocks list. if exist, set rate of this clock.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			ret = clk_set_rate(clk->hw->clk, rate);
			if (ret) {
				err = -EINVAL;
				goto out;
			}

			pr_info("[%s]: %ld\n\n", clk->name, clk->rate);
			err = cnt;
			goto out;
		}
	}
	/* if clk wasn't in the clocks list, clock name is error. */
	pr_err("clk name error!\n\n");

out:
	kfree(clk_name);
	mutex_unlock(&clock_list_lock);
	return err;
}

ssize_t
clock_setparent_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *Input_string;
	struct clk_core *parent = NULL;
	char *clk_name;
	const char *parent_name;
	int ret = 0;
	int i;
	int err = 0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}
	mutex_lock(&clock_list_lock);

	Input_string = clk_name;

	/*copy clock name from and parent name user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}

	/*get clock parent name.*/
	while (*Input_string != ' ')
		Input_string++;

	*Input_string = '\0';

	Input_string++;

	parent_name = Input_string;

	if (!parent_name) {
		pr_err("please input clk parent name!\n");
		err = -EINVAL;
		goto out;
	}

	/* Check if we have such a clock in the clocks list. if exist, set parent of this clock.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			for (i = 0; i < clk->num_parents; i++) {
				if (strcmp(parent_name, clk->parent_names[i]) == 0) {
					parent = clk->parents[i];
					break;
				}
			}
			if (parent) {
				pr_info("[%s]: set %s\n\n", __func__, parent->name);
				ret = clk_set_parent(clk->hw->clk, parent->hw->clk);
				if (ret) {
					err = -EINVAL;
					goto out;
				}

				pr_info("[%s]: %s\n\n", clk->name, parent->name);

				pr_info("clk set parent ok!\n\n");
			} else {
				printk("no parent find!");
			}
			err = cnt;
			goto out;
		}
	}
	pr_err("clk name error!\n");

out:
	kfree(clk_name);
	mutex_unlock(&clock_list_lock);
	return err;
}

ssize_t
clock_getreg_store(struct file *filp, const char __user *ubuf, size_t cnt,
		   loff_t *ppos)
{
	struct clk_core *clk = filp->private_data;
	char *clk_name;
	struct clk *clock_get = NULL;
	struct clk_core *clock = NULL;
	struct clk_gate *gate = NULL;
	struct clk_mux *mux =  NULL;
	void __iomem	 *ret = NULL;
	u32 bits = 0 ;
	u32 val = 0;
	int err =0;

	if (0 == cnt) {
		pr_err("Input string is NULL.\n");
		return -EINVAL;
	}

	if (CLK_INPUT_MAX_NUM < cnt) {
		pr_err("Input string is too long.\n");
		return -EINVAL;
	}
	clk_name = kzalloc(sizeof(char) * cnt, GFP_KERNEL);
	if (!clk_name) {
		pr_err("Cannot allocate clk_name.\n");
		return -EINVAL;
	}
	mutex_lock(&clock_list_lock);

	/*copy clock name from user space.*/
	if (copy_from_user(clk_name, ubuf, cnt - 1)) {
		err = -EINVAL;
		goto out;
	}


	/* Check if we have such a clock in the clocks list. if exist, get reg of this clock.*/
	list_for_each_entry(clk, &clocks, node) {
		if (strcmp(clk->name, clk_name) == 0) {
			clock_get = clk_get(NULL, clk->name);
			if (IS_ERR(clock_get)) {
				pr_err("%s clock_get failed!\n", clk->name);
				err = -EINVAL;
				goto out;
			}
			clock = clock_get->core;
			if (!clock) {
				pr_err("%s get failed!\n", clk->name);
				err = -EINVAL;
				goto out_put;
			}
			if (clock->ops->get_reg) {			 /* hi3xxx_periclk,hixxx_divclk */
				ret = clock->ops->get_reg(clock->hw);
			} else if (clock->ops->enable) {
				gate = to_clk_gate(clock->hw); /* andgt clock */
				ret = gate->reg;
				bits = BIT(gate->bit_idx);
				if (ret) {
					val = readl(ret);
					val &= bits;
				}
			} else if (clock->ops->set_parent) {	 /* mux clock */
				mux = to_clk_mux(clock->hw);
				ret = mux->reg;
				bits = mux->mask;
				if (ret) {
					val = readl(ret);
					val &= bits;
				}
			} else {
				pr_err("the clock %s is fixed or fiexd-factor\n", clk_name);
			}
			err = cnt;
			goto out_put;
		}
	}
	pr_err("clk name error!\n\n");

out_put:
	pr_info("\n[%s]: reg = 0x%p, bits = 0x%x, regval = 0x%x\n",
		clk_name, ret, bits, val);
	clk_put(clock_get);
out:
	mutex_unlock(&clock_list_lock);
	kfree(clk_name);
	return err;
}

#define MODULE_SHOW_DEFINE(func_name)					\
	static const struct file_operations func_name##_show_fops = {	\
	.open		= func_name##_open,								\
	.read		= seq_read,										\
	.llseek		= seq_lseek,									\
	.release	= single_release,								\
};

MODULE_SHOW_DEFINE(clock_tree);
MODULE_SHOW_DEFINE(clock_get);
MODULE_SHOW_DEFINE(clock_lookup);
MODULE_SHOW_DEFINE(clock_enable);
MODULE_SHOW_DEFINE(clock_disable);
MODULE_SHOW_DEFINE(clock_getrate);
MODULE_SHOW_DEFINE(clock_getparent);

static int clock_store_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

#define MODULE_STORE_DEFINE(func_name)					\
	static const struct file_operations func_name##_fops = {	\
	.open		= clock_store_open,						\
	.read		= seq_read,						\
	.write		= func_name##_store,			\
	.llseek		= seq_lseek,					\
};

MODULE_STORE_DEFINE(clock_enable);
MODULE_STORE_DEFINE(clock_disable);
MODULE_STORE_DEFINE(clock_getrate);
MODULE_STORE_DEFINE(clock_setrate);
MODULE_STORE_DEFINE(clock_getparent);
MODULE_STORE_DEFINE(clock_setparent);
MODULE_STORE_DEFINE(clock_getreg);

int clk_rate_fops_get(void *data, u64 *rate)
{
	struct clk_core *clk = data;

	*rate = clk->rate;

	return 0;
};

int clk_rate_fops_set(void *data, u64 rate)
{
	struct clk_core *clk = data;
	int ret = 0;

	ret = clk_prepare_enable(clk->hw->clk);
	if (ret)
		goto out;
	clk_set_rate(clk->hw->clk, rate);
	clk_disable_unprepare(clk->hw->clk);

out:
	return ret;
};

DEFINE_SIMPLE_ATTRIBUTE(clk_rate_fops, clk_rate_fops_get, clk_rate_fops_set, "%llu\n");

void __clk_statcheck(struct clk_core *clk)
{
	if (WARN_ON(clk_core_is_enabled(clk) == false))
		pr_err("%s stat exception! cnt is %d\n", clk->name, clk->enable_count);
}

int hisi_clk_debug_init(void)
{
#ifdef CONFIG_HISI_DEBUG_FS
	struct dentry *pdentry;

	clock = debugfs_create_dir("clock", NULL);

	if (!clock)
		return -ENOMEM;

	test_one_clock = debugfs_create_dir("test_one_clock", clock);
	if (!test_one_clock)
		return -ENOMEM;

	test_all_clocks = debugfs_create_dir("test_all_clocks", clock);
	if (!test_all_clocks)
		return -ENOMEM;

	debugfs_create_file("clock_tree", S_IRUGO, clock,
			NULL, &clock_tree_show_fops);

	#define PRIV_AUTH	(S_IRUSR|S_IWUSR|S_IRGRP)
	pdentry = test_all_clocks;
	debugfs_create_file("clk_get", PRIV_AUTH, pdentry, NULL, &clock_get_show_fops);
	debugfs_create_file("clk_lookup", PRIV_AUTH, pdentry, NULL, &clock_lookup_show_fops);
	debugfs_create_file("clk_enable", PRIV_AUTH, pdentry, NULL, &clock_enable_show_fops);
	debugfs_create_file("clk_disable", PRIV_AUTH, pdentry, NULL, &clock_disable_show_fops);
	debugfs_create_file("clk_getparent", PRIV_AUTH, pdentry, NULL, &clock_getparent_show_fops);
	debugfs_create_file("clk_getrate", PRIV_AUTH, pdentry, NULL, &clock_getrate_show_fops);

	pdentry = test_one_clock;
	#define PRIV_MODE	(S_IWUSR|S_IWGRP)
	debugfs_create_file("enable", PRIV_MODE, pdentry, NULL, &clock_enable_fops);
	debugfs_create_file("disable", PRIV_MODE, pdentry, NULL, &clock_disable_fops);
	debugfs_create_file("get_parent", PRIV_MODE, pdentry, NULL, &clock_getparent_fops);
	debugfs_create_file("set_parent", PRIV_MODE, pdentry, NULL, &clock_setparent_fops);
	debugfs_create_file("get_rate", PRIV_MODE, pdentry, NULL, &clock_getrate_fops);
	debugfs_create_file("set_rate", PRIV_MODE, pdentry, NULL, &clock_setrate_fops);
	debugfs_create_file("get_reg", PRIV_MODE, pdentry, NULL, &clock_getreg_fops);

#endif
	return 0;
}

void clk_list_add(struct clk_core *clk)
{
	mutex_lock(&clock_list_lock);
	list_add(&clk->node, &clocks);
	mutex_unlock(&clock_list_lock);
	return;
}

struct dentry *
debugfs_create_clkfs(struct clk_core *clk)
{
#ifdef CONFIG_HISI_DEBUG_FS
	return debugfs_create_file("clk_rate", S_IWUSR | S_IRUGO, clk->dentry, clk, &clk_rate_fops);
#else
	return NULL;
#endif
}



#ifdef CONFIG_HISI_CLK_TRACE
static void __track_clk(struct clk *clk, track_clk_type track_item, u32 freq)
{
	clk_record_info info;
	u8 cpu;

	if (!g_clk_hook_on) {
		return;
	}
	if (track_item >= TRACK_CLK_MAX) {
		pr_err("[%s], track_type [%d] is invalid!\n", __func__, track_item);
		return;
	}

	cpu = (u8) raw_smp_processor_id();
	if (SINGLE_BUFF == clk_sel_buf_type)
		cpu = 0;

	info.current_time    = hisi_getcurtime();
	info.item            = track_item;
	info.enable_count    = __clk_get_enable_count(clk);
	info.current_rate    = __clk_get_rate(clk);
	info.cpu_l           = __clk_get_rate(hs_trace_info.clk_cpu_l);
	info.cpu_b           = __clk_get_rate(hs_trace_info.clk_cpu_b);
	if (0 > __clk_get_source(clk)) {
		info.ppll    = CLK_ERR_NUM;
	} else {
		info.ppll    = __clk_get_source(clk);
	}
	info.ddr_freq        = __clk_get_rate(hs_trace_info.clk_ddr);
	info.peri_dvfs_vote0 = readl(CLK_DVFS_ADDR_0(hs_trace_info.pmuctrl));
	info.peri_dvfs_vote1 = readl(CLK_DVFS_ADDR_1(hs_trace_info.pmuctrl));

	(void)strncpy(info.comm, __clk_get_name(clk), sizeof(info.comm) - 1);
	info.comm[CLK_NAME_LEN - 1] = '\0';
	pr_debug("######%s!\n", info.comm);
	hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)g_clk_track_addr->percpu_addr[cpu], (u8 *)&info);
}

void track_clk_enable(struct clk *clk)
{
	if (IS_ERR_OR_NULL(clk)) {
		pr_err("%s param is null!\n", __func__);
		return;
	}
	__track_clk(clk, TRACK_ON_OFF, 0);
}
void track_clk_set_freq(struct clk *clk, u32 freq)
{
	if (IS_ERR_OR_NULL(clk)) {
		pr_err("%s param is null!\n", __func__);
		return;
	}
	__track_clk(clk, TRACK_SET_FREQ, freq);
}
void track_clk_set_dvfs(struct clk *clk, u32 freq)
{
	if (IS_ERR_OR_NULL(clk)) {
		pr_err("%s param is null!\n", __func__);
		return;
	}
	__track_clk(clk, TRACK_SET_DVFS, freq);
}
static void track_clk_reset(u32 modid, u32 etype, u64 coreid)
{
	return;
}

static void track_clk_dump(u32 modid, u32 etype, u64 coreid,
		char *pathname, pfn_cb_dump_done pfn_cb)
{
	if (pfn_cb) {
		pfn_cb(modid, coreid);
	}
	pr_info("%s dump!\n", __func__);
}

static int track_clk_rdr_register(struct rdr_register_module_result *result)
{
	struct rdr_module_ops_pub s_module_ops;
	int ret = -1;
	pr_info("%s start!\n", __func__);
	if (!result) {
		pr_err("%s para null!\n", __func__);
		return ret;
	}
	s_module_ops.ops_dump  = track_clk_dump;
	s_module_ops.ops_reset = track_clk_reset;
	ret = rdr_register_module_ops(clk_rdr_core_id, &s_module_ops, result);
	pr_info("%s end!\n", __func__);
	return ret;
}


int clk_percpu_buffer_init(u8 *addr, u32 size, u32 fieldcnt, u32 magic_number, u32 ratio[][8], buf_type_en buf_type)
{
	int i, ret;
	u32 cpu_num = num_possible_cpus();

	if (SINGLE_BUFF == buf_type)
		cpu_num = 1;
	pr_info("[%s], num_online_cpus [%d] !\n", __func__, num_online_cpus());

	if (IS_ERR_OR_NULL(addr) || IS_ERR_OR_NULL(addr)) {
		pr_err("[%s], buffer_addr [0x%p], buffer_size [0x%x]\n", __func__, addr, size);
		return -1;
	}

	/*set pc info for parse*/
	g_clk_track_addr              = (pc_record_info *)addr;
	g_clk_track_addr->buffer_addr = addr;
	g_clk_track_addr->buffer_size = size - sizeof(pc_record_info);
	g_clk_track_addr->dump_magic  = magic_number;

	/*set per cpu buffer*/
	for (i = 0; i < cpu_num; i++) {
		pr_info("[%s], ratio[%d][%d] = [%d]\n", __func__,
		       (cpu_num - 1), i, ratio[cpu_num - 1][i]);

		g_clk_track_addr->percpu_length[i] = g_clk_track_addr->buffer_size / 16 * ratio[cpu_num - 1][i];
		if (0 == i) {
			g_clk_track_addr->percpu_addr[0] = g_clk_track_addr->buffer_addr + sizeof(pc_record_info);
		} else {
			g_clk_track_addr->percpu_addr[i] =
			g_clk_track_addr->percpu_addr[i - 1] + g_clk_track_addr->percpu_length[i - 1];
		}

		pr_info("[%s], [%d]: percpu_addr [0x%p], percpu_length [0x%x], fieldcnt [%d]\n",
		       __func__, i, g_clk_track_addr->percpu_addr[i],
		       g_clk_track_addr->percpu_length[i], fieldcnt);

		ret = hisiap_ringbuffer_init((struct hisiap_ringbuffer_s *)
					   g_clk_track_addr->percpu_addr[i],
					   g_clk_track_addr->percpu_length[i], fieldcnt,
					   "clk");
		if (ret) {
			pr_err("[%s], cpu [%d] ringbuffer init failed!\n", __func__, i);
			return ret;
		}
	}
	return 0;
}

int clk_buffer_init(u8 *addr, u32 size, buf_type_en buf_type)
{
	unsigned int record_ratio[8][8] = {
	{16, 0, 0, 0, 0, 0, 0, 0},
	{8, 8, 0, 0, 0, 0, 0, 0},
	{6, 5, 5, 0, 0, 0, 0, 0},
	{4, 4, 4, 4, 0, 0, 0, 0},
	{4, 4, 4, 3, 1, 0, 0, 0},
	{4, 4, 3, 3, 1, 1, 0, 0},
	{4, 3, 3, 3, 1, 1, 1, 0},
	{3, 3, 3, 3, 1, 1, 1, 1}
	};

	return clk_percpu_buffer_init(addr, size, sizeof(clk_record_info), CLK_MAGIC_NUM, record_ratio, buf_type);
}



static int __init track_clk_record_init(void)
{
	int ret = -1;
	struct rdr_register_module_result clk_rdr_info;
	unsigned char *vir_addr = NULL;
	struct device_node *np;
	/*alloc rdr memory and init*/
	ret = track_clk_rdr_register(&clk_rdr_info);
	if (ret) {
		return ret;
	}
	if (0 == clk_rdr_info.log_len) {
		pr_err("%s clk_rdr_len is 0x0!\n", __func__);
		return 0;
	}
	vir_addr = (unsigned char *)hisi_bbox_map((phys_addr_t)clk_rdr_info.log_addr, clk_rdr_info.log_len);
	pr_info("%s log_addr is 0x%llx, log_len is 0x%x!\n", __func__, clk_rdr_info.log_addr, clk_rdr_info.log_len);
	if (IS_ERR_OR_NULL(vir_addr)) {
		pr_err("%s vir_addr err!\n", __func__);
		return -EINVAL;
	}
	memset(vir_addr, 0, clk_rdr_info.log_len);/*clean mem 0*/

	ret = clk_buffer_init(vir_addr, clk_rdr_info.log_len, clk_sel_buf_type);

	if (ret) {
		pr_err("%s buffer init err!\n", __func__);
		return -EINVAL;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,clk-pmctrl");
	if (NULL == np) {
		pr_err("[%s] fail to find pmctrl node!\n", __func__);
		return -EINVAL;
	}
	hs_trace_info.pmuctrl = of_iomap(np, 0);
	if (!hs_trace_info.pmuctrl) {
		pr_err("[%s]failed to iomap!\n", __func__);
		return -EINVAL;
	}

	hs_trace_info.clk_cpu_l = __clk_lookup("cpu-cluster.0");
	if (IS_ERR(hs_trace_info.clk_cpu_l)) {
		pr_err("_clk_get: clk_cpu_l not found!\n");
		return -EINVAL;
	}

	hs_trace_info.clk_cpu_b = __clk_lookup("cpu-cluster.1");
	if (IS_ERR(hs_trace_info.clk_cpu_b)) {
		pr_err("_clk_get: clk_cpu_b not found!\n");
		return -EINVAL;
	}

	hs_trace_info.clk_ddr = __clk_lookup("clk_ddrc_freq");
	if (IS_ERR(hs_trace_info.clk_ddr)) {
		pr_err("_clk_get: clk_ddr not found!\n");
		return -EINVAL;
	}

	if (check_himntn(HIMNTN_TRACE_CLK_REGULATOR))
		g_clk_hook_on = SWITCH_OPEN;

	pr_err("%s: hook_on = %d,rdr_phy_addr = 0x%llx, rdr_len = 0x%x, rdr_virt_add = 0x%p\n", __func__, g_clk_hook_on,
			clk_rdr_info.log_addr, clk_rdr_info.log_len, vir_addr);
	return 0;
}
module_init(track_clk_record_init);

static void __exit track_clk_record_exit(void)
{
	return;
}
module_exit(track_clk_record_exit);
MODULE_LICENSE("GPL");

#endif


