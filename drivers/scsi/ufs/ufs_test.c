
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt"\n"

#include <linux/async.h>
#include <linux/atomic.h>
#include <linux/blkdev.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <scsi/scsi.h>
#include <scsi/scsi_device.h>
#include <scsi/scsi_eh.h>
#include <scsi/scsi_cmnd.h>
#include <scsi/scsi_host.h>
#include <linux/devfreq.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/scatterlist.h>
#include <asm/unaligned.h>
#include <linux/uaccess.h>
#include "ufshci.h"
#include "ufshcd.h"
#include "ufs.h"
#include "ufs_test.h"

#define MODULE_NAME "ufs_test"
#define UFS_TEST_VER "V1.0.0.1"


#define SCSI_SENSE_BUF_LEN             0x20
#define SCSI_INQUIRY_LEN               36
#define SCSI_MODE_SENSE_LEN            36
#define SCSI_READ_CAPACITY_LEN         8
#define BLOCK_COUNT 4096
#define PRDT_SG_NUM 128
#define RC_LEN 32

enum ufs_test_testcases {
	UFS_TEST_QUERY,
	NUM_TESTS,
};

static DEFINE_MUTEX(ufs_test_lock);
static LIST_HEAD(ufs_test_file_test);
static LIST_HEAD(ufs_test_result);

struct ufs_test_transfer_result {
	struct list_head link;
	unsigned int count;
	unsigned int sectors;
	struct timespec ts;
	unsigned int rate;
	unsigned int iops;
};

struct ufs_test_general_result {
	struct list_head link;
	int testcase;
	int result;
	struct list_head tr_lst;
};

struct ufs_test_debugfs_file {
	struct list_head link;
	struct dentry *file;
	struct ufs_hba *hba;
};

struct ufs_test_ud {
	struct dentry *debugfs_root;
	struct ufs_hba *hba;
};

struct ufs_test {
	struct ufs_hba *hba;
	unsigned int g_lun;
	unsigned long g_start_addr;
	unsigned long g_length;
	unsigned long g_trunk_size;
	unsigned long g_data_mode;
	unsigned long max_addr;
	unsigned long lun_max_lba[UFS_UPIU_MAX_GENERAL_LUN];
	unsigned int g_cmd;
	unsigned int g_resp;
	unsigned int g_para;
};

struct ufs_test_case {
	const char *name;
	int (*prepare)(struct ufs_test *);
	int (*run)(struct ufs_test *);
	int (*cleanup)(struct ufs_test *);
};

struct ufs_test_query_case {
	const char *name;
	int (*prepare)(void);
	int (*run)(void);
	int (*cleanup)(void);
};

enum cmdflag {
	CMDNONE,
	CONTEXT_ID = 1,
	SYSDTAG = (1 << 4),
	CACHE,
};

enum ufs_test_status_type {
	TEST_STATUS_OK = 0,
	TEST_STATUS_CMD_ERR,
	TEST_STATUS_DATA_CHECK_ERR,
	TEST_STATUS_PARAM_ERR,
	TEST_STATUS_TIMER_OUT,
	TEST_STATUS_NOT_SUPPORT,
};

static unsigned int ufs_test_rate(uint64_t bytes, struct timespec *ts)
{
	uint64_t ns;

	ns = ts->tv_sec;
	ns *= 1000000000;
	ns += ts->tv_nsec;

	bytes *= 1000000000;

	while (ns > UINT_MAX) {
		bytes >>= 1;
		ns >>= 1;
	}

	if (!ns)
		return 0;
	do_div(bytes, (uint32_t) ns);

	return bytes;
}

static void ufs_test_print_rate(uint64_t bytes,
				struct timespec *ts1, struct timespec *ts2)
{
	unsigned int rate, iops, sectors = bytes >> 9;
	struct timespec ts;

	ts = timespec_sub(*ts2, *ts1);

	rate = ufs_test_rate(bytes, &ts);
	iops = ufs_test_rate(100, &ts);	/* I/O ops per sec x 100 */
	pr_info("Transfer of %u sectors (%u%s KiB) took %lu.%09lu"
			"seconds (%u kB/s, %u KiB/s, %u.%02u IOPS)\n",
			sectors, sectors >> 1,
			(sectors & 1 ? ".5" : ""), (unsigned long)ts.tv_sec,
			(unsigned long)ts.tv_nsec, rate / 1000, rate / 1024,
			iops / 100, iops % 100);
}

static int __find_substr(char *str, char *substr, char **endstr)
{
	char *pStr, *pDst;

	pStr = str;
	pDst = substr;
	while (*pStr == ' ') {
		pStr++;
	};

	/* End of string */
	if (*pStr == '\0')
		return 1;

	while (*pStr != ' ') {
		*pDst = *pStr;
		if (*pStr == '\0')
			break;
		pStr++;
		pDst++;
	};
	*pDst = 0;
	*endstr = pStr;
	return 0;
}

static int ufs_test_prepare(struct ufs_test *test)
{
	u8 *desc_buf;
	int qLogicalBlockCount;
	int buf_len = QUERY_DESC_UNIT_MAX_SIZE;
	int i;
	int err;

	desc_buf = kmalloc(sizeof(u8 *) * QUERY_DESC_UNIT_MAX_SIZE, GFP_KERNEL);
	if (!desc_buf)
		return -ENOMEM;
	memset(desc_buf, 0, QUERY_DESC_UNIT_MAX_SIZE);

	for (i = 0; i < UFS_UPIU_MAX_GENERAL_LUN; i++) {
		err = ufshcd_query_descriptor_retry(test->hba,
						  UPIU_QUERY_OPCODE_READ_DESC,
						  QUERY_DESC_IDN_UNIT, i, 0,
						  desc_buf, &buf_len);
		if (!err) {
			qLogicalBlockCount = get_unaligned_be64(&desc_buf[11]);
			test->lun_max_lba[i] = qLogicalBlockCount;
			if (test->max_addr < qLogicalBlockCount) {
				test->max_addr = qLogicalBlockCount;
				test->g_lun = i;
		    }
		} else{
			kfree(desc_buf);
			return err;
		}
	}
	kfree(desc_buf);
	if (test->max_addr < BLOCK_COUNT * 32)
		return -ENOMEM;

	if (test->g_start_addr == 0)
		test->g_start_addr = test->max_addr - BLOCK_COUNT * 32;

	if (test->g_length == 0)
		test->g_length = BLOCK_COUNT;

	if ((test->g_start_addr +
	     (test->g_length + BLOCK_COUNT - 1) / BLOCK_COUNT) >=
	    test->max_addr)
		err = TEST_STATUS_PARAM_ERR;

	return err;
}

void dump_sense_buffer(char *buf, int buf_len)
{
	int index = 0;

	pr_info("----Sense buffer----");
	for (index = 0; index < buf_len; index++)
		pr_info("buf[%d] = %x", index, buf[index]);
	pr_info("----end of buffer---");
}

unsigned long ufs_test_random(void)
{
	static unsigned long ufs_test_rand;

	ufs_test_rand = jiffies;
	/* See "Numerical Recipes in C", second edition, p. 284 */
	ufs_test_rand = ufs_test_rand * 1664525L + 1013904223L;
	return ufs_test_rand;
}

void check_condition_err(struct scsi_cmnd *cmd)
{
	int sense_valid = 0;
	struct scsi_sense_hdr sshdr;

	sense_valid = scsi_command_normalize_sense(cmd, &sshdr);
	switch (sshdr.sense_key) {
	case NO_SENSE:
		pr_info("No additional info or no error");
		break;
	case RECOVERED_ERROR:
		pr_info("Cmd complete success with some revovery action");
		break;
	case NOT_READY:
		pr_info("Lun is not accessible");
		break;
	case MEDIUM_ERROR:
		pr_info("Medium_err cause this fail, Just like ECC err");
		break;
	case HARDWARE_ERROR:
		pr_info("Hardware_err cause this fail");
		break;
	case ILLEGAL_REQUEST:
		pr_info("Your device is not support this scsi cmd or"
				"your paramters in your cdb is wrong");
		break;
	case UNIT_ATTENTION:
		pr_info("Unit_attention, you need to reset or power-on");
		break;
	case DATA_PROTECT:
		pr_info("Failure due to access of protected area of medium");
		break;
	case BLANK_CHECK:
		pr_info("Not applicable for block device");
		break;
	case COPY_ABORTED:
		pr_info("Not applicable for block device");
		break;
	case ABORTED_COMMAND:
		pr_info("device aborted execution of the cmd");
		break;
	case VOLUME_OVERFLOW:
		pr_info("Failure to write all data beacuse"
				"end of range or partition");
		break;
	case MISCOMPARE:
		pr_info("Indicates source data did not"
				"match data read from medium");
		break;
	default:
		break;
	}
}

void sg_init_multi(struct scatterlist *sg, const void *buf,
		unsigned int buflen, int n)
{
	int i;
	char *p = (char *)buf;

	sg_init_table(sg, n);
	for (i = 0; i < n; i++)
		sg_set_buf(sg + i, p + buflen * i, buflen);
}

static struct completion ufs_test_completion;
static struct scsi_device ufs_test_scsi_device;

void ufs_test_done(struct scsi_cmnd *cmd)
{
	complete(&ufs_test_completion);
}

void ufs_test_init_comm_scsi_cmd(struct scsi_cmnd *cmd, struct ufs_hba *hba,
				 unsigned char *cdb,
				 unsigned char *sense_buffer)
{
	ufs_test_scsi_device.host = hba->host;
	cmd->device = &ufs_test_scsi_device;
	cmd->cmd_len = COMMAND_SIZE(cdb[0]);
	cmd->cmnd = cdb;
	cmd->sense_buffer = sense_buffer;
	cmd->scsi_done = ufs_test_done;
	cmd->request = NULL;
}

void ufs_test_init_none_dma_scsi_cmd(struct scsi_cmnd *cmd, struct ufs_hba *hba,
				     unsigned char *cdb,
				     unsigned char *sense_buffer)
{
	ufs_test_init_comm_scsi_cmd(cmd, hba, cdb, sense_buffer);

	cmd->sc_data_direction = DMA_NONE;
	cmd->sdb.table.sgl = NULL;
	cmd->sdb.table.nents = 0;
	cmd->sdb.length = SCSI_SENSE_BUF_LEN;
}

void ufs_test_init_dma_scsi_cmd(struct scsi_cmnd *cmd, struct ufs_hba *hba,
				unsigned char *cdb, unsigned char *sense_buffer,
				enum dma_data_direction sc_data_direction,
				struct scatterlist *sglist, unsigned int nseg,
				unsigned int sg_len)
{
	ufs_test_init_comm_scsi_cmd(cmd, hba, cdb, sense_buffer);

	cmd->sc_data_direction = sc_data_direction;
	cmd->sdb.table.sgl = sglist;
	cmd->sdb.table.nents = nseg;
	cmd->sdb.length = sg_len;

	cmd->serial_number = 0;
	cmd->prot_op = SCSI_PROT_NORMAL;
	cmd->sdb.resid = 0;
	cmd->transfersize = BLOCK_COUNT;
}

void ufs_test_init_cdb(unsigned char cdb[10], int write, unsigned int block,
		       unsigned int block_cnt, enum cmdflag cmd_flag)
{
	cdb[0] = write ? WRITE_10 : READ_10;
	cdb[1] = 0;
	cdb[2] = (unsigned char)(block >> 24) & 0xff;
	cdb[3] = (unsigned char)(block >> 16) & 0xff;
	cdb[4] = (unsigned char)(block >> 8) & 0xff;
	cdb[5] = (unsigned char)block & 0xff;
	cdb[6] = cmd_flag;
	cdb[7] = (unsigned char)(block_cnt >> 8) & 0xff;
	cdb[8] = (unsigned char)block_cnt & 0xff;
	cdb[9] = 0;
}

extern int ufshcd_uic_hibern8_exit(struct ufs_hba *hba);

static int ufs_test_do_scsi_cmd(struct ufs_hba *hba, struct scsi_cmnd *cmd,
				int lun)
{
	struct ufshcd_lrb *lrbp;
	unsigned long flags;
	int tag;
	int err = 0;
	struct completion wait;

	wait_event(hba->dev_cmd.tag_wq, ufshcd_get_dev_cmd_tag(hba, &tag));

	spin_lock_irqsave(hba->host->host_lock, flags);
	if (hba->ufshcd_state != UFSHCD_STATE_OPERATIONAL) {
		err = SCSI_MLQUEUE_HOST_BUSY;
		goto out_unlock;
	}
	spin_unlock_irqrestore(hba->host->host_lock, flags);
	err = ufshcd_hold(hba, true);
	if (err) {
		pr_err("ufshcd_hold err:%d\n", err);
		err = SCSI_MLQUEUE_HOST_BUSY;
		clear_bit_unlock(tag, &hba->lrb_in_use);
		goto out;
	}
	WARN_ON(hba->clk_gating.state != CLKS_ON);
	lrbp = &hba->lrb[tag];

	WARN_ON(lrbp->cmd);
	lrbp->cmd = cmd;
	lrbp->sense_bufflen = UFSHCD_REQ_SENSE_SIZE;
	lrbp->sense_buffer = cmd->sense_buffer;
	lrbp->task_tag = tag;
	lrbp->lun = lun;
	lrbp->intr_cmd = !ufshcd_is_intr_aggr_allowed(hba) ? true : false;
	lrbp->command_type = UTP_CMD_TYPE_SCSI;

	hba->dev_cmd.complete = &wait;

	/* form UPIU before issuing the command */
	ufshcd_compose_upiu(hba, lrbp);
	err = ufshcd_map_sg(lrbp);
	if (err) {
		pr_err("ufshcd_map_sg err:%d##\n", err);
		lrbp->cmd = NULL;
		clear_bit_unlock(tag, &hba->lrb_in_use);
		ufshcd_release(hba);
		goto out;
	}
	/* Make sure descriptors are ready before ringing the doorbell */
	wmb();

	if (ufshcd_is_link_hibern8(hba) && !ufshcd_uic_hibern8_exit(hba))
		ufshcd_set_link_active(hba);
	/* issue command to the controller */
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_send_command(hba, tag);
out_unlock:
	spin_unlock_irqrestore(hba->host->host_lock, flags);
out:
	wake_up(&hba->dev_cmd.tag_wq);
	return err;
}

static int ufs_test_simple_transfer(struct ufs_hba *hba, int block,
				    int block_cnt, int rw_flag,
				    enum cmdflag cmd_flag, int lun)
{
	struct scsi_cmnd *cmd;
	int err = 0;
	struct scatterlist *sglist = NULL;
	unsigned char *buf;
	unsigned char cdb[10] = { 0 };
	struct scsi_device *sdp = hba->sdev_ufs_device;
	char sense_buf[SCSI_SENSE_BUFFERSIZE] = { 0 };
	int i;
	enum dma_data_direction direction;
	struct scsi_device *sdev;

	if (rw_flag)
		direction = DMA_TO_DEVICE;
	else
		direction = DMA_FROM_DEVICE;

	cmd = scsi_get_command(sdp, GFP_ATOMIC);

	ufs_test_init_cdb(cdb, rw_flag, block, block_cnt, cmd_flag);

	buf =
	    kmalloc(BLOCK_COUNT * block_cnt + UFSHCD_REQ_SENSE_SIZE,
		    GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	sglist = kmalloc(block_cnt * sizeof(struct scatterlist), GFP_KERNEL);
	if (!sglist) {
		kfree(buf);
		return -ENOMEM;
	}
	memset(buf, 0, (BLOCK_COUNT * block_cnt + UFSHCD_REQ_SENSE_SIZE));

	sg_init_multi(sglist, buf, BLOCK_COUNT, block_cnt);

	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, direction, sglist,
				   block_cnt, BLOCK_COUNT * block_cnt);

	__shost_for_each_device(sdev, hba->host) {
		if (lun == sdev->lun)
			cmd->device = sdev;
	}

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
		} else {
			pr_info("%s Fail, cmd_result:0x%x,lun:%d"
					"the error reason is:",
					__func__, cmd->result, lun);
			check_condition_err(cmd);
			err = TEST_STATUS_CMD_ERR;
		}
	} else {
		pr_info("%s wait_for_completion_io_timeout time out\n",
			__func__);
		err = -ETIME;
	}

	kfree(sglist);
	kfree(buf);
	return err;
}

static int ufs_scsi_test_unit_ready_do(struct ufs_hba *hba, int lun)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	char cdb[] = {
		TEST_UNIT_READY, 0, 0, 0, 0, 0,
	};
	char buf[SCSI_SENSE_BUF_LEN] = { 0 };
	int i;

	init_completion(&ufs_test_completion);
	ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, buf);
	if (!cmd)
		pr_err("init_basic_scsi_cmd faild");

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			pr_info("%s ##PASS##-lun:%x", __func__, lun);
			err = TEST_STATUS_OK;
		} else {
			pr_info("%s Fail, cmd_result:0x%x,lun:%d"
					"the error reason is:",
					__func__, cmd->result, lun);
			err = TEST_STATUS_CMD_ERR;
			check_condition_err(cmd);
		}
	} else {
		pr_err("%s wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;
}

static int ufs_scsi_test_unit_ready(struct ufs_test *test)
{
	int lun[5] = {0x81, 0xD0, 0xB0, 0xC4, 0x0};
	int i, ret = 0;

	for (i = 0; i < 5; i++)
		ret = ufs_scsi_test_unit_ready_do(test->hba, lun[i]);
	return ret;
}

/* We just send an invalid start_stop_unit to *
 * check if device can send the error response*
 * Beacuse Ufs_sleep and Ufs_active mode may *
 * not change just by only one cmd. *
 * */
static int ufs_scsi_start_stop_unit(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	char cdb[] = {
		START_STOP, 0, 0, 0, 0x11, 0,};
	char buf[SCSI_SENSE_BUF_LEN] = { 0 };
	int i;
	u32 status1, status2;
	struct scsi_device *sdev;
	struct ufs_hba *hba = test->hba;

	__shost_for_each_device(sdev, hba->host) {
		if (0xD0 == sdev->lun)
			cmd->device = sdev;
	}
	err = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_READ_ATTR,
				QUERY_ATTR_IDN_POWER_MODE, 0, 0, &status1);
	pr_err("SSU-curent_state is:%02x\n", status1);

	init_completion(&ufs_test_completion);
	ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, buf);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, 0xD0);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err =
			    ufshcd_query_attr(hba_addr,
					      UPIU_QUERY_OPCODE_READ_ATTR,
					      QUERY_ATTR_IDN_POWER_MODE, 0, 0,
					      &status2);
			pr_err("SSU-after_state is:%02x\n", status2);
			if (status2 != status1) {
				err = TEST_STATUS_OK;
				pr_info("%s ***Active_mode**PASS##\n",
					__func__);
			}
		} else {
			pr_info("%s Fail, the status is:0x%x\n", __func__,
				cmd->result);
			err = TEST_STATUS_CMD_ERR;
			check_condition_err(cmd);
		}

	} else {
		pr_info("%s-wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;
}

static int ufs_scsi_send_inqury(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	char cdb[] = {
		INQUIRY, 0, 0, SCSI_INQUIRY_LEN >> 8, SCSI_INQUIRY_LEN, 0,
	};
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	char sense_buf[SCSI_INQUIRY_LEN] = { 0 };
	int i;
	struct ufs_hba *hba = test->hba;

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;
	memset(dma_buf, 0, BLOCK_COUNT);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);
	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, DMA_FROM_DEVICE,
				   sglist, nseg, BLOCK_COUNT);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (cmd->result == 0) {
			pr_info("%s ##PASS##!", __func__);
			err = TEST_STATUS_OK;
		} else
			goto out;
	} else {
		pr_info("%s-wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}
out:
	kfree(dma_buf);
	return err;
}

static int ufs_scsi_read_capacity_do(struct ufs_hba *hba, char *cdb, int lun)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	unsigned sector_size = 0;
	u8 *desc_buf;
	int buf_len = QUERY_DESC_UNIT_MAX_SIZE;
	int bLogicalBlockSize = 0, qLogicalBlockCount;
	int i;
	unsigned long long lba;

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;

	desc_buf = kmalloc(sizeof(u8 *) * QUERY_DESC_UNIT_MAX_SIZE, GFP_KERNEL);
	if (!desc_buf) {
		kfree(dma_buf);
		return -ENOMEM;
	}
	memset(dma_buf, 0, BLOCK_COUNT);
	memset(desc_buf, 0, QUERY_DESC_UNIT_MAX_SIZE);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);

	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, DMA_FROM_DEVICE,
				   sglist, nseg, BLOCK_COUNT);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		sector_size = get_unaligned_be32(&dma_buf[4]);
		if (cdb[0] == READ_CAPACITY)
			lba = get_unaligned_be32(&dma_buf[0]);
		else
			lba = get_unaligned_be64(&dma_buf[0]);

		pr_info("SCSI_Read_capacity response sucess"
				"cdb[0]:%d  lba:%llu lun:%d\n",
				cdb[0], lba, lun);
		err =
		    ufshcd_query_descriptor_retry(hba,
						  UPIU_QUERY_OPCODE_READ_DESC,
						  QUERY_DESC_IDN_UNIT, lun, 0,
						  desc_buf, &buf_len);
		if (!err) {
			bLogicalBlockSize = desc_buf[10];
			qLogicalBlockCount = get_unaligned_be64(&desc_buf[11]);
			pr_info("Query_Desc: lba:%d lun%d\n",
				qLogicalBlockCount, lun);
			if ((sector_size == (1 << bLogicalBlockSize))
			    && (lba == qLogicalBlockCount - 1))
				err = TEST_STATUS_OK;
		} else {
			kfree(dma_buf);
			kfree(desc_buf);
			return err;
		}
	} else {
		pr_err("%s-wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	kfree(dma_buf);
	kfree(desc_buf);
	return err;
}

static int ufs_scsi_read_capacity(struct ufs_test *test)
{
	int ret;
	int i;
	unsigned char cdb_10[10] = {
		READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	unsigned char cdb_16[16];

	memset(cdb_16, 0, 16);
	cdb_16[0] = SERVICE_ACTION_IN_16;
	cdb_16[1] = SAI_READ_CAPACITY_16;
	cdb_16[13] = RC_LEN;
	for (i = 0; i < 7; i++) {
		ret = ufs_scsi_read_capacity_do(test->hba, cdb_10, i);
		if (ret)
			goto out;
		ret = ufs_scsi_read_capacity_do(test->hba, cdb_16, i);
		if (ret)
			goto out;
	}
out:
	return ret;
}

static int ufs_scsi_report_lun(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	char cdb[] = {
		REPORT_LUNS, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0,
	};
	char buf[8] = { 0 };
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	int i;
	struct ufs_hba *hba = test->hba;

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;

	memset(dma_buf, 0, BLOCK_COUNT);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);
	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, buf, DMA_FROM_DEVICE, sglist,
				   nseg, BLOCK_COUNT);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
			pr_info("%s ##PASS##!", __func__);
		} else {
			pr_info("%s cmd_result:0x%x the error reason is:",
				__func__, cmd->result);
			check_condition_err(cmd);
			err = TEST_STATUS_CMD_ERR;
		}
    } else {
		pr_info("%s-wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;
}

static int ufs_scsi_mode_sense(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[MAX_CDB_SIZE];
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	char sense_buf[SCSI_INQUIRY_LEN] = {0};
	int i;
	struct ufs_hba *hba = test->hba;

	memset(&cdb[0], 0, MAX_CDB_SIZE);

	cdb[0] = MODE_SENSE_10;
	cdb[1] = 0x18;
	cdb[2] = 0xa;
	put_unaligned_be16(0x1C, &cdb[7]);

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;
	memset(dma_buf, 0, BLOCK_COUNT);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);
	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, DMA_FROM_DEVICE,
				   sglist, nseg, BLOCK_COUNT);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
			pr_info("%s ##PASS##!", __func__);
		} else {
			pr_err("%s, cmd_result:0x%x the error reason is:",
			       __func__, cmd->result);
			err = TEST_STATUS_CMD_ERR;
			check_condition_err(cmd);
		}
	} else {
		pr_info("%s-wait_for_completion_io_timeout time out",
		       __func__);
		err = -ETIME;
	}
	return err;
}

static int ufs_scsi_mode_select(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[MAX_CDB_SIZE] = {0};
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	char sense_buf[SCSI_SENSE_BUFFERSIZE] = {0};
	int i;
	struct ufs_hba *hba = test->hba;

	cdb[0] = MODE_SELECT_10;
	cdb[1] = 1 << 4;
	put_unaligned_be16(0x1C, &cdb[7]);

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;
	memset(dma_buf, 0, BLOCK_COUNT);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);
	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, DMA_TO_DEVICE,
				   sglist, nseg, BLOCK_COUNT);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
			pr_info("%s ##PASS##!", __func__);
		} else {
			pr_err("%s, cmd_result:0x%x the error reason is:",
			       __func__, cmd->result);
			err = TEST_STATUS_CMD_ERR;
			check_condition_err(cmd);
		}
	} else {
		pr_info("%s-wait_for_completion_io_timeout time out",
		       __func__);
		err = -ETIME;
	}
	return 0;
}
static int ufs_scsi_sync_cache(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[MAX_CDB_SIZE];
	int blk_cnt = 1;
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	int i;
	struct ufs_hba *hba = test->hba;

	memset(&cdb[0], 0, MAX_CDB_SIZE);

	cdb[0] = SYNCHRONIZE_CACHE;
	cdb[7] = (unsigned char)(blk_cnt >> 8) & 0xff;
	cdb[8] = (unsigned char)(blk_cnt) & 0xff;

	init_completion(&ufs_test_completion);

	ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, sense_buf);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
			pr_info("%s ##PASS##!", __func__);
		} else {
			pr_info("%s Fail, cmd_result:0x%x", __func__,
				cmd->result);
			check_condition_err(cmd);
			err = TEST_STATUS_CMD_ERR;
		}
	} else {
		pr_info("%s-wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;
}

static int ufs_scsi_verify(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[MAX_CDB_SIZE];
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	int i;
	int block;
	int block_cnt = 1;
	struct ufs_hba *hba = test->hba;

	block = test->g_start_addr;
	memset(&cdb[0], 0, MAX_CDB_SIZE);

	cdb[0] = VERIFY;
	cdb[2] = (unsigned char)(block >> 24) & 0xff;
	cdb[3] = (unsigned char)(block >> 16) & 0xff;
	cdb[4] = (unsigned char)(block >> 8) & 0xff;
	cdb[5] = (unsigned char)block & 0xff;
	cdb[7] = (unsigned char)(block_cnt >> 8) & 0xff;
	cdb[8] = (unsigned char)block_cnt & 0xff;

	init_completion(&ufs_test_completion);

	ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, sense_buf);

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
			pr_info("%s ##PASS##!", __func__);
		} else {
			pr_info("%s Fail, cmd_result:0x%x", __func__,
				cmd->result);
			err = TEST_STATUS_CMD_ERR;
			check_condition_err(cmd);
		}
	} else {
		pr_info("%s-wait_for_completion_io_timeout time out",
		       __func__);
		err = -ETIME;
	}

	return err;
}

static int ufs_scsi_request_sense(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[MAX_COMMAND_SIZE];
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	int i;
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	struct ufs_hba *hba = test->hba;

	memset(&cdb[0], 0, MAX_COMMAND_SIZE);
	cdb[0] = REQUEST_SENSE;
	cdb[4] = UFSHCD_REQ_SENSE_SIZE;

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;
	memset(dma_buf, 0, BLOCK_COUNT);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);
	init_completion(&ufs_test_completion);

	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, DMA_FROM_DEVICE,
				   sglist, nseg, BLOCK_COUNT);
	if (!cmd)
		pr_info("init_basic_scsi_cmd failed");

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			err = TEST_STATUS_OK;
			pr_info("%s ##PASS##!", __func__);
		} else {
			pr_info("%s Fail, cmd_result:0x%x", __func__,
				cmd->result);
			err = TEST_STATUS_CMD_ERR;
			check_condition_err(cmd);
		}
	} else {
		pr_info("ufs_test-wait_for_completion_io_timeout time out");
		err = -ETIME;
	}

	return err;
}

struct inqury_pro_param {
	u8 evpd;
	u8 page_code;
	int alloc_len;
	u8 control;
	u8 result[3];
};

struct inquiry_cmd {
	unsigned int evpd;
	unsigned int page_code;
	unsigned int alloc_len;
	unsigned int control;
};

struct inquiry_rsp {
	unsigned int rsp_len;
	unsigned int response;
	unsigned int status;
	unsigned int sense_key;
	unsigned int add_sense_code;
};

struct inquiry_info {
	struct inquiry_cmd cmd;
	struct inquiry_rsp rsp;
};

static int ufs_test_do_inquiry(struct ufs_hba *hba,
		struct inquiry_info *msg, int lun)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	struct scatterlist st_sglist, *sglist = &st_sglist;
	int err = 0;
	unsigned char cdb[MAX_COMMAND_SIZE] = {0};
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	unsigned int nseg = 1;
	unsigned char *dma_buf;

	/* init scsi cmnd */
	cdb[0] = INQUIRY;
	cdb[1] = msg->cmd.evpd;	/* Query VPD */
	cdb[2] = msg->cmd.page_code;	/* Page Code */
	cdb[3] = (msg->cmd.alloc_len >> 8) & 0xff;
	cdb[4] = (msg->cmd.alloc_len & 0xff);
	cdb[5] = msg->cmd.control;

	init_completion(&ufs_test_completion);

	dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
	if (!dma_buf)
		return -ENOMEM;
	memset(dma_buf, 0, BLOCK_COUNT);

	sg_init_one(sglist, dma_buf, BLOCK_COUNT);
	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf,
					DMA_FROM_DEVICE, sglist, nseg,
					BLOCK_COUNT);
	if (!cmd)
		pr_info("init_basic_scsi_cmd failed");

	err = ufs_test_do_scsi_cmd(hba, cmd, lun);

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (cmd->result == 0) {
			pr_info("%s success!", __func__);
			err = TEST_STATUS_OK;
		} else {
			pr_info
			    ("%s Fail, cmd_result:0x%x,error resp is:",
			     __func__, cmd->result);
			check_condition_err(cmd);
			goto out;
		}
	} else {
		pr_info("%s wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}
out:
	return err;
}

struct inquiry_info inquiry_test_cases[] = {
	{{0, 0, 36, 0}, {36, 0, 0, 0, 0} },
	{{0, 0x83, 36, 0}, {0, 0, 0, 0, 0} },
	{{0, 0, 37, 0}, {36, 0, 0, 0, 0} },
	{{0, 0, 35, 0}, {35, 0, 0, 0, 0} },
};

static int ufs_test_protocol_inquiry(struct ufs_test *test)
{
	int i;
	int err;
	int result = 0;

	for (i = 0; i < ARRAY_SIZE(inquiry_test_cases); i++) {
		err = ufs_test_do_inquiry(test->hba,
				&inquiry_test_cases[i], test->g_lun);
		result += err;
		if (err)
			printk
			    ("inquiry_protocol failed, index:%d,err: 0x%x\n",
			     i, err);
	}

	return result;
}

struct mode_sense_msg {
	int pc;
	int page_code;
	int sub_page_code;
	int len;
};
static int ufs_test_mode_sense(struct ufs_hba *hba, struct mode_sense_msg *msg,
			       unsigned char *sense_buffer)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[MAX_COMMAND_SIZE] = { 0 };
	char buf[SCSI_SENSE_BUF_LEN] = { 0 };

	/* init scsi cmnd */
	cdb[0] = MODE_SENSE;
	cdb[1] = (unsigned char)0x80;
	cdb[2] = (unsigned char)((msg->pc & 3) << 5) | (msg->page_code & 0x3f);
	cdb[3] = (unsigned char)msg->sub_page_code;
	cdb[7] = (unsigned char)((msg->pc >> 8) & 0xff);
	cdb[8] = (unsigned char)(msg->pc & 0xff);

	init_completion(&ufs_test_completion);

	ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, buf);
	if (!cmd)
		pr_err("init_basic_scsi_cmd failed");

	err = ufs_test_do_scsi_cmd(hba, cmd, 0);

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result)
			pr_info("Protocol_Mode_Sense cmd Success!");
	} else {
		pr_err("%s wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;
}

int ufs_test_protocol_mode_sense(struct ufs_test *test)
{
	int i;
	int err;
	struct scsi_sense_hdr sshdr;
	unsigned char sense_buffer[SCSI_SENSE_BUFFERSIZE] = { 0 };
	struct mode_sense_msg msgs[] = {
		{0, 0xa, 0, 0},};
	struct ufs_hba *hba = test->hba;
	struct mode_sense_msg chk_condition_msgs[] = {
		{0, 2, 0, 0x1c},
		{1, 2, 0, 0x1c},
		{2, 2, 0, 0x1c},
		{3, 2, 0, 0x1c},
		{0, 0xa, 1, 0x1c},
	};

    for (i = 0; i < ARRAY_SIZE(msgs); i++) {
		err = ufs_test_mode_sense(hba, &msgs[i], sense_buffer);
		if (err)
			return i;
	}

	for (i = 0; i < ARRAY_SIZE(chk_condition_msgs); i++) {
		err =
		    ufs_test_mode_sense(hba, &chk_condition_msgs[i],
					sense_buffer);
		if (err != SAM_STAT_CHECK_CONDITION)
			return i;
		else {
			scsi_normalize_sense(sense_buffer,
					     SCSI_SENSE_BUFFERSIZE, &sshdr);
			pr_info("sense_key: 0x%x, asc: 0x%x", sshdr.sense_key,
			       sshdr.asc);
			if (sshdr.sense_key != ILLEGAL_REQUEST
			    || ((sshdr.asc != 0x24) && (sshdr.asc != 0x0)))
				return i;
		}
	}

	return 0;
}

static int ufs_scsi_basic_process(struct ufs_hba *hba, unsigned char *cdb,
				  int dma_direction, int lun)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned char *dma_buf;
	int i;
	struct scsi_device *sdev;

	init_completion(&ufs_test_completion);

	if (DMA_NONE == dma_direction)
		ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, sense_buf);
	else {
		dma_buf = kmalloc(BLOCK_COUNT, GFP_KERNEL);
		if (!dma_buf)
			return -ENOMEM;
		memset(dma_buf, 0, BLOCK_COUNT);

		sg_init_one(sglist, dma_buf, BLOCK_COUNT);
		ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf,
					   dma_direction, sglist, nseg,
					   BLOCK_COUNT);
	}
	__shost_for_each_device(sdev, hba->host) {
		if (lun == sdev->lun)
			cmd->device = sdev;
	}

	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (0 == cmd->result) {
			pr_info("%s success!", __func__);
			err = TEST_STATUS_OK;
		} else {
			pr_info("cmd Fail, cmd_result:0x%x,%x:%d", cmd->result,
				cdb[0], (cdb[4] >> 4));
			check_condition_err(cmd);
			err = TEST_STATUS_CMD_ERR;
		}
	} else {
		pr_info("%s wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;
}

static int ufs_test_protocol_report_lun(struct ufs_test *test)
{
	int i, ret;
	unsigned char cdb[6][12] = {
		{REPORT_LUNS, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0},
		{REPORT_LUNS, 0, 0, 0, 0, 0, 0x48, 0, 0, 0, 0, 0},
		{REPORT_LUNS, 0, 1, 0, 0, 0, 0x28, 0, 0, 0, 0, 0},
		{REPORT_LUNS, 0, 3, 0, 0, 0, 0x68, 0, 0, 0, 0, 0},
		{REPORT_LUNS, 0, 1, 0, 0, 0, 0x0F, 0, 0, 0, 0, 0},
		{REPORT_LUNS, 0, 1, 0, 0, 0, 0x20, 0, 0, 0, 0, 0},
	};

	for (i = 0; i < 6; i++)
		ret =
		    ufs_scsi_basic_process(test->hba, cdb[i], DMA_FROM_DEVICE,
					   test->g_lun);

	return ret;
}

static int ufs_test_protocol_sync_cache(struct ufs_test *test)
{
	int i, ret;
	unsigned char cdb[5][10] = {
		{SYNCHRONIZE_CACHE, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{SYNCHRONIZE_CACHE, (1 << 2), 0, 0, 0, 0, 0, 0, 1, 0},
		{SYNCHRONIZE_CACHE, (1 << 1), 0, 0, 0, 0, 0, 0, 1, 0},
		{SYNCHRONIZE_CACHE, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	for (i = 0; i < 5; i++)
		ret = ufs_scsi_basic_process(test->hba,
					cdb[i], DMA_NONE, test->g_lun);

	return ret;
}

static int ufs_test_protocol_start_stop_unit(struct ufs_test *test)
{
	int i, ret;
	unsigned char cdb[5][6] = {
		{START_STOP, 0, 0, 0, 0, 0},
		{START_STOP, 1, 0, 0, 0, 0},
		{START_STOP, 0, 0, 0, 1, 0},
		{START_STOP, 1, 0, 0, 1, 0},
		{START_STOP, 0, 0, 0, 0x41, 0},/*Sleep power mode*/
	};

	for (i = 0; i < 4; i++)
		ret = ufs_scsi_basic_process(test->hba,
					cdb[i], DMA_NONE, test->g_lun);

	if (ret)
		ufs_scsi_start_stop_unit(test);

	return ret;
}

static int ufs_test_protocol_verify(struct ufs_test *test)
{
	int i, ret;
	unsigned char cdb[2][10] = {
		{VERIFY, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{VERIFY, 0, 0, 0, 0, 0, 0, 0, 0xA, 0},
	};

	for (i = 0; i < 2; i++)
		ret = ufs_scsi_basic_process(test->hba, cdb[i], DMA_NONE, 2);

	ret = ufs_scsi_read_capacity(test);
	return ret;
}

static int dump_and_check_lun_info(struct ufs_test *test)
{
	u8 *unit_buf, *geometry_buf;
	int unit_len, geometry_len;
	int err;
	int bLogicalBlockSize, bMinAddrBlockSize, bMaxOutBufferSize,
	    bMaxInBufferSize, qLogicalBlockCount;
	int rpmb_bLogicalBlockSize;
	int i, lb_len;

	unit_len = QUERY_DESC_UNIT_MAX_SIZE;
	unit_buf = kmalloc(sizeof(u8 *) * QUERY_DESC_UNIT_MAX_SIZE, GFP_KERNEL);
	if (!unit_buf)
		return -ENOMEM;

	geometry_len = QUERY_DESC_GEOMETRY_MAZ_SIZE;
	geometry_buf =
	    kmalloc(sizeof(u8 *) * QUERY_DESC_GEOMETRY_MAZ_SIZE, GFP_KERNEL);
	if (!geometry_buf) {
		kfree(unit_buf);
		return -ENOMEM;
	}
	for (i = 0; i < 7; i++) {
		err = ufshcd_query_descriptor_retry(hba_addr,
						  UPIU_QUERY_OPCODE_READ_DESC,
						  QUERY_DESC_IDN_UNIT, i, 0,
						  unit_buf, &unit_len);

		if (!err) {
			bLogicalBlockSize = unit_buf[10];
			pr_info("##Logical_lun##-unit_len:%d lun:%d size:%d\n",
			       unit_len, i, bLogicalBlockSize);
		} else {
			kfree(unit_buf);
			kfree(geometry_buf);
			return err;
		}
	}

	err = ufshcd_query_descriptor_retry(hba_addr,
					UPIU_QUERY_OPCODE_READ_DESC,
					QUERY_DESC_IDN_UNIT, 0xC4, 0,
					unit_buf, &unit_len);

	if (!err) {
		rpmb_bLogicalBlockSize = 1 << unit_buf[10];
		qLogicalBlockCount = get_unaligned_be64(&unit_buf[11]);
		pr_info
		    ("##RPMB_lun##-unit_len:%d size:%d qLogicalBlockCount:%d\n",
		     unit_len, rpmb_bLogicalBlockSize, qLogicalBlockCount);
	} else {
		kfree(unit_buf);
		kfree(geometry_buf);
		return err;
	}
	err = ufshcd_query_descriptor_retry(hba_addr,
					UPIU_QUERY_OPCODE_READ_DESC,
					QUERY_DESC_IDN_GEOMETRY, 0, 0,
					geometry_buf, &geometry_len);
	if (!err) {
		bMinAddrBlockSize = geometry_buf[18];
		bMaxInBufferSize = geometry_buf[21];
		bMaxOutBufferSize = geometry_buf[22];
	} else {
		kfree(geometry_buf);
		return err;
	}
	lb_len = 1 << bLogicalBlockSize;
	if ((lb_len > (bMinAddrBlockSize * 512))
	    && (lb_len < (bMaxInBufferSize * 512))
	    && (lb_len < (bMaxOutBufferSize * 512)))
		err = TEST_STATUS_OK;

	return err;
}

static int check_and_test_bkops(struct ufs_test *test)
{
	int ret;
	bool flag;
	u32 attr;
	u32 status;
	struct ufs_hba *hba = test->hba;

	ret = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_READ_ATTR,
				QUERY_ATTR_IDN_EE_STATUS, 0, 0, &status);

	status &= hba->ee_ctrl_mask;

	if (status & MASK_EE_URGENT_BKOPS)
		pr_info
		    ("Bkops Urgent Exception Event is opened.");

	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_READ_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, &flag);
	if (ret)
		return 0;
	if (0 == flag)
		pr_info("Bkops is not enable, We will enable it later");
	if (1 == flag)
		pr_info("Bkops is enable, We will close it later");

	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_SET_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, &flag);
	if (ret)
		return 0;
	/*check the bkops_status */
	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_READ_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, &flag);
	if (ret)
		return 0;

	ret = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_READ_ATTR,
				QUERY_ATTR_IDN_BKOPS_STATUS, 0, 0, &attr);
	switch (attr) {
	case 0:
		pr_info("Bkops Status : Not required");
		break;
	case 1:
		pr_info("Bkops Status : Required, not critical");
		break;
	case 2:
		pr_info("Bkops Status : Required, performance impact");
		break;
	case 3:
		pr_info("Bkops Status : Critical");
		break;
	default:
		break;
	}
	/*clear the Bkops flag which we just wrote in */
	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_CLEAR_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, NULL);
	if (ret)
		return 0;

	return 0;
}

static int ufs_test_ssu_powerdown(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	char buf[SCSI_SENSE_BUF_LEN];
	char cdb[] = {
		START_STOP, 0, 0, 0, (UFS_POWERDOWN_PWR_MODE << 4), 0,};
	unsigned int status;
	struct ufs_hba *hba = test->hba;

	err = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_READ_ATTR,
				QUERY_ATTR_IDN_POWER_MODE, 0, 0, &status);
	pr_err("SSU-curent_state is:%02x lun:%d\n", status, test->g_lun);

	init_completion(&ufs_test_completion);

	ufs_test_init_none_dma_scsi_cmd(cmd, hba, cdb, buf);
	if (!cmd)
		pr_err("init_basic_scsi_cmd failed");

	err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		err = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_READ_ATTR,
					QUERY_ATTR_IDN_POWER_MODE, 0, 0,
					&status);
		pr_err("SSU Success-after_state is:%02x\n", status);
	} else {
		pr_info("%s wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}
	ufs_scsi_start_stop_unit(test);
    return err;
}

static int ufs_test_contextID_info(struct ufs_test *test)
{
	int ret;
	u32 status;
	u8 *desc_buf;
	u8 *unit_buf;
	int buf_len;
	int i;
	u32 val;
	int block = test->g_start_addr;
	struct ufs_hba *hba = test->hba;

	for (i = 0; i < 6; i++) {
		ret = ufshcd_query_attr(hba, UPIU_QUERY_OPCODE_READ_ATTR,
					QUERY_ATTR_IDN_CNTX_CONF, i, 0,
					&status);
		pr_info("Context_Attr_status:%x", status);
	}

	buf_len = QUERY_DESC_GEOMETRY_MAZ_SIZE;
	desc_buf =
	    kmalloc(sizeof(u8 *) * QUERY_DESC_GEOMETRY_MAZ_SIZE, GFP_KERNEL);
	if (!desc_buf)
		return -ENOMEM;

	ret = ufshcd_query_descriptor_retry(hba, UPIU_QUERY_OPCODE_READ_DESC,
					    QUERY_DESC_IDN_GEOMETRY, 0, 0,
					    desc_buf, &buf_len);

	pr_info("This device can support the max Context_ID number id: %d",
		desc_buf[26]);

	buf_len = QUERY_DESC_UNIT_MAX_SIZE;
	unit_buf = kmalloc(sizeof(u8 *) * QUERY_DESC_UNIT_MAX_SIZE, GFP_KERNEL);
	if (!unit_buf) {
		kfree(desc_buf);
		return -ENOMEM;
	}
	ret = ufshcd_query_descriptor_retry(hba, UPIU_QUERY_OPCODE_READ_DESC,
					    QUERY_DESC_IDN_UNIT, 0, 0, unit_buf,
					    &buf_len);

	unit_buf[32] = 0x1;
	ret = ufshcd_query_descriptor_retry(hba, UPIU_QUERY_OPCODE_WRITE_DESC,
					    QUERY_DESC_IDN_UNIT, 0, 0, unit_buf,
					    &buf_len);

	pr_info(" enable wConfig Context_Attr_status");
	val = 0x3;
	val &= 0xFFFF;
	ret = ufshcd_query_attr(hba, UPIU_QUERY_OPCODE_WRITE_ATTR,
				QUERY_ATTR_IDN_CNTX_CONF, 0, 1, &val);

	ret = ufshcd_query_attr(hba, UPIU_QUERY_OPCODE_READ_ATTR,
				QUERY_ATTR_IDN_CNTX_CONF, 0, 1, &status);
	pr_info("After enable wConfig Context_Attr_status:%x", status);

	ufs_test_simple_transfer(hba, block, 1, WRITE, CONTEXT_ID, test->g_lun);
	pr_info("ufs_test-Read_after_Write");
	msleep(1000);
	ufs_test_simple_transfer(hba, block, 1, READ, CONTEXT_ID, test->g_lun);

	unit_buf[32] = 0;
	ret = ufshcd_query_descriptor_retry(hba, UPIU_QUERY_OPCODE_WRITE_DESC,
					    QUERY_DESC_IDN_UNIT, 0, 0, unit_buf,
					    &buf_len);
	kfree(desc_buf);
	kfree(unit_buf);
	return 0;
}

static int ufs_test_system_data_tag(struct ufs_test *test)
{
	int ret;
	u8 *desc_buf;
	int buf_len;
	struct ufs_hba *hba = test->hba;

	buf_len = QUERY_DESC_GEOMETRY_MAZ_SIZE;
	desc_buf =
	    kmalloc(sizeof(u8 *) * QUERY_DESC_GEOMETRY_MAZ_SIZE, GFP_KERNEL);
	if (!desc_buf)
		return -ENOMEM;

	ret = ufshcd_query_descriptor_retry(hba, UPIU_QUERY_OPCODE_READ_DESC,
					    QUERY_DESC_IDN_GEOMETRY, 0, 0,
					    desc_buf, &buf_len);
	if (ret)
		goto out;

	pr_info("bSysDataTagUnitSize:%d,bSysDataTagResSize:%d,", desc_buf[27],
		desc_buf[28]);
	pr_info("System data tag Unit_size is:%d,max system data eare is:%d",
		(desc_buf[18] * 512), desc_buf[28]);

	ret =
	    ufs_test_simple_transfer(hba, test->g_start_addr, 1, WRITE, SYSDTAG,
				     test->g_lun);

out:
	return 0;
}

static int ufs_test_erase_or_discard(struct ufs_test *test)
{
	struct scsi_cmnd st_cmd, *cmd = &st_cmd;
	int err = 0;
	unsigned char cdb[10] = { 0 };
	char sense_buf[UFSHCD_REQ_SENSE_SIZE] = { 0 };
	int i;
	struct scatterlist st_sglist, *sglist = &st_sglist;
	unsigned int nseg = 1;
	unsigned int len = 24;
	char buf[24] = { 0 };
	int block = test->g_start_addr;
	struct ufs_hba *hba = test->hba;
	struct scsi_device *sdev;

	cdb[0] = UNMAP;
	cdb[8] = len;

	put_unaligned_be16(len - 2, &buf[0]);
	put_unaligned_be16(16, &buf[2]);
	put_unaligned_be64(block, &buf[8]);
	put_unaligned_be32(1, &buf[16]);

	sg_init_one(sglist, buf, len);


	ufs_test_init_dma_scsi_cmd(cmd, hba, cdb, sense_buf, DMA_TO_DEVICE,
				   sglist, nseg, len);
	if (!cmd)
		pr_info("init_basic_scsi_cmd failed\n");
	__shost_for_each_device(sdev, hba->host) {
		if (test->g_lun == sdev->lun)
			cmd->device = sdev;
	}
	init_completion(&ufs_test_completion);
	for (i = 0; i < 1000; i++) {
		msleep(3);
		err = ufs_test_do_scsi_cmd(hba, cmd, test->g_lun);
		if (!err)
			break;
	}

	if (0 !=
	    wait_for_completion_io_timeout(&ufs_test_completion,
					   msecs_to_jiffies(1000))) {
		if (cmd->result == 0) {
			pr_info("%s ##PASS##!", __func__);
			err = TEST_STATUS_OK;
		} else {
			pr_info("%s Fail, cmd_result:0x%x\n", __func__,
			       cmd->result);
			err = TEST_STATUS_CMD_ERR;
		}
	} else {
		pr_info("%s wait_for_completion_io_timeout time out\n",
		       __func__);
		err = -ETIME;
	}

	return err;

}

static int ufs_test_health_report(struct ufs_test *test)
{
	int err = 0;
	int buff_len = QUERY_DESC_HEALTH_MAX_SIZE;
	u8 *desc_buf = NULL;

	desc_buf = kzalloc(buff_len, GFP_KERNEL);
	if (!desc_buf)
		return -ENOMEM;

	err =
	    ufshcd_query_descriptor_retry(test->hba,
					  UPIU_QUERY_OPCODE_READ_DESC, 0x09, 0,
					  0, desc_buf, &buff_len);

	if (!err) {
		err = TEST_STATUS_OK;
	    dump_sense_buffer(desc_buf, buff_len);
    } else
		err = TEST_STATUS_CMD_ERR;

	return err;
}

static int ufs_test_simple_read(struct ufs_test *test)
{
	int ret;

	ret =
	    ufs_test_simple_transfer(test->hba, test->g_start_addr, 1, READ,
				     CMDNONE, test->g_lun);

	return ret;
}

static int ufs_test_sequence_read(struct ufs_test *test)
{
	int ret = 0;
	struct timespec ts1, ts2, ts;
	int blk_cnt = (test->g_length + BLOCK_COUNT - 1) / BLOCK_COUNT;
	int i;

	pr_err("%s : start addr:%ld, length:%ld blk_cnt:%d", __func__,
	       test->g_start_addr, test->g_length, blk_cnt);

	getnstimeofday(&ts1);

	for (i = 0; i < (blk_cnt / PRDT_SG_NUM); i++) {
		ret =
		    ufs_test_simple_transfer(test->hba,
					     (test->g_start_addr +
					      i * PRDT_SG_NUM), PRDT_SG_NUM,
					     READ, CMDNONE, test->g_lun);
	}
	if (blk_cnt % 128)
		ret =
		    ufs_test_simple_transfer(test->hba,
					     (test->g_start_addr +
					      (PRDT_SG_NUM *
					       (blk_cnt / PRDT_SG_NUM))),
					     (blk_cnt % PRDT_SG_NUM), READ,
					     CMDNONE, test->g_lun);

	getnstimeofday(&ts2);

	ts = timespec_sub(ts2, ts1);

	ufs_test_print_rate(test->g_length, &ts1, &ts2);

	return ret;
}

static int ufs_test_random_read(struct ufs_test *test)
{
	int i;
	int ret = 0;
	struct timespec ts1, ts2, ts;
	int blk_cnt = (test->g_length + BLOCK_COUNT - 1) / BLOCK_COUNT;
	int rnd_addr;

	pr_err("%s start addr:%ld, length:%ld blk_cnt:%d", __func__,
	       test->g_start_addr, test->g_length, blk_cnt);

	getnstimeofday(&ts1);

	for (i = 0; i < (blk_cnt / PRDT_SG_NUM); i++) {
		rnd_addr =
		    test->g_start_addr + ufs_test_random() % (test->max_addr -
							      test->
							      g_start_addr);
		if (rnd_addr > PRDT_SG_NUM)
			rnd_addr -= PRDT_SG_NUM;

		ret =
		    ufs_test_simple_transfer(test->hba, rnd_addr, PRDT_SG_NUM,
					     READ, CMDNONE, test->g_lun);
	}
	rnd_addr =
	    test->g_start_addr + ufs_test_random() % (test->max_addr -
						      test->g_start_addr);
	if (rnd_addr > PRDT_SG_NUM)
		rnd_addr -= PRDT_SG_NUM;
	if (blk_cnt % PRDT_SG_NUM)
		ret =
		    ufs_test_simple_transfer(test->hba, rnd_addr,
					     (blk_cnt % PRDT_SG_NUM), READ,
					     CMDNONE, test->g_lun);

	getnstimeofday(&ts2);

	ts = timespec_sub(ts2, ts1);
	ufs_test_print_rate(test->g_length, &ts1, &ts2);

	return ret;
}

static int ufs_test_simple_write(struct ufs_test *test)
{
	int ret;

	pr_err("%s start addr:%ld, length:%ld ", __func__, test->g_start_addr,
	       test->g_length);

	ret =
	    ufs_test_simple_transfer(test->hba, test->g_start_addr, 1, WRITE,
				     CMDNONE, test->g_lun);

	return ret;
}

static int ufs_test_verify_write(struct ufs_test *test)
{
	int ret;

	pr_err("%s start addr:%ld, length:%ld ", __func__, test->g_start_addr,
	       test->g_length);
	ret =
	    ufs_test_simple_transfer(test->hba, test->g_start_addr, 1, WRITE,
				     CMDNONE, test->g_lun);
	if (ret) {
		pr_err("%s-Write-Fail", __func__);
		goto out;
	}
	ret =
	    ufs_test_simple_transfer(test->hba, test->g_start_addr, 1, READ,
				     CMDNONE, test->g_lun);
	if (ret)
		pr_err("%s-READ-Fail", __func__);
out:
	return ret;
}

static int ufs_test_sequence_write(struct ufs_test *test)
{
	int ret = 0;
	struct timespec ts1, ts2, ts;
	int blk_cnt = (test->g_length + BLOCK_COUNT - 1) / BLOCK_COUNT;
	int i;

	pr_err("%s : start addr:%ld, length:%ld blk_cnt:%d", __func__,
	       test->g_start_addr, test->g_length, blk_cnt);

	getnstimeofday(&ts1);
	for (i = 0; i < (blk_cnt / PRDT_SG_NUM); i++) {
		ret =
		    ufs_test_simple_transfer(test->hba,
					     (test->g_start_addr +
					      i * PRDT_SG_NUM), PRDT_SG_NUM,
					     WRITE, CMDNONE, test->g_lun);
	}
	if (blk_cnt % 128)
		ret =
		    ufs_test_simple_transfer(test->hba,
					     (test->g_start_addr +
					      (PRDT_SG_NUM *
					       (blk_cnt / PRDT_SG_NUM))),
					     (blk_cnt % PRDT_SG_NUM), WRITE,
					     CMDNONE, test->g_lun);
	getnstimeofday(&ts2);

	ts = timespec_sub(ts2, ts1);
	ufs_test_print_rate(test->g_length, &ts1, &ts2);

	return ret;
}

static int ufs_test_random_write(struct ufs_test *test)
{
	int i;
	int ret = 0;
	struct timespec ts1, ts2, ts;
	int blk_cnt = (test->g_length + BLOCK_COUNT - 1) / BLOCK_COUNT;
	int rnd_addr;

	pr_err("%s start addr:%ld, length:%ld blk_cnt:%d", __func__,
	       test->g_start_addr, test->g_length, blk_cnt);

	getnstimeofday(&ts1);

	for (i = 0; i < (blk_cnt / PRDT_SG_NUM); i++) {
		rnd_addr =
		    test->g_start_addr + ufs_test_random() % (test->max_addr -
							      test->
							      g_start_addr);
		if (rnd_addr > PRDT_SG_NUM)
			rnd_addr -= PRDT_SG_NUM;

		ret =
		    ufs_test_simple_transfer(test->hba, rnd_addr, PRDT_SG_NUM,
					     WRITE, CMDNONE, test->g_lun);
	}
	rnd_addr =
	    test->g_start_addr + ufs_test_random() % (test->max_addr -
						      test->g_start_addr);
	if (rnd_addr > PRDT_SG_NUM)
		rnd_addr -= PRDT_SG_NUM;
	if (blk_cnt % PRDT_SG_NUM)
		ret =
		    ufs_test_simple_transfer(test->hba, rnd_addr,
					     (blk_cnt % PRDT_SG_NUM), WRITE,
					     CMDNONE, test->g_lun);

	getnstimeofday(&ts2);

	ts = timespec_sub(ts2, ts1);
	ufs_test_print_rate(test->g_length, &ts1, &ts2);

	return ret;
}

static const struct ufs_test_case ufs_scsi_cases[] = {
	/*basic_scsi_cmd: 0~7 */
	{
	 .name = "test_unit_ready_00",
	 .run = ufs_scsi_test_unit_ready,
	 },
	{
	 .name = "start_stop_unit_01",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_start_stop_unit,
	 },
	{
	 .name = "inqury_02",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_send_inqury,
	 },
	{
	 .name = "requset_sense_03",
	 .run = ufs_scsi_read_capacity,
	 },
	{
	 .name = "report_lun_04",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_report_lun,
	 },
	{
	 .name = "mode_select_05",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_mode_select,
	 },
	{
	 .name = "mode_sense_06",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_mode_sense,
	 },
	{
	 .name = "sync_cache_07",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_sync_cache,
	 },
	{
	 .name = "verify_08",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_verify,
	 },
	{
	 .name = "request_sense_09",
	 .prepare = ufs_test_prepare,
	 .run = ufs_scsi_request_sense,
	 },
	/*scsi_protocol_test:08~14 */
	{
	 .name = "protocol_inqury_test_10",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_protocol_inquiry,
	 },
	{
	 .name = "protocol_mode_sense_test_11",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_protocol_mode_sense,
	 },
	{
	 .name = "protocol_report_lun_test_12",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_protocol_report_lun,
	 },
	{
	 .name = "protocol_sync_cache_test_13",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_protocol_sync_cache,
	 },
	{
	 .name = "protocol_start_stop_unit_test_14",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_protocol_start_stop_unit,
	},
	{
	 .name = "protocol_verify_test_15",
	 .run = ufs_test_protocol_verify,
	 },
	/*basic_func_test:16~20 */
	{
	 .name = "basic_lun_test_16",
	 .run = dump_and_check_lun_info,
	 },
	{
	 .name = "basic_bkops_func_test_17",
	 .run = check_and_test_bkops,
	 },
	{
	 .name = "basic_ssu_func_test_18",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_ssu_powerdown,
	 },
	{
	 .name = "basic_context_id_test_19",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_contextID_info,
	 },
	{
	 .name = "basic_system_data_tag_test_20",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_system_data_tag,
	 },
	{
	 .name = "basic_erase_or_discard_test_21",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_erase_or_discard,
	 },
	{
	 .name = "basic_get_device_health_report_22",
	 .run = ufs_test_health_report,
	 },
	/*basic_rw_test:22~28, just read_write 128K for one slot*/
	{
	 .name = "test_read_23",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_simple_read,
	 },
	{
	 .name = "test_write_24",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_simple_write,
	 },
	{
	 .name = "test_verify_write_25",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_verify_write,
	 },
	{
	 .name = "test_seq_read_26",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_sequence_read,
	 },
	{
	 .name = "test_random_read_27",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_random_read,
	 },
	{
	 .name = "test_seq_write_28",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_sequence_write,
	 },
	{
	 .name = "test_random_write_29",
	 .prepare = ufs_test_prepare,
	 .run = ufs_test_random_write,
	 },
};

static void ufs_test_run(int testcase, struct ufs_test *test)
{
	int ret;
	int i;
	int start, end;

	if ((testcase >= 0) && (testcase < ARRAY_SIZE(ufs_scsi_cases))) {
		start = testcase;
		end = testcase + 1;
	} else if (testcase == -1) {
		start = 0;
		end = ARRAY_SIZE(ufs_scsi_cases);
		pr_info("Starting all tests ....\n");
	} else {
		pr_info("Invalid param\n");
		return;
	}

	for (i = start; i < end; i++) {
		struct ufs_test_general_result *gr;

		pr_info("Starting testcase :%d-%s...\n", i,
			ufs_scsi_cases[i].name);
		if (ufs_scsi_cases[i].prepare) {
			ret = ufs_scsi_cases[i].prepare(test);
			if (ret) {
				pr_info("%s Prepare stage failed! ret:(%d)\n",
					ufs_scsi_cases[i].name, ret);
				continue;
			}
		}

		gr = kzalloc(sizeof(struct ufs_test_general_result),
			     GFP_KERNEL);
		if (gr) {
			INIT_LIST_HEAD(&gr->tr_lst);

			/* Assign data what we know already */
			gr->testcase = i;

			/* Append container to global one */
			list_add_tail(&gr->link, &ufs_test_result);
		}

		ret = ufs_scsi_cases[i].run(test);
		/* Save the result */
		if (gr)
			gr->result = ret;

		if (ufs_scsi_cases[i].cleanup) {
			ret = ufs_scsi_cases[i].cleanup(test);
			if (ret) {
				pr_info("Warning: Cleanup stage failed! (%d)\n",
						ret);
			}
		}
	}

	pr_info(" Tests completed.\n");
}

static void ufs_test_free_result(struct ufs_test_ud *utd)
{
	struct ufs_test_general_result *gr, *grs;

	mutex_lock(&ufs_test_lock);

	list_for_each_entry_safe(gr, grs, &ufs_test_result, link) {
		struct ufs_test_transfer_result *tr, *trs;

		list_for_each_entry_safe(tr, trs, &gr->tr_lst, link) {
			list_del(&tr->link);
			kfree(tr);
		}

		list_del(&gr->link);
		kfree(gr);
	}

	mutex_unlock(&ufs_test_lock);
}

static int ufs_test_show(struct seq_file *file, void *data)
{
	struct ufs_test_general_result *gr;

	mutex_lock(&ufs_test_lock);

	list_for_each_entry(gr, &ufs_test_result, link) {
		struct ufs_test_transfer_result *tr;

		seq_printf(file, "Test %d: %d\n", gr->testcase, gr->result);

		list_for_each_entry(tr, &gr->tr_lst, link) {
			seq_printf(file, "%u %d %lu.%09lu %u %u.%02u\n",
				   tr->count, tr->sectors,
				   (unsigned long)tr->ts.tv_sec,
				   (unsigned long)tr->ts.tv_nsec,
				   tr->rate, tr->iops / 100, tr->iops % 100);
		}
	}

	mutex_unlock(&ufs_test_lock);

	return 0;
}

static int ufs_test_open(struct inode *inode, struct file *file)
{
	return single_open(file, ufs_test_show, inode->i_private);
}

static ssize_t ufs_scsi_write(struct file *file, const char __user *buf,
			      size_t count, loff_t *ppos)
{
	char lbuf[256];
	char tmp_buf[12];
	char *pStr;
	int idx;
	int ret = 0;
	long testcase;
	struct ufs_test test = { 0 };
	u32 par[8] = { 0 };

	if (count >= sizeof(lbuf))
		return -EINVAL;

	if (copy_from_user(lbuf, buf, count))
		return -EFAULT;

	pr_err("scsi_write:%d\n", (int)count);

	lbuf[count] = '\0';
	pStr = lbuf;

	ret = __find_substr(pStr, tmp_buf, &pStr);
	if (ret)
		return -EINVAL;
	if (kstrtol(tmp_buf, 10, &testcase))
		return -EINVAL;

	pr_err("testcase-id:%ld\n", testcase);

	idx = 0;
	while (0 == ret) {
		ret = __find_substr(pStr, tmp_buf, &pStr);
		if (ret)
			break;

		if (kstrtou32(tmp_buf, 10, &par[idx]))
			return -EINVAL;

		idx++;
		if (idx == 8)
			break;
	}

	test.hba = hba_addr;
	test.g_lun = par[0];
	test.g_start_addr = par[1];
	test.g_length = par[2];
	test.g_trunk_size = par[3];
	test.g_data_mode = par[4];
	test.g_cmd = par[5];
	test.g_para = par[6];
	test.g_resp = par[7];

	ufs_test_free_result(NULL);
	mutex_lock(&ufs_test_lock);
	ufs_test_run(testcase, &test);
	mutex_unlock(&ufs_test_lock);

	return count;
}

const struct file_operations ufs_scsi_fops = {
	.open = ufs_test_open,
	.read = seq_read,
	.write = ufs_scsi_write,
	.llseek = seq_lseek,
	.release = single_release,
};

struct query_flag_param {
	char *name;
	enum flag_idn idn;
};

struct query_attr_param {
	char *name;
	enum attr_idn idn;
	u8 index;
	u8 selector;
};

struct query_desc_param {
	char *name;
	enum desc_idn idn;
	u8 index;
	u8 selector;
	int buf_len;
	u8 result[3];
};

struct query_desc_param query_desc_params[] = {
	{"device", QUERY_DESC_IDN_DEVICE, 0, 0, QUERY_DESC_DEVICE_MAX_SIZE,
	 {0x40, 0x0, 0x0} },
	{"config", QUERY_DESC_IDN_CONFIGURAION, 0, 0,
	 QUERY_DESC_CONFIGURAION_MAX_SIZE, {0x90, 0x1, 0x0} },
	{"unit", QUERY_DESC_IDN_UNIT, 0, 0, QUERY_DESC_UNIT_MAX_SIZE,
	 {0x23, 0x2, 0x0} },
	{"inter", QUERY_DESC_IDN_INTERCONNECT, 0, 0, QUERY_DESC_UNIT_MAX_SIZE,
	 {0x6, 0x4, 0x1} },
	{"sting", QUERY_DESC_IDN_STRING, 0, 0, QUERY_DESC_STRING_MAX_SIZE,
	 {0x8, 0x5, 0x0} },
	{"gometry", QUERY_DESC_IDN_GEOMETRY, 0, 0, QUERY_DESC_GEOMETRY_MAZ_SIZE,
	 {0x44, 0x7, 0x0} },
	{"power", QUERY_DESC_IDN_POWER, 0, 0, QUERY_DESC_POWER_MAX_SIZE,
	 {0x62, 0x8, 0x81} },
	{"invalid", 0xFF, 0, 0, 0xFE, {0xa, 0xFF, 0x0} },
	{"wconfig", QUERY_DESC_IDN_CONFIGURAION, 0, 0,
	 QUERY_DESC_CONFIGURAION_MAX_SIZE},
	{"winvali", QUERY_DESC_IDN_CONFIGURAION, 0, 0,
	 QUERY_DESC_CONFIGURAION_MAX_SIZE},
	{"rewrite", QUERY_DESC_IDN_CONFIGURAION, 0, 0,
	 QUERY_DESC_CONFIGURAION_MAX_SIZE},
};

struct query_flag_param query_flag_params[] = {
	{"fdevInit", QUERY_FLAG_IDN_FDEVICEINIT},
	{"PermWPE", QUERY_FLAG_IDN_PERMANENT_WPE},
	{"PwrOnWPE", QUERY_FLAG_IDN_PWR_ON_WPE},
	{"BkopsOn", QUERY_FLAG_IDN_BKOPS_EN},
	{"PuregeEn", QUERY_FLAG_IDN_PURGE_ENABLE},
	{"fphyres", QUERY_FLAG_IDN_FPHYRESOURCEREMOVAL},
	{"BusyRtc", QUERY_FLAG_IDN_BUSY_RTC},
	{"invalid", 0xFF},
};

struct query_attr_param query_attr_params[] = {
	{"BootLuEn", QUERY_ATTR_IDN_BOOT_LU_EN},
	{"PwrMode", QUERY_ATTR_IDN_POWER_MODE},
	{"ActiveIcc", QUERY_ATTR_IDN_ACTIVE_ICC_LVL},
	{"DataEn", QUERY_ATTR_IDN_OOO_DATA_EN},
	{"BkopsStat", QUERY_ATTR_IDN_BKOPS_STATUS},
	{"PurgeStat", QUERY_ATTR_IDN_PURGE_STATUS},
	{"DataIn", QUERY_ATTR_IDN_MAX_DATA_IN},
	{"DataOut", QUERY_ATTR_IDN_MAX_DATA_OUT},
	{"RefClk", QUERY_ATTR_IDN_REF_CLK_FREQ},
	{"ConDesc", QUERY_ATTR_IDN_CONF_DESC_LOCK},
	{"MaxRtt", QUERY_ATTR_IDN_MAX_NUM_OF_RTT},
	{"EECon", QUERY_ATTR_IDN_EE_CONTROL},
	{"EEStat", QUERY_ATTR_IDN_EE_STATUS},
	{"SecPass", QUERY_ATTR_IDN_SECONDS_PASSED},
	{"CntxCon", QUERY_ATTR_IDN_CNTX_CONF},
	{"PrgBlkN", QUERY_ATTR_IDN_CORR_PRG_BLK_NUM},
};

int query_desc_subtype;
void query_parse_subtype(long testcase, char *subtype)
{
	int i;
	int len;

	if (testcase == 0 || testcase == 1)
		len = ARRAY_SIZE(query_desc_params);
	if (testcase == 2)
		len = ARRAY_SIZE(query_flag_params);
	if (testcase == 3)
		len = ARRAY_SIZE(query_attr_params);

	pr_info("ufs_test-testcase:%ld len:%d\n", testcase, len);
	for (i = 0; i < len; i++) {
		if (testcase == 0 || testcase == 1) {
			if (0 ==
			    strncmp(subtype, query_desc_params[i].name,
				    strlen(query_desc_params[i].name))) {
				query_desc_subtype = i;
				return;
			}
		}
		if (testcase == 2) {
			if (0 ==
			    strncmp(subtype, query_flag_params[i].name,
				    strlen(query_flag_params[i].name))) {
				query_desc_subtype = i;
				return;
			}
		}
		if (testcase == 3) {
			if (0 ==
			    strncmp(subtype, query_attr_params[i].name,
				    strlen(query_attr_params[i].name))) {
				query_desc_subtype = i;
				return;
			}
		}
	}
}

static int query_read_desc(void)
{

	u8 *desc_buf;
	int buf_len;
	int err = 0;
	struct query_desc_param *param = &query_desc_params[query_desc_subtype];

	buf_len = param->buf_len;
	desc_buf = kmalloc(sizeof(u8 *) * param->buf_len, GFP_KERNEL);
	if (!desc_buf)
		return -ENOMEM;

	err =
	    ufshcd_query_descriptor_retry(hba_addr, UPIU_QUERY_OPCODE_READ_DESC,
					  param->idn, param->index,
					  param->selector, desc_buf, &buf_len);
	if (!err) {
	    pr_info("name:%s idn:0x%x buf_len:%d ", param->name,
	       param->idn, buf_len);
	    dump_sense_buffer(desc_buf, buf_len);
	} else {
		kfree(desc_buf);
		return err;
	}

	err = memcmp(param->result, desc_buf, 3);
	if (!err)
		pr_info("query-read %s success", param->name);
	else
		pr_info("query-read %s failed", param->name);

	kfree(desc_buf);

	return 0;
}

static int query_write_desc(void)
{
	u8 *desc_buf;
	int ret = 0;
	struct query_desc_param *param = &query_desc_params[query_desc_subtype];
	int buf_len;

	pr_info("ufs_test_%s\n", __func__);

	desc_buf = kmalloc(sizeof(u8 *) * param->buf_len, GFP_KERNEL);

	ret =
	    ufshcd_query_descriptor_retry(hba_addr, UPIU_QUERY_OPCODE_READ_DESC,
					  param->idn, param->index,
					  param->selector, desc_buf, &buf_len);

	ret =
	    ufshcd_query_descriptor_retry(hba_addr,
					  UPIU_QUERY_OPCODE_WRITE_DESC,
					  param->idn, param->index,
					  param->selector, desc_buf,
					  &param->buf_len);

	kfree(desc_buf);

	return 0;
}

static int query_flag(void)
{
	int ret = 0;
	bool flag;
	struct query_flag_param *param = &query_flag_params[query_desc_subtype];

	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_READ_FLAG,
				param->idn, &flag);
	if (!ret) {
	    pr_info("name:%s idn:0x%x flag:%08x ", param->name,
	       param->idn, flag);
	}

	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_READ_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, &flag);
	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_SET_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, NULL);
	ret = ufshcd_query_flag(hba_addr, UPIU_QUERY_OPCODE_CLEAR_FLAG,
				QUERY_FLAG_IDN_BKOPS_EN, NULL);

	if (ret == 0)
		pr_err("query_flag SUCCESS\n");
	return 0;
}

static int query_attr(void)
{
	u32 attr;
	int ret = 0;
	struct query_attr_param *param = &query_attr_params[query_desc_subtype];
	u32 val;
	int err;

	ret = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_READ_ATTR,
				param->idn, param->index, param->selector,
				&attr);
	if (!ret)
		pr_info("name:%s-idn:0x%x-attr_value:%d",
				param->name, param->idn, attr);
	val = hba_addr->ee_ctrl_mask & ~MASK_EE_URGENT_BKOPS;
	val &= 0xFFFF;
	err = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_WRITE_ATTR,
				QUERY_ATTR_IDN_EE_CONTROL, 0, 0, &val);
	if (!err)
		hba_addr->ee_ctrl_mask &= ~MASK_EE_URGENT_BKOPS;
	val = hba_addr->ee_ctrl_mask | MASK_EE_URGENT_BKOPS;
	val &= 0xFFFF;
	err = ufshcd_query_attr(hba_addr, UPIU_QUERY_OPCODE_WRITE_ATTR,
				QUERY_ATTR_IDN_EE_CONTROL, 0, 0, &val);
	if (!err)
		hba_addr->ee_ctrl_mask |= MASK_EE_URGENT_BKOPS;

	return 0;
}

static const struct ufs_test_query_case ufs_query_cases[] = {
	/*protocol_uic_test:31~34 */
	{
	 .name = "query_read_desc",
	 .run = query_read_desc,
	 },
	{
	 .name = "query_write_desc",
	 .run = query_write_desc,
	 },
	{
	 .name = "query_flag",
	 .run = query_flag,
	 },
	{
	 .name = "query_attr",
	 .run = query_attr,
	 },
};

static ssize_t ufs_query_write(struct file *file, const char __user *buf,
			       size_t count, loff_t *ppos)
{
	int err;
	long testcase;
	char lbuf[128];
	char tmp[64];
	char *pSpace;
	int digit_len;

	if (copy_from_user(lbuf, buf, count > 127 ? 127 : count))
		return -EFAULT;

	lbuf[(count > 127 ? 127 : count)] = '\0';
	pSpace = strstr(lbuf, " ");
	if (!pSpace)
		return -EINVAL;

	digit_len = pSpace - lbuf;
	if ((digit_len <= 0) || (digit_len >= 64)) {
		pr_info("[ufs_test_query_write]: %d, %p, %p\n", digit_len,
		       pSpace, lbuf);
		return -EINVAL;
	}

	memcpy(tmp, lbuf, digit_len);
	tmp[digit_len] = 0;
	err = kstrtol(tmp, 10, &testcase);
	if (err) {
		pr_info("[ufs_test_query_write]: kstrtol failed, err: %d\n",
		       err);
		return err;
	}

	while (' ' == (*pSpace))
		pSpace++;
	query_parse_subtype(testcase, pSpace);
	if (query_desc_subtype < ARRAY_SIZE(query_desc_params))
		pr_info("[ufs_test_query_write] %d, %s\n", query_desc_subtype,
		       query_desc_params[query_desc_subtype].name);
	else {
		pr_info
		    ("invalid query_desc_subtype %d, %s\n",
		     query_desc_subtype, pSpace);
		return -EINVAL;
	}

	pr_info("%s:the ufs_test will run testcase:%ld\n", __func__, testcase);

	mutex_lock(&ufs_test_lock);
	ufs_query_cases[testcase].run();
	mutex_unlock(&ufs_test_lock);

	msleep(1000);

	pr_info("%s: Completed all the ufs test iterations.", __func__);

	return count;
}

const struct file_operations ufs_query_fops = {
	.open = ufs_test_open,
	.read = seq_read,
	.write = ufs_query_write,
	.llseek = seq_lseek,
	.release = single_release,
};

static int mtf_testlist_show(struct seq_file *sf, void *data)
{
	int i;

	mutex_lock(&ufs_test_lock);

	for (i = 0; i < ARRAY_SIZE(ufs_scsi_cases); i++)
		seq_printf(sf, "%d:\t%s\n", i, ufs_scsi_cases[i].name);

	for (i = 0; i < ARRAY_SIZE(ufs_query_cases); i++)
		seq_printf(sf, "%d:\t%s\n", i, ufs_query_cases[i].name);

	mutex_unlock(&ufs_test_lock);

	return 0;
}

static int mtf_testlist_open(struct inode *inode, struct file *file)
{
	return single_open(file, mtf_testlist_show, inode->i_private);
}

static const struct file_operations ufs_test_fops_testlist = {
	.open = mtf_testlist_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static void ufs_test_free_dbgfs_file(void)
{
	struct ufs_test_debugfs_file *df, *dfs;

	mutex_lock(&ufs_test_lock);

	list_for_each_entry_safe(df, dfs, &ufs_test_file_test, link) {
		debugfs_remove(df->file);
		list_del(&df->link);
		kfree(df);
	}

	mutex_unlock(&ufs_test_lock);
}

static int ufs_test_register_dbgfs_file(struct ufs_test_ud *utd,
					const char *name, umode_t mode,
					const struct file_operations *fops)
{
	struct dentry *file = NULL;
	struct ufs_test_debugfs_file *df;

	if (utd->debugfs_root)
		file = debugfs_create_file(name, mode, utd->debugfs_root,
					   utd, fops);

	if (IS_ERR_OR_NULL(file)) {
		pr_err("Can't create %s. Perhaps debugfs is disabled.\n", name);
		return -ENODEV;
	}

	df = kmalloc(sizeof(struct ufs_test_debugfs_file), GFP_KERNEL);
	if (!df) {
		debugfs_remove(file);
		pr_err("Can't allocate memory for internal usage.\n");
		return -ENOMEM;
	}

	df->hba = utd->hba;
	df->file = file;

	list_add(&df->link, &ufs_test_file_test);
	return 0;
}

static int ufs_test_debugfs_init(struct ufs_test_ud *utd)
{
	int ret;

	mutex_lock(&ufs_test_lock);

	utd->debugfs_root = debugfs_create_dir("ufs_test", NULL);

	ret = ufs_test_register_dbgfs_file(utd, "scsi_test", S_IWUSR | S_IRUGO,
					   &ufs_scsi_fops);
	if (ret)
		goto err;

	ret = ufs_test_register_dbgfs_file(utd, "query_test", S_IWUSR | S_IRUGO,
					   &ufs_query_fops);
	if (ret)
		goto err;

	ret = ufs_test_register_dbgfs_file(utd, "testlist", S_IWUSR | S_IRUGO,
					   &ufs_test_fops_testlist);
	if (ret)
		goto err;
err:
	mutex_unlock(&ufs_test_lock);

	return ret;
}

static struct ufs_test_ud utd_test;

static int __init ufs_test_init(void)
{
	struct ufs_test_ud *utd = &utd_test;
	int ret;

	utd->hba = hba_addr;

	ret = ufs_test_debugfs_init(utd);

	return ret;
}

static void __exit ufs_test_exit(void)
{
	struct ufs_test_ud *utd = &utd_test;

	ufs_test_free_dbgfs_file();

	if (utd->debugfs_root != NULL)
		debugfs_remove(utd->debugfs_root);
}

module_init(ufs_test_init);
module_exit(ufs_test_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("UFS host controller Pltform bus based glue driver");
MODULE_VERSION(UFSHCD_DRIVER_VERSION);
