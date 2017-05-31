
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/hardirq.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>
#include <linux/mmc/core.h>
#include <linux/delay.h>
#include <linux/reboot.h>
#include <linux/syscalls.h>
#include <linux/hisi/hisi_bootup_keypoint.h>

#include "rdr_inner.h"
#include "rdr_field.h"
#include "rdr_print.h"
#include "rdr_debug.h"
#include <chipset_common/hwbfm/hw_boot_fail_core.h>

struct bootcheck {
	u64 mask;
	u64 core;
	u32 modid;
	u32 type;
};

#define RDR_NEED_SAVE_MEM  1
#define RDR_DONTNEED_SAVE_MEM  0

/*
check status of last reboot.
return
0 dont need save.
1 need save log.
*/
static int rdr_check_exceptionboot(struct bootcheck *info)
{
	u32 reboot_type;
	struct rdr_base_info_s *base;
	struct rdr_struct_s *tmpbb;

	if (NULL == info) {
		BB_PRINT_PN();
		return RDR_DONTNEED_SAVE_MEM;
	}

	reboot_type = rdr_get_reboot_type();
	/*����쳣����Ϊ����������������Ҫ����log */
	if (REBOOT_REASON_LABEL1 > reboot_type
	    || (REBOOT_REASON_LABEL4 <= reboot_type
	    && REBOOT_REASON_LABEL5 > reboot_type)
	    || (REBOOT_REASON_LABEL6 <= reboot_type
	    && REBOOT_REASON_LABEL8 > reboot_type)) {
		BB_PRINT_PN();
		return RDR_DONTNEED_SAVE_MEM;
	}

	/*��λ�󱣴�log��Ĭ��ֵ��ʼ�� */
	info->modid = RDR_MODID_AP_ABNORMAL_REBOOT;
	info->mask = RDR_AP;
	info->core = RDR_AP;
	info->type = reboot_type;

	/*����쳣����Ϊ�������̸�λ�ģ�����Ҫ�����󱣴�log */
	if ((REBOOT_REASON_LABEL1 <= reboot_type
	    && REBOOT_REASON_LABEL3 > reboot_type)
	    || MMC_S_EXCEPTION == reboot_type
	    || LPM3_S_EXCEPTION == reboot_type) {
		return RDR_NEED_SAVE_MEM;
	}

	/*if reboot_type is about pmu, need save log*/
	if (REBOOT_REASON_LABEL5 <= reboot_type
	    && REBOOT_REASON_LABEL6 > reboot_type) {
		return RDR_NEED_SAVE_MEM;
	}

	/*��ȡbbox���ڴ��ַ */
	tmpbb = rdr_get_tmppbb();
	if (NULL == tmpbb) {
		BB_PRINT_PN();
		return RDR_DONTNEED_SAVE_MEM;
	}

	/*��ȡbboxͷ�ṹ�� */
	base = &(tmpbb->base_info);

	/*�����λǰlogδ������ɣ���λ��������Ҫ�ٴα���һ�� */
	if (RDR_PROC_EXEC_DONE != base->start_flag
	    || RDR_DUMP_LOG_DONE != base->savefile_flag) {
		BB_PRINT_ERR("ap error:start[%x],save done[%x]\n",
			     base->start_flag, base->savefile_flag);
		info->modid = BBOX_MODID_LAST_SAVE_NOT_DONE;
		return RDR_NEED_SAVE_MEM;
	}

	return RDR_DONTNEED_SAVE_MEM;
}

int rdr_bootcheck_thread_body(void *arg)
{
	int cur_reboot_times;
	int ret;
	char path[PATH_MAXLEN];
	struct bootcheck info;
	struct rdr_syserr_param_s p;
	struct rdr_struct_s *temp_pbb;
	int max_reboot_times = rdr_get_reboot_times();
	BB_PRINT_START();

	memset(path, 0, PATH_MAXLEN);

	save_hwbootfailInfo_to_file();

	BB_PRINT_DBG("============wait for fs ready start =============\n");
	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;
	BB_PRINT_DBG("============wait for fs ready e n d =============\n");

	if (is_need_save_dfx2file()) {
		save_dfxpartition_to_file();
	}

	if (RDR_NEED_SAVE_MEM != rdr_check_exceptionboot(&info)) {
		BB_PRINT_ERR("need not save dump file when boot.\n");
		goto end;
	}

	temp_pbb = rdr_get_tmppbb();
	if (RDR_UNEXPECTED_REBOOT_MARK_ADDR == temp_pbb->top_head.reserve) {
		cur_reboot_times = rdr_record_reboot_times2file();
		printk(KERN_ERR "ap has reboot %d times\n", cur_reboot_times);
		if (max_reboot_times < cur_reboot_times) {
			printk(KERN_ERR "need reboot to erecovery.\n");

			/*write "erecovery_enter_reason:=2015" to cache*/
			rdr_record_erecovery_reason();

			/*reset the file of reboot_times*/
			rdr_reset_reboot_times();

			kernel_restart("erecovery");
		}
	} else {
		rdr_reset_reboot_times();
	}
    p.modid = info.modid, p.arg1 = info.core, p.arg2 = info.type;

	ret = rdr_create_epath_bc(path);
	if (-1 == ret) {
		BB_PRINT_ERR("failed to create epath!\n");
		goto end;
	}
	rdr_set_saving_state(1);
	BB_PRINT_DBG("create dump file path:[%s].\n", path);
	while (info.mask) {
		if ((rdr_get_cur_regcore() & info.mask) == 0) {
			BB_PRINT_DBG
			    ("wait module register. cur:[0x%llx],need[0x%llx]\n",
			     rdr_get_cur_regcore(), info.mask);
			msleep(1000);
			continue;
		}
		ret = rdr_notify_onemodule_dump(info.modid, info.mask,
						info.type, info.core, path);
		BB_PRINT_ERR("info.mask is [%llx], ret = [%x]\n", info.mask,
			     ret);
		if (ret) {
			info.mask &= !ret;
		} else {
			break;
		}
		BB_PRINT_ERR("rdr: notify [%s] core dump data done.\n",
			     rdr_get_exception_core(ret));
	}
	if (check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		rdr_save_last_baseinfo(path);
	}

	/* ���쳣Ŀ¼�����½�DONE�ļ�����־�˴��쳣log������� */
	bbox_save_done(path, BBOX_SAVE_STEP_DONE);

	/* �ļ�ϵͳsync����֤��д������� */
	if (!in_atomic() && !irqs_disabled() && !in_irq()) {
		sys_sync();
	}

	rdr_set_saving_state(0);

	BB_PRINT_DBG("saving data done.\n");
	rdr_count_size();
	BB_PRINT_DBG("rdr_count_size: done.\n");
end:
	rdr_clear_tmppbb();
	BB_PRINT_END();
	return 0;
}
