#ifndef __SOC_HIPACKPHY_INTERFACE_H__
#define __SOC_HIPACKPHY_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_HIPACKPHY_REVISION_ADDR(base) ((base) + (0x000))
#define SOC_HIPACKPHY_PHYINITCTRL_ADDR(base) ((base) + (0x004))
#define SOC_HIPACKPHY_PHYINITSTATUS_ADDR(base) ((base) + (0x008))
#define SOC_HIPACKPHY_PHYCLKGATED_ADDR(base) ((base) + (0x000C))
#define SOC_HIPACKPHY_PHYTIMER0_ADDR(base) ((base) + (0x010))
#define SOC_HIPACKPHY_PHYTIMER1_ADDR(base) ((base) + (0x014))
#define SOC_HIPACKPHY_PLLCTRL_ADDR(base) ((base) + (0x018))
#define SOC_HIPACKPHY_PLLTIMER_ADDR(base) ((base) + (0x01C))
#define SOC_HIPACKPHY_DLYMEASCTRL_ADDR(base) ((base) + (0x020))
#define SOC_HIPACKPHY_IMPCTRL_ADDR(base) ((base) + (0x024))
#define SOC_HIPACKPHY_IMPSTATUS_ADDR(base) ((base) + (0x028))
#define SOC_HIPACKPHY_DRAMCFG_ADDR(base) ((base) + (0x02C))
#define SOC_HIPACKPHY_DRAMTIMER0_ADDR(base) ((base) + (0x030))
#define SOC_HIPACKPHY_DRAMTIMER1_ADDR(base) ((base) + (0x034))
#define SOC_HIPACKPHY_DRAMTIMER2_ADDR(base) ((base) + (0x038))
#define SOC_HIPACKPHY_DRAMTIMER3_ADDR(base) ((base) + (0x03C))
#define SOC_HIPACKPHY_DRAMTIMER4_ADDR(base) ((base) + (0x040))
#define SOC_HIPACKPHY_ODTCR_ADDR(base) ((base) + (0x044))
#define SOC_HIPACKPHY_TRAINCTRL0_ADDR(base) ((base) + (0x048))
#define SOC_HIPACKPHY_RANKEN_ADDR(base) ((base) + (0x04C))
#define SOC_HIPACKPHY_TRAINMADDR_ADDR(base) ((base) + (0x0050))
#define SOC_HIPACKPHY_BISTCTRL_ADDR(base) ((base) + (0x0054))
#define SOC_HIPACKPHY_BISTDATA0_ADDR(base) ((base) + (0x0058))
#define SOC_HIPACKPHY_BISTDATA1_ADDR(base) ((base) + (0x005C))
#define SOC_HIPACKPHY_BISTSTATUS_ADDR(base) ((base) + (0x0060))
#define SOC_HIPACKPHY_MODEREG01_ADDR(base) ((base) + (0x0064))
#define SOC_HIPACKPHY_MODEREG23_ADDR(base) ((base) + (0x0068))
#define SOC_HIPACKPHY_DETPATTERN_ADDR(base) ((base) + (0x006C))
#define SOC_HIPACKPHY_MISC_ADDR(base) ((base) + (0x0070))
#define SOC_HIPACKPHY_RNK2RNK_ADDR(base) ((base) + (0x0074))
#define SOC_HIPACKPHY_PHYCTRL0_ADDR(base) ((base) + (0x0078))
#define SOC_HIPACKPHY_PHYDBG_ADDR(base) ((base) + (0x007C))
#define SOC_HIPACKPHY_RETCTRL0_ADDR(base) ((base) + (0x0080))
#define SOC_HIPACKPHY_DMSEL_ADDR(base) ((base) + (0x0084))
#define SOC_HIPACKPHY_IOCTL_ADDR(base) ((base) + (0x0088))
#define SOC_HIPACKPHY_DQSSEL_ADDR(base) ((base) + (0x008C))
#define SOC_HIPACKPHY_PHYCTRL1_ADDR(base) ((base) + (0x0090))
#define SOC_HIPACKPHY_DXNCKCTRL_ADDR(base) ((base) + (0x0094))
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ADDR(base) ((base) + (0x0098))
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_ADDR(base) ((base) + (0x009C))
#define SOC_HIPACKPHY_SWTMODE_ADDR(base) ((base) + (0x00A0))
#define SOC_HIPACKPHY_SWTWLDQS_ADDR(base) ((base) + (0x00A4))
#define SOC_HIPACKPHY_SWTRLT_ADDR(base) ((base) + (0x00A8))
#define SOC_HIPACKPHY_PHYCTRL2_ADDR(base) ((base) + (0x00AC))
#define SOC_HIPACKPHY_IOCTL1_ADDR(base) ((base) + (0x00B0))
#define SOC_HIPACKPHY_IOCTL2_ADDR(base) ((base) + (0x00B4))
#define SOC_HIPACKPHY_TRAINMADDRTG1_ADDR(base) ((base) + (0x00B8))
#define SOC_HIPACKPHY_DRAMTIMER5_ADDR(base) ((base) + (0x0BC))
#define SOC_HIPACKPHY_VREFTCTRL_ADDR(base) ((base) + (0x00C0))
#define SOC_HIPACKPHY_DVRFTCTRL_ADDR(base) ((base) + (0x00C4))
#define SOC_HIPACKPHY_HVRFTCTRL_ADDR(base) ((base) + (0x00C8))
#define SOC_HIPACKPHY_TRAINCTRL1_ADDR(base) ((base) + (0x00D0))
#define SOC_HIPACKPHY_TRAINCTRL2_ADDR(base) ((base) + (0x00D4))
#define SOC_HIPACKPHY_REGBANKCTRL_ADDR(base) ((base) + (0x00D8))
#define SOC_HIPACKPHY_TRAINCTRL3_ADDR(base) ((base) + (0x00DC))
#define SOC_HIPACKPHY_MODEREG45_ADDR(base) ((base) + (0x00E0))
#define SOC_HIPACKPHY_MODEREG67_ADDR(base) ((base) + (0x00E4))
#define SOC_HIPACKPHY_TRAINCTRL6_ADDR(base) ((base) + (0x0E8))
#define SOC_HIPACKPHY_DETPATINDEX_ADDR(base) ((base) + (0x00EC))
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_ADDR(base) ((base) + (0x00F0))
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_ADDR(base) ((base) + (0x00F4))
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_ADDR(base) ((base) + (0x00F8))
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_ADDR(base) ((base) + (0x00FC))
#define SOC_HIPACKPHY_ACBISTCTRL0_ADDR(base) ((base) + (0x100))
#define SOC_HIPACKPHY_ACBISTCTRL1_ADDR(base) ((base) + (0x104))
#define SOC_HIPACKPHY_ACBISTSTS0_ADDR(base) ((base) + (0x108))
#define SOC_HIPACKPHY_ACBISTSTS1_ADDR(base) ((base) + (0x10C))
#define SOC_HIPACKPHY_WDXBOUND_DFS_ADDR(base) ((base) + (0x110))
#define SOC_HIPACKPHY_TRAINCTRL4_ADDR(base) ((base) + (0x114))
#define SOC_HIPACKPHY_TRAINCTRL5_ADDR(base) ((base) + (0x118))
#define SOC_HIPACKPHY_TRAINCTRL7_ADDR(base) ((base) + (0x11C))
#define SOC_HIPACKPHY_ACCMDBDL0_ADDR(base) ((base) + (0x120))
#define SOC_HIPACKPHY_ACCMDBDL1_ADDR(base) ((base) + (0x124))
#define SOC_HIPACKPHY_ACCMDBDL2_ADDR(base) ((base) + (0x128))
#define SOC_HIPACKPHY_ACCMDBDL3_ADDR(base) ((base) + (0x12C))
#define SOC_HIPACKPHY_ACCMDBDL4_ADDR(base) ((base) + (0x130))
#define SOC_HIPACKPHY_ACCMDBDL5_ADDR(base) ((base) + (0x134))
#define SOC_HIPACKPHY_ACCMDBDL6_ADDR(base) ((base) + (0x138))
#define SOC_HIPACKPHY_ACCMDBDL7_ADDR(base) ((base) + (0x13C))
#define SOC_HIPACKPHY_ACADDRBDL0_ADDR(base) ((base) + (0x140))
#define SOC_HIPACKPHY_ACADDRBDL1_ADDR(base) ((base) + (0x144))
#define SOC_HIPACKPHY_ACADDRBDL2_ADDR(base) ((base) + (0x148))
#define SOC_HIPACKPHY_ACADDRBDL3_ADDR(base) ((base) + (0x14C))
#define SOC_HIPACKPHY_ACADDRBDL4_ADDR(base) ((base) + (0x150))
#define SOC_HIPACKPHY_ACADDRBDL5_ADDR(base) ((base) + (0x154))
#define SOC_HIPACKPHY_ACADDRBDL6_ADDR(base) ((base) + (0x158))
#define SOC_HIPACKPHY_ACADDRBDL7_ADDR(base) ((base) + (0x15C))
#define SOC_HIPACKPHY_ACADDRBDL8_ADDR(base) ((base) + (0x160))
#define SOC_HIPACKPHY_ACADDRBDL9_ADDR(base) ((base) + (0x164))
#define SOC_HIPACKPHY_ACCLKBDL_ADDR(base) ((base) + (0x168))
#define SOC_HIPACKPHY_ACPHYCTL0_ADDR(base) ((base) + (0x170))
#define SOC_HIPACKPHY_ACPHYCTL1_ADDR(base) ((base) + (0x174))
#define SOC_HIPACKPHY_ACPHYCTL2_ADDR(base) ((base) + (0x178))
#define SOC_HIPACKPHY_ACPHYCTL3_ADDR(base) ((base) + (0x17C))
#define SOC_HIPACKPHY_ACPHYCTL4_ADDR(base) ((base) + (0x180))
#define SOC_HIPACKPHY_ACPHYCTL5_ADDR(base) ((base) + (0x184))
#define SOC_HIPACKPHY_ACPHYCTL6_ADDR(base) ((base) + (0x188))
#define SOC_HIPACKPHY_ACPHYCTL7_ADDR(base) ((base) + (0x018C))
#define SOC_HIPACKPHY_ACDEBUG_ADDR(base) ((base) + (0x0190))
#define SOC_HIPACKPHY_ACPHYRSVDC_ADDR(base) ((base) + (0x0194))
#define SOC_HIPACKPHY_ACPHYRSVDS_ADDR(base) ((base) + (0x0198))
#define SOC_HIPACKPHY_ACPHYCTL8_ADDR(base) ((base) + (0x019C))
#define SOC_HIPACKPHY_ACCMDBDL8_ADDR(base) ((base) + (0x1A0))
#define SOC_HIPACKPHY_ACCMDBDL9_ADDR(base) ((base) + (0x1A4))
#define SOC_HIPACKPHY_ACCMDBDL10_ADDR(base) ((base) + (0x1A8))
#define SOC_HIPACKPHY_ACCMDBDL11_ADDR(base) ((base) + (0x1AC))
#define SOC_HIPACKPHY_ACPHYDCC_ADDR(base) ((base) + (0x01B0))
#define SOC_HIPACKPHY_ACPHYCTL9_ADDR(base) ((base) + (0x01B4))
#define SOC_HIPACKPHY_CATSWAPINDEX_ADDR(base) ((base) + (0x01B8))
#define SOC_HIPACKPHY_CATSWAPSEL_ADDR(base) ((base) + (0x01BC))
#define SOC_HIPACKPHY_CATTIMER0_ADDR(base) ((base) + (0x01C0))
#define SOC_HIPACKPHY_CATTIMER1_ADDR(base) ((base) + (0x01C4))
#define SOC_HIPACKPHY_CATCONFIG_ADDR(base) ((base) + (0x01C8))
#define SOC_HIPACKPHY_CATRESULT_ADDR(base) ((base) + (0x01CC))
#define SOC_HIPACKPHY_PHYDQRESULT_ADDR(base) ((base) + (0x01D0))
#define SOC_HIPACKPHY_ADDRPHBOUND_ADDR(base) ((base) + (0x01D4))
#define SOC_HIPACKPHY_SWCATPATTERN_P_ADDR(base) ((base) + (0x01D8))
#define SOC_HIPACKPHY_SWCATPATTERN_N_ADDR(base) ((base) + (0x01DC))
#define SOC_HIPACKPHY_MRS_SEQ_PROG_ADDR(base) ((base) + (0x01E0))
#define SOC_HIPACKPHY_LPCTRL_ADDR(base) ((base) + (0x01E4))
#define SOC_HIPACKPHY_ACPHYCTL10_ADDR(base) ((base) + (0x1E8))
#define SOC_HIPACKPHY_ACPHYCTL11_ADDR(base) ((base) + (0x1EC))
#define SOC_HIPACKPHY_AHVREFT_STATUS_ADDR(base) ((base) + (0x1F0))
#define SOC_HIPACKPHY_ADVREF_STATUS_ADDR(base) ((base) + (0x1F4))
#define SOC_HIPACKPHY_DFIMISCCTRL_ADDR(base) ((base) + (0x1FC))
#define SOC_HIPACKPHY_DXNBISTCTRL_ADDR(base,n) ((base) + (0x200+(n)*0x80))
#define SOC_HIPACKPHY_DXNBISTSTS_ADDR(base,n) ((base) + (0x204+(n)*0x80))
#define SOC_HIPACKPHY_DXNCTRL_ADDR(base,n) ((base) + (0x208+(n)*0x80))
#define SOC_HIPACKPHY_DXNWDQNBDL0_ADDR(base,m,n) ((base) + (0x210+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNWDQNBDL1_ADDR(base,m,n) ((base) + (0x214+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNWDQNBDL2_ADDR(base,m,n) ((base) + (0x218+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDQNBDL0_ADDR(base,m,n,l) ((base) + (0x21C+(l)*0x800+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDQNBDL1_ADDR(base,m,n,l) ((base) + (0x220+(l)*0x800+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDQNBDL2_ADDR(base,m,n,l) ((base) + (0x224+(l)*0x800+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNOEBDL_ADDR(base,n) ((base) + (0x228+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDQSDLY_ADDR(base,n) ((base) + (0x22C+(n)*0x80))
#define SOC_HIPACKPHY_DXNWDQSDLY_ADDR(base,n) ((base) + (0x230+(n)*0x80))
#define SOC_HIPACKPHY_DXNWDQDLY_ADDR(base,m,n) ((base) + (0x234+(m)*0x400+(n)*0x80))
#define SOC_HIPACKPHY_DXNWLSL_ADDR(base,n) ((base) + (0x238+(n)*0x80))
#define SOC_HIPACKPHY_DXNGDS_ADDR(base,n) ((base) + (0x23C+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDQSGDLY_ADDR(base,m,n) ((base) + (0x240+(n)*0x80+(m)*0x400))
#define SOC_HIPACKPHY_DXNWDQNLB0_ADDR(base,n) ((base) + (0x244+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_ADDR(base,n) ((base) + (0x248+(n)*0x80))
#define SOC_HIPACKPHY_DXNCLKBDL_ADDR(base,n) ((base) + (0x24C+(n)*0x80))
#define SOC_HIPACKPHY_DXNRDBOUND_ADDR(base,n) ((base) + (0x250+(n)*0x80))
#define SOC_HIPACKPHY_DXNWRBOUND_ADDR(base,n) ((base) + (0x254+(n)*0x80))
#define SOC_HIPACKPHY_DXPHYCTRL_ADDR(base,n) ((base) + (0x258+(n)*0x80))
#define SOC_HIPACKPHY_DXNWDQNLB1_ADDR(base,n) ((base) + (0x25C+(n)*0x80))
#define SOC_HIPACKPHY_DXNMISCCTRL0_ADDR(base,n) ((base) + (0x260+(n)*0x80))
#define SOC_HIPACKPHY_DXNMISCCTRL1_ADDR(base,n) ((base) + (0x264+(n)*0x80))
#define SOC_HIPACKPHY_DXDEBUG0_ADDR(base,n) ((base) + (0x268+(n)*0x80))
#define SOC_HIPACKPHY_DXDEBUG1_ADDR(base,n) ((base) + (0x26C+(n)*0x80))
#define SOC_HIPACKPHY_DVREFT_STATUS_ADDR(base,n) ((base) + (0x270+(n)*0x80))
#define SOC_HIPACKPHY_HVREFT_STATUS_ADDR(base,n) ((base) + (0x274+(n)*0x80))
#define SOC_HIPACKPHY_DXDEBUGCONFIG_ADDR(base,n) ((base) + (0x278+(n)*0x80))
#define SOC_HIPACKPHY_DXNDCC_ADDR(base,n) ((base) + (0x27C+(n)*0x80))
#define SOC_HIPACKPHY_DXNMISCCTRL3_ADDR(base,n) ((base) + (0x20C+(n)*0x80))
#define SOC_HIPACKPHY_IOCTL3_ADDR(base) ((base) + (0xFF0))
#define SOC_HIPACKPHY_IOCTL4_ADDR(base) ((base) + (0xFF4))
#define SOC_HIPACKPHY_IOCTL5_ADDR(base) ((base) + (0xFF8))
#define SOC_HIPACKPHY_AC_PLLCTRL_ADDR(base) ((base) + (0x010))
#define SOC_HIPACKPHY_AC_PHYCTRL0_ADDR(base) ((base) + (0x014))
#define SOC_HIPACKPHY_AC_IOCTL_ADDR(base) ((base) + (0x018))
#define SOC_HIPACKPHY_AC_PHYCTRL1_ADDR(base) ((base) + (0x01C))
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_ADDR(base) ((base) + (0x020))
#define SOC_HIPACKPHY_AC_IOCTL1_ADDR(base) ((base) + (0x024))
#define SOC_HIPACKPHY_AC_IOCTL2_ADDR(base) ((base) + (0x028))
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_ADDR(base) ((base) + (0x02C))
#define SOC_HIPACKPHY_AC_ACCMDBDL0_ADDR(base) ((base) + (0x038))
#define SOC_HIPACKPHY_AC_ACCMDBDL2_ADDR(base) ((base) + (0x040))
#define SOC_HIPACKPHY_AC_ACCMDBDL4_ADDR(base) ((base) + (0x048))
#define SOC_HIPACKPHY_AC_ACCLKBDL_ADDR(base) ((base) + (0x050))
#define SOC_HIPACKPHY_AC_ACPHYCTL0_ADDR(base) ((base) + (0x054))
#define SOC_HIPACKPHY_AC_ACPHYCTL1_ADDR(base) ((base) + (0x058))
#define SOC_HIPACKPHY_AC_ACPHYCTL2_ADDR(base) ((base) + (0x05C))
#define SOC_HIPACKPHY_AC_ACPHYCTL3_ADDR(base) ((base) + (0x060))
#define SOC_HIPACKPHY_AC_ACPHYCTL4_ADDR(base) ((base) + (0x064))
#define SOC_HIPACKPHY_AC_ACPHYCTL5_ADDR(base) ((base) + (0x068))
#define SOC_HIPACKPHY_AC_ACPHYCTL6_ADDR(base) ((base) + (0x06C))
#define SOC_HIPACKPHY_AC_ACPHYCTL7_ADDR(base) ((base) + (0x070))
#define SOC_HIPACKPHY_AC_ACDEBUG_ADDR(base) ((base) + (0x074))
#define SOC_HIPACKPHY_AC_ACPHYRSVDC_ADDR(base) ((base) + (0x078))
#define SOC_HIPACKPHY_AC_ACPHYRSVDS_ADDR(base) ((base) + (0x07C))
#define SOC_HIPACKPHY_AC_ACPHYDCC_ADDR(base) ((base) + (0x094))
#define SOC_HIPACKPHY_AC_ACPHYCTL9_ADDR(base) ((base) + (0x098))
#define SOC_HIPACKPHY_AC_ACPHYCTL10_ADDR(base) ((base) + (0x09C))
#define SOC_HIPACKPHY_AC_ACPHYCTL11_ADDR(base) ((base) + (0x0A0))
#define SOC_HIPACKPHY_AC_IOCTL3_ADDR(base) ((base) + (0x0A4))
#define SOC_HIPACKPHY_AC_IOCTL4_ADDR(base) ((base) + (0x0A8))
#define SOC_HIPACKPHY_AC_ACPHYDCC1_ADDR(base) ((base) + (0x0AC))
#define SOC_HIPACKPHY_AC_ACPHYDCC2_ADDR(base) ((base) + (0x0B0))
#define SOC_HIPACKPHY_AC_IOCTL5_ADDR(base) ((base) + (0x0B4))
#define SOC_HIPACKPHY_AC_IOCTL6_ADDR(base) ((base) + (0x0B8))
#define SOC_HIPACKPHY_DX_PHYCTRL0_ADDR(base) ((base) + (0x200))
#define SOC_HIPACKPHY_DX_IOCTL_ADDR(base) ((base) + (0x204))
#define SOC_HIPACKPHY_DX_DQSSEL_ADDR(base) ((base) + (0x208))
#define SOC_HIPACKPHY_DX_DXNCKCTRL_ADDR(base) ((base) + (0x20C))
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_ADDR(base) ((base) + (0x210))
#define SOC_HIPACKPHY_DX_PHYCTRL2_ADDR(base) ((base) + (0x214))
#define SOC_HIPACKPHY_DX_IOCTL1_ADDR(base) ((base) + (0x218))
#define SOC_HIPACKPHY_DX_IOCTL2_ADDR(base) ((base) + (0x21C))
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_ADDR(base) ((base) + (0x220))
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_ADDR(base) ((base) + (0x224))
#define SOC_HIPACKPHY_DX_DXNCLKBDL_ADDR(base) ((base) + (0x230))
#define SOC_HIPACKPHY_DX_DXPHYCTRL_ADDR(base) ((base) + (0x234))
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_ADDR(base,p) ((base) + (0x238+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_ADDR(base,p) ((base) + (0x264+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXDEBUG0_ADDR(base,p) ((base) + (0x23C+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXPHYRSVD_ADDR(base,p) ((base) + (0x244+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_ADDR(base,p) ((base) + (0x248+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_ADDR(base,p) ((base) + (0x24C+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNDCC_ADDR(base,p) ((base) + (0x250+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_ADDR(base,p) ((base) + (0x254+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_ADDR(base,p) ((base) + (0x258+(p)*0x80))
#define SOC_HIPACKPHY_DX_IOCTL3_ADDR(base,p) ((base) + (0x25C+(p)*0x80))
#define SOC_HIPACKPHY_DX_IOCTL5_ADDR(base) ((base) + (0x260))
#define SOC_HIPACKPHY_DX_DXNDCC1_ADDR(base,p) ((base) + (0x268+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNDCC2_ADDR(base,p) ((base) + (0x26c+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNDCC3_ADDR(base,p) ((base) + (0x270+(p)*0x80))
#define SOC_HIPACKPHY_DX_DXNDCC4_ADDR(base,p) ((base) + (0x274+(p)*0x80))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int minor : 8;
        unsigned int major : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_HIPACKPHY_REVISION_UNION;
#endif
#define SOC_HIPACKPHY_REVISION_minor_START (0)
#define SOC_HIPACKPHY_REVISION_minor_END (7)
#define SOC_HIPACKPHY_REVISION_major_START (8)
#define SOC_HIPACKPHY_REVISION_major_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int init_en : 1;
        unsigned int pll_init_en : 1;
        unsigned int dlymeas_en : 1;
        unsigned int zcal_en : 1;
        unsigned int wl_en : 1;
        unsigned int gt_en : 1;
        unsigned int gdst_en : 1;
        unsigned int wl2_en : 1;
        unsigned int rdet_en : 1;
        unsigned int wdet_en : 1;
        unsigned int dram_init_en : 1;
        unsigned int cat_en : 1;
        unsigned int dram_rst : 1;
        unsigned int phy_rst : 1;
        unsigned int pack_rst : 1;
        unsigned int phyconn_rst : 1;
        unsigned int dvreft_en : 1;
        unsigned int hvreft_en : 1;
        unsigned int dxdvrefs_en : 1;
        unsigned int acdvreft_en : 1;
        unsigned int achvreft_en : 1;
        unsigned int acdvrefs_en : 1;
        unsigned int reserved : 9;
        unsigned int ctl_cke_bypass : 1;
    } reg;
} SOC_HIPACKPHY_PHYINITCTRL_UNION;
#endif
#define SOC_HIPACKPHY_PHYINITCTRL_init_en_START (0)
#define SOC_HIPACKPHY_PHYINITCTRL_init_en_END (0)
#define SOC_HIPACKPHY_PHYINITCTRL_pll_init_en_START (1)
#define SOC_HIPACKPHY_PHYINITCTRL_pll_init_en_END (1)
#define SOC_HIPACKPHY_PHYINITCTRL_dlymeas_en_START (2)
#define SOC_HIPACKPHY_PHYINITCTRL_dlymeas_en_END (2)
#define SOC_HIPACKPHY_PHYINITCTRL_zcal_en_START (3)
#define SOC_HIPACKPHY_PHYINITCTRL_zcal_en_END (3)
#define SOC_HIPACKPHY_PHYINITCTRL_wl_en_START (4)
#define SOC_HIPACKPHY_PHYINITCTRL_wl_en_END (4)
#define SOC_HIPACKPHY_PHYINITCTRL_gt_en_START (5)
#define SOC_HIPACKPHY_PHYINITCTRL_gt_en_END (5)
#define SOC_HIPACKPHY_PHYINITCTRL_gdst_en_START (6)
#define SOC_HIPACKPHY_PHYINITCTRL_gdst_en_END (6)
#define SOC_HIPACKPHY_PHYINITCTRL_wl2_en_START (7)
#define SOC_HIPACKPHY_PHYINITCTRL_wl2_en_END (7)
#define SOC_HIPACKPHY_PHYINITCTRL_rdet_en_START (8)
#define SOC_HIPACKPHY_PHYINITCTRL_rdet_en_END (8)
#define SOC_HIPACKPHY_PHYINITCTRL_wdet_en_START (9)
#define SOC_HIPACKPHY_PHYINITCTRL_wdet_en_END (9)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_init_en_START (10)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_init_en_END (10)
#define SOC_HIPACKPHY_PHYINITCTRL_cat_en_START (11)
#define SOC_HIPACKPHY_PHYINITCTRL_cat_en_END (11)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_rst_START (12)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_rst_END (12)
#define SOC_HIPACKPHY_PHYINITCTRL_phy_rst_START (13)
#define SOC_HIPACKPHY_PHYINITCTRL_phy_rst_END (13)
#define SOC_HIPACKPHY_PHYINITCTRL_pack_rst_START (14)
#define SOC_HIPACKPHY_PHYINITCTRL_pack_rst_END (14)
#define SOC_HIPACKPHY_PHYINITCTRL_phyconn_rst_START (15)
#define SOC_HIPACKPHY_PHYINITCTRL_phyconn_rst_END (15)
#define SOC_HIPACKPHY_PHYINITCTRL_dvreft_en_START (16)
#define SOC_HIPACKPHY_PHYINITCTRL_dvreft_en_END (16)
#define SOC_HIPACKPHY_PHYINITCTRL_hvreft_en_START (17)
#define SOC_HIPACKPHY_PHYINITCTRL_hvreft_en_END (17)
#define SOC_HIPACKPHY_PHYINITCTRL_dxdvrefs_en_START (18)
#define SOC_HIPACKPHY_PHYINITCTRL_dxdvrefs_en_END (18)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvreft_en_START (19)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvreft_en_END (19)
#define SOC_HIPACKPHY_PHYINITCTRL_achvreft_en_START (20)
#define SOC_HIPACKPHY_PHYINITCTRL_achvreft_en_END (20)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvrefs_en_START (21)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvrefs_en_END (21)
#define SOC_HIPACKPHY_PHYINITCTRL_ctl_cke_bypass_START (31)
#define SOC_HIPACKPHY_PHYINITCTRL_ctl_cke_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int pll_lock_err : 1;
        unsigned int dlymeas_err : 1;
        unsigned int zcal_err : 1;
        unsigned int wl_err : 1;
        unsigned int gt_err : 1;
        unsigned int gdst_err : 1;
        unsigned int wl2_err : 1;
        unsigned int rdet_err : 1;
        unsigned int wdet_err : 1;
        unsigned int cat_err : 1;
        unsigned int fst_rdet_wrg : 1;
        unsigned int fst_rdet_err : 1;
        unsigned int wdert_wrg : 1;
        unsigned int wdert_err : 1;
        unsigned int reserved_1 : 16;
        unsigned int retrain_active : 1;
    } reg;
} SOC_HIPACKPHY_PHYINITSTATUS_UNION;
#endif
#define SOC_HIPACKPHY_PHYINITSTATUS_pll_lock_err_START (1)
#define SOC_HIPACKPHY_PHYINITSTATUS_pll_lock_err_END (1)
#define SOC_HIPACKPHY_PHYINITSTATUS_dlymeas_err_START (2)
#define SOC_HIPACKPHY_PHYINITSTATUS_dlymeas_err_END (2)
#define SOC_HIPACKPHY_PHYINITSTATUS_zcal_err_START (3)
#define SOC_HIPACKPHY_PHYINITSTATUS_zcal_err_END (3)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl_err_START (4)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl_err_END (4)
#define SOC_HIPACKPHY_PHYINITSTATUS_gt_err_START (5)
#define SOC_HIPACKPHY_PHYINITSTATUS_gt_err_END (5)
#define SOC_HIPACKPHY_PHYINITSTATUS_gdst_err_START (6)
#define SOC_HIPACKPHY_PHYINITSTATUS_gdst_err_END (6)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl2_err_START (7)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl2_err_END (7)
#define SOC_HIPACKPHY_PHYINITSTATUS_rdet_err_START (8)
#define SOC_HIPACKPHY_PHYINITSTATUS_rdet_err_END (8)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdet_err_START (9)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdet_err_END (9)
#define SOC_HIPACKPHY_PHYINITSTATUS_cat_err_START (10)
#define SOC_HIPACKPHY_PHYINITSTATUS_cat_err_END (10)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_wrg_START (11)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_wrg_END (11)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_err_START (12)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_err_END (12)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_wrg_START (13)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_wrg_END (13)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_err_START (14)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_err_END (14)
#define SOC_HIPACKPHY_PHYINITSTATUS_retrain_active_START (31)
#define SOC_HIPACKPHY_PHYINITSTATUS_retrain_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dx_phy_clkgated : 4;
        unsigned int reserved_0 : 4;
        unsigned int ac_phy_clkgated : 1;
        unsigned int ck_phy_clkgated : 4;
        unsigned int dx_phgated_en : 1;
        unsigned int dx_phclkgated : 1;
        unsigned int dx_phgated_men : 1;
        unsigned int cfg_tx_rx_gcnt : 8;
        unsigned int reserved_1 : 6;
        unsigned int cfg_gcken_ca_rs : 1;
        unsigned int byp_pll_lock : 1;
    } reg;
} SOC_HIPACKPHY_PHYCLKGATED_UNION;
#endif
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phy_clkgated_START (0)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phy_clkgated_END (3)
#define SOC_HIPACKPHY_PHYCLKGATED_ac_phy_clkgated_START (8)
#define SOC_HIPACKPHY_PHYCLKGATED_ac_phy_clkgated_END (8)
#define SOC_HIPACKPHY_PHYCLKGATED_ck_phy_clkgated_START (9)
#define SOC_HIPACKPHY_PHYCLKGATED_ck_phy_clkgated_END (12)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_en_START (13)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_en_END (13)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phclkgated_START (14)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phclkgated_END (14)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_men_START (15)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_men_END (15)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_tx_rx_gcnt_START (16)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_tx_rx_gcnt_END (23)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_gcken_ca_rs_START (30)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_gcken_ca_rs_END (30)
#define SOC_HIPACKPHY_PHYCLKGATED_byp_pll_lock_START (31)
#define SOC_HIPACKPHY_PHYCLKGATED_byp_pll_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_dram_reset : 8;
        unsigned int reserved : 4;
        unsigned int t_dram_cke_high : 20;
    } reg;
} SOC_HIPACKPHY_PHYTIMER0_UNION;
#endif
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_reset_START (0)
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_reset_END (7)
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_cke_high_START (12)
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_cke_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_dram_cke_low : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_HIPACKPHY_PHYTIMER1_UNION;
#endif
#define SOC_HIPACKPHY_PHYTIMER1_t_dram_cke_low_START (0)
#define SOC_HIPACKPHY_PHYTIMER1_t_dram_cke_low_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pll_pwdn : 3;
        unsigned int reserved_0 : 1;
        unsigned int pll_freq_range : 2;
        unsigned int ac_pll_bp_refpfd : 1;
        unsigned int ac_pll_bp_refvco : 1;
        unsigned int ac_pll_enphsel : 1;
        unsigned int ac_pll_en_cal : 1;
        unsigned int ac_pll_initsel : 1;
        unsigned int ac_pll_lockt_sel : 1;
        unsigned int ac_pll_fopetestfb : 1;
        unsigned int ac_pll_fopetestref : 1;
        unsigned int ac_pll_lockin : 1;
        unsigned int ac_pll_outn : 1;
        unsigned int ac_pll_outp : 1;
        unsigned int reserved_1 : 7;
        unsigned int dx_pll_powerdown_23 : 2;
        unsigned int reserved_2 : 2;
        unsigned int dx_pll_powerdown_47 : 4;
    } reg;
} SOC_HIPACKPHY_PLLCTRL_UNION;
#endif
#define SOC_HIPACKPHY_PLLCTRL_pll_pwdn_START (0)
#define SOC_HIPACKPHY_PLLCTRL_pll_pwdn_END (2)
#define SOC_HIPACKPHY_PLLCTRL_pll_freq_range_START (4)
#define SOC_HIPACKPHY_PLLCTRL_pll_freq_range_END (5)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refpfd_START (6)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refpfd_END (6)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refvco_START (7)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refvco_END (7)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_enphsel_START (8)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_enphsel_END (8)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_en_cal_START (9)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_en_cal_END (9)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_initsel_START (10)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_initsel_END (10)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockt_sel_START (11)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockt_sel_END (11)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestfb_START (12)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestfb_END (12)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestref_START (13)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestref_END (13)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockin_START (14)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockin_END (14)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outn_START (15)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outn_END (15)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outp_START (16)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outp_END (16)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_23_START (24)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_23_END (25)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_47_START (28)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_47_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_pll_rst : 8;
        unsigned int reserved : 8;
        unsigned int t_pll_lock : 16;
    } reg;
} SOC_HIPACKPHY_PLLTIMER_UNION;
#endif
#define SOC_HIPACKPHY_PLLTIMER_t_pll_rst_START (0)
#define SOC_HIPACKPHY_PLLTIMER_t_pll_rst_END (7)
#define SOC_HIPACKPHY_PLLTIMER_t_pll_lock_START (16)
#define SOC_HIPACKPHY_PLLTIMER_t_pll_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dly_meas_type : 1;
        unsigned int dly_track_type : 1;
        unsigned int dlytrack_dqsgth : 2;
        unsigned int dynamic_dqsgen : 1;
        unsigned int dynamic_dqsen : 1;
        unsigned int phy_autoref_en : 1;
        unsigned int dly_meas_type_2t : 1;
        unsigned int dly_track_limit : 7;
        unsigned int reserved_0 : 1;
        unsigned int dynamic_dqsg_ph_dis : 1;
        unsigned int reserved_1 : 3;
        unsigned int dlytrack_dqsth : 2;
        unsigned int dlytrack_dqsg_tap : 2;
        unsigned int dlytrack_dqs_tap : 2;
        unsigned int dlytrack_cyc_tap : 4;
        unsigned int rdqsg_mondly_type : 2;
    } reg;
} SOC_HIPACKPHY_DLYMEASCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_START (0)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_END (0)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_type_START (1)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_type_END (1)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsgth_START (2)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsgth_END (3)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsgen_START (4)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsgen_END (4)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsen_START (5)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsen_END (5)
#define SOC_HIPACKPHY_DLYMEASCTRL_phy_autoref_en_START (6)
#define SOC_HIPACKPHY_DLYMEASCTRL_phy_autoref_en_END (6)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_2t_START (7)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_2t_END (7)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_limit_START (8)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_limit_END (14)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsg_ph_dis_START (16)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsg_ph_dis_END (16)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsth_START (20)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsth_END (21)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsg_tap_START (22)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsg_tap_END (23)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqs_tap_START (24)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqs_tap_END (25)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_cyc_tap_START (26)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_cyc_tap_END (29)
#define SOC_HIPACKPHY_DLYMEASCTRL_rdqsg_mondly_type_START (30)
#define SOC_HIPACKPHY_DLYMEASCTRL_rdqsg_mondly_type_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int zcomp_rsp_dly : 6;
        unsigned int tzcomp_upddly : 6;
        unsigned int zcomp_num : 4;
        unsigned int zcalrt_range : 6;
        unsigned int reserved : 4;
        unsigned int zcal_platch_inv : 1;
        unsigned int zcal_pnsequence : 1;
        unsigned int zcal_errstopup : 1;
        unsigned int zcalrt_updckelh_dis : 1;
        unsigned int zcalrt_en : 1;
        unsigned int zcfuzzy_en : 1;
    } reg;
} SOC_HIPACKPHY_IMPCTRL_UNION;
#endif
#define SOC_HIPACKPHY_IMPCTRL_zcomp_rsp_dly_START (0)
#define SOC_HIPACKPHY_IMPCTRL_zcomp_rsp_dly_END (5)
#define SOC_HIPACKPHY_IMPCTRL_tzcomp_upddly_START (6)
#define SOC_HIPACKPHY_IMPCTRL_tzcomp_upddly_END (11)
#define SOC_HIPACKPHY_IMPCTRL_zcomp_num_START (12)
#define SOC_HIPACKPHY_IMPCTRL_zcomp_num_END (15)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_range_START (16)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_range_END (21)
#define SOC_HIPACKPHY_IMPCTRL_zcal_platch_inv_START (26)
#define SOC_HIPACKPHY_IMPCTRL_zcal_platch_inv_END (26)
#define SOC_HIPACKPHY_IMPCTRL_zcal_pnsequence_START (27)
#define SOC_HIPACKPHY_IMPCTRL_zcal_pnsequence_END (27)
#define SOC_HIPACKPHY_IMPCTRL_zcal_errstopup_START (28)
#define SOC_HIPACKPHY_IMPCTRL_zcal_errstopup_END (28)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_updckelh_dis_START (29)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_updckelh_dis_END (29)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_en_START (30)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_en_END (30)
#define SOC_HIPACKPHY_IMPCTRL_zcfuzzy_en_START (31)
#define SOC_HIPACKPHY_IMPCTRL_zcfuzzy_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int zcode_ndrv : 6;
        unsigned int reserved_0 : 1;
        unsigned int ndrv_cal_result : 1;
        unsigned int zcode_ndrv_cal : 7;
        unsigned int reserved_1 : 1;
        unsigned int zcode_pdrv : 6;
        unsigned int reserved_2 : 1;
        unsigned int pdrv_cal_result : 1;
        unsigned int zcode_pdrv_cal : 7;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_HIPACKPHY_IMPSTATUS_UNION;
#endif
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_START (0)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_END (5)
#define SOC_HIPACKPHY_IMPSTATUS_ndrv_cal_result_START (7)
#define SOC_HIPACKPHY_IMPSTATUS_ndrv_cal_result_END (7)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_cal_START (8)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_cal_END (14)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_START (16)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_END (21)
#define SOC_HIPACKPHY_IMPSTATUS_pdrv_cal_result_START (23)
#define SOC_HIPACKPHY_IMPSTATUS_pdrv_cal_result_END (23)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_cal_START (24)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_cal_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dram_type : 3;
        unsigned int dram_type_exd : 1;
        unsigned int nosra : 1;
        unsigned int ma2t : 1;
        unsigned int maddr_mir : 1;
        unsigned int lpddr23_mrw11_en : 1;
        unsigned int lpddr23_pre_en : 1;
        unsigned int lpddr23_mrw1617_en : 1;
        unsigned int lpddr23_zqc_en : 1;
        unsigned int lpddr23_mrw_rst_ca3t : 1;
        unsigned int lpddr23_early_cat_en : 1;
        unsigned int ddr4par_en : 1;
        unsigned int mrs_seq_prog_en : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_HIPACKPHY_DRAMCFG_UNION;
#endif
#define SOC_HIPACKPHY_DRAMCFG_dram_type_START (0)
#define SOC_HIPACKPHY_DRAMCFG_dram_type_END (2)
#define SOC_HIPACKPHY_DRAMCFG_dram_type_exd_START (3)
#define SOC_HIPACKPHY_DRAMCFG_dram_type_exd_END (3)
#define SOC_HIPACKPHY_DRAMCFG_nosra_START (4)
#define SOC_HIPACKPHY_DRAMCFG_nosra_END (4)
#define SOC_HIPACKPHY_DRAMCFG_ma2t_START (5)
#define SOC_HIPACKPHY_DRAMCFG_ma2t_END (5)
#define SOC_HIPACKPHY_DRAMCFG_maddr_mir_START (6)
#define SOC_HIPACKPHY_DRAMCFG_maddr_mir_END (6)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw11_en_START (7)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw11_en_END (7)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_pre_en_START (8)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_pre_en_END (8)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw1617_en_START (9)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw1617_en_END (9)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_zqc_en_START (10)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_zqc_en_END (10)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw_rst_ca3t_START (11)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw_rst_ca3t_END (11)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_early_cat_en_START (12)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_early_cat_en_END (12)
#define SOC_HIPACKPHY_DRAMCFG_ddr4par_en_START (13)
#define SOC_HIPACKPHY_DRAMCFG_ddr4par_en_END (13)
#define SOC_HIPACKPHY_DRAMCFG_mrs_seq_prog_en_START (14)
#define SOC_HIPACKPHY_DRAMCFG_mrs_seq_prog_en_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_rtp : 4;
        unsigned int t_wtr : 4;
        unsigned int t_rp : 4;
        unsigned int t_rcd : 4;
        unsigned int t_ras : 6;
        unsigned int t_rrd : 4;
        unsigned int t_rc : 6;
    } reg;
} SOC_HIPACKPHY_DRAMTIMER0_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER0_t_rtp_START (0)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rtp_END (3)
#define SOC_HIPACKPHY_DRAMTIMER0_t_wtr_START (4)
#define SOC_HIPACKPHY_DRAMTIMER0_t_wtr_END (7)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rp_START (8)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rp_END (11)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rcd_START (12)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rcd_END (15)
#define SOC_HIPACKPHY_DRAMTIMER0_t_ras_START (16)
#define SOC_HIPACKPHY_DRAMTIMER0_t_ras_END (21)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rrd_START (22)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rrd_END (25)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rc_START (26)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rc_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_mrd : 4;
        unsigned int t_mod : 5;
        unsigned int t_faw : 6;
        unsigned int reserved_0: 1;
        unsigned int t_rfc : 9;
        unsigned int t_rtw : 5;
        unsigned int reserved_1: 2;
    } reg;
} SOC_HIPACKPHY_DRAMTIMER1_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER1_t_mrd_START (0)
#define SOC_HIPACKPHY_DRAMTIMER1_t_mrd_END (3)
#define SOC_HIPACKPHY_DRAMTIMER1_t_mod_START (4)
#define SOC_HIPACKPHY_DRAMTIMER1_t_mod_END (8)
#define SOC_HIPACKPHY_DRAMTIMER1_t_faw_START (9)
#define SOC_HIPACKPHY_DRAMTIMER1_t_faw_END (14)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rfc_START (16)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rfc_END (24)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rtw_START (25)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rtw_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_xs : 10;
        unsigned int t_xp : 5;
        unsigned int reserved_0: 1;
        unsigned int t_cke : 4;
        unsigned int t_dllk : 10;
        unsigned int reserved_1: 1;
        unsigned int t_ccd : 1;
    } reg;
} SOC_HIPACKPHY_DRAMTIMER2_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER2_t_xs_START (0)
#define SOC_HIPACKPHY_DRAMTIMER2_t_xs_END (9)
#define SOC_HIPACKPHY_DRAMTIMER2_t_xp_START (10)
#define SOC_HIPACKPHY_DRAMTIMER2_t_xp_END (14)
#define SOC_HIPACKPHY_DRAMTIMER2_t_cke_START (16)
#define SOC_HIPACKPHY_DRAMTIMER2_t_cke_END (19)
#define SOC_HIPACKPHY_DRAMTIMER2_t_dllk_START (20)
#define SOC_HIPACKPHY_DRAMTIMER2_t_dllk_END (29)
#define SOC_HIPACKPHY_DRAMTIMER2_t_ccd_START (31)
#define SOC_HIPACKPHY_DRAMTIMER2_t_ccd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_zcal : 10;
        unsigned int t_init5 : 14;
        unsigned int tdshtrain : 4;
        unsigned int t_wr : 4;
    } reg;
} SOC_HIPACKPHY_DRAMTIMER3_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER3_t_zcal_START (0)
#define SOC_HIPACKPHY_DRAMTIMER3_t_zcal_END (9)
#define SOC_HIPACKPHY_DRAMTIMER3_t_init5_START (10)
#define SOC_HIPACKPHY_DRAMTIMER3_t_init5_END (23)
#define SOC_HIPACKPHY_DRAMTIMER3_tdshtrain_START (24)
#define SOC_HIPACKPHY_DRAMTIMER3_tdshtrain_END (27)
#define SOC_HIPACKPHY_DRAMTIMER3_t_wr_START (28)
#define SOC_HIPACKPHY_DRAMTIMER3_t_wr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_wlmrd : 6;
        unsigned int t_wr_ext : 1;
        unsigned int t_wlo : 5;
        unsigned int t_odt : 4;
        unsigned int t_ccd_s : 4;
        unsigned int t_vref : 3;
        unsigned int reserved : 1;
        unsigned int t_odton : 4;
        unsigned int t_ccd_ddr4 : 4;
    } reg;
} SOC_HIPACKPHY_DRAMTIMER4_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlmrd_START (0)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlmrd_END (5)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wr_ext_START (6)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wr_ext_END (6)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlo_START (7)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlo_END (11)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odt_START (12)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odt_END (15)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_s_START (16)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_s_END (19)
#define SOC_HIPACKPHY_DRAMTIMER4_t_vref_START (20)
#define SOC_HIPACKPHY_DRAMTIMER4_t_vref_END (22)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odton_START (24)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odton_END (27)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_ddr4_START (28)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_ddr4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wodt_rank0 : 4;
        unsigned int wodt_rank1 : 4;
        unsigned int wodt_rank2 : 4;
        unsigned int wodt_rank3 : 4;
        unsigned int reserved : 16;
    } reg;
} SOC_HIPACKPHY_ODTCR_UNION;
#endif
#define SOC_HIPACKPHY_ODTCR_wodt_rank0_START (0)
#define SOC_HIPACKPHY_ODTCR_wodt_rank0_END (3)
#define SOC_HIPACKPHY_ODTCR_wodt_rank1_START (4)
#define SOC_HIPACKPHY_ODTCR_wodt_rank1_END (7)
#define SOC_HIPACKPHY_ODTCR_wodt_rank2_START (8)
#define SOC_HIPACKPHY_ODTCR_wodt_rank2_END (11)
#define SOC_HIPACKPHY_ODTCR_wodt_rank3_START (12)
#define SOC_HIPACKPHY_ODTCR_wodt_rank3_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dtr_rank : 4;
        unsigned int dqsgsl_mrgn : 6;
        unsigned int dqsgrt_shft : 6;
        unsigned int dqsgrt_chk : 6;
        unsigned int gtfback_en : 1;
        unsigned int reserved : 1;
        unsigned int gtdsdly : 6;
        unsigned int dtrerrstop : 1;
        unsigned int detskipeyop : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL0_dtr_rank_START (0)
#define SOC_HIPACKPHY_TRAINCTRL0_dtr_rank_END (3)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgsl_mrgn_START (4)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgsl_mrgn_END (9)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_shft_START (10)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_shft_END (15)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_chk_START (16)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_chk_END (21)
#define SOC_HIPACKPHY_TRAINCTRL0_gtfback_en_START (22)
#define SOC_HIPACKPHY_TRAINCTRL0_gtfback_en_END (22)
#define SOC_HIPACKPHY_TRAINCTRL0_gtdsdly_START (24)
#define SOC_HIPACKPHY_TRAINCTRL0_gtdsdly_END (29)
#define SOC_HIPACKPHY_TRAINCTRL0_dtrerrstop_START (30)
#define SOC_HIPACKPHY_TRAINCTRL0_dtrerrstop_END (30)
#define SOC_HIPACKPHY_TRAINCTRL0_detskipeyop_START (31)
#define SOC_HIPACKPHY_TRAINCTRL0_detskipeyop_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rank_en : 16;
        unsigned int dtbankgrp : 3;
        unsigned int reserved_0 : 1;
        unsigned int dtbankgrp_tg1 : 3;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_HIPACKPHY_RANKEN_UNION;
#endif
#define SOC_HIPACKPHY_RANKEN_rank_en_START (0)
#define SOC_HIPACKPHY_RANKEN_rank_en_END (15)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_START (16)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_END (18)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_tg1_START (20)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_tg1_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dtbank : 3;
        unsigned int reserved : 1;
        unsigned int dtcol : 12;
        unsigned int dtrow : 16;
    } reg;
} SOC_HIPACKPHY_TRAINMADDR_UNION;
#endif
#define SOC_HIPACKPHY_TRAINMADDR_dtbank_START (0)
#define SOC_HIPACKPHY_TRAINMADDR_dtbank_END (2)
#define SOC_HIPACKPHY_TRAINMADDR_dtcol_START (4)
#define SOC_HIPACKPHY_TRAINMADDR_dtcol_END (15)
#define SOC_HIPACKPHY_TRAINMADDR_dtrow_START (16)
#define SOC_HIPACKPHY_TRAINMADDR_dtrow_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bist_op : 2;
        unsigned int reserved_0 : 2;
        unsigned int bist_mode : 3;
        unsigned int reserved_1 : 1;
        unsigned int bist_pat : 3;
        unsigned int sso_bist_cnt : 3;
        unsigned int reserved_2 : 1;
        unsigned int dfi_phyupd_disable : 1;
        unsigned int bist_fail_stop : 8;
        unsigned int rnk_sw_mode : 1;
        unsigned int brst_cnt : 7;
    } reg;
} SOC_HIPACKPHY_BISTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_BISTCTRL_bist_op_START (0)
#define SOC_HIPACKPHY_BISTCTRL_bist_op_END (1)
#define SOC_HIPACKPHY_BISTCTRL_bist_mode_START (4)
#define SOC_HIPACKPHY_BISTCTRL_bist_mode_END (6)
#define SOC_HIPACKPHY_BISTCTRL_bist_pat_START (8)
#define SOC_HIPACKPHY_BISTCTRL_bist_pat_END (10)
#define SOC_HIPACKPHY_BISTCTRL_sso_bist_cnt_START (11)
#define SOC_HIPACKPHY_BISTCTRL_sso_bist_cnt_END (13)
#define SOC_HIPACKPHY_BISTCTRL_dfi_phyupd_disable_START (15)
#define SOC_HIPACKPHY_BISTCTRL_dfi_phyupd_disable_END (15)
#define SOC_HIPACKPHY_BISTCTRL_bist_fail_stop_START (16)
#define SOC_HIPACKPHY_BISTCTRL_bist_fail_stop_END (23)
#define SOC_HIPACKPHY_BISTCTRL_rnk_sw_mode_START (24)
#define SOC_HIPACKPHY_BISTCTRL_rnk_sw_mode_END (24)
#define SOC_HIPACKPHY_BISTCTRL_brst_cnt_START (25)
#define SOC_HIPACKPHY_BISTCTRL_brst_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bist_data_b0 : 8;
        unsigned int bist_data_b1 : 8;
        unsigned int bist_data_b2 : 8;
        unsigned int bist_data_b3 : 8;
    } reg;
} SOC_HIPACKPHY_BISTDATA0_UNION;
#endif
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b0_START (0)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b0_END (7)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b1_START (8)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b1_END (15)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b2_START (16)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b2_END (23)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b3_START (24)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bist_data_b4 : 8;
        unsigned int bist_data_b5 : 8;
        unsigned int bist_data_b6 : 8;
        unsigned int bist_data_b7 : 8;
    } reg;
} SOC_HIPACKPHY_BISTDATA1_UNION;
#endif
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b4_START (0)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b4_END (7)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b5_START (8)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b5_END (15)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b6_START (16)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b6_END (23)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b7_START (24)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bist_done : 1;
        unsigned int bist_acerr : 1;
        unsigned int bist_dxerr : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_HIPACKPHY_BISTSTATUS_UNION;
#endif
#define SOC_HIPACKPHY_BISTSTATUS_bist_done_START (0)
#define SOC_HIPACKPHY_BISTSTATUS_bist_done_END (0)
#define SOC_HIPACKPHY_BISTSTATUS_bist_acerr_START (1)
#define SOC_HIPACKPHY_BISTSTATUS_bist_acerr_END (1)
#define SOC_HIPACKPHY_BISTSTATUS_bist_dxerr_START (2)
#define SOC_HIPACKPHY_BISTSTATUS_bist_dxerr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mr0 : 16;
        unsigned int mr1 : 16;
    } reg;
} SOC_HIPACKPHY_MODEREG01_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG01_mr0_START (0)
#define SOC_HIPACKPHY_MODEREG01_mr0_END (15)
#define SOC_HIPACKPHY_MODEREG01_mr1_START (16)
#define SOC_HIPACKPHY_MODEREG01_mr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mr2 : 16;
        unsigned int mr3 : 16;
    } reg;
} SOC_HIPACKPHY_MODEREG23_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG23_mr2_START (0)
#define SOC_HIPACKPHY_MODEREG23_mr2_END (15)
#define SOC_HIPACKPHY_MODEREG23_mr3_START (16)
#define SOC_HIPACKPHY_MODEREG23_mr3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int det_pat_pat : 32;
    } reg;
} SOC_HIPACKPHY_DETPATTERN_UNION;
#endif
#define SOC_HIPACKPHY_DETPATTERN_det_pat_pat_START (0)
#define SOC_HIPACKPHY_DETPATTERN_det_pat_pat_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_wl : 8;
        unsigned int cfg_rl : 8;
        unsigned int scramb_en : 1;
        unsigned int addr_toggle : 1;
        unsigned int addr_delay : 1;
        unsigned int cfg_dlyupd : 1;
        unsigned int swap_en : 3;
        unsigned int reserved_0 : 2;
        unsigned int swapdm_en : 2;
        unsigned int swapwl_en : 3;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_HIPACKPHY_MISC_UNION;
#endif
#define SOC_HIPACKPHY_MISC_cfg_wl_START (0)
#define SOC_HIPACKPHY_MISC_cfg_wl_END (7)
#define SOC_HIPACKPHY_MISC_cfg_rl_START (8)
#define SOC_HIPACKPHY_MISC_cfg_rl_END (15)
#define SOC_HIPACKPHY_MISC_scramb_en_START (16)
#define SOC_HIPACKPHY_MISC_scramb_en_END (16)
#define SOC_HIPACKPHY_MISC_addr_toggle_START (17)
#define SOC_HIPACKPHY_MISC_addr_toggle_END (17)
#define SOC_HIPACKPHY_MISC_addr_delay_START (18)
#define SOC_HIPACKPHY_MISC_addr_delay_END (18)
#define SOC_HIPACKPHY_MISC_cfg_dlyupd_START (19)
#define SOC_HIPACKPHY_MISC_cfg_dlyupd_END (19)
#define SOC_HIPACKPHY_MISC_swap_en_START (20)
#define SOC_HIPACKPHY_MISC_swap_en_END (22)
#define SOC_HIPACKPHY_MISC_swapdm_en_START (25)
#define SOC_HIPACKPHY_MISC_swapdm_en_END (26)
#define SOC_HIPACKPHY_MISC_swapwl_en_START (27)
#define SOC_HIPACKPHY_MISC_swapwl_en_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trnkwtw : 5;
        unsigned int trnkrtr : 5;
        unsigned int trnkrtw : 5;
        unsigned int trnkwtr : 5;
        unsigned int reserved : 9;
        unsigned int dfi2iomap : 3;
    } reg;
} SOC_HIPACKPHY_RNK2RNK_UNION;
#endif
#define SOC_HIPACKPHY_RNK2RNK_trnkwtw_START (0)
#define SOC_HIPACKPHY_RNK2RNK_trnkwtw_END (4)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtr_START (5)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtr_END (9)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtw_START (10)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtw_END (14)
#define SOC_HIPACKPHY_RNK2RNK_trnkwtr_START (15)
#define SOC_HIPACKPHY_RNK2RNK_trnkwtr_END (19)
#define SOC_HIPACKPHY_RNK2RNK_dfi2iomap_START (29)
#define SOC_HIPACKPHY_RNK2RNK_dfi2iomap_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reg_sel_dficlk_rx : 1;
        unsigned int sel_pos_rx : 1;
        unsigned int lp_ck_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int cmdoen : 1;
        unsigned int ckoen : 3;
        unsigned int ckeoen : 1;
        unsigned int csoen : 1;
        unsigned int resetoen : 1;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_HIPACKPHY_PHYCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_PHYCTRL0_reg_sel_dficlk_rx_START (1)
#define SOC_HIPACKPHY_PHYCTRL0_reg_sel_dficlk_rx_END (1)
#define SOC_HIPACKPHY_PHYCTRL0_sel_pos_rx_START (2)
#define SOC_HIPACKPHY_PHYCTRL0_sel_pos_rx_END (2)
#define SOC_HIPACKPHY_PHYCTRL0_lp_ck_sel_START (3)
#define SOC_HIPACKPHY_PHYCTRL0_lp_ck_sel_END (4)
#define SOC_HIPACKPHY_PHYCTRL0_cmdoen_START (7)
#define SOC_HIPACKPHY_PHYCTRL0_cmdoen_END (7)
#define SOC_HIPACKPHY_PHYCTRL0_ckoen_START (8)
#define SOC_HIPACKPHY_PHYCTRL0_ckoen_END (10)
#define SOC_HIPACKPHY_PHYCTRL0_ckeoen_START (11)
#define SOC_HIPACKPHY_PHYCTRL0_ckeoen_END (11)
#define SOC_HIPACKPHY_PHYCTRL0_csoen_START (12)
#define SOC_HIPACKPHY_PHYCTRL0_csoen_END (12)
#define SOC_HIPACKPHY_PHYCTRL0_resetoen_START (13)
#define SOC_HIPACKPHY_PHYCTRL0_resetoen_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqs_gated_error : 8;
        unsigned int reserved_0 : 8;
        unsigned int dqsb_gated_error : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_HIPACKPHY_PHYDBG_UNION;
#endif
#define SOC_HIPACKPHY_PHYDBG_dqs_gated_error_START (0)
#define SOC_HIPACKPHY_PHYDBG_dqs_gated_error_END (7)
#define SOC_HIPACKPHY_PHYDBG_dqsb_gated_error_START (16)
#define SOC_HIPACKPHY_PHYDBG_dqsb_gated_error_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyupd_resp : 13;
        unsigned int retrain_en : 1;
        unsigned int gtrten : 1;
        unsigned int rderten : 1;
        unsigned int retrain_thrd : 16;
    } reg;
} SOC_HIPACKPHY_RETCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_RETCTRL0_phyupd_resp_START (0)
#define SOC_HIPACKPHY_RETCTRL0_phyupd_resp_END (12)
#define SOC_HIPACKPHY_RETCTRL0_retrain_en_START (13)
#define SOC_HIPACKPHY_RETCTRL0_retrain_en_END (13)
#define SOC_HIPACKPHY_RETCTRL0_gtrten_START (14)
#define SOC_HIPACKPHY_RETCTRL0_gtrten_END (14)
#define SOC_HIPACKPHY_RETCTRL0_rderten_START (15)
#define SOC_HIPACKPHY_RETCTRL0_rderten_END (15)
#define SOC_HIPACKPHY_RETCTRL0_retrain_thrd_START (16)
#define SOC_HIPACKPHY_RETCTRL0_retrain_thrd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_dmswap_sel : 4;
        unsigned int rt_onebyone : 1;
        unsigned int fast_wl2_en : 1;
        unsigned int wlpulsecnt : 2;
        unsigned int tphy_wrdata : 1;
        unsigned int ddr4_dm_inv_en : 1;
        unsigned int rs_rstcont_passthrough : 1;
        unsigned int rs_rst_passthrough : 1;
        unsigned int rs_passthrough : 1;
        unsigned int phystop_en : 1;
        unsigned int phyupd_type_nopre : 2;
        unsigned int phyupd_type_pre : 2;
        unsigned int packdbgout : 1;
        unsigned int rsneg_rstcont_passthrough : 1;
        unsigned int rsneg_rst_passthrough : 1;
        unsigned int rsneg_passthrough : 1;
        unsigned int wlexitmode : 1;
        unsigned int bl32atonthefly : 1;
        unsigned int swapdfibyte_en : 3;
        unsigned int swapaddr_en : 3;
        unsigned int tphy_wrdata_ext : 2;
    } reg;
} SOC_HIPACKPHY_DMSEL_UNION;
#endif
#define SOC_HIPACKPHY_DMSEL_dxctl_dmswap_sel_START (0)
#define SOC_HIPACKPHY_DMSEL_dxctl_dmswap_sel_END (3)
#define SOC_HIPACKPHY_DMSEL_rt_onebyone_START (4)
#define SOC_HIPACKPHY_DMSEL_rt_onebyone_END (4)
#define SOC_HIPACKPHY_DMSEL_fast_wl2_en_START (5)
#define SOC_HIPACKPHY_DMSEL_fast_wl2_en_END (5)
#define SOC_HIPACKPHY_DMSEL_wlpulsecnt_START (6)
#define SOC_HIPACKPHY_DMSEL_wlpulsecnt_END (7)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_START (8)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_END (8)
#define SOC_HIPACKPHY_DMSEL_ddr4_dm_inv_en_START (9)
#define SOC_HIPACKPHY_DMSEL_ddr4_dm_inv_en_END (9)
#define SOC_HIPACKPHY_DMSEL_rs_rstcont_passthrough_START (10)
#define SOC_HIPACKPHY_DMSEL_rs_rstcont_passthrough_END (10)
#define SOC_HIPACKPHY_DMSEL_rs_rst_passthrough_START (11)
#define SOC_HIPACKPHY_DMSEL_rs_rst_passthrough_END (11)
#define SOC_HIPACKPHY_DMSEL_rs_passthrough_START (12)
#define SOC_HIPACKPHY_DMSEL_rs_passthrough_END (12)
#define SOC_HIPACKPHY_DMSEL_phystop_en_START (13)
#define SOC_HIPACKPHY_DMSEL_phystop_en_END (13)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_nopre_START (14)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_nopre_END (15)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_pre_START (16)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_pre_END (17)
#define SOC_HIPACKPHY_DMSEL_packdbgout_START (18)
#define SOC_HIPACKPHY_DMSEL_packdbgout_END (18)
#define SOC_HIPACKPHY_DMSEL_rsneg_rstcont_passthrough_START (19)
#define SOC_HIPACKPHY_DMSEL_rsneg_rstcont_passthrough_END (19)
#define SOC_HIPACKPHY_DMSEL_rsneg_rst_passthrough_START (20)
#define SOC_HIPACKPHY_DMSEL_rsneg_rst_passthrough_END (20)
#define SOC_HIPACKPHY_DMSEL_rsneg_passthrough_START (21)
#define SOC_HIPACKPHY_DMSEL_rsneg_passthrough_END (21)
#define SOC_HIPACKPHY_DMSEL_wlexitmode_START (22)
#define SOC_HIPACKPHY_DMSEL_wlexitmode_END (22)
#define SOC_HIPACKPHY_DMSEL_bl32atonthefly_START (23)
#define SOC_HIPACKPHY_DMSEL_bl32atonthefly_END (23)
#define SOC_HIPACKPHY_DMSEL_swapdfibyte_en_START (24)
#define SOC_HIPACKPHY_DMSEL_swapdfibyte_en_END (26)
#define SOC_HIPACKPHY_DMSEL_swapaddr_en_START (27)
#define SOC_HIPACKPHY_DMSEL_swapaddr_en_END (29)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_ext_START (30)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_ext_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int diff_dqs_en : 1;
        unsigned int dxiopldn : 1;
        unsigned int aciopldn : 1;
        unsigned int ioctl_genvref_dram_refsel_2 : 2;
        unsigned int ioctl_genvref_dram_refsel_1 : 2;
        unsigned int ioctl_genvref_dram_refsel_0 : 2;
        unsigned int ioctl_genvref_dram_pd : 2;
        unsigned int ronsel : 3;
        unsigned int ronsel_dqs : 3;
        unsigned int ronsel_ac1t : 3;
        unsigned int ronsel_ac2t : 3;
        unsigned int ronsel_ck : 3;
        unsigned int odtsel : 3;
        unsigned int odtsel_dqs : 3;
    } reg;
} SOC_HIPACKPHY_IOCTL_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL_diff_dqs_en_START (0)
#define SOC_HIPACKPHY_IOCTL_diff_dqs_en_END (0)
#define SOC_HIPACKPHY_IOCTL_dxiopldn_START (1)
#define SOC_HIPACKPHY_IOCTL_dxiopldn_END (1)
#define SOC_HIPACKPHY_IOCTL_aciopldn_START (2)
#define SOC_HIPACKPHY_IOCTL_aciopldn_END (2)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_2_START (3)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_2_END (4)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_1_START (5)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_1_END (6)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_0_START (7)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_0_END (8)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_pd_START (9)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_pd_END (10)
#define SOC_HIPACKPHY_IOCTL_ronsel_START (11)
#define SOC_HIPACKPHY_IOCTL_ronsel_END (13)
#define SOC_HIPACKPHY_IOCTL_ronsel_dqs_START (14)
#define SOC_HIPACKPHY_IOCTL_ronsel_dqs_END (16)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac1t_START (17)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac1t_END (19)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac2t_START (20)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac2t_END (22)
#define SOC_HIPACKPHY_IOCTL_ronsel_ck_START (23)
#define SOC_HIPACKPHY_IOCTL_ronsel_ck_END (25)
#define SOC_HIPACKPHY_IOCTL_odtsel_START (26)
#define SOC_HIPACKPHY_IOCTL_odtsel_END (28)
#define SOC_HIPACKPHY_IOCTL_odtsel_dqs_START (29)
#define SOC_HIPACKPHY_IOCTL_odtsel_dqs_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqswap_sel : 32;
    } reg;
} SOC_HIPACKPHY_DQSSEL_UNION;
#endif
#define SOC_HIPACKPHY_DQSSEL_dqswap_sel_START (0)
#define SOC_HIPACKPHY_DQSSEL_dqswap_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int ac_pll_thrm : 1;
        unsigned int ac_pll_testpem : 1;
        unsigned int ac_pll_testen : 1;
        unsigned int ac_pll_init : 1;
        unsigned int ac_pll_cpi : 3;
        unsigned int ac_pll_sp : 3;
        unsigned int ac_pll_lt : 2;
        unsigned int ac_pll_calt : 1;
        unsigned int ac_pll_calm : 1;
        unsigned int ac_pll_cal : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_PHYCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_thrm_START (16)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_thrm_END (16)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testpem_START (17)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testpem_END (17)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testen_START (18)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testen_END (18)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_init_START (19)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_init_END (19)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cpi_START (20)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cpi_END (22)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_sp_START (23)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_sp_END (25)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_lt_START (26)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_lt_END (27)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calt_START (28)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calt_END (28)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calm_START (29)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calm_END (29)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cal_START (30)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cal_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dx_ckd2 : 3;
        unsigned int dx_ck0p_mclk : 3;
        unsigned int reserved : 26;
    } reg;
} SOC_HIPACKPHY_DXNCKCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ckd2_START (0)
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ckd2_END (2)
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ck0p_mclk_START (3)
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ck0p_mclk_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_pll_test : 8;
        unsigned int reserved : 23;
        unsigned int ac_pll_lock : 1;
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_AC_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_test_START (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_test_END (7)
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_lock_START (31)
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dx_pll_test : 16;
        unsigned int reserved : 12;
        unsigned int dx_pll_lock : 4;
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_test_START (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_test_END (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_lock_START (28)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw_wlmode : 1;
        unsigned int sw_gtmode : 1;
        unsigned int reserved_0 : 2;
        unsigned int sw_wlmodeb : 8;
        unsigned int reserved_1 : 19;
        unsigned int wl_wdqs_gated : 1;
    } reg;
} SOC_HIPACKPHY_SWTMODE_UNION;
#endif
#define SOC_HIPACKPHY_SWTMODE_sw_wlmode_START (0)
#define SOC_HIPACKPHY_SWTMODE_sw_wlmode_END (0)
#define SOC_HIPACKPHY_SWTMODE_sw_gtmode_START (1)
#define SOC_HIPACKPHY_SWTMODE_sw_gtmode_END (1)
#define SOC_HIPACKPHY_SWTMODE_sw_wlmodeb_START (4)
#define SOC_HIPACKPHY_SWTMODE_sw_wlmodeb_END (11)
#define SOC_HIPACKPHY_SWTMODE_wl_wdqs_gated_START (31)
#define SOC_HIPACKPHY_SWTMODE_wl_wdqs_gated_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw_wl_dqs : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HIPACKPHY_SWTWLDQS_UNION;
#endif
#define SOC_HIPACKPHY_SWTWLDQS_sw_wl_dqs_START (0)
#define SOC_HIPACKPHY_SWTWLDQS_sw_wl_dqs_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wl_dq_result : 8;
        unsigned int gt_result : 8;
        unsigned int gds_result : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_HIPACKPHY_SWTRLT_UNION;
#endif
#define SOC_HIPACKPHY_SWTRLT_wl_dq_result_START (0)
#define SOC_HIPACKPHY_SWTRLT_wl_dq_result_END (7)
#define SOC_HIPACKPHY_SWTRLT_gt_result_START (8)
#define SOC_HIPACKPHY_SWTRLT_gt_result_END (15)
#define SOC_HIPACKPHY_SWTRLT_gds_result_START (16)
#define SOC_HIPACKPHY_SWTRLT_gds_result_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_dqsgerror : 1;
        unsigned int phy_gatetdc : 1;
        unsigned int phy_odten_gated : 1;
        unsigned int phy_dummypad_use : 1;
        unsigned int phy_dyn_pupden : 1;
        unsigned int dx_reg_dvalid_selfgen_en : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_HIPACKPHY_PHYCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_PHYCTRL2_phy_dqsgerror_START (0)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dqsgerror_END (0)
#define SOC_HIPACKPHY_PHYCTRL2_phy_gatetdc_START (1)
#define SOC_HIPACKPHY_PHYCTRL2_phy_gatetdc_END (1)
#define SOC_HIPACKPHY_PHYCTRL2_phy_odten_gated_START (2)
#define SOC_HIPACKPHY_PHYCTRL2_phy_odten_gated_END (2)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dummypad_use_START (3)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dummypad_use_END (3)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dyn_pupden_START (4)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dyn_pupden_END (4)
#define SOC_HIPACKPHY_PHYCTRL2_dx_reg_dvalid_selfgen_en_START (5)
#define SOC_HIPACKPHY_PHYCTRL2_dx_reg_dvalid_selfgen_en_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ioctl_genvref_range_2 : 6;
        unsigned int odt_ioctl_rdsel_p : 3;
        unsigned int odt_ioctl_rdsel_n : 3;
        unsigned int ioctl_genvref_pd : 6;
        unsigned int ioctl_genvref_dram_range_2 : 2;
        unsigned int ioctl_genvref_dram_range_1 : 2;
        unsigned int ioctl_genvref_dram_range_0 : 2;
        unsigned int ioctl_squeach_pd : 4;
        unsigned int odt_ioctl_ronsel : 3;
        unsigned int ioctl_odt_iopldn : 1;
    } reg;
} SOC_HIPACKPHY_IOCTL1_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_range_2_START (0)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_range_2_END (5)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_p_START (6)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_p_END (8)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_n_START (9)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_n_END (11)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_pd_START (12)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_pd_END (17)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_2_START (18)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_2_END (19)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_1_START (20)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_1_END (21)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_0_START (22)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_0_END (23)
#define SOC_HIPACKPHY_IOCTL1_ioctl_squeach_pd_START (24)
#define SOC_HIPACKPHY_IOCTL1_ioctl_squeach_pd_END (27)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_ronsel_START (28)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_ronsel_END (30)
#define SOC_HIPACKPHY_IOCTL1_ioctl_odt_iopldn_START (31)
#define SOC_HIPACKPHY_IOCTL1_ioctl_odt_iopldn_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ioctl_genvref_range_0 : 6;
        unsigned int ioctl_genvref_range_1 : 6;
        unsigned int ioctl_genvref_refsel_0 : 6;
        unsigned int ioctl_genvref_refsel_1 : 6;
        unsigned int ioctl_genvref_refsel_2 : 6;
        unsigned int top_topctl_odt_o : 1;
        unsigned int top_topctl_odt_oe : 1;
    } reg;
} SOC_HIPACKPHY_IOCTL2_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_0_START (0)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_0_END (5)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_1_START (6)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_1_END (11)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_0_START (12)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_0_END (17)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_1_START (18)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_1_END (23)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_2_START (24)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_2_END (29)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_o_START (30)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_o_END (30)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_oe_START (31)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_oe_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dtbank_tg1 : 3;
        unsigned int reserved : 1;
        unsigned int dtcol_tg1 : 12;
        unsigned int dtrow_tg1 : 16;
    } reg;
} SOC_HIPACKPHY_TRAINMADDRTG1_UNION;
#endif
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtbank_tg1_START (0)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtbank_tg1_END (2)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtcol_tg1_START (4)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtcol_tg1_END (15)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtrow_tg1_START (16)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtrow_tg1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_wl : 8;
        unsigned int t_odton_h : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_HIPACKPHY_DRAMTIMER5_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER5_t_wl_START (0)
#define SOC_HIPACKPHY_DRAMTIMER5_t_wl_END (7)
#define SOC_HIPACKPHY_DRAMTIMER5_t_odton_h_START (8)
#define SOC_HIPACKPHY_DRAMTIMER5_t_odton_h_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vreft_bist_runtime : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_HIPACKPHY_VREFTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_VREFTCTRL_vreft_bist_runtime_START (0)
#define SOC_HIPACKPHY_VREFTCTRL_vreft_bist_runtime_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dvreft_maxv : 6;
        unsigned int dvreft_minv : 6;
        unsigned int dvreft_step : 6;
        unsigned int dvreft_hckpts : 4;
        unsigned int reserved : 9;
        unsigned int pdaen : 1;
    } reg;
} SOC_HIPACKPHY_DVRFTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_maxv_START (0)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_maxv_END (5)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_minv_START (6)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_minv_END (11)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_step_START (12)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_step_END (17)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_hckpts_START (18)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_hckpts_END (21)
#define SOC_HIPACKPHY_DVRFTCTRL_pdaen_START (31)
#define SOC_HIPACKPHY_DVRFTCTRL_pdaen_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hvreft_maxv : 6;
        unsigned int hvreft_minv : 6;
        unsigned int hvreft_step : 6;
        unsigned int hvreft_hckpts : 6;
        unsigned int reserved : 8;
    } reg;
} SOC_HIPACKPHY_HVRFTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_maxv_START (0)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_maxv_END (5)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_minv_START (6)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_minv_END (11)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_step_START (12)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_step_END (17)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_hckpts_START (18)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_hckpts_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdet_samp_num : 4;
        unsigned int wdet_trysamp_num : 4;
        unsigned int cfg_fast_rdet_cnt : 3;
        unsigned int wdet_ct_dqs_en : 1;
        unsigned int wrdet_av_en : 1;
        unsigned int wdet_rbs_en : 1;
        unsigned int wdet_ds_en : 1;
        unsigned int wdet_lbs_en : 1;
        unsigned int rdet_samp_num : 4;
        unsigned int rdet_trysamp_num : 4;
        unsigned int cfg_comp_en : 1;
        unsigned int fast_rdet_en : 1;
        unsigned int rdet_dq_evenodd_en : 1;
        unsigned int rdet_ct_dqs_en : 1;
        unsigned int rdet_av_en : 1;
        unsigned int rdet_rbs_en : 1;
        unsigned int rdet_ds_en : 1;
        unsigned int rdet_lbs_en : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_samp_num_START (0)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_samp_num_END (3)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_trysamp_num_START (4)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_trysamp_num_END (7)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_fast_rdet_cnt_START (8)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_fast_rdet_cnt_END (10)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ct_dqs_en_START (11)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ct_dqs_en_END (11)
#define SOC_HIPACKPHY_TRAINCTRL1_wrdet_av_en_START (12)
#define SOC_HIPACKPHY_TRAINCTRL1_wrdet_av_en_END (12)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_rbs_en_START (13)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_rbs_en_END (13)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ds_en_START (14)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ds_en_END (14)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_lbs_en_START (15)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_lbs_en_END (15)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_samp_num_START (16)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_samp_num_END (19)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_trysamp_num_START (20)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_trysamp_num_END (23)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_comp_en_START (24)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_comp_en_END (24)
#define SOC_HIPACKPHY_TRAINCTRL1_fast_rdet_en_START (25)
#define SOC_HIPACKPHY_TRAINCTRL1_fast_rdet_en_END (25)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_dq_evenodd_en_START (26)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_dq_evenodd_en_END (26)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ct_dqs_en_START (27)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ct_dqs_en_END (27)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_av_en_START (28)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_av_en_END (28)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_rbs_en_START (29)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_rbs_en_END (29)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ds_en_START (30)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ds_en_END (30)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_lbs_en_START (31)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_lbs_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mrr_pat_a : 8;
        unsigned int mrr_pat_b : 8;
        unsigned int mrr_pat_mask : 8;
        unsigned int gds_automrg_en : 1;
        unsigned int fast_gt_en : 1;
        unsigned int fast_gdst_en : 1;
        unsigned int mrr_bl4 : 1;
        unsigned int mrr_pat_order : 3;
        unsigned int rdet_method_sel : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_a_START (0)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_a_END (7)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_b_START (8)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_b_END (15)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_mask_START (16)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_mask_END (23)
#define SOC_HIPACKPHY_TRAINCTRL2_gds_automrg_en_START (24)
#define SOC_HIPACKPHY_TRAINCTRL2_gds_automrg_en_END (24)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gt_en_START (25)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gt_en_END (25)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gdst_en_START (26)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gdst_en_END (26)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_bl4_START (27)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_bl4_END (27)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_order_START (28)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_order_END (30)
#define SOC_HIPACKPHY_TRAINCTRL2_rdet_method_sel_START (31)
#define SOC_HIPACKPHY_TRAINCTRL2_rdet_method_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_sel : 1;
        unsigned int op_sel : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_HIPACKPHY_REGBANKCTRL_UNION;
#endif
#define SOC_HIPACKPHY_REGBANKCTRL_wr_sel_START (0)
#define SOC_HIPACKPHY_REGBANKCTRL_wr_sel_END (0)
#define SOC_HIPACKPHY_REGBANKCTRL_op_sel_START (1)
#define SOC_HIPACKPHY_REGBANKCTRL_op_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rpat_cnt_num : 4;
        unsigned int wpat_cnt_num : 4;
        unsigned int rpat_cnt_num_open : 4;
        unsigned int wderten : 1;
        unsigned int wdet_rank_en : 1;
        unsigned int wrenrkswen : 1;
        unsigned int nopre4wrdet : 1;
        unsigned int gdsrt_backtap : 3;
        unsigned int rdet_rank_en : 1;
        unsigned int rdet_dbi_en : 1;
        unsigned int cat_pat_toggle_en : 1;
        unsigned int rpt_mode_en : 1;
        unsigned int wdet_method_sel : 1;
        unsigned int fast_gt_cnt : 5;
        unsigned int phaseradix3en : 1;
        unsigned int rdet_fcomp_en : 1;
        unsigned int exd_gtres_en : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL3_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_START (0)
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_END (3)
#define SOC_HIPACKPHY_TRAINCTRL3_wpat_cnt_num_START (4)
#define SOC_HIPACKPHY_TRAINCTRL3_wpat_cnt_num_END (7)
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_open_START (8)
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_open_END (11)
#define SOC_HIPACKPHY_TRAINCTRL3_wderten_START (12)
#define SOC_HIPACKPHY_TRAINCTRL3_wderten_END (12)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_rank_en_START (13)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_rank_en_END (13)
#define SOC_HIPACKPHY_TRAINCTRL3_wrenrkswen_START (14)
#define SOC_HIPACKPHY_TRAINCTRL3_wrenrkswen_END (14)
#define SOC_HIPACKPHY_TRAINCTRL3_nopre4wrdet_START (15)
#define SOC_HIPACKPHY_TRAINCTRL3_nopre4wrdet_END (15)
#define SOC_HIPACKPHY_TRAINCTRL3_gdsrt_backtap_START (16)
#define SOC_HIPACKPHY_TRAINCTRL3_gdsrt_backtap_END (18)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_rank_en_START (19)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_rank_en_END (19)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_dbi_en_START (20)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_dbi_en_END (20)
#define SOC_HIPACKPHY_TRAINCTRL3_cat_pat_toggle_en_START (21)
#define SOC_HIPACKPHY_TRAINCTRL3_cat_pat_toggle_en_END (21)
#define SOC_HIPACKPHY_TRAINCTRL3_rpt_mode_en_START (22)
#define SOC_HIPACKPHY_TRAINCTRL3_rpt_mode_en_END (22)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_method_sel_START (23)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_method_sel_END (23)
#define SOC_HIPACKPHY_TRAINCTRL3_fast_gt_cnt_START (24)
#define SOC_HIPACKPHY_TRAINCTRL3_fast_gt_cnt_END (28)
#define SOC_HIPACKPHY_TRAINCTRL3_phaseradix3en_START (29)
#define SOC_HIPACKPHY_TRAINCTRL3_phaseradix3en_END (29)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_fcomp_en_START (30)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_fcomp_en_END (30)
#define SOC_HIPACKPHY_TRAINCTRL3_exd_gtres_en_START (31)
#define SOC_HIPACKPHY_TRAINCTRL3_exd_gtres_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mr4 : 16;
        unsigned int mr5 : 16;
    } reg;
} SOC_HIPACKPHY_MODEREG45_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG45_mr4_START (0)
#define SOC_HIPACKPHY_MODEREG45_mr4_END (15)
#define SOC_HIPACKPHY_MODEREG45_mr5_START (16)
#define SOC_HIPACKPHY_MODEREG45_mr5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mr6 : 16;
        unsigned int mr7 : 16;
    } reg;
} SOC_HIPACKPHY_MODEREG67_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG67_mr6_START (0)
#define SOC_HIPACKPHY_MODEREG67_mr6_END (15)
#define SOC_HIPACKPHY_MODEREG67_mr7_START (16)
#define SOC_HIPACKPHY_MODEREG67_mr7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyupdtimer : 16;
        unsigned int cfg_reg_sync_cnt : 4;
        unsigned int cat_re_deskew_en : 1;
        unsigned int det_re_deskew_en : 1;
        unsigned int half_ph_bdl_en : 1;
        unsigned int bdlcarry_done : 1;
        unsigned int row_react_period : 8;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL6_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL6_phyupdtimer_START (0)
#define SOC_HIPACKPHY_TRAINCTRL6_phyupdtimer_END (15)
#define SOC_HIPACKPHY_TRAINCTRL6_cfg_reg_sync_cnt_START (16)
#define SOC_HIPACKPHY_TRAINCTRL6_cfg_reg_sync_cnt_END (19)
#define SOC_HIPACKPHY_TRAINCTRL6_cat_re_deskew_en_START (20)
#define SOC_HIPACKPHY_TRAINCTRL6_cat_re_deskew_en_END (20)
#define SOC_HIPACKPHY_TRAINCTRL6_det_re_deskew_en_START (21)
#define SOC_HIPACKPHY_TRAINCTRL6_det_re_deskew_en_END (21)
#define SOC_HIPACKPHY_TRAINCTRL6_half_ph_bdl_en_START (22)
#define SOC_HIPACKPHY_TRAINCTRL6_half_ph_bdl_en_END (22)
#define SOC_HIPACKPHY_TRAINCTRL6_bdlcarry_done_START (23)
#define SOC_HIPACKPHY_TRAINCTRL6_bdlcarry_done_END (23)
#define SOC_HIPACKPHY_TRAINCTRL6_row_react_period_START (24)
#define SOC_HIPACKPHY_TRAINCTRL6_row_react_period_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int det_pat_index : 4;
        unsigned int reserved_0 : 4;
        unsigned int det_pat_dir : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_HIPACKPHY_DETPATINDEX_UNION;
#endif
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_index_START (0)
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_index_END (3)
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_dir_START (8)
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_dir_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dx_pll_bp_refpfd : 2;
        unsigned int dx_pll_bp_refvco : 2;
        unsigned int dx_pll_enphsel : 2;
        unsigned int dx_pll_en_cal : 2;
        unsigned int dx_pll_initsel : 2;
        unsigned int dx_pll_lockt_sel : 2;
        unsigned int dx_pll_fopetestfb : 2;
        unsigned int dx_pll_fopetestref : 2;
        unsigned int dx_pll_lockin : 2;
        unsigned int dx_pll_outn : 2;
        unsigned int dx_pll_outp : 2;
        unsigned int reserved : 10;
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX2_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refpfd_START (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refpfd_END (1)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refvco_START (2)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refvco_END (3)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_enphsel_START (4)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_enphsel_END (5)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_en_cal_START (6)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_en_cal_END (7)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_initsel_START (8)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_initsel_END (9)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockt_sel_START (10)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockt_sel_END (11)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestfb_START (12)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestfb_END (13)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestref_START (14)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestref_END (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockin_START (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockin_END (17)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outn_START (18)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outn_END (19)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outp_START (20)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outp_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phazmeter_1 : 16;
        unsigned int phazmeter_st_1 : 16;
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX3_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_1_START (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_1_END (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_st_1_START (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_st_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phazmeter_2 : 16;
        unsigned int phazmeter_st_2 : 16;
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX4_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_2_START (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_2_END (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_st_2_START (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_st_2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phazmeter_3 : 16;
        unsigned int phazmeter_st_3 : 16;
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX5_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_3_START (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_3_END (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_st_3_START (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_st_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_cmp_mask : 16;
        unsigned int ba_cmp_mask : 3;
        unsigned int we_cmp_mask : 1;
        unsigned int cas_cmp_mask : 1;
        unsigned int ras_cmp_mask : 1;
        unsigned int cs_cmp_mask : 4;
        unsigned int rst_cmp_mask : 1;
        unsigned int acbist_en : 1;
        unsigned int aclpbk_tg : 1;
        unsigned int ac_rdffsel : 3;
    } reg;
} SOC_HIPACKPHY_ACBISTCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTCTRL0_addr_cmp_mask_START (0)
#define SOC_HIPACKPHY_ACBISTCTRL0_addr_cmp_mask_END (15)
#define SOC_HIPACKPHY_ACBISTCTRL0_ba_cmp_mask_START (16)
#define SOC_HIPACKPHY_ACBISTCTRL0_ba_cmp_mask_END (18)
#define SOC_HIPACKPHY_ACBISTCTRL0_we_cmp_mask_START (19)
#define SOC_HIPACKPHY_ACBISTCTRL0_we_cmp_mask_END (19)
#define SOC_HIPACKPHY_ACBISTCTRL0_cas_cmp_mask_START (20)
#define SOC_HIPACKPHY_ACBISTCTRL0_cas_cmp_mask_END (20)
#define SOC_HIPACKPHY_ACBISTCTRL0_ras_cmp_mask_START (21)
#define SOC_HIPACKPHY_ACBISTCTRL0_ras_cmp_mask_END (21)
#define SOC_HIPACKPHY_ACBISTCTRL0_cs_cmp_mask_START (22)
#define SOC_HIPACKPHY_ACBISTCTRL0_cs_cmp_mask_END (25)
#define SOC_HIPACKPHY_ACBISTCTRL0_rst_cmp_mask_START (26)
#define SOC_HIPACKPHY_ACBISTCTRL0_rst_cmp_mask_END (26)
#define SOC_HIPACKPHY_ACBISTCTRL0_acbist_en_START (27)
#define SOC_HIPACKPHY_ACBISTCTRL0_acbist_en_END (27)
#define SOC_HIPACKPHY_ACBISTCTRL0_aclpbk_tg_START (28)
#define SOC_HIPACKPHY_ACBISTCTRL0_aclpbk_tg_END (28)
#define SOC_HIPACKPHY_ACBISTCTRL0_ac_rdffsel_START (29)
#define SOC_HIPACKPHY_ACBISTCTRL0_ac_rdffsel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odt_cmp_mask : 4;
        unsigned int cke_cmp_mask : 4;
        unsigned int ac_lfsr_seed : 8;
        unsigned int par_cmp_mask : 1;
        unsigned int bg1_cmp_mask : 1;
        unsigned int act_cmp_mask : 1;
        unsigned int prbs_mode : 1;
        unsigned int addro_fp : 1;
        unsigned int reserved : 11;
    } reg;
} SOC_HIPACKPHY_ACBISTCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTCTRL1_odt_cmp_mask_START (0)
#define SOC_HIPACKPHY_ACBISTCTRL1_odt_cmp_mask_END (3)
#define SOC_HIPACKPHY_ACBISTCTRL1_cke_cmp_mask_START (4)
#define SOC_HIPACKPHY_ACBISTCTRL1_cke_cmp_mask_END (7)
#define SOC_HIPACKPHY_ACBISTCTRL1_ac_lfsr_seed_START (8)
#define SOC_HIPACKPHY_ACBISTCTRL1_ac_lfsr_seed_END (15)
#define SOC_HIPACKPHY_ACBISTCTRL1_par_cmp_mask_START (16)
#define SOC_HIPACKPHY_ACBISTCTRL1_par_cmp_mask_END (16)
#define SOC_HIPACKPHY_ACBISTCTRL1_bg1_cmp_mask_START (17)
#define SOC_HIPACKPHY_ACBISTCTRL1_bg1_cmp_mask_END (17)
#define SOC_HIPACKPHY_ACBISTCTRL1_act_cmp_mask_START (18)
#define SOC_HIPACKPHY_ACBISTCTRL1_act_cmp_mask_END (18)
#define SOC_HIPACKPHY_ACBISTCTRL1_prbs_mode_START (19)
#define SOC_HIPACKPHY_ACBISTCTRL1_prbs_mode_END (19)
#define SOC_HIPACKPHY_ACBISTCTRL1_addro_fp_START (20)
#define SOC_HIPACKPHY_ACBISTCTRL1_addro_fp_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_bist_err : 16;
        unsigned int ba_bist_err : 3;
        unsigned int we_bist_err : 1;
        unsigned int cas_bist_err : 1;
        unsigned int ras_bist_err : 1;
        unsigned int cs_bist_err : 4;
        unsigned int rst_bist_err : 1;
        unsigned int par_bist_err : 1;
        unsigned int bg1_bist_err : 1;
        unsigned int act_bist_err : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_HIPACKPHY_ACBISTSTS0_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTSTS0_addr_bist_err_START (0)
#define SOC_HIPACKPHY_ACBISTSTS0_addr_bist_err_END (15)
#define SOC_HIPACKPHY_ACBISTSTS0_ba_bist_err_START (16)
#define SOC_HIPACKPHY_ACBISTSTS0_ba_bist_err_END (18)
#define SOC_HIPACKPHY_ACBISTSTS0_we_bist_err_START (19)
#define SOC_HIPACKPHY_ACBISTSTS0_we_bist_err_END (19)
#define SOC_HIPACKPHY_ACBISTSTS0_cas_bist_err_START (20)
#define SOC_HIPACKPHY_ACBISTSTS0_cas_bist_err_END (20)
#define SOC_HIPACKPHY_ACBISTSTS0_ras_bist_err_START (21)
#define SOC_HIPACKPHY_ACBISTSTS0_ras_bist_err_END (21)
#define SOC_HIPACKPHY_ACBISTSTS0_cs_bist_err_START (22)
#define SOC_HIPACKPHY_ACBISTSTS0_cs_bist_err_END (25)
#define SOC_HIPACKPHY_ACBISTSTS0_rst_bist_err_START (26)
#define SOC_HIPACKPHY_ACBISTSTS0_rst_bist_err_END (26)
#define SOC_HIPACKPHY_ACBISTSTS0_par_bist_err_START (27)
#define SOC_HIPACKPHY_ACBISTSTS0_par_bist_err_END (27)
#define SOC_HIPACKPHY_ACBISTSTS0_bg1_bist_err_START (28)
#define SOC_HIPACKPHY_ACBISTSTS0_bg1_bist_err_END (28)
#define SOC_HIPACKPHY_ACBISTSTS0_act_bist_err_START (29)
#define SOC_HIPACKPHY_ACBISTSTS0_act_bist_err_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odt_bist_err : 4;
        unsigned int cke_bist_err : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_HIPACKPHY_ACBISTSTS1_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTSTS1_odt_bist_err_START (0)
#define SOC_HIPACKPHY_ACBISTSTS1_odt_bist_err_END (3)
#define SOC_HIPACKPHY_ACBISTSTS1_cke_bist_err_START (4)
#define SOC_HIPACKPHY_ACBISTSTS1_cke_bist_err_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdqphase_left_bytelane0 : 6;
        unsigned int reserved_0 : 2;
        unsigned int wdqphase_left_bytelane1 : 6;
        unsigned int reserved_1 : 2;
        unsigned int wdq0bdl_left_bytelane0 : 7;
        unsigned int wdet_err : 1;
        unsigned int wdq0bdl_left_bytelane1 : 7;
        unsigned int init_en : 1;
    } reg;
} SOC_HIPACKPHY_WDXBOUND_DFS_UNION;
#endif
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane0_START (0)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane0_END (5)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane1_START (8)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane1_END (13)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane0_START (16)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane0_END (22)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdet_err_START (23)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdet_err_END (23)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane1_START (24)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane1_END (30)
#define SOC_HIPACKPHY_WDXBOUND_DFS_init_en_START (31)
#define SOC_HIPACKPHY_WDXBOUND_DFS_init_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdet_lb_backtap : 4;
        unsigned int wdet_rb_backtap : 4;
        unsigned int wdert_shift_step : 3;
        unsigned int rdert_bdl_mode : 1;
        unsigned int rdet_lb_backtap : 4;
        unsigned int rdet_rb_backtap : 9;
        unsigned int fast_comp_step : 2;
        unsigned int fast_shift_step : 2;
        unsigned int fast_check_step : 2;
        unsigned int rdet_dq_rank_en : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL4_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_lb_backtap_START (0)
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_lb_backtap_END (3)
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_rb_backtap_START (4)
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_rb_backtap_END (7)
#define SOC_HIPACKPHY_TRAINCTRL4_wdert_shift_step_START (8)
#define SOC_HIPACKPHY_TRAINCTRL4_wdert_shift_step_END (10)
#define SOC_HIPACKPHY_TRAINCTRL4_rdert_bdl_mode_START (11)
#define SOC_HIPACKPHY_TRAINCTRL4_rdert_bdl_mode_END (11)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_lb_backtap_START (12)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_lb_backtap_END (15)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_rb_backtap_START (16)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_rb_backtap_END (24)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_comp_step_START (25)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_comp_step_END (26)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_shift_step_START (27)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_shift_step_END (28)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_check_step_START (29)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_check_step_END (30)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_dq_rank_en_START (31)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_dq_rank_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdet_bdl_step : 2;
        unsigned int wdet_ph_step : 2;
        unsigned int rdet_bdl_step : 2;
        unsigned int rdet_ph_step : 2;
        unsigned int rdet_open_jstep : 4;
        unsigned int gt_bdl_step : 4;
        unsigned int gt_ph_step : 2;
        unsigned int wldqsen : 1;
        unsigned int trainctl_nopostpre : 1;
        unsigned int wl_bdl_step : 2;
        unsigned int wl_ph_step : 2;
        unsigned int cat_bdl_step : 2;
        unsigned int cat_ph_step : 2;
        unsigned int wdert_check_step : 3;
        unsigned int wdert_bdl_mode : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL5_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_bdl_step_START (0)
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_bdl_step_END (1)
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_ph_step_START (2)
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_ph_step_END (3)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_bdl_step_START (4)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_bdl_step_END (5)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_ph_step_START (6)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_ph_step_END (7)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_open_jstep_START (8)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_open_jstep_END (11)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_bdl_step_START (12)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_bdl_step_END (15)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_ph_step_START (16)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_ph_step_END (17)
#define SOC_HIPACKPHY_TRAINCTRL5_wldqsen_START (18)
#define SOC_HIPACKPHY_TRAINCTRL5_wldqsen_END (18)
#define SOC_HIPACKPHY_TRAINCTRL5_trainctl_nopostpre_START (19)
#define SOC_HIPACKPHY_TRAINCTRL5_trainctl_nopostpre_END (19)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_bdl_step_START (20)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_bdl_step_END (21)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_ph_step_START (22)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_ph_step_END (23)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_bdl_step_START (24)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_bdl_step_END (25)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_ph_step_START (26)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_ph_step_END (27)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_check_step_START (28)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_check_step_END (30)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_bdl_mode_START (31)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_bdl_mode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mr0_cl_m2 : 4;
        unsigned int dlymeas_upd_rdqsbdl_en : 1;
        unsigned int wlsyncrank_en : 1;
        unsigned int gt_rdbi_handle_en : 1;
        unsigned int gdsrt_mrank_en : 1;
        unsigned int cfg_rl_rdbi_off : 4;
        unsigned int fast_dqsgsl_mrgn : 6;
        unsigned int reserved_0 : 2;
        unsigned int wdet_open_bdl_jstep : 4;
        unsigned int wdet_open_ph_jstep : 4;
        unsigned int reserved_1 : 1;
        unsigned int trainctl_gtrnowait : 1;
        unsigned int rpt_nomrs : 1;
        unsigned int info_full_tccd_sel : 1;
    } reg;
} SOC_HIPACKPHY_TRAINCTRL7_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL7_mr0_cl_m2_START (0)
#define SOC_HIPACKPHY_TRAINCTRL7_mr0_cl_m2_END (3)
#define SOC_HIPACKPHY_TRAINCTRL7_dlymeas_upd_rdqsbdl_en_START (4)
#define SOC_HIPACKPHY_TRAINCTRL7_dlymeas_upd_rdqsbdl_en_END (4)
#define SOC_HIPACKPHY_TRAINCTRL7_wlsyncrank_en_START (5)
#define SOC_HIPACKPHY_TRAINCTRL7_wlsyncrank_en_END (5)
#define SOC_HIPACKPHY_TRAINCTRL7_gt_rdbi_handle_en_START (6)
#define SOC_HIPACKPHY_TRAINCTRL7_gt_rdbi_handle_en_END (6)
#define SOC_HIPACKPHY_TRAINCTRL7_gdsrt_mrank_en_START (7)
#define SOC_HIPACKPHY_TRAINCTRL7_gdsrt_mrank_en_END (7)
#define SOC_HIPACKPHY_TRAINCTRL7_cfg_rl_rdbi_off_START (8)
#define SOC_HIPACKPHY_TRAINCTRL7_cfg_rl_rdbi_off_END (11)
#define SOC_HIPACKPHY_TRAINCTRL7_fast_dqsgsl_mrgn_START (12)
#define SOC_HIPACKPHY_TRAINCTRL7_fast_dqsgsl_mrgn_END (17)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_bdl_jstep_START (20)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_bdl_jstep_END (23)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_ph_jstep_START (24)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_ph_jstep_END (27)
#define SOC_HIPACKPHY_TRAINCTRL7_trainctl_gtrnowait_START (29)
#define SOC_HIPACKPHY_TRAINCTRL7_trainctl_gtrnowait_END (29)
#define SOC_HIPACKPHY_TRAINCTRL7_rpt_nomrs_START (30)
#define SOC_HIPACKPHY_TRAINCTRL7_rpt_nomrs_END (30)
#define SOC_HIPACKPHY_TRAINCTRL7_info_full_tccd_sel_START (31)
#define SOC_HIPACKPHY_TRAINCTRL7_info_full_tccd_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odt0_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int odt1_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL0_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL0_odt0_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL0_odt0_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL0_odt1_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL0_odt1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odt2_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int odt3_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL1_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL1_odt2_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL1_odt2_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL1_odt3_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL1_odt3_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cs0_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int cs1_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL2_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL2_cs0_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL2_cs0_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL2_cs1_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL2_cs1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cs2_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int cs3_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL3_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL3_cs2_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL3_cs2_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL3_cs3_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL3_cs3_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cke0_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int cke1_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL4_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL4_cke0_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL4_cke0_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL4_cke1_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL4_cke1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cke2_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int cke3_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL5_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL5_cke2_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL5_cke2_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL5_cke3_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL5_cke3_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int we_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int cas_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL6_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL6_we_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL6_we_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL6_cas_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL6_cas_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ras_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int resetn_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL7_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL7_ras_bdl_START (0)
#define SOC_HIPACKPHY_ACCMDBDL7_ras_bdl_END (6)
#define SOC_HIPACKPHY_ACCMDBDL7_resetn_bdl_START (16)
#define SOC_HIPACKPHY_ACCMDBDL7_resetn_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr0_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int addr1_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL0_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL0_addr0_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL0_addr0_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL0_addr1_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL0_addr1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr2_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int addr3_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL1_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL1_addr2_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL1_addr2_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL1_addr3_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL1_addr3_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr4_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int addr5_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL2_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL2_addr4_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL2_addr4_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL2_addr5_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL2_addr5_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr6_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int addr7_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL3_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL3_addr6_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL3_addr6_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL3_addr7_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL3_addr7_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr8_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int addr9_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL4_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL4_addr8_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL4_addr8_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL4_addr9_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL4_addr9_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr10_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int addr11_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL5_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL5_addr10_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL5_addr10_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL5_addr11_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL5_addr11_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr12_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int addr13_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL6_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL6_addr12_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL6_addr12_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL6_addr13_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL6_addr13_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr14_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int addr15_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL7_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL7_addr14_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL7_addr14_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL7_addr15_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL7_addr15_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ba0_bdl : 7;
        unsigned int reserved_0: 9;
        unsigned int ba1_bdl : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL8_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL8_ba0_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL8_ba0_bdl_END (6)
#define SOC_HIPACKPHY_ACADDRBDL8_ba1_bdl_START (16)
#define SOC_HIPACKPHY_ACADDRBDL8_ba1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ba2_bdl : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_HIPACKPHY_ACADDRBDL9_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL9_ba2_bdl_START (0)
#define SOC_HIPACKPHY_ACADDRBDL9_ba2_bdl_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dramclk0_bdl : 7;
        unsigned int reserved_0 : 1;
        unsigned int dramclk1_bdl : 7;
        unsigned int reserved_1 : 1;
        unsigned int refclk_bdl : 5;
        unsigned int reserved_2 : 3;
        unsigned int fbclk_bdl : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_HIPACKPHY_ACCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_ACCLKBDL_dramclk0_bdl_START (0)
#define SOC_HIPACKPHY_ACCLKBDL_dramclk0_bdl_END (6)
#define SOC_HIPACKPHY_ACCLKBDL_dramclk1_bdl_START (8)
#define SOC_HIPACKPHY_ACCLKBDL_dramclk1_bdl_END (14)
#define SOC_HIPACKPHY_ACCLKBDL_refclk_bdl_START (16)
#define SOC_HIPACKPHY_ACCLKBDL_refclk_bdl_END (20)
#define SOC_HIPACKPHY_ACCLKBDL_fbclk_bdl_START (24)
#define SOC_HIPACKPHY_ACCLKBDL_fbclk_bdl_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enshift_a0 : 1;
        unsigned int margin_a0 : 1;
        unsigned int margin_a1 : 1;
        unsigned int dramclk_h : 1;
        unsigned int dramclk_l : 1;
        unsigned int lvdqclkdiv2 : 1;
        unsigned int bufphyclk_div2 : 1;
        unsigned int ac_byp_clk_gated_dis : 1;
        unsigned int ac_byp_ck90_cmd_code : 9;
        unsigned int reserved : 15;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL0_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL0_enshift_a0_START (0)
#define SOC_HIPACKPHY_ACPHYCTL0_enshift_a0_END (0)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a0_START (1)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a0_END (1)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a1_START (2)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a1_END (2)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_h_START (3)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_h_END (3)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_l_START (4)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_l_END (4)
#define SOC_HIPACKPHY_ACPHYCTL0_lvdqclkdiv2_START (5)
#define SOC_HIPACKPHY_ACPHYCTL0_lvdqclkdiv2_END (5)
#define SOC_HIPACKPHY_ACPHYCTL0_bufphyclk_div2_START (6)
#define SOC_HIPACKPHY_ACPHYCTL0_bufphyclk_div2_END (6)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_clk_gated_dis_START (7)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_clk_gated_dis_END (7)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_ck90_cmd_code_START (8)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_ck90_cmd_code_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dram1sel_reset : 1;
        unsigned int dram1sel_cs : 1;
        unsigned int dram1sel_cke : 1;
        unsigned int dram1sel_odt : 1;
        unsigned int dram1sel_ras : 1;
        unsigned int dram1sel_cas : 1;
        unsigned int dram1sel_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int dram1sel_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int dram1sel_addr : 16;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL1_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_reset_START (0)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_reset_END (0)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cs_START (1)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cs_END (1)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cke_START (2)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cke_END (2)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_odt_START (3)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_odt_END (3)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ras_START (4)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ras_END (4)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cas_START (5)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cas_END (5)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_we_START (6)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_we_END (6)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ba_START (8)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ba_END (10)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_addr_START (16)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sdrsel_reset : 1;
        unsigned int sdrsel_cs : 1;
        unsigned int sdrsel_cke : 1;
        unsigned int sdrsel_odt : 1;
        unsigned int sdrsel_ras : 1;
        unsigned int sdrsel_cas : 1;
        unsigned int sdrsel_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int sdrsel_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int sdrsel_addr : 16;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL2_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_reset_START (0)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_reset_END (0)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cs_START (1)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cs_END (1)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cke_START (2)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cke_END (2)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_odt_START (3)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_odt_END (3)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ras_START (4)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ras_END (4)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cas_START (5)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cas_END (5)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_we_START (6)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_we_END (6)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ba_START (8)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ba_END (10)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_addr_START (16)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int posedge_reset : 1;
        unsigned int posedge_cs : 1;
        unsigned int posedge_cke : 1;
        unsigned int posedge_odt : 1;
        unsigned int posedge_ras : 1;
        unsigned int posedge_cas : 1;
        unsigned int posedge_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int posedge_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int posedge_addr : 16;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL3_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_reset_START (0)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_reset_END (0)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cs_START (1)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cs_END (1)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cke_START (2)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cke_END (2)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_odt_START (3)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_odt_END (3)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ras_START (4)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ras_END (4)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cas_START (5)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cas_END (5)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_we_START (6)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_we_END (6)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ba_START (8)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ba_END (10)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_addr_START (16)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timing2t_reset : 1;
        unsigned int timing2t_cs : 1;
        unsigned int timing2t_cke : 1;
        unsigned int timing2t_odt : 1;
        unsigned int timing2t_ras : 1;
        unsigned int timing2t_cas : 1;
        unsigned int timing2t_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int timing2t_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int timing2t_addr : 16;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL4_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_reset_START (0)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_reset_END (0)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cs_START (1)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cs_END (1)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cke_START (2)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cke_END (2)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_odt_START (3)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_odt_END (3)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ras_START (4)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ras_END (4)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cas_START (5)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cas_END (5)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_we_START (6)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_we_END (6)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ba_START (8)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ba_END (10)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_addr_START (16)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk1x_dramclk0 : 4;
        unsigned int clk1x_dramclk1 : 4;
        unsigned int clk1x_cmd2t_ctl : 4;
        unsigned int clk1x_cmd2t : 4;
        unsigned int clk1x_cmd1t : 4;
        unsigned int clk1x_mclk : 4;
        unsigned int clk1x_cmd2t_ctl2 : 4;
        unsigned int reserved : 4;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL5_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk0_START (0)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk0_END (3)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk1_START (4)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk1_END (7)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl_START (8)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl_END (11)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_START (12)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_END (15)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd1t_START (16)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd1t_END (19)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_mclk_START (20)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_mclk_END (23)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl2_START (24)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl2_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk2x_dramclk0 : 4;
        unsigned int clk2x_dramclk1 : 4;
        unsigned int clk2x_cmd2t_ctl : 4;
        unsigned int clk2x_cmd2t : 4;
        unsigned int clk2x_cmd1t : 4;
        unsigned int clk2x_mclk : 4;
        unsigned int clk2x_cmd2t_ctl2 : 4;
        unsigned int reserved : 4;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL6_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk0_START (0)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk0_END (3)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk1_START (4)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk1_END (7)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl_START (8)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl_END (11)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_START (12)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_END (15)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd1t_START (16)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd1t_END (19)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_mclk_START (20)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_mclk_END (23)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl2_START (24)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl2_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ckd2_mclk : 3;
        unsigned int ck0p_mclk : 3;
        unsigned int ck1p_dclk0 : 3;
        unsigned int ck2p_dclk1 : 3;
        unsigned int ck3p_cmd1t : 3;
        unsigned int reserved_0 : 3;
        unsigned int ck5p_cmd2tc : 3;
        unsigned int halft_cmd2tctl : 1;
        unsigned int reserved_1 : 1;
        unsigned int halft_cmd1t : 1;
        unsigned int halft_dramclk1 : 1;
        unsigned int halft_dramclk0 : 1;
        unsigned int halft_cmd2tctl2 : 1;
        unsigned int reserved_2 : 5;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL7_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL7_ckd2_mclk_START (0)
#define SOC_HIPACKPHY_ACPHYCTL7_ckd2_mclk_END (2)
#define SOC_HIPACKPHY_ACPHYCTL7_ck0p_mclk_START (3)
#define SOC_HIPACKPHY_ACPHYCTL7_ck0p_mclk_END (5)
#define SOC_HIPACKPHY_ACPHYCTL7_ck1p_dclk0_START (6)
#define SOC_HIPACKPHY_ACPHYCTL7_ck1p_dclk0_END (8)
#define SOC_HIPACKPHY_ACPHYCTL7_ck2p_dclk1_START (9)
#define SOC_HIPACKPHY_ACPHYCTL7_ck2p_dclk1_END (11)
#define SOC_HIPACKPHY_ACPHYCTL7_ck3p_cmd1t_START (12)
#define SOC_HIPACKPHY_ACPHYCTL7_ck3p_cmd1t_END (14)
#define SOC_HIPACKPHY_ACPHYCTL7_ck5p_cmd2tc_START (18)
#define SOC_HIPACKPHY_ACPHYCTL7_ck5p_cmd2tc_END (20)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl_START (21)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl_END (21)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd1t_START (23)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd1t_END (23)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk1_START (24)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk1_END (24)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk0_START (25)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk0_END (25)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl2_START (26)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl2_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_rdcnt : 3;
        unsigned int reserved_0 : 5;
        unsigned int deskew_regread : 1;
        unsigned int reserved_1 : 7;
        unsigned int acdbg_config : 4;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_HIPACKPHY_ACDEBUG_UNION;
#endif
#define SOC_HIPACKPHY_ACDEBUG_ac_rdcnt_START (0)
#define SOC_HIPACKPHY_ACDEBUG_ac_rdcnt_END (2)
#define SOC_HIPACKPHY_ACDEBUG_deskew_regread_START (8)
#define SOC_HIPACKPHY_ACDEBUG_deskew_regread_END (8)
#define SOC_HIPACKPHY_ACDEBUG_acdbg_config_START (16)
#define SOC_HIPACKPHY_ACDEBUG_acdbg_config_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_rsv_control : 32;
    } reg;
} SOC_HIPACKPHY_ACPHYRSVDC_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYRSVDC_ac_rsv_control_START (0)
#define SOC_HIPACKPHY_ACPHYRSVDC_ac_rsv_control_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_rsv_status : 32;
    } reg;
} SOC_HIPACKPHY_ACPHYRSVDS_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYRSVDS_ac_rsv_status_START (0)
#define SOC_HIPACKPHY_ACPHYRSVDS_ac_rsv_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_ck6p_reserve : 3;
        unsigned int ac_ck7p_reserve : 3;
        unsigned int ac_ck8p_reserve : 3;
        unsigned int ac_ck9p_reserve : 3;
        unsigned int ac_ck10p_reserve : 3;
        unsigned int ac_ck11p_reserve : 3;
        unsigned int ac_ck12p_reserve : 3;
        unsigned int reserved : 11;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL8_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck6p_reserve_START (0)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck6p_reserve_END (2)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck7p_reserve_START (3)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck7p_reserve_END (5)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck8p_reserve_START (6)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck8p_reserve_END (8)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck9p_reserve_START (9)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck9p_reserve_END (11)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck10p_reserve_START (12)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck10p_reserve_END (14)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck11p_reserve_START (15)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck11p_reserve_END (17)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck12p_reserve_START (18)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck12p_reserve_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odt1_bdl0 : 7;
        unsigned int reserved_0: 9;
        unsigned int odt1_bdl1 : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL8_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl0_START (0)
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl0_END (6)
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl1_START (16)
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl1_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odt1_bdl2 : 7;
        unsigned int reserved_0: 9;
        unsigned int odt1_bdl3 : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL9_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl2_START (0)
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl2_END (6)
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl3_START (16)
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl3_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cs1_bdl0 : 7;
        unsigned int reserved_0: 9;
        unsigned int cs1_bdl1 : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL10_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl0_START (0)
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl0_END (6)
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl1_START (16)
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl1_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cs1_bdl2 : 7;
        unsigned int reserved_0: 9;
        unsigned int cs1_bdl3 : 7;
        unsigned int reserved_1: 9;
    } reg;
} SOC_HIPACKPHY_ACCMDBDL11_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl2_START (0)
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl2_END (6)
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl3_START (16)
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl3_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acdcc_dq1 : 3;
        unsigned int acdcc_dq0 : 3;
        unsigned int acdcc_dqs1 : 3;
        unsigned int acdcc_dqs0 : 3;
        unsigned int acdcc_mclk : 3;
        unsigned int reserved_0 : 1;
        unsigned int acdcc_dq1_byt1 : 3;
        unsigned int acdcc_dq0_byt1 : 3;
        unsigned int acdcc_dqs1_byt1 : 3;
        unsigned int acdcc_dqs0_byt1 : 3;
        unsigned int acdcc_mclk_byt1 : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_ACPHYDCC_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_START (0)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_END (2)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_START (3)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_END (5)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_START (6)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_END (8)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_START (9)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_END (11)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_START (12)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_END (14)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_byt1_START (16)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_byt1_END (18)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_byt1_START (19)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_byt1_END (21)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_byt1_START (22)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_byt1_END (24)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_byt1_START (25)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_byt1_END (27)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_byt1_START (28)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_byt1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acsdrsel_cs1 : 1;
        unsigned int acsdrsel_cke1 : 1;
        unsigned int acsdrsel_odt1 : 1;
        unsigned int acposedge_cs1 : 1;
        unsigned int acposedge_cke1 : 1;
        unsigned int acposedge_odt1 : 1;
        unsigned int acdram1sel_cs1 : 1;
        unsigned int acdram1sel_cke1 : 1;
        unsigned int acdram1sel_odt1 : 1;
        unsigned int actiming2t_cs1 : 1;
        unsigned int actiming2t_cke1 : 1;
        unsigned int actiming2t_odt1 : 1;
        unsigned int reserved : 20;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL9_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cs1_START (0)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cs1_END (0)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cke1_START (1)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cke1_END (1)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_odt1_START (2)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_odt1_END (2)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cs1_START (3)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cs1_END (3)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cke1_START (4)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cke1_END (4)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_odt1_START (5)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_odt1_END (5)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cs1_START (6)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cs1_END (6)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cke1_START (7)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cke1_END (7)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_odt1_START (8)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_odt1_END (8)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cs1_START (9)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cs1_END (9)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cke1_START (10)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cke1_END (10)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_odt1_START (11)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_odt1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cat_swap_index : 4;
        unsigned int reserved : 27;
        unsigned int cat_swap_legacy : 1;
    } reg;
} SOC_HIPACKPHY_CATSWAPINDEX_UNION;
#endif
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_index_START (0)
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_index_END (3)
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_legacy_START (31)
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_legacy_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cat_swap_sel : 32;
    } reg;
} SOC_HIPACKPHY_CATSWAPSEL_UNION;
#endif
#define SOC_HIPACKPHY_CATSWAPSEL_cat_swap_sel_START (0)
#define SOC_HIPACKPHY_CATSWAPSEL_cat_swap_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcackel : 6;
        unsigned int reserved_0: 2;
        unsigned int tcaent : 8;
        unsigned int tcacd : 8;
        unsigned int tcackeh : 6;
        unsigned int reserved_1: 2;
    } reg;
} SOC_HIPACKPHY_CATTIMER0_UNION;
#endif
#define SOC_HIPACKPHY_CATTIMER0_tcackel_START (0)
#define SOC_HIPACKPHY_CATTIMER0_tcackel_END (5)
#define SOC_HIPACKPHY_CATTIMER0_tcaent_START (8)
#define SOC_HIPACKPHY_CATTIMER0_tcaent_END (15)
#define SOC_HIPACKPHY_CATTIMER0_tcacd_START (16)
#define SOC_HIPACKPHY_CATTIMER0_tcacd_END (23)
#define SOC_HIPACKPHY_CATTIMER0_tcackeh_START (24)
#define SOC_HIPACKPHY_CATTIMER0_tcackeh_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcaext : 8;
        unsigned int tmrz : 6;
        unsigned int reserved : 18;
    } reg;
} SOC_HIPACKPHY_CATTIMER1_UNION;
#endif
#define SOC_HIPACKPHY_CATTIMER1_tcaext_START (0)
#define SOC_HIPACKPHY_CATTIMER1_tcaext_END (7)
#define SOC_HIPACKPHY_CATTIMER1_tmrz_START (8)
#define SOC_HIPACKPHY_CATTIMER1_tmrz_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ca_samp_num_bdl : 4;
        unsigned int ca_samp_num_ph : 4;
        unsigned int ca_trysamp_num : 4;
        unsigned int cat_rb_backtap : 4;
        unsigned int sw_cat_eyet : 1;
        unsigned int cat_openeye_en : 1;
        unsigned int cat_cat_phydq_sel : 1;
        unsigned int cat_restore_en : 1;
        unsigned int cat_lb_backtap : 4;
        unsigned int sw_cat_mrw42 : 1;
        unsigned int sw_cat_mrw48 : 1;
        unsigned int sw_cat_mrw41 : 1;
        unsigned int sw_cat_strobe : 1;
        unsigned int sw_cat_cke_high : 1;
        unsigned int sw_cat_cke_low : 1;
        unsigned int sw_cat_dqvalid : 1;
        unsigned int sw_cat_en : 1;
    } reg;
} SOC_HIPACKPHY_CATCONFIG_UNION;
#endif
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_bdl_START (0)
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_bdl_END (3)
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_ph_START (4)
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_ph_END (7)
#define SOC_HIPACKPHY_CATCONFIG_ca_trysamp_num_START (8)
#define SOC_HIPACKPHY_CATCONFIG_ca_trysamp_num_END (11)
#define SOC_HIPACKPHY_CATCONFIG_cat_rb_backtap_START (12)
#define SOC_HIPACKPHY_CATCONFIG_cat_rb_backtap_END (15)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_eyet_START (16)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_eyet_END (16)
#define SOC_HIPACKPHY_CATCONFIG_cat_openeye_en_START (17)
#define SOC_HIPACKPHY_CATCONFIG_cat_openeye_en_END (17)
#define SOC_HIPACKPHY_CATCONFIG_cat_cat_phydq_sel_START (18)
#define SOC_HIPACKPHY_CATCONFIG_cat_cat_phydq_sel_END (18)
#define SOC_HIPACKPHY_CATCONFIG_cat_restore_en_START (19)
#define SOC_HIPACKPHY_CATCONFIG_cat_restore_en_END (19)
#define SOC_HIPACKPHY_CATCONFIG_cat_lb_backtap_START (20)
#define SOC_HIPACKPHY_CATCONFIG_cat_lb_backtap_END (23)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw42_START (24)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw42_END (24)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw48_START (25)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw48_END (25)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw41_START (26)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw41_END (26)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_strobe_START (27)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_strobe_END (27)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_high_START (28)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_high_END (28)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_low_START (29)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_low_END (29)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_dqvalid_START (30)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_dqvalid_END (30)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_en_START (31)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cat_reault : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_HIPACKPHY_CATRESULT_UNION;
#endif
#define SOC_HIPACKPHY_CATRESULT_cat_reault_START (0)
#define SOC_HIPACKPHY_CATRESULT_cat_reault_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_dq_result : 32;
    } reg;
} SOC_HIPACKPHY_PHYDQRESULT_UNION;
#endif
#define SOC_HIPACKPHY_PHYDQRESULT_phy_dq_result_START (0)
#define SOC_HIPACKPHY_PHYDQRESULT_phy_dq_result_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrph_a_right : 5;
        unsigned int reserved_0 : 3;
        unsigned int addrph_a_left : 5;
        unsigned int reserved_1 : 3;
        unsigned int addrph_a : 5;
        unsigned int reserved_2 : 3;
        unsigned int addrph_a_ori : 5;
        unsigned int reserved_3 : 1;
        unsigned int cat_err : 1;
        unsigned int init_en : 1;
    } reg;
} SOC_HIPACKPHY_ADDRPHBOUND_UNION;
#endif
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_right_START (0)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_right_END (4)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_left_START (8)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_left_END (12)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_START (16)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_END (20)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_ori_START (24)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_ori_END (28)
#define SOC_HIPACKPHY_ADDRPHBOUND_cat_err_START (30)
#define SOC_HIPACKPHY_ADDRPHBOUND_cat_err_END (30)
#define SOC_HIPACKPHY_ADDRPHBOUND_init_en_START (31)
#define SOC_HIPACKPHY_ADDRPHBOUND_init_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw_cat_pat_p : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_HIPACKPHY_SWCATPATTERN_P_UNION;
#endif
#define SOC_HIPACKPHY_SWCATPATTERN_P_sw_cat_pat_p_START (0)
#define SOC_HIPACKPHY_SWCATPATTERN_P_sw_cat_pat_p_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw_cat_pat_n : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_HIPACKPHY_SWCATPATTERN_N_UNION;
#endif
#define SOC_HIPACKPHY_SWCATPATTERN_N_sw_cat_pat_n_START (0)
#define SOC_HIPACKPHY_SWCATPATTERN_N_sw_cat_pat_n_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mrs_seq_prog : 32;
    } reg;
} SOC_HIPACKPHY_MRS_SEQ_PROG_UNION;
#endif
#define SOC_HIPACKPHY_MRS_SEQ_PROG_mrs_seq_prog_START (0)
#define SOC_HIPACKPHY_MRS_SEQ_PROG_mrs_seq_prog_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_dram_clk_enable : 4;
        unsigned int t_dram_clk_disable : 4;
        unsigned int t_wakeup_thrd_lv3 : 4;
        unsigned int t_resp : 4;
        unsigned int lp_pll_powerdown_disable : 1;
        unsigned int lp_dx_phy_phgated_disable : 1;
        unsigned int lp_dx_phy_clkgated_disable : 1;
        unsigned int lp_ac_phy_clkgated_disable : 1;
        unsigned int lp_cmdoen_disable : 1;
        unsigned int t_wakeup_thrd_lv2 : 4;
        unsigned int gcken_dxbist : 1;
        unsigned int gcken_acbist : 1;
        unsigned int gcken_retrain : 1;
        unsigned int gcken_dtrain : 1;
        unsigned int gcken_dinit : 1;
        unsigned int gcken_dfi_main : 1;
        unsigned int gcken_auto_en : 1;
    } reg;
} SOC_HIPACKPHY_LPCTRL_UNION;
#endif
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_enable_START (0)
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_enable_END (3)
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_disable_START (4)
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_disable_END (7)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv3_START (8)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv3_END (11)
#define SOC_HIPACKPHY_LPCTRL_t_resp_START (12)
#define SOC_HIPACKPHY_LPCTRL_t_resp_END (15)
#define SOC_HIPACKPHY_LPCTRL_lp_pll_powerdown_disable_START (16)
#define SOC_HIPACKPHY_LPCTRL_lp_pll_powerdown_disable_END (16)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_phgated_disable_START (17)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_phgated_disable_END (17)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_clkgated_disable_START (18)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_clkgated_disable_END (18)
#define SOC_HIPACKPHY_LPCTRL_lp_ac_phy_clkgated_disable_START (19)
#define SOC_HIPACKPHY_LPCTRL_lp_ac_phy_clkgated_disable_END (19)
#define SOC_HIPACKPHY_LPCTRL_lp_cmdoen_disable_START (20)
#define SOC_HIPACKPHY_LPCTRL_lp_cmdoen_disable_END (20)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv2_START (21)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv2_END (24)
#define SOC_HIPACKPHY_LPCTRL_gcken_dxbist_START (25)
#define SOC_HIPACKPHY_LPCTRL_gcken_dxbist_END (25)
#define SOC_HIPACKPHY_LPCTRL_gcken_acbist_START (26)
#define SOC_HIPACKPHY_LPCTRL_gcken_acbist_END (26)
#define SOC_HIPACKPHY_LPCTRL_gcken_retrain_START (27)
#define SOC_HIPACKPHY_LPCTRL_gcken_retrain_END (27)
#define SOC_HIPACKPHY_LPCTRL_gcken_dtrain_START (28)
#define SOC_HIPACKPHY_LPCTRL_gcken_dtrain_END (28)
#define SOC_HIPACKPHY_LPCTRL_gcken_dinit_START (29)
#define SOC_HIPACKPHY_LPCTRL_gcken_dinit_END (29)
#define SOC_HIPACKPHY_LPCTRL_gcken_dfi_main_START (30)
#define SOC_HIPACKPHY_LPCTRL_gcken_dfi_main_END (30)
#define SOC_HIPACKPHY_LPCTRL_gcken_auto_en_START (31)
#define SOC_HIPACKPHY_LPCTRL_gcken_auto_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk1x_dramclk0_byt1 : 3;
        unsigned int clk1x_dramclk1_byt1 : 3;
        unsigned int clk1x_cmd2t_byt1 : 3;
        unsigned int clk1x_cmd1t_byt1 : 3;
        unsigned int clk1x_mclk_byt1 : 3;
        unsigned int reserved_0 : 1;
        unsigned int clk2x_dramclk0_byt1 : 3;
        unsigned int clk2x_dramclk1_byt1 : 3;
        unsigned int clk2x_cmd2t_byt1 : 3;
        unsigned int clk2x_cmd1t_byt1 : 3;
        unsigned int clk2x_mclk_byt1 : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL10_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk0_byt1_START (0)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk0_byt1_END (2)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk1_byt1_START (3)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk1_byt1_END (5)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd2t_byt1_START (6)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd2t_byt1_END (8)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd1t_byt1_START (9)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd1t_byt1_END (11)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_mclk_byt1_START (12)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_mclk_byt1_END (14)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk0_byt1_START (16)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk0_byt1_END (18)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk1_byt1_START (19)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk1_byt1_END (21)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd2t_byt1_START (22)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd2t_byt1_END (24)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd1t_byt1_START (25)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd1t_byt1_END (27)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_mclk_byt1_START (28)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_mclk_byt1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ck1p_dclk0_byt1 : 3;
        unsigned int ck2p_dclk1_byt1 : 3;
        unsigned int ck3p_cmd1t_byt1 : 3;
        unsigned int ck4p_cmd2t_byt1 : 3;
        unsigned int reserved_0 : 11;
        unsigned int ac_reg_byone_cmdr1t_sel : 1;
        unsigned int ac_reg_cmd_byt1_phsel : 4;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_HIPACKPHY_ACPHYCTL11_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL11_ck1p_dclk0_byt1_START (0)
#define SOC_HIPACKPHY_ACPHYCTL11_ck1p_dclk0_byt1_END (2)
#define SOC_HIPACKPHY_ACPHYCTL11_ck2p_dclk1_byt1_START (3)
#define SOC_HIPACKPHY_ACPHYCTL11_ck2p_dclk1_byt1_END (5)
#define SOC_HIPACKPHY_ACPHYCTL11_ck3p_cmd1t_byt1_START (6)
#define SOC_HIPACKPHY_ACPHYCTL11_ck3p_cmd1t_byt1_END (8)
#define SOC_HIPACKPHY_ACPHYCTL11_ck4p_cmd2t_byt1_START (9)
#define SOC_HIPACKPHY_ACPHYCTL11_ck4p_cmd2t_byt1_END (11)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_byone_cmdr1t_sel_START (23)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_byone_cmdr1t_sel_END (23)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_cmd_byt1_phsel_START (24)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_cmd_byt1_phsel_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vrftres_ahvref : 6;
        unsigned int vrftres_ahvref_lb : 6;
        unsigned int vrftres_ahvref_ub : 6;
        unsigned int reserved : 14;
    } reg;
} SOC_HIPACKPHY_AHVREFT_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_START (0)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_END (5)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_lb_START (6)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_lb_END (11)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_ub_START (12)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_ub_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_vrftres_dvref : 6;
        unsigned int ac_vrftres_dvref_lb : 6;
        unsigned int ac_vrftres_dvref_ub : 6;
        unsigned int ac_vrftres_dlb_status : 3;
        unsigned int ac_vrftres_dub_status : 3;
        unsigned int reserved : 7;
        unsigned int ac_vreftres_set_type : 1;
    } reg;
} SOC_HIPACKPHY_ADVREF_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_START (0)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_END (5)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_lb_START (6)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_lb_END (11)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_ub_START (12)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_ub_END (17)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dlb_status_START (18)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dlb_status_END (20)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dub_status_START (21)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dub_status_END (23)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vreftres_set_type_START (31)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vreftres_set_type_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_lpwakeup_fg : 5;
        unsigned int reserved : 25;
        unsigned int gcken_apb_ctrlreg : 1;
        unsigned int gcken_apb_auto_en : 1;
    } reg;
} SOC_HIPACKPHY_DFIMISCCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DFIMISCCTRL_t_lpwakeup_fg_START (0)
#define SOC_HIPACKPHY_DFIMISCCTRL_t_lpwakeup_fg_END (4)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_ctrlreg_START (30)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_ctrlreg_END (30)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_auto_en_START (31)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_auto_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bist_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int dq_cmp_mask : 8;
        unsigned int dqm_cmp_mask : 1;
        unsigned int prbs_mode : 2;
        unsigned int reserved_1 : 5;
        unsigned int lfsr_seed : 8;
    } reg;
} SOC_HIPACKPHY_DXNBISTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXNBISTCTRL_bist_en_START (0)
#define SOC_HIPACKPHY_DXNBISTCTRL_bist_en_END (0)
#define SOC_HIPACKPHY_DXNBISTCTRL_dq_cmp_mask_START (8)
#define SOC_HIPACKPHY_DXNBISTCTRL_dq_cmp_mask_END (15)
#define SOC_HIPACKPHY_DXNBISTCTRL_dqm_cmp_mask_START (16)
#define SOC_HIPACKPHY_DXNBISTCTRL_dqm_cmp_mask_END (16)
#define SOC_HIPACKPHY_DXNBISTCTRL_prbs_mode_START (17)
#define SOC_HIPACKPHY_DXNBISTCTRL_prbs_mode_END (18)
#define SOC_HIPACKPHY_DXNBISTCTRL_lfsr_seed_START (24)
#define SOC_HIPACKPHY_DXNBISTCTRL_lfsr_seed_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dq_cmp_rerr : 8;
        unsigned int dq_cmp_ferr : 8;
        unsigned int dqm_cmp_err : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_HIPACKPHY_DXNBISTSTS_UNION;
#endif
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_rerr_START (0)
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_rerr_END (7)
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_ferr_START (8)
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_ferr_END (15)
#define SOC_HIPACKPHY_DXNBISTSTS_dqm_cmp_err_START (16)
#define SOC_HIPACKPHY_DXNBISTSTS_dqm_cmp_err_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bl_dis : 1;
        unsigned int dm_dis : 1;
        unsigned int reserved_0 : 5;
        unsigned int gck_dbi_autoen : 1;
        unsigned int dbi_write_mode : 2;
        unsigned int dbi_read_en : 2;
        unsigned int dbi_write_en : 2;
        unsigned int dbi_polarity : 1;
        unsigned int wdbi_mask_en : 1;
        unsigned int wdbi_mask_data : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_HIPACKPHY_DXNCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXNCTRL_bl_dis_START (0)
#define SOC_HIPACKPHY_DXNCTRL_bl_dis_END (0)
#define SOC_HIPACKPHY_DXNCTRL_dm_dis_START (1)
#define SOC_HIPACKPHY_DXNCTRL_dm_dis_END (1)
#define SOC_HIPACKPHY_DXNCTRL_gck_dbi_autoen_START (7)
#define SOC_HIPACKPHY_DXNCTRL_gck_dbi_autoen_END (7)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_mode_START (8)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_mode_END (9)
#define SOC_HIPACKPHY_DXNCTRL_dbi_read_en_START (10)
#define SOC_HIPACKPHY_DXNCTRL_dbi_read_en_END (11)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_en_START (12)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_en_END (13)
#define SOC_HIPACKPHY_DXNCTRL_dbi_polarity_START (14)
#define SOC_HIPACKPHY_DXNCTRL_dbi_polarity_END (14)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_en_START (15)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_en_END (15)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_data_START (16)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdq0bdl : 7;
        unsigned int reserved_0: 1;
        unsigned int wdq1bdl : 7;
        unsigned int reserved_1: 1;
        unsigned int wdq2bdl : 7;
        unsigned int reserved_2: 1;
        unsigned int wdq3bdl : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_HIPACKPHY_DXNWDQNBDL0_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq0bdl_START (0)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq0bdl_END (6)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq1bdl_START (8)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq1bdl_END (14)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq2bdl_START (16)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq2bdl_END (22)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq3bdl_START (24)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq3bdl_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdq4bdl : 7;
        unsigned int reserved_0: 1;
        unsigned int wdq5bdl : 7;
        unsigned int reserved_1: 1;
        unsigned int wdq6bdl : 7;
        unsigned int reserved_2: 1;
        unsigned int wdq7bdl : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_HIPACKPHY_DXNWDQNBDL1_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq4bdl_START (0)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq4bdl_END (6)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq5bdl_START (8)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq5bdl_END (14)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq6bdl_START (16)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq6bdl_END (22)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq7bdl_START (24)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq7bdl_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdmbdl : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_HIPACKPHY_DXNWDQNBDL2_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNBDL2_wdmbdl_START (0)
#define SOC_HIPACKPHY_DXNWDQNBDL2_wdmbdl_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdq0bdl : 7;
        unsigned int reserved_0: 1;
        unsigned int rdq1bdl : 7;
        unsigned int reserved_1: 1;
        unsigned int rdq2bdl : 7;
        unsigned int reserved_2: 1;
        unsigned int rdq3bdl : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_HIPACKPHY_DXNRDQNBDL0_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq0bdl_START (0)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq0bdl_END (6)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq1bdl_START (8)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq1bdl_END (14)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq2bdl_START (16)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq2bdl_END (22)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq3bdl_START (24)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq3bdl_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdq4bdl : 7;
        unsigned int reserved_0: 1;
        unsigned int rdq5bdl : 7;
        unsigned int reserved_1: 1;
        unsigned int rdq6bdl : 7;
        unsigned int reserved_2: 1;
        unsigned int rdq7bdl : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_HIPACKPHY_DXNRDQNBDL1_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq4bdl_START (0)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq4bdl_END (6)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq5bdl_START (8)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq5bdl_END (14)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq6bdl_START (16)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq6bdl_END (22)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq7bdl_START (24)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq7bdl_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdmbdl : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_HIPACKPHY_DXNRDQNBDL2_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQNBDL2_rdmbdl_START (0)
#define SOC_HIPACKPHY_DXNRDQNBDL2_rdmbdl_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oen_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int wdqsoe_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_DXNOEBDL_UNION;
#endif
#define SOC_HIPACKPHY_DXNOEBDL_oen_bdl_START (0)
#define SOC_HIPACKPHY_DXNOEBDL_oen_bdl_END (6)
#define SOC_HIPACKPHY_DXNOEBDL_wdqsoe_bdl_START (16)
#define SOC_HIPACKPHY_DXNOEBDL_wdqsoe_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdqsbdl : 9;
        unsigned int reserved_0: 7;
        unsigned int rdqscyc : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_HIPACKPHY_DXNRDQSDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqsbdl_START (0)
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqsbdl_END (8)
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqscyc_START (16)
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqscyc_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdqsbdl : 7;
        unsigned int reserved_0: 1;
        unsigned int wdqsphase : 4;
        unsigned int reserved_1: 20;
    } reg;
} SOC_HIPACKPHY_DXNWDQSDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsbdl_START (0)
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsbdl_END (6)
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsphase_START (8)
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsphase_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int wdqphase : 6;
        unsigned int reserved_1: 18;
    } reg;
} SOC_HIPACKPHY_DXNWDQDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQDLY_wdqphase_START (8)
#define SOC_HIPACKPHY_DXNWDQDLY_wdqphase_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int wlsl : 2;
        unsigned int reserved_1: 14;
    } reg;
} SOC_HIPACKPHY_DXNWLSL_UNION;
#endif
#define SOC_HIPACKPHY_DXNWLSL_wlsl_START (16)
#define SOC_HIPACKPHY_DXNWLSL_wlsl_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gds : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_HIPACKPHY_DXNGDS_UNION;
#endif
#define SOC_HIPACKPHY_DXNGDS_gds_START (0)
#define SOC_HIPACKPHY_DXNGDS_gds_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdqsgbdl : 7;
        unsigned int reserved_0 : 2;
        unsigned int rdqsgphase : 6;
        unsigned int reserved_1 : 1;
        unsigned int rdqsgtxbdl : 7;
        unsigned int reserved_2 : 1;
        unsigned int org_rdqsgph : 6;
        unsigned int reserved_3 : 2;
    } reg;
} SOC_HIPACKPHY_DXNRDQSGDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgbdl_START (0)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgbdl_END (6)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgphase_START (9)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgphase_END (14)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgtxbdl_START (16)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgtxbdl_END (22)
#define SOC_HIPACKPHY_DXNRDQSGDLY_org_rdqsgph_START (24)
#define SOC_HIPACKPHY_DXNRDQSGDLY_org_rdqsgph_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdq0bdl_left : 7;
        unsigned int reserved_0 : 1;
        unsigned int wdq1bdl_left : 7;
        unsigned int reserved_1 : 1;
        unsigned int wdq2bdl_left : 7;
        unsigned int reserved_2 : 1;
        unsigned int wdq3bdl_left : 7;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_HIPACKPHY_DXNWDQNLB0_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq0bdl_left_START (0)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq0bdl_left_END (6)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq1bdl_left_START (8)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq1bdl_left_END (14)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq2bdl_left_START (16)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq2bdl_left_END (22)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq3bdl_left_START (24)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq3bdl_left_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdqsbdl30 : 9;
        unsigned int reserved_0 : 7;
        unsigned int bdl_mondly : 9;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_HIPACKPHY_DXNRDQSDLYSUB_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_rdqsbdl30_START (0)
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_rdqsbdl30_END (8)
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_bdl_mondly_START (16)
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_bdl_mondly_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dx_fbclk_bdl : 5;
        unsigned int reserved_0 : 11;
        unsigned int dx_refclk_bdl : 5;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_HIPACKPHY_DXNCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_DXNCLKBDL_dx_fbclk_bdl_START (0)
#define SOC_HIPACKPHY_DXNCLKBDL_dx_fbclk_bdl_END (4)
#define SOC_HIPACKPHY_DXNCLKBDL_dx_refclk_bdl_START (16)
#define SOC_HIPACKPHY_DXNCLKBDL_dx_refclk_bdl_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdqsbdl_right : 9;
        unsigned int reserved_0 : 7;
        unsigned int rdqsbdl_left : 9;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_HIPACKPHY_DXNRDBOUND_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_right_START (0)
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_right_END (8)
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_left_START (16)
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_left_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdqphase_right : 6;
        unsigned int reserved_0 : 10;
        unsigned int wdqphase_left : 6;
        unsigned int reserved_1 : 2;
        unsigned int wdq0bdl_left : 7;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_HIPACKPHY_DXNWRBOUND_UNION;
#endif
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_right_START (0)
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_right_END (5)
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_left_START (16)
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_left_END (21)
#define SOC_HIPACKPHY_DXNWRBOUND_wdq0bdl_left_START (24)
#define SOC_HIPACKPHY_DXNWRBOUND_wdq0bdl_left_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dx_pll_thrm : 1;
        unsigned int dx_pll_testpem : 1;
        unsigned int dx_pll_testen : 1;
        unsigned int dx_pll_init : 1;
        unsigned int dx_pll_cpi : 3;
        unsigned int dx_pll_sp : 3;
        unsigned int dx_pll_lt : 2;
        unsigned int dx_pll_calt : 1;
        unsigned int dx_pll_calm : 1;
        unsigned int dx_pll_cal : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_HIPACKPHY_DXPHYCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_thrm_START (0)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_thrm_END (0)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testpem_START (1)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testpem_END (1)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testen_START (2)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testen_END (2)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_init_START (3)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_init_END (3)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cpi_START (4)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cpi_END (6)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_sp_START (7)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_sp_END (9)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_lt_START (10)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_lt_END (11)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calt_START (12)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calt_END (12)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calm_START (13)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calm_END (13)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cal_START (14)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cal_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdq4bdl_left : 7;
        unsigned int reserved_0 : 1;
        unsigned int wdq5bdl_left : 7;
        unsigned int reserved_1 : 1;
        unsigned int wdq6bdl_left : 7;
        unsigned int reserved_2 : 1;
        unsigned int wdq7bdl_left : 7;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_HIPACKPHY_DXNWDQNLB1_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq4bdl_left_START (0)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq4bdl_left_END (6)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq5bdl_left_START (8)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq5bdl_left_END (14)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq6bdl_left_START (16)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq6bdl_left_END (22)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq7bdl_left_START (24)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq7bdl_left_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rxn_2nd_dq : 8;
        unsigned int rxp_2nd_dq : 8;
        unsigned int dx_margin_a1 : 1;
        unsigned int dx_dqs_l : 1;
        unsigned int dx_dqs_h : 1;
        unsigned int dx_rxn_2nd_dm : 1;
        unsigned int dx_rxp_2nd_dm : 1;
        unsigned int dqsgatedla : 1;
        unsigned int lvdqclkdiv2 : 1;
        unsigned int bufphyclkdiv2 : 1;
        unsigned int margin_a0 : 1;
        unsigned int enshift_a0 : 1;
        unsigned int ptrgated_en : 1;
        unsigned int reserved_0 : 1;
        unsigned int dx_reg_dqsg_extend_en_dqs : 1;
        unsigned int dx_reg_dqsg_extend_2t_dqs : 1;
        unsigned int dx_reg_rxfifo_r1t_sel_dqs : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_DXNMISCCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxn_2nd_dq_START (0)
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxn_2nd_dq_END (7)
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxp_2nd_dq_START (8)
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxp_2nd_dq_END (15)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_margin_a1_START (16)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_margin_a1_END (16)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_l_START (17)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_l_END (17)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_h_START (18)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_h_END (18)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxn_2nd_dm_START (19)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxn_2nd_dm_END (19)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxp_2nd_dm_START (20)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxp_2nd_dm_END (20)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dqsgatedla_START (21)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dqsgatedla_END (21)
#define SOC_HIPACKPHY_DXNMISCCTRL0_lvdqclkdiv2_START (22)
#define SOC_HIPACKPHY_DXNMISCCTRL0_lvdqclkdiv2_END (22)
#define SOC_HIPACKPHY_DXNMISCCTRL0_bufphyclkdiv2_START (23)
#define SOC_HIPACKPHY_DXNMISCCTRL0_bufphyclkdiv2_END (23)
#define SOC_HIPACKPHY_DXNMISCCTRL0_margin_a0_START (24)
#define SOC_HIPACKPHY_DXNMISCCTRL0_margin_a0_END (24)
#define SOC_HIPACKPHY_DXNMISCCTRL0_enshift_a0_START (25)
#define SOC_HIPACKPHY_DXNMISCCTRL0_enshift_a0_END (25)
#define SOC_HIPACKPHY_DXNMISCCTRL0_ptrgated_en_START (26)
#define SOC_HIPACKPHY_DXNMISCCTRL0_ptrgated_en_END (26)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_en_dqs_START (28)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_en_dqs_END (28)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_2t_dqs_START (29)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_2t_dqs_END (29)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_rxfifo_r1t_sel_dqs_START (30)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_rxfifo_r1t_sel_dqs_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclk2x : 4;
        unsigned int mclk1x : 4;
        unsigned int dqsclk2x : 4;
        unsigned int dqsclk1x : 4;
        unsigned int dqsgclk2x : 4;
        unsigned int dqsgclk1x : 4;
        unsigned int dqclk2x : 4;
        unsigned int dqclk1x : 4;
    } reg;
} SOC_HIPACKPHY_DXNMISCCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk2x_START (0)
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk2x_END (3)
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk1x_START (4)
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk1x_END (7)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk2x_START (8)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk2x_END (11)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk1x_START (12)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk1x_END (15)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk2x_START (16)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk2x_END (19)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk1x_START (20)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk1x_END (23)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk2x_START (24)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk2x_END (27)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk1x_START (28)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk1x_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdmbdl_left : 7;
        unsigned int reserved : 9;
        unsigned int dqs0_gold : 16;
    } reg;
} SOC_HIPACKPHY_DXDEBUG0_UNION;
#endif
#define SOC_HIPACKPHY_DXDEBUG0_wdmbdl_left_START (0)
#define SOC_HIPACKPHY_DXDEBUG0_wdmbdl_left_END (6)
#define SOC_HIPACKPHY_DXDEBUG0_dqs0_gold_START (16)
#define SOC_HIPACKPHY_DXDEBUG0_dqs0_gold_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqs0b : 16;
        unsigned int dqs0 : 16;
    } reg;
} SOC_HIPACKPHY_DXDEBUG1_UNION;
#endif
#define SOC_HIPACKPHY_DXDEBUG1_dqs0b_START (0)
#define SOC_HIPACKPHY_DXDEBUG1_dqs0b_END (15)
#define SOC_HIPACKPHY_DXDEBUG1_dqs0_START (16)
#define SOC_HIPACKPHY_DXDEBUG1_dqs0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vrftres_dvref : 6;
        unsigned int vrftres_dvref_lb : 6;
        unsigned int vrftres_dvref_ub : 6;
        unsigned int vrftres_dlb_status : 3;
        unsigned int vrftres_dub_status : 3;
        unsigned int reserved : 8;
    } reg;
} SOC_HIPACKPHY_DVREFT_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_START (0)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_END (5)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_lb_START (6)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_lb_END (11)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_ub_START (12)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_ub_END (17)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dlb_status_START (18)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dlb_status_END (20)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dub_status_START (21)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dub_status_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vrftres_hvref : 6;
        unsigned int vrftres_hvref_lb : 6;
        unsigned int vrftres_dvref_ub : 6;
        unsigned int vrftres_hlb_status : 3;
        unsigned int vrftres_hub_status : 3;
        unsigned int reserved : 8;
    } reg;
} SOC_HIPACKPHY_HVREFT_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_START (0)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_END (5)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_lb_START (6)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_lb_END (11)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_dvref_ub_START (12)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_dvref_ub_END (17)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hlb_status_START (18)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hlb_status_END (20)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hub_status_START (21)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hub_status_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_dbg_reffb_postdly : 1;
        unsigned int reg_dbg_reffb_predly : 1;
        unsigned int reg_dbg_pllclk_sel : 1;
        unsigned int reg_dbg_prepost_sel : 1;
        unsigned int deskew_regread : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_HIPACKPHY_DXDEBUGCONFIG_UNION;
#endif
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_postdly_START (0)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_postdly_END (0)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_predly_START (1)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_predly_END (1)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_pllclk_sel_START (2)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_pllclk_sel_END (2)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_prepost_sel_START (3)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_prepost_sel_END (3)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_deskew_regread_START (4)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_deskew_regread_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_dq_dcc : 3;
        unsigned int dxctl_dqsg_dcc : 3;
        unsigned int dxctl_dqs_dcc : 3;
        unsigned int dxctl_mclk_dcc : 3;
        unsigned int dx_byp_ck90_data_code_dqs : 9;
        unsigned int reserved : 11;
    } reg;
} SOC_HIPACKPHY_DXNDCC_UNION;
#endif
#define SOC_HIPACKPHY_DXNDCC_dxctl_dq_dcc_START (0)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dq_dcc_END (2)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqsg_dcc_START (3)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqsg_dcc_END (5)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqs_dcc_START (6)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqs_dcc_END (8)
#define SOC_HIPACKPHY_DXNDCC_dxctl_mclk_dcc_START (9)
#define SOC_HIPACKPHY_DXNDCC_dxctl_mclk_dcc_END (11)
#define SOC_HIPACKPHY_DXNDCC_dx_byp_ck90_data_code_dqs_START (12)
#define SOC_HIPACKPHY_DXNDCC_dx_byp_ck90_data_code_dqs_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqsg_extdly_dqs : 3;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 7;
        unsigned int reserved_2 : 1;
        unsigned int rxext_dly : 3;
        unsigned int reserved_3 : 1;
        unsigned int dqsdly_demux_code : 3;
        unsigned int post_margin_code : 3;
        unsigned int pre_margin_code : 3;
        unsigned int dqsgclk2x_rank1 : 3;
        unsigned int dqsgclk1x_rank1 : 3;
        unsigned int reserved_4 : 1;
    } reg;
} SOC_HIPACKPHY_DXNMISCCTRL3_UNION;
#endif
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsg_extdly_dqs_START (0)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsg_extdly_dqs_END (2)
#define SOC_HIPACKPHY_DXNMISCCTRL3_rxext_dly_START (12)
#define SOC_HIPACKPHY_DXNMISCCTRL3_rxext_dly_END (14)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsdly_demux_code_START (16)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsdly_demux_code_END (18)
#define SOC_HIPACKPHY_DXNMISCCTRL3_post_margin_code_START (19)
#define SOC_HIPACKPHY_DXNMISCCTRL3_post_margin_code_END (21)
#define SOC_HIPACKPHY_DXNMISCCTRL3_pre_margin_code_START (22)
#define SOC_HIPACKPHY_DXNMISCCTRL3_pre_margin_code_END (24)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk2x_rank1_START (25)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk2x_rank1_END (27)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk1x_rank1_START (28)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk1x_rank1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac1t_ioctl_rdsel_p : 3;
        unsigned int ac1t_ioctl_rdsel_n : 3;
        unsigned int ac1t_ioctl_tdsel_p : 4;
        unsigned int ac1t_ioctl_tdsel_n : 4;
        unsigned int ioctl_ap_rx_mode : 2;
        unsigned int ioctl_odtn : 1;
        unsigned int ioctl_odtp : 1;
        unsigned int odt_ioctl_tdsel_p : 4;
        unsigned int odt_ioctl_tdsel_n : 4;
        unsigned int rx_rx_passthrough : 1;
        unsigned int rx_rsneg_passthrough : 1;
        unsigned int reserved : 4;
    } reg;
} SOC_HIPACKPHY_IOCTL3_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_p_START (0)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_p_END (2)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_n_START (3)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_n_END (5)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_p_START (6)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_p_END (9)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_n_START (10)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_n_END (13)
#define SOC_HIPACKPHY_IOCTL3_ioctl_ap_rx_mode_START (14)
#define SOC_HIPACKPHY_IOCTL3_ioctl_ap_rx_mode_END (15)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtn_START (16)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtn_END (16)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtp_START (17)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtp_END (17)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_p_START (18)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_p_END (21)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_n_START (22)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_n_END (25)
#define SOC_HIPACKPHY_IOCTL3_rx_rx_passthrough_START (26)
#define SOC_HIPACKPHY_IOCTL3_rx_rx_passthrough_END (26)
#define SOC_HIPACKPHY_IOCTL3_rx_rsneg_passthrough_START (27)
#define SOC_HIPACKPHY_IOCTL3_rx_rsneg_passthrough_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ck_ioctl_rdsel_p : 3;
        unsigned int ck_ioctl_rdsel_n : 3;
        unsigned int ck_ioctl_tdsel_p : 4;
        unsigned int ck_ioctl_tdsel_n : 4;
        unsigned int ac2t_ioctl_rdsel_p : 3;
        unsigned int ac2t_ioctl_rdsel_n : 3;
        unsigned int ac2t_ioctl_tdsel_p : 4;
        unsigned int ac2t_ioctl_tdsel_n : 4;
        unsigned int reserved : 4;
    } reg;
} SOC_HIPACKPHY_IOCTL4_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_p_START (0)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_p_END (2)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_n_START (3)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_n_END (5)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_p_START (6)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_p_END (9)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_n_START (10)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_n_END (13)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_p_START (14)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_p_END (16)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_n_START (17)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_n_END (19)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_p_START (20)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_p_END (23)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_n_START (24)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_n_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqs_ioctl_rdsel_p : 3;
        unsigned int dqs_ioctl_rdsel_n : 3;
        unsigned int dqs_ioctl_tdsel_p : 4;
        unsigned int dqs_ioctl_tdsel_n : 4;
        unsigned int dx_ioctl_rdsel_p : 3;
        unsigned int dx_ioctl_rdsel_n : 3;
        unsigned int dx_ioctl_tdsel_p : 4;
        unsigned int dx_ioctl_tdsel_n : 4;
        unsigned int reserved : 4;
    } reg;
} SOC_HIPACKPHY_IOCTL5_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_p_START (0)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_p_END (2)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_n_START (3)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_n_END (5)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_p_START (6)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_p_END (9)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_n_START (10)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_n_END (13)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_p_START (14)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_p_END (16)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_n_START (17)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_n_END (19)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_p_START (20)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_p_END (23)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_n_START (24)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_n_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 6;
        unsigned int acctl_pll_bp_refpfd : 1;
        unsigned int acctl_pll_bp_refvco : 1;
        unsigned int acctl_pll_enphsel : 1;
        unsigned int acctl_pll_en_cal : 1;
        unsigned int acctl_pll_initsel : 1;
        unsigned int acctl_pll_lockt_sel : 1;
        unsigned int acctl_pll_fopetestfb : 1;
        unsigned int acctl_pll_fopetestref : 1;
        unsigned int acctl_pll_lockin : 1;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_HIPACKPHY_AC_PLLCTRL_UNION;
#endif
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refpfd_START (6)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refpfd_END (6)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refvco_START (7)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refvco_END (7)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_enphsel_START (8)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_enphsel_END (8)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_en_cal_START (9)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_en_cal_END (9)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_initsel_START (10)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_initsel_END (10)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockt_sel_START (11)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockt_sel_END (11)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestfb_START (12)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestfb_END (12)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestref_START (13)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestref_END (13)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockin_START (14)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockin_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_odtoen : 1;
        unsigned int reserved_0 : 1;
        unsigned int acctl_cmdoen : 8;
        unsigned int reserved_1 : 2;
        unsigned int acctl_ckoen : 1;
        unsigned int acctl_ckeoen : 2;
        unsigned int acctl_csoen : 2;
        unsigned int acctl_resetoen : 1;
        unsigned int lpddr_mode : 1;
        unsigned int lpbk_addr_v_sel : 1;
        unsigned int wfifo_acctl_gcken : 1;
        unsigned int wfifo_acctl_passthrough : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_HIPACKPHY_AC_PHYCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_odtoen_START (0)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_odtoen_END (0)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_cmdoen_START (2)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_cmdoen_END (9)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckoen_START (12)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckoen_END (12)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckeoen_START (13)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckeoen_END (14)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_csoen_START (15)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_csoen_END (16)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_resetoen_START (17)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_resetoen_END (17)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpddr_mode_START (18)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpddr_mode_END (18)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpbk_addr_v_sel_START (19)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpbk_addr_v_sel_END (19)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_gcken_START (20)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_gcken_END (20)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_passthrough_START (21)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_passthrough_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int acctl_ioctl_diffck_en : 1;
        unsigned int acctl_ioctl_aciopldn : 1;
        unsigned int acctl_ioctl_genvref_dram_refsel_2 : 1;
        unsigned int reserved_1 : 1;
        unsigned int acctl_ioctl_genvref_dram_refsel_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int acctl_ioctl_genvref_dram_refsel_0 : 1;
        unsigned int reserved_3 : 1;
        unsigned int acctl_ioctl_genvref_dram_pd : 1;
        unsigned int reserved_4 : 7;
        unsigned int ac1t_ioctl_ronsel : 3;
        unsigned int ac2t_ioctl_ronsel : 3;
        unsigned int ck_ioctl_ronsel : 3;
        unsigned int reserved_5 : 6;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_diffck_en_START (1)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_diffck_en_END (1)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_aciopldn_START (2)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_aciopldn_END (2)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_2_START (3)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_2_END (3)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_1_START (5)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_1_END (5)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_0_START (7)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_0_END (7)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_pd_START (9)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_pd_END (9)
#define SOC_HIPACKPHY_AC_IOCTL_ac1t_ioctl_ronsel_START (17)
#define SOC_HIPACKPHY_AC_IOCTL_ac1t_ioctl_ronsel_END (19)
#define SOC_HIPACKPHY_AC_IOCTL_ac2t_ioctl_ronsel_START (20)
#define SOC_HIPACKPHY_AC_IOCTL_ac2t_ioctl_ronsel_END (22)
#define SOC_HIPACKPHY_AC_IOCTL_ck_ioctl_ronsel_START (23)
#define SOC_HIPACKPHY_AC_IOCTL_ck_ioctl_ronsel_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 18;
        unsigned int acctl_pll_testen : 1;
        unsigned int acctl_pll_init : 1;
        unsigned int acctl_pll_cpi : 3;
        unsigned int acctl_pll_sp : 2;
        unsigned int reserved_1 : 1;
        unsigned int acctl_pll_lt : 2;
        unsigned int reserved_2 : 4;
    } reg;
} SOC_HIPACKPHY_AC_PHYCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_testen_START (18)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_testen_END (18)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_init_START (19)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_init_END (19)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_cpi_START (20)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_cpi_END (22)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_sp_START (23)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_sp_END (24)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_lt_START (26)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_lt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_pll_test : 6;
        unsigned int reserved : 25;
        unsigned int acctl_pll_lock : 1;
    } reg;
} SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_test_START (0)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_test_END (5)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_lock_START (31)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_ioctl_genvref_range_2 : 4;
        unsigned int reserved_0 : 4;
        unsigned int acctl_ioctl_genvref_pd : 4;
        unsigned int reserved_1 : 6;
        unsigned int acctl_ioctl_genvref_dram_range_2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int acctl_ioctl_genvref_dram_range_1 : 1;
        unsigned int reserved_3 : 1;
        unsigned int acctl_ioctl_genvref_dram_range_0 : 1;
        unsigned int reserved_4 : 1;
        unsigned int acctl_zcal_vbias_n : 2;
        unsigned int acctl_zcal_vbias_p : 2;
        unsigned int reserved_5 : 4;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL1_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_range_2_START (0)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_range_2_END (3)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_pd_START (8)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_pd_END (11)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_2_START (18)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_2_END (18)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_1_START (20)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_1_END (20)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_0_START (22)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_0_END (22)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_n_START (24)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_n_END (25)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_p_START (26)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_p_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_ioctl_genvref_range_0 : 4;
        unsigned int reserved_0 : 2;
        unsigned int acctl_ioctl_genvref_range_1 : 4;
        unsigned int reserved_1 : 2;
        unsigned int acctl_ioctl_genvref_refsel_0 : 4;
        unsigned int reserved_2 : 2;
        unsigned int acctl_ioctl_genvref_refsel_1 : 4;
        unsigned int reserved_3 : 2;
        unsigned int acctl_ioctl_genvref_refsel_2 : 4;
        unsigned int vref_lpbkmode : 2;
        unsigned int reserved_4 : 2;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL2_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_0_START (0)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_0_END (3)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_1_START (6)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_1_END (9)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_0_START (12)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_0_END (15)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_1_START (18)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_1_END (21)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_2_START (24)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_2_END (27)
#define SOC_HIPACKPHY_AC_IOCTL2_vref_lpbkmode_START (28)
#define SOC_HIPACKPHY_AC_IOCTL2_vref_lpbkmode_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_phazmeter_in : 16;
        unsigned int acctl_phazmeter_status : 16;
    } reg;
} SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_in_START (0)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_in_END (15)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_status_START (16)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_odt_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int acctl_odt1_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_AC_ACCMDBDL0_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt_bdl_START (0)
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt_bdl_END (6)
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt1_bdl_START (16)
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_reset_bdl : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_HIPACKPHY_AC_ACCMDBDL2_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCMDBDL2_acctl_reset_bdl_START (0)
#define SOC_HIPACKPHY_AC_ACCMDBDL2_acctl_reset_bdl_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_cke_bdl : 7;
        unsigned int reserved_0 : 9;
        unsigned int acctl_cke1_bdl : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_HIPACKPHY_AC_ACCMDBDL4_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke_bdl_START (0)
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke_bdl_END (6)
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke1_bdl_START (16)
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke1_bdl_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_dramclk0_bdl : 7;
        unsigned int reserved_0 : 1;
        unsigned int acctl_dramclk1_bdl : 7;
        unsigned int reserved_1 : 1;
        unsigned int acctl_refclk_bdl : 5;
        unsigned int reserved_2 : 3;
        unsigned int acctl_fbclk_bdl : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_HIPACKPHY_AC_ACCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk0_bdl_START (0)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk0_bdl_END (6)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk1_bdl_START (8)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk1_bdl_END (14)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_refclk_bdl_START (16)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_refclk_bdl_END (20)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_fbclk_bdl_START (24)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_fbclk_bdl_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 3;
        unsigned int acctl_dramclk_h : 1;
        unsigned int acctl_dramclk_l : 1;
        unsigned int acctl_lvdqclkdiv2 : 1;
        unsigned int acctl_bufphyclk_div2 : 1;
        unsigned int acctl_byp_clk_gated_dis : 1;
        unsigned int acctl_byp_ck90_cmd_code : 18;
        unsigned int acctl_reg_reset_pin_sync_mode : 1;
        unsigned int acctl_reg_sel_pos_rx : 1;
        unsigned int acctl_ppfifo_ptr_en : 1;
        unsigned int acctl_sync_ppfifo_ptr : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL0_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_h_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_h_END (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_l_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_l_END (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_lvdqclkdiv2_START (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_lvdqclkdiv2_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_bufphyclk_div2_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_bufphyclk_div2_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_clk_gated_dis_START (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_clk_gated_dis_END (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_ck90_cmd_code_START (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_ck90_cmd_code_END (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_reset_pin_sync_mode_START (26)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_reset_pin_sync_mode_END (26)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_sel_pos_rx_START (27)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_sel_pos_rx_END (27)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_ppfifo_ptr_en_START (28)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_ppfifo_ptr_en_END (28)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_sync_ppfifo_ptr_START (29)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_sync_ppfifo_ptr_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_dram1sel_reset : 1;
        unsigned int acctl_dram1sel_cs : 1;
        unsigned int acctl_dram1sel_cke : 1;
        unsigned int acctl_dram1sel_odt : 1;
        unsigned int acctl_dram1sel_ras : 1;
        unsigned int acctl_dram1sel_cas : 1;
        unsigned int acctl_dram1sel_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int acctl_dram1sel_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int acctl_dram1sel_addr : 16;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL1_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_reset_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_reset_END (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cs_START (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cs_END (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cke_START (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cke_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_odt_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_odt_END (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ras_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ras_END (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cas_START (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cas_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_we_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_we_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ba_START (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ba_END (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_addr_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_sdrsel_reset : 1;
        unsigned int acctl_sdrsel_cs : 1;
        unsigned int acctl_sdrsel_cke : 1;
        unsigned int acctl_sdrsel_odt : 1;
        unsigned int acctl_sdrsel_ras : 1;
        unsigned int acctl_sdrsel_cas : 1;
        unsigned int acctl_sdrsel_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int acctl_sdrsel_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int acctl_sdrsel_addr : 16;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL2_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_reset_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_reset_END (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cs_START (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cs_END (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cke_START (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cke_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_odt_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_odt_END (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ras_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ras_END (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cas_START (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cas_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_we_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_we_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ba_START (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ba_END (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_addr_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_posedge_reset : 1;
        unsigned int acctl_posedge_cs : 1;
        unsigned int acctl_posedge_cke : 1;
        unsigned int acctl_posedge_odt : 1;
        unsigned int acctl_posedge_ras : 1;
        unsigned int acctl_posedge_cas : 1;
        unsigned int acctl_posedge_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int acctl_posedge_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int acctl_posedge_addr : 16;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL3_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_reset_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_reset_END (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cs_START (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cs_END (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cke_START (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cke_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_odt_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_odt_END (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ras_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ras_END (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cas_START (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cas_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_we_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_we_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ba_START (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ba_END (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_addr_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_timing2t_reset : 1;
        unsigned int acctl_timing2t_cs : 1;
        unsigned int acctl_timing2t_cke : 1;
        unsigned int acctl_timing2t_odt : 1;
        unsigned int acctl_timing2t_ras : 1;
        unsigned int acctl_timing2t_cas : 1;
        unsigned int acctl_timing2t_we : 1;
        unsigned int reserved_0 : 1;
        unsigned int acctl_timing2t_ba : 3;
        unsigned int reserved_1 : 5;
        unsigned int acctl_timing2t_addr : 16;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL4_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_reset_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_reset_END (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cs_START (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cs_END (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cke_START (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cke_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_odt_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_odt_END (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ras_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ras_END (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cas_START (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cas_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_we_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_we_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ba_START (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ba_END (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_addr_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_clk1x_dramclk0 : 3;
        unsigned int reserved_0 : 1;
        unsigned int acctl_clk1x_dramclk1 : 3;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 1;
        unsigned int acctl_clk1x_cmd2t : 3;
        unsigned int reserved_4 : 1;
        unsigned int acctl_clk1x_cmd1t : 3;
        unsigned int reserved_5 : 1;
        unsigned int acctl_clk1x_mclk : 3;
        unsigned int reserved_6 : 9;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL5_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk0_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk0_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk1_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk1_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd2t_START (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd2t_END (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd1t_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd1t_END (18)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_mclk_START (20)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_mclk_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_clk2x_dramclk0 : 3;
        unsigned int reserved_0 : 1;
        unsigned int acctl_clk2x_dramclk1 : 3;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 1;
        unsigned int acctl_clk2x_cmd2t : 3;
        unsigned int reserved_4 : 1;
        unsigned int acctl_clk2x_cmd1t : 3;
        unsigned int reserved_5 : 1;
        unsigned int acctl_clk2x_mclk : 3;
        unsigned int reserved_6 : 9;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL6_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk0_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk0_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk1_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk1_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd2t_START (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd2t_END (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd1t_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd1t_END (18)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_mclk_START (20)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_mclk_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 3;
        unsigned int acctl_ck0p_mclk : 3;
        unsigned int acctl_ck1p_dclk0 : 3;
        unsigned int acctl_ck2p_dclk1 : 3;
        unsigned int acctl_ck3p_cmd1t : 3;
        unsigned int reserved_1 : 8;
        unsigned int acctl_halft_cmd1t : 1;
        unsigned int acctl_halft_dramclk1 : 1;
        unsigned int acctl_halft_dramclk0 : 1;
        unsigned int cmd1t2t_sel : 1;
        unsigned int reserved_2 : 5;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL7_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck0p_mclk_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck0p_mclk_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck1p_dclk0_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck1p_dclk0_END (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck2p_dclk1_START (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck2p_dclk1_END (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck3p_cmd1t_START (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck3p_cmd1t_END (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_cmd1t_START (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_cmd1t_END (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk1_START (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk1_END (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk0_START (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk0_END (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_cmd1t2t_sel_START (26)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_cmd1t2t_sel_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acdbg_rdcnt : 6;
        unsigned int reserved_0 : 2;
        unsigned int acctl_deskew_regread : 1;
        unsigned int reserved_1 : 7;
        unsigned int acdbg_config : 4;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_HIPACKPHY_AC_ACDEBUG_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_rdcnt_START (0)
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_rdcnt_END (5)
#define SOC_HIPACKPHY_AC_ACDEBUG_acctl_deskew_regread_START (8)
#define SOC_HIPACKPHY_AC_ACDEBUG_acctl_deskew_regread_END (8)
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_config_START (16)
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_config_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_rsvdctrl : 32;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYRSVDC_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYRSVDC_acctl_rsvdctrl_START (0)
#define SOC_HIPACKPHY_AC_ACPHYRSVDC_acctl_rsvdctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_rsvdstatus : 32;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYRSVDS_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYRSVDS_acctl_rsvdstatus_START (0)
#define SOC_HIPACKPHY_AC_ACPHYRSVDS_acctl_rsvdstatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_dq1_dcc : 3;
        unsigned int acctl_dq0_dcc : 3;
        unsigned int acctl_dqs1_dcc : 3;
        unsigned int acctl_dqs0_dcc : 3;
        unsigned int acctl_mclk_dcc : 3;
        unsigned int reserved_0 : 1;
        unsigned int acctl_dq1_dcc_byt1 : 3;
        unsigned int acctl_dq0_dcc_byt1 : 3;
        unsigned int acctl_dqs1_dcc_byt1 : 3;
        unsigned int acctl_dqs0_dcc_byt1 : 3;
        unsigned int acctl_mclk_dcc_byt1 : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYDCC_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_START (0)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_END (2)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_START (3)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_END (5)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_START (6)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_END (8)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_START (9)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_END (11)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_START (12)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_END (14)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_byt1_START (16)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_byt1_END (18)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_byt1_START (19)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_byt1_END (21)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_byt1_START (22)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_byt1_END (24)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_byt1_START (25)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_byt1_END (27)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_byt1_START (28)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_byt1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_sdrsel_cs1 : 1;
        unsigned int acctl_sdrsel_cke1 : 1;
        unsigned int acctl_sdrsel_odt1 : 1;
        unsigned int acctl_posedge_cs1 : 1;
        unsigned int acctl_posedge_cke1 : 1;
        unsigned int acctl_posedge_odt1 : 1;
        unsigned int acctl_dram1sel_cs1 : 1;
        unsigned int acctl_dram1sel_cke1 : 1;
        unsigned int acctl_dram1sel_odt1 : 1;
        unsigned int acctl_timing2t_cs1 : 1;
        unsigned int acctl_timing2t_cke1 : 1;
        unsigned int acctl_timing2t_odt1 : 1;
        unsigned int reserved : 20;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL9_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cs1_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cs1_END (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cke1_START (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cke1_END (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_odt1_START (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_odt1_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cs1_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cs1_END (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cke1_START (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cke1_END (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_odt1_START (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_odt1_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cs1_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cs1_END (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cke1_START (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cke1_END (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_odt1_START (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_odt1_END (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cs1_START (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cs1_END (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cke1_START (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cke1_END (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_odt1_START (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_odt1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_clk1x_dramclk0_byt1 : 3;
        unsigned int acctl_clk1x_dramclk1_byt1 : 3;
        unsigned int acctl_clk1x_cmd2t_byt1 : 3;
        unsigned int acctl_clk1x_cmd1t_byt1 : 3;
        unsigned int acctl_clk1x_mclk_byt1 : 3;
        unsigned int reserved_0 : 1;
        unsigned int acctl_clk2x_dramclk0_byt1 : 3;
        unsigned int acctl_clk2x_dramclk1_byt1 : 3;
        unsigned int acctl_clk2x_cmd2t_byt1 : 3;
        unsigned int acctl_clk2x_cmd1t_byt1 : 3;
        unsigned int acctl_clk2x_mclk_byt1 : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL10_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk0_byt1_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk0_byt1_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk1_byt1_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk1_byt1_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd2t_byt1_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd2t_byt1_END (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd1t_byt1_START (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd1t_byt1_END (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_mclk_byt1_START (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_mclk_byt1_END (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk0_byt1_START (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk0_byt1_END (18)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk1_byt1_START (19)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk1_byt1_END (21)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd2t_byt1_START (22)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd2t_byt1_END (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd1t_byt1_START (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd1t_byt1_END (27)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_mclk_byt1_START (28)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_mclk_byt1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_ck1p_dclk0_byt1 : 3;
        unsigned int acctl_ck2p_dclk1_byt1 : 3;
        unsigned int acctl_ck3p_cmd1t_byt1 : 3;
        unsigned int acctl_ck4p_cmd2t_byt1 : 3;
        unsigned int reserved_0 : 11;
        unsigned int acctl_reg_byone_cmdr1t_sel : 1;
        unsigned int acctl_reg_cmd_byt1_phsel : 4;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL11_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck1p_dclk0_byt1_START (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck1p_dclk0_byt1_END (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck2p_dclk1_byt1_START (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck2p_dclk1_byt1_END (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck3p_cmd1t_byt1_START (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck3p_cmd1t_byt1_END (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck4p_cmd2t_byt1_START (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck4p_cmd2t_byt1_END (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_byone_cmdr1t_sel_START (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_byone_cmdr1t_sel_END (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_cmd_byt1_phsel_START (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_cmd_byt1_phsel_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac1t_ioctl_rdsel_p : 4;
        unsigned int ac1t_ioctl_rdsel_n : 4;
        unsigned int ac1t_ioctl_tdsel_p : 4;
        unsigned int ac1t_ioctl_tdsel_n : 4;
        unsigned int acctl_ioctl_zq_rx_mode : 2;
        unsigned int ioctl_reset_rx_mode0 : 1;
        unsigned int ioctl_reset_rx_mode1 : 1;
        unsigned int ioctl_cs_rx_mode0 : 2;
        unsigned int ioctl_cs_rx_mode1 : 2;
        unsigned int ioctl_ck_rx_mode0 : 1;
        unsigned int ioctl_ck_rx_mode1 : 1;
        unsigned int ioctl_cke_rx_mode0 : 2;
        unsigned int ioctl_cke_rx_mode1 : 2;
        unsigned int ioctl_odt_rx_mode0 : 1;
        unsigned int ioctl_odt_rx_mode1 : 1;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL3_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_p_START (0)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_p_END (3)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_n_START (4)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_n_END (7)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_p_START (8)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_p_END (11)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_n_START (12)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_n_END (15)
#define SOC_HIPACKPHY_AC_IOCTL3_acctl_ioctl_zq_rx_mode_START (16)
#define SOC_HIPACKPHY_AC_IOCTL3_acctl_ioctl_zq_rx_mode_END (17)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode0_START (18)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode0_END (18)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode1_START (19)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode1_END (19)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode0_START (20)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode0_END (21)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode1_START (22)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode1_END (23)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode0_START (24)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode0_END (24)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode1_START (25)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode1_END (25)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode0_START (26)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode0_END (27)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode1_START (28)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode1_END (29)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode0_START (30)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode0_END (30)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode1_START (31)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ck_ioctl_rdsel_p : 4;
        unsigned int ck_ioctl_rdsel_n : 4;
        unsigned int ck_ioctl_tdsel_p : 4;
        unsigned int ck_ioctl_tdsel_n : 4;
        unsigned int ac2t_ioctl_rdsel_p : 4;
        unsigned int ac2t_ioctl_rdsel_n : 4;
        unsigned int ac2t_ioctl_tdsel_p : 4;
        unsigned int ac2t_ioctl_tdsel_n : 4;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL4_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_p_START (0)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_p_END (3)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_n_START (4)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_n_END (7)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_p_START (8)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_p_END (11)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_n_START (12)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_n_END (15)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_p_START (16)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_p_END (19)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_n_START (20)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_n_END (23)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_p_START (24)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_p_END (27)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_n_START (28)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_reg_mclk_dcc_v : 5;
        unsigned int acctl_reg_mclk_dcc_h : 5;
        unsigned int acctl_reg_dq0_dcc_v : 5;
        unsigned int acctl_reg_dq0_dcc_h : 5;
        unsigned int acctl_reg_dq1_dcc_v : 5;
        unsigned int acctl_reg_dq1_dcc_h : 5;
        unsigned int reserved : 2;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYDCC1_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_v_START (0)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_v_END (4)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_h_START (5)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_h_END (9)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_v_START (10)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_v_END (14)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_h_START (15)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_h_END (19)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_v_START (20)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_v_END (24)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_h_START (25)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_h_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acctl_reg_dqs0_dcc_h : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_HIPACKPHY_AC_ACPHYDCC2_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYDCC2_acctl_reg_dqs0_dcc_h_START (0)
#define SOC_HIPACKPHY_AC_ACPHYDCC2_acctl_reg_dqs0_dcc_h_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 1;
        unsigned int ioctl_cs_sp : 2;
        unsigned int ioctl_ck_sp : 1;
        unsigned int ioctl_reset_sp : 1;
        unsigned int ioctl_cke_sp : 2;
        unsigned int ioctl_odt_sp : 1;
        unsigned int ioctl_addr_sp : 6;
        unsigned int ioctl_addr_v_sp : 2;
        unsigned int ioctl_addr_rx_mode0 : 6;
        unsigned int ioctl_addr_rx_mode1 : 6;
        unsigned int ioctl_addr_v_rx_mode0 : 2;
        unsigned int ioctl_addr_v_rx_mode1 : 2;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL5_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cs_sp_START (1)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cs_sp_END (2)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_ck_sp_START (3)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_ck_sp_END (3)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_reset_sp_START (4)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_reset_sp_END (4)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cke_sp_START (5)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cke_sp_END (6)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_odt_sp_START (7)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_odt_sp_END (7)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_sp_START (8)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_sp_END (13)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_sp_START (14)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_sp_END (15)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode0_START (16)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode0_END (21)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode1_START (22)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode1_END (27)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode0_START (28)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode0_END (29)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode1_START (30)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ioctl_zcal_lpddr4en : 1;
        unsigned int ioctl_reset_lpddr4en : 1;
        unsigned int ioctl_cs_lpddr4en : 2;
        unsigned int ioctl_ck_lpddr4en : 1;
        unsigned int ioctl_cke_lpddr4en : 2;
        unsigned int ioctl_odt_lpddr4en : 1;
        unsigned int ioctl_addr_lpddr4en : 6;
        unsigned int ioctl_addr_v_lpddr4en : 2;
        unsigned int ioctl_zcal_rdsel_n : 4;
        unsigned int ioctl_zcal_rdsel_p : 4;
        unsigned int ioctl_odtp : 1;
        unsigned int ioctl_odtn : 1;
        unsigned int ioctl_odtsel : 3;
        unsigned int reserved : 3;
    } reg;
} SOC_HIPACKPHY_AC_IOCTL6_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_lpddr4en_START (0)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_lpddr4en_END (0)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_reset_lpddr4en_START (1)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_reset_lpddr4en_END (1)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cs_lpddr4en_START (2)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cs_lpddr4en_END (3)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_ck_lpddr4en_START (4)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_ck_lpddr4en_END (4)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cke_lpddr4en_START (5)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cke_lpddr4en_END (6)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odt_lpddr4en_START (7)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odt_lpddr4en_END (7)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_lpddr4en_START (8)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_lpddr4en_END (13)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_v_lpddr4en_START (14)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_v_lpddr4en_END (15)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_n_START (16)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_n_END (19)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_p_START (20)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_p_END (23)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtp_START (24)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtp_END (24)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtn_START (25)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtn_END (25)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtsel_START (26)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtsel_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_HIPACKPHY_DX_PHYCTRL0_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int dxctl_ioctl_dxiopldn : 1;
        unsigned int top_ioctl_odt_oe : 1;
        unsigned int dxctl_ioctl_genvref_dram_refsel_2 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dxctl_ioctl_genvref_dram_refsel_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int dxctl_ioctl_genvref_dram_refsel_0 : 1;
        unsigned int reserved_3 : 1;
        unsigned int dxctl_ioctl_genvref_dram_pd : 1;
        unsigned int reserved_4 : 1;
        unsigned int dx_ioctl_ronsel : 3;
        unsigned int dqs_ioctl_ronsel : 3;
        unsigned int reserved_5 : 7;
        unsigned int ioctl_dq_odtn : 1;
        unsigned int ioctl_dq_odtp : 1;
        unsigned int ioctl_dqs_odtn : 1;
        unsigned int ioctl_dqs_odtp : 1;
        unsigned int reserved_6 : 1;
        unsigned int dqs_ioctl_odtsel : 3;
    } reg;
} SOC_HIPACKPHY_DX_IOCTL_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_dxiopldn_START (1)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_dxiopldn_END (1)
#define SOC_HIPACKPHY_DX_IOCTL_top_ioctl_odt_oe_START (2)
#define SOC_HIPACKPHY_DX_IOCTL_top_ioctl_odt_oe_END (2)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_2_START (3)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_2_END (3)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_1_START (5)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_1_END (5)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_0_START (7)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_0_END (7)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_pd_START (9)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_pd_END (9)
#define SOC_HIPACKPHY_DX_IOCTL_dx_ioctl_ronsel_START (11)
#define SOC_HIPACKPHY_DX_IOCTL_dx_ioctl_ronsel_END (13)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_ronsel_START (14)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_ronsel_END (16)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtn_START (24)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtn_END (24)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtp_START (25)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtp_END (25)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtn_START (26)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtn_END (26)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtp_START (27)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtp_END (27)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_odtsel_START (29)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_odtsel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_dqswap_sel : 16;
        unsigned int dxctl_dmswap_sel : 2;
        unsigned int reserved : 14;
    } reg;
} SOC_HIPACKPHY_DX_DQSSEL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dqswap_sel_START (0)
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dqswap_sel_END (15)
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dmswap_sel_START (16)
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dmswap_sel_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_ck0p_mclk : 3;
        unsigned int reserved_0 : 1;
        unsigned int dxctl_ck9p_cmd1t : 3;
        unsigned int reserved_1 : 1;
        unsigned int dxctl_ck10p_cmd2t : 3;
        unsigned int reserved_2 : 1;
        unsigned int dxctl_ck11p_dramclk : 3;
        unsigned int reserved_3 : 17;
    } reg;
} SOC_HIPACKPHY_DX_DXNCKCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck0p_mclk_START (0)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck0p_mclk_END (2)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck9p_cmd1t_START (4)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck9p_cmd1t_END (6)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck10p_cmd2t_START (8)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck10p_cmd2t_END (10)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck11p_dramclk_START (12)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck11p_dramclk_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_pll_test : 6;
        unsigned int reserved : 25;
        unsigned int dxctl_pll_lock : 1;
    } reg;
} SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_test_START (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_test_END (5)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_lock_START (31)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int ut_mode : 1;
        unsigned int dxctl_reg_dvalid_selfgen_en : 1;
        unsigned int reserved_1 : 10;
        unsigned int lpddr4_mode : 1;
        unsigned int phy_type : 2;
        unsigned int dxctl_reg_sel_pos_rx : 1;
        unsigned int reserved_2 : 3;
        unsigned int dxctl_reg_wfifo_mode : 1;
        unsigned int dxctl_reg_rdffsel_2rank_en : 1;
        unsigned int dxctl_ppfifo_ptr_en : 1;
        unsigned int dxctl_reg_phy_wdata_ranksw : 3;
        unsigned int wfifo_dxctl_gcken : 1;
        unsigned int wfifo_dxctl_passthrough : 1;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_HIPACKPHY_DX_PHYCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYCTRL2_ut_mode_START (4)
#define SOC_HIPACKPHY_DX_PHYCTRL2_ut_mode_END (4)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_dvalid_selfgen_en_START (5)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_dvalid_selfgen_en_END (5)
#define SOC_HIPACKPHY_DX_PHYCTRL2_lpddr4_mode_START (16)
#define SOC_HIPACKPHY_DX_PHYCTRL2_lpddr4_mode_END (16)
#define SOC_HIPACKPHY_DX_PHYCTRL2_phy_type_START (17)
#define SOC_HIPACKPHY_DX_PHYCTRL2_phy_type_END (18)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_sel_pos_rx_START (19)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_sel_pos_rx_END (19)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_wfifo_mode_START (23)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_wfifo_mode_END (23)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_rdffsel_2rank_en_START (24)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_rdffsel_2rank_en_END (24)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_ppfifo_ptr_en_START (25)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_ppfifo_ptr_en_END (25)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_phy_wdata_ranksw_START (26)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_phy_wdata_ranksw_END (28)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_gcken_START (29)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_gcken_END (29)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_passthrough_START (30)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_passthrough_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_ioctl_genvref_range_2 : 2;
        unsigned int reserved_0 : 4;
        unsigned int dxctl_odt_ioctl_rdsel_p : 3;
        unsigned int dxctl_odt_ioctl_rdsel_n : 3;
        unsigned int dxctl_ioctl_genvref_pd : 2;
        unsigned int reserved_1 : 4;
        unsigned int dxctl_ioctl_genvref_dram_range_2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int dxctl_ioctl_genvref_dram_range_1 : 1;
        unsigned int reserved_3 : 1;
        unsigned int dxctl_ioctl_genvref_dram_range_0 : 1;
        unsigned int reserved_4 : 1;
        unsigned int dxctl_ioctl_squeach_pd : 2;
        unsigned int reserved_5 : 2;
        unsigned int dxctl_odt_ioctl_ronsel : 3;
        unsigned int dxctl_ioctl_odt_iopldn : 1;
    } reg;
} SOC_HIPACKPHY_DX_IOCTL1_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_range_2_START (0)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_range_2_END (1)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_p_START (6)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_p_END (8)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_n_START (9)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_n_END (11)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_pd_START (12)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_pd_END (13)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_2_START (18)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_2_END (18)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_1_START (20)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_1_END (20)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_0_START (22)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_0_END (22)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_squeach_pd_START (24)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_squeach_pd_END (25)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_ronsel_START (28)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_ronsel_END (30)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_odt_iopldn_START (31)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_odt_iopldn_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_ioctl_genvref_range_0 : 2;
        unsigned int reserved_0 : 4;
        unsigned int dxctl_ioctl_genvref_range_1 : 2;
        unsigned int reserved_1 : 4;
        unsigned int dxctl_ioctl_genvref_refsel_0 : 2;
        unsigned int reserved_2 : 4;
        unsigned int dxctl_ioctl_genvref_refsel_1 : 2;
        unsigned int reserved_3 : 4;
        unsigned int dxctl_ioctl_genvref_refsel_2 : 2;
        unsigned int reserved_4 : 1;
        unsigned int dq_vref_sel : 1;
        unsigned int ioctl_dq_sp : 1;
        unsigned int ioctl_dq_lpddr4en : 1;
        unsigned int ioctl_dq_rx_mode0 : 1;
        unsigned int ioctl_dq_rx_mode1 : 1;
    } reg;
} SOC_HIPACKPHY_DX_IOCTL2_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_0_START (0)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_0_END (1)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_1_START (6)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_1_END (7)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_0_START (12)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_0_END (13)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_1_START (18)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_1_END (19)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_2_START (24)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_2_END (25)
#define SOC_HIPACKPHY_DX_IOCTL2_dq_vref_sel_START (27)
#define SOC_HIPACKPHY_DX_IOCTL2_dq_vref_sel_END (27)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_sp_START (28)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_sp_END (28)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_lpddr4en_START (29)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_lpddr4en_END (29)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode0_START (30)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode0_END (30)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode1_START (31)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl__pll_bp_refpfd : 1;
        unsigned int reserved_0 : 1;
        unsigned int dxctl__pll_bp_refvco : 1;
        unsigned int reserved_1 : 1;
        unsigned int dxctl__pll_enphsel : 1;
        unsigned int reserved_2 : 1;
        unsigned int dxctl__pll_en_cal : 1;
        unsigned int reserved_3 : 1;
        unsigned int dxctl__pll_initsel : 1;
        unsigned int reserved_4 : 1;
        unsigned int dxctl__pll_lockt_sel : 1;
        unsigned int reserved_5 : 1;
        unsigned int dxctl__pll_fopetestfb : 1;
        unsigned int reserved_6 : 1;
        unsigned int dxctl__pll_fopetestref : 1;
        unsigned int reserved_7 : 1;
        unsigned int dxctl_pll_lockin : 1;
        unsigned int reserved_8 : 15;
    } reg;
} SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refpfd_START (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refpfd_END (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refvco_START (2)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refvco_END (2)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_enphsel_START (4)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_enphsel_END (4)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_en_cal_START (6)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_en_cal_END (6)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_initsel_START (8)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_initsel_END (8)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_lockt_sel_START (10)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_lockt_sel_END (10)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestfb_START (12)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestfb_END (12)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestref_START (14)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestref_END (14)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl_pll_lockin_START (16)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl_pll_lockin_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_phazmeter_in : 16;
        unsigned int dxctl_phazmeter_status : 16;
    } reg;
} SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_in_START (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_in_END (15)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_status_START (16)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_fbclk_bdl : 4;
        unsigned int reserved_0 : 12;
        unsigned int dxctl_refclk_bdl : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_HIPACKPHY_DX_DXNCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_fbclk_bdl_START (0)
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_fbclk_bdl_END (3)
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_refclk_bdl_START (16)
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_refclk_bdl_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int dxctl_pll_testen : 1;
        unsigned int dxctl_pll_init : 1;
        unsigned int dxctl_pll_cpi : 3;
        unsigned int dxctl_pll_sp : 2;
        unsigned int reserved_1 : 1;
        unsigned int dxctl_pll_lt : 2;
        unsigned int reserved_2 : 20;
    } reg;
} SOC_HIPACKPHY_DX_DXPHYCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_testen_START (2)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_testen_END (2)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_init_START (3)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_init_END (3)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_cpi_START (4)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_cpi_END (6)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_sp_START (7)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_sp_END (8)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_lt_START (10)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_lt_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_rxn_2nd_dq : 8;
        unsigned int dxctl_rxp_2nd_dq : 8;
        unsigned int reserved_0 : 1;
        unsigned int dxctl_dqs_l : 1;
        unsigned int dxctl_dqs_h : 1;
        unsigned int dxctl_rxn_2nd_dm : 1;
        unsigned int dxctl_rxp_2nd_dm : 1;
        unsigned int dxctl_dqsgatedla : 1;
        unsigned int dxctl_lvdqclkdiv2 : 1;
        unsigned int dxctl_bufphyclkdiv2 : 1;
        unsigned int dxctl_reg_sel_lvdqsclkdiv2 : 1;
        unsigned int dxctl_reg_wpst_1p5ten : 1;
        unsigned int dxctl_ptrgated_en : 1;
        unsigned int dxctl_reg_dqsg_toggle_en : 1;
        unsigned int dxctl_reg_dqsg_extend_en_dqs : 1;
        unsigned int dxctl_reg_dqsg_extend_2t_dqs : 1;
        unsigned int dxctl_reg_rxfifo_r1t_sel_dqs : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dq_START (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dq_END (7)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dq_START (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dq_END (15)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_l_START (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_l_END (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_h_START (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_h_END (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dm_START (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dm_END (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dm_START (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dm_END (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqsgatedla_START (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqsgatedla_END (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_lvdqclkdiv2_START (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_lvdqclkdiv2_END (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_bufphyclkdiv2_START (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_bufphyclkdiv2_END (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_sel_lvdqsclkdiv2_START (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_sel_lvdqsclkdiv2_END (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_wpst_1p5ten_START (25)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_wpst_1p5ten_END (25)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_ptrgated_en_START (26)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_ptrgated_en_END (26)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_toggle_en_START (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_toggle_en_END (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_en_dqs_START (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_en_dqs_END (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_2t_dqs_START (29)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_2t_dqs_END (29)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_rxfifo_r1t_sel_dqs_START (30)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_rxfifo_r1t_sel_dqs_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_mclk2x : 3;
        unsigned int reserved_0 : 1;
        unsigned int dxctl_mclk1x : 3;
        unsigned int reserved_1 : 1;
        unsigned int dxctl_dqsclk2x : 3;
        unsigned int reserved_2 : 1;
        unsigned int dxctl_dqsclk1x : 3;
        unsigned int reserved_3 : 1;
        unsigned int dxctl_dqsgclk2x : 3;
        unsigned int reserved_4 : 1;
        unsigned int dxctl_dqsgclk1x : 3;
        unsigned int reserved_5 : 1;
        unsigned int dxctl_dqclk2x : 3;
        unsigned int reserved_6 : 1;
        unsigned int dxctl_dqclk1x : 3;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk2x_START (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk2x_END (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk1x_START (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk1x_END (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk2x_START (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk2x_END (10)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk1x_START (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk1x_END (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk2x_START (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk2x_END (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk1x_START (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk1x_END (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk2x_START (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk2x_END (26)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk1x_START (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk1x_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxdbg_dqs_cb : 3;
        unsigned int dxdbg_dqs_ca : 3;
        unsigned int dxdbg_dqs_rdcnt : 4;
        unsigned int dxdbg_dqs_s2b : 1;
        unsigned int dxdbg_dqs_s2a : 1;
        unsigned int dxdbg_dqs_s1b : 1;
        unsigned int dxdbg_dqs_s1a : 1;
        unsigned int dxdbg_dqs_s0b : 1;
        unsigned int dxdbg_dqs_s0a : 1;
        unsigned int dxctl_rlresult_gds_dqs : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_HIPACKPHY_DX_DXDEBUG0_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_cb_START (0)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_cb_END (2)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_ca_START (3)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_ca_END (5)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_rdcnt_START (6)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_rdcnt_END (9)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2b_START (10)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2b_END (10)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2a_START (11)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2a_END (11)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1b_START (12)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1b_END (12)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1a_START (13)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1a_END (13)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0b_START (14)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0b_END (14)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0a_START (15)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0a_END (15)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxctl_rlresult_gds_dqs_START (16)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxctl_rlresult_gds_dqs_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_rsvdctrl : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HIPACKPHY_DX_DXPHYRSVD_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXPHYRSVD_dxctl_rsvdctrl_START (0)
#define SOC_HIPACKPHY_DX_DXPHYRSVD_dxctl_rsvdctrl_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bufresetcontn_gated_dqsgerror : 1;
        unsigned int bufresetcontn_gated_tdc : 1;
        unsigned int reg_gds_r1t_sel : 1;
        unsigned int reg_odten_gated : 1;
        unsigned int reg_dummypad_use : 1;
        unsigned int reg_dynamic_pupden : 1;
        unsigned int reg_sel_halft_gated : 1;
        unsigned int reg_dqsglat1t_en : 1;
        unsigned int reg_squeach_en : 1;
        unsigned int reg_dqsg_tx_2path : 1;
        unsigned int reg_oe_extend1t_en : 1;
        unsigned int dxctl_reg_perbit_mode_en : 1;
        unsigned int dxctl_reg_phy_dqsdly_stop_enable : 1;
        unsigned int dxctl_reg_phy_dqsg_stop_enable : 1;
        unsigned int dxctl_reg_dqsdly_demux_gated_1 : 1;
        unsigned int dxctl_reg_dqsgdly_demux_gated_0 : 1;
        unsigned int dxctl_reg_post_margin_gated_1 : 1;
        unsigned int dxctl_reg_post_margin_gated_0 : 1;
        unsigned int dxctl_reg_pre_margin_gated_1 : 1;
        unsigned int dxctl_reg_pre_margin_gated_0 : 1;
        unsigned int dxctl_reg_pn_dlyen : 1;
        unsigned int dxctl_reset_n_phyupdate_req : 1;
        unsigned int dxctl_reg_tspc_sel : 1;
        unsigned int dxctl_reg_sel_combout : 1;
        unsigned int dxctl_reg_post_gateden : 1;
        unsigned int reserved_0 : 2;
        unsigned int dxctl_byp_clk_gated_dis : 1;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_dqsgerror_START (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_dqsgerror_END (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_tdc_START (1)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_tdc_END (1)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_gds_r1t_sel_START (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_gds_r1t_sel_END (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_odten_gated_START (3)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_odten_gated_END (3)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dummypad_use_START (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dummypad_use_END (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dynamic_pupden_START (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dynamic_pupden_END (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_sel_halft_gated_START (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_sel_halft_gated_END (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsglat1t_en_START (7)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsglat1t_en_END (7)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_squeach_en_START (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_squeach_en_END (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsg_tx_2path_START (9)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsg_tx_2path_END (9)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_oe_extend1t_en_START (10)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_oe_extend1t_en_END (10)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_perbit_mode_en_START (11)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_perbit_mode_en_END (11)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsdly_stop_enable_START (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsdly_stop_enable_END (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsg_stop_enable_START (13)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsg_stop_enable_END (13)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsdly_demux_gated_1_START (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsdly_demux_gated_1_END (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsgdly_demux_gated_0_START (15)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsgdly_demux_gated_0_END (15)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_1_START (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_1_END (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_0_START (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_0_END (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_1_START (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_1_END (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_0_START (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_0_END (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pn_dlyen_START (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pn_dlyen_END (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reset_n_phyupdate_req_START (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reset_n_phyupdate_req_END (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_tspc_sel_START (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_tspc_sel_END (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_sel_combout_START (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_sel_combout_END (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_gateden_START (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_gateden_END (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_byp_clk_gated_dis_START (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_byp_clk_gated_dis_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_dbg_config : 4;
        unsigned int dxctl_deskew_regread : 1;
        unsigned int reserved_0 : 3;
        unsigned int dxctl_reg_dbg_fotest : 1;
        unsigned int dxctl_reg_dbg_dqsdly_odtpad : 1;
        unsigned int dxctl_reg_dbg_gated_n : 1;
        unsigned int reserved_1 : 21;
    } reg;
} SOC_HIPACKPHY_DX_DXDEBUGCONFIG_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_dbg_config_START (0)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_dbg_config_END (3)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_deskew_regread_START (4)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_deskew_regread_END (4)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_fotest_START (8)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_fotest_END (8)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_dqsdly_odtpad_START (9)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_dqsdly_odtpad_END (9)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_gated_n_START (10)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_gated_n_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_dq_dcc : 5;
        unsigned int dxctl_dqsg_dcc : 5;
        unsigned int dxctl_dqs_dcc : 5;
        unsigned int dxctl_mclk_dcc : 5;
        unsigned int dxctl_byp_ck90_data_code_dqs : 9;
        unsigned int reserved : 3;
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dq_dcc_START (0)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dq_dcc_END (4)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqsg_dcc_START (5)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqsg_dcc_END (9)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqs_dcc_START (10)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqs_dcc_END (14)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_mclk_dcc_START (15)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_mclk_dcc_END (19)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_byp_ck90_data_code_dqs_START (20)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_byp_ck90_data_code_dqs_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_dqsg_extdly_dqs : 3;
        unsigned int reserved_0 : 9;
        unsigned int dxctl_rxext_dly : 3;
        unsigned int reserved_1 : 1;
        unsigned int dxctl_dqsdly_demux_code : 3;
        unsigned int dxctl_post_margin_code : 3;
        unsigned int dxctl_pre_margin_code : 3;
        unsigned int dxctl_dqsgclk2x_rank1 : 3;
        unsigned int dxctl_dqsgclk1x_rank1 : 3;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL3_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsg_extdly_dqs_START (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsg_extdly_dqs_END (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_rxext_dly_START (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_rxext_dly_END (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsdly_demux_code_START (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsdly_demux_code_END (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_post_margin_code_START (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_post_margin_code_END (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_pre_margin_code_START (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_pre_margin_code_END (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk2x_rank1_START (25)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk2x_rank1_END (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk1x_rank1_START (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk1x_rank1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_reg_clkgated_dis : 4;
        unsigned int dxctl_reg_dbgmode_byt1_sel : 1;
        unsigned int dxctl_reg_dbgmode_sel : 1;
        unsigned int dxctl_reg_rst_n : 1;
        unsigned int reserved_0 : 1;
        unsigned int dxctl_reg_asy_cmd_decode_sel : 1;
        unsigned int reserved_1 : 3;
        unsigned int dxctl_pack_cfg_rs_passthrough : 1;
        unsigned int reserved_2 : 3;
        unsigned int dxctl_reg_clkgated_en_dqs : 1;
        unsigned int reserved_3 : 3;
        unsigned int dxctl_reg_1rank_only_en_dqs : 1;
        unsigned int reserved_4 : 3;
        unsigned int dxctl_reg_dqsg_toggle_code90 : 6;
        unsigned int reserved_5 : 2;
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL4_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_dis_START (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_dis_END (3)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_byt1_sel_START (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_byt1_sel_END (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_sel_START (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_sel_END (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_rst_n_START (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_rst_n_END (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_asy_cmd_decode_sel_START (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_asy_cmd_decode_sel_END (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_pack_cfg_rs_passthrough_START (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_pack_cfg_rs_passthrough_END (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_en_dqs_START (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_en_dqs_END (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_1rank_only_en_dqs_START (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_1rank_only_en_dqs_END (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dqsg_toggle_code90_START (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dqsg_toggle_code90_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ioctl_dqs_rx_mode0 : 1;
        unsigned int ioctl_dqs_rx_mode1 : 1;
        unsigned int ioctl_dm_rx_mode0 : 1;
        unsigned int ioctl_dm_rx_mode1 : 1;
        unsigned int ioctl_dummy_rx_mode0 : 1;
        unsigned int ioctl_dummy_rx_mode1 : 1;
        unsigned int reserved_0 : 2;
        unsigned int dxctl_ioctl_dm_sp : 1;
        unsigned int dxctl_ioctl_dummy_sp : 1;
        unsigned int dxctl_ioctl_dqs_sp : 1;
        unsigned int dxctl_ioctl_diffdqs_en : 1;
        unsigned int ioctl_dqs_lpddr4en : 1;
        unsigned int ioctl_dm_lpddr4en : 1;
        unsigned int ioctl_dummy_lpddr4en : 1;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_HIPACKPHY_DX_IOCTL3_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode0_START (0)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode0_END (0)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode1_START (1)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode1_END (1)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode0_START (2)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode0_END (2)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode1_START (3)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode1_END (3)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode0_START (4)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode0_END (4)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode1_START (5)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode1_END (5)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dm_sp_START (8)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dm_sp_END (8)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dummy_sp_START (9)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dummy_sp_END (9)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dqs_sp_START (10)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dqs_sp_END (10)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_diffdqs_en_START (11)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_diffdqs_en_END (11)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_lpddr4en_START (12)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_lpddr4en_END (12)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_lpddr4en_START (13)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_lpddr4en_END (13)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_lpddr4en_START (14)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_lpddr4en_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqs_ioctl_rdsel_p : 4;
        unsigned int dqs_ioctl_rdsel_n : 4;
        unsigned int dqs_ioctl_tdsel_p : 4;
        unsigned int dqs_ioctl_tdsel_n : 4;
        unsigned int dx_ioctl_rdsel_p : 4;
        unsigned int dx_ioctl_rdsel_n : 4;
        unsigned int dx_ioctl_tdsel_p : 4;
        unsigned int dx_ioctl_tdsel_n : 4;
    } reg;
} SOC_HIPACKPHY_DX_IOCTL5_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_p_START (0)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_p_END (3)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_n_START (4)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_n_END (7)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_p_START (8)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_p_END (11)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_n_START (12)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_n_END (15)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_p_START (16)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_p_END (19)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_n_START (20)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_n_END (23)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_p_START (24)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_p_END (27)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_n_START (28)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_reg_rx_dcc_dq0 : 5;
        unsigned int dxctl_reg_rx_dcc_dq1 : 5;
        unsigned int dxctl_reg_rx_dcc_dq2 : 5;
        unsigned int dxctl_reg_rx_dcc_dq3 : 5;
        unsigned int dxctl_reg_rx_dcc_dm : 5;
        unsigned int reserved : 7;
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC1_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq0_START (0)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq0_END (4)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq1_START (5)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq1_END (9)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq2_START (10)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq2_END (14)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq3_START (15)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq3_END (19)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dm_START (20)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dm_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_reg_rx_dcc_dq4 : 5;
        unsigned int dxctl_reg_rx_dcc_dq5 : 5;
        unsigned int dxctl_reg_rx_dcc_dq6 : 5;
        unsigned int dxctl_reg_rx_dcc_dq7 : 5;
        unsigned int reserved : 12;
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC2_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq4_START (0)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq4_END (4)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq5_START (5)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq5_END (9)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq6_START (10)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq6_END (14)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq7_START (15)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq7_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_reg_tx_dcc_dq0 : 5;
        unsigned int dxctl_reg_tx_dcc_dq1 : 5;
        unsigned int dxctl_reg_tx_dcc_dq2 : 5;
        unsigned int dxctl_reg_tx_dcc_dq3 : 5;
        unsigned int dxctl_reg_tx_dcc_dm : 5;
        unsigned int dxctl_reg_tx_dcc_dqs : 5;
        unsigned int reserved : 2;
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC3_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq0_START (0)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq0_END (4)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq1_START (5)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq1_END (9)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq2_START (10)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq2_END (14)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq3_START (15)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq3_END (19)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dm_START (20)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dm_END (24)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dqs_START (25)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dqs_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dxctl_reg_tx_dcc_dq4 : 5;
        unsigned int dxctl_reg_tx_dcc_dq5 : 5;
        unsigned int dxctl_reg_tx_dcc_dq6 : 5;
        unsigned int dxctl_reg_tx_dcc_dq7 : 5;
        unsigned int reserved : 12;
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC4_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq4_START (0)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq4_END (4)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq5_START (5)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq5_END (9)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq6_START (10)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq6_END (14)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq7_START (15)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq7_END (19)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
