#include "ufshcd.h"
#include "unipro.h"
#include "ufs_kirin_rdr.h"
#include "ufs-kirin.h"
#include "ufshci.h"
#include "ufs_kirin_norm_stat.h"
#include "ufs_kirin_norm_log.h"
#include "ufs_kirin_spec_log.h"
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>

/* rdr has not assigned core id for UFS module.
   we use RDR_EMMC on chicago platform
 */
#define UFS_KIRIN_RDR_CORE_ID    RDR_EMMC

#define UFS_KIRIN_RDR_LOG_SIZE_MIN    4096

extern int rdr_unregister_module_ops(u64 coreid);

static struct ufs_hba * ufs_rdr_hba = NULL;

void * ufs_rdr_alloc_nvmem( struct ufs_rdr_ctrl * rdr_ctrl, uint size )
{
	if( rdr_ctrl->log_mem_size <= UFS_KIRIN_RDR_LOG_SIZE_MIN )
		return NULL;

	size = ( size + (uint)sizeof(u32) - 1 ) / (uint)sizeof(u32);
	size = size * (uint)sizeof(u32);

	if( size <= ( rdr_ctrl->log_mem_size - UFS_KIRIN_RDR_LOG_SIZE_MIN ) ) {
		u8 * alloc_addr;

		rdr_ctrl->log_mem_size -= size;
		rdr_ctrl->log_mem_addr += size;

		alloc_addr = rdr_ctrl->nvinfo_mem_addr;

		rdr_ctrl->nvinfo_mem_addr += size;
		rdr_ctrl->nvinfo_mem_size += size;

		return alloc_addr;
	}

	return NULL;
}


static void ufs_rdr_hba_vprint( struct ufs_hba *hba, const char * format, va_list args )
{
	struct ufs_rdr_ctrl * rdr_ctrl;
	uint pr_len, len, size;

	rdr_ctrl = &(((struct ufs_kirin_host *)hba->priv)->rdr_ctrl);

	len = rdr_ctrl->log_mem_length;
	if( len >= rdr_ctrl->log_mem_size )
		return ;

	size = rdr_ctrl->log_mem_size - len;

	if( size > 1 ) {
		pr_len = (uint)vsnprintf( (char *)rdr_ctrl->log_mem_addr + len, (size_t)size, format, args );

		if( pr_len < size ) {
			rdr_ctrl->log_mem_length += pr_len;
		} else {
			rdr_ctrl->log_mem_length += size - 1;
		}
	}
}

static void ufs_rdr_hba_print( struct ufs_hba *hba, const char * format, ... )
{
	va_list args;
	va_start(args, format);

	ufs_rdr_hba_print( hba, format, args );

	va_end(args);
}

static void ufs_rdr_hba_dump( struct ufs_hba * hba, const char * prefix_str,
				const void * buffer, size_t buf_size )
{
	const u8 *ptr;
	size_t i, linelen, remaining;
	char linebuf[16 * 3 + 2 + 2];

	remaining = buf_size;
	ptr = buffer;

	for( i = 0; i < buf_size; i += 16 ) {
		linelen = min(remaining, 16UL);
		remaining -= 16;

		hex_dump_to_buffer( ptr + i, linelen, 16, 1,
				linebuf, sizeof(linebuf)-1, (bool)false );

		ufs_rdr_hba_print( hba, "%s %s\n", prefix_str, linebuf );
	}
}


static void ufs_kirin_rdr_reset( u32 modid, u32 etype, u64 coreid )
{
	return;
}

static void ufs_kirin_rdr_dump( u32 modid, u32 etype, u64 coreid,
				char *pathname, pfn_cb_dump_done pfn_cb )
{
	if( UFS_KIRIN_RDR_CORE_ID != coreid ) {
		return;
	}

	if( NULL != ufs_rdr_hba ) {
		pfn_ufs_hba_print print_hba_fn;
		pfn_ufs_hba_dump  dump_hba_fn;
		struct ufs_rdr_ctrl * rdr_ctrl;
		ulong flags;
		rdr_ctrl = &(((struct ufs_kirin_host *)ufs_rdr_hba->priv)->rdr_ctrl);

		spin_lock_irqsave( &(rdr_ctrl->rdr_lock), flags );
		if( true == rdr_ctrl->dumping ) {
			spin_unlock_irqrestore( &(rdr_ctrl->rdr_lock), flags );
			goto ufs_dump_end_tag ;
		}
		rdr_ctrl->dumping = true;
		spin_unlock_irqrestore( &(rdr_ctrl->rdr_lock), flags );

		ufs_log_get_fn( ufs_rdr_hba, &print_hba_fn, &dump_hba_fn );
		ufs_log_fn_redir( ufs_rdr_hba, ufs_rdr_hba_vprint, ufs_rdr_hba_dump );

		ufs_log_host_state( ufs_rdr_hba, modid );
		ufs_log_pwr_info( ufs_rdr_hba, modid );
		ufs_log_intr_hist(ufs_rdr_hba, modid);
		ufs_log_uic_err_hist_all( ufs_rdr_hba, modid );
		ufs_log_hba_outstanding_upiu( ufs_rdr_hba, modid );
		ufs_log_utp_cmd_hist( ufs_rdr_hba, modid );

		ufs_log_fn_redir( ufs_rdr_hba, print_hba_fn, dump_hba_fn );

		rdr_ctrl->dumping = false;
	}

ufs_dump_end_tag:
	if( NULL != pfn_cb ) {
		pfn_cb(modid, coreid);
	}
}


void ufs_rdr_log_clean( void )
{
	if( NULL != ufs_rdr_hba ) {
		struct ufs_rdr_ctrl * rdr_ctrl;

		rdr_ctrl = &(((struct ufs_kirin_host *)ufs_rdr_hba->priv)->rdr_ctrl);

		rdr_ctrl->log_mem_length = 0;
	}
}


char * ufs_rdr_log_show( void )
{
	ufs_kirin_rdr_dump( 0, 0, (u64)UFS_KIRIN_RDR_CORE_ID, NULL, NULL );

	if( NULL != ufs_rdr_hba ) {
		struct ufs_rdr_ctrl * rdr_ctrl;

		rdr_ctrl = &(((struct ufs_kirin_host *)ufs_rdr_hba->priv)->rdr_ctrl);

		pr_err("ufs_rdr_show[%d,%d,%d,%d]\n%s\n",
				rdr_ctrl->total_mem_size, rdr_ctrl->log_mem_size,
				rdr_ctrl->nvinfo_mem_size, rdr_ctrl->log_mem_length,
				rdr_ctrl->log_mem_addr );

		return (char *)(rdr_ctrl->log_mem_addr);
	}

	return NULL;
}

int ufs_rdr_hist_init( struct ufs_hba * hba )
{
	struct ufshcd_hist *hist_rec;
	struct ufs_kirin_host *kirin_host;

	kirin_host = (struct ufs_kirin_host *)hba->priv;

	if( NULL == kirin_host ) {
		return -1;
	}
	if( NULL != hba->ufs_stats.hist_rec ) {
		pr_err("ufsdev_log:history record has been inited\n");
		return 0;
	}

	hist_rec = (struct ufshcd_hist *)ufs_rdr_alloc_nvmem(&(kirin_host->rdr_ctrl),\
				(uint)sizeof(struct ufshcd_hist));

	if( NULL != hist_rec ) {
		ufs_init_hist_all(hist_rec);
		hba->ufs_stats.hist_rec = hist_rec;

		return 0;
	}
	pr_err("ufsdev_log:failed create UFS history record in rdr memory");

	return -1;
}


int ufs_rdr_init( struct ufs_hba * hba )
{
	struct rdr_module_ops_pub s_module_ops;
	struct rdr_register_module_result reg_mod_info;

	struct ufs_rdr_ctrl * rdr_ctrl;

	u8 *vir_addr;

	int ret;

	if( NULL != ufs_rdr_hba ) {
		pr_err("ufs rdr has registerred\n");
		return 0;
	}

	rdr_ctrl = &(((struct ufs_kirin_host *)hba->priv)->rdr_ctrl);
	rdr_ctrl->total_mem_size = 0;
	rdr_ctrl->log_mem_size   = 0;
	rdr_ctrl->nvinfo_mem_size= 0;
	rdr_ctrl->log_mem_length = 0;

	s_module_ops.ops_dump  = ufs_kirin_rdr_dump;
	s_module_ops.ops_reset = ufs_kirin_rdr_reset;

	ret = rdr_register_module_ops( (u64)UFS_KIRIN_RDR_CORE_ID, &s_module_ops, &reg_mod_info );

	if( 0 != ret || 0 == reg_mod_info.log_len ) {
		pr_err("ufs log rdr register failed with %d, %d\n", ret, reg_mod_info.log_len );
		return -1;
	}
	vir_addr = (unsigned char *)hisi_bbox_map((phys_addr_t)reg_mod_info.log_addr, (size_t)reg_mod_info.log_len);

	pr_info("ufsdev rdr log_addr is 0x%llx, log_len is 0x%x!\n", reg_mod_info.log_addr, reg_mod_info.log_len);

	if (IS_ERR_OR_NULL(vir_addr)) {
		rdr_unregister_module_ops((u64)UFS_KIRIN_RDR_CORE_ID);
		pr_err("ufsdev rdr log_addr map failed!\n");
		return -EINVAL;
	}

	memset(vir_addr, 0, (size_t)reg_mod_info.log_len);

	rdr_ctrl->saved_mem_vaddr = vir_addr;
	rdr_ctrl->total_mem_size  = reg_mod_info.log_len;
	rdr_ctrl->log_mem_addr    = vir_addr;
	rdr_ctrl->log_mem_size    = reg_mod_info.log_len;
	rdr_ctrl->log_mem_length  = 0;

	rdr_ctrl->nvinfo_mem_addr = vir_addr;
	rdr_ctrl->nvinfo_mem_size = 0;

	rdr_ctrl->dumping = false;
	spin_lock_init( &(rdr_ctrl->rdr_lock) );

	ufs_rdr_hba = hba;
	return 0;
}

int ufs_rdr_exit(struct ufs_hba *hba)
{
	pr_err("ufsdev_log:uninstall the rdr of the ufs device\n");

	if( NULL != hba ) {
		hba->ufs_stats.hist_rec = NULL;
	}

	if( NULL != ufs_rdr_hba ) {
		ufs_rdr_hba = NULL;
		return rdr_unregister_module_ops((u64)UFS_KIRIN_RDR_CORE_ID);
	}
	return 0;
}

