#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/bitops.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/semaphore.h>
#include <linux/printk.h>
#include "hisi_ddr_autofsgt_proxy_kernel.h"

/*FOR IPC*/
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/ipc_msg.h>

/*FOR HWLOCK*/
#include  <linux/hwspinlock.h>
#include <soc_acpu_baseaddr_interface.h>
#include <soc_crgperiph_interface.h>
#include <soc_sctrl_interface.h>


int ddr_autofsgt_ctrl(unsigned int client, unsigned int cmd)
{
	return 0;
}

static int __init ddr_autofsgt_proxy_init(void)
{
	return 0;
}


module_init(ddr_autofsgt_proxy_init);
