

#include <linux/clk-provider.h>
#include <linux/fs.h>

int hisi_clk_debug_init(void);
void clk_list_add(struct clk_core *clk);
struct dentry *debugfs_create_clkfs(struct clk_core *clk);

#ifdef CONFIG_HISI_CLK_TRACE
void track_clk_enable(struct clk *clk);
void track_clk_set_freq(struct clk *clk, u32 freq);
void track_clk_set_dvfs(struct clk *clk, u32 freq);
#endif
