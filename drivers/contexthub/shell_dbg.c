#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/time.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <global_ddr_map.h>
#include "protocol.h"
#include "inputhub_route.h"

#define MODULE_NAME "shell_dbg"
#define CHAR_LR 0xA
#define CHAR_CR 0xD
#define SHELL_DBG_STRING_SIZE (MAX_PKT_LENGTH - sizeof(pkt_header_t) - 4)
enum {
	pro_resp_none,
	pro_resp_ipc,
	pro_resp_wait,
};

struct SHELL_DBG_RESP {
    pkt_header_t hd;
	 uint32_t log_addr;
	 uint32_t log_len;
};

struct sh_dbg_pkt {
	pkt_header_t hd;
	unsigned char data[SHELL_DBG_STRING_SIZE];
};

extern int inputhub_mcu_write_cmd_adapter(const void *buf, unsigned int length,
				   struct read_info *rd);

static struct completion wait_resp;
static uint32_t get_resp = pro_resp_none;
static uint32_t log_address, log_length;
static char* str_ipc_tmout = "wait:";
static uint32_t ipc_tmout = 6000;

static int shell_dbg_resp_ope(const pkt_header_t *head)
{
	struct SHELL_DBG_RESP *p = (struct SHELL_DBG_RESP*)head;
	if (p) {
		pr_info("get resp: addr:%x, len:%x;\n", p->log_addr, p->log_len);
		log_address = p->log_addr;
		log_length = p->log_len;
	}
	complete(&wait_resp);
	return 0;
}

int shell_dbg_send(const void *buf, unsigned int len)
{
	struct sh_dbg_pkt pkt;
	pkt.hd.tag = TAG_SHELL_DBG;
	pkt.hd.cmd = CMD_SHELL_DBG_REQ;
	pkt.hd.resp = 0;
	pkt.hd.length = len;
	memset(pkt.data, 0, sizeof(pkt.data));
	memcpy(pkt.data, buf, len);
	return inputhub_mcu_write_cmd_adapter(&pkt, len + offsetof(struct sh_dbg_pkt, data), NULL);
}

static ssize_t shell_dbg_rd(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
	ssize_t wr_len = 0;
	char *p_save;
	char s_buf[0x40] = {0};

	if (get_resp == pro_resp_ipc) {
		/* get ipc message */
		p_save = (char*)ioremap(log_address, count);
		wr_len = simple_read_from_buffer(buf, count, pos, p_save, log_length);
		iounmap(p_save);
	} else if (get_resp == pro_resp_wait) {
		/* return for wait cmd */
		snprintf(s_buf, sizeof(s_buf), "\nset wait %d(ms) success;\n\n", ipc_tmout);
		wr_len = simple_read_from_buffer(buf, count, pos, s_buf, strlen(s_buf));
	} else {
		/* nothing feedback */
		snprintf(s_buf, sizeof(s_buf), "\nerror: no msg get!\n\n");
		wr_len = simple_read_from_buffer(buf, count, pos, s_buf, strlen(s_buf));
	}
	return wr_len;
}

static ssize_t shell_dbg_wr(struct file *file, const char __user *userbuf,
			  size_t bytes, loff_t *off)
{
	char *kn_buf = NULL;
	ssize_t byte_writen = 0;
	int i;
	long val = 0;

	get_resp = pro_resp_none;	/* clear resp flag first */

	if (bytes >= SHELL_DBG_STRING_SIZE) {
		pr_err("Invalide buffer length\n");
		return -1;
	}
	kn_buf = kzalloc(SHELL_DBG_STRING_SIZE, GFP_KERNEL);
	if (NULL == kn_buf) {
		pr_err("kn_buf is null\n");
		return -EFAULT;
	}

	byte_writen = simple_write_to_buffer(kn_buf,
					SHELL_DBG_STRING_SIZE, off,
					userbuf, bytes);
	if (byte_writen <= 0) {
		pr_err("Invalide buffer data\n");
		goto END;
	}

	/* process wait cmd: */
	if (0 == strncmp(str_ipc_tmout, kn_buf, strlen(str_ipc_tmout))) {
		if ((strict_strtol(kn_buf + strlen(str_ipc_tmout), 10, &val) < 0) || (val < 0)) {
			byte_writen = -EINVAL;
		} else {
			get_resp = pro_resp_wait;
			ipc_tmout = val;
			pr_err("ipc_tmout is %d;\n", ipc_tmout);
		}
		goto END;
	}

	/* process normal cmd: */
	for (i = 0; i < SHELL_DBG_STRING_SIZE; i++) {
		if (kn_buf[i] == CHAR_LR || kn_buf[i] == CHAR_CR) {
			kn_buf[i] = '\0';
STRING_END:
			byte_writen = i + 1;
			break;
		}
		if (kn_buf[i] == '\0')
			goto STRING_END;
	}
	kn_buf[SHELL_DBG_STRING_SIZE - 1] = '\0';

	pr_info("shell dgb send str:%s;\n", kn_buf);

	/* process string */
	shell_dbg_send(kn_buf, strlen(kn_buf) + 1);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	INIT_COMPLETION(wait_resp);
#else
	reinit_completion(&wait_resp);
#endif
	barrier();

	if (!!wait_for_completion_timeout
	    (&wait_resp, msecs_to_jiffies(ipc_tmout))) {
		get_resp = pro_resp_ipc;
	}

END:
	kfree(kn_buf);
	return byte_writen;
}

static const struct file_operations shell_dbg_fops = {
	.write = shell_dbg_wr,
	.read = shell_dbg_rd,
};

static int __init shell_dbg_init(void)
{
	struct dentry *ch_root = NULL;
	int ret = -1;
	struct dentry *shell_dbg_file_dentry;
#ifdef CONFIG_HISI_DEBUG_FS
	init_completion(&wait_resp);

	/*creat this dir first, because multi-platform will use this dir */
	ch_root = debugfs_create_dir("contexthub", NULL);
	if (NULL != ch_root) {
		shell_dbg_file_dentry =
		    debugfs_create_file("shell_dbg", 0660, ch_root, NULL,
					&shell_dbg_fops);
		if ((NULL == shell_dbg_file_dentry)
		    || IS_ERR(shell_dbg_file_dentry)) {
			debugfs_remove(ch_root);
			pr_err("contexthub shell dbg creat failed!\n");
			goto FUNC_END;
		} else {
			ret = register_mcu_event_notifier(TAG_SHELL_DBG,
				CMD_SHELL_DBG_RESP, shell_dbg_resp_ope);
			if (ret) {
				pr_err("[%s] register_mcu_event_notifier err\n", __func__);
			} else {
				pr_info("contexthub shell dbg creat successfully!\n");
			}
		}
	}
#endif
FUNC_END:
	return ret;
}

module_init(shell_dbg_init);
MODULE_ALIAS("platform:contexthub"MODULE_NAME);
MODULE_LICENSE("GPL v2");
