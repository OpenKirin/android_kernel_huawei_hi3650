#include "ufshcd.h"
#include "unipro.h"
#include "ufs-kirin.h"
#include "ufshci.h"
#include "ufs_kirin_spec_log.h"
#include "ufs_kirin_norm_stat.h"


static t_reg_info  ufs_hci_vendor_regs_tab [] = {
 { "BUSTHRTL", 0xC0 },
 { "OOCPR",    0xC4 },
 { "FEIE",     0xC8 },
 { "CDACFG",   0xD0 },
 { "CDATX1",   0xD4 },
 { "CDATX2",   0xD8 },
 { "CDARX1",   0xDC },
 { "CDARX2",   0xE0 },
 { "CDASTA",   0xE4 },
 { "LBMCFG",   0xF0 },
 { "LBMSTA",   0xF4 },
 { "DBG",      0xF8 },
 { "HCLKDIV",  0xFC },
};

static t_reg_info  ufs_soc_ufssysctl_regs_tab [] = {
 { "HC_DEBUG",          0x002C },
 { "PHY_MPX_TEST_CTRL", 0x0030 },
 { "PHY_MPX_TEST_OBSV", 0x0034 },
 { "PHY_DTB_OUT",       0x0038 },
 { "DEBUG_MONITOR_HH",  0x003C },
 { "DEBUG_MONITOR_H",   0x0040 },
 { "DEBUG_MONITOR_L",   0x0044 },
 { "DEBUG_MONITORUP_H", 0x0048 },
 { "DEBUG_MONITORUP_L", 0x004C },
 { "RESET_CTRL_EN",     0x001C },
 { "PHY_CLK_CTRL",      0x0010 },
 { "CLOCK_GATE_BYPASS", 0x0018 },
 { "UFS_SYSCTRL",       0x005C },
 { "HC_LP_CTRL",        0x000C },
 { "PHY_ISO_EN",        0x0008 },
 { "PSW_POWER_CTRL",    0x0004 },
 { "PSW_CLK_CTRL",      0x0014 },
 { "UFS_DEVICE_RESET_CTRL", 0x0060 },
};

static t_reg_info  ufs_soc_pericrg_regs_tab [] = {
 { "PERRSTSTAT3",       0x008C },
 { "PERSTAT7",          0x042C },
 { "CLKDIV17",          0x00EC },
 { "CLKDIV19",          0x00F4 },
 };

static t_reg_info ufs_soc_pctrl_regs_tab[] = {
  { "PERI_CTRL3",       0x0010 },
 };

void ufs_kirin_log_hci_vendor_regs( struct ufs_hba *hba, int errType )
{
	UFS_EXC_INFO_LOG( hba, errType, "HCI vendor Regs log Start" );

	ufs_log_memreg_list( hba, hba->mmio_base, ufs_hci_vendor_regs_tab, (u32)ARRAY_SIZE(ufs_hci_vendor_regs_tab) );

	UFS_EXC_INFO_LOG( hba, errType, "HCI vendor Regs log end" );
}

void ufs_kirin_log_phy_mpx_tst(struct ufs_hba *hba)
{
	struct ufs_kirin_host *host;
	int t;
	u32 tst_out;
	u32 tst_in;

	host = (struct ufs_kirin_host *)hba->priv;

	tst_out = 0x01010101;
	for(t = 0; t < 8; t ++) {
		/* write PHY_MPX_TEST_CTRL register */
		ufs_sys_ctrl_writel(host, tst_out, 0x30);
		/*lint !e778 !e774 !e516 */
		udelay(1UL);
		/* read 'PHY_MPX_TEST_OBSV register */
		tst_in = (u32)ufs_sys_ctrl_readl(host, 0x34);

		UFS_INFO_LOG(hba, "PHY_MPX_TEST ctrl[%08x],obsv[%08x]", tst_out, tst_in);

		tst_out = tst_out << 1;
	}
}


static void ufs_kirin_log_soc_ufssysctl_regs( struct ufs_hba *hba, int errType )
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;

	UFS_EXC_INFO_LOG( hba, errType, "soc ufs_sysctl Regs log Start" );

	ufs_log_memreg_list( hba, host->ufs_sys_ctrl, ufs_soc_ufssysctl_regs_tab, (u32)ARRAY_SIZE(ufs_soc_ufssysctl_regs_tab) );

	ufs_kirin_log_phy_mpx_tst(hba);

	UFS_EXC_INFO_LOG( hba, errType, "soc ufs_sysctl Regs log end" );
}

static void ufs_kirin_log_soc_peri_crg_regs( struct ufs_hba *hba, int errType )
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;

	UFS_EXC_INFO_LOG( hba, errType, "soc peri_crg Regs log Start" );

	ufs_log_memreg_list( hba, host->pericrg, ufs_soc_pericrg_regs_tab, (u32)ARRAY_SIZE(ufs_soc_pericrg_regs_tab) );

	UFS_EXC_INFO_LOG( hba, errType, "soc peri_crg Regs log end" );
}

static void ufs_kirin_log_soc_pctrl_regs( struct ufs_hba *hba, int errType )
{
	struct ufs_kirin_host *host = (struct ufs_kirin_host *)hba->priv;

	UFS_EXC_INFO_LOG( hba, errType, "soc pctrl Regs log Start" );

	ufs_log_memreg_list( hba, host->pctrl, ufs_soc_pctrl_regs_tab, (u32)ARRAY_SIZE(ufs_soc_pctrl_regs_tab) );

	UFS_EXC_INFO_LOG( hba, errType, "soc pctrl Regs log end" );
}

void ufs_kirin_log_soc_all_regs( struct ufs_hba *hba, int errType )
{
	ufs_kirin_log_soc_ufssysctl_regs( hba, errType );

	ufs_kirin_log_soc_peri_crg_regs( hba, errType );

	ufs_kirin_log_soc_pctrl_regs( hba, errType );
}
