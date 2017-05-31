#ifndef __SOC_DDRC_DMC_INTERFACE_H__
#define __SOC_DDRC_DMC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_ADDR(base) ((base) + (0x000))
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_ADDR(base) ((base) + (0x004))
#define SOC_DDRC_DMC_DDRC_CTRL_DDRRST_ADDR(base) ((base) + (0x008))
#define SOC_DDRC_DMC_DDRC_CTRL_SFC_ADDR(base) ((base) + (0x00C))
#define SOC_DDRC_DMC_DDRC_CTRL_PERF_ADDR(base) ((base) + (0x010))
#define SOC_DDRC_DMC_DDRC_CTRL_MTEST_ADDR(base) ((base) + (0x014))
#define SOC_DDRC_DMC_DDRC_CTRL_MCLR_ADDR(base) ((base) + (0x018))
#define SOC_DDRC_DMC_DDRC_CFG_LP_ADDR(base) ((base) + (0x01C))
#define SOC_DDRC_DMC_DDRC_CFG_SREF_ADDR(base) ((base) + (0x020))
#define SOC_DDRC_DMC_DDRC_CFG_INIT_ADDR(base) ((base) + (0x024))
#define SOC_DDRC_DMC_DDRC_CFG_PD_ADDR(base) ((base) + (0x028))
#define SOC_DDRC_DMC_DDRC_CFG_AREF_ADDR(base) ((base) + (0x02C))
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ADDR(base) ((base) + (0x030))
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_ADDR(base) ((base) + (0x034))
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_ADDR(base) ((base) + (0x038))
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_ADDR(base) ((base) + (0x040))
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_ADDR(base) ((base) + (0x044))
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_ADDR(base) ((base) + (0x048))
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_ADDR(base) ((base) + (0x050))
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_ADDR(base) ((base) + (0x054))
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_ADDR(base) ((base) + (0x058))
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_ADDR(base) ((base) + (0x05C))
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_ADDR(base,rnks) ((base) + (0x060+0x4*(rnks)))
#define SOC_DDRC_DMC_DDRC_CFG_ODT_ADDR(base,rnks) ((base) + (0x0A0+0x4*(rnks)))
#define SOC_DDRC_DMC_DDRC_CFG_CA_ODT_ADDR(base) ((base) + (0x0E0))
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_ADDR(base) ((base) + (0x0F0))
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_ADDR(base) ((base) + (0x0F4))
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_ADDR(base) ((base) + (0x0F8))
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_ADDR(base) ((base) + (0x0FC))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_ADDR(base) ((base) + (0x100))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_ADDR(base) ((base) + (0x104))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_ADDR(base) ((base) + (0x108))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_ADDR(base) ((base) + (0x10C))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_ADDR(base) ((base) + (0x110))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_ADDR(base) ((base) + (0x114))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_ADDR(base) ((base) + (0x118))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_ADDR(base) ((base) + (0x11C))
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_ADDR(base) ((base) + (0x120))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_ADDR(base) ((base) + (0x124))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_ADDR(base) ((base) + (0x128))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_ADDR(base) ((base) + (0x12C))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_ADDR(base) ((base) + (0x130))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_ADDR(base) ((base) + (0x134))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_ADDR(base) ((base) + (0x138))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_ADDR(base) ((base) + (0x13C))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_ADDR(base) ((base) + (0x140))
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_ADDR(base) ((base) + (0x144))
#define SOC_DDRC_DMC_DDRC_CFG_BLDATA_ADDR(base) ((base) + (0x148))
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_ADDR(base) ((base) + (0x14C))
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_ADDR(base) ((base) + (0x150))
#define SOC_DDRC_DMC_DDRC_CFG_QOS_ADDR(base) ((base) + (0x154))
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_ADDR(base) ((base) + (0x158))
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_ADDR(base) ((base) + (0x15C))
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_ADDR(base) ((base) + (0x160))
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_ADDR(base) ((base) + (0x164))
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_ADDR(base) ((base) + (0x168))
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_ADDR(base) ((base) + (0x16C))
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_ADDR(base) ((base) + (0x170))
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_ADDR(base) ((base) + (0x174))
#define SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_ADDR(base) ((base) + (0x178))
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_ADDR(base) ((base) + (0x17C))
#define SOC_DDRC_DMC_DDRC_CFG_TRAIN_ADDR(base) ((base) + (0x180))
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_ADDR(base) ((base) + (0x184))
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_ADDR(base) ((base) + (0x188))
#define SOC_DDRC_DMC_DDRC_CFG_REC0_ADDR(base) ((base) + (0x190))
#define SOC_DDRC_DMC_DDRC_CFG_REC1_ADDR(base) ((base) + (0x194))
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ADDR(base) ((base) + (0x198))
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_ADDR(base) ((base) + (0x1A0))
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_ADDR(base) ((base) + (0x1A4))
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_ADDR(base) ((base) + (0x1A8))
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_ADDR(base) ((base) + (0x1AC))
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_ADDR(base) ((base) + (0x200))
#define SOC_DDRC_DMC_DDRC_CFG_AGING_ADDR(base) ((base) + (0x204))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_ADDR(base) ((base) + (0x208))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_ADDR(base) ((base) + (0x20C))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR(base) ((base) + (0x210))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_ADDR(base) ((base) + (0x214))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_ADDR(base) ((base) + (0x218))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_ADDR(base) ((base) + (0x21C))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_ADDR(base) ((base) + (0x220))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_ADDR(base) ((base) + (0x224))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_ADDR(base) ((base) + (0x228))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_ADDR(base) ((base) + (0x22C))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_ADDR(base) ((base) + (0x230))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_ADDR(base) ((base) + (0x234))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_ADDR(base) ((base) + (0x238))
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_ADDR(base) ((base) + (0x23C))
#define SOC_DDRC_DMC_DDRC_CFG_TMON_ADDR(base) ((base) + (0x240))
#define SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_ADDR(base) ((base) + (0x244))
#define SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_ADDR(base) ((base) + (0x248))
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_ADDR(base) ((base) + (0x250))
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR(base) ((base) + (0x254))
#define SOC_DDRC_DMC_DDRC_CFG_DATMIN_ADDR(base) ((base) + (0x258))
#define SOC_DDRC_DMC_DDRC_CFG_DATMAX_ADDR(base) ((base) + (0x25C))
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR(base) ((base) + (0x260))
#define SOC_DDRC_DMC_DDRC_CFG_CMDMIN_ADDR(base) ((base) + (0x264))
#define SOC_DDRC_DMC_DDRC_CFG_CMDMAX_ADDR(base) ((base) + (0x268))
#define SOC_DDRC_DMC_DDRC_CFG_PERF_ADDR(base) ((base) + (0x26C))
#define SOC_DDRC_DMC_DDRC_CFG_STAID_ADDR(base) ((base) + (0x270))
#define SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_ADDR(base) ((base) + (0x274))
#define SOC_DDRC_DMC_DDRC_CFG_DUM_EN_ADDR(base) ((base) + (0x278))
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_ADDR(base) ((base) + (0x27C))
#define SOC_DDRC_DMC_DDRC_INTMSK_ADDR(base) ((base) + (0x280))
#define SOC_DDRC_DMC_DDRC_RINT_ADDR(base) ((base) + (0x284))
#define SOC_DDRC_DMC_DDRC_INTSTS_ADDR(base) ((base) + (0x288))
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_ADDR(base) ((base) + (0x290))
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_ADDR(base) ((base) + (0x294))
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_ADDR(base) ((base) + (0x298))
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_ADDR(base) ((base) + (0x29C))
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_ADDR(base) ((base) + (0x2A0))
#define SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_ADDR(base) ((base) + (0x2A4))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_ADDR(base) ((base) + (0x2D0))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_ADDR(base) ((base) + (0x2D4))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_ADDR(base) ((base) + (0x2D8))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_ADDR(base) ((base) + (0x2DC))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_ADDR(base) ((base) + (0x2E0))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_ADDR(base) ((base) + (0x2E4))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_ADDR(base) ((base) + (0x2E8))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_ADDR(base) ((base) + (0x2EC))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_ADDR(base) ((base) + (0x2F0))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_ADDR(base) ((base) + (0x2F4))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_ADDR(base) ((base) + (0x2F8))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_ADDR(base) ((base) + (0x2FC))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_ADDR(base) ((base) + (0x300))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_ADDR(base) ((base) + (0x304))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_ADDR(base) ((base) + (0x308))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_ADDR(base) ((base) + (0x30C))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_ADDR(base) ((base) + (0x310))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_ADDR(base) ((base) + (0x314))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_ADDR(base) ((base) + (0x318))
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_ADDR(base) ((base) + (0x31C))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_ADDR(base) ((base) + (0x320))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_ADDR(base) ((base) + (0x324))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ID_ADDR(base) ((base) + (0x328))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_ADDR(base) ((base) + (0x330))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_ADDR(base) ((base) + (0x334))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_ADDR(base) ((base) + (0x338))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_ADDR(base) ((base) + (0x33C))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_ADDR(base) ((base) + (0x340))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_ADDR(base) ((base) + (0x344))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_ADDR(base) ((base) + (0x348))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_ADDR(base) ((base) + (0x34C))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_ADDR(base) ((base) + (0x350))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_ADDR(base) ((base) + (0x354))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_ADDR(base) ((base) + (0x358))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_ADDR(base) ((base) + (0x35C))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_ADDR(base) ((base) + (0x360))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_ADDR(base) ((base) + (0x364))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_ADDR(base) ((base) + (0x368))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_ADDR(base) ((base) + (0x36C))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_ADDR(base) ((base) + (0x370))
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_ADDR(base) ((base) + (0x374))
#define SOC_DDRC_DMC_DDRC_HIS_SERRCNT_ADDR(base) ((base) + (0x378))
#define SOC_DDRC_DMC_DDRC_HIS_MERRCNT_ADDR(base) ((base) + (0x37C))
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_ADDR(base) ((base) + (0x380))
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_ADDR(base) ((base) + (0x384))
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_ADDR(base) ((base) + (0x0388))
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_ADDR(base) ((base) + (0x038C))
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_ADDR(base) ((base) + (0x390))
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_ADDR(base) ((base) + (0x394))
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_ADDR(base) ((base) + (0x0398))
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_ADDR(base) ((base) + (0x039C))
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_ADDR(base) ((base) + (0x3A0))
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_ADDR(base) ((base) + (0x3A4))
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_ADDR(base) ((base) + (0x3A8))
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_ADDR(base) ((base) + (0x3AC))
#define SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_ADDR(base) ((base) + (0x3B0))
#define SOC_DDRC_DMC_DDRC_STAT_RPT_ADDR(base) ((base) + (0x3B4))
#define SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_ADDR(base) ((base) + (0x3B8))
#define SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_ADDR(base) ((base) + (0x3BC))
#define SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_ADDR(base) ((base) + (0x3C0))
#define SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_ADDR(base) ((base) + (0x3C4))
#define SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_ADDR(base) ((base) + (0x3C8))
#define SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_ADDR(base) ((base) + (0x3CC))
#define SOC_DDRC_DMC_DDRC_HIS_RW_CHG_ADDR(base) ((base) + (0x3D0))
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_ADDR(base) ((base) + (0x3E0))
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_ADDR(base) ((base) + (0x3F0))
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_ADDR(base) ((base) + (0x3F4))
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_ADDR(base) ((base) + (0x3F8))
#define SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_ADDR(base) ((base) + (0x3FC))
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_ADDR(base) ((base) + (0x400))
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_ADDR(base) ((base) + (0x404))
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_ADDR(base) ((base) + (0x40C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_ADDR(base) ((base) + (0x410))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_ADDR(base) ((base) + (0x414))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_ADDR(base) ((base) + (0x418))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_ADDR(base) ((base) + (0x41C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_ADDR(base) ((base) + (0x420))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_ADDR(base) ((base) + (0x424))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_ADDR(base) ((base) + (0x428))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_ADDR(base) ((base) + (0x42C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_ADDR(base) ((base) + (0x430))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_ADDR(base) ((base) + (0x434))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_ADDR(base) ((base) + (0x438))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_ADDR(base) ((base) + (0x43C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_ADDR(base) ((base) + (0x440))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_ADDR(base) ((base) + (0x444))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_ADDR(base) ((base) + (0x448))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_ADDR(base) ((base) + (0x44C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_ADDR(base) ((base) + (0x450))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_ADDR(base) ((base) + (0x454))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_ADDR(base) ((base) + (0x458))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_ADDR(base) ((base) + (0x45C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_ADDR(base) ((base) + (0x460))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_ADDR(base) ((base) + (0x464))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_ADDR(base) ((base) + (0x468))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_ADDR(base) ((base) + (0x46C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_ADDR(base) ((base) + (0x470))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_ADDR(base) ((base) + (0x474))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_ADDR(base) ((base) + (0x478))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_ADDR(base) ((base) + (0x47C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_ADDR(base) ((base) + (0x480))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_ADDR(base) ((base) + (0x484))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_ADDR(base) ((base) + (0x488))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_ADDR(base) ((base) + (0x48C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_ADDR(base) ((base) + (0x490))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_ADDR(base) ((base) + (0x494))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_ADDR(base) ((base) + (0x498))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_ADDR(base) ((base) + (0x49C))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_ADDR(base) ((base) + (0x4A0))
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_ADDR(base) ((base) + (0x4A4))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_ADDR(base) ((base) + (0x4A8))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_ADDR(base) ((base) + (0x4AC))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_ADDR(base) ((base) + (0x4B0))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_ADDR(base) ((base) + (0x4B4))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_ADDR(base) ((base) + (0x4B8))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_ADDR(base) ((base) + (0x4BC))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_ADDR(base) ((base) + (0x4C0))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_ADDR(base) ((base) + (0x4C4))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_ADDR(base) ((base) + (0x4C8))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_ADDR(base) ((base) + (0x4CC))
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_ADDR(base) ((base) + (0x4D0))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_ADDR(base) ((base) + (0x4D4))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_ADDR(base) ((base) + (0x4D8))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_ADDR(base) ((base) + (0x4DC))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_ADDR(base) ((base) + (0x4E0))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_ADDR(base) ((base) + (0x4E4))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_ADDR(base) ((base) + (0x4E8))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_ADDR(base) ((base) + (0x4EC))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_ADDR(base) ((base) + (0x4F0))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_ADDR(base) ((base) + (0x4F4))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_ADDR(base) ((base) + (0x4F8))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_ADDR(base) ((base) + (0x4FC))
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_ADDR(base) ((base) + (0x500))
#define SOC_DDRC_DMC_STAT12_ADDR(base) ((base) + (0x504))
#define SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_ADDR(base) ((base) + (0x508))
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_ADDR(base) ((base) + (0x510))
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_ADDR(base) ((base) + (0x514))
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_ADDR(base) ((base) + (0x518))
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_ADDR(base,rnks) ((base) + (0x520+0x4*(rnks)))
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_ADDR(base,blanes) ((base) + (0x580+0x8*(blanes)))
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_ADDR(base,blanes) ((base) + (0x584+0x8*(blanes)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sref_req : 1;
        unsigned int sref_done : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_SREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_req_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_req_END (0)
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_done_START (1)
#define SOC_DDRC_DMC_DDRC_CTRL_SREF_sref_done_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int init_req : 1;
        unsigned int dfi_init_start : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_INIT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_init_req_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_init_req_END (0)
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_dfi_init_start_START (1)
#define SOC_DDRC_DMC_DDRC_CTRL_INIT_dfi_init_start_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddr3_rst_n : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_DDRRST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_DDRRST_ddr3_rst_n_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_DDRRST_ddr3_rst_n_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_SFC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_SFC_cmd_req_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_SFC_cmd_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perf_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_PERF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_PERF_perf_en_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_PERF_perf_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_MTEST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_MTEST_mtest_start_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_MTEST_mtest_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CTRL_MCLR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CTRL_MCLR_mclr_start_START (0)
#define SOC_DDRC_DMC_DDRC_CTRL_MCLR_mclr_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lp_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int lp_soft_en : 1;
        unsigned int lp_ack : 1;
        unsigned int reserved_1 : 2;
        unsigned int tlp_wakeup : 4;
        unsigned int tlp_resp : 4;
        unsigned int t_wcke : 4;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_LP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_en_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_soft_en_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_soft_en_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_ack_START (5)
#define SOC_DDRC_DMC_DDRC_CFG_LP_lp_ack_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_wakeup_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_wakeup_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_resp_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_LP_tlp_resp_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_LP_t_wcke_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_LP_t_wcke_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sref_cc : 1;
        unsigned int asref_fast_wakeup : 1;
        unsigned int sref_pd : 1;
        unsigned int init_xsref : 1;
        unsigned int sref_odis : 1;
        unsigned int reserved_0 : 3;
        unsigned int clk_switch : 1;
        unsigned int reserved_1 : 3;
        unsigned int sref_arefnum : 4;
        unsigned int asref_en : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_cc_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_cc_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_fast_wakeup_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_fast_wakeup_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_pd_START (2)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_pd_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_init_xsref_START (3)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_init_xsref_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_odis_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_odis_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_clk_switch_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_clk_switch_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_arefnum_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_sref_arefnum_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_en_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_SREF_asref_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int init_arefnum : 8;
        unsigned int wrlvl_en : 1;
        unsigned int reserved : 23;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_INIT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_INIT_init_arefnum_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_INIT_init_arefnum_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_INIT_wrlvl_en_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_INIT_wrlvl_en_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_en : 1;
        unsigned int pd_ac : 1;
        unsigned int pd_cc : 1;
        unsigned int reserved : 1;
        unsigned int pd_prd : 12;
        unsigned int t_clk_cke : 4;
        unsigned int asref_prd : 12;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_en_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_ac_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_ac_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_cc_START (2)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_cc_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_prd_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_PD_pd_prd_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_PD_t_clk_cke_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_PD_t_clk_cke_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_PD_asref_prd_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_PD_asref_prd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int aref_opt : 1;
        unsigned int aref_dual_rank : 1;
        unsigned int aref_alarm_en : 1;
        unsigned int pstpnd_level : 2;
        unsigned int reserved_1 : 1;
        unsigned int aref_alarm_num : 8;
        unsigned int phyupd_level : 4;
        unsigned int modified_mode : 1;
        unsigned int reserved_2 : 11;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_AREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_opt_START (2)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_opt_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_dual_rank_START (3)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_dual_rank_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_en_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_en_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_pstpnd_level_START (5)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_pstpnd_level_END (6)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_num_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_aref_alarm_num_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_phyupd_level_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_phyupd_level_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_modified_mode_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_AREF_modified_mode_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ecc_en : 1;
        unsigned int reserved_0: 3;
        unsigned int eccwb_en : 1;
        unsigned int reserved_1: 3;
        unsigned int ecc_byp : 1;
        unsigned int ecc_msk : 1;
        unsigned int reserved_2: 22;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_ECC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_en_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_eccwb_en_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_eccwb_en_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_byp_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_byp_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_msk_START (9)
#define SOC_DDRC_DMC_DDRC_CFG_ECC_ecc_msk_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int err_inject_mode : 2;
        unsigned int reserved_0 : 2;
        unsigned int err_inject_bl0 : 5;
        unsigned int err_inject_bl1 : 5;
        unsigned int reserved_1 : 2;
        unsigned int err_inject_mask : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_ERRINJ_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mode_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mode_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl0_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl0_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl1_START (9)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl1_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mask_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sbram_err_inj : 2;
        unsigned int reserved_0 : 2;
        unsigned int rpram_err_inj : 2;
        unsigned int reserved_1 : 2;
        unsigned int recram_err_inj : 2;
        unsigned int reserved_2 : 22;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_sbram_err_inj_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_sbram_err_inj_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_rpram_err_inj_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_rpram_err_inj_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_recram_err_inj_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_FIFO_ERRINJ_recram_err_inj_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_ratio : 1;
        unsigned int cmd_clkon : 1;
        unsigned int data_clkon : 1;
        unsigned int func_clkon : 1;
        unsigned int apre_en : 1;
        unsigned int exmbist_clkon : 1;
        unsigned int reserved_0 : 2;
        unsigned int wrap_en : 1;
        unsigned int intlv_en : 1;
        unsigned int addr_mode : 2;
        unsigned int read_mode : 1;
        unsigned int hdr_mode : 1;
        unsigned int wr_intlv_en : 1;
        unsigned int clk_ratio2 : 1;
        unsigned int qos_mode : 1;
        unsigned int reserved_1 : 1;
        unsigned int wr_otf_en : 1;
        unsigned int rd_otf_en : 1;
        unsigned int reorder_en : 1;
        unsigned int reserved_2 : 3;
        unsigned int exclu_en : 1;
        unsigned int reserved_3 : 3;
        unsigned int wr_rcv_mode : 1;
        unsigned int reserved_4 : 3;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_WORKMODE_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_cmd_clkon_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_cmd_clkon_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_data_clkon_START (2)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_data_clkon_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_func_clkon_START (3)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_func_clkon_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_apre_en_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_apre_en_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exmbist_clkon_START (5)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exmbist_clkon_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wrap_en_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wrap_en_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_intlv_en_START (9)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_intlv_en_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_addr_mode_START (10)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_addr_mode_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_read_mode_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_read_mode_END (12)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_hdr_mode_START (13)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_hdr_mode_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_intlv_en_START (14)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_intlv_en_END (14)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio2_START (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio2_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_qos_mode_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_qos_mode_END (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_otf_en_START (18)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_otf_en_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_rd_otf_en_START (19)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_rd_otf_en_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_reorder_en_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_reorder_en_END (20)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exclu_en_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_exclu_en_END (24)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_rcv_mode_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE_wr_rcv_mode_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rank_disable : 16;
        unsigned int openpage_time : 14;
        unsigned int reserved : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_rank_disable_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_rank_disable_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_openpage_time_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE2_openpage_time_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tdbi : 4;
        unsigned int tpl : 4;
        unsigned int tcal : 4;
        unsigned int twrcslat : 4;
        unsigned int trdcslat : 4;
        unsigned int reserved : 12;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tdbi_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tdbi_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tpl_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tpl_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tcal_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_tcal_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_twrcslat_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_twrcslat_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_trdcslat_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_WORKMODE3_trdcslat_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dram_type : 4;
        unsigned int mem_width : 2;
        unsigned int reserved_0 : 1;
        unsigned int brstlen2 : 1;
        unsigned int brstlen : 1;
        unsigned int wr_2t_pre : 1;
        unsigned int rd_2t_pre : 1;
        unsigned int cmd_2t_en : 1;
        unsigned int bc_en : 1;
        unsigned int lpddr4_bl32 : 1;
        unsigned int scramb_en : 1;
        unsigned int crc_en : 1;
        unsigned int zqc_en : 1;
        unsigned int odt_on : 1;
        unsigned int rank_mode : 2;
        unsigned int rank : 2;
        unsigned int sref_zqc_en : 1;
        unsigned int asref_zqc_en : 1;
        unsigned int bank_xor : 2;
        unsigned int reserved_1 : 2;
        unsigned int bank_mode : 3;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DDRMODE_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_dram_type_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_dram_type_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_mem_width_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_mem_width_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen2_START (7)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen2_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_brstlen_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_wr_2t_pre_START (9)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_wr_2t_pre_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rd_2t_pre_START (10)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rd_2t_pre_END (10)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_cmd_2t_en_START (11)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_cmd_2t_en_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bc_en_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bc_en_END (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_lpddr4_bl32_START (13)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_lpddr4_bl32_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_scramb_en_START (14)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_scramb_en_END (14)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_crc_en_START (15)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_crc_en_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_zqc_en_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_zqc_en_END (16)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_odt_on_START (17)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_odt_on_END (17)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_mode_START (18)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_mode_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_rank_END (21)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_sref_zqc_en_START (22)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_sref_zqc_en_END (22)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_asref_zqc_en_START (23)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_asref_zqc_en_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_xor_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_xor_END (25)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_mode_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_DDRMODE_bank_mode_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_mirror : 1;
        unsigned int reserved_0 : 3;
        unsigned int parity_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int cke_share_map : 2;
        unsigned int reserved_2 : 2;
        unsigned int par_dly : 1;
        unsigned int reserved_3 : 19;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DIMM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_addr_mirror_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_addr_mirror_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_parity_en_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_parity_en_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_cke_share_map_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_cke_share_map_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_par_dly_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_DIMM_par_dly_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scramb_seed_sort : 3;
        unsigned int reserved_0 : 1;
        unsigned int scramb_seed_type : 1;
        unsigned int reserved_1 : 3;
        unsigned int dmi_pattern : 8;
        unsigned int wr_dbi_en : 1;
        unsigned int rd_dbi_en : 1;
        unsigned int dbi_low_act : 1;
        unsigned int mrr_dbi_byp : 1;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SCRAMB_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_sort_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_sort_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_type_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_scramb_seed_type_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dmi_pattern_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dmi_pattern_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_wr_dbi_en_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_wr_dbi_en_END (16)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_rd_dbi_en_START (17)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_rd_dbi_en_END (17)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dbi_low_act_START (18)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_dbi_low_act_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_mrr_dbi_byp_START (19)
#define SOC_DDRC_DMC_DDRC_CFG_SCRAMB_mrr_dbi_byp_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lv_ctrl_en : 1;
        unsigned int lv_wren_ext : 1;
        unsigned int reserved : 14;
        unsigned int lv_ctrl_threshold : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_LVCTRL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_en_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_wren_ext_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_wren_ext_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_threshold_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_LVCTRL_lv_ctrl_threshold_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_col : 3;
        unsigned int reserved_0 : 1;
        unsigned int mem_row : 3;
        unsigned int reserved_1 : 1;
        unsigned int mem_bank : 2;
        unsigned int mem_bankgroup : 2;
        unsigned int mem_map : 2;
        unsigned int reserved_2 : 2;
        unsigned int mem_x4 : 1;
        unsigned int reserved_3 : 15;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_RNKVOL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_col_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_col_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_row_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_row_END (6)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bank_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bank_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bankgroup_START (10)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_bankgroup_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_map_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_map_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_x4_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_RNKVOL_mem_x4_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wodt : 16;
        unsigned int rodt : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_ODT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_ODT_wodt_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_ODT_wodt_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_ODT_rodt_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_ODT_rodt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ca_odt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CA_ODT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CA_ODT_ca_odt_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_CA_ODT_ca_odt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mrs : 16;
        unsigned int emrs1 : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS01_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_mrs_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_mrs_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_emrs1_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS01_emrs1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emrs2 : 16;
        unsigned int emrs3 : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS23_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs2_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs2_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs3_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS23_emrs3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emrs4 : 16;
        unsigned int emrs5 : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS45_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs4_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs4_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs5_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS45_emrs5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emrs6 : 16;
        unsigned int emrs7 : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EMRS67_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs6_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs6_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs7_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_EMRS67_emrs7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tras : 6;
        unsigned int reserved : 2;
        unsigned int trc : 6;
        unsigned int trcd : 5;
        unsigned int trp_pb : 5;
        unsigned int trrd : 4;
        unsigned int tmrd : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tras_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tras_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trc_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trc_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trcd_START (14)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trcd_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trp_pb_START (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trp_pb_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trrd_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_trrd_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tmrd_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING0_tmrd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcl : 6;
        unsigned int reserved_0: 2;
        unsigned int twl : 6;
        unsigned int tmrri : 5;
        unsigned int reserved_1: 1;
        unsigned int trtw : 4;
        unsigned int tsre : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tcl_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tcl_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_twl_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_twl_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tmrri_START (14)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tmrri_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_trtw_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_trtw_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tsre_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING1_tsre_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taref : 11;
        unsigned int reserved : 1;
        unsigned int tfaw : 6;
        unsigned int trtrrd : 6;
        unsigned int twtr : 4;
        unsigned int tcke : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_taref_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_taref_END (10)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tfaw_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tfaw_END (17)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_trtrrd_START (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_trtrrd_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_twtr_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_twtr_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tcke_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING2_tcke_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trtp : 4;
        unsigned int txard : 4;
        unsigned int taond : 5;
        unsigned int tzqinit : 9;
        unsigned int tzq_prd : 10;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_trtp_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_trtp_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_txard_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_txard_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_taond_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_taond_END (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzqinit_START (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzqinit_END (21)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzq_prd_START (22)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING3_tzq_prd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tccdmw16 : 6;
        unsigned int reserved_0: 2;
        unsigned int tccdmw32 : 6;
        unsigned int reserved_1: 2;
        unsigned int twlo : 4;
        unsigned int tmod : 5;
        unsigned int reserved_2: 3;
        unsigned int trodt_ext : 3;
        unsigned int reserved_3: 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw16_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw16_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw32_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tccdmw32_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_twlo_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_twlo_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tmod_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_tmod_END (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_trodt_ext_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING4_trodt_ext_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int twr : 5;
        unsigned int reserved_0: 3;
        unsigned int tzqcs : 8;
        unsigned int trnk2rnk : 4;
        unsigned int tdqsck : 3;
        unsigned int reserved_1: 1;
        unsigned int tdqsckmax : 3;
        unsigned int reserved_2: 1;
        unsigned int twodt_ext : 3;
        unsigned int reserved_3: 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twr_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tzqcs_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tzqcs_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_trnk2rnk_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_trnk2rnk_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsck_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsck_END (22)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsckmax_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_tdqsckmax_END (26)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twodt_ext_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING5_twodt_ext_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcksre : 4;
        unsigned int tcksrx : 4;
        unsigned int todt_sft : 4;
        unsigned int tccd_l : 4;
        unsigned int twtr_l : 4;
        unsigned int trrd_l : 4;
        unsigned int tccd_nsr : 4;
        unsigned int tccd_nsw : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksre_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksre_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksrx_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tcksrx_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_todt_sft_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_todt_sft_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_l_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_l_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_twtr_l_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_twtr_l_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_trrd_l_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_trrd_l_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsr_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsr_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsw_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING6_tccd_nsw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnk_twtr : 4;
        unsigned int rnk_trtw : 4;
        unsigned int rnk_twtw : 4;
        unsigned int rnk_trtr : 4;
        unsigned int dimm_twtw : 4;
        unsigned int dimm_trtr : 4;
        unsigned int tckehcmd : 4;
        unsigned int tescke : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtr_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtw_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtw_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtw_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_twtw_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtr_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_rnk_trtr_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_twtw_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_twtw_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_trtr_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_dimm_trtr_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tckehcmd_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tckehcmd_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tescke_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING7_tescke_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trp_ab : 5;
        unsigned int tsr : 5;
        unsigned int trfc_pb : 9;
        unsigned int trfc_ab : 9;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMING8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trp_ab_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trp_ab_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_tsr_START (5)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_tsr_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_pb_START (10)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_pb_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_ab_START (19)
#define SOC_DDRC_DMC_DDRC_CFG_TIMING8_trfc_ab_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tras : 6;
        unsigned int reserved : 2;
        unsigned int trc : 6;
        unsigned int trcd : 5;
        unsigned int trp_pb : 5;
        unsigned int trrd : 4;
        unsigned int tmrd : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tras_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tras_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trc_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trc_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trcd_START (14)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trcd_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trp_pb_START (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trp_pb_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trrd_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_trrd_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tmrd_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING0_tmrd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcl : 6;
        unsigned int reserved_0: 2;
        unsigned int twl : 6;
        unsigned int tmrri : 5;
        unsigned int reserved_1: 1;
        unsigned int trtw : 4;
        unsigned int tsre : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tcl_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tcl_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_twl_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_twl_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tmrri_START (14)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tmrri_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_trtw_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_trtw_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tsre_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING1_tsre_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taref : 11;
        unsigned int reserved : 1;
        unsigned int tfaw : 6;
        unsigned int trtrrd : 6;
        unsigned int twtr : 4;
        unsigned int tcke : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_taref_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_taref_END (10)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tfaw_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tfaw_END (17)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_trtrrd_START (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_trtrrd_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_twtr_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_twtr_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tcke_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING2_tcke_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trtp : 4;
        unsigned int txard : 4;
        unsigned int taond : 5;
        unsigned int tzqinit : 9;
        unsigned int tzq_prd : 10;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_trtp_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_trtp_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_txard_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_txard_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_taond_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_taond_END (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzqinit_START (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzqinit_END (21)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzq_prd_START (22)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING3_tzq_prd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tccdmw16 : 6;
        unsigned int reserved_0: 2;
        unsigned int tccdmw32 : 6;
        unsigned int reserved_1: 2;
        unsigned int twlo : 4;
        unsigned int tmod : 5;
        unsigned int reserved_2: 3;
        unsigned int trodt_ext : 3;
        unsigned int reserved_3: 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw16_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw16_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw32_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tccdmw32_END (13)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_twlo_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_twlo_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tmod_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_tmod_END (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_trodt_ext_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING4_trodt_ext_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int twr : 5;
        unsigned int reserved_0: 3;
        unsigned int tzqcs : 8;
        unsigned int trnk2rnk : 4;
        unsigned int tdqsck : 3;
        unsigned int reserved_1: 1;
        unsigned int tdqsckmax : 3;
        unsigned int reserved_2: 1;
        unsigned int twodt_ext : 3;
        unsigned int reserved_3: 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twr_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tzqcs_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tzqcs_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_trnk2rnk_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_trnk2rnk_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsck_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsck_END (22)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsckmax_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsckmax_END (26)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twodt_ext_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING5_twodt_ext_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcksre : 4;
        unsigned int tcksrx : 4;
        unsigned int todt_sft : 4;
        unsigned int tccd_l : 4;
        unsigned int twtr_l : 4;
        unsigned int trrd_l : 4;
        unsigned int tccd_nsr : 4;
        unsigned int tccd_nsw : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksre_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksre_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksrx_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksrx_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_todt_sft_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_todt_sft_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_l_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_l_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_twtr_l_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_twtr_l_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_trrd_l_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_trrd_l_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsr_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsr_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsw_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING6_tccd_nsw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnk_twtr : 4;
        unsigned int rnk_trtw : 4;
        unsigned int rnk_twtw : 4;
        unsigned int rnk_trtr : 4;
        unsigned int dimm_twtw : 4;
        unsigned int dimm_trtr : 4;
        unsigned int reserved : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtr_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtw_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtw_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtw_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_twtw_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtr_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_rnk_trtr_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_twtw_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_twtw_END (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_trtr_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING7_dimm_trtr_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trp_ab : 5;
        unsigned int tsr : 5;
        unsigned int trfc_pb : 9;
        unsigned int trfc_ab : 9;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trp_ab_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trp_ab_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_tsr_START (5)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_tsr_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_pb_START (10)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_pb_END (18)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_ab_START (19)
#define SOC_DDRC_DMC_DDRC_CFG_NXT_TIMING8_trfc_ab_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bl_data : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_BLDATA_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_BLDATA_bl_data_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_BLDATA_bl_data_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int que_level : 5;
        unsigned int reserved_0 : 3;
        unsigned int mbist_que_level : 5;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DMCLVL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_que_level_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_que_level_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_mbist_que_level_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_DMCLVL_mbist_que_level_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeout_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int timeout_level : 4;
        unsigned int timeout0 : 10;
        unsigned int reserved_1 : 2;
        unsigned int timeout1 : 10;
        unsigned int reserved_2 : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_en_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_level_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout_level_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout0_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout0_END (17)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout1_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_TIMEOUT_timeout1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ageprd : 4;
        unsigned int priadpt : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_QOS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_QOS_ageprd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_QOS_ageprd_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_QOS_priadpt_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_QOS_priadpt_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exmbist_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_exmbist_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_CMD_exmbist_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exmbist_din : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_exmbist_din_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_EXMBIST_DAT_exmbist_din_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mbist_top_addr : 28;
        unsigned int mbist_rank : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MBIST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_top_addr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_top_addr_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_rank_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_MBIST_mbist_rank_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_mclr_pattern0_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN0_mclr_pattern0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_mclr_pattern1_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN1_mclr_pattern1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_mclr_pattern2_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN2_mclr_pattern2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_mclr_pattern3_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN3_mclr_pattern3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_mclr_pattern4_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MCLR_PATTERN4_mclr_pattern4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int osc_prd : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_osc_prd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_PRD_osc_prd_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int osc_run_time : 16;
        unsigned int osc_threshold : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_run_time_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_run_time_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_threshold_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_OSC_CFG_osc_threshold_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int train_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TRAIN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TRAIN_train_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TRAIN_train_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyif_tim_oven : 7;
        unsigned int reserved : 1;
        unsigned int phyif_tim_wodt : 8;
        unsigned int phyif_tim_rodt : 8;
        unsigned int phyif_tim_wden : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_oven_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_oven_END (6)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wodt_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wodt_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_rodt_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_rodt_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wden_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT0_phyif_tim_wden_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyif_tim_wdcs : 8;
        unsigned int phyif_tim_wdda : 8;
        unsigned int phyif_tim_rden : 8;
        unsigned int phyif_tim_rdcs : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdcs_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdcs_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdda_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_wdda_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rden_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rden_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rdcs_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_DFI_LAT1_phyif_tim_rdcs_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rec_en : 1;
        unsigned int rec_ref_en : 1;
        unsigned int rec_upd_en : 1;
        unsigned int reserved_0 : 1;
        unsigned int rec_ref_num : 4;
        unsigned int rec_max_num : 4;
        unsigned int crc_liminal : 6;
        unsigned int reserved_1 : 14;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_REC0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_en_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_en_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_en_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_upd_en_START (2)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_upd_en_END (2)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_num_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_ref_num_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_max_num_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_rec_max_num_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_crc_liminal_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_REC0_crc_liminal_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int talert_syn : 4;
        unsigned int tio2phy_dly : 5;
        unsigned int reserved_0 : 3;
        unsigned int tpar_alert : 5;
        unsigned int reserved_1 : 3;
        unsigned int tcrc_alert : 5;
        unsigned int tphy2io_dly : 5;
        unsigned int reserved_2 : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_REC1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_REC1_talert_syn_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_talert_syn_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tio2phy_dly_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tio2phy_dly_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tpar_alert_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tpar_alert_END (16)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tcrc_alert_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tcrc_alert_END (24)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tphy2io_dly_START (25)
#define SOC_DDRC_DMC_DDRC_CFG_REC1_tphy2io_dly_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int device_x8_x4 : 18;
        unsigned int reserved_0 : 2;
        unsigned int crc_pipe_bypass : 1;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CRC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CRC_device_x8_x4_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_device_x8_x4_END (17)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_crc_pipe_bypass_START (20)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_crc_pipe_bypass_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_err_inj : 1;
        unsigned int crc_inject_mask : 1;
        unsigned int reserved_0 : 2;
        unsigned int crc_inject_dm : 1;
        unsigned int reserved_1 : 3;
        unsigned int crc_inject_pat : 8;
        unsigned int crc_inject_num : 5;
        unsigned int reserved_2 : 11;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_err_inj_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_err_inj_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_mask_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_mask_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_dm_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_dm_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_pat_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_pat_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_num_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ0_crc_inject_num_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_inject_burst : 4;
        unsigned int crc_inject_bl : 18;
        unsigned int reserved : 10;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_burst_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_burst_END (3)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_bl_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_CRC_ERRINJ1_crc_inject_bl_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int par_err_inj : 1;
        unsigned int par_inject_mask : 1;
        unsigned int reserved_0 : 2;
        unsigned int par_inject_num : 5;
        unsigned int reserved_1 : 3;
        unsigned int par_inject_cmd : 8;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_err_inj_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_err_inj_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_mask_START (1)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_mask_END (1)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_num_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_num_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_cmd_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ0_par_inject_cmd_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int par_inject_pos : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_par_inject_pos_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_PAR_ERRINJ1_par_inject_pos_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rcv_pdr : 1;
        unsigned int reserved_0 : 3;
        unsigned int phy_zqen : 1;
        unsigned int reserved_1 : 3;
        unsigned int trdlat : 4;
        unsigned int phy_upden : 1;
        unsigned int reserved_2 : 3;
        unsigned int wr_busy_dly : 6;
        unsigned int reserved_3 : 2;
        unsigned int phyupd_n_pre : 1;
        unsigned int reserved_4 : 3;
        unsigned int phyupd_n_pre_type : 2;
        unsigned int reserved_5 : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DDRPHY_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_rcv_pdr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_rcv_pdr_END (0)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_zqen_START (4)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_zqen_END (4)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_trdlat_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_trdlat_END (11)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_upden_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phy_upden_END (12)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_wr_busy_dly_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_wr_busy_dly_END (21)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_END (24)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_type_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_DDRPHY_phyupd_n_pre_type_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int age_ent_prd : 8;
        unsigned int age_ext_prd : 8;
        unsigned int age_en : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_AGING_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ent_prd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ent_prd_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ext_prd_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_ext_prd_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_en_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_AGING_age_en_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sfc_mask : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_sfc_mask_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_MASK_sfc_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wait_time : 6;
        unsigned int reserved : 10;
        unsigned int wait_tlast : 8;
        unsigned int wait_reserv : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_time_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_time_END (5)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_tlast_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_tlast_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_reserv_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_TIM_wait_reserv_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sfc_que_rptr : 8;
        unsigned int infinite_loop : 1;
        unsigned int sfc_que_clr : 1;
        unsigned int sfc_msk_ctrl : 1;
        unsigned int reserved_0 : 1;
        unsigned int cmd_mrs : 4;
        unsigned int reserved_1 : 15;
        unsigned int wait_en : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_rptr_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_rptr_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_infinite_loop_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_infinite_loop_END (8)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_clr_START (9)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_que_clr_END (9)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_msk_ctrl_START (10)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_sfc_msk_ctrl_END (10)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_cmd_mrs_START (12)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_cmd_mrs_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_wait_en_START (31)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_wait_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sfc_cmd_que : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_cmd_que_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_cmd_que_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 16;
        unsigned int sfc_rank : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_sfc_rank_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_ADDR1_sfc_rank_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_wdata0_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA0_wdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_wdata1_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA1_wdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_wdata2_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA2_wdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_wdata3_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA3_wdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_wdata4_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA4_wdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_wdata5_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA5_wdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_wdata6_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA6_wdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_wdata7_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA7_wdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata_ecc0 : 8;
        unsigned int wdata_ecc1 : 8;
        unsigned int wdata_ecc2 : 8;
        unsigned int wdata_ecc3 : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc0_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc0_END (7)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc1_START (8)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc1_END (15)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc2_START (16)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc2_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc3_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tmon_prd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TMON_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TMON_tmon_prd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TMON_tmon_prd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tmon_rank : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_tmon_rank_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TMON_RANK_tmon_rank_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aref_rate : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_aref_rate_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_TMON_AREF_aref_rate_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mrr_map : 24;
        unsigned int mrr_byte : 5;
        unsigned int reserved : 3;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_map_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_map_END (23)
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_byte_START (24)
#define SOC_DDRC_DMC_DDRC_CFG_MRR_MAP_mrr_byte_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dat_stat_prd : 28;
        unsigned int dat_stat_mode : 2;
        unsigned int dat_stat_en : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STADAT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_prd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_prd_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_mode_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_mode_END (29)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_en_START (30)
#define SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_en_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_dat_min : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DATMIN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DATMIN_dmc_dat_min_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DATMIN_dmc_dat_min_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_dat_max : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DATMAX_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DATMAX_dmc_dat_max_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DATMAX_dmc_dat_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int load_stat_prd : 28;
        unsigned int load_stat_mode : 2;
        unsigned int load_stat_en : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STACMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_prd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_prd_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_mode_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_mode_END (29)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_en_START (30)
#define SOC_DDRC_DMC_DDRC_CFG_STACMD_load_stat_en_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cmd_min : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CMDMIN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CMDMIN_dmc_cmd_min_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_CMDMIN_dmc_cmd_min_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cmd_max : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_CMDMAX_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_CMDMAX_dmc_cmd_max_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_CMDMAX_dmc_cmd_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perf_prd : 28;
        unsigned int perf_mode : 1;
        unsigned int flux_en : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_PERF_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_prd_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_prd_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_mode_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_perf_mode_END (28)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_flux_en_START (29)
#define SOC_DDRC_DMC_DDRC_CFG_PERF_flux_en_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sta_id : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STAID_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STAID_sta_id_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_STAID_sta_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sta_idmask : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_sta_idmask_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_sta_idmask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dummy_rd_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DUM_EN_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DUM_EN_dummy_rd_en_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_EN_dummy_rd_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dummy_rd_cnt : 28;
        unsigned int dummy_rd_mode : 2;
        unsigned int reserved : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_cnt_START (0)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_cnt_END (27)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_mode_START (28)
#define SOC_DDRC_DMC_DDRC_CFG_DUM_CFG_dummy_rd_mode_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_int_mask : 1;
        unsigned int flux_int_mask : 1;
        unsigned int rec_int_mask : 1;
        unsigned int rec_err_int_mask : 1;
        unsigned int merr_int_mask : 1;
        unsigned int sref_err_int_mask : 1;
        unsigned int tmon_err_int_mask : 1;
        unsigned int tmon_upd_int_mask : 1;
        unsigned int dimm_parity_int_mask : 1;
        unsigned int stacmd_min_int_mask : 1;
        unsigned int stacmd_max_int_mask : 1;
        unsigned int reserved_0 : 1;
        unsigned int rdtimeout_int_mask : 1;
        unsigned int stadat_min_int_mask : 1;
        unsigned int stadat_max_int_mask : 1;
        unsigned int reserved_1 : 1;
        unsigned int aref_alarm_int_mask : 1;
        unsigned int osc_rd_int_mask : 1;
        unsigned int osc_ovth_int_mask : 1;
        unsigned int osc_overflow_int_mask : 1;
        unsigned int sbram_serr_int_mask : 1;
        unsigned int reserved_2 : 3;
        unsigned int sbram_merr_int_mask : 1;
        unsigned int reserved_3 : 3;
        unsigned int rpram_serr_int_mask : 1;
        unsigned int recram_serr_int_mask : 1;
        unsigned int recram_merr_int_mask : 1;
        unsigned int rpram_merr_int_mask : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_INTMSK_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_INTMSK_serr_int_mask_START (0)
#define SOC_DDRC_DMC_DDRC_INTMSK_serr_int_mask_END (0)
#define SOC_DDRC_DMC_DDRC_INTMSK_flux_int_mask_START (1)
#define SOC_DDRC_DMC_DDRC_INTMSK_flux_int_mask_END (1)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_int_mask_START (2)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_int_mask_END (2)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_err_int_mask_START (3)
#define SOC_DDRC_DMC_DDRC_INTMSK_rec_err_int_mask_END (3)
#define SOC_DDRC_DMC_DDRC_INTMSK_merr_int_mask_START (4)
#define SOC_DDRC_DMC_DDRC_INTMSK_merr_int_mask_END (4)
#define SOC_DDRC_DMC_DDRC_INTMSK_sref_err_int_mask_START (5)
#define SOC_DDRC_DMC_DDRC_INTMSK_sref_err_int_mask_END (5)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_err_int_mask_START (6)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_err_int_mask_END (6)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_upd_int_mask_START (7)
#define SOC_DDRC_DMC_DDRC_INTMSK_tmon_upd_int_mask_END (7)
#define SOC_DDRC_DMC_DDRC_INTMSK_dimm_parity_int_mask_START (8)
#define SOC_DDRC_DMC_DDRC_INTMSK_dimm_parity_int_mask_END (8)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_min_int_mask_START (9)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_min_int_mask_END (9)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_max_int_mask_START (10)
#define SOC_DDRC_DMC_DDRC_INTMSK_stacmd_max_int_mask_END (10)
#define SOC_DDRC_DMC_DDRC_INTMSK_rdtimeout_int_mask_START (12)
#define SOC_DDRC_DMC_DDRC_INTMSK_rdtimeout_int_mask_END (12)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_min_int_mask_START (13)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_min_int_mask_END (13)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_max_int_mask_START (14)
#define SOC_DDRC_DMC_DDRC_INTMSK_stadat_max_int_mask_END (14)
#define SOC_DDRC_DMC_DDRC_INTMSK_aref_alarm_int_mask_START (16)
#define SOC_DDRC_DMC_DDRC_INTMSK_aref_alarm_int_mask_END (16)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_rd_int_mask_START (17)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_rd_int_mask_END (17)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_ovth_int_mask_START (18)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_ovth_int_mask_END (18)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_overflow_int_mask_START (19)
#define SOC_DDRC_DMC_DDRC_INTMSK_osc_overflow_int_mask_END (19)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_serr_int_mask_START (20)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_serr_int_mask_END (20)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_merr_int_mask_START (24)
#define SOC_DDRC_DMC_DDRC_INTMSK_sbram_merr_int_mask_END (24)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_serr_int_mask_START (28)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_serr_int_mask_END (28)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_serr_int_mask_START (29)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_serr_int_mask_END (29)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_merr_int_mask_START (30)
#define SOC_DDRC_DMC_DDRC_INTMSK_recram_merr_int_mask_END (30)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_merr_int_mask_START (31)
#define SOC_DDRC_DMC_DDRC_INTMSK_rpram_merr_int_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rint : 1;
        unsigned int flux_rint : 1;
        unsigned int rec_rint : 1;
        unsigned int rec_err_rint : 1;
        unsigned int merr_rint : 1;
        unsigned int sref_err_rint : 1;
        unsigned int tmon_err_rint : 1;
        unsigned int tmon_upd_rint : 1;
        unsigned int dimm_parity_rint : 1;
        unsigned int stacmd_min_rint : 1;
        unsigned int stacmd_max_rint : 1;
        unsigned int reserved_0 : 1;
        unsigned int rdtimeout_rint : 1;
        unsigned int stadat_min_rint : 1;
        unsigned int stadat_max_rint : 1;
        unsigned int reserved_1 : 1;
        unsigned int aref_alarm_rint : 1;
        unsigned int osc_rd_rint : 1;
        unsigned int osc_ovth_rint : 1;
        unsigned int osc_overflow_rint : 1;
        unsigned int sbram_serr_rint : 1;
        unsigned int reserved_2 : 3;
        unsigned int sbram_merr_rint : 1;
        unsigned int reserved_3 : 3;
        unsigned int rpram_serr_rint : 1;
        unsigned int recram_serr_rint : 1;
        unsigned int recram_merr_rint : 1;
        unsigned int rpram_merr_rint : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_RINT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_RINT_serr_rint_START (0)
#define SOC_DDRC_DMC_DDRC_RINT_serr_rint_END (0)
#define SOC_DDRC_DMC_DDRC_RINT_flux_rint_START (1)
#define SOC_DDRC_DMC_DDRC_RINT_flux_rint_END (1)
#define SOC_DDRC_DMC_DDRC_RINT_rec_rint_START (2)
#define SOC_DDRC_DMC_DDRC_RINT_rec_rint_END (2)
#define SOC_DDRC_DMC_DDRC_RINT_rec_err_rint_START (3)
#define SOC_DDRC_DMC_DDRC_RINT_rec_err_rint_END (3)
#define SOC_DDRC_DMC_DDRC_RINT_merr_rint_START (4)
#define SOC_DDRC_DMC_DDRC_RINT_merr_rint_END (4)
#define SOC_DDRC_DMC_DDRC_RINT_sref_err_rint_START (5)
#define SOC_DDRC_DMC_DDRC_RINT_sref_err_rint_END (5)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_err_rint_START (6)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_err_rint_END (6)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_upd_rint_START (7)
#define SOC_DDRC_DMC_DDRC_RINT_tmon_upd_rint_END (7)
#define SOC_DDRC_DMC_DDRC_RINT_dimm_parity_rint_START (8)
#define SOC_DDRC_DMC_DDRC_RINT_dimm_parity_rint_END (8)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_min_rint_START (9)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_min_rint_END (9)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_max_rint_START (10)
#define SOC_DDRC_DMC_DDRC_RINT_stacmd_max_rint_END (10)
#define SOC_DDRC_DMC_DDRC_RINT_rdtimeout_rint_START (12)
#define SOC_DDRC_DMC_DDRC_RINT_rdtimeout_rint_END (12)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_min_rint_START (13)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_min_rint_END (13)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_max_rint_START (14)
#define SOC_DDRC_DMC_DDRC_RINT_stadat_max_rint_END (14)
#define SOC_DDRC_DMC_DDRC_RINT_aref_alarm_rint_START (16)
#define SOC_DDRC_DMC_DDRC_RINT_aref_alarm_rint_END (16)
#define SOC_DDRC_DMC_DDRC_RINT_osc_rd_rint_START (17)
#define SOC_DDRC_DMC_DDRC_RINT_osc_rd_rint_END (17)
#define SOC_DDRC_DMC_DDRC_RINT_osc_ovth_rint_START (18)
#define SOC_DDRC_DMC_DDRC_RINT_osc_ovth_rint_END (18)
#define SOC_DDRC_DMC_DDRC_RINT_osc_overflow_rint_START (19)
#define SOC_DDRC_DMC_DDRC_RINT_osc_overflow_rint_END (19)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_serr_rint_START (20)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_serr_rint_END (20)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_merr_rint_START (24)
#define SOC_DDRC_DMC_DDRC_RINT_sbram_merr_rint_END (24)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_serr_rint_START (28)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_serr_rint_END (28)
#define SOC_DDRC_DMC_DDRC_RINT_recram_serr_rint_START (29)
#define SOC_DDRC_DMC_DDRC_RINT_recram_serr_rint_END (29)
#define SOC_DDRC_DMC_DDRC_RINT_recram_merr_rint_START (30)
#define SOC_DDRC_DMC_DDRC_RINT_recram_merr_rint_END (30)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_merr_rint_START (31)
#define SOC_DDRC_DMC_DDRC_RINT_rpram_merr_rint_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_intsts : 1;
        unsigned int flux_intsts : 1;
        unsigned int rec_intsts : 1;
        unsigned int rec_err_intsts : 1;
        unsigned int merr_intsts : 1;
        unsigned int sref_err_intsts : 1;
        unsigned int tmon_err_intsts : 1;
        unsigned int tmon_upd_intsts : 1;
        unsigned int dimm_parity_intsts : 1;
        unsigned int stacmd_min_intsts : 1;
        unsigned int stacmd_max_intsts : 1;
        unsigned int reserved_0 : 1;
        unsigned int rdtimeout_intsts : 1;
        unsigned int stadat_min_intsts : 1;
        unsigned int stadat_max_intsts : 1;
        unsigned int reserved_1 : 1;
        unsigned int aref_alarm_intsts : 1;
        unsigned int osc_rd_intsts : 1;
        unsigned int osc_ovth_intsts : 1;
        unsigned int osc_overflow_intsts : 1;
        unsigned int sbram_serr_intsts : 1;
        unsigned int reserved_2 : 3;
        unsigned int sbram_merr_intsts : 1;
        unsigned int reserved_3 : 3;
        unsigned int rpram_serr_intsts : 1;
        unsigned int recram_serr_intsts : 1;
        unsigned int recram_merr_intsts : 1;
        unsigned int rpram_merr_intsts : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_INTSTS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_INTSTS_serr_intsts_START (0)
#define SOC_DDRC_DMC_DDRC_INTSTS_serr_intsts_END (0)
#define SOC_DDRC_DMC_DDRC_INTSTS_flux_intsts_START (1)
#define SOC_DDRC_DMC_DDRC_INTSTS_flux_intsts_END (1)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_intsts_START (2)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_intsts_END (2)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_err_intsts_START (3)
#define SOC_DDRC_DMC_DDRC_INTSTS_rec_err_intsts_END (3)
#define SOC_DDRC_DMC_DDRC_INTSTS_merr_intsts_START (4)
#define SOC_DDRC_DMC_DDRC_INTSTS_merr_intsts_END (4)
#define SOC_DDRC_DMC_DDRC_INTSTS_sref_err_intsts_START (5)
#define SOC_DDRC_DMC_DDRC_INTSTS_sref_err_intsts_END (5)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_err_intsts_START (6)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_err_intsts_END (6)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_upd_intsts_START (7)
#define SOC_DDRC_DMC_DDRC_INTSTS_tmon_upd_intsts_END (7)
#define SOC_DDRC_DMC_DDRC_INTSTS_dimm_parity_intsts_START (8)
#define SOC_DDRC_DMC_DDRC_INTSTS_dimm_parity_intsts_END (8)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_min_intsts_START (9)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_min_intsts_END (9)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_max_intsts_START (10)
#define SOC_DDRC_DMC_DDRC_INTSTS_stacmd_max_intsts_END (10)
#define SOC_DDRC_DMC_DDRC_INTSTS_rdtimeout_intsts_START (12)
#define SOC_DDRC_DMC_DDRC_INTSTS_rdtimeout_intsts_END (12)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_min_intsts_START (13)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_min_intsts_END (13)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_max_intsts_START (14)
#define SOC_DDRC_DMC_DDRC_INTSTS_stadat_max_intsts_END (14)
#define SOC_DDRC_DMC_DDRC_INTSTS_aref_alarm_intsts_START (16)
#define SOC_DDRC_DMC_DDRC_INTSTS_aref_alarm_intsts_END (16)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_rd_intsts_START (17)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_rd_intsts_END (17)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_ovth_intsts_START (18)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_ovth_intsts_END (18)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_overflow_intsts_START (19)
#define SOC_DDRC_DMC_DDRC_INTSTS_osc_overflow_intsts_END (19)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_serr_intsts_START (20)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_serr_intsts_END (20)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_merr_intsts_START (24)
#define SOC_DDRC_DMC_DDRC_INTSTS_sbram_merr_intsts_END (24)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_serr_intsts_START (28)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_serr_intsts_END (28)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_serr_intsts_START (29)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_serr_intsts_END (29)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_merr_intsts_START (30)
#define SOC_DDRC_DMC_DDRC_INTSTS_recram_merr_intsts_END (30)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_merr_intsts_START (31)
#define SOC_DDRC_DMC_DDRC_INTSTS_rpram_merr_intsts_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int busy : 1;
        unsigned int reserved_0: 3;
        unsigned int busy_dmc : 1;
        unsigned int reserved_1: 3;
        unsigned int busy_func : 1;
        unsigned int reserved_2: 23;
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_STATUS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_START (0)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_END (0)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_dmc_START (4)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_dmc_END (4)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_func_START (8)
#define SOC_DDRC_DMC_DDRC_CURR_STATUS_busy_func_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int in_sref : 1;
        unsigned int in_tmon : 1;
        unsigned int reserved_0 : 2;
        unsigned int in_init : 1;
        unsigned int dfi_init_complete : 1;
        unsigned int reserved_1 : 2;
        unsigned int aref_opt_stat : 1;
        unsigned int reserved_2 : 3;
        unsigned int in_sfc : 1;
        unsigned int reserved_3 : 3;
        unsigned int in_eccwb : 1;
        unsigned int reserved_4 : 3;
        unsigned int in_mtest : 1;
        unsigned int reserved_5 : 3;
        unsigned int in_mclr : 1;
        unsigned int in_rec : 1;
        unsigned int reserved_6 : 2;
        unsigned int in_phyupd : 1;
        unsigned int in_srpd : 1;
        unsigned int reserved_7 : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_FUNC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sref_START (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sref_END (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_tmon_START (1)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_tmon_END (1)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_init_START (4)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_init_END (4)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_dfi_init_complete_START (5)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_dfi_init_complete_END (5)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_aref_opt_stat_START (8)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_aref_opt_stat_END (8)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sfc_START (12)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_sfc_END (12)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_eccwb_START (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_eccwb_END (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mtest_START (20)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mtest_END (20)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mclr_START (24)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_mclr_END (24)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_rec_START (25)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_rec_END (25)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_phyupd_START (28)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_phyupd_END (28)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_srpd_START (29)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC_in_srpd_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int in_pd : 16;
        unsigned int in_asref : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_FUNC2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_pd_START (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_pd_END (15)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_asref_START (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC2_in_asref_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int in_dummy_rd : 16;
        unsigned int in_osc : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_FUNC3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_dummy_rd_START (0)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_dummy_rd_END (15)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_osc_START (16)
#define SOC_DDRC_DMC_DDRC_CURR_FUNC3_in_osc_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cv : 16;
        unsigned int dmc_ct : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_EXECST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_cv_START (0)
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_cv_END (15)
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_ct_START (16)
#define SOC_DDRC_DMC_DDRC_CURR_EXECST_dmc_ct_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wgntfifo_e : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_wgntfifo_e_START (0)
#define SOC_DDRC_DMC_DDRC_CURR_WGFIFOST_wgntfifo_e_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_adr0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_serr_adr0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR0_serr_adr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_adr1 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_serr_adr1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_ADR1_serr_adr1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_serr_rdata0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA0_serr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_serr_rdata1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA1_serr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_serr_rdata2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA2_serr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_serr_rdata3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA3_serr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_serr_rdata4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA4_serr_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_serr_rdata5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA5_serr_rdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_serr_rdata6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA6_serr_rdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_serr_rdata7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA7_serr_rdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata8 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_serr_rdata8_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_RDATA8_serr_rdata8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_serr_expdata0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA0_serr_expdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_serr_expdata1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA1_serr_expdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_serr_expdata2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA2_serr_expdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_serr_expdata3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA3_serr_expdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_serr_expdata4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA4_serr_expdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_serr_expdata5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA5_serr_expdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_serr_expdata6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA6_serr_expdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_serr_expdata7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA7_serr_expdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata8 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_serr_expdata8_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERR_EXPDATA8_serr_expdata8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_adr0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_merr_adr0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR0_merr_adr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_adr1 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_merr_adr1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ADR1_merr_adr1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_id : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_ID_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ID_merr_id_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_ID_merr_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_merr_rdata0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA0_merr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_merr_rdata1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA1_merr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_merr_rdata2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA2_merr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_merr_rdata3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA3_merr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_merr_rdata4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA4_merr_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_merr_rdata5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA5_merr_rdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_merr_rdata6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA6_merr_rdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_merr_rdata7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA7_merr_rdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata8 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_merr_rdata8_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_RDATA8_merr_rdata8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_merr_expdata0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA0_merr_expdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_merr_expdata1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA1_merr_expdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_merr_expdata2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA2_merr_expdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_merr_expdata3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA3_merr_expdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_merr_expdata4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA4_merr_expdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_merr_expdata5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA5_merr_expdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_merr_expdata6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA6_merr_expdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_merr_expdata7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA7_merr_expdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_expdata8 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_merr_expdata8_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERR_EXPDATA8_merr_expdata8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_cnt : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SERRCNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SERRCNT_serr_cnt_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SERRCNT_serr_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_cnt : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MERRCNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MERRCNT_merr_cnt_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MERRCNT_merr_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_wr : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_flux_wr_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WR_flux_wr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_rd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_flux_rd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RD_flux_rd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_wr_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_flux_wr_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_WCMD_flux_wr_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_rd_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_flux_rd_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUX_RCMD_flux_rd_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_wr : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_fluxid_wr_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WR_fluxid_wr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_rd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_fluxid_rd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RD_fluxid_rd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_wr_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_fluxid_wr_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_WCMD_fluxid_wr_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_rd_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_fluxid_rd_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_FLUXID_RCMD_fluxid_rd_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wlatcnt_min : 16;
        unsigned int wlatcnt_max : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_min_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_min_END (15)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_max_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_max_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wlatcnt_all : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_wlatcnt_all_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_WLATCNT1_wlatcnt_all_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rlatcnt_min : 16;
        unsigned int rlatcnt_max : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_min_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_min_END (15)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_max_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_max_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rlatcnt_all : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_rlatcnt_all_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RLATCNT1_rlatcnt_all_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inhere_rlatcnt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_inhere_rlatcnt_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_inhere_rlatcnt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stat_rpt : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DDRC_DMC_DDRC_STAT_RPT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_STAT_RPT_stat_rpt_START (0)
#define SOC_DDRC_DMC_DDRC_STAT_RPT_stat_rpt_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cmd_sum : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_dmc_cmd_sum_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_dmc_cmd_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_dat_sum : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_dmc_dat_sum_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_DAT_SUM_dmc_dat_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_pre_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_dmc_pre_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_PRE_CMD_dmc_pre_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_act_cmd : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_dmc_act_cmd_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_ACT_CMD_dmc_act_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_bnk_chg : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_dmc_bnk_chg_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_BNK_CHG_dmc_bnk_chg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_rnk_chg : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_dmc_rnk_chg_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RNK_CHG_dmc_rnk_chg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_rw_chg : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RW_CHG_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RW_CHG_dmc_rw_chg_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RW_CHG_dmc_rw_chg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tmon_err : 8;
        unsigned int reserved : 8;
        unsigned int tmon_err_rank : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_END (7)
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_rank_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_TMON_ERR_tmon_err_rank_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rerr_addrl : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_rerr_addrl_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRL_rerr_addrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rerr_addrh : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_rerr_addrh_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ADDRH_rerr_addrh_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rerr_id : 31;
        unsigned int rerr_type : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_ID_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_id_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_id_END (30)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_type_START (31)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_ID_rerr_type_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rerr_cnt : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_rerr_cnt_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_RERR_CNT_rerr_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crcerr_cnt : 16;
        unsigned int parerr_cnt : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_crcerr_cnt_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_crcerr_cnt_END (15)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_parerr_cnt_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR0_parerr_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overnum_cnt : 8;
        unsigned int crc_no_wr_cnt : 8;
        unsigned int rec_cnt : 4;
        unsigned int overnum_err : 1;
        unsigned int crc_no_wr : 1;
        unsigned int reseverd : 10;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_cnt_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_cnt_END (7)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_cnt_START (8)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_cnt_END (15)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_rec_cnt_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_rec_cnt_END (19)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_err_START (20)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_overnum_err_END (20)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_START (21)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_crc_no_wr_END (21)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_reseverd_START (22)
#define SOC_DDRC_DMC_DDRC_HIS_REC_ERR1_reseverd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bist_done : 1;
        unsigned int bist_pass : 1;
        unsigned int reserved_0 : 2;
        unsigned int parity_error : 1;
        unsigned int watchdog_error : 1;
        unsigned int diag_fifo_last : 1;
        unsigned int reserved_1 : 1;
        unsigned int diag_ip : 3;
        unsigned int reserved_2 : 1;
        unsigned int fingerprint : 4;
        unsigned int iter_cnt : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_done_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_done_END (0)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_pass_START (1)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_bist_pass_END (1)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_parity_error_START (4)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_parity_error_END (4)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_watchdog_error_START (5)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_watchdog_error_END (5)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_fifo_last_START (6)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_fifo_last_END (6)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_ip_START (8)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_diag_ip_END (10)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_fingerprint_START (12)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_fingerprint_END (15)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_iter_cnt_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_EXMBIST_STATUS_iter_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err : 1;
        unsigned int reserved_0 : 3;
        unsigned int mtest_bg_cnt : 4;
        unsigned int mtest_element : 3;
        unsigned int reserved_1 : 21;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_err_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_err_END (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_bg_cnt_START (4)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_bg_cnt_END (7)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_element_START (8)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_element_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_addr : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_mtest_err_addr_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRADDR_mtest_err_addr_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_mtest_exp_data0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_mtest_exp_data0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_mtest_exp_data1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_mtest_exp_data1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_mtest_exp_data2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_mtest_exp_data2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_mtest_exp_data3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_mtest_exp_data3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_mtest_exp_data4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_mtest_exp_data4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_mtest_exp_data5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_mtest_exp_data5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_mtest_exp_data6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_mtest_exp_data6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_mtest_exp_data7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_mtest_exp_data7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data8 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_mtest_exp_data8_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_mtest_exp_data8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data9 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_mtest_exp_data9_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_mtest_exp_data9_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data10 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_mtest_exp_data10_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_mtest_exp_data10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data11 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_mtest_exp_data11_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_mtest_exp_data11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data12 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_mtest_exp_data12_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_mtest_exp_data12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data13 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_mtest_exp_data13_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_mtest_exp_data13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data14 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_mtest_exp_data14_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_mtest_exp_data14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data15 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_mtest_exp_data15_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_mtest_exp_data15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data16 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_mtest_exp_data16_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_mtest_exp_data16_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data17 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_mtest_exp_data17_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_mtest_exp_data17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_mtest_err_data0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_mtest_err_data0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_mtest_err_data1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_mtest_err_data1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_mtest_err_data2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_mtest_err_data2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_mtest_err_data3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_mtest_err_data3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_mtest_err_data4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_mtest_err_data4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_mtest_err_data5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_mtest_err_data5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_mtest_err_data6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_mtest_err_data6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_mtest_err_data7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_mtest_err_data7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data8 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_mtest_err_data8_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_mtest_err_data8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data9 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_mtest_err_data9_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_mtest_err_data9_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data10 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_mtest_err_data10_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_mtest_err_data10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data11 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_mtest_err_data11_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_mtest_err_data11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data12 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_mtest_err_data12_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_mtest_err_data12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data13 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_mtest_err_data13_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_mtest_err_data13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data14 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_mtest_err_data14_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_mtest_err_data14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data15 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_mtest_err_data15_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_mtest_err_data15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data16 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_mtest_err_data16_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_mtest_err_data16_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data17 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_mtest_err_data17_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_mtest_err_data17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata0 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_rdata0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA0_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata1 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_rdata1_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA1_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata2 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_rdata2_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA2_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata3 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_rdata3_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA3_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata4 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_rdata4_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA4_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata5 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_rdata5_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA5_rdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata6 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_rdata6_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA6_rdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata7 : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_rdata7_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA7_rdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata_ecc0 : 8;
        unsigned int rdata_ecc1 : 8;
        unsigned int rdata_ecc2 : 8;
        unsigned int rdata_ecc3 : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc0_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc0_END (7)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc1_START (8)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc1_END (15)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc2_START (16)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc2_END (23)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc3_START (24)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata_dbi : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_rdata_dbi_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_DBI_rdata_dbi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata_ecc_dbi : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_rdata_ecc_dbi_START (0)
#define SOC_DDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_DBI_rdata_ecc_dbi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aref_farb_req : 16;
        unsigned int farb_aref_grant : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_aref_farb_req_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_aref_farb_req_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_farb_aref_grant_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT0_farb_aref_grant_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aref_farb_bp : 16;
        unsigned int farb_aref_bpidle : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_aref_farb_bp_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_aref_farb_bp_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_farb_aref_bpidle_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT1_farb_aref_bpidle_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_farb_req : 16;
        unsigned int farb_pd_grant : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_pd_farb_req_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_pd_farb_req_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_farb_pd_grant_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT2_farb_pd_grant_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_farb_bp : 16;
        unsigned int farb_pd_bpidle : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT3_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_pd_farb_bp_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_pd_farb_bp_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_farb_pd_bpidle_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT3_farb_pd_bpidle_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_farb_creq : 16;
        unsigned int aref_farb_creq : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT4_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_pd_farb_creq_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_pd_farb_creq_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_aref_farb_creq_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT4_aref_farb_creq_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int farb_cmd_idle : 1;
        unsigned int aref_farb_req_ex : 1;
        unsigned int farb_aref_ack : 1;
        unsigned int farb_cbug_grant : 29;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT5_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cmd_idle_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cmd_idle_END (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_aref_farb_req_ex_START (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_aref_farb_req_ex_END (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_aref_ack_START (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_aref_ack_END (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cbug_grant_START (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT5_farb_cbug_grant_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sref_farb_req : 1;
        unsigned int farb_sref_grant : 1;
        unsigned int sref_farb_flush : 1;
        unsigned int farb_sref_idle : 1;
        unsigned int sref_farb_creq : 1;
        unsigned int sfc_farb_req : 1;
        unsigned int farb_sfc_grant : 1;
        unsigned int sfc_farb_bp : 1;
        unsigned int farb_sfc_ack : 1;
        unsigned int farb_sfc_bpidle : 1;
        unsigned int sfc_farb_creq : 1;
        unsigned int eccwb_farb_req : 1;
        unsigned int farb_eccwb_grant : 1;
        unsigned int eccwb_farb_bp : 1;
        unsigned int farb_eccwb_ack : 1;
        unsigned int eccwb_farb_creq : 1;
        unsigned int phyupd_farb_req : 1;
        unsigned int farb_phyupd_grant : 1;
        unsigned int phyupd_farb_bp : 1;
        unsigned int farb_phyupd_ack : 1;
        unsigned int phyupd_farb_creq : 1;
        unsigned int reserved_0 : 2;
        unsigned int que_func_ack : 1;
        unsigned int func_que_flush : 1;
        unsigned int que_func_idle : 1;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT6_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_req_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_req_END (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_grant_START (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_grant_END (1)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_flush_START (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_flush_END (2)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_idle_START (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sref_idle_END (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_creq_START (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sref_farb_creq_END (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_req_START (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_req_END (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_grant_START (6)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_grant_END (6)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_bp_START (7)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_bp_END (7)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_ack_START (8)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_ack_END (8)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_bpidle_START (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_sfc_bpidle_END (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_creq_START (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_sfc_farb_creq_END (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_req_START (11)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_req_END (11)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_grant_START (12)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_grant_END (12)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_bp_START (13)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_bp_END (13)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_ack_START (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_eccwb_ack_END (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_creq_START (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_eccwb_farb_creq_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_req_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_req_END (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_grant_START (17)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_grant_END (17)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_bp_START (18)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_bp_END (18)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_ack_START (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_farb_phyupd_ack_END (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_creq_START (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_phyupd_farb_creq_END (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_ack_START (23)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_ack_END (23)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_func_que_flush_START (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_func_que_flush_END (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_idle_START (25)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT6_que_func_idle_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_state_rnk0 : 5;
        unsigned int pd_state_rnk1 : 5;
        unsigned int pd_state_rnk2 : 5;
        unsigned int pd_state_rnk3 : 5;
        unsigned int pd_state_rnk4 : 5;
        unsigned int pd_state_rnk5 : 5;
        unsigned int reserved : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT7_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk0_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk0_END (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk1_START (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk1_END (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk2_START (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk2_END (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk3_START (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk3_END (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk4_START (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk4_END (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk5_START (25)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT7_pd_state_rnk5_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_state_rnk6 : 5;
        unsigned int pd_state_rnk7 : 5;
        unsigned int pd_state_rnk8 : 5;
        unsigned int pd_state_rnk9 : 5;
        unsigned int pd_state_rnk10 : 5;
        unsigned int pd_state_rnk11 : 5;
        unsigned int reserved : 2;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT8_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk6_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk6_END (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk7_START (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk7_END (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk8_START (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk8_END (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk9_START (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk9_END (19)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk10_START (20)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk10_END (24)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk11_START (25)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT8_pd_state_rnk11_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_state_rnk12 : 5;
        unsigned int pd_state_rnk13 : 5;
        unsigned int pd_state_rnk14 : 5;
        unsigned int pd_state_rnk15 : 5;
        unsigned int reserved : 12;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT9_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk12_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk12_END (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk13_START (5)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk13_END (9)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk14_START (10)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk14_END (14)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk15_START (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT9_pd_state_rnk15_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aref_state : 4;
        unsigned int sref_state : 4;
        unsigned int sfc_state : 5;
        unsigned int phyupd_state : 4;
        unsigned int reserved : 15;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT10_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_aref_state_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_aref_state_END (3)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sref_state_START (4)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sref_state_END (7)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sfc_state_START (8)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_sfc_state_END (12)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_phyupd_state_START (13)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT10_phyupd_state_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_zq_req : 16;
        unsigned int pd_zq_grant : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_FUNC_STAT11_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_req_START (0)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_req_END (15)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_grant_START (16)
#define SOC_DDRC_DMC_DDRC_FUNC_STAT11_pd_zq_grant_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sb_fifo_full : 1;
        unsigned int sb_fifo_empty : 1;
        unsigned int rp_fifo_full : 1;
        unsigned int rp_fifo_empty : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DDRC_DMC_STAT12_UNION;
#endif
#define SOC_DDRC_DMC_STAT12_sb_fifo_full_START (0)
#define SOC_DDRC_DMC_STAT12_sb_fifo_full_END (0)
#define SOC_DDRC_DMC_STAT12_sb_fifo_empty_START (1)
#define SOC_DDRC_DMC_STAT12_sb_fifo_empty_END (1)
#define SOC_DDRC_DMC_STAT12_rp_fifo_full_START (2)
#define SOC_DDRC_DMC_STAT12_rp_fifo_full_END (2)
#define SOC_DDRC_DMC_STAT12_rp_fifo_empty_START (3)
#define SOC_DDRC_DMC_STAT12_rp_fifo_empty_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ram_tmod : 32;
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_ram_tmod_START (0)
#define SOC_DDRC_DMC_DDRC_TEST_RAM_TMOD_ram_tmod_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mddrc_dmc_version : 16;
        unsigned int mddrc_dmc_width : 4;
        unsigned int mddrc_ecc_width : 4;
        unsigned int mddrc_cfifo_num : 8;
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_version_START (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_version_END (15)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_width_START (16)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_dmc_width_END (19)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_ecc_width_START (20)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_ecc_width_END (23)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_cfifo_num_START (24)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG0_mddrc_cfifo_num_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mddrc_rank_num : 4;
        unsigned int mddrc_addr_width : 4;
        unsigned int mddrc_phy_type : 8;
        unsigned int mddrc_bank_xor_pos : 5;
        unsigned int reserved_0 : 3;
        unsigned int mddrc_mbist_type : 2;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_rank_num_START (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_rank_num_END (3)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_addr_width_START (4)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_addr_width_END (7)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_phy_type_START (8)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_phy_type_END (15)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_bank_xor_pos_START (16)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_bank_xor_pos_END (20)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_mbist_type_START (24)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG1_mddrc_mbist_type_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mddrc_rlast_en : 1;
        unsigned int mddrc_ffbyp_en : 1;
        unsigned int mddrc_phy_in_flop : 1;
        unsigned int mddrc_ecc_en : 1;
        unsigned int mddrc_debug_bus : 1;
        unsigned int mddrc_crc_pipe_en : 1;
        unsigned int mddrc_ram_ecc_en : 1;
        unsigned int mddrc_rec_en : 1;
        unsigned int mddrc_hdr_mode : 2;
        unsigned int mddrc_dasw_pipe_en : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rlast_en_START (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rlast_en_END (0)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ffbyp_en_START (1)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ffbyp_en_END (1)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_phy_in_flop_START (2)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_phy_in_flop_END (2)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ecc_en_START (3)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ecc_en_END (3)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_debug_bus_START (4)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_debug_bus_END (4)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_crc_pipe_en_START (5)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_crc_pipe_en_END (5)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ram_ecc_en_START (6)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_ram_ecc_en_END (6)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rec_en_START (7)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_rec_en_END (7)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_hdr_mode_START (8)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_hdr_mode_END (9)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_dasw_pipe_en_START (10)
#define SOC_DDRC_DMC_DDRC_TEST_RTL_CFG2_mddrc_dasw_pipe_en_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int osc_count : 16;
        unsigned int osc_count_base : 16;
    } reg;
} SOC_DDRC_DMC_DDRC_OSC_COUNT_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_START (0)
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_END (15)
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_base_START (16)
#define SOC_DDRC_DMC_DDRC_OSC_COUNT_osc_count_base_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int edxn_dq0_map : 3;
        unsigned int reserved_0 : 1;
        unsigned int edxn_dq1_map : 3;
        unsigned int reserved_1 : 1;
        unsigned int edxn_dq2_map : 3;
        unsigned int reserved_2 : 1;
        unsigned int edxn_dq3_map : 3;
        unsigned int reserved_3 : 1;
        unsigned int edxn_dq4_map : 3;
        unsigned int reserved_4 : 1;
        unsigned int edxn_dq5_map : 3;
        unsigned int reserved_5 : 1;
        unsigned int edxn_dq6_map : 3;
        unsigned int reserved_6 : 1;
        unsigned int edxn_dq7_map : 3;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_EDXN_DQMAP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq0_map_START (0)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq0_map_END (2)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq1_map_START (4)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq1_map_END (6)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq2_map_START (8)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq2_map_END (10)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq3_map_START (12)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq3_map_END (14)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq4_map_START (16)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq4_map_END (18)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq5_map_START (20)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq5_map_END (22)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq6_map_START (24)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq6_map_END (26)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq7_map_START (28)
#define SOC_DDRC_DMC_DDRC_EDXN_DQMAP_edxn_dq7_map_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int odxn_dq0_map : 3;
        unsigned int reserved_0 : 1;
        unsigned int odxn_dq1_map : 3;
        unsigned int reserved_1 : 1;
        unsigned int odxn_dq2_map : 3;
        unsigned int reserved_2 : 1;
        unsigned int odxn_dq3_map : 3;
        unsigned int reserved_3 : 1;
        unsigned int odxn_dq4_map : 3;
        unsigned int reserved_4 : 1;
        unsigned int odxn_dq5_map : 3;
        unsigned int reserved_5 : 1;
        unsigned int odxn_dq6_map : 3;
        unsigned int reserved_6 : 1;
        unsigned int odxn_dq7_map : 3;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_DDRC_DMC_DDRC_ODXN_DQMAP_UNION;
#endif
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq0_map_START (0)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq0_map_END (2)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq1_map_START (4)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq1_map_END (6)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq2_map_START (8)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq2_map_END (10)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq3_map_START (12)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq3_map_END (14)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq4_map_START (16)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq4_map_END (18)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq5_map_START (20)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq5_map_END (22)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq6_map_START (24)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq6_map_END (26)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq7_map_START (28)
#define SOC_DDRC_DMC_DDRC_ODXN_DQMAP_odxn_dq7_map_END (30)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
