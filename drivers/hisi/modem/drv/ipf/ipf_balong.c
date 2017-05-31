

/*lint -save -e429 -e529 -e534 -e550 -e650 -e661 -e715 -e537  -e737 -e539 -e574 -e239 -e438 -e701 -e740 -e958 -e451
-e64 -e732 -e740
*/
/*lint --e{750} */

#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/skbuff.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>
#include <linux/syscore_ops.h>
#include <bsp_ipc.h>
#include "osl_cache.h"
#include <bsp_ddr.h>
#include <bsp_psam.h>
#include <bsp_ipf.h>
#include <ipf_balong.h>

#include <bsp_reset.h>
/*C������(��������)��ʾ*/
IPF_FORRESET_CONTROL_E* modem_reset_flag = NULL;
int ccore_rst_idle = 0;
static IPF_FORRESET_CONTROL_E bsp_ipf_get_control_flag_for_ccore_reset(void);

IPF_UL_S g_stIpfUl = {0};
IPF_DL_S g_stIpfDl = {0};
ipf_ctx_t g_ipf_ctx;
unsigned long long dma_mask;

/*C������(��������)��ʾ���ñ�־����Acore�����Ƿ������������*/
IPF_FORRESET_CONTROL_E g_eCcoreResetFlag = IPF_FORRESET_CONTROL_ALLOW;

/*k3�͹��Ļָ����*/
unsigned int* ipf_acore_init_status = NULL;
unsigned int* ipf_ccore_init_status = NULL;
static spinlock_t ipf_filter_spinlock;
void ipf_check_filter_restore(void);

IPF_TIMESTAMP_INFO_S g_ipf_dl_timestamp_info;
unsigned int g_ipf_ul_start_enable;
#define IPF_GET_TIMESTAMP_INFO() (&g_ipf_dl_timestamp_info)
#define IPF_START_STAMP_ENABLE (g_ipf_ul_start_enable)

/*****************************************************************************
* �� �� ��	   : get_ipf_int_stat
*
* ��������	: ipf����acore��򿪼�¼��pm-om����
*
* �������	: ��
*
* �������	: ��
*
* �� �� ֵ	   : ��
*
* �޸ļ�¼	:2015/01/22 ���� ����
*****************************************************************************/
static void get_ipf_int_stat(void)
{
	unsigned int status = 0;
	dev_info(g_ipf_ctx.dev, "%s resume +\n", __func__);
	status = ipf_readl(g_ipf_ctx.regs + HI_IPF_INT1_OFFSET);
	if (status & (IPF_DL_RPT_INT1 \
					| IPF_DL_TIMEOUT_INT1 \
					| IPF_DL_ADQ0_EPTY_INT1 \
					| IPF_DL_ADQ1_EPTY_INT1)) {
		g_ipf_ctx.status->resume_with_intr++;
	}
	dev_info(g_ipf_ctx.dev, "%s resume -\n", __func__);
}


/*****************************************************************************
* �� �� ��	   : ipf_dl_dpm_prepare
*
* ��������	: dpm����׼������
*
* �������	: �豸ָ��
*
* �������	: ��
*
* �� �� ֵ	   : IPF_ERROR ʧ��
							IPF_SUCCESS �ɹ�
*
* �޸ļ�¼	:2013��6��16��	 �¶���  ����
*****************************************************************************/
static int ipf_dl_dpm_prepare(struct device *pdev)
{
	unsigned int u32_dl_state;

	/* ���Ccore�Ƿ��ϵ磬����Ѿ��µ磬�����͹��ı���ָ�����*/
	if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
	{
		dev_err(g_ipf_ctx.dev, "%s ccore resetting, skip dpm process\n", __func__);
		return IPF_SUCCESS;
	}

	/* �ж�����IPF�Ƿ���� */
	u32_dl_state = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_STATE_OFFSET);

	if(u32_dl_state != IPF_CHANNEL_STATE_IDLE)
	{
		dev_err(g_ipf_ctx.dev, "%s ipf is busy\n", __func__);
		return IPF_ERROR;
	}
	return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��	   : ipf_dl_dpm_complete
*
* ��������	: dpm׮����
*
* �������	: �豸ָ��
*
* �������	: ��
*
* �� �� ֵ	   : ��
*
* �޸ļ�¼	:2013��6��16��	 �¶���  ����
*****************************************************************************/
static void ipf_dl_dpm_complete(struct device *pdev)
{
	return ;
}

/*****************************************************************************
* �� �� ��	   : ipf_dl_suspend
*
* ��������	: dpm׮����
*
* �������	: �豸ָ��
*
* �������	: ��
*
* �� �� ֵ	   : �ɹ�
*
* �޸ļ�¼	:2013��6��16��	 �¶���  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
static int ipf_dl_suspend(struct device *dev)
{

	unsigned long ipf_flags = 0;
	dev_info(g_ipf_ctx.dev, "%s suspend +\n", __func__);

	/* ���Ccore�Ƿ��ϵ�����Ѿ��µ磬�����͹��ı���ָ�����*/
	if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
	{
		dev_err(g_ipf_ctx.dev, "%s ccore resetting, skip dpm process\n", __func__);
		return IPF_SUCCESS;
	}

	spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
	bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
	*ipf_acore_init_status = IPF_PWC_DOWN;
	cache_sync();
	bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
	spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);

	g_ipf_ctx.status->suspend++;
	dev_info(g_ipf_ctx.dev, "%s suspend -\n", __func__);
	return IPF_SUCCESS;
}


/*****************************************************************************
* �� �� ��	   : ipf_dl_resume
*
* ��������	: dpm׮����
*
* �������	: �豸ָ��
*
* �������	: ��
*
* �� �� ֵ	   : �ɹ�
*
* �޸ļ�¼	:2013��6��16��	 �¶���  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
static int ipf_dl_resume(struct device *dev)
{
	dev_info(g_ipf_ctx.dev, "%s resume +\n", __func__);
	/* ���Ccore�Ƿ��ϵ�����Ѿ��µ磬�����͹��ı���ָ�����*/
	if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
	{
		dev_err(g_ipf_ctx.dev, "%s ccore resetting, skip dpm process\n", __func__);
		return IPF_SUCCESS;
	}

	/*����K3V3����������⣬�ָ��������ƶ����˴�*/
	ipf_check_filter_restore();
	g_ipf_ctx.status->resume++;
	dev_info(g_ipf_ctx.dev, "%s resume -\n", __func__);
	return IPF_SUCCESS;
}

static struct syscore_ops ipf_dpm_ops = {
	.resume = get_ipf_int_stat,
	};


/*
 * On ARMv5 and above those functions can be implemented around
 * the clz instruction.
 * refer to kernel/arch/arm/include/asm/bitops.h
 * put the code here for both vxWorks and linux version.
 */
static inline int ipf_fls(int x)
{
    int ret;

    asm("clz\t%0, %1" : "=r" (ret) : "r" (x));
    ret = 32 - ret;
    return ret;
}

static inline void ipf_record_start_time_stamp(unsigned int en, unsigned int* rec_point)
{
    if (!en) {
        return;
    }
    *rec_point = bsp_get_slice_value_hrt();
    return;
}

static inline void
ipf_record_end_time_stamp(unsigned int en, unsigned int beg_time)
{
    unsigned int diff_time;
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();
    int idx;

    if (!en) {
        return;
    }

    diff_time = bsp_get_slice_value_hrt() - beg_time;

    /* avoid to record the overflowed value */
    if (diff_time > IPF_MAX_TIME_LIMIT) {
        stamp_info->overflow++;
    }
    else {
        if (diff_time > stamp_info->diff_max)
            stamp_info->diff_max = diff_time;

        stamp_info->diff_sum += diff_time;
        stamp_info->cnt_sum++;

        /* find the first bit not zero */
        idx = ((ipf_fls(diff_time)-1) & IPF_FLS_MASK);
        stamp_info->diff_order_cnt[idx]++;
    }
}

static inline
unsigned int ipf_calc_percent(unsigned int value, unsigned int sum)
{
    if (0 == sum) {
        return 0;
    }
    return (value * 100 / sum);
}

static void ipf_get_version(void)
{
	unsigned int ver = 0;
	ver = ipf_readl(g_ipf_ctx.regs + HI_IPF_VERSION_OFFSET);
	printk(" ipf version is 0x%x\n", ver);
	switch(ver){
	case IPF_VER_120A:
		g_ipf_ctx.ipf_version = IPF_VERSION_120a;
		break;
	case IPF_VER_130A:
		g_ipf_ctx.ipf_version = IPF_VERSION_130a;
		break;
	case IPF_VER_130B:
		g_ipf_ctx.ipf_version = IPF_VERSION_130b;
		break;
	case IPF_VER_140A:
		g_ipf_ctx.ipf_version = IPF_VERSION_140a;
		break;
	default:
		g_ipf_ctx.ipf_version = IPF_VERSION_0000;
		break;
	}
}

void ipf_enable_dl_time_stamp(int en)
{
	g_ipf_ctx.status->timestamp_en = en;
    return;
}

void ipf_enable_rd_rate(int en)
{
	g_ipf_ctx.status->rate_en = en;
    return;
}

void ipf_clear_time_stamp(void)
{
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();

    memset(stamp_info, 0, sizeof(IPF_TIMESTAMP_INFO_S));/*[false alarm]:fortify*/
    return;
}

void ipf_dump_time_stamp(void)
{
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();
    unsigned int tmp = 0;
    int i;

    printk(" max diff:%u(%uus)\n",
              stamp_info->diff_max, stamp_info->diff_max*10/192);
    printk(" sum diff:%u(%uus)\n",
              stamp_info->diff_sum, stamp_info->diff_max/19);

    if (stamp_info->cnt_sum) {
        tmp = stamp_info->diff_sum / stamp_info->cnt_sum;
    }

    printk(" avg diff:%u(%uus)\n", tmp, tmp*10/192);

    for (i = 0; i < IPF_MAX_STAMP_ORDER; i++) {
        tmp = ipf_calc_percent(stamp_info->diff_order_cnt[i], stamp_info->cnt_sum);
        printk(" diff time (%u~%u) (%uus~%uus) count:%u (%u %%)\n",
            (0x80000000 >> (31-i)),
            (0xFFFFFFFF >> (31-i)),
            (0x80000000 >> (31-i))/19,
            (0xFFFFFFFF >> (31-i))/19,
            stamp_info->diff_order_cnt[i], tmp);
    }
    return;
}

static int ipf_get_limit_addr(void)
{
    struct memblock_type *type = NULL;
	phys_addr_t mem_start = 0, mem_end = 0;
    unsigned int i = 0;

	type = &memblock.memory;

	if(0 == type->cnt){
		dev_err(g_ipf_ctx.dev, "ipf limit addr not get\n");
		g_ipf_ctx.limit_addr->block_err = 1;
		return BSP_ERR_IPF_INVALID_PARA;
	}

    mem_start = type->regions[0].base;
	mem_end = type->regions[type->cnt-1].base + type->regions[type->cnt-1].size;

    *(g_ipf_ctx.memblock_show) = type->cnt;
    for(i=0; i < type->cnt; i++){
        *(g_ipf_ctx.memblock_show + i + 1) = (unsigned int)(type->regions[i].base);
        if(mem_start > type->regions[i].base){
            mem_start = type->regions[i].base;
        }
        
        if(mem_end < (type->regions[i].base + type->regions[i].size)){
            mem_end = type->regions[i].base + type->regions[i].size;
        }
    }

    if(mem_end > (phys_addr_t)0xffffffff){
        mem_end = (phys_addr_t)0xffffffff;
    }
    
	if((MODEM_START_ADDR >= mem_start) && ((MODEM_START_ADDR + MODEM_START_SIZE) <= mem_end)){
		g_ipf_ctx.limit_addr->block_sum 		=2;
		g_ipf_ctx.limit_addr->block1_start 		=(unsigned int)mem_start;
		g_ipf_ctx.limit_addr->block1_end		=MODEM_START_ADDR;
		g_ipf_ctx.limit_addr->block2_start 		=MODEM_START_ADDR + MODEM_START_SIZE;
		g_ipf_ctx.limit_addr->block2_end		=(unsigned int)mem_end;
	}
	else{
		g_ipf_ctx.limit_addr->block_sum 		=1;
		g_ipf_ctx.limit_addr->block1_start 		=(unsigned int)mem_start;
		g_ipf_ctx.limit_addr->block1_end		=(unsigned int)mem_end;
	}

	return 0;
}

/* IPF transfer time recorder end */
void ipf_get_shared_ddr(void)
{

	ipf_ddr_t *ddr_info;

	ddr_info = &g_ipf_ctx.status->share_ddr_info;
	ddr_info->start = SHM_OFFSET_IPF;
	ddr_info->ul_start = IPF_ULBD_MEM_ADDR;
	ddr_info->filter_pwc_start = IPF_PWRCTL_BASIC_FILTER_ADDR;
	ddr_info->pwc_info_start = IPF_PWRCTL_INFO_ADDR;
	ddr_info->dlcdrptr = IPF_DLCDRPTR_MEM_ADDR;
	ddr_info->end = IPF_SHM_USED_END_ADDR;
	ddr_info->len = IPF_SHM_USED_END_ADDR - (unsigned long)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_IPF);
}


void ipf_write_basic_filter(unsigned int filter_hw_id, IPF_MATCH_INFO_S* match_infos)
{
    unsigned int j;
    unsigned int match_info;
    unsigned int* match_info_addr = (unsigned int*)match_infos;
    ipf_writel(filter_hw_id, g_ipf_ctx.regs + HI_BFLT_INDEX_OFFSET);
    for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
    {
        match_info = *(match_info_addr+j);
        ipf_writel((match_info), (g_ipf_ctx.regs+HI_FLT_LOCAL_ADDR0_OFFSET+j*4));
    }
}


static irqreturn_t ipf_interuppt(int irq, void* dev)
{
	unsigned int status = 0;

	status = ipf_readl(g_ipf_ctx.regs + HI_IPF_INT1_OFFSET);

	ipf_writel(status, g_ipf_ctx.regs + HI_IPF_INT_STATE_OFFSET);

	if(status & (IPF_DL_RPT_INT1 | IPF_DL_TIMEOUT_INT1 | IPF_DL_RD_FULL_INT1))
	{
		if (status & IPF_DL_RPT_INT1) {
			g_ipf_ctx.status->rd_comp_intr++;
		}
		if (status & IPF_DL_TIMEOUT_INT1) {
			g_ipf_ctx.status->time_out_intr++;
		}

		if (status & IPF_DL_RD_FULL_INT1) {
			g_ipf_ctx.status->rd_full_intr++;
		}

        if(g_stIpfDl.pFnDlIntCb) {
            (void)g_stIpfDl.pFnDlIntCb();
			g_ipf_ctx.status->rd_cb++;
        } else {
        	g_ipf_ctx.status->rd_cb_null++;
        }

		if(ccore_rst_idle){
			g_ipf_ctx.status->ccore_rst_err ++;
		}
    }
    if(status & (IPF_DL_ADQ0_EPTY_INT1 | IPF_DL_ADQ1_EPTY_INT1)) {
		if(g_stIpfDl.pAdqEmptyDlCb) {
        	if ((status & (IPF_DL_ADQ0_EPTY_INT1 | IPF_DL_ADQ1_EPTY_INT1))
			== (IPF_DL_ADQ0_EPTY_INT1 | IPF_DL_ADQ1_EPTY_INT1)) {
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_0]++;
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_1]++;
				g_stIpfDl.pAdqEmptyDlCb(IPF_EMPTY_ADQ);

			} else if (status & IPF_DL_ADQ0_EPTY_INT1) {
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_0]++;
				g_stIpfDl.pAdqEmptyDlCb(IPF_EMPTY_ADQ0);
			} else {
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_1]++;
				g_stIpfDl.pAdqEmptyDlCb(IPF_EMPTY_ADQ1);
			}

			g_ipf_ctx.status->ad_epty_cb++;

        } else {
        	g_ipf_ctx.status->ad_epty_cb_null++;
        }
    }

    if(status & IPF_UL_BDQ_EPTY_INT1) {
		g_ipf_ctx.status->bd_epty_intr++;
		if(g_stIpfUl.handle_bd_empty)
        {
			g_stIpfUl.handle_bd_empty();
			g_ipf_ctx.status->bd_epty_cb++;
        } else {
        	g_ipf_ctx.status->bd_epty_cb_null++;
        }
    }

	if(status & IPF_MST_SEC_RD_ERR){
		disable_irq_nosync(g_ipf_ctx.irq);
		g_ipf_ctx.status->reg_scur_rd_err++;
		IPF_PRINT("ipf sec rd err\n");

		system_error(DRV_ERRNO_IPF_OUT_REG, 0, 0, (char *)IPF_ULAD0_MEM_ADDR, IPF_ULAD0_MEM_SIZE + IPF_ULAD1_MEM_SIZE);
	}

	if(status & IPF_MST_SEC_WR_ERR){
		disable_irq_nosync(g_ipf_ctx.irq);
		g_ipf_ctx.status->reg_scur_wr_err++;
		IPF_PRINT("ipf sec wr err\n");

		system_error(DRV_ERRNO_IPF_OUT_REG, 0, 0, (char *)IPF_ULAD0_MEM_ADDR, IPF_ULAD0_MEM_SIZE + IPF_ULAD1_MEM_SIZE);
	}

    if(status & IPF_DL_RDQ_FULL) {
		g_ipf_ctx.status->rd_full++;
    }
    return IRQ_HANDLED;
}/*lint !e550*/

/*****************************************************************************
* �� �� ��      : ipf_init
*
* ��������  : IPF��ʼ��     �ڲ�ʹ�ã�����Ϊ�ӿں���
*
* �������  : void
* �������  : ��
* �� �� ֵ     : IPF_SUCCESS    ��ʼ���ɹ�
*                           IPF_ERROR      ��ʼ��ʧ��
*
* �޸ļ�¼  :2011��1��21��   ³��  ����
				 2013��4��30��    �¶����޸ģ����Ĵ������÷��䵽����
*****************************************************************************/
int ipf_init(void)
{
	int ret;

    unsigned int ipf_flags;

    memset((void*)IPF_DLBD_MEM_ADDR, 0x0, IPF_DLDESC_SIZE);
    g_stIpfUl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_ULBD_MEM_ADDR;
    g_stIpfUl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_ULRD_MEM_ADDR;
    g_stIpfUl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_ULAD0_MEM_ADDR;
    g_stIpfUl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_ULAD1_MEM_ADDR;
    g_stIpfUl.pu32IdleBd = (unsigned int*)IPF_ULBD_IDLENUM_ADDR;

    g_stIpfDl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_DLBD_MEM_ADDR;
    g_stIpfDl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_DLRD_MEM_ADDR;
    g_stIpfDl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_DLAD0_MEM_ADDR;
    g_stIpfDl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_DLAD1_MEM_ADDR;
    g_stIpfDl.pstIpfCDQ = (IPF_CD_DESC_S*)IPF_DLCD_MEM_ADDR;

    g_stIpfDl.pstIpfPhyBDQ = (IPF_BD_DESC_S*)(SHD_DDR_V2P((void *)IPF_DLBD_MEM_ADDR));
    g_stIpfDl.pstIpfPhyRDQ = (IPF_RD_DESC_S*)(SHD_DDR_V2P((void *)IPF_DLRD_MEM_ADDR));
    g_stIpfDl.pstIpfPhyADQ0 = (IPF_AD_DESC_S*)(SHD_DDR_V2P((void *)IPF_DLAD0_MEM_ADDR));
    g_stIpfDl.pstIpfPhyADQ1 = (IPF_AD_DESC_S*)(SHD_DDR_V2P((void *)IPF_DLAD1_MEM_ADDR));

    /*s00219058 �����ڴ� ����CD��ָ�� ��ʼ��Ϊ0*/
    g_stIpfDl.u32IpfCdRptr = (unsigned int*) IPF_DLCDRPTR_MEM_ADDR;
    *(g_stIpfDl.u32IpfCdRptr) = 0;

    spin_lock_init(&ipf_filter_spinlock);

    /* ��������ͨ����AD��BD��RD��� */
    ipf_writel(IPF_DLRD_DESC_SIZE-1, g_ipf_ctx.regs + HI_IPF_CH1_BDQ_SIZE_OFFSET);
    ipf_writel(IPF_DLRD_DESC_SIZE-1, g_ipf_ctx.regs + HI_IPF_CH1_RDQ_SIZE_OFFSET);

	ipf_writel(IPF_ADQ_DEFAULT_SEETING, g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);

    /*����ͨ����BD��RD��ʼ��ַ*/
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyBDQ, g_ipf_ctx.regs + HI_IPF_CH1_BDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyRDQ, g_ipf_ctx.regs + HI_IPF_CH1_RDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyADQ0, g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_BASE_OFFSET);
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyADQ1, g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_BASE_OFFSET);

    register_syscore_ops(&ipf_dpm_ops);

	ret = request_irq(g_ipf_ctx.irq, ipf_interuppt, IRQF_SHARED, "ipf", g_ipf_ctx.dev);
	if(0 != ret) {
		dev_err(g_ipf_ctx.dev, "request irq failed\n");
	}

    ipf_acore_init_status = (unsigned int*)IPF_INIT_ADDR;
    ipf_ccore_init_status = (unsigned int*)(IPF_INIT_ADDR+4);

    spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
    bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
    *ipf_acore_init_status = IPF_ACORE_INIT_SUCCESS;
    cache_sync();
    bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
    spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);

    modem_reset_flag = (IPF_FORRESET_CONTROL_E*)(IPF_INIT_ADDR+8);
    *modem_reset_flag = IPF_FORRESET_CONTROL_ALLOW;

    if(0 != mdrv_sysboot_register_reset_notify("IPF_BALONG",bsp_ipf_reset_ccore_cb, 0, DRV_RESET_CB_PIOR_IPF))
    {
    	dev_err(g_ipf_ctx.dev, "set modem reset call back func failed\n");
    }

	/*acore use first block,ccore use scnd block*/
	g_ipf_ctx.status = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR) ;
	memset(g_ipf_ctx.status, 0, sizeof(struct ipf_debug));

	ipf_get_version();
    g_ipf_ctx.status->init_ok = IPF_ACORE_INIT_SUCCESS;

	dev_err(g_ipf_ctx.dev, "ipf init success\n");

	return 0;
}

/*����K3V3����������⣬ipf�޷���M3�ϻָ�ipf�Ĵ��������ƶ���acore��ccore*/

/*****************************************************************************
* �� �� ��       : ipf_drx_restore_filter
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ�����IPF�ϵ�ָ�
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ     : ��
*
* ע��:�ú�����Ҫ�����жϵ�����µ���
* �޸ļ�¼  : 2013��4��23��v1.00 chendongyue ����
			2014��1��23��v1.01 chendongyue ��ֲ��A9core
*****************************************************************************/
int ipf_drx_restore_filter(void)
{
    unsigned int i,j,k,filter_serial;
    IPF_MATCH_INFO_S* pstMatchInfo;
    unsigned int match_info;
    unsigned int* match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR);

    for(i=0 ; i < IPF_MODEM_MAX; i++)
    {
        match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR + i*sizeof(IPF_MATCH_INFO_S));
        pstMatchInfo = (IPF_MATCH_INFO_S*)match_info_addr;
        filter_serial = i;
        k = 0;
        do
        {
            if(filter_serial < IPF_BF_NUM)
            {
                ipf_writel(filter_serial, g_ipf_ctx.regs + HI_BFLT_INDEX_OFFSET);
                for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
                {
                        match_info = *(match_info_addr+j);
                        ipf_writel((match_info), (g_ipf_ctx.regs+HI_FLT_LOCAL_ADDR0_OFFSET+j*4));
                }
                k++;
            }
            filter_serial = pstMatchInfo->unFltChain.Bits.u16NextIndex;
            pstMatchInfo = (IPF_MATCH_INFO_S*)(IPF_PWRCTL_BASIC_FILTER_ADDR + filter_serial*sizeof(IPF_MATCH_INFO_S));
            match_info_addr = (unsigned int *)pstMatchInfo;
            if(k >= IPF_BF_NUM)
            {
                break;
            }
        }while(filter_serial != IPF_TAIL_INDEX);
    }

	g_ipf_ctx.status->flt_chain_loop = readl(g_ipf_ctx.regs + HI_FLT_CHAIN_LOOP_OFFSET);

    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��       : ipf_check_filter_restore
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ�����IPF�ϵ�ָ�
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ     : ��
*
*
* �޸ļ�¼  : 2014��1��23��v1.00 chendongyue����
*****************************************************************************/
void ipf_check_filter_restore(void)
{
	unsigned long ipf_flags = 0;
	unsigned int ipf_init_status = 0;
	spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
	bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);

	ipf_init_status = (*ipf_acore_init_status)|(*ipf_ccore_init_status);

	*ipf_acore_init_status = IPF_ACORE_INIT_SUCCESS;

	cache_sync();

	if(IPF_PWC_DOWN != ipf_init_status)
	{
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
		spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
		return;
	}
	else
	{
		ipf_drx_restore_filter();
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
		spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
		return;
	}
}


void bsp_ipf_set_debug_para(void ** psam_get_debug)
{
	*(psam_get_debug) = (void *)(g_ipf_ctx.status);
}

int bsp_ipf_srest(void)
{
	int tmp_cnt = 10000;
	/*reset*/
	ipf_writel(1, g_ipf_ctx.regs + HI_IPF_SRST_OFFSET);

	while(!ipf_readl(g_ipf_ctx.regs + HI_IPF_SRST_STATE_OFFSET)){
		tmp_cnt--;
		if(!tmp_cnt){
			return -1;
		}
	}
	/*start*/
	ipf_writel(0, g_ipf_ctx.regs + HI_IPF_SRST_OFFSET);

	ipf_writel(IPF_INT_OPEN0, g_ipf_ctx.regs + HI_IPF_INT_MASK0_OFFSET);
    ipf_writel(IPF_INT_OPEN1, g_ipf_ctx.regs + HI_IPF_INT_MASK1_OFFSET);
	return 0;
}

/*****************************************************************************
* �� �� ��      : bsp_ipf_config_timeout
*
* ��������  : ����ʹ�ã����ó�ʱʱ��ӿ�
*
* �������  : unsigned int u32Timeout ���õĳ�ʱʱ��
* �������  : ��
* �� �� ֵ     : IPF_SUCCESS    �ɹ�
*                           BSP_ERR_IPF_INVALID_PARA      ������Ч
*
* ˵��              : 1����256��ʱ������
*
* �޸ļ�¼   : 2011��11��30��   ³��  ����
*****************************************************************************/
int bsp_ipf_config_timeout(unsigned int u32Timeout)
{
    if((u32Timeout == 0) || (u32Timeout > 0xFFFF))
    {
    	dev_err(g_ipf_ctx.dev, "%s para invalid\n", __func__);
        return BSP_ERR_IPF_INVALID_PARA;
    }

    u32Timeout |= TIME_OUT_ENABLE;
    ipf_writel(u32Timeout, g_ipf_ctx.regs + HI_IPF_TIME_OUT_OFFSET);

    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��      : BSP_IPF_PktLen
*
* ��������  : �ýӿ��������ù�������������С����
*
* �������  : unsigned int MaxLen   ������
*                           unsigned int MinLen   ��С����
*
* �������   : ��
* �� �� ֵ      : IPF_SUCCESS                �ɹ�
*                           BSP_ERR_IPF_INVALID_PARA   ��������(����������С����С)
*
* �޸ļ�¼  :2011��2��17��   ³��  ����
*****************************************************************************/
int bsp_ipf_set_pktlen(unsigned int u32MaxLen, unsigned int u32MinLen)
{
    unsigned int u32PktLen = 0;

    /* ������� */
    if(u32MaxLen < u32MinLen)
    {
    	dev_err(g_ipf_ctx.dev, "%s para invalid\n", __func__);
        return BSP_ERR_IPF_INVALID_PARA;
    }

    u32PktLen = ((u32MaxLen&0x3FFF)<<16) | (u32MinLen&0x3FFF);

    ipf_writel(u32PktLen, g_ipf_ctx.regs + HI_IPF_PKT_LEN_OFFSET);
    return IPF_SUCCESS;
}/*lint !e550*/

/**********************************��ά�ɲ�ӿں���************************************/
void bsp_ipf_help(void)
{
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_info    ����1:ͨ������  0Ϊ���У�1Ϊ����\n");
    IPF_PRINT("bsp_ipf_mem 	   ��ӡipf share ddr ����\n");
    IPF_PRINT("bsp_ipf_bdinfo  ����1:ͨ������  ����2:BDָ��\n");
    IPF_PRINT("bsp_ipf_rdinfo  ����1:ͨ������  ����2:RDָ��\n");
    IPF_PRINT("bsp_ipf_adinfo  ����1:ͨ������  ����2:ADָ�����3:AD ��������0Ϊ��,1Ϊ��\n");
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_dump_bdinfo  ����1:ͨ������\n");
    IPF_PRINT("bsp_ipf_dump_rdinfo  ����1:ͨ������\n");
    IPF_PRINT("bsp_ipf_dump_adinfo  ����1:ͨ������\n");
    IPF_PRINT("===============================================\n");
	IPF_PRINT("bsp_ipf_show_status  ��ӡa/c������ʱ�����������Ϣ\n");
	IPF_PRINT("===============================================\n");
    IPF_PRINT("ipf_enable_ul_time_stamp  ����1:0-disable, 1-enable\n");
    IPF_PRINT("ipf_enable_dl_time_stamp  ����1:0-disable, 1-enable\n");
    IPF_PRINT("ipf_clear_time_stamp  ���ʵ�ʴ���¼\n");
    IPF_PRINT("ipf_dump_time_stamp  Linux:����ʱ���, vxWorks:����ʱ���\n");
    IPF_PRINT("===============================================\n");
}
void bsp_ipf_show_status(void)
{
	int i;
	struct ipf_debug* ptr = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR);

	g_ipf_ctx.status->flt_chain_loop = (int)readl(g_ipf_ctx.regs + HI_FLT_CHAIN_LOOP_OFFSET);

	printk("======acore only=======================");
	printk("ipf_rst_leave 		%d\n", g_ipf_ctx.ipf_rst_leave);
	printk("dont get acore seg  %d\n", g_ipf_ctx.not_get_space);

	for (i = 0; i < IPF_CHANNEL_MAX; i++) {
		printk("====ipf %score status====\n", i == 0 ? "a" : "c");
		printk("flt_chain_loop		%d\n", ptr->flt_chain_loop);
		printk("time_out_intr		%d\n", ptr->time_out_intr);
		printk("rd_comp_intr			%d\n", ptr->rd_comp_intr);
		printk("rd_full_intr			%d\n", ptr->rd_full_intr);
		printk("rd_full			%d\n", ptr->rd_full);
		printk("rd_cb			%d\n", ptr->rd_cb);
		printk("rd_cb_null		%d\n", ptr->rd_cb_null);
		printk("get_rd_num_times		%d\n", ptr->get_rd_num_times);
		printk("get_rd_times			%d\n", ptr->get_rd_times);
		printk("get_rd_short_cnt		%d\n", ptr->get_rd_cnt[IPF_AD_0]);
		printk("get_rd_long_cnt		%d\n", ptr->get_rd_cnt[IPF_AD_1]);
		printk("get_ad_num_times		%d\n", ptr->get_ad_num_times);
		printk("get_ad_thred		%d\n", ptr->ad_thred);
		printk("short_adq_empty_intr	%d\n", ptr->ad_epty_intr[IPF_AD_0]);
		printk("short_adq_cfg_count	%d\n", ptr->cfg_ad_cnt[IPF_AD_0]);
		printk("short_adq_out_ptr_null	%d\n", ptr->ad_out_ptr_null[IPF_AD_0]);
		printk("long_adq_cfg_count	%d\n", ptr->cfg_ad_cnt[IPF_AD_1]);
		printk("long_adq_empty_intr	%d\n", ptr->ad_epty_intr[IPF_AD_1]);
		printk("long_adq_out_ptr_null	%d\n", ptr->ad_out_ptr_null[IPF_AD_1]);
		printk("ad_epty_cb		%d\n", ptr->ad_epty_cb);
		printk("ad_epty_cb_null		%d\n", ptr->ad_epty_cb_null);
		printk("bd_epty_intr		%d\n", ptr->bd_epty_intr);
		printk("bd_epty_cb		%d\n", ptr->bd_epty_cb);
		printk("bd_epty_cb_null		%d\n", ptr->bd_epty_cb_null);
		printk("get_bd_num_times		%d\n", ptr->get_bd_num_times);
		printk("bd_cfg_times		%d\n", ptr->cfg_bd_times);
		printk("cfg_bd_cnt		%d\n", ptr->cfg_bd_cnt);
		printk("bd_full			%d\n", ptr->bd_full);
		printk("bd_len_zero_err		%d\n", ptr->bd_len_zero_err);
		printk("busy_cnt			%d\n", ptr->busy_cnt);
		printk("resume			%d\n", ptr->resume);
		printk("suspend			%d\n", ptr->suspend);
		printk("time_stamp_en		%d\n", ptr->timestamp_en);
		printk("rate_en			%d\n", ptr->rate_en);
		printk("init_ok			0x%x\n", ptr->init_ok);
		printk("mdrv_called_not_init	%d\n", ptr->mdrv_called_not_init);
		printk("invalid_para		%d\n", ptr->invalid_para);
		printk("debug			%d\n", ptr->debug);
		printk("scr wr			%d\n", ptr->reg_scur_wr_err);
		printk("scr rd			%d\n", ptr->reg_scur_rd_err);
		printk("ccore rst idle err		%d\n", ptr->ccore_rst_err);
		printk("========================\n");
		ptr++;
	}
}

int bsp_ipf_bdinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32BdqPtr)
{
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32BdqPtr >= IPF_ULBD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("==========BD Info=========\n");
            IPF_PRINT("BDλ��:         %d\n",u32BdqPtr);
            IPF_PRINT("u16Attribute:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:      %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
            IPF_PRINT("u16Resv:        %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
			IPF_PRINT("BD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfBDQ + u32BdqPtr));
			IPF_PRINT("BD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfBDQ + u32BdqPtr)));
            break;
       case IPF_CHANNEL_DOWN:
            if(u32BdqPtr >= IPF_DLBD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("==========BD Info=========\n");
            IPF_PRINT("BDλ��:         %d\n",u32BdqPtr);
            IPF_PRINT("u16Attribute:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:      %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
            IPF_PRINT("u16Resv:        %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
			IPF_PRINT("BD Desc Virt Addr:	0x%x\n",(g_stIpfDl.pstIpfBDQ + u32BdqPtr));
			IPF_PRINT("BD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfDl.pstIpfBDQ + u32BdqPtr)));
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}

int bsp_ipf_dump_bdinfo(IPF_CHANNEL_TYPE_E eChnType)
{
    unsigned int i;
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:

            for(i = 0;i < IPF_ULBD_DESC_SIZE;i++)
            {
                bsp_ipf_bdinfo(IPF_CHANNEL_UP,i);
            }
        break;

        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLBD_DESC_SIZE;i++)
            {
                bsp_ipf_bdinfo(IPF_CHANNEL_DOWN,i);
            }
        break;

        default:
        IPF_PRINT("Input param invalid ! \n");
        break;

    }
    return 0;
}

unsigned long bsp_ipf_ad0_info(unsigned long *ad0_addr)
{
	*ad0_addr = IPF_DLAD0_MEM_ADDR;
	return IPF_DLAD0_MEM_SIZE;
}

unsigned long bsp_ipf_ad1_info(unsigned long *ad1_addr)
{
	*ad1_addr = IPF_DLAD1_MEM_ADDR;
	return IPF_DLAD1_MEM_SIZE;
}

int bsp_ipf_rdinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32RdqPtr)
{
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32RdqPtr >= IPF_ULRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("===========RD Info==========\n");
            IPF_PRINT("RDλ��:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
			IPF_PRINT("RD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfRDQ + u32RdqPtr));
			IPF_PRINT("RD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfRDQ + u32RdqPtr)));
            break;
       case IPF_CHANNEL_DOWN:
            if(u32RdqPtr >= IPF_DLRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("============RD Info===========\n");
            IPF_PRINT("RDλ��:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
			IPF_PRINT("RD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfRDQ + u32RdqPtr));
			IPF_PRINT("RD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfRDQ + u32RdqPtr)));
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}


int bsp_ipf_dump_rdinfo(IPF_CHANNEL_TYPE_E eChnType)
{
    int i;

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:

            for(i = 0;i < IPF_ULBD_DESC_SIZE;i++)
            {
                bsp_ipf_rdinfo(IPF_CHANNEL_UP,i);
            }
        break;

        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLBD_DESC_SIZE;i++)
            {
                bsp_ipf_rdinfo(IPF_CHANNEL_DOWN,i);
            }
        break;
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;
    }
    return 0;
}
int bsp_ipf_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdqPtr, unsigned int u32AdType)
{

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32AdqPtr >= IPF_ULAD0_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            if(0 == u32AdType)
            {
                 IPF_PRINT("===========UL AD0 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfUl.pstIpfADQ0[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfUl.pstIpfADQ0[u32AdqPtr].u32OutPtr1);
            }
            else
            {
                 IPF_PRINT("===========UL AD1 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfUl.pstIpfADQ1[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfUl.pstIpfADQ1[u32AdqPtr].u32OutPtr1);
            }
            break;
       case IPF_CHANNEL_DOWN:
            if(u32AdqPtr >= IPF_ULAD1_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            if(0 == u32AdType)
	      	{
                 IPF_PRINT("===========DL AD0 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfDl.pstIpfADQ0[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfDl.pstIpfADQ0[u32AdqPtr].u32OutPtr1);
            }
            else
            {
                 IPF_PRINT("===========DL AD1 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfDl.pstIpfADQ1[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfDl.pstIpfADQ1[u32AdqPtr].u32OutPtr1);
            }
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}


int bsp_ipf_dump_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdType)
{
    int i;

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            for(i = 0;i < IPF_ULAD0_DESC_SIZE;i++)
            {
                bsp_ipf_adinfo(IPF_CHANNEL_UP, i, u32AdType);
            }
        break;

        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLAD1_DESC_SIZE;i++)
            {
                bsp_ipf_adinfo(IPF_CHANNEL_DOWN, i, u32AdType);
            }
        break;

        default:
        IPF_PRINT("Input param invalid ! \n");
        break;
    }
    return 0;
}

int bsp_ipf_info(IPF_CHANNEL_TYPE_E eChnType)
{
    unsigned int u32BdqDepth = 0;
    unsigned int u32BdqWptr = 0;
    unsigned int u32BdqRptr = 0;
    unsigned int u32BdqWaddr = 0;
    unsigned int u32BdqRaddr = 0;
    unsigned int u32RdqDepth = 0;
    unsigned int u32RdqRptr = 0;
    unsigned int u32RdqWptr = 0;
    unsigned int u32RdqWaddr = 0;
    unsigned int u32RdqRaddr = 0;
    unsigned int u32Depth = 0;
    unsigned int u32status = 0;

    unsigned int u32Adq0Rptr = 0;
    unsigned int u32Adq0Wptr = 0;

    unsigned int u32Adq1Rptr = 0;
    unsigned int u32Adq1Wptr = 0;

    if(IPF_CHANNEL_UP == eChnType)
    {
        u32Depth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_DQ_DEPTH_OFFSET);
        u32RdqDepth = (u32Depth>>16)&IPF_DQ_DEPTH_MASK;
        u32BdqDepth = u32Depth&IPF_DQ_DEPTH_MASK;

        u32status = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_STATE_OFFSET);

        u32BdqWptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WPTR_OFFSET);
        u32BdqRptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_RPTR_OFFSET);
        u32BdqWaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WADDR_OFFSET);
        u32BdqRaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_RADDR_OFFSET);

        u32RdqWptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_RDQ_WPTR_OFFSET);
        u32RdqRptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_RDQ_RPTR_OFFSET);
        u32RdqWaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_RDQ_WADDR_OFFSET);
        u32RdqRaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_RDQ_RADDR_OFFSET);

        u32Adq0Rptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
        u32Adq0Wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_WPTR_OFFSET);

        u32Adq1Rptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
        u32Adq1Wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_WPTR_OFFSET);

    }
    else if(IPF_CHANNEL_DOWN == eChnType)
    {
        u32Depth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_DQ_DEPTH_OFFSET);
        u32RdqDepth = (u32Depth>>16)&IPF_DQ_DEPTH_MASK;
        u32BdqDepth = u32Depth&IPF_DQ_DEPTH_MASK;

        u32status = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_STATE_OFFSET);

        u32BdqWptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_BDQ_WPTR_OFFSET);
        u32BdqRptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_BDQ_RPTR_OFFSET);
        u32BdqWaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_BDQ_WADDR_OFFSET);
        u32BdqRaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_BDQ_RADDR_OFFSET);

        u32RdqWptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_RDQ_WPTR_OFFSET);
        u32RdqRptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_RDQ_RPTR_OFFSET);
        u32RdqWaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_RDQ_WADDR_OFFSET);
        u32RdqRaddr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_RDQ_RADDR_OFFSET);

        u32Adq0Rptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
        u32Adq0Wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);

        u32Adq1Rptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
        u32Adq1Wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);

    }
    else
    {
        return 1;
    }
    IPF_PRINT("============================\n");
    IPF_PRINT("ͨ�� ״̬:            0x%x\n", u32status);
    IPF_PRINT("BD ���:            %d\n", u32BdqDepth);
    IPF_PRINT("BD дָ��:          %d\n", u32BdqWptr);
    IPF_PRINT("BD ��ָ��:          %d\n", u32BdqRptr);
    IPF_PRINT("BD д��ַ:          0x%x\n", u32BdqWaddr);
    IPF_PRINT("BD ����ַ:          0x%x\n", u32BdqRaddr);
    IPF_PRINT("RD ���:            %d\n", u32RdqDepth);
    IPF_PRINT("RD ��ָ��:          %d\n", u32RdqRptr);
    IPF_PRINT("RD дָ��:          %d\n", u32RdqWptr);
    IPF_PRINT("RD ����ַ:          0x%x\n", u32RdqRaddr);
    IPF_PRINT("RD д��ַ:          0x%x\n", u32RdqWaddr);

    IPF_PRINT("AD0 ��ָ��:          %d\n", u32Adq0Rptr);
    IPF_PRINT("AD0 дָ��:          %d\n", u32Adq0Wptr);

    IPF_PRINT("AD1 ��ָ��:          %d\n", u32Adq1Rptr);
    IPF_PRINT("AD1 дָ��:          %d\n", u32Adq1Wptr);
    IPF_PRINT("============================\n");
    return 0;
}

void bsp_ipf_mem(void)
{
	ipf_ddr_t *ddr_info;
	unsigned int dl_start = IPF_DLBD_MEM_ADDR;
	ipf_get_shared_ddr();
	ddr_info= &g_ipf_ctx.status->share_ddr_info;

	IPF_PRINT("IPF Shared DDR information:\n");
	IPF_PRINT("start                 0x%x \n", ddr_info->start);
	IPF_PRINT("ul_start              0x%x \n", ddr_info->ul_start);
	IPF_PRINT("dl_start              0x%x \n", dl_start);
	IPF_PRINT("filter_pwc_start      0x%x \n", ddr_info->filter_pwc_start);
	IPF_PRINT("pwc_info_start        0x%x \n", ddr_info->pwc_info_start);
	IPF_PRINT("dlcdrptr              0x%x \n", ddr_info->dlcdrptr);
	IPF_PRINT("debug_dlcd_start      0x%x \n", ddr_info->debug_dlcd_start);
	IPF_PRINT("debug_dlcd_size       0x%x \n", ddr_info->debug_dlcd_size);
	IPF_PRINT("end                   0x%x \n", ddr_info->end);
	IPF_PRINT("len(The max:0x10000)  0x%x \n", ddr_info->len);

    IPF_PRINT("=======================================\n");
    IPF_PRINT("   bsp_ipf_mem          ADDR            SIZE\n");
    IPF_PRINT("%s%lx\t\t%lu\n", "IPF_ULBD_MEM_ADDR    ", IPF_ULBD_MEM_ADDR, (unsigned long)IPF_ULBD_MEM_SIZE);
    IPF_PRINT("%s%lx\t\t%lu\n", "IPF_ULRD_MEM_ADDR    ", IPF_ULRD_MEM_ADDR, (unsigned long)IPF_ULRD_MEM_SIZE);
    IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLBD_MEM_ADDR    ", IPF_DLBD_MEM_ADDR, (unsigned long)IPF_DLBD_MEM_SIZE);
    IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLRD_MEM_ADDR    ", IPF_DLRD_MEM_ADDR, (unsigned long)IPF_DLRD_MEM_SIZE);
    IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLCD_MEM_ADDR    ", IPF_DLCD_MEM_ADDR, (unsigned long)IPF_DLCD_MEM_SIZE);
    IPF_PRINT("%s%lx\t\t%d\n", "IPF_INIT_ADDR        ", IPF_INIT_ADDR, IPF_INIT_SIZE);
    IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DEBUG_INFO_ADDR  ", IPF_DEBUG_INFO_ADDR, (unsigned long)IPF_DEBUG_INFO_SIZE);
}

void bsp_set_init_status(int stat)
{
    g_ipf_ctx.status->init_ok = stat;    
}

int bsp_get_init_status(void)
{
    return g_ipf_ctx.status->init_ok;    
}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_reinit_dlreg
*
* ��������  : Ccore��λʱ,IPF����֮��λ,��Ĵ�����Ϣ��ȫ����ʧ��
				  �ú�����ccore��λ���⸴λ�������ɹ���,
				  ��ADS�ص����������ȵ���,������������IPF����ͨ����ؼĴ���

*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : ��
*
* �޸ļ�¼  :2013��9��1��   �¶�������
*****************************************************************************/
void mdrv_ipf_reinit_dlreg(void)
{
	/*����IPF����ͨ���Ĵ���*/
    memset((void*)IPF_DLBD_MEM_ADDR, 0x0, IPF_DLDESC_SIZE);

    g_stIpfUl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_ULBD_MEM_ADDR;
    g_stIpfUl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_ULRD_MEM_ADDR;
    g_stIpfUl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_ULAD0_MEM_ADDR;
    g_stIpfUl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_ULAD1_MEM_ADDR;
    g_stIpfUl.pu32IdleBd = (unsigned int*)IPF_ULBD_IDLENUM_ADDR;

    g_stIpfDl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_DLBD_MEM_ADDR;
    g_stIpfDl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_DLRD_MEM_ADDR;
    g_stIpfDl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_DLAD0_MEM_ADDR;
    g_stIpfDl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_DLAD1_MEM_ADDR;
    g_stIpfDl.pstIpfCDQ = (IPF_CD_DESC_S*)IPF_DLCD_MEM_ADDR;

    g_stIpfDl.pstIpfPhyBDQ = (IPF_BD_DESC_S *)SHD_DDR_V2P((void *)IPF_DLBD_MEM_ADDR);
    g_stIpfDl.pstIpfPhyRDQ = (IPF_RD_DESC_S *)SHD_DDR_V2P((void *)IPF_DLRD_MEM_ADDR);
    g_stIpfDl.pstIpfPhyADQ0 = (IPF_AD_DESC_S *)SHD_DDR_V2P((void *)IPF_DLAD0_MEM_ADDR);
    g_stIpfDl.pstIpfPhyADQ1 = (IPF_AD_DESC_S *)SHD_DDR_V2P((void *)IPF_DLAD1_MEM_ADDR);

    g_stIpfDl.u32IpfCdRptr = (unsigned int*) IPF_DLCDRPTR_MEM_ADDR;
    *(g_stIpfDl.u32IpfCdRptr) = 0;
    /* ��������ͨ����AD��BD��RD��� */
    ipf_writel(IPF_DLBD_DESC_SIZE - 1, g_ipf_ctx.regs + HI_IPF_CH1_BDQ_SIZE_OFFSET);
    ipf_writel(IPF_DLRD_DESC_SIZE - 1, g_ipf_ctx.regs + HI_IPF_CH1_RDQ_SIZE_OFFSET);

	ipf_writel(IPF_ADQ_DEFAULT_SEETING, g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);


    /*����ͨ����BD��RD��ʼ��ַ*/
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyBDQ, g_ipf_ctx.regs + HI_IPF_CH1_BDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyRDQ, g_ipf_ctx.regs + HI_IPF_CH1_RDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyADQ0, g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_BASE_OFFSET);
    ipf_writel((unsigned int)(unsigned long)g_stIpfDl.pstIpfPhyADQ1, g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_BASE_OFFSET);


    g_ipf_ctx.status->init_ok = IPF_ACORE_INIT_SUCCESS;

    dev_err(g_ipf_ctx.dev, "ipf dl register reinit success\n");

    return;

}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_used_dlad
*
* ��������  : ����ͬV9R1��ͬ�����������ڻ�ȡ���ø�AD���еģ�
				  ����δ��Ӳ��ʹ�õ�AD��Ϣ���������ͷŻ�ȡ��AD
				  �ж�Ӧ��skb(IMM_Zc)���Է�ֹCcore resetʱ�ڴ�й¶
				  ���øú����ڼ䣬Ӧ��ֹ����BD��
				  �ú�������ʱ��ر�ͨ��

* �������  : eAdType: AD��������
*
* �������  : pu32AdNum: ��Ҫ�ͷŵ�AD��Ŀ
				  pstAdDesc: ��Ҫ�ͷŵ�AD����ͷָ��
*
* �� �� ֵ     : BSP_ERR_IPF_INVALID_PARA ��ηǷ�
				  IPF_ERROR ʧ��
*				  IPF_SUCCESS �ɹ�
* �޸ļ�¼  :2013��9��1��   �¶�������
*****************************************************************************/
int bsp_ipf_get_used_dlad(IPF_AD_TYPE_E eAdType, unsigned int * pu32AdNum, IPF_AD_DESC_S * pstAdDesc)
{
	unsigned int u32Timeout = 10;
	unsigned int u32DlStateValue;
	unsigned int u32ChanEnable;
	unsigned int u32AdStateValue;
	unsigned int u32FreeAdNum = 0;
	unsigned int u32ADQwptr;
	unsigned int u32ADQrptr;
	unsigned int u32ADCtrl;

	/*��μ��*/
	if((NULL == pu32AdNum)||(NULL == pstAdDesc))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_ConfigDlAd input para ERROR!NULL == pu32AdNum or NULL == pstAdDesc\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}
	/*�ر�����AD���ýӿ�*/
	if (g_ipf_ctx.status) {
		g_ipf_ctx.status->init_ok = 0;
	}
	/*�ȴ�ͨ��idle ,200ms��ʱ*/
	do
	{
		u32DlStateValue = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_STATE_OFFSET);
		if(u32DlStateValue == IPF_CHANNEL_STATE_IDLE)
		{
			break;
		}
		msleep(20);
	}while(--u32Timeout);
	if (!u32Timeout)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r After 20ms IPF dl channel still on, unable to free AD \n");
		return IPF_ERROR;
	}
	/*���Թر�����ͨ��*/
	u32ChanEnable = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH_EN_OFFSET);
	u32ChanEnable &= 0xFFFFFFFF ^ (0x1<<IPF_CHANNEL_DOWN);
	ipf_writel(u32ChanEnable, g_ipf_ctx.regs + HI_IPF_CH_EN_OFFSET);

	u32ADCtrl = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);
	u32ADCtrl &= IPF_ADQ_EN_MASK;
	u32ADCtrl |= (IPF_NONE_ADQ_EN);

	/*�ر�AD�����ڷ�ֹ����ADQԤȡ*/
	ipf_writel(u32ADCtrl, g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);
	if(IPF_AD_0 == eAdType)
	{
		u32AdStateValue = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_STAT_OFFSET);/*[false alarm]:fortify*/
		/*����AD��ָ��*/
		u32ADQwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
		u32ADQrptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
		while(u32ADQrptr != u32ADQwptr)
		{
			pstAdDesc->u32OutPtr1 = g_stIpfDl.pstIpfADQ0[u32ADQrptr].u32OutPtr1;
			pstAdDesc->u32OutPtr0 = g_stIpfDl.pstIpfADQ0[u32ADQrptr].u32OutPtr0;
			//printk("AD0[%u]OutPtr1 = 0x%x \n", u32ADQrptr, pstAdDesc->u32OutPtr1);
			u32ADQrptr = ((u32ADQrptr + 1) < IPF_DLAD0_DESC_SIZE)? (u32ADQrptr + 1) : 0;
			pstAdDesc++;
			u32FreeAdNum++;
		}
	}
	else if(IPF_AD_1 == eAdType)
	{
		u32AdStateValue = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_STAT_OFFSET);/*[false alarm]:fortify*/
		/*����AD��ָ��*/
		u32ADQwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
		u32ADQrptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
		while(u32ADQrptr != u32ADQwptr)
		{
			pstAdDesc->u32OutPtr1 = g_stIpfDl.pstIpfADQ1[u32ADQrptr].u32OutPtr1;
			pstAdDesc->u32OutPtr0 = g_stIpfDl.pstIpfADQ1[u32ADQrptr].u32OutPtr0;
			//printk("AD1[%u]OutPtr1 = 0x%x", u32ADQrptr, pstAdDesc->u32OutPtr1);
			u32ADQrptr = ((u32ADQrptr + 1) < IPF_DLAD1_DESC_SIZE)? (u32ADQrptr + 1) : 0;
			pstAdDesc++;
			u32FreeAdNum++;
		}
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_ConfigDlAd input para ERROR! u32AdType >= IPF_AD_MAX\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}
	/*����AD*/
	*pu32AdNum = u32FreeAdNum;
	return IPF_SUCCESS;

}

int mdrv_ipf_get_used_dlad(IPF_AD_TYPE_E eAdType, unsigned int * pu32AdNum, IPF_AD_DESC_S * pstAdDesc)
{	
	return bsp_ipf_get_used_dlad(eAdType, pu32AdNum, pstAdDesc);
}


/*****************************************************************************
* �� �� ��     : bsp_ipf_set_control_flag_for_ccore_reset
*
* ��������  : modem������λipf���亯���������ڸ�λʱ��ֹ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :	2013��4��19��   ¬��ʤ����
					2013��6��16��   �¶������䵽V7R2
*****************************************************************************/
void bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_E eResetFlag)
{
    if(eResetFlag >= IPF_FORRESET_CONTROL_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r bsp_ipf_set_control_flag_for_ccore_reset eResetFlag overflow! \n");
        return;
    }
    /*���ñ�־����ֹ��������*/
    g_eCcoreResetFlag = eResetFlag;
    /*���ñ�־����ֹ��������*/
    *modem_reset_flag = eResetFlag;
    cache_sync();
}

/*****************************************************************************
* �� �� ��     : bsp_ipf_get_control_flag_for_ccore_reset
*
* ��������  : modem������λipf���亯���������ڸ�λʱ��ֹ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
*****************************************************************************/
static IPF_FORRESET_CONTROL_E bsp_ipf_get_control_flag_for_ccore_reset(void)
{
    return g_eCcoreResetFlag;
}

int bsp_ipf_reset_ccore_cb(DRV_RESET_CB_MOMENT_E eparam, int userdata)
{
	unsigned int u32Timeout = 30;
	unsigned int idle_cnt = 10;
	unsigned int time_out = 2000;
	unsigned int u32DlStateValue;
	unsigned int psam_status = 0;
	if(MDRV_RESET_CB_BEFORE == eparam)
	{
		bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_FORBID);

		if(g_ipf_ctx.ipf_version >= IPF_VERSION_130b){
			do{
				udelay(2);	//wait cipher idle
				u32DlStateValue = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_STATE_OFFSET);
				psam_status = bsp_psam_idle();
				time_out--;
				if((u32DlStateValue == IPF_CHANNEL_STATE_IDLE) && psam_status){
					idle_cnt--;
				}else{
					idle_cnt = 10;
				}
			}while(idle_cnt && time_out);

			if(!idle_cnt){
				ccore_rst_idle = 1;
			}

			if (!time_out)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,
					"\r IPF dl channel on after bsp_ipf_reset_ccore_cb called \n");
			}
		}else{
		do
		{
			u32DlStateValue = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_STATE_OFFSET);
			if(u32DlStateValue == IPF_CHANNEL_STATE_IDLE)
			{
				break;
			}
				msleep(10);
			}while(--u32Timeout);
			if (!u32Timeout)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,
					"\r IPF dl channel on after bsp_ipf_reset_ccore_cb called \n");
			}else{
				ccore_rst_idle = 1;
			}
		}
	}
	else if(MDRV_RESET_CB_AFTER == eparam)
	{
		ccore_rst_idle = 0;
		bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_ALLOW);
		return IPF_SUCCESS;
	}
	else
	{
		/*under the requeset of yaoguocai*/
		return IPF_SUCCESS;
	}
	return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : BSP_IPF_ConfigDlAd
*
* ��������  : �ýӿڽ���A���ṩ�������ƶ�ADQдָ�룬
				�����е�AD�����µ��ڴ滺������һ�ο��Դ�����AD��
				����ǰҪ��������������仺������
*
* �������  : unsigned int u32ADNum0;
				 unsigned int u32ADNum1;
				 void* psk0;
				 void* psk1
*
* �������  : ��
* �� �� ֵ      : ��
* �޸ļ�¼  :2012��11��24��   �¶���  ����
*****************************************************************************/
int ipf_config_dl_ad(unsigned int u32AdType, unsigned int  u32AdNum, IPF_AD_DESC_S * pstAdDesc)
{
	unsigned int u32ADQwptr = 0;
	struct tagIPF_AD_DESC_S * pstADDesc = pstAdDesc;
	IPF_DL_S* dl_ad = &g_stIpfDl;
	unsigned int i;

	g_ipf_ctx.status->cfg_ad_times++;
	if(NULL == pstAdDesc || u32AdType >= IPF_AD_MAX)
	{
		pr_err("%s para invalid\n", __func__);
		g_ipf_ctx.status->invalid_para++;
		return BSP_ERR_IPF_INVALID_PARA;
	}

	/* ���ģ���Ƿ��ʼ�� */
	if(g_ipf_ctx.status && (IPF_ACORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok))
	{
		g_ipf_ctx.status->mdrv_called_not_init++;
		pr_err("%s ipf not init\n", __func__);
		return BSP_ERR_IPF_NOT_INIT;
	}


	if(IPF_AD_0 == u32AdType)
	{
		if(u32AdNum >= IPF_DLAD0_DESC_SIZE)
		{
			pr_err("%s too much short ad num\n", __func__);
			g_ipf_ctx.status->invalid_para++;
			return BSP_ERR_IPF_INVALID_PARA;
		}

		/*����дָ��*/
		u32ADQwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
		for(i=0; i < u32AdNum; i++)
		{
			if(0 == pstADDesc->u32OutPtr1)
			{
				pr_err("%s the %d short ad outptr is null\n", __func__, i);
				g_ipf_ctx.status->ad_out_ptr_null[IPF_AD_0]++;
				return BSP_ERR_IPF_INVALID_PARA;
			}
			dl_ad->pstIpfADQ0[u32ADQwptr].u32OutPtr1 = pstADDesc->u32OutPtr1;
			dl_ad->pstIpfADQ0[u32ADQwptr].u32OutPtr0 = pstADDesc->u32OutPtr0;
			u32ADQwptr = ((u32ADQwptr + 1) < IPF_DLAD0_DESC_SIZE)? (u32ADQwptr + 1) : 0;
			pstADDesc++;
		}
		g_ipf_ctx.status->cfg_ad_cnt[IPF_AD_0] += u32AdNum;
		/* ����AD0дָ��*/
		ipf_writel(u32ADQwptr, g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
	}
	else if(IPF_AD_1 == u32AdType)
	{
		if(u32AdNum >= IPF_DLAD1_DESC_SIZE)
		{
			pr_err("%s too much long ad num\n", __func__);
			g_ipf_ctx.status->invalid_para++;
			return BSP_ERR_IPF_INVALID_PARA;
		}

		/*����дָ��*/
		u32ADQwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
		for(i=0; i < u32AdNum; i++)
		{
			if(0 == pstADDesc->u32OutPtr1)
			{
				pr_err("%s the %d long ad outptr is null\n", __func__, i);
				g_ipf_ctx.status->ad_out_ptr_null[IPF_AD_1]++;
				return BSP_ERR_IPF_INVALID_PARA;
			}

			dl_ad->pstIpfADQ1[u32ADQwptr].u32OutPtr1 = pstADDesc->u32OutPtr1;
			dl_ad->pstIpfADQ1[u32ADQwptr].u32OutPtr0 = pstADDesc->u32OutPtr0;
			u32ADQwptr = ((u32ADQwptr + 1) < IPF_DLAD1_DESC_SIZE)? (u32ADQwptr + 1) : 0;
			pstADDesc++;
		}
		g_ipf_ctx.status->cfg_ad_cnt[IPF_AD_1] += u32AdNum;

		/* ����AD1дָ��*/
		ipf_writel(u32ADQwptr, g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
	}
	return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��       : BSP_IPF_GetDlAdNum
*
* ��������  : �ýӿ�ֻ��A���ṩ����ȡ���У�A�ˣ�
					����(�������AD�Ļ������Ѿ���ռ��)AD��Ŀ
*
* �������  :BSP_OK����������
                            BSP_ERROR������
*
* �������  : ��
* �� �� ֵ     : ��
* �޸ļ�¼  : 2011��11��24��   �¶���  ����
*****************************************************************************/
int ipf_get_dl_ad_num(unsigned int* pu32AD0Num,unsigned int* pu32AD1Num)
{
	unsigned int u32DlAdDepth = 0;
	unsigned int u32DlAdwptr = 0;
	unsigned int u32DlAdrptr = 0;

	/* ���ģ���Ƿ��ʼ�� */

	/*��μ��*/
	if((NULL == pu32AD0Num)||(NULL == pu32AD1Num))
	{
		g_ipf_ctx.status->invalid_para++;
		pr_err("%s para invalid\n", __func__);
		return BSP_ERR_IPF_INVALID_PARA;
	}

	if(g_ipf_ctx.status && (IPF_ACORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok))
	{
		g_ipf_ctx.status->mdrv_called_not_init++;
		pr_err("%s ipf not init\n", __func__);
		return BSP_ERR_IPF_NOT_INIT;
	}

	/* �������AD0���� */
	u32DlAdwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
	u32DlAdrptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
	if (u32DlAdwptr >= u32DlAdrptr)/*дָ����ǰ������˳����ָ����ȵ�������Ϊ0*/
	{
		u32DlAdDepth = IPF_DLAD0_DESC_SIZE - (u32DlAdwptr - u32DlAdrptr);
	}
	else
	{
		u32DlAdDepth = u32DlAdrptr -u32DlAdwptr;
	}

	/*�۳�reserve ad�����ڷ�ֹӲ����ad������ʶ��ɿպ͵͹��������ڴ�й¶*/
	if(u32DlAdDepth > IPF_ADQ_RESERVE_NUM)
	{
		*pu32AD0Num = u32DlAdDepth - IPF_ADQ_RESERVE_NUM;
	}
	else
	{
		*pu32AD0Num = 0;
	}

	/* �������AD1���� */
	u32DlAdwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
	u32DlAdrptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
	if (u32DlAdwptr >= u32DlAdrptr)/*дָ����ǰ������˳��*/
	{
		u32DlAdDepth = IPF_DLAD1_DESC_SIZE - (u32DlAdwptr - u32DlAdrptr);
	}
	else
	{
		u32DlAdDepth =  u32DlAdrptr - u32DlAdwptr;
	}
	*pu32AD1Num = u32DlAdDepth;

	/*�۳�reserve ad�����ڷ�ֹӲ����ad������ʶ��ɿպ͵͹��������ڴ�й¶*/
	if(u32DlAdDepth > IPF_ADQ_RESERVE_NUM)
	{
		*pu32AD1Num = u32DlAdDepth - IPF_ADQ_RESERVE_NUM;
	}
	else
	{
		*pu32AD1Num = 0;
	}

	return IPF_SUCCESS;
}


/*****************************************************************************
* �� �� ��     : BSP_IPF_RegisterWakeupDlCb
*
* ��������  : �ýӿ�����ע������PS����ص�����
*
* �������  : BSP_IPF_WakeupDlkCb *pFnWakeupDl
*
* �������  : ��
* �� �� ֵ      : ��
*
* �޸ļ�¼  :2011��11��30��   ³��  ����
*****************************************************************************/
int ipf_register_wakeup_dlcb(BSP_IPF_WakeupDlCb pFnWakeupDl)
{
    /* ������� */
    if(NULL == pFnWakeupDl)
    {
    	g_ipf_ctx.status->invalid_para++;
    	pr_err("%s invalid para\n", __func__);
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_stIpfDl.pFnDlIntCb = pFnWakeupDl;
    return IPF_SUCCESS;
}


int ipf_register_ul_bd_empty(ipf_bd_empty bd_handle)
{
   if(NULL == bd_handle)
    {
    	g_ipf_ctx.status->invalid_para++;
    	pr_err("%s invalid para\n", __func__);
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_stIpfUl.handle_bd_empty = bd_handle;
	return 0;
}


/*****************************************************************************
* �� �� ��     : IPF_RegisterAdqEmptyDlCb
*
* ��������  : �˽ӿ�ֻ��A���ṩ������ע�ỽ������PS��
                             ADQ���пջص�����
*
* �������  : BSP_IPF_AdqEmptyCb pAdqEmptyDl
*
* �������  : ��
* �� �� ֵ      : IPF_SUCCESS ע��ɹ�
*                            IPF_ERROR	ע��ʧ��
* �޸ļ�¼  :2012��11��24��   �¶���  ����
*****************************************************************************/
int ipf_register_adq_empty_dlcb(BSP_IPF_AdqEmptyDlCb pAdqEmptyDl)
{
    /* ������� */
    if(NULL == pAdqEmptyDl)
    {
    	g_ipf_ctx.status->invalid_para++;
    	pr_err("%s invalid para\n", __func__);
        return IPF_ERROR;
    }
    g_stIpfDl.pAdqEmptyDlCb = pAdqEmptyDl;
    return IPF_SUCCESS;
}


int ipf_rd_rate(unsigned int enable, IPF_CHANNEL_TYPE_E eChnType)
{
	unsigned int rate = 0;
	unsigned int rd_len = 0;
	unsigned int rd_ts =  0;
	unsigned int ratio = IPF_LEN_RATIO / (IPF_TIMER_RATIO * 8);

	if(!enable) {
		return IPF_ERROR;
	}

	if(eChnType > IPF_CHANNEL_DOWN){
		IPF_PRINT("eChnType err!\n");
		return IPF_ERROR;
	}

	switch(eChnType)
    {
		case IPF_CHANNEL_DOWN:
			rd_ts =  bsp_get_slice_value() - g_ipf_ctx.status->rd_ts;
			if(rd_ts < IPF_RD_TMOUT) {
				return IPF_ERROR;
			}

			rd_len = g_ipf_ctx.status->rd_len_update - g_ipf_ctx.status->rd_len;
			g_ipf_ctx.status->rd_ts = bsp_get_slice_value();
			g_ipf_ctx.status->rd_len = g_ipf_ctx.status->rd_len_update;
			break;
		default:
            break;
	}

	if(rd_len <= 0 || rd_ts <= 0) {
		IPF_PRINT("ipf rd len or ts err!\n");
		return IPF_ERROR;
	} else {
		rate = rd_len / (rd_ts * ratio);
		IPF_PRINT("ipf rd rate:%uMbps\n", rate);
	}

	return IPF_SUCCESS;
}


/******************************************************************************
* �� �� ��     : mdrv_ipf_get_ulbd_num
*
* ��������  : �ýӿ����ڻ�ȡ���п���BD ��Ŀ
*                            ��Χ: 0~64
* �������  : ��
*
* �������  : ��
* �� �� ֵ      : ����BD��Ŀ
*
* �޸ļ�¼  :2011��11��30��   ³��  ����
*****************************************************************************/
unsigned int mdrv_ipf_get_ulbd_num(void)
{
    unsigned int u32UlBdDepth = 0;
    unsigned int u32IdleBd = 0;

	g_ipf_ctx.status->get_bd_num_times++;
    /* �������BD���� */
    u32UlBdDepth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_DQ_DEPTH_OFFSET);

    u32IdleBd = IPF_ULBD_DESC_SIZE - (u32UlBdDepth & IPF_DQ_DEPTH_MASK);
    *(g_stIpfUl.pu32IdleBd) = u32IdleBd;

    if(0 == u32IdleBd)
	{
		g_ipf_ctx.status->bd_full++;
	}
    return u32IdleBd;
}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_ulrd_num
*
* ��������  : �ýӿ����ڶ�ȡ����RD��Ŀ
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : ����RD��Ŀ
*
* �޸ļ�¼  :2013��8��1��   chendongyue  ����
*****************************************************************************/
unsigned int mdrv_ipf_get_ulrd_num(void)
{
    unsigned int u32RdqDepth = 0;

    /* ��ȡRD��� */
    u32RdqDepth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    return u32RdqDepth;
}


/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_uldesc_num
*
* ��������  : �ýӿڿɶ�ȡ���пɴ������
			���ڹ��ipfӲ����ͷ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : ���пɷ��Ͱ���
*
* �޸ļ�¼  :2013��8��1��   chendongyue  ����
*****************************************************************************/

unsigned int mdrv_ipf_get_uldesc_num(void)
{
	unsigned int u32UlAd0Num = 0;
	unsigned int u32UlAd1Num = 0;
	unsigned int u32UlBdNum = 0;
/*	unsigned int u32UlRdNum = 0;*/
	unsigned int u32UlAdwptr = 0;
	unsigned int u32UlAdrptr = 0;
	unsigned int u32UlBdDepth = 0;

	u32UlBdNum = mdrv_ipf_get_ulbd_num();
	if(g_ipf_ctx.ipf_version < IPF_VERSION_120a){
		/* �������AD0���� */
		u32UlBdDepth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_DQ_DEPTH_OFFSET);
		u32UlAdwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_WPTR_OFFSET);
		u32UlAdrptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
		u32UlBdDepth = u32UlBdDepth&IPF_DQ_DEPTH_MASK;

		if (u32UlAdwptr >= u32UlAdrptr)/*дָ����ǰ������˳��*/
		{
			u32UlAd0Num = u32UlAdwptr - u32UlAdrptr;
		}
		else
		{
			u32UlAd0Num = IPF_ULAD0_DESC_SIZE - (u32UlAdrptr -u32UlAdwptr);
		}
		if(u32UlAd0Num > u32UlBdDepth)
		{
			u32UlAd0Num -= u32UlBdDepth;
		}
		else
		{
			u32UlAd0Num = 0;
			g_ipf_ctx.status->ad_not_enough[IPF_AD_0]++;
		}


		/* �������AD1���� */
		u32UlBdDepth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_DQ_DEPTH_OFFSET);
		u32UlAdwptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_WPTR_OFFSET);
		u32UlAdrptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
		u32UlBdDepth = u32UlBdDepth&IPF_DQ_DEPTH_MASK;

		if (u32UlAdwptr >= u32UlAdrptr)/*дָ����ǰ������˳��*/
		{
			u32UlAd1Num = u32UlAdwptr - u32UlAdrptr;
		}
		else
		{
			u32UlAd1Num =  IPF_ULAD1_DESC_SIZE - (u32UlAdrptr -u32UlAdwptr);
		}

		if(u32UlAd1Num > u32UlBdDepth)
		{
			u32UlAd1Num -= u32UlBdDepth;
		}
		else
		{
			u32UlAd1Num = 0;
			g_ipf_ctx.status->ad_not_enough[IPF_AD_1]++;
		}

		if(u32UlBdNum > u32UlAd0Num)
		{
			u32UlBdNum = u32UlAd0Num;
		}

		if(u32UlBdNum > u32UlAd1Num)
		{
			u32UlBdNum = u32UlAd1Num;
		}

	}
	return u32UlBdNum;

}


/*****************************************************************************
* �� �� ��      : mdrv_ipf_config_ulbd
*
* ��������  : IPF����BD���ú���
*
* �������  : unsigned int u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara
* �������  : ��
* �� �� ֵ      : IPF_SUCCESS    ���óɹ�
*                           IPF_ERROR      ����ʧ��
*                           BSP_ERR_IPF_NOT_INIT         ģ��δ��ʼ��
*                           BSP_ERR_IPF_INVALID_PARA     ��������
*
* �޸ļ�¼  :2011��11��30��   ³��  ����
				2012��11��30��	�¶����޸���Ӷ����������
									��̬ҵ��ģʽ���õ�֧��
*****************************************************************************/
int mdrv_ipf_config_ulbd(unsigned int u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara)
{
    unsigned int u32BdqWptr = 0;
    IPF_CONFIG_ULPARAM_S* pstUlParam = pstUlPara;
    unsigned int u32BD = 0;
    unsigned int i = 0;
    unsigned int u32TimeStampEn;
    ipf_desc_attr_t bd_attr;


	g_ipf_ctx.status->cfg_bd_times++;

    /* ������� */
    if((NULL == pstUlPara)||(0 == u32Num))
    {
    	g_ipf_ctx.status->invalid_para++;
    	pr_err("%s para invalid\n", __func__);
        return BSP_ERR_IPF_INVALID_PARA;
    }

    /* ���ģ���Ƿ��ʼ�� */
    if(g_ipf_ctx.status && (IPF_ACORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok))
    {
		g_ipf_ctx.status->mdrv_called_not_init++;
		pr_err("%s ipf not init\n", __func__);
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* ���Ccore�Ƿ��ϵ�*/
    if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
    {
       	g_ipf_ctx.status->mdrv_called_not_init++;
        return BSP_ERR_IPF_CCORE_RESETTING;
    }

    /*
    chendongyue c00228781: DTS2013061501582
    ���ÿ��BD�����ݵ���Ч�ԣ���������Ӧ�����ϲ㱣֤��
    ���ǳ���BUG��BD����Ϊ0������������й��
    */
    for(i = 0; i < u32Num; i++)
    {
        if(0 == pstUlParam[i].u16Len)
        {
        	pr_err("%s the %d bdlen is zero drop packet\n", __func__, i);
			g_ipf_ctx.status->bd_len_zero_err++;
            return BSP_ERR_IPF_INVALID_PARA;
        }
    }

    u32TimeStampEn = g_ipf_ctx.status->timestamp_en;
    /* ����BDдָ��,��u32BdqWptr��Ϊ��ʱдָ��ʹ�� */
    u32BdqWptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WPTR_OFFSET);
    u32BD = (u32BdqWptr&IPF_DQ_PTR_MASK);
    for(i = 0; i < u32Num; i++)
    {
        bd_attr.u16 = pstUlPara[i].u16Attribute;
        bd_attr.bits.cd_en = ipf_disable;
        g_stIpfUl.pstIpfBDQ[u32BD].u16Attribute = bd_attr.u16;
        g_stIpfUl.pstIpfBDQ[u32BD].u32InPtr = pstUlParam[i].u32Data;
        g_stIpfUl.pstIpfBDQ[u32BD].u16PktLen = pstUlParam[i].u16Len;
        g_stIpfUl.pstIpfBDQ[u32BD].u16UsrField1 = pstUlParam[i].u16UsrField1;
        g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField2= pstUlParam[i].u32UsrField2;
        g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField3 = pstUlParam[i].u32UsrField3;
        ipf_record_start_time_stamp(u32TimeStampEn, &g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField2);

        u32BD = ((u32BD + 1) < IPF_ULBD_DESC_SIZE)? (u32BD + 1) : 0;
    }

    /* ���Ccore�Ƿ��ϵ�*/
    if(IPF_FORRESET_CONTROL_FORBID <= bsp_ipf_get_control_flag_for_ccore_reset())
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        return BSP_ERR_IPF_CCORE_RESETTING;
    }
	g_ipf_ctx.status->cfg_bd_cnt += u32Num;

    /* ����BDдָ��*/
    ipf_writel(u32BD, g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WPTR_OFFSET);
    return IPF_SUCCESS;
}

int mdrv_ipf_config_dlad(IPF_AD_TYPE_E eAdType, unsigned int u32AdNum, IPF_AD_DESC_S * pstAdDesc)
{
	return ipf_config_dl_ad(eAdType, u32AdNum, pstAdDesc);

}

int mdrv_ipf_register_ops(struct mdrv_ipf_ops *ops)
{
	if(ops)
	{
		if(ipf_register_wakeup_dlcb(ops->rx_complete_cb)!= IPF_SUCCESS)
			return IPF_ERROR;
		if(ipf_register_adq_empty_dlcb(ops->adq_empty_cb)!= IPF_SUCCESS)
			return IPF_ERROR;
	} else {
		pr_err("%s para invalid\n", __func__);
		g_ipf_ctx.status->invalid_para++;
		return IPF_ERROR;
	}
	return IPF_SUCCESS;
}

static inline void ipf_pm_print_packet(void *buf, size_t len)
{
	void *virt = buf;

	if (g_ipf_ctx.status->resume_with_intr){
		if (!virt_addr_valid(buf)){
			virt = phys_to_virt((unsigned long)buf);
			if(!virt_addr_valid(virt)){
				return;
			}
		}

		virt = (void *)(((struct sk_buff*)virt)->data);
		if (!virt_addr_valid(virt)){
			return;
		}
		
		if (len > MAX_PM_OM_SAVE_SIZE) {
			len = MAX_PM_OM_SAVE_SIZE;
		}
		
    	dma_unmap_single(g_ipf_ctx.dev, (dma_addr_t)virt_to_phys(virt), len, DMA_FROM_DEVICE);

		bsp_pm_log(PM_OM_AIPF, len, virt);

		print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 16, 1, virt, len, 0);

		g_ipf_ctx.status->resume_with_intr = 0;
	}
	return;
}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_dlrd
*
* ��������  : �ýӿ����ڶ�ȡ����BD, ֧��һ�ζ�ȡ���BD
*
* �������  : unsigned int* pu32Num
*                           IPF_RD_DESC_S *pstRd
*
* �������  : unsigned int* pu32Num    ʵ�ʶ�ȡ��RD��Ŀ
*
* �� �� ֵ     : IPF_SUCCESS               �����ɹ�
*                           IPF_ERROR                   ����ʧ��
*
* �޸ļ�¼  :2011��11��30��   ³��  ����
*****************************************************************************/
void mdrv_ipf_get_dlrd(unsigned int* pu32Num, IPF_RD_DESC_S *pstRd)
{
    unsigned int u32RdqRptr = 0;
    unsigned int u32RdqDepth = 0;
    unsigned int u32Num = 0;
    unsigned int i = 0;
    unsigned int u32CdqRptr;
    unsigned int u32TimeStampEn;
	unsigned int rd_rate_en;
    ipf_desc_attr_t rd_attr;

    /* ��ȡRD��� */
    u32RdqDepth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;

	g_ipf_ctx.status->get_rd_times++;
    u32Num = (u32RdqDepth < *pu32Num)?u32RdqDepth:*pu32Num;
    if(0 == u32Num)
    {
        *pu32Num = 0;
        return;
    }

    u32TimeStampEn = g_ipf_ctx.status->timestamp_en;
	rd_rate_en = g_ipf_ctx.status->rate_en;

    /* ��ȡRD��ָ�� */
    u32RdqRptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_RDQ_RPTR_OFFSET);
    for(i = 0; i < u32Num; i++)
    {
        rd_attr.u16 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16Attribute;
        /* ��ȡRD */
        pstRd[i].u16Attribute = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16Attribute;
        pstRd[i].u16PktLen = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16PktLen;
        pstRd[i].u16Result = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16Result;
        pstRd[i].u32InPtr = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32InPtr;
		pstRd[i].u32OutPtr = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32OutPtr;
        pstRd[i].u16UsrField1 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16UsrField1;
        pstRd[i].u32UsrField2 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32UsrField2;
        pstRd[i].u32UsrField3 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32UsrField3;
        ipf_record_end_time_stamp(u32TimeStampEn, g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32UsrField2);
        if(ipf_enable == rd_attr.bits.cd_en){
            /* ����CD��ָ�� */
        	u32CdqRptr = ((unsigned long)SHD_DDR_P2V((void *)(unsigned long)MDDR_FAMA(pstRd[i].u32InPtr)) - (unsigned long)g_stIpfDl.pstIpfCDQ)/sizeof(IPF_CD_DESC_S);

            while(g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16Attribute != 1)
            {
                /* ���ͷŵ�CD  ��0 */
                g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16Attribute = 0;
                g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16PktLen = 0;
                g_stIpfDl.pstIpfCDQ[u32CdqRptr].u32Ptr = 0;
                u32CdqRptr = ((u32CdqRptr+1) < IPF_DLCD_DESC_SIZE)?(u32CdqRptr+1):0;
            }
            g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16Attribute = 0;
            g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16PktLen = 0;
            g_stIpfDl.pstIpfCDQ[u32CdqRptr].u32Ptr = 0;
            u32CdqRptr = ((u32CdqRptr+1) < IPF_DLCD_DESC_SIZE)?(u32CdqRptr+1):0;
            *(g_stIpfDl.u32IpfCdRptr) = u32CdqRptr;
        }
		ipf_pm_print_packet((void *)(unsigned long)MDDR_FAMA(pstRd[i].u32OutPtr), pstRd[i].u16PktLen);
        /* ����RD��ָ�� */
        u32RdqRptr = ((u32RdqRptr+1) < IPF_DLRD_DESC_SIZE)?(u32RdqRptr+1):0;
		pstRd[i].u16PktLen > (g_ipf_ctx.status->ad_thred)? g_ipf_ctx.status->get_rd_cnt[IPF_AD_1]++:\
						   		  					   g_ipf_ctx.status->get_rd_cnt[IPF_AD_0]++;

        g_ipf_ctx.status->rd_len_update += pstRd[i].u16PktLen;
    }

	ipf_rd_rate(rd_rate_en, IPF_CHANNEL_DOWN);
    ipf_writel(u32RdqRptr, g_ipf_ctx.regs + HI_IPF_CH1_RDQ_RPTR_OFFSET);
    *pu32Num = u32Num;

}

int mdrv_ipf_get_dlad_num (unsigned int* pu32AD0Num, unsigned int* pu32AD1Num)
{
	g_ipf_ctx.status->get_ad_num_times++;

	return ipf_get_dl_ad_num(pu32AD0Num, pu32AD1Num);
}


/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_dlrd_num
*
* ��������  : �ýӿ����ڶ�ȡ����RD��Ŀ
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : ����RD��Ŀ
*
* �޸ļ�¼  :2012��7��16��   ³��  ����
*****************************************************************************/
unsigned int mdrv_ipf_get_dlrd_num(void)
{
    unsigned int u32RdqDepth = 0;

    /* ��ȡRD��� */
    u32RdqDepth = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
	g_ipf_ctx.status->get_rd_num_times++;
    return u32RdqDepth;
}

void ipf_reset_platform(void)
{
	unsigned int bak_reg=0;
	void * base_addr = NULL;
	unsigned int reset_staus = 0;
	unsigned int reset_peri_crg[5] = {0};

	/*only dallas platform need to reset ipf by peri_crg before going to start.*/
	(void)of_property_read_u32_array(g_ipf_ctx.dev->of_node, "rst_crg", reset_peri_crg, 5);
	dev_info(g_ipf_ctx.dev, "reset_peri_crg %x, %x, %x\n", reset_peri_crg[0],reset_peri_crg[1],reset_peri_crg[2]);

	if(reset_peri_crg[0]){
		g_ipf_ctx.ipf_rst_leave++;
		base_addr=(void *)ioremap_nocache(reset_peri_crg[0], PERI_CRG_4K);
		reset_staus = ipf_readl(base_addr + reset_peri_crg[3]);
		reset_staus &= reset_peri_crg[4];
		if(reset_staus){
			bak_reg = ipf_readl(base_addr + reset_peri_crg[1]);
			bak_reg |= reset_peri_crg[2];

			ipf_writel(bak_reg, base_addr + reset_peri_crg[1]);
		}
	}
}

/*****************************************************************************
* �� �� ��     : ipf_probe
*
* ��������  : ƽ̨�豸׮����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
*****************************************************************************/
static int ipf_probe(struct platform_device *pdev)
{
	struct resource	*regs;
	int ret;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs)
		return -ENXIO;

	g_ipf_ctx.irq = platform_get_irq(pdev, 0);
	if (unlikely(g_ipf_ctx.irq == 0))
		return -ENXIO;

	g_ipf_ctx.regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(g_ipf_ctx.regs))
		return PTR_ERR(g_ipf_ctx.regs);


	g_ipf_ctx.dev = &pdev->dev;
	dma_mask = 0xffffffffULL;
	g_ipf_ctx.dev->dma_mask = &dma_mask;

	g_ipf_ctx.clk = devm_clk_get(g_ipf_ctx.dev, "ipf_clk");
	if (IS_ERR(g_ipf_ctx.clk)) {
		dev_err(g_ipf_ctx.dev, "ipf clock not available\n");
		return -ENXIO;
	} else {
		ret = clk_prepare_enable(g_ipf_ctx.clk);
		if (ret) {
			dev_err(g_ipf_ctx.dev, "failed to enable ipf clock\n");
			return ret;
		}
	}

	g_ipf_ctx.limit_addr = (IPF_LIMIT_ADDR_S *)IPF_TRANS_LIMIT_ADDR;
    g_ipf_ctx.memblock_show = (unsigned int *)IPF_ADDR_LIMIT_MEMBLOCK;
	memset((void*)IPF_TRANS_LIMIT_ADDR, 0x0, IPF_TRANS_LIMIT_SIZE);
    memset((void*)IPF_ADDR_LIMIT_MEMBLOCK, 0x0, IPF_ADDR_MEMBLOCK_SIZE);

	ipf_reset_platform();

	if(ipf_get_limit_addr()){
		g_ipf_ctx.not_get_space++;
		dev_info(g_ipf_ctx.dev, "ipf addr limit func disable\n");
	}

	ipf_init();

	return 0;

}

/*****************************************************************************
* �� �� ��     : ipf_remove
*
* ��������  : ƽ̨�豸׮����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
*****************************************************************************/
static int ipf_remove(struct platform_device *pdev)
{
    return IPF_SUCCESS;
}

static const struct dev_pm_ops ipf_dev_pm_ops ={
	.prepare = ipf_dl_dpm_prepare,
	.suspend = ipf_dl_suspend,
	.resume = ipf_dl_resume,
	.complete = ipf_dl_dpm_complete,
};

static const struct of_device_id ipf_match[] = {
	{ .compatible = "hisilicon,ipf_balong_app" },
	{},
};

static struct platform_driver ipf_pltfm_driver = {
	.probe		= ipf_probe,
	.remove		= ipf_remove,
	.driver		= {
		.name		= "ipf",
		.of_match_table	= ipf_match,
		.pm = &ipf_dev_pm_ops,
	},
};
EXPORT_SYMBOL(g_ipf_ctx);
EXPORT_SYMBOL(mdrv_ipf_config_dlad);
EXPORT_SYMBOL(mdrv_ipf_get_used_dlad);
EXPORT_SYMBOL(bsp_ipf_config_timeout);
EXPORT_SYMBOL(bsp_ipf_dump_bdinfo);
EXPORT_SYMBOL(bsp_ipf_set_control_flag_for_ccore_reset);
EXPORT_SYMBOL(bsp_ipf_help);
EXPORT_SYMBOL(bsp_ipf_set_pktlen);
EXPORT_SYMBOL(mdrv_ipf_reinit_dlreg);
EXPORT_SYMBOL(mdrv_ipf_get_uldesc_num);
EXPORT_SYMBOL(mdrv_ipf_config_ulbd);
EXPORT_SYMBOL(bsp_ipf_dump_adinfo);
EXPORT_SYMBOL(mdrv_ipf_get_dlad_num);
EXPORT_SYMBOL(mdrv_ipf_get_ulbd_num);
EXPORT_SYMBOL(bsp_ipf_mem);
EXPORT_SYMBOL(bsp_ipf_srest);
EXPORT_SYMBOL(bsp_ipf_info);
EXPORT_SYMBOL(ipf_init);
EXPORT_SYMBOL(mdrv_ipf_get_dlrd);
EXPORT_SYMBOL(bsp_ipf_dump_rdinfo);
EXPORT_SYMBOL(mdrv_ipf_register_ops);
EXPORT_SYMBOL(bsp_ipf_ad0_info);
EXPORT_SYMBOL(bsp_ipf_ad1_info);
EXPORT_SYMBOL(ipf_register_wakeup_dlcb);


module_platform_driver(ipf_pltfm_driver);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ipf");


/*lint -restore*/

