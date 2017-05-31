/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  ��    ��  ��   : mmc_trace.c
  ��    ��  ��   : ����
  ��            ��   : Ԭ�� 00145322
  ��������   : 2015��3��9��
  ����޸�   :
  ��������   : mmc log ��¼����
  �����б�   :
  �޸���ʷ   :
  ��            ��   : 2015��3��9��
  ��            ��   : Ԭ�� 00145322
  �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ��ͷ�ļ�����
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/module.h>
#include <linux/init.h>
#include <linux/ctype.h>
#include <linux/poll.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/debugfs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/of_gpio.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/unistd.h>
#include <linux/sort.h>
#include <linux/err.h>
#include <linux/workqueue.h>
#include <asm/uaccess.h>
#include <linux/mmc/host.h>
#include <linux/sysfs.h>
#include <linux/semaphore.h>
#include <linux/stat.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>
#include <linux/hisi/mmc_trace.h>
#include <linux/pm_runtime.h>

#ifdef CONFIG_HISILICON_PLATFORM_MAINTAIN
#include "../../hisi/mntn/blackbox/rdr_print.h"
#include "../../hisi/mntn/blackbox/rdr_inner.h"
#include "../../hisi/mntn/blackbox/rdr_field.h"
#include "../../hisi/mntn/mntn_filesys.h"
#endif

#include "sdhci.h"
#include "dw_mmc.h"

#ifdef CONFIG_HISI_BB
#include <linux/hisi/rdr_pub.h>
#endif

/*****************************************************************************
  2 ��ȫ�ֱ�������
*****************************************************************************/
struct mmc_trace_client *mmc_trace_fd = NULL;

/*���֧��4���ַ�*/
static char *_dev_name[4] = {
	"emmc",
	"sd",
	"wifi",
	"mdm"
};

u64 *mmc_trace_switch = NULL;
u64 g_mmc_trace_buffer_addr = NULL;
u32 g_mmc_trace_fd_size = 0;

/* ע��ʱ���ص�ģ����Ϣ*/
struct rdr_register_module_result mmc_current_info;

/* ��ǰ�쳣coreid*/
static long current_core_id = RDR_EMMC;

/*ά��buffer��ʼ�����ַ*/
static u64 *dump_vir_addr = NULL;

/*��ӡ����0:OFF  1:ON*/
int g_mmctrace_dbg_lvl = 0;

extern struct sdhci_host *g_sdhci_for_mmctrace;
extern struct mmc_host *g_mmc_for_mmctrace[3];

extern u64 hisi_getcurtime(void);

#ifdef CONFIG_HISILICON_PLATFORM_MAINTAIN
extern int check_himntn(int feature);
extern int mntn_filesys_rm_file(const char *fullname);
extern int mntn_filesys_write_log(const char *pname, void *pbuf_vir, unsigned int ulen, umode_t mode);
#else
int check_himntn(int feature)
{
	return 0;
}

int mntn_filesys_rm_file(const char *fullname)
{
	return -1;
}

int mntn_filesys_write_log(const char *pname, void *pbuf_vir, unsigned int ulen, umode_t mode)
{
	return -1;
}
#endif

/*****************************************************************************
  3 ������ʵ��
*****************************************************************************/

void sdhci_dumpregs_fortrace(struct sdhci_host *host)
{
#ifdef CONFIG_PM
	/*sdhci_runtime_pm_get*/
	(void)pm_runtime_get_sync(host->mmc->parent);
#endif

	mmc_trace_comm_record (host->mmc, ": =========== REGISTER DUMP (%s)===========\n",
		mmc_hostname(host->mmc));

	mmc_trace_comm_record(host->mmc,": Sys addr: 0x%x | Version:  0x%x\n",
		sdhci_readl(host, SDHCI_DMA_ADDRESS),
		sdhci_readw(host, SDHCI_HOST_VERSION));
	mmc_trace_comm_record(host->mmc,": Blk size: 0x%x | Blk cnt:  0x%x\n",
		sdhci_readw(host, SDHCI_BLOCK_SIZE),
		sdhci_readw(host, SDHCI_BLOCK_COUNT));
	mmc_trace_comm_record(host->mmc,": Argument: 0x%x | Trn mode: 0x%x\n",
		sdhci_readl(host, SDHCI_ARGUMENT),
		sdhci_readw(host, SDHCI_TRANSFER_MODE));
	mmc_trace_comm_record(host->mmc,": Present:  0x%x | Host ctl: 0x%x\n",
		sdhci_readl(host, SDHCI_PRESENT_STATE),
		sdhci_readb(host, SDHCI_HOST_CONTROL));
	mmc_trace_comm_record(host->mmc,": Power:    0x%x | Blk gap:  0x%x\n",
		sdhci_readb(host, SDHCI_POWER_CONTROL),
		sdhci_readb(host, SDHCI_BLOCK_GAP_CONTROL));
	mmc_trace_comm_record(host->mmc,": Wake-up:  0x%x | Clock:    0x%x\n",
		sdhci_readb(host, SDHCI_WAKE_UP_CONTROL),
		sdhci_readw(host, SDHCI_CLOCK_CONTROL));
	mmc_trace_comm_record(host->mmc,": Timeout:  0x%x | Int stat: 0x%x\n",
		sdhci_readb(host, SDHCI_TIMEOUT_CONTROL),
		sdhci_readl(host, SDHCI_INT_STATUS));
	mmc_trace_comm_record(host->mmc,": Int enab: 0x%x | Sig enab: 0x%x\n",
		sdhci_readl(host, SDHCI_INT_ENABLE),
		sdhci_readl(host, SDHCI_SIGNAL_ENABLE));
	mmc_trace_comm_record(host->mmc,": AC12 err: 0x%x | Slot int: 0x%x\n",
		sdhci_readw(host, SDHCI_ACMD12_ERR),
		sdhci_readw(host, SDHCI_SLOT_INT_STATUS));
	mmc_trace_comm_record(host->mmc,": Caps:     0x%x | Caps_1:   0x%x\n",
		sdhci_readl(host, SDHCI_CAPABILITIES),
		sdhci_readl(host, SDHCI_CAPABILITIES_1));
	mmc_trace_comm_record(host->mmc,": Cmd:      0x%x | Max curr: 0x%x\n",
		sdhci_readw(host, SDHCI_COMMAND),
		sdhci_readl(host, SDHCI_MAX_CURRENT));
	mmc_trace_comm_record(host->mmc,": Host ctl2: 0x%x\n",
		sdhci_readw(host, SDHCI_HOST_CONTROL2));
	mmc_trace_comm_record(host->mmc,": Dbg Reg0: 0x%x | Reg1: 0x%x\n",
		sdhci_readl(host, SDHCI_DEBUG_REG0),
		sdhci_readl(host, SDHCI_DEBUG_REG1));
	mmc_trace_comm_record(host->mmc,": Dbg Reg2: 0x%x | Reg3: 0x%x\n",
		sdhci_readl(host, SDHCI_DEBUG_REG2),
		sdhci_readl(host, SDHCI_DEBUG_REG3));
	mmc_trace_comm_record(host->mmc,": PHY Ctrl1: 0x%x | Ctrl2: 0x%x\n",
		sdhci_readl(host, SDHCI_PHY_CTRL1),
		sdhci_readl(host,  SDHCI_PHY_CTRL2));
	mmc_trace_comm_record(host->mmc,": PHY Ctrl3: 0x%x | Status: 0x%x\n",
		sdhci_readl(host, SDHCI_PHY_CTRL3),
		sdhci_readl(host,  SDHCI_PHY_STATUS));
	if (host->flags & SDHCI_USE_ADMA) {
		if (host->flags & SDHCI_USE_64_BIT_DMA)
			mmc_trace_comm_record(host->mmc,": ADMA Err: 0x%x | ADMA Ptr: 0x%x%x\n",
				 sdhci_readl(host, SDHCI_ADMA_ERROR),
				 sdhci_readl(host, SDHCI_ADMA_ADDRESS_HI),
				 sdhci_readl(host, SDHCI_ADMA_ADDRESS));
		else
		mmc_trace_comm_record(host->mmc,": ADMA Err: 0x%x | ADMA Ptr: 0x%x\n",
		       sdhci_readl(host, SDHCI_ADMA_ERROR),
		       sdhci_readl(host, SDHCI_ADMA_ADDRESS));
	}
#ifdef CONFIG_PM
	/*sdhci_runtime_pm_put*/
	pm_runtime_mark_last_busy(host->mmc->parent);
	(void)pm_runtime_put_autosuspend(host->mmc->parent);
#endif
	mmc_trace_comm_record(host->mmc,": ===========================================\n");
}

static void queue_init(struct queue *q, char *name, unsigned int len)
{
	memset(q->name, 0, QUEUE_NAME_LEN);
	if (name) {
		strncpy(q->name, name, QUEUE_NAME_LEN);
		q->name[QUEUE_NAME_LEN - 1] = 0;
	}

	spin_lock_init(&q->lock);

	q->max = len;
	q->head = 0;
	q->tail = 0;
	q->in = 0;
	q->out = 0;

	memset(q->data, 0, len);

	return;
}

static void _queue_loop_in(struct queue *q, void *element, unsigned int len)
{
	unsigned int copy = min((q->max - q->head), len);
	unsigned int omit = len;
	unsigned int left = 0;

	/*left room */
	left = q->max - (MOD_SUB(q->head, q->tail, q->max));
	if (left > (len + 1)) {
		omit = 0;
	}

	/*update tail index */
	q->tail = MOD_ADD(q->tail, omit, q->max);

	/*copy data */
	memcpy(&(q->data[q->head]), element, copy);
	if (len > copy) {
		memcpy(&(q->data[0]), element + copy, len - copy);
	}
	q->head = MOD_ADD(q->head, len, q->max);
	q->in += len;

	return;
}

static void queue_loop_in(struct queue *q, void *element, unsigned int len)
{
	unsigned long flags = 0;

	spin_lock_irqsave(&q->lock, flags);
	_queue_loop_in(q, element, len);
	spin_unlock_irqrestore(&q->lock, flags);

	return;
}

/*****************************************************************************
 �� �� �� 	: mmc_trace_proc_write
 ��������   : proc �ڵ�д��������
 �������   :
 �������   : ��
 �� �� ֵ       :

 �޸���ʷ   :
 ��            ��   : 2015��4��15��
 ��            ��   : �˺�00221160
 �޸�����   : �����ɺ���
*****************************************************************************/
static ssize_t mmc_trace_proc_write(struct file *file, const char __user * userbuf, size_t count, loff_t * ppos)
{
	char buf;
	char getvalue;

	if (count <= 0)
		return 0;

	if (copy_from_user(&buf, userbuf, sizeof(char)))
		return -EFAULT;

	if ((buf != '0') && (buf != '1') && (buf != '2'))
		return -EFAULT;

	getvalue = buf - 48;

	memcpy(mmc_trace_switch, &getvalue, sizeof(char));

	return count;

}

/*****************************************************************************
�� �� �� 	: mmc_trace_proc_read
 ��������   : proc �ڵ����������
 �������   :
 �������   : ��
 �� �� ֵ       :

 �޸���ʷ   :
 ��            ��   : 2015��4��15��
 ��            ��   : �˺�00221160
 �޸�����   : �����ɺ���
*****************************************************************************/
static ssize_t mmc_trace_proc_read(struct file *file, char __user * userbuf, size_t count, loff_t * ppos)
{
	int cnt;

	if (count > sizeof(char))
		cnt = sizeof(char);
	else
		cnt = count;

	if (copy_to_user(userbuf, mmc_trace_switch, cnt))
		return -EFAULT;
	else {
		pr_err("data is 0x%llx\n", mmc_trace_switch[0]);
		return 0;
	}
}

static const struct file_operations mmc_trace_file_ops = {
	.owner = THIS_MODULE,
	.write = mmc_trace_proc_write,
	.read = mmc_trace_proc_read,
};

/*****************************************************************************
 �� �� �� 	    : mmc_trace_get_cur_time_str
 ��������   : ��ǰʱ���ȡ
 �������   : poutstr-���ʱ���ַ�����ulen-�ַ�����
 �������   : ��
 �� �� ֵ       : ��

 �޸���ʷ   :
 ��            ��   : 2015��4��15��
 ��            ��   : �˺�00221160
 �޸�����   : �����ɺ���
*****************************************************************************/
static void mmc_trace_get_cur_time_str(char *poutstr, unsigned int ulen)
{
	u64 ts = 0;

	if (NULL != poutstr) {
		ts = hisi_getcurtime();
		snprintf(poutstr, ulen, "\n[%lu]", (unsigned long)ts);
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_get_cmd_level_str
 ��������       : ��ǰ�豸���ͻ�ȡ
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_get_time_str(u64 time, char *poutstr, unsigned int ulen)
{
	if (NULL != poutstr) {
		snprintf(poutstr, ulen, "%llx", time);
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_get_device_str
 ��������       : ��ǰ�豸���ͻ�ȡ
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_get_device_str(int id, char *poutstr, unsigned int ulen)
{
	char *mmc_trace_devname = NULL;

	if (NULL != poutstr) {
		mmc_trace_devname = _dev_name[id];
		snprintf(poutstr, ulen, "%s", mmc_trace_devname);
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_get_cmd_level_str
 ��������       : ��ǰ�豸���ͻ�ȡ
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_get_cmd_level_str(char pos, char *poutstr, unsigned int ulen)
{
	if (NULL != poutstr) {
		snprintf(poutstr, ulen, "%d", pos);
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_get_cmd_level_str
 ��������       : ��ǰ���ͻ�ȡ
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_get_perf_flag_str(int arg, char *poutstr, unsigned int ulen)
{
	if (NULL != poutstr) {
		snprintf(poutstr, ulen, "%x", arg);
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_hex2asc
 ��������       : ���ֵ�ascת���ӿ�
 �������       : number
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
static int mmc_trace_hex2asc(int n)
{
	n &= 15;
	if (n > 9) {
		return ('a' - 10) + n;
	} else {
		return '0' + n;
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_printf_putc_init
 ��������       : ��ʼ����־д��
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_printf_putc_init(unsigned n, struct mmc_trace_client *client)
{
	struct mmc_trace_init *pInit = (struct mmc_trace_init *)MMC_TRACE_INIT_START_ADDR;
	u64 start_addr = (u64) ((struct queue *)(pInit->init_buff))->data;
	size_t len = MMC_TRACE_INIT_SIZE - sizeof(struct queue) - sizeof(struct mmc_trace_init);

	struct queue *q = (struct queue *)(((struct mmc_trace_init *)(client->mmc_trace_init))->init_buff);

	if (((u64) (&(q->data[q->head])) < start_addr)
		|| ((u64) (&(q->data[q->head])) > start_addr + len)) {
		pr_err("mmc trace init record  out of address!\n");
		return;
	}
	queue_loop_in((struct queue *)(((struct mmc_trace_init *)(client->mmc_trace_init))->init_buff), &n, sizeof(char));
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_printf_putc_init
 ��������       : ��ʼ����־д��
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_printf_putc_comm(unsigned n, struct mmc_trace_client *client)
{
	struct mmc_trace_comm *pComm = (struct mmc_trace_comm *)MMC_TRACE_COMM_START_ADDR;
	u64 start_addr = (u64) ((struct queue *)(pComm->comm_buff))->data;
	size_t len = MMC_TRACE_COMM_SIZE - sizeof(struct queue) - sizeof(struct mmc_trace_comm);

	struct queue *q = (struct queue *)(((struct mmc_trace_comm *)(client->mmc_trace_comm))->comm_buff);
	if (((u64) (&(q->data[q->head])) < start_addr)
		|| ((u64) (&(q->data[q->head])) > start_addr + len)) {
		pr_err("mmc trace comm record  out of address!\n");
		return;
	}
	queue_loop_in((struct queue *)(((struct mmc_trace_comm *)(client->mmc_trace_comm))->comm_buff), &n, sizeof(char));
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_printf_putc_init
 ��������       : ��ʼ����־д��
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_printf_putc_perf(unsigned n, struct mmc_trace_client *client)
{
	struct mmc_trace_perf *pPerf = (struct mmc_trace_perf *)MMC_TRACE_PERF_START_ADDR;
	u64 start_addr = (u64) ((struct queue *)(pPerf->perf_buff))->data;
	size_t len = MMC_TRACE_PERF_SIZE - sizeof(struct queue) - sizeof(struct mmc_trace_perf);

	struct queue *q = (struct queue *)(((struct mmc_trace_perf *)(client->mmc_trace_perf))->perf_buff);
	if (((u64) (&(q->data[q->head])) < start_addr)
		|| ((u64) (&(q->data[q->head])) > start_addr + len)) {
		pr_err("mmc trace perf record  out of address!\n");
		return;
	}
	queue_loop_in((struct queue *)(((struct mmc_trace_perf *)(client->mmc_trace_perf))->perf_buff), &n, sizeof(char));
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_printf_putc_init
 ��������       : ��ʼ����־д��
 �������       : id- �豸����id��poutstr-�����ulen����
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_xputs(const char *s, void (*mmc_trace_printf_putc) (unsigned n, struct mmc_trace_client * client), struct mmc_trace_client *client)
{
	while (*s) {
		mmc_trace_printf_putc(*s++, client);
	}
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_xprintf
 ��������       : ���д��
 �������       : mmc_trace_printf_putc-д����ú�����idex-ģ��id
 �������       : ��
 �� �� ֵ       : ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_xprintf(const char *fmt, va_list ap, void (*mmc_trace_printf_putc) (unsigned n, struct mmc_trace_client * client), struct mmc_trace_client *client, unsigned int idex)
{
	char scratch[MMC_TRACE_SCRATCH_SIZE] = { 0 };
	char time_trace[MMC_TRACE_TIME_SIZE] = { 0 };
	char dev_name[MMC_TRACE_DEVNAME_SIZE] = { 0 };
	int i = 0;

	mmc_trace_get_cur_time_str(time_trace, sizeof(time_trace));
	for (i = 0; i < sizeof(time_trace); i++) {
		mmc_trace_printf_putc(time_trace[i], client);
	}

	mmc_trace_get_device_str(idex, dev_name, sizeof(dev_name));
	for (i = 0; i < sizeof(dev_name); i++) {
		mmc_trace_printf_putc(dev_name[i], client);
	}

	for (;;) {
		switch (*fmt) {
		case 0:
			va_end(ap);
			return;
		case '%':
			switch (fmt[1]) {
			case 'c':{
					unsigned n = va_arg(ap, unsigned);
					mmc_trace_printf_putc(n, client);
					fmt += 2;
					continue;
				}
			case 'h':{
					unsigned n = va_arg(ap, unsigned);
					mmc_trace_printf_putc(mmc_trace_hex2asc(n >> 12), client);
					mmc_trace_printf_putc(mmc_trace_hex2asc(n >> 8), client);
					mmc_trace_printf_putc(mmc_trace_hex2asc(n >> 4), client);
					mmc_trace_printf_putc(mmc_trace_hex2asc(n >> 0), client);
					fmt += 2;
					continue;
				}
			case 'b':{
					unsigned n = va_arg(ap, unsigned);
					mmc_trace_printf_putc(mmc_trace_hex2asc(n >> 4), client);
					mmc_trace_printf_putc(mmc_trace_hex2asc(n >> 0), client);
					fmt += 2;
					continue;
				}
			case 'p':
			case 'X':
			case 'x':{
					unsigned n = va_arg(ap, unsigned);
					char *p = scratch + 15;
					*p = 0;
					do {
						*--p = mmc_trace_hex2asc(n);
						n = n >> 4;
					} while (n != 0);
					while (p > (scratch + 7))
						*--p = '0';
					mmc_trace_xputs(p, mmc_trace_printf_putc, client);
					fmt += 2;
					continue;
				}
			case 'd':{
					int n = va_arg(ap, int);
					char *p = scratch + 15;
					*p = 0;
					if (n < 0) {
						mmc_trace_printf_putc('-', client);
						n = -n;
					}
					do {
						*--p = (n % 10) + '0';
						n /= 10;
					} while (n != 0);
					mmc_trace_xputs(p, mmc_trace_printf_putc, client);
					fmt += 2;
					continue;
				}
			case 's':{
					char *s = va_arg(ap, char *);
					if (s == 0)
						s = "(null)";
					mmc_trace_xputs(s, mmc_trace_printf_putc, client);
					fmt += 2;
					continue;
				}
			}
			mmc_trace_printf_putc(*fmt++, client);
			break;
		case '\n':
			mmc_trace_printf_putc('\r', client);
			mmc_trace_printf_putc(*fmt++, client);
			break;
		default:
			mmc_trace_printf_putc(*fmt++, client);
			break;
		}
	}
}

/*****************************************************************************
 ��    ��  ��   : mmc_trace_rdr_dump
 ��������       : RDR �ڴ��ʼ��
 �������       : void
 �������       : ��
 ��    �� ֵ    : 0 success, -1 fail

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_rdr_dump(u32 modid, u32 etype, u64 coreid, char *pathname, pfn_cb_dump_done pfn_cb)
{
	/* ����ص�������Ϊ����������־�����֪ͨ��ܱ�����־������� */
	pfn_cb(modid, coreid);
	return;
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_rdr_reset
 ��������       : RDR�ڴ��ʼ��
 �������       : void
 �������       : ��
 �� �� ֵ       : 0 success, -1 fail

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static void mmc_trace_rdr_reset(u32 modid, u32 etype, u64 coreid)
{
	pr_err("%s enter \n", __func__);
	return;
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_clean_rdr_memory
 ��������       : RDR�ڴ��ʼ��
 �������       : void
 �������       : ��
 �� �� ֵ       : 0 success, -1 fail

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static int mmc_trace_clean_rdr_memory(struct rdr_register_module_result rdr_info)
{
	dump_vir_addr = (u64 *) hisi_bbox_map(rdr_info.log_addr, rdr_info.log_len);
	if (NULL == dump_vir_addr) {
		pr_err("hisi_bbox_map (%llx) failed in %s!\n", rdr_info.log_addr, __func__);
		return -1;
	}

	pr_err("mmc trace buf [%p] , size [%x] \n", dump_vir_addr, rdr_info.log_len);

	memset(dump_vir_addr, 0, rdr_info.log_len);

	return 0;
}

/*****************************************************************************
 ��   ��   ��   : mmc_trace_rdr_register_core
 ��������       : ע�᱾ģ�����ָ��
 �������       : void
 �������       : ��
 ��    ��  ֵ   : 0 success, -1 fail

 �޸���ʷ       :
 ��        ��   : 2015��4��15��
 ��        ��   : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static int mmc_trace_rdr_register_core(void)
{
	struct rdr_module_ops_pub s_module_ops;
	int ret = -1;

	s_module_ops.ops_dump = mmc_trace_rdr_dump;
	s_module_ops.ops_reset = mmc_trace_rdr_reset;

	/* �����ṩ��ģ�鱣����־�ķ����ͱ�ģ������״̬�ĺ���. */
	ret = rdr_register_module_ops(current_core_id, &s_module_ops, &mmc_current_info);
	if (ret < 0) {
		pr_err("%s:rdr register module ops fail!\n", __func__);
		return ret;
	}

	/*RDR �ڴ��ʼ�� */
	ret = mmc_trace_clean_rdr_memory(mmc_current_info);
	if (ret < 0) {
		pr_err("%s:rdr clean memory fail!\n", __func__);
		return ret;
	}

	return ret;
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_rdr_register_exception
 ��������       : ����ע�᱾ģ����ܷ������쳣����
 �������       : void
 �������       : ��
 �� �� ֵ       : 0 success, -1 fail

 �޸���ʷ       :
 ��       ��    : 2015��4��15��
 ��       ��    : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static int mmc_trace_rdr_register_exception(void)
{
	struct rdr_exception_info_s einfo;
	int ret = -1;

	/*��ģ���ʼ��ʧ���쳣ע��. */
	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	/*��ʼ��ʧ��RDR_MODID_MMC_INIT_FAIL */
	einfo.e_modid = RDR_MODID_MMC_INIT_FAIL;
	einfo.e_modid_end = RDR_MODID_MMC_INIT_FAIL;
	/*���������. */
	einfo.e_process_priority = RDR_ERR;
	/* �������� */
	einfo.e_reboot_priority = RDR_REBOOT_NOW;
	/* ֪ͨAP������־.���޸� */
	einfo.e_notify_core_mask = RDR_AP;
	/* ֪ͨAP����״̬.����֪ͨap��λȫϵͳ */
	einfo.e_reset_core_mask = RDR_AP;
	/* �������쳣����(��η������ظ�����). */
	einfo.e_reentrant = RDR_REENTRANT_DISALLOW;
	/* �쳣���ͳ�ʼ��ʧ�� */
	einfo.e_exce_type = MMC_S_EXCEPTION;
	/* �쳣������EMMC. */
	einfo.e_from_core = RDR_EMMC;
	einfo.e_upload_flag = RDR_UPLOAD_NO;
	memcpy(einfo.e_from_module, "RDR_MMC_INIT", sizeof("RDR_MMC_INIT"));
	memcpy(einfo.e_desc, "RDR_MMC_init fail.", sizeof("RDR_MMC_init fail."));

	ret = rdr_register_exception(&einfo);
	if (ret != RDR_MODID_MMC_INIT_FAIL) {
		pr_err(" register exception faild [0x%x]\n", einfo.e_modid);
		return -1;
	}

	/*��ģ�鳬ʱ�쳣. */
	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	einfo.e_modid = RDR_MODID_MMC_CMD_TIMEOUT;
	einfo.e_modid_end = RDR_MODID_MMC_CMD_TIMEOUT;
	einfo.e_process_priority = RDR_ERR;
	einfo.e_reboot_priority = RDR_REBOOT_NOW;
	einfo.e_notify_core_mask = RDR_AP;
	einfo.e_reset_core_mask = RDR_AP;
	einfo.e_reentrant = RDR_REENTRANT_DISALLOW;
	einfo.e_exce_type = MMC_S_EXCEPTION;
	einfo.e_from_core = RDR_EMMC;
	einfo.e_upload_flag = RDR_UPLOAD_NO;
	memcpy(einfo.e_from_module, "RDR_MMC_TIME_OUT", sizeof("RDR_MMC_TIME_OUT"));
	memcpy(einfo.e_desc, "RDR_MMC_TIME_OUT fail.", sizeof("RDR_MMC_TIME_OUT fail."));

	ret = rdr_register_exception(&einfo);
	if (ret != RDR_MODID_MMC_CMD_TIMEOUT) {
		pr_err("register exception faild [0x%x]\n", einfo.e_modid);
		return -1;
	}

	return 0;
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_rdr_init
 ��������       : ��RDRע��ģ��
 �������       : void
 �������       : ��
 �� �� ֵ       : 0 success, -1 fail

 �޸���ʷ       :
 ��       ��    : 2015��4��15��
 ��       ��    : �˺�00221160
 �޸�����       : �����ɺ���
*****************************************************************************/
static int mmc_trace_rdr_init(void)
{
	int ret = 0;

	ret = mmc_trace_rdr_register_core();
	if (ret != 0) {
		pr_err("%s:mmc trace rdr register core fail!\n", __func__);
		return ret;
	}

	ret = mmc_trace_rdr_register_exception();
	if (ret != 0) {
		pr_err("%s:mmc trace rdr register exception fail!\n", __func__);
		return ret;
	}

	return ret;
}

/*****************************************************************************
 �� �� �� 	    : mmc_trace_client_register
 ��������       : mmc trace client��ʼ�����
 �������       : void
 �������       : ��
 �� �� ֵ       : mmc_trace_client�ṹ��

 �޸���ʷ       :
 ��        ��   : 2015��3��9��
 ��        ��   : Ԭ�� 00145322
 �޸�����       : �����ɺ���
*****************************************************************************/
struct mmc_trace_client *mmc_trace_client_init(void)
{
	struct mmc_trace_client *pClt = NULL;
	struct mmc_trace_init *pInit = NULL;
	struct mmc_trace_comm *pComm = NULL;
	struct mmc_trace_perf *pPerf = NULL;
	struct proc_dir_entry *entry = NULL;

	if (0 == check_himntn(HIMNTN_MMC_TRACE)) {
		pr_err("%s:mmc trace init fail! check himntn fail \n",__func__);
		return NULL;
	}

	/*RDR ģ���ʼ�� */
	if (mmc_trace_rdr_init() != 0) {
		pr_err("%s:mmc trace init fail!\n", __func__);
		return NULL;
	}

	pClt = (struct mmc_trace_client *)dump_vir_addr;

	g_mmc_trace_buffer_addr = (u64) dump_vir_addr;
	g_mmc_trace_fd_size = sizeof(struct mmc_trace_client);

	/*  ��ʼ����ͨ�á�������־�ڴ滮�ֳ�ʼ�� */
	pInit = (struct mmc_trace_init *)MMC_TRACE_INIT_START_ADDR;
	pComm = (struct mmc_trace_comm *)MMC_TRACE_COMM_START_ADDR;
	pPerf = (struct mmc_trace_perf *)MMC_TRACE_PERF_START_ADDR;

	pInit->init_save_filepath = MMC_TRACE_INIT_PATH;
	pInit->buff_size = MMC_TRACE_INIT_SIZE;
	pInit->name = MMC_TRACE_INIT_NAME;

	pComm->comm_save_filepath = MMC_TRACE_COMM_PATH;
	pComm->buff_size = MMC_TRACE_COMM_SIZE;
	pComm->name = MMC_TRACE_COMM_NAME;

	pPerf->perf_save_filepath = MMC_TRACE_PERF_PATH;
	pPerf->buff_size = MMC_TRACE_PERF_SIZE;
	pPerf->name = MMC_TRACE_PERF_NAME;

	pClt->mmc_trace_init = (void *)pInit;
	pClt->mmc_trace_comm = (void *)pComm;
	pClt->mmc_trace_perf = (void *)pPerf;

	pClt->client_name = "storage_trace";
	pClt->proc_flag = MMC_COMMON_FLAG;
	pClt->buff_size = MMC_TRACE_TOTAL_SIZE - sizeof(struct mmc_trace_client);

	mmc_trace_switch = &(pClt->proc_flag);

	spin_lock_init(&pClt->init_lock);
	spin_lock_init(&pClt->comm_lock);
	spin_lock_init(&pClt->lock);

	entry = proc_create(pClt->client_name, 0660, NULL, &mmc_trace_file_ops);
	if (!entry) {
		pr_err("%s: failed to create proc entry, %p\n", __func__, entry);
		return NULL;
	}

	pr_err("mmc_trace adr begin [%p] ,fd size [%d] \n", dump_vir_addr, g_mmc_trace_fd_size);
	pr_err("mmc_trace initbuf [%p], size [%ld] \n", ((struct queue *)(pInit->init_buff))->data, pInit->buff_size - sizeof(struct queue) - sizeof(struct mmc_trace_init));
	pr_err("mmc_trace commbuf [%p], size [%ld] \n", ((struct queue *)(pComm->comm_buff))->data, pComm->buff_size - sizeof(struct queue) - sizeof(struct mmc_trace_comm));
	pr_err("mmc_trace perfbuf [%p], size [%ld] \n", ((struct queue *)(pPerf->perf_buff))->data, pPerf->buff_size - sizeof(struct queue) - sizeof(struct mmc_trace_perf));

	queue_init((struct queue *)(pInit->init_buff), pInit->name, pInit->buff_size - sizeof(struct queue) - sizeof(struct mmc_trace_init));
	queue_init((struct queue *)(pComm->comm_buff), pComm->name, pComm->buff_size - sizeof(struct queue) - sizeof(struct mmc_trace_comm));
	queue_init((struct queue *)(pPerf->perf_buff), pPerf->name, pPerf->buff_size - sizeof(struct queue) - sizeof(struct mmc_trace_perf));

	return pClt;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_init_record
 ��������      : ��ʼ�����ݼ�¼�ӿڣ�  ����ʹ�����ж�������
 �������      : void
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
static int mmc_trace_init_record(struct mmc_host *host, const char *fmt, ...)
{
	va_list ap;

	if (NULL == mmc_trace_fd) {
		MMCTRACE_DEBUGPL(0x3, "%s: mmc_trace_fd is NULL \n", __func__);
		return -1;
	}

	if (NULL == host) {
		MMCTRACE_DEBUGPL(0x3, "%s:host is null \n", __func__);
		return -1;
	}

	/*ͨ��mntn���������Ƿ��¼log */
	if (0 == check_himntn(HIMNTN_MMC_TRACE)) {
		MMCTRACE_DEBUGPL(0x3, "%s:mntn is closed \n", __func__);
		return 0;
	}

	spin_lock(&mmc_trace_fd->init_lock);

	va_start(ap, fmt);
	mmc_trace_xprintf(fmt, ap, mmc_trace_printf_putc_init, mmc_trace_fd, host->index);
	va_end(ap);

	spin_unlock(&mmc_trace_fd->init_lock);

	return 0;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_comm_record
 ��������      :  ͨ�����ݼ�¼�ӿ� ����ʹ�����ж�������
 �������      : host��fmt
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
int mmc_trace_comm_record(struct mmc_host *host, const char *fmt, ...)
{
	va_list ap;

	if (NULL == mmc_trace_fd) {
		MMCTRACE_DEBUGPL(0x3, "%s: mmc_trace_fd is NULL \n", __func__);
		return -1;
	}

	if (NULL == host) {
		MMCTRACE_DEBUGPL(0x3, "%s:host is null \n", __func__);
		return -1;
	}

	/*ͨ��mntn���������Ƿ��¼log */
	if (0 == check_himntn(HIMNTN_MMC_TRACE)) {
		MMCTRACE_DEBUGPL(0x3, "%s:mntn is closed \n", __func__);
		return 0;
	}

	/*ͨ��proc�ڵ������Ƿ��¼log */
	if (!(MMC_COMMON_FLAG & (mmc_trace_fd->proc_flag))) {
		return 0;
	}

	spin_lock(&mmc_trace_fd->comm_lock);

	va_start(ap, fmt);
	mmc_trace_xprintf(fmt, ap, mmc_trace_printf_putc_comm, mmc_trace_fd, host->index);
	va_end(ap);

	spin_unlock(&mmc_trace_fd->comm_lock);
	return 0;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_perf_record
 ��������      : �������ݼ�¼�ӿڣ�����ʹ�����ж�������
 �������      : record
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_perf_record(struct mmc_trace_perf_point_record *record)
{
	int i = 0;
	u64 ts = 0;
	int length = sizeof(struct mmc_trace_perf_point_record) + sizeof(u64);
	char log_tmp[sizeof(struct mmc_trace_perf_point_record) + sizeof(u64)];

	if (NULL == mmc_trace_fd) {
		MMCTRACE_DEBUGPL(0x3, "%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	if (NULL == record) {
		MMCTRACE_DEBUGPL(0x3, "%s:record is null \n", __func__);
		return;
	}

	if (mmc_trace_fd->mmc_trace_tofile_perf == true)
		return;

	/*ͨ��mntn���������Ƿ��¼log */
	if (0 == check_himntn(HIMNTN_MMC_TRACE)) {
		MMCTRACE_DEBUGPL(0x3, "%s:mntn is closed \n", __func__);
		return;
	}

	/*ͨ��proc�ڵ������Ƿ��¼log */
	if (!(MMC_PERFORMANCE_FLAG & (mmc_trace_fd->proc_flag))) {
		return;
	}

	spin_lock(&mmc_trace_fd->lock);

	ts = hisi_getcurtime();

	memset(log_tmp, 0x00, sizeof(struct mmc_trace_perf_point_record) + sizeof(u64));
	memcpy(log_tmp, &ts, sizeof(u64));
	memcpy(log_tmp + sizeof(u64), record, sizeof(struct mmc_trace_perf_point_record));

	for (i = 0; i < length; i++)
		mmc_trace_printf_putc_perf(log_tmp[i], mmc_trace_fd);

	spin_unlock(&mmc_trace_fd->lock);

	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_sdhci_dumpregs
 ��������      : sdhciIP�Ĵ���dump�ӿ�
 �������      : host
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
static void mmc_trace_sdhci_dumpregs(struct sdhci_host *host)
{
	if (NULL == host) {
		pr_err("%s: sdhci hsot is NULL \n", __func__);
		return;
	}

	sdhci_dumpregs_fortrace(host);
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_dwmmc_dumpregs
 ��������      : dwmmcIP�Ĵ���dump�ӿ�
 �������      : mmc
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
static void mmc_trace_dwmmc_dumpregs(struct mmc_host *mmc)
{
	if (NULL == mmc) {
		pr_err("%s: mmc host is NULL \n", __func__);
		return;
	}

	dw_mci_reg_dump_fortrace(mmc);
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_dumpregs
 ��������      : IP�Ĵ���dump�ӿ�
 �������      : index
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
static int mmc_trace_dumpregs(unsigned int index)
{
	if (index >= DEV_TRACE_MAX)
		return -1;

	switch (index) {
	case EMMC:
		mmc_trace_sdhci_dumpregs(g_sdhci_for_mmctrace);
		break;
	case SD:
		mmc_trace_dwmmc_dumpregs(g_mmc_for_mmctrace[index]);
		break;
	case SDIO:
		mmc_trace_dwmmc_dumpregs(g_mmc_for_mmctrace[index]);
		break;
	default:
		;
	}

	return 0;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_tofile
 ��������      : trace log ��¼
 �������      : trace_type ��־��¼���
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
static int mmc_trace_tofile(MMC_TRACE_TYPE trace_type)
{
	char *mmc_trace_filepath = NULL;
	char *mmc_trace_buffer = NULL;
	size_t mmc_trace_size = 0;
	int retval = 0;

	if (NULL == mmc_trace_fd) {
		pr_err("%s: mmc_trace_fd is NULL \n", __func__);
		return -1;
	}

	/*��ȡ��ά��log�������ļ������ڴ�·������С */
	if (trace_type == TRACE_INIT) {
		mmc_trace_filepath = ((struct mmc_trace_init *)(mmc_trace_fd->mmc_trace_init))->init_save_filepath;
		mmc_trace_buffer = ((struct mmc_trace_init *)(mmc_trace_fd->mmc_trace_init))->init_buff;
		mmc_trace_size = ((struct mmc_trace_init *)(mmc_trace_fd->mmc_trace_init))->buff_size - sizeof(struct mmc_trace_init) - sizeof(struct queue);
	} else if (trace_type == TRACE_COMM) {
		mmc_trace_filepath = ((struct mmc_trace_comm *)(mmc_trace_fd->mmc_trace_comm))->comm_save_filepath;
		mmc_trace_buffer = ((struct mmc_trace_comm *)(mmc_trace_fd->mmc_trace_comm))->comm_buff;
		mmc_trace_size = ((struct mmc_trace_comm *)(mmc_trace_fd->mmc_trace_comm))->buff_size - sizeof(struct mmc_trace_comm) - sizeof(struct queue);
	} else if (trace_type == TRACE_PERF) {
		mmc_trace_filepath = MMC_TRACE_PERF_RAWDATA_PATH;
		mmc_trace_buffer = ((struct mmc_trace_perf *)(mmc_trace_fd->mmc_trace_perf))->perf_buff;
		mmc_trace_size = ((struct mmc_trace_perf *)(mmc_trace_fd->mmc_trace_perf))->buff_size - sizeof(struct mmc_trace_perf) - sizeof(struct queue);
	} else {
		pr_err("%s: trace_type is invalid \n", __func__);
		return -1;
	}

	/*ɾ��hisi_logsĿ¼�µľ��ļ� */
	retval = mntn_filesys_rm_file(mmc_trace_filepath);
	if (0 != retval) {
		pr_err("%s: mntn_filesys_rm_file fail \n", __func__);
		return -1;
	}

	if ((NULL == mmc_trace_filepath) || (NULL == mmc_trace_buffer)
		|| (0 == mmc_trace_size)) {
		pr_err("%s: input para is invalid \n", __func__);
		return -1;
	}

	/*�����µ�bin�ļ��ӿ� */
	retval = mntn_filesys_write_log(mmc_trace_filepath, ((struct queue *)(mmc_trace_buffer))->data, mmc_trace_size, 0660);
	if (!retval) {
		pr_err("%s: mntn_filesys_write_log fail \n", __func__);
		return -1;
	}

	return 0;

}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_init_tofile
 ��������      : trace init��¼
 �������      : ��
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_init_tofile(void)
{
	int retval = 0;

	retval = mmc_trace_tofile(TRACE_INIT);
	if (0 == retval) {
		pr_err("mmc trace init record ok\n");
	} else {
		pr_err("mmc trace init record fail\n");
	}
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_comm_tofile
 ��������      : trace comm��¼
 �������      : ��
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_comm_tofile(int index)
{
	int retval = 0;

	if (mmc_trace_fd == NULL) {
		pr_err("%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	/*��ֹ������¼log */
	mmc_trace_fd->mmc_trace_tofile_comm = true;

	mdelay(100);

	retval = mmc_trace_dumpregs(index);
	if (0 != retval) {
		pr_err("mmc trace comm record fail\n");
		mmc_trace_fd->mmc_trace_tofile_comm = false;

		return;
	}

	retval = mmc_trace_tofile(TRACE_COMM);
	if (0 == retval) {
		pr_err("mmc trace comm record ok\n");
	} else {
		pr_err("mmc trace comm record fail\n");
	}

	mmc_trace_fd->mmc_trace_tofile_comm = false;

	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_perf_tofile
 ��������      : trace perf��¼
 �������      : ��
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_perf_tofile(void)
{
	int i = 0;
	int cnt = 0;
	int trace_len = 0;
	int retval = 0;
	int buf_size = 0;
	int step = 0;
	char *mmc_trace_filepath = NULL;
	char *record_position = NULL;
	struct mmc_trace_perf_record_exp *record_exp;
	struct mmc_trace_perf_record_act *record_act;
	char end_flag[3] = "\n";

	if (mmc_trace_fd == NULL) {
		pr_err("%s: mmc_trace_fd is NULL, mmc trace perf record fail \n", __func__);
		return;
	}

	/*��ֹ������¼log */
	mmc_trace_fd->mmc_trace_tofile_perf = true;

	mdelay(100);

	/*����ʹ�� */
#if 0
	retval = mmc_trace_tofile(TRACE_PERF);
	if (0 == retval) {
	} else {
		MMCTRACE_DEBUGPL(0x3, "mmc trace perf record raw fail\n");
		mmc_trace_fd->mmc_trace_tofile_perf = false;
		return;
	}
#endif

	/*����һ��������־���ݽṹ���������������䲢д���ڴ� */
	record_exp = (struct mmc_trace_perf_record_exp *)(((struct mmc_trace_perf *)(mmc_trace_fd->mmc_trace_perf))->perf_buff + sizeof(struct queue) - 8);
	record_position = (char *)(((struct mmc_trace_perf *)(mmc_trace_fd->mmc_trace_perf))->perf_buff + sizeof(struct queue) - 8);

	/*��־���������ݻ����ڴ��С������ */
	buf_size = ((struct queue *)(((struct mmc_trace_perf *)(mmc_trace_fd->mmc_trace_perf))->perf_buff))->max;
	cnt = buf_size / sizeof(struct mmc_trace_perf_record_exp);
	step = sizeof(struct mmc_trace_perf_record_exp);

	MMCTRACE_DEBUGPL(0x3, "@@@@ record is %p \n", record_exp);
	MMCTRACE_DEBUGPL(0x3, "@@@@ record time is %llx \n", record_exp->time);
	MMCTRACE_DEBUGPL(0x3, "@@@@ record id is %d \n", record_exp->id);
	MMCTRACE_DEBUGPL(0x3, "@@@@ record pos is %d \n", record_exp->pos);
	MMCTRACE_DEBUGPL(0x3, "@@@@ record arg1 is %d \n", record_exp->arg1);
	MMCTRACE_DEBUGPL(0x3, "@@@@ record arg2 is %d \n", record_exp->arg2);
	MMCTRACE_DEBUGPL(0x3, "@@@@, %d, cnt is %x , step is %d \n", buf_size, cnt, step);

	mmc_trace_filepath = ((struct mmc_trace_perf *)(mmc_trace_fd->mmc_trace_perf))->perf_save_filepath;
	trace_len = sizeof(struct mmc_trace_perf_record_act);

	retval = mntn_filesys_rm_file(mmc_trace_filepath);
	if (0 != retval) {
		MMCTRACE_DEBUGPL(0x3, "%s: mntn_filesys_rm_file fail \n", __func__);
		mmc_trace_fd->mmc_trace_tofile_perf = false;
		return;
	}

	record_act = (struct mmc_trace_perf_record_act *)
		kmalloc(sizeof(struct mmc_trace_perf_record_act), GFP_KERNEL);

	for (i = 0; i < cnt; i++) {
		if (record_exp->time != 0) {
			MMCTRACE_DEBUGPL(0x3, "%d,%x,%d \n", record_exp->id, record_exp->pos, i);
			MMCTRACE_DEBUGPL(0x3, "%s: %p \n", __func__, record_exp);

			memset(record_act, 0x00, trace_len);
			strncpy(&(record_act->end[0]), end_flag, sizeof(end_flag));
			mmc_trace_get_time_str(record_exp->time, &(record_act->time[0]), sizeof(record_act->time));
			mmc_trace_get_device_str(record_exp->id, &(record_act->device[0]), sizeof(record_act->device));
			mmc_trace_get_cmd_level_str(record_exp->pos, &(record_act->cmd[0]), sizeof(record_act->cmd));
			mmc_trace_get_perf_flag_str(record_exp->arg1, &(record_act->flag1[0]), sizeof(record_act->flag1));
			mmc_trace_get_perf_flag_str(record_exp->arg2, &(record_act->flag2[0]), sizeof(record_act->flag2));

			retval = mntn_filesys_write_log(mmc_trace_filepath, record_act, trace_len, 0660);
			if (!retval) {
				MMCTRACE_DEBUGPL(0x3, "%s: mntn_filesys_write_log fail,mmc trace perf record fail \n", __func__);
				mmc_trace_fd->mmc_trace_tofile_perf = false;
				goto done;
			}
		} else {
			pr_err("mmc trace comm perf ok\n");
			mmc_trace_fd->mmc_trace_tofile_perf = false;
			goto done;
		}

		record_position = record_position + step;
		record_exp = (struct mmc_trace_perf_record_exp *)(record_position);
	}

	mmc_trace_fd->mmc_trace_tofile_perf = false;

done:
	kfree(record_act);
	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_byself
 ��������      : trace ��¼
 �������      : ��
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_byself(int index)
{
	mmc_trace_init_tofile();
	mmc_trace_comm_tofile(index);
	mmc_trace_perf_tofile();
}

/*��������ʹ�ýӿ�*/
#if 0
void mmc_trace_raw_data(void)
{
	int retval = -1;

	if (dump_vir_addr == NULL)
		return;

	/*ɾ��hisi_logsĿ¼�µľ��ļ� */
	retval = mntn_filesys_rm_file(MMC_TRACE_RAW_DATA_PATH);
	if (0 != retval) {
		printk(KERN_ERR "%s: mntn_filesys_rm_file fail \n", __func__);
		return;
	}

	/*�����µ�bin�ļ��ӿ� */
	retval = mntn_filesys_write_log(MMC_TRACE_RAW_DATA_PATH, dump_vir_addr, MMC_TRACE_TOTAL_SIZE, 0660);
	if (!retval) {
		printk(KERN_ERR "%s: mntn_filesys_write_log fail \n", __func__);
		return;
	}

	return;
}
#endif

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_init_begin
 ��������      : ��ʼ����¼��ʼ���
 �������      : host
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
           ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_init_begin(struct mmc_host *host)
{
	if (NULL == mmc_trace_fd) {
		pr_err("%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	if (NULL == host) {
		mmc_trace_fd->mmc_trace_init_mmc_flag = 1;
		mmc_trace_fd->mmc_trace_init_sd_flag = 1;
		mmc_trace_fd->mmc_trace_init_sdio_flag = 1;
		return;
	}

	switch (host->index) {
	case EMMC:
		mmc_trace_fd->mmc_trace_init_mmc_flag = 1;
		break;
	case SD:
		mmc_trace_fd->mmc_trace_init_sd_flag = 1;
		break;
	case SDIO:
		mmc_trace_fd->mmc_trace_init_sdio_flag = 1;
		break;
	default:
		;
	}

	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_init_end
 ��������      : ��ʼ����¼�������
 �������      : host
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_init_end(struct mmc_host *host)
{
	if (NULL == mmc_trace_fd) {
		pr_err("%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	if (NULL == host) {
		mmc_trace_fd->mmc_trace_init_mmc_flag = 0;
		mmc_trace_fd->mmc_trace_init_sd_flag = 0;
		mmc_trace_fd->mmc_trace_init_sdio_flag = 0;
		return;
	}

	switch (host->index) {
	case EMMC:
		mmc_trace_fd->mmc_trace_init_mmc_flag = 0;
		break;
	case SD:
		mmc_trace_fd->mmc_trace_init_sd_flag = 0;
		break;
	case SDIO:
		mmc_trace_fd->mmc_trace_init_sdio_flag = 0;
		break;
	default:
		;
	}

	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_record
 ��������      : ��־��¼�ӿ� ����ʹ�����ж�������
 �������      : struct mmc_host *host, struct mmc_request *mrq
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_record(struct mmc_host *host, struct mmc_request *mrq)
{
	if ((NULL == host) || (NULL == mrq)) {
		MMCTRACE_DEBUGPL(0x3, "%s , host or mrq is null \n", __func__);
		return;
	}

	if (NULL == mmc_trace_fd) {
		MMCTRACE_DEBUGPL(0x3, "%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	if ((mmc_trace_fd->mmc_trace_tofile_comm == true)
		|| (mmc_trace_fd->mmc_trace_reset_initfail == true)
		|| (mmc_trace_fd->mmc_trace_reset_cmdtimeout == true))
		return;

	/*��ʼ����־��¼ */
	if (((host->index == EMMC) && mmc_trace_fd->mmc_trace_init_mmc_flag)
		|| ((host->index == SD) && mmc_trace_fd->mmc_trace_init_sd_flag)
		|| ((host->index == SDIO)
			&& mmc_trace_fd->mmc_trace_init_sdio_flag)) {
		mmc_trace_init_record(host, "[A]%x,[R0]%x,[C]%d\n", mrq->cmd->arg, mrq->cmd->resp[0], mrq->cmd->opcode);
	} else {
		/*ͨ����־��¼ */
		if ((mrq->cmd->opcode == CMD25) || (mrq->cmd->opcode == CMD18)
			|| (mrq->cmd->opcode == CMD13)) {
			mmc_trace_comm_record(host, "[C]%d\n", mrq->cmd->opcode);
		} else {
			mmc_trace_comm_record(host, "[A]%x,[R0]%x,[C]%d\n", mrq->cmd->arg, mrq->cmd->resp[0], mrq->cmd->opcode);
		}
	}

	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_emmc_init_fail_reset
 ��������      : �����ʼ����λ�ӿ�
 �������      : ��
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_emmc_init_fail_reset(void)
{
	if (check_himntn(HIMNTN_MMC_TRACE) == 0) {
		pr_err("%s:emmc init failed\n", __func__);
		BUG_ON(true);
	}

	if (NULL == mmc_trace_fd) {
		pr_err("%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	/*��ֹ������¼log */
	mmc_trace_fd->mmc_trace_reset_initfail = true;

	mdelay(15000);

	mmc_trace_dumpregs(EMMC);

#ifdef CONFIG_HISI_BB
	rdr_syserr_process_for_ap(RDR_MODID_MMC_INIT_FAIL, 0, 0);
#endif

	return;
}

/*****************************************************************************
 ��	  ��   ��  : mmc_trace_emmc_cmd_timeout_reset
 ��������      : �������ʱ��λ�ӿ�
 �������      : ��
 �������      : ��
 ��   ��   ֵ  : void
 ���ú���      :
 ��������      :

 �޸���ʷ      :
 ��        ��  : 2015��3��9��
 ��        ��  : Ԭ�� 00145322
 �޸�����      : �����ɺ���
*****************************************************************************/
void mmc_trace_emmc_cmd_timeout_reset(void)
{
	return;
#if 0
	if (NULL == mmc_trace_fd) {
		pr_err("%s: mmc_trace_fd is NULL \n", __func__);
		return;
	}

	/*��ֹ������¼log */
	mmc_trace_fd->mmc_trace_reset_cmdtimeout = true;

	mdelay(15000);

	mmc_trace_dumpregs(EMMC);

#ifdef CONFIG_HISI_BB
	rdr_syserr_process_for_ap(RDR_MODID_MMC_CMD_TIMEOUT, 0, 0);
#endif

	return;
#endif
}

void mmc_trace_fd_init(void)
{
	if (check_himntn(HIMNTN_MMC_TRACE) != 0) {
		mmc_trace_fd = mmc_trace_client_init();
	}

	if(NULL == mmc_trace_fd)
	{
	    printk(KERN_ERR "mmc trace init fail\n");
	}
	else
	{
	    printk(KERN_ERR "mmc trace init success\n");
	}

}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
