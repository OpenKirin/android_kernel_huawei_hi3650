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
#include <linux/workqueue.h>

#include <global_ddr_map.h>
#include "protocol.h"
#include "inputhub_route.h"

#define SHMEM_AP_RECV_PHY_ADDR (HISI_RESERVED_CH_BLOCK_SHMEM_PHYMEM_BASE)
#define SHMEM_AP_RECV_PHY_SIZE (HISI_RESERVED_CH_BLOCK_SHMEM_PHYMEM_SIZE/2)
#define SHMEM_AP_SEND_PHY_ADDR (SHMEM_AP_RECV_PHY_ADDR + SHMEM_AP_RECV_PHY_SIZE)
#define SHMEM_AP_SEND_PHY_SIZE (HISI_RESERVED_CH_BLOCK_SHMEM_PHYMEM_SIZE/2)
#define SHMEM_INIT_OK (0x0aaaa5555)
#define MODULE_NAME "sharemem"

extern int inputhub_mcu_write_cmd_adapter(const void *buf, unsigned int length,
					  struct read_info *rd);

static LIST_HEAD(shmem_client_list);
static DEFINE_MUTEX(shmem_recv_lock);

struct shmem_ipc_data {
	unsigned int module_id;	/*enum is different between M7 & A53, so use "unsigned int" */
	unsigned int buf_size;
};

struct shmem_ipc {
	pkt_header_t hd;
	struct shmem_ipc_data data;
};

struct shmem_resp {
	pkt_header_t hd;
};

struct shmem_client {
	obj_tag_t module_id;
	void (*notifier_call) (void __iomem * buf_addr, unsigned int buf_size);
	struct list_head node;
};

struct shmem {
	unsigned int init_flag;
	void __iomem *recv_addr;
	void __iomem *send_addr;
	struct semaphore send_sem;
#ifdef CONFIG_HISI_DEBUG_FS
	struct dentry *debugfs_root;
#endif
};

static struct shmem shmem_gov;

static int shmem_ipc_send(unsigned char cmd, obj_tag_t module_id,
			  unsigned int size)
{
	struct shmem_ipc pkt;
	pkt.hd.tag = TAG_SHAREMEM;
	pkt.hd.cmd = cmd;
	pkt.hd.resp = 0;
	pkt.data.module_id = module_id;
	pkt.data.buf_size = size;
	pkt.hd.length = sizeof(struct shmem_ipc_data);
	return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
}

static int shmem_recv(const pkt_header_t * head)
{
	struct shmem_client *pos, *next;
	struct shmem_ipc *msg = (struct shmem_ipc *)head;
	int result = 0;
	if (NULL == head)
		return -EINVAL;

	mutex_lock(&shmem_recv_lock);
	list_for_each_entry_safe(pos, next, &shmem_client_list, node)
	    if (pos->module_id == msg->data.module_id) {
		if (pos->notifier_call)
			pos->notifier_call(shmem_gov.recv_addr,
					   msg->data.buf_size);
		break;
	}

	if (pos->module_id != msg->data.module_id)
		pr_err("[%s]not find module_id[0x%0x]\n", __func__,
		       msg->data.module_id);

	result =
	    shmem_ipc_send(CMD_SHMEM_AP_RECV_RESP, pos->module_id,
			   msg->data.buf_size);
	mutex_unlock(&shmem_recv_lock);
	return result;
}

int shmem_notifier_register(obj_tag_t module_id,
			    void (*notifier_call) (void __iomem * buf_addr,
						   unsigned int buf_size))
{
	struct shmem_client *pos, *next, *new_client;

	if (TAG_BEGIN > module_id || module_id >= TAG_END
	    || NULL == notifier_call)
		return -EINVAL;

	mutex_lock(&shmem_recv_lock);

	list_for_each_entry_safe(pos, next, &shmem_client_list, node) {
		if (pos->module_id == module_id
		    && notifier_call == pos->notifier_call) {
			pr_err("[%s][0x%x] have registered\n", __func__,
			       module_id);
			mutex_unlock(&shmem_recv_lock);
			return -EEXIST;
		}
	}

	new_client =
	    (struct shmem_client *)kzalloc(sizeof(struct shmem_client),
					   GFP_KERNEL);
	if (!new_client) {
		pr_err("[%s]kzalloc err\n", __func__);
		mutex_unlock(&shmem_recv_lock);
		return -ENOMEM;
	}

	new_client->module_id = module_id;
	new_client->notifier_call = notifier_call;
	list_add_tail(&new_client->node, &shmem_client_list);
	mutex_unlock(&shmem_recv_lock);
	return 0;
}

struct workqueue_struct *receive_response_wq = NULL;
struct receive_response_work_t {
	struct shmem_ipc_data data;
	struct work_struct worker;
};

struct receive_response_work_t receive_response_work;

static void receive_response_work_handler(struct work_struct *work)
{
	struct receive_response_work_t *p =
	    container_of(work, struct receive_response_work_t, worker);
	if (!p) {
		pr_err("%s NULL pointer\n", __func__);
		return;
	}
	shmem_ipc_send(CMD_SHMEM_AP_RECV_RESP, p->data.module_id,
		       p->data.buf_size);
}

const pkt_header_t *shmempack(const char *buf, unsigned int length)
{
	struct shmem_ipc *msg = NULL;
	static char recv_buf[SHMEM_AP_RECV_PHY_SIZE] = { 0, };
	const pkt_header_t *head = (const pkt_header_t *)recv_buf;

	if (NULL == buf)
		return NULL;

	msg = (struct shmem_ipc *)buf;

	memcpy(recv_buf, shmem_gov.recv_addr, msg->data.buf_size);
	INIT_WORK(&receive_response_work.worker, receive_response_work_handler);
	queue_work(receive_response_wq, &receive_response_work.worker);

	return head;
}

int shmem_notifier_unregister(obj_tag_t module_id)
{
	struct shmem_client *pos, *next;
	if (TAG_BEGIN > module_id || module_id >= TAG_END)
		return -EINVAL;
	mutex_lock(&shmem_recv_lock);
	list_for_each_entry_safe(pos, next, &shmem_client_list, node)
	    if (pos->module_id == module_id)
		break;
	if (pos->module_id != module_id) {
		pr_err("[%s]not find module_id[0x%0x]\n", __func__, module_id);
		mutex_unlock(&shmem_recv_lock);
		return -ENODEV;
	}
	list_del(&pos->node);
	kfree(pos);
	mutex_unlock(&shmem_recv_lock);
	return 0;
}

static int shmem_recv_init(void)
{
	int ret = 0;

	receive_response_wq =
	    create_freezable_workqueue("sharemem_receive_response");

	if (!receive_response_wq) {
		pr_err
		    ("failed to create sharemem_receive_response workqueue\n");
		return -1;
	}

	ret = register_mcu_event_notifier(TAG_SHAREMEM,
					  CMD_SHMEM_AP_RECV_REQ, shmem_recv);
	if (ret) {
		pr_err("[%s] register_mcu_event_notifier err\n", __func__);
		return ret;
	}

	shmem_gov.recv_addr =
	    ioremap_wc(SHMEM_AP_RECV_PHY_ADDR, SHMEM_AP_RECV_PHY_SIZE);
	if (!shmem_gov.recv_addr) {
		unregister_mcu_event_notifier(TAG_SHAREMEM,
					      CMD_SHMEM_AP_RECV_REQ,
					      shmem_recv);
		pr_err("[%s] ioremap err\n", __func__);
		return -ENOMEM;
	}

	return 0;
}

int shmem_send(obj_tag_t module_id, const void *usr_buf,
	       unsigned int usr_buf_size)
{
	int ret;
	if ((NULL == usr_buf) || (usr_buf_size > SHMEM_AP_SEND_PHY_SIZE))
		return -EINVAL;
	if (SHMEM_INIT_OK != shmem_gov.init_flag)
		return -EPERM;
	ret = down_timeout(&shmem_gov.send_sem, msecs_to_jiffies(500));
	if (ret)
		pr_warning("[%s]down_timeout 500\n", __func__);
	memcpy((void *)shmem_gov.send_addr, usr_buf, usr_buf_size);
	return shmem_ipc_send(CMD_SHMEM_AP_SEND_REQ, module_id, usr_buf_size);
}

static int shmem_send_resp(const pkt_header_t * head)
{
	up(&shmem_gov.send_sem);
	return 0;
}

static int shmem_send_init(void)
{
	int ret = register_mcu_event_notifier(TAG_SHAREMEM,
					      CMD_SHMEM_AP_SEND_RESP,
					      shmem_send_resp);
	if (ret) {
		pr_err("[%s] register_mcu_event_notifier err\n", __func__);
		return ret;
	}

	shmem_gov.send_addr =
	    ioremap_wc(SHMEM_AP_SEND_PHY_ADDR, SHMEM_AP_SEND_PHY_SIZE);
	if (!shmem_gov.send_addr) {
		unregister_mcu_event_notifier(TAG_SHAREMEM,
					      CMD_SHMEM_AP_SEND_RESP,
					      shmem_send_resp);
		pr_err("[%s] ioremap err\n", __func__);
		return -ENOMEM;
	}

	sema_init(&shmem_gov.send_sem, 1);

	return 0;
}

#ifdef CONFIG_DEBUG_FS
int show_buff = 1;
long udata_size;
unsigned char t_pool_send[SHMEM_AP_SEND_PHY_SIZE];

static void shmem_callback(void __iomem * buf_addr, unsigned int buf_size)
{
	struct timeval tv;
	if (NULL == buf_addr)
		return;
	show_buff = memcmp(buf_addr, t_pool_send, udata_size);
	do_gettimeofday(&tv);
	pr_err("R:tv_sec[%ld]tv_usec[%06ld]\n", tv.tv_sec, tv.tv_usec);
}

static int shmem_debugfs_show(struct seq_file *s, void *data)
{
	return seq_printf(s, "%d\n", show_buff);
}

static int shmem_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, shmem_debugfs_show, NULL);
}

static ssize_t shmem_debugfs_write(struct file *file,
				   const char __user * user_buf,
				   size_t count, loff_t * ppos)
{
	long val;
	char buf[64];
	int b_max;
	int ret = 0;
	struct timeval tv;

	b_max = min(count, sizeof(buf) - 1);

	if (copy_from_user(buf, user_buf, b_max))
		return -EFAULT;

	buf[b_max] = 0;

	ret = kstrtol(buf, 10, &val);
	if (ret < 0) {
		pr_err("%s: input error!\n", MODULE_NAME);
		return count;
	}

	switch (val) {
	case 1:
		ret = shmem_notifier_register(TAG_SHAREMEM, shmem_callback);
		if (ret)
			pr_err("[%s]registered failed\n", __func__);
		return count;
	case 2:
		ret = shmem_notifier_unregister(TAG_SHAREMEM);
		if (ret)
			pr_err("[%s]unregistered failed\n", __func__);
		return count;
	default:
		break;
	}

	udata_size = val;
	memset((void *)t_pool_send, 0xaa, val);
	do_gettimeofday(&tv);
	pr_err("S:tv_sec[%ld]tv_usec[%06ld]\n", tv.tv_sec, tv.tv_usec);
	ret = shmem_send(TAG_SHAREMEM, (const void *)t_pool_send, val);
	if (ret)
		pr_err("[%s]shmem_send failed[ret %d]\n", __func__, ret);
	return count;
}

static const struct file_operations shmem_operations = {
	.open = shmem_debugfs_open,
	.read = seq_read,
	.write = shmem_debugfs_write,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
int __init contexthub_shmem_init(void)
{
	int ret = 0;
	ret = shmem_recv_init();
	if (ret)
		return ret;
	ret = shmem_send_init();
	if (ret)
		return ret;

#ifdef CONFIG_HISI_DEBUG_FS
	shmem_gov.debugfs_root = debugfs_create_dir(MODULE_NAME, NULL);
	if (IS_ERR(shmem_gov.debugfs_root) || !shmem_gov.debugfs_root) {
		pr_err("[%s]%s: failed to create debugfs directory!\n",
		       __func__, MODULE_NAME);
		return -ENOENT;
	}

	debugfs_create_file("test", S_IFREG | S_IRUGO,
			    shmem_gov.debugfs_root, NULL, &shmem_operations);
#endif

	shmem_gov.init_flag = SHMEM_INIT_OK;
	return ret;
}

MODULE_ALIAS("platform:contexthub" MODULE_NAME);
MODULE_LICENSE("GPL v2");
